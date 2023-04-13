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
/*  $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/cmplrs/RCS/fioext.h,v 1.9 1996/06/04 21:51:42 calvin Exp $ */

/* Do not include this file in a normal program, it is only intended to 
   be included by fio.h */

#ifndef __IN_FIO_H
#error Do not include this file
#endif

/* external read, write */
typedef struct
{	flag cierr;
	ftnint ciunit;
	flag ciend;
	char *cifmt;
	XINT64 cirec;
	ftnint cimatch;
	ftnint cikeytype;
	Ucikeyval cikeyval;
	ftnint cikeyid;
	char *cinml;
	ftnint cikeyvallen;
#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) /* MIPSpro */
				/* Fortran-90 extension */
	char *ciadvance;	/* ADVANCE=		*/
	ftnint ciadvancelen;
	flag cieor;		/* EOR=			*/
	int *cisize;		/* SIZE=		*/
	int (*civfmt)(void *);
	void *civfmtfp;
#endif /* MIPSpro */
} NAMEcilist;

/* internal read, write */
typedef struct
{
	flag icierr;
	char *iciunit;
	flag iciend;
	char *icifmt;
	XINT icirlen;
	XINT icirnum;
	int (*icivfmt)(void *);
	void *icivfmtfp;
} NAMEicilist;

/* open */
typedef struct
{	flag oerr;
	ftnint ounit;
	char *ofnm;
	ftnlen ofnmlen;
	char *osta;
	char *oacc;
	char *ofm;
	XINT orl;
	char *oblnk;
	char *occ;
	char *oorg;
	flag oshared;
	flag oreadonly;
	ftnint onkeys;
	Keyspec *okeys;
	ftnintu *oassocv;
#ifdef FIELDS_602
	XINT64 omaxrec;
#endif
	char *odfnm;
	ftnlen odfnmlen;
	char *odisp;
#ifndef FIELDS_602
	ftnint omaxrec;
#endif
	char *orectype;
#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) /* MIPSpro */
			/* Extensions in F77 for portability and performance */
	char *oconv;		/* File conversion parameter.  Valid values */
	ftnlen	oconvlen;	/* are: "LITTLE_ENDIAN", "BIG_ENDIAN",
				   "CRAY", "IBM", "VAXD", "VAXD", "NATIVE" */
	ftnint	obuffsize;	/* User-selected buffer size */
	flag	odirect;	/* applying direct I/O to this direct
				   unformatted file
				*/
				/* Fortran-90 extension */
	char *oaction;		/* ACTION=		*/
	ftnlen oactionlen;
	char *odelim;		/* DELIM=		*/
	ftnlen odelimlen;
	char *opad;		/* PAD=			*/
	ftnlen opadlen;
	char *oposition;	/* POSITION=		*/
	ftnlen opositionlen;
#endif /* MIPSpro */
} NAMEolist;

/* find */
typedef struct
{	flag ferr;
	ftnint funit;
	XINT64 frec;
} NAMEflist;

struct NAMEdfnf_struct {
      XINT64          maxrec;
      XINT          recl;
      ftnint          unit;
      ftnintu         *assocv;
   };

/* inquire */
typedef struct
{	flag inerr;
	ftnint inunit;
	char *infile;
	ftnlen infilen;
	ftnintu	*inex;		/* parameters in standard's order */
	ftnintu	*inopen;
	ftnintu	*innum;
	ftnintu	*innamed;
	char	*inname;
	ftnlen	innamlen;
	char	*inacc;
	ftnlen	inacclen;
	char	*inseq;
	ftnlen	inseqlen;
	char 	*indir;
	ftnlen	indirlen;
	char	*infmt;
	ftnlen	infmtlen;
	char	*inform;
	ftnlen	informlen;
	char	*inunf;
	ftnlen	inunflen;
	ftnintu	*inrecl;
	ftnintu	*innrec;
	char	*inblank;
	ftnlen	inblanklen;
	char	*indefaultfile;
	ftnlen	indefaultfilelen;
	char	*incc;
	ftnlen	incclen;
	char	*inkeyed;
	ftnlen	inkeyedlen;
	char	*inorg;
	ftnlen	inorglen;
	char	*inrecordtype;
	ftnlen	inrecordtypelen;

#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) /* MIPSpro */
#ifdef FIELDS_602
	char 	*inconv;		/* new */
	ftnlen	inconvlen;		/* new */
	flex	*inbuffsize;		/* new */
#endif
					/* Fortran-90 extension */
	char	*inaction;		/* ACTION=		*/
	ftnlen	inactionlen;		
	char	*indelim;		/* DELIM=		*/
	ftnlen	indelimlen;
	char	*inpad;			/* PAD=			*/
	ftnlen	inpadlen;
	char	*inposition;		/* POSITION=		*/
	ftnlen	inpositionlen;
	char	*inread;		/* READ=		*/
	ftnlen	inreadlen;
	char	*inreadwrite;		/* READWRITE=		*/
	ftnlen	inreadwritelen;
	char	*inwrite;		/* WRITE=		*/
	ftnlen	inwritelen;
#endif /* MIPSpro */
} NAMEinlist;
