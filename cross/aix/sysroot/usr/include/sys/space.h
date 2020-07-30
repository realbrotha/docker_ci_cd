/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/sys/space.h 1.32.1.20                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)94       1.32.1.20  src/bos/kernel/sys/space.h, sysios, bos53D, d2004_45B5 10/25/04 16:22:30 */
/*
 *   COMPONENT_NAME: (SYSIOS) IO subsystems
 *
 *   ORIGINS: 27, 83
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988, 1994
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */


#ifndef _H_SPACE
#define _H_SPACE

#include <sys/proc.h>

#include <sys/sysinfo.h>
struct sysinfo sysinfo;
#ifndef __64BIT_KERNEL
struct sysinfo64 sysinfo64;
#endif
struct syswait syswait;
struct syserr syserr;
struct cpuinfo cpuinfo[MAXCPU];
struct waitinfo *waitinfo;

#include <sys/var.h>
#ifndef __64BIT_KERNEL
struct var v = {
	/* The following fields with RW in comment can be updated during 
	 * runtime via the sysconfig system call. The fields with RO in 
	 * comment cannot be updated using sysconfig.  
	 */
	0,			/* var_vers field 		*/
	0,			/* var_gen field  		*/	
	SYSCONFIG_VARSIZE,	/* var size for SYSCONFIG  	*/
	0,			/* RW: v_bufhw field  		*/
	0,			/* RW: v_mbufhw field  		*/
	CHILD_MAX,		/* RW: v_maxup field  		*/
	0,			/* RW: v_iostrun field		*/
	0,			/* RW: v_leastpriv field 	*/
	0,			/* RW: v_autost field  		*/
	0,			/* RW: v_maxpout field 		*/
	0,			/* RW: v_minpout field 		*/
	0,			/* RW: v_memscrub field 	*/
	0,			/* RO: v_lock field   		*/
	(char *)0,		/* RO: ve_lock field  		*/
	0,			/* RO: v_file field   		*/
	(char *)0,		/* RO: ve_file field  		*/
	NPROC,			/* RO: v_proc field	  	*/
	(char *)(&pvproc[0]),	/* RO: ve_proc field  		*/
	NCLIST,			/* RO: v_clist field  		*/
	NTHREAD,		/* RO: v_thread field 		*/
	(char *)(&pvthread[0]),	/* RO: ve_thread field		*/
	(char *)(&pvproc[0]),	/* RO: vb_proc field  		*/
	(char *)(&pvthread[0]),	/* RO: vb_thread field		*/
	0,			/* RO: v_ncpus	  		*/
	0,			/* RO: v_ncpus_cfg	  	*/
	0,			/* RW: v_fullcore field 	*/
	{ (char)0,(char)0,(char)0,(char)0 }, /* RW: v_initlvl field */
	(char)0,		/* RW: v_pre430core field 	*/
	0,			/* RW: v_xmgc field 		*/
	0,			/* RW: v_cpuguard field 	*/
	6,			/* RW: v_ncargs field 		*/
	0,			/* RW: v_pre520tune field 	*/
	0,			/* RW: Hard stack max for 64-bit app */
	1,			/* RW: Number of XMDBG segments      */
	LOGIN_NAME_MAX,		/* RW: v_max_logname field	*/
	MIN_XMFRECS		/* RW: Number of XM free records */
};
#else
struct kernvars v = {
	/* The following fields with RW in comment can be updated during 
	 * runtime via the sysconfig system call. The fields with RO in 
	 * comment cannot be updated using sysconfig.  
	 */
	0,			/* var_vers field 		*/
	0,			/* var_gen field  		*/	
	SYSCONFIG_VARSIZE,	/* var size for SYSCONFIG  	*/
	0,			/* RW: v_bufhw field  		*/
	0,			/* RW: v_mbufhw field  		*/
	CHILD_MAX,		/* RW: v_maxup field  		*/
	0,			/* RW: v_iostrun field		*/
	0,			/* RW: v_leastpriv field 	*/
	0,			/* RW: v_autost field  		*/
	0,			/* RW: v_maxpout field 		*/
	0,			/* RW: v_minpout field 		*/
	0,			/* RW: v_memscrub field 	*/
	0,			/* RO: v_lock field   		*/
	0,			/* RO: ve_lock field  		*/
	0,			/* RO: v_file field   		*/
	0,			/* RO: ve_file field  		*/
	NPROC,			/* RO: v_proc field	  	*/
	(char *)(&pvproc[0]),	/* RO: ve_proc field  		*/
	NCLIST,			/* RO: v_clist field  		*/
	NTHREAD,		/* RO: v_thread field 		*/
	(char *)(&pvthread[0]),	/* RO: ve_thread field		*/
	(char *)(&pvproc[0]),	/* RO: vb_proc field  		*/
	(char *)(&pvthread[0]),	/* RO: vb_thread field		*/
	0,			/* RO: v_ncpus	  		*/
	0,			/* RO: v_ncpus_cfg	  	*/
	0,			/* RW: v_fullcore field 	*/
	{ (char)0,(char)0,(char)0,(char)0 }, /* RW: v_initlvl field */
	0,			/* RW: v_coreformat field 	*/
	0,			/* RW: v_xmgc field 		*/
	0,			/* RW: v_cpuguard field 	*/
	6,			/* RW: v_ncargs field 		*/
	0,			/* RW: v_pre520tune field 	*/
	0,			/* RW: Hard stack max for 64-bit app */
	1,			/* RW: Number of XMDBG segments      */
	LOGIN_NAME_MAX,		/* RW: v_max_logname field	*/
	MIN_XMFRECS		/* RW: Number of XM free records */

};
#endif /* __64BIT_KERNEL */

#endif /* _H_SPACE */
