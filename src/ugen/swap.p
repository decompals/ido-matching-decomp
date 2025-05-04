#include "common.h"
#include "tree.h"

procedure swap_tree(var a: Ptree; var b: Ptree);
var
    temp: Ptree;
begin
    temp := a;
    a := b;
    b := temp;
end;

procedure swap_int(var a: integer; var b: integer);
var
    temp: integer;
begin
    temp := a;
    a := b;
    b := temp;
end;