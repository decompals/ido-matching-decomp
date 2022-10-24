#!/usr/bin/env python3

import argparse
import os
import subprocess
import sys
from pathlib import Path

script_dir = Path(__file__).parent
root_dir = script_dir / ".."
src_dir = root_dir / "src"

INCLUDES = [
    "include",
    "src",
]

DEFINES = [
    "_MIPS_FPSET=16",
    "_MIPS_ISA=2",
    "_ABIO32=1",
    "_MIPS_SIM=_ABIO32",
    "_MIPS_SZINT=32",
    "_MIPS_SZLONG=32",
    "_MIPS_SZPTR=32",
    "__EXTENSIONS__",
    "LANGUAGE_C",
    "_LANGUAGE_C",
    "__INLINE_INTRINSICS",
    "sgi",
    "__sgi",
    "unix",
    "mips",
    "host_mips",
    "__unix",
    "__host_mips",
    "_SVR4_SOURCE",
    "_MODERN_C",
    "_SGI_SOURCE",
    "__DSO__",
    "SYSTYPE_SVR4",
    "_SYSTYPE_SVR4",
    "_LONGLONG",
    "__mips=2",
    "_MIPSEB",
    "MIPSEB",
    # "__STDC__=1", # gcc complains about it being redefined
    "_CFE",
    "_POSIX_SOURCE",
]

def import_c_file(in_file: Path) -> str:
    in_file = Path(os.path.relpath(in_file, root_dir))

    cpp_command = [
        "gcc", "-E", "-P",
        "-Iinclude", "-Iassets", "-Isrc",
    ]
    cpp_command += ["-I" + i for i in INCLUDES]
    cpp_command.append("-undef")
    cpp_command += ["-D" + d for d in DEFINES]
    cpp_command.append(str(in_file))
    try:
        return subprocess.check_output(cpp_command, cwd=root_dir, encoding="utf-8")
    except subprocess.CalledProcessError:
        print(
            "Failed to preprocess input file, when running command:\n", cpp_command,
            file=sys.stderr,
        )
        sys.exit(1)


def main():
    parser = argparse.ArgumentParser(usage="./m2ctx.py path/to/file.c",
                                     description="Creates a ctx.c file for m2c. "
                                     "Output will be saved as ctx.c")
    parser.add_argument('filepath', help="path of c file to be processed")
    args = parser.parse_args()

    c_file_path = Path(args.filepath)
    print(f"Using file: {c_file_path}")

    output = import_c_file(c_file_path)

    outputPath = root_dir / "ctx.c"
    with outputPath.open("w", encoding="UTF-8") as f:
        f.write(output)


if __name__ == "__main__":
    main()
