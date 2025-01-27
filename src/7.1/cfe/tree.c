#ifdef __GNUC__
// workaround to pass gcc check
#define __STDARG_H__
#define va_list int
#define va_start(x, y)
#define va_arg(x, y) (0)
#endif

#include "common.h"

// .data
static int D_1001D470 = 0;
static int D_1001D474 = 0;

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

static char* D_1001D4DC[] = {
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
    { 0x80000000, "VOL"},
    { 0x40000000, "CONST"},
    { 0x20000000, "PACK"},
    { 0x10000000, "TYPE"},
    { 0x08000000, "EXT"},
    { 0x04000000, "STAT"},
    { 0x02000000, "AUTO"},
    { 0x01000000, "REG"},
    { 0x00800000, "PROT"},
    { 0x00400000, "PUB"},
    { 0x00200000, "PRIV"},
    { 0x00100000, "VIRT"},
    { 0x00000800, "FRIE"},
    { 0x00080000, "INL"},
    { 0x00040000, "VAL"},
    { 0x00020000, "REF"},
    { 0x00010000, "VAR"},
    { 0x00008000, "TRY"},
    { 0x00004000, "INTR"},
    { 0x00000004, "NO_SIDE_EFFECT"},
    { 0x00000002, "TMP_REGS_INTACT"},
    { 0x00002000, "WEAK"},
    { 0x00001000, "INTU"},
    { 0x00000800, "CONSTRUCTOR"},
    { 0x00000400, "DESTRUCTOR"},
    { 0x00000400, "OPER"},
    { 0x00000200, "PTR_TO_MEM"},
    { 0x00000100, "ACCESS_ADJUST"},
    { 0x00000080, "UNALIGNED"},
    { 0x00000040, "CLINKAGE"},
    { 0x00000020, "CPLUSLINKAGE"},
    { 0x00040000, "FVAL(TRUEARRAY)"},
    { 0x04000000, "SWAP"},
    { 0x01000000, "TMP"},
    { 0x20000000, "BL"},
    { 0x08000000, "BR"},
    { 0x04000000, "LL"},
    { 0x02000000, "LR"},
    { 0x08000000, "UNSC"},
    { 0x00000010, "PLAIN"},
};

// .bss
/* 0x1002C2F0 */ static int* B_1002C2F0;
/* 0x1002C2F4 */ static int B_1002C2F4;

void set_visited(int arg0, int arg1) {
    B_1002C2F0[arg1] = arg0;
}

int get_visited(int arg0) {
    return B_1002C2F0[arg0];
}

char* get_type_name(int arg0) {
    if (arg0 >= Identifier && arg0 <= Struct_type) {
        return type_name[arg0];
    }
    return "???";
}

char* code_to_string(int arg0) {
    return D_1001D4DC[arg0];
}

void display_attr(int arg0) {
    int i;
    int s2 = 0;
    int found = FALSE;
    
    if (arg0 == 0) {
        fprintf(stderr, "0 ");
        return;
    }

    for (i = 0; i < 40; i++) {
        if (attr_list[i].value & arg0) {
            fprintf(stderr, "%s%s", found ? "|" : "", attr_list[i].desc);
            found = TRUE;
            s2 = s2 | attr_list[i].value;
        }
    }

    if (s2 != arg0) {
        fprintf(stderr, "|%x", s2 ^ arg0);
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
    for (i = 0; i < B_1002C2F4; i++) {
        fprintf(stderr, " .");
    }

    fprintf(stderr, "%-14s ", D_1001D4DC[TREE_CODE(t)]);
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
            if (STRUCT_TYPE(t).info & 0x80000000) {
                fprintf(stderr, "struct ");
            } else if (STRUCT_TYPE(t).info & 0x40000000) {
                fprintf(stderr, "union ");
            } else if (STRUCT_TYPE(t).info & 0x20000000) {
                fprintf(stderr, "class ");
            }
            if (STRUCT_TYPE(t).info & 0x10000000) {
                fprintf(stderr, "const-members ");
            }
            if (STRUCT_TYPE(t).info & 0x08000000) {
                fprintf(stderr, "volatile-members ");
            }
            if (STRUCT_TYPE(t).info & 0x04000000) {
                fprintf(stderr, "packed");
            }
            if (STRUCT_TYPE(t).info & 0x02000000) {
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
            fprintf(stderr, "size=%u ", REFERENCE_TYPE(t).size);
            fprintf(stderr, "align=%u ", REFERENCE_TYPE(t).align);
            fprintf(stderr, "base_type=%u\n", TREE_ID(REFERENCE_TYPE(t).base_type));
            break;
        case Pointer_type:
            fprintf(stderr, "size=%u ", POINTER_TYPE(t).size);
            fprintf(stderr, "align=%u ", POINTER_TYPE(t).align);
            fprintf(stderr, "base_type=%u\n", TREE_ID(POINTER_TYPE(t).base_type));
            break;
        case Field_decl:
            fprintf(stderr, "field=%u ", TREE_ID(FIELD_DECL(t).field));
            fprintf(stderr, "width=%u\n", FIELD_DECL(t).width);
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
            fprintf(stderr, "expr=%u ", TREE_ID(SWITCH_STMT(t).expr));
            fprintf(stderr, "stmt=%u ", TREE_ID(SWITCH_STMT(t).stmt));
            fprintf(stderr, "breaklab=%d contlab=%d\n", SWITCH_STMT(t).breaklab, SWITCH_STMT(t).contlab);
            break;
        case Try_stmt:
            fprintf(stderr, "expr=%u ", TREE_ID(TRY_STMT(t).expr));
            fprintf(stderr, "guard=%u ", TREE_ID(TRY_STMT(t).guard));
            fprintf(stderr, "handler=%u\n", TREE_ID(TRY_STMT(t).handler));
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
                    fprintf(stderr, "i64=(%d,%u)\n", GET_CONSTANT(t).value.ll);
                    break;
                case Unsigned_type:
                case Uchar_type:
                case Uint_type:
                case Ulong_type:
                case Ulonglong_type:
                case Ushort_type:
                case Pointer_type:
                    fprintf(stderr, "ui64=(%d,%u)\n", GET_CONSTANT(t).value.ull);
                    break;
                case Double_type:
                case Longdouble_type:
                case Float_type:
                    if (!(TREE_ATTRIBUTE(t) & 0x40000)) { // TODO name attribute
                        int a0;
                        fprintf(stderr, "real=%s\n", GET_CONSTANT(t).value.real->name);
                        a0 = GET_CONSTANT(t).value.real->unk_00; 
                        if (a0) {
                            display_node((TreeNode*)a0); // TODO type!
                        }
                    } else if (TREE_CODE(TREE_TYPE(t)) == Float_type) {
                        fprintf(stderr, "fp=%g\n", GET_CONSTANT(t).value.flt);
                    } else {
                        fprintf(stderr, "fp=%g\n", GET_CONSTANT(t).value.dbl);
                    }
                    break;
                case Array_type:
                    if (TREE_CODE(t) == Constant && TREE_CODE(TREE_TYPE(t)) == Array_type &&
                        (TREE_CODE(TREE_TYPE(TREE_TYPE(t))) == Uchar_type || TREE_CODE(TREE_TYPE(TREE_TYPE(t))) == Char_type)) {
                        fprintf(stderr, "s=%s\n", GET_CONSTANT(t).value.str);
                    } else {
                        for (k = 0, l = 3; k < GET_UNKNOWN1(ARRAY_TYPE(TREE_TYPE(t)).index_type).size && k != 80; k++, l++) {
                            if (l == 7) {
                                fprintf(stderr, "\n");
                                l = 0;
                            }
                            fprintf(stderr, "w[%d]=%ld (%c) ", k, GET_CONSTANT(t).value.array[k], GET_CONSTANT(t).value.array[k]);
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
    if (t == NULL || B_1002C2F0[t->id]) {
        return;
    }

    B_1002C2F0[t->id] = TRUE;
    B_1002C2F4++;

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
            preorder_walk(REFERENCE_TYPE(t).base_type, disp);
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
            for (child = TREE_LINK(t), B_1002C2F4--; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            B_1002C2F4++;
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
                fprintf(stderr, "\t>value of offset is %d\n", GET_CONSTANT(BINARY_EXPR(t).operand[1]).value.ll);
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
            for (child = TREE_LINK(t), B_1002C2F4--; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            B_1002C2F4++;
            break;
        case Access_spec:
            disp(t);
            for (child = ACCESS_SPEC(t).access; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            for (child = TREE_LINK(t), B_1002C2F4--; child != NULL; child = TREE_LINK(child)) {
                preorder_walk(child, disp);
            }
            B_1002C2F4++;
            break;
        default:
            __assert("FALSE", "tree.c", 1010);
            break;
    }
    B_1002C2F4--;
}

void walk(TreeNode* t, char arg1, void (*disp)(TreeNode*)) {
    B_1002C2F0 = mem_alloc(tree_handle, 4 * D_1001D470 + 4, 4);

    switch (arg1) {
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
    B_1002C2F4 = -1;
    walk(t, 't', display_node);
}

TreeNode* func_0041F630(TreeNode* t, char* c) {
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
            return REFERENCE_TYPE(t).base_type;
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
                t = func_0041F630(t, buffer + 2);
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
            REFERENCE_TYPE(copy).size = REFERENCE_TYPE(t).size;
            REFERENCE_TYPE(copy).align = REFERENCE_TYPE(t).align;
            REFERENCE_TYPE(copy).base_type = REFERENCE_TYPE(t).base_type;
            break;
        case Constant:
            switch (TREE_CODE(TREE_TYPE(t))) {
                case Char_type:
                case Int_type:
                case Long_type:
                case Longlong_type:
                case Short_type:
                case Signed_type:
                    copy = make_iconstant(TREE_LOCATION(t), TREE_TYPE(t), GET_CONSTANT(t).value.ll);
                    break;
                case Unsigned_type:
                case Uchar_type:
                case Uint_type:
                case Ulong_type:
                case Ulonglong_type:
                case Ushort_type:
                case Pointer_type:
                    // why not make_uiconstant ??
                    copy = make_iconstant(TREE_LOCATION(t), TREE_TYPE(t), GET_CONSTANT(t).value.ull);
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
    TreeNode* a2;
    int v1;

    if ((TREE_ATTRIBUTE(t) & PLAIN_ATTRIBUTE) && !(IS_STD_TREE(t))) {
        v1 = TRUE;
    } else {
        v1 = FALSE;
    }

    if (TREE_ATTRIBUTE(t) & (VOL_ATTRIBUTE | CONST_ATTRIBUTE | TYPE_ATTRIBUTE | UNALIGNED_ATTRIBUTE)) {
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
    
    if (v1) {
        TreeNode* v0;
        
        for (v0 = t, a2 = t; v0 != NULL; v0 = TREE_TYPE(v0)) {
            if (IS_STD_TREE(v0)) {
                break;
            }
            a2 = v0;
        }
        TREE_ATTRIBUTE(a2) |= PLAIN_ATTRIBUTE;
    }

    return t;
}

TreeNode* make(int code, int location, ...) {
    TreeNode* t;
    va_list args;
    int num_args;
    TreeNode* arg;
    TreeNode* t3;

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
            COMPOUND_STMT(t).context = va_arg(args, TreeNode*);
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
            WHILE_STMT(t).breaklab = va_arg(args, int);
            break;
        case Dowhile_stmt:
            t = mem_alloc(tree_handle, sizeof(TreeNode_Dowhile_stmt), 4);
            DOWHILE_STMT(t).expr = va_arg(args, TreeNode*);
            DOWHILE_STMT(t).stmt = va_arg(args, TreeNode*);
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
            num_args = 0;
            t = va_arg(args, TreeNode*);
            for (arg = t; arg != NULL; arg = TREE_LINK(arg)) {
                num_args++;
            }

            t = mem_alloc(tree_handle, sizeof(TreeNode_Aggregate_expr) + 4 * num_args, 4);
            // TODOOOOOO
            break;
        case Constant:
            t3 = va_arg(args, TreeNode*);
            switch (TREE_CODE(t3)) {
                case Char_type:
                case Int_type:
                case Long_type:
                case Longlong_type:
                case Short_type:
                case Signed_type:
                    if (D_1001D474 == 0) {
                        __assert("FALSE", "tree.c", 0x75A);
                    }
                    D_1001D474 = 0;

                    t = mem_alloc(tree_handle, sizeof(TreeNode_Constant), 4);
                    GET_CONSTANT(t).value.ll = va_arg(args, long long);
                    break;
                case Enum_type:
                    t3 = uint_type;
                    /* fallthrough */
                case Unsigned_type:
                case Uchar_type:
                case Uint_type:
                case Ulong_type:
                case Ulonglong_type:
                case Ushort_type:
                case Pointer_type:
                    if (D_1001D474 == 0) {
                        __assert("FALSE", "tree.c", 0x76C);
                    }
                    D_1001D474 = 0;

                    t = mem_alloc(tree_handle, sizeof(TreeNode_Constant), 4);
                    GET_CONSTANT(t).value.ull = va_arg(args, unsigned long long);
                    break;
                case Double_type:
                case Longdouble_type:
                case Float_type:
                    t = mem_alloc(tree_handle, sizeof(TreeNode_Constant), 4);
                    GET_CONSTANT(t).value.flt = va_arg(args, float);
                    break;
                case Label_type:
                case Void_type:
                case Any_type:
                    __assert("FALSE", "tree.c", 0x785);
                    break;
                case Array_type:
                    // TODODODOOOO
                    break;
                default:
                    __assert("FALSE", "tree.c", 0x796);
                    break;
            }
            break;
    }

    t->id = ++D_1001D470;
    TREE_CODE(t) = code;
    TREE_LOCATION(t) = location;
}

void init_trees(void) {
    tree_handle = general_handle;
}