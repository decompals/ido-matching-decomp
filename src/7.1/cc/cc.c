/**
 * @file cc.c
 * @brief Compiler driver for IDO 7.1.
 */

#include "signal.h"
#include "wait.h"
#include "sex.h"
#include "sys/times.h"
#include "stdlib.h"
#include "utime.h"
#include "varargs.h"
#include "errno.h"
#include "unistd.h"
#include "ctype.h"
#include "fcntl.h"
#include "sys/file.h"
#include "sys/stat.h"
#include "sys/ioctl.h"
#include "ucontext.h"
#include "sys/procfs.h"
#include "string.h"
#include "malloc.h"

#define GET_ERRNO_STR(errnoValue) sys_errlist[errnoValue]

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef _UINTPTR_T
typedef unsigned long int uintptr_t;
#define _UINTPTR_T
#endif

// ctype.h macro
#define TO_LOWER(x) ((isupper(x)) ? _tolower(x) : (x))
#define TO_UPPER(x) ((islower(x)) ? _toupper(x) : (x))

/* File, -O1 */
typedef struct {
    int capacity;
    int length;
    char** entries;
} list;

#if __STDC_VERSION__ >= 201112L
#include <stdnoreturn.h>
extern noreturn void exit(int);
#endif

void process_config(int argc, char** argv);
void add_info(char* str);
void parse_command(int argc, char** argv);
void get_host_chiptype(void);
// error
void relocate_passes(const char* arg0, const char* arg1, const char* arg2);
void newrunlib(void);
void compose_G0_libs(const char* arg0);
// compose_reg_libs
// mkstr
void mklist(list* arg0);
// addstr
void addspacedstr(list* arg0, char* str);
char* newstr(const char* src);
int save_place(list* arg0);
void set_place(list* arg0, char* str, int place);
void addlist(list* arg0, list* arg1);
void adduldlist(list* arg0, list* arg1, list* arg2);
int nodup(list* arg0, const char* str);
char getsuf(const char* path);
char* mksuf(const char* path, char value);
char* savestr(const char* src, size_t extra_length);
void mktempstr(void);
int run(char* name, char* const argv[], char* input, char* output, char* err_output);
int edit_src(const char* program, const char* srcpath, int lino_mode);
void get_lino(char* arg0, const char* arg1, int arg2);
void show_err(const char* path);
void handler(void);
void cleanup(void);
void whats(void);
void settimes(void);
void dotime(const char* programName);
static char* func_0042FD7C(const char* name, char** dirs);
int isdir(const char* path);
int regular_file(const char* path);
int regular_not_writeable(const char* path);
// basename
// dirname
static const char* func_00430414(char* arg0, int arg1);
int force_use_cfront(int argc, char** argv);
void exec_OCC(int argc, char** argv);
int add_cxx_symbol_options(void);
// init_curr_dir
char* full_path(const char* relative_path);
void add_static_opt(char* opt);
void record_static_fileset(const char* arg0);
int touch(const char* arg0);
void add_prelinker_objects(list* arg0, list* arg1);
// quoted_length
// quote_shell_arg
static void func_00431A3C(int argc, char** argv);
static void func_00431B38(int first, int count);
// func_00431B88
static void func_00431D00(const char* arg0);
static void func_00431DD8(void);
// skip_old_ii_controls
char* make_ii_file_name(const char* arg0);
void update_instantiation_info_file(const char* arg0, const char* arg1);
static int func_00432940(pid_t arg0);
static void func_00432BDC(void);
static void func_00432C94(void);
static void func_00432D3C(const char* arg0, int count);
static char* func_00433534(const char* arg0);

// Functions which cannot use proper prototypes
#if 0
void error(int arg0, const char* arg1, int arg2, const char* arg3, int arg4, const char* arg5, ...);
char* mkstr(const char*, ...);
void addstr(list* arg0, char* str);
#else
void error();  // variadic but not defined as such
char* mkstr(); // old-style varargs
void addstr(); // sometimes called incorrectly
#endif

typedef int UNK_TYPE;

//! @note a pseudoboolean is something that usually looks like a boolean type but is occasionally not treated as one,
//! e.g. if something increments it.

char* LD = "ld";

typedef enum AnsiChoice {
    /* 0 */ ANSICHOICE_KR,
    /* 1 */ ANSICHOICE_ANSI,
    /* 2 */ ANSICHOICE_ANSIPOSIX,
    /* 3 */ ANSICHOICE_XANSI
} AnsiChoice;

int ansichoice = ANSICHOICE_XANSI;

typedef enum CCompilerChoice {
    /* 0 */ C_COMPILER_CHOICE_0, // default, presumably "cc"
    /* 1 */ C_COMPILER_CHOICE_1, // "ncc" (NCC but for C?)
    /* 2 */ C_COMPILER_CHOICE_2, // "CC.eh", (C++ compiler with exception handling)
                                 // "CC", (Ordinary C++ compiler)
                                 // "NCC" (32-bit native C++ compiler, apparently just "CC -32")
    /* 3 */ C_COMPILER_CHOICE_3  // "DCC" (Delta/C++)
} CCompilerChoice;

int c_compiler_choice = C_COMPILER_CHOICE_0;

struct _struct_suffixes_0x8 {
    /* 0x0 */ const char* unk0; // name
    /* 0x4 */ int unk4;         // language?
};                              // size = 0x8

typedef enum Suffix {
    /* 1 */ SUF_1 = 1, // PL/1
    /* 2 */ SUF_2,     // COBOL
    /* 3 */ SUF_3,     // ?
    /* 4 */ SUF_4,     // ?
    /* 5 */ SUF_5,     // ?
    /* 6 */ SUF_6,     // C++
    /* 7 */ SUF_7      // C
} Suffix;

// Special suffixes
struct _struct_suffixes_0x8 suffixes[] = {
    { "pl1", SUF_1 }, { "pli", SUF_1 }, // PL/1?
    { "cob", SUF_2 },                   // COBOL
    { "il", SUF_3 },                    // ?
    { "st", SUF_4 },                    // ?
    { "anl", SUF_5 },                   // ?
    { "c++", SUF_6 }, { "cc", SUF_6 },  { "cxx", SUF_6 }, { "C", SUF_6 },
    { "cpp", SUF_6 }, { "CXX", SUF_6 }, { "CPP", SUF_6 }, // C++
    { ".c", SUF_7 },                                      // C
    { NULL, 0 },
};

char perr_msg[0x100];

char* include = NULL;
char* includeB = NULL;
char* einclude = NULL;
char* eincludeB = NULL;

//! Program paths
char* cpp = NULL; //!< K&R preprocessor
char* ccom = NULL;
char* mpc = NULL;
char* cfe = NULL;  //!< C frontend
char* upas = NULL; //!< Pascal frontend
char* fcom = NULL; //!< FORTRAN frontend
char* upl1 = NULL; //!< PL/I frontend
char* pl1err = NULL;
char* ulpi = NULL;
char* ucob = NULL;
char* ujoin = NULL;
char* usplit = NULL;
char* uld = NULL; //!< ucode loader
char* umerge = NULL;
char* uloop = NULL;
char* uopt0 = NULL;
char* ddopt = NULL;
char* opt = NULL; //!< optimiser, `uopt`
char* gen = NULL; //!< code generator, `ugen`
char* as0 = NULL; //!< Assembler for handwritten ".s" files
char* as1 = NULL; //!< Assembler used for generated ".s" files
char* ld = NULL;  //!< linker
char* ftoc = NULL;
char* cord = NULL;
char* btou = NULL;
char* utob = NULL;
char* strip = NULL;
char* patch = NULL;
char* filter = NULL;
char* prelinker = NULL;

int smart_build = FALSE; //!< flag, boolean. Set by "-smart". Passed on to `cfe` as "-YR".
char* sbrepos = NULL;    //!< argument of "-YR". @see smart_build

int do_strip = FALSE;   //!< flag, boolean. For C++ compilers, whether to run strip (for C passed on to `ld` as "-s"
                        //!< instead). Set by "-s".
int no_prelink = FALSE; //! flag, boolean. For C++ compilers, whether to not run the prelinker, `edg_prelink` (used for
                        //! ".ii" files containing template instantiation information). Set by "-no_prelink". @see
                        //! force_prelink, default_template_instantiation_mode
int nofilt = FALSE; //!< flag, boolean. For C++ compilers, whether to not run the filter, `c++filt`. Set by "-nofilt".
int force_prelink =
    FALSE; //!< flag, boolean. Whether to force prelinking, also requires nonzero default_template_instantiation_mode.
           //!< Set by "-prelink". @see no_prelink, default_template_instantiation_mode
int default_template_instantiation_mode;
int verbose_prelink = FALSE;      //!< flag, pseudoboolean. For C++ compilers, whether to pass "-v" to prelinker. Set by
                                  //!< "-ptv". Passed on to prelinker as "-v". @see vflag
int auto_template_include = TRUE; //!< flag, boolean. For C++ compilers. Set by "-auto_include" and unset by
                                  //!< "-no_auto_include", last takes priority. Passed on to `cfe` as "-B" when not set.
int nocode = FALSE; //!< flag, boolean. Whether to *not* create object files (used for e.g. static analysis). Set by
                    //!< "-nocode". Passed to `cfe` as "-n", `fcom` as "-nocode". @see cflag
int nocompileneeded = FALSE; //!< boolean. Whether to continue compilation after preprocessing. Set by return of `cfe`
                             //!< being 0xFA if smart_build is enabled.

UNK_TYPE efl; // Unused
char* ratfor; //!< Always set to "/usr/bin/ratfor" in main()
char* m4;     //!< Always set to "/usr/bin/m4" in main()
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

char* xpg_env = NULL; //!< value of `_XPG` environment variable
int xpg_flag = FALSE; //!< boolean. Whether `_XPG` environment variable has been specified.
int crtn_required =
    TRUE; //!< flag, boolean. On by default, unset by "-crt0", set by "-crt1", ANSICHOICE_ANSI and ANSICHOICE_ANSIPOSIX
char* CRTX;
char* MCRTX;
list undefineflags;
list cppflags;
list olimitflags;
list acppflags;
list mpcflags;
list accomflags;
list cfeflags;
list cpp2flags;
list uldlibflags;
list edisonflags;
list prelinkerflags;
list ccomflags;
list upasflags;
list fcomflags;
list eflflags;
list ratforflags;
list upl1flags;
list ucobflags;
list ulpiflags;
list ujoinflags;
list uldflags;
list usplitflags;
list umergeflags;
list uloopflags;
list uopt0flags;
list ddoptflags;
list optflags;
list genflags;
list asflags;
list as1flags;
list ldflags;
list nldflags;
list ftocflags;
list cordflags;
list srcfiles;
list ufiles;
list objfiles;
list feedlist;
list execlist;
list dashlfiles;

static int B_1000ED2C; // number of times -lgl_s is passed
static int B_1000ED30; // number of times -lc_s is passed

list dirs_for_crtn;
list dirs_for_nonshared_crtn;
list dirs_for_abi_crtn;
list ldZflags;

static int B_1000ED74; // -no_mpc

list pfaflags;
char* pfa;
char* libI77_mp;
list pcaflags;
char* pca = NULL;
char* libc_mp = NULL;
list soptflags;
char* fopt = NULL;
char* copt = NULL;
list staticopts;

static int D_1000BF74 = FALSE;  //!< flag, boolean. Whether to perform static analysis. Set by "-sa".
static int D_1000BF78 = FALSE;  //!< flag, boolean. Static analysis, no source. Set by "-sa,nosrc".
static int D_1000BF7C = TRUE;   //!< boolean. Related to exception handling, used in force_use_cfront().
static char* D_1000BF80 = NULL; //!< Static analysis directory
static char* D_1000BF84 = NULL; //!< Static fileset
static int D_1000BF88 =
    FALSE; //!< flag, pseudoboolean. Disables adding to `staticopt` with add_static_opt(). Set by "-sa_fs"

static int D_1000BF8C = TRUE; //!< flag, boolean. For C++ compilers, whether to use "usr/lib/DCC/" paths for `uopt`,
                              //!< `ugen`, `as1`. Set by enabling environment variable "DCC_STD_PATHS"
static int D_1000BF90 =
    FALSE; //!< boolean. Related to unused warnings. Set by using "DCC" compiler, unset by `D_1000BF8C` off, "-old_ld".
static int D_1000BF94 = FALSE; //!< boolean. Disables use of "-new_ld" or "-old_ld". Never set.

int Eflag = FALSE; //!< flag, pseudoboolean. Only preprocess, do not run subsequent passes, output to stdout. Set by
                   //!< "-E", "-H", "-M".
int Pflag = FALSE; //!< flag, pseudoboolean. Only preprocess, do not run subsequent passes, output to file with
                   //!< extension replaced by ".i". Set by "-P".

int gflag = 0; //!< Option. Debugging level, 0 by default. Set by "-gN", N one of 0,1,2,3, or "-g". Interacts with
               //!< `Oflag`, see parse_command() for details.

int pflag = 0;  //!< Option. Enabled profiling level. Set to 1 by "-p" or "-pg".
int pgflag = 0; //!< Option. Related to profiling. Set to 1 by "-pg".

int jflag = FALSE; //!< flag, pseudoboolean. Only process to ucode, do not run subsequent passes, output to file with
                   //!< extension replaced by ".u". Set by "-j".
int cflag = FALSE; //!< flag, pseudoboolean. Compile a single file to a ".o", do not link. Set by "-c", "-nocode", "+I",
                   //!< and "-F" for C++ compilers.
int Sflag = FALSE; //! flag, pseudoboolean. only compile to assembly, do not assemble, output to file with extension
                   //! replaced by ".s". Set by "-S".

int Oflag = 1; //! Option. Optimisation level, 1 by default. Set by "-ON", N one of 0,1,2,3, or "-O". Interacts with
               //! `gflag`, see parse_command() for details.

int vflag = FALSE; //! flag, boolean. Whether to print verbose output of compilation steps including program arguments.
                   //! Set by "-show", "-v", "-Wxv", "-Zq", "+v" Passed to other programs. "-v" also sets `time_flag`
                   //! @see time_flag
int time_flag =
    FALSE; //! flag, boolean. Whether to print execution times for called programs. Set by "-showt" and "-v".
int execute_flag =
    TRUE; //! flag, boolean. Whether to execute the programs called. Unset by "-show0" and "-show_defaults".

int Vflag = FALSE;    //! flag, boolean. Should print version information, but is disabled, see 'V' in parse_command().
int Kflag = FALSE;    //! flag, pseudoboolean. Whether to keep intermediate files from compilation. These have the same
                      //! filename but change the extension based on pass. Set by "-K" and "-keep".
                      //! TODO: document extensions
int nodeflib = FALSE; //! flag, boolean. Do not use libraries? Set by "-nodeflib"
int minus_M = FALSE;  //! flag, pseudoboolean. Whether to use preprocessor to generate dependencies for `make`, write to
                      //! stdout, do not run subsequent passes. Set by "-M".
int anachronisms = TRUE; //!< flag, boolean. Adds "-O" to `execlist`
int disable_inlines =
    FALSE; //!< flag, boolean. Whether to disable inlining? Set by "+d". Passed to preprocessor as "-YJ"
int cfront_compatible =
    TRUE; //! flag, boolean. Set by "-cfront", unset by "+pp", "+pc", and using "CC.eh". Passed to preprocessor as "-b"
int make_edison_shlib = FALSE; //!< flag, pseudoboolean. Set by "-shared"
int plusIflag = FALSE;         //! flag, boolean. Changes suffix for output of preprocessor? Set by "+I".
int signedcharflag = FALSE;  //!< flag, boolean. Use signed chars, only effective on non-default C_COMPILER_CHOICEs. Set
                             //!< by "-signed" passed on to `cfe` as "-s".
int Lflag = FALSE;           //! flag, boolean. Whether a library directory has been specified. Set by "-L[dir]".
int set_loop_unroll = FALSE; //! flag, boolean. Set by "-Wo,loopunroll".
int mflag = FALSE;           //! flag, pseudoboolean.  Set by "-m"
int Fflag = FALSE;           //! flag, pseudoboolean. Set by "-F" and "+I"
int stdflag = 0;             //! flag. Set to 0 by "-std0" and 1 by "-std" and "-std1".
int cplusflag = FALSE;       //! flag, boolean. Set by "-cplus". Unused
int ucodeflag = FALSE;       //! flag, boolean. Never set.
int Bflag = FALSE;           //! boolean. Set by any "-B" flag apart from "static", "dynamic", and "symbolic"
int fiveflag = FALSE;        //!< flag, pseudoboolean. Set by passing "-5".
int automaticflag = TRUE;    //! flag, boolean. For FORTRAN. Set by "-automatic", unset by "-static". Passes appropriate
                             //! option on to `fcom`.
int emptyIflag = FALSE;      //! flag, pseudoboolean. Set by "-I" on its own, and "-nostdinc".
int cordflag = FALSE;        //! flag, boolean. Whether to run `cord`. Set by "-cord".
int ansiflag = FALSE;        //! flag, boolean. Set by "-ansi" when using the COBOL compiler. Unused.
int lpilockflag = FALSE;     //! flag, boolean. Not set by anything. Cannot be used with `nolockflag`.
int nolockflag = FALSE;      //! flag, boolean. Set by "-nolock". Cannot be used with `lpilockflag`.
int unrollflag = FALSE;      //! flag, boolean. Whether to run `uloop` pass. Not set by anything.
int libm_spec = 0;           //! flag, boolean. Add "-lm" to `uld. Not set.
int libfastm_spec = 0;       //! flag, boolean. Add "-lfastm" to `uld. Not set.

typedef enum EditFlag {
    /* 0 */ EDIT_FLAG_0, //!< E
    /* 1 */ EDIT_FLAG_1, //!< "-edit[0-9]"
    /* 2 */ EDIT_FLAG_2  //!< "-edit[0-9]" and environment variable for EDITOR contains "emacs"
} EditFlag;

int editflag = EDIT_FLAG_0; //!< Option. Set by "-edit[0-9]".

int oldccomflag = FALSE; //!< flag, boolean. Purpose unclear, sets @see oldcflag. Never set to `TRUE`.
int oldcflag = FALSE;    //!< flag, boolean. Purpose unclear, related to preprocessing. Never set to `TRUE`.
int oldcppflag = FALSE;  //!< flag, boolean. Use a different preprocessor from the one built in to `cfe`, `acpp` in ANSI
                         //!< modes and `cpp` in ANSICHOICE_KR. (`cfe` is run with "-nocpp" passed.). Set by "-oldcpp".
int fflag = 0;           // Unused
int tpflag = FALSE;      //!< flag, boolean. Never set. Related to "-oldcpp".
int ddoptflag =
    FALSE; //!< flag, boolean. Whether to run `ddopt`. Set by "-ddopt". Passed on to `as1` as "-e [source file]".
int uopt0flag = FALSE;      //!< flag, boolean. Whether to run `uopt0`. Unset by "-nouopt0", never set.
int protoflag = FALSE;      // Unused
int kminabiflag = FALSE;    //!< flag, boolean. Set by "-Kminabi". Not checked.
int kpicopt_flag = FALSE;   //!< flag, boolean. Set by "-kpicopt". Passed on to `uopt` as "-kpicopt".
int nokpicopt_flag = FALSE; //!< flag, boolean. Set by "-nokpicopt". Passed on to `uopt` as "-nokpicopt".
int elfflag = TRUE; //!< flag, boolean. Whether to assemble/link an ELF. On by default, off for irix4, and set by
                    //!< "-elf" or "-systype svr4". @see elf_spec.
int coff_spec =
    FALSE; //!< flag, boolean. Whether "-coff" has been passed explicitly. Passed on to other programs as "-coff"
int elf_spec = FALSE;         //!< boolean. Whether "-elf" has been passed explicitly. Never checked. @see elfflag.
int compose_first_G0 = FALSE; //!< flag, boolean. Never set except in a dead block.

//! Flags relating to the specified MIPS ISA
int mips2_spec_flag =
    FALSE; //!< flag, boolean. Whether "-mips2" has been passed explicitly (and not overridden). Set by "-mips2".
//! Only one of the following can be set at once.
int mips1flag = FALSE; //!< flag, boolean. Set by "-mips1".
int mips2flag = TRUE;  //!< flag, boolean. Set by "-mips2". @see mips2_spec_flag
int mips3flag = FALSE; //!< flag, boolean. Set by "-mips3" and in several other places.

//! Flags associated to resolving symbols. `ignore_unresolved_flag` takes precedence.
int ignore_unresolved_flag =
    FALSE; //!< flag, boolean. Set by passing "-ignore_unresolved". Passed on to `ld` as "-ignore_unresolved"
int no_unresolved_flag =
    FALSE; //!< flag, boolean. Set by passing "-no_unresolved". Passed on to `ld` as "-no_unresolved"

int swopcodeflag =
    FALSE; //!< flag, boolean. Set by passing "-swopcode". Errors if used with 64-bit, otherwise no effect.
int dwopcodeflag = FALSE; //!< flag, boolean. Set by passing "-mips3". Passed on to other programs as "-dwopcode".
                          //!< Cannot be used with "-mips1" or "-mips2"

int sixty4bit_spec = FALSE;     //!< boolean. Set by passing "-64bit". Unused.
int sixty4bitflag = FALSE;      //!< flag, boolean. Always 0
int thirty2bitflag = FALSE;     //!< flag, boolean
int fullasoptflag = FALSE;      //!< flag, boolean. Whether full assembler optimisation is enabled. Set by "-fullasopt".
                                //!< Passed on as "-noglobal" when not set
int old_non_shared = FALSE;     //!< flag, boolean. Set in (most of) the same places as `non_shared`.
int non_shared_emitted = FALSE; //!< flag, boolean. Whether non_shared code will be emitted in this pass?
int longlong_emitted = FALSE;   //!< boolean. Set when passing on "-D_LONGLONG"
int non_shared = FALSE; //!< flag, boolean. Produce a static executable (non-PIC, incompatible with -KPIC, -shared,
                        //!< etc.) Set by "-non_shared".
int Gseen_flag =
    FALSE; //!< boolean. Whether a "-G" argument has been parsed yet, triggers a relocate_passes() call if not.

//! Flags associated to transitive linking. Only one may be `TRUE` at a time: the last will take precedence.
int transitive_link = FALSE; //!< flag, boolean. Set by "-transitive_link". Passed on to `ld` as "-transitive_link"
int full_transitive_link =
    FALSE; //!< flag, boolean. Set by "-full_transitive_link". Passed on to `ld` as "-full_transitive_link"
int no_transitive_link =
    FALSE; //!< flag, boolean. Set by "-no_transitive_link". Passed on to `ld` as "-no_transitive_link"

int quickstart_info = FALSE;    //!< flag, boolean. Set by "-quickstart_info". Passed on to `ld` as "-quickstart_info".
int force_rm_dead_code = FALSE; //!< flag, boolean. Whether `uld` should remove dead code? Set by "-rm_dead_code",
                                //!< passed on as "-preserve_dead_code" if not set.
int kpic_flag = TRUE;    //!< flag, boolean. Whether to emit Position-Independent Code. On by default, set by "-KPIC",
                         //!< unset by IRIX4 and "-non_shared"
int kpic_spec = FALSE;   //!< flag, boolean. Whether "-KPIC" has been passed explicitly?
int call_shared = FALSE; //!< flag, boolean. Allows created object to call shared library code. Set by "-call_shared".
int excpt_flag = FALSE; //!< flag, boolean. Set by "-excpt". Purpose unclear, not passed on, not useable with "-shared".
int trapuv_flag =
    FALSE; //!< flag, boolean. Whether to compile with trapping for uninitialised variables. Set by "-trapuv".
int dmips_emit = 0;
int Xvalues_Flag = 0;     // Unused
int user_systype = FALSE; //!< boolean. Whether user has specified a `-systype` argument.
int ddoptinfo = FALSE;    //!< flag, boolean. Set by "-ddoptinfo". Passed on to `ddopt` as "-e", inter alia.
int systype_seen = FALSE; //!< boolean. Whether a "-systype" argument has been parsed yet, used to confirm that it
                          //!< precedes any "-B" arguments.
int multiple_systype =
    FALSE;                //!< boolean. Disables some systype checking. Set by passing multiple "-systype" arguments.
int systype_warn = FALSE; //!< flag, boolean. Warned about unrecongized argument to "-systype".
int svr4_systype = FALSE; //!< flag, boolean. Set by main() as default, unset by IRIX4, set by "-systype svr4"
int c_inline = FALSE; //!< flag, boolean. Whether to run `umerge`. Set by `cfe`/`fcom` returning `0xFF`. Passes on to
                      //!< `umerge` as "-c_inline".
int tfp_flag = FALSE; //!< flag, boolean. Set by "-tfp"
int abi_flag = 0;
int NoMoreOptions = FALSE;      //!< flag, pseudoboolean
int memory_flag = 0;            // Probably meant to be boolean, but is checked for being larger than 1 in func_00432D3C
int default_call_shared = TRUE; //!< flag, boolean. Default to "-call_shared"?

static int B_1000E4C0;    //!< argc
static char** B_1000E4C4; //!< argv

int plain_g;               //!< flag, boolean. Indicates that "-g" was passed (= "-O1 -g2")
int plain_O;               //!< flag, boolean. Indicates that "-O" was passed (= "-O1")
int noaliasokflag;         //!< flag, boolean. "-noaliasok"
int haspascal = FALSE;     //!< flag, boolean. If file is Pascal, set by file extension ".p"
int hasfortran = FALSE;    //!< flag, boolean. If file is FORTRAN, set by file extension ".f" or ".m" (at least)
int haspl1;                //?< flag, boolean. Argument has a suffix corresponding to a PL/I program
                           //!< TODO: confirm
int lmflag = FALSE;        //!< flag, pseudoboolean, set and not used
int srcexists = 0;         // Number of source code files present? Set in the main loop of parse_command()
int w1flag = 1;            //!< flag, values 0,1,2 used
static int D_1000C130 = 0; // 0, 1 (-share_io) or 2 (-share_all)
UNK_TYPE p2cstr;           // Unused
int align;                 //!< alignment, set using "-align8", "-align16", "-align32" or "-align64". Set but not used.
int align_common; //!< flag, pseudoboolean. Set by "-align-common" and other alignment flags under certain conditions
                  //!< TODO: which conditions?
char* alignarg;   //!< alignment argument passed on to `execlist`.
int use_real_fp;  //!< Never set, but checked.
int dollar_sign;  //!< flag, pseudoboolean, set by "-dollar"
int prototype_checking_on = FALSE; //!< flag, boolean. Set on by "-prototypes" and off by "-noprototypes"
int mp_flag;                       //!< Set of flags, 1, 2, 4, and 0x10000 are used
int mp_onetripflag;                //!< Set by "-onetrip"
UNK_TYPE mp_staticflag;            // Unused
int mp_dlinesflag;                 //!< flag, boolean. Set by "-d_lines"
int mp_caseflag;                   //!< flag, boolean. Set by "-U"
int mp_66flag;                     //!< flag, boolean. Set by "-6"
int mp_i2flag;                     //!< flag, boolean. Set by "-i2" or "-i8"
int mp_col120flag;                 //!< flag, boolean. Set by "-col120"
int mp_extendflag;                 //!< flag, boolean. Set by "-extend_source"
int mp_uflag;                      //!< flag, boolean. Set by "-u"
int mp_backslashflag;              //!< flag, boolean. Set by "-backslash"
int showdirt_flag = FALSE;         //!< flag, boolean. Set by "-mp_keep"
UNK_TYPE mp_uniq_specified;        // Unused
UNK_TYPE mp_passes_relocated;      // Unused
int mp_prepass_count = 0;

// not sure about this struct
typedef struct {
    const char* unk_0;
    unsigned int unk_4;
} struct_mpflags;

struct_mpflags mpflags[] = {
    { "list", 0x10003 },
    { "keep", 0x10007 },
    { NULL, 0 },
};
int cmp_flag; //!< Set of flags, 1, 2, 4, 0x10000 used
struct_mpflags cmpflags[] = {
    { "list", 0x10003 },
    { "keep", 0x10007 },
    { NULL, 0 },
};
int fullwarn; //!< flag, boolean. Set by "-fullwarn"

int acpp = FALSE; //! flag, boolean. Set by "-acpp"

// Ought to be related to the _MIPS_SIM defines, but is not
typedef enum MipsAbi {
    /* 0 */ MIPS_ABI_0, // ?. Set by IRIX4 flags and environment variable
    /* 1 */ MIPS_ABI_1, // O32. Default, also set by "-32bit", "-32", "-o32"
    /* 2 */ MIPS_ABI_2  // N64, not set
} MipsAbi;

int mips_abi = MIPS_ABI_1;

typedef enum CompChoice {
    /* 0 */ COMP_CHOICE_0,
    /* 1 */ COMP_CHOICE_1,
    /* 2 */ COMP_CHOICE_2,
    /* 3 */ COMP_CHOICE_3,
    /* 4 */ COMP_CHOICE_4
} CompChoice;

int compchoice = COMP_CHOICE_0; //!< ?. Uses `CompChoice` enum.

typedef enum CppChoice {
    /* 0 */ CPP_CHOICE_0,
    /* 1 */ CPP_CHOICE_1,
    /* 2 */ CPP_CHOICE_2, // ANSICHOICE_KR
    /* 3 */ CPP_CHOICE_3  // Other ANSICHOICE_
} CppChoice;

int cppchoice = CPP_CHOICE_0; //!< Preprocessor selection? Uses `CppChoice` enum. CPP_CHOICE_1 and CPP_CHOICE_3 use
                              //!< `acpp`, rest use `cpp`?

int acpp_traditional = FALSE; //!< flag, pseudoboolean. (Could be increased by being passed several times)
char* aligndir;               //!< Set to comp_host_root + "lib/align" and not used
int G_flag = FALSE;           //!< flag, boolean. Whether "-G" has been passed
int dn_flag = FALSE;          //!< flag, boolean. Enable static linking over the default dynamic linking. Set by "-dn"
int docpp;                    //!< flag, boolean. Whether to use the preprocessor?
int default_nocpp;            //!< flag, boolean
unsigned int j;               // Looks like a normal index variable, but is global bss for some reason
int edison_cpp = 1;           //!< set and not used

typedef enum EdisonType {
    /* 1 */ EDISON_TYPE_1 = 1,
    /* 2 */ EDISON_TYPE_2,
    /* 3 */ EDISON_TYPE_3
} EdisonType;

int edison_type = EDISON_TYPE_1; //!< Uses `EdisonType` enum. Set based on `ansichoice`.

int exception_handling = FALSE; //!< flag, boolean. Whether to use exception handling in C++.
char* Gnum = "0";               //!< argument to pass with "-G"
char* tstring;                  //!< Used as the first argument of relocate_passes()
char* hstring;                  //!< Used as the second argument of relocate_passes()
char* Bstring;                  //!< Used as the third argument of relocate_passes()
const char* allBstring;         //!< Sometimes set in relocate_passes()
char alltstring[20];            //!< Used in relocate_passes()
char* Warg;
char* Wpass;
char* Kpass;  // Start of current "-K" argument
char Karg[6]; // Current "-K" argument
char Hchar;
int runerror = 0; //!< number of errors triggered
int retcode;
int uload = FALSE;     //!< flag, boolean. Whether to run `uld` after compiling all files. Set by -O>=3
int uldobj_place = -1; //!< Index into the `objfiles` list where the output of `uld` is?
char* tmp_uldobj = NULL;
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
char* lpi_pd;
char* linkorder;
UNK_TYPE valuesstr;
UNK_TYPE tmp_elfobj;
FILE* ldw_file;
FILE* tmpsfile;

char* editor;
char* xserver;
int times_edited;
int edit_cnt_max;

typedef enum ChipTarget {
    /* -1 */ CHIP_TARGET_UNSET = -1,
    /*  0 */ CHIP_TARGET_MIPS1,
    /*  1 */ CHIP_TARGET_MIPS2,
    /*  2 */ CHIP_TARGET_MIPS3
} ChipTarget;

int chip_targ = CHIP_TARGET_UNSET; //!< "Chip target", uses `ChipTarget` enum.
char srcsuf;
int tmpst;

int nobjs = 0;             //!< Number of output objects?
int targetsex = BIGENDIAN; //!< Endianness, constants from sex.h (yes really).
char* comp_target_root;
char* comp_host_root;
char* systype;
int nonshared;
int default_svr4 = FALSE; //!< flag, boolean. Set by environment variable "SGI_SVR4"
int irix4 = FALSE; //!< flag, boolean. Whether to use irix4 libraries etc. Set by `-irix4` or environment variable
                   //!< "SGI_IRIX4"
char* runlib = "/";
char* runlib_base = "/";
char* tmpdir;
char* rls_id_object;
char* progname; //!< Path of this executable, used to determine `compiler`
char* currcomp;
char* compdirs[7]; // might also be a struct?

typedef enum Compiler {
    /* 1 */ COMPILER_1 = 1, // C
    /* 2 */ COMPILER_2,     // Pascal
    /* 3 */ COMPILER_3,     // FORTRAN
    /* 4 */ COMPILER_4,     // Assembler
    /* 5 */ COMPILER_5,     // PL1
    /* 6 */ COMPILER_6      // COBOL
} Compiler;

int compiler;

char* tempstr[34]; // Possibly a struct?

static prmap_sgi_t B_1000CAC0[100];
static prmap_sgi_arg_t D_1000C1C8 = { (caddr_t)B_1000CAC0, sizeof(B_1000CAC0) };

static char* D_1000C1D0 = NULL; // full path of current working directory
int run_sopt = FALSE;           //!< flag, boolean. Whether to run the scalar optimiser `copt`. Enabled by "-sopt"

static int B_1000EC98[2]; // pipe

// (these feel like in-function statics but I can't get that to match wrt bss reordering)
static char* D_1000C1D8 = NULL; // progname
static char* D_1000C1DC = NULL; // progname space padding

static char* B_1000ECCC; // outfile
static char* B_1000ECDC; // cmdline

typedef enum ErrorCategory {
    /* 0 */ ERRORCAT_INTERNAL, // Unused
    /* 1 */ ERRORCAT_ERROR,
    /* 2 */ ERRORCAT_WARNING,
    /* 3 */ ERRORCAT_INFO, // Unsued
    /* 4 */ ERRORCAT_FIX,  // Unused
    /* 5 */ ERRORCAT_ERRNO // Used for printing `GET_ERRNO_STR(errno)`
} ErrorCategory;

// function main # 2
/**
 * Main fuction for `cc`. Structure is roughly
 * 1. Argument parsing
 *   a. Environment variable parsing. The `compiler` (overall set of programs to run for compilation) is determined from
 * the name of the executable (for example `cc` for the default C compiler, `pc` for Pascal).
 *   b. Initial pass through options, presumably to pick up the most important ones.
 *   c. Preliminary uses of relocate_passes().
 *   d. process_config() and parse_command() to parse and store all remaining options.
 *   e. End of initial option parsing, including setting endianness, propagating debugging and optimisation arguments,
 * etc.
 *   .
 * 2. Main loop for parsing files: looks through all the input file arguments one by one, follows a complex graph of
 * options depending on the type of file present and various options. The file type is determined by its suffix, both
 * for input/output and internally between the various stages. Most of this loop is composed of blocks that
 *   a. Check flags, both for whether to carry out the compilation step in the first place, and what options to add for
 * that program.
 *   b. actually run the external program for that pass using run().
 *   c. based on the output, either clean up and error out, or clean up and continue to the next stage, or the next loop
 * iteration.
 *   .
 *   Assuming success, files will emerge from this loop as unlinked ".o" files.
 * 3. Execute linking
 *   a. Post-loop cleanup.
 *   b. If enabled, run prelinking.
 *   c. link with `ld`.
 *   d. If enabled, run supplementary programs: `filter`, `patch`, and `strip`.
 *   .
 * 4. Final cleanup and exit
 */
int main(int argc, char** argv) {
    register int i;
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
    unsigned int spD8;
    char* spD4;
    int spD0;
    struct stat sp48;

    sp148 = 0;
    sp144 = NULL;
    sp140 = NULL;

    progname = argv[0];

    if ((ansichoice == ANSICHOICE_ANSI) || (ansichoice == ANSICHOICE_ANSIPOSIX)) {
        CRTX = "acrt1.o";
    } else {
        CRTX = "crt1.o";
    }
    MCRTX = "mcrt1.o";
    m4 = "/usr/bin/m4";
    ratfor = "/usr/bin/ratfor";

    xpg_env = getenv("_XPG");
    if (xpg_env != NULL) {
        xpg_flag = TRUE;
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
        default_svr4 = TRUE;
    }

    sp138 = getenv("SGI_CC");
    if (sp138 != NULL) {
        while (isspace(*sp138)) {
            sp138++;
        }
        sp130 = strlen(sp138);
        if (sp130 <= 0) {
            error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "Environment variable SGI_CC is empty: ignored\n");
        } else {
            sp134 = sp130 + sp138 - 1;
            while (isspace(*sp134)) {
                sp134--;
            }
            sp134++;
            *sp134 = '\0';
            if (strcmp(sp138, "-cckr") == 0) {
                ansichoice = ANSICHOICE_KR;
                cppchoice = CPP_CHOICE_2;
                relocate_passes("p", NULL, NULL);
            } else if (strcmp(sp138, "-ansi") == 0) {
                ansichoice = ANSICHOICE_ANSI;
                cppchoice = CPP_CHOICE_3;
                relocate_passes("p", NULL, NULL);
            } else if (strcmp(sp138, "-xansi") == 0) {
                ansichoice = ANSICHOICE_XANSI;
                cppchoice = CPP_CHOICE_3;
                relocate_passes("p", NULL, NULL);
            } else if (strcmp(sp138, "-ansiposix") == 0) {
                ansichoice = ANSICHOICE_ANSIPOSIX;
                cppchoice = CPP_CHOICE_3;
                relocate_passes("p", NULL, NULL);
            } else {
                error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                      "Environment variable SGI_CC contents unrecognizable and ignored; \"%s\" not one of: -cckr -ansi "
                      "-xansi -ansiposix\n",
                      sp138);
                sp138 = NULL;
            }
        }
    }
    compiler = COMPILER_1;

    // Find the basename of the executable (look for the last '/' in the program name. If there is no '/', progname is
    // the basename, otherwise basename starts 1 char past the found '/'.
    var_s1 = strrchr(progname, '/');
    var_s1 = (var_s1 == NULL) ? progname : var_s1 + 1;

    compdirs[0] = mkstr(var_s1, "/", NULL);

    // Determine compiler based on basename of executable
    if (strncmp(var_s1, "cc", strlen("cc")) == 0) { // C
        compiler = COMPILER_1;
        Bstring = var_s1 + strlen("cc");
    } else if (strncmp(var_s1, "pc", strlen("pc")) == 0) { // Pascal
        compiler = COMPILER_2;
        Bstring = var_s1 + strlen("pc");
    } else if (strncmp(var_s1, "f77", strlen("f77")) == 0) { // FORTRAN 77
        compiler = COMPILER_3;
        Bstring = var_s1 + strlen("f77");
    } else if (strncmp(var_s1, "f90", strlen("f90")) == 0) { // Fortran 90
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-32 compilation not supported for ucode\n");
        exit(2);
    } else if (strncmp(var_s1, "as", strlen("as")) == 0) { // (MIPS) Assembly
        compiler = COMPILER_4;
        Bstring = var_s1 + strlen("as");
        strcpy(compdirs[0], compdirs[1]);
    } else if (strncmp(var_s1, "pl1", strlen("pl1")) == 0) { // PL/I
        compiler = COMPILER_5;
        Bstring = var_s1 + strlen("pl1");
    } else if (strncmp(var_s1, "cobol", strlen("cobol")) == 0) { // COBOL
        compiler = COMPILER_6;
        Bstring = var_s1 + strlen("cobol");
    } else if (strncmp(var_s1, "ncc", strlen("ncc")) == 0) {
        compiler = COMPILER_1;
        c_compiler_choice = C_COMPILER_CHOICE_1;
        edison_cpp = 1;
        Bstring = var_s1 + strlen("ncc");
    } else if (strncmp(var_s1, "CC.eh", strlen("CC.eh")) == 0) {
        compiler = COMPILER_1;
        c_compiler_choice = C_COMPILER_CHOICE_2;
        edison_cpp = 1;
        anachronisms = FALSE;
        cfront_compatible = FALSE;
        D_1000BF7C = FALSE;
        exception_handling = TRUE;
        Bstring = var_s1 + strlen("CC"); //! @bug too short?
    } else if (strncmp(var_s1, "CC", strlen("CC")) == 0) {
        compiler = COMPILER_1;
        c_compiler_choice = C_COMPILER_CHOICE_2;
        edison_cpp = 1;
        D_1000BF7C = FALSE;
        Bstring = var_s1 + strlen("CC");
    } else if (strncmp(var_s1, "NCC", strlen("NCC")) == 0) {
        compiler = COMPILER_1;
        c_compiler_choice = C_COMPILER_CHOICE_2;
        edison_cpp = 1;
        Bstring = var_s1 + strlen("NCC");
    } else if (strncmp(var_s1, "DCC", strlen("DCC")) == 0) {
        compiler = COMPILER_1;
        c_compiler_choice = C_COMPILER_CHOICE_3;
        edison_cpp = 1;
        Bstring = var_s1 + strlen("DCC");
        D_1000BF90 = TRUE;
    }
    Bstring = NULL; // This appears to make the `Bstring` operations done in the above code useless?

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
    D_1000BF8C = (sp12C == NULL) || (sp12C[0] == '\0') || sp12C[0] == '0';
    if (!D_1000BF8C) {
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

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-non_shared") == 0) {
            non_shared = TRUE;
            if (Oflag < 3) {
                Gnum = "8";
            }
        } else if (strcmp(argv[i], "-irix4") == 0) {
            irix4 = TRUE;
            Gnum = "8";
        } else if (strcmp(argv[i], "-coff") == 0) {
            LD = "old_ld";
            coff_spec = TRUE;
            kpic_flag = FALSE;
            Gnum = "8";
        } else if (strcmp(argv[i], "-mips3") == 0) {
            mips3flag = TRUE;
            Gnum = "8";
            kpic_flag = FALSE;
        } else if (strcmp(argv[i], "-excpt") == 0) {
            excpt_flag = TRUE;
            kpic_flag = FALSE;
            Gnum = "8";
        } else if (strcmp(argv[i], "-abi") == 0) {
            abi_flag = 1;
            mips1flag = TRUE;
            mips2flag = FALSE;
        } else if (strcmp(argv[i], "-O3") == 0) {
            Oflag = 3;
        } else if (strcmp(argv[i], "-old_ld") == 0) {
            LD = "old_ld";
            D_1000BF90 = FALSE;
        }
    }

    if ((compiler == COMPILER_1) || (compiler == COMPILER_2) || (compiler == COMPILER_3) || (compiler == COMPILER_4)) {
        docpp = TRUE;
        default_nocpp = FALSE;
    } else {
        docpp = FALSE;
        default_nocpp = TRUE;
    }

    currcomp = compdirs[0];
    mklist(&dirs_for_nonshared_crtn);
    mklist(&dirs_for_abi_crtn);
    mklist(&dirs_for_crtn);

    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-nostdlib") == 0) {
                sp148 = 1;
            } else {
                switch (argv[i][1]) {
                    case 'E':
                        if ((argv[i][3] == '\0') && ((argv[i][2] == 'B') || (argv[i][2] == 'L'))) {
                            if (argv[i][2] == 'B') {
                                if (Bflag && (targetsex != BIGENDIAN)) {
                                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                                          "-EB or -EL must precede any -B flags for ucode compilers.\n");
                                    exit(2);
                                }
                                targetsex = BIGENDIAN;
                            } else { // argv[i][2] == 'L'
                                if (Bflag && (targetsex != LITTLEENDIAN)) {
                                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                                          "-EB or -EL must precede any -B flags for ucode compilers.\n");
                                    exit(2);
                                }
                                targetsex = LITTLEENDIAN;
                            }
                            newrunlib();
                        }
                        break;

                    case 'L':
                        if (argv[i][2] == '\0') {
                            if (((i + 1) >= argc) || (argv[i + 1][0] == '-') || !isdir(argv[i + 1])) {
                                sp148 = 1;
                                break;
                            } else {
                                i++;
                                sp128 = mkstr(argv[i], NULL);
                            }
                        } else {
                            sp128 = mkstr(argv[i] + 2, NULL);
                        }
                        if (sp128[strlen(sp128) - 1] == '/') {
                            sp128[strlen(sp128) - 1] = '\0';
                        }
                        addstr(&dirs_for_crtn, sp128);
                        addstr(&dirs_for_nonshared_crtn, sp128);
                        addstr(&dirs_for_abi_crtn, sp128);
                        break;
                }
            }
        }
    }

    if (sp148 == 0) {
        if (non_shared || coff_spec || mips3flag || excpt_flag) {
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

    if (compiler == COMPILER_1) {
        oldcflag = FALSE;
    } else {
        cpp_stdflag = "-std0";
    }

    systype = "svr4";
    svr4_systype = TRUE;

    process_config(argc, argv);
    parse_command(argc - 1, argv + 1);

    func_00431DD8();

    if (D_1000BF74) {
        if (D_1000BF80 == NULL) {
            D_1000BF80 = "";
        }
        sp144 = mkstr((D_1000BF78 ? "-YSv" : "-YSz"), D_1000BF80, NULL);
        if (compiler == COMPILER_1) {
            addstr(&edisonflags, sp144);
        } else {
            if (D_1000BF78) {
                sp140 = "-cvs_nosrc";
            } else {
                sp140 = "-cvs";
            }
            if (D_1000BF80[0] != '\0') {
                sp140 = mkstr(sp140, ",", D_1000BF80, NULL);
            }
            addstr(&fcomflags, sp140);
        }
    }

    if (!user_systype) {
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

    if ((mips2flag || mips3flag || sixty4bitflag) && !kpic_flag && (non_shared || call_shared || default_call_shared)) {
        if (!non_shared) {
            non_shared = TRUE;
            old_non_shared = TRUE;
        }
        default_call_shared = FALSE;
        call_shared = FALSE;
        if (!non_shared_emitted) {
            addstr(&ldflags, "-non_shared");
            addstr(&cfeflags, "-non_shared");
            non_shared_emitted = TRUE;
        }
    }
    if (non_shared && !non_shared_emitted) {
        addstr(&ldflags, "-non_shared");
        addstr(&cfeflags, "-non_shared");
        non_shared_emitted = TRUE;
    } else if (call_shared) {
        addstr(&ldflags, "-call_shared");
        addstr(&cfeflags, "-call_shared");
    }

    if (!Vflag && (srcfiles.length == 0) && (objfiles.length == 0) && (ufiles.length == 0)) {
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "no source, object or ucode file specified\n");
        exit(2);
    }

    if (w1flag == 1) {
        addstr(&fcomflags, "-w1");
    } else if (w1flag == 2) {
        addstr(&fcomflags, "-w");
    }

    if ((srcexists == 0) && (cflag || Sflag)) {
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "no source file for ucode compilers.\n");
        exit(4);
    }

    if (mp_flag && (gflag != 0) && (mp_flag & 1)) {
        mp_flag |= 4;
    }
    if ((cmp_flag != 0) && (gflag != 0) && (cmp_flag & 1)) {
        cmp_flag |= 4;
    }

    if ((ansichoice == ANSICHOICE_ANSI) || (ansichoice == ANSICHOICE_ANSIPOSIX)) {
        CRTX = "acrt1.o";
        crtn_required = TRUE;
    }

    relocate_passes("r", NULL, NULL);

    if ((B_1000ED30 != 0) && (compiler == COMPILER_1) &&
        ((ansichoice == ANSICHOICE_ANSI) || (ansichoice == ANSICHOICE_ANSIPOSIX))) {
        error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
              "'-lc_s' specified. Shared version of C library does not conform to ANSI X3.159-1989.\n");
    }

    //! FAKE: The second and third comparison of this if check are fake and optimized out
    if (Oflag >= 3 && Oflag >= 3 && Oflag >= 3) {}

    if (kpic_flag && (strcmp(Gnum, "0") != 0) && (Oflag < 3)) {
        error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
              "-KPIC (the default) is only compatible with -G 0 for ucode compilers, changing to -G 0. \n");
        Gnum = "0";
    }

    if ((abi_flag != 0) && non_shared) {
        error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
              "-non_shared is not compatible with -abi for ucode compilers, changing to -abi.\n");
        non_shared = FALSE;
        kpic_flag = TRUE;
        Gnum = "0";
    }

    if ((Oflag >= 3) && (compiler == COMPILER_4)) {
        error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
              "-O3 is not supported for assembly compiles for ucode compilers; changing to -O2.\n");
        Oflag = 2;
        uload = FALSE;
    }

    get_host_chiptype();

    if (targetsex == BIGENDIAN) {
        addstr(&cppflags, "-D_MIPSEB");
        if ((compiler != COMPILER_1) || (ansichoice == ANSICHOICE_KR) || (ansichoice == ANSICHOICE_XANSI)) {
            addstr(&cppflags, "-DMIPSEB");
        }
        if ((compiler == COMPILER_1) && ((ansichoice == ANSICHOICE_ANSI) || (ansichoice == ANSICHOICE_ANSIPOSIX) ||
                                         ((ansichoice == ANSICHOICE_XANSI) && !irix4))) {
            addstr(&cppflags, "-D__STDC__=1");
        }
        if ((compiler == COMPILER_1) && (ansichoice == ANSICHOICE_ANSIPOSIX)) {
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
        if ((compiler != COMPILER_1) || (ansichoice == ANSICHOICE_KR) || (ansichoice == ANSICHOICE_XANSI)) {
            addstr(&cppflags, "-DMIPSEL");
        }
        if ((compiler == COMPILER_1) && ((ansichoice == ANSICHOICE_ANSI) || (ansichoice == ANSICHOICE_ANSIPOSIX) ||
                                         ((ansichoice == ANSICHOICE_XANSI) && !irix4))) {
            addstr(&cppflags, "-D__STDC__=1");
        }
        if ((compiler == COMPILER_1) && (ansichoice == ANSICHOICE_ANSIPOSIX)) {
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

    // Propagate `gFlag`
    switch (gflag) {
        case 0:
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
            if (!nocode) {
                addstr(&edisonflags, "-Zg0");
            }
            break;

        case 1:
            addstr(&edisonflags, "-Zg1");
            addstr(&ccomflags, "-Xg1");
            add_info("-g1");
            break;

        case 2:
            addstr(&edisonflags, "-Zg2");
            addstr(&ccomflags, "-Xg2");
            add_info("-g2");
            break;

        case 3:
            gflag++;
            addstr(&edisonflags, "-Zg3");
            addstr(&ccomflags, "-Xg3");
            add_info("-g3");
            break;
    }

    if (mp_flag && ddoptflag) {
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't use -mp/-pfa with -ddopt\n");
        exit(2);
    }
    if (mips3flag && !thirty2bitflag) {
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-mips3 implies -64bit for ucode compilers, which is not supported.\n");
        exit(2);
    }
    if (irix4 && (compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "IRIX4 not supported in Delta-C++\n");
        exit(2);
    }
    if (irix4 && (compiler == COMPILER_3) && D_1000BF74) {
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "IRIX4 and -sa not supported together\n");
        exit(2);
    }
    if ((cflag || Sflag || nocode || Eflag || Pflag) && make_edison_shlib) {
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
              "-shared can be specified only when a link is to be performed for ucode compilers\n");
        exit(2);
    }

    if (!cflag && !nocode && (srcfiles.length == 1) && (objfiles.length == 1)) {
        default_template_instantiation_mode = 1;
    }
    if ((compiler == COMPILER_1) &&
        ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3)) && Fflag &&
        smart_build) {
        error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
              "-F and -smart cannot be specified together for ucode compilers: -smart ignored\n");
        smart_build = FALSE;
    }
    if ((default_template_instantiation_mode != 0) && !force_prelink) {
        no_prelink = TRUE;
    }

    if ((compiler == COMPILER_1) && (c_compiler_choice == C_COMPILER_CHOICE_3)) {
        sp124 = getenv("DCC_FORCE_OPT");
        sp120 = 1;
        if (Oflag >= 3) {
            Oflag = 2;
            uload = FALSE;
        }
        if (sp124 != NULL) {
            if ((sp124[0] >= '0') && (sp124[0] <= '3') && (sp124[1] == '\0')) {
                sp120 = sp124[0] - '0';
            }
        }
        if (Oflag > sp120) {
            Oflag = sp120;
        }
    }

    addstr(&execlist, "-Dunix");

    if (dmips_emit == 0) {
        if (mips2flag) {
            if (dwopcodeflag) {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't mix -mips2 with -dwopcode for ucode compilers\n");
                exit(2);
            }
            addstr(&execlist, "-Dmips=2");
        }
        if (mips3flag) {
            addstr(&execlist, "-Dmips=3");
        } else {
            addstr(&execlist, "-Dmips=1");
        }
    }

    addstr(&execlist, "-Dhost_mips");

    if (sixty4bitflag) {
        addstr(&ccomflags, "-64bit");
        add_info("-64bit");
        addstr(&ccomflags, "-dwopcode");
        add_info("-dwopcode");
        if (!mips3flag) {
            chip_targ = CHIP_TARGET_MIPS3;
            mips3flag = TRUE;
            addstr(&ccomflags, "-mips3");
            add_info("-mips3");
            relocate_passes("M", NULL, NULL);
        }
    } else if (dwopcodeflag) {
        addstr(&ccomflags, "-dwopcode");
        add_info("-dwopcode");
        if (!mips3flag) {
            chip_targ = CHIP_TARGET_MIPS3;
            mips3flag = TRUE;
            addstr(&ccomflags, "-mips3");
            add_info("-mips3");
            relocate_passes("M", NULL, NULL);
        }
    }

    // Propagate `Oflag`
    switch (Oflag) { /* switch 1 */
        case 0:      /* switch 1 */
            var_s1 = "-O0";
            break;
        case 1: /* switch 1 */
            var_s1 = "-O1";
            break;
        case 2: /* switch 1 */
            var_s1 = "-O2";
            break;
        case 3: /* switch 1 */
            var_s1 = "-O3";
            break;
        case 4: /* switch 1 */
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

    if (compiler == COMPILER_3) {
        if (automaticflag) {
            addstr(&fcomflags, "-automatic");
        } else {
            addstr(&fcomflags, "-static");
            addstr(&optflags, "-static");
        }
    }
    if (Vflag) {
        whats();
    }
    if (runerror != 0) {
        exit(1);
    }
    if (sigset(SIGINT, SIG_IGN) != SIG_IGN) {
        sigset(SIGINT, handler);
    }
    if (sigset(SIGTERM, SIG_IGN) != SIG_IGN) {
        sigset(SIGTERM, handler);
    }
    if (sigset(SIGPIPE, SIG_IGN) != SIG_IGN) {
        sigset(SIGPIPE, handler);
    }

    if ((compiler == COMPILER_6) && nolockflag && lpilockflag) {
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
              "Conflicting flags; -nolock and -lpilock can't both be specified for ucode compilers\n");
        exit(2);
    }

    if ((Oflag >= 3) && cflag && (srcfiles.length == 1)) {
        error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
              "-c should not be used with ucode -O3 -o32 on a single file; use -j instead to get inter-module "
              "optimization.\n");
    }

    if ((srcfiles.length >= 2) && (compiler == COMPILER_4) && !Eflag && !Pflag) {
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "only one source file can be specified with %s for ucode compilers\n",
              "as");
        exit(2);
    }

    mktempstr();

    // Main loop for program execution, runs per source file
    for (i = 0; (i < srcfiles.length) || uload; i++) {
        nocompileneeded = FALSE;
        sp118 = NULL;
        longlong_emitted = FALSE;
        sp11C = D_1000BF74;

        // Finished srcfiles, `uload` on.
        if (i == srcfiles.length) {
            uload = FALSE;
            if ((runerror == 0) && !Eflag && !Pflag) {
                if (uoutfile == NULL) {
                    addstr(&srcfiles, "u.out.?");
                } else if (getsuf(uoutfile) != '\0') {
                    addstr(&srcfiles, mksuf(uoutfile, '?'));
                } else {
                    addstr(&srcfiles, mkstr(uoutfile, ".?", NULL));
                }
                srcsuf = '?';
                if ((Hchar == 's') || (Hchar == 'm') || (Hchar == 'o') || (Hchar == 'c') || Kflag) {
                    symtab = mksuf(srcfiles.entries[i], 'T');
                    tmpst = 0;
                } else {
                    symtab = tempstr[0];
                    tmpst = 1;
                }
                goto phase_uld;
            }
            continue;
        }

        if (srcfiles.length >= 2) {
            fprintf(stderr, "%s:\n", srcfiles.entries[i]);
        }
        if (NoMoreOptions && (*srcfiles.entries[i] == '-')) {
            passin = func_00433534(srcfiles.entries[i]);
        } else {
            passin = srcfiles.entries[i];
        }
        if (compiler != COMPILER_4) {
            srcsuf = getsuf(srcfiles.entries[i]);
            if (srcsuf == 'm') {
                srcsuf = 'f';
            }
        } else {
            srcsuf = 's';
        }
        if ((Hchar == 'f') || (Hchar == 's') || (Hchar == 'm') || (Hchar == 'o') || (Hchar == 'k') || (Hchar == 'c') ||
            Kflag || (srcsuf == 'B') || (srcsuf == 'U') || (srcsuf == 'O') || (srcsuf == 'G') || (srcsuf == 'S') ||
            (srcsuf == 'M') || (srcsuf == 'V') || (srcsuf == 'D') || (srcsuf == 'Q')) {
            tmpst = 0;
            if ((compiler == COMPILER_4) && (getsuf(srcfiles.entries[i]) == '\0')) {
                symtab = mkstr(srcfiles.entries[i], ".T", NULL);
            } else {
                symtab = mksuf(srcfiles.entries[i], 'T');
            }
        } else {
            tmpst = 1;
            symtab = tempstr[0];
        }

        switch (srcsuf) { /* switch 11 */
            case 's':     /* switch 11 */
                if (compiler == COMPILER_1) {
                    if (compdirs[0] != currcomp) {
                        currcomp = compdirs[0];
                        relocate_passes("pKfjsmvocabtyz", NULL, NULL);
                    }
                }
                /* fallthrough */
            case 'i': /* switch 11 */
                if (compiler == COMPILER_1) {
                    if (compdirs[0] != currcomp) {
                        currcomp = compdirs[0];
                        relocate_passes("pKfjsmvocabtyz", NULL, NULL);
                    }
                }
                /* fallthrough */
            case SUF_6: /* switch 11 */
            case 'c':   /* switch 11 */
                if (compiler != COMPILER_1) {
                    if (compdirs[1] != currcomp) {
                        currcomp = compdirs[1];
                        relocate_passes("pKfjsmvocabtyz", NULL, NULL);
                    }
                } else {
                    if (compdirs[0] != currcomp) {
                        currcomp = compdirs[0];
                        relocate_passes("pKfjsmvocabtyz", NULL, NULL);
                    }
                }
                compchoice = COMP_CHOICE_0;
                break;

            case 'p': /* switch 11 */
                if (compiler != COMPILER_2) {
                    if (compdirs[2] != currcomp) {
                        currcomp = compdirs[2];
                        relocate_passes("pfjsmvocabtyz", NULL, NULL);
                    }
                } else {
                    if (compdirs[0] != currcomp) {
                        currcomp = compdirs[0];
                        relocate_passes("pfjsmvocabtyz", NULL, NULL);
                    }
                }
                break;

            case 'F': /* switch 11 */
            case 'f': /* switch 11 */
                if (compiler != COMPILER_3) {
                    if (compdirs[3] != currcomp) {
                        currcomp = compdirs[3];
                        relocate_passes("pfjsmvocabtyz", NULL, NULL);
                    }
                } else {
                    if (compdirs[0] != currcomp) {
                        currcomp = compdirs[0];
                        relocate_passes("pfjsmvocabtyz", NULL, NULL);
                    }
                }
                break;

            case SUF_1: /* switch 11 */
                if (compiler != COMPILER_5) {
                    if (compdirs[5] != currcomp) {
                        currcomp = compdirs[5];
                        relocate_passes("pfekjsmvocabtyz", NULL, NULL);
                    }
                } else {
                    if (compdirs[0] != currcomp) {
                        currcomp = compdirs[0];
                        relocate_passes("pfekjsmvocabtyz", NULL, NULL);
                    }
                }
                break;

            case SUF_2: /* switch 11 */
                if (compiler != COMPILER_6) {
                    if (compdirs[6] != currcomp) {
                        currcomp = compdirs[6];
                        relocate_passes("pfekjsmvocabtyz", NULL, NULL);
                    }
                } else {
                    if (compdirs[0] != currcomp) {
                        currcomp = compdirs[0];
                        relocate_passes("pfekjsmvocabtyz", NULL, NULL);
                    }
                }
                break;

            case SUF_3: /* switch 11 */
                if ((compiler != COMPILER_1) && (compiler != COMPILER_5) && (compiler != COMPILER_6)) {
                    if ((compdirs[1] != currcomp) && (compdirs[5] != currcomp) && (compdirs[6] != currcomp)) {
                        currcomp = compdirs[1];
                        relocate_passes("pekjsmvocabtyz", NULL, NULL);
                    }
                } else {
                    if (compdirs[0] != currcomp) {
                        currcomp = compdirs[0];
                        relocate_passes("pfjsmvocabtyz", NULL, NULL);
                    }
                }
                break;
        }

        if ((compiler == COMPILER_3) && D_1000BF74 && (srcsuf != 'f') && (srcsuf != 'F')) {
            D_1000BF74 = FALSE;
            relocate_passes("f", NULL, NULL);
        }
        if (D_1000BF74 &&
            ((compiler == COMPILER_3) || ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)))) {
            record_static_fileset(srcfiles.entries[i]);
        }

        if ((compiler == COMPILER_1) && (c_compiler_choice == C_COMPILER_CHOICE_1)) {
            switch (ansichoice) {
                case ANSICHOICE_ANSI:
                case ANSICHOICE_ANSIPOSIX:
                    edison_type = EDISON_TYPE_2;
                    break;
                case ANSICHOICE_XANSI:
                    edison_type = EDISON_TYPE_1;
                    break;
                default:
                case ANSICHOICE_KR:
                    edison_type = EDISON_TYPE_3;
                    break;
            }
        }

    repeat_after_edit:
        if (compchoice == COMP_CHOICE_0) {
            if (irix4) {
                if (ansichoice == ANSICHOICE_KR) {
                    compchoice = COMP_CHOICE_1;
                } else {
                    compchoice = COMP_CHOICE_2;
                }
            } else {
                if (ansichoice == ANSICHOICE_KR) {
                    compchoice = COMP_CHOICE_3;
                } else {
                    compchoice = COMP_CHOICE_3;
                }
            }
        }

        if (!Eflag || (srcsuf == 'a')) {
            switch (srcsuf) { /* switch 19 */
                case SUF_6:   /* switch 19 */
                case 'c':     /* switch 19 */
                    if (oldccomflag != TRUE) {
                        oldcflag = FALSE;
                    }
                    if (docpp || default_nocpp) {
                        goto block_531;
                    }
                    goto phase_copt;

                case 'i': /* switch 19 */
                    // 'i' is a preprocessed file so does not convey a specific compiler by itself
                    switch (compiler) {
                        case COMPILER_1:
                            goto phase_copt;
                        case COMPILER_2:
                            goto phase_upas;
                        case COMPILER_3:
                            goto phase_fopt;
                        case COMPILER_4:
                            goto block_512;
                        case COMPILER_5:
                            goto phase_upl1;
                        case COMPILER_6:
                            goto phase_ucob;
                    }
                    // fallthrough
                case 'p': /* switch 19 */
                block_512:
                    if (stdflag != 0 || (!docpp && !default_nocpp)) {
                        goto phase_upas;
                    }
                    goto block_531;

                case 'f': /* switch 19 */
                    if (docpp) {
                        goto block_531;
                    }
                    goto phase_fopt;

                case SUF_1: /* switch 19 */
                    if (docpp) {
                        goto block_531;
                    }
                    goto phase_upl1;

                case SUF_2: /* switch 19 */
                    if (docpp) {
                        goto block_531;
                    }
                    goto phase_ucob;

                case SUF_3: /* switch 19 */
                    goto phase_ulpi;

                case 'U': /* switch 19 */
                    execlist.length = 0;
                    addstr(&execlist, "utob");
                    addstr(&execlist, srcfiles.entries[i]);
                    if (Kflag) {
                        passout = mksuf(srcfiles.entries[i], 'B');
                    } else {
                        passout = tempstr[1];
                    }
                    if ((passout != NULL) && (regular_not_writeable(passout) == 1)) {
                        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n",
                              passout);
                        exit(2);
                    }
                    addstr(&execlist, passout);
                    if (run(utob, execlist.entries, NULL, NULL, NULL) != 0) {
                        runerror++;
                        if (!Kflag) {
                            unlink(passout);
                        }
                        continue;
                    }
                    passin = passout;
                    goto phase_ujoin;

                case 'e': /* switch 19 */
                case 'r': /* switch 19 */
                case 's': /* switch 19 */
                    goto phase_m4;

                case 'u': /* switch 19 */
                    goto phase_usplit;

                case 'B': /* switch 19 */
                    goto phase_ujoin;

                case 'S': /* switch 19 */
                    goto phase_umerge;

                case 'M': /* switch 19 */
                    goto phase_uloop;

                case 'G': /* switch 19 */
                    goto phase_as1;

                case 'D': /* switch 19 */
                case 'Q': /* switch 19 */
                case 'V': /* switch 19 */
                    goto phase_uopt;

                case 'O': /* switch 19 */
                    goto phase_ugen;
            }
        }

    block_531:
        dmips_emit = 0;
        execlist.length = 0;
        sp114 = cppchoice;
        execlist.length = 0;

        if (Eflag && !irix4) {
            compchoice = COMP_CHOICE_3;
        } else if (srcsuf == 's') {
            compchoice = COMP_CHOICE_4;
        }

        if ((srcsuf == 'c') || (srcsuf == SUF_6) ||
            ((compiler == COMPILER_1) && nocode && D_1000BF74 && (srcsuf == 'h'))) {
            if ((cppchoice != CPP_CHOICE_2) || (oldcppflag && (ansichoice != ANSICHOICE_KR))) {
                cppchoice = CPP_CHOICE_1;
                relocate_passes("p", NULL, NULL);
            }
        } else if ((srcsuf == 'h') && (compiler == COMPILER_1)) {
            if (cppchoice == CPP_CHOICE_0) {
                cppchoice = CPP_CHOICE_1;
                relocate_passes("p", NULL, NULL);
            }
        } else if (compiler == COMPILER_1) {
            if (!Eflag && !Pflag && (cppchoice == CPP_CHOICE_3)) {
                cppchoice = CPP_CHOICE_2;
                relocate_passes("p", NULL, NULL);
            }
        } else if (cppchoice == CPP_CHOICE_3) {
            cppchoice = CPP_CHOICE_2;
            relocate_passes("p", NULL, NULL);
        }

        if (((compchoice == COMP_CHOICE_3) || (compchoice == COMP_CHOICE_4)) && !run_sopt && !(cmp_flag & 1) &&
            !(cmp_flag & 8)) {
            addstr(&execlist, cfe);
        } else {
            if (sixty4bitflag) {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-64bit option is not implemented with ccom or accom.\n");
                exit(2);
            }
            if (c_compiler_choice == C_COMPILER_CHOICE_0) {
                addstr(&execlist, ((cppchoice != CPP_CHOICE_1) && (cppchoice != CPP_CHOICE_3) ? "cpp" : "acpp"));
            }
        }

        if (mips_abi == MIPS_ABI_1) {
            addstr(&execlist, "-D_MIPS_FPSET=16");
            if (mips1flag) {
                addstr(&execlist, "-D_MIPS_ISA=1");
            } else if (mips2flag) {
                addstr(&execlist, "-D_MIPS_ISA=2");
            } else if (mips3flag) {
                addstr(&execlist, "-D_MIPS_ISA=3");
            }
            addstr(&execlist, "-D_ABIO32=1");
            addstr(&execlist, "-D_MIPS_SIM=_ABIO32");
            addstr(&execlist, "-D_MIPS_SZINT=32");
            addstr(&execlist, "-D_MIPS_SZLONG=32");
            addstr(&execlist, "-D_MIPS_SZPTR=32");
        } else if (mips_abi == MIPS_ABI_2) {
            addstr(&execlist, "-D_MIPS_FPSET=32");
            addstr(&execlist, "-D_MIPS_ISA=_MIPS_ISA_MIPS3");
            addstr(&execlist, "-D_MIPS_SIM=_MIPS_SIM_ABI64");
            addstr(&execlist, "-D_MIPS_SZINT=32");
            addstr(&execlist, "-D_MIPS_SZLONG=64");
            addstr(&execlist, "-D_MIPS_SZPTR=64");
        } else if (mips_abi != MIPS_ABI_0) {
            if (1) {}
            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "Unknown value for mips_abi: %d.\n", mips_abi);
            exit(2);
        }

        if (c_compiler_choice == C_COMPILER_CHOICE_0) {
            if (emptyIflag && (compchoice != COMP_CHOICE_3)) {
                addstr(&execlist, "-nostdinc");
            }

            if (cppchoice == CPP_CHOICE_1) {
                if ((ansichoice == ANSICHOICE_KR) || (ansichoice == ANSICHOICE_XANSI)) {
                    addstr(&execlist, "-D__EXTENSIONS__");
                }

                if (compchoice != COMP_CHOICE_3) {
                    if (fullwarn) {
                        addstr(&execlist, "-Wall");
                    }
                    if (acpp_traditional) {
                        addstr(&execlist, "-traditional");
                    }
                    addstr(&execlist, "-trigraphs");
                    if (ansichoice != ANSICHOICE_KR) {
                        addstr(&execlist, "-undef");
                        addstr(&execlist, "-p");
                    }
                }
            }

            if ((cppchoice == CPP_CHOICE_2) && (compchoice == COMP_CHOICE_3)) {
                addstr(&execlist, "-D__EXTENSIONS__");
            }
        } else {
            addstr(&execlist, "-YE");
            if (edison_type == EDISON_TYPE_2) {
                addstr(&execlist, "-a");
            }
            if ((edison_type == EDISON_TYPE_1) || (edison_type == EDISON_TYPE_3)) {
                addstr(&execlist, "-D__EXTENSIONS__");
            }
        }

        switch (srcsuf) { /* switch 13 */
            case SUF_6:   /* switch 13 */
            case 'c':     /* switch 13 */
            case 'h':     /* switch 13 */
                if ((srcsuf != 'h') || D_1000BF74) {
                    if ((compiler == COMPILER_1) &&
                        ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3))) {
                        addstr(&execlist, "-D_LANGUAGE_C_PLUS_PLUS=1");
                        addstr(&execlist, "-D__cplusplus=1");
                        addstr(&execlist, "-D__ANSI_CPP__=1");
                        if ((compiler == COMPILER_1) && (c_compiler_choice == C_COMPILER_CHOICE_3)) {
                            addstr(&execlist, "-D_DELTA_EXTENSIONS=1");
                        }
                    } else {
                        if ((ansichoice == ANSICHOICE_KR) || (ansichoice == ANSICHOICE_XANSI)) {
                            addstr(&execlist, "-DLANGUAGE_C");
                        }
                        addstr(&execlist, "-D_LANGUAGE_C");
                        if (cmp_flag != 0) {
                            addstr(&execlist, "-D_LANGUAGE_PWRC");
                        }
                        if (((cmp_flag & 1) || run_sopt) && (cppchoice == CPP_CHOICE_1)) {
                            addstr(&execlist, "-trigraphs");
                        }
                    }
                }
                break;

            case 'p': /* switch 13 */
                addstr(&execlist, "-DLANGUAGE_PASCAL");
                addstr(&execlist, "-D_LANGUAGE_PASCAL");
                addstr(&execlist, "-Q");
                break;

            case 'F': /* switch 13 */
            case 'e': /* switch 13 */
            case 'f': /* switch 13 */
            case 'r': /* switch 13 */
                addstr(&execlist, "-DLANGUAGE_FORTRAN");
                addstr(&execlist, "-D_LANGUAGE_FORTRAN");
                break;

            case 's': /* switch 13 */
                addstr(&execlist, "-DLANGUAGE_ASSEMBLY");
                addstr(&execlist, "-D_LANGUAGE_ASSEMBLY");
                break;

            case SUF_1: /* switch 13 */
                addstr(&execlist, "-DLANGUAGE_PL1");
                addstr(&execlist, "-D_LANGUAGE_PL1");
                break;

            case SUF_2: /* switch 13 */
                addstr(&execlist, "-DLANGUAGE_COBOL");
                addstr(&execlist, "-D_LANGUAGE_COBOL");
                break;
        }

        if ((ansichoice == ANSICHOICE_KR) || (ansichoice == ANSICHOICE_XANSI)) {
            addstr(&execlist, "-D__INLINE_INTRINSICS");
            addstr(&execlist, "-Dsgi");
            if (!svr4_systype) {
                addstr(&execlist, "-DSVR3");
                addstr(&execlist, "-D__SVR3");
            }
            addstr(&execlist, "-D__sgi");
        } else {
            addstr(&execlist, "-D__sgi");
            if (!svr4_systype) {
                addstr(&execlist, "-D__SVR3");
            }
        }

        if ((compchoice != COMP_CHOICE_3) && dollar_sign) {
            if (cppchoice == CPP_CHOICE_1) {
                addstr(&execlist, "-$");
            } else {
                addstr(&execlist, "-dollar");
            }
        }

        if ((ansichoice == ANSICHOICE_KR) || (ansichoice == ANSICHOICE_XANSI)) {
            addstr(&execlist, "-Dunix");
            addstr(&execlist, "-Dmips");
            addstr(&execlist, "-Dhost_mips");
            addstr(&execlist, "-D__unix");
            addstr(&execlist, "-D__host_mips");
            if (!irix4) {
                if (svr4_systype && (ansichoice != ANSICHOICE_ANSI) && (ansichoice != ANSICHOICE_ANSIPOSIX)) {
                    addstr(&execlist, "-D_SVR4_SOURCE");
                }
                addstr(&execlist, "-D_MODERN_C");
                addstr(&execlist, "-D_SGI_SOURCE");
            }
            if (kpic_flag) {
                addstr(&execlist, "-D_PIC");
            }
            addstr(&execlist, "-D__DSO__");
        } else {
            addstr(&execlist, "-D__unix");
            addstr(&execlist, "-D__host_mips");
            if (!irix4) {
                if (svr4_systype && (ansichoice != ANSICHOICE_ANSI) && (ansichoice != ANSICHOICE_ANSIPOSIX)) {
                    addstr(&execlist, "-D_SVR4_SOURCE");
                }
                addstr(&execlist, "-D_MODERN_C");
            }
            if (kpic_flag) {
                addstr(&execlist, "-D_PIC");
            }
            addstr(&execlist, "-D__DSO__");
        }

        if ((systype != NULL) && !irix4) {
            var_s1 = systype;
            while (*var_s1 != '\0') {
                *var_s1 = toupper(*var_s1);
                var_s1++;
            }
            if ((ansichoice == ANSICHOICE_KR) || (ansichoice == ANSICHOICE_XANSI)) {
                addstr(&execlist, mkstr("-DSYSTYPE_", systype, NULL));
            }
            addstr(&execlist, mkstr("-D_SYSTYPE_", systype, NULL));
        }

        if (!svr4_systype) {
            if ((ansichoice == ANSICHOICE_KR) || (ansichoice == ANSICHOICE_XANSI)) {
                addstr(&execlist, "-DSYSTYPE_SYSV");
            }
            addstr(&execlist, "-D_SYSTYPE_SYSV");
        }

        if (sixty4bitflag) {
            addstr(&execlist, "-D__64BIT");
        }

        if (((ansichoice == ANSICHOICE_KR) || (ansichoice == ANSICHOICE_XANSI)) && !longlong_emitted) {
            addstr(&execlist, "-D_LONGLONG");
            longlong_emitted = TRUE;
        }

        if (dmips_emit == 0) {
            if (mips2flag) {
                if ((call_shared || default_call_shared) && !kpic_flag) {
                    old_non_shared = TRUE;
                    non_shared = TRUE;
                    default_call_shared = FALSE;
                    call_shared = FALSE;
                }
                addstr(&execlist, "-D__mips=2");
            } else if (mips3flag) {
                addstr(&execlist, "-D__mips=3");
            } else {
                addstr(&execlist, "-D__mips=1");
            }
        }
        dmips_emit = 1;

        if (irix4) {
            include = mkstr("/usr/irix4/", "usr/include", NULL);
        }
        if ((((include != NULL) && ((strcmp(comp_target_root, "/") != 0) || (systype != NULL))) || fiveflag) &&
            ((compiler != COMPILER_1) || (c_compiler_choice == C_COMPILER_CHOICE_0)) &&
            ((compiler != COMPILER_3) || !D_1000BF74)) {
            addstr(&execlist, "-I");
        }

        addlist(&execlist, &cppflags);

        if (cppchoice == CPP_CHOICE_1) {
            addlist(&execlist, &acppflags);
        }

        addlist(&execlist, &undefineflags);

        if (!emptyIflag) {
            if ((abi_flag != 0) && (includeB != NULL)) {
                addstr(&execlist, mkstr("-I", includeB, NULL));
            }
            if ((einclude != NULL) && (compiler == COMPILER_1) &&
                ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3))) {
                addstr(&execlist, mkstr("-I", einclude, NULL));
            }
            if (include != NULL) {
                addstr(&execlist, mkstr("-I", include, NULL));
            }
        }

        if (Pflag) {
            if ((compiler == COMPILER_4) && (getsuf(srcfiles.entries[i]) == 0)) {
                passout = mkstr(srcfiles.entries[i], ".i", NULL);
            } else {
                passout = mksuf(srcfiles.entries[i], 'i');
            }
        } else if (Eflag) {
            passout = NULL;
        } else if ((Hchar == 'K') || Kflag) {
            if ((compchoice == COMP_CHOICE_3) && !run_sopt && !acpp && (cmp_flag == 0) && (compiler == COMPILER_1)) {
                passout = mksuf(srcfiles.entries[i], 'B');
            } else {
                passout = mksuf(srcfiles.entries[i], 'i');
            }
        } else {
            passout = tempstr[2];
        }
        if ((passout != NULL) && (regular_not_writeable(passout) == 1)) {
            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
            exit(2);
        }

        if ((compiler == COMPILER_3) && D_1000BF74) {
            addstr(&execlist, "-K");
            addstr(&execlist, "-E");
            addstr(&execlist, sp144);
        }

        if (c_compiler_choice == C_COMPILER_CHOICE_0) {
            addstr(&execlist, passin);
        }

        if (((compchoice != COMP_CHOICE_3) && (compchoice != COMP_CHOICE_4)) ||
            ((compiler != COMPILER_1) && (compiler != COMPILER_4)) || run_sopt || (cmp_flag & 1) || (cmp_flag & 8) ||
            acpp || oldcppflag) {
            if (run((((compiler == COMPILER_3) && D_1000BF74) ? cfe : cpp), execlist.entries, NULL, passout, NULL) !=
                0) {
                runerror++;
                if (!Eflag && ((((srcsuf == 'e') || (srcsuf == 'r')) && !Kflag) || ((srcsuf == 's') && mflag))) {
                    unlink(passin);
                }
                unlink(passout);
                cppchoice = sp114;
                relocate_passes("p", NULL, NULL);
                continue;
            }
            goto block_922;
        }

        cppchoice = sp114;
        relocate_passes("p", NULL, NULL);

        if (((srcsuf == 'c') || (srcsuf == SUF_6) ||
             ((compiler == COMPILER_1) && nocode && D_1000BF74 && (srcsuf == 'h'))) &&
            !Pflag && !Eflag) {
            goto block_1042;
        }

        if (!minus_M) {
            addstr(&execlist, "-E");
        }

        if ((compiler != COMPILER_1) || (c_compiler_choice == C_COMPILER_CHOICE_0)) {
            switch (srcsuf) {
                case 'c':
                    addstr(&execlist, "-D_LANGUAGE_C");
                    if (!oldcflag) {
                        addstr(&execlist, "-D_CFE");
                    }
                    break;

                case 'p':
                    addstr(&execlist, "-DLANGUAGE_PASCAL");
                    addstr(&execlist, "-D_LANGUAGE_PASCAL");
                    addstr(&execlist, "-Q");
                    break;

                case 'F':
                case 'e':
                case 'f':
                case 'r':
                    addstr(&execlist, "-DLANGUAGE_FORTRAN");
                    addstr(&execlist, "-D_LANGUAGE_FORTRAN");
                    break;

                case 's':
                    addstr(&execlist, "-std0");
                    addstr(&execlist, "-DLANGUAGE_ASSEMBLY");
                    addstr(&execlist, "-D_LANGUAGE_ASSEMBLY");
                    break;

                case SUF_1:
                    addstr(&execlist, "-DLANGUAGE_PL1");
                    addstr(&execlist, "-D_LANGUAGE_PL1");
                    break;

                case SUF_2:
                    addstr(&execlist, "-DLANGUAGE_COBOL");
                    addstr(&execlist, "-D_LANGUAGE_COBOL");
                    break;
            }
            addstr(&execlist, "-D__unix");
            if (sixty4bitflag) {
                addstr(&execlist, "-D__64BIT");
            }
            if (((ansichoice == ANSICHOICE_KR) || (ansichoice == ANSICHOICE_XANSI)) && !longlong_emitted) {
                addstr(&execlist, "-D_LONGLONG");
                longlong_emitted = TRUE;
            }
            if (dmips_emit == 0) {
                if (mips2flag) {
                    if (call_shared || default_call_shared) {
                        old_non_shared = TRUE;
                        non_shared = TRUE;
                        default_call_shared = FALSE;
                        call_shared = FALSE;
                    }
                    addstr(&execlist, "-D__mips=2");
                } else if (mips3flag) {
                    addstr(&execlist, "-D__mips=3");
                } else {
                    addstr(&execlist, "-D__mips=1");
                }
            }
            dmips_emit = 1;

            addstr(&execlist, "-D__host_mips");
            if (kpic_flag) {
                addstr(&execlist, "-D_PIC");
            }
            addstr(&execlist, "-D__DSO__");
            if (systype != NULL) {
                var_s1 = systype;
                while (*var_s1 != '\0') {
                    *var_s1 = toupper(*var_s1);
                    var_s1++;
                }
            } else {
                addstr(&execlist, "-D_SYSTYPE_SVR4");
            }
        }

        if (!Eflag && !Pflag) {
            if ((((include != NULL) && ((strcmp(comp_target_root, "/") != 0) || (systype != NULL))) || fiveflag) &&
                (c_compiler_choice == C_COMPILER_CHOICE_0)) {
                addstr(&execlist, "-I");
            }
            addlist(&execlist, &cppflags);
            addlist(&execlist, &undefineflags);
            if (cpp_stdflag != NULL) {
                addstr(&execlist, cpp_stdflag);
            }
            if (!emptyIflag) {
                if ((abi_flag != 0) && (includeB != NULL)) {
                    addstr(&execlist, mkstr("-I", includeB, NULL));
                }
                if (include != NULL) {
                    addstr(&execlist, mkstr("-I", include, NULL));
                }
            }
        }

        if ((Pflag || Eflag) && (c_compiler_choice == C_COMPILER_CHOICE_0)) {
            if ((ansichoice == ANSICHOICE_ANSI) || (ansichoice == ANSICHOICE_ANSIPOSIX)) {
                addstr(&execlist, "-std1");
            } else if (ansichoice == ANSICHOICE_XANSI) {
                addstr(&execlist, "-std");
            } else if (ansichoice == ANSICHOICE_KR) {
                addstr(&execlist, "-std0");
            }
        }

        if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
            if (vflag) {
                addstr(&execlist, "-v");
            }
            if (fullwarn) {
                addstr(&execlist, "-Yw");
            }
            if (srcfiles.length == 1) {
                if (outfile != NULL) {
                    sp118 = outfile;
                } else if (!cflag) {
                    sp118 = "a.out";
                } else {
                    sp118 = mksuf(srcfiles.entries[i], 'o');
                }
            } else {
                sp118 = mksuf(srcfiles.entries[i], 'o');
            }
            addstr(&execlist, mkstr("-YN", sp118, NULL));
            if (c_compiler_choice == C_COMPILER_CHOICE_2) {

            } else if (c_compiler_choice == C_COMPILER_CHOICE_3) {
                addstr(&execlist, "-YD");
            } else if (edison_type == EDISON_TYPE_3) {
                addstr(&execlist, "-K");
            } else {
                addstr(&execlist, "-m");
            }
            addstr(&execlist, passin);
        }

        if (Pflag) {
            if ((compiler == COMPILER_4) && (getsuf(srcfiles.entries[i]) == 0)) {
                passout = mkstr(srcfiles.entries[i], ".i", NULL);
            } else {
                passout = mksuf(srcfiles.entries[i], 'i');
            }
        } else if (Eflag) {
            passout = NULL;
        } else {
            passout = tempstr[2];
        }
        if ((passout != NULL) && (regular_not_writeable(passout) == 1)) {
            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
            exit(2);
        }

        if (oldcflag == TRUE) {
            if (oldcppflag) {
                retcode = run(cpp, execlist.entries, NULL, passout, NULL);
            } else {
                retcode = run(cpp, execlist.entries, NULL, passout, NULL);
            }
        } else {
            if (oldcppflag) {
                retcode = run(cpp, execlist.entries, NULL, passout, NULL);
            } else {
                retcode = run(cfe, execlist.entries, NULL, passout, NULL);
            }
        }

        if (retcode != 0) {
            runerror++;
            if (!Eflag && ((((srcsuf == 'e') || (srcsuf == 'r')) && !Kflag) || ((srcsuf == 's') && mflag))) {
                unlink(passin);
            }
            unlink(passout);
            continue;
        }

        if (Pflag || Eflag) {
            continue;
        }

        if ((((srcsuf == 'e') || (srcsuf == 'r')) && !Kflag) || ((srcsuf == 's') && mflag)) {
            unlink(passin);
        }
        passin = passout;
        dmips_emit = 0;

        switch (srcsuf) { /* switch 17 */
            case SUF_1:
                goto phase_upl1;

            case SUF_2: /* switch 17 */
                goto phase_ucob;

            case 'c': /* switch 17 */
                goto phase_copt;

            case 'p': /* switch 17 */
                goto phase_upas;

            case 's': /* switch 17 */
                goto phase_as0;

            case 'F': /* switch 17 */
            case 'e': /* switch 17 */
            case 'f': /* switch 17 */
            case 'r': /* switch 17 */
                goto phase_fopt;
        }

    block_922:
        cppchoice = sp114;
        relocate_passes("p", NULL, NULL);

        if (c_compiler_choice == C_COMPILER_CHOICE_0) {
            if (!Pflag && !Eflag) {
                if ((((srcsuf == 'e') || (srcsuf == 'r')) && !Kflag) || ((srcsuf == 's') && mflag)) {
                    unlink(passin);
                }
                passin = passout;
            } else {
                continue;
            }
        }

        dmips_emit = 0;

        switch (srcsuf) { /* switch 18 */
            case SUF_1:   /* switch 18 */
                goto phase_upl1;

            case SUF_2: /* switch 18 */
                goto phase_ucob;

            case SUF_6: /* switch 18 */
            case 'c':   /* switch 18 */
                goto phase_copt;

            case 'p': /* switch 18 */
                goto phase_upas;

            case 's': /* switch 18 */
                goto phase_as0;

            case 'F': /* switch 18 */
            case 'e': /* switch 18 */
            case 'f': /* switch 18 */
            case 'r': /* switch 18 */
                goto phase_fopt;
        }

    phase_copt:
        if (run_sopt) {
            if (cmp_flag & 1) {
                error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "-sopt and -pca both specified; -sopt ignored.\n");
                goto phase_pca;
            }

            execlist.length = 0;

            addstr(&execlist, "copt");
            if ((Oflag >= 2) && !set_loop_unroll) {
                addstr(&optflags, "-loopunroll");
                addstr(&optflags, "0");
            }
            addstr(&execlist, mkstr("-I=", passin, NULL));
            if ((Hchar == 'K') || Kflag) {
                passout = mksuf(srcfiles.entries[i], 'M');
            } else {
                passout = mkstr(tempstr[31], "M", NULL);
            }
            addstr(&execlist, mkstr("-CMP=", passout, NULL));
            addstr(&execlist, "-cp=i");
            if (ansichoice == ANSICHOICE_KR) {
                addstr(&execlist, "-sy=k");
            }
            addlist(&execlist, &soptflags);

            if (run(copt, execlist.entries, NULL, NULL, NULL) != 0) {
                runerror++;
                if (docpp && (srcsuf != 'i') && !Kflag) {
                    unlink(passin);
                }
                if ((Hchar != 'K') || Kflag) {
                    unlink(passout);
                }
                continue;
            }

            if (docpp && (srcsuf != 'i') && !Kflag) {
                unlink(passin);
            }
            passin = passout;
            if ((compchoice != COMP_CHOICE_3) || (cmp_flag & 0x10000)) {
                if (Hchar == 'K') {
                    continue;
                }
                if ((Hchar == 'K') || Kflag) {
                    passout = mksuf(srcfiles.entries[i], 'I');
                } else {
                    passout = mkstr(tempstr[31], "I", NULL);
                }
                if (vflag) {
                    addstr(&execlist, "-v");
                }
                execlist.length = 0;
                addstr(&execlist, (((cppchoice != CPP_CHOICE_1) && (cppchoice != CPP_CHOICE_3)) ? "cpp" : "acpp"));
                addstr(&execlist, passin);
                if (cppchoice != CPP_CHOICE_2) {
                    cppchoice = CPP_CHOICE_1;
                } else {
                    addstr(&execlist, "-l");
                }
                if (emptyIflag) {
                    addstr(&execlist, "-nostdinc");
                }
                addlist(&execlist, &cpp2flags);

                relocate_passes("p", NULL, NULL);

                if (run(cpp, execlist.entries, NULL, passout, NULL) != 0) {
                    runerror++;
                    if (!Kflag) {
                        unlink(passin);
                    }
                    unlink(passout);
                    continue;
                }

                if (!Kflag) {
                    unlink(passin);
                }
                passin = passout;
            }
            goto block_1042;
        }

    phase_pca:
        {
            if ((Hchar == 'K') || Kflag) {
                cmp_flag |= 6;
            }
            if (cmp_flag & 1) {
                if ((Oflag >= 2) && !set_loop_unroll) {
                    addstr(&optflags, "-loopunroll");
                    addstr(&optflags, "0");
                }

                execlist.length = 0;
                addstr(&execlist, "pca");
                addstr(&execlist, mkstr("-I=", passin, NULL));
                if (cmp_flag & 4) {
                    passout = mksuf(srcfiles.entries[i], 'M');
                } else {
                    passout = mkstr(tempstr[31], "M", NULL);
                }
                addstr(&execlist, mkstr("-CMP=", passout, NULL));
                if (cmp_flag & 2) {
                    sp110 = mksuf(srcfiles.entries[i], 'L');
                } else {
                    sp110 = mkstr(tempstr[31], "L", NULL);
                }
                addstr(&execlist, mkstr("-L=", sp110, NULL));
                addstr(&execlist, "-lo=ls");
                addstr(&execlist, "-cp=i");
                if (ansichoice == ANSICHOICE_KR) {
                    addstr(&execlist, "-sy=k");
                }
                addlist(&execlist, &pcaflags);
                if (run(pca, execlist.entries, NULL, NULL, NULL) != 0) {
                    runerror++;
                    if (docpp && (srcsuf != 'i') && !Kflag) {
                        unlink(passin);
                    }
                    if (!(cmp_flag & 4)) {
                        unlink(passout);
                    }
                    continue;
                }
                if (!(cmp_flag & 2)) {
                    unlink(sp110);
                }
                if (docpp && (srcsuf != 'i') && !Kflag) {
                    unlink(passin);
                }
                passin = passout;

                if (Hchar != 'K') {
                    execlist.length = 0;
                    addstr(&execlist, ((cppchoice != CPP_CHOICE_1) && (cppchoice != CPP_CHOICE_3) ? "cpp" : "acpp"));
                    if ((Hchar == 'K') || Kflag) {
                        passout = mksuf(srcfiles.entries[i], 'I');
                    } else {
                        passout = mkstr(tempstr[31], "I", NULL);
                    }
                    if (vflag) {
                        addstr(&execlist, "-v");
                    }
                    addstr(&execlist, passin);
                    if (cppchoice != CPP_CHOICE_2) {
                        cppchoice = CPP_CHOICE_1;
                    } else {
                        addstr(&execlist, "-l");
                    }
                    if (emptyIflag) {
                        addstr(&execlist, "-nostdinc");
                    }
                    addlist(&execlist, &cpp2flags);
                    addlist(&execlist, &undefineflags);
                    relocate_passes("p", NULL, NULL);
                    if (run(cpp, execlist.entries, NULL, passout, NULL) != 0) {
                        runerror++;
                        if (!Kflag && !(cmp_flag & 4)) {
                            unlink(passin);
                        }
                        unlink(passout);
                        continue;
                    }
                    if (!Kflag && !(cmp_flag & 4)) {
                        unlink(passin);
                    }
                    passin = passout;
                } else
                    continue;
            }
        }

    block_1042:
        if (gflag >= 2) {
            func_00431D00(srcfiles.entries[i]);
        }

        if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) {
            if (!docpp || oldcppflag || run_sopt || (srcsuf == 'i') || acpp) {
                execlist.length = 0;
                addstr(&execlist, cfe);
            }
            if (vflag) {
                addstr(&execlist, "-v");
            }
            if ((compiler == COMPILER_1) &&
                ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3))) {
                if (anachronisms) {
                    addstr(&execlist, "-O");
                }
                if (cfront_compatible) {
                    addstr(&execlist, "-b");
                }
            }
            if (nocode) {
                addstr(&execlist, "-n");
            }
            if (!Fflag) {
                addstr(&execlist, "-Zz");
                addstr(&execlist, "-ZO");
                addstr(&execlist, mkstr("-ZS", symtab, NULL));
            }
            if ((compiler == COMPILER_1) &&
                ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3))) {
                if (Oflag >= 3) {
                    addstr(&execlist, "-Qz");
                }
                if (non_shared) {
                    addstr(&execlist, "-Qn");
                }
            }
            if (signedcharflag) {
                addstr(&execlist, "-s");
            } else {
                addstr(&execlist, "-u");
            }
            if (fullwarn) {
                addstr(&execlist, "-Yw");
            }
            if (disable_inlines) {
                addstr(&execlist, "-YJ");
            }
            if (c_compiler_choice == C_COMPILER_CHOICE_2) {
            } else if (c_compiler_choice == C_COMPILER_CHOICE_3) {
                addstr(&execlist, "-YD");
            } else if (edison_type == EDISON_TYPE_3) {
                addstr(&execlist, "-K");
            } else {
                addstr(&execlist, "-m");
            }

            if (srcsuf == 'i') {
                addstr(&execlist, "-Yp");
            }
            if (smart_build) {
                addstr(&execlist, mkstr("-YR", sbrepos, NULL));
            }

            if (srcfiles.length == 1) {
                if (outfile != NULL) {
                    sp118 = outfile;
                } else if (!cflag) {
                    sp118 = "a.out";
                } else {
                    sp118 = mksuf(srcfiles.entries[i], 'o');
                }
            } else {
                sp118 = mksuf(srcfiles.entries[i], 'o');
            }

            addstr(&execlist, mkstr("-YN", sp118, NULL));
            if ((compiler == COMPILER_1) &&
                ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3))) {
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

                if (no_prelink) {
                    addstr(&execlist, "-T");
                } else {
                    if ((outfile != NULL) && cflag && (srcfiles.length == 1)) {
                        sp10C = outfile;
                    } else {
                        sp10C = mksuf(srcfiles.entries[i], 'o');
                    }
                    sp108 = make_ii_file_name(sp10C);
                    addstr(&execlist, mkstr("-YO", sp108, NULL));
                    free(sp108);
                }

                if (!auto_template_include) {
                    addstr(&execlist, "-B");
                }
            }
            if (gflag >= 2) {
                addstr(&execlist, mkstr("-Zc", tempstr[33], NULL));
            }
            addstr(&execlist, mkstr("-YG", Gnum, NULL));
            addlist(&execlist, &edisonflags);
            if (dollar_sign) {
                addstr(&execlist, "-$");
            }
            if (Fflag) {
                addstr(&execlist, mkstr("-", NULL));
            } else {
                addstr(&execlist, passin);
            }

            var_s1 = 0;
        }

        if (compchoice == COMP_CHOICE_3) {
            if (cmp_flag & 0x10000) {
                if ((Hchar == 'M') || Kflag || (cmp_flag & 4)) {
                    passout = mksuf(srcfiles.entries[i], 'P');
                } else {
                    passout = mkstr(tempstr[31], "P", NULL);
                }

                execlist.length = 0;
                addstr(&execlist, mpc);
                addstr(&execlist, passin);
                addstr(&execlist, mkstr("-K", passout, NULL));
                if ((ansichoice == ANSICHOICE_ANSI) || (ansichoice == ANSICHOICE_ANSIPOSIX)) {
                    addstr(&execlist, "-ansi");
                } else if (ansichoice == ANSICHOICE_KR) {
                    addstr(&execlist, "-cckr");
                } else {
                    addstr(&execlist, "-xansi");
                }
                addlist(&execlist, &mpcflags);
                retcode = run(mpc, execlist.entries, NULL, NULL, errout);
                if (!Kflag) {
                    unlink(passin);
                }
                if (retcode != 0) {
                    runerror++;
                    if ((Hchar != 'M') && !Kflag && !(cmp_flag & 4)) {
                        unlink(passout);
                    }
                    continue;
                }

                if (Hchar == 'M') {
                    continue;
                }

                passin = passout;
            }

            if ((!docpp || oldcppflag || run_sopt || (srcsuf == 'i') || acpp || (cmp_flag & 0x10000)) &&
                (c_compiler_choice == C_COMPILER_CHOICE_0)) {
                execlist.length = 0;
                addstr(&execlist, cfe);
                addstr(&execlist, passin);
            }

            if (Hchar == 'f') {
                if (ucodeflag) {
                    passout = tempstr[3];
                } else {
                    passout = mksuf(srcfiles.entries[i], 'B');
                }
            } else if ((Fflag && !plusIflag) || nocode) {
                passout = NULL;
            } else if (plusIflag) {
                passout = mksuf(srcfiles.entries[i], SUF_7);
            } else if (Kflag) {
                passout = mksuf(srcfiles.entries[i], 'B');
            } else {
                passout = tempstr[3];
            }
            if ((passout != NULL) && (regular_not_writeable(passout) == 1)) {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                exit(2);
            }

            if ((!docpp || (srcsuf == 'i') || acpp || oldcppflag) && !run_sopt) {
                if (!default_nocpp && ((srcsuf == 'c') || (srcsuf == 's') || (srcsuf == 'p'))) {
                    addstr(&execlist, "-nocpp");
                }
                if (srcsuf == i) { //! @bug typo for 'i'? So was this variable was actually called `i`?
                    addstr(&execlist, "-nocpp");
                }
            }

            if (c_compiler_choice == C_COMPILER_CHOICE_0) {
                if (vflag) {
                    addstr(&execlist, "-Xv");
                }
                if (compiler == COMPILER_1) {
                    if (!run_sopt && !(cmp_flag & 1)) {
                        addstr(&execlist, "-D_CFE");
                        addstr(&execlist, "-Amachine(mips)");
                        addstr(&execlist, "-Asystem(unix)");
                        addlist(&execlist, &accomflags);
                    }
                    addlist(&execlist, &cfeflags);
                    addstr(&execlist, "-G");
                    addstr(&execlist, Gnum);
                }
                if ((ansichoice == ANSICHOICE_ANSI) || (ansichoice == ANSICHOICE_ANSIPOSIX)) {
                    addstr(&execlist, "-std1");
                } else if (ansichoice == ANSICHOICE_XANSI) {
                    addstr(&execlist, "-std");
                } else if (ansichoice == ANSICHOICE_KR) {
                    addstr(&execlist, "-std0");
                }
                if (prototype_checking_on) {
                    addstr(&execlist, "-Xprototypes");
                }
                addstr(&execlist, mkstr("-XS", symtab, NULL));
                addlist(&execlist, &ccomflags);
                if (gflag >= 2) {
                    addstr(&execlist, mkstr("-Xcmd:", tempstr[33], NULL));
                }
            }

            if (run_sopt || (cmp_flag & 1)) {
                unlink(tempstr[2]);
            }

            if (run_sopt) {
                addlist(&execlist, &undefineflags);
            }
            retcode = run(cfe, execlist.entries, (Fflag ? passin : NULL), passout, errout);
            if (smart_build && (retcode == 0xFA)) {
                retcode = 0;
                nocompileneeded = TRUE;

                if ((outfile != NULL) && cflag && (srcfiles.length == 1)) {
                    sp104 = outfile;
                } else if ((srcsuf == '?') && (Hchar != 'b') && !Kflag) {
                    tmp_uldobj = sp104 = tempstr[12];
                } else {
                    sp104 = mksuf(srcfiles.entries[i], 'o');
                }

                if (touch(sp118) < 0) {
                    runerror++;
                }

                if ((srcfiles.length == 1) && !cflag) {
                    goto phase_cord;
                }
            }

            if (Fflag) {
                continue;
            }

            if (retcode == 0xFF) {
                c_inline = TRUE;
                addstr(&umergeflags, "-c_inline");
            } else if (retcode != 0) {
                runerror++;
                if ((oldcflag == TRUE) && docpp && (srcsuf != 'i') && (c_compiler_choice == C_COMPILER_CHOICE_0)) {
                    unlink(passin);
                }
                if (!Kflag) {
                    unlink(passout);
                    unlink(symtab);
                }
                continue;
            }

            if ((run_sopt && !Kflag) || acpp || oldcppflag || (cmp_flag & 0x10000)) {
                unlink(passin);
            }

            if (NoMoreOptions && (*passout == '-')) {
                passout = func_00433534(passout);
            }
            passin = passout;

            if ((Hchar == 'f') && ucodeflag) {
                execlist.length = 0;
                addstr(&execlist, "btou");
                addstr(&execlist, passin);
                passout = mksuf(srcfiles.entries[i], 'U');
                if ((passout != NULL) && (regular_not_writeable(passout) == 1)) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
                addstr(&execlist, passout);
                if (run(btou, execlist.entries, NULL, NULL, NULL) != 0) {
                    runerror++;
                    if (!Kflag) {
                        unlink(passin);
                        unlink(passout);
                    }

                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                } else if (!Kflag) {
                    unlink(passin);
                }
                continue;
            }
            passin = passout;
            if (Hchar == 'f') {
                continue;
            }
            if ((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0) &&
                (Eflag || nocode || nocompileneeded)) {
                unlink(passout);
                continue;
            }
            goto phase_ujoin;
        }

    phase_ccom:
        {
            execlist.length = 0;
            addstr(&execlist, (ansichoice != ANSICHOICE_KR) ? "accom" : "ccom");
            if (vflag) {
                addstr(&execlist, "-Xv");
            }
            if (cmp_flag & 0x10000) {
                addstr(&execlist, "-XMP");
            }
            addlist(&execlist, &ccomflags);
            if (dollar_sign) {
                addstr(&execlist, "-Xdollar");
            }
            if (use_real_fp) {
                addstr(&execlist, "-Xreal_fp");
            }
            if (prototype_checking_on || (ansichoice != ANSICHOICE_KR)) {
                addstr(&execlist, "-Xprototypes");
            }
            if (ansichoice != ANSICHOICE_KR) {
                if (ansichoice == ANSICHOICE_XANSI) {
                    addstr(&execlist, "-Xxansi");
                } else {
                    addstr(&execlist, "-Xansi");
                }
                addlist(&execlist, &accomflags);
            }

            if (Hchar == 'f') {
                if (ucodeflag) {
                    passout = tempstr[3];
                } else {
                    passout = mksuf(srcfiles.entries[i], 'B');
                }
            } else if (Kflag) {
                passout = mksuf(srcfiles.entries[i], 'B');
            } else {
                passout = tempstr[3];
            }
            if (regular_not_writeable(passout) == 1) {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                exit(2);
            }

            addstr(&execlist, mkstr("-XS", symtab, NULL));
            if (!Kflag && docpp && (srcsuf != 'i')) {
                var_s1 = passin;
            } else {
                addstr(&execlist, passin);
                var_s1 = NULL;
            }

            retcode = run(ccom, execlist.entries, var_s1, passout, errout);
            if (retcode == 0xFF) {
                c_inline = TRUE;
                addstr(&umergeflags, "-c_inline");
            } else if (retcode != 0) {
                if (editflag != EDIT_FLAG_0) {
                    if (times_edited < edit_cnt_max) {
                        times_edited++;
                        if (edit_src(editor, srcfiles.entries[i], 1) != 0) {
                            show_err(errout);
                            exit(1);
                        }
                        if (docpp && (srcsuf != 'i')) {
                            unlink(passin);
                        }
                        unlink(passout);
                        unlink(errout);
                        unlink(symtab);
                        passin = srcfiles.entries[i];
                        goto repeat_after_edit;
                    }
                    show_err(errout);
                }
                runerror++;

                if (!Kflag && docpp && (srcsuf != 'i')) {
                    unlink(passin);
                }

                if (!Kflag) {
                    unlink(passout);
                    unlink(symtab);
                }
                continue;
            }

            if (editflag != EDIT_FLAG_0) {
                unlink(errout);
            }

            if (!Kflag && docpp && (srcsuf != 'i')) {
                unlink(passin);
            }
            passin = passout;

            if ((Hchar == 'f') && ucodeflag) {
                execlist.length = 0;
                addstr(&execlist, "btou");
                addstr(&execlist, passin);
                passout = mksuf(srcfiles.entries[i], 'U');
                if (regular_not_writeable(passout) == 1) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
                addstr(&execlist, passout);
                if (run(btou, execlist.entries, NULL, NULL, NULL) != 0) {
                    runerror++;
                    if (!Kflag) {
                        unlink(passin);
                        unlink(passout);
                    }
                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                } else if (!Kflag) {
                    unlink(passin);
                }
                continue;
            }
            if (Hchar == 'f') {
                continue;
            }
            if (((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) &&
                (Eflag || nocode || nocompileneeded)) {
                continue;
            }
            goto phase_ujoin;
        }

    phase_upas:
        {
            execlist.length = 0;
            addstr(&execlist, "upas");
            if (vflag) {
                addstr(&execlist, "-v");
            }
            addstr(&execlist, "-G");
            addstr(&execlist, Gnum);
            addlist(&execlist, &upasflags);
            addstr(&execlist, passin);
            if (((Hchar == 'f') && !ucodeflag) || Kflag) {
                passout = mksuf(srcfiles.entries[i], 'B');
                if (regular_not_writeable(passout) == 1) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
            } else {
                passout = tempstr[3];
            }
            addstr(&execlist, passout);
            addstr(&execlist, "-t");
            addstr(&execlist, symtab);
            if (run(upas, execlist.entries, NULL, NULL, errout) != 0) {
                if (editflag != EDIT_FLAG_0) {
                    if (times_edited < edit_cnt_max) {
                        times_edited++;
                        if (edit_src(editor, srcfiles.entries[i], 2) != 0) {
                            show_err(errout);
                            exit(1);
                        }
                        if ((stdflag == 0) && docpp && (srcsuf != 'i') && !Kflag) {
                            unlink(passin);
                        }
                        unlink(passout);
                        unlink(errout);
                        unlink(symtab);
                        passin = srcfiles.entries[i];
                        goto repeat_after_edit;
                    }
                    show_err(errout);
                }
                runerror++;

                if ((stdflag == 0) && docpp && (srcsuf != 'i') && !Kflag) {
                    unlink(passin);
                }

                if (!Kflag) {
                    unlink(passout);
                    unlink(symtab);
                }
                continue;
            }

            if (editflag != EDIT_FLAG_0) {
                unlink(errout);
            }

            if ((stdflag == 0) && docpp && (srcsuf != 'i') && !Kflag) {
                unlink(passin);
            }
            passin = passout;

            if ((Hchar == 'f') && ucodeflag) {
                execlist.length = 0;
                addstr(&execlist, "btou");
                addstr(&execlist, passin);
                passout = mksuf(srcfiles.entries[i], 'U');
                if (regular_not_writeable(passout) == 1) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
                addstr(&execlist, passout);
                if (run(btou, execlist.entries, NULL, NULL, NULL) != 0) {
                    runerror++;
                    if (!Kflag) {
                        unlink(passin);
                        unlink(passout);
                    }
                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                } else if (!Kflag) {
                    unlink(passin);
                }
                continue;
            }
            if (Hchar == 'f') {
                continue;
            }

            goto phase_ujoin;
        }

    phase_upl1:
        {
            execlist.length = 0;
            addstr(&execlist, "pl1fe");
            if (vflag) {
                addstr(&execlist, "-v");
            }
            addlist(&execlist, &upl1flags);
            addstr(&execlist, passin);

            if ((Hchar == 'f') || Kflag) {
                passout = mksuf(srcfiles.entries[i], SUF_3);
                lpi_st = mksuf(srcfiles.entries[i], SUF_4);
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
                if (editflag != EDIT_FLAG_0) {
                    if (times_edited < edit_cnt_max) {
                        times_edited++;
                        if (edit_src(editor, srcfiles.entries[i], 5) != 0) {
                            show_err(errout);
                            exit(1);
                        }
                        if (docpp && (srcsuf != 'i')) {
                            unlink(passin);
                        }
                        unlink(passout);
                        unlink(errout);
                        unlink(lpi_st);
                        unlink(lpi_p1);
                        passin = srcfiles.entries[i];
                        goto repeat_after_edit;
                    }
                    show_err(errout);
                }

                runerror++;

                if (docpp && (srcsuf != 'i')) {
                    unlink(passin);
                }
                if (!Kflag) {
                    unlink(passout);
                    unlink(lpi_st);
                }
                unlink(lpi_p1);
                continue;
            }

            if (editflag != EDIT_FLAG_0) {
                unlink(errout);
            }
            unlink(lpi_p1);
            if (docpp && (srcsuf != 'i')) {
                unlink(passin);
            }
            if (Hchar == 'f') {
                continue;
            }
            passin = passout;
        }

    phase_ulpi:
        {
            execlist.length = 0;
            addstr(&execlist, "ulpi");
            if (vflag) {
                addstr(&execlist, "-v");
            }
            addlist(&execlist, &ulpiflags);
            addstr(&execlist, passin);

            if (((Hchar == 'k') && !ucodeflag) || Kflag) {
                passout = mksuf(srcfiles.entries[i], 'B');
            } else {
                passout = tempstr[3];
            }

            if ((srcsuf == SUF_3) || Kflag) {
                lpi_st = mksuf(srcfiles.entries[i], SUF_4);
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
                runerror++;
                if (srcsuf != 3) {
                    unlink(passin);
                }
                if (!Kflag) {
                    unlink(passout);
                    if (srcsuf != 3) {
                        unlink(lpi_st);
                    }
                }
                if (tmpst != 0) {
                    unlink(symtab);
                }
                continue;
            }

            if ((srcsuf != 3) && !Kflag) {
                unlink(passin);
            }
            if (!Kflag && (srcsuf != 3)) {
                unlink(lpi_st);
            }

            passin = passout;

            if ((Hchar == 'k') && ucodeflag) {
                execlist.length = 0;
                addstr(&execlist, "btou");
                addstr(&execlist, passin);
                passout = mksuf(srcfiles.entries[i], 'U');
                addstr(&execlist, passout);
                if (run(btou, execlist.entries, NULL, NULL, NULL) != 0) {
                    runerror++;
                    if (!Kflag) {
                        unlink(passin);
                        unlink(passout);
                    }
                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                } else if (!Kflag) {
                    unlink(passin);
                }
                continue;
            }
            if (Hchar == 'k') {
                continue;
            }

            goto phase_ujoin;
        }

    phase_ucob:
        {
            execlist.length = 0;
            addstr(&execlist, "cobfe");
            if (vflag) {
                addstr(&execlist, "-v");
            }
            addlist(&execlist, &ucobflags);
            addstr(&execlist, passin);

            if ((Hchar == 'f') || Kflag) {
                passout = mksuf(srcfiles.entries[i], SUF_3);
                lpi_st = mksuf(srcfiles.entries[i], SUF_4);
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
                if (editflag != EDIT_FLAG_0) {
                    if (times_edited < edit_cnt_max) {
                        times_edited++;
                        if (edit_src(editor, srcfiles.entries[i], 6) != 0) {
                            show_err(errout);
                            exit(1);
                        }
                        if (docpp && (srcsuf != 'i')) {
                            unlink(passin);
                        }
                        unlink(passout);
                        unlink(errout);
                        unlink(lpi_st);
                        unlink(lpi_p1);
                        unlink(lpi_pd);
                        unlink(lpi_dd);
                        passin = srcfiles.entries[i];
                        goto repeat_after_edit;
                    }
                    show_err(errout);
                }

                runerror++;

                if (docpp && (srcsuf != 'i')) {
                    unlink(passin);
                }
                if (!Kflag) {
                    unlink(passout);
                    unlink(lpi_st);
                }
                unlink(lpi_p1);
                unlink(lpi_pd);
                unlink(lpi_dd);
                continue;
            }

            if (editflag != EDIT_FLAG_0) {
                unlink(errout);
            }
            if (docpp && (srcsuf != 'i')) {
                unlink(passin);
            }
            unlink(lpi_p1);
            unlink(lpi_pd);
            unlink(lpi_dd);
            if (Hchar == 'f') {
                continue;
            }

            passin = passout;
            goto phase_ulpi;
        }

    phase_m4:
        if (mflag) {
            execlist.length = 0;
            addstr(&execlist, "m4");
            addstr(&execlist, passin);

            if ((compiler == COMPILER_4) || (srcsuf == 's')) {
                passout = tempstr[14];
            } else {
                passout = mksuf(srcfiles.entries[i], 'p');
            }
            if (run(m4, execlist.entries, NULL, passout, NULL) != 0) {
                runerror++;
                if (!Kflag) {
                    unlink(passout);
                }
                continue;
            }

            passin = passout;
        }

        switch (srcsuf) {
            case 's':
                if (docpp || default_nocpp) {
                    goto block_531;
                }
                goto phase_as0;

            case 'e':
            default:
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "efl not supported. Cannot use .e files\n");
                exit(2);
                // not actually fallthrough due to exit being noreturn
            case 'r':
                execlist.length = 0;
                addstr(&execlist, "ratfor");
                addlist(&execlist, &ratforflags);
                addstr(&execlist, passin);
                passout = mksuf(srcfiles.entries[i], 'f');
                if (run(ratfor, execlist.entries, NULL, passout, NULL) != 0) {
                    runerror++;
                    if (!Kflag) {}
                    continue;
                }
                if (mflag) {
                    unlink(passin);
                }
                passin = passout;

                if (Fflag) {
                    continue;
                }
                if (docpp) {
                    goto block_531;
                }
                break;
        }

    phase_fopt:
        {
            sp100 = 0;
            spFC = 0;
            spF0[0] = '1';
            spF0[1] = '\0';

            if (run_sopt) {
                if (mp_flag & 1) {
                    error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "-sopt and -pfa both specified; -sopt ignored.\n");
                    goto phase_pfa;
                }

                if ((Oflag >= 2) && !set_loop_unroll) {
                    addstr(&optflags, "-loopunroll");
                    addstr(&optflags, "0");
                }

                if (mp_i2flag && (w1flag != 2)) {
                    error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "fopt does not recognize the -i2 option\n");
                }
                if (mp_66flag && (w1flag != 2)) {
                    error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "fopt does not recognize the -66 option\n");
                }
                if (mp_uflag && (w1flag != 2)) {
                    error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "fopt does not recognize the -u option\n");
                }
                if (mp_backslashflag && (w1flag != 2)) {
                    error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "fopt does not support the -backslash option\n");
                }
                if (mp_caseflag) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "fopt does not support the -U option\n");
                    exit(2);
                }

                execlist.length = 0;
                addstr(&execlist, "fopt");
                spF4 = mkstr(tempstr[31], "l", NULL);
                addstr(&execlist, mkstr("-L=", spF4, NULL));

                if ((Hchar == 'K') || Kflag) {
                    passout = mksuf(srcfiles.entries[i], 'm');
                } else {
                    passout = mkstr(tempstr[31], "m", &spF0, NULL);
                }

                addstr(&execlist, mkstr("-F=", passout, NULL));
                addstr(&execlist, mkstr("-I=", passin, NULL));
                if (mp_col120flag) {
                    addstr(&execlist, "-scan=120");
                }
                if (mp_extendflag) {
                    addstr(&execlist, "-scan=132");
                }
                if (!automaticflag) {
                    addstr(&execlist, "-save=all");
                }
                if (mp_onetripflag) {
                    addstr(&execlist, "-onetrip");
                }
                if (mp_dlinesflag) {
                    addstr(&execlist, "-dlines");
                }
                if (w1flag == 2) {
                    addstr(&execlist, "-suppress=w");
                }
                if (vflag) {
                    addstr(&execlist, "-lo=lno");
                }
                if (irix4) {
                    addstr(&execlist, mkstr("-customer=", mksuf(srcfiles.entries[i], srcsuf), NULL));
                } else {
                    addstr(&execlist, mkstr("-original_filename=", mksuf(srcfiles.entries[i], srcsuf), NULL));
                }
                //! @bug addstr called with extra argument
                addstr(&execlist, "-include=/usr/include", 0);
                addstr(&execlist, "-cp=i");
                addlist(&execlist, &soptflags);
                if (run(fopt, execlist.entries, NULL, NULL, NULL) != 0) {
                    runerror++;
                    if ((docpp || (srcsuf == 'e') || (srcsuf == 'r')) && (srcsuf != 'i') && !Kflag) {
                        unlink(passin);
                    }
                    if ((Hchar != 'K') || Kflag) {
                        unlink(passout);
                    }
                    unlink(spF4);
                    continue;
                }
                if ((docpp || (srcsuf == 'e') || (srcsuf == 'r') || (srcsuf == 'F')) && (srcsuf != 'i') && !Kflag) {
                    unlink(passin);
                }
                unlink(spF4);

                passin = passout;

                if (Hchar == 'K') {
                    continue;
                }
                goto phase_fcom;
            }
        }

    phase_pfa:
        {
            if ((Hchar == 'K') || Kflag) {
                mp_flag |= 6;
            }
            if (mp_flag & 1) {
                if ((Oflag >= 2) && !set_loop_unroll) {
                    addstr(&optflags, "-loopunroll");
                    addstr(&optflags, "0");
                }

                if (mp_i2flag && (w1flag != 2)) {
                    error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "PFA does not recognize the -i2 option\n");
                }
                if (mp_66flag && (w1flag != 2)) {
                    error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "PFA does not recognize the -66 option\n");
                }
                if (mp_uflag && (w1flag != 2)) {
                    error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "PFA does not recognize the -u option\n");
                }
                if (mp_backslashflag && (w1flag != 2)) {
                    error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "PFA does not support the -backslash option\n");
                }
                if (mp_caseflag) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "PFA does not support the -U option\n");
                    exit(2);
                }

            loop_pfa:
                {
                    execlist.length = 0;
                    addstr(&execlist, "pfa");
                    spF0[0] = (char)(spFC + '1');
                    if (mp_flag & 2) {
                        spF8 = mksuf(srcfiles.entries[i], 'l');
                        if (mp_prepass_count > spFC) {
                            spF8 = mkstr(spF8, spF0, NULL);
                        }
                    } else {
                        spF8 = mkstr(tempstr[31], "l", spF0, NULL);
                    }
                    addstr(&execlist, mkstr("-L=", spF8, NULL));

                    if (mp_flag & 4) {
                        passout = mksuf(srcfiles.entries[i], 'm');
                        if (mp_prepass_count > spFC) {
                            passout = mkstr(passout, spF0, NULL);
                        }
                    } else {
                        passout = mkstr(tempstr[31], "m", spF0, NULL);
                    }

                    addstr(&execlist, mkstr("-F=", passout, NULL));
                    addstr(&execlist, mkstr("-I=", passin, NULL));
                    if (mp_col120flag) {
                        addstr(&execlist, "-scan=120");
                    }
                    if (mp_extendflag) {
                        addstr(&execlist, "-scan=132");
                    }
                    if (!automaticflag) {
                        addstr(&execlist, "-save=all");
                    }
                    if (mp_onetripflag) {
                        addstr(&execlist, "-onetrip");
                    }
                    if (mp_dlinesflag) {
                        addstr(&execlist, "-dlines");
                    }
                    if (w1flag == 2) {
                        addstr(&execlist, "-suppress=w");
                    }
                    if (vflag) {
                        addstr(&execlist, "-lo=lno");
                    } else {
                        addstr(&execlist, "-lo=lo");
                    }
                    if (mp_flag & 2) {
                        addstr(&execlist, mkstr("-analysis=", mksuf(srcfiles.entries[i], SUF_5), NULL));
                    } else if (!irix4) {
                        addstr(&execlist, "-noanalysis");
                    }
                    if (irix4) {
                        addstr(&execlist, mkstr("-customer=", mksuf(srcfiles.entries[i], srcsuf), NULL));
                    } else {
                        addstr(&execlist, mkstr("-original_filename=", mksuf(srcfiles.entries[i], srcsuf), NULL));
                    }
                    //! @bug addstr called with extra argument
                    addstr(&execlist, "-include=/usr/include", 0);
                    addstr(&execlist, "-cp=i");
                    if (mp_prepass_count <= spFC) {
                        addlist(&execlist, &pfaflags);
                    } else {
                        addstr(&execlist, "-p=1");
                        addstr(&execlist, "-ur=1");

                        sp100++;
                        while (strncmp(argv[sp100], "-pfaprepass,", 12) != 0) {
                            sp100++;
                            if (argv[sp100] == NULL) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "Can't parse -pfaprepass option\n");
                                exit(2);
                            }
                        }

                        spE8 = argv[sp100] + strlen("-pfaprepass");
                        while (TRUE) {
                            spEC = spE8 + 1;
                            if (*spEC == 0) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "Bad pfaprepass syntax: no arg after comma\n");
                                exit(2);
                            }
                            spE8 = spEC + 1;
                            while (*spE8 != ',' && *spE8 != '\0')
                                spE8++;
                            spE7 = spE8[0];
                            spE8[0] = 0;
                            addstr(&execlist, mkstr(spEC, NULL));
                            if (spE7 == 0)
                                break;
                            spE8[0] = spE7;
                        }
                    }
                    if (run(pfa, execlist.entries, NULL, NULL, NULL) != 0) {
                        runerror++;
                        if ((docpp || (srcsuf == 'e') || (srcsuf == 'r')) && (srcsuf != 'i') && !Kflag) {
                            unlink(passin);
                        }
                        if (!(mp_flag & 4)) {
                            unlink(passout);
                        }
                        continue;
                    }

                    if (!(mp_flag & 2)) {
                        unlink(spF8);
                    }
                    if (spFC == 0) {
                        if ((docpp || (srcsuf == 'e') || (srcsuf == 'r') || (srcsuf == 'F')) && (srcsuf != 'i') &&
                            !Kflag) {
                            unlink(passin);
                        }
                    } else if (!(mp_flag & 4)) {
                        unlink(passin);
                    }

                    spFC++;
                    if (mp_prepass_count >= spFC) {
                        passin = passout;
                        goto loop_pfa;
                    }
                    passin = passout;

                    if (Hchar == 'K') {
                        continue;
                    }
                }
            }
        }

    phase_fcom:
        {
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
            if (showdirt_flag) {
                addstr(&execlist, "-showdirt");
            }
            if (vflag) {
                addstr(&execlist, "-v");
            }
            addlist(&execlist, &fcomflags);
            if (!nocode) {
                addstr(&execlist, mkstr("-XS", symtab, NULL));
            }

            var_s2 = NULL;
            if (nocode) {
                addstr(&execlist, "-nocode");
                passout = NULL;
            } else if (Hchar == 'f') {
                passout = mksuf(srcfiles.entries[i], 'B');
                if (ucodeflag) {
                    addstr(&execlist, "-Xu");
                    var_s2 = mksuf(srcfiles.entries[i], 'U');
                }
            } else if (Kflag) {
                passout = mksuf(srcfiles.entries[i], 'B');
                if (regular_not_writeable(passout) == 1) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
            } else {
                passout = tempstr[3];
            }
            if (passout != NULL) {
                addstr(&execlist, "-t");
                addstr(&execlist, passout);
            }

            if (docpp && (srcsuf != 'i') && (srcsuf != 'm')) {
                var_s1 = passin;
            } else {
                addstr(&execlist, passin);
                var_s1 = NULL;
            }
            if (run(fcom, execlist.entries, var_s1, var_s2, errout) != 0) {
                if (editflag != EDIT_FLAG_0) {
                    if (times_edited < edit_cnt_max) {
                        times_edited++;
                        if (edit_src(editor, srcfiles.entries[i], 3) != 0) {
                            show_err(errout);
                            exit(1);
                        }
                        if ((docpp || (srcsuf == 'e') || (srcsuf == 'r')) && (srcsuf != 'i') && (srcsuf != 'f')) {
                            unlink(passin);
                        }
                        unlink(passout);
                        unlink(errout);
                        unlink(symtab);

                        passin = srcfiles.entries[i];

                        goto repeat_after_edit;
                    }
                    show_err(errout);
                }

                runerror++;

                if ((docpp || (mp_flag & 1) || (srcsuf == 'e') || (srcsuf == 'r')) && (srcsuf != 'i') &&
                    (srcsuf != 'm') && !Kflag && !(mp_flag & 4)) {
                    unlink(passin);
                }
                if (!Kflag) {
                    unlink(passout);
                    unlink(symtab);
                }
                continue;
            }

            if (editflag != EDIT_FLAG_0) {
                unlink(errout);
            }
            if (nocode) {
                if (docpp) {
                    unlink(passin);
                }
                continue;
            }

            if ((docpp || (mp_flag & 1) || run_sopt || (srcsuf == 'e') || (srcsuf == 'r') || (srcsuf == 'F')) &&
                (srcsuf != 'i') && (srcsuf != 'm') && !Kflag && !(mp_flag & 4)) {
                unlink(passin);
            }

            passin = passout;

            if (Hchar == 'f') {
                continue;
            }
        }

    phase_ujoin:
        {
            if ((Oflag != 3) && (Oflag != 4) && !jflag) {
                if (!c_inline) {
                    goto phase_uloop;
                } else {
                    goto phase_umerge;
                }
            }

            execlist.length = 0;
            addstr(&execlist, "ujoin");
            if (vflag) {
                addstr(&execlist, "-v");
            }
            addlist(&execlist, &ujoinflags);

            if ((outfile != NULL) && jflag && (srcfiles.length == 1)) {
                passout = outfile;
            } else {
                passout = mksuf(srcfiles.entries[i], 'u');
            }

            addstr(&execlist, "-o");
            addstr(&execlist, passout);
            addstr(&execlist, passin);
            addstr(&execlist, symtab);
            if (run(ujoin, execlist.entries, NULL, NULL, NULL) != 0) {
                runerror++;
                if (!Kflag) {
                    if (srcsuf != 'B') {
                        unlink(passin);
                    }
                    unlink(passout);
                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                }
                continue;
            }
            if (!cflag || (Oflag == 3) || (Oflag == 4)) {
                if (!Kflag) {
                    if (srcsuf != 'B') {
                        unlink(passin);
                    }
                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                }
                passin = passout;
                continue;
            }
            goto phase_uloop;
        }

    phase_uld:
        {
            if (non_shared && !non_shared_emitted) {
                addstr(&ldflags, "-non_shared");
                non_shared_emitted = TRUE;
            }

            execlist.length = 0;
            addstr(&execlist, "uld");
            if (mips2flag && (sp148 == 0)) {
                if (strcmp("/", comp_target_root) != 0) {
                    if (non_shared) {
                        addstr(&execlist,
                               mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "nonshared", NULL));
                    } else {
                        addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "", NULL));
                    }
                } else {
                    if (non_shared) {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "nonshared", NULL));
                    } else {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "", NULL));
                    }
                }
            }
            if (mips1flag && (sp148 == 0)) {
                if (strcmp("/", comp_target_root) != 0) {
                    if (non_shared) {
                        addstr(&execlist,
                               mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "nonshared", NULL));
                    } else {
                        addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "", NULL));
                    }
                } else {
                    if (non_shared) {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "nonshared", NULL));
                    } else {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "", NULL));
                    }
                }
            }
            if ((fiveflag || (strcmp("/", comp_target_root) != 0)) && !Lflag && (strcmp("/", comp_target_root) != 0)) {
                if (non_shared) {
                    addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/nonshared/", currcomp, NULL));
                } else {
                    addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, NULL));
                }
            }
            if (svr4_systype) {
                if (compchoice == COMP_CHOICE_1) {
                    addstr(&execlist, mkstr("-SYSTYPE_SVR4", NULL, NULL));
                }
                addstr(&execlist, mkstr("-_SYSTYPE_SVR4", NULL, NULL));
                if (call_shared) {
                    addstr(&execlist, "-require_dynamic_link");
                    addstr(&execlist, "_rld_new_interface");
                }
            }
            if ((allBstring != NULL) && (*allBstring != '\0')) {
                addstr(&execlist, mkstr("-kB", allBstring, NULL));
            }
            addlist(&execlist, &uldflags);
            addlist(&execlist, &ldflags);
            if (irix4) {
                addstr(&execlist, mkstr("-L", NULL));
                if (non_shared) {
                    addstr(&execlist, mkstr("-L", "/usr/irix4/", "usr/lib/nonshared/", NULL));
                    crtx = mkstr(comp_host_root, "usr/lib/nonshared/", CRTX, NULL);
                    crtn = mkstr(comp_host_root, "usr/lib/nonshared/", "crtn.o", NULL);
                } else {
                    addstr(&execlist, mkstr("-L", "/usr/irix4/", "usr/lib/", NULL));
                    crtx = mkstr(comp_host_root, "usr/lib/", CRTX, NULL);
                    crtn = mkstr(comp_host_root, "usr/lib/", "crtn.o", NULL);
                }
            }
            if (!cflag) {
                addstr(&execlist, crtx);
            } else {
                addstr(&execlist, "-no_AutoGnum");
                if (!force_rm_dead_code) {
                    addstr(&execlist, "-preserve_dead_code");
                }
            }
            adduldlist(&execlist, &ufiles, &objfiles);
            if (!cflag) {
                addlist(&execlist, &uldlibflags);
                if ((compiler == COMPILER_2) || haspascal) {
                    addspacedstr(&execlist, newstr(libp));
                    addspacedstr(&execlist, newstr(libxmalloc));
                    addspacedstr(&execlist, newstr(libexc));
                    addspacedstr(&execlist, newstr(libmld));
                    if ((default_call_shared || call_shared) && (systype != NULL) && (strcmp(systype, "svr3") == 0)) {
                        addspacedstr(&execlist, "-lbsd");
                    }
                }
                if ((compiler == COMPILER_3) || hasfortran) {
                    if (mp_flag) {
                        addstr(&execlist, libI77_mp);
                    }
                    if (non_shared || irix4) {
                        addspacedstr(&execlist, newstr(libF77));
                    } else {
                        addspacedstr(&execlist, libftn);
                    }
                    if (non_shared || irix4) {
                        addspacedstr(&execlist, newstr(libI77));
                    }
                    if (non_shared || irix4) {
                        addspacedstr(&execlist, newstr(libU77));
                    }
                    if (non_shared || irix4) {
                        addspacedstr(&execlist, newstr(libisam));
                    }
                }
                if (compiler == COMPILER_5) {
                    addstr(&execlist, libpl1);
                    addstr(&execlist, libxmalloc);
                    addstr(&execlist, "-ltermcap");
                    addstr(&execlist, libexc);
                    addstr(&execlist, libmld);
                }
                if (((compiler == COMPILER_2) || (compiler == COMPILER_3) || haspascal || hasfortran || haspl1 ||
                     (compiler == COMPILER_5) || (compiler == COMPILER_6)) &&
                    (nonshared != 0)) {
                    addspacedstr(&execlist, newstr(libm));
                }
                if (pgflag != 0) {
                    addspacedstr(&execlist, newstr(libgprof));
                } else if (pflag != 0) {
                    addspacedstr(&execlist, newstr(libprof));
                }
                if (cmp_flag & 0x10000) {
                    addstr(&execlist, libc_mp);
                    if (compiler == COMPILER_1) {
                        addstr(&execlist, "-lkapio");
                    }
                }
                if (run_sopt && (compiler == COMPILER_1)) {
                    addstr(&execlist, "-lkapio");
                }
                if (compiler == COMPILER_3) {
                    if (D_1000C130 == 2) {
                        addstr(&execlist, "-lc_s");
                        if (xpg_flag) {
                            addstr(&execlist, "-dont_warn_unused");
                            addstr(&execlist, "-lgen");
                            addstr(&execlist, "-warn_unused");
                        }
                        addstr(&execlist, "-lc");
                    } else {
                        if (irix4 && (B_1000ED74 == 0)) {
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

                if (!sixty4bitflag) {
                    ldw_file = fopen(libdw_path, "r");
                    if (ldw_file != NULL) {
                        addspacedstr(&execlist, newstr(libdw));
                    }
                }

                if (xpg_flag) {
                    addstr(&execlist, "-dont_warn_unused");
                    addstr(&execlist, "-lgen");
                    addstr(&execlist, "-warn_unused");
                }
                addstr(&execlist, "-lc");
                if (libm_spec) {
                    addstr(&execlist, "-lm");
                }
                if (libfastm_spec) {
                    addstr(&execlist, "-lfastm");
                }
            }
            if (!cflag && crtn_required) {
                addstr(&execlist, crtn);
            }
            if (rls_id_object != NULL) {
                addstr(&execlist, rls_id_object);
            }
            addstr(&execlist, "-ko");

            if (uoutfile != NULL) {
                passout = uoutfile;
            } else if ((Hchar == 'u') || Kflag) {
                passout = mksuf(srcfiles.entries[i], 'u');
            } else {
                passout = tempstr[4];
            }
            addstr(&execlist, passout);
            if (run(uld, execlist.entries, NULL, NULL, NULL) != 0) {
                runerror++;
                if (!Kflag) {
                    unlink(passout);
                }
                continue;
            }

            passin = passout;

            if ((ufiles.length == 1) && (srcfiles.length == 2) && ((Oflag == 3) || (Oflag == 4))) {
                unlink(ufiles.entries[0]);
            }
            if (Hchar == 'u') {
                continue;
            }
        }

    phase_usplit:
        {
            execlist.length = 0;
            addstr(&execlist, "usplit");
            if (vflag) {
                addstr(&execlist, "-v");
            }
            addlist(&execlist, &usplitflags);

            if ((Hchar == 's') || Kflag) {
                passout = mksuf(srcfiles.entries[i], 'S');
                if (regular_not_writeable(passout) == 1) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
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
                runerror++;
                if (!Kflag) {
                    unlink(passin);
                    unlink(passout);
                }
                if (tmpst != 0) {
                    unlink(symtab);
                }
                continue;
            }

            if (!Kflag && (srcsuf != 'u') && (uoutfile == NULL)) {
                unlink(passin);
            }

            passin = passout;

            if (Hchar == 's') {
                continue;
            }
        }

    phase_umerge:
        if ((Oflag == 3) || (Oflag == 4) || c_inline) {
            execlist.length = 0;
            addstr(&execlist, "umerge");
            if (vflag) {
                addstr(&execlist, "-v");
            }
            addlist(&execlist, &umergeflags);
            addstr(&execlist, passin);
            addstr(&execlist, "-o");

            if ((Hchar == 'm') || Kflag) {
                passout = mksuf(srcfiles.entries[i], 'M');
                if (regular_not_writeable(passout) == 1) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
            } else {
                passout = tempstr[6];
            }

            addstr(&execlist, passout);
            addstr(&execlist, "-t");
            addstr(&execlist, symtab);
            if (run(umerge, execlist.entries, NULL, NULL, NULL) != 0) {
                runerror++;

                if (!Kflag) {
                    if (srcsuf != 'S') {
                        unlink(passin);
                    }
                    unlink(passout);
                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                }
                continue;
            }

            if (!Kflag && (srcsuf != 'S')) {
                unlink(passin);
            }

            passin = passout;

            if (Hchar == 'm') {
                continue;
            }
        }

    phase_uloop:
        if (unrollflag) {
            execlist.length = 0;
            addstr(&execlist, "uloop");
            if (vflag) {
                addstr(&execlist, "-v");
            }
            addlist(&execlist, &uloopflags);
            addstr(&execlist, passin);
            addstr(&execlist, "-o");

            if ((Hchar == 'v') || Kflag) {
                if ((Hchar == 'v') || Kflag) {
                    passout = mksuf(srcfiles.entries[i], 'V');
                    if (regular_not_writeable(passout) == 1) {
                        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n",
                              passout);
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
                runerror++;
                if (!Kflag) {
                    if (srcsuf != 'M') {
                        unlink(passin);
                    }
                    unlink(passout);
                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                }
                continue;
            }

            if (!Kflag && (srcsuf != 'M')) {
                unlink(passin);
            }
            passin = passout;

            if (Hchar == 'v') {
                continue;
            }
        }

    phase_uopt0:
        if ((uopt0flag == TRUE) && (compiler == COMPILER_3) && (Oflag >= 2)) {
            execlist.length = 0;
            addstr(&execlist, "uopt0");
            if (vflag) {
                addstr(&execlist, "-v");
            }
            addstr(&execlist, "-G");
            addstr(&execlist, Gnum);
            addlist(&execlist, &uopt0flags);
            addstr(&execlist, passin);

            if ((Hchar == 'q') || Kflag) {
                passout = mksuf(srcfiles.entries[i], 'Q');
                if (regular_not_writeable(passout) == 1) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
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
                runerror++;
                if (!Kflag) {
                    if ((srcsuf != 'M') && (srcsuf != 'B') && (srcsuf != 'S') && (srcsuf != 'Q')) {
                        unlink(passin);
                    }
                    unlink(passout);
                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                }
                unlink(uopt0str);
                continue;
            }

            if (!Kflag && (srcsuf != 'M') && (srcsuf != 'B') && (srcsuf != 'S') && (srcsuf != 'Q')) {
                unlink(passin);
            }
            unlink(uopt0str);

            passin = passout;

            if (Hchar == 'q') {
                continue;
            }
        }

    phase_ddopt:
        if ((ddoptflag == TRUE) && (compiler == COMPILER_3) && (Oflag >= 2)) {
            execlist.length = 0;
            addstr(&execlist, "ddopt");
            if (vflag) {
                addstr(&execlist, "-v");
            }
            addstr(&execlist, "-G");
            addstr(&execlist, Gnum);
            addlist(&execlist, &ddoptflags);
            addstr(&execlist, passin);

            if (((Hchar == 'd') && !ucodeflag) || Kflag) {
                passout = mksuf(srcfiles.entries[i], 'D');
                if (regular_not_writeable(passout) == 1) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
            } else {
                passout = tempstr[27];
            }

            if (ddoptinfo) {
                addstr(&execlist, "-e");
                if (((Hchar == 'd') && !ucodeflag) || Kflag) {
                    addstr(&execlist, mksuf(srcfiles.entries[i], 'E'));
                } else {
                    addstr(&execlist, tempstr[26]);
                }
            }
            addstr(&execlist, passout);
            if (run(ddopt, execlist.entries, NULL, NULL, NULL) != 0) {
                runerror++;
                if (!Kflag) {
                    if ((srcsuf != 'B') && (srcsuf != 'S') && (srcsuf != 'M') && (srcsuf != 'Q')) {
                        unlink(passin);
                    }
                    unlink(passout);
                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                }
                unlink(ddoptstr);
                continue;
            }

            if (!Kflag && (srcsuf != 'B') && (srcsuf != 'S') && (srcsuf != 'M') && (srcsuf != 'Q')) {
                unlink(passin);
            }
            unlink(ddoptstr);

            passin = passout;

            if (Hchar == 'd') {
                continue;
            }
        }

    phase_uopt:
        if ((Oflag == 2) || (Oflag == 3) || (Oflag == 4)) {
            execlist.length = 0;
            addstr(&execlist, "uopt");
            if (vflag) {
                addstr(&execlist, "-v");
            }
            addstr(&execlist, "-G");
            addstr(&execlist, Gnum);
            if ((mp_flag & 0x10000) && ((srcsuf == 'f') || (srcsuf == 'F'))) {
                addstr(&execlist, "-noPalias");
            }
            if (!irix4) {
                if (kpicopt_flag) {
                    addstr(&execlist, "-kpicopt");
                }
                if (nokpicopt_flag) {
                    addstr(&execlist, "-nokpicopt");
                }
            }
            addlist(&execlist, &optflags);
            addstr(&execlist, passin);

            if (((Hchar == 'o') && !ucodeflag) || Kflag) {
                passout = mksuf(srcfiles.entries[i], 'O');
                if (regular_not_writeable(passout) == 1) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
                if (NoMoreOptions) {
                    *passout = '-';
                    if (*passout != '\0') {
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
                runerror++;
                if (!Kflag) {
                    if ((srcsuf != 'B') && (srcsuf != 'S') && (srcsuf != 'Q') && (srcsuf != 'D') && (srcsuf != 'M') &&
                        (srcsuf != 'V')) {
                        unlink(passin);
                    }
                    unlink(passout);
                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                }
                unlink(optstr);
                continue;
            }

            if (!Kflag && (srcsuf != 'B') && (srcsuf != 'S') && (srcsuf != 'Q') && (srcsuf != 'D') && (srcsuf != 'M') &&
                (srcsuf != 'V')) {
                unlink(passin);
            }
            unlink(optstr);

            passin = passout;

            if ((Hchar == 'o') && ucodeflag) {
                execlist.length = 0;
                addstr(&execlist, "btou");
                addstr(&execlist, passin);
                passout = mksuf(srcfiles.entries[i], 'U');
                addstr(&execlist, passout);
                if (run(btou, execlist.entries, NULL, NULL, NULL) != 0) {
                    runerror++;
                    if (!Kflag) {
                        unlink(passin);
                        unlink(passout);
                        if (tmpst != 0) {
                            unlink(symtab);
                        }
                    }
                    continue;
                }
                if (!Kflag) {
                    unlink(passin);
                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                }
                continue;
            }
            if (Hchar == 'o') {
                continue;
            }
        }

    phase_ugen:
        {
            execlist.length = 0;
            addstr(&execlist, "ugen");
            if (vflag) {
                addstr(&execlist, "-v");
            }
            addstr(&execlist, "-G");
            addstr(&execlist, Gnum);
            if (kpic_flag && !coff_spec && !irix4) {
                if (Oflag >= 3) {
                    addstr(&execlist, "-pic1");
                } else {
                    addstr(&execlist, "-pic2");
                }
            }
            addlist(&execlist, &genflags);
            addstr(&execlist, passin);
            if (Sflag) {
                addstr(&execlist, "-o");
                if (Kflag) {
                    addstr(&execlist, mksuf(srcfiles.entries[i], 'G'));
                } else {
                    binasm = tempstr[9];
                    addstr(&execlist, binasm);
                }
                addstr(&execlist, "-l");
                passout = mksuf(srcfiles.entries[i], 's');
                if (regular_not_writeable(passout) == 1) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
                addstr(&execlist, passout);
            } else if (Hchar == 'c') {
                addstr(&execlist, "-o");
                passout = mksuf(srcfiles.entries[i], 'G');
                if (regular_not_writeable(passout) == 1) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
                addstr(&execlist, passout);
            } else if (Kflag) {
                addstr(&execlist, "-o");
                passout = mksuf(srcfiles.entries[i], 'G');
                if (regular_not_writeable(passout) == 1) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
                addstr(&execlist, passout);
                if (regular_not_writeable(mksuf(srcfiles.entries[i], 's')) == 1) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n",
                          mksuf(srcfiles.entries[i], 's'));
                    exit(2);
                }
                addstr(&execlist, "-l");
                addstr(&execlist, mksuf(srcfiles.entries[i], 's'));
            } else {
                addstr(&execlist, "-o");
                passout = tempstr[10];
                if (regular_not_writeable(passout) == 1) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
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
                runerror++;
                if (!Kflag) {
                    if ((srcsuf != 'B') && (srcsuf != 'O') && (srcsuf != 'Q') && (srcsuf != 'D') && (srcsuf != 'M') &&
                        (srcsuf != 'S') && (srcsuf != 'V')) {
                        unlink(passin);
                    }
                    unlink(passout);
                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                } else if (Sflag) {
                    unlink(binasm);
                }
                unlink(gentmp);
                continue;
            }

            unlink(gentmp);
            if ((((srcsuf != 'B') && (srcsuf != 'S') && (srcsuf != 'Q') && (srcsuf != 'D') && (srcsuf != 'M') &&
                  (srcsuf != 'V')) ||
                 (Oflag >= 2)) &&
                (srcsuf != 'O') && !Kflag) {
                unlink(passin);
            }
            if (Sflag) {
                if (!Kflag) {
                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                    unlink(binasm);
                }
                continue;
            }

            if (Hchar == 'c') {
                continue;
            }
            passin = passout;
        }

    phase_as0:
        if (srcsuf == 's') {
            execlist.length = 0;
            addstr(&execlist, "as0");
            if (vflag) {
                addstr(&execlist, "-v");
            }
            addstr(&execlist, "-G");
            addstr(&execlist, Gnum);
            addlist(&execlist, &asflags);
            if (NoMoreOptions && (*passin == '-')) {
                passin = func_00433534(passin);
            }
            addstr(&execlist, passin);
            addstr(&execlist, "-o");

            if ((Hchar == 'a') || Kflag) {
                if ((compiler == COMPILER_4) && (getsuf(srcfiles.entries[i]) == 0)) {
                    passout = mkstr(srcfiles.entries[i], ".G", NULL);
                } else {
                    passout = mksuf(srcfiles.entries[i], 'G');
                }
                if (regular_not_writeable(passout) == 1) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
            } else {
                passout = tempstr[11];
                if (regular_not_writeable(passout) == 1) {
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't overwrite a write-protected file %s \n", passout);
                    exit(2);
                }
            }

            addstr(&execlist, passout);
            addstr(&execlist, "-t");
            addstr(&execlist, symtab);
            if (run(as0, execlist.entries, NULL, NULL, NULL) != 0) {
                runerror++;
                if (docpp || mflag) {
                    unlink(passin);
                }
                if (!Kflag) {
                    unlink(passout);
                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                }
                continue;
            }

            if (docpp || mflag) {
                unlink(passin);
            }

            if (Hchar == 'a') {
                continue;
            }

            passin = passout;
        }

    phase_as1:
        {
            execlist.length = 0;
            addstr(&execlist, "as1");
            addstr(&execlist, "-t5_ll_sc_bug");
            if (tfp_flag) {
                addstr(&execlist, "-tfp");
            }
            if (noaliasokflag) {
                addstr(&execlist, "-noaliasok");
            }
            if (alignarg != NULL) {
                addstr(&execlist, alignarg);
            }
            if (align_common > 0) {
                addstr(&execlist, "-align_common");
            }
            //! @note `as1` does not generate PIC by default, -KPIC must be passed explicitly or an assembler directive
            //! used
            //! (.pic0 for not PIC, .pic2 for PIC)
            if (((compiler == COMPILER_4) || (srcsuf == 's')) && !kpic_spec && !irix4) {
                addstr(&execlist, "-pic0");
            }
            if (coff_spec) {
                addstr(&execlist, "-coff");
                kpic_flag = FALSE;
            } else if (kpic_flag) {
                if (!irix4) {
                    if (!coff_spec) {
                        addstr(&execlist, "-elf");
                        if (Oflag >= 3) {
                            addstr(&execlist, "-pic1");
                        } else {
                            addstr(&execlist, "-pic2");
                        }
                    } else {
                        addstr(&execlist, "-coff");
                        kpic_flag = FALSE;
                    }
                }
            } else if (!irix4) {
                if (coff_spec) {
                    addstr(&execlist, "-coff");
                } else {
                    addstr(&execlist, "-elf");
                }
            }
            if (vflag) {
                addstr(&execlist, "-v");
            }
            if (!fullasoptflag && (srcsuf == 's') && (Oflag >= 2)) {
                addstr(&execlist, "-noglobal");
            }
            addstr(&execlist, "-G");
            addstr(&execlist, Gnum);
            switch (pflag) {
                case 0:
                    addstr(&execlist, "-p0");
                    break;
                case 1:
                    addstr(&execlist, "-p1");
                    break;
            }
            addlist(&execlist, &asflags);
            addlist(&execlist, &as1flags);
            if (!irix4) {
                addlist(&execlist, &olimitflags);
            }

            if (NoMoreOptions && (*passin == '-')) {
                passin = func_00433534(passin);
            }
            addstr(&execlist, passin);
            addstr(&execlist, "-o");

            if (compiler == COMPILER_4) {
                if (outfile != NULL) {
                    passout = outfile;
                } else {
                    passout = "a.out";
                }
            } else if ((outfile != NULL) && cflag && ((Oflag == 3) || (srcfiles.length == 1))) {
                passout = outfile;
            } else {
                if ((srcsuf == '?') && (Hchar != 'b') && !Kflag) {
                    if (!cflag) {
                        tmp_uldobj = passout = tempstr[12];
                    } else if (srcfiles.length == 2) {
                        passout = mksuf(*srcfiles.entries, 'o');
                        tmp_uldobj = NULL;
                    } else {
                        passout = mksuf(srcfiles.entries[i], 'o');
                        tmp_uldobj = NULL;
                    }
                } else {
                    passout = mksuf(srcfiles.entries[i], 'o');
                }
                if (uldobj_place != -1) {
                    set_place(&objfiles, passout, uldobj_place);
                }
            }
            addstr(&execlist, passout);
            addstr(&execlist, "-t");
            addstr(&execlist, symtab);
            if ((ddoptflag == TRUE) && (compiler == COMPILER_3) && ddoptinfo && (Oflag >= 2)) {
                addstr(&execlist, "-e");
                if (((Hchar == 'b') && !ucodeflag) || Kflag) {
                    addstr(&execlist, mksuf(srcfiles.entries[i], 'E'));
                } else {
                    addstr(&execlist, tempstr[26]);
                }
            }
            if (regular_not_writeable(passout) != 0) {
                unlink(passout);
            }
            if (run(as1, execlist.entries, NULL, NULL, NULL) != 0) {
                runerror++;
                if (!Kflag) {
                    if (srcsuf != 'G') {
                        unlink(passin);
                    }
                    spE0 = regular_file(passout);
                    if (spE0 == 1) {
                        unlink(passout);
                    } else if (spE0 != 0) {
                        error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                              "%s does not exist or is not stat(2)-able. Not deleted (if it exists) even though as1 "
                              "failed.\n",
                              passout);
                    } else {
                        error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                              "%s is not a regular file, not deleted even though as1 failed.\n", passout);
                    }
                    if (tmpst != 0) {
                        unlink(symtab);
                    }
                }
                if (tmp_uldobj != NULL) {
                    unlink(tmp_uldobj);
                }
                continue;
            }

            if ((ddoptflag == TRUE) && (compiler == COMPILER_3) && ddoptinfo && (Oflag >= 2)) {
                unlink(tempstr[26]);
            }
            if ((srcsuf != 'G') && !Kflag) {
                unlink(passin);
            }
            if ((tmpst != 0) && !Kflag) {
                unlink(symtab);
            }

            if ((compiler == COMPILER_3) && sp11C && (srcsuf != 'f') && (srcsuf != 'F')) {
                D_1000BF74 = sp11C;
                relocate_passes("f", NULL, NULL);
            }
            if ((compiler == COMPILER_1) &&
                ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                !no_prelink) {
                update_instantiation_info_file(srcfiles.entries[i], passout);
            }
        }
    } /* end of main file-processing loop */

    srcsuf = '\0';
    if (compiler == COMPILER_4) {
        if (runerror != 0) {
            exit(1);
        } else {
            exit(0);
        }
    }

    if (NoMoreOptions) {
        for (i = 0; i < objfiles.length; i++) {
            if ((objfiles.entries[i][0] == '-') && (strchr(objfiles.entries[i], '.') != NULL)) {
                objfiles.entries[i] = func_00433534(objfiles.entries[i]);
            }
        }
    }

    // linking passes
    if (!cflag && !Sflag && !Eflag && !Pflag && !jflag && (runerror == 0) && (objfiles.length != 0) &&
        (Hchar == '\0') && !nocode) {
        if (old_non_shared && mips2flag && !kpic_flag) {
            error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                  "can't mix -mips2 with shared for ucode compilers, try using -non_shared\n");
            default_call_shared = FALSE;
            call_shared = FALSE;
        }
        if (old_non_shared && mips3flag) {
            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't mix ucode 32-bit -mips3 with shared\n");
            default_call_shared = FALSE;
            call_shared = FALSE;
            exit(2);
        }
        if (old_non_shared && coff_spec) {
            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't mix -coff with shared, try using -non_shared\n");
            default_call_shared = FALSE;
            call_shared = FALSE;
            exit(2);
        }
        if (old_non_shared && excpt_flag) {
            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't mix -excpt with shared, try using -non_shared\n");
            default_call_shared = FALSE;
            call_shared = FALSE;
            exit(2);
        }
        if ((old_non_shared || non_shared) && make_edison_shlib) {
            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't mix -shared with -non_shared\n");
            exit(2);
        }
        if (cordflag && make_edison_shlib) {
            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't mix -shared with -cord\n");
            exit(2);
        }

    phase_prelinker:
        {
            if ((compiler == COMPILER_1) &&
                ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                !no_prelink) {
                execlist.length = 0;
                addstr(&execlist, "edg_prelink");
                addstr(&execlist, "-fSGI");
                addlist(&execlist, &prelinkerflags);
                if (vflag || verbose_prelink) {
                    addstr(&execlist, "-v");
                }
                add_prelinker_objects(&execlist, &objfiles);
                if (xpg_flag) {
                    add_prelinker_objects(&execlist, &dashlfiles);
                }
                if (run(prelinker, execlist.entries, NULL, NULL, NULL) != 0) {
                    runerror++;
                    goto phase_cord;
                }
            }
        }

    phase_ld:
        {
            execlist.length = 0;
            addstr(&execlist, LD);
            if (kpic_flag && !irix4 && !coff_spec) {
                addstr(&ldflags, "-KPIC");
            }
            if (non_shared && !non_shared_emitted) {
                if (!mips2flag && !mips3flag) {
                    addstr(&ldflags, "-non_shared");
                    non_shared_emitted = TRUE;
                }
            } else if (call_shared || make_edison_shlib) {
                if (transitive_link) {
                    addstr(&ldflags, "-transitive_link");
                } else if (full_transitive_link) {
                    addstr(&ldflags, "-full_transitive_link");
                } else if (no_transitive_link) {
                    addstr(&ldflags, "-no_transitive_link");
                }
            }
            if (quickstart_info) {
                addstr(&ldflags, "-quickstart_info");
            }
            if (elfflag && !coff_spec) {
                addstr(&execlist, "-elf");
            }
            if (tfp_flag) {
                addstr(&execlist, "-allow_jump_at_eop");
            }
            if ((compiler == COMPILER_1) && (c_compiler_choice == C_COMPILER_CHOICE_3)) {
                addstr(&execlist, "-delta");
            }
            if (cordflag) {
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
            if (make_edison_shlib) {
                addstr(&execlist, "-shared");
            }
            if ((compiler == COMPILER_1) &&
                ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3))) {
                add_cxx_symbol_options();
            }
            if (irix4) {
                addstr(&execlist, mkstr("-L", NULL));
                if (non_shared) {
                    addstr(&execlist, mkstr("-L", "/usr/irix4/", "usr/lib/nonshared/", NULL));
                    crtx = mkstr(comp_host_root, "usr/lib/nonshared/", CRTX, NULL);
                    crtn = mkstr(comp_host_root, "usr/lib/nonshared/", "crtn.o", NULL);
                } else {
                    addstr(&execlist, mkstr("-L", "/usr/irix4/", "usr/lib/", NULL));
                    crtx = mkstr(comp_host_root, "usr/lib/", CRTX, NULL);
                    crtn = mkstr(comp_host_root, "usr/lib/", "crtn.o", NULL);
                }
            }
            if (svr4_systype) {
                if (compchoice == COMP_CHOICE_1) {
                    addstr(&execlist, mkstr("-SYSTYPE_SVR4", NULL, NULL));
                }
                addstr(&execlist, mkstr("-_SYSTYPE_SVR4", NULL, NULL));
                if (call_shared || make_edison_shlib) {
                    addstr(&execlist, "-require_dynamic_link");
                    addstr(&execlist, "_rld_new_interface");
                    if (ignore_unresolved_flag) {
                        addstr(&execlist, "-ignore_unresolved");
                    } else if (no_unresolved_flag) {
                        addstr(&execlist, "-no_unresolved");
                    } else if (default_svr4 || make_edison_shlib) {
                        addstr(&execlist, "-ignore_unresolved");
                    } else {
                        addstr(&execlist, "-no_unresolved");
                    }
                }
            }
            if (fiveflag) {
                addstr(&execlist, mkstr("-L", runlib, NULL));
            }
            if ((allBstring != NULL) && (*allBstring != '\0')) {
                addstr(&execlist, mkstr("-B", allBstring, NULL));
            }
            if (cordflag) {
                addstr(&execlist, "-r");
                addstr(&execlist, "-d");
                addstr(&execlist, "-z");
            }
            if (irix4) {
                addstr(&execlist, "-G");
            } else {
                addstr(&execlist, mkstr("-Wx", ",", "-G", NULL));
            }
            addstr(&execlist, Gnum);
            addlist(&execlist, &ldflags);
            addlist(&execlist, &nldflags);
            if (mips2flag && (sp148 == 0)) {
                if (strcmp("/", comp_target_root) != 0) {
                    if (non_shared) {
                        addstr(&execlist,
                               mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "nonshared", NULL));
                    } else {
                        addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "", NULL));
                    }
                } else {
                    if (non_shared) {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "nonshared", NULL));
                    } else {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "", NULL));
                    }
                }
            }
            if (mips1flag && (sp148 == 0)) {
                if (strcmp("/", comp_target_root) != 0) {
                    if (non_shared) {
                        addstr(&execlist,
                               mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "nonshared", NULL));
                    } else if (abi_flag == 0) {
                        addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, "", NULL));
                    }
                } else {
                    if (non_shared) {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "nonshared", NULL));
                    } else if (abi_flag == 0) {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/", currcomp, "", NULL));
                    }
                }
            }
            if (strcmp("/", comp_target_root) != 0) {
                if (!Lflag) {
                    if ((compiler == COMPILER_1) && (c_compiler_choice == C_COMPILER_CHOICE_3)) {
                        addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/DCC", currcomp, NULL));
                    }
                    if (non_shared) {
                        addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/nonshared/", currcomp, NULL));
                    } else if (abi_flag == 0) {
                        addstr(&execlist, mkstr("-L", comp_target_root, runlib, "usr/lib/", currcomp, NULL));
                    }
                }
            } else {
                if (!Lflag) {
                    if ((compiler == COMPILER_1) && (c_compiler_choice == C_COMPILER_CHOICE_3)) {
                        addstr(&execlist, mkstr("-L", runlib, "usr/lib/DCC", currcomp, NULL));
                    }
                }
            }
            if (make_edison_shlib) {
                if ((compiler == COMPILER_1) &&
                    ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3))) {
                    addstr(&execlist, cxx_init);
                }
                if ((compiler == COMPILER_1) && (c_compiler_choice == C_COMPILER_CHOICE_3)) {
                    addstr(&execlist, delta_init);
                }
                addlist(&execlist, &objfiles);
                if (xpg_flag) {
                    addlist(&execlist, &dashlfiles);
                }
                if (!nodeflib) {
                    if ((compiler == COMPILER_1) &&
                        ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3))) {
                        spDC = !D_1000BF90 && (strcmp(LD, "old_ld") != 0);
                        if (spDC) {
                            addstr(&execlist, "-dont_warn_unused");
                        }
                        if (exception_handling) {
                            addstr(&execlist, "-lCsup");
                        }
                        addstr(&execlist, "-lC");
                        if (spDC) {
                            addstr(&execlist, "-warn_unused");
                        }
                    }
                    if (xpg_flag) {
                        addstr(&execlist, "-dont_warn_unused");
                        addstr(&execlist, "-lgen");
                        addstr(&execlist, "-warn_unused");
                    }
                    addstr(&execlist, "-lc");
                }
            } else {
                addstr(&execlist, "-nocount");
                addstr(&execlist, crtx);
                if ((compiler == COMPILER_1) &&
                    ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3))) {
                    addstr(&execlist, cxx_init);
                }
                if ((compiler == COMPILER_1) && (c_compiler_choice == C_COMPILER_CHOICE_3)) {
                    addstr(&execlist, delta_init);
                }
                addstr(&execlist, "-count");
                addlist(&execlist, &objfiles);
                if (xpg_flag) {
                    addlist(&execlist, &dashlfiles);
                }
                addlist(&execlist, &ldZflags);
                if ((ansichoice == ANSICHOICE_KR) && (compiler == COMPILER_1) && !irix4) {
                    addstr(&execlist, "-cckr");
                }
                addstr(&execlist, "-nocount");
                if (!nodeflib) {
                    if ((compiler == COMPILER_2) || haspascal) {
                        addspacedstr(&execlist, libp);
                        addspacedstr(&execlist, libxmalloc);
                        addspacedstr(&execlist, libexc);
                        addspacedstr(&execlist, libmld);
                    }
                    if ((compiler == COMPILER_3) || hasfortran) {
                        if (mp_flag) {
                            addspacedstr(&execlist, libI77_mp);
                        }
                        if (non_shared || irix4) {
                            addspacedstr(&execlist, libF77);
                            addspacedstr(&execlist, libm);
                            addspacedstr(&execlist, libU77);
                            if (D_1000C130 != 0) {
                                spD8 = strlen(libI77);
                                spD4 = malloc(spD8 + 2);
                                memcpy(spD4, libI77, spD8);
                                spD4[spD8 + 0] = '_';
                                spD4[spD8 + 1] = 's';
                                spD4[spD8 + 2] = '\0';
                                libI77 = spD4;
                            }
                            addspacedstr(&execlist, libI77);
                            addspacedstr(&execlist, libisam);
                        } else {
                            addspacedstr(&execlist, libftn);
                            addspacedstr(&execlist, libm);
                        }
                    }
                    if (compiler == COMPILER_5) {
                        addstr(&execlist, libpl1);
                        addspacedstr(&execlist, libxmalloc);
                        addstr(&execlist, "-ltermcap");
                        addspacedstr(&execlist, libexc);
                        addspacedstr(&execlist, libmld);
                    }
                    if ((compiler == COMPILER_2) || (hasfortran && (compiler != COMPILER_3)) || haspascal || haspl1 ||
                        (compiler == COMPILER_5) || (compiler == COMPILER_6)) {
                        addspacedstr(&execlist, libm);
                    }
                    if (pgflag != 0) {
                        addspacedstr(&execlist, libgprof);
                    } else if (pflag != 0) {
                        addspacedstr(&execlist, libprof);
                    }
                    if (!sixty4bitflag) {
                        ldw_file = fopen(libdw_path, "r");
                        if (ldw_file != NULL) {
                            addspacedstr(&execlist, libdw);
                        }
                    }
                    if (cmp_flag & 0x10000) {
                        addstr(&execlist, libc_mp);
                        if (compiler == COMPILER_1) {
                            addstr(&execlist, "-lkapio");
                        }
                    }
                    if (run_sopt && (compiler == COMPILER_1)) {
                        addstr(&execlist, "-lkapio");
                    }
                    if (compiler == COMPILER_3) {
                        if (D_1000C130 == 2) {
                            addstr(&execlist, "-lc_s");
                            if (xpg_flag) {
                                addstr(&execlist, "-dont_warn_unused");
                                addstr(&execlist, "-lgen");
                                addstr(&execlist, "-warn_unused");
                            }
                            addstr(&execlist, "-lc");
                        } else {
                            if (irix4 && (B_1000ED74 == 0)) {
                                addstr(&execlist, "-lmpc");
                            }
                            if (B_1000ED2C != 0) {
                                addstr(&execlist, "-lc_s");
                            } else if (B_1000ED30 != 0) {
                                addstr(&execlist, "-lc_s");
                            }
                            if (xpg_flag) {
                                addstr(&execlist, "-dont_warn_unused");
                                addstr(&execlist, "-lgen");
                                addstr(&execlist, "-warn_unused");
                            }
                            addstr(&execlist, "-lc");
                        }
                    } else {
                        if (irix4 && (cmp_flag & 0x10000)) {
                            addstr(&execlist, "-lmpc");
                        }
                        if ((compiler == COMPILER_1) && ((c_compiler_choice == C_COMPILER_CHOICE_2) ||
                                                         (c_compiler_choice == C_COMPILER_CHOICE_3))) {
                            spD0 = !D_1000BF90 && (strcmp(LD, "old_ld") != 0);
                            if (spD0) {
                                addstr(&execlist, "-dont_warn_unused");
                            }
                            if (exception_handling) {
                                addstr(&execlist, "-lCsup");
                            }
                            addstr(&execlist, "-lC");
                            if (spD0) {
                                addstr(&execlist, "-warn_unused");
                            }
                        }
                        if (B_1000ED2C != 0) {
                            addstr(&execlist, "-lc_s");
                        } else if (B_1000ED30 != 0) {
                            addstr(&execlist, "-lc_s");
                        }
                        if (xpg_flag) {
                            addstr(&execlist, "-dont_warn_unused");
                            addstr(&execlist, "-lgen");
                            addstr(&execlist, "-warn_unused");
                        }
                        addstr(&execlist, "-lc");
                    }
                }
                if (crtn_required) {
                    addstr(&execlist, crtn);
                }
                if (rls_id_object != NULL) {
                    addstr(&execlist, rls_id_object);
                }
            }

            passin = NULL;
            if (run(ld, execlist.entries, NULL, NULL, tempstr[32]) != 0) {
                runerror++;
                if (!Kflag) {
                    if ((strcmp(LD, "old_ld") == 0) ||
                        ((compiler == COMPILER_1) &&
                         ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3)))) {
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
        }

    phase_filter:
        if (tempstr[32] != NULL) {
            if ((stat(tempstr[32], &sp48) == 0) && (sp48.st_size > 0)) {
                execlist.length = 0;
                addstr(&execlist, "c++filt");
                run(filter, execlist.entries, tempstr[32], NULL, NULL);
            }
            unlink(tempstr[32]);
        }

    phase_patch:
        if ((runerror == 0) && (compiler == COMPILER_1) &&
            ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3))) {
            execlist.length = 0;
            addstr(&execlist, patch);
            if (vflag) {
                addstr(&execlist, "-d");
            }
            if (outfile != NULL) {
                addstr(&execlist, outfile);
            } else {
                addstr(&execlist, "a.out");
            }
            if (run(patch, execlist.entries, NULL, NULL, NULL) != 0) {
                runerror++;
            }
        }

    phase_strip:
        if ((runerror == 0) && do_strip) {
            execlist.length = 0;
            addstr(&execlist, strip);
            if (outfile != NULL) {
                addstr(&execlist, outfile);
            } else {
                addstr(&execlist, "a.out");
            }
            if (run(strip, execlist.entries, NULL, NULL, NULL) != 0) {
                runerror++;
            }
        }

    phase_cord:
        {
            if (cordflag && (runerror == 0)) {
                execlist.length = 0;
                addstr(&execlist, "cord");
                if (vflag) {
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
                    runerror++;
                    unlink(passout);
                    unlink(tempstr[22]);
                } else {
                    unlink(tempstr[22]);
                }
            }
            if ((runerror == 0) && (srcfiles.length == 1) && (nobjs == 1) && !Kflag) {
                unlink(mksuf(srcfiles.entries[0], 'o'));
            }
        }
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
    if ((compiler == COMPILER_1) && (gflag >= 2)) {
        unlink(tempstr[33]);
    }
    if (runerror != 0) {
        exit(1);
    }
    return 0;
}

// function process_config # 3
void process_config(int argc, char** argv) {
    register int i;
    register char* var_s1;
    char* sp1144 = comp_target_root;
    char* sp1140;
    FILE* sp113C;
    char sp13C[0x1000];
    int sp138;
    char* sp38[0x40];

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-systype") == 0) {
            i++;
            if (i >= argc) {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-systype must have an argument\n");
                exit(2);
            }

            user_systype = TRUE;
            systype = argv[i];
            if (strcmp(systype, "svr4") == 0) {
                svr4_systype = TRUE;
            } else {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "only systype svr4 allowed\n");
                exit(2);
            }

            // clang-format off
            if ((strcmp(systype, "svr4") != 0) 
                && (strcmp(systype, "bsd43") != 0) 
                && (strcmp(systype, "svr3") != 0) 
                && (strcmp(systype, "sysv") != 0) 
                && (fopen(strcat("/", systype), "r") == NULL) 
                && !systype_warn) {
                // clang-format on
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
        if (1) {} // FAKE
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
// Process most of the options passed, the vast majority of which begin with '-'
void parse_command(int argc, char** argv) {
    register int var_s0;   // option index
    register char var_s1;  // file suffix, multipurpose?
    register char* var_s2; // multipurpose string pointer
    register char* var_s3; // used for -G?
    char* sp15C = NULL;    // related to -MD?
    char* sp158 = NULL;
    char* sp154 = NULL; // target
    char sp153 = 0;     // unused
    int sp14C = 1;      // Treat bad options as errors
    char* sp148 = getenv("SGI_IRIX4");

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
        if ((argv[var_s0][0] == '-') && (!NoMoreOptions || (strchr(argv[var_s0], '.') == NULL))) {
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
                    if (strncmp(argv[var_s0], "-DEFAULT:", strlen("-DEFAULT:")) == 0) {
                        break;
                    }
                    if (argv[var_s0][2] == '\0') {
                        if ((var_s0 + 1) < argc) {
                            char* sp140;
                            int pad[2];

                            if (0) {}
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

                    if (0) {
                        // TODO: work out where these should actually go
                        // There needs to be a mention of strtoul here for the symbol
                        // table to end up in the right order (after the first call to
                        // add_static_opt, but before full_path).
                        (void)"-D taken as empty cpp -D, not ld(1) -D hexnum\n";
                        (void)"-D";
                        (void)"ld requires -D to have an argument\n";
                        strtoul(sp15C, &sp15C, 16);
                    }

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
                        addstr(&fcomflags, argv[var_s0]);
                        add_static_opt(mkstr("-I", full_path(argv[var_s0] + 2), NULL));
                    }
                    break;

                case 'J': /* switch 1 */
                    if (strcmp(argv[var_s0], "-Jsfm") == 0) {
                        break;
                    }
                    if (strcmp(argv[var_s0], "-J") == 0) {
                        char* sp130;
                        char* sp12C = argv[var_s0 + 1];

                        for (sp130 = sp12C; *sp130 != 0; sp130++) {
                            if (!isdigit(*sp130)) {
                                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "non-digit character in -J %s\n", sp12C);
                                exit(2);
                            }
                        }
                        addstr(&prelinkerflags, argv[var_s0]);
                        addstr(&prelinkerflags, sp12C);
                        var_s0++;
                        break;
                    }
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
                            addstr(&prelinkerflags, sp128);
                            Lflag = TRUE;
                            break;
                        } else {
                            addstr(&prelinkerflags, mkstr("-YB", NULL));
                        }
                    }
                    Lflag = TRUE;
                    addstr(&ldflags, argv[var_s0]);
                    addstr(&prelinkerflags, argv[var_s0]);
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
                        if (xpg_flag && (var_s1 == 'f')) {
                            fprintf(stderr, "Error: optlevel should be specified\n");
                            exit(1);
                        }
                        Oflag = 2;
                        plain_O = TRUE;
                        if (plain_g) {
                            Oflag = 1;
                        }
                        if (((var_s0 + 1) < argc) && (argv[var_s0 + 1][1] == '\0') && (*argv[var_s0 + 1] >= '0') &&
                            (*argv[var_s0 + 1] <= '4')) {
                            char* sp124 = malloc(strlen(argv[var_s0 + 1]) + 3);

                            sp124[0] = '-';
                            sp124[1] = 'O';
                            sp124[2] = 0;
                            Oflag = *argv[var_s0 + 1] - '0'; // '0' -> 0, '1' -> 1, etc.
                            addstr(&fcomflags, strcat(sp124, argv[var_s0 + 1]));
                            var_s0++;
                        }
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
                    if ((argv[var_s0][2] == '\0') && ((var_s0 + 1) < argc)) {
                        char* sp118 = malloc(strlen(argv[var_s0 + 1]) + 3);

                        sp118[0] = '-';
                        sp118[1] = 'U';
                        sp118[2] = 0;
                        addstr(&undefineflags, strcat(sp118, argv[var_s0 + 1]));
                        var_s0++;
                        break;
                    }
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
                                                        unsigned int sp114;
                                                        char* sp110;

                                                        sp114 = strtoul(argv[var_s0 + 1], &sp110, 16);
                                                        if (((size_t)(sp110 - argv[var_s0 + 1]) !=
                                                             strlen(argv[var_s0 + 1])) ||
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
                    if ((compiler == COMPILER_1) &&
                        ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                        (strcmp(argv[var_s0], "-anach") == 0)) {
                        anachronisms = TRUE;
                        break;
                    }
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
                        docpp = 0;
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
                    if ((compiler == COMPILER_1) &&
                        ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                        (strcmp(argv[var_s0], "-cfront") == 0)) {
                        cfront_compatible = TRUE;
                        break;
                    }
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
                         (strcmp(argv[var_s0], "-chararg1") == 0) || (strcmp(argv[var_s0], "-chunk") == 0) ||
                         (strcmp(argv[var_s0], "-check_bounds") == 0))) {
                        if (strcmp(argv[var_s0], "-col120") == 0) {
                            mp_col120flag = TRUE;
                        }
                        if (strcmp(argv[var_s0], "-check_bounds") == 0) {
                            addstr(&fcomflags, "-C");
                        } else if (strncmp(argv[var_s0], "-chunk=", strlen("-chunk=")) == 0) {
                            char* sp10C = argv[var_s0] + strlen("-chunk=");

                            while (*sp10C != 0) {
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
                        if ((compiler == COMPILER_1) &&
                            ((c_compiler_choice == C_COMPILER_CHOICE_2) ||
                             (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                            (strcmp(argv[var_s0], "-exceptions") == 0)) {
                            if ((compiler != COMPILER_1) || (c_compiler_choice != C_COMPILER_CHOICE_3)) {
                                exception_handling = TRUE;
                                relocate_passes("f", NULL, NULL);
                                if (access(cfe, EX_OK) == -1) {
                                    exception_handling = FALSE;
                                    relocate_passes("f", NULL, NULL);
                                } else {
                                    break;
                                }
                            }
                            goto bad_option;
                        }
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
                    if ((strcmp(argv[var_s0], "-full_transtive_link") == 0) ||
                        (strcmp(argv[var_s0], "-full_transitive_link") == 0)) {
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
                    if (strcmp(argv[var_s0], "-keep") == 0) {
                        Kflag++;
                        break;
                    }
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
                        } else if ((argv[var_s0][2] == '\0') && ((var_s0 + 1) < argc)) {
                            char* sp104 = malloc(strlen(argv[var_s0 + 1]) + 3);

                            sp104[0] = '-';
                            sp104[1] = 'l';
                            sp104[2] = '\0';
                            if (xpg_flag) {
                                addstr(&dashlfiles, strcat(sp104, argv[var_s0 + 1]));
                            } else {
                                addstr(&objfiles, strcat(sp104, argv[var_s0 + 1]));
                            }
                            var_s0++;
                            break;
                        }
                        if (xpg_flag) {
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

                case 'm': /* switch 1 */
                    if (strcmp(argv[var_s0], "-multigot") == 0) {
                        addstr(&nldflags, argv[var_s0]);
                        break;
                    }
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
                        mips1flag = TRUE;
                        mips2flag = FALSE;
                        if (dwopcodeflag) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't mix -mips1 with -dwopcode\n");
                            exit(2);
                        }
                        if (mips2_spec_flag) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                                  "-mips1 conflicts with -mips2; using last value (mips1)\n");
                            mips2_spec_flag = FALSE;
                        }
                        break;
                    }
                    if (strcmp(argv[var_s0], "-mips2") == 0) {
                        if (mips1flag || mips3flag) {
                            error(ERRORCAT_WARNING, NULL, 0, NULL, 0,
                                  "-mips2 conflicts with -mips1; using last value (mips2)\n");
                        }
                        mips1flag = FALSE;
                        mips2flag = TRUE;
                        mips2_spec_flag = TRUE;
                        relocate_passes("M", NULL, NULL);
                        break;
                    }
                    if (strcmp(argv[var_s0], "-mips3") == 0) {
                        mips1flag = FALSE;
                        mips2flag = FALSE;
                        if (mips2_spec_flag) {
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
                    if ((compiler == COMPILER_1) &&
                        ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                        (strcmp(argv[var_s0], "-no_exceptions") == 0)) {
                        if ((compiler != COMPILER_1) || (c_compiler_choice != C_COMPILER_CHOICE_3)) {
                            exception_handling = FALSE;
                            relocate_passes("f", NULL, NULL);
                            break;
                        }
                        goto bad_option;
                    }
                    if (strcmp(argv[var_s0], "-new_ld") == 0) {
                        if (D_1000BF94) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "malformed or unknown option: -new_ld\n");
                            exit(2);
                        } else if ((compiler == COMPILER_1) && (c_compiler_choice == C_COMPILER_CHOICE_3)) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "-new_ld not supported for DCC\n");
                            exit(2);
                        } else {
                            LD = "ld";
                            D_1000BF90 = FALSE;
                        }
                        relocate_passes("l", NULL, NULL);
                        break;
                    }
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
                        addstr(&prelinkerflags, mkstr("-YB", NULL));
                        break;
                    }
                    if (strcmp(argv[var_s0], "-nodeflib") == 0) {
                        nodeflib = TRUE;
                        break;
                    }
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
                        B_1000ED74 = 1;
                        break;
                    }
                    if ((compiler == COMPILER_3) &&
                        ((strcmp(argv[var_s0], "-noextend_source") == 0) || (strcmp(argv[var_s0], "-noi4") == 0) ||
                         (strcmp(argv[var_s0], "-noisam") == 0) || (strcmp(argv[var_s0], "-noexpopt") == 0) ||
                         (strcmp(argv[var_s0], "-noequivauto") == 0) || (strcmp(argv[var_s0], "-nof77") == 0))) {
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
                    if (strcmp(argv[var_s0], "-old_ld") == 0) {
                        if (D_1000BF94) {
                            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "malformed or unknown option: -old_ld\n");
                            exit(2);
                        } else {
                            LD = "old_ld";
                            relocate_passes("l", NULL, NULL);
                        }
                        break;
                    }
                    if (strcmp(argv[var_s0], "-o32") == 0) {
                        thirty2bitflag = TRUE;
                        mips_abi = 1;
                        if (var_s0 >= (argc - MIPS_ABI_1)) {
                            func_00431B38(var_s0 + 1, 1);
                        }
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
                            B_1000ECCC = mkstr(outfile, NULL);
                            func_00431B38(var_s0, 2);
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
                    } else if (strcmp(argv[var_s0], "-pg") == 0) {
                        pflag = 1;
                        pgflag = 1;
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
                        if ((compiler == COMPILER_1) && ((c_compiler_choice == C_COMPILER_CHOICE_2) ||
                                                         (c_compiler_choice == C_COMPILER_CHOICE_3))) {
                            do_strip = TRUE;
                        } else {
                            addstr(&ldflags, argv[var_s0]);
                        }
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
                        D_1000BF74 = TRUE;
                        if ((argv[var_s0][3] == ',') && (argv[var_s0][4] != '\0')) {
                            char* sp64;

                            for (sp64 = strtok(argv[var_s0] + 4, ","); sp64 != NULL; sp64 = strtok(NULL, ",")) {
                                if (strcmp(sp64, "nosrc") == 0) {
                                    D_1000BF78 = 1;
                                } else if (D_1000BF80 != NULL) {
                                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0,
                                          "Static analysis directory already specified\n");
                                } else {
                                    D_1000BF80 = sp64;
                                    if (sp64[strlen(sp64) - 1] != '/') {
                                        D_1000BF80 = mkstr(sp64, "/", NULL);
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
                        D_1000BF84 =
                            (argv[var_s0][6] == ',') ? mkstr(argv[var_s0] + 7, NULL) : mkstr("cvstatic.fileset", NULL);
                        D_1000BF88++;
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
                    if (strcmp(argv[var_s0], "-showt") == 0) {
                        time_flag = TRUE;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-show0") == 0) {
                        vflag = TRUE;
                        execute_flag = FALSE;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-showm") == 0) {
                        memory_flag++;
                        break;
                    }
                    if (strcmp(argv[var_s0], "-show_defaults") == 0) {
                        execute_flag = FALSE;
                        exit(0);
                        break;
                    }
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
                                D_1000C130 = 1;
                                break;
                            }
                            if (strcmp(argv[var_s0] + 7, "all") == 0) {
                                D_1000C130 = 2;
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
                    if (argv[var_s0][2] == '\0') {
                        if (xpg_flag) {
                            NoMoreOptions++;
                        }
                    } else {
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
                            time_flag = TRUE;
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
            (var_s1 == SUF_6) || ((compiler == COMPILER_1) && nocode && D_1000BF74 && (var_s1 == 'h')) || Eflag ||
            (compiler == COMPILER_4)) {
            int sp60; // number of '-' on the end?
            int sp5C; // option index

            srcexists++;
            if ((argv[var_s0][0] == '-') && !NoMoreOptions) {
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
        func_00431B38(var_s0 + 1, 1);
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
            ((compiler == COMPILER_3) && D_1000BF74)) {
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

    if (mips2flag) {
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
    // Error message types
    static const char* D_1000C1E0[] = {
        "Internal", // ERRORCAT_INTERNAL
        "Error",    // ERRORCAT_ERROR
        "Warning",  // ERRORCAT_WARNING
        "Info",     // ERRORCAT_INFO
        "Fix",      // ERRORCAT_FIX
        "",         // ERRORCAT_ERRNO
    };

    int len;
    int i;

    if (!Vflag && (D_1000C1D8 == NULL)) {
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
                fprintf(stderr, "%s: %s\n", D_1000C1D8, GET_ERRNO_STR(errno));
            }
            exit(1);
        }

        for (i = 0; i < len; i++) {
            D_1000C1DC[i] = ' ';
        }
        D_1000C1DC[i] = '\0';
    }

    if (arg0 == ERRORCAT_ERRNO) {
        //! @bug `D_1000C1DC` is null if the previous block did not run.
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

    // condition never passes since `compose_first_G0` is never `TRUE`
    if ((strcmp(Gnum, "0") == 0) && compose_first_G0) {
        compose_first_G0 = FALSE;
        compose_G0_libs("PE1COMFIUSXnW");
    }

    for (; *var_s1 != '\0'; var_s1++) {
        if ((arg1 != NULL) || (strchr(alltstring, *var_s1) == NULL)) {
            switch (*var_s1) {
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
                        } else {
                            if (fiveflag) {
                                includeB = mkstr(comp_target_root, "usr/5include", arg2, NULL);
                            } else if (abi_flag != 0) {
                                includeB = mkstr(comp_target_root, "usr/include/abi", arg2, NULL);
                            } else {
                                eincludeB = mkstr(comp_target_root, "usr/include/CC", arg2, NULL);
                                includeB = mkstr(comp_target_root, "usr/include", arg2, NULL);
                            }
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
                        cpp =
                            mkstr(arg1, (((cppchoice != CPP_CHOICE_1) && (cppchoice != CPP_CHOICE_3)) ? "cpp" : "acpp"),
                                  arg2, NULL);
                    } else {
                        cpp = mkstr(comp_host_root, "usr/lib/", currcomp,
                                    ((cppchoice != CPP_CHOICE_1) && (cppchoice != CPP_CHOICE_3) ? "cpp" : "acpp"), arg2,
                                    NULL);
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
                        ccom = mkstr(arg1, (ansichoice != ANSICHOICE_KR) ? "accom" : "ccom", arg2, NULL);
                        cfe = mkstr(
                            arg1,
                            (((c_compiler_choice != C_COMPILER_CHOICE_0) || ((compiler == COMPILER_3) && D_1000BF74))
                                 ? (exception_handling ? "edgcpfe.eh" : "edgcpfe")
                                 : "cfe"),
                            arg2, NULL);
                        upas = mkstr(arg1, "upas", arg2, NULL);
                        fcom = mkstr(arg1, "fcom", arg2, NULL);
                        upl1 = mkstr(arg1, "pl1fe", arg2, NULL);
                        ucob = mkstr(arg1, "cobfe", arg2, NULL);
                    } else {
                        if (cmp_flag & 0x10000) {
                            mpc = mkstr(comp_host_root, "usr/lib/", currcomp, "mpc", arg2, NULL);
                        }
                        ccom = mkstr(comp_host_root, "usr/lib/", currcomp,
                                     (ansichoice != ANSICHOICE_KR) ? "accom" : "ccom", arg2, NULL);
                        if (((compiler == COMPILER_1) && (c_compiler_choice != C_COMPILER_CHOICE_0)) ||
                            ((compiler == COMPILER_3) && D_1000BF74)) {
                            cfe = mkstr(comp_host_root, "usr/lib/DCC/", currcomp,
                                        (((c_compiler_choice != C_COMPILER_CHOICE_0) ||
                                          ((compiler == COMPILER_3) && D_1000BF74))
                                             ? (exception_handling ? "edgcpfe.eh" : "edgcpfe")
                                             : "cfe"),
                                        arg2, NULL);
                        } else {
                            cfe = mkstr(comp_host_root, "usr/lib/", currcomp,
                                        (((c_compiler_choice != C_COMPILER_CHOICE_0) ||
                                          ((compiler == COMPILER_3) && D_1000BF74))
                                             ? (exception_handling ? "edgcpfe.eh" : "edgcpfe")
                                             : "cfe"),
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
                    } else if ((compiler == COMPILER_1) &&
                               ((c_compiler_choice == C_COMPILER_CHOICE_2) ||
                                (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                               D_1000BF8C) {
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
                               D_1000BF8C) {
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
                               D_1000BF8C) {
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
                        if ((compiler == COMPILER_1) &&
                            ((c_compiler_choice == C_COMPILER_CHOICE_2) ||
                             (c_compiler_choice == C_COMPILER_CHOICE_3)) &&
                            D_1000BF90) {
                            ld = mkstr(comp_host_root, "usr/lib/DCC/", currcomp, LD, arg2, NULL);
                        } else if (irix4) {
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
                        } else if (non_shared) {
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
                    } else if (non_shared) {
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
                        if (non_shared) {
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
                            if (non_shared) {
                                libdw = mkstr("-L", comp_target_root, "usr/lib/nonshared/", currcomp, " -B", arg2,
                                              LibDw, NULL);
                            } else {
                                libdw = mkstr("-L", comp_target_root, "usr/lib/", currcomp, " -B", arg2, LibDw, NULL);
                            }
                        } else {
                            if (non_shared) {
                                libdw = mkstr("-L", comp_target_root, "usr/lib/", currcomp, LibDw, NULL);
                            } else {
                                libdw = mkstr("-L", comp_target_root, "usr/lib/", currcomp, LibDw, NULL);
                            }
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
                        if ((arg2 != NULL) && (*arg2 != 0)) {
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
                            if ((arg2 != NULL) && (*arg2 != 0)) {
                                libprof = mkstr("-L", arg1, " -B", arg2, LibProf1, NULL);
                                libgprof = mkstr("-L", arg1, " -B", arg2, LibGProf1, NULL);
                            } else {
                                libprof = mkstr("-L", arg1, LibProf1, NULL);
                                libgprof = mkstr("-L", arg1, LibGProf1, NULL);
                            }
                        } else if (non_shared) {
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
                            case CHIP_TARGET_MIPS1:
                                if ((arg2 != NULL) && (*arg2 != 0)) {
                                    libm = mkstr(arg1, " -B", arg2, LibM, NULL);
                                } else {
                                    libm = mkstr("-L", arg1, LibM, NULL);
                                }
                                libm_b = mkstr(arg1, "libm.b", arg2, NULL);
                                break;

                            case CHIP_TARGET_MIPS2:
                                libm = mkstr(arg1, "libm_mips2.a", arg2, NULL);
                                libm_b = mkstr(arg1, "libm_mips2.b", arg2, NULL);
                                break;

                            case CHIP_TARGET_MIPS3:
                                libm = mkstr(arg1, "libm_mips3.a", arg2, NULL);
                                libm_b = mkstr(arg1, "libm_mips3.b", arg2, NULL);
                                break;
                        }
                    } else {
                        switch (chip_targ) {
                            default:
                            case CHIP_TARGET_MIPS1:
                                libm = "-lm";
                                if (non_shared) {
                                    libm_b =
                                        mkstr(comp_target_root, "usr/lib/nonshared/", currcomp, "libm.b", arg2, NULL);
                                } else {
                                    libm_b = mkstr(comp_target_root, "usr/lib/", currcomp, "libm.b", arg2, NULL);
                                }
                                break;

                            case CHIP_TARGET_MIPS2:
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

                            case CHIP_TARGET_MIPS3:
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
                        if ((arg2 != NULL) && (*arg2 != 0)) {
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
                        if ((arg2 != NULL) && (*arg2 != 0)) {
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
                        if ((arg2 != NULL) && (*arg2 != 0)) {
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
                        if ((arg2 != NULL) && (*arg2 != 0)) {
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
                    error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "Unknown character in -t%c\n", *var_s1);
                    exit(2);
                    break;
            }
        }
    }
}

// function newrunlib # 9
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
 *  -returns 1 if the va_alist marker is the first
 *      parameter in the parameter list, or
 *  -returns 2 if the va_alist marker is the second
 *      parameter in the parameter list, and the
 *      first parameter has type double, or
 *  -returns 0 otherwise.
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
        error(ERRORCAT_ERROR, NULL, 0, "mkstr ()", 0x38BC, "out of memory\n");
        if (errno < sys_nerr) {
            error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", GET_ERRNO_STR(errno));
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
        error(ERRORCAT_ERROR, NULL, 0, "mklist ()", 14561, "out of memory\n");
        if (errno < sys_nerr) {
            error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", GET_ERRNO_STR(errno));
        }
        exit(1);
    }
    arg0->capacity = LIST_INITIAL_CAPACITY;
    arg0->length = 0;
    arg0->entries[0] = NULL;
}

// function addstr # 14
// Add a single string entry to a list.
// Called incorrectly.
void addstr(arg0, str)
    // clang-format off
    list* arg0;
    char* str;
// clang-format on
{
    if ((arg0->length + 1) >= arg0->capacity) {
        if ((arg0->entries = realloc(arg0->entries, (arg0->capacity + LIST_CAPACITY_INCR) * sizeof(char*))) == 0) {
            error(ERRORCAT_ERROR, NULL, 0, "addstr()", 14595, "out of memory\n");
            if (errno < sys_nerr) {
                error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", GET_ERRNO_STR(errno));
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
/**
 * Add a space-separated string to a list, dividing it up into separate entries by space characters (' ')
 *
 * @param arg0 List to add the entries to
 * @param str Space-separated string to add
 */
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
                error(ERRORCAT_ERROR, NULL, 0, "addspacedstr()", 14639, "out of memory\n");
                if (errno < sys_nerr) {
                    error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", GET_ERRNO_STR(errno));
                }
                exit(1);
            }
            arg0->capacity += LIST_CAPACITY_INCR;
        }
        arg0->entries[arg0->length] = str;
        arg0->length++;
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
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "newstr: unable to malloc for string %s\n", src);
        exit(2);
    }
    return dest;
}

// function save_place # 17
/**
 * Add one new uninitialised entry to a list
 *
 * @param arg0 list to add it to
 * @return int index of new entry
 */
int save_place(list* arg0) {
    int new_entry_index;

    if ((arg0->length + 1) >= arg0->capacity) {
        if ((arg0->entries = realloc(arg0->entries, (arg0->capacity + LIST_CAPACITY_INCR) * sizeof(char*))) == NULL) {
            error(ERRORCAT_ERROR, NULL, 0, "save_place()", 14695, "out of memory\n");

            if (errno < sys_nerr) {
                error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", GET_ERRNO_STR(errno));
            }
            exit(1);
        }
        arg0->capacity += LIST_CAPACITY_INCR;
    }
    new_entry_index = arg0->length;
    arg0->length++;
    arg0->entries[arg0->length] = NULL;
    return new_entry_index;
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
        error(ERRORCAT_INTERNAL, NULL, 0, "set_place ()", 14726, "place out of range");
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
            error(ERRORCAT_ERROR, NULL, 0, "addlist ()", 14756, "out of memory\n");
            if (errno < sys_nerr) {
                error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", GET_ERRNO_STR(errno));
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
/**
 * Adds entries from arg1 and arg2 onto the end of arg0:
 * - up to the first NULL from arg2,
 * - then everything from arg1,
 * - then the rest of arg2.
 */
void adduldlist(list* arg0, list* arg1, list* arg2) {
    int sp3C;
    int sp38;

    if ((arg0->length + arg1->length + arg2->length + 1) >= arg0->capacity) {

        if ((arg0->entries =
                 realloc(arg0->entries, (arg0->capacity + arg1->capacity + arg2->capacity + LIST_CAPACITY_INCR) *
                                            sizeof(char*))) == NULL) {
            error(ERRORCAT_ERROR, NULL, 0, "addlist ()", 14795, "out of memory\n");
            if (errno < sys_nerr) {
                error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", GET_ERRNO_STR(errno));
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
/**
 * Search for a string in a list.
 *
 * return int boolean, TRUE if not found
 */
int nodup(list* arg0, const char* str) {
    register int i;
    register char* entry;

    for (i = 0; i < arg0->length; i++) {
        entry = arg0->entries[i];
        if ((entry != NULL) && (strcmp(entry, str) == 0)) {
            return FALSE;
        }
    }

    return TRUE;
}

// function getsuf # 22
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
char getsuf(const char* path) {
    int basename_len = 0; // Length of suffix
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
    for (i = 0; suffixes[i].unk0 != NULL; i++) {
        if (strcmp(str, suffixes[i].unk0) == 0) {
            return suffixes[i].unk4;
        }
    }

    // Special case for "for"/"FOR".
    if (strcmp(str, "for") == 0) {
        return 'f';
    }
    if (strcmp(str, "FOR") == 0) {
        return 'F';
    }

    // Suffix not recognised.
    return '\0';
}

// function mksuf # 23
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
        for (i = 0; suffixes[i].unk0 != NULL; i++) {
            if (suffixes[i].unk4 == value) {
                new_suf = suffixes[i].unk0;
                break;
            }
        }

        if (new_suf == NULL) {
            error(ERRORCAT_INTERNAL, NULL, 0, "mksuf ()", 14938, "passed an unknown suffix value: %s\n", value);
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
            error(ERRORCAT_ERROR, NULL, 0, "mksuf ()", 14977, "Bad file name, no suffix: %s\n", path);
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
    // return new basename?
    return sp44;
}

// function savestr # 24
// Copy a string, adding extra_length bytes to the allocation.
char* savestr(const char* src, size_t extra_length) {
    char* dest = malloc(strlen(src) + extra_length + 1);

    if (dest == NULL) {
        error(ERRORCAT_ERROR, NULL, 0, "savestr ()", 15014, "out of memory\n");
        if (errno < sys_nerr) {
            error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", GET_ERRNO_STR(errno));
        }
        exit(1);
    }
    strcpy(dest, src);
    return dest;
}

//! FAKE: bss-shifting padding
static char bss_pad0, bss_pad1;

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

    if ((compiler == COMPILER_1) &&
        ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3)) && !nofilt &&
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

    if (vflag) {
        fprintf(stderr, "%s ", arg0);
        spA4 = arg1 + 1;
        while (*spA4 != NULL) {
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
    if (time_flag) {
        settimes();
    }
    if (!execute_flag) {
        return 0;
    }
    if ((memory_flag != 0) && (pipe(B_1000EC98) < 0)) {
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "pipe failed for -showm");
        return -1;
    }

    spA0 = fork();
    if (spA0 == -1) { // fork failed
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "no more processes\n");
        if (errno < sys_nerr) {
            error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", GET_ERRNO_STR(errno));
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
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't open input file: %s\n", arg2);
                if (errno < sys_nerr) {
                    error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", GET_ERRNO_STR(errno));
                }
                cleanup();
                exit(1);
            }
            dup2(sp94, fileno(stdin));
        }

        if (arg3 != NULL) {
            sp90 = creat(arg3, S_IRWXU | S_IRWXG | S_IRWXO); // 0777
            if (sp90 == -1) {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't create output file: %s\n", arg3);
                if (errno < sys_nerr) {
                    error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", GET_ERRNO_STR(errno));
                }
                cleanup();
                exit(1);
            }
            dup2(sp90, fileno(stdout));
        }

        if (arg4 != NULL) {
            sp8C = creat(arg4, S_IRWXU | S_IRWXG | S_IRWXO); // 0777
            if (sp8C == -1) {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't create error file: %s\n", arg4);
                if (errno < sys_nerr) {
                    error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", GET_ERRNO_STR(errno));
                }
                cleanup();
                exit(1);
            }
            dup2(sp8C, fileno(stderr));
        }

        execvp(arg0, arg1);
        sp78 = func_00430414(arg0, 1);
        if ((errno == ENOENT) && (sp78 != NULL)) {
            error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "%s is not installed (could not find %s).\n", sp78, arg0);
        } else {
            sp78 = func_00430414(arg0, 0);
            if ((errno == ENOENT) && (sp78 != NULL)) {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "%s may not be installed (could not find %s).\n", sp78, arg0);
            } else {
                error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "can't find or exec: %s\n", arg0);
                if (errno < sys_nerr) {
                    error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", GET_ERRNO_STR(errno));
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

        if (time_flag) {
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
int edit_src(const char* arg0, const char* arg1, int arg2) {
    char sp58[16];
    pid_t forkPid;
    pid_t sp50;
    int temp_t7; // sp4C
    SIG_PF sp48;
    SIG_PF sp44;
    int stat_loc;

    forkPid = fork();
    if (forkPid == (pid_t)-1) { // fork failed
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "fork to edit failed\n");
        if (errno < sys_nerr) {
            error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", GET_ERRNO_STR(errno));
        }
        return -1;
    }

    if (forkPid == (pid_t)0) { // child process

        if (editflag == EDIT_FLAG_2) {
            get_lino(sp58, arg1, arg2);
            execlp(arg0, arg0, sp58, arg1, "-l", tempstr[25], "-f", "err-window", (char*)NULL);
        } else if (xserver == 0) {
            execlp(arg0, arg0, "+1", errout, arg1, (char*)NULL);
        } else {
            execlp("xterm", "xterm", "-display", xserver, "-ls", "-e", arg0, "+1", errout, arg1, (char*)NULL);
        }
        error(ERRORCAT_ERROR, NULL, 0, NULL, 0, "failed to exec: %s\n", arg0);
        if (errno < sys_nerr) {
            error(ERRORCAT_ERRNO, NULL, 0, NULL, 0, "%s\n", GET_ERRNO_STR(errno));
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
void get_lino(char* arg0, const char* arg1, int arg2) {
    int sp83C;
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
    if (!Kflag) {
        if (passout != NULL) {
            unlink(passout);
        }
        if (passin != NULL) {
            char suf = getsuf(passin);

            if (((suf == '\0')) || ((suf != srcsuf) && (suf != 'm'))) {
                if (!Eflag) {
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
}

// function whats # 32
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
    printf("\tMips Computer Systems %d.%d\n", 7, 10);
}

int time0;
struct tms tm0;

// function settimes # 33
void settimes() {
    time0 = times(&tm0);
}

// function dotime # 34
#define CLOCK_TICKS 100

void dotime(const char* programName) {
    clock_t time1; // sp6C;
    clock_t clockTimeDiff;
    double milis;   // sp60
    double seconds; // sp58
    struct tms tm1; // sp48;

    time1 = times(&tm1);
    milis = (double)(tm1.tms_utime + tm1.tms_cutime - tm0.tms_utime - tm0.tms_cutime) / CLOCK_TICKS;
    seconds = (double)(tm1.tms_stime + tm1.tms_cstime - tm0.tms_stime - tm0.tms_cstime) / CLOCK_TICKS;
    clockTimeDiff = time1 - time0;
    fprintf(stderr, "%s phase time: %.2fu %.2fs %u:%04.1f %.0f%%\n", programName, milis, seconds,
            clockTimeDiff / (60 * CLOCK_TICKS), (double)(clockTimeDiff % (60 * CLOCK_TICKS)) / CLOCK_TICKS,
            ((milis + seconds) / ((double)clockTimeDiff / CLOCK_TICKS)) * 100.0);
}

// function func_0042FD7C # 35
// Search for a lib in directories (?)
static char* func_0042FD7C(const char* name, char** dirs) {
    int fildes;
    char* path;

    for (; *dirs != NULL; dirs++) {
        if ((compiler == COMPILER_1) &&
            ((c_compiler_choice == C_COMPILER_CHOICE_2) || (c_compiler_choice == C_COMPILER_CHOICE_3))) {
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
    } else if (non_shared) {
        path = mkstr("/", "usr/lib/nonshared", runlib, name, NULL);
    } else {
        path = mkstr("/", "usr/lib", runlib, name, NULL);
    }
    return path;
}

// function isdir # 36
/**
 * Checks if `path` is a directory.
 *
 * @param path
 * @return int boolean, true if
 */
int isdir(const char* path) {
    int spAC;
    struct stat statbuf;

    spAC = stat(path, &statbuf);
    if (spAC == -1) {
        return FALSE;
    }
    if (S_ISDIR(statbuf.st_mode)) {
        return TRUE;
    }
    return FALSE;
}

// function regular_not_writeable # 37
int regular_not_writeable(const char* arg0) {
    int sp24;

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
int regular_file(const char* path) {
    int spAC;
    struct stat statbuf;

    spAC = stat(path, &statbuf);
    if (spAC == -1) {
        return -1;
    }
    if (!S_ISREG(statbuf.st_mode)) {
        return 0;
    }
    return 1;
}

static char B_1000E5E0[0x400];

// function basename # 39
// Obtain the base name of a file path, i.e. the part after the final '/'
char* basename(const char* path) {
    register char* ret;
    register char* str = B_1000E5E0;
    register size_t len;

    if ((path == NULL) || (*path == '\0')) {
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

struct {
    /* 0x0 */ const char* unk0; // name?
    /* 0x4 */ const char* unk4; // full path?
    /* 0x8 */ const char* unk8; // description?
} // size = 0xC
prod_name[] = {
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
/**
 * Whether to force using cfront over the built-in C++ compiler. Can be set by `USE_CFRONT` environment variable, or
 * various flags.
 *
 * @param argc
 * @param argv
 * @return int boolean TRUE if should use cfront.
 */
int force_use_cfront(int argc, char** argv) {
    int i;
    char* sp28 = getenv("USE_CFRONT");
    int sp24 = 0; // Set but not used

    if ((sp28 != NULL) && (*sp28 != '0')) {
        return TRUE;
    }

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-exceptions") == 0) {
            D_1000BF7C = TRUE;
        }
        if (!D_1000BF7C && !exception_handling && ((strcmp(argv[i], "-F") == 0) || (strcmp(argv[i], "-Fc") == 0))) {
            return TRUE;
        }
        // clang-format off
        if ((strcmp(argv[i], "-use_cfront") == 0) 
            || (strcmp(argv[i], "-v2") == 0) 
            || (strcmp(argv[i], "+I") == 0) 
            || (strncmp(argv[i], "-.", 2) == 0)) {
            // clang-format on
            return TRUE;
        }
    }
    return FALSE;
}

// function exec_OCC # 43
void exec_OCC(int argc, char** argv) {
    char spB8[0x400];
    char pad[0x88]; // !

    sprintf(spB8, "%susr/bin/OCC", comp_host_root);
    *argv = spB8;
    execv(spB8, argv);
    error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "could not exec %s", spB8);
}

// function add_cxx_symbol_options # 44
int add_cxx_symbol_options(void) {
    addstr(&execlist, "-cxx");
    if (!D_1000BF90 && (strcmp(LD, "old_ld") != 0)) {
        addstr(&execlist, "-woff");
        addstr(&execlist, "134");
    }
    return 0;
}

static char* D_1000C2E8 = NULL;
static char* D_1000C2EC = NULL;
static char* D_1000C2F0 = NULL; // basename of progname (?)

// function init_curr_dir # 45
// Sets D_1000C2F0 to current executable's basename and D_1000C1D0 to the current working directiory
void init_curr_dir(void) {
    if (D_1000C2F0 == NULL) {
        D_1000C2F0 = strrchr(progname, '/');
        if (D_1000C2F0 == NULL) {
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
void add_static_opt(char* opt) {
    if (!D_1000BF88) {
        addstr(&staticopts, opt);
    }
}

// function record_static_fileset # 48
void record_static_fileset(const char* arg0) {
    int sp28E4;
    FILE* sp28E0;
    FILE* sp28DC;
    int sp28D8;
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

    if ((D_1000BF84[0] == '/') || (D_1000BF80[0] == '\0')) {
        D_1000C2E8 = mkstr(D_1000BF84, NULL);
    } else {
        D_1000C2E8 = mkstr(D_1000BF80, D_1000BF84, NULL);
    }

    D_1000C2EC = mkstr(tmpdir, "cvstatic.fileset", &spBC, NULL);
    spD4 = full_path(arg0);
    spD0 = strlen(spD4);

    if (vflag) {
        fprintf(stderr, "Static fileset: %s %s", spD4, D_1000C2F0);
        for (sp28E4 = 0; sp28E4 < staticopts.length; sp28E4++) {
            fprintf(stderr, " %s", staticopts.entries[sp28E4]);
        }
        fprintf(stderr, "\n");
    }

    sp28E0 = fopen(D_1000C2EC, "w+");
    if (sp28E0 == NULL) {
        error(ERRORCAT_ERROR, 0, 0, "record_static_fileset", 0, "could not open cvstatic fileset temp file %s\n",
              D_1000C2EC);
        perror(D_1000C2F0);
        cleanup();
        exit(1);
    }

    sp28D8 = open(D_1000C2E8, 0x102, 0777);
    if (sp28D8 < 0) {
        error(ERRORCAT_ERROR, 0, 0, "record_static_fileset", 0, "could not open or create cvstatic fileset file %s\n",
              D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }

    if (flock(sp28D8, 2) < 0) {
        error(ERRORCAT_ERROR, 0, 0, "record_static_fileset", 0, "error in locking cvstatic fileset file %s\n",
              D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }

    if (fstat(sp28D8, &sp34) < 0) {
        error(ERRORCAT_ERROR, 0, 0, "record_static_fileset", 0, "could not fstat cvstatic fileset file %s\n",
              D_1000C2E8);
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
        error(ERRORCAT_ERROR, 0, 0, "record_static_fileset", 0, "could not fdopen cvstatic fileset file %s\n",
              D_1000C2E8);
        perror(D_1000C2F0);
        unlink(D_1000C2EC);
        cleanup();
        exit(1);
    }

    while (fgets(spD8, 0x2800, sp28DC) != 0) {
        if ((strncmp(spD8, spD4, spD0) != 0) || !isspace(spD8[spD0])) {
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
    ftruncate(fileno(sp28DC), 0);

    while ((sp28E4 = fread(spD8, 1, 0x2800, sp28E0)) > 0) {
        if ((int)fwrite(&spD8, 1, sp28E4, sp28DC) != sp28E4) {
            error(ERRORCAT_ERROR, 0, 0, "record_static_fileset", 0, "error in writing cvstatic fileset file %s\n",
                  D_1000C2E8);
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
int touch(const char* arg0) {
    time_t curtime = time(NULL);
    struct utimbuf sp34;
    char* str;

    init_curr_dir();
    if (vflag) {
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
    unsigned int len = 0;
    unsigned char ch;

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
size_t quote_shell_arg(const char* p, char* buf) {
    char c;
    int quoted = FALSE;
    size_t len;

    len = quoted_length(p, &quoted);
    if (quoted) {
        *buf++ = '"';
    }

    while ((c = *p++)) { // != 0 does not match
        if ((c == '"') || (c == '\\') || (c == '`') || (c == '$')) {
            *buf++ = '\\';
        }
        *buf++ = c;
    }

    if (quoted) {
        *buf++ = '"';
    }
    return len;
}

// function func_00431A3C # 53
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
static void func_00431B88(FILE* arg0, const char* arg1, int arg2) {
    if (arg2) {
        fputs("CMDLINE=", arg0);
    }
    fprintf(arg0, "%s ", progname);
    if (!cflag) {
        fputs("-c ", arg0);
    }
    if ((srcfiles.length == 1) && cflag) {
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
        error(ERRORCAT_WARNING, NULL, 0, NULL, 0, "cannot open commandfile '%s'\n", tempstr[33]);
    }
}

// function func_00431DD8 # 57
static void func_00431DD8(void) {
    int sp34 = 0;
    int sp30 = 0; // Unused
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
// Search file for the first "----" and move position to the line after it
void skip_old_ii_controls(FILE* arg0) {
    int ch;
    int sp50 = FALSE;

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
// TODO: name vars

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
            error(ERRORCAT_ERROR, NULL, 0, "update_instantiation_info_file", 0, "error in creating file %s\n", sp50);
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
            error(ERRORCAT_ERROR, NULL, 0, "update_instantiation_info_file", 0, "error in renaming %s to %s\n", sp50,
                  sp54);
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
static void func_00432D3C(const char* arg0, int count) {
    int i;
    int identified_segment;
    unsigned int flags;
    int pagesize;
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
