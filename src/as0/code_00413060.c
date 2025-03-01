/*
 * @file: code_00413060.c
 *
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// array declaration (Only declared in this file)
char* opt_strings[0x6D] = {
    "-EB",
    "-EL",
    "-G",
    "-K",
    "-M",
    "-NR",
    "-O",
    "-O0",
    "-O1",
    "-O2",
    "-O3",
    "-O4",
    "-Olimit",
    "-R",
    "-RD",
    "-T",
    "-e",
    "-fli",
    "-f",
    "-f0",
    "-f1",
    "-f2",
    "-f3",
    "-f4",
    "-g",
    "-g0",
    "-g1",
    "-g2",
    "-g3",
    "-l",
    "-o",
    "-p",
    "-p0",
    "-p1",
    "-p2",
    "-p3",
    "-r",
    "-t",
    "-v",
    "-w",
    "-w1",
    "-w2",
    "-w3",
    "-no_const_opts",
    "-no_lui_opts",
    "-no_div_rem_opts",
    "-no_at_compression",
    "-no_branch_target",
    "-mips1",
    "-mips2",
    "-mips3",
    "-mips4",
    "-nopool",
    "-align8",
    "-align16",
    "-align32",
    "-align64",
    "-align_common",
    "-gp_warn",
    "-non_pic",
    "-r3000",
    "-r4000",
    "-r6000",
    "-r6000LHU",
    "-r6000LWL",
    "-trapuv",
    "-nopeep",
    "-peepdbg",
    "-noswpipe",
    "-swpdbg",
    "-nosymregs",
    "-noxbb",
    "-aggr_xbb",
    "-xbbdbg",
    "-newhilo",
    "-domtag",
    "-fpstall_nop",
    "-noglobal",
    "-nobopt",
    "-dwalign",
    "-excpt",
    "-diag",
    "-mednat",
    "-dwopcode",
    "-64bit",
    "-fp32reg",
    "-extsyms",
    "-pic0",
    "-pic1",
    "-pic2",
    "-big_got",
    "-coff",
    "-elf",
    "-mscoff",
    "-mscoff1",
    "-multi_issue",
    "-nonzero_scnbase",
    "-new_mdebug",
    "-abi",
    "-tfprev10",
    "-force_branch_fixup",
    "-r4200",
    "-r4600",
    "-tfp",
    "-r4300_mul",
    "",
};

#define MIN(a, b) ((a > b) ? b : a)

// Extern declarations
extern int CurrentLine;
extern int debugflag;
extern int severity;
extern int verbose;
extern int CurrentFile;
extern int nowarnflag;
extern int linelength;
extern int warnexitflag;
extern int printedline;
extern char line[0x420];

extern void* xmalloc(unsigned int);
extern void* xrealloc(void*, unsigned int);
extern char* st_str_idn(int idn);

// File declarations (code_00413060.c)
static int D_10001094 = 0;
static char* as0_msg[5] = { "Internal", "Error", "Warning", "Info", "" };
static int D_10001090 = 0;


static void func_00413060(char* arg0, int arg1);
static void func_00413224(char* arg0);
void call_name_and_line(int arg0);
void call_perror(int arg0, char* arg1);
void new_error(void);
void posterror(char* error, char* arg1, int arg2);
void postcerror(char* error, int arg1);
void assertion_failed(char* assert_name, char* file, int file_line);
int which_opt(char* name);
void* grow_array(size_t* capacity_count, size_t new_count, size_t width, void* ptr, int clear_mem);

static void func_00413060(char* arg0, int arg1) {
    if (verbose) {
        if (arg1 != 3) {
            if (D_10001094 != 0) {
                fprintf(stderr, "\n");
                D_10001094 = 0;
            }
        } else if (D_10001094 != 0) {
            return;
        }
    }
    severity = MIN(arg1, severity);

    if (arg1 != 3) {
        fprintf(stderr, "%s", "as0: ");
    }

    if (arg1 == 1) {
        debugflag = 0;
    } else if (arg1 == 3) {
        D_10001094 = 1;
        return;
    }

    fprintf(stderr, "%s: ", as0_msg[arg1]);
    if (arg0[0] != '\0') {
        fprintf(stderr, "%s", arg0);
    }
    fprintf(stderr, ", line %1d:", CurrentLine);
}

static void func_00413224(char* arg0) {
    if (D_10001090 != 0) {
        *arg0 = 0;
        return;
    }
    D_10001090 = 1;
    if (CurrentFile != -1) {
        strcpy(arg0, st_str_idn(CurrentFile));
    } else {
        *arg0 = 0;
    }
    D_10001090 = 0;
}

void call_name_and_line(int arg0) {
    char sp20[0x400];

    func_00413224(sp20);
    func_00413060(sp20, arg0);
}

void call_perror(int arg0, char* arg1) {
    call_name_and_line(arg0);
    perror(arg1);
    fflush(stderr);
}

void new_error(void) {
    call_perror(1, 0);
    fflush(stderr);
}

void posterror(char* error, char* arg1, int arg2) {
    if (warnexitflag != 0) {
        severity = MIN(arg2, severity);
    }
    if ((arg2 < 2) || !nowarnflag) {
        call_name_and_line(arg2);
        fprintf(stderr, "%s", error);
        if (arg1 != NULL) {
            fprintf(stderr, ": %s\n", arg1);
        } else {
            fprintf(stderr, "\n");
        }
        if ((printedline == 0) && (linelength > 0)) {
            fprintf(stderr, "     %s\n", line);
            printedline = 1;
        }
    }
}

void postcerror(char* error, int arg1) {
    call_name_and_line(arg1);
    if (error) {
        fprintf(stderr, "%s\n", error);
    }
}

void assertion_failed(char* assert_name, char* file, int file_line) {
    call_name_and_line(0);
    fprintf(stderr, "%s, line %1d:\n", file, file_line);
    if (assert_name != NULL) {
        fprintf(stderr, "    assertion (%s) failed\n", assert_name);
    }
    fflush(stderr);
    exit(1);
}

int which_opt(char* name) {
    int i;
    char** opt = opt_strings;

    for (i = 0; i <= 105; i++) {
        if (strcmp(name, *opt) == 0) {
            return i;
        }
        opt++;
    }
    return 105;
}

void* grow_array(size_t* capacity_count, size_t new_count, size_t width, void* ptr, int clear_mem) {
    char* new_ptr;
    int old_size;
    int new_size;

    if (*capacity_count == 0) {
        if (new_count >= 0x400) {
            *capacity_count = new_count + 1;
        } else {
            *capacity_count = 0x400;
        }

        new_size = *capacity_count * width;
        if ((new_ptr = xmalloc(new_size)) == NULL) {
            new_error();
        } else if (clear_mem) {
            new_ptr = memset(new_ptr, 0, new_size);
        }
    } else {
        old_size = *capacity_count * width;
        *capacity_count *= 2;
        if (new_count >= *capacity_count) {
            *capacity_count = new_count + 1;
        }

        new_size = *capacity_count * width;
        if ((new_ptr = xrealloc(ptr, new_size)) == NULL) {
            new_error();
        } else if (clear_mem) {
            memset(new_ptr + old_size, 0, new_size - old_size);
        }
    }
    return new_ptr;
}
