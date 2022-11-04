/**************************************************************************
 *									  *
 * 		 Copyright (C) 1990-1993 Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/
/*
 * Copyright 1985 by MIPS Computer Systems, Inc.
 */
#ifndef __SYS_SYSCALL_H__
#define __SYS_SYSCALL_H__
#ident	"$Revision: 1.29 $"

#if defined(_LANGUAGE_ASSEMBLY)
/*
 * SYSCALL -- standard system call sequence
 * The kernel expects arguments to be passed with the normal C calling
 * sequence.  v0 should contain the system call number.  On return from
 * the kernel mode, a3 will be 0 to indicate no error and non-zero to
 * indicate an error; if an error occurred v0 will contain an errno.
 * WARNING - restartable system call conventions REQUIRES that the li of
 * v0 is immediately before the syscall instrcution
 */
	.globl	_cerror
#define JCERROR						\
	la	t9, _cerror;				\
	j	t9

	.globl	_cerror64
#define	JCERROR64					\
	la	t9, _cerror64;				\
	j	t9

#ifdef PIC

#define EPILOGUE_BODY					\
	.set	noreorder;				\
9:							\
	move	t8, ra;		/* save old ra */	\
	bal	10f;		/* find addr of cpload */\
	nop;						\
10:							\
	.cpload ra;					\
	move	ra, t8;					\
	.set	reorder

#else /* PIC */

#define EPILOGUE_BODY					\
9:							\
	.set	reorder

#endif /* PIC */

#define	EPILOGUE					\
	EPILOGUE_BODY;					\
	JCERROR

#define EPILOGUE64					\
	EPILOGUE_BODY;					\
	JCERROR64

#define SYSCALL(x)	GSYSCALL(x,x)
#define PSEUDO(x,y)	GSYSCALL(x,y)

#define	GSYSCALL(x,y)					\
.weakext	x, _/**/x;				\
PICOPT;							\
LEAF(_/**/x);						\
	.set	noreorder;				\
	li	v0,SYS_/**/y;				\
	syscall;					\
	bne	a3,zero,9f;				\
	nop;

#define	RET(x)						\
	j	ra;					\
	nop;						\
	EPILOGUE;					\
	.end	x

#define	RET64(x)					\
	j	ra;					\
	nop;						\
	EPILOGUE64;					\
	.end	x

#endif /* ASSEMBLY */

/*
 * Rest of file for /proc system call tracing and kernel syscall table
 */
#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
#include "sys/types.h"

#ifndef _KERNEL
/*
 * The /proc syscall numbers start from 2 onwards. 2 corresponds to bit 1
 * (assuming an integer's bits are numbered 0..31 with 0 being the LSB)
 * in sysset_t since it gets decremented by 1 in praddset (sys/procfs.h).
 * Thus we maintain compatibility with the old /debug syscall numbers
 * (which start with 1) since the same bit would be set for both 
 * the /debug and /proc interfaces.
 */
#include <sys.s>	/* syscall numbers with kernel offset SYSVoffset */
#undef SYSVoffset
#define SYSVoffset	1
#endif /* !_KERNEL */

typedef struct {
	__uint32_t word[16];
} sysset_t;


#if defined(_SGI_SOURCE) || defined (_KERNEL)
/*
 * system call argument encoding - used by par(1)
 */
typedef unsigned short sysargdesc_t;

/*
 * top 4 bits are arg#
 * next 4 bits are type
 * bottom 8 bits are size
 * a 0 implies that the arg is passed by value rather than by reference
 * NOTE - we use arg #'s 1-n so various macros subtract 1 to get an
 * array index.
 */
/* arg numbers */
#define SY_GETARG(x)	((((x) >> 12) & 0xf) -1)
#define SY_ARG(x)	(x<<12)	/* arg #x */

/* types */
#define SY_GETTYPE(x)	((x) & 0x0f00)
#define SY_STRING	(1<<8)	/* arg is null terminated string */
#define SY_OUTSTRING	(2<<8)	/* arg is returned string */
#define SY_IN		(3<<8)	/* arg pts to fixed # of bytes */
#define SY_OUT		(4<<8)	/* arg pts to fixed # of bytes (output) */
#define SY_INSPECIAL	(5<<8)	/* special difficult decoding - use bottom
				 * bits to index into special table
				 */
#define SY_OUTSPECIAL	(6<<8)	/* special difficult decoding - output */
#define SY_OUTV		(7<<8)	/* arg pts to variable # of bytes */
#define SY_INV		(8<<8)	/* arg pts to variable # of bytes -
				 * bottom bits says which arg to use
				 */
#define SY_OUTVI	(9<<8)	/* arg pts to variable # of bytes
				 * which is given by a value-result parm
				 * an arg # 0 means use rval1
				 */

#define SY_GETSIZE(x)	((x) & 0xff)

/* SY_VARIABLE encodes variable # in 'size' field */
#define SY_GETVARG(x)	(((x) & 0xff) - 1)
#define SY_VARG(x)	(x)

/* SY_SPECIAL - encode special table index in 'size' field */
#define SY_GETSPIDX(x)	((x) & 0xff)
#define SY_SPIDX(x)	(x)

#endif
	
#ifdef _KERNEL

#define MAX_SYSARGS	6
/*
 * Structure of the system-entry table
 */
extern struct sysent {
	char	sy_narg;	/* total number of arguments */
	char	sy_flags;	/* various flag bits (see below) */
	int	(*sy_call)();	/* handler */
	sysargdesc_t *sy_argdesc; /* descriptors for args */
} sysent[];

#define	SY_SETJMP	0x01	/* if setjmp() is necessary before syscall */
#define	SY_INDIR	0x02	/* another routine will do demultiplexing */
#define	SY_FULLRESTORE	0x10	/* restore all regs */
#define SY_NOXFSZ	0x40	/* do not send SIGXFSZ if EFBIG error */
#define SY_NORESTART	0x80	/* don't restart these syscalls */

/*
 * Per-process system call handler info
 */
struct syscallsw {
	struct	sysent	*sc_sysent;		/* pointer to sysent table */
	unsigned sc_nsysent;			/* table size */
	int	(*sc_maperrno)(int);		/* function to remap errnos */
	int	sc_flags;			/* everything has flags! */
	int	(*sc_mapsignal)(int);		/* function to remap signals */
	int	(*sc_uipc_ioctl)(int, int, char *);   /* remap uipc ioctls */
};

extern struct syscallsw	syscallsw[];		/* defined in os/main.c */

#endif /* _KERNEL */

#endif /* language C */
#endif /* __SYS_SYSCALL_H__ */
