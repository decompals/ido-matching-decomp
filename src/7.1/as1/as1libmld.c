/******************************************************************************
* @file: as1libmld.c
* @brief: Simmiliar to as0, contains a modified version of some libmld functions
*******************************************************************************/
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/stat.h"
#include "as1/types.h"
#include "as1/protos.h"

#define EOF -1

int filesize(FILE** file) {
    struct stat buf;

    if (file != NULL) {
        if (*file != NULL) {
            if (fstat((*file)->_file, &buf) == 0) {
                return buf.st_size;
            }
        }
    }
    return EOF;
}

void ltoa(s32 src, const char* dest) {
    sprintf(dest, "%d", src);
}

void st_error(const char* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    fprintf(stderr, "libmld--");
    call_name_and_line(1);
    fprintf(stderr, arg0, arg1, arg2, arg3, arg4);
    fprintf(stderr, "\n");
    exit(1);
}

void st_warning(const char* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    fprintf(stderr, "\nlibmld--");
    call_name_and_line(2);
    fprintf(stderr, arg0, arg1, arg2, arg3, arg4);
    fprintf(stderr, "\n");
}

void st_printf_2(s32 arg0, s32 arg1) {
    fprintf(stderr, arg0, arg1);
}

void st_printf_3(s32 arg0, s32 arg1, s32 arg2) {
    fprintf(stderr, arg0, arg1, arg2);
}

void st_internal(const char* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    fprintf(stderr, "libmld--");
    call_name_and_line(0);
    fprintf(stderr, arg0, arg1, arg2, arg3, arg4);
    fprintf(stderr, "\n");
    exit(1);
}

int l_addr(int arg0) {
   return arg0;
}

int e_addr(int arg0) {
  return arg0;
}

int s_addr(int arg0) {
  return arg0;
}
