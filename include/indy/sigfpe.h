/**************************************************************************
 *                                                                        *
 * Copyright (C) 1989-1993 Silicon Graphics, Inc.                         *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/
#ifndef __SIGFPE_H__
#define __SIGFPE_H__

#ifdef __cplusplus
extern "C" {
#endif
/*

	sigfpe.h - constants and data areas for the floating-point exception-
	handling package when C is the native language. 

	The MIPS floating-point accelerator may raise floating-point exceptions
	due to five conditions:
	_OVERFL (overflow), _UNDERFL (underflow), _DIVZERO (divide-by-zero),
	_INEXACT (inexact result), or _INVALID (invalid operand, e.g. infinity). 
	Usually these conditions are masked and do not cause a floating-point
	exception; instead, a default value is substituted for the result of
	the operation and the program continues silently.  This event may be
	intercepted by causing an exception to be raised.  Once an exception
	is raised, the specific conditions which caused the exception may be 
	determined, and more appropriate action taken.  This package provides a
	mechanism for 'handling' such exceptions, classifying them by the 
	conditions which caused them, and substituting a value, either a default
	value or one supplied by the user.  This package also includes mechanisms
	useful in debugging code that causes traps : stack trace, trap counts, 
	abort and exit functions.  This package is provided for all of the above
	conditions except _INEXACT.  Two options exist to initiate trap handling:
	the programmable interface, and the environment variable (runtime)
	interface.

        *********************************************************************
       The Runtime interface:

       Link time switch -lfpe:
	In order to acquire the trap handler runtime interface, link the program
	with the switch -lfpe.   Traps will then be handled according to the
        runtime environment variable TRAP_FPE.

      TRAP_FPE:
	This runtime environment variable specifies how the enabled trap handler
	shall behave.   If TRAP_FPE is undefined, the program will execute with
	sgi defaults (as found in the default values of sigfpe(3f) : 
	array sigfpe_[].repls).  To execute user routine as if it was not compiled
	-lfpe, use TRAP_FPE=OFF

      Syntax:

	The string "TRAP_FPE" will be checked as an environment variable, in
	upper case letters only.  The string defining the actions of the trap 
	handler can be in either upper case, or lower case for the user's 
	convenience.

	The TRAP_FPE variable can take one of two forms:  either a "global"
	value, or a list of individual items.  The two forms cannot be combined.
	The global form is given by:

	setenv TRAP_FPE global_value

	where global_value takes on one of the following values:

		"" or OFF
					Execute the program with no trap handling 
					enabled.  Same as linking WITHOUT -lfpe.
					Same as TRAP_FPE undefined.
		ON
					Same as TRAP_FPE="ALL=DEFAULT".

	Alternately, replacement values and actions may be specified for
	each of the possible trap types individually. This is accomplished by:

	setenv TRAP_FPE  "item;item;item...."

					TRAP_FPE is set to a list of items. 
					The length of this is limited by csh.

		an item can be one of the following:

			traptype=statuslist
					where traptype defines the specific
					floating point exception to enable,
					and statuslist defines the list of
					actions upon encountering the trap.
			DEBUG
					confirm the parsing of the environment
					variable and the trap settings.


		trap type can be one of the following literal strings:

			UNDERFL
					underflow
			OVERFL
					overflow
			DIVZERO
					divide by zero	
			INVALID
					invalid operand
			ALL
					all of the above

		statuslist is a list separated by commas.  It contains an 
		optional symbolic replacement value and an optional list of
		actions.

		replacement values:

			DEFAULT
					Use the predefined SGI default
					(from fsigfpe(3f), sigfpe_[].repls)
					as the return result, and continue
					execution.  If no other replacement
					value is specified, this is the
					default.
			
			APPROPRIATE
					Use IEEE standard results as the 
					return result for _OVERFL, _DIVZERO,
					and _INVALID exceptions.  Use _ZERO
					for _UNDERFL exceptions.
			ZERO		
					substitute _ZERO as the return result.
			MIN
					substitute _MIN as the return result.
			MAX
					substitute _MIN as the return result.
			INF		
					substitute _INF as the return result.
			NAN
					substitute _NAN as the return result.
			FLUSH_ZERO	
					set the flush to zero bit in the 
					Control Status Register.  Causes
					flush to zero without invoking the
					trap handler.  Works only for under-
					flow on the R4000 and later processors.
					Works like ZERO for the R3000.
				
		actions:

			COUNT(n)
					A count of the trap type will be 
					printed to stderr at the end of 
					execution of the program, and every
					nth trap. 
			
		these actions take an optional integer in parentheses

			ABORT(n)
					Core dump and abort program upon 
					encountering the nth trap, default 
					is 1.
			EXIT(n)
					Exit program without coredump upon 
					encountering the nth trap, default 
					is 1.
			TRACE(n)
					If trap is encountered, print a 
					stack trace to stderr. Print this
					stack trace up to n times.  Default
					is 10.

       Example:

		setenv TRAP_FPE "ALL=COUNT;UNDERFLOW=ZERO;OVERFLOW=APPROPRIATE,
		TRACE(5),ABORT(100); DIVZERO=ABORT"

	count all traps, print final results (even on abort) to stderr,
	underflow to zero, overflow to IEEE, trace first five overflows, if
	100 overflows occur then abort, abort on first zero divide.

        *********************************************************************
	The programmable interface:
	Control is initiated (and canceled) by calling the function 
	handle_sigfpes.  The function takes four arguments:

		handle_sigfpes(onoff, en_mask, user_routine,
			abort_action, abort_routine)

		   onoff - a flag indicating whether handling is 
			being turned on (onoff == _ON) or 
			debug (onoff = _DEBUG)
			off (onoff != _ON && onoff != _DEBUG)
	
		   The remaining parameters are only valid 
		   if onoff == _ON or _DEBUG.

		   en_mask - indicates which of the four conditions should
			raise a floating-point exception.  This parameter
			is only valid if onoff == _ON or _DEBUG, and is the 
			bit-or of _EN_UNDERFL, _EN_OVERFL, _EN_DIVZERO, and
			_EN_INVALID

		   user_routine - The address of a user's routine which
			is called to set the value.  This routine is called
			if the replacement value code for the condition-at-hand
			is _USER_DETERMINED (see below). It
			is invoked with the following parameters:

			user_routine(exception, val);
			unsigned exception[5];
			int val[2];

			The exception array contains useful information
			concerning the exception.  Its elements are
			_EXCEPTION_TYPE (0), _INVALID_ACTION (1),
			_INVALID_TYPE (2), _VALUE_TYPE (3), _VALUE_SIGN (4):
	
			_EXCEPTION_TYPE : _OVERFL, _UNDERFL, etc.

			_INVALID_ACTION : _SET_RESULT if result is being set;
					_REPL_OPERAND if operand is being 
					replaced

			_INVALID_TYPE: if exception_type is _INVALID, this
					indicates the type of _INVALID
					exception which occurred: 
					_CVTW_OVERFL, _ZERO_TIMES_INF, etc.

			_VALUE_TYPE: _SINGLE, _DOUBLE, or _WORD

			_VALUE_SIGN: The suggested sign for the value, 
				based on an analysis of the instruction:
				_NEGATIVE or _POSITIVE

			val: an array in which the modified value should
				be placed.  If an operand is being replaced,
				val has a copy of the current operand.
	
		   abort_action - If the handler encounters an unexpected 
			condition, an inconsistency, or begins looping, 
			this flag indicates what action should be taken.  The 
			possible values are:
	
				_TURN_OFF_HANDLER_ON_ERROR - instruct the 
					floating-point-accelerator to cease
					causing exceptions and continue.
					(i.e., disable handling)

				_ABORT_ON_ERROR - kill the process after 
					giving an error message and possibly 
					calling a user-supplied cleanup routine.

				_REPLACE_HANDLER_ON_ERROR - install the 
					indicated user routine as the handler
					when such an error is encountered.
					Future floating-point exceptions will
					branch to the user-routine. 
					(see signal(2))

				_USER_HANDLER - install the indicated user 
					routine as the handler.  (see signal(2))
	
		    abort_routine - When a fatal error (i.e., one described
			under 'abort_action' above) is encountered, this
			argument is used as the address of a user routine.  
			If abort_action is _ABORT_ON_ERROR, and this argument
			is non-zero, it is used as the address of a routine
			to call before aborting.  The routine is invoked
			with a single argument - the pc of the exception.
			If abort_action is _REPLACE_HANDLER_ON_ERROR, or
			_USER_HANDLER, and abort_routine is non-zero, it 
			will be installed as the floating point exception
			handler.  In the former case, the instruction which
			caused the unexpected exception will be re-executed, 
			causing a new exception, and abort_routine entered.
			(see signal(2)).  If abort_action is _ABORT_ON_ERROR,
			then abort_routine is invoked with the following
			parameter:

			abort_routine( pc_ptr )
			unsigned int **pc_ptr;

			Thus, *pc_ptr is the program counter of the instruction
			which caused the exception (*pc_ptr + 4, if the
			instruction is in a branch delay slot), and **pc_ptr
			(or *(*pc_ptr + 4)) is the instruction.

			If abort_action is _REPLACE_HANDLER_ON_ERROR or
			_USER_HANDLER (i.e. abort_routine is actually a
			floating point exception handler), then abort_routine
			is invoked with the following parameters:
			int abort_routine( sig, code, sc )
			int sig, code;
			struct sigcontext *sc;

			In the preceding case, the abort_routine, i.e. the
			user's floating point exception handler, should
			return 0 to continue normal processing and a non-
			zero value to turn off floating point exception
			handling.  Abort_routine should not issue a call
			to signal(), because this is done in the routine
			which calls it.




	
*/

#define _ON  1
#define _OFF  0
#define _DEBUG 2
	
typedef void (*user_t)(unsigned[5], int[2]);
typedef void (*abort_t)(unsigned int **);

#define _TURN_OFF_HANDLER_ON_ERROR  1
#define _ABORT_ON_ERROR  0
#define _REPLACE_HANDLER_ON_ERROR  2
#define _USER_HANDLER	3
	
 /* 	exceptions 	*/

#define _UNDERFL  1
#define _OVERFL   2
#define _DIVZERO  3
#define _INVALID  4
#define	_INT_OVERFL	5
#define _N_EXCEPTION_TYPES  5
#define _NO_EXCEPTION_TYPE -1
#define _ALL_EXCEPTION_TYPES 0


	
#define _EN_UNDERFL  2
#define _EN_OVERFL   4
#define _EN_DIVZERO  8
#define _EN_INVALID  16
#define _EN_INT_OVERFL 32

 /* types */

#define _SINGLE  0
#define _DOUBLE  1
#define _WORD     2
#define _LONGWORD 3
#define _FIRST_TYPE  _SINGLE
#define _LAST_TYPE  _LONGWORD

 /* signs */

#define _POSITIVE  0
#define _NEGATIVE  1
	
 /* actions  */

#define _SET_RESULT  0
#define	_REPL_OPERAND 1
#define _REPL_RS  1
#define _REPL_RT  2

 /* elements of exception array */

#define _EXCEPTION_TYPE  0
#define _INVALID_ACTION  1
#define _INVALID_TYPE    2
#define _VALUE_TYPE      3
#define _VALUE_SIGN      4

	
/*
	When an exception is encountered, the handler examines the instruction
	causing the exception and the state of the floating-point accelerator
	to determine the correct action to take, and the program is continued.
	In most cases of floating-point exceptions, e.g.  _UNDERFL, _OVERFL, 
	_DIVZERO, and some instances of _INVALID, an appropriate value is 
	substituted for the result of the operation, and the instruction 
	which caused the exception is skipped.  For most exceptions arising 
	due to an invalid operand (_INVALID exceptions), more meaningful 
	behavior may be obtained by replacing an erroneous operand.  In this
	case, the operand is replaced, and the instruction re-issued.
	
	For exceptions which always warrant the setting of the result, the
	value used is determined by the exception type (_UNDERFL, _OVERFL,
	or _DIVZERO).

	These may be overridden by initializing a global array of structures
        named 'sigfpe_'.  A declaration for this array of structures is below.  
	
	Each element in the sigfpe_[].repls is interpreted as an integer code
	used to select one of a set of replacement values, or the code 
	_USER_DETERMINED, which indicates that the user's routine should be 
	invoked to provide the replacement value.  If the code is not 
	_USER_DETERMINED, the appropriately-typed (single- or double- precision)
	and appropriately-signed replacement value is then substituted in the 
	operation causing the exception.  The integer codes, and the corresponding
	replacement values they select, are listed below:

		_ZERO 	- use zero as the replacement value.

		_MIN  	- use the appropriately-typed minimum value as 
			  the replacement. (i.e., the smallest number
			  which is representable in that format)

		_MAX  	- use the appropriately-typed maximum value as 
			  the replacement.

		_INF  	- use the appropriately-typed value for infinity 
			  as the replacement.

		_NAN  	- use the appropriately-typed value for not-a-number 
			  as the replacement.

		_APPROPRIATE- use a handler-supplied appropriate value 
			  as the replacement.  These are _ZERO for _UNDERFL,
			  and values which will produce the IEEE result the
			  instruction would have produced if it had not been
			  trapped.

		_USER_DETERMINED - call the user's routine to set the value.

		_NEG    - use the negative of the original argument (valid
			  only for cases _SQRT_NEG_X and _RSQRT_NEG_X (see
			  below)

		_FLUSH_ZERO 	
			- set the flush to zero bit in the Control Status
			  Register.  Causes flush to zero without invoking
			  the trap handler.  Works only for underflow traps
			  on the R4000 and later processors.  Works like 
			  ZERO for the R3000.
				

	
	If the replacement-value code for _INVALID exceptions is _USER_DETERMINED,
	the replacement value for all _INVALID exceptions will be obtained from 
	the user_routine.  Otherwise, the code for _INVALID is ignored, as this 
	exception has cases which warrant the replacement of an operand as well
	as cases which warrant the setting of the result (see below).
	
	
	The elements of this array are interpreted as follows:

		sigfpe_[0] is ignored.
		sigfpe_[1] is the structure for _UNDERFL
		sigfpe_[2] is the structure for _OVERFL
		sigfpe_[3] is the structure for _DIVZERO
		sigfpe_[4] is the structure for _INVALID -

	Each structure contains the following:

		struct sigfpe_template
			{
			int repls;	The replacement value
			int count;	The count limit
			int trace;	The trace limit
			int abort;	The abort limit
			int exit ;	The exit limit
			};

	Each limit defines the number of traps that will be executed
	before the defined action occurs:

	count : print a count of all traps that have count enabled.
	trace : print a dbx stack trace.
	abort : abort with a core dump.
	exit  : exit program, no core dump.

	
	If no sigfpe_ structure is initialized no count, trace, exit or
        abort actions will be performed. The default values for
	sigfpe_[].repls are used as if the following initialization 
	had been performed:
	 
		int sigfpe_[_N_EXCEPTION_TYPES+1].repls = {
		0, _ZERO, _APPROPRIATE, _APPROPRIATE, 0 };

	Thus replacement values for _INVALID floating point exceptions
	are by default obtained from the tables invalidop_results_
	and invalidop_operands_.
	
*/
	
 /* the possible replacement values: _ZERO=0, _MIN=minimum valid number, etc. */

#define _ZERO		  1
#define _MIN		  2
#define _MAX		  3
#define _INF		  4
#define _NAN		  5
#define _FLUSH_ZERO	  6
#define _APPROPRIATE	  7
#define _USER_DETERMINED  8
#define _NEG		  9

#define _MIN_REPL	  _ZERO
#define _MAX_REPL	  _NEG
#define _DEFAULT_REPL_VAL 0
#define _NO_REPL_VAL	  0



struct sigfpe_template
	{
	int repls;
	int count;
	int trace;
	int abort;
	int exit ;
	};

extern struct sigfpe_template sigfpe_[_N_EXCEPTION_TYPES+1];

/*
	For _INVALID exceptions, the correct action may be either to
	set the result and skip the instruction, or to replace an
	operand and retry the instruction.  

	There are four cases in which the result is set.  The array
	named 'invalidop_results_' is consulted for user-initialized
	codes for these cases.  A declaration for invalidop_results_
	is below.  Each element governs the following cases:
	
	---index---
	#  mnemonic			exception condition
	--------------------------------------------------------------
	0  (none)			(ignored)
	1  _MAGNITUDE_INF_SUBTRACTION   subtraction of infinities: 
	2  _ZERO_TIMES_INF	        multiplication 0 * infinity
	3  _ZERO_DIV_ZERO	        0/0
	4  _INF_DIV_INF		        infinity / infinity

	The default value in the array is _APPROPRIATE, which causes
	the result used to be _NAN.
	
*/
	
 /* invalid ops for which the result is set  */

#define _MAGNITUDE_INF_SUBTRACTION	1
#define _ZERO_TIMES_INF			2
#define _ZERO_DIV_ZERO			3
#define _INF_DIV_INF			4

#if (_MIPS_SIM == _ABIO32)

#define _N_INVALIDOP_RESULTS		4

#else

#define _N_INVALIDOP_RESULTS		12

#endif

extern int invalidop_results_[_N_INVALIDOP_RESULTS+1];

	
/*

	There are ten cases in which an offending operand is replaced.  
	An array named 'invalidop_operands_' is consulted for 
	user-initialized codes for these cases.  A declaration for 
	invalidop_operands_ is below.  Notice that the size of array
	invalidop_operands_ is larger for mips3 and later architectures.
	Only in those cases are entries 8-11 present.

	Each element governs the following cases:

	---index---
	#  mnemonic		exception condition
	--------------------------------------------------------------
	0  (none)	    (ignored)
	1  _SQRT_NEG_X 	    sqrt(-x)
	2  (unused)
	3  _CVTW_OVERFL     conversion to integer caused target to overflow
	4  _CVTW_NAN	    conversion of NaN to integer
	5  _CVTW_INF	    conversion of infinity to integer
	6  _UNORDERED_CMP   comparison to NaN
	7  _SNAN_OP	    operand was Signaling Nan
	8  _CVTL_OVERFL     conversion to long long caused target to overflow
	9  _CVTL_NAN	    conversion of NaN to long long
	10 _CVTL_INF	    conversion of infinity to long long
	11 _RSQRT_NEG_X	    reciprocal sqrt(-x)
	
	Default values for this array are:  _APPROPRIATE, which causes
	the instruction to be re-executed with the same operands and
	floating point traps disabled.
*/
	
 /* invalid ops for which the offending operand is replaced  */

#define _SQRT_NEG_X     	  1
#define _CVT_OVERFL		  2 /* not supported */
#define _TRUNK_OVERFL     	  3 /* obsolete; see next entry */
#define _CVTW_OVERFL     	  3 /* new name */
#define _CVT_NAN		  4 /* obsolete; see next entry */
#define _CVTW_NAN		  4 /* new name */
#define _CVT_INF		  5 /* obsolete; see next entry */
#define _CVTW_INF		  5 /* new name */
#define _UNORDERED_CMP	 	  6
#define _SNAN_OP		  7

/* the table ends here for mips1 and mips2 architectures */

#if (_MIPS_SIM == _ABIO32)
#define _N_INVALIDOP_OPERANDS     7
#else
#define _CVTL_OVERFL     	  8 /* new entry */
#define _CVTL_NAN		  9 /* new entry */
#define _CVTL_INF		 10 /* new entry */
#define _RSQRT_NEG_X		 11 /* new entry */
#define _N_INVALIDOP_OPERANDS    19
#endif

	

extern int invalidop_operands_[_N_INVALIDOP_OPERANDS+1];

	
/*
	Once handle_sigfpes has been called, the values for the
	various conditions are set.  Subsequent assignments to these
	arrays will have no effect, unless handling is suspended
	and resumed.
*/

extern void	handle_sigfpes( int, int, void (*) (unsigned [5], int [2]),
				int, void (*) (unsigned int **) );

#ifdef __cplusplus
}
#endif

#endif

