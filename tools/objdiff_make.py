#!/usr/bin/env python3
"""Build one object for objdiff through the project Makefile.

objdiff runs its configured ``custom_make`` with a single object path relative
to the project root. The Makefile needs ``VERSION`` to select the IDO
toolchain, so derive it from ``build/{src,asm}/<version>/...`` and pass it
explicitly. This keeps one objdiff.json usable for both 5.3 and 7.1.
"""

from __future__ import annotations

import json
import os
import re
import subprocess
import sys
from pathlib import Path

from mdebug import repair_mdebug
from symbolize_base import symbolize_base

ROOT = Path(__file__).resolve().parent.parent
VERSION_RE = re.compile(r"(?:^|/)build/(?:src|asm)/(5\.3|7\.1)/")


def target_for_base(base: Path, allow_library: bool = False) -> Path | None:
    try:
        rel = base.relative_to(ROOT).as_posix()
    except ValueError:
        return None

    config_path = ROOT / "objdiff.json"
    if config_path.is_file():
        try:
            config = json.loads(config_path.read_text(encoding="utf-8"))
        except (OSError, json.JSONDecodeError):
            config = {}
        for unit in config.get("units", []):
            if unit.get("base_path") != rel:
                continue
            if unit.get("metadata", {}).get("library") and not allow_library:
                continue
            target = ROOT / unit.get("target_path", "")
            if target.is_file():
                return target

    parts = Path(rel).parts
    if len(parts) >= 4 and parts[0] == "build" and parts[1] == "src":
        target = ROOT / "build" / "asm" / parts[2] / Path(*parts[3:])
        if target.is_file():
            return target
    return None


def symbolize_built_base(path: str) -> None:
    base = Path(path)
    if not base.is_absolute():
        base = ROOT / base
    if not base.is_file():
        return

    target = target_for_base(base)
    if target is not None:
        try:
            symbolize_base(target, base)
        except Exception as exc:  # keep objdiff usable if symbol mirroring fails
            print(f"warning: could not symbolize {base}: {exc}", file=sys.stderr)
        return

    library_target = target_for_base(base, allow_library=True)
    if library_target is not None:
        try:
            repair_mdebug(base, library_target)
        except Exception as exc:
            print(f"warning: could not repair {base}: {exc}", file=sys.stderr)


def main(argv: list[str]) -> int:
    if len(argv) != 1:
        print("usage: objdiff_make.py <object-path>", file=sys.stderr)
        return 2

    target = argv[0]
    match = VERSION_RE.search(target)
    command = [os.environ.get("MAKE", "make")]
    if match is not None:
        command.append(f"VERSION={match.group(1)}")
    command.append(target)
    result = subprocess.call(command, cwd=ROOT)
    if result == 0:
        symbolize_built_base(target)
    return result


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
