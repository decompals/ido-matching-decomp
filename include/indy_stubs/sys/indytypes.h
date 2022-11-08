#ifndef INDYTYPES_H
#define INDYTYPES_H

/* POSIX Extensions */
typedef unsigned char   uchar_t;
typedef unsigned short  ushort_t;
typedef unsigned int    uint_t;
typedef unsigned long   ulong_t;

/* Primarily Kernel types */
typedef	char *		addr_t;		/* ?<core address> type */
typedef	char *		caddr_t;	/* ?<core address> type */
// typedef	long		daddr_t;	/* <disk address> type */
typedef	long		pgno_t;		/* virtual page number type */
typedef	__uint32_t	pfn_t;		/* physical page number type */
typedef	short		cnt_t;		/* ?<count> type */

// TODO: this macro is gcc specific
#if __WORDSIZE == 64
typedef __int64_t __scint_t;
typedef __uint64_t __scunsigned_t;
#else
typedef __int32_t __scint_t;
typedef __uint32_t __scunsigned_t;
#endif

typedef __scint_t	__scoff_t;	/* scaling off_t */

#endif
