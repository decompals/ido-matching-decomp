/* Handwritten */

// function __start # 0
#pragma GLOBAL_ASM("asm/functions/cc/__start.s")

// function _mcount # 1
#pragma GLOBAL_ASM("asm/functions/cc/_mcount.s")

#include "signal.h"
#include "wait.h"
#include "cc.h"
#include "sex.h"
#include "sys/times.h"
#include "utime.h"
#include "varargs.h"
#include "errno.h"
#include "unistd.h"

/* File, -O1 */
typedef struct {
    s32 capacity;
    s32 length;
    char** entries;
} list;

static void func_00432C94(void);
void relocate_passes(const char *arg0, const char *arg1, const char *arg2);
void error();
char* mkstr();
char* savestr(const char* src, size_t extra_length);
void get_lino(char* arg0, const char* arg1, s32 arg2);

void cleanup(void);
extern int vflag;

// data
char* LD = "ld";
int ansi_choice = 3;
int c_compiler_choice = 0;

int fiveflag = 0;
int runerror = 0;
int abi_flag = 0;
int non_shared = 0;
int irix4 = 0;
int targetsex = BIGENDIAN;

struct _struct_suffixes_0x8 {
    /* 0x0 */ const char *unk0;
    /* 0x4 */ int unk4;
}; // size = 0x8

struct _struct_suffixes_0x8 suffixes[0xF] = {
    {"pl1", 1 },
    {"pli", 1 },
    {"cob", 2 },
    {"il", 3 },
    {"st", 4 },
    {"anl", 5 },
    {"c++", 6 },
    {"cc", 6 },
    {"cxx", 6 },
    {"C", 6 },
    {"cpp", 6 },
    {"CXX", 6 },
    {"CPP", 6 },
    {".c", 7 },
    {NULL, 0},
};

#pragma GLOBAL_ASM("asm/functions/cc/STR_1000403C.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004044.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_1000404C.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004054.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_1000405C.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004064.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_1000406C.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004074.s")

#pragma GLOBAL_ASM("asm/functions/cc/STR_1000407C.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004084.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004090.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_1000409C.s")

#pragma GLOBAL_ASM("asm/functions/cc/STR_100040A4.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_100040AC.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_100040B4.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_100040BC.s")

char* Gnum = "0";
char *runlib = "/";
char *runlib_base = "/";

static int D_1000BF88 = 0;


int svr4_systype = 0;
int systype_warn = 0;
int user_systype = 0;

char* comp_target_root;
char* currcomp;
char* systype;


// function main # 2
#pragma GLOBAL_ASM("asm/functions/cc/main.s")

// function process_config # 3
void process_config(int argc, char** argv) {
    register int i;
    register char* var_s1;
    char* sp1144 = comp_target_root;
    char* sp1140;
    FILE* sp113C;
    char sp13C[0x1000];
    s32 sp138;
    char* sp38[0x40];

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-systype") == 0) {
            i++;
            if (i >= argc) {
                error(1, 0, 0, 0, 0, "-systype must have an argument\n");
                exit(2);
            }

            user_systype = 1;
            systype = argv[i];
            if (strcmp(systype, "svr4") == 0) {
                svr4_systype = 1;
            } else {
                error(1, 0, 0, 0, 0, "only systype svr4 allowed\n");
                exit(2);
            }

            if ((strcmp(systype, "svr4") != 0) 
                && (strcmp(systype, "bsd43") != 0) 
                && (strcmp(systype, "svr3") != 0) 
                && (strcmp(systype, "sysv") != 0) 
                && (fopen(strcat("/", systype), "r") == NULL) 
                && (systype_warn == 0)) {
                error(2, 0, 0, 0, 0, "This systype doesn't exist on this machine; changed systype to svr3.\n");
                systype_warn = 1;
                systype = "svr3";
            }

            if (svr4_systype == 0) {
                sp1144 = mkstr(comp_target_root, systype, "/", NULL);
            }
            break;
        }
    }

    
    if (user_systype == 0) {
        sp1144 = mkstr(comp_target_root, systype, "/", NULL);
    }
    
    user_systype = 0;
    sp1140 = mkstr(sp1144, "usr/lib/", currcomp, "comp.config", NULL);
    sp113C = fopen(sp1140, "r");
    if (sp113C != NULL) {
        if (1) {} // FAKE
        if (fgets(sp13C, 0x1000, sp113C) != NULL) {
            if (sp13C[strlen(sp13C) - 1] == '\n') {
                sp13C[strlen(sp13C) - 1] = '\0';
            }
            var_s1 = sp13C;
            i = sp138 = 0;
            while (*var_s1 != 0) {
                while ((*var_s1 != '\0') && ((*var_s1 == ' ') || (*var_s1 == '\t'))) {
                    var_s1++;
                }

                if (*var_s1 != 0) {
                    sp38[sp138] = var_s1;
                    sp138 += 1;
                }
    
                while ((*var_s1 != '\0') && (*var_s1 != ' ') && (*var_s1 != '\t')) {
                        var_s1++;
                }
    
                if (*var_s1 != 0) {
                    *var_s1++ = '\0';
                }
            }
            parse_command(sp138, sp38);
        }
    }
}

// function add_info # 4
list asflags;
list ddoptflags;
list fcomflags;
list genflags;
list ldflags;
list optflags;
list uloopflags;
list ulpiflags;
list umergeflags;
list uopt0flags;
list upasflags;

void addstr(list* arg0, char* str);

void add_info(char* str) {
    addstr(&upasflags, str);
    addstr(&fcomflags, str);
    addstr(&ulpiflags, str);
    addstr(&uopt0flags, str);
    addstr(&ddoptflags, str);
    addstr(&optflags, str);
    addstr(&umergeflags, str);
    addstr(&uloopflags, str);
    addstr(&genflags, str);
    addstr(&asflags, str);
    addstr(&ldflags, str);
}

// function parse_command # 5
#pragma GLOBAL_ASM("asm/functions/cc/parse_command.s")




// bss
int compiler;


// function get_host_chiptype # 6
// Blank function
void get_host_chiptype (void) {
}


// function error # 7
static const char* D_1000C1E0[] = {
    "Internal", 
    "Error", 
    "Warning", 
    "Info", 
    "Fix", 
    "", 
};
static char* D_1000C1D8 = NULL;
static char* D_1000C1DC = NULL;


extern s32 Vflag;
extern s32 errno;
extern s32 sys_nerr;


char* progname;

#ifndef PERMUTER

// Print an error. Has to be K&R for the variadic stuff to work in other functions
void error(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB)
    s32 arg0;
    const char* arg1;
    s32 arg2;
    const char* arg3;
    s32 arg4;
    const char* arg5;
    s32 arg6;
    s32 arg7;
    s32 arg8;
    s32 arg9;
    s32 argA;
    s32 argB;
{
    s32 len;
    s32 i;

    if ((Vflag == 0) && (D_1000C1D8 == NULL)) {
        D_1000C1D8 = strrchr(progname, '/');
        if (D_1000C1D8 == NULL) {
            D_1000C1D8 = progname;
        } else {
            D_1000C1D8++;
        }

        len = strlen(D_1000C1D8);
        D_1000C1DC = malloc(len + 2);
        if (D_1000C1DC == NULL) { // malloc failed
            fprintf(stderr, "%s: Error: error (), %d: Out of memory\n", D_1000C1D8, 13332);
            
            if (errno < sys_nerr) {
                fprintf(stderr, "%s: %s\n", D_1000C1D8, sys_errlist[errno]);
            }
            exit(1);
        }

        for (i = 0; i < len; i++) {
            D_1000C1DC[i] = ' ';
        }
        D_1000C1DC[i] = '\0';
    }

    if (arg0 == 5) {
        fprintf(stderr, "%s: ", D_1000C1DC);
    } else {
        fprintf(stderr, "%s: %s: ", D_1000C1D8, D_1000C1E0[arg0]);
    }
    if (arg1 != NULL) {
        if (arg2 != 0) {
            fprintf(stderr, "%s, line %d: ", arg1, arg2);
        } else {
            fprintf(stderr, "%s: ", arg1);
        }
    }
    if (arg3 != NULL) {
        if (arg4 != 0) {
            fprintf(stderr, "%s, line %d: ", arg3, arg4);
        } else {
            fprintf(stderr, "%s: ", arg3);
        }
    }
    if (arg5 == NULL) {
        arg5 = "";
    }
    fprintf(stderr, arg5, arg6, arg7, arg8, arg9, argA, argB);
}
#else
void error(s32 arg0, const char* arg1, s32 arg2, const char* arg3, s32 arg4, const char* arg5, ...);
#endif /* PERMUTER */

// function relocate_passes # 8
#pragma GLOBAL_ASM("asm/functions/cc/relocate_passes.s")


// function newrunlib # 9
void newrunlib(void) {
    if (fiveflag != 0) {
        runlib_base = "usr/5lib";
    } else if (irix4 != 0) {
        runlib_base = "/usr/irix4/";
    } else {
        runlib_base = "/";
    }
    if (gethostsex() == targetsex) {
        runlib = runlib_base;
    } else if (targetsex == BIGENDIAN) {
        runlib = "eb/";
    } else {
        runlib = "el/";
    }
    relocate_passes("rP1EXCOnMFISU", NULL, NULL);
}

// function compose_G0_libs # 10
char* LibCob = NULL;
char* LibDw = " -ldw";
char* LibExc = " -lexc";
char* LibF77 = " -lF77";
char* LibGProf1 = " -lgprof";
char* LibI77 = " -lI77";
char* LibIsam = " -lisam";
char* LibM = " -lm";
char* LibMld = " -lmld";
char* LibP = " -lp";
char* LibPl1 = NULL;
char* LibProf1 = " -lprof";
char* LibSort = NULL;
char* LibU77 = " -lU77";
char* LibXmalloc = " -lxmalloc";

void compose_G0_libs(const char* arg0) {
    for (; *arg0 != '\0'; arg0++) {
        switch (*arg0) {
        case 'P':
            LibP = mkstr(LibP, "_G0", NULL);
            break;
        case 'E':
            LibExc = mkstr(LibExc, "_G0", NULL);
            break;
        case '1':
            LibPl1 = mkstr(LibPl1, "_G0", NULL);
            break;
        case 'C':
            LibCob = mkstr(LibCob, "_G0", NULL);
            break;
        case 'O':
            LibSort = mkstr(LibSort, "_G0", NULL);
            break;
        case 'M':
            LibM = mkstr(LibM, "_G0", NULL);
            break;
        case 'F':
            LibF77 = mkstr(LibF77, "_G0", NULL);
            break;
        case 'I':
            LibI77 = mkstr(LibI77, "_G0", NULL);
            break;
        case 'U':
            LibU77 = mkstr(LibU77, "_G0", NULL);
            break;
        case 'S':
            LibIsam = mkstr(LibIsam, "_G0", NULL);
            break;
        case 'W':
            LibDw = mkstr(LibDw, "_G0", NULL);
            break;
        case 'X':
            LibXmalloc = mkstr(LibXmalloc, "_G0", NULL);
            break;
        case 'n':
            LibProf1 = mkstr(LibProf1, "_G0", NULL);
            break;
        }
    }
}

// function compose_reg_libs # 11
void compose_reg_libs(char* arg0) {
    for (; *arg0 != '\0'; arg0++) {
        switch (*arg0) {
        case 'P':
            LibP = mkstr("libp", ".a", NULL);
            break;
        case 'E':
            LibExc = mkstr("libexc", ".a", NULL);
            break;
        case '1':
            LibPl1 = mkstr("libpl1", ".a", NULL);
            break;
        case 'C':
            LibCob = mkstr("libcob", ".a", NULL);
            break;
        case 'O':
            LibSort = mkstr("libsort", ".a", NULL);
            break;
        case 'M':
            LibM = mkstr("libm", ".a", NULL);
            break;
        case 'F':
            LibF77 = mkstr("libF77", ".a", NULL);
            break;
        case 'I':
            LibI77 = mkstr("libI77", ".a", NULL);
            break;
        case 'U':
            LibU77 = mkstr("libU77", ".a", NULL);
            break;
        case 'S':
            LibIsam = mkstr("libisam", ".a", NULL);
            break;
        case 'n':
            LibProf1 = mkstr("libprof", ".a", NULL);
            LibGProf1 = mkstr("libgprof", ".a", NULL);
            break;
        case 'X':
            LibXmalloc = mkstr("libxmalloc", ".a", NULL);
            break;
        }
    }
}

// function mkstr # 12
/*
 * The compiler built-in symbol _VA_INIT_STATE:
 *	-returns 1 if the va_alist marker is the first
 *		parameter in the parameter list, or
 *	-returns 2 if the va_alist marker is the second
 *		parameter in the parameter list, and the
 *		first parameter has type double, or
 *	-returns 0 otherwise.
 */
#define _VA_INIT_STATE 1

#ifndef PERMUTER

char* mkstr(va_alist)
va_dcl // K&R syntax
{
    register char* ret;
    register const char* arg;
    register u32 len;
    va_list args;

    len = 1;
    va_start(args);
    while ((arg = va_arg(args, const char*)) != NULL) {
            len += strlen(arg);
    }
    va_end(args);
    
    ret = malloc(len);
    if (ret == NULL) {
        error(1, 0, 0, "mkstr ()", 0x38BC, "out of memory\n");
        if (errno < sys_nerr) {
            error(5, 0, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        exit(1);
    }
    *ret = 0;

    va_start(args);
    while ((arg = va_arg(args, const char*)) != NULL) {
        strcat(ret, arg);
    }
    
    va_end(args);
    return ret;
}
#endif /* PERMUTER */

// function mklist # 13
void mklist(list* arg0) {
    if ((arg0->entries = malloc(20 * sizeof(char*))) == NULL) {
        error(1, NULL, 0, "mklist ()", 14561, "out of memory\n");
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        exit(1);
    }
    arg0->capacity = 20;
    arg0->length = 0;
    *arg0->entries = NULL;
}


// function addstr # 14
void addstr(list* arg0, char* str) {
    if ((arg0->length + 1) >= arg0->capacity) {
        if ((arg0->entries = realloc(arg0->entries, (arg0->capacity + 20) * sizeof(char*))) == 0) {
            error(1, NULL, 0, "addstr()", 14595, "out of memory\n");
            if (errno < sys_nerr) {
                error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
            }
            exit(1);
        }
        arg0->capacity += 20;
    }
    arg0->entries[arg0->length] = str;
    arg0->length++;
    arg0->entries[arg0->length] = NULL;
}

// function addspacedstr # 15
void addspacedstr(list* arg0, char* str) {
    char* str_end = str;

    do {
        str_end = strchr(str_end, ' ');
        if (str_end != NULL) {
            *str_end = '\0';
            str_end++;
        }
        if ((arg0->length + 1) >= arg0->capacity) {
            if ((arg0->entries = realloc(arg0->entries, (arg0->capacity + 20) * sizeof(char*))) == NULL) {
                error(1, 0, 0, "addspacedstr()", 14639, "out of memory\n");
                if (errno < sys_nerr) {
                    error(5, 0, 0, NULL, 0, "%s\n", sys_errlist[errno]);
                }
                exit(1);
            }
            arg0->capacity += 20;
        }
        arg0->entries[arg0->length] = str;
        arg0->length += 1;
        arg0->entries[arg0->length] = NULL;
    } while ((str = str_end) != NULL);
}

// function newstr # 16
char* newstr(const char* src) {
    char* dest = malloc(strlen(src) + 1);

    if (dest != NULL) {
        strcpy(dest, src);
    } else {
        error(1, NULL, 0, NULL, 0, "newstr: unable to malloc for string %s\n", src);
        exit(2);
    }
    return dest;
}

// function save_place # 17
int save_place(list* arg0) {
    int ret;

    if ((arg0->length + 1) >= arg0->capacity) {
        if ((arg0->entries = realloc(arg0->entries, (arg0->capacity + 20) * sizeof(char*))) == NULL) {
            error(1, 0, 0, "save_place()", 14695, "out of memory\n");
            
            if (errno < sys_nerr) {
                error(5, 0, 0, NULL, 0, "%s\n", sys_errlist[errno]);
            }
            exit(1);
        }
        arg0->capacity += 20;
    }
    ret = arg0->length;
    arg0->length++;
    arg0->entries[arg0->length] = NULL;
    return ret;
}

// function set_place # 18
void set_place(list* arg0, char* str, int place) {
    if ((place < 0) || (place >= arg0->length)) {
        error(0, 0, 0, "set_place ()", 14726, "place out of range");
        exit(1);
    }
    arg0->entries[place] = str;
}

// function addlist # 19
void addlist(list* arg0, list* arg1) {
    int i;

    if ((arg0->length + arg1->length + 1) >= arg0->capacity) {
        if ((arg0->entries = realloc(arg0->entries, (arg0->capacity + arg1->capacity + 20) * sizeof(char*))) == NULL) {
            error(1, NULL, 0, "addlist ()", 14756, "out of memory\n");
            if (errno < sys_nerr) {
                error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
            }
            exit(1);
        }
        arg0->capacity += arg1->capacity + 20;
    }
    for (i = 0; i < arg1->length; i++) {
            if (arg1->entries[i] != NULL) {
                arg0->entries[arg0->length] = arg1->entries[i];
                arg0->length++;
            }
    }
    arg0->entries[arg0->length] = NULL;
}

// function adduldlist # 20
// Copies onto the end of arg0: up to the first NULL from arg2, then everything from arg1, then the rest of arg2.
void adduldlist(list* arg0, list* arg1, list* arg2) {
    s32 sp3C;
    s32 sp38;

    if ((arg0->length + arg1->length + arg2->length + 1) >= arg0->capacity) {
        
        if ((arg0->entries = realloc(arg0->entries, (arg0->capacity + arg1->capacity + arg2->capacity + 20) * sizeof(char*))) == NULL) {
            error(1, 0, 0, "addlist ()", 14795, "out of memory\n");
            if (errno < sys_nerr) {
                error(5, 0, 0, NULL, 0, "%s\n", sys_errlist[errno]);
            }
            exit(1);
        }
        arg0->capacity += arg1->capacity + arg2->capacity + 20;
    }
    
    for (sp3C = 0; (sp3C < arg2->length) && (arg2->entries[sp3C] != NULL); sp3C++) {
        arg0->entries[arg0->length] = arg2->entries[sp3C];
        arg0->length++;
    }

    for (sp38 = 0; sp38 < arg1->length; sp38++) {
        if (arg1->entries[sp38] != NULL) {
            arg0->entries[arg0->length] = arg1->entries[sp38];
            arg0->length++;
        }
    }

    for (; sp3C < arg2->length; sp3C++) {
        if (arg2->entries[sp3C] != NULL) {
            arg0->entries[arg0->length] = arg2->entries[sp3C];
            arg0->length++;
        }
    }

    arg0->entries[arg0->length] = NULL;
}


// function nodup # 21
s32 nodup(list* arg0, const char* str) {
    register s32 i;
    register char* entry;

    for (i = 0; i < arg0->length; i++) {
        entry = arg0->entries[i];
        if ((entry != NULL) && (strcmp(entry, str) == 0)) {
            return 0;
        }
    }

    return 1;
}

// function getsuf # 22
char getsuf(const char* path) {
    int suflen = 0; // Length of suffix
    int i;
    char ch;
    const char* str = path;

    while (ch = *path++) {
        if (ch == '/') {
            suflen = 0;
            str = path;
        } else {
            suflen++;
        }
    }

    if (suflen < 3) {
        return '\0';
    }

    if (path[-3] == '.') {
        if (path[-2] == 'C') {
            return 6; // ACK?
        }
        return path[-2];
    }

    for (i = suflen - 2; i > 0; i--) {
        if (str[i] == '.') {
            break;
        }
    }

    if (i == 0) {
        return '\0';
    }

    str = &str[i + 1];
    for (i = 0; suffixes[i].unk0 != NULL; i++) {
        if (strcmp(str, suffixes[i].unk0) == 0) {
            return suffixes[i].unk4;
        }
    }

    if (strcmp(str, "for") == 0) {
        return 'f';
    }
    if (strcmp(str, "FOR") == 0) {
        return 'F';
    }
    return '\0';
}

// function mksuf # 23
char* mksuf(const char* path, char value) {
    s32 i; // sp54
    s32 j; // sp50, also suffix length
    size_t sp4C;
    char* sp48;
    char* sp44;
    char* sp40;
    const char* sp3C = NULL;
    char ch; // sp38

    if (value < 8) {
        for (i = 0; suffixes[i].unk0 != NULL; i++) {
            if (suffixes[i].unk4 == value) {
                sp3C = suffixes[i].unk0;
                break;
            }
        }
    
        if (sp3C == NULL) {
            error(0, NULL, 0, "mksuf ()", 0x3A5A, "passed an unknown suffix value: %s\n", value);
            exit(4);
        }
        sp4C = strlen(sp3C);
    } else {
        sp4C = 0;
    }

    i = 0;
    sp40 = sp44 = sp48 = savestr(path, sp4C);

    while (ch = *sp44++) {
        if (ch == '/') {
            i = 0;
            sp40 = sp44;
        } else {
            i++;
        }
    }

    if ((i >= 3) && (sp44[-3] == '.')) {
        if (value < 8) {
            strcpy(sp44 - 2, sp3C);
        } else {
            sp44[-2] = value;
            sp44[-1] = 0;
        }
    } else {
        for (j = i - 2; j > 0; j--) {
            if (sp40[j] == '.') {
                break;
            }
        }

        if (j == 0) {
            error(1, NULL, 0, "mksuf ()", 0x3A81, "Bad file name, no suffix: %s\n", path);
            exit(4);
        }
        sp40 = &sp40[j + 1];
        if (value < 8) {
            strcpy(sp40, sp3C);
        } else {
            sp40[0] = value;
            sp40[1] = 0;
        }
    }

    sp44 = sp48;
    while (*sp48 != '\0') {
        if (*sp48++ == '/') {
            sp44 = sp48;
        }
    }
    return sp44;
}

// function savestr # 24
char* savestr(const char* src, size_t extra_length) {
    char* dest = malloc(strlen(src) + extra_length + 1);

    if (dest == NULL) {
        error(1, NULL, 0, "savestr ()", 15014, "out of memory\n");
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        exit(1);
    }
    strcpy(dest, src);
    return dest;
}

// function mktempstr # 25
const char* filter = NULL;
s32 nofilt = 0;
extern char* tmpdir;
extern char* tempstr[34];

void mktempstr(void) {
    tempstr[0] = mktemp(mkstr(tmpdir, "ctmstXXXXXX", 0));
    tempstr[1] = mktemp(mkstr(tmpdir, "ctmuXXXXXX", 0));
    tempstr[2] = mktemp(mkstr(tmpdir, "ctmpXXXXXX", 0));
    tempstr[3] = mktemp(mkstr(tmpdir, "ctmfXXXXXX", 0));
    tempstr[4] = mktemp(mkstr(tmpdir, "ctmluXXXXXX", 0));
    tempstr[5] = mktemp(mkstr(tmpdir, "ctmsXXXXXX", 0));
    tempstr[6] = mktemp(mkstr(tmpdir, "ctmmXXXXXX", 0));
    tempstr[7] = mktemp(mkstr(tmpdir, "ctmoXXXXXX", 0));
    tempstr[8] = mktemp(mkstr(tmpdir, "ctmosXXXXXX", 0));
    tempstr[9] = mktemp(mkstr(tmpdir, "ctmcbXXXXXX", 0));
    tempstr[10] = mktemp(mkstr(tmpdir, "ctmcXXXXXX", 0));
    tempstr[11] = mktemp(mkstr(tmpdir, "ctmaXXXXXX", 0));
    tempstr[12] = mktemp(mkstr(tmpdir, "ctmbXXXXXX", 0));
    tempstr[13] = mktemp(mkstr(tmpdir, "ctmlXXXXXX", 0));
    tempstr[14] = mktemp(mkstr(tmpdir, "ctmm4XXXXXX", 0));
    tempstr[15] = mktemp(mkstr(tmpdir, "ctmgtXXXXXX", 0));
    tempstr[16] = mktemp(mkstr(tmpdir, "ctmilXXXXXX", 0));
    tempstr[17] = mktemp(mkstr(tmpdir, "ctmltXXXXXX", 0));
    tempstr[18] = mktemp(mkstr(tmpdir, "ctmp1XXXXXX", 0));

    tempstr[20] = mktemp(mkstr(tmpdir, "ctmpdXXXXXX", 0));
    tempstr[19] = mktemp(mkstr(tmpdir, "ctmddXXXXXX", 0));
    tempstr[21] = mktemp(mkstr(tmpdir, "ctmloXXXXXX", 0));
    tempstr[22] = mktemp(mkstr(tmpdir, "ctmciXXXXXX", 0));
    tempstr[23] = mktemp(mkstr(tmpdir, "ctmvXXXXXX", 0));
    tempstr[24] = mktemp(mkstr(tmpdir, "ctmerrXXXXXX", 0));
    tempstr[25] = mktemp(mkstr(tmpdir, "ctmemXXXXXX", 0));
    tempstr[26] = mktemp(mkstr(tmpdir, "ctmeXXXXXX", 0));
    tempstr[27] = mktemp(mkstr(tmpdir, "ctmdXXXXXX", 0));
    tempstr[28] = mktemp(mkstr(tmpdir, "ctmqXXXXXX", 0));
    tempstr[29] = mktemp(mkstr(tmpdir, "ctmqsXXXXXX", 0));
    //! @bug 5 Xs instead of 6
    tempstr[30] = mktemp(mkstr(tmpdir, "ctmelfXXXXX", 0));
    tempstr[31] = mktemp(mkstr(tmpdir, "ctmkXXXXXX", 0));

    tempstr[33] = mktemp(mkstr(tmpdir, "ctmcmdXXXXXX", 0));

    // 0x10 argument of access doesn't make sense
    if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (nofilt == 0) && (access(filter, 0x10) == 0)) {
        tempstr[32] = mktemp(mkstr(tmpdir, "ctmfiltXXXXXX", NULL));
    } else {
        tempstr[32] = NULL;
    }
}

// function run # 26
#pragma GLOBAL_ASM("asm/functions/cc/run.s")

// function edit_src # 27
int editflag = 0;
extern s32 xserver;
extern char* errout;

s32 edit_src(const char* arg0, char* arg1, s32 arg2) {
    s32 pad[3];
    char* sp58;
    pid_t fokrPid;
    pid_t sp50;
    s32 temp_t7; // sp4C
    SIG_PF sp48;
    SIG_PF sp44;
    s32 stat_loc;

    fokrPid = fork();
    if (fokrPid == (pid_t)-1) {
        // fork failed
        error(1, NULL, 0, NULL, 0, "fork to edit failed\n");
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        return -1;
    }

    if (fokrPid ==(pid_t)0) {
        // children process

        if (editflag == 2) {
            get_lino(sp58, arg1, arg2);
            execlp(arg0, arg0, sp58, arg1, "-l", tempstr[25], "-f", "err-window", (char*)NULL);
        } else if (xserver == 0) {
            execlp(arg0, arg0, "+1", errout, arg1, (char*)NULL);
        } else {
            execlp("xterm", "xterm", "-display", xserver, "-ls", "-e", arg0, "+1", errout, arg1, (char*)NULL);
        }
        error(1, NULL, 0, NULL, 0, "failed to exec: %s\n", arg0);
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }

        exit(1);
        return;
    }

    // this process, fokrPid is the pid of the child process

    sp44 = sigset(SIGINT, SIG_IGN);
    sp48 = sigset(SIGTERM, SIG_IGN);
    sp50 = wait(&stat_loc);
    while (sp50 != fokrPid) {
        if (sp50 == -1) {
            return -1;
        }
        sp50 = wait(&stat_loc);
    }

    sigset(SIGINT, sp44);
    sigset(SIGTERM, sp48);
    temp_t7 = stat_loc & 0xFF;
    if ((temp_t7 != 0) && (temp_t7 != 2)) {
        fprintf(stderr, "Fatal error in: %s ", arg0);
        printf(" Signal %d ", temp_t7);
        if (stat_loc & WCOREFLAG) {
            fprintf(stderr, "- core dumped\n");
        } else {
            fprintf(stderr, "\n");
        }
        cleanup();
        exit(temp_t7);
    }
    if (temp_t7 == 2) {
        cleanup();
        exit(3);
    }

    return stat_loc & 0xFF00;
}

// function get_lino # 28
#define GET_LINO_BUF_SIZE 0x800
void get_lino(char* arg0, const char* arg1, s32 arg2) {
    char* sp83C;
    int sp838;
    char* sp834 = arg0;
    char* sp830;
    char sp30[GET_LINO_BUF_SIZE];

    *arg0 = '+';
    sp834++;
    sp83C = open(errout, 0);
    sp838 = read(sp83C, &sp30, GET_LINO_BUF_SIZE);
    close(sp83C);

    if (sp838 < GET_LINO_BUF_SIZE) {
        sp30[sp838] = 0;
    } else {
        sp30[GET_LINO_BUF_SIZE - 1] = 0;
    }

    switch (arg2) {
        case 1:
        case 2:
            for (sp830 = sp30; sp830 < sp30 + sp838; sp830++) {
                if ((strncmp(sp830, ": Error: ", 9) == 0) 
                    && ((sp830 = strchr(sp830, ',')) != NULL) 
                    && (strncmp(sp830 - strlen(arg1), arg1, strlen(arg1)) == 0) 
                    && (strncmp(sp830, ", line ", 7) == 0)) {
                    sp830 += 7;
                    while (isdigit(*sp830) && ((sp834 - arg0) <= 10)) {
                        *sp834++ = *sp830++;
                    }
                    break;
                }
            }
            break;
    
            case 3:
            for (sp830 = sp30; sp830 < sp30 + sp838; sp830++) {
                if (strncmp(sp830, "Error on line ", 14) == 0) {
                    sp830 += 14;
                    while (isdigit(*sp830) && ((sp834 - arg0) <= 10)) {
                        *sp834++ = *sp830++;
                    }
                    break;
                }
            }
            break;
    
        case 5:
        case 6:
            for (sp830 = sp30; sp830 < sp30 + sp838; sp830++) {
                if (strncmp(sp830, "ERROR ", 6) == 0) {
                    sp830 += 6;
                    break;
                }
            }
    
            for (; sp830 < sp30 + sp838; sp830++) {
                if (strncmp(sp830, " LINE ", 6) == 0) {
                    sp830 += 6;
                    while (isdigit(*sp830) && ((sp834 - arg0) <= 10)) {
                        *sp834++ = *sp830++;
                    }
                    break;
                }
            }
            break;

        default:
            break;
    }

    if ((arg0 + 1) < sp834) {
        sp834[0] = 0;
    } else {
        sp834[0] = 0x31;
        sp834[1] = 0;
    }
}

// function show_err # 29
#define BUF_SIZE 0x10000
void show_err(const char* path) {
    int desc;
    int bytes_read;
    char buf[BUF_SIZE];

    desc = open(path, O_RDONLY);
    bytes_read = read(desc, buf, BUF_SIZE);
    close(desc);

    if (bytes_read < BUF_SIZE) {
        buf[bytes_read] = '\0';
    } else {
        buf[BUF_SIZE - 1] = '\0';
    }
    fprintf(stderr, "%s\n", buf);
}
#undef BUF_SIZE

// function handler # 30
void handler(void) {
    cleanup();
    exit(3);
}

// function cleanup # 31
int Kflag = 0;
char* passout;
char* passin;
char srcsuf;
int Eflag = 0;
int tmpst;
char* symtab;
char* lpi_st;
char* lpi_p1;
char* lpi_pd;
char* lpi_dd;
char* uopt0str;
char* ddoptstr;
char* optstr;
char* gentmp;
char* binasm;
char* linkorder;
char* tmp_uldobj;
int editflag;
char* tempstr[34];

char* errout;

void cleanup(void) {
    if (Kflag == 0) {
        if (passout != NULL) {
            unlink(passout);
        }
        if (passin != NULL) {
            char sp27 = getsuf(passin);
            if (((sp27 == 0)) || ((sp27 != srcsuf) && (sp27 != 'm'))) {
                if (Eflag == 0) {
                    unlink(passin);
                }
            }
        }
        if (tmpst != 0) {
            if (symtab != NULL) {
                unlink(symtab);
            }
        }
        if (lpi_st != NULL) {
            unlink(lpi_st);
        }
        if (lpi_p1 != NULL) {
            unlink(lpi_p1);
        }
        if (lpi_pd != NULL) {
            unlink(lpi_pd);
        }
        if (lpi_dd != NULL) {
            unlink(lpi_dd);
        }
        if (uopt0str != NULL) {
            unlink(uopt0str);
        }
        if (ddoptstr != NULL) {
            unlink(ddoptstr);
        }
        if (optstr != NULL) {
            unlink(optstr);
        }
        if (gentmp != NULL) {
            unlink(gentmp);
        }
        if (binasm != NULL) {
            unlink(binasm);
        }
        if (linkorder != NULL) {
            unlink(linkorder);
        }
        if (tmp_uldobj != NULL) {
            unlink(tmp_uldobj);
        }
        if (editflag != 0) {
            unlink(errout);
            if (editflag == 2) {
                unlink(tempstr[25]);
            }
        }
        if (compiler == 1) {
            unlink(tempstr[33]);
        }
    }
}

// function whats # 32
void whats(void) {
    s32 sp24 = runerror;

    if (compiler == 2) {
        printf("%s  (%s)\n", progname, "pc");
    } else if (compiler == 4) {
        printf("%s  (%s)\n", progname, "as");
    } else if (compiler == 3) {
        printf("%s  (%s)\n", progname, "f77");
    } else if (compiler == 5) {
        printf("%s  (%s)\n", progname, "pl1");
    } else if (compiler == 6) {
        printf("%s  (%s)\n", progname, "cobol");
    } else {
        printf("%s  (%s)\n", progname, "cc");
    }
    printf("\tMips Computer Systems %d.%d\n", 7, 10);
}

// function settimes # 33
clock_t time0;
struct tms tm0;

void settimes(void) {
    time0 = times(&tm0);
}

// function dotime # 34
#define CLOCK_TICKS 100

void dotime(const char* programName) {
    clock_t time1; // sp6C;
    clock_t clockTimeDiff;
    f64 milis; // sp60
    f64 seconds; // sp58
    struct tms tm1; //sp48;

    time1 = times(&tm1);
    milis = (f64) (tm1.tms_utime + tm1.tms_cutime - tm0.tms_utime - tm0.tms_cutime) / CLOCK_TICKS;
    seconds = (f64) (tm1.tms_stime + tm1.tms_cstime - tm0.tms_stime - tm0.tms_cstime) / CLOCK_TICKS;
    clockTimeDiff = time1 - time0;
    fprintf(stderr, "%s phase time: %.2fu %.2fs %u:%04.1f %.0f%%\n", programName, milis, seconds, clockTimeDiff / (60 * CLOCK_TICKS), (f64) (clockTimeDiff % (60 * CLOCK_TICKS)) / CLOCK_TICKS, ((milis + seconds) / ((f64) clockTimeDiff / CLOCK_TICKS)) * 100.0);
}

// function func_0042FD7C # 35
// Search for a lib in directories (?)
static char* func_0042FD7C(const char* name, char** dirs) {
    s32 fildes;
    char* path;

    for (; *dirs != NULL; dirs++) {
        if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
            fildes = open(path = mkstr(*dirs, "/DCC", runlib, name, NULL), 0, 0);
            if (fildes >= 0) {
                close(fildes);
                return path;
            }
        }

        fildes = open(path = mkstr(*dirs, runlib, name, NULL), 0, 0);
        if (fildes >= 0) {
            close(fildes);
            return path;
        }
    }

    if (abi_flag != 0) {
        path = mkstr("/", "usr/lib/abi", runlib, name, NULL);
    } else if (non_shared != 0) {
        path = mkstr("/", "usr/lib/nonshared", runlib, name, NULL);
    } else {
        path = mkstr("/", "usr/lib", runlib, name, NULL);
    }
    return path;
}


// function isdir # 36
int isdir(const char* path) {
    s32 spAC;
    struct stat statbuf;

    spAC = stat(path, &statbuf);
    if (spAC == -1) {
        return 0;
    }
    if ((statbuf.st_mode & 0xF000) == 0x4000) {
        return 1;
    }
    return 0;
}

// function regular_not_writeable # 37
int regular_not_writeable(const char* arg0) {
    s32 sp24;

    if (regular_file(arg0) != 1) {
        return 0;
    }
    sp24 = open(arg0, 2, 0777);
    if (sp24 >= 0) {
        close(sp24);
        return 0;
    }
    return 1;
}

// function regular_file # 38
// Needs stat.h
int regular_file(const char* path) {
    s32 spAC;
    struct stat statbuf;

    spAC = stat(path, &statbuf);
    if (spAC == -1) {
        return -1;
    }
    if ((statbuf.st_mode & 0xF000) != 0x8000) {
        return 0;
    }
    return 1;
}

// function basename # 39
static char B_1000E5E0[0x400];

// Obtain the base name of a file path, i.e. the part after the final '/'
char* basename(const char* path) {
    register char* ret;
    register char* str = B_1000E5E0;
    register size_t len;

    if ((path == NULL) || (*path == 0)) {
        return strcpy(str, ".");
    }

    ret = strcpy(str, path);
    len = strlen(ret);
    ret += len;

    while ((ret != str) && (*--ret == '/')) {
        *ret = '\0';
    }

    while (ret != str) {
        if (*--ret == '/') {
            ret++;
            return ret;
        }
    }

    return ret;
}

// function dirname # 40
// Obtain the directory name of a file path, i.e. the part before the final '/'
const char* dirname(const char* path) {
    register char* ret;
    register char* str = B_1000E5E0;
    register size_t len;

    if ((path == NULL) || (*path == 0)) {
        return strcpy(str, ".");
    }

    ret = strcpy(str, path);
    len = strlen(ret);
    ret += len;

    while ((ret != str) && *--ret == '/') {}

    if ((ret == str) && (*ret == '/')) {
        return strcpy(str, "/");
    }

    while (ret != str) {
        if (*--ret == '/') {
            if (ret == str) {        
                return strcpy(str, "/");
            }
            while (*ret == '/') {
                ret--;
            }
            ret++;
            *ret = 0;
            return str;
        }
    }
    
    return strcpy(str, ".");
}

// function func_00430414 # 41
struct _struct_prod_name_0xC {
    /* 0x0 */ const char *unk0; // name?
    /* 0x4 */ const char *unk4; // full path?
    /* 0x8 */ const char *unk8; // description?
}; // size = 0xC

struct _struct_prod_name_0xC prod_name[] = {
    { "accom", "/usr/lib/accom", "ANSI C" },
    { "ccom", "/usr/lib/ccom", "ANSI C" },
    { "acpp", "/usr/lib/acpp", "ANSI C" },
    { "cpp", "/usr/lib/cpp", "Development option" },
    { "fcom", "/usr/lib/fcom", "Fortran" },
    { "fopt", "/usr/lib/fopt", "Fortran" },
    { "pfa", "/usr/lib/pfa", "Power Fortran" },
    { "accom_mp", "/usr/lib/accom_mp", "Power C" },
    { "ccom_mp", "/usr/lib/ccom_mp", "Power C" },
    { "pca", "/usr/lib/pca", "Power C" },
    { "copt", "/usr/lib/copt", "ANSI C" },
    { "upas", "/usr/lib/upas", "Pascal" },
    { "pl1fe", "/usr/lib/pl1fe", "PL/1" },
    { "pl1error", "/usr/lib/pl1error", "PL/1" },
    { "as0", "/usr/lib/as0", "Development option" },
    { "as1", "/usr/lib/as1", "Development option" },
    { "ld", "/usr/lib/ld", "Development option" },
    { "cobfe", "/usr/lib/cobfe", "COBOL" },
    { "edgcpfe", "/usr/lib/DCC/edgcpfe", "Delta C++" },
    { "edgcpfe.alt", "/usr/lib/DCC/edgcpfe.alt", "C++" },
};

static const char* func_00430414(char* arg0, int arg1) {
    int i;
    int sp28;
    char* sp24;
    const char* sp20;

    if (arg1 != 0) {
        sp24 = arg0;
    } else {
        sp24 = strrchr(arg0, '/');
        if (sp24 != NULL) {
            sp24++;
        }
    }

    sp28 = 20;
    for(i = 0; i < sp28; i++) {
        if (arg1 != 0) {
            sp20 = prod_name[i].unk4;
        } else {
            sp20 = prod_name[i].unk0;
        }
        if (strcmp(sp24, sp20) == 0) {
            return prod_name[i].unk8;
        }
    }
    return NULL;
}

// function force_use_cfront # 42
static int D_1000BF7C;
static int D_1000BF90;

extern char* comp_host_root;
extern int exception_handling;
extern list execlist;

int force_use_cfront(int argc, char** argv) {
    int i;
    char* sp28 = getenv("USE_CFRONT");
    int sp24 = 0;

    if ((sp28 != NULL) && (*sp28 != '0')) {
        return 1;
    }

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-exceptions") == 0) {
            D_1000BF7C = 1;
        }
        if ((D_1000BF7C == 0) && (exception_handling == 0) && ((strcmp(argv[i], "-F") == 0) || (strcmp(argv[i], "-Fc") == 0))) {
            return 1;
        }
        if ((strcmp(argv[i], "-use_cfront") == 0) || (strcmp(argv[i], "-v2") == 0) || (strcmp(argv[i], "+I") == 0) || (strncmp(argv[i], "-.", 2) == 0)) {
            return 1;
        }
    }
    return 0;
}

// function exec_OCC # 43
void exec_OCC(int argc, char** argv) {
    char spB8[0x400];
    char pad[0x88]; // !

    sprintf(spB8, "%susr/bin/OCC", comp_host_root);
    *argv = spB8;
    execv(spB8, argv);
    error(2, NULL, 0, NULL, 0, "could not exec %s", spB8);
}

// function add_cxx_symbol_options # 44
int add_cxx_symbol_options(void) {
    addstr(&execlist, "-cxx");
    if ((D_1000BF90 == 0) && (strcmp(LD, "old_ld") != 0)) {
        addstr(&execlist, "-woff");
        addstr(&execlist, "134");
    }
    return 0;
}

// function init_curr_dir # 45
static char* D_1000C1D0 = NULL; // full path of current working directory
static char* D_1000C2F0 = NULL; // basename of progname (?)

void init_curr_dir(void) {
    if (D_1000C2F0 == 0) {
        D_1000C2F0 = strrchr(progname, '/');
        if (D_1000C2F0 == 0) {
            D_1000C2F0 = progname;
        } else {
            D_1000C2F0++;
        }
    }
    if (D_1000C1D0 == NULL) {
        D_1000C1D0 = getcwd(NULL, 0x400);
        if (D_1000C1D0 == NULL) {
            D_1000C1D0 = getenv("PWD");
            if (D_1000C1D0 == NULL) {
                D_1000C1D0 = ".";
            }
        }
        if (strncmp(D_1000C1D0, "/tmp_mnt", 8) == 0) {
            D_1000C1D0 += 8;
        }
    }
}


// function full_path # 46
char* full_path(const char* relative_path) {
    char* path;

    init_curr_dir();
    if (*relative_path == '/') {
        path = mkstr(relative_path, NULL);
    } else {
        path = mkstr(D_1000C1D0, "/", relative_path, 0);
    }
    return path;
}

// function add_static_opt # 47
list staticopts;

void add_static_opt(char* opt) {
    if (D_1000BF88 == 0) {
        addstr(&staticopts, opt);
    }
}

// function record_static_fileset # 48
static char* D_1000BF80;
static char* D_1000BF84;
static char* D_1000C2E8;
static char* D_1000C2EC;
char* tmpdir;

void record_static_fileset(s32 arg0) {
    s32 sp28E4;
    FILE* sp28E0;
    FILE* sp28DC;
    s32 sp28D8;
    char spD8[0x2800];
    char* spD4;
    size_t spD0;
    char spBC[20];
    struct stat sp34;

    sprintf(spBC, ".%d", getpid());

    if (D_1000BF80 == NULL) {
        D_1000BF80 = "";
    }

    if (D_1000BF84 == NULL) {
        D_1000BF84 = mkstr("cvstatic.fileset", NULL);
    }

    if ((*D_1000BF84 == '/') || (*D_1000BF80 == 0)) {
        D_1000C2E8 = mkstr(D_1000BF84, NULL);
    } else {
        D_1000C2E8 = mkstr(D_1000BF80, D_1000BF84, NULL);
    }

    D_1000C2EC = mkstr(tmpdir, "cvstatic.fileset", &spBC, 0);
    spD4 = full_path(arg0);
    spD0 = strlen(spD4);

    if (vflag != 0) {
        fprintf(stderr, "Static fileset: %s %s", spD4, D_1000C2F0);
        for (sp28E4 = 0; sp28E4 < staticopts.length; sp28E4++) {
            fprintf(stderr, " %s", staticopts.entries[sp28E4]);
        }
        fprintf(stderr, "\n");
    }

    sp28E0 = fopen(D_1000C2EC, "w+");
    if (sp28E0 == NULL) {
        error(1, 0, 0, "record_static_fileset", 0, "could not open cvstatic fileset temp file %s\n", D_1000C2EC);
        perror(D_1000C2F0);
        cleanup();
        exit(1);
    }

    sp28D8 = open(D_1000C2E8, 0x102, 0777);
    if (sp28D8 < 0) {
        error(1, 0, 0, "record_static_fileset", 0, "could not open or create cvstatic fileset file %s\n", D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }

    if (flock(sp28D8, 2) < 0) {
        error(1, 0, 0, "record_static_fileset", 0, "error in locking cvstatic fileset file %s\n", D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }

    if (fstat(sp28D8, &sp34) < 0) {
        error(1, 0, 0, "record_static_fileset", 0, "could not fstat cvstatic fileset file %s\n", D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }

    if (sp34.st_size == 0) {
        fprintf(sp28E0, "-cvstatic\n");
    }

    sp28DC = fdopen(sp28D8, "r+");
    if (sp28DC == NULL) {
        error(1, 0, 0, "record_static_fileset", 0, "could not fdopen cvstatic fileset file %s\n", D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }

    while (fgets(spD8, 0x2800, sp28DC) != 0) {
        if ((strncmp(spD8, spD4, spD0) != 0) || !(__ctype[spD8[spD0] + 1] & 8)) {
            fputs(spD8, sp28E0);
        }
    }
    fprintf(sp28E0, "%s %s", spD4, D_1000C2F0);

    for (sp28E4 = 0; sp28E4 < staticopts.length; sp28E4++) {
        fprintf(sp28E0, " %s", staticopts.entries[sp28E4]);
    }
    fprintf(sp28E0, "\n");

    free(spD4);
    rewind(sp28DC);
    rewind(sp28E0);
    ftruncate(sp28DC->_file, 0);

    while ((sp28E4 = fread(spD8, 1, 0x2800, sp28E0)) > 0) {
        if (fwrite(&spD8, 1, sp28E4, sp28DC) != sp28E4) {
            error(1, 0, 0, "record_static_fileset", 0, "error in writing cvstatic fileset file %s\n", D_1000C2E8);
            perror(D_1000C2F0);
            unlink(D_1000C2EC);
            cleanup();
            exit(1);
        }
    }

    fclose(sp28DC);
    fclose(sp28E0);
    unlink(D_1000C2EC);
    free(D_1000C2E8);
    free(D_1000C2EC);
}

// function touch # 49
// Needs utime.h
int touch(const char* arg0) {
    time_t curtime = time(NULL);
    struct utimbuf sp34;
    char* str;

    init_curr_dir();
    if (vflag != 0) {
        fprintf(stderr, "%s: touch %s\n", D_1000C2F0, arg0);
    }
    sp34.modtime = curtime;
    sp34.actime = curtime;
    if (utime(arg0, &sp34) < 0) {
        str = malloc(strlen(arg0) + strlen(D_1000C2F0) + 10);
        sprintf(str, "%s: touch %s", D_1000C2F0, arg0);
        perror(str);
        free(str);
        return -1;
    }
    return 0;
}

// function add_prelinker_objects # 50
void add_prelinker_objects(list* arg0, list* arg1) {
    int i;

    for (i = 0; i < arg1->length; i++) {
        if ((arg1->entries[i][0] == '-') 
            && (arg1->entries[i][1] != 'l') 
            && (arg1->entries[i][1] != 'L')) {
            if (1) {} // FAKE

            if (strcmp(arg1->entries[i], "-nostdlib") == 0) {
                addstr(arg0, mkstr("-YB", NULL));
            } else if (strcmp(arg1->entries[i], "-objectlist") == 0) {
                addstr(arg0, mkstr("-YO=", arg1->entries[i + 1], NULL));
                i++;
            } else if (strcmp(arg1->entries[i], "-B") == 0) {
                i++;
                if (strcmp(arg1->entries[i], "static") == 0) {
                    addstr(arg0, mkstr("-Bstatic", NULL));
                } else if (strcmp(arg1->entries[i], "dynamic") == 0) {
                    addstr(arg0, mkstr("-Bdynamic", NULL));
                }
            }
        } else {
            addstr(arg0, arg1->entries[i]);
        }
    }
}

// function quoted_length # 51
size_t quoted_length(const char* arg0, int* arg1) {
    u32 len = 0;
    u8 ch;

    *arg1 = 0;
    while (ch = *arg0++) { // != 0 does not match
        if (*arg1 == 0) {
            if ((ch == '\'') || (ch == '|') || (ch == '&') || (ch == '*') || (ch == '?') || (ch == '[') || (ch == ']') || (ch == ';') || (ch == '!') || (ch == '(') || (ch == ')') || (ch == '^') || (ch == '<') || (ch == '>') || (ch <= ' ') || (ch == '\t') || (ch == '\"') || (ch == '\\') || (ch == '`') || (ch == '$')) {
                *arg1 = 1;
                len += 2;
            }
        }
        if ((ch == '"') || (ch == '\\') || (ch == '`') || (ch == '$')) {
            len++;
        }
        len++;
    }
    return len;
}


// function quote_shell_arg # 52
size_t quote_shell_arg(const char* arg0, char* arg1) {
    char ch;
    int sp28;
    size_t len;

    sp28 = 0;
    len = quoted_length(arg0, &sp28);
    if (sp28 != 0) {
        *arg1++ = '""';
    }
    
    while ((ch = *arg0++)) { // != 0 does not match
        if ((ch == '"') || (ch == '\\') || (ch == '`') || (ch == '$')) {
            *arg1++ = '\\';
        }
        *arg1++ = ch;
    }

    if (sp28 != 0) {
        *arg1++ = '"';
    }
    return len;
}

// function func_00431A3C # 53
static int B_1000E4C0; // argc
static char** B_1000E4C4; // argv
static char* B_1000ECDC;

static void func_00431A3C(int argc, char** argv) {
    int i;

    B_1000E4C0 = argc;
    B_1000E4C4 = malloc((argc + 1) * sizeof(char*));

    for (i = 0; i < argc; i++) {        
        if (argv[i] != NULL) {
            B_1000E4C4[i] = strdup(argv[i]);
        } else {
            B_1000E4C4[i] = NULL;
        }
    }
    B_1000E4C4[B_1000E4C0] = NULL;
}

// function func_00431B38 # 54
static void func_00431B38(int first, int count) {
    int i;

    for (i = 0; i < count; i++) {
        B_1000E4C4[first + i] = NULL;
    }
}

// function func_00431B88 # 55
static char* B_1000ECCC;
int cflag = 0;
list srcfiles;

// arg2 is verbosity?
static void func_00431B88(FILE* arg0, const char* arg1, s32 arg2) {
    if (arg2) {
        fputs("CMDLINE=", arg0);
    }
    fprintf(arg0, "%s ", progname);
    if (cflag == 0) {
        fputs("-c ", arg0);
    }
    if ((srcfiles.length == 1) && (cflag != 0)) {
        if (B_1000ECCC != 0) {
            fprintf(arg0, "-o %s ", B_1000ECCC);
        }
    }
    fprintf(arg0, "%s %s\n", B_1000ECDC, arg1);
    if (arg2) {
        fputs("PWD=", arg0);
    }
    fprintf(arg0, "%s\n", D_1000C1D0);
    if (arg2) {
        fputs("----\n", arg0);
    }
}

// function func_00431D00 # 56
static void func_00431D00(const char* arg0) {
    FILE* file = fopen(tempstr[33], "w");

    if (file != NULL) {
        init_curr_dir();
        func_00431B88(file, arg0, FALSE);
        fclose(file);
    } else {
        error(2, NULL, 0, NULL, 0, "cannot open commandfile '%s'\n", tempstr[33]);
    }
}

// function func_00431DD8 # 57
static void func_00431DD8(void) {
    int sp34 = 0;
    int sp30 = 0;
    int sp2C = 0;
    int i;
    char* sp24;

    for (i = 1; i < B_1000E4C0; i++) {
        if (B_1000E4C4[i] != NULL) {
            sp34 += quoted_length(B_1000E4C4[i], &sp2C) + 1;
        }
    }

    B_1000ECDC = sp24 = malloc(sp34 + 1);
    for (i = 1; i < B_1000E4C0; i++) {
        if (B_1000E4C4[i] != NULL) {
            sp24 += quote_shell_arg(B_1000E4C4[i], sp24);
            *sp24 = ' ';
            sp24++;
        }
    }

    if (sp24 > B_1000ECDC) {
        sp24[-1] = '\0';
    } else {
        sp24[0] = '\0';
    }
}


// function skip_old_ii_controls # 58
#define EOF	(-1) // can go when headers in

// Search file for the first "----" and move position to the line after it
void skip_old_ii_controls(FILE* arg0) {
    s32 ch;
    s32 sp50 = FALSE;

    ch = getc_locked(arg0);
    while (ch != EOF) {
        if (ch == '-' 
            && (ch = getc_locked(arg0)) == '-' 
            && (ch = getc_locked(arg0)) == '-' 
            && (ch = getc_locked(arg0)) == '-') {
            sp50 = TRUE;
        }

        while ((ch != '\n') && (ch != EOF)) {
                ch = getc_locked(arg0);
        }

        if (sp50) {
            break;
        }

        if (ch == '\n') {
            ch = getc_locked(arg0);
        }
    }
    if (ch == EOF) {
        rewind(arg0);
    }
}

// function make_ii_file_name # 59
// path/to/file -> path/to/ii_files/file.ii
// path/to/file.o -> path/to/ii_files/file.ii
char* make_ii_file_name(const char* arg0) {
    char* sp2C; // basename
    size_t sp28; // basename length

    sp2C = basename(arg0);
    sp28 = strlen(sp2C);
    sp2C = mkstr(sp2C, "   ", 0);
    if ((sp2C[sp28 - 2] == '.') && (sp2C[sp28 - 1] == 'o')) {
        strcpy(&sp2C[sp28 - 1], "ii");
    } else {
        strcpy(&sp2C[sp28], ".ii");
    }
    return mkstr(dirname(arg0), "/ii_files/", sp2C, 0);
}

// function update_instantiation_info_file # 60
// TODO: type of error(), name vars
int vflag = 0;

void update_instantiation_info_file(const char* arg0, const char* arg1) {
    char* sp54 = make_ii_file_name(arg1);
    char* sp50 = mkstr(sp54, ".NEW", 0);
    FILE* sp4C = fopen(sp54, "r");
    FILE* sp48;
    int sp44;

    if (sp4C != NULL) {
        init_curr_dir();
        if (vflag) {
            fprintf(stderr, "%s: update_instantiation_info_file %s\n", D_1000C2F0, sp54);
        }
        sp48 = fopen(sp50, "w");
        if (sp48 == NULL) {
            error(1, NULL, NULL, "update_instantiation_info_file", NULL, "error in creating file %s\n", sp50);
            perror(D_1000C2F0);
            cleanup();
            exit(1);
        }
        skip_old_ii_controls(sp4C);
        func_00431B88(sp48, arg0, TRUE);

        while ((sp44 = getc_locked(sp4C)) != -1) {
            putc_locked(sp44, sp48);
        }

        fclose(sp4C);
        fclose(sp48);

        if (rename(sp50, sp54) < 0) {
            error(1, NULL, NULL, "update_instantiation_info_file", NULL, "error in renaming %s to %s\n", sp50, sp54);
            perror(D_1000C2F0);
            cleanup();
            exit(1);
        }
    }
    free(sp54);
    free(sp50);
}



// function func_00432940 # 61
static int func_00432940(pid_t arg0) {
    int fd; // sp29C
    char pathname[20]; // sp288
    prstatus_t status; // sp68
    int sp64 = 0; // set and not used
    sysset_t syscalls; // sp24

    sprintf(pathname, "/proc/%-d", arg0);
    fd = open(pathname, O_RDWR | O_EXCL);
    if (fd == -1) {
        perror("Opening /proc");
        kill(arg0, 9);
        exit(1);
    }

    premptyset(&syscalls);
    praddset(&syscalls, 2); // size 2?

    if (ioctl(fd, PIOCSENTRY, &syscalls) < 0) {
        perror("PIOCSENTRY");
        kill(arg0, 9);
        exit(1);
    }

    func_00432C94();

    if (ioctl(fd, PIOCWSTOP, &status) < 0) {
        perror("PIOCWSTOP");
        kill(arg0, 9);
        exit(1);
    }

    if (status.pr_why != PR_SYSENTRY) {
        perror("program halted prematurely");
        kill(arg0, 9);
        exit(1);
    }

    if (status.pr_what != 2) { // PR_SIGNALLED ?
        perror("program halted in wrong system call");
        kill(arg0, 9);
        exit(1);
    }

    if (status.pr_errno != 0) {
        perror("unknown problem\n");
        exit(1);
    }

    return fd;
}

static int B_1000EC98[2];

// function func_00432BDC # 62
// test pipe read
static void func_00432BDC(void) {
    char buf;
    int failure;

    close(B_1000EC98[1]);
    failure = (read(B_1000EC98[0], &buf, 1) != 1);
    if (failure) {
        perror("read on pipe failed");
        exit(1);
    }
    close(B_1000EC98[0]);
}

// function func_00432C94 # 63
// test pipe write
static void func_00432C94(void) {
    char buf;

    close(B_1000EC98[0]);
    if (write(B_1000EC98[1], &buf, 1) != 1) {
        perror("write on pipe failed");
        exit(1);
    }
    close(B_1000EC98[1]);
}



extern int getpagesize(void);
static prmap_sgi_t B_1000CAC0[100];
s32 memory_flag = 0;

// function func_00432D3C # 64
static void func_00432D3C(const char* arg0, s32 count) {
    int i;
    s32 identified_segment;
    u32 flags;
    s32 pagesize;
    size_t text_size;
    size_t data_size;
    size_t brk_size;
    size_t stack_size;
    size_t so_text_size;
    size_t so_data_size;
    size_t so_brk_size;
    size_t mmap_size;
    int memflag;

    memflag = (memory_flag > 1);
    mmap_size = 0;
    so_brk_size = 0;
    so_data_size = 0;
    so_text_size = 0;
    stack_size = 0;
    brk_size = 0;
    data_size = 0;
    text_size = 0;
    pagesize = getpagesize();

    for (i = 0; i < count; i++) {
        identified_segment = FALSE;
        flags = B_1000CAC0[i].pr_mflags & 0xFFFF;
        if (flags == (MA_PRIMARY | 0xD)) {
            text_size += B_1000CAC0[i].pr_vsize * pagesize;
            identified_segment = TRUE;
        }

        if (flags == (MA_READ | MA_EXEC | MA_SHARED)) {
            so_text_size += B_1000CAC0[i].pr_vsize * pagesize;
            identified_segment = TRUE;
        }

        if (flags == (MA_READ | MA_WRITE | MA_COW)) {
            if ((uintptr_t)B_1000CAC0[i].pr_vaddr < 0x10000000) {
                so_data_size += B_1000CAC0[i].pr_vsize * pagesize;
                identified_segment = TRUE;
            }
        }
        
        if ((flags == (MA_READ | MA_WRITE)) 
            || (flags == MA_READ) 
            || (flags == (MA_READ | MA_WRITE | MA_SHARED)) 
            || (flags == (MA_READ | MA_SHARED))) {
            if ((uintptr_t)B_1000CAC0[i].pr_vaddr < 0x10000000) {
                mmap_size += B_1000CAC0[i].pr_vsize * pagesize;
                identified_segment = TRUE;
            }
        }
        flags &= ~MA_PRIMARY;
        if (flags == (MA_READ | MA_WRITE | MA_COW)) {
            if ((uintptr_t)B_1000CAC0[i].pr_vaddr >= 0x10000000) {
                data_size += B_1000CAC0[i].pr_vsize * pagesize;
                identified_segment = TRUE;
            }
        }
        if (flags == (MA_READ | MA_WRITE | MA_BREAK | MA_COW)) {
            if ((uintptr_t)B_1000CAC0[i].pr_vaddr >= 0x10000000) {
                brk_size += B_1000CAC0[i].pr_vsize * pagesize;
                identified_segment = TRUE;
            }
        }
        if (flags == (MA_READ | MA_WRITE | MA_STACK)) {
            stack_size += B_1000CAC0[i].pr_vsize * pagesize;
            identified_segment = TRUE;
        }
        if (!identified_segment) {
            fprintf(stderr, "-showm: Unidentified: segment %d\n", i);
        }
        if (memflag || !identified_segment) {
            fprintf(stderr, "pr_vaddr[%d]= %lx\n", i,  B_1000CAC0[i].pr_vaddr);
            fprintf(stderr, "pr_size[%d]= %lx\n", i,   B_1000CAC0[i].pr_size);
            fprintf(stderr, "pr_off[%d]= %lx\n", i,    B_1000CAC0[i].pr_off);
            fprintf(stderr, "pr_mflags[%d]= %lx\n", i, B_1000CAC0[i].pr_mflags);
            fprintf(stderr, "pr_vsize[%d]= %lx\n", i,  B_1000CAC0[i].pr_vsize);
            fprintf(stderr, "pr_psize[%d]= %lx\n", i,  B_1000CAC0[i].pr_psize);
            fprintf(stderr, "pr_wsize[%d]= %lx\n", i,  B_1000CAC0[i].pr_wsize);
            fprintf(stderr, "pr_rsize[%d]= %lx\n", i,  B_1000CAC0[i].pr_rsize);
            fprintf(stderr, "pr_msize[%d]= %lx\n", i,  B_1000CAC0[i].pr_msize);
            fprintf(stderr, "pr_dev[%d]= %lx\n", i,    B_1000CAC0[i].pr_dev);
            fprintf(stderr, "pr_ino[%d]= %lx\n", i,    B_1000CAC0[i].pr_ino);
            fprintf(stderr, "\n");
        }
    }
    
    fprintf(stderr, "%s phase mem: %dT %dD %dB %dS %dt %dd %db %dm= %dK\n", \
        arg0, \
        text_size / 0x400, data_size / 0x400, brk_size / 0x400, stack_size / 0x400, \
        so_text_size / 0x400, so_data_size / 0x400, so_brk_size / 0x400, mmap_size / 0x400, \
        (text_size + data_size + brk_size + stack_size 
        + so_text_size + so_data_size + so_brk_size + mmap_size) / 0x400);

    if (memflag) {
        fprintf(stderr, "text_size= %d Kbytes\n", text_size / 0x400);
        fprintf(stderr, "data_size= %d Kbytes\n", data_size / 0x400);
        fprintf(stderr, "brk_size= %d Kbytes\n", brk_size / 0x400);
        fprintf(stderr, "stack_size= %d Kbytes\n", stack_size / 0x400);
        fprintf(stderr, "so_text_size= %d Kbytes\n", so_text_size / 0x400);
        fprintf(stderr, "so_data_size= %d Kbytes\n", so_data_size / 0x400);
        fprintf(stderr, "so_brk_size= %d Kbytes\n", so_brk_size / 0x400);
        fprintf(stderr, "mmap_size= %d Kbytes\n", mmap_size / 0x400);
        fprintf(stderr, "TOTAL_SIZE= %d Kbytes\n", \
            (
            + text_size 
            + data_size 
            + brk_size 
            + stack_size 
            + so_text_size 
            + so_data_size 
            + so_brk_size 
            + mmap_size
            ) / 0x400);
    }
}

// function func_00433534 # 65
// Prepends "--" to a string by copying.
static char* func_00433534(const char* arg0) {
    char* ret = (char*)malloc(strlen(arg0) + 3);

    ret[0] = '-';
    ret[1] = '-';
    ret[2] = '\0';
    strcat(ret, arg0);

    return ret;
}






/* File boundary, -O2 */

// gethostsex


#pragma GLOBAL_ASM("asm/functions/cc/__Release_ID.s")
