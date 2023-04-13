/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1984, 1986, 1987, 1988, 1989, 1990 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef __PROC_AUXV_H__	/* wrapper symbol for kernel use */
#define __PROC_AUXV_H__	/* subject to change without notice */
#ident	"@(#)uts-3b2:proc/auxv.h	1.2"

#ifdef __cplusplus
}
#endif


typedef struct
{
       int     a_type;
       union {
               long    a_val;
#ifdef __STDC__
               void    *a_ptr;
#else
               char    *a_ptr;
#endif
               void    (*a_fcn)();
       } a_un;
} auxv_t;

#define AT_NULL		0
#define AT_IGNORE	1
#define AT_EXECFD	2
#define AT_PHDR		3	/* &phdr[0] */
#define AT_PHENT	4	/* sizeof(phdr[0]) */
#define AT_PHNUM	5	/* # phdr entries */
#define AT_PAGESZ	6	/* getpagesize(2) */
#define AT_BASE		7	/* ld.so base addr */
#define AT_FLAGS	8	/* processor flags */
#define AT_ENTRY	9	/* a.out entry point */
#define AT_PFETCHFD     100     /* executable's fd for prefetch fix-up */

#ifdef __cplusplus
}
#endif

#endif
