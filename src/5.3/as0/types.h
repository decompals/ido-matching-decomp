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

struct sym {
/* 0x0 */ struct sym* next;
/* 0x4 */ s32 unk4;
/* 0x8 */ s32 unk8;
/* 0xC */ char unk_0C[4];
/* 0x10 */ s32 unk10;
/* 0x14 */ s32 unk14;
/* 0x18 */ s32 unk18;
};
#endif /* TYPES_H */
