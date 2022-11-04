#! /usr/bin/env python3

import argparse
import csv
import dataclasses
import os
import sys


@dataclasses.dataclass
class Fn:
    name: str
    vram: int
    vrom: int
    size: int


def process_migrated(migrated_file):
    with open(migrated_file) as m:
        return [line.strip() for line in m.readlines()]


def get_str_contents(file):
    with open(file) as f:
        return f.read().split('"')[1]


def process_csv(csv_file, asm, migrated):
    symbols = {}
    with open(csv_file) as c:
        reader = csv.DictReader(c)
        for row in reader:
            name = row["getName"]
            if name in migrated:
                if row["getType"] == "@function":
                    symbols[name] = Fn(
                        row["getName"],
                        int(row["address"], 0),
                        int(row["getVrom"], 0),
                        int(row["getSize"], 0),
                    )
                elif name.startswith("STR_"):
                    symbols[name] = get_str_contents(os.path.join(asm, name + ".s"))

    return symbols


DOCUMENTATION_COMMENT = """\
/**
 * {name}
 * Address: 0x{vram:08X}
 * VROM: 0x{vrom:06X}
 * Size: 0x{size:X}
 */\
"""
GLOBAL_ASM = '#pragma GLOBAL_ASM("{}.s")'

STRING = """\
static const char {}[] = "{}";\
"""


def write_file(out, asm, symbols, migrated):

    with open(out, "w") as f:
        prev_was_function = False
        for name in migrated:
            sym = symbols[name]
            if type(sym) == Fn:
                f.write("\n")
                f.write(
                    DOCUMENTATION_COMMENT.format(
                        name=sym.name, vram=sym.vram, vrom=sym.vrom, size=sym.size
                    )
                )
                f.write("\n")

                if name.startswith("func_"):
                    f.write(f"// /* static */ int {sym.name}();")
                else:
                    f.write(f"// int {sym.name}();")
                f.write("\n")

                f.write(GLOBAL_ASM.format(os.path.join(asm, sym.name)))
                f.write("\n")

                prev_was_function = True
            elif type(sym) == str:
                if prev_was_function:
                    f.write("\n")
                f.write(STRING.format(name, sym))
                f.write("\n")
                prev_was_function = False
            else:
                print(
                    f"Not a recognised symbol type: {name}, {type(sym)}",
                    file=sys.stderr,
                )


def main():
    description = "Initialise a file with the appropriate function GLOBAL_ASM and address info given a csv"
    epilog = ""

    parser = argparse.ArgumentParser(
        description=description,
        epilog=epilog,
        formatter_class=argparse.RawTextHelpFormatter,
    )
    parser.add_argument("csv", help="csv file to read.")
    parser.add_argument("asm", help="Functions asm directory.")
    parser.add_argument("migrated", help="Migrated functions list.")
    parser.add_argument("output", help="File to write.")

    args = parser.parse_args()

    migrated = process_migrated(args.migrated)
    symbols = process_csv(args.csv, args.asm, migrated)

    write_file(args.output, args.asm, symbols, migrated)


if __name__ == "__main__":
    main()
