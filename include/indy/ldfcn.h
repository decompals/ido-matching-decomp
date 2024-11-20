/* Copyright (C) 1989 Silicon Graphics, Inc. All rights reserved.  */
#ifndef __LDFCN_H__
#define __LDFCN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Copyright (C) 1987,1989 Silicon Graphics, Inc. All rights reserved.  */
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
/* $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/RCS/ldfcn.h,v 7.14 1995/03/07 23:11:52 davea Exp $ */

/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
 *	The following two declarations appear in the IH versions of
 *	"stdio.h" but do not appear in the normal 1.2 versions.
 */
#ifdef __mips
#ifdef __sgi
/* have to include stdio.h for FILE, ftell() and fgets() declarations. */
#include <stdio.h>
#else 
long ftell();
char *fgets();
#endif 
#endif /* __mips */

struct	ldfile {
	int		_fnum_;	/* so each instance of an LDFILE is unique */
	FILE	*	ioptr;	/* system I/O pointer value */
	long		offset;	/* absolute offset to the start of the file */
	FILHDR		header;	/* the file header of the opened file */
#ifdef __mips
	pCHDRR		pchdr;  /* pointer to the symbol table */
	long		lastindex; /* index of last symbol accessed */
	unsigned short	type;	/* indicator of the type of the file */
	unsigned	fswap : 1;	/* if set, we must swap */
	unsigned	fBigendian : 1;	/* if set, we must swap aux for the
					 * last retrieved symbol
					 */
#else
	unsigned short	type;		/* indicator of the type of the file */
#endif /* __mips */
};


/*
	provide a structure "type" definition, and the associated
	"attributes"
*/

#define	LDFILE		struct ldfile
#define IOPTR(x)	x->ioptr
#define OFFSET(x)	x->offset
#define TYPE(x)		x->type
#define	HEADER(x)	x->header
#define LDFSZ		sizeof(LDFILE)
#ifdef __mips
#define PSYMTAB(x)	x->pchdr
#define SYMTAB(x)	(ldreadst(x, -1), x->pchdr)
#define SYMHEADER(x)	x->pchdr->hdr
#define PFD(x)		x->pchdr->pfd
#define LDSWAP(x)	x->fswap
#define LDAUXSWAP(x,ifd) (PFD(x)[ifd].fBigendian != x->fBigendian)
#define LDERROR(x,y,z)  fprintf(stderr,"libmld: x:"); fprintf (stderr, y, z);
#endif /* __mips */

/*
	define various values of TYPE(ldptr)
*/

#define ARTYPE 	0177545
#define ISARCHIVE(x) ((x) == ARTYPE)

/*
	define symbolic positioning information for FSEEK (and fseek)
*/

#define BEGINNING	0
#define CURRENT		1
#define END		2

/*
	define a structure "type" for an archive header
*/

typedef struct
{
	char ar_name[16];
	long ar_date;
	int ar_uid;
	int ar_gid;
	long ar_mode;
	long ar_size;
} archdr;

#define	ARCHDR	archdr
#define ARCHSZ	sizeof(ARCHDR)


/*
	define some useful symbolic constants
*/

#define SYMTBL	0	/* section nnumber and/or section name of the Symbol Table */

#define	SUCCESS	 1
#define	CLOSED	 1
#define	FAILURE	 0
#define	NOCLOSE	 0
#define	BADINDEX	-1L

#define	OKFSEEK	0

/*
	define macros to permit the direct use of LDFILE pointers with the
	standard I/O library procedures
*/

#include "obj.h"

#ifdef  _LIBMLD_PRIVATE
#ifndef __elf32_LDFILE
#define __elf32_LDFILE
typedef struct {
  LDFILE ldfile;
  pOBJ obj;
  int arfd;
  off_t aroffset;               /* offset to next archive header */
  ARCHDR archdr;
} elf32_LDFILE;
#endif
#else /* public interface */
#define elf32_LDFILE  LDFILE
#endif

/*
  The libmld support has been rewritten. Basic things work the same,
  though some little-used things are now absent or have slightly
  different semantics in obscure undocumented corners.
*/
#if 0 /* Used in IRIX 4.0.1. No longer supported */
#define GETC(ldptr)	getc(IOPTR(ldptr))
#define GETW(ldptr)	getw(IOPTR(ldptr))
#define FEOF(ldptr)	feof(IOPTR(ldptr))
#define FERROR(ldptr)	ferror(IOPTR(ldptr))
#define FGETC(ldptr)	fgetc(IOPTR(ldptr))
#define FGETS(s,n,ldptr)	fgets(s,n,IOPTR(ldptr))
#define FILENO(ldptr)	fileno(IOPTR(ldptr))
#endif
/* the following two continue to be supported */
#define FREAD(p,s,n,ldptr)  ldfread(p,s,n,ldptr)
#define FSEEK(ldptr,o,p)    ldfseek(ldptr,o,p)
#ifdef __sgi
/* support for FTELL has been added for COFF files by sgi */
#define FTELL(ldptr)		__sgi_ldftell(ldptr)
#endif
#if 0 /* were in IRIX4.0.1. No longer supported */
#define FTELL(ldptr)		(ftell(IOPTR(ldptr)) - OFFSET(ldptr))
#define FWRITE(p,s,n,ldptr)       fwrite(p,s,n,IOPTR(ldptr))
#define REWIND(ldptr)	rewind(IOPTR(ldptr))
#define SETBUF(ldptr,b)	setbuf(IOPTR(ldptr),b)
#define UNGETC(c,ldptr)		ungetc(c,IOPTR(ldptr))
#endif
#ifndef __mips
#define STROFFSET(ldptr)	(HEADER(ldptr).f_symptr + HEADER(ldptr).f_nsyms * 18) /* 18 == SYMESZ */
#else /* __mips */
#define STROFFSET(ldptr)	(SYMHEADER(ldptr).cbSsOffset)
#endif /* __mips */

#ifdef __sgi
extern int ldfseek(elf32_LDFILE *,int /*offset*/,int/*whence*/);
extern int ldfread(char */*buffer*/,int /*size*/,int/*count*/,elf32_LDFILE *);
extern char *	ldgetname (LDFILE *, SYMR *);	/* should be elf32_LDFILE */
extern long     ldgetpd( LDFILE * , int /*ipd*/, PDR * /*ppd*/);
extern int      ldreadst(elf32_LDFILE * /*ldptr*/, int /*flags*/);
AUXU *          ldgetaux(LDFILE * /*ldptr*/, int    /*iaux*/);
extern long 	__sgi_ldftell(elf32_LDFILE *);
extern elf32_LDFILE *	ldopen (const char *, elf32_LDFILE *);
extern elf32_LDFILE *	ldaopen (const char *, elf32_LDFILE *);
extern int	ldclose (elf32_LDFILE *) ;
extern int	ldaclose (elf32_LDFILE *);
extern int	ldahread (elf32_LDFILE *, ARCHDR *);
extern int	ldfhread (elf32_LDFILE *, FILHDR *) ;
#ifdef SCNHDR
extern int	ldshread (elf32_LDFILE *, int, SCNHDR *);
extern int	ldnshread (elf32_LDFILE *, const char *, SCNHDR *);
#endif
extern int	ldtbread (LDFILE *, long, SYMR *);
extern int	ldohseek (elf32_LDFILE *);
extern int	ldsseek (elf32_LDFILE *, unsigned short);
extern int	ldnsseek (elf32_LDFILE *, const char *);
extern int	ldrseek (elf32_LDFILE *, unsigned short);
extern int	ldnrseek (elf32_LDFILE *, const char *);
extern int	ldlseek (elf32_LDFILE *, unsigned short);
extern int	ldnlseek (elf32_LDFILE *, const char *);
extern int	ldtbseek (elf32_LDFILE *);
extern long	ldtbindex (LDFILE *);
extern int	ldlread (LDFILE *, long, unsigned short, LINER *) ;
extern int	ldlinit (LDFILE *, long) ;
extern int	ldlitem (LDFILE *, unsigned short, LINER *) ;
extern void	sputl (long, char *);
extern long	sgetl (char *);
/*extern LDFILE *ldinitheaders(LDFILE *);   NOT AVAILABLE */
#endif /* __sgi */

#ifdef __cplusplus
}
#endif

#endif /* __LDFCN_H__ */
