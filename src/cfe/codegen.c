#include "cmplrs/usys.h"
#include "cmplrs/ucode.h"
#include "common.h"

typedef struct UnkCodegen_Struct_s {
    TreeNode node;
    unsigned int unk18;
} UnkCodegen_Struct;

struct Uw_if {     /* output format for each type	*/
    int If_nbytes; /*  # of bytes to read (doesn't include opcode or val)*/
    int If_hasval; /*  if it has a value		*/
}; 

/* U-code output formats	*/
enum /*				*/
    Uw_otype {
        Uwof_init,   /* the init statement		*/
        Uwof_comm,   /* the comment statement	*/
        Uwof_lca,    /* the lca statement		*/
        Uwof_ldc,    /* the ldc statement		*/
        Uwof_normal, /* normal format of printf 	*/
                     /*	format and pointers	*/
        Uwof_undef   /* still working ones of this 	*/
                     /*	type			*/
    }; /*				*/
/*				*/
struct Uw_of {             /* output format for each type	*/
    enum Uw_otype Of_type; /*    the output format type to	*/
    /*		choose		*/
    int Of_nbytes;   /* number of bytes		*/
    int Of_hasval;   /* set if it has a constant	*/
    char *Of_format; /*    a "printf" style output	*/
    /*		format string	*/
}; /*				*/

typedef struct UnkStruct_RuntimeId_s {
    char pad[0x3C];
    int unk3C;
} UnkStruct_RuntimeId;

extern int Label_sufix;
extern struct Bcrec *Ucp;
extern char Uout_buff[];
extern struct Uw_of Uw_of[];
extern int addr_dtype;
extern FILE *Ucw_binout;

void UWRITE(void *ucode, int size) {
    if (debug_arr['U'] >= 3) {
        fprintf(dbgout, "writing ucode size=%d\n", size);
    }
    if (fwrite(ucode, 1, size, Ucw_binout) != (unsigned int) size) {
        error(0x50087, LEVEL_FATAL, -1, infile ? infile : "");
    }
}

// This match is just *wrong*
void UW_CONST_str(char *str) {
    size_t len; /* compiler-managed */

    if (strlen(str) >= Filenamelen + 1) {
        len = Filenamelen;
    } else {
        len = strlen(str);
    }
    UWRITE(&len, sizeof(len));
    len = (int) (len + 3) / 4;
    UWRITE(&len, sizeof(len));
    if ((len & 1) == 1) {
        len++;
    }
    UWRITE(str, len * 4);
}

void UW_CONST_m(int arg0, void *arg1) {
    int sp24; /* compiler-managed */

    UWRITE(&arg0, 4U);
    sp24 = (int) (arg0 + 3) / 4;
    UWRITE(&sp24, 4U);
    if ((sp24 & 1) == 1) {
        sp24 += 1;
    }
    sp24 *= 4;
    UWRITE(arg1, sp24);
}

void UW_CONST_s(int arg0, int arg1) {
    char filename[Filenamelen];
    unsigned int sp24;

    sprintf(filename, "%d", arg1);
    sp24 = strlen(filename);
    UWRITE(&sp24, 4U);
    sp24 = (int) (sp24 + 3) / 4;
    UWRITE(&sp24, 4U);
    if ((sp24 & 1) == 1) {
        sp24 += 1;
    }
    UWRITE(filename, sp24 * 4);
}

void UW_CONST_f(char *arg0, double arg2, int arg4) {
    char buf[1024];
    char *ptr;

    if (arg0 == NULL) {
        sprintf(buf, "%.16e", arg2);
        if (strncmp(buf, "inf", strlen("inf")) == 0) {
            error(0x3010C, LEVEL_WARNING, arg4, "infinity");
        } else if (strncmp(buf, "-inf", strlen("-inf")) == 0) {
            error(0x3010C, LEVEL_WARNING, arg4, "-infinity");
        }
        UW_CONST_str(buf);
        return;
    }
    ptr = arg0;
    while (*ptr != 0) {
        ptr++;
    }

    if ((arg0 < ptr)
        && (((ptr[-1] == 'F')) || (ptr[-1] == 'f') || (ptr[-1] == 'L') || (ptr[-1] == 'l'))) {
        ptr[-1] = '\0';
    }
    UW_CONST_str(arg0);
}

void UW_CONST_l(int arg0) {
    char buf[1024];

    sprintf(buf, "L%d", arg0);
    UW_CONST_str(buf);
}

void UW_CONST_i(int arg0) {
    union {
        long long l;
        int i;
    } sp20;

    sp20.i = arg0;
    UWRITE(&sp20, sizeof(sp20.l));
}

void UW_CONST_lli(long long arg0) {
    UWRITE(&arg0, sizeof(arg0));
}

enum Datatype U_DT(UnkCodegen_Struct *arg0) {
    switch (arg0->node.code) {
    case Array_type:
    case Struct_type:
        return Mdt;
    case Pointer_type:
        return addr_dtype;
    case Func_type:
        return Fdt;
    case Void_type:
    case Any_type:
        return Pdt;
    case Label_type:
        return Ndt;
    case Signed_type:
        __assert("FALSE", "codegen.c", 192);
        /* fallthrough */
    case Char_type:
    case Int_type:
    case Long_type:
    case Longlong_type:
    case Short_type:
    case Enum_type:
        if (arg0->unk18 >= 0x21) {
            return Idt;
        }
        return Jdt;
    case Unsigned_type:
        __assert("FALSE", "codegen.c", 210);
        /* fallthrough */
    case Uchar_type:
    case Uint_type:
    case Ulong_type:
    case Ulonglong_type:
    case Ushort_type:
        if (arg0->unk18 >= 0x21) {
            return Kdt;
        }
        return Ldt;
    case Double_type:
    case Longdouble_type:
    case Float_type:
        if (arg0->unk18 == 0x20) {
            return Rdt;
        }
        return Qdt;
    default:
        return __assert("FALSE", "codegen.c", 233);
    }
}


int init_codegen(char *arg0, FILE *arg1, int arg2) {
    UnkStruct_RuntimeId *temp_v0;

    Label_sufix = 0xA;
    if (arg1 != 0) {
        Ucw_binout = arg1;
    } else {
        Ucw_binout = stdout;
    }
    Ucp = (struct Bcrec*)Uout_buff;
    if (bit_size[9] == 0x40) {
        addr_dtype = Wdt;
    } else {
        addr_dtype = Adt;
    }
    Ucp->Opc = Ubgn;
    if (options[OPTION_ENDIANNESS] != 0) {
        Ucp->I1 = 0;
    } else {
        Ucp->I1 = 1;
    }
    Ucp->Uopcde.uiequ1.Length = 7;
    Ucp->Uopcde.uiequ1.offset = 10;

    Ucp = (struct Bcrec*)((char*)Ucp + Uw_of[Ucp->Opc].Of_nbytes);
    if ((char*)Ucp - (char*)&Uout_buff > 0x800) {
        UWRITE(Uout_buff, (char*)Ucp - (char*)Uout_buff);
        Ucp = (struct Bcrec*)Uout_buff;
    }
    
    Ucp->Opc = Uoptn;
    Ucp->I1 = 0;
    Ucp->Uopcde.uiequ1.Length = arg2;

    Ucp = (struct Bcrec*)((char*)Ucp + Uw_of[Ucp->Opc].Of_nbytes);
    if ((char*)Ucp - (char*)Uout_buff > 0x800) {
        UWRITE(Uout_buff, (char*)Ucp - (char*)Uout_buff);
        Ucp = (struct Bcrec*)Uout_buff;
    }
    
    Ucp->Opc = Ucomm;
    Ucp->Dtype = Mdt;

    Ucp = (struct Bcrec*)((char*)Ucp + Uw_of[Ucp->Opc].Of_nbytes);
    if ((char*)Ucp - (char*)Uout_buff > 0x800) {
        UWRITE(Uout_buff, (char*)Ucp - (char*)Uout_buff);
        Ucp = (struct Bcrec*)Uout_buff;
    }
    
    UWRITE(Uout_buff, (char*)Ucp - (char*)Uout_buff);
    Ucp = (struct Bcrec*)Uout_buff;

    UW_CONST_m((size_t) strlen(arg0) >= 1024 + 1 ? 1024 : strlen(arg0), arg0);
    if (options[OPTION_VERBOSITY] & VERBOSE_FLAG_8) {
        fprintf(stderr, "%s: ", myname);
        fflush(stderr);
    }
    if (options[OPTION_CHECKSTACK]) {
        temp_v0 = get_runtime_id("_RtlCheckStack", void_type, 0);
        if (temp_v0 != 0) {
            Ucp->Opc = 0x63;
            Ucp->I1 = 2;
            Ucp->Uopcde.uiequ1.Length = (int) temp_v0->unk3C;

            Ucp = (struct Bcrec*)((char*)Ucp + Uw_of[Ucp->Opc].Of_nbytes);
            if ((char*)Ucp - (char*)Uout_buff > 0x800) {
                UWRITE(Uout_buff, (char*)Ucp - (char*)Uout_buff);
                Ucp = (struct Bcrec*)Uout_buff;
            }
        }
    }
    return 1;
}

static void func_004628B0(void) {
    Ucp->Opc = Ustp;
    Ucp->I1 = 0;
    Ucp = (struct Bcrec*)((char*)Ucp + Uw_of[Ucp->Opc].Of_nbytes);
    if ((char*)Ucp - (char*)Uout_buff >= 0x801) {
        UWRITE(Uout_buff, (char*)Ucp - (char*)Uout_buff);
        Ucp = (struct Bcrec *) Uout_buff;
    }
    UWRITE(Uout_buff, (char*)Ucp - (char*)Uout_buff);
    Ucp = (struct Bcrec *) Uout_buff;
}


#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/uw_init.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_00463488.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_00463894.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_00464D18.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_00464F1C.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_0046508C.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/LDC_integer.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_00465654.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_00465D90.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_00466804.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_00468244.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_004688C8.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_0046A1D8.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/codegen.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_0046ACAC.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_0046ACB4.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_0046AEC0.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_0046AF34.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_0046B038.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_0046B094.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/func_0046B13C.s")

#pragma GLOBAL_ASM("asm/7.1/functions/cfe/codegen/Set_Small_Data_Upper_Limit.s")
