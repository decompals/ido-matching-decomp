#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "unistd.h"

static int UgetBuf[4096];
static int UgetPos;
static int UputBuf[4096];
static int UputPos;
static char UgetPath[1024];
static char UputPath[1024];
static int* UgetBufptr = UgetBuf;
static int UgetBufLen = -1;
static int UgetFd = -1;
static int UputFd = -1;

void uputinit(char* path) {
    char* pos;

    for (pos = UputPath; 
        pos < UputPath + 1024 
        && *path != '\0' 
        && *path != ' '; 
        pos++, path++) {
        *pos = (signed)*path;
    }
    *pos = '\0';
    
    if (UputPath[0] != '\0') {
        if ((UputFd = open(UputPath, 0x301, 0666)) < 0) {
            perror(UputPath);
            exit(EXIT_FAILURE);
        }
    }
}

void uputinitfd(int fd) {
    UputFd = fd;
}

void uputint(int arg0) {
    if (UputFd < 0) {
        fprintf(stderr, "uput: output file not initialized\n");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    if (UputPos >= 0x1000) {
        if (write(UputFd, &UputBuf, 0x4000U) != 0x4000) {
            perror("writing out file");
            exit(EXIT_FAILURE);
        }
        UputPos = 0;
        UputPos = 0;
    }
    UputBuf[UputPos] = arg0;
    UputPos++;
}

void uputflush(void) {
    if (UputFd < 0) {
        fprintf(stderr, "uput: output file not initialized\n");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    if (write(UputFd, UputBuf, UputPos * 4) != (UputPos * 4)) {
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
        pos < UgetPath + 1024 
        && *path != '\0' 
        && *path != ' '; 
        pos++, path++) {
        *pos = (signed)*path;
    }
    *pos = '\0';
    
    if (UgetPath[0] != '\0') {
        if ((UgetFd = open(UgetPath, 0, 0)) < 0) {
            perror(UgetPath);
            exit(EXIT_FAILURE);
        }
    }
}

void ugetinitfd(int fd) {
    UgetFd = fd;
}

void ugetbufinit(int *buf, int len_bytes) {
    UgetFd = 0xFFFF;
    UgetBufptr = buf;
    UgetBufLen = len_bytes / 4;
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
            UgetBufLen = read(UgetFd, UgetBufptr, 0x4000U);
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


