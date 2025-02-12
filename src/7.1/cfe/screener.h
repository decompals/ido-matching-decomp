#ifndef SCREENER_H
#define SCREENER_H

struct TreeNode* normalize_type(int ts, int location);
int yylex();
int was_plain_char(int);
char* attribute_to_string(unsigned int attr);
char* type_to_string(unsigned int arg0);

#endif
