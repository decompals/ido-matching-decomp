/**
 * @file cc.c
 * @brief Compiler driver for IDO 5.3 (or 3.19 as it styles itself internally)
 *
 * This file incorporates code from Open64's Osprey driver, version 0.13.0, licensed under GPL Version 2
 */
#include "sys/types.h"
#include "ctype.h"
#include "stdio.h"
#include "errno.h"
#include "string.h"
#include "malloc.h"
#include "sys/file.h"
#include "sys/procfs.h"
#include "sys/stat.h"
#include "sys/times.h"
#include "fcntl.h"
#include "signal.h"
#include "sex.h"
#include "termios.h"
#include "wait.h"
#include "varargs.h"
#include "unistd.h"

/**
 * _ftext
 *
 * Not clear what this is, but it's a separate section if not a separate file
 *
 * Address: 0x00405550
 * VROM: 0x005550
 * Size: 0x10
 */
// int _ftext();
// #pragma GLOBAL_ASM("asm/5.3/functions/cc/_ftext.s")

/**
 * func_00405560
 *
 * This should be mips.STUBS
 *
 * Address: 0x00405560
 * VROM: 0x005560
 * Size: 0x400
 */
// static int func_00405560();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/func_00405560.s")

/**
 * __start
 * Address: 0x00405960
 * VROM: 0x005960
 * Size: 0x108
 */
// int __start();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/__start.s")

/**
 * _mcount
 * Address: 0x00405A68
 * VROM: 0x005A68
 * Size: 0xC8
 */
// int _mcount();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/_mcount.s")

/* Actual file starts here */

typedef int UNK_TYPE;

/* basics.h */

typedef int boolean;
#define FALSE 0
#define TRUE 1
typedef char* string;
typedef char buffer_t[0x200];
#define NIL '\0'

/* string_utils.h */

/* return true if strings are identical */
#define same_string(x, y) (strcmp(x, y) == 0)
#define same_string_prefix(x, y) (strncmp(x, y, strlen(y)) == 0)

/* return true if sub string is contained in s string */
#define contains_substring(s, sub) (strstr(s, sub) != NULL)

/**
 * list of strings, implemented as vector.
 *
 * @note By Open64 the implementation had become a linked string_list. We write the type as `string_list` instead of
 * `string_list_t` to distinguish them.
 */
typedef struct {
    int capacity;
    int length;
    string* entries;
} string_list;

#define LIST_CAPACITY_INCR 20
#define LIST_INITIAL_CAPACITY LIST_CAPACITY_INCR

typedef struct {
    const char* unk_0;
    unsigned int unk_4;
} struct_mpflags;

typedef enum {
    /* 0 */ ERRORCAT_INTERNAL, // Unused
    /* 1 */ ERRORCAT_ERROR,
    /* 2 */ ERRORCAT_WARNING,
    /* 3 */ ERRORCAT_INFO, // Unsued
    /* 4 */ ERRORCAT_FIX,  // Unused
    /* 5 */ ERRORCAT_ERRNO // Used for printing `sys_errlist[errno]`
} ErrorCategory;

void error(); // Called incorrectly
// void error(ErrorCategory category, const char* arg1, int arg2, const char* arg3, int arg4, const char* fmt, ...);

typedef enum {
    /* 1 */ SUF_1 = 1, // PL/1
    /* 2 */ SUF_2,     // COBOL
    /* 3 */ SUF_3,     // ?
    /* 4 */ SUF_4,     // ?
    /* 5 */ SUF_5,     // ?
    /* 6 */ SUF_6,     // C++
    /* 7 */ SUF_7      // C
} Suffix;

// This has been totally refactored in Open64
struct _struct_suffixes_0x8 {
    /* 0x0 */ const char* name; // suffix as a string
    /* 0x4 */ Suffix suffix;    // single-char code
};                              // size = 0x8

typedef enum {
    /* 1 */ COMPILER_1 = 1, // C
    /* 2 */ COMPILER_2,     // Pascal
    /* 3 */ COMPILER_3,     // FORTRAN
    /* 4 */ COMPILER_4,     // Assembler
    /* 5 */ COMPILER_5,     // PL1
    /* 6 */ COMPILER_6      // COBOL
} Compiler;

//! TODO: check
typedef enum {
    /* 0 */ C_COMPILER_CHOICE_0, // default, presumably "cc"
    /* 1 */ C_COMPILER_CHOICE_1, // "ncc" (NCC but for C?)
    /* 2 */ C_COMPILER_CHOICE_2, // "CC.eh", (C++ compiler with exception handling)
                                 // "CC", (Ordinary C++ compiler)
                                 // "NCC" (32-bit native C++ compiler, apparently just "CC -32")
    /* 3 */ C_COMPILER_CHOICE_3  // "DCC" (Delta/C++)
} CCompilerChoice;

typedef enum {
    /* 0 */ EDIT_FLAG_0, //!< E
    /* 1 */ EDIT_FLAG_1, //!< "-edit[0-9]"
    /* 2 */ EDIT_FLAG_2  //!< "-edit[0-9]" and environment variable for EDITOR contains "emacs"
} EditFlag;

typedef enum {
    /* 0 */ ANSICHOICE_KR,
    /* 1 */ ANSICHOICE_ANSI,
    /* 2 */ ANSICHOICE_ANSIPOSIX,
    /* 3 */ ANSICHOICE_XANSI
} AnsiChoice;

typedef enum {
    /* -1 */ CHIP_TARGET_UNSET = -1,
    /*  0 */ CHIP_TARGET_MIPS1,
    /*  1 */ CHIP_TARGET_MIPS2,
    /*  2 */ CHIP_TARGET_MIPS3
} ChipTarget;

//! TODO: check
typedef enum {
    /* 0 */ CPP_CHOICE_0,
    /* 1 */ CPP_CHOICE_1,
    /* 2 */ CPP_CHOICE_2, // ANSICHOICE_KR
    /* 3 */ CPP_CHOICE_3  // Other ANSICHOICE_
} CppChoice;

typedef enum {
    /* 0 */ MIPS_ABI_0, // ?. Set by IRIX4 flags and environment variable
    /* 1 */ MIPS_ABI_1, // O32. Default, also set by "-32bit", "-32", "-o32"
    /* 2 */ MIPS_ABI_2  // N64, not set
} MipsAbi;

typedef enum {
    /* 0 */ COMP_CHOICE_0,
    /* 1 */ COMP_CHOICE_1,
    /* 2 */ COMP_CHOICE_2,
    /* 3 */ COMP_CHOICE_3,
    /* 4 */ COMP_CHOICE_4
} CompChoice;

typedef enum {
    /* 1 */ EDISON_TYPE_1 = 1,
    /* 2 */ EDISON_TYPE_2,
    /* 3 */ EDISON_TYPE_3
} EdisonType;

void parse_command(int argc, char** argv);
void relocate_passes(char* arg0, char* arg1, char* arg2);
void newrunlib(void);
char getsuf(const /* string */ char* path);
char* mksuf(const char* path, char value);
/* string */ char* full_path(const /* string */ char* base);
void add_static_opt(/* string */ char* opt);
void compose_G0_libs(char* arg0);
int regular_file(const char*);
void addstr(string_list* list, string str);
void cleanup(void);
char* mkstr();
/* string */ char* savestr(const /* string */ char* src, size_t extra_length);

void get_lino(char* lino, const char* path, int mode);
void settimes(void);
void dotime(void);
static char* func_004339C8(char* name, char** dirs);
static void func_00436680(void);
static void func_0043673C(char* phase, int num_maps);
static const char* func_00434094(const char* path, int check_full_path);
static int func_004362CC(pid_t pid);
static void func_004365B8(void);

// bss

/* 03F310 10008310 */ static prmap_sgi_t B_10008310[100];      // equivalent of B_1000CAC0, "mapbuf"
/* 040C10 10009C10 */ clock_t time0;                           // line 174
                                                               // 0x4 padding
/* 040C18 10009C18 */ struct tms tm0;                          // line 176
/* 040C28 10009C28 */ char perr_msg[0x100];                    // char perr_msg[0x100]; // line 124
/* 040D28 10009D28 */ static char B_10009D28[0x400];           // "dirbuf"/"basebuf", likely declared above `basename`
/* 041128 1000A128 */ int plain_g;                             // line 127
/* 04112C 1000A12C */ int plain_O;                             // line 128
/* 041130 1000A130 */ int noaliasokflag;                       // line 129
/* 041134 1000A134 */ int haspl1;                              // line 130
/* 041138 1000A138 */ UNK_TYPE p2cstr;                         // line 132
/* 04113C 1000A13C */ int align;                               // line 133
/* 041140 1000A140 */ int align_common;                        // line 134
/* 041144 1000A144 */ char* alignarg;                          // line 136
/* 041148 1000A148 */ int use_real_fp;                         // line 137
/* 04114C 1000A14C */ int dollar_sign;                         // line 138
/* 041150 1000A150 */ int mp_flag;                             // line 140
/* 041154 1000A154 */ int mp_onetripflag;                      // line 141
/* 041158 1000A158 */ UNK_TYPE mp_staticflag;                  // line 142
/* 04115C 1000A15C */ int mp_dlinesflag;                       // line 143
/* 041160 1000A160 */ int mp_caseflag;                         // line 144
/* 041164 1000A164 */ int mp_66flag;                           // line 146
/* 041168 1000A168 */ int mp_i2flag;                           // line 148
/* 04116C 1000A16C */ int mp_col120flag;                       // line 150
/* 041170 1000A170 */ int mp_extendflag;                       // line 151
/* 041174 1000A174 */ int mp_uflag;                            // line 152
/* 041178 1000A178 */ int mp_backslashflag;                    // line 153
/* 04117C 1000A17C */ UNK_TYPE mp_uniq_specified;              // line 154
/* 041180 1000A180 */ UNK_TYPE mp_passes_relocated;            // line 155
/* 041184 1000A184 */ int default_template_instantiation_mode; // line 139
/* 041188 1000A188 */ int cmp_flag;                            // line 156
/* 04118C 1000A18C */ UNK_TYPE efl;                            // line 145
/* 041190 1000A190 */ char* ratfor;                            // line 147
/* 041194 1000A194 */ char* m4;                                // line 149
/* 041198 1000A198 */ int fullwarn;                            // line 157
/* 04119C 1000A19C */ char* aligndir;                          // line 158
/* 0411A0 1000A1A0 */ int docpp;                               // line 159
/* 0411A4 1000A1A4 */ int default_nocpp;                       // line 160
/* 0411A8 1000A1A8 */ unsigned int j;                          // line 161
/* 0411AC 1000A1AC */ char* tstring;                           // line 162
/* 0411B0 1000A1B0 */ char* hstring;                           // line 163
/* 0411B4 1000A1B4 */ char* Bstring;                           // line 164
/* 0411B8 1000A1B8 */ char* allBstring;                        // line 165
                                                               // 0x4 padding
/* 0411C0 1000A1C0 */ char alltstring[20];                     // line 167
/* 0411D4 1000A1D4 */ char* Warg;                              // line 168
/* 0411D8 1000A1D8 */ char* Wpass;                             // line 169
/* 0411DC 1000A1DC */ char* Kpass;                             // line 170
/* 0411E0 1000A1E0 */ char Karg[6];                            // line 171
/* 0411E6 1000A1E6 */ char Hchar;                              // line 172
/* 0411E8 1000A1E8 */ int retcode;                             // line 177
/* 0411EC 1000A1EC */ char* outfile;                           // line 178
/* 0411F0 1000A1F0 */ char* passin;                            // line 179
/* 0411F4 1000A1F4 */ char* passout;                           // line 180
/* 0411F8 1000A1F8 */ char* errout;                            // line 181
/* 0411FC 1000A1FC */ char* symtab;                            // line 182
/* 041200 1000A200 */ char* uopt0str;                          // line 183
/* 041204 1000A204 */ char* ddoptstr;                          // line 184
/* 041208 1000A208 */ char* optstr;                            // line 185
/* 04120C 1000A20C */ char* gentmp;                            // line 186
/* 041210 1000A210 */ char* binasm;                            // line 187
/* 041214 1000A214 */ char* uoutfile;                          // line 188
/* 041218 1000A218 */ char* lpi_st;                            // line 189
/* 04121C 1000A21C */ char* lpi_p1;                            // line 190
/* 041220 1000A220 */ char* lpi_dd;                            // line 191
/* 041224 1000A224 */ char* lpi_pd;                            // line 194
/* 041228 1000A228 */ char* linkorder;                         // line 195
/* 04122C 1000A22C */ UNK_TYPE valuesstr;                      // line 196
/* 041230 1000A230 */ UNK_TYPE tmp_elfobj;                     // line 197
/* 041234 1000A234 */ FILE* ldw_file;                          // line 199
/* 041238 1000A238 */ FILE* tmpsfile;                          // line 201
/* 04123C 1000A23C */ char* editor;                            // line 203
/* 041240 1000A240 */ char* xserver;                           // line 205
/* 041244 1000A244 */ int times_edited;                        // line 207
/* 041248 1000A248 */ int edit_cnt_max;                        // line 209
/* 04124C 1000A24C */ char srcsuf;                             // line 213
/* 041250 1000A250 */ /* boolean */ int tmpst;                 // line 216
/* 041254 1000A254 */ char* CRTX;                              // line 198
/* 041258 1000A258 */ char* MCRTX;                             // line 200
/* 04125C 1000A25C */ char* comp_target_root;                  // line 222
/* 041260 1000A260 */ string_list undefineflags;               // line 202
/* 04126C 1000A26C */ char* comp_host_root;                    // line 261
/* 041270 1000A270 */ string_list cppflags;                    // line 204
/* 04127C 1000A27C */ char* systype;                           // line 226
/* 041280 1000A280 */ string_list olimitflags;                 // line 206
/* 04128C 1000A28C */ int nonshared;                           // line 228
/* 041290 1000A290 */ string_list acppflags;                   // line 208
                                                               // 0x4 padding
/* 0412A0 1000A2A0 */ string_list mpcflags;                    // line 210
                                                               // 0x4 padding
/* 0412B0 1000A2B0 */ string_list accomflags;                  // line 212
                                                               // 0x4 padding
/* 0412C0 1000A2C0 */ string_list cfeflags;                    // line 215
                                                               // 0x4 padding
/* 0412D0 1000A2D0 */ string_list cpp2flags;                   // line 217
                                                               // 0x4 padding
/* 0412E0 1000A2E0 */ string_list uldlibflags;                 // line 219
                                                               // 0x4 padding
/* 0412F0 1000A2F0 */ string_list edisonflags;                 // line 221
/* 0412FC 1000A2FC */ char* tmpdir;                            // line 242
/* 041300 1000A300 */ string_list prelinkerflags;              // line 223
/* 04130C 1000A30C */ char* rls_id_object;                     // line 244
/* 041310 1000A310 */ string_list ccomflags;                   // line 225
/* 04131C 1000A31C */ char* progname;                          // line 246
/* 041320 1000A320 */ string_list upasflags;                   // line 227
/* 04132C 1000A32C */ char* currcomp;                          // line 248
/* 041330 1000A330 */ string_list fcomflags;                   // line 229
                                                               // 0x4 padding
/* 041340 1000A340 */ char* compdirs[7];                       // line 251
                                                               // 0x4 padding
/* 041360 1000A360 */ string_list eflflags;                    // line 231
/* 04136C 1000A36C */ Compiler compiler;                       // line 264
/* 041370 1000A370 */ string_list ratforflags;                 // line 233
                                                               // 0x4 padding
/* 041380 1000A380 */ char* tempstr[34];                       // line 268
/* 041408 1000A408 */ string_list upl1flags;                   // line 235
                                                               // 0x4 padding
/* 041418 1000A418 */ string_list ucobflags;                   // line 237
                                                               // 0x4 padding
/* 041428 1000A428 */ string_list ulpiflags;                   // line 239
                                                               // 0x4 padding
/* 041438 1000A438 */ string_list ujoinflags;                  // line 241
                                                               // 0x4 padding
/* 041448 1000A448 */ string_list uldflags;                    // line 243
                                                               // 0x4 padding
/* 041458 1000A458 */ static int B_1000A458[2];                // Pipe
/* 041460 1000A460 */ string_list usplitflags;                 // line 245
                                                               // 0x4 padding
/* 041470 1000A470 */ string_list umergeflags;                 // line 247
                                                               // 0x4 padding
/* 041480 1000A480 */ string_list uloopflags;                  // line 249
/* 04148C 1000A48C */ static char* B_1000A48C;                 // string containing most arguments "command_line"
/* 041490 1000A490 */ string_list uopt0flags;                  // line 253
/* 04149C 1000A49C */ static char* B_1000A49C;                 // string containing last "-o" argument ("outfile")
/* 0414A0 1000A4A0 */ string_list ddoptflags;                  // line 266
                                                               // 0x4 padding
/* 0414B0 1000A4B0 */ string_list optflags;                    // line 269
                                                               // 0x4 padding
/* 0414C0 1000A4C0 */ string_list genflags;                    // line 271
                                                               // 0x4 padding
/* 0414D0 1000A4D0 */ string_list asflags;                     // line 273
                                                               // 0x4 padding
/* 0414E0 1000A4E0 */ string_list ldflags;                     // line 277
                                                               // 0x4 padding
/* 0414F0 1000A4F0 */ string_list as1flags;                    // line 275
                                                               // 0x4 padding
/* 041500 1000A500 */ string_list ftocflags;                   // line 282
                                                               // 0x4 padding
/* 041510 1000A510 */ string_list cordflags;                   // line 284
                                                               // 0x4 padding
/* 041520 1000A520 */ string_list srcfiles;                    // line 286
                                                               // 0x4 padding
/* 041530 1000A530 */ string_list ufiles;                      // line 288
                                                               // 0x4 padding
/* 041540 1000A540 */ string_list objfiles;                    // line 290
                                                               // 0x4 padding
/* 041550 1000A550 */ string_list feedlist;                    // line 292
                                                               // 0x4 padding
/* 041560 1000A560 */ string_list execlist;                    // line 294
/* 04156C 1000A56C */ static int B_1000A56C;
/* 041570 1000A570 */ static int B_1000A570;
/* 041578 1000A578 */ string_list dirs_for_crtn;           // line 299
                                                           // 0x4 padding
/* 041588 1000A588 */ string_list dirs_for_nonshared_crtn; // line 301
                                                           // 0x4 padding
/* 041598 1000A598 */ string_list dirs_for_abi_crtn;       // line 303
                                                           // 0x4 padding
/* 0415A8 1000A5A8 */ string_list ldZflags;                // line 305
/* 0415B4 1000A5B4 */ static int B_1000A5B4;
/* 0415B8 1000A5B8 */ string_list pfaflags;         // line 307
/* 0415C4 1000A5C4 */ char* pfa;                    // line 307
/* 0415C8 1000A5C8 */ char* libI77_mp;              // line 309
                                                    // 0x4 padding
/* 0415D0 1000A5D0 */ string_list pcaflags;         // line 311
                                                    // 0x4 padding
/* 0415E0 1000A5E0 */ string_list soptflags;        // line 313
                                                    // 0x4 padding
/* 0415F0 1000A5F0 */ string_list staticopts;       // line 315
                                                    // 0x4 padding
/* 041600 1000A600 */ int __Argc;                   // line 319
/* 041604 1000A604 */ char** __Argv;                // line 317
/* 041608 1000A608 */ UNK_TYPE __rld_obj_head;      // line 318
/* 04160C 1000A60C */ static char B_1000A60C[0x04]; // padding?

// data

/* 0x037000 0x10000000 161  */ /* boolean */ int alternate_fe = FALSE;
/* 0x037004 0x10000004 162  */ AnsiChoice ansichoice = ANSICHOICE_XANSI;
/* 0x037008 0x10000008 163  */ CCompilerChoice c_compiler_choice = C_COMPILER_CHOICE_0;

/* 0x03700C 0x1000000C 164  */ struct _struct_suffixes_0x8 suffixes[] = {
    { "pl1", SUF_1 }, { "pli", SUF_1 }, { "cob", SUF_2 }, { "il", SUF_3 },  { "st", SUF_4 },
    { "anl", SUF_5 }, { "c++", SUF_6 }, { "cc", SUF_6 },  { "cxx", SUF_6 }, { "C", SUF_6 },
    { "cpp", SUF_6 }, { "CXX", SUF_6 }, { "CPP", SUF_6 }, { ".c", SUF_7 },  { NULL, 0 },
};

/* 0x037084 0x10000084 165  */ char* include = NULL;
/* 0x037088 0x10000088 166  */ char* includeB = NULL;
/* 0x03708C 0x1000008C 167  */ char* einclude = NULL;
/* 0x037090 0x10000090 168  */ char* eincludeB = NULL;
/* 0x037094 0x10000094 169  */ char* cpp = NULL;
/* 0x037098 0x10000098 170  */ char* ccom = NULL;
/* 0x03709C 0x1000009C 171  */ char* mpc = NULL;
/* 0x0370A0 0x100000A0 172  */ char* cfe = NULL;
/* 0x0370A4 0x100000A4 173  */ char* upas = NULL;
/* 0x0370A8 0x100000A8 174  */ char* fcom = NULL;
/* 0x0370AC 0x100000AC 175  */ char* upl1 = NULL;
/* 0x0370B0 0x100000B0 176  */ char* pl1err = NULL;
/* 0x0370B4 0x100000B4 177  */ char* ulpi = NULL;
/* 0x0370B8 0x100000B8 178  */ char* ucob = NULL;
/* 0x0370BC 0x100000BC 179  */ char* ujoin = NULL;
/* 0x0370C0 0x100000C0 180  */ char* usplit = NULL;
/* 0x0370C4 0x100000C4 181  */ char* uld = NULL;
/* 0x0370C8 0x100000C8 182  */ char* umerge = NULL;
/* 0x0370CC 0x100000CC 183  */ char* uloop = NULL;
/* 0x0370D0 0x100000D0 184  */ char* uopt0 = NULL;
/* 0x0370D4 0x100000D4 185  */ char* ddopt = NULL;
/* 0x0370D8 0x100000D8 186  */ char* opt = NULL;
/* 0x0370DC 0x100000DC 187  */ char* gen = NULL;
/* 0x0370E0 0x100000E0 188  */ char* as0 = NULL;
/* 0x0370E4 0x100000E4 189  */ char* as1 = NULL;
/* 0x0370E8 0x100000E8 190  */ char* ld = NULL;
/* 0x0370EC 0x100000EC 191  */ char* ftoc = NULL;
/* 0x0370F0 0x100000F0 192  */ char* cord = NULL;
/* 0x0370F4 0x100000F4 193  */ char* btou = NULL;
/* 0x0370F8 0x100000F8 194  */ char* utob = NULL;
/* 0x0370FC 0x100000FC 195  */ char* patch = NULL;
/* 0x037100 0x10000100 196  */ /* string */ char* filter = NULL;
/* 0x037104 0x10000104 197  */ char* prelinker = NULL;
/* 0x037108 0x10000108 198  */ /* boolean */ int smart_build = FALSE;
/* 0x03710C 0x1000010C 199  */ char* sbrepos = NULL;
/* 0x037110 0x10000110 200  */ /* boolean */ int no_prelink = FALSE;
/* 0x037114 0x10000114 201  */ /* boolean */ int nofilt = FALSE;
/* 0x037118 0x10000118 202  */ /* boolean */ int force_prelink = FALSE;
/* 0x03711C 0x1000011C 203  */ int verbose_prelink = FALSE; // pseudoboolean
/* 0x037120 0x10000120 204  */ /* boolean */ int auto_template_include = TRUE;
/* 0x037124 0x10000124 205  */ /* boolean */ int nocode = FALSE;
/* 0x037128 0x10000128 206  */ /* boolean */ int nocompileneeded = FALSE;
/* 0x03712C 0x1000012C 207  */ char* LibM = " -lm";
/* 0x037130 0x10000130 208  */ char* LibP = " -lp";
/* 0x037134 0x10000134 209  */ char* LibF77 = " -lF77";
/* 0x037138 0x10000138 210  */ char* LibI77 = " -lI77";
/* 0x03713C 0x1000013C 211  */ char* LibU77 = " -lU77";
/* 0x037140 0x10000140 212  */ char* LibIsam = " -lisam";
/* 0x037144 0x10000144 213  */ char* LibExc = " -lexc";
/* 0x037148 0x10000148 214  */ char* LibDw = " -ldw";
/* 0x03714C 0x1000014C 215  */ char* LibPl1 = NULL;
/* 0x037150 0x10000150 216  */ char* LibCob = NULL;
/* 0x037154 0x10000154 217  */ char* LibSort = NULL;
/* 0x037158 0x10000158 218  */ char* LibProf1 = " -lprof";
/* 0x03715C 0x1000015C 219  */ char* LibXmalloc = " -lxmalloc";
/* 0x037160 0x10000160 220  */ char* LibMld = " -lmld";
/* 0x037164 0x10000164 221  */ char* crtx = NULL;
/* 0x037168 0x10000168 222  */ char* crtn = NULL;
/* 0x03716C 0x1000016C 223  */ char* cxx_init = NULL;
/* 0x037170 0x10000170 224  */ char* delta_init = NULL;
/* 0x037174 0x10000174 225  */ char* libp = NULL;
/* 0x037178 0x10000178 226  */ char* libp_b = NULL;
/* 0x03717C 0x1000017C 227  */ char* libm = NULL;
/* 0x037180 0x10000180 228  */ char* libm_b = NULL;
/* 0x037184 0x10000184 229  */ char* libF77 = NULL;
/* 0x037188 0x10000188 230  */ char* libF77_b = NULL;
/* 0x03718C 0x1000018C 231  */ char* libI77 = NULL;
/* 0x037190 0x10000190 232  */ char* libI77_b = NULL;
/* 0x037194 0x10000194 233  */ char* libU77 = NULL;
/* 0x037198 0x10000198 234  */ char* libftn = NULL;
/* 0x03719C 0x1000019C 235  */ char* libU77_b = NULL;
/* 0x0371A0 0x100001A0 236  */ char* libisam = NULL;
/* 0x0371A4 0x100001A4 237  */ char* libisam_b = NULL;
/* 0x0371A8 0x100001A8 238  */ char* libdw_path = NULL;
/* 0x0371AC 0x100001AC 239  */ char* libdw = NULL;
/* 0x0371B0 0x100001B0 240  */ char* libdw_b = NULL;
/* 0x0371B4 0x100001B4 241  */ char* libpl1 = NULL;
/* 0x0371B8 0x100001B8 242  */ char* libpl1_b = NULL;
/* 0x0371BC 0x100001BC 243  */ char* libexc = NULL;
/* 0x0371C0 0x100001C0 244  */ char* libexc_b = NULL;
/* 0x0371C4 0x100001C4 21   */ int libcob = NULL;    // unused // dynsym reorder?
/* 0x0371C8 0x100001C8 22   */ int libcob_b = NULL;  // unused
/* 0x0371CC 0x100001CC 245  */ char* libsort = NULL; // dynsym reorder?
/* 0x0371D0 0x100001D0 246  */ char* libsort_b = NULL;
/* 0x0371D4 0x100001D4 247  */ char* libprof = NULL;
/* 0x0371D8 0x100001D8 248  */ char* libxmalloc = NULL;
/* 0x0371DC 0x100001DC 249  */ char* libxmalloc_b = NULL;
/* 0x0371E0 0x100001E0 250  */ char* cpp_stdflag = NULL;
/* 0x0371E4 0x100001E4 251  */ char* libmld = NULL;
/* 0x0371E8 0x100001E8 252  */ /* boolean */ int crtn_required = TRUE;
/* 0x0371EC 0x100001EC 253  */ char* pca = NULL;
/* 0x0371F0 0x100001F0 254  */ char* libc_mp = NULL;
/* 0x0371F4 0x100001F4 255  */ char* fopt = NULL;
/* 0x0371F8 0x100001F8 256  */ char* copt = NULL;
/* 0x0371FC 0x100001FC None */ static /* boolean */ int D_100001FC = FALSE;
/* 0x037200 0x10000200 None */ static /* boolean */ int D_10000200 = FALSE;
/* 0x037204 0x10000204 None */ static char* D_10000204 = NULL;
/* 0x037208 0x10000208 None */ static char* D_10000208 = NULL;
/* 0x03720C 0x1000020C None */ static /* boolean */ int D_1000020C = FALSE;
/* 0x037210 0x10000210 None */ static /* boolean */ int D_10000210 = TRUE;
/* 0x037214 0x10000214 257  */ /* boolean */ int Eflag;
/* 0x037218 0x10000218 258  */ int Pflag = FALSE; // pseudoboolean
/* 0x03721C 0x1000021C 259  */ int gflag = 0;
/* 0x037220 0x10000220 260  */ int pflag = 0;
/* 0x037224 0x10000224 261  */ int jflag = FALSE; // pseudoboolean
/* 0x037228 0x10000228 262  */ int cflag = FALSE; // pseudoboolean
/* 0x03722C 0x1000022C 263  */ int Sflag = FALSE; // pseudoboolean
/* 0x037230 0x10000230 264  */ int Oflag = 1;
/* 0x037234 0x10000234 265  */ /* boolean */ int vflag = FALSE;
/* 0x037238 0x10000238 266  */ /* boolean */ int execute_flag = TRUE;
/* 0x03723C 0x1000023C 267  */ /* boolean */ int Vflag = FALSE;
/* 0x037240 0x10000240 268  */ /* boolean */ int Kflag = FALSE;
/* 0x037244 0x10000244 269  */ int minus_M = FALSE; // pseudoboolean
/* 0x037248 0x10000248 270  */ /* boolean */ int anachronisms = TRUE;
/* 0x03724C 0x1000024C 271  */ /* boolean */ int disable_inlines = FALSE;
/* 0x037250 0x10000250 272  */ /* boolean */ int cfront_compatible = TRUE;
/* 0x037254 0x10000254 273  */ int make_edison_shlib = FALSE; // pseudoboolean
/* 0x037258 0x10000258 274  */ /* boolean */ int plusIflag = FALSE;
/* 0x03725C 0x1000025C 275  */ /* boolean */ int signedcharflag = FALSE;
/* 0x037260 0x10000260 276  */ /* boolean */ int Lflag = FALSE;
/* 0x037264 0x10000264 277  */ /* boolean */ int set_loop_unroll = FALSE;
/* 0x037268 0x10000268 278  */ int mflag = FALSE; // pseudoboolean
/* 0x03726C 0x1000026C 279  */ int Fflag = FALSE; // pseudoboolean
/* 0x037270 0x10000270 280  */ int stdflag = 0;
/* 0x037274 0x10000274 281  */ /* boolean */ int cplusflag = FALSE;
/* 0x037278 0x10000278 282  */ /* boolean */ int ucodeflag = FALSE;
/* 0x03727C 0x1000027C 283  */ /* boolean */ int Bflag = FALSE;
/* 0x037280 0x10000280 284  */ /* boolean */ int fiveflag = FALSE;
/* 0x037284 0x10000284 285  */ /* boolean */ int automaticflag = TRUE;
/* 0x037288 0x10000288 286  */ int emptyIflag = FALSE; // pseudoboolean
/* 0x03728C 0x1000028C 287  */ /* boolean */ int cordflag = FALSE;
/* 0x037290 0x10000290 288  */ /* boolean */ int ansiflag = FALSE;
/* 0x037294 0x10000294 289  */ /* boolean */ int lpilockflag = FALSE;
/* 0x037298 0x10000298 290  */ /* boolean */ int nolockflag = FALSE;
/* 0x03729C 0x1000029C 291  */ /* boolean */ int unrollflag = FALSE;
/* 0x0372A0 0x100002A0 292  */ /* boolean */ int libm_spec = FALSE;
/* 0x0372A4 0x100002A4 293  */ /* boolean */ int libfastm_spec = FALSE;
/* 0x0372A8 0x100002A8 294  */ EditFlag editflag = EDIT_FLAG_0;
/* 0x0372AC 0x100002AC 295  */ /* boolean */ int oldccomflag = FALSE;
/* 0x0372B0 0x100002B0 296  */ /* boolean */ int oldcflag = FALSE;
/* 0x0372B4 0x100002B4 297  */ /* boolean */ int oldcppflag = FALSE;
/* 0x0372B8 0x100002B8 23   */ /* boolean */ int fflag = FALSE;  // unused // dynsym reorder?
/* 0x0372BC 0x100002BC 298  */ /* boolean */ int tpflag = FALSE; // dynsym reorder?
/* 0x0372C0 0x100002C0 299  */ /* boolean */ int ddoptflag = FALSE;
/* 0x0372C4 0x100002C4 300  */ /* boolean */ int uopt0flag = FALSE;
/* 0x0372C8 0x100002C8 24   */ /* boolean */ int protoflag = FALSE;   // dynsym reorder?
/* 0x0372CC 0x100002CC 301  */ /* boolean */ int kminabiflag = FALSE; // dynsym reorder?
/* 0x0372D0 0x100002D0 302  */ /* boolean */ int kpicopt_flag = FALSE;
/* 0x0372D4 0x100002D4 303  */ /* boolean */ int nokpicopt_flag = FALSE;
/* 0x0372D8 0x100002D8 304  */ /* boolean */ int elfflag = TRUE;
/* 0x0372DC 0x100002DC 305  */ /* boolean */ int coff_spec = FALSE;
/* 0x0372E0 0x100002E0 306  */ /* boolean */ int elf_spec = FALSE;
/* 0x0372E4 0x100002E4 307  */ /* boolean */ int compose_first_G0 = FALSE;
/* 0x0372E8 0x100002E8 308  */ /* boolean */ int mips1_spec_flag = FALSE;
/* 0x0372EC 0x100002EC 309  */ /* boolean */ int mips1flag = TRUE;
/* 0x0372F0 0x100002F0 310  */ /* boolean */ int mips2flag = FALSE;
/* 0x0372F4 0x100002F4 311  */ /* boolean */ int mips3flag = FALSE;
/* 0x0372F8 0x100002F8 312  */ /* boolean */ int ignore_unresolved_flag = FALSE;
/* 0x0372FC 0x100002FC 313  */ /* boolean */ int no_unresolved_flag = FALSE;
/* 0x037300 0x10000300 314  */ /* boolean */ int swopcodeflag = FALSE;
/* 0x037304 0x10000304 315  */ /* boolean */ int dwopcodeflag = FALSE;
/* 0x037308 0x10000308 316  */ /* boolean */ int sixty4bit_spec = FALSE;
/* 0x03730C 0x1000030C 317  */ /* boolean */ int sixty4bitflag = FALSE;
/* 0x037310 0x10000310 318  */ /* boolean */ int thirty2bitflag = FALSE;
/* 0x037314 0x10000314 319  */ /* boolean */ int fullasoptflag = FALSE;
/* 0x037318 0x10000318 320  */ /* boolean */ int old_non_shared = FALSE;
/* 0x03731C 0x1000031C 321  */ /* boolean */ int non_shared_emitted = FALSE;
/* 0x037320 0x10000320 322  */ /* boolean */ int longlong_emitted = FALSE;
/* 0x037324 0x10000324 323  */ /* boolean */ int non_shared = FALSE;
/* 0x037328 0x10000328 324  */ /* boolean */ int Gseen_flag = FALSE;
/* 0x03732C 0x1000032C 325  */ /* boolean */ int transitive_link = FALSE;
/* 0x037330 0x10000330 326  */ /* boolean */ int full_transitive_link = FALSE;
/* 0x037334 0x10000334 327  */ /* boolean */ int no_transitive_link = FALSE;
/* 0x037338 0x10000338 328  */ /* boolean */ int quickstart_info = FALSE;
/* 0x03733C 0x1000033C 329  */ /* boolean */ int force_rm_dead_code = FALSE;
/* 0x037340 0x10000340 330  */ /* boolean */ int kpic_flag = TRUE;
/* 0x037344 0x10000344 331  */ /* boolean */ int kpic_spec = FALSE;
/* 0x037348 0x10000348 332  */ /* boolean */ int call_shared = FALSE;
/* 0x03734C 0x1000034C 333  */ /* boolean */ int excpt_flag = FALSE;
/* 0x037350 0x10000350 334  */ /* boolean */ int trapuv_flag = FALSE;
/* 0x037354 0x10000354 335  */ int dmips_emit = 0;                     // boolean?
/* 0x037358 0x10000358 25   */ int Xvalues_Flag = 0;                   // dynsym reorder?
/* 0x03735C 0x1000035C 336  */ /* boolean */ int user_systype = FALSE; // dynsym reorder?
/* 0x037360 0x10000360 337  */ /* boolean */ int ddoptinfo = FALSE;
/* 0x037364 0x10000364 338  */ /* boolean */ int systype_seen = FALSE;
/* 0x037368 0x10000368 339  */ /* boolean */ int multiple_systype = FALSE;
/* 0x03736C 0x1000036C 340  */ /* boolean */ int systype_warn = FALSE;
/* 0x037370 0x10000370 341  */ /* boolean */ int svr4_systype = FALSE;
/* 0x037374 0x10000374 342  */ /* boolean */ int c_inline = FALSE;
/* 0x037378 0x10000378 343  */ /* boolean */ int tfp_flag = FALSE;
/* 0x03737C 0x1000037C 344  */ int abi_flag = 0;
/* 0x037380 0x10000380 345  */ int memory_flag = 0;
/* 0x037384 0x10000384 346  */ /* boolean */ int default_call_shared = TRUE;
/* 0x037388 0x10000388 347  */ /* boolean */ int haspascal = FALSE;
/* 0x03738C 0x1000038C 348  */ /* boolean */ int hasfortran = FALSE;
/* 0x037390 0x10000390 349  */ int lmflag = FALSE; // pseudoboolean
/* 0x037394 0x10000394 350  */ int srcexists = FALSE;
/* 0x037398 0x10000398 351  */ int w1flag = 1;
/* 0x03739C 0x1000039C None */ static int D_1000039C = 0;
/* 0x0373A0 0x100003A0 352  */ /* boolean */ int prototype_checking_on = FALSE;
/* 0x0373A4 0x100003A4 353  */ /* boolean */ int showdirt_flag = FALSE;
/* 0x0373A8 0x100003A8 354  */ int mp_prepass_count = 0;

/* 0x0373AC 0x100003AC 355  */ struct_mpflags mpflags[] = {
    { "list", 0x10003 },
    { "keep", 0x10007 },
    { NULL, 0 },
};

/* 0x0373C4 0x100003C4 356  */ struct_mpflags cmpflags[] = {
    { "list", 0x10003 },
    { "keep", 0x10007 },
    { NULL, 0 },
};

/* 0x0373DC 0x100003DC 357  */ /* boolean */ int acpp = FALSE;
/* 0x0373E0 0x100003E0 358  */ MipsAbi mips_abi = MIPS_ABI_1;
/* 0x0373E4 0x100003E4 359  */ CompChoice compchoice = COMP_CHOICE_0;
/* 0x0373E8 0x100003E8 360  */ CppChoice cppchoice = CPP_CHOICE_0;
/* 0x0373EC 0x100003EC 361  */ int acpp_traditional = FALSE; // pseudoboolean
/* 0x0373F0 0x100003F0 362  */ /* boolean */ int G_flag = FALSE;
/* 0x0373F4 0x100003F4 363  */ /* boolean */ int dn_flag = FALSE;
/* 0x0373F8 0x100003F8 364  */ int edison_cpp = 1;
/* 0x0373FC 0x100003FC 365  */ EdisonType edison_type = EDISON_TYPE_1;
/* 0x037400 0x10000400 366  */ char* Gnum = "0";
/* 0x037404 0x10000404 367  */ int runerror = 0;
/* 0x037408 0x10000408 368  */ /* boolean */ int uload = FALSE;
/* 0x03740C 0x1000040C 369  */ int uldobj_place = -1;
/* 0x037410 0x10000410 370  */ char* tmp_uldobj = NULL;
/* 0x037414 0x10000414 371  */ ChipTarget chip_targ = CHIP_TARGET_UNSET;
/* 0x037418 0x10000418 372  */ int nobjs = FALSE; // pseudoboolean
/* 0x03741C 0x1000041C 373  */ int targetsex = BIGENDIAN;
/* 0x037420 0x10000420 374  */ /* boolean */ int default_svr4 = FALSE;
/* 0x037424 0x10000424 375  */ /* boolean */ int irix4 = FALSE;
/* 0x037428 0x10000428 376  */ char* runlib = "/";
/* 0x03742C 0x1000042C 377  */ char* runlib_base = "/";
/* 0x037430 0x10000430 None */ static prmap_sgi_arg_t D_10000430 = { (caddr_t)B_10008310, 0x1900 }; // mapbuf_desc
/* 0x037438 0x10000438 None */ static char* D_10000438 = NULL; // current working directory (D_1000C1D0 in 7.1)
/* 0x03743C 0x1000043C 378  */ /* boolean */ int run_sopt = FALSE;
/* 0x037440 0x10000440 None */ static char* D_10000440 = NULL;
/* 0x037444 0x10000444 None */ static char* D_10000444 = NULL;

// static int Pipe[2]; /* for implementing semaphore */
#ifndef linux
// static prmap_sgi_t mapbuf[100]; // B_10008310
// static prmap_sgi_arg_t mapbuf_desc = { (char *) mapbuf, sizeof (mapbuf)} ;
#define DATA_ADDRESS ((char*)0x10000000)
#define TEXT_ADDRESS ((char*)0x400000)
#endif

/**
 * main
 * Address: 0x00405B30
 * VROM: 0x005B30
 * Size: 0x16250
 */
// int main();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/main.s")

/**
 * process_config
 * Address: 0x0041BD80
 * VROM: 0x01BD80
 * Size: 0x570
 */
void process_config(int argc, char** argv) {
    register int i;
    register char* var_s1;
    char* sp1144 = comp_target_root;
    char* sp1140;
    FILE* sp113C;
    char sp13C[0x1000]; // can be scoped
    int sp138;
    char* sp38[0x40];

    for (i = 1; i < argc; i++) {
        if (same_string(argv[i], "-systype")) {
            i++;
            if (i >= argc) {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-systype must have an argument\n");
                exit(2);
            }
            user_systype = TRUE;
            systype = argv[i];
            if (same_string(systype, "svr4")) {
                svr4_systype = TRUE;
            } else {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "only systype svr4 allowed\n");
                exit(2);
            }
            if (!same_string(systype, "svr4") && !same_string(systype, "bsd43") && !same_string(systype, "svr3") &&
                !same_string(systype, "sysv") && (fopen(strcat("/", systype), "r") == NULL) && !systype_warn) {
                error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                      "This systype doesn't exist on this machine; changed systype to svr3.\n");
                systype_warn = TRUE;
                systype = "svr3";
            }
            if (!svr4_systype) {
                sp1144 = mkstr(comp_target_root, systype, "/", NULL);
            }
            break;
        }
    }

    if (!user_systype) {
        sp1144 = mkstr(comp_target_root, systype, "/", NULL);
    }
    user_systype = FALSE;
    sp1140 = mkstr(sp1144, "usr/lib/", currcomp, "comp.config", NULL);
    sp113C = fopen(sp1140, "r");
    if (sp113C != NULL) {
        if (1) {}
        if (fgets(sp13C, 0x1000, sp113C) != NULL) {
            if (sp13C[strlen(sp13C) - 1] == '\n') {
                sp13C[strlen(sp13C) - 1] = '\0';
            }
            var_s1 = sp13C;
            i = sp138 = 0;
            while (*var_s1 != '\0') {
                while ((*var_s1 != '\0') && ((*var_s1 == ' ') || (*var_s1 == '\t'))) {
                    var_s1++;
                }

                if (*var_s1 != 0) {
                    sp38[sp138] = var_s1;
                    sp138++;
                }

                while ((*var_s1 != '\0') && (*var_s1 != ' ') && (*var_s1 != '\t')) {
                    var_s1++;
                }

                if (*var_s1 != '\0') {
                    *var_s1++ = '\0';
                }
            }

            parse_command(sp138, sp38);
        }
    }
}

/**
 * add_info
 * Address: 0x0041C2F0
 * VROM: 0x01C2F0
 * Size: 0x12C
 */
void add_info(char* s) {
    addstr(&upasflags, s);
    addstr(&fcomflags, s);
    addstr(&ulpiflags, s);
    addstr(&uopt0flags, s);
    addstr(&ddoptflags, s);
    addstr(&optflags, s);
    addstr(&umergeflags, s);
    addstr(&uloopflags, s);
    addstr(&genflags, s);
    addstr(&asflags, s);
    addstr(&ldflags, s);
}

/**
 * parse_command
 * Address: 0x0041C41C
 * VROM: 0x01C41C
 * Size: 0xEA64
 */
/**
Notes on stack:
sp54, sp58, sp5C are in the same place
sp60 gone
sp64 -> 60
sp68 -> 64
sp6C -> 68
sp70 -> 6C
sp74 -> 70
spFC -> F8
sp100 -> FC
sp104 gone
sp108 -> 100
sp10C -> 104
sp110 -> 108
sp114 -> 10C
sp118 gone
sp11C -> 110
sp120 -> 114
sp120/sp124 new
sp128 -> 118
sp12C gone
sp130 gone
sp134 -> 11C
sp140 + 2 pads gone
sp144 -> 128
sp148 -> 12C
sp14C -> 130
sp154 -> 134
sp158 -> 138
sp15C -> 13C
*/
void parse_command(int argc, char** argv) {
    register int var_s0;   // option index
    register char var_s1;  // file suffix, multipurpose?
    register char* var_s2; // multipurpose string pointer
    register char* var_s3; // used for -G?
    char* sp15C = NULL;    // related to -MD? // sp13C
    char* sp158 = NULL;    // sp138
    char* sp154 = NULL;    // target // sp134
    // char sp153 = 0;     // unused
    int sp14C = 1;                     // Treat bad options as errors // sp130
    char* sp148 = getenv("SGI_IRIX4"); // sp12C

    if (sp148 != NULL) {
        irix4 = TRUE;
        comp_host_root = "/usr/irix4/";
        systype = "";
        elfflag = FALSE;
        svr4_systype = FALSE;
        call_shared = FALSE;
        non_shared = FALSE;
        old_non_shared = FALSE;
        default_call_shared = FALSE;
        Gnum = "8";
        kpic_flag = FALSE;
        mips_abi = MIPS_ABI_0;
        runlib = "/usr/irix4/";
        relocate_passes("pKfjrsulmvocabtyz", NULL, NULL);
    }

    for (var_s0 = 0; var_s0 < argc; var_s0++) {
        if ((argv[var_s0][0] == '-')
            // && (!NoMoreOptions || (strchr(argv[var_s0], '.') == NULL))
        ) {
            switch (argv[var_s0][1]) { /* switch 1 */
                case '#':              /* switch 1 */
                                       //! @bug Should end in '\n'.
                    error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "-# is not supported. Use -v to see compiler passesn");
                    break;

                case '1': /* switch 1 */
                    if ((compiler == COMPILER_3) && (argv[var_s0][2] == '\0')) {
                        mp_onetripflag = TRUE;
                        addstr(&fcomflags, argv[var_s0]);
                        break;
                    }
                    goto bad_option;

                case '3': /* switch 1 */
                    if ((strcmp(argv[var_s0], "-32bit") == 0) || (strcmp(argv[var_s0], "-32") == 0)) {
                        thirty2bitflag = TRUE;
                        mips_abi = MIPS_ABI_1;
                    }
                    break;

                case '5': /* switch 1 */
                    error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "-5 not supported\n");
                    if (argv[var_s0][2] == '\0') {
                        if (Bflag) {
                            if (!fiveflag) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-5 must precede any -B flags\n");
                                exit(2);
                            }
                        } else {
                            fiveflag++;
                            include = mkstr(comp_target_root, "usr/5include", NULL);
                            if (Bstring != NULL) {
                                relocate_passes("h", NULL, Bstring);
                            }
                            newrunlib();
                        }
                        break;
                    }
                    goto bad_option;

                case '6': /* switch 1 */
                    if ((compiler == COMPILER_3) && (strcmp(argv[var_s0], "-66") == 0)) {
                        addstr(&fcomflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-64bit") == 0) {
                        error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                              "-64bit option is not yet implemented for ucode compilers, ignore\n");
                        sixty4bit_spec = TRUE;
                        if (swopcodeflag) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                                  "-64bit can not be used with -swopcode for ucode compilers\n");
                            exit(2);
                        }
                        break;
                    }
                    goto bad_option;

                case 'A': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        var_s0++;
                        if (var_s0 < argc) {
                            addstr(&objfiles, "-A");
                            addstr(&objfiles, argv[var_s0]);
                            break;
                        } else {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "ld requires -A to have an argument\n");
                            exit(2);
                        }
                    }
                    if (strcmp(argv[var_s0], "-AutoGnum") == 0) {
                        addstr(&uldflags, argv[var_s0]);
                        if (strcmp(Gnum, "0") != 0) {
                            Gnum = "0";
                        }
                        break;
                    }
                    // -AA[cpp flag]
                    if (argv[var_s0][1] == 'A') {
                        addstr(&cppflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-A-") == 0) {
                        addstr(&cppflags, argv[var_s0]);
                        break;
                    }
                    goto bad_option;

                case 'B': /* switch 1 */
                          // clang-format off
                    if ((argv[var_s0][2] == '\0') && (var_s0 < (argc - 1)) &&
                        ((strcmp(argv[var_s0 + 1], "static") == 0)
                        || (strcmp(argv[var_s0 + 1], "dynamic") == 0)
                        || (strcmp(argv[var_s0 + 1], "symbolic") == 0))) {
                          // clang-format on
                        addstr(&objfiles, argv[var_s0]);
                        var_s0++;
                        addstr(&objfiles, argv[var_s0]);
                    } else {
                        char* sp144;

                        Bflag = TRUE;
                        sp144 = argv[var_s0] + 2;
                        relocate_passes(tstring, hstring, sp144);
                        if (tstring == NULL) {
                            Bstring = sp144;
                        }
                    }
                    break;

                case 'C': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        if (compiler == COMPILER_3) {
                            addstr(&fcomflags, argv[var_s0]);
                            break;
                        }
                        if (compiler == COMPILER_2) {
                            addstr(&upasflags, argv[var_s0]);
                            break;
                        }
                        if (compiler == COMPILER_1) {
                            addstr(&cppflags, argv[var_s0]);
                            break;
                        }
                    }
                    //! @note Only checks for "-CG_E"
                    if (strncmp(argv[var_s0], "-CG_EMIT:", 5) == 0) {
                        error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "-CG_EMIT options are ignored\n");
                        break;
                    }
                    goto bad_option;

                case 'D': /* switch 1 */
                    // Has changed completely
                    // if (strncmp(argv[var_s0], "-DEFAULT:", strlen("-DEFAULT:")) == 0) {
                    //     break;
                    // }
                    if (argv[var_s0][2] == '\0') {
                        if (default_svr4 != 0) {
                            addstr(&undefineflags, strcat("-D", argv[var_s0 + 1]));
                            add_static_opt(argv[var_s0]);
                            var_s0++;
                            break;
                        }
                        if (((var_s0 + 1) < argc)) {
                            unsigned long sp124;
                            char* sp120;
                            sp124 = strtoul(argv[var_s0 + 1], &sp120, 16);
                            if (((sp120 - argv[var_s0 + 1]) != strlen(argv[var_s0 + 1])) ||
                                ((sp124 == 0) && (argv[var_s0 + 1] == sp120)) || (argv[var_s0 + 1][0] == '-') ||
                                (argv[var_s0 + 1][0] == '+')) {
                                error(2, 0, 0, 0, 0, "-D taken as empty cpp -D, not ld(1) -D hexnum\n");
                                break;
                            }
                        }
                        // if ((var_s0 + 1) < argc) {
                        //     char* sp140;
                        //     // TODO: work out where these should actually go
                        //     // int pad[2];

                        //     if (0) {
                        //         (void)"-D taken as empty cpp -D, not ld(1) -D hexnum\n";
                        //         (void)"-D";
                        //         (void)"ld requires -D to have an argument\n";
                        //     }
                        //     sp140 = malloc(strlen(argv[var_s0 + 1]) + 3);
                        //     sp140[0] = '-';
                        //     sp140[1] = 'D';
                        //     sp140[2] = '\0';
                        //     addstr(&undefineflags, strcat(sp140, argv[var_s0 + 1]));
                        //     add_static_opt(mkstr(argv[var_s0], argv[var_s0 + 1], NULL));
                        // }
                        var_s0++;
                        if (var_s0 < argc) {
                            addstr(&ldflags, "-D");
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        } else {
                            error(1, 0, 0, 0, 0, "ld requires -D to have an argument\n");
                            exit(2);
                        }
                    }
                    addstr(&undefineflags, argv[var_s0]);
                    add_static_opt(argv[var_s0]);
                    break;

                case 'E': /* switch 1 */
                    // -E
                    if (argv[var_s0][2] == '\0') {
                        Eflag++;
                        docpp = TRUE;
                        break;
                    }
                    // -EB/-EL (Endian)
                    if ((argv[var_s0][3] == '\0') && ((argv[var_s0][2] == 'B') || (argv[var_s0][2] == 'L'))) {
                        if (argv[var_s0][2] == 'B') {
                            if (Bflag && (targetsex != BIGENDIAN)) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                                      "-EB or -EL must precede any -B flags for ucode compilers\n");
                                exit(2);
                            }
                            targetsex = BIGENDIAN;
                        } else {
                            if (Bflag && (targetsex != LITTLEENDIAN)) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                                      "-EB or -EL must precede any -B flags for ucode compilers\n");
                                exit(2);
                            }
                            targetsex = LITTLEENDIAN;
                        }
                        newrunlib();
                        break;
                    }
                    goto bad_option;

                case 'F': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        if (compiler == COMPILER_3) {
                            Fflag++;
                        } else if ((compiler == COMPILER_1) && ((c_compiler_choice == C_COMPILER_CHOICE_2) ||
                                                                (c_compiler_choice == C_COMPILER_CHOICE_3))) {
                            cflag = TRUE;
                            Fflag = TRUE;
                            default_template_instantiation_mode = 1;
                        } else {
                            addstr(&ldflags, argv[var_s0]);
                        }
                        break;
                    }
                    goto bad_option;

                case 'G': /* switch 1 */
                    if (strncmp(argv[var_s0], "-GCM:", 5) == 0) {
                        error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "-GCM options are ignored\n");
                        break;
                    }
                    if (argv[var_s0][2] == '\0') {
                        if (default_svr4) {
                            if (dn_flag) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-G can not be used with -dn \n");
                                exit(2);
                            }
                            G_flag = TRUE;
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        }
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-G requires a decimal number argument\n");
                            exit(2);
                        }
                        if (Oflag < 3) {
                            Gnum = argv[var_s0];
                        } else {
                            Gnum = "0";
                        }
                    } else {
                        if (default_svr4) {
                            break;
                        }
                        if (Oflag < 3) {
                            Gnum = argv[var_s0] + 2;
                        } else {
                            Gnum = "0";
                        }
                    }
                    for (var_s2 = Gnum; *var_s2 != '\0'; var_s2++) {
                        if (!isdigit(*var_s2)) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "non-digit character in -G %s\n", Gnum);
                            exit(2);
                        }
                    }
                    if (!Gseen_flag) {
                        relocate_passes(tstring, hstring, NULL);
                        Gseen_flag = TRUE;
                    }
                    break;

                case 'H': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        addstr(&cppflags, argv[var_s0]);
                        Eflag++;
                        break;
                    }
                    if (argv[var_s0][3] == '\0') {
                        if (1) {} // FAKE
                        Hchar = argv[var_s0][2];

                        for (var_s2 = "fKMdkjusmocab"; (*var_s2 != '\0' && *var_s2 != Hchar); var_s2++) {}

                        if (*var_s2 == '\0') {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "Unknown character in %s\n", argv[var_s0]);
                            exit(2);
                        }
                        break;
                    }
                    goto bad_option;

                case 'I': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        if (((argv[var_s0 + 1] != NULL) && (*argv[var_s0 + 1] == '-')) ||
                            (isdir(argv[var_s0 + 1]) == 0)) {
                            emptyIflag++;
                        } else {
                            char* sp134;

                            var_s0++;
                            sp134 = mkstr("-I", argv[var_s0], NULL);
                            addstr(&cppflags, sp134);
                            addstr(&cpp2flags, sp134);
                            add_static_opt(mkstr("-I", full_path(argv[var_s0]), NULL));
                        }
                    } else {
                        addstr(&cppflags, argv[var_s0]);
                        addstr(&cpp2flags, argv[var_s0]);
                        // addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(mkstr("-I", full_path(argv[var_s0] + 2), NULL));
                    }
                    break;

                case 'J': /* switch 1 */
                    if (strcmp(argv[var_s0], "-Jsfm") == 0) {
                        break;
                    }
                    // if (strcmp(argv[var_s0], "-J") == 0) {
                    //     char* sp130;
                    //     char* sp12C = argv[var_s0 + 1];

                    //     for (sp130 = sp12C; *sp130 != 0; sp130++) {
                    //         if (!isdigit(*sp130)) {
                    //             error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "non-digit character in -J %s\n", sp12C);
                    //             exit(2);
                    //         }
                    //     }
                    //     addstr(&prelinkerflags, argv[var_s0]);
                    //     addstr(&prelinkerflags, sp12C);
                    //     var_s0++;
                    //     break;
                    // }
                    //! @bug fallthrough means -K options can also be specified with -J
                case 'K': /* switch 1 */
                    if (default_svr4) {
                        Kpass = argv[var_s0] + 2;
                        if (*Kpass == '\0') {
                            Kpass = argv[var_s0] + 3;
                        }

                        while ((*Kpass != '\0') || (*Kpass == ',')) {
                            //! @bug Specifying a long argument to "-K" will overwrite subsequent bss variables.
                            for (j = 0, var_s2 = Kpass; (*var_s2 != ',' && *var_s2 != '\0'); j++, var_s2++) {
                                Karg[j] = *var_s2;
                            }

                            Kpass = var_s2;

                            if (strncmp(Karg, "minabi", 6) == 0) {
                                kminabiflag = TRUE;
                            } else if (strncmp(Karg, "fpe", 3) == 0) {
                                addstr(&ldflags, "-Kfpe");
                            } else if (strncmp(Karg, "sd", 2) == 0) {
                                addstr(&ldflags, "-Ksd");
                            } else if (strncmp(Karg, "sz", 2) == 0) {
                                addstr(&ldflags, "-Ksz");
                            } else if (strncmp(Karg, "mau", 3) == 0) {
                                addstr(&ldflags, "-Kmau");
                            } else if (strncmp(Karg, "PIC", 3) == 0) {
                                if (non_shared) {
                                    error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                                          "Can't mix -KPIC and -non_shared, change to -non_shared\n");
                                    kpic_flag = FALSE;
                                } else {
                                    kpic_flag = TRUE;
                                    kpic_spec = TRUE;
                                }
                            } else {
                                goto bad_option;
                            }

                            for (j = 0; j < strlen(Karg); j++) {
                                Karg[j] = ' ';
                            }

                            while ((Kpass != NULL) && (*Kpass == ',') && (*Kpass != '\0')) {
                                Kpass++;
                            }
                        }
                        break;
                    }
                    if (svr4_systype) {
                        Kpass = argv[var_s0] + 2;
                        if (*Kpass == '\0') {
                            Kflag++;
                            addstr(&fcomflags, argv[var_s0]);
                        }

                        while ((*Kpass != '\0') || (*Kpass == ',')) {
                            //! @bug Specifying a long argument to "-K" will overwrite subsequent bss variables.
                            for (j = 0, var_s2 = Kpass; (*var_s2 != ',' && *var_s2 != '\0'); j++, var_s2++) {
                                Karg[j] = *var_s2;
                            }

                            Kpass = var_s2;

                            if (strncmp(Karg, "minabi", 6) == 0) {
                                kminabiflag = TRUE;
                            } else if (strncmp(Karg, "fpe", 3) == 0) {
                                addstr(&ldflags, "-Kfpe");
                            } else if (strncmp(Karg, "sd", 2) == 0) {
                                addstr(&ldflags, "-Ksd");
                            } else if (strncmp(Karg, "sz", 2) == 0) {
                                addstr(&ldflags, "-Ksz");
                            } else if (strncmp(Karg, "mau", 3) == 0) {
                                addstr(&ldflags, "-Kmau");
                            } else if (strncmp(Karg, "PIC", 3) == 0) {
                                if (non_shared) {
                                    error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                                          "Can't mix -KPIC and -non_shared, change to -non_shared\n");
                                    kpic_flag = FALSE;
                                } else {
                                    kpic_flag = TRUE;
                                    kpic_spec = TRUE;
                                }
                            } else {
                                goto bad_option;
                            }

                            for (j = 0; j < strlen(Karg); j++) {
                                Karg[j] = ' ';
                            }

                            while ((Kpass != NULL) && (*Kpass == ',') && (*Kpass != '\0')) {
                                Kpass++;
                            }
                        }
                        break;
                    }
                    if (argv[var_s0][2] != '\0') {
                        if (strcmp(argv[var_s0], "-KPIC") == 0) {
                            if (non_shared) {
                                error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                                      "Can't mix -KPIC and -non_shared, change to -non_shared\n");
                                kpic_flag = FALSE;
                            } else {
                                kpic_flag = TRUE;
                                kpic_spec = TRUE;
                            }
                            break;
                        } else {
                            addstr(&ldflags, argv[var_s0]);
                        }
                    } else {
                        Kflag++;
                        addstr(&fcomflags, argv[var_s0]);
                    }

                    break;

                case 'L': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        if (((var_s0 + 1) < argc) && (argv[var_s0 + 1][0] != '-') && isdir(argv[var_s0 + 1])) {
                            char* sp128;

                            var_s0++;
                            sp128 = mkstr(argv[var_s0 - 1], argv[var_s0], NULL);
                            addstr(&ldflags, sp128);
                            // addstr(&prelinkerflags, sp128);
                            Lflag = TRUE;
                            break;
                        } else {
                            // addstr(&prelinkerflags, mkstr("-YB", NULL));
                        }
                    }
                    Lflag = TRUE;
                    addstr(&ldflags, argv[var_s0]);
                    // addstr(&prelinkerflags, argv[var_s0]);
                    break;

                case 'M':                         /* switch 1 */
                    if (argv[var_s0][2] == 'D') { // -MD
                        if (strcmp(argv[var_s0] + 3, "update") == 0) {
                            sp15C = argv[var_s0 + 1];
                        } else if (strcmp(argv[var_s0] + 3, "ignore") == 0) {
                            addstr(&ldflags, argv[var_s0]);
                            addstr(&ldflags, argv[var_s0 + 1]);
                        } else if (strcmp(argv[var_s0] + 3, "ignoredir") == 0) {
                            addstr(&ldflags, argv[var_s0]);
                            addstr(&ldflags, argv[var_s0 + 1]);
                        } else if (strcmp(argv[var_s0] + 3, "target") == 0) {
                            if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
                                sp154 = argv[var_s0 + 1];
                            } else {
                                addstr(&cppflags, argv[var_s0]);
                                addstr(&cppflags, argv[var_s0 + 1]);
                            }
                        } else {
                            goto bad_option;
                        }
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "%s must be followed by a file name\n",
                                  argv[var_s0 - 1]);
                            exit(2);
                        }
                        break;
                    }
                    if (argv[var_s0][2] == '\0') {
                        if (1) {} // FAKE
                        addstr(&cppflags, argv[var_s0]);
                        Eflag++;
                        minus_M++;
                        break;
                    }
                    goto bad_option;

                case 'N': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    if (compiler == COMPILER_3) {
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                        break;
                    }
                    goto bad_option;

                case 'O': /* switch 1 */
                    plain_O = FALSE;
                    if (argv[var_s0][2] == '\0') {
                        //! @bug var_s1 possibly used uninitialised
                        // if (xpg_flag && (var_s1 == 'f')) {
                        //     fprintf(stderr, "Error: optlevel should be specified\n");
                        //     exit(1);
                        // }
                        Oflag = 2;
                        plain_O = TRUE;
                        if (plain_g) {
                            Oflag = 1;
                        }
                        // if (((var_s0 + 1) < argc) && (argv[var_s0 + 1][1] == '\0') && (*argv[var_s0 + 1] >= '0') &&
                        //     (*argv[var_s0 + 1] <= '4')) {
                        //     char* sp124 = malloc(strlen(argv[var_s0 + 1]) + 3);

                        //     sp124[0] = '-';
                        //     sp124[1] = 'O';
                        //     sp124[2] = 0;
                        //     Oflag = *argv[var_s0 + 1] - '0'; // '0' -> 0, '1' -> 1, etc.
                        //     addstr(&fcomflags, strcat(sp124, argv[var_s0 + 1]));
                        //     var_s0++;
                        // }
                        break;
                    }
                    if (argv[var_s0][3] == '\0') {
                        if ((argv[var_s0][2] >= '0') && (argv[var_s0][2] <= '4')) {
                            Oflag = argv[var_s0][2] - '0';
                            if (Oflag == 3) {
                                char* sp120 = "-Olimit";
                                char* sp11C = "5000";

                                Gnum = "0";
                                addstr(&umergeflags, sp120);
                                addstr(&umergeflags, sp11C);

                                addstr(&optflags, sp120);
                                addstr(&optflags, sp11C);

                                addstr(&ddoptflags, sp120);
                                addstr(&ddoptflags, sp11C);

                                addstr(&uopt0flags, sp120);
                                addstr(&uopt0flags, sp11C);

                                addstr(&olimitflags, sp120);
                                addstr(&olimitflags, sp11C);
                            }
                            if ((Oflag >= 3) && !jflag) {
                                uload = TRUE;
                            }
                            break;
                        }
                        goto bad_option;
                    }
                    if (strcmp(argv[var_s0], "-Olimit") == 0) {
                        addstr(&umergeflags, argv[var_s0]);
                        addstr(&optflags, argv[var_s0]);
                        addstr(&ddoptflags, argv[var_s0]);
                        addstr(&uopt0flags, argv[var_s0]);
                        addstr(&olimitflags, argv[var_s0]);
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-Olimit must have an argument\n");
                            exit(2);
                        }
                        for (var_s2 = argv[var_s0]; *var_s2 != 0; var_s2++) {
                            if (!isdigit(*var_s2)) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "non-digit character in -Olimit %s\n",
                                      argv[var_s0]);
                                exit(2);
                            }
                        }
                        addstr(&umergeflags, argv[var_s0]);
                        addstr(&optflags, argv[var_s0]);
                        addstr(&ddoptflags, argv[var_s0]);
                        addstr(&uopt0flags, argv[var_s0]);
                        addstr(&olimitflags, argv[var_s0]);
                        break;
                    }
                    if (strncmp(argv[var_s0], "-OPT:", 5) == 0) {
                        error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "-OPT options are ignored\n");
                        break;
                    }
                    goto bad_option;

                case 'P': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        if (1) {} // FAKE
                        docpp = TRUE;
                        addstr(&cppflags, argv[var_s0]);
                        if (!Eflag) {
                            Pflag++;
                        }
                        break;
                    }
                    goto bad_option;

                case 'Q': /* switch 1 */
                    if ((strcmp(argv[var_s0], "-Qy") != 0) && (strcmp(argv[var_s0], "-Qn") != 0)) {
                        addstr(&cppflags, argv[var_s0]);
                    }
                    break;

                case 'R': /* switch 1 */
                    if (compiler == COMPILER_3) {
                        addstr(&ratforflags, argv[var_s0] + 2);
                        add_static_opt(argv[var_s0]);
                        break;
                    }
                    goto bad_option;

                case 'S': /* switch 1 */
                    if (strncmp(argv[var_s0], "-SWP:", 5) == 0) {
                        error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "-SWP options are ignored\n");
                        break;
                    }
                    if (argv[var_s0][2] == '\0') {
                        Sflag++;
                        break;
                    }
                    goto bad_option;

                case 'T': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        var_s0++;
                        if (var_s0 < argc) {
                            addstr(&ldflags, "-T");
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        }
                        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "ld requires -T to have an argument\n");
                        exit(2);
                    }
                    if (strncmp(argv[var_s0], "-TARG:", 6) == 0) {
                        error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "-TARG options are ignored\n");
                        break;
                    }
                    if (strncmp(argv[var_s0], "-TENV:", 6) == 0) {
                        error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "-TENV options are ignored\n");
                        break;
                    }
                    goto bad_option;

                case 'U': /* switch 1 */
                    if ((compiler == COMPILER_3) && (argv[var_s0][2] == '\0')) {
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                        mp_caseflag = 1;
                        break;
                    }
                    // if ((argv[var_s0][2] == '\0') && ((var_s0 + 1) < argc)) {
                    //     char* sp118 = malloc(strlen(argv[var_s0 + 1]) + 3);

                    //     sp118[0] = '-';
                    //     sp118[1] = 'U';
                    //     sp118[2] = 0;
                    //     addstr(&undefineflags, strcat(sp118, argv[var_s0 + 1]));
                    //     var_s0++;
                    //     break;
                    // }
                    addstr(&undefineflags, argv[var_s0]);
                    add_static_opt(argv[var_s0]);
                    break;

                case 'V': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "-V is not supported.\n");
                        break;
                    }
                    if (strcmp(argv[var_s0], "-VS") == 0) {
                        var_s0++;
                        if (var_s0 < argc) {
                            addstr(&ldflags, "-VS");
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        }
                        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "ld requires -VS to have an argument\n");
                        exit(2);
                    }
                    goto bad_option;

                case 'W': /* switch 1 */
                    // Options to pass on to subsequent programs Use as -W[letter],option1,option2,...
                    Wpass = argv[var_s0] + 2;
                    if (*Wpass != '\0') {
                        if (1) {} // FAKE
                        Warg = argv[var_s0] + 3;

                        while (*Warg != ',') {
                            if (*Warg++ == '\0') {
                                goto bad_option;
                            }
                        }
                        while (*Warg == ',') {
                            *Warg = '\0';
                            Warg++;
                            for (var_s2 = Wpass; *var_s2 != '\0'; var_s2++) {
                                switch (*var_s2) { /* switch 2 */
                                    case 'p':      /* switch 2 */
                                        addstr(&cppflags, Warg);
                                        break;

                                    case 'K': /* switch 2 */
                                        if (compiler == COMPILER_3) {
                                            addstr(&pfaflags, Warg);
                                        } else if (compiler == COMPILER_1) {
                                            addstr(&pcaflags, Warg);
                                        } else {
                                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                                                  "-WK only valid in FORTRAN or C compilations.\n");
                                            exit(2);
                                        }
                                        break;

                                    case '0': /* switch 2 */
                                    case 'f': /* switch 2 */
                                        switch (compiler) {
                                            case COMPILER_2:
                                                addstr(&upasflags, Warg);
                                                break;
                                            case COMPILER_3:
                                                addstr(&fcomflags, Warg);
                                                break;
                                            case COMPILER_5:
                                                addstr(&upl1flags, Warg);
                                                break;
                                            case COMPILER_6:
                                                addstr(&ucobflags, Warg);
                                                break;
                                            default: // COMPILER_1, COMPILER_4
                                                addstr(&ccomflags, Warg);
                                                addstr(&edisonflags, Warg);
                                                break;
                                        }
                                        break;

                                    case 'w': /* switch 2 */
                                        addstr(&prelinkerflags, Warg);
                                        break;

                                    case 'k': /* switch 2 */
                                        addstr(&ulpiflags, Warg);
                                        break;

                                    case 'j': /* switch 2 */
                                        addstr(&ujoinflags, Warg);
                                        break;

                                    case 'u': /* switch 2 */
                                        addstr(&uldflags, Warg);
                                        break;

                                    case 's': /* switch 2 */
                                        addstr(&usplitflags, Warg);
                                        break;

                                    case 'm': /* switch 2 */
                                        addstr(&umergeflags, Warg);
                                        break;

                                    case 'q': /* switch 2 */
                                        addstr(&uopt0flags, Warg);
                                        break;

                                    case 'd': /* switch 2 */
                                        addstr(&ddoptflags, Warg);
                                        break;

                                    case '2': /* switch 2 */
                                        addstr(&optflags, Warg);
                                        break;

                                    case 'o': /* switch 2 */
                                        addstr(&optflags, Warg);
                                        if (strstr(Warg, "loopunroll") != NULL) {
                                            set_loop_unroll = TRUE;
                                        }
                                        break;

                                    case 'c': /* switch 2 */
                                        addstr(&genflags, Warg);
                                        break;

                                    case 'a': /* switch 2 */
                                        addstr(&asflags, Warg);
                                        break;

                                    case 'b': /* switch 2 */
                                        addstr(&asflags, Warg);
                                        break;

                                    case 'l': /* switch 2 */
                                        addstr(&ldflags, Warg);
                                        break;

                                    case 'y': /* switch 2 */
                                        addstr(&ftocflags, Warg);
                                        break;

                                    case 'z': /* switch 2 */
                                        addstr(&cordflags, Warg);
                                        break;

                                    case 'M': /* switch 2 */
                                        addstr(&mpcflags, Warg);
                                        break;

                                    case 'x':              /* switch 2 */
                                        switch (Warg[1]) { /* switch 3 */
                                            case 'G':      /* switch 3 */
                                                if (Warg[2] == '\0') {
                                                    var_s0++;
                                                    if (var_s0 >= argc) {
                                                        error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                                                              "-G requires a decimal number argument\n");
                                                        exit(2);
                                                    }
                                                    if (Oflag < 3) {
                                                        Gnum = argv[var_s0];
                                                    } else {
                                                        Gnum = "0";
                                                    }
                                                } else if (Oflag < 3) {
                                                    Gnum = Warg + 2;
                                                } else {
                                                    Gnum = "0";
                                                }
                                                for (var_s3 = Gnum; ((*var_s3 != ',') && (*var_s3 != 0));) {
                                                    if (!isdigit(*var_s3)) {
                                                        error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                                                              "non-digit character in -G %s\n", Gnum);
                                                        exit(2);
                                                    }
                                                    if (*var_s3 != ',') {
                                                        var_s3++;
                                                    }
                                                }
                                                if (!Gseen_flag) {
                                                    Gseen_flag = TRUE;
                                                    relocate_passes(tstring, hstring, NULL);
                                                }
                                                Warg = var_s3;
                                                break;

                                            case 'v': /* switch 3 */
                                                // -Wxv
                                                if ((Warg[2] == '\0') || (Warg[2] == ',')) {
                                                    vflag = TRUE;
                                                    if (getenv("ROOTDIR") != NULL) {
                                                        error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                                                              "ROOTDIR env var ignored, use COMP_TARGET_ROOT and "
                                                              "COMP_HOST_ROOT\n");
                                                    }
                                                }
                                                break;

                                            case 'D': /* switch 3 */
                                                // -WxD
                                                if (argv[var_s0][2] == '\0') {
                                                    if ((var_s0 + 1) < argc) {
                                                        unsigned long sp114;
                                                        char* sp110;

                                                        sp114 = strtoul(argv[var_s0 + 1], &sp110, 16);
                                                        if (((sp110 - argv[var_s0 + 1]) != strlen(argv[var_s0 + 1])) ||
                                                            ((sp114 == 0) && (sp110 == argv[var_s0 + 1])) ||
                                                            (*argv[var_s0 + 1] == '-') || (*argv[var_s0 + 1] == '+')) {
                                                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                                                                  "-D taken as empty cpp -D, not ld(1) -D hexnum\n");
                                                            break;
                                                        }
                                                    }

                                                    var_s0++;
                                                    if (var_s0 < argc) {
                                                        addstr(&ldflags, "-D");
                                                        addstr(&ldflags, argv[var_s0]);
                                                        break;
                                                    } else {
                                                        error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                                                              "ld requires -D to have an argument\n");
                                                        exit(2);
                                                    }
                                                }
                                                // fallthrough
                                            case 'b': /* switch 3 */
                                                if ((Warg[2] == '\0') || (Warg[2] == ',')) {
                                                    addstr(&ldflags, mkstr(argv[var_s0], ",", Warg, NULL));
                                                }
                                                break;

                                            case 'K': /* switch 3 */
                                                if (strcmp(Warg, "-K") != 0) {
                                                    addstr(&ldflags, mkstr(argv[var_s0], ",", Warg, NULL));
                                                } else {
                                                    Kflag++;
                                                }
                                                break;

                                            case 'A': /* switch 3 */
                                                if (Warg[2] == 0) {
                                                    var_s0++;
                                                    if (var_s0 < argc) {
                                                        addstr(&objfiles, "-A");
                                                    }
                                                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                                                          "ld requires -A to have an argument\n");
                                                    exit(2);
                                                }
                                                break;
                                        }
                                        break;

                                    default: /* switch 2 */
                                        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "Unknown pass character in %s\n",
                                              argv[var_s0]);
                                        exit(2);
                                        break;
                                }
                            }
                            while ((*Warg != ',') && (*Warg != '\0')) {
                                Warg++;
                            }
                        }
                        break;
                    }
                    goto bad_option;

                case 'X': /* switch 1 */
                    if (compiler == COMPILER_1) {
                        if (strcmp(argv[var_s0], "-Xcpluscomm") == 0) {
                            addstr(&ccomflags, argv[var_s0]);
                            break;
                        }
                        if (strcmp(argv[var_s0], "-Xt") == 0) {
                            stdflag = 0;
                            addstr(&ccomflags, "-std0");
                            break;
                        }
                        if (strcmp(argv[var_s0], "-Xc") == 0) {
                            stdflag = 1;
                            addstr(&ccomflags, "-std1");
                            break;
                        }
                        if (strcmp(argv[var_s0], "-Xa") == 0) {
                            stdflag = 1;
                            addstr(&ccomflags, "-std");
                            break;
                        }
                    }
                    if (strcmp(argv[var_s0], "-Xprototypes") == 0) {
                        addstr(&ccomflags, argv[var_s0]);
                        break;
                    }
                    addstr(&ldflags, argv[var_s0]);
                    if ((strcmp(argv[var_s0], "-Xndlocaldata") == 0) || (strcmp(argv[var_s0], "-Xlocaldata") == 0) ||
                        (strcmp(argv[var_s0], "-Xndblock") == 0) || (strcmp(argv[var_s0], "-Xblock") == 0) ||
                        (strcmp(argv[var_s0], "-Xalignbss") == 0) || (strcmp(argv[var_s0], "-Xnoalignbss") == 0) ||
                        (strcmp(argv[var_s0], "-Xcachesize") == 0) || (strcmp(argv[var_s0], "-Xcachelinesize") == 0) ||
                        (strcmp(argv[var_s0], "-Xdefmovemax") == 0) || (strcmp(argv[var_s0], "-Xsetalign") == 0) ||
                        (strcmp(argv[var_s0], "-Xblockrange") == 0)) {
                        var_s0++;
                        if (var_s0 < argc) {
                            addstr(&ldflags, argv[var_s0]);
                        } else {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "%s must have an argument\n", argv[var_s0 - 1]);
                        }
                    }
                    break;

                case 'a': /* switch 1 */
                    if ((compiler == COMPILER_1) && (strcmp(argv[var_s0], "-all") == 0)) {
                        addstr(&objfiles, argv[var_s0]);
                        break;
                    }
                    if ((compiler == COMPILER_1) &&
                        ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                        (strcmp(argv[var_s0], "-auto_include") == 0)) {
                        auto_template_include = TRUE;
                        break;
                    }
                    // if ((compiler == COMPILER_1) &&
                    //     ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                    //     (strcmp(argv[var_s0], "-anach") == 0)) {
                    //     anachronisms = TRUE;
                    //     break;
                    // }
                    if (strcmp(argv[var_s0], "-ansi") == 0) {
                        if (compchoice == COMP_CHOICE_1) {
                            compchoice = COMP_CHOICE_0;
                        }
                        ansichoice = ANSICHOICE_ANSI;
                        if (cppchoice != CPP_CHOICE_1) {
                            cppchoice = CPP_CHOICE_3;
                        }
                        relocate_passes("p", NULL, NULL);
                        add_static_opt(argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-ansiposix") == 0) {
                        if (compchoice == COMP_CHOICE_1) {
                            compchoice = COMP_CHOICE_0;
                        }
                        ansichoice = ANSICHOICE_ANSIPOSIX;
                        if (cppchoice != CPP_CHOICE_1) {
                            cppchoice = CPP_CHOICE_3;
                        }
                        relocate_passes("p", NULL, NULL);
                        add_static_opt(argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-abi") == 0) {
                        abi_flag = 1;
                        addstr(&cppflags, "-D_ABI_SOURCE");
                        addstr(&asflags, "-abi");
                        addstr(&ldflags, "-abi");
                        break;
                    }
                    if (strcmp(argv[var_s0], "-acpp") == 0) {
                        if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n",
                                  argv[var_s0], "");
                        } else {
                            cppchoice = CPP_CHOICE_1;
                            acpp = TRUE;
                            relocate_passes("p", NULL, NULL);
                        }
                        break;
                    }
                    if (strcmp(argv[var_s0], "-align8") == 0) {
                        align = 8;
                        if (compiler == COMPILER_3) {
                            align_common++;
                        }
                    } else if (strcmp(argv[var_s0], "-align16") == 0) {
                        align = 0x10;
                        if (compiler == COMPILER_3) {
                            align_common++;
                        }
                    } else if (strcmp(argv[var_s0], "-align32") == 0) {
                        align = 0x20;
                        if (compiler == COMPILER_3) {
                            align_common++;
                        }
                    } else if (strcmp(argv[var_s0], "-align64") == 0) {
                        align = 0x40;
                        if (compiler == COMPILER_3) {
                            align_common++;
                        }
                    } else if (strcmp(argv[var_s0], "-align_common") == 0) {
                        align_common = 1;
                        break;
                    }
                    if (compiler == COMPILER_3) {
                        if ((strcmp(argv[var_s0], "-align8") == 0) || (strcmp(argv[var_s0], "-align16") == 0) ||
                            (strcmp(argv[var_s0], "-align32") == 0) || (strcmp(argv[var_s0], "-align64") == 0)) {
                            addstr(&fcomflags, argv[var_s0]);
                            addstr(&genflags, argv[var_s0]);
                            addstr(&asflags, argv[var_s0]);
                            break;
                        }
                        if (strcmp(argv[var_s0], "-automatic") == 0) {
                            automaticflag = TRUE;
                            break;
                        }
                    }
                    if ((compiler == COMPILER_6) && (strcmp(argv[var_s0], "-ansi") == 0)) {
                        ansiflag = TRUE;
                        break;
                    }
                    if ((compiler == COMPILER_2) && (strcmp(argv[var_s0], "-apc") == 0)) {
                        addstr(&upasflags, argv[var_s0]);
                        addstr(&genflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-align8") == 0) {
                        align = 8;
                        alignarg = savestr(argv[var_s0], 0);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-align16") == 0) {
                        align = 0x10;
                        alignarg = savestr(argv[var_s0], 0);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-align32") == 0) {
                        align = 0x20;
                        alignarg = savestr(argv[var_s0], 0);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-align64") == 0) {
                        align = 0x40;
                        alignarg = savestr(argv[var_s0], 0);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-ajeop") == 0) {
                        addstr(&ldflags, argv[var_s0]);
                        addstr(&cordflags, "-no_r4000_fix");
                        break;
                    }
                    goto bad_option;

                case 'b': /* switch 1 */
                    if ((argv[var_s0][2] == '\0') || (strcmp(argv[var_s0], "-bestGnum") == 0)) {
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-bytereclen") == 0) {
                        addstr(&fcomflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-backslash") == 0) {
                        mp_backslashflag = 1;
                        // docpp = 0;
                    }
                    addstr(&fcomflags, argv[var_s0]);
                    add_static_opt(argv[var_s0]);
                    break;

                case 'c': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        cflag++;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-cckr") == 0) {
                        ansichoice = ANSICHOICE_KR;
                        if (cppchoice != CPP_CHOICE_1) {
                            cppchoice = CPP_CHOICE_2;
                        }
                        add_static_opt(argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-cfe") == 0) {
                        if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n",
                                  argv[var_s0], "");
                        } else {
                            compchoice = COMP_CHOICE_3;
                            relocate_passes("p", NULL, NULL);
                        }
                        break;
                    }
                    if (strcmp(argv[var_s0], "-common") == 0) {
                        if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n",
                                  argv[var_s0], "");
                        } else {
                            addstr(&accomflags, "-Xcommon");
                        }
                        break;
                    }
                    // if ((compiler == COMPILER_1) &&
                    //     ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                    //     (strcmp(argv[var_s0], "-cfront") == 0)) {
                    //     cfront_compatible = TRUE;
                    //     break;
                    // }
                    if (strcmp(argv[var_s0], "-cachesz") == 0) {
                        addstr(&ddoptflags, argv[var_s0]);
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-cachesz must have an argument\n");
                            exit(2);
                        }

                        for (var_s2 = Gnum; *var_s2 != 0; var_s2++) {
                            if (!isdigit(*var_s2)) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "non-digit character in -G %s\n", argv[var_s0]);
                                exit(2);
                            }
                        }

                        addstr(&ddoptflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-cplus") == 0) {
                        cplusflag = TRUE;
                        addstr(&ccomflags, "-cplus");
                        break;
                    }
                    if (strcmp(argv[var_s0], "-cpp") == 0) {
                        error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "-cpp is default\n");
                        break;
                    }
                    if (strcmp(argv[var_s0], "-cord") == 0) {
                        cordflag = TRUE;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-coff") == 0) {
                        addstr(&ldflags, argv[var_s0]);
                        coff_spec = TRUE;
                        if (default_call_shared == TRUE) {
                            if (!non_shared) {
                                old_non_shared = TRUE;
                                non_shared = TRUE;
                            }
                            default_call_shared = FALSE;
                            call_shared = FALSE;
                        }
                        break;
                    }
                    //! @bug Impossible to satisfy this conditional
                    if ((strcmp(argv[var_s0], "-call_shared") == 0) &&
                        ((strcmp(argv[var_s0], "-count") == 0) || (strcmp(argv[var_s0], "-countall") == 0))) {
                        addstr(&objfiles, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-call_shared") == 0) {
                        non_shared = FALSE;
                        call_shared = TRUE;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-crt0") == 0) {
                        CRTX = "crt0.o";
                        MCRTX = "mcrt0.o";
                        crtn_required = FALSE;
                        relocate_passes("r", NULL, NULL);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-crt1") == 0) {
                        if ((ansichoice == ANSICHOICE_ANSI) || (ansichoice == ANSICHOICE_ANSIPOSIX)) {
                            CRTX = "acrt1.o";
                        } else {
                            CRTX = "crt1.o";
                        }
                        MCRTX = "mcrt1.o";
                        crtn_required = TRUE;
                        relocate_passes("r", NULL, NULL);
                        break;
                    }
                    if ((compiler == COMPILER_2) && (strcmp(argv[var_s0], "-casesense") == 0)) {
                        addstr(&upasflags, argv[var_s0]);
                        break;
                    }
                    if ((compiler == COMPILER_3) && (strcmp(argv[var_s0], "-change_const") == 0)) {
                        addstr(&fcomflags, "-change_const");
                        break;
                    }
                    if ((compiler == COMPILER_3) &&
                        ((strcmp(argv[var_s0], "-col120") == 0) || (strcmp(argv[var_s0], "-col72") == 0) ||
                         (strcmp(argv[var_s0], "-charargv") == 0) || (strcmp(argv[var_s0], "-chunk") == 0) ||
                         (strcmp(argv[var_s0], "-check_bounds") == 0))) {
                        if (strcmp(argv[var_s0], "-col120") == 0) {
                            mp_col120flag = TRUE;
                        }
                        if (strcmp(argv[var_s0], "-check_bounds") == 0) {
                            addstr(&fcomflags, "-C");
                        } else if (strncmp(argv[var_s0], "-chunk=", strlen("-chunk=")) == 0) {
                            char* sp10C = argv[var_s0] + strlen("-chunk=");

                            while (*sp10C != '\0') {
                                *sp10C = TO_LOWER(*sp10C);
                                sp10C++;
                            }
                            addstr(&fcomflags, mkstr("-mp_chunk=", argv[var_s0] + strlen("-chunk="), NULL));
                        } else {
                            addstr(&fcomflags, argv[var_s0]);
                            if (strncmp(argv[var_s0], "-col", 4) == 0) {
                                add_static_opt(argv[var_s0]);
                            }
                        }
                        break;
                    }
                    if ((compiler == COMPILER_6) && (strcmp(argv[var_s0], "-comp_trunc") == 0)) {
                        addstr(&ucobflags, argv[var_s0]);
                        break;
                    }
                    if ((compiler == COMPILER_1) && (strcmp(argv[var_s0], "-check_registry") == 0)) {
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-check_registry requires a filename argument\n");
                            exit(2);
                        }
                        addstr(&ldflags, argv[var_s0 - 1]);
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    goto bad_option;

                case 'd': /* switch 1 */
                    if ((compiler == COMPILER_1) && (strcmp(argv[var_s0], "-dollar") == 0)) {
                        addstr(&pcaflags, "-dollar");
                        addstr(&mpcflags, "-dollar");
                        addstr(&soptflags, "-dollar");
                        addstr(&cfeflags, "-Xdollar");
                        add_static_opt(argv[var_s0]);
                        dollar_sign++;
                        break;
                    }
                    if (argv[var_s0][2] == '\0') {
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-ddoptinfo") == 0) {
                        ddoptinfo = TRUE;
                        break;
                    }
                    if ((strcmp(argv[var_s0], "-dy") == 0) || (strcmp(argv[var_s0], "-dn") == 0)) {
                        if (G_flag) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-dn can not be used with -G \n");
                            exit(2);
                        }
                        dn_flag = TRUE;
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-ddopt") == 0) {
                        ddoptflag = TRUE;
                        break;
                    }
                    if ((compiler == COMPILER_3) && (strcmp(argv[var_s0], "-d_lines") == 0)) {
                        mp_dlinesflag = TRUE;
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                        break;
                    }
                    if ((compiler == COMPILER_5) && (strcmp(argv[var_s0], "-defext") == 0)) {
                        addstr(&ulpiflags, argv[var_s0]);
                        break;
                    }
                    if ((compiler == COMPILER_6) &&
                        ((strcmp(argv[var_s0], "-dline") == 0) || (strcmp(argv[var_s0], "-defext") == 0))) {
                        addstr(&ucobflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-delay_load") == 0) {
                        addstr(&objfiles, argv[var_s0]);
                        break;
                    }
                    if ((compiler == COMPILER_1) && (strcmp(argv[var_s0], "-default_delay_load") == 0)) {
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    goto bad_option;

                case 'e': /* switch 1 */
                    if (strcmp(argv[var_s0], "-excpt") == 0) {
                        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-excpt is not supported in svr4 env.\n");
                        exit(2);
                    }
                    if (compiler == COMPILER_1) {
                        if (strcmp(argv[var_s0], "-elf") == 0) {
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        }
                        if ((strcmp(argv[var_s0], "-export") == 0) || (strcmp(argv[var_s0], "-exports") == 0)) {
                            addstr(&objfiles, argv[var_s0]);
                            break;
                        }
                        if (strcmp(argv[var_s0], "-exported_symbol") == 0) {
                            var_s0++;
                            if ((var_s0 >= argc) || (argv[var_s0][0] == '-')) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                                      "-exported_symbol requires a symbol argument\n");
                                exit(2);
                            }
                            addstr(&ldflags, argv[var_s0 - 1]);
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        }
                        if (strcmp(argv[var_s0], "-exports_file") == 0) {
                            var_s0++;
                            if ((var_s0 >= argc) || (argv[var_s0][0] == '-')) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-exports_file requires a filename argument\n");
                                exit(2);
                            }
                            addstr(&ldflags, argv[var_s0 - 1]);
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        }
                        if (strcmp(argv[var_s0], "-exclude") == 0) {
                            var_s0++;
                            if ((var_s0 >= argc) || (argv[var_s0][0] == '-')) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-exclude requires a filename argument\n");
                                exit(2);
                            }
                            addstr(&objfiles, argv[var_s0 - 1]);
                            addstr(&objfiles, argv[var_s0]);
                            break;
                        }
                        // if ((compiler == COMPILER_1) &&
                        //     ((c_compiler_choice == C_COMPILER_CHOICE_2) ||
                        //      (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                        //     (strcmp(argv[var_s0], "-exceptions") == 0)) {
                        //     if ((compiler != COMPILER_1) || (c_compiler_choice != C_COMPILER_CHOICE_3)) {
                        //         exception_handling = TRUE;
                        //         relocate_passes("f", NULL, NULL);
                        //         if (access(cfe, EX_OK) == -1) {
                        //             exception_handling = FALSE;
                        //             relocate_passes("f", NULL, NULL);
                        //         } else {
                        //             break;
                        //         }
                        //     }
                        //     goto bad_option;
                        // }
                    }

                    if (argv[var_s0][2] == '\0') {
                        var_s0++;
                        if (var_s0 < argc) {
                            addstr(&ldflags, "-e");
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        } else {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "ld requires -e to have an argument\n");
                            exit(2);
                        }
                    }

                    if (strcmp(argv[var_s0], "-exact_version") == 0) {
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-elf") == 0) {
                        elfflag = TRUE;
                        elf_spec = TRUE;
                        addstr(&asflags, argv[var_s0]);
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    if ((compiler == COMPILER_3) && (strcmp(argv[var_s0], "-extend_source") == 0)) {
                        mp_extendflag = 1;
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                        break;
                    }
                    if ((compiler == COMPILER_3) && (strcmp(argv[var_s0], "-expand_include") == 0)) {
                        addstr(&fcomflags, argv[var_s0]);
                        break;
                    }
                    if (strncmp(argv[var_s0], "-edit", 5) == 0) {
                        pid_t sp108; // process group id

                        if (argv[var_s0][5] == '\0') {
                            edit_cnt_max = 0x100;
                        } else if (isdigit(argv[var_s0][5]) && (argv[var_s0][6] == '\0')) {
                            edit_cnt_max = argv[var_s0][5] - '0';
                        } else {
                            //! @remark typo of "syntax"
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "the correct -edit option sybtax is -edit[0-9]\n");
                            exit(2);
                        }
                        editflag = EDIT_FLAG_1;
                        editor = getenv("EDITOR");
                        if (editor != NULL) {
                            for (var_s2 = editor; strlen(var_s2) >= 5; var_s2++) {
                                if (strncmp(var_s2, "emacs", 5) == 0) {
                                    editflag = EDIT_FLAG_2;
                                    break;
                                }
                            }
                        }
                        if ((editflag == EDIT_FLAG_1) && (editor == NULL)) {
                            editor = "vi";
                        }

                        xserver = getenv("DISPLAY");
                        if ((ioctl(2, TIOCGPGRP, &sp108) == 0) && (getpgrp() == sp108) && (xserver == 0)) {
                            editflag = EDIT_FLAG_0;
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                                  "%s ignored for background compile in non-X environment\n", argv[var_s0]);
                        }
                        break;
                    }
                    goto bad_option;

                case 'f': /* switch 1 */
                          // Accounts for a misspelling?
                    if ((strcmp(argv[var_s0], "-full_transtive_link") == 0)
                        // || (strcmp(argv[var_s0], "-full_transitive_link") == 0)
                    ) {
                        full_transitive_link = TRUE;
                        transitive_link = FALSE;
                        no_transitive_link = FALSE;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-feedback") == 0) {
                        var_s0++;
                        if (var_s0 < argc) {
                            addstr(&feedlist, argv[var_s0]);
                            break;
                        } else {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-feedback must have an argument\n");
                            exit(2);
                        }
                    }

                    if (strcmp(argv[var_s0], "-fullasopt") == 0) {
                        fullasoptflag = 1;
                        break;
                    }
                    if ((compiler == COMPILER_1) && (strcmp(argv[var_s0], "-force_load") == 0)) {
                        addstr(&objfiles, argv[var_s0]);
                        break;
                    }
                    if ((strcmp(argv[var_s0], "-fullwarn") == 0) && (fullwarn = TRUE, (compiler == COMPILER_1))) {
                        addstr(&accomflags, "-Xfullwarn");
                        addstr(&cfeflags, "-verbose");
                        addstr(&cfeflags, "-wimplicit");
                        break;
                    }
                    if (strcmp(argv[var_s0], "-framepointer") == 0) {
                        if (compiler == COMPILER_1) {
                            addstr(&ccomflags, argv[var_s0]);
                            break;
                        }
                        if (compiler == COMPILER_2) {
                            addstr(&upasflags, argv[var_s0]);
                            break;
                        }
                        if (compiler == COMPILER_3) {
                            addstr(&fcomflags, argv[var_s0]);
                            break;
                        }
                        goto bad_option;
                    }

                    if ((compiler == COMPILER_1) && (strcmp(argv[var_s0], "-float") == 0)) {
                        addstr(&pcaflags, "-float");
                        addstr(&soptflags, "-float");
                        addstr(&ccomflags, "-Xfloat");
                        break;
                    }
                    if (((compiler == COMPILER_4) || (compiler == COMPILER_2)) &&
                        (strcmp(argv[var_s0], "-float") == 0)) {
                        break;
                    }
                    if (compiler == COMPILER_6) {
                        if (strcmp(argv[var_s0], "-fsc74") == 0) {
                            addstr(&ucobflags, argv[var_s0]);
                            break;
                        }
                        if (argv[var_s0][2] == '\0') {
                            var_s0++;
                            if ((var_s0 < argc) && (addstr(&ucobflags, "-f"), (argv[var_s0][1] == '\0')) &&
                                (argv[var_s0][0] >= '1') && (argv[var_s0][0] <= '4')) {
                                addstr(&ucobflags, argv[var_s0]);
                                break;
                            } else {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-f requires an argument of 1, 2, 3 or 4\n");
                                exit(2);
                            }
                        } else {
                            goto bad_option;
                        }
                    }
                    if (argv[var_s0][2] == '\0') {
                        var_s0++;
                        if (var_s0 < argc) {
                            addstr(&ldflags, "-f");
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        }
                        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "ld requires -f to have an argument\n");
                        exit(2);
                    }
                    goto bad_option;

                case 'g': /* switch 1 */
                    plain_g = FALSE;
                    // "-g" , which is converted to "-g2 -O1"
                    if (argv[var_s0][2] == '\0') {
                        gflag = 2;
                        plain_g = TRUE;
                        if (plain_O) {
                            Oflag = 1;
                        }
                        break;
                    }
                    // "-gN" for N in 0,1,2,3
                    if ((argv[var_s0][3] == '\0') && (argv[var_s0][2] >= '0') && (argv[var_s0][2] <= '3')) {
                        gflag = argv[var_s0][2] - '0';
                        if (gflag == 2) {
                            plain_g = TRUE;
                            if (plain_O) {
                                Oflag = 1;
                            }
                        }
                        break;
                    }
                    goto bad_option;

                case 'h': /* switch 1 */
                    if (strcmp(argv[var_s0], "-hostcache") == 0) {
                        addstr(&ddoptflags, argv[var_s0]);
                        break;
                    }
                    if (strncmp(argv[var_s0], "-help", 5) == 0) {
                        error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "-help is ignored.\n");
                        break;
                    }
                    if (compiler == COMPILER_1) {
                        if (strcmp(argv[var_s0], "-hides") == 0) {
                            addstr(&objfiles, argv[var_s0]);
                            break;
                        }
                        if (strcmp(argv[var_s0], "-hidden_symbol") == 0) {
                            var_s0++;
                            if ((var_s0 >= argc) || (argv[var_s0][0] == '-')) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-hidden_symbol requires a symbol argument\n");
                                exit(2);
                            }
                            addstr(&ldflags, argv[var_s0 - 1]);
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        }
                        if (strcmp(argv[var_s0], "-hides_file") == 0) {
                            var_s0++;
                            if ((var_s0 >= argc) || (argv[var_s0][0] == '-')) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-hides_file requires a filename argument\n");
                                exit(2);
                            }
                            addstr(&ldflags, argv[var_s0 - 1]);
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        }
                    }
                    hstring = argv[var_s0] + 2;
                    if (hstring[strlen(hstring) - 1] != '/') {
                        hstring = mkstr(hstring, "/", NULL);
                    }
                    break;

                case 'i': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        var_s0++;
                        if (var_s0 < argc) {
                            addstr(&ldflags, "-i");
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        } else {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "ld requires -i to have an argument\n");
                            exit(2);
                        }
                    }

                    if (strcmp(argv[var_s0], "-inline_to") == 0) {
                        addstr(&umergeflags, argv[var_s0]);
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-inline_to must have an argument\n");
                            exit(2);
                        }
                        for (var_s2 = Gnum; *var_s2 != 0; var_s2++) {
                            if (!isdigit(*var_s2)) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "non-digit character in -G %s\n", argv[var_s0]);
                                exit(2);
                            }
                        }
                        addstr(&umergeflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-ignore_unresolved") == 0) {
                        ignore_unresolved_flag = TRUE;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-ignore_minor") == 0) {
                        addstr(&objfiles, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-irix4") == 0) {
                        irix4 = TRUE;
                        comp_host_root = "/usr/irix4/";
                        Gnum = "8";
                        systype = "";
                        elfflag = FALSE;
                        svr4_systype = FALSE;
                        kpic_flag = FALSE;
                        default_call_shared = FALSE;
                        call_shared = FALSE;
                        non_shared = FALSE;
                        old_non_shared = FALSE;
                        mips_abi = MIPS_ABI_0;
                        relocate_passes("pKfjrsulmvocabtyz", NULL, NULL);
                        add_static_opt(argv[var_s0]);
                        break;
                    }
                    if (((compiler == COMPILER_3) &&
                         ((strcmp(argv[var_s0], "-i2") == 0) || (strcmp(argv[var_s0], "-i4") == 0))) ||
                        (strcmp(argv[var_s0], "-i8") == 0)) {
                        if ((argv[var_s0][2] == '2') || (argv[var_s0][2] == '8')) {
                            mp_i2flag = TRUE;
                        }
                        addstr(&fcomflags, argv[var_s0]);
                        break;
                    }
                    if (compiler == COMPILER_5) {
                        if (strcmp(argv[var_s0], "-ipath") == 0) {
                            var_s0++;
                            if (var_s0 < argc) {
                                addstr(&upl1flags, "-ipath");
                                addstr(&upl1flags, argv[var_s0]);
                                break;
                            } else {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-ipath must have an argument\n");
                                exit(2);
                            }
                        }
                        if (strcmp(argv[var_s0], "-isuffix") == 0) {
                            var_s0++;
                            if (var_s0 < argc) {
                                addstr(&upl1flags, "-isuffix");
                                addstr(&upl1flags, argv[var_s0]);
                                break;
                            } else {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-isuffix must have an argument\n");
                                exit(2);
                            }
                        }
                    }
                    goto bad_option;

                case 'j': /* switch 1 */
                          // "-j"
                    if (argv[var_s0][2] == '\0') {
                        jflag++;
                        uload = FALSE;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-jalr") == 0) {
                        addstr(&genflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-jmpopt") == 0) {
                        addstr(&objfiles, argv[var_s0]);
                        break;
                    }
                    goto bad_option;

                case 'k': /* switch 1 */
                    // if (strcmp(argv[var_s0], "-keep") == 0) {
                    //     Kflag++;
                    //     break;
                    // }
                    if (strcmp(argv[var_s0], "-kpicopt") == 0) {
                        kpicopt_flag = TRUE;
                        break;
                    }
                    switch (argv[var_s0][2]) { /* switch 7; irregular */
                        case 'o':              /* switch 7 */
                            var_s0++;
                            if (var_s0 < argc) {
                                uoutfile = argv[var_s0];
                                var_s1 = getsuf(uoutfile);
                                if ((var_s1 == 'c') || (var_s1 == 'p') || (var_s1 == 'f') || (var_s1 == 'F') ||
                                    (var_s1 == 'r') || (var_s1 == 'e') || (var_s1 == 6) || (var_s1 == 's') ||
                                    (var_s1 == 1) || (var_s1 == 2)) {
                                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-ko would overwrite %s\n", argv[var_s0]);
                                    exit(2);
                                }
                            }
                            break;

                        case 'p': /* switch 7 */
                            var_s0++;
                            if (var_s0 < argc) {
                                addstr(&uldflags, "-kp");
                                addstr(&uldflags, argv[var_s0]);
                            }
                            break;

                        case 'u': /* switch 7 */
                            var_s0++;
                            if (var_s0 < argc) {
                                addstr(&uldflags, "-ku");
                                addstr(&uldflags, argv[var_s0]);
                            }
                            break;

                        default: /* switch 7 */
                            addstr(&ufiles, argv[var_s0]);
                            break;
                    }
                    break;

                case 'l': /* switch 1 */
                    if (strcmp("isting", argv[var_s0] + 2) == 0) {
                        addstr(&fcomflags, argv[var_s0]);
                    } else {
                        if ((argv[var_s0][2] == 'm') && (argv[var_s0][3] == '\0')) {
                            lmflag++;
                        }
                        // else if ((argv[var_s0][2] == '\0') && ((var_s0 + 1) < argc)) {
                        //     char* sp104 = malloc(strlen(argv[var_s0 + 1]) + 3);

                        //     sp104[0] = '-';
                        //     sp104[1] = 'l';
                        //     sp104[2] = '\0';
                        //     if (xpg_flag) {
                        //         addstr(&dashlfiles, strcat(sp104, argv[var_s0 + 1]));
                        //     } else {
                        //         addstr(&objfiles, strcat(sp104, argv[var_s0 + 1]));
                        //     }
                        //     var_s0++;
                        //     break;
                        // }
                        // if (xpg_flag) {
                        //     addstr(&dashlfiles, argv[var_s0]);
                        // } else {
                        addstr(&objfiles, argv[var_s0]);
                        // }
                        if (strcmp(argv[var_s0], "-lgl_s") == 0) {
                            B_1000A56C++;
                            addstr(&objfiles, "-lX11_s");
                        }
                        if (strcmp(argv[var_s0], "-lc_s") == 0) {
                            B_1000A570++;
                        }
                    }
                    break;

                case 'm': /* switch 1 */
                    // if (strcmp(argv[var_s0], "-multigot") == 0) {
                    //     addstr(&nldflags, argv[var_s0]);
                    //     break;
                    // }
                    if ((compiler == COMPILER_1) && (strcmp(argv[var_s0], "-mp") == 0)) {
                        cmp_flag |= 0x10008;
                        if (Bflag) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "'-mp' must preceed any -B flags.\n");
                            exit(2);
                        }
                        relocate_passes("fY", NULL, NULL);
                        break;
                    }
                    if (argv[var_s0][2] == '\0') {
                        if ((compiler == COMPILER_4) || (compiler == COMPILER_3)) {
                            mflag++;
                        } else {
                            addstr(&ldflags, argv[var_s0]);
                        }
                        if (compiler == COMPILER_3) {
                            add_static_opt(argv[var_s0]);
                        }
                        break;
                    }
                    if (compiler == COMPILER_6) {
                        if (strcmp(argv[var_s0], "-mfext") == 0) {
                            addstr(&ucobflags, argv[var_s0]);
                            break;
                        }
                        if (strcmp(argv[var_s0], "-map") == 0) {
                            addstr(&ucobflags, argv[var_s0]);
                            break;
                        }
                    }
                    if (strcmp(argv[var_s0], "-mips1") == 0) {
                        chip_targ = CHIP_TARGET_MIPS1;
                        // mips1flag = TRUE;
                        // mips2flag = FALSE;
                        if (dwopcodeflag) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't mix -mips1 with -dwopcode\n");
                            exit(2);
                        }
                        mips1_spec_flag = TRUE;
                        // if (mips2_spec_flag) {
                        //     error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                        //           "-mips1 conflicts with -mips2; using last value (mips1)\n");
                        //     mips2_spec_flag = FALSE;
                        // }
                        break;
                    }
                    if (strcmp(argv[var_s0], "-mips2") == 0) {
                        mips1flag = FALSE;
                        mips2flag = TRUE;
                        if (mips1_spec_flag || mips3flag) {
                            // error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                            //       "-mips2 conflicts with -mips1; using last value (mips2)\n");
                            error(ERRORCAT_ERROR, 0, 0, 0, 0, "can't mix -mips2 with -mips[1,3]\n");
                            exit(2);
                        }
                        // mips2_spec_flag = TRUE;
                        relocate_passes("M", NULL, NULL);

                        addstr(&ccomflags, argv[var_s0]);
                        addstr(&upasflags, argv[var_s0]);
                        addstr(&fcomflags, argv[var_s0]);
                        addstr(&upl1flags, argv[var_s0]);
                        addstr(&ucobflags, argv[var_s0]);
                        addstr(&ulpiflags, argv[var_s0]);
                        addstr(&eflflags, argv[var_s0]);
                        addstr(&ratforflags, argv[var_s0]);
                        addstr(&ujoinflags, argv[var_s0]);
                        addstr(&usplitflags, argv[var_s0]);
                        addstr(&umergeflags, argv[var_s0]);
                        addstr(&uloopflags, argv[var_s0]);
                        addstr(&optflags, argv[var_s0]);
                        addstr(&genflags, argv[var_s0]);
                        addstr(&asflags, argv[var_s0]);
                        addstr(&ldflags, argv[var_s0]);
                        addstr(&ftocflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-mips3") == 0) {
                        mips1flag = FALSE;
                        // mips2flag = FALSE;
                        // if (mips2_spec_flag) {
                        if (mips1_spec_flag || mips2flag) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't mix -mips3 with -mips[1,2]\n");
                            exit(2);
                        }
                        if ((compiler == COMPILER_4) || (compiler == COMPILER_1)) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                                  "-mips3 should not be used for ucode 32-bit compiles\n");
                        } else {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                                  "-mips3 cannot be used for ucode 32-bit compiles\n");
                            exit(2);
                        }
                        chip_targ = CHIP_TARGET_MIPS3;
                        mips3flag = TRUE;
                        dwopcodeflag = TRUE;
                        relocate_passes("M", NULL, NULL);
                        if (!non_shared_emitted) {
                            addstr(&ldflags, "-non_shared");
                            addstr(&cfeflags, "-non_shared");
                            non_shared_emitted = TRUE;
                        }
                        addstr(&ccomflags, argv[var_s0]);
                        addstr(&upasflags, argv[var_s0]);
                        addstr(&fcomflags, argv[var_s0]);
                        addstr(&upl1flags, argv[var_s0]);
                        addstr(&ucobflags, argv[var_s0]);
                        addstr(&ulpiflags, argv[var_s0]);
                        addstr(&eflflags, argv[var_s0]);
                        addstr(&ratforflags, argv[var_s0]);
                        addstr(&ddoptflags, argv[var_s0]);
                        addstr(&optflags, argv[var_s0]);
                        addstr(&genflags, argv[var_s0]);
                        addstr(&asflags, argv[var_s0]);
                        addstr(&ldflags, argv[var_s0]);
                        addstr(&ftocflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-mips4") == 0) {
                        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-mips4 cannot be used for ucode 32-bit compiles\n");
                        exit(2);
                    }
                    if (compiler == COMPILER_3) {
                        if ((argv[var_s0][2] == 'p') && (argv[var_s0][3] == '\0')) {
                            mp_flag |= 0x10000;
                            break;
                        }
                        if (strncmp(argv[var_s0], "-mp_keep", strlen("-mp_keep")) == 0) {
                            if (argv[var_s0][8] != '\0') {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, " Unknown flag: %s\n", argv[var_s0]);
                                exit(2);
                            }
                            mp_flag |= 0x10000;
                            showdirt_flag = TRUE;
                            break;
                        }
                        if (strncmp(argv[var_s0], "-mp_schedtype=", strlen("-mp_schedtype=")) == 0) {
                            char* sp100 = argv[var_s0] + strlen("-mp_schedtype=");

                            while (*sp100 != 0) {
                                *sp100 = TO_LOWER(*sp100);
                                sp100++;
                            }
                            addstr(&fcomflags, argv[var_s0]);
                            break;
                        }
                    }
                    goto bad_option;

                case 'n': /* switch 1 */
                    if (strcmp(argv[var_s0], "-nokpicopt") == 0) {
                        nokpicopt_flag = TRUE;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-no_unresolved") == 0) {
                        no_unresolved_flag = TRUE;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-no_transitive_link") == 0) {
                        transitive_link = FALSE;
                        full_transitive_link = FALSE;
                        no_transitive_link = TRUE;
                        break;
                    }
                    // if ((compiler == COMPILER_1) &&
                    //     ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                    //     (strcmp(argv[var_s0], "-no_exceptions") == 0)) {
                    //     if ((compiler != COMPILER_1) || (c_compiler_choice != C_COMPILER_CHOICE_3)) {
                    //         exception_handling = FALSE;
                    //         relocate_passes("f", NULL, NULL);
                    //         break;
                    //     }
                    //     goto bad_option;
                    // }
                    // if (strcmp(argv[var_s0], "-new_ld") == 0) {
                    //     if (D_1000BF94) {
                    //         error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "malformed or unknown option: -new_ld\n");
                    //         exit(2);
                    //     } else if ((compiler == COMPILER_1) && (c_compiler_choice == C_COMPILER_CHOICE_3)) {
                    //         error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-new_ld not supported for DCC\n");
                    //         exit(2);
                    //     } else {
                    //         LD = "ld";
                    //         D_1000BF90 = FALSE;
                    //     }
                    //     relocate_passes("l", NULL, NULL);
                    //     break;
                    // }
                    if (strcmp(argv[var_s0], "-noinline") == 0) {
                        addstr(&umergeflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-nouopt0") == 0) {
                        uopt0flag = FALSE;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-noaliasok") == 0) {
                        noaliasokflag = TRUE;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-nostdinc") == 0) {
                        emptyIflag = TRUE;
                        add_static_opt(argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-nostdlib") == 0) {
                        addstr(&ldflags, argv[var_s0]);
                        // addstr(&prelinkerflags, mkstr("-YB", NULL));
                        break;
                    }
                    // if (strcmp(argv[var_s0], "-nodeflib") == 0) {
                    //     nodeflib = TRUE;
                    //     break;
                    // }
                    if (strcmp(argv[var_s0], "-noprototypes") == 0) {
                        prototype_checking_on = FALSE;
                        break;
                    }
                    if ((argv[var_s0][2] == '\0') || (strcmp(argv[var_s0], "-nocount") == 0) ||
                        (strcmp(argv[var_s0], "-nN") == 0) || (strcmp(argv[var_s0], "-nojmpopt") == 0)) {
                        addstr(&objfiles, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-non_shared") == 0) {
                        old_non_shared = FALSE;
                        non_shared = TRUE;
                        default_call_shared = FALSE;
                        call_shared = FALSE;
                        kpic_flag = FALSE;
                        if (!non_shared_emitted) {
                            addstr(&ldflags, "-non_shared");
                            addstr(&cfeflags, "-non_shared");
                            non_shared_emitted = TRUE;
                        }
                        break;
                    }
                    if (strcmp(argv[var_s0], "-no_archive") == 0) {
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-no_mpc") == 0) {
                        B_1000A5B4 = 1;
                        break;
                    }
                    if ((compiler == COMPILER_3) &&
                        (
                            // (strcmp(argv[var_s0], "-noextend_source") == 0) ||
                            (strcmp(argv[var_s0], "-noi4") == 0) || (strcmp(argv[var_s0], "-noisam") == 0) ||
                            (strcmp(argv[var_s0], "-noexpopt") == 0) || (strcmp(argv[var_s0], "-noequivauto") == 0) ||
                            (strcmp(argv[var_s0], "-nof77") == 0))) {
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                        break;
                    }
                    if (compiler == COMPILER_6) {
                        if (strcmp(argv[var_s0], "-nolock") == 0) {
                            nolockflag = TRUE;
                            break;
                        }
                        if ((strcmp(argv[var_s0], "-nomfdata") == 0) || (strcmp(argv[var_s0], "-normdata") == 0)) {
                            addstr(&ucobflags, argv[var_s0]);
                            break;
                        }
                        goto bad_option;
                    }
                    if (strcmp(argv[var_s0], "-nocpp") == 0) {
                        if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n",
                                  argv[var_s0], "");
                        } else {
                            docpp = FALSE;
                            add_static_opt(argv[var_s0]);
                        }
                        break;
                    }
                    if ((compiler == COMPILER_3) ||
                        ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0))) {
                        if (strcmp(argv[var_s0], "-nocode") == 0) {
                            nocode = TRUE;
                            cflag = TRUE;
                            break;
                        }
                        if (strcmp(argv[var_s0], "-no_prelink") == 0) {
                            no_prelink = TRUE;
                            break;
                        }
                        if (strcmp(argv[var_s0], "-no_auto_include") == 0) {
                            auto_template_include = FALSE;
                            add_static_opt(argv[var_s0]);
                            break;
                        }
                    }
                    if (strcmp(argv[var_s0], "-none") == 0) {
                        addstr(&objfiles, argv[var_s0]);
                        break;
                    }
                    if ((compiler == COMPILER_1) &&
                        ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                        (strcmp(argv[var_s0], "-nofilt") == 0)) {
                        nofilt = TRUE;
                        add_static_opt(argv[var_s0]);
                        break;
                    }
                    if ((compiler == COMPILER_1) && (c_compiler_choice == C_COMPILER_CHOICE_3) &&
                        (strncmp(argv[var_s0], "-no_delta", 9) == 0)) {
                        char* spFC;

                        if (argv[var_s0][9] == '\0') {
                            spFC = "-YDN";
                        } else if (strcmp(argv[var_s0] + 9, "_expr") == 0) {
                            spFC = "-YDE";
                        } else if (strcmp(argv[var_s0] + 9, "_include") == 0) {
                            spFC = "-YDI";
                        } else {
                            spFC = NULL;
                        }
                        if (spFC != NULL) {
                            if (var_s0 >= (argc - 1)) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "%s must have an argument\n", argv[var_s0]);
                                exit(2);
                            }
                            var_s0++;
                            if (argv[var_s0][0] == '-') {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "%s must have an argument\n", argv[var_s0 - 1]);
                                exit(2);
                            }
                            addstr(&edisonflags, mkstr(spFC, argv[var_s0], NULL));
                            add_static_opt(argv[var_s0 - 1]);
                            add_static_opt(argv[var_s0]);
                            break;
                        }
                    }
                    goto bad_option;

                case 'o': /* switch 1 */
                    if (strcmp(argv[var_s0], "-old_rl") == 0) {
                        addstr(&fcomflags, "-old_rl");
                        break;
                    }
                    if (strcmp(argv[var_s0], "-oldcpp") == 0) {
                        if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n",
                                  argv[var_s0], "");
                        } else {
                            oldcppflag = TRUE;
                            if ((compiler == COMPILER_1) && tpflag) {
                                relocate_passes(tstring, hstring, Bstring);
                            }
                        }
                        break;
                    }
                    // if (strcmp(argv[var_s0], "-old_ld") == 0) {
                    //     if (D_1000BF94) {
                    //         error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "malformed or unknown option: -old_ld\n");
                    //         exit(2);
                    //     } else {
                    //         LD = "old_ld";
                    //         relocate_passes("l", NULL, NULL);
                    //     }
                    //     break;
                    // }
                    if (strcmp(argv[var_s0], "-o32") == 0) {
                        thirty2bitflag = TRUE;
                        mips_abi = 1;
                        // if (var_s0 >= (argc - MIPS_ABI_1)) {
                        //     func_00431B38(var_s0 + 1, 1);
                        // }
                        break;
                    }
                    if (strcmp(argv[var_s0], "-objectlist") == 0) {
                        if ((argv[var_s0 + 1] != 0) && (argv[var_s0 + 1][0] != '-')) {
                            addstr(&objfiles, argv[var_s0]);
                            var_s0++;
                            addstr(&objfiles, argv[var_s0]);
                        } else {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-objectlist must be given a file argument\n");
                        }
                        break;
                    }
                    if (argv[var_s0][2] == '\0') {
                        var_s0++;
                        if (var_s0 < argc) {
                            struct stat sp74;

                            outfile = argv[var_s0];
                            var_s1 = getsuf(outfile);
                            if (((var_s1 == 'c') || (var_s1 == 'p') || (var_s1 == 'f') || (var_s1 == 'F') ||
                                 (var_s1 == 'r') || (var_s1 == 'e') ||
                                 ((compiler == COMPILER_1) &&
                                  ((c_compiler_choice == C_COMPILER_CHOICE_2) ||
                                   (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                                  (var_s1 == 6)) ||
                                 (var_s1 == 's') || (var_s1 == 1) || (var_s1 == 2)) &&
                                (stat(outfile, &sp74) == 0)) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                                      "-o %s resembles the name of a source file, disallowed\n", argv[var_s0]);
                                exit(2);
                            }
                            // B_1000ECCC = mkstr(outfile, NULL);
                            // func_00431B38(var_s0, 2);
                            break;
                        } else {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-o must have an argument\n");
                            exit(2);
                        }
                    }
                    if ((compiler == COMPILER_3) && (strcmp(argv[var_s0], "-onetrip") == 0)) {
                        addstr(&fcomflags, "-1");
                        mp_onetripflag = TRUE;
                        break;
                    }
                    goto bad_option;

                case 'p': /* switch 1 */
                    if (strcmp(argv[var_s0], "-prototypes") == 0) {
                        if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n",
                                  argv[var_s0], "");
                        } else {
                            prototype_checking_on = TRUE;
                        }
                        break;
                    }
                    if ((compiler == COMPILER_1) && (strcmp(argv[var_s0], "-pedantic") == 0)) {
                        if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n",
                                  argv[var_s0], "");
                        } else {
                            addstr(&acppflags, "-p");
                        }
                        break;
                    }
                    if (strcmp(argv[var_s0], "-pfa") == 0) {
                        mp_flag |= 0x10001;
                        if ((var_s0 + 1) < argc) {
                            struct_mpflags* sp70 = mpflags;

                            while ((sp70->unk_0 != NULL) && (strcmp(argv[var_s0 + 1], sp70->unk_0) != 0)) {
                                sp70++;
                            }
                            if (sp70->unk_0 != NULL) {
                                if (1) {} // FAKE
                                var_s0++;
                                mp_flag |= sp70->unk_4;
                            }
                        }
                        break;
                    }
                    if (strncmp(argv[var_s0], "-pfaprepass,", 12) == 0) {
                        mp_flag |= 0x10001;
                        mp_prepass_count++;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-pca") == 0) {
                        cmp_flag |= 0x10001;
                        if (Bflag) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-pca must preceed any -B flags.\n");
                            exit(2);
                        }
                        relocate_passes("fKY", NULL, NULL);
                        if ((var_s0 + 1) < argc) {
                            struct_mpflags* sp6C = cmpflags;

                            while ((sp6C->unk_0 != NULL) && (strcmp(argv[var_s0 + 1], sp6C->unk_0) != 0)) {
                                sp6C++;
                            }

                            if (sp6C->unk_0 != NULL) {
                                if (1) {} // FAKE
                                var_s0++;
                                cmp_flag |= sp6C->unk_4;
                            }
                        }
                        break;
                    }
                    if ((compiler == COMPILER_1) &&
                        ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3))) {
                        if (strncmp(argv[var_s0], "-pt", 3) == 0) {
                            char* sp68 = argv[var_s0] + 3;

                            if (strcmp(sp68, "v") == 0) {
                                verbose_prelink++;
                            } else if (strcmp(sp68, "none") == 0) {
                                default_template_instantiation_mode = 0;
                            } else if (strcmp(sp68, "used") == 0) {
                                default_template_instantiation_mode = 1;
                            } else if ((strcmp(sp68, "a") == 0) || (strcmp(sp68, "all") == 0)) {
                                default_template_instantiation_mode = 2;
                            } else if (*sp68 == 'e') {
                                if ((strcmp(sp68 + 1, ".c") != 0) && (strcmp(sp68 + 1, ".cc") != 0) &&
                                    (strcmp(sp68 + 1, ".c++") != 0) && (strcmp(sp68 + 1, ".C") != 0) &&
                                    (strcmp(sp68 + 1, ".cxx") != 0) && (strcmp(sp68 + 1, ".CXX") != 0) &&
                                    (strcmp(sp68 + 1, ".cpp") != 0) && (strcmp(sp68 + 1, ".CPP") != 0)) {
                                    error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "unsupported suffix in %s\n",
                                          argv[var_s0]);
                                }
                            } else {
                                error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "ignored unsupported option %s\n",
                                      argv[var_s0]);
                            }
                            break;
                        }
                        if (strcmp(argv[var_s0], "-prelink") == 0) {
                            force_prelink = TRUE;
                            break;
                        }
                    }
                    if (argv[var_s0][2] == '\0') {
                        pflag = 1;
                        // } else if (strcmp(argv[var_s0], "-pg") == 0) {
                        //     pflag = 1;
                        //     pgflag = 1;
                    } else if (argv[var_s0][3] == '\0') {
                        if (1) {} // FAKE
                        if ((argv[var_s0][2] >= '0') && (argv[var_s0][2] <= '3')) {
                            pflag = argv[var_s0][2] - '0';
                        } else {
                            goto bad_option;
                        }
                    } else {
                        goto bad_option;
                    }
                    if ((pflag == 0) || (pflag == 1)) {
                        if (Bflag) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-p0 or -p1 must precede any -B flags\n");
                            exit(2);
                        }
                    } else {
                        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "%s has been superseded, see prof (1) and pixie (1)\n",
                              argv[var_s0]);
                        exit(2);
                    }
                    relocate_passes("rn", NULL, NULL);
                    break;

                case 'q': /* switch 1 */
                    if (strcmp(argv[var_s0], "-quickstart_info") == 0) {
                        quickstart_info = TRUE;
                        break;
                    }
                    if ((strcmp(argv[var_s0], "-ql") == 0) || (strcmp(argv[var_s0], "-qp") == 0)) {
                        break;
                    }
                    goto bad_option;

                case 'r': /* switch 1 */
                    if ((strcmp(argv[var_s0], "-r4000") == 0) || (strcmp(argv[var_s0], "-r6000") == 0)) {
                        addstr(&asflags, argv[var_s0]);
                        break;
                    }
                    if (argv[var_s0][2] == '\0') {
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-require_minor") == 0) {
                        addstr(&objfiles, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-rm_dead_code") == 0) {
                        force_rm_dead_code = TRUE;
                        break;
                    }
                    if ((strcmp(argv[var_s0], "-rpath") == 0) && (argv[var_s0 + 1] != 0) &&
                        (argv[var_s0 + 1][0] != '-')) {
                        addstr(&ldflags, argv[var_s0]);
                        var_s0++;
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    if ((strcmp(argv[var_s0], "-rdata_shared") == 0) ||
                        (strcmp(argv[var_s0], "-rdata_writable") == 0)) {
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    if ((compiler == COMPILER_3) && (strcmp(argv[var_s0], "-r8") == 0)) {
                        addstr(&fcomflags, argv[var_s0]);
                        break;
                    }
                    if ((compiler == COMPILER_6) &&
                        ((strcmp(argv[var_s0], "-range") == 0) || (strcmp(argv[var_s0], "-rmansi") == 0) ||
                         (strcmp(argv[var_s0], "-rmext") == 0))) {
                        addstr(&ucobflags, argv[var_s0]);
                        break;
                    }
                    goto bad_option;

                case 's': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        // if ((compiler == COMPILER_1) && ((c_compiler_choice == C_COMPILER_CHOICE_2) ||
                        //                                  (c_compiler_choice == C_COMPILER_CHOICE_3))) {
                        //     do_strip = TRUE;
                        //     break;
                        // }
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-strictIEEE") == 0) {
                        addstr(&optflags, argv[var_s0]);
                        break;
                    }
                    if ((((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) ||
                         (compiler == COMPILER_3)) &&
                        (strncmp(argv[var_s0], "-sa", 3) == 0) &&
                        ((argv[var_s0][3] == '\0') || (argv[var_s0][3] == ','))) {
                        D_100001FC = TRUE;
                        if ((argv[var_s0][3] == ',') && (argv[var_s0][4] != '\0')) {
                            char* sp64;

                            for (sp64 = strtok(argv[var_s0] + 4, ","); sp64 != NULL; sp64 = strtok(NULL, ",")) {
                                if (strcmp(sp64, "nosrc") == 0) {
                                    D_10000200 = TRUE;
                                } else if (D_10000204 != NULL) {
                                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                                          "Static analysis directory already specified\n");
                                } else {
                                    D_10000204 = sp64;
                                    if (sp64[strlen(sp64) - 1] != '/') {
                                        D_10000204 = mkstr(sp64, "/", NULL);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    if ((((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) ||
                         (compiler == COMPILER_3)) &&
                        (strncmp(argv[var_s0], "-sa_fs", 6) == 0) &&
                        ((argv[var_s0][6] == '\0') || (argv[var_s0][6] == ','))) {
                        D_10000208 =
                            (argv[var_s0][6] == ',') ? mkstr(argv[var_s0] + 7, NULL) : mkstr("cvstatic.fileset", NULL);
                        D_1000020C++;
                        break;
                    }
                    if ((compiler == COMPILER_1) && (strcmp(argv[var_s0], "-set_version") == 0)) {
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-set_version requires an argument\n");
                            exit(2);
                        }
                        addstr(&ldflags, argv[var_s0 - 1]);
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    if ((compiler == COMPILER_1) && (strcmp(argv[var_s0], "-soname") == 0)) {
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-soname requires an argument\n");
                            exit(2);
                        }
                        addstr(&ldflags, argv[var_s0 - 1]);
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-systype") == 0) {
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-systype must have an argument\n");
                            exit(2);
                        }
                        if (user_systype) {                           // systype already specified via an argument
                            if (strcmp(systype, argv[var_s0]) != 0) { // Different systype from previous
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "only one -systype option allowed\n");
                                exit(2);
                            } else {
                                multiple_systype = TRUE;
                            }
                        }
                        systype = argv[var_s0];
                        user_systype = TRUE;
                        if (Bflag && !systype_seen) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-systype must precede any -B flags\n");
                            exit(2);
                        } else {
                            systype_seen = TRUE;
                        }
                        if (!multiple_systype) {
                            if (strcmp(systype, "svr4") == 0) {
                                svr4_systype = TRUE;
                                if (!elfflag) {
                                    addstr(&asflags, "-elf");
                                    addstr(&ldflags, "-elf");
                                }
                                elfflag = TRUE;
                            } else {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "Only systype svr4 allowed\n");
                                exit(2);
                            }
                            if ((strcmp(systype, "svr4") != 0) && (strcmp(systype, "bsd43") != 0) &&
                                (strcmp(systype, "svr3") != 0) && (strcmp(systype, "sysv") != 0) &&
                                (fopen(strcat("/", systype), "r") == NULL)) {
                                if (!systype_warn) {
                                    error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                                          "This systype doesn't exist on this machine; changed systype to svr3.\n");
                                }
                                systype = "svr3";
                            }
                            if (!svr4_systype) {
                                comp_target_root = mkstr(comp_target_root, systype, "/", NULL);
                            }
                            if (fiveflag) {
                                include = mkstr(comp_target_root, "usr/5include", NULL);
                            } else {
                                einclude = mkstr(comp_target_root, "usr/include/CC", NULL);
                                include = mkstr(comp_target_root, "usr/include", NULL);
                            }
                            if (Bstring != NULL) {
                                relocate_passes("h", NULL, Bstring);
                            }
                            newrunlib();
                        }
                        add_static_opt(argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-swopcode") == 0) {
                        if (dwopcodeflag || sixty4bitflag) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                                  "-swopcode can not be used with -dwopcode/-64bit\n");
                            exit(2);
                        }
                        swopcodeflag = TRUE;
                        break;
                    }
                    if ((argv[var_s0][2] == 'o') && (argv[var_s0][3] == 'p') && (argv[var_s0][4] == 't')) { // "-sopt"
                        if ((compiler != COMPILER_1) && (compiler != COMPILER_3)) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                                  "-sopt only available with Fortran and C; option ignored.\n");
                        } else if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n",
                                  argv[var_s0], "");
                        } else {
                            Warg = argv[var_s0] + 5;
                            while (*Warg == ',') {
                                *Warg++ = 0;
                                addstr(&soptflags, Warg);
                                while ((*Warg != ',') && (*Warg != 0)) {
                                    Warg++;
                                }
                            }
                            run_sopt = TRUE;
                        }
                        break;
                    }
                    if (strcmp(argv[var_s0], "-show") == 0) {
                        vflag = TRUE;
                        break;
                    }
                    // if (strcmp(argv[var_s0], "-showt") == 0) {
                    //     time_flag = TRUE;
                    //     break;
                    // }
                    if (strcmp(argv[var_s0], "-show0") == 0) {
                        vflag = TRUE;
                        execute_flag = FALSE;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-showm") == 0) {
                        memory_flag++;
                        break;
                    }
                    // if (strcmp(argv[var_s0], "-show_defaults") == 0) {
                    //     execute_flag = FALSE;
                    //     exit(0);
                    //     break;
                    // }
                    if (compiler == COMPILER_1) {
                        if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0) &&
                            (strncmp(argv[var_s0], "-smart", 6) == 0)) {
                            if ((argv[var_s0][6] == ',') && (argv[var_s0][7] != 0)) {
                                sbrepos = argv[var_s0] + 7;
                            } else {
                                sbrepos = NULL;
                            }
                            add_static_opt(argv[var_s0]);
                            smart_build = TRUE;
                            break;
                        }
                        if (strcmp(argv[var_s0], "-shared") == 0) {
                            call_shared = FALSE;
                            make_edison_shlib++;
                            break;
                        }
                        if (strcmp(argv[var_s0], "-std0") == 0) {
                            stdflag = 0;
                            addstr(&ccomflags, argv[var_s0]);
                            break;
                        }
                        if ((strcmp(argv[var_s0], "-std") == 0) || (strcmp(argv[var_s0], "-std1") == 0)) {
                            stdflag = 1;
                            addstr(&ccomflags, argv[var_s0]);
                            break;
                        }
                        if (strcmp(argv[var_s0], "-signed") == 0) {
                            addstr(&pcaflags, "-signed");
                            addstr(&soptflags, "-signed");
                            addstr(&ccomflags, "-Xsigned");
                            if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
                                signedcharflag = TRUE;
                            }
                            break;
                        }
                    }
                    if ((compiler == COMPILER_4) &&
                        ((strcmp(argv[var_s0], "-std") == 0) || (strcmp(argv[var_s0], "-std0") == 0) ||
                         (strcmp(argv[var_s0], "-std1") == 0))) {
                        stdflag = 1;
                        addstr(&ccomflags, argv[var_s0]);
                        break;
                    }
                    if (compiler == COMPILER_3) {
                        if (strcmp(argv[var_s0], "-std") == 0) {
                            addstr(&fcomflags, argv[var_s0]);
                            break;
                        }
                        if (strcmp(argv[var_s0], "-static") == 0) {
                            automaticflag = FALSE;
                            break;
                        }
                        if (strncmp(argv[var_s0], "-share_", 7) == 0) {
                            if (strcmp(argv[var_s0] + 7, "io") == 0) {
                                D_1000039C = 1;
                                break;
                            }
                            if (strcmp(argv[var_s0] + 7, "all") == 0) {
                                D_1000039C = 2;
                                break;
                            }
                        }
                    }
                    if ((compiler == COMPILER_2) && (strcmp(argv[var_s0], "-std") == 0)) {
                        stdflag = 1;
                        addstr(&upasflags, argv[var_s0]);
                        break;
                    }
                    if ((compiler == COMPILER_6) &&
                        ((strcmp(argv[var_s0], "-supp_cob85") == 0) || (strcmp(argv[var_s0], "-supp_cod") == 0) ||
                         (strcmp(argv[var_s0], "-supp_rm") == 0))) {
                        addstr(&ucobflags, argv[var_s0]);
                        break;
                    }
                    if ((compiler == COMPILER_4) && (strcmp(argv[var_s0], "-signed") == 0)) {
                        break;
                    }
                    goto bad_option;

                case 't': /* switch 1 */
                    if (strcmp(argv[var_s0], "-transitive_link") == 0) {
                        full_transitive_link = FALSE;
                        transitive_link = TRUE;
                        no_transitive_link = FALSE;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-trapuv") == 0) {
                        trapuv_flag = TRUE;
                        addstr(&upasflags, argv[var_s0]);
                        addstr(&fcomflags, argv[var_s0]);
                        addstr(&upl1flags, argv[var_s0]);
                        addstr(&ucobflags, argv[var_s0]);
                        addstr(&ulpiflags, argv[var_s0]);
                        addstr(&eflflags, argv[var_s0]);
                        addstr(&ratforflags, argv[var_s0]);
                        addstr(&genflags, argv[var_s0]);
                        addstr(&asflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-tfp") == 0) {
                        tfp_flag = TRUE;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-traditional") == 0) {
                        acpp_traditional++;
                        break;
                    }
                    tstring = argv[var_s0] + 2;
                    strcat(alltstring, tstring);
                    break;

                case 'Z':                      /* switch 1 */
                    switch (argv[var_s0][2]) { /* switch 4 */
                        case 'A':              /* switch 4 */
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;

                        case 'C': /* switch 4 */
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;

                        case 'F': /* switch 4 */
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;

                        case 'N': /* switch 4 */
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;

                        case 'P': /* switch 4 */
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;

                        case 'U': /* switch 4 */
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;

                        case 'f': /* switch 4 */
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;

                        case 'i': /* switch 4 */
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;

                        case 'R': /* switch 4 */
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;

                        case 'G': /* switch 4 */
                            addstr(&ldZflags, "-ZG");
                            break;

                        case 'q': /* switch 4 */
                            // -Zq
                            vflag = TRUE;
                            break;

                        case 'g': /* switch 4 */
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "-Zg is obsolete and is ignored.\n");
                            if (compiler == COMPILER_1) {
                                error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                                      "perhaps replace -Zg with -lgl_s. See your graphics documentation.\n");
                            }
                            if (hasfortran || (compiler == COMPILER_3)) {
                                error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                                      "perhaps replace -Zg with -lfgl -lgl_s  See f77(1).\n");
                            }
                            if (haspascal || (compiler == COMPILER_2)) {
                                error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                                      "perhaps replace -Zg with -lpgl /usr/lib/p2cstr.o -lgl_s  See pc(1).\n");
                            }
                            break;

                        case 'r': /* switch 4 */
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "-Zr is obsolete and is ignored.\n");
                            break;

                        case 'v': /* switch 4 */
                            stdflag = 1;
                            addstr(&ccomflags, "-std");
                            addstr(&upasflags, "-std");
                            addstr(&fcomflags, "-std");
                            addstr(&upl1flags, "-std");
                            addstr(&ucobflags, "-std");
                            break;

                        case 'z': /* switch 4 */
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;

                        default: /* switch 4 */
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "Unknown character in %s\n", argv[var_s0]);
                            exit(2);
                            break;
                    }
                    break;

                case '-': /* switch 1 */
                    // if (argv[var_s0][2] == '\0') {
                    //     if (xpg_flag) {
                    //         NoMoreOptions++;
                    //     }
                    //     break;
                    // }
                    switch (argv[var_s0][2]) { /* switch 8; irregular */
                        case 'n':              /* switch 8 */
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "%s is default\n", argv[var_s0]);
                            break;
                        case 'x': /* switch 8 */
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "%s is default\n", argv[var_s0]);
                            break;
                        default:
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "Unknown character in %s\n", argv[var_s0]);
                            exit(2);
                            break;
                    }

                    break;

                case 'u': /* switch 1 */
                    if (strcmp(argv[var_s0], "-uopt0") == 0) {
                        break;
                    }
                    if (argv[var_s0][2] == '\0') {
                        if (compiler == COMPILER_3) {
                            mp_uflag = TRUE;
                            addstr(&fcomflags, argv[var_s0]);
                            add_static_opt(argv[var_s0]);
                            break;
                        } else {
                            var_s0++;
                            if (var_s0 < argc) {
                                addstr(&objfiles, "-u");
                                addstr(&objfiles, argv[var_s0]);
                                break;
                            } else {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "ld requires -u to have an argument\n");
                                exit(2);
                            }
                        }
                    }

                    if (strcmp(argv[var_s0], "-unroll") == 0) {
                        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "This flag is no longer supported\n");
                        exit(2);
                    } else if ((compiler == COMPILER_3) && (strcmp(argv[var_s0], "-usefpidx") == 0)) {
                        addstr(&fcomflags, argv[var_s0]);
                        break;
                    }

                    if (strcmp(argv[var_s0], "-use_readwrite_const") == 0) {
                        if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
                            addstr(&edisonflags, "-Yr0");
                        } else {
                            addstr(&accomflags, "-use_readwrite_const");
                        }
                        break;
                    }
                    if (strcmp(argv[var_s0], "-use_readonly_const") == 0) {
                        if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
                            addstr(&edisonflags, "-Yr1");
                        } else {
                            addstr(&accomflags, "-use_readonly_const");
                        }
                        break;
                    }
                    if ((compiler == COMPILER_1) && (strcmp(argv[var_s0], "-update_registry") == 0)) {
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-update_registry requires a filename argument\n");
                            exit(2);
                        }
                        addstr(&ldflags, argv[var_s0 - 1]);
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    goto bad_option;

                case 'v': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        if (!default_svr4) {
                            vflag = TRUE;
                            // time_flag = TRUE;
                        }
                        break;
                    }
                    if (compiler == COMPILER_1) {
                        if (strcmp(argv[var_s0], "-volatile") == 0) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                                  "-volatile is no longer supported; use the volatile qualifier instead\n");
                            break;
                        }
                        if (strcmp(argv[var_s0], "-varargs") == 0) {
                            addstr(&ccomflags, "-Xvarargs");
                            break;
                        }
                        if (strcmp(argv[var_s0], "-verbose") == 0) {
                            addstr(&ccomflags, "-verbose");
                            break;
                        }
                    }
                    if ((compiler == COMPILER_3) &&
                        ((strncmp(argv[var_s0], "-vms", 4) == 0) || (strcmp(argv[var_s0], "-varargs") == 0))) {
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                        break;
                    }
                    if ((compiler == COMPILER_1) &&
                        ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                        (strcmp(argv[var_s0], "-v2") == 0)) {
                        if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n",
                                  argv[var_s0], "");
                        }
                        break;
                    }
                    goto bad_option;

                case 'w': /* switch 1 */
                    if ((compiler == COMPILER_1) && (strncmp(argv[var_s0], "-wlint", 6) == 0)) {
                        if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n",
                                  argv[var_s0], "");
                        } else {
                            addstr(&ccomflags, argv[var_s0]);
                        }
                        break;
                    }
                    if (strcmp(argv[var_s0], "-woff") == 0) {
                        var_s0++;
                        if (var_s0 < argc) {
                            if (strcmp(argv[var_s0], "options") == 0) {
                                sp14C = 0;
                                break;
                            }
                            if ((argv[var_s0][0] < '0') || (argv[var_s0][0] > '9')) {
                                error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                                      "-woff requires a comma-separated list of error numbers - ignored\n");
                                var_s0--;
                                break;
                            }
                            addstr(&accomflags, mkstr("-Xwoff", argv[var_s0], NULL));
                            addstr(&edisonflags, mkstr("-YW", argv[var_s0], NULL));
                            break;
                        }
                        error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                              "-woff requires a warning number (or a list of them)\n");
                        exit(2);
                    }
                    if ((argv[var_s0][2] == '1') && (argv[var_s0][3] == '\0')) {
                        if (compiler != COMPILER_3) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "Unknown flag: %s\n", argv[var_s0]);
                        } else {
                            w1flag = 1;
                        }
                        break;
                    }
                    if ((argv[var_s0][2] == '0') && (argv[var_s0][3] == '\0')) {
                        if (compiler != COMPILER_3) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "Unknown flag: %s\n", argv[var_s0]);
                        } else {
                            w1flag = 0;
                        }
                        break;
                    }
                    if (argv[var_s0][2] == '6') {
                        if ((compiler == COMPILER_3) && (argv[var_s0][2] == '6')) {
                            mp_66flag = TRUE;
                        }
                        addstr(&fcomflags, argv[var_s0]);
                        break;
                    }
                    if ((argv[var_s0][2] != 0) && (compiler == COMPILER_1) &&
                        (c_compiler_choice != C_COMPILER_CHOICE_0)) {
                        error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n",
                              argv[var_s0], "");
                        break;
                    }
                    if ((argv[var_s0][2] == '\0') ||
                        ((argv[var_s0][3] == '\0') &&
                         ((argv[var_s0][2] == '1') || (argv[var_s0][2] == '2') || (argv[var_s0][2] == '3')))) {
                        addstr(&cppflags, argv[var_s0]);
                        addstr(&ccomflags, argv[var_s0]);
                        addstr(&edisonflags, argv[var_s0]);
                        w1flag = 2;
                        addstr(&upasflags, argv[var_s0]);
                        addstr(&upl1flags, argv[var_s0]);
                        addstr(&ucobflags, argv[var_s0]);
                        addstr(&ulpiflags, argv[var_s0]);
                        addstr(&uldflags, argv[var_s0]);
                        addstr(&uopt0flags, argv[var_s0]);
                        addstr(&ddoptflags, argv[var_s0]);
                        addstr(&uloopflags, argv[var_s0]);
                        addstr(&optflags, argv[var_s0]);
                        addstr(&genflags, argv[var_s0]);
                        addstr(&ldflags, argv[var_s0]);
                        addstr(&asflags, argv[var_s0]);
                        addstr(&ldflags, argv[var_s0]);
                        addstr(&ftocflags, argv[var_s0]);
                        break;
                    }
                    goto bad_option;

                case 'y': /* switch 1 */
                    if (argv[var_s0][2] != '\0') {
                        addstr(&objfiles, argv[var_s0]);
                        break;
                    }
                    goto bad_option;

                case 'x': /* switch 1 */
                    if (strcmp(argv[var_s0], "-xansi") == 0) {
                        if (compchoice == COMP_CHOICE_1) {
                            compchoice = COMP_CHOICE_0;
                        }
                        ansichoice = ANSICHOICE_XANSI;
                        cppchoice = CPP_CHOICE_3;
                        relocate_passes("p", NULL, NULL);
                        add_static_opt(argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-xgot") == 0) {
                        addstr(&asflags, "-big_got");
                        break;
                    }
                    if (argv[var_s0][2] == '\0') {
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    goto bad_option;

                case 'z': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    }
                    goto bad_option;

                default:
                    goto bad_option;
            }
            continue;
        } else if ((argv[var_s0][0] == '+') && (compiler == COMPILER_1) &&
                   ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3))) {
            switch (argv[var_s0][1]) { /* switch 5 */
                case 'p':              /* switch 5 */
                    if (argv[var_s0][2] == '\0') {
                        anachronisms = FALSE;
                    } else if (argv[var_s0][2] == 'p') {
                        anachronisms = FALSE;
                        cfront_compatible = FALSE;
                    } else if (argv[var_s0][2] == 'a') {
                        anachronisms = FALSE;
                    } else if (argv[var_s0][2] == 'c') {
                        cfront_compatible = FALSE;
                    }
                    add_static_opt(argv[var_s0]);
                    break;

                case 'w': /* switch 5 */
                    fullwarn = TRUE;
                    break;

                case 'v': /* switch 5 */
                    vflag = TRUE;
                    break;

                case 'd': /* switch 5 */
                    disable_inlines = TRUE;
                    break;

                case 'e': /* switch 5 */
                    if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
                        error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n",
                              argv[var_s0], "");
                        break;
                    }

                case 'I': /* switch 5 */
                    cflag = TRUE;
                    plusIflag = TRUE;
                    Fflag = TRUE;
                    default_template_instantiation_mode = 1;
                    break;

                case 'a':
                case 'L':
                    break;

                default: /* switch 5 */
                    goto bad_option;
            }
            continue;
        }

        var_s1 = getsuf(argv[var_s0]);
        if (var_s1 == 'm') {
            var_s1 = 'f';
        }
        if (var_s1 == 'p') {
            haspascal = TRUE;
        }
        if (var_s1 == 'f') {
            hasfortran = TRUE;
        }
        if (var_s1 == SUF_1) {
            haspl1 = TRUE;
        }
        if ((var_s1 == 'c') || (var_s1 == 'p') || (var_s1 == 'f') || (var_s1 == 'F') || (var_s1 == 'r') ||
            (var_s1 == 'e') || (var_s1 == 'B') || (var_s1 == 'U') || (var_s1 == 's') || (var_s1 == 'O') ||
            (var_s1 == 'G') || (var_s1 == 'S') || (var_s1 == 'M') || (var_s1 == 'V') || (var_s1 == 'i') ||
            (var_s1 == SUF_1) || (var_s1 == 'D') || (var_s1 == SUF_3) || (var_s1 == SUF_2) || (var_s1 == 'u') ||
            (var_s1 == SUF_6) || ((compiler == COMPILER_1) && nocode && D_100001FC && (var_s1 == 'h')) || Eflag ||
            (compiler == COMPILER_4)) {
            // int sp60; // number of '-' on the end?
            int sp5C; // option index

            srcexists++;
            // if ((argv[var_s0][0] == '-') && !NoMoreOptions) {
            //     sp60 = 1;
            //     while (argv[var_s0][sp60] == '-') {
            //         sp60++;
            //     }
            //     argv[var_s0] += sp60;
            // }
            for (sp5C = 1; sp5C < argc; sp5C++) {
                if ((argv[sp5C][1] == 'j') && (strcmp(argv[sp5C], "-j") == 0)) {
                    jflag++;
                }
            }
            if (((Oflag == 3) || (Oflag == 4)) && !jflag &&
                ((var_s1 == 'c') || (var_s1 == 'p') || (var_s1 == 'f') || (var_s1 == 'F') || (var_s1 == 'r') ||
                 (var_s1 == 'e') || (var_s1 == 'B') || (var_s1 == 'U') || (var_s1 == 'i') || (var_s1 == SUF_1) ||
                 (var_s1 == SUF_3) || (var_s1 == SUF_2) || (var_s1 == SUF_6) || (var_s1 == 'u') || (var_s1 == 'D'))) {
                if (var_s1 != 'u') {
                    addstr(&srcfiles, argv[var_s0]);
                    var_s2 = mksuf(argv[var_s0], 'u');
                } else {
                    var_s2 = argv[var_s0];
                }
                uload = TRUE;
                if (uldobj_place == -1) {
                    uldobj_place = save_place(&objfiles);
                }
                if (nodup(&ufiles, var_s2) != 0) {
                    addstr(&ufiles, var_s2);
                }
                var_s2 = mksuf(argv[var_s0], 'o');
                if (nodup(&objfiles, var_s2) != 0) {
                    sp158 = var_s2;
                }
            } else if (!Eflag && (compiler != COMPILER_4)) {
                addstr(&srcfiles, argv[var_s0]);
                var_s2 = mksuf(argv[var_s0], 'o');
                if (nodup(&objfiles, var_s2) != 0) {
                    addstr(&objfiles, var_s2);
                    sp158 = var_s2;
                    nobjs++;
                }
            } else {
                addstr(&srcfiles, argv[var_s0]);
            }
        } else if (var_s1 == 'b') {
            if (((Oflag == 3) || (Oflag == 4)) && !jflag) {
                if (uldobj_place == -1) {
                    uldobj_place = save_place(&objfiles);
                }
                addstr(&ufiles, argv[var_s0]);
                uload = TRUE;
            }
        } else {
            addstr(&objfiles, argv[var_s0]);
            if (var_s1 == 'o') {
                nobjs++;
            }
        }
        // func_00431B38(var_s0 + 1, 1);
        continue;

    bad_option:
        if (sp14C != 0) {
            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "malformed or unknown option: %s\n", argv[var_s0]);
            exit(2);
        } else {
            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "malformed or unknown option: %s\n", argv[var_s0]);
        }
    } /* end of loop */

    if (sp15C != NULL) {
        char* sp58; // name of source file if there is only one

        if (srcfiles.length == 1) {
            sp58 = strdup(srcfiles.entries[0]);
            if (sp58 == NULL) {
                sp58 = sp158;
            } else {
                int sp54 = strlen(sp58); // length of single source file's name

                if ((sp54 >= 3) && (sp58[sp54 - 2] == '.')) {
                    if (Eflag) {
                        sp58[sp54 - 1] = 'i';
                    } else if (Sflag) {
                        sp58[sp54 - 1] = 's';
                    } else if (jflag) {
                        sp58[sp54 - 1] = 'u';
                    } else {
                        sp58[sp54 - 2] = '\0';
                    }
                }
            }
        }

        if (((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) ||
            ((compiler == COMPILER_3) && D_100001FC)) {
            if ((srcfiles.length == 1) && ((outfile != NULL) || !cflag)) {
                addstr(&ldflags, "-MDignore");
                addstr(&ldflags, sp158);
            }
            addstr(&cppflags, mkstr("-YM", sp15C, NULL));
            if (sp154 != NULL) {
                addstr(&cppflags, mkstr("-Yt", sp154, NULL));
            }
            addstr(&ldflags, "-MDupdate");
            addstr(&ldflags, sp15C);
        } else {
            if ((srcfiles.length == 1) && ((outfile != NULL) || !cflag)) {
                addstr(&cppflags, "-MDtarget");
                if (outfile != NULL) {
                    addstr(&cppflags, outfile);
                } else { // if no outfile specified, default to name of input file with suffix replaced
                    addstr(&cppflags, sp58);
                }
                addstr(&ldflags, "-MDignore");
                addstr(&ldflags, sp158);
            }
            addstr(&cppflags, "-MDupdate");
            addstr(&cppflags, sp15C);
            if (Oflag == 3) {
                addstr(&uldflags, "-MDtarget");
                if (outfile != NULL) {
                    addstr(&uldflags, outfile);
                } else if (cflag) {
                    addstr(&uldflags, "u.out.o");
                } else {
                    addstr(&uldflags, "a.out");
                }
                addstr(&uldflags, "-MDupdate");
                addstr(&uldflags, sp15C);
            } else {
                addstr(&ldflags, "-MDupdate");
                addstr(&ldflags, sp15C);
            }
        }
    }

    // if (mips2flag) {
    //     addstr(&ccomflags, "-mips2");
    //     addstr(&upasflags, "-mips2");
    //     addstr(&fcomflags, "-mips2");
    //     addstr(&upl1flags, "-mips2");
    //     addstr(&ucobflags, "-mips2");
    //     addstr(&ulpiflags, "-mips2");
    //     addstr(&eflflags, "-mips2");
    //     addstr(&ratforflags, "-mips2");
    //     addstr(&ujoinflags, "-mips2");
    //     addstr(&usplitflags, "-mips2");
    //     addstr(&umergeflags, "-mips2");
    //     addstr(&uloopflags, "-mips2");
    //     addstr(&optflags, "-mips2");
    //     addstr(&genflags, "-mips2");
    //     addstr(&asflags, "-mips2");
    //     addstr(&ldflags, "-mips2");
    //     addstr(&ftocflags, "-mips2");
    // }
}
// #pragma GLOBAL_ASM("asm/5.3/functions/cc/parse_command.s")

static const char STR_10005234[] = "Internal";
static const char STR_10005240[] = "Error";
static const char STR_10005248[] = "Warning";
static const char STR_10005250[] = "Info";
static const char STR_10005258[] = "Fix";
static const char STR_1000525C[] = "";

/**
 * get_host_chiptype
 * Address: 0x0042AE80
 * VROM: 0x02AE80
 * Size: 0x14
 */
void get_host_chiptype(void) {
}

/* 0x037448 0x10000448 None */ static const char* D_10000448[] = {
    "Internal", "Error", "Warning", "Info", "Fix", "",
}; // Error category strings

/**
 * error
 * Address: 0x0042AE94
 * VROM: 0x02AE94
 * Size: 0x3C0
 */
// Print an error. Has to be K&R for the variadic stuff to work in other functions
void error(category, arg1, arg2, arg3, arg4, fmt, arg6, arg7, arg8, arg9, argA, argB)
    // clang-format off
    ErrorCategory category;
    const char* arg1;
    int arg2;
    const char* arg3;
    int arg4;
    const char* fmt;
    void* arg6;
    void* arg7;
    void* arg8;
    void* arg9;
    void* argA;
    void* argB;
// clang-format on
{
    int sp34;
    int sp30;

    if (!Vflag && (D_10000440 == NULL)) {
        D_10000440 = strrchr(progname, '/');
        if (D_10000440 == NULL) {
            D_10000440 = progname;
        } else {
            D_10000440++;
        }
        sp34 = strlen(D_10000440);
        D_10000444 = malloc(sp34 + 2);
        if (D_10000444 == NULL) {
            fprintf(stderr, "%s: Error: error (), %d: Out of memory\n", D_10000440, 12929);
            if (errno < sys_nerr) {
                fprintf(stderr, "%s: %s\n", D_10000440, sys_errlist[errno]);
            }
            exit(1);
        }

        for (sp30 = 0; sp30 < sp34; sp30++) {
            D_10000444[sp30] = ' ';
        }
        D_10000444[sp30] = '\0';
    }

    if (category == ERRORCAT_ERRNO) {
        //! @bug `D_10000444` is null if the previous block did not run.
        fprintf(stderr, "%s: ", D_10000444);
    } else {
        fprintf(stderr, "%s: %s: ", D_10000440, D_10000448[category]);
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

    if (fmt == NULL) {
        fmt = "";
    }
    fprintf(stderr, fmt, arg6, arg7, arg8, arg9, argA, argB);
}

// Macros for common selections of these three programs
#define CPP_MACRO (((cppchoice != CPP_CHOICE_1) && (cppchoice != CPP_CHOICE_3)) ? "cpp" : "acpp")
#define CCOM_MACRO ((ansichoice != ANSICHOICE_KR) ? "accom" : "ccom")
#define CFE_MACRO                                                                             \
    (((c_compiler_choice != C_COMPILER_CHOICE_0) || ((compiler == COMPILER_3) && D_100001FC)) \
         ? (alternate_fe ? "edgcpfe.eh" : "edgcpfe")                                          \
         : "cfe")

/**
 * relocate_passes
 * Address: 0x0042B254
 * VROM: 0x02B254
 * Size: 0x3F5C
 */
/**
 * List of letters used and programs affected
 * h: include, einclude, includeB
 * p: cpp
 * f: mpc, ccom, cfe, upas, fcom, upl1 (pl1fe), ucob (cobfe)
 * e: pl1err (pl1error)
 * k: ulpi
 * j: ujoin
 * u: uld
 * s: usplit
 * m: umerge
 * v: uloop
 * o: opt (uopt)
 * d: ddopt
 * q: uopt0
 * c: gen (ugen)
 * a: as0
 * b: as1
 * l: ld, patch (c++patch), filter (c++filt)
 * y: ftoc
 * z: cord
 * r: crtx, cxx_init, delta_init, crtn
 * P: lipb, libp_b
 * 1: libpl1, libpl1_b
 * E: libexc, libmld
 * W: libdw, libdw_path, libdw_b
 * X: libxmalloc, libxmalloc_b
 * C: -
 * O: libsort, libsort_b
 * n: libprof
 * M: libm, libm_b
 * F: libF77, libF77_b, libftn
 * I: libI77, libI77_b
 * S: libisam, libisam_b
 * U: libU77, libU77_b
 * t: btou, utob
 * K: fopt, copt, pfa, pca
 * Y: libI77_mp, libc_mp
 * w: prelinker (edg_prelink)
 */
void relocate_passes(char* arg0, char* arg1, char* arg2) {
    register int pad;
    register char* p;

    currcomp = "";
    if (arg2 == NULL) {
        arg2 = Bstring;
    }
    if (arg0 == NULL) {
        p = "hpfekjusmvodqcablyzrP1EXCOnMFISUtKYw";
        allBstring = arg2;
    } else {
        p = arg0;
    }
    if ((same_string(Gnum, "0")) && compose_first_G0) {
        compose_first_G0 = FALSE;
        compose_G0_libs("PE1COMFIUSXnW");
    }

    for (; *p != '\0'; p++) {
        if ((arg1 != NULL) || (strchr(alltstring, *p) == NULL)) {
            switch (*p) {
                case 'h':
                    if (includeB != NULL) {
                        free(includeB);
                    }
                    if (eincludeB != NULL) {
                        free(eincludeB);
                    }
                    if ((arg0 != NULL) || ((arg2 != NULL) && (*arg2 != '\0'))) {
                        if (arg1 != NULL) {
                            if (fiveflag) {
                                includeB = mkstr(arg1, "usr/5include", arg2, NULL);
                            } else if (abi_flag != 0) {
                                includeB = mkstr(arg1, "usr/include/abi", arg2, NULL);
                            } else {
                                eincludeB = mkstr(arg1, "usr/include/CC", arg2, NULL);
                                includeB = mkstr(arg1, "usr/include", arg2, NULL);
                            }
                        } else if (fiveflag) {
                            includeB = mkstr(comp_target_root, "usr/5include", arg2, NULL);
                        } else if (abi_flag != 0) {
                            includeB = mkstr(comp_target_root, "usr/include/abi", arg2, NULL);
                        } else {
                            eincludeB = mkstr(comp_target_root, "usr/include/CC", arg2, NULL);
                            includeB = mkstr(comp_target_root, "usr/include", arg2, NULL);
                        }
                    } else {
                        includeB = NULL;
                    }
                    break;

                case 'p':
                    if (cpp != NULL) {
                        free(cpp);
                    }
                    if (arg1 != NULL) {
                        cpp = mkstr(arg1, CPP_MACRO, arg2, NULL);
                    } else {
                        cpp = mkstr(comp_host_root, "usr/lib/", currcomp, CPP_MACRO, arg2, NULL);
                    }
                    break;

                case 'f':
                    if (mpc != NULL) {
                        free(mpc);
                    }
                    if (ccom != NULL) {
                        free(ccom);
                    }
                    if (cfe != NULL) {
                        free(cfe);
                    }
                    if (upas != NULL) {
                        free(upas);
                    }
                    if (fcom != NULL) {
                        free(fcom);
                    }
                    if (upl1 != NULL) {
                        free(upl1);
                    }
                    if (ucob != NULL) {
                        free(ucob);
                    }
                    if (arg1 != NULL) {
                        if (cmp_flag & 0x10000) {
                            mpc = mkstr(arg1, "mpc", arg2, NULL);
                        }
                        ccom = mkstr(arg1, CCOM_MACRO, arg2, NULL);
                        cfe = mkstr(arg1, CFE_MACRO, arg2, NULL);
                        upas = mkstr(arg1, "upas", arg2, NULL);
                        fcom = mkstr(arg1, "fcom", arg2, NULL);
                        upl1 = mkstr(arg1, "pl1fe", arg2, NULL);
                        ucob = mkstr(arg1, "cobfe", arg2, NULL);
                    } else {
                        if (cmp_flag & 0x10000) {
                            mpc = mkstr(comp_host_root, "usr/lib/", currcomp, "mpc", arg2, NULL);
                        }
                        ccom = mkstr(comp_host_root, "usr/lib/", currcomp, CCOM_MACRO, arg2, NULL);
                        if (((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) ||
                            ((compiler == COMPILER_3) && D_100001FC)) {
                            cfe = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, CFE_MACRO, arg2, NULL);
                        } else {
                            cfe = mkstr(comp_host_root, "usr/lib/", currcomp, CFE_MACRO, arg2, NULL);
                        }
                        upas = mkstr(comp_host_root, "usr/lib/", currcomp, "upas", arg2, NULL);
                        fcom = mkstr(comp_host_root, "usr/lib/", currcomp, "fcom", arg2, NULL);
                        upl1 = mkstr(comp_host_root, "usr/lib/", currcomp, "pl1fe", arg2, NULL);
                        ucob = mkstr(comp_host_root, "usr/lib/", currcomp, "cobfe", arg2, NULL);
                    }
                    break;

                case 'e':
                    if (pl1err != NULL) {
                        free(pl1err);
                    }
                    if (arg1 != NULL) {
                        pl1err = mkstr(arg1, "pl1error", arg2, NULL);
                    } else {
                        pl1err = mkstr(comp_host_root, "usr/lib/", currcomp, "pl1error", arg2, NULL);
                    }
                    break;

                case 'k':
                    if (ulpi != NULL) {
                        free(ulpi);
                    }
                    if (arg1 != NULL) {
                        ulpi = mkstr(arg1, "ulpi", arg2, NULL);
                    } else {
                        ulpi = mkstr(comp_host_root, "usr/lib/", currcomp, "ulpi", arg2, NULL);
                    }
                    break;

                case 'j':
                    if (ujoin != NULL) {
                        free(ujoin);
                    }
                    if (arg1 != NULL) {
                        ujoin = mkstr(arg1, "ujoin", arg2, NULL);
                    } else {
                        ujoin = mkstr(comp_host_root, "usr/lib/", currcomp, "ujoin", arg2, NULL);
                    }
                    break;

                case 'u':
                    if (uld != NULL) {
                        free(uld);
                    }
                    if (arg1 != NULL) {
                        uld = mkstr(arg1, "uld", arg2, NULL);
                    } else {
                        uld = mkstr(comp_host_root, "usr/lib/", currcomp, "uld", arg2, NULL);
                    }
                    break;

                case 's':
                    if (usplit != NULL) {
                        free(usplit);
                    }
                    if (arg1 != NULL) {
                        usplit = mkstr(arg1, "usplit", arg2, NULL);
                    } else {
                        usplit = mkstr(comp_host_root, "usr/lib/", currcomp, "usplit", arg2, NULL);
                    }
                    break;

                case 'q':
                    if (uopt0 != NULL) {
                        free(uopt0);
                    }
                    if (arg1 != NULL) {
                        uopt0 = mkstr(arg1, "uopt0", arg2, NULL);
                    } else {
                        uopt0 = mkstr(comp_host_root, "usr/lib/", currcomp, "uopt0", arg2, NULL);
                    }
                    break;

                case 'd':
                    if (ddopt != NULL) {
                        free(ddopt);
                    }
                    if (arg1 != NULL) {
                        ddopt = mkstr(arg1, "ddopt", arg2, NULL);
                    } else {
                        ddopt = mkstr(comp_host_root, "usr/lib/", currcomp, "ddopt", arg2, NULL);
                    }
                    break;

                case 'm':
                    if (umerge != NULL) {
                        free(umerge);
                    }
                    if (arg1 != NULL) {
                        umerge = mkstr(arg1, "umerge", arg2, NULL);
                    } else {
                        umerge = mkstr(comp_host_root, "usr/lib/", currcomp, "umerge", arg2, NULL);
                    }
                    break;

                case 'v':
                    if (uloop != NULL) {
                        free(uloop);
                    }
                    if (arg1 != NULL) {
                        uloop = mkstr(arg1, "uloop", arg2, NULL);
                    } else {
                        uloop = mkstr(comp_host_root, "usr/lib/", currcomp, "uloop", arg2, NULL);
                    }
                    break;

                case 'o':
                    if (opt != NULL) {
                        free(opt);
                    }
                    if (arg1 != NULL) {
                        opt = mkstr(arg1, "uopt", arg2, NULL);
                    } else if ((compiler == COMPILER_1) &&
                               ((c_compiler_choice == C_COMPILER_CHOICE_2) ||
                                (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                               (D_10000210 != 0)) {
                        opt = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "uopt", arg2, NULL);
                    } else {
                        opt = mkstr(comp_host_root, "usr/lib/", currcomp, "uopt", arg2, NULL);
                    }
                    break;

                case 'c':
                    if (gen != NULL) {
                        free(gen);
                    }
                    if (arg1 != NULL) {
                        gen = mkstr(arg1, "ugen", arg2, NULL);
                    } else if ((compiler == COMPILER_1) &&
                               ((c_compiler_choice == C_COMPILER_CHOICE_2) ||
                                (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                               (D_10000210 != 0)) {
                        gen = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "ugen", arg2, NULL);
                    } else {
                        gen = mkstr(comp_host_root, "usr/lib/", currcomp, "ugen", arg2, NULL);
                    }
                    break;

                case 'a':
                    if (as0 != NULL) {
                        free(as0);
                    }
                    if (arg1 != NULL) {
                        as0 = mkstr(arg1, "as0", arg2, NULL);
                    } else {
                        as0 = mkstr(comp_host_root, "usr/lib/", currcomp, "as0", arg2, NULL);
                    }
                    break;

                case 'b':
                    if (as1 != NULL) {
                        free(as1);
                    }
                    if (arg1 != NULL) {
                        as1 = mkstr(arg1, "as1", arg2, NULL);
                    } else if ((compiler == COMPILER_1) &&
                               ((c_compiler_choice == C_COMPILER_CHOICE_2) ||
                                (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                               (D_10000210 != 0)) {
                        as1 = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "as1", arg2, NULL);
                    } else {
                        as1 = mkstr(comp_host_root, "usr/lib/", currcomp, "as1", arg2, NULL);
                    }
                    break;

                case 'w':
                    if (prelinker != NULL) {
                        free(prelinker);
                    }
                    if (arg1 != NULL) {
                        prelinker = mkstr(arg1, "edg_prelink", arg2, NULL);
                    } else {
                        prelinker = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "edg_prelink", arg2, NULL);
                    }
                    break;

                case 'l':
                    if (ld != NULL) {
                        free(ld);
                    }
                    if (patch != NULL) {
                        free(patch);
                    }
                    if (filter != 0) {
                        free((void*)filter);
                    }
                    if (arg1 != NULL) {
                        ld = mkstr(arg1, "ld", arg2, NULL);
                        patch = mkstr(arg1, "c++patch", arg2, NULL);
                        filter = mkstr(arg1, "c++filt", arg2, NULL);
                    } else {
                        if ((compiler == COMPILER_1) &&
                            ((c_compiler_choice == C_COMPILER_CHOICE_2) ||
                             (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                            (D_10000210 != 0)) {
                            ld = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "ld", arg2, NULL);
                        } else if (irix4 != 0) {
                            ld = mkstr(comp_host_root, "usr/bin/", currcomp, "ld", arg2, NULL);
                        } else {
                            ld = mkstr(comp_host_root, "usr/lib/", currcomp, "ld", arg2, NULL);
                        }
                        patch = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "c++patch", arg2, NULL);
                        filter = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "c++filt", arg2, NULL);
                    }
                    break;

                case 't':
                    if (btou != NULL) {
                        free(btou);
                    }
                    if (utob != NULL) {
                        free(utob);
                    }
                    if (arg1 != NULL) {
                        btou = mkstr(arg1, "btou", arg2, NULL);
                        utob = mkstr(arg1, "utob", arg2, NULL);
                    } else {
                        btou = mkstr(comp_host_root, "usr/lib/", currcomp, "btou", arg2, NULL);
                        utob = mkstr(comp_host_root, "usr/lib/", currcomp, "utob", arg2, NULL);
                    }
                    break;

                case 'y':
                    if (ftoc != NULL) {
                        free(ftoc);
                    }
                    if (arg1 != NULL) {
                        ftoc = mkstr(arg1, "ftoc", arg2, NULL);
                    } else {
                        ftoc = mkstr(comp_host_root, "usr/lib/", currcomp, "ftoc", arg2, NULL);
                    }
                    break;

                case 'z':
                    if (cord != NULL) {
                        free(cord);
                    }
                    if (arg1 != NULL) {
                        cord = mkstr(arg1, "cord", arg2, NULL);
                    } else {
                        cord = mkstr(comp_host_root, "usr/bin/", currcomp, "cord", arg2, NULL);
                    }
                    break;

                case 'r':
                    if (arg1 != NULL) {
                        if (pflag != 0) {
                            crtx = mkstr(arg1, MCRTX, arg2, NULL);
                            cxx_init = mkstr(arg1, "c++init.o", arg2, NULL);
                            delta_init = mkstr(arg1, "delta_init.o", arg2, NULL);
                            crtn = mkstr(arg1, "crtn.o", arg2, NULL);
                        } else {
                            crtx = mkstr(arg1, CRTX, arg2, NULL);
                            cxx_init = mkstr(arg1, "c++init.o", arg2, NULL);
                            delta_init = mkstr(arg1, "delta_init.o", arg2, NULL);
                            crtn = mkstr(arg1, "crtn.o", arg2, NULL);
                        }
                    } else if (pflag != 0) {
                        if (abi_flag != 0) {
                            crtx = func_004339C8(mkstr(MCRTX, arg2, NULL), dirs_for_abi_crtn.entries);
                            crtn = func_004339C8(mkstr("crtn.o", arg2, NULL), dirs_for_abi_crtn.entries);
                            cxx_init = func_004339C8(mkstr("c++init.o", arg2, NULL), dirs_for_abi_crtn.entries);
                            delta_init = func_004339C8(mkstr("delta_init.o", arg2, NULL), dirs_for_abi_crtn.entries);
                        } else if (non_shared) {
                            crtx = func_004339C8(mkstr(MCRTX, arg2, NULL), dirs_for_nonshared_crtn.entries);
                            crtn = func_004339C8(mkstr("crtn.o", arg2, NULL), dirs_for_nonshared_crtn.entries);
                            cxx_init = func_004339C8(mkstr("c++init.o", arg2, NULL), dirs_for_nonshared_crtn.entries);
                            delta_init =
                                func_004339C8(mkstr("delta_init.o", arg2, NULL), dirs_for_nonshared_crtn.entries);
                        } else {
                            crtx = func_004339C8(mkstr(MCRTX, arg2, NULL), dirs_for_crtn.entries);
                            crtn = func_004339C8(mkstr("crtn.o", arg2, NULL), dirs_for_crtn.entries);
                            cxx_init = func_004339C8(mkstr("c++init.o", arg2, NULL), dirs_for_crtn.entries);
                            delta_init = func_004339C8(mkstr("delta_init.o", arg2, NULL), dirs_for_crtn.entries);
                        }
                    } else if (abi_flag != 0) {
                        crtx = func_004339C8(CRTX, dirs_for_abi_crtn.entries);
                        crtn = func_004339C8("crtn.o", dirs_for_abi_crtn.entries);
                        cxx_init = func_004339C8("c++init.o", dirs_for_abi_crtn.entries);
                        delta_init = func_004339C8("delta_init.o", dirs_for_abi_crtn.entries);
                    } else if (non_shared) {
                        crtx = func_004339C8(CRTX, dirs_for_nonshared_crtn.entries);
                        crtn = func_004339C8("crtn.o", dirs_for_nonshared_crtn.entries);
                        cxx_init = func_004339C8("c++init.o", dirs_for_nonshared_crtn.entries);
                        delta_init = func_004339C8("delta_init.o", dirs_for_nonshared_crtn.entries);
                    } else {
                        crtx = func_004339C8(CRTX, dirs_for_crtn.entries);
                        crtn = func_004339C8("crtn.o", dirs_for_crtn.entries);
                        cxx_init = func_004339C8("c++init.o", dirs_for_crtn.entries);
                        delta_init = func_004339C8("delta_init.o", dirs_for_crtn.entries);
                    }
                    break;

                case 'P':
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && (*arg2 != '\0')) {
                            libp = mkstr("-L", arg1, "-B", arg2, LibP, NULL);
                        } else {
                            libp = mkstr("-L", arg1, LibP, NULL);
                        }
                        libp_b = mkstr(arg1, "libp.b", arg2, NULL);
                    } else {
                        libp = "-lp";
                        if (non_shared) {
                            libp_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libp.b", arg2, NULL);
                        } else {
                            libp_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libp.b", arg2, NULL);
                        }
                    }
                    break;

                case '1':
                    if (arg1 != NULL) {
                        libpl1 = mkstr(arg1, LibPl1, arg2, NULL);
                        libpl1_b = mkstr(arg1, "libpl1.b", arg2, NULL);
                    } else {
                        libpl1 = "-lpl1";
                        if (non_shared) {
                            libpl1_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libpl1.b", arg2, NULL);
                        } else {
                            libpl1_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libpl1.b", arg2, NULL);
                        }
                    }
                    break;

                case 'E':
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && (*arg2 != '\0')) {
                            libexc = mkstr("-L", arg1, "-B", arg2, LibExc, NULL);
                            libmld = mkstr("-L", arg1, "-B", arg2, LibMld, NULL);
                        } else {
                            libexc = mkstr("-L", arg1, LibExc, NULL);
                            libmld = mkstr("-L", arg1, LibMld, NULL);
                        }
                        libexc_b = mkstr(arg1, "libexc.b", arg2, NULL);
                    } else {
                        if ((arg2 != NULL) && (*arg2 != '\0')) {
                            libexc = mkstr("-L", "-B", arg2, LibExc, NULL);
                            libmld = mkstr("-L", "-B", arg2, LibMld, NULL);
                        } else {
                            libexc = "-lexc";
                            libmld = "-lmld";
                        }
                        if (non_shared) {
                            libexc_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libexc.b", arg2, NULL);
                        } else {
                            libexc_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libexc.b", arg2, NULL);
                        }
                    }
                    break;

                case 'W':
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && (*arg2 != '\0')) {
                            libdw = mkstr("-L", arg1, "-B", arg2, LibDw, NULL);
                        } else {
                            libdw = mkstr("-L", arg1, LibDw, NULL);
                        }
                        libdw_path = mkstr(arg1, "libdw.a", arg2, NULL);
                        libdw_b = mkstr(arg1, "libdw.b", arg2, NULL);
                    } else {
                        if ((arg2 != NULL) && (*arg2 != '\0')) {
                            if (non_shared) {
                                libdw = mkstr("-L", comp_target_root, "usr/lib/nonshared/", currcomp, " -B", arg2,
                                              LibDw, NULL);
                            } else {
                                libdw = mkstr("-L", comp_target_root, "usr/lib/", currcomp, " -B", arg2, LibDw, NULL);
                            }
                        } else if (non_shared) {
                            libdw = mkstr("-L", comp_target_root, "usr/lib/", currcomp, LibDw, NULL);
                        } else {
                            libdw = mkstr("-L", comp_target_root, "usr/lib/", currcomp, LibDw, NULL);
                        }
                        if (non_shared) {
                            libdw_path = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libdw.a", arg2, NULL);
                            libdw_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libdw.b", arg2, NULL);
                        } else {
                            libdw_path = mkstr(comp_target_root, "usr/lib/", currcomp, "libdw.a", arg2, NULL);
                            libdw_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libdw.b", arg2, NULL);
                        }
                    }
                    break;

                case 'X':
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && (*arg2 != '\0')) {
                            libxmalloc = mkstr("-L", arg1, " -B", arg2, LibXmalloc, NULL);
                        } else {
                            libxmalloc = mkstr("-L", arg1, LibXmalloc, NULL);
                        }
                        libxmalloc_b = mkstr(arg1, "libxmalloc.b", arg2, NULL);
                    } else {
                        libxmalloc = "-lxmalloc";
                        if (non_shared) {
                            libxmalloc_b =
                                mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libxmalloc.b", arg2, NULL);
                        } else {
                            libxmalloc_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libxmalloc.b", arg2, NULL);
                        }
                    }
                    break;

                case 'O':
                    if (arg1 != NULL) {
                        libsort = mkstr(arg1, LibSort, arg2, NULL);
                        libsort_b = mkstr(arg1, "libsort.b", arg2, NULL);
                    } else {
                        libsort = "-lsort";
                        if (non_shared) {
                            libsort_b =
                                mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libsort.b", arg2, NULL);
                        } else {
                            libsort_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libsort.b", arg2, NULL);
                        }
                    }
                    break;

                case 'n':
                    if (pflag != 0) {
                        if (arg1 != NULL) {
                            if ((arg2 != NULL) && (*arg2 != '\0')) {
                                libprof = mkstr("-L", arg1, " -B", arg2, LibProf1, NULL);
                            } else {
                                libprof = mkstr("-L", arg1, LibProf1, NULL);
                            }
                        } else if (non_shared) {
                            libprof = func_004339C8("libprof.a", dirs_for_nonshared_crtn.entries);
                        } else {
                            libprof = func_004339C8("libprof.a", dirs_for_crtn.entries);
                        }
                    }
                    break;

                case 'M':
                    if (arg1 != NULL) {
                        switch (chip_targ) {        /* switch 2; irregular */
                            default:                /* switch 2 */
                            case CHIP_TARGET_MIPS1: /* switch 2 */
                                if ((arg2 != NULL) && (*arg2 != '\0')) {
                                    libm = mkstr(arg1, " -B", arg2, LibM, NULL);
                                } else {
                                    libm = mkstr("-L", arg1, LibM, NULL);
                                }
                                libm_b = mkstr(arg1, "libm.b", arg2, NULL);
                                break;

                            case CHIP_TARGET_MIPS2: /* switch 2 */
                                libm = mkstr(arg1, "libm_mips2.a", arg2, NULL);
                                libm_b = mkstr(arg1, "libm_mips2.b", arg2, NULL);
                                break;

                            case CHIP_TARGET_MIPS3: /* switch 2 */
                                libm = mkstr(arg1, "libm_mips3.a", arg2, NULL);
                                libm_b = mkstr(arg1, "libm_mips3.b", arg2, NULL);
                                break;
                        }
                    } else {
                        switch (chip_targ) { /* switch 1; irregular */
                            default:         /* switch 1 */
                            case 0:          /* switch 1 */
                                libm = "-lm";
                                if (non_shared) {
                                    libm_b =
                                        mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm.b", arg2, NULL);
                                } else {
                                    libm_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libm.b", arg2, NULL);
                                }
                                break;

                            case 1: /* switch 1 */
                                if (non_shared) {
                                    libm = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm_mips2.a", arg2,
                                                 NULL);
                                    libm_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm_mips2.b",
                                                   arg2, NULL);
                                } else {
                                    libm = mkstr(comp_target_root, "usr/lib/", currcomp, "libm_mips2.a", arg2, NULL);
                                    libm_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libm_mips2.b", arg2, NULL);
                                }
                                break;

                            case 2: /* switch 1 */
                                if (non_shared) {
                                    libm = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm_mips3.a", arg2,
                                                 NULL);
                                    libm_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm_mips3.b",
                                                   arg2, NULL);
                                } else {
                                    libm = mkstr(comp_target_root, "usr/lib/", currcomp, "libm_mips3.a", arg2, NULL);
                                    libm_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libm_mips3.b", arg2, NULL);
                                }
                                break;
                        }
                    }
                    break;

                case 'F':
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && (*arg2 != '\0')) {
                            libF77 = mkstr("-L", arg1, " -B", arg2, LibF77, NULL);
                        } else {
                            libF77 = mkstr("-L", arg1, LibF77, NULL);
                        }
                        libF77_b = mkstr(arg1, "libF77.b", arg2, NULL);
                    } else {
                        libftn = "-lftn";
                        libF77 = "-lF77";
                        if (non_shared) {
                            libF77_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libF77.b", arg2, NULL);
                        } else {
                            libF77_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libF77.b", arg2, NULL);
                        }
                    }
                    break;

                case 'I':
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && (*arg2 != '\0')) {
                            libI77 = mkstr("-L", arg1, " -B", arg2, LibI77, NULL);
                        } else {
                            libI77 = mkstr("-L", arg1, LibI77, NULL);
                        }
                        libI77_b = mkstr(arg1, "libI77.b", arg2, NULL);
                    } else {
                        libI77 = "-lI77";
                        if (non_shared) {
                            libI77_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libI77.b", arg2, NULL);
                        } else {
                            libI77_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libI77.b", arg2, NULL);
                        }
                    }
                    break;

                case 'S':
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && (*arg2 != '\0')) {
                            libisam = mkstr("-L", arg1, " -B", arg2, LibIsam, NULL);
                        } else {
                            libisam = mkstr("-L", arg1, LibIsam, NULL);
                        }
                        libisam_b = mkstr(arg1, "libisam.b", arg2, NULL);
                    } else {
                        libisam = "-lisam";
                        if (non_shared) {
                            libisam_b =
                                mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libisam.b", arg2, NULL);
                        } else {
                            libisam_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libisam.b", arg2, NULL);
                        }
                    }
                    break;

                case 'U':
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && (*arg2 != '\0')) {
                            libU77 = mkstr("-L", arg1, " -B", arg2, LibU77, NULL);
                        } else {
                            libU77 = mkstr("-L", arg1, LibU77, NULL);
                        }
                        libU77_b = mkstr(arg1, "libU77.b", arg2, NULL);
                    } else {
                        libU77 = "-lU77";
                        if (non_shared) {
                            libU77_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libU77.b", arg2, NULL);
                        } else {
                            libU77_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libU77.b", arg2, NULL);
                        }
                    }
                    break;

                case 'K':
                    if (arg1 != NULL) {
                        fopt = mkstr(arg1, "fopt", arg2, NULL);
                        copt = mkstr(arg1, "copt", arg2, NULL);
                        pfa = mkstr(arg1, "pfa", arg2, NULL);
                        pca = mkstr(arg1, "pca", arg2, NULL);
                    } else {
                        fopt = mkstr(comp_host_root, "usr/lib/", "fopt", arg2, NULL);
                        copt = mkstr(comp_host_root, "usr/lib/", "copt", arg2, NULL);
                        pfa = mkstr(comp_host_root, "usr/lib/", "pfa", arg2, NULL);
                        pca = mkstr(comp_host_root, "usr/lib/", "pca", arg2, NULL);
                    }
                    break;

                case 'Y':
                    if (arg1 != NULL) {
                        libI77_mp = mkstr(arg1, "libI77_mp.a", arg2, NULL);
                        libc_mp = mkstr(arg1, "libc_mp.a", arg2, NULL);
                    } else {
                        libI77_mp = "-lI77_mp";
                        libc_mp = "-lc_mp";
                    }
                    break;

                case 'C':
                    break;

                default:
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "Unknown character in -t%c\n", *p);
                    exit(2);
                    break;
            }
        }
    }
}

/**
 * newrunlib
 * Address: 0x0042F1B0
 * VROM: 0x02F1B0
 * Size: 0x11C
 */
void newrunlib(void) {
    if (fiveflag) {
        runlib_base = "usr/5lib";
    } else if (irix4) {
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

/**
 * compose_G0_libs
 * Address: 0x0042F2CC
 * VROM: 0x02F2CC
 * Size: 0x30C
 */
void compose_G0_libs(char* arg0) {
    for (; *arg0 != 0; arg0++) {
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

/**
 * compose_reg_libs
 * Address: 0x0042F5D8
 * VROM: 0x02F5D8
 * Size: 0x2DC
 */
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
                break;

            case 'X':
                LibXmalloc = mkstr("libxmalloc", ".a", NULL);
                break;
        }
    }
}

// Defines from Open64 string_utils.c. TODO: decide whether to use them.
#define BLANK ' '
#define DOT '.'
#define SLASH '/'
#define PERCENT '%'

#define _VA_INIT_STATE 1
/**
 * mkstr
 * Address: 0x0042F8B4
 * VROM: 0x02F8B4
 * Size: 0x214
 */
// Actual prototype is char* mkstr(const char*, ...);
#ifndef PERMUTER
// Return the concatenation of the passed strings. Arguments are a NULL-terminated list of const char*.
char* mkstr(va_alist)
    // clang-format off
va_dcl // K&R syntax
// clang-format on
{
    register char* ret;
    register const char* arg;
    register size_t len = 1;
    va_list args;

    va_start(args);
    while ((arg = va_arg(args, const char*)) != NULL) {
        len += strlen(arg);
    }
    va_end(args);

    ret = malloc(len);
    if (ret == NULL) {
        error(ERRORCAT_ERROR, NULL, 0, "mkstr ()", 14103, "out of memory\n");
        if (errno < sys_nerr) {
            error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
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
#endif

/**
 * mklist
 * Address: 0x0042FAC8
 * VROM: 0x02FAC8
 * Size: 0x130
 */
// Initialise a specified string_list with capacity LIST_INITIAL_CAPACITY and length 0.
void mklist(string_list* list) {
    if ((list->entries = malloc(LIST_INITIAL_CAPACITY * sizeof(char*))) == NULL) {
        error(ERRORCAT_ERROR, NULL, 0, "mklist ()", 14140, "out of memory\n");
        if (errno < sys_nerr) {
            error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        exit(1);
    }

    list->capacity = LIST_INITIAL_CAPACITY;
    list->length = 0;
    *list->entries = NULL;
}

/**
 * addstr
 * Address: 0x0042FBF8
 * VROM: 0x02FBF8
 * Size: 0x194
 */
// Add a single string entry to a string_list.
void addstr(string_list* list, string str) {
    if ((list->length + 1) >= list->capacity) {
        if ((list->entries = realloc(list->entries, (list->capacity + LIST_CAPACITY_INCR) * sizeof(char*))) == 0) {
            error(ERRORCAT_ERROR, NULL, 0, "addstr()", 14174, "out of memory\n");
            if (errno < sys_nerr) {
                error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
            }
            exit(1);
        }
        list->capacity += LIST_CAPACITY_INCR;
    }
    list->entries[list->length] = str;
    list->length++;
    list->entries[list->length] = NULL;
}

/**
 * addspacedstr
 * Address: 0x0042FD8C
 * VROM: 0x02FD8C
 * Size: 0x1E8
 */
/**
 * Add a space-separated string to a string_list, dividing it up into separate entries by space characters (' ')
 *
 * @param list List to add the entries to
 * @param str Space-separated string to add
 */
void addspacedstr(string_list* list, char* str) {
    char* str_end = str;

    do {
        str_end = strchr(str_end, ' ');
        if (str_end != NULL) {
            *str_end = '\0';
            str_end++;
        }
        if ((list->length + 1) >= list->capacity) {
            if ((list->entries = realloc(list->entries, (list->capacity + LIST_CAPACITY_INCR) * sizeof(char*))) ==
                NULL) {
                error(ERRORCAT_ERROR, NULL, 0, "addspacedstr()", 14218, "out of memory\n");
                if (errno < sys_nerr) {
                    error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
                }
                exit(1);
            }
            list->capacity += LIST_CAPACITY_INCR;
        }
        list->entries[list->length] = str;
        list->length++;
        list->entries[list->length] = NULL;
    } while ((str = str_end) != NULL);
}

/**
 * newstr
 * Address: 0x0042FF74
 * VROM: 0x02FF74
 * Size: 0xA4
 */
/**
 * Copy a string
 *
 * @param s string to copy
 * @return char* mallocked pointer to copy
 * @note Similar to `string_copy` in Open64 `string_utils.c`
 */
char* newstr(char* s) {
    char* new = malloc(strlen(s) + 1);

    if (new != NULL) {
        strcpy(new, s);
    } else {
        //! @bug Called incorrectly (fixed in 7.1)
        error("newstr: unable to malloc for string %s\n", s);
    }
    return new;
}

/**
 * save_place
 * Address: 0x00430018
 * VROM: 0x030018
 * Size: 0x184
 */
/**
 * Add one new uninitialised entry to a string_list
 *
 * @param list string_list to add it to
 * @return int index of new entry
 */
int save_place(string_list* list) {
    int new_entry_index;

    if ((list->length + 1) >= list->capacity) {

        if ((list->entries = realloc(list->entries, (list->capacity + LIST_CAPACITY_INCR) * sizeof(char*))) == NULL) {
            error(ERRORCAT_ERROR, NULL, 0, "save_place()", 14271, "out of memory\n");
            if (errno < sys_nerr) {
                error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
            }
            exit(1);
        }
        list->capacity += LIST_CAPACITY_INCR;
    }
    new_entry_index = list->length;
    list->length++;
    list->entries[list->length] = NULL;
    return new_entry_index;
}

/**
 * set_place
 * Address: 0x0043019C
 * VROM: 0x03019C
 * Size: 0xC4
 */
/**
 * Set a specified entry of a string_list to a particular string
 *
 * @param list string_list to set entry of
 * @param str string to set entry to
 * @param place entry to write to
 */
void set_place(string_list* list, char* str, int place) {
    if ((place < 0) || (place >= list->length)) {
        error(ERRORCAT_INTERNAL, NULL, 0, "set_place ()", 14302, "place out of range");
        exit(1);
    }
    list->entries[place] = str;
}

/**
 * addlist
 * Address: 0x00430260
 * VROM: 0x030260
 * Size: 0x214
 */
// Append the entries from `b` to `a`.
void addlist(string_list* a, string_list* b) {
    int i;

    if ((a->length + b->length + 1) >= a->capacity) {

        if ((a->entries = realloc(a->entries, (a->capacity + b->capacity + LIST_CAPACITY_INCR) * sizeof(char*))) ==
            NULL) {
            error(ERRORCAT_ERROR, NULL, 0, "addlist ()", 14332, "out of memory\n");
            if (errno < sys_nerr) {
                error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
            }
            exit(1);
        }
        a->capacity += b->capacity + LIST_CAPACITY_INCR;
    }
    for (i = 0; i < b->length; i++) {
        if (b->entries[i] != NULL) {
            a->entries[a->length] = b->entries[i];
            a->length++;
        }
    }
    a->entries[a->length] = NULL;
}

/**
 * adduldlist
 * Address: 0x00430474
 * VROM: 0x030474
 * Size: 0x384
 */
/**
 * Adds entries from `b` and `c` onto the end of `a`:
 * - up to the first NULL from `c`,
 * - then everything from `b`,
 * - then the rest of `c`.
 */
void adduldlist(string_list* a, string_list* b, string_list* c) {
    int ic;
    int ib;

    if ((a->length + b->length + c->length + 1) >= a->capacity) {

        if ((a->entries = realloc(a->entries, ((a->capacity + b->capacity + c->capacity) + LIST_CAPACITY_INCR) *
                                                  sizeof(char*))) == NULL) {
            error(ERRORCAT_ERROR, NULL, 0, "addlist ()", 14371, "out of memory\n");
            if (errno < sys_nerr) {
                error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
            }
            exit(1);
        }
        a->capacity += b->capacity + c->capacity + LIST_CAPACITY_INCR;
    }

    for (ic = 0; (ic < c->length) && (c->entries[ic] != NULL); ic++) {
        a->entries[a->length] = c->entries[ic];
        a->length++;
    }

    for (ib = 0; ib < b->length; ib++) {
        if (b->entries[ib] != NULL) {
            a->entries[a->length] = b->entries[ib];
            a->length++;
        }
    }

    for (; ic < c->length; ic++) {
        if (c->entries[ic] != NULL) {
            a->entries[a->length] = c->entries[ic];
            a->length++;
        }
    }

    a->entries[a->length] = NULL;
}

/**
 * nodup
 * Address: 0x004307F8
 * VROM: 0x0307F8
 * Size: 0xBC
 */
/**
 * Search for a string in a string_list.
 *
 * @return int boolean, TRUE if not found
 */
/* boolean */ int nodup(string_list* list, const /* string */ char* s) {
    register int i;
    register char* entry;

    for (i = 0; i < list->length; i++) {
        entry = list->entries[i];
        if ((entry != NULL) && same_string(entry, s)) {
            return FALSE;
        }
    }
    return TRUE;
}

/**
 * getsuf
 * Address: 0x004308B4
 * VROM: 0x0308B4
 * Size: 0x258
 */
/**
 * Find the file extension (suffix) of a path.
 * - Most single-letter extensions will be returned as-is (with the exception of 'C').
 * - Most multi-letter extensions are checked in the `suffixes` table and a special value is returned.
 * - "for" -> 'f' and "FOR" -> 'F'.
 * - If extension is not recognised, return '\0'.
 * .
 * @param path path to find the extension of
 * @return char path's extension or special case (see enum)
 */
char getsuf(const /* string */ char* path) {
    int basename_len = 0;
    int i;
    char ch;
    const char* str = path;

    // Look for the start of the path's basename and find its length.
    while (ch = *path++) { // != '\0'
        if (ch == '/') {
            basename_len = 0;
            str = path;
        } else {
            basename_len++;
        }
    }
    // `path` now points to after the trailing '\0'

    // no room for a suffix
    if (basename_len <= 2) {
        return '\0';
    }

    // Single-letter suffix
    if (path[-3] == '.') {
        if (path[-2] == 'C') { // "*.C"
            return 6;
        } else { // Any other single letter
            return path[-2];
        }
    }

    // Multi-letter suffix, look backwards through basename for the last '.'
    for (i = basename_len - 2; i > 0; i--) {
        if (str[i] == '.') {
            break;
        }
    }

    // if no '.' found, no suffix.
    if (i == 0) {
        return '\0';
    }

    // Search table for suffix.
    str = &str[i + 1];
    for (i = 0; suffixes[i].name != NULL; i++) {
        if (same_string(str, suffixes[i].name)) {
            return suffixes[i].suffix;
        }
    }

    // Special case for "for"/"FOR".
    if (same_string(str, "for")) {
        return 'f';
    }
    if (same_string(str, "FOR")) {
        return 'F';
    }

    // Suffix not recognised.
    return '\0';
}

/**
 * mksuf
 * Address: 0x00430B0C
 * VROM: 0x030B0C
 * Size: 0x3B0
 */
/**
 * Given a file path and a value, returns a basename with an extension specified by the value.
 *
 * @param path Path to start with
 * @param value Value of suffix. Values smaller than 8 will be looked up in the `suffixes` table
 * @return char* basename of `path` with extension attached
 */
char* mksuf(const char* path, char value) {
    int i;                      // sp54, also basename length
    int k;                      // sp50
    size_t new_suf_length;      // sp4C
    char* sp48;                 // Iterator used to find start of new basename
    char* sp44;                 // various uses: pointing to end of new copy of `path`, used for return
    char* sp40;                 // Start of copied basename, then start of copied extension
    const char* new_suf = NULL; // sp3C
    char ch;                    // sp38

    if (value < 8) { // Special cases covered by the table
        for (i = 0; suffixes[i].name != NULL; i++) {
            if (suffixes[i].suffix == value) {
                new_suf = suffixes[i].name;
                break;
            }
        }

        if (new_suf == NULL) {
            //! @bug: %s used for printing a char.
            error(ERRORCAT_INTERNAL, NULL, 0, "mksuf ()", 14514, "passed an unknown suffix value: %s\n", value);
            exit(4);
        }
        new_suf_length = strlen(new_suf);
    } else {
        new_suf_length = 0;
    }

    i = 0;
    sp40 = sp44 = sp48 = savestr(path, new_suf_length);

    // Look for the start of the (copied) path's basename
    while (ch = *sp44++) {
        if (ch == '/') {
            i = 0;
            sp40 = sp44;
        } else {
            i++;
        }
    }
    // `sp40` now points to start of basename,
    // `sp44` to after the trailing '\0',
    // `i` is basename length

    if ((i >= 3) && (sp44[-3] == '.')) { // Path currently has a single-letter extension
        if (value < 8) {                 // Copy extension from table
            strcpy(sp44 - 2, new_suf);
        } else { // set single-letter extension from `value`
            sp44[-2] = value;
            sp44[-1] = 0;
        }
    } else { // no extension or a longer one
             // Look backwards through basename for last '.'
        for (k = i - 2; k > 0; k--) {
            if (sp40[k] == '.') {
                break;
            }
        }

        // If no extension, error out
        if (k == 0) {
            error(ERRORCAT_ERROR, NULL, 0, "mksuf ()", 14553, "Bad file name, no suffix: %s\n", path);
            exit(4);
        }

        // move to start of current extension
        sp40 = &sp40[k + 1];
        // Replace extension
        if (value < 8) { // Copy from table
            strcpy(sp40, new_suf);
        } else { // set single-letter extension from `value`
            sp40[0] = value;
            sp40[1] = 0;
        }
    }

    sp44 = sp48; // sp44 to start of copied path
    // Find start of new basename
    while (*sp48 != '\0') {
        if (*sp48++ == '/') {
            sp44 = sp48;
        }
    }
    // return new basename
    return sp44;
}

/**
 * savestr
 * Address: 0x00430EBC
 * VROM: 0x030EBC
 * Size: 0x140
 */
// Copy a string, adding extra_length bytes to the allocation.
/* string */ char* savestr(const /* string */ char* src, size_t extra_length) {
    char* dest = malloc(strlen(src) + extra_length + 1);

    if (dest == NULL) {
        error(ERRORCAT_ERROR, NULL, 0, "savestr ()", 14590, "out of memory\n");
        if (errno < sys_nerr) {
            error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        exit(1);
    }
    strcpy(dest, src);
    return dest;
}

/**
 * mktempstr
 * Address: 0x00430FFC
 * VROM: 0x030FFC
 * Size: 0x930
 */
void mktempstr(void) {
    tempstr[0] = mktemp(mkstr(tmpdir, "ctmstXXXXXX", NULL));
    tempstr[1] = mktemp(mkstr(tmpdir, "ctmuXXXXXX", NULL));
    tempstr[2] = mktemp(mkstr(tmpdir, "ctmpXXXXXX", NULL));
    tempstr[3] = mktemp(mkstr(tmpdir, "ctmfXXXXXX", NULL));
    tempstr[4] = mktemp(mkstr(tmpdir, "ctmluXXXXXX", NULL));
    tempstr[5] = mktemp(mkstr(tmpdir, "ctmsXXXXXX", NULL));
    tempstr[6] = mktemp(mkstr(tmpdir, "ctmmXXXXXX", NULL));
    tempstr[7] = mktemp(mkstr(tmpdir, "ctmoXXXXXX", NULL));
    tempstr[8] = mktemp(mkstr(tmpdir, "ctmosXXXXXX", NULL));
    tempstr[9] = mktemp(mkstr(tmpdir, "ctmcbXXXXXX", NULL));
    tempstr[10] = mktemp(mkstr(tmpdir, "ctmcXXXXXX", NULL));
    tempstr[11] = mktemp(mkstr(tmpdir, "ctmaXXXXXX", NULL));
    tempstr[12] = mktemp(mkstr(tmpdir, "ctmbXXXXXX", NULL));
    tempstr[13] = mktemp(mkstr(tmpdir, "ctmlXXXXXX", NULL));
    tempstr[14] = mktemp(mkstr(tmpdir, "ctmm4XXXXXX", NULL));
    tempstr[15] = mktemp(mkstr(tmpdir, "ctmgtXXXXXX", NULL));
    tempstr[16] = mktemp(mkstr(tmpdir, "ctmilXXXXXX", NULL));
    tempstr[17] = mktemp(mkstr(tmpdir, "ctmltXXXXXX", NULL));
    tempstr[18] = mktemp(mkstr(tmpdir, "ctmp1XXXXXX", NULL));
    tempstr[20] = mktemp(mkstr(tmpdir, "ctmpdXXXXXX", NULL));
    tempstr[19] = mktemp(mkstr(tmpdir, "ctmddXXXXXX", NULL));
    tempstr[21] = mktemp(mkstr(tmpdir, "ctmloXXXXXX", NULL));
    tempstr[22] = mktemp(mkstr(tmpdir, "ctmciXXXXXX", NULL));
    tempstr[23] = mktemp(mkstr(tmpdir, "ctmvXXXXXX", NULL));
    tempstr[24] = mktemp(mkstr(tmpdir, "ctmerrXXXXXX", NULL));
    tempstr[25] = mktemp(mkstr(tmpdir, "ctmemXXXXXX", NULL));
    tempstr[26] = mktemp(mkstr(tmpdir, "ctmeXXXXXX", NULL));
    tempstr[27] = mktemp(mkstr(tmpdir, "ctmdXXXXXX", NULL));
    tempstr[28] = mktemp(mkstr(tmpdir, "ctmqXXXXXX", NULL));
    tempstr[29] = mktemp(mkstr(tmpdir, "ctmqsXXXXXX", NULL));
    tempstr[30] = mktemp(mkstr(tmpdir, "ctmelfXXXXX", NULL));
    tempstr[31] = mktemp(mkstr(tmpdir, "ctmkXXXXXX", NULL));
    tempstr[33] = mktemp(mkstr(tmpdir, "ctmcmdXXXXXX", NULL));

    if ((compiler == COMPILER_1) &&
        ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3)) && !nofilt &&
        (access(filter, EX_OK) == 0)) {
        tempstr[32] = mktemp(mkstr(tmpdir, "ctmfiltXXXXXX", NULL));
    } else {
        tempstr[32] = NULL;
    }
}

/**
 * run
 * Address: 0x0043192C
 * VROM: 0x03192C
 * Size: 0xD34
 */
/**
 * Run a program, possibly duplicating stdin/stdout/stderr, and with the option of running memory analysis.
 *
 * @param name Name of program to run.
 * @param argv Arguments to pass (as an `argv`-style string list).
 * @param input File to dup `stdin` to.
 * @param output File to dup `stdout` to.
 * @param err_output File to dup `stderr` to.
 * @return int 0 on success, -1 on failure.
 *
 * @remark This was clearly used as a basis for Open64's `run_phase`.
 */
int run(char* name, char* const argv[], char* input, char* output, char* err_output) {
    char* const* p;       // spA4
    int forkpid;          // spA0
    int waitpid;          // sp9C
    int termsig;          // sp98
    int fdin;             // sp94
    int fdout;            // sp90
    int fderr;            // sp8C
    int sigterm;          // sp88
    int sigint;           // sp84
    int waitstatus;       // sp80
    int num_maps;         // sp7C
    const char* prodname; // sp78

    if (vflag) {
        fprintf(stderr, "%s ", name);
        p = argv + 1;
        while (*p != NULL) {
            fprintf(stderr, "%s ", *p++);
        }
        if (input != NULL) {
            fprintf(stderr, "< %s ", input);
        }
        if (output != 0) {
            fprintf(stderr, "> %s ", output);
        }
        fprintf(stderr, "\n");
        settimes();
    }

    if (!execute_flag) {
        return 0;
    }

    if (memory_flag != 0) {
        if (pipe(B_1000A458) < 0) {
            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "pipe failed for -showm");
            return -1;
        }
    }

    forkpid = fork();
    if (forkpid == -1) {
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "no more processes\n");
        if (errno < sys_nerr) {
            error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        return -1;
    }

    if (forkpid == 0) {
        /* child */
        /* if we want memory stats, we have to wait for
           parent to connect to our /proc */
        if (memory_flag) {
            func_004365B8();
        }

        if (input != NULL) {
            if ((fdin = open(input, O_RDONLY)) == -1) {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't open input file: %s\n", input);
                if (errno < sys_nerr) {
                    error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
                }
                cleanup();
                exit(1);
                /* NOTREACHED */
            }
            dup2(fdin, fileno(stdin));
        }

        if (output != NULL) {
            fdout = creat(output, 0666);
            if (fdout == -1) {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't create output file: %s\n", output);
                if (errno < sys_nerr) {
                    error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
                }
                cleanup();
                exit(1);
                /* NOTREACHED */
            }
            dup2(fdout, fileno(stdout));
        }

        if (err_output != NULL) {
            fderr = creat(err_output, 0666);
            if (fderr == -1) {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't create error file: %s\n", err_output);
                if (errno < sys_nerr) {
                    error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
                }
                cleanup();
                exit(1);
                /* NOTREACHED */
            }
            dup2(fderr, fileno(stderr));
        }

        execvp(name, argv);
        prodname = func_00434094(name, TRUE);
        if ((errno == ENOENT) && (prodname != NULL)) {
            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "%s is not installed (could not find %s).\n", prodname, name);
        } else {
            prodname = func_00434094(name, FALSE);
            if ((errno == ENOENT) && (prodname != NULL)) {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "%s may not be installed (could not find %s).\n", prodname,
                      name);
            } else {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't find or exec: %s\n", name);
                if (errno < sys_nerr) {
                    error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
                }
            }
        }
        cleanup();
        exit(1);
        /* NOTREACHED */
    } else {
        /* parent */
        int procid; /* id of the /proc file */ // sp74
        sysset_t syscallSet;                   // sp34

        /* copy this wait stuff from old driver */
        // old being this one?
        sigint = sigset(SIGINT, SIG_IGN);
        sigterm = sigset(SIGTERM, SIG_IGN);
        /* if we are interested in memory statistics, we need to
           set a stop-on-exit for the child */
        if (memory_flag != 0) {
            procid = func_004362CC(forkpid);
            if ((num_maps = ioctl(procid, PIOCMAP_SGI, &D_10000430)) < 0) {
                perror("PIOCMAP_SGI");
                kill(forkpid, SIGKILL);
                return -1;
            }

            premptyset(&syscallSet);
            if (ioctl(procid, PIOCSEXIT, &syscallSet) < 0) {
                perror("PIOCSEXIT");
                kill(forkpid, SIGKILL);
                return -1;
            }
            /* continue the process */
            ioctl(procid, PIOCRUN, NULL);
            close(procid);
        }

        while ((waitpid = wait(&waitstatus)) != forkpid) {
            if (waitpid == -1) {
                return -1;
            }
        }

        (void)sigset(SIGINT, sigint);
        (void)sigset(SIGTERM, sigterm);
        if (vflag) {
            dotime();
        }
        if (memory_flag != 0) {
            func_0043673C(name, num_maps);
        }

        if (WIFSTOPPED(waitstatus)) {
            termsig = WSTOPSIG(waitstatus);
            fprintf(stderr, "STOPPED signal received from: %s ", name);
            fprintf(stderr, " (Signal %d) ", termsig);
            fprintf(stderr, " Process  %d abandoned\n", waitpid);
            return termsig;
        } else if (WIFEXITED(waitstatus)) {
            return WEXITSTATUS(waitstatus);
        } else if (WIFSIGNALED(waitstatus)) {
            termsig = WTERMSIG(waitstatus);
            fprintf(stderr, "Fatal error in: %s ", name);
            printf(" child died due to signal %d.\n", termsig);
            if (termsig == SIGKILL) {
                printf("Probably caused by running out of swap space -- check /usr/adm/SYSLOG.\n");
                exit(termsig);
            }
            if (termsig == SIGINT) {
                cleanup();
                exit(3);
            }
            fprintf(stderr, "Fatal error in: %s ", name);
            fprintf(stderr, " Signal %d ", termsig);
            if (waitstatus & WCOREFLAG) {
                fprintf(stderr, "- core dumped\n");
            } else {
                fprintf(stderr, "\n");
            }
            exit(termsig);
        } else {
            return 0;
        }
    }
}

/**
 * edit_src
 * Address: 0x00432660
 * VROM: 0x032660
 * Size: 0x4FC
 */
/**
 * Open the source file in `program` at the line indicated by the first error.
 *
 * @param program Editor to run.
 * @param srcpath Path of source file to open.
 * @param lino_mode Mode to use to find the error @see get_lino().
 * @return int ?
 */
int edit_src(const char* program, const char* srcpath, int lino_mode) {
    char lino[0x10]; // buffer for lino (need only be 12 long) // sp58
    pid_t forkpid;   // sp54
    int waitpid;     // sp50
    int termsig;     // sp4C
    int sigterm;     // sp48
    int sigint;      // sp44
    int waitstatus;  // sp40

    forkpid = fork();
    if (forkpid == (pid_t)-1) { // fork failed
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "fork to edit failed\n");
        if (errno < sys_nerr) {
            error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        return -1;
    }
    if (forkpid == (pid_t)0) {
        /* child */
        if (editflag == EDIT_FLAG_2) {
            get_lino(lino, srcpath, lino_mode);
            execlp(program, program, lino, srcpath, "-l", tempstr[25], "-f", "err-window", NULL);
        } else if (xserver == NULL) {
            execlp(program, program, "+1", errout, srcpath, NULL);
        } else {
            execlp("xterm", "xterm", "-display", xserver, "-ls", "-e", program, "+1", errout, srcpath, NULL);
        }
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "failed to exec: %s\n", program);
        if (errno < sys_nerr) {
            error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        exit(1);
        /* NOTREACHED */
    } else {
        /* parent */
        sigint = sigset(SIGINT, SIG_IGN);
        sigterm = sigset(SIGTERM, SIG_IGN);

        while ((waitpid = wait(&waitstatus)) != forkpid) {
            if (waitpid == -1) {
                return -1;
            }
        }

        (void)sigset(SIGINT, sigint);
        (void)sigset(SIGTERM, sigterm);

        termsig = waitstatus & 0xFF;
        if ((termsig != 0) && (termsig != SIGINT)) {
            fprintf(stderr, "Fatal error in: %s ", program);
            printf(" Signal %d ", termsig);
            if (waitstatus & WCOREFLAG) {
                fprintf(stderr, "- core dumped\n");
            } else {
                fprintf(stderr, "\n");
            }
            cleanup();
            exit(termsig);
            /* NOTREACHED */
        }
        if (termsig == SIGINT) {
            cleanup();
            exit(3);
            /* NOTREACHED */
        }
        return waitstatus & 0xFF00;
    }
}

/**
 * get_lino
 * Address: 0x00432B5C
 * VROM: 0x032B5C
 * Size: 0x5B0
 */
#define GET_LINO_BUF_SIZE 0x800
/**
 * Extract the printed line number of an error from `errout`. The strings to search for depend on the `mode` set. In
 * terms of regular expressions,
 * - 1/2 look for errors of the form "Error: <filename>, line: (\d{0,10})"
 * - 3 looks for "Error on line (\d{0,10})"
 * - 5/6 look for "ERROR .* LINE (\d{0,10})"
 *
 * @param[out] lino Found line number as a string, preceded by '+'.
 * @param[in] path Name of file to search for errors from. Only used in modes 1 and 2.
 * @param[in] mode Which format to look for.
 */
void get_lino(char* lino, const char* path, int mode) {
    int erroutid;                // fd of errout // sp83C
    int buf_len;                 // number of chars read // sp838
    char* lino_p = lino;         // sp834
    char* p;                     // iterator over buffer // sp830
    char buf[GET_LINO_BUF_SIZE]; // sp30

    *lino = '+';
    lino_p++;

    erroutid = open(errout, O_RDONLY);
    buf_len = read(erroutid, &buf, GET_LINO_BUF_SIZE);
    close(erroutid);

    // 0-terminate buffer
    if (buf_len < GET_LINO_BUF_SIZE) {
        buf[buf_len] = '\0';
    } else {
        buf[GET_LINO_BUF_SIZE - 1] = '\0';
    }

    switch (mode) {
        case 1:
        case 2:
            // Look through buffer for first ": Error: ".
            // If found, find the next comma,
            // check if the chunk before the comma matches `path`,
            // and the chunk after is ", line "
            // then copy the number following to lino via lino_p (max 10 digits).
            for (p = buf; p < buf + buf_len; p++) {
                if (strncmp(p, ": Error: ", 9) == 0) {
                    p = strchr(p, ',');
                    if ((p != NULL) && same_string_prefix(p - strlen(path), path) && (strncmp(p, ", line ", 7) == 0)) {
                        p += 7;
                        while (isdigit(*p) && ((lino_p - lino) <= 10)) {
                            *lino_p++ = *p++;
                        }
                        break;
                    }
                }
            }
            break;

        case 3:
            // look for first "Error on line " and copy the number following to lino (max 10 digits).
            for (p = buf; p < buf + buf_len; p++) {
                if (strncmp(p, "Error on line ", 14) == 0) {
                    p += 14;
                    while (isdigit(*p) && ((lino_p - lino) <= 10)) {
                        *lino_p++ = *p++;
                    }
                    break;
                }
            }
            break;

        case 5:
        case 6:
            // Look for first "ERROR ".
            for (p = buf; p < buf + buf_len; p++) {
                if (strncmp(p, "ERROR ", 6) == 0) {
                    p += 6;
                    break;
                }
            }
            // Then look for first subsequent " LINE " and copy the number following.
            for (; p < buf + buf_len; p++) {
                if (strncmp(p, " LINE ", 6) == 0) {
                    p += 6;
                    while (isdigit(*p) && ((lino_p - lino) <= 10)) {
                        *lino_p++ = *p++;
                    }
                    break;
                }
            }
            break;

        default:
            break;
    }

    // 0-terminate lino
    if ((lino + 1) < lino_p) {
        lino_p[0] = '\0';
    } else { // No digits found
        lino_p[0] = '1';
        lino_p[1] = '\0';
    }
}
#undef GET_LINO_BUF_SIZE

/**
 * show_err
 * Address: 0x0043310C
 * VROM: 0x03310C
 * Size: 0x10C
 */
#define SHOW_ERR_BUF_SIZE 0x10000
void show_err(const char* path) {
    int fd;
    int bytes_read;
    char buf[SHOW_ERR_BUF_SIZE];

    fd = open(path, O_RDONLY);
    bytes_read = read(fd, buf, SHOW_ERR_BUF_SIZE);
    close(fd);

    if (bytes_read < SHOW_ERR_BUF_SIZE) {
        buf[bytes_read] = '\0';
    } else {
        buf[SHOW_ERR_BUF_SIZE - 1] = '\0';
    }
    fprintf(stderr, "%s\n", buf);
}
#undef SHOW_ERR_BUF_SIZE

/**
 * handler
 * Address: 0x00433218
 * VROM: 0x033218
 * Size: 0x48
 */
/*
 * Handler () is used for catching signals.
 */
void handler(void) {
    // error added in Open64
    cleanup();
    exit(3);
}

/**
 * cleanup
 * Address: 0x00433260
 * VROM: 0x033260
 * Size: 0x3EC
 */
void cleanup(void) {
    // Do not delete any intermediates if "-K" passed.
    if (Kflag) {
        return;
    }
    if (passout != NULL) {
        unlink(passout);
    }
    if (passin != NULL) {
        char suf = getsuf(passin);

        if ((suf == '\0') || ((suf != srcsuf) && (suf != 'm'))) {
            if (!Eflag) {
                unlink(passin);
            }
        }
    }
    if ((tmpst != 0) && (symtab != NULL)) {
        unlink(symtab);
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
    if (editflag != EDIT_FLAG_0) {
        unlink(errout);
        if (editflag == EDIT_FLAG_2) {
            unlink(tempstr[25]);
        }
    }
    if (compiler == COMPILER_1) {
        unlink(tempstr[33]);
    }
}

/**
 * whats
 * Address: 0x0043364C
 * VROM: 0x03364C
 * Size: 0x1C0
 */
void whats(void) {
    int sp24 = runerror;

    if (compiler == COMPILER_2) {
        printf("%s  (%s)\n", progname, "pc");
    } else if (compiler == COMPILER_4) {
        printf("%s  (%s)\n", progname, "as");
    } else if (compiler == COMPILER_3) {
        printf("%s  (%s)\n", progname, "f77");
    } else if (compiler == COMPILER_5) {
        printf("%s  (%s)\n", progname, "pl1");
    } else if (compiler == COMPILER_6) {
        printf("%s  (%s)\n", progname, "cobol");
    } else {
        printf("%s  (%s)\n", progname, "cc");
    }
    printf("\tMips Computer Systems %d.%d\n", 3, 19);
}

/* this code is copied from csh, for printing times */
// No evidence of this code in anything resembling this form in csh

/**
 * settimes
 * Address: 0x0043380C
 * VROM: 0x03380C
 * Size: 0x3C
 */
// clock_t time0;
// struct tms tm0;

void settimes(void) {
    time0 = times(&tm0);
}

/**
 * dotime
 * Address: 0x00433848
 * VROM: 0x033848
 * Size: 0x180
 */
#define HZ 100

void dotime(void) {
    clock_t time1;
    clock_t wtime;
    int pad[2]; // removed by 7.1
    double utime;
    double stime;
    struct tms tm1;

    time1 = times(&tm1);
    utime = (double)(tm1.tms_utime + tm1.tms_cutime - tm0.tms_utime - tm0.tms_cutime) / (double)HZ;
    stime = (double)(tm1.tms_stime + tm1.tms_cstime - tm0.tms_stime - tm0.tms_cstime) / (double)HZ;
    wtime = time1 - time0;

    // phase time and program name added by 7.1
    fprintf(stderr, "%.2fu %.2fs %u:%04.1f %.0f%%\n", utime, stime, wtime / (60 * HZ), (wtime % (60 * HZ)) / (double)HZ,
            (utime + stime) / ((double)wtime / (double)HZ) * 100.0);
}

/**
 * func_004339C8
 * Address: 0x004339C8
 * VROM: 0x0339C8
 * Size: 0x260
 */
// Search through a NULL-terminated array of directory names for a library. If not found there, use an appropriate
// subdir of `usr/lib` instead.
static char* func_004339C8(char* name, char** dirs) {
    int fd;
    char* path;

    for (; *dirs != NULL; dirs++) {
        if ((compiler == COMPILER_1) &&
            ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3))) {
            fd = open(path = mkstr(*dirs, "/DCC", runlib, name, NULL), O_RDONLY, 0);
            if (fd >= 0) {
                close(fd);
                return path;
            }
        }

        fd = open(path = mkstr(*dirs, runlib, name, NULL), O_RDONLY, 0);
        if (fd >= 0) {
            close(fd);
            return path;
        }
    }

    if (abi_flag != 0) {
        path = mkstr("/", "usr/lib/abi", runlib, name, NULL);
    } else if (non_shared) {
        path = mkstr("/", "usr/lib/nonshared", runlib, name, NULL);
    } else {
        path = mkstr("/", "usr/lib", runlib, name, NULL);
    }
    return path;
}

/**
 * isdir
 * Address: 0x00433C28
 * VROM: 0x033C28
 * Size: 0x7C
 */
boolean isdir(const char* path) {
    int st;
    struct stat sbuf;

    st = stat(path, &sbuf);
    if (st == -1) {
        return FALSE;
    } else if (S_ISDIR(sbuf.st_mode)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * regular_not_writeable
 * Address: 0x00433CA4
 * VROM: 0x033CA4
 * Size: 0x98
 */
// Looks boolean, but not treated as one.
int regular_not_writeable(const char* path) {
    int fd;

    if (regular_file(path) != 1) {
        return 0;
    }
    fd = open(path, O_RDWR, 0666);
    if (fd >= 0) {
        close(fd);
        return 0;
    }
    return 1;
}

/**
 * regular_file
 * Address: 0x00433D3C
 * VROM: 0x033D3C
 * Size: 0x7C
 */
int regular_file(const char* path) {
    int st;
    struct stat sbuf;

    st = stat(path, &sbuf);
    if (st == -1) {
        return -1;
    } else if (!S_ISREG(sbuf.st_mode)) {
        return 0;
    } else {
        return 1;
    }
}

/**
 * basename
 * Address: 0x00433DB8
 * VROM: 0x033DB8
 * Size: 0x118
 */
// Almost identical in Open64
char* basename(char* const s) {
    register char* p;
    register char* const t = B_10009D28;

    if ((s == NULL) || (*s == '\0')) {
        return strcpy(t, ".");
    } else {
        p = strcpy(t, s);
        p += strlen(p);
        while (p != t && *--p == '/') { /* skip trailing /s */
            *p = '\0';
        }

        while (p != t) {
            if (*--p == '/') {
                return ++p;
            }
        }
        return p;
    }
}

/**
 * dirname
 * Address: 0x00433ED0
 * VROM: 0x033ED0
 * Size: 0x1C4
 */
// Almost identical in Open64
char* dirname(char* const s) {
    register char* p;
    register char* const t = B_10009D28;

    if ((s == NULL) || (*s == '\0')) {
        return strcpy(t, ".");
    } else {
        p = strcpy(t, s);
        p += strlen(p);
        while ((p != t) && (*--p == '/')) {} /* skip trailing /s */

        if ((p == t) && (*p == '/')) {
            return strcpy(t, "/");
        }

        while (p != t) {
            if (*--p == '/') {
                if (p == t) {
                    return strcpy(t, "/");
                }
                while (*p == '/') {
                    p--;
                }
                *++p = '\0';
                return t;
            }
        }
        return strcpy(t, ".");
    }
}

/* 0x037460 0x10000460 379  */ struct {
    /* 0x0 */ const char* basename;  // name of executable
    /* 0x4 */ const char* full_path; // full path of executable
    /* 0x8 */ const char* product;   // package/product executable is part of
} prod_name[20] = {
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
    { "edgcpfe.alt", "/usr/lib/DCC/edgcpfe.alt", "Delta C++" },
};
/* 0x037550 0x10000550 None */ static char* D_10000550 = NULL;
/* 0x037554 0x10000554 None */ static char* D_10000554 = NULL;
/* 0x037558 0x10000558 None */ static char* D_10000558 = NULL; // program_name (D_1000C2F0 in 7.1)

/**
 * func_00434094
 * Address: 0x00434094
 * VROM: 0x034094
 * Size: 0x134
 */
// obvious name suggestion would be `get_product` or similar?
/**
 * Looks for `path` in the `prod_name` table and returns the name of the corresponding product/package.
 *
 * @param path name of executable to look for, either basename or full path
 * @param check_full_path Check for basename if FALSE, full path if TRUE.
 * @return const char* name of product containing the executable (NULL if not found).
 */
static const char* func_00434094(const char* path, int check_full_path) {
    int i;
    int prod_count;
    const char* check_path;
    const char* prod_path;

    if (check_full_path) {
        check_path = path;
    } else {
        check_path = strrchr(path, '/');
        if (check_path != NULL) {
            check_path++;
        }
    }

    prod_count = 20;
    for (i = 0; i < prod_count; i++) {
        if (check_full_path) {
            prod_path = prod_name[i].full_path;
        } else {
            prod_path = prod_name[i].basename;
        }
        if (same_string(check_path, prod_path)) {
            return prod_name[i].product;
        }
    }
    return NULL;
}

/**
 * add_cxx_symbol_options
 * Address: 0x004341C8
 * VROM: 0x0341C8
 * Size: 0x40
 */
int add_cxx_symbol_options(void) {
    addstr(&execlist, "-cxx");
    return 0;
}

/**
 * init_curr_dir
 * Address: 0x00434208
 * VROM: 0x034208
 * Size: 0x158
 */
void init_curr_dir(void) {
    if (D_10000558 == NULL) {
        D_10000558 = strrchr(progname, '/');
        if (D_10000558 == NULL) {
            D_10000558 = progname;
        } else {
            D_10000558++;
        }
    }
    if (D_10000438 == 0) {
        D_10000438 = getcwd(NULL, 0x400);
        if (D_10000438 == NULL) {
            fprintf(stderr, "%s: ", D_10000558);
            perror("full_path");
            cleanup();
            exit(1);
        }
    }
}

/**
 * full_path
 * Address: 0x00434360
 * VROM: 0x034360
 * Size: 0x90
 */
// Make a full path name from a base file name.
/* string */ char* full_path(const /* string */ char* base) {
    /* string */ char* path;

    init_curr_dir();
    if (*base == '/') {
        path = mkstr(base, NULL);
    } else {
        path = mkstr(D_10000438, "/", base, NULL);
    }
    return path;
}

/**
 * add_static_opt
 * Address: 0x004343F0
 * VROM: 0x0343F0
 * Size: 0x54
 */
void add_static_opt(/* string */ char* opt) {
    if (!D_1000020C) {
        addstr(&staticopts, opt);
    }
}

#define CONTENTS_BUF_SIZE 0x2800
/**
 * record_static_fileset
 * Address: 0x00434444
 * VROM: 0x034444
 * Size: 0x9F4
 */
void record_static_fileset(const char* arg0) {
    int sp28E4;                           // multipurpose
    FILE* temp_file;                      // sp28E0
    FILE* file;                           // sp28DC
    int fd;                               // sp28D8
    char contents_buf[CONTENTS_BUF_SIZE]; // spD8
    char* fullpath;                       // spD4
    size_t path_length;                   // spD0
    char pid_buf[20];                     // spBC
    struct stat sbuf;                     // sp34

    sprintf(pid_buf, ".%d", getpid());
    if (D_10000204 == NULL) {
        D_10000204 = "";
    }
    if (D_10000208 == NULL) {
        D_10000208 = mkstr("cvstatic.fileset", NULL);
    }
    if ((D_10000208[0] == '/') || (D_10000204[0] == '\0')) {
        D_10000550 = mkstr(D_10000208, NULL);
    } else {
        D_10000550 = mkstr(D_10000204, D_10000208, NULL);
    }
    D_10000554 = mkstr(tmpdir, "cvstatic.fileset", pid_buf, NULL);

    fullpath = full_path(arg0);
    path_length = strlen(fullpath);

    if (vflag) {
        fprintf(stderr, "Static fileset: %s %s", fullpath, D_10000558);
        for (sp28E4 = 0; sp28E4 < staticopts.length; sp28E4++) {
            fprintf(stderr, " %s", staticopts.entries[sp28E4]);
        }
        fprintf(stderr, "\n");
    }

    temp_file = fopen(D_10000554, "w+");
    if (temp_file == NULL) {
        error(ERRORCAT_ERROR, NULL, 0, "record_static_fileset", 0, "could not open cvstatic fileset temp file %s\n",
              D_10000554);
        perror(D_10000558);
        cleanup();
        exit(1);
    }

    fd = open(D_10000550, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        error(ERRORCAT_ERROR, NULL, 0, "record_static_fileset", 0,
              "could not open or create cvstatic fileset file %s\n", D_10000550);
        perror(D_10000558);
        unlink(D_10000554);
        cleanup();
        exit(1);
    }
    if (flock(fd, LOCK_EX) < 0) {
        error(ERRORCAT_ERROR, NULL, 0, "record_static_fileset", 0, "error in locking cvstatic fileset file %s\n",
              D_10000550);
        perror(D_10000558);
        unlink(D_10000554);
        cleanup();
        exit(1);
    }
    if (fstat(fd, &sbuf) < 0) {
        error(ERRORCAT_ERROR, NULL, 0, "record_static_fileset", 0, "could not fstat cvstatic fileset file %s\n",
              D_10000550);
        perror(D_10000558);
        unlink(D_10000554);
        cleanup();
        exit(1);
    }
    if (sbuf.st_size == 0) {
        fprintf(temp_file, "-cvstatic\n");
    }

    file = fdopen(fd, "r+");
    if (file == NULL) {
        error(ERRORCAT_ERROR, NULL, 0, "record_static_fileset", 0, "could not fdopen cvstatic fileset file %s\n",
              D_10000550);
        perror(D_10000558);
        unlink(D_10000554);
        cleanup();
        exit(1);
    }
    while (fgets(contents_buf, CONTENTS_BUF_SIZE, file) != NULL) {
        if ((strncmp(contents_buf, fullpath, path_length) != 0) || !isspace(contents_buf[path_length])) {
            fputs(contents_buf, temp_file);
        }
    }
    fprintf(temp_file, "%s %s", fullpath, D_10000558);
    for (sp28E4 = 0; sp28E4 < staticopts.length; sp28E4++) {
        fprintf(temp_file, " %s", staticopts.entries[sp28E4]);
    }

    fprintf(temp_file, "\n");
    free(fullpath);
    rewind(file);
    rewind(temp_file);
    ftruncate(file->_file, 0);

    while ((sp28E4 = fread(contents_buf, 1, CONTENTS_BUF_SIZE, temp_file)) > 0) {
        if (fwrite(&contents_buf, 1, sp28E4, file) != sp28E4) {
            error(ERRORCAT_ERROR, NULL, 0, "record_static_fileset", 0, "error in writing cvstatic fileset file %s\n",
                  D_10000550);
            perror(D_10000558);
            unlink(D_10000554);
            cleanup();
            exit(1);
        }
    }
    fclose(file);
    fclose(temp_file);
    unlink(D_10000554);
    free(D_10000550);
    free(D_10000554);
}
#undef CONTENTS_BUF_SIZE

/**
 * touch
 * Address: 0x00434E38
 * VROM: 0x034E38
 * Size: 0x17C
 */
int touch(const char* path) {
    time_t curtime = time(NULL);
    struct utimbuf times;
    char* err_str;

    init_curr_dir();
    if (vflag) {
        fprintf(stderr, "%s: touch %s\n", D_10000558, path);
    }
    times.modtime = curtime;
    times.actime = curtime;
    if (utime(path, &times) < 0) {
        err_str = malloc(strlen(path) + strlen(D_10000558) + 10);
        sprintf(err_str, "%s: touch %s", D_10000558, path);
        perror(err_str);
        free(err_str);
        return -1;
    }
    return 0;
}

/**
 * add_prelinker_objects
 * Address: 0x00434FB4
 * VROM: 0x034FB4
 * Size: 0xFC
 */
// Append the `list` to `execlist`, skipping any entries that are "-B"
void add_prelinker_objects(string_list* execlist, string_list* list) {
    int i;

    for (i = 0; i < list->length; i++) {
        if (list->entries[i][0] == '-') {
            if (same_string(list->entries[i], "-B")) {
                i++;
            }
        } else {
            addstr(execlist, list->entries[i]);
        }
    }
}

/*
 * The mechanism for updating the template instantiation info file for
 * the current object file.
 *
 * We base the .ii filename on the object file name by creating a name
 * as follows: dirname(obj)/ii_files/basename(obj,.o).ii.
 *
 * If this file exists, we look for a terminator (a line with the contents
 * "----"), and replace everything before that line with updated information
 * about the command-line used to compile the object file, and the working
 * directory from where the command was issued. If the terminator is missing,
 * it is prepended to the file.
 */

/*
 * Is "c" a character that would need quoting to the shell?
 */

#define is_shell_special(c)                                                                                           \
    ((c) == '\'' || (c) == '|' || (c) == '&' || (c) == '*' || (c) == '?' || (c) == '[' || (c) == ']' || (c) == ';' || \
     (c) == '!' || (c) == '(' || (c) == ')' || (c) == '^' || (c) == '<' || (c) == '>' || (c) <= ' ' || (c) == '\t' || \
     is_shell_quote_special(c))

/*
 * Is "c" a character that would have to be \-escaped inside double-quotes?
 *
 * The answer to this one actually depends on the shell. Especially
 * troublesome is '!': for csh, it *must* be \-escaped inside quotes,
 * and for sh, it *must not* be \-escaped. sh preserves the \ if it
 * is not quoting something significant. Sigh.
 *
 * However, since most "make"s and "make"-clones use /bin/sh as the shell
 * regardless of the SHELL setting, and since system() always uses /bin/sh
 * to execute the command, I am going to stick with whatever sh needs.
 */
#define is_shell_quote_special(c) ((c) == '"' || (c) == '\\' || (c) == '`' || (c) == '$')

/**
 * quoted_length
 * Address: 0x004350B0
 * VROM: 0x0350B0
 * Size: 0x174
 */
/*
 * returns the length of the argument after inserting any required quoting
 * characters.
 */
/* size_t */ int quoted_length(char* p, /* boolean */ int* quoted) {
    /* size_t */ int len = 0;
    char c;

    *quoted = 0;

    while (c = *p++) {
        if (!(*quoted) && is_shell_special(c)) {
            (*quoted) = 1;
            len += 2;
        }
        if (is_shell_quote_special(c))
            len++;
        len++; /* the character itself */
    }
    return len;
}

/**
 * quote_shell_arg
 * Address: 0x00435224
 * VROM: 0x035224
 * Size: 0x140
 */
/*
 * writes a quoted (if necessary) copy of p into the buffer pointed to
 * by buf, and returns the length of the quoted string written.
 */
/* size_t */ int quote_shell_arg(/* string */ char* p, /* string */ char* buf) {
    char c;
    /* boolean */ int quoted = 0;
    /* size_t */ int len;

    len = quoted_length(p, &quoted);

    if (quoted)
        *buf++ = '"';
    while (c = *p++) {
        if (is_shell_quote_special(c))
            *buf++ = '\\';
        *buf++ = c;
    }
    if (quoted)
        *buf++ = '"';

    return len;
}

/**
 * save_off_command_line
 * Address: 0x00435364
 * VROM: 0x035364
 * Size: 0x340
 */
void save_off_command_line(int argc, char** argv) {
    int len = 0;   // total length of most arguments
    int o_len = 0; // total length of "-o" arguments
    /* boolean */ int quoted = FALSE;
    int i;
    string p;   // string pointer for most arguments
    string o_p; // string pointer for "-o" arguments

    // Find total length of arguments to add
    for (i = 1; i < argc; i++) {
        if (same_string(argv[i], "-o") && (i < (argc - 1))) { // output file argument
            o_len += quoted_length(argv[i], &quoted) + 1;
            o_len += quoted_length(argv[i + 1], &quoted) + 1;
            i++;
        } else {
            len += quoted_length(argv[i], &quoted) + 1;
        }
    }

    // allocate strings for arguments.
    B_1000A48C = p = malloc(len + 1);
    if (o_len != 0) {
        B_1000A49C = malloc(o_len + 1);
    }

    // copy arguments
    for (i = 1; i < argc; i++) {
        if (same_string(argv[i], "-o") && (i < (argc - 1))) {
            o_p = B_1000A49C; // Reset `o_p` every time to only keep last "-o" argument
            o_p += quote_shell_arg(argv[i], o_p);
            *o_p++ = ' ';
            o_p += quote_shell_arg(argv[i + 1], o_p);
            *o_p++ = ' ';
            *o_p = '\0';
            i++;
        } else {
            p += quote_shell_arg(argv[i], p);
            *p++ = ' ';
        }
    }

    p[-1] = '\0';
}

/**
 * skip_old_ii_controls
 * Address: 0x004356A4
 * VROM: 0x0356A4
 * Size: 0x4FC
 */
/*
 * Skip over leading lines upto and including the terminator (a line that
 * starts with ----). If the terminator is not found, rewind back to start.
 */
void skip_old_ii_controls(FILE* f) {
    int c;
    int terminator_found = 0;

    c = getc(f);
    while (c != EOF) {
        if (c == '-' && (c = getc(f)) == '-' && (c = getc(f)) == '-' && (c = getc(f)) == '-') {
            terminator_found = 1;
        }
        while (c != '\n' && c != EOF)
            c = getc(f);
        if (terminator_found)
            break;
        if (c == '\n')
            c = getc(f);
    }

    if (c == EOF)
        rewind(f);
}

/**
 * make_ii_file_name
 * Address: 0x00435BA0
 * VROM: 0x035BA0
 * Size: 0x134
 */
char* make_ii_file_name(char* objname) {
    char* base = basename(objname);
    /* size_t */ int baselen = strlen(base);

    base = mkstr(base, "   ", NULL);
    if ((base[baselen - 2] == '.') && (base[baselen - 1] == 'o')) {
        strcpy(&base[baselen - 1], "ii");
    } else {
        strcpy(&base[baselen], ".ii");
    }
    return mkstr(dirname(objname), "/ii_files/", base, NULL);
}

/**
 * update_instantiation_info_file
 * Address: 0x00435CD4
 * VROM: 0x035CD4
 * Size: 0x5F8
 */
/*
 * The actual function that updates the instantiation information
 * in the .ii file.
 */
void update_instantiation_info_file(char* objname) {
    char* ii_file_name = make_ii_file_name(objname);
    char* new_ii_file_name = mkstr(ii_file_name, ".NEW", NULL);
    FILE* old_ii = fopen(ii_file_name, "r");
    FILE* new_ii;
    int c;

    if (old_ii != NULL) {
        /* There is an existing .ii file (may be empty) */
        /* need to update that file! */

        init_curr_dir();
        if (vflag) {
            fprintf(stderr, "%s: update_instantiation_info_file %s\n", D_10000558, ii_file_name);
        }

        new_ii = fopen(new_ii_file_name, "w");
        if (new_ii == NULL) {
            /* could not open the (new) file: permission problem in
             * directory? */
            error(ERRORCAT_ERROR, NULL, 0, "update_instantiation_info_file", 0, "error in creating file %s\n",
                  new_ii_file_name);
            perror(D_10000558);
            cleanup();
            exit(1);
        }

        /*
         * skip over the existing control information (upto the standard
         * separator), if any.
         */
        skip_old_ii_controls(old_ii);

        /*
         * Now, write out the new control information. For now, we have
         * only two lines:
         * CMDLINE=<compiler name> <quote-protected command-line arguments>
         * PWD=<current working directory>
         */
        // Became a separate function by 7.1
        fprintf(new_ii, "CMDLINE=%s %s%s%s\n", progname, (((srcfiles.length == 1) && !cflag) ? "-c " : ""),
                ((((srcfiles.length == 1) && !cflag) || (B_1000A49C == NULL)) ? "" : B_1000A49C), B_1000A48C);
        fprintf(new_ii, "PWD=%s\n", D_10000438);
        fprintf(new_ii, "----\n");

        /* Now copy over the remainder of the old file. */
        while ((c = getc(old_ii)) != EOF) {
            putc(c, new_ii);
        }

        /* Rename the new file to replace the existing .ii file */
        fclose(old_ii);
        fclose(new_ii);
        if (rename(new_ii_file_name, ii_file_name) < 0) {
            error(ERRORCAT_ERROR, NULL, 0, "update_instantiation_info_file", 0, "error in renaming %s to %s\n",
                  new_ii_file_name, ii_file_name);
            perror(D_10000558);
            cleanup();
            exit(1);
        }
    }

    free(ii_file_name);
    free(new_ii_file_name);
}

/* code used to handle the -showm */

/**
 * func_004362CC
 * Address: 0x004362CC
 * VROM: 0x0362CC
 * Size: 0x2EC
 */
// stop_on_exit
static int func_004362CC(pid_t pid) { /* sets a child process to stop on exit */
#ifndef linux
    int procid; /* fd for process */            // sp29C
    char procname[20]; /* name - /proc/<pid> */ // sp288
    prstatus_t pstatus;                         // sp68
    long modeFlags = 0;                         // sp64
    sysset_t syscallSet;                        // sp24

    sprintf(procname, "/proc/%-d", pid);
    if ((procid = open(procname, O_RDWR | O_EXCL)) == -1) {
        perror("Opening /proc");
        kill(pid, SIGKILL);
        exit(1);
    }

    // The following code from Open64 is included based on `modeflags` existing but being unused
#if 0
    /* set it so it wont trace child */
    modeFlags = PR_FORK;
    if (ioctl(procid, PIOCRESET, &modeFlags) < 0) {
        perror("PIOCRESET");
        kill(pid, SIGKILL);
        return 0;
    }
#endif

    premptyset(&syscallSet);
    praddset(&syscallSet, 2); // SYS_exit in Open64, but does not line up

    if (ioctl(procid, PIOCSENTRY, &syscallSet) < 0) {
        perror("PIOCSENTRY");
        kill(pid, SIGKILL);
        exit(1);
    }

    func_00436680();

    if (ioctl(procid, PIOCWSTOP, &pstatus) < 0) {
        perror("PIOCWSTOP");
        kill(pid, SIGKILL);
        exit(1);
    }

    if (pstatus.pr_why != PR_SYSENTRY) {
        perror("program halted prematurely");
        kill(pid, SIGKILL);
        exit(1);
    }
    if (pstatus.pr_what != 2) { // SYS_exit in Open64, but does not line up
        perror("program halted in wrong system call");
        kill(pid, SIGKILL);
        exit(1);
    }
    if (pstatus.pr_errno != 0) {
        perror("unknown problem\n");
        exit(1);
    }

    /* at this point the child is stopped on exit */
    return procid;
#else
    return 0;
#endif
}

/**
 * func_004365B8
 * Address: 0x004365B8
 * VROM: 0x0365B8
 * Size: 0xC8
 */
// my_psema
// Test reading from Pipe.
// Temp is removed in Open64.
static void func_004365B8(void) {
    char c;
    int failure;

    close(B_1000A458[1]);
    failure = (read(B_1000A458[0], &c, 1) != 1);
    if (failure) {
        perror("read on pipe failed");
        exit(1);
    }
    close(B_1000A458[0]);
}

/**
 * func_00436680
 * Address: 0x00436680
 * VROM: 0x036680
 * Size: 0xBC
 */
// my_vsema
// Test writing to Pipe
static void func_00436680(void) {
    char c;

    close(B_1000A458[0]);
    if (write(B_1000A458[1], &c, 1) != 1) {
        perror("write on pipe failed");
        exit(1);
    }
    close(B_1000A458[1]);
}

/**
 * func_0043673C
 * Address: 0x0043673C
 * VROM: 0x03673C
 * Size: 0x844
 */
// print_mem
// Very similar in Open64, which uses `pr_size` instead of `pr_vsize * pagesize` and has an extra check.
static void func_0043673C(char* phase, int num_maps) {
#ifndef linux
    int i, identified;
    ulong_t mflags;
    int pagesize;
    size_t text_size, data_size, brk_size, stack_size, so_text_size, so_data_size, so_brk_size, mmap_size;
    int verbose = (memory_flag > 1);

    text_size = data_size = brk_size = stack_size = so_text_size = so_data_size = so_brk_size = mmap_size = 0;

    pagesize = getpagesize();

    /* now print out the maps obtained */
    for (i = 0; i < num_maps; i++) {
        identified = 0;
        mflags = B_10008310[i].pr_mflags & ((1 << MA_REFCNT_SHIFT) - 1);
        if (mflags == (MA_READ | MA_SHARED | MA_EXEC | MA_PRIMARY)) {
            /* program text */
            text_size += B_10008310[i].pr_vsize * pagesize;
            identified = 1;
        }
        if (mflags == (MA_READ | MA_SHARED | MA_EXEC)) {
            /* .so text */
            so_text_size += B_10008310[i].pr_vsize * pagesize;
            identified = 1;
        }
        if (mflags == (MA_COW | MA_READ | MA_WRITE) && B_10008310[i].pr_vaddr < DATA_ADDRESS) {
            /* .so  data */
            so_data_size += B_10008310[i].pr_vsize * pagesize;
            identified = 1;
        }
        if ((mflags == (MA_READ | MA_WRITE) || mflags == (MA_READ) || mflags == (MA_READ | MA_WRITE | MA_SHARED) ||
             mflags == (MA_READ | MA_SHARED)) &&
            B_10008310[i].pr_vaddr < DATA_ADDRESS) {
            /* some sort of mmap region */
            mmap_size += B_10008310[i].pr_vsize * pagesize;
            identified = 1;
        }
        mflags &= ~MA_PRIMARY;
        if (mflags == (MA_COW | MA_READ | MA_WRITE) && B_10008310[i].pr_vaddr >= DATA_ADDRESS) {
            /* data space */
            data_size += B_10008310[i].pr_vsize * pagesize;
            identified = 1;
        }
        if (mflags == (MA_COW | MA_READ | MA_WRITE | MA_BREAK) && B_10008310[i].pr_vaddr >= DATA_ADDRESS) {
            /* brk space */
            brk_size += B_10008310[i].pr_vsize * pagesize;
            identified = 1;
        }
        if (mflags == (MA_STACK | MA_READ | MA_WRITE)) { // Open64 has extra check,
                                                         // || mflags==(MA_STACK|MA_READ|MA_WRITE|MA_COW)
            /* stack space */
            stack_size += B_10008310[i].pr_vsize * pagesize;
            identified = 1;
        }
        if (identified == 0) {
            fprintf(stderr, "-showm: Unidentified: segment %d\n", i);
        }
        if (verbose || identified == 0) {
            fprintf(stderr, "pr_vaddr[%d]= %lx\n", i, B_10008310[i].pr_vaddr);
            fprintf(stderr, "pr_size[%d]= %lx\n", i, B_10008310[i].pr_size);
            fprintf(stderr, "pr_off[%d]= %lx\n", i, B_10008310[i].pr_off);
            fprintf(stderr, "pr_mflags[%d]= %lx\n", i, B_10008310[i].pr_mflags);
            fprintf(stderr, "pr_vsize[%d]= %lx\n", i, B_10008310[i].pr_vsize);
            fprintf(stderr, "pr_psize[%d]= %lx\n", i, B_10008310[i].pr_psize);
            fprintf(stderr, "pr_wsize[%d]= %lx\n", i, B_10008310[i].pr_wsize);
            fprintf(stderr, "pr_rsize[%d]= %lx\n", i, B_10008310[i].pr_rsize);
            fprintf(stderr, "pr_msize[%d]= %lx\n", i, B_10008310[i].pr_msize);
            fprintf(stderr, "pr_dev[%d]= %lx\n", i, B_10008310[i].pr_dev);
            fprintf(stderr, "pr_ino[%d]= %lx\n", i, B_10008310[i].pr_ino);
            fprintf(stderr, "\n");
        }
    }
    fprintf(stderr, "%s phase mem: %ldT %ldD %ldB %ldS %ldt %ldd %ldb %ldm= %ldK\n", phase, text_size / 0x400,
            data_size / 0x400, brk_size / 0x400, stack_size / 0x400, so_text_size / 0x400, so_data_size / 0x400,
            so_brk_size / 0x400, mmap_size / 0x400,
            (text_size + data_size + brk_size + stack_size + so_text_size + so_data_size + so_brk_size + mmap_size) /
                0x400);
    if (verbose) {
        fprintf(stderr, "text_size= %ld Kbytes\n", text_size / 0x400);
        fprintf(stderr, "data_size= %ld Kbytes\n", data_size / 0x400);
        fprintf(stderr, "brk_size= %ld Kbytes\n", brk_size / 0x400);
        fprintf(stderr, "stack_size= %ld Kbytes\n", stack_size / 0x400);
        fprintf(stderr, "so_text_size= %ld Kbytes\n", so_text_size / 0x400);
        fprintf(stderr, "so_data_size= %ld Kbytes\n", so_data_size / 0x400);
        fprintf(stderr, "so_brk_size= %ld Kbytes\n", so_brk_size / 0x400);
        fprintf(stderr, "mmap_size= %ld Kbytes\n", mmap_size / 0x400);
        fprintf(
            stderr, "TOTAL_SIZE= %ld Kbytes\n",
            (text_size + data_size + brk_size + stack_size + so_text_size + so_data_size + so_brk_size + mmap_size) /
                0x400);
    }
#else
    fprintf(stderr, "-showm not implemented under linux\n");
#endif
}
