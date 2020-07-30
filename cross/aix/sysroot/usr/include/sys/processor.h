/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/kernel/sys/processor.h 1.13                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1993,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)48	1.13  src/bos/kernel/sys/processor.h, sysml, bos53J, j2006_37B9 9/13/06 12:50:32 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27,83
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#ifndef _H_PROCESSOR
#define _H_PROCESSOR

typedef short cpu_t;            /* logical processor ID               */
typedef short cpuidx_t;         /* cpu index on srad                  */
typedef short sradid_t;         /* logical Srad ID                    */
typedef short processor_t;      /* physical processor ID              */
/*
 * Bind a process/thread to a processor 
 */
extern int bindprocessor(int What, int Who, cpu_t Where); 
/*
 * Values for What
 */
#define BINDPROCESS  1    /* Bind all threads in process Who        */
#define BINDTHREAD   2    /* Only bind thread Who                   */
/*
 * Values for Where
 */
#define PROCESSOR_CLASS_ANY ((cpu_t)(-1))  /* Unbound               */
/*
 * The next one is  T E M P O R A R I L Y !
 */
extern cpu_t mycpu(void);
/*
 * Kernel internal
 */
#ifdef _KERNEL
extern int switch_cpu(cpu_t Where, int Options);
#define SET_PROCESSOR_ID   1
#define RESET_PROCESSOR_ID 2
#define MP_MASTER          0
#define PREVIOUSLY_FUNNELLED 0x10000

extern unsigned long long kget_mypurr(void);
extern unsigned long long kget_my_spurr(void);
#endif	/* _KERNEL */

#endif /* _H_PROCESSOR */
