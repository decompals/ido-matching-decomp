#ifndef DELTA_INTERNAL_H
#define DELTA_INTERNAL_H 1

#include "delta_runtime.h"

enum _delta_access {
    _DELTA_ACCESS_PUBLIC,
    _DELTA_ACCESS_PROTECTED,
    _DELTA_ACCESS_PRIVATE,
    _DELTA_ACCESS_UNKNOWN
};

enum _delta_alignment {
    _DELTA_BYTE_ALIGNED = 1,
    _DELTA_HALF_ALIGNED = 2,
    _DELTA_WORD_ALIGNED = 4,
    _DELTA_DOUBLE_ALIGNED = 8
};   

struct _delta_base {
    char is_virtual;
    enum _delta_access access;
    ClassSize offset;
    ClassSize vbase_ptr_offset;
    struct __classinfo *base_class;
};

struct _delta_data {
    char is_static;
    char is_main_element;
    enum _delta_access access;
    char *name;
    
    ClassSize size;
    ClassSize offset;
    ClassSize vbase_offset;
    unsigned char bit_field_size;
    unsigned char bit_field_position;

    void *var_ptr;

    void *info;
    struct __classinfo *qualified_class;
    struct __classinfo *declaring_class;

    union {
	struct __voinfo *voinfo_ptr;
	struct __svoinfo *svoinfo_ptr;
    } info_ptr;
};

struct _delta_method {
    char is_static;
    char is_virtual;
    char is_main_element;
    enum _delta_access access;
    char *name;

    ClassSize this_offset;
    ClassSize vtable_offset;
    ClassSize vptr_offset;
    ClassSize vbase_offset;

    void *function_ptr;

    void *info;
    struct __classinfo *qualified_class;
    struct __classinfo *declaring_class;
    struct __classinfo *defining_class;

    struct __moinfo *moinfo_ptr;
};  

#endif /* DELTA_INTERNAL_H */
