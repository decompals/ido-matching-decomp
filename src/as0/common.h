#include "stdio.h"
#include "binasm_rec.h"
#ifndef ASM_H
#define ASM_H

#define TRUE 1
#define FALSE 0

struct _struct_asm_info_0x8 {
    /* 0x0 */ char* name;
    /* 0x4 */ unsigned int unk4;
};

struct _struct_asm_info {
    /* 0x0 */ char* name;
    /* 0x4 */ unsigned unk4_FE : 7;
    /* 0x4 */ unsigned unk4_1FFFFFF_ : 0x19;
};

#define DECLARE_OPTIONS                                                                                                \
    /*  0x0 */ DECLARE_OPTION(EB), /*  0x1 */ DECLARE_OPTION(EL), /*  0x2 */ DECLARE_OPTION(G),                        \
        /*  0x3 */ DECLARE_OPTION(K), /*  0x4 */ DECLARE_OPTION(M), /*  0x5 */ DECLARE_OPTION(NR),                     \
        /*  0x6 */ DECLARE_OPTION(O), /*  0x7 */ DECLARE_OPTION(O0), /*  0x8 */ DECLARE_OPTION(O1),                    \
        /*  0x9 */ DECLARE_OPTION(O2), /*  0xA */ DECLARE_OPTION(O3), /*  0xB */ DECLARE_OPTION(O4),                   \
        /*  0xC */ DECLARE_OPTION(Olimit), /*  0xD */ DECLARE_OPTION(R), /*  0xE */ DECLARE_OPTION(RD),                \
        /*  0xF */ DECLARE_OPTION(T), /* 0x10 */ DECLARE_OPTION(e), /* 0x11 */ DECLARE_OPTION(fli),                    \
        /* 0x12 */ DECLARE_OPTION(f), /* 0x13 */ DECLARE_OPTION(f0), /* 0x14 */ DECLARE_OPTION(f1),                    \
        /* 0x15 */ DECLARE_OPTION(f2), /* 0x16 */ DECLARE_OPTION(f3), /* 0x17 */ DECLARE_OPTION(f4),                   \
        /* 0x18 */ DECLARE_OPTION(g), /* 0x19 */ DECLARE_OPTION(g0), /* 0x1A */ DECLARE_OPTION(g1),                    \
        /* 0x1B */ DECLARE_OPTION(g2), /* 0x1C */ DECLARE_OPTION(g3), /* 0x1D */ DECLARE_OPTION(l),                    \
        /* 0x1E */ DECLARE_OPTION(o), /* 0x1F */ DECLARE_OPTION(p), /* 0x20 */ DECLARE_OPTION(p0),                     \
        /* 0x21 */ DECLARE_OPTION(p1), /* 0x22 */ DECLARE_OPTION(p2), /* 0x23 */ DECLARE_OPTION(p3),                   \
        /* 0x24 */ DECLARE_OPTION(r), /* 0x25 */ DECLARE_OPTION(t), /* 0x26 */ DECLARE_OPTION(v),                      \
        /* 0x27 */ DECLARE_OPTION(w), /* 0x28 */ DECLARE_OPTION(w1), /* 0x29 */ DECLARE_OPTION(w2),                    \
        /* 0x2A */ DECLARE_OPTION(w3), /* 0x2B */ DECLARE_OPTION(no_const_opts),                                       \
        /* 0x2C */ DECLARE_OPTION(no_lui_opts), /* 0x2D */ DECLARE_OPTION(no_div_rem_opts),                            \
        /* 0x2E */ DECLARE_OPTION(no_at_compression), /* 0x2F */ DECLARE_OPTION(no_branch_target),                     \
        /* 0x30 */ DECLARE_OPTION(mips1), /* 0x31 */ DECLARE_OPTION(mips2), /* 0x32 */ DECLARE_OPTION(mips3),          \
        /* 0x33 */ DECLARE_OPTION(mips4), /* 0x34 */ DECLARE_OPTION(nopool), /* 0x35 */ DECLARE_OPTION(align8),        \
        /* 0x36 */ DECLARE_OPTION(align16), /* 0x37 */ DECLARE_OPTION(align32), /* 0x38 */ DECLARE_OPTION(align64),    \
        /* 0x39 */ DECLARE_OPTION(align_common), /* 0x3A */ DECLARE_OPTION(gp_warn),                                   \
        /* 0x3B */ DECLARE_OPTION(non_pic), /* 0x3C */ DECLARE_OPTION(r3000), /* 0x3D */ DECLARE_OPTION(r4000),        \
        /* 0x3E */ DECLARE_OPTION(r6000), /* 0x3F */ DECLARE_OPTION(r6000LHU), /* 0x40 */ DECLARE_OPTION(r6000LWL),    \
        /* 0x41 */ DECLARE_OPTION(trapuv), /* 0x42 */ DECLARE_OPTION(nopeep), /* 0x43 */ DECLARE_OPTION(peepdbg),      \
        /* 0x44 */ DECLARE_OPTION(noswpipe), /* 0x45 */ DECLARE_OPTION(swpdbg), /* 0x46 */ DECLARE_OPTION(nosymregs),  \
        /* 0x47 */ DECLARE_OPTION(noxbb), /* 0x48 */ DECLARE_OPTION(aggr_xbb), /* 0x49 */ DECLARE_OPTION(xbbdbg),      \
        /* 0x4A */ DECLARE_OPTION(newhilo), /* 0x4B */ DECLARE_OPTION(domtag), /* 0x4C */ DECLARE_OPTION(fpstall_nop), \
        /* 0x4D */ DECLARE_OPTION(noglobal), /* 0x4E */ DECLARE_OPTION(nobopt), /* 0x4F */ DECLARE_OPTION(dwalign),    \
        /* 0x50 */ DECLARE_OPTION(excpt), /* 0x51 */ DECLARE_OPTION(diag), /* 0x52 */ DECLARE_OPTION(mednat),          \
        /* 0x53 */ DECLARE_OPTION(dwopcode), /* 0x54 */ DECLARE_OPTION(64bit), /* 0x55 */ DECLARE_OPTION(fp32reg),     \
        /* 0x56 */ DECLARE_OPTION(extsyms), /* 0x57 */ DECLARE_OPTION(pic0), /* 0x58 */ DECLARE_OPTION(pic1),          \
        /* 0x59 */ DECLARE_OPTION(pic2), /* 0x5A */ DECLARE_OPTION(big_got), /* 0x5B */ DECLARE_OPTION(coff),          \
        /* 0x5C */ DECLARE_OPTION(elf), /* 0x5D */ DECLARE_OPTION(mscoff), /* 0x5E */ DECLARE_OPTION(mscoff1),         \
        /* 0x5F */ DECLARE_OPTION(multi_issue), /* 0x60 */ DECLARE_OPTION(nonzero_scnbase),                            \
        /* 0x61 */ DECLARE_OPTION(new_mdebug), /* 0x62 */ DECLARE_OPTION(abi), /* 0x63 */ DECLARE_OPTION(tfprev10),    \
        /* 0x64 */ DECLARE_OPTION(force_branch_fixup), /* 0x65 */ DECLARE_OPTION(r4200),                               \
        /* 0x66 */ DECLARE_OPTION(r4600), /* 0x67 */ DECLARE_OPTION(tfp), /* 0x68 */ DECLARE_OPTION(r4300_mul)

#define DECLARE_OPTION(name) OPTION_##name
typedef enum option_name { DECLARE_OPTIONS, OPTION_MAX } OPTION;
#undef DECLARE_OPTION

typedef enum mips_isa {
    /* 0 */ ISA_UNSPECIFIED,
    /* 1 */ ISA_MIPS1,
    /* 2 */ ISA_MIPS2,
    /* 3 */ ISA_MIPS3,
    /* 4 */ ISA_MIPS4
} mips_isa;

typedef struct sym {
    /* 0x0 */ struct sym* next;
    /* 0x4 */ char* name;
    /* 0x8 */ int unk8;
    /* 0xC */ struct sym* unkC;
    /* 0x10 */ int unk10;
    /* 0x14 */ int reg;
    /* 0x18 */ int unk18;
} sym;

#endif /* ASM_H */
