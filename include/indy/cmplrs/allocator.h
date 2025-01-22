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
/* $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/cmplrs/RCS/allocator.h,v 7.3 1992/01/20 12:59:40 daveb Exp $ */

function alloc_mark (
       var fheap : pointer)
   : integer;
  external;

procedure alloc_release (
	var fheap : pointer;
	    fmark : integer);
  external;

function alloc_new (
	   fsize : integer;
       var fheap : pointer)
   : pointer;
  external;

procedure alloc_dispose (
	    fptr : pointer;
	var fheap : pointer);
  external;

function alloc_resize (
	    fptr : pointer;
	    fsize : cardinal;
	var fheap : pointer)
   : pointer;
  external;

function malloc (
	   fsize : integer)
   : pointer;
  external;

procedure free (
	    fptr : pointer);
  external;

function realloc (
           fptr : pointer;
	   fsize : integer)
   : pointer;
  external;

