#ifndef __MIPS_PERF_H__
#define __MIPS_PERF_H__

#if 0
	NEW PERFORMANCE TOOLS SECTIONS


The goal here is for pixie and cvinstr to produce the same
information and for both the case and compiler consuming
tools to be able to work on either.

The following definitions need to be accessable to a variety
of tools.

These sections are all of type SHT_MIPS_PIXIE.


	.MIPS.Perf_function	- function node table.
	.MIPS.Perf_weak_names	- weak function name table.
	.MIPS.Perf_call_graph	- static call graph.
	.MIPS.Perf_bb_offsets	- map of offsets to basic block and
				  branch count buckets in output file.
	.MIPS.Perf_argtrace	- function argument trace table.
	.MIPS.Perf_table	- description table for the above tables
				  and transformed executable settings.

Each section that uses a string table (.MIPS.Perf_strtab) will
refer to it by section table index in it's sh_link field. We can 
use existing string tables adding to them if we have a unique
string. .MIPS.Perf_strtab has the type SHT_STRTAB and is of the form
of any other ELF string table.

Each of the above sections are tables of fix sized structures and
the structure size will be described in the sh_entsize field and the
size of the table will be the section size. Number of entries = 
sh_size/sh_entsize. 

Each of the above sections have their names defined in <sys/elf.h>
    #define MIPS_PERF_FUNCTIONS	    ".MIPS.Perf_function"
    #define MIPS_PERF_WEAKNAMES	    ".MIPS.Perf_weak_names"
    #define MIPS_PERF_CALLGRAPH	    ".MIPS.Perf_call_graph"
    #define MIPS_PERF_BBOFFSETS	    ".MIPS.Perf_bb_offsets"
    #define MIPS_PERF_ARGTRACE	    ".MIPS.Perf_argtrace"
    #define MIPS_PERF_TABLE	    ".MIPS.Perf_table"


Elfdump must learn to dump them and the other sections that are
produced by the performance tools.

#endif

#if 0
	.MIPS.Perf_function	- function node table
#endif

typedef	struct	map_func_node {
	__uint32_t	mfn_funcname;	/* String table offset for function name. */
	__uint32_t	mfn_filename;	/* String table offset for source file name. */
	__int32_t	mfn_binoffset;	/* Addrs/Binmap table offset for function. */
					/* -3 for aggregate, the aggregate function  */
					/* includes the stubs. */
					/* -2 for excluded functions. */
				/*
				 * WARNING! The next 4 fields represent the lower
				 * 32 bits of a possible 64 bit field. To generate
				 * the full address add the upper 32 bits represented
				 * by PHT_BASE_ADDR value in .MIPS.Perf table.
				 */
	__uint32_t	mfn_oldpcst;	/* Original function start address. */
	__uint32_t	mfn_oldpcend;	/* Original function end address. */
	__uint32_t	mfn_newpcst;	/* Instrumented function start address. */
	__uint32_t	mfn_newpcend;	/* Instrumented function end address. */

	__uint32_t	mfn_nodetype;	/* Node (function) type: */
#define MFN_REGULAR	0x1		/* regular node (normal function), was 1 */
#define MFN_AGGREGATE	0x2		/* aggregate node (one per binary), was 2 */
#define MFN_EXCLUDED	0x4		/* excluded node (no counting in node), was -2 */
#define MFN_PROLOG_3	0x8		/* this function has a 3 instruction old abi gp prolog */
#define MFN_PROLOG_6	0x10		/* this function has a 6 instruction old abi gp prolog */
#define MFN_STATIC	0x20		/* this is a static function */

	__uint32_t	mfn_fcnindex;	/* Function index. */
} map_func_node_t;

#if 0
	.MIPS.Perf_weak_names	- weak function name table 
#endif

typedef	struct	map_weak {
	__uint32_t	mw_name;	/* Offset into string table for weak name. */
	__uint32_t	mw_index;	/* Function index of strong function. */
} map_weak_t;

#if 0
	.MIPS.Perf_call_graph	- static call graph table 
#endif


/* 
    This value in the gr_calleeidx indicates that the target of
    this call is unknown, and is considered a function pointer.
*/
#define FUNCTION_PTR_IDX	-1

/*
 *  These are for the bit map gr_callee_desc which describes
 *  the callee.
 */
#define GRAPH_NONE		0x0	/* no meaning */
#define GRAPH_EXT		0x1	/* calls external function */
#define GRAPH_WEAK		0x2	/* calls weak function name */
#define GRAPH_COND_CALL		0x4	/* conditional branch and link */
#define GRAPH_FUNC_PTR		0x8	/* function pointer with destination unkown */
#define GRAPH_LOC		0x10	/* calls function defined in this object */
#define GRAPH_STUB		0x20	/* calls rld for function defined in this object */

/*
 * The bits in the gr_callee_desc field have the following affect
 * on the gr_callee_index field:
 *  GRAPH_EXT	    content is an index into the perf string table.
 *  GRAPH_WEAK	    content is an index into the perf weak table.
 *  GRAPH_COND_CALL content is an index into the perf func map table.
 *  GRAPH_FUNC_PTR  content has no current meaning.
 *  GRAPH_LOC	    content is an index into the perf func map table.
 *  GRAPH_STUB	    content is an index into the perf string table.
 */

typedef struct  graphrec {
    __uint32_t	gr_calleridx;	/* Call site function index */
    __uint32_t	gr_calleraddr;	/* Call site lower 32 bit address */
    __uint32_t	gr_bin;		/* Call site bin number */
    __int32_t	gr_calleeidx;	/* Overloaded. See GRAPH_* descriptions above. */
    __uint32_t	gr_callee_desc;	/* Describes the gr_calleeidx. */
} graphrec_t;


#if 0
	.MIPS.Perf_bb_offsets	- map of runtime counting bins 

		This will follow the current pixie .Addrs section format
		with the following exceptions:

			Branch counts bins will be designated by -1 and not
			0.

			There will not be any header information at the beginning
			of the section. This will be a fixed sized table.

		Each bin with a non-negative content will represent a basic
		block counting bin address. The address will be the offset/4
		from PHT_TEXT_BASE_ADDR stored in the perf header.

		There will be one extra bin at the end of the section representing
		the basic block beyond the last real basic block. This is used to
		determine the size of the last basic block.

		Bins with negative numbers represent special counts. So far we only
		have one, branch counts, which is marked with -1. It's offset is
		the same as the last basic block bin.

			It is a direct representation of the array of
			text indexes for fast lookups.

		The consuming tool will now have to look up the function
		information in the .MIPS.Node section to determine if the
		invocation counts need to be taken from after a gp-prolog.
#endif


/* Indicates that the corresponding bin is a conditional branch count. */
#define BRANCH_COUNT_OFFSET	-1
#define FUNCTION_COUNT_OFFSET	-2

typedef struct  addrec {
        __int32_t        ar_pc;
} addrec_t;


#if 0
	.MIPS.Perf_table	- Description table for perfomance sections
	
#endif

typedef	struct	perf_header {
	__uint64_t ph_type;
	__uint64_t ph_value;
} perf_header_t;

#define PHT_NODE_VERSION	1	/* .MIPS.Node format version number */
#   define CUR_NODE_VERSION	0
#define PHT_GRAPH_VERSION      	2	/* .MIPS.Graph format version number */
#   define CUR_GRAPH_VERSION	1
#define PHT_COUNTS_VERSION     	3	/* .Counts file structure format version number */
#   define CUR_COUNTS_VERSION	0
#define PHT_BINMAP_VERSION	4	/* .MIPS.Perf_bb_offsets format version number */
#   define BINMAP_VERSION	0
#define PHT_WEAK_VERSION	5	/* .MIPS.Perf_weak_names format version number */
#   define CUR_WEAK_VERSION	0
#define PHT_GMAP_VERSION	6	/* internal gmap version number */
#   define CUR_GMAP_VERSION	0
#define PHT_GPROF_VERSION	7	/* gprof structure version number */
#   define CUR_GPROF_VERSION	0
#define PHT_IDTRACE_VERSION	8	/* idtrace structure version number */
#   define CUR_IDTRACE_VERSION	0
#define PHT_TEXT_RANGE		14	/* size (in bytes) of original text */
#define PHT_BASE_ADDR		15	/* upper 32 bits of 64-bit base address in the form */
					/* 0xXXXXXXXX00000000 where XXXXXXXX is the upper 32 */
					/* bit address. */

#define PHT_TEXT_BASE_ADDR	16	/* 64-bit starting original text address */
#define PHT_NUM_BBCOUNTS	17	/* number of basic block bins in .MIPS.Perf_bb_offsets */
#define PHT_NUM_BCCOUNTS	18	/* number of branch count bins in .MIPS.Perf_bb_offsets */
#define PHT_FCNPTR_CALL_NO	19	/* number of function pointer call sites */
#define PHT_TEXT_HASH		20	/* hash of text sections that matches that */
					/* matches the one in the .Counts file */
#define PHT_PIXIE_TIMESTAMP	21	/* compile time timestamp of pixie */
#define PHT_SUFFIX		22	/* offset into the perf string table for the */
					/* default suffix of the instrumented executable. */
#define PHT_FORTRAN_MAIN       	23	/* fortran MAIN__ kluge */
					/* The value field is the address of main */
#define PHT_TRANS_TEXT_RANGE	24	/* size (in bytes) of transformed text */
#define PHT_TRANS_TEXT_BASE_ADDR    25	/* 64-bit starting transformed text address */

#define PHT_FLAGS		40	/* bitmap of instrument time flags */
#	define	PFLAGS_BBCOUNTS		0x00000001	/* -bbcounts */
#	define	PFLAGS_PCSAMP		0x00000002	/* -pcsampling */
#	define	PFLAGS_BRANCHCOUNTS    	0x00000004	/* -branchcounts */
#	define	PFLAGS_FPCOUNTS		0x00000008	/* -fpcounts */
#	define	PFLAGS_64_BBCOUNTS     	0x00000010	/* 64 bb count bins */
#	define	PFLAGS_FCNCOUNTS	0x00000020	/* -fcncounts */
#	define	PFLAGS_IDTRACE		0x00000040	/* -idtrace */
#	define	PFLAGS_IDTRACE_EXT	0x00000080	/* -idtrace extended format */
#	define	PFLAGS_ARGTRACE		0x00000100	/* -idtrace extended format */

#define PHT_NODE_SIZE		51	/* map_func_node_t structure size */
#define PHT_GRAPH_SIZE      	52	/* graphrec_t structure size */
#define PHT_PHDR_SIZE     	53	/* .Counts Phdr structure size */
#define PHT_SHDR_SIZE     	54	/* .Counts Shdr structure size */
#define PHT_WEAK_SIZE		55	/* map_weak_t structure size */
#define PHT_GMAP_SIZE		56	/* internal gmap structure size */
#define PHT_LMAP_SIZE		57	/* internal lmap structure size */
#define PHT_GPROF_SIZE		58	/* gprof structure structure size */

#if 0
	.MIPS.Perf_argtrace	- function argument trace table.
#endif

typedef	struct	arg_trace {
	__uint64_t	at_funcaddr;	/* Address of fuction entry point. */
	__uint32_t	at_funcname;	/* String table offset for function name. */
	__uint32_t	at_argname;	/* String table offset for argument name. */
	__uint32_t	at_argtype;	/* Argument type (float, int, ...). */
					/* Types have been defined in symconst.h */
					/* (btFloat, btInt, ...) */
	__uint32_t	at_tracerange;	/* Trace minimum or maximum. */
	__uint32_t	at_traceindex;	/* Index into the argument trace. */
	__uint32_t	at_tracetype;	/* trace argument or return value. */
} arg_trace_t;

#define ARGTRACE_MIN	0
#define ARGTRACE_MAX	1
#define ARGTRACE_ARG	0
#define ARGTRACE_RET	1

/*
    This struct is used to convey information about function pointers.
*/
typedef	struct gprof_header {
    __uint64_t  gph_source_size; /* Size of the source address field, 4 now */
    __uint64_t  gph_target_size; /* Size of the target address field, 8 now */
    __uint64_t  gph_count_size;  /* Size of the count field, 8 now */
} gprof_header_t;


/*
    This structure size needs to be kept
    as a multiple of 8 bytes because the
    padding otherwise will change between
    32 and 64 bit programs.
*/
typedef	struct gprof_entry {
    __uint64_t  gpe_target;	/* normalized to static instrumented address */
    __uint64_t  gpe_count;
    __uint32_t  gpe_source;	/* index into instruction array */
    __uint32_t  gpe_object_id;	/* see p_shdr->indirect_hash */
} gprof_entry_t;

#endif /* __MIPS_PERF_H__ */
