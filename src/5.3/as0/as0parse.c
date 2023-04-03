/*
 * @file: as0parse.c
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"


typedef struct {
    s8 pad[0xC];
    u8 unkC;
}foo;

struct binasm {
/* 0x0 */ s32 unk0;
/* 0x4 */ char unk4;
/* 0x5 */ u8 unk5;
/* 0x8 */ s32 unk8;
/* 0xC */ s32 unkC;
};


struct sym {
/* 0x0 */ struct sym* next;
/* 0x4 */ s32 unk4;
/* 0x8 */ s32 unk8;
/* 0xC */ char unk_0C[4];
/* 0x10 */ s32 unk10;
/* 0x14 */ s32 unk14;
/* 0x18 */ s32 unk18;
};

//static void func_00404234(void);


static s32 B_1000A7F0; //.bss
static s32 B_1000A7F4; //.bss
static s32 D_10000024; //.data

foo *in_file;
s32 severity;
s32 verbose;
s32 warnexitflag;
u8 Tokench;
u8 Tstring[];
struct binasm binasm_rec;
s32 list_extsyms;
s32 CurrentFile;
s32 CurrentLine;
s32 Tstringlength;
s32 invent_locs;
s32 isStruct;
s32 mednat;
s32 printedline;
s32 StructOrg;
s32 isStruct;
s32 LastLabel;
s32 atflag;

// static void func_00405574(s32 arg0) {}
// static s32 func_0040CC44(u8** arg0, struct binasm* binasm_rec) {}
void func_00405574(s32 arg0);
void EnterSym(s32 arg0, struct sym** arg1, s32 arg2);
s32 LookUp(s32*, void**);
extern void func_004054E8(s32 arg0, u8* arg1);
void nexttoken();
s32 opLookUp(s8*, struct sym**);
void posterror(char*, char*, s32);
void put_binasmfyle();
s32 sym_define(s32, u32, s32);
void GetItem(s32 *arg0, s32 *arg1);
extern void Parsestmt(void);
s32 func_0040CC44(u8** arg0, struct binasm* binasm_rec);


#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00403F10.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00404008.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00404108.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_004041A8.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00404234.s")


s32 main() {
    func_00404234(); //static
    if (!(in_file->unkC & 0x10)) {
        do {
            readinline();
            Parsestmt();
        } while (!(in_file->unkC & 0x10));
    }
    if (verbose != 0) {
        fprintf(stderr, "\n");
    }
    if ((severity < 2) || ((warnexitflag != 0) && (severity < 3))) {
        exit(1);
    }
    do_dot_end(1);
    sym_finish(B_1000A7F0, B_1000A7F4);
    return 0;
}

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00404B80.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00405178.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_004054E8.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00405574.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_004055D4.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_004056DC.s")


//Parse the break operand
s32 func_00405884(void) {
    s32 val;
    s32 retval;

    val = GetExpr();                //Yes..
    if ((val < 0) || (retval = val, (val > 0x400-1))) {
        posterror("break operand out of range", NULL, 1);
        return retval = 0;
    } else {
        return retval;
    }
}


/*void func_004058F0(s32 arg0) {
    s32 sp34;
    s32 ret; //temp_t0
    s32 var_v1;

    if (arg0 != 0x1B) {
        if (arg0 == 0x198) {
            func_00405178(0, 2, 0, 0, 3, 0, 0);
            return;
        }
        if (arg0 == 0x199) {
            func_00405178(0, 0x4F, 0, 0, 4, 0x48, 1);
            return;
        }
        func_00405178(0, arg0, 0x48, 0x48, 2, 0x48, 0);
        return;
    }

    ret = func_00405884();

    var_v1 = (Tokench == 0x23) ? 0 : func_00405884();

    func_00405178(0, arg0, 0x48, 0x48, 0xD, 0x48, (var_v1 << 0xA) + ret);
}*/

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_004058F0.s")

void func_00405A80(s32* arg0, s32 *arg1) {
    if (Tokench == ':') {
        nexttoken();
        *arg1 = GetExpr();
        return;
    }
    if ((Tokench == '+') || (Tokench == '-')) {
        GetItem(arg0, arg1);
        return;
    }
    if ((Tokench != '#') && (Tokench != ',')) {
        posterror("ill-formed symbolic expression", NULL, 1);
    }
}


#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00405B54.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00405C28.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00405DE4.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00406034.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_004061F8.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00406340.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00406684.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00406728.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00406C48.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00406FE8.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00407334.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_004075CC.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_004076A0.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00407A20.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040848C.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_004085D8.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_004086EC.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_004088B8.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00408C80.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00409118.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_004092FC.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00409850.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00409B10.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00409ECC.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00409FD0.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040A044.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040A0D4.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040A160.s")

void func_0040A208(void) {
    s32 sp24;

    sp24 = GetExpr();
    GetExpr();
    if (sp24 != 3) {
        posterror("version stamp does not match", NULL, 2);
    }
}


#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040A280.s")

void func_0040A4B0(void) {
    if (LastLabel != 0) {
        func_00405574(0);
    }
    StructOrg = GetExpr();
    isStruct = 1;
    LastLabel = 0;
}


#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040A530.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040A5D4.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040A6B8.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040A79C.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040A958.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040AAD4.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040ADFC.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040AF00.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040B0F4.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040B340.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040B554.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040B5F0.s")

void func_0040B984(void) {
    struct sym* cur_symbol;
    s32 sp38;

    do {
        if (Tokench != 'i') {
            posterror("identifer expected", NULL, 1);
        } else {
            if (LookUp(&Tstring, &cur_symbol) == 0) {
                EnterSym(&Tstring, &cur_symbol, 1);
            }
            sym_define(cur_symbol->unk18, 0x22, 0);
            if (cur_symbol->unk10 == 3) {
                if (list_extsyms != 0) {
                    func_004054E8(cur_symbol->unk18, &Tstring);
                }
                binasm_rec.unk0 = (s32) cur_symbol->unk18;
                binasm_rec.unk5 = (u8) ((binasm_rec.unk5 & 0xFFC0) | 2);

                put_binasmfyle();
                sp38 = cur_symbol->unk18;
            } else {
                posterror("invalid symbol for .globl ", &Tstring, 1);
            }
        }

        if (Tokench != '#') {
            nexttoken();
        }

        if (Tokench == 'i') {
            if (opLookUp(&Tstring, &cur_symbol) == 0) {
                posterror("bad section name\0bad section name", NULL, 1);
            } else if (cur_symbol->unk10 == 2) {
                switch (cur_symbol->unk14) {                /* irregular */
                case 21:
                    sym_define(sp38, '#', 0);
                    break;
                case 10:
                    sym_define(sp38, 2, 0);
                    break;
                case 25:
                    sym_define(sp38, 0xD, 0);
                    break;
                case 26:
                    sym_define(sp38, 0xF, 0);
                    break;
                }
            }
            nexttoken();
        }
    } while (Tokench == ',');


}

void func_0040BC84(void) {
    struct sym* sp4C;
    struct sym* sp48;

    do {
        if (Tokench != 'i') {
            posterror("identifer expected", NULL, 1);
        } else {
            if (LookUp((s32* ) &Tstring, &sp4C) == 0) {
                EnterSym((s32) &Tstring, (struct sym** ) &sp4C, 1);
            }
            sym_define(sp4C->unk18, 0x22U, 0);
            if (sp4C->unk10 == 3) {
                binasm_rec.unk0 = sp4C->unk18;
                binasm_rec.unk5 = (binasm_rec.unk5 & 0xFFC0) | 0x12;
                nexttoken();
                if (Tokench == ',') {
                    nexttoken();
                }
                if (LookUp((s32* ) &Tstring, &sp48) == 0) {
                    EnterSym((s32) &Tstring, (struct sym** ) &sp48, 1);
                }
                if (sp48 != sp4C) {
                    binasm_rec.unk8 = sp48->unk18;
                } else {
                    binasm_rec.unk8 = 0;
                }
                put_binasmfyle();
            } else {
                posterror("invalid symbol for .globl ", (s8* ) &Tstring, 1);
            }
        }

        if (Tokench != '#') {
            nexttoken();
        }
    } while (Tokench == ',');
}


#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040BEBC.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040C048.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040C218.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040C2E0.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040C360.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040C3E0.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040C460.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040C4CC.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040C5E8.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040C66C.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040C830.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040C928.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040C9D0.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040CC44.s")


void func_0040CCCC(void) {
    s32 temp_v0;

    binasm_rec.unk0 = 0;
    binasm_rec.unk5 = (binasm_rec.unk5 & 0xFFC0) | 0x20;
    if (Tokench != 0x69) {
        posterror(".set option expected", NULL, 2);
    } else {
        temp_v0 = func_0040CC44(&Tstring, &binasm_rec);
        binasm_rec.unk8 = temp_v0;
        switch (temp_v0) {                          /* irregular */
        case 5:
            atflag = 1;
            break;
        case 6:
            atflag = 0;
            break;
        case 0:
            posterror("unknown option in .set", (s8* ) &Tstring, 2);
            break;
        }
        nexttoken();
    }
    put_binasmfyle();
}


#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040CDE4.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040CEB4.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040CF9C.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040D110.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040D284.s")

void Parsestmt(void) {
    char sp38[0x400];
    struct sym* cur_symbol;
    s32 temp_a0;
    s32 expression_eval;
    // s32 temp_v0;

    nexttoken();
    strcpy(sp38, Tstring);

    if (Tokench == '#') {
        return;
    }
    if (invent_locs != 0) {
        binasm_rec.unk0 = 0;
        binasm_rec.unk5 = (binasm_rec.unk5 & 0xFFC0) | 0x1C;
        binasm_rec.unk8 = CurrentFile;
        binasm_rec.unkC = CurrentLine;
        put_binasmfyle();
    }
    if (Tokench == 'd') {
        make_local_label(Tstring, &Tstringlength);
        strcpy(sp38, Tstring);
        nexttoken();
        if (Tokench != ':') {
            posterror("colon must follow a local label", NULL, 1);
            return;
        }
    } else if (Tokench != 'i') {
        posterror("malformed statement", NULL, 1);
        return;
    } else {
        nexttoken();
    }
    if (Tokench == '=') {
        func_004056DC(sp38);
        return;
    }
    if (Tokench == ':') {
        if (isStruct) {
            func_004055D4(sp38);
        } else {
            func_0040D284(sp38);
        }
        nexttoken();
        if (Tokench == '#') {
            return;
        }
        if (Tokench != 'i') {
            posterror("malformed statement", NULL, 1);
            return;
        }
        strcpy(sp38, Tstring);
        nexttoken();
    }
    if (opLookUp(sp38, &cur_symbol) == 0) {
        posterror("undefined assembler operation", sp38, 1);
        return;
    }
    // temp_v0 = cur_symbol->unk10;
    if (cur_symbol->unk10 == 2) {
        temp_a0 = cur_symbol->unk14;
        switch (temp_a0) {          /* switch 1 */
        case 0xA:                   /* switch 1 */
        case 0x15:                  /* switch 1 */
        case 0x19:                  /* switch 1 */
        case 0x1A:                  /* switch 1 */
            func_0040AF00();
            break;
        case 0x4:                   /* switch 1 */
            func_0040A5D4();
            break;
        case 0x5:                   /* switch 1 */
            func_0040A79C(0);
            break;
        case 0x6:                   /* switch 1 */
            func_0040A79C(1);
            break;
        case 0x7:                   /* switch 1 */
            func_0040A958();
            break;
        case 0x8:                   /* switch 1 */
            func_0040AAD4(8);
            break;
        case 0xD:                   /* switch 1 */
            func_0040B0F4(1);
            break;
        case 0xB:                   /* switch 1 */
            func_0040B0F4(2);
            break;
        case 0x2C:                  /* switch 1 */
            func_0040B0F4(4);
            break;
        case 0x2:                   /* switch 1 */
            func_0040B984();
            break;
        case 0x12:                  /* switch 1 */
            func_0040BC84();
            break;
        case 0xE:                   /* switch 1 */
            func_0040C048();
            break;
        case 0x9:                   /* switch 1 */
            func_0040AAD4(9);
            break;
        case 0x2D:                  /* switch 1 */
            func_0040AAD4(0x2D);
            break;
        case 0x2F:                  /* switch 1 */
            func_0040C9D0();
            break;
        case 0x20:                  /* switch 1 */
            func_0040CCCC();
            break;
        case 0x14:                  /* switch 1 */
            func_0040CEB4();
            break;
        case 0x16:                  /* switch 1 */
            func_0040CF9C();
            break;
        case 0x3B:                  /* switch 1 */
            func_00406034();
            break;
        case 0x18:                  /* switch 1 */
        case 0x1B:                  /* switch 1 */
        case 0x2E:                  /* switch 1 */
            func_0040B5F0();
            break;
        case 0x1D:                  /* switch 1 */
        case 0x1E:                  /* switch 1 */
        case 0x24:                  /* switch 1 */
            func_0040C830();
            break;
        case 0x1C:                  /* switch 1 */
            func_0040C218();
            break;
        case 0x25:                  /* switch 1 */
            func_0040C928();
            break;
        case 0x22:                  /* switch 1 */
            func_0040C66C(1, GetExpr(temp_a0));
            break;
        case '#':                  /* switch 1 */
            func_0040C66C(0, 0);
            break;
        case 0x28:                  /* switch 1 */
            posterror(".err directive encountered", NULL, 1);
            break;
        case 0x1:                   /* switch 1 */
            func_0040ADFC();
            break;
        case 0x26:                  /* switch 1 */
            func_0040C5E8(0x26);
            break;
        case 0x27:                  /* switch 1 */
            func_0040C5E8(0x27);
            break;
        case 0x34:                  /* switch 1 */
            func_0040A4B0();
            break;
        case 0x2B:                  /* switch 1 */
            func_0040A280();
            break;
        case '*':                  /* switch 1 */
            func_0040A208();
            break;
        case 0xC:                   /* switch 1 */
            func_0040B340();
            break;
        case 0x32:                  /* switch 1 */
            func_0040C360();
            break;
        case 0x33:                  /* switch 1 */
            func_0040C3E0();
            break;
        case 0x13:                  /* switch 1 */
            func_0040C2E0();
            break;
        case 0x30:                  /* switch 1 */
            func_0040CDE4(0x30);
            break;
        case 0x31:                  /* switch 1 */
            func_0040CDE4(0x31);
            break;
        case 0x35:                  /* switch 1 */
        case 0x36:                  /* switch 1 */
        case 0x37:                  /* switch 1 */
        case 0x38:                  /* switch 1 */
            func_0040C5E8(temp_a0);
            break;
        case '9':                  /* switch 1 */
            mednat != false ? func_0040A530() : assertion_failed("false", "as0parse.c", 3537);
            break;
        case ':':                  /* switch 1 */

        if (mednat != false) {
            binasm_rec.unk5 = (binasm_rec.unk5 & 0xFFC0) | ':';
            put_binasmfyle();
        } else {
            assertion_failed("false", "as0parse.c", 3545);
        }
            break;
        case '<':                  /* switch 1 */
            func_0040C460();
            break;
        case '=':                  /* switch 1 */
            func_0040C4CC();
            break;
        case 0x3:                   /* switch 1 */
            func_0040A044(3);
            break;
        case 0xF:                   /* switch 1 */
            func_0040A0D4();
            break;
        case 0x11:                  /* switch 1 */
            func_0040A044(0x11);
            break;
        case 0x10:                  /* switch 1 */
            func_0040D110();
            break;
        case 0x21:                  /* switch 1 */
            func_0040A160();
            break;
        default:                    /* switch 1 */
            assertion_failed("false", "as0parse.c", 3569);
            break;
        }
        if ((printedline == 0) && (Tokench != '#')) {
            posterror("stmt extends past logical end", NULL, 1);
        }
    } else if (cur_symbol->unk10 == 1) {

        expression_eval = cur_symbol->unk14;
        switch (cur_symbol->unk18) {          /* switch 2 */
        case 0:                     /* switch 2 */
            func_004058F0(expression_eval);
            break;
        case 5:                     /* switch 2 */
            func_00408C80(expression_eval);
            break;
        case 10:                    /* switch 2 */
            func_00409FD0(expression_eval);
            break;
        case 4:                     /* switch 2 */
            func_0040848C(expression_eval);
            break;
        case 3:                     /* switch 2 */
            func_00407A20(expression_eval);
            break;
        case 1:                     /* switch 2 */
            func_00406728(expression_eval);
            break;
        case 12:                    /* switch 2 */
            func_00406FE8(expression_eval);
            break;
        case 2:                     /* switch 2 */
            func_004076A0(expression_eval);
            break;
        case 11:                    /* switch 2 */
            func_004075CC(expression_eval);
            break;
        case 8:                     /* switch 2 */
            func_00409B10(expression_eval);
            break;
        case 7:                     /* switch 2 */
            func_00409850(expression_eval);
            break;
        case 6:                     /* switch 2 */
            func_004092FC(expression_eval);
            break;
        case 9:                     /* switch 2 */
            func_00409ECC(expression_eval);
            break;
        case 13:                    /* switch 2 */
            func_004088B8(expression_eval);
            break;
        case 15:                    /* switch 2 */
            func_00406C48(expression_eval);
            break;
        case 14:                    /* switch 2 */
            func_004061F8(expression_eval);
            break;
        case 16:                    /* switch 2 */
            func_004085D8(expression_eval);
            break;
        case 17:                    /* switch 2 */
            func_004086EC(expression_eval);
            break;
        default:                    /* switch 2 */
            assertion_failed("false", "as0parse.c", 3632);
            break;
        }
        if ((printedline == 0) && (Tokench != '#')) {
            posterror("stmt extends past logical end", NULL, 1);
        }
    } else {
        posterror("assembler op/directive expected", sp38, 1);
    }
}

void func_0040E180(s8* arg0, s32 arg1, s32 arg2) {
    s8 dest[0x100];

    sprintf(&dest, arg0, arg1);
    postcerror(&dest, arg2);
}


s32 sym_undefined(s32 arg0) {
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;

    st_sym_idn(arg0, &sp30, &sp2C, &sp34, &sp28);
    return sp30 == 0;
}

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040E230.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040E3F0.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040E554.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040E760.s")

void sym_init(s32 arg0) {
    st_cuinit();
    D_10000024 = arg0 != 0;
}

#pragma GLOBAL_ASM("asm/5.3/functions/as0/sym_finish.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/sym_define.s")


void st_feinit() {


}

void itoa(s32 arg0, s8* dest) {
    sprintf(dest, "%d", arg0);
}

