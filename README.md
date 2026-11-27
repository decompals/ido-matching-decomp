# IDO matching decomp

Matching decompilation of the IRIX Development Option (IDO) compiler
toolchain: rebuild the original programs as C, Pascal and assembly sources that
produce byte-identical objects with the original IDO compilers.

Highest priority, for compiling a C file to an unlinked object:

- `cc` - compiler driver
- `cfe` - C frontend, preprocessor and driver for optimisation/code generation
- `uopt` - optimiser used by `-O2`
- `ugen` - code generator used at lower optimisation levels
- `as1` - assembler for compiler-generated assembly

Lower priority: `as0` (handwritten assembly), `ld` (linker), `uld` and `umerge`
(for `-O3`), and `upas` (Pascal). `cc`, `cfe` and `as0` are C (`cfe` also uses
Yacc); the rest are Pascal. 5.3 builds `cc`, `cfe`, `as0` and `ugen`; 7.1 adds
`as1`, `uopt` and `umerge`. `ld`, `uld`, `upas`, `ujoin`, `usplit`, `acpp` and
`copt` are not wired yet.

## Progress

`PROGRESS.md` is the only progress output. `make progress` regenerates it; do not
edit it by hand.

## Requirements and setup

Linux x86_64 is tested; macOS needs `mips-linux-gnu` binutils and the macOS IDO
recomp release. Required: `git`, `make`, `gcc`, `curl`, `tar`, `uv` with Python
3.13, MIPS binutils (`ld`, `as`, `objcopy`, `objdump`, `readelf`, `nm`),
`gcc-multilib`, `objdiff-cli` 3.8.3+ and network access.

```bash
sudo apt-get update
sudo apt-get install -y build-essential git curl binutils-mips-linux-gnu gcc-multilib
curl -LsSf https://astral.sh/uv/install.sh | sh && uv python install 3.13
mkdir -p "$HOME/.local/bin"
curl -fsSL https://github.com/encounter/objdiff/releases/download/v3.8.3/objdiff-cli-linux-x86_64 -o "$HOME/.local/bin/objdiff-cli"
chmod +x "$HOME/.local/bin/objdiff-cli" && export PATH="$HOME/.local/bin:$PATH"
git clone https://github.com/Unnunu/ido-matching-decomp.git
cd ido-matching-decomp
uv sync && make setup && make disasm && make
```

On other platforms use the objdiff releases page, or pass `OBJDIFF_CLI=/path/to/objdiff-cli`.

`make setup` installs Python packages, downloads IDO recomp into `tools/ido_recomp/` and builds
`tools/yacc/yacc`. `make disasm` is incremental per program via `.disasm` stamps, rerunning when a
binary, split CSV, address override file or the `Makefile` changes (`make -B disasm` forces it).
For both: `make disasm-all` then `make both`.

## Building

```bash
make                  # current VERSION, default 7.1
make VERSION=5.3      # IDO 5.3
make both             # 5.3 and 7.1 without cleaning
make clean            # remove build/ and generated Yacc C files
make distclean        # also remove asm/, tools/ido_recomp and tools/yacc/yacc
```

Supported `VERSION` values are `7.1` and `5.3`. Builds use the recompiled IDO compilers, `mips-linux-gnu-as` and a host `gcc` check; matching optimisation overrides live in the `Makefile`.

## Diffing

`make diff` rebuilds stale objects, regenerates `objdiff.json` and runs the diff.
`make objdiff` only regenerates the config. `objdiff.json` is generated and ignored.

Console:

```bash
make diff UNIT=7.1/ugen/build SYM=build_tree
```

For raw `objdiff-cli`, build and generate the config first:

```bash
make both && make objdiff
objdiff-cli diff -p . -u 7.1/ugen/build build_tree
```

For the GUI, open the repository root and use the **Build** button or the on-save
watcher; both rebuild through `build_base`/`custom_make` in `objdiff.json`.

`objdiff-cli` is required for `make progress`. The GUI is convenient for
inspecting diffs because it shows the units in a tree, including `.data` and
`.rodata`.

## Provenance

`lib/indy/dev/usr/lib/crt1.o` and `crtn.o` are from `IRISDevelopmentOption7.1.1forIRIX6.4_02-97_812-0625-002.iso`.
