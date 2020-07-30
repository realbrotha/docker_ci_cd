/*
 * Copyright (c) 1983,1987,1997-1998 by Sun Microsystems, Inc.
 * All rights reserved.
 */

#ifndef _SYS_MEMREG_H
#define	_SYS_MEMREG_H

#pragma ident	"@(#)memreg.h	1.23	98/01/06 SMI"	/* SunOS4.1.2 1.16 */

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Rasterop hardware registers.	 To do a rasterop set the
 * rasterop function in mrc_op.	 Clear mrc_pattern unless
 * a special pattern is desired.
 *
 * Set mrc_shift to cause the source to be properly
 * aligned with the destination:  if words are being processed
 * left-to-right, then mrc_shift should be a positive number
 * between 0 and 15 inclusive; if words are being processed
 * right-to-left, then mrc_shift should be a negative number
 * between -16 and -1 inclusive.  If the first source word
 * does not supply enough data to satisfy the first destination
 * words requirements then load mrc_source1 (in the left-to-right
 * case) or mcr_source2 (in the right-to-left case) with the
 * first source word.
 *
 * Load mrc_mask1 with a mask of the bits not contributed by
 * the first source word (if the width were large), i.e. a
 * mask of high-order bits.  Load mrc_mask2 with a mask of the
 * bits not contributed by the last source word, i.e. a mask
 * of low-order bits.  Set mrc_width to the number of words
 * in the destination line.
 *
 * Then enable the chip and stuff the data through it and
 * finally disable the chip.
 */
struct memropc {
	ushort_t mrc_dest;		/* destination register */
	ushort_t mrc_source1;		/* source1 register (right) */
	ushort_t mrc_source2;		/* source2 register (left) */
	ushort_t mrc_pattern;		/* pattern register */
	ushort_t mrc_mask1;		/* mask1 register */
	ushort_t mrc_mask2;		/* mask2 register */
	short	mrc_shift;		/* bit 0..3 shift count for source */
					/* bit 8    sourceload bit */
	short	mrc_op;			/* function */
	short	mrc_width;		/* word width */
	short	mrc_opcount;		/* counts down the width */
	short	mrc_decoderout;		/* decoder output */
	short	mrc_x11;		/* manual load destination (diag) */
	short	mrc_x12;		/* manual load source (diag) */
	short	mrc_x13;
	short	mrc_x14;
	short	mrc_x15;		/* flags register for applications */
};

/* note: these are not relevant to color boards */
#define	mrc_enable(mrc)		((mrc)->mrc_shift |= (ushort_t)0x100)
#define	mrc_disable(mrc)	((mrc)->mrc_shift &= ~(ushort_t)0x100)

/* macros for generating left (mask1) and right (mask2) masks */
#define	mrc_lmask(x)	((unsigned)0xffff0000 >> (x))
#define	mrc_rmask(x)	((unsigned)0x7fff >> (x))

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_MEMREG_H */
