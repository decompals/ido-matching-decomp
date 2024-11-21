#ifndef MEM_H
#define MEM_H

#include "stdlib.h"

#define ALIGN(x, n) (char*)(((int)(x) + n - 1) & ~(n - 1))

typedef struct MemCtx {
    /* 0x00 */ char** list_start;
    /* 0x04 */ char** current_region;
    /* 0x08 */ char* ptr;
    /* 0x0C */ char* region_end;
    /* 0x10 */ char** list_end;
} MemCtx; // size = 0x14

void* Malloc(size_t size);
void* Calloc(size_t nmemb, size_t size);
void* Realloc(void* ptr, size_t size);
MemCtx* mem_start(void);
void* __mem_alloc(MemCtx* s, size_t size);
int mem_free(MemCtx* s);
size_t mem_usage(MemCtx* s);

#define mem_alloc(mem, size, align) \
    (mem->ptr = ALIGN(mem->ptr, align)) + (size) > mem->region_end ? \
    __mem_alloc(mem, size) : \
    (mem->ptr += (size), mem->ptr - (size))

#endif
