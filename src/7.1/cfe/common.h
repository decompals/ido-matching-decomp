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

typedef struct TokenIdentifier {
    int unk_00;
    struct Symbol* unk_04;
    int unk_08;
} TokenIdentifier;

typedef struct DeclSpec {
    struct TreeNode* unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    int unk_0C;
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
