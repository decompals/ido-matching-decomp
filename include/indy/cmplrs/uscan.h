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
/* $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/cmplrs/RCS/uscan.h,v 7.3 1992/01/20 13:00:42 daveb Exp $ */

procedure Abort;
  external;

procedure openstdout(
	var F	     : text);
  external;

procedure opnstdin(
	var F	     : text);
  external;

procedure openinput(
	var F	     : text;
	    Fname    : Filename);
  external;

procedure openoutput(
	var F	     : text;
	    Fname    : Filename);
  external;

function getclock
   : integer;
  external;

function eopage(
	var Fil	    : text)
   : boolean;
  external;

procedure readpage(
	var Fil	     : text);
  external;

procedure printdate(
	var Fil	     : text);
  external;

procedure printtime(
	var Fil	     : text);
  external;

#if 0
function max(
	   I, 
	   J	    : integer)
   : integer;
  external;

function min(
	   I, 
	   J	    : integer)
   : integer;
  external;
#endif
