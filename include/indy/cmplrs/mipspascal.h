/*
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991, 1990 MIPS Computer Systems, Inc.      |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 252.227-7013.  |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Avenue                               |
 * |         Sunnyvale, California 94088-3650, USA             |
 * |-----------------------------------------------------------|
 */
/* $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/cmplrs/RCS/mipspascal.h,v 7.3 1992/01/20 13:00:09 daveb Exp $ */
#ifdef _PASTEL
/* Define all these in uppercase as well?? */
#define lbound lowerbound
#define hbound upperbound
/* use "And" instead of "and" to prevent further expansion into "andif". */
#define bitand(_a,_b) ((_a) And (_b))
#define bitxor(_a,_b) ((_a) Xor (_b))
#define bitor(_a,_b) ((_a) Or (_b))
#define bitnot(_a) (Not (_a))
#define sizeof size
#define otherwise others
#define and andif
#define or orif
type
    double = longreal;
    /* These are not part of the MIPS Pascal standard.
        long = integer;
        ushort = 0..65535;
        short = -32768..32767;
    */
#define err ttyoutput
#include "/usr/local/include/pastel/pc-compatibility.h"
#endif
#ifdef _PP
/* Define all these in uppercase as well?? */
/* use "And" instead of "and" to prevent further expansion into "andif". */
#define bitand(_a,_b) ((_a) And (_b))
#define bitxor(_a,_b) ((_a) Xor (_b))
#define bitor(_a,_b) ((_a) Or (_b))
#define bitnot(_a) (Not (_a))
#define otherwise others
#define and andif
#define or orif
#define assert(_b) begin if not (_b) then assertion_error end
#define argv(_i,_s) _s := argv_string(_i)
var
  argc: external cardinal;

function argv_string (
    in i: cardinal
    ): string;
  external;
function clock (): cardinal;
  external;
function sysclock (): cardinal;
  external;
function wallclock (): cardinal;
  external;
procedure remove (
    in filename: string );
  external;
procedure assertion_error;
  external;
procedure halt;
  external;
#endif
