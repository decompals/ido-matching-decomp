#!/bin/bash
mkdir -p a b
c="mips-linux-gnu-objcopy -O binary"
for A in .interp .MIPS.options .reginfo .dynamic .liblist .dynsym .dynstr .hash .MIPS.symlib .msym .MIPS.stubs .text .init .rodata .data .got .bss; do
	B=${A#.}
	OLDHASH=$(sha256sum b/$B | head -c 10 2>/dev/null)
	$c $1 -j $A a/$B
	$c $2 -j $A b/$B
	chmod -x a/$B b/$B
	printf "%-15s" $A
	NEWHASH=$(sha256sum b/$B | head -c 10)
	cmp=""
	if [ $OLDHASH = $NEWHASH ]; then
		cmp=", unchanged"
	fi
	diff -q a/$B b/$B >/dev/null && echo OK || echo DIFF \($NEWHASH$cmp\)
done

# Global entries:
# SHN_MIPS_DATA = PRC[0xff02]
# SHN_MIPS_TEXT = PRC[0xff01]
#   Address     Access  Initial Sym.Val. Type    Ndx Name
#  1000c4f4 -32252(gp) 004314e8 004314dc FUNC    PRC[0xff01] add_prelinker_objects
#  1000ca58 -30872(gp) 1000ec68 1000ec68 OBJECT  PRC[0xff02] asflags
mips-linux-gnu-readelf -A $1 > a/got-text
mips-linux-gnu-readelf -A $2 > b/got-text

# python3 -m spimdisasm.elfObjDisasm --no-emit-cpload --Mreg-names o32 --no-use-fpccsr --aggressive-string-guesser --save-context a/disasm_context.csv $1 a/disasm/
python3 -m spimdisasm.elfObjDisasm --no-emit-cpload --Mreg-names o32 --no-use-fpccsr --aggressive-string-guesser --save-context b/disasm_context.csv $2 b/disasm/

python3 tools/print_context_symbols.py a/disasm_context.csv >a/context_symbols.txt
python3 tools/print_context_symbols.py b/disasm_context.csv >b/context_symbols.txt

python3 tools/sort_libc_symbols.py a/got-text >a/libc_syms.txt
python3 tools/sort_libc_symbols.py b/got-text >b/libc_syms.txt
