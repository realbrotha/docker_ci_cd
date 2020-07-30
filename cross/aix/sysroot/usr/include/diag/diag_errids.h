/*
../../../../../src/bos/diag/diags/bos.diag.rte.err.S:
@(#)79	1.1.1.1  src/bos/diag/diags/bos.diag.rte.err.S, diagsup, bos53X, x2011_14A5 3/8/11 11:41:50
*/

/*
 * COMPONENT_NAME: CMDERRLG  system error logging facility
 *
 * FUNCTIONS:  header file for error ids
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989, 1990
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_DIAG_ERRIDS
#define _H_DIAG_ERRIDS

#include "sys/err_rec.h"


#define ERRID_DIAG_REPORT    0xd5cfa810 /* Diagnostics report */
#define ERRID_PERIODIC_DIAG  0xd07fee3e /* Periodic Diagnostics report */

#endif /* _H_DIAG_ERRIDS */

