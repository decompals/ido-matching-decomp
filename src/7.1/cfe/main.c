#include "common.h"

/* .data      */
char* ident = "$Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/targucode/cfe/RCS/main.c,v 1.36 1995/12/13 22:32:10 zaineb Exp $";
char* outfile = "";
static char* D_1001D44C[] = {
    "/usr/lib/",
    "/lib/"
};

/* .bss       */
/* 0x1002BAD0 */ static int B_1002BAD0;
/* 0x1002BAD8 */ static char B_1002BAD8[1024];
/* 0x1002BED8 */ static char B_1002BED8[1024];
/* 0x1002C2D8 */ static char* B_1002C2D8[6];

static char* func_0041CAA0(char* arg0);
static void func_0041BB98(int argc, char** argv);
static int func_0041B7FC(char* path);

int main(int argc, char** argv) {
    char* error_file;
    char* lang;    
    char* sp34;
    int sp30;
    char* sp2C;

    catchall();
    init_options();
    general_handle = mem_start();
    sp30 = 0;

    lang = getenv("__LANG");
    if (lang == NULL) {
        lang = "english";
    }

    error_file = getenv("__ERROR_FILE");
    if (error_file != NULL) {
        sp30 = 1;
        B_1002C2D8[0] = error_file;
    }

    sprintf(B_1002BAD8, "err.%s.cc", lang);

    sp2C = strrchr(argv[0], '/');
    if (sp2C != NULL) {
        strncpy(B_1002BED8, argv[0], sp2C - argv[0] + 1);
        strcpy(&B_1002BED8[sp2C - argv[0] + 1], B_1002BAD8);
        B_1002C2D8[sp30++] = B_1002BED8;
    } else {
        sp34 = func_0041CAA0(argv[0]);
        strcpy(B_1002BED8, sp34);
        strcat(B_1002BED8, B_1002BAD8);
        B_1002C2D8[sp30++] = B_1002BED8;
        free(sp34);
    }

    B_1002C2D8[sp30++] = B_1002BAD8;
    B_1002C2D8[sp30++] = "/usr/lib/cmplrs/err.cc";

    if ((options[13] && (options[5] & 1) || !options[13] && (options[5] & 1)) && (options[5] & 3) == 3) {
        sp30 = 2;
    } else if (options[13] && (options[5] & 1) || !options[13] && (options[5] & 1)) {
        sp30 = 1;
    } else {
        sp30 = 0;
    }

    if (!error_init(B_1002C2D8, NULL, sp30)) {
        return 5;
    }

    func_0041BB98(argc, argv);

    if (!options[13] && !(options[5] & 1) && !options[24]) {
        options[24] = TRUE;
    }

    if ((options[13] && (options[5] & 1) || !options[13] && (options[5] & 1)) && (options[5] & 3) == 3) {
        sp30 = 2;
    } else if (options[13] && (options[5] & 1) || !options[13] && (options[5] & 1)) {
        sp30 = 1;
    } else {
        sp30 = 0;
    }

    set_error_mode(sp30);

    switch(func_0041B7FC(argv[0])) {
        case 0:
            B_1002BAD0 = 3;
            if (options[19] & 1) {
                options[23] = 1;
                B_1002BAD0 = lint(argc, argv);
            } else {
                B_1002BAD0 = cfe(argc, argv);
            }
            break;
        case 2:
            B_1002BAD0 = 1;
            B_1002BAD0 = cpp(argc, argv);
            if (B_1002BAD0 == 0x1007A) {
                B_1002BAD0 = 0;
            }
            break;
        case 1:
            B_1002BAD0 = 2;
            options[19] |= 1;
            options[19] |= 2;
            options[23] = 1;
            B_1002BAD0 = lint(argc, argv);
            break;
        default:
            ((void)((FALSE)||__assert("FALSE", "main.c", 0x9D)));
            break;
    }

    if (debug_arr['h']) {
        hash_table_statistics();
    }

    exit(B_1002BAD0);
    return 0;
}

static int func_0041B7FC(char* path) {
    char* v0 = strrchr(path, '/');
    if (v0 != NULL) {
        path = v0 + 1;
    }
    myname = path;

    if (strncmp(path, "cfe", strlen("cfe")) == 0 || strncmp(path, "ccom", strlen("ccom")) == 0) {
        return 0;
    }
    if (strncmp(path, "cpp", strlen("cpp")) == 0) {
        return 2;
    }
    if (strncmp(path, "lint", strlen("lint")) == 0) {
        return 1;
    }
    return -1;
}

void fatal(void) {
    exit(B_1002BAD0);
}

static void func_0041B978(char* arg0, int* arg1, int* arg2, int* arg3) {
    int i = 6;
    int len = strlen(arg0);    
    int s0, s3;

    while (i < len) {
        if (isdigit(arg0[i])) {
            s0 = atoi(&arg0[i]);
            i++;
            while (isdigit(arg0[i])) {
                i++;
            }
            
            if (arg0[i] == '-' && isdigit(arg0[++i])) {
                s3 = atoi(&arg0[i]);
            } else {
                s3 = s0;
            }
            
            while (s0 <= s3) {
                if (!set_woff(s0)) {
                    *arg1 = 1;
                    *arg2 = s0;
                }
                s0++;
            }
        } else {
            *arg3 = 1;
        }

        while (i < len && arg0[i] != ',') {
            if (!isdigit(arg0[i])) {
                *arg3 = 1;
            }
            i++;
        }
        if (i < len && arg0[i] == ',') {
            i++;
        }
    }
}

static void func_0041BB98(int argc, char** argv) {
    int i;
    int u1;
    int sp8C = 0;
    int sp88 = 0;
    int sp84;
    int sp80 = 0;
    int sp7C = 0;
    int sp78 = 0;
    
    if (getenv("_XPG") != NULL) {
        xpg_flag = TRUE;
    } else {
        xpg_flag = FALSE;
    }
    
    for (i = 1; i < argc; i++) {
        if (*argv[i] == '-') {
            switch(argv[i][1]) {
                case 'M':
                    if (argv[i][2] == 'D') {
                        // skip next argument
                        i++;
                    }
                    break;
                case '-':
                    if (argv[i][2] == '-' && xpg_flag) {
                        infile = argv[i] + 2;
                        continue;
                    }
                    /* fallthrough */
                case 'X':
                    switch(argv[i][2]) {
                        case 'c':
                            if (strcmp(argv[i], "-Xcommon") == 0) {
                                options[24] = TRUE;
                            } else if (strcmp(argv[i], "-Xcpluscomm") == 0) {
                                options[26] = TRUE;
                            } else if (strncmp(argv[i], "-Xcmd:", 6) == 0) {
                                command_line_file_name = argv[i] + 6;
                            }
                            break;
                        case 'd':
                            if (strncmp(argv[i], "-Xdollar", 8) == 0) {
                                options[7] = TRUE;
                            } else {
                                int v1;

                                if (argv[i][4] == 0) {
                                    v1 = 1;
                                } else {
                                    v1 = atoi(argv[i] + 4);
                                }
                                debug_arr[argv[i][3]] = v1;
                                if (argv[i][3] == 'y') {
                                    yydebug = v1;
                                }
                            }
                            break;
                        case 'f':
                            if (strncmp(argv[i], "-Xfloat", 7) == 0) {
                                options[4] = TRUE;
                            } else if (strncmp(argv[i], "-Xfullwarn", 10) == 0) {
                                options[23] = TRUE;
                            }
                            break;
                        case 'g':
                            options[1] = atoi(argv[i] + 3);
                            break;
                        case 'p':
                            if (strncmp(argv[i], "-Xprototypes", 12) == 0) {
                                options[22] = TRUE;
                            }
                            break;
                        case 's':
                            if (strcmp(argv[i], "-Xsigned") == 0) {
                                options[6] = TRUE;
                            }
                            break;
                        case 'N':
                            break;
                        case 'S':
                            st_filename = argv[i] + 3;
                            break;
                        case 't':
                            if (argv[i][3] == 0) {
                                options[16] = TRUE;
                            } else if (strncmp(argv[i], "-Xtypebind:", 11) == 0) {
                                char* ptr = argv[i] + 11;
                                int c;
                                int s1;
                                int size;
                                
                                while (c = *ptr) {
                                    switch(*ptr) {
                                        case 'c':
                                            s1 = 1;
                                            break;
                                        case 's':
                                            s1 = 2;
                                            break;
                                        case 'i':
                                            s1 = 3;
                                            break;
                                        case 'l':
                                            s1 = 4;
                                            break;
                                        case 'L':
                                            s1 = 5;
                                            break;
                                        case 'p':
                                            s1 = 9;
                                            break;
                                        case 'f':
                                            s1 = 6;
                                            break;
                                        case 'd':
                                            s1 = 7;
                                            break;
                                        case 'D':
                                            s1 = 8;
                                            break;                                        
                                        default:
                                            fprintf(stderr, "-Xtypebind: unknown type %c\n", *ptr);
                                            s1 = 0;
                                            break;
                                    }
                                    
                                    ptr++;
                                    size = atoi(ptr);
                                    if (size & 1) {
                                        fprintf(stderr, "-Xtypebind: bad size %d\n", size);
                                        s1 = 0;
                                    }

                                    bit_size[s1] = size;
                                    while(isdigit(*ptr) || *ptr == ':') {
                                        ptr++;
                                    }
                                }

                                if (bit_size[2] < bit_size[1] ||
                                    bit_size[3] < bit_size[2] ||
                                    bit_size[4] < bit_size[3] ||
                                    bit_size[5] < bit_size[4] ||
                                    bit_size[7] < bit_size[6] ||
                                    bit_size[8] < bit_size[7]) {
                                    fprintf(stderr, "-Xtypebind: specified sizes violate the language rules\n");
                                }
                            }
                            break;
                        case 'u':
                            if (strcmp(argv[i], "-Xunsigned") == 0) {
                                options[6] = FALSE;
                            } else {
                                outfile = NULL;
                            }
                            break;
                        case 'v':
                            if (strcmp(argv[i], "-Xvolatile") == 0) {
                                options[25] = TRUE;
                                error(0x4015F, 1, -1, "-volatile");
                                break;
                            } if (strcmp(argv[i], "-Xv") == 0) {
                                options[3] |= 8;
                            }
                            break;
                        case 'w':
                            if (strncmp(argv[i], "-Xwoff", 6) == 0) {
                                func_0041B978(argv[i], &sp8C, &sp88, &sp80);
                            }
                            break;
                    }
                    break;
                case 's':
                    if (strncmp(argv[i], "-std", 4) == 0) {
                        if (argv[i][4] == '0' && argv[i][5] == 0) {
                            options[5] = 0;
                        } else if (argv[i][4] == 0) {
                            options[5] = 3;
                        } else if (argv[i][4] == '1' && argv[i][5] == 0) {
                            options[5] = 5;
                        }
                    } else if (strncmp(argv[i], "-saveargs", 9) == 0) {
                        options[18] = TRUE;
                    }
                    break;
                case 'c':
                    if (strncmp(argv[i], "-call_shared", 12) == 0) {
                        // ignored
                    } else if (strncmp(argv[i], "-cplus", 6) == 0) {
                        options[13]++;
                    } else if (strncmp(argv[i], "-checkstack", 11) == 0) {
                        options[15]++;
                        i++; // skip next argument
                    } else if (strncmp(argv[i], "-check_bounds", 13) == 0) {
                        options[17]++;
                    }
                    break;
                case 'n':
                    if (strncmp(argv[i], "-non_shared", 11) == 0) {
                        // ignored
                    }
                    break;
                case 't':
                    if (strncmp(argv[i], "-trapuv", 7) == 0) {
                        options[10] = TRUE;
                    }
                    break;
                case 'A':
                    if (i + 1 < argc && argv[i + 1][0] == '(' && i + 2 < argc && argv[i + 2][0] == ')') {
                        i += 2;
                    }
                    break;
                case 'G':
                    if (isdigit(argv[i + 1][0])) {
                        Set_Small_Data_Upper_Limit(atoi(argv[++i]));
                    }
                    break;
                case 'E':
                    if (argv[i][2] == 'B' && argv[i][3] == 0) {
                        options[2] = options[2];
                    } else if (argv[i][2] == 'L' && argv[i][3] == 0) {
                        options[2] = !options[2];
                    }
                    break;
                case 'O':
                    options[0] = atoi(argv[i] + 2);
                    break;
                case 'T':
                    options[8] = atoi(argv[i] + 2);
                    break;
                case 'o':
                    if (argv[i][2] == 0) {
                        i++;
                        if (i < argc) {
                            outfile = argv[i];
                        }
                    }
                    break;
                case 'w':
                    if (strcmp(argv[i], "-wimplicit") == 0) {
                        options[20] = TRUE;
                    } else if (strncmp(argv[i], "-wlint", 6) == 0) {
                        options[19] |= 1;
                    } else {
                        switch (argv[i][2]) {
                            case 0:
                            case '1':
                                options[3] &= ~1;
                                break;
                            case '3':
                                options[3] &= ~1;
                                // fallthrough */
                            case '2':
                                options[3] |= 0x10;
                                break;
                        }
                    }
                    break;
                case 'v':
                    if (strcmp(argv[i], "-verbose") == 0) {
                        options[3] |= 4;
                    }
                    break;
                case 'f':
                    if (strcmp(argv[i], "-framepointer") == 0) {
                        options[9] = TRUE;
                    }
                    break;
                case 'Z':
                    if (argv[i][2] == 'p' && argv[i][3] != 0) {
                        set_def_member_pack(atoi(argv[i] + 3));
                    }
                    break;
                case 'm':
                    if (strncmp(argv[i], "-mips", 5) == 0) {
                        options[12] = atoi(argv[i] + 5);
                        if (options[12] > 2) {
                            options[14] = TRUE;
                        }
                    } else if (strncmp(argv[i], "-msft", 5) == 0) {
                        options[21] = TRUE;
                    } else if (strncmp(argv[i], "-min_st_indirection", 19) == 0) {
                        minimize_indirection_entries = TRUE;
                    } else if (strncmp(argv[i], "-max_st_indirection", 19) == 0) {
                        minimize_indirection_entries = FALSE;
                    } else if (strncmp(argv[i], "-max_rec_depth=", 15) == 0) {
                        cpp_symentry_setMaxMacroRecursionDepth(atoi(argv[i] + 15));
                    }
                    break;
                case 'd':
                    if (strcmp(argv[i], "-dwopcode") == 0) {
                        options[14] = TRUE;
                    }
                    break;
                case 'u':
                    if (strncmp(argv[i], "-use_readonly_const", 19) == 0) {
                        options[27] = TRUE;
                        sp7C = TRUE;
                    } else if (strncmp(argv[i], "-use_readwrite_const", 20) == 0) {
                        options[27] = FALSE;
                        sp7C = TRUE;
                    } else if (strncmp(argv[i], "-use_literal_const", 18) == 0) {
                        options[28] = TRUE;
                        sp78 = TRUE;
                    } else if (strncmp(argv[i], "-use_variable_const", 19) == 0) {
                        options[28] = FALSE;
                        sp78 = TRUE;
                    }
                    break;
                case '6':
                    if (strcmp(argv[i], "-64data") == 0) {
                        bit_size[9] = 64;
                        bit_size[4] = 64;
                        options[14] = TRUE;
                    }
                    break;
            }
        } else {
            if (infile == NULL) {
                infile = argv[i];
            } else if (func_0041B7FC(argv[0]) != 2) {
                error(0x40040, 2, -1, argv[i]);
            }
        }
    }

    if (!sp7C) {
        options[27] = TRUE;
    }
    if (!sp78) {
        options[28] = (options[13] && (options[5] & 1) || !options[13] && (options[5] & 1)) &&
            (!(options[13] && (options[5] & 1) || !options[13] && (options[5] & 1)) ||
            !((options[5] & 3) == 3));
    }
    if (options[23] && sp8C) {
        error(0x40135, 1, -1, "such as ", sp88, 0x1F4, 0x358);
    }
    if (options[23] && sp80) {
        error(0x40135, 1, -1, "numbers (ranges) should be seperated by commas only: e.g. -woff 505-550,", 0x25f, 0x1F4, 0x358);
    }
}

static char* func_0041CAA0(char* arg0) {
    char* ptr = getenv("PATH");
    int i;
    char sp4C[100];
    int fd;    
    char* path;

    while (*ptr != 0) {
        char* ptr2 = sp4C;

        while (*ptr != ':' && *ptr != 0) {
            *ptr2++ = *ptr++;
        }

        if (*ptr == ':') {
            ptr++;
        }

        if (ptr2[-1] != '/') {
            *ptr2 = '/';
            ptr2++;
        }

        *ptr2 = 0;

        strcat(sp4C, arg0);
        fd = open(sp4C, O_RDONLY);
        if (fd >= 0) {
            close(fd);
            *ptr2 = 0;
            path = Malloc(strlen(sp4C) + 1);
            strcpy(path, sp4C);
            return path;
        }
    }

    for (i = 0; D_1001D44C[i] != NULL; i++) {
        sp4C[0] = 0;
        strcat(sp4C, D_1001D44C[i]);
        strcat(sp4C, arg0);
        fd = open(sp4C, O_RDONLY);
        if (fd >= 0) {
            close(fd);
            path = Malloc(strlen(D_1001D44C[i]) + 1);
            strcpy(path, D_1001D44C[i]);
            return path;
        }
    }

    sp4C[0] = 0;
    path = Malloc(strlen(sp4C) + 1);
    strcpy(path, sp4C);
    return path;
}