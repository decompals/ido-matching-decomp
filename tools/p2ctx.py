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
    "include/indy",
    "src",
]

DEFINES = [
    # cfe built-in defines
    "-D_MIPS_FPSET=16",
    "-D_MIPS_ISA=2",
    "-D_ABIO32=1 ",
    "-D_MIPS_SIM=_ABIO32",
    "-D_MIPS_SZINT=32 ",
    "-D_MIPS_SZLONG=32 ",
    "-D_MIPS_SZPTR=32 ",
    "-DLANGUAGE_PASCAL ",
    "-D_LANGUAGE_PASCAL " "-Q ",
    "-D__INLINE_INTRINSICS ",
    "-Dsgi",
    "-D__sgi ",
    "-Dunix ",
    "-Dmips ",
    "-Dhost_mips ",
    "-D__unix ",
    "-D__host_mips ",
    "-D_SVR4_SOURCE ",
    "-D_MODERN_C ",
    "-D_SGI_SOURCE ",
    "-D_PIC ",
    "-D__DSO__ ",
    "-DSYSTYPE_SVR4 ",
    "-D_SYSTYPE_SVR4 ",
    "-D_LONGLONG ",
    "-D__mips=2 ",
    "-D_MIPSEB",
    "-DMIPSEB ",
    "-D__STDC__=1 ",
    "-DIDO_71 ",
    # m2c tweaks
    # "PERMUTER=1"
    ## This block is required to avoid the vararg shitshow
    # "va_arg(...)=0",
    # "__VARARGS_H__",
    # "__STDARG_H__",
    # "va_dcl=long va_alist;",
    # "va_list=char *"
]

IDO_RECOMP_PATH = "tools/ido_recomp/7.1/"


def import_c_file(in_file: Path) -> str:
    in_file = Path(os.path.relpath(in_file, root_dir))

    # Yes, we will pre process our old pascal code using cfe

    cfe = IDO_RECOMP_PATH + "cfe"
    cfe_command = [
        str(cfe),
        *DEFINES,
        str(in_file),
        "-E",
        "-DLANGUAGE_PASCAL",
        "-D_LANGUAGE_PASCAL",
        "-Q",
        "-D__unix",
        "-D__host_mips",
        "-D_PIC",
        "-D__DSO__",
    ]
    cfe_command += ["-I" + i for i in INCLUDES]
    try:
        return subprocess.check_output(cfe_command, cwd=root_dir, encoding="utf-8")
    except subprocess.CalledProcessError:
        print(
            "Failed to preprocess input file, when running command:\n",
            cfe_command,
            file=sys.stderr,
        )
        sys.exit(1)


def postProcessOutput(output: str) -> str:
    return output.replace("#ident ", "// #ident ")


def main():
    parser = argparse.ArgumentParser(
        usage="./m2ctx.py path/to/file.p",
        description="Creates a ctx.p file for m2c. " "Output will be saved as ctx.p",
    )
    parser.add_argument("filepath", help="path of SGI Pascal file to be processed")
    args = parser.parse_args()

    c_file_path = Path(args.filepath)
    print(f"Using file: {c_file_path}")

    output = import_c_file(c_file_path)
    #output = postProcessOutput(output)

    outputPath = root_dir / "ctx.p"
    with outputPath.open("w", encoding="UTF-8") as f:
        f.write(output)


if __name__ == "__main__":
    main()
