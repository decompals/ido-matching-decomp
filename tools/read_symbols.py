#! /usr/bin/env python3

import argparse
import csv
import dataclasses
import os
import sys
import struct
import enum
import elftools.elf.elffile
import elftools.elf.enums
# import elftools.elf.dynamic
# import elftools.elf.sections

@dataclasses.dataclass
class DynSym:
    index: int
    name: str
    name_index: int
    type: str
    section: int | str
    value: int
    size: int
    got: int | None = None

def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} ELF_FILE")
        exit(1)

    file = sys.argv[1]

    with open(file, "rb") as f:
        elf_file = elftools.elf.elffile.ELFFile(f)
        endian_format = "<" if elf_file.little_endian else ">"

        dynamic_sec = elf_file.get_section_by_name(".dynamic")
        gotsym = int(dynamic_sec.get_table_offset("DT_MIPS_GOTSYM")[0])
        localgotno = int(dynamic_sec.get_table_offset("DT_MIPS_LOCAL_GOTNO")[0])

        dynsym_sec = elf_file.get_section_by_name(".dynsym")
        got_sec = elf_file.get_section_by_name(".got")

        symbols = []
        for i,sym in enumerate(dynsym_sec.iter_symbols()):
            dynsym = DynSym(i, sym.name, sym["st_name"], sym["st_info"]["type"], sym["st_shndx"], sym["st_value"], sym["st_size"])
            if i >= gotsym:
                dynsym.got = struct.unpack_from(endian_format + "I", got_sec.data()[4 * (localgotno + i - gotsym):])[0]
            symbols.append(dynsym)

        # symbols.sort(key=lambda sym: sym.value)
        prev_got_index = gotsym - 1
        prev_notgot_index = -1

        text_passed = False
        text_lines = []
        if len(sys.argv) > 2:
            text = sys.argv[2]
            with open(text) as t:
                text_lines = t.readlines()
            text_passed = True

        print("Index, Value,   Name,                               NameIdx, Size, Section, Type, GOT index")
        for sym in symbols:
            padded_name = sym.name + ","
            padded_name = f"{padded_name:35}"
            section = f"0x{sym.section:X}," if type(sym.section) == int else sym.section + ","
            got = f"{sym.got:08X}" if sym.got else ""
            print(f'{sym.index:4}, {sym.value:08X}, {padded_name} 0x{sym.name_index:X}, 0x{sym.size:X}, {section:8} {sym.type}', end="")
            
            if sym.index >= gotsym:
                print(f", {sym.index - gotsym}", end="")
                if text_passed:
                    for i, line in enumerate(text_lines):
                        if line.find(f"({sym.name})") >= 0:
                            print(f", {i:5}, {line.strip().split()[2]}", end="")
                            break
            else:
                print(", None", end="")


            # if sym.index >= gotsym:
            #     if sym.index != prev_got_index + 1:
            #         print(" # reordered!", end="")
            #     prev_got_index = sym.index
            # else:
            #     if sym.index != prev_notgot_index + 1:
            #         print(" # reordered!", end="")
            #     prev_notgot_index = sym.index
            print()


if __name__ == "__main__":
    main()
