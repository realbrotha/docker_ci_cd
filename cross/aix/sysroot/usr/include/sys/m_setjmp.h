/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/usr/include/sys/POWER/m_setjmp.h 1.7                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)74  1.7  src/bos/usr/include/sys/POWER/m_setjmp.h, incstd, bos53H, h2006_10A1 2/23/06 18:48:43 */

#ifdef __64BIT__
#define __MTYPE long  /* need 8-byte alignment of jmp_buf's in 64-bit mode */
#else /* __64BIT__ */
#define __MTYPE int   /* need 4-byte alignment of jmp_buf's in 32-bit mode */
#endif /* __64BIT__ */


#if defined(__EXTABI__) || defined(__AIXEXTABI)
/* Extended ABI sized jumpbufs */

#ifdef __64BIT__
#define _JBLEN  128    /* doublewords, 1K (364 legacy + 228 VMX + 432 rsvd) */
#define _UKJBLEN  131  /* + 3 doublewords */
#else /* __64BIT__ */
#define _JBLEN  229    /* words, 916 bytes (256 legacy + 228 VMX + 432 rsvd) */
#define _UKJBLEN  233   /* + 4 words */
#endif /* __64BIT__ */

#else
/* Legacy ABI sized jumpbufs */

#ifdef __64BIT__
#define _JBLEN  85    /* regs, fp regs, cr, sigmask, context, etc. */
#define _UKJBLEN  88    /* + 3 doublewords */
#else /* __64BIT__ */
#define _JBLEN  64    /* regs, fp regs, cr, sigmask, context, etc. */
#define _UKJBLEN  68    /* + 4 words */
#endif /* __64BIT__ */

#endif /* __EXTABI__ || __AIXEXTABI */

