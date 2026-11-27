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
//.bss
extern int map_glevel[4];
static int B_1000A810; //!< boolean, only used in readinline

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
        posterror("Local label number is out of range", token_tmp, 1);
        stubbed_printf("No such label");
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
    sym* sym;

    *arg1 = NULL;
    for (sym = hashtable[hash(name)]; sym != NULL; sym = sym->next) {
        if (strcmp(name, sym->name) == 0) {
            *arg1 = sym;
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
    arg0[Tstringlength] = '\0';
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

    ptr = malloc(sizeof(sym));

    if (ptr == NULL) {
        new_error();
    } else {
        memset(ptr, 0, sizeof(sym));
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
    int not;   //!< BOOL
    int sp34;  // sp+34
    sym* sp30; // sp+30
    int ret;   //!< BOOL

    sp34 = 0;
    minus = FALSE;
    not= FALSE;
    if (Tokench == '-') {
        minus = 1;
        nexttoken();
    } else if (Tokench == '+') {
        nexttoken();
    } else if (Tokench == '~') {
        not= 1;
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
    } else if (not) {
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

#ifdef __GNUC__
__attribute__((noreturn)) static long long func_0041213C(void) {
}
#else
static long long func_0041213C(void) {
} // The long long type is required to match
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
    int sp24 = FALSE;

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
    return (*high != 0) && ((*high != 0xFFFFFFFF) || ((int)*low >= 0));
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
