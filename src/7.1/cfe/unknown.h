#ifndef UNKNOWN_H
#define UNKNOWN_H

// contains all symbols which will be moved to their own .c and .h files later

#include <stdio.h>
#include "mem.h"
#include "linklist.h"

#define GET_SYM_CAT(x) (x != 0 ? (x == -1 ? "typedef" : "keyword") : "regular")

#define IS_ANSI ((options[OPTION_CPLUSPLUS] && (options[OPTION_ANSI_MODE] & 1) || !options[OPTION_CPLUSPLUS] && (options[OPTION_ANSI_MODE] & 1)))
#define IS_STRICT_ANSI (IS_ANSI && (options[OPTION_ANSI_MODE] & 5) == 5)
#define IS_RELAXED_ANSI (IS_ANSI && (options[OPTION_ANSI_MODE] & 3) == 3)

enum Option {
    OPTION_O_LEVEL = 0,
    OPTION_G_LEVEL = 1,
    OPTION_ENDIANNESS = 2,
    OPTION_VERBOSITY = 3,
    OPTION_FLOAT = 4,
    OPTION_ANSI_MODE = 5,
    OPTION_SIGNED = 6,
    OPTION_DOLLAR = 7,
    OPTION_T_LEVEL = 8,
    OPTION_FRAMEPOINTER = 9,
    OPTION_TRAPUV = 10,
    OPTION_11 = 11, // unused ?
    OPTION_MIPS_GEN = 12,
    OPTION_CPLUSPLUS = 13,
    OPTION_14 = 14,
    OPTION_CHECKSTACK = 15,
    OPTION_T = 16,
    OPTION_CHECK_BOUNDS = 17,
    OPTION_SAVEARGS = 18,
    OPTION_LINT_FLAGS = 19,
    OPTION_WIMPLICIT = 20,
    OPTION_MSFT = 21,
    OPTION_PROTOTYPES = 22,
    OPTION_FULLWARN = 23,
    OPTION_XCOMMON = 24,
    OPTION_VOLATILE = 25,
    OPTION_CPLUSCOMM = 26,
    OPTION_READONLY_CONST = 27,
    OPTION_LITERAL_CONST = 28,
};

enum VerbosityFlags {
    VERBOSE_FLAG_1 = 0x1,
    VERBOSE_FLAG_2 = 0x2,
    VERBOSE_FLAG_4 = 0x4,
    VERBOSE_FLAG_8 = 0x8,
    VERBOSE_FLAG_10 = 0x10,
    VERBOSE_FLAG_20 = 0x20,
};

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
void init_options(void);
int lint(int argc, char** argv);
int cfe(int argc, char** argv);
int cpp(int argc, char** argv);
void hash_table_statistics(void);
void Set_Small_Data_Upper_Limit(int);
void set_def_member_pack(int);
void cpp_symentry_setMaxMacroRecursionDepth(int);

#endif
