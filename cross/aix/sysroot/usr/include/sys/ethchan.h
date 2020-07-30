/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/ethchan.h 1.41.1.3                           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1999,2011              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/* @(#)82     1.41.1.3  src/bos/kernel/sys/ethchan.h, sysxentchan, bos53X, x2011_14A2 3/10/11 04:39:38 */

/*
 *	COMPONENT_NAME: sysxentchan
 *
 *	ORIGINS: 27
 *
 *	NOTES:
 *		Header file containing structures and #defines for the
 *		EtherChannel kernel extension.
 */

#ifndef	_H_ETHCHAN
#define	_H_ETHCHAN

#include <sys/types.h>
#include <sys/err_rec.h>
#include <sys/cdli_entuser.h>
#include <sys/cdli_entuser.ethchan.h>
#include <sys/ethernet_mibs.h>
#include <sys/watchdog.h>
#include <net/net_globals.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip6_icmp.h>
#include <netinet/if_ether.h>

/* jumbo packet max data size */
#define JUMBO_MAX_MTU 9014

/* The biggest size a link-layer header could possibly have */
#define MAX_LINKHDR	24

/* Used for converting numbers represented as strings to numbers */
#define islower(c)	((c>='a') && (c<='z'))
#define isdigit(c)	((c>='0') && (c<='9'))

#define DIGIT(x)	(isdigit(x) ? (x) - '0' : \
			islower(x) ? (x) + 10 - 'a' : (x) + 10 - 'A')

#define	ETHCHAN_TRACE_SIZE	(1000 * 8) /* Maximum number of trace */
#define	ETHCHAN_OPLEVEL		(PL_IMP)

/* This macro decides whether the provided device is a virtual device
 * (i.e. not really a physical device) or not: this is used to know whether
 * the idle channel should have a different MAC address than the active
 * channel (which is the case with virtual devices)
 * List of virtual devices: Host Ethernet Adapter (HEA)
 */
#define IS_VIRTUAL_DEVICE(nddp) \
	(((nddp->ndd_2_flags & NDD_2_HEA))? TRUE: FALSE)

/* These constants are used in the statistics to signal which channel
 * is active, or if a backup has not even been defined
 */
#define BACKUP_NOT_DEFINED	0
#define PRIMARY_CHANNEL_ACTIVE	1
#define BACKUP_ADAPTER_ACTIVE	2

/* This constant defines how many gratuitous ARP packets are sent
 * after a failover. Since now a recovery will only take place when we
 * are sure that the primary channel's port has been initialized by the
 * switch, we are pretty sure that the first ARP packets will be sent
 * out correctly. However, to avoid regressions, we will leave this value
 * pretty high and avoid potential problems.
 */
#define ARP_SEND_MAX		30

/* This constant is used when probing gratuitous ARP packets are to be set
 * continuously; after a failover, when the primary channel recovers we
 * will send out probing ARP packets, and when any of these packets
 * or actually, any other packet, is received by the primary channel, we
 * know for sure that its port has been initialized and we can proceed
 * to recover the EtherChannel to the primary channel.
 * Since we do not know how many seconds it will take for the primary
 * channel's port to be initialized, we will keep sending ARPs forever
 * (or until the primary channel fails again or the EtherChannel is closed).
 * We must do this to make sure that there is broadcast traffic on the
 * network for the primary channel to "listen to."
 */
#define ARP_SEND_INFINITY	23456

/* These constants are used to identify the reason why a failover occurred:
 * it may have been due to all the adapters in the channel having failed,
 * or if the ping feature in netif_backup is enabled, it may also be due to
 * the failure of the ping attempts
 */
#define ECH_CHANNEL_FAILURE	0
#define ECH_PING_FAILURE	1

/* These constants identify the current state of the EtherChannel */
#define ECH_DOWN        (0x00000000)
#define ECH_UP          (0x11111111)
#define ECH_SWITCHING   (0x22222222)

/* Specifies the maximum length of an adapter's name */
#ifndef ECH_ADAPNAME_SIZE
#define ECH_ADAPNAME_SIZE	ERR_NAMESIZE
#endif

/* -------------------------------------------------------------------- */
/* Error Log Structures  						*/
/* -------------------------------------------------------------------- */

/* Defines for error logger */

/* This failure code value indicates an adapter has gone down */
#define ECH_FC_LINK_FAIL 	0

/* This failure code value indicates the remote host could not be pinged */
#define ECH_FC_NET_FAIL 	1

typedef struct error_log_no_adapters
{
	struct	err_rec0 errhead;
} error_log_no_adapters_t;

typedef struct error_log_one_adapter
{
	struct	err_rec0 errhead;
	uchar_t	adapter1[ECH_ADAPNAME_SIZE];
} error_log_one_adapter_t;

typedef struct error_log_two_adapters
{
	struct	err_rec0 errhead;
	uchar_t	adapter1[ECH_ADAPNAME_SIZE];
	uchar_t	adapter2[ECH_ADAPNAME_SIZE];
} error_log_two_adapters_t;

/* -------------------------------------------------------------------- */
/* Define Device Structure                                		*/
/* -------------------------------------------------------------------- */
/* These flags are used to specify the operating mode of the EtherChannel */
#define ECH_STANDARD_MODE	0x01	/* Sets the channel to select the
					 * adapter using an algorithm
					 */
#define ECH_ROUND_ROBIN_MODE 	0x02	/* Sets the channel to send over
					 * the adapters in round robin fashion
					 */
#define ECH_8023AD_MODE 	0x04	/* Sets the channel to use the IEEE
					 * 802.3ad protocol 
					 */
#define ECH_NETIF_BACKUP_MODE 	0x08	/* Only for internal use, since
					 * netif_backup is no longer an
					 * explicit mode
					 */

/* These flags are used to specify the hashing mode of the EtherChannel */
#define ECH_HASH_DST_IP		0x01	/* Hashes on the last byte of the
					 * destination IP address
					 */
#define ECH_HASH_PORT_MODE	0x10	/* Signals that hashing is done on
					 * TCP/UDP port (used to group
					 * together the following modes)
					 */
#define ECH_HASH_SRC_PORT	0x11	/* Hashes on the TCP/UDP source 
					 * port only
					 */
#define ECH_HASH_DST_PORT	0x12	/* Hashes on the TCP/UDP destination
					 * port only
					 */
#define ECH_HASH_SRC_DST_PORT	0x14	/* Hashes on both the TCP/UDP
					 * destination and source ports
					 */

#define IP_OFFMASK              0x1FFF  /* Used to get the fragment offset from
                                         * the "ip_off" field from the "ip"
                                         * structure
                                         */
typedef struct ethchan_dds
{
	uint32_t locator;		/* "ECDD", for debugging */
	uchar_t	lname[ECH_ADAPNAME_SIZE]; /* Device logical name (i.e. ent5) */
	uchar_t	alias[ECH_ADAPNAME_SIZE]; /* Alias to the device (i.e. en5) */
	uint32_t no_of_adapters;	/* Number of adapters in the channel */
	uchar_t	adapter_names[MAXIFPERCHAN][ECH_ADAPNAME_SIZE];
					/* Device logical names of the
					 * adapters forming the channel
					 */
	uchar_t	jumbo_frames;		/* If non-zero, set the MTU to that
					 * of jumbo frames
					 */
	uchar_t	mode;			/* Sets the mode for accessing the 
					 * adapters
					 */
	uchar_t	use_alt_addr;		/* TRUE => use the following
					 * alt_addr otherwise use the address
					 * from the adapter
					 */
	uchar_t	alt_addr[ENT_NADR_LENGTH];

	uint32_t netaddr;		/* If in Network Interface Backup
					 * mode, ping this address periodically
					 * to detect network failures
					 */
	uint32_t num_retries;		/* The number of pings that may go
					 * unanswered before a failover is
					 * triggered
					 */
	uint32_t retry_to;		/* Time in seconds in between ping
					 * attempts
					 */
	uchar_t	backup_adapter_name[ECH_ADAPNAME_SIZE]; 
					/* Name of the backup adapter */

	uchar_t	hash_mode;		/* Hashing mode */

	boolean_t automatic_recovery;	/* True if automatic recovery should
					 * be performed, false otherwise
					 */

	boolean_t lossless_failover;	/* True if lossless failover should
					 * be performed, false otherwise
					 */
} ethchan_dds_t;

/* -------------------------------------------------------------------- */
/*	CCS Device Driver Variables					*/
/* -------------------------------------------------------------------- */
typedef struct ethchan_dev
{
	uint32_t	locator;	/* "ECDV", for debugging */
	uint32_t	state;   	/* This field holds the state of 
					 * the device driver
					 */
	/* -------------------------------------------- */
	/* The counter section.  For the ctl options    */
	/* -------------------------------------------- */
	uint32_t	adap_switches;	/* Count of the number of times the
					 * channel has failed over
					 */
	uint32_t	multi_cnt;	/* Count of the number of times the
					 * channel has had multicast enabled
					 * (used to know when to reset the
					 * NDD_MULTICAST flag)
					 */
	uint32_t	prom_cnt;	/* Count of the number of times the
					 * channel has been put in promiscuous
					 * mode (used to know when to reset the
					 * NDD_PROMISC flag)
					 */
	struct watchdog wdt;		/* Timer used to send ping packets
					 * periodically when said feature is
					 * enabled
					 */
	Simple_lock	lock; 		/* Locks control functions for the 
					 * device 
					 */
	uint32_t	locked;		/* We need a lock that can be held
					 * for code with no lock (we are 
					 * employing a flag that will be 
					 * checked when the lock is obtained
					 * and if the flag is set, the lock
					 * is released, until the flag is 
					 * cleared, and then the process is 
					 * repeated until the lock is 
					 * available).
					 */
	struct sockaddr_in sa;		/* The IP address of the host we will
					 * ping, if that feature is enabled
					 */
	struct watchdog arp_timer;	/* Timer used to send several
					 * gratuitous ARP packets after a
					 * failover
					 */
	uint32_t 	arp_cnt;	/* Count of how many ARP packets have
					 * been sent after a failover
					 */
	time_t		ndd_stime;	/* Time when the adapter is restarted
					 */
	struct watchdog lacpdu_sender_timer;
					/* Timer that checks if a LACPDU must
					 * be sent and sends one if necessary
					 */
	struct watchdog lacpdu_periodic_timer;
					/* Timer that sends a LACPDU
					 * periodically
					 */
	struct rw_lock	rw_lock;	/* Read/write lock used to
					 * synchronize the modification
					 * of attributes at runtime
					 */
	int32_t		refcnt;		/* Number of functions that are
					 * using data structures that should
					 * not be changed, but are unable to
					 * do so while holding the lock
					 */
	void		(*ls_func)();   /* Pointer to link status callback
					 * function registered by container
					 * device
					 */
	void		*ls_param;      /* Parameter to the link status
					 * callback function
					 */
	Simple_lock	filter_lock;	/* Locking syncronization between 
					 * adding and deleting of filters
					 */
} ethchan_dev_t;

typedef char ethchan_addr_t[ENT_NADR_LENGTH];

/* The "lacpdu_t" structure describes a LACPDU, the type of packet
 * exchanged by the protocol used by IEEE 802.3ad Link Aggregation mode
 */
typedef struct lacpdu
{
        uchar_t		subtype;
        uchar_t		version;
        uchar_t 	actor_tlv_type;
        uchar_t 	actor_information_length;
        ushort_t     	actor_system_priority;
        uchar_t		actor_system [6];
        ushort_t     	actor_key;
        ushort_t     	actor_port_priority;
        ushort_t     	actor_port;
        uchar_t		actor_state;
        uchar_t		actor_reserved [3];
        uchar_t		partner_tlv_type;
        uchar_t		partner_information_length;
        ushort_t     	partner_system_priority;
        uchar_t		partner_system [6];
        ushort_t     	partner_key;
        ushort_t     	partner_port_priority;
        ushort_t     	partner_port;
        uchar_t		partner_state;
        uchar_t		partner_reserved [3];
        uchar_t		collector_tlv_type;
        uchar_t		collector_information_length;
        ushort_t     	collector_max_delay;
        uchar_t		collector_reserved [12];
        uchar_t		terminator_tlv_type;
        uchar_t		terminator_length;
	uchar_t		terminator_reserved [50];
} lacpdu_t;

/* The "marker_pdu_t" structure describes a marker PDU, the type of packet
 * exchanged to mark when a port should stop being used for transmission
 * in case of dynamic port reallocation
 */
typedef struct marker_pdu
{
        uchar_t		subtype;
        uchar_t		version;
        uchar_t 	requester_tlv_type;
        uchar_t 	requester_information_length;
        ushort_t     	requester_port;
        uchar_t		requester_system [6];
        uint32_t     	requester_transaction_id;
        ushort_t     	pad;
        uchar_t		terminator_tlv_type;
        uchar_t		terminator_length;
	uchar_t		terminator_reserved [90];
} marker_pdu_t;

/* Each port (adapter) in an IEEE 802.3ad aggregation will have one of
 * these structures to keep track of each port's run-time values
 * and the values of the port's partner; it also holds the port's
 * statistics
 */
typedef struct ieee8023ad_port_info
{
	ndd_t   			*nddp;
	boolean_t			ntt;

	struct pkt
	{
		struct ether_header	header;
		lacpdu_t		lacpdu;
	} pkt;

	ieee_8023ad_stats_t		stats;
} ieee8023ad_port_info_t;

/* Contains information regarding the aggregator pertaining to an
 * EtherChannel; it contains structures for all the ports in an IEEE
 * 802.3ad aggregation (even the backup, if one is defined)
 */
typedef struct ieee8023ad_aggregator
{ 
	uint32_t		locator;	/* "ECAG", for debugging */
	ieee8023ad_port_info_t	port_info[MAXIFPERCHAN];
						/* Static array
						 * of port_info structures;
						 * there will be one port_info
						 * structure for each adapter
						 * in the main channel
						 */
	ieee8023ad_port_info_t	backup_port_info;
						/* The port_info structure
						 * for the backup adapter (if
						 * defined)
						 */
	uchar_t			aggregation_status;
						/* Status of the link
						 * aggregation: before the
						 * protocol is initiated, it
						 * is set to "Inactive"; then
						 * it is set to "Negotiating".
						 * When convergence has
						 * been achieved, it is set
						 * to "Aggregated", and if it
						 * fails, to "Failed"
						 */	
	ns_user_t		ns_user;	/* The user for the filters
						 * used to receive LACPDUs;
						 * it is contained here
						 * because it must indicate
						 * the EtherChannel for which
						 * a LACPDU is intended
						 */
} ieee8023ad_aggregator_t;

/* 
 * Interface configured over etherchannel or 
 * any container device over etherchannel
 */
typedef struct ethchan_if
{
	struct ifnet *ifp;
	struct ethchan_if *next;
} ethchan_if_t;

/* ----------------------------------------------------------------- */
/* EtherChannel control structure				     */
/* ----------------------------------------------------------------- */

typedef struct ethchan_ccs
{
	struct ethchan_ccs	*next_ccs;	/* Pointer to next EtherChannel
						 * in the linked list
						 */
	ndd_t			*nddp_adapter[MAXIFPERCHAN];
						/* Pointers to the ndd
						 * structures of the adapters
						 * of this channel
						 */
	uint32_t		seq_number;	/* The sequence number the
						 * ccs was configured with
						 */
	uint32_t		current_adapter;
						/* Used for some modes for
						 * to specify the adapter to 	
						 * transmit on
						 */
	uint32_t		icmp_outstanding;
						/* Number of pings packets
						 * that have been sent but
						 * whose reply has not yet
						 * been received
						 */
	ethchan_dds_t		dds;	   	/* Define Device Structure */
	ndd_t			ndd;		/* The copy of ndd structure
						 * for this channel
						 */
	ethchan_addr_t		src_addr;	/* Source address used by
						 * packets generated by the
						 * channel (e.g. gratuitous
						 * ARP packets)
						 */
	uint32_t		unit;		/* Number associated with
						 * the interface
						 */
	ethchan_if_t		*if_list;	/* List of interfaces configured
						 * over etherchannel
						 */
	ethchan_dev_t		dev;		/* Device control area */

	ndd_t			*nddp_backup_adapter;
						/* Pointer to the backup
						 * adapter for the
						 * channel, null if there
						 * is none
						 */
	uint32_t		flags;		/* State flags for the channel
						 * (see below for flags)
						 */
	uint32_t		no_of_initialized_adapters;
						/* The number of adapters
						 * whose link status we have
						 * learned every time the
						 * channel is opened: the
						 * backup adapter is counted
						 * in these calculations
						 */
	uint32_t		failure_reason; /* The reason why the
						 * channel failed over: may be
						 * ECH_CHANNEL_FAILURE or
						 * ECH_PING_FAILURE
						 */
	ieee8023ad_aggregator_t aggregator;	/* Contains information
						 * pertaining to the
						 * aggregator for this link
						 * aggregation
						 */
	ent_genstats_t		statistics;	/* Holds the statistics
						 * for the EtherChannel
						 */
	ndd_t			*nddp_address_owner;
						/* Adapter where we got the
						 * EtherChannel's MAC from
						 */
	ethchan_addr_t		adapter_addresses[MAXIFPERCHAN];
						/* Original MAC addresses for
						 * adapters in the main
						 * channel
						 */
	ethchan_addr_t		backup_address;
						/* Original MAC addresses for
						 * the backup adapter
						 */
} ethchan_ccs_t;

/* These flags are used for masking the "flags" member of "ethchan_ccs" */

/* Set when all the primary adapters have failed and the backup adapter is
 * being used
 */
#define	ETHCH_BACKUP_IS_ACTIVE		0x0001

/* Set when the channel has learned of the link status of all the adapters
 * after it is opened
 */
#define ETHCH_CHANNEL_IS_INITIALIZED	0x0002

/* Set when the channel has been configured with an IP address */
#define ETHCH_INTERFACE_IS_CONFIGURED	0x0004

/* Set when a recovery from backup to primary is pending */
#define ETHCH_RECOVERY_IS_PENDING	0x0008

/* Set when a failover from primary to backup is pending */
#define ETHCH_FAILOVER_IS_PENDING	0x0010

/* Set when a failover is due to ping failure (if clear, failover was due
 * to link failure); used to determine what type of logging should be
 * used when a failure is pending
 */
#define ETHCH_PING_FAILURE_FAILOVER	0x0020

/* Set when only internally-generated packets (like LACPDUs) should be traced:
 * used when the EtherChannel is in a container device that is already tracing
 * packets, so the EtherChannel should NOT trace them again in its output
 * routine
 */
#define ETHCH_INTERNAL_TRACE_ONLY	0x0040

/* State whether an EtherChannel with a backup adapter should recover
 * automatically after a failover when at least one of the main adapters
 * recovers; it is set by default
 */
#define ETHCH_AUTOMATIC_RECOVERY	0x0080

/* State whether an EtherChannel should perform delayed recovery to
 * improve failover and recovery times
 */
#define ETHCH_DELAYED_RECOVERY		0x0100

/* State whether an EtherChannel should perform lossless failover to
 * prevent packet loss when doing ping failovers
 */
#define ETHCH_LOSSLESS_FAILOVER		0x0200

/* Command passed to "ieee8023ad_init()" to configure IEEE 802.3ad */
#define IEEE_8023AD_CONFIGURE_CMD	0

/* Command passed to "ieee8023ad_init()" to unconfigure IEEE 802.3ad */
#define IEEE_8023AD_UNCONFIGURE_CMD	1

/* The number of seconds between sending LACPDUs periodically for long interval*/
#define IEEE_8023AD_LONG_TIMEOUT 	30

/* The number of seconds between sending LACPDUs periodically for short interval */
#define IEEE_8023AD_SHORT_TIMEOUT   1

/* The MAC address of the Slow Protocols Multicast group, which
 * is where LACPDUs are sent (01-80-C2-00-00-02)
 */
#define SLOW_PROTOCOLS_MULTICAST_ADDRESS {0x01, 0x80, 0xC2, 0x00, 0x00, 0x02}

/* The Ethertype value of LACPDUs */
#define IEEE_8023AD_ETHERTYPE		0x8809

/* The value of the system priority of this system */
#define IEEE_8023AD_SYSTEM_PRIORITY	0x8000

/* The value of the operational key for all adapters */
#define IEEE_8023AD_OPERATIONAL_KEY	0xBEEF

/* The value of the port priority for all the ports */
#define IEEE_8023AD_PORT_PRIORITY	0x80

/* The value of the maximum delay between when a packet is received and
 * it is sent to the collector
 */
#define IEEE_8023AD_COLLECTOR_MAX_DELAY 0x8000

/* These constants are used in the construction of LACPDUs */
#define IEEE_8023AD_LACPDU_SUBTYPE			0x01
#define IEEE_8023AD_LACPDU_VERSION			0x01
#define IEEE_8023AD_LACPDU_ACTOR_TLV_TYPE		0x01
#define IEEE_8023AD_LACPDU_ACTOR_INFORMATION_LENGTH	0x14
#define IEEE_8023AD_LACPDU_PARTNER_TLV_TYPE		0x02
#define IEEE_8023AD_LACPDU_PARTNER_INFORMATION_LENGTH	0x14
#define IEEE_8023AD_LACPDU_COLLECTOR_TLV_TYPE		0x03
#define IEEE_8023AD_LACPDU_COLLECTOR_INFORMATION_LENGTH	0x10

/* These constants are used in the construction of marker PDUs */
#define IEEE_8023AD_MARKER_PDU_SUBTYPE			0x02
#define IEEE_8023AD_MARKER_INFORMATION_TYPE		0x01
#define IEEE_8023AD_MARKER_RESPONSE_INFORMATION_TYPE	0x02

/* These flags are used for masking the "actor_state" and "partner_state"
 * fields of LACPDUs
 */
#define IEEE_8023AD_LACP_ACTIVITY	0x01
#define IEEE_8023AD_LACP_TIMEOUT	0x02
#define IEEE_8023AD_AGGREGATION		0x04
#define IEEE_8023AD_SYNCHRONIZATION	0x08
#define IEEE_8023AD_COLLECTING		0x10
#define IEEE_8023AD_DISTRIBUTING	0x20
#define IEEE_8023AD_DEFAULTED		0x40
#define IEEE_8023AD_EXPIRED		0x80

/* These values indicate the status of the link aggregation: its values
 * are set in ethchan_recalculate_status() and are queried by the
 * GET_ALL_STATS ioctl so the status of the aggregation can be
 * printed by the "entstat.ethchan" command
 */
#define IEEE_8023AD_STATUS_INACTIVE	0x00
#define IEEE_8023AD_STATUS_NEGOTIATING	0x01
#define IEEE_8023AD_STATUS_AGGREGATED	0x02
#define IEEE_8023AD_STATUS_FAILED	0x03

typedef struct ethchan_trc
{
	uint32_t	res[3],		/* Reserved */
			next,		/* Next index to put trace data in
					 * the table
					 */
			res1,
			res2,
			res3;
	uint32long64_t	table[ETHCHAN_TRACE_SIZE];
} ethchan_trc_t;

typedef struct ethchan_tbl
{
	lock_t		table_lock;
	uint32_t	ccs_cnt;	/* Number of channels we have */
	uint32_t	open_cnt;	/* Count of active opens */
	ethchan_ccs_t	*p_ccs;		/* CCS pointer for each channel */
	Simple_lock	trace_lock;	/* Locks internal trace table */
	ethchan_trc_t	trace;		/* Internal trace table */
	Complex_lock	dd_clock; 	/* The lock for the open/close sync */
} ethchan_tbl_t;

typedef struct ech_icmp
{
	struct	ip ip;
	struct	icmp icmp;
} ech_icmp_t;

typedef struct ech_icmp6
{
	struct	ipv6 ip6;
	struct	icmpv6 icmp6;
} ech_icmp6_t;

/* Structure representing an Ethernet header containing a VLAN tag */
typedef struct ethchan_vlan_hdr
{
	struct ether_header;
	ushort_t vlan_id;
	ushort_t actual_ether_type;
} ethchan_vlan_hdr_t;

/* Macros for defining and using read/write locks */

/* Initialization of the read/write lock */
#define ETHCHAN_LOCKINIT() \
{	\
        lock_alloc (&((&p_ccs->dev.rw_lock)->simple_lock), LOCK_ALLOC_PIN, \
		XETHCHAN_DD_LOCK, -1); \
	\
        simple_lock_init (&((&p_ccs->dev.rw_lock)->simple_lock)); \
        (&p_ccs->dev.rw_lock)->read_cnt = 0; \
}

/* Initialization of the filter lock */
#define ETHCHAN_FILTER_LOCKINIT() \
{	\
	lock_alloc (&p_ccs->dev.filter_lock, LOCK_ALLOC_PIN, \
		XETHCHAN_DD_LOCK, -1); \
	\
	simple_lock_init (&p_ccs->dev.filter_lock); \
}

/* Macros for locking and unlocking filters for add and delete */
#define ETHCHAN_FILTER_LOCK() \
	simple_lock (&p_ccs->dev.filter_lock);

#define ETHCHAN_FILTER_UNLOCK() \
	simple_unlock (&p_ccs->dev.filter_lock);

#define ETHCHAN_FILTER_LOCK_FREE() \
	lock_free (&p_ccs->dev.filter_lock);

/* Declaration of local variables for storing interrupt priorities */
#define ETHCHAN_LOCK_DECL()						\
	int	_writepri

/* Macros for locking and unlocking for exclusive write access */

/* We use the version of RW_WRITE_LOCK that does not hold the lock while
 * spinning to enable nested readers without causing a deadlock
 */
#define ETHCHAN_WRITE_LOCK()						\
	RW_WRITE_LOCK_RELEASE(&p_ccs->dev.rw_lock, _writepri, PL_IMP)

#define ETHCHAN_WRITE_UNLOCK()						\
	RW_WRITE_UNLOCK(&p_ccs->dev.rw_lock, _writepri)

/* Macros for locking and unlocking shared read locks */

/* We use the version of read locks that do not disable/re-enable interrupts:
 * we can do this because in our code we can never be interrupted by a thread
 * trying to get the write lock while we are holding the read lock because
 * all the functions that grab the write lock are called exclusively in the
 * process thread
 */
#define ETHCHAN_READ_LOCK()						\
	RW_READ_LOCK_NO_DISABLE(&p_ccs->dev.rw_lock, _writepri, PL_IMP)

#define ETHCHAN_READ_UNLOCK()						\
	RW_READ_UNLOCK_NO_ENABLE(&p_ccs->dev.rw_lock)

/* Macro for going from an exclusive write lock to a shared read lock */
#define ETHCHAN_WRITE_TO_READ_LOCK()					\
	RW_WRITE_TO_READ_LOCK_NO_DISABLE(&p_ccs->dev.rw_lock, _writepri)

/* Macro for going from a shared read lock to an exclusive write lock */
#define ETHCHAN_READ_TO_WRITE_LOCK()					\
	RW_READ_TO_WRITE_LOCK_NO_ENABLE(&p_ccs->dev.rw_lock, _writepri, PL_IMP)

/* We will use the "ndd_reserved" field in the "ndd" structure to store
 * a pointer to the EtherChannel to which each adapter belongs. We use
 * this pointer to implement "delayed recovery": we do not recover to the
 * main channel until we know for sure its port has been initalized and it
 * can receive packets.
 * We cannot use the "ndd_ptr" field because that is already in use by
 * the Shared Ethernet Adapter (SEA), and an EtherChannel could be defined
 * within a SEA and we do not want to overwrite this field. Thus, we will
 * use the "ndd_reserved" field in the "ndd" structure: specifically, we will
 * use the 14th word (and optionally the 15th) of the field to store the
 * pointer to the EtherChannel to which the adapter belongs (32-bit
 * architectures will only need word 14, but 64-bit architectures will take
 * up words 14 and 15).
 * We define these macros to make the code more readable.
 */

/* This macro is used to read the stored EtherChannel pointer into the
 * the specified variable (we cast it to an EtherChannel CCS structure)
 */
#define ETHCHAN_POINTER_READ(variable,nddp)				\
{									\
	caddr_t *ptr = (caddr_t *) &nddp->ndd_reserved [14];		\
	variable = (ethchan_ccs_t *) *ptr;				\
}

/* This macro is used to store the EtherChannel pointer into the
 * "ndd.ndd_reserved" field
 */
#define ETHCHAN_POINTER_STORE(nddp,value)				\
{									\
	caddr_t *ptr = (caddr_t *) &nddp->ndd_reserved [14];		\
	*ptr = (caddr_t) value;						\
}

/* This macro is used to set the receive function pointer in an adapter */
#define ETHCHAN_SET_RECEIVE_FUNC(nddp,new_func)				\
{									\
	nddp->nd_receive = new_func;					\
}

/* Macros for debug and error tracing */
#define	ETHCHAN_XMIT	((HKWD_ETHCHAN_XMIT  << 20) | HKTY_GT | 4)
#define	ETHCHAN_OTHER	((HKWD_ETHCHAN_OTHER << 20) | HKTY_GT | 4)

#define	ETHCHAN_ETRACE(tag, a1, a2, a3)					\
{									\
	if (ERR_LEVEL(ras_ethchan_cbp) >= ERRCHECK_DETAIL) {    	\
		ethchan_trace (tag, (uint32long64_t) a1,	 	\
			(uint32long64_t) a2, (uint32long64_t) a3);	\
	}								\
	CT_HOOK5(ras_ethchan_cbp, CT_LVL_MINIMAL, RAS_MEM_PRIV,		\
		ETHCHAN_OTHER, *(ulong *) (tag),			\
		(ulong)(a1), (ulong)(a2), (ulong)(a3), 0);		\
}
#define	ETHCHAN_ETRACE_DETAIL(tag, a1, a2, a3)				\
{									\
	if (ERR_LEVEL(ras_ethchan_cbp) >= ERRCHECK_DETAIL) {    	\
		ethchan_trace (tag, (uint32long64_t) a1,	 	\
			(uint32long64_t) a2, (uint32long64_t) a3);	\
	}								\
	CT_HOOK5(ras_ethchan_cbp, CT_LVL_DETAIL, RAS_MEM_PRIV,		\
		ETHCHAN_OTHER, *(ulong *) (tag),			\
		(ulong)(a1), (ulong)(a2), (ulong)(a3), 0);		\
}

#define ETHCHAN_TRACE(tag, a1, a2, a3)                          	\
{                                                               	\
	if (ERR_LEVEL(ras_ethchan_cbp) >= ERRCHECK_DETAIL) {    	\
	        ethchan_trace (tag, (uint32long64_t) a1,                \
			(uint32long64_t) a2, (uint32long64_t) a3);      \
	}								\
	CT_HOOK5(ras_ethchan_cbp, CT_LVL_MINIMAL, RAS_MEM_PRIV,		\
		ETHCHAN_OTHER, *(ulong *) (tag),               		\
                (ulong) (a1), (ulong) (a2), (ulong) (a3), 0);   	\
}

#define ETHCHAN_TTRACE(tag, a1, a2, a3)					\
{									\
	if (ERR_LEVEL(ras_ethchan_cbp) >= ERRCHECK_DETAIL) {    	\
		ethchan_trace (tag, (uint32long64_t) a1, 		\
			(uint32long64_t) a2, (uint32long64_t) a3);	\
	}								\
	CT_HOOK5(ras_ethchan_cbp, CT_LVL_MINIMAL, RAS_MEM_PRIV,		\
		ETHCHAN_XMIT, *(ulong *) (tag), 			\
		(ulong) (a1), (ulong) (a2), (ulong) (a3), 0);		\
}
#define ETHCHAN_TTRACE_DETAIL(tag, a1, a2, a3)				\
{									\
	if (ERR_LEVEL(ras_ethchan_cbp) >= ERRCHECK_DETAIL) {    	\
		ethchan_trace (tag, (uint32long64_t) a1, 		\
			(uint32long64_t) a2, (uint32long64_t) a3);	\
	}								\
	CT_HOOK5(ras_ethchan_cbp, CT_LVL_DETAIL, RAS_MEM_PRIV,		\
		ETHCHAN_XMIT, *(ulong *) (tag), 			\
		(ulong) (a1), (ulong) (a2), (ulong) (a3), 0);		\
}

#endif	/* ! _H_ETHCHAN */
