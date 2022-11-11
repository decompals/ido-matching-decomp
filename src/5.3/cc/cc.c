/**
 * @file cc.c
 * @brief Compiler driver for IDO 5.3 (or 3.19 as it styles itself internally)
 *
 * This file incorporates code from Open64's Osprey driver, version 0.13.0, licensed under GPL Version 2
 */
#include "sys/types.h"
#include "stdio.h"
#include "errno.h"
#include "string.h"
#include "malloc.h"
#include "sys/times.h"
#include "sex.h"
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
// /* static */ int func_00405560();
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

typedef enum Compiler {
    /* 1 */ COMPILER_1 = 1, // C
    /* 2 */ COMPILER_2,     // Pascal
    /* 3 */ COMPILER_3,     // FORTRAN
    /* 4 */ COMPILER_4,     // Assembler
    /* 5 */ COMPILER_5,     // PL1
    /* 6 */ COMPILER_6      // COBOL
} Compiler;

//! TODO: check
typedef enum CCompilerChoice {
    /* 0 */ C_COMPILER_CHOICE_0, // default, presumably "cc"
    /* 1 */ C_COMPILER_CHOICE_1, // "ncc" (NCC but for C?)
    /* 2 */ C_COMPILER_CHOICE_2, // "CC.eh", (C++ compiler with exception handling)
                                 // "CC", (Ordinary C++ compiler)
                                 // "NCC" (32-bit native C++ compiler, apparently just "CC -32")
    /* 3 */ C_COMPILER_CHOICE_3  // "DCC" (Delta/C++)
} CCompilerChoice;

typedef enum EditFlag {
    /* 0 */ EDIT_FLAG_0, //!< E
    /* 1 */ EDIT_FLAG_1, //!< "-edit[0-9]"
    /* 2 */ EDIT_FLAG_2  //!< "-edit[0-9]" and environment variable for EDITOR contains "emacs"
} EditFlag;

/* 03F310 10008310 */ static char B_10008310[0x1900];          // equivalent of B_1000CAC0
/* 040C10 10009C10 */ clock_t time0;                           // line 174
                                                               // 0x4 padding
/* 040C18 10009C18 */ struct tms tm0;                          // line 176
/* 040C28 10009C28 */ char perr_msg[0x100];                    // char perr_msg[0x100]; // line 124
/* 040D28 10009D28 */ static char B_10009D28[0x400];           // equivalent of B_1000E5E0
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
/* 0411B8 1000A1B8 */ const char* allBstring;                  // line 165
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
/* 041240 1000A240 */ int xserver;                             // line 205
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
/* 041458 1000A458 */ static char B_1000A458[0x08];
/* 041460 1000A460 */ string_list usplitflags; // line 245
                                               // 0x4 padding
/* 041470 1000A470 */ string_list umergeflags; // line 247
                                               // 0x4 padding
/* 041480 1000A480 */ string_list uloopflags;  // line 249
/* 04148C 1000A48C */ static char* B_1000A48C; // string containing most arguments "command_line"
/* 041490 1000A490 */ string_list uopt0flags;  // line 253
/* 04149C 1000A49C */ static char* B_1000A49C; // string containing last "-o" argument ("outfile")
/* 0414A0 1000A4A0 */ string_list ddoptflags;  // line 266
                                               // 0x4 padding
/* 0414B0 1000A4B0 */ string_list optflags;    // line 269
                                               // 0x4 padding
/* 0414C0 1000A4C0 */ string_list genflags;    // line 271
                                               // 0x4 padding
/* 0414D0 1000A4D0 */ string_list asflags;     // line 273
                                               // 0x4 padding
/* 0414E0 1000A4E0 */ string_list ldflags;     // line 277
                                               // 0x4 padding
/* 0414F0 1000A4F0 */ string_list as1flags;    // line 275
                                               // 0x4 padding
/* 041500 1000A500 */ string_list ftocflags;   // line 282
                                               // 0x4 padding
/* 041510 1000A510 */ string_list cordflags;   // line 284
                                               // 0x4 padding
/* 041520 1000A520 */ string_list srcfiles;    // line 286
                                               // 0x4 padding
/* 041530 1000A530 */ string_list ufiles;      // line 288
                                               // 0x4 padding
/* 041540 1000A540 */ string_list objfiles;    // line 290
                                               // 0x4 padding
/* 041550 1000A550 */ string_list feedlist;    // line 292
                                               // 0x4 padding
/* 041560 1000A560 */ string_list execlist;    // line 294
/* 04156C 1000A56C */ static char B_1000A56C[0x04];
/* 041570 1000A570 */ static char B_1000A570[0x08];
/* 041578 1000A578 */ string_list dirs_for_crtn;           // line 299
                                                           // 0x4 padding
/* 041588 1000A588 */ string_list dirs_for_nonshared_crtn; // line 301
                                                           // 0x4 padding
/* 041598 1000A598 */ string_list dirs_for_abi_crtn;       // line 303
                                                           // 0x4 padding
/* 0415A8 1000A5A8 */ string_list ldZflags;                // line 305
/* 0415B4 1000A5B4 */ static char B_1000A5B4[0x04];
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

static const char STR_10000560[] = "pl1";
static const char STR_10000564[] = "pli";
static const char STR_10000568[] = "cob";
static const char STR_1000056C[] = "il";
static const char STR_10000570[] = "st";
static const char STR_10000574[] = "anl";
static const char STR_10000578[] = "c++";
static const char STR_1000057C[] = "cc";
static const char STR_10000580[] = "cxx";
static const char STR_10000584[] = "C";
static const char STR_10000588[] = "cpp";
static const char STR_1000058C[] = "CXX";
static const char STR_10000590[] = "CPP";
static const char STR_10000594[] = ".c";
static const char STR_10000598[] = " -lm";
static const char STR_100005A0[] = " -lp";
static const char STR_100005A8[] = " -lF77";
static const char STR_100005B0[] = " -lI77";
static const char STR_100005B8[] = " -lU77";
static const char STR_100005C0[] = " -lisam";
static const char STR_100005C8[] = " -lexc";
static const char STR_100005D0[] = " -ldw";
static const char STR_100005D8[] = " -lprof";
static const char STR_100005E0[] = " -lxmalloc";
static const char STR_100005EC[] = " -lmld";
static const char STR_100005F4[] = "list";
static const char STR_100005FC[] = "keep";
static const char STR_10000604[] = "list";
static const char STR_1000060C[] = "keep";
static const char STR_10000614[] = "0";
static const char STR_10000618[] = "/";
static const char STR_1000061C[] = "/";

/* 0x037000 0x10000000 161  */ extern UNK_TYPE alternate_fe;
/* 0x037004 0x10000004 162  */ extern UNK_TYPE ansichoice;
/* 0x037008 0x10000008 163  */ extern CCompilerChoice c_compiler_choice;
/* 0x03700C 0x1000000C 164  */ extern struct _struct_suffixes_0x8 suffixes[];
/* 0x037084 0x10000084 165  */ extern UNK_TYPE include;
/* 0x037088 0x10000088 166  */ extern UNK_TYPE includeB;
/* 0x03708C 0x1000008C 167  */ extern UNK_TYPE einclude;
/* 0x037090 0x10000090 168  */ extern UNK_TYPE eincludeB;
/* 0x037094 0x10000094 169  */ extern UNK_TYPE cpp;
/* 0x037098 0x10000098 170  */ extern UNK_TYPE ccom;
/* 0x03709C 0x1000009C 171  */ extern UNK_TYPE mpc;
/* 0x0370A0 0x100000A0 172  */ extern UNK_TYPE cfe;
/* 0x0370A4 0x100000A4 173  */ extern UNK_TYPE upas;
/* 0x0370A8 0x100000A8 174  */ extern UNK_TYPE fcom;
/* 0x0370AC 0x100000AC 175  */ extern UNK_TYPE upl1;
/* 0x0370B0 0x100000B0 176  */ extern UNK_TYPE pl1err;
/* 0x0370B4 0x100000B4 177  */ extern UNK_TYPE ulpi;
/* 0x0370B8 0x100000B8 178  */ extern UNK_TYPE ucob;
/* 0x0370BC 0x100000BC 179  */ extern UNK_TYPE ujoin;
/* 0x0370C0 0x100000C0 180  */ extern UNK_TYPE usplit;
/* 0x0370C4 0x100000C4 181  */ extern UNK_TYPE uld;
/* 0x0370C8 0x100000C8 182  */ extern UNK_TYPE umerge;
/* 0x0370CC 0x100000CC 183  */ extern UNK_TYPE uloop;
/* 0x0370D0 0x100000D0 184  */ extern UNK_TYPE uopt0;
/* 0x0370D4 0x100000D4 185  */ extern UNK_TYPE ddopt;
/* 0x0370D8 0x100000D8 186  */ extern UNK_TYPE opt;
/* 0x0370DC 0x100000DC 187  */ extern UNK_TYPE gen;
/* 0x0370E0 0x100000E0 188  */ extern UNK_TYPE as0;
/* 0x0370E4 0x100000E4 189  */ extern UNK_TYPE as1;
/* 0x0370E8 0x100000E8 190  */ extern UNK_TYPE ld;
/* 0x0370EC 0x100000EC 191  */ extern UNK_TYPE ftoc;
/* 0x0370F0 0x100000F0 192  */ extern UNK_TYPE cord;
/* 0x0370F4 0x100000F4 193  */ extern UNK_TYPE btou;
/* 0x0370F8 0x100000F8 194  */ extern UNK_TYPE utob;
/* 0x0370FC 0x100000FC 195  */ extern UNK_TYPE patch;
/* 0x037100 0x10000100 196  */ extern /* string */ char* filter;
/* 0x037104 0x10000104 197  */ extern UNK_TYPE prelinker;
/* 0x037108 0x10000108 198  */ extern UNK_TYPE smart_build;
/* 0x03710C 0x1000010C 199  */ extern UNK_TYPE sbrepos;
/* 0x037110 0x10000110 200  */ extern UNK_TYPE no_prelink;
/* 0x037114 0x10000114 201  */ extern /* boolean */ int nofilt;
/* 0x037118 0x10000118 202  */ extern UNK_TYPE force_prelink;
/* 0x03711C 0x1000011C 203  */ extern UNK_TYPE verbose_prelink;
/* 0x037120 0x10000120 204  */ extern UNK_TYPE auto_template_include;
/* 0x037124 0x10000124 205  */ extern UNK_TYPE nocode;
/* 0x037128 0x10000128 206  */ extern UNK_TYPE nocompileneeded;
/* 0x03712C 0x1000012C 207  */ extern char* LibM;
/* 0x037130 0x10000130 208  */ extern char* LibP;
/* 0x037134 0x10000134 209  */ extern char* LibF77;
/* 0x037138 0x10000138 210  */ extern char* LibI77;
/* 0x03713C 0x1000013C 211  */ extern char* LibU77;
/* 0x037140 0x10000140 212  */ extern char* LibIsam;
/* 0x037144 0x10000144 213  */ extern char* LibExc;
/* 0x037148 0x10000148 214  */ extern char* LibDw;
/* 0x03714C 0x1000014C 215  */ extern char* LibPl1;
/* 0x037150 0x10000150 216  */ extern char* LibCob;
/* 0x037154 0x10000154 217  */ extern char* LibSort;
/* 0x037158 0x10000158 218  */ extern char* LibProf1;
/* 0x03715C 0x1000015C 219  */ extern char* LibXmalloc;
/* 0x037160 0x10000160 220  */ extern UNK_TYPE LibMld;
/* 0x037164 0x10000164 221  */ extern UNK_TYPE crtx;
/* 0x037168 0x10000168 222  */ extern UNK_TYPE crtn;
/* 0x03716C 0x1000016C 223  */ extern UNK_TYPE cxx_init;
/* 0x037170 0x10000170 224  */ extern UNK_TYPE delta_init;
/* 0x037174 0x10000174 225  */ extern UNK_TYPE libp;
/* 0x037178 0x10000178 226  */ extern UNK_TYPE libp_b;
/* 0x03717C 0x1000017C 227  */ extern UNK_TYPE libm;
/* 0x037180 0x10000180 228  */ extern UNK_TYPE libm_b;
/* 0x037184 0x10000184 229  */ extern UNK_TYPE libF77;
/* 0x037188 0x10000188 230  */ extern UNK_TYPE libF77_b;
/* 0x03718C 0x1000018C 231  */ extern UNK_TYPE libI77;
/* 0x037190 0x10000190 232  */ extern UNK_TYPE libI77_b;
/* 0x037194 0x10000194 233  */ extern UNK_TYPE libU77;
/* 0x037198 0x10000198 234  */ extern UNK_TYPE libftn;
/* 0x03719C 0x1000019C 235  */ extern UNK_TYPE libU77_b;
/* 0x0371A0 0x100001A0 236  */ extern UNK_TYPE libisam;
/* 0x0371A4 0x100001A4 237  */ extern UNK_TYPE libisam_b;
/* 0x0371A8 0x100001A8 238  */ extern UNK_TYPE libdw_path;
/* 0x0371AC 0x100001AC 239  */ extern UNK_TYPE libdw;
/* 0x0371B0 0x100001B0 240  */ extern UNK_TYPE libdw_b;
/* 0x0371B4 0x100001B4 241  */ extern UNK_TYPE libpl1;
/* 0x0371B8 0x100001B8 242  */ extern UNK_TYPE libpl1_b;
/* 0x0371BC 0x100001BC 243  */ extern UNK_TYPE libexc;
/* 0x0371C0 0x100001C0 244  */ extern UNK_TYPE libexc_b;
/* 0x0371C4 0x100001C4 21   */ extern UNK_TYPE libcob; // dynsym reorder?
/* 0x0371C8 0x100001C8 22   */ extern UNK_TYPE libcob_b;
/* 0x0371CC 0x100001CC 245  */ extern UNK_TYPE libsort; // dynsym reorder?
/* 0x0371D0 0x100001D0 246  */ extern UNK_TYPE libsort_b;
/* 0x0371D4 0x100001D4 247  */ extern UNK_TYPE libprof;
/* 0x0371D8 0x100001D8 248  */ extern UNK_TYPE libxmalloc;
/* 0x0371DC 0x100001DC 249  */ extern UNK_TYPE libxmalloc_b;
/* 0x0371E0 0x100001E0 250  */ extern UNK_TYPE cpp_stdflag;
/* 0x0371E4 0x100001E4 251  */ extern UNK_TYPE libmld;
/* 0x0371E8 0x100001E8 252  */ extern UNK_TYPE crtn_required;
/* 0x0371EC 0x100001EC 253  */ extern UNK_TYPE pca;
/* 0x0371F0 0x100001F0 254  */ extern UNK_TYPE libc_mp;
/* 0x0371F4 0x100001F4 255  */ extern UNK_TYPE fopt;
/* 0x0371F8 0x100001F8 256  */ extern UNK_TYPE copt;
/* 0x0371FC 0x100001FC None */ /* static */ extern UNK_TYPE D_100001FC;
/* 0x037200 0x10000200 None */ /* static */ extern UNK_TYPE D_10000200;
/* 0x037204 0x10000204 None */ /* static */ extern UNK_TYPE D_10000204;
/* 0x037208 0x10000208 None */ /* static */ extern UNK_TYPE D_10000208;
/* 0x03720C 0x1000020C None */ /* static */ extern UNK_TYPE D_1000020C;
/* 0x037210 0x10000210 None */ /* static */ extern UNK_TYPE D_10000210;
/* 0x037214 0x10000214 257  */ extern /* boolean */ int Eflag;
/* 0x037218 0x10000218 258  */ extern UNK_TYPE Pflag;
/* 0x03721C 0x1000021C 259  */ extern UNK_TYPE gflag;
/* 0x037220 0x10000220 260  */ extern UNK_TYPE pflag;
/* 0x037224 0x10000224 261  */ extern UNK_TYPE jflag;
/* 0x037228 0x10000228 262  */ extern UNK_TYPE cflag;
/* 0x03722C 0x1000022C 263  */ extern UNK_TYPE Sflag;
/* 0x037230 0x10000230 264  */ extern UNK_TYPE Oflag;
/* 0x037234 0x10000234 265  */ extern UNK_TYPE vflag;
/* 0x037238 0x10000238 266  */ extern UNK_TYPE execute_flag;
/* 0x03723C 0x1000023C 267  */ extern /* boolean */ int Vflag;
/* 0x037240 0x10000240 268  */ extern /* boolean */ int Kflag;
/* 0x037244 0x10000244 269  */ extern UNK_TYPE minus_M;
/* 0x037248 0x10000248 270  */ extern UNK_TYPE anachronisms;
/* 0x03724C 0x1000024C 271  */ extern UNK_TYPE disable_inlines;
/* 0x037250 0x10000250 272  */ extern UNK_TYPE cfront_compatible;
/* 0x037254 0x10000254 273  */ extern UNK_TYPE make_edison_shlib;
/* 0x037258 0x10000258 274  */ extern UNK_TYPE plusIflag;
/* 0x03725C 0x1000025C 275  */ extern UNK_TYPE signedcharflag;
/* 0x037260 0x10000260 276  */ extern UNK_TYPE Lflag;
/* 0x037264 0x10000264 277  */ extern UNK_TYPE set_loop_unroll;
/* 0x037268 0x10000268 278  */ extern UNK_TYPE mflag;
/* 0x03726C 0x1000026C 279  */ extern UNK_TYPE Fflag;
/* 0x037270 0x10000270 280  */ extern UNK_TYPE stdflag;
/* 0x037274 0x10000274 281  */ extern UNK_TYPE cplusflag;
/* 0x037278 0x10000278 282  */ extern UNK_TYPE ucodeflag;
/* 0x03727C 0x1000027C 283  */ extern UNK_TYPE Bflag;
/* 0x037280 0x10000280 284  */ extern /* boolean */ int fiveflag;
/* 0x037284 0x10000284 285  */ extern UNK_TYPE automaticflag;
/* 0x037288 0x10000288 286  */ extern UNK_TYPE emptyIflag;
/* 0x03728C 0x1000028C 287  */ extern UNK_TYPE cordflag;
/* 0x037290 0x10000290 288  */ extern UNK_TYPE ansiflag;
/* 0x037294 0x10000294 289  */ extern UNK_TYPE lpilockflag;
/* 0x037298 0x10000298 290  */ extern UNK_TYPE nolockflag;
/* 0x03729C 0x1000029C 291  */ extern UNK_TYPE unrollflag;
/* 0x0372A0 0x100002A0 292  */ extern UNK_TYPE libm_spec;
/* 0x0372A4 0x100002A4 293  */ extern UNK_TYPE libfastm_spec;
/* 0x0372A8 0x100002A8 294  */ extern EditFlag editflag;
/* 0x0372AC 0x100002AC 295  */ extern UNK_TYPE oldccomflag;
/* 0x0372B0 0x100002B0 296  */ extern UNK_TYPE oldcflag;
/* 0x0372B4 0x100002B4 297  */ extern UNK_TYPE oldcppflag;
/* 0x0372B8 0x100002B8 23   */ extern UNK_TYPE fflag;  // dynsym reorder?
/* 0x0372BC 0x100002BC 298  */ extern UNK_TYPE tpflag; // dynsym reorder?
/* 0x0372C0 0x100002C0 299  */ extern UNK_TYPE ddoptflag;
/* 0x0372C4 0x100002C4 300  */ extern UNK_TYPE uopt0flag;
/* 0x0372C8 0x100002C8 24   */ extern UNK_TYPE protoflag;   // dynsym reorder?
/* 0x0372CC 0x100002CC 301  */ extern UNK_TYPE kminabiflag; // dynsym reorder?
/* 0x0372D0 0x100002D0 302  */ extern UNK_TYPE kpicopt_flag;
/* 0x0372D4 0x100002D4 303  */ extern UNK_TYPE nokpicopt_flag;
/* 0x0372D8 0x100002D8 304  */ extern UNK_TYPE elfflag;
/* 0x0372DC 0x100002DC 305  */ extern UNK_TYPE coff_spec;
/* 0x0372E0 0x100002E0 306  */ extern UNK_TYPE elf_spec;
/* 0x0372E4 0x100002E4 307  */ extern UNK_TYPE compose_first_G0;
/* 0x0372E8 0x100002E8 308  */ extern UNK_TYPE mips1_spec_flag;
/* 0x0372EC 0x100002EC 309  */ extern UNK_TYPE mips1flag;
/* 0x0372F0 0x100002F0 310  */ extern UNK_TYPE mips2flag;
/* 0x0372F4 0x100002F4 311  */ extern UNK_TYPE mips3flag;
/* 0x0372F8 0x100002F8 312  */ extern UNK_TYPE ignore_unresolved_flag;
/* 0x0372FC 0x100002FC 313  */ extern UNK_TYPE no_unresolved_flag;
/* 0x037300 0x10000300 314  */ extern UNK_TYPE swopcodeflag;
/* 0x037304 0x10000304 315  */ extern UNK_TYPE dwopcodeflag;
/* 0x037308 0x10000308 316  */ extern UNK_TYPE sixty4bit_spec;
/* 0x03730C 0x1000030C 317  */ extern UNK_TYPE sixty4bitflag;
/* 0x037310 0x10000310 318  */ extern UNK_TYPE thirty2bitflag;
/* 0x037314 0x10000314 319  */ extern UNK_TYPE fullasoptflag;
/* 0x037318 0x10000318 320  */ extern UNK_TYPE old_non_shared;
/* 0x03731C 0x1000031C 321  */ extern UNK_TYPE non_shared_emitted;
/* 0x037320 0x10000320 322  */ extern UNK_TYPE longlong_emitted;
/* 0x037324 0x10000324 323  */ extern UNK_TYPE non_shared;
/* 0x037328 0x10000328 324  */ extern UNK_TYPE Gseen_flag;
/* 0x03732C 0x1000032C 325  */ extern UNK_TYPE transitive_link;
/* 0x037330 0x10000330 326  */ extern UNK_TYPE full_transitive_link;
/* 0x037334 0x10000334 327  */ extern UNK_TYPE no_transitive_link;
/* 0x037338 0x10000338 328  */ extern UNK_TYPE quickstart_info;
/* 0x03733C 0x1000033C 329  */ extern UNK_TYPE force_rm_dead_code;
/* 0x037340 0x10000340 330  */ extern UNK_TYPE kpic_flag;
/* 0x037344 0x10000344 331  */ extern UNK_TYPE kpic_spec;
/* 0x037348 0x10000348 332  */ extern UNK_TYPE call_shared;
/* 0x03734C 0x1000034C 333  */ extern UNK_TYPE excpt_flag;
/* 0x037350 0x10000350 334  */ extern UNK_TYPE trapuv_flag;
/* 0x037354 0x10000354 335  */ extern UNK_TYPE dmips_emit;
/* 0x037358 0x10000358 25   */ extern UNK_TYPE Xvalues_Flag;          // dynsym reorder?
/* 0x03735C 0x1000035C 336  */ extern /* boolean */ int user_systype; // dynsym reorder?
/* 0x037360 0x10000360 337  */ extern UNK_TYPE ddoptinfo;
/* 0x037364 0x10000364 338  */ extern UNK_TYPE systype_seen;
/* 0x037368 0x10000368 339  */ extern UNK_TYPE multiple_systype;
/* 0x03736C 0x1000036C 340  */ extern /* boolean */ int systype_warn;
/* 0x037370 0x10000370 341  */ extern /* boolean */ int svr4_systype;
/* 0x037374 0x10000374 342  */ extern UNK_TYPE c_inline;
/* 0x037378 0x10000378 343  */ extern UNK_TYPE tfp_flag;
/* 0x03737C 0x1000037C 344  */ extern UNK_TYPE abi_flag;
/* 0x037380 0x10000380 345  */ extern UNK_TYPE memory_flag;
/* 0x037384 0x10000384 346  */ extern UNK_TYPE default_call_shared;
/* 0x037388 0x10000388 347  */ extern UNK_TYPE haspascal;
/* 0x03738C 0x1000038C 348  */ extern UNK_TYPE hasfortran;
/* 0x037390 0x10000390 349  */ extern UNK_TYPE lmflag;
/* 0x037394 0x10000394 350  */ extern UNK_TYPE srcexists;
/* 0x037398 0x10000398 351  */ extern UNK_TYPE w1flag;
/* 0x03739C 0x1000039C None */ /* static */ extern UNK_TYPE D_1000039C;
/* 0x0373A0 0x100003A0 352  */ extern UNK_TYPE prototype_checking_on;
/* 0x0373A4 0x100003A4 353  */ extern UNK_TYPE showdirt_flag;
/* 0x0373A8 0x100003A8 354  */ extern UNK_TYPE mp_prepass_count;
/* 0x0373AC 0x100003AC 355  */ extern UNK_TYPE mpflags;
/* 0x0373C4 0x100003C4 356  */ extern UNK_TYPE cmpflags;
/* 0x0373DC 0x100003DC 357  */ extern UNK_TYPE acpp;
/* 0x0373E0 0x100003E0 358  */ extern UNK_TYPE mips_abi;
/* 0x0373E4 0x100003E4 359  */ extern UNK_TYPE compchoice;
/* 0x0373E8 0x100003E8 360  */ extern UNK_TYPE cppchoice;
/* 0x0373EC 0x100003EC 361  */ extern UNK_TYPE acpp_traditional;
/* 0x0373F0 0x100003F0 362  */ extern UNK_TYPE G_flag;
/* 0x0373F4 0x100003F4 363  */ extern UNK_TYPE dn_flag;
/* 0x0373F8 0x100003F8 364  */ extern UNK_TYPE edison_cpp;
/* 0x0373FC 0x100003FC 365  */ extern UNK_TYPE edison_type;
/* 0x037400 0x10000400 366  */ extern UNK_TYPE Gnum;
/* 0x037404 0x10000404 367  */ extern int runerror;
/* 0x037408 0x10000408 368  */ extern UNK_TYPE uload;
/* 0x03740C 0x1000040C 369  */ extern UNK_TYPE uldobj_place;
/* 0x037410 0x10000410 370  */ extern char* tmp_uldobj;
/* 0x037414 0x10000414 371  */ extern UNK_TYPE chip_targ;
/* 0x037418 0x10000418 372  */ extern UNK_TYPE nobjs;
/* 0x03741C 0x1000041C 373  */ extern int targetsex;
/* 0x037420 0x10000420 374  */ extern UNK_TYPE default_svr4;
/* 0x037424 0x10000424 375  */ extern /* boolean */ int irix4;
/* 0x037428 0x10000428 376  */ extern char* runlib;
/* 0x03742C 0x1000042C 377  */ extern char* runlib_base;
/* 0x037430 0x10000430 None */ /* static */ extern int D_10000430;
/* 0x037438 0x10000438 None */ /* static */ extern char* D_10000438; // current working directory (D_1000C1D0 in 7.1)
/* 0x03743C 0x1000043C 378  */ extern UNK_TYPE run_sopt;
/* 0x037440 0x10000440 None */ /* static */ extern char* D_10000440;
/* 0x037444 0x10000444 None */ /* static */ extern char* D_10000444;
/* 0x037448 0x10000448 None */ /* static */ extern char* D_10000448; // Error category strings
/* 0x037460 0x10000460 379  */ extern UNK_TYPE prod_name;
/* 0x037550 0x10000550 None */ /* static */ extern UNK_TYPE D_10000550;
/* 0x037554 0x10000554 None */ /* static */ extern UNK_TYPE D_10000554;
/* 0x037558 0x10000558 None */ /* static */ extern char* D_10000558; // program_name (D_1000C2F0 in 7.1)

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
// int parse_command();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/parse_command.s")

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
            fprintf(stderr, "%s: Error: error (), %d: Out of memory\n", D_10000440, 0x3281);
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

/**
 * relocate_passes
 * Address: 0x0042B254
 * VROM: 0x02B254
 * Size: 0x3F5C
 */
// int relocate_passes();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/relocate_passes.s")

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

/**
 * mkstr
 * Address: 0x0042F8B4
 * VROM: 0x02F8B4
 * Size: 0x214
 */
// int mkstr();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/mkstr.s")

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
// int mksuf();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/mksuf.s")

/**
 * savestr
 * Address: 0x00430EBC
 * VROM: 0x030EBC
 * Size: 0x140
 */
// Copy a string, adding extra_length bytes to the allocation.
/* string */ char* savestr(const /* string */ char* src, int extra_length) {
    char* dest = malloc(strlen(src) + extra_length + 1);

    if (dest == NULL) {
        error(ERRORCAT_ERROR, NULL, 0, "savestr ()", 0x38FE, "out of memory\n");
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
// int run();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/run.s")

/**
 * edit_src
 * Address: 0x00432660
 * VROM: 0x032660
 * Size: 0x4FC
 */
// int edit_src();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/edit_src.s")

/**
 * get_lino
 * Address: 0x00432B5C
 * VROM: 0x032B5C
 * Size: 0x5B0
 */
// int get_lino();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/get_lino.s")

/**
 * show_err
 * Address: 0x0043310C
 * VROM: 0x03310C
 * Size: 0x10C
 */
// int show_err();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/show_err.s")

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
// /* static */ int func_004339C8();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/func_004339C8.s")

/**
 * isdir
 * Address: 0x00433C28
 * VROM: 0x033C28
 * Size: 0x7C
 */
// int isdir();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/isdir.s")

/**
 * regular_not_writeable
 * Address: 0x00433CA4
 * VROM: 0x033CA4
 * Size: 0x98
 */
// int regular_not_writeable();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/regular_not_writeable.s")

/**
 * regular_file
 * Address: 0x00433D3C
 * VROM: 0x033D3C
 * Size: 0x7C
 */
// int regular_file();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/regular_file.s")

/**
 * basename
 * Address: 0x00433DB8
 * VROM: 0x033DB8
 * Size: 0x118
 */
char* basename(const char*);
#pragma GLOBAL_ASM("asm/5.3/functions/cc/basename.s")

/**
 * dirname
 * Address: 0x00433ED0
 * VROM: 0x033ED0
 * Size: 0x1C4
 */
char* dirname(const char*);
#pragma GLOBAL_ASM("asm/5.3/functions/cc/dirname.s")

static const char STR_10006754[] = "accom";
static const char STR_1000675C[] = "/usr/lib/accom";
static const char STR_1000676C[] = "ANSI C";
static const char STR_10006774[] = "ccom";
static const char STR_1000677C[] = "/usr/lib/ccom";
static const char STR_1000678C[] = "ANSI C";
static const char STR_10006794[] = "acpp";
static const char STR_1000679C[] = "/usr/lib/acpp";
static const char STR_100067AC[] = "ANSI C";
static const char STR_100067B4[] = "cpp";
static const char STR_100067B8[] = "/usr/lib/cpp";
static const char STR_100067C8[] = "Development option";
static const char STR_100067DC[] = "fcom";
static const char STR_100067E4[] = "/usr/lib/fcom";
static const char STR_100067F4[] = "Fortran";
static const char STR_100067FC[] = "fopt";
static const char STR_10006804[] = "/usr/lib/fopt";
static const char STR_10006814[] = "Fortran";
static const char STR_1000681C[] = "pfa";
static const char STR_10006820[] = "/usr/lib/pfa";
static const char STR_10006830[] = "Power Fortran";
static const char STR_10006840[] = "accom_mp";
static const char STR_1000684C[] = "/usr/lib/accom_mp";
static const char STR_10006860[] = "Power C";
static const char STR_10006868[] = "ccom_mp";
static const char STR_10006870[] = "/usr/lib/ccom_mp";
static const char STR_10006884[] = "Power C";
static const char STR_1000688C[] = "pca";
static const char STR_10006890[] = "/usr/lib/pca";
static const char STR_100068A0[] = "Power C";
static const char STR_100068A8[] = "copt";
static const char STR_100068B0[] = "/usr/lib/copt";
static const char STR_100068C0[] = "ANSI C";
static const char STR_100068C8[] = "upas";
static const char STR_100068D0[] = "/usr/lib/upas";
static const char STR_100068E0[] = "Pascal";
static const char STR_100068E8[] = "pl1fe";
static const char STR_100068F0[] = "/usr/lib/pl1fe";
static const char STR_10006900[] = "PL/1";
static const char STR_10006908[] = "pl1error";
static const char STR_10006914[] = "/usr/lib/pl1error";
static const char STR_10006928[] = "PL/1";
static const char STR_10006930[] = "as0";
static const char STR_10006934[] = "/usr/lib/as0";
static const char STR_10006944[] = "Development option";
static const char STR_10006958[] = "as1";
static const char STR_1000695C[] = "/usr/lib/as1";
static const char STR_1000696C[] = "Development option";
static const char STR_10006980[] = "ld";
static const char STR_10006984[] = "/usr/lib/ld";
static const char STR_10006990[] = "Development option";
static const char STR_100069A4[] = "cobfe";
static const char STR_100069AC[] = "/usr/lib/cobfe";
static const char STR_100069BC[] = "COBOL";
static const char STR_100069C4[] = "edgcpfe";
static const char STR_100069CC[] = "/usr/lib/DCC/edgcpfe";
static const char STR_100069E4[] = "Delta C++";
static const char STR_100069F0[] = "edgcpfe.alt";
static const char STR_100069FC[] = "/usr/lib/DCC/edgcpfe.alt";
static const char STR_10006A18[] = "Delta C++";

/**
 * func_00434094
 * Address: 0x00434094
 * VROM: 0x034094
 * Size: 0x134
 */
// /* static */ int func_00434094();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/func_00434094.s")

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
/* string */ char* full_path(/* string */ char* base) {
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
// int add_static_opt();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/add_static_opt.s")

/**
 * record_static_fileset
 * Address: 0x00434444
 * VROM: 0x034444
 * Size: 0x9F4
 */
// int record_static_fileset();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/record_static_fileset.s")

/**
 * touch
 * Address: 0x00434E38
 * VROM: 0x034E38
 * Size: 0x17C
 */
// int touch();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/touch.s")

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
        fprintf(new_ii, "CMDLINE=%s %s%s%s\n", progname, (((srcfiles.length == 1) && (cflag == 0)) ? "-c " : ""),
                ((((srcfiles.length == 1) && (cflag == 0)) || (B_1000A49C == NULL)) ? "" : B_1000A49C), B_1000A48C);
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

/**
 * func_004362CC
 * Address: 0x004362CC
 * VROM: 0x0362CC
 * Size: 0x2EC
 */
// /* static */ int func_004362CC();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/func_004362CC.s")

/**
 * func_004365B8
 * Address: 0x004365B8
 * VROM: 0x0365B8
 * Size: 0xC8
 */
// /* static */ int func_004365B8();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/func_004365B8.s")

/**
 * func_00436680
 * Address: 0x00436680
 * VROM: 0x036680
 * Size: 0xBC
 */
// /* static */ int func_00436680();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/func_00436680.s")

/**
 * func_0043673C
 * Address: 0x0043673C
 * VROM: 0x03673C
 * Size: 0x844
 */
// /* static */ int func_0043673C();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/func_0043673C.s")
