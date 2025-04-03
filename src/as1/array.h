#ifndef DYNARRAY_H
#define DYNARRAY_H

#define ARRAY_OF(type) DynArray##type
#define ARRAY_OF_INTERNAL(type) DynArray_Internal##type

#define ARRAY_AT(a, index) a.data^[index]
#define ARRAY_GROW(a, newsize) \
    if newsize >= a.size then \
        a.data := grow_array(a.size, newsize, sizeof(ARRAY_AT(a, 0)), a.data, false)

#define ARRAY_DECLARE(type) \
    ARRAY_OF_INTERNAL(type) = array [0..0] of type; \
    ARRAY_OF(type) = record \
        data: ^ARRAY_OF_INTERNAL(type); \
        size: cardinal; \
    end

#endif
