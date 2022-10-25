/*
 * Copyright 1990,1992 Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
 * the contents of this file may not be disclosed to third parties, copied or
 * duplicated in any form, in whole or in part, without the prior written
 * permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
 * and Computer Software clause at DFARS 252.227-7013, and/or in similar or
 * successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
 * rights reserved under the Copyright Laws of the United States.
 */
/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#ident	"$Revision: 3.70 $"

#include <sgidefs.h>

/* POSIX Extensions */
typedef unsigned char   uchar_t;
typedef unsigned short  ushort_t;
typedef unsigned int    uint_t;
typedef unsigned long   ulong_t;

/* Primarily Kernel types */
typedef	char *		addr_t;		/* ?<core address> type */
typedef	char *		caddr_t;	/* ?<core address> type */
typedef	long		daddr_t;	/* <disk address> type */
typedef	long		pgno_t;		/* virtual page number type */
typedef	__uint32_t	pfn_t;		/* physical page number type */
typedef	short		cnt_t;		/* ?<count> type */
#if !defined(_POSIX_SOURCE)
typedef enum { B_FALSE, B_TRUE } boolean_t;
#endif

/*
 * The following type is for various kinds of identifiers.  The
 * actual type must be the same for all since some system calls
 * (such as sigsend) take arguments that may be any of these
 * types.  The enumeration type idtype_t defined in sys/procset.h
 * is used to indicate what type of id is being specified.
 */

#if (_MIPS_SZLONG == 32)
typedef long			id_t;	/* A process id,	*/
					/* process group id,	*/
					/* session id, 		*/
					/* scheduling class id,	*/
					/* user id, or group id.*/
#endif
#if (_MIPS_SZLONG == 64)
typedef __uint32_t		id_t;
#endif

/* Typedefs for dev_t components */

#if (_MIPS_SZLONG == 32)
typedef ulong_t	major_t;	/* major part of device number */
typedef ulong_t	minor_t;	/* minor part of device number */
#endif
#if (_MIPS_SZLONG == 64)
typedef __uint32_t major_t;	/* major part of device number */
typedef __uint32_t minor_t;	/* minor part of device number */
#endif

/* Universally Unique Identifiers */

typedef struct {
        unsigned char	u_bits[16];
} uuid_t, *uuid_p_t;


/*
 * For compatilbility reasons the following typedefs (prefixed o_) 
 * can't grow regardless of the EFT definition. Although,
 * applications should not explicitly use these typedefs
 * they may be included via a system header definition.
 * WARNING: These typedefs may be removed in a future
 * release. 
 *		ex. the definitions in s5inode.h remain small 
 *			to preserve compatibility in the S5
 *			file system type.
 */
typedef	ushort_t o_mode_t;		/* old file attribute type */
typedef short	o_dev_t;		/* old device type	*/
typedef	ushort_t o_uid_t;		/* old UID type		*/
typedef	o_uid_t	o_gid_t;		/* old GID type		*/
typedef	short	o_nlink_t;		/* old file link type	*/
typedef short	o_pid_t;		/* old process id type */
typedef __uint32_t o_ino_t;		/* old inode type	*/

#if (_MIPS_SZLONG == 32)
typedef	unsigned long	mode_t;		/* file attrs */
typedef	unsigned long	dev_t;		/* device type */
typedef	long		uid_t;
typedef	long		gid_t;
typedef unsigned long	nlink_t;	/* used for link counts */
typedef long		pid_t;		/* proc & grp IDs  */
typedef	unsigned long	ino_t;		/* <inode> type */
#endif
#if (_MIPS_SZLONG == 64)
typedef	__uint32_t	mode_t;		/* file attrs */
typedef	__uint32_t	dev_t;		/* device type */
typedef	__int32_t	uid_t;
typedef	__int32_t	gid_t;
typedef __uint32_t	nlink_t;	/* used for link counts */
typedef __int32_t	pid_t;		/* proc & grp IDs  */
typedef	__uint32_t	ino_t;		/* <inode> type */
#endif

typedef __uint64_t	ino64_t;	/* bit inode number type */

#if !defined(_KERNEL) || defined(_STANDALONE)
typedef	long		off_t;		/* byte offset type */
#else	/* !_KERNEL || _STANDALONE */
typedef __int64_t	off_t;		/* byte offset type */
#endif	/* !_KERNEL || _STANDALONE */
typedef	__int64_t	off64_t;	/* big byte offset type */

typedef __scint_t	__scoff_t;	/* scaling off_t */
#if defined(_KERNEL) || ( !defined(_XOPEN_SOURCE) && !defined(_POSIX_SOURCE) )
typedef __scoff_t	scoff_t;	/* kernel scaling off_t */
#endif /* defined(_KERNEL) || ( !defined(_XOPEN_SOURCE) && !defined(_POSIX_SOURCE) ) */


typedef	long		swblk_t;
typedef	unsigned long	paddr_t;	/* <physical address> type */
typedef	int		key_t;		/* IPC key type */
typedef	unsigned char	use_t;		/* use count for swap.  */
typedef	short		sysid_t;
typedef	short		index_t;
typedef unsigned int	lock_t;		/* <spinlock> type */
typedef	signed char	cpuid_t;	/* cpuid */

#if !defined(_SIZE_T) && !defined(_SIZE_T_)
#define _SIZE_T
#if (_MIPS_SZLONG == 32)
typedef unsigned int size_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef unsigned long size_t;
#endif
#endif /* !_SIZE_T */

#ifndef _SSIZE_T
#define _SSIZE_T
#if (_MIPS_SZLONG == 32)
typedef int    ssize_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef long    ssize_t;
#endif
#endif

#ifndef _TIME_T
#define _TIME_T
typedef	long		time_t;		/* <time> type */
#endif /* !_TIME_T */

#ifndef _CLOCK_T
#define _CLOCK_T
typedef	long		clock_t; /* relative time in a specified resolution */
#endif	/* !_CLOCK_T */

#if defined(__mips)
/*
 * To permit types.h to be used for rudimentary cross-compilation -
 * don't define any type that requires sgidefs.h/mips C compiler
 */
typedef __scunsigned_t	bitnum_t;	/* bit number */
typedef __scunsigned_t	bitlen_t;	/* bit length */
#endif

typedef int processorid_t;		/* a processor name */
typedef int toid_t;			/* timeout id */
typedef	long *qaddr_t;		      /* XXX should be typedef quad * qaddr_t */
typedef __uint32_t inst_t;		/* an instruction */

/* a cpu machine register - user interface definitions */

#if (_MIPS_ISA == _MIPS_ISA_MIPS1 || _MIPS_ISA == _MIPS_ISA_MIPS2) 
typedef unsigned machreg_t;
#endif

#if (_MIPS_ISA == _MIPS_ISA_MIPS3 || _MIPS_ISA == _MIPS_ISA_MIPS4) 
typedef __uint64_t machreg_t;
#endif

/* a fpu machine register - user interface definitions */

#if (_MIPS_FPSET == 16)
typedef __uint32_t fpreg_t;
#endif

#if (_MIPS_FPSET == 32)
typedef __uint64_t fpreg_t;
#endif

typedef	signed char	int8_t;
typedef	short		int16_t;
typedef	__int32_t	int32_t;
typedef	unsigned char	u_int8_t;
typedef	unsigned short	u_int16_t;
typedef	__uint32_t	u_int32_t;

#if defined(_KERNEL) || ( !defined(_XOPEN_SOURCE) && !defined(_POSIX_SOURCE) )
/*
 * The following is the value of type id_t to use to indicate the
 * caller's current id.  See procset.h for the type idtype_t
 * which defines which kind of id is being specified.
 */
#define	P_MYID	(-1)

#define NOPID (pid_t)(-1)

#ifndef NODEV
#define NODEV (dev_t)(-1)
#endif /* !NODEV */

#define	P_MYPID	((pid_t)0)
/*
 * A host identifier is used to uniquely define a particular node
 * on an rfs network.  Its type is as follows.
 */
typedef	long	hostid_t;

/*
 * The following value of type hostid_t is used to indicate the
 * current host.
 */
#define	P_MYHOSTID	(-1)

#endif /* defined(_KERNEL) || ( !defined(_XOPEN_SOURCE) && !defined(_POSIX_SOURCE) ) */

#if ( !defined(_XOPEN_SOURCE) && !defined(_POSIX_SOURCE) ) || defined(_BSD_TYPES) || defined(_BSD_COMPAT)
/*
 * Nested include for BSD/sockets source compatibility.
 * (The select macros used to be defined here).
 */
#include <sys/bsd_types.h>
#endif

/*typedef __uint64_t k_sigset_t;*/
typedef struct {                /* signal set type */
        __uint32_t sigbits[2];
} k_sigset_t;
typedef __uint32_t k_fltset_t;     /* kernel fault set type */

#if defined(_KERNEL) || defined(_STANDALONE) || defined(_KMEMUSER)
/*
 * The Kernel must be able to interface between 32 and 64 bit programs
 * at the same time. Thus any user<->kernel interface structures
 * must either be the same size regardless of compilation mode, or
 * the kernel needs special internal versions of the structures.
 * Since how many bits are in an 'int/unsigned/long' hasn't been
 * decided yet, we use typedefs to permit easy changing
 *
 * The syscall interface is always composed of machine register sized
 * quantitied. So in 32 bit mode, every arg is 32 bits and in 64 bit
 * mode all args are 64 bit, regardless of the true 'type'
 */

/*
 * application base types
 * Currently assume 32 bit int, 64 bit long for 64 bit apps
 */
typedef __int32_t app32_int_t;
typedef __uint32_t app32_uint_t;
typedef __int32_t app32_long_t;
typedef __uint32_t app32_ulong_t;
typedef __int64_t app32_long_long_t;
typedef __uint64_t app32_ulong_long_t;
typedef __int32_t app64_int_t;
typedef __uint32_t app64_uint_t;
typedef __int64_t app64_long_t;
typedef __uint64_t app64_ulong_t;
typedef __uint32_t app32_ptr_t;
typedef __uint64_t app64_ptr_t;

/*
 * syscall arg type - its 32 or 64 bit depending on the compilation mode
 * its either signed or unsigned
 */
#if defined(_K64U64)
typedef __int64_t sysarg_t;
typedef __uint64_t usysarg_t;
#else
typedef int sysarg_t;
typedef unsigned usysarg_t;
#endif

/* a cpu machine register - kernel view */
#if defined(_K32U64) || defined(_K64U64) || defined(_K32US64)
typedef __uint64_t k_machreg_t;
typedef __int64_t k_smachreg_t;
#else
typedef unsigned k_machreg_t;
typedef long k_smachreg_t;
#endif

#if defined(_K64U64) || defined(_K32U64)
typedef __uint64_t k_fpreg_t;
#else
typedef unsigned k_fpreg_t;
#endif

/*
 * Since device drivers may need to know which ABI the current user process
 * is running under in order to use the correct types, we provide the
 * following structure.  See ddi.h for the definition of userabi().
 * All sizes are in bytes.
 */
typedef struct __userabi {
	short uabi_szint;
	short uabi_szlong;
	short uabi_szptr;
	short uabi_szlonglong;
} __userabi_t;


/*
 * Internal Kernel types only
 */
typedef void *		sm_swaphandle_t;/* swap manager handle */
typedef struct anon *	anon_hdl;	/* anon manager handle */
typedef	int		 (*pl_t)();	/* priority level */
#ifdef EVEREST
typedef long long	cpumask_t;	/* bit position == cpuid */
#else
typedef unsigned int	cpumask_t;	/* bit position == cpuid */
#endif

#endif /* _KERNEL || _STANDALONE || _KMEMUSER */

#endif /* _SYS_TYPES_H */
