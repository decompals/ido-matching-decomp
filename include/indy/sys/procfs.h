/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1984, 1986, 1987, 1988, 1989, 1990 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/**************************************************************************
 *									  *
 * 		 Copyright (C) 1990, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

#ifndef _FS_PROCFS_PROCFS_H	/* wrapper symbol for kernel use */
#define _FS_PROCFS_PROCFS_H	/* subject to change without notice */

#ident	"$Revision: 1.41 $"

#include <sys/fault.h>
#include <sys/siginfo.h>
#include <sys/signal.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/ucontext.h>

/*
 * ioctl codes and system call interfaces for /proc.
 */
#define PIOC		('q'<<8)
#define PIOCSTATUS	(PIOC|1)	/* get process status */
#define PIOCSTOP	(PIOC|2)	/* post STOP request and... */
#define PIOCWSTOP	(PIOC|3)	/* wait for process to STOP */
#define PIOCRUN		(PIOC|4)	/* make process runnable */
#define PIOCGTRACE	(PIOC|5)	/* get traced signal set */
#define PIOCSTRACE	(PIOC|6)	/* set traced signal set */
#define PIOCSSIG	(PIOC|7)	/* set current signal */
#define PIOCKILL	(PIOC|8)	/* send signal */
#define PIOCUNKILL	(PIOC|9)	/* delete a signal */
#define PIOCGHOLD	(PIOC|10)	/* get held signal set */
#define PIOCSHOLD	(PIOC|11)	/* set held signal set */
#define PIOCMAXSIG	(PIOC|12)	/* get max signal number */
#define PIOCACTION	(PIOC|13)	/* get signal action structs */
#define PIOCGFAULT	(PIOC|14)	/* get traced fault set */
#define PIOCSFAULT	(PIOC|15)	/* set traced fault set */
#define PIOCCFAULT	(PIOC|16)	/* clear current fault */
#define PIOCGENTRY	(PIOC|17)	/* get syscall entry set */
#define PIOCSENTRY	(PIOC|18)	/* set syscall entry set */
#define PIOCGEXIT	(PIOC|19)	/* get syscall exit set */
#define PIOCSEXIT	(PIOC|20)	/* set syscall exit set */
/*
 * These four are obsolete (replaced by PIOCSET/PIOCRESET)
 */
#define PIOCSFORK	(PIOC|21)	/* set inherit-on-fork flag */
#define PIOCRFORK	(PIOC|22)	/* reset inherit-on-fork flag */
#define PIOCSRLC	(PIOC|23)	/* set run-on-last-close flag */
#define PIOCRRLC	(PIOC|24)	/* reset run-on-last-close flag */

#define PIOCGREG	(PIOC|25)	/* get general registers */
#define PIOCSREG	(PIOC|26)	/* set general registers */
#define PIOCGFPREG	(PIOC|27)	/* get floating-point registers */
#define PIOCSFPREG	(PIOC|28)	/* set floating-point registers */
#define PIOCNICE	(PIOC|29)	/* set nice priority */
#define PIOCPSINFO	(PIOC|30)	/* get ps(1) information */
#define PIOCNMAP	(PIOC|31)	/* get number of memory mappings */
#define PIOCMAP		(PIOC|32)	/* get memory map information */
#define PIOCOPENM	(PIOC|33)	/* open mapped object for reading */
#define PIOCCRED	(PIOC|34)	/* get process credentials */
#define PIOCGROUPS	(PIOC|35)	/* get supplementary groups */
#define PIOCGETPR	(PIOC|36)	/* read struct proc */
#define PIOCGETU	(PIOC|37)	/* read user area */
/*
 * These are new with SVR4
 */
#define PIOCSET		(PIOC|38)	/* set modes of operation */
#define PIOCRESET	(PIOC|39)	/* reset modes of operation */
#define PIOCNWATCH	(PIOC|40)	/* get # watch points */
#define PIOCGWATCH	(PIOC|41)	/* get watch point */
#define PIOCSWATCH	(PIOC|42)	/* set watch point */
#define PIOCUSAGE	(PIOC|43)	/* get prusage_t structure */

/* SGI calls */
#ifdef _VM_WS_SWAPPING
#define PIOCWSINFO_SGI	(PIOC|247)	/* (SGI) get working set info. */
#endif
#define PIOCPGD_SGI	(PIOC|248)	/* (SGI) get page tbl information */
#define PIOCMAP_SGI	(PIOC|249)	/* (SGI) get region map information */
#if !STAT_TIME
#define PIOCGETPTIMER	(PIOC|250)	/* get process timers */
#endif

#define PIOC_IRIX5_64	(1<<16)

#define PRSYSARGS	6		/* max number of syscall arguments */

typedef struct prstatus {
	ulong_t		pr_flags;	/* Process flags */
	short		pr_why;		/* Reason for process stop */
	short		pr_what;	/* More detailed reason */
	short		pr_cursig;	/* Current signal */
	sigset_t	pr_sigpend;	/* Set of pending signals */
	sigset_t	pr_sighold;	/* Set of held signals */
	struct siginfo	pr_info;	/* info assoc. with signal or fault */
	struct sigaltstack pr_altstack;	/* Alternate signal stack info */
	sigaction_t	pr_action;	/* Signal action for current signal */
	long		pr_syscall;	/* syscall number (if in syscall) */
	long		pr_nsysarg;	/* number of arguments to syscall */
	long		pr_errno;	/* error number from system call */
	long		pr_rval1;	/* syscall return value 1 */
	long		pr_rval2;	/* syscall return value 2 */
	long		pr_sysarg[PRSYSARGS];	/* syscall arguments */
	pid_t		pr_pid;		/* Process id */
	pid_t		pr_ppid;	/* Parent process id */
	pid_t		pr_pgrp;	/* Process group id */
	pid_t		pr_sid;		/* Session id */
	timestruc_t	pr_utime;	/* Process user cpu time */
	timestruc_t	pr_stime;	/* Process system cpu time */
	timestruc_t	pr_cutime;	/* Sum of children's user times */
	timestruc_t	pr_cstime;	/* Sum of children's system times */
	char		pr_clname[8];	/* Scheduling class name */
	long		pr_filler[20];	/* Filler area for future expansion */
	inst_t		pr_instr;	/* Current instruction */
	gregset_t	pr_reg;		/* General registers */
} prstatus_t;
  

/* values for pr_flags */
#define PR_STOPPED	0x0001	/* process is stopped */
#define PR_ISTOP	0x0002	/* process is stopped on event of interest */
#define PR_DSTOP	0x0004	/* process has stop directive in effect */
#define PR_ASLEEP	0x0008	/* process is in an interruptible sleep */
#define PR_FORK		0x0010	/* process has inherit-on-fork flag set. */
#define PR_RLC		0x0020	/* process has run-on-last-close flag set. */
#define PR_PTRACE	0x0040	/* process is traced with ptrace() too */
#define PR_PCINVAL	0x0080	/* current pc is invalid */
#define PR_ISSYS	0x0100	/* process is a system process */
#define PR_STEP		0x0200	/* process has single step pending */
#define PR_KLC		0x0400	/* process has kill-on-last-close flag set. */

/* values for pr_why */
#define PR_REQUESTED	1	/* in the interest of binary compatibility, */
#define PR_SIGNALLED	2	/* PR_REQUESTED thru PR_SYSEXIT match the   */
#define PR_SYSENTRY	3	/* prior settings from proc.h               */
#define PR_SYSEXIT	4
#define PR_FAULTED	5
#define PR_JOBCONTROL	6

typedef struct prrun {
	ulong_t		pr_flags;	/* Flags */
	sigset_t	pr_trace;	/* Set of signals to be traced */
	sigset_t	pr_sighold;	/* Set of signals to be held */
	fltset_t	pr_fault;	/* Set of faults to be traced */
	caddr_t		pr_vaddr;	/* Virt. address at which to resume */
	long		pr_filler[8];	/* Filler area for future expansion */
} prrun_t ;

/* values for pr_flags */
#define PRCSIG		0x0001	/* Clear current signal */
#define PRCFAULT	0x0002	/* Clear current fault */
#define PRSTRACE	0x0004	/* set traced signals from pr_trace */
#define PRSHOLD		0x0008	/* set held signals from pr_sighold */
#define PRSFAULT	0x0010	/* set fault tracing mask from pr_trace */
#define PRSVADDR	0x0020	/* set PC on resumption from pr_vaddr */
#define PRSTEP		0x0040	/* single step the process */
#define PRSABORT	0x0080	/* abort current system call */
#define PRSTOP		0x0100	/* stop as soon as possible */
#define PRCSTEP		0x0200	/* cancel outstanding single step */

#ifdef _KERNEL
#define KPRIFORK	0x0001	/* inherit-on-fork */
#define KPRRLC		0x0002	/* run-on-last-close */
#define KPRCLRHALT	0x0004	/* clear current halt reason */
#define KPRSUIDEXEC	0x0008	/* internal flag for secure setuid exec() */
#define KPRKLC		0x0020	/* kill-on-last-close */
#endif

#define PRNODEV		(dev_t)(-1)     /* non-existent device */
#define PRARGSZ		80		/* should match PSARGSZ in user.h */
#define PRCOMSIZ	32		/* should match PSCOMSIZ in user.h */

typedef struct prpsinfo {
	char	pr_state;	/* numeric process state */
	char	pr_sname;	/* printable character representing pr_state */
	char	pr_zomb;	/* !=0: process exited but not waited for */
	char	pr_nice;	/* process priority */
	ulong_t	pr_flag;	/* process flags */
	uid_t	pr_uid;		/* real user id */
	gid_t	pr_gid;		/* real group id */
	pid_t	pr_pid;		/* process id */
	pid_t	pr_ppid;	/* parent process id */
	pid_t	pr_pgrp;	/* pid of process group leader */
	pid_t	pr_sid;		/* session id */
	caddr_t	pr_addr;	/* physical address of process */
	long	pr_size;	/* process image size in pages */
	long	pr_rssize;	/* resident set size in pages */
	caddr_t	pr_wchan;	/* wait addr for sleeping process */
	timestruc_t	pr_start;	/* process start time */
	timestruc_t	pr_time;	/* usr+sys cpu time for this process */
	long	pr_pri;		/* priority */
	long	pr_oldpri;	/* pre-svr4 priority */
	char	pr_cpu;		/* pre-svr4 cpu usage */
	dev_t	pr_ttydev;	/* controlling tty */
	char	pr_clname[8];	/* scheduling class name */
	char	pr_fname[PRCOMSIZ];	/* basename of exec()'d pathname */
	char	pr_psargs[PRARGSZ];	/* initial chars of arg list */
	uint_t	pr_pset;	/* associated processor set name */
	cpuid_t	pr_sonproc;	/* processor running on */
	timestruc_t     pr_ctime;       /* usr+sys cpu time for all children */
	long	pr_fill[17];	/* spares */
} prpsinfo_t;

#ifdef _VM_WS_SWAPPING
typedef struct pr_commonwsinfo {
	time_t	pr_ws_slice_limit;	/* working set slice time 	*/
					/* limit (future lbolt value)	*/
	time_t	pr_ws_active_time; 	/* last time process was	*/
	unchar	pr_ws_pri;		/* working set priority */
	unchar	pr_ws_upri;		/* working set priority */
	ushort_t pr_ws_flags;		/* working set state flags   */
	long	pr_filler[6];		/* spares */
} pr_commonwsinfo_t;

typedef struct prwsinfo {
	pr_commonwsinfo_t	pr_priv;
	pr_commonwsinfo_t	pr_shrd;
} prwsinfo_t;
#endif /* _VM_WS_SWAPPING */

typedef struct prmap {
	caddr_t	pr_vaddr;	/* Virtual base address */
	ulong_t	pr_size;	/* Size of mapping in bytes */
	__scoff_t	pr_off;	/* Offset into mapped object, if any */
	ulong_t	pr_mflags;	/* Protection and attribute flags */
	long	pr_fill[4];	/* spares */
} prmap_t;

typedef struct prmap_sgi {
	caddr_t	pr_vaddr;	/* Virtual base address */
	ulong_t	pr_size;	/* Size of mapping in bytes */
	__scoff_t	pr_off;	/* Offset into mapped object, if any */
	ulong_t	pr_mflags;	/* Protection and attribute flags */
				/* non PYHS type region information... */
	pgno_t	pr_vsize;	/* # of valid pages in this region */
	pgno_t	pr_psize;	/* # of private pages in this region */
	pgno_t	pr_wsize;	/* # of pages in region weighted base 256 */
	pgno_t	pr_rsize;	/* # of referenced pages in this region */
	pgno_t	pr_msize;	/* # of modified pages in this region */
	dev_t	pr_dev;		/* Device # of region iff mapped */
	ino_t	pr_ino;		/* Inode # of region iff mapped */
	long	pr_fill[5];	/* spares */
} prmap_sgi_t;

typedef struct prmap_sgi_arg {
	caddr_t	pr_vaddr;	/* Virtual pointer to base of map buffer */
	ulong_t	pr_size;	/* Size of user's map buffer in bytes */
} prmap_sgi_arg_t;

/* flag values in pr_mflags */
#define MA_READ		0x0001	/* mapping has readable permission */
#define MA_WRITE	0x0002	/* mapping has writable permission */
#define MA_EXEC		0x0004	/* mapping has executable permission */
#define MA_SHARED	0x0008	/* mapping is a shared or mapped object */
#define MA_BREAK	0x0010	/* mapping is grown by brk(2) */
#define MA_STACK	0x0020	/* mapping is grown on stack faults */
#define MA_PHYS		0x0040	/* mapping is a physical device */
/* flag values added for prmap_sgi */
#define	MA_PRIMARY	0x0800	/* mapping is part of primary object */
#define MA_SREGION	0x1000	/* mapping is on shared region list */
#define MA_COW		0x2000	/* mapping is set to copy on write */
#define	MA_NOTCACHED	0x4000	/* mapping is not cacheable by process */
#define MA_SHMEM	0x8000	/* mapping is a shmem() memory region */
#define	MA_REFCNT_SHIFT	    16	/* shift for region reference count */
/* fractional base for pr_wsize */
#define	MA_WSIZE_FRAC	   256	/* base for pr_wsize */

/* WARNING: pgd_t is the same size for both 32 bit and 64 bit
 * programs, do not break this assumption.
 */
typedef struct pgd {		/* per-page data */
	short pr_flags;		/* flags */
	short pr_value;		/* page use count /or/ vfault page offset */
} pgd_t;
typedef struct prpgd_sgi {
	caddr_t	pr_vaddr;	/* virtual base address of region to stat */
	pgno_t	pr_pglen;	/* number of pages in data list... */
	pgd_t	pr_data[1];	/* variable length array of page flags */
} prpgd_sgi_t;

/* flag values in prpgd_sgi pr_data.pr_flags */
#define	PGF_REFERENCED	0x0001	/* page is hardware valid in region */
#define	PGF_GLOBAL	0x0002	/* page is hardware global in region */
#define	PGF_WRITEABLE	0x0004	/* page is hardware writeable in region */
#define	PGF_NOTCACHED	0x0008	/* page is not hardware cached in region */
#define	PGF_ISVALID	0x0010	/* page is valid */
#define	PGF_ISDIRTY	0x0020	/* page is dirty */
#define PGF_PRIVATE	0x0040	/* page is private (reference count == 1) */
#define PGF_FAULT	0x0080	/* page fault offset stored pr_value */
#define	PGF_SWAPPED	0x0100	/* page has been swapped in the past */
#define	PGF_USRHISTORY	0x0800	/* history flag reserved for the caller */
#define PGF_REFHISTORY	0x1000	/* has page ever been marked hrdwr valid? */
#define PGF_WRTHISTORY	0x2000	/* has page ever been marked hrdwr dirty? */
#define PGF_VALHISTORY	0x4000	/* has page ever been marked softw valid? */
#define PGF_CLEAR	0x8000	/* clear hardware REF/WRT for this page */
#define	PGF_NONHIST	0xF800	/* mask to clear per call flags */

/* WARNING: prcred_t is the same size for both 32 bit and 64 bit
 * programs, do not break this assumption.
 */
/* credentials structure */
typedef struct prcred {
	uid_t	pr_euid;	/* Effective user id */
	uid_t	pr_ruid;	/* Real user id */
	uid_t	pr_suid;	/* Saved user id (from exec) */
	gid_t	pr_egid;	/* Effective group id */
	gid_t	pr_rgid;	/* Real group id */
	gid_t	pr_sgid;	/* Saved group id */
	uint_t	pr_ngroups;	/* number of supplementary groups */
} prcred_t;

/* watchpoints structure */
typedef struct prwatch {
	caddr_t pr_vaddr;
	ulong_t	pr_size;
	ulong_t	pr_wflags;
	long	pr_filler;
} prwatch_t;

/* prusage structure */
typedef struct prusage {
	timestruc_t pu_tstamp;	/* time stamp */ 
	timestruc_t pu_starttime;	/* time process was started */ 
	timestruc_t pu_utime;	/* user CPU time */ 
	timestruc_t pu_stime;	/* system CPU time */ 
	ulong_t pu_minf;	/* minor (mapping) page faults */
	ulong_t pu_majf;	/* major (disk) page faults */
	ulong_t pu_utlb;	/* User TLB misses - always zero */
	ulong_t pu_nswap;	/* swaps (process only) */
	ulong_t pu_gbread;	/* gigabytes ... */ 
	ulong_t pu_bread;	/* and bytes read */
	ulong_t pu_gbwrit;	/* gigabytes ... */ 
	ulong_t pu_bwrit;	/* and bytes written */
	ulong_t pu_sigs;	/* signals received */
	ulong_t pu_vctx;	/* voluntary context switches */
	ulong_t pu_ictx;	/* involuntary context switches */
	ulong_t pu_sysc;	/* system calls */ 
	ulong_t pu_syscr;	/* read() system calls */ 
	ulong_t pu_syscw;	/* write() system calls */ 
	ulong_t pu_syscps;	/* poll() or select() system calls */
	ulong_t pu_sysci;	/* ioctl() system calls */ 
	ulong_t pu_graphfifo;	/* graphics pipeline stalls */
	ulong_t pu_graph_req[8];	/* graphics resource requests */
	ulong_t pu_graph_wait[8];/* graphics resource waits */
	ulong_t pu_size;	/* size of swappable image in pages */
	ulong_t pu_rss;		/* resident set size */
	ulong_t pu_inblock;	/* block input operations */
	ulong_t pu_oublock;	/* block output operations */
	ulong_t pu_vfault;	/* total number of vfaults */
	ulong_t pu_unused[1];	/* currently unused */
} prusage_t; 

/* values for pr_wflags - see MA_* */

/*
 * Macros for manipulating sets of flags.
 * sp must be a pointer to one of sigset_t, fltset_t, or sysset_t.
 * flag must be a member of the enumeration corresponding to *sp.
 */

/* turn on all flags in set */
#define prfillset(sp) \
	{ register int _i_ = sizeof(*(sp))/sizeof(__uint32_t); \
		while(_i_) ((__uint32_t*)(sp))[--_i_] = 0xFFFFFFFF; }

/* turn off all flags in set */
#define premptyset(sp) \
	{ register int _i_ = sizeof(*(sp))/sizeof(__uint32_t); \
		while(_i_) ((__uint32_t*)(sp))[--_i_] = 0L; }

/* is this set empty? */
#define prisemptyset(set) \
	(setisempty(set, sizeof(*(set))/sizeof(__uint32_t)))

/* turn on specified flag in set */
#define praddset(sp, flag) \
	(((unsigned)((flag)-1) < 32*sizeof(*(sp))/sizeof(__uint32_t)) \
	&& (((__uint32_t*)(sp))[((flag)-1)/32] |= (1L<<(((flag)-1)%32))))

/* turn off specified flag in set */
#define prdelset(sp, flag) \
	(((unsigned)((flag)-1) < 32*sizeof(*(sp))/sizeof(__uint32_t)) \
	&& (((__uint32_t*)(sp))[((flag)-1)/32] &= ~(1L<<(((flag)-1)%32))))

/* query: != 0 iff flag is turned on in set */
#define prismember(sp, flag) \
	(((unsigned)((flag)-1) < 32*sizeof(*(sp))/sizeof(__uint32_t)) \
	&& (((__uint32_t*)(sp))[((flag)-1)/32] & (1L<<(((flag)-1)%32))))


#endif	/* _FS_PROCFS_PROCFS_H */
