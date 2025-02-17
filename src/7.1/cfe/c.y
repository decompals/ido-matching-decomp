%{
#include "common.h"
char* ident = "$Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/targucode/cfe/RCS/c.y,v 1.17 1995/02/27 21:57:39 rdahl Exp $";

#define YYMAXDEPTH 800

typedef struct UnkBeta {
    LinkedListEntry link;
    Symbol* unk_04;
} UnkBeta;

static LinkedList* B_10020F00;
static int B_10020F04;
static LinkedList* B_10020F08;
static TreeNodeList B_10020F10;

int yyparse(void);

#define LINK_PUSH_BACK(list, item) \
{ \
	TreeNode* ptr; \
	TreeNode* prev; \
	for (ptr = list, prev = list; ptr != NULL; ptr = TREE_LINK(ptr)) { \
		prev = ptr; \
	} \
	TREE_LINK(prev) = item; \
}

#define TYPE_PUSH_BACK(list, item) \
{ \
	TreeNode* ptr; \
	TreeNode* prev; \
	for (ptr = list, prev = list; ptr != NULL; ptr = TREE_TYPE(ptr)) { \
		prev = ptr; \
	} \
	TREE_TYPE(prev) = item; \
}

#define QUALIFIERS_PUSH_BACK(id_decl, qual) \
{ \
	TreeNode* ptr; \
	TreeNode* prev; \
	for (prev = ptr = ID_DECL(id_decl).qualifiers; ptr != NULL; ptr = TREE_TYPE(ptr)) { \
		prev = ptr; \
	} \
	if (prev == NULL) { \
		ID_DECL(id_decl).qualifiers = qual; \
	} else { \
		TREE_TYPE(prev) = qual; \
	} \
}

// TODO remove error() from yaccpar and probably replace ti with macro

void parse_init(void) {
    if (B_10020F00 == NULL) {
        B_10020F00 = link_start(general_handle, sizeof(UnkChi));
    } else {
        free_link_list(B_10020F00);
    }

    if (B_10020F08 == NULL) {
        B_10020F08 = link_start(general_handle, sizeof(UnkBeta));
    }

    cur_lvl = (UnkChi*)get_link_elem(B_10020F00);
    cur_lvl->unk_04 = 1;
    cur_lvl->unk_08 = 1;
    cur_lvl->unk_0C = FALSE;
    cur_lvl->in_struct_def = FALSE;
    cur_lvl->link.next = B_10020F00->used_list;
    B_10020F00->used_list = &cur_lvl->link;

    B_10020F04 = 0;
    tree_handle = general_handle;    
}

TreeNode* parse(void) {
    temp_handle = mem_start();
    B_10020F10.first = NULL;
    B_10020F10.last = NULL;
    parse_init();
    if (yyparse() != 0) {
        return NULL;
    } else {
        return B_10020F10.first;
    }
}

void delete_local_decls(int level) {
    UnkBeta* s2 = (UnkBeta*)B_10020F08->used_list;
    ParseSymbol* s1;

    while (s2 != NULL) {
        if (s2 == NULL) {
            return;
        }
        s1 = s2->unk_04->psymb;
        
        if (s1 == NULL) {
            link_pop(B_10020F08);
            return;
        }
        if (s1->level < level) {
            return;
        }

        while (s1 != NULL && s1->level >= level) {
            ParseSymbol* s0 = (ParseSymbol*)s1->link.next;
            if (debug_arr[80] > 0) {
                fprintf(dbgout, "deleting %.*s (0x%x:%d:%s) unhides (0x%x:%d:%s)\n",
                        s2->unk_04->namelen, s2->unk_04->name,
                        s1, s1->level, GET_SYM_CAT(s1->id),
                        s0, s0 != NULL ? s0->level : -1, s0 != NULL ? GET_SYM_CAT(s0->id) : "<nil>");
            }

            s1->link.next = psymb_handle->free_list;
            psymb_handle->free_list = &s1->link;
            s1 = s0;
            s2->unk_04->psymb = s0;
        }
        s2 = link_pop(B_10020F08);
    }
}

TreeNode* make_topdecl(TreeNode* type, int attr, int typespec, TreeNode* ids, int location) {
    TreeNode* v1;
    
    v1 = make(Declare_decl, location, NULL, ids);
	TREE_ATTRIBUTE(v1) = attr;
    if (type != NULL) {
		TREE_TYPE(v1) = type;
        if (typespec != 0) {
            error(0x2010F, LEVEL_WARNING, location);
        }
        return v1;
    } else {
        TREE_TYPE(v1) = normalize_type(typespec, location);
        if (was_plain_char(typespec)) {
            TREE_ATTRIBUTE(v1) |= PLAIN_ATTRIBUTE;
        }
        return v1;
    }
}

static void* func_00409D18(int code, int location, TreeNode* arg2) {
	// TODO type of arg2
    TreeNode* zeta;
    TreeNode* v0;    
    
    if (!options[OPTION_MSFT]) {
        error(0x3015A, LEVEL_WARNING, location);
    }
    
    if (arg2 == NULL || BINARY_EXPR(arg2).operand[0] == NULL) {
        return NULL;
    }

    zeta = BINARY_EXPR(BINARY_EXPR(arg2).operand[0]).operand[0];
    v0 = make(Pointer_type, location, zeta, arg2);
    POINTER_TYPE(v0).size = bit_size[9];
    POINTER_TYPE(v0).align = bit_size[9];


    if (zeta == NULL) {
		BINARY_EXPR(BINARY_EXPR(arg2).operand[0]).operand[0] = v0;
    } else {
        TreeNode* ptr = zeta;
        TreeNode* a0 = ptr;
        
        while (ptr != NULL) {
            a0 = ptr;
            ptr = TREE_TYPE(ptr);
        }
        TREE_TYPE(a0) = v0;
    }
    return make(code, location, make(Indirect_expr, location, arg2));
}

%}

%union {
	int location;
	TreeNode* node; 
	struct TokenIdentifier identifier;
	struct DeclSpec declspec;
	struct Declarator declarator;
	struct TreeNodeList list;
}

%token	<identifier>	IDENTIFIER
%token	<location>		SIZEOF ALIGNOF CLASSOF UNALIGN
%token	<node>			STRING WSTRING CONSTANT
%token	<location>		PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP AND_OP OR_OP GE_OP NE_OP EQ_OP
						MUL_ASSIGN DIV_ASSIGN REM_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
						TYPEDEF EXTERN STATIC AUTO REGISTER
						CHAR SHORT INT LONG LONGLONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
						STRUCT UNION ENUM
						ELLIPSIS
%token	<identifier>	TYPE_IDENT
%token	<location>		CASE DEFAULT IF ELSE SWITCH WHILE DO FOR
						GOTO LEAVE CONTINUE BREAK RETURN
						TRY EXCEPT FINALLY
						__PRAGMA
%token	<location>		'(' ')' '{' '}' '[' ']' '?' ':' '~' ',' ';'
%left	<location>		'+' '-'
%left	<location>		'/' '%'
%left  	<location>		'&' '|'
%token	<location>		'^' '!' '=' '*' '.' '<' '>'
						CLASS VIRTUAL PROTECTED PUBLIC PRIVATE COLONCOLON COLCOLSTAR OPERATOR THIS MEMDOT_OP MEMPTR_OP NEW DELETE INLINE FRIEND

%type <node> identifier
%type <node> constant
%type <node> string_literal
%type <node> labeled_statement
%type <node> selection_statement
%type <node> expression_statement
%type <node> jump_statement
%type <node> compound_statement
%type <node> iteration_statement
%type <node> try_statement
%type <node> translation_unit
%type <node> primary_expression
%type <node> postfix_expression
%type <node> argument_expression_list
%type <node> unary_expression
%type <node> unary_operator
%type <node> cast_expression
%type <node> multiplicative_expression
%type <node> additive_expression
%type <node> shift_expression
%type <node> relational_expression
%type <node> equality_expression
%type <node> AND_expression
%type <node> exclusive_OR_expression
%type <node> inclusive_OR_expression
%type <node> logical_AND_expression
%type <node> logical_OR_expression
%type <node> conditional_expression
%type <node> assignment_expression
%type <node> assignment_operator
%type <node> expression
%type <node> constant_expression
%type <node> declaration
%type <node> top_declaration
%type <declspec> declaration_specifiers
%type <list> init_declarator_list
%type <node> init_declarator
%type <declspec> storage_class_specifier
%type <declspec> fct_specifier
%type <declspec> type_specifier
%type <node> struct_or_union_specifier
%type <node> struct_or_union
%type <node> struct_declaration_list_semi
%type <node> struct_declaration_list
%type <node> struct_declaration
%type <declspec> specifier_qualifier_list
%type <node> struct_declarator_list
%type <node> struct_declarator
%type <node> enum
%type <node> enum_specifier
%type <list> enumerator_list
%type <node> enumerator
%type <declspec> type_qualifier
%type <declarator> declarator
%type <declarator> direct_declarator
%type <node> pointer
%type <declspec> type_qualifier_list
%type <list> identifier_list
%type <list> identifier_or_constant_list
%type <list> parameter_type_list
%type <list> parameter_list
%type <node> parameter_declaration
%type <node> type_name
%type <node> abstract_declarator
%type <node> direct_abstract_declarator
%type <node> initializer
%type <list> initializer_list
%type <node> statement
%type <list> declaration_list
%type <list> statement_list
%type <node> external_definition
%type <node> function_definition
%type <node> function_body
%type <location> optcomma
%type <node> build_program_tree
%type <identifier> typedef_name
%type <location> fdecl_start
%type <location> comp_start

%start build_program_tree
%%

identifier
	: IDENTIFIER {
		if (debug_arr['y'] > 0) {
			fprintf(dbgout, "IDENT=%s, was_typedef=%d\n", $1.symbol->name, $1.was_typedef);
		}
		$$ = make(Identifier, $1.location, $1.symbol);
	}
	;

string_literal
	: STRING
	;

constant
	: CONSTANT
	;

primary_expression
	: identifier
	| string_literal
	| constant
	| '(' expression ')' { $$ = $2; }
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']' { $$ = make(Index_expr, $2, $1, $3); }
	| postfix_expression '(' argument_expression_list ')'
		{ 
			TreeNode* sp108 = make(Aggregate_expr, TREE_LOCATION($3), $3);
			$$ = make(Call_expr, $2, $1, sp108);
		}
	| postfix_expression '(' ')' { $$ = make(Call_expr, $2, $1, NULL); }
	| postfix_expression '.' { cur_lvl->unk_04 = 0; } identifier
		{ 
			$$ = make(Component_ref, $2, $1, $4);
			cur_lvl->unk_04 = 1;
		}
	| postfix_expression PTR_OP { cur_lvl->unk_04 = 0; } identifier
		{
			$$ = make(Indirect_component_ref, $2, $1, $4);
			cur_lvl->unk_04 = 1;
		}
	| postfix_expression INC_OP { $$ = make(Postincrement_expr, $2, $1); }
	| postfix_expression DEC_OP { $$ = make(Postdecrement_expr, $2, $1); }
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
		{
			LINK_PUSH_BACK($$, $3);
		}
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression { $$ = make(Preincrement_expr, $1, $2); }
	| DEC_OP unary_expression { $$ = make(Predecrement_expr, $1, $2); }
	| unary_operator cast_expression { UNARY_EXPR($$).operand[0] = $2; }
	| '&' ELLIPSIS
		{
			TreeNode* spFC = make(Identifier, $2, builtins[6]);
			$$ = make(Addr_expr, $1, spFC);
			if (IS_STRICT_ANSI) {
				error(0x2012D, LEVEL_WARNING, $2);
			}
		}
	| SIZEOF unary_expression { $$ = make(Sizeof_expr, $1, $2); }
	| SIZEOF '(' type_name { cur_lvl->unk_04 = 1; } ')' { $$ = make(Sizeof_expr, $1, $3); }
	| ALIGNOF unary_expression { $$ = make(Alignof_expr, $1, $2); }
	| ALIGNOF '(' type_name { cur_lvl->unk_04 = 1; } ')' { $$ = make(Alignof_expr, $1, $3); }
	| CLASSOF unary_expression { $$ = make(Classof_expr, $1, $2); }
	| CLASSOF '(' type_name { cur_lvl->unk_04 = 1; } ')' { $$ = make(Classof_expr, $1, $3); }
	;

unary_operator
	: '&' { $$ = make(Addr_expr, $1, NULL); }
	| '*' { $$ = make(Indirect_expr, $1, NULL); }
	| '+' { $$ = make(Uplus_expr, $1, NULL); }
	| '-' { $$ = make(Uminus_expr, $1, NULL); }
	| '~' { $$ = make(Bitcomplement_expr, $1, NULL); }
	| '!' { $$ = make(Not_expr, $1, NULL); }
	;

cast_expression
	: unary_expression
	| '(' type_name { cur_lvl->unk_04 = 1; } ')' cast_expression { $$ = make(Cast_expr, $1, $2, $5); }
	| DEC_OP '(' type_name { cur_lvl->unk_04 = 1; } ')' cast_expression
		{
			TreeNode* spF8 = make(Cast_expr, $2, $3, $6);
			$$ = func_00409D18(Predecrement_expr, $1, spF8);
		}
	| INC_OP '(' type_name { cur_lvl->unk_04 = 1; } ')' cast_expression
		{
			TreeNode* spF4 = make(Cast_expr, $2, $3, $6);
			$$ = func_00409D18(Preincrement_expr, $1, spF4);
		}
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression { $$ = make(Mult_expr, $2, $1, $3); }
	| multiplicative_expression '/' cast_expression { $$ = make(Div_expr, $2, $1, $3); }
	| multiplicative_expression '%' cast_expression { $$ = make(Rem_expr, $2, $1, $3); }
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression { $$ = make(Plus_expr, $2, $1, $3); }
	| additive_expression '-' multiplicative_expression { $$ = make(Minus_expr, $2, $1, $3); }
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression { $$ = make(Lshift_expr, $2, $1, $3); }
	| shift_expression RIGHT_OP additive_expression { $$ = make(Rshift_expr, $2, $1, $3); }
	;

relational_expression
	: shift_expression
	| relational_expression LE_OP shift_expression { $$ = make(Leq_expr, $2, $1, $3); }
	| relational_expression GE_OP shift_expression { $$ = make(Geq_expr, $2, $1, $3); }
	| relational_expression '<' shift_expression { $$ = make(Lt_expr, $2, $1, $3); }
	| relational_expression '>' shift_expression { $$ = make(Gt_expr, $2, $1, $3); }
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression { $$ = make(Eq_expr, $2, $1, $3); }
	| equality_expression NE_OP relational_expression { $$ = make(Neq_expr, $2, $1, $3); }
	;

AND_expression
	: equality_expression
	| AND_expression '&' equality_expression { $$ = make(Bitand_expr, $2, $1, $3); }
	;

exclusive_OR_expression
	: AND_expression
	| exclusive_OR_expression '^' AND_expression { $$ = make(Bitxor_expr, $2, $1, $3); }
	;

inclusive_OR_expression
	: exclusive_OR_expression
	| inclusive_OR_expression '|' exclusive_OR_expression { $$ = make(Bitor_expr, $2, $1, $3); }
	;

logical_AND_expression
	: inclusive_OR_expression
	| logical_AND_expression AND_OP inclusive_OR_expression { $$ = make(And_expr, $2, $1, $3); }
	;

logical_OR_expression
	: logical_AND_expression
	| logical_OR_expression OR_OP logical_AND_expression { $$ = make(Or_expr, $2, $1, $3); }
	;

conditional_expression
	: logical_OR_expression
	| logical_OR_expression '?' expression ':' conditional_expression { $$ = make(Conditional_expr, $2, $1, $3, $5); }
	;

assignment_expression
	: conditional_expression
	| cast_expression assignment_operator assignment_expression
		{
			BINARY_EXPR($2).operand[0] = $1;
			BINARY_EXPR($2).operand[1] = $3;
			$$ = $2;
		}
	;

assignment_operator
	: '=' { $$ = make(Assign_expr, $1, NULL, NULL); }
	| MUL_ASSIGN { $$ = make(Mult_assign_expr, $1, NULL, NULL); }
	| DIV_ASSIGN { $$ = make(Div_assign_expr, $1, NULL, NULL); }
	| REM_ASSIGN { $$ = make(Rem_assign_expr, $1, NULL, NULL); }
	| ADD_ASSIGN { $$ = make(Plus_assign_expr, $1, NULL, NULL); }
	| SUB_ASSIGN { $$ = make(Minus_assign_expr, $1, NULL, NULL); }
	| LEFT_ASSIGN { $$ = make(Lshift_assign_expr, $1, NULL, NULL); }
	| RIGHT_ASSIGN { $$ = make(Rshift_assign_expr, $1, NULL, NULL); }
	| AND_ASSIGN { $$ = make(Bitand_assign_expr, $1, NULL, NULL); }
	| XOR_ASSIGN { $$ = make(Bitxor_assign_expr, $1, NULL, NULL); }
	| OR_ASSIGN { $$ = make(Bitor_assign_expr, $1, NULL, NULL); }
	;

expression
	: assignment_expression
	| expression ',' assignment_expression { $$ = make(Comma_expr, $2, $1, $3); }
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers init_declarator_list ';'
		{
			if (B_10020F04 == 0) {
                error(0x2007B, LEVEL_ERROR, curloc);
            }
			$$ = make_topdecl($1.unk_00, $1.unk_04, $1.unk_08, $2.first, $1.unk_0C);
			cur_lvl->unk_04 = 1;
			cur_lvl->unk_08 = 1;
		}
	| declaration_specifiers ';'
		{
			if (B_10020F04 == 0) {
                error(0x2007B, LEVEL_ERROR, curloc);
            }
			$$ = make_topdecl($1.unk_00, $1.unk_04, $1.unk_08, NULL, $1.unk_0C);
			cur_lvl->unk_04 = 1;
			cur_lvl->unk_08 = 1;
		}
	;

top_declaration
	: declaration_specifiers init_declarator_list ';' 
		{
			$$ = make_topdecl($1.unk_00, $1.unk_04, $1.unk_08, $2.first, $1.unk_0C);
			cur_lvl->unk_04 = 1;
			cur_lvl->unk_08 = 1;
		}
	| declaration_specifiers ';' 
		{
			$$ = make_topdecl($1.unk_00, $1.unk_04, $1.unk_08, NULL, $1.unk_0C);
			cur_lvl->unk_04 = 1;
			cur_lvl->unk_08 = 1;
		}
	| init_declarator_list ';'
		{
			$$ = make_topdecl(NULL, 0, 0, $1.first, TREE_LOCATION($1.first));
			error(0x20092, LEVEL_DEFAULT, TREE_LOCATION($1.first));
		}
	;

declaration_specifiers
	: storage_class_specifier
	| type_specifier
	| type_qualifier
	| declaration_specifiers storage_class_specifier
		{
			if (($$.unk_04 & 0x1F000000) && ($2.unk_04 & 0x1F000000)) {
				error(0x20103, LEVEL_WARNING, $2.unk_0C, attribute_to_string($2.unk_04));
			} else if ($$.unk_04 & $2.unk_04) {
				error(0x20094, LEVEL_WARNING, $2.unk_0C, attribute_to_string($2.unk_04));
			} else {
				$$.unk_04 |= $2.unk_04;
				$$.unk_0C = $2.unk_0C;
			}
		}
	| declaration_specifiers type_specifier
		{
			if ($$.unk_00 != NULL) {
				error(0x20162, LEVEL_WARNING, TREE_LOCATION($$.unk_00));
			}
			if ($2.unk_00 != NULL) {
				$$.unk_00 = $2.unk_00;
			} else if ($$.unk_08 & $2.unk_08) {
				if ($2.unk_08 == 0x01000000) {
					if (IS_STRICT_ANSI) {
						error(0x20131, LEVEL_WARNING, $2.unk_0C, "long long");
					}
					$$.unk_08 = $$.unk_08 ^ $2.unk_08;
					$$.unk_08 |= 0x800000;
				} else {
					error(0x20094, LEVEL_WARNING, $2.unk_0C, type_to_string($2.unk_08));
				}
			} else {
				$$.unk_08 |= $2.unk_08;
			}
		}
	| declaration_specifiers type_qualifier
		{
			if (($$.unk_04 & 0x1F000000) && ($2.unk_04 & 0x1F000000)) {
				error(0x20103, LEVEL_WARNING, $2.unk_0C, attribute_to_string($2.unk_04));
			} else if ($$.unk_04 & $2.unk_04) {
				error(0x20094, LEVEL_WARNING, $2.unk_0C, attribute_to_string($2.unk_04));
			} else {
				$$.unk_04 |= $2.unk_04;
				$$.unk_0C = $2.unk_0C;
			}
		}
	| fct_specifier
	| declaration_specifiers fct_specifier
		{
			if (($$.unk_04 & 0x1F000000) && ($2.unk_04 & 0x1F000000)) {
				error(0x20103, LEVEL_WARNING, $2.unk_0C, attribute_to_string($2.unk_04));
			} else if ($$.unk_04 & $2.unk_04) {
				error(0x20094, LEVEL_WARNING, $2.unk_0C, attribute_to_string($2.unk_04));
			} else {
				$$.unk_04 |= $2.unk_04;
				$$.unk_0C = $2.unk_0C;
			}
		}
	;

fct_specifier
	: INLINE
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0x80000;
			$$.unk_08 = 0;
			$$.unk_0C = $1;
		}

init_declarator_list
	: init_declarator
		{
			$$.first = $$.last = $1;
		}
	| init_declarator_list ',' { cur_lvl->unk_04 = 0; } init_declarator
		{
			if ($$.first == NULL) {
				$$.first = $$.last = $4;
			} else if ($4 != NULL) {
				$$.last = TREE_LINK($$.last) = $4;
			}
		}
	;

init_declarator
	: declarator
		{
			if ($1.unk_00) {
				delete_local_decls(B_10020F04);
                cur_lvl = link_pop(B_10020F00);
                B_10020F04--;
			}
			$$ = $1.unk_04;
		} 
	| declarator '=' initializer
		{
			if ($1.unk_00) {
				delete_local_decls(B_10020F04);
                cur_lvl = link_pop(B_10020F00);
                B_10020F04--;
			}
			ID_DECL($1.unk_04).init_value = $3;
			$$ = $1.unk_04;
		}
	;

storage_class_specifier
	: TYPEDEF
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0x10000000;
			$$.unk_08 = 0;
			$$.unk_0C = $1;
			cur_lvl->unk_08 = 0;
		}
	| EXTERN 
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0x08000000;
			$$.unk_08 = 0;
			$$.unk_0C = $1;
		}
	| STATIC
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0x04000000;
			$$.unk_08 = 0;
			$$.unk_0C = $1;
		}
	| AUTO
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0x02000000;
			$$.unk_08 = 0;
			$$.unk_0C = $1;
		}
	| REGISTER
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0x01000000;
			$$.unk_08 = 0;
			$$.unk_0C = $1;
		}
	;

type_specifier
	: CHAR
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0;
			$$.unk_08 = 0x04000000;
			$$.unk_0C = $1;
			cur_lvl->unk_04 = 0;
		}
	| SHORT
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0;
			$$.unk_08 = 0x400000;
			$$.unk_0C = $1;
			cur_lvl->unk_04 = 0;
		}
	| INT
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0;
			$$.unk_08 = 0x02000000;
			$$.unk_0C = $1;
			cur_lvl->unk_04 = 0;
		}
	| LONG
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0;
			$$.unk_08 = 0x01000000;
			$$.unk_0C = $1;
			cur_lvl->unk_04 = 0;
		}
	| LONGLONG
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0;
			$$.unk_08 = 0x800000;
			$$.unk_0C = $1;
			cur_lvl->unk_04 = 0;
		}
	| SIGNED
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0;
			$$.unk_08 = 0x200000;
			$$.unk_0C = $1;
			cur_lvl->unk_04 = 0;
		}
	| UNSIGNED
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0;
			$$.unk_08 = 0x100000;
			$$.unk_0C = $1;
			cur_lvl->unk_04 = 0;
		}
	| FLOAT
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0;
			$$.unk_08 = 0x10000000;
			$$.unk_0C = $1;
			cur_lvl->unk_04 = 0;
		}
	| DOUBLE
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0;
			$$.unk_08 = 0x40000000;
			$$.unk_0C = $1;
			cur_lvl->unk_04 = 0;
		}
	| VOID
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0;
			$$.unk_08 = 0x4000;
			$$.unk_0C = $1;
			cur_lvl->unk_04 = 0;
		}
	| struct_or_union_specifier
		{
			$$.unk_00 = $1;
			$$.unk_04 = 0;
			$$.unk_08 = 0;
			$$.unk_0C = TREE_LOCATION($1);
			cur_lvl->unk_04 = 0;
		}
	| enum_specifier
		{
			$$.unk_00 = $1;
			$$.unk_04 = 0;
			$$.unk_08 = 0;
			$$.unk_0C = TREE_LOCATION($1);
			cur_lvl->unk_04 = 0;
		}
	| typedef_name
		{
			$$.unk_00 = make(Identifier, $1.location, $1.symbol);
			$$.unk_04 = 0;
			$$.unk_08 = 0;
			$$.unk_0C = $1.location;
		}
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{'
		{
			if (debug_arr['y'] > 0) {
				fprintf(dbgout, "IDENT=%s, was_typedef=%d\n", $2.symbol->name, $2.was_typedef);
			}
			cur_lvl = (UnkChi*)get_link_elem(B_10020F00);
			cur_lvl->unk_04 = 1;
			cur_lvl->in_struct_def = TRUE;
			cur_lvl->link.next = B_10020F00->used_list;
    		B_10020F00->used_list = &cur_lvl->link;
		}
	  struct_declaration_list_semi '}'
	  	{
			STRUCT_TYPE($$).sname = make(Id_decl, $2.location, $2.symbol);
			STRUCT_TYPE($$).members = $5;
			cur_lvl = link_pop(B_10020F00);
            if (B_10020F04 == 0) {
                tree_handle = cur_lvl->unk_14;
            }
		}
	| struct_or_union '{'
		{
			cur_lvl = (UnkChi*)get_link_elem(B_10020F00);
			cur_lvl->unk_04 = 1;
			cur_lvl->in_struct_def = TRUE;
			cur_lvl->link.next = B_10020F00->used_list;
    		B_10020F00->used_list = &cur_lvl->link;
		}
	  struct_declaration_list_semi '}'
	  	{
			STRUCT_TYPE($$).members = $4;
			cur_lvl = link_pop(B_10020F00);
            if (B_10020F04 == 0) {
                tree_handle = cur_lvl->unk_14;
            }
		}
	| struct_or_union IDENTIFIER
		{
			if (debug_arr['y'] > 0) {
				fprintf(dbgout, "IDENT=%s, was_typedef=%d\n", $2.symbol->name, $2.was_typedef);
			}
			STRUCT_TYPE($$).sname = make(Id_decl, $2.location, $2.symbol);
			cur_lvl->unk_04 = 1;
			if (B_10020F04 == 0) {
                tree_handle = cur_lvl->unk_14;
            }
		}
	;

struct_or_union
	: STRUCT
		{
			if (B_10020F04 == 0) {
                cur_lvl->unk_14 = tree_handle;
                tree_handle = general_handle;
            }
            $$ = make(Struct_type, $1, STRUCT_INFO_STRUCT);
            cur_lvl->unk_04 = 0;
		}
	| UNION
		{
			if (B_10020F04 == 0) {
                cur_lvl->unk_14 = tree_handle;
                tree_handle = general_handle;
            }
            $$ = make(Struct_type, $1, STRUCT_INFO_UNION);
            cur_lvl->unk_04 = 0;
		}
	;

struct_declaration_list_semi
	: struct_declaration_list { error(0x20097, LEVEL_DEFAULT, curloc); } 
	| struct_declaration_list ';'
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list ';' struct_declaration
		{
			LINK_PUSH_BACK($$, $3);
		}
	;

struct_declaration
	: specifier_qualifier_list { cur_lvl->unk_04 = 0; } struct_declarator_list
		{
			cur_lvl->unk_04 = 1;
			$$ = make_topdecl($1.unk_00, $1.unk_04, $1.unk_08, $3, $1.unk_0C);
		}
	;

specifier_qualifier_list
	: type_specifier
	| type_qualifier
	| specifier_qualifier_list type_specifier
		{
			if ($$.unk_00 != NULL) {
				error(0x20162, LEVEL_WARNING, TREE_LOCATION($$.unk_00));
			}
			if ($2.unk_00 != NULL) {
				$$.unk_00 = $2.unk_00;
			} else if ($$.unk_08 & $2.unk_08) {
				if ($2.unk_08 == 0x01000000) {
					if (IS_STRICT_ANSI) {
						error(0x20131, LEVEL_WARNING, $2.unk_0C, "long long");
					}
					$$.unk_08 = $$.unk_08 ^ $2.unk_08;
					$$.unk_08 |= 0x800000;
				} else {
					error(0x20094, LEVEL_WARNING, $2.unk_0C, type_to_string($2.unk_08));
				}
			} else {
				$$.unk_08 |= $2.unk_08;
			}
		}
	| specifier_qualifier_list type_qualifier
		{
			if (($$.unk_04 & 0x1F000000) && ($2.unk_04 & 0x1F000000)) {
				error(0x20103, LEVEL_WARNING, $2.unk_0C, attribute_to_string($2.unk_04));
			} else if ($$.unk_04 & $2.unk_04) {
				error(0x20094, LEVEL_WARNING, $2.unk_0C, attribute_to_string($2.unk_04));
			} else {
				$$.unk_04 |= $2.unk_04;
				$$.unk_0C = $2.unk_0C;
			}
		}
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' { cur_lvl->unk_04 = 0; } struct_declarator
		{
			LINK_PUSH_BACK($$, $4);
		}
	;

struct_declarator
	: declarator
		{
			if ($1.unk_00) {
				delete_local_decls(B_10020F04);
                cur_lvl = link_pop(B_10020F00);
                B_10020F04--;
			}
			$$ = make(Field_decl, TREE_LOCATION($1.unk_04));
			FIELD_DECL($$).field = $1.unk_04;
		}
	| ':' { cur_lvl->unk_04 = 1; } constant_expression
		{
			$$ = make(Field_decl, TREE_LOCATION($3));
			FIELD_DECL($$).field = make(Id_decl, TREE_LOCATION($3), anonymous);
			FIELD_DECL($$).width = (int)$3; /* TODO figure out type */
		}
	| declarator ':' constant_expression
		{
			if ($1.unk_00 != NULL) {
				delete_local_decls(B_10020F04);
                cur_lvl = link_pop(B_10020F00);
                B_10020F04--;
			}
			$$ = make(Field_decl, TREE_LOCATION($1.unk_04));
			FIELD_DECL($$).field = $1.unk_04;
			FIELD_DECL($$).width = (int)$3; /* TODO figure out type */
		}
	|
		{
			error(0x20098, LEVEL_DEFAULT, curloc);
			$$ = make(Field_decl, curloc);
		}
	;

enum_specifier
	: enum { cur_lvl->unk_04 = 1; } '{' enumerator_list optcomma '}'
		{
			ENUM_TYPE($$).literals = $4.first;
			if ($5 != -1) {
				error(0x2007E, LEVEL_DEFAULT, $5);
			}
			if (B_10020F04 == 0) {
                tree_handle = cur_lvl->unk_14;
            }
		}
	| enum IDENTIFIER
		{
			if (debug_arr['y'] > 0) {
				fprintf(dbgout, "IDENT=%s, was_typedef=%d\n", $2.symbol->name, $2.was_typedef);
			}
			cur_lvl->unk_04 = 1;
		}
	  '{' enumerator_list optcomma '}'
	  	{
			ENUM_TYPE($$).ename = make(Id_decl, $2.location, $2.symbol);
			ENUM_TYPE($$).literals = $5.first;
			if ($6 != -1) {
				error(0x2007E, LEVEL_DEFAULT, $6);
			}
			if (B_10020F04 == 0) {
                tree_handle = cur_lvl->unk_14;
            }
		}
	| enum IDENTIFIER
		{
			if (debug_arr['y'] > 0) {
				fprintf(dbgout, "IDENT=%s, was_typedef=%d\n", $2.symbol->name, $2.was_typedef);
			}
			ENUM_TYPE($$).ename = make(Id_decl, $2.location, $2.symbol);
			cur_lvl->unk_04 = 1;
			if (B_10020F04 == 0) {
                tree_handle = cur_lvl->unk_14;
            }
		}
	;

optcomma
	: { $$ = -1; }
	| ','
	;

enum
	: ENUM
		{
			if (B_10020F04 == 0) {
                cur_lvl->unk_14 = tree_handle;
                tree_handle = general_handle;
            }
            cur_lvl->unk_04 = 0;
            $$ = make(Enum_type, $1);
		}
	;

enumerator_list
	: enumerator { $$.first = $$.last = $1; }
	| enumerator_list ',' enumerator
		{
			if ($$.first == NULL) {
				$$.first = $$.last = $3;
			} else if ($3 != NULL) {
				$$.last = TREE_LINK($$.last) = $3;
			}
		}
	;

enumerator
	: IDENTIFIER
		{
			if (debug_arr['y'] > 0) {
				fprintf(dbgout, "IDENT=%s, was_typedef=%d\n", $1.symbol->name, $1.was_typedef);
			}
			$$ = make(Id_decl, $1.location, $1.symbol);
		}
	| IDENTIFIER '=' constant_expression
		{
			if (debug_arr['y'] > 0) {
				fprintf(dbgout, "IDENT=%s, was_typedef=%d\n", $1.symbol->name, $1.was_typedef);
			}
			$$ = make(Id_decl, $1.location, $1.symbol);
			ID_DECL($$).init_value = $3;
		}
	;

type_qualifier
	: CONST
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0x40000000;
			$$.unk_08 = 0;
			$$.unk_0C = $1;
		}
	| VOLATILE
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0x80000000;
			$$.unk_08 = 0;
			$$.unk_0C = $1;
		}
	| UNALIGN
		{
			$$.unk_00 = NULL;
			$$.unk_04 = 0x80;
			$$.unk_08 = 0;
			$$.unk_0C = $1;
		}
	;

declarator
	: direct_declarator
	| pointer direct_declarator
		{
			QUALIFIERS_PUSH_BACK($2.unk_04, $1);
			$$ = $2;
		}
	;

direct_declarator
	: IDENTIFIER
		{
			if (debug_arr['y'] > 0) {
				fprintf(dbgout, "IDENT=%s, was_typedef=%d\n", $1.symbol->name, $1.was_typedef);
			}
			$$.unk_00 = 0;
			cur_lvl->unk_04 = 1;
			if ($1.was_typedef && !cur_lvl->in_struct_def && cur_lvl->unk_08 == 1) {
				UnkBeta* spD8;
				mk_parse_symb($1.symbol, 0, B_10020F04);
				spD8 = (UnkBeta*)get_link_elem(B_10020F08);
				spD8->unk_04 = $1.symbol;
				spD8->link.next = B_10020F08->used_list;
				B_10020F08->used_list = &spD8->link;
			}
			if (!cur_lvl->in_struct_def && cur_lvl->unk_08 == 0 && !$1.was_typedef) {
				UnkBeta* spD4;
				mk_parse_symb($1.symbol, -1, B_10020F04);
				spD4 = (UnkBeta*)get_link_elem(B_10020F08);
				spD4->unk_04 = $1.symbol;
				spD4->link.next = B_10020F08->used_list;
				B_10020F08->used_list = &spD4->link;
				$$.unk_04 = make(Id_decl, $1.location, $1.symbol);
			} else {
				$$.unk_04 = make(Id_decl, $1.location, $1.symbol);
			}
		}
	| '(' declarator ')'
		{
			$$ = $2;
			cur_lvl->unk_04 = 1;
		}
	| direct_declarator '[' ']'
		{
			$$.unk_04 = make(Array_type, $2, NULL);
			QUALIFIERS_PUSH_BACK($1.unk_04, $$.unk_04);
			$$ = $1;
		}
	| direct_declarator '[' constant_expression ']'
		{
			$$.unk_04 = make(Array_type, $2, $3);
			QUALIFIERS_PUSH_BACK($1.unk_04, $$.unk_04);
			$$ = $1;
		}
	| direct_declarator fdecl_start ')'
		{
			$$.unk_04 = make(Func_type, $2, NULL);
			QUALIFIERS_PUSH_BACK($1.unk_04, $$.unk_04);
			$$ = $1;
			if (B_10020F04 >= 2) {
                delete_local_decls(B_10020F04);
                cur_lvl = link_pop(B_10020F00);
                B_10020F04--;
            } else {
                $$.unk_00 = 1;
            }
		}
	| direct_declarator fdecl_start parameter_type_list ')'
		{
			$$.unk_04 = make(Func_type, $2, $3.first);
			QUALIFIERS_PUSH_BACK($1.unk_04, $$.unk_04);
			$$ = $1;
			if (B_10020F04 >= 2) {
                delete_local_decls(B_10020F04);
                cur_lvl = link_pop(B_10020F00);
                B_10020F04--;
            } else {
                $$.unk_00 = 1;
            }
		}
	| direct_declarator fdecl_start identifier_list ')'
		{
			$$.unk_04 = make(Func_type, $2, $3.first);
			QUALIFIERS_PUSH_BACK($1.unk_04, $$.unk_04);
			$$ = $1;
			if (B_10020F04 >= 2) {
                delete_local_decls(B_10020F04);
                cur_lvl = link_pop(B_10020F00);
                B_10020F04--;
            } else {
                $$.unk_00 = 1;
            }
			cur_lvl->unk_04 = 1;
		}
	;

fdecl_start
	: '('
		{
			cur_lvl = (UnkChi*)get_link_elem(B_10020F00);
			cur_lvl->unk_04 = 1;
			cur_lvl->unk_0C = FALSE;
			cur_lvl->in_struct_def = FALSE;
			cur_lvl->unk_08 = 1;
			cur_lvl->link.next = B_10020F00->used_list;
			B_10020F00->used_list = &cur_lvl->link;
			B_10020F04++;
		}
	;

pointer
	: '*'
		{
			$$ = make(Pointer_type, $1);
			POINTER_TYPE($$).size = bit_size[9];
			POINTER_TYPE($$).align = bit_size[9];
		}
	| '*' type_qualifier_list
		{
			$$ = make(Pointer_type, $2.unk_0C);
			POINTER_TYPE($$).size = bit_size[9];
			POINTER_TYPE($$).align = bit_size[9];
			TREE_ATTRIBUTE($$) = $2.unk_04;
		}
	| '*' pointer
		{
			$$ = make(Pointer_type, TREE_LOCATION($2));
			POINTER_TYPE($$).size = bit_size[9];
			POINTER_TYPE($$).align = bit_size[9];
			TYPE_PUSH_BACK($2, $$);
			$$ = $2;
		}
	| '*' type_qualifier_list pointer
		{
			$$ = make(Pointer_type, $2.unk_0C);
			POINTER_TYPE($$).size = bit_size[9];
			POINTER_TYPE($$).align = bit_size[9];
			TREE_ATTRIBUTE($$) = $2.unk_04;
			TYPE_PUSH_BACK($3, $$);
			$$ = $3;
		}
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
		{
			if (($$.unk_04 & 0x1F000000) && ($2.unk_04 & 0x1F000000)) {
				error(0x20103, LEVEL_WARNING, $2.unk_0C, attribute_to_string($2.unk_04));
			} else if ($$.unk_04 & $2.unk_04) {
				error(0x20094, LEVEL_WARNING, $2.unk_0C, attribute_to_string($2.unk_04));
			} else {
				$$.unk_04 |= $2.unk_04;
				$$.unk_0C = $2.unk_0C;
			}
		}
	;

identifier_list
	: identifier
		{
			cur_lvl->unk_04 = 0;
			$$.first = $$.last = $1;
		}
	| identifier_list ',' identifier
		{
			if ($$.first == NULL) {
				$$.first = $$.last = $3;
			} else if ($3 != NULL) {
				$$.last = TREE_LINK($$.last) = $3;
			}
		}
	;

identifier_or_constant_list
	: identifier
		{
			cur_lvl->unk_04 = 0;
			$$.first = $$.last = $1;
		}
	| CONSTANT
		{
			cur_lvl->unk_04 = 0;
			$$.first = $$.last = $1;
		}
	| identifier_list ',' identifier
		{
			if ($$.first == NULL) {
				$$.first = $$.last = $3;
			} else if ($3 != NULL) {
				$$.last = TREE_LINK($$.last) = $3;
			}
		}
	| identifier_list ',' CONSTANT
		{
			if ($$.first == NULL) {
				$$.first = $$.last = $3;
			} else if ($3 != NULL) {
				$$.last = TREE_LINK($$.last) = $3;	
			}
		}
	;

parameter_type_list
	: parameter_list
	| ELLIPSIS
		{
			TreeNode* sp98;
			sp98 = make(Id_decl, $1, builtins[6]);
			sp98 = make(Declare_decl, $1, ellipsis, sp98);
			$$.first = $$.last = sp98;
			if (IS_STRICT_ANSI) {
				error(0x2012C, LEVEL_WARNING, $1);
			}
		}
	| parameter_list ',' ELLIPSIS
		{
			TreeNode* sp94;
			sp94 = make(Id_decl, $3, builtins[6]);
			sp94 = make(Declare_decl, $3, ellipsis, sp94);
			if ($$.first == NULL) {
				$$.first = $$.last = sp94;
			} else if (sp94 != NULL) {
				$$.last = TREE_LINK($$.last) = sp94;
			}
		}
	;

parameter_list
	: parameter_declaration
		{
			$$.first = $$.last = $1;
		}
	| parameter_list ',' parameter_declaration
		{
			if ($$.first == NULL) {
				$$.first = $$.last = $3;
			} else if ($3 != NULL) {
				$$.last = TREE_LINK($$.last) = $3;
			}
		}
	;

parameter_declaration
	: declaration_specifiers declarator
		{
			if ($2.unk_00 != NULL)	{
				delete_local_decls(B_10020F04);
                cur_lvl = link_pop(B_10020F00);
                B_10020F04--;
			}
			$$ = make_topdecl($1.unk_00, $1.unk_04, $1.unk_08, $2.unk_04, $1.unk_0C);
			cur_lvl->unk_08 = 1;
		}
	| declaration_specifiers
		{
			$$ = make_topdecl($1.unk_00, $1.unk_04, $1.unk_08, NULL, $1.unk_0C);
			cur_lvl->unk_04 = 1;
			cur_lvl->unk_08 = 1;
		}
	| declaration_specifiers abstract_declarator
		{
			$$ = make_topdecl($1.unk_00, $1.unk_04, $1.unk_08, $2, $1.unk_0C);
			cur_lvl->unk_04 = 1;
			cur_lvl->unk_08 = 1;
		}
	;

type_name
	: specifier_qualifier_list
		{
			$$ = make_topdecl($1.unk_00, $1.unk_04, $1.unk_08, NULL, $1.unk_0C);
		}
	| specifier_qualifier_list abstract_declarator
		{
			$$ = make_topdecl($1.unk_00, $1.unk_04, $1.unk_08, $2, $1.unk_0C);
		}
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
		{
			TYPE_PUSH_BACK($2, $1);
			$$ = $2;
		}
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
		{
			$$ = $2;
		}
	| '[' ']'
		{
			$$ = make(Array_type, $1, NULL);
		}
	| '[' constant_expression ']'
		{
			$$ = make(Array_type, $1, $2);
		}
	| direct_abstract_declarator '[' ']'
		{
			$$ = make(Array_type, $2, NULL);
			TYPE_PUSH_BACK($1, $$);
			$$ = $1;
		}
	| direct_abstract_declarator '[' constant_expression ']'
		{
			$$ = make(Array_type, $2, $3);
			TYPE_PUSH_BACK($1, $$);
			$$ = $1;
		}
	| fdecl_start ')'
		{
			$$ = make(Func_type, $1, NULL);
			delete_local_decls(B_10020F04);
            cur_lvl = link_pop(B_10020F00);
            B_10020F04--;
		}
	| fdecl_start parameter_type_list ')'
		{
			$$ = make(Func_type, $1, $2.first);
			delete_local_decls(B_10020F04);
            cur_lvl = link_pop(B_10020F00);
            B_10020F04--;
		}
	| direct_abstract_declarator fdecl_start ')'
		{
			$$ = make(Func_type, $2, NULL);
			TYPE_PUSH_BACK($1, $$);
			$$ = $1;
			delete_local_decls(B_10020F04);
            cur_lvl = link_pop(B_10020F00);
            B_10020F04--;
		}
	| direct_abstract_declarator fdecl_start parameter_type_list ')'
		{
			$$ = make(Func_type, $2, $3.first);
			TYPE_PUSH_BACK($1, $$);
			$$ = $1;
			delete_local_decls(B_10020F04);
            cur_lvl = link_pop(B_10020F00);
            B_10020F04--;
		}
	;

typedef_name
	: TYPE_IDENT
		{
			cur_lvl->unk_04 = 0;
			if (debug_arr['y'] > 0) {
				fprintf(dbgout, "T_IDENT=%s, was_typedef=%d\n", $1.symbol->name, $1.was_typedef);
			}
		}
	;

initializer
	: assignment_expression
	| '{' { tree_handle = temp_handle; } initializer_list optcomma '}'
		{
			$$ = make(Aggregate_expr, TREE_LOCATION($3.first), $3.first);
			if (B_10020F04 == 0) {
				tree_handle = general_handle;
			}
		}
	;

initializer_list
	: initializer { $$.first = $$.last = $1; }
	| initializer_list ',' initializer
		{
			if ($$.first == NULL) {
				$$.first = $$.last = $3;
			} else if ($3 != NULL) {
				$$.last = TREE_LINK($$.last) = $3;
			}
		}
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	| try_statement
	;

labeled_statement
	: IDENTIFIER ':' statement
		{
			if (debug_arr['y'] > 0) {
				fprintf(dbgout, "IDENT=%s, was_typedef=%d\n", $1.symbol->name, $1.was_typedef);
			}
			$$ = make(Id_decl, $1.location, $1.symbol);
			$$ = make(Idlabeled_stmt, $1.location, $$, $3);
		}
	| typedef_name ':' { cur_lvl->unk_04 = 1; } statement
		{
			$$ = make(Id_decl, $1.location, $1.symbol);
			$$ = make(Idlabeled_stmt, $1.location, $$, $4);
		}
	| CASE constant_expression ':' statement
		{
			$$ = make(Caselabeled_stmt, $1, $2, $4);
		}
	| DEFAULT ':' statement
		{
			$$ = make(Defaultlabeled_stmt, $1, $3);
		}
	;

compound_statement
	: comp_start '}'
		{
			$$ = make(Compound_stmt, $1, NULL, NULL, $2);
			delete_local_decls(B_10020F04);
            cur_lvl = link_pop(B_10020F00);
            B_10020F04--;
		}
	| comp_start statement_list '}'
		{
			$$ = make(Compound_stmt, $1, NULL, $2.first, $3);
			delete_local_decls(B_10020F04);
            cur_lvl = link_pop(B_10020F00);
            B_10020F04--;
		}
	| comp_start declaration_list '}'
		{
			$$ = make(Compound_stmt, $1, $2.first, NULL, $3);
			delete_local_decls(B_10020F04);
            cur_lvl = link_pop(B_10020F00);
            B_10020F04--;
		}
	| comp_start declaration_list statement_list '}'
		{
			$$ = make(Compound_stmt, $1, $2.first, $3.first, $4);
			delete_local_decls(B_10020F04);
            cur_lvl = link_pop(B_10020F00);
            B_10020F04--;
		}
	;

comp_start
	: '{'
		{
			if (cur_lvl->unk_0C) {
				cur_lvl = (UnkChi*)get_link_elem(B_10020F00);
				cur_lvl->unk_04 = 1;
				cur_lvl->in_struct_def = FALSE;				
				cur_lvl->unk_08 = 1;
				cur_lvl->link.next = B_10020F00->used_list;
				B_10020F00->used_list = &cur_lvl->link;
				B_10020F04++;
			}
			cur_lvl->unk_08 = 1;
			cur_lvl->unk_0C = TRUE;
			tree_handle = temp_handle;
		}
	;

declaration_list
	: declaration { $$.first = $$.last = $1; }
	| declaration_list declaration
		{
			if ($$.first == NULL) {
				$$.first = $$.last = $2;
			} else if ($2 != NULL) {
				$$.last = TREE_LINK($$.last) = $2;
			}
		}
	;

statement_list
	: statement { $$.first = $$.last = $1; }
	| statement_list statement
		{
			if ($$.first == NULL) {
				$$.first = $$.last = $2;
			} else if ($2 != NULL) {
				$$.last = TREE_LINK($$.last) = $2;
			}
		}
	| error { $$.first = $$.last = NULL; } 
	| statement_list error
	;

expression_statement
	: ';'
		{
			$$ = make(Expr_stmt, $1, NULL);
		}
	| expression ';'
		{
			$$ = make(Expr_stmt, TREE_LOCATION($1), $1);
		}
	;

selection_statement
	: IF '(' expression ')' statement
		{
			$$ = make(If_stmt, $1, $3, $5, NULL);
		}
	| IF '(' expression ')' statement ELSE statement
		{
			$$ = make(If_stmt, $1, $3, $5, $7);
		}
	| SWITCH '(' expression ')' statement
		{
			$$ = make(Switch_stmt, $1, $3, $5);
		}
	;

iteration_statement
	: WHILE '(' expression ')' statement
		{
			$$ = make(While_stmt, $1, $3, $5);
		}
	| DO statement WHILE '(' expression ')' ';'
		{
			$$ = make(Dowhile_stmt, $1, $2, $5);
		}
	| FOR '(' ';' ';' ')' statement
		{
			$$ = make(For_stmt, $1, NULL, NULL, NULL, $6);
		}
	| FOR '(' ';' ';' expression ')' statement
		{
			$$ = make(For_stmt, $1, NULL, NULL, $5, $7);
		}
	| FOR '(' ';' expression ';' ')' statement
		{
			$$ = make(For_stmt, $1, NULL, $4, NULL, $7);
		}
	| FOR '(' ';' expression ';' expression ')' statement
		{
			$$ = make(For_stmt, $1, NULL, $4, $6, $8);
		}
	| FOR '(' expression ';' ';' ')' statement
		{
			$$ = make(For_stmt, $1, $3, NULL, NULL, $7);
		}
	| FOR '(' expression ';' ';' expression ')' statement
		{
			$$ = make(For_stmt, $1, $3, NULL, $6, $8);
		}
	| FOR '(' expression ';' expression ';' ')' statement
		{
			$$ = make(For_stmt, $1, $3, $5, NULL, $8);
		}
	| FOR '(' expression ';' expression ';' expression ')' statement
		{
			$$ = make(For_stmt, $1, $3, $5, $7, $9);
		}
	;

jump_statement
	: GOTO IDENTIFIER ';'
		{
			if (debug_arr['y'] > 0) {
				fprintf(dbgout, "IDENT=%s, was_typedef=%d\n", $2.symbol->name, $2.was_typedef);
			}
			$$ = make(Id_decl, $2.location, $2.symbol);
			$$ = make(Goto_stmt, $1, $$);
		}
	| CONTINUE ';'
		{
			$$ = make(Continue_stmt, $1);
		}
	| BREAK ';'
		{
			$$ = make(Break_stmt, $1);
		}
	| RETURN ';'
		{
			$$ = make(Return_stmt, $1, NULL);
		}
	| RETURN expression ';'
		{
			$$ = make(Return_stmt, $1, $2);
		}
	| LEAVE ';'
		{
			$$ = make(Leave_stmt, $1);
		}
	;

try_statement
	: TRY compound_statement EXCEPT '(' expression ')' compound_statement
		{
			$$ = make(Try_stmt, $1, $5, $2, $7);
		}
	| TRY compound_statement FINALLY compound_statement
		{
			$$ = make(Try_stmt, $1, NULL, $2, $4);
		}

translation_unit
	: external_definition
		{
			if (B_10020F10.first == NULL) {
				B_10020F10.first = B_10020F10.last = $1;
			} else if ($1 != NULL) {
				B_10020F10.last = TREE_LINK(B_10020F10.last) = $1;
			}
			if (temp_handle->current_region - temp_handle->list_start > options[OPTION_T_LEVEL]) {
				YYACCEPT;
			}
			parse_init();
		}
	| translation_unit external_definition
		{
			if (B_10020F10.first == NULL) {
				B_10020F10.first = B_10020F10.last = $2;
			} else if ($2 != NULL) {
				B_10020F10.last = TREE_LINK(B_10020F10.last) = $2;
			}
			if (temp_handle->current_region - temp_handle->list_start > options[OPTION_T_LEVEL]) {
				YYACCEPT;
			}
			parse_init();
		}
	;

external_definition
	: function_definition
	| top_declaration
	| ';'
		{
			error(0x2007F, LEVEL_DEFAULT, $1);
			$$ = NULL;
		}
	| error
		{
			tree_handle = general_handle;
			$$ = NULL;
		}
	| __PRAGMA '(' CONSTANT ',' identifier_or_constant_list ')' ';'
		{
			$$ = make(Pragma, $1, (int)ICONSTANT($3).value, $5);
		}
	| __PRAGMA '(' CONSTANT ')' ';'
		{
			$$ = make(Pragma, $1, (int)ICONSTANT($3).value, NULL);
		}
	;

function_definition
	: declarator function_body
		{
			if (TREE_CODE($1.unk_04) == Id_decl) {
				char* sp68 = NULL;
				char* sp64 = NULL;
				int sp60 = 0;
				real_file_line(TREE_LOCATION($1.unk_04), &sp68, &sp60, 0);
				real_file_line(TREE_LOCATION($2), &sp64, &sp60, 0);
				if (sp68 != NULL && sp64 != NULL && strcmp(sp68, sp64) != 0) {
					TREE_LOCATION($1.unk_04) = TREE_LOCATION($2);
				}
			}
			if (ID_DECL($1.unk_04).qualifiers == NULL || TREE_CODE(ID_DECL($1.unk_04).qualifiers) != Func_type) {
				error(0x2010A, LEVEL_DEFAULT, TREE_LOCATION($2), ID_DECL($1.unk_04).id->name);
			} else if (TREE_LINK($2) != NULL) {
				FUNC_TYPE(ID_DECL($1.unk_04).qualifiers).decls = TREE_LINK($2);
				ID_DECL($1.unk_04).init_value = $2;
				TREE_LINK($2) = NULL;
			} else {
				ID_DECL($1.unk_04).init_value = $2;
			}
			tree_handle = general_handle;
			$$ = make_topdecl(int_type, NULL, NULL, $1.unk_04, TREE_LOCATION($1.unk_04));
		}
	| declaration_specifiers declarator { cur_lvl->unk_08 = 1; } function_body
		{
			if (TREE_CODE($2.unk_04) == Id_decl) {
				char* sp5C = NULL;
				char* sp58 = NULL;
				int sp54 = 0;
				real_file_line(TREE_LOCATION($2.unk_04), &sp5C, &sp54, 0);
				real_file_line(TREE_LOCATION($4), &sp58, &sp54, 0);
				if (sp5C != NULL && sp58 != NULL && strcmp(sp5C, sp58) != 0) {
					TREE_LOCATION($2.unk_04) = TREE_LOCATION($4);
				}
			}
			if (ID_DECL($2.unk_04).qualifiers == NULL || TREE_CODE(ID_DECL($2.unk_04).qualifiers) != Func_type) {
				error(0x2010A, LEVEL_DEFAULT, TREE_LOCATION($4), ID_DECL($2.unk_04).id->name);
			} else if (TREE_LINK($4) != NULL) {
				FUNC_TYPE(ID_DECL($2.unk_04).qualifiers).decls = TREE_LINK($4);
				ID_DECL($2.unk_04).init_value = $4;
				TREE_LINK($4) = NULL;
			} else {
				ID_DECL($2.unk_04).init_value = $4;
			}
			tree_handle = general_handle;
			$$ = make_topdecl($1.unk_00, $1.unk_04, $1.unk_08, $2.unk_04, $1.unk_0C);
		}
	;

function_body
	: compound_statement
	| declaration_list compound_statement
		{
			LINK_PUSH_BACK($2, $1.first);
			$$ = $2;
		}

build_program_tree
	: translation_unit {  }
	| { B_10020F10.first = make(End_of_file, -1); }
	;

%%
