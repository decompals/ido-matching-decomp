#include "common.h"

#define TREE_UNKNOWN_MACRO_1(t) \
    (TREE_CODE(t) == Struct_type || (TREE_CODE(t) == Enum_type && !(TREE_ATTRIBUTE(t) & PACKED_ATTRIBUTE)))

#define TREE_UNKNOWN_MACRO_2(t)                        \
    TREE_UNKNOWN_MACRO_1(t) && TREE_TYPE(t) != NULL && \
        (TREE_ATTRIBUTE(t) & (VOLATILE_ATTRIBUTE | CONST_ATTRIBUTE | TYPEDEF_ATTRIBUTE))

#define TREE_UNKNOWN_MACRO_3(t) (TREE_UNKNOWN_MACRO_2(t) ? TREE_TYPE(t) : (t))

#define TREE_UNKNOWN_MACRO_4(t)                                                                     \
    (!((TREE_CODE(t) == Array_type) && (ARRAY_TYPE(TREE_UNKNOWN_MACRO_3(t)).index_type == NULL)) && \
     !((TREE_CODE(t) == Struct_type) && (STRUCT_TYPE(TREE_UNKNOWN_MACRO_3(t)).members == NULL)) &&  \
     !((TREE_CODE(t) == Enum_type) && (ENUM_TYPE(TREE_UNKNOWN_MACRO_3(t)).literals == NULL)))

// .data
static int D_1001D430 = 0;
static unsigned int D_1001D434 = 0;

// .bss
static TreeNode*** B_1002BAC0;
static unsigned int* B_1002BAC4;
static unsigned int* B_1002BAC8;

static int func_00419B80(TreeNode* arg0, TreeNode* arg1);
static void func_0041894C(TreeNode* t);

static TreeNode* func_00417880(TreeNode* type) {
    unsigned int level;
    unsigned int s0;
    unsigned int i;

    switch (TREE_CODE(type)) {
        case Struct_type:
            if (STRUCT_TYPE(type).sname == NULL) {
                __assert("STRUCT_TYPE(type).sname != EMPTY", "symtab.c", 114);
            }
            level = ID_DECL(STRUCT_TYPE(type).sname).level;
            break;

        case Enum_type:
            if (ENUM_TYPE(type).ename == NULL) {
                __assert("ENUM_TYPE(type).ename != EMPTY", "symtab.c", 118);
            }
            level = ID_DECL(ENUM_TYPE(type).ename).level;
            break;
        default:
            __assert("FALSE", "symtab.c", 122);
            break;
    }

    if (level >= D_1001D434) {
        s0 = D_1001D434 + 16;
        if (D_1001D434 == 0) {
            B_1002BAC0 = Malloc(0x40);
            B_1002BAC4 = Malloc(0x40);
            B_1002BAC8 = Malloc(0x40);
        } else {
            B_1002BAC0 = Realloc(B_1002BAC0, s0 * 4);
            B_1002BAC4 = Realloc(B_1002BAC4, s0 * 4);
            B_1002BAC8 = Realloc(B_1002BAC4, s0 * 4); // @BUG should be B_1002BAC8 instead of B_1002BAC4
        }

        for (i = D_1001D434; i < s0; i++) {
            B_1002BAC0[i] = NULL;
            B_1002BAC4[i] = 0;
            B_1002BAC8[i] = 0;
        }

        D_1001D434 = s0;
    }

    if (B_1002BAC8[level] <= B_1002BAC4[level]) {
        s0 = B_1002BAC8[level] + 32;
        if (B_1002BAC8[level] == 0) {
            B_1002BAC0[level] = Malloc(0x80);
        } else {
            B_1002BAC0[level] = Realloc(B_1002BAC0[level], s0 * 4);
        }

        B_1002BAC8[level] = s0;
    }

    B_1002BAC0[level][B_1002BAC4[level]] = type;
    B_1002BAC4[level]++;

    return type;
}

static void func_00417BD8(unsigned int level) {
    unsigned int i;
    TreeNode* type;
    TreeNode** s0;

    if (level < D_1001D434) {
        s0 = B_1002BAC0[level];
        for (i = 0; i < B_1002BAC4[level]; i++) {
            type = s0[i];

            switch (TREE_CODE(type)) {
                case Struct_type:
                    TREE_TYPE(type) = NULL;
                    TREE_ATTRIBUTE(type) = NULL;
                    STRUCT_TYPE(type).sname = NULL;
                    STRUCT_TYPE(type).members = NULL;
                    s0[i] = NULL;
                    break;

                case Enum_type:
                    TREE_TYPE(type) = NULL;
                    TREE_ATTRIBUTE(type) = NULL;
                    ENUM_TYPE(type).ename = NULL;
                    ENUM_TYPE(type).literals = NULL;
                    s0[i] = NULL;
                    break;

                default:
                    __assert("FALSE", "symtab.c", 216);
                    break;
            }
        }

        B_1002BAC4[level] = 0;
    }
}

static TreeNode* func_00417D1C(TreeNode* t) {
    int pad;
    TreeNode* copy;
    MemCtx* sp24;

    sp24 = tree_handle;
    tree_handle = general_handle;
    copy = duplicate_node(t);
    tree_handle = sp24;
    return copy;
}

static TreeNode* func_00417D74(TreeNode* t) {
    TreeNode* sp34;
    TreeNode* s1;
    TreeNode* s2;
    TreeNode* v0;
    TreeNode* a;
    TreeNode* b;

    if (t == NULL) {
        return NULL;
    }

    if (t->id <= last_stdtree_id) {
        return t;
    }

    switch (TREE_CODE(t)) {
        case Array_type:
            sp34 = duplicate_node(t);
            ARRAY_TYPE(sp34).index_type = func_00417D74(ARRAY_TYPE(t).index_type);
            TREE_TYPE(sp34) = func_00417D74(TREE_TYPE(t));
            break;

        case Struct_type:
            if (!(TREE_ATTRIBUTE(t) & TYPEDEF_ATTRIBUTE) &&
                !(TREE_ATTRIBUTE(t) & (VOLATILE_ATTRIBUTE | CONST_ATTRIBUTE | UNALIGNED_ATTRIBUTE)) &&
                STRUCT_TYPE(t).sname != NULL && ID_DECL(STRUCT_TYPE(t).sname).level == 2) {
                return t;
            }

            sp34 = duplicate_node(t);
            if (TREE_UNKNOWN_MACRO_2(t)) {
                t = TREE_TYPE(t);
            }

            if (STRUCT_TYPE(t).sname != NULL) {
                if (ID_DECL(STRUCT_TYPE(t).sname).level == 2) {
                    return sp34;
                } else {
                    return func_00417880(sp34);
                }
            }

            TREE_TYPE(sp34) = NULL;
            TREE_ATTRIBUTE(sp34) = NULL;
            STRUCT_TYPE(sp34).sname = NULL;
            STRUCT_TYPE(sp34).members = NULL;
            break;

        case Func_type:
            sp34 = duplicate_node(t);
            s2 = NULL;

            for (s1 = FUNC_TYPE(sp34).params; s1 != NULL; s1 = TREE_LINK(s1)) {
                v0 = func_00417D1C(s1);
                TREE_LINK(v0) = NULL;
                TREE_TYPE(v0) = func_00417D74(TREE_TYPE(s1));

                if (s2 == NULL) {
                    s2 = v0;
                } else {
                    a = s2;
                    b = s2;
                    while (a != NULL) {
                        b = a;
                        a = TREE_LINK(a);
                    }
                    TREE_LINK(b) = v0;
                }
            }

            FUNC_TYPE(sp34).params = s2;
            TREE_TYPE(sp34) = func_00417D74(TREE_TYPE(t));
            break;

        case Enum_type:
            if (!(TREE_ATTRIBUTE(t) & TYPEDEF_ATTRIBUTE) &&
                !(TREE_ATTRIBUTE(t) & (VOLATILE_ATTRIBUTE | CONST_ATTRIBUTE | UNALIGNED_ATTRIBUTE)) &&
                ENUM_TYPE(t).ename != NULL && ID_DECL(ENUM_TYPE(t).ename).level == 2) {
                return t;
            }

            sp34 = duplicate_node(t);
            if (TREE_UNKNOWN_MACRO_2(t)) {
                t = TREE_TYPE(t);
            }

            if (ENUM_TYPE(t).ename != NULL) {
                if (ID_DECL(ENUM_TYPE(t).ename).level == 2) {
                    return sp34;
                } else {
                    return func_00417880(sp34);
                }
            }

            TREE_TYPE(sp34) = NULL;
            TREE_ATTRIBUTE(sp34) = NULL;
            ENUM_TYPE(sp34).ename = NULL;
            ENUM_TYPE(sp34).literals = NULL;
            break;

        case Pointer_type:
            sp34 = duplicate_node(t);
            TREE_TYPE(sp34) = func_00417D74(TREE_TYPE(t));
            if (TREE_TYPE(t) != POINTER_TYPE(t).base_type) {
                POINTER_TYPE(sp34).base_type = func_00417D74(POINTER_TYPE(sp34).base_type);
            }
            break;

        default:
            sp34 = duplicate_node(t);
            break;
    }

    return sp34;
}

static void func_004181C8(TreeNode* t, TreeNode* arg1) {
    TreeNode* sp54;
    TreeNode* s7;
    MemCtx* sp4C;
    TreeNode* v0;
    TreeNode* a2;
    TreeNode* s0;

    sp54 = TREE_TYPE(t);
    sp4C = tree_handle;
    a2 = NULL;

    if (TREE_ATTRIBUTE(t) & EXTERN_ATTRIBUTE) {
        ID_DECL(t).flags |= 0x100;
    }

    for (s7 = arg1; s7 != NULL; s7 = ID_DECL(s7).hidden) {
        for (s0 = s7; s0 != NULL; s0 = ID_DECL(s0).overloads) {
            if ((TREE_ATTRIBUTE(s0) & EXTERN_ATTRIBUTE) && ID_DECL(s0).level == 2 ||
                (TREE_ATTRIBUTE(s0) & STATIC_ATTRIBUTE) && ID_DECL(s0).level == 2) {
                if (ID_DECL(s0).level != ID_DECL(t).level &&
                    (!(TREE_ATTRIBUTE(s0) & (EXTERN_ATTRIBUTE | STATIC_ATTRIBUTE)) || ID_DECL(s0).context == NULL ||
                     ID_DECL(s0).level != 2 || TREE_LOCATION(s0) != -1)) {
                    func_00419B80(t, s0);
                }
                a2 = s0;
            }
        }
    }

    if (a2 != NULL && ID_DECL(a2).level == 2) {
        if (TREE_ATTRIBUTE(a2) & INTR_ATTRIBUTE) {
            TREE_ATTRIBUTE(t) |= INTR_ATTRIBUTE;
        }
    } else {
        tree_handle = general_handle;
        v0 = duplicate_node(t);
        if (a2 != NULL) {
            ID_DECL(v0).blkno = ID_DECL(a2).blkno;
        }
        ID_DECL(v0).flags &= ~0x100;
        TREE_TYPE(v0) = sp54;
        ID_DECL(v0).level = 2;
        ID_DECL(v0).st_list = NULL;
        ID_DECL(v0).overloads = NULL;
        ID_DECL(v0).hidden = NULL;
        TREE_TYPE(v0) = func_00417D74(sp54);

        enter_id(v0);

        if (!options[OPTION_CPLUSPLUS] && !(options[OPTION_ANSI_MODE] & 1) && (TREE_ATTRIBUTE(v0) & EXTERN_ATTRIBUTE)) {
            ID_DECL(v0).context = NULL;
        }

        TREE_ATTRIBUTE(t) = TREE_ATTRIBUTE(v0);
        tree_handle = sp4C;
    }
}

void enter_id(TreeNode* id) {
    TreeNode* s1;
    TreeNode* v0;
    TreeNode* t1;
    int a0;

    if (TREE_CODE(id) != Id_decl) {
        __assert("TREE_CODE(id) == Id_decl", "symtab.c", 489);
    }

    if (ID_DECL(id).id == anonymous || ID_DECL(id).id == NULL) {
        mips_st(id);
        return;
    }

    if (TREE_ATTRIBUTE(id) & WEAK_ATTRIBUTE) {
        mips_st(id);
        return;
    }

    if (debug_arr['T'] > 0) {
        fprintf(dbgout,
                "Entering '%s'(overload class %d, symbol %x, scope %d, overloads %x, hidden %x) from "
                "instance table\n",
                ID_DECL(id).id->name, ID_DECL(id).oclass, ID_DECL(id).id, ID_DECL(id).level, ID_DECL(id).overloads,
                ID_DECL(id).hidden);
    }

    s1 = ID_DECL(id).id->constVal;
    if (s1 == NULL) {
        if ((!(TREE_ATTRIBUTE(id) & EXTERN_ATTRIBUTE) &&
                 !(!(TREE_ATTRIBUTE(id) & STATIC_ATTRIBUTE) && TREE_CODE(TREE_TYPE(id)) == Func_type &&
                   ID_DECL(id).init_value == NULL) ||
             ID_DECL(id).level != 2 || ID_DECL(id).context == NULL) &&
            ID_DECL(id).sclass != 7) {
            mips_st(id);
        }

        ID_DECL(id).id->constVal = id;
        ID_DECL(id).id->unk_10 = 0;
    } else {
        while (ID_DECL(s1).level > ID_DECL(id).level && ID_DECL(s1).hidden != NULL) {
            s1 = ID_DECL(s1).hidden;
        }

        if (ID_DECL(id).level == ID_DECL(s1).level) {
            if (func_00419B80(id, s1) &&
                ((TREE_ATTRIBUTE(id) & EXTERN_ATTRIBUTE) || TREE_CODE(TREE_TYPE(id)) == Func_type) &&
                ID_DECL(id).level >= FUNCTION_SCOPE()) {
                func_004181C8(id, s1);
            }

            return;
        }

        if (((TREE_ATTRIBUTE(id) & EXTERN_ATTRIBUTE) || TREE_CODE(TREE_TYPE(id)) == Func_type) &&
            ID_DECL(id).level >= FUNCTION_SCOPE()) {

            for (t1 = s1, a0 = FALSE; t1 != NULL && !a0; t1 = ID_DECL(t1).hidden) {
                for (v0 = t1; v0 != NULL && !a0; v0 = ID_DECL(v0).overloads) {
                    if ((TREE_ATTRIBUTE(v0) & EXTERN_ATTRIBUTE) ||
                        (!(TREE_ATTRIBUTE(v0) & STATIC_ATTRIBUTE) && TREE_CODE(TREE_TYPE(v0)) == Func_type &&
                         ID_DECL(v0).init_value == NULL) ||
                        (ID_DECL(v0).sclass == 5 || ID_DECL(v0).sclass == 6) && ID_DECL(v0).level == 2) {
                        a0 = TRUE;
                        ID_DECL(id).blkno = ID_DECL(v0).blkno;
                    }
                }
            }
        }

        if (ID_DECL(id).level < ID_DECL(s1).level && ID_DECL(s1).hidden == NULL) {
            if ((!(TREE_ATTRIBUTE(id) & EXTERN_ATTRIBUTE) &&
                     !(!(TREE_ATTRIBUTE(id) & STATIC_ATTRIBUTE) && TREE_CODE(TREE_TYPE(id)) == Func_type &&
                       ID_DECL(id).init_value == NULL) ||
                 ID_DECL(id).level != 2 || ID_DECL(id).context == NULL) &&
                ID_DECL(id).sclass != 7) {
                mips_st(id);
            }

            ID_DECL(s1).hidden = id;
        } else {
            if ((!(TREE_ATTRIBUTE(id) & EXTERN_ATTRIBUTE) &&
                     !(!(TREE_ATTRIBUTE(id) & STATIC_ATTRIBUTE) && TREE_CODE(TREE_TYPE(id)) == Func_type &&
                       ID_DECL(id).init_value == NULL) ||
                 ID_DECL(id).level != 2 || ID_DECL(id).context == NULL) &&
                ID_DECL(id).sclass != 7) {
                mips_st(id);
            }

            ID_DECL(id).hidden = s1;
            ID_DECL(id).id->constVal = id;
        }
    }

    func_0041894C(id);

    if (((TREE_ATTRIBUTE(id) & EXTERN_ATTRIBUTE) || TREE_CODE(TREE_TYPE(id)) == Func_type) &&
        ID_DECL(id).level >= FUNCTION_SCOPE()) {
        func_004181C8(id, s1);
    }
}

static void func_0041894C(TreeNode* id) {
    Scope* v0;
    TreeNode* type;

    v0 = current_scope;
    type = TREE_TYPE(id);

    if (ID_DECL(id).level != current_scope->level) {
        if (ID_DECL(id).level == 2) {
            v0 = file_scope;
        } else if (id != NULL && TREE_CODE(id) == Id_decl && ID_DECL(id).init_value != NULL &&
                   TREE_CODE(TREE_TYPE(id)) == Func_type) {
            v0 = current_scope->parent;
        } else if (TREE_CODE(type) == Label_type) {
            v0 = function_scope;
        } else {
            __assert("FALSE", "symtab.c", 590);
        }
    }

    if (TREE_CODE(TREE_TYPE(id)) == Func_type && ID_DECL(id).level == 2) {
        if (v0->unk_18 == NULL) {
            ID_DECL(id).st_list = v0->unk_00;
            v0->unk_18 = id;
            v0->unk_00 = id;
        } else {
            ID_DECL(id).st_list = ID_DECL(v0->unk_18).st_list;
            ID_DECL(v0->unk_18).st_list = id;
        }
    } else {
        ID_DECL(id).st_list = v0->unk_00;
        v0->unk_00 = id;
    }
}

TreeNode* lookup_id(Symbol* arg0, TreeNode* arg1, int arg2, int arg3, int arg4, int* arg5, int arg6) {
    TreeNode* s0;
    TreeNode* hidden;
    TreeNode* v1; // sp44
    int t1;
    int t0;
    int t2;
    MemCtx* sp34;

    v1 = NULL;
    t1 = TRUE;
    t0 = FALSE;
    t2 = FALSE;
    s0 = arg0->constVal;

    if (!options[OPTION_CPLUSPLUS] && !(options[OPTION_ANSI_MODE] & 1) && arg1 != NULL && arg2 == 3) {
        t0 = (TREE_CODE(arg1) >= Double_type && TREE_CODE(arg1) <= Struct_type) ? TREE_UNKNOWN_MACRO_4(arg1)
                                                                                : TREE_UNKNOWN_MACRO_4(TREE_TYPE(arg1));
    }

    while (s0 != NULL && !t2) {
        hidden = ID_DECL(s0).hidden;
        for (; s0 != NULL && !t2; s0 = ID_DECL(s0).overloads) {
            if ((ID_DECL(s0).oclass == arg2 && arg2 != 3) ||
                (ID_DECL(s0).oclass == arg2 && arg1 == ID_DECL(s0).context)) {
                t2 = TRUE;
                if (arg5 != NULL) {
                    *arg5 = ID_DECL(s0).blkno;
                }

                if (IS_ANSI && (TREE_ATTRIBUTE(s0) & (EXTERN_ATTRIBUTE | STATIC_ATTRIBUTE)) &&
                    ID_DECL(s0).context != NULL && ID_DECL(s0).level == 2) {
                    s0 = NULL;
                }
                break;
            }

            if (ID_DECL(s0).oclass == 3 && t1 && t0) {
                if (v1 == NULL) {
                    v1 = s0;
                } else if (ID_DECL(s0).offset != ID_DECL(v1).offset) {
                    v1 = NULL;
                    t1 = FALSE;
                }
            }
        }

        if (t2) {
            break;
        }

        s0 = hidden;
    }

    if ((!t2 || s0 == NULL) && arg3) {
        if (v1 != NULL) {
            error(0x300FE, LEVEL_WARNING, arg4, arg0->name);
            return v1;
        } else {
            sp34 = tree_handle;
            error(0x30082, LEVEL_ERROR, arg4, arg0->name);
            tree_handle = general_handle;
            s0 = make(Id_decl, arg4, arg0);
            declarator(s0, arg1, 0, arg2, 0, any_type);
            enter_id(s0);
            tree_handle = sp34;
            return NULL;
        }
    }

    if (s0 != NULL && t2 && arg6) {
        if (((TREE_ATTRIBUTE(s0) & EXTERN_ATTRIBUTE) || ID_DECL(s0).level == 2) &&
            (ID_DECL(s0).sclass == 5 || ID_DECL(s0).sclass == 6) && !(ID_DECL(s0).flags & 0x30)) {
            mips_st_extundefined(s0);
            if (arg5 != NULL) {
                *arg5 = ID_DECL(s0).blkno;
            }
        }

        if (!options[OPTION_LINT_FLAGS]) {
            ID_DECL(s0).flags |= 0x30;
        } else {
            lint_setref(s0, arg6, arg4);
        }
    }

    return s0;
}

void push_scope(int arg0) {
    Scope* new_scope;

    if (current_scope == NULL) {
        current_scope = mem_alloc(general_handle, sizeof(Scope), 4);
        current_scope->level = 2;
    } else if (current_scope->child != NULL && current_scope->child->level == current_scope->level + 1) {
        current_scope->child->parent = current_scope;
        current_scope = current_scope->child;
        current_scope->unk_00 = NULL;
        current_scope->unk_18 = NULL;
    } else {
        new_scope = mem_alloc(general_handle, sizeof(Scope), 4);
        new_scope->level = current_scope->level + 1;
        current_scope->child = new_scope;
        new_scope->parent = current_scope;
        current_scope = new_scope;
    }

    current_scope->unk_10 = current_scope->unk_14 = 0;
}

void pop_scope(void) {
    TreeNode* id;
    TreeNode* v1;

    if (current_scope == NULL) {
        __assert("current_scope != NULL", "symtab.c", 742);
    }

    func_00417BD8(current_scope->level);

    for (id = current_scope->unk_00; id != NULL; id = ID_DECL(id).st_list) {
        if (debug_arr['T'] > 0) {
            fprintf(
                dbgout,
                "Removing '%s'(overload class %d, symbol %x, scope %d, overloads %x, hidden %x) from instance table\n",
                ID_DECL(id).id->name, ID_DECL(id).oclass, ID_DECL(id).id, ID_DECL(id).level, ID_DECL(id).overloads,
                ID_DECL(id).hidden);
        }

        if (options[OPTION_LINT_FLAGS] && current_function != NULL) {
            lint_checks(id);
        }

        if (TREE_CODE(TREE_TYPE(id)) == Func_type && (ID_DECL(id).flags & 0x30) &&
            (TREE_ATTRIBUTE(id) & STATIC_ATTRIBUTE)) {
            for (v1 = id; ID_DECL(v1).hidden != NULL; v1 = ID_DECL(v1).hidden) {}
            if (v1 != NULL && (TREE_ATTRIBUTE(v1) & (EXTERN_ATTRIBUTE | STATIC_ATTRIBUTE)) &&
                ID_DECL(v1).context != NULL && ID_DECL(v1).level == 2) {
                ID_DECL(v1).flags = ID_DECL(id).flags;
            }
        }

        if (ID_DECL(id).hidden == NULL) {
            ID_DECL(id).id->constVal = NULL;
            ID_DECL(id).id->unk_10 = 1;
        } else {
            ID_DECL(id).id->constVal = ID_DECL(id).hidden;
            ID_DECL(id).id->unk_10 = 0;
        }
    }

    current_scope = current_scope->parent;
}

static int func_004194B4(TreeNode* arg0, TreeNode* arg1, int arg2) {
    char* sp5C;
    int sp58;
    int sp54;
    TreeNode* v0;
    TreeNode* sp4C;
    int sp48;
    int sp44;

    sp5C = NULL;
    sp58 = 0;

    sp44 = TRUE;
    sp48 = TRUE;
    sp4C = TREE_TYPE(arg1);

    sp54 = (current_scope->level > 2) ||
           (TREE_CODE(sp4C) == Func_type && FUNC_TYPE(sp4C).params != NULL ||
            FUNC_TYPE(sp4C).decls != NULL); // TODO: figure out sp4C code in the last case, probably it's not FUNC_TYPE

    if (ID_DECL(arg0).blkno == 0) {
        ID_DECL(arg0).blkno = ID_DECL(arg1).blkno;
    } else {
        ID_DECL(arg1).blkno = ID_DECL(arg0).blkno;
    }

    if ((TREE_ATTRIBUTE(arg0) & (EXTERN_ATTRIBUTE | STATIC_ATTRIBUTE)) && ID_DECL(arg0).context != NULL &&
        ID_DECL(arg0).level == 2 && (ID_DECL(arg1).sclass == 5 || ID_DECL(arg1).sclass == 6) &&
        ID_DECL(arg1).level == 2) {
        ID_DECL(arg0).context = NULL;
    }

    if ((!((TREE_ATTRIBUTE(arg0) & EXTERN_ATTRIBUTE) || (TREE_ATTRIBUTE(arg0) & STATIC_ATTRIBUTE) ||
           TREE_CODE(TREE_TYPE(arg0)) == Func_type && ID_DECL(arg0).init_value == NULL) ||
         (TREE_ATTRIBUTE(arg0) & EXTERN_ATTRIBUTE) ||
         (!(TREE_ATTRIBUTE(arg0) & STATIC_ATTRIBUTE) && TREE_CODE(TREE_TYPE(arg0)) == Func_type &&
          ID_DECL(arg0).init_value == NULL)) &&
        (TREE_ATTRIBUTE(arg1) & STATIC_ATTRIBUTE)) {

        real_file_line(TREE_LOCATION(arg0), &sp5C, &sp58, 0);
        sp48 = FALSE;

        if (ID_DECL(arg0).init_value != NULL) {
            error(0x30081, LEVEL_ERROR, TREE_LOCATION(arg1), ID_DECL(arg1).id->name, sp58, sp5C);
        } else {
            if (IS_ANSI || ID_DECL(arg1).init_value == NULL) {
                error(0x300F5, LEVEL_WARNING, TREE_LOCATION(arg1), ID_DECL(arg1).id->name);
                error(0x3009C, LEVEL_WARNING, TREE_LOCATION(arg1), ID_DECL(arg1).id->name, sp58, sp5C);
                sp48 = FALSE;
            }

            sp44 = TREE_CODE(sp4C) == Func_type || !(TREE_ATTRIBUTE(arg0) & STATIC_ATTRIBUTE);
        }

        TREE_ATTRIBUTE(arg0) &= ~EXTERN_ATTRIBUTE;
        TREE_ATTRIBUTE(arg0) |= STATIC_ATTRIBUTE;
        sp54 = TRUE;
    } else if ((TREE_ATTRIBUTE(arg0) & STATIC_ATTRIBUTE) && !(TREE_ATTRIBUTE(arg1) & EXTERN_ATTRIBUTE) &&
               !(TREE_ATTRIBUTE(arg1) & STATIC_ATTRIBUTE) &&
               !(TREE_CODE(TREE_TYPE(arg1)) == Func_type && ID_DECL(arg1).init_value == NULL)) {

        error(0x300F5, LEVEL_WARNING, TREE_LOCATION(arg1), ID_DECL(arg1).id->name);
        real_file_line(TREE_LOCATION(arg0), &sp5C, &sp58, 0);
        error(0x3009C, LEVEL_WARNING, TREE_LOCATION(arg1), ID_DECL(arg1).id->name, sp58, sp5C);

        sp44 = TREE_CODE(sp4C) == Func_type;
        sp48 = FALSE;
        TREE_ATTRIBUTE(arg1) &= ~EXTERN_ATTRIBUTE;
        TREE_ATTRIBUTE(arg1) |= STATIC_ATTRIBUTE;
    } else if ((TREE_ATTRIBUTE(arg0) & STATIC_ATTRIBUTE) &&
               ((TREE_ATTRIBUTE(arg1) & EXTERN_ATTRIBUTE) || !(TREE_ATTRIBUTE(arg1) & STATIC_ATTRIBUTE) &&
                                                                 TREE_CODE(TREE_TYPE(arg1)) == Func_type &&
                                                                 ID_DECL(arg1).init_value == NULL)) {

        TREE_ATTRIBUTE(arg1) &= ~EXTERN_ATTRIBUTE;
        TREE_ATTRIBUTE(arg1) |= STATIC_ATTRIBUTE;
    } else if ((TREE_ATTRIBUTE(arg0) & EXTERN_ATTRIBUTE) && ID_DECL(arg0).init_value == NULL &&
               !(TREE_ATTRIBUTE(arg1) & EXTERN_ATTRIBUTE) && !(TREE_ATTRIBUTE(arg1) & STATIC_ATTRIBUTE) &&
               !(TREE_CODE(TREE_TYPE(arg1)) == Func_type && ID_DECL(arg1).init_value == NULL)) {

        sp54 = TRUE;
        TREE_ATTRIBUTE(arg0) &= ~EXTERN_ATTRIBUTE;
    } else if (!options[OPTION_CPLUSPLUS] && !(options[OPTION_ANSI_MODE] & 1) && TREE_CODE(sp4C) != Func_type &&
               (TREE_ATTRIBUTE(arg0) & STATIC_ATTRIBUTE) && (TREE_ATTRIBUTE(arg1) & STATIC_ATTRIBUTE)) {
        real_file_line(TREE_LOCATION(arg0), &sp5C, &sp58, 0);
        error(0x30081, LEVEL_ERROR, TREE_LOCATION(arg1), ID_DECL(arg1).id->name, sp58, sp5C);
        sp48 = FALSE;
    }

    if (sp44 && (sp54 || arg2) &&
        (!(TREE_ATTRIBUTE(arg1) & EXTERN_ATTRIBUTE) &&
             !(!(TREE_ATTRIBUTE(arg1) & STATIC_ATTRIBUTE) && TREE_CODE(TREE_TYPE(arg1)) == Func_type &&
               ID_DECL(arg1).init_value == NULL) ||
         ID_DECL(arg1).level != 2 || ID_DECL(arg1).context == NULL) &&
        ID_DECL(arg1).sclass != 7) {
        mips_st(arg1);
    }

    if (ID_DECL(arg0).blkno == 0) {
        ID_DECL(arg0).blkno = ID_DECL(arg1).blkno;
    }

    v0 = TREE_TYPE(arg0);
    if (ID_DECL(arg1).init_value != NULL && ID_DECL(arg0).init_value == NULL) {
        ID_DECL(arg0).init_value = ID_DECL(arg1).init_value;

        if (TREE_CODE(v0) == Func_type) {
            TREE_TYPE(arg0) = sp4C;
            if (FUNC_TYPE(v0).params != NULL && FUNC_TYPE(sp4C).params == NULL) {
                FUNC_TYPE(sp4C).params = FUNC_TYPE(v0).params;
                FUNC_TYPE(sp4C).decls = NULL;
            }
            FUNC_TYPE(TREE_TYPE(arg0)).fname = arg0;
        }
    } else if (TREE_CODE(v0) == Func_type && FUNC_TYPE(v0).params == NULL && FUNC_TYPE(sp4C).params != NULL) {
        FUNC_TYPE(v0).params = FUNC_TYPE(sp4C).params;
        FUNC_TYPE(v0).decls = NULL;
    }

    return sp48;
}

static int func_00419B80(TreeNode* arg0, TreeNode* arg1) {
    int pad;
    TreeNode* s0;
    TreeNode* sp74;
    TreeNode* sp70;
    int sp6C;
    int sp68;
    char* sp64;
    int sp60;
    int sp5C;
    int sp58;

    sp6C = (!(ID_DECL(arg0).sclass == 5) && !(ID_DECL(arg0).sclass == 6) || !(ID_DECL(arg0).level == 2)) &&
               (!(TREE_ATTRIBUTE(arg0) & EXTERN_ATTRIBUTE) &&
                (!(TREE_ATTRIBUTE(arg0) & STATIC_ATTRIBUTE) || !(TREE_CODE(TREE_TYPE(arg0)) == Func_type))) ||
           (TREE_ATTRIBUTE(arg0) & TYPEDEF_ATTRIBUTE);

    sp64 = NULL;
    sp60 = 0;

    sp58 = TRUE;
    sp74 = TREE_TYPE(arg0);

    sp5C = !TREE_UNKNOWN_MACRO_4(sp74);

    for (s0 = arg1; s0 != NULL; s0 = ID_DECL(s0).overloads) {
        if (ID_DECL(s0).oclass == ID_DECL(arg0).oclass &&
            (ID_DECL(arg0).oclass != 3 || ID_DECL(s0).context == ID_DECL(arg0).context)) {

            if (ID_DECL(arg0).oclass == 3) {
                error(0x300B5, LEVEL_ERROR, TREE_LOCATION(arg0), ID_DECL(arg0).id->name);
                return FALSE;
            }

            sp70 = TREE_TYPE(s0);
            sp68 = type_compatible(sp74, sp70, TRUE);

            if (sp68 == 0) {
                if (ID_DECL(arg0).init_value != NULL && ID_DECL(s0).init_value != NULL) {
                    real_file_line(TREE_LOCATION(s0), &sp64, &sp60, 0);

                    if (TREE_ATTRIBUTE(arg0) & TREE_ATTRIBUTE(s0) & CONST_ATTRIBUTE) {
                        error(0x30081, LEVEL_ERROR, TREE_LOCATION(arg0), ID_DECL(arg0).id->name, sp60, sp64);
                        return FALSE;
                    } else if (sp74 == label_type) {
                        error(0x300C9, LEVEL_ERROR, TREE_LOCATION(arg0), ID_DECL(arg0).id->name);
                        return FALSE;
                    } else if (TREE_CODE(sp74) == Func_type) {
                        error(0x300F8, LEVEL_ERROR, TREE_LOCATION(arg0), ID_DECL(arg0).id->name, sp60, sp64);
                        return FALSE;
                    } else {
                        error(0x30099, LEVEL_ERROR, TREE_LOCATION(arg0), ID_DECL(arg0).id->name);
                        return FALSE;
                    }
                }

                if ((TREE_ATTRIBUTE(s0) & EXTERN_ATTRIBUTE) && ID_DECL(s0).init_value == NULL &&
                    ID_DECL(s0).blkno == 0 && TREE_TYPE(s0) != NULL && TREE_CODE(TREE_TYPE(s0)) != Func_type &&
                    ID_DECL(s0).level == 2 && ID_DECL(arg0).level == 2 &&
                    !((TREE_ATTRIBUTE(arg0) & EXTERN_ATTRIBUTE) && ID_DECL(arg0).init_value == NULL)) {
                    mips_st_extundefined(s0);
                }

                if (!TREE_UNKNOWN_MACRO_4(sp70) && sp5C || TREE_UNKNOWN_MACRO_4(sp70) && sp5C) {
                    if (TREE_UNKNOWN_MACRO_4(sp70) && sp5C && TREE_CODE(sp74) == Array_type &&
                        (TREE_ATTRIBUTE(s0) & EXTERN_ATTRIBUTE) && !(TREE_ATTRIBUTE(arg0) & EXTERN_ATTRIBUTE)) {
                        ARRAY_TYPE(sp74).index_type = ARRAY_TYPE(sp70).index_type;
                        func_004194B4(s0, arg0, TRUE);
                    }

                    ID_DECL(arg0).blkno = ID_DECL(s0).blkno;

                    if ((TREE_ATTRIBUTE(s0) & (EXTERN_ATTRIBUTE | STATIC_ATTRIBUTE)) && ID_DECL(s0).context != NULL &&
                        ID_DECL(s0).level == 2 &&
                        ((ID_DECL(arg0).sclass == 5 || ID_DECL(arg0).sclass == 6) && ID_DECL(arg0).level == 2)) {
                        ID_DECL(s0).context = NULL;
                    }
                    return TRUE;
                }

                if (!options[OPTION_CPLUSPLUS] && !(options[OPTION_ANSI_MODE] & 1) && TREE_CODE(sp74) != Func_type &&
                    (TREE_ATTRIBUTE(arg0) & STATIC_ATTRIBUTE) && (TREE_ATTRIBUTE(s0) & STATIC_ATTRIBUTE)) {
                    real_file_line(TREE_LOCATION(s0), &sp64, &sp60, 0);
                    error(0x30081, LEVEL_ERROR, TREE_LOCATION(arg0), ID_DECL(arg0).id->name, sp60, sp64);
                    return FALSE;
                }

                if (((sp6C && ID_DECL(arg0).oclass == 4) ||
                     (((ID_DECL(s0).sclass != 5 && ID_DECL(s0).sclass != 6 || ID_DECL(s0).level != 2) &&
                       !(TREE_ATTRIBUTE(s0) & EXTERN_ATTRIBUTE) &&
                       (!(TREE_ATTRIBUTE(s0) & STATIC_ATTRIBUTE) || TREE_CODE(TREE_TYPE(s0)) != Func_type)) ||
                      (TREE_ATTRIBUTE(s0) & TYPEDEF_ATTRIBUTE)) &&
                         ID_DECL(s0).oclass == 4) &&
                    (options[OPTION_CPLUSPLUS] || (options[OPTION_ANSI_MODE] & 1) ||
                     !(TREE_ATTRIBUTE(s0) & TYPEDEF_ATTRIBUTE) || !(TREE_ATTRIBUTE(arg0) & TYPEDEF_ATTRIBUTE))) {
                    if (!options[OPTION_CPLUSPLUS] && !(options[OPTION_ANSI_MODE] & 1) && ID_DECL(arg0).sclass == 1 &&
                        ((TREE_ATTRIBUTE(s0) & EXTERN_ATTRIBUTE) || !(TREE_ATTRIBUTE(s0) & STATIC_ATTRIBUTE) &&
                                                                        TREE_CODE(TREE_TYPE(s0)) == Func_type &&
                                                                        ID_DECL(s0).init_value == NULL) &&
                        ID_DECL(s0).level == ID_DECL(arg0).level) {

                        ID_DECL(s0).sclass = ID_DECL(arg0).sclass;
                        ID_DECL(s0).oclass = ID_DECL(arg0).oclass;
                        ID_DECL(s0).offset = ID_DECL(arg0).offset;
                        ID_DECL(s0).alevel = ID_DECL(arg0).alevel;
                        ID_DECL(s0).init_value = ID_DECL(arg0).init_value;
                        ID_DECL(s0).blkno = ID_DECL(arg0).blkno;
                        TREE_ATTRIBUTE(s0) = TREE_ATTRIBUTE(arg0);
                        return FALSE;
                    } else {
                        real_file_line(TREE_LOCATION(s0), &sp64, &sp60, 0);
                        error(0x30081, LEVEL_ERROR, TREE_LOCATION(arg0), ID_DECL(arg0).id->name, sp60, sp64);
                        return FALSE;
                    }
                }

                if (TREE_UNKNOWN_MACRO_4(sp70) && !sp5C && ID_DECL(s0).oclass == 2) {
                    real_file_line(TREE_LOCATION(s0), &sp64, &sp60, 0);
                    error(0x30081, LEVEL_ERROR, TREE_LOCATION(arg0), ID_DECL(arg0).id->name, sp60, sp64);
                    return FALSE;
                }

                if ((!TREE_UNKNOWN_MACRO_4(sp70) && !sp5C) ||
                    (TREE_CODE(sp74) == Struct_type || TREE_CODE(sp74) == Enum_type || TREE_CODE(sp74) == Array_type) &&
                        STRUCT_TYPE(TREE_UNKNOWN_MACRO_3(sp70)).size == 0 &&
                        STRUCT_TYPE(TREE_UNKNOWN_MACRO_3(sp74)).size != 0) { // TODO: type

                    if (TREE_CODE(sp74) == Struct_type) {
                        STRUCT_TYPE(sp70).members = STRUCT_TYPE(sp74).members;
                        ID_DECL(s0).context = ID_DECL(arg0).context;
                        sp58 = func_004194B4(s0, s0, TRUE);
                    } else if (TREE_CODE(sp74) == Enum_type) {
                        ENUM_TYPE(sp70).literals = ENUM_TYPE(sp74).literals;
                        sp58 = func_004194B4(s0, s0, TRUE);
                    } else if (TREE_CODE(sp74) == Array_type) {
                        ARRAY_TYPE(sp70).index_type = ARRAY_TYPE(sp74).index_type;
                        sp58 = func_004194B4(s0, arg0, TRUE);
                    }

                    // TODO: check types
                    if (sp58 || STRUCT_TYPE(TREE_UNKNOWN_MACRO_3(sp70)).size == NULL) {
                        if (TREE_UNKNOWN_MACRO_2(sp74)) {
                            STRUCT_TYPE(sp70).size = STRUCT_TYPE(TREE_TYPE(sp74)).size;
                        } else {
                            STRUCT_TYPE(sp70).size = STRUCT_TYPE(sp74).size;
                        }
                        if (TREE_UNKNOWN_MACRO_2(sp74)) {
                            STRUCT_TYPE(sp70).align = STRUCT_TYPE(TREE_TYPE(sp74)).align;
                        } else {
                            STRUCT_TYPE(sp70).align = STRUCT_TYPE(sp74).align;
                        }
                    }
                    return sp58;
                }

                // 10a8
                if (ID_DECL(arg0).init_value != NULL && ID_DECL(s0).init_value == NULL) {
                    return func_004194B4(s0, arg0, TRUE);
                } else if (ID_DECL(arg0).init_value == NULL && ID_DECL(s0).init_value != NULL) {
                    return func_004194B4(s0, arg0, FALSE);
                } else if (ID_DECL(arg0).init_value == NULL && ID_DECL(s0).init_value == NULL) {
                    return func_004194B4(s0, arg0, FALSE);
                }
            } // end of (sp68 == 0)

            if (sp6C && ID_DECL(arg0).oclass == 4) {
                if (!options[OPTION_CPLUSPLUS] && !(options[OPTION_ANSI_MODE] & 1) && ID_DECL(arg0).sclass == 1 &&
                    ((TREE_ATTRIBUTE(s0) & EXTERN_ATTRIBUTE) || !(TREE_ATTRIBUTE(s0) & STATIC_ATTRIBUTE) &&
                                                                    TREE_CODE(TREE_TYPE(s0)) == Func_type &&
                                                                    ID_DECL(s0).init_value == NULL) &&
                    ID_DECL(s0).level == ID_DECL(arg0).level) {

                    TREE_TYPE(s0) = TREE_TYPE(arg0);
                    ID_DECL(s0).sclass = ID_DECL(arg0).sclass;
                    ID_DECL(s0).oclass = ID_DECL(arg0).oclass;
                    ID_DECL(s0).offset = ID_DECL(arg0).offset;
                    ID_DECL(s0).alevel = ID_DECL(arg0).alevel;
                    ID_DECL(s0).init_value = ID_DECL(arg0).init_value;
                    ID_DECL(s0).blkno = ID_DECL(arg0).blkno;
                    TREE_ATTRIBUTE(s0) = TREE_ATTRIBUTE(arg0);
                    return FALSE;
                } else {
                    real_file_line(TREE_LOCATION(s0), &sp64, &sp60, 0);
                    if (options[OPTION_CPLUSPLUS] || (options[OPTION_ANSI_MODE] & 1) ||
                        (TREE_ATTRIBUTE(arg0) != TYPEDEF_ATTRIBUTE) || (TREE_ATTRIBUTE(arg1) != TYPEDEF_ATTRIBUTE)) {
                        error(0x30081, LEVEL_ERROR, TREE_LOCATION(arg0), ID_DECL(arg0).id->name, sp60, sp64);
                        return FALSE;
                    } else {
                        return TRUE;
                    }
                }
            }

            if ((TREE_ATTRIBUTE(s0) & (EXTERN_ATTRIBUTE | STATIC_ATTRIBUTE)) && ID_DECL(s0).context != NULL &&
                ID_DECL(s0).level == 2 &&
                ((ID_DECL(arg0).sclass == 5 || ID_DECL(arg0).sclass == 6) && ID_DECL(arg0).level == 2)) {
                if ((TREE_CODE(TREE_TYPE(arg0)) == Enum_type || TREE_CODE(TREE_TYPE(arg0)) == Pointer_type ||
                     TREE_CODE(TREE_TYPE(arg0)) >= Double_type && TREE_CODE(TREE_TYPE(arg0)) <= Ushort_type) &&
                    sp68 == 0x300DA) {
                    real_file_line(TREE_LOCATION(s0), &sp64, &sp60, 0);
                    error(0x30081, LEVEL_ERROR, TREE_LOCATION(arg0), ID_DECL(arg0).id->name, sp60, sp64);
                }

                TREE_TYPE(s0) = TREE_TYPE(arg0);
                ID_DECL(arg0).blkno = ID_DECL(s0).blkno;
                ID_DECL(s0).context = NULL;
                mips_st(arg0);

                if (IS_ANSI) {}
            }

            if (IS_ANSI && ID_DECL(s0).level < ID_DECL(arg0).level &&
                (!(TREE_ATTRIBUTE(arg0) & EXTERN_ATTRIBUTE) && !(TREE_ATTRIBUTE(arg0) & STATIC_ATTRIBUTE) ||
                 ID_DECL(s0).level != 2)) {
                return TRUE;
            }

            if (sp68 == 0x300D3) {
                error(sp68, LEVEL_ERROR, TREE_LOCATION(arg0));
                real_file_line(TREE_LOCATION(s0), &sp64, &sp60, 0);
                error(0x3009C, LEVEL_WARNING, TREE_LOCATION(arg0), ID_DECL(arg0).id->name, sp60, sp64);
                return FALSE;
            }

            real_file_line(TREE_LOCATION(s0), &sp64, &sp60, 0);
            error(0x30081, LEVEL_ERROR, TREE_LOCATION(arg0), ID_DECL(arg0).id->name, sp60, sp64);
            ID_DECL(arg0).flags |= 0x200;
            return FALSE;
        }
    }

    if ((!(TREE_ATTRIBUTE(arg0) & EXTERN_ATTRIBUTE) &&
             !(!(TREE_ATTRIBUTE(arg0) & STATIC_ATTRIBUTE) && TREE_CODE(TREE_TYPE(arg0)) == Func_type &&
               ID_DECL(arg0).init_value == NULL) ||
         ID_DECL(arg0).level != 2 || ID_DECL(arg0).context == NULL) &&
        ID_DECL(arg0).sclass != 7) {
        mips_st(arg0);
    }

    ID_DECL(arg0).overloads = ID_DECL(arg1).overloads;
    ID_DECL(arg1).overloads = arg0;
    ID_DECL(arg0).hidden = ID_DECL(arg1).hidden;
    func_0041894C(arg0);
    return TRUE;
}

void mark_id_used(TreeNode* arg0) {
    mips_st_extundefined(arg0);
}

void check_static_functions(void) {
    TreeNode* s0;

    s0 = file_scope->unk_18;

    if (num_errs == 0) {
        while (s0 != NULL) {
            if (TREE_CODE(TREE_TYPE(s0)) != Func_type) {
                break;
            }

            if ((TREE_ATTRIBUTE(s0) & STATIC_ATTRIBUTE) && (ID_DECL(s0).flags & 0x30) &&
                ID_DECL(s0).init_value == NULL) {
                error(0x30116, LEVEL_ERROR, TREE_LOCATION(s0), ID_DECL(s0).id->name);
            }
            s0 = ID_DECL(s0).st_list;
        }
    }
}
