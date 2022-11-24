#! /usr/bin/env python3

import argparse
import csv
import dataclasses
import os
import sys
import enum


class SymCat(enum.Enum):
    Function = 1
    Data = 2
    Bss = 4
    String = 5
    Special = 6


@dataclasses.dataclass
class Sym:
    name: str
    category: SymCat
    vram: int
    vrom: int
    got: int | None
    dynsym: int | None
    dynstr: int | None
    size: int


@dataclasses.dataclass
class StrSym(Sym):
    contents: str


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
                    symbols[name] = Sym(
                        row["getName"],
                        SymCat.Function,
                        int(row["address"], 0),
                        int(row["getVrom"], 0),
                        int(row["gotIndex"], 0) if row["gotIndex"] != "None" else None,
                        int(row["dynsymIndex"], 0)
                        if row["dynsymIndex"] != "None"
                        else None,
                        int(row["dynstrIndex"], 0)
                        if row["dynstrIndex"] != "None"
                        else None,
                        int(row["getSize"], 0),
                    )
                elif name.startswith("STR_") or name == "__Release_ID":
                    # hack, could do with a way to check for strings
                    symbols[name] = StrSym(
                        row["getName"],
                        SymCat.String,
                        int(row["address"], 0),
                        int(row["getVrom"], 0),
                        int(row["gotIndex"], 0) if row["gotIndex"] != "None" else None,
                        int(row["dynsymIndex"], 0)
                        if row["dynsymIndex"] != "None"
                        else None,
                        int(row["dynstrIndex"], 0)
                        if row["dynstrIndex"] != "None"
                        else None,
                        int(row["getSize"], 0),
                        get_str_contents(os.path.join(asm, name + ".s")),
                    )
            elif row["sectionType"] == ".data":
                symbols[name] = Sym(
                    row["getName"],
                    SymCat.Data,
                    int(row["address"], 0),
                    int(row["getVrom"], 0),
                    int(row["gotIndex"], 0) if row["gotIndex"] != "None" else None,
                    int(row["dynsymIndex"], 0)
                    if row["dynsymIndex"] != "None"
                    else None,
                    int(row["dynstrIndex"], 0)
                    if row["dynstrIndex"] != "None"
                    else None,
                    int(row["getSize"], 0),
                )
            elif row["sectionType"] == ".bss":
                symbols[name] = Sym(
                    row["getName"],
                    SymCat.Bss,
                    int(row["address"], 0),
                    int(row["getVrom"], 0),
                    int(row["gotIndex"], 0) if row["gotIndex"] != "None" else None,
                    int(row["dynsymIndex"], 0)
                    if row["dynsymIndex"] != "None"
                    else None,
                    int(row["dynstrIndex"], 0)
                    if row["dynstrIndex"] != "None"
                    else None,
                    int(row["getSize"], 0),
                )


    return symbols


# SHORT_COMMENT = " // Address: 0x{vram:08X}, GOT: {gotIndex}"
# SHORT_COMMENT = "/* Address: 0x{vram:08X}, GOT: {gotIndex:4} */ "
SHORT_COMMENT = "/* 0x{vrom:06X} 0x{vram:08X} {dynsym:>4} {dynstr:>4} */ "

DOCUMENTATION_COMMENT = """\
/**
 * Name: {name}
 * VROM: 0x{vrom:06X}
 * Address: 0x{vram:08X}
 * dynsym index: {dynsym}
 * dynstr index: {dynstr}
 * Size: 0x{size:X}
 */\
"""

GLOBAL_ASM = '#pragma GLOBAL_ASM("{}.s")'

STRING = """\
static const char {}[] = "{}";\
"""


def write_file(out, asm, symbols, migrated):
    with open(out, "w") as f:
        f.write("typedef void* UNK_TYPE;")
        f.write("\n")
        f.write("\n")

        # bss
        last_notgot = None
        last_notgotstr = None
        last_got = None
        last_gotstr = None
        f.write("/* VROM     Address   dynsym dynstr */\n")
        for sym in symbols.values():
            if sym.category == SymCat.Bss:
                f.write(
                    SHORT_COMMENT.format(
                        vrom=sym.vrom,
                        vram=sym.vram,
                        dynsym=str(sym.dynsym),
                        dynstr=str(sym.dynstr),
                    )
                )
                if sym.name.startswith("B_"):
                    f.write("static ")
                f.write("char {}[0x{:X}];".format(sym.name, sym.size))
                if sym.dynsym:
                    if sym.got:
                        if last_got and sym.dynsym < last_got:
                            f.write(" // dynsym/got reorder?")
                        if last_gotstr and sym.dynstr < last_gotstr:
                            f.write(" // dynstr/got reorder?")
                        last_got = sym.dynsym
                        last_gotstr = sym.dynstr
                    else:
                        if last_notgot and sym.dynsym < last_notgot:
                            f.write(" // dynsym reorder?")
                        if last_notgotstr and sym.dynstr < last_notgotstr:
                            f.write(" // dynstr reorder?")
                        last_notgot = sym.dynsym
                        last_notgotstr = sym.dynstr
                f.write("\n")

        f.write("\n")

        # data
        last_notgot = None
        last_got = None
        last_gotstr = None
        for sym in symbols.values():
            # print(type(sym))
            if sym.category == SymCat.Data:
                f.write(
                    SHORT_COMMENT.format(
                        vrom=sym.vrom,
                        vram=sym.vram,
                        dynsym=str(sym.dynsym),
                        dynstr=str(sym.dynstr),
                    )
                )
                if sym.name.startswith("D_"):
                    f.write("/* static */ ")

                f.write("extern UNK_TYPE {};".format(sym.name, sym.size))
                if sym.dynsym:
                    if last_got and sym.dynsym < last_got:
                        f.write(" // dynsym reorder?")
                    if last_gotstr and sym.dynstr < last_gotstr:
                        f.write(" // dynstr reorder?")
                    last_got = sym.dynsym
                    last_gotstr = sym.dynstr
                f.write("\n")

        f.write("\n")

        # functions and strings
        last_notgot = None
        last_got = None
        prev_was_function = False
        for name in migrated:
            sym = symbols[name]
            # print(type(sym))
            if sym.category == SymCat.Function:
                f.write("\n")
                f.write(
                    DOCUMENTATION_COMMENT.format(
                        name=sym.name,
                        vrom=sym.vrom,
                        vram=sym.vram,
                        dynsym=sym.dynsym,
                        dynstr=sym.dynstr,
                        size=sym.size,
                    )
                )
                f.write("\n")

                if name.startswith("func_"):
                    f.write(f"// /* static */ int {sym.name}();")
                else:
                    f.write(f"// int {sym.name}();")

                if sym.dynsym:
                    if last_got and sym.dynsym != last_got + 1:
                        f.write(" // dynsym reorder?")
                    last_got = sym.dynsym
                f.write("\n")
                f.write(GLOBAL_ASM.format(os.path.join(asm, sym.name)))
                f.write("\n")

                prev_was_function = True
            elif sym.category == SymCat.String:
                if prev_was_function:
                    f.write("\n")
                f.write(STRING.format(name, sym.contents))
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

    # for sym, entry in symbols.items():
    #     print(entry)

    write_file(args.output, args.asm, symbols, migrated)


if __name__ == "__main__":
    main()
