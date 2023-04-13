
#ifndef _CMPLRS_LEB128_H
#define _CMPLRS_LEB128_H
/*

	LEB128.H

	reading and writing leb128 numbers.
	See the DWARF documentation for further information on leb numbers.
	No error indication is returned.

	The supplied buffer must be long enough to hold the leb number.
	For encode, 5 bytes is sufficient for 32 bit values and 10 bytes
	is sufficient for 64 bit values.

	The value returned is the number of bytes in the leb encoding.

	For improperly coded leb number (or one having more than
	the allowed number of leb digits with the most significant
	bit on in the input buffer) the
	leb buffer decode scan stops at 5 characters for 32 bit decodes 
	and stops at 10 characters for 64 bit decodes.  
	For such numbers the returned length will be 5  or 10 
	respectively, and no error indication is supplied.
	
	These routines are in libelfutil.a

*/
 


int _leb128_unsigned_encode64(__uint64_t /*number*/, char* /*buffer*/);
int _leb128_signed_encode64(__int64_t /*number*/, char* /*buffer*/);

int _leb128_unsigned_encode32(__uint32_t /*number*/, char* /*buffer*/);
int _leb128_signed_encode32(__int32_t /*number*/, char* /*buffer*/);

int _leb128_unsigned_decode64(char* /*data*/, __uint64_t* /*value*/);
int _leb128_signed_decode64(char* /*data*/, __int64_t* /*value*/);

int _leb128_unsigned_decode32(char* /*data*/, __uint32_t* /*value*/);
int _leb128_signed_decode32(char* /*data*/, __int32_t* /*value*/);

#endif
