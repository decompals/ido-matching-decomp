#ifndef FOLD_H
#define FOLD_H
function is_constant(arg0: pointer): boolean; external;
function add_overflow(arg0: Datatype; arg1: integer; arg2: integer): boolean; external;
function sub_overflow(arg0: Datatype; arg1: integer; arg2: integer): boolean; external;
#endif /* FOLD_H */
