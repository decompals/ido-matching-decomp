

#### Tools ####
ifeq ($(shell type mips-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
  MIPS_BINUTILS_PREFIX := mips-linux-gnu-
else
  $(error Please install or build mips-linux-gnu)
endif

RECOMP := tools/recomp
BUILD  := build
ASM    := asm

CC       := $(RECOMP)/build/7.1/out/cc
CC_OLD   := $(RECOMP)/build/5.3/out/cc

AS         := $(MIPS_BINUTILS_PREFIX)as
LD         := $(MIPS_BINUTILS_PREFIX)ld
OBJCOPY    := $(MIPS_BINUTILS_PREFIX)objcopy
OBJDUMP    := $(MIPS_BINUTILS_PREFIX)objdump
MIPS_GCC   := $(MIPS_BINUTILS_PREFIX)gcc

DISASSEMBLER  := python3 -m spimdisasm.elfObjDisasm
ASM_PROCESSOR := python3 tools/asm-processor/build.py

IINC       := -Iinclude -Isrc


LDFLAGS := -L$(RECOMP)/ido/7.1/lib/ -lc


ASMPROCFLAGS := 
OPTFLAGS := -O2
ASFLAGS := -march=vr4300 -32 -Iinclude
MIPS_VERSION := -mips2

CFLAGS += -G 0 -non_shared -Xfullwarn -Xcpluscomm $(IINC) -nostdinc -Wab,-r4300_mul -woff 624,649,838,712


CC_ELF := $(BUILD)/cc

# Targets

.PHONY: all clean
.DEFAULT_GOAL:= all

all: $(CC_ELF)

clean:
	$(RM) -r $(BUILD)

distclean: clean
	$(MAKE) -C $(RECOMP) clean
	$(RM) -r $(ASM)

setup:
	$(MAKE) -C $(RECOMP) setup
	$(MAKE) -C $(RECOMP)

disasm:
	mkdir -p buildasm/cc
	$(DISASSEMBLER) $(RECOMP)/ido/7.1/usr/bin/cc asm/cc


$(CC_ELF): build/asm/cc/cc.text.o build/asm/cc/cc.data.o build/asm/cc/cc.rodata.o build/asm/cc/cc.bss.o
	$(LD) $^ $(LDFLAGS) --no-check-sections --accept-unknown-input-arch --emit-relocs -Map build/cc.map -o $@ || rm -f $@ && exit 1

$(BUILD)/$(ASM)/%.o: $(ASM)/%.s
	$(AS) $(ASFLAGS) $< -o $@

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
