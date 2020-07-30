/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/pfmod.h 1.1                                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1995               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)41	1.1  src/bos/kernel/sys/pfmod.h, sysxpse, bos530 8/17/95 14:16:56  */
/*
 *   COMPONENT_NAME: sysxpse
 *
 *   FUNCTIONS: PF_ARG
 *		PF_CMD
 *		PF_OP
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * pfmod.h - packet filter module definitions
 */

#define	PFIOCSETF	(('P') << 8 | 1)

#define	MAXFILTERS	255

typedef struct packetfilt {
	uchar	Pf_Priority;		/* ignored this release */
	uchar	Pf_FilterLen;		/* number of commands in list */
	ushort	Pf_Filter[MAXFILTERS];	/* command list */
} pfilter_t;

/* filter command masks */
#define	PF_CMD(x)	(x & 0x7000)
#define	PF_OP(x)	(x & 0x0f00)
#define	PF_ARG(x)	(x & 0x00ff)

/*
 * commands
 */

#define	PF_NOPUSH	0x0000		/* do not push anything */
#define	PF_PUSHLIT	0x1000		/* push the next shortword */
#define	PF_PUSHZERO	0x2000		/* push 0x0000 */
#define	PF_PUSHONE	0x3000		/* push 0x0001 */
#define	PF_PUSHFFFF	0x4000		/* push 0xffff */
#define	PF_PUSHFF00	0x5000		/* push 0xff00 */
#define	PF_PUSH00FF	0x6000		/* push 0x00ff */
#define	PF_PUSHWORD	0x7000		/* push word 0-255 from packet */

/*
 * operators
 */

#define	PF_NOP		0x0000		/* do nothing */

/* logical */
#define	PF_EQ		0x0100		/* == */
#define	PF_NEQ		0x0200		/* != */
#define	PF_LT		0x0300		/* <  */
#define	PF_LE		0x0400		/* <= */
#define	PF_GT		0x0500		/* >  */
#define	PF_GE		0x0600		/* >= */

/* bitwise */
#define	PF_AND		0x0700		/* &  */
#define	PF_OR		0x0800		/* |  */
#define	PF_XOR		0x0900		/* ^  */

/* short-circuit (immediate accept/reject) */
#define	PF_COR		0x0a00		/* if == accept */
#define	PF_CNOR		0x0b00		/* if == reject */
#define	PF_CAND		0x0c00		/* if != reject */
#define	PF_CNAND	0x0d00		/* if != accept */

#ifdef	_SUN
/*
 * Sun(tm) porting compatibility only.
 * This is a generic Packet Filter (PF), not an EtherNet Filter (ENF).
 */

#define	ENMAXFILTERS	MAXFILTERS
#define	ENF_NOPUSH	PF_NOPUSH
#define	ENF_PUSHLIT	PF_PUSHLIT
#define	ENF_PUSHZERO	PF_PUSHZERO
#define	ENF_PUSHONE	PF_PUSHONE
#define	ENF_PUSHFFFF	PF_PUSHFFFF
#define	ENF_PUSHFF00	PF_PUSHFF00
#define	ENF_PUSH00FF	PF_PUSH00FF
#define	ENF_PUSHWORD	PF_PUSHWORD
#define	ENF_NOP		PF_NOP
#define	ENF_EQ		PF_EQ
#define	ENF_NEQ		PF_NEQ
#define	ENF_LT		PF_LT
#define	ENF_LE		PF_LE
#define	ENF_GT		PF_GT
#define	ENF_GE		PF_GE
#define	ENF_AND		PF_AND
#define	ENF_OR		PF_OR
#define	ENF_XOR		PF_XOR
#define	ENF_COR		PF_COR
#define	ENF_CNOR	PF_CNOR
#define	ENF_CAND	PF_CAND
#define	ENF_CNAND	PF_CNAND
#endif
