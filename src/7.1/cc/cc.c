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
void addstr(); // (list* arg0, char* str), but sometimes called incorrectly
char* newstr(const char* src);
char* savestr(const char* src, size_t extra_length);

static const char* func_00430414(char* arg0, int arg1);
static void func_00431A3C(int argc, char** argv);
static void func_00431B38(int first, int count);
static void func_00431D00(const char* arg0);
static void func_00431DD8(void);
static int func_00432940(pid_t arg0);
static void func_00432BDC();
static void func_00432D3C(const char* arg0, int count);
static char* func_00433534(const char* arg0);

char* make_ii_file_name(const char* arg0);

void get_lino(char* arg0, const char* arg1, int arg2);
void settimes(void);
void dotime(const char* programName);
void handler(void);
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
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/7.1/functions/cc/main.s")
#else

int main(int argc, char** argv) {
	register int var_s0;
	register char* var_s1;
	register char* var_s2;
	int sp148;
	char* sp144;
	char* sp140;
	char* sp13C;
	char* sp138;
	char* sp134;
	int sp130;
	char* sp12C;
	char* sp128;
	char* sp124;
	int sp120;
	int sp11C;
	char* sp118;
	int sp114;
	char* sp110;
	char* sp10C;
	char* sp108;
	char* sp104;
	int sp100;
	int spFC;
	char* spF8;
	char* spF4;
	char spF0[4];
	char* spEC;
	char* spE8;
	char spE7;

	int spE0;
	int spDC;
	u32 spD8;
	char* spD4;
	int spD0;
	struct stat sp48;

	sp148 = 0;
	sp144 = NULL;
	sp140 = NULL;
	progname = *argv;
	if ((ansichoice == 1) || (ansichoice == 2)) {
		CRTX = "acrt1.o";
	} else {
		CRTX = "crt1.o";
	}
	MCRTX = "mcrt1.o";
	m4 = "/usr/bin/m4";
	ratfor = "/usr/bin/ratfor";
	xpg_env = getenv("_XPG");
	if (xpg_env != NULL) {
		xpg_flag = 1;
	}
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

	compdirs[1] = mkstr("cc", "/", NULL);
	compdirs[2] = mkstr("pc", "/", NULL);
	compdirs[3] = mkstr("f77", "/", NULL);
	compdirs[4] = mkstr("cc", "/", NULL);
	compdirs[5] = mkstr("pl1", "/", NULL);
	compdirs[6] = mkstr("cobol", "/", NULL);

	call_shared = default_call_shared;
	sp13C = getenv("SGI_SVR4");
	if (sp13C != NULL) {
		default_svr4 = 1;
	}
	sp138 = getenv("SGI_CC");
	if (sp138 != NULL) {
		while (isspace(*sp138)) {
			sp138++;
		}
		sp130 = strlen(sp138);
		if (sp130 <= 0) {
			error(2, NULL, 0, NULL, 0, "Environment variable SGI_CC is empty: ignored\n");
		} else {
			sp134 = sp138 + sp130 - 1;
			while (isspace(*sp134)) {
				sp134--;
			}
			sp134++;
			sp134[0] = 0;
			if (strcmp(sp138, "-cckr") == 0) {
				ansichoice = 0;
				cppchoice = 2;
				relocate_passes("p", NULL, NULL);
			} else if (strcmp(sp138, "-ansi") == 0) {
				ansichoice = 1;
				cppchoice = 3;
				relocate_passes("p", NULL, NULL);
			} else if (strcmp(sp138, "-xansi") == 0) {
				ansichoice = 3;
				cppchoice = 3;
				relocate_passes("p", NULL, NULL);
			} else if (strcmp(sp138, "-ansiposix") == 0) {
				ansichoice = 2;
				cppchoice = 3;
				relocate_passes("p", NULL, NULL);
			} else {
				error(2, NULL, 0, NULL, 0, "Environment variable SGI_CC contents unrecognizable and ignored; \"%s\" not one of: -cckr -ansi -xansi -ansiposix\n", sp138);
				sp138 = NULL;
			}
		}
	}
	compiler = 1;

	var_s1 = strrchr(progname, '/');
	var_s1 = (var_s1 == NULL) ? progname : var_s1 + 1;
	compdirs[0] = mkstr(var_s1, "/", NULL);

	if (strncmp(var_s1, "cc", strlen("cc")) == 0) {
		compiler = 1;
		Bstring = var_s1 + strlen("cc");
	} else if (strncmp(var_s1, "pc", strlen("pc")) == 0) {
		compiler = 2;
		Bstring = var_s1 + strlen("pc");
	} else if (strncmp(var_s1, "f77", strlen("f77")) == 0) {
		compiler = 3;
		Bstring = var_s1 + strlen("f77");
	} else if (strncmp(var_s1, "f90", strlen("f90")) == 0) {
		error(1, NULL, 0, NULL, 0, "-32 compilation not supported for ucode\n");
		exit(2);
	} else if (strncmp(var_s1, "as", strlen("as")) == 0) {
		compiler = 4;
		Bstring = var_s1 + strlen("as");
		strcpy(compdirs[0], compdirs[1]);
	} else if (strncmp(var_s1, "pl1", strlen("pl1")) == 0) {
		compiler = 5;
		Bstring = var_s1 + strlen("pl1");
	} else if (strncmp(var_s1, "cobol", strlen("cobol")) == 0) {
		compiler = 6;
		Bstring = var_s1 + strlen("cobol");
	} else if (strncmp(var_s1, "ncc", strlen("ncc")) == 0) {
		compiler = 1;
		c_compiler_choice = 1;
		edison_cpp = 1;
		Bstring = var_s1 + strlen("ncc");
	} else if (strncmp(var_s1, "CC.eh", strlen("CC.eh")) == 0) {
		compiler = 1;
		c_compiler_choice = 2;
		edison_cpp = 1;
		anachronisms = 0;
		cfront_compatible = 0;
		D_1000BF7C = 0;
		exception_handling = 1;
		Bstring = var_s1 + strlen("CC");
	} else if (strncmp(var_s1, "CC", strlen("CC")) == 0) {
		compiler = 1;
		c_compiler_choice = 2;
		edison_cpp = 1;
		D_1000BF7C = 0;
		Bstring = var_s1 + strlen("CC");
	} else if (strncmp(var_s1, "NCC", strlen("NCC")) == 0) {
		compiler = 1;
		c_compiler_choice = 2;
		edison_cpp = 1;
		Bstring = var_s1 + strlen("NCC");
	} else if (strncmp(var_s1, "DCC", strlen("DCC")) == 0) {
		compiler = 1;
		c_compiler_choice = 3;
		edison_cpp = 1;
		Bstring = var_s1 + strlen("DCC");
		D_1000BF90 = 1;
	}
	Bstring = NULL;
	comp_target_root = getenv("COMP_TARGET_ROOT");
	if (comp_target_root == NULL) {
		comp_target_root = "/";
	} else if (comp_target_root[strlen(comp_target_root) - 1] != '/') {
		comp_target_root = mkstr(comp_target_root, "/", NULL);
	}
	comp_host_root = getenv("TOOLROOT");
	if (comp_host_root == NULL) {
		comp_host_root = "/";
	} else if (comp_host_root[strlen(comp_host_root) - 1] != '/') {
		comp_host_root = mkstr(comp_host_root, "/", NULL);
	}
	aligndir = mkstr(comp_host_root, "lib/align", NULL);
	sp12C = getenv("DCC_STD_PATHS");
	D_1000BF8C = sp12C == NULL || *sp12C == 0 || *sp12C == '0';
	if (D_1000BF8C == 0) {
		D_1000BF90 = D_1000BF8C;
	}
	if (force_use_cfront(argc, argv)) {
		exec_OCC(argc, argv);
	}
	func_00431A3C(argc, argv);
	tmpdir = getenv("TMPDIR");
	if (tmpdir == NULL) {
		tmpdir = "/tmp/";
	} else if (tmpdir[strlen(tmpdir) - 1] != '/') {
		tmpdir = mkstr(tmpdir, "/", NULL);
	}
	passout = mktemp(mkstr(tmpdir, "ctmtstXXXXXX", NULL));
	tmpsfile = fopen(passout, "w");
	if (tmpsfile == NULL) {
		sprintf(perr_msg, "cc: can't write to $TMPDIR: %s", tmpdir);
		perror(perr_msg);
		exit(2);
	} else {
		fclose(tmpsfile);
		unlink(passout);
	}
	rls_id_object = getenv("RLS_ID_OBJECT");

	for (var_s0 = 1; var_s0 < argc; var_s0++) {
		if (strcmp(argv[var_s0], "-non_shared") == 0) {
			non_shared = 1;
			if (Oflag < 3) {
				Gnum = "8";
			}
		} else if (strcmp(argv[var_s0], "-irix4") == 0) {
			irix4 = 1;
			Gnum = "8";
		} else if (strcmp(argv[var_s0], "-coff") == 0) {
			LD = "old_ld";
			coff_spec = 1;
			kpic_flag = 0;
			Gnum = "8";
		} else if (strcmp(argv[var_s0], "-mips3") == 0) {
			mips3flag = 1;
			Gnum = "8";
			kpic_flag = 0;
		} else if (strcmp(argv[var_s0], "-excpt") == 0) {
			excpt_flag = 1;
			kpic_flag = 0;
			Gnum = "8";
		} else if (strcmp(argv[var_s0], "-abi") == 0) {
			abi_flag = 1;
			mips1flag = 1;
			mips2flag = 0;
		} else if (strcmp(argv[var_s0], "-O3") == 0) {
			Oflag = 3;
		} else if (strcmp(argv[var_s0], "-old_ld") == 0) {
			LD = "old_ld";
			D_1000BF90 = 0;
		}
	}

	if ((compiler == 1) || (compiler == 2) || (compiler == 3) || (compiler == 4)) {
		docpp = 1;
		default_nocpp = 0;
	} else {
		docpp = 0;
		default_nocpp = 1;
	}
	currcomp = compdirs[0];
	mklist(&dirs_for_nonshared_crtn);
	mklist(&dirs_for_abi_crtn);
	mklist(&dirs_for_crtn);

	for (var_s0 = 1; var_s0 < argc; var_s0++) {
		if (argv[var_s0][0] == 0x2D) {
			if (strcmp(argv[var_s0], "-nostdlib") == 0) {
				sp148 = 1;
			} else {
				switch (argv[var_s0][1]) {              /* switch 9; irregular */
				case 0x45:                      /* switch 9 */
					if ((argv[var_s0][3] == 0) && ((argv[var_s0][2] == 0x42) || (argv[var_s0][2] == 0x4C))) {
						if (argv[var_s0][2] == 0x42) {
							if ((Bflag != 0) && (targetsex != 0)) {
								error(1, NULL, 0, NULL, 0, "-EB or -EL must precede any -B flags for ucode compilers.\n");
								exit(2);
							}
							targetsex = 0;
						} else {
							if ((Bflag != 0) && (targetsex != 1)) {
								error(1, NULL, 0, NULL, 0, "-EB or -EL must precede any -B flags for ucode compilers.\n");
								exit(2);
							}
							targetsex = 1;
						}
						newrunlib();
					}
					break;
				case 0x4C:                      /* switch 9 */
					if (argv[var_s0][2] == 0) {
						if (((var_s0 + 1) >= argc) || (argv[var_s0 + 1][0] == 0x2D) || (isdir(argv[var_s0 + 1]) == 0)) {
							sp148 = 1;
							break;
						} else {
							var_s0 += 1;
							sp128 = mkstr(argv[var_s0], NULL);
						}
					} else {
						sp128 = mkstr(argv[var_s0] + 2, NULL);
					}
					if (sp128[strlen(sp128) - 1] == 0x2F) {
						sp128[strlen(sp128) - 1] = 0;
					}
					addstr(&dirs_for_crtn, sp128);
					addstr(&dirs_for_nonshared_crtn, sp128);
					addstr(&dirs_for_abi_crtn, sp128);
					break;
				}
			}
		}
done:;
	}

	if (sp148 == 0) {
		if ((non_shared != 0) || (coff_spec != 0) || (mips3flag != 0) || (excpt_flag != 0)) {
			addstr(&dirs_for_nonshared_crtn, mkstr(comp_target_root, "usr/lib/nonshared", NULL));
		} else if (abi_flag != 0) {
			addstr(&dirs_for_abi_crtn, mkstr(comp_target_root, "usr/lib/abi", NULL));
		} else {
			addstr(&dirs_for_crtn, mkstr(comp_target_root, "usr/lib", NULL));
			addstr(&dirs_for_crtn, mkstr(comp_target_root, "lib", NULL));
		}
	}
	relocate_passes(tstring, NULL, Bstring);
	relocate_passes("h", NULL, Bstring);
	if (strcmp("/", comp_target_root) != 0) {
		einclude = mkstr(comp_target_root, "usr/include/CC", NULL);
		include = mkstr(comp_target_root, "usr/include", NULL);
	}
	if (compiler == 1) {
		oldcflag = 0;
	} else {
		cpp_stdflag = "-std0";
	}
	systype = "svr4";
	svr4_systype = 1;
	process_config(argc, argv);
	parse_command(argc - 1, argv + 4);
	func_00431DD8();
	if (D_1000BF74 != 0) {
		if (D_1000BF80 == NULL) {
			D_1000BF80 = "";
		}
		sp144 = mkstr(D_1000BF78 != 0 ? "-YSv" : "-YSz", D_1000BF80, NULL);
		if (compiler == 1) {
			addstr(&edisonflags, sp144);
		} else {
			if (D_1000BF78 != 0) {
				sp140 = "-cvs_nosrc";
			} else {
				sp140 = "-cvs";
			}
			if (D_1000BF80[0] != 0) {
				sp140 = mkstr(sp140, ",", D_1000BF80, NULL);
			}
			addstr(&fcomflags, sp140);
		}
	}
	if (user_systype == 0) {
		if (fiveflag != 0) {
			include = mkstr(comp_target_root, "usr/5include", NULL);
		} else {
			einclude = mkstr(comp_target_root, "usr/include/CC", NULL);
			include = mkstr(comp_target_root, "usr/include", NULL);
		}
		// include = var_v0_2;
		if (Bstring != NULL) {
			relocate_passes("h", NULL, Bstring);
		}
		newrunlib();
	}
	if (((mips2flag != 0) || (mips3flag != 0) || (sixty4bitflag != 0)) && (kpic_flag == 0) && ((non_shared != 0) || (call_shared != 0) || (default_call_shared != 0))) {
		if (non_shared == 0) {
			non_shared = 1;
			old_non_shared = 1;
		}
		default_call_shared = 0;
		call_shared = 0;
		if (non_shared_emitted == 0) {
			addstr(&ldflags, "-non_shared");
			addstr(&cfeflags, "-non_shared");
			non_shared_emitted = 1;
		}
	}
	if ((non_shared != 0) && (non_shared_emitted == 0)) {
		addstr(&ldflags, "-non_shared");
		addstr(&cfeflags, "-non_shared");
		non_shared_emitted = 1;
	} else if (call_shared != 0) {
		addstr(&ldflags, "-call_shared");
		addstr(&cfeflags, "-call_shared");
	}
	if ((Vflag == 0) && (srcfiles.length == 0) && (objfiles.length == 0) && (ufiles.length == 0)) {
		error(1, NULL, 0, NULL, 0, "no source, object or ucode file specified\n");
		exit(2);
	}
	if (w1flag == 1) {
		addstr(&fcomflags, "-w1");
	} else if (w1flag == 2) {
		addstr(&fcomflags, "-w");
	}
	if ((srcexists == 0) && ((cflag != 0) || (Sflag != 0))) {
		error(1, NULL, 0, NULL, 0, "no source file for ucode compilers.\n");
		exit(4);
	}
	if ((mp_flag != 0) && (gflag != 0) && (mp_flag & 1)) {
		mp_flag |= 4;
	}
	if ((cmp_flag != 0) && (gflag != 0) && (cmp_flag & 1)) {
		cmp_flag |= 4;
	}
	if ((ansichoice == 1) || (ansichoice == 2)) {
		CRTX = "acrt1.o";
		crtn_required = 1;
	}
	relocate_passes("r", NULL, NULL);
	if ((B_1000ED30 != 0) && (compiler == 1) && ((ansichoice == 1) || (ansichoice == 2))) {
		error(2, NULL, 0, NULL, 0, "'-lc_s' specified. Shared version of C library does not conform to ANSI X3.159-1989.\n");
	}
	// The second and third comparison of this if check are fake and optimized out
	if (Oflag >= 3 && Oflag >= 3 && Oflag >= 3) {
	}
	if ((kpic_flag != 0) && (strcmp(Gnum, "0") != 0) && (Oflag < 3)) {
		error(2, NULL, 0, NULL, 0, "-KPIC (the default) is only compatible with -G 0 for ucode compilers, changing to -G 0. \n");
		Gnum = "0";
	}
	if ((abi_flag != 0) && (non_shared != 0)) {
		error(2, NULL, 0, NULL, 0, "-non_shared is not compatible with -abi for ucode compilers, changing to -abi.\n");
		non_shared = 0;
		kpic_flag = 1;
		Gnum = "0";
	}
	if ((Oflag >= 3) && (compiler == 4)) {
		error(2, NULL, 0, NULL, 0, "-O3 is not supported for assembly compiles for ucode compilers; changing to -O2.\n");
		Oflag = 2;
		uload = 0;
	}
	get_host_chiptype();
	if (targetsex == 0) {
		addstr(&cppflags, "-D_MIPSEB");
		if ((compiler != 1) || (ansichoice == 0) || (ansichoice == 3)) {
			addstr(&cppflags, "-DMIPSEB");
		}
		if ((compiler == 1) && ((ansichoice == 1) || (ansichoice == 2) || ((ansichoice == 3) && (irix4 == 0)))) {
			addstr(&cppflags, "-D__STDC__=1");
		}
		if ((compiler == 1) && (ansichoice == 2)) {
			addstr(&cppflags, "-D_POSIX_SOURCE=1");
		}
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
	} else {
		addstr(&cppflags, "-D_MIPSEL");
		addstr(&cppflags, "-D_MIPSEL");
		if ((compiler != 1) || (ansichoice == 0) || (ansichoice == 3)) {
			addstr(&cppflags, "-DMIPSEL");
		}
		if ((compiler == 1) && ((ansichoice == 1) || (ansichoice == 2) || ((ansichoice == 3) && (irix4 == 0)))) {
			addstr(&cppflags, "-D__STDC__=1");
		}
		if ((compiler == 1) && (ansichoice == 2)) {
			addstr(&cppflags, "-D_POSIX_SOURCE=1");
		}
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
	}
	switch (gflag) {                                /* switch 10; irregular */
	case 0:                                         /* switch 10 */
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
		if (nocode == 0) {
			addstr(&edisonflags, "-Zg0");
		}
		break;
	case 1:                                         /* switch 10 */
		addstr(&edisonflags, "-Zg1");
		addstr(&ccomflags, "-Xg1");
		add_info("-g1");
		break;
	case 2:                                         /* switch 10 */
		addstr(&edisonflags, "-Zg2");
		addstr(&ccomflags, "-Xg2");
		add_info("-g2");
		break;
	case 3:                                         /* switch 10 */
		gflag += 1;
		addstr(&edisonflags, "-Zg3");
		addstr(&ccomflags, "-Xg3");
		add_info("-g3");
		break;
	}
	if ((mp_flag != 0) && (ddoptflag != 0)) {
		error(1, NULL, 0, NULL, 0, "can't use -mp/-pfa with -ddopt\n");
		exit(2);
	}
	if ((mips3flag != 0) && (thirty2bitflag == 0)) {
		error(1, NULL, 0, NULL, 0, "-mips3 implies -64bit for ucode compilers, which is not supported.\n");
		exit(2);
	}
	if ((irix4 != 0) && (compiler == 1) && (c_compiler_choice != 0)) {
		error(1, NULL, 0, NULL, 0, "IRIX4 not supported in Delta-C++\n");
		exit(2);
	}
	if ((irix4 != 0) && (compiler == 3) && (D_1000BF74 != 0)) {
		error(1, NULL, 0, NULL, 0, "IRIX4 and -sa not supported together\n");
		exit(2);
	}
	if (((cflag != 0) || (Sflag != 0) || (nocode != 0) || (Eflag != 0) || (Pflag != 0)) && (make_edison_shlib != 0)) {
		error(1, NULL, 0, NULL, 0, "-shared can be specified only when a link is to be performed for ucode compilers\n");
		exit(2);
	}
	if ((cflag == 0) && (nocode == 0) && (srcfiles.length == 1) && (objfiles.length == 1)) {
		default_template_instantiation_mode = 1;
	}
	if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (Fflag != 0) && (smart_build != 0)) {
		error(2, NULL, 0, NULL, 0, "-F and -smart cannot be specified together for ucode compilers: -smart ignored\n");
		smart_build = 0;
	}
	if ((default_template_instantiation_mode != 0) && (force_prelink == 0)) {
		no_prelink = 1;
	}
	if ((compiler == 1) && (c_compiler_choice == 3)) {
		sp124 = getenv("DCC_FORCE_OPT");
		sp120 = 1;
		if (Oflag >= 3) {
			Oflag = 2;
			uload = 0;
		}
		if (sp124 != NULL) {
			// temp_t6 = sp124->unk_0;
			if ((sp124[0] >= 0x30) && (sp124[0] < 0x34) && (sp124[1] == 0)) {
				sp120 = sp124[0] - 0x30;
			}
		}
		if (Oflag > sp120) {
			Oflag = sp120;
		}
	}
	addstr(&execlist, "-Dunix");
	if (dmips_emit == 0) {
		if (mips2flag != 0) {
			if (dwopcodeflag != 0) {
				error(1, NULL, 0, NULL, 0, "can't mix -mips2 with -dwopcode for ucode compilers\n");
				exit(2);
			}
			addstr(&execlist, "-Dmips=2");
		}
		if (mips3flag != 0) {
			addstr(&execlist, "-Dmips=3");
		} else {
			addstr(&execlist, "-Dmips=1");
		}
	}
	addstr(&execlist, "-Dhost_mips");
	if (sixty4bitflag != 0) {
		addstr(&ccomflags, "-64bit");
		add_info("-64bit");
		addstr(&ccomflags, "-dwopcode");
		add_info("-dwopcode");
		if (mips3flag == 0) {
			chip_targ = 2;
			mips3flag = 1;
			addstr(&ccomflags, "-mips3");
			add_info("-mips3");
			relocate_passes("M", NULL, NULL);
		}
	} else if (dwopcodeflag != 0) {
		addstr(&ccomflags, "-dwopcode");
		add_info("-dwopcode");
		if (mips3flag == 0) {
			chip_targ = 2;
			mips3flag = 1;
			addstr(&ccomflags, "-mips3");
			add_info("-mips3");
			relocate_passes("M", NULL, NULL);
		}
	}
	switch (Oflag) {                                /* switch 1 */
	case 0:                                         /* switch 1 */
		var_s1 = "-O0";
		break;
	case 1:                                         /* switch 1 */
		var_s1 = "-O1";
		break;
	case 2:                                         /* switch 1 */
		var_s1 = "-O2";
		break;
	case 3:                                         /* switch 1 */
		var_s1 = "-O3";
		break;
	case 4:                                         /* switch 1 */
		var_s1 = "-O4";
		break;
	}
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
	if (compiler == 3) {
		if (automaticflag != 0) {
			addstr(&fcomflags, "-automatic");
		} else {
			addstr(&fcomflags, "-static");
			addstr(&optflags, "-static");
		}
	}
	if (Vflag != 0) {
		whats();
	}
	if (runerror != 0) {
		exit(1);
	}
	if (sigset(2, (void (*)())1) != (void (*)())1) {
		sigset(2, handler);
	}
	if (sigset(0xF, (void (*)())1) != (void (*)())1) {
		sigset(0xF, handler);
	}
	if (sigset(0xD, (void (*)())1) != (void (*)())1) {
		sigset(0xD, handler);
	}
	if ((compiler == 6) && (nolockflag != 0) && (lpilockflag != 0)) {
		error(1, NULL, 0, NULL, 0, "Conflicting flags; -nolock and -lpilock can't both be specified for ucode compilers\n");
		exit(2);
	}
	if ((Oflag >= 3) && (cflag != 0) && (srcfiles.length == 1)) {
		error(2, NULL, 0, NULL, 0, "-c should not be used with ucode -O3 -o32 on a single file; use -j instead to get inter-module optimization.\n");
	}
	if ((srcfiles.length >= 2) && (compiler == 4) && (Eflag == 0) && (Pflag == 0)) {
		error(1, NULL, 0, NULL, 0, "only one source file can be specified with %s for ucode compilers\n", "as");
		exit(2);
	}
	mktempstr();
	for (var_s0 = 0; (var_s0 < srcfiles.length) || (uload != 0); var_s0++) {
		// var_s0 = 0;
		// if ((srcfiles.length > 0) || (uload != 0))
loop_363:
		nocompileneeded = 0;
		sp118 = NULL;
		longlong_emitted = 0;
		sp11C = D_1000BF74;
		if (var_s0 == srcfiles.length) {
			uload = 0;
			if ((runerror == 0) && (Eflag == 0) && (Pflag == 0)) {
				if (uoutfile == NULL) {
					addstr(&srcfiles, "u.out.?");
				} else if (getsuf(uoutfile) != 0) {
					addstr(&srcfiles, mksuf(uoutfile, 0x3F));
				} else {
					addstr(&srcfiles, mkstr(uoutfile, ".?", NULL));
				}
				srcsuf = 0x3F;
				if ((Hchar == 0x73) || (Hchar == 0x6D) || (Hchar == 0x6F) || (Hchar == 0x63) || (Kflag != 0)) {
					symtab = mksuf(srcfiles.entries[var_s0], 0x54);
					tmpst = 0;
				} else {
					symtab = tempstr[0];
					tmpst = 1;
				}
                goto c8d8;
			}
			continue;
		}

        if (srcfiles.length >= 2) {
            fprintf(stderr, "%s:\n", srcfiles.entries[var_s0]);
        }
        if ((NoMoreOptions != 0) && (*srcfiles.entries[var_s0] == 0x2D)) {
            passin = func_00433534(srcfiles.entries[var_s0]);
        } else {
            passin = srcfiles.entries[var_s0];
        }
        if (compiler != 4) {
            srcsuf = getsuf(srcfiles.entries[var_s0]);
            if (srcsuf == 0x6D) {
                srcsuf = 0x66;
            }
        } else {
            srcsuf = 0x73;
        }
        if ((Hchar == 0x66) || (Hchar == 0x73) || (Hchar == 0x6D) || (Hchar == 0x6F) || (Hchar == 0x6B) || (Hchar == 0x63) || (Kflag != 0) || (srcsuf == 0x42) || (srcsuf == 0x55) || (srcsuf == 0x4F) || (srcsuf == 0x47) || (srcsuf == 0x53) || (srcsuf == 0x4D) || (srcsuf == 0x56) || (srcsuf == 0x44) || (srcsuf == 0x51)) {
            tmpst = 0;
            if ((compiler == 4) && (getsuf(srcfiles.entries[var_s0]) == 0)) {
                symtab = mkstr(srcfiles.entries[var_s0], ".T", NULL);
            } else {
                symtab = mksuf(srcfiles.entries[var_s0], 0x54);
            }
        } else {
            tmpst = 1;
            symtab = tempstr[0];
        }
        switch (srcsuf) {                /* switch 11; irregular */
        case 0x73:                                  /* switch 11 */
            if ((compiler == 1) && (compdirs[0] != currcomp)) {
                currcomp = compdirs[0];
                relocate_passes("pKfjsmvocabtyz", NULL, NULL);
            }
            /* fallthrough */
        case 0x69:                                  /* switch 11 */
            if ((compiler == 1) && (compdirs[0] != currcomp)) {
                currcomp = compdirs[0];
                relocate_passes("pKfjsmvocabtyz", NULL, NULL);
            }
            /* fallthrough */
        case 0x6:                                   /* switch 11 */
        case 0x63:                                  /* switch 11 */
            if (compiler != 1) {
                if (compdirs[1] != currcomp) {
                    currcomp = compdirs[1];
                    relocate_passes("pKfjsmvocabtyz", NULL, NULL);
                }
            } else if (compdirs[0] != currcomp) {
                currcomp = compdirs[0];
                relocate_passes("pKfjsmvocabtyz", NULL, NULL);
            }
            compchoice = 0;
            break;
        case 0x70:                                  /* switch 11 */
            if (compiler != 2) {
                if (compdirs[2] != currcomp) {
                    currcomp = compdirs[2];
                    relocate_passes("pfjsmvocabtyz", NULL, NULL);
                }
            } else if (compdirs[0] != currcomp) {
                currcomp = compdirs[0];
                relocate_passes("pfjsmvocabtyz", NULL, NULL);
            }
            break;
        case 0x46:                                  /* switch 11 */
        case 0x66:                                  /* switch 11 */
            if (compiler != 3) {
                if (compdirs[3] != currcomp) {
                    currcomp = compdirs[3];
                    relocate_passes("pfjsmvocabtyz", NULL, NULL);
                }
            } else if (compdirs[0] != currcomp) {
                currcomp = compdirs[0];
                relocate_passes("pfjsmvocabtyz", NULL, NULL);
            }
            break;
        case 0x1:                                   /* switch 11 */
            if (compiler != 5) {
                if (compdirs[5] != currcomp) {
                    currcomp = compdirs[5];
                    relocate_passes("pfekjsmvocabtyz", NULL, NULL);
                }
            } else if (compdirs[0] != currcomp) {
                currcomp = compdirs[0];
                relocate_passes("pfekjsmvocabtyz", NULL, NULL);
            }
            break;
        case 0x2:                                   /* switch 11 */
            if (compiler != 6) {
                if (compdirs[6] != currcomp) {
                    currcomp = compdirs[6];
                    relocate_passes("pfekjsmvocabtyz", NULL, NULL);
                }
            } else if (compdirs[0] != currcomp) {
                currcomp = compdirs[0];
                relocate_passes("pfekjsmvocabtyz", NULL, NULL);
            }
            break;
        case 0x3:                                   /* switch 11 */
            if ((compiler != 1) && (compiler != 5) && (compiler != 6)) {
                if ((compdirs[1] != currcomp) && (compdirs[5] != currcomp) && (compdirs[6] != currcomp)) {
                    currcomp = compdirs[1];
                    relocate_passes("pekjsmvocabtyz", NULL, NULL);
                }
            } else if (compdirs[0] != currcomp) {
                currcomp = compdirs[0];
                relocate_passes("pfjsmvocabtyz", NULL, NULL);
            }
            break;
        }
        if ((compiler == 3) && (D_1000BF74 != 0) && (srcsuf != 0x66) && (srcsuf != 0x46)) {
            D_1000BF74 = 0;
            relocate_passes("f", NULL, NULL);
        }
        if ((D_1000BF74 != 0) && ((compiler == 3) || ((compiler == 1) && (c_compiler_choice != 0)))) {
            record_static_fileset(srcfiles.entries[var_s0]);
        }
        if ((compiler == 1) && (c_compiler_choice == 1)) {
            switch (ansichoice) {                   /* switch 12; irregular */
            case 1:                                 /* switch 12 */
            case 2:                                 /* switch 12 */
                edison_type = (char* )2;
                break;
            case 3:                                 /* switch 12 */
                edison_type = (char* )1;
                break;
            default:                                /* switch 12 */
            case 0:                                 /* switch 12 */
                edison_type = (char* )3;
                break;
            }
        }
loop_484:
        if (compchoice == 0) {
            if (irix4 != 0) {
                if (ansichoice == 0) {
                    compchoice = 1;
                } else {
                    compchoice = 2;
                }
            } else if (ansichoice == 0) {
                compchoice = 3;
            } else {
                compchoice = 3;
            }
        }
        if ((Eflag == 0) || (srcsuf == 0x61)) {
            switch (srcsuf) {            /* switch 19; irregular */
            case 0x6:                               /* switch 19 */
            case 0x63:                              /* switch 19 */
                if (oldccomflag != 1) {
                    oldcflag = 0;
                }
                if (docpp == 0) {
                    if (default_nocpp != 0) {
                        goto block_531;
                    }
                    goto block_940;
                }
                goto block_531;
            case 0x69:                              /* switch 19 */
                switch (compiler) { // switch 4
                case 1:
                    goto block_940;
                case 2:
                    goto block_1341;
                case 3:
                    goto block_1505;
                case 4:
                    goto block_512;
                case 5:
                    goto block_1388;
                case 6:                     /* switch 4 */
                    goto block_1453;
                }
                // fallthrough
            case 0x70:                          /* switch 19 */
block_512:
                if (stdflag == 0) {
                    if ((docpp == 0) && (default_nocpp == 0)) {
                        goto block_1341;
                    }
                    goto block_531;
                }
                goto block_1341;
            case 0x66:                              /* switch 19 */
                if (docpp != 0) {
                    goto block_531;
                }
                goto block_1505;
            case 0x1:                               /* switch 19 */
                if (docpp != 0) {
                    goto block_531;
                }
                goto block_1388;
            case 0x2:                               /* switch 19 */
                if (docpp != 0) {
                    goto block_531;
                }
                goto block_1453;
            case 0x3:                               /* switch 19 */
                goto block_1417;
            case 0x55:                              /* switch 19 */
                execlist.length = 0;
                addstr(&execlist, "utob");
                addstr(&execlist, srcfiles.entries[var_s0]);
                if (Kflag != 0) {
                    passout = mksuf(srcfiles.entries[var_s0], 0x42);
                } else {
                    passout = tempstr[1];
                }
                if ((passout != NULL) && (regular_not_writeable(passout) == 1)) {
                    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
                addstr(&execlist, passout);
                if (run(utob, execlist.entries, NULL, NULL, NULL) != 0) {
                    runerror += 1;
                    if (Kflag == 0) {
                        unlink(passout);
                    }
                } else {
                    passin = passout;
                    goto block_1729;
                }
                goto done;
            case 0x65:                              /* switch 19 */
            case 0x72:                              /* switch 19 */
            case 0x73:                              /* switch 19 */
                goto block_A;
            case 0x75:                              /* switch 19 */
                goto block_1896;
            case 0x42:                              /* switch 19 */
                goto block_1729;
            case 0x53:                              /* switch 19 */
                goto block_1913;
            }
        }
        {
block_531:
            dmips_emit = 0;
            execlist.length = 0;
            sp114 = cppchoice;
            execlist.length = 0;
            if ((Eflag != 0) && (irix4 == 0)) {
                compchoice = 3;
            } else if (srcsuf == 0x73) {
                compchoice = 4;
            }
            if ((srcsuf == 0x63) || (srcsuf == 6) || ((compiler == 1) && (nocode != 0) && (D_1000BF74 != 0) && (srcsuf == 0x68))) {
                if ((cppchoice != 2) || ((oldcppflag != 0) && (ansichoice != 0))) {
                    cppchoice = 1;
                    relocate_passes("p", NULL, NULL);
                }
            } else if ((srcsuf == 0x68) && (compiler == 1)) {
                if (cppchoice == 0) {
                    cppchoice = 1;
                    relocate_passes("p", NULL, NULL);
                }
            } else if (compiler == 1) {
                if ((Eflag == 0) && (Pflag == 0) && (cppchoice == 3)) {
                    cppchoice = 2;
                    relocate_passes("p", NULL, NULL);
                }
            } else if (cppchoice == 3) {
                cppchoice = 2;
                relocate_passes("p", NULL, NULL);
            }
            if (((compchoice == 3) || (compchoice == 4)) && (run_sopt == 0) && !(cmp_flag & 1) && !(cmp_flag & 8)) {
                addstr(&execlist, cfe);
            } else {
                if (sixty4bitflag != 0) {
                    error(1, NULL, 0, NULL, 0, "-64bit option is not implemented with ccom or accom.\n");
                    exit(2);
                }
                if (c_compiler_choice == 0) {
                    addstr(&execlist, (cppchoice != 1) && (cppchoice != 3) ? "cpp" : "acpp");
                }
            }
            if (mips_abi == 1) {
                addstr(&execlist, "-D_MIPS_FPSET=16");
                if (mips1flag != 0) {
                    addstr(&execlist, "-D_MIPS_ISA=1");
                } else if (mips2flag != 0) {
                    addstr(&execlist, "-D_MIPS_ISA=2");
                } else if (mips3flag != 0) {
                    addstr(&execlist, "-D_MIPS_ISA=3");
                }
                addstr(&execlist, "-D_ABIO32=1");
                addstr(&execlist, "-D_MIPS_SIM=_ABIO32");
                addstr(&execlist, "-D_MIPS_SZINT=32");
                addstr(&execlist, "-D_MIPS_SZLONG=32");
                addstr(&execlist, "-D_MIPS_SZPTR=32");
            } else if (mips_abi == 2) {
                addstr(&execlist, "-D_MIPS_FPSET=32");
                addstr(&execlist, "-D_MIPS_ISA=_MIPS_ISA_MIPS3");
                addstr(&execlist, "-D_MIPS_SIM=_MIPS_SIM_ABI64");
                addstr(&execlist, "-D_MIPS_SZINT=32");
                addstr(&execlist, "-D_MIPS_SZLONG=64");
                addstr(&execlist, "-D_MIPS_SZPTR=64");
            } else if (mips_abi != 0) {
                if (1) {}
                error(1, NULL, 0, NULL, 0, "Unknown value for mips_abi: %d.\n", mips_abi);
                exit(2);
            }
            if (c_compiler_choice == 0) {
                if ((emptyIflag != 0) && (compchoice != 3)) {
                    addstr(&execlist, "-nostdinc");
                }
                if (cppchoice == 1) {
                    if ((ansichoice == 0) || (ansichoice == 3)) {
                        addstr(&execlist, "-D__EXTENSIONS__");
                    }
                    if (compchoice != 3) {
                        if (fullwarn != 0) {
                            addstr(&execlist, "-Wall");
                        }
                        if (acpp_traditional != 0) {
                            addstr(&execlist, "-traditional");
                        }
                        addstr(&execlist, "-trigraphs");
                        if (ansichoice != 0) {
                            addstr(&execlist, "-undef");
                            addstr(&execlist, "-p");
                        }
                    }
                }
                if ((cppchoice == 2) && (compchoice == 3)) {
                    addstr(&execlist, "-D__EXTENSIONS__");
                }
            } else {
                addstr(&execlist, "-YE");
                if (edison_type == (char* )2) {
                    addstr(&execlist, "-a");
                }
                if ((edison_type == (char* )1) || (edison_type == (char* )3)) {
                    addstr(&execlist, "-D__EXTENSIONS__");
                }
            }

            switch (srcsuf) {        /* switch 13; irregular */
            case 0x6:
            case 0x63:
            case 0x68:
                if ((srcsuf != 0x68) || (D_1000BF74 != 0)) {
                    if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                        addstr(&execlist, "-D_LANGUAGE_C_PLUS_PLUS=1");
                        addstr(&execlist, "-D__cplusplus=1");
                        addstr(&execlist, "-D__ANSI_CPP__=1");
                        if ((compiler == 1) && (c_compiler_choice == 3)) {
                            addstr(&execlist, "-D_DELTA_EXTENSIONS=1");
                        }
                    } else {
                        if ((ansichoice == 0) || (ansichoice == 3)) {
                            addstr(&execlist, "-DLANGUAGE_C");
                        }
                        addstr(&execlist, "-D_LANGUAGE_C");
                        if (cmp_flag != 0) {
                            addstr(&execlist, "-D_LANGUAGE_PWRC");
                        }
                        if (((cmp_flag & 1) || (run_sopt != 0)) && (cppchoice == 1)) {
                            addstr(&execlist, "-trigraphs");
                        }
                    }
                }
                break;
            case 0x70:
                addstr(&execlist, "-DLANGUAGE_PASCAL");
                addstr(&execlist, "-D_LANGUAGE_PASCAL");
                addstr(&execlist, "-Q");
                break;
            case 0x46:
            case 0x65:
            case 0x66:
            case 0x72:
                addstr(&execlist, "-DLANGUAGE_FORTRAN");
                addstr(&execlist, "-D_LANGUAGE_FORTRAN");
                break;
            case 0x73:                          /* switch 13 */
                addstr(&execlist, "-DLANGUAGE_ASSEMBLY");
                addstr(&execlist, "-D_LANGUAGE_ASSEMBLY");
                break;
            case 0x1:
                addstr(&execlist, "-DLANGUAGE_PL1");
                addstr(&execlist, "-D_LANGUAGE_PL1");
                break;
            case 0x2:
                addstr(&execlist, "-DLANGUAGE_COBOL");
                addstr(&execlist, "-D_LANGUAGE_COBOL");
                break;
            }

            if ((ansichoice == 0) || (ansichoice == 3)) {
                addstr(&execlist, "-D__INLINE_INTRINSICS");
                addstr(&execlist, "-Dsgi");
                if (svr4_systype == 0) {
                    addstr(&execlist, "-DSVR3");
                    addstr(&execlist, "-D__SVR3");
                }
                addstr(&execlist, "-D__sgi");
            } else {
                addstr(&execlist, "-D__sgi");
                if (svr4_systype == 0) {
                    addstr(&execlist, "-D__SVR3");
                }
            }
            if ((compchoice != 3) && (dollar_sign != 0)) {
                if (cppchoice == 1) {
                    addstr(&execlist, "-$");
                } else {
                    addstr(&execlist, "-dollar");
                }
            }
            if ((ansichoice == 0) || (ansichoice == 3)) {
                addstr(&execlist, "-Dunix");
                addstr(&execlist, "-Dmips");
                addstr(&execlist, "-Dhost_mips");
                addstr(&execlist, "-D__unix");
                addstr(&execlist, "-D__host_mips");
                if (irix4 == 0) {
                    if ((svr4_systype != 0) && (ansichoice != 1) && (ansichoice != 2)) {
                        addstr(&execlist, "-D_SVR4_SOURCE");
                    }
                    addstr(&execlist, "-D_MODERN_C");
                    addstr(&execlist, "-D_SGI_SOURCE");
                }
                if (kpic_flag != 0) {
                    addstr(&execlist, "-D_PIC");
                }
                addstr(&execlist, "-D__DSO__");
            } else {
                addstr(&execlist, "-D__unix");
                addstr(&execlist, "-D__host_mips");
                if (irix4 == 0) {
                    if ((svr4_systype != 0) && (ansichoice != 1) && (ansichoice != 2)) {
                        addstr(&execlist, "-D_SVR4_SOURCE");
                    }
                    addstr(&execlist, "-D_MODERN_C");
                }
                if (kpic_flag != 0) {
                    addstr(&execlist, "-D_PIC");
                }
                addstr(&execlist, "-D__DSO__");
            }
            if ((systype != NULL) && (irix4 == 0)) {
                var_s1 = systype;
                while (*var_s1 != '\0') {
                    *var_s1++ = toupper(*var_s1);
                }
                if ((ansichoice == 0) || (ansichoice == 3)) {
                    addstr(&execlist, mkstr("-DSYSTYPE_", systype, NULL));
                }
                addstr(&execlist, mkstr("-D_SYSTYPE_", systype, NULL));
            }
            if (svr4_systype == 0) {
                if ((ansichoice == 0) || (ansichoice == 3)) {
                    addstr(&execlist, "-DSYSTYPE_SYSV");
                }
                addstr(&execlist, "-D_SYSTYPE_SYSV");
            }
            if (sixty4bitflag != 0) {
                addstr(&execlist, "-D__64BIT");
            }
            if (((ansichoice == 0) || (ansichoice == 3)) && (longlong_emitted == 0)) {
                addstr(&execlist, "-D_LONGLONG");
                longlong_emitted = 1;
            }
            if (dmips_emit == 0) {
                if (mips2flag != 0) {
                    if (((call_shared != 0) || (default_call_shared != 0)) && (kpic_flag == 0)) {
                        old_non_shared = 1;
                        non_shared = 1;
                        default_call_shared = 0;
                        call_shared = 0;
                    }
                    addstr(&execlist, "-D__mips=2");
                } else if (mips3flag != 0) {
                    addstr(&execlist, "-D__mips=3");
                } else {
                    addstr(&execlist, "-D__mips=1");
                }
            }
            dmips_emit = 1;
            if (irix4 != 0) {
                include = mkstr("/usr/irix4/", "usr/include", NULL);
            }
            if ((((include != NULL) && ((strcmp(comp_target_root, "/") != 0) || (systype != NULL))) || (fiveflag != 0)) && ((compiler != 1) || (c_compiler_choice == 0)) && ((compiler != 3) || (D_1000BF74 == 0))) {
                addstr(&execlist, "-I");
            }
            addlist(&execlist, &cppflags);
            if (cppchoice == 1) {
                addlist(&execlist, &acppflags);
            }
            addlist(&execlist, &undefineflags);
            if (emptyIflag == 0) {
                if ((abi_flag != 0) && (includeB != NULL)) {
                    addstr(&execlist, mkstr("-I", includeB, NULL));
                }
                if ((einclude != NULL) && (compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                    addstr(&execlist, mkstr("-I", einclude, NULL));
                }
                if (include != NULL) {
                    addstr(&execlist, mkstr("-I", include, NULL));
                }
            }
            if (Pflag != 0) {
                if ((compiler == 4) && (getsuf(srcfiles.entries[var_s0]) == 0)) {
                    passout = mkstr(srcfiles.entries[var_s0], ".i", NULL);
                } else {
                    passout = mksuf(srcfiles.entries[var_s0], 0x69);
                }
            } else if (Eflag != 0) {
                passout = NULL;
            } else if ((Hchar == 0x4B) || (Kflag != 0)) {
                if ((compchoice == 3) && (run_sopt == 0) && (acpp == 0) && (cmp_flag == 0) && (compiler == 1)) {
                    passout = mksuf(srcfiles.entries[var_s0], 0x42);
                } else {
                    passout = mksuf(srcfiles.entries[var_s0], 0x69);
                }
            } else {
                passout = tempstr[2];
            }
            if ((passout != NULL) && (regular_not_writeable(passout) == 1)) {
                error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                exit(2);
            }
            if ((compiler == 3) && (D_1000BF74 != 0)) {
                addstr(&execlist, "-K");
                addstr(&execlist, "-E");
                addstr(&execlist, sp144);
            }
            if (c_compiler_choice == 0) {
                addstr(&execlist, passin);
            }
            if (((compchoice != 3) && (compchoice != 4)) || ((compiler != 1) && (compiler != 4)) || (run_sopt != 0) || (cmp_flag & 1) || (cmp_flag & 8) || (acpp != 0) || (oldcppflag != 0)) {
                if (run((compiler == 3) && (D_1000BF74 != 0) ? cfe : cpp, execlist.entries, NULL, passout, NULL) != 0) {
                    runerror += 1;
                    if ((Eflag == 0) && ((((srcsuf == 0x65) || (srcsuf == 0x72)) && (Kflag == 0)) || ((srcsuf == 0x73) && (mflag != 0)))) {
                        unlink(passin);
                    }
                    unlink(passout);
                    cppchoice = sp114;
                    relocate_passes("p", NULL, NULL);
                    goto block_2269;
                }
                goto block_922;
            }
            cppchoice = sp114;
            relocate_passes("p", NULL, NULL);
            if (((srcsuf != 0x63) && (srcsuf != 6) && ((compiler != 1) || (nocode == 0) || (D_1000BF74 == 0) || (srcsuf != 0x68))) || (Pflag != 0) || (Eflag != 0)) {
                if (minus_M == 0) {
                    addstr(&execlist, "-E");
                }
                if ((compiler != 1) || (c_compiler_choice == 0)) {
                    switch (srcsuf) {    /* switch 16; irregular */
                    case 0x63:                      /* switch 16 */
                        addstr(&execlist, "-D_LANGUAGE_C");
                        if (oldcflag == 0) {
                            addstr(&execlist, "-D_CFE");
                        }
                        break;
                    case 0x70:                      /* switch 16 */
                        addstr(&execlist, "-DLANGUAGE_PASCAL");
                        addstr(&execlist, "-D_LANGUAGE_PASCAL");
                        addstr(&execlist, "-Q");
                        break;
                    case 0x46:                      /* switch 16 */
                    case 0x65:                      /* switch 16 */
                    case 0x66:                      /* switch 16 */
                    case 0x72:                      /* switch 16 */
                        addstr(&execlist, "-DLANGUAGE_FORTRAN");
                        addstr(&execlist, "-D_LANGUAGE_FORTRAN");
                        break;
                    case 0x73:                      /* switch 16 */
                        addstr(&execlist, "-std0");
                        addstr(&execlist, "-DLANGUAGE_ASSEMBLY");
                        addstr(&execlist, "-D_LANGUAGE_ASSEMBLY");
                        break;
                    case 0x1:                       /* switch 16 */
                        addstr(&execlist, "-DLANGUAGE_PL1");
                        addstr(&execlist, "-D_LANGUAGE_PL1");
                        break;
                    case 0x2:                       /* switch 16 */
                        addstr(&execlist, "-DLANGUAGE_COBOL");
                        addstr(&execlist, "-D_LANGUAGE_COBOL");
                        break;
                    }
                    addstr(&execlist, "-D__unix");
                    if (sixty4bitflag != 0) {
                        addstr(&execlist, "-D__64BIT");
                    }
                    if (((ansichoice == 0) || (ansichoice == 3)) && (longlong_emitted == 0)) {
                        addstr(&execlist, "-D_LONGLONG");
                        longlong_emitted = 1;
                    }
                    if (dmips_emit == 0) {
                        if (mips2flag != 0) {
                            if ((call_shared != 0) || (default_call_shared != 0)) {
                                old_non_shared = 1;
                                non_shared = 1;
                                default_call_shared = 0;
                                call_shared = 0;
                            }
                            addstr(&execlist, "-D__mips=2");
                        } else if (mips3flag != 0) {
                            addstr(&execlist, "-D__mips=3");
                        } else {
                            addstr(&execlist, "-D__mips=1");
                        }
                    }
                    dmips_emit = 1;
                    addstr(&execlist, "-D__host_mips");
                    if (kpic_flag != 0) {
                        addstr(&execlist, "-D_PIC");
                    }
                    addstr(&execlist, "-D__DSO__");
                    if (systype != NULL) {
                        var_s1 = systype;
                        while (*var_s1 != '\0') {
                            *var_s1++ = toupper(*var_s1);
                        }
                    } else {
                        addstr(&execlist, "-D_SYSTYPE_SVR4");
                    }
                }
                if ((Eflag == 0) && (Pflag == 0)) {
                    if ((((include != NULL) && ((strcmp(comp_target_root, "/") != 0) || (systype != NULL))) || (fiveflag != 0)) && (c_compiler_choice == 0)) {
                        addstr(&execlist, "-I");
                    }
                    addlist(&execlist, &cppflags);
                    addlist(&execlist, &undefineflags);
                    if (cpp_stdflag != NULL) {
                        addstr(&execlist, cpp_stdflag);
                    }
                    if (emptyIflag == 0) {
                        if ((abi_flag != 0) && (includeB != NULL)) {
                            addstr(&execlist, mkstr("-I", includeB, NULL));
                        }
                        if (include != NULL) {
                            addstr(&execlist, mkstr("-I", include, NULL));
                        }
                    }
                }
                if (((Pflag != 0) || (Eflag != 0)) && (c_compiler_choice == 0)) {
                    if ((ansichoice == 1) || (ansichoice == 2)) {
                        addstr(&execlist, "-std1");
                    } else if (ansichoice == 3) {
                        addstr(&execlist, "-std");
                    } else if (ansichoice == 0) {
                        addstr(&execlist, "-std0");
                    }
                }
                if ((compiler == 1) && (c_compiler_choice != 0)) {
                    if (vflag != 0) {
                        addstr(&execlist, "-v");
                    }
                    if (fullwarn != 0) {
                        addstr(&execlist, "-Yw");
                    }
                    if (srcfiles.length == 1) {
                        if (outfile != NULL) {
                            sp118 = outfile;
                        } else if (cflag == 0) {
                            sp118 = "a.out";
                        } else {
                            sp118 = mksuf(srcfiles.entries[var_s0], 0x6F);
                            // goto block_870;
                        }
                    } else {
                        sp118 = mksuf(srcfiles.entries[var_s0], 0x6F);
                        // block_870:
                        //                         sp118 = var_v0_4;
                    }
                    addstr(&execlist, mkstr("-YN", sp118, NULL));
                    if (c_compiler_choice == 2) {

                    } else if (c_compiler_choice == 3) {
                        addstr(&execlist, "-YD");
                    } else if (edison_type == (char* )3) {
                        addstr(&execlist, "-K");
                    } else {
                        addstr(&execlist, "-m");
                    }
                    addstr(&execlist, passin);
                }
                if (Pflag != 0) {
                    if ((compiler == 4) && (getsuf(srcfiles.entries[var_s0]) == 0)) {
                        passout = mkstr(srcfiles.entries[var_s0], ".i", NULL);
                    } else {
                        passout = mksuf(srcfiles.entries[var_s0], 0x69);
                    }
                } else if (Eflag != 0) {
                    passout = NULL;
                } else {
                    passout = tempstr[2];
                }
                if ((passout != NULL) && (regular_not_writeable(passout) == 1)) {
                    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
                if (oldcflag == 1) {
                    if (oldcppflag != 0) {
                        retcode = run(cpp, execlist.entries, NULL, passout, NULL);
                    } else {
                        retcode = run(cpp, execlist.entries, NULL, passout, NULL);
                    }
                } else if (oldcppflag != 0) {
                    retcode = run(cpp, execlist.entries, NULL, passout, NULL);
                } else {
                    retcode = run(cfe, execlist.entries, NULL, passout, NULL);
                }

                if (retcode != 0) {
                    runerror += 1;
                    if ((Eflag == 0) && ((((srcsuf == 0x65) || (srcsuf == 0x72)) && (Kflag == 0)) || ((srcsuf == 0x73) && (mflag != 0)))) {
                        unlink(passin);
                    }
                    unlink(passout);
                    goto block_2269;
                }
                if ((Pflag == 0) && (Eflag == 0)) {
                    if ((((srcsuf == 0x65) || (srcsuf == 0x72)) && (Kflag == 0)) || ((srcsuf == 0x73) && (mflag != 0))) {
                        unlink(passin);
                    }
                    passin = passout;
                    dmips_emit = 0;
                    switch (srcsuf) {    /* switch 17; irregular */
                    case 0x1:
                        goto block_1388;
                    case 0x2:                       /* switch 17 */
                        goto block_1453;
                    case 0x63:
                        goto block_940;
                    case 0x70:                      /* switch 17 */
                        goto block_1341;
                    case 0x73:                      /* switch 17 */
                        goto block_2130;
                    case 0x46:                      /* switch 17 */
                    case 0x65:                      /* switch 17 */
                    case 0x66:                      /* switch 17 */
                    case 0x72:                      /* switch 17 */
                        goto block_1505;
                    }
block_922:
                    cppchoice = sp114;
                    relocate_passes("p", NULL, NULL);
                    if (c_compiler_choice == 0) {
                        if ((Pflag == 0) && (Eflag == 0)) {
                            if ((((srcsuf == 0x65) || (srcsuf == 0x72)) && (Kflag == 0)) || ((srcsuf == 0x73) && (mflag != 0))) {
                                unlink(passin);
                            }
                            passin = passout;
                        }
                        else break;
                    }
                    dmips_emit = 0;
                    switch (srcsuf) { /* switch 18; irregular */
                    case 0x63:                  /* switch 18 */
                    case 0x64:                  /* switch 18 */
                    case 0x67:                  /* switch 18 */
                    case 0x68:                  /* switch 18 */
                    case 0x69:                  /* switch 18 */
                    case 0x6A:                  /* switch 18 */
                    case 0x6B:                  /* switch 18 */
                    case 0x6C:                  /* switch 18 */
                    case 0x6D:                  /* switch 18 */
                    case 0x6E:                  /* switch 18 */
                    case 0x6F:                  /* switch 18 */
                    case 0x71:                  /* switch 18 */
block_940:
                        if (run_sopt != 0) {
                            if (cmp_flag & 1) {
                                error(2, NULL, 0, NULL, 0, "-sopt and -pca both specified; -sopt ignored.\n");
                                goto block_989;
                            }
                            execlist.length = 0;
                            addstr(&execlist, "copt");
                            if ((Oflag >= 2) && (set_loop_unroll == 0)) {
                                addstr(&optflags, "-loopunroll");
                                addstr(&optflags, "0");
                            }
                            addstr(&execlist, mkstr("-I=", passin, NULL));
                            if ((Hchar == 0x4B) || (Kflag != 0)) {
                                passout = mksuf(srcfiles.entries[var_s0], 0x4D);
                            } else {
                                passout = mkstr(tempstr[31], "M", NULL);
                            }
                            addstr(&execlist, mkstr("-CMP=", passout, NULL));
                            addstr(&execlist, "-cp=i");
                            if (ansichoice == 0) {
                                addstr(&execlist, "-sy=k");
                            }
                            addlist(&execlist, &soptflags);
                            if (run(copt, execlist.entries, NULL, NULL, NULL) != 0) {
                                runerror += 1;
                                if ((docpp != 0) && (srcsuf != 0x69) && (Kflag == 0)) {
                                    unlink(passin);
                                }
                                if ((Hchar != 0x4B) || (Kflag != 0)) {
                                    unlink(passout);
                                }
                                break;
                            }
                            if ((docpp != 0) && (srcsuf != 0x69) && (Kflag == 0)) {
                                unlink(passin);
                            }
                            passin = passout;
                            if ((compchoice != 3) || (cmp_flag & 0x10000)) {
                                if (Hchar == 0x4B) {
                                    break;
                                }
                                if ((Hchar == 0x4B) || (Kflag != 0)) {
                                    passout = mksuf(srcfiles.entries[var_s0], 0x49);
                                } else {
                                    passout = mkstr(tempstr[31], "I", NULL);
                                }
                                // passout = var_v0_7;
                                if (vflag != 0) {
                                    addstr(&execlist, "-v");
                                }
                                execlist.length = 0;
                                addstr(&execlist, (cppchoice != 1) && (cppchoice != 3) ? "cpp" : "acpp");
                                addstr(&execlist, passin);
                                if (cppchoice != 2) {
                                    cppchoice = 1;
                                } else {
                                    addstr(&execlist, "-l");
                                }
                                if (emptyIflag != 0) {
                                    addstr(&execlist, "-nostdinc");
                                }
                                addlist(&execlist, &cpp2flags);
                                relocate_passes("p", NULL, NULL);
                                if (run(cpp, execlist.entries, NULL, passout, NULL) != 0) {
                                    runerror += 1;
                                    if (Kflag == 0) {
                                        unlink(passin);
                                    }
                                    unlink(passout);
                                    goto block_2269;
                                }
                                if (Kflag == 0) {
                                    unlink(passin);
                                }
                                passin = passout;
                                goto block_1042;

                                break;
                            }
                            goto block_1042;
                        }
block_989:
                        if ((Hchar == 0x4B) || (Kflag != 0)) {
                            cmp_flag |= 6;
                        }
                        if (cmp_flag & 1) {
                            if ((Oflag >= 2) && (set_loop_unroll == 0)) {
                                addstr(&optflags, "-loopunroll");
                                addstr(&optflags, "0");
                            }
                            execlist.length = 0;
                            addstr(&execlist, "pca");
                            addstr(&execlist, mkstr("-I=", passin, NULL));
                            if (cmp_flag & 4) {
                                passout = mksuf(srcfiles.entries[var_s0], 0x4D);
                            } else {
                                passout = mkstr(tempstr[31], "M", NULL);
                            }
                            addstr(&execlist, mkstr("-CMP=", passout, NULL));
                            if (cmp_flag & 2) {
                                sp110 = mksuf(srcfiles.entries[var_s0], 0x4C);
                            } else {
                                sp110 = mkstr(tempstr[31], "L", NULL);
                            }
                            addstr(&execlist, mkstr("-L=", sp110, NULL));
                            addstr(&execlist, "-lo=ls");
                            addstr(&execlist, "-cp=i");
                            if (ansichoice == 0) {
                                addstr(&execlist, "-sy=k");
                            }
                            addlist(&execlist, &pcaflags);
                            if (run(pca, execlist.entries, NULL, NULL, NULL) != 0) {
                                runerror += 1;
                                if ((docpp != 0) && (srcsuf != 0x69) && (Kflag == 0)) {
                                    unlink(passin);
                                }
                                if (!(cmp_flag & 4)) {
                                    unlink(passout);
                                }
                                break;
                            }
                            if (!(cmp_flag & 2)) {
                                unlink(sp110);
                            }
                            if ((docpp != 0) && (srcsuf != 0x69) && (Kflag == 0)) {
                                unlink(passin);
                            }
                            passin = passout;
                            if (Hchar != 0x4B) {
                                execlist.length = 0;
                                addstr(&execlist, (cppchoice != 1) && (cppchoice != 3) ? "cpp" : "acpp");
                                if ((Hchar == 0x4B) || (Kflag != 0)) {
                                    passout = mksuf(srcfiles.entries[var_s0], 0x49);
                                } else {
                                    passout = mkstr(tempstr[31], "I", NULL);
                                }
                                if (vflag != 0) {
                                    addstr(&execlist, "-v");
                                }
                                addstr(&execlist, passin);
                                if (cppchoice != 2) {
                                    cppchoice = 1;
                                } else {
                                    addstr(&execlist, "-l");
                                }
                                if (emptyIflag != 0) {
                                    addstr(&execlist, "-nostdinc");
                                }
                                addlist(&execlist, &cpp2flags);
                                addlist(&execlist, &undefineflags);
                                relocate_passes("p", NULL, NULL);
                                if (run(cpp, execlist.entries, NULL, passout, NULL) != 0) {
                                    runerror += 1;
                                    if ((Kflag == 0) && !(cmp_flag & 4)) {
                                        unlink(passin);
                                    }
                                    unlink(passout);
                                    goto block_2269;
                                }
                                if ((Kflag == 0) && !(cmp_flag & 4)) {
                                    unlink(passin);
                                }
                                passin = passout;
                            }
                            else break;
                        }


block_1042:
                        if (gflag >= 2) {
                            func_00431D00(srcfiles.entries[var_s0]);
                        }
                        if ((compiler == 1) && (c_compiler_choice != 0)) {
                            if ((docpp == 0) || (oldcppflag != 0) || (run_sopt != 0) || (srcsuf == 0x69) || (acpp != 0)) {
                                execlist.length = 0;
                                addstr(&execlist, cfe);
                            }
                            if (vflag != 0) {
                                addstr(&execlist, "-v");
                            }
                            if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                                if (anachronisms != 0) {
                                    addstr(&execlist, "-O");
                                }
                                if (cfront_compatible != 0) {
                                    addstr(&execlist, "-b");
                                }
                            }
                            if (nocode != 0) {
                                addstr(&execlist, "-n");
                            }
                            if (Fflag == 0) {
                                addstr(&execlist, "-Zz");
                                addstr(&execlist, "-ZO");
                                addstr(&execlist, mkstr("-ZS", symtab, NULL));
                            }
                            if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                                if (Oflag >= 3) {
                                    addstr(&execlist, "-Qz");
                                }
                                if (non_shared != 0) {
                                    addstr(&execlist, "-Qn");
                                }
                            }
                            if (signedcharflag != 0) {
                                addstr(&execlist, "-s");
                            } else {
                                addstr(&execlist, "-u");
                            }
                            if (fullwarn != 0) {
                                addstr(&execlist, "-Yw");
                            }
                            if (disable_inlines != 0) {
                                addstr(&execlist, "-YJ");
                            }
                            if (c_compiler_choice == 2) {
                            } else if (c_compiler_choice == 3) {
                                addstr(&execlist, "-YD");
                            } else if (edison_type == (char* )3) {
                                addstr(&execlist, "-K");
                            } else {
                                addstr(&execlist, "-m");
                            }

                            if (srcsuf == 0x69) {
                                addstr(&execlist, "-Yp");
                            }
                            if (smart_build != 0) {
                                addstr(&execlist, mkstr("-YR", sbrepos, NULL));
                            }
                            if (srcfiles.length == 1) {
                                if (outfile != NULL) {
                                    sp118 = outfile;
                                } else if (cflag == 0) {
                                    sp118 = "a.out";
                                } else {
                                    sp118 = mksuf(srcfiles.entries[var_s0], 0x6F);
                                }
                            } else {
                                sp118 = mksuf(srcfiles.entries[var_s0], 0x6F);
                            }
                            addstr(&execlist, mkstr("-YN", sp118, NULL));
                            if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
                                switch (default_template_instantiation_mode) {
                                case 0:
                                    break;
                                case 1:
                                    addstr(&execlist, "-tused");
                                    break;
                                case 2:
                                    addstr(&execlist, "-tall");
                                    break;
                                }
                                if (no_prelink != 0) {
                                    addstr(&execlist, "-T");
                                } else {
                                    if ((outfile != NULL) && (cflag != 0) && (srcfiles.length == 1)) {
                                        sp10C = outfile;
                                    } else {
                                        sp10C = mksuf(srcfiles.entries[var_s0], 0x6F);
                                    }
                                    sp108 = make_ii_file_name(sp10C);
                                    addstr(&execlist, mkstr("-YO", sp108, NULL));
                                    free(sp108);
                                }
                                if (auto_template_include == 0) {
                                    addstr(&execlist, "-B");
                                }
                            }
                            if (gflag >= 2) {
                                addstr(&execlist, mkstr("-Zc", tempstr[33], NULL));
                            }
                            addstr(&execlist, mkstr("-YG", Gnum, NULL));
                            addlist(&execlist, &edisonflags);
                            if (dollar_sign != 0) {
                                addstr(&execlist, "-$");
                            }
                            if (Fflag != 0) {
                                addstr(&execlist, mkstr("-", NULL));
                            } else {
                                addstr(&execlist, passin);
                            }
                            var_s1 = 0;
                        }
                        if (compchoice == 3) {
                            if (cmp_flag & 0x10000) {
                                if ((Hchar == 0x4D) || (Kflag != 0) || (cmp_flag & 4)) {
                                    passout = mksuf(srcfiles.entries[var_s0], 0x50);
                                } else {
                                    passout = mkstr(tempstr[31], "P", NULL);
                                }
                                execlist.length = 0;
                                addstr(&execlist, mpc);
                                addstr(&execlist, passin);
                                addstr(&execlist, mkstr("-K", passout, NULL));
                                if ((ansichoice == 1) || (ansichoice == 2)) {
                                    addstr(&execlist, "-ansi");
                                } else if (ansichoice == 0) {
                                    addstr(&execlist, "-cckr");
                                } else {
                                    addstr(&execlist, "-xansi");
                                }
                                addlist(&execlist, &mpcflags);
                                retcode = run(mpc, execlist.entries, NULL, NULL, errout);
                                if (Kflag == 0) {
                                    unlink(passin);
                                }
                                if (retcode != 0) {
                                    runerror += 1;
                                    if ((Hchar != 0x4D) && (Kflag == 0) && !(cmp_flag & 4)) {
                                        unlink(passout);
                                    }
                                    break;
                                }
                                if (Hchar != 0x4D) {
                                    passin = passout;
                                }
                                else break;
                            }
                            if (((docpp == 0) || (oldcppflag != 0) || (run_sopt != 0) || (srcsuf == 0x69) || (acpp != 0) || (cmp_flag & 0x10000)) && (c_compiler_choice == 0)) {
                                execlist.length = 0;
                                addstr(&execlist, cfe);
                                addstr(&execlist, passin);
                            }
                            if (Hchar == 0x66) {
                                if (ucodeflag != 0) {
                                    passout = tempstr[3];
                                } else {
                                    passout = mksuf(srcfiles.entries[var_s0], 0x42);
                                }
                            } else if (((Fflag != 0) && (plusIflag == 0)) || (nocode != 0)) {
                                passout = NULL;
                            } else if (plusIflag != 0) {
                                passout = mksuf(srcfiles.entries[var_s0], 7);
                            } else if (Kflag != 0) {
                                passout = mksuf(srcfiles.entries[var_s0], 0x42);
                            } else {
                                passout = tempstr[3];
                            }
                            if ((passout != NULL) && (regular_not_writeable(passout) == 1)) {
                                error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                exit(2);
                            }
                            if (((docpp == 0) || (srcsuf == 0x69) || (acpp != 0) || (oldcppflag != 0)) && (run_sopt == 0)) {
                                if ((default_nocpp == 0) && ((srcsuf == 0x63) || (srcsuf == 0x73) || (srcsuf == 0x70))) {
                                    addstr(&execlist, "-nocpp");
                                }
                                if (srcsuf == var_s0) {
                                    addstr(&execlist, "-nocpp");
                                }
                            }
                            if (c_compiler_choice == 0) {
                                if (vflag != 0) {
                                    addstr(&execlist, "-Xv");
                                }
                                if (compiler == 1) {
                                    if ((run_sopt == 0) && !(cmp_flag & 1)) {
                                        addstr(&execlist, "-D_CFE");
                                        addstr(&execlist, "-Amachine(mips)");
                                        addstr(&execlist, "-Asystem(unix)");
                                        addlist(&execlist, &accomflags);
                                    }
                                    addlist(&execlist, &cfeflags);
                                    addstr(&execlist, "-G");
                                    addstr(&execlist, Gnum);
                                }
                                if ((ansichoice == 1) || (ansichoice == 2)) {
                                    addstr(&execlist, "-std1");
                                } else if (ansichoice == 3) {
                                    addstr(&execlist, "-std");
                                } else if (ansichoice == 0) {
                                    addstr(&execlist, "-std0");
                                }
                                if (prototype_checking_on != 0) {
                                    addstr(&execlist, "-Xprototypes");
                                }
                                addstr(&execlist, mkstr("-XS", symtab, NULL));
                                addlist(&execlist, &ccomflags);
                                if (gflag >= 2) {
                                    addstr(&execlist, mkstr("-Xcmd:", tempstr[33], NULL));
                                }
                            }
                            if ((run_sopt != 0) || (cmp_flag & 1)) {
                                unlink(tempstr[2]);
                            }
                            if (run_sopt != 0) {
                                addlist(&execlist, &undefineflags);
                            }
                            retcode = run(cfe, execlist.entries, Fflag != 0 ? passin : NULL, passout, errout);
                            if ((smart_build != 0) && (retcode == 0xFA)) {
                                retcode = 0;
                                nocompileneeded = 1;
                                if ((outfile != NULL) && (cflag != 0) && (srcfiles.length == 1)) {
                                    sp104 = outfile;
                                } else if ((srcsuf == 0x3F) && (Hchar != 0x62) && (Kflag == 0)) {
                                    tmp_uldobj = sp104 = tempstr[12];
                                } else {
                                    sp104 = mksuf(srcfiles.entries[var_s0], 0x6F);
                                }
                                if (touch(sp118) < 0) {
                                    runerror += 1;
                                }
                                if ((srcfiles.length != 1) || (cflag != 0)) {
                                    goto block_1227;
                                }
                                goto block_2588;
                            }
block_1227:
                            if (Fflag == 0) {
                                if (retcode == 0xFF) {
                                    c_inline = 1;
                                    addstr(&umergeflags, "-c_inline");
                                    goto block_1238;
                                }
                                if (retcode != 0) {
                                    runerror += 1;
                                    if ((oldcflag == 1) && (docpp != 0) && (srcsuf != 0x69) && (c_compiler_choice == 0)) {
                                        unlink(passin);
                                    }
                                    if (Kflag == 0) {
                                        unlink(passout);
                                        unlink(symtab);
                                    }
                                } else {
block_1238:
                                    if (((run_sopt != 0) && (Kflag == 0)) || (acpp != 0) || (oldcppflag != 0) || (cmp_flag & 0x10000)) {
                                        unlink(passin);
                                    }
                                    if ((NoMoreOptions != 0) && (*passout == 0x2D)) {
                                        passout = func_00433534(passout);
                                    }
                                    passin = passout;
                                    if ((Hchar == 0x66) && (ucodeflag != 0)) {
                                        execlist.length = 0;
                                        addstr(&execlist, "btou");
                                        addstr(&execlist, passin);
                                        passout = mksuf(srcfiles.entries[var_s0], 0x55);
                                        if ((passout != NULL) && (regular_not_writeable(passout) == 1)) {
                                            error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                            exit(2);
                                        }
                                        addstr(&execlist, passout);
                                        if (run(btou, execlist.entries, NULL, NULL, NULL) != 0) {
                                            runerror += 1;
                                            if (Kflag == 0) {
                                                unlink(passin);
                                                unlink(passout);
                                            }
                                            if (tmpst != 0) {
                                                unlink(symtab);
                                            }
                                        } else if (Kflag == 0) {
                                            unlink(passin);
                                        }
                                    } else {
                                        passin = passout;
                                        if (Hchar != 0x66) {
                                            if ((compiler == 1) && (c_compiler_choice != 0) && ((Eflag != 0) || (nocode != 0) || (nocompileneeded != 0))) {
                                                unlink(passout);
                                            } else {
                                                goto block_1729;
                                            }
                                        }
                                    }
                                }
                            }
                            break;
                        }
                        execlist.length = 0;
                        addstr(&execlist, ansichoice != 0 ? "accom" : "ccom");
                        if (vflag != 0) {
                            addstr(&execlist, "-Xv");
                        }
                        if (cmp_flag & 0x10000) {
                            addstr(&execlist, "-XMP");
                        }
                        addlist(&execlist, &ccomflags);
                        if (dollar_sign != 0) {
                            addstr(&execlist, "-Xdollar");
                        }
                        if (use_real_fp != 0) {
                            addstr(&execlist, "-Xreal_fp");
                        }
                        if ((prototype_checking_on != 0) || (ansichoice != 0)) {
                            addstr(&execlist, "-Xprototypes");
                        }
                        if (ansichoice != 0) {
                            if (ansichoice == 3) {
                                addstr(&execlist, "-Xxansi");
                            } else {
                                addstr(&execlist, "-Xansi");
                            }
                            addlist(&execlist, &accomflags);
                        }
                        if (Hchar == 0x66) {
                            if (ucodeflag != 0) {
                                passout = tempstr[3];
                            } else {
                                passout = mksuf(srcfiles.entries[var_s0], 0x42);
                            }
                        } else if (Kflag != 0) {
                            passout = mksuf(srcfiles.entries[var_s0], 0x42);
                        } else {
                            passout = tempstr[3];
                        }
                        if (regular_not_writeable(passout) == 1) {
                            error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                            exit(2);
                        }
                        addstr(&execlist, mkstr("-XS", symtab, NULL));
                        if ((Kflag == 0) && (docpp != 0) && (srcsuf != 0x69)) {
                            var_s1 = passin;
                        } else {
                            addstr(&execlist, passin);
                            var_s1 = NULL;
                        }
                        retcode = run(ccom, execlist.entries, var_s1, passout, errout);
                        if (retcode == 0xFF) {
                            c_inline = 1;
                            addstr(&umergeflags, "-c_inline");
                            goto block_1317;
                        }
                        if (retcode != 0) {
                            if (editflag != 0) {
                                if (times_edited < edit_cnt_max) {
                                    times_edited += 1;
                                    if (edit_src(editor, srcfiles.entries[var_s0], 1) != 0) {
                                        show_err(errout);
                                        exit(1);
                                    }
                                    if ((docpp != 0) && (srcsuf != 0x69)) {
                                        unlink(passin);
                                    }
                                    unlink(passout);
                                    unlink(errout);
                                    unlink(symtab);
                                    passin = srcfiles.entries[var_s0];
                                    goto loop_484;
                                }
                                show_err(errout);
                                goto block_1311;
                            }
block_1311:
                            runerror += 1;
                            if ((Kflag == 0) && (docpp != 0) && (srcsuf != 0x69)) {
                                unlink(passin);
                            }
                            if (Kflag == 0) {
                                unlink(passout);
                                unlink(symtab);
                            }
                            break;
                        }
block_1317:
                        if (editflag != 0) {
                            unlink(errout);
                        }
                        if ((Kflag == 0) && (docpp != 0) && (srcsuf != 0x69)) {
                            unlink(passin);
                        }
                        passin = passout;
                        if ((Hchar == 0x66) && (ucodeflag != 0)) {
                            execlist.length = 0;
                            addstr(&execlist, "btou");
                            addstr(&execlist, passin);
                            passout = mksuf(srcfiles.entries[var_s0], 0x55);
                            if (regular_not_writeable(passout) == 1) {
                                error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                exit(2);
                            }
                            addstr(&execlist, passout);
                            if (run(btou, execlist.entries, NULL, NULL, NULL) != 0) {
                                runerror += 1;
                                if (Kflag == 0) {
                                    unlink(passin);
                                    unlink(passout);
                                }
                                if (tmpst != 0) {
                                    unlink(symtab);
                                }
                            } else if (Kflag == 0) {
                                unlink(passin);
                            }
                            continue;
                        } else if (
                                Hchar == 0x66 ||
                                (
                                    (compiler == 1 && c_compiler_choice != 0) &&
                                    (Eflag != 0 || nocode != 0 || nocompileneeded != 0)
                                 )) {
                            continue;
                        } else {
                            goto block_1729;
                        }

                    case 0x70:                  /* switch 18 */
block_1341:
                        execlist.length = 0;
                        addstr(&execlist, "upas");
                        if (vflag != 0) {
                            addstr(&execlist, "-v");
                        }
                        addstr(&execlist, "-G");
                        addstr(&execlist, Gnum);
                        addlist(&execlist, &upasflags);
                        addstr(&execlist, passin);
                        if (((Hchar == 0x66) && (ucodeflag == 0)) || (Kflag != 0)) {
                            passout = mksuf(srcfiles.entries[var_s0], 0x42);
                            if (regular_not_writeable(passout) == 1) {
                                error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                exit(2);
                            }
                        } else {
                            passout = tempstr[3];
                        }
                        addstr(&execlist, passout);
                        addstr(&execlist, "-t");
                        addstr(&execlist, symtab);
                        if (run(upas, execlist.entries, NULL, NULL, errout) != 0) {
                            if (editflag != 0) {
                                if (times_edited < edit_cnt_max) {
                                    times_edited += 1;
                                    if (edit_src(editor, srcfiles.entries[var_s0], 2) != 0) {
                                        show_err(errout);
                                        exit(1);
                                    }
                                    if ((stdflag == 0) && (docpp != 0) && (srcsuf != 0x69) && (Kflag == 0)) {
                                        unlink(passin);
                                    }
                                    unlink(passout);
                                    unlink(errout);
                                    unlink(symtab);
                                    passin = srcfiles.entries[var_s0];
                                    goto loop_484;
                                }
                                show_err(errout);
                                goto block_1361;
                            }
block_1361:
                            runerror += 1;
                            if ((stdflag == 0) && (docpp != 0) && (srcsuf != 0x69) && (Kflag == 0)) {
                                unlink(passin);
                            }
                            if (Kflag == 0) {
                                unlink(passout);
                                unlink(symtab);
                            }
                            break;
                        }
                        if (editflag != 0) {
                            unlink(errout);
                        }
                        if ((stdflag == 0) && (docpp != 0) && (srcsuf != 0x69) && (Kflag == 0)) {
                            unlink(passin);
                        }
                        passin = passout;
                        if ((Hchar == 0x66) && (ucodeflag != 0)) {
                            execlist.length = 0;
                            addstr(&execlist, "btou");
                            addstr(&execlist, passin);
                            passout = mksuf(srcfiles.entries[var_s0], 0x55);
                            if (regular_not_writeable(passout) == 1) {
                                error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                exit(2);
                            }
                            addstr(&execlist, passout);
                            if (run(btou, execlist.entries, NULL, NULL, NULL) != 0) {
                                runerror += 1;
                                if (Kflag == 0) {
                                    unlink(passin);
                                    unlink(passout);
                                }
                                if (tmpst != 0) {
                                    unlink(symtab);
                                }
                            } else if (Kflag == 0) {
                                unlink(passin);
                            }
                        } else if (Hchar == 0x66) {

                        } else {
                            goto block_1729;
                        }
                        break;
                    case 0x1:                   /* switch 18 */
block_1388:
                        execlist.length = 0;
                        addstr(&execlist, "pl1fe");
                        if (vflag != 0) {
                            addstr(&execlist, "-v");
                        }
                        addlist(&execlist, &upl1flags);
                        addstr(&execlist, passin);
                        if ((Hchar == 0x66) || (Kflag != 0)) {
                            passout = mksuf(srcfiles.entries[var_s0], 3);
                            lpi_st = mksuf(srcfiles.entries[var_s0], 4);
                        } else {
                            passout = tempstr[16];
                            lpi_st = tempstr[17];
                        }
                        lpi_p1 = tempstr[18];
                        addstr(&execlist, "-o");
                        addstr(&execlist, passout);
                        addstr(&execlist, "-s");
                        addstr(&execlist, lpi_st);
                        addstr(&execlist, "-p");
                        addstr(&execlist, lpi_p1);
                        addstr(&execlist, "-e");
                        addstr(&execlist, pl1err);
                        if (run(upl1, execlist.entries, NULL, errout, NULL) != 0) {
                            if (editflag != 0) {
                                if (times_edited < edit_cnt_max) {
                                    times_edited += 1;
                                    if (edit_src(editor, srcfiles.entries[var_s0], 5) != 0) {
                                        show_err(errout);
                                        exit(1);
                                    }
                                    if ((docpp != 0) && (srcsuf != 0x69)) {
                                        unlink(passin);
                                    }
                                    unlink(passout);
                                    unlink(errout);
                                    unlink(lpi_st);
                                    unlink(lpi_p1);
                                    passin = srcfiles.entries[var_s0];
                                    goto loop_484;
                                }
                                show_err(errout);
                                goto block_1404;
                            }
block_1404:
                            runerror += 1;
                            if ((docpp != 0) && (srcsuf != 0x69)) {
                                unlink(passin);
                            }
                            if (Kflag == 0) {
                                unlink(passout);
                                unlink(lpi_st);
                            }
                            unlink(lpi_p1);
                            goto block_2269;
                        }
                        if (editflag != 0) {
                            unlink(errout);
                        }
                        unlink(lpi_p1);
                        if ((docpp != 0) && (srcsuf != 0x69)) {
                            unlink(passin);
                        }
                        if (Hchar != 0x66) {
                            passin = passout;
block_1417:
                            execlist.length = 0;
                            addstr(&execlist, "ulpi");
                            if (vflag != 0) {
                                addstr(&execlist, "-v");
                            }
                            addlist(&execlist, &ulpiflags);
                            addstr(&execlist, passin);
                            if (((Hchar == 0x6B) && (ucodeflag == 0)) || (Kflag != 0)) {
                                passout = mksuf(srcfiles.entries[var_s0], 0x42);
                            } else {
                                passout = tempstr[3];
                            }
                            if ((srcsuf == 3) || (Kflag != 0)) {
                                lpi_st = mksuf(srcfiles.entries[var_s0], 4);
                            } else {
                                lpi_st = tempstr[17];
                            }
                            addstr(&execlist, "-s");
                            addstr(&execlist, lpi_st);
                            addstr(&execlist, "-o");
                            addstr(&execlist, passout);
                            addstr(&execlist, "-t");
                            addstr(&execlist, symtab);
                            if (run(ulpi, execlist.entries, NULL, NULL, NULL) != 0) {
                                runerror += 1;
                                if (srcsuf != 3) {
                                    unlink(passin);
                                }
                                if (Kflag == 0) {
                                    unlink(passout);
                                    if (srcsuf != 3) {
                                        unlink(lpi_st);
                                    }
                                }
                                if (tmpst != 0) {
                                    unlink(symtab);
                                }
                            } else {
                                if ((srcsuf != 3) && (Kflag == 0)) {
                                    unlink(passin);
                                }
                                if ((Kflag == 0) && (srcsuf != 3)) {
                                    unlink(lpi_st);
                                }
                                passin = passout;
                                if ((Hchar == 0x6B) && (ucodeflag != 0)) {
                                    execlist.length = 0;
                                    addstr(&execlist, "btou");
                                    addstr(&execlist, passin);
                                    passout = mksuf(srcfiles.entries[var_s0], 0x55);
                                    addstr(&execlist, passout);
                                    if (run(btou, execlist.entries, NULL, NULL, NULL) != 0) {
                                        runerror += 1;
                                        if (Kflag == 0) {
                                            unlink(passin);
                                            unlink(passout);
                                        }
                                        if (tmpst != 0) {
                                            unlink(symtab);
                                        }
                                    } else if (Kflag == 0) {
                                        unlink(passin);
                                    }
                                } else if (Hchar == 0x6B) {

                                } else {
                                    goto block_1729;
                                }
                            }
                        }
                        break;
                    case 0x2:                   /* switch 18 */
block_1453:
                        execlist.length = 0;
                        addstr(&execlist, "cobfe");
                        if (vflag != 0) {
                            addstr(&execlist, "-v");
                        }
                        addlist(&execlist, &ucobflags);
                        addstr(&execlist, passin);
                        if ((Hchar == 0x66) || (Kflag != 0)) {
                            passout = mksuf(srcfiles.entries[var_s0], 3);
                            lpi_st = mksuf(srcfiles.entries[var_s0], 4);
                        } else {
                            passout = tempstr[16];
                            lpi_st = tempstr[17];
                        }
                        lpi_p1 = tempstr[18];
                        lpi_pd = tempstr[20];
                        lpi_dd = tempstr[19];
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
                        if (run(ucob, execlist.entries, NULL, errout, NULL) != 0) {
                            if (editflag != 0) {
                                if (times_edited < edit_cnt_max) {
                                    times_edited += 1;
                                    if (edit_src(editor, srcfiles.entries[var_s0], 6) != 0) {
                                        show_err(errout);
                                        exit(1);
                                    }
                                    if ((docpp != 0) && (srcsuf != 0x69)) {
                                        unlink(passin);
                                    }
                                    unlink(passout);
                                    unlink(errout);
                                    unlink(lpi_st);
                                    unlink(lpi_p1);
                                    unlink(lpi_pd);
                                    unlink(lpi_dd);
                                    passin = srcfiles.entries[var_s0];
                                    goto loop_484;
                                }
                                show_err(errout);
                                goto block_1469;
                            }
block_1469:
                            runerror += 1;
                            if ((docpp != 0) && (srcsuf != 0x69)) {
                                unlink(passin);
                            }
                            if (Kflag == 0) {
                                unlink(passout);
                                unlink(lpi_st);
                            }
                            unlink(lpi_p1);
                            unlink(lpi_pd);
                            unlink(lpi_dd);
                            goto block_2269;
                        }
                        if (editflag != 0) {
                            unlink(errout);
                        }
                        if ((docpp != 0) && (srcsuf != 0x69)) {
                            unlink(passin);
                        }
                        unlink(lpi_p1);
                        unlink(lpi_pd);
                        unlink(lpi_dd);
                        if (Hchar != 0x66) {
                            passin = passout;
                            goto block_1417;
                        }
                        break;
block_A:
                        if (mflag != 0) {
                            execlist.length = 0;
                            addstr(&execlist, "m4");
                            addstr(&execlist, passin);
                            if ((compiler == 4) || (srcsuf == 0x73)) {
                                passout = tempstr[14];
                            } else {
                                passout = mksuf(srcfiles.entries[var_s0], 0x70);
                            }
                            if (run(m4, execlist.entries, NULL, passout, NULL) != 0) {
                                runerror += 1;
                                if (Kflag == 0) {
                                    unlink(passout);
                                }
                                continue;
                            }
                            passin = passout;
                        }

                        switch (srcsuf) {
                        case 0x73:
                            if (docpp == 0) {
                                if (default_nocpp != 0) {
                                    goto block_531;
                                }
                                goto block_2130;
                            }
                            goto block_531;
                        case 0x65:
                        default:
                            error(1, NULL, 0, NULL, 0, "efl not supported. Cannot use .e files\n");
                            exit(2);
                        case 0x72:
                            execlist.length = 0;
                            addstr(&execlist, "ratfor");
                            addlist(&execlist, &ratforflags);
                            addstr(&execlist, passin);
                            passout = mksuf(srcfiles.entries[var_s0], 0x66);
                            if (run(ratfor, execlist.entries, NULL, passout, NULL) != 0) {
                                runerror += 1;
                                if (Kflag == 0) {

                                }
                                break;
                            }
                            if (mflag != 0) {
                                unlink(passin);
                            }
                            passin = passout;
                            if (Fflag == 0) {
                                if (docpp == 0) {
                                    // TODO: pointless 'b'
                                    goto block_1505;
                                }
                                goto block_531;
                            }
                            break;
                        }
                        break;

                    case 0x46:                  /* switch 18 */
                    case 0x65:                  /* switch 18 */
                    case 0x66:                  /* switch 18 */
                    case 0x72:                  /* switch 18 */
block_1505:
                        sp100 = 0;
                        spFC = 0;
                        spF0[0] = 0x31;
                        spF0[1] = 0;
                        if (run_sopt != 0) {
                            if (mp_flag & 1) {
                                error(2, NULL, 0, NULL, 0, "-sopt and -pfa both specified; -sopt ignored.\n");
                                goto block_1566;
                            }
                            if ((Oflag >= 2) && (set_loop_unroll == 0)) {
                                addstr(&optflags, "-loopunroll");
                                addstr(&optflags, "0");
                            }
                            if ((mp_i2flag != 0) && (w1flag != 2)) {
                                error(2, NULL, 0, NULL, 0, "fopt does not recognize the -i2 option\n");
                            }
                            if ((mp_66flag != 0) && (w1flag != 2)) {
                                error(2, NULL, 0, NULL, 0, "fopt does not recognize the -66 option\n");
                            }
                            if ((mp_uflag != 0) && (w1flag != 2)) {
                                error(2, NULL, 0, NULL, 0, "fopt does not recognize the -u option\n");
                            }
                            if ((mp_backslashflag != 0) && (w1flag != 2)) {
                                error(2, NULL, 0, NULL, 0, "fopt does not support the -backslash option\n");
                            }
                            if (mp_caseflag != 0) {
                                error(1, NULL, 0, NULL, 0, "fopt does not support the -U option\n");
                                exit(2);
                            }
                            execlist.length = 0;
                            addstr(&execlist, "fopt");
                            spF4 = mkstr(tempstr[31], "l", NULL);
                            addstr(&execlist, mkstr("-L=", spF4, NULL));
                            if ((Hchar == 0x4B) || (Kflag != 0)) {
                                passout = mksuf(srcfiles.entries[var_s0], 0x6D);
                            } else {
                                passout = mkstr(tempstr[31], "m", &spF0, NULL);
                            }
                            addstr(&execlist, mkstr("-F=", passout, NULL));
                            addstr(&execlist, mkstr("-I=", passin, NULL));
                            if (mp_col120flag != 0) {
                                addstr(&execlist, "-scan=120");
                            }
                            if (mp_extendflag != 0) {
                                addstr(&execlist, "-scan=132");
                            }
                            if (automaticflag == 0) {
                                addstr(&execlist, "-save=all");
                            }
                            if (mp_onetripflag != 0) {
                                addstr(&execlist, "-onetrip");
                            }
                            if (mp_dlinesflag != 0) {
                                addstr(&execlist, "-dlines");
                            }
                            if (w1flag == 2) {
                                addstr(&execlist, "-suppress=w");
                            }
                            if (vflag != 0) {
                                addstr(&execlist, "-lo=lno");
                            }
                            if (irix4 != 0) {
                                addstr(&execlist, mkstr("-customer=", mksuf(srcfiles.entries[var_s0], srcsuf), NULL));
                            } else {
                                addstr(&execlist, mkstr("-original_filename=", mksuf(srcfiles.entries[var_s0], srcsuf), NULL));
                            }
                            addstr(&execlist, "-include=/usr/include", 0);
                            addstr(&execlist, "-cp=i");
                            addlist(&execlist, &soptflags);
                            if (run(fopt, execlist.entries, NULL, NULL, NULL) != 0) {
                                runerror += 1;
                                if (((docpp != 0) || (srcsuf == 0x65) || (srcsuf == 0x72)) && (srcsuf != 0x69) && (Kflag == 0)) {
                                    unlink(passin);
                                }
                                if ((Hchar != 0x4B) || (Kflag != 0)) {
                                    unlink(passout);
                                }
                                unlink(spF4);
                                goto block_2269;
                            }
                            if (((docpp != 0) || (srcsuf == 0x65) || (srcsuf == 0x72) || (srcsuf == 0x46)) && (srcsuf != 0x69) && (Kflag == 0)) {
                                unlink(passin);
                            }
                            unlink(spF4);
                            passin = passout;
                            if (Hchar == 0x4B) {
                                break;
                            }
                            goto block_1660;
                        }
block_1566:
                        if ((Hchar == 0x4B) || (Kflag != 0)) {
                            mp_flag |= 6;
                        }
                        if (mp_flag & 1) {
                            if ((Oflag >= 2) && (set_loop_unroll == 0)) {
                                addstr(&optflags, "-loopunroll");
                                addstr(&optflags, "0");
                            }
                            if ((mp_i2flag != 0) && (w1flag != 2)) {
                                error(2, NULL, 0, NULL, 0, "PFA does not recognize the -i2 option\n");
                            }
                            if ((mp_66flag != 0) && (w1flag != 2)) {
                                error(2, NULL, 0, NULL, 0, "PFA does not recognize the -66 option\n");
                            }
                            if ((mp_uflag != 0) && (w1flag != 2)) {
                                error(2, NULL, 0, NULL, 0, "PFA does not recognize the -u option\n");
                            }
                            if ((mp_backslashflag != 0) && (w1flag != 2)) {
                                error(2, NULL, 0, NULL, 0, "PFA does not support the -backslash option\n");
                            }
                            if (mp_caseflag != 0) {
                                error(1, NULL, 0, NULL, 0, "PFA does not support the -U option\n");
                                exit(2);
                            }
loop_1587:
                            execlist.length = 0;
                            addstr(&execlist, "pfa");
                            spF0[0] = spFC + 0x31;
                            if (mp_flag & 2) {
                                spF8 = mksuf(srcfiles.entries[var_s0], 0x6C);
                                if (spFC < mp_prepass_count) {
                                    spF8 = mkstr(spF8, spF0, NULL);
                                }
                            } else {
                                spF8 = mkstr(tempstr[31], "l", spF0, NULL);
                            }
                            addstr(&execlist, mkstr("-L=", spF8, NULL));
                            if (mp_flag & 4) {
                                passout = mksuf(srcfiles.entries[var_s0], 0x6D);
                                if (spFC < mp_prepass_count) {
                                    passout = mkstr(passout, spF0, NULL);
                                }
                            } else {
                                passout = mkstr(tempstr[31], "m", spF0, NULL);
                            }
                            addstr(&execlist, mkstr("-F=", passout, NULL));
                            addstr(&execlist, mkstr("-I=", passin, NULL));
                            if (mp_col120flag != 0) {
                                addstr(&execlist, "-scan=120");
                            }
                            if (mp_extendflag != 0) {
                                addstr(&execlist, "-scan=132");
                            }
                            if (automaticflag == 0) {
                                addstr(&execlist, "-save=all");
                            }
                            if (mp_onetripflag != 0) {
                                addstr(&execlist, "-onetrip");
                            }
                            if (mp_dlinesflag != 0) {
                                addstr(&execlist, "-dlines");
                            }
                            if (w1flag == 2) {
                                addstr(&execlist, "-suppress=w");
                            }
                            if (vflag != 0) {
                                addstr(&execlist, "-lo=lno");
                            } else {
                                addstr(&execlist, "-lo=lo");
                            }
                            if (mp_flag & 2) {
                                addstr(&execlist, mkstr("-analysis=", mksuf(srcfiles.entries[var_s0], 5), NULL));
                            } else if (irix4 == 0) {
                                addstr(&execlist, "-noanalysis");
                            }
                            if (irix4 != 0) {
                                addstr(&execlist, mkstr("-customer=", mksuf(srcfiles.entries[var_s0], srcsuf), NULL));
                            } else {
                                addstr(&execlist, mkstr("-original_filename=", mksuf(srcfiles.entries[var_s0], srcsuf), NULL));
                            }
                            addstr(&execlist, "-include=/usr/include", 0);
                            addstr(&execlist, "-cp=i");
                            if (spFC >= mp_prepass_count) {
                                addlist(&execlist, &pfaflags);
                            } else {
                                addstr(&execlist, "-p=1");
                                addstr(&execlist, "-ur=1");

                                sp100++;
                                if (strncmp(argv[sp100], "-pfaprepass,", 12) != 0) {
                                    do {
                                        sp100++;
                                        if (argv[sp100] == NULL) {
                                            error(1, NULL, 0, NULL, 0, "Can't parse -pfaprepass option\n");
                                            exit(2);
                                        }
                                    } while (strncmp(argv[sp100], "-pfaprepass,", 12) != 0);
                                }

                                spE8 = argv[sp100] + strlen("-pfaprepass");
                                for (;;) {
                                    spEC = spE8 + 1;
                                    if (*spEC == 0) {
                                        error(1, NULL, 0, NULL, 0, "Bad pfaprepass syntax: no arg after comma\n");
                                        exit(2);
                                    }
                                    spE8 = spEC + 1;
                                    while (*spE8 != ',' && *spE8 != '\0') spE8++;
                                    spE7 = spE8[0];
                                    spE8[0] = 0;
                                    addstr(&execlist, mkstr(spEC, NULL));
                                    if (spE7 == 0) break;
                                    spE8[0] = spE7;
                                }
                            }
                            if (run(pfa, execlist.entries, NULL, NULL, NULL) != 0) {
                                runerror += 1;
                                if (((docpp != 0) || (srcsuf == 0x65) || (srcsuf == 0x72)) && (srcsuf != 0x69) && (Kflag == 0)) {
                                    unlink(passin);
                                }
                                if (!(mp_flag & 4)) {
                                    unlink(passout);
                                }
                                break;
                            }
                            if (!(mp_flag & 2)) {
                                unlink(spF8);
                            }
                            if (spFC == 0) {
                                if (((docpp != 0) || (srcsuf == 0x65) || (srcsuf == 0x72) || (srcsuf == 0x46)) && (srcsuf != 0x69) && (Kflag == 0)) {
                                    unlink(passin);
                                }
                            } else if (!(mp_flag & 4)) {
                                unlink(passin);
                            }
                            spFC++;
                            if (mp_prepass_count >= spFC) {
                                passin = passout;
                                goto loop_1587;
                            }
                            passin = passout;
                            if (Hchar != 0x4B) {
                                goto block_1660;
                            }
                            break;
                        }
block_1660:
                        execlist.length = 0;
                        addstr(&execlist, "fcom");
                        if (alignarg != NULL) {
                            addstr(&execlist, alignarg);
                        }
                        if (align_common > 0) {
                            addstr(&execlist, "-align_common");
                        }
                        if (mp_flag & 0x10000) {
                            addstr(&execlist, "-MP");
                        }
                        if (showdirt_flag != 0) {
                            addstr(&execlist, "-showdirt");
                        }
                        if (vflag != 0) {
                            addstr(&execlist, "-v");
                        }
                        addlist(&execlist, &fcomflags);
                        if (nocode == 0) {
                            addstr(&execlist, mkstr("-XS", symtab, NULL));
                        }
                        var_s2 = NULL;
                        if (nocode != 0) {
                            addstr(&execlist, "-nocode");
                            passout = NULL;
                        } else if (Hchar == 0x66) {
                            passout = mksuf(srcfiles.entries[var_s0], 0x42);
                            if (ucodeflag != 0) {
                                addstr(&execlist, "-Xu");
                                var_s2 = mksuf(srcfiles.entries[var_s0], 0x55);
                            }
                        } else if (Kflag != 0) {
                            passout = mksuf(srcfiles.entries[var_s0], 0x42);
                            if (regular_not_writeable(passout) == 1) {
                                error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                exit(2);
                            }
                        } else {
                            passout = tempstr[3];
                        }
                        if (passout != NULL) {
                            addstr(&execlist, "-t");
                            addstr(&execlist, passout);
                        }
                        if ((docpp != 0) && (srcsuf != 0x69) && (srcsuf != 0x6D)) {
                            var_s1 = passin;
                        } else {
                            addstr(&execlist, passin);
                            var_s1 = NULL;
                        }
                        if (run(fcom, execlist.entries, var_s1, var_s2, errout) != 0) {
                            if (editflag != 0) {
                                if (times_edited < edit_cnt_max) {
                                    times_edited += 1;
                                    if (edit_src(editor, srcfiles.entries[var_s0], 3) != 0) {
                                        show_err(errout);
                                        exit(1);
                                    }
                                    if (((docpp != 0) || (srcsuf == 0x65) || (srcsuf == 0x72)) && (srcsuf != 0x69) && (srcsuf != 0x66)) {
                                        unlink(passin);
                                    }
                                    unlink(passout);
                                    unlink(errout);
                                    unlink(symtab);
                                    passin = srcfiles.entries[var_s0];
                                    goto loop_484;
                                }
                                show_err(errout);
                                goto block_1701;
                            }
block_1701:
                            runerror += 1;
                            if (((docpp != 0) || (mp_flag & 1) || (srcsuf == 0x65) || (srcsuf == 0x72)) && (srcsuf != 0x69) && (srcsuf != 0x6D) && (Kflag == 0) && !(mp_flag & 4)) {
                                unlink(passin);
                            }
                            if (Kflag == 0) {
                                unlink(passout);
                                unlink(symtab);
                            }
                            break;
                        }
                        if (editflag != 0) {
                            unlink(errout);
                        }
                        if (nocode != 0) {
                            if (docpp != 0) {
                                unlink(passin);
                            }
                        } else {
                            if (((docpp != 0) || (mp_flag & 1) || (run_sopt != 0) || (srcsuf == 0x65) || (srcsuf == 0x72) || (srcsuf == 0x46)) && (srcsuf != 0x69) && (srcsuf != 0x6D) && (Kflag == 0) && !(mp_flag & 4)) {
                                unlink(passin);
                            }
                            passin = passout;
                            if (Hchar != 0x66) {

block_1729:
                                if ((Oflag != 3) && (Oflag != 4) && (jflag == 0)) {
                                    if (c_inline == 0) {
                                        goto block_1933;
                                    } else {
                                        goto block_1913;
                                    }
                                } else {
                                    execlist.length = 0;
                                    addstr(&execlist, "ujoin");
                                    if (vflag != 0) {
                                        addstr(&execlist, "-v");
                                    }
                                    addlist(&execlist, &ujoinflags);
                                    if ((outfile != NULL) && (jflag != 0) && (srcfiles.length == 1)) {
                                        passout = outfile;
                                    } else {
                                        passout = mksuf(srcfiles.entries[var_s0], 0x75);
                                    }
                                    addstr(&execlist, "-o");
                                    addstr(&execlist, passout);
                                    addstr(&execlist, passin);
                                    addstr(&execlist, symtab);
                                    if (run(ujoin, execlist.entries, NULL, NULL, NULL) != 0) {
                                        runerror += 1; 
                                        if (Kflag == 0) {
                                            if (srcsuf != 0x42) {
                                                unlink(passin);
                                            }
                                            unlink(passout);
                                            if (tmpst != 0) {
                                                unlink(symtab);
                                            }
                                        }
                                        continue;
                                    } else if ((cflag == 0) || (Oflag == 3) || (Oflag == 4)) {
                                        if (Kflag == 0) {
                                            if (srcsuf != 0x42) {
                                                unlink(passin);
                                            }
                                            if (tmpst != 0) {
                                                unlink(symtab);
                                            }
                                        }
                                        passin = passout;
                                        continue;
                                    } else {
                                        goto block_1933;
                                    }
c8d8:
                                    if ((non_shared != 0) && (non_shared_emitted == 0)) {
                                        addstr(&ldflags, "-non_shared");
                                        non_shared_emitted = 1;
                                    }

                                    execlist.length = 0;
                                    addstr(&execlist, "uld");
                                    if ((mips2flag != 0) && (sp148 == 0)) {
                                        if (strcmp("/", comp_target_root) != 0) {
                                            if (non_shared != 0) {
                                                addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "nonshared", NULL));
                                            } else {
                                                addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "", NULL));
                                            }
                                        } else if (non_shared != 0) {
                                            addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "nonshared", NULL));
                                        } else {
                                            addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "", NULL));
                                        }
                                    }
                                    if ((mips1flag != 0) && (sp148 == 0)) {
                                        if (strcmp("/", comp_target_root) != 0) {
                                            if (non_shared != 0) {
                                                addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "nonshared", NULL));
                                            } else {
                                                addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "", NULL));
                                            }
                                        } else if (non_shared != 0) {
                                            addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "nonshared", NULL));
                                        } else {
                                            addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "", NULL));
                                        }
                                    }
                                    if (((fiveflag != 0) || (strcmp("/", comp_target_root) != 0)) && (Lflag == 0) && (strcmp("/", comp_target_root) != 0)) {
                                        if (non_shared != 0) {
                                            addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/nonshared/", currcomp, NULL));
                                        } else {
                                            addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, NULL));
                                        }
                                    }
                                    if (svr4_systype != 0) {
                                        if (compchoice == 1) {
                                            addstr(&execlist, mkstr("-SYSTYPE_SVR4", NULL, NULL));
                                        }
                                        addstr(&execlist, mkstr("-_SYSTYPE_SVR4", NULL, NULL));
                                        if (call_shared != 0) {
                                            addstr(&execlist, "-require_dynamic_link");
                                            addstr(&execlist, "_rld_new_interface");
                                        }
                                    }
                                    if ((allBstring != NULL) && (*allBstring != 0)) {
                                        addstr(&execlist, mkstr("-kB", allBstring, NULL));
                                    }
                                    addlist(&execlist, &uldflags);
                                    addlist(&execlist, &ldflags);
                                    if (irix4 != 0) {
                                        addstr(&execlist, mkstr("-L", NULL));
                                        if (non_shared != 0) {
                                            addstr(&execlist, mkstr("-L", "/usr/irix4/", "usr/lib/nonshared/", NULL));
                                            crtx = mkstr(comp_host_root, "usr/lib/nonshared/", CRTX, NULL);
                                            crtn = mkstr(comp_host_root, "usr/lib/nonshared/", "crtn.o", NULL);
                                        } else {
                                            addstr(&execlist, mkstr("-L", "/usr/irix4/", "usr/lib/", NULL));
                                            crtx = mkstr(comp_host_root, "usr/lib/", CRTX, NULL);
                                            crtn = mkstr(comp_host_root, "usr/lib/", "crtn.o", NULL);
                                        }
                                    }
                                    if (cflag == 0) {
                                        addstr(&execlist, crtx);
                                    } else {
                                        addstr(&execlist, "-no_AutoGnum");
                                        if (force_rm_dead_code == 0) {
                                            addstr(&execlist, "-preserve_dead_code");
                                        }
                                    }
                                    adduldlist(&execlist, &ufiles, &objfiles);
                                    if (cflag == 0) {
                                        addlist(&execlist, &uldlibflags);
                                        if (((compiler == 2) || (haspascal != 0)) && ((addspacedstr(&execlist, newstr(libp)), addspacedstr(&execlist, newstr(libxmalloc)), addspacedstr(&execlist, newstr(libexc)), addspacedstr(&execlist, newstr(libmld)), (default_call_shared != 0)) || (call_shared != 0)) && (systype != NULL) && (strcmp(systype, "svr3") == 0)) {
                                            addspacedstr(&execlist, "-lbsd");
                                        }
                                        if ((compiler == 3) || (hasfortran != 0)) {
                                            if (mp_flag != 0) {
                                                addstr(&execlist, libI77_mp);
                                            }
                                            if ((non_shared != 0) || (irix4 != 0)) {
                                                addspacedstr(&execlist, newstr(libF77));
                                            } else {
                                                addspacedstr(&execlist, libftn);
                                            }
                                            if ((non_shared != 0) || (irix4 != 0)) {
                                                addspacedstr(&execlist, newstr(libI77));
                                            }
                                            if ((non_shared != 0) || (irix4 != 0)) {
                                                addspacedstr(&execlist, newstr(libU77));
                                            }
                                            if ((non_shared != 0) || (irix4 != 0)) {
                                                addspacedstr(&execlist, newstr(libisam));
                                            }
                                        }
                                        if (compiler == 5) {
                                            addstr(&execlist, libpl1);
                                            addstr(&execlist, libxmalloc);
                                            addstr(&execlist, "-ltermcap");
                                            addstr(&execlist, libexc);
                                            addstr(&execlist, libmld);
                                        }
                                        if (((compiler == 2) || (compiler == 3) || (haspascal != 0) || (hasfortran != 0) || (haspl1 != 0) || (compiler == 5) || (compiler == 6)) && (nonshared != 0)) {
                                            addspacedstr(&execlist, newstr(libm));
                                        }
                                        if (pgflag != 0) {
                                            addspacedstr(&execlist, newstr(libgprof));
                                        } else if (pflag != 0) {
                                            addspacedstr(&execlist, newstr(libprof));
                                        }
                                        if (cmp_flag & 0x10000) {
                                            addstr(&execlist, libc_mp);
                                            if (compiler == 1) {
                                                addstr(&execlist, "-lkapio");
                                            }
                                        }
                                        if ((run_sopt != 0) && (compiler == 1)) {
                                            addstr(&execlist, "-lkapio");
                                        }
                                        if (compiler == 3) {
                                            if (D_1000C130 == 2) {
                                                addstr(&execlist, "-lc_s");
                                                if (xpg_flag != 0) {
                                                    addstr(&execlist, "-dont_warn_unused");
                                                    addstr(&execlist, "-lgen");
                                                    addstr(&execlist, "-warn_unused");
                                                }
                                                addstr(&execlist, "-lc");
                                            } else {
                                                if ((irix4 != 0) && (B_1000ED74 == 0)) {
                                                    addstr(&execlist, "-lmpc");
                                                }
                                                if (B_1000ED2C != 0) {
                                                    addstr(&execlist, "-lc_s");
                                                } else if (B_1000ED30 != 0) {
                                                    addstr(&execlist, "-lc_s");
                                                }
                                            }
                                        } else if (B_1000ED2C != 0) {
                                            addstr(&execlist, "-lc_s");
                                        }
                                        if (sixty4bitflag == 0) {
                                            ldw_file = fopen(libdw_path, "r");
                                            if (ldw_file != NULL) {
                                                addspacedstr(&execlist, newstr(libdw));
                                            }
                                        }
                                        if (xpg_flag != 0) {
                                            addstr(&execlist, "-dont_warn_unused");
                                            addstr(&execlist, "-lgen");
                                            addstr(&execlist, "-warn_unused");
                                        }
                                        addstr(&execlist, "-lc");
                                        if (libm_spec != 0) {
                                            addstr(&execlist, "-lm");
                                        }
                                        if (libfastm_spec != 0) {
                                            addstr(&execlist, "-lfastm");
                                        }
                                    }
                                    if ((cflag == 0) && (crtn_required != 0)) {
                                        addstr(&execlist, crtn);
                                    }
                                    if (rls_id_object != NULL) {
                                        addstr(&execlist, rls_id_object);
                                    }
                                    addstr(&execlist, "-ko");
                                    if (uoutfile != NULL) {
                                        passout = uoutfile;
                                    } else if ((Hchar == 0x75) || (Kflag != 0)) {
                                        passout = mksuf(srcfiles.entries[var_s0], 0x75);
                                    } else {
                                        passout = tempstr[4];
                                    }
                                    addstr(&execlist, passout);
                                    if (run(uld, execlist.entries, NULL, NULL, NULL) != 0) {
                                        runerror += 1;
                                        if (Kflag == 0) {
                                            unlink(passout);
                                        }
                                        continue;
                                    }
                                    passin = passout;
                                    if ((ufiles.length == 1) && (srcfiles.length == 2) && ((Oflag == 3) || (Oflag == 4))) {
                                        unlink(*ufiles.entries);
                                    }
                                    if (Hchar == 0x75) {
                                        continue;
                                    }
block_1896:
                                    execlist.length = 0;
                                    addstr(&execlist, "usplit");
                                    if (vflag != 0) {
                                        addstr(&execlist, "-v");
                                    }
                                    addlist(&execlist, &usplitflags);
                                    if ((Hchar == 0x73) || (Kflag != 0)) {
                                        passout = mksuf(srcfiles.entries[var_s0], 0x53);
                                        if (regular_not_writeable(passout) == 1) {
                                            error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                            exit(2);
                                        }
                                    } else {
                                        passout = tempstr[5];
                                    }
                                    addstr(&execlist, "-o");
                                    addstr(&execlist, passout);
                                    addstr(&execlist, "-t");
                                    addstr(&execlist, symtab);
                                    addstr(&execlist, passin);
                                    if (run(usplit, execlist.entries, NULL, NULL, NULL) != 0) {
                                        runerror += 1;
                                        if (Kflag == 0) {
                                            unlink(passin);
                                            unlink(passout);
                                        }
                                        if (tmpst != 0) {
                                            unlink(symtab);
                                        }
                                    } else {
                                        if ((Kflag == 0) && (srcsuf != 0x75) && (uoutfile == NULL)) {
                                            unlink(passin);
                                        }
                                        passin = passout;
                                        if (Hchar != 0x73) {
                                            block_1913:
                                            if ((Oflag == 3) || (Oflag == 4) || (c_inline != 0)) {
                                                execlist.length = 0;
                                                addstr(&execlist, "umerge");
                                                if (vflag != 0) {
                                                    addstr(&execlist, "-v");
                                                }
                                                addlist(&execlist, &umergeflags);
                                                addstr(&execlist, passin);
                                                addstr(&execlist, "-o");
                                                if ((Hchar == 0x6D) || (Kflag != 0)) {
                                                    passout = mksuf(srcfiles.entries[var_s0], 0x4D);
                                                    if (regular_not_writeable(passout) == 1) {
                                                        error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                        exit(2);
                                                    }
                                                } else {
                                                    passout = tempstr[6];
                                                }
                                                addstr(&execlist, passout);
                                                addstr(&execlist, "-t");
                                                addstr(&execlist, symtab);
                                                if (run(umerge, execlist.entries, NULL, NULL, NULL) != 0) {
                                                    runerror += 1;
                                                    if (Kflag == 0) {
                                                        if (srcsuf != 0x53) {
                                                            unlink(passin);
                                                        }
                                                        unlink(passout);
                                                        if (tmpst != 0) {
                                                            unlink(symtab);
                                                        }
                                                    }
                                                } else {
                                                    if ((Kflag == 0) && (srcsuf != 0x53)) {
                                                        unlink(passin);
                                                    }
                                                    passin = passout;
                                                    if (Hchar != 0x6D) {
                                                        // TODO: pointless 'b'
                                                        goto block_1933;
                                                    }
                                                }
                                            } else {
                                                goto block_1933;
                                            }

                                        }
                                    }
                                    break;

                                    // case 0x4D:              /* switch 19 */
block_1933:
                                    if (unrollflag != 0) {
                                        execlist.length = 0;
                                        addstr(&execlist, "uloop");
                                        if (vflag != 0) {
                                            addstr(&execlist, "-v");
                                        }
                                        addlist(&execlist, &uloopflags);
                                        addstr(&execlist, passin);
                                        addstr(&execlist, "-o");
                                        if ((Hchar == 0x76) || (Kflag != 0)) {
                                            if ((Hchar == 0x76) || (Kflag != 0)) {
                                                passout = mksuf(srcfiles.entries[var_s0], 0x56);
                                                if (regular_not_writeable(passout) == 1) {
                                                    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                    exit(2);
                                                }
                                            } else {
                                                passout = tempstr[23];
                                            }
                                        }
                                        addstr(&execlist, passout);
                                        addstr(&execlist, "-t");
                                        addstr(&execlist, symtab);
                                        if (run(uloop, execlist.entries, NULL, NULL, NULL) != 0) {
                                            runerror += 1;
                                            if (Kflag == 0) {
                                                if (srcsuf != 0x4D) {
                                                    unlink(passin);
                                                }
                                                unlink(passout);
                                                if (tmpst != 0) {
                                                    unlink(symtab);
                                                }
                                            }
                                        } else {
                                            if ((Kflag == 0) && (srcsuf != 0x4D)) {
                                                unlink(passin);
                                            }
                                            passin = passout;
                                            if (Hchar != 0x76) {
                                                // TODO: pointless 'b'
                                                goto block_1953;
                                            }
                                        }
                                    } else {
block_1953:
                                        if ((uopt0flag == 1) && (compiler == 3) && (Oflag >= 2)) {
                                            execlist.length = 0;
                                            addstr(&execlist, "uopt0");
                                            if (vflag != 0) {
                                                addstr(&execlist, "-v");
                                            }
                                            addstr(&execlist, "-G");
                                            addstr(&execlist, Gnum);
                                            addlist(&execlist, &uopt0flags);
                                            addstr(&execlist, passin);
                                            if ((Hchar == 0x71) || (Kflag != 0)) {
                                                passout = mksuf(srcfiles.entries[var_s0], 0x51);
                                                if (regular_not_writeable(passout) == 1) {
                                                    error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                    exit(2);
                                                }
                                            } else {
                                                passout = tempstr[28];
                                            }
                                            addstr(&execlist, passout);
                                            addstr(&execlist, "-t");
                                            addstr(&execlist, symtab);
                                            uopt0str = tempstr[29];
                                            addstr(&execlist, uopt0str);
                                            if (run(uopt0, execlist.entries, NULL, NULL, NULL) != 0) {
                                                runerror += 1;
                                                if (Kflag == 0) {
                                                    if ((srcsuf != 0x4D) && (srcsuf != 0x42) && (srcsuf != 0x53) && (srcsuf != 0x51)) {
                                                        unlink(passin);
                                                    }
                                                    unlink(passout);
                                                    if (tmpst != 0) {
                                                        unlink(symtab);
                                                    }
                                                }
                                                unlink(uopt0str);
                                            } else {
                                                if ((Kflag == 0) && (srcsuf != 0x4D) && (srcsuf != 0x42) && (srcsuf != 0x53) && (srcsuf != 0x51)) {
                                                    unlink(passin);
                                                }
                                                unlink(uopt0str);
                                                passin = passout;
                                                if (Hchar != 0x71) {
                                                    goto block_1980;
                                                }
                                            }
                                        } else {
block_1980:
                                            if ((ddoptflag == 1) && (compiler == 3) && (Oflag >= 2)) {
                                                execlist.length = 0;
                                                addstr(&execlist, "ddopt");
                                                if (vflag != 0) {
                                                    addstr(&execlist, "-v");
                                                }
                                                addstr(&execlist, "-G");
                                                addstr(&execlist, Gnum);
                                                addlist(&execlist, &ddoptflags);
                                                addstr(&execlist, passin);
                                                if (((Hchar == 0x64) && (ucodeflag == 0)) || (Kflag != 0)) {
                                                    passout = mksuf(srcfiles.entries[var_s0], 0x44);
                                                    if (regular_not_writeable(passout) == 1) {
                                                        error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                        exit(2);
                                                    }
                                                } else {
                                                    passout = tempstr[27];
                                                }
                                                if (ddoptinfo != 0) {
                                                    addstr(&execlist, "-e");
                                                    if (((Hchar == 0x64) && (ucodeflag == 0)) || (Kflag != 0)) {
                                                        addstr(&execlist, mksuf(srcfiles.entries[var_s0], 0x45));
                                                    } else {
                                                        addstr(&execlist, tempstr[26]);
                                                    }
                                                }
                                                addstr(&execlist, passout);
                                                if (run(ddopt, execlist.entries, NULL, NULL, NULL) != 0) {
                                                    runerror += 1;
                                                    if (Kflag == 0) {
                                                        if ((srcsuf != 0x42) && (srcsuf != 0x53) && (srcsuf != 0x4D) && (srcsuf != 0x51)) {
                                                            unlink(passin);
                                                        }
                                                        unlink(passout);
                                                        if (tmpst != 0) {
                                                            unlink(symtab);
                                                        }
                                                    }
                                                    unlink(ddoptstr);
                                                } else {
                                                    if ((Kflag == 0) && (srcsuf != 0x42) && (srcsuf != 0x53) && (srcsuf != 0x4D) && (srcsuf != 0x51)) {
                                                        unlink(passin);
                                                    }
                                                    unlink(ddoptstr);
                                                    passin = passout;
                                                    if (Hchar != 0x64) {
                                                        goto block_2015;
                                                    }
                                                }
                                            } else {
                                                // case 0x44:  /* switch 19 */
                                                // case 0x51:  /* switch 19 */
                                                // case 0x56:  /* switch 19 */
block_2015:
                                                if ((Oflag == 2) || (Oflag == 3) || (Oflag == 4)) {
                                                    execlist.length = 0;
                                                    addstr(&execlist, "uopt");
                                                    if (vflag != 0) {
                                                        addstr(&execlist, "-v");
                                                    }
                                                    addstr(&execlist, "-G");
                                                    addstr(&execlist, Gnum);
                                                    if ((mp_flag & 0x10000) && ((srcsuf == 0x66) || (srcsuf == 0x46))) {
                                                        addstr(&execlist, "-noPalias");
                                                    }
                                                    if (irix4 == 0) {
                                                        if (kpicopt_flag != 0) {
                                                            addstr(&execlist, "-kpicopt");
                                                        }
                                                        if (nokpicopt_flag != 0) {
                                                            addstr(&execlist, "-nokpicopt");
                                                        }
                                                    }
                                                    addlist(&execlist, &optflags);
                                                    addstr(&execlist, passin);
                                                    if (((Hchar == 0x6F) && (ucodeflag == 0)) || (Kflag != 0)) {
                                                        passout = mksuf(srcfiles.entries[var_s0], 0x4F);
                                                        if (regular_not_writeable(passout) == 1) {
                                                            error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                            exit(2);
                                                        }
                                                        if (NoMoreOptions != 0) {
                                                            *passout = 0x2D;
                                                            if (*passout != 0) {
                                                                passout = func_00433534(passout);
                                                            }
                                                        }
                                                    } else {
                                                        passout = tempstr[7];
                                                    }
                                                    addstr(&execlist, passout);
                                                    addstr(&execlist, "-t");
                                                    addstr(&execlist, symtab);
                                                    optstr = tempstr[8];
                                                    addstr(&execlist, optstr);
                                                    if (run(opt, execlist.entries, NULL, NULL, NULL) != 0) {
                                                        runerror += 1;
                                                        if (Kflag == 0) {
                                                            if ((srcsuf != 0x42) && (srcsuf != 0x53) && (srcsuf != 0x51) && (srcsuf != 0x44) && (srcsuf != 0x4D) && (srcsuf != 0x56)) {
                                                                unlink(passin);
                                                            }
                                                            unlink(passout);
                                                            if (tmpst != 0) {
                                                                unlink(symtab);
                                                            }
                                                        }
                                                        unlink(optstr);
                                                    } else {
                                                        if ((Kflag == 0) && (srcsuf != 0x42) && (srcsuf != 0x53) && (srcsuf != 0x51) && (srcsuf != 0x44) && (srcsuf != 0x4D) && (srcsuf != 0x56)) {
                                                            unlink(passin);
                                                        }
                                                        unlink(optstr);
                                                        passin = passout;
                                                        if ((Hchar == 0x6F) && (ucodeflag != 0)) {
                                                            execlist.length = 0;
                                                            addstr(&execlist, "btou");
                                                            addstr(&execlist, passin);
                                                            passout = mksuf(srcfiles.entries[var_s0], 0x55);
                                                            addstr(&execlist, passout);
                                                            if (run(btou, execlist.entries, NULL, NULL, NULL) != 0) {
                                                                runerror += 1;
                                                                if (Kflag == 0) {
                                                                    unlink(passin);
                                                                    unlink(passout);
                                                                    if (tmpst != 0) {
                                                                        unlink(symtab);
                                                                    }
                                                                }
                                                            } else if (Kflag == 0) {
                                                                unlink(passin);
                                                                if (tmpst != 0) {
                                                                    unlink(symtab);
                                                                }
                                                            }
                                                        } else if (Hchar != 0x6F) {
                                                            // TODO: pointless 'b'
                                                            goto block_2068;
                                                        }
                                                    }
                                                } else {
                                                    // case 0x4F: /* switch 19 */
block_2068:
                                                    execlist.length = 0;
                                                    addstr(&execlist, "ugen");
                                                    if (vflag != 0) {
                                                        addstr(&execlist, "-v");
                                                    }
                                                    addstr(&execlist, "-G");
                                                    addstr(&execlist, Gnum);
                                                    if ((kpic_flag != 0) && (coff_spec == 0) && (irix4 == 0)) {
                                                        if (Oflag >= 3) {
                                                            addstr(&execlist, "-pic1");
                                                        } else {
                                                            addstr(&execlist, "-pic2");
                                                        }
                                                    }
                                                    addlist(&execlist, &genflags);
                                                    addstr(&execlist, passin);
                                                    if (Sflag != 0) {
                                                        addstr(&execlist, "-o");
                                                        if (Kflag != 0) {
                                                            addstr(&execlist, mksuf(srcfiles.entries[var_s0], 0x47));
                                                        } else {
                                                            binasm = tempstr[9];
                                                            addstr(&execlist, binasm);
                                                        }
                                                        addstr(&execlist, "-l");
                                                        passout = mksuf(srcfiles.entries[var_s0], 0x73);
                                                        if (regular_not_writeable(passout) == 1) {
                                                            error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                            exit(2);
                                                        }
                                                        addstr(&execlist, passout);
                                                    } else if (Hchar == 0x63) {
                                                        addstr(&execlist, "-o");
                                                        passout = mksuf(srcfiles.entries[var_s0], 0x47);
                                                        if (regular_not_writeable(passout) == 1) {
                                                            error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                            exit(2);
                                                        }
                                                        addstr(&execlist, passout);
                                                    } else if (Kflag != 0) {
                                                        addstr(&execlist, "-o");
                                                        passout = mksuf(srcfiles.entries[var_s0], 0x47);
                                                        if (regular_not_writeable(passout) == 1) {
                                                            error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                            exit(2);
                                                        }
                                                        addstr(&execlist, passout);
                                                        if (regular_not_writeable(mksuf(srcfiles.entries[var_s0], 0x73)) == 1) {
                                                            error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", mksuf(srcfiles.entries[var_s0], 0x73));
                                                            exit(2);
                                                        }
                                                        addstr(&execlist, "-l");
                                                        addstr(&execlist, mksuf(srcfiles.entries[var_s0], 0x73));
                                                    } else {
                                                        addstr(&execlist, "-o");
                                                        passout = tempstr[10];
                                                        if (regular_not_writeable(passout) == 1) {
                                                            error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                            exit(2);
                                                        }
                                                        addstr(&execlist, passout);
                                                    }
                                                    addstr(&execlist, "-t");
                                                    addstr(&execlist, symtab);
                                                    addstr(&execlist, "-temp");
                                                    gentmp = tempstr[15];
                                                    addstr(&execlist, gentmp);
                                                    if (run(gen, execlist.entries, NULL, NULL, NULL) != 0) {
                                                        runerror += 1;
                                                        if (Kflag == 0) {
                                                            if ((srcsuf != 0x42) && (srcsuf != 0x4F) && (srcsuf != 0x51) && (srcsuf != 0x44) && (srcsuf != 0x4D) && (srcsuf != 0x53) && (srcsuf != 0x56)) {
                                                                unlink(passin);
                                                            }
                                                            unlink(passout);
                                                            if (tmpst != 0) {
                                                                unlink(symtab);
                                                            }
                                                        } else if (Sflag != 0) {
                                                            unlink(binasm);
                                                        }
                                                        unlink(gentmp);
                                                    } else {
                                                        unlink(gentmp);
                                                        if ((((srcsuf != 0x42) && (srcsuf != 0x53) && (srcsuf != 0x51) && (srcsuf != 0x44) && (srcsuf != 0x4D) && (srcsuf != 0x56)) || (Oflag >= 2)) && (srcsuf != 0x4F) && (Kflag == 0)) {
                                                            unlink(passin);
                                                        }
                                                        if (Sflag != 0) {
                                                            if (Kflag == 0) {
                                                                if (tmpst != 0) {
                                                                    unlink(symtab);
                                                                }
                                                                unlink(binasm);
                                                            }
                                                        } else if (Hchar != 0x63) {
                                                            passin = passout;
                                                            // case 0x73: /* switch 18 */
block_2130:
                                                            if (srcsuf == 0x73) {
                                                                execlist.length = 0;
                                                                addstr(&execlist, "as0");
                                                                if (vflag != 0) {
                                                                    addstr(&execlist, "-v");
                                                                }
                                                                addstr(&execlist, "-G");
                                                                addstr(&execlist, Gnum);
                                                                addlist(&execlist, &asflags);
                                                                if ((NoMoreOptions != 0) && (*passin == 0x2D)) {
                                                                    passin = func_00433534(passin);
                                                                }
                                                                addstr(&execlist, passin);
                                                                addstr(&execlist, "-o");
                                                                if ((Hchar == 0x61) || (Kflag != 0)) {
                                                                    if ((compiler == 4) && (getsuf(srcfiles.entries[var_s0]) == 0)) {
                                                                        passout = mkstr(srcfiles.entries[var_s0], ".G", NULL);
                                                                    } else {
                                                                        passout = mksuf(srcfiles.entries[var_s0], 0x47);
                                                                    }
                                                                    if (regular_not_writeable(passout) == 1) {
                                                                        error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                                        exit(2);
                                                                    }
                                                                } else {
                                                                    passout = tempstr[11];
                                                                    if (regular_not_writeable(passout) == 1) {
                                                                        error(1, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                                                                        exit(2);
                                                                    }
                                                                }
                                                                addstr(&execlist, passout);
                                                                addstr(&execlist, "-t");
                                                                addstr(&execlist, symtab);
                                                                if (run(as0, execlist.entries, NULL, NULL, NULL) != 0) {
                                                                    runerror += 1;
                                                                    if ((docpp != 0) || (mflag != 0)) {
                                                                        unlink(passin);
                                                                    }
                                                                    if (Kflag == 0) {
                                                                        unlink(passout);
                                                                        if (tmpst != 0) {
                                                                            unlink(symtab);
                                                                        }
                                                                    }
                                                                } else {
                                                                    if ((docpp != 0) || (mflag != 0)) {
                                                                        unlink(passin);
                                                                    }
                                                                    if (Hchar != 0x61) {
                                                                        passin = passout;
                                                                        goto block_2159;
                                                                    }
                                                                }
                                                            } else {
                                                                // case 0x47: /* switch 19 */
block_2159:
                                                                execlist.length = 0;
                                                                addstr(&execlist, "as1");
                                                                addstr(&execlist, "-t5_ll_sc_bug");
                                                                if (tfp_flag != 0) {
                                                                    addstr(&execlist, "-tfp");
                                                                }
                                                                if (noaliasokflag != 0) {
                                                                    addstr(&execlist, "-noaliasok");
                                                                }
                                                                if (alignarg != NULL) {
                                                                    addstr(&execlist, alignarg);
                                                                }
                                                                if (align_common > 0) {
                                                                    addstr(&execlist, "-align_common");
                                                                }
                                                                if (((compiler == 4) || (srcsuf == 0x73)) && (kpic_spec == 0) && (irix4 == 0)) {
                                                                    addstr(&execlist, "-pic0");
                                                                }
                                                                if (coff_spec != 0) {
                                                                    addstr(&execlist, "-coff");
                                                                    kpic_flag = 0;
                                                                } else if (kpic_flag != 0) {
                                                                    if (irix4 == 0) {
                                                                        if (coff_spec == 0) {
                                                                            addstr(&execlist, "-elf");
                                                                            if (Oflag >= 3) {
                                                                                addstr(&execlist, "-pic1");
                                                                            } else {
                                                                                addstr(&execlist, "-pic2");
                                                                            }
                                                                        } else {
                                                                            addstr(&execlist, "-coff");
                                                                            kpic_flag = 0;
                                                                        }
                                                                    }
                                                                } else if (irix4 == 0) {
                                                                    if (coff_spec != 0) {
                                                                        addstr(&execlist, "-coff");
                                                                    } else {
                                                                        addstr(&execlist, "-elf");
                                                                    }
                                                                }
                                                                if (vflag != 0) {
                                                                    addstr(&execlist, "-v");
                                                                }
                                                                if ((fullasoptflag == 0) && (srcsuf == 0x73) && (Oflag >= 2)) {
                                                                    addstr(&execlist, "-noglobal");
                                                                }
                                                                addstr(&execlist, "-G");
                                                                addstr(&execlist, Gnum);
                                                                switch (pflag) { /* switch 15; irregular */
                                                                case 0: /* switch 15 */
                                                                    addstr(&execlist, "-p0");
                                                                    break;
                                                                case 1: /* switch 15 */
                                                                    addstr(&execlist, "-p1");
                                                                    break;
                                                                }
                                                                addlist(&execlist, &asflags);
                                                                addlist(&execlist, &as1flags);
                                                                if (irix4 == 0) {
                                                                    addlist(&execlist, &olimitflags);
                                                                }
                                                                if ((NoMoreOptions != 0) && (*passin == 0x2D)) {
                                                                    passin = func_00433534(passin);
                                                                }
                                                                addstr(&execlist, passin);
                                                                addstr(&execlist, "-o");
                                                                if (compiler == 4) {
                                                                    if (outfile != NULL) {
                                                                        passout = outfile;
                                                                    } else {
                                                                        passout = "a.out";
                                                                    }
                                                                } else if ((outfile != NULL) && (cflag != 0) && ((Oflag == 3) || (srcfiles.length == 1))) {
                                                                    passout = outfile;
                                                                } else {
                                                                    if ((srcsuf == 0x3F) && (Hchar != 0x62) && (Kflag == 0)) {
                                                                        if (cflag == 0) {
                                                                            tmp_uldobj = passout = tempstr[12];
                                                                        } else if (srcfiles.length == 2) {
                                                                            passout = mksuf(*srcfiles.entries, 0x6F);
                                                                            tmp_uldobj = NULL;
                                                                        } else {
                                                                            passout = mksuf(srcfiles.entries[var_s0], 0x6F);
                                                                            tmp_uldobj = NULL;
                                                                        }
                                                                    } else {
                                                                        passout = mksuf(srcfiles.entries[var_s0], 0x6F);
                                                                    }
                                                                    if (uldobj_place != -1) {
                                                                        set_place(&objfiles, passout, uldobj_place);
                                                                    }
                                                                }
                                                                addstr(&execlist, passout);
                                                                addstr(&execlist, "-t");
                                                                addstr(&execlist, symtab);
                                                                if ((ddoptflag == 1) && (compiler == 3) && (ddoptinfo != 0) && (Oflag >= 2)) {
                                                                    addstr(&execlist, "-e");
                                                                    if (((Hchar == 0x62) && (ucodeflag == 0)) || (Kflag != 0)) {
                                                                        addstr(&execlist, mksuf(srcfiles.entries[var_s0], 0x45));
                                                                    } else {
                                                                        addstr(&execlist, tempstr[26]);
                                                                    }
                                                                }
                                                                if (regular_not_writeable(passout) != 0) {
                                                                    unlink(passout);
                                                                }
                                                                if (run(as1, execlist.entries, NULL, NULL, NULL) != 0) {
                                                                    runerror += 1;
                                                                    if (Kflag == 0) {
                                                                        if (srcsuf != 0x47) {
                                                                            unlink(passin);
                                                                        }
                                                                        spE0 = regular_file(passout);
                                                                        if (spE0 == 1) {
                                                                            unlink(passout);
                                                                        } else if (spE0 != 0) {
                                                                            error(2, NULL, 0, NULL, 0, "%s does not exist or is not stat(2)-able. Not deleted (if it exists) even though as1 failed.\n", passout);
                                                                        } else {
                                                                            error(2, NULL, 0, NULL, 0, "%s is not a regular file, not deleted even though as1 failed.\n", passout);
                                                                        }
                                                                        if (tmpst != 0) {
                                                                            unlink(symtab);
                                                                        }
                                                                    }
                                                                    if (tmp_uldobj != NULL) {
                                                                        unlink(tmp_uldobj);
                                                                    }
                                                                } else {
                                                                    if ((ddoptflag == 1) && (compiler == 3) && (ddoptinfo != 0) && (Oflag >= 2)) {
                                                                        unlink(tempstr[26]);
                                                                    }
                                                                    if ((srcsuf != 0x47) && (Kflag == 0)) {
                                                                        unlink(passin);
                                                                    }
                                                                    if ((tmpst != 0) && (Kflag == 0)) {
                                                                        unlink(symtab);
                                                                    }
                                                                    if ((compiler == 3) && (sp11C != 0) && (srcsuf != 0x66) && (srcsuf != 0x46)) {
                                                                        D_1000BF74 = sp11C;
                                                                        relocate_passes("f", NULL, NULL);
                                                                    }
                                                                    if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (no_prelink == 0)) {
                                                                        update_instantiation_info_file(srcfiles.entries[var_s0], passout);
block_2269:;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                goto block_1042;
            }
        }
	}



	{
block_2272:
		srcsuf = 0;
		if (compiler == 4) {
			if (runerror != 0) {
				exit(1);
			} else {
				exit(0);
			}
		}
		if (NoMoreOptions != 0) {
			for (var_s0 = 0; var_s0 < objfiles.length; var_s0++) {
				if ((*objfiles.entries[var_s0] == 0x2D) && (strchr(objfiles.entries[var_s0], 0x2E) != NULL)) {
					objfiles.entries[var_s0] = func_00433534(objfiles.entries[var_s0]);
				}
			}
		}
		if ((cflag == 0) && (Sflag == 0) && (Eflag == 0) && (Pflag == 0) && (jflag == 0) && (runerror == 0) && (objfiles.length != 0) && (Hchar == 0) && (nocode == 0)) {
			if ((old_non_shared != 0) && (mips2flag != 0) && (kpic_flag == 0)) {
				error(1, NULL, 0, NULL, 0, "can't mix -mips2 with shared for ucode compilers, try using -non_shared\n");
				default_call_shared = 0;
				call_shared = 0;
			}
			if ((old_non_shared != 0) && (mips3flag != 0)) {
				error(1, NULL, 0, NULL, 0, "can't mix ucode 32-bit -mips3 with shared\n");
				default_call_shared = 0;
				call_shared = 0;
				exit(2);
			}
			if ((old_non_shared != 0) && (coff_spec != 0)) {
				error(1, NULL, 0, NULL, 0, "can't mix -coff with shared, try using -non_shared\n");
				default_call_shared = 0;
				call_shared = 0;
				exit(2);
			}
			if ((old_non_shared != 0) && (excpt_flag != 0)) {
				error(1, NULL, 0, NULL, 0, "can't mix -excpt with shared, try using -non_shared\n");
				default_call_shared = 0;
				call_shared = 0;
				exit(2);
			}
			if (((old_non_shared != 0) || (non_shared != 0)) && (make_edison_shlib != 0)) {
				error(1, NULL, 0, NULL, 0, "can't mix -shared with -non_shared\n");
				exit(2);
			}
			if ((cordflag != 0) && (make_edison_shlib != 0)) {
				error(1, NULL, 0, NULL, 0, "can't mix -shared with -cord\n");
				exit(2);
			}
			if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)) && (no_prelink == 0)) {
				execlist.length = 0;
				addstr(&execlist, "edg_prelink");
				addstr(&execlist, "-fSGI");
				addlist(&execlist, &prelinkerflags);
				if ((vflag != 0) || (verbose_prelink != 0)) {
					addstr(&execlist, "-v");
				}
				add_prelinker_objects(&execlist, &objfiles);
				if (xpg_flag != 0) {
					add_prelinker_objects(&execlist, &dashlfiles);
				}
				if (run(prelinker, execlist.entries, NULL, NULL, NULL) != 0) {
					runerror += 1;
				} else {
					goto block_2323;
				}
			} else {
block_2323:
				execlist.length = 0;
				addstr(&execlist, LD);
				if ((kpic_flag != 0) && (irix4 == 0) && (coff_spec == 0)) {
					addstr(&ldflags, "-KPIC");
				}
				if ((non_shared != 0) && (non_shared_emitted == 0)) {
					if ((mips2flag == 0) && (mips3flag == 0)) {
						addstr(&ldflags, "-non_shared");
						non_shared_emitted = 1;
					}
				} else if ((call_shared != 0) || (make_edison_shlib != 0)) {
					if (transitive_link != 0) {
						addstr(&ldflags, "-transitive_link");
					} else if (full_transitive_link != 0) {
						addstr(&ldflags, "-full_transitive_link");
					} else if (no_transitive_link != 0) {
						addstr(&ldflags, "-no_transitive_link");
					}
				}
				if (quickstart_info != 0) {
					addstr(&ldflags, "-quickstart_info");
				}
				if ((elfflag != 0) && (coff_spec == 0)) {
					addstr(&execlist, "-elf");
				}
				if (tfp_flag != 0) {
					addstr(&execlist, "-allow_jump_at_eop");
				}
				if ((compiler == 1) && (c_compiler_choice == 3)) {
					addstr(&execlist, "-delta");
				}
				if (cordflag != 0) {
					addstr(&execlist, "-o");
					passout = tempstr[22];
					addstr(&execlist, passout);
				} else if (outfile != NULL) {
					addstr(&execlist, "-o");
					addstr(&execlist, outfile);
				}
				if (gethostsex() != targetsex) {
					if (targetsex == 0) {
						addstr(&execlist, "-EB");
					} else {
						addstr(&execlist, "-EL");
					}
				}
				if (make_edison_shlib != 0) {
					addstr(&execlist, "-shared");
				}
				if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
					add_cxx_symbol_options();
				}
				if (irix4 != 0) {
					addstr(&execlist, mkstr("-L", NULL));
					if (non_shared != 0) {
						addstr(&execlist, mkstr("-L", "/usr/irix4/", "usr/lib/nonshared/", NULL));
						crtx = mkstr(comp_host_root, "usr/lib/nonshared/", CRTX, NULL);
						crtn = mkstr(comp_host_root, "usr/lib/nonshared/", "crtn.o", NULL);
					} else {
						addstr(&execlist, mkstr("-L", "/usr/irix4/", "usr/lib/", NULL));
						crtx = mkstr(comp_host_root, "usr/lib/", CRTX, NULL);
						crtn = mkstr(comp_host_root, "usr/lib/", "crtn.o", NULL);
					}
				}
				if (svr4_systype != 0) {
					if (compchoice == 1) {
						addstr(&execlist, mkstr("-SYSTYPE_SVR4", NULL, NULL));
					}
					addstr(&execlist, mkstr("-_SYSTYPE_SVR4", NULL, NULL));
					if ((call_shared != 0) || (make_edison_shlib != 0)) {
						addstr(&execlist, "-require_dynamic_link");
						addstr(&execlist, "_rld_new_interface");
						if (ignore_unresolved_flag != 0) {
							addstr(&execlist, "-ignore_unresolved");
						} else if (no_unresolved_flag != 0) {
							addstr(&execlist, "-no_unresolved");
						} else if ((default_svr4 != 0) || (make_edison_shlib != 0)) {
							addstr(&execlist, "-ignore_unresolved");
						} else {
							addstr(&execlist, "-no_unresolved");
						}
					}
				}
				if (fiveflag != 0) {
					addstr(&execlist, mkstr("-L", runlib, NULL));
				}
				if ((allBstring != NULL) && (*allBstring != 0)) {
					addstr(&execlist, mkstr("-B", allBstring, NULL));
				}
				if (cordflag != 0) {
					addstr(&execlist, "-r");
					addstr(&execlist, "-d");
					addstr(&execlist, "-z");
				}
				if (irix4 != 0) {
					addstr(&execlist, "-G");
				} else {
					addstr(&execlist, mkstr("-Wx", ",", "-G", NULL));
				}
				addstr(&execlist, Gnum);
				addlist(&execlist, &ldflags);
				addlist(&execlist, &nldflags);
				if ((mips2flag != 0) && (sp148 == 0)) {
					if (strcmp("/", comp_target_root) != 0) {
						if (non_shared != 0) {
							addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "nonshared", NULL));
						} else {
							addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "", NULL));
						}
					} else if (non_shared != 0) {
						addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "nonshared", NULL));
					} else {
						addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "", NULL));
					}
				}
				if ((mips1flag != 0) && (sp148 == 0)) {
					if (strcmp("/", comp_target_root) != 0) {
						if (non_shared != 0) {
							addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "nonshared", NULL));
						} else if (abi_flag == 0) {
							addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "", NULL));
						}
					} else if (non_shared != 0) {
						addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "nonshared", NULL));
					} else if (abi_flag == 0) {
						addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "", NULL));
					}
				}
				if (strcmp("/", comp_target_root) != 0) {
					if (Lflag == 0) {
						if ((compiler == 1) && (c_compiler_choice == 3)) {
							addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/DCC", currcomp, NULL));
						}
						if (non_shared != 0) {
							addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/nonshared/", currcomp, NULL));
						} else if (abi_flag == 0) {
							addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, NULL));
						}
					}
				} else if ((Lflag == 0) && (compiler == 1) && (c_compiler_choice == 3)) {
					addstr(&execlist, mkstr("-L", runlib, "usr/lib/DCC", currcomp, NULL));
				}
				if (make_edison_shlib != 0) {
					if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
						addstr(&execlist, cxx_init);
					}
					if ((compiler == 1) && (c_compiler_choice == 3)) {
						addstr(&execlist, delta_init);
					}
					addlist(&execlist, &objfiles);
					if (xpg_flag != 0) {
						addlist(&execlist, &dashlfiles);
					}
					if (nodeflib == 0) {
						if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
							spDC = D_1000BF90 == 0 && strcmp(LD, "old_ld") != 0;
							if (spDC != 0) {
								addstr(&execlist, "-dont_warn_unused");
							}
							if (exception_handling != 0) {
								addstr(&execlist, "-lCsup");
							}
							addstr(&execlist, "-lC");
							if (spDC != 0) {
								addstr(&execlist, "-warn_unused");
							}
						}
						if (xpg_flag != 0) {
							addstr(&execlist, "-dont_warn_unused");
							addstr(&execlist, "-lgen");
							addstr(&execlist, "-warn_unused");
						}
						addstr(&execlist, "-lc");
					}
				} else {
					addstr(&execlist, "-nocount");
					addstr(&execlist, crtx);
					if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
						addstr(&execlist, cxx_init);
					}
					if ((compiler == 1) && (c_compiler_choice == 3)) {
						addstr(&execlist, delta_init);
					}
					addstr(&execlist, "-count");
					addlist(&execlist, &objfiles);
					if (xpg_flag != 0) {
						addlist(&execlist, &dashlfiles);
					}
					addlist(&execlist, &ldZflags);
					if ((ansichoice == 0) && (compiler == 1) && (irix4 == 0)) {
						addstr(&execlist, "-cckr");
					}
					addstr(&execlist, "-nocount");
					if (nodeflib == 0) {
						if ((compiler == 2) || (haspascal != 0)) {
							addspacedstr(&execlist, libp);
							addspacedstr(&execlist, libxmalloc);
							addspacedstr(&execlist, libexc);
							addspacedstr(&execlist, libmld);
						}
						if ((compiler == 3) || (hasfortran != 0)) {
							if (mp_flag != 0) {
								addspacedstr(&execlist, libI77_mp);
							}
							if ((non_shared != 0) || (irix4 != 0)) {
								addspacedstr(&execlist, libF77);
								addspacedstr(&execlist, libm);
								addspacedstr(&execlist, libU77);
								if (D_1000C130 != 0) {
									spD8 = strlen(libI77);
									spD4 = malloc(spD8 + 2);
									memcpy(spD4, libI77, spD8);
									spD4[spD8] = 0x5F;
									spD4[spD8+1] = 0x73;
									spD4[spD8+2] = 0;
									libI77 = spD4;
								}
								addspacedstr(&execlist, libI77);
								addspacedstr(&execlist, libisam);
							} else {
								addspacedstr(&execlist, libftn);
								addspacedstr(&execlist, libm);
							}
						}
						if (compiler == 5) {
							addstr(&execlist, libpl1);
							addspacedstr(&execlist, libxmalloc);
							addstr(&execlist, "-ltermcap");
							addspacedstr(&execlist, libexc);
							addspacedstr(&execlist, libmld);
						}
						if ((compiler == 2) || ((hasfortran != 0) && (compiler != 3)) || (haspascal != 0) || (haspl1 != 0) || (compiler == 5) || (compiler == 6)) {
							addspacedstr(&execlist, libm);
						}
						if (pgflag != 0) {
							addspacedstr(&execlist, libgprof);
						} else if (pflag != 0) {
							addspacedstr(&execlist, libprof);
						}
						if (sixty4bitflag == 0) {
							ldw_file = fopen(libdw_path, "r");
							if (ldw_file != NULL) {
								addspacedstr(&execlist, libdw);
							}
						}
						if (cmp_flag & 0x10000) {
							addstr(&execlist, libc_mp);
							if (compiler == 1) {
								addstr(&execlist, "-lkapio");
							}
						}
						if ((run_sopt != 0) && (compiler == 1)) {
							addstr(&execlist, "-lkapio");
						}
						if (compiler == 3) {
							if (D_1000C130 == 2) {
								addstr(&execlist, "-lc_s");
								if (xpg_flag != 0) {
									addstr(&execlist, "-dont_warn_unused");
									addstr(&execlist, "-lgen");
									addstr(&execlist, "-warn_unused");
								}
								addstr(&execlist, "-lc");
							} else {
								if ((irix4 != 0) && (B_1000ED74 == 0)) {
									addstr(&execlist, "-lmpc");
								}
								if (B_1000ED2C != 0) {
									addstr(&execlist, "-lc_s");
								} else if (B_1000ED30 != 0) {
									addstr(&execlist, "-lc_s");
								}
								if (xpg_flag != 0) {
									addstr(&execlist, "-dont_warn_unused");
									addstr(&execlist, "-lgen");
									addstr(&execlist, "-warn_unused");
								}
								addstr(&execlist, "-lc");
							}
						} else {
							if ((irix4 != 0) && (cmp_flag & 0x10000)) {
								addstr(&execlist, "-lmpc");
							}
							if ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
								spD0 = D_1000BF90 == 0 && strcmp(LD, "old_ld") != 0;
								if (spD0 != 0) {
									addstr(&execlist, "-dont_warn_unused");
								}
								if (exception_handling != 0) {
									addstr(&execlist, "-lCsup");
								}
								addstr(&execlist, "-lC");
								if (spD0 != 0) {
									addstr(&execlist, "-warn_unused");
								}
							}
							if (B_1000ED2C != 0) {
								addstr(&execlist, "-lc_s");
							} else if (B_1000ED30 != 0) {
								addstr(&execlist, "-lc_s");
							}
							if (xpg_flag != 0) {
								addstr(&execlist, "-dont_warn_unused");
								addstr(&execlist, "-lgen");
								addstr(&execlist, "-warn_unused");
							}
							addstr(&execlist, "-lc");
						}
					}
					if (crtn_required != 0) {
						addstr(&execlist, crtn);
					}
					if (rls_id_object != NULL) {
						addstr(&execlist, rls_id_object);
					}
				}
				passin = NULL;
				if (run(ld, execlist.entries, NULL, NULL, tempstr[32]) != 0) {
					runerror += 1;
					if (Kflag == 0) {
						if ((strcmp(LD, "old_ld") == 0) || ((compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3)))) {
							if (outfile != NULL) {
								unlink(outfile);
							} else {
								unlink("a.out");
							}
						}
						if (tmp_uldobj != NULL) {
							unlink(tmp_uldobj);
						}
					}
				}
				if (tempstr[32] != NULL) {
					if ((stat(tempstr[32], &sp48) == 0) && (sp48.st_size > 0)) {
						execlist.length = 0;
						addstr(&execlist, "c++filt");
						run(filter, execlist.entries, tempstr[32], NULL, NULL);
					}
					unlink(tempstr[32]);
				}
				if ((runerror == 0) && (compiler == 1) && ((c_compiler_choice == 2) || (c_compiler_choice == 3))) {
					execlist.length = 0;
					addstr(&execlist, patch);
					if (vflag != 0) {
						addstr(&execlist, "-d");
					}
					if (outfile != NULL) {
						addstr(&execlist, outfile);
					} else {
						addstr(&execlist, "a.out");
					}
					if (run(patch, execlist.entries, NULL, NULL, NULL) != 0) {
						runerror += 1;
					}
				}
				if ((runerror == 0) && (do_strip != 0)) {
					execlist.length = 0;
					addstr(&execlist, strip);
					if (outfile != NULL) {
						addstr(&execlist, outfile);
					} else {
						addstr(&execlist, "a.out");
					}
					if (run(strip, execlist.entries, NULL, NULL, NULL) != 0) {
						runerror += 1;
					}
				}
			}
block_2588:
			if ((cordflag != 0) && (runerror == 0)) {
				execlist.length = 0;
				addstr(&execlist, "cord");
				if (vflag != 0) {
					addstr(&execlist, "-v");
				}
				addlist(&execlist, &cordflags);
				if (outfile != NULL) {
					passout = outfile;
				} else {
					passout = "a.out";
				}
				addstr(&execlist, "-o");
				addstr(&execlist, passout);
				addstr(&execlist, tempstr[22]);
				if (feedlist.length != 0) {
					addlist(&execlist, &feedlist);
				} else {
					addstr(&execlist, mkstr(passout, ".fb", NULL));
				}
				if (run(cord, execlist.entries, NULL, NULL, NULL) != 0) {
					runerror += 1;
					unlink(passout);
					unlink(tempstr[22]);
				} else {
					unlink(tempstr[22]);
				}
			}
			if ((runerror == 0) && (srcfiles.length == 1) && (nobjs == 1) && (Kflag == 0)) {
				unlink(mksuf(*srcfiles.entries, 0x6F));
			}
		}
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
	if ((compiler == 1) && (gflag >= 2)) {
		unlink(tempstr[33]);
	}
	if (runerror != 0) {
		exit(1);
	}
	return 0;
}

#endif

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
    pid_t forkPid;
    pid_t sp50;
    s32 temp_t7; // sp4C
    SIG_PF sp48;
    SIG_PF sp44;
    s32 stat_loc;

    forkPid = fork();
    if (forkPid == (pid_t)-1) { // fork failed
        error(1, NULL, 0, NULL, 0, "fork to edit failed\n");
        if (errno < sys_nerr) {
            error(5, NULL, 0, NULL, 0, "%s\n", sys_errlist[errno]);
        }
        return -1;
    }

    if (forkPid == (pid_t)0) { // child process

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
    } else { // this process, forkPid is the pid of the child process

        sp44 = sigset(SIGINT, SIG_IGN);
        sp48 = sigset(SIGTERM, SIG_IGN);
        sp50 = wait(&stat_loc);
        while (sp50 != forkPid) {
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
