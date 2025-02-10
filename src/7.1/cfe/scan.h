#ifndef SCAN_H
#define SCAN_H

typedef struct TokenIdentifier {
    int unk_00;
    struct Symbol* unk_04;
    int unk_08;
} TokenIdentifier;

union YYLVAL {
    struct TreeNode* node;
    TokenIdentifier identifier;
    int loc;
    int _force_alignment[4];
};

int cpp_line_ptr(char* arg0, char* arg1, int arg2);
int scan();

#endif
