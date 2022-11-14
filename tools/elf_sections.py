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

def align(number, multiple):
    if multiple != 0:
        number += (-number) % multiple
    return number

def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} ELF_FILE")
        exit(1)

    file = sys.argv[1]

    with open(file, "rb") as f:
        elf_file = elftools.elf.elffile.ELFFile(f)
        f.seek(0, os.SEEK_END)
        file_size = f.tell()

        prev_end = 0x34
        print("Idx Offset_Range  (Size, Align) Name")
        for i, sec in enumerate(elf_file.iter_sections()):
            offset = sec['sh_offset']
            size = sec['sh_size']
            if size == 0:
                continue
            alignment = sec['sh_addralign']
            if sec['sh_type'] != 'SHT_NOBITS' and align(prev_end, alignment) < offset:
                print(f"    {prev_end:06X}-{offset:06X} ({offset - prev_end:06X})")
            print(f"{i:3} {offset:06X}-{offset + size:06X} ({size:06X}, {alignment:2X}) {sec.name}")
            if sec['sh_type'] != 'SHT_NOBITS':
                prev_end = align(offset + size, alignment)

        if prev_end != file_size:
            print(f"      {prev_end:06X}-{file_size:06X} ({file_size - prev_end})")




if __name__ == "__main__":
    main()
