/*     @(#)fioflags.h	  */
/*  $Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/include/cmplrs/RCS/fioflags.h,v 1.4 1993/11/05 23:10:18 dlai Exp $ */

/*
**      This header defines all the external flags that can be set
**      when using the Fortran I/O library with a C main program.
**      To set a particular flag the set the appropriate array element:
**
**		Fortran I/O Operation   f77 Option    f77vms_flag_
**		---------------------   ------------  ------------
**		VMS Carriage Control    -vms_cc	      VMS_CC
**		Allow rereading stdin   -vms_stdin    VMS_IN
**		Write VMS endfile	-vms_endfile  VMS_EF
**		Byte Record Length	-bytereclen   OLD_RL
**		Byte Record Length	-old_rl       OLD_RL
**
**	To set the appropriate I/O flag, the corresponding array element of
**	f77vms_flag_ must be set to 1.  For example, in order to use the
**	VMS carrage control interpretation on unit 6, you have to add the
**	statement:
**
**      	f77vms_flag_[VMS_CC] = 1;
**
**      to the C main program before Fortran I/O is done.
*/


#define VMS_FLAGS	4

#define VMS_CC  0
#define OLD_RL	1
#define VMS_IN  2
#define VMS_EF  3

extern unsigned short f77vms_flag_[VMS_FLAGS];
