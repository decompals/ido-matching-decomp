/*
* @file: as0libmld.c
* @brief: Contains a modified version of some libmld functions.
*/

#include "stdio.h"
#include "types.h"

void ltoa(s32 arg0, u8* dest) {
    sprintf(dest, "%d", arg0);
}

void st_error(u8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    fprintf(stderr, "libmld--");
    call_name_and_line(1);
    fprintf(stderr, arg0, arg1, arg2, arg3, arg4);
    fprintf(stderr, "\n");
    exit(1);
}

void st_warning(u8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    fprintf(stderr, "\nlibmld--");
    call_name_and_line(2);
    fprintf(stderr, arg0, arg1, arg2, arg3, arg4);
    fprintf(stderr, "\n");
}


void st_printf_2(u8* arg0, s32 arg1) {
    fprintf(stderr, arg0, arg1);
}

void st_printf_3(u8* arg0, s32 arg1, u8* arg2) {
    fprintf(stderr, arg0, arg1, arg2);
}

void st_internal(u8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    fprintf(stderr, "libmld--");
    call_name_and_line(0);
    fprintf(stderr, arg0, arg1, arg2, arg3, arg4);
    fprintf(stderr, "\n");
    exit(1);
}

s32 l_addr(s32 arg0) {
    return arg0;
}

s32 e_addr(s32 arg0) {
    return arg0;
}

s32 s_addr(s32 arg0) {
    return arg0;
}

