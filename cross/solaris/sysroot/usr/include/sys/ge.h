
/*
 * Copyright (c) 1995-2001 by Sun Microsystems, Inc.
 * All rights reserved.
 */

#ifndef	_SYS_GE_H
#define	_SYS_GE_H

#pragma ident	"@(#)ge.h	2.16	04/04/01 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Gem diagnostics IOCTLS.		-DJ
 */
#define	GEMIOC		('G' << 8)

#define	GE_SET_LOOP_MODE	(GEMIOC|1)	/* Set Gem Loopback mode */
#define	GE_GET_LOOP_MODE	(GEMIOC|2)	/* Get Gem Loopback modes */

/*
 * Loopback modes: For diagnostic testing purposes the GEM card
 * can be placed in loopback mode.
 * There are three modes of loopback provided by the driver,
 * MAC loopback, PCS loopback and SERDES loopback.
 */
#define	GEM_LOOPBACK_OFF		0
#define	GEM_MAC_LOOPBACK_ON		1	/* doesn't work */
#define	GEM_PCS_LOOPBACK_ON 		2	/* doesn't work */
#define	GEM_SER_LOOPBACK_ON 		4
typedef struct {
	int loopback;
} ge_loopback_t;			/* -DJ */


#ifdef _KERNEL

#ifndef	D_HOTPLUG
#define	D_HOTPLUG	0x00
#endif

#ifdef	SUNTRUNKING
#define	GETRUNK
#include	<sys/nettr.h>
#include	<sys/nettr_ge.h>
#endif

extern	timestruc_t hrestime;

/* Named Dispatch Parameter Management Structure */
typedef struct geparam_s {
	uint32_t ge_param_min;
	uint32_t ge_param_max;
	uint32_t ge_param_val;
	char   *ge_param_name;
} geparam_t;

#define	GE_PARAM_CNT	49

/*
 * Definitions for module_info.
 */

#define		GEIDNUM	(130)		/* module ID number */
#define		GENAME		"ge"		/* module name */
#define		GEMINPSZ	(0)		/* min packet size */
#define		GEMAXPSZ	(ETHERMTU +14) 	/* max packet size */
#define		GEHIWAT	(128 * 1024)	/* hi-water mark */
#define		GELOWAT	(1)		/* lo-water mark */

/*
 * Per-Stream instance state information.
 *
 * Each instance is dynamically allocated at open() and free'd
 * at close().  Each per-Stream instance points to at most one
 * per-device structure using the sb_gep field.  All instances
 * are threaded together into one list of active instances
 * ordered on minor device number.
 */


#define	NMCHASH	64			/* # of multicast hash buckets */
#define	INIT_BUCKET_SIZE	16	/* Initial Hash Bucket Size */
#define	NMCFILTER_BITS	256		/* # of multicast filter bits */

struct	gestr {
	struct	gestr	*sb_nextp;	/* next in list */
	queue_t	*sb_rq;			/* pointer to our rq */
	struct	ge *sb_gep;		/* attached device */
	t_uscalar_t sb_state;		/* current DL state */
	t_uscalar_t sb_sap;		/* bound sap */
	uint32_t sb_flags;		/* misc. flags */
	minor_t sb_minor;		/* minor device number */

	struct	ether_addr
		*sb_mctab[NMCHASH];	/* Hash table of multicast addrs */
	uint32_t sb_mccount[NMCHASH];	/* # valid addresses in mctab[i] */
	uint32_t sb_mcsize[NMCHASH];	/* Allocated size of mctab[i] */

	uint16_t sb_ladrf[NMCFILTER_BITS/16];	/* Multicast filter bits */
	uint16_t sb_ladrf_refcnt[NMCFILTER_BITS];
					/* Reference count for filter bits */

	kmutex_t	sb_lock;	/* protect this structure */
	int		(*sb_canputp)();/* Control canput procedure upstream */
	void		(*sb_putp)();	/* Control put procedure for upstream */

#ifndef SOL2_8
	uint32_t	sb_notifications;	/* DLPI notifications */
#endif
};


#define	MCHASH(a)	((*(((uchar_t *) (a)) + 0) ^		\
			*(((uchar_t *) (a)) + 1) ^		\
			*(((uchar_t *) (a)) + 2) ^		\
			*(((uchar_t *) (a)) + 3) ^		\
			*(((uchar_t *) (a)) + 4) ^		\
			*(((uchar_t *) (a)) + 5)) % (uint32_t) NMCHASH)


/* per-stream flags */
#define	GESFAST		0x01	/* "M_DATA fastpath" mode */
#define	GESRAW		0x02	/* M_DATA plain raw mode */
#define	GESALLPHYS	0x04	/* "promiscuous mode" */
#define	GESALLMULTI	0x08	/* enable all multicast addresses */
#define	GESALLSAP	0x10	/* enable all ether type values */
#define	GESCKSUM	0x20	/* Enable hardware tcp checksumming */
#define	GESMULTI	0x40	/* enable multicast addresses */
#define	GESSERLPBK	0x80	/* Enable SERDES loopback -DJ */
#define	GESMACLPBK	0x100	/* Enable MAC int loopback -DJ */

/*
 * MAC Operation Mode
 */

#define	GEMAC_MODE_NONE		0x0	/* Not Enabled Yet */
#define	GEMAC_MODE_UNI		0x1	/* Unicast Mode */
#define	GEMAC_MODE_MULTI	0x2	/* Multicast Mode */
#define	GEMAC_MODE_PROM		0x4	/* Promiscuous Mode */
#define	GEMAC_MODE_LOOP		0x8	/* Loopback Mode */


/*
 * Maximum number of receive descriptors posted to the chip.
 */
#define	GERPENDING		(gep->ge_rpending)
#define	GERPENDING_FE	256	/* recv buffers posted for 10/100 Mbps */
#define	GERPENDING_GE	GE_RMDMAX /*  recv buffers posted for 1000 Mbps */

/*
 * Maximum number of transmit descriptors for lazy reclaim.
 */
#define	GETPENDING	(gep->ge_tpending)
#define	GETPENDING_FE	256	/* Max xmit buffers posted for 10/100 Mbps */
#define	GETPENDING_GE	GE_TMDMAX /* Max xmit buffers posted for 1000 Mbps */


		/* DMA Mapping types */
#define	GE_DMA_NONE	0	/*  No DMA buffers are allocated */
#define	GE_DMA_FAST	2	/*  Use Fast DMA Mapping */
#define	GE_DMA_REGULAR	4	/*  Use Regular DMA Mapping */

/* how many dvma bufs to allocate */
#define	GETDVMA		(gep->ge_tdvma)
/* #define	GETDVMA		256 aaa */


/*
 * Full DLSAP address length (in struct dladdr format).
 */
#define	GEADDRL	(sizeof (uint16_t) + ETHERADDRL)

/*
 * Return the address of an adjacent descriptor in the given ring.
 */
/* aaa NEXTRMD macro is not used anywhere! */
#define	NEXTRMD(gep, rmdp)	(((rmdp) + 1) == (gep)->ge_rmdlimp	\
	? (gep)->ge_rmdp : ((rmdp) + 1))
#define	NEXTTMD(gep, tmdp)	(((tmdp) + 1) == (gep)->ge_tmdlimp	\
	? (gep)->ge_tmdp : ((tmdp) + 1))

#define	MSECOND(t)	t
#define	SECOND(t)	t*1000
#define	GE_TICKS	MSECOND(100)

#define	GE_NTRIES_LOW		(SECOND(5)/GE_TICKS)   /* 5 Seconds */
#define	GE_NTRIES_HIGH		(SECOND(5)/GE_TICKS)   /* 5 Seconds */
#define	GE_NTRIES_LOW_10	(SECOND(2)/GE_TICKS)   /* 2 Seconds */
#define	GE_LINKDOWN_TIME	(SECOND(2)/GE_TICKS)   /* 2 Seconds */


/* GEM ASIC Revision Numbers */
#define	GE_GEMREV_1_0	0x1

/*
 * Link poll interval for detecting change of transceivers
 */
#define	GE_LINKCHECK_TIMER	SECOND(30)

/* Link bringup modes */
#define	GE_AUTO_BRINGUP		0
#define	GE_FORCED_BRINGUP	1

/*
 * Transceivers selected for use by the driver.
 */
#define	GE_EXTERNAL_TRANSCEIVER		0
#define	GE_INTERNAL_TRANSCEIVER		1
#define	GE_NO_TRANSCEIVER		2

/*
 * states for manually creating the link down condition
 */
#define	GE_LINKDOWN_OK		0
#define	GE_FORCE_LINKDOWN	1
#define	GE_LINKDOWN_STARTED	2
#define	GE_LINKDOWN_DONE	3


/*
 * GEM Supported PHY devices
 * GEM ASIC supports a built in Gigabit Serial LInk Interface and MII/GMII/
 * External SERDES interfaces with shared pins.
 * On some product implementations, the built-in Serial Link may not be present
 * either because the Serial Link circuitry does not work or because the product
 * needs to use only the MII/GMII interface.
 * When both the Serial Link and MII/GMII PHY's are present, the driver normally
 * tries to bring up both the links. If both of them come up, it will select the
 * link defined by the "ge_default_link" variable by default.
 * The user may use the configuration variable
 * ge_select_link to manually select
 * either the Serial Link or the MII/GMII PHY to be used.
 */


/*
 * Values for the ge_non-serial-link field
 * For now, GMII is not used.
 */
#define	GE_NO_SHARED_PIN_PHY		0
#define	GE_MII_PRESENT			1
#define	GE_SERDES_PRESENT		2
#define	GE_GMII_PRESENT			3

/*
 * Values for the default selection when both the serial link and
 * the MII/GMII links are present.
 */

#define	GE_DEFAULT_SERIAL_LINK	0
#define	GE_DEFAULT_MII_LINK	1

/* Values for the ge_select_link field to manually select the PHY */
#define	GE_AUTO_PHY			0	/* Select PHY automatically */
#define	GE_USE_SERIAL_LINK		1	/* Select the serial-link */
#define	GE_USE_NON_SERIAL_LINK		2	/* Select the non-serial-link */

/* Speed definitions for ge_param_speed */
#define	GE_SPEED_10	10
#define	GE_SPEED_100	100
#define	GE_SPEED_1000	1000

/* Mode definitions for ge_param_mode */
#define	GE_MODE_HDX	0
#define	GE_MODE_FDX	1

/* ge_datapath definitions */

#define	GE_DP_SERIAL_LINK	0
#define	GE_DP_SERDES		1
#define	GE_DP_MII		2
#define	GE_DP_GMII		3

/* ge_linkup_state" definitions */

#define	GE_START_LINK_BRINGUP	0
#define	GE_SERIAL_LINK_BRINGUP	1
#define	GE_SERDES_LINK_BRINGUP	2
#define	GE_MII_LINK_BRINGUP	3
#define	GE_DEFAULT_LINK_BRINGUP	4
#define	GE_ALT_LINK_BRINGUP	5


/* rcv thread status	*/
#define	GE_RCV_THREAD_CREATED	1
#define	GE_RCV_THREAD_RCVD	2
#define	GE_RCV_THREAD_POLL	4
#define	GE_RCV_THREAD_DESTROY	8
#define	GE_RCV_THREAD_SLEEP	0x10
#define	GE_RCVQ_DEPTH		1024


/* aaa new */


typedef struct ge_txinfo {
	unsigned short		flags;
	signed short		idx;
	uint32_t		reserved;
	mblk_t			*mp;	/* XXX must be in _LAST_ descr */
	ddi_dma_handle_t	handle;
} ge_txinfo_t;

#define	TXB_BINDMAP	0x8000
#define	TXB_TINYBUF	0x4000
#define	TXB_FASTMAP	0x2000

typedef struct ge_rxinfo {
	mblk_t			*mp;
	ddi_dma_handle_t	handle;
	uint32_t		ioaddr;
	uint32_t		offset; /* offset into handle, for SHEFFIELD */
} ge_rxinfo_t;



typedef struct drv_queue {
	mblk_t *drvq_head;
	mblk_t *drvq_tail;
	int 	drvq_count;
	unsigned int drvq_drops;
}drv_queue_t;

#define	TX_RSRV_SEGS	256		/* aaa orig: 128, try 256 */
#define	TX_FASTDVMA_MIN	1024
#define	TX_STREAM_MIN	512
	/* TX tinybufs, for small mblks */
/* aaa #define	TX_MAX_TBUFS		512	*/
#define	TX_BCOPY_MAX		256
#define	GE_MDS_8 8192
#define	GE_MDS_7 4096
#define	GE_MDS_6 2048
#define	GE_MDS_5 1024
#define	GE_MDS_4 512


/*
 * GE Device Channel instance state information.
 *
 * Each instance is dynamically allocated on first attach.
 */
struct	ge {
	struct	ge		*ge_nextp;	/* next in a linked list */
	dev_info_t		*ge_dip;	/* associated dev_info */
	/*
	 * used by suntrunking, add any future elements after this
	 * #ifdef SUNTRUNKING.
	 */
#ifdef	SUNTRUNKING
	int			ge_id;		/* instance number */
	getrunk_t		*ge_trunkp;	/* trunking ptr if trunked */
	struct nettr_stats 	ge_stats;	/* netwoek statistics */
	struct ether_addr	ge_savaddr;	/* used in trunking */
#endif
	uint_t			ge_promisc_cnt; /* Promiscuous streams open */

	int			ge_pci_mode;	/* sbus/pci device */
	int			ge_asic_rev;	/* GEM ASIC rev no. */
	int			ge_burstsizes;	/* binary encoded val */
	int			ge_64bit_xfer;	/* 64-bit Sbus xfers */
	uint32_t		ge_rxfifo_size;	/* RX FIFO size */

	ssize_t			ge_mymtu;	/* size of mtu, for dlinfo */
						/* either 1500 or 9000 */
	int			ge_bufsize;	/* size of RX bufs posted */
	int			ge_rpending;	/* Max.no. of RX bufs posted */
	int			ge_tpending;	/* Max.no. of tX bufs posted */
	int			ge_tdvma;	/* no. of tX dvma bufs */
	int			ge_jdvmax;	/* max# of tX dvma bufs used */
	int			ge_jtxnodvma; /* max# of tX dvma bufs unavail */
	int			ge_jtxdvmadeep;	/* max# tX dvma bufs unavail */
	int			ge_tx_cur_cnt;	/* No. of packets for int_me */

	/* ge_txinfo_t		txinfo[GE_TMDMAX];	*/
	ge_txinfo_t		*txinfo; /* ptr to array of ge_txinfo_t */
	ge_rxinfo_t		rxinfo[GE_RMDMAX];

	int			ge_mifpoll_enable;
	int			ge_frame_enable;
	int			ge_lance_mode_enable;
	int			ge_ngu_enable;
	int			ge_link_pulse_disabled;
	int			ge_xmit_dma_mode;
	int			ge_rcv_dma_mode;
	struct	ether_addr	ge_factaddr;	/* factory mac address */
	struct	ether_addr	ge_ouraddr;	/* individual address */
	uint32_t		ge_addrflags;	/* address flags */
	uint32_t		ge_flags;	/* misc. flags */
	uint32_t		ge_alloc_flag;	/* Buffer alloc. status flags */
	uint32_t		ge_wantw;	/* xmit: out of resources */

	volatile struct	ge_global	*ge_globregp;	/* GE global regs */
	volatile struct	ge_etx		*ge_etxregp;	/* GE ETX regs */
	volatile struct	ge_erx		*ge_erxregp;	/* GE ERX regs */
	volatile struct	ge_bmac		*ge_bmacregp;	/* BigMAC registers */
	volatile struct	ge_mif		*ge_mifregp;	/* GE transceiver */
	volatile struct	ge_pcslink	*ge_pcsregp;	/* GE PCS registers */
	unsigned char			*ge_romp;	/* fcode rom pointer */

	uint32_t	*ge_sw_reset_reg;

	uint32_t	*ge_Sbus_reset_reg;	/* mapping for Sbus reset. */
	uint32_t	*ge_Sbus_config_reg;	/* mapping for Sbus config. */
	uint32_t	*ge_Sbus_status_reg;	/* mapping for Sbus Status. */
	uint32_t	*ge_Sbus_id_reg;

	queue_t			*ge_ip4q;	/* ipv4 read queue */
	queue_t			*ge_ip6q;	/* ipv6 read queue */

	struct	ge_tmd		*ge_tmdp;	/* xmit descriptor ring start */
	struct	ge_tmd		*ge_tmdlimp;	/* xmit descriptor ring end */

	volatile struct	ge_tmd	*ge_tnextp;	/* next free tmd */
	volatile struct	ge_tmd	*ge_tcurp;	/* next tmd to reclaim (used) */

	/* Receive fields */
	uint32_t		ge_rx_kick;	/* RX kick register val */
	uint32_t		ge_rx_completion; /* RX completion reg val */

	int32_t			ge_ovrflpkts;

	struct	ge_rmd		*ge_rmdp;	/* rcv descriptor ring start */
	struct	ge_rmd		*ge_rmdlimp;	/* rcv descriptor ring end */

	volatile struct	ge_rmd	*ge_rnextp;	/* next chip rmd */
	volatile struct	ge_rmd	*ge_rlastp;	/* last free rmd */

	/*
	 * these are handles for the dvma resources reserved
	 * by dvma_reserve
	 */
	ddi_dma_handle_t	ge_dvmarh;	/* dvma recv handle */
/* aaa after new xmit scheme works, we don't need ge_dvmaxh */
	ddi_dma_handle_t	ge_dvmaxh;	/* dvma xmit handle */

	ddi_dma_handle_t	ge_ndmarh[GE_RMDMAX];
/* aaa after new xmit scheme works, we don't need ge_ndmaxh[GE_TMDMAX] */
	ddi_dma_handle_t	ge_ndmaxh[GE_TMDMAX];
	ddi_dma_handle_t	ge_rxspareh;
	int			ge_rcv_handle_cnt;
	int			ge_xmit_handle_cnt;

	int			ge_rx_reset_issued;
	int			ge_tx_reset_issued;
	int			ge_rxmac_reset_issued;
	int			ge_txmac_reset_issued;

	int			ge_global_reset_issued;
	uint32_t		ge_gerpending_mask;
	int			ge_germdmax_mask;
	int			ge_init_macregs;

	int			ge_mii_phyad;	/* Address of the PHY in use */
	int			ge_mii_transceiver;  /* current PHY in use */

	int			ge_mii_linkup_10;
	int			ge_pace_count;	/* pacing pkt count */

	int			ge_nlasttries;
	int			ge_ntries;
	int			ge_delay;
	int			ge_linkup_attempts;

	int			ge_rcv_thread_status;
	int			ge_polling_on;
	int			ge_mifpoll_data;
	int			ge_mifpoll_flag; /* indicates MIF interrupt */

	int			ge_pauseTX;	/* pcs link - pause TX enable */
	int			ge_pauseRX;	/* pcs link - pause RX enable */
	int			ge_macfdx;	/* mac full-duplex mode */
	timeout_id_t		ge_timerid;	/* timer id for link handling */

	uint16_t		ge_aner;	/* MII ANER register */

	int			ge_linkup;	/* selected link status */
	int			ge_linkup_state; /* link bringup state */
	int			ge_linkup_changed; /* link bringup state */

	ulong_t			ge_pagesize;
	int			ge_linkcheck;
	int			ge_linksts_msg;
	int			ge_datapath;	/* datapath selection */
	caddr_t			ge_g_nd;	/* head of the */
						/* named dispatch table */

	ddi_device_acc_attr_t	ge_dev_attr;
	ddi_iblock_cookie_t	ge_cookie;	/* interrupt cookie */
	ddi_acc_handle_t	ge_globregh;   /* GE global regs */
	ddi_acc_handle_t	ge_etxregh;    /* GE ETX regs */
	ddi_acc_handle_t	ge_erxregh;    /* GE ERX regs */
	ddi_acc_handle_t	ge_bmacregh;   /* BigMAC registers */
	ddi_acc_handle_t	ge_mifregh;    /* GE transceiver */
	ddi_acc_handle_t	ge_pcsregh;    /* GE PCS regs */
	ddi_acc_handle_t	ge_Sbus_reset_regh;	/* Sbus reset Reg. */
	ddi_acc_handle_t	ge_Sbus_config_regh;	/* Sbus Configuration */
							/* Register */
	ddi_acc_handle_t	ge_Sbus_status_regh;	/* Gem Sbus Status */
							/* Register */
	ddi_acc_handle_t	ge_Sbus_id_regh;	/* Sbus Id  Register */

	ddi_acc_handle_t	ge_sw_reset_regh;	/* GE Reset Register */

	ddi_dma_cookie_t	ge_md_c;	/* trmd dma cookie */
	ddi_acc_handle_t	ge_mdm_h;	/* trmd memory handle */
	ddi_dma_handle_t	ge_md_h;	/* trmdp dma handle */
	ddi_acc_handle_t	ge_romh;	/* rom handle */

	ddi_dma_handle_t	txfast_handle;
	/* aaa orig: short int		txfast_queue[TX_RSRV_SEGS]; */
	uint16_t		*txfast_queue;
	int32_t			txfast_quehd;
	int			txfast_alloc; /* gep->txfast_handle allocated */


	caddr_t			tbuf_kaddr;
	uint32_t		tbuf_ioaddr;
	ddi_dma_handle_t	tbuf_handle;


	/*
	 * DDI dma handle, kernel virtual base,
	 * and io virtual base of IOPB area.
	 */
	ddi_dma_handle_t	ge_iopbhandle;
	uintptr_t		ge_iopbkbase;
	uintptr_t		ge_iopbiobase;
	kstat_t	*ge_ksp;	/* kstat pointer */

	void			(*geread_func) (register struct ge *gep,
				    volatile struct ge_rmd *rmdp,
				    register int rmdi, uint64_t flags);

	void			(*gecopy_func) (register struct ge *gep,
				    volatile struct ge_rmd *rmdp,
				    register int rmdi, uint64_t flags);

	int			(*gestart_func) (queue_t *wq,
				    register mblk_t *mp,
				    register struct ge *gep,
				    boolean_t from_wput);

	struct xcvr_table	*ge_xcvr_table; /* XCVR Fill up Table */
	kmutex_t		ge_xmitlock;	/* protect xmit-side fields */
	kmutex_t		ge_intrlock;	/* protect intr-side fields */
	kmutex_t		ge_linklock;	/* protect link-side fields */

	kmutex_t		ge_rcvlock;	/* protect rcv-side fields */
	kmutex_t		ge_ouraddr_lock; /* protect ouraddr access */
	kcondvar_t		ge_rcv_poll;	/* protect rcv fields */
	kcondvar_t		ge_suspend_cv;	/* protect suspend/resume */
	kthread_id_t		ge_rcv_thread;	/* RCV Processing Thread */

	drv_queue_t		drv_queue;	/* Our Local Queue */


/* aaa after new xmit scheme works, we don't need *ge_tmblkp[GE_TMDMAX] */
	mblk_t		*ge_tmblkp[GE_TMDMAX]; /* mblks associated with TMD */
	mblk_t		*ge_rmblkp[GE_RMDMAX];	/* mblks associated with RMD */
	geparam_t	ge_param_arr[GE_PARAM_CNT];
	uint32_t	ge_param_display[GE_PARAM_CNT]; /* control displaying */

/* Link Input/Output stats */
	uint32_t	ge_ipackets;
	uint32_t	ge_ierrors;
	uint32_t	ge_opackets;
	uint32_t	ge_oerrors;
	uint32_t	ge_collisions;
	uint32_t	ge_ifspeed;

	/*
	 * PSARC 1997/198 : 64bit kstats
	 */
	uint64_t 	ge_ipackets64;
	uint64_t 	ge_opackets64;
	uint64_t 	ge_rbytes64;
	uint64_t 	ge_obytes64;

	/*
	 * PSARC 1997/247 : RFC 1643
	*/
	uint32_t 	ge_align_errors;
	uint32_t 	ge_fcs_errors;
	uint32_t 	ge_multi_collisions;
	uint32_t 	ge_sqe_errors;
	uint32_t 	ge_defer_xmts;
	uint32_t 	ge_ex_collisions;
	uint32_t 	ge_macxmt_errors;
	uint32_t 	ge_carrier_errors;
	uint32_t 	ge_toolong_errors;
	uint32_t 	ge_macrcv_errors;

/* MAC TX Event stats */
	uint32_t	ge_txmac_urun;
	uint32_t	ge_txmac_maxpkt_err;
	uint32_t	ge_excessive_coll;
	uint32_t	ge_late_coll;
	uint32_t	ge_first_coll;
	uint32_t	ge_defer_timer_exp;
	uint32_t	ge_peak_attempt_cnt;

/* MAC RX Event stats */
	uint32_t	ge_no_free_rx_desc;	/* no free rx desc. */
	uint32_t	ge_rx_overflow;
	uint32_t	ge_rx_hang;
	uint32_t	ge_rx_align_err;
	uint32_t	ge_rx_crc_err;
	uint32_t	ge_rx_length_err;
	uint32_t	ge_rx_code_viol_err;

/* MAC Control event stats */
	uint32_t	ge_pause_rxcount;	/* PAUSE Receive cnt */
	uint32_t	ge_pause_oncount;
	uint32_t	ge_pause_offcount;
	uint32_t	ge_pause_time_count;
	uint32_t	ge_mac_mode; /* MAC Operation mode */

/* Software event stats */
	uint32_t	ge_inits;
	uint32_t	ge_tnocar;	/* Link down counter */
	uint32_t	ge_jab;
	uint32_t	ge_txinits;
	uint32_t	ge_notmds;
	uint32_t	ge_nocanput;
	uint32_t	ge_allocbfail;
	uint32_t	ge_drop;

	uint32_t	ge_rxinits;
	uint32_t	ge_rx_corrupted;
	uint32_t	ge_rx_bad_pkts;

/* Fatal errors */
	uint32_t	ge_rxtag_err;

/* PCI fatal error stats */
	uint32_t	ge_pci_badack;	/* Bad ACK */
	uint32_t	ge_pci_dtrto;	/* Delayed PCI Transaction  Timeout */

/* From the PCI Configuration space staus register */
	uint32_t	ge_pci_data_parity_err;	/* Data parity error detected */
	uint32_t	ge_pci_signal_target_abort;
	uint32_t	ge_pci_rcvd_target_abort;
	uint32_t	ge_pci_rcvd_master_abort;
	uint32_t	ge_pci_signal_system_err;
	uint32_t	ge_pci_det_parity_err;

/* Bus Speed and Size */
	uint32_t	ge_pci_speed;
	uint32_t	ge_pci_size;


/* SBus fatal error stats */
	uint32_t	ge_sbus_txlaterr;
	uint32_t	ge_sbus_rxlaterr;
	uint32_t	ge_sbus_slvparerr;
	uint32_t	ge_sbus_txparerr;
	uint32_t	ge_sbus_rxparerr;
	uint32_t	ge_sbus_slverrack;
	uint32_t	ge_sbus_txerrack;
	uint32_t	ge_sbus_rxerrack;

/* To check if transmitter is hung */
	uint32_t	ge_starts;

	/*
	 * MIB II variables
	 */
	uint32_t	ge_rcvbytes;	/* # bytes received */
	uint32_t	ge_xmtbytes;	/* # bytes transmitted */
	uint32_t	ge_multircv;	/* # multicast packets received */
	uint32_t	ge_multixmt;	/* # multicast packets for xmit */
	uint32_t	ge_brdcstrcv;	/* # broadcast packets received */
	uint32_t	ge_brdcstxmt;	/* # broadcast packets for xmit */
	uint32_t	ge_norcvbuf;	/* # rcv packets discarded */
	uint32_t	ge_noxmtbuf;	/* # xmit packets discarded */

#ifdef XMIT_SERIAL_QUEUE
	/* A syncq implementation. */
	mblk_t		*ge_sqfirst;	/* first mblk chain or NULL */
	mblk_t		*ge_sqlast;	/* last mblk chain or NULL */
	kmutex_t	ge_sqlock;	/* lock before using any member */
	uint16_t	ge_sqrefcnt;	/* count of threads using */
	uint16_t	ge_sqnmblks;
#endif

	/*
	 * Additional counters for checksum errors and driver queue full.
	 */
	uint32_t	ge_csumerr;	/* checksum errors */
	uint32_t	ge_queue_full_cnt; /* driver queue full counter */

	/*
	 * Link Status
	 */
	uint32_t	ge_link_up;
	/*
	 * Added the counters below to check for DMA hang of SBUS GEM.
	 */
	uint64_t	ge_ipackets64_save;
	uint64_t	ge_opackets64_save;
	uint32_t	ge_rxhung;
	uint32_t	ge_txhung;
	uint32_t	ge_do_sbus_reset;
	/*
	 * Loopback re-initiate
	 */
	uint32_t	ge_lb_init;
};


/* flags */
#define	GERUNNING	0x01	/* chip is initialized */
#define	GEPROMISC	0x02	/* promiscuous mode enabled */
#define	GEMULTICAST	0x04	/* Multicast mode enabled */
#define	GESUSPENDED	0x08	/* suspended interface */
#define	GEINITIALIZED	0x10	/* interface initialized */
#define	GENOTIMEOUTS	0x20	/* disallow timeout rescheduling */
#define	GETXINIT	0x40	/* TX Portion Init'ed */
#define	GERXINIT	0x80	/* TX Portion Init'ed */
#define	GEMACLOOPBACK	0x100   /* device has MAC int loopback -DJ */
#define	GESERLOOPBACK	0x200	/* device has SERDES int loopback -DJ */
#define	GETHREADEXIT	0x400	/* sigal receive polling thread to exit */

/* Mac address flags */

#define	GE_FACTADDR_PRESENT	0x01	/* factory MAC id present */
#define	GE_FACTADDR_USE	0x02	/* use factory MAC id */

struct	gekstat {
/* Link Input/Output stats */
	struct kstat_named	gek_ipackets;
	struct kstat_named	gek_ierrors;
	struct kstat_named	gek_opackets;
	struct kstat_named	gek_oerrors;
	struct kstat_named	gek_collisions;
	struct kstat_named	gek_ifspeed;	/* Interface Speed */
	struct kstat_named	gek_maxframesize; /* Max frame size, jmbo pkt */

	/*
	 * required by kstat for MIB II objects(RFC 1213)
	 */
	struct  kstat_named	gek_rcvbytes; 	/* # octets received */
						/* MIB - ifInOctets */
	struct  kstat_named	gek_xmtbytes; 	/* # octets transmitted */
						/* MIB - ifOutOctets */
	struct  kstat_named	gek_multircv; 	/* # multicast packets */
						/* delivered to upper layer */
						/* MIB - ifInNUcastPkts */
	struct  kstat_named	gek_multixmt; 	/* # multicast packets */
						/* requested to be sent */
						/* MIB - ifOutNUcastPkts */
	struct  kstat_named	gek_brdcstrcv;	/* # broadcast packets */
						/* delivered to upper layer */
						/* MIB - ifInNUcastPkts */
	struct  kstat_named	gek_brdcstxmt;	/* # broadcast packets */
						/* requested to be sent */
						/* MIB - ifOutNUcastPkts */
	struct  kstat_named	gek_norcvbuf; 	/* # rcv packets discarded */
						/* MIB - ifInDiscards */
	struct  kstat_named	gek_noxmtbuf; 	/* # xmt packets discarded */
						/* MIB - ifOutDiscards */
/* Software event stats */
	struct kstat_named	gek_inits;
	struct kstat_named	gek_mac_mode;
	struct kstat_named	gek_xmit_dma_mode;
	struct kstat_named	gek_rcv_dma_mode;

	struct kstat_named	gek_tnocar;	/* Link down counter */
	struct kstat_named	gek_nocanput;
	struct kstat_named	gek_allocbfail;


/* MAC Control event stats */
	struct kstat_named	gek_pause_rxcount; /* PAUSE Receive count */
	struct kstat_named	gek_pause_oncount;
	struct kstat_named	gek_pause_offcount;
	struct kstat_named	gek_pause_time_count;

/* MAC TX Event stats */
	struct kstat_named	gek_txmac_urun;
	struct kstat_named	gek_txmac_maxpkt_err;
	struct kstat_named	gek_excessive_coll;
	struct kstat_named	gek_late_coll;
	struct kstat_named	gek_first_coll;
	struct kstat_named	gek_defer_timer_exp;
	struct kstat_named	gek_peak_attempt_cnt;
	struct kstat_named	gek_jab;
	struct kstat_named	gek_notmds;
	struct kstat_named	gek_txinits;

/* MAC RX Event stats */
	struct kstat_named	gek_drop;
	struct kstat_named	gek_rxinits;

	struct kstat_named	gek_no_free_rx_desc; /* no free rx desc. */
	struct kstat_named	gek_rx_overflow;
	struct kstat_named	gek_rx_hang;

	struct kstat_named	gek_rxtag_err; /* Fatal Error */
	struct kstat_named	gek_rx_align_err;
	struct kstat_named	gek_rx_crc_err;
	struct kstat_named	gek_rx_length_err;
	struct kstat_named	gek_rx_code_viol_err;


/* PCI fatal error stats */
	struct kstat_named	gek_pci_badack;  /* Bad ACK */
	struct kstat_named	gek_pci_dtrto; /* Delayed Transaction Timeout */
/* From the PCI Configuration space staus register */
	struct kstat_named	gek_pci_data_parity_err;
						/* Data parity error detected */
	struct kstat_named	gek_pci_signal_target_abort;
	struct kstat_named	gek_pci_rcvd_target_abort;
	struct kstat_named	gek_pci_rcvd_master_abort;
	struct kstat_named	gek_pci_signal_system_err;
	struct kstat_named	gek_pci_det_parity_err;

/* PCI Bus Size and Speed */
	struct kstat_named	gek_pci_speed;
	struct kstat_named	gek_pci_size;


/* SBus fatal error stats */
	struct kstat_named	gek_sbus_txlaterr;
	struct kstat_named	gek_sbus_rxlaterr;
	struct kstat_named	gek_sbus_slvparerr;
	struct kstat_named	gek_sbus_txparerr;
	struct kstat_named	gek_sbus_rxparerr;
	struct kstat_named	gek_sbus_slverrack;
	struct kstat_named	gek_sbus_txerrack;
	struct kstat_named	gek_sbus_rxerrack;

	/*
	 * PSARC 1997/198
	 */
	struct kstat_named	gek_ipackets64;	/* packets received */
	struct kstat_named	gek_opackets64;	/* packets transmitted */
	struct kstat_named	gek_rbytes64;	/* bytes received */
	struct kstat_named	gek_obytes64;	/* bytes transmitted */

	/*
	 * PSARC 1997/247 : RFC 1643
	 * SNMP Variables
	*/
	struct kstat_named	gek_align_errors;
					/* dot3StatsAlignmentErrors */
	struct kstat_named	gek_fcs_errors;
					/* dot3StatsFCSErrors */
	struct kstat_named	gek_multi_collisions;
					/* dot3StatsMultipleCollisionFrames */
	struct kstat_named	gek_sqe_errors;
					/* dot3StatsSQETestErrors */
	struct kstat_named	gek_defer_xmts;
					/* dot3StatsDeferredTransmissions */
	struct kstat_named	gek_ex_collisions;
					/* dot3StatsExcessiveCollisions */
	struct kstat_named	gek_macxmt_errors;
					/* dot3StatsInternalMacTransmitErrors */
	struct kstat_named	gek_carrier_errors;
					/* dot3StatsCarrierSenseErrors  */
	struct kstat_named	gek_toolong_errors;
					/* dot3StatsFrameTooLongs */
	struct kstat_named	gek_macrcv_errors;
					/* dot3StatsInternalMacReceiveErrors  */

	/*
	 * Additional kstat counters for checksum errors and
	 * failing to put incoming packets to driver's internal queue.
	 */
	struct kstat_named	gek_csumerr;	/* checksum errors */
	struct kstat_named	gek_queue_cnt;	/* driver queue counter */
	struct kstat_named	gek_queue_full_cnt; /* queue full count */
	struct kstat_named	gek_link_up;	/* Link Status */

};

/* TBD: new value ? */
#define	GEDRAINTIME	(400000)	/* # microseconds xmit drain */

#define	ROUNDUP(a, n)	(((a) + ((n) - 1)) & ~((n) - 1))
#define	ROUNDUP2(a, n)	(uchar_t *)((((uintptr_t)(a)) + ((n) - 1)) & ~((n) - 1))

/*
 * Xmit/receive buffer structure.
 * This structure is organized to meet the following requirements:
 * - rcv buffs start on an GEBURSTSIZE boundary.
 * - rcv mblks are large enough to contain max frame (9k) plus
 *   (2 x GEBURSTSIZE) rounded up to the next GEBURSTSIZE
 * GEBUFSIZE is the size of rcv buffer to allocate.
 */
#define		GEBURSTSIZE	(128)
#define		GEBURSTMASK	(GEBURSTSIZE - 1)
/* #define		GEBUFSIZE	(ETHERMTU + 228) */
#define		GEBUFSIZE	(1728)
#define		JUMBOMTU	(9000)	/* for jumbo pkt */
#define		GEJUMBOBUFSIZE	(10000)
#define		GEHEADROOM	(34)

/* Offset for the first byte in the receive buffer */
#define	GE_FSTBYTE_OFFSET	2
#define	GE_CKSUM_OFFSET	14

/*
 * Private DLPI full dlsap address format.
 */
struct	gedladdr {
	struct	ether_addr	dl_phys;
	uint16_t dl_sap;
};
#endif	/* _KERNEL */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_GE_H */
