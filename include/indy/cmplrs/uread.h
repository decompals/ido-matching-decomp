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
/* $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/cmplrs/RCS/uread.h,v 7.3 1992/01/20 13:00:40 daveb Exp $ */

procedure resetur;
  external;

PROCEDURE readuinstr (VAR U: Bcrec; strptr: stringtextptr);
  external;

procedure initur(
	var Uname    : Filename);
  external;

procedure ugetinit(
	var ObjectName : Filename);
  external;

procedure ugetclose;
  external;

function ugetint: integer;
  external;

function ugeteof: integer;
  external;

PROCEDURE Ubytetobit (VAR U: Bcrec);
  external;
