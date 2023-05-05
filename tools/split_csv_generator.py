#!/usr/bin/env python3

import argparse
from pathlib import Path
import spimdisasm


def main():
    parser = argparse.ArgumentParser(description="")
    parser.add_argument("elf_program", help="")

    args = parser.parse_args()

    elfPath = Path(args.elf_program)
    programName = elfPath.name

    elfBytes = spimdisasm.common.Utils.readFileAsBytearray(elfPath)
    elfFile = spimdisasm.elf32.Elf32File(elfBytes)

    for header in elfFile.sectionHeaders:
        sectionType = spimdisasm.elf32.Elf32SectionHeaderType.fromValue(header.type)
        sectionName = elfFile.shstrtab[header.name]

        if sectionType == spimdisasm.elf32.Elf32SectionHeaderType.PROGBITS:
            if sectionName in {".text", ".data", ".rodata"}:
                print(f"offset,vram,{sectionName}")
                print(f"{header.offset:06X},{header.addr:08X},{programName}")
            else:
                print(f"offset,vram,.dummy")
                print(f"{header.offset:06X},{header.addr:08X},{sectionName[1:]}")
            print()

        elif sectionType == spimdisasm.elf32.Elf32SectionHeaderType.NOBITS:

            print(f"offset,vram,{sectionName}")
            print(f"{header.offset:06X},{header.addr:08X},{programName}")
            print()

            offsetEnd = header.offset + header.size
            addrEnd = header.addr + header.size
            print(f"{offsetEnd:06X},{addrEnd:08X},.end")


if __name__ == "__main__":
    main()
