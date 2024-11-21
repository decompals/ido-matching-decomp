#include "mem.h"
#include <stdio.h>

#define REGION_SIZE 0x1000

char* ident = "$Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/targucode/cfe/RCS/mem.c,v 1.2 1994/07/18 00:21:05 dlai Exp $";

// TODO move to appropriate place
int error(int, int, int, char*);
extern char* infile;
extern char debug_arr[];
extern FILE* dbgout;

void* Malloc(size_t size) {
    void* ret;
    
    ret = malloc(size);
    if (ret == NULL && size != 0) {
        error(0x40000, 3, -1, infile != NULL ? infile : "");
    }
    return ret;
}

void* Calloc(size_t nmemb, size_t size) {
    void* ret;
    
    ret = calloc(nmemb, size);
    if (ret == NULL && nmemb * size != 0) {
        error(0x40000, 3, -1, infile != NULL ? infile : "");
    }
    return ret;
}

void* Realloc(void* ptr, size_t size) {
    void* ret;
    
    ret = realloc(ptr, size);
    if (ret == NULL && size != 0) {
        error(0x40000, 3, -1, infile != NULL ? infile : "");
    }
    return ret;
}

MemCtx* mem_start(void) {
    MemCtx* s;

    s = (MemCtx*)Malloc(sizeof(MemCtx));
    s->list_start = Calloc(0x10, 4);
    *s->list_start = Calloc(1, REGION_SIZE);
    s->current_region = s->list_start;
    s->ptr = *s->list_start;
    s->region_end = s->ptr + REGION_SIZE;
    s->list_end = s->list_start + 0x10;

    if (debug_arr[0x6D] > 0) {
        fprintf(dbgout, "mem_start returns s=%x r=%x c=%x\n", s, s->list_start, s->ptr);
    }

    return s;
}

void* __mem_alloc(MemCtx* s, size_t size) {
    if (++s->current_region == s->list_end) {
        size_t count = s->list_end - s->list_start + 0x10;
        s->list_start = Realloc(s->list_start, count * 4);
        s->list_end = s->list_start + count;
        s->current_region = s->list_end - 0x10;
    }

    *s->current_region = Calloc(1, size > REGION_SIZE ? size : REGION_SIZE);
    s->region_end = *s->current_region + (size > REGION_SIZE ? size : REGION_SIZE);
    s->ptr = *s->current_region + size;

    if (debug_arr[0x6D] > 0) {
        fprintf(dbgout, "__mem_alloc returns s=%x r=%x cr=%x d=%x\n", s, s->list_start, s->current_region, *s->current_region);
    }
    return *s->current_region;
}

int mem_free(MemCtx* s) {
    if (debug_arr[0x6D] > 0) {
        fprintf(dbgout, "mem_free s=%x\n", s);
    }

    s->list_end = s->list_start;
    while (s->list_end != s->current_region) {
        free(*s->list_end++);
    }
    free(*s->list_end);
    free(s->list_start);
    free(s);

    return 0;
}

size_t mem_usage(MemCtx* s) {
    size_t size = (s->current_region - s->list_start) * REGION_SIZE;
    size += s->ptr - *s->current_region;
    return size;
}
