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

void output_inst_bin(binasm* bin, size_t count, binasm* ibuffer, size_t ibufferSize) {
    for (; ibufferSize > 0; ibufferSize--, ibuffer--) {
        if (fwrite(ibuffer, sizeof(binasm), 1, binasm_file) != 1) {
            fprintf(stderr, "ugen: internal error writing binasm to %s:  %s\n", binasm_name, errno < sys_nerr ? sys_errlist[errno] : "(unknown)");
            fprintf(stderr, "suggestion:  you may want to use TMPDIR to change where temporary files are written\n");
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
    }

    if (fwrite(bin, sizeof(binasm), count, binasm_file) != count) {
        fprintf(stderr, "ugen: internal error writing binasm to %s:  %s\n", binasm_name, errno < sys_nerr ? sys_errlist[errno] : "(unknown)");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

/*
* @brief Appends the contents of a source file to a destination file.
*
* @param destPath Path to the destination file
* @param sourcePath Path to the source file
*/
void cat_files(char* destPath, char* sourcePath) {
    char buf[0x2000];
    int destFd;
    int sourceFd; 
    int bytesWritten;
    int bytesRead;

    destFd = open(destPath, O_WRONLY | O_APPEND);
    if (destFd < 0) {
        fprintf(stderr, "ugen: internal: cannot open %s\n", destPath);
        fflush(stderr);
        exit(1);
    }
    sourceFd = open(sourcePath, O_RDONLY);
    if (sourceFd < 0) {
        fprintf(stderr, "ugen: internal: cannot open %s\n", sourcePath);
        fflush(stderr);
        exit(1);
    }
    if (lseek(destFd, 0, SEEK_END) < 0) {
        fprintf(stderr, "ugen: internal: error in seek\n");
        fflush(stderr);
        exit(1);
    }
    for (bytesRead = read(sourceFd, buf, 0x2000); bytesRead != 0; bytesRead = read(sourceFd, buf, 0x2000)) {
        if (bytesRead < 0) {
            fprintf(stderr, "ugen: internal error reading from %s:  %s\n", sourcePath, errno < sys_nerr ? sys_errlist[errno] : "(unknown)");
            fflush(stderr);
            exit(1);
        }
        bytesWritten = write(destFd, buf, (size_t) bytesRead);
        if (bytesWritten != bytesRead) {
            if (errno == 0) {
                write(destFd, buf + bytesWritten, bytesRead - bytesWritten);
            }
            fprintf(stderr, "ugen: internal error writing to %s: ", destPath);

            errno < sys_nerr ?  fprintf(stderr, "%s\n", sys_errlist[errno]) :  fprintf(stderr, "errno is %d\n", errno);
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
    }
    close(destFd);
    close(sourceFd);
}
