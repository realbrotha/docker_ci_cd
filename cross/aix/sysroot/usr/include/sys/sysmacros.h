/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/sysmacros.h 1.26                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1990          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)50     1.26  src/bos/kernel/sys/sysmacros.h, sysios, bos530 7/25/02 19:28:37 */

/*
 * COMPONENT_NAME: (SYSIOS) IO subsystems
 *
 * ORIGINS: 3, 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1990
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_SYSMACROS
#define _H_SYSMACROS

#include <sys/types.h>
#include <sys/param.h>

/*
 * Some macros for units conversion
 */

/* Core clicks to segments and vice versa */
#if NCPS == 1
#define ctos(x) (x)
#define stoc(x) (x)
#else
#define ctos(x) (((x)+(NCPS-1))/NCPS)
#define	stoc(x) ((x)*NCPS)
#endif

/* Core clicks to disk blocks */
#if NCPD == 1
#define ctod(x) (x)
#else
#define ctod(x) (((x)+(NCPD-1))/NCPD)
#endif
#define bltoc(x) ((x)*NCPD)

/* inumber to disk address */
#ifdef INOSHIFT
#define itod(x) (daddr_t)(((unsigned)(x)+(2*INOPB-1))>>INOSHIFT)
#else
#define itod(x) (daddr_t)(((unsigned)(x)+(2*INOPB-1))/INOPB)
#endif

/* inumber to disk offset */
#ifdef INOSHIFT
#define itoo(x) (int)(((unsigned)(x)+(2*INOPB-1))&(INOPB-1))
#else
#define itoo(x) (int)(((unsigned)(x)+(2*INOPB-1))%INOPB)
#endif

/* clicks to bytes */
#ifdef BPCSHIFT
#define	ctob(x)	((x)<<BPCSHIFT)
#else
#define	ctob(x)	((x)*NBPC)
#endif

#ifdef __64BIT_KERNEL
/* bytes to clicks */
#ifdef BPCSHIFT
#define	btoc(x)	(((unsigned long)(x)+(NBPC-1))>>BPCSHIFT)
#define	btoct(x)	((unsigned long)(x)>>BPCSHIFT)
#else
#define	btoc(x)	(((unsigned long)(x)+(NBPC-1))/NBPC)
#define	btoct(x)	((unsigned long)(x)/NBPC)
#endif
#else
/* bytes to clicks */
#ifdef BPCSHIFT
#define	btoc(x)	(((unsigned )(x)+(NBPC-1))>>BPCSHIFT)
#define	btoct(x)	((unsigned )(x)>>BPCSHIFT)
#else
#define	btoc(x)	(((unsigned )(x)+(NBPC-1))/NBPC)
#define	btoct(x)	((unsigned )(x)/NBPC)
#endif
#endif /* __64BIT_KERNEL */

/*
 * Conversion from bytes to reporting block units, and from stat() block
 * units to reporting block units (and back).  Reporting block units are
 * used as the user interface unit for setting and getting file sizes.
 * These macros assume that the number of bytes represented in blocks
 * never exceeds the maximum file offset; i.e. LONG_MAX.  The macros also
 * assume that a positive value is being converted.
 */
#define	bytes2rblocks(x)	(((unsigned long)(x)+(1024-1))/1024)
#define	rblocks2bytes(x)	((unsigned long)(x)*1024)
#define	stblocks2rblocks(x)	(((unsigned long)(x)*UBSIZE+(1024-1))/1024)
#define	rblocks2stblocks(x)	(((unsigned long)(x)*1024+(UBSIZE-1))/UBSIZE)

/* The major(), minor(), and makedev() macros also exist in types.h for
   BSD compliance.  Any changes to these macros must also be made in
   types.h.
*/

/* major part of a device */
#define major(__x)        (int)((unsigned)(__x)>>16)
#define	bmajor(x)	(int)(((unsigned)x>>16) & 0x7FFF)
#define	brdev(x)	(x&0x7fffffff)

/* minor part of a device */
#define minor(__x)        (int)((__x)&0xFFFF)

/* make a device number */
#define	makedev(__x,__y)	(dev_t)(((__x)<<16) | (__y))


/*
 * Here is what the devno looks like in the 64-bit Kernel
 *
 * 
 * 
 *   +---------------------------------------------------------------+
 *   |V|R|      Major Number         |         Minor Number          |
 *   | |S|                           |                               |
 *   | |V|                          3|3                             6|
 *   |0|1|2                         1|2                             3|
 *   +---------------------------------------------------------------+
 *
 *        V = Version bit
 *                Must be 1
 *
 *        RSV = Reserved bit must be 0
 *
 *        Major = 30 bit major allowing up to 1 billion major numbers
 *
 *        Minor = 32 bit minor number allowing up to 4 billion minor numbers
 */

/*
 * Version bit for 64-bit devno
 */
#define DEVNO64 0x8000000000000000LL

/*
 * Extract major number from 64-bit devno
 */
#define major64(_devno) ((int)(((_devno) & 0x3FFFFFFF00000000LL) >> 32))

/*
 * Extract minor number from 64-bit devno
 */
#define minor64(_devno) ((int)((_devno) & 0x00000000FFFFFFFFLL))

/*
 * Make a 64-bit devno
 */
#define makedev64(_major, _minor)       \
	((dev64_t)(((long long)(_major) << 32LL) | \
		((long long)(_minor) & 0x00000000FFFFFFFFLL) | DEVNO64))


#ifdef _KERNEL
#define DEVNORSV 0x4000000000000000LL
#define DEV64TO32(_devno)       \
        ((dev32_t)((((_devno) & 0x0000FFFF00000000LL) >> 16) | \
		((_devno) & 0xFFFFLL)))

#define DEV32TO64(_devno)       \
        (dev64_t)((((_devno) & 0xFFFF0000LL) << 16LL) | \
		((_devno) & 0xFFFFLL) | DEVNO64)

#define DEV64is32(_devno) \
	(((((dev64_t)(_devno)) & 0xBFFF0000FFFF0000LL) == DEVNO64) ? 1 : 0)

#ifdef _KERNSYS
#define DEV64_valid(_devno) \
	((((((dev64_t)(_devno)) & (DEVNO64 | DEVNORSV)) >> 62) == 4) ? 1 : 0);
#endif


/*
 * See if devno is 64 or 32
 */
#define ISDEVNO64(_devno)  (((ulong)(_devno) & DEVNO64) ? TRUE : FALSE)

/*
 * Convert to 64-bit devno.  
 * Used by 64-bit drivers whose method passed in a 32-bit devno.
 */
/*
 * For DD source code simplicity, map the old to the new
 */
#ifdef __64BIT_KERNEL
#define	DEV32TODEV(_devno)	DEV32TO64(_devno)
#define	DEVTODEV32(_devno)	DEV64TO32(_devno)
#define major_num(_devno) major64(_devno)
#define minor_num(_devno) minor64(_devno)
#define makedevno(_major, _minor) makedev64(_major, _minor)
#else /* __64BIT_KERNEL */
#define	DEV32TODEV(_devno)	(_devno)
#define	DEVTODEV32(_devno)	(_devno)
#define major_num(_devno) major(_devno)
#define minor_num(_devno) minor(_devno)
#define makedevno(_major, _minor) makedev(_major, _minor)
#endif

#endif /* _KERNEL */

#ifdef __64BIT_KERNEL
/*
 * macro for converting from a 32-bit long to a 64-bit long.
 */
#define	LONG32TOLONG64(_l32)	((long)(int)(_l32))

/*
 * macro for converting an int pair to a long long.
 */
#define	INTSTOLLONG(_i1,_i2)	\
	((unsigned long long)(_i1) << 32LL | (unsigned long long)(_i2))

/*
 * macro for converting from a 32-bit int to a 64-bit long.
 */
#define INT32TOLONG64(_x) 	((long)(int)(_x))

#endif /* __64BIT_KERNEL */



#endif/* _H_SYSMACROS */
