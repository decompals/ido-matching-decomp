
# if WERROR is 1, pass -Werror to CC_CHECK, so warnings would be treated as errors
WERROR ?= 0
CC_CHECK_COMP ?= gcc

#### Tools ####
ifeq ($(shell type mips-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
  MIPS_BINUTILS_PREFIX := mips-linux-gnu-
else
  $(error Please install or build mips-linux-gnu)
endif

RECOMP  := tools/recomp
BUILD   := build
ASM     := asm
CONTEXT := context

CC       := $(RECOMP)/build/7.1/out/cc
CC_OLD   := $(RECOMP)/build/5.3/out/cc

AS         := $(MIPS_BINUTILS_PREFIX)as
LD         := $(MIPS_BINUTILS_PREFIX)ld
OBJCOPY    := $(MIPS_BINUTILS_PREFIX)objcopy
OBJDUMP    := $(MIPS_BINUTILS_PREFIX)objdump
MIPS_GCC   := $(MIPS_BINUTILS_PREFIX)gcc

DISASSEMBLER  := python3 -m spimdisasm.elfObjDisasm --no-emit-cpload
ASM_PROCESSOR := python3 tools/asm-processor/build.py

IINC       := -Iinclude -Iinclude/indy -Isrc

# Check code syntax with host compiler
# TODO
# CHECK_WARNINGS := -Wall -Wextra -Wno-unknown-pragmas -Wno-int-conversion
CHECK_WARNINGS := -w
# Have CC_CHECK pretend to be a MIPS compiler
MIPS_BUILTIN_DEFS := -D_MIPS_FPSET=16 -D_MIPS_ISA=2 -D_ABIO32=1 -D_MIPS_SIM=_ABIO32 -D_MIPS_SZINT=32 -D_MIPS_SZLONG=32 -D_MIPS_SZPTR=32
MIPS_BUILTIN_DEFS += -D__EXTENSIONS__ -DLANGUAGE_C -D_LANGUAGE_C -D__INLINE_INTRINSICS
MIPS_BUILTIN_DEFS += -Dsgi -D__sgi -Dunix -Dmips -Dhost_mips -D__unix -D__host_mips -D_SVR4_SOURCE
MIPS_BUILTIN_DEFS += -D_MODERN_C -D_SGI_SOURCE -D__DSO__ -DSYSTYPE_SVR4 -D_SYSTYPE_SVR4 -D_LONGLONG
MIPS_BUILTIN_DEFS += -D__mips=2 -D_MIPSEB -DMIPSEB -D_CFE
MIPS_BUILTIN_DEFS += -DPERMUTER=1
#	The -MMD flags additionaly creates a .d file with the same name as the .o file.
CC_CHECK          := $(CC_CHECK_COMP)
CC_CHECK_FLAGS    := -MMD -fno-builtin -fsyntax-only -fsigned-char -fdiagnostics-color -std=gnu89 -m32 -DNON_MATCHING -DCC_CHECK=1
ifneq ($(WERROR), 0)
	CHECK_WARNINGS += -Werror
endif


LDFLAGS := -nostdlib -L$(RECOMP)/ido/7.1/usr/lib/ -lc


ASMPROCFLAGS := 
OPTFLAGS := -O1
MIPS_VERSION := -mips2
ASFLAGS := -march=vr4300 -32 -Iinclude -KPIC

CFLAGS += -G 0 -kPIC -Xfullwarn -Xcpluscomm $(IINC) -nostdinc -Wab,-r4300_mul -woff 624,649,838,712


CC_ELF := $(BUILD)/7.1/cc.elf


SRC_DIRS := $(shell find src -type d)
ASM_DIRS := $(shell find asm -type d -not -path "asm/7.1/functions*")

C_FILES  := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES  := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))

O_FILES  := $(foreach f,$(C_FILES:.c=.o),$(BUILD)/$(f)) \
            $(foreach f,$(S_FILES:.s=.o),$(BUILD)/$(f))

# Automatic dependency files
DEP_FILES := $(O_FILES:.o=.d) \
             $(O_FILES:.o=.asmproc.d)

# create build directories
$(shell mkdir -p $(foreach dir,$(SRC_DIRS),$(BUILD)/$(dir)) $(BUILD)/7.1)


$(BUILD)/src/%.o: CC := $(ASM_PROCESSOR) $(ASM_PROC_FLAGS) $(CC) -- $(AS) $(ASFLAGS) --

# Targets

.PHONY: all clean distclean setup disasm
.DEFAULT_GOAL:= all

all: $(CC_ELF) $(O_FILES)

clean:
	$(RM) -r $(BUILD)

distclean: clean
	$(MAKE) -C $(RECOMP) clean
	$(RM) -r $(ASM)

setup:
	$(MAKE) -C $(RECOMP) setup
	$(MAKE) -C $(RECOMP) DEBUG=0 VERSION=7.1
	$(MAKE) -C $(RECOMP) DEBUG=0 VERSION=5.3

disasm:
	$(RM) -rf $(ASM)
	mkdir -p $(BUILD)/$(ASM)/7.1/cc
	$(DISASSEMBLER) $(RECOMP)/ido/7.1/usr/bin/cc asm/7.1/cc --Mreg-names o32 --split-functions asm/7.1/functions --aggressive-string-guesser --save-context $(CONTEXT)/7.1/cc.csv


$(CC_ELF): build/asm/7.1/cc/cc.text.o build/asm/7.1/cc/cc.data.o build/asm/7.1/cc/cc.rodata.o build/asm/7.1/cc/cc.bss.o
	$(LD) $^ $(LDFLAGS) --no-check-sections --accept-unknown-input-arch --allow-shlib-undefined -Map build/7.1/cc.map -o $@ || (rm -f $@ && exit 1)

$(BUILD)/$(ASM)/%.o: $(ASM)/%.s
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD)/%.o: %.c
	$(CC_CHECK) $(CC_CHECK_FLAGS) $(IINC) $(CHECK_WARNINGS) $(MIPS_BUILTIN_DEFS) -o $@ $<
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true

-include $(DEP_FILES)
