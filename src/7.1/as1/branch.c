#include "common.h"

#define SWAP(a) ( \
    (((a) << 24) & 0xFF000000) | \
    (((a) <<  8) & 0x00FF0000) | \
    (((a) >>  8) & 0x0000FF00) | \
    (((a) >> 24) & 0x000000FF) )
		            
typedef struct UnkBranchStruct1 {
    /* 0x00 */ union mips_instruction unk_00;
    /* 0x04 */ int unk_04;
    /* 0x08 */ UnkGamma* unk_08;
    /* 0x0C */ struct UnkBranchStruct1* next;
} UnkBranchStruct1; // size = 0x10

static UnkBranchStruct1* B_10023B90;
static UnkBranchStruct1* B_10023B94;

static void func_0040D2E0(unsigned int arg0, int arg1, UnkGamma* arg2) {
    UnkBranchStruct1* temp_v0;

    temp_v0 = allocate_check(sizeof(UnkBranchStruct1));
    if (B_10023B90 == NULL) {
        B_10023B90 = temp_v0;
    } else {
        B_10023B94->next = temp_v0;
    }
    temp_v0->unk_00.word = arg0;
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

        // make jump 
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

        // make another jump
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

static int func_0040D8A4(union mips_instruction* arg0, int arg1, int arg2) {
    int sp24;
    union mips_instruction spA8;
    int spA4;    
    char sp28[124];    

    sp24 = arg1 - arg2 - 4;
    spA8.word = arg0->word;
    if (sp24 & 3) {
        postcerror("branch target should be multiple of 4", 2);
    }

    if (sp24 / 4 < -0x8000 || !(sp24 / 4 < 0x7FFF)) {
        if (spA8.i_format.opcode == beq_op && spA8.i_format.rs == 0 && spA8.i_format.rt == 0) {
            // ba
            spA4 = 1;
            spA8.j_format.opcode = j_op;
        } else {
            spA4 = 2;
            if (spA8.i_format.opcode == bcond_op &&
                (spA8.i_format.rt == bltzal_op ||
                 spA8.i_format.rt == bgezal_op ||
                 spA8.i_format.rt == bltzall_op ||
                 spA8.i_format.rt == bgezall_op)
            ) {
                spA8.j_format.opcode = jal_op;
            } else {
                spA8.j_format.opcode = j_op;
            }
        }
        spA8.j_format.target = 0;
    } else {
        spA4 = 0;
        spA8.i_format.simmediate = sp24 / 4;
    }

    arg0->word = spA8.word;

    if (spA4 != 0 && picflag == 2) {
        sprintf(sp28, "Branch at 0x%x has out of range target; recompile with -Wb,-force_branch_fixup", arg2);
        postcerror(sp28, 1);
    }

    return spA4;
}

void do_forward_branches(UnkGamma* arg0, int arg1) {
    UnkDelta* s3 = arg0->unk_2C;
    int s5;
    union mips_instruction s1;
    union mips_instruction sp58;    
    UnkDelta* tmp;

    if (s3 != NULL) {
        fixup_count--;
        do {
            s1.word = memory[arg1].unk_00[s3->unk_00 >> 2].word;
            if (sexchange) {
                s1.word = SWAP(s1.word);
            }

            sp58.word = s1.word;
            s5 = func_0040D8A4(&sp58, seg_ic[currtextindex], s3->unk_00);
            if (sexchange) {
                sp58.word = SWAP(sp58.word);
            }
            memory[arg1].unk_00[s3->unk_00 >> 2].word = sp58.word;

            if (s5 != 0) {
                if (nextrld >= rld_list.size) {
                    rld_list.array = grow_array(&rld_list.size, nextrld, sizeof(*rld_list.array), rld_list.array, FALSE);
                }
                rld_list.array[nextrld].unk_00 = 0;
                rld_list.array[nextrld].unk_04 = s3->unk_00;
                rld_list.array[nextrld].unk_10 = 6;
                rld_list.array[nextrld].unk_0C = arg1;
                if (s5 == 2) {
                    rld_list.array[nextrld].unk_08 = NULL;
                } else {
                    rld_list.array[nextrld].unk_08 = arg0;
                }
                nextrld++;
                if (s5 == 2) {
                    func_0040D2E0(s1.word, s3->unk_00, arg0);
                }
            }

            tmp = s3;
            s3 = s3->next;
            xfree(tmp);
        } while (s3 != NULL);
    }
}

void do_handle_branchop(UnkGamma* arg0, union mips_instruction* arg1, int* arg2) {
    int unused;
    int t1;
    union mips_instruction sp2C;    
    UnkDelta* d;
    

    if (arg0->unk_37 != 0) {
        sp2C.word = arg1->word;
        t1 = func_0040D8A4(arg1, arg0->unk_10, seg_ic[currtextindex]);

        if (t1 != 0) {
            *arg2 = nextrld;
            if (nextrld >= rld_list.size) {
                rld_list.array = grow_array(&rld_list.size, nextrld, sizeof(*rld_list.array), rld_list.array, FALSE);
            }
            rld_list.array[nextrld].unk_00 = 0;
            rld_list.array[nextrld].unk_10 = 6;
            rld_list.array[nextrld].unk_08 = NULL;
            if (t1 == 2) {
                rld_list.array[nextrld].unk_0C = currtextindex;
                rld_list.array[nextrld].unk_04 = seg_ic[currtextindex];                
                *arg2 = 0;
            }
            nextrld++;

            if (t1 == 2) {
                func_0040D2E0(sp2C.word, seg_ic[currtextindex], arg0);
            }

            if (tracereorder) {
                printf("backward branch at word %d becomes jump\n", seg_ic[currtextindex] / 4);
            }
        }
    } else {
        if (arg0->unk_2C == NULL) {
            fixup_count++;
        }

        d = allocate_check(sizeof(UnkDelta));
        d->unk_00 = seg_ic[currtextindex];
        d->next = arg0->unk_2C;
        arg0->unk_2C = d;
    }
}

void do_branch_opt(UnkEpsilon* arg0_) {
    UnkEpsilon* arg0;
    UnkZeta* v0;
    int v1;
    RegSet sp60;
    RegSet sp54;
    union mips_instruction sp50;

    for (arg0 = arg0_; arg0 != NULL; arg0 = arg0->next) {
        if (arg0->unk_44_23) {
            v0 = find_branch_target(arg0);
            if (v0 != NULL && v0->unk_4E != 0 && v0->unk_50->unk_04 == 0 && eligible(v0->unk_50->unk_00)) {
                if (isa >= 2 || arg0->unk_44_27) {
                    v1 = TRUE;
                } else {
                    defuse(v0->unk_50->unk_00, &sp60, &sp54);
                    v1 = arg0->next != NULL && !SET_INTERSECT(arg0->next->unk_24, sp60) && cannot_trap(v0->unk_50->unk_00);
                }

                if (v1) {
                    memory[currtextindex].unk_00[(arg0->unk_54 >> 2) + arg0->unk_4E - 1].word = memory[currtextindex].unk_00[v0->unk_54 >> 2].word;

                    sp50.word = memory[currtextindex].unk_00[(arg0->unk_54 >> 2) + arg0->unk_4E - 2].word;
                    if (sexchange) {
                        sp50.word = SWAP(sp50.word);
                    }
                    sp50.i_format.simmediate++;

                    if (isa >= 2 && !arg0->unk_44_27) {
                        if (sp50.i_format.opcode == bcond_op ||
                            sp50.i_format.opcode == cop0_op ||
                            sp50.i_format.opcode == cop1_op)
                        {
                            sp50.i_format.rt |= bltzl_op; // ???
                        } else {
                            sp50.i_format.opcode |= cop0_op; // ???
                        }
                    }

                    if (sexchange) {
                        sp50.word = SWAP(sp50.word);
                    }
                    memory[currtextindex].unk_00[(arg0->unk_54 >> 2) + arg0->unk_4E - 2].word = sp50.word;
                }
            }
        }
        arg0->unk_44_23 = FALSE;
    }
}