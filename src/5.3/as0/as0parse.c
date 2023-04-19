/*
 * @file: as0parse.c
 *
 * */

#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "as0/types.h"
#include "as0/arrays.h" //better
#include "as0/opt.h"
#include "as0/protos.h"
#include "sym.h"
#include "stsupport.h"
#include "cmplrs/stext.h"
#include "cmplrs/binasm.h"


typedef struct {
    s8 pad[0xC];
    u8 unkC;
}foo;


struct unk_00405574 {
/* 0x0 */ char unk0[8];
/* 0x8 */ s32 unk8;
/* 0xC */ s32 unkC;
};

//static void func_00404234(void);

static char* B_1000A7F0;
static char* B_1000A7F4;
static char* B_1000A7F8;

static s32 D_10000024; //.data
static const char* D_10000004[4] = {"", "operand 1", "operand 2", "operand 3"}; //lol?
static s32* D_10000014;
static s32 D_10000020;

#define true 1
#define false 0


s32 severity;
s32 verbose;
s32 warnexitflag;
u8 Tokench;
char Tstring[0x100];
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
s32 atflag;
s32 CurrentSegment;
s32 binasm_count;

FILE* extsyms_file;
sym *hashtable[0x100]; //default
s32 gform_extn;
s32 ophashtable[0x100];
s32 freg4;
s32 in_repeat_block;
u32 rep_count;
u32 rep_size;
s32 gp_warn;

static char* assembler_file;
s32 CurrentFile;
s32 CurrentLine;
s32 CurrentSegment;
s32 LastLabel;
s32 atflag;
s32 binasm_count;

FILE* binasmfyle;
s32 debugflag;
s32 diag_flag;
FILE* extsyms_file;
s32 gp_warn;
FILE* in_file;
s32 in_repeat_block;
s32 invent_locs;
s32 isStruct;
char isa;
s32 linelength;
s32 local_label[0x100];
s32 mednat;
s32 nowarnflag;
sym *reg_ptr[0x48];
s32 severity;
static char *sframereg = "$framereg";
static char *sframesize = "$framesize";
s32 shftaddr;

struct binasm binasm_rec;

// static void func_00405574(s32 arg0) {}
// static s32 func_0040CC44(u8** arg0, struct binasm* binasm_rec) {}

extern void sym_finish(char* arg0, char* arg1);


static void func_00403F10(void) {
    struct _struct_asm_info* var_s2;
    s32 operand_hash;
    s32 index;
    char* name;
    sym* cur_symbol;

    for (index = 0, var_s2 = asm_info; index < 0x1AE; index++, var_s2++) {
       name = var_s2->name;
        if (name[0] != '\0') {
            operand_hash = hash(name);
            cur_symbol = alloc_new_sym();

            cur_symbol->next = ophashtable[operand_hash];
            cur_symbol->name = name;
            cur_symbol->unkC = 0;
            cur_symbol->unk8 = 0;
            cur_symbol->unk10 = 1;
            cur_symbol->unk14 = index;

            cur_symbol->unk18 = var_s2->unk4_FE;

            ophashtable[operand_hash] = cur_symbol;
        }
    }
}

static void func_00404008(void) {
    s32 directives_hash;
    s32 index;
    u8* asm_directives;
    sym* cur_symbol;


    for(index = 0 ; index < 0x3F ; index++) {
        if (*sitype[index] == 0x2E) {
            asm_directives = sitype[index];
            directives_hash = hash(asm_directives); //create a hash for each asm directive
            cur_symbol = alloc_new_sym();

            cur_symbol->next =  ophashtable[directives_hash];
            cur_symbol->name = asm_directives;
            cur_symbol->unkC = 0;
            cur_symbol->unk8 = -1;
            cur_symbol->unk10 = 2;
            cur_symbol->unk14 = index;

            ophashtable[directives_hash] = cur_symbol;
        }
    }
}

static int func_00404108(int arg0, char* name, int arg2) {
    sym* temp_v0;
    s32 sp20;

    sp20 = hash(name);
    temp_v0 = alloc_new_sym();

    temp_v0->next = hashtable[sp20];
    temp_v0->name = name;
    temp_v0->unkC = 0;
    temp_v0->unk10 = 0;
    temp_v0->unk8 = arg2;
    temp_v0->unk14 = arg0;

    hashtable[sp20] = temp_v0;
}

static void func_004041A8(char* arg0, s32 arg1) {
    s32 stackPad;
    s32 sp20;
    sym* cur_symbol;


    sp20 = hash(arg0);
    cur_symbol = alloc_new_sym();

    cur_symbol->next = hashtable[sp20];
    cur_symbol->name = arg0;
    cur_symbol->unkC = 0;
    cur_symbol->unk10 = 4;
    cur_symbol->unk8 = arg1;
    hashtable[sp20] = cur_symbol;
}

static void func_00404234(int argc, char** argv) {
    s32 j;
    s32 i;
    s32 k;
    s32 var_s3 = 1;

    assembler_file = NULL;
    B_1000A7F0 = "binasm";
    B_1000A7F4 = NULL;
    B_1000A7F8 = NULL;
    list_extsyms = 0;
    CurrentSegment = 1;
    CurrentLine = 0;
    CurrentFile = EOF;
    linelength = 0;
    severity = 4;
    verbose = 0;
    atflag = 1;
    debugflag = false;
    isStruct = false;
    LastLabel = 0;
    in_repeat_block = 0;
    invent_locs = 1;
    gp_warn = 0;
    mednat = 0;


    for (i = 1; i < argc; i++) {
        char* temp_a1 = argv[i];

        if (*temp_a1 == '-') {
            switch (which_opt(temp_a1)) {
                case OPTION_g0:
                    debugflag = 0;
                    break;

                case OPTION_g1:
                    debugflag = 1;
                    break;

                case OPTION_g:
                case OPTION_g2:
                    debugflag = 2;
                    break;

                case OPTION_g3:
                    debugflag = 3;
                    break;

                case OPTION_p0:
                    var_s3 = 0;
                    break;

                case OPTION_p1:
                    var_s3 = 1;
                    break;

                case OPTION_p:
                case OPTION_p2:
                    var_s3 = 2;
                    break;

                case OPTION_p3:
                    var_s3 = 3;
                    break;

                case OPTION_w:
                case OPTION_w1:
                    nowarnflag = 1;
                    warnexitflag = 0;
                    break;

                case OPTION_w2:
                    nowarnflag = 0;
                    warnexitflag = 1;
                    break;

                case OPTION_w3:
                    nowarnflag = 1;
                    warnexitflag = 1;
                    break;

                case OPTION_v:
                    verbose = 1;
                    fprintf(stderr, "as0: ");
                    fflush(stderr);
                    break;

                case OPTION_t:
                    i++;
                    B_1000A7F4 = argv[i];
                    break;

                case OPTION_extsyms:
                    i++;
                    B_1000A7F8 = argv[i];
                    list_extsyms = 1;
                    break;

                // Ignore these options. They take an argument so increment again.
                case OPTION_G:
                case OPTION_Olimit:
                case OPTION_swpdbg:
                case OPTION_xbbdbg:
                case OPTION_multi_issue:
                    i++;
                    break;

                case OPTION_o:
                    i++;
                    B_1000A7F0 = argv[i];
                    break;

                case OPTION_gp_warn:
                    gp_warn = 1;
                    break;

                case OPTION_MAX:
                    posterror("Unknown option", temp_a1, 2);
                    break;

                case OPTION_mips1:
                    isa = ISA_MIPS1;
                    break;

                case OPTION_mips2:
                    isa = ISA_MIPS2;
                    break;

                case OPTION_mips3:
                    isa = ISA_MIPS3;
                    break;

                case OPTION_mips4:
                    isa = ISA_MIPS4;
                    break;

                case OPTION_mednat:
                    mednat = 1;
                    break;

                case OPTION_diag:
                    diag_flag = 1;
                    break;

                default:
                    break;
            }
        } else if (assembler_file == NULL) {
            assembler_file = argv[i];
        } else {
            posterror("Extra filename on command line", argv[i], 2);
        }
    }
    if (isa == ISA_UNSPECIFIED) { //Default isa.
        isa = ISA_MIPS1;
    }
    if (var_s3 >= 2) {
        debugflag = 2;
    }

    if ((binasmfyle = fopen(B_1000A7F0, "w")) == NULL) {
        call_perror(1, B_1000A7F0);
        exit(1);
    }
    binasm_count = 1;
    if (list_extsyms) {
        if ((B_1000A7F8 == NULL) || ((extsyms_file = fopen(B_1000A7F8, "w")) == NULL)) {
            call_perror(1, B_1000A7F8);
            exit(1);
        }
    }
    binasm_rec.unk5_003F = 0x2A;
    binasm_rec.unk0 = 0;
    binasm_rec.unk8 = 3;
    binasm_rec.opt = 0x13;
    put_binasmfyle();
    sym_init(debugflag);

    if (assembler_file != NULL) {
        if ((in_file = fopen(assembler_file, "r")) == NULL) {
            call_perror(1, assembler_file);
            exit(1);
        }
    } else {
        in_file = stdin;
    }
    if (fgetc(in_file) != '#') {
        make_file(assembler_file);
    }
    fseek(in_file, 0, 0);

    for (j = 0; j < 0x20; j++) {
        reg_ptr[j] = func_00404108(j, sregisters[j], j);
    }
    for (j = 0x20; j < 0x40; j++) {
        func_00404108(j, sregisters[j], j - 0x20);
    }
    for (j = 0x40; j < 0x48 ; j++) {
        func_00404108(j, sregisters[j], j - 0x40);
    }

    //Special operands
    func_00404108(1, "$at", 1);
    func_00404108(0x1A, "$kt0", 0x1B);
    func_00404108(0x1B, "$kt1", 0x1C);
    func_00404108(0x1C, "$gp", 0x1D);
    func_00404108(0x1D, "$sp", 0x1E);
    func_00404108(0x1E, "$fp", 0x1F);
    func_00404108(0x1D, sframereg, 0x1D);
    func_004041A8(sframesize, 0);
    func_00404008();
    func_00403F10();

    for (k = 0; k < 0x100; k++) { \
        local_label[k] = 0;       \
    }
}


int main(int argc, char** arg1) {
    func_00404234(argc, arg1);
    while (!feof(in_file)) {

            readinline();
            Parsestmt();
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

#define UNK_FLAG 1


static void func_00404B80(s32 arg0, s32 arg1, s32 arg2) {
    u32 expression; //could be

    switch (arg0) {                                 /* switch 1; irregular */
    default:                                        /* switch 1 */
    case 1:                                         /* switch 1 */
        expression = asm_info[arg2].unk4 << 0x11  >> 0x1B;
        break;
    case 2:                                         /* switch 1 */
        expression = asm_info[arg2].unk4 << 0x16 >> 0x1B;
        break;
    case 3:                                         /* switch 1 */
        expression = asm_info[arg2].unk4 & 0x1F;
        break;
    }
    switch (expression) {
    case 0: break;
    case 1:
        if ((atflag != 0) && (arg1 == 1)) {
            posterror("Used $at without .set noat", D_10000004[arg0], 2);
        } else if ((arg1 < 0) || (arg1 >= 0x20)) {
            posterror("Should be gp register", D_10000004[arg0], 1);
        }
        break;
    case 2:
        if ((isa < ISA_MIPS3) && ((arg1 < 0) || (arg1 >= 0x20) || (arg1 & UNK_FLAG))) {
            posterror("Should be even gp register", D_10000004[arg0], 1);
        }
        break;
    case 3:
        if (((arg1 < 0) || (arg1 >= 0x20)) && (arg1 != 0x48)) {
            posterror("Should be gp register", D_10000004[arg0], 1);
        } else if (atflag != 0) {
            if (arg1 == 1) {
                posterror("Used $at without .set noat", D_10000004[arg0], 2);
            }
        }
        break;
    case 7:
        if ((arg1 < 0) || (arg1 >= 0x20)) {
            posterror("Should be coprocessor register", D_10000004[arg0], 1);
        }
        break;
    case 8:
        if ((isa < ISA_MIPS3) && ((arg1 < 0) || (arg1 >= 0x20) || (arg1 & UNK_FLAG))) {
            posterror("Should be even coprocessor register", D_10000004[arg0], 1);
        }
        break;
    case 4:
        if ((arg1 < 0x20) || (arg1 >= 0x40)) {
            posterror("Should be floating point register", D_10000004[arg0], 1);
        }
        break;
    case 5:
        if (isa < ISA_MIPS3) {
            if ((arg1 < 0x20) || (arg1 >= 0x40) || (arg1 & UNK_FLAG)) {
                posterror("Should be even floating point register", D_10000004[arg0], 1);
            }
        }
        break;
    case 6:
        if (isa >= ISA_MIPS3) {
            if ((arg1 < 0x20) || (arg1 >= 0x40) || (arg1 & UNK_FLAG)) {
                posterror("Should be even floating point register", D_10000004[arg0], 1);
            }
        } else if ((arg1 < 0x20) || (arg1 >= 0x40) || (arg1 & 3)) {
            posterror("Should be multiple-of-4 floating point register", D_10000004[arg0], 1);
        }
        break;
    case 9:
        if ((isa < ISA_MIPS3) && (arg1 >= 0x20) && (arg1 & UNK_FLAG)) {
            posterror("Should be fp double or gp single register", D_10000004[arg0], 1);
        }
        break;
    case 10:
        if (isa < ISA_MIPS3) {
            if (arg1 & UNK_FLAG) {
                posterror("Should be multiple-of-2 register", D_10000004[arg0], 1);
            }
        }
        break;
    case 11:
        if (isa >= 3) {
            if (arg1 & UNK_FLAG) {
                posterror("Should be multiple-of-2 register", D_10000004[arg0], 1);
            }
        } else if (arg1 & 3) {
            posterror("Should be multiple-of-4 register", D_10000004[arg0], 1);
        }
        break;
    case 12:
        if ((arg1 < 0x40) || (arg1 >= 0x48)) {
            posterror("Should be floating point condition code register", D_10000004[arg0], 1);
        }
        break;
    }
}

static void func_00405178(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u32 arg4, s32 arg5, u32 arg6) {
    binasm_rec.unk0 = arg0;
    binasm_rec.unk5_003F = 0x17;
    binasm_rec.unk6_03FE = arg1;
    binasm_rec.unk8_FE = arg2;
    binasm_rec.unk8_01FC = arg3;
    binasm_rec.unk8_0003C000 = arg4;
    binasm_rec.unk4_01C0 = gform_extn;
    if (gform_extn != 0) {
        binasm_rec.opt = arg6;
    }

    switch (arg4) {
        case 15:
            binasm_rec.unkB_007F = freg4;
            func_00404B80(3, freg4, arg1);
            /* fallthrough */
        case 3:
            binasm_rec.unkA_3F80 = arg5;
            func_00404B80(1, arg2, arg1);
            func_00404B80(2, arg3, arg1);
            func_00404B80(3, arg5, arg1);
            break;

        case 6:
            binasm_rec.opt = arg6;
            break;

        case 2:
            if (arg2 != 0x48) {
                func_00404B80(1, arg2, arg1);
            }
            binasm_rec.opt = arg6;
            break;

        case 14:
            if (arg3 != 0x48) {
                func_00404B80(2, arg3, arg1);
            }
            binasm_rec.opt = arg6;
            break;

        case 0:
        case 1:
        case 4:
            func_00404B80(1, arg2, arg1);
            func_00404B80(2, arg3, arg1);
            binasm_rec.opt = arg6;
            break;

        case 12:
            func_00404B80(1, arg2, arg1);
            binasm_rec.opt = arg6;
            break;

        case 7:
        case 9:
            func_00404B80(1, arg2, arg1);
            break;

        case 5:
        case 8:
            func_00404B80(1, arg2, arg1);
            func_00404B80(2, arg3, arg1);
            break;

        case 13:
            binasm_rec.opt = arg6;
            break;

        case 10:
        case 11:
            break;

        default:
            assertion_failed("false", "as0parse.c", 237);
            break;
    }
    put_binasmfyle();
}


static void func_004054E8(sym *arg0, u8* arg1) {
    u8* var_a2;

    fprintf(extsyms_file, "%1d %1d", binasm_count, arg0);

    if (arg1 != NULL) {
        var_a2 = arg1;
    } else {
        var_a2 = "";
    }

    fprintf(extsyms_file, " %s\n", var_a2);
}


void func_00405574(s32 arg0) {
    struct unk_00405574* var_v0;

    StructOrg = ((((s32)StructOrg + (1 << arg0)) - 1) >> arg0) << arg0;

    for (var_v0 = LastLabel; var_v0 != NULL; var_v0 = var_v0->unkC) {
        var_v0->unk8 = StructOrg;
    }
    LastLabel = NULL;
}

static void func_004055D4(s8* symbol_name) {
    sym* cur_symbol;
    s32 hash_sym;

    if (LookUp(symbol_name, &cur_symbol) != 0) {
        posterror("can not redefine symbol", symbol_name, 2);
        return;
    }
    hash_sym = hash(symbol_name);
    cur_symbol = alloc_new_sym();


    cur_symbol->next = hashtable[hash_sym];
    cur_symbol->name = alloc_new_string(symbol_name);
    cur_symbol->unkC = LastLabel;
    LastLabel = cur_symbol;
    cur_symbol->unk10 = 4;
    cur_symbol->unk8 = 0;
    hashtable[hash_sym] = cur_symbol;
}

static void func_004056DC(char* arg0) {
    sym* sp2C;
    s32 sp28;
    s32 sp24 = LookUp(arg0, &sp2C);

    if (sp24 == 0) {
        sp28 = hash(arg0);
        sp2C =  alloc_new_sym();

        sp2C->next = hashtable[sp28];
        sp2C->name = alloc_new_string(arg0);
        sp2C->unk10 = 4;
        sp2C->unk14 = 1;
        sp2C->unk18 = sym_enter(arg0, 0);
        hashtable[sp28] = sp2C;
    }
    sp2C->unkC = 0;
    sp2C->unk10 = 4;
    nexttoken();
    sp2C->unk8 = GetExpr();
    sym_define(sp2C->unk18, 5U, sp2C->unk8);
    if (sp24 != 0) {
        binasm_rec.unk0 = sp2C->unk18;
        binasm_rec.unk5_003F = 0x29;
        binasm_rec.unk8 = sp2C->unk8;
        put_binasmfyle();
    }
}


//Parse the break operand
static s32 func_00405884(void) {
    s32 val;
    s32 retval;

    val = GetExpr();                //Yes..
    if ((val < 0) || (retval = val, (val > 0x400-1))) {
        posterror("break operand out of range", NULL, 1);
        return retval = false;
    } else {
        return retval;
    }
}

static void func_004058F0(s32 arg0) {
    s32 sp34;
    // s32 temp_t0;
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
    sp34 = func_00405884();
    if (Tokench == '#') {
        var_v1 = 0;
    } else {
        // sp34 = temp_t0;
        var_v1 = func_00405884();
    }
    func_00405178(0, arg0, 0x48, 0x48, 0xD, 0x48, (var_v1 << 0xA) + sp34);
}

static void func_00405A80(s32* arg0, s32 *arg1) {
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


static void func_00405B54(u32 arg0, u32 arg1, s32 *arg2) {
    if (Tokench == ':') {
        nexttoken();
        *arg2 = GetExpr();
        return;
    }
    if ((Tokench == '+') || (Tokench == '-')) {
        dw_GetItem(arg0, arg1, arg2);
        return;
    }
    if ((Tokench != '#') && (Tokench != ',')) {
        posterror("ill-formed symbolic expression", NULL, 1);
    }
}


#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00405C28.s")

static s32 func_00405DE4(s32* arg0, s32 arg1, s32 arg2, s32* arg3) {
    sym* sp2C;

    if (Tokench == 'i') {
        if (!LookUp(Tstring, &sp2C)) {
            EnterSym(Tstring, &sp2C, 1);
        }

        if (sp2C->unk10 == 4) {
            dw_GetItem(arg1, arg2, arg3);
        } else if (sp2C->unk10 == 3) {
            *arg0 = sp2C->unk18;
            nexttoken();
            func_00405B54(arg1, arg2, arg3);
        } else {
            posterror("Bad id in expression", NULL, 1);
            nexttoken();
            return 0;
        }
    } else {
        if (Tokench == '"') {
            func_00405C28(Tstring, strlen(Tstring), arg1, arg2);
            nexttoken();
        } else {
            dw_GetExpr(arg1, arg2);
        }

        if (Tokench == ':') {
            nexttoken();
            *arg3 = GetExpr();
        } else {
            *arg3 = 1;
        }
    }
    if (Tokench == ',') {
        nexttoken();
    }
    return 1;
}


static void func_00406034(void) {
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 var_v1;

    if (LastLabel != 0) {
        func_00405574(2);
    }
    while(true) {
    sp4C = 0;
    sp48 = 0;
    sp50 = 1;
    sp54 = 0;
    if (func_00405DE4(&sp54, &sp4C, &sp48, &sp50) == 0) {

         break;
    }
        if (isStruct) {
            if (sp50 * 4 < 4) {
                var_v1 = 4;
            } else {
                var_v1 = sp50 * 4;
            }
            StructOrg = var_v1 + StructOrg;
        } else {
            binasm_rec.unk0 = sp54;
            binasm_rec.unk5_003F = 0x3B;
            binasm_rec.unk8 = sp4C;
            binasm_rec.opt = sp50;
            put_binasmfyle();
            binasm_rec.unk0 = sp54;
            binasm_rec.unk5_003F = 0x3B;
            binasm_rec.unk8 = sp48;
            binasm_rec.opt = sp50;
            put_binasmfyle();
        }
        if (Tokench == 0x23) {
                break;
        }
    }
}


static void func_004061F8(s32 arg0) {
    sym* sp3C;
    s32 sp38;
    s32 sp34;

    sp38 = 0;
    sp34 = 0;

    sp3C = GetRegister();
    if (sp3C != NULL) {
        if (Tokench == 0x22) {
            func_00405C28(&Tstring, strlen((s8* ) &Tstring), &sp38, &sp34);
        } else {
            dw_GetExpr(&sp38, &sp34);
        }
        func_00405178(0, arg0, sp3C->unk14, 0x48, 2, 0x48, sp38);
        func_00405178(0, arg0, sp3C->unk14, 0x48, 2, 0x48, sp34);
        nexttoken();
    }
}


static void func_00406340(sym** arg0, s32* arg1) {
    *arg0 = 0;
    *arg1 = 0;
    nexttoken();
    if (strcmp(Tstring, "hi") == 0) {
        gform_extn = 1;
    } else if (strcmp(Tstring, "lo") == 0) {
        gform_extn = 2;
    } else if (strcmp(Tstring, "gprel") == 0) {
        gform_extn = 5;
    } else if (strcmp(Tstring, "half") == 0) {
        gform_extn = 6;
    } else {
        posterror("% not followed by hi/lo/gprel", NULL, 1);
        return;
    }
}

static void func_00406684(void) {
    nexttoken();
    if (Tokench != 'd') {
        posterror("invalid memory tag", NULL, 1);
        return;
    }
    binasm_rec.unkA_3FFF = GetExpr();
}


static void func_00406728(s32 arg0) {
    s32 pad;
    sym* sp50;
    s32 sp4C;
    s32 sp48;
    sym* sp44;
    s32 sp40;
    sym* temp_v0;

    sp4C = 0;
    sp50 = NULL;
    if ((temp_v0 = GetRegister()) == NULL) {
        return;
    }
    sp40 = temp_v0->unk14;
    sp44 = NULL;
    if (Tokench == '"') {
        sp48 = 0;
        func_00405C28(Tstring, strlen(Tstring), &sp4C, &sp48);
        func_00405178(0, arg0, sp40, 0x48, 2, 0x48, sp4C);
        func_00405178(0, arg0, sp40, 0x48, 2, 0x48, sp48);
        nexttoken();
        return;
    }
    if (Tokench == 'i') {
        if (!LookUp(Tstring, &sp44)) {
            EnterSym(Tstring, &sp44, 1);
            if (gp_warn != 0) {
                posterror("Load/store of an undefined symbol", sp44->name, 2);
            }
        }
        if (sp44->unk10 == 4) {
            sp44 = NULL;
        } else if (sp44->unk10 == 3) {
            nexttoken();
            if (Tokench == ',') {
                func_00406684();
            }
            if ((Tokench != '+')
                && (Tokench != '-')
                && (Tokench != '(')
                && (Tokench != '#')) {
                posterror("invalid external expression", NULL, 1);
                return;
            }
        }
    }
    if (Tokench == '%') {
        func_00406340(&sp44, &sp4C);
    }
    if ((Tokench == 'i')
        || (Tokench == 'd')
        || (Tokench == 'h')
        || (Tokench == '+')
        || (Tokench == '-')
        || (Tokench == '~')
        || (Tokench == '"')
        || (Tokench == '(')) {
            GetBaseOrExpr(&sp50, &sp4C);
            if ((sp50 == NULL) && (Tokench == '(')) {
            nexttoken();
            if ((sp50 = GetRegister()) == NULL) {
                return;
            }
            if (Tokench != ')') {
                posterror("')' expected", Tstring, 1);
                return;
            }
            nexttoken();
            if (Tokench == ',') {
                func_00406684();
            }
        }
    }
    if (sp44 == NULL) {
        if (sp50 == NULL) {
            sp50 = reg_ptr;
        }
    }
    if (sp44 != NULL) {
        if (list_extsyms != 0) {
            func_004054E8(sp44->unk18, Tstring);
        }
        if (sp50 == NULL) {
            func_00405178(sp44->unk18, arg0, sp40, 0x48, 1, 0x48, sp4C);
        } else {
            func_00405178(sp44->unk18, arg0, sp40, sp50->unk14, 1, 0x48, sp4C);
        }
    } else {
        func_00405178(0, arg0, sp40, sp50->unk14, 0, 0x48, sp4C);
    }
    gform_extn = 0;
}

static void func_00406C48(s32 arg0) {
    s32 pad4C;
    sym* sp48;
    s32 sp44;
    s32 sp40; // u32?
    sym* sp3C;
    s32 pad38;

    sp40 = 0;
    sp48 = NULL;
    sp3C = NULL;

    sp44 = GetExpr();
    if ((sp44 < 0) || (sp44 > 0x1F)) {
        posterror("Cache/Pref instruction has invalid value", NULL, 1);
    }
    if (Tokench == 'i') {
        if (!LookUp(Tstring, &sp3C)) {
            EnterSym(Tstring, &sp3C, 1);
            if (gp_warn != 0) {
                posterror("Load/store of an undefined symbol", sp3C->name, 2);
            }
        }

        if (sp3C->unk10 == 4) {
            sp3C = NULL;
        } else if (sp3C->unk10 == 3) {
            nexttoken();
            if ((Tokench != '+')
                && (Tokench != '-')
                && (Tokench != '(')
                && (Tokench != '#')) {
                posterror("invalid external expression", NULL, 1);
                return;
            }
        }
    }
    if ((Tokench == 'i')
        || (Tokench == 'd')
        || (Tokench == 'h')
        || (Tokench == '+')
        || (Tokench == '-')
        || (Tokench == '~')
        || (Tokench == '"')
        || (Tokench == '(')) {
            GetBaseOrExpr(&sp48, &sp40);
        if ((sp48 == NULL) && (Tokench == '(')) {
            nexttoken();
            if ((sp48 = GetRegister()) == NULL) {
                return;
            }
            if (Tokench != ')') {
                posterror("')' expected", Tstring, 1);
                return;
            }
            nexttoken();
        }
    }

    if (sp3C == NULL) {
        if (sp48 == NULL) {
            sp48 = reg_ptr;
        }
    }
    sp40 &= 0xFFFF;
    if (sp3C != NULL) {
        if (sp48 == NULL) {
            func_00405178(sp3C->unk18, arg0, sp44, 0x48, 0xE, 0x48, sp40);
        } else {
            func_00405178(sp3C->unk18, arg0, sp44, sp48->unk14, 0xE, 0x48, sp40);
        }
    } else {
        func_00405178(0, arg0, sp44, sp48->unk14, 0xE, 0x48, sp40);
    }
}


void func_00406FE8(s32 arg0) {
    sym* sp3C;
    s32 sp38;
    sym* sp34;

    sp38 = 0;
    sp3C = NULL;
    sp34 = NULL;
    if (Tokench == 'i') {
        if (!LookUp(Tstring, &sp34)) {
            EnterSym(Tstring, &sp34, 1);
            if (gp_warn != 0) {
                posterror("Load/store of an undefined symbol", sp34->name, 2);
            }
        }

        if (sp34->unk10 == 4) {
            sp34 = NULL;
        } else if ( sp34->unk10 == 3) {
            nexttoken();
            if ((Tokench != '+')
                && (Tokench != '-')
                && (Tokench != '(')
                && (Tokench != '#')) {
                posterror("invalid external expression", NULL, 1);
                return;
            }
        }
    }

    if ((Tokench != 'i')
        && (Tokench != 'd')
        && (Tokench != 'h')
        && (Tokench != '+')
        && (Tokench != '-')
        && (Tokench != '~')
        && (Tokench != '"')
        && (Tokench != '(')) {
        GetBaseOrExpr(&sp3C, &sp38);
        if ((sp3C == NULL) && (Tokench == '(')) {
            nexttoken();
            if ((sp3C = GetRegister()) == NULL) {
                return;
            }
            if (Tokench != ')') {
                posterror("')' expected", Tstring, 1);
                return;
            }
            nexttoken();
        }
    }
    if (sp34 == NULL) {
        if (sp3C == NULL) {
            sp3C = reg_ptr[0];
        }
    }
    if (sp34 != NULL) {
        if (sp3C == NULL) {
            func_00405178(sp34->unk18, arg0, 0x48, 0x48, 1, 0x48, sp38);
        } else {
            func_00405178(sp34->unk18, arg0, 0x48, sp3C->unk14, 1, 0x48, sp38);
        }
    } else {
        func_00405178(0, arg0, 0x48, sp3C->unk14, 0, 0x48, sp38);
    }
}


#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00407334.s")

static void func_004075CC(s32 arg0) {
    sym* temp_v0;

    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x17;
    binasm_rec.unk6_03FE = arg0;
    temp_v0 = GetRegister();
    if (temp_v0 != NULL) {
        binasm_rec.unk8_FE = temp_v0->unk14;
    }
    binasm_rec.unk8_01FC = 0x48;
    binasm_rec.unk8_0003C000 = 2;
    func_00407334();
}

static void func_004076A0(s32 fasm) {
    s32 stackPad;
    sym* sp48;
    sym* sp44;
    u32 sp40;
    s32 var_a0;
    u32 sp38;
    u32 sp34;
    sym* sp30;
    sp40 = 0;
    sp44 = NULL;
    sp30 = NULL;

    sp48 = GetRegister();
    if (sp48 != 0) {
        sp48 = sp48->unk14;

        if ((diag_flag != 0) && (fasm == zlui) && (Tokench == 'i')) {
            if (LookUp(Tstring, &sp30) != 0) {
                if (sp30->unk10 == 0) {
                    nexttoken();
                    if (Tokench == ',') {
                        nexttoken();
                    }
                } else {
                    sp30 = NULL;
                }
            } else {
                sp30 = NULL;
            }
        }
        if (Tokench == '%') {
            func_00406340(&sp44, &sp40);
        } else if (isa < ISA_MIPS3) {
            sp40 = GetExpr();
        } else if (dw_GetExpr(&sp38, &sp34)) {
            if (fasm == zlui) {
                posterror("lui expression not in 0..65535", NULL, 1);
            }
            if (fasm != zli) {
                assertion_failed("fasm == zli", "as0parse.c", 1094);
            }
            func_00405178(0, 0x14C, sp48, 0x48, 2, 0x48, sp38);
            func_00405178(0, 0x14C, sp48, 0x48, 2, 0x48, sp34);
            return;
        } else {
            sp40 = sp34;
        }

        if (fasm == zlui) {
            if (sp44 == NULL) {
                if ((sp40 >> 0x10) != 0) {
                    posterror("lui expression not in 0..65535", NULL, 1);
                }
                sp40 <<= 0x10;
            }
        }

        if (sp44 != NULL) {
            var_a0 = sp44->unk18;
        } else {
            var_a0 = 0;
        }

        if ((fasm == 0xCD) && (sp30 != NULL)) {
            func_00405178(var_a0, fasm, sp48, sp30->unk14, 4, 0x48, sp40);
        } else {
            func_00405178(var_a0, fasm, sp48, 0x48, 2, 0x48, sp40);
        }
        gform_extn = 0;
    }
}

//if's

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00407A20.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040848C.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_004085D8.s")

static void func_004086EC(s32 arg0) {
    sym* reg1; // sp+44?
    sym* reg2; // sp+40
    sym* reg3; // sp+3C
    s32 sp38;
    s32 sp34;

    if (arg0 == 0x194) {
        sp38 = GetExpr();
        if ((sp38 < 0) || (sp38 > 31)) {
            posterror("hint field not in range 0..31", NULL, 2);
        }
        sp34 = sp38 & 0x1F;
    } else {
        if ((reg1 = GetRegister()) == NULL) {
            return;
        }
        sp34 = reg1->unk14;
    }

    if ((reg2 = GetRegister()) == NULL) {
        return;
    }
    if (Tokench != '(') {
        posterror("expecting '(' before base register", NULL, 1);
        return;
    }
    nexttoken();
    if ((reg3 = GetRegister()) == NULL) {
        return;
    }
    if (Tokench != ')') {
        posterror("expecting ')' after base register", NULL, 1);
        return;
    }
    nexttoken();
    func_00405178(0, arg0, sp34, reg3->unk14, 3, reg2->unk14, 0);
}


static void func_004088B8(s32 arg0) {
    sym* sp4C;
    sym* sp48;
    sym* sp44;
    s32 sp40;
    u32 sp3C;
    s32 sp38;
    s32 sp34;
    // s32 var_v1;
    // void* temp_v0;

    if ((sp4C = GetRegister()) == NULL) {
        return;
    }
    sp48 = NULL;
    if ((Tokench == 'i') && LookUp(Tstring, &sp44) && (sp44->unk10 == 0)) {
        sp48 = sp44;
        nexttoken();
        if (Tokench == ',') {
            nexttoken();
        }
    }

    if ((Tokench == 'i') || (Tokench == 'd')
        || (Tokench == 'h') || (Tokench == '+')
        || (Tokench == '-') || (Tokench == '~')
        || (Tokench == '"') || (Tokench == '(')) {
        if (isa <= ISA_MIPS2) {
            sp38 = 0;
            sp40 = GetExpr();
        } else {
            sp38 = dw_GetExpr(&sp3C, &sp40);
        }

        if ((sp48 != NULL) && ((sp40 < 0) || (sp40 > 0x400) || sp38)) {
            posterror("code field in trap instruction not in 0..1023", NULL, 2);
        }

        if (sp38) {
            sp34 = atflag;
            if (!sp34) {
                posterror("macro expansion needs at register after .set noat", NULL, 1);
            }

            atflag = 0;
            func_00405178(0, 0x14C, 1, 0x48, 2, 0x48, sp3C);
            func_00405178(0, 0x14C, 1, 0x48, 2, 0x48, sp40);
            func_00405178(0, arg0, sp4C->unk14, 1, 4, 0x48, 8);
            atflag = sp34;
        } else if (sp48 != NULL) {
            func_00405178(0, arg0, sp4C->unk14, sp48->unk14, 4, 0x48, sp40);
        } else {
            func_00405178(0, arg0, sp4C->unk14, 0x48, 2, 0x48, sp40);
        }
    } else if (sp48 == NULL) {
        posterror("invalid syntax in statement", NULL, 1);
    } else {
        func_00405178(0, arg0, sp4C->unk14, sp48->unk14, 4, 0x48, 8);
    }
}

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00408C80.s")

static s32 func_00409118(s32* arg0) {
    s32 var_v1;
    s32 var_v1_2;
    s32 temp_v0;

    if ((Tstringlength != 1) || ((u8) *Tstring != 0x2E)) {
        return 0;
    }
    nexttoken();
    var_v1 = 0;
    if (Tokench == '-') {
        var_v1 = 1;
    } else if (Tokench != '+') {
        posterror("+/- expected after .", NULL, 1);
        return 1;
    }

    nexttoken();
    if (Tokench != 'd') {
        posterror("branch offset not specified", NULL, 1);
        return 1;
    }

    temp_v0 = GetExpr();
    if (temp_v0 & 3) {
        posterror("relative offset not multiple of 4", NULL, 1);
        return 1;
    }
    if (temp_v0 >= 0x8001) {
        posterror("relative offset beyond 32768", NULL, 1);
        return 1;
    }
    if ((var_v1 != 0) || (temp_v0 == 0)) {
        gform_extn = 4;
        var_v1_2 = temp_v0 / 4;
    } else {
        gform_extn = 3;
        var_v1_2 = (s32) (temp_v0 - 4) / 4;
    }
    *arg0 = var_v1_2;
    return 1;
}

static void func_004092FC(s32 arg0) {
    sym* sp5C;
    sym* sp58;
    sym* sp54;
    sym* sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    void* temp_v0;

    sp4C = 0;
    sp58 = NULL;

    if ((sp5C = GetRegister()) == NULL) {
        return;
    }
    if ((Tokench == 'i') && (LookUp(Tstring, &sp50) != 0) && (sp50->unk10 == 0)) {
        sp58 = sp50;
        nexttoken();
        if (Tokench == ',') {
            nexttoken();
        }
    }
    if (sp58 == NULL) {
        if  ((Tokench == 'i')
            || (Tokench == 'd')
            || (Tokench == 'h')
            || (Tokench == '+')
            || (Tokench == '-')) {
            if (isa < ISA_MIPS3) {
                sp40 = 0;
                sp48 = GetExpr();
            } else {
                sp40 = dw_GetExpr(&sp3C, &sp48);
            }
            sp4C = 1;
        }
    }
    if ((sp58 == NULL) && (sp4C == 0)) {
        posterror("invalid syntax in statement", NULL, 1);
        return;
    }
    if (Tokench != 'i') {
        posterror("label expected", NULL, 1);
        return;
    }
    if (func_00409118(&sp44) != 0) {
        binasm_rec.unkA_3FFF = sp44;
        if (sp4C != 0) {
            func_00405178(0, arg0, sp5C->unk14, 0x48, 0xC, 0x48, sp48);
        } else {
            func_00405178(0, arg0, sp5C->unk14, sp58->unk14, 8, 0x48, 0);
        }
        gform_extn = 0;
        return;
    }
    if ((&Tstring, &sp50) != 0) {
        if (sp50->unk10 == 3) {
            sp54 = sp50;
        } else {
            posterror("symbol is not a label", &Tstring, 1);
            return;
        }
    } else {
        EnterSym(Tstring, &sp54, 1);
    }

    if (list_extsyms != 0) {
        if (isdigit(Tstring[0])) {
            func_004054E8(sp54->unk18, NULL);
        } else {
            func_004054E8(sp54->unk18, &Tstring);
        }
    }

    nexttoken();
    if (sp4C != 0) {
        sp38 = atflag;
        if (sp40 != 0) {
            if (sp38 == 0) {
                posterror("macro expansion needs at register after .set noat", NULL, 1);
            }
            atflag = 0;
            func_00405178(0, 0x14C, 1, 0x48, 2, 0x48, sp3C);
            func_00405178(0, 0x14C, 1, 0x48, 2, 0x48, sp48);
            func_00405178(sp54->unk18, arg0, sp5C->unk14, 1, 8, 0x48, 0);
            atflag = sp38;
        } else {
            func_00405178(sp54->unk18, arg0, sp5C->unk14, 0x48, 0xC, 0x48, sp48);
        }
    } else {
        func_00405178(sp54->unk18, arg0, sp5C->unk14, sp58->unk14, 8, 0x48, 0);
    }
}

void func_00409850(s32 arg0) {
    sym* sp3C;
    sym* sp38;
    sym* sp34;
    s32 sp30;


    if (arg0 == 0xE3) {
        sp3C = reg_ptr[0];
    } else {
        if ((sp3C = GetRegister()) == NULL) {
            return;
        }
        if (((arg0 == 0xE5) || (arg0 == 0x120) || (arg0 == 0xE4) || (arg0 == 0x124)) && (sp3C == reg_ptr[0x20-1])) {
            posterror("$31 not allowed in conditional branch and link", NULL, 2);
        }
    }

    if (Tokench != 'i') {
        posterror("label expected", NULL, 1);
        return;
    }
    if (func_00409118(&sp30) != 0) {
        binasm_rec.unkA_3FFF = sp30;
        func_00405178(0, arg0, sp3C->unk14, 0x48, 9, 0x48, 0);
        gform_extn = 0;
    } else {
        if (LookUp(Tstring, &sp34)) {
            if (sp34->unk10 == 3) {
                sp38 = sp34;
            } else {
                posterror("symbol is not a label", Tstring, 1);
                return;
            }
        } else {
            EnterSym(Tstring, &sp38, 1);
        }
        if (list_extsyms != 0) {
            if (isdigit(Tstring[0])) {
                func_004054E8(sp38->unk18, NULL);
            } else {
                func_004054E8(sp38->unk18, Tstring);
            }
        }
        nexttoken();
        func_00405178(sp38->unk18, arg0, sp3C->unk14, 0x48, 9, 0x48, 0);
    }
}


static void func_00409B10(s32 arg0) {
    sym* sp4C;
    sym* sp48;
    sym* sp44;
    s32 sp34;
    s32 sp3C;
    s32 sp38;
    // s32 var_v1;

    if (Tokench != 'i') {
        posterror("condition code or label expected", NULL, 1);
        return;
    }

    sp34 = (arg0 == 8) || (arg0 == 7) || (arg0 == 0x128) || (arg0 == 0x127);

    if (sp34) {
        sp3C = 0x40;

        if ((LookUp(Tstring, &sp44)) && (sp44->unk10 == 0)) {
            nexttoken();
            if (Tokench == 0x2C) {
                nexttoken();
            }
            sp3C = sp44->unk14;
        }
    }
    if (Tokench != 'i') {
        posterror("label expected", NULL, 1);
        return;
    }
    if (func_00409118(&sp38) != 0) {
        binasm_rec.unkA_3FFF  = sp38;
        if (sp34) {
            func_00405178(0, arg0, sp3C, 0x48, 9, 0x48, 0);
        } else {
            func_00405178(0, arg0, 0x48, 0x48, 0xA, 0x48, 0);
        }
        gform_extn = 0;
        return;
    }
    if (LookUp(Tstring, &sp48)) {
        if (sp48->unk10 == 3) {
            sp4C = sp48;
        } else {
            posterror("symbol is not a label", Tstring, 1);
            return;
        }
    } else {
        EnterSym(Tstring, &sp4C, 1);
    }
    if (list_extsyms != 0) {
        if (isdigit(Tstring[0])) {
            func_004054E8(sp4C->unk18, NULL);
        } else {
            func_004054E8(sp4C->unk18, Tstring);
        }
    }
    nexttoken();
    if (sp34) {
        func_00405178(sp4C->unk18, arg0, sp3C, 0x48, 9, 0x48, 0);
    } else {
        func_00405178(sp4C->unk18, arg0, 0x48, 0x48, 0xA, 0x48, 0);
    }
}

void func_00409ECC(s32 arg0) {
    u32 temp_v0;

    if ((Tokench == 0x69)
        || (Tokench == 0x64)
        || (Tokench == 0x68)
        || (Tokench == 0x2B)
        || (Tokench == 0x2D)) {
        temp_v0 = GetExpr();
    } else {
        posterror("expression required", NULL, 1);
        return;
    }
    if ((temp_v0 >> 0x19) != 0) {
        posterror("coprocessor operation > 25 bits", NULL, 1);
    }
    func_00405178(0, arg0, 0x48, 0x48, 2, 0x48, temp_v0);
}

static void func_00409FD0(s32 arg0) {
    sym* temp_v0;

    temp_v0 = GetRegister();
    if (temp_v0 != NULL) {
        func_00405178(0, arg0, temp_v0->unk14, 0x48, 7, 0x48, 0);
    }
}

static void func_0040A044(s32 arg0) {
    sym* temp_v0;

    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = arg0;
    temp_v0 = GetRegister();
    if (temp_v0 != NULL) {
        binasm_rec.unk8_FE = temp_v0->unk14;
        put_binasmfyle();
    }
}

static void func_0040A0D4(void) {
    u32 ret;

    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0xF;
    ret = GetExpr();
    binasm_rec.unk8 = ret;
    if (ret & 3) {
        posterror("Offset for cprestore must be positive and divisible by 4", NULL, 1);
    }
    put_binasmfyle();
}


static void func_0040A160(void) {
    sym* var_v1;


    binasm_rec.unk5_003F = 0x21;
    var_v1 = GetRegister();
    if (var_v1 == NULL) {
        posterror(".cpalias requires a register argument", NULL, 1);
    }
    binasm_rec.unk8_FE = var_v1->unk14;
    put_binasmfyle();
}


static void func_0040A208(void) {
    s32 sp24;

    sp24 = GetExpr();
    GetExpr();
    if (sp24 != 3) {
        posterror("version stamp does not match", NULL, 2);
    }
}

static void func_0040A280(void) {
    sym* sp34;
    sym* sp30;
    u32 sp2C;
    sym* sp28;

    if ((sp34 = GetRegister()) == NULL) {
        return;
    }
    if ((Tokench == 'i') || (Tokench == 'd') ||
        (Tokench == 'h') || (Tokench == '+') ||
        (Tokench == '-') || (Tokench == '~') ||
        (Tokench == '(')) {
        sp2C = GetExpr();
    } else {
        posterror("expression required", NULL, 1);
        return;
    }
    if (Tokench != '#') {
        if ((sp30 = GetRegister()) == NULL) {
            return;
        }
    } else {
        sp30 = reg_ptr[0x20-1];
    }
    if (!LookUp(sframereg, &sp28)) {
        posterror("can not find symbol", sframereg, 1);
    }
    sp28->unk8 = sp34->unk8;
    sp28->unk14 = sp34->unk14;
    if (!LookUp(sframesize, &sp28)) {
        posterror("can not find symbol", sframesize, 1);
    }
    sp28->unk8 = sp2C;
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x2B;
    binasm_rec.unkC_FE = sp34->unk14;
    binasm_rec.unk8 = sp2C;
    binasm_rec.unkC_01FC = sp30->unk14;
    put_binasmfyle();
}

static void func_0040A4B0(void) {
    if (LastLabel != 0) {
        func_00405574(0);
    }
    StructOrg = GetExpr();
    isStruct = 1;
    LastLabel = 0;
}


static void func_0040A530(void) {
    s32 var_v1;

    if ((var_v1 =  GetExpr()) != 1) {
        posterror(".shift_addr expression not 1", NULL, 1);

    }
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F =  0x39;
    binasm_rec.unk8 = var_v1;
    put_binasmfyle();
    shftaddr = 1;
}

static void func_0040A5D4(void) {
    s32 temp_v0;

        temp_v0 = GetExpr();
    if ((temp_v0 < 0) || (temp_v0 > 12)) {
        posterror("align expression not 0..12", NULL, 1);
        return;
    }
    if (isStruct) {
        StructOrg = ((((s32)StructOrg + (temp_v0 << temp_v0)) - 1) >> temp_v0) << temp_v0;
    } else {
        binasm_rec.unk0 = 0;
        binasm_rec.unk5_003F = 4;
        binasm_rec.unk8 = temp_v0;
        put_binasmfyle();
    }
}

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040A6B8.s")

static void func_0040A79C(s32 arg0) {

    if (LastLabel != 0) {
        func_00405574(0);
    }

    do {
        if (Tokench != 0x22) {
            posterror("string literal expected", NULL, 1);
        } else if (isStruct != 0) {
            StructOrg += Tstringlength;
            if (arg0 != 0) {
                StructOrg = StructOrg + 1;
            }
        } else if (arg0 != 0) {
            func_0040A6B8(6);
        } else {
            func_0040A6B8(5);
        }
        if (Tokench != 0x23) {
            nexttoken();
        }
    } while (Tokench == 0x2C);
}


void func_0040A958(void) {
    s32 sp4C;
    s32 sp48;

    if (LastLabel != 0) {
        func_00405574(0);
    }
    do {
        GetItem(&sp48, &sp4C);
        if (isStruct) {
            StructOrg = StructOrg + ((sp4C < 1) ? 1 : sp4C);
        } else {
            if (sp48 < -128 || sp48 > 255) {
                posterror("value must be -128..255", NULL, 1);
                sp48 = 0;
            }
            binasm_rec.unk0 = 0;
            binasm_rec.unk5_003F = 7;
            binasm_rec.unk8 = sp48;
            binasm_rec.opt = sp4C;
            put_binasmfyle();
        }
    } while (Tokench != '#');
}

void func_0040AAD4(s32 arg0) {
    sym* sp34;
    u32 sp30;
    u32 sp2C;
    u32 sp28;

    if (Tokench != 'i') {
        posterror("identifer expected", NULL, 1);
        if (Tokench != '#') {
            nexttoken();
        }
        return;
    }
    if (LookUp(Tstring, &sp34) == 0) {
        EnterSym(Tstring, &sp34, arg0 != 9);
    }
    if (list_extsyms != 0) {
        func_004054E8(sp34->unk18, Tstring);
    }
    nexttoken();
    if (Tokench == ',') {
        nexttoken();
    }
    sp28 = 0;
    if ((arg0 == 0x2D) && (Tokench == '#')) {
        sp2C = 0;
    } else {
        sp2C = GetExpr();
    }

    if (Tokench == 'i') {
        if ((Tstring[0] == 'S') && (Tstring[1] == '\0')) {
            sp28 = 1;
        } else {
            posterror("optional argument not S, ignored.", NULL, 2);
        }
        nexttoken();
    }

    if (sp34->unk10 != 3) {
        posterror("invalid symbol for .comm/.lcomm/.extern ", Tstring, 1);
        return;
    }

    binasm_rec.unk0 = sp34->unk18;
    binasm_rec.unk5_003F = arg0;
    binasm_rec.unk8 = sp2C;
    binasm_rec.opt = sp28;
    put_binasmfyle();
    switch (arg0) {                         /* irregular */
    case 8:
        sp30 = 0x11;
        break;
    case 9:
        sp30 = 0x21;
        break;
    case 0x2D:
        sp30 = 0x22;
        break;
    default:
        assertion_failed("false", "as0parse.c", 2568);
        break;
    }
    sym_define(sp34->unk18, sp30, sp2C);
}

static void func_0040ADFC(void) {
    if (Tokench != 'i') {
        posterror("identifer expected", NULL, 1);
    } else {
        nexttoken();
        if (Tokench == ',') {
            nexttoken();
        }
        GetExpr();
    }
    if (Tokench != '#') {
        nexttoken();
    }
    posterror(".sym directive not implemented", NULL, 2);
}


void func_0040AF00(s32 iop) {
    if (LastLabel != 0) {
        func_00405574(0);
    }
    isStruct = 0;
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = iop;
    if (iop == 0x15) {
        binasm_rec.unk8 = (Tokench != '#') ? Tstringlength : 0;
    }
    if ((iop == 0x15) && (Tokench != '#')) {
        int i;

        put_binasmfyle();
        for (i = 0; i < Tstringlength; i++) {
            binasm_rec.arr0[i] = Tstring[i];
        }
        nexttoken();
    }
    put_binasmfyle();

    switch (iop) {
        case 0x15:
            CurrentSegment = 1;
            break;
        case 0xA:
            CurrentSegment = 2;
            break;
        case 0x19:
            CurrentSegment = 0xD;
            break;
        case 0x1A:
            CurrentSegment = 0xF;
            break;
        default:
            if (iop != 0x1A) {
                assertion_failed("iop == irdata", "as0parse.c", 2627);
            }
            break;
    }
}



static void func_0040B0F4(s32 arg0) {
    u8 temp_v0;

    if (LastLabel != 0) {
        if ((arg0 == 2) || (arg0 == 4)) {
            func_00405574(3);
        } else if (arg0 == 1) {
            func_00405574(2);
        }
    }
    do {
        if (isStruct != 0) {
            if ((arg0 == 4) || (arg0 == 2)) {
                StructOrg += 8;
            } else {
                StructOrg += 4;
            }
            if ((Tokench == 0x2D) || (Tokench == 0x2B)) {
                nexttoken();
            }
            nexttoken();
        } else {
            binasm_rec.unk0 = 0;
            if (arg0 == 4) {
                binasm_rec.unk5_003F = 0x2C;
            } else if (arg0 == 2) {
                binasm_rec.unk5_003F = 0xB;
            } else if (arg0 == 1) {
                binasm_rec.unk5_003F = 0xD;
            }
            func_00407334();
        }

        if (Tokench == 0x2C) {
            nexttoken();
        }
    } while (Tokench != 0x23);
}

static void func_0040B340(void) {
    invent_locs = 0;
    GetExpr();
    if (Tokench != '"') {
        posterror("string literal expected", NULL, 1);
    }
    make_file(&Tstring);
    nexttoken();
}

void do_dot_end(s32 arg0) {
    s32* temp_a1;
    s32* temp_s0;

    if ((arg0 == 0) && (D_10000014 == NULL)) {
        posterror(".end without .ent", NULL, 2);
    } else {
        //temp_a1 = D_10000014;
        if ((arg0 != 0) && (D_10000014 != NULL)) {
            posterror("missing .end at end of assembly", NULL, 2);
        }
         while (D_10000014 != NULL) {

                if (sym_undefined(D_10000014[0]) != 0) {
                    posterror(".ent/.end block never defined the procedure name", NULL, 2);
                } else {
                    binasm_rec.unk0 = st_procend(D_10000014[0]);
                }
                temp_s0 = D_10000014[1];
                free(D_10000014);
                D_10000014 = temp_s0;
                binasm_rec.unk5_003F = 0x18;
                put_binasmfyle();
            }
        }
    }


static void func_0040B554(s32 arg0) {
    s32* sp24;
    s32* temp_v0;

    sp24 = D_10000014;
    temp_v0 = D_10000014 =  malloc(sizeof(long long));
    if (temp_v0 == NULL) {
        new_error();
        return;
    }
    *temp_v0 = arg0;
    D_10000014[1] = sp24;
}

static void func_0040B5F0(s32 arg0) {
    sym* sp24;
    // u8 temp_v1;


    if (LastLabel != 0) {
        func_00405574(0);
    }

    isStruct = false;

    if ((Tokench != 'i') && (arg0 != 0x18)) {
            posterror("identifer expected", NULL, 1);
            return;
    }
    if ((arg0 == 0x1B) || (arg0 == 0x2E)) {
        if (verbose != 0) {
            call_name_and_line(3);
            fprintf(stderr, "%s ", &Tstring);
            fflush(stderr);
        }
        binasm_rec.unk8 = 0;
        if (arg0 == 0x1B) {
            if (D_10000014 != 0) {
                posterror("missing .end preceding this .ent", &Tstring, 2);
                do_dot_end(0);
            }
        } else if (D_10000014 == 0) {
            posterror(".aent must be inside .ent/.end block", &Tstring, 2);
            arg0 = 0x1B;
        }
        if (LookUp(Tstring, &sp24) == 0) {
            EnterSym(Tstring, &sp24, 1);
        }
        if (sp24->unk10 != 3) {
            posterror("invalid symbol for .[a]ent ", &Tstring, 1);
        }
        nexttoken();

        if (Tokench == ',') {
            nexttoken();
        }
        if (Tokench == 'd') {
            nexttoken();
        }
        sym_define(sp24->unk18, 0x23U, 0);
        func_0040B554(sp24->unk18);
        binasm_rec.unk0 = sp24->unk18;
        binasm_rec.unk5_003F = arg0;
        put_binasmfyle();
    } else if (arg0 == 0x18) {
        do_dot_end(0);
    }
    if (Tokench == 'i') {
        nexttoken();
    }
}


static void func_0040B984(void) {
    sym* cur_symbol;
    s32 sp38;

    do {
        if (Tokench != 'i') {
            posterror("identifer expected", NULL, 1);
        } else {
            if (LookUp(Tstring, &cur_symbol) == 0) {
                EnterSym(Tstring, &cur_symbol, 1);
            }
            sym_define(cur_symbol->unk18, 0x22, 0);
            if (cur_symbol->unk10 == 3) {
                if (list_extsyms != 0) {
                    func_004054E8(cur_symbol->unk18, &Tstring);
                }
                binasm_rec.unk0 = (s32) cur_symbol->unk18;
                binasm_rec.unk5_003F = 2;

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

static void func_0040BC84(void) {
    sym* sp4C;
    sym* sp48;

    do {
        if (Tokench != 'i') {
            posterror("identifer expected", NULL, 1);
        } else {
            if (LookUp(Tstring, &sp4C) == 0) {
                EnterSym((s32) &Tstring, (sym** ) &sp4C, 1);
            }
            sym_define(sp4C->unk18, 0x22U, 0);
            if (sp4C->unk10 == 3) {
                binasm_rec.unk0 = sp4C->unk18;
                binasm_rec.unk5_003F = 0x12;
                nexttoken();
                if (Tokench == ',') {
                    nexttoken();
                }
                if (LookUp(Tstring, &sp48) == 0) {
                    EnterSym((s32) &Tstring, (sym** ) &sp48, 1);
                }
                if (sp48 != sp4C) {
                    binasm_rec.unk8 = sp48->unk18;
                } else {
                    binasm_rec.unk8 = 0;
                }
                put_binasmfyle();
            } else {
                posterror("invalid symbol for .globl ", &Tstring, 1);
            }
        }

        if (Tokench != '#') {
            nexttoken();
        }
    } while (Tokench == ',');
}

static s32 func_0040BEBC(s32* arg0, s32 arg1, s32 arg2) {
    sym* sp24;


    if (Tokench == 0x69) {
        if (LookUp(Tstring, &sp24) == 0) {
            EnterSym((s32) &Tstring, (sym** ) &sp24, 1);
        }

        if (sp24->unk10 == 4) {
            GetItem(arg1, arg2);
            return 1;
        }
        if (sp24->unk10 == 3) {
            *arg0 = sp24->unk18;
            nexttoken();
            func_00405A80(arg1, arg2);

            if (Tokench == 0x2C) {
                nexttoken();
               return 1;
            }
        } else {
            posterror("Bad id in expression", (s8* ) &Tstring, 1);
            nexttoken();
            return 0;
        }
    } else {
        GetItem(arg1, arg2);
    }
    return 1;
}


#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040C048.s")

static void func_0040C218(void) {
    u32 temp_v0;

    invent_locs = 0;
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x1C;
    GetExpr();
    binasm_rec.unk8 = CurrentFile;
    if (Tokench == 0x3A) {
        nexttoken();
    }

    CurrentLine = GetExpr();
    binasm_rec.opt = CurrentLine;
    put_binasmfyle();
}

static void func_0040C2E0(void) {
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x13;
    binasm_rec.unk8 = GetExpr();
    binasm_rec.opt = GetExpr();
    put_binasmfyle();
}

static void func_0040C360(void) {
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x32;
    binasm_rec.unk8 = GetExpr();
    binasm_rec.opt = GetExpr();
    put_binasmfyle();
}


static void func_0040C3E0(void) {
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F =  0x33; //shift
    binasm_rec.unk8 = GetExpr();
    binasm_rec.opt = GetExpr();
    put_binasmfyle();
}

static void func_0040C460(void) {
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x3C;
    binasm_rec.unk8 = GetExpr();
    put_binasmfyle();
}

static void func_0040C4CC(void) {
    sym* sp24;

    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x3d;
    binasm_rec.unk8 = GetExpr();
    if (binasm_rec.unk8 != 0) {
        sp24 = NULL;
        if (LookUp(Tstring, &sp24) == 0) {
            EnterSym(Tstring, (sym** ) &sp24, 0);
        }

        binasm_rec.unk0 = sp24->unk18;
        sp24 = NULL;

        nexttoken();
        if (LookUp(Tstring, &sp24) == 0) {
            EnterSym(Tstring, &sp24, 1);
        }
        binasm_rec.opt = sp24->unk18;
    }
    put_binasmfyle();
}

static void func_0040C5E8(s32 arg0) {
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = arg0;
    binasm_rec.unk8 = GetExpr();
    binasm_rec.opt = GetExpr();
    put_binasmfyle();
}


void func_0040C66C(s32 arg0, u32 arg1) {
    u32 var_s5;
    u32 var_s0;

    if (isStruct) {
        posterror(".repeat not allowed in struct", NULL, 1);
        return;
    }
    if (arg0 != 0) {
        if (in_repeat_block) {
            posterror(".repeat may not nest", NULL, 1);
            return;
        }
        in_repeat_block = 1;
        rep_count = arg1;
        rep_size = 0;
    } else {
        if (!in_repeat_block) {
            posterror(".endr without preceding .repeat", NULL, 1);
            return;
        }
        in_repeat_block = 0;
        for (var_s5 = rep_count; var_s5 > 0; var_s5--) {
            for (var_s0 = 0; var_s0 < rep_size; var_s0++) {
                binasm_rec = rep_buffer.unk0[var_s0];
                put_binasmfyle();
            }
        }
    }
}


static void func_0040C830(s32 arg0) {
    if (LastLabel != 0) {
        func_00405574(0);
    }
    isStruct = false;
    binasm_rec.unk5_003F = arg0;
    if (arg0 == '$') {
        if (Tokench == 'i') {
            nexttoken();
            return;
        }
        posterror("identifier expected", NULL, 1);
        return;
    }
    binasm_rec.unk0 = GetExpr();
}


static void func_0040C928(void) {
    sym* cur_symbol;

    binasm_rec.unk5_003F = 0x25;

    cur_symbol = GetRegister();
    if (cur_symbol != NULL) {
        binasm_rec.opt = GetExpr();
        binasm_rec.unk0 = GetExpr();
        binasm_rec.unk8_FE = cur_symbol->unk14;
    }
}

//func_0040C9D0
static void Parse_option_directive(void) {
    s32 as1_option;
    char* dest;
    char* temp_v0;

    if (Tokench != 'i') {
        posterror(".option name expected", NULL, 2);
        return;
    }
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x2F;
    dest = malloc(Tstringlength + 2);
    dest[0] = '-';
    strcpy(&dest[1], &Tstring);
    as1_option = which_opt(dest);
    free(dest);
    nexttoken();
    switch (as1_option) {                                 /* irregular */
        case OPTION_O0: //-O0
            binasm_rec.unk6_C0 = 1;
            binasm_rec.opt = 0;
            break;
        case OPTION_O1: //-O1
            binasm_rec.unk6_C0 = 1;
            binasm_rec.opt = 1;
            break;
        case OPTION_O: //-O
        case OPTION_O2: //-O2
            binasm_rec.unk6_C0 = 1;
            binasm_rec.opt = 2;
            break;
        case OPTION_O3: //-O3
            binasm_rec.unk6_C0 = 1;
            binasm_rec.opt = 3;
            break;
        case OPTION_O4: //-O4
            binasm_rec.unk6_C0 = 1;
            binasm_rec.opt = 4;
            break;

        case OPTION_pic0: //-pic0
            binasm_rec.unk6_C0 = 2;
            binasm_rec.opt = 0;
            break;
        case OPTION_pic1: //-pic1
            binasm_rec.unk6_C0 = 2;
            binasm_rec.opt = 1;
            break;
        case OPTION_pic2: //-pic2
            binasm_rec.unk6_C0 = 2;
            binasm_rec.opt = 2;
            break;
        case OPTION_big_got: //big_got
        case OPTION_coff: //coff
        case OPTION_elf: //elf
            break;
        default:
            posterror("Unknown name in .option", NULL, 2);
            break;
    }
    put_binasmfyle();
}


static s32 func_0040CC44(u8** arg0) {
    s32 var_s0;
    s8** var_s1;

    var_s1 = &sset_value;


    for(var_s0 = 0; var_s0 <= 0x10 ; var_s0++){
        if (strcmp(arg0, *var_s1) == 0) {
        return var_s0;
    }
    var_s1 += 1;
    }
    return 0;


}

static void func_0040CCCC(void) {
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x20;

    if (Tokench != 'i') {
        posterror(".set option expected", NULL, 2);
    } else {
        binasm_rec.unk8 = func_0040CC44(&Tstring);
        switch (binasm_rec.unk8) {                          /* irregular */
        case 5:
            atflag = true;
            break;
        case 6:
            atflag = false;
            break;
        case 0:
            posterror("unknown option in .set", (s8* ) &Tstring, 2);
            break;
        }
        nexttoken();
    }
    put_binasmfyle();
}

static void func_0040CDE4(s32 arg0) {
    sym* temp_v0;

    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = arg0;

    if ((temp_v0 = GetRegister()) != NULL) {
        binasm_rec.unk6_FE = temp_v0->unk14;

        if ((temp_v0 = GetRegister()) != NULL) {
            binasm_rec.unk6_01FC = temp_v0->unk14;
            put_binasmfyle();
        }
    }
}


static void func_0040CEB4(void) {
    int temp_v0;
    int temp_v1;
    int var_v1;

    if (LastLabel) {
        func_00405574(0);
    }
    temp_v0 = GetExpr();
    // temp_v1 = temp_v0;
    if (isStruct != 0) {
        var_v1 = (temp_v0 < 0) ? 0 : temp_v0;
        StructOrg = var_v1 + StructOrg;
        return;
    }
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x14;
    binasm_rec.unk8 = temp_v0;
    binasm_rec.opt = 0;
    put_binasmfyle();
}

static void func_0040CF9C(void) {
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 temp_t9;
    s32 var_v1;

    if (LastLabel != 0) {
        func_00405574(2);
    }
    while(true) {
        sp4C = 0;
        sp50 = 1;
        sp54 = 0;
        if (func_0040BEBC(&sp54, &sp4C, &sp50) == 0) {
            break;
        }

        if (isStruct != 0) {
            if (sp50 * 4 < 4) {
                var_v1 = 4;
            } else {
                var_v1 = sp50 * 4;
            }
            StructOrg = var_v1 + StructOrg;

        } else {
            binasm_rec.unk0 = sp54;
            binasm_rec.unk5_003F = 0x16;
            binasm_rec.unk8 = sp4C;
            binasm_rec.opt = sp50;
            put_binasmfyle();
        }
        if (Tokench == 0x23) {
            break;
        }
    }
}



static void func_0040D110(void) {
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 temp_t9;
    s32 var_v1;

    if (LastLabel != 0) {
        func_00405574(2);
    }

    while(true) {

    sp4C = 0;
    sp50 = 1;
    sp54 = 0;

    if (func_0040BEBC(&sp54, &sp4C, &sp50) == 0) {
        break;
    }
        if (isStruct != 0) {
            temp_t9 = sp50 * 4;
            if (temp_t9 < 4) {
                var_v1 = 4;
            } else {
                var_v1 = temp_t9;
            }
            StructOrg += var_v1;
        } else {
            binasm_rec.unk0 = sp54;
            binasm_rec.unk5_003F = 0x10;
            binasm_rec.unk8 = sp4C;
            binasm_rec.opt = sp50;
            put_binasmfyle();
        }
        if (Tokench == 0x23) {
            break;

            }
        }
}

static void func_0040D284(u8* arg0) {
    sym* cur_symbol;

    if (LookUp(arg0, &cur_symbol) == 0) {
        EnterSym(arg0, &cur_symbol, 0);
    }

    if ((cur_symbol->unk10 != 3) && (cur_symbol->unk10 != 4)) {
        posterror("", arg0, 1);
        return;
    }
    sym_define(cur_symbol->unk18, CurrentSegment, 0);

    binasm_rec.unk0 =   cur_symbol->unk18;
    binasm_rec.unk5_003F = ~0x3F; //just keep it

    if (list_extsyms != 0) {
        if (isdigit(*arg0)) {
            func_004054E8(cur_symbol->unk18, NULL);
        } else {
            func_004054E8(cur_symbol->unk18, arg0);
        }
    }
    put_binasmfyle();
}


void Parsestmt(void) {
    char sp38[0x400];
    sym* cur_symbol;
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
        binasm_rec.unk5_003F = 0x1C;
        binasm_rec.unk8 = CurrentFile;
        binasm_rec.opt = CurrentLine;
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
            func_0040AF00(temp_a0);
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
            Parse_option_directive();
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
            func_0040B5F0(temp_a0);
            break;
        case 0x1D:                  /* switch 1 */
        case 0x1E:                  /* switch 1 */
        case 0x24:                  /* switch 1 */
            func_0040C830(temp_a0);
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
            if(mednat != false) {
                func_0040A530();
            } else {
                 assertion_failed("false", "as0parse.c", 3537);
            }
            break;
        case ':':                  /* switch 1 */

        if (mednat != false) {
            binasm_rec.unk5_003F = ':';
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
static void func_0040E180(const char* arg0, s32 arg1, s32 arg2) {
    char dest[0x100];

    sprintf(&dest, arg0, arg1);
    postcerror(&dest, arg2);
}


int sym_undefined(int idn) {
    int sym_value, sym_sc, sym_st, index;

    st_sym_idn(idn, &sym_sc, &sym_st, &sym_value, &index);
    return sym_sc == false;
}

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040E230.s")

void func_0040E3F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    DNR* mP; //mld pointer
    struct RETst_pext_iext* temp_s0;

    mP = st_pdn_idn(arg0);
    if (mP->rfd != 0x7FFFFFFF) {
        postcerror("Expected global in data_localize", 0);
    }
    temp_s0 = st_pext_iext(mP->index);
    if ((arg1 == 0xE) || (arg1 == 6)) {
        postcerror("Expected non-Proc in data_localize", 0);
    }
    mP->index = st_symadd(st_stradd(st_str_extiss(temp_s0->unk_4)), arg3, arg1, arg2, 0xFFFFF);
    mP->rfd = st_currentifd();
    temp_s0->unkC_FC = 0;
    temp_s0->unkC_03E0 = 0;
}

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040E554.s")

//TODO.
static s32* func_0040E760(u32 arg0) {
    void* sp24;

    sp24 = malloc(arg0);
    if (sp24 == NULL) {
        perror("check_malloc");
        exit(2);
    }
    return sp24;
}


void sym_init(s32 arg0) {
    st_cuinit();
    D_10000024 = arg0 != 0;
}

void sym_finish(char* arg0, char* arg1) {
    s32 temp_a1;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 len;
    s32 i;

    if (arg1 == 0) {
        len = strlen(arg0);
        arg1 = strcpy(func_0040E760(len) + 3, arg0);
        if (arg0[len - 1] == 'G') {
            arg1[len - 1] = 'T';
        } else {
            strcat(arg1, ".T");
        }
    }
    for (i = 2; i < st_currentpchdr()->cdn; i++) {
        temp_a1 = st_sym_idn(i, &sp5C, &sp58, &sp60, &sp54);
        if (sp5C == 0) {
            if (sp58 == 0) {
                func_0040E230(i, 1, sp5C, sp60, 1);
            } else if ((sp58 != 1) && (sp58 != 6)) {
                func_0040E180("Symbol %s never defined", temp_a1, 1);
            }
        }
    }
    st_endallfiles();
    st_writebinary(arg1, -1);
}

s32 sym_define(s32 arg0, u32 arg1, s32 arg2) {
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    char* sp2C;

    sp2C = st_sym_idn(arg0, &sp38, &sp34, &sp3C, &sp30);
    switch (arg1) {
        case 5:
            if ((sp34 == 0) && (sp38 == 0)) {
                func_0040E554(arg0, 2, 5, sp3C, 1);
                break;
            }
            if ((sp34 == 1) && (sp38 == 0)) {
                func_0040E230(arg0, 1, 5, sp3C, 1);
                break;
            }
            func_0040E180("Conflicting definition of symbol %s", sp2C, 1);
            return 0;

        case 1:
            if ((sp34 == 0) && (sp38 == 0)) {
                func_0040E554(arg0, 5, 1, sp3C, 0);
                break;
            }
            if ((sp34 == 0xE) && (sp38 == 0)) {
                func_0040E554(arg0, 0xE, 1, sp3C, 1);
                st_procbegin(arg0);
                st_pdadd_idn(arg0);
                break;
            }
            if ((sp34 == 6) && (sp38 == 0)) {
                func_0040E230(arg0, 6, 0, sp3C, 1);
                st_procbegin(arg0);
                st_pdadd_idn(arg0);
                break;
            }
            if ((sp34 == 1) && (sp38 == 0)) {
                func_0040E230(arg0, 5, 1, sp3C, 0);
                break;
            }
            func_0040E180("Conflicting definition of symbol %s", sp2C, 1);
            return 0;

        case 2:
        case 13:
        case 15:
            if ((sp34 == 0) && (sp38 == 0)) {
                func_0040E3F0(arg0, 2, arg1, sp3C);
                break;
            }
            if ((sp34 == 1) && (sp38 == 0)) {
                func_0040E230(arg0, 1, arg1, sp3C, 1);
                break;
            }
            if ((sp34 == 1) && (sp38 == 0x11)) {
                func_0040E230(arg0, 1, arg1, sp3C, 1);
                break;
            }
            func_0040E180("Conflicting definition of symbol %s", (s32) sp2C, 1);
            return 0;

        case 17:
            if ((sp34 == 0) && (sp38 == 0)) {
                func_0040E230(arg0, 1, 0x11, arg2, 1);
                break;
            }
            if ((sp34 == 1) && (sp38 == 0)) {
                func_0040E230(arg0, 1, 0x11, arg2, 1);
                break;
            }
            if ((sp34 == 1) && (sp38 == 0x11)) {
                D_10000020 = 1;
                func_0040E230(arg0, 1, 0x11, arg2, 1);
                D_10000020 = 0;
                break;
            }
            func_0040E180("Cannot use .comm on previously defined symbol %s", (s32) sp2C, 1);
            return 0;

        case 33:
            if ((sp34 == 0) && (sp38 == 0)) {
                func_0040E3F0(arg0, 2, 0x11, arg2);
                break;
            }
            if ((sp34 == 1) && (sp38 == 0)) {
                func_0040E230(arg0, 1, 3, arg2, 1);
                break;
            }
            if ((sp34 == 1) && (sp38 == 3)) {
                D_10000020 = 1;
                func_0040E230(arg0, 1, 3, arg2, 1);
                D_10000020 = 0;
                break;
            }
            func_0040E180("Cannot use .lcomm on previously defined symbol %s", (s32) sp2C, 1);
            return 0;

        case 34:
            if ((sp34 == 0) && (sp38 == 0)) {
                func_0040E230(arg0, 1, 0, sp3C, 1);
                break;
            }
            if (((sp34 != 1) || (sp38 != 0)) && ((sp34 != 1) || (sp38 != 0x11))) {
                if ((sp34 == 0xE) && (sp38 == 0)) {
                    func_0040E230(arg0, 6, 0, sp3C, 1);
                    break;
                }
                func_0040E180(".globl must precede the definition of the symbol %s", sp2C, 1);
                return 0;
            }
            break;

        case 35:
            if ((sp34 == 0) && (sp38 == 0)) {
                func_0040E230(arg0, 0xE, 0, sp3C, 1);
                break;
            }
            if ((sp34 == 1) && (sp38 == 0)) {
                func_0040E230(arg0, 6, 0, sp3C, 1);
                break;
            }
            func_0040E180(".ent must precede the definition of the symbol %s", sp2C, 1);
            return 0;

        case 0:
            if ((sp34 == 0) && (sp38 == 0)) {
                return 1;
            }
            postcerror("scNil to scNil", NULL);
            return 0;

        default:
            postcerror("Internal: bad action in sym_define", NULL);
            return 0;
    }

    return 1;
}

//stub
void st_feinit() {


}

void itoa(s32 arg0, s8* dest) {
    sprintf(dest, "%d", arg0);
}

