#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "unistd.h"
#include "sys/stat.h"
#include "cmplrs/usys.h"

#define U_BUF_LEN 4096

#define UPUT_FD_FLAGS (O_CREAT | O_TRUNC | O_WRONLY)
#define UPUT_FD_MODE  0666

static int UgetBuf[U_BUF_LEN];
static int UgetPos;
static int UputBuf[U_BUF_LEN];
static int UputBufLen;
static char UgetPath[Filenamelen];
static char UputPath[Filenamelen];
static int* UgetBufptr = UgetBuf;
static int UgetBufLen = -1;
static int UgetFd = -1;
static int UputFd = -1;

 
void uputinit(char* path) {
    char* pos;

    // Delete path spaces
    for (pos = UputPath; 
        pos < &UputPath[Filenamelen] 
        && *pos != '\0' 
        && *pos != ' '; 
        pos++, path++) {
        *pos = (signed)*path;
    }
    *pos = '\0';
    
    if (UputPath[0] != '\0') {
        if (UputFd = open(UputPath, UPUT_FD_FLAGS, UPUT_FD_MODE) < 0) {
            perror(UputPath);
            exit(EXIT_FAILURE);
        }
    }
}

void uputinitfd(int fd) {
    UputFd = fd;
}

void uputint(int val) {
    if (UputFd < 0) {
        fprintf(stderr, "uput: output file not initialized\n");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    if (UputBufLen >= U_BUF_LEN) {
        if (write(UputFd, UputBuf, U_BUF_LEN * 4) != U_BUF_LEN * 4) {
            perror("writing out file");
            exit(EXIT_FAILURE);
        }
        UputBufLen = 0;
    }
    UputBuf[UputBufLen++] = val;
}

void uputflush(void) {
    if (UputFd < 0) {
        fprintf(stderr, "uput: output file not initialized\n");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    if (write(UputFd, UputBuf, UputBufLen * 4) != (UputBufLen * 4)) {
        perror("writing out file");
        exit(EXIT_FAILURE);
    }
}

void uputclose(void) {
    uputflush();
    close(UputFd);
    UputFd = -1;
}

void uputkill(void) {
    if (UputFd < 0) {
        fprintf(stderr, "uput: output file not initialized\n");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    if (UputPath[0] != '\0') {
        unlink(UputPath);
    } else {
        fprintf(stderr, "uput: cannot unlink because uputinitfd was used\n");
        fflush(stderr);
    }
}

void ugetinit(char* path) {
    char* pos;

    for (pos = UgetPath; 
        pos < &UgetPath[Filenamelen]
        && *path != '\0' 
        && *path != ' '; 
        pos++, path++) {
        *pos = (signed)*path;
    }
    *pos = '\0';
    
    if (UgetPath[0] != '\0') {
        if ((UgetFd = open(UgetPath, O_RDONLY, 0)) < 0) {
            perror(UgetPath);
            exit(EXIT_FAILURE);
        }
    }
}

void ugetinitfd(int fd) {
    UgetFd = fd;
}

void ugetbufinit(int *buf, int lenBytes) {
    UgetFd = 0xFFFF;
    UgetBufptr = buf;
    UgetBufLen = lenBytes / 4;
    UgetPos = 0;
}

int ugetint(void) {
    if (UgetFd < 0) {
        fprintf(stderr, "uget: input file not initialized\n");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }

    if (UgetPos >= UgetBufLen) {
        if (UgetFd == 0xFFFF) {
            if (UgetBufLen > 0) {
                UgetBufLen = 0;
            } else {
                fprintf(stderr, "read too much from get buffer\n");
                exit(EXIT_FAILURE);
            }
        } else {
            UgetBufLen = read(UgetFd, UgetBufptr, U_BUF_LEN * 4);
            if (UgetBufLen < 0) {
                perror("reading in file");
                exit(EXIT_FAILURE);
            }
            if ((UgetBufLen & 3)) {
                fprintf(stderr, "input buffer on non-int boundry\n");
                exit(EXIT_FAILURE);
            }
        }
        UgetPos = 0;
        UgetBufLen = UgetBufLen / 4;
        UgetPos = 0;
    }
    return UgetBufptr[UgetPos++];
}

int ugeteof(void) {
    ugetint();
    if (UgetBufLen == 0) {
        return 1;
    }
    
    UgetPos--;
    return 0;
}

void ugetclose(void) {
    if (UgetFd < 0) {
        fprintf(stderr, "uget: input file not initialized\n");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    if (UgetFd != 0xFFFF) {
        close(UgetFd);
    }
    UgetFd = -1;
}


