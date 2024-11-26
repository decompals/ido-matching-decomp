#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include "mem.h"
#include "y.tab.h"

#define false 0
#define true 1

typedef struct Location {
    int unk_00;
    int unk_04;
    int unk_08;
} Location;

static char B_10023A90[1];
static char* B_1002BA94;
static int B_1002BA98;
static unsigned int B_1002BA9C;
static void* B_1002BAA0;
static char* B_1002BAA4;
static int* B_1002BAA8;
static int B_1002BAAC;
static FILE* B_1002BAB0;
static int B_1002BAB4;


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
    int unk_00;
    int unk_04;
} UnkQwe;

typedef struct UnkPsi {
    int unk_00;
    UnkQwe* unk_04;
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
extern UnkChi* cur_lvl;

static char func_004119A0(void);
static char func_00411938(void);
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


void adjust_vwbuf(void) {
    B_1002BA9C *= 1.333;
    B_1002BAA0 = Realloc(B_1002BAA0, B_1002BA9C);
    B_1002BAA4 = B_1002BAA0;
    B_1002BAA8 = B_1002BAA0;
}

Location* yylocation(Location* arg0) {
    Location ret;
    
    ret.unk_00 = (int)(B_1002BA94 - B_10023A90) + B_1002BA98;
    ret.unk_04 = yyfile;
    ret.unk_08 = yyline;

    *arg0 = ret;
    return arg0;
}

char* get_buffer(int arg0) {
    if (arg0 != 0x8000) {
        return NULL;
    }
    B_1002BAAC = 0;
    return &B_10023A90[1];
}

void cpp_write(char* arg0, int arg1) {
    if (arg1 != 0x8000 && B_1002BAAC == 0) {
        B_1002BAAC = 1;
        B_10023A90[arg1 + 1] = 0;
    } else if (arg1 == 0x8000 && B_1002BAAC == 0) {
        char* name = tempnam("", "");
        B_1002BAB0 = fopen(name, "w+");
        if (B_1002BAB0 == NULL) {
            error(0x2001A, 3, -1, infile != NULL ? infile : "");
        } else {
            unlink(name);
        }

        fwrite(arg0, 1, arg1, B_1002BAB0);
        if (ferror(B_1002BAB0)) {
            error(0x10047, 3, -1, name);
        }
        B_1002BAAC = 2;
    } else {
        fwrite(arg0, 1, arg1, B_1002BAB0);
        if (ferror(B_1002BAB0)) {
            error(0x10047, 3, -1, "temporary for buffering");
        }
    }
}

void free_buffer(char* arg0) {

}

static int func_00410E40(char arg0) {
    switch (arg0) {
        case 'a':
            return 7;
        case 'b':
            return 8;
        case 'f':
            return 12;
        case 'n':
            return 10;
        case 'r':
            return 13;
        case 't':
            return 9;
        case 'v':
            return 11;
    }
}

#define input() (isprint(*B_1002BA94) ? *B_1002BA94++ : func_004119A0())
#define unput() B_1002BA94--; if (*B_1002BA94 == '\n') { yyline--; }

static int func_00410EBC(int* arg0, char* arg1, int* arg2) {
    char c;
    char* ptr;

    while (c = input()) {
        if (c == ' ' || c == '\t') {
            continue;
        }
        
        if (c == '\n' || c == 0) {
            return 0;
        }

        if (isdigit(c)) {
            break;
        }

        if (c == 'l' && (c = input()) == 'i' && (c = input()) == 'n' && (c = input()) == 'e') {
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
        
            return 0;
        }
    }

    *arg0 = c - '0';
    while (c = (func_00411938() == '\n' ? '\n' : input())) {
        if (isdigit(c)) {
            *arg0 = *arg0 * 10 + c - '0';
        } else {
            if (c != '\n') {
                B_1002BA94--;
                if (*B_1002BA94 == '\n') {
                    yyline--;
                }
            }
            break;
        }
    }

    while (c = (func_00411938() == '\n' ? '\n' : input())) {
        if (c != ' ' && isprint(c)) {
            break;
        }
        if (c == '\n') {
            *arg2 = 0;
            return 1;
        }
    }

    if (c != '"') {
        goto out;
    }

    ptr = arg1;
    while ((c = input()) != '"') {
        if (c == '\n' || c == 0) {
            goto out;
        }
        *ptr++ = c;
    }
    *ptr = 0;
    *arg2 = 1;
    return 1;
}

static int func_00411554(void) {
    int nread;
    int unused[3];
    int sp34;
    char c;
    int sp2C;

    if (B_1002BA94 == NULL) {
        if (B_1002BAAC == 2) {
            rewind(B_1002BAB0);
        }
        B_1002BA98 = 0;
    } else if (*B_1002BA94 == 0) {
        if (B_1002BAAC == 2 && B_1002BAB4 != 0) {
            return 0;
        }

        if (B_1002BAAC == 1) {
            return 0;
        }

        if (B_1002BAAC == 0) {
            error(0x20095, 1, 0);
            return 0;
        }

        B_1002BA94--;
        B_10023A90[0] = *B_1002BA94;
        B_1002BA98 += (int)(B_1002BA94 - B_10023A90);
        B_1002BA94 = B_10023A90 + 1;
    }

    if (B_1002BAAC == 2) {        
        if (fseek(B_1002BAB0, B_1002BA98, SEEK_SET) == -1) {
            return 0;
        }

        nread = fread(B_10023A90 + 1, 1, 0x8000, B_1002BAB0);
        B_10023A90[1 + nread] = 0;
        if (ferror(B_1002BAB0)) {
            error(0x10046, 3, -1, "temporary for buffering");
            return 0;
        }
        if (nread == 0) {
            return 0;
        }

        if (feof(B_1002BAB0)) {
            B_1002BAB4 = 1;
        } else {
            B_1002BAB4 = 0;
        }
    }

    if (B_1002BA94 == NULL) {
        B_1002BA94 = B_10023A90 + 1;
        if (B_10023A90[1] == '#') {
            B_1002BA94++;
            if (func_00410EBC(&sp34, B_1002BAA4, &sp2C) == 1) {
                if (sp2C) {
                    register_file(B_1002BAA4, sp34);
                } else {
                    register_file("", 1);
                }

                if (sp2C) {                    
                    while (c = input()) {
                        if (c == '\n') {
                            break;
                        }
                    }
                }
                B_1002BA94--;
                if (*B_1002BA94 == '\n') {
                    yyline--;
                }
            }
        } else {
            register_file(infile != NULL ? infile : "", 1);
        }
    }

    return 1;
}

static void func_00411930(void) {

}

static char func_00411938(void) {
    if (B_1002BA94 == NULL || *B_1002BA94 == 0) {
        func_00411554();
    }
    return *B_1002BA94;
}

typedef struct CppLineArr {
    unsigned int lines;
    Location* loc;
} CppLineArr;

extern CppLineArr cpplinearr;
extern unsigned int cppline;

// NONMATCHING
static char func_004119A0(void) {
    if (B_1002BA94 == NULL || *B_1002BA94 == 0) {
        if (func_00411554()) {
            return input();
        }

        return *B_1002BA94++;
    }

    if (*B_1002BA94 == '\n') {
        yyline++;
        if (cppline == 0 || ((int)(B_1002BA94 - B_10023A90) + B_1002BA98) != cpplinearr.loc[cppline].unk_00) {
            char* ptr = B_1002BA94 + 1;
            if (*ptr != '#') {
                
                while (*ptr == ' ' || *ptr == '\t') {
                    ptr++;
                }

                if (*ptr != '\n') {
                    cppline++;
                    if (cppline >= cpplinearr.lines) {
                        cpplinearr.lines = cppline + 0x100;
                        cpplinearr.loc = Realloc(cpplinearr.loc, cpplinearr.lines * 3 << 2);
                        yylocation(cpplinearr.loc + cppline);
                    } else {
                        yylocation(cpplinearr.loc + cppline);
                    }
                }
            }
        }
        B_1002BA94++;
        return '\n';
    }

    if (*B_1002BA94 == '\t' || *B_1002BA94 == '\f' || *B_1002BA94 == '\v') {
        return *B_1002BA94++;
    }

    return *B_1002BA94++;
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

static int func_00411CB8(int arg0) {
    int spC4 = false;
    int spC0 = false;
    char* s1;
    int spB8 = false;
    int spB4 = false;
    int spB0 = false;
    int spAC = false;
    int s4 = false;
    int spA4 = false;    
    char* s2;
    char c;
    char sp9E = 0;        
    char c1;

    if (arg0) {
        s4 = true;
        *B_1002BAA4 = '.';
        s1 = B_1002BAA4 + 1;
    } else {
        s1 = B_1002BAA4;
    }

    if(s4) {} // required to match

    while (c = input()) {
        if (isdigit(c)) {
            *s1++ = c;

            if (s1 == B_1002BAA4 + 1 && c == '0') {
                spC0 = true;
            }
            if (spC0 && c > '7' && sp9E == 0) {
                sp9E = c;
            }
        } else if (c == 'X' || c == 'x') {
            if (s1 == B_1002BAA4 + 1 && *B_1002BAA4 == '0') {
                spC4 = true;
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
            if (arg0) {
                break;
            }

            spC0 = false;
            arg0 = true;
            s4 = true;
            *s1++ = c;
        } else if (c == 'e' || c == 'E') {
            *s1++ = c;
            spC0 = false;
            s4 = true;
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
    B_1002BA94--;
    if (*B_1002BA94 == '\n') {
        yyline--;
    }

    while (c = input()) {
        if (s4 && (c == 'f' || c == 'F')) {
            spAC = true;
            *s1++ = c;
            break;
        } else if (!s4 && !spB8 && (c == 'u' || c == 'U')) {
            spB8 = true;
            *s1++ = c;
            if (spB0) {
                break;
            }
        } else if (!s4 && !spB0 && (c == 'l' || c == 'L')) {
            if (spB4) {
                spB0 = true;
                spB4 = false;
            } else {
                spB4 = true;
            }
            *s1++ = c;
        } else if (s4 && (c == 'l' || c == 'L')) {
            spB4 = true;
            *s1++ = c;
            break;
        } else {
            B_1002BA94--;
            if (*B_1002BA94 == '\n') {
                yyline--;
            }
            break;
        }
    }

    if (s4) {
        if (spAC) {
            func_00411C00(B_1002BAA4, s1, curloc);
            yylval.node = make(0x65, curloc, float_type, string_to_symbol(B_1002BAA4, s1 - B_1002BAA4));
        } else {
            func_00411C5C(B_1002BAA4, s1, curloc);
            yylval.node = make(0x65, curloc, double_type, string_to_symbol(B_1002BAA4, s1 - B_1002BAA4));
        }
        return CONSTANT;
    } else {
        unsigned long s42 = 0;
        int unused;
        unsigned long long sp8C = 0;
        int s52 = spB0;
        int sp80 = 0;
        int sp7C = 0;
        int s6 = false;

        if (s52 && ((options[13] && (options[5] & 1) || !options[13] && (options[5] & 1))) && (options[5] & 5) == 5) {
            error(0x20131, 1, curloc, "long long constants (LL)");
        }

        if (spC4) {
            if (s1 == B_1002BAA4 + 2) {
                spA4 = true;
                error(0x2010B, 0, curloc);
            }
            for (s2 = B_1002BAA4 + 2; s2 < s1; s2++) {
                if (!isxdigit(*s2)) {
                    break;
                }

                sp80 += 4;
                if (!spA4 && !s6 && (s52 && sp8C > __ULONGLONG_MAX / 16 || s42 > 0xFFFFFFFF / 16)) {
                    if (s52 || (options[13] && (options[5] & 1) || !options[13] && (options[5] & 1)) && (options[5] & 5) == 5) {
                        s6 = true;
                    } else {
                        sp7C = true;
                        s52 = true;
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
            for (s2 = B_1002BAA4 + 1; s2 < s1; s2++) {
                if (*s2 < '0' || *s2 > '7') {
                    break;
                }
                sp80 += 3;
                if (!s6 && (s52 && sp8C > __ULONGLONG_MAX / 8 || s42 > 0xFFFFFFFF / 8)) {
                    if (s52 || ((options[13] && (options[5] & 1) || !options[13] && (options[5] & 1))) && (options[5] & 5) == 5) {
                        s6 = true;
                    } else {
                        sp7C = true;
                        s52 = true;
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
            
            for (s2 = B_1002BAA4; s2 < s1; s2++) {
                unsigned int s0;
                if (!isdigit(*s2)) {
                    break;
                }
                s0 = *s2 - '0';
                if (!s6 && (s52 && (sp8C > __ULONGLONG_MAX / 10 || sp8C * 10 > __ULONGLONG_MAX - s0) || (s42 > 0xFFFFFFFF / 10 || s42 * 10 > 0xFFFFFFFF - s0))) {
                    if (s52 || ((options[13] && (options[5] & 1) || !options[13] && (options[5] & 1))) && (options[5] & 5) == 5) {
                        s6 = true;
                    } else {
                        sp7C = true;
                        s52 = true;
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
retfalse:
            return false;
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
                    *arg1 = func_00410E40(*arg1);
                    break;
                case 'a':
                    if (options[13] && (options[5] & 1) || !options[13] && (options[5] & 1)) {
                        *arg1 = func_00410E40(*arg1);
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
                            B_1002BA94--;
                            if (*B_1002BA94 == '\n') {
                                yyline--;
                            }
                            if (value > 255 || (int)value < 0) {
                                error(0x20016, 0, curloc, value, 255);
                            }
                            *arg1 = value;
                            break;
                        } else {
                            B_1002BA94--;
                            if (*B_1002BA94 == '\n') {
                                yyline--;
                            }
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
                    goto retfalse;
                default:                    
                    if (islower(*arg1)) {
                        error(0x20018, 0, curloc, *arg1);
                    }
                    break;
            }
            break;
        default:
            if (*arg1 == arg0) {
                goto retfalse;
            }
            break;
    }
    
    return true;
}

static int func_004136C8(char arg0, char* arg1) {
    char c;
    int i;
    unsigned int value;    
    int unused;
    int sp44 = false;
    int sp40 = false;
    int sp3C = false;    

    if (!func_00413014(arg0, arg1, 1, &sp3C)) {
        return false;
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
                                sp44 = true;
                                break;
                            }
                            if (value >> 28) {
                                sp40 = true;
                            }
                            c = input();
                        }
                        B_1002BA94--;
                        if (*B_1002BA94 == '\n') {
                            yyline--;
                        }
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

    return true;
}

int func_00413B2C(void) {
    char* ptr;    
    int len;
    int unused;
    int sp38 = 0;

    for (ptr = B_1002BAA4, len = 0; func_00413014('"', ptr, 0, &sp38); ptr++, len++) {
        if (len >= B_1002BA9C - 1) {
            adjust_vwbuf();
            ptr = &B_1002BAA4[len];
        }
    }

    *ptr = 0;
    yylval.node = make(0x65, curloc, array_type, B_1002BAA4, ptr - B_1002BAA4 + 1);
    return STRING;
}

int func_00413C54(void) {
    int* ptr;
    int len;

    for (ptr = B_1002BAA8, len = 0; func_004136C8('"', ptr); ptr++, len++) {
        if (len >= (B_1002BA9C >> 2) - 1) {
            adjust_vwbuf();
            ptr = &B_1002BAA8[len];
        }
    }

    *ptr = 0;
    yylval.node = make(0x68, curloc, array_type, B_1002BAA8, len + 1);
    return WSTRING;
}

int func_00413D68(void) {
    char* ptr;
    int sp30 = 0;
    unsigned int len;

    for (ptr = B_1002BAA4; func_00413014('\'', ptr, 0, &sp30); ptr++) {
    }

    len = ptr - B_1002BAA4;
    if (len > 4 || len == 0) {
        error(0x20011, 0, curloc);
    }
    len = ptr - B_1002BAA4;
    switch(len) {
        case 0:
            yylval.node = make_iconstant(curloc, int_type, 0);
            break;
        case 1:
            yylval.node = make_iconstant(curloc, int_type, options[6] ? (signed char)B_1002BAA4[0] : (unsigned char)B_1002BAA4[0]);
            break;
        case 2:
            if (options[2]) {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[6] ? (signed char)B_1002BAA4[0] : (unsigned char)B_1002BAA4[0]) << 8) + B_1002BAA4[1]));
            } else {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[6] ? (signed char)B_1002BAA4[1] : (unsigned char)B_1002BAA4[1]) << 8) + B_1002BAA4[0]));
            }
            break;
        case 3:
            if (options[2]) {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[6] ? (signed char)B_1002BAA4[0] : (unsigned char)B_1002BAA4[0]) << 16) + (B_1002BAA4[1] << 8) + B_1002BAA4[2]));
            } else {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[6] ? (signed char)B_1002BAA4[2] : (unsigned char)B_1002BAA4[2]) << 16) + (B_1002BAA4[1] << 8) + B_1002BAA4[0]));
            }
            break;
        default:
            if (options[2]) {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[6] ? (signed char)B_1002BAA4[0] : (unsigned char)B_1002BAA4[0]) << 24) + (B_1002BAA4[1] << 16) + (B_1002BAA4[2] << 8) + B_1002BAA4[3]));
            } else {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[6] ? (signed char)B_1002BAA4[3] : (unsigned char)B_1002BAA4[3]) << 24) + (B_1002BAA4[2] << 16) + (B_1002BAA4[1] << 8) + B_1002BAA4[0]));
            }
            break;
    }

    return CONSTANT;
}

int func_00414114(void) {
    int* ptr;

    for (ptr = B_1002BAA8; func_004136C8('\'', ptr); ptr++) {
    }

    yylval.node = make_iconstant(curloc, long_type, *B_1002BAA8);
    return CONSTANT;
}

void func_004141BC(void) {

}

int func_004141C4(char arg0) {
    char c;
    char* ptr = B_1002BAA4;
    int len;
    int tp;

    *ptr++ = arg0;

    while (c = input()) {
        if (!(isalnum(c) || c == '_' || c == '$' && options[7])) {
            unput();
            break;
        }

        if (ptr - B_1002BAA4 >= B_1002BA9C) {
            len = ptr - B_1002BAA4;
            adjust_vwbuf();
            ptr = &B_1002BAA4[len];
        }
        *ptr++ = c;
    }

    yylval.identifier.unk_04 = string_to_symbol(B_1002BAA4, ptr - B_1002BAA4);
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
    int sp58;
    int sp54;
    char c;
    char c1;

restart:
    curloc = (int)(B_1002BA94 - B_10023A90) + B_1002BA98 - 1;
    switch (c = input()) {
        case 0:
            B_1002BA94--;
            return 0;
        case '\n':
            c1 = input();
            while (c1 == ' ' || c1 == '\t') {
                c1 = input();
            }
            if (c1 == '#') {
                curloc = (int)(B_1002BA94 - B_10023A90) + B_1002BA98 - 1;
                if (func_00410EBC(&sp58, B_1002BAA4, &sp54) == 1) {
                    if (sp54) {
                        register_file(B_1002BAA4, sp54);
                    } else {
                        register_file("", 1);
                    }

                    if (sp54) {                    
                        while (c = input()) {
                            if (c == '\n') {
                                break;
                            }
                        }
                    }
                } else {
                    c = '\n';
                }
            } else {
                unput();
            }
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
            return func_00411CB8(0);
        case '"':
            return func_00413B2C();
        case '\'':
            return func_00413D68();
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
            if (options[21]) {
                if (input() == ':') {
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
                    if (input() == '*') {
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
                
            }
            
    }
}

void useitall(void) {
    func_00410E40(32);
    func_00410EBC(0,0,0);
    func_004119A0();
    func_00411C00(0, 0, 0);
    func_00411C5C(0, 0, 0);
    func_00411CB8(1);
    func_00413014(0, 0, 0, 0);
    func_004136C8(0, 0);
}