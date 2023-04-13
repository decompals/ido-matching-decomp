#ifndef _KMEM_H
#define _KMEM_H
#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (C) 1989 Silicon Graphics, Inc. All rights reserved.  */
/*
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991, 1990 MIPS Computer Systems, Inc.      |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 252.227-7013.  |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Avenue                               |
 * |         Sunnyvale, California 94088-3650, USA             |
 * |-----------------------------------------------------------|
 */
/* $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/RCS/kmem.h,v 1.15 1996/02/07 22:54:24 davea Exp $ */

/*
	This header file contains basic definitions and declarations
	for libkmem. 

	libkmem and this header reserve names starting with
	Kmem kmem and KMEM for their own use.
	Over time more such names may be used.
*/

typedef	int 			Kmem_int;
typedef	unsigned int 		Kmem_uint;
#if (_MIPS_SZLONG == 64)
typedef long                  Kmem_int64;
typedef unsigned long         Kmem_uint64;
#else /* 32-bit */
typedef long long             Kmem_int64;
typedef unsigned long long    Kmem_uint64;
#endif


/* Return values used by some functions */
enum kmem_return_type_e {
	KMEM_OK,
	KMEM_NO_REGION, /* KMEM_NO_REGION used internally by 
			   libkmem, not returned outside 
			   libkmem. Reserved for libkmem. */
	KMEM_CHANGED,
	KMEM_ERR
};

typedef struct _kmem kmem_t;

typedef Kmem_uint64 *pcb_regset;

kmem_t *kmem_open(
	const char*/* executable */, 
	const char*/* corefile */, 
	const char*/* swapfile */,
	Kmem_int   /* flag, O_RDONLY, O_RDWR */,
	const char*/* errstr, appended to error messages */
	);

Kmem_int kmem_setpid(
	kmem_t*	   /* kernel */,
	pid_t	   /* pid to set to */
	);

Kmem_int kmem_getpid(kmem_t * /*kernel*/);
Kmem_uint64 kmem_getprocaddr(kmem_t * /*kernel*/);

/* 
   Note: Callback functions returning negative numbers are 
	 treated as errors
*/

/*
   Call back function 1: Given symbol name, return address

   Function should return -1 in case of error.

*/
typedef Kmem_int (*kmem_sym_addr_func) (
	void*	   /* app_ptr: pointer given to kmem_add_callbacks */,
	char*	   /* name of symbol */,
	Kmem_uint64*	/* address of symbol */
	);
/*
   Call back function 2: Given struct name, return length 
   Function should return -1 in case of error.
*/
typedef Kmem_int (*kmem_struct_len_func) (
	void*	   /* app_ptr: pointer given to kmem_add_callbacks */,
	char*	   /* name of struct */,
	Kmem_int*  /* length of struct */
	);

/*
   Call back function 3: Given struct name and member name, 
   return offset of member in struct 
   Function should return -1 in case of error.
*/
typedef Kmem_int (*kmem_member_offset_func) (
	void*	   /* app_ptr: pointer given to kmem_add_callbacks */,
	char*	   /* name of struct */,
	char*	   /* name of member */,
	Kmem_int*  /* offset of member */
	);

/*
   Call back function 4: Given struct name and member name, 
   return length of member in bits 
   Function should return -1 in case of error.
*/
typedef Kmem_int (*kmem_member_bitlen_func) (
	void*	   /* app_ptr: pointer given to kmem_add_callbacks */,
	char*	   /* name of struct */,
	char*	   /* name of member */,
	Kmem_int*  /* length of member in bits */
	);

/*
	Returns -1 in case of error.
*/
Kmem_int kmem_add_callbacks(
	kmem_t*		    	
		/* kernel */,
	void*	/*app_ptr: passed in to libkmem so it can pass back
		** thru function pointers. calling app determines its
		** use, not used by libkmem (except to pass back when
		** libkmem calls callback functions 
		*/,
	kmem_sym_addr_func  	
		/* sym_addr, given symbol, return address */,
	kmem_struct_len_func	
		/* struct_len, gives length of structure */,
	kmem_member_offset_func 
		/* member_offset, gives offset of struct member */,
	kmem_member_bitlen_func 
		/* member_bitlen, length of struct member in bits */
	);

/*
	Free allocated memory.
	Return -1 on error.
*/
Kmem_int kmem_close(kmem_t *);

/*
	Read from kernel memory.
	Returns -1 on error.
*/
Kmem_int64
kmem_read(
	kmem_t*		/* kernel */, 
	Kmem_uint64 	/* vaddr, virtual address */, 
	char*		/* buf, buffer for read */,
	Kmem_uint64 	/* nbytes, no. of bytes to be read */
	);

/*
	Write  to kernel memory.
	Returns -1 on error.
*/
Kmem_int64
kmem_write(
	kmem_t*		/* kernel */, 
	Kmem_uint64 	/* vaddr */, 
	char*		/* buf */, 
	Kmem_uint64 	/* nbytes */
	);

/*
	Read register data.
	Returns -1 on error.
*/
Kmem_int
kmem_getregs(
	kmem_t*		/* kernel */,
	pcb_regset*	/* register set */
	);

/*
	Return kumode.
	Returns -1 on error.
*/
Kmem_int
kmem_get_kumode( kmem_t* /* kernel */);
/*===============================================================*/
/*
	The following functions were added after the above first set.
	Not the different return value convention.
	The above have not as yet been changed to reflect this
	new convention.
	Jan 96
*/

/*
   Return KMEM_OK if can determine count and count is unchanged
        since the last call.
	Update region_count thru the pointer.
   Return KMEM_CHANGED if can determine count and
        the regions have changed since the last call.
        So this is the value returned on first call when
        there are loadable kernel module regions.
	Update region_count thru the pointer.
	The region_count could be zero!
   Return KMEM_ERR on error (do not update region_count thru the
	pointer).

   --------------------------------------------------------------
   This function actually reads from the kernel's data space to 
        get the list of loadable regions.

   This is the call to use to determine if the caller's list of
   regions is out of date. 
	kmem_get_loadable_region_n()
	kmem_get_loadable_region_symbol_count()
	kmem_get_loadable_region_symbol_n()
	kmem_get_region_number_given_name()
	kmem_get_end_text_address()
   simply use/return data established by kmem_has_regions and do not
   themselves cause reading from the kernel data.

*/
Kmem_int
kmem_has_regions(kmem_t * /*kernel*/,
	Kmem_int  *region_count /* returned */ );
	
/*

  Return KMEM_OK when call succeeds.
	Return the low_pc, size, and name thru the pointers.
  Returns KMEM_ERR otherwise (do not return anything thru the pointers).

*/
Kmem_int
kmem_get_loadable_region_n(kmem_t * /*kernel*/,
	Kmem_int  region_number, /* requested region. 
			0, up to #loadable module regions-1 */
	Kmem_uint64 *low_pc, /* returned low pc of loaded module */
	Kmem_uint64 *size,   /* returned size of loaded module */
	char * module_name,  /* buffer for returned name (should be
		full path of the loadable module) */
	Kmem_int name_buffer_length /* size of module_name buffer  in bytes*/
	);

/*
  Return KMEM_OK if had data for the given kmem_t and region
    and return the number of symbols thru the pointer.
  Return KMEM_ERR 0therwise (meaning in case of error/no such region).
    and do not return number_of_symbols thru the pointer.
*/
Kmem_int
kmem_get_loadable_region_symbol_count(kmem_t * /*kernel */,
	Kmem_int region_number, /* requested region.
                        0, up to #loadable module regions-1 */
	Kmem_int * number_of_symbols /* returned number of symbols
		in loadable module externals table */);

/*
  Return KMEM_OK if had data for the given kmem_t and region and symbol number.
	(return symbol_name sym_address thru the pointers).
  Return KMEM_ERR 0therwise (meaning in case of error/out of range,
	so no symbol_name or sym_address returned).
*/
Kmem_int
kmem_get_loadable_region_symbol_n(kmem_t * /*kernel */,
	Kmem_int region_number, /* requested region.
                        0, up to #loadable module regions-1 */
	Kmem_int number_of_symbol /* 0 to number_of_symbols-1 */,
	char ** symbol_name, /* pointer to symbol name string, returned */
	Kmem_uint64 *sym_address /* The returned
		global address of the named symbol */);

/*
	Return KMEM_OK if found region. Return region number thru ptr.
	Return KMEM_NO_REGION if failed to find region (no region number
		returned).
*/
Kmem_int
kmem_get_region_number_given_name(kmem_t * /*kernel*/,
		char *pathname, Kmem_int *region_num_ret);

/*
	Return KMEM_OK if it found a loadable kernel 
	 region with that number (and thus has an end address).
	 Return end address thru pointer.
	Return KMEM_ERR otherwise (no endaddr returned).
*/
Kmem_int
kmem_get_end_text_address(kmem_t * /*kernel */,Kmem_int region,Kmem_uint64 *endaddr);


#ifdef __cplusplus
}
#endif
#endif
