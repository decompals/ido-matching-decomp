/* Handwritten */
#pragma GLOBAL_ASM("asm/functions/cc/__start.s")
#pragma GLOBAL_ASM("asm/functions/cc/_mcount.s")

#include "cc.h"
//#include "inttypes.h"
#include "sex.h"
#include "sys/times.h"

#include "varargs.h"

/* File, -O1 */
static void func_00432C94(void);
void relocate_passes(const char *arg0, const char *arg1, const char *arg2);
char* mkstr();

int fiveflag = 0;
char *runlib = "/";
char *runlib_base = "/";
int irix4 = 0;
int targetsex = BIGENDIAN;






#pragma GLOBAL_ASM("asm/functions/cc/main.s")

#pragma GLOBAL_ASM("asm/functions/cc/process_config.s")
#pragma GLOBAL_ASM("asm/functions/cc/add_info.s")
#pragma GLOBAL_ASM("asm/functions/cc/parse_command.s")


#pragma GLOBAL_ASM("asm/functions/cc/get_host_chiptype.s")
#pragma GLOBAL_ASM("asm/functions/cc/error.s")
#pragma GLOBAL_ASM("asm/functions/cc/relocate_passes.s")


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


#pragma GLOBAL_ASM("asm/functions/cc/compose_G0_libs.s")

#pragma GLOBAL_ASM("asm/functions/cc/compose_reg_libs.s")

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

char* mkstr(va_alist)
va_dcl // K&R syntax
{
    register char* ret;
    register const char* arg;
    register u32 len;
    va_list args;

    len = 1;
    va_start(args);
    while ((arg = va_arg(args, const char*)) != NULL) {
            len += strlen(arg);
    }
    va_end(args);
    
    ret = malloc(len);
    if (ret == NULL) {
        error(1, 0, 0, "mkstr ()", 0x38BC, "out of memory\n");
        if (errno < sys_nerr) {
            error(5, 0, 0, NULL, 0, "%s\n", sys_errlist[errno]);
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

#pragma GLOBAL_ASM("asm/functions/cc/mklist.s")
#pragma GLOBAL_ASM("asm/functions/cc/addstr.s")
#pragma GLOBAL_ASM("asm/functions/cc/addspacedstr.s")
#pragma GLOBAL_ASM("asm/functions/cc/newstr.s")
#pragma GLOBAL_ASM("asm/functions/cc/save_place.s")
#pragma GLOBAL_ASM("asm/functions/cc/set_place.s")
#pragma GLOBAL_ASM("asm/functions/cc/addlist.s")
#pragma GLOBAL_ASM("asm/functions/cc/adduldlist.s")
#pragma GLOBAL_ASM("asm/functions/cc/nodup.s")
#pragma GLOBAL_ASM("asm/functions/cc/getsuf.s")
#pragma GLOBAL_ASM("asm/functions/cc/mksuf.s")
#pragma GLOBAL_ASM("asm/functions/cc/savestr.s")
#pragma GLOBAL_ASM("asm/functions/cc/mktempstr.s")
#pragma GLOBAL_ASM("asm/functions/cc/run.s")
#pragma GLOBAL_ASM("asm/functions/cc/edit_src.s")
#pragma GLOBAL_ASM("asm/functions/cc/get_lino.s")

#pragma GLOBAL_ASM("asm/functions/cc/show_err.s")
#pragma GLOBAL_ASM("asm/functions/cc/handler.s")
#pragma GLOBAL_ASM("asm/functions/cc/cleanup.s")
#pragma GLOBAL_ASM("asm/functions/cc/whats.s")

clock_t time0;
struct tms tm0;

void settimes(void) {
    time0 = times(&tm0);
}

#define CLOCK_TICKS 100

void dotime(const char* programName) {
    clock_t time1; // sp6C;
    clock_t clockTimeDiff;
    f64 milis; // sp60
    f64 seconds; // sp58
    struct tms tm1; //sp48;

    time1 = times(&tm1);
    milis = (f64) (tm1.tms_utime + tm1.tms_cutime - tm0.tms_utime - tm0.tms_cutime) / CLOCK_TICKS;
    seconds = (f64) (tm1.tms_stime + tm1.tms_cstime - tm0.tms_stime - tm0.tms_cstime) / CLOCK_TICKS;
    clockTimeDiff = time1 - time0;
    fprintf(stderr, "%s phase time: %.2fu %.2fs %u:%04.1f %.0f%%\n", programName, milis, seconds, clockTimeDiff / (60 * CLOCK_TICKS), (f64) (clockTimeDiff % (60 * CLOCK_TICKS)) / CLOCK_TICKS, ((milis + seconds) / ((f64) clockTimeDiff / CLOCK_TICKS)) * 100.0);
}

#pragma GLOBAL_ASM("asm/functions/cc/func_0042FD7C.s")
#pragma GLOBAL_ASM("asm/functions/cc/isdir.s")
#pragma GLOBAL_ASM("asm/functions/cc/regular_not_writeable.s")
#pragma GLOBAL_ASM("asm/functions/cc/regular_file.s")

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

#pragma GLOBAL_ASM("asm/functions/cc/func_00430414.s")
#pragma GLOBAL_ASM("asm/functions/cc/force_use_cfront.s")
#pragma GLOBAL_ASM("asm/functions/cc/exec_OCC.s")
#pragma GLOBAL_ASM("asm/functions/cc/add_cxx_symbol_options.s")
#pragma GLOBAL_ASM("asm/functions/cc/init_curr_dir.s")
#pragma GLOBAL_ASM("asm/functions/cc/full_path.s")
#pragma GLOBAL_ASM("asm/functions/cc/add_static_opt.s")
#pragma GLOBAL_ASM("asm/functions/cc/record_static_fileset.s")
#pragma GLOBAL_ASM("asm/functions/cc/touch.s")
#pragma GLOBAL_ASM("asm/functions/cc/add_prelinker_objects.s")
#pragma GLOBAL_ASM("asm/functions/cc/quoted_length.s")
#pragma GLOBAL_ASM("asm/functions/cc/quote_shell_arg.s")
#pragma GLOBAL_ASM("asm/functions/cc/func_00431A3C.s")
#pragma GLOBAL_ASM("asm/functions/cc/func_00431B38.s")
#pragma GLOBAL_ASM("asm/functions/cc/func_00431B88.s")
#pragma GLOBAL_ASM("asm/functions/cc/func_00431D00.s")
#pragma GLOBAL_ASM("asm/functions/cc/func_00431DD8.s")

#define EOF	(-1) // can go when headers in

// Search file for the first "----" and move position to the line after it
void skip_old_ii_controls(FILE* arg0) {
    s32 ch;
    s32 sp50 = FALSE;

    ch = getc_locked(arg0);
    while (ch != EOF) {
        if (ch == '-' 
            && (ch = getc_locked(arg0)) == '-' 
            && (ch = getc_locked(arg0)) == '-' 
            && (ch = getc_locked(arg0)) == '-') {
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

// path/to/file -> path/to/ii_files/file.ii
// path/to/file.o -> path/to/ii_files/file.ii
char* make_ii_file_name(const char* arg0) {
    char* sp2C; // basename
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

// TODO: type of error(), name vars
int vflag = 0;
char *D_1000C2F0 = "";

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
            error(1, NULL, NULL, "update_instantiation_info_file", NULL, "error in creating file %s\n", sp50);
            perror(D_1000C2F0);
            cleanup();
            exit(1);
        }
        skip_old_ii_controls(sp4C);
        func_00431B88(sp48, arg0, 1);

        while ((sp44 = getc_locked(sp4C)) != -1) {
            putc_locked(sp44, sp48);
        }

        fclose(sp4C);
        fclose(sp48);

        if (rename(sp50, sp54) < 0) {
            error(1, NULL, NULL, "update_instantiation_info_file", NULL, "error in renaming %s to %s\n", sp50, sp54);
            perror(D_1000C2F0);
            cleanup();
            exit(1);
        }
    }
    free(sp54);
    free(sp50);
}



int func_00432940(pid_t arg0) {
    int fd; // sp29C
    char pathname[20]; // sp288
    prstatus_t status; // sp68
    int sp64 = 0; // set and not used
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

static int B_1000EC98[2];

// test pipe read
void func_00432BDC(void) {
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



extern int getpagesize(void);
static prmap_sgi_t B_1000CAC0[100];
s32 memory_flag = 0;

void func_00432D3C(const char* arg0, s32 count) {
    s32 i;
    s32 identified_segment;
    u32 flags;
    s32 pagesize;
    u32 text_size;
    u32 data_size;
    u32 brk_size;
    u32 stack_size;
    u32 so_text_size;
    u32 so_data_size;
    u32 so_brk_size;
    u32 mmap_size;
    s32 memflag;

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
        
        if ((flags == (MA_READ | MA_WRITE)) 
            || (flags == MA_READ) 
            || (flags == (MA_READ | MA_WRITE | MA_SHARED)) 
            || (flags == (MA_READ | MA_SHARED))) {
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
            fprintf(stderr, "pr_vaddr[%d]= %lx\n", i,  B_1000CAC0[i].pr_vaddr);
            fprintf(stderr, "pr_size[%d]= %lx\n", i,   B_1000CAC0[i].pr_size);
            fprintf(stderr, "pr_off[%d]= %lx\n", i,    B_1000CAC0[i].pr_off);
            fprintf(stderr, "pr_mflags[%d]= %lx\n", i, B_1000CAC0[i].pr_mflags);
            fprintf(stderr, "pr_vsize[%d]= %lx\n", i,  B_1000CAC0[i].pr_vsize);
            fprintf(stderr, "pr_psize[%d]= %lx\n", i,  B_1000CAC0[i].pr_psize);
            fprintf(stderr, "pr_wsize[%d]= %lx\n", i,  B_1000CAC0[i].pr_wsize);
            fprintf(stderr, "pr_rsize[%d]= %lx\n", i,  B_1000CAC0[i].pr_rsize);
            fprintf(stderr, "pr_msize[%d]= %lx\n", i,  B_1000CAC0[i].pr_msize);
            fprintf(stderr, "pr_dev[%d]= %lx\n", i,    B_1000CAC0[i].pr_dev);
            fprintf(stderr, "pr_ino[%d]= %lx\n", i,    B_1000CAC0[i].pr_ino);
            fprintf(stderr, "\n");
        }
    }
    
    fprintf(stderr, "%s phase mem: %dT %dD %dB %dS %dt %dd %db %dm= %dK\n", \
        arg0, \
        text_size / 0x400, data_size / 0x400, brk_size / 0x400, stack_size / 0x400, \
        so_text_size / 0x400, so_data_size / 0x400, so_brk_size / 0x400, mmap_size / 0x400, \
        (text_size + data_size + brk_size + stack_size 
        + so_text_size + so_data_size + so_brk_size + mmap_size) / 0x400);

    if (memflag) {
        fprintf(stderr, "text_size= %d Kbytes\n", text_size / 0x400);
        fprintf(stderr, "data_size= %d Kbytes\n", data_size / 0x400);
        fprintf(stderr, "brk_size= %d Kbytes\n", brk_size / 0x400);
        fprintf(stderr, "stack_size= %d Kbytes\n", stack_size / 0x400);
        fprintf(stderr, "so_text_size= %d Kbytes\n", so_text_size / 0x400);
        fprintf(stderr, "so_data_size= %d Kbytes\n", so_data_size / 0x400);
        fprintf(stderr, "so_brk_size= %d Kbytes\n", so_brk_size / 0x400);
        fprintf(stderr, "mmap_size= %d Kbytes\n", mmap_size / 0x400);
        fprintf(stderr, "TOTAL_SIZE= %d Kbytes\n", \
            (
            + text_size 
            + data_size 
            + brk_size 
            + stack_size 
            + so_text_size 
            + so_data_size 
            + so_brk_size 
            + mmap_size
            ) / 0x400);
    }
}

// Prepends "--" to a string by copying.
char* func_00433534(const char* arg0) {
    char* ret = (char*)malloc(strlen(arg0) + 3);

    ret[0] = '-';
    ret[1] = '-';
    ret[2] = '\0';
    strcat(ret, arg0);

    return ret;
}






/* File boundary, -O2 */

// gethostsex
