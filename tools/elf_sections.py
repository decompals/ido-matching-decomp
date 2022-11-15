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
import typing


@dataclasses.dataclass
class ElfChunk:  # Contiguous lump of elf file, e.g. section or header table
    name: str
    offset: int
    size: int
    index: int | None = None
    alignment: int = 4  # assume word by default
    type: str = ""
    hash: str = ""


def align(number: int, multiple: int) -> int:
    if multiple != 0:
        number += (-number) % multiple
    return number


def check_zero_bytes(file, start, end) -> int:
    file.seek(start, os.SEEK_SET)
    b = file.read(end - start)
    found_count = 0
    found_list = []
    for i, byte in enumerate(b):
        if byte != 0:
            found_count += 1
            if found_count >= 5:
                if found_count == 5:
                    found_list.append(f"...")
                continue
            found_list.append(f"{start + i:06X}")

    if found_count > 0:
        print(f"Found {found_count} nonzero bytes: ", end="")
    print(", ".join(found_list))
    return found_count


def get_elf_chunks(file) -> typing.List[ElfChunk]:
    elf_file = elftools.elf.elffile.ELFFile(file)
    header = elf_file.header

    chunks = []

    # ELF header
    file.seek(0, os.SEEK_SET)
    b = file.read(0x34)
    hash = hashlib.sha256(b).hexdigest()[:10]
    chunks.append(
        ElfChunk(offset=0, size=header["e_ehsize"], name="[ELF header]", hash=hash)
    )

    # Program headers
    offset = elf_file.header["e_phoff"]
    size = elf_file.header["e_phentsize"] * elf_file.header["e_phnum"]
    file.seek(offset, os.SEEK_SET)
    b = file.read(size)
    hash = hashlib.sha256(b).hexdigest()[:10]
    chunks.append(
        ElfChunk(offset=offset, size=size, name="[Program headers]", hash=hash)
    )

    # Section headers
    offset = elf_file.header["e_shoff"]
    size = elf_file.header["e_shentsize"] * elf_file.header["e_shnum"]
    file.seek(offset, os.SEEK_SET)
    b = file.read(size)
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
    return chunks


def print_chunk_ranges(file, chunks: typing.List[ElfChunk]):
    print("Idx Offset_Range  (Size, Align) Hash        Name")
    prev_end = 0
    for chunk in chunks:
        if chunk.type != "SHT_NOBITS":
            if align(prev_end, chunk.alignment) < chunk.offset:  # padding
                print(
                    f"    {prev_end:06X}-{chunk.offset:06X} ({chunk.offset - prev_end:06X})  ",
                    end="",
                )
                check_zero_bytes(file, prev_end, chunk.offset)
            prev_end = align(chunk.offset + chunk.size, chunk.alignment)

            print(
                f"{chunk.index or '':3} {chunk.offset:06X}-{chunk.offset + chunk.size:06X} ({chunk.size:06X}, {chunk.alignment:2X})  {chunk.hash or 10 * ' '}  {chunk.name}"
            )
        else:
            print(
                f"{chunk.index or '':3} {chunk.offset:06X}-{chunk.offset:06X} ({chunk.size:06X}, {chunk.alignment:2X})  {chunk.hash or 10 * ' '}  {chunk.name}"
            )

    file.seek(0, os.SEEK_END)
    file_size = file.tell()
    if align(prev_end, 4) < file_size:  # padding
        print(
            f"    {prev_end:06X}-{file_size:06X} ({file_size - prev_end:06X})  ",
            end="",
        )
        check_zero_bytes(file, prev_end, file_size)


def main() -> None:
    if len(sys.argv) < 2:
        print(
            f"""Usage: {sys.argv[0]} ELF_FILE\n\
Prints section/header ranges, sizes and hashes for a given ELF file."""
        )
        exit(1)

    file = sys.argv[1]

    with open(file, "rb") as f:
        chunks = get_elf_chunks(f)
        print_chunk_ranges(f, chunks)


if __name__ == "__main__":
    main()
