import sys

in_bss = False

for line in open(sys.argv[1]).read().splitlines():
    parts = line.strip().split(",")
    if parts[0] != "symbol":
        continue
    if not in_bss:
        if parts[2] == "LD":
            in_bss = True
    if in_bss:
        if parts[-1] == "True":
            name = "<pad>"
        else:
            name = parts[3]
        print(name, parts[-2] if parts[-2] != "None" else "")
