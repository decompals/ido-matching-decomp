#!/usr/bin/env python3
"""Compute matching progress from an objdiff report.

The objdiff report is the source of truth for matches: a function is matched
only when objdiff reports a 100% fuzzy match and a real base symbol or target
to base mapping exists.  Target objects without a base object are still counted
as unmatched so unstarted source files stay in the denominator.

Library code is classified by ``library/member`` names in
``symbols/<version>/<program>.splits.csv``.  Report library units are named
``<version>/<library>/<program>/<member>`` and use the shared base object at
``build/src/<version>/<library>/<member>.o``.  Every copy of a library function
in every program binary is counted separately, including static functions.
Data sections are assigned to a library only when a split row covers the whole
split section interval.  In each section, everything after the first library
range is non-program: it is either library code or belongs to nobody and is
excluded from progress.  Target objects are enumerated from ``asm`` so stale
``build/asm`` objects from older splits cannot affect progress.
"""

from __future__ import annotations

import hashlib
import json
import re
import sys
from collections import defaultdict
from functools import lru_cache
from pathlib import Path
from typing import NamedTuple

from elftools.elf.elffile import ELFFile

from library import (
    DATA_SECTIONS,
    LibraryRanges,
    function_address,
    library_base_path,
    section_intervals,
    section_start,
    section_starts,
    split_intervals,
)

ROOT = Path(__file__).resolve().parent.parent
REPORT = ROOT / "build/report.json"
MARKDOWN = ROOT / "PROGRESS.md"
ASM_BUILD_ROOT = ROOT / "build/asm"
ASM_ROOT = ROOT / "asm"

VERSIONS = ("5.3", "7.1")
TARGET_SUFFIXES = (".text.s", ".data.s", ".rodata.s", ".bss.s")

# Symbols that are not part of the decompilation denominator.  Keep these
# anchored so ordinary functions such as current_address_pair_start or
# mem_start are not excluded by accident.
EXCLUDED_NAME_PATTERNS = (
    re.compile(r"^__start$"),
    re.compile(r"^__start_[A-Za-z0-9_]*$"),
    re.compile(r"^_start$"),
    re.compile(r"^_mcount$"),
    re.compile(r"^__mcount$"),
    re.compile(r"^_ftext$"),
    re.compile(r"^_rld_[A-Za-z0-9_]*$"),
    re.compile(r"^_*crt[A-Za-z0-9_]*$"),
    re.compile(r"^_*runtime[A-Za-z0-9_]*$"),
    re.compile(r"^__runtime_[A-Za-z0-9_]*$"),
)


class ElfData(NamedTuple):
    functions: list[dict]
    sections: dict[str, dict]
    text: bytes
    text_ranges: list[tuple[int, int]]


@lru_cache(maxsize=None)
def read_elf(path: Path) -> ElfData:
    """Read all ELF data needed by progress in one pass."""

    functions: list[dict] = []
    sections: dict[str, dict] = {}
    text = b""

    with path.open("rb") as f:
        elf = ELFFile(f)

        symtab = elf.get_section_by_name(".symtab")
        if symtab is not None:
            for symbol in symtab.iter_symbols():
                name = symbol.name
                if not name or name.endswith(".NON_MATCHING"):
                    continue
                if symbol["st_info"]["type"] not in ("STT_FUNC", "STT_NOTYPE"):
                    continue
                section_index = symbol["st_shndx"]
                if (
                    not isinstance(section_index, int)
                    or section_index <= 0
                    or section_index >= elf.num_sections()
                ):
                    continue
                size = symbol["st_size"]
                if size <= 0:
                    continue
                section = elf.get_section(section_index)
                if section is None or not (section["sh_flags"] & 0x4):
                    continue
                functions.append(
                    {
                        "name": name,
                        "size": size,
                        "address": str(symbol["st_value"]),
                        "section": section.name,
                    }
                )

        text_section = elf.get_section_by_name(".text")
        if text_section is not None:
            text = text_section.data()

        for name in DATA_SECTIONS:
            section = elf.get_section_by_name(name)
            if section is None:
                continue
            size = section["sh_size"]
            if size <= 0:
                continue
            sections[name] = {
                "size": size,
                "digest": hashlib.sha1(section.data()).hexdigest(),
            }

    text_ranges = [
        (int(function["address"]), int(function["address"]) + function["size"])
        for function in functions
        if function["section"] == ".text"
    ]
    return ElfData(functions, sections, text, text_ranges)


def is_excluded_name(name: str) -> bool:
    return any(pattern.match(name) for pattern in EXCLUDED_NAME_PATTERNS)


def is_excluded_unit(rel: str) -> bool:
    return is_excluded_name(Path(rel).name)


def is_padding_unit(rel: str) -> bool:
    return Path(rel).name.startswith("pad_")


def load_overrides(version: str, program: str) -> dict[str, str]:
    path = ROOT / "symbols" / version / f"{program}.match_overrides.txt"
    if not path.is_file():
        return {}

    overrides: dict[str, str] = {}
    for raw_line in path.read_text(encoding="utf-8").splitlines():
        line = raw_line.split("#", 1)[0].strip()
        if not line or "=" not in line:
            continue
        target, action = (part.strip() for part in line.split("=", 1))
        if action == "matched":
            overrides[target] = "matched"
        elif action in ("ignored", "excluded"):
            overrides[target] = "ignored"
    return overrides


def load_report(path: Path) -> dict:
    with path.open("r", encoding="utf-8") as f:
        return json.load(f)


def load_objdiff_units() -> dict[str, dict]:
    path = ROOT / "objdiff.json"
    if not path.is_file():
        return {}
    try:
        with path.open("r", encoding="utf-8") as f:
            config = json.load(f)
    except (OSError, json.JSONDecodeError):
        return {}
    return {
        unit.get("name", ""): unit
        for unit in config.get("units", [])
        if unit.get("name")
    }


def symbol_mappings_from_units(units: dict[str, dict]) -> dict[str, dict[str, str]]:
    return {
        name: unit.get("symbol_mappings", {})
        for name, unit in units.items()
    }


def target_signature(functions: list[dict]) -> tuple:
    return tuple(
        sorted(
            (function["name"], function["size"], function["address"], function["section"])
            for function in functions
        )
    )


def target_data_signature(sections: dict[str, dict]) -> tuple:
    return tuple(
        sorted(
            (name, value["size"], value.get("digest"))
            for name, value in sections.items()
        )
    )


def section_fuzzy_by_name(unit: dict | None) -> dict[str, float]:
    if unit is None:
        return {}
    return {
        section.get("name", ""): float(section.get("fuzzy_match_percent", 0.0))
        for section in unit.get("sections", [])
    }


def is_library_unit_name(name: str, library_names: set[str]) -> bool:
    parts = name.split("/")
    return len(parts) == 4 and parts[1] in library_names


def library_unit_key(
    unit: dict,
    library_names: set[str],
    config_unit: dict | None = None,
) -> tuple[str, str, str, str, str] | None:
    """Return ``(version, program, target_rel, library, member)``.

    The objdiff report drops the library metadata fields, so fall back to the
    generated ``objdiff.json`` unit and finally to the four-part unit name.
    """

    name = unit.get("name", "")
    version = name.split("/", 1)[0]
    metadata: dict = {}
    if config_unit is not None:
        metadata.update(config_unit.get("metadata") or {})
    metadata.update(unit.get("metadata") or {})

    library = metadata.get("library_name")
    module = metadata.get("library_module")
    program = metadata.get("target_program")
    rel = metadata.get("target_rel")
    if not (library and module and program and rel):
        parts = name.split("/")
        if len(parts) != 4 or parts[1] not in library_names:
            return None
        version, library, program, module = parts
        rel = f"{library}/{module}"
    return (version, program, rel, library, module)


def library_report_units(
    report: dict, library_names: set[str], config_units: dict[str, dict]
) -> dict[tuple[str, str, str, str, str], dict]:
    units: dict[tuple[str, str, str, str, str], dict] = {}
    for unit in report.get("units", []):
        name = unit.get("name", "")
        key = library_unit_key(unit, library_names, config_units.get(name))
        if key is not None:
            units[key] = unit
    return units


def disassembled_programs(version: str) -> set[str]:
    """Programs whose disassembly was generated by the current ``make disasm``."""

    version_dir = ASM_ROOT / version
    if not version_dir.is_dir():
        return set()
    return {
        path.name
        for path in version_dir.iterdir()
        if path.is_dir() and (path / ".disasm").is_file()
    }


def target_objects(
    version: str,
    asm_build_root: Path,
    split_names: set[tuple[str, str]] | None = None,
) -> list[tuple[str, str, Path]]:
    """List target objects present in the disassembly tree.

    Scanning ``build/asm`` directly would include stale objects left by older
    splits.  Deriving the list from ``asm`` keeps progress consistent with
    ``gen_objdiff.py`` and ignores those stale files.  When ``split_names`` is
    given, objects whose split row was removed are ignored too, so stale ``asm``
    files cannot keep old content in progress.
    """

    version_dir = ASM_ROOT / version
    if not version_dir.is_dir():
        return []

    objects: list[tuple[str, str, Path]] = []
    for program_dir in sorted(path for path in version_dir.iterdir() if path.is_dir()):
        program = program_dir.name
        rels: set[str] = set()
        for source in sorted(program_dir.rglob("*.s")):
            relative = source.relative_to(program_dir).as_posix()
            for suffix in TARGET_SUFFIXES:
                if relative.endswith(suffix):
                    rels.add(relative[: -len(suffix)])
                    break
        for rel in sorted(rels):
            if split_names is not None and (program, rel) not in split_names:
                continue
            target_path = asm_build_root / version / program / f"{rel}.o"
            if target_path.is_file():
                objects.append((program, rel, target_path))
    return objects


def load_units(
    report: dict, asm_build_root: Path, library_names: set[str]
) -> list[dict]:
    """Load report units and target-only objects with their split layout."""

    units: list[dict] = []
    report_target_paths: set[Path] = set()
    seen_signatures: dict[tuple[str, str], set[tuple]] = {}
    starts = {version: section_starts(version) for version in VERSIONS}
    splits = {version: split_intervals(version) for version in VERSIONS}
    split_names = {
        version: {
            (program, name)
            for (program, _section, name) in splits[version]
        }
        for version in VERSIONS
    }
    active_programs = {
        version: disassembled_programs(version) for version in VERSIONS
    }

    for unit in report.get("units", []):
        name = unit.get("name", "")
        if is_library_unit_name(name, library_names):
            continue
        metadata = unit.get("metadata", {})
        parts = name.split("/", 2)
        if len(parts) != 3:
            continue
        version, program, rel = parts
        if version not in VERSIONS or is_excluded_unit(rel):
            continue
        if program not in active_programs[version]:
            continue
        if (program, rel) not in split_names[version]:
            continue

        source_path = metadata.get("source_path")
        auto_generated = bool(metadata.get("auto_generated", source_path is None))
        complete = bool(metadata.get("complete", True))
        has_source = bool(source_path) and not auto_generated and complete

        target_path = asm_build_root / version / program / f"{rel}.o"
        report_target_paths.add(target_path)
        target_elf = read_elf(target_path) if target_path.is_file() else None
        sections = target_elf.sections if target_elf is not None else {}
        if not sections:
            sections = {
                section.get("name", ""): {"size": int(section.get("size", "0"))}
                for section in unit.get("sections", [])
                if section.get("name") in DATA_SECTIONS
            }
        intervals = section_intervals(
            starts[version], program, rel, sections, splits[version]
        )
        functions = [
            {
                "name": function.get("name", ""),
                "size": int(function.get("size", "0")),
                "address": function.get("address"),
                "section": ".text",
                "fuzzy": function.get("fuzzy_match_percent"),
            }
            for function in unit.get("functions", [])
            if function.get("name")
        ]
        base_path = asm_build_root.parent / "src" / version / program / f"{rel}.o"
        units.append(
            {
                "version": version,
                "program": program,
                "rel": rel,
                "target_path": target_path,
                "report_unit": unit,
                "functions": functions,
                "sections": sections,
                "intervals": intervals,
                "has_source": has_source,
                "base_path": base_path if base_path.is_file() else None,
                "unit_name": f"{version}/{program}/{rel}",
            }
        )

    for version in VERSIONS:
        for program, rel, target_path in target_objects(
            version, asm_build_root, split_names[version]
        ):
            if program not in active_programs[version]:
                continue
            if target_path in report_target_paths:
                continue
            if is_excluded_unit(rel):
                continue

            target_elf = read_elf(target_path)
            if not target_elf.functions and not target_elf.sections:
                continue
            if target_elf.functions:
                signature = ("functions", target_signature(target_elf.functions))
            else:
                signature = ("data", target_data_signature(target_elf.sections))
            seen = seen_signatures.setdefault((version, program), set())
            if signature in seen:
                continue
            seen.add(signature)

            intervals = section_intervals(
                starts[version],
                program,
                rel,
                target_elf.sections,
                splits[version],
            )
            functions = [
                {
                    "name": function["name"],
                    "size": function["size"],
                    "address": function["address"],
                    "section": function["section"],
                    "fuzzy": None,
                }
                for function in target_elf.functions
            ]
            units.append(
                {
                    "version": version,
                    "program": program,
                    "rel": rel,
                    "target_path": target_path,
                    "report_unit": None,
                    "functions": functions,
                    "sections": target_elf.sections,
                    "intervals": intervals,
                    "has_source": False,
                    "base_path": None,
                    "unit_name": f"{version}/{program}/{rel}",
                }
            )

    return units


def library_section_cutoffs(version: str) -> dict[tuple[str, str], int]:
    """First library address in each program section.

    Once a section reaches its first library range, everything later is not
    program code.  It is either part of a library range or belongs to nobody
    and is left out of progress entirely.
    """

    cutoffs: dict[tuple[str, str], int] = {}
    for (program, section, name), (start, _end) in split_intervals(version).items():
        if "/" not in name:
            continue
        key = (program, section)
        cutoffs[key] = min(cutoffs.get(key, start), start)
    return cutoffs


def classify(
    units: list[dict],
    ranges: dict[str, LibraryRanges],
    library_units: dict[tuple[str, str, str, str, str], dict],
    starts: dict[str, dict],
    cutoffs: dict[str, dict[tuple[str, str], int]],
    overrides: dict[tuple[str, str], dict[str, str]],
) -> list[dict]:
    classified: list[dict] = []

    for unit in units:
        version = unit["version"]
        program = unit["program"]
        rel = unit["rel"]
        unit_overrides = overrides.setdefault((version, program), {})
        report_unit = unit["report_unit"]
        report_sections = section_fuzzy_by_name(report_unit)
        program_functions: list[dict] = []
        library_functions: dict[tuple[str, str], list[dict]] = defaultdict(list)
        program_sections: dict[str, dict] = {}
        library_sections: dict[tuple[str, str], dict[str, dict]] = defaultdict(dict)

        for function in unit["functions"]:
            name = function["name"]
            if name.endswith(".NON_MATCHING") or is_excluded_name(name):
                continue
            action = unit_overrides.get(name)
            if action == "ignored":
                continue

            section = function.get("section", ".text")
            address = None
            try:
                if function.get("address") is not None:
                    address = function_address(
                        starts[version],
                        program,
                        rel,
                        section,
                        int(function["address"]),
                    )
            except (TypeError, ValueError):
                address = None

            match = (
                ranges[version].find(program, address)
                if address is not None and section == ".text"
                else None
            )
            if match is None and is_padding_unit(rel):
                continue
            cutoff = cutoffs[version].get((program, section))
            if (
                match is None
                and cutoff is not None
                and address is not None
                and address >= cutoff
            ):
                continue

            record = {
                "name": name,
                "size": int(function.get("size", 0)),
                "fuzzy": function.get("fuzzy"),
                "action": action,
                "matched": False,
                "reason": "unmatched",
            }
            if match is not None:
                category = match.category
                library_unit = library_units.get(
                    (version, program, rel, category[0], category[1])
                )
                record["fuzzy"] = function_fuzzy(library_unit, name)
                record["category"] = category
                record["base_path"] = library_base_path(
                    version, category[0], category[1]
                )
                record["mapping_unit"] = (
                    f"{version}/{category[0]}/{program}/{category[1]}"
                )
                library_functions[category].append(record)
            else:
                record["has_source"] = unit["has_source"]
                record["base_path"] = unit["base_path"]
                record["mapping_unit"] = unit["unit_name"]
                program_functions.append(record)

        for section_name in DATA_SECTIONS:
            interval = unit["intervals"].get(section_name)
            if interval is not None:
                total = interval[1] - interval[0]
            else:
                total = int(unit["sections"].get(section_name, {}).get("size", 0))
            if total <= 0:
                continue

            interval_start = (
                interval[0]
                if interval is not None
                else section_start(
                    starts[version], program, rel, section_name
                )
            )
            match = (
                ranges[version].find_section(program, interval[0], interval[1])
                if interval is not None
                else None
            )
            if match is None and is_padding_unit(rel):
                continue
            cutoff = cutoffs[version].get((program, section_name))
            if (
                match is None
                and cutoff is not None
                and interval_start is not None
                and interval_start >= cutoff
            ):
                continue
            if match is not None:
                category = match.category
                library_unit = library_units.get(
                    (version, program, rel, category[0], category[1])
                )
                fuzzy = section_fuzzy_by_name(library_unit).get(section_name, 0.0)
                library_sections[category][section_name] = {
                    "total": total,
                    "fuzzy": fuzzy,
                }
            else:
                program_sections[section_name] = {
                    "total": total,
                    "fuzzy": report_sections.get(section_name, 0.0),
                }

        classified.append(
            {
                "version": version,
                "program": program,
                "rel": rel,
                "program_functions": program_functions,
                "library_functions": dict(library_functions),
                "program_sections": program_sections,
                "library_sections": dict(library_sections),
            }
        )

    return classified


def function_fuzzy(unit: dict | None, name: str) -> float | None:
    if unit is None:
        return None
    for function in unit.get("functions", []):
        if function.get("name") == name:
            fuzzy = function.get("fuzzy_match_percent")
            return float(fuzzy) if fuzzy is not None else None
    return None


@lru_cache(maxsize=None)
def base_function_names(path: Path | None) -> frozenset[str]:
    if path is None or not path.is_file():
        return frozenset()
    return frozenset(function["name"] for function in read_elf(path).functions)


def match(
    classified: list[dict],
    symbol_mappings: dict[str, dict[str, str]],
) -> None:
    for unit in classified:
        for function in unit["program_functions"]:
            action = function.get("action")
            if action == "matched":
                function["matched"] = True
                function["reason"] = "override"
                continue
            if not function.get("has_source"):
                function["reason"] = "no-source"
                continue
            fuzzy = function.get("fuzzy")
            if fuzzy is None or float(fuzzy) < 100.0 - 1e-9:
                continue
            names = base_function_names(function.get("base_path"))
            mapping = symbol_mappings.get(function.get("mapping_unit", ""), {})
            if (
                function["name"] not in names
                and mapping.get(function["name"]) not in names
            ):
                function["reason"] = "no-base"
                continue
            function["matched"] = True
            function["reason"] = "matched"

        for functions in unit["library_functions"].values():
            for function in functions:
                action = function.get("action")
                if action == "matched":
                    function["matched"] = True
                    function["reason"] = "override"
                    continue
                names = base_function_names(function.get("base_path"))
                mapping = symbol_mappings.get(function.get("mapping_unit", ""), {})
                if (
                    function["name"] not in names
                    and mapping.get(function["name"]) not in names
                ):
                    function["reason"] = "no-base"
                    continue
                fuzzy = function.get("fuzzy")
                if fuzzy is None or float(fuzzy) < 100.0 - 1e-9:
                    continue
                function["matched"] = True
                function["reason"] = "matched"


def empty_measures() -> dict:
    return {
        "functions": 0,
        "matched_functions": 0,
        "code": 0,
        "matched_code": 0,
        "sections": {
            section_name: {"total": 0, "matched": 0}
            for section_name in DATA_SECTIONS
        },
        "units": 0,
    }


def build_measures(functions: list[dict], sections: dict[str, dict]) -> dict:
    measures = empty_measures()
    measures["functions"] = len(functions)
    measures["matched_functions"] = sum(
        1 for function in functions if function["matched"]
    )
    measures["code"] = sum(function["size"] for function in functions)
    measures["matched_code"] = sum(
        function["size"] for function in functions if function["matched"]
    )
    for section_name, section in sections.items():
        total = int(section.get("total", 0))
        fuzzy = float(section.get("fuzzy", 0.0))
        measures["sections"][section_name] = {
            "total": total,
            "matched": int(round(total * fuzzy / 100.0)),
        }
    measures["units"] = 1
    return measures


def add_measures(target: dict, measures: dict) -> None:
    target["functions"] += measures["functions"]
    target["matched_functions"] += measures["matched_functions"]
    target["code"] += measures["code"]
    target["matched_code"] += measures["matched_code"]
    target["units"] += measures["units"]
    for section_name in DATA_SECTIONS:
        target["sections"][section_name]["total"] += measures["sections"][
            section_name
        ]["total"]
        target["sections"][section_name]["matched"] += measures["sections"][
            section_name
        ]["matched"]


def aggregate(classified: list[dict]) -> dict:
    programs: dict[str, dict] = {}
    libraries: dict[str, dict] = {}
    versions: dict[str, dict] = {}

    def add_program(version: str, program: str, measures: dict) -> None:
        add_measures(
            programs.setdefault(f"{version}/{program}", empty_measures()), measures
        )
        add_measures(versions.setdefault(version, empty_measures()), measures)

    def add_library(version: str, library: str, measures: dict) -> None:
        add_measures(
            libraries.setdefault(f"{version}/{library}", empty_measures()), measures
        )
        add_measures(versions.setdefault(version, empty_measures()), measures)

    for unit in classified:
        version = unit["version"]
        program = unit["program"]
        program_sections = unit["program_sections"]
        if unit["program_functions"] or any(
            section["total"] > 0 for section in program_sections.values()
        ):
            add_program(
                version,
                program,
                build_measures(unit["program_functions"], program_sections),
            )

        categories = set(unit["library_functions"]) | set(unit["library_sections"])
        for category in categories:
            functions = unit["library_functions"].get(category, [])
            sections = unit["library_sections"].get(category, {})
            if not functions and not any(
                section["total"] > 0 for section in sections.values()
            ):
                continue
            add_library(
                version,
                category[0],
                build_measures(functions, sections),
            )

    totals = empty_measures()
    for scope in (programs, libraries):
        for value in scope.values():
            add_measures(totals, value)

    return {
        "versions": {key: versions[key] for key in sorted(versions)},
        "programs": {key: programs[key] for key in sorted(programs)},
        "libraries": {key: libraries[key] for key in sorted(libraries)},
        "totals": totals,
    }


def percent(matched: int, total: int) -> str:
    if total <= 0:
        return "0.00%"
    return f"{matched * 100.0 / total:.2f}%"


def section_percent(measures: dict, section_name: str) -> str:
    section = measures["sections"][section_name]
    return percent(section["matched"], section["total"])


def render_markdown(result: dict) -> str:
    programs = result["programs"]
    libraries = result["libraries"]
    versions = sorted(
        {key.split("/", 1)[0] for key in (*programs, *libraries)},
        reverse=True,
    )

    def row(label_version: str, label: str, measures: dict) -> str:
        return (
            f"| {label_version} | {label} | {measures['functions']} | "
            f"{measures['matched_functions']} | "
            f"{percent(measures['matched_code'], measures['code'])} | "
            f"{section_percent(measures, '.data')} | "
            f"{section_percent(measures, '.rodata')} |"
        )

    def subtotal(scope: dict[str, dict], version: str | None = None) -> dict:
        measures = empty_measures()
        for key, value in scope.items():
            if version is not None and key.split("/", 1)[0] != version:
                continue
            add_measures(measures, value)
        return measures

    def table(title: str, label: str, scope: dict[str, dict]) -> list[str]:
        lines = [
            f"## {title}",
            "",
            f"| Version | {label} | Functions | Matched | Code | .data | .rodata |",
            "| --- | --- | ---: | ---: | ---: | ---: | ---: |",
        ]
        for version in versions:
            rows = [
                row(version, name, scope[key])
                for key in sorted(scope)
                for key_version, name in [key.split("/", 1)]
                if key_version == version
            ]
            if not rows:
                continue
            lines.extend(rows)
            lines.append(row(version, "**subtotal**", subtotal(scope, version)))
        lines.append(row("**all**", f"**all {title.lower()}**", subtotal(scope)))
        lines.append("")
        return lines

    def summary_row(label: str, measures: dict) -> str:
        return (
            f"| {label} | {measures['functions']} | "
            f"{measures['matched_functions']} | "
            f"{percent(measures['matched_code'], measures['code'])} | "
            f"{section_percent(measures, '.data')} | "
            f"{section_percent(measures, '.rodata')} |"
        )

    lines = ["# Progress", ""]
    lines.extend(table("Programs", "Program", programs))
    lines.extend(table("Libraries", "Library", libraries))
    lines.extend(
        [
            "## Total",
            "",
            "| Scope | Functions | Matched | Code | .data | .rodata |",
            "| --- | ---: | ---: | ---: | ---: | ---: |",
            summary_row("Programs", subtotal(programs)),
            summary_row("Libraries", subtotal(libraries)),
            summary_row("**All**", result["totals"]),
            "",
            "Percentages are matched byte percentages.",
            "",
            "Only programs with a generated disassembly (`.disasm` stamp) are "
            "included. Library rows are statically linked library code found in "
            "target objects. They are counted separately from the program that "
            "embeds them; library splits are named `library/member`.",
            "",
        ]
    )
    return "\n".join(lines)


def write_if_changed(path: Path, content: str) -> bool:
    if path.is_file():
        try:
            if path.read_text(encoding="utf-8") == content:
                return False
        except UnicodeDecodeError:
            pass
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content, encoding="utf-8")
    return True


def main() -> int:
    if not REPORT.is_file():
        print(f"error: report not found: {REPORT}", file=sys.stderr)
        return 2

    report = load_report(REPORT)
    ranges = {version: LibraryRanges(version) for version in VERSIONS}
    library_names = {
        library
        for version_ranges in ranges.values()
        for library, _module in version_ranges.categories()
    }
    config_units = load_objdiff_units()
    units = load_units(report, ASM_BUILD_ROOT, library_names)
    starts = {version: section_starts(version) for version in VERSIONS}
    cutoffs = {version: library_section_cutoffs(version) for version in VERSIONS}
    library_units = library_report_units(report, library_names, config_units)
    symbol_mappings = symbol_mappings_from_units(config_units)
    overrides: dict[tuple[str, str], dict[str, str]] = {}
    for unit in units:
        key = (unit["version"], unit["program"])
        if key not in overrides:
            overrides[key] = load_overrides(*key)

    classified = classify(
        units, ranges, library_units, starts, cutoffs, overrides
    )
    match(classified, symbol_mappings)
    result = aggregate(classified)

    markdown = render_markdown(result)
    markdown_changed = write_if_changed(MARKDOWN, markdown)

    totals = result["totals"]
    function_units = sum(
        program["units"] for program in result["programs"].values()
    )
    print(
        f"{totals['matched_functions']}/{totals['functions']} functions "
        f"matched ({percent(totals['matched_functions'], totals['functions'])}), "
        f"{percent(totals['matched_code'], totals['code'])} of code; "
        f"{function_units} units"
    )
    if markdown_changed:
        print(f"Wrote {MARKDOWN}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
