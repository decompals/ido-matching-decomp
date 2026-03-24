#include "stdio.h"
#include "stdlib.h"
#include "cmplrs/usys.h"
#include "cmplrs/ucode.h"


#define SQ(x) (x * x)
#define HI(x) (*((unsigned int*)&x))
#define LO(x) (*((unsigned int*)&x + 1))

extern int current_line;
extern int print_warnings;

#ifdef __GNUC__
    #pragma GCC diagnostic ignored "-Wsign-compare"
#endif

void warning(char* warn) {
    if (print_warnings != 0) {
        fprintf(stderr, "ugen: warning: line %d: %s\n", current_line, warn);
    }
}

static int func_0040AE00(long long arg0, long long arg1, int arg2) {
    if (arg2 != 0) {
        return (((arg0 ^ arg1) >= 0)) && (((arg0 + arg1) ^ arg0) < 0);
    }

    return (~(unsigned long long)arg0 < arg1);
}

static int func_0040AEAC(long long arg0, long long arg1, int arg2) {

    if (arg2 != 0) {
        return (((arg0 ^ arg1) < 0)) && (((arg0 - arg1) ^ arg0) < 0);
    }
    
    return (unsigned long long)arg0 < arg1;
}

int fold_constant(enum Uopcode opc, long long op1, long long op2, int is_signed, int arg5, int arg6, long long* arg7) {
    long long sp40;
    long long temp1;
    long long temp2;
    unsigned long long unsigned_op2 = op2;

    switch (opc) {
    case Ucvtl:
        if (arg6) {
            return 0;
        }

        temp1 = (((long long)1 << op2) - 1);
        sp40 = op1 & temp1;
        if (is_signed) {
            // is this an optimisation of something else?
            
            temp2 = ((long long)1 << (op2 - 1));
            temp1 = sp40;
            temp1 ^= temp2;
            sp40 = temp1 - temp2;
        }
        break;
    case Uadd:
        if (arg6 && (func_0040AE00(op1, op2, is_signed))) {
            return 0;
        }
        sp40 = op1 + op2;
        break;
    case Usub:
        if (arg6 && func_0040AEAC(op1, op2, is_signed)) {
            return 0;
        }
        sp40 = op1 - op2;
        break;
    case Umpy:
        if (arg6) {
            return 0;
        }
        sp40 = op1 * op2;
        break;
    case Udiv:
        if (op2 == 0) {
            warning("divide by zero");
            return 0;
        }
        if (is_signed) {
            if (arg6 && op1 == -0x80000000LL && (HI(op2) == -1) && (LO(op2) == -1)) {
                return 0;
            }
            sp40 = op1 / op2;
            break;
        }
        sp40 = op1 / unsigned_op2;
        break;
    case Umod:
        if (op2 == 0) {
            warning("divide by zero");
            return 0;
        }
        if (is_signed) {
            sp40 = op1 % op2;
        } else {
            sp40 = op1 % unsigned_op2;
        }
        break;
    case Uand:
        sp40 = op1 & op2;
        break;
    case Uior:
        sp40 = op1 | op2;
        break;
    case Uxor:
        sp40 = op1 ^ op2;
        break;
    case Ushl:
        if (arg5) {
            sp40 = (int)op1 << op2;
        } else {
            sp40 = op1 << op2;
        }
        break;
    case Ushr: {
        if (arg5) {
            if (is_signed) {
                sp40 = (signed int)op1 >> op2;
            } else {
                sp40 = (unsigned int)op1 >> op2;
            }
        } else {
            if (is_signed) {
                sp40 = op1 >> op2;
            } else {
                sp40 = (unsigned long long)op1 >> unsigned_op2;
            }
        }
        break;
    }
    case Unot:
        sp40 = ~op1;
        break;
    case Ulnot:
        sp40 = ( int)!op1;
        break;
    case Usqr:
        if (arg6) {
            return 0;
        }
        sp40 = SQ(op1);
        break;
    case Uneg:
        if (arg6 && is_signed && (op1 == -0x80000000LL)) {
            return 0;
        }
        sp40 = -op1 ;
        break;
    case Uabs:
        if (is_signed && (op1 == -0x80000000LL)) {
            if (arg6) {
                return 0;
            }
            sp40 = op1;
            break;
        }
        if (is_signed && (op1 < 0)) {
            sp40 = -op1;
        } else {
            sp40 = op1;
        }
        break;
    case Uodd:
        if (op1 % 2 == 0) {
            sp40 = 0;
        } else {
            sp40 = 1;
        }
        break;
    case Ugeq:
        if (is_signed) {
            sp40 = op1 >= op2;
        } else {
            sp40 = op1 >= unsigned_op2;
        }
        break;
    case Ugrt:
        if (is_signed) {
            sp40 = op1 > op2;
        } else {
            sp40 = op1 > unsigned_op2;
        }
        break;
    case Uleq:
        if (is_signed) {
            sp40 = op1 <= op2;
        } else {
            sp40 = op1 <= unsigned_op2;
        }
        break;
    case Ules:
        if (is_signed) {
            sp40 = op1 < op2;
        } else {
            sp40 = op1 < unsigned_op2;
        }
        break;
    case Uequ:
        sp40 = op1 == op2;
        break;
    case Uneq:
        sp40 = op1 != op2;
        break;
    case Umin:
        if (is_signed) {
            // sp40 = MIN(op1, op2);
            if ((long long)(op2 >= op1)) {
                sp40 = op1;
            } else {
                sp40 = op2;
            }
        } else {
            if (unsigned_op2 >= op1) {
                sp40 = op1;
            } else {
                sp40 = unsigned_op2;
            }
        }
        break;
    case Umax:
        if (is_signed) {
            if ((long long)(op1 >= op2)) {
                sp40 = op1;
            } else {
                sp40 = op2;
            }
        } else {
            if (op1 >= unsigned_op2) {
                sp40 = op1;
            } else {
                sp40 = unsigned_op2;
            }
        }
        break;
    case Udup: // Duplicates the top stack item.
        sp40 = op1;
        break;
    default:
        return 0;
    }
    *arg7 = sp40;
    return 1;
}

int fold_identities(enum Uopcode opc, long long dword, int cond) {
        
    switch (opc) {
        case Uadd:
        case Uior:
        case Uxor:
            if (dword == 0) {
                return 1;
            }
            break;
        case Ushl:
        case Ushr:
        case Usub:
            if (dword == 0 && cond) {
                return 1;
            }
            break;
        case Uand:
            if (HI(dword) == -1 && LO(dword) == -1) {
                return 1;
            }
            break;
        case Umpy:
            if (dword == 1) {
                return 1;
            }
            break;
        case Udiv:
            if (dword == 1 && cond) {
                return 1;
            }
            break;
        default:
            return 0;
    }
    
    return 0;
}

int fold_idempotents(enum Uopcode opc, long long dwval, int cond, long long* arg5) {
    switch (opc) {
    case Uand:
    case Umpy:
        if (dwval == 0) {
            *arg5 = 0;
            return 1;
        }
        break;
    case Uior:
        if (HI(dwval) == -1 && LO(dwval) == -1) {
            *arg5 = -1;
            return 1;
        }
        break;
    case Umod:
    case Urem:
        if (dwval == 1 && cond != 0) {
            *arg5 = 0;
            return 1;
        }
        break;

    default:
        return 0;
        
    }
    return 0;
}
