#include "common.h"
#include "y.tab.h"

#define GET_TOKEN() B_1002F1B8 != 0 ? func_0042713C() : scan()

struct LegalTypeSpecifier {
    int unk_00;
    TreeNode* unk_04;
};

struct StringArray {
    unsigned int size;
    YYSTYPE* ptr;
};

struct CharArray {
    unsigned int size;
    char* ptr;
};

struct WCharArray {
    unsigned int size;
    int* ptr;
};

// .data
char* ident = "$Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/targucode/cfe/RCS/screener.c,v 1.4 1993/01/21 15:14:40 hanny Exp $";
struct LegalTypeSpecifier legal_ts[] = {
    { TYPESPEC_CHAR, NULL },
    { TYPESPEC_INT, NULL },
    { TYPESPEC_UNSIGNED, NULL },
    { TYPESPEC_SHORT, NULL },
    { TYPESPEC_LONG, NULL },
    { TYPESPEC_FLOAT, NULL },
    { TYPESPEC_DOUBLE, NULL },
    { TYPESPEC_UNK80, NULL },
    { TYPESPEC_ENUM, NULL },
    { TYPESPEC_VOID, NULL },
    { TYPESPEC_UNSIGNED | TYPESPEC_INT, NULL },
    { TYPESPEC_UNSIGNED | TYPESPEC_SHORT, NULL },
    { TYPESPEC_UNSIGNED | TYPESPEC_LONG, NULL },
    { TYPESPEC_UNK8000000, NULL },
    { TYPESPEC_SHORT | TYPESPEC_INT, NULL },
    { TYPESPEC_LONG | TYPESPEC_INT, NULL },
    { TYPESPEC_SIGNED | TYPESPEC_CHAR, NULL },
    { TYPESPEC_UNSIGNED | TYPESPEC_CHAR, NULL },
    { TYPESPEC_SIGNED | TYPESPEC_SHORT, NULL },
    { TYPESPEC_SIGNED | TYPESPEC_SHORT | TYPESPEC_INT, NULL },
    { TYPESPEC_UNSIGNED | TYPESPEC_SHORT | TYPESPEC_INT, NULL },
    { TYPESPEC_SIGNED, NULL },
    { TYPESPEC_SIGNED | TYPESPEC_INT, NULL },
    { TYPESPEC_SIGNED | TYPESPEC_LONG, NULL },
    { TYPESPEC_SIGNED | TYPESPEC_LONG | TYPESPEC_INT, NULL },
    { TYPESPEC_UNSIGNED | TYPESPEC_LONG | TYPESPEC_INT, NULL },
    { TYPESPEC_LONG | TYPESPEC_DOUBLE, NULL },
    { TYPESPEC_LONG | TYPESPEC_FLOAT, NULL },
    { TYPESPEC_LONGLONG, NULL },
    { TYPESPEC_SIGNED | TYPESPEC_LONGLONG, NULL },
    { TYPESPEC_UNSIGNED | TYPESPEC_LONGLONG, NULL },
    { TYPESPEC_LONGLONG | TYPESPEC_INT, NULL },
    { TYPESPEC_SIGNED | TYPESPEC_LONGLONG | TYPESPEC_INT, NULL },
    { TYPESPEC_UNSIGNED | TYPESPEC_LONGLONG | TYPESPEC_INT, NULL },
};

// .bss
static struct CharArray B_1002F1A0;
static struct WCharArray B_1002F1A8;
static struct StringArray B_1002F1B0;
static int B_1002F1B8;
static YYSTYPE B_1002F1C0;

void init_screener(void) {
    legal_ts[0].unk_04 = options[OPTION_SIGNED] ? char_type : uchar_type;
    legal_ts[1].unk_04 = int_type;
    legal_ts[2].unk_04 = uint_type;
    legal_ts[3].unk_04 = short_type;

    if (!options[OPTION_CPLUSPLUS] && !(options[OPTION_ANSI_MODE] & 1) && BASIC_TYPE(int_type).size == BASIC_TYPE(long_type).size) {
        legal_ts[15].unk_04 = int_type;
        legal_ts[4].unk_04 = int_type;
        legal_ts[23].unk_04 = int_type;
        legal_ts[24].unk_04 = int_type;
    } else {
        legal_ts[24].unk_04 = long_type;
        legal_ts[23].unk_04 = long_type;
        legal_ts[15].unk_04 = long_type;
        legal_ts[4].unk_04 = long_type;
    }

    legal_ts[5].unk_04 = float_type;
    legal_ts[6].unk_04 = double_type;
    legal_ts[7].unk_04 = NULL;
    legal_ts[8].unk_04 = NULL;
    legal_ts[9].unk_04 = void_type;
    legal_ts[10].unk_04 = uint_type;
    legal_ts[11].unk_04 = ushort_type;

    if (!options[OPTION_CPLUSPLUS] && !(options[OPTION_ANSI_MODE] & 1) && BASIC_TYPE(uint_type).size == BASIC_TYPE(ulong_type).size) {
        legal_ts[12].unk_04 = uint_type;
        legal_ts[25].unk_04 = uint_type;
    } else {
        legal_ts[12].unk_04 = ulong_type;
        legal_ts[25].unk_04 = ulong_type;
    }
    
    legal_ts[13].unk_04 = NULL;
    legal_ts[14].unk_04 = short_type;
    legal_ts[16].unk_04 = char_type;
    legal_ts[17].unk_04 = uchar_type;
    legal_ts[18].unk_04 = short_type;
    legal_ts[19].unk_04 = short_type;
    legal_ts[20].unk_04 = ushort_type;
    legal_ts[21].unk_04 = int_type;
    legal_ts[22].unk_04 = int_type;    

    if (BASIC_TYPE(longdouble_type).size == BASIC_TYPE(double_type).size) {
        legal_ts[26].unk_04 = double_type;
    } else {
        legal_ts[26].unk_04 = longdouble_type;
    }

    legal_ts[27].unk_04 = double_type;
    legal_ts[28].unk_04 = longlong_type;
    legal_ts[29].unk_04 = longlong_type;
    legal_ts[30].unk_04 = ulonglong_type;
    legal_ts[31].unk_04 = longlong_type;
    legal_ts[32].unk_04 = longlong_type;
    legal_ts[33].unk_04 = ulonglong_type;
}

static int func_0042713C(void) {
    int tokenId = B_1002F1B8;
    yylval = B_1002F1C0;
    B_1002F1B8 = 0;
    return tokenId;
}

// NON_MATCHING
// url: https://decomp.me/scratch/9dUWy
// score: 18(99.96%)
// only stack diff
int yylex(void) {
    int tokenId;
    int nextTokenId;
    unsigned int numStrings;
    char* str;
    long* wstr;
    int i;
    int len;
    unsigned int str_len;
    char *str_ptr;
    long* wstr_ptr;
    unsigned int wstr_len;
    
    tokenId = GET_TOKEN();
    switch (tokenId) {
        case STRING:
            // concatenate strings
            if (B_1002F1B0.size == 0) {
                B_1002F1B0.size = 256;
                B_1002F1B0.ptr = Realloc(B_1002F1B0.ptr, B_1002F1B0.size * sizeof(YYSTYPE));
                B_1002F1B0.ptr[0] = yylval;
            } else {
                B_1002F1B0.ptr[0] = yylval;
            }

            numStrings = 1;
            while ((nextTokenId = GET_TOKEN()) == tokenId) {
                if (numStrings >= B_1002F1B0.size) {
                    B_1002F1B0.size = numStrings + 256;
                    B_1002F1B0.ptr = Realloc(B_1002F1B0.ptr, (B_1002F1B0.size) * sizeof(YYSTYPE));
                    B_1002F1B0.ptr[numStrings] = yylval;
                } else {
                    B_1002F1B0.ptr[numStrings] = yylval;
                }
                numStrings++;
            }

            B_1002F1B8 = nextTokenId;
            B_1002F1C0 = yylval;
            if (numStrings == 1) {
                // only one string
                yylval = B_1002F1B0.ptr[0];
                return STRING;
            }

            for (i = 0, str_len = 0; i < (int)numStrings; i++) {
                str = str_ptr = STRINGCONSTANT(B_1002F1B0.ptr[i].node).value;
                len = ICONSTANT(ARRAY_TYPE(TREE_TYPE(B_1002F1B0.ptr[i].node)).index_type).value - 1;
                
                while (str_ptr < str + len) {
                    if (str_len >= B_1002F1A0.size) {
                        B_1002F1A0.size = str_len + 256;
                        B_1002F1A0.ptr = Realloc(B_1002F1A0.ptr, B_1002F1A0.size);
                        B_1002F1A0.ptr[str_len] = *str_ptr;
                    } else {
                        B_1002F1A0.ptr[str_len] = *str_ptr;
                    }
                    str_ptr++;
                    str_len++;
                }
            }

            // copy terminating symbol ?
            if (str_len >= B_1002F1A0.size) {
                B_1002F1A0.size = str_len + 256;
                B_1002F1A0.ptr = Realloc(B_1002F1A0.ptr, B_1002F1A0.size);
                B_1002F1A0.ptr[str_len] = *str_ptr;
            } else {
                B_1002F1A0.ptr[str_len] = *str_ptr;
            }

            yylval.node = make(Constant, TREE_LOCATION(B_1002F1B0.ptr[0].node), array_type, B_1002F1A0.ptr, str_len + 1);
            return STRING;
        case WSTRING:
            // concatenate wide strings
            if (B_1002F1B0.size == 0) {
                B_1002F1B0.size = 256;
                B_1002F1B0.ptr = Realloc(B_1002F1B0.ptr, B_1002F1B0.size * sizeof(YYSTYPE));
                B_1002F1B0.ptr[0] = yylval;
            } else {
                B_1002F1B0.ptr[0] = yylval;
            }

            numStrings = 1;
            while ((nextTokenId = GET_TOKEN()) == tokenId) {
                if (numStrings >= B_1002F1B0.size) {
                    B_1002F1B0.size = numStrings + 256;
                    B_1002F1B0.ptr = Realloc(B_1002F1B0.ptr, B_1002F1B0.size * sizeof(YYSTYPE));
                    B_1002F1B0.ptr[numStrings] = yylval;
                } else {
                    B_1002F1B0.ptr[numStrings] = yylval;
                }
                numStrings++;
            }

            B_1002F1B8 = nextTokenId;
            B_1002F1C0 = yylval;
            if (numStrings == 1) {
                // only one string
                yylval = B_1002F1B0.ptr[0];
                return STRING;
            }

            for (i = 0, wstr_len = 0; i < (int)numStrings; i++) {
                wstr = wstr_ptr = WSTRINGCONSTANT(B_1002F1B0.ptr[i].node).value;
                len = ICONSTANT(ARRAY_TYPE(TREE_TYPE(B_1002F1B0.ptr[i].node)).index_type).value - 1;

                while (wstr_ptr < wstr + len) {
                    if (wstr_len >= B_1002F1A8.size) {
                        B_1002F1A8.size = wstr_len + 256;
                        B_1002F1A8.ptr = Realloc(B_1002F1A8.ptr, B_1002F1A8.size * 4);
                        B_1002F1A8.ptr[wstr_len] = *wstr_ptr;
                    } else {
                        B_1002F1A8.ptr[wstr_len] = *wstr_ptr;
                    }
                    wstr_ptr++;
                    wstr_len++;
                }
            }

            if (wstr_len >= B_1002F1A8.size) {
                B_1002F1A8.size = wstr_len + 256;
                B_1002F1A8.ptr = Realloc(B_1002F1A8.ptr, B_1002F1A8.size * 4);
                B_1002F1A8.ptr[wstr_len] = 0;
            } else {
                B_1002F1A8.ptr[wstr_len] = 0;
            }

            yylval.node = make(Constant_special, TREE_LOCATION(B_1002F1B0.ptr[0].node), array_type, B_1002F1A8.ptr, wstr_len + 1);
            return STRING;
        default:
            return tokenId;
    }
}

TreeNode* normalize_type(int ts, int location) {
    int i;

    if (ts == 0) {
        return int_type;
    }

    for (i = 0; i < 34; i++) {
        if (legal_ts[i].unk_00 == ts) {
            if (i == 26) {
                error(0x1200E9, LEVEL_WARNING, location);
            }
            if (i == 27) {
                error(0x1200EA, LEVEL_DEFAULT, location);
            }
            return legal_ts[i].unk_04;
        }
    }

    error(0x20101, LEVEL_ERROR, location);
    return any_type;
}

int was_plain_char(int ts) {
    if ((ts & TYPESPEC_CHAR) && !(ts & TYPESPEC_UNSIGNED) && !(ts & TYPESPEC_SIGNED)) {
        return TRUE;
    }
    return FALSE;
}

char* type_to_string(unsigned int arg0) {
    switch (arg0) {
        case TYPESPEC_CHAR:
            return "char";
        case TYPESPEC_INT:
            return "int";
        case TYPESPEC_UNSIGNED:
            return "unsigned";
        case TYPESPEC_SHORT:
            return "short";
        case TYPESPEC_LONG:
            return "long";
        case TYPESPEC_FLOAT:
            return "float";
        case TYPESPEC_DOUBLE:
            return "double";
        case TYPESPEC_ENUM:
            return "enum";
        case TYPESPEC_VOID:
            return "void";
        case TYPESPEC_SIGNED:
            return "signed";
        default:
            return "((type))";
    }
}

char* attribute_to_string(unsigned int attr) {
    switch (attr) {
        case VOLATILE_ATTRIBUTE:
            return "volatile";
        case CONST_ATTRIBUTE:
            return "constant";
        case TYPEDEF_ATTRIBUTE:
            return "typedef";
        case EXTERN_ATTRIBUTE:
            return "extern";
        case STATIC_ATTRIBUTE:
            return "static";
        case AUTO_ATTRIBUTE:
            return "auto";
        case REGISTER_ATTRIBUTE:
            return "register";
        default:
            return "((qualifier))";
    }
}
