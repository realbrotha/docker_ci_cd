/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/dbexp.h 1.9                                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1989          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)83	1.9  src/bos/kernel/sys/dbexp.h, sysdb, bos530 6/16/90 00:25:49 */

/*
 * COMPONENT_NAME: (SYSDB) Kernel Debugger
 *
 * FUNCTIONS:
 *
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_DBEXP
#define _H_DBEXP

/*
 * Debugger's exported subroutines.
 *
 * The dbfunc data area is defined if DEF_STORAGE is defined.
 */

#define stubent 0
#define dbwtrmf 1
#define dbrtrmf 2
#define dbputchar 3
#define dbgetchar 4

#ifdef DEF_STORAGE
int dbstub();
int (*dbfunc[])() = {dbstub,dbstub,dbstub,dbstub,dbstub};
#else
extern int (*dbfunc[])();
#endif /* DEF_STORAGE */

#endif /* _H_DBEXP */
