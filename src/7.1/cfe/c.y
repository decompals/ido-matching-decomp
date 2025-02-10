%{
#define YYMAXDEPTH 320

%}

%union {
     int intval;
	 char* stringval;
	 struct TokenIdentifier* token_identifier;
	 int force_alignment[4];
}

%token <token_identifier> IDENTIFIER
		SIZEOF ALIGNOF CLASSOF UNALIGN
%token <intval> STRING WSTRING
%token <intval> CONSTANT
%token	PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP
		LE_OP AND_OP OR_OP GE_OP NE_OP EQ_OP
		MUL_ASSIGN DIV_ASSIGN REM_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
		TYPEDEF EXTERN STATIC AUTO REGISTER
		CHAR SHORT INT LONG LONGLONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token <intval> STRUCT UNION
		ENUM
		ELLIPSIS
		TYPE_IDENT
		CASE DEFAULT IF ELSE SWITCH DO WHILE FOR
		GOTO LEAVE CONTINUE BREAK RETURN
		TRY EXCEPT FINALLY
		__PRAGMA
		'(' ')' '{' '}' '[' ']' '?' ':' '~' ',' ';'
%left   '+' '-'
%left   '/' '%'
%left 	'&' '|'
		'^' '!' '=' '*' '.' '<' '>'
		CLASS VIRTUAL PROTECTED PUBLIC PRIVATE COLONCOLON COLCOLSTART OPERATOR THIS MEMDOT_OP MEMPTR_OP NEW DELETE INLINE FRIEND

%type <intval> identifier
%type <intval> constant
%type <intval> string_literal
%type <intval> labeled_statement
%type <intval> selection_statement
%type <intval> expression_statement
%type <intval> jump_statement
%type <intval> compound_statement
%type <intval> iteration_statement
%type <intval> try_statement
%type <intval> translation_unit
%type <intval> primary_expression
%type <intval> postfix_expression
%type <intval> argument_expression_list
%type <intval> unary_expression
%type <intval> unary_operator
%type <intval> cast_expression
%type <intval> multiplicative_expression
%type <intval> additive_expression
%type <intval> shift_expression
%type <intval> relational_expression
%type <intval> equality_expression
%type <intval> AND_expression
%type <intval> exclusive_OR_expression
%type <intval> inclusive_OR_expression
%type <intval> logical_AND_expression
%type <intval> logical_OR_expression
%type <intval> conditional_expression
%type <intval> assignment_expression
%type <intval> assignment_operator
%type <intval> expression
%type <intval> constant_expression
%type <intval> declaration
%type <intval> top_declaration
%type <intval> declaration_specifiers
%type <intval> init_declarator_list
%type <intval> init_declarator
%type <intval> storage_class_specifier
%type <intval> fct_specifier
%type <intval> type_specifier
%type <intval> struct_or_union_specifier
%type <intval> struct_or_union
%type <intval> struct_declaration_list_semi
%type <intval> struct_declaration_list
%type <intval> struct_declaration
%type <intval> specifier_qualifier_list
%type <intval> struct_declarator_list
%type <intval> struct_declarator
%type <intval> enum
%type <intval> enum_specifier
%type <intval> enumerator_list
%type <intval> enumerator
%type <intval> type_qualifier
%type <intval> declarator
%type <intval> direct_declarator
%type <intval> pointer
%type <intval> type_qualifier_list
%type <intval> identifier_list
%type <intval> identifier_or_constant_list
%type <intval> parameter_type_list
%type <intval> parameter_list
%type <intval> parameter_declaration
%type <intval> type_name
%type <intval> abstract_declarator
%type <intval> direct_abstract_declarator
%type <intval> initializer
%type <intval> initializer_list
%type <intval> statement
%type <intval> declaration_list
%type <intval> statement_list
%type <intval> external_definition
%type <intval> function_definition
%type <intval> function_body
%type <intval> optcomma
%type <intval> build_program_tree
%type <intval> typedef_name
%type <intval> fdecl_start
%type <intval> comp_start

%start build_program_tree
%%

identifier
	: IDENTIFIER { 
		if (debug_arr[0x79]) {
			fprintf(dbgout, "IDENT=%s, was_typedef=%d\n", $1->unk_04->unk_18, $1->unk_00);
		}
		$$ = make(0, $1->unk_08, $1->unk_04);
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
	| postfix_expression '[' expression ']' { $$ = make(0x49, $1, $3); }
	| postfix_expression '(' argument_expression_list ')' { $$ = make(0x41, $2, $3, make(0x5D, $1)); }
	| postfix_expression '(' ')' { $$ = make(0x41, $2, $3, NULL); }
	| postfix_expression '.' { cur_lvl->unk_04 = 0; } identifier { $$ = make(0x5F, $1); cur_lvl->unk_04 = 1; }
	| postfix_expression PTR_OP { $$ = make(0x41); } identifier { $$ = make(0x41); }
	| postfix_expression INC_OP { $$ = make(0x41); }
	| postfix_expression DEC_OP { $$ = make(0x41); }
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression { $$ = make(0x41); }
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression { $$ = make(0x41); }
	| DEC_OP unary_expression { $$ = make(0x41); }
	| unary_operator cast_expression { $$ = make(0x41); }
	| '&' ELLIPSIS { $$ = make(0x41); }
	| SIZEOF unary_expression { $$ = make(0x41); }
	| SIZEOF '(' type_name { $$ = make(0x41); } ')' { $$ = make(0x41); }
	| ALIGNOF unary_expression { $$ = make(0x41); }
	| ALIGNOF '(' type_name { $$ = make(0x41); } ')' { $$ = make(0x41); }
	| CLASSOF unary_expression { $$ = make(0x41); }
	| CLASSOF '(' type_name { $$ = make(0x41); } ')' { $$ = make(0x41); }
	;

unary_operator
	: '&' { $$ = make(0x41); }
	| '*' { $$ = make(0x41); }
	| '+' { $$ = make(0x41); }
	| '-' { $$ = make(0x41); }
	| '~' { $$ = make(0x41); }
	| '!' { $$ = make(0x41); }
	;

cast_expression
	: unary_expression
	| '(' type_name { $$ = make(0x41); } ')' cast_expression { $$ = make(0x41); }
	| DEC_OP '(' type_name { $$ = make(0x41); } ')' cast_expression { $$ = make(0x41); }
	| INC_OP '(' type_name { $$ = make(0x41); } ')' cast_expression { $$ = make(0x41); }
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression { $$ = make(0x41); }
	| multiplicative_expression '/' cast_expression { $$ = make(0x41); }
	| multiplicative_expression '%' cast_expression { $$ = make(0x41); }
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression { $$ = make(0x41); }
	| additive_expression '-' multiplicative_expression { $$ = make(0x41); }
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression { $$ = make(0x41); }
	| shift_expression RIGHT_OP additive_expression { $$ = make(0x41); }
	;

relational_expression
	: shift_expression
	| relational_expression LE_OP shift_expression { $$ = make(0x41); }
	| relational_expression GE_OP shift_expression { $$ = make(0x41); }
	| relational_expression '<' shift_expression { $$ = make(0x41); }
	| relational_expression '>' shift_expression { $$ = make(0x41); }
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression { $$ = make(0x41); }
	| equality_expression NE_OP relational_expression { $$ = make(0x41); }
	;

AND_expression
	: equality_expression
	| AND_expression '&' equality_expression { $$ = make(0x41); }
	;

exclusive_OR_expression
	: AND_expression
	| exclusive_OR_expression '^' AND_expression { $$ = make(0x41); }
	;

inclusive_OR_expression
	: exclusive_OR_expression
	| inclusive_OR_expression '|' exclusive_OR_expression { $$ = make(0x41); }
	;

logical_AND_expression
	: inclusive_OR_expression
	| logical_AND_expression AND_OP inclusive_OR_expression { $$ = make(0x41); }
	;

logical_OR_expression
	: logical_AND_expression
	| logical_OR_expression OR_OP logical_AND_expression { $$ = make(0x41); }
	;

conditional_expression
	: logical_OR_expression
	| logical_OR_expression '?' expression ':' conditional_expression { $$ = make(0x41); }
	;

assignment_expression
	: conditional_expression
	| cast_expression assignment_operator assignment_expression { $$ = make(0x41); }
	;

assignment_operator
	: '=' { $$ = make(0x41); }
	| MUL_ASSIGN { $$ = make(0x41); }
	| DIV_ASSIGN { $$ = make(0x41); }
	| REM_ASSIGN { $$ = make(0x41); }
	| ADD_ASSIGN { $$ = make(0x41); }
	| SUB_ASSIGN { $$ = make(0x41); }
	| LEFT_ASSIGN { $$ = make(0x41); }
	| RIGHT_ASSIGN { $$ = make(0x41); }
	| AND_ASSIGN { $$ = make(0x41); }
	| XOR_ASSIGN { $$ = make(0x41); }
	| OR_ASSIGN { $$ = make(0x41); }
	;

expression
	: assignment_expression
	| expression ',' assignment_expression { $$ = make(0x41); }
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers init_declarator_list ';' { $$ = make(0x41); }
	| declaration_specifiers ';' { $$ = make(0x41); }
	;

top_declaration
	: declaration_specifiers init_declarator_list ';' { $$ = make(0x41); }
	| declaration_specifiers ';' { $$ = make(0x41); }
	| init_declarator_list ';' { $$ = make(0x41); }
	;

declaration_specifiers
	: storage_class_specifier
	| type_specifier
	| type_qualifier
	| declaration_specifiers storage_class_specifier { $$ = make(0x41); }
	| declaration_specifiers type_specifier { $$ = make(0x41); }
	| declaration_specifiers type_qualifier { $$ = make(0x41); }
	| fct_specifier
	| declaration_specifiers fct_specifier { $$ = make(0x41); }
	;

fct_specifier
	: INLINE { $$ = make(0x41); }

init_declarator_list
	: init_declarator { $$ = make(0x41); }
	| init_declarator_list ',' { $$ = make(0x41); } init_declarator { $$ = make(0x41); }
	;

init_declarator
	: declarator { $$ = make(0x41); } 
	| declarator '=' initializer { $$ = make(0x41); }
	;

storage_class_specifier
	: TYPEDEF { $$ = make(0x41); }
	| EXTERN { $$ = make(0x41); }
	| STATIC { $$ = make(0x41); }
	| AUTO { $$ = make(0x41); }
	| REGISTER { $$ = make(0x41); }
	;

type_specifier
	: CHAR { $$ = make(0x41); }
	| SHORT { $$ = make(0x41); }
	| INT { $$ = make(0x41); }
	| LONG { $$ = make(0x41); }
	| LONGLONG { $$ = make(0x41); }
	| SIGNED { $$ = make(0x41); }
	| UNSIGNED { $$ = make(0x41); }
	| FLOAT { $$ = make(0x41); }
	| DOUBLE { $$ = make(0x41); }
	| VOID { $$ = make(0x41); }
	| struct_or_union_specifier { $$ = make(0x41); }
	| enum_specifier { $$ = make(0x41); }
	| typedef_name { $$ = make(0x41); }
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' { $$ = make(0x41); } struct_declaration_list_semi '}' { $$ = make(0x41); }
	| struct_or_union '{' { $$ = make(0x41); } struct_declaration_list_semi '}' { $$ = make(0x41); }
	| struct_or_union IDENTIFIER { $$ = make(0x41); }
	;

struct_or_union
	: STRUCT { $$ = make(0x41); }
	| UNION { $$ = make(0x41); }
	;

struct_declaration_list_semi
	: struct_declaration_list { $$ = make(0x41); } 
	| struct_declaration_list ';'
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list ';' struct_declaration { $$ = make(0x41); }
	;

struct_declaration
	: specifier_qualifier_list { $$ = make(0x41); } struct_declarator_list { $$ = make(0x41); }
	;

specifier_qualifier_list
	: type_specifier
	| type_qualifier
	| specifier_qualifier_list type_specifier { $$ = make(0x41); }
	| specifier_qualifier_list type_qualifier { $$ = make(0x41); }
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' { $$ = make(0x41); } struct_declarator { $$ = make(0x41); }
	;

struct_declarator
	: declarator { $$ = make(0x41); }
	| ':' { $$ = make(0x41); } constant_expression { $$ = make(0x41); }
	| declarator ':' constant_expression { $$ = make(0x41); }
	| { $$ = make(0x41); }
	;

enum_specifier
	: enum { $$ = make(0x41); } '{' enumerator_list optcomma '}' { $$ = make(0x41); }
	| enum IDENTIFIER { $$ = make(0x41); } '{' enumerator_list optcomma '}' { $$ = make(0x41); }
	| enum IDENTIFIER { $$ = make(0x41); }
	;

optcomma
	: { $$ = make(0x41); }
	| ','
	;

enum
	: ENUM { $$ = make(0x41); }
	;

enumerator_list
	: enumerator { $$ = make(0x41); }
	| enumerator_list ',' enumerator { $$ = make(0x41); }
	;

enumerator
	: IDENTIFIER { $$ = make(0x41); }
	| IDENTIFIER '=' constant_expression { $$ = make(0x41); }
	;

type_qualifier
	: CONST { $$ = make(0x41); }
	| VOLATILE { $$ = make(0x41); }
	| UNALIGN { $$ = make(0x41); }
	;

declarator
	: direct_declarator
	| pointer direct_declarator { $$ = make(0x41); }
	;

direct_declarator
	: IDENTIFIER { $$ = make(0x41); }
	| '(' declarator ')' { $$ = make(0x41); }
	| direct_declarator '[' ']' { $$ = make(0x41); }
	| direct_declarator '[' constant_expression ']' { $$ = make(0x41); }
	| direct_declarator fdecl_start ')' { $$ = make(0x41); }
	| direct_declarator fdecl_start parameter_type_list ')' { $$ = make(0x41); }
	| direct_declarator fdecl_start identifier_list ')' { $$ = make(0x41); }
	;

fdecl_start
	: '(' { $$ = make(0x41); }
	;

pointer
	: '*' { $$ = make(0x41); }
	| '*' type_qualifier_list { $$ = make(0x41); }
	| '*' pointer { $$ = make(0x41); }
	| '*' type_qualifier_list pointer { $$ = make(0x41); }
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier { $$ = make(0x41); }
	;

identifier_list
	: identifier { $$ = make(0x41); }
	| identifier_list ',' identifier { $$ = make(0x41); }
	;

identifier_or_constant_list
	: identifier { $$ = make(0x41); }
	| CONSTANT { $$ = make(0x41); }
	| identifier_list ',' identifier { $$ = make(0x41); }
	| identifier_list ',' CONSTANT { $$ = make(0x41); }
	;

parameter_type_list
	: parameter_list
	| ELLIPSIS { $$ = make(0x41); }
	| parameter_list ',' ELLIPSIS { $$ = make(0x41); }
	;

parameter_list
	: parameter_declaration { $$ = make(0x41); }
	| parameter_list ',' parameter_declaration { $$ = make(0x41); }
	;

parameter_declaration
	: declaration_specifiers declarator { $$ = make(0x41); }
	| declaration_specifiers { $$ = make(0x41); }
	| declaration_specifiers abstract_declarator { $$ = make(0x41); }
	;

type_name
	: specifier_qualifier_list { $$ = make(0x41); }
	| specifier_qualifier_list abstract_declarator { $$ = make(0x41); }
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator { $$ = make(0x41); }
	;

direct_abstract_declarator
	: '(' abstract_declarator ')' { $$ = make(0x41); }
	| '[' ']' { $$ = make(0x41); }
	| '[' constant_expression ']' { $$ = make(0x41); }
	| direct_abstract_declarator '[' ']' { $$ = make(0x41); }
	| direct_abstract_declarator '[' constant_expression ']' { $$ = make(0x41); }
	| fdecl_start ')' { $$ = make(0x41); }
	| fdecl_start parameter_type_list ')' { $$ = make(0x41); }
	| direct_abstract_declarator fdecl_start ')' { $$ = make(0x41); }
	| direct_abstract_declarator fdecl_start parameter_type_list ')' { $$ = make(0x41); }
	;

typedef_name
	: TYPE_IDENT { $$ = make(0x41); }
	;

initializer
	: assignment_expression
	| '{' { $$ = make(0x41); } initializer_list optcomma '}' { $$ = make(0x41); }
	;

initializer_list
	: initializer { $$ = make(0x41); }
	| initializer_list ',' initializer { $$ = make(0x41); }
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
	: IDENTIFIER ':' statement { $$ = make(0x41); }
	| typedef_name ':' { $$ = make(0x41); } statement { $$ = make(0x41); }
	| CASE constant_expression ':' statement { $$ = make(0x41); }
	| DEFAULT ':' statement { $$ = make(0x41); }
	;

compound_statement
	: comp_start '}' { $$ = make(0x41); }
	| comp_start statement_list '}' { $$ = make(0x41); }
	| comp_start declaration_list '}' { $$ = make(0x41); }
	| comp_start declaration_list statement_list '}' { $$ = make(0x41); }
	;

comp_start
	: '{' { $$ = make(0x41); }
	;

declaration_list
	: declaration { $$ = make(0x41); }
	| declaration_list declaration { $$ = make(0x41); }
	;

statement_list
	: statement { $$ = make(0x41); }
	| statement_list statement { $$ = make(0x41); }
	| error { printf("WTF IS ERROR"); } 
	| statement_list error
	;

expression_statement
	: ';' { $$ = make(0x41); }
	| expression ';' { $$ = make(0x41); }
	;

selection_statement
	: IF '(' expression ')' statement { $$ = make(0x41); }
	| IF '(' expression ')' statement ELSE statement { $$ = make(0x41); }
	| SWITCH '(' expression ')' statement { $$ = make(0x41); }
	;

iteration_statement
	: WHILE '(' expression ')' statement { $$ = make(0x41); }
	| DO statement WHILE '(' expression ')' ';' { $$ = make(0x41); }
	| FOR '(' ';' ';' ')' statement { $$ = make(0x41); }
	| FOR '(' ';' ';' expression ')' statement { $$ = make(0x41); }
	| FOR '(' ';' expression ';' ')' statement { $$ = make(0x41); }
	| FOR '(' ';' expression ';' expression ')' statement { $$ = make(0x41); }
	| FOR '(' expression ';' ';' ')' statement { $$ = make(0x41); }
	| FOR '(' expression ';' ';' expression ')' statement { $$ = make(0x41); }
	| FOR '(' expression ';' expression ';' ')' statement { $$ = make(0x41); }
	| FOR '(' expression ';' expression ';' expression ')' statement { $$ = make(0x41); }
	;

jump_statement
	: GOTO IDENTIFIER ';' { $$ = make(0x41); }
	| CONTINUE ';' { $$ = make(0x41); }
	| BREAK ';' { $$ = make(0x41); }
	| RETURN ';' { $$ = make(0x41); }
	| RETURN expression ';' { $$ = make(0x41); }
	| LEAVE ';' { $$ = make(0x41); }
	;

try_statement
	: TRY compound_statement EXCEPT '(' expression ')' compound_statement { $$ = make(0x41); }
	| TRY compound_statement FINALLY compound_statement { $$ = make(0x41); }

translation_unit
	: external_definition { $$ = make(0x41); }
	| translation_unit external_definition { $$ = make(0x41); }
	;

external_definition
	: function_definition
	| top_declaration
	| ';' { $$ = make(0x41); }
	| error { $$ = make(0x41); }
	| __PRAGMA '(' CONSTANT ',' identifier_or_constant_list ')' ';' { $$ = make(0x41); }
	| __PRAGMA '(' CONSTANT ')' ';' { $$ = make(0x41); }
	;

function_definition
	: declarator function_body { $$ = make(0x41); }
	| declaration_specifiers declarator { $$ = make(0x41); } function_body { $$ = make(0x41); }
	;

function_body
	: compound_statement
	| declaration_list compound_statement { $$ = make(0x41); }

build_program_tree
	: translation_unit { $$ = make(0x41); }
	| { B_10020F10.unk_00 = make(0x66, -1); }
	;

%%
