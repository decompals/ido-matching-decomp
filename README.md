# IDO matching decomp

Matching decompilation of the IRIX Development Option compiler.

The intention is to eventually match all the programs required to build C files to an unlinked binary, namely

- `cc` - compiler driver, runs everything else as appropriate
- `cfe` - "C frontend", preprocessor and runs the optimisation and code generation steps
- `uopt` - optimiser used by `-O2`
- `ugen` - code generator used for lower optimisation
- `as1` - assembler for compiler-generated assembly

since this process is the most useful for other decompilation projects.

Lower priority but also of interest:

- `as0` - assembler for handwritten assembly
- `uld` (ucode linker) and `umerge` (procedure merger) for `-O3`
- `ld` (linker) for outputting linked object files
- `upas` frontend for Pascal, possibly of interest since much of IDO is Pascal

Of these,

- `cc`, `cfe`, `as0` are written in C, `cfe` also contains Yacc components.
- `uopt`, `ugen`, `as1`, `uld`, `umerge`, `upas`, are written in Pascal.
- `ld` is unknown at present

## State of the repository

The following table specify if each binary has been matched or not, and if it has their functions matching or the whole binary/elf.

| Program | 5.3 functions | 5.3 elf | 7.1 functions | 7.1 elf |
| -       | -   | -   | -   | -   |
| `cc`    | :x: | :x: | :heavy_check_mark: | :x: |
| `cfe`   | :x: | :x: | :x: | :x: |
| `uopt`  | :x: | :x: | :x: | :x: |
| `ugen`  | :x: | :x: | :x: | :x: |
| `as1`   | :x: | :x: | :x: | :x: |
| `as0`   | :x: | :x: | :x: | :x: |
| `ld`    | :x: | :x: | :x: | :x: |
| `uld`   | :x: | :x: | :x: | :x: |
| `upas`  | :x: | :x: | :x: | :x: |

## Build dependencies

TODO

```bash
python3 -m pip install -r requirements.txt
```

## Setup

```bash
make setup
make disasm
make
```

Diff: `./diff.py -mwob --objfile build/src/7.1/cc/cc.o main`

## Sources

- `lib/indy/dev/usr/lib/crt{1,n}.o` are from `IRISDevelopmentOption7.1.1forIRIX6.4_02-97_812-0625-002.iso`
