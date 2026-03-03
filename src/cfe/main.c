#include "common.h"

/* .data      */
char* ident = "$Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/targucode/cfe/RCS/main.c,v 1.36 1995/12/13 22:32:10 zaineb Exp $";
static int unused = 0;
char* outfile = "";

/* .bss       */
/* 0x1002BAD0 */ static int exit_code;
/* 0x1002BAD8 */ static char curr_lang_error_file[1024];
/* 0x1002BED8 */ static char err_file_buffer[1024];
/* 0x1002C2D8 */ static char* message_files[6];

static char* get_directory(char* arg0);
static void parse_cmdline(int argc, char** argv);
static int get_program_id(char* path);

int main(int argc, char** argv) {
    char* error_file;
    char* lang;    
    char* dir;
    int error_mode;
    char* dir_end;

    catchall();
    init_options();
    general_handle = mem_start();
    error_mode = 0;

    lang = getenv("__LANG");
    if (lang == NULL) {
        lang = "english";
    }

    error_file = getenv("__ERROR_FILE");
    if (error_file != NULL) {
        message_files[error_mode++] = error_file;
    }

    sprintf(curr_lang_error_file, "err.%s.cc", lang);

    dir_end = strrchr(argv[0], '/');
    if (dir_end != NULL) {
        strncpy(err_file_buffer, argv[0], dir_end - argv[0] + 1);
        strcpy(&err_file_buffer[dir_end - argv[0] + 1], curr_lang_error_file);
        message_files[error_mode++] = err_file_buffer;
    } else {
        dir = get_directory(argv[0]);
        strcpy(err_file_buffer, dir);
        strcat(err_file_buffer, curr_lang_error_file);
        message_files[error_mode++] = err_file_buffer;
        free(dir);
    }

    message_files[error_mode++] = curr_lang_error_file;
    message_files[error_mode++] = "/usr/lib/cmplrs/err.cc";

    if (IS_RELAXED_ANSI) {
        error_mode = 2;
    } else if (IS_ANSI) {
        error_mode = 1;
    } else {
        error_mode = 0;
    }

    if (!error_init(message_files, NULL, error_mode)) {
        return 5;
    }

    parse_cmdline(argc, argv);

    if (!options[OPTION_CPLUSPLUS] && !(options[OPTION_ANSI_MODE] & 1) && !options[OPTION_XCOMMON]) {
        options[OPTION_XCOMMON] = TRUE;
    }

    if (IS_RELAXED_ANSI) {
        error_mode = 2;
    } else if (IS_ANSI) {
        error_mode = 1;
    } else {
        error_mode = 0;
    }

    set_error_mode(error_mode);

    switch (get_program_id(argv[0])) {
        case 0:
            exit_code = 3;
            if (options[OPTION_LINT_FLAGS] & 1) {
                options[OPTION_FULLWARN] = TRUE;
                exit_code = lint(argc, argv);
            } else {
                exit_code = cfe(argc, argv);
            }
            break;
        case 2:
            exit_code = 1;
            exit_code = cpp(argc, argv);
            if (exit_code == 0x1007A) {
                exit_code = 0;
            }
            break;
        case 1:
            exit_code = 2;
            options[OPTION_LINT_FLAGS] |= 1;
            options[OPTION_LINT_FLAGS] |= 2;
            options[OPTION_FULLWARN] = TRUE;
            exit_code = lint(argc, argv);
            break;
        default:
            ((void)((FALSE)||__assert("FALSE", "main.c", 0x9D)));
            break;
    }

    if (debug_arr['h']) {
        hash_table_statistics();
    }

    exit(exit_code);
    return 0;
}

static int get_program_id(char* path) {
    char* ptr = strrchr(path, '/');
    if (ptr != NULL) {
        path = ptr + 1;
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
    exit(exit_code);
}

static void parse_woff(char* input, int* has_error, int* wrong_warn_number, int* invalid_input) {
    int i = 6;
    int len = strlen(input);    
    int num1, num2;

    while (i < len) {
        if (isdigit(input[i])) {
            num1 = atoi(&input[i]);
            i++;
            while (isdigit(input[i])) {
                i++;
            }
            
            if (input[i] == '-' && isdigit(input[++i])) {
                num2 = atoi(&input[i]);
            } else {
                num2 = num1;
            }
            
            while (num1 <= num2) {
                if (!set_woff(num1)) {
                    *has_error = TRUE;
                    *wrong_warn_number = num1;
                }
                num1++;
            }
        } else {
            *invalid_input = TRUE;
        }

        while (i < len && input[i] != ',') {
            if (!isdigit(input[i])) {
                *invalid_input = TRUE;
            }
            i++;
        }
        if (i < len && input[i] == ',') {
            i++;
        }
    }
}

static void parse_cmdline(int argc, char** argv) {
    int i;
    int u1;
    int has_woff_error = 0;
    int woff_warn_num = 0;
    int sp84;
    int invalid_woff = 0;
    int constModeChanged = 0;
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
                                options[OPTION_XCOMMON] = TRUE;
                            } else if (strcmp(argv[i], "-Xcpluscomm") == 0) {
                                options[OPTION_CPLUSCOMM] = TRUE;
                            } else if (strncmp(argv[i], "-Xcmd:", 6) == 0) {
                                command_line_file_name = argv[i] + 6;
                            }
                            break;
                        case 'd':
                            if (strncmp(argv[i], "-Xdollar", 8) == 0) {
                                options[OPTION_DOLLAR] = TRUE;
                            } else {
                                int dbgval;

                                if (argv[i][4] == 0) {
                                    dbgval = 1;
                                } else {
                                    dbgval = atoi(argv[i] + 4);
                                }
                                debug_arr[argv[i][3]] = dbgval;
                                if (argv[i][3] == 'y') {
                                    yydebug = dbgval;
                                }
                            }
                            break;
                        case 'f':
                            if (strncmp(argv[i], "-Xfloat", 7) == 0) {
                                options[OPTION_FLOAT] = TRUE;
                            } else if (strncmp(argv[i], "-Xfullwarn", 10) == 0) {
                                options[OPTION_FULLWARN] = TRUE;
                            }
                            break;
                        case 'g':
                            options[OPTION_G_LEVEL] = atoi(argv[i] + 3);
                            break;
                        case 'p':
                            if (strncmp(argv[i], "-Xprototypes", 12) == 0) {
                                options[OPTION_PROTOTYPES] = TRUE;
                            }
                            break;
                        case 's':
                            if (strcmp(argv[i], "-Xsigned") == 0) {
                                options[OPTION_SIGNED] = TRUE;
                            }
                            break;
                        case 'N':
                            break;
                        case 'S':
                            st_filename = argv[i] + 3;
                            break;
                        case 't':
                            if (argv[i][3] == 0) {
                                options[OPTION_T] = TRUE;
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
                                options[OPTION_SIGNED] = FALSE;
                            } else {
                                outfile = NULL;
                            }
                            break;
                        case 'v':
                            if (strcmp(argv[i], "-Xvolatile") == 0) {
                                options[OPTION_VOLATILE] = TRUE;
                                error(0x4015F, 1, -1, "-volatile");
                                break;
                            } if (strcmp(argv[i], "-Xv") == 0) {
                                options[OPTION_VERBOSITY] |= VERBOSE_FLAG_8;
                            }
                            break;
                        case 'w':
                            if (strncmp(argv[i], "-Xwoff", 6) == 0) {
                                parse_woff(argv[i], &has_woff_error, &woff_warn_num, &invalid_woff);
                            }
                            break;
                    }
                    break;
                case 's':
                    if (strncmp(argv[i], "-std", 4) == 0) {
                        if (argv[i][4] == '0' && argv[i][5] == 0) {
                            options[OPTION_ANSI_MODE] = 0;
                        } else if (argv[i][4] == 0) {
                            options[OPTION_ANSI_MODE] = 3;
                        } else if (argv[i][4] == '1' && argv[i][5] == 0) {
                            options[OPTION_ANSI_MODE] = 5;
                        }
                    } else if (strncmp(argv[i], "-saveargs", 9) == 0) {
                        options[OPTION_SAVEARGS] = TRUE;
                    }
                    break;
                case 'c':
                    if (strncmp(argv[i], "-call_shared", 12) == 0) {
                        // ignored
                    } else if (strncmp(argv[i], "-cplus", 6) == 0) {
                        options[OPTION_CPLUSPLUS]++;
                    } else if (strncmp(argv[i], "-checkstack", 11) == 0) {
                        options[OPTION_CHECKSTACK]++;
                        i++; // skip next argument
                    } else if (strncmp(argv[i], "-check_bounds", 13) == 0) {
                        options[OPTION_CHECK_BOUNDS]++;
                    }
                    break;
                case 'n':
                    if (strncmp(argv[i], "-non_shared", 11) == 0) {
                        // ignored
                    }
                    break;
                case 't':
                    if (strncmp(argv[i], "-trapuv", 7) == 0) {
                        options[OPTION_TRAPUV] = TRUE;
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
                        options[OPTION_ENDIANNESS] = options[OPTION_ENDIANNESS];
                    } else if (argv[i][2] == 'L' && argv[i][3] == 0) {
                        options[OPTION_ENDIANNESS] = !options[OPTION_ENDIANNESS];
                    }
                    break;
                case 'O':
                    options[OPTION_O_LEVEL] = atoi(argv[i] + 2);
                    break;
                case 'T':
                    options[OPTION_T_LEVEL] = atoi(argv[i] + 2);
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
                        options[OPTION_WIMPLICIT] = TRUE;
                    } else if (strncmp(argv[i], "-wlint", 6) == 0) {
                        options[OPTION_LINT_FLAGS] |= 1;
                    } else {
                        switch (argv[i][2]) {
                            case 0:
                            case '1':
                                options[OPTION_VERBOSITY] &= ~VERBOSE_FLAG_1;
                                break;
                            case '3':
                                options[OPTION_VERBOSITY] &= ~VERBOSE_FLAG_1;
                                // fallthrough */
                            case '2':
                                options[OPTION_VERBOSITY] |= VERBOSE_FLAG_10;
                                break;
                        }
                    }
                    break;
                case 'v':
                    if (strcmp(argv[i], "-verbose") == 0) {
                        options[OPTION_VERBOSITY] |= VERBOSE_FLAG_4;
                    }
                    break;
                case 'f':
                    if (strcmp(argv[i], "-framepointer") == 0) {
                        options[OPTION_FRAMEPOINTER] = TRUE;
                    }
                    break;
                case 'Z':
                    if (argv[i][2] == 'p' && argv[i][3] != 0) {
                        set_def_member_pack(atoi(argv[i] + 3));
                    }
                    break;
                case 'm':
                    if (strncmp(argv[i], "-mips", 5) == 0) {
                        options[OPTION_MIPS_GEN] = atoi(argv[i] + 5);
                        if (options[OPTION_MIPS_GEN] > 2) {
                            options[OPTION_14] = TRUE;
                        }
                    } else if (strncmp(argv[i], "-msft", 5) == 0) {
                        options[OPTION_MSFT] = TRUE;
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
                        options[OPTION_14] = TRUE;
                    }
                    break;
                case 'u':
                    if (strncmp(argv[i], "-use_readonly_const", 19) == 0) {
                        options[OPTION_READONLY_CONST] = TRUE;
                        constModeChanged = TRUE;
                    } else if (strncmp(argv[i], "-use_readwrite_const", 20) == 0) {
                        options[OPTION_READONLY_CONST] = FALSE;
                        constModeChanged = TRUE;
                    } else if (strncmp(argv[i], "-use_literal_const", 18) == 0) {
                        options[OPTION_LITERAL_CONST] = TRUE;
                        sp78 = TRUE;
                    } else if (strncmp(argv[i], "-use_variable_const", 19) == 0) {
                        options[OPTION_LITERAL_CONST] = FALSE;
                        sp78 = TRUE;
                    }
                    break;
                case '6':
                    if (strcmp(argv[i], "-64data") == 0) {
                        bit_size[9] = 64;
                        bit_size[4] = 64;
                        options[OPTION_14] = TRUE;
                    }
                    break;
            }
        } else {
            if (infile == NULL) {
                infile = argv[i];
            } else if (get_program_id(argv[0]) != 2) {
                error(0x40040, 2, -1, argv[i]);
            }
        }
    }

    if (!constModeChanged) {
        options[OPTION_READONLY_CONST] = TRUE;
    }
    if (!sp78) {
        options[OPTION_LITERAL_CONST] = IS_ANSI && !IS_RELAXED_ANSI;
    }
    if (options[OPTION_FULLWARN] && has_woff_error) {
        error(0x40135, 1, -1, "such as ", woff_warn_num, 500, 856);
    }
    if (options[OPTION_FULLWARN] && invalid_woff) {
        error(0x40135, 1, -1, "numbers (ranges) should be seperated by commas only: e.g. -woff 505-550,", 607, 500, 856);
    }
}

static char* default_path_dirs[] = {
    "/usr/lib/",
    "/lib/"
};

static char* get_directory(char* name) {
    char* path_ptr = getenv("PATH");
    int i;
    char buffer[100];
    int fd;    
    char* path;

    while (*path_ptr != 0) {
        char* bufptr = buffer;

        while (*path_ptr != ':' && *path_ptr != 0) {
            *bufptr++ = *path_ptr++;
        }

        if (*path_ptr == ':') {
            path_ptr++;
        }

        if (bufptr[-1] != '/') {
            *bufptr = '/';
            bufptr++;
        }

        *bufptr = 0;

        strcat(buffer, name);
        fd = open(buffer, O_RDONLY);
        if (fd >= 0) {
            close(fd);
            *bufptr = 0;
            path = Malloc(strlen(buffer) + 1);
            strcpy(path, buffer);
            return path;
        }
    }

    for (i = 0; default_path_dirs[i] != NULL; i++) {
        buffer[0] = 0;
        strcat(buffer, default_path_dirs[i]);
        strcat(buffer, name);
        fd = open(buffer, O_RDONLY);
        if (fd >= 0) {
            close(fd);
            path = Malloc(strlen(default_path_dirs[i]) + 1);
            strcpy(path, default_path_dirs[i]);
            return path;
        }
    }

    buffer[0] = 0;
    path = Malloc(strlen(buffer) + 1);
    strcpy(path, buffer);
    return path;
}
