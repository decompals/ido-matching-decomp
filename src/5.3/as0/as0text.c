/*
* @file: as0text.c
* @brief: Contains the main print functions
*/
#include <stdio.h>
#include <stdbool.h>
#include "types.h"

s32 CurrentFile;
s32 CurrentLine;
s32 D_10001094; //.data
s32 D_10001098[0x100]; //.data?
static s32 D_10001090 = 0; //.data
s32 debugflag;
s32 severity;
s32 verbose;
char line[4];
s32 linelength;
s32 nowarnflag;
s32 printedline;
s32 severity;
s32 warnexitflag;
s8* opt_strings;

static void func_00413060(u8* arg0, s32 arg1) {
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
    severity = MIN(severity, arg1);

    if (arg1 != 3) {
        fprintf(stderr, "%s", "as0: ", arg1);
    }

    if (arg1 == 1) {
        debugflag = 0;
    } else if (arg1 == 3) {
        D_10001094 = 1;
        return;
    }

    fprintf(stderr, "%s: ", D_10001098[arg1], arg1);
    if (*arg0 != 0) {
        fprintf(stderr, "%s", arg0);
    }
    fprintf(stderr, ", line %1d:", CurrentLine);
}

static void func_00413224(u8* arg0) {
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

void call_name_and_line(s32 arg0) {
    s32 filler;
    u8 sp20[1020];


    func_00413224(sp20);
    func_00413060(sp20, arg0);
}

void call_perror(s32 arg0, u8* arg1) {
    call_name_and_line(arg0);
    perror(arg1);
    fflush(stderr);
}

void new_error(void) {
    call_perror(1, 0);
    fflush(stderr);
}

void posterror(char* arg0, char *arg1, s32 arg2) {
    if (warnexitflag != 0) {
        severity = (severity < arg2) ? severity : arg2;
    }
    if ((arg2 < 2) || !nowarnflag) {
        call_name_and_line(arg2);
        fprintf(stderr, "%s", arg0);
        if (arg1 != 0) {
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

void postcerror(char* error, char* arg1) {
    call_name_and_line(arg1);
    if (error) {
        fprintf(stderr, "%s\n", error);
    }
}

void assertion_failed(char *assert_name, char *file, int line) {
    call_name_and_line(0);
    fprintf(stderr, "%s, line %1d:\n", file, line);
    if (assert_name != 0) {
        fprintf(stderr, "    assertion (%s) failed\n", assert_name);
    }
    fflush(stderr);
    exit(1);
}

int which_opt(char* name) {
    int i;
    char** opt = opt_strings;

    for (i = 0; i <= 105; i++) {
        if (strcmp(arg0, *var_s1) == 0) {
            return i;
        }
        var_s1++;
    }
    return 105;
}

u8* grow_array(size_t* capacity_count, size_t new_count, size_t width, void* ptr, s32 clear_mem) {
    u8* new_ptr;
    s32 old_size;
    s32 new_size;

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
