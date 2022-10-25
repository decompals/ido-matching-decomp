#ifndef _SYS_FNCTL_H
#define _SYS_FNCTL_H

/* Copyright (C) 1989 Silicon Graphics, Inc. All rights reserved.  */
/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*#ident	"@(#)kern-port:sys/fcntl.h	10.3"*/
#ident	"$Revision: 3.37 $"

#ifndef _SYS_TYPES_H
#include <sys/types.h>
#endif

#if defined(_SGI_SOURCE) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)
#ifndef _F_FLAGS		/* Irix compatibility */
#define _F_FLAGS
/*
 * flags for F_GETFL, F_SETFL
 */
#define	FNDELAY		0x04	/* Non-blocking I/O */
#define	FAPPEND		0x08	/* append (writes guaranteed at the end) */
#define	FSYNC		0x10	/* synchronous write option */
#define	FNONBLOCK	0x80	/* Non-blocking I/O */
#define	FASYNC		0x1000	/* interrupt-driven I/O for sockets */
#define	FNONBLK		FNONBLOCK
#define	FDIRECT		0x8000

/*
 * open only modes
 */
#define	FCREAT	0x0100		/* create if nonexistent */
#define	FTRUNC	0x0200		/* truncate to zero length */
#define	FEXCL	0x0400		/* error if already created */
#define	FNOCTTY	0x0800		/* don't make this tty control term */
#endif	/* _F_FLAGS */
#endif /* SGI_SOURCE ... */

/*
 * Flag values accessible to open(2) and fcntl(2)
 * (the first three and O_DIRECT can only be set by open).
 */
#define	O_RDONLY	0
#define	O_WRONLY	1
#define	O_RDWR		2
#if !defined(_POSIX_SOURCE) 
#define	O_NDELAY	0x04	/* non-blocking I/O */
#endif /* !defined(_POSIX_SOURCE) */ 
#define	O_APPEND	0x08	/* append (writes guaranteed at the end) */
#if !defined(_POSIX_SOURCE) || defined(_XOPEN_SOURCE) 
#define	O_SYNC		0x10	/* synchronous write option */
#endif /* !defined(_POSIX_SOURCE) || defined(_XOPEN_SOURCE */ 
#define	O_NONBLOCK	0x80	/* non-blocking I/O (POSIX) */
#if defined(_SGI_SOURCE) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)
#define O_DIRECT	0x8000	/* direct I/O */
#endif /* SGI && !POSIX && !XOPEN */
/*
 * Flag values accessible only to open(2).
 */
#define	O_CREAT		0x100	/* open with file create (uses third open arg) */
#define	O_TRUNC		0x200	/* open with truncation */
#define	O_EXCL		0x400	/* exclusive open */
#define	O_NOCTTY	0x800	/* don't allocate controlling tty (POSIX) */

/* fcntl(2) requests */
#define	F_DUPFD		0	/* Duplicate fildes */
#define	F_GETFD		1	/* Get fildes flags */
#define	F_SETFD		2	/* Set fildes flags */
#define	F_GETFL		3	/* Get file flags */
#define	F_SETFL		4	/* Set file flags */

#define	F_GETLK		14	/* Get file lock */

#define	F_SETLK		6	/* Set file lock */
#define	F_SETLKW	7	/* Set file lock and wait */

#if !defined(_POSIX_SOURCE) 
#define	F_CHKFL		8	/* Unused */
#define	F_ALLOCSP	10	/* Reserved */
#define	F_FREESP	11	/* Free file space */

#if defined(_SGI_SOURCE)
#define	F_SETBSDLK	12	/* Set Berkeley record lock */
#define	F_SETBSDLKW	13	/* Set Berkeley record lock and wait */
#define	F_DIOINFO	30	/* get direct I/O parameters */
#define	F_FSGETXATTR	31	/* get extended file attributes (xFS) */
#define	F_FSSETXATTR	32	/* set extended file attributes (xFS) */
#define	F_GETLK64	33	/* Get 64 bit file lock */
#define	F_SETLK64	34	/* Set 64 bit file lock */
#define	F_SETLKW64	35	/* Set 64 bit file lock and wait */
#define	F_ALLOCSP64	36	/* Alloc 64 bit file space */
#define	F_FREESP64	37	/* Free 64 bit file space */
#define	F_GETBMAP	38	/* Get block map (64 bit only) */
#define	F_FSSETDM	39	/* Set DMI event mask and state (XFS only) */
#endif /* defined(_SGI_SOURCE) */

#define F_RSETLK	20	/* Remote SETLK for NFS */
#define F_RGETLK	21	/* Remote GETLK for NFS */
#define F_RSETLKW	22	/* Remote SETLKW for NFS */

/* only for sockets */
#define	F_GETOWN	23	/* Get owner (socket emulation) */
#define	F_SETOWN	24	/* Set owner (socket emulation) */
#if defined(_KERNEL) || defined(_KMEMUSER)
#define	F_O_GETLK	5	/* SVR3 Get file lock */
#define	F_O_GETOWN	10
#define	F_O_SETOWN	11
#endif /* _KERNEL || _KMEMUSER */
#endif /* !defined(_POSIX_SOURCE) */ 

#if !defined(LANGUAGE_C_PLUS_PLUS) || !defined(_BSD_COMPAT)
/*
 * File segment locking set data type - information passed to system by user.
 */
typedef struct flock {
	short	l_type;
	short	l_whence;
	off_t	l_start;
	off_t	l_len;		/* len == 0 means until end of file */
        long	l_sysid;
        pid_t	l_pid;
	long	pad[4];		/* reserve area */
} flock_t;

#if defined(_SGI_SOURCE) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)
/*
 * File segment locking set data type for 64 bit access.
 */
typedef struct flock64 {
	short	l_type;
	short	l_whence;
	off64_t	l_start;
	off64_t	l_len;		/* len == 0 means until end of file */
        long	l_sysid;
        pid_t	l_pid;
	long	pad[4];		/* reserve area */
} flock64_t;
#endif

#if defined(_KERNEL) || defined(_KMEMUSER)
typedef struct o_flock {
	short	l_type;
	short	l_whence;
	long	l_start;
	long	l_len;		/* len == 0 means until end of file */
        short   l_sysid;
        o_pid_t l_pid;
} o_flock_t;
#endif	/* defined(_KERNEL) */

#endif	/* !C++ || !BSD */

/*
 * File segment locking types.
 */
#define	F_RDLCK	01	/* Read lock */
#define	F_WRLCK	02	/* Write lock */
#define	F_UNLCK	03	/* Remove lock(s) */

/*
 * POSIX constants 
 */

#define	O_ACCMODE	3	/* Mask for file access modes */
#define	FD_CLOEXEC	1	/* close on exec flag */

#if defined(_SGI_SOURCE) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)

/*
 * NOTE: This flag is checked only for graphics processes.  It is for
 *       SGI internal use only.
 */
#define FD_NODUP_FORK	4	/* don't dup fd on fork (sproc overrides) */

/* 
 * direct I/O attribute record used with F_DIOINFO
 * d_miniosz is the min xfer size, xfer size multiple and file seek offset
 * alignment.
 */
struct dioattr {
	unsigned	d_mem;		/* data buffer memory alignment */
	unsigned	d_miniosz;	/* min xfer size */
	unsigned	d_maxiosz;	/* max xfer size */
};

/*
 * Structure for F_FSGETXATTR and F_FSSETXATTR.
 */
struct fsxattr {
	unsigned long	fsx_xflags;	/* xflags field value (get/set) */
	unsigned long	fsx_extsize;	/* extsize field value (get/set) */
	unsigned long	fsx_nextents;	/* nextents field value (get) */
	uuid_t		fsx_uuid;	/* uuid field value (get) */
};

/*
 * Structure for F_GETBMAP.
 * On input, fill in bmv_offset and bmv_length of the first structure
 * to indicate the area of interest in the file, and bmv_entry with the
 * number of array elements given.  The first structure is updated on
 * return to give the offset and length for the next call.
 */
struct getbmap {
	__int64_t	bmv_offset;	/* file offset of segment in blocks */
	__int64_t	bmv_block;	/* starting block (64-bit daddr_t) */
	__int64_t	bmv_length;	/* length of segment, blocks */
	__int32_t	bmv_count;	/* # of entries in array incl. first */
	__int32_t	bmv_entries;	/* # of entries filled in (output) */
};

#endif /* SGI && !POSIX && !XOPEN */

#endif /* !__SYS_FNCTL_H__ */
