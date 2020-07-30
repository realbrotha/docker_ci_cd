/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/diag/tmdefs.h 1.7                           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1992          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)30       1.7  src/bos/usr/include/diag/tmdefs.h, cmddiag, bos530 6/11/02 16:16:39 */
/*
 *   COMPONENT_NAME: CMDDIAG
 *
 *   FUNCTIONS: Diagnostic header file.
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1989,1992
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_TMDEFS
#define _H_TMDEFS

/*  exenv - short: IPL, STD, MNT or CONC.  */
#define	EXENV_IPL		1
#define	EXENV_STD		2
#define	EXENV_REGR		3
#define	EXENV_CONC		4
#define	EXENV_SYSX 		5

/*  advanced - short: TRUE or FALSE.  */
#define	ADVANCED_TRUE		1
#define	ADVANCED_FALSE		0

/*  system - short: TRUE or FALSE.  */
#define	SYSTEM_TRUE		1
#define	SYSTEM_FALSE		0

/*  dmode - short: ELA , PD , REPAIR , MISSING ,FREELANCE, REMINDER .  */
#define	DMODE_ELA		1
#define	DMODE_PD		2
#define	DMODE_REPAIR		4
#define	DMODE_MS1   		8
#define	DMODE_MS2   		16	
#define	DMODE_FREELANCE		32
#define DMODE_ALL_SIBLINGS_MISSING 64
#define DMODE_REMIND		128

/*  loopmode - short: NOTLM, ENTERLM, INLM or EXITLM.  */
#define	LOOPMODE_NOTLM		1
#define	LOOPMODE_ENTERLM	2
#define	LOOPMODE_INLM		4
#define	LOOPMODE_EXITLM		8

/*  console - short: TRUE or FALSE.  */
#define	CONSOLE_TRUE		1
#define	CONSOLE_FALSE		0 

/*  state1 - short: state of child device which has been tested.  */
/*  state2 - short: state of child device which has been tested.  */
#define	STATE_NOTEST     		0
#define	STATE_GOOD  			1
#define	STATE_BAD        		2
#define STATE_MISSING                   3
#define STATE_DR_QUIT			4

#define DIAG_STRING			0
#define DIAG_INT			1
#define DIAG_SHORT			2

#endif
