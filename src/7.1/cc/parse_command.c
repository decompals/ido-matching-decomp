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

typedef enum Compiler {
    /* 0 */ COMPILER_0,
    /* 1 */ COMPILER_1, // C
    /* 2 */ COMPILER_2, // Pascal
    /* 3 */ COMPILER_3, // FORTRAN
    /* 4 */ COMPILER_4, // Assembler
    /* 5 */ COMPILER_5, // PL1
    /* 6 */ COMPILER_6  // COBOL
} Compiler;

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
    /* 0x0 */ const char* unk0; // name
    /* 0x4 */ int unk4;         // language?
};                              // size = 0x8

// For various languages' files?
struct _struct_suffixes_0x8 suffixes[] = {
    { "pl1", 1 }, { "pli", 1 },                                                                     // PL/1?
    { "cob", 2 },                                                                                   // COBOL
    { "il", 3 },                                                                                    // ?
    { "st", 4 },                                                                                    // ?
    { "anl", 5 },                                                                                   // ?
    { "c++", 6 }, { "cc", 6 },  { "cxx", 6 }, { "C", 6 }, { "cpp", 6 }, { "CXX", 6 }, { "CPP", 6 }, // C++
    { ".c", 7 },                                                                                    // C
    { NULL, 0 },
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

int Eflag = 0; // only preprocess
int Pflag = 0;
int gflag = 0;
int pflag = 0;
int pgflag = 0;
int jflag = 0; // only process to ucode
int cflag = 0;
int Sflag = 0; // only compile to assembly
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

// Process most of the options passed, the vast majority of which begin with '-'
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
    char* sp148; // env
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
        if ((argv[var_s0][0] == '-') && ((NoMoreOptions == 0) || (strchr(argv[var_s0], '.') == NULL))) {
            switch (argv[var_s0][1]) { /* switch 1 */
                case '#':              /* switch 1 */
                                       //! @bug Should end in '\n'.
                    error(2, NULL, 0, NULL, 0, "-# is not supported. Use -v to see compiler passesn");
                    break;

                case '1': /* switch 1 */
                    if ((compiler == 3) && (argv[var_s0][2] == '\0')) {
                        mp_onetripflag = 1;
                        addstr(&fcomflags, argv[var_s0]);
                    } else {
                        goto bad_option;
                    }
                    break;

                case '3': /* switch 1 */
                    if ((strcmp(argv[var_s0], "-32bit") == 0) || (strcmp(argv[var_s0], "-32") == 0)) {
                        thirty2bitflag = 1;
                        mips_abi = 1;
                    }
                    break;

                case '5': /* switch 1 */
                    error(2, NULL, 0, NULL, 0, "-5 not supported\n");
                    if (argv[var_s0][2] == '\0') {
                        if (Bflag != 0) {
                            if (fiveflag == 0) {
                                error(1, NULL, 0, NULL, 0, "-5 must precede any -B flags\n");
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
                    if ((compiler == 3) && (strcmp(argv[var_s0], "-66") == 0)) {
                        addstr(&fcomflags, argv[var_s0]);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-64bit") == 0) {
                        error(2, NULL, 0, NULL, 0,
                              "-64bit option is not yet implemented for ucode compilers, ignore\n");
                        sixty4bit_spec = 1;
                        if (swopcodeflag != 0) {
                            error(1, NULL, 0, NULL, 0, "-64bit can not be used with -swopcode for ucode compilers\n");
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
                            error(1, NULL, 0, NULL, 0, "ld requires -A to have an argument\n");
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
                        Bflag = 1;
                        sp144 = argv[var_s0] + 2;
                        relocate_passes(tstring, hstring, sp144);
                        if (tstring == NULL) {
                            Bstring = sp144;
                        }
                    }
                    break;

                case 'C': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        if (compiler == 3) {
                            addstr(&fcomflags, argv[var_s0]);
                            break;
                        }
                        if (compiler == 2) {
                            addstr(&upasflags, argv[var_s0]);
                            break;
                        }
                        if (compiler == 1) {
                            addstr(&cppflags, argv[var_s0]);
                            break;
                        }
                    }
                    //! @note Only checks for "-CG_E"
                    if (strncmp(argv[var_s0], "-CG_EMIT:", 5) == 0) {
                        error(2, NULL, 0, NULL, 0, "-CG_EMIT options are ignored\n");
                        break;
                    }
                    goto bad_option;

                case 'D': /* switch 1 */
                    if (strncmp(argv[var_s0], "-DEFAULT:", strlen("-DEFAULT:")) == 0) {
                        break;
                    }
                    if (argv[var_s0][2] == '\0') {
                        if ((var_s0 + 1) < argc) {
                            // TODO: work out where these should actually go
                            if (0) {
                                (void)"-D taken as empty cpp -D, not ld(1) -D hexnum\n";
                                (void)"-D";
                                (void)"ld requires -D to have an argument\n";
                            }
                            sp140 = malloc(strlen(argv[var_s0 + 1]) + 3);
                            sp140[0] = '-';
                            sp140[1] = 'D';
                            sp140[2] = '\0';
                            addstr(&undefineflags, strcat(sp140, argv[var_s0 + 1]));
                            add_static_opt(mkstr(argv[var_s0], argv[var_s0 + 1], NULL));
                        }
                        var_s0++;
                        break;
                    }
                    addstr(&undefineflags, argv[var_s0]);
                    add_static_opt(argv[var_s0]);
                    break;

                case 'E': /* switch 1 */
                    // -E
                    if (argv[var_s0][2] == '\0') {
                        Eflag++;
                        docpp = 1;
                        break;
                    }
                    // -EB/-EL (Endian)
                    if ((argv[var_s0][3] == '\0') && ((argv[var_s0][2] == 'B') || (argv[var_s0][2] == 'L'))) {
                        if (argv[var_s0][2] == 'B') {
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
                        break;
                    }
                    goto bad_option;

                case 'F': /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        if (compiler == 3) {
                            Fflag++;
                        } else if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                            cflag = 1;
                            Fflag = 1;
                            default_template_instantiation_mode = 1;
                        } else {
                            addstr(&ldflags, argv[var_s0]);
                        }
                        break;
                    }
                    goto bad_option;

                case 'G': /* switch 1 */
                    if (strncmp(argv[var_s0], "-GCM:", 5) == 0) {
                        error(2, NULL, 0, NULL, 0, "-GCM options are ignored\n");
                        break;
                    }
                    if (argv[var_s0][2] == '\0') {
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
                        if (!isdigit(*var_s2)) {
                            error(1, NULL, 0, NULL, 0, "non-digit character in -G %s\n", Gnum);
                            exit(2);
                        }
                    }
                    if (Gseen_flag == 0) {
                        relocate_passes(tstring, hstring, NULL);
                        Gseen_flag = 1;
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

                        for (var_s2 = "fKMdkjusmocab"; (*var_s2 != 0 && *var_s2 != Hchar); var_s2++) {}

                        if (*var_s2 == 0) {
                            error(1, NULL, 0, NULL, 0, "Unknown character in %s\n", argv[var_s0]);
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

                case 'J': /* switch 1 */
                    if (strcmp(argv[var_s0], "-Jsfm") != 0) {
                        if (strcmp(argv[var_s0], "-J") == 0) {
                            sp12C = argv[var_s0 + 1];
                            for (sp130 = sp12C; *sp130 != 0; sp130++) {
                                if (!isdigit(*sp130)) {
                                    error(1, NULL, 0, NULL, 0, "non-digit character in -J %s\n", sp12C);
                                    exit(2);
                                }
                            }
                            addstr(&prelinkerflags, argv[var_s0]);
                            addstr(&prelinkerflags, sp12C);
                            var_s0++;
                        } else {
                            case 'K': /* switch 1 */
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
                    if (argv[var_s0][2] == '\0') {
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
                    } else if (argv[var_s0][2] == '\0') {
                        if (1) {} // FAKE
                        addstr(&cppflags, argv[var_s0]);
                        Eflag++;
                        minus_M++;
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x4E: /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
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
                    if (argv[var_s0][2] == '\0') {
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
                    } else if (argv[var_s0][3] == '\0') {
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
                    if (argv[var_s0][2] == '\0') {
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
                    } else if (argv[var_s0][2] == '\0') {
                        Sflag++;
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x54: /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
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
                    if ((compiler == 3) && (argv[var_s0][2] == '\0')) {
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(argv[var_s0]);
                        mp_caseflag = 1;
                    } else if ((argv[var_s0][2] == '\0') && ((var_s0 + 1) < argc)) {
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
                    if (argv[var_s0][2] == '\0') {
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
                                                if (argv[var_s0][2] == '\0') {
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
                    if ((argv[var_s0][2] == '\0') || (strcmp(argv[var_s0], "-bestGnum") == 0)) {
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
                    if (argv[var_s0][2] == '\0') {
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
                    } else if (argv[var_s0][2] == '\0') {
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
                    if (argv[var_s0][2] == '\0') {
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
                            } else if (argv[var_s0][2] == '\0') {
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
                        if (argv[var_s0][2] == '\0') {
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
                    if (argv[var_s0][2] == '\0') {
                        gflag = 2;
                        plain_g = 1;
                        if (plain_O != 0) {
                            Oflag = 1;
                        }
                    } else if ((argv[var_s0][3] == '\0') && (argv[var_s0][2] >= 0x30) && (argv[var_s0][2] < 0x34)) {
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
                    if (argv[var_s0][2] == '\0') {
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
                    if (argv[var_s0][2] == '\0') {
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
                        if ((argv[var_s0][2] == 0x6D) && (argv[var_s0][3] == '\0')) {
                            lmflag++;
                        } else if ((argv[var_s0][2] == '\0') && ((var_s0 + 1) < argc)) {
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
                    } else if (argv[var_s0][2] == '\0') {
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
                            if ((argv[var_s0][2] == 0x70) && (argv[var_s0][3] == '\0')) {
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
                    } else if ((argv[var_s0][2] == '\0') || (strcmp(argv[var_s0], "-nocount") == 0) ||
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
                    } else if (argv[var_s0][2] == '\0') {
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
                    if (argv[var_s0][2] == '\0') {
                        pflag = 1;
                    } else if (strcmp(argv[var_s0], "-pg") == 0) {
                        pflag = 1;
                        pgflag = 1;
                    } else if (argv[var_s0][3] == '\0') {
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
                    } else if (argv[var_s0][2] == '\0') {
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
                    if (argv[var_s0][2] == '\0') {
                        if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                            do_strip = 1;
                        } else {
                            addstr(&ldflags, argv[var_s0]);
                        }
                    } else if (strcmp(argv[var_s0], "-strictIEEE") == 0) {
                        addstr(&optflags, argv[var_s0]);
                    } else if ((((compiler == 1) && (c_compiler_choice != 0)) || (compiler == 3)) &&
                               (strncmp(argv[var_s0], "-sa", 3U) == 0) &&
                               ((argv[var_s0][3] == '\0') || (argv[var_s0][3] == 0x2C))) {
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
                    if (argv[var_s0][2] == '\0') {
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
                        if (argv[var_s0][2] == '\0') {
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
                    if (argv[var_s0][2] == '\0') {
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
                    if ((argv[var_s0][2] == 0x31) && (argv[var_s0][3] == '\0')) {
                        if (compiler != 3) {
                            error(2, NULL, 0, NULL, 0, "Unknown flag: %s\n", argv[var_s0]);
                        } else {
                            w1flag = 1;
                        }
                    } else if ((argv[var_s0][2] == 0x30) && (argv[var_s0][3] == '\0')) {
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
                    } else if ((argv[var_s0][2] == '\0') ||
                               ((argv[var_s0][3] == '\0') && ((argv[var_s0][2] == 0x31) || (argv[var_s0][2] == 0x32) ||
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
                    } else if (argv[var_s0][2] == '\0') {
                        addstr(&ldflags, argv[var_s0]);
                    } else {
                        goto bad_option;
                    }
                    break;
                case 0x7A: /* switch 1 */
                    if (argv[var_s0][2] == '\0') {
                        addstr(&ldflags, argv[var_s0]);
                    } else {
                        goto bad_option;
                    }
                    break;
                default:
                    goto bad_option;
            }
            continue;
        } else if ((argv[var_s0][0] == '+') && (compiler == 1) &&
                   ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
            switch (argv[var_s0][1]) { /* switch 5 */
                case 'p':              /* switch 5 */
                    if (argv[var_s0][2] == '\0') {
                        anachronisms = 0;
                    } else if (argv[var_s0][2] == 'p') {
                        anachronisms = 0;
                        cfront_compatible = 0;
                    } else if (argv[var_s0][2] == 'a') {
                        anachronisms = 0;
                    } else if (argv[var_s0][2] == 'c') {
                        cfront_compatible = 0;
                    }
                    add_static_opt(argv[var_s0]);
                    break;

                case 'w': /* switch 5 */
                    fullwarn = 1;
                    break;

                case 'v': /* switch 5 */
                    vflag = 1;
                    break;

                case 'd': /* switch 5 */
                    disable_inlines = 1;
                    break;

                case 'e': /* switch 5 */
                    if ((compiler == 1) && (c_compiler_choice != 0)) {
                        error(2, NULL, 0, NULL, 0, "invalid option %s for Delta/C++%s - ignored\n", argv[var_s0], "");
                        break;
                    }

                case 'I': /* switch 5 */
                    cflag = 1;
                    plusIflag = 1;
                    Fflag = 1;
                    default_template_instantiation_mode = 1;
                    break;

                case 'a':
                case 'L':
                    break;

                default: /* switch 5 */
                    goto bad_option;
            }
            continue;
        } else {
            var_s1 = getsuf(argv[var_s0]);
            if (var_s1 == 'm') {
                var_s1 = 'f';
            }
            if (var_s1 == 'p') {
                haspascal = 1;
            }
            if (var_s1 == 'f') {
                hasfortran = 1;
            }
            if (var_s1 == 1) {
                haspl1 = 1;
            }
            if ((var_s1 == 'c') || (var_s1 == 'p') || (var_s1 == 'f') || (var_s1 == 'F') || (var_s1 == 'r') ||
                (var_s1 == 'e') || (var_s1 == 'B') || (var_s1 == 'U') || (var_s1 == 's') || (var_s1 == 'O') ||
                (var_s1 == 'G') || (var_s1 == 'S') || (var_s1 == 'M') || (var_s1 == 'V') || (var_s1 == 'i') ||
                (var_s1 == 1) || (var_s1 == 'D') || (var_s1 == 3) || (var_s1 == 2) || (var_s1 == 'u') ||
                (var_s1 == 6) || ((compiler == 1) && (nocode != 0) && (D_1000BF74 != 0) && (var_s1 == 'h')) ||
                (Eflag != 0) || (compiler == 4)) {
                srcexists++;
                if ((argv[var_s0][0] == '-') && (NoMoreOptions == 0)) {
                    sp60 = 1;
                    while (argv[var_s0][sp60] == '-') {
                        sp60++;
                    }
                    argv[var_s0] += sp60;
                }
                for (sp5C = 1; sp5C < argc; sp5C++) {
                    if ((argv[sp5C][1] == 'j') && (strcmp(argv[sp5C], "-j") == 0)) {
                        jflag++;
                    }
                }
                if (((Oflag == 3) || (Oflag == 4)) && (jflag == 0) &&
                    ((var_s1 == 'c') || (var_s1 == 'p') || (var_s1 == 'f') || (var_s1 == 'F') || (var_s1 == 'r') ||
                     (var_s1 == 'e') || (var_s1 == 'B') || (var_s1 == 'U') || (var_s1 == 'i') || (var_s1 == 1) ||
                     (var_s1 == 3) || (var_s1 == 2) || (var_s1 == 6) || (var_s1 == 'u') || (var_s1 == 'D'))) {
                    if (var_s1 != 'u') {
                        addstr(&srcfiles, argv[var_s0]);
                        var_s2 = mksuf(argv[var_s0], 'u');
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
                    var_s2 = mksuf(argv[var_s0], 'o');
                    if (nodup(&objfiles, var_s2) != 0) {
                        sp158 = var_s2;
                    }
                } else if ((Eflag == 0) && (compiler != 4)) {
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
                if (((Oflag == 3) || (Oflag == 4)) && (jflag == 0)) {
                    if (uldobj_place == -1) {
                        uldobj_place = save_place(&objfiles);
                    }
                    addstr(&ufiles, argv[var_s0]);
                    uload = 1;
                }
            } else {
                addstr(&objfiles, argv[var_s0]);
                if (var_s1 == 'o') {
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
    } /* end of loop */

    if (sp15C != NULL) {
        if (srcfiles.length == 1) {
            sp58 = strdup(srcfiles.entries[0]);
            if (sp58 == NULL) {
                sp58 = sp158;
            } else {
                sp54 = strlen(sp58);
                if ((sp54 >= 3) && (sp58[sp54 - 2] == '.')) {
                    if (Eflag != 0) {
                        sp58[sp54 - 1] = 'i';
                    } else if (Sflag != 0) {
                        sp58[sp54 - 1] = 's';
                    } else if (jflag != 0) {
                        sp58[sp54 - 1] = 'u';
                    } else {
                        sp58[sp54 - 2] = '\0';
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

static void func_00431B38(int first, int count) {
}
