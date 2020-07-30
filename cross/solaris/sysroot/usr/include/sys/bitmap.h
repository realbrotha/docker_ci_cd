/*
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef _SYS_BITMAP_H
#define	_SYS_BITMAP_H

#pragma ident	"@(#)bitmap.h	1.25	05/01/16 SMI"	/* SVr4.0 1.6	*/

#ifdef	__cplusplus
extern "C" {
#endif

#include <sys/feature_tests.h>
#if defined(__GNUC__) && defined(_ASM_INLINES)
#include <asm/bitmap.h>
#endif

/*
 * Operations on bitmaps of arbitrary size
 * A bitmap is a vector of 1 or more ulong_t's.
 * The user of the package is responsible for range checks and keeping
 * track of sizes.
 */

#ifdef _LP64
#define	BT_ULSHIFT	6 /* log base 2 of BT_NBIPUL, to extract word index */
#define	BT_ULSHIFT32	5 /* log base 2 of BT_NBIPUL, to extract word index */
#else
#define	BT_ULSHIFT	5 /* log base 2 of BT_NBIPUL, to extract word index */
#endif

#define	BT_NBIPUL	(1 << BT_ULSHIFT)	/* n bits per ulong_t */
#define	BT_ULMASK	(BT_NBIPUL - 1)		/* to extract bit index */

#ifdef _LP64
#define	BT_NBIPUL32	(1 << BT_ULSHIFT32)	/* n bits per ulong_t */
#define	BT_ULMASK32	(BT_NBIPUL32 - 1)	/* to extract bit index */
#define	BT_ULMAXMASK	0xffffffffffffffff	/* used by bt_getlowbit */
#else
#define	BT_ULMAXMASK	0xffffffff
#endif

/*
 * bitmap is a ulong_t *, bitindex an index_t
 *
 * The macros BT_WIM and BT_BIW internal; there is no need
 * for users of this package to use them.
 */

/*
 * word in map
 */
#define	BT_WIM(bitmap, bitindex) \
	((bitmap)[(bitindex) >> BT_ULSHIFT])
/*
 * bit in word
 */
#define	BT_BIW(bitindex) \
	(1UL << ((bitindex) & BT_ULMASK))

#ifdef _LP64
#define	BT_WIM32(bitmap, bitindex) \
	((bitmap)[(bitindex) >> BT_ULSHIFT32])

#define	BT_BIW32(bitindex) \
	(1UL << ((bitindex) & BT_ULMASK32))
#endif

/*
 * These are public macros
 *
 * BT_BITOUL == n bits to n ulong_t's
 */
#define	BT_BITOUL(nbits) \
	(((nbits) + BT_NBIPUL - 1l) / BT_NBIPUL)
#define	BT_SIZEOFMAP(nbits) \
	(BT_BITOUL(nbits) * sizeof (ulong_t))
#define	BT_TEST(bitmap, bitindex) \
	((BT_WIM((bitmap), (bitindex)) & BT_BIW(bitindex)) ? 1 : 0)
#define	BT_SET(bitmap, bitindex) \
	{ BT_WIM((bitmap), (bitindex)) |= BT_BIW(bitindex); }
#define	BT_CLEAR(bitmap, bitindex) \
	{ BT_WIM((bitmap), (bitindex)) &= ~BT_BIW(bitindex); }

#ifdef _LP64
#define	BT_BITOUL32(nbits) \
	(((nbits) + BT_NBIPUL32 - 1l) / BT_NBIPUL32)
#define	BT_SIZEOFMAP32(nbits) \
	(BT_BITOUL32(nbits) * sizeof (uint_t))
#define	BT_TEST32(bitmap, bitindex) \
	((BT_WIM32((bitmap), (bitindex)) & BT_BIW32(bitindex)) ? 1 : 0)
#define	BT_SET32(bitmap, bitindex) \
	{ BT_WIM32((bitmap), (bitindex)) |= BT_BIW32(bitindex); }
#define	BT_CLEAR32(bitmap, bitindex) \
	{ BT_WIM32((bitmap), (bitindex)) &= ~BT_BIW32(bitindex); }
#endif /* _LP64 */


#if defined(_KERNEL) && !defined(_ASM)
#include <sys/atomic.h>

/*
 * return next available bit index from map with specified number of bits
 */
extern index_t	bt_availbit(ulong_t *bitmap, size_t nbits);
/*
 * find the highest order bit that is on, and is within or below
 * the word specified by wx
 */
extern int	bt_gethighbit(ulong_t *mapp, int wx);
extern int	bt_range(ulong_t *bitmap, size_t *pos1, size_t *pos2,
			size_t end_pos);
/*
 * Find highest and lowest one bit set.
 *	Returns bit number + 1 of bit that is set, otherwise returns 0.
 * Low order bit is 0, high order bit is 31.
 */
extern int	highbit(ulong_t);
extern int	lowbit(ulong_t);
extern int	bt_getlowbit(ulong_t *bitmap, size_t start, size_t stop);
extern void	bt_copy(ulong_t *, ulong_t *, ulong_t);

/*
 * find the parity
 */
extern int	odd_parity(ulong_t);

/*
 * Atomically set/clear bits
 * Atomic exclusive operations will set "result" to "-1"
 * if the bit is already set/cleared. "result" will be set
 * to 0 otherwise.
 */
#define	BT_ATOMIC_SET(bitmap, bitindex) \
	{ atomic_or_long(&(BT_WIM(bitmap, bitindex)), BT_BIW(bitindex)); }
#define	BT_ATOMIC_CLEAR(bitmap, bitindex) \
	{ atomic_and_long(&(BT_WIM(bitmap, bitindex)), ~BT_BIW(bitindex)); }

#define	BT_ATOMIC_SET_EXCL(bitmap, bitindex, result) \
	{ result = atomic_set_long_excl(&(BT_WIM(bitmap, bitindex)),	\
	    (bitindex) % BT_NBIPUL); }
#define	BT_ATOMIC_CLEAR_EXCL(bitmap, bitindex, result) \
	{ result = atomic_clear_long_excl(&(BT_WIM(bitmap, bitindex)),	\
	    (bitindex) % BT_NBIPUL); }

/*
 * Extracts bits between index h (high, inclusive) and l (low, exclusive) from
 * u, which must be an unsigned integer.
 */
#define	BITX(u, h, l)	(((u) >> (l)) & ((1LU << ((h) - (l) + 1LU)) - 1LU))

#endif	/* _KERNEL && !_ASM */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_BITMAP_H */
