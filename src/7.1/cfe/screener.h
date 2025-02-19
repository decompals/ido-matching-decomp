#ifndef SCREENER_H
#define SCREENER_H

#define TYPESPEC_UNK8000000 0x80000000
#define TYPESPEC_DOUBLE     0x40000000
#define TYPESPEC_FLOAT      0x10000000
#define TYPESPEC_CHAR       0x04000000
#define TYPESPEC_INT        0x02000000
#define TYPESPEC_LONG       0x01000000
#define TYPESPEC_LONGLONG   0x00800000
#define TYPESPEC_SHORT      0x00400000
#define TYPESPEC_SIGNED     0x00200000
#define TYPESPEC_UNSIGNED   0x00100000
#define TYPESPEC_VOID       0x00004000
#define TYPESPEC_ENUM       0x00000800
#define TYPESPEC_UNK80      0x00000080

struct TreeNode* normalize_type(int ts, int location);
int yylex();
int was_plain_char(int);
char* attribute_to_string(unsigned int attr);
char* type_to_string(unsigned int arg0);

#endif
