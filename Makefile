

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

IINC       := -Iinclude -Isrc


LDFLAGS := -nostdlib -L$(RECOMP)/ido/7.1/usr/lib/ -lc


ASMPROCFLAGS := 
OPTFLAGS := -O1
MIPS_VERSION := -mips2
ASFLAGS := -march=vr4300 -32 -Iinclude -KPIC

CFLAGS += -G 0 -kPIC -Xfullwarn -Xcpluscomm $(IINC) -nostdinc -Wab,-r4300_mul -woff 624,649,838,712


CC_ELF := $(BUILD)/cc


SRC_DIRS := $(shell find src -type d)
C_FILES  := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
O_FILES  := $(foreach f,$(C_FILES:.c=.o),$(BUILD)/$(f))

# Automatic dependency files
# (Only asm_processor dependencies are handled for now)
DEP_FILES := $(O_FILES:.o=.asmproc.d)

# create build directories
$(shell mkdir -p $(foreach dir,$(SRC_DIRS),$(BUILD)/$(dir)))


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
	mkdir -p $(BUILD)/$(ASM)/cc
	$(DISASSEMBLER) $(RECOMP)/ido/7.1/usr/bin/cc asm/cc --split-functions asm/functions --aggressive-string-guesser --save-context $(CONTEXT)/cc.ctx


$(CC_ELF): build/asm/cc/cc.text.o build/asm/cc/cc.data.o build/asm/cc/cc.rodata.o build/asm/cc/cc.bss.o
	$(LD) $^ $(LDFLAGS) --no-check-sections --accept-unknown-input-arch --allow-shlib-undefined -Map build/cc.map -o $@ || (rm -f $@ && exit 1)

$(BUILD)/$(ASM)/%.o: $(ASM)/%.s
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD)/%.o: %.c
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
