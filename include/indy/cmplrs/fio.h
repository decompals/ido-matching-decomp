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
/*  $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/cmplrs/RCS/fio.h,v 7.26 1996/05/08 21:09:29 rshapiro Exp $ */

#ifndef FIO_INCLUDED
#define FIO_INCLUDED
#include <stdio.h>
#include <sys/stat.h>
#include <sgidefs.h>

/*  #include <sys/types.h>   */
typedef int ftnint;
typedef int ftnlen;
typedef long ftnlong;		/* values with pointer size */

#ifdef _LONGLONG
typedef long long ftnll;
typedef unsigned long long ftnull;
#else
typedef long ftnll;
typedef unsigned long ftnull;
#endif
typedef ftnint flag;

typedef union {
	char byte;
	short word;
	ftnint longword;
	ftnll longlongword;
} ftnintu;

typedef struct  {
	short e1;
	short e2;
	short dt;
} Keyspec;


#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) /* MIPSpro */
typedef union
{       signed char flbyte;
        short   flshort;
        ftnint  flint;
#ifdef _LONGLONG
        long long flll;
#else
        long flll;
#endif
        float   flreal;
        double  fldouble;
	long double flquad;
} flex;

typedef struct
{
        ftnint cimatch;
        ftnint cikeytype;
        union {
           ftnint ciintval;
           char *cicharval;
        } cikeyval;
        ftnint cikeyid;
        char *cinml;
        ftnint cikeyvallen;
} idxlist;
#endif /* MIPSpro */

typedef union {
	ftnint ciintval;
	char *cicharval;
	} Ucikeyval;

#define __IN_FIO_H

#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) /* MIPSpro */
#if (_MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32 || _MIPS_SIM == _MIPS_SIM_ABI32)

/* we define a new set of structures with the following features
	-r32/-n32:	64 bit filelength and record count fields
	-64:		above + 64 bit record length fields

   However we maintain compatible stubs for fcom (-r32) and the
   6.0/6.01 64 bit programs
*/

/* XINT is the external integer interface with the frontend I/O 
calls.  XINT64 is the external integer interface for
the filelength fields */

#define XINT		ftnlong		/* 32 in -r32/-n32, 64 in -64 */
#define XINT64		ftnll		/* -64 always */

#define NAMEcilist	cilist64
#define NAMEinlist	inlist64
#define NAMEicilist	icilist64
#define NAMEolist	olist64
#define NAMEflist	flist64
#define NAMEdfnf_struct	dfnf_struct64
#define FIELDS_602

#include <cmplrs/fioext.h>

#undef XINT
#undef XINT64
#undef NAMEcilist
#undef NAMEinlist
#undef NAMEicilist
#undef NAMEolist
#undef NAMEflist
#undef NAMEdfnf_struct
#undef FIELDS_602

/* now we define the compatibility set */
#define XINT		ftnint	/* in compatibility mode, everything is 32 */
#define XINT64	ftnint  /* in compatibility mode, everything is 32 */

#define NAMEcilist	cilist
#define NAMEinlist	inlist
#define NAMEicilist	icilist
#define NAMEolist	olist
#define NAMEflist	flist
#define NAMEdfnf_struct	dfnf_struct

#include <cmplrs/fioext.h>

#undef XINT
#undef XINT64
#undef NAMEcilist
#undef NAMEinlist
#undef NAMEicilist
#undef NAMEolist
#undef NAMEflist
#undef NAMEdfnf_struct

#define XINT		ftnlong	/* for the rest of this include file */
#define XINT64	ftnll		/* -64 always */

#else

/* not -64, -n32, -r32 ?!?!?! */
#error "UNKNOWN COMPILATION MODE"

#endif

#else	/* ucode */

/* now we define the original 32bit set */
#define XINT		ftnint	/* in compatibility mode, everything is 32 */
#define XINT64	ftnint  /* in compatibility mode, everything is 32 */

#define NAMEcilist	cilist
#define NAMEinlist	inlist
#define NAMEicilist	icilist
#define NAMEolist	olist
#define NAMEflist	flist
#define NAMEdfnf_struct	dfnf_struct

#include <cmplrs/fioext.h>

#undef NAMEcilist
#undef NAMEinlist
#undef NAMEicilist
#undef NAMEolist
#undef NAMEflist
#undef NAMEdfnf_struct


#endif /* defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) */

#undef __IN_FIO_H

/* close */
typedef struct
{	flag cerr;
	ftnint cunit;
	char *csta;
} cllist;

/* rewind, backspace, endfile, delete, unlock */
typedef struct
{	flag aerr;
	ftnint aunit;
} alist;


#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) /* MIPSpro */
struct f77syl
{       int op;
        long p1;
        long p2;
        int p3;
};

#endif /* MIPSpro */

#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) /* MIPSpro */
typedef struct
{       
	char *iciunit;		/* not NULL if it is an internal I/O  */
	int *cisize;		/* SIZE=		*/
	/* flag f77external; */
	flag cierr;
        flag ciend;
        flag cieor;		/* F90 EOR */
        XINT icirlen;
        XINT64 icirnum;
} errlist;
#endif /* MIPSpro */

/* units */
typedef struct UNIT
{
	FILE *ufd;
	int isfd;	/* C-ISAM file descriptor (for KEYED) */
	flag uconn;	/* 0=unconnected */
	char *ufnm;
	ftnint luno;	/* fortran logical unit number */
	ino_t uinode;
	XINT url;	/* 0=sequential */
	flag useek;	/* true=can backspace, use dir, ... */
	flag ufmt;
	flag uprnt;
	flag ublnk;
	flag uend;
	flag uwrt;	/* last io was write */
	flag uscrtch;
	flag uerror;    /* last I/O op. has error */
	flag uistty;	/* the file is a terminal device */
	char ucchar;    /* carriage control character */
	char ucc;	/* carriage control code */
	int uacc;	/* SEQUENTIAL, DIRECT, KEYED, or APPEND */
	ftnint ukeyid;  /* current key of reference */
	ftnint unkeys;  /* # of keys */
	Keyspec *ukeys; /* pointer to table of key definitions */
	flag ushared;   /* for keyed files: 0=exclusive, 1=shared */
	ftnintu *uassocv; /* associate variable */
	ftnint udisp;	/* disposition flag: 0=keep, 1=delete, 2=print,
				3=print/delete,4=submit, 5=submit/delete */
	XINT64 umaxrec; /* maximum direct access records */
	flag ureadonly; /* readonly permission */
	struct UNIT *ualias;   /* alias pointer for carriage control */
	ftnint umask;	/* type mask for return values */
	XINT64 uirec;	/* current direct access record */
	XINT64 flen;	/* length of the file before BACKSPACE/REWIND */
#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) /* MIPSpro */
			/* Fortran-90 extension */

	ftnint uaction; /* action flag: 0=readwrite, 1=readonly, 2=writeonly */
	ftnint udelim;  /* delimit flag: 0=none, 1=quote, 2=apostrophe
                           delimits constants written with list_direct or namelist */
	flag unpad;      /* pad flag: 0=yes, 1=no
	                   determines whether to pad formattted input with blanks */
	XINT urecend;	/* record end in the IO buffer */ /* NOT USED ? */

	/* structures */
	errlist f77errlist;	/* for error recovery */
        idxlist f77idxlist;

	/* 128-bit values */
	flex	lqx;	/* saved value of list-directed read */
	flex	lqy;	/* saved value of list-directed read */

	/* pointers */
	ftnint (*f77getn)(struct UNIT *);
	ftnint (*f77ungetn)(struct UNIT *, int);
	ftnint (*f77gets)(struct UNIT *, char *, int, char);
	ftnint (*f77putn)(struct UNIT *,XINT, char, char *); /* formatted io */
	ftnint (*f77do_unf)(struct UNIT *, XINT *, char *, ftnlen); /* unformatted I/O */
	ftnint (*f77doed)(struct UNIT *, struct f77syl *, char *, ftnlen, ftnint);
	ftnint (*f77doned)(struct UNIT *, struct f77syl *);
	ftnint (*dowrite)(struct UNIT *);
	ftnint (*f77doend)(struct UNIT *);
	ftnint (*f77donewrec)(struct UNIT *);
	ftnint (*f77dorevert)(struct UNIT *);
	ftnint (*f77lioproc)(struct UNIT *, XINT *, flex *, ftnlen, ftnint);
	char   *f77fio_buf;	/* I/O buffer */
	char   *f77fmtbuf;	/* Contents of the FORMAT specification */
	struct f77syl *f77syl;
	char   *startaddr;	/* For F90 namelist */
	unsigned long	lock_unit;

	/* 64/32-bit int */
	XINT f77reclen;
	XINT f77recpos;
	XINT f77cursor;
	XINT f77recend;

	ftnint f77fio_size;	/* size of the buffer f77fio_buf */
	XINT lcount;		/* count for N*data list-directed input
				   also used to save the number of items
				   of an array read/written before an I/O 
				   error */
	ftnint ltype;
	ftnint f77syl_size;
	ftnint nextch;
	XINT suboffset;	/* for namelist I/O */
	XINT substr_lb;	/* for namelist I/O */
	XINT substr_ub;	/* for namelist I/O */


	/* 16-bit integers */
	short int    f77scale;
	short int    parenlvl;
	int    pc;
	int    revloc;
	int	cnt[10];
	int	ret[10];
	int	cp;
	int	rp;

	/* Assorted flags */
	unsigned char f77cplus;
	unsigned char f77cblank;
	unsigned char f77workdone;
	unsigned char f77nonl;
	unsigned char lquit;
	unsigned char overflowed;
	unsigned char l_first;
	unsigned char f90eor;
	unsigned char f90nadv;
	unsigned char f90sw;
	unsigned char subscript;
	unsigned char array_section;


	int (*vfmt)(void *);
	void *vfmtfp;
#endif /* MIPSpro */
} unit;



#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) /* MIPSpro */
extern unit *f77curunit;	/* for backward compatibility */
#endif /* MIPSpro */
extern int errno;
extern ftnint errluno;
extern flag f77init;
#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) /* MIPSpro */
extern cilist64 *f77elist;	/* active external io list */
extern icilist64 *f77svic;
#else
extern cilist *f77elist;	/* active external io list */
extern icilist *f77svic;
#endif

#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) /* MIPSpro */
extern unit *f77units;          /* logical unit map table */
extern unit * Internal_File;
#else
extern flag f77reading,f77external,f77sequential,f77formatted;
extern int (*f77getn)(),(*f77gets)(),(*f77putn)();	/* for formatted io */
extern int (*f77do_unf)();		/* unformatted I/O */
extern int (*_libisam_iscleanup)();
extern int (*_libisam_idxrd)();
extern int (*_libisam_idxwrt)();
extern int (*_libisam_idxcls)();
extern FILE *f77cf;		/* current fil e*/
extern unit *f77curunit;	/* current unit */
extern unit *f77units;		/* logical unit map table */
extern int f77reclen;
extern int f77recpos;	/* position in current record */
#endif /* MIPSpro */

#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) /* MIPSpro */

unit *map_luno(ftnint);
#define err(f,n,s) {if(f){errno=n; if (ftnunit && !ftnunit->f77errlist.iciunit) {errluno=ftnunit->luno; ftnunit->uerror = n;}} else f77fatal(ftnunit,n,s); return(n);}
#define errret(f,n,s) {if(f){errno=n;if(ftnunit) {errluno=ftnunit->luno; ftnunit->uerror = n; ftnunit->lock_unit = 0;}} else f77fatal(ftnunit,n,s); return(n);}
#define ierrret(f,n,s) {if(f){errno=n;if(ftnunit)errluno=ftnunit->luno;ftnunit->uerror = n; ftnunit->lock_unit = 0;} else f77fatal(ftnunit,n,s); return(n);}
#define ierr(f,n,s) {if(f){errno=n;if(ftnunit)errluno=ftnunit->luno;ftnunit->uerror = n;} else f77fatal(ftnunit,n,s); return(n);}

#else /* MIPSpro */

unit *map_luno();
#define err(f,n,s) {if(f){errno=n; if (f77external && f77curunit) {errluno=f77curunit->luno; f77curunit->uerror = errno;}} else f77fatal(n,s); return(n);}
#define ierr(f,n,s) {if(f){errno=n;if(f77curunit)errluno=f77curunit->luno;} else f77fatal(n,s); return(n);}

#endif /* MIPSpro */

#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) /* MIPSpro */
#define	CILISTERR	(ftnunit->f77errlist.cierr)
#else /* MIPSpro */
#define	CILISTERR	(f77external ? f77elist->cierr : f77svic->icierr)
#endif /* MIPSpro */

/* Initial size of f77 unit table */
#define INIT_MXUNIT 100
extern int mxunit;

extern unsigned long	io_lock;  /* exclusive lock for special I/O
				     operations such as open, close,
				     which modifies the static table
				     in libc
				  */

#define EOR     -2

#define WRITE	1
#define READ	2
#define SEQ	3
#define DIR	4
#define FMT	5
#define UNF	6
#define EXT	7
#define INT	8


#define CC_LIST     	  ((char) 0)
#define CC_NONE     	  ((char) 1)
#define CC_FORTRAN  	  ((char) 2)

/*  File access types  */

#define SEQUENTIAL 1
#define DIRECT     2
#define KEYED      3
#define APPEND     4

/* File disposition codes */

#define KEEP	  0
#define DELETE    1
#define PRINT     2
#define SUBMIT    4

#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) /* MIPSpro */
/* File action types  */

#define READWRITE 0
#define READONLY  1
#define WRITEONLY 2

/* File delimeter types  */

#define DELIM_NONE 0
#define QUOTE      1
#define APOSTROPHE 2
#endif /* MIPSpro */

typedef struct {
#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) /* MIPSpro */
   int (*PFI)(void *);
#else /* MIPSpro */
   int (*PFI)();
#endif /* MIPSpro */
   char * static_link;
} vfmt_struct;

#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=400) /* MIPSpro */
/* in redwood, we dont have the xxx64 calls - they are normally 64 anyways */
#if (_MIPS_SIM == _MIPS_SIM_ABI64)
#define LSEEK lseek
#define FSEEK fseek
#define FTELL ftell
#define FTRUNCATE ftruncate
#define TRUNCATE truncate
#define FSTAT fstat
#define STAT_TAG stat
#else
#define LSEEK lseek64
#define FSEEK fseek64
#define FTELL ftell64
#define FTRUNCATE ftruncate64
#define TRUNCATE truncate64
#define FSTAT fstat64
#define STAT_TAG stat64

#endif

#endif /* MIPSPRO */

#endif
