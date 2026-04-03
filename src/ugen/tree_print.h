#ifndef TREE_PRINT_H
#define TREE_PRINT_H
procedure indent_tree(var f: Text; arg1: cardinal); external;
procedure print_ucode(var f: Text; var u: Bcrec); external;
procedure print_node_1(var f: Text; arg1: ^Tree; arg2: cardinal); external;
procedure print_node(var f: Text; arg1: ^Tree); external;
procedure print_tree(var f: Text; arg1: ^tree; arg2: cardinal; arg3: cardinal); external;
procedure debug_tree(arg0: ^tree); external;
#endif /* TREE_PRINT_H */

