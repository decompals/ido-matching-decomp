#ifndef __UNISTD_H__
#define __UNISTD_H__
#ifdef __cplusplus
extern "C" {
#endif
#ident "$Revision: 1.78 $"
/*
*
* Copyright 1992-1993, Silicon Graphics, Inc.
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
/*	Copyright (c) 1988 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) || (_LANGUAGE_ASSEMBLY)

/* Symbolic constants for the "access" routine: */
#ifndef F_OK
#define	R_OK	004	/* Test for Read permission */
#define	W_OK	002	/* Test for Write permission */
#define	X_OK	001	/* Test for eXecute permission */
#define	F_OK	000	/* Test for existence of File */
#endif

#define EFF_ONLY_OK 	010	/* Test using effective ids */
#define EX_OK		020	/* Test for Regular, executable file */
#endif /* _LANGUAGE_C  _LANGUAGE_C_PLUS_PLUS _LANGUAGE_ASSEMBLY */

#if !defined(_POSIX_SOURCE) 
#define F_ULOCK	0	/* Unlock a previously locked region */
#define F_LOCK	1	/* Lock a region for exclusive use */
#define F_TLOCK	2	/* Test and lock a region for exclusive use */
#define F_TEST	3	/* Test a region for other processes locks */

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) || (_LANGUAGE_ASSEMBLY)

/* _daemonize(3C) flags */
#define	_DF_NOFORK	0x1	/* don't fork */
#define	_DF_NOCHDIR	0x2	/* don't chdir to / */
#define	_DF_NOCLOSE	0x4	/* close no files */
#endif /* _LANGUAGE_C  _LANGUAGE_C_PLUS_PLUS _LANGUAGE_ASSEMBLY */
#endif /* !defined(_POSIX_SOURCE) */ 


#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) || (_LANGUAGE_ASSEMBLY)
/* Symbolic constants for the "lseek" routine: */
#ifndef SEEK_SET                /* also defined in stdio.h */
#define	SEEK_SET	0	/* Set file pointer to "offset" */
#define	SEEK_CUR	1	/* Set file pointer to current plus "offset" */
#define	SEEK_END	2	/* Set file pointer to EOF plus "offset" */
#endif /* !SEEK_SET */

#if !defined(_POSIX_SOURCE) 
/* Path names: */
#define	GF_PATH	"/etc/group"	/* Path name of the "group" file */
#define	PF_PATH	"/etc/passwd"	/* Path name of the "passwd" file */
#endif /* !defined(_POSIX_SOURCE) */ 

/* compile-time symbolic constants,
** Support does not mean the feature is enabled.
** Use pathconf/sysconf to obtain actual configuration value.
** 
*/

#define _POSIX_JOB_CONTROL	1
#define _POSIX_SAVED_IDS	1
#define _POSIX_REALTIME_SIGNALS	1
#define _POSIX_ASYNCHRONOUS_IO	1

#ifndef _POSIX_VDISABLE
#define _POSIX_VDISABLE		0
#endif

#ifndef	NULL
#define NULL	0
#endif

#define	STDIN_FILENO	0
#define STDOUT_FILENO	1
#define STDERR_FILENO	2

/* Current version of POSIX */
#ifndef _POSIX_VERSION
#define _POSIX_VERSION	199009L
#endif

/* Current version of XOPEN */
#ifndef _XOPEN_VERSION
#define _XOPEN_VERSION 3
#endif

/* typedefs required by POSIX 1003.1-1990 */
#if !defined(_SIZE_T) && !defined(_SIZE_T_)
#define _SIZE_T
#if (_MIPS_SZLONG == 32)
typedef unsigned int size_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef unsigned long size_t;
#endif
#endif

#ifndef _SSIZE_T
#define _SSIZE_T
#if (_MIPS_SZLONG == 32)
typedef int    ssize_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef long    ssize_t;
#endif
#endif

#include <sys/types.h>
#include <sys/unistd.h>

#if !defined(_POSIX_SOURCE) 
struct iovec;
struct timeval;
extern int acct(const char *);
extern int brk(void *);
extern int chroot(const char *);
extern int fattach(int, const char *);
extern int fchdir(int);
extern int fchown(int, uid_t, gid_t);
extern int fdetach(const char *);
extern int fsync(int);
extern int ftruncate(int, off_t);
extern pid_t getpgid(pid_t);
extern char *gettxt(const char *, const char *);
extern pid_t getsid(pid_t);
extern int ioctl(int, int, ...);
extern int lchown(const char *, uid_t, gid_t);
extern int lockf(int, int, long);
extern int mincore(caddr_t, size_t, char *);
extern int nice(int);
extern void profil(unsigned short *, unsigned int, unsigned int, unsigned int);
extern int ptrace(int, pid_t, int, int);
extern char *re_comp(const char *);
extern int re_exec(const char *);
extern int readlink(const char *, void *, size_t);
extern int readv(int, struct iovec *, int);
extern void *sbrk(int);
#if defined(_BSD_COMPAT)
extern int setgroups(int, int *);
extern int setpgrp(int, int);
#else	/* !_BSD_COMPAT */
extern int setgroups(int, const gid_t *);
extern pid_t    setpgrp(void);
#endif /* _BSD_COMPAT */
extern int stime(const time_t *);
extern int symlink(const char *, const char *);
extern void sync(void);
extern int truncate(const char *, off_t);
extern int vhangup(void);
extern int writev(int, const struct iovec *, int);
#endif /* !defined(_POSIX_SOURCE) */ 

#if ( !defined(_XOPEN_SOURCE) && !defined(_POSIX_SOURCE) ) || defined(_BSD_TYPES) || defined(_BSD_COMPAT)
/* SVR4 doesn't have select here, but want to use the same predicate as
 * types.h for inclusion of bsd_types.h/select.h
 */
extern int select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
#endif

/*
 * POSIX 1003.1 Functions
 */
extern int access(const char *, int);
extern unsigned alarm(unsigned);
extern int chdir(const char *);
extern int chown(const char *, uid_t, gid_t);
extern int close(int);
extern char *ctermid(char *);
extern char *cuserid(char *);
extern int dup(int);
extern int dup2(int, int);
extern int execl(const char *, const char *, ...);
extern int execle(const char *, const char *, ...);
extern int execlp(const char *, const char *, ...);
extern int execv(const char *, char *const *);
extern int execve(const char *, char *const *, char *const *);
extern int execvp(const char *, char *const *);
extern void exit(int);
extern void _exit(int);
extern pid_t fork(void);
extern long fpathconf(int, int);
extern char *getcwd(char *, size_t);    /* POSIX flavor of getcwd) */
extern gid_t getegid(void);
extern uid_t geteuid(void);
extern gid_t getgid(void);
#if defined(_BSD_COMPAT)
extern int getgroups(int, int *);
#else
extern int getgroups(int, gid_t *);
#endif /* _BSD_COMPAT */
extern char *getlogin(void);
#if defined(_BSD_COMPAT)
extern int getpgrp(int);
#else
extern pid_t getpgrp(void);
#endif
extern pid_t getpid(void);
extern pid_t getppid(void);
extern uid_t getuid(void);
extern int isatty(int);
extern int link(const char *, const char *);
extern off_t lseek(int, off_t, int);
extern long pathconf(const char *, int);
extern int pause(void);
extern int pipe(int *);
extern ssize_t read(int, void *, size_t);
extern int rename(const char *, const char *);
extern int rmdir(const char *);
extern int setgid(gid_t);
extern int setpgid(pid_t, pid_t);
extern pid_t setsid(void);
extern int setuid(uid_t);
extern unsigned sleep(unsigned);
extern long sysconf(int);
extern pid_t tcgetpgrp(int);
extern int tcsetpgrp(int, pid_t);
extern char *ttyname(int);
extern int unlink(const char *);
extern ssize_t write(int, const void *, size_t);

/*
 * All SGI specific and non POSIX/XOPEN/SVR4 orphaned calls go here
 */
#if defined(_SGI_SOURCE) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)
#include <utime.h>	/* 4.0 compatibility */
extern int BSDchown(const char *, uid_t, gid_t);
extern int BSDdup2(int, int);
extern int BSDfchown(int, uid_t, gid_t);
extern int BSDsetpgrp(int, int);
extern int BSDsetgroups(int, int *);
extern int BSDgetgroups(int, int *);
#ifndef _ABI_SOURCE
extern void bset(char *, bitnum_t);
extern void bclr(char *, bitnum_t);
extern int btst(char *, bitnum_t);
extern void bfset(char *, bitnum_t, bitlen_t);
extern void bfclr(char *, bitnum_t, bitlen_t);
extern bitlen_t bftstset(char *, bitnum_t, bitlen_t);
extern bitlen_t bftstclr(char *, bitnum_t, bitlen_t);
#endif /* _ABI_SOURCE */
extern int _daemonize(int, int, int, int);
extern int ftruncate64(int, off64_t);
extern int getdtablesize(void);
extern int getdtablehi(void);
extern int getdomainname(char *, int);
extern long gethostid(void);
extern int gethostname(char *, int);
extern int getpagesize(void);
extern char *_getpty(int *, int, mode_t, int);
extern char *getwd(char *);
extern off64_t lseek64(int, off64_t, int);
extern int mpin(void *, size_t);
extern int munpin(void *, size_t);
extern pid_t pcreatel(const char *, const char *, ...);
extern pid_t pcreatelp(const char *, const char *, ...);
extern pid_t pcreatev(const char *, char *const *);
extern pid_t pcreateve(const char *, char *const *, char *const *);
extern pid_t pcreatevp(const char *, char *const *);
extern int setdomainname(const char *, int);
extern int sethostid(long);
extern int sethostname(const char *, int);
extern int setregid(gid_t, gid_t);
extern int setreuid(uid_t, uid_t);
extern int sgikopt(const char *, char *, int);
extern int sginap(long);
extern int truncate64(const char *, off64_t);
#endif 	/* _SGI_SOURCE && !_POSIX_SOURCE && !_XOPEN_SOURCE */

/*
 * Extensions for threads
 */
#if (defined(_SGI_SOURCE) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)) || defined(_SGI_REENTRANT_FUNCTIONS)

extern char *getlogin_r(char *, int);
#endif

#endif /* _LANGUAGE_C  _LANGUAGE_C_PLUS_PLUS  _LANGUAGE_ASSEMBLY */

#ifdef __cplusplus
}
#endif
#endif /* !__UNISTD_H__ */
