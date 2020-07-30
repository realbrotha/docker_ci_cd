/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/ndd.h 1.56.1.6                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1993              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)82       1.56.1.6  src/bos/kernel/sys/ndd.h, sysnet_cdli, bos53X, x2010_01A5 10/13/09 05:55:19 */
/*
 *   COMPONENT_NAME: SYSNET
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,2003
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef	_H_NDD
#define	_H_NDD

#include <sys/types.h>
#include <sys/processor.h>
#include <sys/lockl.h>

#define	NDD_MAXNAMELEN	(16)

/*
 * Structure for generic statistics
 */
struct ndd_genstats
{
	__ulong32_t ndd_elapsed_time;  /* time in seconds since last reset */
	__ulong32_t ndd_ipackets_msw;  /* packets received on interface(msw) */
	__ulong32_t ndd_ipackets_lsw;  /* packets received on interface(lsw) */
	__ulong32_t ndd_ibytes_msw;    /* total # of octets received(msw) */
	__ulong32_t ndd_ibytes_lsw;    /* total # of octets received(lsw) */
	__ulong32_t ndd_recvintr_msw;  /* number of receive interrupts(msw) */
	__ulong32_t ndd_recvintr_lsw;  /* number of receive interrupts(lsw) */
	__ulong32_t ndd_ierrors;       /* input errors on interface */
	__ulong32_t ndd_opackets_msw;  /* packets sent on interface(msw) */
	__ulong32_t ndd_opackets_lsw;  /* packets sent on interface(lsw) */
	__ulong32_t ndd_obytes_msw;    /* total number of octets sent(msw) */
	__ulong32_t ndd_obytes_lsw;    /* total number of octets sent(lsw) */
	__ulong32_t ndd_xmitintr_msw;  /* number of transmit interrupts(msw) */
	__ulong32_t ndd_xmitintr_lsw;  /* number of transmit interrupts(lsw) */
	__ulong32_t ndd_oerrors;       /* output errors on interface */
	__ulong32_t ndd_nobufs;	       /* no buffers available */
	__ulong32_t ndd_xmitque_max;   /* max transmits ever queued */
	__ulong32_t ndd_xmitque_ovf;   /* number of transmit queue overflows */
	__ulong32_t ndd_ipackets_drop; /* number of packets not passed up */
	__ulong32_t ndd_ibadpackets;   /* # of bad pkts recv'd from adapter */
	__ulong32_t ndd_opackets_drop; /* number of packets not transmitted */
	__ulong32_t ndd_xmitque_cur;   /* sum of driver+adapter xmit queues */
	__ulong32_t ndd_ifOutUcastPkts_msw; /* outbound unicast pkts
					       requested */
	__ulong32_t ndd_ifOutUcastPkts_lsw; /* on interface (msw and lsw) */
	__ulong32_t ndd_ifOutMcastPkts_msw; /* outbound multicast pkts
					       requested */
	__ulong32_t ndd_ifOutMcastPkts_lsw; /* on interface (msw and lsw) */
	__ulong32_t ndd_ifOutBcastPkts_msw; /* outbound broadcast pkts
					       requested */
	__ulong32_t ndd_ifOutBcastPkts_lsw; /* on interface (msw and lsw) */
	__ulong32_t ndd_stat_reserved[23];  /* reserved */
};
typedef	struct ndd_genstats ndd_genstats_t;

/*
 * Structure defining a network device driver interface.
 */
struct ndd {
	struct	ndd *ndd_next;		/* next ndd in chain */
	__ulong32_t	ndd_refcnt;	/* number of allocs outstanding */
	char	*ndd_name;		/* name, e.g. ``en0'' or ``tr0'' */
	char	*ndd_alias;		/* alternate name */
	__ulong32_t	ndd_flags;	/* up/down, broadcast, etc. */
	caddr_t	ndd_correlator;		/* correlator for NDD use */
/* procedure handles */
	int	(*ndd_open)();		/* init function */
	int	(*ndd_close)();		/* close function */
	int	(*ndd_output)();	/* output function */
	int	(*ndd_ctl)();		/* control function */
/* user receive and status functions */
	void	(*nd_receive)();	/* demuxer receive function */
	void	(*nd_status)();		/* status notification */
/* driver description */
	__ulong32_t	ndd_mtu;	/* maximum transmission unit */
	__ulong32_t	ndd_mintu;	/* minimum transmission unit */
	__ulong32_t	ndd_type;	/* ethernet, etc (see interface types */
	__ulong32_t	ndd_addrlen;	/* media address length */
	__ulong32_t	ndd_hdrlen;	/* media header length */
	caddr_t	ndd_physaddr; 		/* medias physical address */
/* demuxer linkage */
	struct	ns_demuxer *ndd_demuxer;/* back pointer to associated demuxer */
	struct  ns_dmx_ctl *ndd_nsdemux;/* ptr to common demux control */
	caddr_t	ndd_specdemux;		/* ptr to demuxer specific control */
	int	ndd_demuxsource;	/* 0 if system dmx, 1 if NDD provided */
	Simple_lock ndd_demux_lock;     /* lock for dmx ctl structs */
/* packet tracing */
	void	(*ndd_trace)();		/* packet trace function */
	caddr_t	ndd_trace_arg;		/* argument to trace function */
	Complex_lock ndd_lock;		/* NDD lock for network services */
	__ulong32_t	ndd_reserved[16];	/* reserved. Any reserved field may */
					/* be used/defined, see below for */
					/* any further definition. */
/* stats */
	caddr_t	ndd_specstats;		/* pointer to device specific stats */
	__ulong32_t	ndd_speclen;	/* length of device specific stats */
	struct	ndd_genstats ndd_genstats;	/* generic network stats */

	__ulong32_t ndd_2_flags;	/* flags extension field */
	caddr_t ndd_ptr;		/* pointer for device use */
};
typedef	struct ndd	ndd_t;

typedef	struct ndd	* nddp_t;

/* This structure is used by the NDD_START_TRACE ioctl */
typedef struct ndd_trace_info
{
        caddr_t		ndd_trace_arg;
        void		(*ndd_trace) ();
	uint32_t	ndd_trace_flags;        /* see below for flag values */
} ndd_trace_info_t;

/* Possible values for ndd_trace_flags */
#define NDD_TRACE_INTERNAL_ONLY (0x00000001)    /* Device should only trace
						 * internally-generated packets
						 * and not those given to it
						 * by a container device
						 */

#define	NDD_LOCK(nddp)		lock_write(&(nddp)->ndd_lock)
#define	NDD_UNLOCK(nddp)	lock_done(&(nddp)->ndd_lock)

/* flag values */
#define	NDD_UP		(0x00000001)	/* NDD is opened */
#define	NDD_BROADCAST	(0x00000002)	/* broadcast address valid */
#define	NDD_DEBUG	(0x00000004)	/* operating in debug mode */
#define	NDD_RUNNING	(0x00000008)	/* NDD is operational */
#define	NDD_SIMPLEX	(0x00000010)	/* can't hear own transmissions */
#define	NDD_DEAD	(0x00000020)	/* device is not operational */
#define	NDD_LIMBO	(0x00000040)	/* in network recovery mode */
#define	NDD_PROMISC	(0x00000080)	/* in promiscuous mode */
#define	NDD_ALTADDRS	(0x00000100)	/* receiving additional addresses */
#define	NDD_MULTICAST	(0x00000200)	/* receiving all multicasts */
#define	NDD_DETACHED	(0x00000400)	/* NDD has been detached */
#define NDD_64BIT	(0x00000800)	/* supports 64 bit */
#define	NDD_HIGHFUNC_QOS (0x00001000)	/* supports full QOS scheduling */
#define	NDD_MEDFUNC_QOS	(0x00002000)	/* supports medium QOS scheduling */
#define	NDD_MINFUNC_QOS	(0x00004000)	/* supports minimal QOS scheduling */
#define NDD_QOS		(NDD_HIGHFUNC_QOS|NDD_MEDFUNC_QOS|NDD_MINFUNC_QOS)
#define NDD_CHECKSUM_OFFLOAD (0x00010000) /* supports checksum offload */
#define NDD_PSEG	(0x00020000)	/* support private segment buffers */
#define	NDD_ETHERCHANNEL (0x00040000)	/* Etherchannel */
#define	NDD_VLAN 	(0x00080000)	/* VLAN */
#define	NDD_SPECFLAGS	(0x00100000)	/* min value of device specific flags */

/* flag_2 (extension of flag field) values */
#define	NDD_2_SEA	(0x00000001)	/* Shared Ethernet Adapter      */
#define	NDD_2_VIOENT	(0x00000002)	/* Virtual I/O Ethernet Adapter */
#define NDD_2_VASI	(0x00000004)	/* VASI device			*/
#define	NDD_2_HEA	(0x00000008)	/* Host Ethernet Adapter        */

/* <-Intentional gap left so large receive flag would match other releases-> */

#define NDD_2_LARGE_RECEIVE (0x00000100)/* using large_receive 		*/

/* interface types for benefit of parsing media address headers (ndd_type) */
#define NDD_OTHER	0x1		/* none of the following */
#define NDD_1822	0x2		/* old-style arpanet imp */
#define NDD_HDH1822	0x3		/* HDH arpanet imp */
#define NDD_X25DDN	0x4		/* x25 to imp */
#define NDD_X25		0x5		/* PDN X25 interface */
#define	NDD_ETHER	0x6		/* Ethernet I or II */
#define	NDD_ISO88023	0x7		/* Ethernet 802.3 */
#define	NDD_ISO88024	0x8		/* Token Bus */
#define	NDD_ISO88025	0x9		/* Token Ring */
#define	NDD_ISO88026	0xa		/* MAN */
#define	NDD_STARLAN	0xb
#define	NDD_P10		0xc		/* Proteon 10MBit ring */
#define	NDD_P80		0xd		/* Proteon 10MBit ring */
#define NDD_HY		0xe		/* Hyperchannel */
#define NDD_FDDI	0xf
#define NDD_LAPB	0x10
#define NDD_SDLC	0x11
#define NDD_T1		0x12
#define NDD_CEPT	0x13
#define NDD_ISDNBASIC	0x14
#define NDD_ISDNPRIMARY	0x15
#define NDD_PTPSERIAL	0x16
#define	NDD_LOOP	0x18		/* loopback */
#define NDD_EON		0x19		/* ISO over IP */
#define	NDD_XETHER	0x1a		/* obsolete 3MB experimental ethernet */
#define	NDD_NSIP	0x1b		/* XNS over IP */
#define	NDD_SLIP	0x1c		/* IP over generic TTY */

#define NDD_ATM		0x20		/* ATM device driver */
#define NDD_HDLC	0x21		/* NDD_LABP | NDD_SDLC */

#define	NDD_SCB		0x127		/* SCB device driver */
#define	NDD_FCS		0x128		/* FCS device driver */
#define	NDD_SCSI	0x129		/* SCSI device driver */
#define NDD_HIPPI	0x12a		/* HIPPI driver */
#define	NDD_SN		0x12b		/* Federation driver */
#define	NDD_FCIP	0x12c		/* IP over FC driver */
#define NDD_ISCSI       0x12d           /* iSCSI driver      */
#define NDD_VASI_TYPE	0x12e		/* VASI driver */
#define NDD_VFC         0x12f           /* virtual fibre channel client */

/* 
 * The following primitives define common NDD control operations
 */
#define	NDD_GET_STATS		(0x00000001)
#define	NDD_ENABLE_MULTICAST	(0x00000002)
#define	NDD_DISABLE_MULTICAST	(0x00000003)
#define	NDD_PROMISCUOUS_ON	(0x00000004)
#define	NDD_PROMISCUOUS_OFF	(0x00000005)
#define	NDD_ADD_FILTER		(0x00000006)
#define	NDD_DEL_FILTER		(0x00000007)
#define	NDD_MIB_QUERY		(0x00000008)
#define	NDD_MIB_GET		(0x00000009)
#define	NDD_MIB_SET		(0x0000000A)
#define	NDD_ADD_STATUS		(0x0000000B)
#define	NDD_DEL_STATUS		(0x0000000C)
#define	NDD_ENABLE_ADDRESS	(0x0000000D)
#define	NDD_DISABLE_ADDRESS	(0x0000000E)
#define	NDD_MIB_ADDR		(0x0000000F)
#define	NDD_CLEAR_STATS		(0x00000010)
/*
 * New ioctl used only in an EtherChannel adapter
 * to retrieve statistics from an adapter contained
 * in an EtherChannel
 */
#define NDD_GET_ADAPTER_STATS	(0x00000011)
/*
 * Disable MAC address check for outgoing packets
 */
#define	NDD_DISABLE_ADDRCHK	(0x00000012)
/*
 * New ioctls for flash update firmware
 */
#define NDD_READ_FLASH          (0x00000013)
#define NDD_WRITE_FLASH         (0x00000014)

#define NDD_GET_NDD             (0x00000015)

#define	NDD_DUMP_ADDR		(0x00000100)
#define	NDD_PRIORITY_ADDR	(0x00000101)
#define	NDD_GET_ALL_STATS	(0x00000102)
#define	NDD_DEBUG_TRACE		(0x00000103)
#define	NDD_SET_LINK_STATUS	(0x00000104)
#define	NDD_ENABLE_ADAPTER	(0x00000105)
#define	NDD_DISABLE_ADAPTER	(0x00000106)

/*
 * New ioctls for IPSec offload operation in ethernet adapters
 */
#define NDD_QUERY_IPSEC_OFFLOAD (0x00000107)
#define NDD_ADD_SA_CACHE        (0x00000108)
#define NDD_DELETE_SA_CACHE     (0x00000109)
#define NDD_MODIFY_SA_CACHE     (0x0000010A)
#define NDD_CLEAR_ALL_SA_CACHE  (0x0000010B)
#define NDD_IPSEC_REGISTER	(0x0000010C)
#define NDD_IPSEC_UNREGISTER	(0x0000010D)

/* Used to change an adapter's MAC address at runtime */
#define NDD_SET_MAC_ADDR        (0x0000010E)

#define NDD_NOTIFY_UNCONFIGURE	1

#define NDD_STOP_TRACE          (0x0000010F) 
#define	NDD_DEVICE_SPECIFIC	(0x00010000)

/* New ioctl used to modify an EtherChannel at runtime */
#define NDD_MODIFY_ETHCHAN	(0x00000110)

/* Shared Ethernet Adapter ioctls */
#define NDD_SEA_LIST		(0x00000112)
#define NDD_SEA_MODIFY		(0x00000113)

/* Ioctl for changing the nd_receive pointer for an EtherChannel's
 * underlying adapters
 */
#define NDD_SET_RECEIVE_FUNC	(0x00000114)

/* Ioctl for changing the ndd_ptr pointer for an EtherChannel's
 * underlying adapters
 */
#define NDD_SET_POINTER		(0x00000115)

/* Used to start tracing on an interface */
#define NDD_START_TRACE		(0x00000116)

/* Used by container devices to add filters on their underlying adapters */
#define NDD_CONT_ADD_FILTER	(0x00000117)

/* Used by container devices to delete filters on their underlying adapters */
#define NDD_CONT_DEL_FILTER	(0x00000118)

/* Used by container devices to inform their underlying devices of the
 * container's interface
 */
#define NDD_INTERFACE_CHANGED	(0x00000119)

/* Used to query nesting structure of container devices.  See ndd_tree_node
 * documentation below 
 */
#define NDD_CONT_GET_TREE_SIZE	(0x0000011A)
#define NDD_CONT_GET_TREE	(0x0000011B)

/* Ioctls for enabling/disabling large_receive feature in ethernet adapters */
#define NDD_ENABLE_LARGE_RECEIVE  (0x0000011C)
#define NDD_DISABLE_LARGE_RECEIVE (0x0000011D)

/*
 * The following status's are returned as a result of NDD_GET_LINK_STATUS.  The
 * status is returned into the 32bit integer that arg points to.
 */
#define NDD_LS_DOWN 	(0)	/* link status is down */
#define NDD_LS_UP 	(1) 	/* link status is up on the interface */
#define NDD_LS_ENABLING (2)	/* link status is indeterminate (due to */
				/*   restarting the adapter probably) */
#define NDD_LS_DEAD 	(3)	/* link status is dead */

/* Structure passed as arg for NDD_INTERFACE_CHANGED ioctl */
typedef struct ndd_if {
	caddr_t ifp;			/* Pointer to the interface (struct ifnet) */
#define NDD_INTERFACE_SET	(1)	/* Interface configured/attached */
#define NDD_INTERFACE_UNSET	(2)	/* Interface unconfigured/detached */
	ushort_t flags;
} ndd_if_t;

struct ndd_sls {
	void	(*func)();	/* status function */
	void	*param;
};
typedef struct ndd_sls ndd_sls_t;

/* 
 * Structure returned by getkerninfo KINFO_NDD
 */
struct kinfo_ndd {
	char	ndd_name[NDD_MAXNAMELEN];/* name, e.g. ``en0'' or ``tr0'' */
	char	ndd_alias[NDD_MAXNAMELEN];/* alternate name */
	__ulong32_t	ndd_flags;		/* up/down, broadcast, etc. */
	__ulong32_t	ndd_mtu;		/* maximum transmission unit */
	__ulong32_t	ndd_mintu;		/* minimum transmission unit */
	__ulong32_t	ndd_type;		/* ethernet, etc (see interface types */
	__ulong32_t	ndd_addrlen;		/* physical address length */
	u_char	ndd_addr[64];		/* physical address */
};
/*
 * Flag values for NDD_MIB_QUERY
 */
#define	MIB_NOT_SUPPORTED	(0x00)	/* MIB variable not supported by NDD */
#define	MIB_READ_ONLY		(0x01)	/* MIB variable is read only */
#define	MIB_READ_WRITE		(0x02)	/* MIB variable can be read or set */
#define	MIB_WRITE_ONLY		(0x03)	/* MIB variable can only be set */

struct ndd_mib_query {
	u_int 		mib_get[1];	/* MAC specific MIB structure */
};
typedef	struct ndd_mib_query ndd_mib_query_t;

struct ndd_mib_get {
	u_int 		mib_get[1];	/* MAC specific MIB structure */
};
typedef	struct ndd_mib_get ndd_mib_get_t;

/*
 * status codes for NDD_MIB_SET operations 
 */
#define	MIB_OK			0	/* operation was successful */
#define	MIB_NOT_SETTABLE	1	/* MIB variable is not settable */
#define	MIB_WRONG_STATE		2	/* variable is settable but not now */
#define	MIB_FAILED		3	/* NDD was unable to set variable */
#define	MIB_BAD_VALUE		4	/* incorrect value for variable */

typedef	u_int	mib_t;


/*
 * The MIB set and addr structures are used to represent a packed dynamic 
 * data structure.  Both structures contain a length field as the first few
 * bytes.  The length indicates the number of structures in the rest of the
 * data space.  Since each sub-structure is dynamic, the sub-structure cannot
 * be accessed by indexing the array pointer.  The array pointer, mib and 
 * mib_addr, in ndd_mib_set and ndd_mib_addr respectively, must be used as 
 * starting points in the data space and pointers should be used to walk 
 * through the structure.
 */
struct ndd_mib {
	mib_t	mib;	    	/* a MIB variable to set */
	u_int	status;	    	/* return status from set operation */
	u_short	mib_len;    	/* length of the MIB variable value */
	u_char 	mib_value[2];   /* value to set, length is mib_len */
};
typedef struct ndd_mib ndd_mib_t;

struct ndd_mib_set {
	u_int		count;		/* number of MIB variables to set */
	ndd_mib_t	mib[1];		/* MIB variable. */
};
typedef	struct ndd_mib_set ndd_mib_set_t;

/*
 * These structures are used to receive/get the Address Table by the
 * NDD_MIB_ADDR ioctl().
 */
#define NDD_MIB_OTHER           1
#define NDD_MIB_INVALID         2
#define NDD_MIB_VOLATILE        3
#define NDD_MIB_NONVOLATILE     4

struct ndd_mib_addr_elem  {
	u_int		status;
	u_short		addresslen;
	u_char		address[2];
};
typedef struct ndd_mib_addr_elem ndd_mib_addr_elem_t;

struct ndd_mib_addr {
	u_int			count;
	ndd_mib_addr_elem_t	mib_addr[1];
};
typedef struct ndd_mib_addr ndd_mib_addr_t;


struct ndd_statblk {
	u_int		code;		/* status block code		*/
	u_int		option[10];	/* additional information 	*/
};
typedef struct ndd_statblk ndd_statblk_t;

/* 
 * Status block codes for ndd_statblk
 */
#define	NDD_HARD_FAIL	(0x00000001)	/* A hardware failure has occurred */
#define	NDD_LIMBO_ENTER	(0x00000002)	/* Entered Network Recovery Mode */
#define	NDD_LIMBO_EXIT	(0x00000004)	/* Exited Network Recovery Mode */
#define	NDD_CONNECTED	(0x00000008)	/* Device open successful */
#define	NDD_STATUS	(0x00000010)	/* Various status and event info */
#define	NDD_BAD_PKTS	(0x00000020)	/* A bad packet was received */

#define	NDD_STAT_BLOCK	(0x00100000)	/* Start device specific codes here */

/* 
 * Reason codes for ndd_statblk
 */
#define	NDD_ADAP_CHECK	(0x00000001)	/* Adapter checkstop condition */
#define	NDD_BUS_ERROR	(0x00000002)	/* Bus error */
#define	NDD_CMD_FAIL	(0x00000003)	/* A device command has failed */
#define	NDD_PIO_FAIL	(0x00000004)	/* A PIO operation has failed */
#define	NDD_UCODE_FAIL	(0x00000005)	/* Failure of device microcode */
#define	NDD_TX_ERROR	(0x00000006)	/* A transmission error has occurred */
#define	NDD_TX_TIMEOUT	(0x00000007)	/* Transmission timeout error */
#define	NDD_RCV_ERROR	(0x00000008)	/* A receive error has occured */
#define	NDD_AUTO_RMV	(0x00000009)	/* Auto-remove error detected */
#define	NDD_ADDR_CHANGE	(0x0000000A)	/* MAC address changed at runtime */
#define NDD_ADAPTER_ADDED (0x0000000B)  /* Adapter added dynamically */
#define NDD_ADAPTER_DELETED (0x0000000C)/* Adapter removed dynamically */

#define	NDD_REASON_CODE	(0x00000100)	/* Start device specific reasons here */


struct ndd_config {
	int	seq_number;
	caddr_t	dds;
	int	l_vpd;
	caddr_t	p_vpd;
	caddr_t	ucode;
};
typedef struct ndd_config	ndd_config_t;

#ifdef __64BIT_KERNEL
struct ndd_config32 {
	int	seq_number;
	ptr32	dds;
	int	l_vpd;
	ptr32	p_vpd;
	ptr32	ucode;
};
typedef struct ndd_config32	ndd_config32_t;
#endif /* __64BIT_KERNEL */

/* This type definition macro can be used in configuration methods */
#ifdef __64BIT_KERNEL
	#define NDD_CONFIG_T	ndd_config32_t
#else
	#define NDD_CONFIG_T	ndd_config_t
#endif

/*
 * definition of NDD event tracing
 */

/* event definition */
typedef struct ndd_event {
    struct ndd *ndd_addr;
    char ndd_name[NDD_MAXNAMELEN];
    __ulong32_t ndd_refcnt;
    __ulong32_t ndd_flags;
    char ndd_evt;
    cpu_t ndd_cpu;
    void *ndd_callers[16];
} ndd_event_t;

#ifdef _KERNEL
extern struct ndd *ndd;
/* ndd_events_buf will contains the events. This buffer is
 * dynamically allocated. It is a circular buffer */
extern ndd_event_t *ndd_event_buf;

/* current ndd event index in ndd_events_buf */
extern int ndd_event_index;
/* ndd_event_size define the current size of ndd_event_buf */
extern int ndd_event_size;

#endif


/*
 * Definitions for the ndd_reserved field.
 *
 * For ATM NDD's see the reserved_mapper structure in cdli_atmuser.h
 *
 */

/* 
 * EtherChannel uses ndd_reserved[14] and ndd_reserved[15] to store a
 * pointer to itself in each of its underlying adapters (it uses two
 * array positions to accomodate a 64-bit pointer)
 */

#define ndd_spec_ks	ndd_reserved[0]
#define ndd_spec_conf   ndd_reserved[1]


/*
 * Data structure used to return result for NDD_CONT_GET_TREE_SIZE ioctl
 */
typedef struct ndd_num_children {
	unsigned int num_children;
} ndd_num_children_t;

/*
 * Data structures used by the NDD_CONT_GET_TREE ioctl
 *
 * The ioctl represents the returned tree as a pre-order linearization.
 * Each node specifies how many direct children it has (e.g. with the number
 * of children between ()'s ):
 *     A
 *    / \
 *   B   C    ==>  A(2), B(3), D(0), E(0), F(0), C(1), G(0)
 *  /|\  |
 * D E F G
 *
 * The buffer passed to the ioctl starts with an ndd_tree_header followed by an
 * array of ndd_tree_node. The number of nodes is specified by the 'capacity'
 * field of the header. The 'used' header field contains the number of nodes
 * already used in the tree and is updated by the ioctl call. This allows a
 * tree of ioctl calls to cooperate filling a single buffer (e.g. the layout of
 * the buffer for the above tree before and after an ioctl call to B):
 *
 * [capacity:7 used:1][A][ ][ ][ ][ ][ ][ ]
 * [capacity:7 used:5][A][B][D][E][F][ ][ ]
 *
 * Thus, when a driver receives the NDD_CONT_GET_TREE ioctl, it:
 *  - starts writing at element [header.used] of the node array
 *  - makes sure it doesn't go past header.capacity 
 *  - updates header.used on completion.  
 *
 * On ioctl failure, header.used and the elements [0,header.used) of the node
 * array should be unmodified.  [header.used, header.capacity) may be.
 */

typedef struct ndd_tree_header {
	unsigned int	capacity;	/* total number of nodes allocated */
	unsigned int	used;		/* number of nodes used */
} ndd_tree_header_t;

typedef struct ndd_tree_node {
	unsigned int	num_children;

	/* taken from ndd_t */
	char		adapter_name[NDD_MAXNAMELEN];
	__ulong32_t	ndd_flags;
	__ulong32_t	ndd_2_flags;
	ndd_genstats_t	ndd_genstats;

	/* taken from adapter control structure */
	uint64_t	tree_node_flags;
	uint32_t	adapter_specific[16];
} ndd_tree_node_t;

/*
 * Flags for tree_node_flags field of ndd_tree_node
 */

/* Set on adapters by their SEA owner */
#define NDD_TREE_NODE_PHYSICAL	(0x00000001)
#define NDD_TREE_NODE_CONTROL	(0x00000002)

/* Set on a SEA or children of an EtherChannel */
#define NDD_TREE_NODE_PRIMARY	(0x00000004)
#define NDD_TREE_NODE_BACKUP	(0x00000008)
#define NDD_TREE_NODE_LIMBO	(0x00000010)

#endif	/* _H_NDD */
