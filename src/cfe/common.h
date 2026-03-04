#ifndef COMMON_H
#define COMMON_H

#define FALSE 0
#define TRUE 1

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/fpu.h>
#include <fp_class.h>

typedef struct TokenIdentifier {
    int was_typedef;
    struct Symbol* symbol;
    int location;
} TokenIdentifier;

typedef struct DeclSpec {
    struct TreeNode* type;
    unsigned int type_attr;
    unsigned int type_spec;
    int location;
} DeclSpec;

typedef struct Declarator {
    int unk_00;
    struct TreeNode* unk_04;
} Declarator;

typedef struct TreeNodeList {
    struct TreeNode* first;
    struct TreeNode* last;
} TreeNodeList;

#include "mem.h"
#include "linklist.h"
#include "error.h"
#include "scan.h"
#include "main.h"
#include "modes.h"
#include "symtab.h"
#include "screener.h"
#include "tree.h"
#include "unknown.h"

#endif
