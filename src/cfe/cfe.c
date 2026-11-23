#include "common.h"

char* ident =
    "$Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/targucode/cfe/RCS/cfe.c,v 1.3 1992/10/15 17:36:12 rdahl Exp $";

// NON_MATCHING
// url: https://decomp.me/scratch/74NVp
// score: 105(99.63%)
int cfe(int argc, char** argv) {
    TreeNode* s0;
    int s2;
    FILE* sp34;
    int sp30;
    int v0;

    sp30 = FALSE;

    v0 = cpp(argc, argv);
    if (v0 == 0x1007A) {
        s2 = 0;
        if (num_errs != 0 || s2 == 0 /* @FAKE */ && num_warns != 0 && (options[OPTION_VERBOSITY] & VERBOSE_FLAG_10)) {
            return 3;
        } else {
            return s2;
        }
    }
    v0 = v0 != 0;
    if (v0 != 0) {
        return v0;
    }

    create_symtab();
    init_trees();
    make_std_trees();
    init_scan();
    init_screener();
    init_layout();
    if (origfile->unk_10 == -1) {
        init_mips_st(0);
    }
    // if (!options) {} // @FAKE
    init_sem();

    while (TRUE) {
        s0 = parse();
        s2 = (s0 != NULL);
        if (s2) {
            s2 = TREE_CODE(s0) == End_of_file;
        }

        if (debug_arr['p']) {
            if (debug_arr['p'] > 0) {
                fprintf(dbgout, "***Parse tree***\n");
            }
            display_tree(s0);
        }

        if (debug_arr['S'] == 0 && num_errs == 0) {
            s0 = semantics(s0);
        }

        if (debug_arr['s']) {
            if (debug_arr['s'] > 0) {
                fprintf(dbgout, "***Semantic tree***\n");
            }
            display_tree(s0);
        }

        mips_st(NULL);

        if (num_errs == 0 && outfile != NULL && options[OPTION_11] == 0 && debug_arr['S'] == 0 &&
            !(options[OPTION_LINT_FLAGS] & 2)) {
            if (!sp30) {
                sp30 = TRUE;
                if (outfile[0] == '\0') {
                    sp34 = stdout;
                } else {
                    sp34 = fopen(outfile, "w");
                    if (sp34 == NULL) {
                        error(MSG_CANNOT_WRITE_FILE_2, LEVEL_FATAL, -1, outfile);
                    }
                }

                init_codegen(origfile->unk_0C->unk_18, sp34, 3);
            }

            tree_handle = temp_handle;
            codegen(s0);
        }

        if (s0 != NULL && s2) {
            break;
        }

        mem_free(temp_handle);
    }

    if (options[OPTION_LINT_FLAGS]) {
        lint_outdef(1, file_scope->unk_00, 0);
    }
    error_flush(-1);
    end_mips_st();
    if (num_errs == 0 && debug_arr['S'] == 0 && outfile != NULL && options[OPTION_11] == 0 &&
        !(options[OPTION_LINT_FLAGS] & 2)) {
        fclose(sp34);
    }
    if (num_errs != 0 || num_warns != 0 && (options[OPTION_VERBOSITY] & VERBOSE_FLAG_10)) {
        return 3;
    } else {
        return return_code;
    }
}
