/*
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991 MIPS Computer Systems, Inc.            |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 52.227-7013.   |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Drive                                |
 * |         Sunnyvale, CA 94086                               |
 * |-----------------------------------------------------------|
 */
/* $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/cmplrs/RCS/binasm.h,v 7.24 1996/02/21 19:51:36 mpm Exp $ */

#ifdef _LANGUAGE_PASCAL
const

/* Traumatic change in 1.30: record becomes larger */
  bin_rec_len = 16;	{16 bytes per record}
/*bin_rec_len = 12;	{12 bytes per record}*/
  symtype_first = first(integer);
  symtype_last  = last(integer);

type

  registers = (
	xr0,	xr1,	xr2,	xr3,	xr4,	xr5,	xr6,	xr7,
	xr8,	xr9,	xr10,	xr11,	xr12,	xr13,	xr14,	xr15,
	xr16,	xr17,	xr18,	xr19,	xr20,	xr21,	xr22,	xr23,
	xr24,	xr25,	xr26,	xr27,	xr28,	xr29,	xr30,	xr31,
	xfr0,	xfr1,	xfr2,	xfr3,	xfr4,	xfr5,	xfr6,	xfr7,
	xfr8,	xfr9,	xfr10,	xfr11,	xfr12,	xfr13,	xfr14,	xfr15,
	xfr16,	xfr17,	xfr18,	xfr19,	xfr20,	xfr21,	xfr22,	xfr23,
	xfr24,	xfr25,	xfr26,	xfr27,	xfr28,	xfr29,	xfr30,	xfr31,
	xfcc0, 	xfcc1, 	xfcc2, 	xfcc3, 	xfcc4, 	xfcc5, 	xfcc6, 	xfcc7,
	xnoreg
	);
#ifndef _REG_SET
#define _REG_SET 1
  aligned_registers = (
    ar0,    ar1,    ar2,    ar3,    ar4,    ar5,    ar6,    ar7,
    ar8,    ar9,    ar10,   ar11,   ar12,   ar13,   ar14,   ar15,
    ar16,   ar17,   ar18,   ar19,   ar20,   ar21,   ar22,   ar23,
    ar24,   ar25,   ar26,   ar27,   ar28,   ar29,   ar30,   ar31,
    afr0,   afr1,   afr2,   afr3,   afr4,   afr5,   afr6,   afr7,
    afr8,   afr9,   afr10,  afr11,  afr12,  afr13,  afr14,  afr15,
    afr16,  afr17,  afr18,  afr19,  afr20,  afr21,  afr22,  afr23,
    afr24,  afr25,  afr26,  afr27,  afr28,  afr29,  afr30,  afr31
    );
  aligned_regset = set of aligned_registers;

#endif

  itype = (
	ilabel,     isym,       iglobal,    icpload,    ialign,
	iascii,     iasciiz,    ibyte,      icomm,      ilcomm,
	idata,      idouble,    ifile,      ifloat,     ihalf,
	icprestore, igpword,    icpadd,     iweakext,   iloopno,
	ispace,     itext,      iword,      iocode,     iend,
	isdata,     irdata,     ient,       iloc,       ibgnb,
	iendb,      iasm0,      iset,       icpalias,   irep,
	iendrep,    ilab,       ivreg,      imask,      ifmask,
	ierr,       iglobabs,   iverstamp,  iframe,     iextended,
	iextern,    iaent,      ioption,    inoalias,   ialias,
	imtag,      imalias,    istruct,    ilivereg, 	igjaldef,
	igjallive,  igjrlive, 	ishift_addr, irestext,  idword,
	iprologue,  iedata,     ialloc
	);

  {---------------------------------------------------------------------------}
  { asmcodes specify the assembler instructions 			      }
  {---------------------------------------------------------------------------}

  asmcodes = (
	zabs,       zadd,       zaddu,      zand,       zb,        {000-004}
	zbc0f,      zbc0t,      zbc1f,      zbc1t,      zbc2f,     {005-009}
	zbc2t,      zlgota,     z12,        zbeq,       zbge,      {010-014}
	zbgeu,      zbgez,      zbgt,       zbgtu,      zbgtz,     {015-019}
	zble,       zbleu,      zblez,      zblt,       zbltu,     {020-024}
	zbltz,      zbne,       zbreak,     zc0,        zc1,       {025-029}
	zc2,        z31,        zdiv,       zdivu,      zj,        {030-034}
	zjal,       zla,        zlb,        zlbu,       zlh,       {035-039}
	zlhu,       zli,        zlw,        zjr,        zlwc1,     {040-044}
	zlwc2,      zpref,      zmfhi,      zmflo,      zmove,     {045-049}
	zjalr,      zswc1,      zswc2,      z53,        zmthi,     {050-054}
	zmtlo,      zmul,       zmulo,      zmulou,     zmult,     {055-059}
	zmultu,     zneg,       znop,       znor,       zor,       {060-064}
	zrem,       zremu,      zrfe,       zrol,       zror,      {065-069}
	zsb,        zseq,       zsge,       zsgeu,      zsgt,      {070-074}
	zsgtu,      zsh,        zsle,       zsleu,      zsll,      {075-079}
	zslt,       zsltu,      zsne,       zsra,       zsrl,      {080-084}
	zsub,       zsubu,      zsw,        zsyscall,   zxor,      {085-089}
	znot,       zlwl,       zlwr,       zswl,       zswr,      {090-094}
	zvcall,     zmfc0,      zmfc1,      zmfc2,      z99,       {095-099}
	zmtc0,      zmtc1,      zmtc2,      zsync,      ztlbr,     {100-104}
	ztlbwi,     ztlbwr,     ztlbp,      zld,        zsd,       {106-109}
	z110,       zldc1,      zldc2,      ztlbr1,     ztlbp1,    {110-114}
	zsdc1,      zsdc2,      z117,				   {115-117}
	fl_s,		fl_d,		fl_e,			   {118-120}
	fs_s,		fs_d,		fs_e,			   {121-123}
 	fadd_s,		fadd_d,		fadd_e,			   {124-126}
 	fsub_s,		fsub_d,		fsub_e,			   {127-129}
 	fmul_s,		fmul_d,		fmul_e,			   {130-132}
 	fdiv_s,		fdiv_d,		fdiv_e,			   {133-135}
 	fsqrt_s,	fsqrt_d,	fsqrt_e,		   {136-138}
 	fmov_s,		fmov_d,		fmov_e,			   {139-141}
 	fabs_s,		fabs_d,		fabs_e,			   {142-144}
        		fcvt_s_d,	fcvt_s_e,	fcvt_s_w,  {145-147}
 	fcvt_d_s,        		fcvt_d_e,	fcvt_d_w,  {148-150}
 	fcvt_e_s,	fcvt_e_d,        		fcvt_e_w,  {151-153}
 	fcvt_w_s,	fcvt_w_d,	fcvt_w_e,		   {154-156}
 	fc_f_s,		fc_f_d,		fc_f_e,			   {157-159}
 	fc_un_s,	fc_un_d,	fc_un_e,		   {160-162}
 	fc_eq_s,	fc_eq_d,	fc_eq_e,		   {163-165}
 	fc_ueq_s,	fc_ueq_d,	fc_ueq_e,		   {166-168}
 	fc_olt_s,	fc_olt_d,	fc_olt_e,		   {169-171}
 	fc_ult_s,	fc_ult_d,	fc_ult_e,		   {172-174}
	fc_ole_s,	fc_ole_d,	fc_ole_e,		   {175-177}
 	fc_ule_s,	fc_ule_d,	fc_ule_e,		   {178-180}
 	fc_sf_s,	fc_sf_d,	fc_sf_e,		   {181-183}
 	fc_ngle_s,	fc_ngle_d,	fc_ngle_e,		   {184-186}
 	fc_seq_s,	fc_seq_d,	fc_seq_e,		   {187-189}
 	fc_ngl_s,	fc_ngl_d,	fc_ngl_e,		   {190-192}
 	fc_lt_s,	fc_lt_d,	fc_lt_e,		   {193-195}
 	fc_nge_s,	fc_nge_d,	fc_nge_e,		   {196-198}
 	fc_le_s,	fc_le_d,	fc_le_e,		   {199-201}
 	fc_ngt_s,	fc_ngt_d,	fc_ngt_e,		   {202-204}
	zlui,		zulw,		zulh,		zulhu,	   {205-208}
	zusw,		zush,		zaddi,		zaddiu,	   {209-212}
	zslti,		zsltiu,		zandi,		zori,	   {213-216}
	zxori,		z218,		znegu,		zbeqz,	   {217-220}
	zbnez,							   {221}
	fneg_s,		fneg_d,		fneg_e,			   {222-224}
	zcfc1,		zctc1,		zbal,		zbgezal,   {225-228}
	zbltzal,	zmtc1_d,	zmfc1_d,		   {229-231}
	ztrunc_w_s,	ztrunc_w_d,	ztrunc_w_e,		   {232-234}
	zround_w_s,	zround_w_d,	zround_w_e,		   {235-237}
	zaddou,		zsubou,					   {238-239}
	ztruncu_w_s,	ztruncu_w_d,	ztruncu_w_e,		   {240-242}
	zroundu_w_s,	zroundu_w_d,	zroundu_w_e,		   {243-245}
	zcfc0,		zcfc2,		z248,		zctc0,	   {246-249}
	zctc2,		z251,					   {250-251}
        fli_s,		fli_d,		fli_e,			   {252-254}
	ztlt,		ztltu,		ztge,		ztgeu,	   {255-258}
	zteq,		ztne,		zll,		zsc,	   {259-262}
	zceil_w_s,	zceil_w_d,	zceil_w_e,		   {263-265}
	zceilu_w_s,	zceilu_w_d,	zceilu_w_e,		   {266-268}
	zfloor_w_s,	zfloor_w_d,	zfloor_w_e,		   {269-271}
	zflooru_w_s,	zflooru_w_d,	zflooru_w_e,		   {272-274}
	zbeql,          zbeqzl,         zbnel,          zbnezl,    {275-278}
	zblel,          zbleul,         zblezl,                    {279-281}
	zbgtl,          zbgtul,         zbgtzl,                    {282-284}
	zbltl,          zbltul,         zbltzl,         zbltzall,  {285-288}
	zbgel,          zbgeul,         zbgezl,         zbgezall,  {289-292}
	zbc0fl,         zbc0tl,         zbc1fl,         zbc1tl,    {293-296}
	zbc2fl,         zbc2tl,         z299,           z300,      {297-300}
	zldl,           zldr,           zlld,         	zlwu,	   {301-304}
	zsdl,           zsdr,           zscd,	        	   {305-307}
	zdaddi,         zdaddiu,        zdadd,	        zdaddu,	   {308-311}
	zdsub,          zdsubu,         			   {312-313}
	zdsll,          zdsrl,          zdsra,         		   {314-316}
	zdsllv,         zdsrlv,         zdsrav,         	   {317-319}
	zdmult,         zdmultu,        zddiv,  	zddivu,    {320-323}
	zlsc1,         	zssc1,        	zdmtc1,         zdmfc1,    {324-327}
	zdmtc0,		zdmfc0,		zdmtc2,		zdmfc2,	   {328-331}
	zdli,		zdla,					   {332-333}
        zeret,                                                     {334}
        ztrunc_l_s,     zround_l_s,     zceil_l_s,      zfloor_l_s,{335-338}
        ztrunc_l_d,     zround_l_d,     zceil_l_d,      zfloor_l_d,{339-342}
        ztrunc_l_e,     zround_l_e,     zceil_l_e,      zfloor_l_e,{343-346}
        fcvt_l_s,       fcvt_l_d,       fcvt_l_e,       fcvt_l_w,  {347-350}
        fcvt_s_l,       fcvt_d_l,       fcvt_e_l,       fcvt_w_l,  {351-354}
	zcache,		zcia,					   {355-356}
        zuld,           zusd,           zdabs,          zdneg,     {357-360}
        zdnegu,         zdmul,          zdmulo,         zdmulou,   {361-364}
        zdrem,          zdremu,                                    {365-366}
        zdrol,          zdror,                                     {367-368}
        zdaddou,        zdsubou,	zulwu,		           {369-371}
	zmovt,		zmovf,		zmovn,		zmovz,	   {372-375}
	fmadd_s,	fmadd_d,	fmadd_e,	fmsub_s,   {376-379}
	fmsub_d,	fmsub_e, 	fnmadd_s,	fnmadd_d,  {380-383}
	fnmadd_e,	fnmsub_s,	fnmsub_d,	fnmsub_e,  {384-387}
	frecip_s,	frecip_d,	frsqrt_s,	frsqrt_d,  {388-391}
	fmovt_s,	fmovt_d,	fmovf_s,	fmovf_d,   {392-395}
	fmovn_s,	fmovn_d,	fmovz_s,	fmovz_d,   {396-399}
	zlwxc1,		zldxc1,		zswxc1,		zsdxc1,    {400-403}
	zpfetch,	zdctr,		zdctw,		ztlbw,	   {404-407}	
	znada,		zssnop,					   {408-409}
	zdsll32,	zdsrl32,	zdsra32,		   {410-412}
	zbc3f,		zbc3t,		zc3,		zlwc3,	   {413-416}
	zswc3,		zmfc3,		zmtc3,		zcfc3,	   {417-420}
	zctc3,		zsllv,		zsrlv,		zsrav,     {421-424}
	zmfpc,		zmtpc,		zmfps,		zmtps,	   {425-428}
	zbad
	);

  kind = (
	chars, instruction
	);

  symtype = symtype_first .. symtype_last;

  format_extn = (
	franone
	,frahi				{ reg, [reg], sym[+/-offset]	      }
	,fralo				{ reg, [reg], sym[+/-offset]	      }
	,frrel1				{ reg, .[+offset]		      }
	,frrel2				{ reg, .[-offset]		      }
	,frgprel			{ reg, sym[+/-offset] + reg	      }
        ,frcprel                        { reg, sym[reg]                       }
	);

  format = (
	frob,				{ reg, offset(+/-32k), base	      }
	fra,				{ reg, [sym]+offset		      }
	fri,				{ reg, immed (32 bit)		      }
	frrr,				{ reg, reg, reg 		      }
	frri,				{ reg, reg, immed (32 bit)	      }
	frr,				{ reg, reg			      }
	fa,				{ [sym]+offset [+(base)]	      }
	fr,				{ reg				      }
	frrl,				{ reg, reg, sym 		      }
	frl,				{ reg, sym			      }
	fl,				{ sym				      }
	forrr,				{ co processor if required?	      }
	fril, 				{ reg, immed, label                   }
	fi,				{ immed				      }
	foa,				{ op, address			      }
	frrrr				{ reg, reg, reg, reg		      }
	);

  set_value = (
	set_undefined,
	set_reorder,
	set_noreorder,
	set_macro,
	set_nomacro,
	set_at,
	set_noat,
	set_move,
	set_nomove,
	set_bopt,
	set_nobopt,
	set_volatile,
	set_novolatile,
	set_transform,
	set_notransform,
	set_reposition,
	set_noreposition
	);

  opt_type = (
	o_undefined,
	o_optimize,
	o_pic,
	o_exception_info
	);

  opt_arg_type = (
	opt_none,
	opt_int,
	opt_float,
	opt_string
	);

  /* we have to kluge this declaration so that 2.10 .G's are backward
     compatible due to changes in Mips pascal's packing rule  */
  reg_compat_align = firstof(registers)..lastof(registers) of integer;
  form_compat_align = firstof(format)..lastof(format) of integer;
  form_extn_compat_align = firstof(format_extn)..lastof(format_extn) of integer;
  opt_compat_align = firstof(opt_type)..lastof(opt_type) of integer;

  binasm = packed record
    case kind of
      chars : (
	data : packed array[1 .. bin_rec_len] of char
	);

      instruction : (
	symno : symtype;		{ 32 bits			      }
	fill07 : 0..127;		{ 7 bits to word boundary	      }
	formextn : form_extn_compat_align; { 3 bits			      }
	case instr : itype of 	{ 6 bits			      }
	    ierr : ();		{ ????? 			      }

	    { move itext to case with length field.Gili 7/15/91	}
	    idata, iend, iglobal, iasm0, iendrep, ilabel, ialloc,
		isdata, irdata, ilab, ibgnb,
		irestext,
		iendb : ();		{ symno has the info		      }

	    ient, iaent, iprologue, iweakext : (
	      lexlevel : integer);

	    iframe : (
	      frameoffset : integer;
	      framereg : reg_compat_align;
	      pcreg : reg_compat_align);

	    imask, ifmask : (
	      regmask,			{ 32 bits			      }
	      regoffset : integer);	{ 32 bits			      }

	    iverstamp : (
	      majornumber,		{ 32 bits			      }
	      minornumber : integer);	{ 32 bits			      }

	    iloc : (
	      filenumber,		{ 32 bits			      }
	      linenumber : integer);	{ 32 bits			      }

	    { Add "ishift_addr" . Gili 10/13/89			}
	    { Add "itext". Gili 7/15/91				}
	    ialign, iascii, iasciiz, icomm, ilcomm, isym, ifloat, idouble,
		iextended, irep, iset, ispace, ifile,
    		iglobabs, iextern, ishift_addr, itext, icprestore : (
	      length : integer;		{ 32 bits			      }
	      rep : cardinal);		{ 32 bits - only for ifloat, idouble, }
					{   iextended			      }
	    ilivereg : (
	      gpmask,			{ 32 bits			      }
	      fpmask : cardinal);	{ 32 bits			      }

	    igjaldef, igjallive, igjrlive : (
	      gjmask : aligned_regset);{ 64 bits			      }

	    idword,
	    ibyte, ihalf, iword, igpword : (
	      expression : integer;	{ 32 bits			      }
	      replicate : cardinal);	{ 32 bits			      }
            iedata : (
	      flag    : integer;	{ 32 bits			      }
	      edata   : integer);	{ 32 bits			      }
	    iloopno : (
	      loopnum : integer;	{ 32 bits			      }
	      lflag    : integer);	{ 32 bits			      }
	    iocode, ivreg, icpload, icpalias, icpadd : (
	      fill03 : 0..63;		{  6 bits to half boundary	      }
	      op : asmcodes;		{  9 bits, 16 bits due to alignment   }
	      reg1 : reg_compat_align; 	{  7 bits			      }
	      reg2 : reg_compat_align; 	{  7 bits			      }
	      case form : form_compat_align of	{  4 bits		      }
		frrr,			{ reg4 is unused for frrr	      }
		frrrr : (		{ reg1, reg2, reg3, reg4	      }
		  reg3 : reg_compat_align;	{  7 bits		      }
		  reg4 : reg_compat_align);	{  7 bits		      }
		fa,			{ [sym]+offset			      }
		frob,			{ reg1, offset(+/-32k), reg2	      }
		fra,			{ reg1, [sym]+offset		      }
		fri,			{ reg1, immed (32 bit)		      }
		fril,			{ reg1, immed (32 bit), label	      }
		frri : (		{ reg1, reg2, immed (32 bit)	      }
		  mem_tag : 0.. 16383;  { 14 bits to next word boundary       }
		  immediate : integer); { 32 bits			      }
		fr,			{ reg1				      }
		frr,			{ reg1, reg2			      }
		frl,			{ reg1, sym			      }
		fl : ();		{ sym				      }
		forrr : ();		{ co processor if required?	      }
		fi : (			{ immed				      }
		  imm : integer);	{ 32 bits 			      }
		frrl : ();		{ reg1, reg2, sym		      }
	      );
	    ioption: (
	      option: opt_compat_align;	{ which 2-bit option (e.g. "O" for "-O3")  }
	      fill04: 0 .. 16#3fffffff; { pad to 32-bit boundary	      }
	      case opt_arg_type of	{ associated arg (e.g. "3" for "-O3") }
		opt_none: ();
		opt_int: (opt_int_value: integer);
					{ integer value of argument           }
		opt_float,
		opt_string: (opt_len: integer);
					{ length in bytes of string arg which }
					{   appears in future binasm records, }
					{   representing either fp or string  }
	      );
	    inoalias,			{ no aliasing till reversed by ialias }
	    ialias: (
	      basereg1: reg_compat_align;
	      basereg2: reg_compat_align;
	      );

	    imtag: (
		tagnumber : integer;
		tagtype : integer;
		);
	    imalias: ( memtag1, memtag2 : integer; );

	);
      end;  {record}

#endif /* _LANGUAGE_PASCAL */


#ifdef _LANGUAGE_C


typedef enum {
	xr0,	xr1,	xr2,	xr3,	xr4,	xr5,	xr6,	xr7,
	xr8,	xr9,	xr10,	xr11,	xr12,	xr13,	xr14,	xr15,
	xr16,	xr17,	xr18,	xr19,	xr20,	xr21,	xr22,	xr23,
	xr24,	xr25,	xr26,	xr27,	xr28,	xr29,	xr30,	xr31,
	xfr0,	xfr1,	xfr2,	xfr3,	xfr4,	xfr5,	xfr6,	xfr7,
	xfr8,	xfr9,	xfr10,	xfr11,	xfr12,	xfr13,	xfr14,	xfr15,
	xfr16,	xfr17,	xfr18,	xfr19,	xfr20,	xfr21,	xfr22,	xfr23,
	xfr24,	xfr25,	xfr26,	xfr27,	xfr28,	xfr29,	xfr30,	xfr31,
	xfcc0, 	xfcc1, 	xfcc2, 	xfcc3, 	xfcc4, 	xfcc5, 	xfcc6, 	xfcc7,
	xnoreg
    } registers;

#define n_registers 	73

#define is_int_reg(_r) ((_r) >= xr0 && (_r) <= xr31)
#define is_float_reg(_r) ((_r) >= xfr0 && (_r) <= xfr31)
#define is_ccode_reg(_r) ((_r) >= xfcc0 && (_r) <= xfcc7)


typedef enum {
	ilabel,     isym,       iglobal,    icpload,    ialign,
	iascii,     iasciiz,    ibyte,      icomm,      ilcomm,
	idata,      idouble,    ifile,      ifloat,     ihalf,
	icprestore, igpword,    icpadd,     iweakext,   iloopno,
	ispace,     itext,      iword,      iocode,     iend,
	isdata,     irdata,     ient,       iloc,       ibgnb,
	iendb,      iasm0,      iset,       icpalias,   irep,
	iendrep,    ilab,       ivreg,      imask,      ifmask,
	ierr,       iglobabs,   iverstamp,  iframe,     iextended,
	iextern,    iaent,      ioption,    inoalias,   ialias,
	imtag,      imalias,    istruct,    ilivereg, 	igjaldef,
	igjallive,  igjrlive, 	ishift_addr, irestext,  idword,
	iprologue,  iedata,     ialloc
    } itype;

#define n_itype 	63


/* asmcodes specify the assembler instructions */
typedef enum {
    zabs,       zadd,       zaddu,      zand,       zb,        	/*000-004*/
    zbc0f,      zbc0t,      zbc1f,      zbc1t,      zbc2f,     	/*005-009*/
    zbc2t,      zlgota,     z12,        zbeq,       zbge,      	/*010-014*/
    zbgeu,      zbgez,      zbgt,       zbgtu,      zbgtz,     	/*015-019*/
    zble,       zbleu,      zblez,      zblt,       zbltu,     	/*020-024*/
    zbltz,      zbne,       zbreak,     zc0,        zc1,       	/*025-029*/
    zc2,        z31,        zdiv,       zdivu,      zj,        	/*030-034*/
    zjal,       zla,        zlb,        zlbu,       zlh,       	/*035-039*/
    zlhu,       zli,        zlw,        zjr,        zlwc1,     	/*040-044*/
    zlwc2,      zpref,      zmfhi,      zmflo,      zmove,     	/*045-049*/
    zjalr,      zswc1,      zswc2,      z53,        zmthi,     	/*050-054*/
    zmtlo,      zmul,       zmulo,      zmulou,     zmult,     	/*055-059*/
    zmultu,     zneg,       znop,       znor,       zor,       	/*060-064*/
    zrem,       zremu,      zrfe,       zrol,       zror,      	/*065-069*/
    zsb,        zseq,       zsge,       zsgeu,      zsgt,      	/*070-074*/
    zsgtu,      zsh,        zsle,       zsleu,      zsll,      	/*075-079*/
    zslt,       zsltu,      zsne,       zsra,       zsrl,      	/*080-084*/
    zsub,       zsubu,      zsw,        zsyscall,   zxor,      	/*085-089*/
    znot,       zlwl,       zlwr,       zswl,       zswr,      	/*090-094*/
    zvcall,     zmfc0,      zmfc1,      zmfc2,      z99,       	/*095-099*/
    zmtc0,      zmtc1,      zmtc2,      zsync,      ztlbr,     	/*100-104*/
    ztlbwi,     ztlbwr,     ztlbp,      zld,        zsd,       	/*106-109*/
    z110,       zldc1,      zldc2,      ztlbr1,     ztlbp1,   	/*110-114*/
    zsdc1,      zsdc2,      z117,			 	/*115-117*/
    fl_s,	fl_d,		fl_e,				/*118-120*/
    fs_s,	fs_d,		fs_e,				/*121-123*/
    fadd_s,	fadd_d,		fadd_e,				/*124-126*/
    fsub_s,	fsub_d,		fsub_e,				/*127-129*/
    fmul_s,	fmul_d,		fmul_e,				/*130-132*/
    fdiv_s,	fdiv_d,		fdiv_e,				/*133-135*/
    fsqrt_s,	fsqrt_d,	fsqrt_e,		   	/*136-138*/
    fmov_s,	fmov_d,		fmov_e,				/*139-141*/
    fabs_s,	fabs_d,		fabs_e,				/*142-144*/
    fcvt_s_d,	fcvt_s_e,	fcvt_s_w,  			/*145-147*/
    fcvt_d_s,   fcvt_d_e,	fcvt_d_w,  			/*148-150*/
    fcvt_e_s,	fcvt_e_d,	fcvt_e_w,  			/*151-153*/
    fcvt_w_s,	fcvt_w_d,	fcvt_w_e,		   	/*154-156*/
    fc_f_s,	fc_f_d,		fc_f_e,				/*157-159*/
    fc_un_s,	fc_un_d,	fc_un_e,		   	/*160-162*/
    fc_eq_s,	fc_eq_d,	fc_eq_e,		   	/*163-165*/
    fc_ueq_s,	fc_ueq_d,	fc_ueq_e,		   	/*166-168*/
    fc_olt_s,	fc_olt_d,	fc_olt_e,		   	/*169-171*/
    fc_ult_s,	fc_ult_d,	fc_ult_e,		   	/*172-174*/
    fc_ole_s,	fc_ole_d,	fc_ole_e,		   	/*175-177*/
    fc_ule_s,	fc_ule_d,	fc_ule_e,		   	/*178-180*/
    fc_sf_s,	fc_sf_d,	fc_sf_e,		   	/*181-183*/
    fc_ngle_s,	fc_ngle_d,	fc_ngle_e,		   	/*184-186*/
    fc_seq_s,	fc_seq_d,	fc_seq_e,		   	/*187-189*/
    fc_ngl_s,	fc_ngl_d,	fc_ngl_e,		   	/*190-192*/
    fc_lt_s,	fc_lt_d,	fc_lt_e,		   	/*193-195*/
    fc_nge_s,	fc_nge_d,	fc_nge_e,		   	/*196-198*/
    fc_le_s,	fc_le_d,	fc_le_e,		   	/*199-201*/
    fc_ngt_s,	fc_ngt_d,	fc_ngt_e,		   	/*202-204*/
    zlui,		zulw,		zulh,		zulhu,	/*205-208*/
    zusw,		zush,		zaddi,		zaddiu,	/*209-212*/
    zslti,		zsltiu,		zandi,		zori,	/*213-216*/
    zxori,		z218,		znegu,		zbeqz,	/*217-220*/
    zbnez,							/*221*/
    fneg_s,		fneg_d,		fneg_e,			/*222-224*/
    zcfc1,		zctc1,		zbal,		zbgezal,/*225-228*/
    zbltzal,	zmtc1_d,	zmfc1_d,		   	/*229-231*/
    ztrunc_w_s,	ztrunc_w_d,	ztrunc_w_e,		   	/*232-234*/
    zround_w_s,	zround_w_d,	zround_w_e,		   	/*235-237*/
    zaddou,		zsubou,					/*238-239*/
    ztruncu_w_s,	ztruncu_w_d,	ztruncu_w_e,		/*240-242*/
    zroundu_w_s,	zroundu_w_d,	zroundu_w_e,		/*243-245*/
    zcfc0,		zcfc2,		z248,		zctc0,	/*246-249*/
    zctc2,		z251,					/*250-251*/
    fli_s,		fli_d,		fli_e,			/*252-254*/
    ztlt,		ztltu,		ztge,		ztgeu,	/*255-258*/
    zteq,		ztne,		zll,		zsc,	/*259-262*/
    zceil_w_s,	zceil_w_d,	zceil_w_e,		   	/*263-265*/
    zceilu_w_s,	zceilu_w_d,	zceilu_w_e,		   	/*266-268*/
    zfloor_w_s,	zfloor_w_d,	zfloor_w_e,		   	/*269-271*/
    zflooru_w_s,	zflooru_w_d,	zflooru_w_e,		/*272-274*/
    zbeql,          zbeqzl,         zbnel,          zbnezl,     /*275-278*/
    zblel,          zbleul,         zblezl,                     /*279-281*/
    zbgtl,          zbgtul,         zbgtzl,                     /*282-284*/
    zbltl,          zbltul,         zbltzl,         zbltzall,   /*285-288*/
    zbgel,          zbgeul,         zbgezl,         zbgezall,   /*289-292*/
    zbc0fl,         zbc0tl,         zbc1fl,         zbc1tl,     /*293-296*/
    zbc2fl,         zbc2tl,         z299,           z300,       /*297-300*/
    zldl,           zldr,           zlld,         	zlwu,   /*301-304*/
    zsdl,           zsdr,           zscd,	        	/*305-307*/
    zdaddi,         zdaddiu,        zdadd,	        zdaddu,	/*308-311*/
    zdsub,          zdsubu,         			   	/*312-313*/
    zdsll,          zdsrl,          zdsra,         		/*314-316*/
    zdsllv,         zdsrlv,         zdsrav,         	   	/*317-319*/
    zdmult,         zdmultu,        zddiv,  	zddivu,    	/*320-323*/
    zlsc1,         	zssc1,        	zdmtc1,         zdmfc1, /*324-327*/
    zdmtc0,		zdmfc0,		zdmtc2,		zdmfc2,	/*328-331*/
    zdli,		zdla,					/*332-333*/
    zeret,                                                      /*334*/
    ztrunc_l_s,     zround_l_s,     zceil_l_s,      zfloor_l_s, /*335-338*/
    ztrunc_l_d,     zround_l_d,     zceil_l_d,      zfloor_l_d, /*339-342*/
    ztrunc_l_e,     zround_l_e,     zceil_l_e,      zfloor_l_e, /*343-346*/
    fcvt_l_s,       fcvt_l_d,       fcvt_l_e,       fcvt_l_w,   /*347-350*/
    fcvt_s_l,       fcvt_d_l,       fcvt_e_l,       fcvt_w_l,   /*351-354*/
    zcache,		zcia,					/*355-356*/
    zuld,           zusd,           zdabs,          zdneg,      /*357-360*/
    zdnegu,         zdmul,          zdmulo,         zdmulou,    /*361-364*/
    zdrem,          zdremu,                                     /*365-366*/
    zdrol,          zdror,                                      /*367-368*/
    zdaddou,        zdsubou,	zulwu,		           	/*369-371*/
    zmovt,	zmovf,		zmovn,		zmovz,	   	/*372-375*/
    fmadd_s,	fmadd_d,	fmadd_e,	fmsub_s,   	/*376-379*/
    fmsub_d,	fmsub_e, 	fnmadd_s,	fnmadd_d,  	/*380-383*/
    fnmadd_e,	fnmsub_s,	fnmsub_d,	fnmsub_e,  	/*384-387*/
    frecip_s,	frecip_d,	frsqrt_s,	frsqrt_d,  	/*388-391*/
    fmovt_s,	fmovt_d,	fmovf_s,	fmovf_d,   	/*392-395*/
    fmovn_s,	fmovn_d,	fmovz_s,	fmovz_d,   	/*396-399*/
    zlwxc1,	zldxc1,		zswxc1,		zsdxc1,    	/*400-403*/
    zpfetch,	zdctr,		zdctw,		ztlbw,   	/*404-407*/	
    znada,	zssnop,						/*408-409*/
    zdsll32,	zdsrl32,	zdsra32,		        /*410-412*/
    zbc3f,	zbc3t,		zc3,		zlwc3,	   	/*413-416*/
    zswc3,	zmfc3,		zmtc3,		zcfc3,	   	/*417-420*/
    zctc3,	zsllv,		zsrlv,		zsrav,		/*421-424*/
    zmfpc,	zmtpc,		zmfps,		zmtps,	   	/*425-428*/
    zbad
} asmcodes;

#define n_asmcodes	(zbad+1)


typedef enum {
	frob,				/* reg, offset(+/-32k), base	*/
	fra,				/* reg, [sym]+offset		*/
	fri,				/* reg, immed (32 bit)		*/
	frrr,				/* reg, reg, reg 		*/
	frri,				/* reg, reg, immed (32 bit)	*/
	frr,				/* reg, reg			*/
	fa,				/* [sym]+offset [+(base)]	*/
	fr,				/* reg				*/
	frrl,				/* reg, reg, sym 		*/
	frl,				/* reg, sym			*/
	fl,				/* sym				*/
	forrr,				/* co processor if required?	*/
	fril, 				/* reg, immed, label           	*/
	fi,				/* immed		        */
	foa,				/* op, address			*/
	frrrr				/* reg, reg, reg, reg		*/
    } format;

#define n_format 16


typedef enum {
	franone 			/* default value 		*/
	,frahi				/* reg, [reg], sym[+/-offset]	*/
	,fralo				/* reg, [reg], sym[+/-offset]	*/
	,frrel1				/* reg, .[+offset]		*/
	,frrel2				/* reg, .[-offset]		*/
	,frgprel			/* reg, sym[+/-offset] + reg    */
        ,frcprel                        /* reg, sym[reg]                */
    } format_extn;

#define  n_format_extn  7

typedef enum {
	set_undefined,
	set_reorder,
	set_noreorder,
	set_macro,
	set_nomacro,
	set_at,
	set_noat,
	set_move,
	set_nomove,
	set_bopt,
	set_nobopt,
	set_volatile,
	set_novolatile,
	set_transform,
	set_notransform,
	set_reposition,
	set_noreposition
    } set_value;

#define n_set_value	17

typedef enum {
	o_undefined,
	o_optimize,
	o_pic,
	o_exception_info
    } opt_type;

#define n_opt_type	 4


typedef enum {
	opt_none,
	opt_int,
	opt_float,
	opt_string
    } opt_arg_type;


typedef unsigned asmopcode;
typedef unsigned asmformat;
typedef unsigned asmreg;
typedef int asmint;
typedef unsigned asmuint;
typedef int asmlabel;
typedef int asmsym;
typedef unsigned asmformatextn;

#define zero 0
#define float_register 32


#define binasm_record_length 16

#ifndef _REG_SET_C
#define _REG_SET_C 1
typedef unsigned aligned_regset[2];
#endif /* _REG_SET_C */

typedef union {
  char data[binasm_record_length];
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
  } common;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned lexlev;
  } ent;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    asmint frameoffset;
    asmreg framereg : 7;
    asmreg pcreg : 7;
  } frame;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned regmask;
    asmint regoffset;
  } mask;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    aligned_regset gjmask;
  } gmask;
  struct {
    asmsym symno;		/* handler */
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    int      flag;
    int      data;
  } edata;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    int loopnum;
    unsigned lflag;
  } loopno;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    int majornumber;
    int minornumber;
  } verstamp;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned filenumber;
    unsigned linenumber;
  } loc;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned gpmask;
    unsigned fpmask;
  } livereg;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned length;
    unsigned repeat;
  } chars;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    asmint expression;
    unsigned repeat;
  } value;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned option : 2;
    unsigned fill04 : 30;
    asmint opt_int_value;
  } voption;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned option : 2;
    unsigned fill04 : 30;
    asmint opt_len;
  } loption;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    asmreg basereg1 : 7;
    asmreg basereg2 : 7;
  } alias;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    int tagnumber;
    int tagtype;
  } mtag;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    int memtag1;
    int memtag2;
  } malias;

  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned fill03 : 6;
    asmopcode op : 9;		/* 9 bits plus alignment in pascal */
    asmreg reg1 : 7;
    asmreg reg2 : 7;
    asmformat form : 4;
    asmreg reg3 : 7;
  } rinst;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned fill03 : 6;
    asmopcode op : 9;		/* 9 bits plus alignment in pascal */
    asmreg reg1 : 7;
    asmreg reg2 : 7;
    asmformat form : 4;
    unsigned mem_tag : 14;
    asmint immediate;
  } iinst;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned fill03 : 6;
    asmopcode op : 9;		/* 9 bits plus alignment in pascal */
    asmreg reg1 : 7;
    asmreg reg2 : 7;
    asmformat form : 4;
    unsigned symoffset : 4;
    unsigned fill05 : 10;
    asmint immediate;
  } dinst;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned fill03 : 6;
    asmopcode op : 9;		/* 9 bits plus alignment in pascal */
    asmreg reg1 : 7;
    asmreg reg2 : 7;
    asmformat form : 4;
    asmint imm;
  } linst;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned fill03 : 6;
    asmopcode op : 9; 
    asmreg reg1 : 7;
    asmreg reg2 : 7;
    asmformat form : 4;
    asmreg reg3 : 7;
    asmreg reg4 : 7;
  } rrinst;
} binasm;

#endif /* _LANGUAGE_C */
