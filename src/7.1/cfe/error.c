#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "mem.h"
#include "linklist.h"

typedef struct ErrorStruct {
    /* 0x00 */ struct LinkedListEntry link;
    /* 0x04 */ int message;
    /* 0x08 */ int level;
    /* 0x0C */ int location;
    /* 0x10 */ char* params[4];
} ErrorStruct; // size = 0x20

typedef struct ErrorFmt {
    short unk_00;
    short unk_02;
} ErrorFmt;

typedef struct FmtArr {
    char* unk_00;
    int unk_04;
} FmtArr;

// TODO move to headers
extern short act_to_imp[];
extern short imp_to_act[];
extern int mode;
extern char debug_arr[];
extern FILE* dbgout;
extern int* short_offset;
extern int* long_offset;
extern int* ansi_offset;
extern unsigned short options[];
extern char* myname;
extern int imm_flag;
int real_file_line(int, char**, int*, int);
int cpp_line_ptr(char*, char**, int);
int __assert(char*, char*, int);

extern int num_warns;
extern int num_errs;
extern ErrorFmt err_fmts[];
extern FmtArr fmts_arr[];

int error(int arg0, int arg1, int arg2, ...);
static int D_1001BA24[7][3] = {
    { 2, 2, 2 },
    { 1, 1, 1 },
    { 3, 3, 3 },
    { 1, 2, 1 },
    { 4, 4, 4 },
    { 4, 1, 1 },
    { 4, 2, 2 },
};
static FILE* D_1001BA78 = (FILE*)0x0FB4EE64; // what is this pointer ?
extern int err_options[]; // 1001BAB0
static char** B_10020F20;
static int B_10020F24;
static FILE* B_10020F28;
static MemCtx* B_10020F2C;
static LinkedList* B_10020F30;
static char B_10020F38[0xC00];
static char B_10021F38[0x1000];
static int B_10022F38[8];
static int B_10022F58[358];
static int B_100234F0[357];

int set_woff(int arg0) {
    if (arg0 < 500 || arg0 >= 857 || act_to_imp[arg0 - 500] == -1) {
        return 0;
    }

    B_100234F0[act_to_imp[arg0 - 500]] = 1;
    return 1;
}

int error_init(char** arg0, FILE* arg1, int arg2) {
    if (arg0 != NULL) {
        B_10020F20 = arg0;
    }
    if (arg1 != 0) {
        D_1001BA78 = arg1;
    }
    mode = arg2;
    B_10020F24 = 0;
    B_10020F28 = NULL;
    B_10020F2C = mem_start();
    B_10020F30 = link_start(B_10020F2C, sizeof(ErrorStruct));
    return 1;
}

void set_error_mode(int arg0) {
    mode = arg0;
}

static void func_0040F730(char* arg0, int arg1, int arg2) {
    int a1, s0;
    int i;

    if (B_10020F28 == NULL) {
        while (*B_10020F20 != NULL && B_10020F28 == NULL) {
            B_10020F28 = fopen(*B_10020F20, "r");
            if (debug_arr[0x65] > 0) {
                fprintf(dbgout, "attempting to open msg file %s %s\n", *B_10020F20, B_10020F28 != NULL ? "success" : "failed");
            }
            B_10020F20++;
        }

        if (B_10020F28 == NULL) {
err:
            B_10020F28 = NULL;
            sprintf(arg0, "ERROR MESSAGE %d", arg1);        
            return;
        }
        if (fgetc(B_10020F28) != '@' || fscanf(B_10020F28, "%d %d %d", &B_10020F24, &B_10020F24, &B_10020F24) != 3) {
            goto err;
        }
        
        short_offset = mem_alloc(B_10020F2C, (unsigned int)(B_10020F24 * 4), 4);
        long_offset = mem_alloc(B_10020F2C, (unsigned int)(B_10020F24 * 4), 4);
        ansi_offset = mem_alloc(B_10020F2C, (unsigned int)(B_10020F24 * 4), 4);

        for (i = 0; i < B_10020F24; i++) {
            if (fscanf(B_10020F28, "%ld %ld %ld", &short_offset[i], &long_offset[i], &ansi_offset[i]) != 3) {
                goto err;
            }
        }
        B_10020F24--;
        if (B_10020F24 != 0x165) {
            goto err;
        }
    }

    if (arg1 < B_10020F24) {
        switch (arg2) {
            case 0:
                a1 = short_offset[arg1];
                s0 = long_offset[arg1] - a1;
                break;
            case 1:
                a1 = long_offset[arg1];
                s0 = ansi_offset[arg1] - a1;
                break;
            case 2:
                a1 = ansi_offset[arg1];
                s0 = short_offset[arg1 + 1] - a1;
                break;
        }

        if (fseek(B_10020F28, a1, 0) == -1 || fread(arg0, 1, s0, B_10020F28) != s0) {
            goto err;
        }

        if (arg2 != 1) {
            arg0[s0 != 0 ? s0 - 1 : s0] = 0;
        } else {
            arg0[s0] = 0;
        }
    }
}

static void func_0040FC14(char* arg0, int arg1) {
    sprintf(arg0, "Warning %d: ", imp_to_act[arg1 & 0xFFFF]);
}

void lint_warning(ErrorStruct* arg0) {
    char* sp3C;
    int sp38 = 0;

    strcpy(B_10020F38, "");

    if (arg0->location != -1 && real_file_line(arg0->location, &sp3C, &sp38, 0) == 1) {
        if (sp3C != 0) {
            error(0x170154, 6, -1, sp3C);
            error(0x170155, 6, -1);
        }
        if (sp38 != 0) {
            sprintf(B_10020F38, "(%d)  ", sp38);
        }
    }

    switch (arg0->level) {
        case 1:
            func_0040FC14(B_10021F38, arg0->message);
            strcat(B_10020F38, B_10021F38);
            break;
        case 3:
            func_0040F730(B_10021F38, 5, 0);
            strcat(B_10020F38, B_10021F38);
            break;
        case 2:
            func_0040F730(B_10021F38, 8, 0);
            strcat(B_10020F38, B_10021F38);
            break;
    }

    func_0040F730(B_10021F38, arg0->message & 0xFFFF, 0);
    sprintf(B_10020F38 + strlen(B_10020F38), B_10021F38, arg0->params[0], arg0->params[1], arg0->params[2], arg0->params[3]);
    strcat(B_10020F38, "\n");
    fprintf(D_1001BA78, "%s", B_10020F38);
}

static void func_0040FECC(ErrorStruct* arg0) {
    char* sp3C;
    int sp38 = 0;
    static char* B_10021B38;

    if ((arg0->message >> 20) != 0 && B_10022F58[arg0->message & 0xFFFF]) {
        return;
    }

    B_10022F58[arg0->message & 0xFFFF] = 1;
    if (options[19] && !(options[3] & 0x20)) {
        lint_warning(arg0);
        return;
    }

    strcpy(B_10020F38, "");
    if (myname != NULL) {
        strcat(B_10020F38, myname);
        strcat(B_10020F38, ": ");
    }

    switch (arg0->level) {
        case 1:
            func_0040FC14(B_10021F38, arg0->message);
            strcat(B_10020F38, B_10021F38);
            break;
        case 3:
            func_0040F730(B_10021F38, 5, 0);
            strcat(B_10020F38, B_10021F38);
            break;
        case 2:
            func_0040F730(B_10021F38, 8, 0);
            strcat(B_10020F38, B_10021F38);
            break;
    }

    if (arg0->location != -1 && real_file_line(arg0->location, &sp3C, &sp38, 0) == 1) {
        if (sp3C != 0) {
            strcat(B_10020F38, sp3C);
            strcat(B_10020F38, ", ");
        }
        if (sp38 != 0) {
            func_0040F730(B_10021F38, 3, 0);
            strcat(B_10020F38, B_10021F38);
            sprintf(B_10020F38 + strlen(B_10020F38), " %d: ", sp38);
        }
    }
    func_0040F730(B_10021F38, arg0->message & 0xFFFF, 0);
    sprintf(B_10020F38 + strlen(B_10020F38), B_10021F38, arg0->params[0], arg0->params[1], arg0->params[2], arg0->params[3]);
    if (((options[13] && (options[5] & 1) || !options[13] && (options[5] & 1))) && (options[5] & 5) == 5) {
        func_0040F730(B_10021F38, arg0->message & 0xFFFF, 2);
        if (strlen(B_10021F38) != 0) {
            sprintf(B_10020F38 + strlen(B_10020F38), " (%s)\n", B_10021F38);
        } else {
            strcat(B_10020F38, "\n");
        }
    } else {
        strcat(B_10020F38, "\n");
    }

    if ((options[3] & 2) && sp3C != NULL && sp38 != 0) {
        cpp_line_ptr(B_10020F38 + strlen(B_10020F38), &B_10021B38, arg0->location);
    }
    if (options[3] & 4) {
        func_0040F730(B_10020F38 + strlen(B_10020F38), arg0->message & 0xFFFF, 1);
    }
    fprintf(D_1001BA78, "%s", B_10020F38);
}

void error_flush(int arg0) {
    while (B_10020F30->used_list != NULL) {
        if (arg0 < ((ErrorStruct*)B_10020F30->used_list)->location && arg0 != -1) {
            break;
        }
        func_0040FECC(((ErrorStruct*)B_10020F30->used_list));
        link_pop(B_10020F30);
    }
}

int error(int message, int level, int location, ...) {
    int real_level;
    ErrorStruct* sp80;
    int sp7C = imm_flag;
    int i;
    int msgid = message & 0xFFFF;
    static int D_1001BA7C;
    va_list args;
    int unused[2];

    if (msgid > 356) {
        real_level = 3;
    } else if (level == 0) {
        real_level = D_1001BA24[err_options[msgid]][mode];
    } else {
        real_level = level;
    }

    if (real_level == 4) {
        return 4;
    }

    if (real_level == 1) {
        if (!(options[3] & 1) || B_100234F0[msgid]) {
            return 4;
        }
        num_warns++;
    }

    if (debug_arr[0x65] > 0) {
        fprintf(dbgout, "err_msg #:%d l:%d loca:%x sec:%d\n", msgid, real_level, location, (message >> 16) & 0xF);
    }

    sp80 = get_link_elem(B_10020F30);
    if (msgid < 0x165) {
        va_start(args, location);
        if (err_fmts[msgid].unk_00 != 0) {
            for (i = 0; i < err_fmts[msgid].unk_00; i++) {
                switch(fmts_arr[err_fmts[msgid].unk_02 + i].unk_04) {
                    case 1:
                        sprintf(B_10020F38, fmts_arr[err_fmts[msgid].unk_02 + i].unk_00, va_arg(args, int));
                        break;
                    case 3:
                        sprintf(B_10020F38, fmts_arr[err_fmts[msgid].unk_02 + i].unk_00, va_arg(args, double));
                        break;
                    case 2:
                        sprintf(B_10020F38, fmts_arr[err_fmts[msgid].unk_02 + i].unk_00, va_arg(args, char*));
                        break;
                }
    
                sp80->params[i] = mem_alloc(B_10020F2C, strlen(B_10020F38) + 1, 1);
                strcpy(sp80->params[i], B_10020F38);
            }
        }
    }

    sp80->message = message;
    sp80->level = real_level;
    sp80->location = location;

    if (real_level == 3 || real_level == 6) {
        sp7C = 1;
    }
    if (location == -1) {
        sp7C = 1;
    }

    if (sp7C) {
        func_0040FECC(sp80);
    } else {
        LinkedListEntry* a0 = B_10020F30;
        while (a0->next != NULL) {
            if (sp80->location < ((ErrorStruct*)(a0->next))->location) {
                sp80->link.next = a0->next;
                break;
            }
            a0 = a0->next;
        }
        a0->next = sp80;
    }

    if (real_level == 3) {
        fatal();
    }

    if (real_level == 2) {
        int v1 = (message >> 16) & 0xF;
        num_errs++;

        if (v1 != 0 && v1 < 8) {
            B_10022F38[v1 - 1]++;
        } else {
            ((void)((!v1)||__assert("!i", "error.c", 471)));
        }
    }

    if (num_errs >= 30 && !D_1001BA7C) {
        D_1001BA7C = 1;
        error_flush(-1);
        D_1001BA7C = 0;
        error(0x40007, 3, -1);
    }

    return real_level;
}