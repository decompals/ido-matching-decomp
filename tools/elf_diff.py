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
from itertools import zip_longest


def grouper(iterable, n, fillvalue=None):
    args = [iter(iterable)] * n
    return zip_longest(*args, fillvalue=fillvalue)


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


def get_bytes(file, start: int, size: int) -> bytearray:
    file.seek(start, os.SEEK_SET)
    return file.read(size)


def get_words(b: bytes):
    tuples = struct.iter_unpack(">I", b)
    return [t[0] for t in tuples]


def main() -> None:
    if len(sys.argv) < 3:
        print(
            f"""Usage: {sys.argv[0]} TARGET CURRENT
Print ELF file diffs"""
        )
        exit(1)

    with open(sys.argv[1], "rb") as target, open(sys.argv[2], "rb") as current:
        t_chunks = get_elf_chunks(target)
        c_chunks = get_elf_chunks(current)

        # Crude loop, only examine global section properties
        for t_chunk, c_chunk in zip(t_chunks, c_chunks):
            if c_chunk.name != t_chunk.name:
                print(f"Chunk {t_chunk.name}/{c_chunk.name} has differing name.")
            if c_chunk.size != t_chunk.size:
                print(
                    f"Chunk {t_chunk.name} has differing size: {t_chunk.size} / {c_chunk.size}."
                )

        # Precise loop, actually diff
        for t_chunk, c_chunk in zip(t_chunks, c_chunks):
            t_data = get_bytes(target, t_chunk.offset, align(t_chunk.size, 4))
            c_data = get_bytes(current, c_chunk.offset, align(c_chunk.size, 4))

            t_words = get_words(t_data)
            c_words = get_words(c_data)

            print(t_chunk.name)
            differing_words = 0

            for i, (t_word, c_word) in enumerate(zip(t_words, c_words)):
                if t_word == c_word:
                    continue
                differing_words += 1
                if differing_words > 12:
                    if differing_words == 13:
                        print("     ...")
                    continue
                index = f"0x{i * 4:X}"
                print(
                    f"    + {index:>6}  Word diff: {t_word:08X} != {c_word:08X}"
                )

            if differing_words > 0:
                if differing_words > 1:
                    print(f"    {differing_words} words differ")
                else:
                    print(f"    {differing_words} word differs")
            else:
                print(f"    OK")
            print()

        # print_chunk_ranges(f, chunks)


if __name__ == "__main__":
    main()
