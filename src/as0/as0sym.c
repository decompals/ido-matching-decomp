/*
 * @file: as0sym.c (Guess)
 *
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "sym.h"
#include "symconst.h"
#include "stsupport.h"
#include "filehdr.h"
#include "ldfcn.h"
#include "cmplrs/stext.h"
#include "binasm_rec.h"
#include "scnhdr.h"

//.data
static int D_10000020 = 0;
static int D_10000024 = 0;

//External declarations
extern void postcerror(char* error, int arg1);

//Function declaration (as0sym.c)
static void func_0040E180(char* error, char* arg1, int arg2);
int sym_undefined(int arg0);
static void change_global(int arg0, int st, int sc, int arg3, int arg4);
static void data_localize(int arg0, int arg1, int arg2, int arg3);
static void text_localize(int arg0, int arg1, int arg2, int arg3, int arg4);
static char* check_malloc(size_t arg0);
void sym_init(int arg0);
void sym_finish(char* arg0, char* arg1);
int sym_enter(char* arg0, int arg1);
int sym_define(int arg0, unsigned int section, int arg2);
void st_feinit(void);
void itoa(int arg0, char* arg1);

static void func_0040E180(char* error, char* arg1, int arg2) {
    char dest[0x100];

    sprintf(dest, error, arg1);
    postcerror(dest, arg2);
}

int sym_undefined(int arg0) {
    int sp34;
    int sp30;
    int sp2C;
    int sp28;

    st_sym_idn(arg0, &sp30, &sp2C, &sp34, &sp28);
    return sp30 == 0;
}

static void change_global(int arg0, int st, int sc, int arg3, int arg4) {
    EXTR* temp_v0_2;
    DNR* temp_v0;
    int temp_v1_2;
    int var_a1;

    temp_v0 = st_pdn_idn(arg0);
    if (temp_v0->rfd == 0x7FFFFFFF) {
        if ((st == 0xE) || (var_a1 = (st == 6))) {
            var_a1 = arg4 != 0;
        }

        temp_v0_2 = st_pext_iext(temp_v0->index);
        temp_v0_2->asym.st = st;
        temp_v0_2->asym.sc = sc;

        if (D_10000020 != 0) {
            if (temp_v0_2->asym.value < arg3) {
                temp_v0_2->asym.value = arg3;
            }
        } else {
            temp_v0_2->asym.value = arg3;
        }

        temp_v0_2->asym.index = var_a1 ? st_auxisymadd(-1) : 0xFFFFF;
        if (var_a1 != 0) {
            temp_v0_2->ifd = st_currentifd();
            st_auxbtadd(0);
        }
    } else {
        postcerror("Expected global in change_global()", 0);
    }
}

static void data_localize(int arg0, int arg1, int arg2, int arg3) {
    DNR* mP; // mld pointer
    pEXTR temp_s0;

    mP = st_pdn_idn(arg0);
    if (mP->rfd != 0x7FFFFFFF) {
        postcerror("Expected global in data_localize", 0);
    }
    temp_s0 = st_pext_iext(mP->index);
    if ((arg1 == 0xE) || (arg1 == 6)) {
        postcerror("Expected non-Proc in data_localize", 0);
    }
    mP->index = st_symadd(st_stradd(st_str_extiss(temp_s0->asym.iss)), arg3, arg1, arg2, 0xFFFFF);
    mP->rfd = st_currentifd();
    temp_s0->asym.st = 0;
    temp_s0->asym.sc = 0;
}

static void text_localize(int arg0, int arg1, int arg2, int arg3, int arg4) {
    DNR* sp44;
    EXTR* temp_s0;
    int sp3C;

    sp44 = st_pdn_idn(arg0);
    if (sp44->rfd != 0x7FFFFFFF) {
        postcerror("Expected global in text_localize", 0);
    }
    temp_s0 = st_pext_iext(sp44->index);
    sp3C = ((arg1 == 0xE) || (arg1 == 6)) && (temp_s0->asym.index == 0xFFFFF) && arg4;

    sp44->index = st_symadd(st_stradd(st_str_extiss(temp_s0->asym.iss)), arg3, arg1, arg2,
                            sp3C ? st_auxisymadd(-1) : temp_s0->asym.index);

    if (sp3C) {
        st_auxbtadd(0);
    }
    sp44->rfd = st_currentifd();
    temp_s0->asym.st = 0;
    temp_s0->asym.sc = 0;

    if (arg1 == 0xE) {
        temp_s0->asym.index = 0xFFFFF;
    }
}

static char* check_malloc(size_t arg0) {
    void* ptr;

    ptr = malloc(arg0);
    if (ptr == NULL) {
        perror("check_malloc");
        exit(2);
    }
    return ptr;
}

void sym_init(int arg0) {
    st_cuinit();
    D_10000024 = arg0 != 0;
}

void sym_finish(char* arg0, char* arg1) {
    char* temp_a1;
    int sp60;
    int sp5C;
    int sp58;
    int sp54;
    size_t len;
    int i;

    if (arg1 == 0) {
        len = strlen(arg0);
        arg1 = strcpy(check_malloc(len) + 3, arg0);
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
                change_global(i, 1, sp5C, sp60, 1);
            } else if ((sp58 != 1) && (sp58 != 6)) {
                func_0040E180("Symbol %s never defined", temp_a1, 1);
            }
        }
    }
    st_endallfiles();
    st_writebinary(arg1, -1);
}

int sym_enter(char* arg0, int arg1) {
    return st_idn_index_fext(st_extadd(st_extstradd(arg0), 0, 0, 0, 0xFFFFF), 1);
}

int sym_define(int arg0, unsigned int section, int arg2) {
    int value; // sp3C
    int sc;    // sp38
    int st;    // sp34
    int index; // sp30
    char* sp2C;

    sp2C = st_sym_idn(arg0, &sc, &st, &value, &index);
    switch (section) {
        case scAbs:
            if ((st == stNil) && (sc == scNil)) {
                text_localize(arg0, stStatic, scAbs, value, 1);
                break;
            }
            if ((st == stGlobal) && (sc == scNil)) {
                change_global(arg0, stGlobal, scAbs, value, 1);
                break;
            }
            func_0040E180("Conflicting definition of symbol %s", sp2C, 1);
            return 0;

        case scText:
            if ((st == stNil) && (sc == scNil)) {
                text_localize(arg0, stLabel, scText, value, 0);
                break;
            }
            if ((st == stStaticProc) && (sc == scNil)) {
                text_localize(arg0, stStaticProc, scText, value, 1);
                st_procbegin(arg0);
                st_pdadd_idn(arg0);
                break;
            }
            if ((st == stProc) && (sc == scNil)) {
                change_global(arg0, stProc, scNil, value, 1);
                st_procbegin(arg0);
                st_pdadd_idn(arg0);
                break;
            }
            if ((st == stGlobal) && (sc == scNil)) {
                change_global(arg0, stLabel, scText, value, 0);
                break;
            }
            func_0040E180("Conflicting definition of symbol %s", sp2C, 1);
            return 0;

        case scData:
        case scSData:
        case scRData:
            if ((st == stNil) && (sc == scNil)) {
                data_localize(arg0, stStatic, section, value);
                break;
            }
            if ((st == stGlobal) && (sc == scNil)) {
                change_global(arg0, stGlobal, section, value, 1);
                break;
            }
            if ((st == stGlobal) && (sc == scCommon)) {
                change_global(arg0, stGlobal, section, value, 1);
                break;
            }
            func_0040E180("Conflicting definition of symbol %s", sp2C, 1);
            return 0;

        case scCommon:
            if ((st == stNil) && (sc == scNil)) {
                change_global(arg0, stGlobal, scCommon, arg2, 1);
                break;
            }
            if ((st == stGlobal) && (sc == scNil)) {
                change_global(arg0, stGlobal, scCommon, arg2, 1);
                break;
            }
            if ((st == stGlobal) && (sc == scCommon)) {
                D_10000020 = 1;
                change_global(arg0, stGlobal, scCommon, arg2, 1);
                D_10000020 = 0;
                break;
            }
            func_0040E180("Cannot use .comm on previously defined symbol %s", sp2C, 1);
            return 0;

        case 33:
            if ((st == stNil) && (sc == scNil)) {
                data_localize(arg0, stStatic, scCommon, arg2);
                break;
            }
            if ((st == stGlobal) && (sc == scNil)) {
                change_global(arg0, stGlobal, scBss, arg2, 1);
                break;
            }
            if ((st == stGlobal) && (sc == scBss)) {
                D_10000020 = 1;
                change_global(arg0, stGlobal, scBss, arg2, 1);
                D_10000020 = 0;
                break;
            }
            func_0040E180("Cannot use .lcomm on previously defined symbol %s", sp2C, 1);
            return 0;

        case 34:
            if ((st == stNil) && (sc == scNil)) {
                change_global(arg0, stGlobal, scNil, value, 1);
                break;
            }
            if (((st != stGlobal) || (sc != scNil)) && ((st != stGlobal) || (sc != scCommon))) {
                if ((st == stStaticProc) && (sc == scNil)) {
                    change_global(arg0, stProc, scNil, value, 1);
                    break;
                }
                func_0040E180(".globl must precede the definition of the symbol %s", sp2C, 1);
                return 0;
            }
            break;

        case 35:
            if ((st == stNil) && (sc == scNil)) {
                change_global(arg0, stStaticProc, scNil, value, 1);
                break;
            }
            if ((st == stGlobal) && (sc == scNil)) {
                change_global(arg0, stProc, scNil, value, 1);
                break;
            }
            func_0040E180(".ent must precede the definition of the symbol %s", sp2C, 1);
            return 0;

        case scNil: // scNil?
            if ((st == stNil) && (sc == scNil)) {
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

void st_feinit(void) {
}

void itoa(int arg0, char* arg1) {
    sprintf(arg1, "%d", arg0);
}
