#include "common.h"

var
    print_warnings: boolean;
    current_line: cardinal;
    glevel: DebugLevels;
    ignore_vreg: boolean;
    olevel: OptLevels;
    opt_cse: u8;
    opt_labels: boolean;
    opt_parms: boolean;
    tail_call_opt: boolean;


(*
*  Decides the different optimizations that ugen will use during the codegen processs
*
*  @param optLevel   Optimization level (see OptLevels)
*  @param debugLevel Debug level (see DebugLevels)
*)
#line 21 "opt.p"
procedure set_opts(optLevel: OptLevels; debugLevel: DebugLevels);
begin
    glevel := debugLevel;
    olevel := optLevel;
    if (debugLevel = DEBUG_LEVEL_g2) and (optLevel >= OPT_LEVEL_O2) then begin
        optLevel := OPT_LEVEL_O1;
    end;

    { Required to match }
    case ord(optLevel) of
        ord(OPT_LEVEL_O0):
        begin
            opt_cse := 1;
            opt_labels := false;
            opt_parms := true;
            ignore_vreg := false;
            tail_call_opt := false;
        end;
        ord(OPT_LEVEL_O1):
        begin
            if (debugLevel = DEBUG_LEVEL_g0) or (debugLevel = DEBUG_LEVEL_g3) then begin
                opt_cse := 2;
            end else begin
                opt_cse := 1;
            end;

            opt_labels := (debugLevel = DEBUG_LEVEL_g0) or (debugLevel = DEBUG_LEVEL_g3);
            opt_parms := true;
            ignore_vreg := false;
            tail_call_opt := false;
        end;
        ord(OPT_LEVEL_O2),
        ord(OPT_LEVEL_O3),
        ord(OPT_LEVEL_O4):
        begin
            if (debugLevel = DEBUG_LEVEL_g0) or (debugLevel = DEBUG_LEVEL_g3) then begin
                opt_cse := 2;
            end else begin
                opt_cse := 1;
            end;

            opt_labels := (debugLevel = DEBUG_LEVEL_g0) or (debugLevel = DEBUG_LEVEL_g3);
            opt_parms := false;
            ignore_vreg := true;
            if (optLevel >= OPT_LEVEL_O3) and (tail_call_opt) then begin
                tail_call_opt := true;
            end else begin
                tail_call_opt := false;
            end;
        end;
    end;
end;
