#include "common.h"

char* ident = "$Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/targucode/cfe/RCS/modes.c,v 1.1 1992/07/29 18:45:34 wsj Exp $";

void init_options(void) {
    options[OPTION_DOLLAR] = FALSE;
    options[OPTION_VERBOSITY] = VERBOSE_FLAG_1 | VERBOSE_FLAG_2;
    options[OPTION_SIGNED] = FALSE;
    options[OPTION_ENDIANNESS] = 1;
    options[OPTION_ANSI_MODE] = 0;
    options[OPTION_T_LEVEL] = 50;
    options[OPTION_FRAMEPOINTER] = FALSE;
    options[OPTION_MIPS_GEN] = 1;
}
