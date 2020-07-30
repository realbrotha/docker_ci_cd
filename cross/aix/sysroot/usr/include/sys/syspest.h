/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/syspest.h 1.26                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1992,2002          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)60       1.26  src/bos/kernel/sys/syspest.h, sysdb, bos530 10/7/02 18:02:28 */

#ifndef _H_SYSPEST
#define _H_SYSPEST

/*
 * COMPONENT_NAME: (SYSDB)  Kernel debug macros
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 3, 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1984
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#if __IBMCPP__ 
extern "BUILTIN" int __assert1(unsigned int, int, int);
extern "BUILTIN" void __assert2(int);
#endif

#ifdef __ia64
/*
 * void panic_break() 
 *
 * Special break to capture PANIC State
 *
 *	break.m	0x100888
 */
void panic_break(void);
#pragma mc_func panic_break {				\
	"0c404400000200000002000000000400"	\
}
#pragma reg_killed_by panic_break 
#endif


#ifdef _KERNEL
#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
#if defined(__ia64) && !defined(__IBMC__) && !defined(__IBMCPP__)
extern int brkpoint(...);
#else
extern int brkpoint(long, ...);
#endif
extern int printf(const char *,...);
extern int sprintf(char *, const char *, ...);
extern void panic(const char *);
extern int sio_stat(int);
#endif
#endif /* _KERNEL */

#ifdef DEBUG
/*
 *  This version of assert causes the traditional printf/panic and
 *  is intended for environments where source is available. For
 *  the kernel we don't keep around the printf; for device drivers
 *  we do to keep things working the way they used to.
 *  Usage Note: If ASSERT()/assert() appears as the sole target
 *  statement of the "if" in an if/else construct, it must either
 *  have {} braces around it, or the terminating semicolon must be
 *  left off. Otherwise the following "else" will generate an error.
 */

#ifndef __ia64
#ifdef _KERNSYS
#define assert(p) {__assert2(__assert1(!!(p),0,99));}
#define ASSERT(p) assert(p)
#else
#define assert(p) {if(!(p)){printf("[%s #%d]\n",__FILE__,__LINE__); panic("assert(p)");}} 
#define ASSERT(p) assert(p)
#endif
#else
#define assert(p) {if(!(p)){panic_break();printf("[%s #%d]\n",__FILE__,__LINE__); panic("assert(p)");}} 
#define ASSERT(p) assert(p)
#endif
	      /* suggested values for "DBUGL" */
#define BUGNFO 0x1       /* information: e.g., file open/close */
#define BUGACT 0x2       /* statement of program action */
#define BUGNTF 0x3       /* interfaces: names, data, return codes */
#define BUGNTA 0x4       /* interfaces for subordinate routines */
#define BUGNTX 0x5       /* detailed interface data */
#define BUGGID 0x99      /* gory internal detail */

#define BUGVDEF(bugvar,lev) \
    int bugvar = (lev);

#define BUGXDEF(bugvar) \
    extern bugvar;

#define BUGPR(prspec) \
    {printf("[%s #%d]  ", __FILE__, __LINE__); \
     printf prspec;}
#define BUGLPR(bugvar,buglev,prspec) {if ((buglev) <= (bugvar)) \
    {printf("[%s #%d]  ", __FILE__, __LINE__); \
     printf prspec;}}

#define BUGC(expr,comnt) {if (!(expr)) \
    {printf("[%s #%d]  %s\n", \
    __FILE__, __LINE__,comnt);}}
#define BUGLC(bugvar,buglev,expr,comnt) {\
	if ((!(expr)) && ((buglev) <= (bugvar))) \
    		{printf("[%s #%d]  %s\n", __FILE__, __LINE__,comnt);}}

#define BUGX(expr,funct) {if (!(expr)) \
    {printf("[%s #%d]\n", \
    __FILE__, __LINE__);funct;}}

#define BUGLX(bugvar,buglev,expr,funct) {\
	if ((!(expr)) && ((buglev) <= (bugvar))) \
    		{printf("[%s #%d]\n", __FILE__, __LINE__);funct;}}

#define BUGCX(expr,comnt,funct) { \
	if (!(expr))\
    		{printf("[%s #%d]  %s\n", __FILE__, __LINE__,comnt);funct;}}

#define BUGLCX(bugvar,buglev,expr,comnt,funct) { \
	if ((!(expr)) && ((buglev) <= (bugvar))) \
    		{printf("[%s #%d]  %s\n", __FILE__, __LINE__,comnt);funct;}}

#define BUGVT(variable,type)  \
    {printf("[%s #%d]  variable = %type\n", __FILE__, __LINE__,(variable));}

#define BUGLVT(bugvar,buglev,variable,type)  {\
	if ((buglev) <= (bugvar)) \
    		{printf("[%s #%d]  variable = %type\n", \
		__FILE__, __LINE__,(variable));}}

#define BUGRT(comnt,variable,type)  \
    {printf("[%s #%d]  %s...variable = %type\n", \
    __FILE__, __LINE__,comnt,(variable));}

#define BUGLRT(bugvar,buglev,comnt,variable,type)  {\
	if ((buglev) <= (bugvar)) \
    		{printf("[%s #%d]  %s...variable = %type\n",\
		 __FILE__, __LINE__,comnt,(variable));}}

#define BUGDM(comnt,dumpaddr,dumpl) \
    {printf("[%s #%d]  %s\n", \
    __FILE__, __LINE__,comnt); xdump((dumpaddr),(dumpl));}

#define BUGLDM(bugvar,buglev,comnt,dumpaddr,dumpl) {if (buglev <= bugvar) \
    {printf("[%s #%d]  %s\n", \
    __FILE__, __LINE__,comnt); xdump((dumpaddr),(dumpl));}}

#define	BUGS1(bugvar,buglev,s1) {\
	if ((buglev) <= (bugvar))\
		printf("[%s #%d] s1 =  %d\n", __FILE__, __LINE__, (s1));}

#define	BUGS2(bugvar,buglev,s1,s2) {\
	if ((buglev) <= (bugvar))\
	printf("[%s #%d] s1 = %x s2 = %x\n", __FILE__, __LINE__, (s1),(s2));}

#define BUGFUNCT(funct) {funct;}
#define BUGLFUNCT(bugvar,buglev,expr,funct)\
	 {if ((buglev) <= (bugvar)) funct;}

#else

#ifdef _POWER
/*
 *  This version of assert causes the compiler to generate an inline
 *  trap instead of a printf/panic. It is intended for shipped code
 *  where source is not available. Read Usage Note above.
 */

#ifdef __64BIT_KERNEL
#define assert(p) {__assert2(__assert1(!!(p),0,99));}
#else
#define assert(p) {__assert2(__assert1((unsigned)(p),0,99));}
#endif

#else
#define assert(p) {if(!(p)){panic_break();printf("[%s #%d]\n",__FILE__,__LINE__); panic("asset(p)");}}
#endif /* _POWER */

/*
 * Debug assert resolves to nothing for the base kernel. For kernel
 * extensions use the old definition for source compatibility. Read
 * Usage Note above.
 */
#ifdef _KERNSYS
#define ASSERT(p)
#else
#define ASSERT(p) {(p);}
#endif


#define BUGVDEF(bugvar,lev)
#define BUGXDEF(bugvar)
#define BUGPR(prspec)
#define BUGLPR(bugvar,buglev,prspec)
#define BUGC(expr,comnt)
#define BUGLC(bugvar,buglev,expr,comnt)
#define BUGX(expr,funct)
#define BUGLX(bugvar,buglev,expr,funct)
#define BUGVT(variable,type)
#define BUGLVT(bugvar,buglev,variable,type)
#define BUGRT(comnt,variable,type)
#define BUGLRT(bugvar,buglev,comnt,variable,type)
#define BUGCX(expr,comnt,funct)
#define BUGLCX(bugvar,buglev,expr,comnt,funct)
#define BUGDM(comnt,dumpaddr,dumpl)
#define BUGLDM(bugvar,buglev,comnt,dumpaddr,dumpl)
#define	BUGS1(bugvar,buglev,s1)
#define	BUGS2(bugvar,buglev,s1,s2)
#define BUGFUNCT(funct)
#define BUGLFUNCT(bugvar,buglev,expr,funct)

#endif /* DEBUG */

#endif /* _H_SYSPEST */
