/*
 * @file: code_00412CB0.c
 * @brief: Contains a modified version of some libmld functions.
 */
#include "stdio.h"
#include "stdlib.h"
#include "sys/stat.h"

// External declaration
extern void call_name_and_line(int arg0);

// Function declaration (code_00412CB0.c)
int filesize(FILE** arg0);
void ltoa(int arg0, char* arg1);
void st_error(char* arg0, int arg1, int arg2, int arg3, int arg4);
void st_warning(char* arg0, int arg1, int arg2, int arg3, int arg4);
void st_printf_2(char* arg0, int arg1);
void st_printf_3(char* arg0, int arg1, char* arg2);
void st_internal(char* arg0, int arg1, int arg2, int arg3, int arg4);
int l_addr(int arg0);
int e_addr(int arg0);
int s_addr(int arg0);

// UNUSED
int filesize(FILE** arg0) {
    struct stat buf;
    FILE* temp_v0;

    if (arg0 != NULL) {
        temp_v0 = *arg0;
        if (temp_v0 != NULL) {
            if (fstat(temp_v0->_file, &buf) == 0) {
                return buf.st_size;
            }
        }
    }
    return -1; // End of file
}

void ltoa(int arg0, char* arg1) {
    sprintf(arg1, "%d", arg0);
}

void st_error(char* arg0, int arg1, int arg2, int arg3, int arg4) {
    fprintf(stderr, "libmld--");
    call_name_and_line(1);
    fprintf(stderr, arg0, arg1, arg2, arg3, arg4);
    fprintf(stderr, "\n");
    exit(1);
}

void st_warning(char* arg0, int arg1, int arg2, int arg3, int arg4) {
    fprintf(stderr, "\nlibmld--");
    call_name_and_line(2);
    fprintf(stderr, arg0, arg1, arg2, arg3, arg4);
    fprintf(stderr, "\n");
}

void st_printf_2(char* arg0, int arg1) {
    fprintf(stderr, arg0, arg1);
}

void st_printf_3(char* arg0, int arg1, char* arg2) {
    fprintf(stderr, arg0, arg1, arg2);
}

void st_internal(char* arg0, int arg1, int arg2, int arg3, int arg4) {
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
