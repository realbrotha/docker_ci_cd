/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/systm.h 1.12.1.5                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)71       1.12.1.5  src/bos/kernel/sys/systm.h, sysproc, bos530 3/1/99 15:42:32 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 3,27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_SYSTM
#define _H_SYSTM

#include <sys/types.h>
#include <sys/param.h>
#include <sys/mstsave.h>
#include <sys/vnode.h>
#include <sys/proc.h>
#include <sys/inode.h>
#include <sys/xmem.h>
#include <sys/buf.h>
#include <sys/file.h>
#include <sys/filsys.h>
#include <sys/low.h>

#define USR		USER_ADSPACE	/* user address space  */       
#define SYS		SYS_ADSPACE	/* system address space */

/*
 *  Some important kernel global variables.
 */

extern short cputype;		/* type of cpu */
extern time_t lbolt;		/* time in HZ since last boot */
extern time_t time;		/* time in sec from 1970 */

extern char runin;		/* scheduling flag */
extern char runout;		/* scheduling flag */
extern char curpri;		/* current priority */

extern struct vnode *rootdir;   /* pointer to vnode of root directory */
extern dev_t rootdev;		/* root device */

extern char *panicstr;		/* panic string pointer */
extern int blkacty;		/* active block devices */
extern int pwr_cnt, pwr_act;
extern int (*pwr_clr[])();
extern int danger, synchmode;
extern ulong meminbox;		/* installed memory in this machine # bytes */

int usrchar();

#endif /* _H_SYSTM */
