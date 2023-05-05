#include "xmalloc.h"


var
    alloc_anchor : pointer;

procedure alloc_free(block: AllocBlock_ptr); 
begin
    block^.next := alloc_anchor;
    alloc_anchor := block;

    block^.size := abs(block^.size);
end;


