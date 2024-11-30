#include "common.h"
#include "ugen.h"

/* Special type for ugen */
type
ugen_err_string =  packed array [1..10] of char;

/* File variables */
var
err_tab : array [0..5] of ugen_err_string := (
      "fix\0", "info\0", "warning\0", "error\0", "internal\0", "\0"
      );
errors: array [0..16#20] of integer;

(* ! Unused *)
procedure reset_errors();
var
    i: integer;
begin
    current_line := 0;

    for i := 0 to 4 do begin
        errors[i] := 0;
    end;
end;

(*
*  Reports an exception in ugen internals
*
*  @param: error_kind    Kind of error to be printed (Fix, info, warn, etc..)
*  @param: line          Line that is causing the exception in ugen
*  @param: internal_file File where is located the exception
*  @param: error         Exception message
*)
procedure report_error(error_kind: u8; line: CARDINAL; internal_file: String; error: String); 
begin
    errors[error_kind] := errors[error_kind]+1;

    if (error_kind <> 2) or (print_warnings) then begin
        write(err, "ugen: ", err_tab[error_kind], 
        ": at your source line ", current_line:0, 
        " :  (ugen internal file ", internal_file:0, 
        ", line ", line:0, ")");
        writeln(err);
        write(err, "                ", error:0);
        writeln(err);
        flush(err);
    end;

    if ((addr(errors[4]) = addr(errors[error_kind])) and not (debug_ugen)) then begin
        halt(1);
    end;
end;

function has_error(arg0: cardinal): boolean;
begin
    if (arg0 >= 2) then begin
        return (errors[4] <> 0) and (errors[2] <> 0) and (errors[3] <> 0 );
    end;
    return (errors[4] <> 0) and (errors[3] <> 0);
end;

procedure assertion_error();
begin
    report_error(4, 79, "Assertion failed", "report.p");
end;
