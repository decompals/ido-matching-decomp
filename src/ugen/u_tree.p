#include "tree.h"
#include "cmplrs/uwri.h"

procedure u_tree(arg0: ^Tree);
var
    sp38: Bcrec;
begin
    repeat begin 
        {Do some safety checks}
        if (arg0^.u.Opc <> Unop) then begin
            if (arg0^.op1 <> nil) then begin
                if ((arg0^.u.Opc in [Uaent, Uclab, Uent, Ulab]) = 0) then begin
                    u_tree(arg0^.op1);
                end;
            end;

            if (arg0^.op2 <> nil) then begin
                if ((arg0^.u.Opc in [Uaent, Uclab, Uent, Ufjp, Ulab, Utjp, Uujp, Uxjp]) = 0) then begin
                    u_tree(arg0^.op2);
                end;
            end;

            uwrite(arg0^.u);

            if (arg0^.u.Opc = Uend) then begin
                sp38.opc := Uret;
                uwrite(sp38);
            end;
        end;
        arg0 := arg0^.next;
    end until (arg0 = nil);
end;
