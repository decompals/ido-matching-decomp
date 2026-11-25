#ifndef ERROR_H
#define ERROR_H

enum ErrorLevels { LEVEL_DEFAULT, LEVEL_WARNING, LEVEL_ERROR, LEVEL_FATAL, LEVEL_SUPPRESSED, LEVEL_5, LEVEL_6 };

typedef enum ErrorDefaultClass {
    ERRCLASS_ALWAYS_ERROR,
    ERRCLASS_ALWAYS_WARNING,
    ERRCLASS_ALWAYS_FATAL,
    ERRCLASS_STRICT_ANSI_ERROR,
    ERRCLASS_DISABLED,
    ERRCLASS_ANSI_WARNING,
    ERRCLASS_ANSI_ERROR,
    ERRCLASS_MAX
} ErrorDefaultClass;

enum ErrorModes { ERROR_MODE_KR, ERROR_MODE_ANSI, ERROR_MODE_XANSI, ERROR_MODE_MAX };

int error(int mesg, enum ErrorLevels level, int location, ...);
int error_init(char** msg_files, FILE* file, int error_mode);
void set_error_mode(int error_mode);
int set_woff(int warning_number);
void error_flush(int arg0);

#endif
