/**
 * @file sex.c
 * @brief Function to determine host endian, which for some reason early Unix thought it was a good idea to call "sex".
 */
#include "sex.h"

/**
 * Write to a word and read as a byte to determine host endian
 *
 * File: mld/sex.c
 * Address: 0x00436F80
 * VROM: 0x036F80
 * Size: 0x30
 */
int gethostsex(void) {
    // Not typedefing this since only used once
    union {
        int word;
        signed char byte;
    } sex;

    sex.word = 1;
    if (sex.byte == 1) {
        return LITTLEENDIAN;
    } else {
        return BIGENDIAN;
    }
}
