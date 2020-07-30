/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* IBM CONFIDENTIAL                                                       */
/*                                                                        */
/* OBJECT CODE ONLY SOURCE MATERIALS                                      */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2003,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* The source code for this program is not published or otherwise         */
/* divested of its trade secrets, irrespective of what has been           */
/* deposited with the U.S. Copyright Office.                              */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/*======================================================================*/
/**CPRY                                                                 */
/* Licensed Materials - Property of IBM                                 */
/*                                                                      */
/* 5765-5G24                                                             */ 
/* (C) Copyright IBM Corp. 2002 All rights reserved.                    */
/*                                                                      */
/* US Government Users Restricted Rights - Use, duplication or          */ 
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.    */ 
/**CPRY                                                                 */
/*======================================================================*/

#ifndef SWCLOCK_H
#define SWCLOCK_H

static char sccsid_swclock_h[] = "@(#) src/css/hps/dd/include/swclock.h, fed.dd, css_rc15, rc150530a 1.2 04/02/12 13:53:25";

#include <sys/errno.h>
#include <sys/types.h>
#include <sys/thread.h>
#include <sys/atomic_op.h>

typedef long long       long64_t;
typedef void            *swclock_handle_t; 

extern swclock_handle_t swclockInit(void);
extern long64_t         swclockRead(swclock_handle_t);
extern double           swclockReadSec(swclock_handle_t);
extern int              swclockGetIncrement(swclock_handle_t);
extern int              swclockTerm(swclock_handle_t);

#endif /* SWCLOCK_H */
