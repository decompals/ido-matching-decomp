/* Handwritten */

// function __start # 0
#pragma GLOBAL_ASM("asm/7.1/functions/cc/__start.s")

// function _mcount # 1
#pragma GLOBAL_ASM("asm/7.1/functions/cc/_mcount.s")

#include "signal.h"
#include "wait.h"
#include "cc.h"
#include "sex.h"
#include "sys/times.h"
#include "utime.h"
#include "varargs.h"
#include "errno.h"
#include "unistd.h"
#include "ctype.h"
#include "sys/stat.h"
#include "sys/fcntl.h"

/* File, -O1 */
typedef struct {
    int capacity;
    int length;
    char** entries;
} list;

extern int getpagesize(void);

void parse_command(int argc, char** argv);
void newrunlib(void);
char getsuf(const char* path);
char* mksuf(const char* path, char value);
char* full_path(const char* relative_path);
void add_static_opt(char* opt);
void compose_G0_libs(const char* arg0);
void relocate_passes(const char* arg0, const char* arg1, const char* arg2);

static char* func_0042FD7C(const char* name, char** dirs);
static void func_00432C94(void);

#ifndef PERMUTER
void error();
#else
void error(int arg0, const char* arg1, int arg2, const char* arg3, int arg4, const char* arg5, ...);
#endif /* PERMUTER */

char* mkstr();
void addstr(list* arg0, char* str);
char* savestr(const char* src, size_t extra_length);

static const char* func_00430414(char* arg0, int arg1);
static void func_00431B38(int first, int count);
static int func_00432940(pid_t arg0);
static void func_00432BDC();
static void func_00432D3C(const char* arg0, int count);

void get_lino(char* arg0, const char* arg1, int arg2);
void settimes(void);
void dotime(const char* programName);
void cleanup(void);

typedef int UNK_TYPE;

// bss
static prmap_sgi_t B_1000CAC0[100];
char perr_msg[0x100];
static int B_1000E4C0;
static char** B_1000E4C4;
int plain_g;
int plain_O;
int noaliasokflag;
int haspl1;
UNK_TYPE p2cstr;
int align;
int align_common;
char* alignarg;
int use_real_fp;
int dollar_sign;
int default_template_instantiation_mode;
int mp_flag;
int mp_onetripflag;
UNK_TYPE mp_staticflag;
int mp_dlinesflag;
int mp_caseflag;
UNK_TYPE efl;
int mp_66flag;
char* ratfor;
int mp_i2flag;
char* m4;
int mp_col120flag;
int mp_extendflag;
int mp_uflag;
int mp_backslashflag;
UNK_TYPE mp_uniq_specified;
UNK_TYPE mp_passes_relocated;
int cmp_flag;
int fullwarn;
char* aligndir;
int docpp;
int default_nocpp;
u32 j; // ?
char* tstring;
char* hstring;
char* Bstring;
const char* allBstring;
static UNK_TYPE B_1000E55C; // Unused
char alltstring[20];
char* Warg;
char* Wpass;
char* Kpass;
char Karg;
char Hchar;
static char B_1000E587; // Unused
int time0;
static UNK_TYPE B_1000E58C; // Unused
struct tms tm0;
int retcode;
char* outfile;
char* passin;
char* passout;
char* errout;
char* symtab;
char* uopt0str;
char* ddoptstr;
char* optstr;
char* gentmp;
char* binasm;
char* uoutfile;
char* lpi_st;
char* lpi_p1;
char* lpi_dd;
static UNK_TYPE B_1000E5DC;
static char B_1000E5E0[0x400];
char* lpi_pd;
char* linkorder;
static UNK_TYPE valuesstr;
static UNK_TYPE tmp_elfobj;
char* CRTX;
FILE* ldw_file;
char* MCRTX;
FILE* tmpsfile;
list undefineflags;
char* editor;
list cppflags;
int xserver;
list olimitflags;
int times_edited;
list acppflags;
int edit_cnt_max;
list mpcflags;
static UNK_TYPE B_1000EA4C; // Unused
list accomflags;
char srcsuf;
static UNK_TYPE B_1000EA5D; // Unused
list cfeflags;
int tmpst;
list cpp2flags;
static UNK_TYPE B_1000EA7C; // Unused
list uldlibflags;
static UNK_TYPE B_1000EA8C; // Unused
list edisonflags;
char* comp_target_root;
list prelinkerflags;
char* comp_host_root;
list ccomflags;
char* systype;
list upasflags;
int nonshared;
list fcomflags;
static UNK_TYPE B_1000EADC; // Unused
list eflflags;
static UNK_TYPE B_1000EAEC; // Unused
list ratforflags;
static UNK_TYPE B_1000EAFC; // Unused
list upl1flags;
static UNK_TYPE B_1000EB0C; // Unused
list ucobflags;
static UNK_TYPE B_1000EB1C; // Unused
list ulpiflags;
static UNK_TYPE B_1000EB2C; // Unused
list ujoinflags;
char* tmpdir;
list uldflags;
char* rls_id_object;
list usplitflags;
char* progname;
list umergeflags;
char* currcomp;
list uloopflags;
static UNK_TYPE B_1000EB7C; // Unused
char* compdirs[7];          // might also be a struct?
static UNK_TYPE B_1000EB9C; // Unused
list uopt0flags;
int compiler;
list ddoptflags;
static UNK_TYPE B_1000EBBC; // Unused
char* tempstr[34];
list optflags;
static UNK_TYPE B_1000EC54; // Unused
list genflags;
static UNK_TYPE B_1000EC64; // Unused
list asflags;
static UNK_TYPE B_1000EC74; // Unused
list as1flags;
static UNK_TYPE B_1000EC84; // Unused
list ldflags;
static UNK_TYPE B_1000EC94; // Unused
static int B_1000EC98[2];
list nldflags;
static UNK_TYPE B_1000ECAC; // Unused
list ftocflags;
static UNK_TYPE B_1000ECBC; // Unused
list cordflags;
static char* B_1000ECCC;
list srcfiles;
static char* B_1000ECDC;
list ufiles;
static UNK_TYPE B_1000ECEC; // Unused
list objfiles;
static UNK_TYPE B_1000ECFC; // Unused
list feedlist;
static UNK_TYPE B_1000ED0C; // Unused
list execlist;
static UNK_TYPE B_1000ED1C; // Unused
list dashlfiles;
static int B_1000ED2C;
static int B_1000ED30;
list dirs_for_crtn;
static UNK_TYPE B_1000ED44; // Unused
list dirs_for_nonshared_crtn;
static UNK_TYPE B_1000ED54; // Unused
list dirs_for_abi_crtn;
static UNK_TYPE B_1000ED64; // Unused
list ldZflags;
static int B_1000ED74;
list pfaflags;
char* pfa;
char* libI77_mp;
static UNK_TYPE B_1000ED8C; // Unused
list pcaflags;
static UNK_TYPE B_1000ED9C; // Unused
list soptflags;
static UNK_TYPE B_1000EDAC; // Unused
list staticopts;
static UNK_TYPE B_1000EDBC; // Unused
char** __Argv;
UNK_TYPE __rld_obj_head;
int __Argc; // Unused

// data

// data
char* LD = "ld";
int ansichoice = 3;
int c_compiler_choice = 0;

struct _struct_suffixes_0x8 {
    /* 0x0 */ const char* unk0;
    /* 0x4 */ int unk4;
}; // size = 0x8

struct _struct_suffixes_0x8 suffixes[0xF] = {
    { "pl1", 1 }, { "pli", 1 }, { "cob", 2 }, { "il", 3 },  { "st", 4 },  { "anl", 5 }, { "c++", 6 }, { "cc", 6 },
    { "cxx", 6 }, { "C", 6 },   { "cpp", 6 }, { "CXX", 6 }, { "CPP", 6 }, { ".c", 7 },  { NULL, 0 },
};

char* include = NULL;
char* includeB = NULL;
char* einclude = NULL;
char* eincludeB = NULL;
char* cpp = NULL;
char* ccom = NULL;
char* mpc = NULL;
char* cfe = NULL;
char* upas = NULL;
char* fcom = NULL;
char* upl1 = NULL;
char* pl1err = NULL;
char* ulpi = NULL;
char* ucob = NULL;
char* ujoin = NULL;
char* usplit = NULL;
char* uld = NULL;
char* umerge = NULL;
char* uloop = NULL;
char* uopt0 = NULL;
char* ddopt = NULL;
char* opt = NULL;
char* gen = NULL;
char* as0 = NULL;
char* as1 = NULL;
char* ld = NULL;
char* ftoc = NULL;
char* cord = NULL;
char* btou = NULL;
char* utob = NULL;
char* strip = NULL;
char* patch = NULL;
char* filter = NULL;
char* prelinker = NULL;
int smart_build = 0;
char* sbrepos = NULL;
int do_strip = 0;
int no_prelink = 0;
int nofilt = 0;
int force_prelink = 0;
int verbose_prelink = 0;
int auto_template_include = 1;
int nocode = 0;
int nocompileneeded = 0;
char* LibM = " -lm";
char* LibP = " -lp";
char* LibF77 = " -lF77";
char* LibI77 = " -lI77";
char* LibU77 = " -lU77";
char* LibIsam = " -lisam";
char* LibExc = " -lexc";
char* LibDw = " -ldw";
char* LibPl1 = NULL;
char* LibCob = NULL;
char* LibSort = NULL;
char* LibProf1 = " -lprof";
char* LibGProf1 = " -lgprof";
char* LibXmalloc = " -lxmalloc";
char* LibMld = " -lmld";
char* crtx = NULL;
char* crtn = NULL;
char* cxx_init = NULL;
char* delta_init = NULL;
char* libp = NULL;
char* libp_b = NULL;
char* libm = NULL;
char* libm_b = NULL;
char* libF77 = NULL;
char* libF77_b = NULL;
char* libI77 = NULL;
char* libI77_b = NULL;
char* libU77 = NULL;
char* libftn = NULL;
char* libU77_b = NULL;
char* libisam = NULL;
char* libisam_b = NULL;
char* libdw_path = NULL;
char* libdw = NULL;
char* libdw_b = NULL;
char* libpl1 = NULL;
char* libpl1_b = NULL;
char* libexc = NULL;
char* libexc_b = NULL;
char* libcob = NULL;
char* libcob_b = NULL; // Unused
char* libsort = NULL;
char* libsort_b = NULL;
char* libprof = NULL;
char* libgprof = NULL;
char* libxmalloc = NULL;
char* libxmalloc_b = NULL;
char* cpp_stdflag = NULL;
char* libmld = NULL;
char* xpg_env = NULL;
int xpg_flag = 0;
int crtn_required = 1;
char* pca = NULL;
char* libc_mp = NULL;
char* fopt = NULL;
char* copt = NULL;
static int D_1000BF74 = 0;
static int D_1000BF78 = 0;
static int D_1000BF7C = 1;
static char* D_1000BF80 = NULL;
static char* D_1000BF84 = NULL;
static int D_1000BF88 = 0;
static int D_1000BF8C = 1;
static int D_1000BF90 = 0;
static int D_1000BF94 = 0;

int Eflag = 0;
int Pflag = 0;
int gflag = 0;
int pflag = 0;
int pgflag = 0;
int jflag = 0;
int cflag = 0;
int Sflag = 0;
int Oflag = 1;
int vflag = 0;
int time_flag = 0;
int execute_flag = 1;
int Vflag = 0;
int Kflag = 0;
int nodeflib = 0;
int minus_M = 0;
int anachronisms = 1;
int disable_inlines = 0;
int cfront_compatible = 1;
int make_edison_shlib = 0;
int plusIflag = 0;
int signedcharflag = 0;
int Lflag = 0;
int set_loop_unroll = 0;
int mflag = 0;
int Fflag = 0;
int stdflag = 0;
int cplusflag = 0;
int ucodeflag = 0;
int Bflag = 0;
int fiveflag = 0;
int automaticflag = 1;
int emptyIflag = 0;
int cordflag = 0;
int ansiflag = 0;
int lpilockflag = 0;
int nolockflag = 0;
int unrollflag = 0;
int libm_spec = 0;
int libfastm_spec = 0;
int editflag = 0;
int oldccomflag = 0;
int oldcflag = 0;
int oldcppflag = 0;
int fflag = 0; // Unused
int tpflag = 0;
int ddoptflag = 0;
int uopt0flag = 0;
int protoflag = 0; // Unused
int kminabiflag = 0;
int kpicopt_flag = 0;
int nokpicopt_flag = 0;
int elfflag = 1;
int coff_spec = 0;
int elf_spec = 0;
int compose_first_G0 = 0;
int mips2_spec_flag = 0;
int mips1flag = 0;
int mips2flag = 1;
int mips3flag = 0;
int ignore_unresolved_flag = 0;
int no_unresolved_flag = 0;
int swopcodeflag = 0;
int dwopcodeflag = 0;
int sixty4bit_spec = 0;
int sixty4bitflag = 0;
int thirty2bitflag = 0;
int fullasoptflag = 0;
int old_non_shared = 0;
int non_shared_emitted = 0;
int longlong_emitted = 0;
int non_shared = 0;
int Gseen_flag = 0;
int transitive_link = 0;
int full_transitive_link = 0;
int no_transitive_link = 0;
int quickstart_info = 0;
int force_rm_dead_code = 0;
int kpic_flag = 1;
int kpic_spec = 0;
int call_shared = 0;
int excpt_flag = 0;
int trapuv_flag = 0;
int dmips_emit = 0;
int Xvalues_Flag = 0; // Unused
int user_systype = 0;
int ddoptinfo = 0;
int systype_seen = 0;
int multiple_systype = 0;
int systype_warn = 0;
int svr4_systype = 0;
int c_inline = 0;
int tfp_flag = 0;
int abi_flag = 0;
int NoMoreOptions = 0;
int memory_flag = 0;
int default_call_shared = 1;
int haspascal = 0;
int hasfortran = 0;
int lmflag = 0;
int srcexists = 0;
int w1flag = 1;
static int D_1000C130 = 0;
int prototype_checking_on = 0;
int showdirt_flag = 0;
int mp_prepass_count = 0;

// not sure about this struct
typedef struct {
    const char* unk_0;
    u32 unk_4;
} struct_mpflags;

struct_mpflags mpflags[] = {
    { "list", 0x00010003 },
    { "keep", 0x00010007 },
    { 0 },
};
struct_mpflags cmpflags[] = {
    { "list", 0x00010003 },
    { "keep", 0x00010007 },
    { 0 },
};

int acpp = 0;
int mips_abi = 1;
int compchoice = 0;
int cppchoice = 0;
int acpp_traditional = 0;
int G_flag = 0;
int dn_flag = 0;
int edison_cpp = 1;
char* edison_type = (char*)1;
int exception_handling = 0;
char* Gnum = "0";
int runerror = 0;
int uload = 0;
int uldobj_place = -1;
char* tmp_uldobj = NULL;
int chip_targ = -1;
int nobjs = 0;
int targetsex = BIGENDIAN;
int default_svr4 = 0;
int irix4 = 0;
char* runlib = "/";
char* runlib_base = "/";
static prmap_sgi_arg_t D_1000C1C8 = { (caddr_t)B_1000CAC0, 0x1900 };
static char* D_1000C1D0 = NULL; // full path of current working directory
int run_sopt = 0;
static char* D_1000C1D8 = NULL;
static char* D_1000C1DC = NULL;

// function main # 2
#pragma GLOBAL_ASM("asm/7.1/functions/cc/main.s")

// function process_config # 3
void process_config(int argc, char** argv) {
    register int i;
    register char* var_s1;
    char* sp1144 = comp_target_root;
    char* sp1140;
    FILE* sp113C;
    char sp13C[0x1000];
    s32 sp138;
    char* sp38[0x40];

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-systype") == 0) {
            i++;
            if (i >= argc) {
                error(1, NULL, 0, NULL, 0, "-systype must have an argument\n");
                exit(2);
            }

            user_systype = 1;
            systype = argv[i];
            if (strcmp(systype, "svr4") == 0) {
                svr4_systype = 1;
            } else {
                error(1, NULL, 0, NULL, 0, "only systype svr4 allowed\n");
                exit(2);
            }

            // clang-format off
            if ((strcmp(systype, "svr4") != 0) 
                && (strcmp(systype, "bsd43") != 0) 
                && (strcmp(systype, "svr3") != 0) 
                && (strcmp(systype, "sysv") != 0) 
                && (fopen(strcat("/", systype), "r") == NULL) 
                && (systype_warn == 0)) {
                // clang-format on
                error(2, NULL, 0, NULL, 0, "This systype doesn't exist on this machine; changed systype to svr3.\n");
                systype_warn = 1;
                systype = "svr3";
            }

            if (svr4_systype == 0) {
                sp1144 = mkstr(comp_target_root, systype, "/", NULL);
            }
            break;
        }
    }

    if (user_systype == 0) {
        sp1144 = mkstr(comp_target_root, systype, "/", NULL);
    }

    user_systype = 0;
    sp1140 = mkstr(sp1144, "usr/lib/", currcomp, "comp.config", NULL);
    sp113C = fopen(sp1140, "r");
    if (sp113C != NULL) {
        if (1) {} // FAKE
        if (fgets(sp13C, 0x1000, sp113C) != NULL) {
            if (sp13C[strlen(sp13C) - 1] == '\n') {
                sp13C[strlen(sp13C) - 1] = '\0';
            }
            var_s1 = sp13C;
            i = sp138 = 0;
            while (*var_s1 != 0) {
                while ((*var_s1 != '\0') && ((*var_s1 == ' ') || (*var_s1 == '\t'))) {
                    var_s1++;
                }

                if (*var_s1 != 0) {
                    sp38[sp138] = var_s1;
                    sp138 += 1;
                }

                while ((*var_s1 != '\0') && (*var_s1 != ' ') && (*var_s1 != '\t')) {
                    var_s1++;
                }

                if (*var_s1 != 0) {
                    *var_s1++ = '\0';
                }
            }
            parse_command(sp138, sp38);
        }
    }
}

// function add_info # 4
void add_info(char* str) {
    addstr(&upasflags, str);
    addstr(&fcomflags, str);
    addstr(&ulpiflags, str);
    addstr(&uopt0flags, str);
    addstr(&ddoptflags, str);
    addstr(&optflags, str);
    addstr(&umergeflags, str);
    addstr(&uloopflags, str);
    addstr(&genflags, str);
    addstr(&asflags, str);
    addstr(&ldflags, str);
}

// function parse_command # 5
void parse_command(int argc, char** argv) {
    register int var_s0;
    register char var_s1;
    register char* var_s2;
    register char* var_s3;
    char* sp15C;
    char* sp158;
    char* sp154;
    char sp153;
    int sp14C;
    char* sp148;
    char* sp144;
    char* sp140;
    int pad[2];
    char* sp134;
    char* sp130;
    char* sp12C;
    char* sp128;
    char* sp124;
    char* sp120;
    char* sp11C;
    char* sp118;
    int sp114;
    char* sp110;
    char* sp10C;
    int sp108;
    char* sp104;
    char* sp100;
    char* spFC;
    struct stat sp74;
    struct_mpflags* sp70;
    struct_mpflags* sp6C;
    char* sp68;
    char* sp64;
    int sp60;
    int sp5C;
    char* sp58;
    int sp54;

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
    for (var_s0 = 0; var_s0 < argc; var_s0++) {
        if ((argv[var_s0][0] == 0x2D) && ((NoMoreOptions == 0) || (strchr(argv[var_s0], 0x2EU) == NULL))) {
            // temp_t7 = (argv[var_s0])->unk_1;
            switch (argv[var_s0][1]) { /* switch 1 */
                case 0x23:             /* switch 1 */
                    error(2, NULL, 0, NULL, 0, "-# is not supported. Use -v to see compiler passesn");
                    break;
                case 0x31: /* switch 1 */
                    if ((compiler == 3) && (argv[var_s0][2] == 0)) {
                        mp_onetripflag = 1;
                        addstr(&fcomflags, argv[var_s0]);
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x33: /* switch 1 */
                    if ((strcmp(argv[var_s0], "-32bit") == 0) || (strcmp(argv[var_s0], "-32") == 0)) {
                        thirty2bitflag = 1;
                        mips_abi = 1;
                    }
                    break;
                case 0x35: /* switch 1 */
                    error(2, NULL, 0, NULL, 0, "-5 not supported\n");
                    if (argv[var_s0][2] == 0) {
                        if (Bflag != 0) {
                            if (fiveflag == 0) {
                                error(1, NULL, 0, NULL, 0, "-5 must precede any -B flags\n");
                                exit(2);
                            }
                            break;
                        } else {
                            fiveflag++;
                            include = mkstr(comp_target_root, "usr/5include", NULL);
                            if (Bstring != NULL) {
                                relocate_passes("h", NULL, Bstring);
                            }
                            newrunlib();
                        }
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x36: /* switch 1 */
                    if ((compiler == 3) && (strcmp(argv[var_s0], "-66") == 0)) {
                        addstr(&fcomflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-64bit") == 0) {
                        error(2, NULL, 0, NULL, 0,
                              "-64bit option is not yet implemented for ucode compilers, ignore\n");
                        sixty4bit_spec = 1;
                        if (swopcodeflag != 0) {
                            error(1, NULL, 0, NULL, 0, "-64bit can not be used with -swopcode for ucode compilers\n");
                            exit(2);
                        }
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x41: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        var_s0++;
                        if (var_s0 < argc) {
                            addstr(&objfiles, "-A");
                            addstr(&objfiles, argv[var_s0]);
                            break;
                        } else {
                            error(1, NULL, 0, NULL, 0, "ld requires -A to have an argument\n");
                            exit(2);
                        }
                    }
                    if (strcmp(argv[var_s0], "-AutoGnum") == 0) {
                        addstr(&uldflags, argv[var_s0]);
                        if (strcmp(Gnum, "0") != 0) {
                            Gnum = "0";
                        }
                    } else if (argv[var_s0][1] == 0x41) {
                        addstr(&cppflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-A-") == 0) {
                        addstr(&cppflags, argv[var_s0]);
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x42: /* switch 1 */
                    if ((argv[var_s0][2] == 0) && (var_s0 < (argc - 1)) &&
                        ((strcmp(argv[var_s0 + 1], "static") == 0) || (strcmp(argv[var_s0 + 1], "dynamic") == 0) ||
                         (strcmp(argv[var_s0 + 1], "symbolic") == 0))) {
                        addstr(&objfiles, argv[var_s0]);
                        var_s0++;
                        addstr(&objfiles, argv[var_s0]);
                    } else {
                        Bflag = 1;
                        sp144 = argv[var_s0] + 2;
                        relocate_passes(tstring, hstring, sp144);
                        if (tstring == NULL) {
                            Bstring = sp144;
                        }
                    }
                    break;
                case 0x43: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        if (compiler == 3) {
                            addstr(&fcomflags, argv[var_s0]);
                            break;
                        } else if (compiler == 2) {
                            addstr(&upasflags, argv[var_s0]);
                            break;
                        } else if (compiler == 1) {
                            addstr(&cppflags, argv[var_s0]);
                            break;
                        }
                    }
                    if (strncmp(argv[var_s0], "-CG_EMIT:", 5U) == 0) {
                        error(2, NULL, 0, NULL, 0, "-CG_EMIT options are ignored\n");
                    } else {
                        goto bad_option;
                    }

                    break;
                case 0x44: /* switch 1 */
                    if (strncmp(argv[var_s0], "-DEFAULT:",
                                strlen("-DEFAULT:\0-D taken as empty cpp -D, not ld(1) -D hexnum\n\0-D\0ld requires -D "
                                       "to have an argument\n")) != 0) {
                        if (argv[var_s0][2] == 0) {
                            if ((var_s0 + 1) < argc) {
                                if (1) {} // FAKE
                                // if (1) {}
                                sp140 = malloc(strlen(argv[var_s0 + 1]) + 3);
                                sp140[0] = 0x2D;
                                sp140[1] = 0x44;
                                sp140[2] = 0;
                                addstr(&undefineflags, strcat(sp140, argv[var_s0 + 1]));
                                add_static_opt(mkstr(argv[var_s0], argv[var_s0 + 1], NULL));
                            }
                            var_s0++;
                        } else {
                            addstr(&undefineflags, argv[var_s0]);
                            add_static_opt(argv[var_s0]);
                        }
                    }
                    break;
                case 0x45: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        Eflag++;
                        docpp = 1;
                    } else if ((argv[var_s0][3] == 0) && ((argv[var_s0][2] == 0x42) || (argv[var_s0][2] == 0x4C))) {
                        if (argv[var_s0][2] == 0x42) {
                            if ((Bflag != 0) && (targetsex != 0)) {
                                error(1, NULL, 0, NULL, 0,
                                      "-EB or -EL must precede any -B flags for ucode compilers\n");
                                exit(2);
                            }
                            targetsex = 0;
                        } else {
                            if ((Bflag != 0) && (targetsex != 1)) {
                                error(1, NULL, 0, NULL, 0,
                                      "-EB or -EL must precede any -B flags for ucode compilers\n");
                                exit(2);
                            }
                            targetsex = 1;
                        }
                        newrunlib();
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x46: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        if (compiler == 3) {
                            Fflag++;
                        } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                            cflag = 1;
                            Fflag = 1;
                            default_template_instantiation_mode = 1;
                        } else {
                            addstr(&ldflags, argv[var_s0]);
                        }
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x47: /* switch 1 */
                    if (strncmp(argv[var_s0], "-GCM:", 5U) == 0) {
                        error(2, NULL, 0, NULL, 0, "-GCM options are ignored\n");
                        break;
                    }
                    if (argv[var_s0][2] == 0) {
                        if (default_svr4 != 0) {
                            if (dn_flag != 0) {
                                error(1, NULL, 0, NULL, 0, "-G can not be used with -dn \n");
                                exit(2);
                            }
                            G_flag = 1;
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        }
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(1, NULL, 0, NULL, 0, "-G requires a decimal number argument\n");
                            exit(2);
                        }
                        if (Oflag < 3) {
                            Gnum = argv[var_s0];
                        } else {
                            Gnum = "0";
                        }
                    } else {
                        if (default_svr4 != 0) {
                            break;
                        }
                        if (Oflag < 3) {
                            Gnum = argv[var_s0] + 2;
                        } else {
                            Gnum = "0";
                        }
                    }
                    for (var_s2 = Gnum; *var_s2 != '\0'; var_s2++) {
                        if (!(__ctype[1 + *var_s2] & 4)) {
                            error(1, NULL, 0, NULL, 0, "non-digit character in -G %s\n", Gnum);
                            exit(2);
                        }
                    }
                    if (Gseen_flag == 0) {
                        relocate_passes(tstring, hstring, NULL);
                        Gseen_flag = 1;
                    }

                    break;
                case 0x48: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        addstr(&cppflags, argv[var_s0]);
                        Eflag++;
                    } else if (argv[var_s0][3] == 0) {
                        if (1) {} // FAKE
                        // if (1) {}
                        Hchar = argv[var_s0][2];
                        for (var_s2 = "fKMdkjusmocab"; (*var_s2 != 0 && *var_s2 != Hchar); var_s2++) {}

                        if (*var_s2 == 0) {
                            error(1, NULL, 0, NULL, 0, "Unknown character in %s\n", argv[var_s0]);
                            exit(2);
                        }
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x49: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        if (((argv[var_s0 + 1] != 0) && (*argv[var_s0 + 1] == 0x2D)) ||
                            (isdir(argv[var_s0 + 1]) == 0)) {
                            emptyIflag++;
                        } else {
                            var_s0++;
                            sp134 = mkstr("-I", argv[var_s0], NULL);
                            addstr(&cppflags, sp134);
                            addstr(&cpp2flags, sp134);
                            add_static_opt(mkstr("-I", full_path(argv[var_s0]), NULL));
                        }
                    } else {
                        addstr(&cppflags, argv[var_s0]);
                        addstr(&cpp2flags, argv[var_s0]);
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(mkstr("-I", full_path(argv[var_s0] + 2), NULL));
                    }
                    break;
                case 0x4A: /* switch 1 */
                    if (strcmp(argv[var_s0], "-Jsfm") != 0) {
                        if (strcmp(argv[var_s0], "-J") == 0) {
                            sp12C = argv[var_s0 + 1];
                            for (sp130 = sp12C; *sp130 != 0; sp130++) {
                                if (!(__ctype[1 + *sp130] & 4)) {
                                    error(1, NULL, 0, NULL, 0, "non-digit character in -J %s\n", sp12C);
                                    exit(2);
                                }
                            }
                            addstr(&prelinkerflags, argv[var_s0]);
                            addstr(&prelinkerflags, sp12C);
                            var_s0++;
                        } else {
                            case 0x4B: /* switch 1 */
                                if (default_svr4 != 0) {
                                    Kpass = argv[var_s0] + 2;
                                    if (*Kpass == 0) {
                                        Kpass = argv[var_s0] + 3;
                                    }

                                    while ((*Kpass != 0) || (*Kpass == 0x2C)) {
                                        for (j = 0, var_s2 = Kpass; (*var_s2 != 0x2C && *var_s2 != 0); j++) {
                                            (&Karg)[j] = *var_s2++;
                                        }

                                        Kpass = var_s2;
                                        if (strncmp(&Karg, "minabi", 6U) == 0) {
                                            kminabiflag = 1;
                                        } else if (strncmp(&Karg, "fpe", 3U) == 0) {
                                            addstr(&ldflags, "-Kfpe");
                                        } else if (strncmp(&Karg, "sd", 2U) == 0) {
                                            addstr(&ldflags, "-Ksd");
                                        } else if (strncmp(&Karg, "sz", 2U) == 0) {
                                            addstr(&ldflags, "-Ksz");
                                        } else if (strncmp(&Karg, "mau", 3U) == 0) {
                                            addstr(&ldflags, "-Kmau");
                                        } else if (strncmp(&Karg, "PIC", 3U) == 0) {
                                            if (non_shared != 0) {
                                                error(2, NULL, 0, NULL, 0,
                                                      "Can't mix -KPIC and -non_shared, change to -non_shared\n");
                                                kpic_flag = 0;
                                            } else {
                                                kpic_flag = 1;
                                                kpic_spec = 1;
                                            }
                                        } else {
                                            goto bad_option;
                                        }
                                        for (j = 0; j < strlen(&Karg); j++) {
                                            (&Karg)[j] = 0x20;
                                        }

                                        while ((Kpass != NULL) && (*Kpass == 0x2C) && (*Kpass != 0)) {
                                            Kpass++;
                                        }
                                    }
                                } else if (svr4_systype != 0) {
                                    Kpass = argv[var_s0] + 2;
                                    if (*Kpass == 0) {
                                        Kflag++;
                                        addstr(&fcomflags, argv[var_s0]);
                                    }
                                    while ((*Kpass != 0) || (*Kpass == 0x2C)) {
                                        for (j = 0, var_s2 = Kpass; (*var_s2 != 0x2C && *var_s2 != 0); j++) {
                                            (&Karg)[j] = *var_s2++;
                                        }
                                        Kpass = var_s2;
                                        if (strncmp(&Karg, "minabi", 6U) == 0) {
                                            kminabiflag = 1;
                                        } else if (strncmp(&Karg, "fpe", 3U) == 0) {
                                            addstr(&ldflags, "-Kfpe");
                                        } else if (strncmp(&Karg, "sd", 2U) == 0) {
                                            addstr(&ldflags, "-Ksd");
                                        } else if (strncmp(&Karg, "sz", 2U) == 0) {
                                            addstr(&ldflags, "-Ksz");
                                        } else if (strncmp(&Karg, "mau", 3U) == 0) {
                                            addstr(&ldflags, "-Kmau");
                                        } else if (strncmp(&Karg, "PIC", 3U) == 0) {
                                            if (non_shared != 0) {
                                                error(2, NULL, 0, NULL, 0,
                                                      "Can't mix -KPIC and -non_shared, change to -non_shared\n");
                                                kpic_flag = 0;
                                            } else {
                                                kpic_flag = 1;
                                                kpic_spec = 1;
                                            }
                                        } else {
                                            goto bad_option;
                                        }
                                        for (j = 0; j < strlen(&Karg); j++) {
                                            (&Karg)[j] = 0x20;
                                        }

                                        while ((Kpass != NULL) && (*Kpass == 0x2C) && (*Kpass != 0)) {
                                            Kpass++;
                                        }
                                    }
                                } else if (argv[var_s0][2] != 0) {
                                    if (strcmp(argv[var_s0], "-KPIC") == 0) {
                                        if (non_shared != 0) {
                                            error(2, NULL, 0, NULL, 0,
                                                  "Can't mix -KPIC and -non_shared, change to -non_shared\n");
                                            kpic_flag = 0;
                                            break;
                                        } else {
                                            kpic_flag = 1;
                                            kpic_spec = 1;
                                        }
                                    } else {
                                        addstr(&ldflags, argv[var_s0]);
                                    }
                                } else {
                                    Kflag++;
                                    addstr(&fcomflags, argv[var_s0]);
                                }
                        }
                    }
                    break;
                case 0x4C: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        if (((var_s0 + 1) < argc) && (argv[var_s0 + 1][0] != 0x2D) && (isdir(argv[var_s0 + 1]) != 0)) {
                            var_s0++;
                            sp128 = mkstr(argv[var_s0 - 1], argv[var_s0], NULL);
                            addstr(&ldflags, sp128);
                            addstr(&prelinkerflags, sp128);
                            Lflag = 1;
                            break;
                        } else {
                            addstr(&prelinkerflags, mkstr("-YB", NULL));
                        }
                    }

                    Lflag = 1;
                    addstr(&ldflags, argv[var_s0]);
                    addstr(&prelinkerflags, argv[var_s0]);

                    break;
                case 0x4D: /* switch 1 */
                    if (argv[var_s0][2] == 0x44) {
                        if (strcmp(argv[var_s0] + 3, "update") == 0) {
                            sp15C = argv[var_s0 + 1];
                        } else if (strcmp(argv[var_s0] + 3, "ignore") == 0) {
                            addstr(&ldflags, argv[var_s0]);
                            addstr(&ldflags, argv[var_s0 + 1]);
                        } else if (strcmp(argv[var_s0] + 3, "ignoredir") == 0) {
                            addstr(&ldflags, argv[var_s0]);
                            addstr(&ldflags, argv[var_s0 + 1]);
                        } else if (strcmp(argv[var_s0] + 3, "target") == 0) {
                            if ((compiler == 1) && (c_compiler_choice != 0)) {
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
                            error(1, NULL, 0, NULL, 0, "%s must be followed by a file name\n", argv[var_s0 - 1]);
                            exit(2);
                        }
                        break;
                    } else if (argv[var_s0][2] == 0) {
                        if (1) {} // FAKE
                        addstr(&cppflags, argv[var_s0]);
                        Eflag++;
                        minus_M++;
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x4E: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        addstr(&ldflags, argv[var_s0]);
                    } else if (compiler == 3) {
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x4F: /* switch 1 */
                    plain_O = 0;
                    if (argv[var_s0][2] == 0) {
                        if ((xpg_flag != 0) && (var_s1 == 0x66)) {
                            fprintf(__iob + 2, "Error: optlevel should be specified\n");
                            exit(1);
                        }
                        Oflag = 2;
                        plain_O = 1;
                        if (plain_g != 0) {
                            Oflag = 1;
                        }
                        if (((var_s0 + 1) < argc) && (argv[var_s0 + 1][1] == 0) && (*argv[var_s0 + 1] >= 0x30) &&
                            (*argv[var_s0 + 1] < 0x35)) {
                            sp124 = malloc(strlen(argv[var_s0 + 1]) + 3);
                            sp124[0] = 0x2D;
                            sp124[1] = 0x4F;
                            sp124[2] = 0;
                            Oflag = *argv[var_s0 + 1] - 0x30;
                            addstr(&fcomflags, strcat(sp124, argv[var_s0 + 1]));
                            var_s0++;
                        }
                    } else if (argv[var_s0][3] == 0) {
                        if ((argv[var_s0][2] >= 0x30) && (argv[var_s0][2] < 0x35)) {
                            Oflag = argv[var_s0][2] - 0x30;
                            if (Oflag == 3) {
                                sp120 = "-Olimit";
                                sp11C = "5000";
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
                            if ((Oflag >= 3) && (jflag == 0)) {
                                uload = 1;
                            }
                            break;
                        } else {
                            goto bad_option;
                        }
                    } else if (strcmp(argv[var_s0], "-Olimit") == 0) {
                        addstr(&umergeflags, argv[var_s0]);
                        addstr(&optflags, argv[var_s0]);
                        addstr(&ddoptflags, argv[var_s0]);
                        addstr(&uopt0flags, argv[var_s0]);
                        addstr(&olimitflags, argv[var_s0]);
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(1, NULL, 0, NULL, 0, "-Olimit must have an argument\n");
                            exit(2);
                        }
                        for (var_s2 = argv[var_s0]; *var_s2 != 0; var_s2++) {
                            if (!(__ctype[*var_s2 + 1] & 4)) {
                                error(1, NULL, 0, NULL, 0, "non-digit character in -Olimit %s\n", argv[var_s0]);
                                exit(2);
                            }
                        }
                        addstr(&umergeflags, argv[var_s0]);
                        addstr(&optflags, argv[var_s0]);
                        addstr(&ddoptflags, argv[var_s0]);
                        addstr(&uopt0flags, argv[var_s0]);
                        addstr(&olimitflags, argv[var_s0]);
                    } else if (strncmp(argv[var_s0], "-OPT:", 5U) == 0) {
                        error(2, NULL, 0, NULL, 0, "-OPT options are ignored\n");
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x50: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        if (1) {} // FAKE
                        docpp = 1;
                        addstr(&cppflags, argv[var_s0]);
                        if (Eflag == 0) {
                            Pflag++;
                        }
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x51: /* switch 1 */
                    if ((strcmp(argv[var_s0], "-Qy") != 0) && (strcmp(argv[var_s0], "-Qn") != 0)) {
                        addstr(&cppflags, argv[var_s0]);
                    }
                    break;
                case 0x52: /* switch 1 */
                    if (compiler == 3) {
                        addstr(&ratforflags, argv[var_s0] + 2);
                        add_static_opt(argv[var_s0]);
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x53: /* switch 1 */
                    if (strncmp(argv[var_s0], "-SWP:", 5U) == 0) {
                        error(2, NULL, 0, NULL, 0, "-SWP options are ignored\n");
                    } else if (argv[var_s0][2] == 0) {
                        Sflag++;
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x54: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        var_s0++;
                        if (var_s0 < argc) {
                            addstr(&ldflags, "-T");
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        } else {
                            error(1, NULL, 0, NULL, 0, "ld requires -T to have an argument\n");
                            exit(2);
                        }
                    }
                    if (strncmp(argv[var_s0], "-TARG:", 6U) == 0) {
                        error(2, NULL, 0, NULL, 0, "-TARG options are ignored\n");
                    } else if (strncmp(argv[var_s0], "-TENV:", 6U) == 0) {
                        error(2, NULL, 0, NULL, 0, "-TENV options are ignored\n");
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x55: /* switch 1 */
                    if ((compiler == 3) && (argv[var_s0][2] == 0)) {
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                        mp_caseflag = 1;
                    } else if ((argv[var_s0][2] == 0) && ((var_s0 + 1) < argc)) {
                        sp118 = malloc(strlen(argv[var_s0 + 1]) + 3);
                        sp118[0] = 0x2D;
                        sp118[1] = 0x55;
                        sp118[2] = 0;
                        addstr(&undefineflags, strcat(sp118, argv[var_s0 + 1]));
                        var_s0++;
                    } else {
                        addstr(&undefineflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                    }
                    break;
                case 0x56: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        error(2, NULL, 0, NULL, 0, "-V is not supported.\n");
                    } else if (strcmp(argv[var_s0], "-VS") == 0) {
                        var_s0++;
                        if (var_s0 < argc) {
                            addstr(&ldflags, "-VS");
                            addstr(&ldflags, argv[var_s0]);
                        } else {
                            error(1, NULL, 0, NULL, 0, "ld requires -VS to have an argument\n");
                            exit(2);
                            goto bad_option;
                        }
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x57: /* switch 1 */
                    Wpass = argv[var_s0] + 2;
                    if (*Wpass != 0) {
                        if (1) {} // FAKE
                        Warg = argv[var_s0] + 3;

                        while (*Warg != 0x2C) {
                            if (*Warg++ == 0) {
                                goto bad_option;
                            }
                        }
                        while (*Warg == 0x2C) {
                            *Warg = 0;
                            Warg++;
                            for (var_s2 = Wpass; *var_s2 != 0; var_s2++) {
                                switch (*var_s2) { /* switch 2 */
                                    case 0x70:     /* switch 2 */
                                        addstr(&cppflags, Warg);
                                        break;
                                    case 0x4B: /* switch 2 */
                                        if (compiler == 3) {
                                            addstr(&pfaflags, Warg);
                                        } else if (compiler == 1) {
                                            addstr(&pcaflags, Warg);
                                        } else {
                                            error(1, NULL, 0, NULL, 0,
                                                  "-WK only valid in FORTRAN or C compilations.\n");
                                            exit(2);
                                        }
                                        break;
                                    case 0x30:              /* switch 2 */
                                    case 0x66:              /* switch 2 */
                                        switch (compiler) { /* switch 6; irregular */
                                            case 2:         /* switch 6 */
                                                addstr(&upasflags, Warg);
                                                break;
                                            case 3: /* switch 6 */
                                                addstr(&fcomflags, Warg);
                                                break;
                                            case 5: /* switch 6 */
                                                addstr(&upl1flags, Warg);
                                                break;
                                            case 6: /* switch 6 */
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
                                        // temp_t1_2 = Warg[1];
                                        switch (Warg[1]) { /* switch 3 */
                                            case 0x47:     /* switch 3 */
                                                if (Warg[2] == 0) {
                                                    var_s0++;
                                                    if (var_s0 >= argc) {
                                                        error(1, NULL, 0, NULL, 0,
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
                                                for (var_s3 = Gnum; ((*var_s3 != 0x2C) && (*var_s3 != 0));) {
                                                    if (!(__ctype[1 + *var_s3] & 4)) {
                                                        error(1, NULL, 0, NULL, 0, "non-digit character in -G %s\n",
                                                              Gnum);
                                                        exit(2);
                                                    }
                                                    if (*var_s3 != 0x2C) {
                                                        var_s3++;
                                                    }
                                                }
                                                if (Gseen_flag == 0) {
                                                    Gseen_flag = 1;
                                                    relocate_passes(tstring, hstring, NULL);
                                                }
                                                Warg = var_s3;
                                                break;
                                            case 0x76: /* switch 3 */
                                                // temp_t6_3 = Warg[2];
                                                if ((Warg[2] == 0) || (Warg[2] == 0x2C)) {
                                                    vflag = 1;
                                                    if (getenv("ROOTDIR") != NULL) {
                                                        error(2, NULL, 0, NULL, 0,
                                                              "ROOTDIR env var ignored, use COMP_TARGET_ROOT and "
                                                              "COMP_HOST_ROOT\n");
                                                    }
                                                }
                                                break;
                                            case 0x44: /* switch 3 */
                                                if (argv[var_s0][2] == 0) {
                                                    if ((var_s0 + 1) < argc) {
                                                        sp114 = strtoul(argv[var_s0 + 1], &sp110, 0x10);
                                                        if (((sp110 - argv[var_s0 + 1]) != strlen(argv[var_s0 + 1])) ||
                                                            ((sp114 == 0) && (sp110 == argv[var_s0 + 1])) ||
                                                            (*argv[var_s0 + 1] == 0x2D) ||
                                                            (*argv[var_s0 + 1] == 0x2B)) {
                                                            error(2, NULL, 0, NULL, 0,
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
                                                        error(1, NULL, 0, NULL, 0,
                                                              "ld requires -D to have an argument\n");
                                                        exit(2);
                                                    }
                                                }
                                            case 0x62: /* switch 3 */
                                                if ((Warg[2] == 0) || (Warg[2] == 0x2C)) {
                                                    addstr(&ldflags, mkstr(argv[var_s0], ",", Warg, NULL));
                                                }
                                                // }
                                                break;
                                            case 0x4B: /* switch 3 */
                                                if (strcmp(Warg, "-K") != 0) {
                                                    addstr(&ldflags, mkstr(argv[var_s0], ",", Warg, NULL));
                                                } else {
                                                    Kflag++;
                                                }
                                                break;
                                            case 0x41: /* switch 3 */
                                                if (Warg[2] == 0) {
                                                    var_s0++;
                                                    if (var_s0 < argc) {
                                                        addstr(&objfiles, "-A");
                                                    }
                                                    error(1, NULL, 0, NULL, 0, "ld requires -A to have an argument\n");
                                                    exit(2);
                                                }
                                                break;
                                        }
                                        break;
                                    default: /* switch 2 */
                                        error(1, NULL, 0, NULL, 0, "Unknown pass character in %s\n", argv[var_s0]);
                                        exit(2);
                                        break;
                                }
                            }
                            while ((*Warg != 0x2C) && (*Warg != 0)) {
                                Warg++;
                            }
                        }
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x58: /* switch 1 */
                    if (compiler == 1) {
                        if (strcmp(argv[var_s0], "-Xcpluscomm") == 0) {
                            addstr(&ccomflags, argv[var_s0]);
                            break;
                        } else if (strcmp(argv[var_s0], "-Xt") == 0) {
                            stdflag = 0;
                            addstr(&ccomflags, "-std0");
                            break;
                        } else if (strcmp(argv[var_s0], "-Xc") == 0) {
                            stdflag = 1;
                            addstr(&ccomflags, "-std1");
                            break;
                        } else if (strcmp(argv[var_s0], "-Xa") == 0) {
                            stdflag = 1;
                            addstr(&ccomflags, "-std");
                            break;
                        }
                    }
                    if (strcmp(argv[var_s0], "-Xprototypes") == 0) {
                        addstr(&ccomflags, argv[var_s0]);
                    } else {
                        addstr(&ldflags, argv[var_s0]);
                        if ((strcmp(argv[var_s0], "-Xndlocaldata") == 0) ||
                            (strcmp(argv[var_s0], "-Xlocaldata") == 0) || (strcmp(argv[var_s0], "-Xndblock") == 0) ||
                            (strcmp(argv[var_s0], "-Xblock") == 0) || (strcmp(argv[var_s0], "-Xalignbss") == 0) ||
                            (strcmp(argv[var_s0], "-Xnoalignbss") == 0) || (strcmp(argv[var_s0], "-Xcachesize") == 0) ||
                            (strcmp(argv[var_s0], "-Xcachelinesize") == 0) ||
                            (strcmp(argv[var_s0], "-Xdefmovemax") == 0) || (strcmp(argv[var_s0], "-Xsetalign") == 0) ||
                            (strcmp(argv[var_s0], "-Xblockrange") == 0)) {
                            var_s0++;
                            if (var_s0 < argc) {
                                addstr(&ldflags, argv[var_s0]);
                            } else {
                                error(1, NULL, 0, NULL, 0, "%s must have an argument\n", argv[var_s0 - 1]);
                            }
                        }
                    }

                    break;
                case 0x61: /* switch 1 */
                    if ((compiler == 1) && (strcmp(argv[var_s0], "-all") == 0)) {
                        addstr(&objfiles, argv[var_s0]);
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) &&
                               (strcmp(argv[var_s0], "-auto_include") == 0)) {
                        auto_template_include = 1;
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) &&
                               (strcmp(argv[var_s0], "-anach") == 0)) {
                        anachronisms = 1;
                    } else if (strcmp(argv[var_s0], "-ansi") == 0) {
                        if (compchoice == 1) {
                            compchoice = 0;
                        }
                        ansichoice = 1;
                        if (cppchoice != 1) {
                            cppchoice = 3;
                        }
                        relocate_passes("p", NULL, NULL);
                        add_static_opt(argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-ansiposix") == 0) {
                        if (compchoice == 1) {
                            compchoice = 0;
                        }
                        ansichoice = 2;
                        if (cppchoice != 1) {
                            cppchoice = 3;
                        }
                        relocate_passes("p", NULL, NULL);
                        add_static_opt(argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-abi") == 0) {
                        abi_flag = 1;
                        addstr(&cppflags, "-D_ABI_SOURCE");
                        addstr(&asflags, "-abi");
                        addstr(&ldflags, "-abi");
                    } else if (strcmp(argv[var_s0], "-acpp") == 0) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0],
                                  "");
                        } else {
                            cppchoice = 1;
                            acpp = 1;
                            relocate_passes("p", NULL, NULL);
                        }
                    } else {
                        if (strcmp(argv[var_s0], "-align8") == 0) {
                            align = 8;
                            if (compiler == 3) {
                                align_common++;
                            }
                        } else if (strcmp(argv[var_s0], "-align16") == 0) {
                            align = 0x10;
                            if (compiler == 3) {
                                align_common++;
                            }
                        } else if (strcmp(argv[var_s0], "-align32") == 0) {
                            align = 0x20;
                            if (compiler == 3) {
                                align_common++;
                            }
                        } else if (strcmp(argv[var_s0], "-align64") == 0) {
                            align = 0x40;
                            if (compiler == 3) {
                                align_common++;
                            }
                        } else if (strcmp(argv[var_s0], "-align_common") == 0) {
                            align_common = 1;
                            break;
                        }
                        if (compiler == 3) {
                            if ((strcmp(argv[var_s0], "-align8") == 0) || (strcmp(argv[var_s0], "-align16") == 0) ||
                                (strcmp(argv[var_s0], "-align32") == 0) || (strcmp(argv[var_s0], "-align64") == 0)) {
                                addstr(&fcomflags, argv[var_s0]);
                                addstr(&genflags, argv[var_s0]);
                                addstr(&asflags, argv[var_s0]);
                                break;
                            } else if (strcmp(argv[var_s0], "-automatic") == 0) {
                                automaticflag = 1;
                                break;
                            }
                        }
                        if ((compiler == 6) && (strcmp(argv[var_s0], "-ansi") == 0)) {
                            ansiflag = 1;
                        } else if ((compiler == 2) && (strcmp(argv[var_s0], "-apc") == 0)) {
                            addstr(&upasflags, argv[var_s0]);
                            addstr(&genflags, argv[var_s0]);
                        } else if (strcmp(argv[var_s0], "-align8") == 0) {
                            align = 8;
                            alignarg = savestr(argv[var_s0], 0U);
                        } else if (strcmp(argv[var_s0], "-align16") == 0) {
                            align = 0x10;
                            alignarg = savestr(argv[var_s0], 0U);
                        } else if (strcmp(argv[var_s0], "-align32") == 0) {
                            align = 0x20;
                            alignarg = savestr(argv[var_s0], 0U);
                        } else if (strcmp(argv[var_s0], "-align64") == 0) {
                            align = 0x40;
                            alignarg = savestr(argv[var_s0], 0U);
                        } else if (strcmp(argv[var_s0], "-ajeop") == 0) {
                            addstr(&ldflags, argv[var_s0]);
                            addstr(&cordflags, "-no_r4000_fix");
                        } else {
                            goto bad_option;
                        }
                    }

                    break;
                case 0x62: /* switch 1 */
                    if ((argv[var_s0][2] == 0) || (strcmp(argv[var_s0], "-bestGnum") == 0)) {
                        addstr(&ldflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-bytereclen") == 0) {
                        addstr(&fcomflags, argv[var_s0]);
                    } else {
                        if (strcmp(argv[var_s0], "-backslash") == 0) {
                            mp_backslashflag = 1;
                            docpp = 0;
                        }
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                    }
                    break;
                case 0x63: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        cflag++;
                    } else if (strcmp(argv[var_s0], "-cckr") == 0) {
                        ansichoice = 0;
                        if (cppchoice != 1) {
                            cppchoice = 2;
                        }
                        add_static_opt(argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-cfe") == 0) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0],
                                  "");
                        } else {
                            compchoice = 3;
                            relocate_passes("p", NULL, NULL);
                        }
                    } else if (strcmp(argv[var_s0], "-common") == 0) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0],
                                  "");
                        } else {
                            addstr(&accomflags, "-Xcommon");
                        }
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) &&
                               (strcmp(argv[var_s0], "-cfront") == 0)) {
                        cfront_compatible = 1;
                    } else if (strcmp(argv[var_s0], "-cachesz") == 0) {
                        addstr(&ddoptflags, argv[var_s0]);
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(1, NULL, 0, NULL, 0, "-cachesz must have an argument\n");
                            exit(2);
                        }

                        for (var_s2 = Gnum; *var_s2 != 0; var_s2++) {
                            if (!(__ctype[*var_s2 + 1] & 4)) {
                                error(1, NULL, 0, NULL, 0, "non-digit character in -G %s\n", argv[var_s0]);
                                exit(2);
                            }
                        }

                        addstr(&ddoptflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-cplus") == 0) {
                        cplusflag = 1;
                        addstr(&ccomflags, "-cplus");
                    } else if (strcmp(argv[var_s0], "-cpp") == 0) {
                        error(2, NULL, 0, NULL, 0, "-cpp is default\n");
                    } else if (strcmp(argv[var_s0], "-cord") == 0) {
                        cordflag = 1;
                    } else if (strcmp(argv[var_s0], "-coff") == 0) {
                        addstr(&ldflags, argv[var_s0]);
                        coff_spec = 1;
                        if (default_call_shared == 1) {
                            if (non_shared == 0) {
                                old_non_shared = 1;
                                non_shared = 1;
                            }
                            default_call_shared = 0;
                            call_shared = 0;
                        }
                    } else if ((strcmp(argv[var_s0], "-call_shared") == 0) &&
                               ((strcmp(argv[var_s0], "-count") == 0) || (strcmp(argv[var_s0], "-countall") == 0))) {
                        addstr(&objfiles, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-call_shared") == 0) {
                        non_shared = 0;
                        call_shared = 1;
                    } else if (strcmp(argv[var_s0], "-crt0") == 0) {
                        CRTX = "crt0.o";
                        MCRTX = "mcrt0.o";
                        crtn_required = 0;
                        relocate_passes("r", NULL, NULL);
                    } else if (strcmp(argv[var_s0], "-crt1") == 0) {
                        if ((ansichoice == 1) || (ansichoice == 2)) {
                            CRTX = "acrt1.o";
                        } else {
                            CRTX = "crt1.o";
                        }
                        MCRTX = "mcrt1.o";
                        crtn_required = 1;
                        relocate_passes("r", NULL, NULL);
                    } else if ((compiler == 2) && (strcmp(argv[var_s0], "-casesense") == 0)) {
                        addstr(&upasflags, argv[var_s0]);
                    } else if ((compiler == 3) && (strcmp(argv[var_s0], "-change_const") == 0)) {
                        addstr(&fcomflags, "-change_const");
                    } else if ((compiler == 3) &&
                               ((strcmp(argv[var_s0], "-col120") == 0) || (strcmp(argv[var_s0], "-col72") == 0) ||
                                (strcmp(argv[var_s0], "-charargv") == 0) || (strcmp(argv[var_s0], "-chunk") == 0) ||
                                (strcmp(argv[var_s0], "-check_bounds") == 0))) {
                        if (strcmp(argv[var_s0], "-col120") == 0) {
                            mp_col120flag = 1;
                        }
                        if (strcmp(argv[var_s0], "-check_bounds") == 0) {
                            addstr(&fcomflags, "-C");
                        } else if (strncmp(argv[var_s0], "-chunk=", strlen("-chunk=")) == 0) {
                            sp10C = argv[var_s0] + strlen("-chunk=");
                            while (*sp10C != 0) {
                                if (__ctype[1 + *sp10C] & 1) {
                                    *sp10C = __ctype[1 + *sp10C + 0x101];
                                } else {
                                    *sp10C = *sp10C;
                                }
                                sp10C++;
                            }
                            addstr(&fcomflags, mkstr("-mp_chunk=", argv[var_s0] + strlen("-chunk="), NULL));
                        } else {
                            addstr(&fcomflags, argv[var_s0]);
                            if (strncmp(argv[var_s0], "-col", 4) == 0) {
                                add_static_opt(argv[var_s0]);
                            }
                        }
                    } else if ((compiler == 6) && (strcmp(argv[var_s0], "-comp_trunc") == 0)) {
                        addstr(&ucobflags, argv[var_s0]);
                    } else if ((compiler == 1) && (strcmp(argv[var_s0], "-check_registry") == 0)) {
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(1, NULL, 0, NULL, 0, "-check_registry requires a filename argument\n");
                            exit(2);
                        }
                        addstr(&ldflags, argv[var_s0 - 1]);
                        addstr(&ldflags, argv[var_s0]);
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x64: /* switch 1 */
                    if ((compiler == 1) && (strcmp(argv[var_s0], "-dollar") == 0)) {
                        addstr(&pcaflags, "-dollar");
                        addstr(&mpcflags, "-dollar");
                        addstr(&soptflags, "-dollar");
                        addstr(&cfeflags, "-Xdollar");
                        add_static_opt(argv[var_s0]);
                        dollar_sign++;
                    } else if (argv[var_s0][2] == 0) {
                        addstr(&ldflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-ddoptinfo") == 0) {
                        ddoptinfo = 1;
                    } else if ((strcmp(argv[var_s0], "-dy") == 0) || (strcmp(argv[var_s0], "-dn") == 0)) {
                        if (G_flag != 0) {
                            error(1, NULL, 0, NULL, 0, "-dn can not be used with -G \n");
                            exit(2);
                        }
                        dn_flag = 1;
                        addstr(&ldflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-ddopt") == 0) {
                        ddoptflag = 1;
                    } else if ((compiler == 3) && (strcmp(argv[var_s0], "-d_lines") == 0)) {
                        mp_dlinesflag = 1;
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                    } else if ((compiler == 5) && (strcmp(argv[var_s0], "-defext") == 0)) {
                        addstr(&ulpiflags, argv[var_s0]);
                    } else if ((compiler == 6) &&
                               ((strcmp(argv[var_s0], "-dline") == 0) || (strcmp(argv[var_s0], "-defext") == 0))) {
                        addstr(&ucobflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-delay_load") == 0) {
                        addstr(&objfiles, argv[var_s0]);
                    } else if ((compiler == 1) && (strcmp(argv[var_s0], "-default_delay_load") == 0)) {
                        addstr(&ldflags, argv[var_s0]);
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x65: /* switch 1 */
                    if (strcmp(argv[var_s0], "-excpt") == 0) {
                        error(1, NULL, 0, NULL, 0, "-excpt is not supported in svr4 env.\n");
                        exit(2);
                    }
                    if (compiler == 1) {
                        if (strcmp(argv[var_s0], "-elf") == 0) {
                            addstr(&ldflags, argv[var_s0]);
                            continue;
                        } else if ((strcmp(argv[var_s0], "-export") == 0) || (strcmp(argv[var_s0], "-exports") == 0)) {
                            addstr(&objfiles, argv[var_s0]);
                            continue;
                        } else if (strcmp(argv[var_s0], "-exported_symbol") == 0) {
                            var_s0++;
                            if ((var_s0 >= argc) || (argv[var_s0][0] == 0x2D)) {
                                error(1, NULL, 0, NULL, 0, "-exported_symbol requires a symbol argument\n");
                                exit(2);
                            }
                            addstr(&ldflags, argv[var_s0 - 1]);
                            addstr(&ldflags, argv[var_s0]);
                            continue;
                        } else if (strcmp(argv[var_s0], "-exports_file") == 0) {
                            var_s0++;
                            if ((var_s0 >= argc) || (argv[var_s0][0] == 0x2D)) {
                                error(1, NULL, 0, NULL, 0, "-exports_file requires a filename argument\n");
                                exit(2);
                            }
                            addstr(&ldflags, argv[var_s0 - 1]);
                            addstr(&ldflags, argv[var_s0]);
                            continue;
                        } else if (strcmp(argv[var_s0], "-exclude") == 0) {
                            var_s0++;
                            if ((var_s0 >= argc) || (argv[var_s0][0] == 0x2D)) {
                                error(1, NULL, 0, NULL, 0, "-exclude requires a filename argument\n");
                                exit(2);
                            }
                            addstr(&objfiles, argv[var_s0 - 1]);
                            addstr(&objfiles, argv[var_s0]);
                            continue;
                        } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) &&
                                   (strcmp(argv[var_s0], "-exceptions") == 0)) {
                            if ((compiler != 1) || (c_compiler_choice != 3)) {
                                exception_handling = 1;
                                relocate_passes("f", NULL, NULL);
                                if (access(cfe, 0x10) == -1) {
                                    exception_handling = 0;
                                    relocate_passes("f", NULL, NULL);
                                    goto bad_option;
                                }
                            } else {
                                goto bad_option;
                            }
                            continue;
                        }
                    }
                    if (argv[var_s0][2] == 0) {
                        var_s0++;
                        if (var_s0 < argc) {
                            addstr(&ldflags, "-e");
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        } else {
                            error(1, NULL, 0, NULL, 0, "ld requires -e to have an argument\n");
                            exit(2);
                        }
                    }
                    if (strcmp(argv[var_s0], "-exact_version") == 0) {
                        addstr(&ldflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-elf") == 0) {
                        elfflag = 1;
                        elf_spec = 1;
                        addstr(&asflags, argv[var_s0]);
                        addstr(&ldflags, argv[var_s0]);
                    } else if ((compiler == 3) && (strcmp(argv[var_s0], "-extend_source") == 0)) {
                        mp_extendflag = 1;
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                    } else if ((compiler == 3) && (strcmp(argv[var_s0], "-expand_include") == 0)) {
                        addstr(&fcomflags, argv[var_s0]);
                    } else if (strncmp(argv[var_s0], "-edit", 5U) == 0) {
                        if (argv[var_s0][5] == 0) {
                            edit_cnt_max = 0x100;
                        } else if ((__ctype[1 + argv[var_s0][5]] & 4) && (argv[var_s0][6] == 0)) {
                            edit_cnt_max = argv[var_s0][5] - 0x30;
                        } else {
                            error(1, NULL, 0, NULL, 0, "the correct -edit option sybtax is -edit[0-9]\n");
                            exit(2);
                        }
                        editflag = 1;
                        editor = getenv("EDITOR");
                        if (editor != NULL) {
                            for (var_s2 = editor; (strlen(var_s2) >= 5); var_s2++) {
                                if (strncmp(var_s2, "emacs", 5) == 0) {
                                    editflag = 2;
                                    break;
                                }
                            }
                        }
                        if ((editflag == 1) && (editor == NULL)) {
                            editor = "vi";
                        }
                        xserver = getenv("DISPLAY");
                        if ((ioctl(2, 0x40047477, &sp108) == 0) && (getpgrp() == sp108) && (xserver == 0)) {
                            editflag = 0;
                            error(2, NULL, 0, NULL, 0, "%s ignored for background compile in non-X environment\n",
                                  argv[var_s0]);
                        }
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x66: /* switch 1 */
                    if ((strcmp(argv[var_s0], "-full_transtive_link") == 0) ||
                        (strcmp(argv[var_s0], "-full_transitive_link") == 0)) {
                        full_transitive_link = 1;
                        transitive_link = 0;
                        no_transitive_link = 0;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-feedback") == 0) {
                        var_s0++;
                        if (var_s0 < argc) {
                            addstr(&feedlist, argv[var_s0]);
                            break;
                        } else {
                            error(1, NULL, 0, NULL, 0, "-feedback must have an argument\n");
                            exit(2);
                        }
                    }
                    if (strcmp(argv[var_s0], "-fullasopt") == 0) {
                        fullasoptflag = 1;
                    } else if ((compiler == 1) && (strcmp(argv[var_s0], "-force_load") == 0)) {
                        addstr(&objfiles, argv[var_s0]);
                    } else if ((strcmp(argv[var_s0], "-fullwarn") == 0) && (fullwarn = 1, (compiler == 1))) {
                        addstr(&accomflags, "-Xfullwarn");
                        addstr(&cfeflags, "-verbose");
                        addstr(&cfeflags, "-wimplicit");
                    } else if (strcmp(argv[var_s0], "-framepointer") == 0) {
                        if (compiler == 1) {
                            addstr(&ccomflags, argv[var_s0]);
                        } else if (compiler == 2) {
                            addstr(&upasflags, argv[var_s0]);
                        } else if (compiler == 3) {
                            addstr(&fcomflags, argv[var_s0]);
                        } else {
                            goto bad_option;
                        }
                    } else if ((compiler == 1) && (strcmp(argv[var_s0], "-float") == 0)) {
                        addstr(&pcaflags, "-float");
                        addstr(&soptflags, "-float");
                        addstr(&ccomflags, "-Xfloat");
                    } else if (((compiler != 4) && (compiler != 2)) || (strcmp(argv[var_s0], "-float") != 0)) {
                        if (compiler == 6) {
                            if (strcmp(argv[var_s0], "-fsc74") == 0) {
                                addstr(&ucobflags, argv[var_s0]);
                                break;
                            } else if (argv[var_s0][2] == 0) {
                                var_s0++;
                                if ((var_s0 < argc) && (addstr(&ucobflags, "-f"), (argv[var_s0][1] == 0)) &&
                                    ((int)argv[var_s0][0] >= 0x31) && ((int)argv[var_s0][0] < 0x35)) {
                                    addstr(&ucobflags, argv[var_s0]);
                                    continue;
                                } else {
                                    error(1, NULL, 0, NULL, 0, "-f requires an argument of 1, 2, 3 or 4\n");
                                    exit(2);
                                }
                            } else {
                                goto bad_option;
                            }
                        }
                        if (argv[var_s0][2] == 0) {
                            var_s0++;
                            if (var_s0 < argc) {
                                addstr(&ldflags, "-f");
                                addstr(&ldflags, argv[var_s0]);
                            } else {
                                error(1, NULL, 0, NULL, 0, "ld requires -f to have an argument\n");
                                exit(2);
                                goto bad_option;
                            }
                        } else {
                            goto bad_option;
                        }
                    }

                    break;
                case 0x67: /* switch 1 */
                    plain_g = 0;
                    if (argv[var_s0][2] == 0) {
                        gflag = 2;
                        plain_g = 1;
                        if (plain_O != 0) {
                            Oflag = 1;
                        }
                    } else if ((argv[var_s0][3] == 0) && (argv[var_s0][2] >= 0x30) && (argv[var_s0][2] < 0x34)) {
                        gflag = argv[var_s0][2] - 0x30;
                        if (gflag == 2) {
                            plain_g = 1;
                            if (plain_O != 0) {
                                Oflag = 1;
                            }
                        }
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x68: /* switch 1 */
                    if (strcmp(argv[var_s0], "-hostcache") == 0) {
                        addstr(&ddoptflags, argv[var_s0]);
                        break;
                    } else if (strncmp(argv[var_s0], "-help", 5U) == 0) {
                        error(2, NULL, 0, NULL, 0, "-help is ignored.\n");
                        break;
                    } else if (compiler == 1) {
                        if (strcmp(argv[var_s0], "-hides") == 0) {
                            addstr(&objfiles, argv[var_s0]);
                            break;
                        } else if (strcmp(argv[var_s0], "-hidden_symbol") == 0) {
                            var_s0++;
                            if ((var_s0 >= argc) || (argv[var_s0][0] == 0x2D)) {
                                error(1, NULL, 0, NULL, 0, "-hidden_symbol requires a symbol argument\n");
                                exit(2);
                            }
                            addstr(&ldflags, argv[var_s0 - 1]);
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        } else if (strcmp(argv[var_s0], "-hides_file") == 0) {
                            var_s0++;
                            if ((var_s0 >= argc) || (argv[var_s0][0] == 0x2D)) {
                                error(1, NULL, 0, NULL, 0, "-hides_file requires a filename argument\n");
                                exit(2);
                            }
                            addstr(&ldflags, argv[var_s0 - 1]);
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        }
                    }
                    hstring = argv[var_s0] + 2;
                    if (hstring[strlen(hstring) - 1] != 0x2F) {
                        hstring = mkstr(hstring, "/", NULL);
                    }

                    break;
                case 0x69: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        var_s0++;
                        if (var_s0 < argc) {
                            addstr(&ldflags, "-i");
                            addstr(&ldflags, argv[var_s0]);
                            break;
                        } else {
                            error(1, NULL, 0, NULL, 0, "ld requires -i to have an argument\n");
                            exit(2);
                        }
                    }

                    if (strcmp(argv[var_s0], "-inline_to") == 0) {
                        addstr(&umergeflags, argv[var_s0]);
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(1, NULL, 0, NULL, 0, "-inline_to must have an argument\n");
                            exit(2);
                        }
                        for (var_s2 = Gnum; *var_s2 != 0; var_s2++) {
                            if (!(__ctype[*var_s2 + 1] & 4)) {
                                error(1, NULL, 0, NULL, 0, "non-digit character in -G %s\n", argv[var_s0]);
                                exit(2);
                            }
                        }
                        addstr(&umergeflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-ignore_unresolved") == 0) {
                        ignore_unresolved_flag = 1;
                    } else if (strcmp(argv[var_s0], "-ignore_minor") == 0) {
                        addstr(&objfiles, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-irix4") == 0) {
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
                        add_static_opt(argv[var_s0]);
                    } else if (((compiler == 3) &&
                                ((strcmp(argv[var_s0], "-i2") == 0) || (strcmp(argv[var_s0], "-i4") == 0))) ||
                               (strcmp(argv[var_s0], "-i8") == 0)) {
                        if ((argv[var_s0][2] == 0x32) || (argv[var_s0][2] == 0x38)) {
                            mp_i2flag = 1;
                        }
                        addstr(&fcomflags, argv[var_s0]);
                    } else if (compiler == 5) {
                        if (strcmp(argv[var_s0], "-ipath") == 0) {
                            var_s0++;
                            if (var_s0 < argc) {
                                addstr(&upl1flags, "-ipath");
                                addstr(&upl1flags, argv[var_s0]);
                                continue;
                            } else {
                                error(1, NULL, 0, NULL, 0, "-ipath must have an argument\n");
                                exit(2);
                            }
                        }
                        if (strcmp(argv[var_s0], "-isuffix") == 0) {
                            var_s0++;
                            if (var_s0 < argc) {
                                addstr(&upl1flags, "-isuffix");
                                addstr(&upl1flags, argv[var_s0]);
                                continue;
                            } else {
                                error(1, NULL, 0, NULL, 0, "-isuffix must have an argument\n");
                                exit(2);
                                goto bad_option;
                            }
                        } else {
                            goto bad_option;
                        }
                    } else {
                        goto bad_option;
                    }

                    break;
                case 0x6A: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        jflag++;
                        uload = 0;
                    } else if (strcmp(argv[var_s0], "-jalr") == 0) {
                        addstr(&genflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-jmpopt") == 0) {
                        addstr(&objfiles, argv[var_s0]);
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x6B: /* switch 1 */
                    if (strcmp(argv[var_s0], "-keep") == 0) {
                        Kflag++;
                    } else if (strcmp(argv[var_s0], "-kpicopt") == 0) {
                        kpicopt_flag = 1;
                    } else {
                        switch (argv[var_s0][2]) { /* switch 7; irregular */
                            case 0x6F:             /* switch 7 */
                                var_s0++;
                                if (var_s0 < argc) {
                                    uoutfile = argv[var_s0];
                                    var_s1 = getsuf(uoutfile);
                                    if ((var_s1 == 0x63) || (var_s1 == 0x70) || (var_s1 == 0x66) || (var_s1 == 0x46) ||
                                        (var_s1 == 0x72) || (var_s1 == 0x65) || (var_s1 == 6) || (var_s1 == 0x73) ||
                                        (var_s1 == 1) || (var_s1 == 2)) {
                                        error(1, NULL, 0, NULL, 0, "-ko would overwrite %s\n", argv[var_s0]);
                                        exit(2);
                                    }
                                }
                                break;
                            case 0x70: /* switch 7 */
                                var_s0++;
                                if (var_s0 < argc) {
                                    addstr(&uldflags, "-kp");
                                    addstr(&uldflags, argv[var_s0]);
                                }
                                break;
                            case 0x75: /* switch 7 */
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
                    }
                    break;
                case 0x6C: /* switch 1 */
                    if (strcmp("isting", argv[var_s0] + 2) == 0) {
                        addstr(&fcomflags, argv[var_s0]);
                    } else {
                        if ((argv[var_s0][2] == 0x6D) && (argv[var_s0][3] == 0)) {
                            lmflag++;
                        } else if ((argv[var_s0][2] == 0) && ((var_s0 + 1) < argc)) {
                            sp104 = malloc(strlen(argv[var_s0 + 1]) + 3);
                            sp104[0] = 0x2D;
                            sp104[1] = 0x6C;
                            sp104[2] = 0;
                            if (xpg_flag != 0) {
                                addstr(&dashlfiles, strcat(sp104, argv[var_s0 + 1]));
                            } else {
                                addstr(&objfiles, strcat(sp104, argv[var_s0 + 1]));
                            }
                            var_s0++;
                            break;
                        }
                        if (xpg_flag != 0) {
                            addstr(&dashlfiles, argv[var_s0]);
                        } else {
                            addstr(&objfiles, argv[var_s0]);
                        }
                        if (strcmp(argv[var_s0], "-lgl_s") == 0) {
                            B_1000ED2C++;
                            addstr(&objfiles, "-lX11_s");
                        }
                        if (strcmp(argv[var_s0], "-lc_s") == 0) {
                            B_1000ED30++;
                        }
                    }
                    break;
                case 0x6D: /* switch 1 */
                    if (strcmp(argv[var_s0], "-multigot") == 0) {
                        addstr(&nldflags, argv[var_s0]);
                        break;
                    } else if ((compiler == 1) && (strcmp(argv[var_s0], "-mp") == 0)) {
                        cmp_flag |= 0x10008;
                        if (Bflag != 0) {
                            error(1, NULL, 0, NULL, 0, "'-mp' must preceed any -B flags.\n");
                            exit(2);
                        }
                        relocate_passes("fY", NULL, NULL);
                        break;
                    } else if (argv[var_s0][2] == 0) {
                        if ((compiler == 4) || (compiler == 3)) {
                            mflag++;
                        } else {
                            addstr(&ldflags, argv[var_s0]);
                        }
                        if (compiler == 3) {
                            add_static_opt(argv[var_s0]);
                        }
                        break;
                    } else if (compiler == 6) {
                        if (strcmp(argv[var_s0], "-mfext") == 0) {
                            addstr(&ucobflags, argv[var_s0]);
                            break;
                        } else if (strcmp(argv[var_s0], "-map") == 0) {
                            addstr(&ucobflags, argv[var_s0]);
                            break;
                        }
                    }
                    if (strcmp(argv[var_s0], "-mips1") == 0) {
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
                    } else if (strcmp(argv[var_s0], "-mips2") == 0) {
                        if ((mips1flag != 0) || (mips3flag != 0)) {
                            error(2, NULL, 0, NULL, 0, "-mips2 conflicts with -mips1; using last value (mips2)\n");
                        }
                        mips1flag = 0;
                        mips2flag = 1;
                        mips2_spec_flag = 1;
                        relocate_passes("M", NULL, NULL);
                    } else if (strcmp(argv[var_s0], "-mips3") == 0) {
                        mips1flag = 0;
                        mips2flag = 0;
                        if (mips2_spec_flag != 0) {
                            error(1, NULL, 0, NULL, 0, "can't mix -mips3 with -mips[1,2]\n");
                            exit(2);
                        }
                        if ((compiler == 4) || (compiler == 1)) {
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
                    } else {
                        if (strcmp(argv[var_s0], "-mips4") == 0) {
                            error(1, NULL, 0, NULL, 0, "-mips4 cannot be used for ucode 32-bit compiles\n");
                            exit(2);
                        }
                        if (compiler == 3) {
                            if ((argv[var_s0][2] == 0x70) && (argv[var_s0][3] == 0)) {
                                mp_flag |= 0x10000;
                            } else if (strncmp(argv[var_s0], "-mp_keep", strlen("-mp_keep")) == 0) {
                                if (argv[var_s0][8] != 0) {
                                    error(1, NULL, 0, NULL, 0, " Unknown flag: %s\n", argv[var_s0]);
                                    exit(2);
                                }
                                mp_flag |= 0x10000;
                                showdirt_flag = 1;
                            } else if (strncmp(argv[var_s0], "-mp_schedtype=", strlen("-mp_schedtype=")) == 0) {
                                sp100 = argv[var_s0] + strlen("-mp_schedtype=");
                                while (*sp100 != 0) {
                                    &__ctype[*sp100];
                                    if (__ctype[1 + *sp100] & 1) {
                                        *sp100 = __ctype[1 + *sp100 + 0x101];
                                    } else {
                                        *sp100 = *sp100;
                                    }
                                    sp100++;
                                }
                                addstr(&fcomflags, argv[var_s0]);
                            } else {
                                goto bad_option;
                            }
                        } else {
                            goto bad_option;
                        }
                    }

                    break;
                case 0x6E: /* switch 1 */
                    if (strcmp(argv[var_s0], "-nokpicopt") == 0) {
                        nokpicopt_flag = 1;
                        break;
                    } else if (strcmp(argv[var_s0], "-no_unresolved") == 0) {
                        no_unresolved_flag = 1;
                        break;
                    } else if (strcmp(argv[var_s0], "-no_transitive_link") == 0) {
                        transitive_link = 0;
                        full_transitive_link = 0;
                        no_transitive_link = 1;
                        break;
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) &&
                               (strcmp(argv[var_s0], "-no_exceptions") == 0)) {
                        if ((compiler != 1) || (c_compiler_choice != 3)) {
                            exception_handling = 0;
                            relocate_passes("f", NULL, NULL);
                        } else {
                            goto bad_option;
                        }
                        break;
                    } else if (strcmp(argv[var_s0], "-new_ld") == 0) {
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
                        break;
                    } else if (strcmp(argv[var_s0], "-noinline") == 0) {
                        addstr(&umergeflags, argv[var_s0]);
                        break;
                    } else if (strcmp(argv[var_s0], "-nouopt0") == 0) {
                        uopt0flag = 0;
                        break;
                    } else if (strcmp(argv[var_s0], "-noaliasok") == 0) {
                        noaliasokflag = 1;
                        break;
                    } else if (strcmp(argv[var_s0], "-nostdinc") == 0) {
                        emptyIflag = 1;
                        add_static_opt(argv[var_s0]);
                        break;
                    } else if (strcmp(argv[var_s0], "-nostdlib") == 0) {
                        addstr(&ldflags, argv[var_s0]);
                        addstr(&prelinkerflags, mkstr("-YB", NULL));
                        break;
                    } else if (strcmp(argv[var_s0], "-nodeflib") == 0) {
                        nodeflib = 1;
                        break;
                    } else if (strcmp(argv[var_s0], "-noprototypes") == 0) {
                        prototype_checking_on = 0;
                        break;
                    } else if ((argv[var_s0][2] == 0) || (strcmp(argv[var_s0], "-nocount") == 0) ||
                               (strcmp(argv[var_s0], "-nN") == 0) || (strcmp(argv[var_s0], "-nojmpopt") == 0)) {
                        addstr(&objfiles, argv[var_s0]);
                        break;
                    } else if (strcmp(argv[var_s0], "-non_shared") == 0) {
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
                        break;
                    } else if (strcmp(argv[var_s0], "-no_archive") == 0) {
                        addstr(&ldflags, argv[var_s0]);
                        break;
                    } else if (strcmp(argv[var_s0], "-no_mpc") == 0) {
                        B_1000ED74 = 1;
                        break;
                    } else if ((compiler == 3) &&
                               ((strcmp(argv[var_s0], "-noextend_source") == 0) ||
                                (strcmp(argv[var_s0], "-noi4") == 0) || (strcmp(argv[var_s0], "-noisam") == 0) ||
                                (strcmp(argv[var_s0], "-noexpopt") == 0) ||
                                (strcmp(argv[var_s0], "-noequivauto") == 0) || (strcmp(argv[var_s0], "-nof77") == 0))) {
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                        break;
                    } else if (compiler == 6) {
                        if (strcmp(argv[var_s0], "-nolock") == 0) {
                            nolockflag = 1;
                        } else if ((strcmp(argv[var_s0], "-nomfdata") == 0) ||
                                   (strcmp(argv[var_s0], "-normdata") == 0)) {
                            addstr(&ucobflags, argv[var_s0]);
                        } else {
                            goto bad_option;
                        }
                        break;
                    } else if (strcmp(argv[var_s0], "-nocpp") == 0) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0],
                                  "");
                        } else {
                            docpp = 0;
                            add_static_opt(argv[var_s0]);
                        }
                        break;
                    } else if ((compiler == 3) || ((compiler == 1) && (c_compiler_choice != 0))) {
                        if (strcmp(argv[var_s0], "-nocode") == 0) {
                            nocode = 1;
                            cflag = 1;
                            break;
                        } else if (strcmp(argv[var_s0], "-no_prelink") == 0) {
                            no_prelink = 1;
                            break;
                        } else if (strcmp(argv[var_s0], "-no_auto_include") == 0) {
                            auto_template_include = 0;
                            add_static_opt(argv[var_s0]);
                            break;
                        }
                    }
                    if (strcmp(argv[var_s0], "-none") == 0) {
                        addstr(&objfiles, argv[var_s0]);
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) &&
                               (strcmp(argv[var_s0], "-nofilt") == 0)) {
                        nofilt = 1;
                        add_static_opt(argv[var_s0]);
                    } else if ((compiler == 1) && (c_compiler_choice == 3) &&
                               (strncmp(argv[var_s0], "-no_delta", 9U) == 0)) {
                        if (argv[var_s0][9] == 0) {
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
                                error(1, NULL, 0, NULL, 0, "%s must have an argument\n", argv[var_s0]);
                                exit(2);
                            }
                            var_s0++;
                            if (argv[var_s0][0] == 0x2D) {
                                error(1, NULL, 0, NULL, 0, "%s must have an argument\n", argv[var_s0 - 1]);
                                exit(2);
                            }
                            addstr(&edisonflags, mkstr(spFC, argv[var_s0], NULL));
                            add_static_opt(argv[var_s0 - 1]);
                            add_static_opt(argv[var_s0]);
                        } else {
                            goto bad_option;
                        }
                    } else {
                        goto bad_option;
                    }

                    break;
                case 0x6F: /* switch 1 */
                    if (strcmp(argv[var_s0], "-old_rl") == 0) {
                        addstr(&fcomflags, "-old_rl");
                        break;
                    } else if (strcmp(argv[var_s0], "-oldcpp") == 0) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0],
                                  "");
                        } else {
                            oldcppflag = 1;
                            if ((compiler == 1) && (tpflag != 0)) {
                                relocate_passes(tstring, hstring, Bstring);
                            }
                        }
                        break;
                    } else if (strcmp(argv[var_s0], "-old_ld") == 0) {
                        if (D_1000BF94 != 0) {
                            error(1, NULL, 0, NULL, 0, "malformed or unknown option: -old_ld\n");
                            exit(2);
                        } else {
                            LD = "old_ld";
                            relocate_passes("l", NULL, NULL);
                        }
                        break;
                    } else if (strcmp(argv[var_s0], "-o32") == 0) {
                        thirty2bitflag = 1;
                        mips_abi = 1;
                        if (var_s0 >= (argc - 1)) {
                            func_00431B38(var_s0 + 1, 1);
                        }
                        break;
                    } else if (strcmp(argv[var_s0], "-objectlist") == 0) {
                        if ((argv[var_s0 + 1] != 0) && (argv[var_s0 + 1][0] != 0x2D)) {
                            addstr(&objfiles, argv[var_s0]);
                            var_s0++;
                            addstr(&objfiles, argv[var_s0]);
                        } else {
                            error(1, NULL, 0, NULL, 0, "-objectlist must be given a file argument\n");
                        }
                        break;
                    } else if (argv[var_s0][2] == 0) {
                        var_s0++;
                        if (var_s0 < argc) {
                            outfile = argv[var_s0];
                            var_s1 = getsuf(outfile);
                            if (((var_s1 == 0x63) || (var_s1 == 0x70) || (var_s1 == 0x66) || (var_s1 == 0x46) ||
                                 (var_s1 == 0x72) || (var_s1 == 0x65) ||
                                 ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) &&
                                  (var_s1 == 6)) ||
                                 (var_s1 == 0x73) || (var_s1 == 1) || (var_s1 == 2)) &&
                                (stat(outfile, &sp74) == 0)) {
                                error(1, NULL, 0, NULL, 0, "-o %s resembles the name of a source file, disallowed\n",
                                      argv[var_s0]);
                                exit(2);
                            }
                            B_1000ECCC = mkstr(outfile, NULL);
                            func_00431B38(var_s0, 2);
                            break;
                        } else {
                            error(1, NULL, 0, NULL, 0, "-o must have an argument\n");
                            exit(2);
                        }
                    }
                    if ((compiler == 3) && (strcmp(argv[var_s0], "-onetrip") == 0)) {
                        addstr(&fcomflags, "-1");
                        mp_onetripflag = 1;
                    } else {
                        goto bad_option;
                    }

                    break;
                case 0x70: /* switch 1 */
                    if (strcmp(argv[var_s0], "-prototypes") == 0) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0],
                                  "");
                        } else {
                            prototype_checking_on = 1;
                        }
                        break;
                    } else if ((compiler == 1) && (strcmp(argv[var_s0], "-pedantic") == 0)) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0],
                                  "");
                        } else {
                            addstr(&acppflags, "-p");
                        }
                        break;
                    } else if (strcmp(argv[var_s0], "-pfa") == 0) {
                        mp_flag |= 0x10001;
                        if ((var_s0 + 1) < argc) {
                            sp70 = mpflags;
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
                    } else if (strncmp(argv[var_s0], "-pfaprepass,", 12) == 0) {
                        mp_flag |= 0x10001;
                        mp_prepass_count++;
                        break;
                    } else if (strcmp(argv[var_s0], "-pca") == 0) {
                        cmp_flag |= 0x10001;
                        if (Bflag != 0) {
                            error(1, NULL, 0, NULL, 0, "-pca must preceed any -B flags.\n");
                            exit(2);
                        }
                        relocate_passes("fKY", NULL, NULL);
                        if ((var_s0 + 1) < argc) {
                            sp6C = cmpflags;
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
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                        if (strncmp(argv[var_s0], "-pt", 3U) == 0) {
                            sp68 = argv[var_s0] + 3;
                            if (strcmp(sp68, "v") == 0) {
                                verbose_prelink++;
                            } else if (strcmp(sp68, "none") == 0) {
                                default_template_instantiation_mode = 0;
                            } else if (strcmp(sp68, "used") == 0) {
                                default_template_instantiation_mode = 1;
                            } else if ((strcmp(sp68, "a") == 0) || (strcmp(sp68, "all") == 0)) {
                                default_template_instantiation_mode = 2;
                            } else if (*sp68 == 0x65) {
                                if ((strcmp(sp68 + 1, ".c") != 0) && (strcmp(sp68 + 1, ".cc") != 0) &&
                                    (strcmp(sp68 + 1, ".c++") != 0) && (strcmp(sp68 + 1, ".C") != 0) &&
                                    (strcmp(sp68 + 1, ".cxx") != 0) && (strcmp(sp68 + 1, ".CXX") != 0) &&
                                    (strcmp(sp68 + 1, ".cpp") != 0) && (strcmp(sp68 + 1, ".CPP") != 0)) {
                                    error(2, NULL, 0, NULL, 0, "unsupported suffix in %s\n", argv[var_s0]);
                                }
                            } else {
                                error(2, NULL, 0, NULL, 0, "ignored unsupported option %s\n", argv[var_s0]);
                            }
                            continue;
                        } else if (strcmp(argv[var_s0], "-prelink") == 0) {
                            force_prelink = 1;
                            break;
                        }
                    }
                    if (argv[var_s0][2] == 0) {
                        pflag = 1;
                    } else if (strcmp(argv[var_s0], "-pg") == 0) {
                        pflag = 1;
                        pgflag = 1;
                    } else if (argv[var_s0][3] == 0) {
                        if (1) {}
                        if (1) {}
                        if ((argv[var_s0][2] >= 0x30) && (argv[var_s0][2] < 0x34)) {
                            pflag = argv[var_s0][2] - 0x30;
                        } else {
                            goto bad_option;
                        }
                    } else {
                        goto bad_option;
                    }
                    if ((pflag == 0) || (pflag == 1)) {
                        if (Bflag != 0) {
                            error(1, NULL, 0, NULL, 0, "-p0 or -p1 must precede any -B flags\n");
                            exit(2);
                        }
                    } else {
                        error(1, NULL, 0, NULL, 0, "%s has been superseded, see prof (1) and pixie (1)\n",
                              argv[var_s0]);
                        exit(2);
                    }
                    relocate_passes("rn", NULL, NULL);

                    break;
                case 0x71: /* switch 1 */
                    if (strcmp(argv[var_s0], "-quickstart_info") == 0) {
                        quickstart_info = 1;
                    } else if ((strcmp(argv[var_s0], "-ql") == 0) || (strcmp(argv[var_s0], "-qp") == 0)) {

                    } else {
                        goto bad_option;
                    }

                    break;
                case 0x72: /* switch 1 */
                    if ((strcmp(argv[var_s0], "-r4000") == 0) || (strcmp(argv[var_s0], "-r6000") == 0)) {
                        addstr(&asflags, argv[var_s0]);
                    } else if (argv[var_s0][2] == 0) {
                        addstr(&ldflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-require_minor") == 0) {
                        addstr(&objfiles, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-rm_dead_code") == 0) {
                        force_rm_dead_code = 1;
                    } else if ((strcmp(argv[var_s0], "-rpath") == 0) && (argv[var_s0 + 1] != 0) &&
                               (argv[var_s0 + 1][0] != 0x2D)) {
                        addstr(&ldflags, argv[var_s0]);
                        var_s0++;
                        addstr(&ldflags, argv[var_s0]);
                    } else if ((strcmp(argv[var_s0], "-rdata_shared") == 0) ||
                               (strcmp(argv[var_s0], "-rdata_writable") == 0)) {
                        addstr(&ldflags, argv[var_s0]);
                    } else if ((compiler == 3) && (strcmp(argv[var_s0], "-r8") == 0)) {
                        addstr(&fcomflags, argv[var_s0]);
                    } else if ((compiler == 6) &&
                               ((strcmp(argv[var_s0], "-range") == 0) || (strcmp(argv[var_s0], "-rmansi") == 0) ||
                                (strcmp(argv[var_s0], "-rmext") == 0))) {
                        addstr(&ucobflags, argv[var_s0]);
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x73: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                            do_strip = 1;
                        } else {
                            addstr(&ldflags, argv[var_s0]);
                        }
                    } else if (strcmp(argv[var_s0], "-strictIEEE") == 0) {
                        addstr(&optflags, argv[var_s0]);
                    } else if ((((compiler == 1) && (c_compiler_choice != 0)) || (compiler == 3)) &&
                               (strncmp(argv[var_s0], "-sa", 3U) == 0) &&
                               ((argv[var_s0][3] == 0) || (argv[var_s0][3] == 0x2C))) {
                        D_1000BF74 = 1;
                        if ((argv[var_s0][3] == 0x2C) && (argv[var_s0][4] != 0)) {
                            for (sp64 = strtok(argv[var_s0] + 4, ","); sp64 != NULL; sp64 = strtok(NULL, ",")) {
                                if (strcmp(sp64, "nosrc") == 0) {
                                    D_1000BF78 = 1;
                                } else if (D_1000BF80 != NULL) {
                                    error(1, NULL, 0, NULL, 0, "Static analysis directory already specified\n");
                                } else {
                                    D_1000BF80 = sp64;
                                    if (sp64[strlen(sp64) - 1] != 0x2F) {
                                        D_1000BF80 = mkstr(sp64, "/", NULL);
                                    }
                                }
                            }
                        }
                    } else if ((((compiler == 1) && (c_compiler_choice != 0)) || (compiler == 3)) &&
                               (strncmp(argv[var_s0], "-sa_fs", 6U) == 0) &&
                               ((argv[var_s0][6] == 0) || (argv[var_s0][6] == 0x2C))) {
                        D_1000BF84 =
                            (argv[var_s0][6] == 0x2C) ? mkstr(argv[var_s0] + 7, NULL) : mkstr("cvstatic.fileset", NULL);
                        D_1000BF88++;
                    } else if ((compiler == 1) && (strcmp(argv[var_s0], "-set_version") == 0)) {
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(1, NULL, 0, NULL, 0, "-set_version requires an argument\n");
                            exit(2);
                        }
                        addstr(&ldflags, argv[var_s0 - 1]);
                        addstr(&ldflags, argv[var_s0]);
                    } else if ((compiler == 1) && (strcmp(argv[var_s0], "-soname") == 0)) {
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(1, NULL, 0, NULL, 0, "-soname requires an argument\n");
                            exit(2);
                        }
                        addstr(&ldflags, argv[var_s0 - 1]);
                        addstr(&ldflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-systype") == 0) {
                        var_s0++;
                        if (var_s0 >= argc) {
                            error(1, NULL, 0, NULL, 0, "-systype must have an argument\n");
                            exit(2);
                        }
                        if (user_systype != 0) {
                            if (strcmp(systype, argv[var_s0]) != 0) {
                                error(1, NULL, 0, NULL, 0, "only one -systype option allowed\n");
                                exit(2);
                            } else {
                                multiple_systype = 1;
                            }
                        }
                        systype = argv[var_s0];
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
                            if ((strcmp(systype, "svr4") != 0) && (strcmp(systype, "bsd43") != 0) &&
                                (strcmp(systype, "svr3") != 0) && (strcmp(systype, "sysv") != 0) &&
                                (fopen(strcat("/", systype), "r") == NULL)) {
                                if (systype_warn == 0) {
                                    error(2, NULL, 0, NULL, 0,
                                          "This systype doesn't exist on this machine; changed systype to svr3.\n");
                                }
                                systype = "svr3";
                            }
                            if (svr4_systype == 0) {
                                comp_target_root = mkstr(comp_target_root, systype, "/", NULL);
                            }
                            if (fiveflag != 0) {
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
                    } else if (strcmp(argv[var_s0], "-swopcode") == 0) {
                        if ((dwopcodeflag != 0) || (sixty4bitflag != 0)) {
                            error(1, NULL, 0, NULL, 0, "-swopcode can not be used with -dwopcode/-64bit\n");
                            exit(2);
                        }
                        swopcodeflag = 1;
                    } else if ((argv[var_s0][2] == 0x6F) && (argv[var_s0][3] == 0x70) && (argv[var_s0][4] == 0x74)) {
                        if ((compiler != 1) && (compiler != 3)) {
                            error(2, NULL, 0, NULL, 0, "-sopt only available with Fortran and C; option ignored.\n");
                        } else if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0],
                                  "");
                        } else {
                            Warg = argv[var_s0] + 5;
                            while (*Warg == 0x2C) {
                                *Warg++ = 0;
                                addstr(&soptflags, Warg);
                                while ((*Warg != 0x2C) && (*Warg != 0)) {
                                    Warg++;
                                }
                            }
                            run_sopt = 1;
                        }
                    } else if (strcmp(argv[var_s0], "-show") == 0) {
                        vflag = 1;
                    } else if (strcmp(argv[var_s0], "-showt") == 0) {
                        time_flag = 1;
                    } else if (strcmp(argv[var_s0], "-show0") == 0) {
                        vflag = 1;
                        execute_flag = 0;
                    } else if (strcmp(argv[var_s0], "-showm") == 0) {
                        memory_flag++;
                    } else if (strcmp(argv[var_s0], "-show_defaults") == 0) {
                        execute_flag = 0;
                        exit(0);
                    } else {
                        if (compiler == 1) {
                            if ((compiler == 1) && (c_compiler_choice != 0) &&
                                (strncmp(argv[var_s0], "-smart", 6U) == 0)) {
                                if ((argv[var_s0][6] == 0x2C) && (argv[var_s0][7] != 0)) {
                                    sbrepos = argv[var_s0] + 7;
                                } else {
                                    sbrepos = NULL;
                                }
                                add_static_opt(argv[var_s0]);
                                smart_build = 1;
                                break;
                            } else if (strcmp(argv[var_s0], "-shared") == 0) {
                                call_shared = 0;
                                make_edison_shlib++;
                                break;
                            } else if (strcmp(argv[var_s0], "-std0") == 0) {
                                stdflag = 0;
                                addstr(&ccomflags, argv[var_s0]);
                                break;
                            } else if ((strcmp(argv[var_s0], "-std") == 0) || (strcmp(argv[var_s0], "-std1") == 0)) {
                                stdflag = 1;
                                addstr(&ccomflags, argv[var_s0]);
                                break;
                            } else if (strcmp(argv[var_s0], "-signed") == 0) {
                                addstr(&pcaflags, "-signed");
                                addstr(&soptflags, "-signed");
                                addstr(&ccomflags, "-Xsigned");
                                if ((compiler == 1) && (c_compiler_choice != 0)) {
                                    signedcharflag = 1;
                                }
                                break;
                            }
                        }
                        if ((compiler == 4) &&
                            ((strcmp(argv[var_s0], "-std") == 0) || (strcmp(argv[var_s0], "-std0") == 0) ||
                             (strcmp(argv[var_s0], "-std1") == 0))) {
                            stdflag = 1;
                            addstr(&ccomflags, argv[var_s0]);
                            break;
                        } else if (compiler == 3) {
                            if (strcmp(argv[var_s0], "-std") == 0) {
                                addstr(&fcomflags, argv[var_s0]);
                                break;
                            } else if (strcmp(argv[var_s0], "-static") == 0) {
                                automaticflag = 0;
                                break;
                            } else if (strncmp(argv[var_s0], "-share_", 7U) == 0) {
                                if (strcmp(argv[var_s0] + 7, "io") == 0) {
                                    D_1000C130 = 1;
                                    break;
                                } else if (strcmp(argv[var_s0] + 7, "all") == 0) {
                                    D_1000C130 = 2;
                                    break;
                                }
                            }
                        }
                        if ((compiler == 2) && (strcmp(argv[var_s0], "-std") == 0)) {
                            stdflag = 1;
                            addstr(&upasflags, argv[var_s0]);
                        } else if ((compiler == 6) && ((strcmp(argv[var_s0], "-supp_cob85") == 0) ||
                                                       (strcmp(argv[var_s0], "-supp_cod") == 0) ||
                                                       (strcmp(argv[var_s0], "-supp_rm") == 0))) {
                            addstr(&ucobflags, argv[var_s0]);
                        } else if ((compiler == 4) && (strcmp(argv[var_s0], "-signed") == 0)) {

                        } else {
                            goto bad_option;
                        }
                    }

                    break;
                case 0x74: /* switch 1 */
                    if (strcmp(argv[var_s0], "-transitive_link") == 0) {
                        full_transitive_link = 0;
                        transitive_link = 1;
                        no_transitive_link = 0;
                    } else if (strcmp(argv[var_s0], "-trapuv") == 0) {
                        trapuv_flag = 1;
                        addstr(&upasflags, argv[var_s0]);
                        addstr(&fcomflags, argv[var_s0]);
                        addstr(&upl1flags, argv[var_s0]);
                        addstr(&ucobflags, argv[var_s0]);
                        addstr(&ulpiflags, argv[var_s0]);
                        addstr(&eflflags, argv[var_s0]);
                        addstr(&ratforflags, argv[var_s0]);
                        addstr(&genflags, argv[var_s0]);
                        addstr(&asflags, argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-tfp") == 0) {
                        tfp_flag = 1;
                    } else if (strcmp(argv[var_s0], "-traditional") == 0) {
                        acpp_traditional++;
                    } else {
                        tstring = argv[var_s0] + 2;
                        strcat(alltstring, tstring);
                    }
                    break;
                case 0x5A:                     /* switch 1 */
                    switch (argv[var_s0][2]) { /* switch 4 */
                        case 0x41:             /* switch 4 */
                            error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;
                        case 0x43: /* switch 4 */
                            error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;
                        case 0x46: /* switch 4 */
                            error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;
                        case 0x4E: /* switch 4 */
                            error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;
                        case 0x50: /* switch 4 */
                            error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;
                        case 0x55: /* switch 4 */
                            error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;
                        case 0x66: /* switch 4 */
                            error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;
                        case 0x69: /* switch 4 */
                            error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;
                        case 0x52: /* switch 4 */
                            error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;
                        case 0x47: /* switch 4 */
                            addstr(&ldZflags, "-ZG");
                            break;
                        case 0x71: /* switch 4 */
                            vflag = 1;
                            break;
                        case 0x67: /* switch 4 */
                            error(2, NULL, 0, NULL, 0, "-Zg is obsolete and is ignored.\n");
                            if (compiler == 1) {
                                error(2, NULL, 0, NULL, 0,
                                      "perhaps replace -Zg with -lgl_s. See your graphics documentation.\n");
                            }
                            if ((hasfortran != 0) || (compiler == 3)) {
                                error(2, NULL, 0, NULL, 0, "perhaps replace -Zg with -lfgl -lgl_s  See f77(1).\n");
                            }
                            if ((haspascal != 0) || (compiler == 2)) {
                                error(2, NULL, 0, NULL, 0,
                                      "perhaps replace -Zg with -lpgl /usr/lib/p2cstr.o -lgl_s  See pc(1).\n");
                            }
                            break;
                        case 0x72: /* switch 4 */
                            error(2, NULL, 0, NULL, 0, "-Zr is obsolete and is ignored.\n");
                            break;
                        case 0x76: /* switch 4 */
                            stdflag = 1;
                            addstr(&ccomflags, "-std");
                            addstr(&upasflags, "-std");
                            addstr(&fcomflags, "-std");
                            addstr(&upl1flags, "-std");
                            addstr(&ucobflags, "-std");
                            break;
                        case 0x7A: /* switch 4 */
                            error(2, NULL, 0, NULL, 0, "%s not supported\n", argv[var_s0]);
                            break;
                        default: /* switch 4 */
                            error(1, NULL, 0, NULL, 0, "Unknown character in %s\n", argv[var_s0]);
                            exit(2);
                            break;
                    }
                    break;
                case 0x2D: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        if (xpg_flag != 0) {
                            NoMoreOptions++;
                        }
                    } else {
                        switch (argv[var_s0][2]) { /* switch 8; irregular */
                            case 0x6E:             /* switch 8 */
                                error(2, NULL, 0, NULL, 0, "%s is default\n", argv[var_s0]);
                                break;
                            case 0x78: /* switch 8 */
                                error(2, NULL, 0, NULL, 0, "%s is default\n", argv[var_s0]);
                                break;
                            default: /* switch 8 */
                                error(1, NULL, 0, NULL, 0, "Unknown character in %s\n", argv[var_s0]);
                                exit(2);
                                break;
                        }
                    }
                    break;
                case 0x75: /* switch 1 */
                    if (strcmp(argv[var_s0], "-uopt0") != 0) {
                        if (argv[var_s0][2] == 0) {
                            if (compiler == 3) {
                                mp_uflag = 1;
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
                                    error(1, NULL, 0, NULL, 0, "ld requires -u to have an argument\n");
                                    exit(2);
                                }
                            }
                        }
                        if (strcmp(argv[var_s0], "-unroll") == 0) {
                            error(1, NULL, 0, NULL, 0, "This flag is no longer supported\n");
                            exit(2);
                        } else if ((compiler == 3) && (strcmp(argv[var_s0], "-usefpidx") == 0)) {
                            addstr(&fcomflags, argv[var_s0]);
                            break;
                        }
                        if (strcmp(argv[var_s0], "-use_readwrite_const") == 0) {
                            if ((compiler == 1) && (c_compiler_choice != 0)) {
                                addstr(&edisonflags, "-Yr0");
                            } else {
                                addstr(&accomflags, "-use_readwrite_const");
                            }
                        } else if (strcmp(argv[var_s0], "-use_readonly_const") == 0) {
                            if ((compiler == 1) && (c_compiler_choice != 0)) {
                                addstr(&edisonflags, "-Yr1");
                            } else {
                                addstr(&accomflags, "-use_readonly_const");
                            }
                        } else if ((compiler == 1) && (strcmp(argv[var_s0], "-update_registry") == 0)) {
                            var_s0++;
                            if (var_s0 >= argc) {
                                error(1, NULL, 0, NULL, 0, "-update_registry requires a filename argument\n");
                                exit(2);
                            }
                            addstr(&ldflags, argv[var_s0 - 1]);
                            addstr(&ldflags, argv[var_s0]);
                        } else {
                            goto bad_option;
                        }
                    }
                    break;
                case 0x76: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        if (default_svr4 == 0) {
                            vflag = 1;
                            time_flag = 1;
                        }
                        break;
                    } else if (compiler == 1) {
                        if (strcmp(argv[var_s0], "-volatile") == 0) {
                            error(2, NULL, 0, NULL, 0,
                                  "-volatile is no longer supported; use the volatile qualifier instead\n");
                            break;
                        } else if (strcmp(argv[var_s0], "-varargs") == 0) {
                            addstr(&ccomflags, "-Xvarargs");
                            break;
                        } else if (strcmp(argv[var_s0], "-verbose") == 0) {
                            addstr(&ccomflags, "-verbose");
                            break;
                        }
                    }
                    if ((compiler == 3) &&
                        ((strncmp(argv[var_s0], "-vms", 4U) == 0) || (strcmp(argv[var_s0], "-varargs") == 0))) {
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) &&
                               (strcmp(argv[var_s0], "-v2") == 0)) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0],
                                  "");
                        }
                    } else {
                        goto bad_option;
                    }

                    break;
                case 0x77: /* switch 1 */
                    if ((compiler == 1) && (strncmp(argv[var_s0], "-wlint", 6U) == 0)) {
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0],
                                  "");
                        } else {
                            addstr(&ccomflags, argv[var_s0]);
                        }
                        break;
                    } else if (strcmp(argv[var_s0], "-woff") == 0) {
                        var_s0++;
                        if (var_s0 < argc) {
                            if (strcmp(argv[var_s0], "options") == 0) {
                                sp14C = 0;
                                continue;
                            } else if ((argv[var_s0][0] < 0x30) || (argv[var_s0][0] >= 0x3A)) {
                                error(2, NULL, 0, NULL, 0,
                                      "-woff requires a comma-separated list of error numbers - ignored\n");
                                var_s0 -= 1;
                                continue;
                            } else {
                                addstr(&accomflags, mkstr("-Xwoff", argv[var_s0], NULL));
                                addstr(&edisonflags, mkstr("-YW", argv[var_s0], NULL));
                            }
                            break;
                        } else {
                            error(1, NULL, 0, NULL, 0, "-woff requires a warning number (or a list of them)\n");
                            exit(2);
                        }
                    }
                    if ((argv[var_s0][2] == 0x31) && (argv[var_s0][3] == 0)) {
                        if (compiler != 3) {
                            error(2, NULL, 0, NULL, 0, "Unknown flag: %s\n", argv[var_s0]);
                        } else {
                            w1flag = 1;
                        }
                    } else if ((argv[var_s0][2] == 0x30) && (argv[var_s0][3] == 0)) {
                        if (compiler != 3) {
                            error(2, NULL, 0, NULL, 0, "Unknown flag: %s\n", argv[var_s0]);
                        } else {
                            w1flag = 0;
                        }
                    } else if (argv[var_s0][2] == 0x36) {
                        if ((compiler == 3) && (argv[var_s0][2] == 0x36)) {
                            mp_66flag = 1;
                        }
                        addstr(&fcomflags, argv[var_s0]);
                    } else if ((argv[var_s0][2] != 0) && (compiler == 1) && (c_compiler_choice != 0)) {
                        error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0], "");
                    } else if ((argv[var_s0][2] == 0) ||
                               ((argv[var_s0][3] == 0) && ((argv[var_s0][2] == 0x31) || (argv[var_s0][2] == 0x32) ||
                                                           (argv[var_s0][2] == 0x33)))) {
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
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x79: /* switch 1 */
                    if (argv[var_s0][2] != 0) {
                        addstr(&objfiles, argv[var_s0]);
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x78: /* switch 1 */
                    if (strcmp(argv[var_s0], "-xansi") == 0) {
                        if (compchoice == 1) {
                            compchoice = 0;
                        }
                        ansichoice = 3;
                        cppchoice = 3;
                        relocate_passes("p", NULL, NULL);
                        add_static_opt(argv[var_s0]);
                    } else if (strcmp(argv[var_s0], "-xgot") == 0) {
                        addstr(&asflags, "-big_got");
                    } else if (argv[var_s0][2] == 0) {
                        addstr(&ldflags, argv[var_s0]);
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x7A: /* switch 1 */
                    if (argv[var_s0][2] == 0) {
                        addstr(&ldflags, argv[var_s0]);
                    } else {
                        goto bad_option;
                    }
                    break;
                default:
                    goto bad_option;
            }
            continue;
        } else if ((argv[var_s0][0] == 0x2B) && (compiler == 1) &&
                   ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
            switch (argv[var_s0][1]) { /* switch 5 */
                case 0x70:             /* switch 5 */
                    if (argv[var_s0][2] == 0) {
                        anachronisms = 0;
                    } else if (argv[var_s0][2] == 0x70) {
                        anachronisms = 0;
                        cfront_compatible = 0;
                    } else if (argv[var_s0][2] == 0x61) {
                        anachronisms = 0;
                    } else if (argv[var_s0][2] == 0x63) {
                        cfront_compatible = 0;
                    }
                    add_static_opt(argv[var_s0]);
                    break;
                case 0x77: /* switch 5 */
                    fullwarn = 1;
                    break;
                case 0x76: /* switch 5 */
                    vflag = 1;
                    break;
                case 0x64: /* switch 5 */
                    disable_inlines = 1;
                    break;
                case 0x65: /* switch 5 */
                    if ((compiler == 1) && (c_compiler_choice != 0)) {
                        error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0], "");
                        break;
                    }
                case 0x49: /* switch 5 */
                    cflag = 1;
                    plusIflag = 1;
                    Fflag = 1;
                    default_template_instantiation_mode = 1;
                    break;
                case 0x61:
                case 0x4C:
                    break;
                default: /* switch 5 */
                    goto bad_option;
            }
            continue;
        } else {
            var_s1 = getsuf(argv[var_s0]);
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
            if ((var_s1 == 0x63) || (var_s1 == 0x70) || (var_s1 == 0x66) || (var_s1 == 0x46) || (var_s1 == 0x72) ||
                (var_s1 == 0x65) || (var_s1 == 0x42) || (var_s1 == 0x55) || (var_s1 == 0x73) || (var_s1 == 0x4F) ||
                (var_s1 == 0x47) || (var_s1 == 0x53) || (var_s1 == 0x4D) || (var_s1 == 0x56) || (var_s1 == 0x69) ||
                (var_s1 == 1) || (var_s1 == 0x44) || (var_s1 == 3) || (var_s1 == 2) || (var_s1 == 0x75) ||
                (var_s1 == 6) || ((compiler == 1) && (nocode != 0) && (D_1000BF74 != 0) && (var_s1 == 0x68)) ||
                (Eflag != 0) || (compiler == 4)) {
                srcexists++;
                if ((argv[var_s0][0] == 0x2D) && (NoMoreOptions == 0)) {
                    sp60 = 1;
                    while (argv[var_s0][sp60] == 0x2D) {
                        sp60++;
                    }
                    argv[var_s0] += sp60;
                }
                for (sp5C = 1; sp5C < argc; sp5C++) {
                    if ((argv[sp5C][1] == 0x6A) && (strcmp(argv[sp5C], "-j") == 0)) {
                        jflag++;
                    }
                }
                if (((Oflag == 3) || (Oflag == 4)) && (jflag == 0) &&
                    ((var_s1 == 0x63) || (var_s1 == 0x70) || (var_s1 == 0x66) || (var_s1 == 0x46) || (var_s1 == 0x72) ||
                     (var_s1 == 0x65) || (var_s1 == 0x42) || (var_s1 == 0x55) || (var_s1 == 0x69) || (var_s1 == 1) ||
                     (var_s1 == 3) || (var_s1 == 2) || (var_s1 == 6) || (var_s1 == 0x75) || (var_s1 == 0x44))) {
                    if (var_s1 != 0x75) {
                        addstr(&srcfiles, argv[var_s0]);
                        var_s2 = mksuf(argv[var_s0], 0x75);
                    } else {
                        var_s2 = argv[var_s0];
                    }
                    uload = 1;
                    if (uldobj_place == -1) {
                        uldobj_place = save_place(&objfiles);
                    }
                    if (nodup(&ufiles, var_s2) != 0) {
                        addstr(&ufiles, var_s2);
                    }
                    var_s2 = mksuf(argv[var_s0], 0x6F);
                    if (nodup(&objfiles, var_s2) != 0) {
                        sp158 = var_s2;
                    }
                } else if ((Eflag == 0) && (compiler != 4)) {
                    addstr(&srcfiles, argv[var_s0]);
                    var_s2 = mksuf(argv[var_s0], 0x6F);
                    if (nodup(&objfiles, var_s2) != 0) {
                        addstr(&objfiles, var_s2);
                        sp158 = var_s2;
                        nobjs++;
                    }
                } else {
                    addstr(&srcfiles, argv[var_s0]);
                }
            } else if (var_s1 == 0x62) {
                if (((Oflag == 3) || (Oflag == 4)) && (jflag == 0)) {
                    if (uldobj_place == -1) {
                        uldobj_place = save_place(&objfiles);
                    }
                    addstr(&ufiles, argv[var_s0]);
                    uload = 1;
                }
            } else {
                addstr(&objfiles, argv[var_s0]);
                if (var_s1 == 0x6F) {
                    nobjs++;
                }
            }
            func_00431B38(var_s0 + 1, 1);
            continue;
        }
    bad_option:
        if (sp14C != 0) {
            error(1, NULL, 0, NULL, 0, "malformed or unknown option: %s\n", argv[var_s0]);
            exit(2);
        } else {
            error(2, NULL, 0, NULL, 0, "malformed or unknown option: %s\n", argv[var_s0]);
        }
    }

    if (sp15C != NULL) {
        if (srcfiles.length == 1) {
            sp58 = strdup(*srcfiles.entries);
            if (sp58 == NULL) {
                sp58 = sp158;
            } else {
                sp54 = strlen(sp58);
                if ((sp54 >= 3) && (sp58[sp54 - 2] == 0x2E)) {
                    if (Eflag != 0) {
                        sp58[sp54 - 1] = 0x69;
                    } else if (Sflag != 0) {
                        sp58[sp54 - 1] = 0x73;
                    } else if (jflag != 0) {
                        sp58[sp54 - 1] = 0x75;
                    } else {
                        sp58[sp54 - 2] = 0;
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
                if (outfile != NULL) {
                    addstr(&cppflags, outfile);
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
                if (outfile != NULL) {
                    addstr(&uldflags, outfile);
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

// function get_host_chiptype # 6
// Blank function
void get_host_chiptype(void) {
}

// function error # 7

static const char* D_1000C1E0[] = {
    "Internal", "Error", "Warning", "Info", "Fix", "",
};

#ifndef PERMUTER

// Print an error. Has to be K&R for the variadic stuff to work in other functions
void error(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB)
    // clang-format off
    int arg0;
    const char* arg1;
    int arg2;
    const char* arg3;
    int arg4;
    const char* arg5;
    int arg6;
    int arg7;
    int arg8;
    int arg9;
    int argA;
    int argB;
// clang-format on
{
    int len;
    int i;

    if ((Vflag == 0) && (D_1000C1D8 == NULL)) {
        D_1000C1D8 = strrchr(progname, '/');
        if (D_1000C1D8 == NULL) {
            D_1000C1D8 = progname;
        } else {
            D_1000C1D8++;
        }

        len = strlen(D_1000C1D8);
        D_1000C1DC = malloc(len + 2);
        if (D_1000C1DC == NULL) { // malloc failed
            fprintf(stderr, "%s: Error: error (), %d: Out of memory\n", D_1000C1D8, 13332);

            if (errno < sys_nerr) {
                fprintf(stderr, "%s: %s\n", D_1000C1D8, sys_errlist[errno]);
            }
            exit(1);
        }

        for (i = 0; i < len; i++) {
            D_1000C1DC[i] = ' ';
        }
        D_1000C1DC[i] = '\0';
    }

    if (arg0 == 5) {
        fprintf(stderr, "%s: ", D_1000C1DC);
    } else {
        fprintf(stderr, "%s: %s: ", D_1000C1D8, D_1000C1E0[arg0]);
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
    if (arg5 == NULL) {
        arg5 = "";
    }
    fprintf(stderr, arg5, arg6, arg7, arg8, arg9, argA, argB);
}
#endif /* PERMUTER */

// function relocate_passes # 8
void relocate_passes(const char* arg0, const char* arg1, const char* arg2) {
    register int pad;
    register const char* var_s1;

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
    for (; *var_s1 != '\0'; var_s1++) {
        if ((arg1 != NULL) || (strchr(alltstring, *var_s1) == 0)) {
            switch (*var_s1) {
                case 'h':
                    if (includeB != NULL) {
                        free(includeB);
                    }
                    if (eincludeB != NULL) {
                        free(eincludeB);
                    }
                    if ((arg0 != NULL) || ((arg2 != NULL) && (*arg2 != 0))) {
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

                case 'p':
                    if (cpp != NULL) {
                        free(cpp);
                    }
                    if (arg1 != NULL) {
                        cpp = mkstr(arg1, ((cppchoice != 1) && (cppchoice != 3)) ? "cpp" : "acpp", arg2, NULL);
                    } else {
                        cpp = mkstr(comp_host_root, "usr/lib/", currcomp,
                                    (cppchoice != 1) && (cppchoice != 3) ? "cpp" : "acpp", arg2, NULL);
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
                        ccom = mkstr(arg1, ansichoice ? "accom" : "ccom", arg2, NULL);
                        cfe = mkstr(arg1,
                                    ((c_compiler_choice != 0) || ((compiler == 3) && (D_1000BF74 != 0)))
                                        ? (exception_handling ? "edgcpfe.eh" : "edgcpfe")
                                        : "cfe",
                                    arg2, NULL);
                        upas = mkstr(arg1, "upas", arg2, NULL);
                        fcom = mkstr(arg1, "fcom", arg2, NULL);
                        upl1 = mkstr(arg1, "pl1fe", arg2, NULL);
                        ucob = mkstr(arg1, "cobfe", arg2, NULL);
                    } else {
                        if (cmp_flag & 0x10000) {
                            mpc = mkstr(comp_host_root, "usr/lib/", currcomp, "mpc", arg2, NULL);
                        }
                        ccom = mkstr(comp_host_root, "usr/lib/", currcomp, ansichoice ? "accom" : "ccom", arg2, NULL);
                        if (((compiler == 1) && (c_compiler_choice != 0)) || ((compiler == 3) && (D_1000BF74 != 0))) {
                            cfe = mkstr(comp_host_root, "usr/lib/DCC/", currcomp,
                                        ((c_compiler_choice != 0) || ((compiler == 3) && (D_1000BF74 != 0)))
                                            ? (exception_handling ? "edgcpfe.eh" : "edgcpfe")
                                            : "cfe",
                                        arg2, NULL);
                        } else {
                            cfe = mkstr(comp_host_root, "usr/lib/", currcomp,
                                        ((c_compiler_choice != 0) || ((compiler == 3) && (D_1000BF74 != 0)))
                                            ? (exception_handling ? "edgcpfe.eh" : "edgcpfe")
                                            : "cfe",
                                        arg2, NULL);
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
                        uld = mkstr(comp_host_root, "usr/lib/", currcomp, "uld", arg2, 0);
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
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) &&
                               (D_1000BF8C != 0)) {
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
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) &&
                               (D_1000BF8C != 0)) {
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
                    } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) &&
                               (D_1000BF8C != 0)) {
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
                    if (filter != NULL) {
                        free(filter);
                    }
                    if (arg1 != NULL) {
                        ld = mkstr(arg1, LD, arg2, NULL);
                        patch = mkstr(arg1, "c++patch", arg2, NULL);
                        filter = mkstr(arg1, "c++filt", arg2, NULL);
                    } else {
                        if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) &&
                            (D_1000BF90 != 0)) {
                            ld = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, LD, arg2, NULL);
                        } else if (irix4 != 0) {
                            ld = mkstr(comp_host_root, "usr/bin/", currcomp, LD, arg2, NULL);
                        } else {
                            ld = mkstr(comp_host_root, "usr/lib/", currcomp, LD, arg2, NULL);
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

                case 'x':
                    if (strip != NULL) {
                        free(strip);
                    }
                    if (arg1 != NULL) {
                        strip = mkstr(arg1, "strip", arg2, NULL);
                    } else {
                        strip = mkstr(comp_host_root, "usr/bin/", currcomp, "strip", arg2, NULL);
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
                            cxx_init = mkstr(arg1, exception_handling ? "c++init_eh.o" : "c++init.o", arg2, NULL);
                            delta_init = mkstr(arg1, "delta_init.o", arg2, NULL);
                            crtn = mkstr(arg1, "crtn.o", arg2, NULL);
                        } else {
                            crtx = mkstr(arg1, CRTX, arg2, NULL);
                            cxx_init = mkstr(arg1, exception_handling ? "c++init_eh.o" : "c++init.o", arg2, NULL);
                            delta_init = mkstr(arg1, "delta_init.o", arg2, NULL);
                            crtn = mkstr(arg1, "crtn.o", arg2, NULL);
                        }
                    } else if (pflag != 0) {
                        if (abi_flag != 0) {
                            crtx = func_0042FD7C(mkstr(MCRTX, arg2, NULL), dirs_for_abi_crtn.entries);
                            crtn = func_0042FD7C(mkstr("crtn.o", arg2, NULL), dirs_for_abi_crtn.entries);
                            cxx_init =
                                func_0042FD7C(mkstr(exception_handling ? "c++init_eh.o" : "c++init.o", arg2, NULL),
                                              dirs_for_abi_crtn.entries);
                            delta_init = func_0042FD7C(mkstr("delta_init.o", arg2, NULL), dirs_for_abi_crtn.entries);
                        } else if (non_shared != 0) {
                            crtx = func_0042FD7C(mkstr(MCRTX, arg2, NULL), dirs_for_nonshared_crtn.entries);
                            crtn = func_0042FD7C(mkstr("crtn.o", arg2, NULL), dirs_for_nonshared_crtn.entries);
                            cxx_init =
                                func_0042FD7C(mkstr(exception_handling ? "c++init_eh.o" : "c++init.o", arg2, NULL),
                                              dirs_for_nonshared_crtn.entries);
                            delta_init =
                                func_0042FD7C(mkstr("delta_init.o", arg2, NULL), dirs_for_nonshared_crtn.entries);
                        } else {
                            crtx = func_0042FD7C(mkstr(MCRTX, arg2, NULL), dirs_for_crtn.entries);
                            crtn = func_0042FD7C(mkstr("crtn.o", arg2, NULL), dirs_for_crtn.entries);
                            cxx_init =
                                func_0042FD7C(mkstr(exception_handling ? "c++init_eh.o" : "c++init.o", arg2, NULL),
                                              dirs_for_crtn.entries);
                            delta_init = func_0042FD7C(mkstr("delta_init.o", arg2, NULL), dirs_for_crtn.entries);
                        }
                    } else if (abi_flag != 0) {
                        crtx = func_0042FD7C(CRTX, dirs_for_abi_crtn.entries);
                        crtn = func_0042FD7C("crtn.o", dirs_for_abi_crtn.entries);
                        cxx_init =
                            func_0042FD7C(exception_handling ? "c++init_eh.o" : "c++init.o", dirs_for_abi_crtn.entries);
                        delta_init = func_0042FD7C("delta_init.o", dirs_for_abi_crtn.entries);
                    } else if (non_shared != 0) {
                        crtx = func_0042FD7C(CRTX, dirs_for_nonshared_crtn.entries);
                        crtn = func_0042FD7C("crtn.o", dirs_for_nonshared_crtn.entries);
                        cxx_init = func_0042FD7C(exception_handling ? "c++init_eh.o" : "c++init.o",
                                                 dirs_for_nonshared_crtn.entries);
                        delta_init = func_0042FD7C("delta_init.o", dirs_for_nonshared_crtn.entries);
                    } else {
                        crtx = func_0042FD7C(CRTX, dirs_for_crtn.entries);
                        crtn = func_0042FD7C("crtn.o", dirs_for_crtn.entries);
                        cxx_init =
                            func_0042FD7C(exception_handling ? "c++init_eh.o" : "c++init.o", dirs_for_crtn.entries);
                        delta_init = func_0042FD7C("delta_init.o", dirs_for_crtn.entries);
                    }
                    break;

                case 'P':
                    if (arg1 != NULL) {
                        libp = ((arg2 != NULL) && (*arg2 != 0)) ? mkstr("-L", arg1, "-B", arg2, LibP, NULL)
                                                                : mkstr("-L", arg1, LibP, NULL);
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

                case '1':
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

                case 'E':
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && (*arg2 != 0)) {
                            libexc = mkstr("-L", arg1, "-B", arg2, LibExc, NULL);
                            libmld = mkstr("-L", arg1, "-B", arg2, LibMld, NULL);
                        } else {
                            libexc = mkstr("-L", arg1, LibExc, NULL);
                            libmld = mkstr("-L", arg1, LibMld, NULL);
                        }
                        libexc_b = mkstr(arg1, "libexc.b", arg2, NULL);
                    } else {
                        if ((arg2 != NULL) && (*arg2 != 0)) {
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

                case 'W':
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && (*arg2 != 0)) {
                            libdw = mkstr("-L", arg1, "-B", arg2, LibDw, NULL);
                        } else {
                            libdw = mkstr("-L", arg1, LibDw, NULL);
                        }
                        libdw_path = mkstr(arg1, "libdw.a", arg2, NULL);
                        libdw_b = mkstr(arg1, "libdw.b", arg2, NULL);
                    } else {
                        if ((arg2 != NULL) && (*arg2 != 0)) {
                            if (non_shared != 0) {
                                libdw = mkstr("-L", comp_target_root, "usr/lib/nonshared/", currcomp, " -B", arg2,
                                              LibDw, NULL);
                            } else {
                                libdw = mkstr("-L", comp_target_root, "usr/lib/", currcomp, " -B", arg2, LibDw, NULL);
                            }
                        } else if (non_shared != 0) {
                            libdw = mkstr("-L", comp_target_root, "usr/lib/", currcomp, LibDw, NULL);
                        } else {
                            libdw = mkstr("-L", comp_target_root, "usr/lib/", currcomp, LibDw, NULL);
                        }
                        if (non_shared != 0) {
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
                        if ((arg2 != NULL) && (*arg2 != 0)) {
                            libxmalloc = mkstr("-L", arg1, " -B", arg2, LibXmalloc, NULL);
                        } else {
                            libxmalloc = mkstr("-L", arg1, LibXmalloc, NULL);
                        }
                        libxmalloc_b = mkstr(arg1, "libxmalloc.b", arg2, NULL);
                    } else {
                        libxmalloc = "-lxmalloc";
                        if (non_shared != 0) {
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
                        if (non_shared != 0) {
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
                            if ((arg2 != NULL) && (*arg2 != 0)) {
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

                case 'M':
                    if (arg1 != NULL) {
                        switch (chip_targ) {
                            default:
                            case 0:
                                if ((arg2 != NULL) && (*arg2 != 0)) {
                                    libm = mkstr(arg1, " -B", arg2, LibM, NULL);
                                } else {
                                    libm = mkstr("-L", arg1, LibM, NULL);
                                }
                                libm_b = mkstr(arg1, "libm.b", arg2, NULL);
                                break;
                            case 1:
                                libm = mkstr(arg1, "libm_mips2.a", arg2, NULL);
                                libm_b = mkstr(arg1, "libm_mips2.b", arg2, NULL);
                                break;
                            case 2:
                                libm = mkstr(arg1, "libm_mips3.a", arg2, NULL);
                                libm_b = mkstr(arg1, "libm_mips3.b", arg2, NULL);
                                break;
                        }
                    } else {
                        switch (chip_targ) {
                            default:
                            case 0:
                                libm = "-lm";
                                if (non_shared != 0) {
                                    libm_b =
                                        mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm.b", arg2, NULL);
                                } else {
                                    libm_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libm.b", arg2, NULL);
                                }
                                break;
                            case 1:
                                if (non_shared != 0) {
                                    libm = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm_mips2.a", arg2,
                                                 NULL);
                                    libm_b = mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm_mips2.b",
                                                   arg2, NULL);
                                } else {
                                    libm = mkstr(comp_target_root, "usr/lib/", currcomp, "libm_mips2.a", arg2, NULL);
                                    libm_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libm_mips2.b", arg2, NULL);
                                }
                                break;
                            case 2:
                                if (non_shared != 0) {
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
                        if ((arg2 != NULL) && (*arg2 != 0)) {
                            libF77 = mkstr("-L", arg1, " -B", arg2, LibF77, NULL);
                        } else {
                            libF77 = mkstr("-L", arg1, LibF77, NULL);
                        }
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

                case 'I':
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && (*arg2 != 0)) {
                            libI77 = mkstr("-L", arg1, " -B", arg2, LibI77, NULL);
                        } else {
                            libI77 = mkstr("-L", arg1, LibI77, NULL);
                        }
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

                case 'S':
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && (*arg2 != 0)) {
                            libisam = mkstr("-L", arg1, " -B", arg2, LibIsam, NULL);
                        } else {
                            libisam = mkstr("-L", arg1, LibIsam, NULL);
                        }
                        libisam_b = mkstr(arg1, "libisam.b", arg2, NULL);
                    } else {
                        libisam = "-lisam";
                        if (non_shared != 0) {
                            libisam_b =
                                mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libisam.b", arg2, NULL);
                        } else {
                            libisam_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libisam.b", arg2, NULL);
                        }
                    }
                    break;

                case 'U':
                    if (arg1 != NULL) {
                        if ((arg2 != NULL) && (*arg2 != 0)) {
                            libU77 = mkstr("-L", arg1, " -B", arg2, LibU77, NULL);
                        } else {
                            libU77 = mkstr("-L", arg1, LibU77, NULL);
                        }
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

                default:
                    error(1, NULL, 0, NULL, 0, "Unknown character in -t%c\n", *var_s1);
                    exit(2);
                    break;
            }
        }
    }
}

// function newrunlib # 9
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
    } else if (targetsex == BIGENDIAN) {
        runlib = "eb/";
    } else {
        runlib = "el/";
    }
    relocate_passes("rP1EXCOnMFISU", NULL, NULL);
}

// function compose_G0_libs # 10
void compose_G0_libs(const char* arg0) {
    for (; *arg0 != '\0'; arg0++) {
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

// function compose_reg_libs # 11
void compose_reg_libs(const char* arg0) {
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
                LibGProf1 = mkstr("libgprof", ".a", NULL);
                break;
            case 'X':
                LibXmalloc = mkstr("libxmalloc", ".a", NULL);
                break;
        }
    }
}

// function mkstr # 12
/*
 * The compiler built-in symbol _VA_INIT_STATE:
 *	-returns 1 if the va_alist marker is the first
 *		parameter in the parameter list, or
 *	-returns 2 if the va_alist marker is the second
 *		parameter in the parameter list, and the
 *		first parameter has type double, or
 *	-returns 0 otherwise.
 */
#define _VA_INIT_STATE 1

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
        error(1, NULL, 0, "mkstr ()", 0x38BC, "out of memory\n");
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
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
#endif /* PERMUTER */

#undef _VA_INIT_STATE

#define LIST_CAPACITY_INCR 20
#define LIST_INITIAL_CAPACITY LIST_CAPACITY_INCR

// function mklist # 13
// Initialise a specified list with capacity LIST_INITIAL_CAPACITY and length 0.
void mklist(list* arg0) {
    if ((arg0->entries = malloc(LIST_INITIAL_CAPACITY * sizeof(char*))) == NULL) {
        error(1, NULL, 0, "mklist ()", 14561, "out of memory\n");
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        exit(1);
    }
    arg0->capacity = LIST_INITIAL_CAPACITY;
    arg0->length = 0;
    *arg0->entries = NULL;
}

// function addstr # 14
// Add a single string entry to a list.
void addstr(list* arg0, char* str) {
    if ((arg0->length + 1) >= arg0->capacity) {
        if ((arg0->entries = realloc(arg0->entries, (arg0->capacity + LIST_CAPACITY_INCR) * sizeof(char*))) == 0) {
            error(1, NULL, 0, "addstr()", 14595, "out of memory\n");
            if (errno < sys_nerr) {
                error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
            }
            exit(1);
        }
        arg0->capacity += LIST_CAPACITY_INCR;
    }
    arg0->entries[arg0->length] = str;
    arg0->length++;
    arg0->entries[arg0->length] = NULL;
}

// function addspacedstr # 15
// Add a space-separated string to a list, dividing it up into separate entries by space characters (' ')
void addspacedstr(list* arg0, char* str) {
    char* str_end = str;

    do {
        str_end = strchr(str_end, ' ');
        if (str_end != NULL) {
            *str_end = '\0';
            str_end++;
        }
        if ((arg0->length + 1) >= arg0->capacity) {
            if ((arg0->entries = realloc(arg0->entries, (arg0->capacity + LIST_CAPACITY_INCR) * sizeof(char*))) ==
                NULL) {
                error(1, NULL, 0, "addspacedstr()", 14639, "out of memory\n");
                if (errno < sys_nerr) {
                    error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
                }
                exit(1);
            }
            arg0->capacity += LIST_CAPACITY_INCR;
        }
        arg0->entries[arg0->length] = str;
        arg0->length += 1;
        arg0->entries[arg0->length] = NULL;
    } while ((str = str_end) != NULL);
}

// function newstr # 16
/**
 * Copy a string
 *
 * @param src string to copy
 * @return char* mallocked pointer to copy
 */
char* newstr(const char* src) {
    char* dest = malloc(strlen(src) + 1);

    if (dest != NULL) {
        strcpy(dest, src);
    } else {
        error(1, NULL, 0, NULL, 0, "newstr: unable to malloc for string %s\n", src);
        exit(2);
    }
    return dest;
}

// function save_place # 17
int save_place(list* arg0) {
    int ret;

    if ((arg0->length + 1) >= arg0->capacity) {
        if ((arg0->entries = realloc(arg0->entries, (arg0->capacity + LIST_CAPACITY_INCR) * sizeof(char*))) == NULL) {
            error(1, NULL, 0, "save_place()", 14695, "out of memory\n");

            if (errno < sys_nerr) {
                error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
            }
            exit(1);
        }
        arg0->capacity += LIST_CAPACITY_INCR;
    }
    ret = arg0->length;
    arg0->length++;
    arg0->entries[arg0->length] = NULL;
    return ret;
}

// function set_place # 18
/**
 * Set a specified entry of a list to a particular string
 *
 * @param arg0 list to set entry of
 * @param str string to set entry to
 * @param place entry to write to
 */
void set_place(list* arg0, char* str, int place) {
    if ((place < 0) || (place >= arg0->length)) {
        error(0, NULL, 0, "set_place ()", 14726, "place out of range");
        exit(1);
    }
    arg0->entries[place] = str;
}

// function addlist # 19
// Append all the entries in arg1 to arg0.
void addlist(list* arg0, list* arg1) {
    int i;

    if ((arg0->length + arg1->length + 1) >= arg0->capacity) {
        if ((arg0->entries = realloc(arg0->entries,
                                     (arg0->capacity + arg1->capacity + LIST_CAPACITY_INCR) * sizeof(char*))) == NULL) {
            error(1, NULL, 0, "addlist ()", 14756, "out of memory\n");
            if (errno < sys_nerr) {
                error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
            }
            exit(1);
        }
        arg0->capacity += arg1->capacity + LIST_CAPACITY_INCR;
    }
    for (i = 0; i < arg1->length; i++) {
        if (arg1->entries[i] != NULL) {
            arg0->entries[arg0->length] = arg1->entries[i];
            arg0->length++;
        }
    }
    arg0->entries[arg0->length] = NULL;
}

// function adduldlist # 20
// Adds entries from arg1 and arg2 onto the end of arg0:
// - up to the first NULL from arg2,
// - then everything from arg1,
// - then the rest of arg2.
void adduldlist(list* arg0, list* arg1, list* arg2) {
    s32 sp3C;
    s32 sp38;

    if ((arg0->length + arg1->length + arg2->length + 1) >= arg0->capacity) {

        if ((arg0->entries =
                 realloc(arg0->entries, (arg0->capacity + arg1->capacity + arg2->capacity + LIST_CAPACITY_INCR) *
                                            sizeof(char*))) == NULL) {
            error(1, NULL, 0, "addlist ()", 14795, "out of memory\n");
            if (errno < sys_nerr) {
                error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
            }
            exit(1);
        }
        arg0->capacity += arg1->capacity + arg2->capacity + LIST_CAPACITY_INCR;
    }

    for (sp3C = 0; (sp3C < arg2->length) && (arg2->entries[sp3C] != NULL); sp3C++) {
        arg0->entries[arg0->length] = arg2->entries[sp3C];
        arg0->length++;
    }

    for (sp38 = 0; sp38 < arg1->length; sp38++) {
        if (arg1->entries[sp38] != NULL) {
            arg0->entries[arg0->length] = arg1->entries[sp38];
            arg0->length++;
        }
    }

    for (; sp3C < arg2->length; sp3C++) {
        if (arg2->entries[sp3C] != NULL) {
            arg0->entries[arg0->length] = arg2->entries[sp3C];
            arg0->length++;
        }
    }

    arg0->entries[arg0->length] = NULL;
}

// function nodup # 21
// Search for a string in a list. If found, return 0, else return 1.
s32 nodup(list* arg0, const char* str) {
    register s32 i;
    register char* entry;

    for (i = 0; i < arg0->length; i++) {
        entry = arg0->entries[i];
        if ((entry != NULL) && (strcmp(entry, str) == 0)) {
            return 0;
        }
    }

    return 1;
}

// function getsuf # 22
char getsuf(const char* path) {
    int suflen = 0; // Length of suffix
    int i;
    char ch;
    const char* str = path;

    while (ch = *path++) {
        if (ch == '/') {
            suflen = 0;
            str = path;
        } else {
            suflen++;
        }
    }

    if (suflen < 3) {
        return '\0';
    }

    if (path[-3] == '.') {
        if (path[-2] == 'C') {
            return 6; // ACK?
        }
        return path[-2];
    }

    for (i = suflen - 2; i > 0; i--) {
        if (str[i] == '.') {
            break;
        }
    }

    if (i == 0) {
        return '\0';
    }

    str = &str[i + 1];
    for (i = 0; suffixes[i].unk0 != NULL; i++) {
        if (strcmp(str, suffixes[i].unk0) == 0) {
            return suffixes[i].unk4;
        }
    }

    if (strcmp(str, "for") == 0) {
        return 'f';
    }
    if (strcmp(str, "FOR") == 0) {
        return 'F';
    }
    return '\0';
}

// function mksuf # 23
char* mksuf(const char* path, char value) {
    s32 i; // sp54
    s32 k; // sp50, also suffix length
    size_t sp4C;
    char* sp48;
    char* sp44;
    char* sp40;
    const char* sp3C = NULL;
    char ch; // sp38

    if (value < 8) {
        for (i = 0; suffixes[i].unk0 != NULL; i++) {
            if (suffixes[i].unk4 == value) {
                sp3C = suffixes[i].unk0;
                break;
            }
        }

        if (sp3C == NULL) {
            error(0, NULL, 0, "mksuf ()", 14938, "passed an unknown suffix value: %s\n", value);
            exit(4);
        }
        sp4C = strlen(sp3C);
    } else {
        sp4C = 0;
    }

    i = 0;
    sp40 = sp44 = sp48 = savestr(path, sp4C);

    while (ch = *sp44++) {
        if (ch == '/') {
            i = 0;
            sp40 = sp44;
        } else {
            i++;
        }
    }

    if ((i >= 3) && (sp44[-3] == '.')) {
        if (value < 8) {
            strcpy(sp44 - 2, sp3C);
        } else {
            sp44[-2] = value;
            sp44[-1] = 0;
        }
    } else {
        for (k = i - 2; k > 0; k--) {
            if (sp40[k] == '.') {
                break;
            }
        }

        if (k == 0) {
            error(1, NULL, 0, "mksuf ()", 14977, "Bad file name, no suffix: %s\n", path);
            exit(4);
        }
        sp40 = &sp40[k + 1];
        if (value < 8) {
            strcpy(sp40, sp3C);
        } else {
            sp40[0] = value;
            sp40[1] = 0;
        }
    }

    sp44 = sp48;
    while (*sp48 != '\0') {
        if (*sp48++ == '/') {
            sp44 = sp48;
        }
    }
    return sp44;
}

// function savestr # 24
// Copy a string, adding extra_length bytes to the allocation.
char* savestr(const char* src, size_t extra_length) {
    char* dest = malloc(strlen(src) + extra_length + 1);

    if (dest == NULL) {
        error(1, NULL, 0, "savestr ()", 15014, "out of memory\n");
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        exit(1);
    }
    strcpy(dest, src);
    return dest;
}

// function mktempstr # 25
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
    //! @bug 5 Xs instead of 6
    tempstr[30] = mktemp(mkstr(tmpdir, "ctmelfXXXXX", NULL));
    tempstr[31] = mktemp(mkstr(tmpdir, "ctmkXXXXXX", NULL));

    tempstr[33] = mktemp(mkstr(tmpdir, "ctmcmdXXXXXX", NULL));

    if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (nofilt == 0) &&
        (access(filter, EX_OK) == 0)) {
        tempstr[32] = mktemp(mkstr(tmpdir, "ctmfiltXXXXXX", NULL));
    } else {
        tempstr[32] = NULL;
    }
}

// function run # 26
int run(char* arg0, char* const arg1[], char* arg2, char* arg3, char* arg4) {
    char* const* spA4;
    pid_t spA0;
    int sp9C;
    int sp98;
    int sp94;
    int sp90;
    int sp8C;
    SIG_PF sp88;
    SIG_PF sp84;
    int sp80;
    int sp7C;
    const char* sp78;
    int sp74;
    sysset_t sp34;
    register int var_s0;

    if (vflag != 0) {
        fprintf(stderr, "%s ", arg0);
        spA4 = arg1 + 1;
        while (*spA4 != 0) {
            fprintf(stderr, "%s ", *spA4++);
        }

        if (arg2 != NULL) {
            fprintf(stderr, "< %s ", arg2);
        }
        if (arg3 != NULL) {
            fprintf(stderr, "> %s ", arg3);
        }
        fprintf(stderr, "\n");
    }
    if (time_flag != 0) {
        settimes();
    }
    if (execute_flag == 0) {
        return 0;
    }
    if ((memory_flag != 0) && (pipe(B_1000EC98) < 0)) {
        error(1, NULL, 0, NULL, 0, "pipe failed for -showm");
        return -1;
    }

    spA0 = fork();
    if (spA0 == -1) { // fork failed
        error(1, NULL, 0, NULL, 0, "no more processes\n");
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        return -1;
    }

    if (spA0 == 0) {
        if (memory_flag != 0) {
            func_00432BDC();
        }

        if (arg2 != NULL) {
            sp94 = open(arg2, O_RDONLY);
            if (sp94 == -1) {
                error(1, NULL, 0, NULL, 0, "can't open input file: %s\n", arg2);
                if (errno < sys_nerr) {
                    error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
                }
                cleanup();
                exit(1);
            }
            dup2(sp94, fileno_unlocked(stdin));
        }

        if (arg3 != NULL) {
            sp90 = creat(arg3, S_IRWXU | S_IRWXG | S_IRWXO); // 0777
            if (sp90 == -1) {
                error(1, NULL, 0, NULL, 0, "can't create output file: %s\n", arg3);
                if (errno < sys_nerr) {
                    error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
                }
                cleanup();
                exit(1);
            }
            dup2(sp90, fileno_unlocked(stdout));
        }

        if (arg4 != NULL) {
            sp8C = creat(arg4, S_IRWXU | S_IRWXG | S_IRWXO); // 0777
            if (sp8C == -1) {
                error(1, NULL, 0, NULL, 0, "can't create error file: %s\n", arg4);
                if (errno < sys_nerr) {
                    error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
                }
                cleanup();
                exit(1);
            }
            dup2(sp8C, fileno_unlocked(stderr));
        }

        execvp(arg0, arg1);
        sp78 = func_00430414(arg0, 1);
        if ((errno == ENOENT) && (sp78 != NULL)) {
            error(1, NULL, 0, NULL, 0, "%s is not installed (could not find %s).\n", sp78, arg0);
        } else {
            sp78 = func_00430414(arg0, 0);
            if ((errno == ENOENT) && (sp78 != NULL)) {
                error(1, NULL, 0, NULL, 0, "%s may not be installed (could not find %s).\n", sp78, arg0);
            } else {
                error(1, NULL, 0, NULL, 0, "can't find or exec: %s\n", arg0);
                if (errno < sys_nerr) {
                    error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
                }
            }
        }
        cleanup();
        exit(1);
    } else {
        sp84 = sigset(SIGINT, SIG_IGN);
        sp88 = sigset(SIGTERM, SIG_IGN);

        if (memory_flag != 0) {
            sp74 = func_00432940(spA0);
            sp7C = ioctl(sp74, PIOCMAP_SGI, &D_1000C1C8);
            if (sp7C < 0) {
                perror("PIOCMAP_SGI");
                kill(spA0, SIGKILL);
                return -1;
            }

            var_s0 = 0x10;
            while (var_s0 != 0) {
                var_s0--;
                sp34.word[var_s0] = 0;
            }

            if (ioctl(sp74, PIOCSEXIT, &sp34) < 0) {
                perror("PIOCSEXIT");
                kill(spA0, SIGKILL);
                return -1;
            }

            ioctl(sp74, PIOCRUN, NULL);
            close(sp74);
        }

        while ((sp9C = wait(&sp80)) != spA0) {
            if (sp9C == -1) {
                return -1;
            }
        }

        sigset(SIGINT, sp84);
        sigset(SIGTERM, sp88);

        if (time_flag != 0) {
            dotime(arg0);
        }

        if (memory_flag != 0) {
            func_00432D3C(arg0, sp7C);
        }

        if (WIFSTOPPED(sp80)) {
            sp98 = WSTOPSIG(sp80);
            fprintf(stderr, "STOPPED signal received from: %s ", arg0);
            fprintf(stderr, " (Signal %d) ", sp98);
            fprintf(stderr, " Process  %d abandoned\n", sp9C);
            return sp98;
        }

        if (WIFEXITED(sp80)) {
            return WEXITSTATUS(sp80);
        }

        if (WIFSIGNALED(sp80)) {
            sp98 = WTERMSIG(sp80);
            fprintf(stderr, "Fatal error in: %s ", arg0);
            printf(" child died due to signal %d.\n", sp98);
            if (sp98 == SIGKILL) {
                printf("Probably caused by running out of swap space -- check /usr/adm/SYSLOG.\n");
                exit(sp98);
            }
            if (sp98 == SIGINT) {
                cleanup();
                exit(3);
            }
            fprintf(stderr, "Fatal error in: %s ", arg0);
            fprintf(stderr, " Signal %d ", sp98);
            if (sp80 & WCOREFLAG) { // Cannot be WCOREDUMP
                fprintf(stderr, "- core dumped\n");
            } else {
                fprintf(stderr, "\n");
            }
            exit(sp98);
        } else {
            return 0;
        }
    }
}

// function edit_src # 27
s32 edit_src(const char* arg0, char* arg1, s32 arg2) {
    s32 pad[3];
    char* sp58;
    pid_t fokrPid;
    pid_t sp50;
    s32 temp_t7; // sp4C
    SIG_PF sp48;
    SIG_PF sp44;
    s32 stat_loc;

    fokrPid = fork();
    if (fokrPid == (pid_t)-1) { // fork failed
        error(1, NULL, 0, NULL, 0, "fork to edit failed\n");
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        return -1;
    }

    if (fokrPid == (pid_t)0) { // child process

        if (editflag == 2) {
            get_lino(sp58, arg1, arg2);
            execlp(arg0, arg0, sp58, arg1, "-l", tempstr[25], "-f", "err-window", (char*)NULL);
        } else if (xserver == 0) {
            execlp(arg0, arg0, "+1", errout, arg1, (char*)NULL);
        } else {
            execlp("xterm", "xterm", "-display", xserver, "-ls", "-e", arg0, "+1", errout, arg1, (char*)NULL);
        }
        error(1, NULL, 0, NULL, 0, "failed to exec: %s\n", arg0);
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }

        exit(1);
    } else { // this process, fokrPid is the pid of the child process

        sp44 = sigset(SIGINT, SIG_IGN);
        sp48 = sigset(SIGTERM, SIG_IGN);
        sp50 = wait(&stat_loc);
        while (sp50 != fokrPid) {
            if (sp50 == -1) {
                return -1;
            }
            sp50 = wait(&stat_loc);
        }

        sigset(SIGINT, sp44);
        sigset(SIGTERM, sp48);
        temp_t7 = stat_loc & 0xFF;
        if ((temp_t7 != 0) && (temp_t7 != 2)) {
            fprintf(stderr, "Fatal error in: %s ", arg0);
            printf(" Signal %d ", temp_t7);
            if (stat_loc & WCOREFLAG) { // Cannot be WCOREDUMP
                fprintf(stderr, "- core dumped\n");
            } else {
                fprintf(stderr, "\n");
            }
            cleanup();
            exit(temp_t7);
        }
        if (temp_t7 == 2) {
            cleanup();
            exit(3);
        }

        return stat_loc & 0xFF00;
    }
}

// function get_lino # 28
#define GET_LINO_BUF_SIZE 0x800
// arg2 is probably a size_t
void get_lino(char* arg0, const char* arg1, s32 arg2) {
    char* sp83C;
    int sp838;
    char* sp834 = arg0;
    char* sp830;
    char sp30[GET_LINO_BUF_SIZE];

    *arg0 = '+';
    sp834++;
    sp83C = open(errout, O_RDONLY);
    sp838 = read(sp83C, &sp30, GET_LINO_BUF_SIZE);
    close(sp83C);

    if (sp838 < GET_LINO_BUF_SIZE) {
        sp30[sp838] = 0;
    } else {
        sp30[GET_LINO_BUF_SIZE - 1] = 0;
    }

    switch (arg2) {
        case 1:
        case 2:
            for (sp830 = sp30; sp830 < sp30 + sp838; sp830++) {
                // clang-format off
                if ((strncmp(sp830, ": Error: ", 9) == 0) 
                    && ((sp830 = strchr(sp830, ',')) != NULL) 
                    && (strncmp(sp830 - strlen(arg1), arg1, strlen(arg1)) == 0) 
                    && (strncmp(sp830, ", line ", 7) == 0)) {
                    // clang-format on
                    sp830 += 7;
                    while (isdigit(*sp830) && ((sp834 - arg0) <= 10)) {
                        *sp834++ = *sp830++;
                    }
                    break;
                }
            }
            break;

        case 3:
            for (sp830 = sp30; sp830 < sp30 + sp838; sp830++) {
                if (strncmp(sp830, "Error on line ", 14) == 0) {
                    sp830 += 14;
                    while (isdigit(*sp830) && ((sp834 - arg0) <= 10)) {
                        *sp834++ = *sp830++;
                    }
                    break;
                }
            }
            break;

        case 5:
        case 6:
            for (sp830 = sp30; sp830 < sp30 + sp838; sp830++) {
                if (strncmp(sp830, "ERROR ", 6) == 0) {
                    sp830 += 6;
                    break;
                }
            }

            for (; sp830 < sp30 + sp838; sp830++) {
                if (strncmp(sp830, " LINE ", 6) == 0) {
                    sp830 += 6;
                    while (isdigit(*sp830) && ((sp834 - arg0) <= 10)) {
                        *sp834++ = *sp830++;
                    }
                    break;
                }
            }
            break;

        default:
            break;
    }

    if ((arg0 + 1) < sp834) {
        sp834[0] = 0;
    } else {
        sp834[0] = '1';
        sp834[1] = 0;
    }
}

// function show_err # 29
#define SHOW_ERR_BUF_SIZE 0x10000
void show_err(const char* path) {
    int desc;
    int bytes_read;
    char buf[SHOW_ERR_BUF_SIZE];

    desc = open(path, O_RDONLY);
    bytes_read = read(desc, buf, SHOW_ERR_BUF_SIZE);
    close(desc);

    if (bytes_read < SHOW_ERR_BUF_SIZE) {
        buf[bytes_read] = '\0';
    } else {
        buf[SHOW_ERR_BUF_SIZE - 1] = '\0';
    }
    fprintf(stderr, "%s\n", buf);
}
#undef BUF_SIZE

// function handler # 30
void handler(void) {
    cleanup();
    exit(3);
}

// function cleanup # 31
void cleanup(void) {
    if (Kflag == 0) {
        if (passout != NULL) {
            unlink(passout);
        }
        if (passin != NULL) {
            char sp27 = getsuf(passin);
            if (((sp27 == 0)) || ((sp27 != srcsuf) && (sp27 != 'm'))) {
                if (Eflag == 0) {
                    unlink(passin);
                }
            }
        }
        if (tmpst != 0) {
            if (symtab != NULL) {
                unlink(symtab);
            }
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
        if (editflag != 0) {
            unlink(errout);
            if (editflag == 2) {
                unlink(tempstr[25]);
            }
        }
        if (compiler == 1) {
            unlink(tempstr[33]);
        }
    }
}

// function whats # 32
void whats(void) {
    s32 sp24 = runerror;

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
    printf("\tMips Computer Systems %d.%d\n", 7, 10);
}

// function settimes # 33
void settimes(void) {
    time0 = times(&tm0);
}

// function dotime # 34
#define CLOCK_TICKS 100

void dotime(const char* programName) {
    clock_t time1; // sp6C;
    clock_t clockTimeDiff;
    f64 milis;      // sp60
    f64 seconds;    // sp58
    struct tms tm1; // sp48;

    time1 = times(&tm1);
    milis = (f64)(tm1.tms_utime + tm1.tms_cutime - tm0.tms_utime - tm0.tms_cutime) / CLOCK_TICKS;
    seconds = (f64)(tm1.tms_stime + tm1.tms_cstime - tm0.tms_stime - tm0.tms_cstime) / CLOCK_TICKS;
    clockTimeDiff = time1 - time0;
    fprintf(stderr, "%s phase time: %.2fu %.2fs %u:%04.1f %.0f%%\n", programName, milis, seconds,
            clockTimeDiff / (60 * CLOCK_TICKS), (f64)(clockTimeDiff % (60 * CLOCK_TICKS)) / CLOCK_TICKS,
            ((milis + seconds) / ((f64)clockTimeDiff / CLOCK_TICKS)) * 100.0);
}

// function func_0042FD7C # 35
// Search for a lib in directories (?)
static char* func_0042FD7C(const char* name, char** dirs) {
    s32 fildes;
    char* path;

    for (; *dirs != NULL; dirs++) {
        if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
            fildes = open(path = mkstr(*dirs, "/DCC", runlib, name, NULL), 0, 0);
            if (fildes >= 0) {
                close(fildes);
                return path;
            }
        }

        fildes = open(path = mkstr(*dirs, runlib, name, NULL), 0, 0);
        if (fildes >= 0) {
            close(fildes);
            return path;
        }
    }

    if (abi_flag != 0) {
        path = mkstr("/", "usr/lib/abi", runlib, name, NULL);
    } else if (non_shared != 0) {
        path = mkstr("/", "usr/lib/nonshared", runlib, name, NULL);
    } else {
        path = mkstr("/", "usr/lib", runlib, name, NULL);
    }
    return path;
}

// function isdir # 36
int isdir(const char* path) {
    s32 spAC;
    struct stat statbuf;

    spAC = stat(path, &statbuf);
    if (spAC == -1) {
        return 0;
    }
    if ((statbuf.st_mode & 0xF000) == 0x4000) {
        return 1;
    }
    return 0;
}

// function regular_not_writeable # 37
int regular_not_writeable(const char* arg0) {
    s32 sp24;

    if (regular_file(arg0) != 1) {
        return 0;
    }
    sp24 = open(arg0, 2, 0777);
    if (sp24 >= 0) {
        close(sp24);
        return 0;
    }
    return 1;
}

// function regular_file # 38
// Needs stat.h
int regular_file(const char* path) {
    s32 spAC;
    struct stat statbuf;

    spAC = stat(path, &statbuf);
    if (spAC == -1) {
        return -1;
    }
    if ((statbuf.st_mode & 0xF000) != 0x8000) {
        return 0;
    }
    return 1;
}

// function basename # 39
static char B_1000E5E0[0x400];

// Obtain the base name of a file path, i.e. the part after the final '/'
char* basename(const char* path) {
    register char* ret;
    register char* str = B_1000E5E0;
    register size_t len;

    if ((path == NULL) || (*path == 0)) {
        return strcpy(str, ".");
    }

    ret = strcpy(str, path);
    len = strlen(ret);
    ret += len;

    while ((ret != str) && (*--ret == '/')) {
        *ret = '\0';
    }

    while (ret != str) {
        if (*--ret == '/') {
            ret++;
            return ret;
        }
    }

    return ret;
}

// function dirname # 40
// Obtain the directory name of a file path, i.e. the part before the final '/'
const char* dirname(const char* path) {
    register char* ret;
    register char* str = B_1000E5E0;
    register size_t len;

    if ((path == NULL) || (*path == 0)) {
        return strcpy(str, ".");
    }

    ret = strcpy(str, path);
    len = strlen(ret);
    ret += len;

    while ((ret != str) && *--ret == '/') {}

    if ((ret == str) && (*ret == '/')) {
        return strcpy(str, "/");
    }

    while (ret != str) {
        if (*--ret == '/') {
            if (ret == str) {
                return strcpy(str, "/");
            }
            while (*ret == '/') {
                ret--;
            }
            ret++;
            *ret = 0;
            return str;
        }
    }

    return strcpy(str, ".");
}

struct _struct_prod_name_0xC {
    /* 0x0 */ const char* unk0; // name?
    /* 0x4 */ const char* unk4; // full path?
    /* 0x8 */ const char* unk8; // description?
};                              // size = 0xC

struct _struct_prod_name_0xC prod_name[] = {
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

static char* D_1000C2E8 = NULL;
static char* D_1000C2EC = NULL;
static char* D_1000C2F0 = NULL; // basename of progname (?)

// function func_00430414 # 41
static const char* func_00430414(char* arg0, int arg1) {
    int i;
    int sp28;
    char* sp24;
    const char* sp20;

    if (arg1 != 0) {
        sp24 = arg0;
    } else {
        sp24 = strrchr(arg0, '/');
        if (sp24 != NULL) {
            sp24++;
        }
    }

    sp28 = 20;
    for (i = 0; i < sp28; i++) {
        if (arg1 != 0) {
            sp20 = prod_name[i].unk4;
        } else {
            sp20 = prod_name[i].unk0;
        }
        if (strcmp(sp24, sp20) == 0) {
            return prod_name[i].unk8;
        }
    }
    return NULL;
}

// function force_use_cfront # 42
static int D_1000BF7C;
static int D_1000BF90;

extern char* comp_host_root;
extern int exception_handling;
extern list execlist;

int force_use_cfront(int argc, char** argv) {
    int i;
    char* sp28 = getenv("USE_CFRONT");
    int sp24 = 0;

    if ((sp28 != NULL) && (*sp28 != '0')) {
        return 1;
    }

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-exceptions") == 0) {
            D_1000BF7C = 1;
        }
        if ((D_1000BF7C == 0) && (exception_handling == 0) &&
            ((strcmp(argv[i], "-F") == 0) || (strcmp(argv[i], "-Fc") == 0))) {
            return 1;
        }
        // clang-format off
        if ((strcmp(argv[i], "-use_cfront") == 0) 
            || (strcmp(argv[i], "-v2") == 0) 
            || (strcmp(argv[i], "+I") == 0) 
            || (strncmp(argv[i], "-.", 2) == 0)) {
            // clang-format on
            return 1;
        }
    }
    return 0;
}

// function exec_OCC # 43
void exec_OCC(int argc, char** argv) {
    char spB8[0x400];
    char pad[0x88]; // !

    sprintf(spB8, "%susr/bin/OCC", comp_host_root);
    *argv = spB8;
    execv(spB8, argv);
    error(2, NULL, 0, NULL, 0, "could not exec %s", spB8);
}

// function add_cxx_symbol_options # 44
int add_cxx_symbol_options(void) {
    addstr(&execlist, "-cxx");
    if ((D_1000BF90 == 0) && (strcmp(LD, "old_ld") != 0)) {
        addstr(&execlist, "-woff");
        addstr(&execlist, "134");
    }
    return 0;
}

// function init_curr_dir # 45

void init_curr_dir(void) {
    if (D_1000C2F0 == 0) {
        D_1000C2F0 = strrchr(progname, '/');
        if (D_1000C2F0 == 0) {
            D_1000C2F0 = progname;
        } else {
            D_1000C2F0++;
        }
    }
    if (D_1000C1D0 == NULL) {
        D_1000C1D0 = getcwd(NULL, 0x400);
        if (D_1000C1D0 == NULL) {
            D_1000C1D0 = getenv("PWD");
            if (D_1000C1D0 == NULL) {
                D_1000C1D0 = ".";
            }
        }
        if (strncmp(D_1000C1D0, "/tmp_mnt", 8) == 0) {
            D_1000C1D0 += 8;
        }
    }
}

// function full_path # 46
char* full_path(const char* relative_path) {
    char* path;

    init_curr_dir();
    if (*relative_path == '/') {
        path = mkstr(relative_path, NULL);
    } else {
        path = mkstr(D_1000C1D0, "/", relative_path, 0);
    }
    return path;
}

// function add_static_opt # 47
list staticopts;

void add_static_opt(char* opt) {
    if (D_1000BF88 == 0) {
        addstr(&staticopts, opt);
    }
}

// function record_static_fileset # 48
static char* D_1000BF80;
static char* D_1000BF84;
static char* D_1000C2E8;
static char* D_1000C2EC;
char* tmpdir;

void record_static_fileset(s32 arg0) {
    s32 sp28E4;
    FILE* sp28E0;
    FILE* sp28DC;
    s32 sp28D8;
    char spD8[0x2800];
    char* spD4;
    size_t spD0;
    char spBC[20];
    struct stat sp34;

    sprintf(spBC, ".%d", getpid());

    if (D_1000BF80 == NULL) {
        D_1000BF80 = "";
    }

    if (D_1000BF84 == NULL) {
        D_1000BF84 = mkstr("cvstatic.fileset", NULL);
    }

    if ((*D_1000BF84 == '/') || (*D_1000BF80 == 0)) {
        D_1000C2E8 = mkstr(D_1000BF84, NULL);
    } else {
        D_1000C2E8 = mkstr(D_1000BF80, D_1000BF84, NULL);
    }

    D_1000C2EC = mkstr(tmpdir, "cvstatic.fileset", &spBC, 0);
    spD4 = full_path(arg0);
    spD0 = strlen(spD4);

    if (vflag != 0) {
        fprintf(stderr, "Static fileset: %s %s", spD4, D_1000C2F0);
        for (sp28E4 = 0; sp28E4 < staticopts.length; sp28E4++) {
            fprintf(stderr, " %s", staticopts.entries[sp28E4]);
        }
        fprintf(stderr, "\n");
    }

    sp28E0 = fopen(D_1000C2EC, "w+");
    if (sp28E0 == NULL) {
        error(1, 0, 0, "record_static_fileset", 0, "could not open cvstatic fileset temp file %s\n", D_1000C2EC);
        perror(D_1000C2F0);
        cleanup();
        exit(1);
    }

    sp28D8 = open(D_1000C2E8, 0x102, 0777);
    if (sp28D8 < 0) {
        error(1, 0, 0, "record_static_fileset", 0, "could not open or create cvstatic fileset file %s\n", D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }

    if (flock(sp28D8, 2) < 0) {
        error(1, 0, 0, "record_static_fileset", 0, "error in locking cvstatic fileset file %s\n", D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }

    if (fstat(sp28D8, &sp34) < 0) {
        error(1, 0, 0, "record_static_fileset", 0, "could not fstat cvstatic fileset file %s\n", D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }

    if (sp34.st_size == 0) {
        fprintf(sp28E0, "-cvstatic\n");
    }

    sp28DC = fdopen(sp28D8, "r+");
    if (sp28DC == NULL) {
        error(1, 0, 0, "record_static_fileset", 0, "could not fdopen cvstatic fileset file %s\n", D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }

    while (fgets(spD8, 0x2800, sp28DC) != 0) {
        if ((strncmp(spD8, spD4, spD0) != 0) || !(__ctype[spD8[spD0] + 1] & 8)) {
            fputs(spD8, sp28E0);
        }
    }
    fprintf(sp28E0, "%s %s", spD4, D_1000C2F0);

    for (sp28E4 = 0; sp28E4 < staticopts.length; sp28E4++) {
        fprintf(sp28E0, " %s", staticopts.entries[sp28E4]);
    }
    fprintf(sp28E0, "\n");

    free(spD4);
    rewind(sp28DC);
    rewind(sp28E0);
    ftruncate(sp28DC->_file, 0);

    while ((sp28E4 = fread(spD8, 1, 0x2800, sp28E0)) > 0) {
        if (fwrite(&spD8, 1, sp28E4, sp28DC) != sp28E4) {
            error(1, 0, 0, "record_static_fileset", 0, "error in writing cvstatic fileset file %s\n", D_1000C2E8);
            perror(D_1000C2F0);
            unlink(D_1000C2EC);
            cleanup();
            exit(1);
        }
    }

    fclose(sp28DC);
    fclose(sp28E0);
    unlink(D_1000C2EC);
    free(D_1000C2E8);
    free(D_1000C2EC);
}

// function touch # 49
// Needs utime.h
int touch(const char* arg0) {
    time_t curtime = time(NULL);
    struct utimbuf sp34;
    char* str;

    init_curr_dir();
    if (vflag != 0) {
        fprintf(stderr, "%s: touch %s\n", D_1000C2F0, arg0);
    }
    sp34.modtime = curtime;
    sp34.actime = curtime;
    if (utime(arg0, &sp34) < 0) {
        str = malloc(strlen(arg0) + strlen(D_1000C2F0) + 10);
        sprintf(str, "%s: touch %s", D_1000C2F0, arg0);
        perror(str);
        free(str);
        return -1;
    }
    return 0;
}

// function add_prelinker_objects # 50
void add_prelinker_objects(list* arg0, list* arg1) {
    int i;

    for (i = 0; i < arg1->length; i++) {
        if ((arg1->entries[i][0] == '-') && (arg1->entries[i][1] != 'l') && (arg1->entries[i][1] != 'L')) {
            if (1) {} // FAKE

            if (strcmp(arg1->entries[i], "-nostdlib") == 0) {
                addstr(arg0, mkstr("-YB", NULL));
            } else if (strcmp(arg1->entries[i], "-objectlist") == 0) {
                addstr(arg0, mkstr("-YO=", arg1->entries[i + 1], NULL));
                i++;
            } else if (strcmp(arg1->entries[i], "-B") == 0) {
                i++;
                if (strcmp(arg1->entries[i], "static") == 0) {
                    addstr(arg0, mkstr("-Bstatic", NULL));
                } else if (strcmp(arg1->entries[i], "dynamic") == 0) {
                    addstr(arg0, mkstr("-Bdynamic", NULL));
                }
            }
        } else {
            addstr(arg0, arg1->entries[i]);
        }
    }
}

// function quoted_length # 51
size_t quoted_length(const char* arg0, int* arg1) {
    u32 len = 0;
    u8 ch;

    *arg1 = 0;
    while (ch = *arg0++) { // != 0 does not match
        if (*arg1 == 0) {
            if ((ch == '\'') || (ch == '|') || (ch == '&') || (ch == '*') || (ch == '?') || (ch == '[') ||
                (ch == ']') || (ch == ';') || (ch == '!') || (ch == '(') || (ch == ')') || (ch == '^') || (ch == '<') ||
                (ch == '>') || (ch <= ' ') || (ch == '\t') || (ch == '\"') || (ch == '\\') || (ch == '`') ||
                (ch == '$')) {
                *arg1 = 1;
                len += 2;
            }
        }
        if ((ch == '"') || (ch == '\\') || (ch == '`') || (ch == '$')) {
            len++;
        }
        len++;
    }
    return len;
}

// function quote_shell_arg # 52
size_t quote_shell_arg(const char* arg0, char* arg1) {
    char ch;
    int sp28;
    size_t len;

    sp28 = 0;
    len = quoted_length(arg0, &sp28);
    if (sp28 != 0) {
        *arg1++ = '""';
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

// function func_00431A3C # 53
static int B_1000E4C0;    // argc
static char** B_1000E4C4; // argv
static char* B_1000ECDC;

static void func_00431A3C(int argc, char** argv) {
    int i;

    B_1000E4C0 = argc;
    B_1000E4C4 = malloc((argc + 1) * sizeof(char*));

    for (i = 0; i < argc; i++) {
        if (argv[i] != NULL) {
            B_1000E4C4[i] = strdup(argv[i]);
        } else {
            B_1000E4C4[i] = NULL;
        }
    }
    B_1000E4C4[B_1000E4C0] = NULL;
}

// function func_00431B38 # 54
static void func_00431B38(int first, int count) {
    int i;

    for (i = 0; i < count; i++) {
        B_1000E4C4[first + i] = NULL;
    }
}

// function func_00431B88 # 55

// arg2 is verbosity?
static void func_00431B88(FILE* arg0, const char* arg1, s32 arg2) {
    if (arg2) {
        fputs("CMDLINE=", arg0);
    }
    fprintf(arg0, "%s ", progname);
    if (cflag == 0) {
        fputs("-c ", arg0);
    }
    if ((srcfiles.length == 1) && (cflag != 0)) {
        if (B_1000ECCC != 0) {
            fprintf(arg0, "-o %s ", B_1000ECCC);
        }
    }
    fprintf(arg0, "%s %s\n", B_1000ECDC, arg1);
    if (arg2) {
        fputs("PWD=", arg0);
    }
    fprintf(arg0, "%s\n", D_1000C1D0);
    if (arg2) {
        fputs("----\n", arg0);
    }
}

// function func_00431D00 # 56
static void func_00431D00(const char* arg0) {
    FILE* file = fopen(tempstr[33], "w");

    if (file != NULL) {
        init_curr_dir();
        func_00431B88(file, arg0, FALSE);
        fclose(file);
    } else {
        error(2, NULL, 0, NULL, 0, "cannot open commandfile '%s'\n", tempstr[33]);
    }
}

// function func_00431DD8 # 57
static void func_00431DD8(void) {
    int sp34 = 0;
    int sp30 = 0;
    int sp2C = 0;
    int i;
    char* sp24;

    for (i = 1; i < B_1000E4C0; i++) {
        if (B_1000E4C4[i] != NULL) {
            sp34 += quoted_length(B_1000E4C4[i], &sp2C) + 1;
        }
    }

    B_1000ECDC = sp24 = malloc(sp34 + 1);
    for (i = 1; i < B_1000E4C0; i++) {
        if (B_1000E4C4[i] != NULL) {
            sp24 += quote_shell_arg(B_1000E4C4[i], sp24);
            *sp24 = ' ';
            sp24++;
        }
    }

    if (sp24 > B_1000ECDC) {
        sp24[-1] = '\0';
    } else {
        sp24[0] = '\0';
    }
}

// function skip_old_ii_controls # 58
#define EOF (-1) // can go when headers in

// Search file for the first "----" and move position to the line after it
void skip_old_ii_controls(FILE* arg0) {
    s32 ch;
    s32 sp50 = FALSE;

    ch = getc_locked(arg0);
    while (ch != EOF) {
        if (ch == '-' && (ch = getc_locked(arg0)) == '-' && (ch = getc_locked(arg0)) == '-' &&
            (ch = getc_locked(arg0)) == '-') {
            sp50 = TRUE;
        }

        while ((ch != '\n') && (ch != EOF)) {
            ch = getc_locked(arg0);
        }

        if (sp50) {
            break;
        }

        if (ch == '\n') {
            ch = getc_locked(arg0);
        }
    }
    if (ch == EOF) {
        rewind(arg0);
    }
}

// function make_ii_file_name # 59
// path/to/file -> path/to/ii_files/file.ii
// path/to/file.o -> path/to/ii_files/file.ii
char* make_ii_file_name(const char* arg0) {
    char* sp2C;  // basename
    size_t sp28; // basename length

    sp2C = basename(arg0);
    sp28 = strlen(sp2C);
    sp2C = mkstr(sp2C, "   ", 0);
    if ((sp2C[sp28 - 2] == '.') && (sp2C[sp28 - 1] == 'o')) {
        strcpy(&sp2C[sp28 - 1], "ii");
    } else {
        strcpy(&sp2C[sp28], ".ii");
    }
    return mkstr(dirname(arg0), "/ii_files/", sp2C, 0);
}

// function update_instantiation_info_file # 60
// TODO: type of error(), name vars

void update_instantiation_info_file(const char* arg0, const char* arg1) {
    char* sp54 = make_ii_file_name(arg1);
    char* sp50 = mkstr(sp54, ".NEW", 0);
    FILE* sp4C = fopen(sp54, "r");
    FILE* sp48;
    int sp44;

    if (sp4C != NULL) {
        init_curr_dir();
        if (vflag) {
            fprintf(stderr, "%s: update_instantiation_info_file %s\n", D_1000C2F0, sp54);
        }
        sp48 = fopen(sp50, "w");
        if (sp48 == NULL) {
            error(1, NULL, 0, "update_instantiation_info_file", 0, "error in creating file %s\n", sp50);
            perror(D_1000C2F0);
            cleanup();
            exit(1);
        }
        skip_old_ii_controls(sp4C);
        func_00431B88(sp48, arg0, TRUE);

        while ((sp44 = getc_locked(sp4C)) != -1) {
            putc_locked(sp44, sp48);
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

// function func_00432940 # 61
static int func_00432940(pid_t arg0) {
    int fd;            // sp29C
    char pathname[20]; // sp288
    prstatus_t status; // sp68
    int sp64 = 0;      // set and not used
    sysset_t syscalls; // sp24

    sprintf(pathname, "/proc/%-d", arg0);
    fd = open(pathname, O_RDWR | O_EXCL);
    if (fd == -1) {
        perror("Opening /proc");
        kill(arg0, 9);
        exit(1);
    }

    premptyset(&syscalls);
    praddset(&syscalls, 2); // size 2?

    if (ioctl(fd, PIOCSENTRY, &syscalls) < 0) {
        perror("PIOCSENTRY");
        kill(arg0, 9);
        exit(1);
    }

    func_00432C94();

    if (ioctl(fd, PIOCWSTOP, &status) < 0) {
        perror("PIOCWSTOP");
        kill(arg0, 9);
        exit(1);
    }

    if (status.pr_why != PR_SYSENTRY) {
        perror("program halted prematurely");
        kill(arg0, 9);
        exit(1);
    }

    if (status.pr_what != 2) { // PR_SIGNALLED ?
        perror("program halted in wrong system call");
        kill(arg0, 9);
        exit(1);
    }

    if (status.pr_errno != 0) {
        perror("unknown problem\n");
        exit(1);
    }

    return fd;
}

// function func_00432BDC # 62
// test pipe read
static void func_00432BDC(void) {
    char buf;
    int failure;

    close(B_1000EC98[1]);
    failure = (read(B_1000EC98[0], &buf, 1) != 1);
    if (failure) {
        perror("read on pipe failed");
        exit(1);
    }
    close(B_1000EC98[0]);
}

// function func_00432C94 # 63
// test pipe write
static void func_00432C94(void) {
    char buf;

    close(B_1000EC98[0]);
    if (write(B_1000EC98[1], &buf, 1) != 1) {
        perror("write on pipe failed");
        exit(1);
    }
    close(B_1000EC98[1]);
}

// function func_00432D3C # 64
static void func_00432D3C(const char* arg0, s32 count) {
    int i;
    s32 identified_segment;
    u32 flags;
    s32 pagesize;
    size_t text_size;
    size_t data_size;
    size_t brk_size;
    size_t stack_size;
    size_t so_text_size;
    size_t so_data_size;
    size_t so_brk_size;
    size_t mmap_size;
    int memflag;

    memflag = (memory_flag > 1);
    mmap_size = 0;
    so_brk_size = 0;
    so_data_size = 0;
    so_text_size = 0;
    stack_size = 0;
    brk_size = 0;
    data_size = 0;
    text_size = 0;
    pagesize = getpagesize();

    for (i = 0; i < count; i++) {
        identified_segment = FALSE;
        flags = B_1000CAC0[i].pr_mflags & 0xFFFF;
        if (flags == (MA_PRIMARY | 0xD)) {
            text_size += B_1000CAC0[i].pr_vsize * pagesize;
            identified_segment = TRUE;
        }

        if (flags == (MA_READ | MA_EXEC | MA_SHARED)) {
            so_text_size += B_1000CAC0[i].pr_vsize * pagesize;
            identified_segment = TRUE;
        }

        if (flags == (MA_READ | MA_WRITE | MA_COW)) {
            if ((uintptr_t)B_1000CAC0[i].pr_vaddr < 0x10000000) {
                so_data_size += B_1000CAC0[i].pr_vsize * pagesize;
                identified_segment = TRUE;
            }
        }

        // clang-format off
        if ((flags == (MA_READ | MA_WRITE)) 
            || (flags == MA_READ) 
            || (flags == (MA_READ | MA_WRITE | MA_SHARED)) 
            || (flags == (MA_READ | MA_SHARED))) {
            // clang-format on
            if ((uintptr_t)B_1000CAC0[i].pr_vaddr < 0x10000000) {
                mmap_size += B_1000CAC0[i].pr_vsize * pagesize;
                identified_segment = TRUE;
            }
        }
        flags &= ~MA_PRIMARY;
        if (flags == (MA_READ | MA_WRITE | MA_COW)) {
            if ((uintptr_t)B_1000CAC0[i].pr_vaddr >= 0x10000000) {
                data_size += B_1000CAC0[i].pr_vsize * pagesize;
                identified_segment = TRUE;
            }
        }
        if (flags == (MA_READ | MA_WRITE | MA_BREAK | MA_COW)) {
            if ((uintptr_t)B_1000CAC0[i].pr_vaddr >= 0x10000000) {
                brk_size += B_1000CAC0[i].pr_vsize * pagesize;
                identified_segment = TRUE;
            }
        }
        if (flags == (MA_READ | MA_WRITE | MA_STACK)) {
            stack_size += B_1000CAC0[i].pr_vsize * pagesize;
            identified_segment = TRUE;
        }
        if (!identified_segment) {
            fprintf(stderr, "-showm: Unidentified: segment %d\n", i);
        }
        if (memflag || !identified_segment) {
            fprintf(stderr, "pr_vaddr[%d]= %lx\n", i, B_1000CAC0[i].pr_vaddr);
            fprintf(stderr, "pr_size[%d]= %lx\n", i, B_1000CAC0[i].pr_size);
            fprintf(stderr, "pr_off[%d]= %lx\n", i, B_1000CAC0[i].pr_off);
            fprintf(stderr, "pr_mflags[%d]= %lx\n", i, B_1000CAC0[i].pr_mflags);
            fprintf(stderr, "pr_vsize[%d]= %lx\n", i, B_1000CAC0[i].pr_vsize);
            fprintf(stderr, "pr_psize[%d]= %lx\n", i, B_1000CAC0[i].pr_psize);
            fprintf(stderr, "pr_wsize[%d]= %lx\n", i, B_1000CAC0[i].pr_wsize);
            fprintf(stderr, "pr_rsize[%d]= %lx\n", i, B_1000CAC0[i].pr_rsize);
            fprintf(stderr, "pr_msize[%d]= %lx\n", i, B_1000CAC0[i].pr_msize);
            fprintf(stderr, "pr_dev[%d]= %lx\n", i, B_1000CAC0[i].pr_dev);
            fprintf(stderr, "pr_ino[%d]= %lx\n", i, B_1000CAC0[i].pr_ino);
            fprintf(stderr, "\n");
        }
    }

    fprintf(stderr, "%s phase mem: %dT %dD %dB %dS %dt %dd %db %dm= %dK\n", arg0, text_size / 0x400, data_size / 0x400,
            brk_size / 0x400, stack_size / 0x400, so_text_size / 0x400, so_data_size / 0x400, so_brk_size / 0x400,
            mmap_size / 0x400,
            (text_size + data_size + brk_size + stack_size + so_text_size + so_data_size + so_brk_size + mmap_size) /
                0x400);

    if (memflag) {
        fprintf(stderr, "text_size= %d Kbytes\n", text_size / 0x400);
        fprintf(stderr, "data_size= %d Kbytes\n", data_size / 0x400);
        fprintf(stderr, "brk_size= %d Kbytes\n", brk_size / 0x400);
        fprintf(stderr, "stack_size= %d Kbytes\n", stack_size / 0x400);
        fprintf(stderr, "so_text_size= %d Kbytes\n", so_text_size / 0x400);
        fprintf(stderr, "so_data_size= %d Kbytes\n", so_data_size / 0x400);
        fprintf(stderr, "so_brk_size= %d Kbytes\n", so_brk_size / 0x400);
        fprintf(stderr, "mmap_size= %d Kbytes\n", mmap_size / 0x400);
        fprintf(
            stderr, "TOTAL_SIZE= %d Kbytes\n",
            (text_size + data_size + brk_size + stack_size + so_text_size + so_data_size + so_brk_size + mmap_size) /
                0x400);
    }
}

// function func_00433534 # 65
// Prepends "--" to a string by copying.
static char* func_00433534(const char* arg0) {
    char* ret = (char*)malloc(strlen(arg0) + 3);

    ret[0] = '-';
    ret[1] = '-';
    ret[2] = '\0';
    strcat(ret, arg0);

    return ret;
}

/* File boundary, -O2 */

// gethostsex

#pragma GLOBAL_ASM("asm/7.1/functions/cc/__Release_ID.s")
