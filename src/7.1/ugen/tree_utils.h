#ifndef TREE_UTILS_H
#define TREE_UTILS_H
procedure build_u(var u: Bcrec); external;
procedure build_u1(var u: Bcrec; op1: ^Tree); external;
procedure build_u2(var u: Bcrec; op1: ^Tree; op2: ^Tree); external;
function build_op(arg0: Uopcode): pointer; external;
procedure free_node(arg0: ^Tree); external;
procedure free_tree(t: ^tree); external;
procedure delete_statement(arg0: ^tree); external;
function ivalue(Dtype: Datatype; dwval_l: integer; dwval_h: integer): pointer; external;
function gen_label_id(): integer; external;
function new_tree(): pointer; external;
function build_1op(uopc: Uopcode; op: ^tree): pointer; external;
function build_2op(Opc: Uopcode; op1: ^tree; op2: ^tree): pointer; external;
function dup_tree(arg0 : ^tree): pointer; external;
function next_mark(): integer; external;
function dwvalue(Dtype: Datatype; arg1: integer64): pointer; external;
function rvalue(Dtype: Datatype; arg1: String): pointer; external;
function is_zero(arg0: ^Tree): boolean; external;
function is_ivalue(arg0: ^tree; arg1: integer; arg2: integer): boolean; external;
function result_type(arg0: ^Tree): Datatype; external;
function const_equal(arg0: ^Tree; arg1: ^Tree): boolean; external;
#endif /* TREE_UTILS_H */
