#ifndef TYPES_H
#define TYPES_H
/* types */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short int s16;
typedef unsigned short int u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long int s64;
typedef unsigned long long int u64;
typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;
typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;
typedef float f32;
typedef double f64;

struct new_binasm {
/* 0x0 */ s32 unk0;
/* 0x5 */ u32 unk4_1: 10;
/* 0x5 */ u32 unk4_2: 6;
/* 0x5 */ u32 unk4_3: 16;
    union {
    u32 unk8;
    struct {
/* 0x8 */ u32 unk8_1 : 7;
/* 0x8 */ u32 unk8_2 : 1;
/* 0x8 */ u32 unk8_3 : 8;
/* 0x8 */ u32 unk8_4 : 2;
/* 0x8 */ u32 unk8_5 : 14;
};
};
/* 0xC */ u32 unkC;
};

struct sym {
/* 0x0 */  struct sym* next;
/* 0x4 */  char* name;
/* 0x8 */  s32 unk8;
/* 0xC */  s32 unkC;
/* 0x10 */ s32 unk10;
/* 0x14 */ s32 unk14;
/* 0x18 */ s32 unk18;
};

u8 *sitype[0x3F] = {
    "label",
    ".sym",
    ".globl",
    ".cpload",
    ".align",
    ".ascii",
    ".asciiz",
    ".byte",
    ".comm",
    ".lcomm",
    ".data",
    ".double",
    ".file",
    ".float",
    ".half",
    ".cprestore",
    ".gpword",
    ".cpadd",
    ".weakext",
    ".loopno",
    ".space",
    ".text",
    ".word",
    "ocode",
    ".end",
    ".sdata",
    ".rdata",
    ".ent",
    ".loc",
    ".bgnb",
    ".endb",
    ".asm0",
    ".set",
    ".cpalias",
    ".repeat",
    ".endr",
    ".lab",
    ".vreg",
    ".mask",
    ".fmask",
    ".err",
    "globabs",
    ".verstamp",
     ".frame",
    ".extended",
    ".extern",
    ".aent",
    ".option",
    ".noalias",
    ".alias",
    ".mtag",
    ".malias",
    ".struct",
    ".livereg",
    ".gjaldef",
    ".gjallive",
    ".gjrlive",
    ".ishift_addr",
    ".irestext",
    ".dword",
    ".prologue",
    ".edata",
    ".alloc",
};

extern struct {
    struct new_binasm* unk0;
    size_t unk4;
} rep_buffer;
void* memset(void*, int, size_t);

struct new_binasm binasm_rec;

#endif /* TYPES_H */
