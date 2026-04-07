#ifndef UNKNOWN_H
#define UNKNOWN_H

// contains all symbols which will be moved to their own .c and .h files later

#include <stdio.h>
#include "mem.h"
#include "linklist.h"
#include "tree.h"

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

typedef struct ParseLevel {
    LinkedListEntry link;
    int type_ident_expected;
    int normal_ident;
    int in_comp_expr;
    int in_struct_def;
    MemCtx* saved_ctx;
} ParseLevel;

typedef struct ErrorFmt {
    short unk_00;
    short unk_02;
} ErrorFmt;

typedef struct FmtArr {
    char* unk_00;
    int unk_04;
} FmtArr;

typedef struct Scope {
    /* 0x00 */ TreeNode* unk_00;
    /* 0x04 */ unsigned int level;
    /* 0x08 */ struct Scope* parent;
    /* 0x0C */ struct Scope* child;
    /* 0x10 */ int unk_10;
    /* 0x14 */ int unk_14;
    /* 0x18 */ TreeNode* unk_18;
} Scope; // size = 0x1C

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
extern TreeNode* char_type;
extern TreeNode* uchar_type;
extern TreeNode* float_type;
extern TreeNode* double_type;
extern TreeNode* ulonglong_type;
extern TreeNode* longlong_type;
extern TreeNode* array_type;
extern TreeNode* voidstar_type;
extern TreeNode* ulong_type;
extern TreeNode* long_type;
extern TreeNode* uint_type;
extern TreeNode* int_type;
extern TreeNode* short_type;
extern TreeNode* ushort_type;
extern TreeNode* signed_type;
extern TreeNode* label_type;
extern TreeNode* void_type;
extern TreeNode* any_type;
extern TreeNode* int32_type;
extern TreeNode* uint32_type;
extern TreeNode* int64_type;
extern TreeNode* uint64_type;
extern TreeNode* unsigned_type;
extern TreeNode* longdouble_type;
extern TreeNode* one_constant;
extern TreeNode* zero_constant;
extern TreeNode* ellipsis;
extern unsigned int last_stdtree_id;
extern unsigned short options[];
extern unsigned long long __ULONGLONG_MAX;
extern long long __LONGLONG_MAX;
extern long long __LONGLONG_MIN;
extern ParseLevel* cur_lvl;
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
extern char* sc_names[];
extern MemCtx* tree_handle;
extern MemCtx* temp_handle;
extern Symbol* builtins[];
extern Symbol* anonymous;
extern Scope* function_scope;
extern Scope* current_scope;
extern Scope* file_scope;
extern void* current_function;

int real_file_line(int, char**, int*, int);
void __assert(char*, char*, int);
void register_file(char*, int);
float str_to_float(char* arg0, int arg1, int arg2);
double str_to_double(char* arg0, int arg1, int arg2);
Symbol* string_to_symbol(char*, size_t);
unsigned int sizeof_type(int);
char* get_type_name(int);
int loc_to_cppline(int);
int lint(int argc, char** argv);
int cfe(int argc, char** argv);
int cpp(int argc, char** argv);
void hash_table_statistics(void);
void Set_Small_Data_Upper_Limit(int);
void set_def_member_pack(int);
void cpp_symentry_setMaxMacroRecursionDepth(int);
void* get_runtime_id(char*, TreeNode*, int);
void declarator(TreeNode* id, TreeNode* context, int sclass, int oclass, int attr, TreeNode* type);
void mips_st(TreeNode*);
void mips_st_extundefined(TreeNode*);
void lint_setref(TreeNode*, int, int);
void lint_checks(TreeNode*);
int type_compatible(TreeNode* arg0, TreeNode* arg1, int arg2);

#endif
