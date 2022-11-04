/**************************************************************************
 *									  *
 * 		 Copyright (C) 1986-1993, Silicon Graphics, Inc.	  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

/*
 * prctl.h - struct for private process data area and prctl and sproc
 */
#ifndef __PRCTL_H__
#define __PRCTL_H__

#ifdef __cplusplus
extern "C" {
#endif

#ident "$Revision: 3.33 $"

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
/*
 * PRDA area - mapped privately into each process/thread
 */
/* address of the process data area */
#define PRDA		((struct prda *)0x00200000)

/* the system portion of the prda */
struct prda_sys {
	uint_t	t_pid;		/* pid */
	uint_t	t_hint;		/* Share group scheduling hint */
	uint_t	t_dlactseq;	/* Deadline scheduler activation seqence # */
	uint_t	t_unus2;	/* */
	uint_t	t_unus3;	/* */
	uint_t	t_unus4;	/* */
	uint_t	t_scassrch;	/* start of cas search area */
	uint_t	t_ecassrch;	/* end of cas search area */
	uint_t	t_slckcas1;	/* start lock cas1 area */
	uint_t	t_elckcas1;	/* end lock cas1 area */
	uint_t	t_slckcas2;	/* start lock cas2 area */
	uint_t	t_elckcas2;	/* end lock cas2 area */
	uint_t	t_sunlckcas1;	/* start unlock cas1 area */
	uint_t	t_eunlckcas1;	/* end unlock cas1 area */
	uint_t	t_sunlckcas2;	/* start unlock cas2 area */
	uint_t	t_eunlckcas2;	/* end unlock cas2 area */
	uint_t	t_scas;		/* start SP cas area */
	uint_t	t_ecas;		/* end SP cas area */
	uint_t	t_casfail;	/* SP failure address */
	uint_t	t_sclckcas1;	/* start conditional lock cas1 area */
	uint_t	t_eclckcas1;	/* end conditional lock cas1 area */
	uint_t	t_hscas;	/* start MP cas area */
	uint_t	t_hecas;	/* end MP cas area */
	uint_t	t_hcasfail;	/* MP cas failure address */
	uint_t	t_hcasmayhave;	/* MP cas address */
	uint_t	t_hcashavelock;	/* MP cas address */
};

struct prda {
	char unused[2048];
	union {
		char fill[512];
	} sys2_prda;
	union {
		char fill[512];
	} lib2_prda;
	union {
		char fill[512];
	} usr2_prda;

	union {
		char fill[128];
		struct prda_sys prda_sys;
	} sys_prda;
	union {
		char fill[256];
	} lib_prda;
	union {
		char fill[128];
	} usr_prda;
};
#define t_sys		sys_prda.prda_sys

#ifndef _KERNEL

/* prototypes for process control functions */
#include "stddef.h"
#include "sys/types.h"
int blockproc(pid_t);
int unblockproc(pid_t);
int setblockproccnt(pid_t, int);
int blockprocall(pid_t);
int unblockprocall(pid_t);
int setblockproccntall(pid_t, int);
ptrdiff_t prctl(unsigned, ...);
int sproc(void (*)(void *), unsigned, ...);
int sprocsp(void (*)(void *, size_t), unsigned, void *, caddr_t, size_t);

#endif /* !_KERNEL */
#endif /* (_LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS) */

#if defined(_LANGUAGE_ASSEMBLY)
#define PRDA		0x00200000
#define T_PID		0xe00
#define T_HINT		0xe04
#endif

/* values for prctl */
#define PR_MAXPROCS	1	/* maximum # procs per user */
#define PR_ISBLOCKED	2	/* return if pid is blocked */
#define PR_SETSTACKSIZE 3	/* set max stack size */
#define PR_GETSTACKSIZE 4	/* get max stack size */
#define PR_MAXPPROCS	5	/* max parallel processes */
#define PR_UNBLKONEXEC	6	/* unblock pid on exec/exit */
#define PR_ATOMICSIM	7	/* enable atomic operator simulation */
#define PR_SETEXITSIG	8	/* set signal for on exit */
#define PR_RESIDENT	9	/* set process immune to swapout */
#define PR_ATTACHADDR	10	/* re-attach a region */
#define PR_DETACHADDR	11	/* detach a region */
#define PR_TERMCHILD	12	/* terminate child proc when parent exits */
#define PR_GETSHMASK	13	/* retrieve share mask */
#define PR_GETNSHARE	14	/* return # of members of share group */

/*
 * sproc (2) sharing options
 */
#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) || defined(_LANGUAGE_ASSEMBLY)
#define PR_SPROC	0x00001	/* doing an sproc(2) call */
#define PR_SFDS		0x00002	/* share file descriptors */
#define PR_SDIR		0x00004	/* share current/root directory */
#define PR_SUMASK	0x00008	/* share umask value */
#define PR_SULIMIT	0x00010	/* share ulimit value */
#define PR_SID		0x00020	/* share uid/gid values */
#define PR_SADDR	0x00040	/* share virtual address space */
#define PR_SALL		0x00ffffff	/* share it all */

/* sproc(2) flags */
#define PR_FLAGMASK	0xff000000
#define PR_BLOCK	0x01000000	/* caller blocks on sproc */
#define PR_NOLIBC	0x02000000	/* do not start libc arena */
#endif

#if defined(_LANGUAGE_FORTRAN)
#define PR_SPROC	'00001'x	/* doing an sproc(2) call */
#define PR_SFDS		'00002'x	/* share file descriptors */
#define PR_SDIR		'00004'x	/* share current/root directory */
#define PR_SUMASK	'00008'x	/* share umask value */
#define PR_SULIMIT	'00010'x	/* share ulimit value */
#define PR_SID		'00020'x	/* share uid/gid values */
#define PR_SADDR	'00040'x	/* share virtual address space */
#define PR_SALL		'00ffffff'x	/* share it all */

/* sproc(2) flags */
#define PR_FLAGMASK	'ff000000'x
#define PR_BLOCK	'01000000'x	/* caller blocks on sproc */
#define PR_NOLIBC	'02000000'x	/* do not start libc arena */
#endif

/* blockproc[all](2), unblockproc[all](2), setblockproccnt[all](2) limits */
#define PR_MAXBLOCKCNT	 10000
#define PR_MINBLOCKCNT	-10000

#ifdef __cplusplus
}
#endif

#endif /* __PRCTL_H__ */
