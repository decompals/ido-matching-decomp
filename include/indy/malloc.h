/**************************************************************************
 *									  *
 * 		 Copyright (C) 1989-1994 Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/
/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/
#ifndef __MALLOC_H__
#define __MALLOC_H__

#ifdef __cplusplus
extern "C" {
#endif

#ident "$Revision: 1.35 $"

/* Definitions for malloc(3X) and amalloc(3P) routines */

/* Commands for mallopt(), amallopt() */
#define M_MXFAST	1	/* set size of blocks to be fast */
#define M_NLBLKS	2	/* set number of block in a holding block */
#define M_GRAIN		3	/* set number of sizes mapped to one, for
				 * small blocks */
#define M_KEEP		4	/* retain contents of block after a free until
				 * another allocation */

#if defined (_SGI_SOURCE)
#define M_BLKSZ		5	/* minimum amount of memory by which to
				 * grow when sbrk'ing more memory */
#define M_MXCHK		6	/* maximum number of blocks to check before
				 * giving up and calling sbrk() */
#define M_FREEHD	7	/* Free blocks go to head (tail) of free list */
#define M_CRLOCK	8	/* make the arena MP safe - allocating
				 * a lock, etc. (amallopt only)
				 */
#define M_DEBUG		100	/* turn on arena checking */

/* NOTE: the following options only work with special versions of malloc */
#define	M_LOG		101	/* turn on/off malloc/realloc/free logging */
#define	M_LOGFILE	102	/* set the file to use for logging */
#define	M_LOGDEPTH	103	/* set the maximum stack depth */
#define M_CLRONFREE	104	/* clear block on free */

/* Flags for acreate(3P) */
#define MEM_SHARED	0x0001	/* region is shared and should be
				 * protected with locks */
#define MEM_NOAUTOGROW	0x0004	/* arena is not an autogrow area */
#endif /* SGI_SOURCE */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
#include <sgidefs.h>
#include <stddef.h>

/* Structure filled by mallinfo(), amallinfo() */
struct mallinfo  {
	__scint_t arena;	/* total space in arena */
	__scint_t ordblks;	/* number of ordinary blocks */
	__scint_t smblks;	/* number of small blocks */
	__scint_t hblks;	/* number of holding blocks */
	__scint_t hblkhd;	/* space in holding block headers */
	__scint_t usmblks;	/* space in small blocks in use */
	__scint_t fsmblks;	/* space in free small blocks */
	__scint_t uordblks;	/* space in ordinary blocks in use */
	__scint_t fordblks;	/* space in free ordinary blocks */
	__scint_t keepcost;	/* cost of enabling keep option */
};

#if defined (_SGI_SOURCE)
#include <ulocks.h>

/* Logging data structures */

/* logging entry types */
enum malloc_log_type {
	malloc_log_malloc,
	malloc_log_realloc,
	malloc_log_free
};

/* log file entry.  One entry per operation that was logged. */
struct malloc_log_entry  {
	enum malloc_log_type type;
	void* address;			/* address */
	size_t size;			/* size of malloc/realloc */
	void* oldaddress;		/* for realloc only */
	unsigned int numpcs;		/* number of pcs that follow */
	char* pcs[1];			/* 0 or more pcs */
};

/*
 * Locking macro for mallocs
 * ALL malloc replacements must provide for single threading
 * The __mmalloclock is automatically initialized whenever a process
 * does an sproc(2)
 * Note that us* are macros so they don't name-space pollute
 */
extern int __us_rsthread_malloc;
extern ulock_t __mmalloclock;
#ifdef _ABI_SOURCE
#define __LOCK_MALLOC()		1
#define __UNLOCK_MALLOC()	0
#else
#define __LOCK_MALLOC()	__us_rsthread_malloc ?  ussetlock(__mmalloclock) : 1
#define __UNLOCK_MALLOC() __us_rsthread_malloc ?  usunsetlock(__mmalloclock) : 0
#endif

#endif /* SGI_SOURCE */

extern void *		calloc(size_t, size_t);
extern void *		malloc(size_t);
extern void		free(void *);
extern void *		realloc(void *, size_t);
extern int		mallopt(int, int);
extern struct mallinfo	mallinfo(void);

#if defined (_SGI_SOURCE)
/* additional libmalloc entry points */
extern void		*recalloc(void *, size_t, size_t);
extern size_t		mallocblksize(void *);
extern void		*memalign(size_t, size_t);

/* AMALLOC(3P) */
extern void *		acreate(void *, size_t, int, void *,
					void * (*)(size_t, void *));
extern void		afree(void *, void *);
extern void		*arealloc(void *, size_t, void *);
extern void		*arecalloc(void *, size_t, size_t, void *);
extern void		*amalloc(size_t, void *);
extern void		*acalloc(size_t, size_t, void *);
extern struct mallinfo	amallinfo(void *);
extern int		amallopt(int, int, void *);
extern void		adelete(void *);
extern size_t		amallocblksize(void *, void *);
extern void		*amemalign(size_t, size_t, void *);
#endif /* SGI_SOURCE */

#endif /* (_LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS) */
#ifdef __cplusplus
}
#endif
#endif /* !__MALLOC_H__ */
