#include "sex.h"

int gethostsex(void) {
    union {
        int word;
        char byte;
    } sex;

    sex.word = 1;
    return sex.byte == 1 ? LITTLEENDIAN : BIGENDIAN;
}
