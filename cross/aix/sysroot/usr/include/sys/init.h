/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/sys/init.h 1.54.1.47                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)72     1.54.1.47  src/bos/kernel/sys/init.h, syssi, bos53D, d2005_10C5 3/8/05 15:04:08 */
/*
 * COMPONENT_NAME: (SYSSI) System Initialization
 */

#ifndef _H_INIT
#define _H_INIT

/*----------------------------------------------------------------------*/
/*  Array containing the addresses of the various initializing		*/
/*  routines executed at boot time.  Any initialization not required	*/
/*  can be commented out of the initialization array.			*/
/*----------------------------------------------------------------------*/

extern void clkstart(void);
extern void cinit(void);
extern void credinit(void);
extern void ps_init(void);
extern void trc_init(void);
extern void trcconfig_dmy(void);
extern void j2_global_init(void);
extern void binit(void);
extern void errinit(void);
extern void finit(void);
extern void utsinit(void);
extern void vfsinit(void);
extern void flckinit(void);
extern void audinit(void);
extern void iost_init(void);
extern void tinit(void);
extern void devsw_init(void);
extern void dmpinit(void);
extern void init_mname(void);
extern void privinit(void);
extern void vm_init(void);
extern void cs_mpc_init(void);
extern void scrubinit(void);
extern void upfinit(void);
extern void csinit(void);
extern void utrchook_init(void);
extern void intr_init(void);
extern void ipc_initialize(void);
extern void rtipc_init(void);
extern void errinit2(void);
#ifdef _POWER_MP
extern void selpollinit(void);
extern void stop_cpus_init(void);
#ifndef __64BIT_KERNEL
extern void pinu_init(void);
#endif /* !__64BIT_KERNEL */
#endif /* _POWER_MP */
#if defined(_RSPC)
extern void rminit(void);
#endif /* _RSPC */
extern void mdinit(void);
#ifdef PM_SUPPORT
extern void pm_kernel_init(void);
#endif /* PM_SUPPORT */
extern void init_msg_heap(void);
extern void ppda_align_check(void);
extern void ri_flih_init(void);
extern void xmgc_init(void);
extern void ha_init(void);
extern void procfsInit(void);
extern void bsr_init(void);
extern void mtrc_init_defered(void);

/* init_tbl moved into si/main.c so it isn't duplicated*/

#ifdef _KERNEL
void (*init_tbl[])(void);
#endif /* _KERNEL */

#endif	/* _H_INIT */
