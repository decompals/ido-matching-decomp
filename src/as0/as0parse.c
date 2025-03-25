/*
 * @file: as0parse.c
 *
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "common.h"
#include "binasm_rec.h"
#include "cmplrs/binasm.h" //Original binsasm file

extern struct {
    binasm_r* unk0;
    size_t unk4;
} rep_buffer;

struct unk_struct {
    int sym;
    struct unk_struct* next;
};

// external declarations
extern char isa;
extern int atflag;
extern FILE* extsyms_file;
extern int binasm_count;
extern sym* LastLabel;
extern sym* hashtable[0x80];
extern char Tokench;
extern char Tstring[0x400];
extern int gp_warn;
extern sym* reg_ptr[0x20];
extern int list_extsyms;
extern int Tstringlength;
extern int diag_flag;
extern char* sframereg;
extern char* sframesize;
extern int CurrentSegment;
extern int invent_locs;
extern int verbose;
extern int CurrentFile;
extern int CurrentLine;
extern int in_repeat_block;
extern size_t rep_size;
extern int mednat;
extern struct _struct_asm_info_0x8 asm_info[0x1AF];
extern char* sset_value[0x11];
extern int StructOrg;
extern int shftaddr;
extern int printedline;
extern unsigned int rep_count;
extern binasm_r binasm_rec;
extern int isStruct;

// as0parse.c
//.data
static char* D_10000004[4] = { "", "operand 1", "operand 2", "operand 3" };
int gform_extn = 0;
static struct unk_struct* D_10000014 = NULL;

//.bss
/* 029800 1000A800 */ int freg4;

// External declarations
extern int LookUp(char*, sym**);
extern void posterror(char* error, char* reg, int file_line);
extern void assertion_failed(const char* assertion, const char* file, int file_line);
extern void put_binasmfyle(void);
extern char* alloc_new_string(char*);
extern int hash(char*);
extern sym* alloc_new_sym(void);
extern int sym_enter(char* arg0, int arg1);
extern void nexttoken(void);
extern int GetExpr(void);
extern int sym_define(int arg0, unsigned int arg1, int arg2);
extern void GetItem(int* arg0, int* arg1);
extern void dw_GetItem(unsigned int* arg0, unsigned int* arg1, int* arg2);
extern int hex_to_num(char c);
extern int dw_GetExpr(unsigned int* high, unsigned int* low);
extern void EnterSym(char* arg0, sym** arg1, int arg2);
extern sym* GetRegister(void);
extern void GetBaseOrExpr(sym** arg0, int* arg1);
extern int sym_undefined(int arg0);
extern int st_procend(int);
extern void make_file(const char* filename);
extern void new_error(void);
extern void GetItem(int* arg0, int* arg1);
extern int which_opt(char* name);
extern void make_local_label(char* name, size_t* out_len);
extern int opLookUp(char* name, struct sym** arg1);
extern void call_name_and_line(int arg0);

// Function declaration (as0parse.c)
static void func_00405574(int arg0);
static void func_004055D4(char* symbol_name);
static void func_00404B80(int operand_index, int reg, int asm_index);
static void func_00405178(int arg0, int arg1, int arg2, int arg3, unsigned arg4, int arg5, int arg6);
static void func_004054E8(int arg0, char* arg1);
static void func_00405574(int arg0);
static void func_004055D4(char* symbol_name);
static void func_004056DC(char* arg0);
static void func_004058F0(int arg0);
static void func_00405A80(int* arg0, int* arg1);
static void func_00405B54(unsigned int* arg0, unsigned int* arg1, int* arg2);
static void func_00405C28(char* in, int in_len, unsigned int* hi_word, unsigned int* lo_word);
static void parse_idword(void);
static void func_004061F8(int arg0);
static void func_00406340(sym** arg0, unsigned int* arg1);
static void func_00406684(void);
static void func_00406728(int arg0);
static void func_00406C48(int arg0);
static void func_00406FE8(int arg0);
static void func_00407334(void);
static void func_004075CC(int arg0);
static void func_004076A0(int fasm);
static void func_00407A20(asmcodes asm_code);
static void func_0040848C(int arg0);
static void func_004085D8(int arg0);
static void func_004086EC(int arg0);
static void func_004088B8(int arg0);
static void func_00408C80(int arg0);
static int func_00409118(int* arg0);
static void func_004092FC(int arg0);
static void func_00409850(int arg0);
static void func_00409B10(int arg0);
static void func_00409ECC(int arg0);
static void func_00409FD0(int arg0);
static void func_0040A044(int arg0);
static void func_0040A0D4(void);
static void parse_cpalias(void);
static void parse_verstamp(void);
static void func_0040A280(void);
static void func_0040A4B0(void);
static void func_0040A530(void);
static void func_0040A5D4(void);
static void func_0040A6B8(unsigned int arg0);
static void func_0040A79C(int arg0);
static void func_0040A958(void);
static void func_0040AAD4(int arg0);
static void func_0040ADFC(void);
static void func_0040AF00(itype iop);
static void func_0040B0F4(int arg0);
static void func_0040B340(void);
int do_dot_end(int arg0);
static void func_0040B554(int arg0);
static void func_0040B5F0(int arg0);
static void func_0040B984(void);
static void func_0040BC84(void);
static int func_0040BEBC(int* arg0, int* arg1, int* arg2);
static void func_0040C048(void);
static void func_0040C218(void);
static void func_0040C2E0(void);
static void func_0040C360(void);
static void func_0040C3E0(void);
static void func_0040C460(void);
static void func_0040C4CC(void);
static void func_0040C5E8(int arg0);
static void parse_repeat(int arg0, int arg1);
static void func_0040C830(int arg0);
static void func_0040C928(void);
static void parse_option(void);
static int func_0040CC44(char* name);
static void parse_set(void);
static void func_0040CDE4(int arg0);
static void func_0040CEB4(void);
static void func_0040CF9C(void);
static void func_0040D110(void);
static void func_0040D284(char* arg0);

static void func_00404B80(int operand_index, int reg, int asm_index) {
    unsigned var_v0;

    switch (operand_index) {                                 /* switch 1; irregular */
    default:                                        /* switch 1 */
    case 1:                                         /* switch 1 */
        var_v0 = asm_info[asm_index].unk4 << 0x11 >> 0x1B;
        break;
    case 2:                                         /* switch 1 */
        var_v0 = asm_info[asm_index].unk4 << 0x16 >> 0x1B;
        break;
    case 3:                                         /* switch 1 */
        var_v0 = asm_info[asm_index].unk4 & 0x1F;
        break;
    }
    switch (var_v0) {
    case 0: break;
    case 1:
        if ((atflag != 0) && (reg == 1)) {
            posterror("Used $at without .set noat",D_10000004[operand_index], 2);
        } else if ((reg < 0) || (reg >= 0x20)) {
            posterror("Should be gp register",D_10000004[operand_index], 1);
        }
        break;
    case 2:
        if ((isa < ISA_MIPS3) && ((reg < 0) || (reg >= 0x20) || (reg & 1))) {
            posterror("Should be even gp register",D_10000004[operand_index], 1);
        }
        break;
    case 3:
        if (((reg < 0) || (reg >= 0x20)) && (reg != 0x48)) {
            posterror("Should be gp register",D_10000004[operand_index], 1);
        } else if (atflag != 0) {
            if (reg == 1) {
            posterror("Used $at without .set noat",D_10000004[operand_index], 2);
            }
        }
        break;
    case 7:
        if ((reg < 0) || (reg >= 0x20)) {
            posterror("Should be coprocessor register",D_10000004[operand_index], 1);
        }
        break;
    case 8:
        if ((isa < ISA_MIPS3) && ((reg < 0) || (reg >= 0x20) || (reg & 1))) {
            posterror("Should be even coprocessor register",D_10000004[operand_index], 1);
        }
        break;
    case 4:
        if ((reg < 0x20) || (reg >= 0x40)) {
            posterror("Should be floating point register",D_10000004[operand_index], 1);
        }
        break;
    case 5:
        #ifdef IDO_71
        if ((reg < 0x20) || (reg >= 0x40)) {
            posterror("Should be floating point register", D_10000004[operand_index], 1);
        } else if ((isa < 3) && (reg & 1)) {
            posterror("Should be even floating point register", D_10000004[operand_index], 1);
        }
        #else
        if (isa < ISA_MIPS3) {
            if ((reg < 0x20) || (reg >= 0x40) || (reg & 1)) {
                posterror("Should be even floating point register", D_10000004[operand_index], 1);
            }
        }
        #endif
        break;
    case 6:
        #ifdef IDO_71
        if ((reg < 0x20) || (reg >= 0x40)) {
            posterror("Should be floating point register",D_10000004[operand_index], 1);
        } else if ((isa >= ISA_MIPS3) && (reg & 1)) {
            posterror("Should be even floating point register",D_10000004[operand_index], 1);
        } else if ((isa < ISA_MIPS3) && (reg & 3)) {
            posterror("Should be multiple-of-4 floating point register",D_10000004[operand_index], 1);
        }
        #else
        if (isa >= ISA_MIPS3) {
            if ((reg < 0x20) || (reg >= 0x40) || (reg & 1)) {
                posterror("Should be even floating point register", D_10000004[operand_index], 1);
            }
        } else if ((reg < 0x20) || (reg >= 0x40) || (reg & 3)) {
            posterror("Should be multiple-of-4 floating point register", D_10000004[operand_index], 1);
        }
        #endif
        break;
    case 9:
        if ((isa < ISA_MIPS3) && (reg >= 0x20) && (reg & 1)) {
            posterror("Should be fp double or gp single register", D_10000004[operand_index], 1);
        }
        break;
    case 10:
        if ((isa < ISA_MIPS3) && (reg & 1)) {
            posterror("Should be multiple-of-2 register", D_10000004[operand_index], 1);
        }
        break;
    case 11:
        if (isa >= ISA_MIPS3) {
            if (reg & 1) {
                posterror("Should be multiple-of-2 register", D_10000004[operand_index], 1);
            }
        } else if (reg & 3) {
            posterror("Should be multiple-of-4 register", D_10000004[operand_index], 1);
        }
        break;
    case 12:
        if ((reg < 0x40) || (reg >= 0x48)) {
            posterror("Should be floating point condition code register", D_10000004[operand_index], 1);
        }
        break;
    }
}

static void func_00405178(int arg0, int arg1, int arg2, int arg3, unsigned arg4, int arg5, int arg6) {
    binasm_rec.unk0 = arg0;
    binasm_rec.unk5_003F = 0x17; // asm_type
    binasm_rec.unk6_03FE = arg1;
    binasm_rec.unk8_FE = arg2;
    binasm_rec.unk8_01FC = arg3;
    binasm_rec.unk8_0003C000 = arg4;
    binasm_rec.unk4_01C0 = gform_extn;
    if (gform_extn != 0) {
        binasm_rec.unkC = arg6;
    }

    switch (arg4) {
        case 15:
            binasm_rec.unkB_007F = freg4;
            func_00404B80(3, freg4, arg1);
        case 3:
            binasm_rec.unkA_3F80 = arg5;
            func_00404B80(1, arg2, arg1);
            func_00404B80(2, arg3, arg1);
            func_00404B80(3, arg5, arg1);
            break;

        case 6:
            binasm_rec.unkC = arg6;
            break;

        case 2:
            if (arg2 != 0x48) {
                func_00404B80(1, arg2, arg1);
            }
            binasm_rec.unkC = arg6;
            break;

        case 14:
            if (arg3 != 0x48) {
                func_00404B80(2, arg3, arg1);
            }
            binasm_rec.unkC = arg6;
            break;

        case 0:
        case 1:
        case 4:
            func_00404B80(1, arg2, arg1);
            func_00404B80(2, arg3, arg1);
            binasm_rec.unkC = arg6;
            break;

        case 12:
            func_00404B80(1, arg2, arg1);
            binasm_rec.unkC = arg6;
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
            binasm_rec.unkC = arg6;
            break;

        case 10:
        case 11:
            break;

        default:
            #ifdef IDO_71
            assertion_failed("false", "as0pasre.c", 241);
            #else
            assertion_failed("false", "as0parse.c", 237);
            #endif
            break;
    }
    put_binasmfyle();
}

static void func_004054E8(int arg0, char* arg1) {
    fprintf(extsyms_file, "%1d %1d", binasm_count, arg0);
    fprintf(extsyms_file, " %s\n", arg1 ? arg1 : "");
}

static void func_00405574(int arg0) {
    sym* var_v0;

    StructOrg = (((int)StructOrg + (1 << arg0) - 1) >> arg0) << arg0;

    for (var_v0 = LastLabel; var_v0 != NULL; var_v0 = var_v0->unkC) {
        var_v0->unk8 = StructOrg;
    }
    LastLabel = NULL;
}

static void func_004055D4(char* symbol_name) {
    sym* cur_symbol;
    int hash_sym;

    if (LookUp(symbol_name, &cur_symbol)) {
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
    int sp28;
    int sp24 = LookUp(arg0, &sp2C);

    // If the sym is not in the hastable add it
    if (sp24 == FALSE) {
        sp28 = hash(arg0);
        sp2C = alloc_new_sym();

        sp2C->next = hashtable[sp28];
        sp2C->name = alloc_new_string(arg0);
        sp2C->unk10 = 4;
        sp2C->reg = 1;
        sp2C->unk18 = sym_enter(arg0, 0);
        hashtable[sp28] = sp2C;
    }

    // Define symbol

    sp2C->unkC = 0;
    sp2C->unk10 = 4;
    nexttoken();
    sp2C->unk8 = GetExpr();
    sym_define(sp2C->unk18, 5U, sp2C->unk8);

    if (sp24) {
        binasm_rec.unk0 = sp2C->unk18;
        binasm_rec.unk5_003F = 0x29;
        binasm_rec.unk8 = sp2C->unk8;
        put_binasmfyle();
    }
}

static int parse_break(void) {
    int range = GetExpr();

    if ((range < 0) || (range > 0x3FF)) {
        posterror("break operand out of range", NULL, 1);
        return 0;
    }
    return range;
}

static void func_004058F0(int arg0) {
    int sp34;
    int var_v1;
    int a[5];

    if (arg0 != zbreak) {
        if (arg0 == znada) {
            func_00405178(0, 2, 0, 0, 3, 0, 0);
            return;
        }
        if (arg0 == zssnop) {
            func_00405178(0, 0x4F, 0, 0, 4, 0x48, 1);
            return;
        }
        func_00405178(0, arg0, 0x48, 0x48, 2, 0x48, 0);
        return;
    }
    sp34 = parse_break();
    if (Tokench == '#') {
        var_v1 = 0;
    } else {
        var_v1 = parse_break();
    }
    func_00405178(0, arg0, 0x48, 0x48, 0xD, 0x48, (var_v1 << 0xA) + sp34);
}

static void func_00405A80(int* arg0, int* arg1) {
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

static void func_00405B54(unsigned int* arg0, unsigned int* arg1, int* arg2) {
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

static void func_00405C28(char* in, int in_len, unsigned int* hi_word, unsigned int* lo_word) {
    char buf[0x10]; // sp48
    int i;

    if (in_len > 0x10) {
        in_len = 0x10;
    }

    for (i = 0; i < in_len; i++) {
        buf[i + 16 - in_len] = in[i];
    }
    for (i = 0; i < 16 - in_len; i++) {
        buf[i] = '0';
    }

    *hi_word = 0;
    *lo_word = 0;

    for (i = 0; i < 8; i++) {
        *hi_word = *hi_word * 16 + hex_to_num(buf[i]);
    }
    for (i = 8; i < 0x10; i++) {
        *lo_word = *lo_word * 16 + hex_to_num(buf[i]);
    }
}

static int parse_id_expr(int* arg0, unsigned int* arg1, unsigned int* arg2, int* arg3) {
    sym* sp2C;

    if (Tokench == 'i') {
        if (!LookUp(&Tstring[0], &sp2C)) {
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

static void parse_idword(void) {
    int sp54;
    int sp50;
    unsigned int sp4C;
    unsigned int sp48;
    int var_v1;

    if (LastLabel != NULL) {
        func_00405574(2);
    }

    while (TRUE) {
        sp4C = 0;
        sp48 = 0;
        sp50 = 1;
        sp54 = 0;

        if (parse_id_expr(&sp54, &sp4C, &sp48, &sp50) == 0) {
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
            binasm_rec.unk5_003F = idword;
            binasm_rec.unk8 = sp4C;
            binasm_rec.unkC = sp50;
            put_binasmfyle();
            binasm_rec.unk0 = sp54;
            binasm_rec.unk5_003F = idword;
            binasm_rec.unk8 = sp48;
            binasm_rec.unkC = sp50;
            put_binasmfyle();
        }
        if (Tokench == '#') {
            break;
        }
    }
}

static void func_004061F8(int arg0) {
    sym* sp3C;
    unsigned int sp38 = 0;
    unsigned int sp34 = 0;

    sp3C = GetRegister();
    if (sp3C != NULL) {
        if (Tokench == '"') {
            func_00405C28(&Tstring[0], strlen(&Tstring[0]), &sp38, &sp34); // TODO: warning !!
        } else {
            dw_GetExpr(&sp38, &sp34);
        }
        func_00405178(0, arg0, sp3C->reg, 0x48, 2, 0x48, sp38);
        func_00405178(0, arg0, sp3C->reg, 0x48, 2, 0x48, sp34);
        nexttoken();
    }
}

static void func_00406340(sym** arg0, unsigned int* arg1) {
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

    nexttoken();
    if (Tokench != '(') {
        posterror("%hi/%lo/%gprel not followed by (", NULL, 1);
        return;
    }

    nexttoken();
    if (Tokench == 'i') {
        if (LookUp(Tstring, arg0) == 0) {
            EnterSym(Tstring, arg0, 1);
            if (gp_warn != 0) {
                posterror("Load/Store of undefined symbol", (*arg0)->name, 2);
            }
        }

        if ((*arg0)->unk10 == 4) {
            *arg0 = NULL;
        } else if ((*arg0)->unk10 == 3) {
            nexttoken();
            if ((Tokench != '+') && (Tokench != '-') && (Tokench != ')')) {
                posterror("invalid expression with %hi/%lo", Tstring, 1);
                return;
            }
        }
    }

    if ((Tokench == '+') || (Tokench == '-') || (Tokench == 'i')) {
        *arg1 = GetExpr();
    }
    if (Tokench != ')') {
        posterror("')' expected", Tstring, 1);
        return;
    }
    nexttoken();
}

static void func_00406684(void) {
    nexttoken();
    if (Tokench != 'd') {
        posterror("invalid memory tag", NULL, 1);
        return;
    }
    binasm_rec.unkA_3FFF = GetExpr();
}

static void func_00406728(int arg0) {
    int unused;
    sym* sp50;
    unsigned int sp4C;
    unsigned int sp48;
    sym* sp44;
    int sp40;
    struct sym* temp_v0;

    sp4C = 0;
    sp50 = NULL;
    if ((temp_v0 = GetRegister()) == NULL) {
        return;
    }
    sp40 = temp_v0->reg;
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
        if (LookUp(Tstring, &sp44) == 0) {
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
            if ((Tokench != '+') && (Tokench != '-') && (Tokench != '(') && (Tokench != '#')) {
                posterror("invalid external expression", NULL, 1);
                return;
            }
        }
    }
    if (Tokench == '%') {
        func_00406340(&sp44, (unsigned int*)&sp4C);
    }
    if (((Tokench == 'i') || (Tokench == 'd') || (Tokench == 'h') || (Tokench == '+') || (Tokench == '-') ||
         (Tokench == '~') || (Tokench == '"') || (Tokench == '(')) &&
        (GetBaseOrExpr(&sp50, (int*)&sp4C), (sp50 == NULL)) && (Tokench == '(')) {
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
    if (sp44 == NULL) {
        if (sp50 == NULL) {
            sp50 = reg_ptr[0];
        }
    }
    if (sp44 != NULL) {
        if (list_extsyms != 0) {
            func_004054E8(sp44->unk18, Tstring); // TODO: Check if matches
        }
        if (sp50 == NULL) {
            func_00405178(sp44->unk18, arg0, sp40, 0x48, 1, 0x48, sp4C);
        } else {
            func_00405178(sp44->unk18, arg0, sp40, sp50->reg, 1, 0x48, sp4C);
        }
    } else {
        func_00405178(0, arg0, sp40, sp50->reg, 0, 0x48, sp4C);
    }
    gform_extn = 0;
}

static void func_00406C48(int arg0) {
    int pad4C;
    sym* sp48;
    int sp44;
    int sp40; // u32?
    sym* sp3C;
    int pad38;

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
            if ((Tokench != '+') && (Tokench != '-') && (Tokench != '(') && (Tokench != '#')) {
                posterror("invalid external expression", NULL, 1);
                return;
            }
        }
    }
    if ((Tokench == 'i') || (Tokench == 'd') || (Tokench == 'h') || (Tokench == '+') || (Tokench == '-') ||
        (Tokench == '~') || (Tokench == '"') || (Tokench == '(')) {
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
            sp48 = reg_ptr[0];
        }
    }
    sp40 &= 0xFFFF;
    if (sp3C != NULL) {
        if (sp48 == NULL) {
            func_00405178(sp3C->unk18, arg0, sp44, 0x48, 0xE, 0x48, sp40);
        } else {
            func_00405178(sp3C->unk18, arg0, sp44, sp48->reg, 0xE, 0x48, sp40);
        }
    } else {
        func_00405178(0, arg0, sp44, sp48->reg, 0xE, 0x48, sp40);
    }
}

static void func_00406FE8(int arg0) {
    sym* sp3C;
    int sp38 = 0;
    sym* sp34;

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
        } else if (sp34->unk10 == 3) {
            nexttoken();
            if ((Tokench != '+') && (Tokench != '-') && (Tokench != '(') && (Tokench != '#')) {
                posterror("invalid external expression", NULL, 1);
                return;
            }
        }
    }

    if ((Tokench != 'i') && (Tokench != 'd') && (Tokench != 'h') && (Tokench != '+') && (Tokench != '-') &&
        (Tokench != '~') && (Tokench != '"') && (Tokench != '(')) {
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
            func_00405178(sp34->unk18, arg0, 0x48, sp3C->reg, 1, 0x48, sp38);
        }
    } else {
        func_00405178(0, arg0, 0x48, sp3C->reg, 0, 0x48, sp38);
    }
}

static void func_00407334(void) {
    unsigned int var_s1;
    int var_s5;
    int var_v0;
    unsigned int temp_s6;
    char sp50[0x400];
    unsigned* temp = &binasm_rec.unk8;

    var_s5 = 0;
    if (Tokench == '-') {
        var_s5 = 1;
        nexttoken();
    } else if (Tokench == '+') {
        nexttoken();
    }

    if (Tokench != 'f') {
        posterror("floating point constant expected", NULL, 1);
        if (Tokench != '#') {
            nexttoken();
        }
        return;
    }

    temp_s6 = Tstringlength;
    strcpy(sp50, Tstring);
    nexttoken();

    if (binasm_rec.unk5_003F == 0x17) {
        func_00405178(0, binasm_rec.unk6_03FE, binasm_rec.unk8_FE, 0x48, 2, 0x48, var_s5 + temp_s6);
    } else {
        *temp = var_s5 + temp_s6;
        if (Tokench == ':') {
            nexttoken();
            binasm_rec.unkC = GetExpr();
        } else {
            binasm_rec.unkC = 1;
        }
        put_binasmfyle();
    }

    var_v0 = sizeof(binasm_rec);
    for (var_s1 = 0; var_s1 < temp_s6; var_s1++) {
        if (var_v0 == sizeof(binasm_rec)) {
            if (var_s1 != 0) {
                put_binasmfyle();
            }
            if (var_s5) {
                binasm_rec.arr0[0] = '-';
                var_s5 = 0;
                var_v0 = 1;
            } else {
                var_v0 = 0;
            }
        }
        binasm_rec.arr0[var_v0] = sp50[var_s1];
        var_v0++;
    }

    put_binasmfyle();
}

static void func_004075CC(int arg0) {
    sym* temp_v0;

    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x17;
    binasm_rec.unk6_03FE = arg0;
    temp_v0 = GetRegister();
    if (temp_v0 != NULL) {
        binasm_rec.unk8_FE = temp_v0->reg;
    }
    binasm_rec.unk8_01FC = 0x48;
    binasm_rec.unk8_0003C000 = 2;
    func_00407334();
}

static void func_004076A0(int fasm) {
    sym* pad;
    int sp48;
    sym* sp44;
    unsigned int sp40;
    int var_a0;
    unsigned int sp38;
    unsigned int sp34;
    struct sym* sp30;
    sp40 = 0;
    sp44 = NULL;
    sp30 = NULL;

    pad = GetRegister();
    if (pad != NULL) {
        sp48 = pad->reg;

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
                #ifdef IDO_71
                assertion_failed("fasm == zli", "as0parse.c", 1098);
                #else
                assertion_failed("fasm == zli", "as0parse.c", 1094);
                #endif
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

        if ((fasm == zlui) && (sp30 != NULL)) {
            func_00405178(var_a0, fasm, sp48, sp30->reg, 4, 0x48, sp40);
        } else {
            func_00405178(var_a0, fasm, sp48, 0x48, 2, 0x48, sp40);
        }
        gform_extn = 0;
    }
}

static void func_00407A20(asmcodes asm_code) {
    sym* sp5C;
    sym* sp58;
    sym* sp54;
    sym* sp50;
    sym* sp4C;
    int has_immed; // sp+48
    int immed_lo; // sp+44
    int immed_hi; // sp+40
    int outside_int32; // sp+3C
    int temp_atflag; // sp+38

    immed_lo = 0;
    sp54 = NULL;
    sp50 = NULL;
    outside_int32 = 0;

    if ((sp5C = GetRegister()) == NULL) {
        return;
    }

    if ((Tokench == 'i') && LookUp(Tstring, &sp58) && (sp58->unk10 == 0)) {
        sp54 = sp58;
        nexttoken();
        if (Tokench == ',') {
            nexttoken();
        }
        if ((Tokench == 'i') && LookUp(Tstring, &sp58) && (sp58->unk10 == 0)) {
            sp50 = sp58;
            nexttoken();
        }
    }

    has_immed = 0;
    if (sp50 == NULL) {
        if (Tokench == '%') {
            if (sp54 == NULL) {
                posterror("invalid syntax in statement", NULL, 1);
                return;
            }
            func_00406340(&sp4C, &immed_lo);
            func_00405178(((sp4C != NULL) ? sp4C->unk18 : 0), asm_code, sp5C->reg, sp54->reg, 4, 0x48, immed_lo);
            gform_extn = 0;
            return;
        }

        if ((Tokench == 'i') || (Tokench == 'd') || (Tokench == 'h')
            || (Tokench == '+') || (Tokench == '-') || (Tokench == '~')
            || (Tokench == '"') || (Tokench == '(')) {
            if (isa <= 2) {
                immed_lo = GetExpr();
            } else {
                outside_int32 = dw_GetExpr(&immed_hi, &immed_lo);
            }
            if (sp54 == NULL) {
                sp54 = sp5C;
            }
            has_immed = 1;
        } else {
            if (isa >= 2) {
                switch (asm_code) {
                    case zmovt:
                    case zmovf:
                    case fmovt_s:
                    case fmovt_d:
                    case fmovf_s:
                    case fmovf_d:
                        func_00405178(0, asm_code, sp5C->reg, sp54->reg, 3, 0x40, 0);
                        return;

                    case ztrunc_w_s:
                    case ztrunc_w_d:
                    case ztrunc_w_e:
                    case zround_w_s:
                    case zround_w_d:
                    case zround_w_e:
                    case zceil_w_s:
                    case zceil_w_d:
                    case zceil_w_e:
                    case zfloor_w_s:
                    case zfloor_w_d:
                    case zfloor_w_e:
                    case ztrunc_l_s:
                    case zround_l_s:
                    case zceil_l_s:
                    case zfloor_l_s:
                    case ztrunc_l_d:
                    case zround_l_d:
                    case zceil_l_d:
                    case zfloor_l_d:
                    case ztrunc_l_e:
                    case zround_l_e:
                    case zceil_l_e:
                    case zfloor_l_e:
                        func_00405178(0, asm_code, sp5C->reg, sp54->reg, 5, 0x48, 0);
                        return;

                    default:
                        break;
                }
            }
            sp50 = sp54;
            sp54 = sp5C;
        }
    }

    if ((sp54 == NULL) || ((sp50 == NULL) && !has_immed)) {
        posterror("invalid syntax in statement", NULL, 1);
        return;
    }

    switch (asm_code) {
        case zrol:
        case zror:
        case zsll:
        case zsra:
        case zsrl:
            if (has_immed && ((immed_lo < 0) || (immed_lo > 31) || outside_int32)) {
                posterror("shift amount not 0..31", NULL, 1);
                return;
            }
            break;

        case zdsll:
        case zdsrl:
        case zdsra:
        case zdrol:
        case zdror:
            if (has_immed && ((immed_lo < 0) || (immed_lo > 63) || outside_int32)) {
                posterror("shift amount not 0..63", NULL, 1);
                return;
            }
            break;

        case zdsll32:
        case zdsrl32:
        case zdsra32:
            if (has_immed && ((immed_lo < 0) || (immed_lo > 31) || outside_int32)) {
                posterror("shift amount not 0..31", NULL, 1);
                return;
            }
            immed_lo += 32;
            if (asm_code == zdsll32) {
                asm_code = zdsll;
            } else if (asm_code == zdsrl32) {
                asm_code = zdsrl;
            } else { // zdsra32
                asm_code = zdsra;
            }
            break;

        case zaddi:
        case zaddiu:
        case zslti:
        case zsltiu:
        case zandi:
        case zori:
        case zxori:
        case zdaddi:
        case zdaddiu:
            if (!has_immed) {
                posterror("operation needs immed operand", NULL, 1);
                return;
            }

            if ((asm_code == zandi) || (asm_code == zori) || (asm_code == zxori)) {
                if ((immed_lo > 65535) || (immed_lo < 0) || outside_int32) {
                    // range of UINT16
                    posterror("immed operand not -0..65535", NULL, 1);
                }
            } else {
                if ((immed_lo < 0x10000) && (immed_lo >= 0x8000)) {
                    immed_lo += 0xFFFF0000;
                }
                if ((immed_lo > 32767) || (immed_lo < -32768) || outside_int32) {
                    // range of INT16
                    posterror("immed operand not -32768..32767", NULL, 1);
                }
            }
            break;

        case fadd_s:
        case fadd_d:
        case fadd_e:
        case fsub_s:
        case fsub_d:
        case fsub_e:
        case fmul_s:
        case fmul_d:
        case fmul_e:
        case fdiv_s:
        case fdiv_d:
        case fdiv_e:
        case ztrunc_w_s:
        case ztrunc_w_d:
        case ztrunc_w_e:
        case zround_w_s:
        case zround_w_d:
        case zround_w_e:
        case zceil_w_s:
        case zceil_w_d:
        case zceil_w_e:
        case zfloor_w_s:
        case zfloor_w_d:
        case zfloor_w_e:
            if (has_immed) {
                posterror("immed operand not allowed on fp ", NULL, 1);
            }
        break;
        #ifdef IDO_71
        case zmovt:
        case zmovf:
        case fmovt_s:
        case fmovt_d:
        case fmovf_s:
        case fmovf_d:
        if (has_immed != 0) {
            posterror("immed operand not allowed for cc ", NULL, 1);
        }
        #endif
        break;

        default: 
            break;
    }

    if (has_immed) {
        temp_atflag = atflag;
        if (outside_int32) {
            switch (asm_code){
                case zadd:
                case zaddu:
                case zdiv:
                case zdivu:
                case zmul:
                case zmulo:
                case zmulou:
                case zrem:
                case zremu:
                case zsub:
                case zsubu:
                    posterror("Immediate value out of range", NULL, 1);
                    break;

                default:
                    break;
            }
            if (!temp_atflag) {
                posterror("macro expansion needs at register after .set noat", NULL, 1);
            }
            atflag = 0;
            func_00405178(0, 0x14C, 1, 0x48, 2, 0x48, immed_hi);
            func_00405178(0, 0x14C, 1, 0x48, 2, 0x48, immed_lo);
            func_00405178(0, asm_code, sp5C->reg, sp54->reg, 3, 1, 0);
            atflag = temp_atflag;
        } else {
            func_00405178(0, asm_code, sp5C->reg, sp54->reg, 4, 0x48, immed_lo);
        }
    } else {
        func_00405178(0, asm_code, sp5C->reg, sp54->reg, 3, sp50->reg, 0);
    }
}

static void func_0040848C(int arg0) {
    struct sym* var_t0;
    struct sym* var_v1;
    int pad;
    int var_a2;

    if ((var_t0 = GetRegister()) == NULL) {
        return;
    }

    if (Tokench != '#') {
        if ((var_v1 = GetRegister()) == NULL) {
            return;
        }
    } else {
        var_v1 = var_t0;
    }

    if ((arg0 >= fc_f_s) && (arg0 < zlui)) {
        var_a2 = 0x40;
        if (Tokench != '#') {
            var_a2 = var_t0->reg;
            var_t0 = var_v1;
            if ((var_v1 = GetRegister()) == NULL) {
                return;
            }
        }
        func_00405178(0, arg0, var_a2, var_t0->reg, 3, var_v1->reg, 0);
    } else {
        func_00405178(0, arg0, var_t0->reg, var_v1->reg, 5, 0x48, 0);
    }
}

static void func_004085D8(int arg0) {
    sym* reg1; // sp3C
    sym* reg2; // sp38
    sym* reg3; // sp34
    sym* reg4;

    if ((reg1 = GetRegister()) == NULL) {
        return;
    }
    if ((reg2 = GetRegister()) == NULL) {
        return;
    }
    if ((reg3 = GetRegister()) == NULL) {
        return;
    }
    if (Tokench != '#') {
        if ((reg4 = GetRegister()) == NULL) {
            return;
        }
    } else {
        reg4 = reg3;
        reg3 = reg2;
        reg2 = reg1;
    }

    freg4 = reg4->reg;
    func_00405178(0, arg0, reg1->reg, reg2->reg, 0xF, reg3->reg, 0);
}

static void func_004086EC(int arg0) {
    sym* reg1; // sp+44?
    sym* reg2; // sp+40
    sym* reg3; // sp+3C
    int sp38;
    int sp34;

    if (arg0 == zpfetch) {
        sp38 = GetExpr();
        if ((sp38 < 0) || (sp38 > 31)) {
            posterror("hint field not in range 0..31", NULL, 2);
        }
        sp34 = sp38 & 0x1F;
    } else {
        if ((reg1 = GetRegister()) == NULL) {
            return;
        }
        sp34 = reg1->reg;
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
    func_00405178(0, arg0, sp34, reg3->reg, 3, reg2->reg, 0);
}

static void func_004088B8(int arg0) {
    sym* sp4C;
    sym* sp48;
    sym* sp44;
    int sp40;
    unsigned int sp3C;
    int sp38;
    int sp34;

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

    if ((Tokench == 'i') || (Tokench == 'd') || (Tokench == 'h') || (Tokench == '+') || (Tokench == '-') ||
        (Tokench == '~') || (Tokench == '"') || (Tokench == '(')) {
        if (isa <= ISA_MIPS2) {
            sp38 = 0;
            sp40 = GetExpr();
        } else {
            sp38 = dw_GetExpr(&sp3C, (unsigned int*)&sp40);
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
            func_00405178(0, arg0, sp4C->reg, 1, 4, 0x48, 8);
            atflag = sp34;
        } else if (sp48 != NULL) {
            func_00405178(0, arg0, sp4C->reg, sp48->reg, 4, 0x48, sp40);
        } else {
            func_00405178(0, arg0, sp4C->reg, 0x48, 2, 0x48, sp40);
        }
    } else if (sp48 == NULL) {
        posterror("invalid syntax in statement", NULL, 1);
    } else {
        func_00405178(0, arg0, sp4C->reg, sp48->reg, 4, 0x48, 8);
    }
}

static void func_00408C80(int arg0) {
    struct sym* sp54;
    struct sym* sp50;
    int sp4C;
    int sp48;
    int i;
    sym* sp38[3];

    if (arg0 == zjr) {
        arg0 = zj;
    } else if (arg0 == zjalr) {
        arg0 = zjal;
    }

    sp4C = 0;
    sp54 = NULL;
    sp48 = 0x48;
    sp50 = NULL;

    if (Tokench == 'i') {
        if (!LookUp(Tstring, &sp50)) {
            EnterSym(Tstring, &sp50, 1);
        }

        if (sp50->unk10 == 3) {
            if (list_extsyms) {
                func_004054E8(sp50->unk18, Tstring);
            }
            nexttoken();
            sp38[1] = NULL;

            if ((Tokench != '+') && (Tokench != '-') && (Tokench != '#') && (Tokench != ',')) {
                posterror("invalid external expression", NULL, 1);
                return;
            }

            if (Tokench != '#') {
                if (Tokench != ',') {
                    sp4C = GetExpr();
                }

                if (Tokench != '#') {
                    if (Tokench == ',') {
                        nexttoken();
                    }

                    if (((sp38[1] = GetRegister()) == NULL) || (Tokench == '#')) {
                        if (Tokench == '#') {
                            posterror("stmt extends past logical end", NULL, 1);
                        }
                        return;
                    }

                    if (((sp38[2] = GetRegister()) == NULL) || (Tokench != '#')) {
                        return;
                    }
                }
            }
        } else if (sp50->unk10 == 0) {
            nexttoken();
            sp54 = sp50;
            sp50 = NULL;

            if (arg0 == zjal) {
                if (Tokench != '#') {
                    if (Tokench != ',') {
                        return;
                    }
                    nexttoken();
                    i = 0;
                    do {
                        i++;
                        if ((sp38[i] = GetRegister()) == NULL) {
                            return;
                        }
                    } while ((i != 3) && (Tokench != '#'));

                    if (i != 2) {
                        sp48 = sp54->reg;
                        sp54 = sp38[1];
                        if (sp48 == sp54->reg) {
                            posterror("JAL should not use same register twice", Tstring, 2);
                        }
                    }
                }
            }
        } else {
            if (sp50->unk10 == 4) {
                sp50 = NULL;
                sp4C = GetExpr();
            } else {
                posterror("invalid symbol for address", Tstring, 1);
                return;
            }
        }
    } else {
        sp4C = GetExpr();
    }

    if (sp54 != NULL) {
        func_00405178(0, arg0, sp54->reg, sp48, 7, 0x48, 0);
    } else if (sp50 != NULL) {
        func_00405178(sp50->unk18, arg0, 0x48, 0x48, 6, 0x48, sp4C);
    } else {
        func_00405178(0, arg0, 0x48, 0x48, 6, 0x48, sp4C);
    }
}

static int func_00409118(int* arg0) {
    int var_v1;
    int var_v1_2;
    int temp_v0;

    if ((Tstringlength != 1) || (Tstring[0] != '.')) {
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
        var_v1_2 = (temp_v0 - 4) / 4;
    }
    *arg0 = var_v1_2;
    return 1;
}

static void func_004092FC(int arg0) {
    sym* sp5C;
    sym* sp58;
    sym* sp54;
    sym* sp50;
    int sp4C;
    int sp48;
    int sp44;
    int sp40;
    int sp3C;
    int sp38;
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
        if ((Tokench == 'i') || (Tokench == 'd') || (Tokench == 'h') || (Tokench == '+') || (Tokench == '-')) {
            if (isa < 3) {
                sp40 = 0;
                sp48 = GetExpr();
            } else {
                sp40 = dw_GetExpr((unsigned int*)&sp3C, (unsigned int*)&sp48);
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
            func_00405178(0, arg0, sp5C->reg, 0x48, 0xC, 0x48, sp48);
        } else {
            func_00405178(0, arg0, sp5C->reg, sp58->reg, 8, 0x48, 0);
        }
        gform_extn = 0;
        return;
    }
    if (LookUp(Tstring, &sp50) != 0) {
        if (sp50->unk10 == 3) {
            sp54 = sp50;
        } else {
            posterror("symbol is not a label", Tstring, 1);
            return;
        }
    } else {
        EnterSym(Tstring, &sp54, 1);
    }

    if (list_extsyms != 0) {
        if (isdigit(Tstring[0])) {
            func_004054E8(sp54->unk18, NULL);
        } else {
            func_004054E8(sp54->unk18, Tstring);
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
            func_00405178(sp54->unk18, arg0, sp5C->reg, 1, 8, 0x48, 0);
            atflag = sp38;
        } else {
            func_00405178(sp54->unk18, arg0, sp5C->reg, 0x48, 0xC, 0x48, sp48);
        }
    } else {
        func_00405178(sp54->unk18, arg0, sp5C->reg, sp58->reg, 8, 0x48, 0);
    }
}

static void func_00409850(int arg0) {
    struct sym* sp3C;
    struct sym* sp38;
    struct sym* sp34;
    int sp30;

    if (arg0 == zbal) {
        sp3C = reg_ptr[0];
    } else {
        if ((sp3C = GetRegister()) == NULL) {
            return;
        }
        if (((arg0 == 0xE5) || (arg0 == 0x120) || (arg0 == 0xE4) || (arg0 == 0x124)) && (sp3C == reg_ptr[0x20 - 1])) {
            posterror("$31 not allowed in conditional branch and link", NULL, 2);
        }
    }

    if (Tokench != 'i') {
        posterror("label expected", NULL, 1);
        return;
    }
    if (func_00409118(&sp30) != 0) {
        binasm_rec.unkA_3FFF = sp30;
        func_00405178(0, arg0, sp3C->reg, 0x48, 9, 0x48, 0);
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
        func_00405178(sp38->unk18, arg0, sp3C->reg, 0x48, 9, 0x48, 0);
    }
}

static void func_00409B10(int arg0) {
    sym* sp4C;
    sym* sp48;
    sym* sp44;
    int sp40;
    int sp3C;
    int sp38;

    if (Tokench != 'i') {
        posterror("condition code or label expected", NULL, 1);
        return;
    }

    sp40 = (arg0 == 8) || (arg0 == 7) || (arg0 == zbc1tl) || (arg0 == zbc1fl);

    if (sp40) {
        sp3C = 0x40;
        if ((LookUp(Tstring, &sp44)) && (sp44->unk10 == 0)) {
            nexttoken();
            if (Tokench == ',') {
                nexttoken();
            }
            sp3C = sp44->reg;
        }
    }
    if (Tokench != 'i') {
        posterror("label expected", NULL, 1);
        return;
    }
    if (func_00409118(&sp38) != 0) {
        binasm_rec.unkA_3FFF = sp38;
        if (sp40) {
            func_00405178(0, arg0, sp3C, 0x48, 9, 0x48, 0);
        } else {
            func_00405178(0, arg0, 0x48, 0x48, 0xA, 0x48, 0);
        }
        gform_extn = 0;
    } else {
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
        if (sp40) {
            func_00405178(sp4C->unk18, arg0, sp3C, 0x48, 9, 0x48, 0);
        } else {
            func_00405178(sp4C->unk18, arg0, 0x48, 0x48, 0xA, 0x48, 0);
        }
    }
}

static void func_00409ECC(int arg0) {
    unsigned int temp_v0;

    if ((Tokench == 'i') || (Tokench == 'd') || (Tokench == 'h') || (Tokench == '+') || (Tokench == '-')) {
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

static void func_00409FD0(int arg0) {
    sym* temp_v0;

    temp_v0 = GetRegister();
    if (temp_v0 != NULL) {
        func_00405178(0, arg0, temp_v0->reg, 0x48, 7, 0x48, 0);
    }
}

static void func_0040A044(int arg0) {
    sym* cur_symbol;

    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = arg0;

    cur_symbol = GetRegister();
    if (cur_symbol != NULL) {
        binasm_rec.unk8_FE = cur_symbol->reg;
        put_binasmfyle();
    }
}

static void func_0040A0D4(void) {
    unsigned int ret;

    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0xF;
    ret = GetExpr();
    binasm_rec.unk8 = ret;
    if (ret & 3) {
        posterror("Offset for cprestore must be positive and divisible by 4", NULL, 1);
    }
    put_binasmfyle();
}

static void parse_cpalias(void) {
    sym* var_v1;

    binasm_rec.unk5_003F = icpalias;
    var_v1 = GetRegister();
    if (var_v1 == NULL) {
        posterror(".cpalias requires a register argument", NULL, 1);
    }
    binasm_rec.unk8_FE = var_v1->reg;
    put_binasmfyle();
}

static void parse_verstamp(void) {
    int version;

    version = GetExpr();
    GetExpr();

    #ifdef IDO_71
    if (version != 7) {
    #else
    if (version != 3) {
    #endif
        posterror("version stamp does not match", NULL, 2);
    }
}

static void func_0040A280(void) {
    sym* sp34;
    sym* sp30;
    unsigned int sp2C;
    sym* sp28;

    if ((sp34 = GetRegister()) == NULL) {
        return;
    }
    if ((Tokench == 'i') || (Tokench == 'd') || (Tokench == 'h') || (Tokench == '+') || (Tokench == '-') ||
        (Tokench == '~') || (Tokench == '(')) {
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
        sp30 = reg_ptr[0x20 - 1];
    }
    if (!LookUp(sframereg, &sp28)) {
        posterror("can not find symbol", sframereg, 1);
    }
    sp28->unk8 = sp34->unk8;
    sp28->reg = sp34->reg;
    if (!LookUp(sframesize, &sp28)) {
        posterror("can not find symbol", sframesize, 1);
    }
    sp28->unk8 = sp2C;
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x2B;
    binasm_rec.unkC_FE = sp34->reg;
    binasm_rec.unk8 = sp2C;
    binasm_rec.unkC_01FC = sp30->reg;
    put_binasmfyle();
}

static void func_0040A4B0(void) {
    if (LastLabel)
        func_00405574(0);

    StructOrg = GetExpr();
    isStruct = 1;
    LastLabel = 0;
}

static void func_0040A530(void) {
    int var_v1;

    if ((var_v1 = GetExpr()) != 1) {
        posterror(".shift_addr expression not 1", NULL, 1);
    }
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x39;
    binasm_rec.unk8 = var_v1;
    put_binasmfyle();
    shftaddr = 1;
}

static void func_0040A5D4(void) {
    int temp_v0 = GetExpr();
    if ((temp_v0 < 0) || (temp_v0 > 12)) {
        posterror("align expression not 0..12", NULL, 1);
        return;
    }
    if (isStruct) {
        StructOrg = ((((int)StructOrg + (temp_v0 << temp_v0)) - 1) >> temp_v0) << temp_v0;
    } else {
        binasm_rec.unk0 = 0;
        binasm_rec.unk5_003F = 4;
        binasm_rec.unk8 = temp_v0;
        put_binasmfyle();
    }
}

static void func_0040A6B8(unsigned int arg0) {
    int i;
    int j;

    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = arg0;
    binasm_rec.unk8 = Tstringlength;

    j = sizeof(binasm_rec);
    for (i = 0; i < Tstringlength; i++) {
        if (j == sizeof(binasm_rec)) {
            put_binasmfyle();
            j = 0;
        }
        ((char*)&binasm_rec)[j] = Tstring[i];
        j++;
    }
    put_binasmfyle();
}

static void func_0040A79C(int arg0) {
    if (LastLabel != 0) {
        func_00405574(0);
    }

    do {
        if (Tokench != '"') {
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
        if (Tokench != '#') {
            nexttoken();
        }
    } while (Tokench == ',');
}

static void func_0040A958(void) {
    int sp4C;
    int sp48;

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
            binasm_rec.unkC = sp4C;
            put_binasmfyle();
        }
    } while (Tokench != '#');
}

static void func_0040AAD4(int arg0) {
    struct sym* sp34;
    unsigned int sp30;
    unsigned int sp2C;
    unsigned int sp28;

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
    if ((arg0 == zlwc2) && (Tokench == '#')) {
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
    binasm_rec.unkC = sp28;
    put_binasmfyle();
    switch (arg0) { /* irregular */
        case icomm:
            sp30 = 0x11;
            break;
        case ilcomm:
            sp30 = 0x21;
            break;
        case iextern:
            sp30 = 0x22;
            break;
        default:
            #ifdef IDO_71
            assertion_failed("false", "as0parse.c", 2578);
            #else
            assertion_failed("false", "as0parse.c", 2568);
            #endif
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

static void func_0040AF00(itype iop) {
    if (LastLabel != 0) {
        func_00405574(0);
    }
    isStruct = 0;
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = iop;
    if (iop == itext) {
        binasm_rec.unk8 = (Tokench != '#') ? Tstringlength : 0;
    }
    if ((iop == itext) && (Tokench != '#')) {
        int i;

        put_binasmfyle();
        for (i = 0; i < Tstringlength; i++) {
            binasm_rec.arr0[i] = Tstring[i];
        }
        nexttoken();
    }
    put_binasmfyle();

    switch (iop) {
        case itext:
            CurrentSegment = 1;
            break;
        case idata:
            CurrentSegment = 2;
            break;
        case isdata:
            CurrentSegment = 0xD;
            break;
        case irdata:
            CurrentSegment = 0xF;
            break;
        default:
            #ifdef IDO_71
            assertion_failed("iop == irdata", "as0parse.c", 2637);
            #else
            assertion_failed("iop == irdata", "as0parse.c", 2627);
            #endif
            break;
    }
}

static void func_0040B0F4(int arg0) {
    char temp_v0;

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
            if ((Tokench == '-') || (Tokench == '+')) {
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

        if (Tokench == ',') {
            nexttoken();
        }
    } while (Tokench != '#');
}

static void func_0040B340(void) {
    invent_locs = 0;
    GetExpr();
    if (Tokench != '"') {
        posterror("string literal expected", NULL, 1);
    }
    make_file(&Tstring[0]);
    nexttoken();
}

int do_dot_end(int arg0) {
    struct unk_struct* temp_s0;

    if ((arg0 == 0) && (D_10000014 == NULL)) {
        posterror(".end without .ent", NULL, 2);
    } else {
        if ((arg0 != 0) && (D_10000014 != NULL)) {
            posterror("missing .end at end of assembly", NULL, 2);
        }
        while (D_10000014 != NULL) {
            if (sym_undefined(D_10000014->sym) != 0) {
                posterror(".ent/.end block never defined the procedure name", NULL, 2);
            } else {
                binasm_rec.unk0 = st_procend(D_10000014->sym);
            }
            temp_s0 = D_10000014->next;
            free(D_10000014);
            D_10000014 = temp_s0;
            binasm_rec.unk5_003F = 0x18;
            put_binasmfyle();
        }
    }
}

static void func_0040B554(int arg0) {
    struct unk_struct* sp24;

    sp24 = D_10000014;
    D_10000014 = malloc(sizeof(long long));
    if (D_10000014 == NULL) {
        new_error();
        return;
    }

    D_10000014->sym = arg0;
    D_10000014->next = sp24;
}

static void func_0040B5F0(int arg0) {
    sym* sp24;

    if (LastLabel != 0) {
        func_00405574(0);
    }

    isStruct = 0;

    if ((Tokench != 'i') && (arg0 != 0x18)) {
        posterror("identifer expected", NULL, 1);
        return;
    }
    if ((arg0 == zbreak) || (arg0 == zpref)) {
        if (verbose != 0) {
            call_name_and_line(3);
            fprintf(stderr, "%s ", &Tstring[0]);
            fflush(stderr);
        }
        binasm_rec.unk8 = 0;
        if (arg0 == 0x1B) {
            if (D_10000014 != 0) {
                posterror("missing .end preceding this .ent", &Tstring[0], 2);
                do_dot_end(0);
            }
        } else if (D_10000014 == 0) {
            posterror(".aent must be inside .ent/.end block", &Tstring[0], 2);
            arg0 = 0x1B;
        }
        if (LookUp(&Tstring[0], &sp24) == 0) {
            EnterSym(&Tstring[0], &sp24, 1);
        }
        if (sp24->unk10 != 3) {
            posterror("invalid symbol for .[a]ent ", &Tstring[0], 1);
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
    int sp38;

    do {
        if (Tokench != 'i') {
            posterror("identifer expected", NULL, 1);
        } else {
            if (LookUp(&Tstring[0], &cur_symbol) == 0) {
                EnterSym(&Tstring[0], &cur_symbol, 1);
            }
            sym_define(cur_symbol->unk18, 0x22, 0);
            if (cur_symbol->unk10 == 3) {
                if (list_extsyms != 0) {
                    func_004054E8(cur_symbol->unk18, &Tstring[0]);
                }
                binasm_rec.unk0 = cur_symbol->unk18;
                binasm_rec.unk5_003F = 2;

                put_binasmfyle();
                sp38 = cur_symbol->unk18;
            } else {
                posterror("invalid symbol for .globl ", &Tstring[0], 1);
            }
        }

        if (Tokench != '#') {
            nexttoken();
        }

        if (Tokench == 'i') {
            if (opLookUp(&Tstring[0], &cur_symbol) == 0) {
                posterror("bad section name\0bad section name", NULL, 1);
            } else if (cur_symbol->unk10 == 2) {
                switch (cur_symbol->reg) { /* irregular */
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

// Implements the .type directive
#ifdef IDO_71
static void parse_type(void) {
    sym* sp2C;
    int sp28;
    int temp_v0;

    if (Tokench != 'i') {
        posterror("identifer expected", NULL, 1);
    } else {
        if (LookUp(Tstring, &sp2C) == 0) {
            EnterSym(Tstring, &sp2C, 1);
        }
        sym_define(sp2C->unk18, 0x22U, 0);
        if (sp2C->unk10 == 3) {
            sp28 = sp2C->unk18;
        } else {
            posterror("invalid symbol for .type", Tstring, 1);
        }
    }
    nexttoken();
    if (Tokench == ',') {
        nexttoken();
    }
    temp_v0 = GetExpr();
    if (temp_v0 != 1) {
        if (temp_v0 == 2) {
            sym_define(sp28, 0x23U, 0);
            return;
        }
    } else {
        sym_define(sp28, 2U, 0);
        return;
    }
    posterror("bad .type value", NULL, 1);
}
#endif

static void func_0040BC84(void) {
    sym* sp4C;
    sym* sp48;

    do {
        if (Tokench != 'i') {
            posterror("identifer expected", NULL, 1);
        } else {
            if (LookUp(&Tstring[0], &sp4C) == 0) {
                EnterSym(&Tstring[0], &sp4C, 1);
            }
            sym_define(sp4C->unk18, 0x22U, 0);
            if (sp4C->unk10 == 3) {
                binasm_rec.unk0 = sp4C->unk18;
                binasm_rec.unk5_003F = 0x12;
                nexttoken();
                if (Tokench == ',') {
                    nexttoken();
                }
                if (LookUp(&Tstring[0], &sp48) == 0) {
                    EnterSym(&Tstring[0], &sp48, 1);
                }
                if (sp48 != sp4C) {
                    binasm_rec.unk8 = sp48->unk18;
                } else {
                    binasm_rec.unk8 = 0;
                }
                put_binasmfyle();
            } else {
                posterror("invalid symbol for .globl ", &Tstring[0], 1);
            }
        }

        if (Tokench != '#') {
            nexttoken();
        }
    } while (Tokench == ',');
}

static int func_0040BEBC(int* arg0, int* arg1, int* arg2) {
    struct sym* sp24;

    if (Tokench == 'i') {
        if (LookUp(&Tstring[0], &sp24) == 0) {
            EnterSym(&Tstring[0], &sp24, 1);
        }

        if (sp24->unk10 == 4) {
            GetItem(arg1, arg2);
            return 1;
        }
        if (sp24->unk10 == 3) {
            *arg0 = sp24->unk18;
            nexttoken();
            func_00405A80(arg1, arg2);

            if (Tokench == ',') {
                nexttoken();
                return 1;
            }
        } else {
            posterror("Bad id in expression", &Tstring[0], 1);
            nexttoken();
            return 0;
        }
    } else {
        GetItem(arg1, arg2);
    }
    return 1;
}

static void func_0040C048(void) {
    int sp54;
    int sp50;
    int sp4C;

    if (LastLabel != 0) {
        func_00405574(1);
    }

    do {
        sp4C = 0;
        sp50 = 1;
        sp54 = 0;
        if (func_0040BEBC(&sp54, &sp4C, &sp50) == 0) {
            return;
        }

        if (isStruct) {
            StructOrg = StructOrg + ((sp50 * 2 < 2) ? 2 : sp50 * 2);
        } else {
            int var_v1 = sp4C;

            if (shftaddr == 1) {
                var_v1 >>= 1;
            }

            if ((var_v1 < -32768) || (var_v1 > 65535)) {
                posterror("value must be -32768..65535", NULL, 1);
                sp4C = 0;
            }

            binasm_rec.unk0 = sp54;
            binasm_rec.unk5_003F = 0xE;
            binasm_rec.unk8 = sp4C;
            binasm_rec.unkC = sp50;
            put_binasmfyle();
        }
    } while (Tokench != '#');
    shftaddr = 0;
}

static void func_0040C218(void) {
    unsigned int temp_v0;

    invent_locs = 0;
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = iloc;
    GetExpr();
    binasm_rec.unk8 = CurrentFile;
    if (Tokench == ':') {
        nexttoken();
    }

    CurrentLine = GetExpr();
    binasm_rec.unkC = CurrentLine;
    put_binasmfyle();
}

static void func_0040C2E0(void) {
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x13;
    binasm_rec.unk8 = GetExpr();
    binasm_rec.unkC = GetExpr();
    put_binasmfyle();
}

static void func_0040C360(void) {
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x32;
    binasm_rec.unk8 = GetExpr();
    binasm_rec.unkC = GetExpr();
    put_binasmfyle();
}

static void func_0040C3E0(void) {
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x33;
    binasm_rec.unk8 = GetExpr();
    binasm_rec.unkC = GetExpr();
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
        if (LookUp(&Tstring[0], &sp24) == 0) {
            EnterSym(&Tstring[0], &sp24, 0);
        }

        binasm_rec.unk0 = sp24->unk18;
        sp24 = NULL;

        nexttoken();
        if (LookUp(&Tstring[0], &sp24) == 0) {
            EnterSym(&Tstring[0], &sp24, 1);
        }
        binasm_rec.unkC = sp24->unk18;
    }
    put_binasmfyle();
}

static void func_0040C5E8(int arg0) {
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = arg0;
    binasm_rec.unk8 = GetExpr();
    binasm_rec.unkC = GetExpr();
    put_binasmfyle();
}
// parse_repeat
static void parse_repeat(int arg0, int arg1) {
    unsigned int var_s5;
    unsigned int var_s0;

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

static void func_0040C830(int itype) {
    if (LastLabel != 0) {
        func_00405574(0);
    }
    isStruct = 0;
    binasm_rec.unk5_003F = itype;
    if (itype == ilab) {
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
    sym* sp24;

    binasm_rec.unk5_003F = 0x25;

    sp24 = GetRegister();
    if (sp24 != NULL) {
        binasm_rec.unkC = GetExpr();
        binasm_rec.unk0 = GetExpr();
        binasm_rec.unk8_FE = sp24->reg;
    }
}
// func_0040C9D0
static void parse_option(void) {
    int opt;
    char* opt_name;

    if (Tokench != 'i') {
        posterror(".option name expected", NULL, 2);
        return;
    }
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = ioption;
    
    opt_name = malloc(Tstringlength + 2);
    
    opt_name[0] = '-';
    
    strcpy(&opt_name[1], &Tstring[0]);
    opt = which_opt(opt_name);
    free(opt_name);

    nexttoken();

    switch (opt) {
        case OPTION_O0:
            binasm_rec.unk6_C0 = 1;
            binasm_rec.unkC = 0;
            break;
        case OPTION_O1:
            binasm_rec.unk6_C0 = 1;
            binasm_rec.unkC = 1;
            break;
        case 0x6:
        case 0x9:
            binasm_rec.unk6_C0 = 1;
            binasm_rec.unkC = 2;
            break;
        case 0xA:
            binasm_rec.unk6_C0 = 1;
            binasm_rec.unkC = 3;
            break;
        case 0xB:
            binasm_rec.unk6_C0 = 1;
            binasm_rec.unkC = 4;
            break;

        case 0x57:
            binasm_rec.unk6_C0 = 2;
            binasm_rec.unkC = 0;
            break;
        case OPTION_pic1:
            binasm_rec.unk6_C0 = 2;
            binasm_rec.unkC = 1;
            break;
        case 0x59:
            binasm_rec.unk6_C0 = 2;
            binasm_rec.unkC = 2;
            break;
        case OPTION_big_got:
        case OPTION_coff:
        case OPTION_elf:
            break;
        default:
            posterror("Unknown name in .option", NULL, 2);
            break;
    }
    put_binasmfyle();
}

static int func_0040CC44(char* name) {
    int var_s0;
    char** var_s1;

    var_s1 = sset_value;

    for (var_s0 = 0; var_s0 <= 0x10; var_s0++) {
        if (strcmp(name, *var_s1) == 0) {
            return var_s0;
        }
        var_s1++;
    }
    return 0;
}

// func_0040CCCC
static void parse_set(void) {
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = iset; // asmtype

    if (Tokench != 'i') {
        posterror(".set option expected", NULL, 2);
    } else {
        binasm_rec.unk8 = func_0040CC44(&Tstring[0]);
        switch (binasm_rec.unk8) { /* irregular */
            case 5:
                atflag = 1;
                break;
            case 6:
                atflag = 0;
                break;
            case 0:
                posterror("unknown option in .set", &Tstring[0], 2);
                break;
        }
        nexttoken();
    }
    put_binasmfyle();
}

static void func_0040CDE4(int arg0) {
    sym* temp_v0;

    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = arg0;

    if ((temp_v0 = GetRegister()) != NULL) {
        binasm_rec.unk6_FE = temp_v0->reg;

        if ((temp_v0 = GetRegister()) != NULL) {
            binasm_rec.unk6_01FC = temp_v0->reg;
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
    if (isStruct != 0) {
        var_v1 = (temp_v0 < 0) ? 0 : temp_v0;
        StructOrg = var_v1 + StructOrg;
        return;
    }
    binasm_rec.unk0 = 0;
    binasm_rec.unk5_003F = 0x14;
    binasm_rec.unk8 = temp_v0;
    binasm_rec.unkC = 0;
    put_binasmfyle();
}

static void func_0040CF9C(void) {
    int sp54;
    int sp50;
    int sp4C;
    int temp_t9;
    int var_v1;

    if (LastLabel != 0) {
        func_00405574(2);
    }
    while (1) {
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
            binasm_rec.unkC = sp50;
            put_binasmfyle();
        }
        if (Tokench == '#') {
            break;
        }
    }
}

static void func_0040D110(void) {
    int sp54;
    int sp50;
    int sp4C;
    int temp_t9;
    int var_v1;

    if (LastLabel != 0) {
        func_00405574(2);
    }

    while (1) {
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
            binasm_rec.unk5_003F = 0x10; // Fake?
            binasm_rec.unk8 = sp4C;
            binasm_rec.unkC = sp50;
            put_binasmfyle();
        }
        if (Tokench == '#') {
            break;
        }
    }
}

static void func_0040D284(char* arg0) {
    sym* cur_symbol;

    if (LookUp(arg0, &cur_symbol) == FALSE) {
        EnterSym(arg0, &cur_symbol, 0);
    }

    if ((cur_symbol->unk10 != 3) && (cur_symbol->unk10 != 4)) {
        posterror("Reserved name used as label", arg0, 1);
        return;
    }
    sym_define(cur_symbol->unk18, CurrentSegment, 0);

    binasm_rec.unk0 = cur_symbol->unk18;

    // TODO: Maybe introduce a AVOID_UB flag to fix this..
#ifdef __GNUC__
    #pragma GCC diagnostic ignored "-Woverflow"
#endif
    binasm_rec.unk5_003F = ~0x3F;

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

    nexttoken();
    strcpy(sp38, Tstring);

    if (Tokench == '#') {
        return;
    }
    if (invent_locs != 0) {
        binasm_rec.unk0 = 0;
        binasm_rec.unk5_003F = iloc;
        binasm_rec.unk8 = CurrentFile;
        binasm_rec.unkC = CurrentLine;
        put_binasmfyle();
    }
    if (Tokench == 'd') {
        make_local_label(Tstring, (size_t*)&Tstringlength);
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

#ifdef IDO_71
    if (opLookUp(sp38, &cur_symbol) == 0) {
        if (strcmp(sp38, ".type") == 0) {
            parse_type();
    } else {
        posterror("undefined assembler operation", sp38, 1);
        return;    
        }
    } else {
#else
    if (opLookUp(sp38, &cur_symbol) == 0) {
        posterror("undefined assembler operation", sp38, 1);
        return;
    }
#endif

    /* Parse different asm directives */
    if (cur_symbol->unk10 == 2) {
        int temp_a0 = cur_symbol->reg;
        switch (temp_a0) {
            case idata:
            case itext:
            case isdata:
            case irdata:
                func_0040AF00(temp_a0);
                break;
            case ialign:
                func_0040A5D4();
                break;
            case iascii:
                func_0040A79C(0);
                break;
            case iasciiz:
                func_0040A79C(1);
                break;
            case ibyte:
                func_0040A958();
                break;
            case icomm:
                func_0040AAD4(8);
                break;
            case ifloat:
                func_0040B0F4(1);
                break;
            case idouble:
                func_0040B0F4(2);
                break;
            case iextended:
                func_0040B0F4(4);
                break;
            case iglobal:
                func_0040B984();
                break;
            case iweakext:
                func_0040BC84();
                break;
            case ihalf:
                func_0040C048();
                break;
            case ilcomm:
                func_0040AAD4(9);
                break;
            case iextern:
                func_0040AAD4(iextern);
                break;
            case ioption:
                parse_option();
                break;
            case iset:
                parse_set();
                break;
            case ispace:
                func_0040CEB4();
                break;
            case iword:
                func_0040CF9C();
                break;
            case idword:
                parse_idword();
                break;
            case iend:
            case ient:
            case iaent:
                func_0040B5F0(temp_a0);
                break;
            case ibgnb:
            case iendb:
            case ilab:
                func_0040C830(temp_a0);
                break;
            case iloc:
                func_0040C218();
                break;
            case ivreg:
                func_0040C928();
                break;
            case irep:
                parse_repeat(1, GetExpr());
                break;
            case iendrep:
                parse_repeat(0, 0);
                break;
            case ierr:
                posterror(".err directive encountered", NULL, 1);
                break;
            case isym:
                func_0040ADFC();
                break;
            case imask:
                func_0040C5E8(imask);
                break;
            case ifmask:
                func_0040C5E8(ifmask);
                break;
            case istruct:
                func_0040A4B0();
                break;
            case iframe:
                func_0040A280();
                break;
            case iverstamp:
                parse_verstamp();
                break;
            case ifile:
                func_0040B340();
                break;
            case imtag:
                func_0040C360();
                break;
            case imalias:
                func_0040C3E0();
                break;
            case iloopno:
                func_0040C2E0();
                break;
            case inoalias:
                func_0040CDE4(inoalias);
                break;
            case ialias:
                func_0040CDE4(ialias);
                break;
            case ilivereg:
            case igjaldef:
            case igjallive:
            case igjrlive:
                func_0040C5E8(temp_a0);
                break;
            case ishift_addr:
                if (mednat) {
                    func_0040A530();
                } else {
                    #ifdef IDO_71
                    assertion_failed("false", "as0parse.c", 3592);
                    #else
                    assertion_failed("false", "as0parse.c", 3537);
                    #endif
                }
                break;
            case irestext:
                if (mednat) {
                    binasm_rec.unk5_003F = 0x3A;
                    put_binasmfyle();
                } else {
                    #ifdef IDO_71
                    assertion_failed("false", "as0parse.c", 3600);
                    #else
                    assertion_failed("false", "as0parse.c", 3545);
                    #endif
                }
                break;
            case iprologue:
                func_0040C460();
                break;
            case iedata:
                func_0040C4CC();
                break;
            case icpload:
                func_0040A044(3);
                break;
            case icprestore:
                func_0040A0D4();
                break;
            case icpadd:
                func_0040A044(0x11);
                break;
            case igpword:
                func_0040D110();
                break;
            case icpalias:
                parse_cpalias();
                break;
            default:
                #ifdef IDO_71
                assertion_failed("false", "as0parse.c", 3624);
                #else
                assertion_failed("false", "as0parse.c", 3569);
                #endif
                break;
        }
        if (!printedline && (Tokench != '#')) {
            posterror("stmt extends past logical end", NULL, 1);
        }
    } else if (cur_symbol->unk10 == 1) {
        int temp_a0 = cur_symbol->reg;

        switch (cur_symbol->unk18) {
            case 0:
                func_004058F0(temp_a0);
                break;
            case 5:
                func_00408C80(temp_a0);
                break;
            case 10:
                func_00409FD0(temp_a0);
                break;
            case 4:
                func_0040848C(temp_a0);
                break;
            case 3:
                func_00407A20(temp_a0);
                break;
            case 1:
                func_00406728(temp_a0);
                break;
            case 12:
                func_00406FE8(temp_a0);
                break;
            case 2:
                func_004076A0(temp_a0);
                break;
            case 11:
                func_004075CC(temp_a0);
                break;
            case 8:
                func_00409B10(temp_a0);
                break;
            case 7:
                func_00409850(temp_a0);
                break;
            case 6:
                func_004092FC(temp_a0);
                break;
            case 9:
                func_00409ECC(temp_a0);
                break;
            case 13:
                func_004088B8(temp_a0);
                break;
            case 15:
                func_00406C48(temp_a0);
                break;
            case 14:
                func_004061F8(temp_a0);
                break;
            case 16:
                func_004085D8(temp_a0);
                break;
            case 17:
                func_004086EC(temp_a0);
                break;
            default:
                #ifdef IDO_71
                assertion_failed("false", "as0parse.c", 3687);
                #else
                assertion_failed("false", "as0parse.c", 3632);
                #endif
                break;
        }
        if (!printedline && (Tokench != '#')) {
            posterror("stmt extends past logical end", NULL, 1);
        }
    } else {
        posterror("assembler op/directive expected", sp38, 1);
    }
#ifdef IDO_71
  }
#endif
}
