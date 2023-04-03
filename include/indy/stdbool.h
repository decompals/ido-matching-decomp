#ifndef __STDBOOL_H__
#define __STDBOOL_H__
/*
#ifndef __c99
#error This header file is to be used only for c99 mode compilations
#else
*/

/* undefine if already defined by user */

#undef bool
#undef true
#undef false
#undef __bool_true_false_are_defined

#define bool    _Bool
#define true    1
#define false   0
#define __bool_true_false_are_defined 1

//#endif /* __C99 */

#endif /* __STDBOOL_H__ */
