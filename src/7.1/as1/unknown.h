#ifndef UNKNOWN_H
#define UNKNOWN_H

// contains all symbols which will be moved to their own .c and .h files later

typedef int UNK_TYPE;
typedef int* UNK_PTR;

typedef struct UnkAlpha {
    /* 0x00 */ union mips_instruction* unk_00;
    /* 0x04 */ UNK_TYPE unk_04;
    /* 0x08 */ UNK_TYPE unk_08;
    /* 0x0C */ UNK_TYPE unk_0C;
    /* 0x10 */ UNK_TYPE unk_10;
    /* 0x14 */ UNK_TYPE unk_14;
    /* 0x18 */ UNK_TYPE unk_18;
    /* 0x1C */ UNK_TYPE unk_1C;
    /* 0x20 */ UNK_TYPE unk_20;
    /* 0x24 */ UNK_TYPE unk_24;
    /* 0x28 */ UNK_TYPE unk_28;
} UnkAlpha; // size = 0x2C

typedef struct UnkBeta {
    /* 0x00 */ UNK_TYPE unk_00;
    /* 0x04 */ UNK_TYPE unk_04;
    /* 0x08 */ UNK_TYPE unk_08;
    /* 0x0C */ UNK_TYPE unk_0C;
    /* 0x10 */ char unk_10;
    /* 0x14 */ UNK_TYPE unk_14;
} UnkBeta; // size = 0x18

typedef struct UnkBetaArray {
    /* 0x00 */ UnkBeta* array;
    /* 0x04 */ size_t size;    
} UnkBetaArray; // size = 0x08

extern UnkAlpha* memory;
extern int currtextindex;
extern unsigned char sexchange;
extern int* seg_ic;
extern UnkBetaArray rld_list;
extern int nextrld;

void* allocate_check(int size);
void appendtextword(unsigned int, UNK_TYPE, UNK_TYPE, UNK_TYPE, UNK_TYPE);
void* grow_array(size_t* capacity_count, size_t new_count, size_t width, void* ptr, int clear_mem);

#endif
