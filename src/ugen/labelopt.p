#include "common.h"
#include "report.h"
#include "tree.h"
#include "loop_header.h"
#include "tree_print.h"
#include "tree_utils.h"

type
    { Tree header? }
    Punk = ^unk_record;
    unk_record = Packed Record;
        op1: ^tree;
        op2: ^tree;
        prior: ^tree;
        next: ^tree;
    end;



{ From loop_header.p }
procedure labelopt(arg0: ^Tree; var pFile: Text; debugPhases: boolean; cross_jumping_opt: boolean);
var
    mark: integer;
    mark1: integer;

    procedure func_004351C0(arg0: ^Tree);
    var
        var_s0: ^Tree;
    begin
        var_s0 := arg0^.next;
        while (not (var_s0^.u.Opc in [Uaent, Ubgn, Uclab, Uend, Uent, Ueof, Ulab, Ustp])) do begin
            if (not (var_s0^.u.Opc in [Ubgnb, Ucomm, Udef, Uendb, Ulex, Uoptn, Usdef, Uunal])) then begin
                delete_statement(var_s0);
            end;
            var_s0 := var_s0^.next;
        end;
    end;

    procedure func_004352AC(arg0: ^tree);
    label next_op;
    label loop;
    var
        var_s2: ^tree;
        var_a1: boolean;
        var_s0: ^tree;
        var_s1: ^tree;
        var_v0_2: ^tree;
        temp_s0: Uopcode;
        var_v1_2: integer;
        v0: integer;
    begin
        var_s2 := arg0;
        while var_s2 <> nil do begin
            temp_s0 := var_s2^.u.Opc;
            if (temp_s0 = Uclab) or (temp_s0 = Ulab) or (temp_s0 = Uent) or (temp_s0 = Uaent) then begin
                var_s2^.op1 := nil;
                var_s2^.op2 := nil;
            end else if (temp_s0 = Uujp) or (temp_s0 = Uxjp) or (temp_s0 = Uret) then begin
                func_004351C0(var_s2);
            end;
            if (temp_s0 = Utjp) or (temp_s0 = Ufjp) or (temp_s0 = Uujp) then begin
                if temp_s0 <> Uujp then begin
                    case var_s2^.op1^.u.Opc of
                        Uilod, Uisld, Ulod: begin
                            if var_s2^.op1^.u.Lexlev & 1 <> 0 then begin
                                var_s2^.op2^.mark := mark;
                                goto next_op;
                            end;
                        end;
                        otherwise begin end;
                    end;
                end;

loop:
                var_a1 := false;
                var_s0 := var_s2^.op2^.next;
                while var_s0^.u.Opc in [Ubgnb, Ucomm, Udef, Uendb, Ulab, Ulex, Uloc, Unop, Uoptn, Usdef, Uunal]
 do begin
                    if (var_s0^.u.Opc = Ulab) then begin
                        if (var_s0^.u.Lexlev <> 0) then begin
                            break;
                        end;
                        var_s2^.op2 := var_s0;
                    end;
                    var_s0 := var_s0^.next;
                end;
                if var_s0^.u.Opc = Uujp then begin
                    var_s2^.op2 := var_s0^.op2;
                end;
                var_s0 := var_s2^.op2;
                var_s1 := var_s2^.next;
                while var_s1^.u.Opc in [Ubgnb, Ucomm, Udef, Uendb, Ulab, Ulex, Uloc, Unop, Uoptn, Usdef, Uunal]
 do begin
                    if (var_s1^.u.Opc = Ulab) and (var_s1^.u.Lexlev <> 0) then begin
                        break;
                    end;
                    if var_s0 = var_s1 then begin
                        delete_statement(var_s2);
                        goto next_op;
                    end;
                    var_a1 := var_a1 or (var_s1^.u.Opc = Ulab);
                    var_s1 := var_s1^.next;
                end;
                if not var_a1 and (var_s2^.u.Opc <> Uujp) and (var_s1^.u.Opc = Uujp) then begin
                    func_004351C0(var_s1);
                    var_v0_2 := var_s1^.next;
                    while var_v0_2^.u.Opc in [Ubgnb, Ucomm, Udef, Uendb, Ulab, Ulex, Uloc, Unop, Uoptn, Usdef, Uunal]
 do begin
                        if var_s0 = var_v0_2 then begin
                            if var_s2^.u.Opc = Utjp then begin
                                var_s2^.u.Opc := Ufjp;
                            end else begin
                                var_s2^.u.Opc := Utjp;
                            end;
                            var_s2^.op2 := var_s1^.op2;
                            if var_s2^.u.Lexlev <> 0 then begin
                                if var_s2^.u.Lexlev = 1 then begin
                                    var_s2^.u.Lexlev := 2;
                                end else begin
                                    var_s2^.u.Lexlev:= 1;
                                end;
                            end;
                            delete_statement(var_s1);
                            goto loop;
                        end;
                        var_v0_2 := var_v0_2^.next;
                    end;
                end;
                var_s2^.op2^.mark := mark;
            end else if var_s2^.u.Opc = Uclab then begin
                v0 := var_s2^.u.Length;
                if v0 <> 0 then begin
                    var_v1_2 := v0;
                    repeat begin
                        var_s2 := var_s2^.next;
                        var_s0 := var_s2^.op2^.next;
                        while var_s0^.u.Opc in [Ubgnb, Ucomm, Udef, Uendb, Ulab, Ulex, Uloc, Unop, Uoptn, Usdef, Uunal]
 do begin
                            if (var_s0^.u.Opc = Ulab) and (var_s0^.u.Lexlev <> 0) then begin
                                var_s2^.op2 := var_s0;
                            end;
                            var_s0 := var_s0^.next;
                        end;
                        if var_s0^.u.Opc = Uujp then begin
                            var_s2^.op2 := var_s0^.op2;
                        end;
                        var_v1_2 := var_v1_2 - 1;
                        var_s2^.op2^.mark := mark;
                    end until (var_v1_2 = 0);
                end;
            end else if var_s2^.u.Opc = Uijp then begin
                var_s0 := var_s2^.op2;
                while var_s0 <> nil do begin
                    var_s0^.op1^.mark := mark;
                    var_s0 := var_s0^.next;
                end;
            end;
        next_op:
            var_s2 := var_s2^.next;
        end;
    end;
    
    procedure func_004357C4(arg0: ^Tree; arg1: ^Tree);
    var 
        ref: ^Tree;
        temp_v0: ^unk_record;
    begin
        ref := arg0^.op1;
        while (ref <> nil) do begin
            if (arg1 = ref^.op2) then begin    
                return;
            end;
            ref := ref^.prior;
        end;

        new(temp_v0);

        if (temp_v0 = nil) then begin
            report_error(Internal, 229, "labelopt.p", "Insufficiant memory");
            return;
        end;

        temp_v0^.op1 := arg0;
        temp_v0^.op2 := arg1;
        temp_v0^.next := arg0^.op1;
        temp_v0^.prior := arg1^.op2;
        arg0^.op1 := pointer(temp_v0);
        arg1^.op2 := pointer(temp_v0);
    end;

    procedure func_0043595C(arg0: ^Tree);
    var
        var_s4: boolean;
        var_s1: ^tree;
        var_s3: ^tree;
        var_s5: ^tree;
        var_s0: ^tree;
        
    begin
        var_s5 := nil;
        var_s1 := arg0;

        while (var_s1 <> nil) do begin
            case var_s1^.u.Opc of 
                Uaent,
                Uent:
                begin
                    var_s4 := true;
                    var_s3 := var_s1;
                    var_s1^.mark := mark1;

                    if (var_s1^.u.Opc = Uent) then begin
                        var_s5 := var_s1;
                    end else begin
                        func_004357C4(var_s5, var_s1);
                    end;
                end;

                Uret:
                begin
                    var_s4 := false;
                end;

                Ulab:
                begin
                    if ((var_s1^.mark <> mark) and (var_s1^.u.Lexlev = 0) and (var_s1^.u.Length = 0)) then begin
                        delete_statement(var_s1);
                        if not var_s4 then begin
                            func_004351C0(var_s1);
                        end;
                    end else begin
                            if ((var_s1^.u.Lexlev <> 0) or (var_s1^.u.Length <> 0)) then begin
                                func_004357C4(var_s5, var_s1);
                            end;

                            if var_s4 then begin 
                                func_004357C4(var_s3, var_s1);                                    
                            end;
                            var_s4 := true;
                            

                            var_s3 := var_s1;
                            var_s1^.mark := mark1;
                        end;
                end;

                Uclab:
                begin
                    if (var_s1^.u.Length <> 0) then begin
                        var_s3 := var_s1;
                        var_s1^.mark := mark1;
                    end;
                end;

                Uujp,
                Uxjp:
                begin
                    func_004357C4(var_s3, var_s1^.op2);
                    var_s4 := false;
                end;

                Ufjp,
                Utjp:
                begin
                    func_004357C4(var_s3, var_s1^.op2);
                end;

                Uijp:
                begin
                    var_s0 := var_s1^.op2;
                    var_s4 := false;

                    while (var_s0 <> nil) do begin
                        func_004357C4(var_s3, var_s0^.op1);
                        var_s0 := var_s0^.next;
                    end;
                end;

                otherwise:;
                
            end;
            var_s1 := var_s1^.next;
        end;
    end;

    procedure func_00435C44(arg0: ^Tree);
    var
        var_s1: ^tree;
    begin
        write(pFile, 'L', arg0^.node_id:1);
        write(pFile, " IN:");

        var_s1 := arg0^.op2;

        while (var_s1 <> nil) do begin
            write(pFile, " L", var_s1^.op1^.node_id:1);
            var_s1 := var_s1^.next;
        end;

        write(pFile, " OUT:");

        var_s1 := arg0^.op1;
        while (var_s1 <> nil) do begin
            write(pFile, " L", var_s1^.op2^.node_id:1);
            var_s1 := var_s1^.prior;
        end;

        writeln(pFile);
    end;

    procedure func_00435DE8(arg0: ^Tree);
    var
        var_s0: ^tree;
    begin
        if (arg0^.mark <> mark) then begin
            var_s0 := arg0^.op1;
            arg0^.mark := mark;
            
            while (var_s0 <> nil) do begin
                func_00435DE8(var_s0^.op2);
                var_s0 := var_s0^.prior;
            end;
        end;
    end;

    function func_00435E68(arg0: Ptree; arg1: Ptree): boolean;
    var
        var_v0: Ptree;
    begin
        var_v0 := arg0^.op1;

        while (var_v0 <> nil) do begin
            if (arg1 = var_v0^.op2) then begin
                return false;
            end;
            var_v0 := var_v0^.prior;
        end;
        return true;
    end;

    function func_00435EA0(arg0: ^Tree): pointer;
    var
        var_v1: ^tree;
    begin
        var_v1 := arg0;

        repeat begin
            var_v1 := var_v1^.next;
        end until (var_v1 = nil) or (var_v1^.u.Opc in [Uaent, Uent, Ulab]);
        
        return var_v1;
    end;

    function func_00435EF0(arg0: ^Tree): Ptree;
    label loop;
    var
        var_v1: ^Tree;
    begin
        var_v1 := arg0;

        loop:
        var_v1 := var_v1^.prior;
        if (var_v1 <> nil) then begin
            if not (var_v1^.u.Opc in [Uaent, Uent, Ulab]) then begin
                goto loop;
            end;
        end;
        return var_v1;
    end;
    
    function func_00435F40(arg0: ^Tree): boolean;
    var
        var_v0: ^tree;
    begin
        var_v0 := arg0;
        while (true) do begin
            var_v0 := var_v0^.next;
            if (var_v0 = nil) then begin
                func_00435F40 := false;
                return;
            end;

            if (var_v0^.u.Opc in [Uaent, Uent, Ulab, Uxjp]) then begin
                func_00435F40 := (var_v0^.u.Opc = Uxjp);
                return;
            end;
        end;
    end;

    procedure func_00435FA4(arg0: Ptree);
    var
        var_s0: ^Tree;
        var_s2: ^Tree;
        var_s3: ^Tree;
        temp_v1: ^Tree;
        temp_v1_2: ^Tree;
        temp_a0: ^Tree;
        temp_v0: ^Tree;
    begin
        var_s0 := arg0;
        while (var_s0^.u.Opc <> Uent) do begin
            var_s0 := var_s0^.next;
        end;

        repeat begin
            var_s2 := func_00435EA0(var_s0);
            if func_00435E68(var_s0, var_s2) and (var_s2 <> nil) then begin
                temp_v1 := var_s2^.prior;
            
                if (temp_v1^.u.Opc = Uujp) then begin
                    var_s0 := temp_v1^.op2;
                    var_s3 := func_00435EA0(var_s0);

                    if (var_s3 <> nil) and (func_00435F40(var_s0) or func_00435E68(var_s0, var_s3)) and func_00435E68(func_00435EF0(var_s0), var_s0) then begin
                        temp_v1_2 := var_s0^.prior;
                        temp_a0 := var_s3^.prior;
                        temp_v1_2^.next := var_s3;
                        var_s3^.prior := temp_v1_2;
                        temp_v0 := var_s2^.prior;
                        var_s0^.prior := temp_v0;
                        temp_a0^.next := var_s2;
                        temp_v0^.next := var_s0;
                        var_s2^.prior := temp_v0;
                        return;
                    end;
                end;
            end;
    
            var_s0 := var_s2;
        end until var_s2 = nil;
    end;

    procedure func_00436148(arg0: ^Tree);
    var
        var_s0: ^Tree;
        var_s2: boolean;
        var_v0: Uopcode;
    begin
        var_s2 := false;
        var_s0 := arg0;

        while (var_s0 <> nil) do begin
            var_v0 := var_s0^.u.Opc;
            if (var_v0 = Uent) or (var_v0 = Uaent) or (var_v0 = Ulab) or ((var_v0 = Uclab) and (var_s0^.u.Length <> 0)) then begin      
                if ((var_v0 = Uent) or (var_v0 = Uaent))  then begin
                    func_00435DE8(var_s0);
                end;
                
                if (debugPhases) then begin
                    func_00435C44(var_s0);
                end;

                if (var_s0^.u.Opc = Uclab) then begin
                    var_s2 := var_s0^.mark <> mark;
                end else begin
                    var_s2 := (var_s0^.mark <> mark) and (var_s0^.u.Lexlev = 0) and (var_s0^.u.Length = 0);
                end;
            end;
                

            if (var_s2) then begin
                if not (var_s0^.u.Opc in [Ubgnb, Udef, Uend, Uendb, Ulex, Uoptn, Ustp]) then begin
                    delete_statement(var_s0);
                end;
            end;
            
            var_s0 := var_s0^.next;
        end; 
        
    end;
    
begin
    mark := next_mark();
    mark1 := next_mark();

    func_004352AC(arg0);
    func_0043595C(arg0);
    func_00435FA4(arg0);

    if (debugPhases) then begin
        writeln(pFile, "Tree dump after 1st localopt:");
        print_tree(pFile, arg0, 16#7FFFFFFF, 16#7FFFFFFF);
        writeln(pFile);
        flush(pFile);
    end;

    func_00436148(arg0);
    if (debugPhases) then begin
        writeln(pFile, "Tree dump after 1st label phase:");
        print_tree(pFile, arg0, 16#7FFFFFFF, 16#7FFFFFFF);
        writeln(pFile);
        flush(pFile);
    end;

    if (cross_jumping_opt) then begin
        cross_jump(arg0);
        if (debugPhases) then begin
            writeln(pFile, "Tree dump after cross jumping");
            print_tree(pFile, arg0, 16#7FFFFFFF, 16#7FFFFFFF);
            writeln(pFile);
            flush(pFile);
        end;
    end;

    mark := next_mark();
    mark1 := next_mark();

    func_004352AC(arg0);
    func_0043595C(arg0);
    func_00436148(arg0);

    if (debugPhases) then begin
        writeln(pFile, "Tree dump after 2nd label phase:");
        print_tree(pFile, arg0, 16#7FFFFFFF, 16#7FFFFFFF);
        writeln(pFile);
        flush(pFile);
    end;
end;
