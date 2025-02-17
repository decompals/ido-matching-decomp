%{
#include "common.h"
char* ident = "$Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/targucode/cfe/RCS/c.y,v 1.17 1995/02/27 21:57:39 rdahl Exp $";

#define YYMAXDEPTH 800

typedef struct LocalDeclaration {
    LinkedListEntry link;
    Symbol* symbol;
} LocalDeclaration;

// .bss
/* 0x10020F00 */ static LinkedList* level_list;
/* 0x10020F04 */ static int depth;
/* 0x10020F08 */ static LinkedList* local_decls;
/* 0x10020F10 */ static TreeNodeList B_10020F10;

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

#define LIST_APPEND(list, item) \
if (list.first == NULL) { \
	list.first = list.last = item; \
} else if (item != NULL) { \
	list.last = TREE_LINK(list.last) = item; \
}

#define LIST_INIT(list, item) \
	list.first = list.last = item;

// TODO remove error() from yaccpar and probably replace ti with macro

void parse_init(void) {
    if (level_list == NULL) {
        level_list = link_start(general_handle, sizeof(ParseLevel));
    } else {
        free_link_list(level_list);
    }

    if (local_decls == NULL) {
        local_decls = link_start(general_handle, sizeof(LocalDeclaration));
    }

    cur_lvl = (ParseLevel*)get_link_elem(level_list);
    cur_lvl->type_ident_expected = TRUE;
    cur_lvl->normal_ident = TRUE;
    cur_lvl->in_comp_expr = FALSE;
    cur_lvl->in_struct_def = FALSE;
    cur_lvl->link.next = level_list->used_list;
    level_list->used_list = &cur_lvl->link;

    depth = 0;
    tree_handle = general_handle;    
}

TreeNode* parse(void) {
    temp_handle = mem_start();
	LIST_INIT(B_10020F10, NULL);
    parse_init();
    if (yyparse() != 0) {
        return NULL;
    } else {
        return B_10020F10.first;
    }
}

void delete_local_decls(int level) {
    LocalDeclaration* local_decl = (LocalDeclaration*)local_decls->used_list;
    ParseSymbol* psymb;

    while (local_decl != NULL) {
        if (local_decl == NULL) {
            return;
        }
        psymb = local_decl->symbol->psymb;
        
        if (psymb == NULL) {
            link_pop(local_decls);
            return;
        }
        if (psymb->level < level) {
            return;
        }

        while (psymb != NULL && psymb->level >= level) {
            ParseSymbol* unhidden = (ParseSymbol*)psymb->link.next;
            if (debug_arr['P'] > 0) {
                fprintf(dbgout, "deleting %.*s (0x%x:%d:%s) unhides (0x%x:%d:%s)\n",
                        local_decl->symbol->namelen, local_decl->symbol->name,
                        psymb, psymb->level, GET_SYM_CAT(psymb->id),
                        unhidden, unhidden != NULL ? unhidden->level : -1, unhidden != NULL ? GET_SYM_CAT(unhidden->id) : "<nil>");
            }

            psymb->link.next = psymb_handle->free_list;
            psymb_handle->free_list = &psymb->link;
            psymb = unhidden;
            local_decl->symbol->psymb = unhidden;
        }
        local_decl = link_pop(local_decls);
    }
}

TreeNode* make_topdecl(TreeNode* type, int attr, int typespec, TreeNode* ids, int location) {
    TreeNode* decl;
    
    decl = make(Declare_decl, location, NULL, ids);
	TREE_ATTRIBUTE(decl) = attr;
    if (type != NULL) {
		TREE_TYPE(decl) = type;
        if (typespec != 0) {
            error(0x2010F, LEVEL_WARNING, location);
        }
        return decl;
    } else {
        TREE_TYPE(decl) = normalize_type(typespec, location);
        if (was_plain_char(typespec)) {
            TREE_ATTRIBUTE(decl) |= PLAIN_ATTRIBUTE;
        }
        return decl;
    }
}

static TreeNode* make_pre_update_cast(int pre_update_code, int location, TreeNode* cast_expr) {
    TreeNode* cast_type;
    TreeNode* pointer;    
    
    if (!options[OPTION_MSFT]) {
        error(0x3015A, LEVEL_WARNING, location);
    }
    
    if (cast_expr == NULL || BINARY_EXPR(cast_expr).operand[0] == NULL) {
        return NULL;
    }

    cast_type = DECLARE_DECL(BINARY_EXPR(cast_expr).operand[0]).ids;
    pointer = make(Pointer_type, location, cast_type, cast_expr);
    POINTER_TYPE(pointer).size = bit_size[9];
    POINTER_TYPE(pointer).align = bit_size[9];


    if (cast_type == NULL) {
		DECLARE_DECL(BINARY_EXPR(cast_expr).operand[0]).ids = pointer;
    } else {
        TreeNode* ptr = cast_type;
        TreeNode* prev = ptr;
        
        while (ptr != NULL) {
            prev = ptr;
            ptr = TREE_TYPE(ptr);
        }
        TREE_TYPE(prev) = pointer;
    }
    return make(pre_update_code, location, make(Indirect_expr, location, cast_expr));
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
			TreeNode* arglist = make(Aggregate_expr, TREE_LOCATION($3), $3);
			$$ = make(Call_expr, $2, $1, arglist);
		}
	| postfix_expression '(' ')' { $$ = make(Call_expr, $2, $1, NULL); }
	| postfix_expression '.' { cur_lvl->type_ident_expected = FALSE; } identifier
		{ 
			$$ = make(Component_ref, $2, $1, $4);
			cur_lvl->type_ident_expected = TRUE;
		}
	| postfix_expression PTR_OP { cur_lvl->type_ident_expected = FALSE; } identifier
		{
			$$ = make(Indirect_component_ref, $2, $1, $4);
			cur_lvl->type_ident_expected = TRUE;
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
			TreeNode* ident_ellipsis = make(Identifier, $2, builtins[6]);
			$$ = make(Addr_expr, $1, ident_ellipsis);
			if (IS_STRICT_ANSI) {
				error(0x2012D, LEVEL_WARNING, $2);
			}
		}
	| SIZEOF unary_expression { $$ = make(Sizeof_expr, $1, $2); }
	| SIZEOF '(' type_name { cur_lvl->type_ident_expected = TRUE; } ')' { $$ = make(Sizeof_expr, $1, $3); }
	| ALIGNOF unary_expression { $$ = make(Alignof_expr, $1, $2); }
	| ALIGNOF '(' type_name { cur_lvl->type_ident_expected = TRUE; } ')' { $$ = make(Alignof_expr, $1, $3); }
	| CLASSOF unary_expression { $$ = make(Classof_expr, $1, $2); }
	| CLASSOF '(' type_name { cur_lvl->type_ident_expected = TRUE; } ')' { $$ = make(Classof_expr, $1, $3); }
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
	| '(' type_name { cur_lvl->type_ident_expected = TRUE; } ')' cast_expression { $$ = make(Cast_expr, $1, $2, $5); }
	| DEC_OP '(' type_name { cur_lvl->type_ident_expected = TRUE; } ')' cast_expression
		{
			TreeNode* cast_expr = make(Cast_expr, $2, $3, $6);
			$$ = make_pre_update_cast(Predecrement_expr, $1, cast_expr);
		}
	| INC_OP '(' type_name { cur_lvl->type_ident_expected = TRUE; } ')' cast_expression
		{
			TreeNode* cast_expr = make(Cast_expr, $2, $3, $6);
			$$ = make_pre_update_cast(Preincrement_expr, $1, cast_expr);
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
			if (depth == 0) {
                error(0x2007B, LEVEL_ERROR, curloc);
            }
			$$ = make_topdecl($1.type, $1.type_attr, $1.type_spec, $2.first, $1.location);
			cur_lvl->type_ident_expected = TRUE;
			cur_lvl->normal_ident = TRUE;
		}
	| declaration_specifiers ';'
		{
			if (depth == 0) {
                error(0x2007B, LEVEL_ERROR, curloc);
            }
			$$ = make_topdecl($1.type, $1.type_attr, $1.type_spec, NULL, $1.location);
			cur_lvl->type_ident_expected = TRUE;
			cur_lvl->normal_ident = TRUE;
		}
	;

top_declaration
	: declaration_specifiers init_declarator_list ';' 
		{
			$$ = make_topdecl($1.type, $1.type_attr, $1.type_spec, $2.first, $1.location);
			cur_lvl->type_ident_expected = TRUE;
			cur_lvl->normal_ident = TRUE;
		}
	| declaration_specifiers ';' 
		{
			$$ = make_topdecl($1.type, $1.type_attr, $1.type_spec, NULL, $1.location);
			cur_lvl->type_ident_expected = TRUE;
			cur_lvl->normal_ident = TRUE;
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
			if (($$.type_attr & STORAGE_CLASS_ATTRIBUTE) && ($2.type_attr & STORAGE_CLASS_ATTRIBUTE)) {
				error(0x20103, LEVEL_WARNING, $2.location, attribute_to_string($2.type_attr));
			} else if ($$.type_attr & $2.type_attr) {
				error(0x20094, LEVEL_WARNING, $2.location, attribute_to_string($2.type_attr));
			} else {
				$$.type_attr |= $2.type_attr;
				$$.location = $2.location;
			}
		}
	| declaration_specifiers type_specifier
		{
			if ($$.type != NULL) {
				error(0x20162, LEVEL_WARNING, TREE_LOCATION($$.type));
			}
			if ($2.type != NULL) {
				$$.type = $2.type;
			} else if ($$.type_spec & $2.type_spec) {
				if ($2.type_spec == TYPESPEC_LONG) {
					if (IS_STRICT_ANSI) {
						error(0x20131, LEVEL_WARNING, $2.location, "long long");
					}
					$$.type_spec = $$.type_spec ^ $2.type_spec;
					$$.type_spec |= TYPESPEC_LONGLONG;
				} else {
					error(0x20094, LEVEL_WARNING, $2.location, type_to_string($2.type_spec));
				}
			} else {
				$$.type_spec |= $2.type_spec;
			}
		}
	| declaration_specifiers type_qualifier
		{
			if (($$.type_attr & STORAGE_CLASS_ATTRIBUTE) && ($2.type_attr & STORAGE_CLASS_ATTRIBUTE)) {
				error(0x20103, LEVEL_WARNING, $2.location, attribute_to_string($2.type_attr));
			} else if ($$.type_attr & $2.type_attr) {
				error(0x20094, LEVEL_WARNING, $2.location, attribute_to_string($2.type_attr));
			} else {
				$$.type_attr |= $2.type_attr;
				$$.location = $2.location;
			}
		}
	| fct_specifier
	| declaration_specifiers fct_specifier
		{
			if (($$.type_attr & STORAGE_CLASS_ATTRIBUTE) && ($2.type_attr & STORAGE_CLASS_ATTRIBUTE)) {
				error(0x20103, LEVEL_WARNING, $2.location, attribute_to_string($2.type_attr));
			} else if ($$.type_attr & $2.type_attr) {
				error(0x20094, LEVEL_WARNING, $2.location, attribute_to_string($2.type_attr));
			} else {
				$$.type_attr |= $2.type_attr;
				$$.location = $2.location;
			}
		}
	;

fct_specifier
	: INLINE
		{
			$$.type = NULL;
			$$.type_attr = INLINE_ATTRIBUTE;
			$$.type_spec = 0;
			$$.location = $1;
		}

init_declarator_list
	: init_declarator
		{
			LIST_INIT($$, $1);
		}
	| init_declarator_list ',' { cur_lvl->type_ident_expected = FALSE; } init_declarator
		{
			LIST_APPEND($$, $4);
		}
	;

init_declarator
	: declarator
		{
			if ($1.unk_00) {
				delete_local_decls(depth);
                cur_lvl = link_pop(level_list);
                depth--;
			}
			$$ = $1.unk_04;
		} 
	| declarator '=' initializer
		{
			if ($1.unk_00) {
				delete_local_decls(depth);
                cur_lvl = link_pop(level_list);
                depth--;
			}
			ID_DECL($1.unk_04).init_value = $3;
			$$ = $1.unk_04;
		}
	;

storage_class_specifier
	: TYPEDEF
		{
			$$.type = NULL;
			$$.type_attr = TYPEDEF_ATTRIBUTE;
			$$.type_spec = 0;
			$$.location = $1;
			cur_lvl->normal_ident = FALSE;
		}
	| EXTERN 
		{
			$$.type = NULL;
			$$.type_attr = EXTERN_ATTRIBUTE;
			$$.type_spec = 0;
			$$.location = $1;
		}
	| STATIC
		{
			$$.type = NULL;
			$$.type_attr = STATIC_ATTRIBUTE;
			$$.type_spec = 0;
			$$.location = $1;
		}
	| AUTO
		{
			$$.type = NULL;
			$$.type_attr = AUTO_ATTRIBUTE;
			$$.type_spec = 0;
			$$.location = $1;
		}
	| REGISTER
		{
			$$.type = NULL;
			$$.type_attr = REGISTER_ATTRIBUTE;
			$$.type_spec = 0;
			$$.location = $1;
		}
	;

type_specifier
	: CHAR
		{
			$$.type = NULL;
			$$.type_attr = 0;
			$$.type_spec = TYPESPEC_CHAR;
			$$.location = $1;
			cur_lvl->type_ident_expected = FALSE;
		}
	| SHORT
		{
			$$.type = NULL;
			$$.type_attr = 0;
			$$.type_spec = TYPESPEC_SHORT;
			$$.location = $1;
			cur_lvl->type_ident_expected = FALSE;
		}
	| INT
		{
			$$.type = NULL;
			$$.type_attr = 0;
			$$.type_spec = TYPESPEC_INT;
			$$.location = $1;
			cur_lvl->type_ident_expected = FALSE;
		}
	| LONG
		{
			$$.type = NULL;
			$$.type_attr = 0;
			$$.type_spec = TYPESPEC_LONG;
			$$.location = $1;
			cur_lvl->type_ident_expected = FALSE;
		}
	| LONGLONG
		{
			$$.type = NULL;
			$$.type_attr = 0;
			$$.type_spec = TYPESPEC_LONGLONG;
			$$.location = $1;
			cur_lvl->type_ident_expected = FALSE;
		}
	| SIGNED
		{
			$$.type = NULL;
			$$.type_attr = 0;
			$$.type_spec = TYPESPEC_SIGNED;
			$$.location = $1;
			cur_lvl->type_ident_expected = FALSE;
		}
	| UNSIGNED
		{
			$$.type = NULL;
			$$.type_attr = 0;
			$$.type_spec = TYPESPEC_UNSIGNED;
			$$.location = $1;
			cur_lvl->type_ident_expected = FALSE;
		}
	| FLOAT
		{
			$$.type = NULL;
			$$.type_attr = 0;
			$$.type_spec = TYPESPEC_FLOAT;
			$$.location = $1;
			cur_lvl->type_ident_expected = FALSE;
		}
	| DOUBLE
		{
			$$.type = NULL;
			$$.type_attr = 0;
			$$.type_spec = TYPESPEC_DOUBLE;
			$$.location = $1;
			cur_lvl->type_ident_expected = FALSE;
		}
	| VOID
		{
			$$.type = NULL;
			$$.type_attr = 0;
			$$.type_spec = TYPESPEC_VOID;
			$$.location = $1;
			cur_lvl->type_ident_expected = FALSE;
		}
	| struct_or_union_specifier
		{
			$$.type = $1;
			$$.type_attr = 0;
			$$.type_spec = 0;
			$$.location = TREE_LOCATION($1);
			cur_lvl->type_ident_expected = FALSE;
		}
	| enum_specifier
		{
			$$.type = $1;
			$$.type_attr = 0;
			$$.type_spec = 0;
			$$.location = TREE_LOCATION($1);
			cur_lvl->type_ident_expected = FALSE;
		}
	| typedef_name
		{
			$$.type = make(Identifier, $1.location, $1.symbol);
			$$.type_attr = 0;
			$$.type_spec = 0;
			$$.location = $1.location;
		}
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{'
		{
			if (debug_arr['y'] > 0) {
				fprintf(dbgout, "IDENT=%s, was_typedef=%d\n", $2.symbol->name, $2.was_typedef);
			}
			cur_lvl = (ParseLevel*)get_link_elem(level_list);
			cur_lvl->type_ident_expected = TRUE;
			cur_lvl->in_struct_def = TRUE;
			cur_lvl->link.next = level_list->used_list;
    		level_list->used_list = &cur_lvl->link;
		}
	  struct_declaration_list_semi '}'
	  	{
			STRUCT_TYPE($$).sname = make(Id_decl, $2.location, $2.symbol);
			STRUCT_TYPE($$).members = $5;
			cur_lvl = link_pop(level_list);
            if (depth == 0) {
                tree_handle = cur_lvl->saved_ctx;
            }
		}
	| struct_or_union '{'
		{
			cur_lvl = (ParseLevel*)get_link_elem(level_list);
			cur_lvl->type_ident_expected = TRUE;
			cur_lvl->in_struct_def = TRUE;
			cur_lvl->link.next = level_list->used_list;
    		level_list->used_list = &cur_lvl->link;
		}
	  struct_declaration_list_semi '}'
	  	{
			STRUCT_TYPE($$).members = $4;
			cur_lvl = link_pop(level_list);
            if (depth == 0) {
                tree_handle = cur_lvl->saved_ctx;
            }
		}
	| struct_or_union IDENTIFIER
		{
			if (debug_arr['y'] > 0) {
				fprintf(dbgout, "IDENT=%s, was_typedef=%d\n", $2.symbol->name, $2.was_typedef);
			}
			STRUCT_TYPE($$).sname = make(Id_decl, $2.location, $2.symbol);
			cur_lvl->type_ident_expected = TRUE;
			if (depth == 0) {
                tree_handle = cur_lvl->saved_ctx;
            }
		}
	;

struct_or_union
	: STRUCT
		{
			if (depth == 0) {
                cur_lvl->saved_ctx = tree_handle;
                tree_handle = general_handle;
            }
            $$ = make(Struct_type, $1, STRUCT_INFO_STRUCT);
            cur_lvl->type_ident_expected = FALSE;
		}
	| UNION
		{
			if (depth == 0) {
                cur_lvl->saved_ctx = tree_handle;
                tree_handle = general_handle;
            }
            $$ = make(Struct_type, $1, STRUCT_INFO_UNION);
            cur_lvl->type_ident_expected = FALSE;
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
	: specifier_qualifier_list { cur_lvl->type_ident_expected = FALSE; } struct_declarator_list
		{
			cur_lvl->type_ident_expected = TRUE;
			$$ = make_topdecl($1.type, $1.type_attr, $1.type_spec, $3, $1.location);
		}
	;

specifier_qualifier_list
	: type_specifier
	| type_qualifier
	| specifier_qualifier_list type_specifier
		{
			if ($$.type != NULL) {
				error(0x20162, LEVEL_WARNING, TREE_LOCATION($$.type));
			}
			if ($2.type != NULL) {
				$$.type = $2.type;
			} else if ($$.type_spec & $2.type_spec) {
				if ($2.type_spec == TYPESPEC_LONG) {
					if (IS_STRICT_ANSI) {
						error(0x20131, LEVEL_WARNING, $2.location, "long long");
					}
					$$.type_spec = $$.type_spec ^ $2.type_spec;
					$$.type_spec |= TYPESPEC_LONGLONG;
				} else {
					error(0x20094, LEVEL_WARNING, $2.location, type_to_string($2.type_spec));
				}
			} else {
				$$.type_spec |= $2.type_spec;
			}
		}
	| specifier_qualifier_list type_qualifier
		{
			if (($$.type_attr & STORAGE_CLASS_ATTRIBUTE) && ($2.type_attr & STORAGE_CLASS_ATTRIBUTE)) {
				error(0x20103, LEVEL_WARNING, $2.location, attribute_to_string($2.type_attr));
			} else if ($$.type_attr & $2.type_attr) {
				error(0x20094, LEVEL_WARNING, $2.location, attribute_to_string($2.type_attr));
			} else {
				$$.type_attr |= $2.type_attr;
				$$.location = $2.location;
			}
		}
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' { cur_lvl->type_ident_expected = FALSE; } struct_declarator
		{
			LINK_PUSH_BACK($$, $4);
		}
	;

struct_declarator
	: declarator
		{
			if ($1.unk_00) {
				delete_local_decls(depth);
                cur_lvl = link_pop(level_list);
                depth--;
			}
			$$ = make(Field_decl, TREE_LOCATION($1.unk_04));
			FIELD_DECL($$).field = $1.unk_04;
		}
	| ':' { cur_lvl->type_ident_expected = TRUE; } constant_expression
		{
			$$ = make(Field_decl, TREE_LOCATION($3));
			FIELD_DECL($$).field = make(Id_decl, TREE_LOCATION($3), anonymous);
			FIELD_DECL($$).width = (int)$3; /* TODO figure out type */
		}
	| declarator ':' constant_expression
		{
			if ($1.unk_00 != NULL) {
				delete_local_decls(depth);
                cur_lvl = link_pop(level_list);
                depth--;
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
	: enum { cur_lvl->type_ident_expected = TRUE; } '{' enumerator_list optcomma '}'
		{
			ENUM_TYPE($$).literals = $4.first;
			if ($5 != -1) {
				error(0x2007E, LEVEL_DEFAULT, $5);
			}
			if (depth == 0) {
                tree_handle = cur_lvl->saved_ctx;
            }
		}
	| enum IDENTIFIER
		{
			if (debug_arr['y'] > 0) {
				fprintf(dbgout, "IDENT=%s, was_typedef=%d\n", $2.symbol->name, $2.was_typedef);
			}
			cur_lvl->type_ident_expected = TRUE;
		}
	  '{' enumerator_list optcomma '}'
	  	{
			ENUM_TYPE($$).ename = make(Id_decl, $2.location, $2.symbol);
			ENUM_TYPE($$).literals = $5.first;
			if ($6 != -1) {
				error(0x2007E, LEVEL_DEFAULT, $6);
			}
			if (depth == 0) {
                tree_handle = cur_lvl->saved_ctx;
            }
		}
	| enum IDENTIFIER
		{
			if (debug_arr['y'] > 0) {
				fprintf(dbgout, "IDENT=%s, was_typedef=%d\n", $2.symbol->name, $2.was_typedef);
			}
			ENUM_TYPE($$).ename = make(Id_decl, $2.location, $2.symbol);
			cur_lvl->type_ident_expected = TRUE;
			if (depth == 0) {
                tree_handle = cur_lvl->saved_ctx;
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
			if (depth == 0) {
                cur_lvl->saved_ctx = tree_handle;
                tree_handle = general_handle;
            }
            cur_lvl->type_ident_expected = FALSE;
            $$ = make(Enum_type, $1);
		}
	;

enumerator_list
	: enumerator { LIST_INIT($$, $1); }
	| enumerator_list ',' enumerator
		{
			LIST_APPEND($$, $3);
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
			$$.type = NULL;
			$$.type_attr = CONST_ATTRIBUTE;
			$$.type_spec = 0;
			$$.location = $1;
		}
	| VOLATILE
		{
			$$.type = NULL;
			$$.type_attr = VOLATILE_ATTRIBUTE;
			$$.type_spec = 0;
			$$.location = $1;
		}
	| UNALIGN
		{
			$$.type = NULL;
			$$.type_attr = UNALIGNED_ATTRIBUTE;
			$$.type_spec = 0;
			$$.location = $1;
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
			cur_lvl->type_ident_expected = TRUE;
			if ($1.was_typedef && !cur_lvl->in_struct_def && cur_lvl->normal_ident == TRUE) {
				LocalDeclaration* spD8;
				mk_parse_symb($1.symbol, 0, depth);
				spD8 = (LocalDeclaration*)get_link_elem(local_decls);
				spD8->symbol = $1.symbol;
				spD8->link.next = local_decls->used_list;
				local_decls->used_list = &spD8->link;
			}
			if (!cur_lvl->in_struct_def && cur_lvl->normal_ident == FALSE && !$1.was_typedef) {
				LocalDeclaration* spD4;
				mk_parse_symb($1.symbol, -1, depth);
				spD4 = (LocalDeclaration*)get_link_elem(local_decls);
				spD4->symbol = $1.symbol;
				spD4->link.next = local_decls->used_list;
				local_decls->used_list = &spD4->link;
				$$.unk_04 = make(Id_decl, $1.location, $1.symbol);
			} else {
				$$.unk_04 = make(Id_decl, $1.location, $1.symbol);
			}
		}
	| '(' declarator ')'
		{
			$$ = $2;
			cur_lvl->type_ident_expected = TRUE;
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
			if (depth >= 2) {
                delete_local_decls(depth);
                cur_lvl = link_pop(level_list);
                depth--;
            } else {
                $$.unk_00 = 1;
            }
		}
	| direct_declarator fdecl_start parameter_type_list ')'
		{
			$$.unk_04 = make(Func_type, $2, $3.first);
			QUALIFIERS_PUSH_BACK($1.unk_04, $$.unk_04);
			$$ = $1;
			if (depth >= 2) {
                delete_local_decls(depth);
                cur_lvl = link_pop(level_list);
                depth--;
            } else {
                $$.unk_00 = 1;
            }
		}
	| direct_declarator fdecl_start identifier_list ')'
		{
			$$.unk_04 = make(Func_type, $2, $3.first);
			QUALIFIERS_PUSH_BACK($1.unk_04, $$.unk_04);
			$$ = $1;
			if (depth >= 2) {
                delete_local_decls(depth);
                cur_lvl = link_pop(level_list);
                depth--;
            } else {
                $$.unk_00 = 1;
            }
			cur_lvl->type_ident_expected = TRUE;
		}
	;

fdecl_start
	: '('
		{
			cur_lvl = (ParseLevel*)get_link_elem(level_list);
			cur_lvl->type_ident_expected = TRUE;
			cur_lvl->in_comp_expr = FALSE;
			cur_lvl->in_struct_def = FALSE;
			cur_lvl->normal_ident = TRUE;
			cur_lvl->link.next = level_list->used_list;
			level_list->used_list = &cur_lvl->link;
			depth++;
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
			$$ = make(Pointer_type, $2.location);
			POINTER_TYPE($$).size = bit_size[9];
			POINTER_TYPE($$).align = bit_size[9];
			TREE_ATTRIBUTE($$) = $2.type_attr;
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
			$$ = make(Pointer_type, $2.location);
			POINTER_TYPE($$).size = bit_size[9];
			POINTER_TYPE($$).align = bit_size[9];
			TREE_ATTRIBUTE($$) = $2.type_attr;
			TYPE_PUSH_BACK($3, $$);
			$$ = $3;
		}
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
		{
			if (($$.type_attr & 0x1F000000) && ($2.type_attr & 0x1F000000)) {
				error(0x20103, LEVEL_WARNING, $2.location, attribute_to_string($2.type_attr));
			} else if ($$.type_attr & $2.type_attr) {
				error(0x20094, LEVEL_WARNING, $2.location, attribute_to_string($2.type_attr));
			} else {
				$$.type_attr |= $2.type_attr;
				$$.location = $2.location;
			}
		}
	;

identifier_list
	: identifier
		{
			cur_lvl->type_ident_expected = FALSE;
			LIST_INIT($$, $1);
		}
	| identifier_list ',' identifier
		{
			LIST_APPEND($$, $3);
		}
	;

identifier_or_constant_list
	: identifier
		{
			cur_lvl->type_ident_expected = FALSE;
			LIST_INIT($$, $1);
		}
	| CONSTANT
		{
			cur_lvl->type_ident_expected = FALSE;
			LIST_INIT($$, $1);
		}
	| identifier_list ',' identifier
		{
			LIST_APPEND($$, $3);
		}
	| identifier_list ',' CONSTANT
		{
			LIST_APPEND($$, $3);
		}
	;

parameter_type_list
	: parameter_list
	| ELLIPSIS
		{
			TreeNode* sp98;
			sp98 = make(Id_decl, $1, builtins[6]);
			sp98 = make(Declare_decl, $1, ellipsis, sp98);
			LIST_INIT($$, sp98);
			if (IS_STRICT_ANSI) {
				error(0x2012C, LEVEL_WARNING, $1);
			}
		}
	| parameter_list ',' ELLIPSIS
		{
			TreeNode* sp94;
			sp94 = make(Id_decl, $3, builtins[6]);
			sp94 = make(Declare_decl, $3, ellipsis, sp94);
			LIST_APPEND($$, sp94);
		}
	;

parameter_list
	: parameter_declaration
		{
			LIST_INIT($$, $1);
		}
	| parameter_list ',' parameter_declaration
		{
			LIST_APPEND($$, $3);
		}
	;

parameter_declaration
	: declaration_specifiers declarator
		{
			if ($2.unk_00 != NULL)	{
				delete_local_decls(depth);
                cur_lvl = link_pop(level_list);
                depth--;
			}
			$$ = make_topdecl($1.type, $1.type_attr, $1.type_spec, $2.unk_04, $1.location);
			cur_lvl->normal_ident = TRUE;
		}
	| declaration_specifiers
		{
			$$ = make_topdecl($1.type, $1.type_attr, $1.type_spec, NULL, $1.location);
			cur_lvl->type_ident_expected = TRUE;
			cur_lvl->normal_ident = TRUE;
		}
	| declaration_specifiers abstract_declarator
		{
			$$ = make_topdecl($1.type, $1.type_attr, $1.type_spec, $2, $1.location);
			cur_lvl->type_ident_expected = TRUE;
			cur_lvl->normal_ident = TRUE;
		}
	;

type_name
	: specifier_qualifier_list
		{
			$$ = make_topdecl($1.type, $1.type_attr, $1.type_spec, NULL, $1.location);
		}
	| specifier_qualifier_list abstract_declarator
		{
			$$ = make_topdecl($1.type, $1.type_attr, $1.type_spec, $2, $1.location);
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
			delete_local_decls(depth);
            cur_lvl = link_pop(level_list);
            depth--;
		}
	| fdecl_start parameter_type_list ')'
		{
			$$ = make(Func_type, $1, $2.first);
			delete_local_decls(depth);
            cur_lvl = link_pop(level_list);
            depth--;
		}
	| direct_abstract_declarator fdecl_start ')'
		{
			$$ = make(Func_type, $2, NULL);
			TYPE_PUSH_BACK($1, $$);
			$$ = $1;
			delete_local_decls(depth);
            cur_lvl = link_pop(level_list);
            depth--;
		}
	| direct_abstract_declarator fdecl_start parameter_type_list ')'
		{
			$$ = make(Func_type, $2, $3.first);
			TYPE_PUSH_BACK($1, $$);
			$$ = $1;
			delete_local_decls(depth);
            cur_lvl = link_pop(level_list);
            depth--;
		}
	;

typedef_name
	: TYPE_IDENT
		{
			cur_lvl->type_ident_expected = FALSE;
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
			if (depth == 0) {
				tree_handle = general_handle;
			}
		}
	;

initializer_list
	: initializer { LIST_INIT($$, $1); }
	| initializer_list ',' initializer
		{
			LIST_APPEND($$, $3);
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
	| typedef_name ':' { cur_lvl->type_ident_expected = TRUE; } statement
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
			delete_local_decls(depth);
            cur_lvl = link_pop(level_list);
            depth--;
		}
	| comp_start statement_list '}'
		{
			$$ = make(Compound_stmt, $1, NULL, $2.first, $3);
			delete_local_decls(depth);
            cur_lvl = link_pop(level_list);
            depth--;
		}
	| comp_start declaration_list '}'
		{
			$$ = make(Compound_stmt, $1, $2.first, NULL, $3);
			delete_local_decls(depth);
            cur_lvl = link_pop(level_list);
            depth--;
		}
	| comp_start declaration_list statement_list '}'
		{
			$$ = make(Compound_stmt, $1, $2.first, $3.first, $4);
			delete_local_decls(depth);
            cur_lvl = link_pop(level_list);
            depth--;
		}
	;

comp_start
	: '{'
		{
			if (cur_lvl->in_comp_expr) {
				cur_lvl = (ParseLevel*)get_link_elem(level_list);
				cur_lvl->type_ident_expected = TRUE;
				cur_lvl->in_struct_def = FALSE;				
				cur_lvl->normal_ident = TRUE;
				cur_lvl->link.next = level_list->used_list;
				level_list->used_list = &cur_lvl->link;
				depth++;
			}
			cur_lvl->normal_ident = TRUE;
			cur_lvl->in_comp_expr = TRUE;
			tree_handle = temp_handle;
		}
	;

declaration_list
	: declaration { LIST_INIT($$, $1); }
	| declaration_list declaration
		{
			LIST_APPEND($$, $2);
		}
	;

statement_list
	: statement { LIST_INIT($$, $1); }
	| statement_list statement
		{
			LIST_APPEND($$, $2);
		}
	| error { LIST_INIT($$, NULL);} 
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
			LIST_APPEND(B_10020F10, $1);
			if (temp_handle->current_region - temp_handle->list_start > options[OPTION_T_LEVEL]) {
				YYACCEPT;
			}
			parse_init();
		}
	| translation_unit external_definition
		{
			LIST_APPEND(B_10020F10, $2);
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
	| declaration_specifiers declarator { cur_lvl->normal_ident = TRUE; } function_body
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
			$$ = make_topdecl($1.type, $1.type_attr, $1.type_spec, $2.unk_04, $1.location);
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
	: translation_unit { /* do nothing */ }
	| { B_10020F10.first = make(End_of_file, -1); }
	;

%%
