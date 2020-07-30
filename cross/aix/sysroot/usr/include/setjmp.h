/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/usr/include/setjmp.h 1.14.1.8                           */
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
/* @(#)01       1.14.1.8  src/bos/usr/include/setjmp.h, incstd, bos53H, h2006_10A1 2/23/06 18:50:36 */

/*
 * COMPONENT_NAME: (INCSTD)
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_SETJMP
#define _H_SETJMP

#ifndef _H_STANDARDS
#include <standards.h>
#endif /* _H_STANDARDS */

#ifdef __cplusplus
extern "C" {
#endif

/*
 *
 *      The ANSI and POSIX standards require that certain values be in setjmp.h.
 *      They also require that if _ANSI_C_SOURCE or _POSIX_SOURCE is defined 
 *      then ONLY those standard specific values are present. This header 
 *      includes all the ANSI and POSIX required entries.
 *
 */

#ifdef _ANSI_C_SOURCE
#include <sys/m_setjmp.h>	/* define _JBLEN */

typedef __MTYPE jmp_buf[_JBLEN];

#if defined(_ALL_SOURCE) && (defined(__EXTABI__) || defined(__AIXEXTABI))
/* Extended ABI versions */
#define setjmp		setjmpx
#define longjmp		longjmpx
#define sigsetjmp 	sigsetjmpx
#define siglongjmp 	siglongjmpx
#define _setjmp		_setjmpx
#define _longjmp	_longjmpx
#endif /* _ALL_SOURCE && (__EXTABI__ || __AIXEXTABI) */

#ifdef   _NO_PROTO
extern void longjmp();
extern int setjmp(); 

#else  /*_NO_PROTO */

extern void longjmp(jmp_buf, int);
extern int setjmp(jmp_buf); 

#endif /*_NO_PROTO */

#if __STDC__ == 1
#ifndef setjmp
#define	setjmp(__X)	setjmp(__X)
#endif
#endif	/* __STDC__ */

#endif /* _ANSI_C_SOURCE */

#ifdef _POSIX_SOURCE

typedef __MTYPE sigjmp_buf[_JBLEN];
 
#ifdef _NO_PROTO
extern int sigsetjmp();
extern void siglongjmp();
#if _XOPEN_SOURCE_EXTENDED==1
extern int _setjmp();
extern void _longjmp();
#endif /* _XOPEN_SOURCE_EXTENDED */
#else /* _NO_PROTO */
extern int sigsetjmp(sigjmp_buf, int);
extern void siglongjmp(sigjmp_buf, int);
#if _XOPEN_SOURCE_EXTENDED==1
extern int _setjmp(jmp_buf);
extern void _longjmp(jmp_buf, int);
#endif /* _XOPEN_SOURCE_EXTENDED */
#endif /* _NO_PROTO */

#if __STDC__ == 1
#define	sigsetjmp(__X, __Y)	sigsetjmp(__X, __Y)
#endif	/* __STDC__ */

#endif /* _POSIX_SOURCE */

#ifdef _ALL_SOURCE

typedef __MTYPE ukey_jmp_buf[_UKJBLEN];

extern int ukey_setjmp(ukey_jmp_buf);

#pragma reachable (setjmp, _setjmp, sigsetjmp, ukey_setjmp)
#pragma leaves (longjmp, _longjmp, siglongjmp)

#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif
#endif /* _H_SETJMP */
