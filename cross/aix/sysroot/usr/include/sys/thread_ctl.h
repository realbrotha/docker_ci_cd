/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/thread_ctl.h 1.2                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2000               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)66     1.2  src/bos/kernel/sys/thread_ctl.h, sysproc, bos530 4/6/00 19:08:55 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   ORIGINS: 27, 83
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1993, 1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/**************************************************************************/
/*									  */
/*   Description:  Header file for exemption control facility             */
/*									  */
/**************************************************************************/

#if !defined(_SYS_THREAD_CTL_H)
#define _SYS_THREAD_CTL_H

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * Flag arguments to the kernel service.
 */
#define CTL_ENABLE		1
#define CTL_DISABLE		2
#define CTL_YIELD		3

/*
 * Bits for benefit grant by the kernel to the thread.
 */
#define PREEMPTION_GRANTED	0x00000001
#define SUSPENSION_GRANTED	0x00000002

typedef struct {
	unsigned short flags;
	unsigned short count;
} control_word_t;


#if !defined(_KERNEL)

/*
 * The prototype for the service registration function.
 */
int EnableCriticalSections(void);
void BeginCriticalSection(void);
void EndCriticalSection(void);

#endif	/* _KERNEL */

#if defined(__cplusplus)
}
#endif

#endif  /* _SYS_THREAD_CTL_H */
