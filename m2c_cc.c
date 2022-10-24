Warning: missing "jr $ra" in last block (.L00406670).

Bad function call operand .L0040661C
Bad function call operand .L0040661C
s32 creat(s8*, ?);                                  /* extern */
FILE* fdopen(s32, ?*);                              /* extern */
s32 flock(s32, ?);                                  /* extern */
s32 fstat(s32, ?*);                                 /* extern */
? memcpy(s8*, s8*, u32);                            /* extern */
s8* mktemp(s8*);                                    /* extern */
s32 open(s8*, ?, ?);                                /* extern */
s32 stat(s8*, ?*);                                  /* extern */
s8* strchr(s8*, u8);                                /* extern */
s32 strcmp(s8*, s8*);                               /* extern */
s8* strdup(s8*);                                    /* extern */
s32 strstr(s8*, ?*);                                /* extern */
s8* strtok(s32, ?*);                                /* extern */
s32 strtoul(s32, s32*, ?);                          /* extern */
s32 time(?);                                        /* extern */
u8 toupper(u8);                                     /* extern */
s32 wait(s32*);                                     /* extern */
void __start(s32 arg0, s32 arg1, s32 arg2, void* arg6); /* static */
void _mcount();                                     /* static */
void add_info(s8* arg0);                            /* static */
void compose_G0_libs(u8* arg0);                     /* static */
void compose_reg_libs(u8* arg0);                    /* static */
s32 edit_src(s8* arg0, s8* arg1, s32 arg2);         /* static */
void func_00431A3C(s32 arg0, s8** arg1);            /* static */
void func_00431B38(s32 arg0, s32 arg1);             /* static */
void func_00431B88(FILE* arg0, s8* arg1, s32 arg2); /* static */
void func_00431D00(s8* arg0);                       /* static */
void get_lino(u8* arg0, s8* arg1, s32 arg2);        /* static */
s8 getsuf(s8* arg0);                                /* static */
? main(s32 arg0, s8** arg1);                        /* static */
s8* mksuf(s8* arg0, u8 arg1);                       /* static */
void parse_command(s32 arg0, s8** arg1);            /* static */
void process_config(s32 arg0, s8** arg1);           /* static */
s32 run(s8* arg0, s8** arg1, s8* arg2, s8* arg3, s8* arg4); /* static */
static ? B_1000E55C;
static ? B_1000E587;
static ? B_1000E58C;
static ? B_1000E5DC;
static ? B_1000EA4C;
static ? B_1000EA5D;
static ? B_1000EA7C;
static ? B_1000EA8C;
static ? B_1000EADC;
static ? B_1000EAEC;
static ? B_1000EAFC;
static ? B_1000EB0C;
static ? B_1000EB1C;
static ? B_1000EB2C;
static ? B_1000EB7C;
static ? B_1000EB9C;
static ? B_1000EBBC;
static ? B_1000EC54;
static ? B_1000EC64;
static ? B_1000EC74;
static ? B_1000EC84;
static ? B_1000EC94;
static ? B_1000ECAC;
static ? B_1000ECBC;
static s8* B_1000ECCC;
static ? B_1000ECEC;
static ? B_1000ECFC;
static ? B_1000ED0C;
static ? B_1000ED1C;
static s32 B_1000ED2C;
static s32 B_1000ED30;
static ? B_1000ED44;
static ? B_1000ED54;
static ? B_1000ED64;
static s32 B_1000ED74;
static ? B_1000ED8C;
static ? B_1000ED9C;
static ? B_1000EDAC;
static ? B_1000EDBC;
static s32 Bflag = 0;
static s8* Bstring;
static s8* CRTX;
static s32 D_1000BF74 = 0;
static s32 D_1000BF78 = 0;
static s32 D_1000BF8C = 1;
static s32 D_1000BF94 = 0;
static s32 D_1000C130 = 0;
static ? D_1000C1C8;                                /* unable to generate initializer */
static s32 Fflag = 0;
static s32 G_flag = 0;
static s32 Gseen_flag = 0;
static u8 Hchar;
static s8 Karg;
static u8* Kpass;
static s32 Lflag = 0;
static s8* LibCob = NULL;
static s8* LibDw = " -ldw";
static s8* LibExc = " -lexc";
static s8* LibF77 = " -lF77";
static s8* LibGProf1 = " -lgprof";
static s8* LibI77 = " -lI77";
static s8* LibIsam = " -lisam";
static s8* LibM = " -lm";
static s8* LibMld = " -lmld";
static s8* LibP = " -lp";
static s8* LibPl1 = NULL;
static s8* LibProf1 = " -lprof";
static s8* LibSort = NULL;
static s8* LibU77 = " -lU77";
static s8* LibXmalloc = " -lxmalloc";
static s8* MCRTX;
static s32 NoMoreOptions = 0;
static s32 Oflag = 1;
static s32 Pflag = 0;
static s32 Sflag = 0;
static s8* Warg;
static u8* Wpass;
static ? Xvalues_Flag;                              /* unable to generate initializer */
static ? __Argc;
static ? __Argv;
static ? __rld_obj_head;
static list accomflags;
static s32 acpp = 0;
static s32 acpp_traditional = 0;
static list acppflags;
static s32 align;
static s32 align_common;
static s8* alignarg;
static s8* aligndir;
static s8* allBstring;
static s8 alltstring[0x14];
static s32 anachronisms = 1;
static s32 ansichoice = 3;
static s32 ansiflag = 0;
static s8* as0 = NULL;
static s8* as1 = NULL;
static list as1flags;
static list asflags;
static s32 auto_template_include = 1;
static s32 automaticflag = 1;
static s8* btou = NULL;
static s32 c_inline = 0;
static s32 call_shared = 0;
static s8* ccom = NULL;
static list ccomflags;
static s8* cfe = NULL;
static list cfeflags;
static s32 cflag = 0;
static s32 cfront_compatible = 1;
static s32 chip_targ = 0xFFFFFFFF;
static s32 cmp_flag;
static s8* cmpflags[6] = { "list", (s8* )0x10003, "keep", (s8* )0x10007, NULL, NULL };
static s32 coff_spec = 0;
static s8* comp_target_root;
static s32 compchoice = 0;
static ? compdirs;
static s32 compose_first_G0 = 0;
static s8* copt = NULL;
static s8* cord = NULL;
static s32 cordflag = 0;
static list cordflags;
static s32 cplusflag = 0;
static s8* cpp = NULL;
static list cpp2flags;
static s8* cpp_stdflag = NULL;
static s32 cppchoice = 0;
static list cppflags;
static s8* crtn = NULL;
static s32 crtn_required = 1;
static s8* crtx = NULL;
static s8* currcomp;
static s8* cxx_init = NULL;
static list dashlfiles;
static s8* ddopt = NULL;
static s32 ddoptflag = 0;
static list ddoptflags;
static s32 ddoptinfo = 0;
static s32 default_call_shared = 1;
static s32 default_nocpp;
static s32 default_svr4 = 0;
static s32 default_template_instantiation_mode;
static s8* delta_init = NULL;
static list dirs_for_abi_crtn;
static list dirs_for_crtn;
static list dirs_for_nonshared_crtn;
static s32 disable_inlines = 0;
static s32 dmips_emit = 0;
static s32 dn_flag = 0;
static s32 do_strip = 0;
static s32 docpp;
static s32 dollar_sign;
static s32 dwopcodeflag = 0;
static s32 edison_cpp = 1;
static s8* edison_type = (s8* )1;
static list edisonflags;
static s32 edit_cnt_max;
static s8* editor;
static ? efl;
static list eflflags;
static s8* einclude = NULL;
static s8* eincludeB = NULL;
static s32 elf_spec = 0;
static s32 elfflag = 1;
static s32 emptyIflag = 0;
static s32 excpt_flag = 0;
static s32 execute_flag = 1;
static s8* fcom = NULL;
static list fcomflags;
static list feedlist;
static ? fflag;                                     /* unable to generate initializer */
static s8* fopt = NULL;
static s32 force_prelink = 0;
static s32 force_rm_dead_code = 0;
static s8* ftoc = NULL;
static list ftocflags;
static s32 full_transitive_link = 0;
static s32 fullasoptflag = 0;
static s32 fullwarn;
static s8* gen = NULL;
static list genflags;
static s32 gflag = 0;
static s32 hasfortran = 0;
static s32 haspascal = 0;
static s32 haspl1;
static s8* hstring;
static s32 ignore_unresolved_flag = 0;
static s8* include = NULL;
static s8* includeB = NULL;
static u32 j;
static s32 jflag = 0;
static s32 kminabiflag = 0;
static s32 kpic_flag = 1;
static s32 kpic_spec = 0;
static s32 kpicopt_flag = 0;
static s8* ld = NULL;
static list ldZflags;
static list ldflags;
static FILE* ldw_file;
static s8* libF77 = NULL;
static s8* libF77_b = NULL;
static s8* libI77 = NULL;
static s8* libI77_b = NULL;
static s8* libI77_mp;
static s8* libU77 = NULL;
static s8* libU77_b = NULL;
static s8* libc_mp = NULL;
static ? libcob;                                    /* unable to generate initializer */
static ? libcob_b;                                  /* unable to generate initializer */
static s8* libdw = NULL;
static s8* libdw_b = NULL;
static s8* libdw_path = NULL;
static s8* libexc = NULL;
static s8* libexc_b = NULL;
static s32 libfastm_spec = 0;
static s8* libftn = NULL;
static s8* libgprof = NULL;
static s8* libisam = NULL;
static s8* libisam_b = NULL;
static s8* libm = NULL;
static s8* libm_b = NULL;
static s32 libm_spec = 0;
static s8* libmld = NULL;
static s8* libp = NULL;
static s8* libp_b = NULL;
static s8* libpl1 = NULL;
static s8* libpl1_b = NULL;
static s8* libprof = NULL;
static s8* libsort = NULL;
static s8* libsort_b = NULL;
static s8* libxmalloc = NULL;
static s8* libxmalloc_b = NULL;
static s32 lmflag = 0;
static s32 longlong_emitted = 0;
static s32 lpilockflag = 0;
static s8* m4;
static s32 make_edison_shlib = 0;
static s32 mflag = 0;
static s32 minus_M = 0;
static s32 mips1flag = 0;
static s32 mips2_spec_flag = 0;
static s32 mips2flag = 1;
static s32 mips3flag = 0;
static s32 mips_abi = 1;
static s32 mp_66flag;
static s32 mp_backslashflag;
static s32 mp_caseflag;
static s32 mp_col120flag;
static s32 mp_dlinesflag;
static s32 mp_extendflag;
static s32 mp_flag;
static s32 mp_i2flag;
static s32 mp_onetripflag;
static ? mp_passes_relocated;
static s32 mp_prepass_count = 0;
static ? mp_staticflag;
static s32 mp_uflag;
static ? mp_uniq_specified;
static s8* mpc = NULL;
static list mpcflags;
static s8* mpflags[6] = { "list", (s8* )0x10003, "keep", (s8* )0x10007, NULL, NULL };
static s32 multiple_systype = 0;
static list nldflags;
static s32 no_prelink = 0;
static s32 no_transitive_link = 0;
static s32 no_unresolved_flag = 0;
static s32 noaliasokflag;
static s32 nobjs = 0;
static s32 nocode = 0;
static s32 nocompileneeded = 0;
static s32 nodeflib = 0;
static s32 nokpicopt_flag = 0;
static s32 nolockflag = 0;
static s32 non_shared_emitted = 0;
static s32 nonshared;
static list objfiles;
static s32 old_non_shared = 0;
static s32 oldccomflag = 0;
static s32 oldcflag = 0;
static s32 oldcppflag = 0;
static list olimitflags;
static s8* opt = NULL;
static list optflags;
static s8* outfile;
static ? p2cstr;
static s8* patch = NULL;
static s8* pca = NULL;
static list pcaflags;
static s8 perr_msg[0x100];
static s8* pfa;
static list pfaflags;
static s32 pflag = 0;
static s32 pgflag = 0;
static s8* pl1err = NULL;
static s32 plain_O;
static s32 plain_g;
static s32 plusIflag = 0;
static s8* prelinker = NULL;
static list prelinkerflags;
static ? protoflag;                                 /* unable to generate initializer */
static s32 prototype_checking_on = 0;
static s32 quickstart_info = 0;
static s8* ratfor;
static list ratforflags;
static s32 retcode;
static s8* rls_id_object;
static s32 run_sopt = 0;
static s8* sbrepos = NULL;
static s32 set_loop_unroll = 0;
static s32 showdirt_flag = 0;
static s32 signedcharflag = 0;
static s32 sixty4bit_spec = 0;
static s32 sixty4bitflag = 0;
static s32 smart_build = 0;
static list soptflags;
static s32 srcexists = 0;
static list srcfiles;
static s32 stdflag = 0;
static s8* strip = NULL;
static s32 svr4_systype = 0;
static s32 swopcodeflag = 0;
static s8* systype;
static s32 systype_seen = 0;
static s32 systype_warn = 0;
static s32 tfp_flag = 0;
static s32 thirty2bitflag = 0;
static s32 time_flag = 0;
static s32 times_edited;
static ? tmp_elfobj;
static FILE* tmpsfile;
static s32 tpflag = 0;
static s32 transitive_link = 0;
static s32 trapuv_flag = 0;
static s8* tstring;
static s8* ucob = NULL;
static list ucobflags;
static s32 ucodeflag = 0;
static list ufiles;
static s8* ujoin = NULL;
static list ujoinflags;
static s8* uld = NULL;
static list uldflags;
static list uldlibflags;
static s32 uldobj_place = -1;
static s32 uload = 0;
static s8* uloop = NULL;
static list uloopflags;
static s8* ulpi = NULL;
static list ulpiflags;
static s8* umerge = NULL;
static list umergeflags;
static list undefineflags;
static s32 unrollflag = 0;
static s8* uopt0 = NULL;
static s32 uopt0flag = 0;
static list uopt0flags;
static s8* uoutfile;
static s8* upas = NULL;
static list upasflags;
static s8* upl1 = NULL;
static list upl1flags;
static s32 use_real_fp;
static s32 user_systype = 0;
static s8* usplit = NULL;
static list usplitflags;
static s8* utob = NULL;
static ? valuesstr;
static s32 verbose_prelink = 0;
static s32 w1flag = 1;
static s8* xpg_env = NULL;
static s32 xpg_flag = 0;
static s8* xserver;
prmap_sgi_t B_1000CAC0[0x64];
s32 B_1000E4C0;
s8** B_1000E4C4;
s8 B_1000E5E0[0x400];
s32 B_1000EC98[2];
s8* B_1000ECDC;
s32 D_1000BF7C = 1;
s8* D_1000BF80 = NULL;
s8* D_1000BF84 = NULL;
s32 D_1000BF88 = 0;
s32 D_1000BF90 = 0;
s8* D_1000C1D0 = NULL;
s8* D_1000C1D8 = NULL;
s8* D_1000C1DC = NULL;
s8* D_1000C1E0[6] = { "Internal", "Error", "Warning", "Info", "Fix", "" };
s8* D_1000C2E8 = NULL;
s8* D_1000C2EC = NULL;
s8* D_1000C2F0 = NULL;
s32 Eflag = 0;
s8* Gnum = "0";
s32 Kflag = 0;
s8* LD = "ld";
s32 Vflag = 0;
s32 abi_flag = 0;
s8* binasm;
s32 c_compiler_choice = 0;
s8* comp_host_root;
s32 compiler;
s8* ddoptstr;
s32 editflag = 0;
s8* errout;
s32 exception_handling = 0;
list execlist;
s8* filter = NULL;
s32 fiveflag = 0;
s8* gentmp;
s32 irix4 = 0;
s8* linkorder;
s8* lpi_dd;
s8* lpi_p1;
s8* lpi_pd;
s8* lpi_st;
s32 memory_flag = 0;
s32 nofilt = 0;
s32 non_shared = 0;
s8* optstr;
s8* passin;
s8* passout;
struct _struct_prod_name_0xC prod_name[0x14] = {
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
    { "edgcpfe.alt", "/usr/lib/DCC/edgcpfe.alt", "C++" },
};
s8* progname;
s32 runerror = 0;
s8* runlib = "/";
s8* runlib_base = "/";
s8 srcsuf;
list staticopts;
struct _struct_suffixes_0x8 suffixes[0xF] = {
    { "pl1", 1 },
    { "pli", 1 },
    { "cob", 2 },
    { "il", 3 },
    { "st", 4 },
    { "anl", 5 },
    { "c++", 6 },
    { "cc", 6 },
    { "cxx", 6 },
    { "C", 6 },
    { "cpp", 6 },
    { "CXX", 6 },
    { "CPP", 6 },
    { ".c", 7 },
    { NULL, 0 },
};
s8* symtab;
s32 targetsex = 0;
s8* tempstr[0x22];
s32 time0;
struct tms tm0;
s8* tmp_uldobj = NULL;
s8* tmpdir;
s32 tmpst;
s8* uopt0str;
s32 vflag = 0;

void __start(s32 arg0, s32 arg1, s32 arg2, void* arg6) {
    // Error: Bad function call operand .L0040661C
    // At instruction: bal .L0040661C
    if (M2C_ERROR()) {
        *saved_reg_gp->unk_-7FB8 = arg2;
    }
    *saved_reg_gp->unk_-783C = arg0;
    arg7 = 0;
    *saved_reg_gp->unk_-7840 = arg1;
    saved_reg_gp->unk_-7DE0();
    arg6->unk_-7FB0();
    arg6->unk_-7FB4(arg6->unk_-7EB0(*arg6->unk_-783C, *arg6->unk_-7840, *arg6->unk_-7FB8));
    M2C_BREAK(0);
}

void _mcount(void) {

}

? main(s32 arg0, s8** arg1) {
    s32 sp148;
    s8* sp144;
    s8* sp140;
    s8* sp13C;
    s8* sp138;
    s8* sp134;
    u32 sp130;
    s8* sp12C;
    s8* sp128;
    s8* sp124;
    s32 sp120;
    s32 sp11C;
    s8* sp118;
    s32 sp114;
    s8* sp110;
    s8* sp10C;
    s8* sp108;
    s8* sp104;
    s32 sp100;
    s32 spFC;
    s8* spF8;
    s8* spF4;
    s8 spF0;
    s8* spEC;
    s8* spE8;
    u8 spE7;
    s32 spE0;
    s32 spDC;
    u32 spD8;
    s8* spD4;
    s32 spD0;
    ? sp48;
    s32 temp_s3_10;
    s32 temp_s3_12;
    s32 temp_s3_2;
    s32 temp_s3_4;
    s32 temp_t0;
    s32 temp_t0_12;
    s32 temp_t0_4;
    s32 temp_t0_5;
    s32 temp_t0_8;
    s32 temp_t1_14;
    s32 temp_t1_2;
    s32 temp_t1_5;
    s32 temp_t2;
    s32 temp_t2_10;
    s32 temp_t2_2;
    s32 temp_t2_3;
    s32 temp_t2_4;
    s32 temp_t2_5;
    s32 temp_t2_7;
    s32 temp_t3_11;
    s32 temp_t3_13;
    s32 temp_t3_14;
    s32 temp_t3_16;
    s32 temp_t3_3;
    s32 temp_t3_6;
    s32 temp_t3_7;
    s32 temp_t4;
    s32 temp_t4_11;
    s32 temp_t4_15;
    s32 temp_t4_2;
    s32 temp_t4_7;
    s32 temp_t4_8;
    s32 temp_t5;
    s32 temp_t5_10;
    s32 temp_t5_11;
    s32 temp_t5_14;
    s32 temp_t5_15;
    s32 temp_t5_16;
    s32 temp_t5_3;
    s32 temp_t5_4;
    s32 temp_t5_5;
    s32 temp_t6_10;
    s32 temp_t6_11;
    s32 temp_t6_19;
    s32 temp_t6_6;
    s32 temp_t6_8;
    s32 temp_t7;
    s32 temp_t7_12;
    s32 temp_t7_14;
    s32 temp_t7_15;
    s32 temp_t7_18;
    s32 temp_t7_19;
    s32 temp_t7_5;
    s32 temp_t7_8;
    s32 temp_t7_9;
    s32 temp_t8;
    s32 temp_t8_10;
    s32 temp_t8_14;
    s32 temp_t8_15;
    s32 temp_t8_17;
    s32 temp_t8_18;
    s32 temp_t8_19;
    s32 temp_t8_2;
    s32 temp_t8_3;
    s32 temp_t8_6;
    s32 temp_t8_8;
    s32 temp_t8_9;
    s32 temp_t9_10;
    s32 temp_t9_11;
    s32 temp_t9_14;
    s32 temp_t9_19;
    s32 temp_t9_21;
    s32 temp_t9_3;
    s32 temp_t9_4;
    s32 temp_t9_9;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s3;
    s32 var_s3_10;
    s32 var_s3_9;
    s32 var_v0_4;
    s8* temp_t0_10;
    s8* temp_t0_11;
    s8* temp_t0_13;
    s8* temp_t0_2;
    s8* temp_t0_3;
    s8* temp_t0_6;
    s8* temp_t0_9;
    s8* temp_t1;
    s8* temp_t1_11;
    s8* temp_t1_13;
    s8* temp_t1_3;
    s8* temp_t1_4;
    s8* temp_t1_6;
    s8* temp_t1_8;
    s8* temp_t1_9;
    s8* temp_t2_14;
    s8* temp_t2_15;
    s8* temp_t2_16;
    s8* temp_t2_17;
    s8* temp_t2_6;
    s8* temp_t2_8;
    s8* temp_t3;
    s8* temp_t3_10;
    s8* temp_t3_12;
    s8* temp_t3_17;
    s8* temp_t3_2;
    s8* temp_t3_5;
    s8* temp_t3_8;
    s8* temp_t3_9;
    s8* temp_t4_10;
    s8* temp_t4_4;
    s8* temp_t4_5;
    s8* temp_t4_6;
    s8* temp_t5_17;
    s8* temp_t5_9;
    s8* temp_t6_13;
    s8* temp_t6_14;
    s8* temp_t6_15;
    s8* temp_t6_16;
    s8* temp_t6_17;
    s8* temp_t6_18;
    s8* temp_t6_20;
    s8* temp_t6_21;
    s8* temp_t6_2;
    s8* temp_t6_3;
    s8* temp_t6_5;
    s8* temp_t6_7;
    s8* temp_t6_9;
    s8* temp_t7_10;
    s8* temp_t7_11;
    s8* temp_t7_20;
    s8* temp_t7_2;
    s8* temp_t7_3;
    s8* temp_t7_4;
    s8* temp_t7_6;
    s8* temp_t7_7;
    s8* temp_t8_16;
    s8* temp_t8_4;
    s8* temp_t8_5;
    s8* temp_t9;
    s8* temp_t9_17;
    s8* temp_t9_18;
    s8* temp_t9_20;
    s8* temp_t9_22;
    s8* temp_t9_23;
    s8* temp_t9_2;
    s8* temp_t9_6;
    s8* temp_t9_7;
    s8* temp_t9_8;
    s8* temp_v0;
    s8* var_s1;
    s8* var_s1_2;
    s8* var_s1_3;
    s8* var_s1_4;
    s8* var_s1_5;
    s8* var_s2;
    s8* var_s3_2;
    s8* var_s3_3;
    s8* var_s3_5;
    s8* var_s3_6;
    s8* var_s3_7;
    s8* var_s3_8;
    s8* var_t4;
    s8* var_v0;
    s8* var_v0_10;
    s8* var_v0_11;
    s8* var_v0_12;
    s8* var_v0_13;
    s8* var_v0_14;
    s8* var_v0_15;
    s8* var_v0_16;
    s8* var_v0_17;
    s8* var_v0_2;
    s8* var_v0_3;
    s8* var_v0_5;
    s8* var_v0_6;
    s8* var_v0_7;
    s8* var_v0_8;
    s8* var_v0_9;
    s8** temp_t5_13;
    s8** temp_t5_2;
    s8** var_at;
    s8** var_s3_4;
    u8 temp_s3;
    u8 temp_s3_11;
    u8 temp_s3_3;
    u8 temp_s3_5;
    u8 temp_s3_6;
    u8 temp_s3_7;
    u8 temp_s3_8;
    u8 temp_s3_9;
    u8 temp_t0_7;
    u8 temp_t1_10;
    u8 temp_t1_12;
    u8 temp_t1_7;
    u8 temp_t2_11;
    u8 temp_t2_12;
    u8 temp_t2_13;
    u8 temp_t2_9;
    u8 temp_t3_15;
    u8 temp_t3_4;
    u8 temp_t4_12;
    u8 temp_t4_13;
    u8 temp_t4_14;
    u8 temp_t4_3;
    u8 temp_t4_9;
    u8 temp_t5_12;
    u8 temp_t5_6;
    u8 temp_t5_7;
    u8 temp_t5_8;
    u8 temp_t6;
    u8 temp_t6_12;
    u8 temp_t6_4;
    u8 temp_t7_13;
    u8 temp_t7_16;
    u8 temp_t7_17;
    u8 temp_t7_21;
    u8 temp_t8_11;
    u8 temp_t8_12;
    u8 temp_t8_13;
    u8 temp_t8_7;
    u8 temp_t9_12;
    u8 temp_t9_13;
    u8 temp_t9_15;
    u8 temp_t9_16;
    u8 temp_t9_5;

    /* Flowgraph is not reducible, falling back to gotos-only mode. */
    sp148 = 0;
    sp144 = NULL;
    sp140 = NULL;
    temp_t8 = ansichoice;
    progname = *arg1;
    if (temp_t8 == 1) {
        goto block_2;
    }
    if (temp_t8 != 2) {
        goto block_3;
    }
block_2:
    CRTX = "acrt1.o";
    goto block_4;
block_3:
    CRTX = "crt1.o";
block_4:
    MCRTX = "mcrt1.o";
    m4 = "/usr/bin/m4";
    ratfor = "/usr/bin/ratfor";
    xpg_env = getenv("_XPG");
    if (xpg_env == NULL) {
        goto block_6;
    }
    xpg_flag = 1;
block_6:
    mklist(&undefineflags);
    mklist(&cppflags);
    mklist(&ccomflags);
    mklist(&cfeflags);
    mklist(&upasflags);
    mklist(&fcomflags);
    mklist(&upl1flags);
    mklist(&ucobflags);
    mklist(&ulpiflags);
    mklist(&eflflags);
    mklist(&ratforflags);
    mklist(&ujoinflags);
    mklist(&uldflags);
    mklist(&olimitflags);
    mklist(&ldZflags);
    mklist(&acppflags);
    mklist(&cpp2flags);
    mklist(&mpcflags);
    mklist(&accomflags);
    mklist(&uldlibflags);
    mklist(&edisonflags);
    mklist(&prelinkerflags);
    mklist(&pfaflags);
    mklist(&pcaflags);
    mklist(&soptflags);
    mklist(&usplitflags);
    mklist(&umergeflags);
    mklist(&uloopflags);
    mklist(&uopt0flags);
    mklist(&ddoptflags);
    mklist(&optflags);
    mklist(&genflags);
    mklist(&asflags);
    mklist(&as1flags);
    mklist(&ldflags);
    mklist(&nldflags);
    mklist(&ftocflags);
    mklist(&cordflags);
    mklist(&srcfiles);
    mklist(&ufiles);
    mklist(&objfiles);
    mklist(&execlist);
    mklist(&feedlist);
    mklist(&dashlfiles);
    compdirs.unk_4 = mkstr("cc", "/", NULL);
    compdirs.unk_8 = mkstr("pc", "/", NULL);
    compdirs.unk_C = mkstr("f77", "/", NULL);
    compdirs.unk_10 = mkstr("cc", "/", NULL);
    compdirs.unk_14 = mkstr("pl1", "/", NULL);
    compdirs.unk_18 = mkstr("cobol", "/", NULL);
    call_shared = default_call_shared;
    sp13C = getenv("SGI_SVR4");
    if (sp13C == NULL) {
        goto block_8;
    }
    default_svr4 = 1;
block_8:
    sp138 = getenv("SGI_CC");
    if (sp138 == NULL) {
        goto block_24;
    }
    if (!(__ctype[(u8) *sp138].unk_1 & 8)) {
        goto block_11;
    }
loop_10:
    sp138 += 1;
    if (__ctype[(u8) *sp138].unk_1 & 8) {
        goto loop_10;
    }
block_11:
    sp130 = strlen(sp138);
    if ((s32) sp130 > 0) {
        goto block_13;
    }
    error(2, NULL, 0, NULL, 0, "Environment variable SGI_CC is empty: ignored\n");
    goto block_24;
block_13:
    temp_t3 = &sp138[sp130];
    sp134 = temp_t3 - 1;
    if (!(__ctype[temp_t3->unk_-1].unk_1 & 8)) {
        goto block_15;
    }
loop_14:
    sp134 -= 1;
    if (__ctype[(u8) *sp134].unk_1 & 8) {
        goto loop_14;
    }
block_15:
    sp134 += 1;
    sp134[1] = 0;
    if (strcmp(sp138, "-cckr") != 0) {
        goto block_17;
    }
    ansichoice = 0;
    cppchoice = 2;
    relocate_passes("p", NULL, NULL);
    goto block_24;
block_17:
    if (strcmp(sp138, "-ansi") != 0) {
        goto block_19;
    }
    ansichoice = 1;
    cppchoice = 3;
    relocate_passes("p", NULL, NULL);
    goto block_24;
block_19:
    if (strcmp(sp138, "-xansi") != 0) {
        goto block_21;
    }
    ansichoice = 3;
    cppchoice = 3;
    relocate_passes("p", NULL, NULL);
    goto block_24;
block_21:
    if (strcmp(sp138, "-ansiposix") != 0) {
        goto block_23;
    }
    ansichoice = 2;
    cppchoice = 3;
    relocate_passes("p", NULL, NULL);
    goto block_24;
block_23:
    error(2, NULL, 0, NULL, 0, "Environment variable SGI_CC contents unrecognizable and ignored; \"%s\" not one of: -cckr -ansi -xansi -ansiposix\n", sp138);
    sp138 = NULL;
block_24:
    compiler = 1;
    temp_v0 = strrchr(progname, 0x2F);
    if (temp_v0 != NULL) {
        goto block_26;
    }
    var_s1 = progname;
    goto block_27;
block_26:
    var_s1 = temp_v0 + 1;
block_27:
    compdirs.unk_0 = mkstr(var_s1, "/", NULL);
    if (strncmp(var_s1, "cc", strlen("cc")) != 0) {
        goto block_29;
    }
    compiler = 1;
    Bstring = &var_s1[strlen("cc")];
    goto block_51;
block_29:
    if (strncmp(var_s1, "pc", strlen("pc")) != 0) {
        goto block_31;
    }
    compiler = 2;
    Bstring = &var_s1[strlen("pc")];
    goto block_51;
block_31:
    if (strncmp(var_s1, "f77", strlen("f77")) != 0) {
        goto block_33;
    }
    compiler = 3;
    Bstring = &var_s1[strlen("f77")];
    goto block_51;
block_33:
    if (strncmp(var_s1, "f90", strlen("f90")) != 0) {
        goto block_35;
    }
    error(1, NULL, 0, NULL, 0, "-32 compilation not supported for ucode\n");
    exit(2);
    goto block_51;
block_35:
    if (strncmp(var_s1, "as", strlen("as")) != 0) {
        goto block_37;
    }
    compiler = 4;
    Bstring = &var_s1[strlen("as")];
    strcpy(compdirs.unk_0, compdirs.unk_4);
    goto block_51;
block_37:
    if (strncmp(var_s1, "pl1", strlen("pl1")) != 0) {
        goto block_39;
    }
    compiler = 5;
    Bstring = &var_s1[strlen("pl1")];
    goto block_51;
block_39:
    if (strncmp(var_s1, "cobol", strlen("cobol")) != 0) {
        goto block_41;
    }
    compiler = 6;
    Bstring = &var_s1[strlen("cobol")];
    goto block_51;
block_41:
    if (strncmp(var_s1, "ncc", strlen("ncc")) != 0) {
        goto block_43;
    }
    compiler = 1;
    c_compiler_choice = 1;
    edison_cpp = 1;
    Bstring = &var_s1[strlen("ncc")];
    goto block_51;
block_43:
    if (strncmp(var_s1, "CC.eh", strlen("CC.eh")) != 0) {
        goto block_45;
    }
    compiler = 1;
    c_compiler_choice = 2;
    edison_cpp = 1;
    anachronisms = 0;
    cfront_compatible = 0;
    D_1000BF7C = 0;
    exception_handling = 1;
    Bstring = &var_s1[strlen("CC")];
    goto block_51;
block_45:
    if (strncmp(var_s1, "CC", strlen("CC")) != 0) {
        goto block_47;
    }
    compiler = 1;
    c_compiler_choice = 2;
    edison_cpp = 1;
    D_1000BF7C = 0;
    Bstring = &var_s1[strlen("CC")];
    goto block_51;
block_47:
    if (strncmp(var_s1, "NCC", strlen("NCC")) != 0) {
        goto block_49;
    }
    compiler = 1;
    c_compiler_choice = 2;
    edison_cpp = 1;
    Bstring = &var_s1[strlen("NCC")];
    goto block_51;
block_49:
    if (strncmp(var_s1, "DCC", strlen("DCC")) != 0) {
        goto block_51;
    }
    compiler = 1;
    c_compiler_choice = 3;
    edison_cpp = 1;
    Bstring = &var_s1[strlen("DCC")];
    D_1000BF90 = 1;
block_51:
    Bstring = NULL;
    comp_target_root = getenv("COMP_TARGET_ROOT");
    if (comp_target_root != NULL) {
        goto block_53;
    }
    comp_target_root = "/";
    goto block_55;
block_53:
    temp_t9 = comp_target_root;
    if (temp_t9[strlen(comp_target_root)].unk_-1 == 0x2F) {
        goto block_55;
    }
    comp_target_root = mkstr(temp_t9, "/", NULL);
block_55:
    comp_host_root = getenv("TOOLROOT");
    if (comp_host_root != NULL) {
        goto block_57;
    }
    comp_host_root = "/";
    goto block_59;
block_57:
    temp_t3_2 = comp_host_root;
    if (temp_t3_2[strlen(comp_host_root)].unk_-1 == 0x2F) {
        goto block_59;
    }
    comp_host_root = mkstr(temp_t3_2, "/", NULL);
block_59:
    aligndir = mkstr(comp_host_root, "lib/align", NULL);
    sp12C = getenv("DCC_STD_PATHS");
    var_s3 = sp12C == NULL;
    if (var_s3 != 0) {
        goto block_62;
    }
    var_s3 = (u8) *sp12C == 0;
    if (var_s3 != 0) {
        goto block_62;
    }
    var_s3 = (u8) *sp12C == 0x30;
block_62:
    D_1000BF8C = var_s3;
    temp_t8_2 = D_1000BF8C;
    if (temp_t8_2 != 0) {
        goto block_64;
    }
    D_1000BF90 = temp_t8_2;
block_64:
    if (force_use_cfront(arg0, arg1) == 0) {
        goto block_66;
    }
    exec_OCC(arg0, arg1);
block_66:
    func_00431A3C(arg0, arg1);
    tmpdir = getenv("TMPDIR");
    if (tmpdir != NULL) {
        goto block_68;
    }
    tmpdir = "/tmp/";
    goto block_70;
block_68:
    temp_t9_2 = tmpdir;
    if (temp_t9_2[strlen(tmpdir)].unk_-1 == 0x2F) {
        goto block_70;
    }
    tmpdir = mkstr(temp_t9_2, "/", NULL);
block_70:
    passout = mktemp(mkstr(tmpdir, "ctmtstXXXXXX", NULL));
    tmpsfile = fopen(passout, "w");
    if (tmpsfile != NULL) {
        goto block_72;
    }
    sprintf(perr_msg, "cc: can't write to $TMPDIR: %s", tmpdir);
    perror(perr_msg);
    exit(2);
    goto block_73;
block_72:
    fclose(tmpsfile);
    unlink(passout);
block_73:
    var_s0 = 1;
    rls_id_object = getenv("RLS_ID_OBJECT");
    if (arg0 <= 1) {
        goto block_92;
    }
loop_74:
    if (strcmp(arg1[var_s0], "-non_shared") != 0) {
        goto block_77;
    }
    non_shared = 1;
    if (Oflag >= 3) {
        goto block_91;
    }
    Gnum = "8";
    goto block_91;
block_77:
    if (strcmp(arg1[var_s0], "-irix4") != 0) {
        goto block_79;
    }
    irix4 = 1;
    Gnum = "8";
    goto block_91;
block_79:
    if (strcmp(arg1[var_s0], "-coff") != 0) {
        goto block_81;
    }
    LD = "old_ld";
    coff_spec = 1;
    kpic_flag = 0;
    Gnum = "8";
    goto block_91;
block_81:
    if (strcmp(arg1[var_s0], "-mips3") != 0) {
        goto block_83;
    }
    mips3flag = 1;
    Gnum = "8";
    kpic_flag = 0;
    goto block_91;
block_83:
    if (strcmp(arg1[var_s0], "-excpt") != 0) {
        goto block_85;
    }
    excpt_flag = 1;
    kpic_flag = 0;
    Gnum = "8";
    goto block_91;
block_85:
    if (strcmp(arg1[var_s0], "-abi") != 0) {
        goto block_87;
    }
    abi_flag = 1;
    mips1flag = 1;
    mips2flag = 0;
    goto block_91;
block_87:
    if (strcmp(arg1[var_s0], "-O3") != 0) {
        goto block_89;
    }
    Oflag = 3;
    goto block_91;
block_89:
    if (strcmp(arg1[var_s0], "-old_ld") != 0) {
        goto block_91;
    }
    LD = "old_ld";
    D_1000BF90 = 0;
block_91:
    var_s0 += 1;
    if (var_s0 < arg0) {
        goto loop_74;
    }
block_92:
    temp_t7 = compiler;
    if (temp_t7 == 1) {
        goto block_96;
    }
    if (temp_t7 == 2) {
        goto block_96;
    }
    if (temp_t7 == 3) {
        goto block_96;
    }
    if (temp_t7 != 4) {
        goto block_97;
    }
block_96:
    docpp = 1;
    default_nocpp = 0;
    goto block_98;
block_97:
    docpp = 0;
    default_nocpp = 1;
block_98:
    currcomp = compdirs.unk_0;
    mklist(&dirs_for_nonshared_crtn);
    mklist(&dirs_for_abi_crtn);
    mklist(&dirs_for_crtn);
    var_s0_2 = 1;
    if (arg0 <= 1) {
        goto block_130;
    }
loop_99:
    if ((u8) *arg1[var_s0_2] != 0x2D) {
        goto block_129;
    }
    if (strcmp(arg1[var_s0_2], "-nostdlib") != 0) {
        goto block_102;
    }
    sp148 = 1;
    goto block_129;
block_102:
    temp_s3 = arg1[var_s0_2]->unk_1;
    if (temp_s3 == 0x45) {
        goto block_105;
    }
    if (temp_s3 == 0x4C) {
        goto block_118;
    }
    goto block_129;
block_105:
    if (arg1[var_s0_2]->unk_3 != 0) {
        goto block_129;
    }
    if (arg1[var_s0_2]->unk_2 == 0x42) {
        goto block_108;
    }
    if (arg1[var_s0_2]->unk_2 != 0x4C) {
        goto block_129;
    }
block_108:
    if (arg1[var_s0_2]->unk_2 != 0x42) {
        goto block_113;
    }
    if (Bflag == 0) {
        goto block_112;
    }
    if (targetsex == 0) {
        goto block_112;
    }
    error(1, NULL, 0, NULL, 0, "-EB or -EL must precede any -B flags for ucode compilers.\n");
    exit(2);
block_112:
    targetsex = 0;
    goto block_117;
block_113:
    if (Bflag == 0) {
        goto block_116;
    }
    if (targetsex == 1) {
        goto block_116;
    }
    error(1, NULL, 0, NULL, 0, "-EB or -EL must precede any -B flags for ucode compilers.\n");
    exit(2);
block_116:
    targetsex = 1;
block_117:
    newrunlib();
    goto block_128;
block_118:
    if (arg1[var_s0_2].unk_0->unk_2 != 0) {
        goto block_124;
    }
    if ((var_s0_2 + 1) >= arg0) {
        goto block_122;
    }
    if (*arg1[var_s0_2].unk_4 == 0x2D) {
        goto block_122;
    }
    if (isdir(arg1[var_s0_2].unk_4) != 0) {
        goto block_123;
    }
block_122:
    sp148 = 1;
    goto block_129;
block_123:
    var_s0_2 += 1;
    var_v0 = mkstr(arg1[var_s0_2], NULL);
    goto block_125;
block_124:
    var_v0 = mkstr(arg1[var_s0_2] + 2, NULL);
block_125:
    sp128 = var_v0;
    if (sp128[strlen(sp128)].unk_-1 != 0x2F) {
        goto block_127;
    }
    sp128[strlen(sp128)].unk_-1 = 0;
block_127:
    addstr(&dirs_for_crtn, sp128);
    addstr(&dirs_for_nonshared_crtn, sp128);
    addstr(&dirs_for_abi_crtn, sp128);
block_128:
block_129:
    var_s0_2 += 1;
    if (var_s0_2 < arg0) {
        goto loop_99;
    }
block_130:
    if (sp148 != 0) {
        goto block_140;
    }
    if (non_shared != 0) {
        goto block_135;
    }
    if (coff_spec != 0) {
        goto block_135;
    }
    if (mips3flag != 0) {
        goto block_135;
    }
    if (excpt_flag == 0) {
        goto block_136;
    }
block_135:
    addstr(&dirs_for_nonshared_crtn, mkstr(comp_target_root, "usr/lib/nonshared", NULL));
    goto block_139;
block_136:
    if (abi_flag == 0) {
        goto block_138;
    }
    addstr(&dirs_for_abi_crtn, mkstr(comp_target_root, "usr/lib/abi", NULL));
    goto block_139;
block_138:
    addstr(&dirs_for_crtn, mkstr(comp_target_root, "usr/lib", NULL));
    addstr(&dirs_for_crtn, mkstr(comp_target_root, "lib", NULL));
block_139:
block_140:
    relocate_passes(tstring, NULL, Bstring);
    relocate_passes("h", NULL, Bstring);
    if (strcmp("/", comp_target_root) == 0) {
        goto block_142;
    }
    einclude = mkstr(comp_target_root, "usr/include/CC", NULL);
    include = mkstr(comp_target_root, "usr/include", NULL);
block_142:
    if (compiler != 1) {
        goto block_144;
    }
    oldcflag = 0;
    goto block_145;
block_144:
    cpp_stdflag = "-std0";
block_145:
    systype = "svr4";
    svr4_systype = 1;
    process_config(arg0, arg1);
    parse_command(arg0 - 1, arg1 + 4);
    func_00431DD8();
    if (D_1000BF74 == 0) {
        goto block_160;
    }
    if (D_1000BF80 != NULL) {
        goto block_148;
    }
    D_1000BF80 = "";
block_148:
    if (D_1000BF78 == 0) {
        goto block_150;
    }
    var_s3_2 = "-YSv";
    goto block_151;
block_150:
    var_s3_2 = "-YSz";
block_151:
    sp144 = mkstr(var_s3_2, D_1000BF80, NULL);
    if (compiler != 1) {
        goto block_153;
    }
    addstr(&edisonflags, sp144);
    goto block_159;
block_153:
    if (D_1000BF78 == 0) {
        goto block_155;
    }
    sp140 = "-cvs_nosrc";
    goto block_156;
block_155:
    sp140 = "-cvs";
block_156:
    temp_t7_2 = D_1000BF80;
    if ((u8) *temp_t7_2 == 0) {
        goto block_158;
    }
    sp140 = mkstr(sp140, ",", temp_t7_2, NULL);
block_158:
    addstr(&fcomflags, sp140);
block_159:
block_160:
    if (user_systype != 0) {
        goto block_167;
    }
    if (fiveflag == 0) {
        goto block_163;
    }
    var_v0_2 = mkstr(comp_target_root, "usr/5include", NULL);
    goto block_164;
block_163:
    einclude = mkstr(comp_target_root, "usr/include/CC", NULL);
    var_v0_2 = mkstr(comp_target_root, "usr/include", NULL);
block_164:
    include = var_v0_2;
    temp_t1 = Bstring;
    if (temp_t1 == NULL) {
        goto block_166;
    }
    relocate_passes("h", NULL, temp_t1);
block_166:
    newrunlib();
block_167:
    if (mips2flag != 0) {
        goto block_170;
    }
    if (mips3flag != 0) {
        goto block_170;
    }
    if (sixty4bitflag == 0) {
        goto block_178;
    }
block_170:
    if (kpic_flag != 0) {
        goto block_178;
    }
    if (non_shared != 0) {
        goto block_174;
    }
    if (call_shared != 0) {
        goto block_174;
    }
    if (default_call_shared == 0) {
        goto block_178;
    }
block_174:
    if (non_shared != 0) {
        goto block_176;
    }
    non_shared = 1;
    old_non_shared = 1;
block_176:
    default_call_shared = 0;
    call_shared = 0;
    if (non_shared_emitted != 0) {
        goto block_178;
    }
    addstr(&ldflags, "-non_shared");
    addstr(&cfeflags, "-non_shared");
    non_shared_emitted = 1;
block_178:
    if (non_shared == 0) {
        goto block_181;
    }
    if (non_shared_emitted != 0) {
        goto block_181;
    }
    addstr(&ldflags, "-non_shared");
    addstr(&cfeflags, "-non_shared");
    non_shared_emitted = 1;
    goto block_183;
block_181:
    if (call_shared == 0) {
        goto block_183;
    }
    addstr(&ldflags, "-call_shared");
    addstr(&cfeflags, "-call_shared");
block_183:
    if (Vflag != 0) {
        goto block_188;
    }
    if (srcfiles.length != 0) {
        goto block_188;
    }
    if (objfiles.length != 0) {
        goto block_188;
    }
    if (ufiles.length != 0) {
        goto block_188;
    }
    error(1, NULL, 0, NULL, 0, "no source, object or ucode file specified\n");
    exit(2);
block_188:
    if (w1flag != 1) {
        goto block_190;
    }
    addstr(&fcomflags, "-w1");
    goto block_192;
block_190:
    if (w1flag != 2) {
        goto block_193;
    }
    addstr(&fcomflags, "-w");
block_192:
block_193:
    if (srcexists != 0) {
        goto block_197;
    }
    if (cflag != 0) {
        goto block_196;
    }
    if (Sflag == 0) {
        goto block_197;
    }
block_196:
    error(1, NULL, 0, NULL, 0, "no source file for ucode compilers.\n");
    exit(4);
block_197:
    temp_t8_3 = mp_flag;
    if (temp_t8_3 == 0) {
        goto block_201;
    }
    if (gflag == 0) {
        goto block_201;
    }
    if (!(temp_t8_3 & 1)) {
        goto block_201;
    }
    mp_flag = temp_t8_3 | 4;
block_201:
    temp_t5 = cmp_flag;
    if (temp_t5 == 0) {
        goto block_205;
    }
    if (gflag == 0) {
        goto block_205;
    }
    if (!(temp_t5 & 1)) {
        goto block_205;
    }
    cmp_flag = temp_t5 | 4;
block_205:
    temp_t9_3 = ansichoice;
    if (temp_t9_3 == 1) {
        goto block_207;
    }
    if (temp_t9_3 != 2) {
        goto block_208;
    }
block_207:
    CRTX = "acrt1.o";
    crtn_required = 1;
block_208:
    relocate_passes("r", NULL, NULL);
    if (B_1000ED30 == 0) {
        goto block_213;
    }
    if (compiler != 1) {
        goto block_213;
    }
    temp_t4 = ansichoice;
    if (temp_t4 == 1) {
        goto block_212;
    }
    if (temp_t4 != 2) {
        goto block_213;
    }
block_212:
    error(2, NULL, 0, NULL, 0, "'-lc_s' specified. Shared version of C library does not conform to ANSI X3.159-1989.\n");
block_213:
    if (Oflag < 3) {
        goto block_214;
    }
block_214:
    if (kpic_flag == 0) {
        goto block_218;
    }
    if (strcmp(Gnum, "0") == 0) {
        goto block_218;
    }
    if (Oflag >= 3) {
        goto block_218;
    }
    error(2, NULL, 0, NULL, 0, "-KPIC (the default) is only compatible with -G 0 for ucode compilers, changing to -G 0. \n");
    Gnum = "0";
block_218:
    if (abi_flag == 0) {
        goto block_221;
    }
    if (non_shared == 0) {
        goto block_221;
    }
    error(2, NULL, 0, NULL, 0, "-non_shared is not compatible with -abi for ucode compilers, changing to -abi.\n");
    non_shared = 0;
    kpic_flag = 1;
    Gnum = "0";
block_221:
    if (Oflag < 3) {
        goto block_224;
    }
    if (compiler != 4) {
        goto block_224;
    }
    error(2, NULL, 0, NULL, 0, "-O3 is not supported for assembly compiles for ucode compilers; changing to -O2.\n");
    Oflag = 2;
    uload = 0;
block_224:
    get_host_chiptype();
    if (targetsex != 0) {
        goto block_239;
    }
    addstr(&cppflags, "-D_MIPSEB");
    if (compiler != 1) {
        goto block_228;
    }
    temp_t1_2 = ansichoice;
    if (temp_t1_2 == 0) {
        goto block_228;
    }
    if (temp_t1_2 != 3) {
        goto block_229;
    }
block_228:
    addstr(&cppflags, "-DMIPSEB");
block_229:
    if (compiler != 1) {
        goto block_235;
    }
    temp_t4_2 = ansichoice;
    if (temp_t4_2 == 1) {
        goto block_234;
    }
    if (temp_t4_2 == 2) {
        goto block_234;
    }
    if (temp_t4_2 != 3) {
        goto block_235;
    }
    if (irix4 != 0) {
        goto block_235;
    }
block_234:
    addstr(&cppflags, "-D__STDC__=1");
block_235:
    if (compiler != 1) {
        goto block_238;
    }
    if (ansichoice != 2) {
        goto block_238;
    }
    addstr(&cppflags, "-D_POSIX_SOURCE=1");
block_238:
    addstr(&ccomflags, "-EB");
    addstr(&upasflags, "-EB");
    addstr(&fcomflags, "-EB");
    addstr(&upl1flags, "-EB");
    addstr(&ulpiflags, "-EB");
    addstr(&ucobflags, "-EB");
    addstr(&umergeflags, "-EB");
    addstr(&optflags, "-EB");
    addstr(&genflags, "-EB");
    addstr(&asflags, "-EB");
    goto block_253;
block_239:
    addstr(&cppflags, "-D_MIPSEL");
    addstr(&cppflags, "-D_MIPSEL");
    if (compiler != 1) {
        goto block_242;
    }
    temp_t9_4 = ansichoice;
    if (temp_t9_4 == 0) {
        goto block_242;
    }
    if (temp_t9_4 != 3) {
        goto block_243;
    }
block_242:
    addstr(&cppflags, "-DMIPSEL");
block_243:
    if (compiler != 1) {
        goto block_249;
    }
    temp_t0 = ansichoice;
    if (temp_t0 == 1) {
        goto block_248;
    }
    if (temp_t0 == 2) {
        goto block_248;
    }
    if (temp_t0 != 3) {
        goto block_249;
    }
    if (irix4 != 0) {
        goto block_249;
    }
block_248:
    addstr(&cppflags, "-D__STDC__=1");
block_249:
    if (compiler != 1) {
        goto block_252;
    }
    if (ansichoice != 2) {
        goto block_252;
    }
    addstr(&cppflags, "-D_POSIX_SOURCE=1");
block_252:
    addstr(&ccomflags, "-EL");
    addstr(&upasflags, "-EL");
    addstr(&fcomflags, "-EL");
    addstr(&upl1flags, "-EL");
    addstr(&ulpiflags, "-EL");
    addstr(&ucobflags, "-EL");
    addstr(&genflags, "-EL");
    addstr(&umergeflags, "-EL");
    addstr(&optflags, "-EL");
    addstr(&asflags, "-EL");
    addstr(&ldflags, "-EL");
block_253:
    temp_s3_2 = gflag;
    if (temp_s3_2 == 0) {
        goto block_258;
    }
    if (temp_s3_2 == 1) {
        goto block_260;
    }
    if (temp_s3_2 == 2) {
        goto block_261;
    }
    if (temp_s3_2 == 3) {
        goto block_262;
    }
    goto block_264;
block_258:
    addstr(&ccomflags, "-Xg0");
    addstr(&upasflags, "-g0");
    addstr(&fcomflags, "-g0");
    addstr(&ulpiflags, "-g0");
    addstr(&uopt0flags, "-g0");
    addstr(&ddoptflags, "-g0");
    addstr(&optflags, "-g0");
    addstr(&umergeflags, "-g0");
    addstr(&uloopflags, "-g0");
    addstr(&genflags, "-g0");
    addstr(&asflags, "-g0");
    addstr(&ldflags, "-g0");
    if (nocode != 0) {
        goto block_264;
    }
    addstr(&edisonflags, "-Zg0");
    goto block_263;
block_260:
    addstr(&edisonflags, "-Zg1");
    addstr(&ccomflags, "-Xg1");
    add_info("-g1");
    goto block_263;
block_261:
    addstr(&edisonflags, "-Zg2");
    addstr(&ccomflags, "-Xg2");
    add_info("-g2");
    goto block_263;
block_262:
    gflag += 1;
    addstr(&edisonflags, "-Zg3");
    addstr(&ccomflags, "-Xg3");
    add_info("-g3");
block_263:
block_264:
    if (mp_flag == 0) {
        goto block_267;
    }
    if (ddoptflag == 0) {
        goto block_267;
    }
    error(1, NULL, 0, NULL, 0, "can't use -mp/-pfa with -ddopt\n");
    exit(2);
block_267:
    if (mips3flag == 0) {
        goto block_270;
    }
    if (thirty2bitflag != 0) {
        goto block_270;
    }
    error(1, NULL, 0, NULL, 0, "-mips3 implies -64bit for ucode compilers, which is not supported.\n");
    exit(2);
block_270:
    if (irix4 == 0) {
        goto block_274;
    }
    if (compiler != 1) {
        goto block_274;
    }
    if (c_compiler_choice == 0) {
        goto block_274;
    }
    error(1, NULL, 0, NULL, 0, "IRIX4 not supported in Delta-C++\n");
    exit(2);
block_274:
    if (irix4 == 0) {
        goto block_278;
    }
    if (compiler != 3) {
        goto block_278;
    }
    if (D_1000BF74 == 0) {
        goto block_278;
    }
    error(1, NULL, 0, NULL, 0, "IRIX4 and -sa not supported together\n");
    exit(2);
block_278:
    if (cflag != 0) {
        goto block_283;
    }
    if (Sflag != 0) {
        goto block_283;
    }
    if (nocode != 0) {
        goto block_283;
    }
    if (Eflag != 0) {
        goto block_283;
    }
    if (Pflag == 0) {
        goto block_285;
    }
block_283:
    if (make_edison_shlib == 0) {
        goto block_285;
    }
    error(1, NULL, 0, NULL, 0, "-shared can be specified only when a link is to be performed for ucode compilers\n");
    exit(2);
block_285:
    if (cflag != 0) {
        goto block_290;
    }
    if (nocode != 0) {
        goto block_290;
    }
    if (srcfiles.length != 1) {
        goto block_290;
    }
    if (objfiles.length != 1) {
        goto block_290;
    }
    default_template_instantiation_mode = 1;
block_290:
    if (compiler != 1) {
        goto block_296;
    }
    temp_t3_3 = c_compiler_choice;
    if (temp_t3_3 == 2) {
        goto block_293;
    }
    if (temp_t3_3 != 3) {
        goto block_296;
    }
block_293:
    if (Fflag == 0) {
        goto block_296;
    }
    if (smart_build == 0) {
        goto block_296;
    }
    error(2, NULL, 0, NULL, 0, "-F and -smart cannot be specified together for ucode compilers: -smart ignored\n");
    smart_build = 0;
block_296:
    if (default_template_instantiation_mode == 0) {
        goto block_299;
    }
    if (force_prelink != 0) {
        goto block_299;
    }
    no_prelink = 1;
block_299:
    if (compiler != 1) {
        goto block_310;
    }
    if (c_compiler_choice != 3) {
        goto block_310;
    }
    sp124 = getenv("DCC_FORCE_OPT");
    sp120 = 1;
    if (Oflag < 3) {
        goto block_303;
    }
    Oflag = 2;
    uload = 0;
block_303:
    if (sp124 == NULL) {
        goto block_308;
    }
    temp_t6 = (u8) sp124->unk_0;
    if ((s32) temp_t6 < 0x30) {
        goto block_308;
    }
    if ((s32) temp_t6 >= 0x34) {
        goto block_308;
    }
    if (sp124->unk_1 != 0) {
        goto block_308;
    }
    sp120 = temp_t6 - 0x30;
block_308:
    if (sp120 >= Oflag) {
        goto block_310;
    }
    Oflag = sp120;
block_310:
    addstr(&execlist, "-Dunix");
    if (dmips_emit != 0) {
        goto block_319;
    }
    if (mips2flag == 0) {
        goto block_315;
    }
    if (dwopcodeflag == 0) {
        goto block_314;
    }
    error(1, NULL, 0, NULL, 0, "can't mix -mips2 with -dwopcode for ucode compilers\n");
    exit(2);
block_314:
    addstr(&execlist, "-Dmips=2");
block_315:
    if (mips3flag == 0) {
        goto block_317;
    }
    addstr(&execlist, "-Dmips=3");
    goto block_318;
block_317:
    addstr(&execlist, "-Dmips=1");
block_318:
block_319:
    addstr(&execlist, "-Dhost_mips");
    if (sixty4bitflag == 0) {
        goto block_322;
    }
    addstr(&ccomflags, "-64bit");
    add_info("-64bit");
    addstr(&ccomflags, "-dwopcode");
    add_info("-dwopcode");
    if (mips3flag != 0) {
        goto block_326;
    }
    chip_targ = 2;
    mips3flag = 1;
    addstr(&ccomflags, "-mips3");
    add_info("-mips3");
    relocate_passes("M", NULL, NULL);
    goto block_325;
block_322:
    if (dwopcodeflag == 0) {
        goto block_326;
    }
    addstr(&ccomflags, "-dwopcode");
    add_info("-dwopcode");
    if (mips3flag != 0) {
        goto block_326;
    }
    chip_targ = 2;
    mips3flag = 1;
    addstr(&ccomflags, "-mips3");
    add_info("-mips3");
    relocate_passes("M", NULL, NULL);
block_325:
block_326:
    temp_t2 = Oflag;
    if ((u32) temp_t2 >= 5U) {
        goto block_333;
    }
    switch (temp_t2);                               /* switch 1; jump table: jtbl_1000B274 */
case 0x0:                                           /* switch 1 */
    var_s1 = "-O0";
    goto block_333;
case 0x1:                                           /* switch 1 */
    var_s1 = "-O1";
    goto block_333;
case 0x2:                                           /* switch 1 */
    var_s1 = "-O2";
    goto block_333;
case 0x3:                                           /* switch 1 */
    var_s1 = "-O3";
    goto block_333;
case 0x4:                                           /* switch 1 */
    var_s1 = "-O4";
block_333:
    addstr(&ccomflags, var_s1);
    addstr(&upasflags, var_s1);
    addstr(&fcomflags, var_s1);
    addstr(&upl1flags, var_s1);
    addstr(&ulpiflags, var_s1);
    addstr(&ucobflags, var_s1);
    addstr(&uopt0flags, var_s1);
    addstr(&ddoptflags, var_s1);
    addstr(&optflags, var_s1);
    addstr(&umergeflags, var_s1);
    addstr(&uloopflags, var_s1);
    addstr(&genflags, var_s1);
    addstr(&asflags, var_s1);
    if (compiler != 3) {
        goto block_338;
    }
    if (automaticflag == 0) {
        goto block_336;
    }
    addstr(&fcomflags, "-automatic");
    goto block_337;
block_336:
    addstr(&fcomflags, "-static");
    addstr(&optflags, "-static");
block_337:
block_338:
    if (Vflag == 0) {
        goto block_340;
    }
    whats();
block_340:
    if (runerror == 0) {
        goto block_342;
    }
    exit(1);
block_342:
    if (sigset(2, (void (*)())1) == (void (*)())1) {
        goto block_344;
    }
    sigset(2, handler);
block_344:
    if (sigset(0xF, (void (*)())1) == (void (*)())1) {
        goto block_346;
    }
    sigset(0xF, handler);
block_346:
    if (sigset(0xD, (void (*)())1) == (void (*)())1) {
        goto block_348;
    }
    sigset(0xD, handler);
block_348:
    if (compiler != 6) {
        goto block_352;
    }
    if (nolockflag == 0) {
        goto block_352;
    }
    if (lpilockflag == 0) {
        goto block_352;
    }
    error(1, NULL, 0, NULL, 0, "Conflicting flags; -nolock and -lpilock can't both be specified for ucode compilers\n");
    exit(2);
block_352:
    if (Oflag < 3) {
        goto block_356;
    }
    if (cflag == 0) {
        goto block_356;
    }
    if (srcfiles.length != 1) {
        goto block_356;
    }
    error(2, NULL, 0, NULL, 0, "-c should not be used with ucode -O3 -o32 on a single file; use -j instead to get inter-module optimization.\n");
block_356:
    if (srcfiles.length < 2) {
        goto block_361;
    }
    if (compiler != 4) {
        goto block_361;
    }
    if (Eflag != 0) {
        goto block_361;
    }
    if (Pflag != 0) {
        goto block_361;
    }
    error(1, NULL, 0, NULL, 0, "only one source file can be specified with %s for ucode compilers\n", "as");
    exit(2);
block_361:
    mktempstr();
    var_s0_3 = 0;
    if (srcfiles.length > 0) {
        goto loop_363;
    }
    if (uload == 0) {
        goto block_2273;
    }
loop_363:
    nocompileneeded = 0;
    sp118 = NULL;
    longlong_emitted = 0;
    sp11C = D_1000BF74;
    if (var_s0_3 != srcfiles.length) {
        goto block_379;
    }
    uload = 0;
    if (runerror != 0) {
        goto block_2271;
    }
    if (Eflag != 0) {
        goto block_2271;
    }
    if (Pflag != 0) {
        goto block_2271;
    }
    if (uoutfile != NULL) {
        goto block_369;
    }
    addstr(&srcfiles, "u.out.?");
    goto block_372;
block_369:
    if (getsuf(uoutfile) == 0) {
        goto block_371;
    }
    addstr(&srcfiles, mksuf(uoutfile, 0x3FU));
    goto block_372;
block_371:
    addstr(&srcfiles, mkstr(uoutfile, ".?", NULL));
block_372:
    temp_t4_3 = Hchar;
    srcsuf = 0x3F;
    if (temp_t4_3 == 0x73) {
        goto block_377;
    }
    if (temp_t4_3 == 0x6D) {
        goto block_377;
    }
    if (temp_t4_3 == 0x6F) {
        goto block_377;
    }
    if (temp_t4_3 == 0x63) {
        goto block_377;
    }
    if (Kflag == 0) {
        goto block_378;
    }
block_377:
    symtab = mksuf(srcfiles.entries[var_s0_3], 0x54U);
    tmpst = 0;
    goto block_1757;
block_378:
    symtab = tempstr->unk_0;
    tmpst = 1;
    goto block_1757;
block_379:
    if (srcfiles.length < 2) {
        goto block_381;
    }
    fprintf(__iob + 0x20, "%s:\n", srcfiles.entries[var_s0_3]);
block_381:
    if (NoMoreOptions == 0) {
        goto block_384;
    }
    temp_t5_2 = srcfiles.entries;
    if ((u8) *temp_t5_2[var_s0_3] != 0x2D) {
        goto block_384;
    }
    passin = func_00433534(temp_t5_2[var_s0_3]);
    goto block_385;
block_384:
    passin = srcfiles.entries[var_s0_3];
block_385:
    if (compiler == 4) {
        goto block_388;
    }
    srcsuf = getsuf(srcfiles.entries[var_s0_3]);
    if ((u8) srcsuf != 0x6D) {
        goto block_389;
    }
    srcsuf = 0x66;
    goto block_389;
block_388:
    srcsuf = 0x73;
block_389:
    temp_t3_4 = Hchar;
    if (temp_t3_4 == 0x66) {
        goto block_405;
    }
    if (temp_t3_4 == 0x73) {
        goto block_405;
    }
    if (temp_t3_4 == 0x6D) {
        goto block_405;
    }
    if (temp_t3_4 == 0x6F) {
        goto block_405;
    }
    if (temp_t3_4 == 0x6B) {
        goto block_405;
    }
    if (temp_t3_4 == 0x63) {
        goto block_405;
    }
    if (Kflag != 0) {
        goto block_405;
    }
    temp_t9_5 = (u8) srcsuf;
    if (temp_t9_5 == 0x42) {
        goto block_405;
    }
    if (temp_t9_5 == 0x55) {
        goto block_405;
    }
    if (temp_t9_5 == 0x4F) {
        goto block_405;
    }
    if (temp_t9_5 == 0x47) {
        goto block_405;
    }
    if (temp_t9_5 == 0x53) {
        goto block_405;
    }
    if (temp_t9_5 == 0x4D) {
        goto block_405;
    }
    if (temp_t9_5 == 0x56) {
        goto block_405;
    }
    if (temp_t9_5 == 0x44) {
        goto block_405;
    }
    if (temp_t9_5 != 0x51) {
        goto block_409;
    }
block_405:
    tmpst = 0;
    if (compiler != 4) {
        goto block_408;
    }
    if (getsuf(srcfiles.entries[var_s0_3]) != 0) {
        goto block_408;
    }
    symtab = mkstr(srcfiles.entries[var_s0_3], ".T", NULL);
    goto block_410;
block_408:
    symtab = mksuf(srcfiles.entries[var_s0_3], 0x54U);
    goto block_410;
block_409:
    tmpst = 1;
    symtab = tempstr->unk_0;
block_410:
    temp_s3_3 = (u8) srcsuf;
    if ((s32) temp_s3_3 < 4) {
        goto block_417;
    }
    if ((s32) temp_s3_3 < 0x47) {
        goto block_414;
    }
    if ((u32) (temp_s3_3 - 0x63) >= 0x11U) {
        goto block_464;
    }
    switch (temp_s3_3);                             /* switch 2; jump table: jtbl_1000B288 */
block_414:
    if (temp_s3_3 == 6) {
        goto block_427;
    }
    if (temp_s3_3 == 0x46) {
        goto block_439;
    }
    goto block_464;
block_417:
    if (temp_s3_3 == 1) {
        goto block_444;
    }
    if (temp_s3_3 == 2) {
        goto block_449;
    }
    if (temp_s3_3 == 3) {
        goto block_454;
    }
    goto block_464;
case 0x73:                                          /* switch 2 */
    if (compiler != 1) {
        goto block_424;
    }
    temp_t4_4 = compdirs.unk_0;
    if (temp_t4_4 == currcomp) {
        goto block_424;
    }
    currcomp = temp_t4_4;
    relocate_passes("pKfjsmvocabtyz", NULL, NULL);
case 0x69:                                          /* switch 2 */
block_424:
    if (compiler != 1) {
        goto block_427;
    }
    temp_t6_2 = compdirs.unk_0;
    if (temp_t6_2 == currcomp) {
        goto block_427;
    }
    currcomp = temp_t6_2;
    relocate_passes("pKfjsmvocabtyz", NULL, NULL);
case 0x63:                                          /* switch 2 */
block_427:
    if (compiler == 1) {
        goto block_430;
    }
    temp_t1_3 = compdirs.unk_4;
    if (temp_t1_3 == currcomp) {
        goto block_433;
    }
    currcomp = temp_t1_3;
    relocate_passes("pKfjsmvocabtyz", NULL, NULL);
    goto block_432;
block_430:
    temp_t4_5 = compdirs.unk_0;
    if (temp_t4_5 == currcomp) {
        goto block_433;
    }
    currcomp = temp_t4_5;
    relocate_passes("pKfjsmvocabtyz", NULL, NULL);
block_432:
block_433:
    compchoice = 0;
    goto block_464;
case 0x70:                                          /* switch 2 */
    if (compiler == 2) {
        goto block_437;
    }
    temp_t6_3 = compdirs.unk_8;
    if (temp_t6_3 == currcomp) {
        goto block_464;
    }
    currcomp = temp_t6_3;
    relocate_passes("pfjsmvocabtyz", NULL, NULL);
    goto block_463;
block_437:
    temp_t8_4 = compdirs.unk_0;
    if (temp_t8_4 == currcomp) {
        goto block_464;
    }
    currcomp = temp_t8_4;
    relocate_passes("pfjsmvocabtyz", NULL, NULL);
    goto block_463;
case 0x66:                                          /* switch 2 */
block_439:
    if (compiler == 3) {
        goto block_442;
    }
    temp_t4_6 = compdirs.unk_C;
    if (temp_t4_6 == currcomp) {
        goto block_464;
    }
    currcomp = temp_t4_6;
    relocate_passes("pfjsmvocabtyz", NULL, NULL);
    goto block_463;
block_442:
    temp_t0_2 = compdirs.unk_0;
    if (temp_t0_2 == currcomp) {
        goto block_464;
    }
    currcomp = temp_t0_2;
    relocate_passes("pfjsmvocabtyz", NULL, NULL);
    goto block_463;
block_444:
    if (compiler == 5) {
        goto block_447;
    }
    temp_t8_5 = compdirs.unk_14;
    if (temp_t8_5 == currcomp) {
        goto block_464;
    }
    currcomp = temp_t8_5;
    relocate_passes("pfekjsmvocabtyz", NULL, NULL);
    goto block_463;
block_447:
    temp_t9_6 = compdirs.unk_0;
    if (temp_t9_6 == currcomp) {
        goto block_464;
    }
    currcomp = temp_t9_6;
    relocate_passes("pfekjsmvocabtyz", NULL, NULL);
    goto block_463;
block_449:
    if (compiler == 6) {
        goto block_452;
    }
    temp_t0_3 = compdirs.unk_18;
    if (temp_t0_3 == currcomp) {
        goto block_464;
    }
    currcomp = temp_t0_3;
    relocate_passes("pfekjsmvocabtyz", NULL, NULL);
    goto block_463;
block_452:
    temp_t3_5 = compdirs.unk_0;
    if (temp_t3_5 == currcomp) {
        goto block_464;
    }
    currcomp = temp_t3_5;
    relocate_passes("pfekjsmvocabtyz", NULL, NULL);
    goto block_463;
block_454:
    temp_t2_2 = compiler;
    if (temp_t2_2 == 1) {
        goto block_461;
    }
    if (temp_t2_2 == 5) {
        goto block_461;
    }
    if (temp_t2_2 == 6) {
        goto block_461;
    }
    temp_t9_7 = compdirs.unk_4;
    temp_t7_3 = currcomp;
    if (temp_t9_7 == temp_t7_3) {
        goto block_464;
    }
    if (compdirs.unk_14 == temp_t7_3) {
        goto block_464;
    }
    if (compdirs.unk_18 == temp_t7_3) {
        goto block_464;
    }
    currcomp = temp_t9_7;
    relocate_passes("pekjsmvocabtyz", NULL, NULL);
    goto block_463;
block_461:
    temp_t1_4 = compdirs.unk_0;
    if (temp_t1_4 == currcomp) {
        goto block_464;
    }
    currcomp = temp_t1_4;
    relocate_passes("pfjsmvocabtyz", NULL, NULL);
block_463:
block_464:
    if (compiler != 3) {
        goto block_469;
    }
    if (D_1000BF74 == 0) {
        goto block_469;
    }
    temp_t6_4 = (u8) srcsuf;
    if (temp_t6_4 == 0x66) {
        goto block_469;
    }
    if (temp_t6_4 == 0x46) {
        goto block_469;
    }
    D_1000BF74 = 0;
    relocate_passes("f", NULL, NULL);
block_469:
    if (D_1000BF74 == 0) {
        goto block_474;
    }
    temp_t5_3 = compiler;
    if (temp_t5_3 == 3) {
        goto block_473;
    }
    if (temp_t5_3 != 1) {
        goto block_474;
    }
    if (c_compiler_choice == 0) {
        goto block_474;
    }
block_473:
    record_static_fileset((s32) srcfiles.entries[var_s0_3]);
block_474:
    if (compiler != 1) {
        goto loop_485;
    }
    if (c_compiler_choice != 1) {
        goto loop_485;
    }
    temp_s3_4 = ansichoice;
    if (temp_s3_4 == 0) {
        goto block_483;
    }
    if (temp_s3_4 == 1) {
        goto block_481;
    }
    if (temp_s3_4 == 2) {
        goto block_481;
    }
    if (temp_s3_4 == 3) {
        goto block_482;
    }
    goto block_483;
block_481:
    edison_type = (s8* )2;
    goto loop_485;
block_482:
    edison_type = (s8* )1;
    goto loop_485;
block_483:
    var_at = &edison_type;
    var_t4 = (s8* )3;
block_484:
    *var_at = var_t4;
loop_485:
    if (compchoice != 0) {
        goto block_493;
    }
    if (irix4 == 0) {
        goto block_490;
    }
    if (ansichoice != 0) {
        goto block_489;
    }
    compchoice = 1;
    goto block_493;
block_489:
    compchoice = 2;
    goto block_493;
block_490:
    if (ansichoice != 0) {
        goto block_492;
    }
    compchoice = 3;
    goto block_493;
block_492:
    compchoice = 3;
block_493:
    if (Eflag == 0) {
        goto block_495;
    }
    if ((u8) srcsuf != 0x61) {
        goto block_532;
    }
block_495:
    temp_s3_5 = (u8) srcsuf;
    if ((s32) temp_s3_5 < 4) {
        goto block_501;
    }
    if ((s32) temp_s3_5 < 7) {
        goto block_499;
    }
    if ((u32) (temp_s3_5 - 0x42) >= 0x34U) {
        goto block_532;
    }
    switch (temp_s3_5);                             /* switch 3; jump table: jtbl_1000B2CC */
block_499:
    if (temp_s3_5 == 6) {
        goto block_505;
    }
    goto block_532;
block_501:
    if (temp_s3_5 == 1) {
        goto block_518;
    }
    if (temp_s3_5 == 2) {
        goto block_520;
    }
    if (temp_s3_5 == 3) {
        goto block_1418;
    }
    goto block_532;
case 0x63:                                          /* switch 3 */
block_505:
    if (oldccomflag == 1) {
        goto block_507;
    }
    oldcflag = 0;
block_507:
    if (docpp != 0) {
        goto block_532;
    }
    if (default_nocpp == 0) {
        goto block_941;
    }
    goto block_532;
case 0x69:                                          /* switch 3 */
    temp_t8_6 = compiler;
    if ((u32) (temp_t8_6 - 1) >= 6U) {
        goto block_512;
    }
    switch (temp_t8_6);                             /* switch 4; jump table: jtbl_1000B39C */
case 0x70:                                          /* switch 3 */
case 0x4:                                           /* switch 4 */
block_512:
    if (stdflag != 0) {
        goto block_1342;
    }
    if (docpp != 0) {
        goto block_532;
    }
    if (default_nocpp != 0) {
        goto block_532;
    }
    goto block_1342;
case 0x66:                                          /* switch 3 */
    if (docpp == 0) {
        goto block_1506;
    }
    goto block_532;
block_518:
    if (docpp == 0) {
        goto block_1389;
    }
    goto block_532;
block_520:
    if (docpp == 0) {
        goto block_1454;
    }
    goto block_532;
case 0x55:                                          /* switch 3 */
    execlist.length = 0;
    addstr(&execlist, "utob");
    addstr(&execlist, srcfiles.entries[var_s0_3]);
    if (Kflag == 0) {
        goto block_524;
    }
    passout = mksuf(srcfiles.entries[var_s0_3], 0x42U);
    goto block_525;
block_524:
    passout = tempstr->unk_4;
block_525:
    temp_t7_4 = passout;
    if (temp_t7_4 == NULL) {
        goto block_528;
    }
    if (regular_not_writeable(temp_t7_4) != 1) {
        goto block_528;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
block_528:
    addstr(&execlist, passout);
    if (run(utob, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_531;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_2271;
    }
    unlink(passout);
    goto block_2270;
block_531:
    passin = passout;
    goto block_1730;
case 0x43:                                          /* switch 3 */
case 0x45:                                          /* switch 3 */
case 0x46:                                          /* switch 3 */
case 0x48:                                          /* switch 3 */
case 0x49:                                          /* switch 3 */
case 0x4A:                                          /* switch 3 */
case 0x4B:                                          /* switch 3 */
case 0x4C:                                          /* switch 3 */
case 0x4E:                                          /* switch 3 */
case 0x50:                                          /* switch 3 */
case 0x52:                                          /* switch 3 */
case 0x54:                                          /* switch 3 */
case 0x57:                                          /* switch 3 */
case 0x58:                                          /* switch 3 */
case 0x59:                                          /* switch 3 */
case 0x5A:                                          /* switch 3 */
case 0x5B:                                          /* switch 3 */
case 0x5C:                                          /* switch 3 */
case 0x5D:                                          /* switch 3 */
case 0x5E:                                          /* switch 3 */
case 0x5F:                                          /* switch 3 */
case 0x60:                                          /* switch 3 */
case 0x61:                                          /* switch 3 */
case 0x62:                                          /* switch 3 */
case 0x64:                                          /* switch 3 */
case 0x67:                                          /* switch 3 */
case 0x68:                                          /* switch 3 */
case 0x6A:                                          /* switch 3 */
case 0x6B:                                          /* switch 3 */
case 0x6C:                                          /* switch 3 */
case 0x6D:                                          /* switch 3 */
case 0x6E:                                          /* switch 3 */
case 0x6F:                                          /* switch 3 */
case 0x71:                                          /* switch 3 */
case 0x74:                                          /* switch 3 */
block_532:
    dmips_emit = 0;
    execlist.length = 0;
    sp114 = cppchoice;
    execlist.length = 0;
    if (Eflag == 0) {
        goto block_535;
    }
    if (irix4 != 0) {
        goto block_535;
    }
    compchoice = 3;
    goto block_537;
block_535:
    if ((u8) srcsuf != 0x73) {
        goto block_537;
    }
    compchoice = 4;
block_537:
    temp_t8_7 = (u8) srcsuf;
    if (temp_t8_7 == 0x63) {
        goto block_543;
    }
    if (temp_t8_7 == 6) {
        goto block_543;
    }
    if (compiler != 1) {
        goto block_547;
    }
    if (nocode == 0) {
        goto block_547;
    }
    if (D_1000BF74 == 0) {
        goto block_547;
    }
    if (temp_t8_7 != 0x68) {
        goto block_547;
    }
block_543:
    if (cppchoice != 2) {
        goto block_546;
    }
    if (oldcppflag == 0) {
        goto block_559;
    }
    if (ansichoice == 0) {
        goto block_559;
    }
block_546:
    cppchoice = 1;
    relocate_passes("p", NULL, NULL);
    goto block_558;
block_547:
    if ((u8) srcsuf != 0x68) {
        goto block_551;
    }
    if (compiler != 1) {
        goto block_551;
    }
    if (cppchoice != 0) {
        goto block_559;
    }
    cppchoice = 1;
    relocate_passes("p", NULL, NULL);
    goto block_558;
block_551:
    if (compiler != 1) {
        goto block_556;
    }
    if (Eflag != 0) {
        goto block_559;
    }
    if (Pflag != 0) {
        goto block_559;
    }
    if (cppchoice != 3) {
        goto block_559;
    }
    cppchoice = 2;
    relocate_passes("p", NULL, NULL);
    goto block_558;
block_556:
    if (cppchoice != 3) {
        goto block_559;
    }
    cppchoice = 2;
    relocate_passes("p", NULL, NULL);
block_558:
block_559:
    temp_t0_4 = compchoice;
    if (temp_t0_4 == 3) {
        goto block_561;
    }
    if (temp_t0_4 != 4) {
        goto block_565;
    }
block_561:
    if (run_sopt != 0) {
        goto block_565;
    }
    temp_t3_6 = cmp_flag;
    if (temp_t3_6 & 1) {
        goto block_565;
    }
    if (temp_t3_6 & 8) {
        goto block_565;
    }
    addstr(&execlist, cfe);
    goto block_573;
block_565:
    if (sixty4bitflag == 0) {
        goto block_567;
    }
    error(1, NULL, 0, NULL, 0, "-64bit option is not implemented with ccom or accom.\n");
    exit(2);
block_567:
    if (c_compiler_choice != 0) {
        goto block_574;
    }
    temp_t7_5 = cppchoice;
    if (temp_t7_5 == 1) {
        goto block_571;
    }
    if (temp_t7_5 == 3) {
        goto block_571;
    }
    var_s3_3 = "cpp";
    goto block_572;
block_571:
    var_s3_3 = "acpp";
block_572:
    addstr(&execlist, var_s3_3);
block_573:
block_574:
    if (mips_abi != 1) {
        goto block_583;
    }
    addstr(&execlist, "-D_MIPS_FPSET=16");
    if (mips1flag == 0) {
        goto block_577;
    }
    addstr(&execlist, "-D_MIPS_ISA=1");
    goto block_581;
block_577:
    if (mips2flag == 0) {
        goto block_579;
    }
    addstr(&execlist, "-D_MIPS_ISA=2");
    goto block_581;
block_579:
    if (mips3flag == 0) {
        goto block_582;
    }
    addstr(&execlist, "-D_MIPS_ISA=3");
block_581:
block_582:
    addstr(&execlist, "-D_ABIO32=1");
    addstr(&execlist, "-D_MIPS_SIM=_ABIO32");
    addstr(&execlist, "-D_MIPS_SZINT=32");
    addstr(&execlist, "-D_MIPS_SZLONG=32");
    addstr(&execlist, "-D_MIPS_SZPTR=32");
    goto block_587;
block_583:
    if (mips_abi != 2) {
        goto block_585;
    }
    addstr(&execlist, "-D_MIPS_FPSET=32");
    addstr(&execlist, "-D_MIPS_ISA=_MIPS_ISA_MIPS3");
    addstr(&execlist, "-D_MIPS_SIM=_MIPS_SIM_ABI64");
    addstr(&execlist, "-D_MIPS_SZINT=32");
    addstr(&execlist, "-D_MIPS_SZLONG=64");
    addstr(&execlist, "-D_MIPS_SZPTR=64");
    goto block_587;
block_585:
    if (mips_abi == 0) {
        goto block_588;
    }
    error(1, NULL, 0, NULL, 0, "Unknown value for mips_abi: %d.\n", mips_abi);
    exit(2);
block_587:
block_588:
    if (c_compiler_choice != 0) {
        goto block_606;
    }
    if (emptyIflag == 0) {
        goto block_592;
    }
    if (compchoice == 3) {
        goto block_592;
    }
    addstr(&execlist, "-nostdinc");
block_592:
    if (cppchoice != 1) {
        goto block_603;
    }
    temp_t1_5 = ansichoice;
    if (temp_t1_5 == 0) {
        goto block_595;
    }
    if (temp_t1_5 != 3) {
        goto block_596;
    }
block_595:
    addstr(&execlist, "-D__EXTENSIONS__");
block_596:
    if (compchoice == 3) {
        goto block_603;
    }
    if (fullwarn == 0) {
        goto block_599;
    }
    addstr(&execlist, "-Wall");
block_599:
    if (acpp_traditional == 0) {
        goto block_601;
    }
    addstr(&execlist, "-traditional");
block_601:
    addstr(&execlist, "-trigraphs");
    if (ansichoice == 0) {
        goto block_603;
    }
    addstr(&execlist, "-undef");
    addstr(&execlist, "-p");
block_603:
    if (cppchoice != 2) {
        goto block_612;
    }
    if (compchoice != 3) {
        goto block_612;
    }
    addstr(&execlist, "-D__EXTENSIONS__");
    goto block_611;
block_606:
    addstr(&execlist, "-YE");
    if (edison_type != (s8* )2) {
        goto block_608;
    }
    addstr(&execlist, "-a");
block_608:
    temp_t9_8 = edison_type;
    if (temp_t9_8 == (s8* )1) {
        goto block_610;
    }
    if (temp_t9_8 != (s8* )3) {
        goto block_612;
    }
block_610:
    addstr(&execlist, "-D__EXTENSIONS__");
block_611:
block_612:
    temp_s3_6 = (u8) srcsuf;
    if ((s32) temp_s3_6 < 7) {
        goto block_618;
    }
    if ((s32) temp_s3_6 < 0x47) {
        goto block_616;
    }
    if ((u32) (temp_s3_6 - 0x63) >= 0x11U) {
        goto block_644;
    }
    switch (temp_s3_6);                             /* switch 5; jump table: jtbl_1000B3B4 */
block_616:
    if (temp_s3_6 == 0x46) {
        goto block_639;
    }
    goto block_644;
block_618:
    if (temp_s3_6 == 1) {
        goto block_641;
    }
    if (temp_s3_6 == 2) {
        goto block_642;
    }
    if (temp_s3_6 != 6) {
        goto block_644;
    }
case 0x63:                                          /* switch 5 */
case 0x68:                                          /* switch 5 */
    if ((u8) srcsuf != 0x68) {
        goto block_623;
    }
    if (D_1000BF74 == 0) {
        goto block_644;
    }
block_623:
    if (compiler != 1) {
        goto block_629;
    }
    temp_t8_8 = c_compiler_choice;
    if (temp_t8_8 == 2) {
        goto block_626;
    }
    if (temp_t8_8 != 3) {
        goto block_629;
    }
block_626:
    addstr(&execlist, "-D_LANGUAGE_C_PLUS_PLUS=1");
    addstr(&execlist, "-D__cplusplus=1");
    addstr(&execlist, "-D__ANSI_CPP__=1");
    if (compiler != 1) {
        goto block_644;
    }
    if (c_compiler_choice != 3) {
        goto block_644;
    }
    addstr(&execlist, "-D_DELTA_EXTENSIONS=1");
    goto block_643;
block_629:
    temp_t5_4 = ansichoice;
    if (temp_t5_4 == 0) {
        goto block_631;
    }
    if (temp_t5_4 != 3) {
        goto block_632;
    }
block_631:
    addstr(&execlist, "-DLANGUAGE_C");
block_632:
    addstr(&execlist, "-D_LANGUAGE_C");
    if (cmp_flag == 0) {
        goto block_634;
    }
    addstr(&execlist, "-D_LANGUAGE_PWRC");
block_634:
    if (cmp_flag & 1) {
        goto block_636;
    }
    if (run_sopt == 0) {
        goto block_644;
    }
block_636:
    if (cppchoice != 1) {
        goto block_644;
    }
    addstr(&execlist, "-trigraphs");
    goto block_643;
case 0x70:                                          /* switch 5 */
    addstr(&execlist, "-DLANGUAGE_PASCAL");
    addstr(&execlist, "-D_LANGUAGE_PASCAL");
    addstr(&execlist, "-Q");
    goto block_643;
case 0x65:                                          /* switch 5 */
case 0x66:                                          /* switch 5 */
case 0x72:                                          /* switch 5 */
block_639:
    addstr(&execlist, "-DLANGUAGE_FORTRAN");
    addstr(&execlist, "-D_LANGUAGE_FORTRAN");
    goto block_643;
case 0x73:                                          /* switch 5 */
    addstr(&execlist, "-DLANGUAGE_ASSEMBLY");
    addstr(&execlist, "-D_LANGUAGE_ASSEMBLY");
    goto block_643;
block_641:
    addstr(&execlist, "-DLANGUAGE_PL1");
    addstr(&execlist, "-D_LANGUAGE_PL1");
    goto block_643;
block_642:
    addstr(&execlist, "-DLANGUAGE_COBOL");
    addstr(&execlist, "-D_LANGUAGE_COBOL");
block_643:
block_644:
    temp_t3_7 = ansichoice;
    if (temp_t3_7 == 0) {
        goto block_646;
    }
    if (temp_t3_7 != 3) {
        goto block_649;
    }
block_646:
    addstr(&execlist, "-D__INLINE_INTRINSICS");
    addstr(&execlist, "-Dsgi");
    if (svr4_systype != 0) {
        goto block_648;
    }
    addstr(&execlist, "-DSVR3");
    addstr(&execlist, "-D__SVR3");
block_648:
    addstr(&execlist, "-D__sgi");
    goto block_651;
block_649:
    addstr(&execlist, "-D__sgi");
    if (svr4_systype != 0) {
        goto block_652;
    }
    addstr(&execlist, "-D__SVR3");
block_651:
block_652:
    if (compchoice == 3) {
        goto block_658;
    }
    if (dollar_sign == 0) {
        goto block_658;
    }
    if (cppchoice != 1) {
        goto block_656;
    }
    addstr(&execlist, "-$");
    goto block_657;
block_656:
    addstr(&execlist, "-dollar");
block_657:
block_658:
    temp_t9_9 = ansichoice;
    if (temp_t9_9 == 0) {
        goto block_660;
    }
    if (temp_t9_9 != 3) {
        goto block_669;
    }
block_660:
    addstr(&execlist, "-Dunix");
    addstr(&execlist, "-Dmips");
    addstr(&execlist, "-Dhost_mips");
    addstr(&execlist, "-D__unix");
    addstr(&execlist, "-D__host_mips");
    if (irix4 != 0) {
        goto block_666;
    }
    if (svr4_systype == 0) {
        goto block_665;
    }
    temp_t2_3 = ansichoice;
    if (temp_t2_3 == 1) {
        goto block_665;
    }
    if (temp_t2_3 == 2) {
        goto block_665;
    }
    addstr(&execlist, "-D_SVR4_SOURCE");
block_665:
    addstr(&execlist, "-D_MODERN_C");
    addstr(&execlist, "-D_SGI_SOURCE");
block_666:
    if (kpic_flag == 0) {
        goto block_668;
    }
    addstr(&execlist, "-D_PIC");
block_668:
    addstr(&execlist, "-D__DSO__");
    goto block_678;
block_669:
    addstr(&execlist, "-D__unix");
    addstr(&execlist, "-D__host_mips");
    if (irix4 != 0) {
        goto block_675;
    }
    if (svr4_systype == 0) {
        goto block_674;
    }
    temp_t4_7 = ansichoice;
    if (temp_t4_7 == 1) {
        goto block_674;
    }
    if (temp_t4_7 == 2) {
        goto block_674;
    }
    addstr(&execlist, "-D_SVR4_SOURCE");
block_674:
    addstr(&execlist, "-D_MODERN_C");
block_675:
    if (kpic_flag == 0) {
        goto block_677;
    }
    addstr(&execlist, "-D_PIC");
block_677:
    addstr(&execlist, "-D__DSO__");
block_678:
    temp_t7_6 = systype;
    if (temp_t7_6 == NULL) {
        goto block_686;
    }
    if (irix4 != 0) {
        goto block_686;
    }
    var_s1_2 = temp_t7_6;
    if ((u8) *var_s1_2 == 0) {
        goto block_682;
    }
loop_681:
    var_s1_2->unk_0 = toupper((u8) var_s1_2->unk_0);
    var_s1_2 += 1;
    if (var_s1_2->unk_1 != 0) {
        goto loop_681;
    }
block_682:
    temp_t2_4 = ansichoice;
    if (temp_t2_4 == 0) {
        goto block_684;
    }
    if (temp_t2_4 != 3) {
        goto block_685;
    }
block_684:
    addstr(&execlist, mkstr("-DSYSTYPE_", systype, NULL));
block_685:
    addstr(&execlist, mkstr("-D_SYSTYPE_", systype, NULL));
block_686:
    if (svr4_systype != 0) {
        goto block_691;
    }
    temp_t8_9 = ansichoice;
    if (temp_t8_9 == 0) {
        goto block_689;
    }
    if (temp_t8_9 != 3) {
        goto block_690;
    }
block_689:
    addstr(&execlist, "-DSYSTYPE_SYSV");
block_690:
    addstr(&execlist, "-D_SYSTYPE_SYSV");
block_691:
    if (sixty4bitflag == 0) {
        goto block_693;
    }
    addstr(&execlist, "-D__64BIT");
block_693:
    temp_t4_8 = ansichoice;
    if (temp_t4_8 == 0) {
        goto block_695;
    }
    if (temp_t4_8 != 3) {
        goto block_697;
    }
block_695:
    if (longlong_emitted != 0) {
        goto block_697;
    }
    addstr(&execlist, "-D_LONGLONG");
    longlong_emitted = 1;
block_697:
    if (dmips_emit != 0) {
        goto block_708;
    }
    if (mips2flag == 0) {
        goto block_704;
    }
    if (call_shared != 0) {
        goto block_701;
    }
    if (default_call_shared == 0) {
        goto block_703;
    }
block_701:
    if (kpic_flag != 0) {
        goto block_703;
    }
    old_non_shared = 1;
    non_shared = 1;
    default_call_shared = 0;
    call_shared = 0;
block_703:
    addstr(&execlist, "-D__mips=2");
    goto block_707;
block_704:
    if (mips3flag == 0) {
        goto block_706;
    }
    addstr(&execlist, "-D__mips=3");
    goto block_707;
block_706:
    addstr(&execlist, "-D__mips=1");
block_707:
block_708:
    dmips_emit = 1;
    if (irix4 == 0) {
        goto block_710;
    }
    include = mkstr("/usr/irix4/", "usr/include", NULL);
block_710:
    if (include == NULL) {
        goto block_713;
    }
    if (strcmp(comp_target_root, "/") != 0) {
        goto block_714;
    }
    if (systype != NULL) {
        goto block_714;
    }
block_713:
    if (fiveflag == 0) {
        goto block_719;
    }
block_714:
    if (compiler != 1) {
        goto block_716;
    }
    if (c_compiler_choice != 0) {
        goto block_719;
    }
block_716:
    if (compiler != 3) {
        goto block_718;
    }
    if (D_1000BF74 != 0) {
        goto block_719;
    }
block_718:
    addstr(&execlist, "-I");
block_719:
    addlist(&execlist, &cppflags);
    if (cppchoice != 1) {
        goto block_721;
    }
    addlist(&execlist, &acppflags);
block_721:
    addlist(&execlist, &undefineflags);
    if (emptyIflag != 0) {
        goto block_732;
    }
    if (abi_flag == 0) {
        goto block_725;
    }
    temp_t7_7 = includeB;
    if (temp_t7_7 == NULL) {
        goto block_725;
    }
    addstr(&execlist, mkstr("-I", temp_t7_7, NULL));
block_725:
    if (einclude == NULL) {
        goto block_730;
    }
    if (compiler != 1) {
        goto block_730;
    }
    temp_t2_5 = c_compiler_choice;
    if (temp_t2_5 == 2) {
        goto block_729;
    }
    if (temp_t2_5 != 3) {
        goto block_730;
    }
block_729:
    addstr(&execlist, mkstr("-I", einclude, NULL));
block_730:
    temp_t3_8 = include;
    if (temp_t3_8 == NULL) {
        goto block_732;
    }
    addstr(&execlist, mkstr("-I", temp_t3_8, NULL));
block_732:
    if (Pflag == 0) {
        goto block_737;
    }
    if (compiler != 4) {
        goto block_736;
    }
    if (getsuf(srcfiles.entries[var_s0_3]) != 0) {
        goto block_736;
    }
    passout = mkstr(srcfiles.entries[var_s0_3], ".i", NULL);
    goto block_749;
block_736:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x69U);
    goto block_749;
block_737:
    if (Eflag == 0) {
        goto block_739;
    }
    passout = NULL;
    goto block_749;
block_739:
    if (Hchar == 0x4B) {
        goto block_741;
    }
    if (Kflag == 0) {
        goto block_748;
    }
block_741:
    if (compchoice != 3) {
        goto block_747;
    }
    if (run_sopt != 0) {
        goto block_747;
    }
    if (acpp != 0) {
        goto block_747;
    }
    if (cmp_flag != 0) {
        goto block_747;
    }
    if (compiler != 1) {
        goto block_747;
    }
    passout = mksuf(srcfiles.entries[var_s0_3], 0x42U);
    goto block_749;
block_747:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x69U);
    goto block_749;
block_748:
    passout = tempstr->unk_8;
block_749:
    temp_t1_6 = passout;
    if (temp_t1_6 == NULL) {
        goto block_752;
    }
    if (regular_not_writeable(temp_t1_6) != 1) {
        goto block_752;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
block_752:
    if (compiler != 3) {
        goto block_755;
    }
    if (D_1000BF74 == 0) {
        goto block_755;
    }
    addstr(&execlist, "-K");
    addstr(&execlist, "-E");
    addstr(&execlist, sp144);
block_755:
    if (c_compiler_choice != 0) {
        goto block_757;
    }
    addstr(&execlist, passin);
block_757:
    temp_t5_5 = compchoice;
    if (temp_t5_5 == 3) {
        goto block_759;
    }
    if (temp_t5_5 != 4) {
        goto block_766;
    }
block_759:
    temp_t9_10 = compiler;
    if (temp_t9_10 == 1) {
        goto block_761;
    }
    if (temp_t9_10 != 4) {
        goto block_766;
    }
block_761:
    if (run_sopt != 0) {
        goto block_766;
    }
    temp_t0_5 = cmp_flag;
    if (temp_t0_5 & 1) {
        goto block_766;
    }
    if (temp_t0_5 & 8) {
        goto block_766;
    }
    if (acpp != 0) {
        goto block_766;
    }
    if (oldcppflag == 0) {
        goto block_779;
    }
block_766:
    if (compiler != 3) {
        goto block_769;
    }
    if (D_1000BF74 == 0) {
        goto block_769;
    }
    var_s3_4 = &cfe;
    goto block_770;
block_769:
    var_s3_4 = &cpp;
block_770:
    if (run(*var_s3_4, execlist.entries, NULL, passout, NULL) == 0) {
        goto block_923;
    }
    runerror += 1;
    if (Eflag != 0) {
        goto block_778;
    }
    temp_t1_7 = (u8) srcsuf;
    if (temp_t1_7 == 0x65) {
        goto block_774;
    }
    if (temp_t1_7 != 0x72) {
        goto block_775;
    }
block_774:
    if (Kflag == 0) {
        goto block_777;
    }
block_775:
    if ((u8) srcsuf != 0x73) {
        goto block_778;
    }
    if (mflag == 0) {
        goto block_778;
    }
block_777:
    unlink(passin);
block_778:
    unlink(passout);
    cppchoice = sp114;
    relocate_passes("p", NULL, NULL);
    goto block_2270;
block_779:
    cppchoice = sp114;
    relocate_passes("p", NULL, NULL);
    temp_t4_9 = (u8) srcsuf;
    if (temp_t4_9 == 0x63) {
        goto block_785;
    }
    if (temp_t4_9 == 6) {
        goto block_785;
    }
    if (compiler != 1) {
        goto block_787;
    }
    if (nocode == 0) {
        goto block_787;
    }
    if (D_1000BF74 == 0) {
        goto block_787;
    }
    if (temp_t4_9 != 0x68) {
        goto block_787;
    }
block_785:
    if (Pflag != 0) {
        goto block_787;
    }
    if (Eflag == 0) {
        goto block_1043;
    }
block_787:
    if (minus_M != 0) {
        goto block_789;
    }
    addstr(&execlist, "-E");
block_789:
    if (compiler != 1) {
        goto block_791;
    }
    if (c_compiler_choice != 0) {
        goto block_831;
    }
block_791:
    temp_s3_7 = (u8) srcsuf;
    if ((s32) temp_s3_7 < 3) {
        goto block_797;
    }
    if ((s32) temp_s3_7 < 0x47) {
        goto block_795;
    }
    if ((u32) (temp_s3_7 - 0x63) >= 0x11U) {
        goto block_808;
    }
    switch (temp_s3_7);                             /* switch 6; jump table: jtbl_1000B3F8 */
block_795:
    if (temp_s3_7 == 0x46) {
        goto block_803;
    }
    goto block_808;
block_797:
    if (temp_s3_7 == 1) {
        goto block_805;
    }
    if (temp_s3_7 == 2) {
        goto block_806;
    }
    goto block_808;
case 0x63:                                          /* switch 6 */
    addstr(&execlist, "-D_LANGUAGE_C");
    if (oldcflag != 0) {
        goto block_808;
    }
    addstr(&execlist, "-D_CFE");
    goto block_807;
case 0x70:                                          /* switch 6 */
    addstr(&execlist, "-DLANGUAGE_PASCAL");
    addstr(&execlist, "-D_LANGUAGE_PASCAL");
    addstr(&execlist, "-Q");
    goto block_807;
case 0x65:                                          /* switch 6 */
case 0x66:                                          /* switch 6 */
case 0x72:                                          /* switch 6 */
block_803:
    addstr(&execlist, "-DLANGUAGE_FORTRAN");
    addstr(&execlist, "-D_LANGUAGE_FORTRAN");
    goto block_807;
case 0x73:                                          /* switch 6 */
    addstr(&execlist, "-std0");
    addstr(&execlist, "-DLANGUAGE_ASSEMBLY");
    addstr(&execlist, "-D_LANGUAGE_ASSEMBLY");
    goto block_807;
block_805:
    addstr(&execlist, "-DLANGUAGE_PL1");
    addstr(&execlist, "-D_LANGUAGE_PL1");
    goto block_807;
block_806:
    addstr(&execlist, "-DLANGUAGE_COBOL");
    addstr(&execlist, "-D_LANGUAGE_COBOL");
block_807:
block_808:
    addstr(&execlist, "-D__unix");
    if (sixty4bitflag == 0) {
        goto block_810;
    }
    addstr(&execlist, "-D__64BIT");
block_810:
    temp_t7_8 = ansichoice;
    if (temp_t7_8 == 0) {
        goto block_812;
    }
    if (temp_t7_8 != 3) {
        goto block_814;
    }
block_812:
    if (longlong_emitted != 0) {
        goto block_814;
    }
    addstr(&execlist, "-D_LONGLONG");
    longlong_emitted = 1;
block_814:
    if (dmips_emit != 0) {
        goto block_824;
    }
    if (mips2flag == 0) {
        goto block_820;
    }
    if (call_shared != 0) {
        goto block_818;
    }
    if (default_call_shared == 0) {
        goto block_819;
    }
block_818:
    old_non_shared = 1;
    non_shared = 1;
    default_call_shared = 0;
    call_shared = 0;
block_819:
    addstr(&execlist, "-D__mips=2");
    goto block_823;
block_820:
    if (mips3flag == 0) {
        goto block_822;
    }
    addstr(&execlist, "-D__mips=3");
    goto block_823;
block_822:
    addstr(&execlist, "-D__mips=1");
block_823:
block_824:
    dmips_emit = 1;
    addstr(&execlist, "-D__host_mips");
    if (kpic_flag == 0) {
        goto block_826;
    }
    addstr(&execlist, "-D_PIC");
block_826:
    addstr(&execlist, "-D__DSO__");
    temp_t1_8 = systype;
    if (temp_t1_8 == NULL) {
        goto block_830;
    }
    var_s1_3 = temp_t1_8;
    if ((u8) *var_s1_3 == 0) {
        goto block_831;
    }
loop_828:
    var_s1_3->unk_0 = toupper((u8) var_s1_3->unk_0);
    var_s1_3 += 1;
    if (var_s1_3->unk_1 != 0) {
        goto loop_828;
    }
    goto block_831;
block_830:
    addstr(&execlist, "-D_SYSTYPE_SVR4");
block_831:
    if (Eflag != 0) {
        goto block_847;
    }
    if (Pflag != 0) {
        goto block_847;
    }
    if (include == NULL) {
        goto block_836;
    }
    if (strcmp(comp_target_root, "/") != 0) {
        goto block_837;
    }
    if (systype != NULL) {
        goto block_837;
    }
block_836:
    if (fiveflag == 0) {
        goto block_839;
    }
block_837:
    if (c_compiler_choice != 0) {
        goto block_839;
    }
    addstr(&execlist, "-I");
block_839:
    addlist(&execlist, &cppflags);
    addlist(&execlist, &undefineflags);
    temp_t4_10 = cpp_stdflag;
    if (temp_t4_10 == NULL) {
        goto block_841;
    }
    addstr(&execlist, temp_t4_10);
block_841:
    if (emptyIflag != 0) {
        goto block_847;
    }
    if (abi_flag == 0) {
        goto block_845;
    }
    temp_t2_6 = includeB;
    if (temp_t2_6 == NULL) {
        goto block_845;
    }
    addstr(&execlist, mkstr("-I", temp_t2_6, NULL));
block_845:
    temp_t3_9 = include;
    if (temp_t3_9 == NULL) {
        goto block_847;
    }
    addstr(&execlist, mkstr("-I", temp_t3_9, NULL));
block_847:
    if (Pflag != 0) {
        goto block_849;
    }
    if (Eflag == 0) {
        goto block_858;
    }
block_849:
    if (c_compiler_choice != 0) {
        goto block_858;
    }
    temp_t9_11 = ansichoice;
    if (temp_t9_11 == 1) {
        goto block_852;
    }
    if (temp_t9_11 != 2) {
        goto block_853;
    }
block_852:
    addstr(&execlist, "-std1");
    goto block_857;
block_853:
    if (ansichoice != 3) {
        goto block_855;
    }
    addstr(&execlist, "-std");
    goto block_857;
block_855:
    if (ansichoice != 0) {
        goto block_858;
    }
    addstr(&execlist, "-std0");
block_857:
block_858:
    if (compiler != 1) {
        goto block_880;
    }
    if (c_compiler_choice == 0) {
        goto block_880;
    }
    if (vflag == 0) {
        goto block_862;
    }
    addstr(&execlist, "-v");
block_862:
    if (fullwarn == 0) {
        goto block_864;
    }
    addstr(&execlist, "-Yw");
block_864:
    if (srcfiles.length != 1) {
        goto block_870;
    }
    temp_t6_5 = outfile;
    if (temp_t6_5 == NULL) {
        goto block_867;
    }
    sp118 = temp_t6_5;
    goto block_872;
block_867:
    if (cflag != 0) {
        goto block_869;
    }
    sp118 = "a.out";
    goto block_872;
block_869:
    var_v0_3 = mksuf(srcfiles.entries[var_s0_3], 0x6FU);
    goto block_871;
block_870:
    var_v0_3 = mksuf(srcfiles.entries[var_s0_3], 0x6FU);
block_871:
    sp118 = var_v0_3;
block_872:
    addstr(&execlist, mkstr("-YN", sp118, NULL));
    if (c_compiler_choice == 2) {
        goto block_879;
    }
    if (c_compiler_choice != 3) {
        goto block_875;
    }
    addstr(&execlist, "-YD");
    goto block_878;
block_875:
    if (edison_type != (s8* )3) {
        goto block_877;
    }
    addstr(&execlist, "-K");
    goto block_878;
block_877:
    addstr(&execlist, "-m");
block_878:
block_879:
    addstr(&execlist, passin);
block_880:
    if (Pflag == 0) {
        goto block_885;
    }
    if (compiler != 4) {
        goto block_884;
    }
    if (getsuf(srcfiles.entries[var_s0_3]) != 0) {
        goto block_884;
    }
    passout = mkstr(srcfiles.entries[var_s0_3], ".i", NULL);
    goto block_888;
block_884:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x69U);
    goto block_888;
block_885:
    if (Eflag == 0) {
        goto block_887;
    }
    passout = NULL;
    goto block_888;
block_887:
    passout = tempstr->unk_8;
block_888:
    temp_t0_6 = passout;
    if (temp_t0_6 == NULL) {
        goto block_891;
    }
    if (regular_not_writeable(temp_t0_6) != 1) {
        goto block_891;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
block_891:
    if (oldcflag != 1) {
        goto block_895;
    }
    if (oldcppflag == 0) {
        goto block_894;
    }
    var_v0_4 = run(cpp, execlist.entries, NULL, passout, NULL);
    goto block_898;
block_894:
    var_v0_4 = run(cpp, execlist.entries, NULL, passout, NULL);
    goto block_898;
block_895:
    if (oldcppflag == 0) {
        goto block_897;
    }
    var_v0_4 = run(cpp, execlist.entries, NULL, passout, NULL);
    goto block_898;
block_897:
    var_v0_4 = run(cfe, execlist.entries, NULL, passout, NULL);
block_898:
    retcode = var_v0_4;
    if (retcode == 0) {
        goto block_907;
    }
    runerror += 1;
    if (Eflag != 0) {
        goto block_906;
    }
    temp_t0_7 = (u8) srcsuf;
    if (temp_t0_7 == 0x65) {
        goto block_902;
    }
    if (temp_t0_7 != 0x72) {
        goto block_903;
    }
block_902:
    if (Kflag == 0) {
        goto block_905;
    }
block_903:
    if ((u8) srcsuf != 0x73) {
        goto block_906;
    }
    if (mflag == 0) {
        goto block_906;
    }
block_905:
    unlink(passin);
block_906:
    unlink(passout);
    goto block_2270;
block_907:
    if (Pflag != 0) {
        goto block_2271;
    }
    if (Eflag != 0) {
        goto block_2271;
    }
    temp_t9_12 = (u8) srcsuf;
    if (temp_t9_12 == 0x65) {
        goto block_911;
    }
    if (temp_t9_12 != 0x72) {
        goto block_912;
    }
block_911:
    if (Kflag == 0) {
        goto block_914;
    }
block_912:
    if ((u8) srcsuf != 0x73) {
        goto block_915;
    }
    if (mflag == 0) {
        goto block_915;
    }
block_914:
    unlink(passin);
block_915:
    temp_s3_8 = (u8) srcsuf;
    passin = passout;
    dmips_emit = 0;
    if ((s32) temp_s3_8 < 3) {
        goto block_921;
    }
    if ((s32) temp_s3_8 < 0x47) {
        goto block_919;
    }
    if ((u32) (temp_s3_8 - 0x63) >= 0x11U) {
        goto block_923;
    }
    switch (temp_s3_8);                             /* switch 7; jump table: jtbl_1000B43C */
block_919:
    if (temp_s3_8 == 0x46) {
        goto block_1506;
    }
    goto block_923;
block_921:
    if (temp_s3_8 == 1) {
        goto block_1389;
    }
    if (temp_s3_8 == 2) {
        goto block_1454;
    }
case 0x64:                                          /* switch 7 */
case 0x67:                                          /* switch 7 */
case 0x68:                                          /* switch 7 */
case 0x69:                                          /* switch 7 */
case 0x6A:                                          /* switch 7 */
case 0x6B:                                          /* switch 7 */
case 0x6C:                                          /* switch 7 */
case 0x6D:                                          /* switch 7 */
case 0x6E:                                          /* switch 7 */
case 0x6F:                                          /* switch 7 */
case 0x71:                                          /* switch 7 */
block_923:
    cppchoice = sp114;
    relocate_passes("p", NULL, NULL);
    if (c_compiler_choice != 0) {
        goto block_933;
    }
    if (Pflag != 0) {
        goto block_2271;
    }
    if (Eflag != 0) {
        goto block_2271;
    }
    temp_t9_13 = (u8) srcsuf;
    if (temp_t9_13 == 0x65) {
        goto block_928;
    }
    if (temp_t9_13 != 0x72) {
        goto block_929;
    }
block_928:
    if (Kflag == 0) {
        goto block_931;
    }
block_929:
    if ((u8) srcsuf != 0x73) {
        goto block_932;
    }
    if (mflag == 0) {
        goto block_932;
    }
block_931:
    unlink(passin);
block_932:
    passin = passout;
block_933:
    temp_s3_9 = (u8) srcsuf;
    dmips_emit = 0;
    if ((s32) temp_s3_9 < 7) {
        goto block_939;
    }
    if ((s32) temp_s3_9 < 0x47) {
        goto block_937;
    }
    if ((u32) (temp_s3_9 - 0x63) >= 0x11U) {
        goto block_941;
    }
    switch (temp_s3_9);                             /* switch 8; jump table: jtbl_1000B480 */
block_937:
    if (temp_s3_9 == 0x46) {
        goto block_1506;
    }
    goto block_941;
block_939:
    if (temp_s3_9 == 1) {
        goto block_1389;
    }
    if (temp_s3_9 == 2) {
        goto block_1454;
    }
case 0x1:                                           /* switch 4 */
case 0x63:                                          /* switch 7 */
case 0x63:                                          /* switch 8 */
case 0x64:                                          /* switch 8 */
case 0x67:                                          /* switch 8 */
case 0x68:                                          /* switch 8 */
case 0x69:                                          /* switch 8 */
case 0x6A:                                          /* switch 8 */
case 0x6B:                                          /* switch 8 */
case 0x6C:                                          /* switch 8 */
case 0x6D:                                          /* switch 8 */
case 0x6E:                                          /* switch 8 */
case 0x6F:                                          /* switch 8 */
case 0x71:                                          /* switch 8 */
block_941:
    if (run_sopt == 0) {
        goto block_990;
    }
    if (!(cmp_flag & 1)) {
        goto block_944;
    }
    error(2, NULL, 0, NULL, 0, "-sopt and -pca both specified; -sopt ignored.\n");
    goto block_990;
block_944:
    execlist.length = 0;
    addstr(&execlist, "copt");
    if (Oflag < 2) {
        goto block_947;
    }
    if (set_loop_unroll != 0) {
        goto block_947;
    }
    addstr(&optflags, "-loopunroll");
    addstr(&optflags, "0");
block_947:
    addstr(&execlist, mkstr("-I=", passin, NULL));
    if (Hchar == 0x4B) {
        goto block_949;
    }
    if (Kflag == 0) {
        goto block_950;
    }
block_949:
    var_v0_5 = mksuf(srcfiles.entries[var_s0_3], 0x4DU);
    goto block_951;
block_950:
    var_v0_5 = mkstr(tempstr->unk_7C, "M", NULL);
block_951:
    passout = var_v0_5;
    addstr(&execlist, mkstr("-CMP=", passout, NULL));
    addstr(&execlist, "-cp=i");
    if (ansichoice != 0) {
        goto block_953;
    }
    addstr(&execlist, "-sy=k");
block_953:
    addlist(&execlist, &soptflags);
    if (run(copt, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_961;
    }
    runerror += 1;
    if (docpp == 0) {
        goto block_958;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_958;
    }
    if (Kflag != 0) {
        goto block_958;
    }
    unlink(passin);
block_958:
    if (Hchar != 0x4B) {
        goto block_960;
    }
    if (Kflag == 0) {
        goto block_2271;
    }
block_960:
    unlink(passout);
    goto block_2270;
block_961:
    if (docpp == 0) {
        goto block_965;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_965;
    }
    if (Kflag != 0) {
        goto block_965;
    }
    unlink(passin);
block_965:
    passin = passout;
    if (compchoice != 3) {
        goto block_967;
    }
    if (!(cmp_flag & 0x10000)) {
        goto block_1043;
    }
block_967:
    if (Hchar == 0x4B) {
        goto block_2271;
    }
    if (Hchar == 0x4B) {
        goto block_970;
    }
    if (Kflag == 0) {
        goto block_971;
    }
block_970:
    var_v0_6 = mksuf(srcfiles.entries[var_s0_3], 0x49U);
    goto block_972;
block_971:
    var_v0_6 = mkstr(tempstr->unk_7C, "I", NULL);
block_972:
    passout = var_v0_6;
    if (vflag == 0) {
        goto block_974;
    }
    addstr(&execlist, "-v");
block_974:
    temp_t7_9 = cppchoice;
    execlist.length = 0;
    if (temp_t7_9 == 1) {
        goto block_977;
    }
    if (temp_t7_9 == 3) {
        goto block_977;
    }
    var_s3_5 = "cpp";
    goto block_978;
block_977:
    var_s3_5 = "acpp";
block_978:
    addstr(&execlist, var_s3_5);
    addstr(&execlist, passin);
    if (cppchoice == 2) {
        goto block_980;
    }
    cppchoice = 1;
    goto block_981;
block_980:
    addstr(&execlist, "-l");
block_981:
    if (emptyIflag == 0) {
        goto block_983;
    }
    addstr(&execlist, "-nostdinc");
block_983:
    addlist(&execlist, &cpp2flags);
    relocate_passes("p", NULL, NULL);
    if (run(cpp, execlist.entries, NULL, passout, NULL) == 0) {
        goto block_987;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_986;
    }
    unlink(passin);
block_986:
    unlink(passout);
    goto block_2270;
block_987:
    if (Kflag != 0) {
        goto block_989;
    }
    unlink(passin);
block_989:
    passin = passout;
    goto block_1043;
block_990:
    if (Hchar == 0x4B) {
        goto block_992;
    }
    if (Kflag == 0) {
        goto block_993;
    }
block_992:
    cmp_flag |= 6;
block_993:
    if (!(cmp_flag & 1)) {
        goto block_1043;
    }
    if (Oflag < 2) {
        goto block_997;
    }
    if (set_loop_unroll != 0) {
        goto block_997;
    }
    addstr(&optflags, "-loopunroll");
    addstr(&optflags, "0");
block_997:
    execlist.length = 0;
    addstr(&execlist, "pca");
    addstr(&execlist, mkstr("-I=", passin, NULL));
    if (!(cmp_flag & 4)) {
        goto block_999;
    }
    var_v0_7 = mksuf(srcfiles.entries[var_s0_3], 0x4DU);
    goto block_1000;
block_999:
    var_v0_7 = mkstr(tempstr->unk_7C, "M", NULL);
block_1000:
    passout = var_v0_7;
    addstr(&execlist, mkstr("-CMP=", passout, NULL));
    if (!(cmp_flag & 2)) {
        goto block_1002;
    }
    var_v0_8 = mksuf(srcfiles.entries[var_s0_3], 0x4CU);
    goto block_1003;
block_1002:
    var_v0_8 = mkstr(tempstr->unk_7C, "L", NULL);
block_1003:
    sp110 = var_v0_8;
    addstr(&execlist, mkstr("-L=", sp110, NULL));
    addstr(&execlist, "-lo=ls");
    addstr(&execlist, "-cp=i");
    if (ansichoice != 0) {
        goto block_1005;
    }
    addstr(&execlist, "-sy=k");
block_1005:
    addlist(&execlist, &pcaflags);
    if (run(pca, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_1012;
    }
    runerror += 1;
    if (docpp == 0) {
        goto block_1010;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1010;
    }
    if (Kflag != 0) {
        goto block_1010;
    }
    unlink(passin);
block_1010:
    if (cmp_flag & 4) {
        goto block_2271;
    }
    unlink(passout);
    goto block_2270;
block_1012:
    if (cmp_flag & 2) {
        goto block_1014;
    }
    unlink(sp110);
block_1014:
    if (docpp == 0) {
        goto block_1018;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1018;
    }
    if (Kflag != 0) {
        goto block_1018;
    }
    unlink(passin);
block_1018:
    passin = passout;
    if (Hchar == 0x4B) {
        goto block_2271;
    }
    temp_t2_7 = cppchoice;
    execlist.length = 0;
    if (temp_t2_7 == 1) {
        goto block_1022;
    }
    if (temp_t2_7 == 3) {
        goto block_1022;
    }
    var_s3_6 = "cpp";
    goto block_1023;
block_1022:
    var_s3_6 = "acpp";
block_1023:
    addstr(&execlist, var_s3_6);
    if (Hchar == 0x4B) {
        goto block_1025;
    }
    if (Kflag == 0) {
        goto block_1026;
    }
block_1025:
    var_v0_9 = mksuf(srcfiles.entries[var_s0_3], 0x49U);
    goto block_1027;
block_1026:
    var_v0_9 = mkstr(tempstr->unk_7C, "I", NULL);
block_1027:
    passout = var_v0_9;
    if (vflag == 0) {
        goto block_1029;
    }
    addstr(&execlist, "-v");
block_1029:
    addstr(&execlist, passin);
    if (cppchoice == 2) {
        goto block_1031;
    }
    cppchoice = 1;
    goto block_1032;
block_1031:
    addstr(&execlist, "-l");
block_1032:
    if (emptyIflag == 0) {
        goto block_1034;
    }
    addstr(&execlist, "-nostdinc");
block_1034:
    addlist(&execlist, &cpp2flags);
    addlist(&execlist, &undefineflags);
    relocate_passes("p", NULL, NULL);
    if (run(cpp, execlist.entries, NULL, passout, NULL) == 0) {
        goto block_1039;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_1038;
    }
    if (cmp_flag & 4) {
        goto block_1038;
    }
    unlink(passin);
block_1038:
    unlink(passout);
    goto block_2270;
block_1039:
    if (Kflag != 0) {
        goto block_1042;
    }
    if (cmp_flag & 4) {
        goto block_1042;
    }
    unlink(passin);
block_1042:
    passin = passout;
block_1043:
    if (gflag < 2) {
        goto block_1045;
    }
    func_00431D00(srcfiles.entries[var_s0_3]);
block_1045:
    if (compiler != 1) {
        goto block_1127;
    }
    if (c_compiler_choice == 0) {
        goto block_1127;
    }
    if (docpp == 0) {
        goto block_1052;
    }
    if (oldcppflag != 0) {
        goto block_1052;
    }
    if (run_sopt != 0) {
        goto block_1052;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1052;
    }
    if (acpp == 0) {
        goto block_1053;
    }
block_1052:
    execlist.length = 0;
    addstr(&execlist, cfe);
block_1053:
    if (vflag == 0) {
        goto block_1055;
    }
    addstr(&execlist, "-v");
block_1055:
    if (compiler != 1) {
        goto block_1062;
    }
    temp_t6_6 = c_compiler_choice;
    if (temp_t6_6 == 2) {
        goto block_1058;
    }
    if (temp_t6_6 != 3) {
        goto block_1062;
    }
block_1058:
    if (anachronisms == 0) {
        goto block_1060;
    }
    addstr(&execlist, "-O");
block_1060:
    if (cfront_compatible == 0) {
        goto block_1062;
    }
    addstr(&execlist, "-b");
block_1062:
    if (nocode == 0) {
        goto block_1064;
    }
    addstr(&execlist, "-n");
block_1064:
    if (Fflag != 0) {
        goto block_1066;
    }
    addstr(&execlist, "-Zz");
    addstr(&execlist, "-ZO");
    addstr(&execlist, mkstr("-ZS", symtab, NULL));
block_1066:
    if (compiler != 1) {
        goto block_1073;
    }
    temp_t0_8 = c_compiler_choice;
    if (temp_t0_8 == 2) {
        goto block_1069;
    }
    if (temp_t0_8 != 3) {
        goto block_1073;
    }
block_1069:
    if (Oflag < 3) {
        goto block_1071;
    }
    addstr(&execlist, "-Qz");
block_1071:
    if (non_shared == 0) {
        goto block_1073;
    }
    addstr(&execlist, "-Qn");
block_1073:
    if (signedcharflag == 0) {
        goto block_1075;
    }
    addstr(&execlist, "-s");
    goto block_1076;
block_1075:
    addstr(&execlist, "-u");
block_1076:
    if (fullwarn == 0) {
        goto block_1078;
    }
    addstr(&execlist, "-Yw");
block_1078:
    if (disable_inlines == 0) {
        goto block_1080;
    }
    addstr(&execlist, "-YJ");
block_1080:
    if (c_compiler_choice == 2) {
        goto block_1087;
    }
    if (c_compiler_choice != 3) {
        goto block_1083;
    }
    addstr(&execlist, "-YD");
    goto block_1086;
block_1083:
    if (edison_type != (s8* )3) {
        goto block_1085;
    }
    addstr(&execlist, "-K");
    goto block_1086;
block_1085:
    addstr(&execlist, "-m");
block_1086:
block_1087:
    if ((u8) srcsuf != 0x69) {
        goto block_1089;
    }
    addstr(&execlist, "-Yp");
block_1089:
    if (smart_build == 0) {
        goto block_1091;
    }
    addstr(&execlist, mkstr("-YR", sbrepos, NULL));
block_1091:
    if (srcfiles.length != 1) {
        goto block_1097;
    }
    temp_t3_10 = outfile;
    if (temp_t3_10 == NULL) {
        goto block_1094;
    }
    sp118 = temp_t3_10;
    goto block_1099;
block_1094:
    if (cflag != 0) {
        goto block_1096;
    }
    sp118 = "a.out";
    goto block_1099;
block_1096:
    var_v0_10 = mksuf(srcfiles.entries[var_s0_3], 0x6FU);
    goto block_1098;
block_1097:
    var_v0_10 = mksuf(srcfiles.entries[var_s0_3], 0x6FU);
block_1098:
    sp118 = var_v0_10;
block_1099:
    addstr(&execlist, mkstr("-YN", sp118, NULL));
    if (compiler != 1) {
        goto block_1119;
    }
    temp_t3_11 = c_compiler_choice;
    if (temp_t3_11 == 2) {
        goto block_1102;
    }
    if (temp_t3_11 != 3) {
        goto block_1119;
    }
block_1102:
    temp_s3_10 = default_template_instantiation_mode;
    if (temp_s3_10 == 0) {
        goto block_1109;
    }
    if (temp_s3_10 == 1) {
        goto block_1106;
    }
    if (temp_s3_10 == 2) {
        goto block_1107;
    }
    goto block_1109;
block_1106:
    addstr(&execlist, "-tused");
    goto block_1108;
block_1107:
    addstr(&execlist, "-tall");
block_1108:
block_1109:
    if (no_prelink == 0) {
        goto block_1111;
    }
    addstr(&execlist, "-T");
    goto block_1117;
block_1111:
    temp_t6_7 = outfile;
    if (temp_t6_7 == NULL) {
        goto block_1115;
    }
    if (cflag == 0) {
        goto block_1115;
    }
    if (srcfiles.length != 1) {
        goto block_1115;
    }
    sp10C = temp_t6_7;
    goto block_1116;
block_1115:
    sp10C = mksuf(srcfiles.entries[var_s0_3], 0x6FU);
block_1116:
    sp108 = make_ii_file_name(sp10C);
    addstr(&execlist, mkstr("-YO", sp108, NULL));
    free(sp108);
block_1117:
    if (auto_template_include != 0) {
        goto block_1119;
    }
    addstr(&execlist, "-B");
block_1119:
    if (gflag < 2) {
        goto block_1121;
    }
    addstr(&execlist, mkstr("-Zc", tempstr->unk_84, NULL));
block_1121:
    addstr(&execlist, mkstr("-YG", Gnum, NULL));
    addlist(&execlist, &edisonflags);
    if (dollar_sign == 0) {
        goto block_1123;
    }
    addstr(&execlist, "-$");
block_1123:
    if (Fflag == 0) {
        goto block_1125;
    }
    addstr(&execlist, mkstr("-", NULL));
    goto block_1126;
block_1125:
    addstr(&execlist, passin);
block_1126:
block_1127:
    if (compchoice != 3) {
        goto block_1267;
    }
    temp_t6_8 = cmp_flag;
    if (!(temp_t6_8 & 0x10000)) {
        goto block_1149;
    }
    if (Hchar == 0x4D) {
        goto block_1132;
    }
    if (Kflag != 0) {
        goto block_1132;
    }
    if (!(temp_t6_8 & 4)) {
        goto block_1133;
    }
block_1132:
    var_v0_11 = mksuf(srcfiles.entries[var_s0_3], 0x50U);
    goto block_1134;
block_1133:
    var_v0_11 = mkstr(tempstr->unk_7C, "P", NULL);
block_1134:
    passout = var_v0_11;
    execlist.length = 0;
    addstr(&execlist, mpc);
    addstr(&execlist, passin);
    addstr(&execlist, mkstr("-K", passout, NULL));
    temp_t9_14 = ansichoice;
    if (temp_t9_14 == 1) {
        goto block_1136;
    }
    if (temp_t9_14 != 2) {
        goto block_1137;
    }
block_1136:
    addstr(&execlist, "-ansi");
    goto block_1140;
block_1137:
    if (ansichoice != 0) {
        goto block_1139;
    }
    addstr(&execlist, "-cckr");
    goto block_1140;
block_1139:
    addstr(&execlist, "-xansi");
block_1140:
    addlist(&execlist, &mpcflags);
    retcode = run(mpc, execlist.entries, NULL, NULL, errout);
    if (Kflag != 0) {
        goto block_1142;
    }
    unlink(passin);
block_1142:
    if (retcode == 0) {
        goto block_1147;
    }
    runerror += 1;
    if (Hchar == 0x4D) {
        goto block_2271;
    }
    if (Kflag != 0) {
        goto block_2271;
    }
    if (cmp_flag & 4) {
        goto block_2271;
    }
    unlink(passout);
    goto block_2270;
block_1147:
    if (Hchar == 0x4D) {
        goto block_2271;
    }
    passin = passout;
block_1149:
    if (docpp == 0) {
        goto block_1155;
    }
    if (oldcppflag != 0) {
        goto block_1155;
    }
    if (run_sopt != 0) {
        goto block_1155;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1155;
    }
    if (acpp != 0) {
        goto block_1155;
    }
    if (!(cmp_flag & 0x10000)) {
        goto block_1157;
    }
block_1155:
    if (c_compiler_choice != 0) {
        goto block_1157;
    }
    execlist.length = 0;
    addstr(&execlist, cfe);
    addstr(&execlist, passin);
block_1157:
    if (Hchar != 0x66) {
        goto block_1161;
    }
    if (ucodeflag == 0) {
        goto block_1160;
    }
    passout = tempstr->unk_C;
    goto block_1170;
block_1160:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x42U);
    goto block_1170;
block_1161:
    if (Fflag == 0) {
        goto block_1163;
    }
    if (plusIflag == 0) {
        goto block_1164;
    }
block_1163:
    if (nocode == 0) {
        goto block_1165;
    }
block_1164:
    passout = NULL;
    goto block_1170;
block_1165:
    if (plusIflag == 0) {
        goto block_1167;
    }
    passout = mksuf(srcfiles.entries[var_s0_3], 7U);
    goto block_1170;
block_1167:
    if (Kflag == 0) {
        goto block_1169;
    }
    passout = mksuf(srcfiles.entries[var_s0_3], 0x42U);
    goto block_1170;
block_1169:
    passout = tempstr->unk_C;
block_1170:
    temp_t7_10 = passout;
    if (temp_t7_10 == NULL) {
        goto block_1173;
    }
    if (regular_not_writeable(temp_t7_10) != 1) {
        goto block_1173;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
block_1173:
    if (docpp == 0) {
        goto block_1177;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1177;
    }
    if (acpp != 0) {
        goto block_1177;
    }
    if (oldcppflag == 0) {
        goto block_1185;
    }
block_1177:
    if (run_sopt != 0) {
        goto block_1185;
    }
    if (default_nocpp != 0) {
        goto block_1183;
    }
    temp_t9_15 = (u8) srcsuf;
    if (temp_t9_15 == 0x63) {
        goto block_1182;
    }
    if (temp_t9_15 == 0x73) {
        goto block_1182;
    }
    if (temp_t9_15 != 0x70) {
        goto block_1183;
    }
block_1182:
    addstr(&execlist, "-nocpp");
block_1183:
    if ((u8) srcsuf != var_s0_3) {
        goto block_1185;
    }
    addstr(&execlist, "-nocpp");
block_1185:
    if (c_compiler_choice != 0) {
        goto block_1205;
    }
    if (vflag == 0) {
        goto block_1188;
    }
    addstr(&execlist, "-Xv");
block_1188:
    if (compiler != 1) {
        goto block_1193;
    }
    if (run_sopt != 0) {
        goto block_1192;
    }
    if (cmp_flag & 1) {
        goto block_1192;
    }
    addstr(&execlist, "-D_CFE");
    addstr(&execlist, "-Amachine(mips)");
    addstr(&execlist, "-Asystem(unix)");
    addlist(&execlist, &accomflags);
block_1192:
    addlist(&execlist, &cfeflags);
    addstr(&execlist, "-G");
    addstr(&execlist, Gnum);
block_1193:
    temp_t8_10 = ansichoice;
    if (temp_t8_10 == 1) {
        goto block_1195;
    }
    if (temp_t8_10 != 2) {
        goto block_1196;
    }
block_1195:
    addstr(&execlist, "-std1");
    goto block_1200;
block_1196:
    if (ansichoice != 3) {
        goto block_1198;
    }
    addstr(&execlist, "-std");
    goto block_1200;
block_1198:
    if (ansichoice != 0) {
        goto block_1201;
    }
    addstr(&execlist, "-std0");
block_1200:
block_1201:
    if (prototype_checking_on == 0) {
        goto block_1203;
    }
    addstr(&execlist, "-Xprototypes");
block_1203:
    addstr(&execlist, mkstr("-XS", symtab, NULL));
    addlist(&execlist, &ccomflags);
    if (gflag < 2) {
        goto block_1205;
    }
    addstr(&execlist, mkstr("-Xcmd:", tempstr->unk_84, NULL));
block_1205:
    if (run_sopt != 0) {
        goto block_1207;
    }
    if (!(cmp_flag & 1)) {
        goto block_1208;
    }
block_1207:
    unlink(tempstr->unk_8);
block_1208:
    if (run_sopt == 0) {
        goto block_1210;
    }
    addlist(&execlist, &undefineflags);
block_1210:
    if (Fflag == 0) {
        goto block_1212;
    }
    var_s3_7 = passin;
    goto block_1213;
block_1212:
    var_s3_7 = NULL;
block_1213:
    retcode = run(cfe, execlist.entries, var_s3_7, passout, errout);
    if (smart_build == 0) {
        goto block_1228;
    }
    if (retcode != 0xFA) {
        goto block_1228;
    }
    retcode = 0;
    temp_t6_9 = outfile;
    nocompileneeded = 1;
    if (temp_t6_9 == NULL) {
        goto block_1219;
    }
    if (cflag == 0) {
        goto block_1219;
    }
    if (srcfiles.length != 1) {
        goto block_1219;
    }
    sp104 = temp_t6_9;
    goto block_1224;
block_1219:
    if ((u8) srcsuf != 0x3F) {
        goto block_1223;
    }
    if (Hchar == 0x62) {
        goto block_1223;
    }
    if (Kflag != 0) {
        goto block_1223;
    }
    temp_t7_11 = tempstr->unk_30;
    sp104 = temp_t7_11;
    tmp_uldobj = temp_t7_11;
    goto block_1224;
block_1223:
    sp104 = mksuf(srcfiles.entries[var_s0_3], 0x6FU);
block_1224:
    if (touch(sp118) >= 0) {
        goto block_1226;
    }
    runerror += 1;
block_1226:
    if (srcfiles.length != 1) {
        goto block_1228;
    }
    if (cflag == 0) {
        goto block_2589;
    }
block_1228:
    if (Fflag != 0) {
        goto block_2271;
    }
    if (retcode != 0xFF) {
        goto block_1231;
    }
    c_inline = 1;
    addstr(&umergeflags, "-c_inline");
    goto block_1239;
block_1231:
    if (retcode == 0) {
        goto block_1239;
    }
    runerror += 1;
    if (oldcflag != 1) {
        goto block_1237;
    }
    if (docpp == 0) {
        goto block_1237;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1237;
    }
    if (c_compiler_choice != 0) {
        goto block_1237;
    }
    unlink(passin);
block_1237:
    if (Kflag != 0) {
        goto block_2271;
    }
    unlink(passout);
    unlink(symtab);
    goto block_2270;
block_1239:
    if (run_sopt == 0) {
        goto block_1241;
    }
    if (Kflag == 0) {
        goto block_1244;
    }
block_1241:
    if (acpp != 0) {
        goto block_1244;
    }
    if (oldcppflag != 0) {
        goto block_1244;
    }
    if (!(cmp_flag & 0x10000)) {
        goto block_1245;
    }
block_1244:
    unlink(passin);
block_1245:
    if (NoMoreOptions == 0) {
        goto block_1248;
    }
    temp_t3_12 = passout;
    if ((u8) *temp_t3_12 != 0x2D) {
        goto block_1248;
    }
    passout = func_00433534(temp_t3_12);
block_1248:
    passin = passout;
    if (Hchar != 0x66) {
        goto block_1260;
    }
    if (ucodeflag == 0) {
        goto block_1260;
    }
    execlist.length = 0;
    addstr(&execlist, "btou");
    addstr(&execlist, passin);
    passout = mksuf(srcfiles.entries[var_s0_3], 0x55U);
    temp_t2_8 = passout;
    if (temp_t2_8 == NULL) {
        goto block_1253;
    }
    if (regular_not_writeable(temp_t2_8) != 1) {
        goto block_1253;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
block_1253:
    addstr(&execlist, passout);
    if (run(btou, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_1258;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_1256;
    }
    unlink(passin);
    unlink(passout);
block_1256:
    if (tmpst == 0) {
        goto block_2271;
    }
    unlink(symtab);
    goto block_2270;
block_1258:
    if (Kflag != 0) {
        goto block_2271;
    }
    unlink(passin);
    goto block_2270;
block_1260:
    passin = passout;
    if (Hchar == 0x66) {
        goto block_2271;
    }
    if (compiler != 1) {
        goto block_1730;
    }
    if (c_compiler_choice == 0) {
        goto block_1730;
    }
    if (Eflag != 0) {
        goto block_1266;
    }
    if (nocode != 0) {
        goto block_1266;
    }
    if (nocompileneeded == 0) {
        goto block_1730;
    }
block_1266:
    unlink(passout);
    goto block_2270;
block_1267:
    execlist.length = 0;
    if (ansichoice == 0) {
        goto block_1269;
    }
    var_s3_8 = "accom";
    goto block_1270;
block_1269:
    var_s3_8 = "ccom";
block_1270:
    addstr(&execlist, var_s3_8);
    if (vflag == 0) {
        goto block_1272;
    }
    addstr(&execlist, "-Xv");
block_1272:
    if (!(cmp_flag & 0x10000)) {
        goto block_1274;
    }
    addstr(&execlist, "-XMP");
block_1274:
    addlist(&execlist, &ccomflags);
    if (dollar_sign == 0) {
        goto block_1276;
    }
    addstr(&execlist, "-Xdollar");
block_1276:
    if (use_real_fp == 0) {
        goto block_1278;
    }
    addstr(&execlist, "-Xreal_fp");
block_1278:
    if (prototype_checking_on != 0) {
        goto block_1280;
    }
    if (ansichoice == 0) {
        goto block_1281;
    }
block_1280:
    addstr(&execlist, "-Xprototypes");
block_1281:
    temp_t3_13 = ansichoice;
    if (temp_t3_13 == 0) {
        goto block_1286;
    }
    if (temp_t3_13 != 3) {
        goto block_1284;
    }
    addstr(&execlist, "-Xxansi");
    goto block_1285;
block_1284:
    addstr(&execlist, "-Xansi");
block_1285:
    addlist(&execlist, &accomflags);
block_1286:
    if (Hchar != 0x66) {
        goto block_1290;
    }
    if (ucodeflag == 0) {
        goto block_1289;
    }
    passout = tempstr->unk_C;
    goto block_1293;
block_1289:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x42U);
    goto block_1293;
block_1290:
    if (Kflag == 0) {
        goto block_1292;
    }
    passout = mksuf(srcfiles.entries[var_s0_3], 0x42U);
    goto block_1293;
block_1292:
    passout = tempstr->unk_C;
block_1293:
    if (regular_not_writeable(passout) != 1) {
        goto block_1295;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
block_1295:
    addstr(&execlist, mkstr("-XS", symtab, NULL));
    if (Kflag != 0) {
        goto block_1299;
    }
    if (docpp == 0) {
        goto block_1299;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1299;
    }
    var_s1_4 = passin;
    goto block_1300;
block_1299:
    addstr(&execlist, passin);
    var_s1_4 = NULL;
block_1300:
    retcode = run(ccom, execlist.entries, var_s1_4, passout, errout);
    if (retcode != 0xFF) {
        goto block_1302;
    }
    c_inline = 1;
    addstr(&umergeflags, "-c_inline");
    goto block_1318;
block_1302:
    if (retcode == 0) {
        goto block_1318;
    }
    if (editflag == 0) {
        goto block_1312;
    }
    temp_t4_11 = times_edited;
    if (temp_t4_11 >= edit_cnt_max) {
        goto block_1311;
    }
    times_edited = temp_t4_11 + 1;
    if (edit_src(editor, srcfiles.entries[var_s0_3], 1) == 0) {
        goto block_1307;
    }
    show_err(errout);
    exit(1);
block_1307:
    if (docpp == 0) {
        goto block_1310;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1310;
    }
    unlink(passin);
block_1310:
    unlink(passout);
    unlink(errout);
    unlink(symtab);
    var_at = &passin;
    var_t4 = srcfiles.entries[var_s0_3];
    goto block_484;
block_1311:
    show_err(errout);
block_1312:
    runerror += 1;
    if (Kflag != 0) {
        goto block_1316;
    }
    if (docpp == 0) {
        goto block_1316;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1316;
    }
    unlink(passin);
block_1316:
    if (Kflag != 0) {
        goto block_2271;
    }
    unlink(passout);
    unlink(symtab);
    goto block_2270;
block_1318:
    if (editflag == 0) {
        goto block_1320;
    }
    unlink(errout);
block_1320:
    if (Kflag != 0) {
        goto block_1324;
    }
    if (docpp == 0) {
        goto block_1324;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1324;
    }
    unlink(passin);
block_1324:
    passin = passout;
    if (Hchar != 0x66) {
        goto block_1335;
    }
    if (ucodeflag == 0) {
        goto block_1335;
    }
    execlist.length = 0;
    addstr(&execlist, "btou");
    addstr(&execlist, passin);
    passout = mksuf(srcfiles.entries[var_s0_3], 0x55U);
    if (regular_not_writeable(passout) != 1) {
        goto block_1328;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
block_1328:
    addstr(&execlist, passout);
    if (run(btou, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_1333;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_1331;
    }
    unlink(passin);
    unlink(passout);
block_1331:
    if (tmpst == 0) {
        goto block_2271;
    }
    unlink(symtab);
    goto block_2270;
block_1333:
    if (Kflag != 0) {
        goto block_2271;
    }
    unlink(passin);
    goto block_2270;
block_1335:
    if (Hchar == 0x66) {
        goto block_2271;
    }
    if (compiler != 1) {
        goto block_1730;
    }
    if (c_compiler_choice == 0) {
        goto block_1730;
    }
    if (Eflag != 0) {
        goto block_2271;
    }
    if (nocode != 0) {
        goto block_2271;
    }
    if (nocompileneeded == 0) {
        goto block_1730;
    }
    goto block_2271;
case 0x2:                                           /* switch 4 */
case 0x70:                                          /* switch 7 */
case 0x70:                                          /* switch 8 */
block_1342:
    execlist.length = 0;
    addstr(&execlist, "upas");
    if (vflag == 0) {
        goto block_1344;
    }
    addstr(&execlist, "-v");
block_1344:
    addstr(&execlist, "-G");
    addstr(&execlist, Gnum);
    addlist(&execlist, &upasflags);
    addstr(&execlist, passin);
    if (Hchar != 0x66) {
        goto block_1346;
    }
    if (ucodeflag == 0) {
        goto block_1347;
    }
block_1346:
    if (Kflag == 0) {
        goto block_1349;
    }
block_1347:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x42U);
    if (regular_not_writeable(passout) != 1) {
        goto block_1350;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
    goto block_1350;
block_1349:
    passout = tempstr->unk_C;
block_1350:
    addstr(&execlist, passout);
    addstr(&execlist, "-t");
    addstr(&execlist, symtab);
    if (run(upas, execlist.entries, NULL, NULL, errout) == 0) {
        goto block_1369;
    }
    if (editflag == 0) {
        goto block_1362;
    }
    temp_t6_10 = times_edited;
    if (temp_t6_10 >= edit_cnt_max) {
        goto block_1361;
    }
    times_edited = temp_t6_10 + 1;
    if (edit_src(editor, srcfiles.entries[var_s0_3], 2) == 0) {
        goto block_1355;
    }
    show_err(errout);
    exit(1);
block_1355:
    if (stdflag != 0) {
        goto block_1360;
    }
    if (docpp == 0) {
        goto block_1360;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1360;
    }
    if (Kflag != 0) {
        goto block_1360;
    }
    unlink(passin);
block_1360:
    unlink(passout);
    unlink(errout);
    unlink(symtab);
    passin = srcfiles.entries[var_s0_3];
    goto loop_485;
block_1361:
    show_err(errout);
block_1362:
    runerror += 1;
    if (stdflag != 0) {
        goto block_1367;
    }
    if (docpp == 0) {
        goto block_1367;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1367;
    }
    if (Kflag != 0) {
        goto block_1367;
    }
    unlink(passin);
block_1367:
    if (Kflag != 0) {
        goto block_2271;
    }
    unlink(passout);
    unlink(symtab);
    goto block_2270;
block_1369:
    if (editflag == 0) {
        goto block_1371;
    }
    unlink(errout);
block_1371:
    if (stdflag != 0) {
        goto block_1376;
    }
    if (docpp == 0) {
        goto block_1376;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1376;
    }
    if (Kflag != 0) {
        goto block_1376;
    }
    unlink(passin);
block_1376:
    passin = passout;
    if (Hchar != 0x66) {
        goto block_1387;
    }
    if (ucodeflag == 0) {
        goto block_1387;
    }
    execlist.length = 0;
    addstr(&execlist, "btou");
    addstr(&execlist, passin);
    passout = mksuf(srcfiles.entries[var_s0_3], 0x55U);
    if (regular_not_writeable(passout) != 1) {
        goto block_1380;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
block_1380:
    addstr(&execlist, passout);
    if (run(btou, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_1385;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_1383;
    }
    unlink(passin);
    unlink(passout);
block_1383:
    if (tmpst == 0) {
        goto block_2271;
    }
    unlink(symtab);
    goto block_2270;
block_1385:
    if (Kflag != 0) {
        goto block_2271;
    }
    unlink(passin);
    goto block_2270;
block_1387:
    if (Hchar != 0x66) {
        goto block_1730;
    }
    goto block_2271;
case 0x5:                                           /* switch 4 */
block_1389:
    execlist.length = 0;
    addstr(&execlist, "pl1fe");
    if (vflag == 0) {
        goto block_1391;
    }
    addstr(&execlist, "-v");
block_1391:
    addlist(&execlist, &upl1flags);
    addstr(&execlist, passin);
    if (Hchar == 0x66) {
        goto block_1393;
    }
    if (Kflag == 0) {
        goto block_1394;
    }
block_1393:
    passout = mksuf(srcfiles.entries[var_s0_3], 3U);
    lpi_st = mksuf(srcfiles.entries[var_s0_3], 4U);
    goto block_1395;
block_1394:
    passout = tempstr->unk_40;
    lpi_st = tempstr->unk_44;
block_1395:
    lpi_p1 = tempstr->unk_48;
    addstr(&execlist, "-o");
    addstr(&execlist, passout);
    addstr(&execlist, "-s");
    addstr(&execlist, lpi_st);
    addstr(&execlist, "-p");
    addstr(&execlist, lpi_p1);
    addstr(&execlist, "-e");
    addstr(&execlist, pl1err);
    if (run(upl1, execlist.entries, NULL, errout, NULL) == 0) {
        goto block_1411;
    }
    if (editflag == 0) {
        goto block_1405;
    }
    temp_t7_12 = times_edited;
    if (temp_t7_12 >= edit_cnt_max) {
        goto block_1404;
    }
    times_edited = temp_t7_12 + 1;
    if (edit_src(editor, srcfiles.entries[var_s0_3], 5) == 0) {
        goto block_1400;
    }
    show_err(errout);
    exit(1);
block_1400:
    if (docpp == 0) {
        goto block_1403;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1403;
    }
    unlink(passin);
block_1403:
    unlink(passout);
    unlink(errout);
    unlink(lpi_st);
    unlink(lpi_p1);
    passin = srcfiles.entries[var_s0_3];
    goto loop_485;
block_1404:
    show_err(errout);
block_1405:
    runerror += 1;
    if (docpp == 0) {
        goto block_1408;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1408;
    }
    unlink(passin);
block_1408:
    if (Kflag != 0) {
        goto block_1410;
    }
    unlink(passout);
    unlink(lpi_st);
block_1410:
    unlink(lpi_p1);
    goto block_2270;
block_1411:
    if (editflag == 0) {
        goto block_1413;
    }
    unlink(errout);
block_1413:
    unlink(lpi_p1);
    if (docpp == 0) {
        goto block_1416;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1416;
    }
    unlink(passin);
block_1416:
    if (Hchar == 0x66) {
        goto block_2271;
    }
    passin = passout;
block_1418:
    execlist.length = 0;
    addstr(&execlist, "ulpi");
    if (vflag == 0) {
        goto block_1420;
    }
    addstr(&execlist, "-v");
block_1420:
    addlist(&execlist, &ulpiflags);
    addstr(&execlist, passin);
    if (Hchar != 0x6B) {
        goto block_1422;
    }
    if (ucodeflag == 0) {
        goto block_1423;
    }
block_1422:
    if (Kflag == 0) {
        goto block_1424;
    }
block_1423:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x42U);
    goto block_1425;
block_1424:
    passout = tempstr->unk_C;
block_1425:
    if ((u8) srcsuf == 3) {
        goto block_1427;
    }
    if (Kflag == 0) {
        goto block_1428;
    }
block_1427:
    lpi_st = mksuf(srcfiles.entries[var_s0_3], 4U);
    goto block_1429;
block_1428:
    lpi_st = tempstr->unk_44;
block_1429:
    addstr(&execlist, "-s");
    addstr(&execlist, lpi_st);
    addstr(&execlist, "-o");
    addstr(&execlist, passout);
    addstr(&execlist, "-t");
    addstr(&execlist, symtab);
    if (run(ulpi, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_1437;
    }
    runerror += 1;
    if ((u8) srcsuf == 3) {
        goto block_1432;
    }
    unlink(passin);
block_1432:
    if (Kflag != 0) {
        goto block_1435;
    }
    unlink(passout);
    if ((u8) srcsuf == 3) {
        goto block_1435;
    }
    unlink(lpi_st);
block_1435:
    if (tmpst == 0) {
        goto block_2271;
    }
    unlink(symtab);
    goto block_2270;
block_1437:
    if ((u8) srcsuf == 3) {
        goto block_1440;
    }
    if (Kflag != 0) {
        goto block_1440;
    }
    unlink(passin);
block_1440:
    if (Kflag != 0) {
        goto block_1443;
    }
    if ((u8) srcsuf == 3) {
        goto block_1443;
    }
    unlink(lpi_st);
block_1443:
    passin = passout;
    if (Hchar != 0x6B) {
        goto block_1452;
    }
    if (ucodeflag == 0) {
        goto block_1452;
    }
    execlist.length = 0;
    addstr(&execlist, "btou");
    addstr(&execlist, passin);
    passout = mksuf(srcfiles.entries[var_s0_3], 0x55U);
    addstr(&execlist, passout);
    if (run(btou, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_1450;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_1448;
    }
    unlink(passin);
    unlink(passout);
block_1448:
    if (tmpst == 0) {
        goto block_2271;
    }
    unlink(symtab);
    goto block_2270;
block_1450:
    if (Kflag != 0) {
        goto block_2271;
    }
    unlink(passin);
    goto block_2270;
block_1452:
    if (Hchar != 0x6B) {
        goto block_1730;
    }
    goto block_2271;
case 0x6:                                           /* switch 4 */
block_1454:
    execlist.length = 0;
    addstr(&execlist, "cobfe");
    if (vflag == 0) {
        goto block_1456;
    }
    addstr(&execlist, "-v");
block_1456:
    addlist(&execlist, &ucobflags);
    addstr(&execlist, passin);
    if (Hchar == 0x66) {
        goto block_1458;
    }
    if (Kflag == 0) {
        goto block_1459;
    }
block_1458:
    passout = mksuf(srcfiles.entries[var_s0_3], 3U);
    lpi_st = mksuf(srcfiles.entries[var_s0_3], 4U);
    goto block_1460;
block_1459:
    passout = tempstr->unk_40;
    lpi_st = tempstr->unk_44;
block_1460:
    lpi_p1 = tempstr->unk_48;
    lpi_pd = tempstr->unk_50;
    lpi_dd = tempstr->unk_4C;
    addstr(&execlist, "-o");
    addstr(&execlist, passout);
    addstr(&execlist, "-s");
    addstr(&execlist, lpi_st);
    addstr(&execlist, "-p");
    addstr(&execlist, lpi_p1);
    addstr(&execlist, "-pd");
    addstr(&execlist, lpi_pd);
    addstr(&execlist, "-dd");
    addstr(&execlist, lpi_dd);
    addstr(&execlist, "-e");
    addstr(&execlist, pl1err);
    if (run(ucob, execlist.entries, NULL, errout, NULL) == 0) {
        goto block_1476;
    }
    if (editflag == 0) {
        goto block_1470;
    }
    temp_t3_14 = times_edited;
    if (temp_t3_14 >= edit_cnt_max) {
        goto block_1469;
    }
    times_edited = temp_t3_14 + 1;
    if (edit_src(editor, srcfiles.entries[var_s0_3], 6) == 0) {
        goto block_1465;
    }
    show_err(errout);
    exit(1);
block_1465:
    if (docpp == 0) {
        goto block_1468;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1468;
    }
    unlink(passin);
block_1468:
    unlink(passout);
    unlink(errout);
    unlink(lpi_st);
    unlink(lpi_p1);
    unlink(lpi_pd);
    unlink(lpi_dd);
    passin = srcfiles.entries[var_s0_3];
    goto loop_485;
block_1469:
    show_err(errout);
block_1470:
    runerror += 1;
    if (docpp == 0) {
        goto block_1473;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1473;
    }
    unlink(passin);
block_1473:
    if (Kflag != 0) {
        goto block_1475;
    }
    unlink(passout);
    unlink(lpi_st);
block_1475:
    unlink(lpi_p1);
    unlink(lpi_pd);
    unlink(lpi_dd);
    goto block_2270;
block_1476:
    if (editflag == 0) {
        goto block_1478;
    }
    unlink(errout);
block_1478:
    if (docpp == 0) {
        goto block_1481;
    }
    if ((u8) srcsuf == 0x69) {
        goto block_1481;
    }
    unlink(passin);
block_1481:
    unlink(lpi_p1);
    unlink(lpi_pd);
    unlink(lpi_dd);
    if (Hchar == 0x66) {
        goto block_2271;
    }
    passin = passout;
    goto block_1418;
case 0x65:                                          /* switch 3 */
case 0x72:                                          /* switch 3 */
case 0x73:                                          /* switch 3 */
    if (mflag == 0) {
        goto block_1492;
    }
    execlist.length = 0;
    addstr(&execlist, "m4");
    addstr(&execlist, passin);
    if (compiler == 4) {
        goto block_1486;
    }
    if ((u8) srcsuf != 0x73) {
        goto block_1487;
    }
block_1486:
    passout = tempstr->unk_38;
    goto block_1488;
block_1487:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x70U);
block_1488:
    if (run(m4, execlist.entries, NULL, passout, NULL) == 0) {
        goto block_1491;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_2271;
    }
    unlink(passout);
    goto block_2270;
block_1491:
    passin = passout;
block_1492:
    temp_s3_11 = (u8) srcsuf;
    if (temp_s3_11 == 0x65) {
        goto block_1498;
    }
    if (temp_s3_11 == 0x72) {
        goto block_1499;
    }
    if (temp_s3_11 != 0x73) {
        goto block_1498;
    }
    if (docpp != 0) {
        goto block_532;
    }
    if (default_nocpp == 0) {
        goto block_2131;
    }
    goto block_532;
block_1498:
    error(1, NULL, 0, NULL, 0, "efl not supported. Cannot use .e files\n");
    exit(2);
block_1499:
    execlist.length = 0;
    addstr(&execlist, "ratfor");
    addlist(&execlist, &ratforflags);
    addstr(&execlist, passin);
    passout = mksuf(srcfiles.entries[var_s0_3], 0x66U);
    if (run(ratfor, execlist.entries, NULL, passout, NULL) == 0) {
        goto block_1502;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_2271;
    }
    goto block_2271;
block_1502:
    if (mflag == 0) {
        goto block_1504;
    }
    unlink(passin);
block_1504:
    passin = passout;
    if (Fflag != 0) {
        goto block_2271;
    }
    if (docpp != 0) {
        goto block_532;
    }
case 0x3:                                           /* switch 4 */
case 0x65:                                          /* switch 7 */
case 0x66:                                          /* switch 7 */
case 0x72:                                          /* switch 7 */
case 0x65:                                          /* switch 8 */
case 0x66:                                          /* switch 8 */
case 0x72:                                          /* switch 8 */
block_1506:
    sp100 = 0;
    spFC = 0;
    spF0.unk_0 = 0x31;
    spF0.unk_1 = 0;
    if (run_sopt == 0) {
        goto block_1567;
    }
    if (!(mp_flag & 1)) {
        goto block_1509;
    }
    error(2, NULL, 0, NULL, 0, "-sopt and -pfa both specified; -sopt ignored.\n");
    goto block_1567;
block_1509:
    if (Oflag < 2) {
        goto block_1512;
    }
    if (set_loop_unroll != 0) {
        goto block_1512;
    }
    addstr(&optflags, "-loopunroll");
    addstr(&optflags, "0");
block_1512:
    if (mp_i2flag == 0) {
        goto block_1515;
    }
    if (w1flag == 2) {
        goto block_1515;
    }
    error(2, NULL, 0, NULL, 0, "fopt does not recognize the -i2 option\n");
block_1515:
    if (mp_66flag == 0) {
        goto block_1518;
    }
    if (w1flag == 2) {
        goto block_1518;
    }
    error(2, NULL, 0, NULL, 0, "fopt does not recognize the -66 option\n");
block_1518:
    if (mp_uflag == 0) {
        goto block_1521;
    }
    if (w1flag == 2) {
        goto block_1521;
    }
    error(2, NULL, 0, NULL, 0, "fopt does not recognize the -u option\n");
block_1521:
    if (mp_backslashflag == 0) {
        goto block_1524;
    }
    if (w1flag == 2) {
        goto block_1524;
    }
    error(2, NULL, 0, NULL, 0, "fopt does not support the -backslash option\n");
block_1524:
    if (mp_caseflag == 0) {
        goto block_1526;
    }
    error(1, NULL, 0, NULL, 0, "fopt does not support the -U option\n");
    exit(2);
block_1526:
    execlist.length = 0;
    addstr(&execlist, "fopt");
    spF4 = mkstr(tempstr->unk_7C, "l", NULL);
    addstr(&execlist, mkstr("-L=", spF4, NULL));
    if (Hchar == 0x4B) {
        goto block_1528;
    }
    if (Kflag == 0) {
        goto block_1529;
    }
block_1528:
    var_v0_12 = mksuf(srcfiles.entries[var_s0_3], 0x6DU);
    goto block_1530;
block_1529:
    var_v0_12 = mkstr(tempstr->unk_7C, "m", &spF0, NULL);
block_1530:
    passout = var_v0_12;
    addstr(&execlist, mkstr("-F=", passout, NULL));
    addstr(&execlist, mkstr("-I=", passin, NULL));
    if (mp_col120flag == 0) {
        goto block_1532;
    }
    addstr(&execlist, "-scan=120");
block_1532:
    if (mp_extendflag == 0) {
        goto block_1534;
    }
    addstr(&execlist, "-scan=132");
block_1534:
    if (automaticflag != 0) {
        goto block_1536;
    }
    addstr(&execlist, "-save=all");
block_1536:
    if (mp_onetripflag == 0) {
        goto block_1538;
    }
    addstr(&execlist, "-onetrip");
block_1538:
    if (mp_dlinesflag == 0) {
        goto block_1540;
    }
    addstr(&execlist, "-dlines");
block_1540:
    if (w1flag != 2) {
        goto block_1542;
    }
    addstr(&execlist, "-suppress=w");
block_1542:
    if (vflag == 0) {
        goto block_1544;
    }
    addstr(&execlist, "-lo=lno");
block_1544:
    if (irix4 == 0) {
        goto block_1546;
    }
    addstr(&execlist, mkstr("-customer=", mksuf(srcfiles.entries[var_s0_3], (u8) srcsuf), NULL));
    goto block_1547;
block_1546:
    addstr(&execlist, mkstr("-original_filename=", mksuf(srcfiles.entries[var_s0_3], (u8) srcsuf), NULL));
block_1547:
    addstr(&execlist, "-include=/usr/include");
    addstr(&execlist, "-cp=i");
    addlist(&execlist, &soptflags);
    if (run(fopt, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_1558;
    }
    runerror += 1;
    if (docpp != 0) {
        goto block_1551;
    }
    temp_t7_13 = (u8) srcsuf;
    if (temp_t7_13 == 0x65) {
        goto block_1551;
    }
    if (temp_t7_13 != 0x72) {
        goto block_1554;
    }
block_1551:
    if ((u8) srcsuf == 0x69) {
        goto block_1554;
    }
    if (Kflag != 0) {
        goto block_1554;
    }
    unlink(passin);
block_1554:
    if (Hchar != 0x4B) {
        goto block_1556;
    }
    if (Kflag == 0) {
        goto block_1557;
    }
block_1556:
    unlink(passout);
block_1557:
    unlink(spF4);
    goto block_2270;
block_1558:
    if (docpp != 0) {
        goto block_1562;
    }
    temp_t5_6 = (u8) srcsuf;
    if (temp_t5_6 == 0x65) {
        goto block_1562;
    }
    if (temp_t5_6 == 0x72) {
        goto block_1562;
    }
    if (temp_t5_6 != 0x46) {
        goto block_1565;
    }
block_1562:
    if ((u8) srcsuf == 0x69) {
        goto block_1565;
    }
    if (Kflag != 0) {
        goto block_1565;
    }
    unlink(passin);
block_1565:
    unlink(spF4);
    passin = passout;
    if (Hchar != 0x4B) {
        goto block_1661;
    }
    goto block_2271;
block_1567:
    if (Hchar == 0x4B) {
        goto block_1569;
    }
    if (Kflag == 0) {
        goto block_1570;
    }
block_1569:
    mp_flag |= 6;
block_1570:
    if (!(mp_flag & 1)) {
        goto block_1661;
    }
    if (Oflag < 2) {
        goto block_1574;
    }
    if (set_loop_unroll != 0) {
        goto block_1574;
    }
    addstr(&optflags, "-loopunroll");
    addstr(&optflags, "0");
block_1574:
    if (mp_i2flag == 0) {
        goto block_1577;
    }
    if (w1flag == 2) {
        goto block_1577;
    }
    error(2, NULL, 0, NULL, 0, "PFA does not recognize the -i2 option\n");
block_1577:
    if (mp_66flag == 0) {
        goto block_1580;
    }
    if (w1flag == 2) {
        goto block_1580;
    }
    error(2, NULL, 0, NULL, 0, "PFA does not recognize the -66 option\n");
block_1580:
    if (mp_uflag == 0) {
        goto block_1583;
    }
    if (w1flag == 2) {
        goto block_1583;
    }
    error(2, NULL, 0, NULL, 0, "PFA does not recognize the -u option\n");
block_1583:
    if (mp_backslashflag == 0) {
        goto block_1586;
    }
    if (w1flag == 2) {
        goto block_1586;
    }
    error(2, NULL, 0, NULL, 0, "PFA does not support the -backslash option\n");
block_1586:
    if (mp_caseflag == 0) {
        goto loop_1588;
    }
    error(1, NULL, 0, NULL, 0, "PFA does not support the -U option\n");
    exit(2);
loop_1588:
    execlist.length = 0;
    addstr(&execlist, "pfa");
    spF0.unk_0 = spFC + 0x31;
    if (!(mp_flag & 2)) {
        goto block_1591;
    }
    spF8 = mksuf(srcfiles.entries[var_s0_3], 0x6CU);
    if (spFC >= mp_prepass_count) {
        goto block_1593;
    }
    var_v0_13 = mkstr(spF8, &spF0, NULL);
    goto block_1592;
block_1591:
    var_v0_13 = mkstr(tempstr->unk_7C, "l", &spF0, NULL);
block_1592:
    spF8 = var_v0_13;
block_1593:
    addstr(&execlist, mkstr("-L=", spF8, NULL));
    if (!(mp_flag & 4)) {
        goto block_1596;
    }
    passout = mksuf(srcfiles.entries[var_s0_3], 0x6DU);
    if (spFC >= mp_prepass_count) {
        goto block_1598;
    }
    var_v0_14 = mkstr(passout, &spF0, NULL);
    goto block_1597;
block_1596:
    var_v0_14 = mkstr(tempstr->unk_7C, "m", &spF0, NULL);
block_1597:
    passout = var_v0_14;
block_1598:
    addstr(&execlist, mkstr("-F=", passout, NULL));
    addstr(&execlist, mkstr("-I=", passin, NULL));
    if (mp_col120flag == 0) {
        goto block_1600;
    }
    addstr(&execlist, "-scan=120");
block_1600:
    if (mp_extendflag == 0) {
        goto block_1602;
    }
    addstr(&execlist, "-scan=132");
block_1602:
    if (automaticflag != 0) {
        goto block_1604;
    }
    addstr(&execlist, "-save=all");
block_1604:
    if (mp_onetripflag == 0) {
        goto block_1606;
    }
    addstr(&execlist, "-onetrip");
block_1606:
    if (mp_dlinesflag == 0) {
        goto block_1608;
    }
    addstr(&execlist, "-dlines");
block_1608:
    if (w1flag != 2) {
        goto block_1610;
    }
    addstr(&execlist, "-suppress=w");
block_1610:
    if (vflag == 0) {
        goto block_1612;
    }
    addstr(&execlist, "-lo=lno");
    goto block_1613;
block_1612:
    addstr(&execlist, "-lo=lo");
block_1613:
    if (!(mp_flag & 2)) {
        goto block_1615;
    }
    addstr(&execlist, mkstr("-analysis=", mksuf(srcfiles.entries[var_s0_3], 5U), NULL));
    goto block_1617;
block_1615:
    if (irix4 != 0) {
        goto block_1618;
    }
    addstr(&execlist, "-noanalysis");
block_1617:
block_1618:
    if (irix4 == 0) {
        goto block_1620;
    }
    addstr(&execlist, mkstr("-customer=", mksuf(srcfiles.entries[var_s0_3], (u8) srcsuf), NULL));
    goto block_1621;
block_1620:
    addstr(&execlist, mkstr("-original_filename=", mksuf(srcfiles.entries[var_s0_3], (u8) srcsuf), NULL));
block_1621:
    addstr(&execlist, "-include=/usr/include");
    addstr(&execlist, "-cp=i");
    if (spFC < mp_prepass_count) {
        goto block_1623;
    }
    addlist(&execlist, &pfaflags);
    goto block_1636;
block_1623:
    addstr(&execlist, "-p=1");
    addstr(&execlist, "-ur=1");
    temp_t6_11 = sp100 + 1;
    sp100 = temp_t6_11;
    if (strncmp(arg1[temp_t6_11], "-pfaprepass,", 0xCU) == 0) {
        goto block_1627;
    }
loop_1624:
    temp_t7_14 = sp100 + 1;
    sp100 = temp_t7_14;
    if (arg1[temp_t7_14] != NULL) {
        goto block_1626;
    }
    error(1, NULL, 0, NULL, 0, "Can't parse -pfaprepass option\n");
    exit(2);
block_1626:
    if (strncmp(arg1[sp100], "-pfaprepass,", 0xCU) != 0) {
        goto loop_1624;
    }
block_1627:
    spE8 = &arg1[sp100][strlen("-pfaprepass")];
loop_1628:
    spEC = spE8 + 1;
    if (spE8->unk_1 != 0) {
        goto block_1630;
    }
    error(1, NULL, 0, NULL, 0, "Bad pfaprepass syntax: no arg after comma\n");
    exit(2);
block_1630:
    spE8 = spEC + 1;
    temp_t8_11 = spEC->unk_1;
    if (temp_t8_11 == 0x2C) {
        goto block_1634;
    }
    if (temp_t8_11 == 0) {
        goto block_1634;
    }
loop_1632:
    spE8 += 1;
    temp_t5_7 = (u8) spE8->unk_0;
    if (temp_t5_7 == 0x2C) {
        goto block_1634;
    }
    if (temp_t5_7 != 0) {
        goto loop_1632;
    }
block_1634:
    spE7 = (u8) spE8->unk_0;
    spE8->unk_0 = 0;
    addstr(&execlist, mkstr(spEC, NULL));
    if (spE7 == 0) {
        goto block_1636;
    }
    spE8->unk_0 = (s8) spE7;
    goto loop_1628;
block_1636:
    if (run(pfa, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_1645;
    }
    runerror += 1;
    if (docpp != 0) {
        goto block_1640;
    }
    temp_t6_12 = (u8) srcsuf;
    if (temp_t6_12 == 0x65) {
        goto block_1640;
    }
    if (temp_t6_12 != 0x72) {
        goto block_1643;
    }
block_1640:
    if ((u8) srcsuf == 0x69) {
        goto block_1643;
    }
    if (Kflag != 0) {
        goto block_1643;
    }
    unlink(passin);
block_1643:
    if (mp_flag & 4) {
        goto block_2271;
    }
    unlink(passout);
    goto block_2270;
block_1645:
    if (mp_flag & 2) {
        goto block_1647;
    }
    unlink(spF8);
block_1647:
    if (spFC != 0) {
        goto block_1655;
    }
    if (docpp != 0) {
        goto block_1652;
    }
    temp_t2_9 = (u8) srcsuf;
    if (temp_t2_9 == 0x65) {
        goto block_1652;
    }
    if (temp_t2_9 == 0x72) {
        goto block_1652;
    }
    if (temp_t2_9 != 0x46) {
        goto block_1658;
    }
block_1652:
    if ((u8) srcsuf == 0x69) {
        goto block_1658;
    }
    if (Kflag != 0) {
        goto block_1658;
    }
    unlink(passin);
    goto block_1657;
block_1655:
    if (mp_flag & 4) {
        goto block_1658;
    }
    unlink(passin);
block_1657:
block_1658:
    temp_t7_15 = spFC + 1;
    spFC = temp_t7_15;
    if (mp_prepass_count < temp_t7_15) {
        goto block_1660;
    }
    passin = passout;
    goto loop_1588;
block_1660:
    passin = passout;
    if (Hchar == 0x4B) {
        goto block_2271;
    }
block_1661:
    execlist.length = 0;
    addstr(&execlist, "fcom");
    temp_t6_13 = alignarg;
    if (temp_t6_13 == NULL) {
        goto block_1663;
    }
    addstr(&execlist, temp_t6_13);
block_1663:
    if (align_common <= 0) {
        goto block_1665;
    }
    addstr(&execlist, "-align_common");
block_1665:
    if (!(mp_flag & 0x10000)) {
        goto block_1667;
    }
    addstr(&execlist, "-MP");
block_1667:
    if (showdirt_flag == 0) {
        goto block_1669;
    }
    addstr(&execlist, "-showdirt");
block_1669:
    if (vflag == 0) {
        goto block_1671;
    }
    addstr(&execlist, "-v");
block_1671:
    addlist(&execlist, &fcomflags);
    if (nocode != 0) {
        goto block_1673;
    }
    addstr(&execlist, mkstr("-XS", symtab, NULL));
block_1673:
    var_s2 = NULL;
    if (nocode == 0) {
        goto block_1675;
    }
    addstr(&execlist, "-nocode");
    passout = NULL;
    goto block_1682;
block_1675:
    if (Hchar != 0x66) {
        goto block_1678;
    }
    passout = mksuf(srcfiles.entries[var_s0_3], 0x42U);
    if (ucodeflag == 0) {
        goto block_1682;
    }
    addstr(&execlist, "-Xu");
    var_s2 = mksuf(srcfiles.entries[var_s0_3], 0x55U);
    goto block_1682;
block_1678:
    if (Kflag == 0) {
        goto block_1681;
    }
    passout = mksuf(srcfiles.entries[var_s0_3], 0x42U);
    if (regular_not_writeable(passout) != 1) {
        goto block_1682;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
    goto block_1682;
block_1681:
    passout = tempstr->unk_C;
block_1682:
    if (passout == NULL) {
        goto block_1684;
    }
    addstr(&execlist, "-t");
    addstr(&execlist, passout);
block_1684:
    if (docpp == 0) {
        goto block_1688;
    }
    temp_t7_16 = (u8) srcsuf;
    if (temp_t7_16 == 0x69) {
        goto block_1688;
    }
    if (temp_t7_16 == 0x6D) {
        goto block_1688;
    }
    var_s1_5 = passin;
    goto block_1689;
block_1688:
    addstr(&execlist, passin);
    var_s1_5 = NULL;
block_1689:
    if (run(fcom, execlist.entries, var_s1_5, var_s2, errout) == 0) {
        goto block_1713;
    }
    if (editflag == 0) {
        goto block_1702;
    }
    temp_t2_10 = times_edited;
    if (temp_t2_10 >= edit_cnt_max) {
        goto block_1701;
    }
    times_edited = temp_t2_10 + 1;
    if (edit_src(editor, srcfiles.entries[var_s0_3], 3) == 0) {
        goto block_1694;
    }
    show_err(errout);
    exit(1);
block_1694:
    if (docpp != 0) {
        goto block_1697;
    }
    temp_t7_17 = (u8) srcsuf;
    if (temp_t7_17 == 0x65) {
        goto block_1697;
    }
    if (temp_t7_17 != 0x72) {
        goto block_1700;
    }
block_1697:
    temp_t8_12 = (u8) srcsuf;
    if (temp_t8_12 == 0x69) {
        goto block_1700;
    }
    if (temp_t8_12 == 0x66) {
        goto block_1700;
    }
    unlink(passin);
block_1700:
    unlink(passout);
    unlink(errout);
    unlink(symtab);
    passin = srcfiles.entries[var_s0_3];
    goto loop_485;
block_1701:
    show_err(errout);
block_1702:
    runerror += 1;
    if (docpp != 0) {
        goto block_1706;
    }
    if (mp_flag & 1) {
        goto block_1706;
    }
    temp_t8_13 = (u8) srcsuf;
    if (temp_t8_13 == 0x65) {
        goto block_1706;
    }
    if (temp_t8_13 != 0x72) {
        goto block_1711;
    }
block_1706:
    temp_t4_12 = (u8) srcsuf;
    if (temp_t4_12 == 0x69) {
        goto block_1711;
    }
    if (temp_t4_12 == 0x6D) {
        goto block_1711;
    }
    if (Kflag != 0) {
        goto block_1711;
    }
    if (mp_flag & 4) {
        goto block_1711;
    }
    unlink(passin);
block_1711:
    if (Kflag != 0) {
        goto block_2271;
    }
    unlink(passout);
    unlink(symtab);
    goto block_2270;
block_1713:
    if (editflag == 0) {
        goto block_1715;
    }
    unlink(errout);
block_1715:
    if (nocode == 0) {
        goto block_1718;
    }
    if (docpp == 0) {
        goto block_2271;
    }
    unlink(passin);
    goto block_2270;
block_1718:
    if (docpp != 0) {
        goto block_1724;
    }
    if (mp_flag & 1) {
        goto block_1724;
    }
    if (run_sopt != 0) {
        goto block_1724;
    }
    temp_t2_11 = (u8) srcsuf;
    if (temp_t2_11 == 0x65) {
        goto block_1724;
    }
    if (temp_t2_11 == 0x72) {
        goto block_1724;
    }
    if (temp_t2_11 != 0x46) {
        goto block_1729;
    }
block_1724:
    temp_t5_8 = (u8) srcsuf;
    if (temp_t5_8 == 0x69) {
        goto block_1729;
    }
    if (temp_t5_8 == 0x6D) {
        goto block_1729;
    }
    if (Kflag != 0) {
        goto block_1729;
    }
    if (mp_flag & 4) {
        goto block_1729;
    }
    unlink(passin);
block_1729:
    passin = passout;
    if (Hchar == 0x66) {
        goto block_2271;
    }
case 0x42:                                          /* switch 3 */
block_1730:
    temp_t8_14 = Oflag;
    if (temp_t8_14 == 3) {
        goto block_1735;
    }
    if (temp_t8_14 == 4) {
        goto block_1735;
    }
    if (jflag != 0) {
        goto block_1735;
    }
    if (c_inline != 0) {
        goto block_1914;
    }
    goto block_1934;
block_1735:
    execlist.length = 0;
    addstr(&execlist, "ujoin");
    if (vflag == 0) {
        goto block_1737;
    }
    addstr(&execlist, "-v");
block_1737:
    addlist(&execlist, &ujoinflags);
    temp_t5_9 = outfile;
    if (temp_t5_9 == NULL) {
        goto block_1741;
    }
    if (jflag == 0) {
        goto block_1741;
    }
    if (srcfiles.length != 1) {
        goto block_1741;
    }
    passout = temp_t5_9;
    goto block_1742;
block_1741:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x75U);
block_1742:
    addstr(&execlist, "-o");
    addstr(&execlist, passout);
    addstr(&execlist, passin);
    addstr(&execlist, symtab);
    if (run(ujoin, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_1748;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_2271;
    }
    if ((u8) srcsuf == 0x42) {
        goto block_1746;
    }
    unlink(passin);
block_1746:
    unlink(passout);
    if (tmpst == 0) {
        goto block_2271;
    }
    unlink(symtab);
    goto block_2270;
block_1748:
    if (cflag == 0) {
        goto block_1751;
    }
    temp_t5_10 = Oflag;
    if (temp_t5_10 == 3) {
        goto block_1751;
    }
    if (temp_t5_10 != 4) {
        goto block_1934;
    }
block_1751:
    if (Kflag != 0) {
        goto block_1756;
    }
    if ((u8) srcsuf == 0x42) {
        goto block_1754;
    }
    unlink(passin);
block_1754:
    if (tmpst == 0) {
        goto block_1756;
    }
    unlink(symtab);
block_1756:
    passin = passout;
    goto block_2271;
block_1757:
    if (non_shared == 0) {
        goto block_1760;
    }
    if (non_shared_emitted != 0) {
        goto block_1760;
    }
    addstr(&ldflags, "-non_shared");
    non_shared_emitted = 1;
block_1760:
    execlist.length = 0;
    addstr(&execlist, "uld");
    if (mips2flag == 0) {
        goto block_1770;
    }
    if (sp148 != 0) {
        goto block_1770;
    }
    if (strcmp("/", comp_target_root) == 0) {
        goto block_1766;
    }
    if (non_shared == 0) {
        goto block_1765;
    }
    addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "nonshared", NULL));
    goto block_1769;
block_1765:
    addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "", NULL));
    goto block_1769;
block_1766:
    if (non_shared == 0) {
        goto block_1768;
    }
    addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "nonshared", NULL));
    goto block_1769;
block_1768:
    addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "", NULL));
block_1769:
block_1770:
    if (mips1flag == 0) {
        goto block_1780;
    }
    if (sp148 != 0) {
        goto block_1780;
    }
    if (strcmp("/", comp_target_root) == 0) {
        goto block_1776;
    }
    if (non_shared == 0) {
        goto block_1775;
    }
    addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "nonshared", NULL));
    goto block_1779;
block_1775:
    addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "", NULL));
    goto block_1779;
block_1776:
    if (non_shared == 0) {
        goto block_1778;
    }
    addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "nonshared", NULL));
    goto block_1779;
block_1778:
    addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "", NULL));
block_1779:
block_1780:
    if (fiveflag != 0) {
        goto block_1782;
    }
    if (strcmp("/", comp_target_root) == 0) {
        goto block_1788;
    }
block_1782:
    if (Lflag != 0) {
        goto block_1788;
    }
    if (strcmp("/", comp_target_root) == 0) {
        goto block_1788;
    }
    if (non_shared == 0) {
        goto block_1786;
    }
    addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/nonshared/", currcomp, NULL));
    goto block_1787;
block_1786:
    addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, NULL));
block_1787:
block_1788:
    if (svr4_systype == 0) {
        goto block_1793;
    }
    if (compchoice != 1) {
        goto block_1791;
    }
    addstr(&execlist, mkstr("-SYSTYPE_SVR4", NULL, NULL));
block_1791:
    addstr(&execlist, mkstr("-_SYSTYPE_SVR4", NULL, NULL));
    if (call_shared == 0) {
        goto block_1793;
    }
    addstr(&execlist, "-require_dynamic_link");
    addstr(&execlist, "_rld_new_interface");
block_1793:
    temp_t6_14 = allBstring;
    if (temp_t6_14 == NULL) {
        goto block_1796;
    }
    if ((u8) *temp_t6_14 == 0) {
        goto block_1796;
    }
    addstr(&execlist, mkstr("-kB", temp_t6_14, NULL));
block_1796:
    addlist(&execlist, &uldflags);
    addlist(&execlist, &ldflags);
    if (irix4 == 0) {
        goto block_1801;
    }
    addstr(&execlist, mkstr("-L", NULL));
    if (non_shared == 0) {
        goto block_1799;
    }
    addstr(&execlist, mkstr("-L", "/usr/irix4/", "usr/lib/nonshared/", NULL));
    crtx = mkstr(comp_host_root, "usr/lib/nonshared/", CRTX, NULL);
    var_v0_15 = mkstr(comp_host_root, "usr/lib/nonshared/", "crtn.o", NULL);
    goto block_1800;
block_1799:
    addstr(&execlist, mkstr("-L", "/usr/irix4/", "usr/lib/", NULL));
    crtx = mkstr(comp_host_root, "usr/lib/", CRTX, NULL);
    var_v0_15 = mkstr(comp_host_root, "usr/lib/", "crtn.o", NULL);
block_1800:
    crtn = var_v0_15;
block_1801:
    if (cflag != 0) {
        goto block_1803;
    }
    addstr(&execlist, crtx);
    goto block_1805;
block_1803:
    addstr(&execlist, "-no_AutoGnum");
    if (force_rm_dead_code != 0) {
        goto block_1806;
    }
    addstr(&execlist, "-preserve_dead_code");
block_1805:
block_1806:
    adduldlist(&execlist, &ufiles, &objfiles);
    if (cflag != 0) {
        goto block_1877;
    }
    addlist(&execlist, &uldlibflags);
    if (compiler == 2) {
        goto block_1809;
    }
    if (haspascal == 0) {
        goto block_1814;
    }
block_1809:
    addspacedstr(&execlist, newstr(libp));
    addspacedstr(&execlist, newstr(libxmalloc));
    addspacedstr(&execlist, newstr(libexc));
    addspacedstr(&execlist, newstr(libmld));
    if (default_call_shared != 0) {
        goto block_1811;
    }
    if (call_shared == 0) {
        goto block_1814;
    }
block_1811:
    temp_t6_15 = systype;
    if (temp_t6_15 == NULL) {
        goto block_1814;
    }
    if (strcmp(temp_t6_15, "svr3") != 0) {
        goto block_1814;
    }
    addspacedstr(&execlist, "-lbsd");
block_1814:
    if (compiler == 3) {
        goto block_1816;
    }
    if (hasfortran == 0) {
        goto block_1831;
    }
block_1816:
    if (mp_flag == 0) {
        goto block_1818;
    }
    addstr(&execlist, libI77_mp);
block_1818:
    if (non_shared != 0) {
        goto block_1820;
    }
    if (irix4 == 0) {
        goto block_1821;
    }
block_1820:
    addspacedstr(&execlist, newstr(libF77));
    goto block_1822;
block_1821:
    addspacedstr(&execlist, libftn);
block_1822:
    if (non_shared != 0) {
        goto block_1824;
    }
    if (irix4 == 0) {
        goto block_1825;
    }
block_1824:
    addspacedstr(&execlist, newstr(libI77));
block_1825:
    if (non_shared != 0) {
        goto block_1827;
    }
    if (irix4 == 0) {
        goto block_1828;
    }
block_1827:
    addspacedstr(&execlist, newstr(libU77));
block_1828:
    if (non_shared != 0) {
        goto block_1830;
    }
    if (irix4 == 0) {
        goto block_1831;
    }
block_1830:
    addspacedstr(&execlist, newstr(libisam));
block_1831:
    if (compiler != 5) {
        goto block_1833;
    }
    addstr(&execlist, libpl1);
    addstr(&execlist, libxmalloc);
    addstr(&execlist, "-ltermcap");
    addstr(&execlist, libexc);
    addstr(&execlist, libmld);
block_1833:
    temp_t5_11 = compiler;
    if (temp_t5_11 == 2) {
        goto block_1840;
    }
    if (temp_t5_11 == 3) {
        goto block_1840;
    }
    if (haspascal != 0) {
        goto block_1840;
    }
    if (hasfortran != 0) {
        goto block_1840;
    }
    if (haspl1 != 0) {
        goto block_1840;
    }
    if (temp_t5_11 == 5) {
        goto block_1840;
    }
    if (temp_t5_11 != 6) {
        goto block_1842;
    }
block_1840:
    if (nonshared == 0) {
        goto block_1842;
    }
    addspacedstr(&execlist, newstr(libm));
block_1842:
    if (pgflag == 0) {
        goto block_1844;
    }
    addspacedstr(&execlist, newstr(libgprof));
    goto block_1846;
block_1844:
    if (pflag == 0) {
        goto block_1847;
    }
    addspacedstr(&execlist, newstr(libprof));
block_1846:
block_1847:
    if (!(cmp_flag & 0x10000)) {
        goto block_1850;
    }
    addstr(&execlist, libc_mp);
    if (compiler != 1) {
        goto block_1850;
    }
    addstr(&execlist, "-lkapio");
block_1850:
    if (run_sopt == 0) {
        goto block_1853;
    }
    if (compiler != 1) {
        goto block_1853;
    }
    addstr(&execlist, "-lkapio");
block_1853:
    if (compiler != 3) {
        goto block_1865;
    }
    if (D_1000C130 != 2) {
        goto block_1858;
    }
    addstr(&execlist, "-lc_s");
    if (xpg_flag == 0) {
        goto block_1857;
    }
    addstr(&execlist, "-dont_warn_unused");
    addstr(&execlist, "-lgen");
    addstr(&execlist, "-warn_unused");
block_1857:
    addstr(&execlist, "-lc");
    goto block_1867;
block_1858:
    if (irix4 == 0) {
        goto block_1861;
    }
    if (B_1000ED74 != 0) {
        goto block_1861;
    }
    addstr(&execlist, "-lmpc");
block_1861:
    if (B_1000ED2C == 0) {
        goto block_1863;
    }
    addstr(&execlist, "-lc_s");
    goto block_1867;
block_1863:
    if (B_1000ED30 == 0) {
        goto block_1868;
    }
    addstr(&execlist, "-lc_s");
    goto block_1867;
block_1865:
    if (B_1000ED2C == 0) {
        goto block_1868;
    }
    addstr(&execlist, "-lc_s");
block_1867:
block_1868:
    if (sixty4bitflag != 0) {
        goto block_1871;
    }
    ldw_file = fopen(libdw_path, "r");
    if (ldw_file == NULL) {
        goto block_1871;
    }
    addspacedstr(&execlist, newstr(libdw));
block_1871:
    if (xpg_flag == 0) {
        goto block_1873;
    }
    addstr(&execlist, "-dont_warn_unused");
    addstr(&execlist, "-lgen");
    addstr(&execlist, "-warn_unused");
block_1873:
    addstr(&execlist, "-lc");
    if (libm_spec == 0) {
        goto block_1875;
    }
    addstr(&execlist, "-lm");
block_1875:
    if (libfastm_spec == 0) {
        goto block_1877;
    }
    addstr(&execlist, "-lfastm");
block_1877:
    if (cflag != 0) {
        goto block_1880;
    }
    if (crtn_required == 0) {
        goto block_1880;
    }
    addstr(&execlist, crtn);
block_1880:
    temp_t6_16 = rls_id_object;
    if (temp_t6_16 == NULL) {
        goto block_1882;
    }
    addstr(&execlist, temp_t6_16);
block_1882:
    addstr(&execlist, "-ko");
    temp_t1_9 = uoutfile;
    if (temp_t1_9 == NULL) {
        goto block_1884;
    }
    passout = temp_t1_9;
    goto block_1888;
block_1884:
    if (Hchar == 0x75) {
        goto block_1886;
    }
    if (Kflag == 0) {
        goto block_1887;
    }
block_1886:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x75U);
    goto block_1888;
block_1887:
    passout = tempstr->unk_10;
block_1888:
    addstr(&execlist, passout);
    if (run(uld, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_1891;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_2271;
    }
    unlink(passout);
    goto block_2270;
block_1891:
    passin = passout;
    if (ufiles.length != 1) {
        goto block_1896;
    }
    if (srcfiles.length != 2) {
        goto block_1896;
    }
    temp_t7_18 = Oflag;
    if (temp_t7_18 == 3) {
        goto block_1895;
    }
    if (temp_t7_18 != 4) {
        goto block_1896;
    }
block_1895:
    unlink(*ufiles.entries);
block_1896:
    if (Hchar == 0x75) {
        goto block_2271;
    }
case 0x75:                                          /* switch 3 */
    execlist.length = 0;
    addstr(&execlist, "usplit");
    if (vflag == 0) {
        goto block_1899;
    }
    addstr(&execlist, "-v");
block_1899:
    addlist(&execlist, &usplitflags);
    if (Hchar == 0x73) {
        goto block_1901;
    }
    if (Kflag == 0) {
        goto block_1903;
    }
block_1901:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x53U);
    if (regular_not_writeable(passout) != 1) {
        goto block_1904;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
    goto block_1904;
block_1903:
    passout = tempstr->unk_14;
block_1904:
    addstr(&execlist, "-o");
    addstr(&execlist, passout);
    addstr(&execlist, "-t");
    addstr(&execlist, symtab);
    addstr(&execlist, passin);
    if (run(usplit, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_1909;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_1907;
    }
    unlink(passin);
    unlink(passout);
block_1907:
    if (tmpst == 0) {
        goto block_2271;
    }
    unlink(symtab);
    goto block_2270;
block_1909:
    if (Kflag != 0) {
        goto block_1913;
    }
    if ((u8) srcsuf == 0x75) {
        goto block_1913;
    }
    if (uoutfile != NULL) {
        goto block_1913;
    }
    unlink(passin);
block_1913:
    passin = passout;
    if (Hchar == 0x73) {
        goto block_2271;
    }
case 0x53:                                          /* switch 3 */
block_1914:
    temp_t8_15 = Oflag;
    if (temp_t8_15 == 3) {
        goto block_1917;
    }
    if (temp_t8_15 == 4) {
        goto block_1917;
    }
    if (c_inline == 0) {
        goto block_1934;
    }
block_1917:
    execlist.length = 0;
    addstr(&execlist, "umerge");
    if (vflag == 0) {
        goto block_1919;
    }
    addstr(&execlist, "-v");
block_1919:
    addlist(&execlist, &umergeflags);
    addstr(&execlist, passin);
    addstr(&execlist, "-o");
    if (Hchar == 0x6D) {
        goto block_1921;
    }
    if (Kflag == 0) {
        goto block_1923;
    }
block_1921:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x4DU);
    if (regular_not_writeable(passout) != 1) {
        goto block_1924;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
    goto block_1924;
block_1923:
    passout = tempstr->unk_18;
block_1924:
    addstr(&execlist, passout);
    addstr(&execlist, "-t");
    addstr(&execlist, symtab);
    if (run(umerge, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_1930;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_2271;
    }
    if ((u8) srcsuf == 0x53) {
        goto block_1928;
    }
    unlink(passin);
block_1928:
    unlink(passout);
    if (tmpst == 0) {
        goto block_2271;
    }
    unlink(symtab);
    goto block_2270;
block_1930:
    if (Kflag != 0) {
        goto block_1933;
    }
    if ((u8) srcsuf == 0x53) {
        goto block_1933;
    }
    unlink(passin);
block_1933:
    passin = passout;
    if (Hchar == 0x6D) {
        goto block_2271;
    }
case 0x4D:                                          /* switch 3 */
block_1934:
    if (unrollflag == 0) {
        goto block_1954;
    }
    execlist.length = 0;
    addstr(&execlist, "uloop");
    if (vflag == 0) {
        goto block_1937;
    }
    addstr(&execlist, "-v");
block_1937:
    addlist(&execlist, &uloopflags);
    addstr(&execlist, passin);
    addstr(&execlist, "-o");
    if (Hchar == 0x76) {
        goto block_1939;
    }
    if (Kflag == 0) {
        goto block_1944;
    }
block_1939:
    if (Hchar == 0x76) {
        goto block_1941;
    }
    if (Kflag == 0) {
        goto block_1943;
    }
block_1941:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x56U);
    if (regular_not_writeable(passout) != 1) {
        goto block_1944;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
    goto block_1944;
block_1943:
    passout = tempstr->unk_5C;
block_1944:
    addstr(&execlist, passout);
    addstr(&execlist, "-t");
    addstr(&execlist, symtab);
    if (run(uloop, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_1950;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_2271;
    }
    if ((u8) srcsuf == 0x4D) {
        goto block_1948;
    }
    unlink(passin);
block_1948:
    unlink(passout);
    if (tmpst == 0) {
        goto block_2271;
    }
    unlink(symtab);
    goto block_2270;
block_1950:
    if (Kflag != 0) {
        goto block_1953;
    }
    if ((u8) srcsuf == 0x4D) {
        goto block_1953;
    }
    unlink(passin);
block_1953:
    passin = passout;
    if (Hchar == 0x76) {
        goto block_2271;
    }
block_1954:
    if (uopt0flag != 1) {
        goto block_1981;
    }
    if (compiler != 3) {
        goto block_1981;
    }
    if (Oflag < 2) {
        goto block_1981;
    }
    execlist.length = 0;
    addstr(&execlist, "uopt0");
    if (vflag == 0) {
        goto block_1959;
    }
    addstr(&execlist, "-v");
block_1959:
    addstr(&execlist, "-G");
    addstr(&execlist, Gnum);
    addlist(&execlist, &uopt0flags);
    addstr(&execlist, passin);
    if (Hchar == 0x71) {
        goto block_1961;
    }
    if (Kflag == 0) {
        goto block_1963;
    }
block_1961:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x51U);
    if (regular_not_writeable(passout) != 1) {
        goto block_1964;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
    goto block_1964;
block_1963:
    passout = tempstr->unk_70;
block_1964:
    addstr(&execlist, passout);
    addstr(&execlist, "-t");
    addstr(&execlist, symtab);
    temp_t0_9 = tempstr->unk_74;
    uopt0str = temp_t0_9;
    addstr(&execlist, temp_t0_9);
    if (run(uopt0, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_1974;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_1973;
    }
    temp_t4_13 = (u8) srcsuf;
    if (temp_t4_13 == 0x4D) {
        goto block_1971;
    }
    if (temp_t4_13 == 0x42) {
        goto block_1971;
    }
    if (temp_t4_13 == 0x53) {
        goto block_1971;
    }
    if (temp_t4_13 == 0x51) {
        goto block_1971;
    }
    unlink(passin);
block_1971:
    unlink(passout);
    if (tmpst == 0) {
        goto block_1973;
    }
    unlink(symtab);
block_1973:
    unlink(uopt0str);
    goto block_2270;
block_1974:
    if (Kflag != 0) {
        goto block_1980;
    }
    temp_t1_10 = (u8) srcsuf;
    if (temp_t1_10 == 0x4D) {
        goto block_1980;
    }
    if (temp_t1_10 == 0x42) {
        goto block_1980;
    }
    if (temp_t1_10 == 0x53) {
        goto block_1980;
    }
    if (temp_t1_10 == 0x51) {
        goto block_1980;
    }
    unlink(passin);
block_1980:
    unlink(uopt0str);
    passin = passout;
    if (Hchar == 0x71) {
        goto block_2271;
    }
block_1981:
    if (ddoptflag != 1) {
        goto block_2016;
    }
    if (compiler != 3) {
        goto block_2016;
    }
    if (Oflag < 2) {
        goto block_2016;
    }
    execlist.length = 0;
    addstr(&execlist, "ddopt");
    if (vflag == 0) {
        goto block_1986;
    }
    addstr(&execlist, "-v");
block_1986:
    addstr(&execlist, "-G");
    addstr(&execlist, Gnum);
    addlist(&execlist, &ddoptflags);
    addstr(&execlist, passin);
    if (Hchar != 0x64) {
        goto block_1988;
    }
    if (ucodeflag == 0) {
        goto block_1989;
    }
block_1988:
    if (Kflag == 0) {
        goto block_1991;
    }
block_1989:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x44U);
    if (regular_not_writeable(passout) != 1) {
        goto block_1992;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
    goto block_1992;
block_1991:
    passout = tempstr->unk_6C;
block_1992:
    if (ddoptinfo == 0) {
        goto block_1999;
    }
    addstr(&execlist, "-e");
    if (Hchar != 0x64) {
        goto block_1995;
    }
    if (ucodeflag == 0) {
        goto block_1996;
    }
block_1995:
    if (Kflag == 0) {
        goto block_1997;
    }
block_1996:
    addstr(&execlist, mksuf(srcfiles.entries[var_s0_3], 0x45U));
    goto block_1998;
block_1997:
    addstr(&execlist, tempstr->unk_68);
block_1998:
block_1999:
    addstr(&execlist, passout);
    if (run(ddopt, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_2009;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_2008;
    }
    temp_t2_12 = (u8) srcsuf;
    if (temp_t2_12 == 0x42) {
        goto block_2006;
    }
    if (temp_t2_12 == 0x53) {
        goto block_2006;
    }
    if (temp_t2_12 == 0x4D) {
        goto block_2006;
    }
    if (temp_t2_12 == 0x51) {
        goto block_2006;
    }
    unlink(passin);
block_2006:
    unlink(passout);
    if (tmpst == 0) {
        goto block_2008;
    }
    unlink(symtab);
block_2008:
    unlink(ddoptstr);
    goto block_2270;
block_2009:
    if (Kflag != 0) {
        goto block_2015;
    }
    temp_t3_15 = (u8) srcsuf;
    if (temp_t3_15 == 0x42) {
        goto block_2015;
    }
    if (temp_t3_15 == 0x53) {
        goto block_2015;
    }
    if (temp_t3_15 == 0x4D) {
        goto block_2015;
    }
    if (temp_t3_15 == 0x51) {
        goto block_2015;
    }
    unlink(passin);
block_2015:
    unlink(ddoptstr);
    passin = passout;
    if (Hchar == 0x64) {
        goto block_2271;
    }
case 0x44:                                          /* switch 3 */
case 0x51:                                          /* switch 3 */
case 0x56:                                          /* switch 3 */
block_2016:
    temp_t7_19 = Oflag;
    if (temp_t7_19 == 2) {
        goto block_2019;
    }
    if (temp_t7_19 == 3) {
        goto block_2019;
    }
    if (temp_t7_19 != 4) {
        goto block_2069;
    }
block_2019:
    execlist.length = 0;
    addstr(&execlist, "uopt");
    if (vflag == 0) {
        goto block_2021;
    }
    addstr(&execlist, "-v");
block_2021:
    addstr(&execlist, "-G");
    addstr(&execlist, Gnum);
    if (!(mp_flag & 0x10000)) {
        goto block_2025;
    }
    temp_t2_13 = (u8) srcsuf;
    if (temp_t2_13 == 0x66) {
        goto block_2024;
    }
    if (temp_t2_13 != 0x46) {
        goto block_2025;
    }
block_2024:
    addstr(&execlist, "-noPalias");
block_2025:
    if (irix4 != 0) {
        goto block_2030;
    }
    if (kpicopt_flag == 0) {
        goto block_2028;
    }
    addstr(&execlist, "-kpicopt");
block_2028:
    if (nokpicopt_flag == 0) {
        goto block_2030;
    }
    addstr(&execlist, "-nokpicopt");
block_2030:
    addlist(&execlist, &optflags);
    addstr(&execlist, passin);
    if (Hchar != 0x6F) {
        goto block_2032;
    }
    if (ucodeflag == 0) {
        goto block_2033;
    }
block_2032:
    if (Kflag == 0) {
        goto block_2038;
    }
block_2033:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x4FU);
    if (regular_not_writeable(passout) != 1) {
        goto block_2035;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
block_2035:
    if (NoMoreOptions == 0) {
        goto block_2039;
    }
    *passout = 0x2D;
    temp_t0_10 = passout;
    if ((u8) *temp_t0_10 == 0) {
        goto block_2039;
    }
    passout = func_00433534(temp_t0_10);
    goto block_2039;
block_2038:
    passout = tempstr->unk_1C;
block_2039:
    addstr(&execlist, passout);
    addstr(&execlist, "-t");
    addstr(&execlist, symtab);
    temp_t2_14 = tempstr->unk_20;
    optstr = temp_t2_14;
    addstr(&execlist, temp_t2_14);
    if (run(opt, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_2051;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_2050;
    }
    temp_t9_16 = (u8) srcsuf;
    if (temp_t9_16 == 0x42) {
        goto block_2048;
    }
    if (temp_t9_16 == 0x53) {
        goto block_2048;
    }
    if (temp_t9_16 == 0x51) {
        goto block_2048;
    }
    if (temp_t9_16 == 0x44) {
        goto block_2048;
    }
    if (temp_t9_16 == 0x4D) {
        goto block_2048;
    }
    if (temp_t9_16 == 0x56) {
        goto block_2048;
    }
    unlink(passin);
block_2048:
    unlink(passout);
    if (tmpst == 0) {
        goto block_2050;
    }
    unlink(symtab);
block_2050:
    unlink(optstr);
    goto block_2270;
block_2051:
    if (Kflag != 0) {
        goto block_2059;
    }
    temp_t5_12 = (u8) srcsuf;
    if (temp_t5_12 == 0x42) {
        goto block_2059;
    }
    if (temp_t5_12 == 0x53) {
        goto block_2059;
    }
    if (temp_t5_12 == 0x51) {
        goto block_2059;
    }
    if (temp_t5_12 == 0x44) {
        goto block_2059;
    }
    if (temp_t5_12 == 0x4D) {
        goto block_2059;
    }
    if (temp_t5_12 == 0x56) {
        goto block_2059;
    }
    unlink(passin);
block_2059:
    unlink(optstr);
    passin = passout;
    if (Hchar != 0x6F) {
        goto block_2068;
    }
    if (ucodeflag == 0) {
        goto block_2068;
    }
    execlist.length = 0;
    addstr(&execlist, "btou");
    addstr(&execlist, passin);
    passout = mksuf(srcfiles.entries[var_s0_3], 0x55U);
    addstr(&execlist, passout);
    if (run(btou, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_2065;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_2271;
    }
    unlink(passin);
    unlink(passout);
    if (tmpst == 0) {
        goto block_2271;
    }
    unlink(symtab);
    goto block_2270;
block_2065:
    if (Kflag != 0) {
        goto block_2271;
    }
    unlink(passin);
    if (tmpst == 0) {
        goto block_2271;
    }
    unlink(symtab);
    goto block_2270;
block_2068:
    if (Hchar == 0x6F) {
        goto block_2271;
    }
case 0x4F:                                          /* switch 3 */
block_2069:
    execlist.length = 0;
    addstr(&execlist, "ugen");
    if (vflag == 0) {
        goto block_2071;
    }
    addstr(&execlist, "-v");
block_2071:
    addstr(&execlist, "-G");
    addstr(&execlist, Gnum);
    if (kpic_flag == 0) {
        goto block_2078;
    }
    if (coff_spec != 0) {
        goto block_2078;
    }
    if (irix4 != 0) {
        goto block_2078;
    }
    if (Oflag < 3) {
        goto block_2076;
    }
    addstr(&execlist, "-pic1");
    goto block_2077;
block_2076:
    addstr(&execlist, "-pic2");
block_2077:
block_2078:
    addlist(&execlist, &genflags);
    addstr(&execlist, passin);
    if (Sflag == 0) {
        goto block_2085;
    }
    addstr(&execlist, "-o");
    if (Kflag == 0) {
        goto block_2081;
    }
    addstr(&execlist, mksuf(srcfiles.entries[var_s0_3], 0x47U));
    goto block_2082;
block_2081:
    temp_t1_11 = tempstr->unk_24;
    binasm = temp_t1_11;
    addstr(&execlist, temp_t1_11);
block_2082:
    addstr(&execlist, "-l");
    passout = mksuf(srcfiles.entries[var_s0_3], 0x73U);
    if (regular_not_writeable(passout) != 1) {
        goto block_2084;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
block_2084:
    addstr(&execlist, passout);
    goto block_2098;
block_2085:
    if (Hchar != 0x63) {
        goto block_2089;
    }
    addstr(&execlist, "-o");
    passout = mksuf(srcfiles.entries[var_s0_3], 0x47U);
    if (regular_not_writeable(passout) != 1) {
        goto block_2088;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
block_2088:
    addstr(&execlist, passout);
    goto block_2098;
block_2089:
    if (Kflag == 0) {
        goto block_2095;
    }
    addstr(&execlist, "-o");
    passout = mksuf(srcfiles.entries[var_s0_3], 0x47U);
    if (regular_not_writeable(passout) != 1) {
        goto block_2092;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
block_2092:
    addstr(&execlist, passout);
    if (regular_not_writeable(mksuf(srcfiles.entries[var_s0_3], 0x73U)) != 1) {
        goto block_2094;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", mksuf(srcfiles.entries[var_s0_3], 0x73U));
    exit(2);
block_2094:
    addstr(&execlist, "-l");
    addstr(&execlist, mksuf(srcfiles.entries[var_s0_3], 0x73U));
    goto block_2098;
block_2095:
    addstr(&execlist, "-o");
    temp_t6_17 = tempstr->unk_28;
    passout = temp_t6_17;
    if (regular_not_writeable(temp_t6_17) != 1) {
        goto block_2097;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
block_2097:
    addstr(&execlist, passout);
block_2098:
    addstr(&execlist, "-t");
    addstr(&execlist, symtab);
    addstr(&execlist, "-temp");
    temp_t7_20 = tempstr->unk_3C;
    gentmp = temp_t7_20;
    addstr(&execlist, temp_t7_20);
    if (run(gen, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_2114;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_2110;
    }
    temp_t4_14 = (u8) srcsuf;
    if (temp_t4_14 == 0x42) {
        goto block_2108;
    }
    if (temp_t4_14 == 0x4F) {
        goto block_2108;
    }
    if (temp_t4_14 == 0x51) {
        goto block_2108;
    }
    if (temp_t4_14 == 0x44) {
        goto block_2108;
    }
    if (temp_t4_14 == 0x4D) {
        goto block_2108;
    }
    if (temp_t4_14 == 0x53) {
        goto block_2108;
    }
    if (temp_t4_14 == 0x56) {
        goto block_2108;
    }
    unlink(passin);
block_2108:
    unlink(passout);
    if (tmpst == 0) {
        goto block_2113;
    }
    unlink(symtab);
    goto block_2112;
block_2110:
    if (Sflag == 0) {
        goto block_2113;
    }
    unlink(binasm);
block_2112:
block_2113:
    unlink(gentmp);
    goto block_2270;
block_2114:
    unlink(gentmp);
    temp_t1_12 = (u8) srcsuf;
    if (temp_t1_12 == 0x42) {
        goto block_2120;
    }
    if (temp_t1_12 == 0x53) {
        goto block_2120;
    }
    if (temp_t1_12 == 0x51) {
        goto block_2120;
    }
    if (temp_t1_12 == 0x44) {
        goto block_2120;
    }
    if (temp_t1_12 == 0x4D) {
        goto block_2120;
    }
    if (temp_t1_12 != 0x56) {
        goto block_2121;
    }
block_2120:
    if (Oflag < 2) {
        goto block_2124;
    }
block_2121:
    if ((u8) srcsuf == 0x4F) {
        goto block_2124;
    }
    if (Kflag != 0) {
        goto block_2124;
    }
    unlink(passin);
block_2124:
    if (Sflag == 0) {
        goto block_2129;
    }
    if (Kflag != 0) {
        goto block_2271;
    }
    if (tmpst == 0) {
        goto block_2128;
    }
    unlink(symtab);
block_2128:
    unlink(binasm);
    goto block_2270;
block_2129:
    if (Hchar == 0x63) {
        goto block_2271;
    }
    passin = passout;
case 0x73:                                          /* switch 7 */
case 0x73:                                          /* switch 8 */
block_2131:
    if ((u8) srcsuf != 0x73) {
        goto block_2160;
    }
    execlist.length = 0;
    addstr(&execlist, "as0");
    if (vflag == 0) {
        goto block_2134;
    }
    addstr(&execlist, "-v");
block_2134:
    addstr(&execlist, "-G");
    addstr(&execlist, Gnum);
    addlist(&execlist, &asflags);
    if (NoMoreOptions == 0) {
        goto block_2137;
    }
    temp_t9_17 = passin;
    if ((u8) *temp_t9_17 != 0x2D) {
        goto block_2137;
    }
    passin = func_00433534(temp_t9_17);
block_2137:
    addstr(&execlist, passin);
    addstr(&execlist, "-o");
    if (Hchar == 0x61) {
        goto block_2139;
    }
    if (Kflag == 0) {
        goto block_2145;
    }
block_2139:
    if (compiler != 4) {
        goto block_2142;
    }
    if (getsuf(srcfiles.entries[var_s0_3]) != 0) {
        goto block_2142;
    }
    var_v0_16 = mkstr(srcfiles.entries[var_s0_3], ".G", NULL);
    goto block_2143;
block_2142:
    var_v0_16 = mksuf(srcfiles.entries[var_s0_3], 0x47U);
block_2143:
    passout = var_v0_16;
    if (regular_not_writeable(passout) != 1) {
        goto block_2148;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
    goto block_2147;
block_2145:
    temp_t6_18 = tempstr->unk_2C;
    passout = temp_t6_18;
    if (regular_not_writeable(temp_t6_18) != 1) {
        goto block_2148;
    }
    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
    exit(2);
block_2147:
block_2148:
    addstr(&execlist, passout);
    addstr(&execlist, "-t");
    addstr(&execlist, symtab);
    if (run(as0, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_2155;
    }
    runerror += 1;
    if (docpp != 0) {
        goto block_2151;
    }
    if (mflag == 0) {
        goto block_2152;
    }
block_2151:
    unlink(passin);
block_2152:
    if (Kflag != 0) {
        goto block_2271;
    }
    unlink(passout);
    if (tmpst == 0) {
        goto block_2271;
    }
    unlink(symtab);
    goto block_2270;
block_2155:
    if (docpp != 0) {
        goto block_2157;
    }
    if (mflag == 0) {
        goto block_2158;
    }
block_2157:
    unlink(passin);
block_2158:
    if (Hchar == 0x61) {
        goto block_2271;
    }
    passin = passout;
case 0x47:                                          /* switch 3 */
block_2160:
    execlist.length = 0;
    addstr(&execlist, "as1");
    addstr(&execlist, "-t5_ll_sc_bug");
    if (tfp_flag == 0) {
        goto block_2162;
    }
    addstr(&execlist, "-tfp");
block_2162:
    if (noaliasokflag == 0) {
        goto block_2164;
    }
    addstr(&execlist, "-noaliasok");
block_2164:
    temp_t0_11 = alignarg;
    if (temp_t0_11 == NULL) {
        goto block_2166;
    }
    addstr(&execlist, temp_t0_11);
block_2166:
    if (align_common <= 0) {
        goto block_2168;
    }
    addstr(&execlist, "-align_common");
block_2168:
    if (compiler == 4) {
        goto block_2170;
    }
    if ((u8) srcsuf != 0x73) {
        goto block_2173;
    }
block_2170:
    if (kpic_spec != 0) {
        goto block_2173;
    }
    if (irix4 != 0) {
        goto block_2173;
    }
    addstr(&execlist, "-pic0");
block_2173:
    if (coff_spec == 0) {
        goto block_2175;
    }
    addstr(&execlist, "-coff");
    kpic_flag = 0;
    goto block_2187;
block_2175:
    if (kpic_flag == 0) {
        goto block_2182;
    }
    if (irix4 != 0) {
        goto block_2187;
    }
    if (coff_spec != 0) {
        goto block_2181;
    }
    addstr(&execlist, "-elf");
    if (Oflag < 3) {
        goto block_2180;
    }
    addstr(&execlist, "-pic1");
    goto block_2186;
block_2180:
    addstr(&execlist, "-pic2");
    goto block_2186;
block_2181:
    addstr(&execlist, "-coff");
    kpic_flag = 0;
    goto block_2187;
block_2182:
    if (irix4 != 0) {
        goto block_2187;
    }
    if (coff_spec == 0) {
        goto block_2185;
    }
    addstr(&execlist, "-coff");
    goto block_2186;
block_2185:
    addstr(&execlist, "-elf");
block_2186:
block_2187:
    if (vflag == 0) {
        goto block_2189;
    }
    addstr(&execlist, "-v");
block_2189:
    if (fullasoptflag != 0) {
        goto block_2193;
    }
    if ((u8) srcsuf != 0x73) {
        goto block_2193;
    }
    if (Oflag < 2) {
        goto block_2193;
    }
    addstr(&execlist, "-noglobal");
block_2193:
    addstr(&execlist, "-G");
    addstr(&execlist, Gnum);
    temp_s3_12 = pflag;
    if (temp_s3_12 == 0) {
        goto block_2196;
    }
    if (temp_s3_12 == 1) {
        goto block_2197;
    }
    goto block_2199;
block_2196:
    addstr(&execlist, "-p0");
    goto block_2198;
block_2197:
    addstr(&execlist, "-p1");
block_2198:
block_2199:
    addlist(&execlist, &asflags);
    addlist(&execlist, &as1flags);
    if (irix4 != 0) {
        goto block_2201;
    }
    addlist(&execlist, &olimitflags);
block_2201:
    if (NoMoreOptions == 0) {
        goto block_2204;
    }
    temp_t9_18 = passin;
    if ((u8) *temp_t9_18 != 0x2D) {
        goto block_2204;
    }
    passin = func_00433534(temp_t9_18);
block_2204:
    addstr(&execlist, passin);
    addstr(&execlist, "-o");
    if (compiler != 4) {
        goto block_2208;
    }
    temp_t8_16 = outfile;
    if (temp_t8_16 == NULL) {
        goto block_2207;
    }
    passout = temp_t8_16;
    goto block_2224;
block_2207:
    passout = "a.out";
    goto block_2224;
block_2208:
    if (outfile == NULL) {
        goto block_2213;
    }
    if (cflag == 0) {
        goto block_2213;
    }
    if (Oflag == 3) {
        goto block_2212;
    }
    if (srcfiles.length != 1) {
        goto block_2213;
    }
block_2212:
    passout = outfile;
    goto block_2224;
block_2213:
    if ((u8) srcsuf != 0x3F) {
        goto block_2221;
    }
    if (Hchar == 0x62) {
        goto block_2221;
    }
    if (Kflag != 0) {
        goto block_2221;
    }
    if (cflag != 0) {
        goto block_2218;
    }
    temp_t2_15 = tempstr->unk_30;
    passout = temp_t2_15;
    tmp_uldobj = temp_t2_15;
    goto block_2222;
block_2218:
    if (srcfiles.length != 2) {
        goto block_2220;
    }
    passout = mksuf(*srcfiles.entries, 0x6FU);
    tmp_uldobj = NULL;
    goto block_2222;
block_2220:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x6FU);
    tmp_uldobj = NULL;
    goto block_2222;
block_2221:
    passout = mksuf(srcfiles.entries[var_s0_3], 0x6FU);
block_2222:
    temp_t4_15 = uldobj_place;
    if (temp_t4_15 == -1) {
        goto block_2224;
    }
    set_place(&objfiles, passout, temp_t4_15);
block_2224:
    addstr(&execlist, passout);
    addstr(&execlist, "-t");
    addstr(&execlist, symtab);
    if (ddoptflag != 1) {
        goto block_2234;
    }
    if (compiler != 3) {
        goto block_2234;
    }
    if (ddoptinfo == 0) {
        goto block_2234;
    }
    if (Oflag < 2) {
        goto block_2234;
    }
    addstr(&execlist, "-e");
    if (Hchar != 0x62) {
        goto block_2230;
    }
    if (ucodeflag == 0) {
        goto block_2231;
    }
block_2230:
    if (Kflag == 0) {
        goto block_2232;
    }
block_2231:
    addstr(&execlist, mksuf(srcfiles.entries[var_s0_3], 0x45U));
    goto block_2233;
block_2232:
    addstr(&execlist, tempstr->unk_68);
block_2233:
block_2234:
    if (regular_not_writeable(passout) == 0) {
        goto block_2236;
    }
    unlink(passout);
block_2236:
    if (run(as1, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_2249;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_2247;
    }
    if ((u8) srcsuf == 0x47) {
        goto block_2240;
    }
    unlink(passin);
block_2240:
    spE0 = regular_file(passout);
    if (spE0 != 1) {
        goto block_2242;
    }
    unlink(passout);
    goto block_2245;
block_2242:
    if (spE0 == 0) {
        goto block_2244;
    }
    error(2, NULL, 0, NULL, 0, "%s does not exist or is not stat(2)-able. Not deleted (if it exists) even though as1 failed.\n", passout);
    goto block_2245;
block_2244:
    error(2, NULL, 0, NULL, 0, "%s is not a regular file, not deleted even though as1 failed.\n", passout);
block_2245:
    if (tmpst == 0) {
        goto block_2247;
    }
    unlink(symtab);
block_2247:
    temp_t1_13 = tmp_uldobj;
    if (temp_t1_13 == NULL) {
        goto block_2271;
    }
    unlink(temp_t1_13);
    goto block_2270;
block_2249:
    if (ddoptflag != 1) {
        goto block_2254;
    }
    if (compiler != 3) {
        goto block_2254;
    }
    if (ddoptinfo == 0) {
        goto block_2254;
    }
    if (Oflag < 2) {
        goto block_2254;
    }
    unlink(tempstr->unk_68);
block_2254:
    if ((u8) srcsuf == 0x47) {
        goto block_2257;
    }
    if (Kflag != 0) {
        goto block_2257;
    }
    unlink(passin);
block_2257:
    if (tmpst == 0) {
        goto block_2260;
    }
    if (Kflag != 0) {
        goto block_2260;
    }
    unlink(symtab);
block_2260:
    if (compiler != 3) {
        goto block_2265;
    }
    if (sp11C == 0) {
        goto block_2265;
    }
    temp_t7_21 = (u8) srcsuf;
    if (temp_t7_21 == 0x66) {
        goto block_2265;
    }
    if (temp_t7_21 == 0x46) {
        goto block_2265;
    }
    D_1000BF74 = sp11C;
    relocate_passes("f", NULL, NULL);
block_2265:
    if (compiler != 1) {
        goto block_2271;
    }
    temp_t9_19 = c_compiler_choice;
    if (temp_t9_19 == 2) {
        goto block_2268;
    }
    if (temp_t9_19 != 3) {
        goto block_2271;
    }
block_2268:
    if (no_prelink != 0) {
        goto block_2271;
    }
    update_instantiation_info_file(srcfiles.entries[var_s0_3], passout);
block_2270:
block_2271:
    var_s0_3 += 1;
    if (var_s0_3 < srcfiles.length) {
        goto loop_363;
    }
    if (uload != 0) {
        goto loop_363;
    }
block_2273:
    srcsuf = 0;
    if (compiler != 4) {
        goto block_2278;
    }
    if (runerror == 0) {
        goto block_2276;
    }
    exit(1);
    goto block_2277;
block_2276:
    exit(0);
block_2277:
block_2278:
    if (NoMoreOptions == 0) {
        goto block_2284;
    }
    var_s0_4 = 0;
    if (objfiles.length <= 0) {
        goto block_2284;
    }
loop_2280:
    temp_t5_13 = objfiles.entries;
    if ((u8) *temp_t5_13[var_s0_4] != 0x2D) {
        goto block_2283;
    }
    if (strchr(temp_t5_13[var_s0_4], 0x2EU) == NULL) {
        goto block_2283;
    }
    objfiles.entries[var_s0_4] = func_00433534(objfiles.entries[var_s0_4]);
block_2283:
    var_s0_4 += 1;
    if (var_s0_4 < objfiles.length) {
        goto loop_2280;
    }
block_2284:
    if (cflag != 0) {
        goto block_2608;
    }
    if (Sflag != 0) {
        goto block_2608;
    }
    if (Eflag != 0) {
        goto block_2608;
    }
    if (Pflag != 0) {
        goto block_2608;
    }
    if (jflag != 0) {
        goto block_2608;
    }
    if (runerror != 0) {
        goto block_2608;
    }
    if (objfiles.length == 0) {
        goto block_2608;
    }
    if (Hchar != 0) {
        goto block_2608;
    }
    if (nocode != 0) {
        goto block_2608;
    }
    if (old_non_shared == 0) {
        goto block_2297;
    }
    if (mips2flag == 0) {
        goto block_2297;
    }
    if (kpic_flag != 0) {
        goto block_2297;
    }
    error(1, NULL, 0, NULL, 0, "can't mix -mips2 with shared for ucode compilers, try using -non_shared\n");
    default_call_shared = 0;
    call_shared = 0;
block_2297:
    if (old_non_shared == 0) {
        goto block_2300;
    }
    if (mips3flag == 0) {
        goto block_2300;
    }
    error(1, NULL, 0, NULL, 0, "can't mix ucode 32-bit -mips3 with shared\n");
    default_call_shared = 0;
    call_shared = 0;
    exit(2);
block_2300:
    if (old_non_shared == 0) {
        goto block_2303;
    }
    if (coff_spec == 0) {
        goto block_2303;
    }
    error(1, NULL, 0, NULL, 0, "can't mix -coff with shared, try using -non_shared\n");
    default_call_shared = 0;
    call_shared = 0;
    exit(2);
block_2303:
    if (old_non_shared == 0) {
        goto block_2306;
    }
    if (excpt_flag == 0) {
        goto block_2306;
    }
    error(1, NULL, 0, NULL, 0, "can't mix -excpt with shared, try using -non_shared\n");
    default_call_shared = 0;
    call_shared = 0;
    exit(2);
block_2306:
    if (old_non_shared != 0) {
        goto block_2308;
    }
    if (non_shared == 0) {
        goto block_2310;
    }
block_2308:
    if (make_edison_shlib == 0) {
        goto block_2310;
    }
    error(1, NULL, 0, NULL, 0, "can't mix -shared with -non_shared\n");
    exit(2);
block_2310:
    if (cordflag == 0) {
        goto block_2313;
    }
    if (make_edison_shlib == 0) {
        goto block_2313;
    }
    error(1, NULL, 0, NULL, 0, "can't mix -shared with -cord\n");
    exit(2);
block_2313:
    if (compiler != 1) {
        goto block_2324;
    }
    temp_t5_14 = c_compiler_choice;
    if (temp_t5_14 == 2) {
        goto block_2316;
    }
    if (temp_t5_14 != 3) {
        goto block_2324;
    }
block_2316:
    if (no_prelink != 0) {
        goto block_2324;
    }
    execlist.length = 0;
    addstr(&execlist, "edg_prelink");
    addstr(&execlist, "-fSGI");
    addlist(&execlist, &prelinkerflags);
    if (vflag != 0) {
        goto block_2319;
    }
    if (verbose_prelink == 0) {
        goto block_2320;
    }
block_2319:
    addstr(&execlist, "-v");
block_2320:
    add_prelinker_objects(&execlist, &objfiles);
    if (xpg_flag == 0) {
        goto block_2322;
    }
    add_prelinker_objects(&execlist, &dashlfiles);
block_2322:
    if (run(prelinker, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_2324;
    }
    runerror += 1;
    goto block_2589;
block_2324:
    execlist.length = 0;
    addstr(&execlist, LD);
    if (kpic_flag == 0) {
        goto block_2328;
    }
    if (irix4 != 0) {
        goto block_2328;
    }
    if (coff_spec != 0) {
        goto block_2328;
    }
    addstr(&ldflags, "-KPIC");
block_2328:
    if (non_shared == 0) {
        goto block_2333;
    }
    if (non_shared_emitted != 0) {
        goto block_2333;
    }
    if (mips2flag != 0) {
        goto block_2342;
    }
    if (mips3flag != 0) {
        goto block_2342;
    }
    addstr(&ldflags, "-non_shared");
    non_shared_emitted = 1;
    goto block_2342;
block_2333:
    if (call_shared != 0) {
        goto block_2335;
    }
    if (make_edison_shlib == 0) {
        goto block_2342;
    }
block_2335:
    if (transitive_link == 0) {
        goto block_2337;
    }
    addstr(&ldflags, "-transitive_link");
    goto block_2341;
block_2337:
    if (full_transitive_link == 0) {
        goto block_2339;
    }
    addstr(&ldflags, "-full_transitive_link");
    goto block_2341;
block_2339:
    if (no_transitive_link == 0) {
        goto block_2342;
    }
    addstr(&ldflags, "-no_transitive_link");
block_2341:
block_2342:
    if (quickstart_info == 0) {
        goto block_2344;
    }
    addstr(&ldflags, "-quickstart_info");
block_2344:
    if (elfflag == 0) {
        goto block_2347;
    }
    if (coff_spec != 0) {
        goto block_2347;
    }
    addstr(&execlist, "-elf");
block_2347:
    if (tfp_flag == 0) {
        goto block_2349;
    }
    addstr(&execlist, "-allow_jump_at_eop");
block_2349:
    if (compiler != 1) {
        goto block_2352;
    }
    if (c_compiler_choice != 3) {
        goto block_2352;
    }
    addstr(&execlist, "-delta");
block_2352:
    if (cordflag == 0) {
        goto block_2354;
    }
    addstr(&execlist, "-o");
    temp_t2_16 = tempstr->unk_58;
    passout = temp_t2_16;
    addstr(&execlist, temp_t2_16);
    goto block_2356;
block_2354:
    if (outfile == NULL) {
        goto block_2357;
    }
    addstr(&execlist, "-o");
    addstr(&execlist, outfile);
block_2356:
block_2357:
    temp_t5_15 = targetsex;
    if (gethostsex() == temp_t5_15) {
        goto block_2362;
    }
    if (temp_t5_15 != 0) {
        goto block_2360;
    }
    addstr(&execlist, "-EB");
    goto block_2361;
block_2360:
    addstr(&execlist, "-EL");
block_2361:
block_2362:
    if (make_edison_shlib == 0) {
        goto block_2364;
    }
    addstr(&execlist, "-shared");
block_2364:
    if (compiler != 1) {
        goto block_2368;
    }
    temp_t3_16 = c_compiler_choice;
    if (temp_t3_16 == 2) {
        goto block_2367;
    }
    if (temp_t3_16 != 3) {
        goto block_2368;
    }
block_2367:
    add_cxx_symbol_options();
block_2368:
    if (irix4 == 0) {
        goto block_2373;
    }
    addstr(&execlist, mkstr("-L", NULL));
    if (non_shared == 0) {
        goto block_2371;
    }
    addstr(&execlist, mkstr("-L", "/usr/irix4/", "usr/lib/nonshared/", NULL));
    crtx = mkstr(comp_host_root, "usr/lib/nonshared/", CRTX, NULL);
    var_v0_17 = mkstr(comp_host_root, "usr/lib/nonshared/", "crtn.o", NULL);
    goto block_2372;
block_2371:
    addstr(&execlist, mkstr("-L", "/usr/irix4/", "usr/lib/", NULL));
    crtx = mkstr(comp_host_root, "usr/lib/", CRTX, NULL);
    var_v0_17 = mkstr(comp_host_root, "usr/lib/", "crtn.o", NULL);
block_2372:
    crtn = var_v0_17;
block_2373:
    if (svr4_systype == 0) {
        goto block_2387;
    }
    if (compchoice != 1) {
        goto block_2376;
    }
    addstr(&execlist, mkstr("-SYSTYPE_SVR4", NULL, NULL));
block_2376:
    addstr(&execlist, mkstr("-_SYSTYPE_SVR4", NULL, NULL));
    if (call_shared != 0) {
        goto block_2378;
    }
    if (make_edison_shlib == 0) {
        goto block_2387;
    }
block_2378:
    addstr(&execlist, "-require_dynamic_link");
    addstr(&execlist, "_rld_new_interface");
    if (ignore_unresolved_flag == 0) {
        goto block_2380;
    }
    addstr(&execlist, "-ignore_unresolved");
    goto block_2386;
block_2380:
    if (no_unresolved_flag == 0) {
        goto block_2382;
    }
    addstr(&execlist, "-no_unresolved");
    goto block_2386;
block_2382:
    if (default_svr4 != 0) {
        goto block_2384;
    }
    if (make_edison_shlib == 0) {
        goto block_2385;
    }
block_2384:
    addstr(&execlist, "-ignore_unresolved");
    goto block_2386;
block_2385:
    addstr(&execlist, "-no_unresolved");
block_2386:
block_2387:
    if (fiveflag == 0) {
        goto block_2389;
    }
    addstr(&execlist, mkstr("-L", runlib, NULL));
block_2389:
    temp_t9_20 = allBstring;
    if (temp_t9_20 == NULL) {
        goto block_2392;
    }
    if ((u8) *temp_t9_20 == 0) {
        goto block_2392;
    }
    addstr(&execlist, mkstr("-B", temp_t9_20, NULL));
block_2392:
    if (cordflag == 0) {
        goto block_2394;
    }
    addstr(&execlist, "-r");
    addstr(&execlist, "-d");
    addstr(&execlist, "-z");
block_2394:
    if (irix4 == 0) {
        goto block_2396;
    }
    addstr(&execlist, "-G");
    goto block_2397;
block_2396:
    addstr(&execlist, mkstr("-Wx", ",", "-G", NULL));
block_2397:
    addstr(&execlist, Gnum);
    addlist(&execlist, &ldflags);
    addlist(&execlist, &nldflags);
    if (mips2flag == 0) {
        goto block_2407;
    }
    if (sp148 != 0) {
        goto block_2407;
    }
    if (strcmp("/", comp_target_root) == 0) {
        goto block_2403;
    }
    if (non_shared == 0) {
        goto block_2402;
    }
    addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "nonshared", NULL));
    goto block_2406;
block_2402:
    addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "", NULL));
    goto block_2406;
block_2403:
    if (non_shared == 0) {
        goto block_2405;
    }
    addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "nonshared", NULL));
    goto block_2406;
block_2405:
    addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "", NULL));
block_2406:
block_2407:
    if (mips1flag == 0) {
        goto block_2419;
    }
    if (sp148 != 0) {
        goto block_2419;
    }
    if (strcmp("/", comp_target_root) == 0) {
        goto block_2414;
    }
    if (non_shared == 0) {
        goto block_2412;
    }
    addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "nonshared", NULL));
    goto block_2418;
block_2412:
    if (abi_flag != 0) {
        goto block_2419;
    }
    addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "", NULL));
    goto block_2418;
block_2414:
    if (non_shared == 0) {
        goto block_2416;
    }
    addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "nonshared", NULL));
    goto block_2418;
block_2416:
    if (abi_flag != 0) {
        goto block_2419;
    }
    addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "", NULL));
block_2418:
block_2419:
    if (strcmp("/", comp_target_root) == 0) {
        goto block_2428;
    }
    if (Lflag != 0) {
        goto block_2433;
    }
    if (compiler != 1) {
        goto block_2424;
    }
    if (c_compiler_choice != 3) {
        goto block_2424;
    }
    addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/DCC", currcomp, NULL));
block_2424:
    if (non_shared == 0) {
        goto block_2426;
    }
    addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/nonshared/", currcomp, NULL));
    goto block_2432;
block_2426:
    if (abi_flag != 0) {
        goto block_2433;
    }
    addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, NULL));
    goto block_2432;
block_2428:
    if (Lflag != 0) {
        goto block_2433;
    }
    if (compiler != 1) {
        goto block_2433;
    }
    if (c_compiler_choice != 3) {
        goto block_2433;
    }
    addstr(&execlist, mkstr("-L", runlib, "usr/lib/DCC", currcomp, NULL));
block_2432:
block_2433:
    if (make_edison_shlib == 0) {
        goto block_2458;
    }
    if (compiler != 1) {
        goto block_2438;
    }
    temp_t0_12 = c_compiler_choice;
    if (temp_t0_12 == 2) {
        goto block_2437;
    }
    if (temp_t0_12 != 3) {
        goto block_2438;
    }
block_2437:
    addstr(&execlist, cxx_init);
block_2438:
    if (compiler != 1) {
        goto block_2441;
    }
    if (c_compiler_choice != 3) {
        goto block_2441;
    }
    addstr(&execlist, delta_init);
block_2441:
    addlist(&execlist, &objfiles);
    if (xpg_flag == 0) {
        goto block_2443;
    }
    addlist(&execlist, &dashlfiles);
block_2443:
    if (nodeflib != 0) {
        goto block_2554;
    }
    if (compiler != 1) {
        goto block_2455;
    }
    temp_t5_16 = c_compiler_choice;
    if (temp_t5_16 == 2) {
        goto block_2447;
    }
    if (temp_t5_16 != 3) {
        goto block_2455;
    }
block_2447:
    var_s3_9 = D_1000BF90 == 0;
    if (var_s3_9 == 0) {
        goto block_2449;
    }
    var_s3_9 = strcmp(LD, "old_ld") != 0;
block_2449:
    spDC = var_s3_9;
    if (spDC == 0) {
        goto block_2451;
    }
    addstr(&execlist, "-dont_warn_unused");
block_2451:
    if (exception_handling == 0) {
        goto block_2453;
    }
    addstr(&execlist, "-lCsup");
block_2453:
    addstr(&execlist, "-lC");
    if (spDC == 0) {
        goto block_2455;
    }
    addstr(&execlist, "-warn_unused");
block_2455:
    if (xpg_flag == 0) {
        goto block_2457;
    }
    addstr(&execlist, "-dont_warn_unused");
    addstr(&execlist, "-lgen");
    addstr(&execlist, "-warn_unused");
block_2457:
    addstr(&execlist, "-lc");
    goto block_2553;
block_2458:
    addstr(&execlist, "-nocount");
    addstr(&execlist, crtx);
    if (compiler != 1) {
        goto block_2462;
    }
    temp_t9_21 = c_compiler_choice;
    if (temp_t9_21 == 2) {
        goto block_2461;
    }
    if (temp_t9_21 != 3) {
        goto block_2462;
    }
block_2461:
    addstr(&execlist, cxx_init);
block_2462:
    if (compiler != 1) {
        goto block_2465;
    }
    if (c_compiler_choice != 3) {
        goto block_2465;
    }
    addstr(&execlist, delta_init);
block_2465:
    addstr(&execlist, "-count");
    addlist(&execlist, &objfiles);
    if (xpg_flag == 0) {
        goto block_2467;
    }
    addlist(&execlist, &dashlfiles);
block_2467:
    addlist(&execlist, &ldZflags);
    if (ansichoice != 0) {
        goto block_2471;
    }
    if (compiler != 1) {
        goto block_2471;
    }
    if (irix4 != 0) {
        goto block_2471;
    }
    addstr(&execlist, "-cckr");
block_2471:
    addstr(&execlist, "-nocount");
    if (nodeflib != 0) {
        goto block_2549;
    }
    if (compiler == 2) {
        goto block_2474;
    }
    if (haspascal == 0) {
        goto block_2475;
    }
block_2474:
    addspacedstr(&execlist, libp);
    addspacedstr(&execlist, libxmalloc);
    addspacedstr(&execlist, libexc);
    addspacedstr(&execlist, libmld);
block_2475:
    if (compiler == 3) {
        goto block_2477;
    }
    if (hasfortran == 0) {
        goto block_2486;
    }
block_2477:
    if (mp_flag == 0) {
        goto block_2479;
    }
    addspacedstr(&execlist, libI77_mp);
block_2479:
    if (non_shared != 0) {
        goto block_2481;
    }
    if (irix4 == 0) {
        goto block_2484;
    }
block_2481:
    addspacedstr(&execlist, libF77);
    addspacedstr(&execlist, libm);
    addspacedstr(&execlist, libU77);
    if (D_1000C130 == 0) {
        goto block_2483;
    }
    spD8 = strlen(libI77);
    spD4 = malloc(spD8 + 2);
    memcpy(spD4, libI77, spD8);
    spD4[spD8] = 0x5F;
    spD4[spD8].unk_1 = 0x73;
    spD4[spD8].unk_2 = 0;
    libI77 = spD4;
block_2483:
    addspacedstr(&execlist, libI77);
    addspacedstr(&execlist, libisam);
    goto block_2485;
block_2484:
    addspacedstr(&execlist, libftn);
    addspacedstr(&execlist, libm);
block_2485:
block_2486:
    if (compiler != 5) {
        goto block_2488;
    }
    addstr(&execlist, libpl1);
    addspacedstr(&execlist, libxmalloc);
    addstr(&execlist, "-ltermcap");
    addspacedstr(&execlist, libexc);
    addspacedstr(&execlist, libmld);
block_2488:
    temp_t8_17 = compiler;
    if (temp_t8_17 == 2) {
        goto block_2495;
    }
    if (hasfortran == 0) {
        goto block_2491;
    }
    if (temp_t8_17 != 3) {
        goto block_2495;
    }
block_2491:
    if (haspascal != 0) {
        goto block_2495;
    }
    if (haspl1 != 0) {
        goto block_2495;
    }
    temp_t6_19 = compiler;
    if (temp_t6_19 == 5) {
        goto block_2495;
    }
    if (temp_t6_19 != 6) {
        goto block_2496;
    }
block_2495:
    addspacedstr(&execlist, libm);
block_2496:
    if (pgflag == 0) {
        goto block_2498;
    }
    addspacedstr(&execlist, libgprof);
    goto block_2500;
block_2498:
    if (pflag == 0) {
        goto block_2501;
    }
    addspacedstr(&execlist, libprof);
block_2500:
block_2501:
    if (sixty4bitflag != 0) {
        goto block_2504;
    }
    ldw_file = fopen(libdw_path, "r");
    if (ldw_file == NULL) {
        goto block_2504;
    }
    addspacedstr(&execlist, libdw);
block_2504:
    if (!(cmp_flag & 0x10000)) {
        goto block_2507;
    }
    addstr(&execlist, libc_mp);
    if (compiler != 1) {
        goto block_2507;
    }
    addstr(&execlist, "-lkapio");
block_2507:
    if (run_sopt == 0) {
        goto block_2510;
    }
    if (compiler != 1) {
        goto block_2510;
    }
    addstr(&execlist, "-lkapio");
block_2510:
    if (compiler != 3) {
        goto block_2526;
    }
    if (D_1000C130 != 2) {
        goto block_2515;
    }
    addstr(&execlist, "-lc_s");
    if (xpg_flag == 0) {
        goto block_2514;
    }
    addstr(&execlist, "-dont_warn_unused");
    addstr(&execlist, "-lgen");
    addstr(&execlist, "-warn_unused");
block_2514:
    addstr(&execlist, "-lc");
    goto block_2548;
block_2515:
    if (irix4 == 0) {
        goto block_2518;
    }
    if (B_1000ED74 != 0) {
        goto block_2518;
    }
    addstr(&execlist, "-lmpc");
block_2518:
    if (B_1000ED2C == 0) {
        goto block_2520;
    }
    addstr(&execlist, "-lc_s");
    goto block_2522;
block_2520:
    if (B_1000ED30 == 0) {
        goto block_2523;
    }
    addstr(&execlist, "-lc_s");
block_2522:
block_2523:
    if (xpg_flag == 0) {
        goto block_2525;
    }
    addstr(&execlist, "-dont_warn_unused");
    addstr(&execlist, "-lgen");
    addstr(&execlist, "-warn_unused");
block_2525:
    addstr(&execlist, "-lc");
    goto block_2548;
block_2526:
    if (irix4 == 0) {
        goto block_2529;
    }
    if (!(cmp_flag & 0x10000)) {
        goto block_2529;
    }
    addstr(&execlist, "-lmpc");
block_2529:
    if (compiler != 1) {
        goto block_2540;
    }
    temp_t1_14 = c_compiler_choice;
    if (temp_t1_14 == 2) {
        goto block_2532;
    }
    if (temp_t1_14 != 3) {
        goto block_2540;
    }
block_2532:
    var_s3_10 = D_1000BF90 == 0;
    if (var_s3_10 == 0) {
        goto block_2534;
    }
    var_s3_10 = strcmp(LD, "old_ld") != 0;
block_2534:
    spD0 = var_s3_10;
    if (spD0 == 0) {
        goto block_2536;
    }
    addstr(&execlist, "-dont_warn_unused");
block_2536:
    if (exception_handling == 0) {
        goto block_2538;
    }
    addstr(&execlist, "-lCsup");
block_2538:
    addstr(&execlist, "-lC");
    if (spD0 == 0) {
        goto block_2540;
    }
    addstr(&execlist, "-warn_unused");
block_2540:
    if (B_1000ED2C == 0) {
        goto block_2542;
    }
    addstr(&execlist, "-lc_s");
    goto block_2544;
block_2542:
    if (B_1000ED30 == 0) {
        goto block_2545;
    }
    addstr(&execlist, "-lc_s");
block_2544:
block_2545:
    if (xpg_flag == 0) {
        goto block_2547;
    }
    addstr(&execlist, "-dont_warn_unused");
    addstr(&execlist, "-lgen");
    addstr(&execlist, "-warn_unused");
block_2547:
    addstr(&execlist, "-lc");
block_2548:
block_2549:
    if (crtn_required == 0) {
        goto block_2551;
    }
    addstr(&execlist, crtn);
block_2551:
    temp_t6_20 = rls_id_object;
    if (temp_t6_20 == NULL) {
        goto block_2554;
    }
    addstr(&execlist, temp_t6_20);
block_2553:
block_2554:
    passin = NULL;
    if (run(ld, execlist.entries, NULL, NULL, tempstr->unk_80) == 0) {
        goto block_2566;
    }
    runerror += 1;
    if (Kflag != 0) {
        goto block_2566;
    }
    if (strcmp(LD, "old_ld") == 0) {
        goto block_2560;
    }
    if (compiler != 1) {
        goto block_2564;
    }
    temp_t8_18 = c_compiler_choice;
    if (temp_t8_18 == 2) {
        goto block_2560;
    }
    if (temp_t8_18 != 3) {
        goto block_2564;
    }
block_2560:
    temp_t2_17 = outfile;
    if (temp_t2_17 == NULL) {
        goto block_2562;
    }
    unlink(temp_t2_17);
    goto block_2563;
block_2562:
    unlink("a.out");
block_2563:
block_2564:
    temp_t9_22 = tmp_uldobj;
    if (temp_t9_22 == NULL) {
        goto block_2566;
    }
    unlink(temp_t9_22);
block_2566:
    temp_t5_17 = tempstr->unk_80;
    if (temp_t5_17 == NULL) {
        goto block_2571;
    }
    if (stat(temp_t5_17, &sp48) != 0) {
        goto block_2570;
    }
    if (sp78 <= 0) {
        goto block_2570;
    }
    execlist.length = 0;
    addstr(&execlist, "c++filt");
    run(filter, execlist.entries, tempstr->unk_80, NULL, NULL);
block_2570:
    unlink(tempstr->unk_80);
block_2571:
    if (runerror != 0) {
        goto block_2582;
    }
    if (compiler != 1) {
        goto block_2582;
    }
    temp_t8_19 = c_compiler_choice;
    if (temp_t8_19 == 2) {
        goto block_2575;
    }
    if (temp_t8_19 != 3) {
        goto block_2582;
    }
block_2575:
    execlist.length = 0;
    addstr(&execlist, patch);
    if (vflag == 0) {
        goto block_2577;
    }
    addstr(&execlist, "-d");
block_2577:
    temp_t9_23 = outfile;
    if (temp_t9_23 == NULL) {
        goto block_2579;
    }
    addstr(&execlist, temp_t9_23);
    goto block_2580;
block_2579:
    addstr(&execlist, "a.out");
block_2580:
    if (run(patch, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_2582;
    }
    runerror += 1;
block_2582:
    if (runerror != 0) {
        goto block_2589;
    }
    if (do_strip == 0) {
        goto block_2589;
    }
    execlist.length = 0;
    addstr(&execlist, strip);
    temp_t0_13 = outfile;
    if (temp_t0_13 == NULL) {
        goto block_2586;
    }
    addstr(&execlist, temp_t0_13);
    goto block_2587;
block_2586:
    addstr(&execlist, "a.out");
block_2587:
    if (run(strip, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_2589;
    }
    runerror += 1;
block_2589:
    if (cordflag == 0) {
        goto block_2603;
    }
    if (runerror != 0) {
        goto block_2603;
    }
    execlist.length = 0;
    addstr(&execlist, "cord");
    if (vflag == 0) {
        goto block_2593;
    }
    addstr(&execlist, "-v");
block_2593:
    addlist(&execlist, &cordflags);
    temp_t6_21 = outfile;
    if (temp_t6_21 == NULL) {
        goto block_2595;
    }
    passout = temp_t6_21;
    goto block_2596;
block_2595:
    passout = "a.out";
block_2596:
    addstr(&execlist, "-o");
    addstr(&execlist, passout);
    addstr(&execlist, tempstr->unk_58);
    if (feedlist.length == 0) {
        goto block_2598;
    }
    addlist(&execlist, &feedlist);
    goto block_2599;
block_2598:
    addstr(&execlist, mkstr(passout, ".fb", NULL));
block_2599:
    if (run(cord, execlist.entries, NULL, NULL, NULL) == 0) {
        goto block_2601;
    }
    runerror += 1;
    unlink(passout);
    unlink(tempstr->unk_58);
    goto block_2602;
block_2601:
    unlink(tempstr->unk_58);
block_2602:
block_2603:
    if (runerror != 0) {
        goto block_2608;
    }
    if (srcfiles.length != 1) {
        goto block_2608;
    }
    if (nobjs != 1) {
        goto block_2608;
    }
    if (Kflag != 0) {
        goto block_2608;
    }
    unlink(mksuf(*srcfiles.entries, 0x6FU));
block_2608:
    temp_t3_17 = tmp_uldobj;
    if (temp_t3_17 == NULL) {
        goto block_2610;
    }
    unlink(temp_t3_17);
block_2610:
    if (editflag == 0) {
        goto block_2613;
    }
    unlink(errout);
    if (editflag != 2) {
        goto block_2613;
    }
    unlink(tempstr->unk_64);
block_2613:
    if (compiler != 1) {
        goto block_2616;
    }
    if (gflag < 2) {
        goto block_2616;
    }
    unlink(tempstr->unk_84);
block_2616:
    if (runerror == 0) {
        goto block_2618;
    }
    exit(1);
block_2618:
    return 0;
}

void process_config(s32 arg0, s8** arg1) {
    s8* sp1144;
    s8* sp1140;
    FILE* sp113C;
    s8 sp13C;
    s32 sp138;
    s32 temp_s0;
    s32 var_s0;
    s8* temp_t7;
    s8* var_s1;
    u8 temp_t7_2;
    u8 temp_t8;

    var_s0 = 1;
    sp1144 = comp_target_root;
    if (arg0 > 1) {
loop_1:
        if (strcmp(*(arg1 + (var_s0 * 4)), "-systype") == 0) {
            temp_s0 = var_s0 + 1;
            if (temp_s0 >= arg0) {
                error(1, NULL, 0, NULL, 0, "-systype must have an argument\n");
                exit(2);
            }
            user_systype = 1;
            temp_t7 = *(arg1 + (temp_s0 * 4));
            systype = temp_t7;
            if (strcmp(temp_t7, "svr4") == 0) {
                svr4_systype = 1;
            } else {
                error(1, NULL, 0, NULL, 0, "only systype svr4 allowed\n");
                exit(2);
            }
            if ((strcmp(systype, "svr4") != 0) && (strcmp(systype, "bsd43") != 0) && (strcmp(systype, "svr3") != 0) && (strcmp(systype, "sysv") != 0) && (fopen(strcat("/", systype), "r") == NULL) && (systype_warn == 0)) {
                error(2, NULL, 0, NULL, 0, "This systype doesn't exist on this machine; changed systype to svr3.\n");
                systype_warn = 1;
                systype = "svr3";
            }
            if (svr4_systype == 0) {
                sp1144 = mkstr(comp_target_root, systype, "/", NULL);
            }
        } else {
            var_s0 += 1;
            if (var_s0 < arg0) {
                goto loop_1;
            }
        }
    }
    if (user_systype == 0) {
        sp1144 = mkstr(comp_target_root, systype, "/", NULL);
    }
    user_systype = 0;
    sp1140 = mkstr(sp1144, "usr/lib/", currcomp, "comp.config", NULL);
    sp113C = fopen(sp1140, "r");
    if ((sp113C != NULL) && (fgets(&sp13C, 0x1000, sp113C) != NULL)) {
        if ((&sp13C)[strlen(&sp13C)].unk_-1 == 0xA) {
            (&sp13C)[strlen(&sp13C)].unk_-1 = 0;
        }
        var_s1 = &sp13C;
        sp138 = 0;
        if ((u8) *var_s1 != 0) {
            do {
                if (((u8) *var_s1 != 0) && (((u8) *var_s1 == 0x20) || ((u8) *var_s1 == 9))) {
loop_27:
                    temp_t7_2 = var_s1->unk_1;
                    var_s1 += 1;
                    if (temp_t7_2 != 0) {
                        if (((u8) *var_s1 == 0x20) || ((u8) *var_s1 == 9)) {
                            goto loop_27;
                        }
                    }
                }
                if ((u8) *var_s1 != 0) {
                    (&sp38[0])[sp138] = var_s1;
                    sp138 += 1;
                }
                if (((u8) *var_s1 != 0) && ((u8) *var_s1 != 0x20) && ((u8) *var_s1 != 9)) {
loop_35:
                    temp_t8 = var_s1->unk_1;
                    var_s1 += 1;
                    if ((temp_t8 != 0) && ((u8) *var_s1 != 0x20)) {
                        if ((u8) *var_s1 != 9) {
                            goto loop_35;
                        }
                    }
                }
                if ((u8) *var_s1 != 0) {
                    *var_s1 = 0;
                    var_s1 += 1;
                }
            } while ((u8) *var_s1 != 0);
        }
        parse_command(sp138, &sp38[0]);
    }
}

void add_info(s8* arg0) {
    addstr(&upasflags, arg0);
    addstr(&fcomflags, arg0);
    addstr(&ulpiflags, arg0);
    addstr(&uopt0flags, arg0);
    addstr(&ddoptflags, arg0);
    addstr(&optflags, arg0);
    addstr(&umergeflags, arg0);
    addstr(&uloopflags, arg0);
    addstr(&genflags, arg0);
    addstr(&asflags, arg0);
    addstr(&ldflags, arg0);
}

void parse_command(s32 arg0, s8** arg1) {
    s8* sp15C;
    s8* sp158;
    s8* sp154;
    s8 sp153;
    s32 sp14C;
    s8* sp148;
    s8* sp144;
    s8* sp140;
    s8* sp134;
    s8* sp130;
    s8* sp12C;
    s8* sp128;
    s8* sp124;
    s8* sp120;
    s8* sp11C;
    s8* sp118;
    s32 sp114;
    s32 sp110;
    u8* sp10C;
    s32 sp108;
    s8* sp104;
    u8* sp100;
    s8* spFC;
    ? sp74;
    s8** sp70;
    s8** sp6C;
    s8* sp68;
    s8* sp64;
    s32 sp60;
    s32 sp5C;
    s8* sp58;
    u32 sp54;
    s32 temp_s4;
    s32 temp_t0_2;
    s32 temp_t1_3;
    s32 temp_t1_4;
    s32 temp_t1_7;
    s32 temp_t3;
    s32 temp_t3_4;
    s32 temp_t4_10;
    s32 temp_t4_11;
    s32 temp_t4_12;
    s32 temp_t4_3;
    s32 temp_t4_8;
    s32 temp_t4_9;
    s32 temp_t5_8;
    s32 temp_t6_6;
    s32 temp_t7_10;
    s32 temp_t7_11;
    s32 temp_t7_5;
    s32 temp_t8_4;
    s32 temp_t8_5;
    s32 temp_t9_3;
    s32 temp_t9_4;
    s32 temp_t9_6;
    s32 temp_t9_7;
    s32 temp_t9_8;
    s32 temp_t9_9;
    s32 var_s0;
    s32 var_s1;
    s32 var_t2;
    s32* var_at;
    s32* var_at_2;
    s8* temp_t0_3;
    s8* temp_t1_5;
    s8* temp_t1_6;
    s8* temp_t2;
    s8* temp_t3_6;
    s8* temp_t4_13;
    s8* temp_t4_4;
    s8* temp_t5;
    s8* temp_t5_6;
    s8* temp_t5_7;
    s8* temp_t5_9;
    s8* temp_t6_4;
    s8* temp_t6_7;
    s8* temp_t6_8;
    s8* temp_t6_9;
    s8* temp_t7_6;
    s8* temp_t7_8;
    s8* temp_t8;
    s8* temp_t8_6;
    s8* temp_t8_8;
    s8* temp_t8_9;
    s8* temp_t9_5;
    s8* temp_v0;
    s8* temp_v0_2;
    s8* var_s2;
    s8* var_s2_10;
    s8* var_s2_7;
    s8* var_s2_8;
    s8* var_s2_9;
    s8* var_s3;
    s8* var_v0;
    s8* var_v0_2;
    u8 temp_s4_2;
    u8 temp_s4_3;
    u8 temp_t1;
    u8 temp_t1_2;
    u8 temp_t2_2;
    u8 temp_t2_3;
    u8 temp_t3_2;
    u8 temp_t3_5;
    u8 temp_t4_14;
    u8 temp_t4_2;
    u8 temp_t4_5;
    u8 temp_t4_6;
    u8 temp_t4_7;
    u8 temp_t5_2;
    u8 temp_t5_4;
    u8 temp_t5_5;
    u8 temp_t6;
    u8 temp_t6_5;
    u8 temp_t7;
    u8 temp_t7_2;
    u8 temp_t7_3;
    u8 temp_t7_4;
    u8 temp_t7_7;
    u8 temp_t7_9;
    u8 temp_t8_10;
    u8 temp_t8_2;
    u8 temp_t8_3;
    u8 temp_t9;
    u8* temp_t0;
    u8* temp_t2_4;
    u8* temp_t3_3;
    u8* temp_t4;
    u8* temp_t5_3;
    u8* temp_t6_2;
    u8* temp_t6_3;
    u8* temp_t8_7;
    u8* temp_t9_2;
    u8* var_s2_2;
    u8* var_s2_3;
    u8* var_s2_4;
    u8* var_s2_5;
    u8* var_s2_6;

    var_s1 = saved_reg_s1;
    sp15C = NULL;
    sp158 = NULL;
    sp154 = NULL;
    sp153 = 0;
    sp14C = 1;
    sp148 = getenv("SGI_IRIX4");
    if (sp148 != NULL) {
        irix4 = 1;
        comp_host_root = "/usr/irix4/";
        systype = "";
        elfflag = 0;
        svr4_systype = 0;
        call_shared = 0;
        non_shared = 0;
        old_non_shared = 0;
        default_call_shared = 0;
        Gnum = "8";
        kpic_flag = 0;
        mips_abi = 0;
        runlib = "/usr/irix4/";
        relocate_passes("pKfjrsulmvocabtyz", NULL, NULL);
    }
    var_s0 = 0;
    if (arg0 > 0) {
        do {
            if ((**(arg1 + (var_s0 * 4)) == 0x2D) && ((NoMoreOptions == 0) || (strchr(*(arg1 + (var_s0 * 4)), 0x2EU) == NULL))) {
                temp_t7 = (*(arg1 + (var_s0 * 4)))->unk_1;
                switch (temp_t7) {                  /* switch 1 */
                    case 0x23:                      /* switch 1 */
                        error(2, NULL, 0, NULL, 0, "-# is not supported. Use -v to see compiler passesn");
                        break;
                    case 0x31:                      /* switch 1 */
                        if ((compiler == 3) && ((*(arg1 + (var_s0 * 4)))->unk_2 == 0)) {
                            mp_onetripflag = 1;
                            addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x33:                      /* switch 1 */
                        if ((strcmp(*(arg1 + (var_s0 * 4)), "-32bit") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-32") == 0)) {
                            thirty2bitflag = 1;
                            mips_abi = 1;
                        }
                        break;
                    case 0x35:                      /* switch 1 */
                        error(2, NULL, 0, NULL, 0, "-5 not supported\n");
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            if (Bflag != 0) {
                                if (fiveflag == 0) {
                                    error(1, NULL, 0, NULL, 0, "-5 must precede any -B flags\n");
                                    exit(2);
                                }
                            } else {
                                fiveflag += 1;
                                temp_t8 = Bstring;
                                include = mkstr(comp_target_root, "usr/5include", NULL);
                                if (temp_t8 != NULL) {
                                    relocate_passes("h", NULL, temp_t8);
                                }
                                newrunlib();
                            }
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x36:                      /* switch 1 */
                        if ((compiler == 3) && (strcmp(*(arg1 + (var_s0 * 4)), "-66") == 0)) {
                            addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-64bit") == 0) {
                            error(2, NULL, 0, NULL, 0, "-64bit option is not yet implemented for ucode compilers, ignore\n");
                            sixty4bit_spec = 1;
                            if (swopcodeflag != 0) {
                                error(1, NULL, 0, NULL, 0, "-64bit can not be used with -swopcode for ucode compilers\n");
                                exit(2);
                            }
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x41:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            var_s0 += 1;
                            if (var_s0 < arg0) {
                                addstr(&objfiles, "-A");
                                addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                            } else {
                                error(1, NULL, 0, NULL, 0, "ld requires -A to have an argument\n");
                                exit(2);
                                goto block_32;
                            }
                        } else {
block_32:
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-AutoGnum") == 0) {
                                addstr(&uldflags, *(arg1 + (var_s0 * 4)));
                                if (strcmp(Gnum, "0") != 0) {
                                    Gnum = "0";
                                }
                            } else if ((*(arg1 + (var_s0 * 4)))->unk_1 == 0x41) {
                                addstr(&cppflags, *(arg1 + (var_s0 * 4)));
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-A-") == 0) {
                                addstr(&cppflags, *(arg1 + (var_s0 * 4)));
                            } else {
                                goto block_1537;
                            }
                        }
                        break;
                    case 0x42:                      /* switch 1 */
                        if (((*(arg1 + (var_s0 * 4)))->unk_2 == 0) && (var_s0 < (arg0 - 1)) && ((strcmp((arg1 + (var_s0 * 4))->unk_4, "static") == 0) || (strcmp((arg1 + (var_s0 * 4))->unk_4, "dynamic") == 0) || (strcmp((arg1 + (var_s0 * 4))->unk_4, "symbolic") == 0))) {
                            addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                            var_s0 += 1;
                            addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                        } else {
                            Bflag = 1;
                            temp_t5 = *(arg1 + (var_s0 * 4)) + 2;
                            sp144 = temp_t5;
                            relocate_passes(tstring, hstring, temp_t5);
                            if (tstring == NULL) {
                                Bstring = sp144;
                            }
                        }
                        break;
                    case 0x43:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            if (compiler == 3) {
                                addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                            } else if (compiler == 2) {
                                addstr(&upasflags, *(arg1 + (var_s0 * 4)));
                            } else if (compiler == 1) {
                                addstr(&cppflags, *(arg1 + (var_s0 * 4)));
                            } else {
                                goto block_54;
                            }
                        } else {
block_54:
                            if (strncmp(*(arg1 + (var_s0 * 4)), "-CG_EMIT:", 5U) == 0) {
                                error(2, NULL, 0, NULL, 0, "-CG_EMIT options are ignored\n");
                            } else {
                                goto block_1537;
                            }
                        }
                        break;
                    case 0x44:                      /* switch 1 */
                        if (strncmp(*(arg1 + (var_s0 * 4)), "-DEFAULT:", strlen("-DEFAULT:\0-D taken as empty cpp -D, not ld(1) -D hexnum\n\0-D\0ld requires -D to have an argument\n")) != 0) {
                            if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                                if ((var_s0 + 1) < arg0) {
                                    sp140 = malloc(strlen((arg1 + (var_s0 * 4))->unk_4) + 3);
                                    sp140->unk_0 = 0x2D;
                                    sp140->unk_1 = 0x44;
                                    sp140->unk_2 = 0;
                                    addstr(&undefineflags, strcat(sp140, (arg1 + (var_s0 * 4))->unk_4));
                                    add_static_opt(mkstr(*(arg1 + (var_s0 * 4)), (arg1 + (var_s0 * 4))->unk_4, NULL));
                                }
                                var_s0 += 1;
                            } else {
                                addstr(&undefineflags, *(arg1 + (var_s0 * 4)));
                                add_static_opt(*(arg1 + (var_s0 * 4)));
                            }
                        }
                        break;
                    case 0x45:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            Eflag += 1;
                            docpp = 1;
                        } else if (((*(arg1 + (var_s0 * 4)))->unk_3 == 0) && (((*(arg1 + (var_s0 * 4)))->unk_2 == 0x42) || ((*(arg1 + (var_s0 * 4)))->unk_2 == 0x4C))) {
                            if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0x42) {
                                if ((Bflag != 0) && (targetsex != 0)) {
                                    error(1, NULL, 0, NULL, 0, "-EB or -EL must precede any -B flags for ucode compilers\n");
                                    exit(2);
                                }
                                targetsex = 0;
                            } else {
                                if ((Bflag != 0) && (targetsex != 1)) {
                                    error(1, NULL, 0, NULL, 0, "-EB or -EL must precede any -B flags for ucode compilers\n");
                                    exit(2);
                                }
                                targetsex = 1;
                            }
                            newrunlib();
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x46:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            if (compiler == 3) {
                                Fflag += 1;
                            } else if ((compiler == 1) && ((temp_t3 = c_compiler_choice, (temp_t3 == 2)) || (temp_t3 == 3))) {
                                cflag = 1;
                                Fflag = 1;
                                default_template_instantiation_mode = 1;
                            } else {
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                            }
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x47:                      /* switch 1 */
                        if (strncmp(*(arg1 + (var_s0 * 4)), "-GCM:", 5U) == 0) {
                            error(2, NULL, 0, NULL, 0, "-GCM options are ignored\n");
                        } else if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            if (default_svr4 != 0) {
                                if (dn_flag != 0) {
                                    error(1, NULL, 0, NULL, 0, "-G can not be used with -dn \n");
                                    exit(2);
                                }
                                G_flag = 1;
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                            } else {
                                var_s0 += 1;
                                if (var_s0 >= arg0) {
                                    error(1, NULL, 0, NULL, 0, "-G requires a decimal number argument\n");
                                    exit(2);
                                }
                                if (Oflag < 3) {
                                    Gnum = *(arg1 + (var_s0 * 4));
                                } else {
                                    Gnum = "0";
                                }
                                goto block_101;
                            }
                        } else if (default_svr4 == 0) {
                            if (Oflag < 3) {
                                Gnum = *(arg1 + (var_s0 * 4)) + 2;
                            } else {
                                Gnum = "0";
                            }
block_101:
                            var_s2 = Gnum;
                            if ((u8) *var_s2 != 0) {
                                do {
                                    if (!(__ctype[(u8) var_s2->unk_0].unk_1 & 4)) {
                                        error(1, NULL, 0, NULL, 0, "non-digit character in -G %s\n", Gnum);
                                        exit(2);
                                    }
                                    temp_t7_2 = var_s2->unk_1;
                                    var_s2 += 1;
                                } while (temp_t7_2 != 0);
                            }
                            if (Gseen_flag == 0) {
                                relocate_passes(tstring, hstring, NULL);
                                Gseen_flag = 1;
                            }
                        }
                        break;
                    case 0x48:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            addstr(&cppflags, *(arg1 + (var_s0 * 4)));
                            Eflag += 1;
                        } else if ((*(arg1 + (var_s0 * 4)))->unk_3 == 0) {
                            temp_t6 = (*(arg1 + (var_s0 * 4)))->unk_2;
                            var_s2_2 = "fKMdkjusmocab";
                            Hchar = temp_t6;
                            if ((*"fKMdkjusmocab" != 0) && (*"fKMdkjusmocab" != temp_t6)) {
loop_112:
                                temp_t5_2 = var_s2_2->unk_1;
                                var_s2_2 += 1;
                                if (temp_t5_2 != 0) {
                                    if (*var_s2_2 != Hchar) {
                                        goto loop_112;
                                    }
                                }
                            }
                            if (*var_s2_2 == 0) {
                                error(1, NULL, 0, NULL, 0, "Unknown character in %s\n", *(arg1 + (var_s0 * 4)));
                                exit(2);
                            }
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x49:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            if ((((arg1 + (var_s0 * 4))->unk_4 != 0) && (*(arg1 + (var_s0 * 4))->unk_4 == 0x2D)) || (isdir((arg1 + (var_s0 * 4))->unk_4) == 0)) {
                                emptyIflag += 1;
                            } else {
                                var_s0 += 1;
                                sp134 = mkstr("-I", *(arg1 + (var_s0 * 4)), NULL);
                                addstr(&cppflags, sp134);
                                addstr(&cpp2flags, sp134);
                                add_static_opt(mkstr("-I", full_path(*(arg1 + (var_s0 * 4))), NULL));
                            }
                        } else {
                            addstr(&cppflags, *(arg1 + (var_s0 * 4)));
                            addstr(&cpp2flags, *(arg1 + (var_s0 * 4)));
                            addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                            add_static_opt(mkstr("-I", full_path(*(arg1 + (var_s0 * 4)) + 2), NULL));
                        }
                        break;
                    case 0x4A:                      /* switch 1 */
                        if (strcmp(*(arg1 + (var_s0 * 4)), "-Jsfm") != 0) {
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-J") == 0) {
                                temp_t2 = (arg1 + (var_s0 * 4))->unk_4;
                                sp12C = temp_t2;
                                sp130 = temp_t2;
                                if ((u8) *temp_t2 != 0) {
                                    do {
                                        if (!(__ctype[(u8) *sp130].unk_1 & 4)) {
                                            error(1, NULL, 0, NULL, 0, "non-digit character in -J %s\n", sp12C);
                                            exit(2);
                                        }
                                        sp130 += 1;
                                    } while ((u8) sp130[1] != 0);
                                }
                                addstr(&prelinkerflags, *(arg1 + (var_s0 * 4)));
                                addstr(&prelinkerflags, sp12C);
                                var_s0 += 1;
                            } else {
                            case 0x4B:              /* switch 1 */
                                if (default_svr4 != 0) {
                                    temp_t0 = *(arg1 + (var_s0 * 4)) + 2;
                                    Kpass = temp_t0;
                                    if (*temp_t0 == 0) {
                                        Kpass = *(arg1 + (var_s0 * 4)) + 3;
                                    }
                                    temp_t3_2 = *Kpass;
                                    if ((temp_t3_2 != 0) || (temp_t3_2 == 0x2C)) {
loop_135:
                                        var_s2_3 = Kpass;
                                        j = 0;
                                        if ((*var_s2_3 != 0x2C) && (*var_s2_3 != 0)) {
loop_137:
                                            (&Karg)[j] = (s8) *var_s2_3;
                                            var_s2_3 += 1;
                                            j += 1;
                                            if (*var_s2_3 != 0x2C) {
                                                if (*var_s2_3 != 0) {
                                                    goto loop_137;
                                                }
                                            }
                                        }
                                        Kpass = var_s2_3;
                                        if (strncmp(&Karg, "minabi", 6U) == 0) {
                                            kminabiflag = 1;
                                            goto block_153;
                                        }
                                        if (strncmp(&Karg, "fpe", 3U) == 0) {
                                            addstr(&ldflags, "-Kfpe");
                                            goto block_153;
                                        }
                                        if (strncmp(&Karg, "sd", 2U) == 0) {
                                            addstr(&ldflags, "-Ksd");
                                            goto block_153;
                                        }
                                        if (strncmp(&Karg, "sz", 2U) == 0) {
                                            addstr(&ldflags, "-Ksz");
                                            goto block_153;
                                        }
                                        if (strncmp(&Karg, "mau", 3U) == 0) {
                                            addstr(&ldflags, "-Kmau");
                                            goto block_153;
                                        }
                                        if (strncmp(&Karg, "PIC", 3U) == 0) {
                                            if (non_shared != 0) {
                                                error(2, NULL, 0, NULL, 0, "Can't mix -KPIC and -non_shared, change to -non_shared\n");
                                                kpic_flag = 0;
                                            } else {
                                                kpic_flag = 1;
                                                kpic_spec = 1;
                                            }
block_153:
                                            j = 0;
                                            if ((u32) j < strlen(&Karg)) {
                                                do {
                                                    (&Karg)[j] = 0x20;
                                                    j += 1;
                                                } while ((u32) j < strlen(&Karg));
                                            }
                                            temp_t6_2 = Kpass;
                                            if (temp_t6_2 != NULL) {
                                                temp_t7_3 = *temp_t6_2;
                                                if ((temp_t7_3 == 0x2C) && (temp_t7_3 != 0)) {
loop_158:
                                                    Kpass += 1;
                                                    temp_t4 = Kpass;
                                                    if (temp_t4 != NULL) {
                                                        temp_t9 = *temp_t4;
                                                        if (temp_t9 == 0x2C) {
                                                            if (temp_t9 != 0) {
                                                                goto loop_158;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            temp_t2_2 = *Kpass;
                                            if ((temp_t2_2 == 0) && (temp_t2_2 != 0x2C)) {

                                            } else {
                                                goto loop_135;
                                            }
                                        } else {
                                            goto block_1537;
                                        }
                                    }
                                } else if (svr4_systype != 0) {
                                    temp_t5_3 = *(arg1 + (var_s0 * 4)) + 2;
                                    Kpass = temp_t5_3;
                                    if (*temp_t5_3 == 0) {
                                        Kflag += 1;
                                        addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                                    }
                                    temp_t7_4 = *Kpass;
                                    if ((temp_t7_4 != 0) || (temp_t7_4 == 0x2C)) {
loop_169:
                                        var_s2_4 = Kpass;
                                        j = 0;
                                        if ((*var_s2_4 != 0x2C) && (*var_s2_4 != 0)) {
loop_171:
                                            (&Karg)[j] = (s8) *var_s2_4;
                                            var_s2_4 += 1;
                                            j += 1;
                                            if (*var_s2_4 != 0x2C) {
                                                if (*var_s2_4 != 0) {
                                                    goto loop_171;
                                                }
                                            }
                                        }
                                        Kpass = var_s2_4;
                                        if (strncmp(&Karg, "minabi", 6U) == 0) {
                                            kminabiflag = 1;
                                            goto block_187;
                                        }
                                        if (strncmp(&Karg, "fpe", 3U) == 0) {
                                            addstr(&ldflags, "-Kfpe");
                                            goto block_187;
                                        }
                                        if (strncmp(&Karg, "sd", 2U) == 0) {
                                            addstr(&ldflags, "-Ksd");
                                            goto block_187;
                                        }
                                        if (strncmp(&Karg, "sz", 2U) == 0) {
                                            addstr(&ldflags, "-Ksz");
                                            goto block_187;
                                        }
                                        if (strncmp(&Karg, "mau", 3U) == 0) {
                                            addstr(&ldflags, "-Kmau");
                                            goto block_187;
                                        }
                                        if (strncmp(&Karg, "PIC", 3U) == 0) {
                                            if (non_shared != 0) {
                                                error(2, NULL, 0, NULL, 0, "Can't mix -KPIC and -non_shared, change to -non_shared\n");
                                                kpic_flag = 0;
                                            } else {
                                                kpic_flag = 1;
                                                kpic_spec = 1;
                                            }
block_187:
                                            j = 0;
                                            if ((u32) j < strlen(&Karg)) {
                                                do {
                                                    (&Karg)[j] = 0x20;
                                                    j += 1;
                                                } while ((u32) j < strlen(&Karg));
                                            }
                                            temp_t3_3 = Kpass;
                                            if (temp_t3_3 != NULL) {
                                                temp_t4_2 = *temp_t3_3;
                                                if ((temp_t4_2 == 0x2C) && (temp_t4_2 != 0)) {
loop_192:
                                                    Kpass += 1;
                                                    temp_t6_3 = Kpass;
                                                    if (temp_t6_3 != NULL) {
                                                        temp_t2_3 = *temp_t6_3;
                                                        if (temp_t2_3 == 0x2C) {
                                                            if (temp_t2_3 != 0) {
                                                                goto loop_192;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            temp_t8_2 = *Kpass;
                                            if ((temp_t8_2 == 0) && (temp_t8_2 != 0x2C)) {

                                            } else {
                                                goto loop_169;
                                            }
                                        } else {
                                            goto block_1537;
                                        }
                                    }
                                } else if ((*(arg1 + (var_s0 * 4)))->unk_2 != 0) {
                                    if (strcmp(*(arg1 + (var_s0 * 4)), "-KPIC") == 0) {
                                        if (non_shared != 0) {
                                            error(2, NULL, 0, NULL, 0, "Can't mix -KPIC and -non_shared, change to -non_shared\n");
                                            kpic_flag = 0;
                                        } else {
                                            kpic_flag = 1;
                                            kpic_spec = 1;
                                        }
                                    } else {
                                        addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                                    }
                                } else {
                                    Kflag += 1;
                                    addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                                }
                            }
                        }
                        break;
                    case 0x4C:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            if (((var_s0 + 1) < arg0) && (*(arg1 + (var_s0 * 4))->unk_4 != 0x2D) && (isdir((arg1 + (var_s0 * 4))->unk_4) != 0)) {
                                var_s0 += 1;
                                sp128 = mkstr((arg1 + (var_s0 * 4))->unk_-4, *(arg1 + (var_s0 * 4)), NULL);
                                addstr(&ldflags, sp128);
                                addstr(&prelinkerflags, sp128);
                                Lflag = 1;
                            } else {
                                addstr(&prelinkerflags, mkstr("-YB", NULL));
                                goto block_211;
                            }
                        } else {
block_211:
                            Lflag = 1;
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                            addstr(&prelinkerflags, *(arg1 + (var_s0 * 4)));
                        }
                        break;
                    case 0x4D:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0x44) {
                            if (strcmp(*(arg1 + (var_s0 * 4)) + 3, "update") == 0) {
                                sp15C = (arg1 + (var_s0 * 4))->unk_4;
                                goto block_225;
                            }
                            if (strcmp(*(arg1 + (var_s0 * 4)) + 3, "ignore") == 0) {
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                                addstr(&ldflags, (arg1 + (var_s0 * 4))->unk_4);
                                goto block_224;
                            }
                            if (strcmp(*(arg1 + (var_s0 * 4)) + 3, "ignoredir") == 0) {
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                                addstr(&ldflags, (arg1 + (var_s0 * 4))->unk_4);
                                goto block_224;
                            }
                            if (strcmp(*(arg1 + (var_s0 * 4)) + 3, "target") == 0) {
                                if ((compiler == 1) && (c_compiler_choice != 0)) {
                                    sp154 = (arg1 + (var_s0 * 4))->unk_4;
                                } else {
                                    addstr(&cppflags, *(arg1 + (var_s0 * 4)));
                                    addstr(&cppflags, (arg1 + (var_s0 * 4))->unk_4);
block_224:
                                }
block_225:
                                var_s0 += 1;
                                if (var_s0 >= arg0) {
                                    error(1, NULL, 0, NULL, 0, "%s must be followed by a file name\n", (arg1 + (var_s0 * 4))->unk_-4);
                                    exit(2);
                                }
                            } else {
                                goto block_1537;
                            }
                        } else if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            addstr(&cppflags, *(arg1 + (var_s0 * 4)));
                            Eflag += 1;
                            minus_M += 1;
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x4E:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                        } else if (compiler == 3) {
                            addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                            add_static_opt(*(arg1 + (var_s0 * 4)));
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x4F:                      /* switch 1 */
                        plain_O = 0;
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            if ((xpg_flag != 0) && (var_s1 == 0x66)) {
                                fprintf(__iob + 0x20, "Error: optlevel should be specified\n");
                                exit(1);
                            }
                            Oflag = 2;
                            plain_O = 1;
                            if (plain_g != 0) {
                                Oflag = 1;
                            }
                            if (((var_s0 + 1) < arg0) && ((arg1 + (var_s0 * 4))->unk_4->unk_1 == 0) && ((s32) *(arg1 + (var_s0 * 4))->unk_4 >= 0x30) && ((s32) *(arg1 + (var_s0 * 4))->unk_4 < 0x35)) {
                                sp124 = malloc(strlen((arg1 + (var_s0 * 4))->unk_4) + 3);
                                sp124->unk_0 = 0x2D;
                                sp124->unk_1 = 0x4F;
                                sp124->unk_2 = 0;
                                Oflag = *(arg1 + (var_s0 * 4))->unk_4 - 0x30;
                                addstr(&fcomflags, strcat(sp124, (arg1 + (var_s0 * 4))->unk_4));
                                var_s0 += 1;
                            }
                        } else if ((*(arg1 + (var_s0 * 4)))->unk_3 == 0) {
                            if (((s32) (*(arg1 + (var_s0 * 4)))->unk_2 >= 0x30) && ((s32) (*(arg1 + (var_s0 * 4)))->unk_2 < 0x35)) {
                                temp_t4_3 = (*(arg1 + (var_s0 * 4)))->unk_2 - 0x30;
                                Oflag = temp_t4_3;
                                if (temp_t4_3 == 3) {
                                    sp120 = "-Olimit";
                                    sp11C = "5000";
                                    Gnum = "0";
                                    addstr(&umergeflags, "-Olimit");
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
                                if ((Oflag >= 3) && (jflag == 0)) {
                                    uload = 1;
                                }
                            } else {
                                goto block_1537;
                            }
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-Olimit") == 0) {
                            addstr(&umergeflags, *(arg1 + (var_s0 * 4)));
                            addstr(&optflags, *(arg1 + (var_s0 * 4)));
                            addstr(&ddoptflags, *(arg1 + (var_s0 * 4)));
                            addstr(&uopt0flags, *(arg1 + (var_s0 * 4)));
                            addstr(&olimitflags, *(arg1 + (var_s0 * 4)));
                            var_s0 += 1;
                            if (var_s0 >= arg0) {
                                error(1, NULL, 0, NULL, 0, "-Olimit must have an argument\n");
                                exit(2);
                            }
                            var_s2_5 = *(arg1 + (var_s0 * 4));
                            if (*var_s2_5 != 0) {
                                do {
                                    if (!(__ctype[var_s2_5->unk_0].unk_1 & 4)) {
                                        error(1, NULL, 0, NULL, 0, "non-digit character in -Olimit %s\n", *(arg1 + (var_s0 * 4)));
                                        exit(2);
                                    }
                                    temp_t1 = var_s2_5->unk_1;
                                    var_s2_5 += 1;
                                } while (temp_t1 != 0);
                            }
                            addstr(&umergeflags, *(arg1 + (var_s0 * 4)));
                            addstr(&optflags, *(arg1 + (var_s0 * 4)));
                            addstr(&ddoptflags, *(arg1 + (var_s0 * 4)));
                            addstr(&uopt0flags, *(arg1 + (var_s0 * 4)));
                            addstr(&olimitflags, *(arg1 + (var_s0 * 4)));
                        } else if (strncmp(*(arg1 + (var_s0 * 4)), "-OPT:", 5U) == 0) {
                            error(2, NULL, 0, NULL, 0, "-OPT options are ignored\n");
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x50:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            docpp = 1;
                            addstr(&cppflags, *(arg1 + (var_s0 * 4)));
                            if (Eflag == 0) {
                                Pflag += 1;
                            }
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x51:                      /* switch 1 */
                        if ((strcmp(*(arg1 + (var_s0 * 4)), "-Qy") != 0) && (strcmp(*(arg1 + (var_s0 * 4)), "-Qn") != 0)) {
                            addstr(&cppflags, *(arg1 + (var_s0 * 4)));
                        }
                        break;
                    case 0x52:                      /* switch 1 */
                        if (compiler == 3) {
                            addstr(&ratforflags, *(arg1 + (var_s0 * 4)) + 2);
                            add_static_opt(*(arg1 + (var_s0 * 4)));
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x53:                      /* switch 1 */
                        if (strncmp(*(arg1 + (var_s0 * 4)), "-SWP:", 5U) == 0) {
                            error(2, NULL, 0, NULL, 0, "-SWP options are ignored\n");
                        } else if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            Sflag += 1;
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x54:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            var_s0 += 1;
                            if (var_s0 < arg0) {
                                addstr(&ldflags, "-T");
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                            } else {
                                error(1, NULL, 0, NULL, 0, "ld requires -T to have an argument\n");
                                exit(2);
                                goto block_278;
                            }
                        } else {
block_278:
                            if (strncmp(*(arg1 + (var_s0 * 4)), "-TARG:", 6U) == 0) {
                                error(2, NULL, 0, NULL, 0, "-TARG options are ignored\n");
                            } else if (strncmp(*(arg1 + (var_s0 * 4)), "-TENV:", 6U) == 0) {
                                error(2, NULL, 0, NULL, 0, "-TENV options are ignored\n");
                            } else {
                                goto block_1537;
                            }
                        }
                        break;
                    case 0x55:                      /* switch 1 */
                        if ((compiler == 3) && ((*(arg1 + (var_s0 * 4)))->unk_2 == 0)) {
                            addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                            add_static_opt(*(arg1 + (var_s0 * 4)));
                            mp_caseflag = 1;
                        } else if (((*(arg1 + (var_s0 * 4)))->unk_2 == 0) && ((var_s0 + 1) < arg0)) {
                            sp118 = malloc(strlen((arg1 + (var_s0 * 4))->unk_4) + 3);
                            sp118->unk_0 = 0x2D;
                            sp118->unk_1 = 0x55;
                            sp118->unk_2 = 0;
                            addstr(&undefineflags, strcat(sp118, (arg1 + (var_s0 * 4))->unk_4));
                            var_s0 += 1;
                        } else {
                            addstr(&undefineflags, *(arg1 + (var_s0 * 4)));
                            add_static_opt(*(arg1 + (var_s0 * 4)));
                        }
                        break;
                    case 0x56:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            error(2, NULL, 0, NULL, 0, "-V is not supported.\n");
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-VS") == 0) {
                            var_s0 += 1;
                            if (var_s0 < arg0) {
                                addstr(&ldflags, "-VS");
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                            } else {
                                error(1, NULL, 0, NULL, 0, "ld requires -VS to have an argument\n");
                                exit(2);
                                goto block_1537;
                            }
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x57:                      /* switch 1 */
                        temp_t9_2 = *(arg1 + (var_s0 * 4)) + 2;
                        Wpass = temp_t9_2;
                        if (*temp_t9_2 != 0) {
                            temp_t6_4 = *(arg1 + (var_s0 * 4)) + 3;
                            Warg = temp_t6_4;
                            if ((u8) *temp_t6_4 != 0x2C) {
loop_297:
                                temp_t4_4 = Warg;
                                Warg = temp_t4_4 + 1;
                                if ((u8) temp_t4_4->unk_0 != 0) {
                                    if ((u8) Warg->unk_0 == 0x2C) {
                                        goto block_299;
                                    }
                                    goto loop_297;
                                }
                                goto block_1537;
                            }
block_299:
                            if ((u8) Warg->unk_0 == 0x2C) {
                                do {
                                    Warg->unk_0 = 0;
                                    var_s2_6 = Wpass;
                                    Warg += 1;
                                    if (*var_s2_6 != 0) {
                                        do {
                                            temp_t4_5 = var_s2_6->unk_0;
                                            switch (temp_t4_5) { /* switch 2 */
                                                case 0x70: /* switch 2 */
                                                    addstr(&cppflags, Warg);
                                                    break;
                                                case 0x4B: /* switch 2 */
                                                    if (compiler == 3) {
                                                        addstr(&pfaflags, Warg);
                                                    } else if (compiler == 1) {
                                                        addstr(&pcaflags, Warg);
                                                    } else {
                                                        error(1, NULL, 0, NULL, 0, "-WK only valid in FORTRAN or C compilations.\n");
                                                        exit(2);
                                                    }
                                                    break;
                                                case 0x30: /* switch 2 */
                                                case 0x66: /* switch 2 */
                                                    temp_s4 = compiler;
                                                    switch (temp_s4) { /* switch 6; irregular */
                                                        case 0x2: /* switch 6 */
                                                            addstr(&upasflags, Warg);
                                                            break;
                                                        case 0x3: /* switch 6 */
                                                            addstr(&fcomflags, Warg);
                                                            break;
                                                        case 0x5: /* switch 6 */
                                                            addstr(&upl1flags, Warg);
                                                            break;
                                                        case 0x6: /* switch 6 */
                                                            addstr(&ucobflags, Warg);
                                                            break;
                                                        default: /* switch 6 */
                                                            addstr(&ccomflags, Warg);
                                                            addstr(&edisonflags, Warg);
                                                            break;
                                                    }
                                                    break;
                                                case 0x77: /* switch 2 */
                                                    addstr(&prelinkerflags, Warg);
                                                    break;
                                                case 0x6B: /* switch 2 */
                                                    addstr(&ulpiflags, Warg);
                                                    break;
                                                case 0x6A: /* switch 2 */
                                                    addstr(&ujoinflags, Warg);
                                                    break;
                                                case 0x75: /* switch 2 */
                                                    addstr(&uldflags, Warg);
                                                    break;
                                                case 0x73: /* switch 2 */
                                                    addstr(&usplitflags, Warg);
                                                    break;
                                                case 0x6D: /* switch 2 */
                                                    addstr(&umergeflags, Warg);
                                                    break;
                                                case 0x71: /* switch 2 */
                                                    addstr(&uopt0flags, Warg);
                                                    break;
                                                case 0x64: /* switch 2 */
                                                    addstr(&ddoptflags, Warg);
                                                    break;
                                                case 0x32: /* switch 2 */
                                                    addstr(&optflags, Warg);
                                                    break;
                                                case 0x6F: /* switch 2 */
                                                    addstr(&optflags, Warg);
                                                    if (strstr(Warg, "loopunroll") != 0) {
                                                        set_loop_unroll = 1;
                                                    }
                                                    break;
                                                case 0x63: /* switch 2 */
                                                    addstr(&genflags, Warg);
                                                    break;
                                                case 0x61: /* switch 2 */
                                                    addstr(&asflags, Warg);
                                                    break;
                                                case 0x62: /* switch 2 */
                                                    addstr(&asflags, Warg);
                                                    break;
                                                case 0x6C: /* switch 2 */
                                                    addstr(&ldflags, Warg);
                                                    break;
                                                case 0x79: /* switch 2 */
                                                    addstr(&ftocflags, Warg);
                                                    break;
                                                case 0x7A: /* switch 2 */
                                                    addstr(&cordflags, Warg);
                                                    break;
                                                case 0x4D: /* switch 2 */
                                                    addstr(&mpcflags, Warg);
                                                    break;
                                                case 0x78: /* switch 2 */
                                                    temp_t1_2 = Warg->unk_1;
                                                    switch (temp_t1_2) { /* switch 3 */
                                                        case 0x47: /* switch 3 */
                                                            if (Warg->unk_2 == 0) {
                                                                var_s0 += 1;
                                                                if (var_s0 >= arg0) {
                                                                    error(1, NULL, 0, NULL, 0, "-G requires a decimal number argument\n");
                                                                    exit(2);
                                                                }
                                                                if (Oflag < 3) {
                                                                    Gnum = *(arg1 + (var_s0 * 4));
                                                                } else {
                                                                    Gnum = "0";
                                                                }
                                                            } else if (Oflag < 3) {
                                                                Gnum = Warg + 2;
                                                            } else {
                                                                Gnum = "0";
                                                            }
                                                            var_s3 = Gnum;
                                                            if (((u8) *var_s3 != 0x2C) && ((u8) *var_s3 != 0)) {
loop_350:
                                                                if (!(__ctype[(u8) *var_s3].unk_1 & 4)) {
                                                                    error(1, NULL, 0, NULL, 0, "non-digit character in -G %s\n", Gnum);
                                                                    exit(2);
                                                                }
                                                                if ((u8) *var_s3 != 0x2C) {
                                                                    var_s3 += 1;
                                                                }
                                                                if (((u8) *var_s3 != 0x2C) && ((u8) *var_s3 != 0)) {
                                                                    goto loop_350;
                                                                }
                                                            }
                                                            if (Gseen_flag == 0) {
                                                                Gseen_flag = 1;
                                                                relocate_passes(tstring, hstring, NULL);
                                                            }
                                                            Warg = var_s3;
                                                            break;
                                                        case 0x76: /* switch 3 */
                                                            temp_t6_5 = Warg->unk_2;
                                                            if ((temp_t6_5 == 0) || (temp_t6_5 == 0x2C)) {
                                                                vflag = 1;
                                                                if (getenv("ROOTDIR") != NULL) {
                                                                    error(2, NULL, 0, NULL, 0, "ROOTDIR env var ignored, use COMP_TARGET_ROOT and COMP_HOST_ROOT\n");
                                                                }
                                                            }
                                                            break;
                                                        case 0x44: /* switch 3 */
                                                            if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                                                                if (((var_s0 + 1) < arg0) && ((sp114 = strtoul((arg1 + (var_s0 * 4))->unk_4, &sp110, 0x10), (strlen((arg1 + (var_s0 * 4))->unk_4) != (sp110 - (arg1 + (var_s0 * 4))->unk_4))) || ((sp114 == 0) && ((arg1 + (var_s0 * 4))->unk_4 == sp110)) || (*(arg1 + (var_s0 * 4))->unk_4 == 0x2D) || (*(arg1 + (var_s0 * 4))->unk_4 == 0x2B))) {
                                                                    error(2, NULL, 0, NULL, 0, "-D taken as empty cpp -D, not ld(1) -D hexnum\n");
                                                                } else {
                                                                    var_s0 += 1;
                                                                    if (var_s0 < arg0) {
                                                                        addstr(&ldflags, "-D");
                                                                        addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                                                                    } else {
                                                                        error(1, NULL, 0, NULL, 0, "ld requires -D to have an argument\n");
                                                                        exit(2);
                                                                        goto block_374;
                                                                    }
                                                                }
                                                            } else {
                                                            case 0x62: /* switch 3 */
block_374:
                                                                temp_t4_6 = Warg->unk_2;
                                                                if ((temp_t4_6 == 0) || (temp_t4_6 == 0x2C)) {
                                                                    addstr(&ldflags, mkstr(*(arg1 + (var_s0 * 4)), ",", Warg, NULL));
                                                                }
                                                            }
                                                            break;
                                                        case 0x4B: /* switch 3 */
                                                            if (strcmp(Warg, "-K") != 0) {
                                                                addstr(&ldflags, mkstr(*(arg1 + (var_s0 * 4)), ",", Warg, NULL));
                                                            } else {
                                                                Kflag += 1;
                                                            }
                                                            break;
                                                        case 0x41: /* switch 3 */
                                                            if (Warg->unk_2 == 0) {
                                                                var_s0 += 1;
                                                                if (var_s0 < arg0) {
                                                                    addstr(&objfiles, "-A");
                                                                }
                                                                error(1, NULL, 0, NULL, 0, "ld requires -A to have an argument\n");
                                                                exit(2);
                                                            }
                                                            break;
                                                    }
                                                    break;
                                                default: /* switch 2 */
                                                    error(1, NULL, 0, NULL, 0, "Unknown pass character in %s\n", *(arg1 + (var_s0 * 4)));
                                                    exit(2);
                                                    break;
                                            }
                                            temp_t5_4 = var_s2_6->unk_1;
                                            var_s2_6 += 1;
                                        } while (temp_t5_4 != 0);
                                    }
                                    temp_t4_7 = (u8) Warg->unk_0;
                                    if ((temp_t4_7 != 0x2C) && (temp_t4_7 != 0)) {
loop_389:
                                        Warg += 1;
                                        temp_t8_3 = (u8) Warg->unk_0;
                                        if (temp_t8_3 != 0x2C) {
                                            if (temp_t8_3 != 0) {
                                                goto loop_389;
                                            }
                                        }
                                    }
                                } while ((u8) Warg->unk_0 == 0x2C);
                            }
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x58:                      /* switch 1 */
                        if (compiler == 1) {
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-Xcpluscomm") == 0) {
                                addstr(&ccomflags, *(arg1 + (var_s0 * 4)));
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-Xt") == 0) {
                                stdflag = 0;
                                addstr(&ccomflags, "-std0");
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-Xc") == 0) {
                                stdflag = 1;
                                addstr(&ccomflags, "-std1");
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-Xa") == 0) {
                                stdflag = 1;
                                addstr(&ccomflags, "-std");
                            } else {
                                goto block_402;
                            }
                        } else {
block_402:
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-Xprototypes") == 0) {
                                addstr(&ccomflags, *(arg1 + (var_s0 * 4)));
                            } else {
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                                if ((strcmp(*(arg1 + (var_s0 * 4)), "-Xndlocaldata") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-Xlocaldata") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-Xndblock") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-Xblock") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-Xalignbss") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-Xnoalignbss") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-Xcachesize") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-Xcachelinesize") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-Xdefmovemax") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-Xsetalign") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-Xblockrange") == 0)) {
                                    var_s0 += 1;
                                    if (var_s0 < arg0) {
                                        addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                                    } else {
                                        error(1, NULL, 0, NULL, 0, "%s must have an argument\n", (arg1 + (var_s0 * 4))->unk_-4);
                                    }
                                }
                            }
                        }
                        break;
                    case 0x61:                      /* switch 1 */
                        if ((compiler == 1) && (strcmp(*(arg1 + (var_s0 * 4)), "-all") == 0)) {
                            addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                        } else if ((compiler == 1) && ((temp_t8_4 = c_compiler_choice, (temp_t8_4 == 2)) || (temp_t8_4 == 3)) && (strcmp(*(arg1 + (var_s0 * 4)), "-auto_include") == 0)) {
                            auto_template_include = 1;
                        } else if ((compiler == 1) && ((temp_t4_8 = c_compiler_choice, (temp_t4_8 == 2)) || (temp_t4_8 == 3)) && (strcmp(*(arg1 + (var_s0 * 4)), "-anach") == 0)) {
                            anachronisms = 1;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-ansi") == 0) {
                            if (compchoice == 1) {
                                compchoice = 0;
                            }
                            ansichoice = 1;
                            if (cppchoice != 1) {
                                cppchoice = 3;
                            }
                            relocate_passes("p", NULL, NULL);
                            add_static_opt(*(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-ansiposix") == 0) {
                            if (compchoice == 1) {
                                compchoice = 0;
                            }
                            ansichoice = 2;
                            if (cppchoice != 1) {
                                cppchoice = 3;
                            }
                            relocate_passes("p", NULL, NULL);
                            add_static_opt(*(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-abi") == 0) {
                            abi_flag = 1;
                            addstr(&cppflags, "-D_ABI_SOURCE");
                            addstr(&asflags, "-abi");
                            addstr(&ldflags, "-abi");
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-acpp") == 0) {
                            if ((compiler == 1) && (c_compiler_choice != 0)) {
                                error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", *(arg1 + (var_s0 * 4)), "");
                            } else {
                                cppchoice = 1;
                                acpp = 1;
                                relocate_passes("p", NULL, NULL);
                            }
                        } else {
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-align8") == 0) {
                                align = 8;
                                if (compiler == 3) {
                                    align_common += 1;
                                }
                                goto block_464;
                            }
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-align16") == 0) {
                                align = 0x10;
                                if (compiler == 3) {
                                    align_common += 1;
                                }
                                goto block_464;
                            }
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-align32") == 0) {
                                align = 0x20;
                                if (compiler == 3) {
                                    align_common += 1;
                                }
                                goto block_464;
                            }
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-align64") == 0) {
                                align = 0x40;
                                if (compiler == 3) {
                                    align_common += 1;
                                }
                                goto block_464;
                            }
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-align_common") == 0) {
                                align_common = 1;
                            } else {
block_464:
                                if (compiler == 3) {
                                    if ((strcmp(*(arg1 + (var_s0 * 4)), "-align8") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-align16") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-align32") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-align64") == 0)) {
                                        addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                                        addstr(&genflags, *(arg1 + (var_s0 * 4)));
                                        addstr(&asflags, *(arg1 + (var_s0 * 4)));
                                    } else if (strcmp(*(arg1 + (var_s0 * 4)), "-automatic") == 0) {
                                        automaticflag = 1;
                                    } else {
                                        goto block_472;
                                    }
                                } else {
block_472:
                                    if ((compiler == 6) && (strcmp(*(arg1 + (var_s0 * 4)), "-ansi") == 0)) {
                                        ansiflag = 1;
                                    } else if ((compiler == 2) && (strcmp(*(arg1 + (var_s0 * 4)), "-apc") == 0)) {
                                        addstr(&upasflags, *(arg1 + (var_s0 * 4)));
                                        addstr(&genflags, *(arg1 + (var_s0 * 4)));
                                    } else if (strcmp(*(arg1 + (var_s0 * 4)), "-align8") == 0) {
                                        align = 8;
                                        alignarg = savestr(*(arg1 + (var_s0 * 4)), 0);
                                    } else if (strcmp(*(arg1 + (var_s0 * 4)), "-align16") == 0) {
                                        align = 0x10;
                                        alignarg = savestr(*(arg1 + (var_s0 * 4)), 0);
                                    } else if (strcmp(*(arg1 + (var_s0 * 4)), "-align32") == 0) {
                                        align = 0x20;
                                        alignarg = savestr(*(arg1 + (var_s0 * 4)), 0);
                                    } else if (strcmp(*(arg1 + (var_s0 * 4)), "-align64") == 0) {
                                        align = 0x40;
                                        alignarg = savestr(*(arg1 + (var_s0 * 4)), 0);
                                    } else if (strcmp(*(arg1 + (var_s0 * 4)), "-ajeop") == 0) {
                                        addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                                        addstr(&cordflags, "-no_r4000_fix");
                                    } else {
                                        goto block_1537;
                                    }
                                }
                            }
                        }
                        break;
                    case 0x62:                      /* switch 1 */
                        if (((*(arg1 + (var_s0 * 4)))->unk_2 == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-bestGnum") == 0)) {
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-bytereclen") == 0) {
                            addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                        } else {
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-backslash") == 0) {
                                mp_backslashflag = 1;
                                docpp = 0;
                            }
                            addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                            add_static_opt(*(arg1 + (var_s0 * 4)));
                        }
                        break;
                    case 0x63:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            cflag += 1;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-cckr") == 0) {
                            ansichoice = 0;
                            if (cppchoice != 1) {
                                cppchoice = 2;
                            }
                            add_static_opt(*(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-cfe") == 0) {
                            if ((compiler == 1) && (c_compiler_choice != 0)) {
                                error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", *(arg1 + (var_s0 * 4)), "");
                            } else {
                                compchoice = 3;
                                relocate_passes("p", NULL, NULL);
                            }
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-common") == 0) {
                            if ((compiler == 1) && (c_compiler_choice != 0)) {
                                error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", *(arg1 + (var_s0 * 4)), "");
                            } else {
                                addstr(&accomflags, "-Xcommon");
                            }
                        } else if ((compiler == 1) && ((temp_t8_5 = c_compiler_choice, (temp_t8_5 == 2)) || (temp_t8_5 == 3)) && (strcmp(*(arg1 + (var_s0 * 4)), "-cfront") == 0)) {
                            cfront_compatible = 1;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-cachesz") == 0) {
                            addstr(&ddoptflags, *(arg1 + (var_s0 * 4)));
                            var_s0 += 1;
                            if (var_s0 >= arg0) {
                                error(1, NULL, 0, NULL, 0, "-cachesz must have an argument\n");
                                exit(2);
                            }
                            var_s2_7 = Gnum;
                            if ((u8) *var_s2_7 != 0) {
                                do {
                                    if (!(__ctype[(u8) var_s2_7->unk_0].unk_1 & 4)) {
                                        error(1, NULL, 0, NULL, 0, "non-digit character in -G %s\n", *(arg1 + (var_s0 * 4)));
                                        exit(2);
                                    }
                                    temp_t5_5 = var_s2_7->unk_1;
                                    var_s2_7 += 1;
                                } while (temp_t5_5 != 0);
                            }
                            addstr(&ddoptflags, *(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-cplus") == 0) {
                            cplusflag = 1;
                            addstr(&ccomflags, "-cplus");
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-cpp") == 0) {
                            error(2, NULL, 0, NULL, 0, "-cpp is default\n");
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-cord") == 0) {
                            cordflag = 1;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-coff") == 0) {
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                            coff_spec = 1;
                            if (default_call_shared == 1) {
                                if (non_shared == 0) {
                                    old_non_shared = 1;
                                    non_shared = 1;
                                }
                                default_call_shared = 0;
                                call_shared = 0;
                            }
                        } else if ((strcmp(*(arg1 + (var_s0 * 4)), "-call_shared") == 0) && ((strcmp(*(arg1 + (var_s0 * 4)), "-count") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-countall") == 0))) {
                            addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-call_shared") == 0) {
                            non_shared = 0;
                            call_shared = 1;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-crt0") == 0) {
                            CRTX = "crt0.o";
                            MCRTX = "mcrt0.o";
                            crtn_required = 0;
                            relocate_passes("r", NULL, NULL);
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-crt1") == 0) {
                            temp_t4_9 = ansichoice;
                            if ((temp_t4_9 == 1) || (temp_t4_9 == 2)) {
                                CRTX = "acrt1.o";
                            } else {
                                CRTX = "crt1.o";
                            }
                            MCRTX = "mcrt1.o";
                            crtn_required = 1;
                            relocate_passes("r", NULL, NULL);
                        } else if ((compiler == 2) && (strcmp(*(arg1 + (var_s0 * 4)), "-casesense") == 0)) {
                            addstr(&upasflags, *(arg1 + (var_s0 * 4)));
                        } else if ((compiler == 3) && (strcmp(*(arg1 + (var_s0 * 4)), "-change_const") == 0)) {
                            addstr(&fcomflags, "-change_const");
                        } else if ((compiler == 3) && ((strcmp(*(arg1 + (var_s0 * 4)), "-col120") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-col72") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-chararg1") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-chunk") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-check_bounds") == 0))) {
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-col120") == 0) {
                                mp_col120flag = 1;
                            }
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-check_bounds") == 0) {
                                addstr(&fcomflags, "-C");
                            } else if (strncmp(*(arg1 + (var_s0 * 4)), "-chunk=", strlen("-chunk=")) == 0) {
                                sp10C = strlen("-chunk=") + *(arg1 + (var_s0 * 4));
                                if (*sp10C != 0) {
                                    do {
                                        temp_t2_4 = &__ctype[*sp10C];
                                        if (temp_t2_4->unk_1 & 1) {
                                            *sp10C = temp_t2_4->unk_102;
                                        } else {
                                            *sp10C = *sp10C;
                                        }
                                        sp10C += 1;
                                    } while (*sp10C != 0);
                                }
                                addstr(&fcomflags, mkstr("-mp_chunk=", strlen("-chunk=") + *(arg1 + (var_s0 * 4)), NULL));
                            } else {
                                addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                                if (strncmp(*(arg1 + (var_s0 * 4)), "-col", 4U) == 0) {
                                    add_static_opt(*(arg1 + (var_s0 * 4)));
                                }
                            }
                        } else if ((compiler == 6) && (strcmp(*(arg1 + (var_s0 * 4)), "-comp_trunc") == 0)) {
                            addstr(&ucobflags, *(arg1 + (var_s0 * 4)));
                        } else if ((compiler == 1) && (strcmp(*(arg1 + (var_s0 * 4)), "-check_registry") == 0)) {
                            var_s0 += 1;
                            if (var_s0 >= arg0) {
                                error(1, NULL, 0, NULL, 0, "-check_registry requires a filename argument\n");
                                exit(2);
                            }
                            addstr(&ldflags, (arg1 + (var_s0 * 4))->unk_-4);
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x64:                      /* switch 1 */
                        if ((compiler == 1) && (strcmp(*(arg1 + (var_s0 * 4)), "-dollar") == 0)) {
                            addstr(&pcaflags, "-dollar");
                            addstr(&mpcflags, "-dollar");
                            addstr(&soptflags, "-dollar");
                            addstr(&cfeflags, "-Xdollar");
                            add_static_opt(*(arg1 + (var_s0 * 4)));
                            dollar_sign += 1;
                        } else if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-ddoptinfo") == 0) {
                            ddoptinfo = 1;
                        } else if ((strcmp(*(arg1 + (var_s0 * 4)), "-dy") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-dn") == 0)) {
                            if (G_flag != 0) {
                                error(1, NULL, 0, NULL, 0, "-dn can not be used with -G \n");
                                exit(2);
                            }
                            dn_flag = 1;
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-ddopt") == 0) {
                            ddoptflag = 1;
                        } else if ((compiler == 3) && (strcmp(*(arg1 + (var_s0 * 4)), "-d_lines") == 0)) {
                            mp_dlinesflag = 1;
                            addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                            add_static_opt(*(arg1 + (var_s0 * 4)));
                        } else if ((compiler == 5) && (strcmp(*(arg1 + (var_s0 * 4)), "-defext") == 0)) {
                            addstr(&ulpiflags, *(arg1 + (var_s0 * 4)));
                        } else if ((compiler == 6) && ((strcmp(*(arg1 + (var_s0 * 4)), "-dline") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-defext") == 0))) {
                            addstr(&ucobflags, *(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-delay_load") == 0) {
                            addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                        } else if ((compiler == 1) && (strcmp(*(arg1 + (var_s0 * 4)), "-default_delay_load") == 0)) {
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x65:                      /* switch 1 */
                        if (strcmp(*(arg1 + (var_s0 * 4)), "-excpt") == 0) {
                            error(1, NULL, 0, NULL, 0, "-excpt is not supported in svr4 env.\n");
                            exit(2);
                        }
                        if (compiler == 1) {
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-elf") == 0) {
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                            } else if ((strcmp(*(arg1 + (var_s0 * 4)), "-export") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-exports") == 0)) {
                                addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-exported_symbol") == 0) {
                                var_s0 += 1;
                                if ((var_s0 >= arg0) || (**(arg1 + (var_s0 * 4)) == 0x2D)) {
                                    error(1, NULL, 0, NULL, 0, "-exported_symbol requires a symbol argument\n");
                                    exit(2);
                                }
                                addstr(&ldflags, (arg1 + (var_s0 * 4))->unk_-4);
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-exports_file") == 0) {
                                var_s0 += 1;
                                if ((var_s0 >= arg0) || (**(arg1 + (var_s0 * 4)) == 0x2D)) {
                                    error(1, NULL, 0, NULL, 0, "-exports_file requires a filename argument\n");
                                    exit(2);
                                }
                                addstr(&ldflags, (arg1 + (var_s0 * 4))->unk_-4);
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-exclude") == 0) {
                                var_s0 += 1;
                                if ((var_s0 >= arg0) || (**(arg1 + (var_s0 * 4)) == 0x2D)) {
                                    error(1, NULL, 0, NULL, 0, "-exclude requires a filename argument\n");
                                    exit(2);
                                }
                                addstr(&objfiles, (arg1 + (var_s0 * 4))->unk_-4);
                                addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                            } else if ((compiler == 1) && ((temp_t9_3 = c_compiler_choice, (temp_t9_3 == 2)) || (temp_t9_3 == 3)) && (strcmp(*(arg1 + (var_s0 * 4)), "-exceptions") == 0)) {
                                if ((compiler != 1) || (c_compiler_choice != 3)) {
                                    exception_handling = 1;
                                    relocate_passes("f", NULL, NULL);
                                    if (access(cfe, 0x10) == -1) {
                                        exception_handling = 0;
                                        relocate_passes("f", NULL, NULL);
                                        goto block_1537;
                                    }
                                } else {
                                    goto block_1537;
                                }
                            } else {
                                goto block_643;
                            }
                        } else {
block_643:
                            if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                                var_s0 += 1;
                                if (var_s0 < arg0) {
                                    addstr(&ldflags, "-e");
                                    addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                                } else {
                                    error(1, NULL, 0, NULL, 0, "ld requires -e to have an argument\n");
                                    exit(2);
                                    goto block_647;
                                }
                            } else {
block_647:
                                if (strcmp(*(arg1 + (var_s0 * 4)), "-exact_version") == 0) {
                                    addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                                } else if (strcmp(*(arg1 + (var_s0 * 4)), "-elf") == 0) {
                                    elfflag = 1;
                                    elf_spec = 1;
                                    addstr(&asflags, *(arg1 + (var_s0 * 4)));
                                    addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                                } else if ((compiler == 3) && (strcmp(*(arg1 + (var_s0 * 4)), "-extend_source") == 0)) {
                                    mp_extendflag = 1;
                                    addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                                    add_static_opt(*(arg1 + (var_s0 * 4)));
                                } else if ((compiler == 3) && (strcmp(*(arg1 + (var_s0 * 4)), "-expand_include") == 0)) {
                                    addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                                } else if (strncmp(*(arg1 + (var_s0 * 4)), "-edit", 5U) == 0) {
                                    if ((*(arg1 + (var_s0 * 4)))->unk_5 == 0) {
                                        edit_cnt_max = 0x100;
                                    } else if ((__ctype[(*(arg1 + (var_s0 * 4)))->unk_5].unk_1 & 4) && ((*(arg1 + (var_s0 * 4)))->unk_6 == 0)) {
                                        edit_cnt_max = (*(arg1 + (var_s0 * 4)))->unk_5 - 0x30;
                                    } else {
                                        error(1, NULL, 0, NULL, 0, "the correct -edit option sybtax is -edit[0-9]\n");
                                        exit(2);
                                    }
                                    editflag = 1;
                                    editor = getenv("EDITOR");
                                    temp_t8_6 = editor;
                                    if (temp_t8_6 != NULL) {
                                        var_s2_8 = temp_t8_6;
                                        if (strlen(var_s2_8) >= 5U) {
loop_666:
                                            if (strncmp(var_s2_8, "emacs", 5U) == 0) {
                                                editflag = 2;
                                            } else {
                                                var_s2_8 += 1;
                                                if (strlen(var_s2_8) >= 5U) {
                                                    goto loop_666;
                                                }
                                            }
                                        }
                                    }
                                    if ((editflag == 1) && (editor == NULL)) {
                                        editor = "vi";
                                    }
                                    xserver = getenv("DISPLAY");
                                    if ((ioctl(2, 0x40047477, &sp108) == 0) && (getpgrp() == sp108) && (xserver == NULL)) {
                                        editflag = 0;
                                        error(2, NULL, 0, NULL, 0, "%s ignored for background compile in non-X environment\n", *(arg1 + (var_s0 * 4)));
                                    }
                                } else {
                                    goto block_1537;
                                }
                            }
                        }
                        break;
                    case 0x66:                      /* switch 1 */
                        if ((strcmp(*(arg1 + (var_s0 * 4)), "-full_transtive_link") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-full_transitive_link") == 0)) {
                            full_transitive_link = 1;
                            transitive_link = 0;
                            no_transitive_link = 0;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-feedback") == 0) {
                            var_s0 += 1;
                            if (var_s0 < arg0) {
                                addstr(&feedlist, *(arg1 + (var_s0 * 4)));
                            } else {
                                error(1, NULL, 0, NULL, 0, "-feedback must have an argument\n");
                                exit(2);
                                goto block_683;
                            }
                        } else {
block_683:
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-fullasopt") == 0) {
                                fullasoptflag = 1;
                            } else if ((compiler == 1) && (strcmp(*(arg1 + (var_s0 * 4)), "-force_load") == 0)) {
                                addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                            } else if ((strcmp(*(arg1 + (var_s0 * 4)), "-fullwarn") == 0) && (fullwarn = 1, (compiler == 1))) {
                                addstr(&accomflags, "-Xfullwarn");
                                addstr(&cfeflags, "-verbose");
                                addstr(&cfeflags, "-wimplicit");
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-framepointer") == 0) {
                                if (compiler == 1) {
                                    addstr(&ccomflags, *(arg1 + (var_s0 * 4)));
                                } else if (compiler == 2) {
                                    addstr(&upasflags, *(arg1 + (var_s0 * 4)));
                                } else if (compiler == 3) {
                                    addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                                } else {
                                    goto block_1537;
                                }
                            } else if ((compiler == 1) && (strcmp(*(arg1 + (var_s0 * 4)), "-float") == 0)) {
                                addstr(&pcaflags, "-float");
                                addstr(&soptflags, "-float");
                                addstr(&ccomflags, "-Xfloat");
                            } else {
                                temp_t7_5 = compiler;
                                if (((temp_t7_5 != 4) && (temp_t7_5 != 2)) || (strcmp(*(arg1 + (var_s0 * 4)), "-float") != 0)) {
                                    if (compiler == 6) {
                                        if (strcmp(*(arg1 + (var_s0 * 4)), "-fsc74") == 0) {
                                            addstr(&ucobflags, *(arg1 + (var_s0 * 4)));
                                        } else if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                                            var_s0 += 1;
                                            if ((var_s0 < arg0) && (addstr(&ucobflags, "-f"), ((*(arg1 + (var_s0 * 4)))->unk_1 == 0)) && ((s32) **(arg1 + (var_s0 * 4)) >= 0x31) && ((s32) **(arg1 + (var_s0 * 4)) < 0x35)) {
                                                addstr(&ucobflags, *(arg1 + (var_s0 * 4)));
                                            } else {
                                                error(1, NULL, 0, NULL, 0, "-f requires an argument of 1, 2, 3 or 4\n");
                                                exit(2);
                                                goto block_714;
                                            }
                                        } else {
                                            goto block_1537;
                                        }
                                    } else {
block_714:
                                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                                            var_s0 += 1;
                                            if (var_s0 < arg0) {
                                                addstr(&ldflags, "-f");
                                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                                            } else {
                                                error(1, NULL, 0, NULL, 0, "ld requires -f to have an argument\n");
                                                exit(2);
                                                goto block_1537;
                                            }
                                        } else {
                                            goto block_1537;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case 0x67:                      /* switch 1 */
                        plain_g = 0;
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            gflag = 2;
                            plain_g = 1;
                            if (plain_O != 0) {
                                Oflag = 1;
                            }
                        } else if (((*(arg1 + (var_s0 * 4)))->unk_3 == 0) && ((s32) (*(arg1 + (var_s0 * 4)))->unk_2 >= 0x30) && ((s32) (*(arg1 + (var_s0 * 4)))->unk_2 < 0x34)) {
                            temp_t6_6 = (*(arg1 + (var_s0 * 4)))->unk_2 - 0x30;
                            gflag = temp_t6_6;
                            if (temp_t6_6 == 2) {
                                plain_g = 1;
                                if (plain_O != 0) {
                                    Oflag = 1;
                                }
                            }
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x68:                      /* switch 1 */
                        if (strcmp(*(arg1 + (var_s0 * 4)), "-hostcache") == 0) {
                            addstr(&ddoptflags, *(arg1 + (var_s0 * 4)));
                        } else if (strncmp(*(arg1 + (var_s0 * 4)), "-help", 5U) == 0) {
                            error(2, NULL, 0, NULL, 0, "-help is ignored.\n");
                        } else if (compiler == 1) {
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-hides") == 0) {
                                addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-hidden_symbol") == 0) {
                                var_s0 += 1;
                                if ((var_s0 >= arg0) || (**(arg1 + (var_s0 * 4)) == 0x2D)) {
                                    error(1, NULL, 0, NULL, 0, "-hidden_symbol requires a symbol argument\n");
                                    exit(2);
                                }
                                addstr(&ldflags, (arg1 + (var_s0 * 4))->unk_-4);
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-hides_file") == 0) {
                                var_s0 += 1;
                                if ((var_s0 >= arg0) || (**(arg1 + (var_s0 * 4)) == 0x2D)) {
                                    error(1, NULL, 0, NULL, 0, "-hides_file requires a filename argument\n");
                                    exit(2);
                                }
                                addstr(&ldflags, (arg1 + (var_s0 * 4))->unk_-4);
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                            } else {
                                goto block_744;
                            }
                        } else {
block_744:
                            temp_t5_6 = *(arg1 + (var_s0 * 4)) + 2;
                            hstring = temp_t5_6;
                            temp_t7_6 = hstring;
                            if (temp_t7_6[strlen(temp_t5_6)].unk_-1 != 0x2F) {
                                hstring = mkstr(temp_t7_6, "/", NULL);
                            }
                        }
                        break;
                    case 0x69:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            var_s0 += 1;
                            if (var_s0 < arg0) {
                                addstr(&ldflags, "-i");
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                            } else {
                                error(1, NULL, 0, NULL, 0, "ld requires -i to have an argument\n");
                                exit(2);
                                goto block_750;
                            }
                        } else {
block_750:
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-inline_to") == 0) {
                                addstr(&umergeflags, *(arg1 + (var_s0 * 4)));
                                var_s0 += 1;
                                if (var_s0 >= arg0) {
                                    error(1, NULL, 0, NULL, 0, "-inline_to must have an argument\n");
                                    exit(2);
                                }
                                var_s2_9 = Gnum;
                                if ((u8) *var_s2_9 != 0) {
                                    do {
                                        if (!(__ctype[(u8) var_s2_9->unk_0].unk_1 & 4)) {
                                            error(1, NULL, 0, NULL, 0, "non-digit character in -G %s\n", *(arg1 + (var_s0 * 4)));
                                            exit(2);
                                        }
                                        temp_t7_7 = var_s2_9->unk_1;
                                        var_s2_9 += 1;
                                    } while (temp_t7_7 != 0);
                                }
                                addstr(&umergeflags, *(arg1 + (var_s0 * 4)));
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-ignore_unresolved") == 0) {
                                ignore_unresolved_flag = 1;
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-ignore_minor") == 0) {
                                addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-irix4") == 0) {
                                irix4 = 1;
                                comp_host_root = "/usr/irix4/";
                                Gnum = "8";
                                systype = "";
                                elfflag = 0;
                                svr4_systype = 0;
                                kpic_flag = 0;
                                default_call_shared = 0;
                                call_shared = 0;
                                non_shared = 0;
                                old_non_shared = 0;
                                mips_abi = 0;
                                relocate_passes("pKfjrsulmvocabtyz", NULL, NULL);
                                add_static_opt(*(arg1 + (var_s0 * 4)));
                            } else if (((compiler == 3) && ((strcmp(*(arg1 + (var_s0 * 4)), "-i2") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-i4") == 0))) || (strcmp(*(arg1 + (var_s0 * 4)), "-i8") == 0)) {
                                if (((*(arg1 + (var_s0 * 4)))->unk_2 == 0x32) || ((*(arg1 + (var_s0 * 4)))->unk_2 == 0x38)) {
                                    mp_i2flag = 1;
                                }
                                addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                            } else if (compiler == 5) {
                                if (strcmp(*(arg1 + (var_s0 * 4)), "-ipath") == 0) {
                                    var_s0 += 1;
                                    if (var_s0 < arg0) {
                                        addstr(&upl1flags, "-ipath");
                                        addstr(&upl1flags, *(arg1 + (var_s0 * 4)));
                                    } else {
                                        error(1, NULL, 0, NULL, 0, "-ipath must have an argument\n");
                                        exit(2);
                                        goto block_777;
                                    }
                                } else {
block_777:
                                    if (strcmp(*(arg1 + (var_s0 * 4)), "-isuffix") == 0) {
                                        var_s0 += 1;
                                        if (var_s0 < arg0) {
                                            addstr(&upl1flags, "-isuffix");
                                            addstr(&upl1flags, *(arg1 + (var_s0 * 4)));
                                        } else {
                                            error(1, NULL, 0, NULL, 0, "-isuffix must have an argument\n");
                                            exit(2);
                                            goto block_1537;
                                        }
                                    } else {
                                        goto block_1537;
                                    }
                                }
                            } else {
                                goto block_1537;
                            }
                        }
                        break;
                    case 0x6A:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            jflag += 1;
                            uload = 0;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-jalr") == 0) {
                            addstr(&genflags, *(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-jmpopt") == 0) {
                            addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x6B:                      /* switch 1 */
                        if (strcmp(*(arg1 + (var_s0 * 4)), "-keep") == 0) {
                            Kflag += 1;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-kpicopt") == 0) {
                            kpicopt_flag = 1;
                        } else {
                            temp_s4_2 = (*(arg1 + (var_s0 * 4)))->unk_2;
                            switch (temp_s4_2) {    /* switch 7; irregular */
                                case 0x6F:          /* switch 7 */
                                    var_s0 += 1;
                                    if ((var_s0 < arg0) && ((temp_t7_8 = *(arg1 + (var_s0 * 4)), uoutfile = temp_t7_8, var_s1 = getsuf(temp_t7_8) & 0xFF, (var_s1 == 0x63)) || (var_s1 == 0x70) || (var_s1 == 0x66) || (var_s1 == 0x46) || (var_s1 == 0x72) || (var_s1 == 0x65) || (var_s1 == 6) || (var_s1 == 0x73) || (var_s1 == 1) || (var_s1 == 2))) {
                                        error(1, NULL, 0, NULL, 0, "-ko would overwrite %s\n", *(arg1 + (var_s0 * 4)));
                                        exit(2);
                                    }
                                    break;
                                case 0x70:          /* switch 7 */
                                    var_s0 += 1;
                                    if (var_s0 < arg0) {
                                        addstr(&uldflags, "-kp");
                                        addstr(&uldflags, *(arg1 + (var_s0 * 4)));
                                    }
                                    break;
                                case 0x75:          /* switch 7 */
                                    var_s0 += 1;
                                    if (var_s0 < arg0) {
                                        addstr(&uldflags, "-ku");
                                        addstr(&uldflags, *(arg1 + (var_s0 * 4)));
                                    }
                                    break;
                                default:            /* switch 7 */
                                    addstr(&ufiles, *(arg1 + (var_s0 * 4)));
                                    break;
                            }
                        }
                        break;
                    case 0x6C:                      /* switch 1 */
                        if (strcmp("isting", *(arg1 + (var_s0 * 4)) + 2) == 0) {
                            addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                        } else {
                            if (((*(arg1 + (var_s0 * 4)))->unk_2 == 0x6D) && ((*(arg1 + (var_s0 * 4)))->unk_3 == 0)) {
                                lmflag += 1;
                                goto block_823;
                            }
                            if (((*(arg1 + (var_s0 * 4)))->unk_2 == 0) && ((var_s0 + 1) < arg0)) {
                                sp104 = malloc(strlen((arg1 + (var_s0 * 4))->unk_4) + 3);
                                sp104->unk_0 = 0x2D;
                                sp104->unk_1 = 0x6C;
                                sp104->unk_2 = 0;
                                if (xpg_flag != 0) {
                                    addstr(&dashlfiles, strcat(sp104, (arg1 + (var_s0 * 4))->unk_4));
                                } else {
                                    addstr(&objfiles, strcat(sp104, (arg1 + (var_s0 * 4))->unk_4));
                                }
                                var_s0 += 1;
                            } else {
block_823:
                                if (xpg_flag != 0) {
                                    addstr(&dashlfiles, *(arg1 + (var_s0 * 4)));
                                } else {
                                    addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                                }
                                if (strcmp(*(arg1 + (var_s0 * 4)), "-lgl_s") == 0) {
                                    B_1000ED2C += 1;
                                    addstr(&objfiles, "-lX11_s");
                                }
                                if (strcmp(*(arg1 + (var_s0 * 4)), "-lc_s") == 0) {
                                    B_1000ED30 += 1;
                                }
                            }
                        }
                        break;
                    case 0x6D:                      /* switch 1 */
                        if (strcmp(*(arg1 + (var_s0 * 4)), "-multigot") == 0) {
                            addstr(&nldflags, *(arg1 + (var_s0 * 4)));
                        } else if ((compiler == 1) && (strcmp(*(arg1 + (var_s0 * 4)), "-mp") == 0)) {
                            cmp_flag |= 0x10008;
                            if (Bflag != 0) {
                                error(1, NULL, 0, NULL, 0, "'-mp' must preceed any -B flags.\n");
                                exit(2);
                            }
                            relocate_passes("fY", NULL, NULL);
                        } else if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            temp_t1_3 = compiler;
                            if ((temp_t1_3 == 4) || (temp_t1_3 == 3)) {
                                mflag += 1;
                            } else {
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                            }
                            if (compiler == 3) {
                                add_static_opt(*(arg1 + (var_s0 * 4)));
                            }
                        } else if (compiler == 6) {
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-mfext") == 0) {
                                addstr(&ucobflags, *(arg1 + (var_s0 * 4)));
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-map") == 0) {
                                addstr(&ucobflags, *(arg1 + (var_s0 * 4)));
                            } else {
                                goto block_849;
                            }
                        } else {
block_849:
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-mips1") == 0) {
                                chip_targ = 0;
                                mips1flag = 1;
                                mips2flag = 0;
                                if (dwopcodeflag != 0) {
                                    error(1, NULL, 0, NULL, 0, "can't mix -mips1 with -dwopcode\n");
                                    exit(2);
                                }
                                if (mips2_spec_flag != 0) {
                                    error(2, NULL, 0, NULL, 0, "-mips1 conflicts with -mips2; using last value (mips1)\n");
                                    mips2_spec_flag = 0;
                                }
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-mips2") == 0) {
                                if ((mips1flag != 0) || (mips3flag != 0)) {
                                    error(2, NULL, 0, NULL, 0, "-mips2 conflicts with -mips1; using last value (mips2)\n");
                                }
                                mips1flag = 0;
                                mips2flag = 1;
                                mips2_spec_flag = 1;
                                relocate_passes("M", NULL, NULL);
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-mips3") == 0) {
                                mips1flag = 0;
                                mips2flag = 0;
                                if (mips2_spec_flag != 0) {
                                    error(1, NULL, 0, NULL, 0, "can't mix -mips3 with -mips[1,2]\n");
                                    exit(2);
                                }
                                temp_t0_2 = compiler;
                                if ((temp_t0_2 == 4) || (temp_t0_2 == 1)) {
                                    error(2, NULL, 0, NULL, 0, "-mips3 should not be used for ucode 32-bit compiles\n");
                                } else {
                                    error(1, NULL, 0, NULL, 0, "-mips3 cannot be used for ucode 32-bit compiles\n");
                                    exit(2);
                                }
                                chip_targ = 2;
                                mips3flag = 1;
                                dwopcodeflag = 1;
                                relocate_passes("M", NULL, NULL);
                                if (non_shared_emitted == 0) {
                                    addstr(&ldflags, "-non_shared");
                                    addstr(&cfeflags, "-non_shared");
                                    non_shared_emitted = 1;
                                }
                                addstr(&ccomflags, *(arg1 + (var_s0 * 4)));
                                addstr(&upasflags, *(arg1 + (var_s0 * 4)));
                                addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                                addstr(&upl1flags, *(arg1 + (var_s0 * 4)));
                                addstr(&ucobflags, *(arg1 + (var_s0 * 4)));
                                addstr(&ulpiflags, *(arg1 + (var_s0 * 4)));
                                addstr(&eflflags, *(arg1 + (var_s0 * 4)));
                                addstr(&ratforflags, *(arg1 + (var_s0 * 4)));
                                addstr(&ddoptflags, *(arg1 + (var_s0 * 4)));
                                addstr(&optflags, *(arg1 + (var_s0 * 4)));
                                addstr(&genflags, *(arg1 + (var_s0 * 4)));
                                addstr(&asflags, *(arg1 + (var_s0 * 4)));
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                                addstr(&ftocflags, *(arg1 + (var_s0 * 4)));
                            } else {
                                if (strcmp(*(arg1 + (var_s0 * 4)), "-mips4") == 0) {
                                    error(1, NULL, 0, NULL, 0, "-mips4 cannot be used for ucode 32-bit compiles\n");
                                    exit(2);
                                }
                                if (compiler == 3) {
                                    if (((*(arg1 + (var_s0 * 4)))->unk_2 == 0x70) && ((*(arg1 + (var_s0 * 4)))->unk_3 == 0)) {
                                        mp_flag |= 0x10000;
                                    } else if (strncmp(*(arg1 + (var_s0 * 4)), "-mp_keep", strlen("-mp_keep")) == 0) {
                                        if ((*(arg1 + (var_s0 * 4)))->unk_8 != 0) {
                                            error(1, NULL, 0, NULL, 0, " Unknown flag: %s\n", *(arg1 + (var_s0 * 4)));
                                            exit(2);
                                        }
                                        mp_flag |= 0x10000;
                                        showdirt_flag = 1;
                                    } else if (strncmp(*(arg1 + (var_s0 * 4)), "-mp_schedtype=", strlen("-mp_schedtype=")) == 0) {
                                        sp100 = strlen("-mp_schedtype=") + *(arg1 + (var_s0 * 4));
                                        if (*sp100 != 0) {
                                            do {
                                                temp_t8_7 = &__ctype[*sp100];
                                                if (temp_t8_7->unk_1 & 1) {
                                                    *sp100 = temp_t8_7->unk_102;
                                                } else {
                                                    *sp100 = *sp100;
                                                }
                                                sp100 += 1;
                                            } while (*sp100 != 0);
                                        }
                                        addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                                    } else {
                                        goto block_1537;
                                    }
                                } else {
                                    goto block_1537;
                                }
                            }
                        }
                        break;
                    case 0x6E:                      /* switch 1 */
                        if (strcmp(*(arg1 + (var_s0 * 4)), "-nokpicopt") == 0) {
                            nokpicopt_flag = 1;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-no_unresolved") == 0) {
                            no_unresolved_flag = 1;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-no_transitive_link") == 0) {
                            transitive_link = 0;
                            full_transitive_link = 0;
                            no_transitive_link = 1;
                        } else if ((compiler == 1) && ((temp_t4_10 = c_compiler_choice, (temp_t4_10 == 2)) || (temp_t4_10 == 3)) && (strcmp(*(arg1 + (var_s0 * 4)), "-no_exceptions") == 0)) {
                            if ((compiler != 1) || (c_compiler_choice != 3)) {
                                exception_handling = 0;
                                relocate_passes("f", NULL, NULL);
                            } else {
                                goto block_1537;
                            }
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-new_ld") == 0) {
                            if (D_1000BF94 != 0) {
                                error(1, NULL, 0, NULL, 0, "malformed or unknown option: -new_ld\n");
                                exit(2);
                            } else if ((compiler == 1) && (c_compiler_choice == 3)) {
                                error(1, NULL, 0, NULL, 0, "-new_ld not supported for DCC\n");
                                exit(2);
                            } else {
                                LD = "ld";
                                D_1000BF90 = 0;
                            }
                            relocate_passes("l", NULL, NULL);
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-noinline") == 0) {
                            addstr(&umergeflags, *(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-nouopt0") == 0) {
                            uopt0flag = 0;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-noaliasok") == 0) {
                            noaliasokflag = 1;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-nostdinc") == 0) {
                            emptyIflag = 1;
                            add_static_opt(*(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-nostdlib") == 0) {
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                            addstr(&prelinkerflags, mkstr("-YB", NULL));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-nodeflib") == 0) {
                            nodeflib = 1;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-noprototypes") == 0) {
                            prototype_checking_on = 0;
                        } else if (((*(arg1 + (var_s0 * 4)))->unk_2 == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-nocount") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-nN") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-nojmpopt") == 0)) {
                            addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-non_shared") == 0) {
                            old_non_shared = 0;
                            non_shared = 1;
                            default_call_shared = 0;
                            call_shared = 0;
                            kpic_flag = 0;
                            if (non_shared_emitted == 0) {
                                addstr(&ldflags, "-non_shared");
                                addstr(&cfeflags, "-non_shared");
                                non_shared_emitted = 1;
                            }
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-no_archive") == 0) {
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-no_mpc") == 0) {
                            B_1000ED74 = 1;
                        } else if ((compiler == 3) && ((strcmp(*(arg1 + (var_s0 * 4)), "-noextend_source") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-noi4") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-noisam") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-noexpopt") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-noequivauto") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-nof77") == 0))) {
                            addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                            add_static_opt(*(arg1 + (var_s0 * 4)));
                        } else if (compiler == 6) {
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-nolock") == 0) {
                                nolockflag = 1;
                            } else if ((strcmp(*(arg1 + (var_s0 * 4)), "-nomfdata") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-normdata") == 0)) {
                                addstr(&ucobflags, *(arg1 + (var_s0 * 4)));
                            } else {
                                goto block_1537;
                            }
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-nocpp") == 0) {
                            if ((compiler == 1) && (c_compiler_choice != 0)) {
                                error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", *(arg1 + (var_s0 * 4)), "");
                            } else {
                                docpp = 0;
                                add_static_opt(*(arg1 + (var_s0 * 4)));
                            }
                        } else {
                            temp_t1_4 = compiler;
                            if ((temp_t1_4 == 3) || ((temp_t1_4 == 1) && (c_compiler_choice != 0))) {
                                if (strcmp(*(arg1 + (var_s0 * 4)), "-nocode") == 0) {
                                    nocode = 1;
                                    cflag = 1;
                                } else if (strcmp(*(arg1 + (var_s0 * 4)), "-no_prelink") == 0) {
                                    no_prelink = 1;
                                } else if (strcmp(*(arg1 + (var_s0 * 4)), "-no_auto_include") == 0) {
                                    auto_template_include = 0;
                                    add_static_opt(*(arg1 + (var_s0 * 4)));
                                } else {
                                    goto block_961;
                                }
                            } else {
block_961:
                                if (strcmp(*(arg1 + (var_s0 * 4)), "-none") == 0) {
                                    addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                                } else if ((compiler == 1) && ((temp_t9_4 = c_compiler_choice, (temp_t9_4 == 2)) || (temp_t9_4 == 3)) && (strcmp(*(arg1 + (var_s0 * 4)), "-nofilt") == 0)) {
                                    nofilt = 1;
                                    add_static_opt(*(arg1 + (var_s0 * 4)));
                                } else if ((compiler == 1) && (c_compiler_choice == 3) && (strncmp(*(arg1 + (var_s0 * 4)), "-no_delta", 9U) == 0)) {
                                    if ((*(arg1 + (var_s0 * 4)))->unk_9 == 0) {
                                        spFC = "-YDN";
                                    } else if (strcmp(*(arg1 + (var_s0 * 4)) + 9, "_expr") == 0) {
                                        spFC = "-YDE";
                                    } else if (strcmp(*(arg1 + (var_s0 * 4)) + 9, "_include") == 0) {
                                        spFC = "-YDI";
                                    } else {
                                        spFC = NULL;
                                    }
                                    if (spFC != NULL) {
                                        if (var_s0 >= (arg0 - 1)) {
                                            error(1, NULL, 0, NULL, 0, "%s must have an argument\n", *(arg1 + (var_s0 * 4)));
                                            exit(2);
                                        }
                                        var_s0 += 1;
                                        if (**(arg1 + (var_s0 * 4)) == 0x2D) {
                                            error(1, NULL, 0, NULL, 0, "%s must have an argument\n", (arg1 + (var_s0 * 4))->unk_-4);
                                            exit(2);
                                        }
                                        addstr(&edisonflags, mkstr(spFC, *(arg1 + (var_s0 * 4)), NULL));
                                        add_static_opt((arg1 + (var_s0 * 4))->unk_-4);
                                        add_static_opt(*(arg1 + (var_s0 * 4)));
                                    } else {
                                        goto block_1537;
                                    }
                                } else {
                                    goto block_1537;
                                }
                            }
                        }
                        break;
                    case 0x6F:                      /* switch 1 */
                        if (strcmp(*(arg1 + (var_s0 * 4)), "-old_rl") == 0) {
                            addstr(&fcomflags, "-old_rl");
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-oldcpp") == 0) {
                            if ((compiler == 1) && (c_compiler_choice != 0)) {
                                error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", *(arg1 + (var_s0 * 4)), "");
                            } else {
                                oldcppflag = 1;
                                if ((compiler == 1) && (tpflag != 0)) {
                                    relocate_passes(tstring, hstring, Bstring);
                                }
                            }
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-old_ld") == 0) {
                            if (D_1000BF94 != 0) {
                                error(1, NULL, 0, NULL, 0, "malformed or unknown option: -old_ld\n");
                                exit(2);
                            } else {
                                LD = "old_ld";
                                relocate_passes("l", NULL, NULL);
                            }
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-o32") == 0) {
                            thirty2bitflag = 1;
                            mips_abi = 1;
                            if (var_s0 >= (arg0 - 1)) {
                                func_00431B38(var_s0 + 1, 1);
                            }
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-objectlist") == 0) {
                            if (((arg1 + (var_s0 * 4))->unk_4 != 0) && (*(arg1 + (var_s0 * 4))->unk_4 != 0x2D)) {
                                addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                                var_s0 += 1;
                                addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                            } else {
                                error(1, NULL, 0, NULL, 0, "-objectlist must be given a file argument\n");
                            }
                        } else if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            var_s0 += 1;
                            if (var_s0 < arg0) {
                                temp_t9_5 = *(arg1 + (var_s0 * 4));
                                outfile = temp_t9_5;
                                var_s1 = getsuf(temp_t9_5) & 0xFF;
                                if (((var_s1 == 0x63) || (var_s1 == 0x70) || (var_s1 == 0x66) || (var_s1 == 0x46) || (var_s1 == 0x72) || (var_s1 == 0x65) || ((compiler == 1) && ((temp_t4_11 = c_compiler_choice, (temp_t4_11 == 2)) || (temp_t4_11 == 3)) && (var_s1 == 6)) || (var_s1 == 0x73) || (var_s1 == 1) || (var_s1 == 2)) && (stat(outfile, &sp74) == 0)) {
                                    error(1, NULL, 0, NULL, 0, "-o %s resembles the name of a source file, disallowed\n", *(arg1 + (var_s0 * 4)));
                                    exit(2);
                                }
                                B_1000ECCC = mkstr(outfile, NULL);
                                func_00431B38(var_s0, 2);
                            } else {
                                error(1, NULL, 0, NULL, 0, "-o must have an argument\n");
                                exit(2);
                                goto block_1024;
                            }
                        } else {
block_1024:
                            if ((compiler == 3) && (strcmp(*(arg1 + (var_s0 * 4)), "-onetrip") == 0)) {
                                addstr(&fcomflags, "-1");
                                mp_onetripflag = 1;
                            } else {
                                goto block_1537;
                            }
                        }
                        break;
                    case 0x70:                      /* switch 1 */
                        if (strcmp(*(arg1 + (var_s0 * 4)), "-prototypes") == 0) {
                            if ((compiler == 1) && (c_compiler_choice != 0)) {
                                error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", *(arg1 + (var_s0 * 4)), "");
                            } else {
                                prototype_checking_on = 1;
                            }
                        } else if ((compiler == 1) && (strcmp(*(arg1 + (var_s0 * 4)), "-pedantic") == 0)) {
                            if ((compiler == 1) && (c_compiler_choice != 0)) {
                                error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", *(arg1 + (var_s0 * 4)), "");
                            } else {
                                addstr(&acppflags, "-p");
                            }
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-pfa") == 0) {
                            mp_flag |= 0x10001;
                            if ((var_s0 + 1) < arg0) {
                                sp70 = mpflags;
                                temp_t1_5 = *mpflags;
                                if ((temp_t1_5 != NULL) && (strcmp((arg1 + (var_s0 * 4))->unk_4, temp_t1_5) != 0)) {
loop_1042:
                                    sp70 += 8;
                                    temp_t6_7 = sp70->unk_0;
                                    if (temp_t6_7 != NULL) {
                                        if (strcmp((arg1 + (var_s0 * 4))->unk_4, temp_t6_7) != 0) {
                                            goto loop_1042;
                                        }
                                    }
                                }
                                if (sp70->unk_0 != NULL) {
                                    var_s0 += 1;
                                    mp_flag |= sp70->unk_4;
                                }
                            }
                        } else if (strncmp(*(arg1 + (var_s0 * 4)), "-pfaprepass,", 0xCU) == 0) {
                            mp_flag |= 0x10001;
                            mp_prepass_count += 1;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-pca") == 0) {
                            cmp_flag |= 0x10001;
                            if (Bflag != 0) {
                                error(1, NULL, 0, NULL, 0, "-pca must preceed any -B flags.\n");
                                exit(2);
                            }
                            relocate_passes("fKY", NULL, NULL);
                            if ((var_s0 + 1) < arg0) {
                                sp6C = cmpflags;
                                temp_t1_6 = *cmpflags;
                                if ((temp_t1_6 != NULL) && (strcmp((arg1 + (var_s0 * 4))->unk_4, temp_t1_6) != 0)) {
loop_1054:
                                    sp6C += 8;
                                    temp_t8_8 = sp6C->unk_0;
                                    if (temp_t8_8 != NULL) {
                                        if (strcmp((arg1 + (var_s0 * 4))->unk_4, temp_t8_8) != 0) {
                                            goto loop_1054;
                                        }
                                    }
                                }
                                if (sp6C->unk_0 != NULL) {
                                    var_s0 += 1;
                                    cmp_flag |= sp6C->unk_4;
                                }
                            }
                        } else if ((compiler == 1) && ((temp_t9_6 = c_compiler_choice, (temp_t9_6 == 2)) || (temp_t9_6 == 3))) {
                            if (strncmp(*(arg1 + (var_s0 * 4)), "-pt", 3U) == 0) {
                                temp_t6_8 = *(arg1 + (var_s0 * 4)) + 3;
                                sp68 = temp_t6_8;
                                if (strcmp(temp_t6_8, "v") == 0) {
                                    verbose_prelink += 1;
                                } else if (strcmp(sp68, "none") == 0) {
                                    default_template_instantiation_mode = 0;
                                } else if (strcmp(sp68, "used") == 0) {
                                    default_template_instantiation_mode = 1;
                                } else if ((strcmp(sp68, "a") == 0) || (strcmp(sp68, "all") == 0)) {
                                    default_template_instantiation_mode = 2;
                                } else if ((u8) *sp68 == 0x65) {
                                    if ((strcmp(sp68 + 1, ".c") != 0) && (strcmp(sp68 + 1, ".cc") != 0) && (strcmp(sp68 + 1, ".c++") != 0) && (strcmp(sp68 + 1, ".C") != 0) && (strcmp(sp68 + 1, ".cxx") != 0) && (strcmp(sp68 + 1, ".CXX") != 0) && (strcmp(sp68 + 1, ".cpp") != 0) && (strcmp(sp68 + 1, ".CPP") != 0)) {
                                        error(2, NULL, 0, NULL, 0, "unsupported suffix in %s\n", *(arg1 + (var_s0 * 4)));
                                    }
                                } else {
                                    error(2, NULL, 0, NULL, 0, "ignored unsupported option %s\n", *(arg1 + (var_s0 * 4)));
                                }
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-prelink") == 0) {
                                force_prelink = 1;
                            } else {
                                goto block_1084;
                            }
                        } else {
block_1084:
                            if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                                pflag = 1;
                                goto block_1093;
                            }
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-pg") == 0) {
                                var_t2 = 1;
                                pflag = 1;
                                var_at = &pgflag;
                                goto block_1092;
                            }
                            if (((*(arg1 + (var_s0 * 4)))->unk_3 == 0) && ((s32) (*(arg1 + (var_s0 * 4)))->unk_2 >= 0x30) && ((s32) (*(arg1 + (var_s0 * 4)))->unk_2 < 0x34)) {
                                var_at = &pflag;
                                var_t2 = (*(arg1 + (var_s0 * 4)))->unk_2 - 0x30;
block_1092:
                                *var_at = var_t2;
block_1093:
                                temp_t9_7 = pflag;
                                if ((temp_t9_7 == 0) || (temp_t9_7 == 1)) {
                                    if (Bflag != 0) {
                                        error(1, NULL, 0, NULL, 0, "-p0 or -p1 must precede any -B flags\n");
                                        exit(2);
                                    }
                                } else {
                                    error(1, NULL, 0, NULL, 0, "%s has been superseded, see prof (1) and pixie (1)\n", *(arg1 + (var_s0 * 4)));
                                    exit(2);
                                }
                                relocate_passes("rn", NULL, NULL);
                            } else {
                                goto block_1537;
                            }
                        }
                        break;
                    case 0x71:                      /* switch 1 */
                        if (strcmp(*(arg1 + (var_s0 * 4)), "-quickstart_info") == 0) {
                            quickstart_info = 1;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-ql") != 0) {
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-qp") == 0) {

                            } else {
                                goto block_1537;
                            }
                        }
                        break;
                    case 0x72:                      /* switch 1 */
                        if ((strcmp(*(arg1 + (var_s0 * 4)), "-r4000") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-r6000") == 0)) {
                            addstr(&asflags, *(arg1 + (var_s0 * 4)));
                        } else if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-require_minor") == 0) {
                            addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-rm_dead_code") == 0) {
                            force_rm_dead_code = 1;
                        } else if ((strcmp(*(arg1 + (var_s0 * 4)), "-rpath") == 0) && ((arg1 + (var_s0 * 4))->unk_4 != 0) && (*(arg1 + (var_s0 * 4))->unk_4 != 0x2D)) {
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                            var_s0 += 1;
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                        } else if ((strcmp(*(arg1 + (var_s0 * 4)), "-rdata_shared") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-rdata_writable") == 0)) {
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                        } else if ((compiler == 3) && (strcmp(*(arg1 + (var_s0 * 4)), "-r8") == 0)) {
                            addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                        } else if ((compiler == 6) && ((strcmp(*(arg1 + (var_s0 * 4)), "-range") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-rmansi") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-rmext") == 0))) {
                            addstr(&ucobflags, *(arg1 + (var_s0 * 4)));
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x73:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            if ((compiler == 1) && ((temp_t4_12 = c_compiler_choice, (temp_t4_12 == 2)) || (temp_t4_12 == 3))) {
                                do_strip = 1;
                            } else {
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                            }
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-strictIEEE") == 0) {
                            addstr(&optflags, *(arg1 + (var_s0 * 4)));
                        } else if ((((compiler == 1) && (c_compiler_choice != 0)) || (compiler == 3)) && (strncmp(*(arg1 + (var_s0 * 4)), "-sa", 3U) == 0) && (((*(arg1 + (var_s0 * 4)))->unk_3 == 0) || ((*(arg1 + (var_s0 * 4)))->unk_3 == 0x2C))) {
                            D_1000BF74 = 1;
                            if (((*(arg1 + (var_s0 * 4)))->unk_3 == 0x2C) && ((*(arg1 + (var_s0 * 4)))->unk_4 != 0)) {
                                sp64 = strtok(*(arg1 + (var_s0 * 4)) + 4, ",");
                                if (sp64 != NULL) {
                                    do {
                                        if (strcmp(sp64, "nosrc") == 0) {
                                            D_1000BF78 = 1;
                                        } else if (D_1000BF80 != NULL) {
                                            error(1, NULL, 0, NULL, 0, "Static analysis directory already specified\n");
                                        } else {
                                            D_1000BF80 = sp64;
                                            if (sp64[strlen(sp64)].unk_-1 != 0x2F) {
                                                D_1000BF80 = mkstr(sp64, "/", NULL);
                                            }
                                        }
                                        sp64 = strtok(0, ",");
                                    } while (sp64 != NULL);
                                }
                            }
                        } else if ((((compiler == 1) && (c_compiler_choice != 0)) || (compiler == 3)) && (strncmp(*(arg1 + (var_s0 * 4)), "-sa_fs", 6U) == 0) && (((*(arg1 + (var_s0 * 4)))->unk_6 == 0) || ((*(arg1 + (var_s0 * 4)))->unk_6 == 0x2C))) {
                            if ((*(arg1 + (var_s0 * 4)))->unk_6 == 0x2C) {
                                var_v0 = mkstr(*(arg1 + (var_s0 * 4)) + 7, NULL);
                            } else {
                                var_v0 = mkstr("cvstatic.fileset", NULL);
                            }
                            D_1000BF84 = var_v0;
                            D_1000BF88 += 1;
                        } else if ((compiler == 1) && (strcmp(*(arg1 + (var_s0 * 4)), "-set_version") == 0)) {
                            var_s0 += 1;
                            if (var_s0 >= arg0) {
                                error(1, NULL, 0, NULL, 0, "-set_version requires an argument\n");
                                exit(2);
                            }
                            addstr(&ldflags, (arg1 + (var_s0 * 4))->unk_-4);
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                        } else if ((compiler == 1) && (strcmp(*(arg1 + (var_s0 * 4)), "-soname") == 0)) {
                            var_s0 += 1;
                            if (var_s0 >= arg0) {
                                error(1, NULL, 0, NULL, 0, "-soname requires an argument\n");
                                exit(2);
                            }
                            addstr(&ldflags, (arg1 + (var_s0 * 4))->unk_-4);
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-systype") == 0) {
                            var_s0 += 1;
                            if (var_s0 >= arg0) {
                                error(1, NULL, 0, NULL, 0, "-systype must have an argument\n");
                                exit(2);
                            }
                            if (user_systype != 0) {
                                if (strcmp(systype, *(arg1 + (var_s0 * 4))) != 0) {
                                    error(1, NULL, 0, NULL, 0, "only one -systype option allowed\n");
                                    exit(2);
                                } else {
                                    multiple_systype = 1;
                                }
                            }
                            systype = *(arg1 + (var_s0 * 4));
                            user_systype = 1;
                            if ((Bflag != 0) && (systype_seen == 0)) {
                                error(1, NULL, 0, NULL, 0, "-systype must precede any -B flags\n");
                                exit(2);
                            } else {
                                systype_seen = 1;
                            }
                            if (multiple_systype == 0) {
                                if (strcmp(systype, "svr4") == 0) {
                                    svr4_systype = 1;
                                    if (elfflag == 0) {
                                        addstr(&asflags, "-elf");
                                        addstr(&ldflags, "-elf");
                                    }
                                    elfflag = 1;
                                } else {
                                    error(1, NULL, 0, NULL, 0, "Only systype svr4 allowed\n");
                                    exit(2);
                                }
                                if ((strcmp(systype, "svr4") != 0) && (strcmp(systype, "bsd43") != 0) && (strcmp(systype, "svr3") != 0) && (strcmp(systype, "sysv") != 0) && (fopen(strcat("/", systype), "r") == NULL)) {
                                    if (systype_warn == 0) {
                                        error(2, NULL, 0, NULL, 0, "This systype doesn't exist on this machine; changed systype to svr3.\n");
                                    }
                                    systype = "svr3";
                                }
                                if (svr4_systype == 0) {
                                    comp_target_root = mkstr(comp_target_root, systype, "/", NULL);
                                }
                                if (fiveflag != 0) {
                                    var_v0_2 = mkstr(comp_target_root, "usr/5include", NULL);
                                } else {
                                    einclude = mkstr(comp_target_root, "usr/include/CC", NULL);
                                    var_v0_2 = mkstr(comp_target_root, "usr/include", NULL);
                                }
                                include = var_v0_2;
                                temp_t6_9 = Bstring;
                                if (temp_t6_9 != NULL) {
                                    relocate_passes("h", NULL, temp_t6_9);
                                }
                                newrunlib();
                            }
                            add_static_opt(*(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-swopcode") == 0) {
                            if ((dwopcodeflag != 0) || (sixty4bitflag != 0)) {
                                error(1, NULL, 0, NULL, 0, "-swopcode can not be used with -dwopcode/-64bit\n");
                                exit(2);
                            }
                            swopcodeflag = 1;
                        } else if (((*(arg1 + (var_s0 * 4)))->unk_2 == 0x6F) && ((*(arg1 + (var_s0 * 4)))->unk_3 == 0x70) && ((*(arg1 + (var_s0 * 4)))->unk_4 == 0x74)) {
                            temp_t3_4 = compiler;
                            if ((temp_t3_4 != 1) && (temp_t3_4 != 3)) {
                                error(2, NULL, 0, NULL, 0, "-sopt only available with Fortran and C; option ignored.\n");
                            } else if ((compiler == 1) && (c_compiler_choice != 0)) {
                                error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", *(arg1 + (var_s0 * 4)), "");
                            } else {
                                temp_t8_9 = *(arg1 + (var_s0 * 4)) + 5;
                                Warg = temp_t8_9;
                                if ((u8) *temp_t8_9 == 0x2C) {
                                    do {
                                        Warg->unk_0 = 0;
                                        temp_t4_13 = Warg + 1;
                                        Warg = temp_t4_13;
                                        addstr(&soptflags, temp_t4_13);
                                        temp_t3_5 = (u8) Warg->unk_0;
                                        if ((temp_t3_5 != 0x2C) && (temp_t3_5 != 0)) {
loop_1225:
                                            Warg += 1;
                                            temp_t8_10 = (u8) Warg->unk_0;
                                            if (temp_t8_10 != 0x2C) {
                                                if (temp_t8_10 != 0) {
                                                    goto loop_1225;
                                                }
                                            }
                                        }
                                    } while ((u8) Warg->unk_0 == 0x2C);
                                }
                                run_sopt = 1;
                            }
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-show") == 0) {
                            vflag = 1;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-showt") == 0) {
                            time_flag = 1;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-show0") == 0) {
                            vflag = 1;
                            execute_flag = 0;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-showm") == 0) {
                            memory_flag += 1;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-show_defaults") == 0) {
                            execute_flag = 0;
                            exit(0);
                        } else {
                            temp_t1_7 = compiler == 1;
                            if (temp_t1_7 != 0) {
                                if ((temp_t1_7 != 0) && (c_compiler_choice != 0) && (strncmp(*(arg1 + (var_s0 * 4)), "-smart", 6U) == 0)) {
                                    if (((*(arg1 + (var_s0 * 4)))->unk_6 == 0x2C) && ((*(arg1 + (var_s0 * 4)))->unk_7 != 0)) {
                                        sbrepos = *(arg1 + (var_s0 * 4)) + 7;
                                    } else {
                                        sbrepos = NULL;
                                    }
                                    add_static_opt(*(arg1 + (var_s0 * 4)));
                                    smart_build = 1;
                                } else if (strcmp(*(arg1 + (var_s0 * 4)), "-shared") == 0) {
                                    call_shared = 0;
                                    make_edison_shlib += 1;
                                } else if (strcmp(*(arg1 + (var_s0 * 4)), "-std0") == 0) {
                                    stdflag = 0;
                                    addstr(&ccomflags, *(arg1 + (var_s0 * 4)));
                                } else if ((strcmp(*(arg1 + (var_s0 * 4)), "-std") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-std1") == 0)) {
                                    stdflag = 1;
                                    addstr(&ccomflags, *(arg1 + (var_s0 * 4)));
                                } else if (strcmp(*(arg1 + (var_s0 * 4)), "-signed") == 0) {
                                    addstr(&pcaflags, "-signed");
                                    addstr(&soptflags, "-signed");
                                    addstr(&ccomflags, "-Xsigned");
                                    if ((compiler == 1) && (c_compiler_choice != 0)) {
                                        signedcharflag = 1;
                                    }
                                } else {
                                    goto block_1259;
                                }
                            } else {
block_1259:
                                if ((compiler == 4) && ((strcmp(*(arg1 + (var_s0 * 4)), "-std") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-std0") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-std1") == 0))) {
                                    stdflag = 1;
                                    addstr(&ccomflags, *(arg1 + (var_s0 * 4)));
                                } else if (compiler == 3) {
                                    if (strcmp(*(arg1 + (var_s0 * 4)), "-std") == 0) {
                                        addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                                    } else if (strcmp(*(arg1 + (var_s0 * 4)), "-static") == 0) {
                                        automaticflag = 0;
                                    } else if (strncmp(*(arg1 + (var_s0 * 4)), "-share_", 7U) == 0) {
                                        if (strcmp(*(arg1 + (var_s0 * 4)) + 7, "io") == 0) {
                                            D_1000C130 = 1;
                                        } else if (strcmp(*(arg1 + (var_s0 * 4)) + 7, "all") == 0) {
                                            D_1000C130 = 2;
                                        } else {
                                            goto block_1274;
                                        }
                                    } else {
                                        goto block_1274;
                                    }
                                } else {
block_1274:
                                    if ((compiler == 2) && (strcmp(*(arg1 + (var_s0 * 4)), "-std") == 0)) {
                                        stdflag = 1;
                                        addstr(&upasflags, *(arg1 + (var_s0 * 4)));
                                    } else if ((compiler == 6) && ((strcmp(*(arg1 + (var_s0 * 4)), "-supp_cob85") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-supp_cod") == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-supp_rm") == 0))) {
                                        addstr(&ucobflags, *(arg1 + (var_s0 * 4)));
                                    } else if ((compiler == 4) && (strcmp(*(arg1 + (var_s0 * 4)), "-signed") == 0)) {

                                    } else {
                                        goto block_1537;
                                    }
                                }
                            }
                        }
                        break;
                    case 0x74:                      /* switch 1 */
                        if (strcmp(*(arg1 + (var_s0 * 4)), "-transitive_link") == 0) {
                            full_transitive_link = 0;
                            transitive_link = 1;
                            no_transitive_link = 0;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-trapuv") == 0) {
                            trapuv_flag = 1;
                            addstr(&upasflags, *(arg1 + (var_s0 * 4)));
                            addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                            addstr(&upl1flags, *(arg1 + (var_s0 * 4)));
                            addstr(&ucobflags, *(arg1 + (var_s0 * 4)));
                            addstr(&ulpiflags, *(arg1 + (var_s0 * 4)));
                            addstr(&eflflags, *(arg1 + (var_s0 * 4)));
                            addstr(&ratforflags, *(arg1 + (var_s0 * 4)));
                            addstr(&genflags, *(arg1 + (var_s0 * 4)));
                            addstr(&asflags, *(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-tfp") == 0) {
                            tfp_flag = 1;
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-traditional") == 0) {
                            acpp_traditional += 1;
                        } else {
                            temp_t5_7 = *(arg1 + (var_s0 * 4)) + 2;
                            tstring = temp_t5_7;
                            strcat(alltstring, temp_t5_7);
                        }
                        break;
                    case 0x5A:                      /* switch 1 */
                        temp_t7_9 = (*(arg1 + (var_s0 * 4)))->unk_2;
                        switch (temp_t7_9) {        /* switch 4 */
                            case 0x41:              /* switch 4 */
                                error(2, NULL, 0, NULL, 0, "%s not supported\n", *(arg1 + (var_s0 * 4)));
                                break;
                            case 0x43:              /* switch 4 */
                                error(2, NULL, 0, NULL, 0, "%s not supported\n", *(arg1 + (var_s0 * 4)));
                                break;
                            case 0x46:              /* switch 4 */
                                error(2, NULL, 0, NULL, 0, "%s not supported\n", *(arg1 + (var_s0 * 4)));
                                break;
                            case 0x4E:              /* switch 4 */
                                error(2, NULL, 0, NULL, 0, "%s not supported\n", *(arg1 + (var_s0 * 4)));
                                break;
                            case 0x50:              /* switch 4 */
                                error(2, NULL, 0, NULL, 0, "%s not supported\n", *(arg1 + (var_s0 * 4)));
                                break;
                            case 0x55:              /* switch 4 */
                                error(2, NULL, 0, NULL, 0, "%s not supported\n", *(arg1 + (var_s0 * 4)));
                                break;
                            case 0x66:              /* switch 4 */
                                error(2, NULL, 0, NULL, 0, "%s not supported\n", *(arg1 + (var_s0 * 4)));
                                break;
                            case 0x69:              /* switch 4 */
                                error(2, NULL, 0, NULL, 0, "%s not supported\n", *(arg1 + (var_s0 * 4)));
                                break;
                            case 0x52:              /* switch 4 */
                                error(2, NULL, 0, NULL, 0, "%s not supported\n", *(arg1 + (var_s0 * 4)));
                                break;
                            case 0x47:              /* switch 4 */
                                addstr(&ldZflags, "-ZG");
                                break;
                            case 0x71:              /* switch 4 */
                                vflag = 1;
                                break;
                            case 0x67:              /* switch 4 */
                                error(2, NULL, 0, NULL, 0, "-Zg is obsolete and is ignored.\n");
                                if (compiler == 1) {
                                    error(2, NULL, 0, NULL, 0, "perhaps replace -Zg with -lgl_s. See your graphics documentation.\n");
                                }
                                if ((hasfortran != 0) || (compiler == 3)) {
                                    error(2, NULL, 0, NULL, 0, "perhaps replace -Zg with -lfgl -lgl_s  See f77(1).\n");
                                }
                                if ((haspascal != 0) || (compiler == 2)) {
                                    error(2, NULL, 0, NULL, 0, "perhaps replace -Zg with -lpgl /usr/lib/p2cstr.o -lgl_s  See pc(1).\n");
                                }
                                break;
                            case 0x72:              /* switch 4 */
                                error(2, NULL, 0, NULL, 0, "-Zr is obsolete and is ignored.\n");
                                break;
                            case 0x76:              /* switch 4 */
                                stdflag = 1;
                                addstr(&ccomflags, "-std");
                                addstr(&upasflags, "-std");
                                addstr(&fcomflags, "-std");
                                addstr(&upl1flags, "-std");
                                addstr(&ucobflags, "-std");
                                break;
                            case 0x7A:              /* switch 4 */
                                error(2, NULL, 0, NULL, 0, "%s not supported\n", *(arg1 + (var_s0 * 4)));
                                break;
                            default:                /* switch 4 */
                                error(1, NULL, 0, NULL, 0, "Unknown character in %s\n", *(arg1 + (var_s0 * 4)));
                                exit(2);
                                break;
                        }
                        break;
                    case 0x2D:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            if (xpg_flag != 0) {
                                NoMoreOptions += 1;
                            }
                        } else {
                            temp_s4_3 = (*(arg1 + (var_s0 * 4)))->unk_2;
                            switch (temp_s4_3) {    /* switch 8; irregular */
                                case 0x6E:          /* switch 8 */
                                    error(2, NULL, 0, NULL, 0, "%s is default\n", *(arg1 + (var_s0 * 4)));
                                    break;
                                case 0x78:          /* switch 8 */
                                    error(2, NULL, 0, NULL, 0, "%s is default\n", *(arg1 + (var_s0 * 4)));
                                    break;
                                default:            /* switch 8 */
                                    error(1, NULL, 0, NULL, 0, "Unknown character in %s\n", *(arg1 + (var_s0 * 4)));
                                    exit(2);
                                    break;
                            }
                        }
                        break;
                    case 0x75:                      /* switch 1 */
                        if (strcmp(*(arg1 + (var_s0 * 4)), "-uopt0") != 0) {
                            if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                                if (compiler == 3) {
                                    mp_uflag = 1;
                                    addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                                    add_static_opt(*(arg1 + (var_s0 * 4)));
                                } else {
                                    var_s0 += 1;
                                    if (var_s0 < arg0) {
                                        addstr(&objfiles, "-u");
                                        addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                                    } else {
                                        error(1, NULL, 0, NULL, 0, "ld requires -u to have an argument\n");
                                        exit(2);
                                        goto block_1335;
                                    }
                                }
                            } else {
block_1335:
                                if (strcmp(*(arg1 + (var_s0 * 4)), "-unroll") == 0) {
                                    error(1, NULL, 0, NULL, 0, "This flag is no longer supported\n");
                                    exit(2);
                                    goto block_1340;
                                }
                                if ((compiler == 3) && (strcmp(*(arg1 + (var_s0 * 4)), "-usefpidx") == 0)) {
                                    addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                                } else {
block_1340:
                                    if (strcmp(*(arg1 + (var_s0 * 4)), "-use_readwrite_const") == 0) {
                                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                                            addstr(&edisonflags, "-Yr0");
                                        } else {
                                            addstr(&accomflags, "-use_readwrite_const");
                                        }
                                    } else if (strcmp(*(arg1 + (var_s0 * 4)), "-use_readonly_const") == 0) {
                                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                                            addstr(&edisonflags, "-Yr1");
                                        } else {
                                            addstr(&accomflags, "-use_readonly_const");
                                        }
                                    } else if ((compiler == 1) && (strcmp(*(arg1 + (var_s0 * 4)), "-update_registry") == 0)) {
                                        var_s0 += 1;
                                        if (var_s0 >= arg0) {
                                            error(1, NULL, 0, NULL, 0, "-update_registry requires a filename argument\n");
                                            exit(2);
                                        }
                                        addstr(&ldflags, (arg1 + (var_s0 * 4))->unk_-4);
                                        addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                                    } else {
                                        goto block_1537;
                                    }
                                }
                            }
                        }
                        break;
                    case 0x76:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            if (default_svr4 == 0) {
                                vflag = 1;
                                time_flag = 1;
                            }
                        } else if (compiler == 1) {
                            if (strcmp(*(arg1 + (var_s0 * 4)), "-volatile") == 0) {
                                error(2, NULL, 0, NULL, 0, "-volatile is no longer supported; use the volatile qualifier instead\n");
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-varargs") == 0) {
                                addstr(&ccomflags, "-Xvarargs");
                            } else if (strcmp(*(arg1 + (var_s0 * 4)), "-verbose") == 0) {
                                addstr(&ccomflags, "-verbose");
                            } else {
                                goto block_1365;
                            }
                        } else {
block_1365:
                            if ((compiler == 3) && ((strncmp(*(arg1 + (var_s0 * 4)), "-vms", 4U) == 0) || (strcmp(*(arg1 + (var_s0 * 4)), "-varargs") == 0))) {
                                addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                                add_static_opt(*(arg1 + (var_s0 * 4)));
                            } else if ((compiler == 1) && ((temp_t9_8 = c_compiler_choice, (temp_t9_8 == 2)) || (temp_t9_8 == 3)) && (strcmp(*(arg1 + (var_s0 * 4)), "-v2") == 0)) {
                                if ((compiler == 1) && (c_compiler_choice != 0)) {
                                    error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", *(arg1 + (var_s0 * 4)), "");
                                }
                            } else {
                                goto block_1537;
                            }
                        }
                        break;
                    case 0x77:                      /* switch 1 */
                        if ((compiler == 1) && (strncmp(*(arg1 + (var_s0 * 4)), "-wlint", 6U) == 0)) {
                            if ((compiler == 1) && (c_compiler_choice != 0)) {
                                error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", *(arg1 + (var_s0 * 4)), "");
                            } else {
                                addstr(&ccomflags, *(arg1 + (var_s0 * 4)));
                            }
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-woff") == 0) {
                            var_s0 += 1;
                            if (var_s0 < arg0) {
                                if (strcmp(*(arg1 + (var_s0 * 4)), "options") == 0) {
                                    sp14C = 0;
                                } else if (((s32) **(arg1 + (var_s0 * 4)) < 0x30) || ((s32) **(arg1 + (var_s0 * 4)) >= 0x3A)) {
                                    error(2, NULL, 0, NULL, 0, "-woff requires a comma-separated list of error numbers - ignored\n");
                                    var_s0 -= 1;
                                } else {
                                    addstr(&accomflags, mkstr("-Xwoff", *(arg1 + (var_s0 * 4)), NULL));
                                    addstr(&edisonflags, mkstr("-YW", *(arg1 + (var_s0 * 4)), NULL));
                                }
                            } else {
                                error(1, NULL, 0, NULL, 0, "-woff requires a warning number (or a list of them)\n");
                                exit(2);
                                goto block_1391;
                            }
                        } else {
block_1391:
                            if (((*(arg1 + (var_s0 * 4)))->unk_2 == 0x31) && ((*(arg1 + (var_s0 * 4)))->unk_3 == 0)) {
                                if (compiler != 3) {
                                    error(2, NULL, 0, NULL, 0, "Unknown flag: %s\n", *(arg1 + (var_s0 * 4)));
                                } else {
                                    w1flag = 1;
                                }
                            } else if (((*(arg1 + (var_s0 * 4)))->unk_2 == 0x30) && ((*(arg1 + (var_s0 * 4)))->unk_3 == 0)) {
                                if (compiler != 3) {
                                    error(2, NULL, 0, NULL, 0, "Unknown flag: %s\n", *(arg1 + (var_s0 * 4)));
                                } else {
                                    w1flag = 0;
                                }
                            } else if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0x36) {
                                if ((compiler == 3) && ((*(arg1 + (var_s0 * 4)))->unk_2 == 0x36)) {
                                    mp_66flag = 1;
                                }
                                addstr(&fcomflags, *(arg1 + (var_s0 * 4)));
                            } else if (((*(arg1 + (var_s0 * 4)))->unk_2 != 0) && (compiler == 1) && (c_compiler_choice != 0)) {
                                error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", *(arg1 + (var_s0 * 4)), "");
                            } else if (((*(arg1 + (var_s0 * 4)))->unk_2 == 0) || (((*(arg1 + (var_s0 * 4)))->unk_3 == 0) && (((*(arg1 + (var_s0 * 4)))->unk_2 == 0x31) || ((*(arg1 + (var_s0 * 4)))->unk_2 == 0x32) || ((*(arg1 + (var_s0 * 4)))->unk_2 == 0x33)))) {
                                addstr(&cppflags, *(arg1 + (var_s0 * 4)));
                                addstr(&ccomflags, *(arg1 + (var_s0 * 4)));
                                addstr(&edisonflags, *(arg1 + (var_s0 * 4)));
                                w1flag = 2;
                                addstr(&upasflags, *(arg1 + (var_s0 * 4)));
                                addstr(&upl1flags, *(arg1 + (var_s0 * 4)));
                                addstr(&ucobflags, *(arg1 + (var_s0 * 4)));
                                addstr(&ulpiflags, *(arg1 + (var_s0 * 4)));
                                addstr(&uldflags, *(arg1 + (var_s0 * 4)));
                                addstr(&uopt0flags, *(arg1 + (var_s0 * 4)));
                                addstr(&ddoptflags, *(arg1 + (var_s0 * 4)));
                                addstr(&uloopflags, *(arg1 + (var_s0 * 4)));
                                addstr(&optflags, *(arg1 + (var_s0 * 4)));
                                addstr(&genflags, *(arg1 + (var_s0 * 4)));
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                                addstr(&asflags, *(arg1 + (var_s0 * 4)));
                                addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                                addstr(&ftocflags, *(arg1 + (var_s0 * 4)));
                            } else {
                                goto block_1537;
                            }
                        }
                        break;
                    case 0x79:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 != 0) {
                            addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x78:                      /* switch 1 */
                        if (strcmp(*(arg1 + (var_s0 * 4)), "-xansi") == 0) {
                            if (compchoice == 1) {
                                compchoice = 0;
                            }
                            ansichoice = 3;
                            cppchoice = 3;
                            relocate_passes("p", NULL, NULL);
                            add_static_opt(*(arg1 + (var_s0 * 4)));
                        } else if (strcmp(*(arg1 + (var_s0 * 4)), "-xgot") == 0) {
                            addstr(&asflags, "-big_got");
                        } else if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                        } else {
                            goto block_1537;
                        }
                        break;
                    case 0x7A:                      /* switch 1 */
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            addstr(&ldflags, *(arg1 + (var_s0 * 4)));
                        } else {
                            goto block_1537;
                        }
                        break;
                }
            } else if ((**(arg1 + (var_s0 * 4)) == 0x2B) && (compiler == 1) && ((temp_t7_10 = c_compiler_choice, (temp_t7_10 == 2)) || (temp_t7_10 == 3))) {
                temp_t4_14 = (*(arg1 + (var_s0 * 4)))->unk_1;
                switch (temp_t4_14) {               /* switch 5 */
                    case 0x70:                      /* switch 5 */
                        var_at_2 = &anachronisms;
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0) {
                            goto block_1441;
                        }
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0x70) {
                            anachronisms = 0;
                            var_at_2 = &cfront_compatible;
                            goto block_1441;
                        }
                        var_at_2 = &anachronisms;
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0x61) {
                            goto block_1441;
                        }
                        var_at_2 = &cfront_compatible;
                        if ((*(arg1 + (var_s0 * 4)))->unk_2 == 0x63) {
block_1441:
                            *var_at_2 = 0;
                        }
                        add_static_opt(*(arg1 + (var_s0 * 4)));
                        break;
                    case 0x77:                      /* switch 5 */
                        fullwarn = 1;
                        break;
                    case 0x76:                      /* switch 5 */
                        vflag = 1;
                        break;
                    case 0x64:                      /* switch 5 */
                        disable_inlines = 1;
                        break;
                    case 0x65:                      /* switch 5 */
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", *(arg1 + (var_s0 * 4)), "");
                        } else {
                        case 0x49:                  /* switch 5 */
                            cflag = 1;
                            plusIflag = 1;
                            Fflag = 1;
                            default_template_instantiation_mode = 1;
                        }
                        break;
                    default:                        /* switch 5 */
                    default:                        /* switch 1 */
block_1537:
                        if (sp14C != 0) {
                            error(1, NULL, 0, NULL, 0, "malformed or unknown option: %s\n", *(arg1 + (var_s0 * 4)));
                            exit(2);
                        } else {
                            error(2, NULL, 0, NULL, 0, "malformed or unknown option: %s\n", *(arg1 + (var_s0 * 4)));
                        }
                        break;
                }
            } else {
                var_s1 = getsuf(*(arg1 + (var_s0 * 4))) & 0xFF;
                if (var_s1 == 0x6D) {
                    var_s1 = 0x66;
                }
                if (var_s1 == 0x70) {
                    haspascal = 1;
                }
                if (var_s1 == 0x66) {
                    hasfortran = 1;
                }
                if (var_s1 == 1) {
                    haspl1 = 1;
                }
                if ((var_s1 == 0x63) || (var_s1 == 0x70) || (var_s1 == 0x66) || (var_s1 == 0x46) || (var_s1 == 0x72) || (var_s1 == 0x65) || (var_s1 == 0x42) || (var_s1 == 0x55) || (var_s1 == 0x73) || (var_s1 == 0x4F) || (var_s1 == 0x47) || (var_s1 == 0x53) || (var_s1 == 0x4D) || (var_s1 == 0x56) || (var_s1 == 0x69) || (var_s1 == 1) || (var_s1 == 0x44) || (var_s1 == 3) || (var_s1 == 2) || (var_s1 == 0x75) || (var_s1 == 6) || ((compiler == 1) && (nocode != 0) && (D_1000BF74 != 0) && (var_s1 == 0x68)) || (Eflag != 0) || (compiler == 4)) {
                    srcexists += 1;
                    if ((**(arg1 + (var_s0 * 4)) == 0x2D) && (NoMoreOptions == 0)) {
                        sp60 = 1;
                        if ((*(arg1 + (var_s0 * 4)))->unk_1 == 0x2D) {
                            do {
                                sp60 += 1;
                            } while (*(*(arg1 + (var_s0 * 4)) + sp60) == 0x2D);
                        }
                        *(arg1 + (var_s0 * 4)) = *(arg1 + (var_s0 * 4)) + sp60;
                    }
                    sp5C = 1;
                    if (arg0 >= 2) {
                        do {
                            temp_t3_6 = *(arg1 + (sp5C * 4));
                            if ((temp_t3_6->unk_1 == 0x6A) && (strcmp(temp_t3_6, "-j") == 0)) {
                                jflag += 1;
                            }
                            temp_t5_8 = sp5C + 1;
                            sp5C = temp_t5_8;
                        } while (temp_t5_8 < arg0);
                    }
                    temp_t7_11 = Oflag;
                    if (((temp_t7_11 == 3) || (temp_t7_11 == 4)) && (jflag == 0) && ((var_s1 == 0x63) || (var_s1 == 0x70) || (var_s1 == 0x66) || (var_s1 == 0x46) || (var_s1 == 0x72) || (var_s1 == 0x65) || (var_s1 == 0x42) || (var_s1 == 0x55) || (var_s1 == 0x69) || (var_s1 == 1) || (var_s1 == 3) || (var_s1 == 2) || (var_s1 == 6) || (var_s1 == 0x75) || (var_s1 == 0x44))) {
                        if (var_s1 != 0x75) {
                            addstr(&srcfiles, *(arg1 + (var_s0 * 4)));
                            var_s2_10 = mksuf(*(arg1 + (var_s0 * 4)), 0x75U);
                        } else {
                            var_s2_10 = *(arg1 + (var_s0 * 4));
                        }
                        uload = 1;
                        if (uldobj_place == -1) {
                            uldobj_place = save_place(&objfiles);
                        }
                        if (nodup(&ufiles, var_s2_10) != 0) {
                            addstr(&ufiles, var_s2_10);
                        }
                        temp_v0 = mksuf(*(arg1 + (var_s0 * 4)), 0x6FU);
                        if (nodup(&objfiles, temp_v0) != 0) {
                            sp158 = temp_v0;
                        }
                    } else if ((Eflag == 0) && (compiler != 4)) {
                        addstr(&srcfiles, *(arg1 + (var_s0 * 4)));
                        temp_v0_2 = mksuf(*(arg1 + (var_s0 * 4)), 0x6FU);
                        if (nodup(&objfiles, temp_v0_2) != 0) {
                            addstr(&objfiles, temp_v0_2);
                            sp158 = temp_v0_2;
                            nobjs += 1;
                        }
                    } else {
                        addstr(&srcfiles, *(arg1 + (var_s0 * 4)));
                    }
                } else if (var_s1 == 0x62) {
                    temp_t9_9 = Oflag;
                    if (((temp_t9_9 == 3) || (temp_t9_9 == 4)) && (jflag == 0)) {
                        if (uldobj_place == -1) {
                            uldobj_place = save_place(&objfiles);
                        }
                        addstr(&ufiles, *(arg1 + (var_s0 * 4)));
                        uload = 1;
                    }
                } else {
                    addstr(&objfiles, *(arg1 + (var_s0 * 4)));
                    if (var_s1 == 0x6F) {
                        nobjs += 1;
                    }
                }
                func_00431B38(var_s0 + 1, 1);
            }
            var_s0 += 1;
        } while (var_s0 < arg0);
    }
    if (sp15C != NULL) {
        if (srcfiles.length == 1) {
            sp58 = strdup(*srcfiles.entries);
            if (sp58 == NULL) {
                sp58 = sp158;
            } else {
                sp54 = strlen(sp58);
                if (((s32) sp54 >= 3) && (sp58[sp54].unk_-2 == 0x2E)) {
                    if (Eflag != 0) {
                        sp58[sp54].unk_-1 = 0x69;
                    } else if (Sflag != 0) {
                        sp58[sp54].unk_-1 = 0x73;
                    } else if (jflag != 0) {
                        sp58[sp54].unk_-1 = 0x75;
                    } else {
                        sp58[sp54].unk_-2 = 0;
                    }
                }
            }
        }
        if (((compiler == 1) && (c_compiler_choice != 0)) || ((compiler == 3) && (D_1000BF74 != 0))) {
            if ((srcfiles.length == 1) && ((outfile != NULL) || (cflag == 0))) {
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
            if ((srcfiles.length == 1) && ((outfile != NULL) || (cflag == 0))) {
                addstr(&cppflags, "-MDtarget");
                temp_t0_3 = outfile;
                if (temp_t0_3 != NULL) {
                    addstr(&cppflags, temp_t0_3);
                } else {
                    addstr(&cppflags, sp58);
                }
                addstr(&ldflags, "-MDignore");
                addstr(&ldflags, sp158);
            }
            addstr(&cppflags, "-MDupdate");
            addstr(&cppflags, sp15C);
            if (Oflag == 3) {
                addstr(&uldflags, "-MDtarget");
                temp_t5_9 = outfile;
                if (temp_t5_9 != NULL) {
                    addstr(&uldflags, temp_t5_9);
                } else if (cflag != 0) {
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
    if (mips2flag != 0) {
        addstr(&ccomflags, "-mips2");
        addstr(&upasflags, "-mips2");
        addstr(&fcomflags, "-mips2");
        addstr(&upl1flags, "-mips2");
        addstr(&ucobflags, "-mips2");
        addstr(&ulpiflags, "-mips2");
        addstr(&eflflags, "-mips2");
        addstr(&ratforflags, "-mips2");
        addstr(&ujoinflags, "-mips2");
        addstr(&usplitflags, "-mips2");
        addstr(&umergeflags, "-mips2");
        addstr(&uloopflags, "-mips2");
        addstr(&optflags, "-mips2");
        addstr(&genflags, "-mips2");
        addstr(&asflags, "-mips2");
        addstr(&ldflags, "-mips2");
        addstr(&ftocflags, "-mips2");
    }
}

void get_host_chiptype(void) {

}

void error(s32 arg0, s8* arg1, s32 arg2, s8* arg3, s32 arg4, s8* arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, ...) {
    u32 sp34;
    s32 sp30;
    s32 temp_t3;
    s32 temp_t3_2;

    if ((Vflag == 0) && (D_1000C1D8 == NULL)) {
        D_1000C1D8 = strrchr(progname, 0x2F);
        if (D_1000C1D8 == NULL) {
            D_1000C1D8 = progname;
        } else {
            D_1000C1D8 += 1;
        }
        sp34 = strlen(D_1000C1D8);
        D_1000C1DC = malloc(sp34 + 2);
        if (D_1000C1DC == NULL) {
            fprintf(__iob + 0x20, "%s: Error: error (), %d: Out of memory\n", D_1000C1D8, 0x3414);
            temp_t3 = errno;
            if (temp_t3 < sys_nerr) {
                fprintf(__iob + 0x20, "%s: %s\n", D_1000C1D8, sys_errlist[temp_t3]);
            }
            exit(1);
        }
        sp30 = 0;
        if ((s32) sp34 > 0) {
            do {
                D_1000C1DC[sp30] = 0x20;
                temp_t3_2 = sp30 + 1;
                sp30 = temp_t3_2;
            } while (temp_t3_2 < (s32) sp34);
        }
        D_1000C1DC[sp30] = 0;
    }
    if (arg0 == 5) {
        fprintf(__iob + 0x20, "%s: ", D_1000C1DC);
    } else {
        fprintf(__iob + 0x20, "%s: %s: ", D_1000C1D8, D_1000C1E0[arg0]);
    }
    if (arg1 != NULL) {
        if (arg2 != 0) {
            fprintf(__iob + 0x20, "%s, line %d: ", arg1, arg2);
        } else {
            fprintf(__iob + 0x20, "%s: ", arg1);
        }
    }
    if (arg3 != NULL) {
        if (arg4 != 0) {
            fprintf(__iob + 0x20, "%s, line %d: ", arg3, arg4);
        } else {
            fprintf(__iob + 0x20, "%s: ", arg3);
        }
    }
    if (arg5 == NULL) {
        arg5 = "";
    }
    fprintf(__iob + 0x20, arg5, arg6, arg7, arg8, arg9, argA, argB);
}

void relocate_passes(s8* arg0, s8* arg1, s8* arg2) {
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_t0_2;
    s32 temp_t6_5;
    s32 temp_t6_6;
    s32 temp_t8;
    s32 temp_t9;
    s32 temp_t9_3;
    s8* temp_t0;
    s8* temp_t1;
    s8* temp_t1_2;
    s8* temp_t2;
    s8* temp_t2_2;
    s8* temp_t2_3;
    s8* temp_t3;
    s8* temp_t3_2;
    s8* temp_t3_3;
    s8* temp_t3_4;
    s8* temp_t3_5;
    s8* temp_t4_2;
    s8* temp_t4_3;
    s8* temp_t4_4;
    s8* temp_t4_5;
    s8* temp_t5;
    s8* temp_t5_2;
    s8* temp_t5_3;
    s8* temp_t6;
    s8* temp_t6_2;
    s8* temp_t6_3;
    s8* temp_t6_4;
    s8* temp_t6_7;
    s8* temp_t7_2;
    s8* temp_t7_3;
    s8* temp_t7_4;
    s8* temp_t7_5;
    s8* temp_t7_6;
    s8* temp_t8_2;
    s8* temp_t8_3;
    s8* temp_t8_4;
    s8* temp_t9_2;
    s8* var_s1;
    s8* var_s2;
    s8* var_s2_10;
    s8* var_s2_11;
    s8* var_s2_12;
    s8* var_s2_2;
    s8* var_s2_3;
    s8* var_s2_4;
    s8* var_s2_5;
    s8* var_s2_6;
    s8* var_s2_7;
    s8* var_s2_8;
    s8* var_s2_9;
    s8* var_s3;
    s8* var_s3_2;
    s8* var_s3_3;
    s8* var_s3_4;
    s8* var_s3_5;
    s8* var_s3_6;
    s8* var_v0;
    s8* var_v0_10;
    s8* var_v0_11;
    s8* var_v0_12;
    s8* var_v0_2;
    s8* var_v0_3;
    s8* var_v0_4;
    s8* var_v0_5;
    s8* var_v0_6;
    s8* var_v0_7;
    s8* var_v0_8;
    s8* var_v0_9;
    u8 temp_t4;
    u8 temp_t7;

    currcomp = "";
    if (arg2 == NULL) {
        arg2 = Bstring;
    }
    if (arg0 == NULL) {
        var_s1 = "hpfekjusmvodqcablyzrP1EXCOnMFISUtKYwx";
        allBstring = arg2;
    } else {
        var_s1 = arg0;
    }
    if ((strcmp(Gnum, "0") == 0) && (compose_first_G0 != 0)) {
        compose_first_G0 = 0;
        compose_G0_libs("PE1COMFIUSXnW");
    }
    if ((u8) *var_s1 != 0) {
        do {
            if ((arg1 != NULL) || (strchr(alltstring, (u8) var_s1->unk_0) == NULL)) {
                temp_t4 = (u8) var_s1->unk_0;
                switch (temp_t4) {
                    case 0x68:
                        temp_t6 = includeB;
                        if (temp_t6 != NULL) {
                            free(temp_t6);
                        }
                        temp_t7_2 = eincludeB;
                        if (temp_t7_2 != NULL) {
                            free(temp_t7_2);
                        }
                        if ((arg0 != NULL) || ((arg2 != NULL) && ((u8) *arg2 != 0))) {
                            if (arg1 != NULL) {
                                if (fiveflag != 0) {
                                    includeB = mkstr(arg1, "usr/5include", arg2, NULL);
                                } else if (abi_flag != 0) {
                                    includeB = mkstr(arg1, "usr/include/abi", arg2, NULL);
                                } else {
                                    eincludeB = mkstr(arg1, "usr/include/CC", arg2, NULL);
                                    includeB = mkstr(arg1, "usr/include", arg2, NULL);
                                }
                            } else if (fiveflag != 0) {
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
                    case 0x70:
                        temp_t6_2 = cpp;
                        if (temp_t6_2 != NULL) {
                            free(temp_t6_2);
                        }
                        if (arg1 != NULL) {
                            temp_t8 = cppchoice;
                            if ((temp_t8 != 1) && (temp_t8 != 3)) {
                                var_s2 = "cpp";
                            } else {
                                var_s2 = "acpp";
                            }
                            cpp = mkstr(arg1, var_s2, arg2, NULL);
                        } else {
                            temp_t9 = cppchoice;
                            if ((temp_t9 != 1) && (temp_t9 != 3)) {
                                var_s2_2 = "cpp";
                            } else {
                                var_s2_2 = "acpp";
                            }
                            cpp = mkstr(comp_host_root, "usr/lib/", currcomp, var_s2_2, arg2, NULL);
                        }
                        break;
                    case 0x66:
                        temp_t2 = mpc;
                        if (temp_t2 != NULL) {
                            free(temp_t2);
                        }
                        temp_t1 = ccom;
                        if (temp_t1 != NULL) {
                            free(temp_t1);
                        }
                        temp_t3 = cfe;
                        if (temp_t3 != NULL) {
                            free(temp_t3);
                        }
                        temp_t4_2 = upas;
                        if (temp_t4_2 != NULL) {
                            free(temp_t4_2);
                        }
                        temp_t5 = fcom;
                        if (temp_t5 != NULL) {
                            free(temp_t5);
                        }
                        temp_t6_3 = upl1;
                        if (temp_t6_3 != NULL) {
                            free(temp_t6_3);
                        }
                        temp_t7_3 = ucob;
                        if (temp_t7_3 != NULL) {
                            free(temp_t7_3);
                        }
                        if (arg1 != NULL) {
                            if (cmp_flag & 0x10000) {
                                mpc = mkstr(arg1, "mpc", arg2, NULL);
                            }
                            if (ansichoice != 0) {
                                var_s2_3 = "accom";
                            } else {
                                var_s2_3 = "ccom";
                            }
                            ccom = mkstr(arg1, var_s2_3, arg2, NULL);
                            if ((c_compiler_choice != 0) || ((compiler == 3) && (D_1000BF74 != 0))) {
                                if (exception_handling != 0) {
                                    var_s3 = "edgcpfe.eh";
                                } else {
                                    var_s3 = "edgcpfe";
                                }
                                var_s2_4 = var_s3;
                            } else {
                                var_s2_4 = "cfe";
                            }
                            cfe = mkstr(arg1, var_s2_4, arg2, NULL);
                            upas = mkstr(arg1, "upas", arg2, NULL);
                            fcom = mkstr(arg1, "fcom", arg2, NULL);
                            upl1 = mkstr(arg1, "pl1fe", arg2, NULL);
                            ucob = mkstr(arg1, "cobfe", arg2, NULL);
                        } else {
                            if (cmp_flag & 0x10000) {
                                mpc = mkstr(comp_host_root, "usr/lib/", currcomp, "mpc", arg2, NULL);
                            }
                            if (ansichoice != 0) {
                                var_s2_5 = "accom";
                            } else {
                                var_s2_5 = "ccom";
                            }
                            ccom = mkstr(comp_host_root, "usr/lib/", currcomp, var_s2_5, arg2, NULL);
                            if (((compiler == 1) && (c_compiler_choice != 0)) || ((compiler == 3) && (D_1000BF74 != 0))) {
                                if ((c_compiler_choice != 0) || ((compiler == 3) && (D_1000BF74 != 0))) {
                                    if (exception_handling != 0) {
                                        var_s3_2 = "edgcpfe.eh";
                                    } else {
                                        var_s3_2 = "edgcpfe";
                                    }
                                    var_s2_6 = var_s3_2;
                                } else {
                                    var_s2_6 = "cfe";
                                }
                                var_v0 = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, var_s2_6, arg2, NULL);
                            } else {
                                if ((c_compiler_choice != 0) || ((compiler == 3) && (D_1000BF74 != 0))) {
                                    if (exception_handling != 0) {
                                        var_s3_3 = "edgcpfe.eh";
                                    } else {
                                        var_s3_3 = "edgcpfe";
                                    }
                                    var_s2_7 = var_s3_3;
                                } else {
                                    var_s2_7 = "cfe";
                                }
                                var_v0 = mkstr(comp_host_root, "usr/lib/", currcomp, var_s2_7, arg2, NULL);
                            }
                            cfe = var_v0;
                            upas = mkstr(comp_host_root, "usr/lib/", currcomp, "upas", arg2, NULL);
                            fcom = mkstr(comp_host_root, "usr/lib/", currcomp, "fcom", arg2, NULL);
                            upl1 = mkstr(comp_host_root, "usr/lib/", currcomp, "pl1fe", arg2, NULL);
                            ucob = mkstr(comp_host_root, "usr/lib/", currcomp, "cobfe", arg2, NULL);
                        }
                        break;
                    case 0x65:
                        temp_t0 = pl1err;
                        if (temp_t0 != NULL) {
                            free(temp_t0);
                        }
                        if (arg1 != NULL) {
                            pl1err = mkstr(arg1, "pl1error", arg2, NULL);
                        } else {
                            pl1err = mkstr(comp_host_root, "usr/lib/", currcomp, "pl1error", arg2, NULL);
                        }
                        break;
                    case 0x6B:
                        temp_t1_2 = ulpi;
                        if (temp_t1_2 != NULL) {
                            free(temp_t1_2);
                        }
                        if (arg1 != NULL) {
                            ulpi = mkstr(arg1, "ulpi", arg2, NULL);
                        } else {
                            ulpi = mkstr(comp_host_root, "usr/lib/", currcomp, "ulpi", arg2, NULL);
                        }
                        break;
                    case 0x6A:
                        temp_t5_2 = ujoin;
                        if (temp_t5_2 != NULL) {
                            free(temp_t5_2);
                        }
                        if (arg1 != NULL) {
                            ujoin = mkstr(arg1, "ujoin", arg2, NULL);
                        } else {
                            ujoin = mkstr(comp_host_root, "usr/lib/", currcomp, "ujoin", arg2, NULL);
                        }
                        break;
                    case 0x75:
                        temp_t9_2 = uld;
                        if (temp_t9_2 != NULL) {
                            free(temp_t9_2);
                        }
                        if (arg1 != NULL) {
                            uld = mkstr(arg1, "uld", arg2, NULL);
                        } else {
                            uld = mkstr(comp_host_root, "usr/lib/", currcomp, "uld", arg2, NULL);
                        }
                        break;
                    case 0x73:
                        temp_t2_2 = usplit;
                        if (temp_t2_2 != NULL) {
                            free(temp_t2_2);
                        }
                        if (arg1 != NULL) {
                            usplit = mkstr(arg1, "usplit", arg2, NULL);
                        } else {
                            usplit = mkstr(comp_host_root, "usr/lib/", currcomp, "usplit", arg2, NULL);
                        }
                        break;
                    case 0x71:
                        temp_t4_3 = uopt0;
                        if (temp_t4_3 != NULL) {
                            free(temp_t4_3);
                        }
                        if (arg1 != NULL) {
                            uopt0 = mkstr(arg1, "uopt0", arg2, NULL);
                        } else {
                            uopt0 = mkstr(comp_host_root, "usr/lib/", currcomp, "uopt0", arg2, NULL);
                        }
                        break;
                    case 0x64:
                        temp_t7_4 = ddopt;
                        if (temp_t7_4 != NULL) {
                            free(temp_t7_4);
                        }
                        if (arg1 != NULL) {
                            ddopt = mkstr(arg1, "ddopt", arg2, NULL);
                        } else {
                            ddopt = mkstr(comp_host_root, "usr/lib/", currcomp, "ddopt", arg2, NULL);
                        }
                        break;
                    case 0x6D:
                        temp_t8_2 = umerge;
                        if (temp_t8_2 != NULL) {
                            free(temp_t8_2);
                        }
                        if (arg1 != NULL) {
                            umerge = mkstr(arg1, "umerge", arg2, NULL);
                        } else {
                            umerge = mkstr(comp_host_root, "usr/lib/", currcomp, "umerge", arg2, NULL);
                        }
                        break;
                    case 0x76:
                        temp_t3_2 = uloop;
                        if (temp_t3_2 != NULL) {
                            free(temp_t3_2);
                        }
                        if (arg1 != NULL) {
                            uloop = mkstr(arg1, "uloop", arg2, NULL);
                        } else {
                            uloop = mkstr(comp_host_root, "usr/lib/", currcomp, "uloop", arg2, NULL);
                        }
                        break;
                    case 0x6F:
                        temp_t6_4 = opt;
                        if (temp_t6_4 != NULL) {
                            free(temp_t6_4);
                        }
                        if (arg1 != NULL) {
                            opt = mkstr(arg1, "uopt", arg2, NULL);
                        } else if ((compiler == 1) && ((temp_t0_2 = c_compiler_choice, (temp_t0_2 == 2)) || (temp_t0_2 == 3)) && (D_1000BF8C != 0)) {
                            opt = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "uopt", arg2, NULL);
                        } else {
                            opt = mkstr(comp_host_root, "usr/lib/", currcomp, "uopt", arg2, NULL);
                        }
                        break;
                    case 0x63:
                        temp_t3_3 = gen;
                        if (temp_t3_3 != NULL) {
                            free(temp_t3_3);
                        }
                        if (arg1 != NULL) {
                            gen = mkstr(arg1, "ugen", arg2, NULL);
                        } else if ((compiler == 1) && ((temp_t6_5 = c_compiler_choice, (temp_t6_5 == 2)) || (temp_t6_5 == 3)) && (D_1000BF8C != 0)) {
                            gen = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "ugen", arg2, NULL);
                        } else {
                            gen = mkstr(comp_host_root, "usr/lib/", currcomp, "ugen", arg2, NULL);
                        }
                        break;
                    case 0x61:
                        temp_t8_3 = as0;
                        if (temp_t8_3 != NULL) {
                            free(temp_t8_3);
                        }
                        if (arg1 != NULL) {
                            as0 = mkstr(arg1, "as0", arg2, NULL);
                        } else {
                            as0 = mkstr(comp_host_root, "usr/lib/", currcomp, "as0", arg2, NULL);
                        }
                        break;
                    case 0x62:
                        temp_t3_4 = as1;
                        if (temp_t3_4 != NULL) {
                            free(temp_t3_4);
                        }
                        if (arg1 != NULL) {
                            as1 = mkstr(arg1, "as1", arg2, NULL);
                        } else if ((compiler == 1) && ((temp_t6_6 = c_compiler_choice, (temp_t6_6 == 2)) || (temp_t6_6 == 3)) && (D_1000BF8C != 0)) {
                            as1 = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "as1", arg2, NULL);
                        } else {
                            as1 = mkstr(comp_host_root, "usr/lib/", currcomp, "as1", arg2, NULL);
                        }
                        break;
                    case 0x77:
                        temp_t8_4 = prelinker;
                        if (temp_t8_4 != NULL) {
                            free(temp_t8_4);
                        }
                        if (arg1 != NULL) {
                            prelinker = mkstr(arg1, "edg_prelink", arg2, NULL);
                        } else {
                            prelinker = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "edg_prelink", arg2, NULL);
                        }
                        break;
                    case 0x6C:
                        temp_t3_5 = ld;
                        if (temp_t3_5 != NULL) {
                            free(temp_t3_5);
                        }
                        temp_t4_4 = patch;
                        if (temp_t4_4 != NULL) {
                            free(temp_t4_4);
                        }
                        temp_t5_3 = filter;
                        if (temp_t5_3 != NULL) {
                            free(temp_t5_3);
                        }
                        if (arg1 != NULL) {
                            ld = mkstr(arg1, LD, arg2, NULL);
                            patch = mkstr(arg1, "c++patch", arg2, NULL);
                            filter = mkstr(arg1, "c++filt", arg2, NULL);
                        } else {
                            if ((compiler == 1) && ((temp_t9_3 = c_compiler_choice, (temp_t9_3 == 2)) || (temp_t9_3 == 3)) && (D_1000BF90 != 0)) {
                                var_v0_2 = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, LD, arg2, NULL);
                            } else if (irix4 != 0) {
                                var_v0_2 = mkstr(comp_host_root, "usr/bin/", currcomp, LD, arg2, NULL);
                            } else {
                                var_v0_2 = mkstr(comp_host_root, "usr/lib/", currcomp, LD, arg2, NULL);
                            }
                            ld = var_v0_2;
                            patch = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "c++patch", arg2, NULL);
                            filter = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, "c++filt", arg2, NULL);
                        }
                        break;
                    case 0x74:
                        temp_t6_7 = btou;
                        if (temp_t6_7 != NULL) {
                            free(temp_t6_7);
                        }
                        temp_t7_5 = utob;
                        if (temp_t7_5 != NULL) {
                            free(temp_t7_5);
                        }
                        if (arg1 != NULL) {
                            btou = mkstr(arg1, "btou", arg2, NULL);
                            utob = mkstr(arg1, "utob", arg2, NULL);
                        } else {
                            btou = mkstr(comp_host_root, "usr/lib/", currcomp, "btou", arg2, NULL);
                            utob = mkstr(comp_host_root, "usr/lib/", currcomp, "utob", arg2, NULL);
                        }
                        break;
                    case 0x78:
                        temp_t2_3 = strip;
                        if (temp_t2_3 != NULL) {
                            free(temp_t2_3);
                        }
                        if (arg1 != NULL) {
                            strip = mkstr(arg1, "strip", arg2, NULL);
                        } else {
                            strip = mkstr(comp_host_root, "usr/bin/", currcomp, "strip", arg2, NULL);
                        }
                        break;
                    case 0x79:
                        temp_t4_5 = ftoc;
                        if (temp_t4_5 != NULL) {
                            free(temp_t4_5);
                        }
                        if (arg1 != NULL) {
                            ftoc = mkstr(arg1, "ftoc", arg2, NULL);
                        } else {
                            ftoc = mkstr(comp_host_root, "usr/lib/", currcomp, "ftoc", arg2, NULL);
                        }
                        break;
                    case 0x7A:
                        temp_t7_6 = cord;
                        if (temp_t7_6 != NULL) {
                            free(temp_t7_6);
                        }
                        if (arg1 != NULL) {
                            cord = mkstr(arg1, "cord", arg2, NULL);
                        } else {
                            cord = mkstr(comp_host_root, "usr/bin/", currcomp, "cord", arg2, NULL);
                        }
                        break;
                    case 0x72:
                        if (arg1 != NULL) {
                            if (pflag != 0) {
                                crtx = mkstr(arg1, MCRTX, arg2, NULL);
                                if (exception_handling != 0) {
                                    var_s2_8 = "c++init_eh.o";
                                } else {
                                    var_s2_8 = "c++init.o";
                                }
                                cxx_init = mkstr(arg1, var_s2_8, arg2, NULL);
                                delta_init = mkstr(arg1, "delta_init.o", arg2, NULL);
                                crtn = mkstr(arg1, "crtn.o", arg2, NULL);
                            } else {
                                crtx = mkstr(arg1, CRTX, arg2, NULL);
                                if (exception_handling != 0) {
                                    var_s2_9 = "c++init_eh.o";
                                } else {
                                    var_s2_9 = "c++init.o";
                                }
                                cxx_init = mkstr(arg1, var_s2_9, arg2, NULL);
                                delta_init = mkstr(arg1, "delta_init.o", arg2, NULL);
                                crtn = mkstr(arg1, "crtn.o", arg2, NULL);
                            }
                        } else if (pflag != 0) {
                            if (abi_flag != 0) {
                                crtx = func_0042FD7C(mkstr(MCRTX, arg2, NULL), dirs_for_abi_crtn.entries);
                                crtn = func_0042FD7C(mkstr("crtn.o", arg2, NULL), dirs_for_abi_crtn.entries);
                                if (exception_handling != 0) {
                                    var_s3_4 = "c++init_eh.o";
                                } else {
                                    var_s3_4 = "c++init.o";
                                }
                                cxx_init = func_0042FD7C(mkstr(var_s3_4, arg2, NULL), dirs_for_abi_crtn.entries);
                                delta_init = func_0042FD7C(mkstr("delta_init.o", arg2, NULL), dirs_for_abi_crtn.entries);
                            } else if (non_shared != 0) {
                                crtx = func_0042FD7C(mkstr(MCRTX, arg2, NULL), dirs_for_nonshared_crtn.entries);
                                crtn = func_0042FD7C(mkstr("crtn.o", arg2, NULL), dirs_for_nonshared_crtn.entries);
                                if (exception_handling != 0) {
                                    var_s3_5 = "c++init_eh.o";
                                } else {
                                    var_s3_5 = "c++init.o";
                                }
                                cxx_init = func_0042FD7C(mkstr(var_s3_5, arg2, NULL), dirs_for_nonshared_crtn.entries);
                                delta_init = func_0042FD7C(mkstr("delta_init.o", arg2, NULL), dirs_for_nonshared_crtn.entries);
                            } else {
                                crtx = func_0042FD7C(mkstr(MCRTX, arg2, NULL), dirs_for_crtn.entries);
                                crtn = func_0042FD7C(mkstr("crtn.o", arg2, NULL), dirs_for_crtn.entries);
                                if (exception_handling != 0) {
                                    var_s3_6 = "c++init_eh.o";
                                } else {
                                    var_s3_6 = "c++init.o";
                                }
                                cxx_init = func_0042FD7C(mkstr(var_s3_6, arg2, NULL), dirs_for_crtn.entries);
                                delta_init = func_0042FD7C(mkstr("delta_init.o", arg2, NULL), dirs_for_crtn.entries);
                            }
                        } else if (abi_flag != 0) {
                            crtx = func_0042FD7C(CRTX, dirs_for_abi_crtn.entries);
                            crtn = func_0042FD7C("crtn.o", dirs_for_abi_crtn.entries);
                            if (exception_handling != 0) {
                                var_s2_10 = "c++init_eh.o";
                            } else {
                                var_s2_10 = "c++init.o";
                            }
                            cxx_init = func_0042FD7C(var_s2_10, dirs_for_abi_crtn.entries);
                            delta_init = func_0042FD7C("delta_init.o", dirs_for_abi_crtn.entries);
                        } else if (non_shared != 0) {
                            crtx = func_0042FD7C(CRTX, dirs_for_nonshared_crtn.entries);
                            crtn = func_0042FD7C("crtn.o", dirs_for_nonshared_crtn.entries);
                            if (exception_handling != 0) {
                                var_s2_11 = "c++init_eh.o";
                            } else {
                                var_s2_11 = "c++init.o";
                            }
                            cxx_init = func_0042FD7C(var_s2_11, dirs_for_nonshared_crtn.entries);
                            delta_init = func_0042FD7C("delta_init.o", dirs_for_nonshared_crtn.entries);
                        } else {
                            crtx = func_0042FD7C(CRTX, dirs_for_crtn.entries);
                            crtn = func_0042FD7C("crtn.o", dirs_for_crtn.entries);
                            if (exception_handling != 0) {
                                var_s2_12 = "c++init_eh.o";
                            } else {
                                var_s2_12 = "c++init.o";
                            }
                            cxx_init = func_0042FD7C(var_s2_12, dirs_for_crtn.entries);
                            delta_init = func_0042FD7C("delta_init.o", dirs_for_crtn.entries);
                        }
                        break;
                    case 0x50:
                        if (arg1 != NULL) {
                            if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                                var_v0_3 = mkstr("-L", arg1, "-B", arg2, LibP, NULL);
                            } else {
                                var_v0_3 = mkstr("-L", arg1, LibP, NULL);
                            }
                            libp = var_v0_3;
                            libp_b = mkstr(arg1, "libp.b", arg2, NULL);
                        } else {
                            libp = "-lp";
                            if (non_shared != 0) {
                                libp_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libp.b", arg2, NULL);
                            } else {
                                libp_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libp.b", arg2, NULL);
                            }
                        }
                        break;
                    case 0x31:
                        if (arg1 != NULL) {
                            libpl1 = mkstr(arg1, LibPl1, arg2, NULL);
                            libpl1_b = mkstr(arg1, "libpl1.b", arg2, NULL);
                        } else {
                            libpl1 = "-lpl1";
                            if (non_shared != 0) {
                                libpl1_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libpl1.b", arg2, NULL);
                            } else {
                                libpl1_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libpl1.b", arg2, NULL);
                            }
                        }
                        break;
                    case 0x45:
                        if (arg1 != NULL) {
                            if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                                libexc = mkstr("-L", arg1, "-B", arg2, LibExc, NULL);
                                var_v0_4 = mkstr("-L", arg1, "-B", arg2, LibMld, NULL);
                            } else {
                                libexc = mkstr("-L", arg1, LibExc, NULL);
                                var_v0_4 = mkstr("-L", arg1, LibMld, NULL);
                            }
                            libmld = var_v0_4;
                            libexc_b = mkstr(arg1, "libexc.b", arg2, NULL);
                        } else {
                            if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                                libexc = mkstr("-L", "-B", arg2, LibExc, NULL);
                                libmld = mkstr("-L", "-B", arg2, LibMld, NULL);
                            } else {
                                libexc = "-lexc";
                                libmld = "-lmld";
                            }
                            if (non_shared != 0) {
                                libexc_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libexc.b", arg2, NULL);
                            } else {
                                libexc_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libexc.b", arg2, NULL);
                            }
                        }
                        break;
                    case 0x57:
                        if (arg1 != NULL) {
                            if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                                var_v0_5 = mkstr("-L", arg1, "-B", arg2, LibDw, NULL);
                            } else {
                                var_v0_5 = mkstr("-L", arg1, LibDw, NULL);
                            }
                            libdw = var_v0_5;
                            libdw_path = mkstr(arg1, "libdw.a", arg2, NULL);
                            libdw_b = mkstr(arg1, "libdw.b", arg2, NULL);
                        } else {
                            if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                                if (non_shared != 0) {
                                    var_v0_6 = mkstr("-L", comp_target_root, "usr/lib/nonshared/", currcomp, " -B", arg2, LibDw, 0);
                                } else {
                                    var_v0_6 = mkstr("-L", comp_target_root, "usr/lib/", currcomp, " -B", arg2, LibDw, 0);
                                }
                            } else if (non_shared != 0) {
                                var_v0_6 = mkstr("-L", comp_target_root, "usr/lib/", currcomp, LibDw, NULL);
                            } else {
                                var_v0_6 = mkstr("-L", comp_target_root, "usr/lib/", currcomp, LibDw, NULL);
                            }
                            libdw = var_v0_6;
                            if (non_shared != 0) {
                                libdw_path = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libdw.a", arg2, NULL);
                                libdw_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libdw.b", arg2, NULL);
                            } else {
                                libdw_path = mkstr(comp_target_root, "usr/lib/", currcomp, "libdw.a", arg2, NULL);
                                libdw_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libdw.b", arg2, NULL);
                            }
                        }
                        break;
                    case 0x58:
                        if (arg1 != NULL) {
                            if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                                var_v0_7 = mkstr("-L", arg1, " -B", arg2, LibXmalloc, NULL);
                            } else {
                                var_v0_7 = mkstr("-L", arg1, LibXmalloc, NULL);
                            }
                            libxmalloc = var_v0_7;
                            libxmalloc_b = mkstr(arg1, "libxmalloc.b", arg2, NULL);
                        } else {
                            libxmalloc = "-lxmalloc";
                            if (non_shared != 0) {
                                libxmalloc_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libxmalloc.b", arg2, NULL);
                            } else {
                                libxmalloc_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libxmalloc.b", arg2, NULL);
                            }
                        }
                        break;
                    case 0x4F:
                        if (arg1 != NULL) {
                            libsort = mkstr(arg1, LibSort, arg2, NULL);
                            libsort_b = mkstr(arg1, "libsort.b", arg2, NULL);
                        } else {
                            libsort = "-lsort";
                            if (non_shared != 0) {
                                libsort_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libsort.b", arg2, NULL);
                            } else {
                                libsort_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libsort.b", arg2, NULL);
                            }
                        }
                        break;
                    case 0x6E:
                        if (pflag != 0) {
                            if (arg1 != NULL) {
                                if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                                    libprof = mkstr("-L", arg1, " -B", arg2, LibProf1, NULL);
                                    libgprof = mkstr("-L", arg1, " -B", arg2, LibGProf1, NULL);
                                } else {
                                    libprof = mkstr("-L", arg1, LibProf1, NULL);
                                    libgprof = mkstr("-L", arg1, LibGProf1, NULL);
                                }
                            } else if (non_shared != 0) {
                                libprof = func_0042FD7C("libprof.a", dirs_for_nonshared_crtn.entries);
                                libgprof = func_0042FD7C("libgprof.a", dirs_for_nonshared_crtn.entries);
                            } else {
                                libprof = func_0042FD7C("libprof.a", dirs_for_crtn.entries);
                                libgprof = func_0042FD7C("libgprof.a", dirs_for_crtn.entries);
                            }
                        }
                        break;
                    case 0x4D:
                        if (arg1 != NULL) {
                            temp_s2 = chip_targ;
                            switch (temp_s2) {      /* switch 2; irregular */
                                default:            /* switch 2 */
                                case 0x0:           /* switch 2 */
                                    if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                                        var_v0_8 = mkstr(arg1, " -B", arg2, LibM, NULL);
                                    } else {
                                        var_v0_8 = mkstr("-L", arg1, LibM, NULL);
                                    }
                                    libm = var_v0_8;
                                    libm_b = mkstr(arg1, "libm.b", arg2, NULL);
                                    break;
                                case 0x1:           /* switch 2 */
                                    libm = mkstr(arg1, "libm_mips2.a", arg2, NULL);
                                    libm_b = mkstr(arg1, "libm_mips2.b", arg2, NULL);
                                    break;
                                case 0x2:           /* switch 2 */
                                    libm = mkstr(arg1, "libm_mips3.a", arg2, NULL);
                                    libm_b = mkstr(arg1, "libm_mips3.b", arg2, NULL);
                                    break;
                            }
                        } else {
                            temp_s2_2 = chip_targ;
                            switch (temp_s2_2) {    /* switch 1; irregular */
                                default:            /* switch 1 */
                                case 0x0:           /* switch 1 */
                                    libm = "-lm";
                                    if (non_shared != 0) {
                                        libm_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm.b", arg2, NULL);
                                    } else {
                                        libm_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libm.b", arg2, NULL);
                                    }
                                    break;
                                case 0x1:           /* switch 1 */
                                    if (non_shared != 0) {
                                        libm = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm_mips2.a", arg2, NULL);
                                        libm_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm_mips2.b", arg2, NULL);
                                    } else {
                                        libm = mkstr(comp_target_root, "usr/lib/", currcomp, "libm_mips2.a", arg2, NULL);
                                        libm_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libm_mips2.b", arg2, NULL);
                                    }
                                    break;
                                case 0x2:           /* switch 1 */
                                    if (non_shared != 0) {
                                        libm = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm_mips3.a", arg2, NULL);
                                        libm_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm_mips3.b", arg2, NULL);
                                    } else {
                                        libm = mkstr(comp_target_root, "usr/lib/", currcomp, "libm_mips3.a", arg2, NULL);
                                        libm_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libm_mips3.b", arg2, NULL);
                                    }
                                    break;
                            }
                        }
                        break;
                    case 0x46:
                        if (arg1 != NULL) {
                            if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                                var_v0_9 = mkstr("-L", arg1, " -B", arg2, LibF77, NULL);
                            } else {
                                var_v0_9 = mkstr("-L", arg1, LibF77, NULL);
                            }
                            libF77 = var_v0_9;
                            libF77_b = mkstr(arg1, "libF77.b", arg2, NULL);
                        } else {
                            libftn = "-lftn";
                            libF77 = "-lF77";
                            if (non_shared != 0) {
                                libF77_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libF77.b", arg2, NULL);
                            } else {
                                libF77_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libF77.b", arg2, NULL);
                            }
                        }
                        break;
                    case 0x49:
                        if (arg1 != NULL) {
                            if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                                var_v0_10 = mkstr("-L", arg1, " -B", arg2, LibI77, NULL);
                            } else {
                                var_v0_10 = mkstr("-L", arg1, LibI77, NULL);
                            }
                            libI77 = var_v0_10;
                            libI77_b = mkstr(arg1, "libI77.b", arg2, NULL);
                        } else {
                            libI77 = "-lI77";
                            if (non_shared != 0) {
                                libI77_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libI77.b", arg2, NULL);
                            } else {
                                libI77_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libI77.b", arg2, NULL);
                            }
                        }
                        break;
                    case 0x53:
                        if (arg1 != NULL) {
                            if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                                var_v0_11 = mkstr("-L", arg1, " -B", arg2, LibIsam, NULL);
                            } else {
                                var_v0_11 = mkstr("-L", arg1, LibIsam, NULL);
                            }
                            libisam = var_v0_11;
                            libisam_b = mkstr(arg1, "libisam.b", arg2, NULL);
                        } else {
                            libisam = "-lisam";
                            if (non_shared != 0) {
                                libisam_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libisam.b", arg2, NULL);
                            } else {
                                libisam_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libisam.b", arg2, NULL);
                            }
                        }
                        break;
                    case 0x55:
                        if (arg1 != NULL) {
                            if ((arg2 != NULL) && ((u8) *arg2 != 0)) {
                                var_v0_12 = mkstr("-L", arg1, " -B", arg2, LibU77, NULL);
                            } else {
                                var_v0_12 = mkstr("-L", arg1, LibU77, NULL);
                            }
                            libU77 = var_v0_12;
                            libU77_b = mkstr(arg1, "libU77.b", arg2, NULL);
                        } else {
                            libU77 = "-lU77";
                            if (non_shared != 0) {
                                libU77_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libU77.b", arg2, NULL);
                            } else {
                                libU77_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libU77.b", arg2, NULL);
                            }
                        }
                        break;
                    case 0x4B:
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
                    case 0x59:
                        if (arg1 != NULL) {
                            libI77_mp = mkstr(arg1, "libI77_mp.a", arg2, NULL);
                            libc_mp = mkstr(arg1, "libc_mp.a", arg2, NULL);
                        } else {
                            libI77_mp = "-lI77_mp";
                            libc_mp = "-lc_mp";
                        }
                        break;
                    default:
                        error(1, NULL, 0, NULL, 0, "Unknown character in -t%c\n", (s32) (u8) var_s1->unk_0);
                        exit(2);
                        break;
                }
            }
            temp_t7 = var_s1->unk_1;
            var_s1 += 1;
        } while (temp_t7 != 0);
    }
}

void newrunlib(void) {
    if (fiveflag != 0) {
        runlib_base = "usr/5lib";
    } else if (irix4 != 0) {
        runlib_base = "/usr/irix4/";
    } else {
        runlib_base = "/";
    }
    if (gethostsex() == targetsex) {
        runlib = runlib_base;
    } else if (targetsex == 0) {
        runlib = "eb/";
    } else {
        runlib = "el/";
    }
    relocate_passes("rP1EXCOnMFISU", NULL, NULL);
}

void compose_G0_libs(u8* arg0) {
    s8* var_v0;
    s8** var_at;
    u8 temp_t9;
    u8* temp_t2;

    if (*arg0 != 0) {
        do {
            temp_t9 = *arg0;
            switch (temp_t9) {
                case 0x50:
                    var_v0 = mkstr(LibP, "_G0", NULL);
                    var_at = &LibP;
block_16:
                    *var_at = var_v0;
                    break;
                case 0x45:
                    var_v0 = mkstr(LibExc, "_G0", NULL);
                    var_at = &LibExc;
                    goto block_16;
                case 0x31:
                    var_v0 = mkstr(LibPl1, "_G0", NULL);
                    var_at = &LibPl1;
                    goto block_16;
                case 0x43:
                    var_v0 = mkstr(LibCob, "_G0", NULL);
                    var_at = &LibCob;
                    goto block_16;
                case 0x4F:
                    var_v0 = mkstr(LibSort, "_G0", NULL);
                    var_at = &LibSort;
                    goto block_16;
                case 0x4D:
                    var_v0 = mkstr(LibM, "_G0", NULL);
                    var_at = &LibM;
                    goto block_16;
                case 0x46:
                    var_v0 = mkstr(LibF77, "_G0", NULL);
                    var_at = &LibF77;
                    goto block_16;
                case 0x49:
                    var_v0 = mkstr(LibI77, "_G0", NULL);
                    var_at = &LibI77;
                    goto block_16;
                case 0x55:
                    var_v0 = mkstr(LibU77, "_G0", NULL);
                    var_at = &LibU77;
                    goto block_16;
                case 0x53:
                    var_v0 = mkstr(LibIsam, "_G0", NULL);
                    var_at = &LibIsam;
                    goto block_16;
                case 0x57:
                    var_v0 = mkstr(LibDw, "_G0", NULL);
                    var_at = &LibDw;
                    goto block_16;
                case 0x58:
                    var_v0 = mkstr(LibXmalloc, "_G0", NULL);
                    var_at = &LibXmalloc;
                    goto block_16;
                case 0x6E:
                    var_v0 = mkstr(LibProf1, "_G0", NULL);
                    var_at = &LibProf1;
                    goto block_16;
            }
            temp_t2 = arg0 + 1;
            arg0 = temp_t2;
        } while (*temp_t2 != 0);
    }
}

void compose_reg_libs(u8* arg0) {
    s8* var_v0;
    s8** var_at;
    u8 temp_t9;
    u8* temp_t2;

    if (*arg0 != 0) {
        do {
            temp_t9 = *arg0;
            switch (temp_t9) {
                case 0x50:
                    var_v0 = mkstr("libp", ".a", NULL);
                    var_at = &LibP;
block_15:
                    *var_at = var_v0;
                    break;
                case 0x45:
                    var_v0 = mkstr("libexc", ".a", NULL);
                    var_at = &LibExc;
                    goto block_15;
                case 0x31:
                    var_v0 = mkstr("libpl1", ".a", NULL);
                    var_at = &LibPl1;
                    goto block_15;
                case 0x43:
                    var_v0 = mkstr("libcob", ".a", NULL);
                    var_at = &LibCob;
                    goto block_15;
                case 0x4F:
                    var_v0 = mkstr("libsort", ".a", NULL);
                    var_at = &LibSort;
                    goto block_15;
                case 0x4D:
                    var_v0 = mkstr("libm", ".a", NULL);
                    var_at = &LibM;
                    goto block_15;
                case 0x46:
                    var_v0 = mkstr("libF77", ".a", NULL);
                    var_at = &LibF77;
                    goto block_15;
                case 0x49:
                    var_v0 = mkstr("libI77", ".a", NULL);
                    var_at = &LibI77;
                    goto block_15;
                case 0x55:
                    var_v0 = mkstr("libU77", ".a", NULL);
                    var_at = &LibU77;
                    goto block_15;
                case 0x53:
                    var_v0 = mkstr("libisam", ".a", NULL);
                    var_at = &LibIsam;
                    goto block_15;
                case 0x6E:
                    LibProf1 = mkstr("libprof", ".a", NULL);
                    var_v0 = mkstr("libgprof", ".a", NULL);
                    var_at = &LibGProf1;
                    goto block_15;
                case 0x58:
                    var_v0 = mkstr("libxmalloc", ".a", NULL);
                    var_at = &LibXmalloc;
                    goto block_15;
            }
            temp_t2 = arg0 + 1;
            arg0 = temp_t2;
        } while (*temp_t2 != 0);
    }
}

s8* mkstr(s8* arg0, f64 arg1, s8* arg2, s8* arg3) {
    f64 sp60;
    f64 sp58;
    void* sp48;
    s32 temp_t1;
    s32 temp_t3;
    s32 temp_t7_2;
    s32 temp_t8;
    s32 temp_t9;
    s8* temp_v0;
    s8* var_s1;
    s8* var_s1_2;
    u32 temp_s3;
    u32 var_s2;
    void* temp_t5;
    void* temp_t7;

    temp_t7 = &arg0 - 1;
    temp_t9 = (s32) (temp_t7 + 3) & ~3;
    sp48 = temp_t7;
    sp60 = arg0;
    sp58 = arg1;
    sp48 = temp_t9 + 4;
    var_s1 = *temp_t9;
    var_s2 = 1;
    if (var_s1 != NULL) {
        do {
            temp_s3 = strlen(var_s1);
            temp_t3 = (s32) (sp48 + 3) & ~3;
            sp48 = temp_t3 + 4;
            var_s1 = *temp_t3;
            var_s2 += temp_s3;
        } while (var_s1 != NULL);
    }
    temp_v0 = malloc(var_s2);
    if (temp_v0 == NULL) {
        error(1, NULL, 0, "mkstr ()", 0x38BC, "out of memory\n");
        temp_t7_2 = errno;
        if (temp_t7_2 < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[temp_t7_2]);
        }
        exit(1);
    }
    temp_t5 = &arg0 - 1;
    *temp_v0 = 0;
    temp_t8 = (s32) (temp_t5 + 3) & ~3;
    sp48 = temp_t5;
    sp48 = temp_t8 + 4;
    var_s1_2 = *temp_t8;
    if (var_s1_2 != NULL) {
        do {
            strcat(temp_v0, var_s1_2);
            temp_t1 = (s32) (sp48 + 3) & ~3;
            sp48 = temp_t1 + 4;
            var_s1_2 = *temp_t1;
        } while (var_s1_2 != NULL);
    }
    return temp_v0;
}

void mklist(list* arg0) {
    s32 temp_t9;
    s8** temp_v0;

    temp_v0 = malloc(0x50U);
    arg0->entries = temp_v0;
    if (temp_v0 == NULL) {
        error(1, NULL, 0, "mklist ()", 0x38E1, "out of memory\n");
        temp_t9 = errno;
        if (temp_t9 < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[temp_t9]);
        }
        exit(1);
    }
    arg0->capacity = 0x14;
    arg0->length = 0;
    *arg0->entries = NULL;
}

void addstr(list* arg0, s8* str) {
    s32 temp_t3;
    s32 temp_t7;
    s8** temp_v0;

    temp_t7 = arg0->capacity;
    if ((arg0->length + 1) >= temp_t7) {
        temp_v0 = realloc(arg0->entries, (temp_t7 * 4) + 0x50);
        arg0->entries = temp_v0;
        if (temp_v0 == NULL) {
            error(1, NULL, 0, "addstr()", 0x3903, "out of memory\n");
            temp_t3 = errno;
            if (temp_t3 < sys_nerr) {
                error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[temp_t3]);
            }
            exit(1);
        }
        arg0->capacity += 0x14;
    }
    arg0->entries[arg0->length] = str;
    arg0->length += 1;
    arg0->entries[arg0->length] = NULL;
}

void addspacedstr(list* arg0, s8* str) {
    s8* sp34;
    s32 temp_t1;
    s32 temp_t7;
    s8** temp_v0;

    sp34 = str;
    do {
        sp34 = strchr(sp34, 0x20U);
        if (sp34 != NULL) {
            *sp34 = 0;
            sp34 += 1;
        }
        temp_t1 = arg0->capacity;
        if ((arg0->length + 1) >= temp_t1) {
            temp_v0 = realloc(arg0->entries, (temp_t1 * 4) + 0x50);
            arg0->entries = temp_v0;
            if (temp_v0 == NULL) {
                error(1, NULL, 0, "addspacedstr()", 0x392F, "out of memory\n");
                temp_t7 = errno;
                if (temp_t7 < sys_nerr) {
                    error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[temp_t7]);
                }
                exit(1);
            }
            arg0->capacity += 0x14;
        }
        arg0->entries[arg0->length] = str;
        arg0->length += 1;
        arg0->entries[arg0->length] = NULL;
        str = sp34;
    } while (sp34 != NULL);
}

s8* newstr(s8* src) {
    s8* sp34;

    sp34 = malloc(strlen(src) + 1);
    if (sp34 != NULL) {
        strcpy(sp34, src);
    } else {
        error(1, NULL, 0, NULL, 0, "newstr: unable to malloc for string %s\n", src);
        exit(2);
    }
    return sp34;
}

s32 save_place(list* arg0) {
    s32 sp34;
    s32 temp_t3;
    s32 temp_t7;
    s8** temp_v0;

    temp_t7 = arg0->capacity;
    if ((arg0->length + 1) >= temp_t7) {
        temp_v0 = realloc(arg0->entries, (temp_t7 * 4) + 0x50);
        arg0->entries = temp_v0;
        if (temp_v0 == NULL) {
            error(1, NULL, 0, "save_place()", 0x3967, "out of memory\n");
            temp_t3 = errno;
            if (temp_t3 < sys_nerr) {
                error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[temp_t3]);
            }
            exit(1);
        }
        arg0->capacity += 0x14;
    }
    sp34 = arg0->length;
    arg0->length += 1;
    arg0->entries[arg0->length] = NULL;
    return sp34;
}

void set_place(list* arg0, s8* str, s32 place) {
    if ((place < 0) || (place >= arg0->length)) {
        error(0, NULL, 0, "set_place ()", 0x3986, "place out of range");
        exit(1);
    }
    arg0->entries[place] = str;
}

void addlist(list* arg0, list* arg1) {
    s32 sp34;
    s32 temp_t0;
    s32 temp_t0_2;
    s32 temp_t7;
    s8* temp_t2;
    s8** temp_v0;

    temp_t7 = arg0->capacity;
    if ((arg0->length + arg1->length + 1) >= temp_t7) {
        temp_v0 = realloc(arg0->entries, ((temp_t7 + arg1->capacity) * 4) + 0x50);
        arg0->entries = temp_v0;
        if (temp_v0 == NULL) {
            error(1, NULL, 0, "addlist ()", 0x39A4, "out of memory\n");
            temp_t0 = errno;
            if (temp_t0 < sys_nerr) {
                error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[temp_t0]);
            }
            exit(1);
        }
        arg0->capacity = arg0->capacity + arg1->capacity + 0x14;
    }
    sp34 = 0;
    if (arg1->length > 0) {
        do {
            temp_t2 = arg1->entries[sp34];
            if (temp_t2 != NULL) {
                arg0->entries[arg0->length] = temp_t2;
                arg0->length += 1;
            }
            temp_t0_2 = sp34 + 1;
            sp34 = temp_t0_2;
        } while (temp_t0_2 < arg1->length);
    }
    arg0->entries[arg0->length] = NULL;
}

void adduldlist(list* arg0, list* arg1, list* arg2) {
    s32 sp3C;
    s32 sp38;
    s32 temp_t3;
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_t8;
    s32 temp_t9;
    s8* temp_t6_2;
    s8* temp_t9_2;
    s8** temp_v0;

    temp_t7 = arg0->capacity;
    if ((arg0->length + arg1->length + arg2->length + 1) >= temp_t7) {
        temp_v0 = realloc(arg0->entries, ((temp_t7 + arg1->capacity + arg2->capacity) * 4) + 0x50);
        arg0->entries = temp_v0;
        if (temp_v0 == NULL) {
            error(1, NULL, 0, "addlist ()", 0x39CB, "out of memory\n");
            temp_t6 = errno;
            if (temp_t6 < sys_nerr) {
                error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[temp_t6]);
            }
            exit(1);
        }
        arg0->capacity = arg0->capacity + (arg1->capacity + arg2->capacity) + 0x14;
    }
    sp3C = 0;
    if ((arg2->length > 0) && (*arg2->entries != NULL)) {
loop_8:
        arg0->entries[arg0->length] = arg2->entries[sp3C];
        arg0->length += 1;
        temp_t3 = sp3C + 1;
        sp3C = temp_t3;
        if (temp_t3 < arg2->length) {
            if (arg2->entries[temp_t3] != NULL) {
                goto loop_8;
            }
        }
    }
    sp38 = 0;
    if (arg1->length > 0) {
        do {
            temp_t6_2 = arg1->entries[sp38];
            if (temp_t6_2 != NULL) {
                arg0->entries[arg0->length] = temp_t6_2;
                arg0->length += 1;
            }
            temp_t9 = sp38 + 1;
            sp38 = temp_t9;
        } while (temp_t9 < arg1->length);
    }
    if (sp3C < arg2->length) {
        do {
            temp_t9_2 = arg2->entries[sp3C];
            if (temp_t9_2 != NULL) {
                arg0->entries[arg0->length] = temp_t9_2;
                arg0->length += 1;
            }
            temp_t8 = sp3C + 1;
            sp3C = temp_t8;
        } while (temp_t8 < arg2->length);
    }
    arg0->entries[arg0->length] = NULL;
}

s32 nodup(list* arg0, s8* str) {
    s32 var_s0;
    s8* temp_s1;

    var_s0 = 0;
    if (arg0->length > 0) {
loop_1:
        temp_s1 = arg0->entries[var_s0];
        if ((temp_s1 != NULL) && (strcmp(temp_s1, str) == 0)) {
            return 0;
        }
        var_s0 += 1;
        if (var_s0 >= arg0->length) {
            goto block_5;
        }
        goto loop_1;
    }
block_5:
    return 1;
}

s8 getsuf(s8* arg0) {
    s32 sp34;
    s32 sp30;
    u8 sp2F;
    s8* sp28;
    s32 temp_t0;
    s32 temp_t2;
    s32 temp_t5;
    s32 temp_t6;
    u8 temp_t4;
    u8 temp_t7;

    sp34 = 0;
    sp28 = arg0;
    temp_t7 = (u8) arg0->unk_0;
    arg0 += 1;
    sp2F = temp_t7;
    if (temp_t7 != 0) {
        do {
            if (sp2F == 0x2F) {
                sp34 = 0;
                sp28 = arg0;
            } else {
                sp34 += 1;
            }
            temp_t4 = (u8) arg0->unk_0;
            arg0 += 1;
            sp2F = temp_t4;
        } while (temp_t4 != 0);
    }
    if (sp34 < 3) {
        goto block_24;
    }
    if (arg0->unk_-3 == 0x2E) {
        if (arg0->unk_-2 == 0x43) {
            return 6;
        }
        return (s8) arg0->unk_-2;
    }
    temp_t2 = sp34 - 2;
    sp30 = temp_t2;
    if (temp_t2 > 0) {
loop_12:
        if ((u8) sp28[sp30] != 0x2E) {
            temp_t6 = sp30 - 1;
            sp30 = temp_t6;
            if (temp_t6 > 0) {
                goto loop_12;
            }
        }
    }
    if (sp30 == 0) {
        goto block_24;
    }
    temp_t0 = sp30;
    sp30 = 0;
    sp28 = &sp28[temp_t0] + 1;
    if (suffixes->unk0 != NULL) {
loop_17:
        if (strcmp(sp28, suffixes[sp30].unk0) == 0) {
            return (s8) suffixes[sp30].unk7;
        }
        temp_t5 = sp30 + 1;
        sp30 = temp_t5;
        if (suffixes[temp_t5].unk0 == NULL) {
            goto block_20;
        }
        goto loop_17;
    }
block_20:
    if (strcmp(sp28, "for") == 0) {
        return 0x66;
    }
    if (strcmp(sp28, "FOR") == 0) {
        return 0x46;
    }
block_24:
    return 0;
}

s8* mksuf(s8* arg0, u8 arg1) {
    s32 sp54;
    s32 sp50;
    u32 sp4C;
    s8* sp48;
    s8* sp44;
    s8* sp40;
    s8* sp3C;
    u8 sp3B;
    s32 temp_t0;
    s32 temp_t4;
    s32 temp_t7;
    s8* temp_t7_3;
    s8* temp_t9;
    struct _struct_suffixes_0x8* temp_t2;
    u8 temp_s0;
    u8 temp_t2_2;
    u8 temp_t7_2;

    sp3C = NULL;
    if ((s32) arg1 < 8) {
        sp54 = 0;
        if (suffixes->unk0 != NULL) {
loop_2:
            temp_t2 = &suffixes[sp54];
            if (temp_t2->unk_4 == arg1) {
                sp3C = temp_t2->unk0;
            } else {
                temp_t7 = sp54 + 1;
                sp54 = temp_t7;
                if (suffixes[temp_t7].unk0 != NULL) {
                    goto loop_2;
                }
            }
        }
        if (sp3C == NULL) {
            error(0, NULL, 0, "mksuf ()", 0x3A5A, "passed an unknown suffix value: %s\n", (s32) arg1);
            exit(4);
        }
        sp4C = strlen(sp3C);
    } else {
        sp4C = 0;
    }
    sp54 = 0;
    sp48 = savestr(arg0, (s32) sp4C);
    sp44 = sp48;
    sp40 = sp48;
    temp_t7_2 = (u8) *sp48;
    sp44 = sp48 + 1;
    sp3B = temp_t7_2;
    if (temp_t7_2 != 0) {
        do {
            if (sp3B == 0x2F) {
                sp54 = 0;
                sp40 = sp44;
            } else {
                sp54 += 1;
            }
            temp_t2_2 = (u8) sp44->unk_0;
            sp44 += 1;
            sp3B = temp_t2_2;
        } while (temp_t2_2 != 0);
    }
    if ((sp54 >= 3) && (sp44->unk_-3 == 0x2E)) {
        if ((s32) arg1 < 8) {
            strcpy(sp44 - 2, sp3C);
        } else {
            sp44->unk_-2 = arg1;
            sp44->unk_-1 = 0;
        }
    } else {
        temp_t4 = sp54 - 2;
        sp50 = temp_t4;
        if (temp_t4 > 0) {
loop_20:
            if ((u8) sp40[sp50] != 0x2E) {
                temp_t0 = sp50 - 1;
                sp50 = temp_t0;
                if (temp_t0 > 0) {
                    goto loop_20;
                }
            }
        }
        if (sp50 == 0) {
            error(1, NULL, 0, "mksuf ()", 0x3A81, "Bad file name, no suffix: %s\n", arg0);
            exit(4);
        }
        temp_t9 = &sp40[sp50] + 1;
        sp40 = temp_t9;
        if ((s32) arg1 < 8) {
            strcpy(temp_t9, sp3C);
        } else {
            sp40->unk_0 = (s8) arg1;
            sp40->unk_1 = 0;
        }
    }
    sp44 = sp48;
    if ((u8) *sp48 != 0) {
        do {
            temp_s0 = (u8) *sp48;
            temp_t7_3 = sp48 + 1;
            sp48 = temp_t7_3;
            if (temp_s0 == 0x2F) {
                sp44 = temp_t7_3;
            }
        } while ((u8) *sp48 != 0);
    }
    return sp44;
}

s8* savestr(s8* arg0, s32 arg1) {
    s8* sp34;
    s32 temp_t0;

    sp34 = malloc(strlen(arg0) + arg1 + 1);
    if (sp34 == NULL) {
        error(1, NULL, 0, "savestr ()", 0x3AA6, "out of memory\n");
        temp_t0 = errno;
        if (temp_t0 < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[temp_t0]);
        }
        exit(1);
    }
    strcpy(sp34, arg0);
    return sp34;
}

void mktempstr(void) {
    s32 temp_t0;

    tempstr->unk_0 = mktemp(mkstr(tmpdir, "ctmstXXXXXX", NULL));
    tempstr->unk_4 = mktemp(mkstr(tmpdir, "ctmuXXXXXX", NULL));
    tempstr->unk_8 = mktemp(mkstr(tmpdir, "ctmpXXXXXX", NULL));
    tempstr->unk_C = mktemp(mkstr(tmpdir, "ctmfXXXXXX", NULL));
    tempstr->unk_10 = mktemp(mkstr(tmpdir, "ctmluXXXXXX", NULL));
    tempstr->unk_14 = mktemp(mkstr(tmpdir, "ctmsXXXXXX", NULL));
    tempstr->unk_18 = mktemp(mkstr(tmpdir, "ctmmXXXXXX", NULL));
    tempstr->unk_1C = mktemp(mkstr(tmpdir, "ctmoXXXXXX", NULL));
    tempstr->unk_20 = mktemp(mkstr(tmpdir, "ctmosXXXXXX", NULL));
    tempstr->unk_24 = mktemp(mkstr(tmpdir, "ctmcbXXXXXX", NULL));
    tempstr->unk_28 = mktemp(mkstr(tmpdir, "ctmcXXXXXX", NULL));
    tempstr->unk_2C = mktemp(mkstr(tmpdir, "ctmaXXXXXX", NULL));
    tempstr->unk_30 = mktemp(mkstr(tmpdir, "ctmbXXXXXX", NULL));
    tempstr->unk_34 = mktemp(mkstr(tmpdir, "ctmlXXXXXX", NULL));
    tempstr->unk_38 = mktemp(mkstr(tmpdir, "ctmm4XXXXXX", NULL));
    tempstr->unk_3C = mktemp(mkstr(tmpdir, "ctmgtXXXXXX", NULL));
    tempstr->unk_40 = mktemp(mkstr(tmpdir, "ctmilXXXXXX", NULL));
    tempstr->unk_44 = mktemp(mkstr(tmpdir, "ctmltXXXXXX", NULL));
    tempstr->unk_48 = mktemp(mkstr(tmpdir, "ctmp1XXXXXX", NULL));
    tempstr->unk_50 = mktemp(mkstr(tmpdir, "ctmpdXXXXXX", NULL));
    tempstr->unk_4C = mktemp(mkstr(tmpdir, "ctmddXXXXXX", NULL));
    tempstr->unk_54 = mktemp(mkstr(tmpdir, "ctmloXXXXXX", NULL));
    tempstr->unk_58 = mktemp(mkstr(tmpdir, "ctmciXXXXXX", NULL));
    tempstr->unk_5C = mktemp(mkstr(tmpdir, "ctmvXXXXXX", NULL));
    tempstr->unk_60 = mktemp(mkstr(tmpdir, "ctmerrXXXXXX", NULL));
    tempstr->unk_64 = mktemp(mkstr(tmpdir, "ctmemXXXXXX", NULL));
    tempstr->unk_68 = mktemp(mkstr(tmpdir, "ctmeXXXXXX", NULL));
    tempstr->unk_6C = mktemp(mkstr(tmpdir, "ctmdXXXXXX", NULL));
    tempstr->unk_70 = mktemp(mkstr(tmpdir, "ctmqXXXXXX", NULL));
    tempstr->unk_74 = mktemp(mkstr(tmpdir, "ctmqsXXXXXX", NULL));
    tempstr->unk_78 = mktemp(mkstr(tmpdir, "ctmelfXXXXX", NULL));
    tempstr->unk_7C = mktemp(mkstr(tmpdir, "ctmkXXXXXX", NULL));
    tempstr->unk_84 = mktemp(mkstr(tmpdir, "ctmcmdXXXXXX", NULL));
    if ((compiler == 1) && ((temp_t0 = c_compiler_choice, (temp_t0 == 2)) || (temp_t0 == 3)) && (nofilt == 0) && (access(filter, 0x10) == 0)) {
        tempstr->unk_80 = mktemp(mkstr(tmpdir, "ctmfiltXXXXXX", NULL));
        return;
    }
    tempstr->unk_80 = NULL;
}

s32 run(s8* arg0, s8** arg1, s8* arg2, s8* arg3, s8* arg4) {
    s32* spA4;
    s32 spA0;
    s32 sp9C;
    s32 sp98;
    s32 sp94;
    s32 sp90;
    s32 sp8C;
    void (*sp88)();
    void (*sp84)();
    s32 sp80;
    s32 sp7C;
    s8* sp78;
    s32 sp74;
    s32 temp_a2;
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_t4;
    s32 temp_t5;
    s32 temp_t5_2;
    s32 temp_t5_3;
    s32 temp_t6;
    s32 temp_t7;
    s32 var_s0;

    if (vflag != 0) {
        fprintf(__iob + 0x20, "%s ", arg0);
        spA4 = arg1 + 4;
        if (arg1->unk_4 != 0) {
            do {
                temp_a2 = *spA4;
                spA4 += 4;
                fprintf(__iob + 0x20, "%s ", temp_a2);
            } while (*spA4 != 0);
        }
        if (arg2 != NULL) {
            fprintf(__iob + 0x20, "< %s ", arg2);
        }
        if (arg3 != NULL) {
            fprintf(__iob + 0x20, "> %s ", arg3);
        }
        fprintf(__iob + 0x20, "\n");
    }
    if (time_flag != 0) {
        settimes();
    }
    if (execute_flag == 0) {
        goto block_81;
    }
    if ((memory_flag != 0) && (pipe(B_1000EC98) < 0)) {
        error(1, NULL, 0, NULL, 0, "pipe failed for -showm");
        return -1;
    }
    spA0 = fork();
    if (spA0 == -1) {
        error(1, NULL, 0, NULL, 0, "no more processes\n");
        temp_t2 = errno;
        if (temp_t2 < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[temp_t2]);
        }
        return -1;
    }
    if (spA0 == 0) {
        if (memory_flag != 0) {
            func_00432BDC();
        }
        if (arg2 != NULL) {
            sp94 = open(arg2, 0);
            if (sp94 == -1) {
                error(1, NULL, 0, NULL, 0, "can't open input file: %s\n", arg2);
                temp_t5 = errno;
                if (temp_t5 < sys_nerr) {
                    error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[temp_t5]);
                }
                cleanup();
                exit(1);
            }
            dup2(sp94, (s32) __iob->_file);
        }
        if (arg3 != NULL) {
            sp90 = creat(arg3, 0x1FF);
            if (sp90 == -1) {
                error(1, NULL, 0, NULL, 0, "can't create output file: %s\n", arg3);
                temp_t5_2 = errno;
                if (temp_t5_2 < sys_nerr) {
                    error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[temp_t5_2]);
                }
                cleanup();
                exit(1);
            }
            dup2(sp90, (s32) __iob->unk_1D);
        }
        if (arg4 != NULL) {
            sp8C = creat(arg4, 0x1FF);
            if (sp8C == -1) {
                error(1, NULL, 0, NULL, 0, "can't create error file: %s\n", arg4);
                temp_t5_3 = errno;
                if (temp_t5_3 < sys_nerr) {
                    error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[temp_t5_3]);
                }
                cleanup();
                exit(1);
            }
            dup2(sp8C, (s32) __iob->unk_2D);
        }
        execvp(arg0, arg1);
        sp78 = func_00430414(arg0, 1);
        if ((errno == 2) && (sp78 != NULL)) {
            error(1, NULL, 0, NULL, 0, "%s is not installed (could not find %s).\n", sp78, arg0);
        } else {
            sp78 = func_00430414(arg0, 0);
            if ((errno == 2) && (sp78 != NULL)) {
                error(1, NULL, 0, NULL, 0, "%s may not be installed (could not find %s).\n", sp78, arg0);
            } else {
                error(1, NULL, 0, NULL, 0, "can't find or exec: %s\n", arg0);
                temp_t7 = errno;
                if (temp_t7 < sys_nerr) {
                    error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[temp_t7]);
                }
            }
        }
        cleanup();
        return exit(1);
    }
    sp84 = sigset(2, (void (*)())1);
    sp88 = sigset(0xF, (void (*)())1);
    if (memory_flag != 0) {
        sp74 = func_00432940(spA0);
        sp7C = ioctl(sp74, 0x71F9, &D_1000C1C8);
        if (sp7C < 0) {
            perror("PIOCMAP_SGI");
            kill(spA0, 9);
            return -1;
        }
        var_s0 = 0x10;
        if (0x10 != 0) {
            do {
                var_s0 -= 1;
                (&sp34[0])[var_s0] = 0;
            } while (var_s0 != 0);
        }
        if (ioctl(sp74, 0x7114, &sp34[0]) < 0) {
            perror("PIOCSEXIT");
            kill(spA0, 9);
            return -1;
        }
        ioctl(sp74, 0x7104, 0);
        close(sp74);
        goto block_58;
    }
block_58:
    sp9C = wait(&sp80);
    if (sp9C != spA0) {
loop_59:
        if (sp9C == -1) {
            return -1;
        }
        sp9C = wait(&sp80);
        if (sp9C == spA0) {
            goto block_62;
        }
        goto loop_59;
    }
block_62:
    sigset(2, sp84);
    sigset(0xF, sp88);
    if (time_flag != 0) {
        dotime(arg0);
    }
    if (memory_flag != 0) {
        func_00432D3C(arg0, sp7C);
    }
    temp_t0 = sp80;
    if ((temp_t0 & 0xFF) == 0x7F) {
        temp_t1 = (temp_t0 >> 8) & 0xFF;
        if (temp_t1 != 0) {
            sp98 = temp_t1;
            fprintf(__iob + 0x20, "STOPPED signal received from: %s ", arg0);
            fprintf(__iob + 0x20, " (Signal %d) ", sp98);
            fprintf(__iob + 0x20, " Process  %d abandoned\n", sp9C);
            return sp98;
        }
    }
    temp_t4 = sp80;
    if (!(temp_t4 & 0xFF)) {
        return (temp_t4 >> 8) & 0xFF;
    }
    temp_t6 = sp80;
    if (((temp_t6 & 0xFF) > 0) && !((temp_t6 >> 8) & 0xFF)) {
        sp98 = temp_t6 & 0x7F;
        fprintf(__iob + 0x20, "Fatal error in: %s ", arg0);
        printf(" child died due to signal %d.\n", sp98);
        if (sp98 == 9) {
            printf("Probably caused by running out of swap space -- check /usr/adm/SYSLOG.\n");
            exit(sp98);
        }
        if (sp98 == 2) {
            cleanup();
            exit(3);
        }
        fprintf(__iob + 0x20, "Fatal error in: %s ", arg0);
        fprintf(__iob + 0x20, " Signal %d ", sp98);
        if (sp80 & 0x80) {
            fprintf(__iob + 0x20, "- core dumped\n");
        } else {
            fprintf(__iob + 0x20, "\n");
        }
        return exit(sp98);
    }
block_81:
    return 0;
}

s32 edit_src(s8* arg0, s8* arg1, s32 arg2) {
    u8 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    void (*sp48)();
    void (*sp44)();
    s32 sp40;
    s32 temp_t4;
    s32 temp_t7;
    s32 temp_t8;

    sp54 = fork();
    if (sp54 == -1) {
        error(1, NULL, 0, NULL, 0, "fork to edit failed\n");
        temp_t8 = errno;
        if (temp_t8 < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[temp_t8]);
        }
        return -1;
    }
    if (sp54 == 0) {
        if (editflag == 2) {
            get_lino(&sp58, arg1, arg2);
            execlp(arg0, arg0, &sp58, arg1, "-l", tempstr->unk_64, "-f", "err-window", 0);
        } else if (xserver == NULL) {
            execlp(arg0, arg0, "+1", errout, arg1, 0);
        } else {
            execlp("xterm", "xterm", "-display", xserver, "-ls", "-e", arg0, "+1", errout, arg1, 0);
        }
        error(1, NULL, 0, NULL, 0, "failed to exec: %s\n", arg0);
        temp_t4 = errno;
        if (temp_t4 < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[temp_t4]);
        }
        return exit(1);
    }
    sp44 = sigset(2, (void (*)())1);
    sp48 = sigset(0xF, (void (*)())1);
    sp50 = wait(&sp40);
    if (sp50 != sp54) {
loop_14:
        if (sp50 == -1) {
            return -1;
        }
        sp50 = wait(&sp40);
        if (sp50 == sp54) {
            goto block_17;
        }
        goto loop_14;
    }
block_17:
    sigset(2, sp44);
    sigset(0xF, sp48);
    temp_t7 = sp40 & 0xFF;
    sp4C = temp_t7;
    if ((temp_t7 != 0) && (temp_t7 != 2)) {
        fprintf(__iob + 0x20, "Fatal error in: %s ", arg0);
        printf(" Signal %d ", sp4C);
        if (sp40 & 0x80) {
            fprintf(__iob + 0x20, "- core dumped\n");
        } else {
            fprintf(__iob + 0x20, "\n");
        }
        cleanup();
        exit(sp4C);
    }
    if (sp4C == 2) {
        cleanup();
        exit(3);
    }
    return sp40 & 0xFF00;
}

void get_lino(u8* arg0, s8* arg1, s32 arg2) {
    s32 sp83C;
    s32 sp838;
    u8* sp834;
    s8* sp830;
    s8 sp30;
    s8* temp_t2;
    s8* temp_t3;
    s8* temp_t8;
    s8* temp_t9;
    u32 temp_s1;

    sp834 = arg0;
    *arg0 = 0x2B;
    sp834 += 1;
    sp83C = open(errout, 0);
    sp838 = read(sp83C, &sp30, 0x800U);
    close(sp83C);
    if (sp838 < 0x800) {
        (&sp30)[sp838] = 0;
    } else {
        sp30.unk_7FF = 0;
    }
    switch (arg2) {
        case 0x1:
        case 0x2:
            sp830 = &sp30;
            if ((u32) &sp30 < (u32) &(&sp30)[sp838]) {
loop_6:
                if ((strncmp(sp830, ": Error: ", 9U) == 0) && (sp830 = strchr(sp830, 0x2CU), (sp830 != NULL)) && (temp_s1 = strlen(arg1), (strncmp(sp830 - temp_s1, arg1, strlen(arg1)) == 0)) && (strncmp(sp830, ", line ", 7U) == 0)) {
                    sp830 += 7;
                    if ((__ctype[(u8) sp830[7]].unk_1 & 4) && ((sp834 - arg0) < 0xB)) {
loop_12:
                        sp834->unk_0 = (u8) *sp830;
                        sp830 += 1;
                        sp834 += 1;
                        if (__ctype[(u8) *sp830].unk_1 & 4) {
                            if ((sp834 - arg0) >= 0xB) {

                            } else {
                                goto loop_12;
                            }
                        }
                    }
                } else {
                    temp_t8 = sp830 + 1;
                    sp830 = temp_t8;
                    if ((u32) temp_t8 >= (u32) &(&sp30)[sp838]) {

                    } else {
                        goto loop_6;
                    }
                }
            }
            break;
        case 0x3:
            sp830 = &sp30;
            if ((u32) &sp30 < (u32) &(&sp30)[sp838]) {
loop_18:
                if (strncmp(sp830, "Error on line ", 0xEU) == 0) {
                    sp830 += 0xE;
                    if ((__ctype[(u8) sp830[0xE]].unk_1 & 4) && ((sp834 - arg0) < 0xB)) {
loop_21:
                        sp834->unk_0 = (u8) *sp830;
                        sp830 += 1;
                        sp834 += 1;
                        if (__ctype[(u8) *sp830].unk_1 & 4) {
                            if ((sp834 - arg0) >= 0xB) {

                            } else {
                                goto loop_21;
                            }
                        }
                    }
                } else {
                    temp_t3 = sp830 + 1;
                    sp830 = temp_t3;
                    if ((u32) temp_t3 >= (u32) &(&sp30)[sp838]) {

                    } else {
                        goto loop_18;
                    }
                }
            }
            break;
        case 0x5:
        case 0x6:
            sp830 = &sp30;
            if ((u32) &sp30 < (u32) &(&sp30)[sp838]) {
loop_27:
                if (strncmp(sp830, "ERROR ", 6U) == 0) {
                    sp830 += 6;
                } else {
                    temp_t2 = sp830 + 1;
                    sp830 = temp_t2;
                    if ((u32) temp_t2 < (u32) &(&sp30)[sp838]) {
                        goto loop_27;
                    }
                }
            }
            if ((u32) sp830 < (u32) &(&sp30)[sp838]) {
loop_31:
                if (strncmp(sp830, " LINE ", 6U) == 0) {
                    sp830 += 6;
                    if ((__ctype[(u8) sp830[6]].unk_1 & 4) && ((sp834 - arg0) < 0xB)) {
loop_34:
                        sp834->unk_0 = (u8) *sp830;
                        sp830 += 1;
                        sp834 += 1;
                        if (__ctype[(u8) *sp830].unk_1 & 4) {
                            if ((sp834 - arg0) >= 0xB) {

                            } else {
                                goto loop_34;
                            }
                        }
                    }
                } else {
                    temp_t9 = sp830 + 1;
                    sp830 = temp_t9;
                    if ((u32) temp_t9 < (u32) &(&sp30)[sp838]) {
                        goto loop_31;
                    }
                }
            }
            break;
    }
    if ((u32) (arg0 + 1) < (u32) sp834) {
        sp834->unk_0 = 0;
        return;
    }
    sp834->unk_0 = 0x31;
    sp834->unk_1 = 0;
}

void show_err(s8* path) {
    ? sp10000;
    ? sp20;
    s32 temp_t6;

    sp10000.unk_28 = path;
    sp10000.unk_24 = open(sp10000.unk_28, 0);
    sp10000.unk_20 = read(sp10000.unk_24, &sp20, 0x10000U);
    close(sp10000.unk_24);
    temp_t6 = sp10000.unk_20;
    if (temp_t6 < 0x10000) {
        *(temp_t6 + &sp20) = 0;
    } else {
        sp20.unk_FFFF = 0;
    }
    fprintf(__iob + 0x20, "%s\n", &sp20);
}

void handler(void) {
    cleanup();
    exit(3);
}

void cleanup(void) {
    s8 sp27;
    s8* temp_t0;
    s8* temp_t1;
    s8* temp_t2;
    s8* temp_t3;
    s8* temp_t3_2;
    s8* temp_t4;
    s8* temp_t4_2;
    s8* temp_t5;
    s8* temp_t6;
    s8* temp_t7;
    s8* temp_t7_2;
    s8* temp_t8;
    s8* temp_t8_2;
    s8* temp_t9;

    if (Kflag == 0) {
        temp_t7 = passout;
        if (temp_t7 != NULL) {
            unlink(temp_t7);
        }
        temp_t8 = passin;
        if ((temp_t8 != NULL) && ((sp27 = getsuf(temp_t8), ((u8) sp27 == 0)) || (((u8) sp27 != (u8) srcsuf) && ((u8) sp27 != 0x6D))) && (Eflag == 0)) {
            unlink(passin);
        }
        if (tmpst != 0) {
            temp_t3 = symtab;
            if (temp_t3 != NULL) {
                unlink(temp_t3);
            }
        }
        temp_t4 = lpi_st;
        if (temp_t4 != NULL) {
            unlink(temp_t4);
        }
        temp_t5 = lpi_p1;
        if (temp_t5 != NULL) {
            unlink(temp_t5);
        }
        temp_t6 = lpi_pd;
        if (temp_t6 != NULL) {
            unlink(temp_t6);
        }
        temp_t7_2 = lpi_dd;
        if (temp_t7_2 != NULL) {
            unlink(temp_t7_2);
        }
        temp_t8_2 = uopt0str;
        if (temp_t8_2 != NULL) {
            unlink(temp_t8_2);
        }
        temp_t0 = ddoptstr;
        if (temp_t0 != NULL) {
            unlink(temp_t0);
        }
        temp_t9 = optstr;
        if (temp_t9 != NULL) {
            unlink(temp_t9);
        }
        temp_t1 = gentmp;
        if (temp_t1 != NULL) {
            unlink(temp_t1);
        }
        temp_t2 = binasm;
        if (temp_t2 != NULL) {
            unlink(temp_t2);
        }
        temp_t3_2 = linkorder;
        if (temp_t3_2 != NULL) {
            unlink(temp_t3_2);
        }
        temp_t4_2 = tmp_uldobj;
        if (temp_t4_2 != NULL) {
            unlink(temp_t4_2);
        }
        if (editflag != 0) {
            unlink(errout);
            if (editflag == 2) {
                unlink(tempstr->unk_64);
            }
        }
        if (compiler == 1) {
            unlink(tempstr->unk_84);
        }
    }
}

void whats(void) {
    s32 sp24;

    sp24 = runerror;
    if (compiler == 2) {
        printf("%s  (%s)\n", progname, "pc");
    } else if (compiler == 4) {
        printf("%s  (%s)\n", progname, "as");
    } else if (compiler == 3) {
        printf("%s  (%s)\n", progname, "f77");
    } else if (compiler == 5) {
        printf("%s  (%s)\n", progname, "pl1");
    } else if (compiler == 6) {
        printf("%s  (%s)\n", progname, "cobol");
    } else {
        printf("%s  (%s)\n", progname, "cc");
    }
    printf("\tMips Computer Systems %d.%d\n", 7, 0xA);
}

void settimes(void) {
    time0 = times(&tm0);
}

void dotime(s8* programName) {
    s32 sp6C;
    s32 sp68;
    f64 sp60;
    f64 sp58;
    struct tms sp48;
    f64 temp_f10;
    f64 temp_f6;

    sp6C = times(&sp48);
    sp68 = sp6C - time0;
    temp_f10 = (f64) ((((s32) sp48 + sp48.tms_cutime) - tm0.tms_utime) - tm0.tms_cutime) / 100.0;
    temp_f6 = (f64) (((sp48.tms_stime + sp48.tms_cstime) - tm0.tms_stime) - tm0.tms_cstime) / 100.0;
    sp60 = temp_f10;
    sp58 = temp_f6;
    fprintf(__iob + 0x20, "%s phase time: %.2fu %.2fs %u:%04.1f %.0f%%\n", programName, temp_f10, temp_f6, sp68 / 6000, (f64) (sp68 % 6000) / 100.0, ((temp_f10 + temp_f6) / ((f64) sp68 / 100.0)) * 100.0);
}

s8* func_0042FD7C(s8* name, s8** dirs) {
    s32 sp34;
    s8* sp30;
    s32 temp_t9;
    s8* var_v0;
    s8** temp_t5;

    if (*dirs != NULL) {
loop_1:
        if ((compiler == 1) && ((temp_t9 = c_compiler_choice, (temp_t9 == 2)) || (temp_t9 == 3)) && (sp30 = mkstr(*dirs, "/DCC", runlib, name, NULL), sp34 = open(sp30, 0, 0), (sp34 >= 0))) {
            close(sp34);
        } else {
            sp30 = mkstr(*dirs, runlib, name, NULL);
            sp34 = open(sp30, 0, 0);
            if (sp34 >= 0) {
                close(sp34);
            } else {
                temp_t5 = dirs + 4;
                dirs = temp_t5;
                if (*temp_t5 == NULL) {
                    goto block_9;
                }
                goto loop_1;
            }
        }
    } else {
block_9:
        if (abi_flag != 0) {
            var_v0 = mkstr("/", "usr/lib/abi", runlib, name, NULL);
        } else if (non_shared != 0) {
            var_v0 = mkstr("/", "usr/lib/nonshared", runlib, name, NULL);
        } else {
            var_v0 = mkstr("/", "usr/lib", runlib, name, NULL);
        }
        sp30 = var_v0;
    }
    return sp30;
}

s32 isdir(s8* path) {
    s32 spAC;
    ? sp24;

    spAC = stat(path, &sp24);
    if (spAC == -1) {
        goto block_4;
    }
    if ((sp38 & 0xF000) == 0x4000) {
        return 1;
    }
block_4:
    return 0;
}

s32 regular_not_writeable(s8* arg0) {
    s32 sp24;

    if (regular_file(arg0) != 1) {
        return 0;
    }
    sp24 = open(arg0, 2, 0x1FF);
    if (sp24 >= 0) {
        close(sp24);
        return 0;
    }
    return 1;
}

s32 regular_file(s8* path) {
    s32 spAC;
    ? sp24;

    spAC = stat(path, &sp24);
    if (spAC == -1) {
        return -1;
    }
    if ((sp38 & 0xF000) != 0x8000) {
        return 0;
    }
    return 1;
}

s8* basename(s8* path) {
    s8* temp_v0;
    s8* var_s0;
    u8 temp_t1;
    u8 temp_t2;
    u8 temp_t3;

    if ((path == NULL) || ((u8) *path == 0)) {
        B_1000E5E0->unk_0 = (s8) "."->unk_0;
        B_1000E5E0->unk_1 = (u8) "."->unk_1;
        return B_1000E5E0;
    }
    temp_v0 = strcpy(B_1000E5E0, path);
    var_s0 = &temp_v0[strlen(temp_v0)];
    if (var_s0 != B_1000E5E0) {
        temp_t1 = var_s0->unk_-1;
        var_s0 -= 1;
        if (temp_t1 == 0x2F) {
loop_5:
            var_s0->unk_0 = 0;
            if (var_s0 != B_1000E5E0) {
                temp_t2 = var_s0->unk_-1;
                var_s0 -= 1;
                if (temp_t2 == 0x2F) {
                    goto loop_5;
                }
            }
        }
    }
    if (var_s0 != B_1000E5E0) {
loop_8:
        temp_t3 = var_s0->unk_-1;
        var_s0 -= 1;
        if (temp_t3 == 0x2F) {
            var_s0 += 1;
        } else if (var_s0 != B_1000E5E0) {
            goto loop_8;
        }
    }
    return var_s0;
}

s8* dirname(s8* path) {
    s8* temp_v0;
    s8* var_s0;
    u8 temp_t1;
    u8 temp_t2;
    u8 temp_t2_2;
    u8 temp_t7;

    if ((path == NULL) || ((u8) *path == 0)) {
        B_1000E5E0->unk_0 = (s8) "."->unk_0;
        B_1000E5E0->unk_1 = (u8) "."->unk_1;
        return B_1000E5E0;
    }
    temp_v0 = strcpy(B_1000E5E0, path);
    var_s0 = &temp_v0[strlen(temp_v0)];
    if (var_s0 != B_1000E5E0) {
        temp_t1 = var_s0->unk_-1;
        var_s0 -= 1;
        if (temp_t1 == 0x2F) {
loop_5:
            if (var_s0 != B_1000E5E0) {
                temp_t2 = var_s0->unk_-1;
                var_s0 -= 1;
                if (temp_t2 == 0x2F) {
                    goto loop_5;
                }
            }
        }
    }
    if ((var_s0 == B_1000E5E0) && ((u8) *var_s0 == 0x2F)) {
        B_1000E5E0->unk_0 = (s8) "/"->unk_0;
        B_1000E5E0->unk_1 = (u8) "/"->unk_1;
        return B_1000E5E0;
    }
    if (var_s0 != B_1000E5E0) {
loop_11:
        temp_t7 = var_s0->unk_-1;
        var_s0 -= 1;
        if (temp_t7 == 0x2F) {
            if (var_s0 == B_1000E5E0) {
                B_1000E5E0->unk_0 = (s8) "/"->unk_0;
                B_1000E5E0->unk_1 = (u8) "/"->unk_1;
                return B_1000E5E0;
            }
            if ((u8) *var_s0 == 0x2F) {
                do {
                    temp_t2_2 = var_s0->unk_-1;
                    var_s0 -= 1;
                } while (temp_t2_2 == 0x2F);
            }
            var_s0[1] = 0;
            return B_1000E5E0;
        }
        if (var_s0 == B_1000E5E0) {
            goto block_18;
        }
        goto loop_11;
    }
block_18:
    B_1000E5E0->unk_0 = (s8) "."->unk_0;
    B_1000E5E0->unk_1 = (u8) "."->unk_1;
    return B_1000E5E0;
}

s8* func_00430414(s8* arg0, s32 arg1) {
    s32 sp2C;
    s32 sp28;
    s8* sp24;
    s8* sp20;
    s32 temp_t7;

    if (arg1 != 0) {
        sp24 = arg0;
    } else {
        sp24 = strrchr(arg0, 0x2F);
        if (sp24 != NULL) {
            sp24 += 1;
        }
    }
    sp28 = 0x14;
    sp2C = 0;
loop_5:
    if (arg1 != 0) {
        sp20 = prod_name[sp2C].unk4;
    } else {
        sp20 = prod_name[sp2C].unk0;
    }
    if (strcmp(sp24, sp20) == 0) {
        return prod_name[sp2C].unk8;
    }
    temp_t7 = sp2C + 1;
    sp2C = temp_t7;
    if (temp_t7 >= sp28) {
        return NULL;
    }
    goto loop_5;
}

s32 force_use_cfront(s32 argc, s8** argv) {
    s32 sp2C;
    s8* sp28;
    s32 sp24;
    s32 temp_t0;

    sp28 = getenv("USE_CFRONT");
    sp24 = 0;
    if ((sp28 != NULL) && ((u8) *sp28 != 0x30)) {
        return 1;
    }
    sp2C = 1;
    if (argc >= 2) {
loop_4:
        if (strcmp(argv[sp2C], "-exceptions") == 0) {
            D_1000BF7C = 1;
        }
        if ((D_1000BF7C == 0) && (exception_handling == 0) && ((strcmp(argv[sp2C], "-F") == 0) || (strcmp(argv[sp2C], "-Fc") == 0))) {
            return 1;
        }
        if ((strcmp(argv[sp2C], "-use_cfront") == 0) || (strcmp(argv[sp2C], "-v2") == 0) || (strcmp(argv[sp2C], "+I") == 0) || (strncmp(argv[sp2C], "-.", 2U) == 0)) {
            return 1;
        }
        temp_t0 = sp2C + 1;
        sp2C = temp_t0;
        if (temp_t0 >= argc) {
            goto block_17;
        }
        goto loop_4;
    }
block_17:
    return 0;
}

void exec_OCC(s32 argc, s8** argv) {
    s8 spB8;

    sprintf(&spB8, "%susr/bin/OCC", comp_host_root);
    *argv = &spB8;
    execv(&spB8, argv);
    error(2, NULL, 0, NULL, 0, "could not exec %s", &spB8);
}

s32 add_cxx_symbol_options(void) {
    addstr(&execlist, "-cxx");
    if ((D_1000BF90 == 0) && (strcmp(LD, "old_ld") != 0)) {
        addstr(&execlist, "-woff");
        addstr(&execlist, "134");
    }
    return 0;
}

void init_curr_dir(void) {
    if (D_1000C2F0 == NULL) {
        D_1000C2F0 = strrchr(progname, 0x2F);
        if (D_1000C2F0 == NULL) {
            D_1000C2F0 = progname;
        } else {
            D_1000C2F0 += 1;
        }
    }
    if (D_1000C1D0 == NULL) {
        D_1000C1D0 = getcwd(NULL, 0x400U);
        if (D_1000C1D0 == NULL) {
            D_1000C1D0 = getenv("PWD");
            if (D_1000C1D0 == NULL) {
                D_1000C1D0 = ".";
            }
        }
        if (strncmp(D_1000C1D0, "/tmp_mnt", 8U) == 0) {
            D_1000C1D0 += 8;
        }
    }
}

s8* full_path(s8* relative_path) {
    s8* sp24;
    s8* var_v0;

    init_curr_dir();
    if ((u8) *relative_path == 0x2F) {
        var_v0 = mkstr(relative_path, NULL);
    } else {
        var_v0 = mkstr(D_1000C1D0, "/", relative_path, NULL);
    }
    sp24 = var_v0;
    return var_v0;
}

void add_static_opt(s8* opt) {
    if (D_1000BF88 == 0) {
        addstr(&staticopts, opt);
    }
}

void record_static_fileset(s32 arg0) {
    s32 sp28E4;                                     /* compiler-managed */
    FILE* sp28E0;
    FILE* sp28DC;
    s32 sp28D8;
    s8 spD8;
    s8* spD4;
    u32 spD0;
    s8 spBC;
    ? sp34;
    s32 temp_t0;
    s32 temp_t0_2;
    s8* var_v0;

    sprintf(&spBC, ".%d", getpid());
    if (D_1000BF80 == NULL) {
        D_1000BF80 = "";
    }
    if (D_1000BF84 == NULL) {
        D_1000BF84 = mkstr("cvstatic.fileset", NULL);
    }
    if (((u8) *D_1000BF84 == 0x2F) || ((u8) *D_1000BF80 == 0)) {
        var_v0 = mkstr(D_1000BF84, NULL);
    } else {
        var_v0 = mkstr(D_1000BF80, D_1000BF84, NULL);
    }
    D_1000C2E8 = var_v0;
    D_1000C2EC = mkstr(tmpdir, "cvstatic.fileset", &spBC, NULL);
    spD4 = full_path((s8* ) arg0);
    spD0 = strlen(spD4);
    if (vflag != 0) {
        fprintf(__iob + 0x20, "Static fileset: %s %s", spD4, D_1000C2F0);
        sp28E4 = 0;
        if (staticopts.length > 0) {
            do {
                fprintf(__iob + 0x20, " %s", staticopts.entries[sp28E4]);
                temp_t0 = sp28E4 + 1;
                sp28E4 = temp_t0;
            } while (temp_t0 < staticopts.length);
        }
        fprintf(__iob + 0x20, "\n");
    }
    sp28E0 = fopen(D_1000C2EC, "w+");
    if (sp28E0 == NULL) {
        error(1, NULL, 0, "record_static_fileset", 0, "could not open cvstatic fileset temp file %s\n", D_1000C2EC);
        perror(D_1000C2F0);
        cleanup();
        exit(1);
    }
    sp28D8 = open(D_1000C2E8, 0x102, 0x1FF);
    if (sp28D8 < 0) {
        error(1, NULL, 0, "record_static_fileset", 0, "could not open or create cvstatic fileset file %s\n", D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }
    if (flock(sp28D8, 2) < 0) {
        error(1, NULL, 0, "record_static_fileset", 0, "error in locking cvstatic fileset file %s\n", D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }
    if (fstat(sp28D8, &sp34) < 0) {
        error(1, NULL, 0, "record_static_fileset", 0, "could not fstat cvstatic fileset file %s\n", D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }
    if (sp64 == 0) {
        fprintf(sp28E0, "-cvstatic\n");
    }
    sp28DC = fdopen(sp28D8, "r+");
    if (sp28DC == NULL) {
        error(1, NULL, 0, "record_static_fileset", 0, "could not fdopen cvstatic fileset file %s\n", D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }
    if (fgets(&spD8, 0x2800, sp28DC) != NULL) {
        do {
            if ((strncmp(&spD8, spD4, spD0) != 0) || !(__ctype[(u8) (&spD8)[spD0]].unk_1 & 8)) {
                fputs(&spD8, sp28E0);
            }
        } while (fgets(&spD8, 0x2800, sp28DC) != NULL);
    }
    fprintf(sp28E0, "%s %s", spD4, D_1000C2F0);
    sp28E4 = 0;
    if (staticopts.length > 0) {
        do {
            fprintf(sp28E0, " %s", staticopts.entries[sp28E4]);
            temp_t0_2 = sp28E4 + 1;
            sp28E4 = temp_t0_2;
        } while (temp_t0_2 < staticopts.length);
    }
    fprintf(sp28E0, "\n");
    free(spD4);
    rewind(sp28DC);
    rewind(sp28E0);
    ftruncate((s32) sp28DC->_file, 0);
    sp28E4 = fread(&spD8, 1U, 0x2800U, sp28E0);
    if ((s32) sp28E4 > 0) {
        do {
            if (fwrite(&spD8, 1U, sp28E4, sp28DC) != sp28E4) {
                error(1, NULL, 0, "record_static_fileset", 0, "error in writing cvstatic fileset file %s\n", D_1000C2E8);
                perror(D_1000C2F0);
                unlink(D_1000C2EC);
                cleanup();
                exit(1);
            }
            sp28E4 = fread(&spD8, 1U, 0x2800U, sp28E0);
        } while ((s32) sp28E4 > 0);
    }
    fclose(sp28DC);
    fclose(sp28E0);
    unlink(D_1000C2EC);
    free(D_1000C2E8);
    free(D_1000C2EC);
}

s32 touch(s8* arg0) {
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s8* sp30;
    u32 temp_s1;

    sp3C = time(0);
    init_curr_dir();
    if (vflag != 0) {
        fprintf(__iob + 0x20, "%s: touch %s\n", D_1000C2F0, arg0);
    }
    sp38 = sp3C;
    sp34 = sp3C;
    if (utime(arg0, (struct utimbuf* ) &sp34) < 0) {
        temp_s1 = strlen(arg0);
        sp30 = malloc(strlen(D_1000C2F0) + temp_s1 + 0xA);
        sprintf(sp30, "%s: touch %s", D_1000C2F0, arg0);
        perror(sp30);
        free(sp30);
        return -1;
    }
    return 0;
}

void add_prelinker_objects(list* arg0, list* arg1) {
    s32 sp24;
    s32 temp_t0;
    s32 temp_t6;
    s8* temp_t3;
    u8 temp_t5;

    sp24 = 0;
    if (arg1->length > 0) {
        do {
            temp_t3 = arg1->entries[sp24];
            if (((u8) temp_t3->unk_0 == 0x2D) && (temp_t5 = temp_t3->unk_1, (temp_t5 != 0x6C)) && (temp_t5 != 0x4C)) {
                if (strcmp(arg1->entries[sp24], "-nostdlib") == 0) {
                    addstr(arg0, mkstr("-YB", NULL));
                } else if (strcmp(arg1->entries[sp24], "-objectlist") == 0) {
                    addstr(arg0, mkstr("-YO=", arg1->entries[sp24].unk_4, NULL));
                    sp24 += 1;
                } else if (strcmp(arg1->entries[sp24], "-B") == 0) {
                    temp_t0 = sp24 + 1;
                    sp24 = temp_t0;
                    if (strcmp(arg1->entries[temp_t0], "static") == 0) {
                        addstr(arg0, mkstr("-Bstatic", NULL));
                    } else if (strcmp(arg1->entries[sp24], "dynamic") == 0) {
                        addstr(arg0, mkstr("-Bdynamic", NULL));
                    }
                }
            } else {
                addstr(arg0, arg1->entries[sp24]);
            }
            temp_t6 = sp24 + 1;
            sp24 = temp_t6;
        } while (temp_t6 < arg1->length);
    }
}

u32 quoted_length(s8* arg0, s32* arg1) {
    u32 spC;
    u8 spB;
    s8* var_a0;

    spC = 0;
    *arg1 = 0;
    var_a0 = arg0 + 1;
    spB = (u8) *arg0;
    if (spB != 0) {
        do {
            if ((*arg1 == 0) && ((spB == 0x27) || (spB == 0x7C) || (spB == 0x26) || (spB == 0x2A) || (spB == 0x3F) || (spB == 0x5B) || (spB == 0x5D) || (spB == 0x3B) || (spB == 0x21) || (spB == 0x28) || (spB == 0x29) || (spB == 0x5E) || (spB == 0x3C) || (spB == 0x3E) || ((s32) spB < 0x21) || (spB == 9) || (spB == 0x22) || (spB == 0x5C) || (spB == 0x60) || (spB == 0x24))) {
                *arg1 = 1;
                spC += 2;
            }
            if ((spB == 0x22) || (spB == 0x5C) || (spB == 0x60) || (spB == 0x24)) {
                spC += 1;
            }
            var_a0 += 1;
            spC += 1;
            spB = var_a0->unk_-1;
        } while (spB != 0);
    }
    return spC;
}

u32 quote_shell_arg(s8* arg0, s8* arg1) {
    u8 sp2F;
    s32 sp28;
    u32 sp24;
    u8 temp_t2;
    u8 temp_t4;

    sp28 = 0;
    sp24 = quoted_length(arg0, &sp28);
    if (sp28 != 0) {
        *arg1 = 0x22;
        arg1 += 1;
    }
    temp_t2 = (u8) *arg0;
    arg0 += 1;
    sp2F = temp_t2;
    if (temp_t2 != 0) {
        do {
            if ((sp2F == 0x22) || (sp2F == 0x5C) || (sp2F == 0x60) || (sp2F == 0x24)) {
                *arg1 = 0x5C;
                arg1 += 1;
            }
            *arg1 = (s8) sp2F;
            arg1 += 1;
            temp_t4 = (u8) *arg0;
            arg0 += 1;
            sp2F = temp_t4;
        } while (temp_t4 != 0);
    }
    if (sp28 != 0) {
        *arg1 = 0x22;
        arg1 += 1;
    }
    return sp24;
}

void func_00431A3C(s32 arg0, s8** arg1) {
    s32 sp24;
    s32 temp_t2;
    s8* temp_t2_2;
    s8** temp_v0;

    B_1000E4C0 = arg0;
    temp_v0 = malloc((arg0 * 4) + 4);
    sp24 = 0;
    B_1000E4C4 = temp_v0;
    if (arg0 > 0) {
        do {
            temp_t2_2 = *(arg1 + (sp24 * 4));
            if (temp_t2_2 != NULL) {
                B_1000E4C4[sp24] = strdup(temp_t2_2);
            } else {
                B_1000E4C4[sp24] = NULL;
            }
            temp_t2 = sp24 + 1;
            sp24 = temp_t2;
        } while (temp_t2 < arg0);
    }
    B_1000E4C4[B_1000E4C0] = NULL;
}

void func_00431B38(s32 arg0, s32 arg1) {
    s32 sp4;
    s32 temp_t2;

    sp4 = 0;
    if (arg1 > 0) {
        do {
            B_1000E4C4[arg0 + sp4] = NULL;
            temp_t2 = sp4 + 1;
            sp4 = temp_t2;
        } while (temp_t2 < arg1);
    }
}

void func_00431B88(FILE* arg0, s8* arg1, s32 arg2) {
    s8* temp_t0;

    if (arg2 != 0) {
        fputs("CMDLINE=", arg0);
    }
    fprintf(arg0, "%s ", progname);
    if (cflag == 0) {
        fputs("-c ", arg0);
    }
    if ((srcfiles.length == 1) && (cflag != 0)) {
        temp_t0 = B_1000ECCC;
        if (temp_t0 != NULL) {
            fprintf(arg0, "-o %s ", temp_t0);
        }
    }
    fprintf(arg0, "%s %s\n", B_1000ECDC, arg1);
    if (arg2 != 0) {
        fputs("PWD=", arg0);
    }
    fprintf(arg0, "%s\n", D_1000C1D0);
    if (arg2 != 0) {
        fputs("----\n", arg0);
    }
}

void func_00431D00(s8* arg0) {
    FILE* sp34;

    sp34 = fopen(tempstr->unk_84, "w");
    if (sp34 != NULL) {
        init_curr_dir();
        func_00431B88(sp34, arg0, 0);
        fclose(sp34);
        return;
    }
    error(2, NULL, 0, NULL, 0, "cannot open commandfile '%s'\n", tempstr->unk_84);
}

void func_00431DD8(void) {
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s8* sp24;
    s32 temp_t2_2;
    s32 temp_t7;
    s8* temp_t2;
    s8* temp_t6;
    s8* temp_t9;

    sp34 = 0;
    sp30 = 0;
    sp2C = 0;
    sp28 = 1;
    if (B_1000E4C0 >= 2) {
        do {
            temp_t2 = B_1000E4C4[sp28];
            if (temp_t2 != NULL) {
                sp34 = sp34 + quoted_length(temp_t2, &sp2C) + 1;
            }
            temp_t7 = sp28 + 1;
            sp28 = temp_t7;
        } while (temp_t7 < B_1000E4C0);
    }
    sp24 = malloc(sp34 + 1);
    B_1000ECDC = sp24;
    sp28 = 1;
    if (B_1000E4C0 >= 2) {
        do {
            temp_t6 = B_1000E4C4[sp28];
            if (temp_t6 != NULL) {
                temp_t9 = &sp24[quote_shell_arg(temp_t6, sp24)];
                sp24 = temp_t9;
                *temp_t9 = 0x20;
                sp24 += 1;
            }
            temp_t2_2 = sp28 + 1;
            sp28 = temp_t2_2;
        } while (temp_t2_2 < B_1000E4C0);
    }
    if ((u32) B_1000ECDC < (u32) sp24) {
        sp24->unk_-1 = 0;
        return;
    }
    sp24->unk_0 = 0;
}

void skip_old_ii_controls(FILE* arg0) {
    s32 sp54;
    s32 sp50;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;

    sp50 = 0;
    if (__us_rsthread_stdio != 0) {
        sp54 = __semgetc(arg0);
    } else {
        arg0->_cnt -= 1;
        if (arg0->_cnt < 0) {
            var_s0 = __filbuf(arg0);
        } else {
            var_s0 = (s32) *arg0->_ptr;
            arg0->_ptr += 1;
        }
        sp54 = var_s0;
    }
    if (sp54 != -1) {
loop_7:
        if (sp54 == 0x2D) {
            if (__us_rsthread_stdio != 0) {
                var_s0_2 = __semgetc(arg0);
            } else {
                arg0->_cnt -= 1;
                if (arg0->_cnt < 0) {
                    var_s1 = __filbuf(arg0);
                } else {
                    var_s1 = (s32) *arg0->_ptr;
                    arg0->_ptr += 1;
                }
                var_s0_2 = var_s1;
            }
            sp54 = var_s0_2;
            if (sp54 == 0x2D) {
                if (__us_rsthread_stdio != 0) {
                    var_s2 = __semgetc(arg0);
                } else {
                    arg0->_cnt -= 1;
                    if (arg0->_cnt < 0) {
                        var_s3 = __filbuf(arg0);
                    } else {
                        var_s3 = (s32) *arg0->_ptr;
                        arg0->_ptr += 1;
                    }
                    var_s2 = var_s3;
                }
                sp54 = var_s2;
                if (sp54 == 0x2D) {
                    if (__us_rsthread_stdio != 0) {
                        var_s4 = __semgetc(arg0);
                    } else {
                        arg0->_cnt -= 1;
                        if (arg0->_cnt < 0) {
                            var_s5 = __filbuf(arg0);
                        } else {
                            var_s5 = (s32) *arg0->_ptr;
                            arg0->_ptr += 1;
                        }
                        var_s4 = var_s5;
                    }
                    sp54 = var_s4;
                    if (sp54 == 0x2D) {
                        sp50 = 1;
                    }
                }
            }
        }
        if ((sp54 != 0xA) && (sp54 != -1)) {
loop_32:
            if (__us_rsthread_stdio != 0) {
                sp54 = __semgetc(arg0);
            } else {
                arg0->_cnt -= 1;
                if (arg0->_cnt < 0) {
                    var_s0_3 = __filbuf(arg0);
                } else {
                    var_s0_3 = (s32) *arg0->_ptr;
                    arg0->_ptr += 1;
                }
                sp54 = var_s0_3;
            }
            if ((sp54 != 0xA) && (sp54 != -1)) {
                goto loop_32;
            }
        }
        if (sp50 == 0) {
            if (sp54 == 0xA) {
                if (__us_rsthread_stdio != 0) {
                    sp54 = __semgetc(arg0);
                } else {
                    arg0->_cnt -= 1;
                    if (arg0->_cnt < 0) {
                        var_s0_4 = __filbuf(arg0);
                    } else {
                        var_s0_4 = (s32) *arg0->_ptr;
                        arg0->_ptr += 1;
                    }
                    sp54 = var_s0_4;
                }
            }
            if (sp54 != -1) {
                goto loop_7;
            }
        }
    }
    if (sp54 == -1) {
        rewind(arg0);
    }
}

s8* make_ii_file_name(s8* arg0) {
    s8* sp2C;
    u32 sp28;
    s8* temp_t8;

    sp2C = basename(arg0);
    sp28 = strlen(sp2C);
    sp2C = mkstr(sp2C, "   ", NULL);
    temp_t8 = &sp2C[sp28];
    if ((temp_t8->unk_-2 == 0x2E) && (temp_t8->unk_-1 == 0x6F)) {
        temp_t8->unk_-1 = (u8) "ii"->unk_0;
        temp_t8->unk_0 = (s8) "ii"->unk_1;
        temp_t8->unk_1 = (u8) "ii"->unk_2;
    } else {
        sp2C[sp28] = (unaligned s32) *".ii";
    }
    return mkstr(dirname(arg0), "/ii_files/", sp2C, NULL);
}

void update_instantiation_info_file(s8* arg0, s8* arg1) {
    s8* sp54;
    s8* sp50;
    FILE* sp4C;
    FILE* sp48;
    s32 sp44;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s1_2;

    sp54 = make_ii_file_name(arg1);
    sp50 = mkstr(sp54, ".NEW", NULL);
    sp4C = fopen(sp54, "r");
    if (sp4C != NULL) {
        init_curr_dir();
        if (vflag != 0) {
            fprintf(__iob + 0x20, "%s: update_instantiation_info_file %s\n", D_1000C2F0, sp54);
        }
        sp48 = fopen(sp50, "w");
        if (sp48 == NULL) {
            error(1, NULL, 0, "update_instantiation_info_file", 0, "error in creating file %s\n", sp50);
            perror(D_1000C2F0);
            cleanup();
            exit(1);
        }
        skip_old_ii_controls(sp4C);
        func_00431B88(sp48, arg0, 1);
        if (__us_rsthread_stdio != 0) {
            var_s0 = __semgetc(sp4C);
        } else {
            sp4C->_cnt -= 1;
            if (sp4C->_cnt < 0) {
                var_s1 = __filbuf(sp4C);
            } else {
                var_s1 = (s32) *sp4C->_ptr;
                sp4C->_ptr += 1;
            }
            var_s0 = var_s1;
        }
        sp44 = var_s0;
        if (sp44 != -1) {
            do {
                if (__us_rsthread_stdio != 0) {
                    __semputc(sp44, sp48);
                } else {
                    sp48->_cnt -= 1;
                    if (sp48->_cnt < 0) {
                        __flsbuf(sp44, sp48);
                    } else {
                        *sp48->_ptr = (u8) sp44;
                        sp48->_ptr += 1;
                    }
                }
                if (__us_rsthread_stdio != 0) {
                    var_s0_2 = __semgetc(sp4C);
                } else {
                    sp4C->_cnt -= 1;
                    if (sp4C->_cnt < 0) {
                        var_s1_2 = __filbuf(sp4C);
                    } else {
                        var_s1_2 = (s32) *sp4C->_ptr;
                        sp4C->_ptr += 1;
                    }
                    var_s0_2 = var_s1_2;
                }
                sp44 = var_s0_2;
            } while (sp44 != -1);
        }
        fclose(sp4C);
        fclose(sp48);
        if (rename(sp50, sp54) < 0) {
            error(1, NULL, 0, "update_instantiation_info_file", 0, "error in renaming %s to %s\n", sp50, sp54);
            perror(D_1000C2F0);
            cleanup();
            exit(1);
        }
    }
    free(sp54);
    free(sp50);
}

s32 func_00432940(s32 arg0) {
    s32 sp29C;
    s8 sp288;
    ? sp68;
    s32 sp64;
    s32 var_s0;

    sp64 = 0;
    sprintf(&sp288, "/proc/%-d", arg0);
    sp29C = open(&sp288, 0x402);
    if (sp29C == -1) {
        perror("Opening /proc");
        kill(arg0, 9);
        exit(1);
    }
    var_s0 = 0x10;
    if (0x10 != 0) {
        do {
            var_s0 -= 1;
            (&sp24[0])[var_s0] = 0;
        } while (var_s0 != 0);
    }
    sp24[0] |= 2;
    if (ioctl(sp29C, 0x7112, &sp24[0]) < 0) {
        perror("PIOCSENTRY");
        kill(arg0, 9);
        exit(1);
    }
    func_00432C94();
    if (ioctl(sp29C, 0x7103, &sp68) < 0) {
        perror("PIOCWSTOP");
        kill(arg0, 9);
        exit(1);
    }
    if (sp6C != 3) {
        perror("program halted prematurely");
        kill(arg0, 9);
        exit(1);
    }
    if (sp6E != 2) {
        perror("program halted in wrong system call");
        kill(arg0, 9);
        exit(1);
    }
    if (sp148 != 0) {
        perror("unknown problem\n");
        exit(1);
    }
    return sp29C;
}

void func_00432BDC(void) {
    ? sp27;
    s32 sp20;

    close(B_1000EC98->unk_4);
    sp20 = read(B_1000EC98->unk_0, &sp27, 1U) != 1;
    if (sp20 != 0) {
        perror("read on pipe failed");
        exit(1);
    }
    close(B_1000EC98->unk_0);
}

void func_00432C94(void) {
    ? sp27;

    close(B_1000EC98->unk_0);
    if (write(B_1000EC98->unk_4, &sp27, 1U) != 1) {
        perror("write on pipe failed");
        exit(1);
    }
    close(B_1000EC98->unk_4);
}

void func_00432D3C(s8* arg0, s32 count) {
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    u32 sp64;
    u32 sp60;
    u32 sp5C;
    u32 sp58;
    u32 sp54;
    u32 sp50;
    u32 sp4C;
    u32 sp48;
    s32 sp44;
    prmap_sgi_t* temp_t0;
    prmap_sgi_t* temp_t2;
    prmap_sgi_t* temp_t3;
    prmap_sgi_t* temp_t6;
    prmap_sgi_t* temp_t9;
    s32 temp_t1;
    s32 temp_t4;
    s32 temp_t6_2;

    sp44 = memory_flag > 1;
    sp48 = 0;
    sp4C = 0;
    sp50 = 0;
    sp54 = 0;
    sp58 = 0;
    sp5C = 0;
    sp60 = 0;
    sp64 = 0;
    sp68 = getpagesize();
    sp74 = 0;
    if (count > 0) {
        do {
            sp70 = 0;
            temp_t2 = &B_1000CAC0[sp74];
            temp_t4 = temp_t2->pr_mflags & 0xFFFF;
            sp6C = temp_t4;
            if (temp_t4 == 0x80D) {
                sp70 = 1;
                sp64 += temp_t2->pr_vsize * sp68;
            }
            if (sp6C == 0xD) {
                sp70 = 1;
                sp54 += B_1000CAC0[sp74].pr_vsize * sp68;
            }
            if (sp6C == 0x2003) {
                temp_t6 = &B_1000CAC0[sp74];
                if ((u32) temp_t6->pr_vaddr < 0x10000000U) {
                    sp70 = 1;
                    sp50 += temp_t6->pr_vsize * sp68;
                }
            }
            if ((sp6C == 3) || (sp6C == 1) || (sp6C == 0xB) || (sp6C == 9)) {
                temp_t9 = &B_1000CAC0[sp74];
                if ((u32) temp_t9->pr_vaddr < 0x10000000U) {
                    sp70 = 1;
                    sp48 += temp_t9->pr_vsize * sp68;
                }
            }
            temp_t6_2 = sp6C & ~0x800;
            sp6C = temp_t6_2;
            if (temp_t6_2 == 0x2003) {
                temp_t0 = &B_1000CAC0[sp74];
                if ((u32) temp_t0->pr_vaddr >= 0x10000000U) {
                    sp70 = 1;
                    sp60 += temp_t0->pr_vsize * sp68;
                }
            }
            if (sp6C == 0x2013) {
                temp_t3 = &B_1000CAC0[sp74];
                if ((u32) temp_t3->pr_vaddr >= 0x10000000U) {
                    sp70 = 1;
                    sp5C += temp_t3->pr_vsize * sp68;
                }
            }
            if (sp6C == 0x23) {
                sp70 = 1;
                sp58 += B_1000CAC0[sp74].pr_vsize * sp68;
            }
            if (sp70 == 0) {
                fprintf(__iob + 0x20, "-showm: Unidentified: segment %d\n", sp74);
            }
            if ((sp44 != 0) || (sp70 == 0)) {
                fprintf(__iob + 0x20, "pr_vaddr[%d]= %lx\n", sp74, B_1000CAC0[sp74].pr_vaddr);
                fprintf(__iob + 0x20, "pr_size[%d]= %lx\n", sp74, B_1000CAC0[sp74].pr_size);
                fprintf(__iob + 0x20, "pr_off[%d]= %lx\n", sp74, B_1000CAC0[sp74].pr_off);
                fprintf(__iob + 0x20, "pr_mflags[%d]= %lx\n", sp74, B_1000CAC0[sp74].pr_mflags);
                fprintf(__iob + 0x20, "pr_vsize[%d]= %lx\n", sp74, B_1000CAC0[sp74].pr_vsize);
                fprintf(__iob + 0x20, "pr_psize[%d]= %lx\n", sp74, B_1000CAC0[sp74].pr_psize);
                fprintf(__iob + 0x20, "pr_wsize[%d]= %lx\n", sp74, B_1000CAC0[sp74].pr_wsize);
                fprintf(__iob + 0x20, "pr_rsize[%d]= %lx\n", sp74, B_1000CAC0[sp74].pr_rsize);
                fprintf(__iob + 0x20, "pr_msize[%d]= %lx\n", sp74, B_1000CAC0[sp74].pr_msize);
                fprintf(__iob + 0x20, "pr_dev[%d]= %lx\n", sp74, B_1000CAC0[sp74].pr_dev);
                fprintf(__iob + 0x20, "pr_ino[%d]= %lx\n", sp74, B_1000CAC0[sp74].pr_ino);
                fprintf(__iob + 0x20, "\n");
            }
            temp_t1 = sp74 + 1;
            sp74 = temp_t1;
        } while (temp_t1 < count);
    }
    fprintf(__iob + 0x20, "%s phase mem: %dT %dD %dB %dS %dt %dd %db %dm= %dK\n", arg0, sp64 >> 0xA, sp60 >> 0xA, sp5C >> 0xA, sp58 >> 0xA, sp54 >> 0xA, sp50 >> 0xA, sp4C >> 0xA, sp48 >> 0xA, (u32) (sp64 + sp60 + sp5C + sp58 + sp54 + sp50 + sp4C + sp48) >> 0xA);
    if (sp44 != 0) {
        fprintf(__iob + 0x20, "text_size= %d Kbytes\n", sp64 >> 0xA);
        fprintf(__iob + 0x20, "data_size= %d Kbytes\n", sp60 >> 0xA);
        fprintf(__iob + 0x20, "brk_size= %d Kbytes\n", sp5C >> 0xA);
        fprintf(__iob + 0x20, "stack_size= %d Kbytes\n", sp58 >> 0xA);
        fprintf(__iob + 0x20, "so_text_size= %d Kbytes\n", sp54 >> 0xA);
        fprintf(__iob + 0x20, "so_data_size= %d Kbytes\n", sp50 >> 0xA);
        fprintf(__iob + 0x20, "so_brk_size= %d Kbytes\n", sp4C >> 0xA);
        fprintf(__iob + 0x20, "mmap_size= %d Kbytes\n", sp48 >> 0xA);
        fprintf(__iob + 0x20, "TOTAL_SIZE= %d Kbytes\n", (u32) (sp64 + sp60 + sp5C + sp58 + sp54 + sp50 + sp4C + sp48) >> 0xA);
    }
}

s8* func_00433534(s8* arg0) {
    s8* sp24;
    s8* temp_v0;

    temp_v0 = malloc(strlen(arg0) + 3);
    sp24 = temp_v0;
    sp24->unk_0 = 0x2D;
    sp24->unk_1 = 0x2D;
    sp24->unk_2 = 0;
    strcat(sp24, arg0);
    return temp_v0;
}

s32 gethostsex(void) {
    s32 sp4;
    s32 var_v0;

    sp4 = 1;
    var_v0 = 0;
    if ((s8) sp4 == 1) {
        var_v0 = 1;
    }
    return var_v0;
}
