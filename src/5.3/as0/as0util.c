#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "types.h"


typedef struct {
/* 0x0 */  struct bar *next;
/* 0x4 */  s32 unk4;
/* 0x5 */  u8 fill[0x5];
/* 0x10 */ s32 unk10;
/* 0x11 */ u8 pad[0x12];
}bar;


//extern
extern u8 Tokench;
extern s8 Tstring;
extern s32 Tstringlength;
s32 linelength;
u8 line[0x420];
s32 ophashtable[0x100];
static char var;
static char buffer[1];
static char buffer2[0x3FF-4];
static char* save;
s32 hashtable[0x10];
s32 nextinline;
s8 token_tmp[0x10];
FILE *CurrentFile;
s32 debugflag;
extern s32 map_glevel[];


//static s32 func_00411898(void) {}


#define LINE_LENGHT 0x3FF
#define MAX(a, b) ((a > b) ? a: b)
#define MIN(a, b) ((a > b) ? b: a)


int hex_to_num(char c) {
    return tolower(c) - (isdigit(c) ? '0' - 0 : 'a' - '\n');
}


#pragma GLOBAL_ASM("asm/5.3/functions/as0/make_local_label.s")

void unscan(u8 arg0) {
    var = Tokench;
    strcpy(buffer, &Tstring);
    save = Tstringlength;
    Tokench = arg0;
}

void make_file(u8* arg0) {
    CurrentFile = st_filebegin(arg0, 3, 1, map_glevel[debugflag]);
}

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040F5D8.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040F77C.s")

s32 hash(char* arg0) {
    s32 k;
    s32 var_a3;

    var_a3 = strlen(arg0);
    if (var_a3 <= 0) {
        assertion_failed("i > 0", "as0util.c", 0xE5);
    }

    k = (arg0[1] * 0xD)
        + (arg0[MIN(var_a3, 2)] * 0x11)
        + (arg0[MIN(var_a3, 3)] * 0xB)
        + (arg0[MAX(var_a3 - 2, 1)] * 3)
        + (arg0[MAX(var_a3 - 1, 1)] * 7)
        + (arg0[var_a3] * 0x13);

    return k % 128;
}


s32 LookUp(u8* arg0, bar** arg1) {
    bar* var_s0;

    *arg1 = NULL;

    for (var_s0 = hashtable[hash(arg0)] ; var_s0 != NULL ; var_s0 = var_s0->next) {
        if (strcmp((s8* ) arg0, var_s0->unk4) == 0) {
            *arg1 = var_s0;
            return true;
        }
    }
    return false;
}


s32 opLookUp(s8* arg0, bar** arg1) {
    bar* op;

    *arg1 = NULL;

    for(op = ophashtable[hash(arg0)]; op != NULL ; op = op->next){ 
        if (strcmp(arg0, op->unk4) == 0) {
            *arg1 = op;
            return true;
        }
    }
    return false;
}

void func_0040FB2C(void) {
    if (linelength >= nextinline) {
        if (((isalpha(line[nextinline]))) || (line[nextinline] == '9')) {
            posterror("Badly delimited numeric literal", 0, 1);
        }
    }
}


void consume(void) {
    if (Tstringlength < LINE_LENGHT)
        token_tmp[Tstringlength] = line[nextinline];

    Tstringlength++;
    nextinline++;
}

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040FC20.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_0040FD98.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_004100C8.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_004101AC.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00410270.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/dot_soon.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/nexttoken.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00410E80.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/readinline.s")

char* alloc_new_sym(void) {
    void* ptr;

    ptr = malloc(0x1C); //sizeof of something

    if (ptr == NULL) {
        new_error();
    } else {
        memset(ptr, 0, 0x1C); //sizeof of something
    }
    return ptr;
}


char* alloc_new_string(char* arg0) {
    s32 stackPad;
    s8* sp20;

    sp20 = malloc(strlen(arg0) + 1);
    if (sp20 == NULL) {
        new_error();
    }
    strcpy(sp20, arg0);
    return sp20;
}


#pragma GLOBAL_ASM("asm/5.3/functions/as0/EnterSym.s")

s32 GetRegister() {
    struct sym* sp24;
    void* sp20;

    sp20 = NULL;
    if (Tokench != 'i') {
        posterror("register expected", NULL, 1);
    } else if (LookUp(&Tstring, &sp24) == 0) {
        posterror("Undefined symbol", &Tstring, 1);
    } else if (sp24->unk10 != 0) {
        posterror("Register expected", &Tstring, 1);
    } else {
        sp20 = sp24;
    }
    nexttoken();
    if (Tokench == ',') {
        nexttoken();
    }
    return sp20;
}


#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00411898.s")

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00411B84.s")

static s32 func_00411ECC() {
    char temp_s1;
    s32 temp_v0;
    s32 var_s2;
    s32 var_s0;

    var_s2 = func_00411898();

    while ((Tokench == '*')
        || (Tokench == '/')
        || (Tokench == '%')
        || (Tokench == '<')
        || (Tokench == '>')
        || (Tokench == '^')
        || (Tokench == '&')
        || (Tokench == '|')
        ) {
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
            var_s2 = (u32) var_s0 >> temp_v0;
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

void func_0041213C(void) {

}

#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00412144.s")

s32 func_0041244C(void) {
    s32 var_s2 = func_00411ECC();

    while ((Tokench == '+') || (Tokench == '-')) {
        s32 var_s0 = var_s2;
        char temp_s1 = Tokench;
        s32 temp_v0;

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


#pragma GLOBAL_ASM("asm/5.3/functions/as0/func_00412548.s")

s32 GetExpr() {
    s32 sp24 = false;

    if ((Tokench == 'i')
        || (Tokench == 'd')
        || (Tokench == 'h')
        || (Tokench == '+')
        || (Tokench == '-')
        || (Tokench == '~')
        || (Tokench == '(')
        || ((Tokench == '"'))) {
        sp24 = func_0041244C();
        if (Tokench == ',') {
            nexttoken();
        }
    } else {
        posterror("Invalid symbol in expression", 0, 1);
        nexttoken();
    }
    return sp24;
}


#pragma GLOBAL_ASM("asm/5.3/functions/as0/dw_GetExpr.s")

void GetBaseOrExpr(bar** arg0, s32* arg1) {
    *arg0 = NULL;
    if (Tokench == ')') {
        nexttoken();
        if ((Tokench == 'i') && (LookUp(&Tstring, arg0) != 0) && arg0[0]->unk10 == 0) {
            nexttoken();
            if (Tokench != ')') {
                posterror("Expected \")\" after base register", 0, 1);
            }
            nexttoken();
            return;
        }
        unscan(')');

    }

    *arg1 = GetExpr();
}

void GetItem(s32* arg0, s32* arg1) {
    *arg0 = GetExpr();
    if (Tokench == ':') {
        nexttoken();
        *arg1 = GetExpr();
        return;
    }
    *arg1 = 1;
}


void dw_GetItem(u32 arg0, u32 arg1, s32* arg2) {
    dw_GetExpr(arg0, arg1);
    if (Tokench == ':') {
        nexttoken();
        *arg2 = GetExpr();
        return;
    }
    *arg2 = 1;
}


#pragma GLOBAL_ASM("asm/5.3/functions/as0/put_binasmfyle.s")
