#include "stdio.h"

typedef struct {
    int capacity;
    int length;
    char** entries;
} list;

typedef int UNK_TYPE;

/* 03F310 10008310 */ static char B_10008310[0x1900]; // equivalent of B_1000CAC0
/* 040C10 10009C10 */ int time0; // line 174
// 0x4 padding
    /* 040C18 10009C18 */ struct tms tm0; // line 176
/* 040C28 10009C28 */ char perr_msg[0x100]; // char perr_msg[0x100]; // line 124
/* 040D28 10009D28 */ static char B_10009D28[0x400]; // equivalent of B_1000E5E0
/* 041128 1000A128 */ int plain_g; // line 127
/* 04112C 1000A12C */ int plain_O; // line 128
/* 041130 1000A130 */ int noaliasokflag; // line 129
/* 041134 1000A134 */ int haspl1; // line 130
/* 041138 1000A138 */ UNK_TYPE p2cstr; // line 132
/* 04113C 1000A13C */ int align; // line 133
/* 041140 1000A140 */ int align_common; // line 134
/* 041144 1000A144 */ char* alignarg; // line 136
/* 041148 1000A148 */ int use_real_fp; // line 137
/* 04114C 1000A14C */ int dollar_sign; // line 138
/* 041150 1000A150 */ int mp_flag; // line 140
/* 041154 1000A154 */ int mp_onetripflag; // line 141
/* 041158 1000A158 */ UNK_TYPE mp_staticflag; // line 142
/* 04115C 1000A15C */ int mp_dlinesflag; // line 143
/* 041160 1000A160 */ int mp_caseflag; // line 144
/* 041164 1000A164 */ int mp_66flag; // line 146
/* 041168 1000A168 */ int mp_i2flag; // line 148
/* 04116C 1000A16C */ int mp_col120flag; // line 150
/* 041170 1000A170 */ int mp_extendflag; // line 151
/* 041174 1000A174 */ int mp_uflag; // line 152
/* 041178 1000A178 */ int mp_backslashflag; // line 153
/* 04117C 1000A17C */ UNK_TYPE mp_uniq_specified; // line 154
/* 041180 1000A180 */ UNK_TYPE mp_passes_relocated; // line 155
    /* 041184 1000A184 */ int default_template_instantiation_mode; // line 139
/* 041188 1000A188 */ int cmp_flag; // line 156
    /* 04118C 1000A18C */ UNK_TYPE efl; // line 145
    /* 041190 1000A190 */ char* ratfor; // line 147
    /* 041194 1000A194 */ char* m4; // line 149
/* 041198 1000A198 */ int fullwarn; // line 157
/* 04119C 1000A19C */ char* aligndir; // line 158
/* 0411A0 1000A1A0 */ int docpp; // line 159
/* 0411A4 1000A1A4 */ int default_nocpp; // line 160
/* 0411A8 1000A1A8 */ unsigned int j; // line 161
/* 0411AC 1000A1AC */ char* tstring; // line 162
/* 0411B0 1000A1B0 */ char* hstring; // line 163
/* 0411B4 1000A1B4 */ char* Bstring; // line 164
/* 0411B8 1000A1B8 */ const char* allBstring; // line 165
// 0x4 padding
/* 0411C0 1000A1C0 */ char alltstring[20]; // line 167
/* 0411D4 1000A1D4 */ char* Warg; // line 168
/* 0411D8 1000A1D8 */ char* Wpass; // line 169
/* 0411DC 1000A1DC */ char* Kpass; // line 170
/* 0411E0 1000A1E0 */ char Karg[6]; // line 171
/* 0411E6 1000A1E6 */ char Hchar; // line 172
/* 0411E8 1000A1E8 */ int retcode; // line 177
/* 0411EC 1000A1EC */ char* outfile; // line 178
/* 0411F0 1000A1F0 */ char* passin; // line 179
/* 0411F4 1000A1F4 */ char* passout; // line 180
/* 0411F8 1000A1F8 */ char* errout; // line 181
/* 0411FC 1000A1FC */ char* symtab; // line 182
/* 041200 1000A200 */ char* uopt0str; // line 183
/* 041204 1000A204 */ char* ddoptstr; // line 184
/* 041208 1000A208 */ char* optstr; // line 185
/* 04120C 1000A20C */ char* gentmp; // line 186
/* 041210 1000A210 */ char* binasm; // line 187
/* 041214 1000A214 */ char* uoutfile; // line 188
/* 041218 1000A218 */ char* lpi_st; // line 189
/* 04121C 1000A21C */ char* lpi_p1; // line 190
/* 041220 1000A220 */ char* lpi_dd; // line 191
/* 041224 1000A224 */ char* lpi_pd; // line 194
/* 041228 1000A228 */ char* linkorder; // line 195
/* 04122C 1000A22C */ UNK_TYPE valuesstr; // line 196
/* 041230 1000A230 */ UNK_TYPE tmp_elfobj; // line 197
/* 041234 1000A234 */ FILE* ldw_file; // line 199
/* 041238 1000A238 */ FILE* tmpsfile; // line 201
/* 04123C 1000A23C */ char* editor; // line 203
/* 041240 1000A240 */ int xserver; // line 205
/* 041244 1000A244 */ int times_edited; // line 207
/* 041248 1000A248 */ int edit_cnt_max; // line 209
/* 04124C 1000A24C */ char srcsuf; // line 213
/* 041250 1000A250 */ int tmpst; // line 216
    /* 041254 1000A254 */ char* CRTX; // line 198
    /* 041258 1000A258 */ char* MCRTX; // line 200
/* 04125C 1000A25C */ char* comp_target_root; // line 222
    /* 041260 1000A260 */ list undefineflags; // line 202
        /* 04126C 1000A26C */ char* comp_host_root; // line 261
    /* 041270 1000A270 */ list cppflags; // line 204
/* 04127C 1000A27C */ char* systype; // line 226
    /* 041280 1000A280 */ list olimitflags; // line 206
    /* 04128C 1000A28C */ int nonshared; // line 228
/* 041290 1000A290 */ list acppflags; // line 208
// 0x4 padding
/* 0412A0 1000A2A0 */ list mpcflags; // line 210
// 0x4 padding
/* 0412B0 1000A2B0 */ list accomflags; // line 212
// 0x4 padding
/* 0412C0 1000A2C0 */ list cfeflags; // line 215
// 0x4 padding
/* 0412D0 1000A2D0 */ list cpp2flags; // line 217
// 0x4 padding
/* 0412E0 1000A2E0 */ list uldlibflags; // line 219
// 0x4 padding
/* 0412F0 1000A2F0 */ list edisonflags; // line 221
    /* 0412FC 1000A2FC */ char* tmpdir; // line 242
/* 041300 1000A300 */ list prelinkerflags; // line 223
    /* 04130C 1000A30C */ char* rls_id_object; // line 244
/* 041310 1000A310 */ list ccomflags; // line 225
    /* 04131C 1000A31C */ char* progname; // line 246
/* 041320 1000A320 */ list upasflags; // line 227
    /* 04132C 1000A32C */ char* currcomp; // line 248
/* 041330 1000A330 */ list fcomflags; // line 229
// 0x4 padding
    /* 041340 1000A340 */ char* compdirs[7]; // line 251
// 0x4 padding
/* 041360 1000A360 */ list eflflags; // line 231
    /* 04136C 1000A36C */ int compiler; // line 264
/* 041370 1000A370 */ list ratforflags; // line 233
// 0x4 padding
    /* 041380 1000A380 */ char* tempstr[34]; // line 268
/* 041408 1000A408 */ list upl1flags; // line 235
// 0x4 padding
/* 041418 1000A418 */ list ucobflags; // line 237
// 0x4 padding
/* 041428 1000A428 */ list ulpiflags; // line 239
// 0x4 padding
/* 041438 1000A438 */ list ujoinflags; // line 241
// 0x4 padding
/* 041448 1000A448 */ list uldflags; // line 243
// 0x4 padding
/* 041458 1000A458 */ static char B_1000A458[0x08];
/* 041460 1000A460 */ list usplitflags; // line 245
// 0x4 padding
/* 041470 1000A470 */ list umergeflags; // line 247
// 0x4 padding
/* 041480 1000A480 */ list uloopflags; // line 249
/* 04148C 1000A48C */ static char B_1000A48C[0x04];
/* 041490 1000A490 */ list uopt0flags; // line 253
/* 04149C 1000A49C */ static char B_1000A49C[0x04];
/* 0414A0 1000A4A0 */ list ddoptflags; // line 266
// 0x4 padding
/* 0414B0 1000A4B0 */ list optflags; // line 269
// 0x4 padding
/* 0414C0 1000A4C0 */ list genflags; // line 271
// 0x4 padding
/* 0414D0 1000A4D0 */ list asflags; // line 273
// 0x4 padding
/* 0414E0 1000A4E0 */ list ldflags; // line 277
// 0x4 padding
/* 0414F0 1000A4F0 */ list as1flags; // line 275
// 0x4 padding
/* 041500 1000A500 */ list ftocflags; // line 282
// 0x4 padding
/* 041510 1000A510 */ list cordflags; // line 284
// 0x4 padding
/* 041520 1000A520 */ list srcfiles; // line 286
// 0x4 padding
/* 041530 1000A530 */ list ufiles; // line 288
// 0x4 padding
/* 041540 1000A540 */ list objfiles; // line 290
// 0x4 padding
/* 041550 1000A550 */ list feedlist; // line 292
// 0x4 padding
/* 041560 1000A560 */ list execlist; // line 294
/* 04156C 1000A56C */ static char B_1000A56C[0x04];
/* 041570 1000A570 */ static char B_1000A570[0x08];
/* 041578 1000A578 */ list dirs_for_crtn; // line 299
// 0x4 padding
/* 041588 1000A588 */ list dirs_for_nonshared_crtn; // line 301
// 0x4 padding
/* 041598 1000A598 */ list dirs_for_abi_crtn; // line 303
// 0x4 padding
/* 0415A8 1000A5A8 */ list ldZflags; // line 305
/* 0415B4 1000A5B4 */ static char B_1000A5B4[0x04];
/* 0415B8 1000A5B8 */ list pfaflags; // line 307
/* 0415C4 1000A5C4 */ char* pfa; // line 307
/* 0415C8 1000A5C8 */ char* libI77_mp; // line 309
// 0x4 padding
/* 0415D0 1000A5D0 */ list pcaflags; // line 311
// 0x4 padding
/* 0415E0 1000A5E0 */ list soptflags; // line 313
// 0x4 padding
/* 0415F0 1000A5F0 */ list staticopts; // line 315
// 0x4 padding
/* 041600 1000A600 */ int __Argc; // line 319
/* 041604 1000A604 */ char** __Argv; // line 317
/* 041608 1000A608 */ UNK_TYPE __rld_obj_head; // line 318
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
// int process_config();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/process_config.s")

/**
 * add_info
 * Address: 0x0041C2F0
 * VROM: 0x01C2F0
 * Size: 0x12C
 */
// int add_info();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/add_info.s")

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
// int get_host_chiptype();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/get_host_chiptype.s")

/**
 * error
 * Address: 0x0042AE94
 * VROM: 0x02AE94
 * Size: 0x3C0
 */
// int error();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/error.s")

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
// int newrunlib();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/newrunlib.s")

/**
 * compose_G0_libs
 * Address: 0x0042F2CC
 * VROM: 0x02F2CC
 * Size: 0x30C
 */
// int compose_G0_libs();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/compose_G0_libs.s")

/**
 * compose_reg_libs
 * Address: 0x0042F5D8
 * VROM: 0x02F5D8
 * Size: 0x2DC
 */
// int compose_reg_libs();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/compose_reg_libs.s")

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
// int mklist();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/mklist.s")

/**
 * addstr
 * Address: 0x0042FBF8
 * VROM: 0x02FBF8
 * Size: 0x194
 */
// int addstr();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/addstr.s")

/**
 * addspacedstr
 * Address: 0x0042FD8C
 * VROM: 0x02FD8C
 * Size: 0x1E8
 */
// int addspacedstr();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/addspacedstr.s")

/**
 * newstr
 * Address: 0x0042FF74
 * VROM: 0x02FF74
 * Size: 0xA4
 */
// int newstr();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/newstr.s")

/**
 * save_place
 * Address: 0x00430018
 * VROM: 0x030018
 * Size: 0x184
 */
// int save_place();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/save_place.s")

/**
 * set_place
 * Address: 0x0043019C
 * VROM: 0x03019C
 * Size: 0xC4
 */
// int set_place();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/set_place.s")

/**
 * addlist
 * Address: 0x00430260
 * VROM: 0x030260
 * Size: 0x214
 */
// int addlist();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/addlist.s")

/**
 * adduldlist
 * Address: 0x00430474
 * VROM: 0x030474
 * Size: 0x384
 */
// int adduldlist();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/adduldlist.s")

/**
 * nodup
 * Address: 0x004307F8
 * VROM: 0x0307F8
 * Size: 0xBC
 */
// int nodup();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/nodup.s")

/**
 * getsuf
 * Address: 0x004308B4
 * VROM: 0x0308B4
 * Size: 0x258
 */
// int getsuf();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/getsuf.s")

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
// int savestr();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/savestr.s")

/**
 * mktempstr
 * Address: 0x00430FFC
 * VROM: 0x030FFC
 * Size: 0x930
 */
// int mktempstr();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/mktempstr.s")

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
// int handler();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/handler.s")

/**
 * cleanup
 * Address: 0x00433260
 * VROM: 0x033260
 * Size: 0x3EC
 */
// int cleanup();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/cleanup.s")

/**
 * whats
 * Address: 0x0043364C
 * VROM: 0x03364C
 * Size: 0x1C0
 */
// int whats();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/whats.s")

/**
 * settimes
 * Address: 0x0043380C
 * VROM: 0x03380C
 * Size: 0x3C
 */
// int settimes();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/settimes.s")

/**
 * dotime
 * Address: 0x00433848
 * VROM: 0x033848
 * Size: 0x180
 */
// int dotime();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/dotime.s")

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
// int basename();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/basename.s")

/**
 * dirname
 * Address: 0x00433ED0
 * VROM: 0x033ED0
 * Size: 0x1C4
 */
// int dirname();
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
// int add_cxx_symbol_options();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/add_cxx_symbol_options.s")

/**
 * init_curr_dir
 * Address: 0x00434208
 * VROM: 0x034208
 * Size: 0x158
 */
// int init_curr_dir();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/init_curr_dir.s")

/**
 * full_path
 * Address: 0x00434360
 * VROM: 0x034360
 * Size: 0x90
 */
// int full_path();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/full_path.s")

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
// int add_prelinker_objects();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/add_prelinker_objects.s")

/**
 * quoted_length
 * Address: 0x004350B0
 * VROM: 0x0350B0
 * Size: 0x174
 */
size_t quoted_length(const char *arg0, int *arg1);
#pragma GLOBAL_ASM("asm/5.3/functions/cc/quoted_length.s")

/**
 * quote_shell_arg
 * Address: 0x00435224
 * VROM: 0x035224
 * Size: 0x140
 */
size_t quote_shell_arg(const char* arg0, char* arg1) {
    char ch;
    int sp28 = 0;
    size_t len = quoted_length(arg0, &sp28);

    if (sp28 != 0) {
        *arg1++ = '"';
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

/**
 * save_off_command_line
 * Address: 0x00435364
 * VROM: 0x035364
 * Size: 0x340
 */
// int save_off_command_line();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/save_off_command_line.s")

/**
 * skip_old_ii_controls
 * Address: 0x004356A4
 * VROM: 0x0356A4
 * Size: 0x4FC
 */
// int skip_old_ii_controls();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/skip_old_ii_controls.s")

/**
 * make_ii_file_name
 * Address: 0x00435BA0
 * VROM: 0x035BA0
 * Size: 0x134
 */
// int make_ii_file_name();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/make_ii_file_name.s")

/**
 * update_instantiation_info_file
 * Address: 0x00435CD4
 * VROM: 0x035CD4
 * Size: 0x5F8
 */
// int update_instantiation_info_file();
#pragma GLOBAL_ASM("asm/5.3/functions/cc/update_instantiation_info_file.s")

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
