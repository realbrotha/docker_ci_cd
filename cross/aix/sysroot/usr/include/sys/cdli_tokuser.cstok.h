/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/cdli_tokuser.cstok.h 1.11                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,1999          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)44	1.11  src/bos/kernel/sys/cdli_tokuser.cstok.h, pcictok, bos530 9/8/99 13:50:58 */
/*  COMPONENT_NAME: pcictok
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27
 *
 *                    -- (                            when
 *   combined with the aggregated modules for this product)
 *   OBJECT CODE ONLY SOURCE MATERIALS
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1997
 *   All Rights Reserved
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#ifndef _H_CDLI_TOKUSER_CSTOK
#define _H_CDLI_TOKUSER_CSTOK

#include <sys/cdli_tokuser.h>
#include <sys/lockname.h>

struct tok_cs_stats
{
	uint	recv_overrun;		/* receive overrun counter */
	uint	xmit_underrun;		/* transmit underrun counter */
	uchar	micro_code_lvl[10];	/* micro code level on the adapter */
	uint	duplex;			/* full or half duplex indicator */
	uint	ring_speed;		/* 4 or 16 Meg ring speed indicator */
	uint	speed_selected;		/* ring speed chosen by user */
	uint	duplex_selected;	/* duplex chosen by user */
	uint	psw_txq_len;		/* number of packets outstanding in the
					 * priority software transmit queue 
					 */
	uint	phw_txq_len;		/* number of packets outstanding in the
					 * priority hardware transmit queue 
					 */
	uint	arifci_err;		/* number of ari or fci errors */
	uchar	open_fw_lvl[10];	/* Contains the firmware level for the
					 *  adapter.			
					 */
};
typedef struct tok_cs_stats tok_cs_stats_t;

struct cs_all_stats
{
	ndd_genstats_t	ndd_genstats;	/* common io statistics */
	tok_genstats_t	tok_genstats;	/* tokenring device specific 
					 * statistics 
					 */
	tok_cs_stats_t	tok_cs_stats;	/* cricketstick adapter specific 
					 * statistics 
					 */
};
typedef struct cs_all_stats cs_all_stats_t;

/* IBM PCI tokenring trace hook numbers */

#define HKWD_CS_XMIT		(0x2DA)           /* transmit events */
#define HKWD_CS_RECV		(0x2DB)           /* receive events  */
#define HKWD_CS_GEN		(0x2DC)           /* general events  */

/* 4 meg and 16 meg MTU sizes */

#define CS_4M_MAX_PACKET	(4446)		/* */
#define CS_16M_MAX_PACKET	(17774)		/* */

/* flag for the device_type field in the tok_genstats structure   */

#define TOK_CS			(0x7)    /* IBM Token-Ring Adapter 14103e00 */
#define TOK_SH			(0x8)    /* IBM High-Speed Token-Ring Adapter */
#define TOK_CS2			(0x9)    /* IBM Token-Ring Adapter 1410e500 */

#endif /* endif ! _H_CDLI_TOKUSER_CSTOK */
