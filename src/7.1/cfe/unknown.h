#ifndef UNKNOWN_H
#define UNKNOWN_H

// contains all symbols which will be moved to their own .c and .h files later

#include <stdio.h>
#include "mem.h"
#include "linklist.h"

#define GET_SYM_CAT(x) (x != 0 ? (x == -1 ? "typedef" : "keyword") : "regular")

typedef struct Location {
    int offset;
    int file;
    int line;
} Location;

typedef struct CppLineArr {
    int size;
    Location* loc;
} CppLineArr;

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

typedef struct ErrorFmt {
    short unk_00;
    short unk_02;
} ErrorFmt;

typedef struct FmtArr {
    char* unk_00;
    int unk_04;
} FmtArr;

typedef struct ParseSymbol {
    LinkedListEntry link;
    int unk_04;
    int unk_08;
} ParseSymbol;

typedef struct Symbol {
    int unk_00;
    ParseSymbol* unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int namelen;
    char name[1];
} Symbol;

extern short act_to_imp[];
extern short imp_to_act[];
extern int mode;
extern char debug_arr[];
extern FILE* dbgout;
extern int* short_offset;
extern int* long_offset;
extern int* ansi_offset;
extern char* myname;
extern int imm_flag;
extern int num_warns;
extern int num_errs;
extern ErrorFmt err_fmts[];
extern FmtArr fmts_arr[];
extern char* infile;
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
extern FILE* dbgout;
extern int err_options[];
extern MemCtx* general_handle;
extern int xpg_flag;
extern char* command_line_file_name;
extern int yydebug;
extern char* st_filename;
extern int bit_size[];
extern int minimize_indirection_entries;

int real_file_line(int, char**, int*, int);
int __assert(char*, char*, int);
void register_file(char*, int);
float str_to_float(char* arg0, int arg1, int arg2);
double str_to_double(char* arg0, int arg1, int arg2);
void* make(int, ...);
Symbol* string_to_symbol(char*, size_t);
UnkOmega* make_uiconstant(int, UnkOmega*, unsigned long long);
UnkOmega* make_iconstant(int, UnkOmega*, long long);
unsigned int sizeof_type(int);
char* get_type_name(int);
int loc_to_cppline(int);
void catchall(void);
int lint(int argc, char** argv);
int cfe(int argc, char** argv);
int cpp(int argc, char** argv);
void hash_table_statistics(void);
void Set_Small_Data_Upper_Limit(int);
void set_def_member_pack(int);
void cpp_symentry_setMaxMacroRecursionDepth(int);

#endif
