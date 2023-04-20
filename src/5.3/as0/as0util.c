/*
* @file: as0util.c
*
*/
#include "stdio.h"
#include "ctype.h"
#include "as0/types.h"



typedef struct {
/* 0x0 */  struct unk_struct *next;
/* 0x4 */  s32 unk4;
/* 0x5 */  u8 fill[0x5];
/* 0x10 */ s32 unk10;
/* 0x11 */ u8 pad[0x12];
}unk_struct;


//extern
extern s32 CurrentLine;
extern s32 invent_locs;
extern u8 Tokench;
extern s8 Tstring[];
extern s32 Tstringlength;
extern s32 linelength;
extern u8 line[0x420];
extern s32 ophashtable[0x100];
static char var;
static char buffer[1];
static char buffer2[0x3FF-4];
extern sym* hashtable[0x100];
extern s32 nextinline;
extern s8 token_tmp[0x10];
extern FILE* CurrentFile;
extern s32 debugflag;
extern s32 map_glevel[];
extern size_t binasm_count;
extern FILE* binasmfyle;
extern s32 in_repeat_block;
extern size_t rep_size;
extern s32 errno;
extern s64 func_00412548(void);
extern FILE* in_file;
extern s32 local_label[];
extern s32 printedline;
static int B_1000A810; // boolean, only used in this function

#define LINE_LENGHT 0x3FF
#define BUF_COUNT 0x400
#define MAX(a, b) ((a > b) ? a: b)
#define MIN(a, b) ((a > b) ? b: a)
#define true 1
#define false 0

int hex_to_num(char c) {
    return tolower(c) - (isdigit(c) ? '0' - 0 : 'a' - '\n');
}


void make_local_label(char* arg0, size_t* arg1) {
    u32 sp2C; // sp+2C
    u32 var_a3; // sp28
    size_t sp24; // sp+24
    char sp23; // sp+23
    size_t strlength; // sp20
    char* temp_a1;

    sp24 = strlen(arg0);
    if (strcmp(token_tmp, arg0) != 0) {
        strcpy(token_tmp, arg0);
    }
    sp2C = atol(token_tmp);
    sp23 = token_tmp[sp24 - 1];

    if (sp2C > 0xFF) {
        posterror("Local label number is out of range\0No such label", token_tmp, 1);
        sp2C = 0;
    }

    ltoa(sp2C, token_tmp);

    if (sp23 == 'b') {
        var_a3 = local_label[sp2C] - 1;
    } else if (sp23 == 'f') {
        var_a3 = local_label[sp2C];
    } else {
        var_a3 = local_label[sp2C];
        if (local_label[sp2C] >= 0x7FFFFFFF) {
            posterror("Too many local labels", token_tmp, 1);
        } else {
            local_label[sp2C]++;
        }
    }

    strlength = strlen(token_tmp);
    token_tmp[strlength] = '$';
    strlength++;
    *arg1 = strlength + 10;
    token_tmp[*arg1] = '\0';

    for (sp2C = 10; sp2C > 0; sp2C--) {
        token_tmp[strlength + sp2C - 1] = (var_a3 % 10) + '0';
        var_a3 /= 10;
    }
    if (strcmp(token_tmp, arg0) != 0) {
        strcpy(arg0, token_tmp);
    }
}


void unscan(char arg0) {
    save.tokench = Tokench;
    strcpy(save.tstring, Tstring);
    save.length = Tstringlength;
    Tokench = arg0;
}

void make_file(const char* file_name) {
    CurrentFile = st_filebegin(file_name, 3, 1, map_glevel[debugflag]);
}

u32 func_0040F5D8(char* arg0, int arg1) {
    u32 temp_v0_2; // digit
    u32 var_s2; // read number
    u32 var_s4; // digit count/return
    u32 var_s5; // radix

    var_s2 = 0;

    // Determine radix and set digit to begin on
    if (arg0[0] == '0') {
        if ((arg0[1] == 'x') || (arg0[1] == 'X')) {
            var_s5 = 16;
            var_s4 = 2;
        } else {
            var_s5 = 8;
            var_s4 = 1;
        }
    } else {
        var_s5 = 10;
        var_s4 = 0;
    }

    if (1) {}

    while (arg0[var_s4] != '\0') {
        temp_v0_2 = hex_to_num(arg0[var_s4]);
        if ((((0x7FFFFFFF / var_s5) * 2) + 1 < var_s2) || ((-1 - (var_s2 * var_s5)) < temp_v0_2)) {
            posterror("Overflow", arg0, 1);
            return var_s4;
        }
        var_s2 = var_s2 * var_s5 + temp_v0_2;
        var_s4++;
    }

    if ((var_s5 == 10) && (var_s2 & 0x80000000) && (var_s2 != 0x80000000)) {
        posterror("Large decimal set sign bit", arg0, 2);
    }

    var_s4 = var_s2;
    if (arg1 != 0) {
        if (var_s2 != 0x80000000) {
            var_s4 = - var_s2;
        }
    }

    return var_s4;
}

s64 func_0040F77C(char* arg0, int arg1) {
    s64 var_v1;

    errno = 0;
    if (Tokench == 'h') {
        var_v1 =  strtoull(arg0, NULL, 0x10);
    } else {
        var_v1 = strtoll(arg0, NULL, 0);
    }
    if (errno == '"') {
        posterror("Number out of range", arg0, 1);
    }
    if (arg1) {
        var_v1 =  -var_v1;
    }
    return var_v1;
}


int hash(char* calc) {
    int k;
    int i;

    i = strlen(calc);

    
    if (i <= 0) {
        assertion_failed("i > 0", "as0util.c", 229);
    }

    k = (calc[1] * 0xD)
        + (calc[MIN(i, 2)] * 0x11)
        + (calc[MIN(i, 3)] * 0xB)
        + (calc[MAX(i - 2, 1)] * 3)
        + (calc[MAX(i - 1, 1)] * 7)
        + (calc[i] * 0x13);

    return k % 128;
}

s32 LookUp(char* name, sym** arg1) {
    sym* var_s0;

    *arg1 = NULL;
    for (var_s0 = hashtable[hash(name)] ; var_s0 != NULL ; var_s0 = var_s0->next) {
        if (strcmp(name, var_s0->name) == 0) {
            *arg1 = var_s0;
            return true;
        }
    }
    return false;
}


s32 opLookUp(s8* arg0, unk_struct** arg1) {
    unk_struct* op;

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
    if (Tstringlength < LINE_LENGHT) {
        token_tmp[Tstringlength] = line[nextinline];
    }
    Tstringlength++;
    nextinline++;
}

int func_0040FC20(int radix) {
    int digit = 1;
    s32 first_inline = nextinline;

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


void func_0040FD98(void) {
    s32 sp2C; // sp+2C
    s32 pad1; // sp+28
    s32 radix; // sp+24

    Tokench = 'h';
    token_tmp[1] = 'x';
    Tstringlength = 2;
    nextinline++;

    sp2C =  func_0040FC20(16);
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


void func_004100C8(void) {

    Tokench = 'd';
     while ((nextinline < linelength) && (line[nextinline] >= '0') && (line[nextinline] < '9')) {
        consume();
     }
    func_0040FB2C();
}

void func_004101AC(void) {
    while ((nextinline < linelength) && (line[nextinline] >= 0x30) && (line[nextinline] < 0x3A)) {
        consume();
    }
}

void func_00410270(u8* arg0) {
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
            return true;
        }
        if (!isdigit(c)) {
            return false;
        }
    }
    return 0;
}

void nexttoken(void) {
    int i; // remaining digits in hex/octal escape code
    int num; // numeric value of octal/hex character code
    char c;
    s32 pad[3];
    int sp4C;

    sp4C = 0;
    if (save.tokench != '\0') {
        Tokench = save.tokench;
        save.tokench = '\0';
        strcpy(Tstring, &save.tstring);
        Tstringlength = save.length;
        return;
    }

    Tstringlength = 0;

    // skip spaces
    while((nextinline < linelength) && (line[nextinline] == ' ')){
        nextinline++;
    }

    // Terminate line in a comment
    if (nextinline >= linelength) {
        Tokench = '#';
        goto end;
    }

    c = line[nextinline];
    Tstringlength = 1;
    token_tmp[0] = c;
    nextinline++;

    switch (c) {
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
            if (((c == '<') && (line[nextinline] == '<')) || ((c == '>') && (line[nextinline] == '>'))) {
                nextinline++;
            }
            Tokench = c;
            break;

        default:
            if (((c >= '1') && (c <= '9'))
                || ((nextinline < linelength)
                    && (((c == '.') && isdigit(line[nextinline]))
                    || ((c == '0') && dot_soon(nextinline))))
                ) {

                if (c == '.') {
                    Tokench = 'f';
                    consume();
                    func_004101AC();
                } else {
                    Tokench = 'd';
                    func_004101AC();

                    if (linelength < nextinline) {
                        break;
                    }

                    if ((line[nextinline] == 'b') || (line[nextinline] == 'f')) {
                        consume();
                        Tokench = 'i';
                        func_00410270(token_tmp);
                        make_local_label(token_tmp, &Tstringlength);
                        func_0040FB2C();
                        break;
                    }

                    if ((line[nextinline] != '.') && (line[nextinline] != 'e') && (line[nextinline] != 'E')) {
                        func_0040FB2C();
                        break;
                    }

                    Tokench = 'f';
                    if (line[nextinline] == '.') {
                        consume();
                        func_004101AC();
                    }
                }

                if (nextinline < linelength){
                    if ((line[nextinline] == 'e') || (line[nextinline] == 'E')) {
                        line[nextinline] = 'e';
                        consume();
                        if (nextinline < linelength) {
                            if ((line[nextinline] == '+') || (line[nextinline] == '-')) {
                                consume();
                            }
                        }
                        if (!(nextinline < linelength) || !(isdigit(line[nextinline]))) {
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

            if (c == '0') {
                sp4C = 1;
                if ((nextinline < linelength) && ((line[nextinline] == 'x') || (line[nextinline] == 'X'))) {
                    func_0040FD98();
                } else {
                    func_004100C8();
                }
                break;
            }

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

                                if (((c >= '0') && (c <= '7'))){
                                    i = 3;
                                    // octal
                                    while (i > 0) {
                                        num = num * 8 + c - '0';
                                        nextinline++;
                                        if (nextinline >= linelength) {
                                            posterror("literal string not terminated", NULL, 1);
                                            goto end;
                                        }
                                        c = line[nextinline];
                                        i--;
                                        if (((c < '0') || (c > '7'))) {
                                            break;
                                        }
                                    }
                                } else {
                                    nextinline++;
                                    c = line[nextinline];
                                    i = 2;
                                    // hex
                                    while (isxdigit(c) && (i > 0)) {
                                        num = (num * 16) + hex_to_num(c);
                                        nextinline++;
                                        if (nextinline >= linelength) {
                                            posterror("literal string not terminated", NULL, 1);
                                            goto end;
                                        }
                                        c = line[nextinline];
                                        i--;
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

/**
 * Reads a cpp-generated file comment of the form
 * `# <line_number> "<file_name>"`
 * or
 * `# line <line_number> "<file_name>"`
 *
 * - the spaces may contain any number of spaces or tabs
 * - line_number must contain only decimal digits
 * - file name may not contain spaces or tabs or newlines
 *
 * @return the next char after the part of the filename recorded,
 *         or the next char after the final `'"'`
 */
char func_00410E80(void) {
    char c;
    int i;
    int line_number;
    char buf[BUF_COUNT]; // sp+44

    for (c = fgetc(in_file);
        (c == ' ') || (c == '\t');
        c = fgetc(in_file)) {}

    if (c == 'l') {
        if (((char)fgetc(in_file) != 'i')
            || ((char)fgetc(in_file) != 'n')
            || ((char)fgetc(in_file) != 'e')) {
            posterror("Expected cpp-generated line number", NULL, 1);
            exit(1);
        }
        for (c = fgetc(in_file);
            (c == ' ') || (c == '\t');
            c = fgetc(in_file)) {}
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
    while ((c != '"') && (c != ' ') && (c != '\n') && (c != 0xFF)) { // eof
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
    char c; //sp+46F
    char prev_c;
    int found_eol; // sp+468
    int i;
    int pad;
    char buf[0x420]; // sp+40
    int var_t0; // sp+3C // not in a character constant or an escaped character

    i = 0;
    prev_c = ' ';
    var_t0 = true;
    found_eol = false;
    printedline = false;

    while (!found_eol) {
        c = fgetc(in_file);
        if ((c == '\t') || (c == '\f')) {
            c = ' ';
        } else if ((c == '"') && (prev_c != '\\')) {
            var_t0 = !var_t0;
        } else if ((c == '\n') || (c == 0xFF)) {
            found_eol = true;
        } else if (var_t0 && ((c == ';') || (c == '#'))) {
            found_eol = true;
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

    if ((c == ';') || (c == 0xFF)) {
        if (!B_1000A810) {
            CurrentLine++;
        }
        B_1000A810 = true;
    } else {
        while ((c != '\n') && (c != 0xFF)) {
            c = fgetc(in_file);
        }

        if ((invent_locs != 0) && !B_1000A810) {
            CurrentLine++;
        }
        B_1000A810 = false;
    }

    if (i > 0x41F) {
        i = 0x41F;
        posterror("Line too long", NULL, 2);
    }

    buf[i] = '\0';
    strcpy(line, buf);
    linelength = i;

    // recurse if empty line
    if ((linelength == 0) && (c != 0xFF)) {
        readinline();
    }
    nextinline = 0;
}


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

void EnterSym(s32 arg0, sym** arg1, s32 arg2) {
    sym* sp2C;
    s32 sp28;

    if (LookUp(arg0, &sp2C) == 0) {
        sp28 = hash(arg0);
        sp2C = alloc_new_sym();
        sp2C->next = hashtable[sp28];

        sp2C->name = alloc_new_string(arg0);
        sp2C->unk10 = 3;
        sp2C->unk8 = 0;
        sp2C->unk14 = 0;
        sp2C->unk18 = sym_enter(arg0, arg2);

        hashtable[sp28] = sp2C;
    }
    if (sp2C->unk10 != 3) {
        posterror("Address symbol expected", &Tstring, 1);
    }
    *arg1 = sp2C;
}

sym *GetRegister() {
    sym* sp24;
    sym* sp20;

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


static s32 func_00411898(void) {
    s32 minus; // sp+3C
    s32 not; // sp+38
    s32 sp34; // sp+34
    sym* sp30; // sp+30
    s32 ret; // sp+2C

    sp34 = 0;
    minus = 0;
    not = 0;
    if (Tokench == '-') {
        minus = 1;
        nexttoken();
    } else if (Tokench == '+') {
        nexttoken();
    } else if (Tokench == '~') {
        not = 1;
        nexttoken();
    }

        switch (Tokench) {                          /* irregular */
            case '(':
                nexttoken();
                sp34 = func_0041244C();
                if (Tokench != ')') {
                    posterror("Right paren expected", NULL, 1);
                }
                break;
    
                case 'i':
                if (LookUp(&Tstring, &sp30) == 0) {
                    posterror("undefined symbol in expression", NULL, 1);
                } else if (sp30->unk10 != 4) {
                    posterror("Symbol must have absolute value", &Tstring, 1);
                } else {
                    sp34 = sp30->unk8;
                }
                break;

            case 'd':
            case 'h':
                sp34 = func_0040F5D8(&Tstring, minus);
                minus = 0;
                break;

            case '"':
                minus = 0;
                sp34 = Tstring;
                if (Tstringlength >= 2) {
                    posterror("String within expression may have only one character", &Tstring, 1);
                }
                break;

            default:
                posterror("Invalid symbol in expression", NULL, 1);
                nexttoken();
                break;
        }
    // } else {
    // }
    if (minus) {
        ret = -sp34;
    } else if (not) {
        ret = ~sp34;
    } else {
        ret = sp34;
    }
    nexttoken();
    return ret;
}

static s64 func_00411B84(void) {
    s32 sp44; // sp+44
    s32 sp40; // sp+40
    s64 sp38; // sp+38
    sym* sp34; // sp+34
    s64 ret; // sp+28

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

//stub
static int func_0041213C(void) {

}

static s64 func_00412144(void) {
    s64 var_s2;
    s64 var_s0;
    s64 temp_v0;
    char temp_s1;

    var_s2 = func_00411B84();
    func_0041213C();

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
            var_s2 = (u64) var_s0 >> temp_v0;
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


s64 func_00412548(void) {
    s64 sp38;
    s64 sp30;
    s64 temp_v0;
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


s32 dw_GetExpr(s32* arg0, u32* arg1) {
    u64 sp20;

    if ((Tokench == 'i') 
        || (Tokench == 'd') 
        || (Tokench == 'h') 
        || (Tokench == '+') 
        || (Tokench == '-') 
        || (Tokench == '~') 
        || (Tokench == '(') 
        || (Tokench == '"')) {
        sp20 = func_00412548();
        func_0041213C();
        if (Tokench == ',') {
            nexttoken();
        }
    } else {
        posterror("Invalid symbol in expression", NULL, 1);
        nexttoken();
    }

    *arg0 = sp20 >> 0x20;
    *arg1 = sp20;

    return (*arg0 != 0) && ((*arg0 != -1) || (s32)sp20 >= 0);
}

void GetBaseOrExpr(unk_struct** arg0, s32* arg1) {
    *arg0 = NULL;
    if (Tokench == ')') {
        nexttoken();
        if ((Tokench == 'i') && !LookUp(Tstring, arg0) && ((*arg0)->unk10 == 0)) {
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
    } else {
    *arg1 = 1;
    }
}


void dw_GetItem(u32 arg0, u32 arg1, s32* arg2) {
    dw_GetExpr(arg0, arg1);
    if (Tokench == ':') {
        nexttoken();
        *arg2 = GetExpr();
        return;
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
        fwrite(&binasm_rec, sizeof(binasm_rec), 1U, binasmfyle);
        memset(&binasm_rec, 0, sizeof(binasm_rec));
        binasm_count++;
    }
}

