#ifndef __PROF_MON_H_
#define __PROF_MON_H_
#ifdef __cplusplus
extern "C" {
#endif
#ident "$Revision: 1.1 $"
/*
*
* Copyright 1992, Silicon Graphics, Inc.
* All Rights Reserved.
*
* This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
* the contents of this file may not be disclosed to third parties, copied or
* duplicated in any form, in whole or in part, without the prior written
* permission of Silicon Graphics, Inc.
*
* RESTRICTED RIGHTS LEGEND:
* Use, duplication or disclosure by the Government is subject to restrictions
* as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
* and Computer Software clause at DFARS 252.227-7013, and/or in similar or
* successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
* rights reserved under the Copyright Laws of the United States.
*/

/*==============================================================================
	mon.h 
 	#defines for PC sampling.
==============================================================================*/

#define PCS_WHOLE       0
#define PCS_MAIN        1
#define PCS_REGION      2

#define PCS_SUSPEND     0
#define PCS_RESUME      1
#define PCS_NEWPHASE    2
#define PCS_DONE        3
#define PCS_USEPIDS     4

#define PCS_GRAIN       1
#define MON_OUT	"mon.out"

#if defined(_MODERN_C)
extern int      monitor(int, int, int *(void), int *(void));
extern void      moncontrol(int);
#else
extern int      monitor();
extern void      moncontrol();
#endif

#ifdef __cplusplus
}
#endif
#endif /* ifndef __PROF_MON_H_ */
