#! /usr/bin/env python3
import re
import sys


def get_type(name: str, file):
    if file:
        with open(file) as f:
            lines = f.readlines()
            for i, line in enumerate(lines):
                if " " + name in line and " =" in line and not name + "_" in line:
                    return " // " + line.split("//")[0].strip() + f" // line {i}"
    return ""


# Data
def run(infile, search_file=""):
    with open(infile) as f:
        lines = f.readlines()
        name = ""
        static = False
        new_symbol = True
        for line in lines:
            if line.startswith("glabel"):
                name = line.split()[1]
                static = name.startswith("B_")
                new_symbol = True
                continue
            if line.startswith("/*"):
                if not new_symbol:
                    continue
                new_symbol = False
                splitline = line.strip().split()
                vrom = splitline[1]
                vram = splitline[2]
                static_str = "static " if static else ""
                print(f"/* {vrom} {vram} */ {static_str}{name}", end="")
                print(get_type(name, search_file))



# BSS version
# def run(infile, search_file=""):
#     with open(infile) as f:
#         lines = f.readlines()
#         name = ""
#         static = False
#         for line in lines:
#             if line.startswith("glabel"):
#                 name = line.split()[1]
#                 static = name.startswith("B_")
#                 continue
#             if line.find(".space") >= 0:
#                 splitline = line.strip().split()
#                 vrom = splitline[1]
#                 vram = splitline[2]
#                 size = splitline[-1]
#                 static_str = "static " if static else ""
#                 print(f"/* {vrom} {vram} */ {static_str}char {name}[{size}];", end="")
#                 print(get_type(name, search_file))
#                 continue


def main():
    infile = sys.argv[1]
    search_file = ""
    if len(sys.argv) > 2:
        search_file = sys.argv[2]
    # outfile = sys.argv[2]

    run(infile, search_file)


if __name__ == "__main__":
    main()
