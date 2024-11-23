/*
 * @file: as0util.c
 *
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "sym.h"
#include "stsupport.h"
#include "filehdr.h"
#include "ldfcn.h"
#include "cmplrs/stext.h"
#include "binasm_rec.h"
#include "common.h"

#define TRUE 1
#define FALSE 0

#define FOUND TRUE
#define NOT_FOUND FALSE

#define BUF_COUNT 0x400

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a > b) ? b : a)

//.data
char* sitype[0x3F] = {
    "label",    ".sym",      ".globl",   ".cpload",      ".align",    ".ascii",  ".asciiz",    ".byte",   ".comm",
    ".lcomm",   ".data",     ".double",  ".file",        ".float",    ".half",   ".cprestore", ".gpword", ".cpadd",
    ".weakext", ".loopno",   ".space",   ".text",        ".word",     "ocode",   ".end",       ".sdata",  ".rdata",
    ".ent",     ".loc",      ".bgnb",    ".endb",        ".asm0",     ".set",    ".cpalias",   ".repeat", ".endr",
    ".lab",     ".vreg",     ".mask",    ".fmask",       ".err",      "globabs", ".verstamp",  ".frame",  ".extended",
    ".extern",  ".aent",     ".option",  ".noalias",     ".alias",    ".mtag",   ".malias",    ".struct", ".livereg",
    ".gjaldef", ".gjallive", ".gjrlive", ".ishift_addr", ".irestext", ".dword",  ".prologue",  ".edata",  ".alloc",
};

char* sregisters[0x49] = {
    "$0",    "$1",    "$2",    "$3",    "$4",    "$5",    "$6",    "$7",   "$8",   "$9",   "$10",  "$11",  "$12",
    "$13",   "$14",   "$15",   "$16",   "$17",   "$18",   "$19",   "$20",  "$21",  "$22",  "$23",  "$24",  "$25",
    "$26",   "$27",   "$28",   "$29",   "$30",   "$31",   "$f0",   "$f1",  "$f2",  "$f3",  "$f4",  "$f5",  "$f6",
    "$f7",   "$f8",   "$f9",   "$f10",  "$f11",  "$f12",  "$f13",  "$f14", "$f15", "$f16", "$f17", "$f18", "$f19",
    "$f20",  "$f21",  "$f22",  "$f23",  "$f24",  "$f25",  "$f26",  "$f27", "$f28", "$f29", "$f30", "$f31", "$fcc0",
    "$fcc1", "$fcc2", "$fcc3", "$fcc4", "$fcc5", "$fcc6", "$fcc7", "   ",
};

// Seems to be unused in 5.3 and 7.1
char* sopt_type[3] = {
    "none",
    "optimize",
    "pic",
};

char* sset_value[0x11] = {
    "",     "reorder", "noreorder", "macro",      "nomacro",   "at",          "noat",       "move",         "nomove",
    "bopt", "nobopt",  "volatile",  "novolatile", "transform", "notransform", "reposition", "noreposition",
};
// UNUSED
char* sformat_extn[7] = {
    "franone", "frahi", "fralo", "frarel1", "frarel2",
    "", // 0x000000
    "", // 0x000000
};

char* sframereg = "$framereg";
char* sframesize = "$framesize";

extern int gform_extn;
struct _struct_asm_info_0x8 asm_info[0x1AF] = {
    { "abs", 0x08000420 },
    { "add", 0x060A0421 },
    { "addu", 0x060A8421 },
    { "and", 0x060C0421 },
    { "b", (unsigned)&gform_extn },
    { "bc0f", 0x101C8000 },
    { "bc0t", 0x101D0000 },
    { "bc1f", 0x101DB000 },
    { "bc1t", 0x101E3000 },
    { "bc2f", 0x101E8000 },
    { "bc2t", 0x101F0000 },
    { "", 0 },
    { "", 0 },
    { "beq", 0x0C258420 },
    { "bge", 0x0C000420 },
    { "bgeu", 0x0C000420 },
    { "bgez", 0x0E1B0400 },
    { "bgt", 0x0C000420 },
    { "bgtu", 0x0C000420 },
    { "bgtz", 0x0E270400 },
    { "ble", 0x0C000420 },
    { "bleu", 0x0C000420 },
    { "blez", 0x0E268400 },
    { "blt", 0x0C000420 },
    { "bltu", 0x0C000420 },
    { "bltz", 0x0E1A8400 },
    { "bne", 0x0C260420 },
    { "break", 0x58000 },
    { "c0", 0x12318000 },
    { "c1", 0x12320000 },
    { "c2", 0x12328000 },
    { "", 0 },
    { "div", 0x06090421 },
    { "divu", 0x06098421 },
    { "j", 0x0A248400 },
    { "jal", 0x0A250400 },
    { "la", 0x02000400 },
    { "lb", 0x02330460 },
    { "lbu", 0x02350460 },
    { "lh", 0x02338460 },
    { "lhu", 0x02358460 },
    { "li", 0x04000400 },
    { "lw", 0x02348460 },
    { "jr", 0x0A040400 },
    { "lwc1", 0x02399060 },
    { "lwc2", 0x023A0460 },
    { "pref", 0x1E9E0460 },
    { "mfhi", 0x14060400 },
    { "mflo", 0x14070400 },
    { "move", 0x08000420 },
    { "jalr", 0x0A048400 },
    { "swc1", 0x023B1060 },
    { "swc2", 0x023B8460 },
    { "", 0 },
    { "mthi", 0x14068400 },
    { "mtlo", 0x14078400 },
    { "mul", 0x06000421 },
    { "mulo", 0x06000421 },
    { "mulou", 0x06000421 },
    { "mult", 0x08080420 },
    { "multu", 0x08088420 },
    { "neg", 0x08000420 },
    { "nop", 0x8000 },
    { "nor", 0x060D8421 },
    { "or", 0x060C8421 },
    { "rem", 0x06090421 },
    { "remu", 0x06098421 },
    { "rfe", 0x498000 },
    { "rol", 0x06000421 },
    { "ror", 0x06000421 },
    { "sb", 0x02368460 },
    { "seq", 0x06000421 },
    { "sge", 0x06000421 },
    { "sgeu", 0x06000421 },
    { "sgt", 0x06000421 },
    { "sgtu", 0x06000421 },
    { "sh", 0x02370460 },
    { "sle", 0x06000421 },
    { "sleu", 0x06000421 },
    { "sll", 0x06010421 },
    { "slt", 0x06000421 },
    { "sltu", 0x06000421 },
    { "sne", 0x06000421 },
    { "sra", 0x06020421 },
    { "srl", 0x06018421 },
    { "sub", 0x060B0421 },
    { "subu", 0x060B8421 },
    { "sw", 0x02380460 },
    { "syscall", 0x50000 },
    { "xor", 0x060D0421 },
    { "not", 0x08000420 },
    { "lwl", 0x02340460 },
    { "lwr", 0x02360460 },
    { "swl", 0x02378460 },
    { "swr", 0x02388460 },
    { "", 0 },
    { "mfc0", 0x084584E0 },
    { "mfc1", 0x08460480 },
    { "mfc2", 0x084684E0 },
    { "", 0 },
    { "mtc0", 0x084784E0 },
    { "mtc1", 0x08480480 },
    { "mtc2", 0x084884E0 },
    { "sync", 0x4C0000 },
    { "tlbr", 0x4A0000 },
    { "tlbwi", 0x4A8000 },
    { "tlbwr", 0x4B0000 },
    { "tlbp", 0x4B8000 },
    { "ld", 0x023C8860 },
    { "sd", 0x023D0860 },
    { "", 0 },
    { "ldc1", 0x023D9460 },
    { "ldc2", 0x023E2060 },
    { "tlbr1", 0x9E8000 },
    { "tlbp1", 0x9F0000 },
    { "sdc1", 0x023E9460 },
    { "sdc2", 0x023F2060 },
    { "", 0 },
    { "l.s", 0x02001460 },
    { "l.d", 0x02001460 },
    { "l.e", 0x02001860 },
    { "s.s", 0x02001460 },
    { "s.d", 0x02001460 },
    { "s.e", 0x02001860 },
    { "add.s", 0x065014A5 },
    { "add.d", 0x065094A5 },
    { "add.e", 0x065118C6 },
    { "sub.s", 0x065194A5 },
    { "sub.d", 0x065214A5 },
    { "sub.e", 0x065298C6 },
    { "mul.s", 0x065314A5 },
    { "mul.d", 0x065394A5 },
    { "mul.e", 0x065418C6 },
    { "div.s", 0x065494A5 },
    { "div.d", 0x065514A5 },
    { "div.e", 0x065598C6 },
    { "sqrt.s", 0x080014A0 },
    { "sqrt.d", 0x080014A0 },
    { "sqrt.e", 0x080018C0 },
    { "mov.s", 0x080014A0 },
    { "mov.d", 0x080014A0 },
    { "mov.e", 0x080018C0 },
    { "abs.s", 0x080014A0 },
    { "abs.d", 0x080014A0 },
    { "abs.e", 0x080018C0 },
    { "cvt.s.d", 0x080014A0 },
    { "cvt.s.e", 0x080014C0 },
    { "cvt.s.w", 0x080014A0 },
    { "cvt.d.s", 0x080014A0 },
    { "cvt.d.e", 0x080014C0 },
    { "cvt.d.w", 0x080014A0 },
    { "cvt.e.s", 0x080018A0 },
    { "cvt.e.d", 0x080018A0 },
    { "cvt.e.w", 0x080018A0 },
    { "cvt.w.s", 0x080014A0 },
    { "cvt.w.d", 0x080014A0 },
    { "cvt.w.e", 0x080014C0 },
    { "c.f.s", 0x080030A5 },
    { "c.f.d", 0x080030A5 },
    { "c.f.e", 0x080030C6 },
    { "c.un.s", 0x080030A5 },
    { "c.un.d", 0x080030A5 },
    { "c.un.e", 0x080030C6 },
    { "c.eq.s", 0x080030A5 },
    { "c.eq.d", 0x080030A5 },
    { "c.eq.e", 0x080030C6 },
    { "c.ueq.s", 0x080030A5 },
    { "c.ueq.d", 0x080030A5 },
    { "c.ueq.e", 0x080030C6 },
    { "c.olt.s", 0x080030A5 },
    { "c.olt.d", 0x080030A5 },
    { "c.olt.e", 0x080030C6 },
    { "c.ult.s", 0x080030A5 },
    { "c.ult.d", 0x080030A5 },
    { "c.ult.e", 0x080030C6 },
    { "c.ole.s", 0x080030A5 },
    { "c.ole.d", 0x080030A5 },
    { "c.ole.e", 0x080030C6 },
    { "c.ule.s", 0x080030A5 },
    { "c.ule.d", 0x080030A5 },
    { "c.ule.e", 0x080030C6 },
    { "c.sf.s", 0x080030A5 },
    { "c.sf.d", 0x080030A5 },
    { "c.sf.e", 0x080030C6 },
    { "c.ngle.s", 0x080030A5 },
    { "c.ngle.d", 0x080030A5 },
    { "c.ngle.e", 0x080030C6 },
    { "c.seq.s", 0x080030A5 },
    { "c.seq.d", 0x080030A5 },
    { "c.seq.e", 0x080030C6 },
    { "c.ngl.s", 0x080030A5 },
    { "c.ngl.d", 0x080030A5 },
    { "c.ngl.e", 0x080030C6 },
    { "c.lt.s", 0x080030A5 },
    { "c.lt.d", 0x080030A5 },
    { "c.lt.e", 0x080030C6 },
    { "c.nge.s", 0x080030A5 },
    { "c.nge.d", 0x080030A5 },
    { "c.nge.e", 0x080030C6 },
    { "c.le.s", 0x080030A5 },
    { "c.le.d", 0x080030A5 },
    { "c.le.e", 0x080030C6 },
    { "c.ngt.s", 0x080030A5 },
    { "c.ngt.d", 0x080030A5 },
    { "c.ngt.e", 0x080030C6 },
    { "lui", 0x042D0400 },
    { "ulw", 0x02000460 },
    { "ulh", 0x02000460 },
    { "ulhu", 0x02000460 },
    { "usw", 0x02000460 },
    { "ush", 0x02000460 },
    { "addi", 0x06298420 },
    { "addiu", 0x062A0420 },
    { "slti", 0x062A8420 },
    { "sltiu", 0x062B0420 },
    { "andi", 0x062B8420 },
    { "ori", 0x062C0420 },
    { "xori", 0x062C8420 },
    { "", 0 },
    { "negu", 0x08000420 },
    { "beqz", 0x0E258400 },
    { "bnez", 0x0E260400 },
    { "neg.s", 0x080014A0 },
    { "neg.d", 0x080014A0 },
    { "neg.e", 0x080018C0 },
    { "cfc1", 0x084704E0 },
    { "ctc1", 0x084904E0 },
    { "bal", 0x0E1C0000 },
    { "bgezal", 0x0E1C0400 },
    { "bltzal", 0x0E1B8400 },
    { "mtc1.d", 0x084808A0 },
    { "mfc1.d", 0x084608A0 },
    { "trunc.w.s", 0x060014A1 },
    { "trunc.w.d", 0x060014A1 },
    { "trunc.w.e", 0x060018C1 },
    { "round.w.s", 0x060014A1 },
    { "round.w.d", 0x060014A1 },
    { "round.w.e", 0x060018C1 },
    { "addou", 0x060A8421 },
    { "subou", 0x060B8421 },
    { "truncu.w.s", 0x060014A1 },
    { "truncu.w.d", 0x060014A1 },
    { "truncu.w.e", 0x060018C1 },
    { "roundu.w.s", 0x060014A1 },
    { "roundu.w.d", 0x060014A1 },
    { "roundu.w.e", 0x060018C1 },
    { "cfc0", 0x087A04E0 },
    { "cfc2", 0x087A84E0 },
    { "", 0 },
    { "ctc0", 0x087B04E0 },
    { "ctc2", 0x087B84E0 },
    { "", 0 },
    { "li.s", 0x167C2400 },
    { "li.d", 0x167CA800 },
    { "li.e", 0x167D2C00 },
    { "tlt", 0x1A0F0420 },
    { "tltu", 0x1A0F8420 },
    { "tge", 0x1A100420 },
    { "tgeu", 0x1A108420 },
    { "teq", 0x1A110420 },
    { "tne", 0x1A118420 },
    { "ll", 0x02390460 },
    { "sc", 0x023A8460 },
    { "ceil.w.s", 0x060014A1 },
    { "ceil.w.d", 0x060014A1 },
    { "ceil.w.e", 0x060018C1 },
    { "ceilu.w.s", 0x060014A1 },
    { "ceilu.w.d", 0x060014A1 },
    { "ceilu.w.e", 0x060018C1 },
    { "floor.w.s", 0x060014A1 },
    { "floor.w.d", 0x060014A1 },
    { "floor.w.e", 0x060018C1 },
    { "flooru.w.s", 0x060014A1 },
    { "flooru.w.d", 0x060014A1 },
    { "flooru.w.e", 0x060018C1 },
    { "beql", 0x0C278420 },
    { "beqzl", 0x0E278400 },
    { "bnel", 0x0C280420 },
    { "bnezl", 0x0E280400 },
    { "blel", 0x0C000420 },
    { "bleul", 0x0C000420 },
    { "blezl", 0x0E288400 },
    { "bgtl", 0x0C000420 },
    { "bgtul", 0x0C000420 },
    { "bgtzl", 0x0E290400 },
    { "bltl", 0x0C000420 },
    { "bltul", 0x0C000420 },
    { "bltzl", 0x0E1F8400 },
    { "bltzall", 0x0E208400 },
    { "bgel", 0x0C000420 },
    { "bgeul", 0x0C000420 },
    { "bgezl", 0x0E200400 },
    { "bgezall", 0x0E210400 },
    { "bc0fl", 0x10218000 },
    { "bc0tl", 0x10220000 },
    { "bc1fl", 0x1022B000 },
    { "bc1tl", 0x10233000 },
    { "bc2fl", 0x10238000 },
    { "bc2tl", 0x10240000 },
    { "", 0 },
    { "", 0 },
    { "ldl", 0x023F8460 },
    { "ldr", 0x02400460 },
    { "lld", 0x02408460 },
    { "lwu", 0x023C0460 },
    { "sdl", 0x02410460 },
    { "sdr", 0x02418460 },
    { "scd", 0x02420460 },
    { "daddi", 0x06308420 },
    { "daddiu", 0x06310420 },
    { "dadd", 0x06120421 },
    { "daddu", 0x06128421 },
    { "dsub", 0x06130421 },
    { "dsubu", 0x06138421 },
    { "dsll", 0x06140421 },
    { "dsrl", 0x06148421 },
    { "dsra", 0x06150421 },
    { "dsllv", 0x06170421 },
    { "dsrlv", 0x06178421 },
    { "dsrav", 0x06180421 },
    { "dmult", 0x08188420 },
    { "dmultu", 0x08190420 },
    { "ddiv", 0x06000421 },
    { "ddivu", 0x06000421 },
    { "", 0 },
    { "", 0 },
    { "dmtc1", 0x084C8480 },
    { "dmfc1", 0x084D0480 },
    { "dmtc0", 0x084D84E0 },
    { "dmfc0", 0x084E04E0 },
    { "dmtc2", 0x084E84E0 },
    { "dmfc2", 0x084F04E0 },
    { "dli", 0x1C000400 },
    { "dla", 0x02000400 },
    { "eret", 0x8D8000 },
    { "trunc.l.s", 0x06001081 },
    { "round.l.s", 0x06001081 },
    { "ceil.l.s", 0x06001081 },
    { "floor.l.s", 0x06001081 },
    { "trunc.l.d", 0x06001081 },
    { "round.l.d", 0x06001081 },
    { "ceil.l.d", 0x06001081 },
    { "floor.l.d", 0x06001081 },
    { "trunc.l.e", 0x060010A1 },
    { "round.l.e", 0x060010A1 },
    { "ceil.l.e", 0x060010A1 },
    { "floor.l.e", 0x060010A1 },
    { "cvt.l.s", 0x08001080 },
    { "cvt.l.d", 0x08001080 },
    { "cvt.l.e", 0x080010A0 },
    { "cvt.l.w", 0x08001080 },
    { "cvt.s.l", 0x08001080 },
    { "cvt.d.l", 0x08001080 },
    { "cvt.e.l", 0x08001480 },
    { "cvt.w.l", 0x08001080 },
    { "cache", 0x1E4F8460 },
    { "cia", 0x04000000 },
    { "uld", 0x02000460 },
    { "usd", 0x02000460 },
    { "dabs", 0x08000420 },
    { "dneg", 0x08000420 },
    { "dnegu", 0x08000420 },
    { "dmul", 0x06000421 },
    { "dmulo", 0x06000421 },
    { "dmulou", 0x06000421 },
    { "drem", 0x06000421 },
    { "dremu", 0x06000421 },
    { "drol", 0x06000421 },
    { "dror", 0x06000421 },
    { "daddou", 0x06128421 },
    { "dsubou", 0x06138421 },
    { "ulwu", 0x02000460 },
    { "movt", 0x0600042C },
    { "movf", 0x0600042C },
    { "movn", 0x06000421 },
    { "movz", 0x06000421 },
    { "madd.s", 0x20001084 },
    { "madd.d", 0x20001084 },
    { "madd.e", 0x200018C6 },
    { "msub.s", 0x20001084 },
    { "msub.d", 0x20001084 },
    { "msub.e", 0x200018C6 },
    { "nmadd.s", 0x20001084 },
    { "nmadd.d", 0x20001084 },
    { "nmadd.e", 0x200018C6 },
    { "nmsub.s", 0x20001084 },
    { "nmsub.d", 0x20001084 },
    { "nmsub.e", 0x200018C6 },
    { "recip.s", 0x08001080 },
    { "recip.d", 0x08001080 },
    { "rsqrt.s", 0x08001080 },
    { "rsqrt.d", 0x08001080 },
    { "movt.s", 0x0600108C },
    { "movt.d", 0x0600108C },
    { "movf.s", 0x0600108C },
    { "movf.d", 0x0600108C },
    { "movn.s", 0x06001081 },
    { "movn.d", 0x06001081 },
    { "movz.s", 0x06001081 },
    { "movz.d", 0x06001081 },
    { "lwxc1", 0x22001021 },
    { "ldxc1", 0x22001021 },
    { "swxc1", 0x22001021 },
    { "sdxc1", 0x22001021 },
    { "prefx", 0x22000421 },
    { "dctr", 0 },
    { "dctw", 0 },
    { "tlbw", 0 },
    { "nada", 0 },
    { "ssnop", 0 },
    { "dsll32", 0x06140421 },
    { "dsrl32", 0x06148421 },
    { "dsra32", 0x06150421 },
    { "bc3f", 0x109F8000 },
    { "bc3t", 0x10A00000 },
    { "c3", 0x12A08000 },
    { "lwc3", 0x02A10460 },
    { "swc3", 0x02A18460 },
    { "mfc3", 0x08A204E0 },
    { "mtc3", 0x08A284E0 },
    { "cfc3", 0x08A304E0 },
    { "ctc3", 0x08A384E0 },
    { "sllv", 0x06028421 },
    { "srlv", 0x06030421 },
    { "srav", 0x06038421 },
    { "mfpc", 0x08A404E0 },
    { "mtpc", 0x08A404E0 },
    { "mfps", 0x08A404E0 },
    { "mtps", 0x08A404E0 },
    { "", 0 },
    { NULL, 0 },
};

extern struct {
    /* 0x000 */ char tokench; /* inferred */
    /* 0x001 */ char tstring[0x400];
    /* 0x404 */ int length;
} save;

// External declarations
extern int debugflag;
extern int CurrentFile;
extern int errno;
extern sym* hashtable[0x80];
extern sym* ophashtable[0x80];
extern int linelength;
extern int invent_locs;
extern int CurrentLine;
extern int printedline;
extern FILE* binasmfyle;
extern size_t binasm_count;
extern int in_repeat_block;
extern binasm_r binasm_rec;
extern FILE* in_file;
extern int nextinline;
extern int local_label[0x100];
extern char Tokench;
extern char Tstring[0x400];
extern char line[0x420];
extern size_t rep_size;
extern char token_tmp[0x100];
extern int Tstringlength;
// external declaration
extern struct {
    binasm_r* unk0;
    size_t unk4;
} rep_buffer;

// file declaration
//.data
int map_glevel[4] = { 2, 1, 0, 3 };
//.bss
static int B_1000A810;              //!< boolean, only used in readinline


extern void postcerror(char* error, int arg1);
extern void posterror(char* error, char* arg1, int arg2);
extern void ltoa(int arg0, char* arg1);
extern void new_error(void);
extern void* grow_array(size_t* capacity_count, size_t new_count, size_t width, void* ptr, int clear_mem);
extern int sym_enter(char* arg0, int arg1);
extern void assertion_failed(const char* assertion, const char* file, int file_line);

// Function declaration (as0util.c)
int hex_to_num(char c);
void make_local_label(char* name, size_t* out_len);
static int func_0041244C(void);
void unscan(char c);
void make_file(const char* filename);
static unsigned int func_0040F5D8(char* in, int is_signed);
static long long func_0040F77C(char* arg0, int arg1);
int hash(char* name);
int LookUp(char* name, sym** arg1);
int opLookUp(char* name, sym** arg1);
static void func_0040FB2C(void);
void consume(void);
static int func_0040FC20(int radix);
static void func_0040FD98(void);
static void func_004100C8(void);
static void func_004101AC(void);
static void func_00410270(char* arg0);
int dot_soon(int arg0);
void nexttoken(void);
static char func_00410E80(void);
void readinline(void);
sym* alloc_new_sym(void);
char* alloc_new_string(char* arg0);
void EnterSym(char* name, sym** arg1, int arg2);
sym* GetRegister(void);
static int func_00411898(void);
static long long func_00411B84(void);
static unsigned int func_00411ECC(void);
static long long func_0041213C(void);
static long long func_00412144(void);
static int func_0041244C(void);
static long long func_00412548(void);
int GetExpr(void);
int dw_GetExpr(unsigned int* high, unsigned int* low);
void GetBaseOrExpr(sym** arg0, int* arg1);
void GetItem(int* arg0, int* arg1);
void dw_GetItem(unsigned int* arg0, unsigned int* arg1, int* arg2);
void put_binasmfyle(void);

int hex_to_num(char c) {
    return tolower(c) - (isdigit(c) ? '0' - 0 : 'a' - '\n');
}

void make_local_label(char* name, size_t* out_len) {
    unsigned int i;   // sp+2C
    unsigned int num; // sp28
    size_t name_len;  // sp+24
    char last_c;      // sp+23
    size_t full_len;  // sp20

    name_len = strlen(name);
    if (strcmp(token_tmp, name) != 0) {
        strcpy(token_tmp, name);
    }

    i = atol(token_tmp);
    last_c = token_tmp[name_len - 1];

    if (i > 0xFF) {
        posterror("Local label number is out of range\0No such label", token_tmp, 1);
        i = 0;
    }

    ltoa(i, token_tmp);

    if (last_c == 'b') {
        num = local_label[i] - 1;
    } else if (last_c == 'f') {
        num = local_label[i];
    } else {
        num = local_label[i];
        if (local_label[i] >= 0x7FFFFFFF) {
            posterror("Too many local labels", token_tmp, 1);
        } else {
            local_label[i]++;
        }
    }

    full_len = strlen(token_tmp);
    token_tmp[full_len] = '$';
    full_len++;
    *out_len = full_len + 10;
    token_tmp[*out_len] = '\0';

    for (i = 10; i > 0; i--) {
        token_tmp[full_len + i - 1] = (num % 10) + '0';
        num /= 10;
    }
    if (strcmp(token_tmp, name) != 0) {
        strcpy(name, token_tmp);
    }
}

void unscan(char c) {
    save.tokench = Tokench;
    strcpy(save.tstring, Tstring);
    save.length = Tstringlength;
    Tokench = c;
}

void make_file(const char* file_name) {
    CurrentFile = st_filebegin(file_name, 3, 1, map_glevel[debugflag]);
}

static unsigned int func_0040F5D8(char* in, int is_signed) {
    unsigned int digit;
    unsigned int num;   // s2
    unsigned int ret;   // s4 // digit count/return
    unsigned int radix; // s5

    num = 0;

    // Determine radix and set digit to begin on
    if (in[0] == '0') {
        if ((in[1] == 'x') || (in[1] == 'X')) {
            radix = 16;
            ret = 2;
        } else {
            radix = 8;
            ret = 1;
        }
    } else {
        radix = 10;
        ret = 0;
    }

    if (1) {}

    while (in[ret] != '\0') {
        digit = hex_to_num(in[ret]);
        if ((((0x7FFFFFFF / radix) * 2) + 1 < num) || ((-1 - (num * radix)) < digit)) {
            posterror("Overflow", in, 1);
            return ret;
        }
        num = num * radix + digit;
        ret++;
    }

    if ((radix == 10) && (num & 0x80000000) && (num != 0x80000000)) {
        posterror("Large decimal set sign bit", in, 2);
    }

    ret = num;
    if (is_signed) {
        // INT32_MIN has no positive equivalent, every other representable number does
        if (num != 0x80000000) {
            ret = -num;
        }
    }

    return ret;
}

static long long func_0040F77C(char* arg0, int arg1) {
    long long var_v1;

    errno = 0;
    if (Tokench == 'h') {
        var_v1 = strtoull(arg0, NULL, 0x10);
    } else {
        var_v1 = strtoll(arg0, NULL, 0);
    }
    if (errno == '"') {
        posterror("Number out of range", arg0, 1);
    }
    if (arg1) {
        var_v1 = -var_v1;
    }
    return var_v1;
}

int hash(char* name) {
    int sp20;
    int var_a3;

    var_a3 = strlen(name);
    if (var_a3 <= 0) {
        assertion_failed("i > 0", "as0util.c", 229);
    }

    sp20 = (name[1] * 0xD) + (name[MIN(var_a3, 2)] * 0x11) + (name[MIN(var_a3, 3)] * 0xB) +
           (name[MAX(var_a3 - 2, 1)] * 3) + (name[MAX(var_a3 - 1, 1)] * 7) + (name[var_a3] * 0x13);

    return sp20 % 128;
}

int LookUp(char* name, sym** arg1) {
    sym* var_s0;

    *arg1 = NULL;
    for (var_s0 = hashtable[hash(name)]; var_s0 != NULL; var_s0 = var_s0->next) {
        if (strcmp(name, var_s0->name) == 0) {
            *arg1 = var_s0;
            return FOUND;
        }
    }
    return NOT_FOUND;
}

int opLookUp(char* name, sym** arg1) {
    sym* op;

    *arg1 = NULL;

    for (op = ophashtable[hash(name)]; op != NULL; op = op->next) {
        if (strcmp(name, op->name) == 0) {
            *arg1 = op;
            return FOUND;
        }
    }
    return NOT_FOUND;
}

static void func_0040FB2C(void) {
    if (linelength >= nextinline) {
        if (((isalpha(line[nextinline]))) || (line[nextinline] == 0x39)) {
            posterror("Badly delimited numeric literal", 0, 1);
        }
    }
}

void consume(void) {
    if (Tstringlength < 0x3FF) {
        token_tmp[Tstringlength] = line[nextinline];
    }
    Tstringlength++;
    nextinline++;
}

static int func_0040FC20(int radix) {
    int digit = 1;
    int first_inline = nextinline;

    while (digit && (nextinline <= linelength)) {
        char c = line[nextinline];

        if (isdigit(c)) {
            consume();
        } else if (isxdigit(c)) {
            if (radix == 10) {
                posterror("Hex digit in decimal literal", NULL, 1);
            }
            line[nextinline] = tolower(c);
            consume();
        } else {
            digit = 0;
        }
    }
    return first_inline < nextinline;
}

static void func_0040FD98(void) {
    int sp2C;  // sp+2C
    int pad28; // sp+28
    int radix; // sp+24

    Tokench = 'h';
    token_tmp[1] = 'x';
    Tstringlength = 2;
    nextinline++;

    sp2C = func_0040FC20(16);
    if ((linelength >= nextinline) && (line[nextinline] == '.')) {
        Tokench = 'f';
        consume();
        sp2C |= func_0040FC20(16);
    }
    if ((sp2C != 0) && (linelength >= nextinline)) {
        line[nextinline] = tolower(line[nextinline]);
        if ((line[nextinline]) == 'h') {
            Tokench = 'f';
            consume();
            if (linelength < nextinline) {
                sp2C = 0;
            } else {
                radix = 10;
                if (nextinline < linelength) {
                    line[nextinline + 1] = tolower(line[nextinline + 1]);
                    if ((line[nextinline] == '0') && (line[nextinline + 1] == 'x')) {
                        radix = 16;
                        consume();
                        consume();
                    }
                }
                if (radix == 10) {
                    if ((line[nextinline] == '+') || (line[nextinline] == '-')) {
                        consume();
                    }
                }
                sp2C = func_0040FC20(radix);
            }
        }
    }
    if (!sp2C) {
        posterror("Badly delimited hexadecimal literal", NULL, 1);
    } else {
        func_0040FB2C();
    }
    if ((Tokench == 'f') && (Tstringlength >= 0x400)) {
        posterror("Hex floating point literal too long", NULL, 1);
        Tstringlength = 0x3FF;
    }
}

static void func_004100C8(void) {

    Tokench = 'd';
    while ((nextinline < linelength) && (line[nextinline] >= '0') && (line[nextinline] < '9')) {
        consume();
    }
    func_0040FB2C();
}

static void func_004101AC(void) {
    while ((nextinline < linelength) && (line[nextinline] >= 0x30) && (line[nextinline] < 0x3A)) {
        consume();
    }
}

static void func_00410270(char* arg0) {
    if (Tstringlength >= 0x400) {
        Tstringlength = 0x3FF;
        posterror("Truncating token", arg0, 1);
    }
    arg0[Tstringlength] = 0;
}

int dot_soon(int arg0) {
    char c;

    for (; arg0 < linelength; arg0++) {
        c = line[arg0];
        if ((c == '.') || (c == 'e') || (c == 'E')) {
            return 1;
        }
        if (!isdigit(c)) {
            return 0;
        }
    }
    return 0;
}

void nexttoken(void) {
    int digits_left; // remaining digits in octal/hex escape code
    int num;         // numeric value of octal/hex escape code
    char c;
    int pad[3];
    int sp4C = 0;

    // check for a stored string and recall if present
    if (save.tokench != '\0') {
        Tokench = save.tokench;
        save.tokench = '\0';
        strcpy(Tstring, save.tstring);
        Tstringlength = save.length;
        return;
    }

    Tstringlength = 0;

    // skip spaces
    while ((nextinline < linelength) && (line[nextinline] == ' ')) {
        nextinline++;
    }

    // Terminate line in a comment
    if (nextinline >= linelength) {
        Tokench = '#';
        goto end;
    }

    // get next char
    c = line[nextinline];
    Tstringlength = 1;
    token_tmp[0] = c;
    nextinline++;

    switch (c) {
        // operators
        case '%':
        case '&':
        case '(':
        case ')':
        case '*':
        case '+':
        case ',':
        case '-':
        case '/':
        case ':':
        case ';':
        case '<':
        case '=':
        case '>':
        case '|':
        case '^':
        case '~':
            // special case for the compound operators "<<" and ">>"
            if (((c == '<') && (line[nextinline] == '<')) || ((c == '>') && (line[nextinline] == '>'))) {
                nextinline++;
            }
            Tokench = c;
            break;

        default:

            if (((c >= '1') && (c <= '9')) // unambiguously decimal digits
                || ((nextinline < linelength) &&
                    (((c == '.') && isdigit(line[nextinline])) || ((c == '0') && dot_soon(nextinline)))) // floats?
            ) {

                if (c == '.') { // floats that start with '.'?
                    Tokench = 'f';
                    consume();
                    func_004101AC();
                } else {
                    Tokench = 'd';
                    func_004101AC();

                    if (linelength < nextinline) {
                        break;
                    }

                    // local labels
                    if ((line[nextinline] == 'b') || (line[nextinline] == 'f')) {
                        consume();
                        Tokench = 'i';
                        func_00410270(token_tmp);
                        make_local_label(token_tmp, (size_t*)&Tstringlength); // TODO
                        func_0040FB2C();
                        break;
                    }

                    //
                    if ((line[nextinline] != '.') && (line[nextinline] != 'e') && (line[nextinline] != 'E')) {
                        func_0040FB2C();
                        break;
                    }

                    // floats?
                    Tokench = 'f';
                    if (line[nextinline] == '.') {
                        consume();
                        func_004101AC();
                    }
                }

                // expenents of floats
                if (nextinline < linelength) {
                    if ((line[nextinline] == 'e') || (line[nextinline] == 'E')) {
                        line[nextinline] = 'e';
                        consume();
                        if (nextinline < linelength) {
                            if ((line[nextinline] == '+') || (line[nextinline] == '-')) {
                                consume();
                            }
                        }
                        if (!(nextinline < linelength) || !isdigit(line[nextinline])) {
                            posterror("Missing exponent in floating-point literal", NULL, 1);
                            Tstringlength -= 1;
                            break;
                        }
                        func_004101AC();
                    }
                }

                func_0040FB2C();
                break;
            }

            // hex and octal
            if (c == '0') {
                sp4C = 1;
                if ((nextinline < linelength) && ((line[nextinline] == 'x') || (line[nextinline] == 'X'))) {
                    func_0040FD98();
                } else {
                    func_004100C8();
                }
                break;
            }

            // identifiers?
            if ((isalpha(c)) || (c == '.') || (c == '_') || (c == '$')) {
                Tokench = 'i';
                while ((nextinline < linelength)) {
                    c = line[nextinline];
                    if ((isalnum(c)) || (c == '.') || (c == '_') || (c == '$')) {
                        consume();
                        continue;
                    }
                    goto end;
                }
                break;
            }
            break;

        case '"':
            // strings
            Tokench = '"';
            Tstringlength = 0;
            while (nextinline < linelength) {
                c = line[nextinline];
                if (c == '"') {
                    nextinline++;
                    if (Tstringlength == 0) {
                        posterror("zero length string", NULL, 2);
                    }
                    goto end;
                }

                // hex and octal escape sequences
                if (c == '\\') {
                    nextinline++;
                    if (nextinline >= linelength) {
                        posterror("literal string not terminated", NULL, 1);
                        goto end;
                    }

                    c = line[nextinline];
                    switch (c) {
                        case 'a':
                            c = '\a';
                            break;
                        case 'b':
                            c = '\b';
                            break;
                        case 'f':
                            c = '\f';
                            break;
                        case 'n':
                            c = '\n';
                            break;
                        case 'r':
                            c = '\r';
                            break;
                        case 't':
                            c = '\t';
                            break;
                        case 'v':
                            c = '\v';
                            break;
                        case '\"':
                        case '\'':
                        case '\\':
                            break;

                        default:
                            if (((c >= '0') && (c <= '7')) || (c == 'x') || (c == 'X')) {
                                sp4C = 1;
                                num = 0;

                                if (((c >= '0') && (c <= '7'))) {
                                    // octal
                                    digits_left = 3;
                                    while (digits_left > 0) {
                                        num = num * 8 + c - '0';
                                        nextinline++;
                                        if (nextinline >= linelength) {
                                            posterror("literal string not terminated", NULL, 1);
                                            goto end;
                                        }
                                        c = line[nextinline];
                                        digits_left--;
                                        if (((c < '0') || (c > '7'))) {
                                            break;
                                        }
                                    }
                                } else {
                                    // hex
                                    nextinline++;
                                    c = line[nextinline];
                                    digits_left = 2;
                                    while (isxdigit(c) && (digits_left > 0)) {
                                        num = (num * 16) + hex_to_num(c);
                                        nextinline++;
                                        if (nextinline >= linelength) {
                                            posterror("literal string not terminated", NULL, 1);
                                            goto end;
                                        }
                                        c = line[nextinline];
                                        digits_left--;
                                    }
                                }

                                nextinline--;
                                if (num < 0x100) {
                                    c = num;
                                } else {
                                    posterror(" number in string too big", NULL, 1);
                                    goto end;
                                }
                            }
                            break;
                    }
                }

                if (Tstringlength < 0x3FF) {
                    token_tmp[Tstringlength] = c;
                }
                Tstringlength++;
                nextinline++;
            }

            if (Tstringlength > 0x3FF) {
                posterror("literal string too long", NULL, 1);
                Tstringlength = 0x3FF;
                break;
            }
            if (nextinline >= linelength) {
                posterror("Missing \" at end of string", NULL, 1);
                break;
            }
            break;
    }

end:
    if ((Tokench == 'i') || (Tokench == 'h') || (Tokench == 'd') || (Tokench == 'f') || (Tokench == '"')) {
        func_00410270(token_tmp);
        if (sp4C) {
            memcpy(Tstring, token_tmp, Tstringlength + 1);
        } else {
            strcpy(Tstring, token_tmp);
        }
    }
}

static char func_00410E80(void) {
    char c;
    int i;
    int line_number;
    char buf[BUF_COUNT]; // sp+44

    for (c = fgetc(in_file); (c == ' ') || (c == '\t'); c = fgetc(in_file)) {}

    if (c == 'l') {
        if (((char)fgetc(in_file) != 'i') || ((char)fgetc(in_file) != 'n') || ((char)fgetc(in_file) != 'e')) {
            posterror("Expected cpp-generated line number", NULL, 1);
            exit(1);
        }
        for (c = fgetc(in_file); (c == ' ') || (c == '\t'); c = fgetc(in_file)) {}
    }

    if (!(isdigit(c))) {
        posterror("Expected cpp-generated line number", NULL, 1);
        exit(1);
    }

    // convert line number's decimal digits into integer
    line_number = 0;
    do {
        line_number = (line_number * 10) + (c - '0');
        c = fgetc(in_file);
    } while (isdigit(c));

    while ((c == ' ') || (c == '\t')) {
        c = fgetc(in_file);
    }

    // Look for filename
    if (c != '"') {
        posterror("Expected cpp-generated file name", NULL, 1);
        return c;
    }

    c = fgetc(in_file);
    i = 0;
    while ((c != '"') && (c != ' ') && (c != '\n') && ((int)c != 0xFF)) { // eof
        if (i < BUF_COUNT - 1) {
            buf[i] = c;
        }
        i++;
        c = fgetc(in_file);
    }

    if (i >= BUF_COUNT) {
        buf[BUF_COUNT - 1] = '\0';
        posterror("Truncating cpp-generated filename", buf, 2);
    } else {
        buf[i] = '\0';
    }

    // Record line number and file
    CurrentLine = line_number - 2;
    if (invent_locs != 0) {
        make_file(buf);
    }

    return (c == '"') ? fgetc(in_file) : c;
}

void readinline(void) {
    char c; // sp+46F
    char prev_c;
    int found_eol; // sp+468
    int i;
    int pad;
    char buf[0x420]; // sp+40
    int var_t0;      // sp+3C // not in a character constant or an escaped character

    i = 0;
    prev_c = ' ';
    var_t0 = TRUE;
    found_eol = FALSE;
    printedline = FALSE;

    while (!found_eol) {
        c = fgetc(in_file);
        if ((c == '\t') || (c == '\f')) {
            c = ' ';
        } else if ((c == '"') && (prev_c != '\\')) {
            var_t0 = !var_t0;
        } else if ((c == '\n') || ((int)c == 0xFF)) {
            found_eol = TRUE;
        } else if (var_t0 && ((c == ';') || (c == '#'))) {
            found_eol = TRUE;
        }

        prev_c = c;
        if (!found_eol) {
            if (i < 0x41F) { // avoid out-of-bounds stack writes
                buf[i] = c;
            }
            i++;
        }
    }

    // cpp-generated line/file comments
    if ((c == '#') && (i == 0)) {
        c = func_00410E80();
    }

    if ((c == ';') || ((int)c == 0xFF)) {
        if (!B_1000A810) {
            CurrentLine++;
        }
        B_1000A810 = TRUE;
    } else {
        while ((c != '\n') && ((int)c != 0xFF)) {
            c = fgetc(in_file);
        }

        if ((invent_locs != 0) && !B_1000A810) {
            CurrentLine++;
        }
        B_1000A810 = FALSE;
    }

    if (i > 0x41F) {
        i = 0x41F;
        posterror("Line too long", NULL, 2);
    }

    buf[i] = '\0';
    strcpy(line, buf);
    linelength = i;

    // recurse if empty line
    if ((linelength == 0) && ((int)c != 0xFF)) {
        readinline();
    }
    nextinline = 0;
}

sym* alloc_new_sym(void) {
    sym* ptr;

    ptr = malloc(0x1C);

    if (ptr == NULL) {
        new_error();
    } else {
        memset(ptr, 0, 0x1C);
    }
    return ptr;
}

char* alloc_new_string(char* arg0) {
    int pad_20;
    char* sp20;

    sp20 = malloc(strlen(arg0) + 1);
    if (sp20 == NULL) {
        new_error();
    }
    strcpy(sp20, arg0);
    return sp20;
}

void EnterSym(char* name, sym** arg1, int arg2) {
    sym* sp2C;
    int sp28;

    if (LookUp(name, &sp2C) == 0) {
        sp28 = hash(name);
        sp2C = alloc_new_sym();
        sp2C->next = hashtable[sp28];

        sp2C->name = alloc_new_string(name);
        sp2C->unk10 = 3;
        sp2C->unk8 = 0;
        sp2C->reg = 0;
        sp2C->unk18 = sym_enter(name, arg2);

        hashtable[sp28] = sp2C;
    }
    if (sp2C->unk10 != 3) {
        posterror("Address symbol expected", &Tstring[0], 1);
    }
    *arg1 = sp2C;
}

sym* GetRegister(void) {
    sym* sp24;
    sym* sp20;

    sp20 = NULL;
    if (Tokench != 'i') {
        posterror("register expected", NULL, 1);
    } else if (LookUp(&Tstring[0], &sp24) == 0) {
        posterror("Undefined symbol", &Tstring[0], 1);
    } else if (sp24->unk10 != 0) {
        posterror("Register expected", &Tstring[0], 1);
    } else {
        sp20 = sp24;
    }
    nexttoken();
    if (Tokench == ',') {
        nexttoken();
    }
    return sp20;
}

static int func_00411898(void) {
    int minus; // sp+3C
    int not ;  //!< BOOL
    int sp34;  // sp+34
    sym* sp30; // sp+30
    int ret;   //!< BOOL

    sp34 = 0;
    minus = FALSE;
    not = FALSE;
    if (Tokench == '-') {
        minus = 1;
        nexttoken();
    } else if (Tokench == '+') {
        nexttoken();
    } else if (Tokench == '~') {
        not = 1;
        nexttoken();
    }

    switch (Tokench) {
        case '(':
            nexttoken();
            sp34 = func_0041244C();
            if (Tokench != ')') {
                posterror("Right paren expected", NULL, 1);
            }
            break;

        case 'i':
            if (LookUp(Tstring, &sp30) == 0) {
                posterror("undefined symbol in expression", NULL, 1);
            } else if (sp30->unk10 != 4) {
                posterror("Symbol must have absolute value", Tstring, 1);
            } else {
                sp34 = sp30->unk8;
            }
            break;

        case 'd':
        case 'h':
            sp34 = func_0040F5D8(Tstring, minus);
            minus = 0;
            break;

        case '"':
            minus = 0;
            sp34 = Tstring[0];
            if (Tstringlength >= 2) {
                posterror("String within expression may have only one character", Tstring, 1);
            }
            break;

        default:
            posterror("Invalid symbol in expression", NULL, 1);
            nexttoken();
            break;
    }
    if (minus) {
        ret = -sp34;
    } else if (not ) {
        ret = ~sp34;
    } else {
        ret = sp34;
    }
    nexttoken();
    return ret;
}

static long long func_00411B84(void) {
    int sp44;       // sp+44
    int sp40;       // sp+40
    long long sp38; // sp+38
    sym* sp34;      // sp+34
    long long ret;  // sp+28

    sp38 = 0;
    sp44 = 0;
    sp40 = 0;
    if (Tokench == '-') {
        sp44 = 1;
        nexttoken();
    } else if (Tokench == '+') {
        nexttoken();
    } else if (Tokench == '~') {
        sp40 = 1;
        nexttoken();
    }

    switch (Tokench) {
        case '(':
            nexttoken();
            sp38 = func_00412548();
            if (Tokench != ')') {
                posterror("Right paren expected", NULL, 1);
            }
            break;

        case 'i':
            if (!LookUp(Tstring, &sp34)) {
                posterror("undefined symbol in expression", NULL, 1);
            } else if (sp34->unk10 != 4) {
                posterror("Symbol must have absolute value", Tstring, 1);
            } else {
                sp38 = sp34->unk8;
            }
            break;

        case 'd':
        case 'h':
            sp38 = func_0040F77C(Tstring, sp44);
            sp44 = 0;
            break;

        case '"':
            sp38 = Tstring[0];
            sp44 = 0;
            if (Tstringlength >= 2) {
                posterror("String within expression may have only one character", Tstring, 1);
            }
            break;

        default:
            posterror("Invalid symbol in expression", NULL, 1);
            nexttoken();
            break;
    }

    if (sp44) {
        ret = -sp38;
    } else if (sp40) {
        ret = ~sp38;
    } else {
        ret = sp38;
    }
    nexttoken();
    return ret;
}

static unsigned int func_00411ECC(void) {
    char temp_s1;
    int temp_v0;
    int var_s2;
    int var_s0;

    var_s2 = func_00411898();

    while ((Tokench == '*') || (Tokench == '/') || (Tokench == '%') || (Tokench == '<') || (Tokench == '>') ||
           (Tokench == '^') || (Tokench == '&') || (Tokench == '|')) {
        var_s0 = var_s2;
        temp_s1 = Tokench;
        nexttoken();
        temp_v0 = func_00411898();
        switch (temp_s1) {
            case '*':
                var_s2 = var_s0 * temp_v0;
                break;
            case '/':
                var_s2 = var_s0 / temp_v0;
                break;
            case '%':
                var_s2 = var_s0 % temp_v0;
                break;
            case '<':
                var_s2 = var_s0 << temp_v0;
                break;
            case '>':
                var_s2 = (unsigned int)var_s0 >> temp_v0;
                break;
            case '^':
                var_s2 = var_s0 ^ temp_v0;
                break;
            case '&':
                var_s2 = var_s0 & temp_v0;
                break;
            case '|':
                var_s2 = var_s0 | temp_v0;
                break;
        }
    }
    return var_s2;
}

#ifdef _GNU_C
__attribute__((noreturn)) static long long func_0041213C(void) {}
#else
static long long func_0041213C(void) {} // The long long type is required to match
#endif

static long long func_00412144(void) {
    long long var_s2;
    long long var_s0;
    long long temp_v0;
    char temp_s1;

    var_s2 = func_00411B84();

    func_0041213C();

    while ((Tokench == '*') || (Tokench == '/') || (Tokench == '%') || (Tokench == '<') || (Tokench == '>') ||
           (Tokench == '^') || (Tokench == '&') || (Tokench == '|')) {
        var_s0 = var_s2;
        temp_s1 = Tokench;
        nexttoken();
        temp_v0 = func_00411B84();
        switch (temp_s1) {
            case '*':
                var_s2 = var_s0 * temp_v0;
                break;
            case '/':
                var_s2 = var_s0 / temp_v0;
                break;
            case '%':
                var_s2 = var_s0 % temp_v0;
                break;
            case '<':
                var_s2 = var_s0 << temp_v0;
                break;
            case '>':
                var_s2 = (unsigned long long)var_s0 >> temp_v0;
                break;
            case '^':
                var_s2 = var_s0 ^ temp_v0;
                break;
            case '&':
                var_s2 = var_s0 & temp_v0;
                break;
            case '|':
                var_s2 = var_s0 | temp_v0;
                break;
        }
    }
    return var_s2;
}

static int func_0041244C(void) {
    unsigned int var_s2 = func_00411ECC();

    while ((Tokench == '+') || (Tokench == '-')) {
        int var_s0 = var_s2;
        char temp_s1 = Tokench;
        int temp_v0;

        nexttoken();
        temp_v0 = func_00411ECC();
        switch (temp_s1) {
            case '+':
                var_s2 = var_s0 + temp_v0;
                break;
            case '-':
                var_s2 = var_s0 - temp_v0;
                break;
        }
    }

    return var_s2;
}

static long long func_00412548(void) {
    long long sp38;
    long long sp30;
    long long temp_v0;
    char temp_s0;

    sp38 = func_00412144();
    func_0041213C();

    while ((Tokench == '+') || (Tokench == '-')) {
        sp30 = sp38;
        temp_s0 = Tokench;

        nexttoken();
        temp_v0 = func_00412144();

        switch (temp_s0) {
            case '+':
                sp38 = sp30 + temp_v0;
                break;

            case '-':
                sp38 = sp30 - temp_v0;
                break;
        }
    }

    return sp38;
}

int GetExpr(void) {
    int sp24 = 0;

    if ((Tokench == 'i') || (Tokench == 'd') || (Tokench == 'h') || (Tokench == '+') || (Tokench == '-') ||
        (Tokench == '~') || (Tokench == '(') || ((Tokench == '"'))) {
        sp24 = func_0041244C();
        if (Tokench == ',') {
            nexttoken();
        }
    } else {
        posterror("Invalid symbol in expression", NULL, 1);
        nexttoken();
    }
    return sp24;
}

int dw_GetExpr(unsigned int* high, unsigned int* low) {
    unsigned long long val64;

    if ((Tokench == 'i') || (Tokench == 'd') || (Tokench == 'h') || (Tokench == '+') || (Tokench == '-') ||
        (Tokench == '~') || (Tokench == '(') || (Tokench == '"')) {
        val64 = func_00412548();
        func_0041213C();
        if (Tokench == ',') {
            nexttoken();
        }
    } else {
        posterror("Invalid symbol in expression", NULL, 1);
        nexttoken();
    }

    *high = val64 >> 0x20;
    *low = val64;

    return (*high != 0) && ((*high != 0xFFFFFFFF) || ((int)val64 >= 0));
    // This returns false when `0 <= S <= UINT32_MAX` or `INT32_MIN <= (s64)S <= -1`,
    // in other words, it returns true when `S` *cannot* be expressed as a 32-bit integer, of either type.
}

void GetBaseOrExpr(sym** arg0, int* arg1) {
    *arg0 = NULL;
    if (Tokench == '(') {
        nexttoken();
        if ((Tokench == 'i') && LookUp(&Tstring[0], arg0) && (*arg0)->unk10 == 0) {
            nexttoken();
            if (Tokench != ')') {
                posterror("Expected \")\" after base register", NULL, 1);
            }
            nexttoken();
            return;
        }
        unscan('(');
    }

    *arg1 = GetExpr();
}

void GetItem(int* arg0, int* arg1) {
    *arg0 = GetExpr();
    if (Tokench == ':') {
        nexttoken();
        *arg1 = GetExpr();
    } else {
        *arg1 = 1;
    }
}

void dw_GetItem(unsigned int* arg0, unsigned int* arg1, int* arg2) {
    dw_GetExpr(arg0, arg1);
    if (Tokench == ':') {
        nexttoken();
        *arg2 = GetExpr();
    } else {
        *arg2 = 1;
    }
}

void put_binasmfyle(void) {
    if (in_repeat_block) {
        size_t size = rep_size;

        if (size >= rep_buffer.unk4) {
            rep_buffer.unk0 = grow_array(&rep_buffer.unk4, size, 0x10, rep_buffer.unk0, 0);
        }
        rep_buffer.unk0[rep_size] = binasm_rec;
        rep_size++;
    } else {
        fwrite(&binasm_rec, sizeof(binasm_rec), 1, binasmfyle);
        memset(&binasm_rec, 0, sizeof(binasm_rec));
        binasm_count++;
    }
}
