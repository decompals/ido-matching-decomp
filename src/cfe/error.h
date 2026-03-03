#ifndef ERROR_H
#define ERROR_H

enum ErrorLevels {
    LEVEL_DEFAULT = 0,
    LEVEL_WARNING = 1,
    LEVEL_ERROR = 2,
    LEVEL_FATAL = 3,
    LEVEL_SUPPRESSED = 4,
    LEVEL_6 = 6
};

int error(int mesg, enum ErrorLevels level, int location, ...);
int error_init(char** msg_files, FILE* file, int error_mode);
void set_error_mode(int error_mode);
int set_woff(int warning_number);

#endif
