#include "common.h"

var
	print_warnings: boolean;
	current_line: cardinal;
	debug_ugen: boolean;
	opcode_arch: boolean;
	glevel: u8;
	ignore_vreg: u8;
	olevel: u8;
	opt_cse: u8;
	opt_labels: boolean;
	opt_parms: u8;
	tail_call_opt: u8;

/* Special type for ugen */
type
ugen_err_string =  packed array [1..10] of char;



(* File variables *)
var
err_tab : array [first(ugen_report)..last(ugen_report)] of ugen_err_string := (
      "fix",
      "info",
      "warning",
      "error",
      "internal"
      );

errors: array [first(ugen_report)..last(ugen_report)] of integer; 

(* ! Unused *)
procedure reset_errors();
var
    i: ugen_report;
begin
    current_line := 0;

    for i := first(ugen_report) to last(ugen_report) do begin
        errors[i] := 0;
    end;
end;

(*
*  Reports an exception in ugen internals
*
*  @param error_kind    Kind of error to be printed (Fix, info, warn, etc..)
*  @param line          Line that is causing the exception in ugen
*  @param internal_file File where is located the exception
*  @param error         Exception message
*)
procedure report_error(error_kind: ugen_report; line: CARDINAL; internal_file: String; error: String); 
begin
    errors[error_kind] := succ(errors[error_kind]);

    if (error_kind <> Warn) or (print_warnings) then begin
        write(err, "ugen: ", err_tab[error_kind], 
        ": at your source line ", current_line:0, 
        " :  (ugen internal file ", internal_file:0, 
        ", line ", line:0, ")");
        writeln(err);
        write(err, "                ", error:0);
        writeln(err);
        flush(err);
    end;

    if ((error_kind = internal) and not (debug_ugen)) then begin
        halt(1);
    end;
end;

function has_errors(error_kind: cardinal): boolean;
begin
    if (error_kind >= cardinal(ord(Warn))) then begin
        return (errors[Internal] <> 0) and (errors[Warn] <> 0) and (errors[Error] <> 0 );
    end;
    return (errors[Internal] <> 0) and (errors[Error] <> 0);
end;

procedure assertion_error();
begin
    report_error(Internal, 79, 'report.p', 'Assertion failed');
end;
