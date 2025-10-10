#ifndef UNKNOWN_H
#define UNKNOWN_H

// contains all symbols which will be moved to their own .c and .h files later

#define SET_INTERSECT(x, y) \
    ((((x).unk_00[0] & (y).unk_00[0]) | \
      ((x).unk_00[1] & (y).unk_00[1]) | \
      ((x).unk_00[2] & (y).unk_00[2])) != 0)

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
    /* 0x08 */ struct UnkGamma* unk_08;
    /* 0x0C */ int unk_0C;
    /* 0x10 */ char unk_10;
    /* 0x14 */ UNK_TYPE unk_14;
} UnkBeta; // size = 0x18

typedef struct UnkBetaArray {
    /* 0x00 */ UnkBeta* array;
    /* 0x04 */ size_t size;
} UnkBetaArray; // size = 0x08

typedef struct UnkDelta {
    /* 0x00 */ int unk_00;
    /* 0x04 */ struct UnkDelta* next;
} UnkDelta; // size = 0x08

typedef struct UnkGamma {
    /* 0x00 */ UNK_TYPE unk_00;
    /* 0x04 */ UNK_TYPE unk_04;
    /* 0x08 */ UNK_TYPE unk_08;
    /* 0x0C */ UNK_TYPE unk_0C;
    /* 0x10 */ int unk_10;
    /* 0x14 */ UNK_TYPE unk_14;
    /* 0x18 */ UNK_TYPE unk_18;
    /* 0x1C */ UNK_TYPE unk_1C;
    /* 0x20 */ UNK_TYPE unk_20;
    /* 0x24 */ UNK_TYPE unk_24;
    /* 0x28 */ UNK_TYPE unk_28;
    /* 0x2C */ UnkDelta* unk_2C;
    /* 0x30 */ UNK_TYPE unk_30;
    /* 0x34 */ char unk_34[3];
    /* 0x37 */ char unk_37;
} UnkGamma; // size >= 0x38

typedef struct RegSet {
    /* 0x00 */ int unk_00[3];
} RegSet; // size = 0x0C

typedef struct UnkEpsilon {
    /* 0x00 */ UNK_TYPE unk_00;
    /* 0x04 */ UNK_TYPE unk_04;
    /* 0x08 */ struct UnkEpsilon* next;
    /* 0x0C */ UNK_TYPE unk_0C;
    /* 0x10 */ UNK_TYPE unk_10;
    /* 0x14 */ UNK_TYPE unk_14;
    /* 0x18 */ UNK_TYPE unk_18;
    /* 0x1C */ UNK_TYPE unk_1C;
    /* 0x20 */ UNK_TYPE unk_20;
    /* 0x24 */ RegSet unk_24;
    /* 0x30 */ UNK_TYPE unk_30;
    /* 0x34 */ UNK_TYPE unk_34;
    /* 0x38 */ UNK_TYPE unk_38;
    /* 0x3C */ UNK_TYPE unk_3C;
    /* 0x40 */ UNK_TYPE unk_40;
    /* 0x44 */ int unk_44_0 : 23;
    /* 0x44 */ unsigned char unk_44_23 : 1;
    /* 0x44 */ int unk_44_24 : 3;
    /* 0x44 */ int unk_44_27 : 1;
    /* 0x44 */ int unk_44_28 : 4;
    /* 0x48 */ UNK_TYPE unk_48;
    /* 0x4C */ short unk_4C;
    /* 0x4E */ unsigned short unk_4E;
    /* 0x50 */ UNK_TYPE unk_50;
    /* 0x54 */ unsigned int unk_54;
} UnkEpsilon; // size >= 0x47

typedef struct UnkEta {
    /* 0x00 */ union mips_instruction unk_00;
    /* 0x04 */ UNK_TYPE unk_04;
} UnkEta; // size >= 0x8

// same as UnkEpsilon ??
typedef struct UnkZeta {
    /* 0x00 */ char unk_00[0x4E];
    /* 0x4E */ unsigned short unk_4E;
    /* 0x50 */ UnkEta* unk_50;
    /* 0x54 */ unsigned int unk_54;
} UnkZeta; // size >= 0x54

extern UnkAlpha* memory;
extern int currtextindex;
extern unsigned char sexchange;
extern int* seg_ic;
extern UnkBetaArray rld_list;
extern int nextrld;
extern int picflag;
extern int fixup_count;
extern char tracereorder;
extern unsigned char isa;
extern char bigendian;
extern int debugflag;
extern int gprelsize;
extern char keepflag;
extern int optflag;
extern char verbose;
extern int binasm_count;

UnkZeta* find_branch_target(UnkEpsilon*);
void xfree(void*);
void* xmalloc(size_t size);
void postcerror(char*, int);
void* allocate_check(int size);
void appendtextword(unsigned int, UNK_TYPE, UNK_TYPE, UNK_TYPE, UNK_TYPE);
void* grow_array(size_t* capacity_count, size_t new_count, size_t width, void* ptr, int clear_mem);
int eligible(union mips_instruction);
int cannot_trap(union mips_instruction);
void defuse(union mips_instruction, RegSet*, RegSet*);
extern int idn_for_anon_symbol(void);
extern int idn_for_extern_symbol(char* name);

#endif
