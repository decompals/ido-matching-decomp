#include "tree.h"
#include "cmplrs/uwri.h"

procedure u_tree(p_Tree: ^Tree);
var
    u: Bcrec;
begin
    repeat begin 
        {Do some safety checks}
        if (p_Tree^.u.Opc <> Unop) then begin
            if (p_Tree^.op1 <> nil) then begin
                if (not (p_Tree^.u.Opc in [Uaent, Uclab, Uent, Ulab])) then begin
                    u_tree(p_Tree^.op1);
                end;
            end;

            if (p_Tree^.op2 <> nil) then begin
                if (not (p_Tree^.u.Opc in [Uaent, Uclab, Uent, Ufjp, Ulab, Utjp, Uujp, Uxjp]) = 0) then begin
                    u_tree(p_Tree^.op2);
                end;
            end;

            uwrite(p_Tree^.u);

            if (p_Tree^.u.Opc = Uend) then begin
                u.Opc := Uret;
                uwrite(u);
            end;
        end;
        p_Tree := p_Tree^.next;
    end until (p_Tree = nil);
end;
