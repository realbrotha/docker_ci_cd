/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernel/sys/trcmacros.h 1.34.1.2                         */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1990              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/* @(#)32    1.34.1.2  src/bos/kernel/sys/trcmacros.h, cmdtrace, bos53Q, q2008_07C1 2/7/08 17:36:47 */


#ifndef _H_TRCMACROS
#define _H_TRCMACROS

/*
 * COMPONENT_NAME: (SYSTRACE) system trace facility
 *
 * FUNCTIONS:  macros for trace hook calls
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1990
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#include <sys/types.h>

/* Correct usage of trace hook routines:
 *
 * Use the macros: TRCHKL0, TRCHKL0T, ..., TRCHKL5, TRCHKL5T
 *
 * You may also use TRCHK, TRCHKT, TRCHKL, TRCHKLT, TRCHKG, and TRCHKGT
 *
 * The 32-bit kernel traces either 0, 1, or 5 parameters per nongeneric hook.
 * This corresponds to 0 - TRCHK and TRCHKT, 1 - TRCHKL and TRCHKLT,
 * and 5 - TRCHKG and TRCHKGT.  The TRCHKL0 ... TRCHKL5T macros simply
 * use these macros.
 *
 * However, the 64-bit kernel traces the number of parameters specified,
 * 0 through 5.  Thus the primary set of macros are the TRCHKL0 - TRCHKL5T
 * macros.
 *
 * For generic trace use the macros: TRCGEN, TRCGENT.
 */

/*
 * 64-bit hookword definition:
 *
 * One character represents one nibble (4 bits)
 *
 * ffffllllhhhhssss
 * 
 * Where:	h is the hook id
 * 	f is a 16-bit flag field
 * 	l is the length in bytes
 * 	s is the subhook id
 * 
 * The flags are defined as
 * 	tgbuuuuuuuuuuuuu: t - time stamped,  g - generic (trcgen),
 * 	  b - 32-bit data, u - unused.
 * 
 * Note that the hook id and subhook are passed as 32 bits
 * in the loe-order portion of the first 64-bit word.
 */
/* a 64-bit hook word. */
struct hook64 {
	unsigned short flags;
	unsigned short ln;
	unsigned short hk;
	unsigned short subhk;
};
#define HKWD64_TMASK 0x8000000000000000LL
#define HKWD64_GMASK 0x4000000000000000LL
#define HKWD64_BMASK 0x2000000000000000LL
#define HKWD64_PMASK 0x1000000000000000LL
#define HKWD64_RMASK 0x0800000000000000LL
#define HKWD64_NRMASK 0x0007000000000000LL /* # regs */
#define HKWD64_RSHIFT 48
#define HKWD64_NREGS(hkwd) (((hkwd) & HKWD64_RMASK)?\
	((((hkwd)&HKWD64_NRMASK) >> HKWD64_RSHIFT) + 1): 0)
#define HKWD64_FLAGMASK 0xffff000000000000LL
#define HKWD64_VALIDFLAGMASK 0xf807000000000000LL
/* Valid flags to pass to trchook64 */
#define HKWD64_VALIDINFLAGMASK 0xf000000000000000LL
#define HKWD64_LENMASK 0x0000ffff00000000LL
#define ISTIMESTAMPED64(hkwd) ((hkwd) & HKWD64_TMASK)
#define HKWD64_NONGEN_MAXLEN 5*8
#define HKWD64_HOOKMASK   0x00000000ffff0000LL
#define HKWD64_SUBHKMASK 0x000000000000ffffLL
#define HKWD64_HOOKSMASK 0x00000000ffffffffLL
#define HKWD64_HOOKSMASK12 0x00000000fff0ffffLL
#define HKWD64_TO_HOOKID(h) ((h) & HKWD64_HOOKMASK)
#define HKWD64_TO_HKID(h) (((h) & HKWD64_HOOKMASK) >> 20)
#define HKWD64_TO_LEN(h) (((h) & HKWD64_LENMASK) >> 32)
/* Handle hook data length from a 32-bit app in a 64-bit trace. */
#define HKWD64_LENROUND(l) (((l)+4)&0xfff8)
#define HKWD64_TO_SUBHOOK(h) (((h) & HKWD64_SUBHKMASK))
#define HKWD64_VALIDHOOKMASK \
	(HKWD64_VALIDFLAGMASK | HKWD64_LENMASK | HKWD64_HOOKSMASK)
#define HKWD64_VALIDHOOKMASK12 \
	(HKWD64_VALIDFLAGMASK | HKWD64_LENMASK | HKWD64_HOOKSMASK12)
#define HKWD64_VALIDINHOOKMASK \
	(HKWD64_VALIDINFLAGMASK | HKWD64_LENMASK | HKWD64_HOOKSMASK)
#define HKWD64_VALIDINHOOKMASK12 \
	(HKWD64_VALIDINFLAGMASK | HKWD64_LENMASK | HKWD64_HOOKSMASK12)
/* build a 64-bit hook. */
#define HKWD64_EXPAND(h,len) (((u_longlong_t)(h) | \
	  ((u_longlong_t)(len) << 32)) & \
	  HKWD64_VALIDINHOOKMASK)
/* Same as above except the hookid is always 12 bits. */
#define HKWD64_EXPAND12(h,len) (((u_longlong_t)(h) | \
	  ((u_longlong_t)(len) << 32)) & \
	  HKWD64_VALIDINHOOKMASK12)

/*
 * 32-bit hookword definition:
 *
 *  0        4        8       12       16       20       24       28       32
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |          Hook ID         |  type  |             data field            |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 *
 * The Hook ID field is the three digit hex representation of the hook id.
 *
 * The type field is further defined as:
 *   high-order bit:  0 = no time stamp, 1 = time stamp
 *   low-order bits:  indicate the number of words to trace
 *		      (hookword and data words but not timestamp)
 *
 * The data field definition depends on the type of trace hook:
 *   for generic trace it is reserved and indicates the length of the
 *      variable buffer
 *   for all others it is available for 2 bytes of additional trace data
 */
/* a 32-bit hook word. */
struct hook32 {
#ifndef	__ia64	/* __ia64 */
	unsigned hk:12;
	unsigned tflag:1;
	unsigned ln:3;
	unsigned short subhk;
#else
	unsigned short subhk;
	unsigned ln:3;
	unsigned tflag:1;
	unsigned hk:12;
#endif
};
#define HKID_MASK   0xFFF00000
#define HKTY_XMASK  0xFFF0FFFF
#define HKTY_TMASK  0x00080000
#define HKTY_Vr     0x0
#define HKTY_Sr     0x1
#define HKTY_Lr     0x2
#define HKTY_Gr     0x6
#define HKTY_VTr    0x8
#define HKTY_STr    0x9
#define HKTY_LTr    0xA
#define HKTY_GTr    0xE

#define HKTY_V      (HKTY_Vr  << 16)
#define HKTY_S      (HKTY_Sr  << 16)
#define HKTY_L      (HKTY_Lr  << 16)
#define HKTY_G      (HKTY_Gr  << 16)
#define HKTY_VT     (HKTY_VTr << 16)
#define HKTY_ST     (HKTY_STr << 16)
#define HKTY_LT     (HKTY_LTr << 16)
#define HKTY_GT     (HKTY_GTr << 16)
#define HKTY_LAST   (HKTY_GTr << 16)
#define HKWDTOMAJOR(hw)   (((hw) >> 24) & 0xFF)
#define HKWDTOHKID(hw)    (((hw) >> 20) & 0xFFF)
#define HKWDTOTYPE(hw)    (((hw) >> 16) & 0xF)
#define HKWDTOLEN(hw)     (((hw) >> 16) & 0x7)
#define HKWDTOWLEN(hw)    ((((hw) & 0xFFFF) + 3 ) / 4)
#define HKWDTOBLEN(hw)    ((hw) & 0xFFFF)
#define ISTIMESTAMPED(hw) ((hw) & 0x00080000)
#define __TRCHI64(d) ((long long)d >> 32)
#define __TRCLOW64(d) (unsigned int)((long long)d & 0x00000000ffffffffLL)
#define _TRCTMASK(hw)	((hw) & HKTY_XMASK)

/* Trace channels.
 * Channel 0 is the kernel trace channel and is used for all non-generic
 * trace hooks.
 * Calls to generic trace routines use channels 1-7 or, to include data
 * in the kernel trace, channel 0.
 */
#ifndef TRC_NCHANNELS
#define TRC_NCHANNELS 8
#endif
extern char Trconflag[TRC_NCHANNELS];
#define TRC_ISON(chan) (Trconflag[(chan)])

#ifdef _KERNEL
/* temporary.
 * 64-bit kernel code can continue to use trchook.
 * New code will use trchook64.
 */
#ifdef __64BIT_KERNEL
#define __TRCHOOK trchook64
#else /* !__64BIT_KERNEL */
#define __TRCHOOK trchook
#endif /* __64BIT_KERNEL */

#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
/* This is the common trace hook routine.
 * Up to 5 data words, in addition to the hookword, can be recorded.
 */
extern void __TRCHOOK(ulong_t hkwd, ...);

#ifdef __64BIT_KERNEL
#pragma isolated_call(trchook64)
#else
#pragma isolated_call(trchook)
#endif

/* These are the generic trace hook kernel services.  */
extern void trcgenk(int chan, ulong_t hkwd, ulong_t d1, uint len, void *buf);
extern void trcgenkt(int chan, ulong_t hkwd, ulong_t d1, uint len, void *buf);

#else /* ! (__FULL_PROTO || __64BIT_KERNEL)*/
/* This is the common trace hook routine.  */
extern void __TRCHOOK();

extern void trcgenk();
extern void trcgenkt();
#endif /* (__FULL_PROTO || __64BIT_KERNEL) */

/* Kernel trace hooks use the common trace hook routine, trchook.
 * The call is avoided if trace is off for channel 0.
 */
#ifdef __64BIT_KERNEL
#ifndef __MTRACE
#define TRCHKL0(hw) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,0)) : \
	(void) 0)
#define TRCHKL0T(hw) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,0) | HKWD64_TMASK) : \
	(void) 0)
#define TRCHKL1(hw,a) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,8), (ulong_t)(a)) : \
	(void) 0)
#define TRCHKL1T(hw,a)	(TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,8) | HKWD64_TMASK,\
	  (ulong_t)(a)) : \
	(void) 0)
#define TRCHKL2(hw,a,b) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,16), \
	  (ulong_t)(a), (ulong_t)(b)) : \
	(void) 0)
#define TRCHKL2T(hw,a,b) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,16) | HKWD64_TMASK, \
	  (ulong_t)(a), (ulong_t)(b)) : \
	(void) 0)
#define TRCHKL3(hw,a,b,c) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,24), \
	  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c)) : \
	(void) 0)
#define TRCHKL3T(hw,a,b,c) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,24) | HKWD64_TMASK,\
	  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c)) : \
	(void) 0)
#define TRCHKL4(hw,a,b,c,d) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,32),\
	  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), (ulong_t)(d)) : \
	(void) 0)
#define TRCHKL4T(hw,a,b,c,d) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,32) | HKWD64_TMASK,\
	  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), (ulong_t)(d)) : \
	(void) 0)
#define TRCHKL5(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,40),\
	  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), (ulong_t)(d),\
	  (ulong_t)(e)) : \
	(void) 0)
#define TRCHKL5T(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,40) | HKWD64_TMASK,\
	  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), (ulong_t)(d),\
	  (ulong_t)(e)) :\
	(void) 0)
#endif /* __MTRACE */

/* Kernel generic trace hooks use the kernel services, trcgenk and trcgenkt.
 * The call is avoided if trace is off for the specified channel.
 */
#define TRCGEN(ch,hw,d1,len,buf) (TRC_ISON(ch) ? \
	(void) trcgenk((int)(ch), (hw), \
	  (ulong_t)(d1), (uint)(len), (void *)(buf)) : \
	(void) 0)

#define TRCGENT(ch,hw,d1,len,buf) (TRC_ISON(ch) ? \
	(void) trcgenkt((int)(ch), (hw), \
	  (ulong_t)(d1), (uint)(len), (void *)(buf)) : \
	(void) 0)
#else /* !__64BIT_KERNEL */
#ifdef __FULL_PROTO
#ifndef __MTRACE
#define TRCHK(hw) (TRC_ISON(0) ? \
	(void) __TRCHOOK((long)(_TRCTMASK(hw)|HKTY_S)) : \
	(void) 0)
#define TRCHKT(hw) (TRC_ISON(0) ? \
	(void) __TRCHOOK((long)(_TRCTMASK(hw)|HKTY_ST)) : \
	(void) 0)
#define TRCHKL(hw,a) (TRC_ISON(0) ? \
	(void) __TRCHOOK((long)(_TRCTMASK(hw)|HKTY_L), (long)(a)) : \
	(void) 0)
#define TRCHKLT(hw,a) (TRC_ISON(0) ? \
	(void) __TRCHOOK((long)(_TRCTMASK(hw)|HKTY_LT), (long)(a)) : \
	(void) 0)
#define TRCHKG(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __TRCHOOK((long)(_TRCTMASK(hw)|HKTY_G),\
	  (long)(a), (long)(b), (long)(c), (long)(d), (long)(e)) : \
	(void) 0)
#define TRCHKGT(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __TRCHOOK((long)(_TRCTMASK(hw)|HKTY_GT),\
	  (long)(a), (long)(b), (long)(c), (long)(d), (long)(e)) :\
	(void) 0)
#endif /* __MTRACE */

/* Kernel generic trace hooks use the kernel services, trcgenk and trcgenkt.
 * The call is avoided if trace is off for the specified channel.
 */
#define TRCGEN(ch,hw,d1,len,buf) (TRC_ISON(ch) ? \
	(void) trcgenk((int)(ch), (long)(hw), (int)(d1), (int)(len), (void *)(buf)) : \
	(void) 0)
#define TRCGENT(ch,hw,d1,len,buf) (TRC_ISON(ch) ? \
	(void) trcgenkt((int)(ch), (long)(hw), (int)(d1), (int)(len), (void *)(buf)) : \
	(void) 0)
#else /* ! __FULL_PROTO */
#ifndef __MTRACE
#define TRCHK(hw) (TRC_ISON(0) ? \
	(void) __TRCHOOK(_TRCTMASK(hw)|HKTY_S) : \
	(void) 0)
#define TRCHKT(hw) (TRC_ISON(0) ? \
	(void) __TRCHOOK(_TRCTMASK(hw)|HKTY_ST) : \
	(void) 0)
#define TRCHKL(hw,a) (TRC_ISON(0) ? \
	(void) __TRCHOOK(_TRCTMASK(hw)|HKTY_L,a) : \
	(void) 0)
#define TRCHKLT(hw,a) (TRC_ISON(0) ? \
	(void) __TRCHOOK(_TRCTMASK(hw)|HKTY_LT,a) : \
	(void) 0)
#define TRCHKG(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __TRCHOOK(_TRCTMASK(hw)|HKTY_G,a,b,c,d,e) : \
	(void) 0)
#define TRCHKGT(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __TRCHOOK(_TRCTMASK(hw)|HKTY_GT,a,b,c,d,e) :\
	(void) 0)
#endif /* __MTRACE */

/* Kernel generic trace hooks use the kernel services, trcgenk and trcgenkt.
 * The call is avoided if trace is off for the specified channel.
 */
#define TRCGEN(ch,hw,d1,len,buf) (TRC_ISON(ch) ? \
	(void) trcgenk(ch,hw,d1,len,buf) : \
	(void) 0)
#define TRCGENT(ch,hw,d1,len,buf) (TRC_ISON(ch) ? \
	(void) trcgenkt(ch,hw,d1,len,buf) : \
	(void) 0)
#endif /* __FULL_PROTO */
#endif /* __64BIT_KERNEL */

/* Redefine uses of the old macros to call the correct kernel service.  */
#define TRCGENK(a,b,c,d,e) TRCGEN(a,b,c,d,e)
#define TRCGENKT(a,b,c,d,e) TRCGENT(a,b,c,d,e)

/*
 * Easy to use macros for hooks in system calls.
 * TRCHKT_SYSC(UNAMEX)
 *   expands to:
 * trchook(HKWD_SYSC_UNAMEX | HKTY_T)
 */
#define TRCHKT_SYSC(x) TRCHKT_NOMTRC(HKWD_SYSC_##x)
#define TRCHKLT_SYSC(x,a) TRCHKLT_NOMTRC(HKWD_SYSC_##x,a)
#define TRCHKGT_SYSC(x,a,b,c,d,e) TRCHKGT_NOMTRC(HKWD_SYSC_##x,a,b,c,d,e)


/* Lightweight Memory Trace macros and definitions */
#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
extern void mtrchook0_pre(ulong_t hkwd, int dest);
extern void mtrchook0(ulong_t hkwd, int dest);
extern void mtrchook1_pre(ulong_t hkwd, ulong_t d1, int dest);
extern void mtrchook1(ulong_t hkwd, ulong_t d1, int dest);
extern void mtrchook2_pre(ulong_t hkwd, ulong_t d1, ulong_t d2, int dest);
extern void mtrchook2(ulong_t hkwd, ulong_t d1, ulong_t d2, int dest);
extern void mtrchook3_pre(ulong_t hkwd, ulong_t d1, ulong_t d2, ulong_t d3,
		     int dest);
extern void mtrchook3(ulong_t hkwd, ulong_t d1, ulong_t d2, ulong_t d3,
		     int dest);
extern void mtrchook4_pre(ulong_t hkwd, ulong_t d1, ulong_t d2, ulong_t d3,
		     ulong_t d4, int dest);
extern void mtrchook4(ulong_t hkwd, ulong_t d1, ulong_t d2, ulong_t d3,
		     ulong_t d4, int dest);
extern void mtrchook5_pre(ulong_t hkwd, ulong_t d1, ulong_t d2, ulong_t d3,
		     ulong_t d4, ulong_t d5, int dest);
extern void mtrchook5(ulong_t hkwd, ulong_t d1, ulong_t d2, ulong_t d3,
		     ulong_t d4, ulong_t d5, int dest);

#else /* ! (__FULL_PROTO || __64BIT_KERNEL)*/

extern void mtrchook0_pre();
extern void mtrchook0();
extern void mtrchook1_pre();
extern void mtrchook1();
extern void mtrchook2_pre();
extern void mtrchook2();
extern void mtrchook3_pre();
extern void mtrchook3();
extern void mtrchook4_pre();
extern void mtrchook4();
extern void mtrchook5_pre();
extern void mtrchook5();

#endif /* (__FULL_PROTO || __64BIT_KERNEL) */

#pragma isolated_call(mtrchook0)
#pragma isolated_call(mtrchook0_pre)
#pragma isolated_call(mtrchook1)
#pragma isolated_call(mtrchook1_pre)
#pragma isolated_call(mtrchook2)
#pragma isolated_call(mtrchook2_pre)
#pragma isolated_call(mtrchook3)
#pragma isolated_call(mtrchook3_pre)
#pragma isolated_call(mtrchook4)
#pragma isolated_call(mtrchook4_pre)
#pragma isolated_call(mtrchook5)
#pragma isolated_call(mtrchook5_pre)

/* values of dest parameter of mtrchookx routines
 * MTRC_xxx value is equal to MTR_BUF_xxx << L2_MTRCQSIZE
 * buffer type value may be OR'ed with MTRC_SYSTEM to additionally
 * trace into system trace buffers
 */
#define MTRC_COMMON  0x00   /* trace into common buffer */
#define MTRC_RARE    0x20   /* trace into rare   buffer */
#define MTRC_SYSTEM  0x1000 /* additionally trace into system trace buffers */


/* macros that should be used by base kernel and kernel extensions
 * TRCHKxx        macros which record events in both system trace (if active) 
 *                and memory trace common buffers
 * TRCHKxx_RARE   macros which record events in both system trace (if active)
 *                and memory trace rare buffers
 * TRCHKxx_NOMTRC macros which record events in system trace only (if active)
 * MTRCHKxx       macros which record events in memory trace common buffer only
 * MTRCHKxx_RARE  macros which record events in memory trace rare buffer only
 */
#ifdef __MTRACE
#ifdef __64BIT_KERNEL
/* common trace events */
#define TRCHKL0(hw) \
        mtrchook0(HKWD64_EXPAND(hw,0), \
		  MTRC_COMMON|MTRC_SYSTEM)
#define TRCHKL1(hw,a) \
        mtrchook1(HKWD64_EXPAND(hw,8), \
		  (ulong_t)(a), \
		  MTRC_COMMON|MTRC_SYSTEM)
#define TRCHKL2(hw,a,b) \
        mtrchook2(HKWD64_EXPAND(hw,16), \
		  (ulong_t)(a),(ulong_t)(b), \
		  MTRC_COMMON|MTRC_SYSTEM)
#define TRCHKL3(hw,a,b,c) \
        mtrchook3(HKWD64_EXPAND(hw,24), \
		  (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		  MTRC_COMMON|MTRC_SYSTEM)
#define TRCHKL4(hw,a,b,c,d) \
	mtrchook4(HKWD64_EXPAND(hw,32), \
		  (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		  (ulong_t)(d), \
		  MTRC_COMMON|MTRC_SYSTEM)
#define TRCHKL5(hw,a,b,c,d,e) \
        mtrchook5(HKWD64_EXPAND(hw,40), \
		  (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		  (ulong_t)(d),(ulong_t)(e), \
		  MTRC_COMMON|MTRC_SYSTEM)

#define TRCHKL0T(hw) \
        mtrchook0(HKWD64_EXPAND(hw,0)|HKWD64_TMASK, \
		  MTRC_COMMON|MTRC_SYSTEM)
#define TRCHKL1T(hw,a) \
	mtrchook1(HKWD64_EXPAND(hw,8)|HKWD64_TMASK, \
		  (ulong_t)(a), \
		  MTRC_COMMON|MTRC_SYSTEM)
#define TRCHKL2T(hw,a,b) \
        mtrchook2(HKWD64_EXPAND(hw,16)|HKWD64_TMASK, \
		  (ulong_t)(a),(ulong_t)(b), \
		  MTRC_COMMON|MTRC_SYSTEM)
#define TRCHKL3T(hw,a,b,c) \
        mtrchook3(HKWD64_EXPAND(hw,24)|HKWD64_TMASK, \
		  (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		  MTRC_COMMON|MTRC_SYSTEM)
#define TRCHKL4T(hw,a,b,c,d) \
        mtrchook4(HKWD64_EXPAND(hw,32)|HKWD64_TMASK, \
		  (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		  (ulong_t)(d), \
		  MTRC_COMMON|MTRC_SYSTEM)
#define TRCHKL5T(hw,a,b,c,d,e) \
        mtrchook5(HKWD64_EXPAND(hw,40)|HKWD64_TMASK, \
		  (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		  (ulong_t)(d),(ulong_t)(e), \
		  MTRC_COMMON|MTRC_SYSTEM)

/* rare trace events */
#define TRCHKL0_RARE(hw) \
        mtrchook0_pre(HKWD64_EXPAND(hw,0), \
		      MTRC_RARE|MTRC_SYSTEM)
#define TRCHKL1_RARE(hw,a) \
        mtrchook1_pre(HKWD64_EXPAND(hw,8), \
		      (ulong_t)(a), \
		      MTRC_RARE|MTRC_SYSTEM)
#define TRCHKL2_RARE(hw,a,b) \
        mtrchook2_pre(HKWD64_EXPAND(hw,16), \
		      (ulong_t)(a),(ulong_t)(b),  \
		      MTRC_RARE|MTRC_SYSTEM)
#define TRCHKL3_RARE(hw,a,b,c) \
        mtrchook3_pre(HKWD64_EXPAND(hw,24), \
		      (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		      MTRC_RARE|MTRC_SYSTEM)
#define TRCHKL4_RARE(hw,a,b,c,d) \
        mtrchook4_pre(HKWD64_EXPAND(hw,32), \
		      (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		      (ulong_t)(d), \
		      MTRC_RARE|MTRC_SYSTEM)
#define TRCHKL5_RARE(hw,a,b,c,d,e) \
        mtrchook5_pre(HKWD64_EXPAND(hw,40), \
		      (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		      (ulong_t)(d),(ulong_t)(e), \
		      MTRC_RARE|MTRC_SYSTEM)

#define TRCHKL0T_RARE(hw) \
        mtrchook0_pre(HKWD64_EXPAND(hw,0)|HKWD64_TMASK, \
		      MTRC_RARE|MTRC_SYSTEM)
#define TRCHKL1T_RARE(hw,a) \
        mtrchook1_pre(HKWD64_EXPAND(hw,8)|HKWD64_TMASK, \
		      (ulong_t)(a), \
		      MTRC_RARE|MTRC_SYSTEM)
#define TRCHKL2T_RARE(hw,a,b) \
        mtrchook2_pre(HKWD64_EXPAND(hw,16)|HKWD64_TMASK, \
		      (ulong_t)(a),(ulong_t)(b), \
		      MTRC_RARE|MTRC_SYSTEM)
#define TRCHKL3T_RARE(hw,a,b,c) \
        mtrchook3_pre(HKWD64_EXPAND(hw,24)|HKWD64_TMASK, \
		      (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		      MTRC_RARE|MTRC_SYSTEM)
#define TRCHKL4T_RARE(hw,a,b,c,d) \
        mtrchook4_pre(HKWD64_EXPAND(hw,32)|HKWD64_TMASK, \
		      (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		      (ulong_t)(d), \
		      MTRC_RARE|MTRC_SYSTEM)
#define TRCHKL5T_RARE(hw,a,b,c,d,e) \
        mtrchook5_pre(HKWD64_EXPAND(hw,40)|HKWD64_TMASK, \
		      (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		      (ulong_t)(d),(ulong_t)(e), \
		      MTRC_RARE|MTRC_SYSTEM)


/* system trace only events */
#define TRCHKL0_NOMTRC(hw) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,0)) : \
	(void) 0)
#define TRCHKL0T_NOMTRC(hw) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,0) | HKWD64_TMASK) : \
	(void) 0)
#define TRCHKL1_NOMTRC(hw,a) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,8), (ulong_t)(a)) : \
	(void) 0)
#define TRCHKL1T_NOMTRC(hw,a)	(TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,8) | HKWD64_TMASK,\
	                 (ulong_t)(a)) : \
	(void) 0)
#define TRCHKL2_NOMTRC(hw,a,b) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,16), \
	                 (ulong_t)(a), (ulong_t)(b)) : \
	(void) 0)
#define TRCHKL2T_NOMTRC(hw,a,b) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,16) | HKWD64_TMASK, \
	                 (ulong_t)(a), (ulong_t)(b)) : \
	(void) 0)
#define TRCHKL3_NOMTRC(hw,a,b,c) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,24), \
	                 (ulong_t)(a), (ulong_t)(b), (ulong_t)(c)) : \
	(void) 0)
#define TRCHKL3T_NOMTRC(hw,a,b,c) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,24) | HKWD64_TMASK,\
	                 (ulong_t)(a), (ulong_t)(b), (ulong_t)(c)) : \
	(void) 0)
#define TRCHKL4_NOMTRC(hw,a,b,c,d) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,32),\
	                 (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), \
                         (ulong_t)(d)) : \
	(void) 0)
#define TRCHKL4T_NOMTRC(hw,a,b,c,d) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,32) | HKWD64_TMASK,\
	                 (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), \
                         (ulong_t)(d)) : \
	(void) 0)
#define TRCHKL5_NOMTRC(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,40),\
	                 (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), \
                         (ulong_t)(d), (ulong_t)(e)) : \
	(void) 0)
#define TRCHKL5T_NOMTRC(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __TRCHOOK(HKWD64_EXPAND(hw,40) | HKWD64_TMASK,\
	                 (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), \
                         (ulong_t)(d),(ulong_t)(e)) :\
	(void) 0)

/* common memory trace only events */
#define MTRCHKL0T(hw) \
        mtrchook0(HKWD64_EXPAND(hw,0)|HKWD64_TMASK, \
		  MTRC_COMMON)
#define MTRCHKL1T(hw,a) \
	mtrchook1(HKWD64_EXPAND(hw,8)|HKWD64_TMASK, \
		  (ulong_t)(a), \
		  MTRC_COMMON)
#define MTRCHKL2T(hw,a,b) \
        mtrchook2(HKWD64_EXPAND(hw,16)|HKWD64_TMASK, \
		  (ulong_t)(a),(ulong_t)(b), \
		  MTRC_COMMON)
#define MTRCHKL3T(hw,a,b,c) \
        mtrchook3(HKWD64_EXPAND(hw,24)|HKWD64_TMASK, \
		  (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		  MTRC_COMMON)
#define MTRCHKL4T(hw,a,b,c,d) \
        mtrchook4(HKWD64_EXPAND(hw,32)|HKWD64_TMASK, \
		  (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		  (ulong_t)(d), \
		  MTRC_COMMON)
#define MTRCHKL5T(hw,a,b,c,d,e) \
        mtrchook5(HKWD64_EXPAND(hw,40)|HKWD64_TMASK, \
		  (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		  (ulong_t)(d),(ulong_t)(e), \
		  MTRC_COMMON)

/* rare memory trace only events */
#define MTRCHKL0T_RARE(hw) \
        mtrchook0_pre(HKWD64_EXPAND(hw,0)|HKWD64_TMASK, \
		  MTRC_RARE)
#define MTRCHKL1T_RARE(hw,a) \
	mtrchook1_pre(HKWD64_EXPAND(hw,8)|HKWD64_TMASK, \
		  (ulong_t)(a), \
		  MTRC_RARE)
#define MTRCHKL2T_RARE(hw,a,b) \
        mtrchook2_pre(HKWD64_EXPAND(hw,16)|HKWD64_TMASK, \
		  (ulong_t)(a),(ulong_t)(b), \
		  MTRC_RARE)
#define MTRCHKL3T_RARE(hw,a,b,c) \
        mtrchook3_pre(HKWD64_EXPAND(hw,24)|HKWD64_TMASK, \
		  (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		  MTRC_RARE)
#define MTRCHKL4T_RARE(hw,a,b,c,d) \
        mtrchook4_pre(HKWD64_EXPAND(hw,32)|HKWD64_TMASK, \
		  (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		  (ulong_t)(d), \
		  MTRC_RARE)
#define MTRCHKL5T_RARE(hw,a,b,c,d,e) \
        mtrchook5_pre(HKWD64_EXPAND(hw,40)|HKWD64_TMASK, \
		  (ulong_t)(a),(ulong_t)(b),(ulong_t)(c), \
		  (ulong_t)(d),(ulong_t)(e), \
		  MTRC_RARE)

#else /* !__64BIT_KERNEL */

#define TRCHK(hw) \
        mtrchook0(_TRCTMASK(hw)|HKTY_S, \
		  MTRC_COMMON|MTRC_SYSTEM)
#define TRCHKL(hw,a) \
        mtrchook1(_TRCTMASK(hw)|HKTY_L, \
                  (ulong_t)(a), \
		  MTRC_COMMON|MTRC_SYSTEM)
#define TRCHKG(hw,a,b,c,d,e) \
        mtrchook5(_TRCTMASK(hw)|HKTY_G, \
                  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), \
                  (ulong_t)(d),(ulong_t)(e), \
		  MTRC_COMMON|MTRC_SYSTEM)
#define TRCHKT(hw) \
        mtrchook0(_TRCTMASK(hw)|HKTY_ST, \
		  MTRC_COMMON|MTRC_SYSTEM)
#define TRCHKLT(hw,a) \
        mtrchook1(_TRCTMASK(hw)|HKTY_LT, \
                  (ulong_t)(a), \
		  MTRC_COMMON|MTRC_SYSTEM)
#define TRCHKGT(hw,a,b,c,d,e) \
        mtrchook5(_TRCTMASK(hw)|HKTY_GT, \
                  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), \
                  (ulong_t)(d),(ulong_t)(e), \
		  MTRC_COMMON|MTRC_SYSTEM)

#define TRCHK_RARE(hw) \
        mtrchook0_pre(_TRCTMASK(hw)|HKTY_S, \
		  MTRC_RARE|MTRC_SYSTEM)                
#define TRCHKL_RARE(hw,a)  \
        mtrchook1_pre(_TRCTMASK(hw)|HKTY_L, \
                  (ulong_t)(a), \
		  MTRC_RARE|MTRC_SYSTEM)            
#define TRCHKG_RARE(hw,a,b,c,d,e) \
        mtrchook5_pre(_TRCTMASK(hw)|HKTY_G, \
                  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), \
                  (ulong_t)(d),(ulong_t)(e), \
		  MTRC_RARE|MTRC_SYSTEM)     
#define TRCHKT_RARE(hw) \
        mtrchook0_pre(_TRCTMASK(hw)|HKTY_ST, \
		  MTRC_RARE|MTRC_SYSTEM)
#define TRCHKLT_RARE(hw,a) \
        mtrchook1_pre(_TRCTMASK(hw)|HKTY_LT, \
                  (ulong_t)(a), \
		  MTRC_RARE|MTRC_SYSTEM)
#define TRCHKGT_RARE(hw,a,b,c,d,e)  \
        mtrchook5_pre(_TRCTMASK(hw)|HKTY_GT, \
                  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), \
                  (ulong_t)(d),(ulong_t)(e), \
		  MTRC_RARE|MTRC_SYSTEM)   

#define TRCHK_NOMTRC(hw) (TRC_ISON(0) ? \
	(void) __TRCHOOK((long)(_TRCTMASK(hw)|HKTY_S)) : \
	(void) 0)
#define TRCHKL_NOMTRC(hw,a) (TRC_ISON(0) ? \
	(void) __TRCHOOK((long)(_TRCTMASK(hw)|HKTY_L), (long)(a)) : \
	(void) 0)
#define TRCHKG_NOMTRC(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __TRCHOOK((long)(_TRCTMASK(hw)|HKTY_G),\
	  (long)(a), (long)(b), (long)(c), (long)(d), (long)(e)) : \
	(void) 0)
#define TRCHKT_NOMTRC(hw) (TRC_ISON(0) ? \
	(void) __TRCHOOK((long)(_TRCTMASK(hw)|HKTY_ST)) : \
	(void) 0)
#define TRCHKLT_NOMTRC(hw,a) (TRC_ISON(0) ? \
	(void) __TRCHOOK((long)(_TRCTMASK(hw)|HKTY_LT), (long)(a)) : \
	(void) 0)
#define TRCHKGT_NOMTRC(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __TRCHOOK((long)(_TRCTMASK(hw)|HKTY_GT),\
	  (long)(a), (long)(b), (long)(c), (long)(d), (long)(e)) :\
	(void) 0)

#define MTRCHKT(hw) \
        mtrchook0(_TRCTMASK(hw)|HKTY_ST, \
		  MTRC_COMMON)
#define MTRCHKLT(hw,a) \
        mtrchook1(_TRCTMASK(hw)|HKTY_LT, \
                  (ulong_t)(a), \
		  MTRC_COMMON)
#define MTRCHKGT(hw,a,b,c,d,e) \
        mtrchook5(_TRCTMASK(hw)|HKTY_GT, \
                  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), \
                  (ulong_t)(d),(ulong_t)(e), \
		  MTRC_COMMON)

#define MTRCHKT_RARE(hw) \
        mtrchook0_pre(_TRCTMASK(hw)|HKTY_ST, \
		  MTRC_RARE)
#define MTRCHKLT_RARE(hw,a) \
        mtrchook1_pre(_TRCTMASK(hw)|HKTY_LT, \
                  (ulong_t)(a), \
		  MTRC_RARE)
#define MTRCHKGT_RARE(hw,a,b,c,d,e) \
        mtrchook5_pre(_TRCTMASK(hw)|HKTY_GT, \
                  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), \
                  (ulong_t)(d),(ulong_t)(e), \
		  MTRC_RARE)

#endif /* __64BIT_KERNEL */

#else  /* __MTRACE */
/* Define memory trace related macros to their non-LMT equivalent */
#ifdef __64BIT_KERNEL

#define TRCHKL0_RARE(hw) TRCHKL0(hw)
#define TRCHKL1_RARE(hw,a) TRCHKL1(hw,a)
#define TRCHKL2_RARE(hw,a,b) TRCHKL2(hw,a,b)
#define TRCHKL3_RARE(hw,a,b,c) TRCHKL3(hw,a,b,c)
#define TRCHKL4_RARE(hw,a,b,c,d) TRCHKL4(hw,a,b,c,d)
#define TRCHKL5_RARE(hw,a,b,c,d,e) TRCHKL5(hw,a,b,c,d,e)

#define TRCHKL0T_RARE(hw) TRCHKL0T(hw)
#define TRCHKL1T_RARE(hw,a) TRCHKL1T(hw,a)
#define TRCHKL2T_RARE(hw,a,b) TRCHKL2T(hw,a,b)
#define TRCHKL3T_RARE(hw,a,b,c) TRCHKL3T(hw,a,b,c)
#define TRCHKL4T_RARE(hw,a,b,c,d) TRCHKL4T(hw,a,b,c,d)
#define TRCHKL5T_RARE(hw,a,b,c,d,e) TRCHKL5T(hw,a,b,c,d,e)

#define TRCHKL0_NOMTRC(hw) TRCHKL0(hw)
#define TRCHKL1_NOMTRC(hw,a) TRCHKL1(hw,a)
#define TRCHKL2_NOMTRC(hw,a,b) TRCHKL2(hw,a,b)
#define TRCHKL3_NOMTRC(hw,a,b,c) TRCHKL3(hw,a,b,c)
#define TRCHKL4_NOMTRC(hw,a,b,c,d) TRCHKL4(hw,a,b,c,d)
#define TRCHKL5_NOMTRC(hw,a,b,c,d,e) TRCHKL5(hw,a,b,c,d,e)

#define TRCHKL0T_NOMTRC(hw) TRCHKL0T(hw)
#define TRCHKL1T_NOMTRC(hw,a) TRCHKL1T(hw,a)
#define TRCHKL2T_NOMTRC(hw,a,b) TRCHKL2T(hw,a,b)
#define TRCHKL3T_NOMTRC(hw,a,b,c) TRCHKL3T(hw,a,b,c)
#define TRCHKL4T_NOMTRC(hw,a,b,c,d) TRCHKL4T(hw,a,b,c,d)
#define TRCHKL5T_NOMTRC(hw,a,b,c,d,e) TRCHKL5T(hw,a,b,c,d,e)

#define MTRCHKL0T(hw)
#define MTRCHKL1T(hw,a)
#define MTRCHKL2T(hw,a,b)
#define MTRCHKL3T(hw,a,b,c)
#define MTRCHKL4T(hw,a,b,c,d)
#define MTRCHKL5T(hw,a,b,c,d,e)

#define MTRCHKL0T_RARE(hw)
#define MTRCHKL1T_RARE(hw,a)
#define MTRCHKL2T_RARE(hw,a,b)
#define MTRCHKL3T_RARE(hw,a,b,c)
#define MTRCHKL4T_RARE(hw,a,b,c,d)
#define MTRCHKL5T_RARE(hw,a,b,c,d,e)

#else  /* __64BIT_KERNEL */

#define TRCHK_RARE(hw) TRCHK(hw)
#define TRCHKL_RARE(hw,a) TRCHKL(hw, a)
#define TRCHKG_RARE(hw,a,b,c,d,e) TRCHKG(hw, a, b, c, d, e)

#define TRCHKT_RARE(hw) TRCHKT(hw)
#define TRCHKLT_RARE(hw,a) TRCHKLT(hw, a)
#define TRCHKGT_RARE(hw,a,b,c,d,e) TRCHKGT(hw, a, b, c, d, e)

#define TRCHK_NOMTRC(hw) TRCHK(hw)
#define TRCHKL_NOMTRC(hw,a) TRCHKL(hw, a)
#define TRCHKG_NOMTRC(hw,a,b,c,d,e) TRCHKG(hw, a, b, c, d, e)

#define TRCHKT_NOMTRC(hw) TRCHKT(hw)
#define TRCHKLT_NOMTRC(hw,a) TRCHKLT(hw, a)
#define TRCHKGT_NOMTRC(hw,a,b,c,d,e) TRCHKGT(hw, a, b, c, d, e)

#define MTRCHKT(hw)
#define MTRCHKLT(hw,a)
#define MTRCHKGT(hw,a,b,c,d,e)

#define MTRCHKT_RARE(hw)
#define MTRCHKLT_RARE(hw,a)
#define MTRCHKGT_RARE(hw,a,b,c,d,e)

#endif /* __64BIT_KERNEL */

#endif /* __MTRACE */

/* Define 32b kernel macros equivalent to 64b kernel macros and vice-versa */
#ifdef __64BIT_KERNEL

#define TRCHK_RARE(hw) TRCHKL0_RARE(hw)
#define TRCHKL_RARE(hw,a) TRCHKL1_RARE(hw, a)
#define TRCHKG_RARE(hw,a,b,c,d,e) TRCHKL5_RARE(hw, a, b, c, d, e)

#define TRCHKT_RARE(hw) TRCHKL0T_RARE(hw)
#define TRCHKLT_RARE(hw,a) TRCHKL1T_RARE(hw, a)
#define TRCHKGT_RARE(hw,a,b,c,d,e) TRCHKL5T_RARE(hw, a, b, c, d, e)

#define TRCHK_NOMTRC(hw) TRCHKL0_NOMTRC(hw)
#define TRCHKL_NOMTRC(hw,a) TRCHKL1_NOMTRC(hw, a)
#define TRCHKG_NOMTRC(hw,a,b,c,d,e) TRCHKL5_NOMTRC(hw, a, b, c, d, e)

#define TRCHKT_NOMTRC(hw) TRCHKL0T_NOMTRC(hw)
#define TRCHKLT_NOMTRC(hw,a) TRCHKL1T_NOMTRC(hw, a)
#define TRCHKGT_NOMTRC(hw,a,b,c,d,e) TRCHKL5T_NOMTRC(hw, a, b, c, d, e)

#define MTRCHKT(hw) MTRCHKL0T(hw)
#define MTRCHKLT(hw,a) MTRCHKL1T(hw, a)
#define MTRCHKGT(hw,a,b,c,d,e) MTRCHKL5T(hw, a, b, c, d, e)

#define MTRCHKT_RARE(hw) MTRCHKL0T_RARE(hw)
#define MTRCHKLT_RARE(hw,a) MTRCHKL1T_RARE(hw, a)
#define MTRCHKGT_RARE(hw,a,b,c,d,e) MTRCHKL5T_RARE(hw, a, b, c, d, e)

#else  /* __64BIT_KERNEL */

#define TRCHKL0_RARE(hw) TRCHK_RARE(hw)
#define TRCHKL1_RARE(hw,D1) TRCHKL_RARE(hw,D1)
#define TRCHKL2_RARE(hw,D1,D2) TRCHKG_RARE(hw,D1,D2,0,0,0)
#define TRCHKL3_RARE(hw,D1,D2,D3) TRCHKG_RARE(hw,D1,D2,D3,0,0)
#define TRCHKL4_RARE(hw,D1,D2,D3,D4) TRCHKG_RARE(hw,D1,D2,D3,D4,0)
#define TRCHKL5_RARE(hw,D1,D2,D3,D4,D5) TRCHKG_RARE(hw,D1,D2,D3,D4,D5)

#define TRCHKL0T_RARE(hw) TRCHKT_RARE(hw)
#define TRCHKL1T_RARE(hw,D1) TRCHKLT_RARE(hw,D1)
#define TRCHKL2T_RARE(hw,D1,D2) TRCHKGT_RARE(hw,D1,D2,0,0,0)
#define TRCHKL3T_RARE(hw,D1,D2,D3) TRCHKGT_RARE(hw,D1,D2,D3,0,0)
#define TRCHKL4T_RARE(hw,D1,D2,D3,D4) TRCHKGT_RARE(hw,D1,D2,D3,D4,0)
#define TRCHKL5T_RARE(hw,D1,D2,D3,D4,D5) TRCHKGT_RARE(hw,D1,D2,D3,D4,D5)

#define TRCHKL0_NOMTRC(hw) TRCHK_NOMTRC(hw)
#define TRCHKL1_NOMTRC(hw,D1) TRCHKL_NOMTRC(hw,D1)
#define TRCHKL2_NOMTRC(hw,D1,D2) TRCHKG_NOMTRC(hw,D1,D2,0,0,0)
#define TRCHKL3_NOMTRC(hw,D1,D2,D3) TRCHKG_NOMTRC(hw,D1,D2,D3,0,0)
#define TRCHKL4_NOMTRC(hw,D1,D2,D3,D4) TRCHKG_NOMTRC(hw,D1,D2,D3,D4,0)
#define TRCHKL5_NOMTRC(hw,D1,D2,D3,D4,D5) TRCHKG_NOMTRC(hw,D1,D2,D3,D4,D5)

#define TRCHKL0T_NOMTRC(hw) TRCHKT_NOMTRC(hw)
#define TRCHKL1T_NOMTRC(hw,D1) TRCHKLT_NOMTRC(hw,D1)
#define TRCHKL2T_NOMTRC(hw,D1,D2) TRCHKGT_NOMTRC(hw,D1,D2,0,0,0)
#define TRCHKL3T_NOMTRC(hw,D1,D2,D3) TRCHKGT_NOMTRC(hw,D1,D2,D3,0,0)
#define TRCHKL4T_NOMTRC(hw,D1,D2,D3,D4) TRCHKGT_NOMTRC(hw,D1,D2,D3,D4,0)
#define TRCHKL5T_NOMTRC(hw,D1,D2,D3,D4,D5) TRCHKGT_NOMTRC(hw,D1,D2,D3,D4,D5)

#define MTRCHKL0T(hw) MTRCHKT(hw)
#define MTRCHKL1T(hw,D1) MTRCHKLT(hw,D1)
#define MTRCHKL2T(hw,D1,D2) MTRCHKGT(hw,D1,D2,0,0,0)
#define MTRCHKL3T(hw,D1,D2,D3) MTRCHKGT(hw,D1,D2,D3,0,0)
#define MTRCHKL4T(hw,D1,D2,D3,D4) MTRCHKGT(hw,D1,D2,D3,D4,0)
#define MTRCHKL5T(hw,D1,D2,D3,D4,D5) MTRCHKGT(hw,D1,D2,D3,D4,D5)

#define MTRCHKL0T_RARE(hw) MTRCHKT_RARE(hw)
#define MTRCHKL1T_RARE(hw,D1) MTRCHKLT_RARE(hw,D1)
#define MTRCHKL2T_RARE(hw,D1,D2) MTRCHKGT_RARE(hw,D1,D2,0,0,0)
#define MTRCHKL3T_RARE(hw,D1,D2,D3) MTRCHKGT_RARE(hw,D1,D2,D3,0,0)
#define MTRCHKL4T_RARE(hw,D1,D2,D3,D4) MTRCHKGT_RARE(hw,D1,D2,D3,D4,0)
#define MTRCHKL5T_RARE(hw,D1,D2,D3,D4,D5) MTRCHKGT_RARE(hw,D1,D2,D3,D4,D5)

#endif  /* __64BIT_KERNEL */


#else /* !_KERNEL */

/*
 * Recompiled apps get these routines.
 * If not recompiled, apps use the old utrchook.
 */
#ifdef __64BIT__
/* Old 64-bit apps use an old-format hookword.  Newly compiled apps
 * get utrchook64.
 */
#define __UTRCHOOK utrchook64
#else /* !__64BIT__ */
/* There's no significant gain from having a utrchook32. */
#define __UTRCHOOK utrchook
#endif
#define __TRCGENCALL trcgen
#define __TRCGENTCALL trcgent

#ifdef _NO_PROTO
/* This is the main trace hook routine.  */
extern void __UTRCHOOK();
/* These are the generic trace hook system calls. */
extern void __TRCGENCALL();
extern void __TRCGENTCALL();

extern int trcon();
extern int trcoff();
extern int trcstart();
extern int trcstop();
extern int trc_ishookon();
#else /* !_NO_PROTO */
#ifdef __64BIT__
/* This is the main trace hook routine.  */
extern void __UTRCHOOK(ulong_t hkwd, ulong_t d1, ulong_t d2, ulong_t d3,
	ulong_t d4, ulong_t d5);
/* These are the generic trace hook system calls. */
extern void __TRCGENCALL(int chan, ulong_t hkwd, ulong_t dword,
	uint len, char * buf);
extern void __TRCGENTCALL(int chan, ulong_t hkwd, ulong_t dword,
	uint len, char * buf);
#else /* !__64BIT__ */
/* This is the main trace hook routine.  */
extern void __UTRCHOOK(unsigned int hkwd, unsigned int d1,
	unsigned int d2, unsigned int d3, unsigned int d4,
	unsigned int d5);
/* These are the generic trace hook system calls. */
extern void __TRCGENCALL(int chan, unsigned int hkwd, unsigned int dword,
		unsigned int len, char * buf);
extern void __TRCGENTCALL(int chan, unsigned int hkwd, unsigned int dword,
		unsigned int len, char * buf);
#endif /* __64BIT__ */

/* These have the same prototypes in either environment. */
extern int trcon(int chan);
extern int trcoff(int chan);
extern int trcstart(char * str);
extern int trcstop(int chan);
extern int trc_ishookon(int chan, ulong_t hkwd);
#endif /* _NO_PROTO */

/* User-level trace hooks use the main trace hook routine, UTRCHOOK.
 * The call is avoided if trace is off for channel 0.
 */
#ifdef __64BIT__
#ifdef _NO_PROTO
#define TRCHKL0(hw) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,0)) : \
	(void) 0)
#define TRCHKL0T(hw) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,0) | HKWD64_TMASK) : \
	(void) 0)
#define TRCHKL1(hw,a) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,8), a) : \
	(void) 0)
#define TRCHKL1T(hw,a)	(TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,8) | HKWD64_TMASK, a) : \
	(void) 0)
#define TRCHKL2(hw,a,b) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,16), a, b) : \
	(void) 0)
#define TRCHKL2T(hw,a,b) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,16) | HKWD64_TMASK, a, b) : \
	(void) 0)
#define TRCHKL3(hw,a,b,c) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,24), a, b, c) : \
	(void) 0)
#define TRCHKL3T(hw,a,b,c) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,24) | HKWD64_TMASK, a, b, c) : \
	(void) 0)
#define TRCHKL4(hw,a,b,c,d) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,32), a, b, c, d) : \
	(void) 0)
#define TRCHKL4T(hw,a,b,c,d) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,32) | HKWD64_TMASK, a, b, c, d) : \
	(void) 0)
#define TRCHKL5(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,40), a, b, c, d, e) : \
	(void) 0)
#define TRCHKL5T(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,40) | HKWD64_TMASK, a, b, c, d, e) : \
	(void) 0)
#else /* !_NO_PROTO */
#define TRCHKL0(hw) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,0),0,0,0,0,0) : \
	(void) 0)
#define TRCHKL0T(hw) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,0) | HKWD64_TMASK ,0,0,0,0,0) : \
	(void) 0)
#define TRCHKL1(hw,a) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,8), (ulong_t)(a), 0,0,0,0) : \
	(void) 0)
#define TRCHKL1T(hw,a)	(TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,8) | HKWD64_TMASK,\
	  (ulong_t)(a), 0,0,0,0) : \
	(void) 0)
#define TRCHKL2(hw,a,b) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,16), \
	  (ulong_t)(a), (ulong_t)(b), 0, 0, 0) : \
	(void) 0)
#define TRCHKL2T(hw,a,b) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,16) | HKWD64_TMASK, \
	  (ulong_t)(a), (ulong_t)(b), 0, 0, 0) : \
	(void) 0)
#define TRCHKL3(hw,a,b,c) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,24), \
	  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), 0, 0) : \
	(void) 0)
#define TRCHKL3T(hw,a,b,c) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,24) | HKWD64_TMASK,\
	  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), 0, 0) : \
	(void) 0)
#define TRCHKL4(hw,a,b,c,d) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,32),\
	  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), (ulong_t)(d), 0) : \
	(void) 0)
#define TRCHKL4T(hw,a,b,c,d) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,32) | HKWD64_TMASK,\
	  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), (ulong_t)(d), 0) : \
	(void) 0)
#define TRCHKL5(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,40),\
	  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), (ulong_t)(d),\
	    (ulong_t)(e)) : \
	(void) 0)
#define TRCHKL5T(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(HKWD64_EXPAND(hw,40) | HKWD64_TMASK,\
	  (ulong_t)(a), (ulong_t)(b), (ulong_t)(c), (ulong_t)(d),\
	    (ulong_t)(e)) :\
	(void) 0)
#endif /* _NO_PROTO */

/* Generic trace hook macros. */
#define TRCGEN(ch,hw,d1,len,buf)   (TRC_ISON(ch) ? \
	(void) __TRCGENCALL((int)(ch), (hw | HKWD64_GMASK), \
	  (ulong_t)(d1), (uint)(len), (char *)(buf)) : \
	(void) 0)
#define TRCGENT(ch,hw,d1,len,buf)  (TRC_ISON(ch) ? \
	(void) __TRCGENTCALL((int)(ch), (hw | HKWD64_GMASK), \
	  (ulong_t)(d1), (uint)(len), (char *)(buf)) : \
	(void) 0)
#else /* !__64BIT__ */
#ifdef _NO_PROTO
#define TRCHK(hw) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(_TRCTMASK(hw)|HKTY_S) : \
	(void) 0)
#define TRCHKT(hw) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(_TRCTMASK(hw)|HKTY_ST) : \
	(void) 0)
#define TRCHKL(hw,a) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(_TRCTMASK(hw)|HKTY_L,a) : \
	(void) 0)
#define TRCHKLT(hw,a) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(_TRCTMASK(hw)|HKTY_LT,a) : \
	(void) 0)
#define TRCHKG(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(_TRCTMASK(hw)|HKTY_G,a,b,c,d,e) : \
	(void) 0)
#define TRCHKGT(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(_TRCTMASK(hw)|HKTY_GT,a,b,c,d,e) :\
	(void) 0)
#else /* !_NO_PROTO */
#define TRCHK(hw) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(_TRCTMASK(hw)|HKTY_S,0,0,0,0,0) : \
	(void) 0)
#define TRCHKT(hw) (TRC_ISON(0) ? \
	(void)__UTRCHOOK(_TRCTMASK(hw)|HKTY_ST,0,0,0,0,0) : \
	(void) 0)
#define TRCHKL(hw,a) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(_TRCTMASK(hw)|HKTY_L, a, 0,0,0,0) : \
	(void) 0)
#define TRCHKLT(hw,a) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(_TRCTMASK(hw)|HKTY_LT,  a, 0,0,0,0) : \
	(void) 0)
#define TRCHKG(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(_TRCTMASK(hw)|HKTY_G, a, b, c, d, e) : \
	(void) 0)
#define TRCHKGT(hw,a,b,c,d,e) (TRC_ISON(0) ? \
	(void) __UTRCHOOK(_TRCTMASK(hw)|HKTY_GT, a, b, c, d, e) : \
	(void) 0)
#endif /* _NO_PROTO */

/* Generic trace hook macros. */
#define TRCGEN(ch,hw,d1,len,buf) (TRC_ISON(ch) ? \
	(void) __TRCGENCALL(ch,hw,d1,len,buf) : \
	(void) 0)
#define TRCGENT(ch,hw,d1,len,buf) (TRC_ISON(ch) ? \
	(void) __TRCGENTCALL(ch,hw,d1,len,buf) : \
	(void) 0)
#endif /* __64BIT__ */

#endif /* _KERNEL */

#ifndef __64BIT__
/*
 * These are the preferred macros.
 */
#define TRCHKL0(hw) TRCHK(hw)
#define TRCHKL1(hw,D1) TRCHKL(hw,D1)
#define TRCHKL2(hw,D1,D2) TRCHKG(hw,D1,D2,0,0,0)
#define TRCHKL3(hw,D1,D2,D3) TRCHKG(hw,D1,D2,D3,0,0)
#define TRCHKL4(hw,D1,D2,D3,D4) TRCHKG(hw,D1,D2,D3,D4,0)
#define TRCHKL5(hw,D1,D2,D3,D4,D5) TRCHKG(hw,D1,D2,D3,D4,D5)

#define TRCHKL0T(hw) TRCHKT(hw)
#define TRCHKL1T(hw,D1) TRCHKLT(hw,D1)
#define TRCHKL2T(hw,D1,D2) TRCHKGT(hw,D1,D2,0,0,0)
#define TRCHKL3T(hw,D1,D2,D3) TRCHKGT(hw,D1,D2,D3,0,0)
#define TRCHKL4T(hw,D1,D2,D3,D4) TRCHKGT(hw,D1,D2,D3,D4,0)
#define TRCHKL5T(hw,D1,D2,D3,D4,D5) TRCHKGT(hw,D1,D2,D3,D4,D5)
#else /* __64BIT__ */
#define TRCHK(hw) TRCHKL0(hw)
#define TRCHKL(hw,a) TRCHKL1(hw, a)
#define TRCHKG(hw,a,b,c,d,e) TRCHKL5(hw, a, b, c, d, e)

#define TRCHKT(hw) TRCHKL0T(hw)
#define TRCHKLT(hw,a) TRCHKL1T(hw, a)
#define TRCHKGT(hw,a,b,c,d,e) TRCHKL5T(hw, a, b, c, d, e)
#endif /* __64BIT__ */

/*
 * Old 64-bit trace macros.
 * These are maintained for compatability only.
 */
#ifdef __64BIT__
#define TRCHK64L1(hw,d1) TRCHKL1(hw, d1)
#define TRCHK64L2(hw,d1,d2) TRCHKL2(hw, d1, d2)
#define TRCHK64L1T(hw,d1) TRCHKL1T(hw, d1)
#define TRCHK64L2T(hw,d1,d2) TRCHKL2T(hw, d1, d2)
#else /* !__64BIT__ */
#define TRCHK64L1(hw,d1) TRCHKG(hw,__TRCHI64(d1),__TRCLOW64(d1),0,0,0)
#define TRCHK64L2(hw,d1,d2) TRCHKG(hw,__TRCHI64(d1),__TRCLOW64(d1),\
		__TRCHI64(d2),__TRCLOW64(d2),0)
#define TRCHK64L1T(hw,d1) TRCHKGT(hw,__TRCHI64(d1),__TRCLOW64(d1),0,0,0)
#define TRCHK64L2T(hw,d1,d2) TRCHKGT(hw,__TRCHI64(d1),__TRCLOW64(d1),\
		__TRCHI64(d2),__TRCLOW64(d2),0)
#endif /* __64BIT__ */

#ifndef __RASLIBRTN
/* Redefine calls to the old interfaces to call the correct routine.  */
#define trchk(hw) TRCHK(hw)
#define trchkt(hw) TRCHKT(hw)
#define trchkl(hw,a) TRCHKL(hw,a)
#define trchklt(hw,a) TRCHKLT(hw,a)
#define trchkg(hw,a,b,c,d,e) TRCHKG(hw,a,b,c,d,e)
#define trchkgt(hw,a,b,c,d,e) TRCHKGT(hw,a,b,c,d,e)
#endif /* __RASLIBRTN */

#endif /* _H_TRCMACROS */
