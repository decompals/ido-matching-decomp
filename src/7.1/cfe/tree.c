#ifdef __GNUC__
// workaround to pass gcc check
#define __STDARG_H__
#define va_list int
#define va_start(x, y)
#define va_arg(x, y) (0)
#endif

#include "common.h"

// .data
static int last_node_id = 0;
static int is_making_constant = FALSE;

char* type_name[] = {
    "ident",
    "double",
    "long double",
    "float",
    "label",
    "char",
    "int",
    "long",
    "long long",
    "short",
    "signed",
    "unsigned",
    "unsigned char",
    "unsigned int",
    "unsigned long",
    "unsigned long long",
    "unsigned short",
    "void",
    "any type",
    "array",
    "enum",
    "function",
    "pointer",
    "reference",
    "struct",
};

static char* code_name[] = {
    "Identifier",
    "Double_type",
    "Longdouble_type",
    "Float_type",
    "Label_type",
    "Char_type",
    "Int_type",
    "Long_type",
    "Longlong_type",
    "Short_type",
    "Signed_type",
    "Unsigned_type",
    "Uchar_type",
    "Uint_type",
    "Ulong_type",
    "Ulonglong_type",
    "Ushort_type",
    "Void_type",
    "Any_type",
    "Array_type",
    "Enum_type",
    "Func_type",
    "Pointer_type",
    "Reference_type",
    "Struct_type",
    "Break_stmt",
    "Caselabeled_stmt",
    "Compound_stmt",
    "Continue_stmt",
    "Defaultlabeled_stmt",
    "Dowhile_stmt",
    "Expr_stmt",
    "For_stmt",
    "Goto_stmt",
    "Idlabeled_stmt",
    "If_stmt",
    "Init",
    "Return_stmt",
    "Switch_stmt",
    "While_stmt",
    "Try_stmt",
    "Leave_stmt",
    "Addr_expr",
    "Alignof_expr",
    "Bitcomplement_expr",
    "Classof_expr",
    "Indirect_expr",
    "Not_expr",
    "Postdecrement_expr",
    "Postincrement_expr",
    "Predecrement_expr",
    "Preincrement_expr",
    "Sizeof_expr",
    "Uminus_expr",
    "Uplus_expr",
    "Delete_expr",
    "Addrrel_expr",
    "And_expr",
    "Assign_expr",
    "Bitand_expr",
    "Bitor_expr",
    "Bitxor_expr",
    "Bitand_assign_expr",
    "Bitor_assign_expr",
    "Bitxor_assign_expr",
    "Call_expr",
    "Cast_expr",
    "Comma_expr",
    "Div_expr",
    "Div_assign_expr",
    "Eq_expr",
    "Gt_expr",
    "Geq_expr",
    "Index_expr",
    "Leq_expr",
    "Lshift_expr",
    "Lshift_assign_expr",
    "Lt_expr",
    "Minus_expr",
    "Minus_assign_expr",
    "Rem_expr",
    "Rem_assign_expr",
    "Mult_expr",
    "Mult_assign_expr",
    "Neq_expr",
    "Or_expr",
    "Plus_expr",
    "Plus_assign_expr",
    "Rshift_expr",
    "Rshift_assign_expr",
    "New_expr",
    "Member_init_expr",
    "Conditional_expr",
    "Aggregate_expr",
    "Array_ref",
    "Component_ref",
    "Indirect_component_ref",
    "Qualified_ref",
    "Declare_decl",
    "Id_decl",
    "Field_decl",
    "Constant",
    "End_of_file",
    "Nop",
    "Constant_special",
    "Error_mark",
    "Pragma",
    "Access_spec",
    "Reserved"
};

struct AttrDesc attr_list[] = {
    { VOLATILE_ATTRIBUTE,           "VOL" },
    { CONST_ATTRIBUTE,              "CONST" },
    { PACKED_ATTRIBUTE,             "PACK" },
    { TYPEDEF_ATTRIBUTE,               "TYPE" },
    { EXTERN_ATTRIBUTE,             "EXT" },
    { STATIC_ATTRIBUTE,             "STAT" },
    { AUTO_ATTRIBUTE,               "AUTO" },
    { REGISTER_ATTRIBUTE,           "REG" },
    { PROTECTED_ATTRIBUTE,          "PROT" },
    { PUBLIC_ATTRIBUTE,             "PUB" },
    { PRIVATE_ATTRIBUTE,            "PRIV" },
    { VIRTUAL_ATTRIBUTE,            "VIRT" },
    { FRIEND_ATTRIBUTE,             "FRIE" },
    { INLINE_ATTRIBUTE,             "INL" },
    { VAL_ATTRIBUTE,                "VAL" },
    { REF_ATTRIBUTE,                "REF" },
    { VAR_ATTRIBUTE,                "VAR" },
    { TRY_ATTRIBUTE,                "TRY" },
    { INTR_ATTRIBUTE,               "INTR" },
    { NO_SIDE_EFFECT_ATTRIBUTE,     "NO_SIDE_EFFECT" },
    { TMP_REGS_INTACT_ATTRIBUTE,    "TMP_REGS_INTACT" },
    { WEAK_ATTRIBUTE,               "WEAK" },
    { INTU_ATTRIBUTE,               "INTU" },
    { CONSTRUCTOR_ATTRIBUTE,        "CONSTUCTOR" }, // typo
    { DESTRUCTOR_ATTRIBUTE,         "DESTRUCTOR" },
    { OPERATOR_ATTRIBUTE,           "OPER" },
    { PTR_TO_MEM_ATTRIBUTE,         "PTR_TO_MEM" },
    { ACCESS_ADJUST_ATTRIBUTE,      "ACCESS_ADJUST" },
    { UNALIGNED_ATTRIBUTE,          "UNALIGNED" },
    { CLINKAGE_ATTRIBUTE,           "CLINKAGE" },
    { CPLUSLINKAGE_ATTRIBUTE,       "CPLUSLINKAGE" },
    { FVAL_TRUEARRAY_ATTRIBUTE,     "FVAL(TRUEARRAY)" },
    { SWAP_ATTRIBUTE,               "SWAP" },
    { TMP_ATTRIBUTE,                "TMP" },
    { BL_ATTRIBUTE,                 "BL" },
    { BR_ATTRIBUTE,                 "BR" },
    { LL_ATTRIBUTE,                 "LL" },
    { LR_ATTRIBUTE,                 "LR" },
    { UNSC_ATTRIBUTE,               "UNSC" },
    { PLAIN_ATTRIBUTE,              "PLAIN" },
};

// .bss
/* 0x1002C2F0 */ static int* is_visited;
/* 0x1002C2F4 */ static int current_depth;

void set_visited(int value, int id) {
    is_visited[id] = value;
}

int get_visited(int id) {
    return is_visited[id];
}

char* get_type_name(int code) {
    if (code >= Identifier && code <= Struct_type) {
        return type_name[code];
    }
    return "???";
}

char* code_to_string(int code) {
    return code_name[code];
}

void display_attr(int attr) {
    int i;
    int foundAttrs = 0;
    int found = FALSE;
    
    if (attr == 0) {
        fprintf(stderr, "0 ");
        return;
    }

    for (i = 0; i < 40; i++) {
        if (attr_list[i].value & attr) {
            fprintf(stderr, "%s%s", found ? "|" : "", attr_list[i].desc);
            found = TRUE;
            foundAttrs = foundAttrs | attr_list[i].value;
        }
    }

    if (foundAttrs != attr) {
        fprintf(stderr, "|%x", foundAttrs ^ attr);
    }
    fprintf(stderr, " ");
}

void display_node(TreeNode* t) {
    int i;
    char* file;
    int line;
    int j;
    int k;
    int l;
    
    if (t == NULL) {
        return;
    }
    fprintf(stderr, "%2u ", TREE_ID(t));
    for (i = 0; i < current_depth; i++) {
        fprintf(stderr, " .");
    }

    fprintf(stderr, "%-14s ", code_name[TREE_CODE(t)]);
    fprintf(stderr, "type=%u ", TREE_ID(TREE_TYPE(t)));
    fprintf(stderr, "attr=");
    display_attr(TREE_ATTRIBUTE(t));
    fprintf(stderr, "link=%u ", TREE_ID(TREE_LINK(t)));
    real_file_line(TREE_LOCATION(t), &file, &line, 0);
    fprintf(stderr, "<%s/%d> ", file, line);

    switch (TREE_CODE(t)) {
        case Double_type:
        case Longdouble_type:
        case Float_type:
        case Label_type:
        case Char_type:
        case Int_type:
        case Long_type:
        case Longlong_type:
        case Short_type:
        case Signed_type:
        case Unsigned_type:
        case Uchar_type:
        case Uint_type:
        case Ulong_type:
        case Ulonglong_type:
        case Ushort_type:
        case Void_type:
        case Any_type:
            fprintf(stderr, "size=%u ", BASIC_TYPE(t).size);
            fprintf(stderr, "align=%u\n", BASIC_TYPE(t).align);
            break;
        case Array_type:
            fprintf(stderr, "size=%u ", ARRAY_TYPE(t).size);
            fprintf(stderr, "align=%u ", ARRAY_TYPE(t).align);
            fprintf(stderr, "\tindex_type=%d\n", TREE_ID(ARRAY_TYPE(t).index_type));
            break;
        case Struct_type:
            fprintf(stderr, "size=%u ", STRUCT_TYPE(t).size);
            fprintf(stderr, "align=%u ", STRUCT_TYPE(t).align);
            fprintf(stderr, "sname=%u ", TREE_ID(STRUCT_TYPE(t).sname));
            fprintf(stderr, "members=%u ", TREE_ID(STRUCT_TYPE(t).members));
            fprintf(stderr, "baselist=%u ", TREE_ID(STRUCT_TYPE(t).baselist));
            fprintf(stderr, "info=[");
            if (STRUCT_TYPE(t).info & STRUCT_INFO_STRUCT) {
                fprintf(stderr, "struct ");
            } else if (STRUCT_TYPE(t).info & STRUCT_INFO_UNION) {
                fprintf(stderr, "union ");
            } else if (STRUCT_TYPE(t).info & STRUCT_INFO_CLASS) {
                fprintf(stderr, "class ");
            }
            if (STRUCT_TYPE(t).info & STRUCT_INFO_CONST_MEMBERS) {
                fprintf(stderr, "const-members ");
            }
            if (STRUCT_TYPE(t).info & STRUCT_INFO_VOLATILE_MEMBERS) {
                fprintf(stderr, "volatile-members ");
            }
            if (STRUCT_TYPE(t).info & STRUCT_INFO_PACKED) {
                fprintf(stderr, "packed");
            }
            if (STRUCT_TYPE(t).info & STRUCT_INFO_COMPLETE) {
                fprintf(stderr, "complete");
            }
            fprintf(stderr, "]\n");
            break;
        case Enum_type:
            fprintf(stderr, "size=%u ", ENUM_TYPE(t).size);
            fprintf(stderr, "align=%u ", ENUM_TYPE(t).align);
            fprintf(stderr, "ename=%u ", TREE_ID(ENUM_TYPE(t).ename));
            fprintf(stderr, "literals=%u ", TREE_ID(ENUM_TYPE(t).literals));
            fprintf(stderr, "lb=%d ", ENUM_TYPE(t).lb);
            fprintf(stderr, "ub=%d\n", ENUM_TYPE(t).ub);
            break;
        case Func_type:
            fprintf(stderr, "size=%u ", FUNC_TYPE(t).size);
            fprintf(stderr, "align=%u ", FUNC_TYPE(t).align);
            fprintf(stderr, "fname=%u ", TREE_ID(FUNC_TYPE(t).fname));
            fprintf(stderr, "params=%u ", TREE_ID(FUNC_TYPE(t).params));
            fprintf(stderr, "decls=%u ", TREE_ID(FUNC_TYPE(t).decls));
            fprintf(stderr, "psize=%u ", FUNC_TYPE(t).psize);
            fprintf(stderr, "end_blkno=%d ", FUNC_TYPE(t).end_blkno);
            fprintf(stderr, "handlers=%u\n", TREE_ID(FUNC_TYPE(t).handlers));
            break;
        case Reference_type:
            fprintf(stderr, "size=%u ", POINTER_TYPE(t).size);
            fprintf(stderr, "align=%u ", POINTER_TYPE(t).align);
            fprintf(stderr, "base_type=%u\n", TREE_ID(POINTER_TYPE(t).base_type));
            break;
        case Pointer_type:
            fprintf(stderr, "size=%u ", POINTER_TYPE(t).size);
            fprintf(stderr, "align=%u ", POINTER_TYPE(t).align);
            fprintf(stderr, "base_type=%u\n", TREE_ID(POINTER_TYPE(t).base_type));
            break;
        case Field_decl:
            fprintf(stderr, "field=%u ", TREE_ID(FIELD_DECL(t).field));
            fprintf(stderr, "width=%d\n", FIELD_DECL(t).width);
            break;
        case Id_decl:
            fprintf(stderr, "id=%s ", ID_DECL(t).id->name);
            fprintf(stderr, "init_value=%u ", TREE_ID(ID_DECL(t).init_value));
            fprintf(stderr, "qualifiers=%u ", TREE_ID(ID_DECL(t).qualifiers));
            fprintf(stderr, "offset=%d ", ID_DECL(t).offset);
            fprintf(stderr, "sclass=%s ", sc_names[ID_DECL(t).sclass]);
            fprintf(stderr, "level=%u ", ID_DECL(t).level);
            fprintf(stderr, "alevel=%u ", ID_DECL(t).alevel);
            fprintf(stderr, "hidden=%u ", TREE_ID(ID_DECL(t).hidden));
            fprintf(stderr, "st_list=%u ", TREE_ID(ID_DECL(t).st_list));
            fprintf(stderr, "context=%u ", TREE_ID(ID_DECL(t).context));
            fprintf(stderr, "blkno=%u ", ID_DECL(t).blkno);
            fprintf(stderr, "flags=%u ", ID_DECL(t).flags);
            fprintf(stderr, "overloads=%u ", TREE_ID(ID_DECL(t).overloads));
            fprintf(stderr, "oclass=%d ", ID_DECL(t).oclass);
            if (ID_DECL(t).lastused != 0) {
                real_file_line(ID_DECL(t).lastused, &file, &line, 0);
            }
            fprintf(stderr, "lastused=<%s/%d>\n", file, line);
            break;
        case Declare_decl:
            fprintf(stderr, "ids=%u\n", TREE_ID(DECLARE_DECL(t).ids));
            break;
        case If_stmt:
            fprintf(stderr, "expr=%u ", TREE_ID(IF_STMT(t).expr));
            fprintf(stderr, "then_part=%u ", TREE_ID(IF_STMT(t).then_part));
            fprintf(stderr, "else_part=%u\n", TREE_ID(IF_STMT(t).else_part));
            break;
        case Init:
            fprintf(stderr, "value=%u ", TREE_ID(INIT(t).value));
            fprintf(stderr, "replicate=%d ", INIT(t).replicate);
            fprintf(stderr, "ExtendedSize=%d ", INIT(t).ExtendedSize);
            fprintf(stderr, "start_offset=%d\n", INIT(t).start_offset);
            break;
        case Caselabeled_stmt:
            fprintf(stderr, "expr=%u ", TREE_ID(LABELED_STMT(t).expr));
            fprintf(stderr, "stmt=%u ", TREE_ID(LABELED_STMT(t).stmt));
            fprintf(stderr, "label=%d\n", LABELED_STMT(t).label);
            break;
        case Defaultlabeled_stmt:
            fprintf(stderr, "stmt=%u\n", TREE_ID(LABELED_STMT(t).stmt));
            break;
        case Idlabeled_stmt:
            fprintf(stderr, "id=%s ", GET_IDENTIFIER(LABELED_STMT(t).id).id->name);
            fprintf(stderr, "stmt=%u\n", TREE_ID(LABELED_STMT(t).stmt));
            break;
        case Compound_stmt:
            fprintf(stderr, "decls=%u ", TREE_ID(COMPOUND_STMT(t).decls));
            fprintf(stderr, "stmts=%u ", TREE_ID(COMPOUND_STMT(t).stmts));
            real_file_line(COMPOUND_STMT(t).end_location, &file, &line, 0);
            fprintf(stderr, "end_location=<%s/%d> ", file, line);
            fprintf(stderr, "context=%u ", TREE_ID(COMPOUND_STMT(t).context));
            fprintf(stderr, "cg_info=%x\n", COMPOUND_STMT(t).cg_info);
            break;
        case Expr_stmt:
            fprintf(stderr, "expr=%u\n", TREE_ID(EXPR_STMT(t).expr));
            break;
        case Switch_stmt:
            fprintf(stderr, "expr=%u ", TREE_ID(SWITCH_STMT(t).expr));
            fprintf(stderr, "stmt=%u ", TREE_ID(SWITCH_STMT(t).stmt));
            fprintf(stderr, "breaklab=%d ", SWITCH_STMT(t).breaklab);
            fprintf(stderr, "cases=%u\n", TREE_ID(SWITCH_STMT(t).cases));
            break;
        case While_stmt:
            fprintf(stderr, "expr=%u ", TREE_ID(WHILE_STMT(t).expr));
            fprintf(stderr, "stmt=%u ", TREE_ID(WHILE_STMT(t).stmt));
            fprintf(stderr, "breaklab=%d contlab=%d\n", WHILE_STMT(t).breaklab, WHILE_STMT(t).contlab);
            break;
        case Try_stmt:
            fprintf(stderr, "expr=%u ", TREE_ID(TRY_STMT(t).expr));
            fprintf(stderr, "guard=%u ", TREE_ID(TRY_STMT(t).guard));
            fprintf(stderr, "handler=%u ", TREE_ID(TRY_STMT(t).handler));
            fprintf(stderr, "begin_addr=%u end_addr=%u label=%d jmp_target=%d\n",
                TREE_ID(TRY_STMT(t).begin_addr),
                TREE_ID(TRY_STMT(t).end_addr),
                TRY_STMT(t).label, TRY_STMT(t).jmp_target);
            break;
        case Dowhile_stmt:
            fprintf(stderr, "stmt=%u ", TREE_ID(DOWHILE_STMT(t).stmt));
            fprintf(stderr, "expr=%u ", TREE_ID(DOWHILE_STMT(t).expr));
            fprintf(stderr, "breaklab=%d contlab=%d\n", DOWHILE_STMT(t).breaklab, DOWHILE_STMT(t).contlab);
            break;
        case For_stmt:
            fprintf(stderr, "expr1=%u ", TREE_ID(FOR_STMT(t).expr1));
            fprintf(stderr, "expr2=%u ", TREE_ID(FOR_STMT(t).expr2));
            fprintf(stderr, "expr3=%u ", TREE_ID(FOR_STMT(t).expr3));
            fprintf(stderr, "stmt=%u ", TREE_ID(FOR_STMT(t).stmt));
            fprintf(stderr, "breaklab=%d contlab=%d\n", FOR_STMT(t).breaklab, FOR_STMT(t).contlab);
            break;
        case Goto_stmt:
            fprintf(stderr, "id=%s\n", GET_IDENTIFIER(GOTO_STMT(t).id).id->name);
            break;
        case Break_stmt:
        case Continue_stmt:
        case Leave_stmt:
            fprintf(stderr, "\n");
            break;
        case Return_stmt:
            fprintf(stderr, "expr=%u\n", TREE_ID(RETURN_STMT(t).expr));
            break;
        case Addr_expr:
        case Alignof_expr:
        case Bitcomplement_expr:
        case Classof_expr:
        case Indirect_expr:
        case Not_expr:
        case Postdecrement_expr:
        case Postincrement_expr:
        case Predecrement_expr:
        case Preincrement_expr:
        case Sizeof_expr:
        case Uminus_expr:
        case Uplus_expr:
        case Delete_expr:
        case Array_ref:
            fprintf(stderr, "operand[0]=%u\n", TREE_ID(UNARY_EXPR(t).operand[0]));
            break;
        case Addrrel_expr:
        case And_expr:
        case Assign_expr:
        case Bitand_expr:
        case Bitor_expr:
        case Bitxor_expr:
        case Bitand_assign_expr:
        case Bitor_assign_expr:
        case Bitxor_assign_expr:
        case Call_expr:
        case Cast_expr:
        case Comma_expr:
        case Div_expr:
        case Div_assign_expr:
        case Eq_expr:
        case Gt_expr:
        case Geq_expr:
        case Index_expr:
        case Leq_expr:
        case Lshift_expr:
        case Lshift_assign_expr:
        case Lt_expr:
        case Minus_expr:
        case Minus_assign_expr:
        case Rem_expr:
        case Rem_assign_expr:
        case Mult_expr:
        case Mult_assign_expr:
        case Neq_expr:
        case Or_expr:
        case Plus_expr:
        case Plus_assign_expr:
        case Rshift_expr:
        case Rshift_assign_expr:
        case New_expr:
        case Member_init_expr:
        case Component_ref:
        case Indirect_component_ref:
        case Qualified_ref:
            fprintf(stderr, "operand[0]=%u ", TREE_ID(BINARY_EXPR(t).operand[0]));
            fprintf(stderr, "operand[1]=%u\n", TREE_ID(BINARY_EXPR(t).operand[1]));
            break;
        case Conditional_expr:
            fprintf(stderr, "operand[0]=%u ", TREE_ID(TERNARY_EXPR(t).operand[0]));
            fprintf(stderr, "operand[1]=%u ", TREE_ID(TERNARY_EXPR(t).operand[1]));
            fprintf(stderr, "operand[2]=%u\n", TREE_ID(TERNARY_EXPR(t).operand[2]));
            break;
        case Aggregate_expr:
            for (j = 0; AGGREGATE_EXPR(t).operand[j] != NULL; j++) {
                fprintf(stderr, "operand[%d]=%u ", j, TREE_ID(AGGREGATE_EXPR(t).operand[j]));
            }
            fprintf(stderr, "\n");
            break;
        case Constant:
            switch (TREE_CODE(TREE_TYPE(t))) {
                
                case Char_type:
                case Int_type:
                case Long_type:
                case Longlong_type:
                case Short_type:
                case Signed_type:
                    fprintf(stderr, "i64=(%d,%u)\n", *(long*)&ICONSTANT(t).value, (unsigned long)ICONSTANT(t).value);
                    break;
                case Unsigned_type:
                case Uchar_type:
                case Uint_type:
                case Ulong_type:
                case Ulonglong_type:
                case Ushort_type:
                case Pointer_type:
                    fprintf(stderr, "ui64=(%u,%u)\n", *(unsigned long*)&UICONSTANT(t).value, (unsigned long)UICONSTANT(t).value);
                    break;
                case Double_type:
                case Longdouble_type:
                case Float_type:
                    if (!(TREE_ATTRIBUTE(t) & VAL_ATTRIBUTE)) {
                        fprintf(stderr, "real=%s\n", REALCONSTANT(t).value->name);
                        if (REALCONSTANT(t).value->constVal != NULL) {
                            display_node(REALCONSTANT(t).value->constVal);
                        }
                    } else if (TREE_CODE(TREE_TYPE(t)) == Float_type) {
                        fprintf(stderr, "fp=%g\n", FLTCONSTANT(t).value);
                    } else {
                        fprintf(stderr, "fp=%g\n", DBLCONSTANT(t).value);
                    }
                    break;
                case Array_type:
                    if (TREE_CODE(t) == Constant &&
                        TREE_CODE(TREE_TYPE(t)) == Array_type &&
                        (TREE_CODE(TREE_TYPE(TREE_TYPE(t))) == Uchar_type || TREE_CODE(TREE_TYPE(TREE_TYPE(t))) == Char_type)) {
                        fprintf(stderr, "s=%s\n", STRINGCONSTANT(t).value);
                    } else {
                        for (k = 0, l = 3; k < ICONSTANT(ARRAY_TYPE(TREE_TYPE(t)).index_type).value && k != 80; k++, l++) {
                            if (l == 7) {
                                fprintf(stderr, "\n");
                                l = 0;
                            }
                            fprintf(stderr, "w[%d]=%ld (%c) ", k, WSTRINGCONSTANT(t).value[k], WSTRINGCONSTANT(t).value[k]);
                        }
                        fprintf(stderr, "\n");
                    }
                    display_node(ARRAY_TYPE(TREE_TYPE(t)).index_type);
                    break;
            }
            display_node(TREE_TYPE(t));
            break;
        case Identifier:
            fprintf(stderr, "id=%s\n", GET_IDENTIFIER(t).id->name);
            break;
        case End_of_file:
        case Nop:
        case Error_mark:
        case Reserved:
            fprintf(stderr, "\n");
            break;
        case Pragma:
            fprintf(stderr, "pragma_type = %d, argument=%u\n", GET_PRAGMA(t).pragma_type, TREE_ID(GET_PRAGMA(t).argument));
            break;
        case Access_spec:
            fprintf(stderr, "access=%u\n", TREE_ID(ACCESS_SPEC(t).access));
            break;
        default:
            __assert("FALSE", "tree.c", 702);
            break;
    }
}


void preorder_walk(TreeNode* t, void (*disp)(TreeNode*)) {
    TreeNode* child;
    TreeNode** ptr;
    int j;
    // use get_visited / set_visited ?
    if (t == NULL || is_visited[t->id]) {
        return;
    }

    is_visited[t->id] = TRUE;
    current_depth++;

    switch (TREE_CODE(t)) {
        case Double_type:
        case Longdouble_type:
        case Float_type:
        case Label_type:
        case Char_type:
        case Int_type:
        case Long_type:
        case Longlong_type:
        case Short_type:
        case Signed_type:
        case Unsigned_type:
        case Uchar_type:
        case Uint_type:
        case Ulong_type:
        case Ulonglong_type:
        case Ushort_type:
        case Void_type:
        case Any_type:
            disp(t);
            break;
        case Array_type:
            disp(t);
            preorder_walk(ARRAY_TYPE(t).index_type, disp);
            break;
        case Struct_type:
            disp(t);
            preorder_walk(STRUCT_TYPE(t).sname, disp);
            for (child = STRUCT_TYPE(t).members; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = STRUCT_TYPE(t).baselist; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            break;
        case Enum_type:
            disp(t);
            preorder_walk(ENUM_TYPE(t).ename, disp);
            for (child = ENUM_TYPE(t).literals; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            break;
        case Func_type:
            disp(t);
            preorder_walk(FUNC_TYPE(t).fname, disp);
            for (child = FUNC_TYPE(t).params; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = FUNC_TYPE(t).decls; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = FUNC_TYPE(t).handlers; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            break;
        case Pointer_type:
            disp(t);
            preorder_walk(POINTER_TYPE(t).base_type, disp);
            break;
        case Reference_type:
            disp(t);
            preorder_walk(POINTER_TYPE(t).base_type, disp);
            break;
        case Field_decl:
            disp(t);
            for (child = FIELD_DECL(t).field; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            break;
        case Id_decl:
            disp(t);
            for (child = TREE_TYPE(t); child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            for (child = ID_DECL(t).init_value; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = ID_DECL(t).qualifiers; child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            preorder_walk(ID_DECL(t).context, disp);
            break;
        case Declare_decl:
            disp(t);
            for (child = TREE_TYPE(t); child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            for (child = DECLARE_DECL(t).ids; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = TREE_LINK(t), current_depth--; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            current_depth++;
            break;
        case If_stmt:
            disp(t);
            preorder_walk(IF_STMT(t).expr, disp);
            preorder_walk(IF_STMT(t).else_part, disp);
            preorder_walk(IF_STMT(t).then_part, disp);
            break;
        case Init:
            disp(t);
            preorder_walk(INIT(t).value, disp);
            break;
        case Caselabeled_stmt:
            disp(t);
            preorder_walk(LABELED_STMT(t).expr, disp);
            preorder_walk(LABELED_STMT(t).stmt, disp);
            break;
        case Defaultlabeled_stmt:
            disp(t);
            break;
        case Idlabeled_stmt:
            disp(t);
            preorder_walk(LABELED_STMT(t).id, disp);
            preorder_walk(LABELED_STMT(t).stmt, disp);
            break;
        case Compound_stmt:
            disp(t);
            for (child = COMPOUND_STMT(t).decls; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = COMPOUND_STMT(t).stmts; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            break;
        case Expr_stmt:
            disp(t);
            preorder_walk(EXPR_STMT(t).expr, disp);
            break;
        case Switch_stmt:
            disp(t);
            preorder_walk(SWITCH_STMT(t).expr, disp);
            preorder_walk(SWITCH_STMT(t).stmt, disp);
            break;
        case While_stmt:
            disp(t);
            preorder_walk(WHILE_STMT(t).expr, disp);
            preorder_walk(WHILE_STMT(t).stmt, disp);
            break;
        case Try_stmt:
            disp(t);
            preorder_walk(TRY_STMT(t).expr, disp);
            preorder_walk(TRY_STMT(t).guard, disp);
            preorder_walk(TRY_STMT(t).handler, disp);
            break;
        case Dowhile_stmt:
            disp(t);
            preorder_walk(DOWHILE_STMT(t).stmt, disp);
            preorder_walk(DOWHILE_STMT(t).expr, disp);
            break;
        case For_stmt:
            disp(t);
            preorder_walk(FOR_STMT(t).expr1, disp);
            preorder_walk(FOR_STMT(t).expr2, disp);
            preorder_walk(FOR_STMT(t).expr3, disp);
            preorder_walk(FOR_STMT(t).stmt, disp);
            break;
        case Goto_stmt:
            disp(t);
            preorder_walk(GOTO_STMT(t).id, disp);
            break;
        case Break_stmt:
        case Continue_stmt:
        case Leave_stmt:
            disp(t);
            break;
        case Return_stmt:
            disp(t);
            preorder_walk(RETURN_STMT(t).expr, disp);
            break;
        case Addr_expr:
        case Alignof_expr:
        case Bitcomplement_expr:
        case Classof_expr:
        case Indirect_expr:
        case Not_expr:
        case Postdecrement_expr:
        case Postincrement_expr:
        case Predecrement_expr:
        case Preincrement_expr:
        case Sizeof_expr:
        case Uminus_expr:
        case Uplus_expr:
        case Delete_expr:
        case Array_ref:
            disp(t);
            for (child = TREE_TYPE(t); child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            preorder_walk(UNARY_EXPR(t).operand[0], disp);
            break;
        case Cast_expr:
            disp(t);
            for (child = TREE_TYPE(t); child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            preorder_walk(BINARY_EXPR(t).operand[0], disp);
            for (child = TREE_TYPE(BINARY_EXPR(t).operand[0]); child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            preorder_walk(BINARY_EXPR(t).operand[1], disp);
            break;
        case Addrrel_expr:
        case And_expr:
        case Assign_expr:
        case Bitand_expr:
        case Bitor_expr:
        case Bitxor_expr:
        case Bitand_assign_expr:
        case Bitor_assign_expr:
        case Bitxor_assign_expr:
        case Call_expr:
        case Comma_expr:
        case Div_expr:
        case Div_assign_expr:
        case Eq_expr:
        case Gt_expr:
        case Geq_expr:
        case Index_expr:
        case Leq_expr:
        case Lshift_expr:
        case Lshift_assign_expr:
        case Lt_expr:
        case Minus_expr:
        case Minus_assign_expr:
        case Rem_expr:
        case Rem_assign_expr:
        case Mult_expr:
        case Mult_assign_expr:
        case Neq_expr:
        case Or_expr:
        case Plus_expr:
        case Plus_assign_expr:
        case Rshift_expr:
        case Rshift_assign_expr:
        case New_expr:
        case Member_init_expr:
            disp(t);
            for (child = TREE_TYPE(t); child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            preorder_walk(BINARY_EXPR(t).operand[0], disp);
            preorder_walk(BINARY_EXPR(t).operand[1], disp);
            break;
        case Component_ref:
        case Indirect_component_ref:
        case Qualified_ref:
            disp(t);
            for (child = TREE_TYPE(t); child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            if (TREE_CODE(t) != Qualified_ref && TREE_CODE(BINARY_EXPR(t).operand[1]) == Constant) {
                fprintf(stderr, "\t>value of offset is %d\n", ICONSTANT(BINARY_EXPR(t).operand[1]).value);
            }
            preorder_walk(BINARY_EXPR(t).operand[0], disp);
            preorder_walk(BINARY_EXPR(t).operand[1], disp);
            break;
        case Conditional_expr:
            disp(t);
            for (child = TREE_TYPE(t); child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            preorder_walk(TERNARY_EXPR(t).operand[0], disp);
            preorder_walk(TERNARY_EXPR(t).operand[1], disp);
            preorder_walk(TERNARY_EXPR(t).operand[2], disp);
            break;
        case Aggregate_expr:
            disp(t);
            for (j = 0; AGGREGATE_EXPR(t).operand[j] != NULL; j++) {
                preorder_walk(AGGREGATE_EXPR(t).operand[j], disp);
            }
            break;
        case Identifier:
        case Constant:
        case End_of_file:
        case Nop:
        case Constant_special:
        case Error_mark:
        case Reserved:
            disp(t);
            break;
        case Pragma:
            disp(t);
            for (child = GET_PRAGMA(t).argument; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = TREE_LINK(t), current_depth--; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            current_depth++;
            break;
        case Access_spec:
            disp(t);
            for (child = ACCESS_SPEC(t).access; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = TREE_LINK(t), current_depth--; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            current_depth++;
            break;
        default:
            __assert("FALSE", "tree.c", 1010);
            break;
    }
    current_depth--;
}

void walk(TreeNode* t, char walk_mode, void (*disp)(TreeNode*)) {
    is_visited = mem_alloc(tree_handle, 4 * last_node_id + 4, 4);

    switch (walk_mode) {
        case 't':
            preorder_walk(t, disp);
            break;
        case 'b':
            __assert("FALSE", "tree.c", 1029);
            break;
        case 'i':
            __assert("FALSE", "tree.c", 1032);
            break;
        default:
            __assert("FALSE", "tree.c", 1035);
            break;
    }
}

void display_tree(TreeNode* t) {
    current_depth = -1;
    walk(t, 't', display_node);
}

static TreeNode* debug_child(TreeNode* t, char* c) {
    switch (TREE_CODE(t)) {
        case Array_type:
            return ARRAY_TYPE(t).index_type;
        case Struct_type:
            switch (*c) {
                case 'm':
                    return STRUCT_TYPE(t).members;
                case 's':
                    return STRUCT_TYPE(t).sname;
                case 'b':
                    return STRUCT_TYPE(t).baselist;
            }
            break;
        case Enum_type:
            switch (*c) {
                case 'l':
                    return ENUM_TYPE(t).literals;
                case 'e':
                    return ENUM_TYPE(t).ename;                
            }
            break;
        case Pointer_type:
            return POINTER_TYPE(t).base_type;
        case Reference_type:
            return POINTER_TYPE(t).base_type;
        case Func_type:
            switch (*c) {
                case 'p':
                    return FUNC_TYPE(t).params;
                case 'd':
                    return FUNC_TYPE(t).decls;
                case 'f':
                    return FUNC_TYPE(t).fname;               
                
                case 'h':
                    return FUNC_TYPE(t).handlers;
            }
            break;
        case Field_decl:
            switch (*c) {
                case 'f':
                    return FIELD_DECL(t).field;
            }
            break;
        case Id_decl:
            switch (*c) {
                case 'i':
                    return ID_DECL(t).init_value;
                case 'q':
                    return ID_DECL(t).qualifiers;
                case 'h':
                    return ID_DECL(t).hidden;
                case 's':
                    return ID_DECL(t).st_list;
                case 'c':
                    return ID_DECL(t).context;
                case 'o':
                    return ID_DECL(t).overloads;                
            }
            break;
        case Declare_decl:
            return DECLARE_DECL(t).ids;
        case If_stmt:
            switch (*c) {
                case 'e':
                    c++;
                    if (*c == 'x') {
                        return IF_STMT(t).expr;
                    } else {
                        return IF_STMT(t).else_part;
                    }
                case 't':
                    return IF_STMT(t).then_part;              
            }
            break;
        case Init:
            return INIT(t).value;
        case Caselabeled_stmt:
            switch (*c) {
                case 'e':
                    return LABELED_STMT(t).expr;
                case 's':
                    return LABELED_STMT(t).stmt;           
            }
            break;
        case Defaultlabeled_stmt:
            return LABELED_STMT(t).stmt;
        case Idlabeled_stmt:
            switch (*c) {
                case 'i':
                    return LABELED_STMT(t).id;
                case 's':
                    return LABELED_STMT(t).stmt;           
            }
            break;
        case Compound_stmt:
            switch (*c) {
                case 'd':
                    return COMPOUND_STMT(t).decls; 
                case 's':
                    return COMPOUND_STMT(t).stmts;
                case 'c':
                    return COMPOUND_STMT(t).context;             
            }
            break;
        case Expr_stmt:
            return EXPR_STMT(t).expr;
        case Dowhile_stmt:
            switch (*c) {
                case 'e':
                    return DOWHILE_STMT(t).expr;
                case 's':
                    return DOWHILE_STMT(t).stmt;           
            }
            break;
        case While_stmt:
            switch (*c) {
                case 'e':
                    return WHILE_STMT(t).expr;
                case 's':
                    return WHILE_STMT(t).stmt;           
            }
            break;
        case Try_stmt:
            switch (*c) {
                case 'e':
                    if (c[1] == 'x') {
                        return TRY_STMT(t).expr;    
                    } else {
                        return TRY_STMT(t).end_addr;
                    }
                case 'g':
                    return TRY_STMT(t).guard;
                case 'h':
                    return TRY_STMT(t).handler;
                case 'b':
                    return TRY_STMT(t).begin_addr;
                    
            }
            break;
        case Switch_stmt:
            switch (*c) {
                case 'e':
                    return SWITCH_STMT(t).expr;
                case 's':
                    return SWITCH_STMT(t).stmt;           
            }
            break;
        case For_stmt:
            switch (*c) {
                case '1':
                    return FOR_STMT(t).expr1;
                case '2':
                    return FOR_STMT(t).expr2;
                case '3':
                    return FOR_STMT(t).expr3;
                case 's':
                    return FOR_STMT(t).stmt;    
            }
            break;
        case Goto_stmt:
            return GOTO_STMT(t).id;
        case Return_stmt:
            return RETURN_STMT(t).expr;
        case Addr_expr:
        case Alignof_expr:
        case Bitcomplement_expr:
        case Classof_expr:
        case Indirect_expr:
        case Not_expr:
        case Postdecrement_expr:
        case Postincrement_expr:
        case Predecrement_expr:
        case Preincrement_expr:
        case Sizeof_expr:
        case Uminus_expr:
        case Uplus_expr:
        case Delete_expr:
        case Addrrel_expr:
        case And_expr:
        case Assign_expr:
        case Bitand_expr:
        case Bitor_expr:
        case Bitxor_expr:
        case Bitand_assign_expr:
        case Bitor_assign_expr:
        case Bitxor_assign_expr:
        case Call_expr:
        case Cast_expr:
        case Comma_expr:
        case Div_expr:
        case Div_assign_expr:
        case Eq_expr:
        case Gt_expr:
        case Geq_expr:
        case Index_expr:
        case Leq_expr:
        case Lshift_expr:
        case Lshift_assign_expr:
        case Lt_expr:
        case Minus_expr:
        case Minus_assign_expr:
        case Rem_expr:
        case Rem_assign_expr:
        case Mult_expr:
        case Mult_assign_expr:
        case Neq_expr:
        case Or_expr:
        case Plus_expr:
        case Plus_assign_expr:
        case Rshift_expr:
        case Rshift_assign_expr:
        case New_expr:
        case Member_init_expr:
        case Conditional_expr:
        case Aggregate_expr:
        case Array_ref:
        case Component_ref:
        case Indirect_component_ref:
        case Qualified_ref:
            return BINARY_EXPR(t).operand[atoi(c)];
        case Pragma:
            return GET_PRAGMA(t).argument;
        case Access_spec:
            return ACCESS_SPEC(t).access;
    }

    return t;
}

void debugger(TreeNode* arg) {
    char buffer[0x1000];
    TreeNode* siblingStack[0x1000];
    int siblingIndex = 1;
    TreeNode* childStack[0x1000];    
    int childIndex = 1;
    TreeNode* t;

    t = arg;
    childStack[0] = siblingStack[0] = NULL;
    
    while (TRUE) {
        fprintf(stderr, "(tdb)");
        fflush(stderr);
        if (gets(buffer) == NULL) {
            break;
        }

        switch (buffer[0]) {
            case 'b':
                if (siblingIndex > 1) {
                    t = siblingStack[--siblingIndex];
                }
                break;
            case 'c':
                childStack[childIndex++] = t;
                t = debug_child(t, buffer + 2);
                break;
            case 'd':
                display_node(t);
                break;
            case 'f':
                siblingStack[siblingIndex++] = t;
                t = TREE_LINK(t);
                break;
            case 'q':
                return;
            case 't':
                childStack[childIndex++] = t;
                t = TREE_TYPE(t);
                break;
            case 'u':
                if (childIndex > 1) {
                    t = childStack[--childIndex];
                }
                break;
            case '?':
                fprintf(stderr, "tdb comand      description\n");
                fprintf(stderr, "----------      ------------\n");
                fprintf(stderr, "   b            backward to last sibling\n");
                fprintf(stderr, "   c <tree>     change to subtree with name <tree>.\n");
                fprintf(stderr, "                Use 0,1...,n-1 for <tree> for expression trees\n");
                fprintf(stderr, "   d            display current node\n");
                fprintf(stderr, "   f            forward to next sibling\n");
                fprintf(stderr, "   q            quit debugger\n");
                fprintf(stderr, "   t            change to current node's type\n");
                fprintf(stderr, "   u            up to parent\n");
                fprintf(stderr, "   ?            debugger command help\n");
                break;
            default:
                fprintf(stderr, "type ? for help\n");
                break;
        }
    }
}

TreeNode* duplicate_node(TreeNode* t) {
    TreeNode* copy;

    if (t == NULL) {
        return NULL;
    }

    switch (TREE_CODE(t)) {
        case Error_mark:
            copy = make(Error_mark, TREE_LOCATION(t));
            break;
        case Id_decl:
            copy = make(Id_decl, TREE_LOCATION(t), ID_DECL(t).id);
            ID_DECL(copy).init_value = ID_DECL(t).init_value;
            ID_DECL(copy).qualifiers = ID_DECL(t).qualifiers;
            ID_DECL(copy).offset = ID_DECL(t).offset;
            ID_DECL(copy).level = ID_DECL(t).level;
            ID_DECL(copy).alevel = ID_DECL(t).alevel;
            ID_DECL(copy).sclass = ID_DECL(t).sclass;
            ID_DECL(copy).hidden = ID_DECL(t).hidden;
            ID_DECL(copy).st_list = ID_DECL(t).st_list;
            ID_DECL(copy).context = ID_DECL(t).context;
            ID_DECL(copy).blkno = ID_DECL(t).blkno;
            ID_DECL(copy).flags = ID_DECL(t).flags;
            ID_DECL(copy).overloads = ID_DECL(t).overloads;
            ID_DECL(copy).oclass = ID_DECL(t).oclass;
            ID_DECL(copy).lastused = ID_DECL(t).lastused;
            break;
        case Func_type:
            copy = make(Func_type, TREE_LOCATION(t), FUNC_TYPE(t).params);
            FUNC_TYPE(copy).fname = FUNC_TYPE(t).fname;
            FUNC_TYPE(copy).decls = FUNC_TYPE(t).decls;
            FUNC_TYPE(copy).psize = FUNC_TYPE(t).psize;
            FUNC_TYPE(copy).end_blkno = FUNC_TYPE(t).end_blkno;
            FUNC_TYPE(copy).handlers = FUNC_TYPE(t).handlers;
            break;
        case Struct_type:
            copy = make(Struct_type, TREE_LOCATION(t), NULL);
            STRUCT_TYPE(copy).sname = STRUCT_TYPE(t).sname;
            STRUCT_TYPE(copy).info = STRUCT_TYPE(t).info;
            STRUCT_TYPE(copy).members = STRUCT_TYPE(t).members;
            STRUCT_TYPE(copy).baselist = STRUCT_TYPE(t).baselist;
            STRUCT_TYPE(copy).size = STRUCT_TYPE(t).size;
            STRUCT_TYPE(copy).align = STRUCT_TYPE(t).align;
            break;
        case Enum_type:
            copy = make(Enum_type, TREE_LOCATION(t));
            ENUM_TYPE(copy).ename = ENUM_TYPE(t).ename;
            ENUM_TYPE(copy).literals = ENUM_TYPE(t).literals;
            ENUM_TYPE(copy).lb = ENUM_TYPE(t).lb;
            ENUM_TYPE(copy).ub = ENUM_TYPE(t).ub;
            ENUM_TYPE(copy).size = ENUM_TYPE(t).size;
            ENUM_TYPE(copy).align = ENUM_TYPE(t).align;
            break;
        case Array_type:
            copy = make(Array_type, TREE_LOCATION(t));
            TREE_TYPE(copy) = TREE_TYPE(t);
            ARRAY_TYPE(copy).index_type = ARRAY_TYPE(t).index_type;
            ARRAY_TYPE(copy).size = ARRAY_TYPE(t).size;
            ARRAY_TYPE(copy).align = ARRAY_TYPE(t).align;
            break;
        case Double_type:
        case Longdouble_type:
        case Float_type:
        case Label_type:
        case Char_type:
        case Int_type:
        case Long_type:
        case Longlong_type:
        case Short_type:
        case Signed_type:
        case Unsigned_type:
        case Uchar_type:
        case Uint_type:
        case Ulong_type:
        case Ulonglong_type:
        case Ushort_type:
        case Void_type:
        case Any_type:
            copy = make(TREE_CODE(t), TREE_LOCATION(t), BASIC_TYPE(t).size, BASIC_TYPE(t).align);
            BASIC_TYPE(copy).size = BASIC_TYPE(t).size;
            BASIC_TYPE(copy).align = BASIC_TYPE(t).align;
            break;
        case Pointer_type:
            copy = make(Pointer_type, TREE_LOCATION(t));
            POINTER_TYPE(copy).size = POINTER_TYPE(t).size;
            POINTER_TYPE(copy).align = POINTER_TYPE(t).align;
            POINTER_TYPE(copy).base_type = POINTER_TYPE(t).base_type;
            break;
        case Reference_type:
            copy = make(Reference_type, TREE_LOCATION(t));
            POINTER_TYPE(copy).size = POINTER_TYPE(t).size;
            POINTER_TYPE(copy).align = POINTER_TYPE(t).align;
            POINTER_TYPE(copy).base_type = POINTER_TYPE(t).base_type;
            break;
        case Constant:
            switch (TREE_CODE(TREE_TYPE(t))) {
                case Char_type:
                case Int_type:
                case Long_type:
                case Longlong_type:
                case Short_type:
                case Signed_type:
                    copy = make_iconstant(TREE_LOCATION(t), TREE_TYPE(t), ICONSTANT(t).value);
                    break;
                case Unsigned_type:
                case Uchar_type:
                case Uint_type:
                case Ulong_type:
                case Ulonglong_type:
                case Ushort_type:
                case Pointer_type:
                    // why not make_uiconstant ??
                    copy = make_iconstant(TREE_LOCATION(t), TREE_TYPE(t), UICONSTANT(t).value);
                    break;
                default:
                    __assert("FALSE", "tree.c", 0x5BB);
            }
            break;
        case Addr_expr:
        case Alignof_expr:
        case Bitcomplement_expr:
        case Classof_expr:
        case Indirect_expr:
        case Not_expr:
        case Postdecrement_expr:
        case Postincrement_expr:
        case Predecrement_expr:
        case Preincrement_expr:
        case Sizeof_expr:
        case Uminus_expr:
        case Uplus_expr:
        case Delete_expr:
        case Array_ref:
            copy = make(TREE_CODE(t), TREE_LOCATION(t), UNARY_EXPR(t).operand[0]);
            break;
        case Addrrel_expr:
        case And_expr:
        case Assign_expr:
        case Bitand_expr:
        case Bitor_expr:
        case Bitxor_expr:
        case Bitand_assign_expr:
        case Bitor_assign_expr:
        case Bitxor_assign_expr:
        case Call_expr:
        case Cast_expr:
        case Comma_expr:
        case Div_expr:
        case Div_assign_expr:
        case Eq_expr:
        case Gt_expr:
        case Geq_expr:
        case Index_expr:
        case Leq_expr:
        case Lshift_expr:
        case Lshift_assign_expr:
        case Lt_expr:
        case Minus_expr:
        case Minus_assign_expr:
        case Rem_expr:
        case Rem_assign_expr:
        case Mult_expr:
        case Mult_assign_expr:
        case Neq_expr:
        case Or_expr:
        case Plus_expr:
        case Plus_assign_expr:
        case Rshift_expr:
        case Rshift_assign_expr:
        case New_expr:
        case Member_init_expr:
        case Component_ref:
        case Indirect_component_ref:
        case Qualified_ref:
            copy = make(TREE_CODE(t), TREE_LOCATION(t), BINARY_EXPR(t).operand[0], BINARY_EXPR(t).operand[1]);
            break;
        case Conditional_expr:
            copy = make(TREE_CODE(t), TREE_LOCATION(t), TERNARY_EXPR(t).operand[0], TERNARY_EXPR(t).operand[1], TERNARY_EXPR(t).operand[2]);
            break;
        default:
            __assert("FALSE", "tree.c", 1532);
            break;
    }

    TREE_ATTRIBUTE(copy) = TREE_ATTRIBUTE(t);
    TREE_TYPE(copy) = TREE_TYPE(t);
    TREE_LINK(copy) = TREE_LINK(t);
    return copy;
}

TreeNode* unqual_type(TreeNode* t) {
    TreeNode* nonStdType;
    int isPlain;

    if ((TREE_ATTRIBUTE(t) & PLAIN_ATTRIBUTE) && !(IS_STD_TREE(t))) {
        isPlain = TRUE;
    } else {
        isPlain = FALSE;
    }

    if (TREE_ATTRIBUTE(t) & (VOLATILE_ATTRIBUTE | CONST_ATTRIBUTE | TYPEDEF_ATTRIBUTE | UNALIGNED_ATTRIBUTE)) {
        if (TREE_CODE(t) == Struct_type || TREE_CODE(t) == Enum_type) {
            t = TREE_TYPE(t);
        } else if (TREE_CODE(t) == Array_type || TREE_CODE(t) == Pointer_type || TREE_CODE(t) == Func_type) {
            t = duplicate_node(t);
            TREE_ATTRIBUTE(t) = 0;
        } else {
            switch (TREE_CODE(t)) {
                case Void_type:
                    t = void_type;
                    break;
                case Char_type:
                    t = char_type;
                    break;
                case Uchar_type:
                    t = uchar_type;
                    break;
                case Short_type:
                    t = short_type;
                    break;
                case Ushort_type:
                    t = ushort_type;
                    break;
                case Int_type:
                    t = int_type;
                    break;
                case Long_type:
                    t = long_type;
                    break;
                case Longlong_type:
                    t = longlong_type;
                    break;
                case Signed_type:
                    t = signed_type;
                    break;
                case Unsigned_type:
                    t = unsigned_type;
                    break;
                case Uint_type:
                    t = uint_type;
                    break;
                case Ulong_type:
                    t = ulong_type;
                    break;
                case Ulonglong_type:
                    t = ulonglong_type;
                    break;
                case Float_type:
                    t = float_type;
                    break;
                case Longdouble_type:
                    t = longdouble_type;
                    break;
                case Double_type:
                    t = double_type;
                    break;
            }
        }
    }
    
    if (isPlain) {
        TreeNode* type;
        
        for (type = t, nonStdType = t; type != NULL; type = TREE_TYPE(type)) {
            if (IS_STD_TREE(type)) {
                break;
            }
            nonStdType = type;
        }
        TREE_ATTRIBUTE(nonStdType) |= PLAIN_ATTRIBUTE;
    }

    return t;
}

TreeNode* make(int code, int location, ...) {
    va_list args;
    TreeNode* type;
    char* str;
    int* wide_str;
    TreeNode* t;
    int string_len;
    TreeNode* arg;
    int wide_string_size;
    TreeNode* aggr_operand;
    int i;

    va_start(args, location);
    
    switch (code) {
        case Double_type:
        case Longdouble_type:
        case Float_type:
        case Label_type:
        case Char_type:
        case Int_type:
        case Long_type:
        case Longlong_type:
        case Short_type:
        case Signed_type:
        case Unsigned_type:
        case Uchar_type:
        case Uint_type:
        case Ulong_type:
        case Ulonglong_type:
        case Ushort_type:
        case Void_type:
        case Any_type:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Basic_type), 4);
            BASIC_TYPE(t).size = va_arg(args, int);
            BASIC_TYPE(t).align = va_arg(args, int);
            break;
        case Array_type:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Array_type), 4);
            ARRAY_TYPE(t).index_type = va_arg(args, TreeNode*);
            break;
        case Struct_type:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Struct_type), 4);
            STRUCT_TYPE(t).info = va_arg(args, int);
            break;
        case Enum_type:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Enum_type), 4);
            break;
        case Func_type:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Func_type), 4);
            FUNC_TYPE(t).params = va_arg(args, TreeNode*);
            break;
        case Pointer_type:
        case Reference_type:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Pointer_type), 4);
            break;
        case Field_decl:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Field_decl), 4);
            break;
        case Id_decl:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Id_decl), 4);
            ID_DECL(t).id = va_arg(args, Symbol*);
            break;
        case Declare_decl:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Declare_decl), 4);
            TREE_TYPE(t) = va_arg(args, TreeNode*);
            DECLARE_DECL(t).ids = va_arg(args, TreeNode*);
            break;
        case If_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_If_stmt), 4);
            IF_STMT(t).expr = va_arg(args, TreeNode*);
            IF_STMT(t).then_part = va_arg(args, TreeNode*);
            IF_STMT(t).else_part = va_arg(args, TreeNode*);
            break;
        case Init:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Init), 4);
            INIT(t).value = va_arg(args, TreeNode*);
            INIT(t).replicate = va_arg(args, int);
            INIT(t).start_offset = va_arg(args, int);
            break;
        case Pragma:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Pragma), 4);
            GET_PRAGMA(t).pragma_type = va_arg(args, int);
            GET_PRAGMA(t).argument = va_arg(args, TreeNode*);
            break;
        case Access_spec:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Access_spec), 4);
            ACCESS_SPEC(t).access = va_arg(args, TreeNode*);
            break;
        case Caselabeled_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Labeled_stmt), 4);
            LABELED_STMT(t).expr = va_arg(args, TreeNode*);
            LABELED_STMT(t).stmt = va_arg(args, TreeNode*);
            break;
        case Defaultlabeled_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Labeled_stmt), 4);
            LABELED_STMT(t).stmt = va_arg(args, TreeNode*);
            break;
        case Idlabeled_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Labeled_stmt), 4);
            LABELED_STMT(t).id = va_arg(args, TreeNode*);
            LABELED_STMT(t).stmt = va_arg(args, TreeNode*);
            break;
        case Compound_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Compound_stmt), 4);
            COMPOUND_STMT(t).decls = va_arg(args, TreeNode*);
            COMPOUND_STMT(t).stmts = va_arg(args, TreeNode*);
            COMPOUND_STMT(t).end_location = va_arg(args, int);
            break;
        case Expr_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Expr_stmt), 4);
            EXPR_STMT(t).expr = va_arg(args, TreeNode*);
            break;
        case Switch_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Switch_stmt), 4);
            SWITCH_STMT(t).expr = va_arg(args, TreeNode*);
            SWITCH_STMT(t).stmt = va_arg(args, TreeNode*);
            break;
        case While_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_While_stmt), 4);
            WHILE_STMT(t).expr = va_arg(args, TreeNode*);
            WHILE_STMT(t).stmt = va_arg(args, TreeNode*);
            break;
        case Try_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Try_stmt), 4);
            TRY_STMT(t).expr = va_arg(args, TreeNode*);
            TRY_STMT(t).guard = va_arg(args, TreeNode*);
            TRY_STMT(t).handler = va_arg(args, TreeNode*);
            break;
        case Dowhile_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Dowhile_stmt), 4);
            DOWHILE_STMT(t).stmt = va_arg(args, TreeNode*);
            DOWHILE_STMT(t).expr = va_arg(args, TreeNode*);            
            break;
        case For_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_For_stmt), 4);
            FOR_STMT(t).expr1 = va_arg(args, TreeNode*);
            FOR_STMT(t).expr2 = va_arg(args, TreeNode*);
            FOR_STMT(t).expr3 = va_arg(args, TreeNode*);
            FOR_STMT(t).stmt = va_arg(args, TreeNode*);
            break;
        case Goto_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Goto_stmt), 4);
            GOTO_STMT(t).id = va_arg(args, TreeNode*);
            break;
        case Break_stmt:
        case Continue_stmt:
        case Leave_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode), 4);
            break;
        case Return_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Return_stmt), 4);
            RETURN_STMT(t).expr = va_arg(args, TreeNode*);
            break;
        case Addr_expr:
        case Alignof_expr:
        case Bitcomplement_expr:
        case Classof_expr:
        case Indirect_expr:
        case Not_expr:
        case Postdecrement_expr:
        case Postincrement_expr:
        case Predecrement_expr:
        case Preincrement_expr:
        case Sizeof_expr:
        case Uminus_expr:
        case Uplus_expr:
        case Delete_expr:
        case Array_ref:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Unary_expr), 4);
            UNARY_EXPR(t).operand[0] = va_arg(args, TreeNode*);
            break;
        case Addrrel_expr:
        case And_expr:
        case Assign_expr:
        case Bitand_expr:
        case Bitor_expr:
        case Bitxor_expr:
        case Bitand_assign_expr:
        case Bitor_assign_expr:
        case Bitxor_assign_expr:
        case Call_expr:
        case Cast_expr:
        case Comma_expr:
        case Div_expr:
        case Div_assign_expr:
        case Eq_expr:
        case Gt_expr:
        case Geq_expr:
        case Index_expr:
        case Leq_expr:
        case Lshift_expr:
        case Lshift_assign_expr:
        case Lt_expr:
        case Minus_expr:
        case Minus_assign_expr:
        case Rem_expr:
        case Rem_assign_expr:
        case Mult_expr:
        case Mult_assign_expr:
        case Neq_expr:
        case Or_expr:
        case Plus_expr:
        case Plus_assign_expr:
        case Rshift_expr:
        case Rshift_assign_expr:
        case New_expr:
        case Member_init_expr:
        case Component_ref:
        case Indirect_component_ref:
        case Qualified_ref:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Binary_expr), 4);
            BINARY_EXPR(t).operand[0] = va_arg(args, TreeNode*);
            BINARY_EXPR(t).operand[1] = va_arg(args, TreeNode*);
            break;
        case Conditional_expr:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Ternary_expr), 4);
            TERNARY_EXPR(t).operand[0] = va_arg(args, TreeNode*);
            TERNARY_EXPR(t).operand[1] = va_arg(args, TreeNode*);
            TERNARY_EXPR(t).operand[2] = va_arg(args, TreeNode*);
            break;
        case Aggregate_expr:
            i = 0;
            t = arg = va_arg(args, TreeNode*);
            while (arg != NULL) {
                i++;
                arg = TREE_LINK(arg);
            }
            aggr_operand = t;
            t = mem_alloc(tree_handle, sizeof(TreeNode_Aggregate_expr) + 4 * i, 4);
            i = 0;
            while (TRUE) {
                arg = aggr_operand;
                aggr_operand = TREE_LINK(aggr_operand);
                AGGREGATE_EXPR(t).operand[i] = arg;
                TREE_LINK(arg) = NULL;
                i++;
                if (aggr_operand == NULL) {
                    AGGREGATE_EXPR(t).operand[i] = NULL;
                    break;
                }
            }
            
            break;
        case Constant:
            type = va_arg(args, TreeNode*);
            switch (TREE_CODE(type)) {
                case Char_type:
                case Int_type:
                case Long_type:
                case Longlong_type:
                case Short_type:
                case Signed_type:
                    if (!is_making_constant) {
                        __assert("FALSE", "tree.c", 1882);
                    }
                    is_making_constant = FALSE;

                    t = mem_alloc(tree_handle, sizeof(TreeNode_IConstant), 8);
                    ICONSTANT(t).value = va_arg(args, long long);
                    break;
                case Enum_type:
                    type = uint_type;
                    /* fallthrough */
                case Unsigned_type:
                case Uchar_type:
                case Uint_type:
                case Ulong_type:
                case Ulonglong_type:
                case Ushort_type:
                case Pointer_type:
                    if (!is_making_constant) {
                        __assert("FALSE", "tree.c", 1900);
                    }
                    is_making_constant = FALSE;

                    t = mem_alloc(tree_handle, sizeof(TreeNode_UIConstant), 8);
                    UICONSTANT(t).value = va_arg(args, unsigned long long);
                    break;
                case Double_type:
                case Longdouble_type:
                case Float_type:
                    t = mem_alloc(tree_handle, sizeof(TreeNode_RealConstant), 8);
                    REALCONSTANT(t).value = va_arg(args, Symbol*);
                    break;
                case Label_type:
                case Void_type:
                case Any_type:
                    __assert("FALSE", "tree.c", 1925);
                    break;
                case Array_type:
                    type = mem_alloc(tree_handle, sizeof(TreeNode_Array_type), 4);
                    str = va_arg(args, char*);
                    string_len = va_arg(args, int);
                    ARRAY_TYPE(type).size = bit_size[1] * string_len;
                    ARRAY_TYPE(type).align = bit_size[1];
                    t = mem_alloc(tree_handle, 0x18 + string_len * 1, 4); // sizeof(TreeNode_StringConstant) ?
                    TREE_CODE(type) = Array_type;
                    TREE_TYPE(type) = options[6] ? char_type : uchar_type;
                    type->id = ++last_node_id;
                    ARRAY_TYPE(type).index_type = make_iconstant(location, long_type, string_len);
                    memcpy(STRINGCONSTANT(t).value, str, string_len);
                    break;
                default:
                    __assert("FALSE", "tree.c", 1942);
                    break;
            }
            TREE_TYPE(t) = type;
            break;
        case Constant_special:
            type = va_arg(args, TreeNode*);
            switch (TREE_CODE(type)) {
                case Double_type:
                case Longdouble_type:
                    t = mem_alloc(tree_handle, sizeof(TreeNode_DblConstant), 8);
                    DBLCONSTANT(t).value = va_arg(args, double);
                    TREE_ATTRIBUTE(t) = VAL_ATTRIBUTE;
                    break;
                case Float_type:
                    t = mem_alloc(tree_handle, sizeof(TreeNode_FltConstant), 4);
                    FLTCONSTANT(t).value = va_arg(args, double);
                    TREE_ATTRIBUTE(t) = VAL_ATTRIBUTE;
                    break;
                case Array_type:
                    type = mem_alloc(tree_handle, sizeof(TreeNode_Array_type), 4);
                    wide_str = va_arg(args, int*);
                    string_len = va_arg(args, int);
                    wide_string_size = string_len * 4;
                    ARRAY_TYPE(type).size = bit_size[4] * string_len;
                    ARRAY_TYPE(type).align = bit_size[4];
                    t = mem_alloc(tree_handle, 0x18 + wide_string_size, 4); // sizeof(TreeNode_WStringConstant) ?
                    TREE_CODE(type) = Array_type;
                    TREE_TYPE(type) = long_type;
                    type->id = ++last_node_id;
                    ARRAY_TYPE(type).index_type = make_iconstant(location, long_type, string_len);
                    memcpy(WSTRINGCONSTANT(t).value, wide_str, wide_string_size);
                    break;
            }
            TREE_TYPE(t) = type;
            code = Constant;
            break;
        case Identifier:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Identifier), 4);
            GET_IDENTIFIER(t).id = va_arg(args, Symbol*);
            break;
        case End_of_file:
        case Nop:
        case Error_mark:
        case Reserved:
            t = mem_alloc(tree_handle, sizeof(TreeNode), 4);
            break;
        default:
            __assert("FALSE", "tree.c", 1991);
            break;
    }

    t->id = ++last_node_id;
    TREE_CODE(t) = code;
    TREE_LOCATION(t) = location;

    return t;
}

void init_trees(void) {
    tree_handle = general_handle;
}

void make_std_trees(void) {
    char_type = make(Char_type, -1, bit_size[1], bit_size[1]);
    double_type = make(Double_type, -1, bit_size[7], bit_size[7]);
    int_type = make(Int_type, -1, bit_size[3], bit_size[3]);
    float_type = make(Float_type, -1, bit_size[6], bit_size[6]);
    long_type = make(Long_type, -1, bit_size[4], bit_size[4]);
    longlong_type = make(Longlong_type, -1, bit_size[5], bit_size[5]);
    longdouble_type = make(Longdouble_type, -1, bit_size[8], bit_size[8]);
    short_type = make(Short_type, -1, bit_size[2], bit_size[2]);
    signed_type = make(Signed_type, -1, bit_size[3], bit_size[3]);
    unsigned_type = make(Unsigned_type, -1, 1, bit_size[3], bit_size[3]);
    uchar_type = make(Uchar_type, -1, bit_size[1], bit_size[1]);
    uint_type = make(Uint_type, -1, bit_size[3], bit_size[3]);
    ulong_type = make(Ulong_type, -1, bit_size[4], bit_size[4]);
    ulonglong_type = make(Ulonglong_type, -1, bit_size[5], bit_size[5]);
    ushort_type = make(Ushort_type, -1, bit_size[2], bit_size[2]);
    label_type = make(Label_type, -1, bit_size[9], bit_size[9]);
    void_type = make(Void_type, -1, 0, 0);
    any_type = make(Any_type, -1, bit_size[3], bit_size[3], 0);
    array_type = make(Array_type, -1, NULL);

    voidstar_type = make_pointer(void_type);
    TREE_TYPE(voidstar_type) = void_type;

    int32_type = make(Int_type, -1, 32, 32);
    uint32_type = make(Uint_type, -1, 32, 32);
    int64_type = make(Longlong_type, -1, 64, 64);
    uint64_type = make(Ulonglong_type, -1, 64, 64);
    one_constant = make_iconstant(-1, int_type, 1);
    zero_constant = make_iconstant(-1, int_type, 0);
    ellipsis = any_type;
    last_stdtree_id = zero_constant->id;
}

float cvt_float_const(TreeNode* arg0) {
    int unused;
    float value;
    MemCtx* savedCtx;
    
    savedCtx = tree_handle;
    tree_handle = general_handle;
    REALCONSTANT(arg0).value->constVal = make(Constant_special, TREE_LOCATION(arg0), float_type, value = str_to_float(REALCONSTANT(arg0).value->name, TREE_LOCATION(arg0), 4));
    tree_handle = savedCtx;
    return value;
}

double cvt_double_const(TreeNode* arg0) {
    int unused;
    double value;
    MemCtx* savedCtx;

    savedCtx = tree_handle;
    tree_handle = general_handle;
    REALCONSTANT(arg0).value->constVal = make(Constant_special, TREE_LOCATION(arg0), double_type, value = str_to_double(REALCONSTANT(arg0).value->name, TREE_LOCATION(arg0), 4));
    tree_handle = savedCtx;
    return value;
}

TreeNode* standard_tree(TreeNode* t) {
    switch (TREE_CODE(t)) {
        case Char_type:
            return char_type;
        case Int_type:
            return int_type;
        case Long_type:
            return long_type;
        case Longlong_type:
            return longlong_type;
        case Short_type:
            return short_type;
        case Uchar_type:
            return uchar_type;
        case Uint_type:
            return uint_type;
        case Ulong_type:
            return ulong_type;
        case Ulonglong_type:
            return ulonglong_type;
        case Ushort_type:
            return ushort_type;
        case Float_type:
            return float_type;
        case Double_type:
            return double_type;
        case Longdouble_type:
            return longdouble_type;
        case Void_type:
            return void_type;
        case Label_type:
            return label_type;
        case Enum_type:
            return int_type;
        default:
            return t;
    }
}

TreeNode* make_pointer(TreeNode* t) {
    TreeNode* p;
    p = make(Pointer_type, TREE_LOCATION(t));
    POINTER_TYPE(p).base_type = t;
    POINTER_TYPE(p).size = bit_size[9];
    POINTER_TYPE(p).align = bit_size[9];
}

TreeNode* make_iconstant(int location, TreeNode* type, long long value) {
    is_making_constant = TRUE;
    return make(Constant, location, type, value);
}

TreeNode* make_uiconstant(int location, TreeNode* type, unsigned long long value) {
    is_making_constant = TRUE;
    return make(Constant, location, type, value);
}#ifdef __GNUC__
// workaround to pass gcc check
#define __STDARG_H__
#define va_list int
#define va_start(x, y)
#define va_arg(x, y) (0)
#endif

#include "common.h"

// .data
static int last_node_id = 0;
static int is_making_constant = FALSE;

char* type_name[] = {
    "ident",
    "double",
    "long double",
    "float",
    "label",
    "char",
    "int",
    "long",
    "long long",
    "short",
    "signed",
    "unsigned",
    "unsigned char",
    "unsigned int",
    "unsigned long",
    "unsigned long long",
    "unsigned short",
    "void",
    "any type",
    "array",
    "enum",
    "function",
    "pointer",
    "reference",
    "struct",
};

static char* code_name[] = {
    "Identifier",
    "Double_type",
    "Longdouble_type",
    "Float_type",
    "Label_type",
    "Char_type",
    "Int_type",
    "Long_type",
    "Longlong_type",
    "Short_type",
    "Signed_type",
    "Unsigned_type",
    "Uchar_type",
    "Uint_type",
    "Ulong_type",
    "Ulonglong_type",
    "Ushort_type",
    "Void_type",
    "Any_type",
    "Array_type",
    "Enum_type",
    "Func_type",
    "Pointer_type",
    "Reference_type",
    "Struct_type",
    "Break_stmt",
    "Caselabeled_stmt",
    "Compound_stmt",
    "Continue_stmt",
    "Defaultlabeled_stmt",
    "Dowhile_stmt",
    "Expr_stmt",
    "For_stmt",
    "Goto_stmt",
    "Idlabeled_stmt",
    "If_stmt",
    "Init",
    "Return_stmt",
    "Switch_stmt",
    "While_stmt",
    "Try_stmt",
    "Leave_stmt",
    "Addr_expr",
    "Alignof_expr",
    "Bitcomplement_expr",
    "Classof_expr",
    "Indirect_expr",
    "Not_expr",
    "Postdecrement_expr",
    "Postincrement_expr",
    "Predecrement_expr",
    "Preincrement_expr",
    "Sizeof_expr",
    "Uminus_expr",
    "Uplus_expr",
    "Delete_expr",
    "Addrrel_expr",
    "And_expr",
    "Assign_expr",
    "Bitand_expr",
    "Bitor_expr",
    "Bitxor_expr",
    "Bitand_assign_expr",
    "Bitor_assign_expr",
    "Bitxor_assign_expr",
    "Call_expr",
    "Cast_expr",
    "Comma_expr",
    "Div_expr",
    "Div_assign_expr",
    "Eq_expr",
    "Gt_expr",
    "Geq_expr",
    "Index_expr",
    "Leq_expr",
    "Lshift_expr",
    "Lshift_assign_expr",
    "Lt_expr",
    "Minus_expr",
    "Minus_assign_expr",
    "Rem_expr",
    "Rem_assign_expr",
    "Mult_expr",
    "Mult_assign_expr",
    "Neq_expr",
    "Or_expr",
    "Plus_expr",
    "Plus_assign_expr",
    "Rshift_expr",
    "Rshift_assign_expr",
    "New_expr",
    "Member_init_expr",
    "Conditional_expr",
    "Aggregate_expr",
    "Array_ref",
    "Component_ref",
    "Indirect_component_ref",
    "Qualified_ref",
    "Declare_decl",
    "Id_decl",
    "Field_decl",
    "Constant",
    "End_of_file",
    "Nop",
    "Constant_special",
    "Error_mark",
    "Pragma",
    "Access_spec",
    "Reserved"
};

struct AttrDesc attr_list[] = {
    { VOLATILE_ATTRIBUTE,           "VOL" },
    { CONST_ATTRIBUTE,              "CONST" },
    { PACKED_ATTRIBUTE,             "PACK" },
    { TYPE_ATTRIBUTE,               "TYPE" },
    { EXTERN_ATTRIBUTE,             "EXT" },
    { STATIC_ATTRIBUTE,             "STAT" },
    { AUTO_ATTRIBUTE,               "AUTO" },
    { REGISTER_ATTRIBUTE,           "REG" },
    { PROTECTED_ATTRIBUTE,          "PROT" },
    { PUBLIC_ATTRIBUTE,             "PUB" },
    { PRIVATE_ATTRIBUTE,            "PRIV" },
    { VIRTUAL_ATTRIBUTE,            "VIRT" },
    { FRIEND_ATTRIBUTE,             "FRIE" },
    { INLINE_ATTRIBUTE,             "INL" },
    { VAL_ATTRIBUTE,                "VAL" },
    { REF_ATTRIBUTE,                "REF" },
    { VAR_ATTRIBUTE,                "VAR" },
    { TRY_ATTRIBUTE,                "TRY" },
    { INTR_ATTRIBUTE,               "INTR" },
    { NO_SIDE_EFFECT_ATTRIBUTE,     "NO_SIDE_EFFECT" },
    { TMP_REGS_INTACT_ATTRIBUTE,    "TMP_REGS_INTACT" },
    { WEAK_ATTRIBUTE,               "WEAK" },
    { INTU_ATTRIBUTE,               "INTU" },
    { CONSTRUCTOR_ATTRIBUTE,        "CONSTUCTOR" }, // typo
    { DESTRUCTOR_ATTRIBUTE,         "DESTRUCTOR" },
    { OPERATOR_ATTRIBUTE,           "OPER" },
    { PTR_TO_MEM_ATTRIBUTE,         "PTR_TO_MEM" },
    { ACCESS_ADJUST_ATTRIBUTE,      "ACCESS_ADJUST" },
    { UNALIGNED_ATTRIBUTE,          "UNALIGNED" },
    { CLINKAGE_ATTRIBUTE,           "CLINKAGE" },
    { CPLUSLINKAGE_ATTRIBUTE,       "CPLUSLINKAGE" },
    { FVAL_TRUEARRAY_ATTRIBUTE,     "FVAL(TRUEARRAY)" },
    { SWAP_ATTRIBUTE,               "SWAP" },
    { TMP_ATTRIBUTE,                "TMP" },
    { BL_ATTRIBUTE,                 "BL" },
    { BR_ATTRIBUTE,                 "BR" },
    { LL_ATTRIBUTE,                 "LL" },
    { LR_ATTRIBUTE,                 "LR" },
    { UNSC_ATTRIBUTE,               "UNSC" },
    { PLAIN_ATTRIBUTE,              "PLAIN" },
};

// .bss
/* 0x1002C2F0 */ static int* is_visited;
/* 0x1002C2F4 */ static int current_depth;

void set_visited(int value, int id) {
    is_visited[id] = value;
}

int get_visited(int id) {
    return is_visited[id];
}

char* get_type_name(int code) {
    if (code >= Identifier && code <= Struct_type) {
        return type_name[code];
    }
    return "???";
}

char* code_to_string(int code) {
    return code_name[code];
}

void display_attr(int attr) {
    int i;
    int foundAttrs = 0;
    int found = FALSE;
    
    if (attr == 0) {
        fprintf(stderr, "0 ");
        return;
    }

    for (i = 0; i < 40; i++) {
        if (attr_list[i].value & attr) {
            fprintf(stderr, "%s%s", found ? "|" : "", attr_list[i].desc);
            found = TRUE;
            foundAttrs = foundAttrs | attr_list[i].value;
        }
    }

    if (foundAttrs != attr) {
        fprintf(stderr, "|%x", foundAttrs ^ attr);
    }
    fprintf(stderr, " ");
}

void display_node(TreeNode* t) {
    int i;
    char* file;
    int line;
    int j;
    int k;
    int l;
    
    if (t == NULL) {
        return;
    }
    fprintf(stderr, "%2u ", TREE_ID(t));
    for (i = 0; i < current_depth; i++) {
        fprintf(stderr, " .");
    }

    fprintf(stderr, "%-14s ", code_name[TREE_CODE(t)]);
    fprintf(stderr, "type=%u ", TREE_ID(TREE_TYPE(t)));
    fprintf(stderr, "attr=");
    display_attr(TREE_ATTRIBUTE(t));
    fprintf(stderr, "link=%u ", TREE_ID(TREE_LINK(t)));
    real_file_line(TREE_LOCATION(t), &file, &line, 0);
    fprintf(stderr, "<%s/%d> ", file, line);

    switch (TREE_CODE(t)) {
        case Double_type:
        case Longdouble_type:
        case Float_type:
        case Label_type:
        case Char_type:
        case Int_type:
        case Long_type:
        case Longlong_type:
        case Short_type:
        case Signed_type:
        case Unsigned_type:
        case Uchar_type:
        case Uint_type:
        case Ulong_type:
        case Ulonglong_type:
        case Ushort_type:
        case Void_type:
        case Any_type:
            fprintf(stderr, "size=%u ", BASIC_TYPE(t).size);
            fprintf(stderr, "align=%u\n", BASIC_TYPE(t).align);
            break;
        case Array_type:
            fprintf(stderr, "size=%u ", ARRAY_TYPE(t).size);
            fprintf(stderr, "align=%u ", ARRAY_TYPE(t).align);
            fprintf(stderr, "\tindex_type=%d\n", TREE_ID(ARRAY_TYPE(t).index_type));
            break;
        case Struct_type:
            fprintf(stderr, "size=%u ", STRUCT_TYPE(t).size);
            fprintf(stderr, "align=%u ", STRUCT_TYPE(t).align);
            fprintf(stderr, "sname=%u ", TREE_ID(STRUCT_TYPE(t).sname));
            fprintf(stderr, "members=%u ", TREE_ID(STRUCT_TYPE(t).members));
            fprintf(stderr, "baselist=%u ", TREE_ID(STRUCT_TYPE(t).baselist));
            fprintf(stderr, "info=[");
            if (STRUCT_TYPE(t).info & STRUCT_INFO_STRUCT) {
                fprintf(stderr, "struct ");
            } else if (STRUCT_TYPE(t).info & STRUCT_INFO_UNION) {
                fprintf(stderr, "union ");
            } else if (STRUCT_TYPE(t).info & STRUCT_INFO_CLASS) {
                fprintf(stderr, "class ");
            }
            if (STRUCT_TYPE(t).info & STRUCT_INFO_CONST_MEMBERS) {
                fprintf(stderr, "const-members ");
            }
            if (STRUCT_TYPE(t).info & STRUCT_INFO_VOLATILE_MEMBERS) {
                fprintf(stderr, "volatile-members ");
            }
            if (STRUCT_TYPE(t).info & STRUCT_INFO_PACKED) {
                fprintf(stderr, "packed");
            }
            if (STRUCT_TYPE(t).info & STRUCT_INFO_COMPLETE) {
                fprintf(stderr, "complete");
            }
            fprintf(stderr, "]\n");
            break;
        case Enum_type:
            fprintf(stderr, "size=%u ", ENUM_TYPE(t).size);
            fprintf(stderr, "align=%u ", ENUM_TYPE(t).align);
            fprintf(stderr, "ename=%u ", TREE_ID(ENUM_TYPE(t).ename));
            fprintf(stderr, "literals=%u ", TREE_ID(ENUM_TYPE(t).literals));
            fprintf(stderr, "lb=%d ", ENUM_TYPE(t).lb);
            fprintf(stderr, "ub=%d\n", ENUM_TYPE(t).ub);
            break;
        case Func_type:
            fprintf(stderr, "size=%u ", FUNC_TYPE(t).size);
            fprintf(stderr, "align=%u ", FUNC_TYPE(t).align);
            fprintf(stderr, "fname=%u ", TREE_ID(FUNC_TYPE(t).fname));
            fprintf(stderr, "params=%u ", TREE_ID(FUNC_TYPE(t).params));
            fprintf(stderr, "decls=%u ", TREE_ID(FUNC_TYPE(t).decls));
            fprintf(stderr, "psize=%u ", FUNC_TYPE(t).psize);
            fprintf(stderr, "end_blkno=%d ", FUNC_TYPE(t).end_blkno);
            fprintf(stderr, "handlers=%u\n", TREE_ID(FUNC_TYPE(t).handlers));
            break;
        case Reference_type:
            fprintf(stderr, "size=%u ", POINTER_TYPE(t).size);
            fprintf(stderr, "align=%u ", POINTER_TYPE(t).align);
            fprintf(stderr, "base_type=%u\n", TREE_ID(POINTER_TYPE(t).base_type));
            break;
        case Pointer_type:
            fprintf(stderr, "size=%u ", POINTER_TYPE(t).size);
            fprintf(stderr, "align=%u ", POINTER_TYPE(t).align);
            fprintf(stderr, "base_type=%u\n", TREE_ID(POINTER_TYPE(t).base_type));
            break;
        case Field_decl:
            fprintf(stderr, "field=%u ", TREE_ID(FIELD_DECL(t).field));
            fprintf(stderr, "width=%d\n", FIELD_DECL(t).width);
            break;
        case Id_decl:
            fprintf(stderr, "id=%s ", ID_DECL(t).id->name);
            fprintf(stderr, "init_value=%u ", TREE_ID(ID_DECL(t).init_value));
            fprintf(stderr, "qualifiers=%u ", TREE_ID(ID_DECL(t).qualifiers));
            fprintf(stderr, "offset=%d ", ID_DECL(t).offset);
            fprintf(stderr, "sclass=%s ", sc_names[ID_DECL(t).sclass]);
            fprintf(stderr, "level=%u ", ID_DECL(t).level);
            fprintf(stderr, "alevel=%u ", ID_DECL(t).alevel);
            fprintf(stderr, "hidden=%u ", TREE_ID(ID_DECL(t).hidden));
            fprintf(stderr, "st_list=%u ", TREE_ID(ID_DECL(t).st_list));
            fprintf(stderr, "context=%u ", TREE_ID(ID_DECL(t).context));
            fprintf(stderr, "blkno=%u ", ID_DECL(t).blkno);
            fprintf(stderr, "flags=%u ", ID_DECL(t).flags);
            fprintf(stderr, "overloads=%u ", TREE_ID(ID_DECL(t).overloads));
            fprintf(stderr, "oclass=%d ", ID_DECL(t).oclass);
            if (ID_DECL(t).lastused != 0) {
                real_file_line(ID_DECL(t).lastused, &file, &line, 0);
            }
            fprintf(stderr, "lastused=<%s/%d>\n", file, line);
            break;
        case Declare_decl:
            fprintf(stderr, "ids=%u\n", TREE_ID(DECLARE_DECL(t).ids));
            break;
        case If_stmt:
            fprintf(stderr, "expr=%u ", TREE_ID(IF_STMT(t).expr));
            fprintf(stderr, "then_part=%u ", TREE_ID(IF_STMT(t).then_part));
            fprintf(stderr, "else_part=%u\n", TREE_ID(IF_STMT(t).else_part));
            break;
        case Init:
            fprintf(stderr, "value=%u ", TREE_ID(INIT(t).value));
            fprintf(stderr, "replicate=%d ", INIT(t).replicate);
            fprintf(stderr, "ExtendedSize=%d ", INIT(t).ExtendedSize);
            fprintf(stderr, "start_offset=%d\n", INIT(t).start_offset);
            break;
        case Caselabeled_stmt:
            fprintf(stderr, "expr=%u ", TREE_ID(LABELED_STMT(t).expr));
            fprintf(stderr, "stmt=%u ", TREE_ID(LABELED_STMT(t).stmt));
            fprintf(stderr, "label=%d\n", LABELED_STMT(t).label);
            break;
        case Defaultlabeled_stmt:
            fprintf(stderr, "stmt=%u\n", TREE_ID(LABELED_STMT(t).stmt));
            break;
        case Idlabeled_stmt:
            fprintf(stderr, "id=%s ", GET_IDENTIFIER(LABELED_STMT(t).id).id->name);
            fprintf(stderr, "stmt=%u\n", TREE_ID(LABELED_STMT(t).stmt));
            break;
        case Compound_stmt:
            fprintf(stderr, "decls=%u ", TREE_ID(COMPOUND_STMT(t).decls));
            fprintf(stderr, "stmts=%u ", TREE_ID(COMPOUND_STMT(t).stmts));
            real_file_line(COMPOUND_STMT(t).end_location, &file, &line, 0);
            fprintf(stderr, "end_location=<%s/%d> ", file, line);
            fprintf(stderr, "context=%u ", TREE_ID(COMPOUND_STMT(t).context));
            fprintf(stderr, "cg_info=%x\n", COMPOUND_STMT(t).cg_info);
            break;
        case Expr_stmt:
            fprintf(stderr, "expr=%u\n", TREE_ID(EXPR_STMT(t).expr));
            break;
        case Switch_stmt:
            fprintf(stderr, "expr=%u ", TREE_ID(SWITCH_STMT(t).expr));
            fprintf(stderr, "stmt=%u ", TREE_ID(SWITCH_STMT(t).stmt));
            fprintf(stderr, "breaklab=%d ", SWITCH_STMT(t).breaklab);
            fprintf(stderr, "cases=%u\n", TREE_ID(SWITCH_STMT(t).cases));
            break;
        case While_stmt:
            fprintf(stderr, "expr=%u ", TREE_ID(WHILE_STMT(t).expr));
            fprintf(stderr, "stmt=%u ", TREE_ID(WHILE_STMT(t).stmt));
            fprintf(stderr, "breaklab=%d contlab=%d\n", WHILE_STMT(t).breaklab, WHILE_STMT(t).contlab);
            break;
        case Try_stmt:
            fprintf(stderr, "expr=%u ", TREE_ID(TRY_STMT(t).expr));
            fprintf(stderr, "guard=%u ", TREE_ID(TRY_STMT(t).guard));
            fprintf(stderr, "handler=%u ", TREE_ID(TRY_STMT(t).handler));
            fprintf(stderr, "begin_addr=%u end_addr=%u label=%d jmp_target=%d\n",
                TREE_ID(TRY_STMT(t).begin_addr),
                TREE_ID(TRY_STMT(t).end_addr),
                TRY_STMT(t).label, TRY_STMT(t).jmp_target);
            break;
        case Dowhile_stmt:
            fprintf(stderr, "stmt=%u ", TREE_ID(DOWHILE_STMT(t).stmt));
            fprintf(stderr, "expr=%u ", TREE_ID(DOWHILE_STMT(t).expr));
            fprintf(stderr, "breaklab=%d contlab=%d\n", DOWHILE_STMT(t).breaklab, DOWHILE_STMT(t).contlab);
            break;
        case For_stmt:
            fprintf(stderr, "expr1=%u ", TREE_ID(FOR_STMT(t).expr1));
            fprintf(stderr, "expr2=%u ", TREE_ID(FOR_STMT(t).expr2));
            fprintf(stderr, "expr3=%u ", TREE_ID(FOR_STMT(t).expr3));
            fprintf(stderr, "stmt=%u ", TREE_ID(FOR_STMT(t).stmt));
            fprintf(stderr, "breaklab=%d contlab=%d\n", FOR_STMT(t).breaklab, FOR_STMT(t).contlab);
            break;
        case Goto_stmt:
            fprintf(stderr, "id=%s\n", GET_IDENTIFIER(GOTO_STMT(t).id).id->name);
            break;
        case Break_stmt:
        case Continue_stmt:
        case Leave_stmt:
            fprintf(stderr, "\n");
            break;
        case Return_stmt:
            fprintf(stderr, "expr=%u\n", TREE_ID(RETURN_STMT(t).expr));
            break;
        case Addr_expr:
        case Alignof_expr:
        case Bitcomplement_expr:
        case Classof_expr:
        case Indirect_expr:
        case Not_expr:
        case Postdecrement_expr:
        case Postincrement_expr:
        case Predecrement_expr:
        case Preincrement_expr:
        case Sizeof_expr:
        case Uminus_expr:
        case Uplus_expr:
        case Delete_expr:
        case Array_ref:
            fprintf(stderr, "operand[0]=%u\n", TREE_ID(UNARY_EXPR(t).operand[0]));
            break;
        case Addrrel_expr:
        case And_expr:
        case Assign_expr:
        case Bitand_expr:
        case Bitor_expr:
        case Bitxor_expr:
        case Bitand_assign_expr:
        case Bitor_assign_expr:
        case Bitxor_assign_expr:
        case Call_expr:
        case Cast_expr:
        case Comma_expr:
        case Div_expr:
        case Div_assign_expr:
        case Eq_expr:
        case Gt_expr:
        case Geq_expr:
        case Index_expr:
        case Leq_expr:
        case Lshift_expr:
        case Lshift_assign_expr:
        case Lt_expr:
        case Minus_expr:
        case Minus_assign_expr:
        case Rem_expr:
        case Rem_assign_expr:
        case Mult_expr:
        case Mult_assign_expr:
        case Neq_expr:
        case Or_expr:
        case Plus_expr:
        case Plus_assign_expr:
        case Rshift_expr:
        case Rshift_assign_expr:
        case New_expr:
        case Member_init_expr:
        case Component_ref:
        case Indirect_component_ref:
        case Qualified_ref:
            fprintf(stderr, "operand[0]=%u ", TREE_ID(BINARY_EXPR(t).operand[0]));
            fprintf(stderr, "operand[1]=%u\n", TREE_ID(BINARY_EXPR(t).operand[1]));
            break;
        case Conditional_expr:
            fprintf(stderr, "operand[0]=%u ", TREE_ID(TERNARY_EXPR(t).operand[0]));
            fprintf(stderr, "operand[1]=%u ", TREE_ID(TERNARY_EXPR(t).operand[1]));
            fprintf(stderr, "operand[2]=%u\n", TREE_ID(TERNARY_EXPR(t).operand[2]));
            break;
        case Aggregate_expr:
            for (j = 0; AGGREGATE_EXPR(t).operand[j] != NULL; j++) {
                fprintf(stderr, "operand[%d]=%u ", j, TREE_ID(AGGREGATE_EXPR(t).operand[j]));
            }
            fprintf(stderr, "\n");
            break;
        case Constant:
            switch (TREE_CODE(TREE_TYPE(t))) {
                
                case Char_type:
                case Int_type:
                case Long_type:
                case Longlong_type:
                case Short_type:
                case Signed_type:
                    fprintf(stderr, "i64=(%d,%u)\n", *(long*)&ICONSTANT(t).value, (unsigned long)ICONSTANT(t).value);
                    break;
                case Unsigned_type:
                case Uchar_type:
                case Uint_type:
                case Ulong_type:
                case Ulonglong_type:
                case Ushort_type:
                case Pointer_type:
                    fprintf(stderr, "ui64=(%u,%u)\n", *(unsigned long*)&UICONSTANT(t).value, (unsigned long)UICONSTANT(t).value);
                    break;
                case Double_type:
                case Longdouble_type:
                case Float_type:
                    if (!(TREE_ATTRIBUTE(t) & VAL_ATTRIBUTE)) {
                        fprintf(stderr, "real=%s\n", REALCONSTANT(t).value->name);
                        if (REALCONSTANT(t).value->constVal != NULL) {
                            display_node(REALCONSTANT(t).value->constVal);
                        }
                    } else if (TREE_CODE(TREE_TYPE(t)) == Float_type) {
                        fprintf(stderr, "fp=%g\n", FLTCONSTANT(t).value);
                    } else {
                        fprintf(stderr, "fp=%g\n", DBLCONSTANT(t).value);
                    }
                    break;
                case Array_type:
                    if (TREE_CODE(t) == Constant &&
                        TREE_CODE(TREE_TYPE(t)) == Array_type &&
                        (TREE_CODE(TREE_TYPE(TREE_TYPE(t))) == Uchar_type || TREE_CODE(TREE_TYPE(TREE_TYPE(t))) == Char_type)) {
                        fprintf(stderr, "s=%s\n", STRINGCONSTANT(t).value);
                    } else {
                        for (k = 0, l = 3; k < ICONSTANT(ARRAY_TYPE(TREE_TYPE(t)).index_type).value && k != 80; k++, l++) {
                            if (l == 7) {
                                fprintf(stderr, "\n");
                                l = 0;
                            }
                            fprintf(stderr, "w[%d]=%ld (%c) ", k, WSTRINGCONSTANT(t).value[k], WSTRINGCONSTANT(t).value[k]);
                        }
                        fprintf(stderr, "\n");
                    }
                    display_node(ARRAY_TYPE(TREE_TYPE(t)).index_type);
                    break;
            }
            display_node(TREE_TYPE(t));
            break;
        case Identifier:
            fprintf(stderr, "id=%s\n", GET_IDENTIFIER(t).id->name);
            break;
        case End_of_file:
        case Nop:
        case Error_mark:
        case Reserved:
            fprintf(stderr, "\n");
            break;
        case Pragma:
            fprintf(stderr, "pragma_type = %d, argument=%u\n", GET_PRAGMA(t).pragma_type, TREE_ID(GET_PRAGMA(t).argument));
            break;
        case Access_spec:
            fprintf(stderr, "access=%u\n", TREE_ID(ACCESS_SPEC(t).access));
            break;
        default:
            __assert("FALSE", "tree.c", 702);
            break;
    }
}


void preorder_walk(TreeNode* t, void (*disp)(TreeNode*)) {
    TreeNode* child;
    TreeNode** ptr;
    int j;
    // use get_visited / set_visited ?
    if (t == NULL || is_visited[t->id]) {
        return;
    }

    is_visited[t->id] = TRUE;
    current_depth++;

    switch (TREE_CODE(t)) {
        case Double_type:
        case Longdouble_type:
        case Float_type:
        case Label_type:
        case Char_type:
        case Int_type:
        case Long_type:
        case Longlong_type:
        case Short_type:
        case Signed_type:
        case Unsigned_type:
        case Uchar_type:
        case Uint_type:
        case Ulong_type:
        case Ulonglong_type:
        case Ushort_type:
        case Void_type:
        case Any_type:
            disp(t);
            break;
        case Array_type:
            disp(t);
            preorder_walk(ARRAY_TYPE(t).index_type, disp);
            break;
        case Struct_type:
            disp(t);
            preorder_walk(STRUCT_TYPE(t).sname, disp);
            for (child = STRUCT_TYPE(t).members; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = STRUCT_TYPE(t).baselist; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            break;
        case Enum_type:
            disp(t);
            preorder_walk(ENUM_TYPE(t).ename, disp);
            for (child = ENUM_TYPE(t).literals; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            break;
        case Func_type:
            disp(t);
            preorder_walk(FUNC_TYPE(t).fname, disp);
            for (child = FUNC_TYPE(t).params; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = FUNC_TYPE(t).decls; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = FUNC_TYPE(t).handlers; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            break;
        case Pointer_type:
            disp(t);
            preorder_walk(POINTER_TYPE(t).base_type, disp);
            break;
        case Reference_type:
            disp(t);
            preorder_walk(POINTER_TYPE(t).base_type, disp);
            break;
        case Field_decl:
            disp(t);
            for (child = FIELD_DECL(t).field; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            break;
        case Id_decl:
            disp(t);
            for (child = TREE_TYPE(t); child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            for (child = ID_DECL(t).init_value; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = ID_DECL(t).qualifiers; child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            preorder_walk(ID_DECL(t).context, disp);
            break;
        case Declare_decl:
            disp(t);
            for (child = TREE_TYPE(t); child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            for (child = DECLARE_DECL(t).ids; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = TREE_LINK(t), current_depth--; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            current_depth++;
            break;
        case If_stmt:
            disp(t);
            preorder_walk(IF_STMT(t).expr, disp);
            preorder_walk(IF_STMT(t).else_part, disp);
            preorder_walk(IF_STMT(t).then_part, disp);
            break;
        case Init:
            disp(t);
            preorder_walk(INIT(t).value, disp);
            break;
        case Caselabeled_stmt:
            disp(t);
            preorder_walk(LABELED_STMT(t).expr, disp);
            preorder_walk(LABELED_STMT(t).stmt, disp);
            break;
        case Defaultlabeled_stmt:
            disp(t);
            break;
        case Idlabeled_stmt:
            disp(t);
            preorder_walk(LABELED_STMT(t).id, disp);
            preorder_walk(LABELED_STMT(t).stmt, disp);
            break;
        case Compound_stmt:
            disp(t);
            for (child = COMPOUND_STMT(t).decls; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = COMPOUND_STMT(t).stmts; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            break;
        case Expr_stmt:
            disp(t);
            preorder_walk(EXPR_STMT(t).expr, disp);
            break;
        case Switch_stmt:
            disp(t);
            preorder_walk(SWITCH_STMT(t).expr, disp);
            preorder_walk(SWITCH_STMT(t).stmt, disp);
            break;
        case While_stmt:
            disp(t);
            preorder_walk(WHILE_STMT(t).expr, disp);
            preorder_walk(WHILE_STMT(t).stmt, disp);
            break;
        case Try_stmt:
            disp(t);
            preorder_walk(TRY_STMT(t).expr, disp);
            preorder_walk(TRY_STMT(t).guard, disp);
            preorder_walk(TRY_STMT(t).handler, disp);
            break;
        case Dowhile_stmt:
            disp(t);
            preorder_walk(DOWHILE_STMT(t).stmt, disp);
            preorder_walk(DOWHILE_STMT(t).expr, disp);
            break;
        case For_stmt:
            disp(t);
            preorder_walk(FOR_STMT(t).expr1, disp);
            preorder_walk(FOR_STMT(t).expr2, disp);
            preorder_walk(FOR_STMT(t).expr3, disp);
            preorder_walk(FOR_STMT(t).stmt, disp);
            break;
        case Goto_stmt:
            disp(t);
            preorder_walk(GOTO_STMT(t).id, disp);
            break;
        case Break_stmt:
        case Continue_stmt:
        case Leave_stmt:
            disp(t);
            break;
        case Return_stmt:
            disp(t);
            preorder_walk(RETURN_STMT(t).expr, disp);
            break;
        case Addr_expr:
        case Alignof_expr:
        case Bitcomplement_expr:
        case Classof_expr:
        case Indirect_expr:
        case Not_expr:
        case Postdecrement_expr:
        case Postincrement_expr:
        case Predecrement_expr:
        case Preincrement_expr:
        case Sizeof_expr:
        case Uminus_expr:
        case Uplus_expr:
        case Delete_expr:
        case Array_ref:
            disp(t);
            for (child = TREE_TYPE(t); child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            preorder_walk(UNARY_EXPR(t).operand[0], disp);
            break;
        case Cast_expr:
            disp(t);
            for (child = TREE_TYPE(t); child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            preorder_walk(BINARY_EXPR(t).operand[0], disp);
            for (child = TREE_TYPE(BINARY_EXPR(t).operand[0]); child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            preorder_walk(BINARY_EXPR(t).operand[1], disp);
            break;
        case Addrrel_expr:
        case And_expr:
        case Assign_expr:
        case Bitand_expr:
        case Bitor_expr:
        case Bitxor_expr:
        case Bitand_assign_expr:
        case Bitor_assign_expr:
        case Bitxor_assign_expr:
        case Call_expr:
        case Comma_expr:
        case Div_expr:
        case Div_assign_expr:
        case Eq_expr:
        case Gt_expr:
        case Geq_expr:
        case Index_expr:
        case Leq_expr:
        case Lshift_expr:
        case Lshift_assign_expr:
        case Lt_expr:
        case Minus_expr:
        case Minus_assign_expr:
        case Rem_expr:
        case Rem_assign_expr:
        case Mult_expr:
        case Mult_assign_expr:
        case Neq_expr:
        case Or_expr:
        case Plus_expr:
        case Plus_assign_expr:
        case Rshift_expr:
        case Rshift_assign_expr:
        case New_expr:
        case Member_init_expr:
            disp(t);
            for (child = TREE_TYPE(t); child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            preorder_walk(BINARY_EXPR(t).operand[0], disp);
            preorder_walk(BINARY_EXPR(t).operand[1], disp);
            break;
        case Component_ref:
        case Indirect_component_ref:
        case Qualified_ref:
            disp(t);
            for (child = TREE_TYPE(t); child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            if (TREE_CODE(t) != Qualified_ref && TREE_CODE(BINARY_EXPR(t).operand[1]) == Constant) {
                fprintf(stderr, "\t>value of offset is %d\n", ICONSTANT(BINARY_EXPR(t).operand[1]).value);
            }
            preorder_walk(BINARY_EXPR(t).operand[0], disp);
            preorder_walk(BINARY_EXPR(t).operand[1], disp);
            break;
        case Conditional_expr:
            disp(t);
            for (child = TREE_TYPE(t); child != NULL; child = TREE_TYPE(child)) {
                preorder_walk(child, disp);
            }
            preorder_walk(TERNARY_EXPR(t).operand[0], disp);
            preorder_walk(TERNARY_EXPR(t).operand[1], disp);
            preorder_walk(TERNARY_EXPR(t).operand[2], disp);
            break;
        case Aggregate_expr:
            disp(t);
            for (j = 0; AGGREGATE_EXPR(t).operand[j] != NULL; j++) {
                preorder_walk(AGGREGATE_EXPR(t).operand[j], disp);
            }
            break;
        case Identifier:
        case Constant:
        case End_of_file:
        case Nop:
        case Constant_special:
        case Error_mark:
        case Reserved:
            disp(t);
            break;
        case Pragma:
            disp(t);
            for (child = GET_PRAGMA(t).argument; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = TREE_LINK(t), current_depth--; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            current_depth++;
            break;
        case Access_spec:
            disp(t);
            for (child = ACCESS_SPEC(t).access; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = TREE_LINK(t), current_depth--; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            current_depth++;
            break;
        default:
            __assert("FALSE", "tree.c", 1010);
            break;
    }
    current_depth--;
}

void walk(TreeNode* t, char walk_mode, void (*disp)(TreeNode*)) {
    is_visited = mem_alloc(tree_handle, 4 * last_node_id + 4, 4);

    switch (walk_mode) {
        case 't':
            preorder_walk(t, disp);
            break;
        case 'b':
            __assert("FALSE", "tree.c", 1029);
            break;
        case 'i':
            __assert("FALSE", "tree.c", 1032);
            break;
        default:
            __assert("FALSE", "tree.c", 1035);
            break;
    }
}

void display_tree(TreeNode* t) {
    current_depth = -1;
    walk(t, 't', display_node);
}

static TreeNode* debug_child(TreeNode* t, char* c) {
    switch (TREE_CODE(t)) {
        case Array_type:
            return ARRAY_TYPE(t).index_type;
        case Struct_type:
            switch (*c) {
                case 'm':
                    return STRUCT_TYPE(t).members;
                case 's':
                    return STRUCT_TYPE(t).sname;
                case 'b':
                    return STRUCT_TYPE(t).baselist;
            }
            break;
        case Enum_type:
            switch (*c) {
                case 'l':
                    return ENUM_TYPE(t).literals;
                case 'e':
                    return ENUM_TYPE(t).ename;                
            }
            break;
        case Pointer_type:
            return POINTER_TYPE(t).base_type;
        case Reference_type:
            return POINTER_TYPE(t).base_type;
        case Func_type:
            switch (*c) {
                case 'p':
                    return FUNC_TYPE(t).params;
                case 'd':
                    return FUNC_TYPE(t).decls;
                case 'f':
                    return FUNC_TYPE(t).fname;               
                
                case 'h':
                    return FUNC_TYPE(t).handlers;
            }
            break;
        case Field_decl:
            switch (*c) {
                case 'f':
                    return FIELD_DECL(t).field;
            }
            break;
        case Id_decl:
            switch (*c) {
                case 'i':
                    return ID_DECL(t).init_value;
                case 'q':
                    return ID_DECL(t).qualifiers;
                case 'h':
                    return ID_DECL(t).hidden;
                case 's':
                    return ID_DECL(t).st_list;
                case 'c':
                    return ID_DECL(t).context;
                case 'o':
                    return ID_DECL(t).overloads;                
            }
            break;
        case Declare_decl:
            return DECLARE_DECL(t).ids;
        case If_stmt:
            switch (*c) {
                case 'e':
                    c++;
                    if (*c == 'x') {
                        return IF_STMT(t).expr;
                    } else {
                        return IF_STMT(t).else_part;
                    }
                case 't':
                    return IF_STMT(t).then_part;              
            }
            break;
        case Init:
            return INIT(t).value;
        case Caselabeled_stmt:
            switch (*c) {
                case 'e':
                    return LABELED_STMT(t).expr;
                case 's':
                    return LABELED_STMT(t).stmt;           
            }
            break;
        case Defaultlabeled_stmt:
            return LABELED_STMT(t).stmt;
        case Idlabeled_stmt:
            switch (*c) {
                case 'i':
                    return LABELED_STMT(t).id;
                case 's':
                    return LABELED_STMT(t).stmt;           
            }
            break;
        case Compound_stmt:
            switch (*c) {
                case 'd':
                    return COMPOUND_STMT(t).decls; 
                case 's':
                    return COMPOUND_STMT(t).stmts;
                case 'c':
                    return COMPOUND_STMT(t).context;             
            }
            break;
        case Expr_stmt:
            return EXPR_STMT(t).expr;
        case Dowhile_stmt:
            switch (*c) {
                case 'e':
                    return DOWHILE_STMT(t).expr;
                case 's':
                    return DOWHILE_STMT(t).stmt;           
            }
            break;
        case While_stmt:
            switch (*c) {
                case 'e':
                    return WHILE_STMT(t).expr;
                case 's':
                    return WHILE_STMT(t).stmt;           
            }
            break;
        case Try_stmt:
            switch (*c) {
                case 'e':
                    if (c[1] == 'x') {
                        return TRY_STMT(t).expr;    
                    } else {
                        return TRY_STMT(t).end_addr;
                    }
                case 'g':
                    return TRY_STMT(t).guard;
                case 'h':
                    return TRY_STMT(t).handler;
                case 'b':
                    return TRY_STMT(t).begin_addr;
                    
            }
            break;
        case Switch_stmt:
            switch (*c) {
                case 'e':
                    return SWITCH_STMT(t).expr;
                case 's':
                    return SWITCH_STMT(t).stmt;           
            }
            break;
        case For_stmt:
            switch (*c) {
                case '1':
                    return FOR_STMT(t).expr1;
                case '2':
                    return FOR_STMT(t).expr2;
                case '3':
                    return FOR_STMT(t).expr3;
                case 's':
                    return FOR_STMT(t).stmt;    
            }
            break;
        case Goto_stmt:
            return GOTO_STMT(t).id;
        case Return_stmt:
            return RETURN_STMT(t).expr;
        case Addr_expr:
        case Alignof_expr:
        case Bitcomplement_expr:
        case Classof_expr:
        case Indirect_expr:
        case Not_expr:
        case Postdecrement_expr:
        case Postincrement_expr:
        case Predecrement_expr:
        case Preincrement_expr:
        case Sizeof_expr:
        case Uminus_expr:
        case Uplus_expr:
        case Delete_expr:
        case Addrrel_expr:
        case And_expr:
        case Assign_expr:
        case Bitand_expr:
        case Bitor_expr:
        case Bitxor_expr:
        case Bitand_assign_expr:
        case Bitor_assign_expr:
        case Bitxor_assign_expr:
        case Call_expr:
        case Cast_expr:
        case Comma_expr:
        case Div_expr:
        case Div_assign_expr:
        case Eq_expr:
        case Gt_expr:
        case Geq_expr:
        case Index_expr:
        case Leq_expr:
        case Lshift_expr:
        case Lshift_assign_expr:
        case Lt_expr:
        case Minus_expr:
        case Minus_assign_expr:
        case Rem_expr:
        case Rem_assign_expr:
        case Mult_expr:
        case Mult_assign_expr:
        case Neq_expr:
        case Or_expr:
        case Plus_expr:
        case Plus_assign_expr:
        case Rshift_expr:
        case Rshift_assign_expr:
        case New_expr:
        case Member_init_expr:
        case Conditional_expr:
        case Aggregate_expr:
        case Array_ref:
        case Component_ref:
        case Indirect_component_ref:
        case Qualified_ref:
            return BINARY_EXPR(t).operand[atoi(c)];
        case Pragma:
            return GET_PRAGMA(t).argument;
        case Access_spec:
            return ACCESS_SPEC(t).access;
    }

    return t;
}

void debugger(TreeNode* arg) {
    char buffer[0x1000];
    TreeNode* siblingStack[0x1000];
    int siblingIndex = 1;
    TreeNode* childStack[0x1000];    
    int childIndex = 1;
    TreeNode* t;

    t = arg;
    childStack[0] = siblingStack[0] = NULL;
    
    while (TRUE) {
        fprintf(stderr, "(tdb)");
        fflush(stderr);
        if (gets(buffer) == NULL) {
            break;
        }

        switch (buffer[0]) {
            case 'b':
                if (siblingIndex > 1) {
                    t = siblingStack[--siblingIndex];
                }
                break;
            case 'c':
                childStack[childIndex++] = t;
                t = debug_child(t, buffer + 2);
                break;
            case 'd':
                display_node(t);
                break;
            case 'f':
                siblingStack[siblingIndex++] = t;
                t = TREE_LINK(t);
                break;
            case 'q':
                return;
            case 't':
                childStack[childIndex++] = t;
                t = TREE_TYPE(t);
                break;
            case 'u':
                if (childIndex > 1) {
                    t = childStack[--childIndex];
                }
                break;
            case '?':
                fprintf(stderr, "tdb comand      description\n");
                fprintf(stderr, "----------      ------------\n");
                fprintf(stderr, "   b            backward to last sibling\n");
                fprintf(stderr, "   c <tree>     change to subtree with name <tree>.\n");
                fprintf(stderr, "                Use 0,1...,n-1 for <tree> for expression trees\n");
                fprintf(stderr, "   d            display current node\n");
                fprintf(stderr, "   f            forward to next sibling\n");
                fprintf(stderr, "   q            quit debugger\n");
                fprintf(stderr, "   t            change to current node's type\n");
                fprintf(stderr, "   u            up to parent\n");
                fprintf(stderr, "   ?            debugger command help\n");
                break;
            default:
                fprintf(stderr, "type ? for help\n");
                break;
        }
    }
}

TreeNode* duplicate_node(TreeNode* t) {
    TreeNode* copy;

    if (t == NULL) {
        return NULL;
    }

    switch (TREE_CODE(t)) {
        case Error_mark:
            copy = make(Error_mark, TREE_LOCATION(t));
            break;
        case Id_decl:
            copy = make(Id_decl, TREE_LOCATION(t), ID_DECL(t).id);
            ID_DECL(copy).init_value = ID_DECL(t).init_value;
            ID_DECL(copy).qualifiers = ID_DECL(t).qualifiers;
            ID_DECL(copy).offset = ID_DECL(t).offset;
            ID_DECL(copy).level = ID_DECL(t).level;
            ID_DECL(copy).alevel = ID_DECL(t).alevel;
            ID_DECL(copy).sclass = ID_DECL(t).sclass;
            ID_DECL(copy).hidden = ID_DECL(t).hidden;
            ID_DECL(copy).st_list = ID_DECL(t).st_list;
            ID_DECL(copy).context = ID_DECL(t).context;
            ID_DECL(copy).blkno = ID_DECL(t).blkno;
            ID_DECL(copy).flags = ID_DECL(t).flags;
            ID_DECL(copy).overloads = ID_DECL(t).overloads;
            ID_DECL(copy).oclass = ID_DECL(t).oclass;
            ID_DECL(copy).lastused = ID_DECL(t).lastused;
            break;
        case Func_type:
            copy = make(Func_type, TREE_LOCATION(t), FUNC_TYPE(t).params);
            FUNC_TYPE(copy).fname = FUNC_TYPE(t).fname;
            FUNC_TYPE(copy).decls = FUNC_TYPE(t).decls;
            FUNC_TYPE(copy).psize = FUNC_TYPE(t).psize;
            FUNC_TYPE(copy).end_blkno = FUNC_TYPE(t).end_blkno;
            FUNC_TYPE(copy).handlers = FUNC_TYPE(t).handlers;
            break;
        case Struct_type:
            copy = make(Struct_type, TREE_LOCATION(t), NULL);
            STRUCT_TYPE(copy).sname = STRUCT_TYPE(t).sname;
            STRUCT_TYPE(copy).info = STRUCT_TYPE(t).info;
            STRUCT_TYPE(copy).members = STRUCT_TYPE(t).members;
            STRUCT_TYPE(copy).baselist = STRUCT_TYPE(t).baselist;
            STRUCT_TYPE(copy).size = STRUCT_TYPE(t).size;
            STRUCT_TYPE(copy).align = STRUCT_TYPE(t).align;
            break;
        case Enum_type:
            copy = make(Enum_type, TREE_LOCATION(t));
            ENUM_TYPE(copy).ename = ENUM_TYPE(t).ename;
            ENUM_TYPE(copy).literals = ENUM_TYPE(t).literals;
            ENUM_TYPE(copy).lb = ENUM_TYPE(t).lb;
            ENUM_TYPE(copy).ub = ENUM_TYPE(t).ub;
            ENUM_TYPE(copy).size = ENUM_TYPE(t).size;
            ENUM_TYPE(copy).align = ENUM_TYPE(t).align;
            break;
        case Array_type:
            copy = make(Array_type, TREE_LOCATION(t));
            TREE_TYPE(copy) = TREE_TYPE(t);
            ARRAY_TYPE(copy).index_type = ARRAY_TYPE(t).index_type;
            ARRAY_TYPE(copy).size = ARRAY_TYPE(t).size;
            ARRAY_TYPE(copy).align = ARRAY_TYPE(t).align;
            break;
        case Double_type:
        case Longdouble_type:
        case Float_type:
        case Label_type:
        case Char_type:
        case Int_type:
        case Long_type:
        case Longlong_type:
        case Short_type:
        case Signed_type:
        case Unsigned_type:
        case Uchar_type:
        case Uint_type:
        case Ulong_type:
        case Ulonglong_type:
        case Ushort_type:
        case Void_type:
        case Any_type:
            copy = make(TREE_CODE(t), TREE_LOCATION(t), BASIC_TYPE(t).size, BASIC_TYPE(t).align);
            BASIC_TYPE(copy).size = BASIC_TYPE(t).size;
            BASIC_TYPE(copy).align = BASIC_TYPE(t).align;
            break;
        case Pointer_type:
            copy = make(Pointer_type, TREE_LOCATION(t));
            POINTER_TYPE(copy).size = POINTER_TYPE(t).size;
            POINTER_TYPE(copy).align = POINTER_TYPE(t).align;
            POINTER_TYPE(copy).base_type = POINTER_TYPE(t).base_type;
            break;
        case Reference_type:
            copy = make(Reference_type, TREE_LOCATION(t));
            POINTER_TYPE(copy).size = POINTER_TYPE(t).size;
            POINTER_TYPE(copy).align = POINTER_TYPE(t).align;
            POINTER_TYPE(copy).base_type = POINTER_TYPE(t).base_type;
            break;
        case Constant:
            switch (TREE_CODE(TREE_TYPE(t))) {
                case Char_type:
                case Int_type:
                case Long_type:
                case Longlong_type:
                case Short_type:
                case Signed_type:
                    copy = make_iconstant(TREE_LOCATION(t), TREE_TYPE(t), ICONSTANT(t).value);
                    break;
                case Unsigned_type:
                case Uchar_type:
                case Uint_type:
                case Ulong_type:
                case Ulonglong_type:
                case Ushort_type:
                case Pointer_type:
                    // why not make_uiconstant ??
                    copy = make_iconstant(TREE_LOCATION(t), TREE_TYPE(t), UICONSTANT(t).value);
                    break;
                default:
                    __assert("FALSE", "tree.c", 0x5BB);
            }
            break;
        case Addr_expr:
        case Alignof_expr:
        case Bitcomplement_expr:
        case Classof_expr:
        case Indirect_expr:
        case Not_expr:
        case Postdecrement_expr:
        case Postincrement_expr:
        case Predecrement_expr:
        case Preincrement_expr:
        case Sizeof_expr:
        case Uminus_expr:
        case Uplus_expr:
        case Delete_expr:
        case Array_ref:
            copy = make(TREE_CODE(t), TREE_LOCATION(t), UNARY_EXPR(t).operand[0]);
            break;
        case Addrrel_expr:
        case And_expr:
        case Assign_expr:
        case Bitand_expr:
        case Bitor_expr:
        case Bitxor_expr:
        case Bitand_assign_expr:
        case Bitor_assign_expr:
        case Bitxor_assign_expr:
        case Call_expr:
        case Cast_expr:
        case Comma_expr:
        case Div_expr:
        case Div_assign_expr:
        case Eq_expr:
        case Gt_expr:
        case Geq_expr:
        case Index_expr:
        case Leq_expr:
        case Lshift_expr:
        case Lshift_assign_expr:
        case Lt_expr:
        case Minus_expr:
        case Minus_assign_expr:
        case Rem_expr:
        case Rem_assign_expr:
        case Mult_expr:
        case Mult_assign_expr:
        case Neq_expr:
        case Or_expr:
        case Plus_expr:
        case Plus_assign_expr:
        case Rshift_expr:
        case Rshift_assign_expr:
        case New_expr:
        case Member_init_expr:
        case Component_ref:
        case Indirect_component_ref:
        case Qualified_ref:
            copy = make(TREE_CODE(t), TREE_LOCATION(t), BINARY_EXPR(t).operand[0], BINARY_EXPR(t).operand[1]);
            break;
        case Conditional_expr:
            copy = make(TREE_CODE(t), TREE_LOCATION(t), TERNARY_EXPR(t).operand[0], TERNARY_EXPR(t).operand[1], TERNARY_EXPR(t).operand[2]);
            break;
        default:
            __assert("FALSE", "tree.c", 1532);
            break;
    }

    TREE_ATTRIBUTE(copy) = TREE_ATTRIBUTE(t);
    TREE_TYPE(copy) = TREE_TYPE(t);
    TREE_LINK(copy) = TREE_LINK(t);
    return copy;
}

TreeNode* unqual_type(TreeNode* t) {
    TreeNode* nonStdType;
    int isPlain;

    if ((TREE_ATTRIBUTE(t) & PLAIN_ATTRIBUTE) && !(IS_STD_TREE(t))) {
        isPlain = TRUE;
    } else {
        isPlain = FALSE;
    }

    if (TREE_ATTRIBUTE(t) & (VOLATILE_ATTRIBUTE | CONST_ATTRIBUTE | TYPE_ATTRIBUTE | UNALIGNED_ATTRIBUTE)) {
        if (TREE_CODE(t) == Struct_type || TREE_CODE(t) == Enum_type) {
            t = TREE_TYPE(t);
        } else if (TREE_CODE(t) == Array_type || TREE_CODE(t) == Pointer_type || TREE_CODE(t) == Func_type) {
            t = duplicate_node(t);
            TREE_ATTRIBUTE(t) = 0;
        } else {
            switch (TREE_CODE(t)) {
                case Void_type:
                    t = void_type;
                    break;
                case Char_type:
                    t = char_type;
                    break;
                case Uchar_type:
                    t = uchar_type;
                    break;
                case Short_type:
                    t = short_type;
                    break;
                case Ushort_type:
                    t = ushort_type;
                    break;
                case Int_type:
                    t = int_type;
                    break;
                case Long_type:
                    t = long_type;
                    break;
                case Longlong_type:
                    t = longlong_type;
                    break;
                case Signed_type:
                    t = signed_type;
                    break;
                case Unsigned_type:
                    t = unsigned_type;
                    break;
                case Uint_type:
                    t = uint_type;
                    break;
                case Ulong_type:
                    t = ulong_type;
                    break;
                case Ulonglong_type:
                    t = ulonglong_type;
                    break;
                case Float_type:
                    t = float_type;
                    break;
                case Longdouble_type:
                    t = longdouble_type;
                    break;
                case Double_type:
                    t = double_type;
                    break;
            }
        }
    }
    
    if (isPlain) {
        TreeNode* type;
        
        for (type = t, nonStdType = t; type != NULL; type = TREE_TYPE(type)) {
            if (IS_STD_TREE(type)) {
                break;
            }
            nonStdType = type;
        }
        TREE_ATTRIBUTE(nonStdType) |= PLAIN_ATTRIBUTE;
    }

    return t;
}

TreeNode* make(int code, int location, ...) {
    va_list args;
    TreeNode* type;
    char* str;
    int* wide_str;
    TreeNode* t;
    int string_len;
    TreeNode* arg;
    int wide_string_size;
    TreeNode* aggr_operand;
    int i;

    va_start(args, location);
    
    switch (code) {
        case Double_type:
        case Longdouble_type:
        case Float_type:
        case Label_type:
        case Char_type:
        case Int_type:
        case Long_type:
        case Longlong_type:
        case Short_type:
        case Signed_type:
        case Unsigned_type:
        case Uchar_type:
        case Uint_type:
        case Ulong_type:
        case Ulonglong_type:
        case Ushort_type:
        case Void_type:
        case Any_type:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Basic_type), 4);
            BASIC_TYPE(t).size = va_arg(args, int);
            BASIC_TYPE(t).align = va_arg(args, int);
            break;
        case Array_type:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Array_type), 4);
            ARRAY_TYPE(t).index_type = va_arg(args, TreeNode*);
            break;
        case Struct_type:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Struct_type), 4);
            STRUCT_TYPE(t).info = va_arg(args, int);
            break;
        case Enum_type:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Enum_type), 4);
            break;
        case Func_type:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Func_type), 4);
            FUNC_TYPE(t).params = va_arg(args, TreeNode*);
            break;
        case Pointer_type:
        case Reference_type:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Pointer_type), 4);
            break;
        case Field_decl:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Field_decl), 4);
            break;
        case Id_decl:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Id_decl), 4);
            ID_DECL(t).id = va_arg(args, Symbol*);
            break;
        case Declare_decl:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Declare_decl), 4);
            TREE_TYPE(t) = va_arg(args, TreeNode*);
            DECLARE_DECL(t).ids = va_arg(args, TreeNode*);
            break;
        case If_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_If_stmt), 4);
            IF_STMT(t).expr = va_arg(args, TreeNode*);
            IF_STMT(t).then_part = va_arg(args, TreeNode*);
            IF_STMT(t).else_part = va_arg(args, TreeNode*);
            break;
        case Init:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Init), 4);
            INIT(t).value = va_arg(args, TreeNode*);
            INIT(t).replicate = va_arg(args, int);
            INIT(t).start_offset = va_arg(args, int);
            break;
        case Pragma:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Pragma), 4);
            GET_PRAGMA(t).pragma_type = va_arg(args, int);
            GET_PRAGMA(t).argument = va_arg(args, TreeNode*);
            break;
        case Access_spec:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Access_spec), 4);
            ACCESS_SPEC(t).access = va_arg(args, TreeNode*);
            break;
        case Caselabeled_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Labeled_stmt), 4);
            LABELED_STMT(t).expr = va_arg(args, TreeNode*);
            LABELED_STMT(t).stmt = va_arg(args, TreeNode*);
            break;
        case Defaultlabeled_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Labeled_stmt), 4);
            LABELED_STMT(t).stmt = va_arg(args, TreeNode*);
            break;
        case Idlabeled_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Labeled_stmt), 4);
            LABELED_STMT(t).id = va_arg(args, TreeNode*);
            LABELED_STMT(t).stmt = va_arg(args, TreeNode*);
            break;
        case Compound_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Compound_stmt), 4);
            COMPOUND_STMT(t).decls = va_arg(args, TreeNode*);
            COMPOUND_STMT(t).stmts = va_arg(args, TreeNode*);
            COMPOUND_STMT(t).end_location = va_arg(args, int);
            break;
        case Expr_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Expr_stmt), 4);
            EXPR_STMT(t).expr = va_arg(args, TreeNode*);
            break;
        case Switch_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Switch_stmt), 4);
            SWITCH_STMT(t).expr = va_arg(args, TreeNode*);
            SWITCH_STMT(t).stmt = va_arg(args, TreeNode*);
            break;
        case While_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_While_stmt), 4);
            WHILE_STMT(t).expr = va_arg(args, TreeNode*);
            WHILE_STMT(t).stmt = va_arg(args, TreeNode*);
            break;
        case Try_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Try_stmt), 4);
            TRY_STMT(t).expr = va_arg(args, TreeNode*);
            TRY_STMT(t).guard = va_arg(args, TreeNode*);
            TRY_STMT(t).handler = va_arg(args, TreeNode*);
            break;
        case Dowhile_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Dowhile_stmt), 4);
            DOWHILE_STMT(t).stmt = va_arg(args, TreeNode*);
            DOWHILE_STMT(t).expr = va_arg(args, TreeNode*);            
            break;
        case For_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_For_stmt), 4);
            FOR_STMT(t).expr1 = va_arg(args, TreeNode*);
            FOR_STMT(t).expr2 = va_arg(args, TreeNode*);
            FOR_STMT(t).expr3 = va_arg(args, TreeNode*);
            FOR_STMT(t).stmt = va_arg(args, TreeNode*);
            break;
        case Goto_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Goto_stmt), 4);
            GOTO_STMT(t).id = va_arg(args, TreeNode*);
            break;
        case Break_stmt:
        case Continue_stmt:
        case Leave_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode), 4);
            break;
        case Return_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Return_stmt), 4);
            RETURN_STMT(t).expr = va_arg(args, TreeNode*);
            break;
        case Addr_expr:
        case Alignof_expr:
        case Bitcomplement_expr:
        case Classof_expr:
        case Indirect_expr:
        case Not_expr:
        case Postdecrement_expr:
        case Postincrement_expr:
        case Predecrement_expr:
        case Preincrement_expr:
        case Sizeof_expr:
        case Uminus_expr:
        case Uplus_expr:
        case Delete_expr:
        case Array_ref:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Unary_expr), 4);
            UNARY_EXPR(t).operand[0] = va_arg(args, TreeNode*);
            break;
        case Addrrel_expr:
        case And_expr:
        case Assign_expr:
        case Bitand_expr:
        case Bitor_expr:
        case Bitxor_expr:
        case Bitand_assign_expr:
        case Bitor_assign_expr:
        case Bitxor_assign_expr:
        case Call_expr:
        case Cast_expr:
        case Comma_expr:
        case Div_expr:
        case Div_assign_expr:
        case Eq_expr:
        case Gt_expr:
        case Geq_expr:
        case Index_expr:
        case Leq_expr:
        case Lshift_expr:
        case Lshift_assign_expr:
        case Lt_expr:
        case Minus_expr:
        case Minus_assign_expr:
        case Rem_expr:
        case Rem_assign_expr:
        case Mult_expr:
        case Mult_assign_expr:
        case Neq_expr:
        case Or_expr:
        case Plus_expr:
        case Plus_assign_expr:
        case Rshift_expr:
        case Rshift_assign_expr:
        case New_expr:
        case Member_init_expr:
        case Component_ref:
        case Indirect_component_ref:
        case Qualified_ref:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Binary_expr), 4);
            BINARY_EXPR(t).operand[0] = va_arg(args, TreeNode*);
            BINARY_EXPR(t).operand[1] = va_arg(args, TreeNode*);
            break;
        case Conditional_expr:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Ternary_expr), 4);
            TERNARY_EXPR(t).operand[0] = va_arg(args, TreeNode*);
            TERNARY_EXPR(t).operand[1] = va_arg(args, TreeNode*);
            TERNARY_EXPR(t).operand[2] = va_arg(args, TreeNode*);
            break;
        case Aggregate_expr:
            i = 0;
            t = arg = va_arg(args, TreeNode*);
            while (arg != NULL) {
                i++;
                arg = TREE_LINK(arg);
            }
            aggr_operand = t;
            t = mem_alloc(tree_handle, sizeof(TreeNode_Aggregate_expr) + 4 * i, 4);
            i = 0;
            while (TRUE) {
                arg = aggr_operand;
                aggr_operand = TREE_LINK(aggr_operand);
                AGGREGATE_EXPR(t).operand[i] = arg;
                TREE_LINK(arg) = NULL;
                i++;
                if (aggr_operand == NULL) {
                    AGGREGATE_EXPR(t).operand[i] = NULL;
                    break;
                }
            }
            
            break;
        case Constant:
            type = va_arg(args, TreeNode*);
            switch (TREE_CODE(type)) {
                case Char_type:
                case Int_type:
                case Long_type:
                case Longlong_type:
                case Short_type:
                case Signed_type:
                    if (!is_making_constant) {
                        __assert("FALSE", "tree.c", 1882);
                    }
                    is_making_constant = FALSE;

                    t = mem_alloc(tree_handle, sizeof(TreeNode_IConstant), 8);
                    ICONSTANT(t).value = va_arg(args, long long);
                    break;
                case Enum_type:
                    type = uint_type;
                    /* fallthrough */
                case Unsigned_type:
                case Uchar_type:
                case Uint_type:
                case Ulong_type:
                case Ulonglong_type:
                case Ushort_type:
                case Pointer_type:
                    if (!is_making_constant) {
                        __assert("FALSE", "tree.c", 1900);
                    }
                    is_making_constant = FALSE;

                    t = mem_alloc(tree_handle, sizeof(TreeNode_UIConstant), 8);
                    UICONSTANT(t).value = va_arg(args, unsigned long long);
                    break;
                case Double_type:
                case Longdouble_type:
                case Float_type:
                    t = mem_alloc(tree_handle, sizeof(TreeNode_RealConstant), 8);
                    REALCONSTANT(t).value = va_arg(args, Symbol*);
                    break;
                case Label_type:
                case Void_type:
                case Any_type:
                    __assert("FALSE", "tree.c", 1925);
                    break;
                case Array_type:
                    type = mem_alloc(tree_handle, sizeof(TreeNode_Array_type), 4);
                    str = va_arg(args, char*);
                    string_len = va_arg(args, int);
                    ARRAY_TYPE(type).size = bit_size[1] * string_len;
                    ARRAY_TYPE(type).align = bit_size[1];
                    t = mem_alloc(tree_handle, 0x18 + string_len * 1, 4); // sizeof(TreeNode_StringConstant) ?
                    TREE_CODE(type) = Array_type;
                    TREE_TYPE(type) = options[6] ? char_type : uchar_type;
                    type->id = ++last_node_id;
                    ARRAY_TYPE(type).index_type = make_iconstant(location, long_type, string_len);
                    memcpy(STRINGCONSTANT(t).value, str, string_len);
                    break;
                default:
                    __assert("FALSE", "tree.c", 1942);
                    break;
            }
            TREE_TYPE(t) = type;
            break;
        case Constant_special:
            type = va_arg(args, TreeNode*);
            switch (TREE_CODE(type)) {
                case Double_type:
                case Longdouble_type:
                    t = mem_alloc(tree_handle, sizeof(TreeNode_DblConstant), 8);
                    DBLCONSTANT(t).value = va_arg(args, double);
                    TREE_ATTRIBUTE(t) = VAL_ATTRIBUTE;
                    break;
                case Float_type:
                    t = mem_alloc(tree_handle, sizeof(TreeNode_FltConstant), 4);
                    FLTCONSTANT(t).value = va_arg(args, double);
                    TREE_ATTRIBUTE(t) = VAL_ATTRIBUTE;
                    break;
                case Array_type:
                    type = mem_alloc(tree_handle, sizeof(TreeNode_Array_type), 4);
                    wide_str = va_arg(args, int*);
                    string_len = va_arg(args, int);
                    wide_string_size = string_len * 4;
                    ARRAY_TYPE(type).size = bit_size[4] * string_len;
                    ARRAY_TYPE(type).align = bit_size[4];
                    t = mem_alloc(tree_handle, 0x18 + wide_string_size, 4); // sizeof(TreeNode_WStringConstant) ?
                    TREE_CODE(type) = Array_type;
                    TREE_TYPE(type) = long_type;
                    type->id = ++last_node_id;
                    ARRAY_TYPE(type).index_type = make_iconstant(location, long_type, string_len);
                    memcpy(WSTRINGCONSTANT(t).value, wide_str, wide_string_size);
                    break;
            }
            TREE_TYPE(t) = type;
            code = Constant;
            break;
        case Identifier:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Identifier), 4);
            GET_IDENTIFIER(t).id = va_arg(args, Symbol*);
            break;
        case End_of_file:
        case Nop:
        case Error_mark:
        case Reserved:
            t = mem_alloc(tree_handle, sizeof(TreeNode), 4);
            break;
        default:
            __assert("FALSE", "tree.c", 1991);
            break;
    }

    t->id = ++last_node_id;
    TREE_CODE(t) = code;
    TREE_LOCATION(t) = location;

    return t;
}

void init_trees(void) {
    tree_handle = general_handle;
}

void make_std_trees(void) {
    char_type = make(Char_type, -1, bit_size[1], bit_size[1]);
    double_type = make(Double_type, -1, bit_size[7], bit_size[7]);
    int_type = make(Int_type, -1, bit_size[3], bit_size[3]);
    float_type = make(Float_type, -1, bit_size[6], bit_size[6]);
    long_type = make(Long_type, -1, bit_size[4], bit_size[4]);
    longlong_type = make(Longlong_type, -1, bit_size[5], bit_size[5]);
    longdouble_type = make(Longdouble_type, -1, bit_size[8], bit_size[8]);
    short_type = make(Short_type, -1, bit_size[2], bit_size[2]);
    signed_type = make(Signed_type, -1, bit_size[3], bit_size[3]);
    unsigned_type = make(Unsigned_type, -1, 1, bit_size[3], bit_size[3]);
    uchar_type = make(Uchar_type, -1, bit_size[1], bit_size[1]);
    uint_type = make(Uint_type, -1, bit_size[3], bit_size[3]);
    ulong_type = make(Ulong_type, -1, bit_size[4], bit_size[4]);
    ulonglong_type = make(Ulonglong_type, -1, bit_size[5], bit_size[5]);
    ushort_type = make(Ushort_type, -1, bit_size[2], bit_size[2]);
    label_type = make(Label_type, -1, bit_size[9], bit_size[9]);
    void_type = make(Void_type, -1, 0, 0);
    any_type = make(Any_type, -1, bit_size[3], bit_size[3], 0);
    array_type = make(Array_type, -1, NULL);

    voidstar_type = make_pointer(void_type);
    TREE_TYPE(voidstar_type) = void_type;

    int32_type = make(Int_type, -1, 32, 32);
    uint32_type = make(Uint_type, -1, 32, 32);
    int64_type = make(Longlong_type, -1, 64, 64);
    uint64_type = make(Ulonglong_type, -1, 64, 64);
    one_constant = make_iconstant(-1, int_type, 1);
    zero_constant = make_iconstant(-1, int_type, 0);
    ellipsis = any_type;
    last_stdtree_id = zero_constant->id;
}

float cvt_float_const(TreeNode* arg0) {
    int unused;
    float value;
    MemCtx* savedCtx;
    
    savedCtx = tree_handle;
    tree_handle = general_handle;
    REALCONSTANT(arg0).value->constVal = make(Constant_special, TREE_LOCATION(arg0), float_type, value = str_to_float(REALCONSTANT(arg0).value->name, TREE_LOCATION(arg0), 4));
    tree_handle = savedCtx;
    return value;
}

double cvt_double_const(TreeNode* arg0) {
    int unused;
    double value;
    MemCtx* savedCtx;

    savedCtx = tree_handle;
    tree_handle = general_handle;
    REALCONSTANT(arg0).value->constVal = make(Constant_special, TREE_LOCATION(arg0), double_type, value = str_to_double(REALCONSTANT(arg0).value->name, TREE_LOCATION(arg0), 4));
    tree_handle = savedCtx;
    return value;
}

TreeNode* standard_tree(TreeNode* t) {
    switch (TREE_CODE(t)) {
        case Char_type:
            return char_type;
        case Int_type:
            return int_type;
        case Long_type:
            return long_type;
        case Longlong_type:
            return longlong_type;
        case Short_type:
            return short_type;
        case Uchar_type:
            return uchar_type;
        case Uint_type:
            return uint_type;
        case Ulong_type:
            return ulong_type;
        case Ulonglong_type:
            return ulonglong_type;
        case Ushort_type:
            return ushort_type;
        case Float_type:
            return float_type;
        case Double_type:
            return double_type;
        case Longdouble_type:
            return longdouble_type;
        case Void_type:
            return void_type;
        case Label_type:
            return label_type;
        case Enum_type:
            return int_type;
        default:
            return t;
    }
}

TreeNode* make_pointer(TreeNode* t) {
    TreeNode* p;
    p = make(Pointer_type, TREE_LOCATION(t));
    POINTER_TYPE(p).base_type = t;
    POINTER_TYPE(p).size = bit_size[9];
    POINTER_TYPE(p).align = bit_size[9];
}

TreeNode* make_iconstant(int location, TreeNode* type, long long value) {
    is_making_constant = TRUE;
    return make(Constant, location, type, value);
}

TreeNode* make_uiconstant(int location, TreeNode* type, unsigned long long value) {
    is_making_constant = TRUE;
    return make(Constant, location, type, value);
}