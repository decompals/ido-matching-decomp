#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include "mem.h"

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
static void* B_1002BAA4;
static void* B_1002BAA8;
static int B_1002BAAC;
static FILE* B_1002BAB0;
static int B_1002BAB4;

extern int yyfile;
extern int yyline;
extern char* infile;
extern int origfile;

static char func_004119A0(void);
static char func_00411938(void);
void register_file(char*, int);
int error(int, int, int, ...);
float str_to_float(char* arg0, int arg1, int arg2);
double str_to_double(char* arg0, int arg1, int arg2);

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

#define GETCHAR() (isprint(*B_1002BA94) ? *B_1002BA94++ : func_004119A0())
#define GETCHAR2() (func_00411938() == '\n' ? '\n' : GETCHAR())

static int func_00410EBC(int* arg0, char* arg1, int* arg2) {
    char c;
    char* ptr;

    while (c = GETCHAR()) {
        if (c == ' ' || c == '\t') {
            continue;
        }
        
        if (c == '\n' || c == 0) {
            return 0;
        }

        if (isdigit(c)) {
            break;
        }

        if (c == 'l' && (c = GETCHAR()) == 'i' && (c = GETCHAR()) == 'n' && (c = GETCHAR()) == 'e') {
            continue;
        } else {
out:
            if (origfile == 0) {
                register_file("", 1);
            }
        
            if (c != '\n') {
                while (c = GETCHAR()) {
                    if (c == '\n') {
                        break;
                    }
                }
            }
        
            return 0;
        }
    }

    *arg0 = c - '0';
    while (c = GETCHAR2()) {
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

    while (c = GETCHAR2()) {
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
    while ((c = GETCHAR()) != '"') {
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
                    while (c = GETCHAR()) {
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
            return GETCHAR();
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

// NONMATCHING
static float func_00411C00(char* arg0, char* arg1, int arg2) {
    if (arg0 < arg1) {
        if (arg1[-1] != 0) {
            *arg1 = 0;
        }
        return str_to_float(arg0, arg2, 1);
    }
}

// NONMATCHING
static double func_00411C5C(char* arg0, char* arg1, int arg2) {
    if (arg0 < arg1) {
        if (arg1[-1] != 0) {
            *arg1 = 0;
        }
        return str_to_double(arg0, arg2, 1);
    }
}



void useitall(void) {
    func_00410E40(32);
    func_00410EBC(0,0,0);
    func_004119A0();
    func_00411C00(0, 0, 0);
}

