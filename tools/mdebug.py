#!/usr/bin/env python3
"""Recover IDO source names and line info for objdiff.

IDO keeps local procedure names, static data names and source lines only in
``.mdebug``; they never reach ``.symtab``.  Enabling ``-g``/``-g3`` is not an
option because it changes code generation and breaks matching, so objdiff has
to use the metadata that is already there.  Two IDO quirks block that:

- ``objcopy --add-symbol`` (used to mirror target symbols) moves ``.mdebug``
  but leaves the header offsets pointing at the old file positions;
- objdiff expects ``ST_END.value`` to be an absolute end address, while IDO
  stores the function size.

This module reads the names and repairs both issues in place.  The result is
that objdiff shows C/Pascal names and source lines on the base side instead of
only ``func_...`` / ``D_...`` labels; target assembly has no debug info, so
lines appear on the base side only.
"""

from __future__ import annotations

import struct
from dataclasses import dataclass, field
from pathlib import Path

from elftools.elf.elffile import ELFFile

HEADER_SIZE = 0x60
FDR_SIZE = 0x48
SYMR_SIZE = 0x0C

ST_GLOBAL = 1
ST_STATIC = 2
ST_PROC = 6
ST_END = 8
ST_CONST = 13
ST_STATICPROC = 14

SECTION_BY_SC = {
    2: ".data",
    3: ".bss",
    15: ".rodata",
}

OFFSET_FIELDS = (4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24)


@dataclass(frozen=True)
class SourceNames:
    procs: dict[int, str] = field(default_factory=dict)
    data: dict[str, dict[int, str]] = field(default_factory=dict)

    def name_for(self, section: str, value: int) -> str | None:
        if section == ".text":
            return self.procs.get(value)
        return self.data.get(section, {}).get(value)


def _u16(data: bytes | bytearray, offset: int) -> int:
    return struct.unpack_from(">H", data, offset)[0]


def _u32(data: bytes | bytearray, offset: int) -> int:
    return struct.unpack_from(">I", data, offset)[0]


def _header(data: bytes | bytearray) -> list[int] | None:
    if len(data) < HEADER_SIZE:
        return None
    return list(struct.unpack_from(">2H23I", data, 0))


def _normalize_header(data: bytearray) -> bool:
    values = _header(data)
    if values is None:
        return False
    if values[3] == 0 and values[10] >= HEADER_SIZE:
        old_base = values[10] - HEADER_SIZE
    elif values[4] >= HEADER_SIZE:
        old_base = values[4] - HEADER_SIZE
    else:
        return False
    if old_base == 0:
        return False
    changed = False
    for index in OFFSET_FIELDS:
        value = values[index]
        if value and value >= old_base:
            values[index] = value - old_base
            changed = True
    if changed:
        struct.pack_into(">2H23I", data, 0, *values)
    return changed


def _slice(data: bytes | bytearray, offset: int, size: int) -> bytes | bytearray | None:
    if offset < 0 or size < 0 or offset + size > len(data):
        return None
    return data[offset : offset + size]


def _symbol_name(strings: bytes | bytearray, file_base: int, string_offset: int) -> str | None:
    for offset in (string_offset, file_base + string_offset):
        if offset < 0 or offset >= len(strings):
            continue
        end = strings.find(b"\0", offset)
        if end < 0:
            continue
        try:
            return strings[offset:end].decode("utf-8")
        except UnicodeDecodeError:
            continue
    return None


def _symbols(data: bytearray, header: list[int]) -> list[tuple[int, int, int, int, int]]:
    table = _slice(data, header[10], header[9] * SYMR_SIZE)
    if table is None:
        return []
    symbols: list[tuple[int, int, int, int, int]] = []
    for index in range(header[9]):
        offset = index * SYMR_SIZE
        iss, value, bits = struct.unpack_from(">III", table, offset)
        st = (bits >> 26) & 0x3F
        sc = (bits >> 21) & 0x1F
        symbol_index = bits & 0xFFFFF
        symbols.append((iss, value, st, sc, symbol_index))
    return symbols


def read_source_names(path: Path) -> SourceNames:
    with path.open("rb") as f:
        elf = ELFFile(f)
        section = elf.get_section_by_name(".mdebug")
        if section is None:
            return SourceNames()
        data = bytearray(section.data())

    _normalize_header(data)
    header = _header(data)
    if header is None or header[4] == 0:
        return SourceNames()

    strings = _slice(data, header[16], header[15])
    fdrs = _slice(data, header[20], header[19] * FDR_SIZE)
    if strings is None or fdrs is None:
        return SourceNames()

    symbols = _symbols(data, header)
    procs: dict[int, str] = {}
    data_names: dict[str, dict[int, str]] = {}
    for fdr_index in range(header[19]):
        fdr_offset = fdr_index * FDR_SIZE
        file_base = _u32(fdrs, fdr_offset + 8)
        sym_base = _u32(fdrs, fdr_offset + 16)
        sym_count = _u32(fdrs, fdr_offset + 20)
        if sym_count == 0:
            continue
        for index in range(sym_base, sym_base + sym_count):
            if index >= len(symbols):
                break
            iss, value, st, sc, _symbol_index = symbols[index]
            name = _symbol_name(strings, file_base, iss)
            if name is None:
                continue
            if st in (ST_PROC, ST_STATICPROC):
                procs[value] = name
            elif st in (ST_GLOBAL, ST_STATIC, ST_CONST):
                section_name = SECTION_BY_SC.get(sc)
                if section_name is not None:
                    data_names.setdefault(section_name, {})[value] = name

    return SourceNames(procs=procs, data=data_names)


def target_text_sizes(path: Path) -> dict[int, int]:
    sizes: dict[int, int] = {}
    with path.open("rb") as f:
        elf = ELFFile(f)
        symtab = elf.get_section_by_name(".symtab")
        if symtab is None:
            return sizes
        for symbol in symtab.iter_symbols():
            name = symbol.name
            if not name or name.endswith(".NON_MATCHING"):
                continue
            if symbol["st_info"]["type"] not in ("STT_FUNC", "STT_NOTYPE"):
                continue
            section_index = symbol["st_shndx"]
            if not isinstance(section_index, int):
                continue
            if section_index <= 0 or section_index >= elf.num_sections():
                continue
            section = elf.get_section(section_index)
            if section is None or section.name != ".text":
                continue
            size = symbol["st_size"]
            if size > 0:
                sizes.setdefault(symbol["st_value"], size)
    return sizes


def _fix_end_values(data: bytearray, target_sizes: dict[int, int]) -> bool:
    header = _header(data)
    if header is None or header[4] == 0:
        return False
    symbols = _symbols(data, header)
    fdrs = _slice(data, header[20], header[19] * FDR_SIZE)
    if fdrs is None:
        return False

    changed = False
    for fdr_index in range(header[19]):
        fdr_offset = fdr_index * FDR_SIZE
        sym_base = _u32(fdrs, fdr_offset + 16)
        sym_count = _u32(fdrs, fdr_offset + 20)
        for index in range(sym_base, min(sym_base + sym_count, len(symbols))):
            _iss, value, st, _sc, symbol_index = symbols[index]
            if st != ST_END:
                continue
            start_index = sym_base + symbol_index
            if start_index >= len(symbols):
                continue
            _start_iss, start_value, start_st, _start_sc, _start_index = symbols[start_index]
            if start_st not in (ST_PROC, ST_STATICPROC):
                continue
            target_size = target_sizes.get(start_value)
            if target_size is not None:
                if value == start_value + target_size:
                    continue
                if value == target_size:
                    new_value = start_value + target_size
                elif value < start_value:
                    new_value = start_value + value
                else:
                    continue
            else:
                if value >= start_value:
                    continue
                new_value = start_value + value
            symbol_offset = header[10] + index * SYMR_SIZE + 4
            struct.pack_into(">I", data, symbol_offset, new_value)
            changed = True
    return changed


def repair_mdebug(path: Path, target: Path) -> None:
    if not path.is_file() or not target.is_file():
        return
    sizes = target_text_sizes(target)
    with path.open("r+b") as f:
        elf = ELFFile(f)
        section = elf.get_section_by_name(".mdebug")
        if section is None:
            return
        section_offset = section["sh_offset"]
        data = bytearray(section.data())
        changed = _normalize_header(data)
        changed = _fix_end_values(data, sizes) or changed
        if changed:
            f.seek(section_offset)
            f.write(data)
