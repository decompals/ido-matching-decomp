#include "stdio.h"
#include "string.h"

// write_chars
static void func_00471400(FILE* file, char* string, int arg2) {
    char* ptr;
    char* end;

    if (file->_flag & 2) {
        file->_cnt -= arg2;
        while (file->_cnt < 0) {
            file->_cnt += arg2;
            if (file->_cnt > 0) {
                arg2 -= file->_cnt;
                ptr = file->_ptr;
                end = file->_cnt + string;
                do {
                    *ptr++ = *string++;
                } while (string != end);
                file->_ptr = ptr;
            }

            file->_cnt = -1;
            __flsbuf(*string++, file);
            arg2--;
            if (arg2 == 0) {
                return;
            }
            file->_cnt -= arg2;
        }

        ptr = file->_ptr;
        end = string + arg2;
        do {
            *ptr++ = *string++;
        } while (string != end);
        file->_ptr = ptr;
    }
}

// pad
static void func_00471580(FILE* file, int ch, int arg2) {
    char* ptr;
    char* end;

    if ((file->_flag & 2) && (arg2 > 0)) {
        file->_cnt -= arg2;
        while (file->_cnt < 0) {
            file->_cnt += arg2;
            if (file->_cnt > 0) {
                arg2 -= file->_cnt;
                ptr = file->_ptr;
                end = file->_cnt + ptr;
                do {
                    *ptr++ = ch;
                } while (ptr != end);
                file->_ptr = ptr;
            }

            file->_cnt = -1;
            __flsbuf(ch, file);
            arg2--;
            if (arg2 == 0) {
                return;
            }
            file->_cnt -= arg2;
        }

        ptr = file->_ptr;
        end = ptr + arg2;
        do {
            *ptr++ = ch;
        } while (ptr != end);
        file->_ptr = ptr;
    }
}

void writeln(FILE* file) {
    if (!(file->_flag & 2)) {
        fprintf(stderr, "writeln called on file not open for writing.\n");
        return;
    }
    putc_locked('\n', file);
}

void page(FILE* file) {
    putc_locked('\f', file);
}

void write_char(FILE* file, char ch, int arg2) {
    if (arg2 >= 2) {
        func_00471580(file, ' ', arg2 - 1);
        putc_locked(ch, file);
    } else if (arg2 < -1) {
        putc_locked(ch, file);
        func_00471580(file, ' ', -arg2 - 1);
    } else {
        putc_locked(ch, file);
    }
}

void write_string(FILE* file, char* string, size_t arg2, int arg3) {
    char* ptr;

    if (arg3 == 0) {
        ptr = string + arg2;
        while ((ptr != string) && (ptr[-1] == ' ')) {
            ptr--;
        }
        arg3 = ptr - string;
    } else if (arg2 < (size_t)arg3) {
        func_00471580(file, ' ', arg3 - arg2);
        arg3 = arg2;
    }
    if (arg3 > 0) {
        func_00471400(file, string, arg3);
    }
}

void write_enum(FILE* file, int arg1, char* arg2, int arg3) {
    int sp24 = arg1;

    while (arg1 != 0) {
        while (*arg2++ != '\0') {}
        arg1--;

        if (*arg2 == '\0') {
            fprintf(stderr, "Enumerated value '%d' not within type.\n", sp24);
            return;
        }
    }
    if (*arg2 == ' ') {
        while (*arg2++ == ' ') {}
        arg2--;
    }

    write_string(file, arg2, strlen(arg2), arg3);
}
