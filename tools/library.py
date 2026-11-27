"""Library ownership for code statically linked into the target programs.

The IDO binaries embed ``libu``, ``libp``, ``libmld``, ``libelf``, ``libc`` and
friends.  Counting those functions as program code makes a program look
unstarted, so membership is encoded directly in the split CSVs: a row named
``library/member`` is library code, a plain row is program code.  There is no
separate catalog; the split names are the source of truth.

This module turns those names back into address ranges and finds the source and
base object for a member, e.g. ``libu/uini`` in
``symbols/7.1/ugen.splits.csv`` -> ``src/libu/uini.c`` and
``build/src/7.1/libu/uini.o``.  A split ends where the next row starts, because
object section sizes include trailing padding that would otherwise swallow the
next member.  Data-only members such as ``libp/data`` have ``.data``/``.rodata``
rows but no ``.text`` row.

``progress.py`` uses the ranges to score library copies separately from the
program that embeds them; ``gen_objdiff.py`` uses the paths to emit library
units.  Only libu/libp/libmld have sources and base objects today; the rest are
counted as unmatched.
"""

from __future__ import annotations

import re
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
VERSIONS = ("5.3", "7.1")

SOURCE_EXTS = (".c", ".p")
DATA_SECTIONS = (".data", ".rodata")
TEXT_SECTION = ".text"
LAYOUT_SECTIONS = (TEXT_SECTION, *DATA_SECTIONS)

_SPLIT_SUFFIX = re.compile(r"[A-Za-z0-9]+_([0-9A-Fa-f]{6})")


@dataclass(frozen=True)
class LibraryRange:
    binary: str
    start: int
    end: int
    library: str
    module: str

    @property
    def category(self) -> tuple[str, str]:
        return (self.library, self.module)


def parse_address(text: str) -> int:
    text = text.strip()
    if text.lower().startswith("0x"):
        return int(text, 16)
    return int(text, 16)


def parse_category(text: str) -> tuple[str, str] | None:
    text = text.strip()
    if not text:
        return None
    if "/" in text:
        library, module = text.split("/", 1)
    else:
        library = module = text
    library = library.strip()
    module = module.strip()
    if not library:
        return None
    return (library, module or library)


class LibraryRanges:
    def __init__(self, version: str, root: Path = ROOT) -> None:
        self.version = version
        self.root = root
        self.ranges: list[LibraryRange] = []
        self._load()

    def _load(self) -> None:
        for (program, _section, name), (start, end) in split_intervals(
            self.version, self.root
        ).items():
            if "/" not in name:
                continue
            category = parse_category(name)
            if category is None:
                continue
            self.ranges.append(
                LibraryRange(program, start, end, category[0], category[1])
            )
        self.ranges.sort(key=lambda item: (item.binary, item.start, item.end))

    def find(self, binary: str, address: int) -> LibraryRange | None:
        for item in self.ranges:
            if item.binary != binary:
                continue
            if item.start <= address < item.end:
                return item
        return None

    def find_section(
        self, binary: str, start: int, end: int
    ) -> LibraryRange | None:
        for item in self.ranges:
            if item.binary != binary:
                continue
            if item.start == start and item.end == end:
                return item
        return None

    def categories(self) -> set[tuple[str, str]]:
        return {item.category for item in self.ranges}


def split_intervals(
    version: str, root: Path = ROOT
) -> dict[tuple[str, str, str], tuple[int, int]]:
    """Map ``(program, section, split name)`` to its split address interval.

    The end of a split is the start of the next row in the same splits file.
    This follows the actual split layout instead of an object section size,
    which can include trailing alignment padding and overlap the next split.
    """

    intervals: dict[tuple[str, str, str], tuple[int, int]] = {}
    symbols = root / "symbols" / version
    if not symbols.is_dir():
        return intervals

    for path in sorted(symbols.glob("*.splits.csv")):
        program = path.name[: -len(".splits.csv")]
        section: str | None = None
        rows: list[tuple[str, str, int]] = []
        for raw_line in path.read_text(encoding="utf-8").splitlines():
            line = raw_line.split("#", 1)[0].strip()
            if not line:
                continue
            parts = [part.strip() for part in line.split(",")]
            if len(parts) >= 3 and parts[1] == "vram":
                section = parts[2]
                continue
            if section is None or len(parts) < 3:
                continue
            try:
                vram = int(parts[1], 16)
            except ValueError:
                continue
            rows.append((section, parts[2], vram))
        for index, (row_section, name, start) in enumerate(rows):
            if row_section not in LAYOUT_SECTIONS:
                continue
            end = rows[index + 1][2] if index + 1 < len(rows) else None
            if end is None or end <= start:
                continue
            intervals[(program, row_section, name)] = (start, end)
    return intervals


def section_starts(
    version: str, root: Path = ROOT
) -> dict[tuple[str, str, str], int]:
    return {
        key: interval[0]
        for key, interval in split_intervals(version, root).items()
    }


def section_start(
    starts: dict[tuple[str, str, str], int],
    program: str,
    rel: str,
    section: str,
) -> int | None:
    start = starts.get((program, section, rel))
    if start is not None:
        return start
    if section != TEXT_SECTION:
        return None
    match = _SPLIT_SUFFIX.fullmatch(Path(rel).name)
    if match is None:
        return None
    return 0x400000 + int(match.group(1), 16)


def section_intervals(
    starts: dict[tuple[str, str, str], int],
    program: str,
    rel: str,
    sections: dict[str, dict],
    split_ranges: dict[tuple[str, str, str], tuple[int, int]] | None = None,
) -> dict[str, tuple[int, int]]:
    intervals: dict[str, tuple[int, int]] = {}
    for section, value in sections.items():
        size = int(value.get("size", 0))
        if section not in LAYOUT_SECTIONS or size <= 0:
            continue
        if split_ranges is not None:
            split = split_ranges.get((program, section, rel))
            if split is not None:
                intervals[section] = split
                continue
        start = section_start(starts, program, rel, section)
        if start is None:
            continue
        intervals[section] = (start, start + size)
    return intervals


def function_address(
    starts: dict[tuple[str, str, str], int],
    program: str,
    rel: str,
    section: str,
    value: int,
) -> int | None:
    start = section_start(starts, program, rel, section)
    if start is None:
        return None
    return start + value


def library_base_path(
    version: str, library: str, module: str, root: Path = ROOT
) -> Path | None:
    path = root / "build" / "src" / version / library / f"{module}.o"
    return path if path.is_file() else None


def library_source_path(
    version: str, library: str, module: str, root: Path = ROOT
) -> Path | None:
    for ext in SOURCE_EXTS:
        path = root / "src" / library / f"{module}{ext}"
        if path.is_file():
            return path
    return None


def library_category_id(version: str, library: str) -> str:
    return f"{version}/{library}"


def library_category_name(version: str, library: str) -> str:
    return f"{version} / {library} (library)"
