/*

	EVENTS.H

*/
		/*
		 * This structure is used to gather
		 * information from an events section
		 * record. Since each record is variable
		 * length and is context dependent based
		 * on it's type, the fields for arg[1-3]
		 * are large.
		 * 
		 * It is not expected that this structure
		 * would be used in a table or linked list
		 * thus size is less of a concern.
		 */
typedef struct {
    __uint64_t	fevnt_arg1;	    /* first argument */
    __uint64_t	fevnt_pre_arg1;	    /* raw arg1 value */
    __uint64_t	fevnt_arg2;	    /* first argument */
    __uint64_t	fevnt_pre_arg2;	    /* raw arg1 value */
    __uint64_t	fevnt_arg3;	    /* first argument */
    __uint64_t	fevnt_pre_arg3;	    /* raw arg1 value */
    __uint64_t	fevnt_base;	    /* section base addr */
    __uint32_t	fevnt_type;	    /* record type */
    __uint32_t	fevnt_offset;	    /* accumulated offset */
    __uint32_t	fevnt_index;	    /* text section index */
} Full_Events;

	/*******************************************************/
	/*******************************************************/
		/*
		 * Get information from the events section record
		 * pointed to by p_event and return a pointer 
		 * to the next record.
		 */
char *event_get_next_rec(
	char *,			/* pointer into section */
	__uint32_t ,		/* current offset into text section */
	Full_Events *);		/* information from record */

	/*******************************************************/
	/*******************************************************/
		/*
		 * starting at the given point in the section
		 * pointed to by p_event, find the next events
		 * section record of the given type.
		 * 
		 * It is assumed that the current offset coming 
		 * into this routine will be stored in p_full.
		 * 
		 * Returns EK_NULL if type not found.
		 */
__uint32_t event_find_record(
	char *,			/* pointer into the events section */
	Full_Events *,		/* structure for events record info */
	__uint32_t, 		/* event section type */
	char *);		/* end of the current events section */

	/*******************************************************/
	/*******************************************************/
		/*
		 * Return the name of the the kind based on the
		 * kind number. If I don't reccognize the the kind
		 * return the hex string for the number.
		 * 
		 * The buffer for the string is statically allocated
		 * at compile time. If you want to manipulate the string
		 * or keep it around while making multiple calls to
		 * event_kind_string(), you need to copy it to another 
		 * buffer.
		 * 
		 */
char *event_kind_string(__uint32_t );

	/*******************************************************/
	/*******************************************************/
