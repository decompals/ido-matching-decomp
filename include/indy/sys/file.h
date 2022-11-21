/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1984, 1986, 1987, 1988, 1989, 1990 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef _FS_FILE_H	/* wrapper symbol for kernel use */
#define _FS_FILE_H	/* subject to change without notice */

#ifdef __cplusplus
extern "C" {
#endif

/*#ident	"@(#)uts-3b2:fs/file.h	1.5"*/
#ident	"$Revision: 3.41 $"

#if defined(_KERNEL) || defined(_KMEMUSER)
#include <sys/types.h>
#include <sys/sema.h>
#endif

#ifndef _KERNEL
#include <sys/fcntl.h>			/* Irix and BSD compatibility */
#endif

#if defined(_KERNEL) || defined(_KMEMUSER)
/*
 * One file structure is allocated for each open/creat/pipe call.
 * Main use is to hold the read/write pointer associated with
 * each open file.
 * f_lock  protects:
 *	f_flag
 *	f_count
 *	f_msgcount
 */
typedef struct file {
	struct file	*f_next;	/* pointer to next entry */
	struct file	*f_prev;	/* pointer to previous entry */
	ushort		f_flag;
	cnt_t		f_count;	/* reference count */
	lock_t		f_lock;		/* spinlock for f_flag and f_count */
	struct vnode	*f_vnode;	/* pointer to vnode structure */
	off_t		f_offset;	/* read/write character pointer */
	struct	cred	*f_cred;	/* credentials of user who opened it */
	cnt_t		f_msgcount;	/* Unix domain msg reference count */
#ifdef MERGE
	struct	file	*f_slnk;	/* XENIX semaphore queue */
#endif
} file_t;
#define	NULLFP ((struct file *)0)
#endif /* _KERNEL || _KMEMUSER */

/* flags */
#define	FMASK		0x90FF

#define	FOPEN		0xFFFFFFFF
#define	FREAD		0x01
#define	FWRITE		0x02

#ifndef	_F_FLAGS
#define	_F_FLAGS
#define	FNDELAY		0x04
#define	FAPPEND		0x08
#define	FSYNC		0x10
#define	FNONBLOCK	0x80
#define	FASYNC		0x1000
#if defined(_SGI_SOURCE) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)
#define	FNONBLK		FNONBLOCK
#define FDIRECT		0x8000
#endif

/* open-only modes */
#define	FCREAT		0x0100
#define	FTRUNC		0x0200
#define	FEXCL		0x0400
#define	FNOCTTY		0x0800
#endif	/* _F_FLAGS */

#if defined(_KERNEL) || defined(_KMEMUSER)
#define	IRIX4_FASYNC	0x40
/*
 * Unix domain support.
 * These flags are set and cleared in f_flag - they may overlap
 * with values that are passed only (and never recorded in f_flag) (like FNMFS)
 */
#define	FMARK		0x4000
#define	FDEFER		0x2000

/*
 * shared file descriptor handling
 * This overlaps with open-only flags that are never recorded in f_flag
 */
#define FINPROGRESS	0x0400	/* being opened */
/* Flag to allow I/O without updating timestamps.  Currently only for xFS. */
#define FINVIS		0x0100		/* don't update timestamps */

/*
 * This mode is a kludge to allow pre-SVR4 RFS servers to survive opens
 * of namefs-mounted files.  The SVR4 implmentation of the old protocol
 * expects a lookup to precede every open, but namefs departs from that
 * model.  We provide the mode to allow the client to detect and fail
 * the open, thereby protecting server reference counts.  This mode
 * will disappear when support for the old RFS protocol is dropped.
 */
#define	FNMFS		0x2000
#endif

/* file descriptor flags */
#define	FCLOSEXEC	001	/* close on exec */

#ifdef _KERNEL
/*
 * Routines and macros dealing with user per-open file flags and
 * user open files.  
 */
#define	FLOCK(fp)	splock((fp)->f_lock)
#define	FUNLOCK(fp, s)	spunlock((fp)->f_lock, s)

#define	FHOLD(fp)	{ int _fhold_s = FLOCK(fp); (fp)->f_count++; \
			  FUNLOCK(fp, _fhold_s); }
#define	FDROP(fp)	{ int _fdrop_s = FLOCK(fp); --(fp)->f_count; \
			  FUNLOCK(fp, _fdrop_s); }

/* flags for getff */
#define FDSHD		0x0001	/* sharing file descriptors */
#define FDNOMARK	0x0002	/* do not mark as in use */
#define FDIGNPROGRESS	0x0004	/* ignore fact that fd might be 'INPROGRESS' */

/* definition to mark an fd as allocated, but before a real fp is plugged in */
#define FDALLOCED	(void *)(-1)

struct vnode;
struct user;
extern int getnofiles(void);
extern int getf(int, file_t **);
extern int getff(int, file_t **, int, char *);
extern int getfhi(void);
extern int closef(file_t *);
extern int closefd(int, file_t **);
extern int ufalloc(int, int *);
extern int falloc(struct vnode *, int, file_t **, int *);
extern void fready(file_t *);
extern void finit(void);
extern void unfalloc(file_t *);
extern void setf(int, file_t *);
extern int dupf(int, file_t *, int *);
extern char getpof(int);
extern void setpof(int, char);
extern int fassign(struct vnode **, int, int*);
extern int filescan(int (*)(struct file *, void *), void *);
extern int fdfuser(struct user *, struct vnode *, int);
extern struct ufchunk *fdfork(int *);
extern void fdforkfree(struct ufchunk *, int);
extern void closeall(void);
#else	/* !_KERNEL */

/* The following are extensions for 4.3BSD compatibility. */

/*
 * Flock(3) call.
 */
#define	LOCK_SH		1	/* shared lock */
#define	LOCK_EX		2	/* exclusive lock */
#define	LOCK_NB		4	/* don't block when locking */
#define	LOCK_UN		8	/* unlock */

#if !defined(__cplusplus) || defined(_BSD_COMPAT)
/*
 * In C++, struct flock from <sys/fcntl.h> collides with flock(3B)'s name.
 * Require C++ users to define _BSD_COMPAT to get the flock prototype.
 */
extern int flock(int, int);
#endif /* !__cplusplus || _BSD_COMPAT */

/*
 * Access call.  Also defined in <unistd.h>
 */
#ifndef F_OK
#define	F_OK		0	/* does file exist */
#define	X_OK		1	/* is it executable by caller */
#define	W_OK		2	/* writable by caller */
#define	R_OK		4	/* readable by caller */
#endif

/*
 * Lseek call.	See the POSIX equivalents in <unistd.h>.
 */
#ifndef L_SET
#define	L_SET	0	/* for lseek */
#endif
#ifndef L_INCR
#define	L_INCR		1	/* relative to current offset */
#endif
#ifndef L_XTND
#define	L_XTND		2	/* relative to end of file */
#endif

#endif	/* !_KERNEL */

#ifdef __cplusplus
}
#endif

#endif	/* _FS_FILE_H */
