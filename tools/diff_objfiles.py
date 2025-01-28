#! /usr/bin/env python3

from pathlib import Path
import subprocess
import glob
import itertools

def shell_exec(command):
    return subprocess.run(command.split(), stdout=subprocess.PIPE).stdout.decode('utf-8')

def main():
    programs = ("7.1/cfe", "7.1/cc",)
    objfiles = [f.relative_to('build/src') for p in programs for f in (Path('build/src').glob(f'{p}/*.o'))]
    sections = (".text", ".data", ".rodata")

    for name in objfiles:
        # object file names
        objfile_c = f"build/src/{name}"
        objfile_asm_text = f"build/asm/{name}"

        # object file sections
        readelf_c = shell_exec(f"readelf -S {objfile_c}")
        readelf_asm = shell_exec(f"readelf -S {objfile_asm_text}")

        #get sections content
        content_c = {}
        content_asm = {}
        for section in sections:
            for line in readelf_c.splitlines():
                if " " + section in line:
                    splitted_line = line[line.find(section):].split()
                    offset = int(splitted_line[3], 16)
                    size = int(splitted_line[4], 16)
                    content_c[section] = Path(objfile_c).read_bytes()[offset: offset + size]

            for line in readelf_asm.splitlines():
                if " " + section in line:
                    splitted_line = line[line.find(section):].split()
                    offset = int(splitted_line[3], 16)
                    size = int(splitted_line[4], 16)
                    content_asm[section] = Path(objfile_asm_text).read_bytes()[offset: offset + size]

            if content_c[section] == content_asm[section]:
                print(f"[OK] {name} {section}")
            else:
                print(f"[--] {name} {section}")
                Path(f"build/src/{name}{section}.c.bin").write_bytes(content_c[section])
                Path(f"build/src/{name}{section}.asm.bin").write_bytes(content_asm[section])



if __name__ == "__main__":
    main()