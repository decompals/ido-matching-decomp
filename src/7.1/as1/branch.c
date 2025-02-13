#include "common.h"

#define SWAP(a) ( \
    (((a) << 24) & 0xFF000000) | \
    (((a) <<  8) & 0x00FF0000) | \
    (((a) >>  8) & 0x0000FF00) | \
    (((a) >> 24) & 0x000000FF) )
		            
		            
	                

typedef struct UnkGamma {
    /* 0x00 */ UNK_TYPE unk_00;
    /* 0x04 */ UNK_TYPE unk_04;
    /* 0x08 */ UNK_TYPE unk_08;
    /* 0x0C */ UNK_TYPE unk_0C;
    /* 0x10 */ int unk_10;
} UnkGamma; // size >= 0x14

typedef struct UnkBranchStruct1 {
    /* 0x00 */ union mips_instruction unk_00;
    /* 0x04 */ int unk_04;
    /* 0x08 */ UnkGamma* unk_08;
    /* 0x0C */ struct UnkBranchStruct1* next;
} UnkBranchStruct1; // size = 0x10

static UnkBranchStruct1* B_10023B90;
static UnkBranchStruct1* B_10023B94;

void func_0040D2E0(union mips_instruction arg0, int arg1, UnkGamma* arg2) {
    UnkBranchStruct1* temp_v0;

    temp_v0 = allocate_check(sizeof(UnkBranchStruct1));
    if (B_10023B90 == NULL) {
        B_10023B90 = temp_v0;
    } else {
        B_10023B94->next = temp_v0;
    }
    temp_v0->unk_00.word = arg0.word;
    temp_v0->unk_04 = arg1;
    temp_v0->unk_08 = arg2;
    temp_v0->next = NULL;

    B_10023B94 = temp_v0;
}

void gen_br_patches(void) {
    union mips_instruction sp4C;
    UnkBranchStruct1* s3;    

    for (s3 = B_10023B90; s3 != NULL; s3 = s3->next) {
        // override jump target
        sp4C.word = memory[currtextindex].unk_00[s3->unk_04 >> 2].word;
        if (sexchange) {
            sp4C.word = SWAP(sp4C.word);
        }
        sp4C.j_format.target = seg_ic[currtextindex] >> 2;
        if (sexchange) {
            sp4C.word = SWAP(sp4C.word);
        }
        memory[currtextindex].unk_00[s3->unk_04 >> 2].word = sp4C.word;

        sp4C.word = s3->unk_00.word;
        // replace branch-and-link with simple branch
        if (sp4C.i_format.opcode == bcond_op) {
            switch (sp4C.i_format.rt) {
                case bltzal_op:
                    sp4C.i_format.rt = bltz_op;
                    break;
                case bgezal_op:
                    sp4C.i_format.rt = bgez_op;
                    break;
                case bltzall_op:
                    sp4C.i_format.rt = bltzl_op;
                    break;
                case bgezall_op:
                    sp4C.i_format.rt = bgezl_op;
                    break;
            }
        }
        sp4C.i_format.simmediate = 3;
        appendtextword(sp4C.word, 0, 0, 0, 0);
        appendtextword(INST_NOP, 0, 0, 0, 0);

        // make jal 
        sp4C.j_format.opcode = j_op;
        sp4C.j_format.target = (s3->unk_04 + 8) >> 2;        
        if (nextrld >= rld_list.size) {
            rld_list.array = grow_array(&rld_list.size, nextrld, sizeof(*rld_list.array), rld_list.array, FALSE);
        }
        rld_list.array[nextrld].unk_00 = 0;
        rld_list.array[nextrld].unk_04 = seg_ic[currtextindex];
        rld_list.array[nextrld].unk_10 = 6;
        rld_list.array[nextrld].unk_0C = currtextindex;
        rld_list.array[nextrld].unk_08 = 0;
        nextrld++;
        appendtextword(sp4C.word, 0, 0, 0, 0);
        appendtextword(INST_NOP, 0, 0, 0, 0);

        // make another jal
        sp4C.j_format.target = s3->unk_08->unk_10 >> 2;
        if (nextrld >= rld_list.size) {
            rld_list.array = grow_array(&rld_list.size, nextrld, sizeof(*rld_list.array), rld_list.array, FALSE);
        }
        rld_list.array[nextrld].unk_00 = 0;
        rld_list.array[nextrld].unk_04 = seg_ic[currtextindex];
        rld_list.array[nextrld].unk_10 = 6;
        rld_list.array[nextrld].unk_0C = currtextindex;
        rld_list.array[nextrld].unk_08 = 0;
        nextrld++;
        appendtextword(sp4C.word, 0, 0, 0, 0);
        appendtextword(INST_NOP, 0, 0, 0, 0);

    }

    B_10023B90 = B_10023B94 = NULL;
}