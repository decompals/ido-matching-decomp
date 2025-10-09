#include "errno.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "fcntl.h"
#include "unistd.h"
#include "cmplrs/binasm.h"

static FILE* binasm_file;
static int unused;
static char binasm_name[128];

void open_bin_file(char* fileName) {
    strcpy(binasm_name, fileName); // ! @bug: this can overflow binasm_name!
    binasm_file = fopen(fileName, "w");
    if (binasm_file == NULL) {
        fprintf(stderr, "ugen: internal error opening %s:  %s\n", 
            fileName, errno < sys_nerr ? sys_errlist[errno] : "(unknown)");
        exit(EXIT_FAILURE);
    }
}

void close_bin_file(void) {
    fclose(binasm_file);
}

void output_inst_bin(binasm* arg0, size_t arg1, binasm* arg2, size_t arg3) {
    for (; arg3 != 0; arg3--, arg2--) {
        if (fwrite(arg2, sizeof(binasm), 1, binasm_file) != 1) {
            fprintf(stderr, "ugen: internal error writing binasm to %s:  %s\n", binasm_name, errno < sys_nerr ? sys_errlist[errno] : "(unknown)");
            fprintf(stderr, "suggestion:  you may want to use TMPDIR to change where temporary files are written\n");
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
    }

    if (fwrite(arg0, sizeof(binasm), arg1, binasm_file) != arg1) {
        fprintf(stderr, "ugen: internal error writing binasm to %s:  %s\n", binasm_name, errno < sys_nerr ? sys_errlist[errno] : "(unknown)");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void cat_files(char* arg0, char* arg1) {
    char buf[0x2000];
    int fd;
    int sp50; 
    int temp_v0_3;
    int var_v0;

    fd = open(arg0, 9);
    if (fd < 0) {
        fprintf(stderr, "ugen: internal: cannot open %s\n", arg0);
        fflush(stderr);
        exit(1);
    }
    sp50 = open(arg1, 0);
    if (sp50 < 0) {
        fprintf(stderr, "ugen: internal: cannot open %s\n", arg1);
        fflush(stderr);
        exit(1);
    }
    if (lseek(fd, 0, 2) < 0) {
        fprintf(stderr, "ugen: internal: error in seek\n");
        fflush(stderr);
        exit(1);
    }
    for (var_v0 = read(sp50, &buf, 0x2000U); var_v0 != 0; var_v0 = read(sp50, &buf, 0x2000U)) {
            if (var_v0 < 0) {
                fprintf(stderr, "ugen: internal error reading from %s:  %s\n", arg1, errno < sys_nerr ? sys_errlist[errno] : "(unknown)");
                fflush(stderr);
                exit(1);
            }
            temp_v0_3 = write(fd, &buf, (size_t) var_v0);
            if (temp_v0_3 != var_v0) {
                if (errno == 0) {
                    write(fd, buf + temp_v0_3, var_v0 - temp_v0_3);
                }
                fprintf(stderr, "ugen: internal error writing to %s: ", arg0);

                errno < sys_nerr ?  fprintf(stderr, "%s\n", sys_errlist[errno]) :  fprintf(stderr, "errno is %d\n", errno);
                fflush(stderr);
                exit(EXIT_FAILURE);
            }
        }
    close(fd);
    close(sp50);
}
