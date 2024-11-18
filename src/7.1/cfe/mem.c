#include "stdlib.h"
#include <stdio.h>

const char header[] = "$Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/targucode/cfe/RCS/mem.c,v 1.2 1994/07/18 00:21:05 dlai Exp $"; 

typedef struct MemCtx {
    /* 0x00 */ char** unk_00;
    /* 0x04 */ char** unk_04;
    /* 0x08 */ char* unk_08;
    /* 0x0C */ char* unk_0C;
    /* 0x10 */ char** unk_10;
} MemCtx; // size = 0x14

int error(int, int, int, char*);
extern char* infile;

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

extern char debug_arr[];
extern FILE* dbgout;

MemCtx* mem_start(void) {
    MemCtx* s;

    s = (MemCtx*)Malloc(sizeof(MemCtx));
    s->unk_00 = Calloc(0x10, 4);
    *s->unk_00 = Calloc(1, 0x1000);
    s->unk_04 = s->unk_00;
    s->unk_08 = *s->unk_00;
    s->unk_0C = s->unk_08 + 0x1000;
    s->unk_10 = s->unk_00 + 0x10;

    if (debug_arr[0x6D] > 0) {
        fprintf(dbgout, "mem_start returns s=%x r=%x c=%x\n", s, s->unk_00, s->unk_08);
    }

    return s;
}

void* __mem_alloc(MemCtx* s, size_t size) {
    if (++s->unk_04 == s->unk_10) {
        size_t count = s->unk_10 - s->unk_00 + 0x10;
        s->unk_00 = Realloc(s->unk_00, count * 4);
        s->unk_10 = s->unk_00 + count;
        s->unk_04 = s->unk_10 - 0x10;
    }

    *s->unk_04 = Calloc(1, size > 0x1000 ? size : 0x1000);
    s->unk_0C = *s->unk_04 + (size > 0x1000 ? size : 0x1000);
    s->unk_08 = *s->unk_04 + size;

    if (debug_arr[0x6D] > 0) {
        fprintf(dbgout, "__mem_alloc returns s=%x r=%x cr=%x d=%x\n", s, s->unk_00, s->unk_04, *s->unk_04);
    }
    return *s->unk_04;
}

int mem_free(MemCtx* s) {
    if (debug_arr[0x6D] > 0) {
        fprintf(dbgout, "mem_free s=%x\n", s);
    }

    s->unk_10 = s->unk_00;
    while (s->unk_10 != s->unk_04) {
        free(*s->unk_10++);
    }
    free(*s->unk_10);
    free(s->unk_00);
    free(s);

    return 0;
}

size_t mem_usage(MemCtx* s) {
    size_t size = (s->unk_04 - s->unk_00) * 0x1000;
    size += s->unk_08 - *s->unk_04;
    return size;
}
