/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/sys/cdli_entuser.ethchan.h 1.6.1.7               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999,2007          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)83     1.6.1.7  src/bos/kernel/sys/cdli_entuser.ethchan.h, sysxentchan, bos53L, l2007_10A9 3/7/07 16:46:30 */

/*
 *	COMPONENT_NAME: sysxentchan
 *
 *	ORIGINS: 27
 *
 *	NOTES:
 *		This header file defines structures and #defines used
 *		both by the EtherChannel kernel extension and the
 *		user-level applications that interact with said kernel
 *		extension.
 */

#include <sys/err_rec.h>

#ifndef _H_CDLI_ENTUSER_ETHCHAN
#define _H_CDLI_ENTUSER_ETHCHAN

#define ENT_ETHERCHANNEL	0x0000000B

/* Specifies the maximum length of an adapter's name */
#ifndef ECH_ADAPNAME_SIZE
#define ECH_ADAPNAME_SIZE       ERR_NAMESIZE
#endif

/* Maximum number of adapters that can exist in the main channel */
#define MAXIFPERCHAN    	8

/* EtherChannel trace hook numbers */
#define HKWD_ETHCHAN_XMIT	0x2FA	/* transmit events */
#define HKWD_ETHCHAN_OTHER	0x2FB	/* other events    */

/* Statistics and parameters maintained for each port in a link aggregation */
typedef struct ieee_8023ad_port_stats
{
	ushort_t	actor_system_priority;	/* Local system priority */
	uchar_t		actor_system [6];	/* Local system ID */
	ushort_t	actor_key;		/* Local operational key */
	ushort_t	actor_port_priority;	/* Local port priority value */
	ushort_t	actor_port;		/* Local port number */
	uchar_t		actor_state;		/* Local port state flags */

	ushort_t	partner_system_priority;/* Remote system priority */
	uchar_t		partner_system [6];	/* Remote system ID */
	ushort_t	partner_key;		/* Remote operational key */
	ushort_t	partner_port_priority;	/* Remote port priority value */
	ushort_t	partner_port;		/* Remote port number */
	uchar_t		partner_state;		/* Remote port state flags */

	__ulong32_t	rx_lacpdus; 		/* Valid LACPDUs received on
						 * the port
						 */
	__ulong32_t	rx_marker_lacpdus;	/* Valid marker LACPDUs
						 * received on the port
						 */
	__ulong32_t	rx_marker_response_lacpdus;
						/* Valid marker response
						 * LACPDUs received on
						 * the port
						 */
	__ulong32_t	rx_unknown_lacpdus;	/* Frames received that either
						 * carry the Slow Protocols
						 * Ethernet type but contain
						 * an unknown PDU, or are
						 * addressed to the Slow
						 * protocols group MAC address
						 * but do not carry the Slow
						 * Protocols Ethernet type
						 */
	__ulong32_t	rx_illegal_lacpdus;	/* Frames received that carry
						 * the Slow Protocols Ethernet
						 * type value but contain a
						 * badly formed PDU or an
						 * illegal value of Protocol
						 * Subtype
						 */
	__ulong32_t	tx_lacpdus; 		/* Valid LACPDUs transmitted on
						 * the port
						 */
	__ulong32_t	tx_marker_lacpdus;	/* Valid marker LACPDUs
						 * transmitted on the port
						 */
	__ulong32_t	tx_marker_response_lacpdus;
						/* Valid marker response
						 * LACPDUs transmitted on
						 * the port
						 */
} ieee_8023ad_stats_t;

/* EtherChannel-specific statistics (including per-adapter and per-link
 * aggregation port statistics); we must preemptively make space for the
 * statistics and the name of the backup adapter (which may or may not be
 * actually configured)
 */
typedef struct ethchan_stats
{
        uint32_t		no_of_adapters;	/* Number of adapters in the
						 * EtherChannel
						 */
        ent_ndd_stats_t		adaptstat[MAXIFPERCHAN+1];
						/* Statistics of each
						 * adapter
						 */
        uchar_t			adapter_names
					[MAXIFPERCHAN+1][ECH_ADAPNAME_SIZE];
						/* Names of all the adapters */
        ieee_8023ad_stats_t	ieee8023ad_stats[MAXIFPERCHAN+1];
        ushort_t		active_channel;	/* Can be either
						 * BACKUP_NOT_DEFINED,
						 * PRIMARY_CHANNEL_ACTIVE
                 				 * or BACKUP_ADAPTER_ACTIVE
						 */
        uchar_t			mode;		/* The current operating mode */
        uchar_t			aggregation_status; /* IEEE 802.3ad status */
	uchar_t			hash_mode;	/* Current hash mode */
} ethchan_stats_t;

/* Aggregate statistics for all the adapters in the EtherChannel */
typedef struct ethchan_all_stats
{
        ndd_genstats_t		ent_ndd_stats;	/* Aggregate NDD statistics */
        ent_genstats_t		ent_gen_stats;	/* Aggregate generic
						 * statistics
						 */
        ethchan_stats_t		ethchan_stats;	/* EtherChannel-specific
						 * statistics (including
						 * per-adapter statistics)
						 */
	ieee_8023ad_stats_t	ieee_8023ad_stats;
						/* Aggregate link aggregation
						 * statistics and parameters
						 */
} ethchan_all_stats_t;

#define MAXADAPSTATLEN	8*1024	/* Allow up to 8KB for adapter statistics */

/* Structure used to retrieve statistics from an adapter contained
 * in an EtherChannel; it contains a buffer that should be big enough to
 * accomodate the biggest adapter-specific statistics structure
 */
typedef struct ethchan_adapter_stats
{
        uchar_t		adapter_name [ECH_ADAPNAME_SIZE];
        uint32_t	bufferlen;
        uchar_t		bufferptr [MAXADAPSTATLEN];	
} ethchan_adapter_stats_t;

/* This structure is used as an argument to the NDD_MODIFY_ETHCHAN
 * ioctl to describe the change that will be done to the EtherChannel
 */
typedef struct ethchan_modify
{
	uint32_t	command;
	uint32_t	modifier;
	uchar_t		attribute[128];
	uchar_t		new_value[128];
	uint32_t	flags;
	uint32_t	rc;
} ethchan_modify_t;

/* This structure is passed to the functions that add or delete and adapter
 * from an EtherChannel
 */
typedef struct ethchan_add_delete_modifier
{
	uchar_t		*adapter_name;
	boolean_t	is_backup;
	uint32_t	rc;
} ethchan_add_delete_modifier_t;

/* This structure is passed to the function that changes an attribute in
 * an EtherChannel
 */
typedef struct ethchan_change_modifier
{
	uchar_t		*attribute;
	uchar_t		*new_value;
	uint32_t	rc;
} ethchan_change_modifier_t;

/* The commands that can be done on an EtherChannel through the
 * NDD_MODIFY_ETHCHAN ioctl
 */
#define ETHCHAN_CMD_ADD_ADAPTER		0x00000001
#define ETHCHAN_CMD_DEL_ADAPTER		0x00000010
#define ETHCHAN_CMD_CHG_ATTRIBUTE	0x00000100
#define ETHCHAN_CMD_FORCE_FAILOVER	0x00001000

/* The modifiers to the commands that can be done on an EtherChannel through
 * the NDD_MODIFY_ETHCHAN ioctl
 */
#define ETHCHAN_MOD_BACKUP		0x00000001

/* These are return codes from EtherChannel functions */
#define ETHCH_SUCCESS		0
#define ETHCH_EINVAL		10
#define ETHCH_EMAXADAP		20
#define ETHCH_EBACKUP		30
#define ETHCH_EINVALATTR	40
#define ETHCH_EINVALVALUE	50
#define ETHCH_ENOTFOUND		60
#define ETHCH_ECAPABILITY	70
#define ETHCH_EINVALCOMBINATION 80

/* These return codes signal success, not an error */
#define ETHCH_SDELETEDBACKUP	5
#define ETHCH_SDELETEDMAIN	15

#endif  /* _H_CDLI_ENTUSER_ETHCHAN */
