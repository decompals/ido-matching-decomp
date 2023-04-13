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


struct binasm {
    union {
        u32 unk0;
        u8 arr0[4];
    };
    union {
        u32 unk4;
        struct {
            u32 unk4_FE_ : 7;
            u32 unk4_01C0 : 3;
            u32 unk5_003F : 6;
            u32 unk6_C0 : 2;
            u32 unk6_3C_ : 4;
            u32 unk6_03FE : 9;
            u32 unk7_0001_ : 1;
        };
        struct {
            u32 unk4_FFFF_ : 16;
            u32 unk6_FE: 7;
            u32 unk6_01FC : 7;
            u32 unk7_03_ : 2;
        };
    };
    union {
        u32 unk8;
        struct {
            u32 unk8_FE : 7;
            u32 unk8_01FC : 7;
            u32 unk8_0003C000 : 4;
            u32 unkA_3F80 : 7;
            u32 unkB_007F : 7;
        };
        struct {
            u32 unk8_FFFFC000_ : 18;
            u32 unkA_3FFF : 14;
        };
    };
    union {
        u32 opt;
        struct {
            u32 unkC_FE : 7;
            u32 unkC_01FC : 7;
            u32 unkC_0003 : 2;
        };
    };
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

struct _struct_asm_info {
    /* 0x0 */ char* name;
    /* 0x4 */ u32 unk4_FE : 7;
    /* 0x4 */ u32 unk4_1FFFFFF_ : 0x19;
};

extern struct {
    struct binasm* unk0;
    size_t unk4;
} rep_buffer;
void* memset(void*, int, size_t);

#if 0
//From libmld
typedef struct {
	unsigned long	rfd; /* index into the file table */
	unsigned long	index; /* index int sym/aux/iss tables */
} DNR;
#endif

struct RETst_pext_iext {
    char unk_0[4];
    s32 unk_4;
    char unk_8[4];
    struct {
        u32 unkC_FC : 6;
        u32 unkC_03E0 : 5;
        u32 unkC_1FFFFF_ : 21;
    };
};

struct _struct_asm_info_0x8 {
    /* 0x0 */ char* name;
    /* 0x4 */ u32 unk4;
};


extern struct binasm binasm_rec;
extern s32 gform_extn;

#endif /* TYPES_H */
