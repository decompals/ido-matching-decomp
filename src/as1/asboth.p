#include "common_p.h"

type
    PageTag = (PAGE_TAG_STRING, PAGE_TAG_BYTES);
    CString = record
        pChar: ^char;
    end;

var
    {Global stuff }
    NoWarnFlag: boolean;
    Severity: ErrorLevel;
    WarnExitFlag: Boolean;
    doing_info: boolean;
    recursion: boolean;
    mscoff: boolean;
    mscoff1: boolean;

    { TODO: Migrate this data }
    opt_strings : array [options] of Identname;
    sev_string: array [ErrorLevel] of IdentName;

function e_addr(var arg0 : String): pointer; external;
function strncmp(arg0: ^String; var arg1: String; n: integer): integer; external;
procedure perror(arg0: ^st_string); external;
function memset(p: pointer; value: integer; size: cardinal): pointer; external;
function xrealloc (fptr : pointer; fsize : integer) : pointer; external;
procedure new_error(); external;

procedure null_terminate(arg0: GString);
var
#line 4
    i: integer;
begin
    for i := 1 to 1024 do begin
        if (arg0.f^[i] = ' ') then begin
            arg0.f^[i] := chr(0);
            return;
        end;
    end;
end;

function eindex(var s: error_str): integer;
var
    i: integer;
    strEnd: integer;
begin
    strEnd := 1;
    for i := 80 downto strEnd do begin
        if (s[i] <> ' ') then begin
            return i;
        end;
    end;
    return 80;
end;

procedure name_and_line(arg0: GString; arg1: ErrorLevel);
  begin
      if (verbose) then begin
          if (arg1 <> ErrorLevel_3) then begin
              if (doing_info) then begin
                  writeln(err);
                  doing_info := false;
              end;
          end else if (doing_info) then begin
              return
          end;
      end;

      severity := min(severity, arg1);

      if (arg1 <> ErrorLevel_3) then begin
          write(err, 'as1: ');
      end;

      if (arg1 = ErrorLevel_1) then begin
          debugflag := 0;
      end else if (arg1 = ErrorLevel_3) then begin
          doing_info := true;
          return
      end;

      write(err, sev_string[arg1]:strlen(l_addr(sev_string[arg1])));
      write(err, ': ');

      if (arg0.f^[1] <> chr(0)) then begin
          write(err, arg0.f^:strlen(arg0.f));
      end;

      write(err, ', line ', currentline:1, ': ');
  end;

procedure get_filename(var arg0: GString);
begin
    if (recursion) then begin
        arg0 := emptystring;
        return;
    end;

    recursion := true;

    if (mscoff) or (mscoff1) then begin
        arg0 := emptystring;
    end else if (currentfile <> EOF) then begin
        arg0.st := st_str_idn(currentfile);
    end else begin
        arg0 := emptystring;
    end;
    recursion := false;
end;

procedure call_name_and_line(arg0: ErrorLevel); \
var \
    sp24 : GString; \
begin \
    get_filename(sp24);
    name_and_line(sp24, arg0);
end;

procedure call_perror(arg0: ErrorLevel; arg1: GString);
begin
    call_name_and_line(arg0);
    perror(arg1.st);
    flush(err);
end;

procedure new_error();
#line 1
begin
    call_perror(ErrorLevel_1, emptystring);
    flush(err);
end;

procedure PostError(error: error_str; arg1: GString; level: ErrorLevel);
var
    sp24: GString;
begin
    if WarnExitFlag then
        severity := Min(severity, level);
    if (level < ErrorLevel_2) or not NoWarnFlag then begin
        get_filename(sp24);
        name_and_line(sp24, level);
        Write(err, error:EIndex(error));
        if (arg1.f^[1] <> chr(0)) then begin
            WriteLn(err, '??', arg1.f^:strlen(arg1.f));
        end else begin
            WriteLn(err);
        end;
    end;
end;

procedure p_assertion_failed(arg0: String; arg1: error_str; arg3: integer); \
var \
    sp2C : GString; \
begin \
    get_filename(sp2C);
    name_and_line(sp2C, ErrorLevel_0);

    write(err, arg1:eindex(arg1));
    write(err, ', line ', arg3:1);
    write(err, ': ');
    writeln(err);

    if (arg0[1] <> chr(0)) then begin
        writeln(err, arg0:strlen(e_addr(arg0)));
    end;
    flush(err);
end;

procedure assertion_failed(arg0: GString; arg1: GString; arg2: integer); \
var  \
    sp24 : GString; \
begin \
    get_filename(sp24);
    name_and_line(sp24, ErrorLevel_0);
    write(err, arg1.f^:strlen(arg1.f));
    write(err, ", line ", arg2:1);
    writeln(err, " :");

    if arg0.f^[1] <> chr(0) then begin
        write(err, '   assertion ( ', arg0.f^:strlen(arg0.f));
        write(err, ') failed');
        writeln(err)
    end;
end;

procedure postcerror(arg0: GString; arg1: ErrorLevel);
var
    sp24 : GString;
begin
    get_filename(sp24);
    name_and_line(sp24, arg1);
    if arg0.f^[1] <> chr(0) then begin
        writeln(err, arg0.f^:strlen(arg0.f));
    end;
end;

function negative_file_opt(arg0: GString): boolean;
var
    str: String;
begin
    str := "---";

    str[4] := chr(0);
    if (strncmp(arg0.s, str, 3) = 0) then begin
        return true;
    end;

    return false;
end;

function which_opt(arg0: GString): options; \
var \
    i: options; \
begin \
    for i := first(options) to options(109) do begin {TODO: Some options are missing! }
        if (strcmp(arg0.s, l_addr(opt_strings[i])) = 0) then begin
            return i;
        end;
    end;

    return options(109);
end;


procedure get_lstring(arg0: integer; arg1: GString);
#line 1
begin
    argv(arg0, arg1.o^);
    arg1.o^[32] := ' ';
    null_terminate(arg1);
end;

procedure get_sstring(arg0: integer; arg1: GString);
#line 1
begin
    argv(arg0, arg1.f^);
    arg1.f^[1024] := ' ';
    null_terminate(arg1);
end;

function grow_array(var capacity_count: cardinal; new_count: integer; width: cardinal; ptr: pointer; clear_mem: boolean): pointer;
var
    pad: pointer;
    new_ptr: pointer;
    old_size: cardinal;
    new_size: cardinal;
begin
#line 1
    if (capacity_count = 0) then begin
        if (new_count >= 1024) then begin
            capacity_count := new_count + 1;
        end else begin
            capacity_count := 1024;
        end;

        new_size := capacity_count * width;
        new_ptr := xmalloc(new_size);
        if (new_ptr = nil) then begin
            new_error();
        end else if (clear_mem) then begin
            new_ptr := memset(new_ptr, 0, new_size);
        end;
    end else begin
        old_size := width * capacity_count;
        capacity_count := capacity_count * 2;
        if (cardinal(new_count) >= capacity_count) then begin
            capacity_count := new_count + 1;
        end;

        new_size := capacity_count * width;
        new_ptr := xrealloc(ptr, new_size);
        if (new_ptr = nil) then begin
            new_error();
        end else if (clear_mem) then begin
            pad := memset(pointer(integer(new_ptr) + integer(old_size)), 0, new_size - old_size);
        end;
    end;
    return new_ptr;
end;

function grow_array_size(var capacity_count: integer; new_count: integer; width: integer; ptr: pointer; clear_mem: boolean): pointer;
var
    pad: pointer;
    new_ptr: pointer;
    new_size: integer;
    old_size: integer;
begin

    if (capacity_count = 0) then begin
        new_size := (new_count + 1) * width;
        capacity_count := (new_count + 1);
        new_ptr := xmalloc(new_size);
        if (new_ptr = nil) then begin
            new_error();
        end else if (clear_mem) then begin
            new_ptr := memset(new_ptr, 0, new_size);
        end;
    end else begin
        new_size := width * capacity_count;
        capacity_count := capacity_count + new_count;
        old_size := capacity_count * width;
        new_ptr := xrealloc(ptr, old_size);
        if (new_ptr = nil) then begin
            new_error();
        end else if (clear_mem) then begin
            pad := memset(pointer(integer(new_ptr) + integer(new_size)), 0, old_size - new_size);
        end;
    end;

    return new_ptr;
end;
