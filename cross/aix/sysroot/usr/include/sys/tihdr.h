/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/tihdr.h 1.10                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1991,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)43     1.10  src/bos/kernel/sys/tihdr.h, sysxpse, bos530 4/22/03 15:43:05 */
/*
 *   COMPONENT_NAME: SYSXPSE
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 18,27,63
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1991,1994
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 *   (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC.
 *   All Rights Reserved
 *
 *   Copyright (c) 1989  Mentat Inc.
 */

#ifndef _TIHDR_H
#define _TIHDR_H

#ifndef _T_SCALAR_DEF
#ifdef __64BIT__
typedef signed int      t_scalar_t;
typedef unsigned int    t_uscalar_t;
#else
typedef signed long     t_scalar_t;
typedef unsigned long   t_uscalar_t;
#endif /* __64BIT__ */
#define _T_SCALAR_DEF
#endif

/* User generated requests */
#define	T_BIND_REQ		1	/* Bind request			*/
#define	T_CONN_REQ		2	/* Connection request		*/
#define	T_CONN_RES		3	/* Connection response		*/
#define	T_DATA_REQ		4	/* Data request			*/
#define	T_DISCON_REQ		5	/* Disconnect request		*/
#define	T_EXDATA_REQ		6	/* Expedited data request	*/
#define	T_INFO_REQ		7	/* Information request		*/
#define	T_OPTMGMT_REQ		8	/* Option management request	*/
#define	T_ORDREL_REQ		9	/* Orderly release request	*/
#define	T_UNBIND_REQ		10	/* Unbind request		*/
#define	T_UNITDATA_REQ		11	/* Unitdata (datagram) request	*/
#define	T_ADDR_REQ		12	/* Bound/peer address request	*/
#define	T_FEEDBACK_REQ		19	/* Used internally		*/

/* Transport generated indications and acknowledgements */
#define	T_BIND_ACK		20	/* Bind acknowledgement		*/
#define	T_CONN_CON		21	/* Connection confirmation	*/
#define	T_CONN_IND		22	/* Connection indication	*/
#define	T_DATA_IND		23	/* Data indication		*/
#define	T_DISCON_IND		24	/* Disconnect indication	*/
#define	T_ERROR_ACK		25	/* Error acknowledgement	*/
#define	T_EXDATA_IND		26	/* Expedited data indication	*/
#define	T_INFO_ACK		27	/* Information acknowledgement	*/
#define	T_OK_ACK		28	/* OK acknowledgement		*/
#define	T_OPTMGMT_ACK		29	/* Option management ack.	*/
#define	T_ORDREL_IND		30	/* Orderly release indication	*/
#define	T_UNITDATA_IND		31	/* Unitdata (datagram) ind.	*/
#define	T_UDERROR_IND		32	/* Unitdata error indication	*/
#define	T_ADDR_ACK		33	/* Bound/peer address ack.	*/

/* State values */
#define	TS_UNINIT		0	/* uninitialized		*/
#define	TS_UNBND		1	/* Unbound			*/
#define	TS_WACK_BREQ		2	/* Wait for ack of BIND_REQ	*/
#define	TS_WACK_UREQ		3	/* Wait for ack of UNBIND_REQ	*/
#define	TS_IDLE			4	/* Ho hum			*/
#define	TS_WACK_OPTREQ		5	/* Wait for ack of OPTMGMT_REQ	*/
#define	TS_WACK_CREQ		6	/* Wait for ack of CONN_REQ	*/
#define	TS_WCON_CREQ		7	/* Wait for confirm of CONN_REQ	*/
#define	TS_WRES_CIND		8	/* Wait for response to CONN_IND*/
#define	TS_WACK_CRES		9	/* Wait for ack of CONN_RES	*/
#define	TS_DATA_XFER		10	/* Data transfer		*/
#define	TS_WIND_ORDREL		11	/* Indication of RD/!WR release	*/
#define	TS_WREQ_ORDREL		12	/* Request for WR/!RD release	*/
#define	TS_WACK_DREQ6		13	/* Wait for DISCON_REQ ack	*/
#define	TS_WACK_DREQ7		14	/* ...				*/
#define	TS_WACK_DREQ9		15	/* ...				*/
#define	TS_WACK_DREQ10		16	/* ...				*/
#define	TS_WACK_DREQ11		17	/* ...				*/
#define	TS_WACK_ORDREL		18	/* Used internally (only?)	*/
#define TS_NOSTATES		19	/* Includes "missing" 0 */

/* Transport events */
#define	TE_BIND_REQ		1	/* Bind request			*/
#define	TE_UNBIND_REQ		2	/* Unbind request		*/
#define	TE_OPTMGMT_REQ		3	/* Option management request	*/
#define	TE_BIND_ACK		4	/* Bind acknowledgement		*/
#define	TE_OPTMGMT_ACK		5	/* Option management ack.	*/
#define	TE_CONN_REQ		6	/* Connect request		*/
#define	TE_CONN_RES		7	/* Connect response		*/
#define	TE_DISCON_REQ		8	/* Disconnect request		*/
#define	TE_DATA_REQ		9	/* Data request			*/
#define	TE_EXDATA_REQ		10	/* Expedited data request	*/
#define	TE_ORDREL_REQ		11	/* Orderly release request	*/
#define	TE_CONN_IND		12	/* Connect indication		*/
#define	TE_CONN_CON		13	/* Connect confirmation		*/
#define	TE_DATA_IND		14	/* Data indication		*/
#define	TE_EXDATA_IND		15	/* Expedited data indication	*/
#define	TE_ORDREL_IND		16	/* Orderly release indication	*/
#define	TE_DISCON_IND1		17	/* Disconnect indication seq 0	*/
#define	TE_DISCON_IND2		18	/* Disconnect indication seq 1	*/
#define	TE_DISCON_IND3		19	/* Disconnect indication seq >1	*/
#define	TE_ERROR_ACK		20	/* Error acknowledgement	*/
#define	TE_OK_ACK1		21	/* OK acknowledgement seq 0	*/
#define	TE_OK_ACK2		22	/* OK acknowledgement seq 1 q=r	*/
#define	TE_OK_ACK3		23	/* OK acknowledgement seq 1 q!=r*/
#define	TE_OK_ACK4		24	/* OK acknowledgement seq >1	*/
#define TE_PASS_CONN		25	/* Pass connection		*/
#define	TE_UNITDATA_REQ		26	/* Unitdata (datagram) request	*/
#define	TE_UNITDATA_IND		27	/* Unitdata indication		*/
#define	TE_UDERROR_IND		28	/* Unitdata error indication	*/

#define TE_NOEVENTS		29	/* Includes "missing" 0 */

/* TLI library constant */
#define TLI_STACK_BUF_SIZE	512

struct T_bind_ack {
	t_scalar_t	PRIM_type;	/* Always T_BIND_ACK */
	t_scalar_t	ADDR_length;
	t_scalar_t	ADDR_offset;
	t_uscalar_t 	CONIND_number;
};

struct T_bind_req {
	t_scalar_t	PRIM_type;	/* Always T_BIND_REQ */
	t_scalar_t	ADDR_length;
	t_scalar_t	ADDR_offset;
	t_uscalar_t 	CONIND_number;
};

struct T_addr_req {
	t_scalar_t	PRIM_type;	/* Always T_ADDR_REQ */
};

struct T_addr_ack {
	t_scalar_t	PRIM_type;	/* Always T_ADDR_ACK */
	t_scalar_t	LOCADDR_length; 
	t_scalar_t	LOCADDR_offset; 
	t_scalar_t	REMADDR_length; 
	t_scalar_t	REMADDR_offset; 
};

struct T_conn_con {
	t_scalar_t	PRIM_type;	/* Always T_CONN_CON */
	t_scalar_t	RES_length;	/* Responding address length */
	t_scalar_t	RES_offset;
	t_scalar_t	OPT_length;
	t_scalar_t	OPT_offset;
};

struct T_conn_ind {
	t_scalar_t	PRIM_type;	/* Always T_CONN_IND */
	t_scalar_t	SRC_length;
	t_scalar_t	SRC_offset;
	t_scalar_t	OPT_length;
	t_scalar_t	OPT_offset;
	t_scalar_t	SEQ_number;
};

struct T_conn_req {
	t_scalar_t	PRIM_type;	/* Always T_CONN_REQ */
	t_scalar_t	DEST_length;
	t_scalar_t	DEST_offset;
	t_scalar_t	OPT_length;
	t_scalar_t	OPT_offset;
};

struct T_conn_res {
	t_scalar_t	PRIM_type;	/* Always T_CONN_RES */
	t_uscalar_t	ACCEPTOR_id;
	t_scalar_t	OPT_length;
	t_scalar_t	OPT_offset;
	t_scalar_t	SEQ_number;
};

struct T_data_ind {
	t_scalar_t	PRIM_type;	/* Always T_DATA_IND */
	t_scalar_t	MORE_flag;
};

struct T_data_req {
	t_scalar_t	PRIM_type;	/* Always T_DATA_REQ */
	t_scalar_t	MORE_flag;
};

struct T_discon_ind {
	t_scalar_t	PRIM_type;	/* Always T_DISCON_IND */
	t_scalar_t	DISCON_reason;
	t_scalar_t	SEQ_number;
};

struct T_discon_req {
	t_scalar_t	PRIM_type;	/* Always T_DISCON_REQ */
	t_scalar_t	SEQ_number;
};

struct T_exdata_ind {
	t_scalar_t	PRIM_type;	/* Always T_EXDATA_IND */
	t_scalar_t	MORE_flag;
};

struct T_exdata_req {
	t_scalar_t	PRIM_type;	/* Always T_EXDATA_REQ */
	t_scalar_t	MORE_flag;
};

struct T_error_ack {
	t_scalar_t	PRIM_type;	/* Always T_ERROR_ACK */
	t_scalar_t	ERROR_prim;	/* Primitive in error */
	t_scalar_t	TLI_error;
	t_scalar_t	UNIX_error;
};

struct T_info_ack {
	t_scalar_t	PRIM_type;	/* Always T_INFO_ACK */
	t_scalar_t	TSDU_size;	/* Max TSDU size */
	t_scalar_t	ETSDU_size;	/* Max ETSDU size */
	t_scalar_t	CDATA_size;	/* Connect data size */
	t_scalar_t	DDATA_size;	/* Disconnect data size */
	t_scalar_t	ADDR_size;	/* TSAP size */
	t_scalar_t	OPT_size;	/* Options size */
	t_scalar_t	TIDU_size;	/* TIDU size */
	t_scalar_t	SERV_type;	/* Service type */
	t_scalar_t	CURRENT_state;	/* Current state */
	t_scalar_t	PROVIDER_flag;	/* Provider flags */
};

/* PROVIDER_flag values */
#define SENDZERO        0x00000001
#define XPG4_1          0x00000100

struct T_info_req {
	t_scalar_t	PRIM_type;	/* Always T_INFO_REQ */
};

struct T_ok_ack {
	t_scalar_t	PRIM_type;	/* Always T_OK_ACK */
	t_scalar_t	CORRECT_prim;
};

struct T_optmgmt_ack {
	t_scalar_t	PRIM_type;	/* Always T_OPTMGMT_ACK */
	t_scalar_t	OPT_length;
	t_scalar_t	OPT_offset;
	t_scalar_t	MGMT_flags;
};

struct T_optmgmt_req {
	t_scalar_t	PRIM_type;	/* Always T_OPTMGMT_REQ */
	t_scalar_t	OPT_length;
	t_scalar_t	OPT_offset;
	t_scalar_t	MGMT_flags;
};

struct T_ordrel_ind {
	t_scalar_t	PRIM_type;	/* Always T_ORDREL_IND */
};

struct T_ordrel_req {
	t_scalar_t	PRIM_type;	/* Always T_ORDREL_REQ */
};

struct T_unbind_req {
	t_scalar_t	PRIM_type;	/* Always T_UNBIND_REQ */
};

struct T_uderror_ind {
	t_scalar_t	PRIM_type;	/* Always T_UDERROR_IND */
	t_scalar_t	DEST_length;
	t_scalar_t	DEST_offset;
	t_scalar_t	OPT_length;
	t_scalar_t	OPT_offset;
	t_scalar_t	ERROR_type;
};

struct T_unitdata_ind {
	t_scalar_t	PRIM_type;	/* Always T_UNITDATA_IND */
	t_scalar_t	SRC_length;
	t_scalar_t	SRC_offset;
	t_scalar_t	OPT_length;
	t_scalar_t	OPT_offset;
};

struct T_unitdata_req {
	t_scalar_t	PRIM_type;	/* Always T_UNITDATA_REQ */
	t_scalar_t	DEST_length;
	t_scalar_t	DEST_offset;
	t_scalar_t	OPT_length;
	t_scalar_t	OPT_offset;
};

union T_primitives {
	t_scalar_t		type;
	struct T_bind_ack	bind_ack;
	struct T_bind_req	bind_req;
	struct T_conn_con	conn_con;
	struct T_conn_ind	conn_ind;
	struct T_conn_req	conn_req;
	struct T_conn_res	conn_res;
	struct T_data_ind	data_ind;
	struct T_data_req	data_req;
	struct T_discon_ind	discon_ind;
	struct T_discon_req	discon_req;
	struct T_exdata_ind	exdata_ind;
	struct T_exdata_req	exdata_req;
	struct T_error_ack	error_ack;
	struct T_info_ack	info_ack;
	struct T_info_req	info_req;
	struct T_ok_ack		ok_ack;
	struct T_optmgmt_ack	optmgmt_ack;
	struct T_optmgmt_req	optmgmt_req;
	struct T_ordrel_ind	ordrel_ind;
	struct T_ordrel_req	ordrel_req;
	struct T_unbind_req	unbind_req;
	struct T_uderror_ind	uderror_ind;
	struct T_unitdata_ind	unitdata_ind;
	struct T_unitdata_req	unitdata_req;
	struct T_addr_req	addr_req;
	struct T_addr_ack	addr_ack;
};

#endif	/* _TIHDR_H */
