/*
 * @file: main.c (Guess)
 *
 */
#include "stdio.h"
#include "stdlib.h"
#include "common.h"
#include "cmplrs/binasm.h" //Original binasm header
#include "binasm_rec.h"    //temp

// External data
extern struct _struct_asm_info_0x8 asm_info[0x1AF];
extern char *sframereg;
extern char *sframesize;
extern char *sitype[0x3F];
extern char *sregisters[0x49];

//.bss
/* 027EA0 10008EA0 */ int binasm_count;
/* 027EA4 10008EA4 */ int nowarnflag;
/* 027EA8 10008EA8 */ int warnexitflag;
/* 027EAC 10008EAC */ char isa;
/* 027EB0 10008EB0 */ int CurrentSegment;
/* 027EB4 10008EB4 */ int verbose;
/* 027EB8 10008EB8 */ int debugflag;
/* 027EBC 10008EBC */ int atflag;
/* 027EC0 10008EC0 */ int isStruct; // BOOL
/* 027EC4 10008EC4 */ int StructOrg;
/* 027EC8 10008EC8 */ sym *LastLabel;
/* 027ECC 10008ECC */ int in_repeat_block;
/* 027ED0 10008ED0 */ unsigned int rep_count;
/* 027ED4 10008ED4 */ size_t rep_size;
/* 027ED8 10008ED8 */ struct {
    binasm_r *unk0;
    size_t unk4;
} rep_buffer;
/* 027EE0 10008EE0 */ int invent_locs;
/* 027EE4 10008EE4 */ int gp_warn;
/* 027EE8 10008EE8 */ int linelength;
/* 027EEC 10008EEC */ int nextinline;
/* 027EF0 10008EF0 */ char *line[0x36C];
/* 02825C 1000925C */ char B_1000925C[0xB4]; // P a d
/* 028310 10009310 */ int CurrentFile;
/* 028310 10009310 */ int CurrentLine;
/* 028318 10009318 */ struct {
    /* 0x000 */ char tokench; /* inferred */
    /* 0x001 */ char tstring[0x400];
    /* 0x404 */ int length;
} save;
/* 028720 10009720 */ char Tokench;
/* 028728 10009728 */ char Tstring[0x400];
/* 028B28 10009B28 */ int Tstringlength;
/* 028B30 10009B30 */ char *token_tmp[0x100];
/* 028F30 10009F30 */ int printedline;
/* 028F34 10009F34 */ int severity;
/* 028F38 10009F38 */ sym *reg_ptr[0x20];
/* 028FB8 10009FB8 */ sym *hashtable[0x80];
/* 0291B8 1000A1B8 */ int LastSym; // UNUSED
/* 0291C0 1000A1C0 */ sym *ophashtable[0x80];
/* 0293C0 1000A3C0 */ int local_label[0x100];
/* 0297C0 1000A7C0 */ binasm_r binasm_rec;
/* 0297D0 1000A7D0 */ FILE *binasmfyle;
/* 0297D4 1000A7D4 */ FILE *in_file;
/* 0297D8 1000A7D8 */ int mednat;
/* 0297DC 1000A7DC */ int diag_flag;
/* 0297E0 1000A7E0 */ int shftaddr;
/* 0297E4 1000A7E4 */ FILE *extsyms_file;
/* 0297E8 1000A7E8 */ int list_extsyms; // Boolean
/* 0297EC 1000A7EC */ static char *assembler_file;
/* 0297F0 1000A7F0 */ static char *B_1000A7F0; // Output binasm file path
/* 0297F4 1000A7F4 */ static char *B_1000A7F4;
/* 0297F8 1000A7F8 */ static char *B_1000A7F8;

// External function call
extern void posterror(char *, char *, int);
extern void call_perror(int arg0, const char *arg1);
extern int which_opt(char *);
extern sym *alloc_new_sym(void);
extern int hash(char *);
extern void make_file(const char *arg0);
extern void put_binasmfyle(void);
extern void sym_init(int arg0);
extern void readinline(void);
extern void sym_finish(char *arg0, char *arg1);
extern void Parsestmt(void);
extern void do_dot_end(int arg0);

// Internal function call
static void func_00403F10(void);
static void func_00404008(void);
static sym *func_00404108(registers reg, char *name, registers next_reg);
static void func_004041A8(char *arg0, int arg1);
static void func_00404234(int argc, char **argv);

// func_00403F10
static void func_00403F10(void) {
    struct _struct_asm_info *var_s2;
    int operand_hash;
    int index;
    char *name;
    sym *cur_symbol;

    for (index = 0, var_s2 = (struct _struct_asm_info *) &asm_info; index < 0x1AE; index++, var_s2++) {
        name = var_s2->name;
        if (name[0] != '\0') {
            operand_hash = hash(name);
            cur_symbol = alloc_new_sym();

            cur_symbol->next = ophashtable[operand_hash];
            cur_symbol->name = name;
            cur_symbol->unkC = 0;
            cur_symbol->unk8 = 0;
            cur_symbol->unk10 = 1;
            cur_symbol->reg = index;

            cur_symbol->unk18 = var_s2->unk4_FE;

            ophashtable[operand_hash] = cur_symbol;
        }
    }
}

// func_00404008:
static void func_00404008(void) {
    int directives_hash;
    int index;
    char *asm_directives;
    struct sym *cur_symbol;

    for (index = 0; index < 0x3F; index++) {
        if (*sitype[index] == 0x2E) {
            asm_directives = sitype[index];
            directives_hash = hash(asm_directives); // create a hash for each asm directive
            cur_symbol = alloc_new_sym();

            cur_symbol->next = ophashtable[directives_hash];
            cur_symbol->name = asm_directives;
            cur_symbol->unkC = 0;
            cur_symbol->unk8 = -1;
            cur_symbol->unk10 = 2;
            cur_symbol->reg = index;

            ophashtable[directives_hash] = cur_symbol;
        }
    }
}

static sym *func_00404108(registers reg, char *name, registers next_reg) {
    sym *cur_symbol;
    int reg_hash;

    reg_hash = hash(name);
    cur_symbol = alloc_new_sym();

    cur_symbol->next = hashtable[reg_hash];
    cur_symbol->name = name;
    cur_symbol->unkC = 0;
    cur_symbol->unk10 = 0;
    cur_symbol->unk8 = next_reg;
    cur_symbol->reg = reg;

    hashtable[reg_hash] = cur_symbol;
    return cur_symbol;
}

static void func_004041A8(char *arg0, int arg1) {
    int unused;
    int sp20;
    sym *cur_symbol;

    sp20 = hash(arg0);
    cur_symbol = alloc_new_sym();

    cur_symbol->next = hashtable[sp20];
    cur_symbol->name = arg0;
    cur_symbol->unkC = 0;
    cur_symbol->unk10 = 4;
    cur_symbol->unk8 = arg1;
    hashtable[sp20] = cur_symbol;
}

// func_00404234:
static void func_00404234(int argc, char **argv) {
    int j;
    int i;
    int k;
    int var_s3 = 1;

    assembler_file = NULL;
    B_1000A7F0 = "binasm";
    B_1000A7F4 = NULL;
    B_1000A7F8 = NULL;
    list_extsyms = FALSE;
    CurrentSegment = 1;
    CurrentLine = 0;
    CurrentFile = EOF;
    linelength = 0;
    severity = 4;
    verbose = 0;
    atflag = 1;
    debugflag = 0;
    isStruct = 0;
    LastLabel = NULL;
    in_repeat_block = 0;
    invent_locs = 1;
    gp_warn = 0;
    mednat = 0;

    for (i = 1; i < argc; i++) {
        char *cur_arg = argv[i];

        if (*cur_arg == '-') {
            switch (which_opt(cur_arg)) {
                case OPTION_g0:
                    debugflag = 0;
                    break;

                case OPTION_g1:
                    debugflag = 1;
                    break;

                case OPTION_g:
                case OPTION_g2:
                    debugflag = 2;
                    break;

                case OPTION_g3:
                    debugflag = 3;
                    break;

                case OPTION_p0:
                    var_s3 = 0;
                    break;

                case OPTION_p1:
                    var_s3 = 1;
                    break;

                case OPTION_p:
                case OPTION_p2:
                    var_s3 = 2;
                    break;

                case OPTION_p3:
                    var_s3 = 3;
                    break;

                case OPTION_w:
                case OPTION_w1:
                    nowarnflag = 1;
                    warnexitflag = 0;
                    break;

                case OPTION_w2:
                    nowarnflag = 0;
                    warnexitflag = 1;
                    break;

                case OPTION_w3:
                    nowarnflag = 1;
                    warnexitflag = 1;
                    break;

                case OPTION_v:
                    verbose = 1;
                    fprintf(stderr, "as0: ");
                    fflush(stderr);
                    break;

                case OPTION_t:
                    i++;
                    B_1000A7F4 = argv[i];
                    break;

                case OPTION_extsyms:
                    i++;
                    B_1000A7F8 = argv[i];
                    list_extsyms = TRUE;
                    break;

                // Ignore these options. They take an argument so increment again.
                case OPTION_G:
                case OPTION_Olimit:
                case OPTION_swpdbg:
                case OPTION_xbbdbg:
                case OPTION_multi_issue:
                    i++;
                    break;

                case OPTION_o:
                    i++;
                    B_1000A7F0 = argv[i];
                    break;

                case OPTION_gp_warn:
                    gp_warn = 1;
                    break;

                case OPTION_MAX:
                    posterror("Unknown option", cur_arg, 2);
                    break;

                case OPTION_mips1:
                    isa = ISA_MIPS1;
                    break;

                case OPTION_mips2:
                    isa = ISA_MIPS2;
                    break;

                case OPTION_mips3:
                    isa = ISA_MIPS3;
                    break;

                case OPTION_mips4:
                    isa = ISA_MIPS4;
                    break;

                case OPTION_mednat:
                    mednat = 1;
                    break;

                case OPTION_diag:
                    diag_flag = 1;
                    break;
                default:
                    break;
            }
        } else if (assembler_file == NULL) {
            assembler_file = argv[i];
        } else {
            posterror("Extra filename on command line", argv[i], 2);
        }
    }
    if (isa == ISA_UNSPECIFIED) {
        isa = ISA_MIPS1;
    }
    if (var_s3 >= 2) {
        debugflag = 2;
    }

    if ((binasmfyle = fopen(B_1000A7F0, "w")) == NULL) {
        call_perror(1, B_1000A7F0);
        exit(1);
    }
    binasm_count = 1;
    if (list_extsyms) {
        if ((B_1000A7F8 == NULL) || ((extsyms_file = fopen(B_1000A7F8, "w")) == NULL)) {
            call_perror(1, B_1000A7F8);
            exit(1);
        }
    }
    binasm_rec.unk5_003F =
        0x2A;            //!< Is this something like a universal signature for every binasm file?
    binasm_rec.unk0 = 0; // symno
    binasm_rec.unk8 = 3;
    binasm_rec.unkC = 0x13;
    put_binasmfyle();
    sym_init(debugflag);

    if (assembler_file != NULL) {
        if ((in_file = fopen(assembler_file, "r")) == NULL) {
            call_perror(1, assembler_file);
            exit(1);
        }
    } else {
        in_file = stdin;
    }
    if (fgetc(in_file) != '#') {
        make_file(assembler_file);
    }
    fseek(in_file, 0, 0);

    for (j = 0; j < 0x20; j++) {
        reg_ptr[j] = func_00404108(j, sregisters[j], j);
    }
    for (j = 0x20; j < 0x40; j++) {
        func_00404108(j, sregisters[j], j - 0x20);
    }
    for (j = 0x40; j < 0x48; j++) {
        func_00404108(j, sregisters[j], j - 0x40);
    }

    func_00404108(xr1, "$at", xr1);
    func_00404108(xr26, "$kt0", xr27);
    func_00404108(xr27, "$kt1", xr28);
    func_00404108(xr28, "$gp", xr29);
    func_00404108(xr29, "$sp", xr30);
    func_00404108(xr30, "$fp", xr31);
    func_00404108(xr29, sframereg, xr29);
    func_004041A8(sframesize, 0);
    func_00404008();
    func_00403F10();

    for (k = 0; k < 0x100; k++) {
        local_label[k] = 0;
    }
}

// main
int main(int argc, char **arg1) {
    func_00404234(argc, arg1);
    while (!feof(in_file)) {
        readinline();
        Parsestmt();
    }
    if (verbose != 0) {
        fprintf(stderr, "\n");
    }
    if ((severity < 2) || ((warnexitflag != 0) && (severity < 3))) {
        exit(1);
    }
    do_dot_end(1);
    sym_finish(B_1000A7F0, B_1000A7F4);
    return 0;
}
