#ifndef _PROF_PROFILE_H_
#define _PROF_PROFILE_H_
/*
 *  New PROF data file format.
 *
 *    This new profiler data format is defined for both PC-sampling and BB-counts.
 *    It should be able to handle:
 *
 *     0.  32-bit non-shared, 32-bit DSOs, and 64-bit DSOs.
 *     1.  flexible # of DSOs with single/multiple text segments.
 *     2.  variable 32/64 bit BB-counts.
 *     3.  variable 16/32 bit PC-samples.
 *     4.  variable sampling interval.
 *     5.  recording of dso pathnames,
 *         so that prof & pixstats can duplicate the searching later.
 *     6.  recording of CPU and FPU type in order to determine the
 *         appropriate timing table for analysis later.
 *     7.  recording of processes forked in a MP environment.
 *     8.  recording of the version of performance tools used.
 */

/*  NOTES:
 *    - all sizes are in bytes.
 *    - the data structure has two interpretations:
 *      1.  runtime (pointers contain addresses of malloc-ed buffers,
 *      2.  file layout (pointers contain file offset).
 *    - magic number & versions are stored in a char array, so that it
 *      is not dependent on the endians.
 *    - Prof_Union_Addr is a union type -- containing 32bit addr, 64bit addr, and file offset.
 */

/*  TO DO:
 *    - upgrade pixie_data_ptr in /usr/include/task.h to 64-bit.
 */

/************************************************************************
    EXPLANATIONS
************************************************************************

Image in memory:

    PROF_DATA_PTR points to the Prof header.
    Prof header points to an array of Segment headers.
    Each segment header holds a pointer to the data buffer.
    
    Variables of type Prof_Union_Addr holds addresses when the structure is
    in memory.  Type Prof_Str is equivalent to (char *).
    
File layout:

    Variable of type ProfAddr holds offset from the beginning of file.
    Type Prof_Str is a offset from the beginning of the string section.
    PROF header always start at offset 0.
    Other sections starts at any 16-byte aligned address.
    
    ----------------------------
    |      PROF HEADER         |
    |--------------------------|
    |    Segment header 1      |
    |    Segment header 2      |
    |    ...                   |
    |    Segment header n      |
    |--------------------------|
    |    Process section       |
    |--------------------------|
    |    String section        |
    |--------------------------|
    |    buffer 1              |
    |--------------------------|
    |    buffer 2              |
    |--------------------------|
    |    ...                   |
    |--------------------------|
    |    buffer n              |
    ----------------------------

Shared/Non-shared support:

    For shared programs, each segment in a DSO has an entry 
    in the segment header table.
    
    Non-shared programs are treated like shared program with only
    one DSO segment.

Dlopen/Dlclose support:
    
    When a DSO is closed, its corresponding segment headers
    are marked inactive and the data buffers are unchanged.
    
    The first time a DSO is mapped in or dlopen-ed,
    we extend the segment table to include the new segments
    and create new data buffers.

    Other times, the segment headers already exist, we just
    change the status of relevant segments to active.
    
MP support:

    A multiprocessed program is a tree of processes executing in 
    parallel.  The group_pid field in the prof header identifies
    the root process.  The child array in the prof header maintains
    the pid of the child processes.  By recursively traversing the
    child array starting from the root process, all processes 
    in this run can be identified.


************************************************************************/

#define PI_NIDENT                16

/* 
    Index to Prof_Hdr.ident.

    The PI_BUGFIX byte and the last 8 bytes of
    the Prof_Hdr.ident are currently unused.
*/
#define PI_MAG0		0
#define PI_MAG1		1
#define PI_MAG2		2
#define PI_MAG3		3
#define PI_TOOL		4    /* pixie or libprof */
#define PI_MAJOR	5    /* major version number of compiler source tree */
#define PI_MINOR	6    /* minor version number of the source tree */
#define PI_BUGFIX	7    /* number of bugs fixed for the tool */
#define PI_FORMAT	8    /* the version number of the file format */


/* 
    The first 4 bytes of Prof_Hdr.ident, i.e. PI_MAG0, PI_MAG1, PI_MAG2, 
    and PI_MAG3 should contain one of the following 4-byte words.
*/
#define BBADDRS_MAGIC 		0x0f0e0010    /* this is still the old magic */
#define PROF_MAGIC          	0x0f0e0030    /* new PROF file MAGIC number */
#define NEW_BBCOUNTS_MAGIC	0x0f0e0031    /* new PIXIE file MAGIC number */
#define CACHE_MISS_MAGIC	0x0f0e0032    /* magic number for miss file */
#define USERPC_MAGIC		0xfee1c001    /* USERPC file MAGIC number */

/*
    The PI_TOOL byte of Prof_Hdr.ident should contain 
    one of the following values to distinguish whether
    the tool that generated the file was pixie or prof.
*/
#define PROF_TOOL_PIXIE         1
#define PROF_TOOL_LIBPROF       2
#define PROF_TOOL_USERPC        8

#define IS_PIXIE(phdr) 		(phdr->ident[PI_TOOL] == PROF_TOOL_PIXIE)
#define IS_LIBPROF(phdr)  	(phdr->ident[PI_TOOL] == PROF_TOOL_LIBPROF)
#define IS_USERPC(phdr)		(phdr->ident[PI_TOOL] == PROF_TOOL_USERPC)


/*
    For now, the PI_MAJOR and PI_MINOR bytes of Prof_Hdr.ident
    should contain the following values respectively, to indicate
    that the compiler used is v4.0.
*/
#define PROF_MAJOR              4    /* version 4.0 */
#define PROF_MINOR              1

/* The PI_FORMAT byte of Prof_Hdr.ident should contain this value. */
#define PROF_FORMAT		2
#define PROF_FORMAT_OLD		1

#define PROF_PCSAMPLE           1
#define PROF_BBCOUNTS           2
#define PROF_BBCOUNTS_BRANCH    4
#define PROF_SHARED             8
#define PROF_NONSHARED          16            

#define PROF_int16               2     /* old monitor format */
#define PROF_int32               4     /* new monitor format, old bbcounts */
#define PROF_int64               8     /* new bbcounts */
#define PROF_countsize		 PROF_int16
#define PIXIE_countsize		 PROF_int32

#define PROF_BIGENDIAN           1     /* Big endian */
#define PROF_LITTLEENDIAN        2     /* Little endian */


/* PROF address field */
typedef union {
    struct Prof_Shdr 	*shdr;
    struct Prof_Hdr  	*phdr;
    char         	*cptr;
    __uint32_t		*uptr;
    struct prof		*prptr;
    Elf32_Addr   	addr32;
    Elf64_Addr   	addr64;       /* 64-bit or 32-bit address in memory */
    Elf32_Off    	offset;       /* 64-bit file offset */
} Prof_Union_Addr;


/* PROF string pointer */
typedef union {
    char         *cptr;
    Elf32_Addr   addr32;
    Elf64_Addr   addr64;	/* (char *) pointer */
    Elf32_Off    offset;	/* offset from the string table */
} Prof_Str;                     /* The string type for the prof header */


/* PROF header */
/*
    All the fields have been extended to 64-bits
    to avoid any alignment-related padding.
*/
typedef struct Prof_Hdr {
    char      		ident[PI_NIDENT];        /* magic number & versions */
    __uint64_t 		flags;                   /* shared, non-shared */
    __uint64_t		countsize;               /* size of each count unit */
    Prof_Union_Addr 	text_segment;            /* text segment offset */
    __uint64_t		text_segment_num;        /* number of segments.
                                       		    It is always 1 for a 
						    non_shared program */
    Prof_Union_Addr 	strtab;                  /* string table offset */
    __uint64_t		sample_interval;         /* in microseconds, 
						    if PC-sampling,
						    in nanoseconds in 
						    -nocounts pc-sampling */
    __uint64_t		endian;                  /* what endian mode */
    __uint64_t		cpu;                     /* CPU type at runtime */
    __uint64_t		fpu;                     /* floating point 
						    coprocessor type */
    __uint64_t		n_cpus;                  /* number of CPUs */
    __uint64_t		clock;                   /* CPU clock rate in Hertz */
    Prof_Str  		prog_name;               /* name of this program, 
						    i.e., argv[0] */
    __uint64_t		this_pid;                /* pid of this thread */
    __uint64_t		group_pid;               /* pid of the ancestor 
						    processor */
    __uint64_t		n_child;                 /* number of children */
    Prof_Union_Addr 	child_arr;               /* table of pids of second 
						    generation children */
    __uint64_t		etext;                   /* for compatible with 
						    old prof */
    __uint64_t		eprol;
    
		/* 
		 * additional variables used 
		 * by libprof at runtime 
		 */
    __uint64_t		child_arr_size;          /* number of bytes allocated 
						    for child_arr_off */
    Prof_Union_Addr 	prof_arr;                /* sprof structure */
    __uint64_t		n_prof;                  /* size of prof structure 
						    in memory */
    __uint64_t		use_pid;                 /* process-id to be printed 
						    if non-zero */
    __uint64_t		use_phase_id;            /* phase-id to be printed 
						    if non-zero */
} Prof_Hdr;


/* Text Segment Header (for both PC-sampling and BB-Counting) */
/*
    All the fields have been extended to 64-bits
    to avoid any alignment-related padding.
*/
typedef struct Prof_Shdr {
    Prof_Str  		path_name;	/* The complete path name */
    Prof_Str  		dso_name;	/* DSO name offset into string table */
    Prof_Union_Addr 	text;		/* beginning text address */
    __uint64_t		size;		/* Size of text segment in bytes */
    Prof_Union_Addr 	buf;		/* Counts buffer offset */
    __uint64_t		bufsize;	/* Size of Counts buffer (in bytes) */
    __uint64_t		buffer_type;	/* PC-sampling or BB-counting */
    __uint64_t		scale;		/* Text to buffer scaling,  
					   0x10000 == 1-1 mapping */
    __uint64_t		gprof_data;	/* Offset to gprof data area */
    __uint64_t		shdr_idx;	/* Index of this shdr */
    __uint64_t		checksum;	/* Checksum of the text segment */
    Prof_Union_Addr	phdr;		/* Point back to parent */
    __uint64_t		active;		/* Is this segment currently opened.
					    (pixie: delta of rld relocation) */
    __uint64_t		gprof_size;	/* Size in bytes of gprof data area */
} Prof_Shdr;

typedef struct {
    Prof_Union_Addr buf;
    __uint64_t      bufsize;                      /* The size of buffer */
    __uint64_t	    used;                         /* How many filled */
} Prof_Strtab;

#endif /* ifndef _PROF_PROFILE_H_ */
