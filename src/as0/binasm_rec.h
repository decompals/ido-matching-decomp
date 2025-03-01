#ifndef BINASM_H
#define BINASM_H

typedef struct {
    union {
        unsigned unk0; // always symno
        char arr0[4];  // data
    };
    union {
        unsigned unk4;
        struct {
            unsigned unk4_FE_ : 7;
            unsigned unk4_01C0 : 3;
            unsigned unk5_003F : 6;
            unsigned unk6_C0 : 2;
            unsigned unk6_3C_ : 4;
            unsigned unk6_03FE : 9;
            unsigned unk7_0001_ : 1;
        };
        struct {
            unsigned unk4_FFFF_ : 16;
            unsigned unk6_FE : 7;
            unsigned unk6_01FC : 7;
            unsigned unk7_03_ : 2;
        };
    };
    union {
        unsigned unk8;
        struct {
            unsigned unk8_FE : 7;
            unsigned unk8_01FC : 7;
            unsigned unk8_0003C000 : 4;
            unsigned unkA_3F80 : 7;
            unsigned unkB_007F : 7;
        };
        struct {
            unsigned unk8_FFFFC000_ : 18;
            unsigned unkA_3FFF : 14;
        };
    };
    union {
        unsigned unkC;
        struct {
            unsigned unkC_FE : 7;
            unsigned unkC_01FC : 7;
            unsigned unkC_0003 : 2;
        };
    };
} binasm_r;

#endif /* BINASM_H */
