#ifndef SYMTAB_H
#define SYMTAB_H

#include "tree.h"

#define FUNCTION_SCOPE() (function_scope == NULL ? -1U : function_scope->level)

typedef struct ParseSymbol {
    LinkedListEntry link;
    int id;
    int level;
} ParseSymbol;

struct TreeNode;

typedef struct Symbol {
    struct TreeNode* constVal;
    ParseSymbol* psymb;
    int unk_08;
    int unk_0C;
    short unk_10;
    short unk_12;
    int namelen;
    char name[1];
} Symbol;

void enter_id(TreeNode* id);

#endif
