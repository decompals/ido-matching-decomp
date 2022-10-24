#!/usr/bin/env python3

from pathlib import Path

functionsPath = Path("asm/functions/cc")

strings = []
for p in functionsPath.glob("STR_*.s"):
    prefix, address = p.stem.split("_")
    strings.append((int(address, 16), prefix))
# for p in functionsPath.glob("RO_*.s"):
#     prefix, address = p.stem.split("_")
#     strings.append((int(address, 16), prefix))

strings.sort()
# print(strings)

for address, prefix in strings:
    print(f'#pragma GLOBAL_ASM("asm/functions/cc/{prefix}_{address:08X}.s")')
