#include "cmplrs/usys.h"
#include "cmplrs/ucode.h"

{Functions called from C}
procedure ugetinit(var ObjectName : Filename); external;
procedure ugetclose(); external;
function ugetint(): integer; external;
function ugeteof(): integer; external;

var
    datachars: set of 'A'..'Z';
    dtytype: array ['A'..'Z'] of Datatype;
    memorychars: set of 'A'..'Z';
    mtytype: array ['A'..'Z'] of MemType;
    setconstantchars: set of '0'..'Z';

procedure resetur();
begin
    ugetclose();
end;

var
    Utab: extern array[first(Uopcode)..last(Uopcode)] of Utabrec;


procedure readuinstr(var u: Bcrec; strptr: stringtextptr);
var
    i: integer;
    instlength: integer; { sp58 }
    strlength: integer;
    urec: UtabRec; { sp41 (size 0x13) }
    pad: integer;

    procedure fix_infinity(var str: Filename; var len: integer); internal;
    begin
        if 
        ((len = 8)
            and (str[1] = 'I')
            and (str[2] = 'n')
            and (str[3] = 'f')
            and (str[4] = 'i')
            and (str[5] = 'n')
            and (str[6] = 'i')
            and (str[7] = 't')
            and (str[8] = 'y'))
        or ((len = 3)
            and (str[1] = 'i')
            and (str[2] = 'n')
            and (str[3] = 'f'))
        then begin
            str[1] := '9';
            str[2] := '9';
            str[3] := '.';
            str[4] := '9';
            str[5] := 'e';
            str[6] := '9';
            str[7] := '9';
            str[8] := '9';
            len := 8;
        end else if ((len = 9)
            and (str[1] = '-')
            and (str[2] = 'I')
            and (str[3] = 'n')
            and (str[4] = 'f')
            and (str[5] = 'i')
            and (str[6] = 'n')
            and (str[7] = 'i')
            and (str[8] = 't')
            and (str[9] = 'y'))
        or ((len = 4)
            and (str[1] = '-')
            and (str[2] = 'i')
            and (str[3] = 'n')
            and (str[4] = 'f'))
        then begin
            str[2] := '9';
            str[3] := '9';
            str[4] := '.';
            str[5] := '9';
            str[6] := 'e';
            str[7] := '9';
            str[8] := '9';
            str[9] := '9';
            len := 9;
        end;
    end;

begin
    if (ugeteof() = 1) then begin
        u.Opc := Ueof;
    end else begin
        u.Intarray[1] := ugetint();
        u.Intarray[2] := ugetint();
        urec := utab[u.Opc]; 
        instlength := urec.instlength;
        
        i := 3;
        while i <> instlength + 1 do begin
            u.Intarray[i] := ugetint();
            u.Intarray[i + 1] := ugetint();
            i := i + 2;
        end;

        if (urec.hasconst) then begin
            u.Intarray[instlength + 1] := ugetint();
            u.Intarray[instlength + 2] := ugetint();

            if ((u.Dtype in [Mdt, Qdt, Rdt, Sdt, Xdt]) or (u.Opc = Ucomm)) then begin
            
                strlength := (u.Intarray[instlength + 1] + 3) div 4;

                if ((strlength & 1) <> 0) then begin
                    strlength := strlength + 1;
                end;

                i := 1;
                while i <> strlength + 1 do begin
                    strptr^.ssarray[i] := ugetint();
                    strptr^.ssarray[i + 1] := ugetint();
                    i := i + 2;
                end;

                if ((u.Dtype in [Qdt, Rdt])) then begin
                    if (u.Opc <> Uinit) then begin
                        fix_infinity(strptr^.ss, u.Constval.Ival);
                    end else begin
                        fix_infinity(strptr^.ss, u.Initval.Ival);
                    end;
                end;

                if (u.Opc <> Uinit) then begin
                    u.Constval.Chars := strptr;
                end else begin
                    u.Initval.Chars := strptr;
                end;
            end;
        end;
    end;
end;

procedure initur(arg0: Filename);
begin
    ugetinit(arg0);
    datachars := ['A', 'C', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'W', 'X', 'Z'];    
    memorychars := ['A', 'M', 'P', 'R', 'S', 'Z'];
    setconstantchars := ['0'..'9', 'A'..'F'];
    
    dtytype['A'] := Adt;
    dtytype['C'] := Cdt;
    dtytype['F'] := Fdt;
    dtytype['G'] := Gdt;
    dtytype['H'] := Hdt;
    dtytype['I'] := Idt;
    dtytype['J'] := Jdt;
    dtytype['K'] := Kdt;
    dtytype['L'] := Ldt;
    dtytype['M'] := Mdt;
    dtytype['N'] := Ndt;
    dtytype['P'] := Pdt;
    dtytype['Q'] := Qdt;
    dtytype['R'] := Rdt;
    dtytype['S'] := Sdt;
    dtytype['W'] := Wdt;
    dtytype['X'] := Xdt;

    mtytype['Z'] := Zmt;
    mtytype['M'] := Mmt;
    mtytype['P'] := Pmt;
    mtytype['R'] := Rmt;
    mtytype['S'] := Smt;
    mtytype['A'] := Amt;
end;

{UNUSED}
procedure ubytetobit(var u: Bcrec);
begin
    if (u.Opc in [Uaent, Ubgnb, Ucia, Uclab, Uclbd, Uctrl, Ucubd, Ucup, Udef, Udup, Uendb, Uicuf, Ulab, Ulbdy, Ulbgn, Ulend, Uloc, Ultrm, Umst, Unop, Uret, Ustep, Uujp]) then begin
        u.Offset := u.Offset * 8;
        u.Length := u.Length * 8;
        return;
    end;
    

    if (u.Opc in [Uisst, Ustr]) then begin
        u.I1 := u.I1 * 8;
        u.Length := u.Length * 8;
        return;
    end;

    if (u.Opc in [Uisst, Ustr]) then begin
        u.Offset := u.Offset * 8;
        u.Length := u.Length * 8;
        u.Offset2 := u.Offset2 * 8;
        return;
    end;

    if (u.Opc = Uixa) then begin
        u.I1 := u.I1 * 8;
        return;
    end;

    if (u.Opc in [Uabs..Uirsv]) then begin
        u.Length := u.Length * 8;
        return;
    end;

    if (u.Opc = Uinit) then begin
        u.Offset := u.Offset * 8;
        u.Length := u.Length * 8;
        u.Offset2 := u.Offset2 * 8;
        u.Constval.dwval_l := u.Constval.dwval_l * 8;
        return;
    end;

    if (u.Opc = Uoptn) and (u.I1 = 1) then begin
        u.Length := u.Length * 8;
        return;
    end;
    
end;
