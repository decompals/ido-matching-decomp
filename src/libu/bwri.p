#include "cmplrs/usys.h"
#include "cmplrs/ucode.h"

procedure uputinit(var ObjectName : Filename); external;
procedure uputint(i: integer); external;
procedure uputkill(); external;
procedure uputclose(); external;

(* Also used in ugen *)
#define SKIP_END_SPACES(len, line)  len := sizeof(line); \
    while ((len > 0) and (line[len] = ' ')) do begin  \
        len := len - 1; \
    end; \

var 
    dtyname: Array [first(Datatype)..last(Datatype)] of char;
    mtyname: Array [first(Memtype)..last(Memtype)] of char;
    noerrorsyet: boolean;
    u_indent: integer;
    Utab: extern array[first(Uopcode)..last(Uopcode)] of Utabrec;

procedure inituwrite(var fname: Filename);
begin
    noerrorsyet := true;
    uputinit(fname);
    
    dtyname[Cdt] := 'C';
    dtyname[Fdt] := 'F';
    dtyname[Gdt] := 'G';
    dtyname[Hdt] := 'H';

    dtyname[Cdt] := 'C';
    dtyname[Fdt] := 'F';
    dtyname[Gdt] := 'G';
    dtyname[Hdt] := 'H';
    dtyname[Zdt] := 'Z';
    dtyname[Adt] := 'A';
    dtyname[Jdt] := 'J';
    dtyname[Ldt] := 'L';
    dtyname[Mdt] := 'M';
    dtyname[Ndt] := 'N';
    dtyname[Pdt] := 'P';
    dtyname[Qdt] := 'Q';
    dtyname[Rdt] := 'R';
    dtyname[Sdt] := 'S';
    dtyname[Xdt] := 'X';
    dtyname[Idt] := 'I';
    dtyname[Kdt] := 'K';
    dtyname[Wdt] := 'W';

    mtyname[Zmt] := 'Z';
    mtyname[Mmt] := 'M';
    mtyname[Rmt] := 'R';
    mtyname[Smt] := 'S';
    mtyname[Pmt] := 'P';
    mtyname[Amt] := 'A';

    u_indent := 0;
end;

function idlen(var id: Identname): integer;
var 
    i: integer;
begin
    for i := 32 downto 1 do begin 
        if (id[i] <> ' ') then begin
            return i;
        end;
    end;
    return 0;
end;

function fnamelen(fname: Filename): integer;
var
    i: integer;
begin
    i := 0;
    
    while (i < 1024) do begin
        if (fname[i + 1] = ' ') then begin
            return i;
        end;
        i := i + 1;
    end;
    
    return Filenamelen;
end;

procedure uwrite(var u: Bcrec);
var
    i: integer;
    pad: integer;
    urec: UtabRec;
    strlength: integer;
    str: Stringtextptr;
begin
    if noerrorsyet then begin
        urec := utab[u.Opc];
        i := 1;
        while (i <> (urec.instlength + 1)) do begin
            uputint(u.Intarray[i]);
            uputint(u.Intarray[i +1]);
            i := i + 2;
        end;

        if (urec.hasconst) then begin
            uputint(u.Intarray[urec.instlength + 1]);
            uputint(u.Intarray[urec.instlength + 2]);
            if ((u.Dtype in [Mdt, Qdt, Rdt, Sdt, Xdt]) or (u.Opc = Ucomm)) then begin
                if (u.Opc = Uinit) then begin
                    strlength := (u.Initval.Ival + 3) div 4;
                end else begin
                    strlength := (u.Constval.Ival + 3) div 4;
                end;

                if (strlength & 1 <> 0) then begin
                    strlength := strlength + 1;
                end;

                if (u.Opc = Uinit) then begin
                    str := u.Initval.Chars;
                end else begin
                    str := u.Constval.Chars;
                end;

                i := 1;
                while (i <> (strlength+1)) do begin
                    uputint(str^.ssarray[i]);
                    uputint(str^.ssarray[i + 1]);
                    i := i + 2;
                end;
            end;
        end;
    end;
end;

function getdtyname(Dtyp: Datatype): char;
begin
    getdtyname := dtyname[Dtyp];
end;

function getmtyname(Mtyp: Memtype): char;
begin
    getmtyname := mtyname[Mtyp];
end;

procedure ucoid(Tag: Identname);
var
    i: integer;
    u: Bcrec;
begin
    for i := 1 to Maxinstlength do begin
        u.Intarray[i] := 0;
    end;

    new(u.Constval.Chars);
    
    SKIP_END_SPACES(u.Constval.Ival, Tag);

    for i := 1 to u.Constval.Ival do begin 
        u.Constval.Chars^.ss[i] := Tag[i];
    end;

    u.Opc := Ucomm;
    u.Dtype := Mdt;
    uwrite(u);
    dispose(u.Constval.Chars);
end;

procedure ucofname(fname: Filename);
var
    i: integer;
    u: Bcrec;
begin
    for i := 1 to Maxinstlength do begin    
        u.Intarray[i] := 0;
    end;

    new(u.Constval.Chars);
    u.Constval.Ival := fnamelen(fname);
    
    if (u.Constval.Ival >= 1025) then begin
        u.Constval.Ival := 1024;
    end;

    for i := 1 to u.Constval.Ival do begin 
        u.Constval.Chars^.ss[i] := fname[i];
    end;

    u.Opc := Ucomm;
    u.Dtype := Mdt;
    uwrite(u);
    dispose(u.Constval.Chars);
end;

procedure stopucode();
begin
    uputkill();
    noerrorsyet := false;
end;

procedure ubittobyte(var u: Bcrec);
begin
    if (u.Opc in [Uadj, Uisld, Uisst, Ulod, Umpmv, Upar, Updef, Upmov, Uregs, Urlda, Urpar, Ustr, Uvreg]) then begin
        u.Offset := u.Offset div 8;
        u.Length := u.Length div 8;
        return;
    end;

    if (u.Opc in [Uildv, Uilod, Uistr, Uistv, Urldc]) then begin
        u.I1 := u.I1 div 8;
        u.Length := u.Length div 8;
        return;
    end;

    if (u.Opc in [Uilda, Ulda, Urlod, Urstr]) then begin
        u.Offset := u.Offset div 8;
        u.Length := u.Length div 8;
        u.Offset2 := u.Offset2 div 8;
        return;
    end;

    if (u.Opc in [Uidx, Uixa]) then begin
        u.I1 := u.I1 div 8;
        return;
    end;

    if (u.Opc in [Udef, Udif, Ufill, Uiequ, Uigeq, Uigrt, Uileq, Uiles, Uineq, Uinn, Uint, Ulca, Uldc, Umov, Umus, Usdef, Usgs, Uuni]) then begin
        u.Length := u.Length div 8;
        return;
    end;

    if (u.Opc = Uinit) then begin
        u.Offset := u.Offset div 8;
        u.Length := u.Length div 8;
        u.Offset2 := u.Offset2 div 8;
        u.Constval.dwval_l := u.Constval.dwval_l div 8;
        return;
    end;

    if (u.Opc = Uoptn) and (u.I1 = 1) then begin
        u.Length := u.Length div 8;
        return;
    end;
end;

procedure set_u_indent(ident: integer);
begin
    {u_ident := ident} (* Guess *)
end;