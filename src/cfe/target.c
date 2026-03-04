#include "common.h"

typedef struct UnkTargetStruct {
    /* 0x00 */ char* name;
    /* 0x04 */ int name_length;
    /* 0x08 */ int offset;
    /* 0x0C */ int type;
} UnkTargetStruct; // size = 0x10

char* ident = "$Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/targucode/cfe/RCS/target.c,v 1.2 1993/01/07 "
              "17:49:29 rdahl Exp $";

char* sc_names[] = { "Template_sc", "Local_sc",  "Heap_sc", "Param_sc",
                     "Readonly_sc", "Static_sc", "Text_sc", "Register_sc" };

int bit_size[] = { 0, 8, 16, 32, 32, 64, 32, 64, 64, 32 };

static UnkTargetStruct D_1001D81C[4] = { { "__$2", 4, 0, Int_type },
                                         { "__$f0", 5, 0, Float_type },
                                         { "__$do", 5, 0, Double_type },
                                         { "__$sp", 5, 0, Pointer_type } };

void enter_registers(void) {
    int i;
    TreeNode* t;
    TreeNode* type;

    D_1001D81C[0].offset = bit_size[9] * 2;
    D_1001D81C[1].offset = bit_size[9] * 32;
    D_1001D81C[2].offset = bit_size[9] * 32;
    D_1001D81C[3].offset = bit_size[9] * 29;

    for (i = 0; i < 4; i++) {
        t = make(Id_decl, -1, string_to_symbol(D_1001D81C[i].name, D_1001D81C[i].name_length));
        ID_DECL(t).offset = D_1001D81C[i].offset;

        switch (D_1001D81C[i].type) {
            case Int_type:
                type = int_type;
                break;
            case Float_type:
                type = float_type;
                break;
            case Double_type:
                type = double_type;
                break;
            case Pointer_type:
                type = make_pointer(uchar_type);
                TREE_TYPE(type) = uchar_type;
                break;
        }

        declarator(t, NULL, 7, 4, 0, type);
        enter_id(t);
    }
}

unsigned int sizeof_type(int type_code) {
    switch (type_code) {
        case Char_type:
            return bit_size[1];
        case Uchar_type:
            return bit_size[1];
        case Short_type:
            return bit_size[2];
        case Ushort_type:
            return bit_size[2];
        case Int_type:
        case Enum_type:
            return bit_size[3];
        case Uint_type:
            return bit_size[3];
        case Signed_type:
            return bit_size[3];
        case Long_type:
            return bit_size[4];
        case Longlong_type:
            return bit_size[5];
        case Unsigned_type:
            return bit_size[3];
        case Ulong_type:
            return bit_size[4];
        case Ulonglong_type:
            return bit_size[5];
        case Double_type:
            return bit_size[7];
        case Float_type:
            return bit_size[6];
        case Longdouble_type:
            return bit_size[8];
        case Pointer_type:
            return bit_size[9];
        default:
            __assert("FALSE", "target.c", 162);
            // no value returned
    }
}

TreeNode* standard_type_size(int size) {
    if (size == bit_size[1]) {
        return char_type;
    }
    if (size == bit_size[2]) {
        return short_type;
    }
    if (size == bit_size[3]) {
        return int_type;
    }
    if (size == bit_size[4]) {
        return long_type;
    }
    if (size == bit_size[5]) {
        return longlong_type;
    }
    __assert("FALSE", "target.c", 182);
    // no value returned
}

TreeNode* max_type_of_size(int size, int is_signed) {
    if (size == bit_size[5]) {
        return is_signed ? longlong_type : ulonglong_type;
    }
    if (size == bit_size[4]) {
        return is_signed ? long_type : ulong_type;
    }
    if (size == bit_size[3]) {
        return is_signed ? int_type : uint_type;
    }
    if (size == bit_size[2]) {
        return is_signed ? short_type : ushort_type;
    }
    if (size == bit_size[1]) {
        return is_signed ? char_type : uchar_type;
    }
    if (size == 64) {
        return is_signed ? int64_type : uint64_type;
    }
    if (size == 32) {
        return is_signed ? int32_type : uint32_type;
    }
    __assert("FALSE", "target.c", 209);
    // no value returned
}

#ifdef NON_EQUIVALENT

#define SAME_SIGNS(x, y) ((x ^ y) >= 0)
#define DIFFERENT_SIGNS(x, y) ((x ^ y) < 0)

int overflows(int expr_code, TreeNode* type, TreeNode* op1, TreeNode* op2) {
    long long val1 = ICONSTANT(op1).value;
    long long val2 = ICONSTANT(op2).value;

    switch (expr_code) {
        case Plus_expr:
            if (IS_SIGNED_TYPE(type)) {
                if (IS_64BIT_TYPE(type)) {
                    return SAME_SIGNS(val1, val2) && DIFFERENT_SIGNS(val1 + val2, val2);
                } else {
                    return SAME_SIGNS((int)ICONSTANT(op1).value, (int)ICONSTANT(op2).value) &&
                           DIFFERENT_SIGNS((int)ICONSTANT(op1).value + (int)ICONSTANT(op2).value,
                                           (int)ICONSTANT(op2).value);
                }
            }
            break;
        case Minus_expr:
            if (IS_SIGNED_TYPE(type)) {
                if (IS_64BIT_TYPE(type)) {
                    return DIFFERENT_SIGNS(val1, val2) && DIFFERENT_SIGNS(val1 - val2, val2);
                } else {
                    return DIFFERENT_SIGNS((int)ICONSTANT(op1).value, (int)ICONSTANT(op2).value) &&
                           DIFFERENT_SIGNS((int)ICONSTANT(op1).value - (int)ICONSTANT(op2).value,
                                           (int)ICONSTANT(op2).value);
                }
            }
            break;
        case Mult_expr:
            if (IS_SIGNED_TYPE(type)) {
                if (IS_64BIT_TYPE(type)) {
                    long long a0 = ICONSTANT(op1).value;
                    long long a1 = ICONSTANT(op2).value;

                    if (a0 != 0 && a1 != 0 && a0 != 1 && a1 != 1) {
                        if (a0 < 0) {
                            if (a0 == __LONGLONG_MIN) {
                                return TRUE;
                            }
                            a0 = -a0;
                        }
                        if (a1 < 0) {

                            if (a1 == __LONGLONG_MIN) {
                                return TRUE;
                            }
                            a1 = -a1;
                        }
                        return a1 > __LONGLONG_MAX / a0;
                    }
                } else {
                    int a0 = (int)ICONSTANT(op1).value;
                    int a1 = (int)ICONSTANT(op2).value;
                    if (a0 != 0 && a1 != 0 && a0 != 1 && a1 != 1) {
                        if (a0 < 0) {
                            if ((int)ICONSTANT(op1).value == INT_MIN) {
                                return TRUE;
                            }
                            a0 = -a0;
                        }
                        if (a1 < 0) {
                            if ((int)ICONSTANT(op2).value == INT_MIN) {
                                return TRUE;
                            }
                            a1 = -(int)ICONSTANT(op2).value;
                        }
                        return a1 > INT_MAX / a0;
                    }
                }
            }
            break;
        case Div_expr:
            if (IS_SIGNED_TYPE(type)) {
                if (IS_64BIT_TYPE(type)) {
                    return ICONSTANT(op1).value == __LONGLONG_MIN && ICONSTANT(op2).value == -1;
                } else {
                    return (int)ICONSTANT(op1).value == INT_MIN && (int)ICONSTANT(op2).value == -1;
                }
            }
            break;
    }

    return FALSE;
}

#else
#pragma GLOBAL_ASM("asm/7.1/functions/cfe/target/overflows.s")
#endif

double str_to_double(char* str, int location, int warning_level) {
    double result;

    set_fpc_csr(0);
    result = atof(str);
    if (fp_class_d(result) == FP_POS_INF) {
        error(0x3010D, warning_level, location, "double");
    }
    return result;
}

float str_to_float(char* str, int location, int warning_level) {
    double result;
    double epsilon = 8.222875e-48;

    result = atof(str);
    if (fp_class_d(result) == FP_POS_INF) {
        error(0x3010D, warning_level, location, "float");
    } else if (result != 0 && (result > FLT_MAX || result < FLT_MIN - epsilon)) {
        error(0x3010D, warning_level, location, "float");
    }
    return result;
}

// TODO check types of nodes
int va_encoded_state(TreeNode* t) {
    TreeNode* decls = FUNC_TYPE(TREE_TYPE(t)).decls;
    int res = 0;

    if (decls == NULL) {
        return 0;
    }
    if (TREE_CODE(TREE_TYPE(TREE_TYPE(t))) == Struct_type) {
        return 0;
    }

    if (ID_DECL(decls).id == builtins[2]) {
        res = 1;
    } else if (TREE_CODE(TREE_TYPE(decls)) == Double_type && TREE_LINK(decls) != NULL &&
               ID_DECL(TREE_LINK(decls)).id == builtins[2]) {
        res = 2;
    }

    return res;
}