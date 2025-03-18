#include "cmplrs/usys.h"
#include "cmplrs/allocator.h"
#include "cmplrs/binasm.h"
#include "cmplrs/ucode.h"
#include "common.h"
#include "ibuffer.h"
#include "report.h"

procedure memset(p: pointer; value: integer; size: cardinal); external;

procedure append_i(var inst: binasm); forward;
procedure append_d(var inst: binasm); forward;

var
    debug_ugen: boolean;
    has_calls: boolean;
    uses_gp: boolean;
    pic_level: integer;

procedure save_i_ptrs();
begin
    old_i_ptr := i_ptr;
    old_d_ptr := d_ptr;
end;

procedure restore_i_ptrs();
begin
    memset(addr(ibuffer^[old_i_ptr]), 0, (i_ptr - old_i_ptr) * sizeof(binasm));
    memset(addr(ibuffer^[d_ptr]), 0, (old_d_ptr - d_ptr + 1) * sizeof(binasm));
    i_ptr := old_i_ptr;
    d_ptr := old_d_ptr;
end;

procedure init_ibuffer();
var
    size: cardinal;
begin
    ibuffer_size := 65000;
    size := ibuffer_size * sizeof(binasm);
    
    ibuffer := malloc(size);
    memset(addr(ibuffer^[1]), 0, size);

    if (addr(ibuffer^[1]) = nil) then begin
        report_error(Internal, 96, 'emit.p', 'Insufficiant memory');
    end;
    i_ptr := 1;
    d_ptr := ibuffer_size;
end;

procedure grow_ibuffer();
var
    i: cardinal;
    j: cardinal;
    new_ibuffer: ^BinasmArray;
    new_ibuffer_size: cardinal;
begin
    new_ibuffer_size := ibuffer_size * 2;
    new_ibuffer := malloc(new_ibuffer_size * sizeof(binasm));
    memset(new_ibuffer, 0, new_ibuffer_size * sizeof(binasm));

    if (new_ibuffer = nil) then begin
        report_error(Internal, 112, 'emit.p', 'Insufficiant memory');
    end;

    for i := 1 to i_ptr do begin
        new_ibuffer^[i] := ibuffer^[i];
    end;  

    j := new_ibuffer_size;
    for i := ibuffer_size downto d_ptr do begin
        new_ibuffer^[j] := ibuffer^[i];
        j := j - 1;
    end;
    j := j + 1;

    free(ibuffer);

    ibuffer := new_ibuffer;
    ibuffer_size := new_ibuffer_size;

    old_d_ptr := old_d_ptr + j - d_ptr;
    d_ptr := j;
end;

function create_local_label(labelno: cardinal): integer;
begin
    if (labelno = 0) or (labelno >= lastof(integer)) then begin
        report_error(Internal, 134, 'emit.p', 'local label out of range');
    end else begin
        return -integer(labelno);
    end;
end;

procedure emit_vers();
begin
    ibuffer^[d_ptr].instr := iverstamp;
    ibuffer^[d_ptr].majornumber := 7;
    ibuffer^[d_ptr].minornumber := 10;

    d_ptr := d_ptr - 1;
end;

procedure emit_rob(op: asmcodes; reg1: registers; immediate: integer; reg2: registers; mem_tag: integer);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := frob;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := reg2;
    ibuffer^[i_ptr].symno := 0;
    ibuffer^[i_ptr].mem_tag := mem_tag;
    ibuffer^[i_ptr].immediate := immediate;
    ibuffer^[i_ptr].formextn := franone;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if debug_ugen then begin
        writeln('emit_rob: ', op, ' ', reg1, immediate, ' ', reg2);
        assert(op <> zbad);
    end;
end;

procedure emit_rab(op: asmcodes; reg1: registers; immediate: integer; symno: integer; reg2: registers; mem_tag: integer);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := frob;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := reg2;
    ibuffer^[i_ptr].symno := symno;
    ibuffer^[i_ptr].mem_tag := mem_tag;
    ibuffer^[i_ptr].immediate := immediate;
    ibuffer^[i_ptr].formextn := franone;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_rab: ', op, ' ', reg1, immediate, ' ', reg2);
        assert(op <> zbad);
    end;
end;

procedure emit_rrab(op: asmcodes; reg1: registers; immediate: integer; symno: integer; reg2: registers);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := fra;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := reg2;
    ibuffer^[i_ptr].symno := symno;
    ibuffer^[i_ptr].mem_tag := 0;
    ibuffer^[i_ptr].immediate := immediate;
    ibuffer^[i_ptr].formextn := frcprel;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_rab: ', op, ' ', reg1, immediate, ' ', reg2);
    end;
end;

procedure emit_rllb(op: asmcodes; reg1: registers; immediate: integer; labelno: cardinal; reg2: registers);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := frob;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := reg2;
    ibuffer^[i_ptr].symno := create_local_label(labelno);
    ibuffer^[i_ptr].mem_tag := 0;
    ibuffer^[i_ptr].immediate := immediate;
    ibuffer^[i_ptr].formextn := franone;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_rllb: ', op, ' ', reg1, immediate, labelno, ' ', reg2);
    end;
end;

procedure emit_ra(op: asmcodes; reg1: registers; symno: integer; immediate: integer; mem_tag: integer);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := fra;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := xnoreg;
    ibuffer^[i_ptr].symno := symno;
    ibuffer^[i_ptr].mem_tag := mem_tag;
    ibuffer^[i_ptr].immediate := immediate;
    ibuffer^[i_ptr].formextn := franone;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    uses_gp := true;

    if (debug_ugen) then begin
        writeln('emit_ra: ', op, ' ', reg1, immediate);
    end;
end;

procedure emit_ri_(op: asmcodes; reg1: registers; immediate: integer; formextn: format_extn);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := fri;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := xnoreg;
    ibuffer^[i_ptr].symno := 0;
    ibuffer^[i_ptr].immediate := immediate;
    ibuffer^[i_ptr].formextn := formextn;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_ri: ', op, ' ', reg1, immediate);
    end;
end;

procedure emit_rii(op: asmcodes; reg1: registers; value: Valu);
begin
    emit_ri_(op, reg1, value.dwval_h, franone);
    emit_ri_(op, reg1, value.dwval_l, franone);
    uses_gp := true;
end;

procedure emit_rfi(op: asmcodes; reg1: registers; var value: Valu);
var
    num_records: cardinal;
    remainder: cardinal;
    i: cardinal;
    j: cardinal;
    offset: cardinal;
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := fri;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := xnoreg;
    ibuffer^[i_ptr].symno := 0;
    ibuffer^[i_ptr].immediate := value.Ival;
    ibuffer^[i_ptr].formextn := franone;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    num_records := value.Ival div 16;
    remainder := value.Ival mod 16;
    for i := 1 to num_records do begin
        offset := lshift(i, 4) - 16;
        for j := 1 to 16 do begin
            ibuffer^[i_ptr].data[j] := value.Chars^.ss[offset + j];
        end;

        if i_ptr = d_ptr then begin
            grow_ibuffer();
        end;
        i_ptr := i_ptr + 1;
    end;

    uses_gp := true;

    if (debug_ugen) then begin
        writeln('emit_rfi: ', op, ' ', reg1);
    end;

    if remainder <> 0 then begin
        ibuffer^[i_ptr].data := '';
        for i := 1 to remainder do begin
            ibuffer^[i_ptr].data[i] := value.Chars^.ss[lshift(num_records, 4) + i];
        end;

        if i_ptr = d_ptr then begin
            grow_ibuffer();
        end;
        i_ptr := i_ptr + 1;
    end;
end;

procedure emit_rrfi(op: asmcodes; reg1: registers; symno: cardinal);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := fri;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := xnoreg;
    ibuffer^[i_ptr].symno := symno;
    ibuffer^[i_ptr].immediate := 0;
    ibuffer^[i_ptr].formextn := frcprel;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_rl: ', op, ' ', reg1, symno);
    end;
end;

procedure emit_rrr(op: asmcodes; reg1: registers; reg2: registers; reg3: registers);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := frrr;
    ibuffer^[i_ptr].symno := 0;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := reg2;
    ibuffer^[i_ptr].reg3 := reg3;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_rrr: ', op, ' ', reg1, ' ', reg2, ' ', reg3);
    end;
end;

procedure emit_rri_(op: asmcodes; reg1: registers; reg2: registers; immediate: integer; formextn: format_extn);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := frri;
    ibuffer^[i_ptr].symno := 0;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := reg2;
    ibuffer^[i_ptr].immediate := immediate;
    ibuffer^[i_ptr].formextn := formextn;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_rri: ', op, ' ', reg1, ' ', reg2, immediate);
    end;
end;

procedure emit_rrri(op: asmcodes; reg1: registers; reg2: registers; symno: cardinal);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := frri;
    ibuffer^[i_ptr].symno := symno;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := reg2;
    ibuffer^[i_ptr].immediate := 0;
    ibuffer^[i_ptr].formextn := frcprel;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_rrri: ', op, ' ', reg1, ' ', reg2, symno);
    end;
end;

procedure emit_rr(op: asmcodes; reg1: registers; reg2: registers);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := frr;
    ibuffer^[i_ptr].symno := 0;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := reg2;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_rr: ', op, ' ', reg1, ' ', reg2);
    end;
end;

procedure emit_a(op: asmcodes; symno: cardinal; immediate: integer; formextn : format_extn);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := fa;
    ibuffer^[i_ptr].symno := symno;
    ibuffer^[i_ptr].immediate := immediate;
    ibuffer^[i_ptr].reg1 := xnoreg;
    ibuffer^[i_ptr].reg2 := xnoreg;
    ibuffer^[i_ptr].formextn := formextn;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    has_calls := true;

    if (debug_ugen) then begin
        writeln('emit_a: ', op, immediate);
    end;
end;

procedure emit_r(op: asmcodes; reg1: registers);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := fr;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := xnoreg;
    ibuffer^[i_ptr].symno := 0;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if op = zjal then begin
        has_calls := true;
    end;

    if (debug_ugen) then begin
        writeln('emit_r: ', op, ' ', reg1);
    end;
end;

procedure emit_i(op: asmcodes; immediate: integer);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := fi;
    ibuffer^[i_ptr].immediate := immediate;
    ibuffer^[i_ptr].reg1 := xnoreg;
    ibuffer^[i_ptr].reg2 := xnoreg;
    ibuffer^[i_ptr].symno := 0;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_i: ', op, immediate);
    end;
end;

procedure emit_rrl(op: asmcodes; reg1: registers; reg2: registers; symno: cardinal);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := frrl;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := reg2;
    ibuffer^[i_ptr].symno := symno;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_rrl: ', op, ' ', reg1, ' ', reg2, symno);
    end;
end;

procedure emit_rrll(op: asmcodes; reg1: registers; reg2: registers; labelno: cardinal);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := frrl;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := reg2;
    ibuffer^[i_ptr].symno := create_local_label(labelno);

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_rrll: ', op, ' ', reg1, ' ', reg2, labelno);
    end;
end;

procedure emit_rl(op: asmcodes; reg1: registers; symno: cardinal);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].immediate := 0;
    ibuffer^[i_ptr].form := frl;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := xnoreg;
    ibuffer^[i_ptr].symno := symno;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_rl: ', op, ' ', reg1, symno);
    end;
end;

procedure emit_rll(op: asmcodes; reg1: registers; labelno: cardinal);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].immediate := 0;
    ibuffer^[i_ptr].form := frl;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := xnoreg;
    ibuffer^[i_ptr].symno := create_local_label(labelno);

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_rll: ', op, ' ', reg1, labelno);
    end;
end;

procedure emit_l(op: asmcodes; symno: cardinal);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := fl;
    ibuffer^[i_ptr].symno := symno;
    ibuffer^[i_ptr].reg1 := xnoreg;
    ibuffer^[i_ptr].reg2 := xnoreg;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_l: ', op, symno);
    end;
end;

procedure emit_ll(op: asmcodes; labelno: cardinal);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].form := fl;
    ibuffer^[i_ptr].symno := create_local_label(labelno);
    ibuffer^[i_ptr].reg1 := xnoreg;
    ibuffer^[i_ptr].reg2 := xnoreg;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_ll: ', op, labelno);
    end;
end;

procedure emit_ril(op: asmcodes; reg1: registers; immediate: integer; symno: cardinal);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := xnoreg;
    ibuffer^[i_ptr].immediate := immediate;
    ibuffer^[i_ptr].form := fril;
    ibuffer^[i_ptr].symno := symno;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_ril: ', op, ' ', reg1, immediate, symno);
    end;
end;

procedure emit_rill(op: asmcodes; reg1: registers; immediate: integer; labelno: cardinal);
begin
    ibuffer^[i_ptr].instr := iocode;
    ibuffer^[i_ptr].op := op;
    ibuffer^[i_ptr].reg1 := reg1;
    ibuffer^[i_ptr].reg2 := xnoreg;
    ibuffer^[i_ptr].immediate := immediate;
    ibuffer^[i_ptr].form := fril;
    ibuffer^[i_ptr].symno := create_local_label(labelno);

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    if (debug_ugen) then begin
        writeln('emit_rill: ', op, ' ', reg1, immediate, labelno);
    end;
end;

procedure define_label(labelno: cardinal);
begin
    ibuffer^[i_ptr].instr := ilabel;
    ibuffer^[i_ptr].symno := create_local_label(labelno);

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;
end;

procedure emit_itext(var value: Valu);
var
    i: cardinal;
begin
    ibuffer^[i_ptr].instr := itext;
    ibuffer^[i_ptr].symno := 0;
    ibuffer^[i_ptr].length := value.Ival;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;

    ibuffer^[i_ptr].data := '';

    for i := 1 to value.Ival do begin
        ibuffer^[i_ptr].data[i] := value.Chars^.ss[i];
    end;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;
end;

procedure demit_itext(var value: Valu);
var
    i: cardinal;
begin
    ibuffer^[d_ptr].instr := itext;
    ibuffer^[d_ptr].symno := 0;
    ibuffer^[d_ptr].length := value.Ival;

    if d_ptr = i_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;

    ibuffer^[d_ptr].data := '';

    for i := 1 to value.Ival do begin
        ibuffer^[d_ptr].data[i] := value.Chars^.ss[i];
    end;

    if d_ptr = i_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure emit_dir0(instr: itype; arg1: integer);
begin
    ibuffer^[i_ptr].instr := instr;
    if (instr in [icprestore, iset]) then begin
        ibuffer^[i_ptr].symno := 0;
        ibuffer^[i_ptr].length := arg1;
    end else begin
        ibuffer^[i_ptr].symno := arg1;
        ibuffer^[i_ptr].length := 0;
        ibuffer^[i_ptr].length := 0;
    end;
    ibuffer^[i_ptr].rep := 0;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;
end;

procedure emit_dir1(instr: itype; symno: cardinal; arg2: integer);
begin
    ibuffer^[i_ptr].instr := instr;
    ibuffer^[i_ptr].length := arg2;
    ibuffer^[i_ptr].symno := symno;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;
end;

procedure emit_dir2(instr: itype; symno: cardinal; arg2: integer; arg3: integer);
begin
    ibuffer^[i_ptr].instr := instr;
    ibuffer^[i_ptr].symno := symno;
    case instr of
        iloc: begin
            ibuffer^[i_ptr].filenumber := arg2;
            ibuffer^[i_ptr].linenumber := arg3;
        end;
        imtag: begin
            ibuffer^[i_ptr].tagnumber := arg2;
            ibuffer^[i_ptr].tagtype := arg3;
        end;
        imalias: begin
            ibuffer^[i_ptr].memtag1 := arg2;
            ibuffer^[i_ptr].memtag2 := arg3;
        end;
        otherwise begin
            ibuffer^[i_ptr].length := arg2;
            ibuffer^[i_ptr].rep := arg3;
        end;
    end;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;
end;

procedure emit_alias(instr: itype; reg1: registers; reg2: registers);
begin
    ibuffer^[i_ptr].instr := instr;
    ibuffer^[i_ptr].symno := 0;
    ibuffer^[i_ptr].basereg1 := reg1;
    ibuffer^[i_ptr].basereg2 := reg2;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;
end;

procedure emit_regmask(instr: itype; regmask: integer; regoffset: integer);
begin
    ibuffer^[i_ptr].instr := instr;
    ibuffer^[i_ptr].symno := 0;
    ibuffer^[i_ptr].regmask := regmask;
    ibuffer^[i_ptr].regoffset := regoffset;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;
end;

procedure emit_loopno(loopnum: integer; lflag: integer);
begin
    ibuffer^[i_ptr].instr := iloopno;
    ibuffer^[i_ptr].loopnum := loopnum;
    ibuffer^[i_ptr].lflag := lflag;
    ibuffer^[i_ptr].symno := 0;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;
end;

procedure emit_dir_ll(labelno: cardinal; expression: integer);
begin
    if pic_level = 2 then begin
        ibuffer^[i_ptr].instr := igpword;
    end else begin
        ibuffer^[i_ptr].instr := iword;
    end;
    ibuffer^[i_ptr].expression := expression;
    ibuffer^[i_ptr].symno := create_local_label(labelno);
    ibuffer^[i_ptr].replicate := 1;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;
end;

procedure demit_rob_(op: asmcodes; reg1: registers; immediate: integer; reg2: registers; formextn: format_extn);
begin
    ibuffer^[d_ptr].instr := iocode;
    ibuffer^[d_ptr].op := op;
    ibuffer^[d_ptr].form := frob;
    ibuffer^[d_ptr].symno := 0;
    ibuffer^[d_ptr].reg1 := reg1;
    ibuffer^[d_ptr].reg2 := reg2;
    ibuffer^[d_ptr].mem_tag := 0;
    ibuffer^[d_ptr].immediate := immediate;
    ibuffer^[d_ptr].formextn := formextn;

    if d_ptr = i_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure demit_ri(op: asmcodes; reg1: registers; immediate: integer; formextn: format_extn);
begin
    ibuffer^[d_ptr].instr := iocode;
    ibuffer^[d_ptr].op := op;
    ibuffer^[d_ptr].form := fri;
    ibuffer^[d_ptr].reg1 := reg1;
    ibuffer^[d_ptr].reg2 := xnoreg;
    ibuffer^[d_ptr].symno := 0;
    ibuffer^[d_ptr].immediate := immediate;
    ibuffer^[d_ptr].formextn := formextn;

    if d_ptr = i_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure demit_rr(op: asmcodes; reg1: registers; reg2: registers);
begin
    ibuffer^[d_ptr].instr := iocode;
    ibuffer^[d_ptr].op := op;
    ibuffer^[d_ptr].form := frr;
    ibuffer^[d_ptr].reg1 := reg1;
    ibuffer^[d_ptr].reg2 := reg2;
    ibuffer^[d_ptr].symno := 0;

    if d_ptr = i_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure demit_a(op: asmcodes; symno: cardinal; immediate: integer);
begin
    ibuffer^[d_ptr].instr := iocode;
    ibuffer^[d_ptr].op := op;
    ibuffer^[d_ptr].form := fa;
    ibuffer^[d_ptr].symno := symno;
    ibuffer^[d_ptr].immediate := immediate;
    ibuffer^[d_ptr].reg1 := xnoreg;
    ibuffer^[d_ptr].reg2 := xnoreg;
    ibuffer^[d_ptr].formextn := franone;

    if d_ptr = i_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure demit_regmask(instr: itype; regmask: integer; regoffset: integer);
begin
    ibuffer^[d_ptr].instr := instr;
    ibuffer^[d_ptr].symno := 0;
    ibuffer^[d_ptr].regmask := regmask;
    ibuffer^[d_ptr].regoffset := regoffset;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure demit_rrr(op: asmcodes; reg1: registers; reg2: registers; reg3: registers);
begin
    ibuffer^[d_ptr].instr := iocode;
    ibuffer^[d_ptr].op := op;
    ibuffer^[d_ptr].form := frrr;
    ibuffer^[d_ptr].symno := 0;
    ibuffer^[d_ptr].reg1 := reg1;
    ibuffer^[d_ptr].reg2 := reg2;
    ibuffer^[d_ptr].reg3 := reg3;

    if d_ptr = i_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure demit_rri(op: asmcodes; reg1: registers; reg2: registers; immediate: integer);
begin
    ibuffer^[d_ptr].instr := iocode;
    ibuffer^[d_ptr].op := op;
    ibuffer^[d_ptr].form := frri;
    ibuffer^[d_ptr].reg1 := reg1;
    ibuffer^[d_ptr].reg2 := reg2;
    ibuffer^[d_ptr].symno := 0;
    ibuffer^[d_ptr].immediate := immediate;

    if d_ptr = i_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure demit_rrll(op: asmcodes; reg1: registers; reg2: registers; labelno: cardinal);
begin
    ibuffer^[d_ptr].instr := iocode;
    ibuffer^[d_ptr].op := op;
    ibuffer^[d_ptr].form := frrl;
    ibuffer^[d_ptr].reg1 := reg1;
    ibuffer^[d_ptr].reg2 := reg2;
    ibuffer^[d_ptr].symno := create_local_label(labelno);

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure demit_i(op: asmcodes; immediate: integer);
begin
    ibuffer^[d_ptr].instr := iocode;
    ibuffer^[d_ptr].op := op;
    ibuffer^[d_ptr].form := fi;
    ibuffer^[d_ptr].immediate := immediate;
    ibuffer^[d_ptr].reg1 := xnoreg;
    ibuffer^[d_ptr].reg2 := xnoreg;
    ibuffer^[d_ptr].symno := 0;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure demit_ra(op: asmcodes; reg1: registers; symno: integer; immediate: integer);
begin
    ibuffer^[d_ptr].instr := iocode;
    ibuffer^[d_ptr].op := op;
    ibuffer^[d_ptr].form := fra;
    ibuffer^[d_ptr].reg1 := reg1;
    ibuffer^[d_ptr].reg2 := xnoreg;
    ibuffer^[d_ptr].symno := symno;
    ibuffer^[d_ptr].immediate := immediate;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure demit_dir0(instr: itype; arg1: integer);
begin
    ibuffer^[d_ptr].instr := instr;
    if (instr in [icprestore, iset]) then begin
        ibuffer^[d_ptr].symno := 0;
        ibuffer^[d_ptr].length := arg1;
    end else begin
        ibuffer^[d_ptr].symno := arg1;
        ibuffer^[d_ptr].length := 0;
    end;
    ibuffer^[d_ptr].rep := 0;

    if d_ptr = i_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure demit_dir1(instr: itype; symno: cardinal; arg2: integer);
begin
    ibuffer^[d_ptr].instr := instr;
    ibuffer^[d_ptr].symno := symno;
    case instr of
        ient, iprologue: begin
            ibuffer^[d_ptr].lexlevel := arg2;
        end;
        otherwise begin
            ibuffer^[d_ptr].length := arg2;
        end;
    end;

    if d_ptr = i_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure demit_dir2(instr: itype; symno: cardinal; arg2: integer; arg3: integer);
begin
    ibuffer^[d_ptr].instr := instr;
    ibuffer^[d_ptr].symno := symno;
    case instr of
        iverstamp: begin
            ibuffer^[d_ptr].majornumber := arg2;
            ibuffer^[d_ptr].minornumber := arg3;
        end;
        iloc: begin
            ibuffer^[d_ptr].filenumber := arg2;
            ibuffer^[d_ptr].linenumber := arg3;
        end;
        icomm, ilcomm, iextern: begin
            ibuffer^[d_ptr].length := arg2;
            ibuffer^[d_ptr].rep := arg3;
        end;
        otherwise begin
            ibuffer^[d_ptr].length := arg2;
            ibuffer^[d_ptr].rep := arg3;
        end;
    end;

    if d_ptr = i_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure demit_edata(symno: cardinal; flag: integer; edata: integer);
begin
    ibuffer^[d_ptr].instr := iedata;
    ibuffer^[d_ptr].symno := symno;
    ibuffer^[d_ptr].flag := flag;
    ibuffer^[d_ptr].edata := edata;

    if d_ptr = i_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure demit_weakext(symno: cardinal; lexlevel: integer);
begin
    ibuffer^[d_ptr].instr := iweakext;
    ibuffer^[d_ptr].symno := symno;
    ibuffer^[d_ptr].lexlevel := lexlevel;

    if d_ptr = i_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure emit_cpload(reg1: registers; immediate: integer; symno: cardinal; arg3: boolean);
var
    inst: binasm;
begin
    inst.instr := icpload;
    inst.reg1 := reg1;
    inst.immediate := immediate;
    inst.symno := symno;

    if arg3 then begin
        emit_dir0(iset, 2);
        append_i(inst);
        emit_dir0(iset, 1);
    end else begin
        demit_dir0(iset, 2);
        append_d(inst);
        demit_dir0(iset, 1);
    end;
end;

procedure ddefine_label(labelno: cardinal);
begin
    ibuffer^[d_ptr].instr := ilabel;
    ibuffer^[d_ptr].symno := create_local_label(labelno);

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure define_exception_label(labelno: cardinal);
begin
    ibuffer^[i_ptr].instr := ilabel;
    ibuffer^[i_ptr].symno := labelno;

    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;
end;

procedure append_i{(var inst: binasm)};
begin
    ibuffer^[i_ptr] := inst;
    if i_ptr = d_ptr then begin
        grow_ibuffer();
    end;
    i_ptr := i_ptr + 1;
end;

procedure append_d{(var inst: binasm)};
begin
    ibuffer^[d_ptr] := inst;
    if d_ptr = i_ptr then begin
        grow_ibuffer();
    end;
    d_ptr := d_ptr - 1;
end;

procedure clear_ibuffer();
begin
    memset(addr(ibuffer^[1]), 0, i_ptr * 16);
    memset(addr(ibuffer^[d_ptr]), 0, (ibuffer_size - d_ptr + 1) * 16 );
    i_ptr := 1;
    d_ptr := ibuffer_size;
end;

procedure emit_vreg(reg1: registers; immediate: integer; symno: cardinal);
var
    inst: binasm;
begin
    inst.instr := ivreg;
    inst.reg1 := reg1;
    inst.immediate := immediate;
    inst.symno := symno;
    append_i(inst);
end;

procedure emit_pic(arg0: integer);
begin
    ibuffer^[d_ptr].instr := ioption;
    ibuffer^[d_ptr].option := o_pic;
    ibuffer^[d_ptr].opt_int_value := arg0;

    d_ptr := d_ptr - 1;
end;

procedure demit_cpalias(reg1: registers);
var
    inst: binasm;
begin
    inst.instr := icpalias;
    inst.reg1 := reg1;
    inst.symno := 0;
    append_d(inst);
end;

procedure emit_cpalias(reg1: registers);
var
    inst: binasm;
begin
    inst.instr := icpalias;
    inst.reg1 := reg1;
    inst.symno := 0;
    append_i(inst);
end;

procedure emit_cpadd(reg1: registers);
var
    inst: binasm;
begin
    inst.instr := icpadd;
    inst.reg1 := reg1;
    inst.symno := 0;
    uses_gp := true;
    append_i(inst);
end;
