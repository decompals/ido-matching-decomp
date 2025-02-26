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
/* $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/cmplrs/RCS/ucode.h,v 7.13 1995/12/05 19:30:47 jfw Exp $ */

/* LOD, ILOD, STR, ISTR flags (lexlev field) */
#define VOLATILE_ATTR 1         /* data is volatile */

/* ABS, ADD, SQR, CVT, CVTL, DEC, INC, NEG, DIV, MOD, MPY, SUB and
   REM flags (lexlev field) */
#define OVERFLOW_ATTR 2		/* overflow checking required */

/* Data area designation (lexlev field)
 * Four bits are reserved to designate the data area.
 * Default means the data area is selected based upon size and initialization
 * This field occupies the high order 4 bits of the lexlevel field
 */
#define DATA_AREA_MASK 240      /* 0xF0 mask to isolate this field          */
#define DATA_AREA_BIT_OFS 4     /* number of bits to shift to get this field*/
#define DEFAULT_DATA_AREA 0     /* data defaults into appropriate data area */
#define READONLY_DATA_AREA 1    /* data put in readonly data area (rdata)   */
#define SMALL_DATA_AREA 2       /* data put in small data area (sdata,sbss) */
#define LARGE_DATA_AREA 3       /* data put in large data area (data,bss)   */
#define TEXT_AREA 4 	        /* data put in text area */
#define EXCEPTION_DATA_AREA 5 	/* data put in exception area */

/* ENT flag attributes (extrnal field) */
#define EXTERNAL_ATTR       1	/* external entry point */
#define FRAMEPTR_ATTR       2	/* manifest real frame pointer */
#define PRESERVE_STACK_ATTR 4	/* prevent cutting back stack on exit */
#define STACK_OVERFLOW_ATTR  8	/* check for stack overflow */
#define LOAD_STACKLIMIT_ON_ENTRY_ATTR 16 /* load stack limit register */
#define NO_INLINE_ATTR	    32	/* disable inlining */
#define VARSIZE_LOCAL_ATTR  64  /* some local var with relocatable sizes */
#define VARARG_SUB_ATTR    128  /* the function is a variable argument rtn */
#define IS_VARARG_SUB_ATTR(x) (bitand(x, VARARG_SUB_ATTR) <> 0)
#define THUNK_ENT_ATTR	    256	/* A thunk function */
#define RA_OFFSET_ATTR	512	/* offset to save/restore return address */

/* CUP flag attributes (extrnal field) */
#define NOSIDEEFFECT_ATTR 1		/* indicates call has no side effect */
#define RETURN_ATTR 2			/* indicates call will not return */
/* 4 used in 1.31 for reloading stack limit for ada, but then removed in 2.0 */
#define REALLOC_ARG_ATTR 8              /* reallocate the arg build area */
#define GOTO_ATTR 16			/* indicates call is the Pascal GOOB*/
#define COMPOSITE_CALL_ATTR 32 		/* call returns a composite object */
#define INLINE_ATTR  64			/* inline call */
#define THUNK_CALL_ATTR   128		/* The call in thunk functions */
#define TEMP_REGISTERS_INTACT_ATTR 256	/* The call leaves temp regs intact */

/* CUP flag attributes (push field) */
#define STDARGS_NUM_MASK 224	/* 0xE0 mask to isolate this field */
#define STDARGS_NUM_BIT_OFS 5     /* number of bits to shift to get this field*/
#define STDARGS_NUM_MAX	4  /* max vararg starting position encodable */
			   /* beyond STDARGS_NUM_MAX, use STDARGS_NUM_MAX */
			   /* since there is no effect > 4 anyways (for now */

/* LAB flag attributes (lexlev field) */
#define GOOB_TARGET    1	/* label is target of GOOB (non-local goto) */
#define EXCEPTION_ATTR 2        /* label is jumped to due to an exception */
#define EXTERN_LAB_ATTR 4	/* label is referenced both externally and 
				   internally (for PL/1 only) */
#define IJP_ATTR 8		/* label is target of IJP (for f77 and PL/1) */
#define EXCEPTION_END_ATTR 16	/* label is jumped to due to an exception end*/
#define EXCEPTION_FRAME_ATTR 32	/* code region covered by exception handler */


#define EXCEPTION_FRAME_START_ATTR    EXCEPTION_FRAME_ATTR
#define EXCEPTION_FRAME_END_ATTR      64
#define EXCEPTION_FRAME_TRY_START_ATTR 128
#define EXCEPTION_FRAME_TRY_END_ATTR   256
#define EXCEPTION_HANDLER_START_ATTR  EXCEPTION_ATTR
#define EXCEPTION_HANDLER_END_ATTR    EXCEPTION_END_ATTR

/* PDEF flag attributes (lexlev field) */
#define IN_MODE     1  		/* parameter passing modes */
#define OUT_MODE    2
#define INOUT_MODE  3

#ifdef _LANGUAGE_PASCAL
(*****************************************************************************)
(* This file contains all types that define U-code			     *)
(*****************************************************************************)

/* macros to test and set attributes */
#define IS_INLINE_ATTR(x) (bitand(x, INLINE_ATTR) <> 0)
#define SET_INLINE_ATTR(x) x := bitor(x, INLINE_ATTR)
#define IS_VOLATILE_ATTR(x) (bitand(x, VOLATILE_ATTR) <> 0)
#define SET_VOLATILE_ATTR(x) x := bitor(x, VOLATILE_ATTR)
#define RESET_VOLATILE_ATTR(x) x := bitand(x, bitnot(VOLATILE_ATTR))
#define IS_FRAMEPTR_ATTR(x) (bitand(x, FRAMEPTR_ATTR) <> 0)
#define SET_FRAMEPTR_ATTR(x) x := bitor(x, FRAMEPTR_ATTR)
#define IS_EXTERNAL_ATTR(x) (bitand(x, EXTERNAL_ATTR) <> 0)
#define IS_OVERFLOW_ATTR(x) (bitand(x, OVERFLOW_ATTR) <> 0)
#define SET_OVERFLOW_ATTR(x) x := bitor(x, OVERFLOW_ATTR)
#define IS_PRESERVE_STACK_ATTR(x) (bitand(x, PRESERVE_STACK_ATTR) <> 0)
#define SET_PRESERVE_STACK_ATTR(x) x := bitor(x, PRESERVE_STACK_ATTR)
#define IS_EXCEPTION_ATTR(x) (bitand(x, EXCEPTION_ATTR) <> 0)
#define SET_EXCEPTION_ATTR(x) x := bitor(x, EXCEPTION_ATTR)
#define IS_EXCEPTION_FRAME_ATTR(x) (bitand(x, EXCEPTION_FRAME_ATTR) <> 0)
#define SET_EXCEPTION_FRAME_ATTR(x) x := bitor(x, EXCEPTION_FRAME_ATTR)
#define IS_EXCEPTION_END_ATTR(x) (bitand(x, EXCEPTION_END_ATTR) <> 0)
#define SET_EXCEPTION_END_ATTR(x) x := bitor(x, EXCEPTION_END_ATTR)
#define IS_EXCEPTION_HANDLER_END_ATTR(x) (bitand(x, EXCEPTION_HANDLER_END_ATTR) <> 0)
#define SET_EXCEPTION_HANDLER_END_ATTR(x) x := bitor(x, EXCEPTION_HANDLER_END_ATTR)
#define IS_EXCEPTION_HANDLER_START_ATTR(x) (bitand(x, EXCEPTION_HANDLER_START_ATTR) <> 0)
#define SET_EXCEPTION_HANDLER_START_ATTR(x) x := bitor(x, EXCEPTION_HANDLER_START_ATTR)
#define IS_EXCEPTION_FRAME_END_ATTR(x) (bitand(x, EXCEPTION_FRAME_END_ATTR) <> 0)
#define SET_EXCEPTION_FRAME_END_ATTR(x) x := bitor(x, EXCEPTION_FRAME_END_ATTR)
#define IS_EXCEPTION_FRAME_START_ATTR(x) (bitand(x, EXCEPTION_FRAME_START_ATTR) <> 0)
#define SET_EXCEPTION_FRAME_START_ATTR(x) x := bitor(x, EXCEPTION_FRAME_START_ATTR)
#define IS_EXCEPTION_FRAME_TRY_END_ATTR(x) (bitand(x, EXCEPTION_FRAME_TRY_END_ATTR) <> 0)
#define SET_EXCEPTION_FRAME_TRY_END_ATTR(x) x := bitor(x, EXCEPTION_FRAME_TRY_END_ATTR)
#define IS_EXCEPTION_FRAME_TRY_START_ATTR(x) (bitand(x, EXCEPTION_FRAME_TRY_START_ATTR) <> 0)
#define SET_EXCEPTION_FRAME_TRY_START_ATTR(x) x := bitor(x, EXCEPTION_FRAME_TRY_START_ATTR)
#define IS_EXTERN_LAB_ATTR(x) (bitand(x, EXTERN_LAB_ATTR) <> 0)
#define SET_EXTERN_LAB_ATTR(x) x := bitor(x, EXTERN_LAB_ATTR)
#define IS_IJP_ATTR(x) (bitand(x, IJP_ATTR) <> 0)
#define SET_IJP_ATTR(x) x := bitor(x, IJP_ATTR)
#define IS_STACK_OVERFLOW_ATTR(x) (bitand(x, STACK_OVERFLOW_ATTR) <> 0)
#define SET_STACK_OVERFLOW_ATTR(x)  x := bitor(x, STACK_OVERFLOW_ATTR)
#define	IS_LOAD_STACKLIMIT_ON_ENTRY_ATTR(x) (bitand(x, LOAD_STACKLIMIT_ON_ENTRY_ATTR) <> 0)
#define SET_NO_INLINE_ATTR(x)  x := bitor(x, NO_INLINE_ATTR)
#define IS_NO_INLINE_ATTR(x) (bitand(x, NO_INLINE_ATTR) <> 0)
#define SET_LOAD_STACKLIMIT_ON_ENTRY_ATTR(x) x := bitor(x, LOAD_STACKLIMIT_ON_ENTRY_ATTR)

#define SET_THUNK_ENT_ATTR(x)  x := bitor(x, THUNK_ENT_ATTR)
#define IS_THUNK_ENT_ATTR(x) (bitand(x, THUNK_ENT_ATTR) <> 0)
#define SET_THUNK_CALL_ATTR(x)  x := bitor(x, THUNK_CALL_ATTR)
#define IS_THUNK_CALL_ATTR(x) (bitand(x, THUNK_CALL_ATTR) <> 0)
#define SET_RA_OFFSET_ATTR(x)  x := bitor(x, RA_OFFSET_ATTR)
#define IS_RA_OFFSET_ATTR(x) (bitand(x, RA_OFFSET_ATTR) <> 0)

#define IS_REALLOC_ARG_ATTR(x) (bitand(x, REALLOC_ARG_ATTR) <> 0)
#define SET_REALLOC_ARG_ATTR(x) x := bitor(x, REALLOC_ARG_ATTR)

#define SET_DATA_AREA(x,v) x := bitor(bitand(x,bitnot(DATA_AREA_MASK)),lshift(v,DATA_AREA_BIT_OFS))
#define GET_DATA_AREA(x) rshift(bitand(x,DATA_AREA_MASK),DATA_AREA_BIT_OFS)
#define IS_RETURN_ATTR(x) (bitand(x, RETURN_ATTR) <> 0)
#define SET_RETURN_ATTR(x) x := bitor(x, RETURN_ATTR)
#define IS_NOSIDEEFFECT_ATTR(x) (bitand(x, NOSIDEEFFECT_ATTR) <> 0)
#define SET_NOSIDEEFFECT_ATTR(x) x := bitor(x, NOSIDEEFFECT_ATTR)
#define IS_GOTO_ATTR(x) (bitand(x, GOTO_ATTR) <> 0)
#define SET_GOTO_ATTR(x) x := bitor(x, GOTO_ATTR)
#define IS_COMPOSITE_CALL_ATTR(x) (bitand(x, COMPOSITE_CALL_ATTR) <> 0)
#define SET_COMPOSITE_CALL_ATTR(x) x := bitor(x, COMPOSITE_CALL_ATTR)
#define SET_STDARGS_NUM(x,v) x := bitor(bitand(x,bitnot(STDARGS_NUM_MASK)),lshift(v,STDARGS_NUM_BIT_OFS))
#define GET_STDARGS_NUM(x) rshift(bitand(x,STDARGS_NUM_MASK),STDARGS_NUM_BIT_OFS)
#define IS_TEMP_REGISTERS_INTACT_ATTR(x) (bitand(x, TEMP_REGISTERS_INTACT_ATTR) <> 0)
#define SET_TEMP_REGISTERS_INTACT_ATTR(x) x := bitor(x, TEMP_REGISTERS_INTACT_ATTR)

const
  (* set constant representation in Ucode				     *)
  Maxoperands = 10;			(* maximum number of operands in     *)
					(* u-code instruction + 1	     *)
  Maxinstlength = 8;			{length in words of ucode record}
type
  Datatype = (Adt,			(* address (pointer)		     *)
      Cdt,			 	(* pointer to readonly data	     *)
      Fdt,				(* pointer to procedure		     *)
      Gdt,				(* address of a label		     *)
      Hdt,				(* address that only points to heap  *)
      Idt,				(* integer, double word		     *)
      Jdt,				(* integer, single word 	     *)
      Kdt,				(* unsigned integer, double word     *)
      Ldt,				(* non-negative integer, single word *)
      Mdt,				(* array or record		     *)
      Ndt,				(* non-local label 	             *)
      Pdt,				(* procedure, untyped		     *)
      Qdt,				(* real, double word		     *)
      Rdt,				(* real, single word		     *)
      Sdt,				(* set				     *)
      Wdt,				(* 64 bit wide pointer               *)
      Xdt,				(* extended precision		     *)
      Zdt); 				(* undefined			     *)


  Memtype  = (Zmt, 			(* undefined			     *)
      Mmt,				(* complex variables		     *)
      Pmt, 				(* parameters			     *)
      Rmt,				(* register			     *)
      Smt,				(* statically allocated memory	     *)
      Amt,				(* Parameter build area		     *)
      Tmt,				{  used internally by ugen	      }
      Kmt				{static class data member in C++      }
      );

  (***************************************************************************)
  (* constants								     *)
  (***************************************************************************)
  Valuptr = ^Valu;
  Stringtext = record
		case integer of
		0: (ss: packed array[1..Strglgth] of char);
		1:  (ssarray: array[1..
			(Strglgth+HostCharsPerWord-1) div HostCharsPerWord] of
			integer);
#ifdef _LONGLONG
		2:  (ssdwarray: array[1..
			(Strglgth+HostCharsPerDWord-1) div HostCharsPerDWord] of
			integer64);
#endif
		end;
  Stringtextptr = ^Stringtext;
  Strg =
    record
      Len      : 0..65535;
      Chars    : Stringtextptr;
    end {record};
  Valu =
    record				(* describes a constant value	     *)
      case Datatype of
#ifdef _LONGLONG
	Idt, Kdt, Wdt: (
	  dwval: integer64);
#endif
	Zdt: (
#ifdef _MIPSEL
	  dwval_l, dwval_h: integer);
#else	/* _MIPSEB */
	  dwval_h, dwval_l: integer);
#endif
	Adt, Hdt, Ldt, Jdt, Fdt, Gdt, Ndt,
	Mdt, Qdt, Rdt, Sdt, Xdt: (
	  Ival: integer;
	  case Datatype of
	    Adt, Hdt, Ldt, Jdt, Fdt, Gdt, Ndt: ();
	    Mdt, Qdt, Rdt, Sdt, Xdt:
	    (* Ival gives the length of the string in Chars *)
	      (Chars    : Stringtextptr))
    end {record};

  (***************************************************************************)
  (* ucode instructions 						     *)
  (***************************************************************************)

  Uopcode  = (
	Uabs,	Uadd,	Uadj,	Uaent,	Uand,	Uaos,	Uasym,	Ubgn,
	Ubgnb,	Ubsub,	Ucg1,	Ucg2,	Uchkh,	Uchkl,	Uchkn,	Uchkt,
	Ucia,	Uclab,	Uclbd,	Ucomm,	Ucsym,	Uctrl,	Ucubd,	Ucup,
	Ucvt,	Ucvtl,	Udec,	Udef,	Udif,	Udiv,	Udup,	Uend,
	Uendb,	Uent,	Ueof,	Uequ,	Uesym,	Ufill,	Ufjp,	Ufsym,
	Ugeq,	Ugrt,	Ugsym,	Uhsym,	Uicuf,	Uidx,	Uiequ,	Uigeq,
	Uigrt,	Uijp,	Uilda,	Uildv,	Uileq,	Uiles,	Uilod,	Uinc,
	Uineq,	Uinit,	Uinn,	Uint,	Uior,	Uisld,	Uisst,	Uistr,
	Uistv,	Uixa,	Ulab,	Ulbd,	Ulbdy,	Ulbgn,	Ulca,	Ulda,
	Uldap,	Uldc,	Uldef,	Uldsp,	Ulend,	Uleq,	Ules,	Ulex,
	Ulnot,	Uloc,	Ulod,	Ulsym,	Ultrm,	Umax,	Umin,	Umod,
	Umov,	Umovv,	Umpmv,	Umpy,	Umst,	Umus,	Uneg,	Uneq,
	Unop,	Unot,	Uodd,	Uoptn,	Upar,	Updef,	Upmov,	Upop,
	Uregs,	Urem,	Uret,	Urlda,	Urldc,	Urlod,	Urnd,	Urpar,
	Urstr,	Usdef,	Usgs,	Ushl,	Ushr,	Usign,	Usqr,	Usqrt,	
	Ussym,	Ustep,	Ustp,	Ustr,	Ustsp,	Usub,	Uswp,	Utjp,	
	Utpeq,	Utpge,	Utpgt,	Utple,	Utplt,	Utpne,	Utyp,	Uubd,	
	Uujp,	Uunal,	Uuni,	Uvreg,	Uxjp,	Uxor,	Uxpar,  Umtag,
	Ualia,	Uildi,  Uisti,  Uirld,	Uirst,	Uldrc,	Umsym,	Urcuf,
        Uksym,	Uosym,  Uirlv,  uirsv);
/* The following opcodes are only used internally in UOPT: MOVV, ILDV, ISTV. */
/* The following opcodes are only used internally in UGEN: CG1, CG2. */
/* Warning: Add ucodes at the end only */


  Bcrec = packed record /* minimum length in ucode file is 1 double word */
      case integer of
	0 : (
	  Opc	   : Uopcode;				{ 8 bits }
	  Mtype    : first(Memtype)..last(Memtype);	{ 3 bits }
	  Dtype    : first(Datatype)..last(Datatype);	{ 5 bits }
	  Lexlev   : 0..65535;				{ 16 bits }
	  I1	   : integer;				{ 32 bits }
	  /* ------- 2 words ------- */
	  case Uopcode of
	    Ucvt : (
	      Dtype2 : first(Datatype)..Datatype(255)); { 8 bits }
	    Uent, Ucup: (
	      Pop, Push: 0..255;
	      Extrnal:   integer);
	    Uiequ : (
	      Length : integer;
	      Offset : integer;
	  /* ------- 4 words ------- */
	      case Uopcode of
		Uldc : (
		  Constval : Valu);
	  /* ------- 6 words ------- */
		Uinit : (
		  Offset2  : integer;
		  aryoff   : integer;
	  /* ------- 6 words ------- */
		  Initval  : Valu);
		Uxjp : (
		  case boolean of
#ifdef _LONGLONG
		  false: (
		    lbound,
		    hbound: integer64);
#endif
		  true: (
#ifdef _MIPSEL
		    lbound_l, lbound_h,
		    hbound_l, hbound_h: integer);
#else	/* _MIPSEB */
		    lbound_h, lbound_l,
		    hbound_h, hbound_l: integer);
#endif
		  )
		)
	);
	1 : (
	  Intarray : array[1..Maxinstlength] of integer);
#ifdef _LONGLONG
	2 : (
	  dw_array : array[1..(Maxinstlength div 2)] of integer64);
#endif
    end {record};

  (***************************************************************************)
  (* source line buffer 						     *)
  (***************************************************************************)
  Sourceline = packed array[1..Strglgth] of char;

  Opcstring = packed array[1..4] of char; (* string representation of an     *)
					(* Uopcode			     *)
  (* different types of operands in a u-code inustrtion 		     *)

  Uoperand = (Sdtype, Smtype, Slexlev, Slabel0, Slabel1, Sblockno, Sdtype2,
	  Spop, Spush, Sexternal, Slength, Sconstval, Scomment, Soffset, 
	  Ssomenumber, Soffset2, Sinitval, Slabel2, SarrayOffset, 
	  Sdtypenum, Slbound, Shbound, Send);
  (* describes the order and type of operands in a u-code instruction	     *)
  { Slabel0: label stored in the I1 field that is a label that needs to be
	     written left-justified in ascii ucode;
    Slabel1: label stored in the I1 field that is a label but does not need
	     to be written left-justified in ascii ucode;
    Slabel2: label stored in the Length field;
    Sblockno: the I1 field storing a block number;
    Scomment: the constval field storing a comment;
    Ssomenumber: the I1 field not storing a block number;
    Sdtypenum: the dtype field storing a number;		}
  Uops	   = array[1..Maxoperands] of Uoperand;

  utabrec  =
    record
      Format   : Uops;			(* operands			     *)
      Opcname  : Opcstring;		(* opcode name table		     *)
      Hasattr,				(* true if using lexlev field for \v
					   and \o attributes *)
      Hasconst : boolean;		(* true if instruction requirs	     *)
					(* constant			     *)
      Instlength : 1..Maxinstlength;	(* length of instruction	     *)
      stack_pop: 0..3;			{whether leaf, unary or binary op}
      stack_push: 0..1;			{whether statement or expression}
    end {record};

  {types of memory tags for ILOD and ISTR}
  mtagtype =   (mtag_anything, 		{can dereference anything}
		mtag_heap,		{only dereference heap memory}
		mtag_readonly,		{only dereference readonly memory}
		mtag_non_local,		{only dereference non-local memory}

		mtag_local_stack,	{only dereference local M memory}
		mtag_uplevel_stack,	{only dereference up-level M memory}
		mtag_local_static,	{only dereference FSYM symbols}
		mtag_global_static,   {only dereference non-FSYM static symbols}

		mtag_f77_parm,		{based on a specific f77 parameter}
		mtag_vreg);		{only emitted by ugen}
  {mtag_anything, mtag_heap, mtag_readonly and mtag_non_local each corresponds 
   to 1-and-only-1 tag number; for local_stack, uplevel_stack, local_static and
   global_static, each block number will result in one or more tag numbers;
   for mtag_f77_parm, each f77 parameter will result in 1-and-only-1 tag number}


#endif

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
/* This file MUST correspond to the Pascal definitions found above.
   This represents a fast transliteration of part of it to C (by
   no means is it complete, although the structure was successfully
   used to write binary UCODES and read them back by Pascal programs
   that read the binary form of UCODE).			*/

/*****************************************************************************/
/* This file contains all types that define U-code			     */
/*****************************************************************************/
  /* set constant representation in Ucode				     */
#define  Maxoperands  10		/* maximum number of operands in     */
					/* u-code instruction + 1	     */
#define  Maxinstlength  8		/* maximum size of a b-code	     */
					/* instruction, in host words, = max */
					/* (size of largest set constant (in */
					/* bits), size of largest string     */
					/* constant (in bits)) div wordsize+ */
					/* 2;				     */

/* macros to test and set attributes */
#define IS_INLINE_ATTR(x) (x & INLINE_ATTR) 
#define SET_INLINE_ATTR(x) x = (x | INLINE_ATTR)
#define IS_VOLATILE_ATTR(x) (x & VOLATILE_ATTR) 
#define SET_VOLATILE_ATTR(x) x = (x | VOLATILE_ATTR)
#define IS_FRAMEPTR_ATTR(x) (x & FRAMEPTR_ATTR) 
#define SET_FRAMEPTR_ATTR(x) x = (x | FRAMEPTR_ATTR)
#define IS_EXTERNAL_ATTR(x) (x & EXTERNAL_ATTR) 
#define IS_OVERFLOW_ATTR(x) (x & OVERFLOW_ATTR) 
#define SET_OVERFLOW_ATTR(x) x = (x | OVERFLOW_ATTR)
#define IS_PRESERVE_STACK_ATTR(x) (x & PRESERVE_STACK_ATTR)
#define SET_PRESERVE_STACK_ATTR(x) x = (x | PRESERVE_STACK_ATTR)
#define IS_EXCEPTION_ATTR(x) (x & EXCEPTION_ATTR)
#define SET_EXCEPTION_ATTR(x) x = (x | EXCEPTION_ATTR)
#define IS_EXCEPTION_END_ATTR(x) (x & EXCEPTION_END_ATTR)
#define SET_EXCEPTION_END_ATTR(x) x = (x | EXCEPTION_END_ATTR)
#define IS_EXTERN_LAB_ATTR(x) (x & EXTERN_LAB_ATTR)
#define SET_EXTERN_LAB_ATTR(x) x = (x | EXTERN_LAB_ATTR)
#define IS_STACK_OVERFLOW_ATTR(x) (x & STACK_OVERFLOW_ATTR)
#define SET_STACK_OVERFLOW_ATTR(x)  x = (x |  STACK_OVERFLOW_ATTR)
#define	IS_LOAD_STACKLIMIT_ON_ENTRY_ATTR(x) (x & LOAD_STACKLIMIT_ON_ENTRY_ATTR)
#define SET_LOAD_STACKLIMIT_ON_ENTRY_ATTR(x) x = (x | LOAD_STACKLIMIT_ON_ENTRY_ATTR)
#define SET_NO_INLINE_ATTR(x) x = (x | NO_INLINE_ATTR)
#define IS_NO_INLINE_ATTR(x) (x & NO_INLINE_ATTR)
#define IS_REALLOC_ARG_ATTR(x) (x & REALLOC_ARG_ATTR)
#define SET_REALLOC_ARG_ATTR(x) x = (x | REALLOC_ARG_ATTR)

#define SET_DATA_AREA(x,v) x = ((x & ~DATA_AREA_MASK)|(v << DATA_AREA_BIT_OFS))
#define GET_DATA_AREA(x) ((x & DATA_AREA_MASK) >> DATA_AREA_BIT_OFS)
#define IS_RETURN_ATTR(x) (x & RETURN_ATTR)
#define SET_RETURN_ATTR(x) x = (x | RETURN_ATTR)
#define IS_NOSIDEEFFECT_ATTR(x) (x & NOSIDEEFFECT_ATTR)
#define SET_NOSIDEEFFECT_ATTR(x) x = (x | NOSIDEEFFECT_ATTR)
#define IS_GOTO_ATTR(x) (x & GOTO_ATTR)
#define SET_GOTO_ATTR(x) x = (x | GOTO_ATTR)
#define IS_COMPOSITE_CALL_ATTR(x) (x & COMPOSITE_CALL_ATTR)
#define SET_COMPOSITE_CALL_ATTR(x) x = (x | COMPOSITE_CALL_ATTR)
#define SET_STDARGS_NUM(x,v) x = ((x & ~STDARGS_NUM_MASK)|(v << STDARGS_NUM_BIT_OFS))
#define GET_STDARGS_NUM(x) ((x & STDARGS_NUM_MASK) >> STDARGS_NUM_BIT_OFS)
#define IS_TEMP_REGISTERS_INTACT_ATTR(x) (x & TEMP_REGISTERS_INTACT_ATTR)
#define SET_TEMP_REGISTERS_INTACT_ATTR(x)  x = (x | TEMP_REGISTERS_INTACT_ATTR)


  enum
  Datatype  {Adt,			/* address (pointer)		     */
      Cdt,				/* pointer to readonly data	     */
      Fdt,				/* C pointer to function	     */
      Gdt,				/* address of label		    */
      Hdt,				/* address that only points to heap  */
      Idt,				/* integer, double word		     */
      Jdt,				/* integer, single word 	     */
      Kdt,				/* unsigned integer, double word     */
      Ldt,				/* non-negative integer, single word */
      Mdt,				/* array or record		     */
      Ndt,				/* non-local labels		     */
      Pdt,				/* procedure, untyped		     */
      Qdt,				/* real, double word		     */
      Rdt,				/* real, single word		     */
      Sdt,				/* set				     */
      Wdt,				/* 64 bit wide pointer		     */
      Xdt,				/* extended precision		     */
      Zdt}; 				/* undefined			     */


enum
Memtype
 {    Zmt, 				/*				     */
      Mmt,				/* complex variables		     */
      Pmt, 				/* parameters			     */
      Rmt,				/* register			     */
      Smt,				/* statically allocated memory	     */
      Amt,				/* Parameter build area	   	     */
      Tmt,			        /* used internally by ugen	     */
      Kmt				/* static class data member in C++   */
 } ;



  /***************************************************************************/
  /* constants								     */
  /***************************************************************************/
typedef char Stringtext[Strglgth];

union Valu {
#ifdef _LONGLONG
  long long dwval;
#endif
  struct {
#ifdef _MIPSEL
    int dwval_l, dwval_h;
#else /* _MIPSEB */
    int dwval_h, dwval_l;
#endif
    } dwpart;
  struct {
    int Ival;
    char *Chars;
    } swpart;
};

  /***************************************************************************/
  /* ucode instructions 						     */
  /***************************************************************************/

enum 
  Uopcode   {
	Uabs,	Uadd,	Uadj,	Uaent,	Uand,	Uaos,	Uasym,	Ubgn,
	Ubgnb,	Ubsub,	Ucg1,	Ucg2,	Uchkh,	Uchkl,	Uchkn,	Uchkt,
	Ucia,	Uclab,	Uclbd,	Ucomm,	Ucsym,	Uctrl,	Ucubd,	Ucup,
	Ucvt,	Ucvtl,	Udec,	Udef,	Udif,	Udiv,	Udup,	Uend,
	Uendb,	Uent,	Ueof,	Uequ,	Uesym,	Ufill,	Ufjp,	Ufsym,
	Ugeq,	Ugrt,	Ugsym,	Uhsym,	Uicuf,	Uidx,	Uiequ,	Uigeq,
	Uigrt,	Uijp,	Uilda,	Uildv,	Uileq,	Uiles,	Uilod,	Uinc,
	Uineq,	Uinit,	Uinn,	Uint,	Uior,	Uisld,	Uisst,	Uistr,
	Uistv,	Uixa,	Ulab,	Ulbd,	Ulbdy,	Ulbgn,	Ulca,	Ulda,
	Uldap,	Uldc,	Uldef,	Uldsp,	Ulend,	Uleq,	Ules,	Ulex,
	Ulnot,	Uloc,	Ulod,	Ulsym,	Ultrm,	Umax,	Umin,	Umod,
	Umov,	Umovv,	Umpmv,	Umpy,	Umst,	Umus,	Uneg,	Uneq,
	Unop,	Unot,	Uodd,	Uoptn,	Upar,	Updef,	Upmov,	Upop,
	Uregs,	Urem,	Uret,	Urlda,	Urldc,	Urlod,	Urnd,	Urpar,
	Urstr,	Usdef,	Usgs,	Ushl,	Ushr,	Usign,	Usqr,	Usqrt,	
	Ussym,	Ustep,	Ustp,	Ustr,	Ustsp,	Usub,	Uswp,	Utjp,	
	Utpeq,	Utpge,	Utpgt,	Utple,	Utplt,	Utpne,	Utyp,	Uubd,	
	Uujp,	Uunal,	Uuni,	Uvreg,	Uxjp,	Uxor,	Uxpar,  Umtag,
	Ualia,	Uildi,  Uisti,  Uirld,	Uirst,	Uldrc,	Umsym,	Urcuf,
        Uksym,	Uosym,  Uirlv,  uirsv};
/* The following opcodes are only used internally in UOPT: MOVV, ILDV, ISTV. */
/* The following opcodes are only used internally in UGEN: CG1, CG2. */
/* Warning: Add ucodes at the end only */

struct Bcrec   { 
	  unsigned int  Opc :8;	
	  unsigned int  Mtype :3;	
	  unsigned int  Dtype :5;	
	  unsigned int  Lexlev :16;  		
	  int  I1;         
	  /* ------- 2 words ------- */
	  union {
	    struct {
	      enum Datatype Dtype2:8; unsigned :24;
	    }secondty;
	    struct {
	       unsigned int Pop :8, Push :8, Extrnal :32;
	    }uent;
            struct {
	      int Length;
	      int offset;
	  /* ------- 4 words ------- */
	      union {
		union Valu Constval;
	  /* ------- 6 words ------- */
		union {
#ifdef _LONGLONG
		  struct {
		    long long lbound;
		    long long hbound;
		    } dwbnds;
#endif
		  struct {
#ifdef _MIPSEL
		    int lbound_l, lbound_h;
		    int hbound_l, hbound_h;
#else	/* _MIPSEB */
		    int lbound_h, lbound_l;
		    int hbound_h, hbound_l;
#endif
		    } swbnds;
		  } uxjp;
	        struct {
		      int offset2;
		      int aryoff;
		      union Valu initval;
	  /* ------- 8 words ------- */
		    } uinit;
              }uop2;
	    }uiequ1;
	  }Uopcde;
};

union Bcode {
  struct Bcrec Ucode;
  int intarray[Maxinstlength];
#ifdef _LONGLONG
  long long dw_array[Maxinstlength / 2];
#endif
}Uc;

/* access paths to members of the U_code structure */
#define UCVT    Uopcde
#define UENT    Uopcde.uent
#define UIEQU   Uopcde.uiequ1
#define OPC     Uc.Ucode.Opc
#define DTYPE   Uc.Ucode.Dtype
#define MTYPE   Uc.Ucode.Mtype
#define LEXLEV  Uc.Ucode.Lexlev
#define IONE    Uc.Ucode.I1
#define DTYPE2  Uc.Ucode.Uopcde.secondty.Dtype2
#define POP     Uc.Ucode.Uopcde.uent.Pop
#define PUSH    Uc.Ucode.Uopcde.uent.Push
#define EXTRNAL Uc.Ucode.Uopcde.uent.Extrnal
#define LENGTH  Uc.Ucode.Uopcde.uiequ1.Length
#define OFFSET   Uc.Ucode.Uopcde.uiequ1.offset
#define CONSTVAL Uc.Ucode.Uopcde.uiequ1.uop2.Constval
#define OFFSET2  Uc.Ucode.Uopcde.uiequ1.uop2.uinit.offset2
#define ARYOFF   Uc.Ucode.Uopcde.uiequ1.uop2.uinit.aryoff
#define INITVAL  Uc.Ucode.Uopcde.uiequ1.uop2.uinit.initval
#define LBOUND  Uc.Ucode.Uopcde.uiequ1.uop2.uxjp.dwbnds.lbound
#define HBOUND  Uc.Ucode.Uopcde.uiequ1.uop2.uxjp.dwbnds.hbound
#define LBOUND_L  Uc.Ucode.Uopcde.uiequ1.uop2.uxjp.swbnds.lbound_l
#define LBOUND_H  Uc.Ucode.Uopcde.uiequ1.uop2.uxjp.swbnds.lbound_h
#define HBOUND_L  Uc.Ucode.Uopcde.uiequ1.uop2.uxjp.swbnds.hbound_l
#define HBOUND_H  Uc.Ucode.Uopcde.uiequ1.uop2.uxjp.swbnds.hbound_h

enum uoperand {Sdtype, Smtype, Slexlev, Slabel0, Slabel1, Sblockno, Sdtype2,
	  Spop, Spush, Sexternal, Slength, Sconstval, Scomment, Soffset, 
	  Ssomenumber, Soffset2, Sinitval, Slabel2, SarrayOffset, 
	  Sdtypenum, Slbound, Shbound, Send};
  /* describes the order and type of operands in a u-code instruction:
    Slabel0: label stored in the I1 field that is a label that needs to be
	     written left-justified in ascii ucode;
    Slabel1: label stored in the I1 field that is a label but does not need
	     to be written left-justified in ascii ucode;
    Slabel2: label stored in the Length field;
    Sblockno: the I1 field storing a block number;
    Scomment: the constval field storing a comment;
    Ssomenumber: the I1 field not storing a block number;
    Sdtypenum: the dtype field storing a number;		*/

enum mtagtype {
    mtag_anything, 		/* can dereference anything */
    mtag_heap,			/* only dereference heap memory */
    mtag_readonly,		/* only dereference readonly memory */
    mtag_non_local,		/* only dereference non-local memory */
    mtag_local_stack,		/* only dereference local M memory */
    mtag_uplevel_stack,		/* only dereference up-level M memory */
    mtag_local_static,		/* only dereference FSYM symbols */
    mtag_global_static,		/* only dereference non-FSYM static symbols */
    mtag_f77_parm,		/* based on a specific f77 parameter */
    mtag_vreg 			/* only emitted by ugen */
};

#endif /* (C) */
