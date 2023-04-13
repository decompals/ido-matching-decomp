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
/* $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/cmplrs/RCS/u_outformat.h,v 7.3 1992/01/20 13:00:32 daveb Exp $ */
/* ref.		date		reference				*/
/* !01		07oct85		buffering output			*/
#include	<stdio.h>
#define MIN(a,b) ( ((a) > (b))  ? (b) : (a) )
#define		BUFFLEN 100		/* maximum length of format 	*/
					/*	before expansion	*/
					/*				*/
					/* U-code output formats	*/
#define	UCW_ASCII	1		/* ascii output?		*/
#define	UCW_BIN		2		/* binary output		*/
#define	UCW_OCTAL	4		/* octal output?		*/
#define	UCW_ECHO_OCTAL	8		/* octal output from btou?	*/
int	Ucw_out_type;			/* type of output requested	*/
					/*				*/
int	Ucw_verbose;			/* verbose output?		*/
FILE	*Ucw_binout;			/* binary output file (open)!01	*/
FILE	*Ucw_ascout;			/* ascii output file (fopen)	*/
					/*				*/
struct Uw_if {				/* output format for each type	*/
	int	If_nbytes;		/*  # of bytes to read (doesn't	*/
					/*	include opcode or val)	*/
	int	If_hasval;		/*  if it has a value		*/
	} ;				/*				*/
					/*				*/
					/* U-code output formats	*/
enum					/*				*/
  Uw_otype { Uwof_init,			/* the init statement		*/
	     Uwof_comm,			/* the comment statement	*/
	     Uwof_lca,			/* the lca statement		*/
	     Uwof_ldc,			/* the ldc statement		*/
	     Uwof_normal, 		/* normal format of printf 	*/
					/*	format and pointers	*/
	     Uwof_undef 		/* still working ones of this 	*/
					/*	type			*/
	     } ;			/*				*/
					/*				*/
struct Uw_of {				/* output format for each type	*/
	enum Uw_otype 	Of_type;	/*    the output format type to	*/
					/*		choose		*/
	int		Of_nbytes;	/* number of bytes		*/
	int		Of_hasval;	/* set if it has a constant	*/
	char		*Of_format;	/*    a "printf" style output	*/
					/*		format string	*/
	} ;				/*				*/
					/*				*/
					/*				*/
extern struct Uw_of Uw_of[];		/* the output format data	*/
					/*				*/
