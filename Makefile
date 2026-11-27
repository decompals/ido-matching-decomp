# IDO matching decomp build.
# Override settings on the command line (make SETTING=value) or in .make_options.

-include .make_options

# ---------------------------------------------------------------------------
# Configuration
# ---------------------------------------------------------------------------

# IDO version to build; "both" builds 5.3 and 7.1.
VERSION ?= 7.1
# Treat host syntax-check warnings as errors.
WERROR ?= 0
CC_CHECK_COMP ?= gcc

MIPS_BINUTILS_PREFIX ?= mips-linux-gnu-
UV ?= uv
OBJDIFF_CLI ?= objdiff-cli
DIFF_FLAGS ?=

RECOMP_VERSION := v1.2

# Programs disassembled for each version.
IDO_TC_7.1 := cc cfe ugen as1 umerge as0 uopt
IDO_TC_5.3 := cc cfe as0 ugen

# Source trees that only exist for one version.
SRC_EXCLUDE_7.1 :=
SRC_EXCLUDE_5.3 := src/as1

ifeq ($(filter $(VERSION),5.3 7.1),)
$(error Unknown or unsupported IDO version - $(VERSION))
endif

IDO_VERSION := IDO_$(subst .,,$(VERSION))
IDO_TC := $(IDO_TC_$(VERSION))
SRC_EXCLUDE := $(SRC_EXCLUDE_$(VERSION))

# ---------------------------------------------------------------------------
# Toolchain and paths
# ---------------------------------------------------------------------------

# Fail early if the required binutils are not installed.
ifneq ($(shell type $(MIPS_BINUTILS_PREFIX)ld >/dev/null 2>/dev/null; echo $$?), 0)
$(error Please install or build mips-linux-gnu)
endif

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
DETECTED_OS := linux
else ifeq ($(UNAME_S),Darwin)
DETECTED_OS := macos
else
$(error Unsupported OS: $(UNAME_S))
endif

ROOTDIR := $(CURDIR)
PYTHON := $(UV) run python
RECOMP := $(ROOTDIR)/tools/ido_recomp

BUILD := build
ASM := asm
SYMBOLS := symbols
CONTEXT := context
YACCDIR := tools/yacc

CC := $(RECOMP)/$(VERSION)/cc
AS := $(MIPS_BINUTILS_PREFIX)as
LD := $(MIPS_BINUTILS_PREFIX)ld

DISASSEMBLER := $(PYTHON) -m spimdisasm.elfObjDisasm
DISASSEMBLER_FLAGS := --no-emit-cpload --Mreg-names o32 --no-use-fpccsr \
	--rodata-string-guesser 4 --pascal-rodata-string-guesser 4 \
	--print-new-file-boundaries --asm-jtbl-label jlabel --asm-data-label dlabel

YACC := $(YACCDIR)/yacc
YFLAGS := -p $(YACCDIR)/yaccpar -t

IRIX_BASE ?= ido
IRIX_USR_DIR ?= $(IRIX_BASE)/$(VERSION)/usr

# ---------------------------------------------------------------------------
# Flags
# ---------------------------------------------------------------------------

IINC := -I$(ROOTDIR)/include -I$(ROOTDIR)/include/indy -I$(ROOTDIR)/src

# Host-compiler syntax check.
CHECK_WARNINGS := -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-variable \
	-Wno-char-subscripts -Wno-unused-label -Wno-parentheses \
	-Wno-unused-parameter -Wno-pointer-sign -Wno-switch
MIPS_BUILTIN_DEFS := -D_MIPS_FPSET=16 -D_MIPS_ISA=2 -D_ABIO32=1 -D_MIPS_SIM=_ABIO32 \
	-D_MIPS_SZINT=32 -D_MIPS_SZLONG=32 -D_MIPS_SZPTR=32 \
	-D__EXTENSIONS__ -DLANGUAGE_C -D_LANGUAGE_C -D__INLINE_INTRINSICS \
	-Dsgi -D__sgi -Dunix -Dmips -Dhost_mips -D__unix -D__host_mips -D_SVR4_SOURCE \
	-D_MODERN_C -D_SGI_SOURCE -D__DSO__ -DSYSTYPE_SVR4 -D_SYSTYPE_SVR4 -D_LONGLONG \
	-D__mips=2 -D_MIPSEB -DMIPSEB -D_CFE -DPERMUTER=1

CC_CHECK := $(CC_CHECK_COMP)
# -MMD writes a .d dependency file next to the checked object.
CC_CHECK_FLAGS := -MMD -fno-builtin -fsyntax-only -funsigned-char -std=c11 -m32 \
	-DNON_MATCHING -DCC_CHECK=1
ifneq ($(WERROR), 0)
CHECK_WARNINGS += -Werror
endif

LDFLAGS := -nostdlib -L$(RECOMP)/ido/$(VERSION)/usr/lib/ -lc

OPTFLAGS := -O1
MIPS_VERSION := -mips2
ASFLAGS := -march=vr4300 -32 -Iinclude -KPIC
IDO_WARNINGS := -fullwarn -woff 624,649,838,712,835
CFLAGS += -G 0 -KPIC -Xcpluscomm $(IINC) -nostdinc -Wab,-r4300_mul \
	$(IDO_WARNINGS) -D$(IDO_VERSION)

# Per-directory optimization overrides needed to match the original binaries.
build/src/7.1/libmld/%.o: OPTFLAGS := -O2
build/src/7.1/as0/%.o: OPTFLAGS := -O2
build/src/7.1/as1/%.o: OPTFLAGS := -O2
build/src/7.1/cfe/%.o: OPTFLAGS := -O2
build/src/7.1/ugen/%.o: OPTFLAGS := -O2 -Olimit 1600
build/src/7.1/libu/%.o: OPTFLAGS := -O2
build/src/7.1/libp/%.o: OPTFLAGS := -O2
build/src/5.3/as0/%.o: OPTFLAGS := -O2
build/src/5.3/as0/%.o: MIPS_VERSION := -mips1
build/src/5.3/libu/%.o: OPTFLAGS := -O2
build/src/5.3/libp/%.o: OPTFLAGS := -O2
build/src/5.3/libmld/%.o: OPTFLAGS := -O2

# ---------------------------------------------------------------------------
# Sources and generated objects
# ---------------------------------------------------------------------------

ALL_SRC_DIRS := $(shell find src -type d)
SRC_DIRS := $(filter-out $(SRC_EXCLUDE),$(ALL_SRC_DIRS))
ASM_DIRS := $(shell find $(ASM)/$(VERSION) -type d \
	-not -path "$(ASM)/$(VERSION)/functions*" 2>/dev/null)

C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
P_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.p))
S_FILES := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
COMBINED_S_FILES := $(sort $(basename $(S_FILES:.s=)))
Y_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.y))

O_FILES := $(Y_FILES:src/%.y=$(BUILD)/src/$(VERSION)/%.o) \
	$(C_FILES:src/%.c=$(BUILD)/src/$(VERSION)/%.o) \
	$(P_FILES:src/%.p=$(BUILD)/src/$(VERSION)/%.o) \
	$(COMBINED_S_FILES:$(ASM)/$(VERSION)/%=$(BUILD)/$(ASM)/$(VERSION)/%.o)
DEP_FILES := $(O_FILES:.o=.d)

# ---------------------------------------------------------------------------
# Main targets
# ---------------------------------------------------------------------------

PYTHON_PROGRESS := $(PYTHON) tools/progress.py
OBJDIFF_REPORT := $(OBJDIFF_CLI) report generate -p . -o $(BUILD)/report.json

.PHONY: all build both clean distclean setup uv-sync yacc disasm \
	disasm-all objdiff report diff progress
.DEFAULT_GOAL := all

all: build

build: $(O_FILES)

both:
	$(MAKE) VERSION=5.3 build
	$(MAKE) VERSION=7.1 build

# Tooling setup.
uv-sync:
	$(UV) sync

setup: uv-sync $(RECOMP) $(YACC)

yacc: $(YACC)

# objdiff configuration and report.
objdiff: build
	$(PYTHON) tools/gen_objdiff.py --version all

report: objdiff
	$(OBJDIFF_REPORT)

progress: report
	$(PYTHON_PROGRESS)

diff: objdiff
	@if [ -z "$(UNIT)" ]; then \
		echo "usage: make diff UNIT=<version>/<program>/<file> [SYM=<symbol>]"; \
		exit 2; \
	fi
	$(OBJDIFF_CLI) diff -p . -u $(UNIT) $(SYM) $(DIFF_FLAGS)

clean:
	$(RM) -r $(BUILD)
	$(RM) $(Y_FILES:.y=.c)

distclean: clean
	$(RM) -r $(RECOMP) $(ASM) $(YACC)

# ---------------------------------------------------------------------------
# Build rules
# ---------------------------------------------------------------------------

$(RECOMP):
	mkdir -p $@/5.3 $@/7.1
	curl -sL https://github.com/decompals/ido-static-recomp/releases/download/$(RECOMP_VERSION)/ido-5.3-recomp-$(DETECTED_OS).tar.gz | tar xz -C $@/5.3
	curl -sL https://github.com/decompals/ido-static-recomp/releases/download/$(RECOMP_VERSION)/ido-7.1-recomp-$(DETECTED_OS).tar.gz | tar xz -C $@/7.1

$(YACC):
	gcc -std=c99 $(YACCDIR)/*.c -o $(YACC)

$(BUILD)/src/$(VERSION)/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC_CHECK) $(CC_CHECK_FLAGS) $(IINC) $(CHECK_WARNINGS) $(MIPS_BUILTIN_DEFS) -o $@ $<
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<

$(BUILD)/src/$(VERSION)/%.o: src/%.p
	@mkdir -p $(@D)
	@if [ "$(CC)" != "@:" ]; then \
		(cd $(dir $<) && $(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $(abspath $@) $(notdir $<)); \
	fi

$(BUILD)/$(ASM)/%.o: $(ASM)/%.*.s include/macro.inc
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) $(filter %.s,$^) -o $@

%.c: %.y
	$(YACC) $(YFLAGS) $<
	mv y.tab.c $@

# Kept for future matching-ELF work.
$(BUILD)/$(ASM)/$(VERSION)/%.elf: $(O_FILES)
	@mkdir -p $(@D)
	$(LD) $(BUILD)/$(ASM)/$(VERSION)/$*/*.o $(LDFLAGS) --no-check-sections \
		--accept-unknown-input-arch --allow-shlib-undefined \
		-Map $(BUILD)/$(ASM)/$(VERSION)/$*.map -o $@ || (rm -f $@ && exit 1)

# ---------------------------------------------------------------------------
# Disassembly
# ---------------------------------------------------------------------------

# A .disasm stamp is created after each binary has been disassembled, so an
# up-to-date tree is not regenerated on every invocation.
DISASM_STAMPS := $(foreach binary,$(IDO_TC),$(ASM)/$(VERSION)/$(binary)/.disasm)
DISASM_ADDRS := $(wildcard $(SYMBOLS)/$(VERSION)/*.reloc_addrs.txt) \
	$(wildcard $(SYMBOLS)/$(VERSION)/*.symbol_addrs.txt)

# Optional per-program address overrides.
disasm_addrs = \
	$(if $(wildcard $(SYMBOLS)/$(VERSION)/$(1).reloc_addrs.txt),--reloc-addrs $(SYMBOLS)/$(VERSION)/$(1).reloc_addrs.txt) \
	$(if $(wildcard $(SYMBOLS)/$(VERSION)/$(1).symbol_addrs.txt),--symbol-addrs $(SYMBOLS)/$(VERSION)/$(1).symbol_addrs.txt)

disasm: $(DISASM_STAMPS)
	find $(ASM)/$(VERSION) -type f -name "*.s" -not -path "*/functions/*" | xargs sed -i -E \
		-e 's/^glabel (func_[^ ,]*)([[:space:]]*#.*)?$$/glabel \1, local\2/' \
		-e 's/^dlabel ((RO_|D_|jtbl_)[^ ,]*)([[:space:]]*#.*)?$$/dlabel \1, local\3/' \
		-e 's/^dlabel (B_)/llabel \1/'

disasm-all:
	$(MAKE) VERSION=5.3 disasm
	$(MAKE) VERSION=7.1 disasm

# cc lives in bin/ rather than lib/.
$(ASM)/$(VERSION)/cc/.disasm: $(IRIX_USR_DIR)/bin/cc $(SYMBOLS)/$(VERSION)/cc.splits.csv \
		$(DISASM_ADDRS) Makefile
	$(DISASSEMBLER) $(DISASSEMBLER_FLAGS) $(call disasm_addrs,cc) \
		--file-splits $(SYMBOLS)/$(VERSION)/cc.splits.csv \
		--save-context $(CONTEXT)/$(VERSION)/cc.csv $< $(dir $@)
	@touch $@

$(ASM)/$(VERSION)/%/.disasm: $(IRIX_USR_DIR)/lib/% $(SYMBOLS)/$(VERSION)/%.splits.csv \
		$(DISASM_ADDRS) Makefile
	$(DISASSEMBLER) $(DISASSEMBLER_FLAGS) $(call disasm_addrs,$*) \
		--file-splits $(SYMBOLS)/$(VERSION)/$*.splits.csv \
		--save-context $(CONTEXT)/$(VERSION)/$*.csv \
		$(IRIX_USR_DIR)/lib/$* $(ASM)/$(VERSION)/$*
	@touch $@

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

print-%:
	$(info $* is a $(flavor $*) variable set to [$($*)])
	@true

-include $(DEP_FILES)
