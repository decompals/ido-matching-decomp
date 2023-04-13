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
/* $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/cmplrs/RCS/as1atof.h,v 7.3 1992/01/20 12:59:42 daveb Exp $ */
const
  maxfpstring = 32;

type
  strng = packed array [0..maxfpstring] of char; (* Standard string type.  *)

{ Must call this first to initialize the Hough/Rowen package }
procedure initializefp; external;

{ Hough/Rowen decimal ascii-to-binary conversions: strng is null-terminated,
  function returns mask of exceptions, where all except "inexact" are
  interesting:

  most     least
      ----x		inexact
      ---x-		underflow
      --x--		overflow
      -x---		divide by zero
      x----		invalid operation
}
function atofloat(var { for economy } cstring: strng; var r: integer): integer;
  external;

function atodouble(var { for economy } cstring: strng;
  var rmore, rless: integer): integer;
  external;

function atoextended(var { for economy } cstring: strng;
  var rmost, rmore, rless, rleast:
  integer): integer; external;

