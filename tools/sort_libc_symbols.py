import sys

in_ext = False
lines = []

for line in open(sys.argv[1]).read().splitlines():
    if not in_ext:
        if "__us_rsthread_stdio" in line:
            in_ext = True
    if in_ext:
        if "PRC" in line:
            break
        line = line[22:]
        lines.append(line)
lines.sort()
for line in lines:
    print(line)
