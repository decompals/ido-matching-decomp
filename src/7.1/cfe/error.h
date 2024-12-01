#ifndef ERROR_H
#define ERROR_H

enum ErrorLevels {
    LEVEL_DEFAULT = 0,
    LEVEL_WARNING = 1,
    LEVEL_ERROR = 2,
    LEVEL_FATAL = 3,
    LEVEL_4 = 4,
    LEVEL_6 = 6
};

int error(int mesg, int level, int location, ...);

#endif
