/* Handwritten */
#pragma GLOBAL_ASM("asm/functions/cc/__start.s")
#pragma GLOBAL_ASM("asm/functions/cc/_mcount.s")

#include "cc.h"
//#include "inttypes.h"
#include "sex.h"
#include "sys/times.h"

#include "varargs.h"

/* File, -O1 */
static void func_00432C94(void);
void relocate_passes(const char *arg0, const char *arg1, const char *arg2);
char* mkstr();


// data
int fiveflag = 0;
int runerror = 0;
char *runlib = "/";
char *runlib_base = "/";
int irix4 = 0;
int targetsex = BIGENDIAN;

// LD
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004000.s")

// suffixes
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004004.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004008.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_1000400C.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004010.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004014.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004018.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_1000401C.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004020.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004024.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004028.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_1000402C.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004030.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004034.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_10004038.s")

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

#pragma GLOBAL_ASM("asm/functions/cc/STR_100040C4.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_100040C8.s")
#pragma GLOBAL_ASM("asm/functions/cc/STR_100040CC.s")

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

// function relocate_passes # 8


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


#pragma GLOBAL_ASM("asm/functions/cc/compose_G0_libs.s")

#pragma GLOBAL_ASM("asm/functions/cc/compose_reg_libs.s")

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

// function mklist # 13
// function addstr # 14
void addstr(char**, const char*);

// function addspacedstr # 15
// function newstr # 16
// function save_place # 17
// function set_place # 18
// function addlist # 19
// function adduldlist # 20
// function nodup # 21
// function getsuf # 22
// function mksuf # 23
// function savestr # 24
// function mktempstr # 25
// function run # 26
// function edit_src # 27
// function get_lino # 28

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

struct _struct_prod_name_0xC prod_name[0x14] = {
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

const char* func_00430414(char* arg0, int arg1) {
    int i;
    int sp28;
    char* sp24;
    char* sp20;

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
    return 0;
}

// function force_use_cfront # 42
static s32 D_1000BF7C;
static s32 D_1000BF90;
extern s32 LD;
extern char* comp_host_root;
extern s32 exception_handling;
extern char* execlist; // ?

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
char* progname;

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
// function add_static_opt # 47
// function record_static_fileset # 48

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
// function func_00431B38 # 54
// function func_00431B88 # 55
// function func_00431D00 # 56
// function func_00431DD8 # 57

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
        func_00431B88(sp48, arg0, 1);

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



int func_00432940(pid_t arg0) {
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

// test pipe read
void func_00432BDC(void) {
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

void func_00432D3C(const char* arg0, s32 count) {
    s32 i;
    s32 identified_segment;
    u32 flags;
    s32 pagesize;
    u32 text_size;
    u32 data_size;
    u32 brk_size;
    u32 stack_size;
    u32 so_text_size;
    u32 so_data_size;
    u32 so_brk_size;
    u32 mmap_size;
    s32 memflag;

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

// Prepends "--" to a string by copying.
char* func_00433534(const char* arg0) {
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
