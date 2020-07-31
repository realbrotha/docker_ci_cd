/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_AUXV_SPARC_H
#define	_SYS_AUXV_SPARC_H

#pragma ident	"@(#)auxv_SPARC.h	1.3	06/09/29 SMI"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Flags used to describe various instruction set extensions available
 * on different SPARC processors.
 *
 * [The first three are legacy descriptions.]
 */
#define	AV_SPARC_MUL32	0x0001	/* 32x32-bit smul/umul is efficient */
#define	AV_SPARC_DIV32	0x0002	/* 32x32-bit sdiv/udiv is efficient */
#define	AV_SPARC_FSMULD	0x0004	/* fsmuld is efficient */
#define	AV_SPARC_V8PLUS	0x0008	/* V9 instructions available to 32-bit apps */
#define	AV_SPARC_POPC	0x0010	/* popc is efficient */
#define	AV_SPARC_VIS	0x0020	/* VIS instruction set supported */
#define	AV_SPARC_VIS2	0x0040	/* VIS2 instruction set supported */
#define	AV_SPARC_ASI_BLK_INIT	0x0080	/* ASI_BLK_INIT_xxx ASI */
#define	AV_SPARC_FMAF	0x0100	/* Fused Multiply-Add */

#define	FMT_AV_SPARC	\
	"\20"		\
	"\11fmaf\10ASIBlkInit\7vis2\6vis\5popc\4v8plus\3fsmuld\2div32\1mul32"

/*
 * compatibility defines: Obsolete
 */
#define	AV_SPARC_HWMUL_32x32	AV_SPARC_MUL32
#define	AV_SPARC_HWDIV_32x32	AV_SPARC_DIV32
#define	AV_SPARC_HWFSMULD	AV_SPARC_FSMULD

#ifdef __cplusplus
}
#endif

#endif	/* !_SYS_AUXV_SPARC_H */