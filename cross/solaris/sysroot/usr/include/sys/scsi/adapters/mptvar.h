/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SYS_SCSI_ADAPTERS_MPTVAR_H
#define	_SYS_SCSI_ADAPTERS_MPTVAR_H

#pragma ident	"@(#)mptvar.h	1.21	06/06/30 SMI"

#include <sys/isa_defs.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Compile options
 */
#ifdef DEBUG
#define	MPT_DEBUG		/* turn on debugging code */
#endif	/* DEBUG */

#define	MPT_INITIAL_SOFT_SPACE	4	/* Used	for the	softstate_init func */

#define	MAX_MPI_PORTS		8
#define	MPT_MAX_REPLY_FRAMES	128

/*
 * Reply frame size that we use. That's the maximum of any of the normal
 * MPT replies one can expect.
 */
#define	MPT_REPLY_FRAME_SIZE	0x50

/*
 * MPT HW defines
 */
#define	MAX_REPLY_ELEMENTS	128
#define	MPT_MAX_TARGETS		256
#define	MPT_MAX_DISKS_IN_RAID	8
#define	MPT_MAX_RAIDVOLS	2
#define	NLUNS_MPT		32
#define	N_MPT_UNITS		(MPT_MAX_TARGETS * NLUNS_MPT)
#define	ALL_TARGETS		0xffff

#define	SCSI_OPTIONS_FAST_MASK	0x7f00

/*
 * DMA routine flags
 */
#define	MPT_DMA_HANDLE_ALLOCD	0x2
#define	MPT_DMA_MEMORY_ALLOCD	0x4
#define	MPT_DMA_HANDLE_BOUND	0x8

/*
 * If the HBA supports DMA or bus-mastering, you may have your own
 * scatter-gather list for physically non-contiguous memory in one
 * I/O operation; if so, there's probably a size for that list.
 * It must be placed in the ddi_dma_lim_t structure, so that the system
 * DMA-support routines can use it to break up the I/O request, so we
 * define it here.
 */
#if defined(__sparc)
#define	MPT_MAX_DMA_SEGS	1
#define	MPT_MAX_CMD_SEGS(mpt)	1
#define	MPT_FRAME_SIZE(mpt)	1
#else
#define	MPT_MAX_DMA_SEGS	256
#define	MPT_MAX_CMD_SEGS(mpt)	(mpt->m_io_dma_attr.dma_attr_sgllen)
#define	MPT_FRAME_SIZE(mpt)	(mpt->m_max_chain_depth)
#endif
#define	MPT_MAX_FRAME_SGES(mpt) \
	((((mpt->m_req_frame_size << 2) - \
	(sizeof (struct msg_scsi_io_request))) / 8) + 1)

/*
 * Caculating how many 64-bit DMA simple elements can be stored in the first
 * frame. Note that m_req_frame_size is in double-words (4 bytes) and
 * msg_scsi_io_request contains 2 double-words (8 bytes) for element storage.
 * And 64-bit dma element is 3 double-words (12 bytes) in size.
 */
#define	MPT_MAX_FRAME_SGES64(mpt) \
	(((mpt->m_req_frame_size << 2) - \
	(sizeof (struct msg_scsi_io_request)) + sizeof (sge_io_union_t)) / 12)

/*
 * Scatter-gather list structure defined by HBA hardware
 */
typedef	struct NcrTableIndirect {	/* Table Indirect entries */
	uint32_t count;		/* 24 bit count */
	union {
		uint32_t address32;	/* 32 bit address */
		struct {
			uint32_t Low;
			uint32_t High;
		} address64;		/* 64 bit address */
	} addr;
} mptti_t;

/*
 * preferred pkt_private length in 64-bit quantities
 */
#ifdef	_LP64
#define	PKT_PRIV_SIZE	2
#define	PKT_PRIV_LEN	16	/* in bytes */
#else /* _ILP32 */
#define	PKT_PRIV_SIZE	1
#define	PKT_PRIV_LEN	8	/* in bytes */
#endif

#define	PKT2CMD(pkt)	((struct mpt_cmd *)((pkt)->pkt_ha_private))
#define	CMD2PKT(cmdp)	((struct scsi_pkt *)((cmdp)->cmd_pkt))
#define	EXTCMDS_STATUS_SIZE (sizeof (struct scsi_arq_status))


typedef struct	mpt_cmd {
	uint_t			cmd_flags;	/* flags from scsi_init_pkt */
	ddi_dma_handle_t	cmd_dmahandle;	/* dma handle */
	ddi_dma_cookie_t	cmd_cookie;
	uint_t			cmd_cookiec;
	uint_t			cmd_winindex;
	uint_t			cmd_nwin;
	uint_t			cmd_cur_cookie;
	off_t			cmd_dma_offset;
	size_t			cmd_dma_len;
	uint32_t		cmd_totaldmacount;

	ddi_dma_handle_t	cmd_arqhandle;	/* dma arq handle */
	ddi_dma_cookie_t	cmd_arqcookie;
	struct buf		*cmd_arq_buf;

	int			cmd_pkt_flags;

	struct scsi_pkt		*cmd_pkt;
	struct scsi_arq_status	cmd_scb;
	uchar_t			cmd_cdblen;	/* length of cdb */
	uchar_t			cmd_rqslen;	/* len of requested rqsense */
	uchar_t			cmd_scblen;
	uchar_t			cmd_privlen;
	uint32_t		cmd_dmacount;
	uint32_t		cmd_dma_addr;
	uchar_t			cmd_age;
	ushort_t		cmd_qfull_retries;
	uchar_t			cmd_queued;	/* true if queued */
	struct mpt_cmd		*cmd_linkp;
	mptti_t			*cmd_sg; /* Scatter/Gather structure */
	uchar_t			cmd_cdb[CDB_SIZE];
	uint64_t		cmd_pkt_private[PKT_PRIV_LEN];
	uint32_t		cmd_slot;
	uint32_t		ioc_cmd_slot;

	/*
	 * dma memory handles for extra memory that might need to
	 * allocated for IO's having large numbers of cookies associated
	 * with them
	 */
	ddi_dma_handle_t	cmd_extra_dma_hdl;
	ddi_acc_handle_t	cmd_extra_acc_hdl;
	caddr_t			cmd_extra_frame;
	uint32_t		cmd_extra_fma;
} mpt_cmd_t;

/*
 * These are the defined cmd_flags for this structure.
 */
#define	CFLAG_CMDDISC		0x000001 /* cmd currently disconnected */
#define	CFLAG_WATCH		0x000002 /* watchdog time for this command */
#define	CFLAG_FINISHED		0x000004 /* command completed */
#define	CFLAG_CHKSEG		0x000008 /* check cmd_data within seg */
#define	CFLAG_COMPLETED		0x000010 /* completion routine called */
#define	CFLAG_PREPARED		0x000020 /* pkt has been init'ed */
#define	CFLAG_IN_TRANSPORT	0x000040 /* in use by host adapter driver */
#define	CFLAG_RESTORE_PTRS	0x000080 /* implicit restore ptr on reconnect */
#define	CFLAG_ARQ_IN_PROGRESS	0x000100 /* auto request sense in progress */
#define	CFLAG_TRANFLAG		0x0001ff /* covers transport part of flags */
#define	CFLAG_CMDPROXY		0x000200 /* cmd is a 'proxy' command */
#define	CFLAG_CMDARQ		0x000400 /* cmd is a 'rqsense' command */
#define	CFLAG_DMAVALID		0x000800 /* dma mapping valid */
#define	CFLAG_DMASEND		0x001000 /* data	is going 'out' */
#define	CFLAG_CMDIOPB		0x002000 /* this	is an 'iopb' packet */
#define	CFLAG_CDBEXTERN		0x004000 /* cdb kmem_alloc'd */
#define	CFLAG_SCBEXTERN		0x008000 /* scb kmem_alloc'd */
#define	CFLAG_FREE		0x010000 /* packet is on free list */
#define	CFLAG_PRIVEXTERN	0x020000 /* target private kmem_alloc'd */
#define	CFLAG_DMA_PARTIAL	0x040000 /* partial xfer OK */
#define	CFLAG_QFULL_STATUS	0x080000 /* pkt got qfull status */
#define	CFLAG_CMD_REMOVED	0x100000 /* cmd has been remove */
#define	CFLAG_PMM_RECEIVED	0x200000 /* use cmd_pmm*  for saving pointers */
#define	CFLAG_RETRY		0x400000 /* cmd has been retried */
#define	CFLAG_CMDIOC		0x800000 /* cmd is just for for ioc, no io */

/*
 * Structure to hold active outstanding cmds.  Also, keep
 * timeout on a per target basis.
 */
typedef struct mpt_slots {
	struct mpt_targets {
		ushort_t		m_dups;
		int			m_timeout;
		int			m_timebase;
		int			m_t_throttle;
		int			m_t_ncmds;
		int			m_reset_delay;
		uchar_t			m_qfull_retries;
		ushort_t		m_qfull_retry_interval;
		dev_info_t		*m_tgt_dip;
	} m_target[MPT_MAX_TARGETS];
	struct mpt_raidvols {
		uint32_t	m_raidsize;
		uint8_t		m_israid;
		uint8_t		m_raidtarg;
		uint8_t		m_state;
		uint8_t		m_flags;
		uint8_t		m_diskid[MPT_MAX_DISKS_IN_RAID];
		uint8_t		m_disknum[MPT_MAX_DISKS_IN_RAID];
		ushort_t	m_diskstatus[MPT_MAX_DISKS_IN_RAID];
		uint8_t		m_raidbuilding;
		uint8_t		m_raidlevel;
		uint8_t		m_ndisks;
	} m_raidvol[MPT_MAX_RAIDVOLS];
	uint16_t		m_tags;
	uint32_t		m_buffer;
	uint16_t		m_size;
	uint16_t		m_n_slots;
	mpt_cmd_t		*m_slot[1];
} mpt_slots_t;

/*
 * easily pass around a disk list
 */
typedef struct mpt_disklist {
	int	m_ndisks;
	int	m_diskid[MPT_MAX_DISKS_IN_RAID];
} mpt_disklist_t;

/*
 * Structure to hold command and packets for event ack
 * and task management commands.
 */
typedef struct  m_event_struct {
	struct mpt_cmd		m_event_cmd;
	struct scsi_pkt		m_event_pkt;
	uint_t			in_use;
} m_event_struct_t;

#define	MAX_IOC_COMMANDS	8

/*
 * A pool of MAX_IOC_COMMANDS is maintained for event ack commands.
 * A new event ack command requests mpt_cmd and scsi_pkt structures
 * from this pool, and returns it back when done.
 */
typedef struct m_event_cmd_pool {
	uint_t			cmd_index;
	m_event_struct_t	m_event_cmd[MAX_IOC_COMMANDS];
} m_event_cmd_pool_t;

typedef struct m_replyh_arg {
	void *mpt;
	uint32_t rfm;
} m_replyh_arg_t;

/*
 * add one to hold any polled cmd.
 */
#define	MPT_SLOTS_SIZE(mpt) \
	(sizeof (struct mpt_slots) + (sizeof (struct mpt_cmd *) * \
		(mpt->m_max_request_depth + 1)))

#define	MPT_PROXY_SLOT(mpt)	(mpt->m_max_request_depth)

typedef struct mpt {
	int		m_instance;

	struct mpt *m_next;

	scsi_hba_tran_t		*m_tran;
	kmutex_t		m_mutex;
	kcondvar_t		m_cv;
	dev_info_t		*m_dip;

	/*
	 * soft state flags
	 */
	uint_t		m_softstate;

	struct mpt_slots *m_active;	/* outstanding cmds */

	mpt_cmd_t	*m_waitq;	/* cmd queue for active request */
	mpt_cmd_t	**m_waitqtail;	/* wait queue tail ptr */
	mpt_cmd_t	*m_doneq;	/* queue of completed commands */
	mpt_cmd_t	**m_donetail;	/* queue tail ptr */
	int		m_ncmds;	/* number of outstanding commands */

	ddi_acc_handle_t m_datap;	/* operating regs data access handle */

	struct mptreg	*m_reg;

	ushort_t	m_devid;	/* device id of chip. */
	uchar_t		m_revid;	/* revision of chip. */
	uint16_t	m_ssid;		/* sub system id of chip */

	uchar_t		m_sync_offset;	/* default offset for this chip. */

	timeout_id_t	m_quiesce_timeid;

	ddi_dma_handle_t m_dma_hdl;
	ddi_acc_handle_t m_acc_hdl;
	uint32_t	m_fma;
	caddr_t		m_frame;

	/*
	 * scsi_options for bus and per target
	 */
	int		m_target_scsi_options_defined;
	int		m_scsi_options;
	int		m_target_scsi_options[NTARGETS_WIDE];

	/*
	 * sync/wide backoff bit mask
	 */
	ushort_t	m_backoff;

	/*
	 * This u_short is a bit map for targets who need to have
	 * their properties update deferred.
	 */
	ushort_t	m_props_update;

	/*
	 * This u_short is a bit map for targets who don't appear
	 * to be able to support tagged commands.
	 */
	ushort_t	m_notag;

	/*
	 * This u_short is a bit map for targets who don't support
	 * wide negotiations
	 */
	ushort_t	m_nowide;

	/*
	 * tag age limit per bus
	 */
	int		m_scsi_tag_age_limit;

	/*
	 * list of reset notification requests
	 */
	struct scsi_reset_notify_entry	*m_reset_notify_listf;

	/*
	 * qfull handling
	 */
	timeout_id_t	m_restart_cmd_timeid;

	/*
	 * scsi	reset delay per	bus
	 */
	uint_t		m_scsi_reset_delay;

	uchar_t		m_mptid;	/* this hba's target number and ... */

	uchar_t		m_polled_intr;	/* intr was polled. */
	uchar_t		m_suspended;	/* true	if driver is suspended */

	struct kmem_cache *m_kmem_cache;

	/*
	 * hba options.
	 */
	uint_t		m_options;

	int		m_in_callback;

	uchar_t		m_max_lun[NTARGETS_WIDE];

	int 		m_ntargets;	/* maximum targets supported */

	int		m_power_level;	/* current power level */

	int		m_busy;		/* power management busy state */

	off_t		m_pmcsr_offset; /* PMCSR offset */

	ddi_acc_handle_t m_config_handle;

	ddi_dma_attr_t m_io_dma_attr;

	/*
	 * reply queue variables
	 */
	ddi_acc_handle_t m_reply_acc_h;
	ddi_dma_handle_t m_reply_dma_h;
	caddr_t		m_reply_fifo;
	uint32_t	m_reply_addr;

	m_replyh_arg_t *m_replyh_args;

	uint8_t		m_num_ports;

	uint16_t	m_max_reply_depth;

	uint16_t	m_max_request_depth;

	uint16_t	m_req_frame_size;

	uint8_t		m_max_chain_depth;

	uint_t		m_port_type[MAX_MPI_PORTS];

	uint_t		m_protocol_flags[MAX_MPI_PORTS];

	uint32_t	m_scsi_params;

	ushort_t	m_bus_type;		/* is bus SE or LVD */

	ushort_t	m_neg_occured;

	/*
	 * indicates if the firmware was upload by the driver
	 * at boot time
	 */
	ushort_t	m_fwupload;

	uint16_t	m_productid;

	uint8_t		m_ioc_num;

	/*
	 * per instance cmd data structures for event ack cmds
	 */
	m_event_cmd_pool_t	m_event_ack;

	/*
	 * per instance cmd data structures for task management cmds
	 */
	m_event_struct_t	m_event_task_mgmt;

	/*
	 * per instance data structures for dma memory resources for
	 * MPI handshake protocol. only one handshake cmd can run at a time.
	 */
	ddi_dma_handle_t	m_hshk_dma_hdl;

	ddi_acc_handle_t	m_hshk_acc_hdl;

	caddr_t			m_hshk_memp;

	size_t			m_hshk_dma_size;

	/* Firmware version on the card at boot time */
	uint32_t		m_fwversion;

	/* MSI specific fields */
	ddi_intr_handle_t	*m_htable;	/* For array of interrupts */
	int			m_intr_type;	/* What type of interrupt */
	int			m_intr_cnt;	/* # of intrs count returned */
	size_t			m_intr_size;	/* Size of intr array to */
						/* allocate */
	uint_t			m_intr_pri;	/* Interrupt priority   */
	int			m_intr_cap;	/* Interrupt capabilities */
	ddi_taskq_t		*m_event_taskq;
} mpt_t;

_NOTE(MUTEX_PROTECTS_DATA(mpt::m_mutex, mpt))
_NOTE(SCHEME_PROTECTS_DATA("safe sharing", mpt::m_next))
_NOTE(SCHEME_PROTECTS_DATA("stable data", mpt::m_target_scsi_options))
_NOTE(SCHEME_PROTECTS_DATA("stable data", mpt::m_dip mpt::m_tran))
_NOTE(SCHEME_PROTECTS_DATA("stable data", mpt::m_kmem_cache))

/*
 * These should eventually migrate into the mpt header files
 * that may become the /kernel/misc/mpt module...
 */
#define	mpt_init_std_hdr(hdl, mp, Target, Lun, Bus, ChainOffset, Function) \
	mpt_put_msg_TargetID(hdl, mp, Target); \
	mpt_put_msg_Bus(hdl, mp, Bus); \
	mpt_put_msg_ChainOffset(hdl, mp, ChainOffset); \
	mpt_put_msg_Function(hdl, mp, Function); \
	mpt_put_msg_Lun(hdl, mp, Lun)

#define	mpt_put_msg_TargetID(hdl, mp, val) \
	ddi_put8(hdl, &(mp)->TargetID, (val))
#define	mpt_put_msg_Bus(hdl, mp, val) \
	ddi_put8(hdl, &(mp)->Bus, (val))
#define	mpt_put_msg_ChainOffset(hdl, mp, val) \
	ddi_put8(hdl, &(mp)->ChainOffset, (val))
#define	mpt_put_msg_Function(hdl, mp, val) \
	ddi_put8(hdl, &(mp)->Function, (val))
#define	mpt_put_msg_Lun(hdl, mp, val) \
	ddi_put8(hdl, &(mp)->LUN[1], (val))

#define	mpt_put_msg_MessageContext(hdl, mp, val) \
	ddi_put32(hdl, &(mp)->MsgContext, (val))
#define	mpt_get_msg_MessageContext(hdl, mp) \
	ddi_get32(hdl, &mp->MsgContext)

#define	mpt_get_msg_Function(hdl, mp) \
	ddi_get8(hdl, &(mp)->Function)

#define	mpt_get_msg_MsgFlags(hdl, mp) \
	ddi_get8(hdl, &(mp)->MsgFlags)

#define	MPT_ENABLE_DRWE(hdl) \
	ddi_put32(hdl->m_datap, &hdl->m_reg->m_write_seq, \
		MPI_WRSEQ_KEY_VALUE_MASK); \
	ddi_put32(hdl->m_datap, &hdl->m_reg->m_write_seq, \
		MPI_WRSEQ_1ST_KEY_VALUE); \
	ddi_put32(hdl->m_datap, &hdl->m_reg->m_write_seq, \
		MPI_WRSEQ_2ND_KEY_VALUE); \
	ddi_put32(hdl->m_datap, &hdl->m_reg->m_write_seq, \
		MPI_WRSEQ_3RD_KEY_VALUE); \
	ddi_put32(hdl->m_datap, &hdl->m_reg->m_write_seq, \
		MPI_WRSEQ_4TH_KEY_VALUE); \
	ddi_put32(hdl->m_datap, &hdl->m_reg->m_write_seq, \
		MPI_WRSEQ_5TH_KEY_VALUE)

/*
 * m_options flags
 */
#define	MPT_OPT_PM		0x01	/* Power Management */

/*
 * m_softstate flags
 */
#define	MPT_SS_DRAINING 	0x02
#define	MPT_SS_QUIESCED 	0x04

/*
 * regspec defines.
 */
#define	CONFIG_SPACE	0	/* regset[0] - configuration space */
#define	IO_SPACE	1	/* regset[1] - used for i/o mapped device */
#define	MEM_SPACE	2	/* regset[2] - used for memory mapped device */
#define	BASE_REG2	3	/* regset[3] - used for 875 scripts ram */

/*
 * Handy constants
 */
#define	FALSE		0
#define	TRUE		1
#define	UNDEFINED	-1

/*
 * power management.
 */
#define	MPT_POWER_ON(mpt) { \
	pci_config_put16(mpt->m_config_handle, mpt->m_pmcsr_offset, \
	    PCI_PMCSR_D0); \
	delay(drv_usectohz(10000)); \
	mpt->m_power_level = PM_LEVEL_D0; \
	(void) pci_restore_config_regs(mpt->m_dip); \
	mpt_setup_cmd_reg(mpt); \
	MPT_ENABLE_INTR(mpt); \
}

#define	MPT_POWER_OFF(mpt) { \
	(void) pci_save_config_regs(mpt->m_dip); \
	pci_config_put16(mpt->m_config_handle, mpt->m_pmcsr_offset, \
	    PCI_PMCSR_D3HOT); \
	mpt->m_power_level = PM_LEVEL_D3; \
}

#define	MPT_IS_SCSI(mpt) \
	(mpt->m_port_type[0] == MPI_PORTFACTS_PORTTYPE_SCSI)

#define	MPT_IS_SAS(mpt) \
	(mpt->m_port_type[0] == MPI_PORTFACTS_PORTTYPE_SAS)

#define	MPT_IS_LVD(mpt) \
	(mpt->m_bus_type == MPI_SCSIPORTPAGE0_PHY_SIGNAL_LVD)

#define	MPT_RAID_EXISTS(mpt, slot) \
	(mpt->m_active->m_raidvol[slot].m_israid == 1)

#define	TGT_IS_RAID(mpt, slot, tgt) \
	(mpt->m_active->m_raidvol[slot].m_raidtarg == tgt)

/*
 * Default is to have 10 retries on receiving QFULL status and
 * each retry to be after 100 ms.
 */
#define	QFULL_RETRIES		10
#define	QFULL_RETRY_INTERVAL	100

/*
 * Handy macros
 */
#define	Tgt(sp)	((sp)->cmd_pkt->pkt_address.a_target)
#define	Lun(sp)	((sp)->cmd_pkt->pkt_address.a_lun)

/*
 * poll time for mpt_pollret() and mpt_wait_intr()
 */
#define	MPT_POLL_TIME	60000	/* 60 seconds */
#define	MPT_ONBUS_TIME	0x8F0D18 /* 15 seconds */

/*
 * macro to return the effective address of a given per-target field
 */
#define	EFF_ADDR(start, offset)		((start) + (offset))

#define	SDEV2ADDR(devp)		(&((devp)->sd_address))
#define	SDEV2TRAN(devp)		((devp)->sd_address.a_hba_tran)
#define	PKT2TRAN(pkt)		((pkt)->pkt_address.a_hba_tran)
#define	ADDR2TRAN(ap)		((ap)->a_hba_tran)

#define	TRAN2MPT(hba)		((mpt_t *)(hba)->tran_hba_private)
#define	SDEV2MPT(sd)		(TRAN2MPT(SDEV2TRAN(sd)))
#define	PKT2MPT(pkt)		(TRAN2MPT(PKT2TRAN(pkt)))

#define	ADDR2MPT(ap)		(TRAN2MPT(ADDR2TRAN(ap)))

#define	POLL_TIMEOUT		(2 * SCSI_POLL_TIMEOUT * 1000000)
#define	SHORT_POLL_TIMEOUT	(1000000)	/* in usec, about 1 secs */
#define	MPT_QUIESCE_TIMEOUT	1		/* 1 sec */

#define	MPT_GET_ISTAT(mpt)  (ddi_get32((mpt)->m_datap, \
			&(mpt)->m_reg->m_intr_status))

#define	MPT_SET_SIGP(P) \
		ClrSetBits(mpt->m_devaddr + NREG_ISTAT, 0, NB_ISTAT_SIGP)

#define	MPT_RESET_SIGP(P) (void) ddi_get8(mpt->m_datap, \
			(uint8_t *)(mpt->m_devaddr + NREG_CTEST2))

#define	MPT_GET_INTCODE(P) (ddi_get32(mpt->m_datap, \
			(uint32_t *)(mpt->m_devaddr + NREG_DSPS)))


#define	MPT_START_CMD(mpt, fma) \
	ddi_put32(mpt->m_datap, &mpt->m_reg->m_req_q, fma)

#define	INTPENDING(mpt) \
	(MPT_GET_ISTAT(mpt) & MPI_HIS_REPLY_MESSAGE_INTERRUPT)

#define	MPT_DISABLE_INTR(mpt)	\
	ddi_put32((mpt)->m_datap, &(mpt)->m_reg->m_intr_mask, \
	    (MPI_HIM_RIM | MPI_HIM_DIM))

#define	MPT_ENABLE_INTR(mpt)	\
	ddi_put32(mpt->m_datap, &mpt->m_reg->m_intr_mask, MPI_HIM_DIM)

#define	MPT_GET_NEXT_REPLY(mpt)	\
	ddi_get32(mpt->m_datap, &mpt->m_reg->m_reply_q)

#define	MPT_GET_NEXT_FRAME(mpt, slot) \
	(mpt->m_frame + ((mpt->m_req_frame_size * 4 * MPT_FRAME_SIZE(mpt)) * \
	    slot))

#define	ClrSetBits32(hdl, reg, clr, set) \
	ddi_put32(hdl, (reg), \
	    ((ddi_get32(mpt->m_datap, (reg)) & ~(clr)) | (set)))

#define	ClrSetBits(reg, clr, set) \
	ddi_put8(mpt->m_datap, (uint8_t *)(reg), \
		((ddi_get8(mpt->m_datap, (uint8_t *)(reg)) & ~(clr)) | (set)))

#define	MPT_WAITQ_RM(mpt, cmdp)	\
	if ((cmdp = mpt->m_waitq) != NULL) { \
		/* If the queue is now empty fix the tail pointer */	\
		if ((mpt->m_waitq = cmdp->cmd_linkp) == NULL) \
			mpt->m_waitqtail = &mpt->m_waitq; \
		cmdp->cmd_linkp = NULL; \
		cmdp->cmd_queued = FALSE; \
	}

/*
 * defaults for	the global properties
 */
#define	DEFAULT_SCSI_OPTIONS	SCSI_OPTIONS_DR
#define	DEFAULT_TAG_AGE_LIMIT	2
#define	DEFAULT_WD_TICK		10

/*
 * default hostid.
 */
#define	DEFAULT_HOSTID  7

/*
 * Config space.
 */
#define	MPT_LATENCY_TIMER	0x40

/*
 * Offsets into the cmd_cdb[] array (in mpt_cmd) for proxy data
 */
#define	MPT_PROXY_TYPE		CDB_GROUP0
#define	MPT_PROXY_RESULT	MPT_PROXY_TYPE+1

/*
 * Currently supported proxy types
 */
#define	MPT_PROXY_SNDMSG	1

/*
 * Offset to firmware version
 */
#define	MPT_FW_VERSION_OFFSET	9

/*
 * Offset and masks to get at the ProductId field
 */
#define	MPT_FW_PRODUCTID_OFFSET	8
#define	MPT_FW_PRODUCTID_MASK	0xFFFF0000
#define	MPT_FW_PRODUCTID_SHIFT	16

/*
 * Subsystem ID for HBAs.
 */
#define	MPT_HBA_SUBSYSTEM_ID    0x10C0

/*
 * reset delay tick
 */
#define	MPT_WATCH_RESET_DELAY_TICK 50	/* specified in milli seconds */

/*
 * throttle support.
 */
#define	MAX_THROTTLE	32
#define	HOLD_THROTTLE	0
#define	DRAIN_THROTTLE	-1
#define	QFULL_THROTTLE	-2

#define	NOTAG(mpt, tgt)		(mpt->m_notag & (1<<(tgt)))
#define	TAGGED(mpt, tgt)	(MPT_IS_SCSI(mpt) ? \
				    ((mpt->m_notag & (1<<(tgt))) == 0) : 1)

/*
 * Shared functions
 */
int mpt_save_cmd(struct mpt *mpt, struct mpt_cmd *cmd);
int mpt_config_space_init(struct mpt *mpt);
void mpt_log(struct mpt *mpt, int level, char *fmt, ...);
void mpt_report_fault(dev_info_t *dip, mpt_t *mpt, ddi_fault_impact_t impact,
	ddi_fault_location_t location, char *fmt, ...);
int mpt_poll(mpt_t *mpt, mpt_cmd_t *poll_cmd, int polltime);
int mpt_do_dma(mpt_t *mpt, uint32_t size, int var, int (*callback)());
int mpt_send_config_request_msg(mpt_t *mpt, uint8_t action,
	uint8_t pagetype, uint32_t pageaddress, uint8_t pagenumber,
	uint8_t pageversion, uint8_t pagelength, uint32_t
	SGEflagslength, uint32_t SGEaddress32);
int mpt_send_extended_config_request_msg(mpt_t *mpt, uint8_t action,
	uint8_t extpagetype, uint32_t pageaddress, uint8_t pagenumber,
	uint8_t pageversion, uint16_t extpagelength,
	uint32_t SGEflagslength, uint32_t SGEaddress32);
int mpt_update_flash(mpt_t *mpt, caddr_t ptrbuffer, uint32_t size,
	uint8_t type, int mode);
int mpt_check_flash(mpt_t *mpt, caddr_t origfile, uint32_t size,
	uint8_t type, int mode);
int mpt_download_firmware(mpt_t *mpt);
int mpt_can_download_firmware(mpt_t *mpt);
#ifdef MPT_DEBUG
void mpt_printf(char *fmt, ...);
#endif

/*
 * impl functions
 */
int mpt_ioc_wait_for_response(mpt_t *mpt);
int mpt_ioc_wait_for_doorbell(mpt_t *mpt);
int mpt_ioc_reset(mpt_t *mpt);
int mpt_send_handshake_msg(mpt_t *mpt, caddr_t memp, int numbytes,
	ddi_acc_handle_t accessp);
int mpt_get_handshake_msg(mpt_t *mpt, caddr_t memp, int numbytes,
	ddi_acc_handle_t accessp);
int mpt_request_from_pool(mpt_t *mpt, mpt_cmd_t **cmd, struct scsi_pkt **pkt);
void mpt_return_to_pool(mpt_t *mpt, mpt_cmd_t *cmd);
int mpt_ioc_task_management(struct mpt *mpt, int task_type, int bus,
	int target, int lun, int taskslot);
int mpt_send_event_ack(mpt_t *mpt, uint32_t event, uint32_t eventcntx);
void mpt_set_throttle(struct mpt *mpt, int target, int what);
int mpt_restart_ioc(mpt_t *mpt);
int8_t mpt_get_sas_device_phynum(mpt_t *mpt, int bus, int target);


/*
 * init functions
 */
int mpt_ioc_get_facts(mpt_t *mpt);
int mpt_ioc_get_port_facts(mpt_t *mpt, int port);
int mpt_ioc_enable_port(mpt_t *mpt, int port);
int mpt_ioc_enable_event_notification(mpt_t *mpt);
int mpt_ioc_init(mpt_t *mpt);

/*
 * RAID functions
 */
int mpt_get_raid_settings(mpt_t *mpt, uint8_t volid);
int mpt_get_raid_info(mpt_t *mpt);
int mpt_send_raid_action(mpt_t *mpt, uint8_t action, uint8_t vol,
	uint8_t physdisk, uint32_t flagslength, uint32_t SGEaddr,
	uint32_t dataword);
int mpt_get_physdisk_settings(mpt_t *mpt, int slot, uint8_t physdisknum);
int mpt_create_raid(mpt_t *mpt, mpt_disklist_t *disklist,
	uint8_t volid, int volsize, int raid_level);
int mpt_delete_volume(mpt_t *mpt, uint8_t volid);

/*
 * debugging.
 */
#if defined(MPT_DEBUG)

#define	MPT_DBGPR(m, args)	\
	if (mpt_debug_flags & (m)) \
		mpt_printf args
#else	/* ! defined(MPT_DEBUG) */
#define	MPT_DBGPR(m, args)
#endif	/* defined(MPT_DEBUG) */

#define	NDBG0(args)	MPT_DBGPR(0x01, args)		/* init	*/
#define	NDBG1(args)	MPT_DBGPR(0x02, args)		/* normal running */
#define	NDBG2(args)	MPT_DBGPR(0x04, args)		/* property handling */
#define	NDBG3(args)	MPT_DBGPR(0x08, args)		/* pkt handling */

#define	NDBG4(args)	MPT_DBGPR(0x10, args)		/* kmem alloc/free */
#define	NDBG5(args)	MPT_DBGPR(0x20, args)		/* polled cmds */
#define	NDBG6(args)	MPT_DBGPR(0x40, args)		/* interrupts */
#define	NDBG7(args)	MPT_DBGPR(0x80, args)		/* queue handling */

#define	NDBG8(args)	MPT_DBGPR(0x0100, args)		/* arq */
#define	NDBG9(args)	MPT_DBGPR(0x0200, args)		/* Tagged Q'ing */
#define	NDBG10(args)	MPT_DBGPR(0x0400, args)		/* halting chip */
#define	NDBG11(args)	MPT_DBGPR(0x0800, args)		/* power management */

#define	NDBG12(args)	MPT_DBGPR(0x1000, args)
#define	NDBG13(args)	MPT_DBGPR(0x2000, args)
#define	NDBG14(args)	MPT_DBGPR(0x4000, args)
#define	NDBG15(args)	MPT_DBGPR(0x8000, args)

#define	NDBG16(args)	MPT_DBGPR(0x010000, args)
#define	NDBG17(args)	MPT_DBGPR(0x020000, args)	/* scatter/gather */
#define	NDBG18(args)	MPT_DBGPR(0x040000, args)
#define	NDBG19(args)	MPT_DBGPR(0x080000, args)	/* handshaking */

#define	NDBG20(args)	MPT_DBGPR(0x100000, args)	/* events */
#define	NDBG21(args)	MPT_DBGPR(0x200000, args)	/* dma */
#define	NDBG22(args)	MPT_DBGPR(0x400000, args)	/* reset */
#define	NDBG23(args)	MPT_DBGPR(0x800000, args)	/* abort */

#define	NDBG24(args)	MPT_DBGPR(0x1000000, args)	/* capabilities */
#define	NDBG25(args)	MPT_DBGPR(0x2000000, args)	/* flushing */
#define	NDBG26(args)	MPT_DBGPR(0x4000000, args)
#define	NDBG27(args)	MPT_DBGPR(0x8000000, args)

#define	NDBG28(args)	MPT_DBGPR(0x10000000, args)	/* hotplug */
#define	NDBG29(args)	MPT_DBGPR(0x20000000, args)	/* timeouts */
#define	NDBG30(args)	MPT_DBGPR(0x40000000, args)	/* mpt_watch */
#define	NDBG31(args)	MPT_DBGPR(0x80000000, args)	/* negotations */

/*
 * auto request sense
 */
#define	RQ_MAKECOM_COMMON(pkt, flag, cmd) \
	(pkt)->pkt_flags = (flag), \
	((union scsi_cdb *)(pkt)->pkt_cdbp)->scc_cmd = (cmd), \
	((union scsi_cdb *)(pkt)->pkt_cdbp)->scc_lun = \
	    (pkt)->pkt_address.a_lun

#define	RQ_MAKECOM_G0(pkt, flag, cmd, addr, cnt) \
	RQ_MAKECOM_COMMON((pkt), (flag), (cmd)), \
	FORMG0ADDR(((union scsi_cdb *)(pkt)->pkt_cdbp), (addr)), \
	FORMG0COUNT(((union scsi_cdb *)(pkt)->pkt_cdbp), (cnt))


#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_SCSI_ADAPTERS_MPTVAR_H */
