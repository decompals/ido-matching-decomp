#include "common.h"
#include "ugen.h"
#line 22 "opt.p"
procedure set_opts(arg0: u8; arg1: u8);
begin
    glevel := arg1;
    olevel := arg0;
    if (arg1 = 2) and (arg0 >= 2) then begin
        arg0 := 1;
    end;
    case arg0 of
    0:
    begin
        opt_cse := 1;
        opt_labels := false;
        opt_parms := 1;
        ignore_vreg := 0;
        tail_call_opt := 0;
    end;
    1:
        begin
        if (arg1 = 0) or (arg1 = 3) then begin
            opt_cse := 2;
        end else begin
            opt_cse := 1;
        end;
     
        opt_labels := (arg1 = 0) or (arg1 = 3);
        opt_parms := 1;
        ignore_vreg := 0;
        tail_call_opt := 0;
        end;
    2,
    3,
    4:
        begin
        if (arg1 = 0) or (arg1 = 3) then begin
            opt_cse := 2;
        end else begin
            opt_cse := 1;
        end;
  
        opt_labels := (arg1 = 0) or (arg1 = 3);
        opt_parms := 0;
        ignore_vreg := 1;
        if (arg0 >= 3) and (tail_call_opt <> 0) then begin
            tail_call_opt := 1;
        end else
            tail_call_opt := 0;
        end;
    end;
end;

