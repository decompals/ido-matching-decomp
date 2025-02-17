#ifndef SYMTAB_H
#define SYMTAB_H

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
    int unk_10;
    int namelen;
    char name[1];
} Symbol;

#endif
