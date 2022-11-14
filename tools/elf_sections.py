#! /usr/bin/env python3

import argparse
import csv
import dataclasses
import os
import sys
import struct
import enum
import hashlib
import elftools.elf.elffile
import elftools.elf.enums


@dataclasses.dataclass
class ElfChunk:  # Contiguous lump of elf file, e.g. section or header table
    name: str
    offset: int
    size: int
    index: int | None = None
    alignment: int = 4  # assume word by default
    type: str = ""
    hash: str = ""


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
        header = elf_file.header

        chunks = []

        # ELF header
        f.seek(0, os.SEEK_SET)
        b = f.read(0x34)
        hash = hashlib.sha256(b).hexdigest()[:10]
        chunks.append(
            ElfChunk(offset=0, size=header["e_ehsize"], name="[ELF header]", hash=hash)
        )

        # Program headers
        offset = elf_file.header["e_phoff"]
        size = elf_file.header["e_phentsize"] * elf_file.header["e_phnum"]
        f.seek(offset, os.SEEK_SET)
        b = f.read(size)
        hash = hashlib.sha256(b).hexdigest()[:10]
        chunks.append(
            ElfChunk(offset=offset, size=size, name="[Program headers]", hash=hash)
        )

        # Section headers
        offset = elf_file.header["e_shoff"]
        size = elf_file.header["e_shentsize"] * elf_file.header["e_shnum"]
        f.seek(offset, os.SEEK_SET)
        b = f.read(size)
        hash = hashlib.sha256(b).hexdigest()[:10]
        chunks.append(
            ElfChunk(offset=offset, size=size, name="[Section headers]", hash=hash)
        )

        # Sections
        for i, sec in enumerate(elf_file.iter_sections()):
            size = sec["sh_size"]
            if size == 0:
                continue
            name = sec.name
            offset = sec["sh_offset"]
            alignment = sec["sh_addralign"]

            hash = ""
            if sec["sh_type"] != "SHT_NOBITS":
                hash = hashlib.sha256(sec.data()).hexdigest()[:10]  # should be plenty
            chunks.append(
                ElfChunk(
                    name=name,
                    offset=offset,
                    size=size,
                    index=i,
                    alignment=alignment,
                    type=sec["sh_type"],
                    hash=hash,
                )
            )

        chunks.sort(key=lambda x: x.offset)

        print("Idx Offset_Range  (Size, Align) Hash        Name")
        prev_end = 0
        for chunk in chunks:
            if chunk.type != "SHT_NOBITS":
                if align(prev_end, chunk.alignment) < chunk.offset:  # padding
                    print(
                        f"    {prev_end:06X}-{chunk.offset:06X} ({chunk.offset - prev_end:06X})  ",
                        end="",
                    )
                    f.seek(prev_end, os.SEEK_SET)
                    b = f.read(chunk.offset - prev_end)
                    found_count = 0
                    found_list = []
                    for i, byte in enumerate(b):
                        if byte != 0:
                            found_count += 1
                            if found_count >= 5:
                                if found_count == 5:
                                    found_list.append(f"...")
                                continue
                            found_list.append(f"{prev_end + i:06X}")

                    if found_count > 0:
                        print(f"Found {found_count} nonzero bytes: ", end="")
                    print(", ".join(found_list))
                prev_end = align(chunk.offset + chunk.size, chunk.alignment)

            print(
                f"{chunk.index or '':3} {chunk.offset:06X}-{chunk.offset:06X} ({chunk.size:06X})  {chunk.hash or 10 * ' '}  {chunk.name}"
            )


if __name__ == "__main__":
    main()
