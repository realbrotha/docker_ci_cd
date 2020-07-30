/*
 * Copyright (c) 1992-1999 by Sun Microsystems, Inc.
 * All rights reserved.
 */

#ifndef	_SYS_HME_H
#define	_SYS_HME_H

#pragma	ident "@(#)qfe.h 2.8	03/08/06 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef D_HOTPLUG
#define D_HOTPLUG 0x00
#endif

#ifndef ETHERTYPE_IPV6
#define ETHERTYPE_IPV6 (0x86dd)        /* IPv6 */
#endif


#define	HME_IOC		0x60201ae1	/* random */
typedef struct {
	int		cmd;
	int		reserved[4];
} hme_ioc_hdr_t;

/* cmd */
#define	HME_IOC_GET_SPEED	0x100
#define	HME_IOC_SET_SPEED	0x110

#ifdef QFETRUNK
#define	HME_IOC_TRUNK		0x120

/* trunk commands */
#define	HME_IOC_TRUNK_SETUP	0x01
#define	HME_IOC_TRUNK_RELEASE	0x02
#define	HME_IOC_TRUNK_GETCONF	0x03
#define	HME_IOC_TRUNK_GETSTATS	0x04
#endif

typedef enum {
                SEVERITY_NONE,
                SEVERITY_LOW,
                SEVERITY_MID,
                SEVERITY_HIGH,
                NO_SEVERITY
} severity_t;

typedef enum  {
		DONT_WAIT = 0,
		DO_WAIT
} waitflag_t;

typedef enum  {
		DVMA,
		DMA,
		SDMA
} dma_method_t;

typedef enum  {
		MIF_POLL_STOP,
		MIF_POLL_START
} soft_mif_enable_t;

#define	HME_NO_XCVR		0
#define	HME_INTERNAL_XCVR	1
#define	HME_EXTERNAL_XCVR	2

#ifdef SHEFFIELD
#define qfe_dev_is_usable(a, b) u4ft_ddi_dev_is_usable(a, (u4ft_waitflag_t)b)
#else
typedef severity_t u4ft_severity_t;
typedef waitflag_t u4ft_waitflag_t;
static int qfe_dev_is_usable(dev_info_t *, waitflag_t);
static void u4ft_ddi_report_fault(dev_info_t *, u4ft_severity_t, const char *);
#endif

typedef struct data_descr {
	caddr_t kaddr;
	uint_t ioaddr;
	uint_t len;
	ddi_dma_handle_t handle;
	uint_t offset;
} data_descr_t;

/* mode */
#define	HME_AUTO_SPEED	0
#define	HME_FORCE_SPEED	1

/* speed */
#define	HME_SPEED_10	10
#define	HME_SPEED_100	100

typedef struct {
	hme_ioc_hdr_t	hdr;
	int		mode;
	int		speed;
} hme_ioc_cmd_t;

/* half-duplex or full-duplex mode */

#define	HME_HALF_DUPLEX	0
#define	HME_FULL_DUPLEX	1

#if defined SOL2_4 || defined SOL2_5 || defined SOL2_5_1
#define	ND_BASE		('N' << 8)	/* base */
#define	ND_GET		(ND_BASE + 0)	/* Get a value */
#define	ND_SET		(ND_BASE + 1)	/* Set a value */

#define	NDE_ALLOC_COUNT 4
#define	NDE_ALLOC_SIZE	(sizeof (NDE) * NDE_ALLOC_COUNT)

#define	DDI_UMEM_NOSLEEP 0x01


typedef int int32_t;
typedef unsigned int uintptr_t;
typedef unsigned short uint16_t;
/*
 * Named dispatch table entry
 */
typedef struct nde_s {
	char	*nde_name;
	pfi_t	nde_get_pfi;
	pfi_t	nde_set_pfi;
	caddr_t nde_data;
} NDE;

/*
 * Name dispatch table
 */
typedef struct nd_s {
	int	nd_free_count;	/* number of unused nd table entries */
	int	nd_size;	/* size (in bytes) of current table */
	NDE	*nd_tbl;	/* pointer to table in heap */
} ND;

typedef struct iocblk *IOCP;
typedef void * ddi_umem_cookie_t;

extern	int msgsize();
extern	void usec_delay();
extern	void merror(), miocack(), miocnak(), mcopymsg();
extern	void dlerrorack(), dlokack(), dlbindack(), dlphysaddrack();
extern	void dluderrorind();
extern	mblk_t *desballoc(unsigned char *, int, int, frtn_t *);

#define	ddi_get32(handle, dev_addr) ddi_getl(handle, dev_addr)
#define	ddi_get16(handle, dev_addr) ddi_getw(handle, dev_addr)
#define	ddi_get8(handle, dev_addr) ddi_getb(handle, dev_addr)
#define	ddi_put32(handle, dev_addr, value) ddi_putl(handle, dev_addr, value)
#define	ddi_put16(handle, dev_addr, value) ddi_putw(handle, dev_addr, value)
#define	ddi_put8(handle, dev_addr, value) ddi_putb(handle, dev_addr, value)


static	int nd_set_default(queue_t *, MBLKP, char *, caddr_t);
static	int nd_get_default(queue_t *, MBLKP, caddr_t);
static	int nd_get_names(queue_t *, MBLKP, caddr_t);
static	caddr_t mi_alloc(uint_t, int);
static	void mi_free(char *);
static	int mi_iprintf(char *, va_list, pfi_t, char *);
static	int mi_mpprintf(MBLKP, char *, ...);
static	long mi_strtol(char *, char **, int);
static	int mi_mpprintf_putc(char *, int);
static	int mi_strcmp(char *, char *);
static	void *ddi_umem_alloc(size_t, int, ddi_umem_cookie_t *);
static	void ddi_umem_free(ddi_umem_cookie_t);
#endif

#if defined SOL2_4
/*
 * definig bogus stuff to help compile complete.
 */
/*
 * PCI command register bits, taken from 'pci.h' in Solaris 2.5.1.
 */
#define PCI_COMM_MAE            0x0002   /* memory access enable */
#define PCI_COMM_ME             0x0004   /* master enable */
#define PCI_COMM_PARITY_DETECT  0x0040
#define PCI_COMM_SERR_ENABLE    0x0100

/*
 * Data Access Handle, taken from 'dditypes.h' in Solaris 2.5.1.
 */
typedef void *ddi_acc_handle_t;

typedef struct fake_io_handle {
	dev_info_t *dip;
	ddi_dma_handle_t dmahandle;
	size_t length;
	uint_t rnumber;
	caddr_t kaddrp;
	off_t offset;
	off_t len;
} ddi_acc_hdl_t;

/*
 * Device Access Attributes, taken from 'dditypes.h' in Solaris 2.5.1.
 */
typedef struct ddi_device_acc_attr {
        ushort_t devacc_attr_version;
        uchar_t devacc_attr_endian_flags;
        uchar_t devacc_attr_dataorder;
} ddi_device_acc_attr_t;

#define DDI_DEVICE_ATTR_V0      0x0001

typedef struct ddi_dma_attr {
        uint_t          dma_attr_version;       /* version number */
        uint64_t        dma_attr_addr_lo;       /* low DMA address range */
        uint64_t        dma_attr_addr_hi;       /* high DMA address range */
        uint64_t        dma_attr_count_max;     /* DMA counter register */
        uint64_t        dma_attr_align;         /* DMA address alignment */
        uint_t          dma_attr_burstsizes;    /* DMA burstsizes */
        uint32_t        dma_attr_minxfer;       /* min effective DMA size */
        uint64_t        dma_attr_maxxfer;       /* max DMA xfer size */
        uint64_t        dma_attr_seg;           /* segment boundary */
        int             dma_attr_sgllen;        /* s/g length */
        uint32_t        dma_attr_granular;      /* granularity of device */
        uint_t          dma_attr_flags;         /* Bus specific DMA flags */
} ddi_dma_attr_t;

#define DMA_ATTR_V0      0x0001

/*
 * endian-ness flags, taken from 'dditypes.h' in Solaris 2.5.1.
 */
#define  DDI_STRUCTURE_LE_ACC   0x01
#define  DDI_STRUCTURE_BE_ACC   0x02

/*
 * Data ordering values, taken from 'dditypes.h' in Solaris 2.5.1.
 */
#define DDI_STRICTORDER_ACC     0x00

/*
 * Sequential, unidirectional, block-sized and block aligned transfers,
 * taken from 'ddidmareq.h' in SOlaris 2.7.
 */
#define DDI_DMA_STREAMING       0x0040

static uint16_t ddi_getw(ddi_acc_handle_t, uint16_t *);
static uint32_t ddi_getl(ddi_acc_handle_t, uint32_t *);
static void ddi_putb(ddi_acc_handle_t, uint8_t *, uint8_t);
static void ddi_putw(ddi_acc_handle_t, uint16_t *, uint16_t);
static void ddi_putl(ddi_acc_handle_t, uint32_t *, uint32_t);
static int ddi_dma_set_sbus64(ddi_dma_handle_t, ulong_t);
static int ddi_regs_map_setup(dev_info_t *, uint_t, caddr_t *, offset_t,
                                offset_t, ddi_device_acc_attr_t *,
                                ddi_acc_handle_t *);
static void ddi_regs_map_free(ddi_acc_handle_t *);
static int ddi_dma_alloc_handle(dev_info_t *, ddi_dma_attr_t *,
                        int (*callback) (caddr_t), caddr_t,
                         ddi_dma_handle_t *);
static int ddi_dma_mem_alloc(ddi_dma_handle_t, size_t,
			ddi_device_acc_attr_t *, uint_t,
                        int (*waitfp) (caddr_t), caddr_t,
                        caddr_t *, size_t *,
                        ddi_acc_handle_t *);
static void ddi_dma_mem_free(ddi_acc_handle_t *handlep);
static int ddi_dma_addr_bind_handle(ddi_dma_handle_t, struct as *,
                        caddr_t addr, size_t len, uint_t,
                        int (*callback) (caddr_t) , caddr_t,
                        ddi_dma_cookie_t *, uint_t *);

static int ddi_dma_unbind_handle(ddi_dma_handle_t);
static void ddi_dma_free_handle(ddi_acc_handle_t *);
static int ddi_get_iblock_cookie(dev_info_t *,  uint_t, ddi_iblock_cookie_t *);
#endif

/*
 * Ether-type is specifically big-endian, but data region is unknown endian
 */
#if defined SOL2_4 || defined SOL2_5 || defined SOL2_5_1
#define	ether_bcopy(a, b)	(bcopy((caddr_t)a, (caddr_t)b, 6))
#else
#define	ether_bcopy(a, b)	(bcopy(a, b, 6))
#endif

#ifdef  QFETRUNK
#define	HME_TR_POLICY_MAX	32
/*
 * hme policies: a number between 1 and HME_TR_POLICY_MAX
 * meaning of each policy needs to be documented for the user
 */

/* hme types */
#define	HME_TYPE_HME_SBUS	1
#define	HME_TYPE_HME_PCI	2
#define	HME_TYPE_QFE_SBUS	3
#define	HME_TYPE_QFE_PCI	4

#define	HME_TRUNK_MAXSIZE	4	/* for this release */
/*
 * for trunking 1.2 release
 */
#define	NET_TRUNK_MAXSIZE	16

/* status masks */
#define	HME_SM_LINK		0x01	/* 0 == dn   1 == up  */
#define	HME_SM_MODE		0x02	/* 0 == hdx  1 == fdx */
#define	HME_SM_SPEED		0x04	/* 0 == 10   1 == 100 */
#define	HME_SM_XCVR		0x08	/* 0 == int  1 == ext */

typedef struct {
	struct ether_addr	tr_mac_addr;	/* original mac address */
	int			tr_instance;	/* hme instance number */
	uchar_t			tr_type;	/* shows type of hme card */
	uchar_t			tr_trunked;	/* 1 if part of trunk */
	int			tr_head;	/* head instance */
	uchar_t			tr_policy;
	uchar_t			tr_status;	/* status flags */
	uchar_t			tr_ipg[3];	/* ipg0,1,2 ipg0 != 0 */
						/* if lance_mode */
	uchar_t			tr_cap[3];	/* adv,our,lp capabilities */
} hme_tr_conf_t;

typedef struct {
	int	aggregate;	/* true or false */
	int	hme_instance;
	uint32_t hme_ipackets;
	uint32_t hme_ierrors;
	uint32_t hme_opackets;
	uint32_t hme_oerrors;
	uint32_t hme_coll;
	uint32_t hme_crc;	/* actually, crc is not in netstat */
} hme_tr_stats_t;

/*
 * Note: HME_TRUNK_MAXERR should be large enough to accomodate  (320)
 *       sizeof (hme_tr_stats_t) * (HME_TRUNK_MAXSIZE + 1)      (32*5)
 */
#define	HME_TRUNK_MAXERR	320	/* errbuf size */
#if 0
#define	HME_TRUNK_MAXCONF	(HME_TRUNK_MAXERR/(sizeof (hme_tr_conf_t)))
#endif
#define	HME_TRUNK_MAXCONF	32

typedef struct {
	int		cmd;		/* always == HME_IOC_TRUNK */
	uchar_t		tr_command;	/* sub command */
	int		tr_head;
	uchar_t		tr_trunksize;	/* 2 or 4 */
	uchar_t		tr_policy;

	/* Use this if tr_trunksize is 0, invalid entries are -1 */
	int		tr_members[HME_TRUNK_MAXSIZE];

	/* Returned items */
	uchar_t		tr_error_return;	/* 1 means errors */
	int		tr_count;
	union {
		/* error strings  */
		/*
		 * Sequence of null terminated strings,
		 * where count shows total bytes including last null.
		 * allows for up to four 80-char strings.
		 */
		char		tr_error[HME_TRUNK_MAXERR];

		/* configuration for ALL hme interfaces */
		hme_tr_conf_t	tr_conf[HME_TRUNK_MAXCONF];

		/* individual statistics + last one is aggregate */
		hme_tr_stats_t	tr_stats[HME_TRUNK_MAXSIZE+1];
	} tr_ret;
} hme_tr_ioc_t;

#endif /* QFETRUNK */

#ifdef _KERNEL
/* Named Dispatch Parameter Management Structure */
typedef struct hmeparam_s {
	uint32_t hme_param_min;
	uint32_t hme_param_max;
	uint32_t hme_param_val;
	char   *hme_param_name;
} hmeparam_t;

typedef struct hme_stats {
	uint32_t hme_ipackets;
	uint32_t hme_ierrors;
	uint32_t hme_opackets;
	uint32_t hme_oerrors;
	uint32_t hme_coll;
	uint32_t hme_defer;
	uint32_t hme_fram;
	uint32_t hme_crc;
	uint32_t hme_sqerr;
	uint32_t hme_cvc;
	uint32_t hme_lenerr;
	uint32_t hme_ifspeed;
	uint32_t hme_buff;
	uint32_t hme_oflo;
	uint32_t hme_uflo;
	uint32_t hme_missed;
	uint32_t hme_tlcol;
	uint32_t hme_trtry;
	uint32_t hme_fstcol;
	uint32_t hme_tnocar;
	uint32_t hme_inits;
	uint32_t hme_nocanput;
	uint32_t hme_allocbfail;
	uint32_t hme_runt;
	uint32_t hme_jab;
	uint32_t hme_babl;
	uint32_t hme_tmder;
	uint32_t hme_txlaterr;
	uint32_t hme_rxlaterr;
	uint32_t hme_slvparerr;
	uint32_t hme_txparerr;
	uint32_t hme_rxparerr;
	uint32_t hme_slverrack;
	uint32_t hme_txerrack;
	uint32_t hme_rxerrack;
	uint32_t hme_txtagerr;
	uint32_t hme_rxtagerr;
	uint32_t hme_eoperr;
	uint32_t hme_notmds;
	uint32_t hme_notbufs;
	uint32_t hme_norbufs;
	uint32_t hme_clsn;

	/*
	 * MIB II variables
	 */
	uint32_t hme_rcvbytes;		/* # bytes received */
	uint32_t hme_xmtbytes;		/* # bytes transmitted */
	uint32_t hme_multircv;		/* # multicast packets received */
	uint32_t hme_multixmt;		/* # multicast packets for xmit */
	uint32_t hme_brdcstrcv;		/* # broadcast packets received */
	uint32_t hme_brdcstxmt;		/* # broadcast packets for xmit */
	uint32_t hme_norcvbuf;		/* # rcv packets discarded */
	uint32_t hme_noxmtbuf;		/* # xmit packets discarded */

	uint32_t hme_phy_inits;
	uint32_t hme_tx_inits;
	uint32_t hme_rx_inits;

	/*
	 * PSARC 1997/198 : 64bit kstats
	 */
	uint64_t hme_ipackets64;
	uint64_t hme_opackets64;
	uint64_t hme_rbytes64;
	uint64_t hme_obytes64;

	/*
	 * PSARC 1997/247 : RFC 1643
	 */
	uint32_t hme_align_errors;
	uint32_t hme_fcs_errors;
	uint32_t hme_multi_collisions;
	uint32_t hme_sqe_errors;
	uint32_t hme_defer_xmts;
	uint32_t hme_ex_collisions;
	uint32_t hme_macxmt_errors;
	uint32_t hme_carrier_errors;
	uint32_t hme_toolong_errors;
	uint32_t hme_macrcv_errors;
        /*
	 * cksum flags
	 */
        uint32_t hme_tcpcksum_errors;
        uint32_t hme_hwcksum_errors;

  	/* link status */
	uint32_t hme_link_up;

	/* link duplex */
	uint32_t hme_link_duplex;

} hme_stats_t;

#ifdef  QFETRUNK
#define	HSTAT(hmep, x) \
	hmep->hme_stats.x++; \
	if (hmep->hme_trunkp) { \
		hmep->hme_trunkp->tr_stats.x++; \
	}
#define	HSTATN(hmep, x, n) \
	hmep->hme_stats.x += n; \
	if (hmep->hme_trunkp) { \
		hmep->hme_trunkp->tr_stats.x += n; \
	}
#else
#define	HSTAT(hmep, x)		hmep->hme_stats.x++;
#define	HSTATN(hmep, x, n)	hmep->hme_stats.x += n;
#endif

#ifdef  QFETRUNK
typedef struct hme * (*fptr_hmep_t)();

/*
 * Structure for TRUNKING support
 */
typedef struct hmetrunk_s {
	struct hme		*tr_members[NET_TRUNK_MAXSIZE];
	struct hme		*trunk_head;
	kmutex_t		tr_lock;	/* protect this structure */
	uint_t			tr_trunksize;	/* Save the trunk size here */
	uint_t			tr_mask;	/* value to & index with */
	uint_t			tr_policy;	/* policy */
	uint_t			tr_robin;	/* last index in round robin */
	struct hme_stats	tr_stats;	/* aggregate statistics */
	struct hmetrunk_s	*nextp;		/* Next trunk */
	int			tr_alternate[NET_TRUNK_MAXSIZE];
	uint_t			tr_nextalternate;
} hmetrunk_t;

#define	qt_head(hmep) (hmep->hme_trunkp && \
		(hmep == hmep->hme_trunkp->trunk_head))
#define	qt_member(hmep) (hmep->hme_trunkp && \
		(hmep != hmep->hme_trunkp->trunk_head))
#else	/* define a dummy structure for non trunking */
typedef struct  hmetrunk_s {
	int	reserved;
} hmetrunk_t;
#endif

static hmeparam_t	hme_param_arr[] = {
	/* min		max		value		name */
	{  HME_NO_XCVR,	HME_EXTERNAL_XCVR, HME_NO_XCVR, "transceiver_inuse"},
	{  0,		1,		0,		"link_status"},
	{  0,		1,		0,		"link_speed"},
	{  0,		1,		0,		"link_mode"},
	{  0,		255,		8,		"ipg1"},
	{  0,		255,		4,		"ipg2"},
	{  0,		1,		0,		"use_int_xcvr"},
	{  0,		255,		0,		"pace_size"},
	{  0,		1,		1,		"adv_autoneg_cap"},
	{  0,		1,		1,		"adv_100T4_cap"},
	{  0,		1,		1,		"adv_100fdx_cap"},
	{  0,		1,		1,		"adv_100hdx_cap"},
	{  0,		1,		1,		"adv_10fdx_cap"},
	{  0,		1,		1,		"adv_10hdx_cap"},
	{  0,		1,		0,		"autoneg_cap"},
	{  0,		1,		0,		"100T4_cap"},
	{  0,		1,		0,		"100fdx_cap"},
	{  0,		1,		0,		"100hdx_cap"},
	{  0,		1,		0,		"10fdx_cap"},
	{  0,		1,		0,		"10hdx_cap"},
	{  0,		1,		0,		"lp_autoneg_cap"},
	{  0,		1,		0,		"lp_100T4_cap"},
	{  0,		1,		0,		"lp_100fdx_cap"},
	{  0,		1,		0,		"lp_100hdx_cap"},
	{  0,		1,		0,		"lp_10fdx_cap"},
	{  0,		1,		0,		"lp_10hdx_cap"},
	{  0,		255,		0,		"instance"},
	{  0,		1,		1,		"lance_mode"},
	{  0,		31,		16,		"ipg0"},
};


#define	hme_param_transceiver	(hmep->hme_param_arr[0].hme_param_val)
#define	hme_param_linkup	(hmep->hme_param_arr[1].hme_param_val)
#define	hme_param_speed		(hmep->hme_param_arr[2].hme_param_val)
#define	hme_param_mode		(hmep->hme_param_arr[3].hme_param_val)
#define	hme_param_ipg1		(hmep->hme_param_arr[4].hme_param_val)
#define	hme_param_ipg2		(hmep->hme_param_arr[5].hme_param_val)
#define	hme_param_use_intphy	(hmep->hme_param_arr[6].hme_param_val)
#define	hme_param_pace_count	(hmep->hme_param_arr[7].hme_param_val)
#define	hme_param_autoneg	(hmep->hme_param_arr[8].hme_param_val)
#define	hme_param_anar_100T4	(hmep->hme_param_arr[9].hme_param_val)
#define	hme_param_anar_100fdx	(hmep->hme_param_arr[10].hme_param_val)
#define	hme_param_anar_100hdx	(hmep->hme_param_arr[11].hme_param_val)
#define	hme_param_anar_10fdx	(hmep->hme_param_arr[12].hme_param_val)
#define	hme_param_anar_10hdx	(hmep->hme_param_arr[13].hme_param_val)
#define	hme_param_bmsr_ancap	(hmep->hme_param_arr[14].hme_param_val)
#define	hme_param_bmsr_100T4	(hmep->hme_param_arr[15].hme_param_val)
#define	hme_param_bmsr_100fdx	(hmep->hme_param_arr[16].hme_param_val)
#define	hme_param_bmsr_100hdx	(hmep->hme_param_arr[17].hme_param_val)
#define	hme_param_bmsr_10fdx	(hmep->hme_param_arr[18].hme_param_val)
#define	hme_param_bmsr_10hdx	(hmep->hme_param_arr[19].hme_param_val)
#define	hme_param_aner_lpancap	(hmep->hme_param_arr[20].hme_param_val)
#define	hme_param_anlpar_100T4	(hmep->hme_param_arr[21].hme_param_val)
#define	hme_param_anlpar_100fdx	(hmep->hme_param_arr[22].hme_param_val)
#define	hme_param_anlpar_100hdx	(hmep->hme_param_arr[23].hme_param_val)
#define	hme_param_anlpar_10fdx	(hmep->hme_param_arr[24].hme_param_val)
#define	hme_param_anlpar_10hdx	(hmep->hme_param_arr[25].hme_param_val)
#define	hme_param_device	(hmep->hme_param_arr[26].hme_param_val)
#define	hme_param_lance_mode	(hmep->hme_param_arr[27].hme_param_val)
#define	hme_param_ipg0		(hmep->hme_param_arr[28].hme_param_val)

#define	HME_PARAM_CNT	29


/* command */

#define	HME_ND_GET	ND_GET
#define	HME_ND_SET	ND_SET

/* default IPG settings */
#define	IPG1	8
#define	IPG2	4

#if defined SOL2_4 || defined SOL2_5 || defined SOL2_5_1
extern	int msgsize();
extern	void merror(), miocack(), miocnak(), mcopymsg();
extern	void dlerrorack(), dlokack(), dlbindack(), dlphysaddrack();
extern	void dluderrorind();
extern	mblk_t *desballoc(unsigned char *, int, int, frtn_t *);
#endif

/*
 * Declarations and definitions specific to the
 * FEPS 10/100 Mbps Ethernet (hme) device.
 */

/*
 * Definitions for module_info.
 */
#define	HMEIDNUM	(131)		/* module ID number */
#define	HMENAME		"qfe"		/* module name */
#define	HMEMINPSZ	(0)		/* min packet size */
#define	HMEMAXPSZ	1514		/* max packet size */
#define	HMEHIWAT	(128 * 1024)	/* hi-water mark */
#define	HMELOWAT	(1)		/* lo-water mark */

/*
 * Per-Stream instance state information.
 *
 * Each instance is dynamically allocated at open() and free'd
 * at close().  Each per-Stream instance points to at most one
 * per-device structure using the sb_hmep field.  All instances
 * are threaded together into one list of active instances
 * ordered on minor device number.
 */
#define	NMCHASH	64			/* # of multicast hash buckets */
#define	INIT_BUCKET_SIZE	16	/* Initial Hash Bucket Size */
typedef struct hmestr {
	struct	hmestr	*sb_nextp;	/* next in list */
	queue_t	*sb_rq;			/* pointer to our read queue */
	struct	hme *sb_hmep;		/* attached device */
	t_uscalar_t sb_state;		/* current DL state */
	t_uscalar_t sb_sap;		/* bound sap */
	uint_t sb_flags;		/* misc. flags */
	minor_t sb_minor;		/* minor device number */
	struct ether_addr
		*sb_mctab[NMCHASH];	/* Hash table of multicast addrs */
	uint_t sb_mccount[NMCHASH];	/* # valid addresses in mctab[i] */
	uint_t sb_mcsize[NMCHASH];	/* Allocated size of mctab[i] */
	uint16_t sb_ladrf[4];		/* Multicast filter bits */
	uint16_t sb_ladrf_refcnt[64];	/* Reference count for filter bits */
	kmutex_t sb_lock;		/* protect this structure */
#if !defined SOL2_8
	uint32_t sb_notifications;	/* DLPI notifications */
#endif
} hmestr_t;

#define	MCHASH(a)	((*(((uchar_t *) (a)) + 0) ^		\
			*(((uchar_t *) (a)) + 1) ^		\
			*(((uchar_t *) (a)) + 2) ^		\
			*(((uchar_t *) (a)) + 3) ^		\
			*(((uchar_t *) (a)) + 4) ^		\
			*(((uchar_t *) (a)) + 5)) % (uint_t) NMCHASH)

/* per-stream flags */
#define	HMESFAST	0x01	/* "M_DATA fastpath" mode */
#define	HMESRAW		0x02	/* M_DATA plain raw mode */
#define	HMESALLPHYS	0x04	/* "promiscuous mode" */
#define	HMESALLMULTI	0x08	/* enable all multicast addresses */
#define	HMESALLSAP	0x10	/* enable all ether type values */
#define	HMESCKSUM	0x20	/* Enable hardware tcp checksumming */

/*
 * Maximum # of multicast addresses per Stream.
 */
#define	HMEMAXMC	64
#define	HMEMCALLOC	(HMEMAXMC * sizeof (struct ether_addr))

/*
 * Maximum number of receive descriptors posted to the chip.
 * QFETRUNK: was 64
 */
#define	HMERPENDING	128

/*
 * Maximum number of transmit descriptors for lazy reclaim.
 */
#define	HMETPENDING	64

/*
 * Full DLSAP address length (in struct dladdr format).
 */
#define	HMEADDRL	(sizeof (uint16_t) + ETHERADDRL)

/*
 * Return the address of an adjacent descriptor in the given ring.
 */
#define	NEXTRMD(hmep, rmdp)	(((rmdp) + 1) == (hmep)->hme_rmdlimp	\
	? (hmep)->hme_rmdp : ((rmdp) + 1))
#define	NEXTTMD(hmep, tmdp)	(((tmdp) + 1) == (hmep)->hme_tmdlimp	\
	? (hmep)->hme_tmdp : ((tmdp) + 1))
#define	PREVTMD(hmep, tmdp)	((tmdp) == (hmep)->hme_tmdp		\
	? ((hmep)->hme_tmdlimp - 1) : ((tmdp) - 1))

#define	MSECOND(t)	t
#define	SECOND(t)	t*1000
#define	HME_TICKS	MSECOND(100)

#define	HME_LINKCHECK_TIMER	SECOND(30)

#define	ALL_MACHINES		0x00
#define	SUN4D_MACHINE		0x01

#define	HME_ADAPTER		0x00
#define	QFE_S_ADAPTER		0x01
#define	QFE_P_ADAPTER		0x02

#define	MAX_LINK_DOWN		5

#define	HME_2P0_REVID		0xa0 /* hme - feps. */
#define	HME_2P1_REVID		0x20
#define	HME_2P1_REVID_OBP	0x21
#define	HME_1C0_REVID		0xc0 /* cheerio 1.0, hme 2.0 equiv. */
#define	HME_2C0_REVID		0xc1 /* cheerio 2.0, hme 2.2 equiv. */

#define	HME_NTRIES_LOW		(SECOND(5)/HME_TICKS)	/* 5 Seconds */
#define	HME_NTRIES_HIGH		(SECOND(5)/HME_TICKS)	/* 5 Seconds */
#define	HME_NTRIES_LOW_10	(SECOND(2)/HME_TICKS)	/* 2 Seconds */
#define	HME_LINKDOWN_TIME	(SECOND(2)/HME_TICKS)	/* 2 Seconds */

#define	HME_LINKDOWN_OK		0
#define	HME_FORCE_LINKDOWN	1
#define	HME_LINKDOWN_STARTED	2
#define	HME_LINKDOWN_DONE	3

#define	P1_0    0x100

#define	HME_HWAN_TRY		0 /* Try Hardware autonegotiation */
#define	HME_HWAN_INPROGRESS	1 /* Hardware autonegotiation in progress */
#define	HME_HWAN_SUCCESFUL	2 /* Hardware autonegotiation succesful */
#define	HME_HWAN_FAILED		3 /* Hardware autonegotiation failed */

struct	hmesave {
	ulong_t hme_starts;
	ulong_t hme_opackets;
};

/*
 * HME Device Channel instance state information.
 *
 * Each instance is dynamically allocated on first attach.
 */
typedef struct hme {
	struct	hme		*hme_nextp;	/* next in a linked list */
	dev_info_t		*hme_dip;	/* associated dev_info */
	int			hme_id;		/* instance */
#ifdef  QFETRUNK
	hmetrunk_t		*hme_trunkp;	/* trunk ptr, if trunked */
#endif
#ifdef RX_DRAIN_QUEUE
	mblk_t **rx_dq;
	uint_t rx_dq_size;       /* Size of the receive drain queue. */
	uint_t rx_dq_wr_index;
	uint_t rx_dq_rd_index;
	uint_t rx_dq_rd_pending;
	kthread_t *rx_dq_thread;
	kmutex_t rx_dq_mutex;
	kcondvar_t rx_dq_cv;
#endif
	uint32_t		promisc_phys_cnt; /* Promiscous streams open */
	uint32_t		promisc_multi_cnt;
	int			hme_asicrev;
	int			hme_mifpoll_enable;
	int			hme_frame_enable;
	int			hme_lance_mode_enable;
	int			hme_rxcv_enable;

	uint32_t		hme_config;	/* Config register store*/
	uint32_t		hme_xif_config;
	uint32_t		hme_etx_config;
	uint32_t		hme_erx_config;
	uint32_t		hme_tx_config;
	uint32_t		hme_rx_config;
	uint32_t		hme_mif_config;
	uint32_t		hme_mif_mask;
	int			hme_phyad;
	int			hme_openloop_autoneg;
	int			hme_autoneg;
	int			hme_adapter_type;
	int			hme_cheerio_mode;
	caddr_t			hme_g_nd;	/* head of the */
						/* named dispatch table */
	hmeparam_t		hme_param_arr[HME_PARAM_CNT];
	int			hme_transceiver;  /* current PHY in use */
	int			hme_link_pulse_disabled;
	uint16_t		hme_bmsr;	/* PHY status register */
	uint16_t		hme_idr1;	/* PHY IDR1 register */
	uint16_t		hme_idr2;	/* PHY IDR2 register */
	uint16_t		hme_anar;	/* PHY ANAR register */
	uint16_t		hme_anlpar;	/* PHY ANLPAR register */
	uint16_t		hme_aner;	/* PHY ANER register */
	int			hme_mode;	/* auto/forced mode */
	int			hme_linkup;	/* link status */
	int			hme_forcespeed; /* speed in forced mode */
	int			hme_tryspeed;	/* speed in auto mode */
	int			hme_speed;	/* speed to report */
	int			hme_fdx;	/* full-duplex mode */
	int			hme_pace_count;	/* pacing pkt count */
	int			hme_macfdx;
	int			hme_linkcheck;
	int			hme_linkup_msg;
	int			hme_force_linkdown;
	int			hme_nlasttries;
	int			hme_ntries;
	int			hme_delay;
	int			hme_linkup_10;
	int			hme_linkup_cnt;
	timeout_id_t		hme_timerid;
	timeout_id_t		hme_mif_poll_timerid;
	int			hme_polling_on;
	int			hme_mifpoll_data;
	int			hme_mifpoll_flag;
	int			hme_pollid;
	int			hme_intrpoll;
	int			hme_claim;
	ulong_t			hme_pagesize;

	/*
	 * This is part of the hardening of the hme driver
	 * (following 8 fields)
	 */
	uint16_t		hme_disabled;
	uchar_t			hme_fault_reported; /* link down */
	uchar_t			hme_error_reported; /* non-fatal errrors */
	int			hme_lnk_id;	/* tmout id */
	uint_t			hme_lnk_down;	/* is the link down? Also cnt */
	int			hme_last_down;	/* timestamp last down evnt */
	uint16_t		hme_freq_down;	/* number of 'frequent' downs */
	uint16_t		hme_max_down;	/* max number downs before
						 * reporting error (u4ft...) */

	struct	ether_addr	hme_factaddr;	/* factory mac address */
	struct	ether_addr	hme_ouraddr;	/* individual address */
#ifdef QFETRUNK
	struct	ether_addr	hme_savaddr;	/* used in trunking */
#endif
	uint_t			hme_addrflags;	/* address flags */
	uint_t			hme_flags;	/* misc. flags */
	uint_t			hme_wantw;	/* xmit: out of resources */

	struct	hme_global	*hme_globregp;	/* HME global regs */
	struct	hme_etx		*hme_etxregp;	/* HME ETX regs */
	struct	hme_erx		*hme_erxregp;	/* HME ERX regs */
	struct	hme_bmac	*hme_bmacregp;	/* BigMAC registers */
	struct	hme_mif		*hme_mifregp;	/* HME transceiver */
	unsigned char		*hme_romp;	/* fcode rom pointer */

	kmutex_t	hme_xmitlock;		/* protect xmit-side fields */
	kmutex_t	hme_recvlock;		/* protect recv-side fields */
	kmutex_t	hme_xcvrlock;		/* protect xcvr access fields */
	kmutex_t	hme_linklock;		/* protect link-side fields */

	ddi_iblock_cookie_t	hme_cookie;	/* interrupt cookie */

	ddi_softintr_t		hme_softintr_id;/* Soft interrupt cookie */

	struct	hme_rmd	*hme_rmdp;	/* receive descriptor ring start */
	struct	hme_rmd	*hme_rmdlimp;	/* receive descriptor ring end */
	struct	hme_tmd	*hme_tmdp;	/* transmit descriptor ring start */
	struct	hme_tmd	*hme_tmdlimp;	/* transmit descriptor ring end */
	struct	hme_rmd	*hme_rnextp;	/* next chip rmd */
	struct	hme_rmd	*hme_rlastp;	/* last free rmd */
	struct	hme_tmd	*hme_tnextp;	/* next free tmd */
	struct	hme_tmd	*hme_tcurp;	/* next tmd to reclaim (used) */

        p_hme_tmd_t hme_tx_iobase;
        p_hme_rmd_t hme_rx_iobase;

	mblk_t *hme_tmblkp[HME_TMDMAX];	/* hmebuf associated with TMD */
	mblk_t *hme_rmblkp[HME_RMDMAX];	/* hmebuf associated with RMD */

	data_descr_t hme_stmblkp[HME_TMDMAX]; /* hmebuf associated with TMD */
	data_descr_t hme_srmblkp[HME_RMDMAX]; /* hmebuf associated with RMD */
	ddi_dma_handle_t hme_desc_handle;
	ddi_umem_cookie_t hme_desc_cookie;

	queue_t	*hme_ip4q;		/* ip4 read queue */
        queue_t *hme_ip6q;              /* ip6 read queue */

	ddi_device_acc_attr_t	hme_dev_attr;
	ddi_acc_handle_t	hme_globregh;   /* HME global regs */
	ddi_acc_handle_t	hme_etxregh;    /* HME ETX regs */
	ddi_acc_handle_t	hme_erxregh;    /* HME ERX regs */
	ddi_acc_handle_t	hme_bmacregh;   /* BigMAC registers */
	ddi_acc_handle_t	hme_mifregh;    /* HME transceiver */
	ddi_dma_cookie_t	hme_md_c;	/* trmd dma cookie */
	ddi_acc_handle_t	hme_mdm_h;	/* trmd memory handle */
	ddi_dma_handle_t	hme_md_h;	/* trmdp dma handle */
	ddi_acc_handle_t	hme_romh;	/* rom handle */

	/*
	 * DDI dma handle, kernel virtual base,
	 * and io virtual base of IOPB area.
	 */
	ulong_t			hme_iopbkbase;
	ulong_t			hme_iopbiobase;

	/*
	 * these are handles for the dvma resources reserved
	 * by dvma_reserve
	 */
	ddi_dma_handle_t	hme_dvmarh;	/* dvma recv handle */
	ddi_dma_handle_t	hme_dvmaxh;	/* dvma xmit handle */

	/*
	 * these are used if dvma reserve fails, and we have to fall
	 * back on the older ddi_dma_addr_setup routines
	 */
	ddi_dma_handle_t	*hme_dmarh;
	ddi_dma_handle_t	*hme_dmaxh;

	/*
	 * Depending on how the memory is setup these pointers will be
	 * setup to different pointers.
	 */
	void (*qferead_func) (struct hme *, struct hme_rmd *, uint32_t);
	int (*qfestart_func) (struct hme *, mblk_t *);
	void (*qfereclaim_func) (struct hme *);
	void (*qfeintr_func) (struct hme *);

	kstat_t	*hme_ksp;	/* kstat pointer */
	kstat_t	*hme_intrstats;	/* kstat interrupt counter */
	/*
	 *  These three  are used for qfe devices. All the four hme devices
	 *   on single QFE board point to single qfe structure, hme_qfe.
	 */
	struct qfe *hme_qfe;
	uint32_t hme_qfedev_id;	/* device id 0, 1, 2 or 3 on the qfe */
	uint32_t intr_mask;	/* Interrupt mask. */
	uint32_t mif_status;
	uint32_t softintr_status;
	boolean_t softintr_pending;
	uint32_t hme_iipackets;	/* Used to store the Count of packets */
				/* recieved at the start of 'hme_check_link' */
				/* watch dog interval. */
	struct hme_stats hme_stats;
	/*
	 * check if transmitter is hung
	 */
	uint32_t hme_starts;
	uint32_t hme_txhung;
	time_t hme_msg_time;
	struct hmesave hmesave;
} hme_t;

#ifdef POLL_QFE
struct qfe_nex {
	struct qfe_nex *next;
	kmutex_t qfenp_lock;
	dev_info_t *pdip;
	dev_info_t *intr_dip;
	ddi_iblock_cookie_t intr_cookie;
	ddi_softintr_t softintr_id;
	boolean_t altering_qfei_list;
	struct qfe_inst *qfeip;
};

struct qfe_inst {
	struct qfe_inst *next;
	uint32_t slot_number;
	boolean_t serviced;
	struct hme *hmep;
};

typedef struct qfe_nex qfen_t;
typedef struct qfe_inst qfei_t;
#endif

/* flags */
#define	HMERUNNING	0x01	/* chip is initialized */
#define	HMEPROMISC	0x02	/* promiscuous mode enabled */
#define	HMESUN4C	0x04	/* this system is a sun4c */
#define	HMESUSPENDED	0x08	/* suspended interface */
#define	HMEINITIALIZED	0x10	/* interface initialized */
#define	HMENOTIMEOUTS	0x20	/* disallow timeout rescheduling */
#define	HMEDLPILINKUP	0x40	/* Flag which shows the layers */
#define	HMETHREADRUN	0x80	/* Flag which shows the layers */

/* Mac address flags */

#define	HME_FACTADDR_PRESENT	0x01	/* factory MAC id present */
#define	HME_FACTADDR_USE	0x02	/* use factory MAC id */

struct	hmekstat {
	struct kstat_named	hk_ipackets;	/* packets received */
	struct kstat_named	hk_ierrors;	/* input errors */
	struct kstat_named	hk_opackets;	/* packets transmitted */
	struct kstat_named	hk_oerrors;	/* output errors */
	struct kstat_named	hk_coll;	/* collisions encountered */
	struct kstat_named	hk_defer;	/* slots deferred */
	struct kstat_named	hk_fram;	/* framing errors */
	struct kstat_named	hk_crc;		/* crc errors */
	struct kstat_named	hk_sqerr;	/* SQE test  errors */
	struct kstat_named	hk_cvc;		/* code violation  errors */
	struct kstat_named	hk_lenerr;	/* rx len errors */
	struct kstat_named	hk_ifspeed;	/* interface speed */
	struct kstat_named	hk_buff;	/* buff errors */
	struct kstat_named	hk_oflo;	/* overflow errors */
	struct kstat_named	hk_uflo;	/* underflow errors */
	struct kstat_named	hk_missed;	/* missed/dropped packets */
	struct kstat_named	hk_tlcol;	/* late collisions */
	struct kstat_named	hk_trtry;	/* retry errors */
	struct kstat_named	hk_fstcol;	/* first collisions */
	struct kstat_named	hk_tnocar;	/* no carrier */
	struct kstat_named	hk_inits;	/* initialization */
	struct kstat_named	hk_nocanput;	/* nocanput errors */
	struct kstat_named	hk_allocbfail;	/* allocb failures */
	struct kstat_named	hk_runt;	/* runt errors */
	struct kstat_named	hk_jab;		/* jabber errors */
	struct kstat_named	hk_babl;	/* runt errors */
	struct kstat_named	hk_tmder;	/* tmd errors */
	struct kstat_named	hk_txlaterr;	/* tx late errors */
	struct kstat_named	hk_rxlaterr;	/* rx late errors */
	struct kstat_named	hk_slvparerr;	/* slave parity errors */
	struct kstat_named	hk_txparerr;	/* tx parity errors */
	struct kstat_named	hk_rxparerr;	/* rx parity errors */
	struct kstat_named	hk_slverrack;	/* slave error acks */
	struct kstat_named	hk_txerrack;	/* tx error acks */
	struct kstat_named	hk_rxerrack;	/* rx error acks */
	struct kstat_named	hk_txtagerr;	/* tx tag error */
	struct kstat_named	hk_rxtagerr;	/* rx tag error */
	struct kstat_named	hk_eoperr;	/* eop error */
	struct kstat_named	hk_notmds;	/* tmd errors */
	struct kstat_named	hk_notbufs;	/* tx buf errors */
	struct kstat_named	hk_norbufs;	/* rx buf errors */
	struct kstat_named	hk_clsn;	/* clsn errors */

	/*
	 * required by kstat for MIB II objects(RFC 1213)
	 */
	struct  kstat_named	hk_rcvbytes; 	/* # octets received */
						/* MIB - ifInOctets */
	struct  kstat_named	hk_xmtbytes; 	/* # octets transmitted */
						/* MIB - ifOutOctets */
	struct  kstat_named	hk_multircv; 	/* # multicast packets */
						/* delivered to upper layer */
						/* MIB - ifInNUcastPkts */
	struct  kstat_named	hk_multixmt; 	/* # multicast packets */
						/* requested to be sent */
						/* MIB - ifOutNUcastPkts */
	struct  kstat_named	hk_brdcstrcv;	/* # broadcast packets */
						/* delivered to upper layer */
						/* MIB - ifInNUcastPkts */
	struct  kstat_named	hk_brdcstxmt;	/* # broadcast packets */
						/* requested to be sent */
						/* MIB - ifOutNUcastPkts */
	struct  kstat_named	hk_norcvbuf; 	/* # rcv packets discarded */
						/* MIB - ifInDiscards */
	struct  kstat_named	hk_noxmtbuf; 	/* # xmt packets discarded */
						/* MIB - ifOutDiscards */

	struct	kstat_named	hk_phy_inits;	/* phy failures */
	struct	kstat_named	hk_tx_inits;	/* Transmit side inits*/
	struct	kstat_named	hk_rx_inits;	/* Receive side inits*/

	/*
	 * PSARC 1997/198
	 */
	struct kstat_named	hk_ipackets64;	/* packets received */
	struct kstat_named	hk_opackets64;	/* packets transmitted */
	struct kstat_named	hk_rbytes64;	/* bytes received */
	struct kstat_named	hk_obytes64;	/* bytes transmitted */

        /*
         * PSARC 1997/247 : RFC 1643
         *                                              SNMP Variables
         */
	struct kstat_named	hk_align_errors;
					/* dot3StatsAlignmentErrors */
	struct kstat_named	hk_fcs_errors;
					/* dot3StatsFCSErrors */
	struct kstat_named	hk_multi_collisions;
					/* dot3StatsMultipleCollisionFrames */
	struct kstat_named	hk_sqe_errors;	
					/* dot3StatsSQETestErrors */
	struct kstat_named	hk_defer_xmts;
					/* dot3StatsDeferredTransmissions */
	struct kstat_named	hk_ex_collisions;
					/* dot3StatsExcessiveCollisions */
	struct kstat_named	hk_macxmt_errors;
					/* dot3StatsInternalMacTransmitErrors */
	struct kstat_named	hk_carrier_errors;
					/* dot3StatsCarrierSenseErrors  */
	struct kstat_named	hk_toolong_errors;
					/* dot3StatsFrameTooLongs */
	struct kstat_named	hk_macrcv_errors;
					/* dot3StatsInternalMacReceiveErrors  */
        struct kstat_named      hk_tcpcksum_errors; /* tcp cksum error */
        struct kstat_named      hk_hwcksum_errors;/* harware cksum error */
	struct kstat_named	hk_link_up; /* link status */
	struct kstat_named	hk_link_duplex; /* link duplex */
	struct kstat_named	hk_promisc_mode; /* promisc mode */
};

/*
 * The following structure is to implement the DL_GET_STATISTICS_REQ
 */
#define	MAX_NAMELEN	KSTAT_STRLEN

#define	HMEDRAINTIME	(400000)	/* # microseconds xmit drain */

#define	ROUNDUP(a, n)	(((a) + ((n) - 1)) & ~((n) - 1))
#define	ROUNDUP2(a, n)	(uchar_t *)((((uintptr_t)(a)) + ((n) - 1)) & ~((n) - 1))

/*
 * Xmit/receive buffer structure.
 * This structure is organized to meet the following requirements:
 * - bb_buf starts on an HMEBURSTSIZE boundary.
 * - hmebuf is an even multiple of HMEBURSTSIZE
 * - bb_buf[] is large enough to contain max frame (1518) plus
 *   (3 x HMEBURSTSIZE) rounded up to the next HMEBURSTSIZE
 * XXX What about another 128 bytes (HMEC requirement).
 * Fast aligned copy requires both the source and destination
 * addresses have the same offset from some N-byte boundary.
 */
#define	HMEBURSTSIZE	(64)
#define	HMEBURSTMASK	(HMEBURSTSIZE - 1)
#define	HMEALIGNBUFSIZE (2048)
#ifndef HME_RXBUF
#define		HMEBUFSIZE	(1728)
#else
#define		HMEBUFSIZE	(1728 - sizeof (struct hme *) - sizeof (frtn_t))
#define		HMEBUFPAD	(HMEBURSTSIZE - sizeof (struct hme *) \
				- sizeof (frtn_t))
struct hmebuf {
	uchar_t hb_buf[HMEBUFSIZE];	/* raw buffer */
	struct hme *hb_hmep;		/* link to device structure */
	frtn_t hb_frtn;			/* for esballoc() */
	uchar_t pad[HMEBUFPAD];
};
#endif

/* Offset for the first byte in the receive buffer */
#define	HME_FSTBYTE_OFFSET	2

typedef struct ether_header *eehp;

#define	get_ether_type(ptr) (\
	(((uchar_t *)&((eehp)ptr)->ether_type)[0] << 8) | \
	(((uchar_t *)&((eehp)ptr)->ether_type)[1]))
#define	put_ether_type(ptr, value) {\
	((uchar_t *)(&((eehp)ptr)->ether_type))[0] = \
		((uint_t)value & 0xff00) >> 8; \
	((uchar_t *)(&((eehp)ptr)->ether_type))[1] = (value & 0xff); }

/*
 * Private DLPI full dlsap address format.
 */
struct	hmedladdr {
	struct	ether_addr	dl_phys;
	u_short	dl_sap;
};

#pragma weak strtol
extern long int strtol(const char *, char **, int);
#define strtol(a, b, c) \
	(strtol != NULL ? strtol(a, b, c) : qfe_strtol(a, b, c))

#endif	/* _KERNEL */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_HME_H */
