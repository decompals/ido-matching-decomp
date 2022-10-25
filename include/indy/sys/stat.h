/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef _SYS_STAT_H
#define _SYS_STAT_H
#ident	"$Revision: 3.34 $"

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/time.h>

#define _ST_FSTYPSZ 16		/* array size for file system type name */

/*
 * stat structure, used by stat(2) and fstat(2)
 */

struct	stat {
	dev_t	st_dev;
	long	st_pad1[3];	/* reserved for network id */
	ino_t	st_ino;
	mode_t	st_mode;
	nlink_t st_nlink;
	uid_t 	st_uid;
	gid_t 	st_gid;
	dev_t	st_rdev;
	long	st_pad2[2];	/* dev and off_t expansion */
	off_t	st_size;
	long	st_pad3;	/* future off_t expansion */
	timestruc_t st_atim;	
	timestruc_t st_mtim;	
	timestruc_t st_ctim;	
	long	st_blksize;
	long	st_blocks;
	char	st_fstype[_ST_FSTYPSZ];
	long	st_pad4[8];	/* expansion area */
};


#if defined(_SGI_SOURCE) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)
/*
 * Stat structure used by stat64(2), fstat64(2), and lstat64(2).
 */
struct	stat64 {
	dev_t	st_dev;
	long	st_pad1[3];	/* reserved for network id */
	ino64_t	st_ino;
	mode_t	st_mode;
	nlink_t st_nlink;
	uid_t 	st_uid;
	gid_t 	st_gid;
	dev_t	st_rdev;
	long	st_pad2[2];	/* dev and off_t expansion */
	off64_t	st_size;
	long	st_pad3;	/* future off_t expansion */
	timestruc_t st_atim;	
	timestruc_t st_mtim;	
	timestruc_t st_ctim;	
	long	st_blksize;
	long long	st_blocks;
	char	st_fstype[_ST_FSTYPSZ];
	long	st_pad4[8];	/* expansion area */
};
#endif

#define st_atime	st_atim.tv_sec
#define st_mtime	st_mtim.tv_sec
#define st_ctime	st_ctim.tv_sec

/* MODE MASKS */

/* de facto standard definitions */

#define	S_IFMT		0xF000	/* type of file */
#define S_IAMB		0x1FF	/* access mode bits */
#define	S_IFIFO		0x1000	/* fifo */
#define	S_IFCHR		0x2000	/* character special */
#define	S_IFDIR		0x4000	/* directory */
#define	S_IFNAM		0x5000  /* XENIX special named file */
#define		S_INSEM 0x1	/* XENIX semaphore subtype of IFNAM */
#define		S_INSHD 0x2	/* XENIX shared data subtype of IFNAM */

#define	S_IFBLK		0x6000	/* block special */
#define	S_IFREG		0x8000	/* regular */
#define	S_IFLNK		0xA000	/* symbolic link */
#define	S_IFSOCK	0xC000	/* socket */

#define	S_ISUID		0x800	/* set user id on execution */
#define	S_ISGID		0x400	/* set group id on execution */

#define	S_ISVTX		0x200	/* save swapped text even after use */

#define	S_IREAD		00400	/* read permission, owner */
#define	S_IWRITE	00200	/* write permission, owner */
#define	S_IEXEC		00100	/* execute/search permission, owner */
#define	S_ENFMT		S_ISGID	/* record locking enforcement flag */

/* the following macros are for POSIX conformance */

#define	S_IRWXU	00700		/* read, write, execute: owner */
#define	S_IRUSR	00400		/* read permission: owner */
#define	S_IWUSR	00200		/* write permission: owner */
#define	S_IXUSR	00100		/* execute permission: owner */
#define	S_IRWXG	00070		/* read, write, execute: group */
#define	S_IRGRP	00040		/* read permission: group */
#define	S_IWGRP	00020		/* write permission: group */
#define	S_IXGRP	00010		/* execute permission: group */
#define	S_IRWXO	00007		/* read, write, execute: other */
#define	S_IROTH	00004		/* read permission: other */
#define	S_IWOTH	00002		/* write permission: other */
#define	S_IXOTH	00001		/* execute permission: other */


#define S_ISFIFO(mode)	((mode&S_IFMT) == S_IFIFO)
#define S_ISCHR(mode)	((mode&S_IFMT) == S_IFCHR)
#define S_ISDIR(mode)	((mode&S_IFMT) == S_IFDIR)
#define S_ISBLK(mode)	((mode&S_IFMT) == S_IFBLK)
#define S_ISREG(mode)	((mode&S_IFMT) == S_IFREG) 
#define S_ISLNK(m)      (((m) & S_IFMT) == S_IFLNK)
#define S_ISSOCK(m)     (((m) & S_IFMT) == S_IFSOCK)


/* a version number is included in the SVR4 stat and mknod interfaces. */

#define _R3_MKNOD_VER 1		/* SVR3.0 mknod */
#define _MKNOD_VER 2		/* current version of mknod */
#define _R3_STAT_VER 1		/* SVR3.0 stat */
#define _STAT_VER 2		/* current version of stat */
#define	_STAT64_VER 3		/* [lf]stat64 system calls */	

#if !defined(_KERNEL)
#if defined(_MODERN_C)

int _fxstat(const int, int, struct stat *);
int _xstat(const int, const char *, struct stat *);
#if !defined(_POSIX_SOURCE) 
int _lxstat(const int, const char *, struct stat *);
int _xmknod(const int, const char *, mode_t, dev_t);
int fchmod(int, mode_t);
#endif /* !defined(_POSIX_SOURCE) */
extern int chmod(const char *, mode_t);
extern int mkdir(const char *, mode_t);
extern int mkfifo(const char *, mode_t);
extern mode_t umask(mode_t);

#if defined(_ABI_SOURCE)

static int fstat(int, struct stat *);
static int stat(const char *, struct stat *);
#if !defined(_POSIX_SOURCE) 
static int lstat(const char *, struct stat *);
static int mknod(const char *, mode_t, dev_t);
#endif /* !defined(_POSIX_SOURCE) */
/*
 * NOTE: Application software should NOT program
 * to the _xstat interface.
 */

static int
stat(const char *path, struct stat *buf)
{
int ret;
        ret = _xstat(_STAT_VER, path, buf);
        return ret;
}
static int
fstat(int fd, struct stat *buf)
{
int ret;
        ret = _fxstat(_STAT_VER, fd, buf);
        return ret;
}

#if !defined(_POSIX_SOURCE)
static int
lstat(const char *path, struct stat *buf)
{
int ret;
        ret = _lxstat(_STAT_VER, path, buf);
        return ret;
}

static int
mknod(const char *path, mode_t mode, dev_t dev)
{
int ret;
        ret = _xmknod(_MKNOD_VER, path, mode, dev);
        return ret;
}
#endif /* !defined(_POSIX_SOURCE) */

#else /* _ABI_SOURCE */

int fstat(int, struct stat *);
int stat(const char *, struct stat *);
#if !defined(_POSIX_SOURCE) 
int lstat(const char *, struct stat *);
int mknod(const char *, mode_t, dev_t);

#if defined(_SGI_SOURCE) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)
int fstat64(int, struct stat64 *);
int lstat64(const char *, struct stat64 *);
int stat64(const char *, struct stat64 *);
#endif

#endif /* !defined(POSIX_SOURCE) */

#endif /* _ABI_SOURCE */

#else	/* !_MODERN_C */

extern int fstat(), stat();
extern int mknod(), lstat();

extern int _fxstat(), _xstat();
extern int _xmknod(), _lxstat();
extern int chmod();
extern int mkdir();
extern int mkfifo();
extern mode_t umask();

#if defined(_SGI_SOURCE) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)
extern int fstat64(), lstat64(), stat64();
#endif

#endif /* defined(_MODERN_C) */
#endif /* !defined(_KERNEL) */

#if defined(_KERNEL)
#include "sys/kstat.h"
#endif

#ifdef __cplusplus
}
#endif

#endif	/* _SYS_STAT_H */
