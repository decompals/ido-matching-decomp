#ifndef TREE_H
#define TREE_H

#define PLAIN_ATTRIBUTE 0x00000010
#define UNALIGNED_ATTRIBUTE 0x00000080
#define VOL_ATTRIBUTE 0x80000000
#define CONST_ATTRIBUTE 0x40000000
#define TYPE_ATTRIBUTE 0x10000000

#define TREE_ID(t) (t == NULL ? 0 : ((TreeNode*)t)->id)
#define TREE_CODE(t) (((TreeNode*)t)->code)
#define TREE_TYPE(t) (((TreeNode*)t)->type)
#define TREE_ATTRIBUTE(t) (((TreeNode*)t)->attr)
#define TREE_LINK(t) (((TreeNode*)t)->link)
#define TREE_LOCATION(t) (((TreeNode*)t)->location)

#define BASIC_TYPE(t) (*((TreeNode_Basic_type*)t))
#define ARRAY_TYPE(t) (*((TreeNode_Array_type*)t))
#define STRUCT_TYPE(t) (*((TreeNode_Struct_type*)t))
#define ENUM_TYPE(t) (*((TreeNode_Enum_type*)t))
#define FUNC_TYPE(t) (*((TreeNode_Func_type*)t))
#define REFERENCE_TYPE(t) (*((TreeNode_Reference_type*)t))
#define POINTER_TYPE(t) (*((TreeNode_Pointer_type*)t))
#define FIELD_DECL(t) (*((TreeNode_Field_decl*)t))
#define ID_DECL(t) (*((TreeNode_Id_decl*)t))
#define DECLARE_DECL(t) (*((TreeNode_Declare_decl*)t))
#define IF_STMT(t) (*((TreeNode_If_stmt*)t))
#define INIT(t) (*((TreeNode_Init*)t))
#define LABELED_STMT(t) (*((TreeNode_Labeled_stmt*)t))
#define COMPOUND_STMT(t) (*((TreeNode_Compound_stmt*)t))
#define EXPR_STMT(t) (*((TreeNode_Expr_stmt*)t))
#define WHILE_STMT(t) (*((TreeNode_While_stmt*)t))
#define SWITCH_STMT(t) (*((TreeNode_Switch_stmt*)t))
#define DOWHILE_STMT(t) (*((TreeNode_Dowhile_stmt*)t))
#define TRY_STMT(t) (*((TreeNode_Try_stmt*)t))
#define FOR_STMT(t) (*((TreeNode_For_stmt*)t))
#define GOTO_STMT(t) (*((TreeNode_Goto_stmt*)t))
#define RETURN_STMT(t) (*((TreeNode_Return_stmt*)t))
#define UNARY_EXPR(t) (*((TreeNode_Unary_expr*)t))
#define BINARY_EXPR(t) (*((TreeNode_Binary_expr*)t))
#define TERNARY_EXPR(t) (*((TreeNode_Ternary_expr*)t))
#define AGGREGATE_EXPR(t) (*((TreeNode_Aggregate_expr*)t))
#define GET_CONSTANT(t) (*((TreeNode_Constant*)t))
#define GET_IDENTIFIER(t) (*((TreeNode_Identifier*)t))
#define GET_PRAGMA(t) (*((TreeNode_Pragma*)t))
#define ACCESS_SPEC(t) (*((TreeNode_Access_spec*)t))

#define GET_UNKNOWN1(t) (*((TreeNode_Unknown1*)t))

#define IS_STD_TREE(t) (t == char_type || t == double_type || t == int_type || \
        t == int_type || t == float_type || t == long_type || t == longlong_type || \
        t == longdouble_type || t == short_type || t == signed_type || \
        t == unsigned_type || t == uchar_type || t == uint_type || \
        t == ulong_type || t == ulonglong_type || t == ushort_type || \
        t == label_type || t == void_type || t == any_type || \
        t == int32_type || t == uint32_type || t == int64_type || t == uint64_type)

enum TreeCodes {
    Identifier,
    Double_type,
    Longdouble_type,
    Float_type,
    Label_type,
    Char_type,
    Int_type,
    Long_type,
    Longlong_type,
    Short_type,
    Signed_type,
    Unsigned_type,
    Uchar_type,
    Uint_type,
    Ulong_type,
    Ulonglong_type,
    Ushort_type,
    Void_type,
    Any_type,
    Array_type,
    Enum_type,
    Func_type,
    Pointer_type,
    Reference_type,
    Struct_type,
    Break_stmt,
    Caselabeled_stmt,
    Compound_stmt,
    Continue_stmt,
    Defaultlabeled_stmt,
    Dowhile_stmt,
    Expr_stmt,
    For_stmt,
    Goto_stmt,
    Idlabeled_stmt,
    If_stmt,
    Init,
    Return_stmt,
    Switch_stmt,
    While_stmt,
    Try_stmt,
    Leave_stmt,
    Addr_expr,
    Alignof_expr,
    Bitcomplement_expr,
    Classof_expr,
    Indirect_expr,
    Not_expr,
    Postdecrement_expr,
    Postincrement_expr,
    Predecrement_expr,
    Preincrement_expr,
    Sizeof_expr,
    Uminus_expr,
    Uplus_expr,
    Delete_expr,
    Addrrel_expr,
    And_expr,
    Assign_expr,
    Bitand_expr,
    Bitor_expr,
    Bitxor_expr,
    Bitand_assign_expr,
    Bitor_assign_expr,
    Bitxor_assign_expr,
    Call_expr,
    Cast_expr,
    Comma_expr,
    Div_expr,
    Div_assign_expr,
    Eq_expr,
    Gt_expr,
    Geq_expr,
    Index_expr,
    Leq_expr,
    Lshift_expr,
    Lshift_assign_expr,
    Lt_expr,
    Minus_expr,
    Minus_assign_expr,
    Rem_expr,
    Rem_assign_expr,
    Mult_expr,
    Mult_assign_expr,
    Neq_expr,
    Or_expr,
    Plus_expr,
    Plus_assign_expr,
    Rshift_expr,
    Rshift_assign_expr,
    New_expr,
    Member_init_expr,
    Conditional_expr,
    Aggregate_expr,
    Array_ref,
    Component_ref,
    Indirect_component_ref,
    Qualified_ref,
    Declare_decl,
    Id_decl,
    Field_decl,
    Constant,
    End_of_file,
    Nop,
    Constant_special,
    Error_mark,
    Pragma,
    Access_spec,
    Reserved
};

struct AttrDesc {
    int value;
    char* desc;
};

typedef struct TreeNode {
    int id;
    int code;
    struct TreeNode* type;
    int attr;
    struct TreeNode* link;
    int location;
} TreeNode;

typedef struct TreeNode_Basic_type {
    TreeNode t;
    int size;
    unsigned int align;
} TreeNode_Basic_type;

typedef struct TreeNode_Array_type {
    TreeNode t;
    int size;
    int align;
    TreeNode* index_type;
} TreeNode_Array_type;

typedef struct TreeNode_Struct_type {
    TreeNode t;
    int size;
    int align;
    TreeNode* sname;
    TreeNode* members;
    int info;
    TreeNode* baselist;
} TreeNode_Struct_type;

typedef struct TreeNode_Enum_type {
    TreeNode t;
    int size;
    int align;
    TreeNode* ename;
    TreeNode* literals;
    int lb;
    int ub;
} TreeNode_Enum_type;

typedef struct TreeNode_Func_type {
    TreeNode t;
    int size;
    int align;
    TreeNode* fname;
    TreeNode* params;
    TreeNode* decls;
    int psize;
    int end_blkno;
    TreeNode* handlers;
} TreeNode_Func_type;

typedef struct TreeNode_Reference_type {
    TreeNode t;
    int size;
    int align;
    TreeNode* base_type;
} TreeNode_Reference_type;

typedef struct TreeNode_Pointer_type {
    TreeNode t;
    int size;
    int align;
    TreeNode* base_type;
} TreeNode_Pointer_type;

typedef struct TreeNode_Field_decl {
    TreeNode t;
    TreeNode* field;
    int width;
} TreeNode_Field_decl;

typedef struct TreeNode_Id_decl {
    TreeNode t;
    Symbol* id;
    TreeNode* init_value;
    TreeNode* qualifiers;
    int offset;
    unsigned short level;
    unsigned short alevel;
    int sclass;
    TreeNode* hidden;
    TreeNode* st_list;
    TreeNode* context;
    int blkno;
    short flags;
    TreeNode* overloads;
    int oclass;
    int lastused;
} TreeNode_Id_decl;

typedef struct TreeNode_Declare_decl {
    TreeNode t;
    TreeNode* ids;
} TreeNode_Declare_decl;

typedef struct TreeNode_If_stmt {
    TreeNode t;
    TreeNode* expr;
    TreeNode* then_part;
    TreeNode* else_part;
} TreeNode_If_stmt;

typedef struct TreeNode_Init {
    TreeNode t;
    TreeNode* value;
    int replicate;
    short ExtendedSize;
    int start_offset;
} TreeNode_Init;

typedef struct TreeNode_Labeled_stmt {
    TreeNode t;
    TreeNode* id;
    TreeNode* expr;
    TreeNode* stmt;
    int label;
} TreeNode_Labeled_stmt;

typedef struct TreeNode_Compound_stmt {
    TreeNode t;
    TreeNode* decls;
    TreeNode* stmts;
    TreeNode* context;
    int end_location;
    int cg_info;
} TreeNode_Compound_stmt;

typedef struct TreeNode_Expr_stmt {
    TreeNode t;
    TreeNode* expr;
} TreeNode_Expr_stmt;

typedef struct TreeNode_While_stmt {
    TreeNode t;
    TreeNode* expr;
    TreeNode* stmt;
    int breaklab;
    int contlab;
    int cases;
} TreeNode_While_stmt;

typedef struct TreeNode_Switch_stmt {
    TreeNode t;
    TreeNode* expr;
    TreeNode* stmt;
    int breaklab;
    int contlab;
    int cases;
} TreeNode_Switch_stmt;

typedef struct TreeNode_Dowhile_stmt {
    TreeNode t;
    TreeNode* stmt;
    TreeNode* expr;
    int breaklab;
    int contlab;
} TreeNode_Dowhile_stmt;

typedef struct TreeNode_Try_stmt {
    TreeNode t;
    TreeNode* expr;
    TreeNode* guard;
    TreeNode* handler;
    TreeNode* begin_addr;
    TreeNode* end_addr;
    int label;
    int jmp_target;
} TreeNode_Try_stmt;

typedef struct TreeNode_For_stmt {
    TreeNode t;
    TreeNode* expr1;
    TreeNode* expr2;
    TreeNode* expr3;
    TreeNode* stmt;
    int breaklab;
    int contlab;
} TreeNode_For_stmt;

typedef struct TreeNode_Goto_stmt {
    TreeNode t;
    TreeNode* id;
} TreeNode_Goto_stmt;

typedef struct TreeNode_Return_stmt {
    TreeNode t;
    TreeNode* expr;
} TreeNode_Return_stmt;

typedef struct TreeNode_Unary_expr {
    TreeNode t;
    TreeNode* operand[1];
} TreeNode_Unary_expr;

typedef struct TreeNode_Binary_expr {
    TreeNode t;
    TreeNode* operand[2];
} TreeNode_Binary_expr;

typedef struct TreeNode_Ternary_expr {
    TreeNode t;
    TreeNode* operand[3];
} TreeNode_Ternary_expr;

typedef struct TreeNode_Aggregate_expr {
    TreeNode t;
    TreeNode* operand[1]; // variable size
} TreeNode_Aggregate_expr;

typedef struct TreeNode_Constant {
    TreeNode t;
    union {
        long long ll;
        unsigned long long ull;
        Symbol* real;
        float flt;
        double dbl;
        char str[1];
        int array[1];
    } value;
} TreeNode_Constant;

typedef struct TreeNode_Identifier {
    TreeNode t;
    Symbol* id;
} TreeNode_Identifier;

typedef struct TreeNode_Pragma {
    TreeNode t;
    int pragma_type;
    TreeNode* argument;
} TreeNode_Pragma;

typedef struct TreeNode_Access_spec {
    TreeNode t;
    TreeNode* access;
} TreeNode_Access_spec;

typedef struct TreeNode_Unknown1 {
    TreeNode t;
    long long size;
} TreeNode_Unknown1;

TreeNode* make(int code, int location, ...);
TreeNode* make_uiconstant(int, TreeNode*, unsigned long long);
TreeNode* make_iconstant(int, TreeNode*, long long);

#endif
