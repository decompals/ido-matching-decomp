/****************************************************************/
/*	Copyright (c) 1987, Silicon Graphics, Inc.        	*/
/*			All Rights Reserved			*/
/****************************************************************/

/* --------------------------------------------------- */
/* | Copyright (c) 1986 MIPS Computer Systems, Inc.  | */
/* | All Rights Reserved.                            | */
/* --------------------------------------------------- */
/* $Revision: 7.5 $ */
#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))

/* Sort of like System V's bsearch, but not quite. "key" is a structure,
  "the_array" is an array of such structures, "elem_size" is the size in
  bytes of one element of the array, and "num_elems" is the number of
  elements in the array. Returns pointer to the element which matches
  "key", or pointer to the element which "key" ought to precede.
  Assumes array is already sorted. Both "prof" and "as1" need this. */
char *
psearch(char *key, char *the_array, int num_elems, int elem_size,
  int (*cmp)());
#endif
