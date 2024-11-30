#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "mem.h"
#include "linklist.h"
#include "y.tab.h"

#define FALSE 0
#define TRUE 1

#define BUFFER_SIZE 0x8000

#define GET_SYM_CAT(x) (x != 0 ? (x == -1 ? "typedef" : "keyword") : "regular")

typedef struct Location {
    int offset;
    int file;
    int line;
} Location;

/* .bss       */
/* 0x10023A90 */ static char input_buffer[BUFFER_SIZE + 1];
/* 0x1002BA94 */ static char* inbuf_ptr;
/* 0x1002BA98 */ static int offset_in_file;
/* 0x1002BA9C */ static unsigned int tokenbuf_size;
/* 0x1002BAA0 */ static void* tokenbuf_base;
/* 0x1002BAA4 */ static char* token;
/* 0x1002BAA8 */ static int* wstring_base;
/* 0x1002BAAC */ static int input_file_status;
/* 0x1002BAB0 */ static FILE* input_file;
/* 0x1002BAB4 */ static int input_file_eof;

typedef struct UnkOmega {
    char unk_00[0x04];
    int unk_04;
    struct UnkOmega* unk_08;
    char unk_0C[0x0C];
    int unk_18;
} UnkOmega;

typedef struct UnkChi {
    int unk_00;
    int unk_04;
} UnkChi;

typedef struct UnkQwe {
    LinkedListEntry link;
    int unk_04;
    int unk_08;
} UnkQwe;

typedef struct UnkPsi {
    int unk_00;
    UnkQwe* unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    char unk_18[1];
} UnkPsi;

typedef struct TokenIdentifier {
    int unk_00;
    UnkPsi* unk_04;
    int unk_08;
} TokenIdentifier;

union YYLVAL {
    UnkOmega* node;
    TokenIdentifier identifier;
    int loc;
};

typedef struct CppLineArr {
    unsigned int lines;
    Location* loc;
} CppLineArr;

extern CppLineArr cpplinearr;
extern unsigned int cppline;

extern int yyfile;
extern int yyline;
extern char* infile;
extern int origfile;
extern int curloc;
extern union YYLVAL yylval;
extern void* float_type;
extern void* double_type;
extern void* ulonglong_type;
extern void* longlong_type;
extern void* array_type;
extern void* ulong_type;
extern UnkOmega* long_type;
extern void* uint_type;
extern UnkOmega* int_type;
extern unsigned short options[];
extern unsigned long long __ULONGLONG_MAX;
extern long long __LONGLONG_MAX;
extern long long __LONGLONG_MIN;
extern UnkChi* cur_lvl;
extern MemCtx* pmhandle;
extern LinkedList* psymb_handle;
extern LinkedList* isymb_handle;
extern char debug_arr[];
extern FILE* dbgout;

static char func_004119A0(void);
static char next_char(void);
void register_file(char*, int);
int error(int, int, int, ...);
float str_to_float(char* arg0, int arg1, int arg2);
double str_to_double(char* arg0, int arg1, int arg2);
void* make(int, ...);
UnkPsi* string_to_symbol(char*, size_t);
UnkOmega* make_uiconstant(int, UnkOmega*, unsigned long long);
UnkOmega* make_iconstant(int, UnkOmega*, long long);
unsigned int sizeof_type(int);
char* get_type_name(int);
UnkQwe* mk_parse_symb(UnkPsi* arg0, int arg1, int arg2);
int loc_to_cppline(int);

#define input() (isprint(*inbuf_ptr) ? *inbuf_ptr++ : func_004119A0())
#define unput() inbuf_ptr--; if (*inbuf_ptr == '\n') { yyline--; }

void adjust_vwbuf(void) {
    tokenbuf_size *= 1.333;
    tokenbuf_base = Realloc(tokenbuf_base, tokenbuf_size);
    token = tokenbuf_base;
    wstring_base = tokenbuf_base;
}

Location* yylocation(Location* arg0) {
    Location ret;
    
    ret.offset = (int)(inbuf_ptr - input_buffer) + offset_in_file;
    ret.file = yyfile;
    ret.line = yyline;

    *arg0 = ret;
    return arg0;
}

char* get_buffer(int size) {
    if (size != BUFFER_SIZE) {
        return NULL;
    }
    input_file_status = 0;
    return &input_buffer[1];
}

void cpp_write(char* data, int size) {
    if (size != BUFFER_SIZE && input_file_status == 0) {
        input_file_status = 1;
        input_buffer[size + 1] = 0;
    } else if (size == BUFFER_SIZE && input_file_status == 0) {
        char* name = tempnam("", "");

        input_file = fopen(name, "w+");
        if (input_file == NULL) {
            error(0x2001A, 3, -1, infile != NULL ? infile : "");
        } else {
            // remove this file when it's closed
            unlink(name);
        }

        fwrite(data, 1, size, input_file);
        if (ferror(input_file)) {
            error(0x10047, 3, -1, name);
        }
        input_file_status = 2;
    } else {
        fwrite(data, 1, size, input_file);
        if (ferror(input_file)) {
            error(0x10047, 3, -1, "temporary for buffering");
        }
    }
}

void free_buffer(char* arg0) {

}

static int unescape(char c) {
    switch (c) {
        case 'a':
            return '\a';
        case 'b':
            return '\b';
        case 'f':
            return '\f';
        case 'n':
            return '\n';
        case 'r':
            return '\r';
        case 't':
            return '\t';
        case 'v':
            return '\v';
    }
}

static int scan_line_and_filename(int* line, char* filename, int* hasFilename) {
    char c;
    char* ptr;

    while (c = input()) {
        // skip whitespaces
        if (c == ' ' || c == '\t') {
            continue;
        }
        
        if (c == '\n' || c == 0) {
            return 0;
        }
        // digit encountered -> read line number
        if (isdigit(c)) {
            break;
        }

        if (c == 'l' && (c = input()) == 'i' && (c = input()) == 'n' && (c = input()) == 'e') {
            // skip "line" word
            continue;
        } else {
out:
            if (origfile == 0) {
                register_file("", 1);
            }
        
            if (c != '\n') {
                while (c = input()) {
                    if (c == '\n') {
                        break;
                    }
                }
            }
        
            return FALSE;
        }
    }

    // read line number
    *line = c - '0';
    while (c = (next_char() == '\n' ? '\n' : input())) {
        if (isdigit(c)) {
            *line = *line * 10 + c - '0';
        } else {
            if (c != '\n') {
                unput();
            }
            break;
        }
    }

    while (c = (next_char() == '\n' ? '\n' : input())) {
        if (c != ' ' && isprint(c)) {
            break;
        }
        if (c == '\n') {
            // only line, without filename
            *hasFilename = FALSE;
            return TRUE;
        }
    }

    // filename starts with quote
    if (c != '"') {
        goto out;
    }

    ptr = filename;
    while ((c = input()) != '"') {
        if (c == '\n' || c == 0) {
            goto out;
        }
        *ptr++ = c;
    }
    *ptr = 0;
    *hasFilename = TRUE;
    return TRUE;
}

static int func_00411554(void) {
    int nread;
    int unused[3];
    int line;
    char c;
    int hasFilename;

    if (inbuf_ptr == NULL) {
        if (input_file_status == 2) {
            rewind(input_file);
        }
        offset_in_file = 0;
    } else if (*inbuf_ptr == 0) {
        if (input_file_status == 2 && input_file_eof) {
            return FALSE;
        }

        if (input_file_status == 1) {
            return FALSE;
        }

        if (input_file_status == 0) {
            error(0x20095, 1, 0);
            return FALSE;
        }

        // copy one char to the new buffer
        inbuf_ptr--;
        input_buffer[0] = *inbuf_ptr;

        offset_in_file += (int)(inbuf_ptr - input_buffer);
        inbuf_ptr = input_buffer + 1;
    }

    if (input_file_status == 2) {        
        if (fseek(input_file, offset_in_file, SEEK_SET) == -1) {
            return 0;
        }

        nread = fread(input_buffer + 1, 1, BUFFER_SIZE, input_file);
        input_buffer[1 + nread] = 0;
        if (ferror(input_file)) {
            error(0x10046, 3, -1, "temporary for buffering");
            return 0;
        }
        if (nread == 0) {
            return 0;
        }

        if (feof(input_file)) {
            input_file_eof = TRUE;
        } else {
            input_file_eof = FALSE;
        }
    }

    if (inbuf_ptr == NULL) {
        inbuf_ptr = input_buffer + 1;
        if (input_buffer[1] == '#') {
            inbuf_ptr++;
            if (scan_line_and_filename(&line, token, &hasFilename) == 1) {
                if (hasFilename) {
                    register_file(token, line);
                } else {
                    register_file("", 1);
                }

                if (hasFilename) {                    
                    while (c = input()) {
                        if (c == '\n') {
                            break;
                        }
                    }
                }
                unput();
            }
        } else {
            register_file(infile != NULL ? infile : "", 1);
        }
    }

    return TRUE;
}

static void func_00411930(void) {

}

static char next_char(void) {
    if (inbuf_ptr == NULL || *inbuf_ptr == 0) {
        func_00411554();
    }
    return *inbuf_ptr;
}

// NONMATCHING
static char func_004119A0(void) {
    if (inbuf_ptr == NULL || *inbuf_ptr == 0) {
        if (func_00411554()) {
            return input();
        }

        return *inbuf_ptr++;
    }

    if (*inbuf_ptr == '\n') {
        yyline++;
        if (cppline == 0 || ((int)(inbuf_ptr - input_buffer) + offset_in_file) != cpplinearr.loc[cppline].offset) {
            char* ptr = inbuf_ptr + 1;
            if (*ptr != '#') {
                
                while (*ptr == ' ' || *ptr == '\t') {
                    ptr++;
                }

                if (*ptr != '\n') {
                    cppline++;
                    if (cppline >= cpplinearr.lines) {
                        int newvar = cppline + 0x100;

                        cpplinearr.lines = newvar;
                        cpplinearr.loc = Realloc(cpplinearr.loc, newvar * 12);
                        yylocation(&cpplinearr.loc[cppline]);
                    } else {
                        yylocation(&cpplinearr.loc[cppline]);
                    }
                }
            }
        }
        inbuf_ptr++;
        return '\n';
    }

    if (*inbuf_ptr == '\t' || *inbuf_ptr == '\f' || *inbuf_ptr == '\v') {
        return *inbuf_ptr++;
    }

    return *inbuf_ptr++;
}

static float func_00411C00(char* arg0, char* arg1, int arg2) {
    if (arg0 < arg1) {
        if (arg1[-1] != 0) {
            *arg1 = 0;
        }
        return str_to_float(arg0, arg2, 1);
    }
}

static double func_00411C5C(char* arg0, char* arg1, int arg2) {
    if (arg0 < arg1) {
        if (arg1[-1] != 0) {
            *arg1 = 0;
        }
        return str_to_double(arg0, arg2, 1);
    }
}

static int scan_number(int firstCharIsDot) {
    int spC4 = FALSE;
    int spC0 = FALSE;
    char* s1;
    int spB8 = FALSE;
    int spB4 = FALSE;
    int spB0 = FALSE;
    int spAC = FALSE;
    int s4 = FALSE;
    int spA4 = FALSE;    
    char* s2;
    char c;
    char sp9E = 0;        
    char c1;

    if (firstCharIsDot) {
        s4 = TRUE;
        *token = '.';
        s1 = token + 1;
    } else {
        s1 = token;
    }

    if(s4) {} // required to match

    while (c = input()) {
        if (isdigit(c)) {
            *s1++ = c;

            if (s1 == token + 1 && c == '0') {
                spC0 = TRUE;
            }
            if (spC0 && c > '7' && sp9E == 0) {
                sp9E = c;
            }
        } else if (c == 'X' || c == 'x') {
            if (s1 == token + 1 && *token == '0') {
                spC4 = TRUE;
                *s1++ = c;
                while (c = input()) {
                    if (!isxdigit(c)) {
                        goto out;
                    }
                    *s1++ = c;
                }
                // continue
            } else {
                break;
            }
        } else if (c == '.') {
            if (firstCharIsDot) {
                break;
            }

            spC0 = FALSE;
            firstCharIsDot = TRUE;
            s4 = TRUE;
            *s1++ = c;
        } else if (c == 'e' || c == 'E') {
            *s1++ = c;
            spC0 = FALSE;
            s4 = TRUE;
            c1 = input();
            if (c1 == '+' || c1 == '-') {
                *s1++ = c1;
                c1 = input();
            }
            if (isdigit(c1)) {
                while (isdigit(c1)) {
                    *s1++ = c1;
                    c1 = input();
                }
            } else {
                error(0x2000E, 2, curloc, c1);
            }
            break;
        } else {
            break;
        }
    }
out:
    unput();

    while (c = input()) {
        if (s4 && (c == 'f' || c == 'F')) {
            spAC = TRUE;
            *s1++ = c;
            break;
        } else if (!s4 && !spB8 && (c == 'u' || c == 'U')) {
            spB8 = TRUE;
            *s1++ = c;
            if (spB0) {
                break;
            }
        } else if (!s4 && !spB0 && (c == 'l' || c == 'L')) {
            if (spB4) {
                spB0 = TRUE;
                spB4 = FALSE;
            } else {
                spB4 = TRUE;
            }
            *s1++ = c;
        } else if (s4 && (c == 'l' || c == 'L')) {
            spB4 = TRUE;
            *s1++ = c;
            break;
        } else {
            unput();
            break;
        }
    }

    if (s4) {
        if (spAC) {
            func_00411C00(token, s1, curloc);
            yylval.node = make(0x65, curloc, float_type, string_to_symbol(token, s1 - token));
        } else {
            func_00411C5C(token, s1, curloc);
            yylval.node = make(0x65, curloc, double_type, string_to_symbol(token, s1 - token));
        }
        return CONSTANT;
    } else {
        unsigned long s42 = 0;
        int unused;
        unsigned long long sp8C = 0;
        int s52 = spB0;
        int sp80 = 0;
        int sp7C = 0;
        int s6 = FALSE;

        if (s52 && ((options[13] && (options[5] & 1) || !options[13] && (options[5] & 1))) && (options[5] & 5) == 5) {
            error(0x20131, 1, curloc, "long long constants (LL)");
        }

        if (spC4) {
            if (s1 == token + 2) {
                spA4 = TRUE;
                error(0x2010B, 0, curloc);
            }
            for (s2 = token + 2; s2 < s1; s2++) {
                if (!isxdigit(*s2)) {
                    break;
                }

                sp80 += 4;
                if (!spA4 && !s6 && (s52 && sp8C > __ULONGLONG_MAX / 16 || s42 > 0xFFFFFFFF / 16)) {
                    if (s52 || (options[13] && (options[5] & 1) || !options[13] && (options[5] & 1)) && (options[5] & 5) == 5) {
                        s6 = TRUE;
                    } else {
                        sp7C = TRUE;
                        s52 = TRUE;
                        sp8C = s42;                        
                        s42 = 0;
                    }
                }

                if (s52) {
                    sp8C = (sp8C << 4) + (isdigit(*s2) ? *s2 - '0' : islower(*s2) ? *s2 - 'a' + 10 : *s2 - 'A' + 10);
                } else {
                    s42 = (s42 << 4) + (isdigit(*s2) ? *s2 - '0' : islower(*s2) ? *s2 - 'a' + 10 : *s2 - 'A' + 10);
                }
            }
        } else if (spC0 && sp9E == 0) {
            for (s2 = token + 1; s2 < s1; s2++) {
                if (*s2 < '0' || *s2 > '7') {
                    break;
                }
                sp80 += 3;
                if (!s6 && (s52 && sp8C > __ULONGLONG_MAX / 8 || s42 > 0xFFFFFFFF / 8)) {
                    if (s52 || ((options[13] && (options[5] & 1) || !options[13] && (options[5] & 1))) && (options[5] & 5) == 5) {
                        s6 = TRUE;
                    } else {
                        sp7C = TRUE;
                        s52 = TRUE;
                        sp8C = s42;                        
                        s42 = 0;
                    }
                }

                if (s52) {
                    sp8C = (sp8C << 3) + *s2 - '0';
                } else {
                    s42 = (s42 << 3) + *s2 - '0';
                }
            }
        } else {
            if (sp9E) {
                error(0x20019, 2, curloc, sp9E);
                spC0 = 0;
            }
            
            for (s2 = token; s2 < s1; s2++) {
                unsigned int s0;
                if (!isdigit(*s2)) {
                    break;
                }
                s0 = *s2 - '0';
                if (!s6 && (s52 && (sp8C > __ULONGLONG_MAX / 10 || sp8C * 10 > __ULONGLONG_MAX - s0) || (s42 > 0xFFFFFFFF / 10 || s42 * 10 > 0xFFFFFFFF - s0))) {
                    if (s52 || ((options[13] && (options[5] & 1) || !options[13] && (options[5] & 1))) && (options[5] & 5) == 5) {
                        s6 = TRUE;
                    } else {
                        sp7C = TRUE;
                        s52 = TRUE;
                        sp8C = s42;                        
                        s42 = 0;
                    }
                }

                if (s52) {
                    sp8C = sp8C * 10 + s0;
                } else {
                    s42 = s42 * 10 + s0;
                }
            }
        }

        if (!spA4) {
            if (s6) {
                error(0x2000F, 0, curloc);
            } else if ((((options[13] && (options[5] & 1) || !options[13] && (options[5] & 1))) && (options[5] & 5) == 5 || options[23]) && sp7C){
                error(0x20010, 0, curloc);
            }
        }

        if (spB8 && s52) {
            yylval.node = make_uiconstant(curloc, ulonglong_type, (unsigned long long)sp8C);
        } else if (spB8 && spB4) {
            yylval.node = make_uiconstant(curloc, ulong_type, (unsigned long)s42);
        } else if (spB8) {
            yylval.node = make_uiconstant(curloc, uint_type, (unsigned int)s42);
        } else if (s52) {
            if (sp8C <= __LONGLONG_MAX) {
                yylval.node = make_iconstant(curloc, longlong_type, (long long)sp8C);
            } else {
                yylval.node = make_uiconstant(curloc, ulonglong_type, (unsigned long long)sp8C);
            }
        } else if (spB4) {
            if (s42 < 0x80000000U || !options[13] && !(options[5] & 1)) {
                yylval.node = make_iconstant(curloc, long_type, (long)s42);
            } else {
                yylval.node = make_uiconstant(curloc, ulong_type, (unsigned long)s42);
            }
        } else if (spC4 || spC0) {
            if (options[13] && (options[5] & 1) || !options[13] && (options[5] & 1)) {
                if (s42 < 0x80000000U) {
                    yylval.node = make_iconstant(curloc, int_type, (int)s42);
                } else {
                    yylval.node = make_uiconstant(curloc, uint_type, (unsigned int)s42);
                }
            } else {
                if (s42 < 0x80000000U) {
                    yylval.node = make_iconstant(curloc, int_type, (int)s42);
                } else {
                    yylval.node = make_iconstant(curloc, long_type, (long)s42);
                }
            }
        } else if (s42 < 0x80000000U) {
            yylval.node = make_iconstant(curloc, int_type, (int)s42);
        } else if (s42 < 0x80000000U || !options[13] && !(options[5] & 1)) {
            yylval.node = make_iconstant(curloc, long_type, (long)s42);
        } else {
            yylval.node = make_uiconstant(curloc, ulong_type, (unsigned long)s42);
        }

        if (!options[13] && !(options[5] & 1) && long_type->unk_18 == int_type->unk_18) {
            if (yylval.node->unk_08 == long_type) {
                yylval.node->unk_08 = int_type;
            } else if (yylval.node->unk_08 == ulong_type) {
                yylval.node->unk_08 = uint_type;
            }
        }

        // required to match
        if (1) { }
        if (1) { }
        if (1) { }
        if (1) { }
        
        if (options[19] && !(options[19] & 0x40) && (spC4 || spC0 && sp80 != 0) && sp80 < sizeof_type(yylval.node->unk_08->unk_04)) {
            error(0x7014D, 1, curloc, sp80, spC4 ? "hex" : "octal", get_type_name(yylval.node->unk_08->unk_04));
        }
        return CONSTANT;
    }
}

static int func_00413014(char arg0, char* arg1, int arg2, int* arg3) {
    int i;
    
restart:
    *arg1 = input();
    switch (*arg1) {
        unsigned int value;
        char c;
        case 0:
            goto eof;
        case '\n':
            error(0x20014, 2, curloc);
retFALSE:
            return FALSE;
        case '\\':    
            switch(*arg1 = input()) {
                case '\n':
                    goto restart;
                case 'b':
                case 'f':
                case 'n':
                case 'r':
                case 't':
                case 'v':
                    *arg1 = unescape(*arg1);
                    break;
                case 'a':
                    if (options[13] && (options[5] & 1) || !options[13] && (options[5] & 1)) {
                        *arg1 = unescape(*arg1);
                    } else {
                        *arg1 = 'a';
                        error(0x20018, 0, curloc, *arg1);
                    }
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                    if (!arg2) {        
                        value = *arg1 - '0';
                        for (i = 0; i < 2; i++) {
                            c = input();
                            if (c >= '0' && c <= '7') {
                                value = value * 8 + c - '0';
                            } else {
                                unput();
                                break;
                            }
                        }
        
                        if (value > 255) {
                            error(0x20015, 0, curloc, value, 255);
                        }
                        *arg1 = value;
                        break;
                    }
                    *arg3 = 1;
                    break;
                case 'x':
                    if ((options[13] && (options[5] & 1) || !options[13] && (options[5] & 1)) && !arg2) {
                        c = input();
                        if (isxdigit(c)) {        
                            value = isdigit(c) ? c - '0' : islower(c) ? c - 'a' + 10 : c - 'A' + 10;                        
                            c = input();
                            while (isxdigit(c)) {
                                value = value * 16 + (isdigit(c) ? c - '0' : islower(c) ? c - 'a' + 10 : c - 'A' + 10);
                                c = input();
                            }
                            unput();
                            if (value > 255 || (int)value < 0) {
                                error(0x20016, 0, curloc, value, 255);
                            }
                            *arg1 = value;
                            break;
                        } else {
                            unput();
                        }
                    }
        
                    *arg1 = 'x';
                    if (!(options[13] && (options[5] & 1) || !options[13] && (options[5] & 1))) {
                        error(0x20018, 0, curloc, *arg1);
                    }
                    if (arg2) {
                        *arg3 = 1;
                    }
                    break;
                case 0:
eof:
                    error(0x20017, 2, curloc);
                    goto retFALSE;
                default:                    
                    if (islower(*arg1)) {
                        error(0x20018, 0, curloc, *arg1);
                    }
                    break;
            }
            break;
        default:
            if (*arg1 == arg0) {
                goto retFALSE;
            }
            break;
    }
    
    return TRUE;
}

static int func_004136C8(char arg0, char* arg1) {
    char c;
    int i;
    unsigned int value;    
    int unused;
    int sp44 = FALSE;
    int sp40 = FALSE;
    int sp3C = FALSE;    

    if (!func_00413014(arg0, arg1, 1, &sp3C)) {
        return FALSE;
    }
    if (1) {} if (1) {} if (1) {} if (1) {}
    if (sp3C) {
        switch(*arg1) {
            case 'x':
                if (options[13] && (options[5] & 1) || !options[13] && (options[5] & 1)) {
                    c = input();
                    if (isxdigit(c)) {        
                        value = isdigit(c) ? c - '0' : islower(c) ? c - 'a' + 10 : c - 'A' + 10;                        
                        c = input();
                        while (isxdigit(c)) {
                            value = value * 16 + (isdigit(c) ? c - '0' : islower(c) ? c - 'a' + 10 : c - 'A' + 10);
                            if (sp40) {
                                sp44 = TRUE;
                                break;
                            }
                            if (value >> 28) {
                                sp40 = TRUE;
                            }
                            c = input();
                        }
                        unput();
                        if (sp44) {
                            error(0x20016, 0, curloc, value, 0xFFFFFFFF);
                        }
                        *(int*)arg1 = value;
                        break;
                    } else {
                        unput();
                    }
                }
                *(int*)arg1 = *arg1;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                value = *arg1 - '0';
                for (i = 0; i < 2; i++) {
                    c = input();
                    if (c >= '0' && c <= '7') {
                        value = value * 8 + c - '0';
                    } else {
                        unput();
                        break;
                    }
                }
                *(int*)arg1 = value;
                break;
        }
    } else {
        *(int*)arg1 = *arg1;
    }

    return TRUE;
}

static int scan_string(void) {
    char* ptr;    
    int len;
    int unused;
    int sp38 = 0;

    for (ptr = token, len = 0; func_00413014('"', ptr, 0, &sp38); ptr++, len++) {
        if (len >= tokenbuf_size - 1) {
            adjust_vwbuf();
            ptr = &token[len];
        }
    }

    *ptr = 0;
    yylval.node = make(0x65, curloc, array_type, token, ptr - token + 1);
    return STRING;
}

static int scan_wstring(void) {
    int* ptr;
    int len;

    for (ptr = wstring_base, len = 0; func_004136C8('"', ptr); ptr++, len++) {
        if (len >= (tokenbuf_size >> 2) - 1) {
            adjust_vwbuf();
            ptr = &wstring_base[len];
        }
    }

    *ptr = 0;
    yylval.node = make(0x68, curloc, array_type, wstring_base, len + 1);
    return WSTRING;
}

static int scan_char(void) {
    char* ptr;
    int sp30 = 0;
    unsigned int len;

    for (ptr = token; func_00413014('\'', ptr, 0, &sp30); ptr++) {
    }

    len = ptr - token;
    if (len > 4 || len == 0) {
        error(0x20011, 0, curloc);
    }
    len = ptr - token;
    switch(len) {
        case 0:
            yylval.node = make_iconstant(curloc, int_type, 0);
            break;
        case 1:
            yylval.node = make_iconstant(curloc, int_type, options[6] ? (signed char)token[0] : (unsigned char)token[0]);
            break;
        case 2:
            if (options[2]) {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[6] ? (signed char)token[0] : (unsigned char)token[0]) << 8) + token[1]));
            } else {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[6] ? (signed char)token[1] : (unsigned char)token[1]) << 8) + token[0]));
            }
            break;
        case 3:
            if (options[2]) {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[6] ? (signed char)token[0] : (unsigned char)token[0]) << 16) + (token[1] << 8) + token[2]));
            } else {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[6] ? (signed char)token[2] : (unsigned char)token[2]) << 16) + (token[1] << 8) + token[0]));
            }
            break;
        default:
            if (options[2]) {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[6] ? (signed char)token[0] : (unsigned char)token[0]) << 24) + (token[1] << 16) + (token[2] << 8) + token[3]));
            } else {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[6] ? (signed char)token[3] : (unsigned char)token[3]) << 24) + (token[2] << 16) + (token[1] << 8) + token[0]));
            }
            break;
    }

    return CONSTANT;
}

static int scan_wchar(void) {
    int* ptr;

    for (ptr = wstring_base; func_004136C8('\'', ptr); ptr++) {
    }

    yylval.node = make_iconstant(curloc, long_type, *wstring_base);
    return CONSTANT;
}

void func_004141BC(void) {

}

static int scan_identifier(char firstChar) {
    char c;
    char* ptr = token;
    int len;
    int tp;

    *ptr++ = firstChar;

    while (c = input()) {
        if (!(isalnum(c) || c == '_' || c == '$' && options[7])) {
            unput();
            break;
        }

        if (ptr - token >= tokenbuf_size) {
            len = ptr - token;
            adjust_vwbuf();
            ptr = &token[len];
        }
        *ptr++ = c;
    }

    yylval.identifier.unk_04 = string_to_symbol(token, ptr - token);
    yylval.identifier.unk_08 = curloc;
    yylval.identifier.unk_00 = 0;

    if (yylval.identifier.unk_04->unk_04 != NULL) {
        tp = yylval.identifier.unk_04->unk_04->unk_04; 
        if (tp == -1) {
            if (cur_lvl->unk_04) {
                return TYPE_IDENT;
            } 
            yylval.identifier.unk_00 = 1;
            return IDENTIFIER;
        }
    
        if (tp == 0) {
            return IDENTIFIER;
        }
    
        yylval.identifier.unk_00 = curloc;
        return tp;
    }
    return IDENTIFIER;
}

int scan(void) {
    char c;
    char c1;
    int lineNo;
    int sp54;    

restart:
    curloc = (int)(inbuf_ptr - input_buffer) + offset_in_file - 1;
    c = input();
label2:
    switch (c) {
        case 0:
            inbuf_ptr--;
            return 0;
        case '\n':
            c = input();
            while (c == ' ' || c == '\t') {
                c = input();
            }
            if (c == '#') {
                curloc = (int)(inbuf_ptr - input_buffer) + offset_in_file - 1;
                if (scan_line_and_filename(&lineNo, token, &sp54) != 1) {
                    c = '\n';
                    goto label2;
                }
                
                if (sp54) {
                    register_file(token, lineNo);
                } else {
                    register_file(NULL, lineNo);
                }

                if (sp54) {
                    while (c = input()) {
                        if (c == '\n') {
                            goto label2;
                        }
                    }
                }
                c = '\n';
                goto label2;
            }            
            unput();
            /* fallthrough */
        case '\t':
        case '\v':
        case '\f':
        case ' ':
            goto restart;        
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            unput();
            return scan_number(FALSE);
        case '"':
            return scan_string();
        case '\'':
            return scan_char();
        case '(':
        case ')':
        case ',':
        case ';':
        case '?':
        case '[':
        case ']':
        case '{':
        case '}':
        case '~':
            yylval.loc = curloc;
            return c;
        case ':':
            if (options[13]) {
                c = input();
                if (c == ':') {
                    c = input();
                    if (c == '*') {
                        yylval.loc = curloc;
                        return COLCOLSTAR;
                    }
                    if (c == ' ' || c == '\t') {
                        while (c1 = input()) {
                            if (c1 != ' ' && c1 != '\t') {
                                break;
                            }
                        }
                        if (c1 == '*') {
                            yylval.loc = curloc;
                            return COLCOLSTAR;
                        }
                        unput();
                        yylval.loc = curloc;
                        return COLONCOLON;
                    }
                    unput();
                    yylval.loc = curloc;
                    return COLONCOLON;
                }
                unput();
            }
            yylval.loc = curloc;
            return ':';
        case '+':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return ADD_ASSIGN;
            }
            if (c == '+') {
                yylval.loc = curloc;
                return INC_OP;
            }
            if (c == ' ' || c == '\t') {
                while (c1 = input()) {
                    if (c1 != ' ' && c1 != '\t') {
                        break;
                    }
                }

                if (c1 == '=') {
                    error(0x20111, 0, curloc, "+=");
                    yylval.loc = curloc;
                    return ADD_ASSIGN;
                }
            }
            unput();
            yylval.loc = curloc;
            return '+';
        case '-':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return SUB_ASSIGN;
            }
            if (c == '-') {
                yylval.loc = curloc;
                return DEC_OP;
            }
            if (c == '>') {
                if (options[13]) {
                    c = input();
                    if (c == '*') {
                        yylval.loc = curloc;
                        return MEMPTR_OP;
                    }
                    unput();
                    yylval.loc = curloc;
                    return PTR_OP;
                }
                yylval.loc = curloc;
                return PTR_OP;
            }
            if (c == ' ' || c == '\t') {
                while (c1 = input()) {
                    if (c1 != ' ' && c1 != '\t') {
                        break;
                    }
                }

                if (c1 == '=') {
                    error(0x20111, 0, curloc, "-=");
                    yylval.loc = curloc;
                    return SUB_ASSIGN;
                }
            }
            unput();
            yylval.loc = curloc;
            return '-';
        case '/':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return DIV_ASSIGN;
            }
            if (c == '*') {
                while (TRUE) {
                    c = input();
                    if (c == '*') {
                        c = input();
                        if (c == '/') {
                            break;
                        }
                        unput();
                    } else if (c == 0) {
                        error(0x20017, 2, curloc, c);
                        break;
                    }
                }
                goto restart;
            }
            if (c == ' ' || c == '\t') {
                while (c1 = input()) {
                    if (c1 != ' ' && c1 != '\t') {
                        break;
                    }
                }

                if (c1 == '=') {
                    error(0x20111, 0, curloc, "/=");
                    yylval.loc = curloc;
                    return DIV_ASSIGN;
                }
            }
            unput();
            yylval.loc = curloc;
            return '/';
        case '%':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return REM_ASSIGN;
            }
            if (c == ' ' || c == '\t') {
                while (c1 = input()) {
                    if (c1 != ' ' && c1 != '\t') {
                        break;
                    }
                }

                if (c1 == '=') {
                    error(0x20111, 0, curloc, "%=");
                    yylval.loc = curloc;
                    return REM_ASSIGN;
                }
            }
            unput();
            yylval.loc = curloc;
            return '%';
        case '&':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return AND_ASSIGN;
            }
            if (c == '&') {
                yylval.loc = curloc;
                return AND_OP;
            }
            if (!(options[13] && (options[5] & 1) || !options[13] && (options[5] & 1))) {
                if (c == ' ' || c == '\t') {
                    while (c1 = input()) {
                        if (c1 != ' ' && c1 != '\t') {
                            break;
                        }
                    }
    
                    if (c1 == '=') {
                        error(0x20111, 0, curloc, "&=");
                        yylval.loc = curloc;
                        return AND_ASSIGN;
                    }
                }
            }
            unput();
            yylval.loc = curloc;
            return '&';
        case '|':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return OR_ASSIGN;
            }
            if (c == '|') {
                yylval.loc = curloc;
                return OR_OP;
            }
            if (c == ' ' || c == '\t') {
                while (c1 = input()) {
                    if (c1 != ' ' && c1 != '\t') {
                        break;
                    }
                }

                if (c1 == '=') {
                    error(0x20111, 0, curloc, "|=");
                    yylval.loc = curloc;
                    return OR_ASSIGN;
                }
            }
            unput();
            yylval.loc = curloc;
            return '|';
        case '^':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return XOR_ASSIGN;
            }
            if (c == ' ' || c == '\t') {
                while (c1 = input()) {
                    if (c1 != ' ' && c1 != '\t') {
                        break;
                    }
                }

                if (c1 == '=') {
                    error(0x20111, 0, curloc, "^=");
                    yylval.loc = curloc;
                    return XOR_ASSIGN;
                }
            }
            unput();
            yylval.loc = curloc;
            return '^';
        case '!':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return NE_OP;
            }
            unput();
            yylval.loc = curloc;
            return '!';
        case '=':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return EQ_OP;
            }
            unput();
            yylval.loc = curloc;
            return '=';
        case '*':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return MUL_ASSIGN;
            }
            if (!(options[13] && (options[5] & 1) || !options[13] && (options[5] & 1))) {
                if (c == ' ' || c == '\t') {
                    while (c1 = input()) {
                        if (c1 != ' ' && c1 != '\t') {
                            break;
                        }
                    }
    
                    if (c1 == '=') {
                        error(0x20111, 0, curloc, "*=");
                        yylval.loc = curloc;
                        return MUL_ASSIGN;
                    }
                }
            }
            unput();
            yylval.loc = curloc;
            return '*';
        case '.':
            c = input();
            if (c == '.') {
                c = input();
                if (c == '.') {
                    yylval.loc = curloc;
                    return ELLIPSIS;
                }
                unput();
                yylval.loc = curloc;
                return '..'; // what?
            }
            if (c == '*' && options[13]) {
                yylval.loc = curloc;
                return MEMDOT_OP;
            }
            if (isdigit(c)) {
                unput();
                return scan_number(TRUE);
            }
            unput();
            yylval.loc = curloc;
            return '.';
        case '<':
            c = input();
            if (c == '<') {
                c = input();
                if (c == '=') {
                    yylval.loc = curloc;
                    return LEFT_ASSIGN;
                }
                if (c == ' ' || c == '\t') {
                    while (c1 = input()) {
                        if (c1 != ' ' && c1 != '\t') {
                            break;
                        }
                    }
    
                    if (c1 == '=') {
                        error(0x20111, 0, curloc, "<<=");
                        yylval.loc = curloc;
                        return LEFT_ASSIGN;
                    }
                }
                unput();
                yylval.loc = curloc;
                return LEFT_OP;
            }
            if (c == '=') {
                yylval.loc = curloc;
                return LE_OP;
            }
            unput();
            yylval.loc = curloc;
            return '<';
        case '>':
            c = input();
            if (c == '>') {
                c = input();
                if (c == '=') {
                    yylval.loc = curloc;
                    return RIGHT_ASSIGN;
                }
                if (c == ' ' || c == '\t') {
                    while (c1 = input()) {
                        if (c1 != ' ' && c1 != '\t') {
                            break;
                        }
                    }
    
                    if (c1 == '=') {
                        error(0x20111, 0, curloc, ">>=");
                        yylval.loc = curloc;
                        return RIGHT_ASSIGN;
                    }
                }
                unput();
                yylval.loc = curloc;
                return RIGHT_OP;
            }
            if (c == '=') {
                yylval.loc = curloc;
                return GE_OP;
            }
            unput();
            yylval.loc = curloc;
            return '>';
        case 'L':
            c = input();
            if (c == '"') {
                return scan_wstring();
            }
            if (c == '\'') {
                return scan_wchar();
            }
            unput();
            return scan_identifier('L');
        case '$':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case '_':
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            if (c == '$' && options[7] || c != '$') {
                return scan_identifier(c);
            }
            /* fallthrough */
        default:
            if (isprint(c)) {
                error(0x2000C, 0, curloc, c);
            } else {
                error(0x2000D, 0, curloc, c);
            }
            goto restart;
    }
}

int cpp_line_ptr(char* arg0, char* arg1, int arg2) {
    char* vv;
    int sp58;
    int var_a0;
    int sp50;
    int sp4C;
    int var_a1;
    int var_v1;
    int var_v0_2;
    char* var_a3;
    int unused1;
    int unused2;
    int var_s0;    
    char* var_v0;
    
    sp58 = (arg1 - arg0) / 2;
    var_a1 = loc_to_cppline(arg2);
    var_s0 = cpplinearr.loc[var_a1].offset;
    
    if (var_s0 == arg2 && var_a1 == cppline) {
        var_a1--;
        arg2--;
        var_s0 = cpplinearr.loc[var_a1].offset;
    }
    if (arg2 - var_s0 > (arg1 - arg0) / 3) {
        sp50 = arg2 - var_s0 - (arg1 - arg0) / 3;
    } else {
        sp50 = 0;
    }
    var_a0 = 1;
    if (var_a1 == cppline || var_s0 < offset_in_file || offset_in_file + BUFFER_SIZE < var_s0) {
        var_a0 = 0;
    }
    if ((var_a0 != 0) && (cpplinearr.loc[var_a1 + 1].offset < offset_in_file || offset_in_file + BUFFER_SIZE < cpplinearr.loc[var_a1 + 1].offset)) {
        var_a0 = 0;
    }
    *arg0 = ' ';
    var_a3 = arg0 + 1;   
    
    if (sp50 != 0) {
        *var_a3++ = '.';
        *var_a3++ = '.';
        *var_a3++ = '.';
        *var_a3++ = '.';
        *var_a3++ = ' ';
        arg0 += 5;
    }
    
    
    if (var_a0 || input_file_status == 1) {
        var_v0 = ((var_s0 + input_buffer) - offset_in_file) + 1;
        for (var_v1 = 0; var_v1 < sp50; var_v1++) {
            var_v0++;
        }
        while (*var_v0 != 0 && *var_v0 != '\n' && var_a3 - arg0 <= sp58) {
            if (var_a3 - arg0 < sp58) {
                *var_a3++ = *var_v0++;
            } else {
                var_a3[-1] = '.';
                var_a3[-2] = '.';
                var_a3[-3] = '.';
                var_a3[-4] = '.';
                var_a3[-5] = ' ';
                break;
            }
        }
        if (var_a3[-1] != '\n') {
            *var_a3++ = '\n';
        }
    } else {
        if (fseek(input_file, var_s0, 0) != -1) {
            sp4C = 0;
            while ((var_v0_2 = fgetc(input_file)) != -1) {
                if (sp4C < sp50) {
                    sp4C++;
                } else if (var_a3 - arg0 < sp58) {
                    *var_a3++ = var_v0_2;
                    if ((char)var_v0_2 == '\n') {
                        break;
                    }
                } else {
                    var_a3[-1] = '\n';
                    var_a3[-2] = '.';
                    var_a3[-3] = '.';
                    var_a3[-4] = '.';
                    if (offset_in_file && offset_in_file) {}
                    var_a3[-5] = '.';
                    var_a3[-6] = ' ';
                    
                    break;
                }
            }
        }
    }
    
    *var_a3++ = ' ';    
    if (sp50 != 0) {
        *var_a3++ = '.';
        *var_a3++ = '.';
        *var_a3++ = '.';
        *var_a3++ = '.';
        *var_a3++ = ' ';
    }
    
    vv = arg0 + 1;
    while (var_s0 < arg2 - sp50) {
        if (*vv == '\n') {
            *arg0 = (*vv) * 0; // fake match
            return 0;
        }
        if (*vv == '\t') {
            *var_a3++ = '\t';
        } else {
            *var_a3++ = '-';
        }
        vv++;
        var_s0++;
    }
    
    *var_a3++ = '^';
    *var_a3++ = '\n';
    *var_a3++ = 0;
    return 1;
}

void init_scan(void) {
    long long tmp;
    long long tmp2;

    pmhandle = mem_start();
    tokenbuf_size = 0x1000;
    tokenbuf_base = Malloc(tokenbuf_size);
    token = tokenbuf_base;
    wstring_base = tokenbuf_base;

    psymb_handle = link_start(pmhandle, sizeof(UnkQwe));
    isymb_handle = link_start(pmhandle, 0x14);

    mk_parse_symb(string_to_symbol("__builtin_alignof", 17), ALIGNOF, 0);
    mk_parse_symb(string_to_symbol("__builtin_classof", 17), CLASSOF, 0);
    mk_parse_symb(string_to_symbol("__builtin_try", 13), TRY, 0);
    mk_parse_symb(string_to_symbol("__builtin_except", 16), EXCEPT, 0);
    mk_parse_symb(string_to_symbol("__builtin_finally", 17), FINALLY, 0);
    mk_parse_symb(string_to_symbol("__unaligned", 11), UNALIGN, 0);
    mk_parse_symb(string_to_symbol("__builtin_leave", 15), LEAVE, 0);
    mk_parse_symb(string_to_symbol("auto", 4), AUTO, 0);
    mk_parse_symb(string_to_symbol("break", 5), BREAK, 0);
    mk_parse_symb(string_to_symbol("char", 4), CHAR, 0);
    mk_parse_symb(string_to_symbol("case", 4), CASE, 0);
    mk_parse_symb(string_to_symbol("const", 5), CONST, 0);
    mk_parse_symb(string_to_symbol("continue", 8), CONTINUE, 0);
    mk_parse_symb(string_to_symbol("double", 6), DOUBLE, 0);
    mk_parse_symb(string_to_symbol("default", 7), DEFAULT, 0);
    mk_parse_symb(string_to_symbol("do", 2), DO, 0);
    mk_parse_symb(string_to_symbol("extern", 6), EXTERN, 0);
    mk_parse_symb(string_to_symbol("else", 4), ELSE, 0);
    mk_parse_symb(string_to_symbol("enum", 4), ENUM, 0);
    mk_parse_symb(string_to_symbol("for", 3), FOR, 0);
    mk_parse_symb(string_to_symbol("float", 5), FLOAT, 0);
    mk_parse_symb(string_to_symbol("goto", 4), GOTO, 0);
    mk_parse_symb(string_to_symbol("if", 2), IF, 0);
    mk_parse_symb(string_to_symbol("int", 3), INT, 0);
    mk_parse_symb(string_to_symbol("long", 4), LONG, 0);
    mk_parse_symb(string_to_symbol("__long_long", 11), LONGLONG, 0);
    mk_parse_symb(string_to_symbol("return", 6), RETURN, 0);
    mk_parse_symb(string_to_symbol("register", 8), REGISTER, 0);
    mk_parse_symb(string_to_symbol("switch", 6), SWITCH, 0);
    mk_parse_symb(string_to_symbol("struct", 6), STRUCT, 0);
    mk_parse_symb(string_to_symbol("signed", 6), SIGNED, 0);
    mk_parse_symb(string_to_symbol("sizeof", 6), SIZEOF, 0);
    mk_parse_symb(string_to_symbol("short", 5), SHORT, 0);
    mk_parse_symb(string_to_symbol("static", 6), STATIC, 0);
    mk_parse_symb(string_to_symbol("typedef", 7), TYPEDEF, 0);
    mk_parse_symb(string_to_symbol("unsigned", 8), UNSIGNED, 0);
    mk_parse_symb(string_to_symbol("union", 5), UNION, 0);
    mk_parse_symb(string_to_symbol("void", 4), VOID, 0);
    mk_parse_symb(string_to_symbol("volatile", 8), VOLATILE, 0);
    mk_parse_symb(string_to_symbol("while", 5), WHILE, 0);
    mk_parse_symb(string_to_symbol("__builtin_alignof", 17), ALIGNOF, 0);
    mk_parse_symb(string_to_symbol("__pragma", 8), __PRAGMA, 0);
    if (!options[13] && !(options[5] & 1) || !options[13] && (options[5] & 3) == 3) {
        mk_parse_symb(string_to_symbol("__inline", 8), INLINE, 0);
    }
    if (options[13]) {
        mk_parse_symb(string_to_symbol("class", 5), CLASS, 0);
        mk_parse_symb(string_to_symbol("virtual", 7), VIRTUAL, 0);
        mk_parse_symb(string_to_symbol("protected", 9), PROTECTED, 0);
        mk_parse_symb(string_to_symbol("public", 6), PUBLIC, 0);
        mk_parse_symb(string_to_symbol("private", 7), PRIVATE, 0);
        mk_parse_symb(string_to_symbol("operator", 8), OPERATOR, 0);
        mk_parse_symb(string_to_symbol("this", 4), THIS, 0);
        mk_parse_symb(string_to_symbol("new", 3), NEW, 0);
        mk_parse_symb(string_to_symbol("delete", 6), DELETE, 0);
        mk_parse_symb(string_to_symbol("inline", 6), INLINE, 0);
        mk_parse_symb(string_to_symbol("friend", 6), FRIEND, 0);
    }

    func_00411554();
    
    tmp = 0x7FFFFFFF;
    tmp2 = 1 + tmp * 2;
    __LONGLONG_MAX = tmp2 + tmp * 2 * (tmp + 1);
    __ULONGLONG_MAX = __LONGLONG_MAX * 2 + 1;
    __LONGLONG_MIN = -__LONGLONG_MAX - 1;
}

UnkQwe* mk_parse_symb(UnkPsi* arg0, int arg1, int arg2) {
    UnkQwe* psymb;
    UnkQwe* prev;
    
    psymb = (UnkQwe*)get_link_elem(psymb_handle);
    psymb->unk_04 = arg1;
    psymb->unk_08 = arg2;
    prev = psymb->link.next = arg0->unk_04;
    arg0->unk_04 = psymb;

    if (debug_arr[80] > 0) {
        fprintf(dbgout, "creating %.*s (0x%x:%d:%s) hides (0x%x:%d:%s)\n",
            arg0->unk_14, arg0->unk_18,
            psymb, psymb->unk_08, GET_SYM_CAT(psymb->unk_04),
            prev, prev != NULL ? prev->unk_08 : -1, prev != NULL ? GET_SYM_CAT(prev->unk_04) : "<nil>");
    }

    return psymb;
}