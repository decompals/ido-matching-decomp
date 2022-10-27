#include "cc.h"
#include "sex.h"

typedef struct {
    s32 capacity;
    s32 length;
    char** entries;
} list;

typedef int UNK_TYPE;

#define NULL (void*)0

// bss
static prmap_sgi_t B_1000CAC0[100];
char perr_msg[0x100];
static int B_1000E4C0;
static char **B_1000E4C4;
int plain_g;
int plain_O;
int noaliasokflag;
int haspl1;
UNK_TYPE p2cstr;
int align;
int align_common;
char *alignarg;
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
char *ratfor;
int mp_i2flag;
char *m4;
int mp_col120flag;
int mp_extendflag;
int mp_uflag;
int mp_backslashflag;
UNK_TYPE mp_uniq_specified;
UNK_TYPE mp_passes_relocated;
int cmp_flag;
int fullwarn;
char *aligndir;
int docpp;
int default_nocpp;
u32 j; // ?
char *tstring;
char *hstring;
char *Bstring;
char *allBstring;
static UNK_TYPE B_1000E55C; // Unused
char alltstring[20];
char *Warg;
char *Wpass;
char *Kpass;
char Karg;
char Hchar;
static char B_1000E587; // Unused
int time0;
static UNK_TYPE B_1000E58C; // Unused
struct tms tm0;
int retcode;
char *outfile;
char *passin;
char *passout;
char *errout;
char *symtab;
char *uopt0str;
char *ddoptstr;
char *optstr;
char *gentmp;
char *binasm;
char *uoutfile;
char *lpi_st;
char *lpi_p1;
char *lpi_dd;
static UNK_TYPE B_1000E5DC;
static char B_1000E5E0[0x400];
char *lpi_pd;
char *linkorder;
static UNK_TYPE valuesstr;
static UNK_TYPE tmp_elfobj;
char *CRTX;
FILE *ldw_file;
char *MCRTX;
FILE *tmpsfile;
list undefineflags;
char *editor;
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
char *comp_target_root;
list prelinkerflags;
char *comp_host_root;
list ccomflags;
char *systype;
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
char *tmpdir;
list uldflags;
char *rls_id_object;
list usplitflags;
char *progname;
list umergeflags;
char *currcomp;
list uloopflags;
static UNK_TYPE B_1000EB7C; // Unused
char* compdirs[7]; // might also be a struct?
static UNK_TYPE B_1000EB9C; // Unused
list uopt0flags;
int compiler;
list ddoptflags;
static UNK_TYPE B_1000EBBC; // Unused
char *tempstr[34];
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
static char *B_1000ECCC;
list srcfiles;
static char *B_1000ECDC;
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
char *pfa;
char *libI77_mp;
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
char* LD = "ld";
int ansi_choice = 3;
int c_compiler_choice = 0;

struct _struct_suffixes_0x8 {
    /* 0x0 */ const char* unk0;
    /* 0x4 */ int unk4;
}; // size = 0x8

struct _struct_suffixes_0x8 suffixes[0xF] = {
    { "pl1", 1 }, { "pli", 1 }, { "cob", 2 }, { "il", 3 },  { "st", 4 },  { "anl", 5 }, { "c++", 6 }, { "cc", 6 },
    { "cxx", 6 }, { "C", 6 },   { "cpp", 6 }, { "CXX", 6 }, { "CPP", 6 }, { ".c", 7 },  { NULL, 0 },
};

char *include = NULL;
char *includeB = NULL;
char *einclude = NULL;
char *eincludeB = NULL;
char *cpp = NULL;
char *ccom = NULL;
char *mpc = NULL;
char *cfe = NULL;
char *upas = NULL;
char *fcom = NULL;
char *upl1 = NULL;
char *pl1err = NULL;
char *ulpi = NULL;
char *ucob = NULL;
char *ujoin = NULL;
char *usplit = NULL;
char *uld = NULL;
char *umerge = NULL;
char *uloop = NULL;
char *uopt0 = NULL;
char *ddopt = NULL;
char *opt = NULL;
char *gen = NULL;
char *as0 = NULL;
char *as1 = NULL;
char *ld = NULL;
char *ftoc = NULL;
char *cord = NULL;
char *btou = NULL;
char *utob = NULL;
char *strip = NULL;
char *patch = NULL;
char *filter = NULL;
char *prelinker = NULL;
int smart_build = 0;
char *sbrepos = NULL;
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
char *crtx = NULL;
char *crtn = NULL;
char *cxx_init = NULL;
char *delta_init = NULL;
char *libp = NULL;
char *libp_b = NULL;
char *libm = NULL;
char *libm_b = NULL;
char *libF77 = NULL;
char *libF77_b = NULL;
char *libI77 = NULL;
char *libI77_b = NULL;
char *libU77 = NULL;
char *libftn = NULL;
char *libU77_b = NULL;
char *libisam = NULL;
char *libisam_b = NULL;
char *libdw_path = NULL;
char *libdw = NULL;
char *libdw_b = NULL;
char *libpl1 = NULL;
char *libpl1_b = NULL;
char *libexc = NULL;
char *libexc_b = NULL;
char *libcob = NULL;
char *libcob_b = NULL; // Unused
char *libsort = NULL;
char *libsort_b = NULL;
char *libprof = NULL;
char *libgprof = NULL;
char *libxmalloc = NULL;
char *libxmalloc_b = NULL;
char *cpp_stdflag = NULL;
char *libmld = NULL;
char *xpg_env = NULL;
int xpg_flag = 0;
int crtn_required = 1;
char *pca = NULL;
char *libc_mp = NULL;
char *fopt = NULL;
char *copt = NULL;
static int D_1000BF74 = 0;
static int D_1000BF78 = 0;
static int D_1000BF7C = 1;
static char *D_1000BF80 = NULL;
static char *D_1000BF84 = NULL;
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
char *edison_type = (char *)1;
int exception_handling = 0;
char* Gnum = "0";
int runerror = 0;
int uload = 0;
int uldobj_place = -1;
char *tmp_uldobj = NULL;
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

static const char* D_1000C1E0[] = {
    "Internal", "Error", "Warning", "Info", "Fix", "",
};

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

static char *D_1000C2E8 = NULL;
static char *D_1000C2EC = NULL;
static char* D_1000C2F0 = NULL; // basename of progname (?)
