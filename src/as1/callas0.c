#include "common.h"

typedef struct Sym_s {
        int idn; // Symbol idn
        int parsedIdn;
        int count;
        char* name; // Symbol name
        struct Sym_s* next; // Next in linked list
} Sym;

static unsigned int exec_and_wait(char* path, char** asmFileName);
static char* string_copy(char* str);
static char* string_concatenate(char* name, char* ext);
static void parse_extsyms_file(char* path);
static void resolve_syms(void);
static void process_sym_list(void);
static void print_sym_lists(void);

static Sym* sSymnoList = NULL;
static Sym* sSymnoNames = NULL;

static void stubbed_abort(void) {

}

// The normal WEXITSTATUS macro doesn't seems to match here
#define EXIT_STATUS(x) (unsigned int)(_W_INT(x) & 0xFF00) >> 8

/*
* @brief Executes an executable given its path on another proccess (cpid) and waits until it's finished
* @param path Executable path
* @param argv Arglist to pass to the program
*/
static unsigned int exec_and_wait(char* path, char** argv) {
    int pad;
    int pad2;
    int result; // Child process result
    int pid;
    int cpid; // Child process id
    char** arg;
    wait_t status; // Child process status

    // If verbose print the executable's path and arguments
    if (verbose) {
        fprintf(stderr, "%s ", path);
        for (arg = &argv[1]; *arg != NULL;) {
            fprintf(stderr, "%s ", *arg++);
        }
        fprintf(stderr, "\n");
    }
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "no more processes\n");
        if (errno < sys_nerr) {
            fprintf(stderr, "%s\n", sys_errlist[errno]);
        }
        return -1;
    }
    if (pid == 0) {
        execvp(path, argv);
        fprintf(stderr, "can't find or exec: %s\n", path);
        if (errno < sys_nerr) {
            fprintf(stderr, "%s\n", sys_errlist[errno]);
        }
        stubbed_abort();
        exit(1);
    } else {
        // Why check this with a loop?
        while ((cpid = wait((int*)&status)) != pid) {
            if (cpid == -1) {
                return -1;
            }
        }

        result = _W_INT(status) & 0xFF;
        if ((result != 0) && (result != 2)) {
            fprintf(stderr, "Fatal error in: %s ", path);
            printf(" Signal %d ", result);
            if (WCOREDUMP(status)) {
                fprintf(stderr, "- core dumped\n");
            } else {
                fprintf(stderr, "\n");
            }
            stubbed_abort();
            exit(result);
        }
        if (result == 2) {
            stubbed_abort();
            exit(3);
        }
        return EXIT_STATUS(status);
    }
}

int call_as0(char* execPath, char* asmFileName, char* arg2) {
    char** argList; // Argument list for as0
    int argCount = 0;
    char extraArgs[4];
    FILE* fp;
    int as0Result;

    if (!keepflag) {
        tmpnam(asmFileName);
    }
    fp = fopen(string_concatenate(asmFileName, ".s"), "w");
    if (verbose) {
        fprintf(stderr, "call as0 for:  %s\n", arg2);
    }
    fprintf(fp, "%s\n", arg2);
    fclose(fp);
    argList = xmalloc(80);
    execPath[strlen(execPath) - 1] = '0';
    
    argList[argCount++] = string_copy(execPath);
    if (verbose) {
        argList[argCount++] = string_copy("-v");
    }

    argList[argCount++] = string_copy("-G");

    sprintf(extraArgs, "%d", gprelsize);
    argList[argCount++] = string_copy(extraArgs);

    if (bigendian) {
        argList[argCount++] = string_copy("-EB");
    } else {
        argList[argCount++] = string_copy("-EL");
    }

    sprintf(extraArgs, "-g%d", debugflag);
    argList[argCount++] = string_copy(extraArgs);

    sprintf(extraArgs, "-O%d", optflag);
    argList[argCount++] = string_copy(extraArgs);

    if (isa == 3) {
        argList[argCount++] = string_copy("-mips3");
    } else if (isa == 2) {
        argList[argCount++] = string_copy("-mips2");
    } else if (isa == 4) {
        argList[argCount++] = string_copy("-mips4");
    }

    argList[argCount++] = string_concatenate(asmFileName, ".s");
    argList[argCount++] = string_copy("-o");
    argList[argCount++] = string_concatenate(asmFileName, ".G");
    argList[argCount++] = string_copy("-t");
    argList[argCount++] = string_concatenate(asmFileName, ".T");
    argList[argCount++] = string_copy("-extsyms");
    argList[argCount++] = string_concatenate(asmFileName, ".TE");
    argList[argCount++] = NULL;
    as0Result = exec_and_wait(execPath, argList);
    if (as0Result != 0) {
        postcerror("error while calling as0 on asm string", 0);
    }
    process_sym_list();
    parse_extsyms_file(string_concatenate(asmFileName, ".TE"));
    resolve_syms();
    if (verbose) {
        print_sym_lists();
    }
    if (!keepflag) {
        unlink(string_concatenate(asmFileName, ".s"));
        unlink(string_concatenate(asmFileName, ".T"));
        unlink(string_concatenate(asmFileName, ".TE"));
    }
    strcat(asmFileName, ".G");
    return as0Result;
}

static char* string_copy(char* str) {
    char* newStr;
    
    if (str == NULL) {
        fprintf(stderr, "string_copy empty\n");
    }
    
    newStr = xmalloc(strlen(str) + 1);
    strcpy(newStr, str);
    return newStr;
}

// Concatenates two strings
static char* string_concatenate(char* str1, char* str2) {
    char* newStr;
    int pad;
    size_t len;

    len = strlen(str1);
    newStr = xmalloc((strlen(str2) + len) + 1);
    strcpy(newStr, str1);
    return strcat(newStr, str2);
}

static void parse_extsyms_file(char* path) {
    int ret;
    FILE* fp;
    char symName[80];
    int binasmCount;
    int symIdn;
    Sym* sym;
    
    fp = fopen(path, "r");
    if (fp != NULL) {
        if (!(fp->_flag & (_IOMYBUF | _IOWRT | _IONBF))) {
            do {
                if ((fscanf(fp, "%d %d", &binasmCount, &symIdn) != 2) || !(fp->_flag & (_IOMYBUF | _IOWRT | _IONBF))) { 
                    break;
                }
                sym = xmalloc(sizeof(Sym));
                sym->count = binasmCount;
                ret = fgetc(fp);
                sym->idn = symIdn;
                sym->parsedIdn = 0;
                sym->next = sSymnoList;
                sSymnoList = sym;
                
                if ((ret & 0xFF) == ' ') {
                    ret = fscanf(fp, "%s\n", symName);
                    sym->name = string_copy(symName);
                }
            } while ((ret != -1) && !(fp->_flag & (_IOMYBUF | _IOWRT | _IONBF)));
        } 
        fclose(fp);
    }
}

static void resolve_syms(void) {
    Sym* var_s0;
    Sym* var_s1;

    for (var_s1 = sSymnoList; var_s1 != NULL; var_s1 = var_s1->next) {
        if (var_s1->parsedIdn == 0) {
            if (var_s1->name != NULL) {
                for (var_s0 = sSymnoNames; var_s0 != NULL; var_s0 = var_s0->next) {
                    if (strcmp(var_s0->name, var_s1->name) == 0) {
                        var_s1->parsedIdn = var_s0->parsedIdn;
                        break;
                    }
                }

                if (var_s1->parsedIdn == 0) {
                    var_s1->parsedIdn = idn_for_extern_symbol(var_s1->name);
                }
            } else {
                var_s1->parsedIdn = idn_for_anon_symbol();
            }

            for (var_s0 = sSymnoList; var_s0 != NULL; var_s0 = var_s0->next) {
                if (var_s0->idn == var_s1->idn) {
                    var_s0->parsedIdn = var_s1->parsedIdn;
                }
            }
        }
    }
}

int fixup_symno(int idn) {
    Sym* sym;

    for (sym = sSymnoList; sym != NULL; sym = sym->next) {
        if ((binasm_count == sym->count) && (idn == sym->idn)) {
            return sym->parsedIdn;
        }
    }
    
    return idn;
}

static void process_sym_list(void) {
    Sym* curSym;
    Sym* curSymName;

    curSym = sSymnoList;
    while (curSym != NULL) {
        sSymnoList = curSym->next;
        if (curSym->name != NULL) {
            for (curSymName = sSymnoNames; curSymName != NULL; curSymName = curSymName->next) {
                if (strcmp(curSymName->name, curSym->name) == 0) {
                    curSym->parsedIdn = curSymName->parsedIdn;
                    break;
                }
            }

            if (curSymName == NULL) {
                curSym->idn = 0;
                curSym->next = sSymnoNames;
                sSymnoNames = curSym;
            } else {
                xfree(curSym); // Free repeated syms
            }
        } else {
            xfree(curSym);
        }
        curSym = sSymnoList;
    }
}

static void print_sym_lists(void) {
    Sym* sym;

    sym = sSymnoList;
    printf("symno_list:\n");
    while (sym != NULL) {
        printf("%d: %d->%d for %s\n", sym->count, sym->idn, sym->parsedIdn, sym->name);
        sym = sym->next;
    }
    
    sym = sSymnoNames;
    printf("symno_names:\n");
    while (sym != NULL) {
        printf("->%d for %s\n", sym->parsedIdn, sym->name);
        sym = sym->next;
    }
}
