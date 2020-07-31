/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_SCSI_ADAPTERS_SCSI_VHCI_H
#define	_SYS_SCSI_ADAPTERS_SCSI_VHCI_H

#pragma ident	"@(#)scsi_vhci.h	1.20	06/05/11 SMI"

/*
 * Multiplexed I/O SCSI vHCI global include
 */
#include <sys/note.h>
#include <sys/taskq.h>
#include <sys/mhd.h>
#include <sys/sunmdi.h>
#include <sys/mdi_impldefs.h>
#include <sys/scsi/adapters/mpapi_impl.h>
#include <sys/scsi/adapters/mpapi_scsi_vhci.h>

#ifdef	__cplusplus
extern "C" {
#endif

#if !defined(_BIT_FIELDS_LTOH) && !defined(_BIT_FIELDS_HTOL)
#error	One of _BIT_FIELDS_LTOH or _BIT_FIELDS_HTOL must be defined
#endif  /* _BIT_FIELDS_LTOH */

#ifdef	_KERNEL

#ifdef	UNDEFINED
#undef	UNDEFINED
#endif
#define	UNDEFINED		-1

#define	VHCI_STATE_OPEN		0x00000001


#define	VH_SLEEP		0x0
#define	VH_NOSLEEP		0x1

/*
 * HBA interface macros
 */

#define	TRAN2HBAPRIVATE(tran)	((struct scsi_vhci *)(tran)->tran_hba_private)
#define	VHCI_INIT_WAIT_TIMEOUT	60000000
#define	VHCI_FOWATCH_INTERVAL	1000000		/* in usecs */
#define	VHCI_EXTFO_TIMEOUT	3*60		/* 3 minutes */

#define	SCBP_C(pkt)	((*(pkt)->pkt_scbp) & STATUS_MASK)

int vhci_do_scsi_cmd(struct scsi_pkt *);
void vhci_log(int, dev_info_t *, const char *, ...);

/*
 * debugging stuff
 */

#ifdef	DEBUG

#ifndef VHCI_DEBUG_DEFAULT_VAL
#define	VHCI_DEBUG_DEFAULT_VAL		0
#endif	/* VHCI_DEBUG_DEFAULT_VAL */

extern int vhci_debug;

#include <sys/debug.h>

#define	VHCI_DEBUG(level, stmnt) \
	    if (vhci_debug >= (level)) vhci_log stmnt

#else	/* !DEBUG */

#define	VHCI_DEBUG(level, stmnt)

#endif	/* !DEBUG */



#define	VHCI_PKT_PRIV_SIZE		2

#define	ADDR2VHCI(ap)	(struct scsi_vhci *)((ap)->a_hba_tran->tran_hba_private)
#define	ADDR2VLUN(ap)	(scsi_vhci_lun_t *)((ap)->a_hba_tran->tran_tgt_private)
#define	ADDR2DIP(ap)	(dev_info_t *)((ap)->a_hba_tran->tran_sd->sd_dev)
#define	HBAPKT2VHCIPKT(pkt) (pkt->pkt_private)
#define	TGTPKT2VHCIPKT(pkt) (pkt->pkt_ha_private)
#define	VHCIPKT2HBAPKT(pkt) (pkt->pkt_hba_pkt)
#define	VHCIPKT2TGTPKT(pkt) (pkt->pkt_tgt_pkt)

#define	VHCI_DECR_PATH_CMDCOUNT(svp)	mutex_enter(&(svp)->svp_mutex); \
					(svp)->svp_cmds--; \
					if ((svp)->svp_cmds == 0)  \
						cv_broadcast(&(svp)->svp_cv); \
					mutex_exit(&(svp)->svp_mutex);

#define	VHCI_INCR_PATH_CMDCOUNT(svp)	mutex_enter(&(svp)->svp_mutex); \
					(svp)->svp_cmds++; \
					mutex_exit(&(svp)->svp_mutex);

/*
 * When a LUN is HELD it results in new IOs being returned to the target
 * driver layer with TRAN_BUSY.  Should be used while performing
 * operations that require prevention of any new IOs to the LUN and
 * the LUN should be HELD for the duration of such operations.
 * f can be VH_SLEEP or VH_NOSLEEP.
 * h is set to 1 to indicate LUN was successfully HELD.
 * h is set to 0 when f is VH_NOSLEEP and LUN is already HELD.
 *
 * Application examples:
 *
 * 1) SCSI-II RESERVE: HOLD LUN until it is quiesced and the load balancing
 * policy is switched to NONE before proceeding with RESERVE handling.
 *
 * 2) Failover: HOLD LUN before initiating failover.
 *
 * 3) When an externally initiated failover is detected, HOLD LUN until all
 * path states have been refreshed to reflect the new value.
 *
 */
#define	VHCI_HOLD_LUN(vlun, f, h) { \
	int sleep = (f); \
	mutex_enter(&(vlun)->svl_mutex); \
	if ((vlun)->svl_transient == 1) { \
		if (sleep == VH_SLEEP) { \
			while ((vlun)->svl_transient == 1) \
				cv_wait(&(vlun)->svl_cv, &(vlun)->svl_mutex); \
			(vlun)->svl_transient = 1; \
			(h) = 1; \
		} else { \
			(h) = 0; \
		} \
	} else { \
		(vlun)->svl_transient = 1; \
		(h) = 1; \
	} \
	sleep = (h); \
	mutex_exit(&(vlun)->svl_mutex); \
}

#define	VHCI_RELEASE_LUN(vlun) { \
	mutex_enter(&(vlun)->svl_mutex); \
	(vlun)->svl_transient = 0; \
	cv_broadcast(&(vlun)->svl_cv); \
	mutex_exit(&(vlun)->svl_mutex); \
}

#define	VHCI_LUN_IS_HELD(vlun)	((vlun)->svl_transient == 1)

/*
 * vhci_pkt states
 */
#define	VHCI_PKT_IDLE			0x01
#define	VHCI_PKT_ISSUED			0x02
#define	VHCI_PKT_ABORTING		0x04
#define	VHCI_PKT_STALE_BINDING		0x08
/*
 * Set the first time taskq is dispatched from scsi_start for
 * a packet.  To ensure vhci_scsi_start recognizes that the scsi_pkt
 * is being issued from the taskq and not target driver.
 */
#define	VHCI_PKT_THRU_TASKQ		0x20

#define	VHCI_PKT_TIMEOUT		30		/* seconds */
#define	VHCI_PKT_RETRY_CNT		2
#define	VHCI_POLL_TIMEOUT		60		/* seconds */

/*
 * define extended scsi cmd pkt
 */
#define	EXTCMDS_STATUS_SIZE		(sizeof (struct scsi_arq_status))

#define	CFLAG_NOWAIT		0x1000	/* don't sleep */
#define	CFLAG_DMA_PARTIAL	0x2000	/* Support Partial DMA */

#ifndef SCMD_PRIN
#define	SCMD_PRIN			0x5E
#endif

#ifndef SCMD_PROUT
#define	SCMD_PROUT			0x5F
#endif

/*
 * Maximum size of SCSI cdb in SCSI command
 */
#define	VHCI_SCSI_CDB_SIZE		16
#define	VHCI_SCSI_SCB_SIZE		(sizeof (struct scsi_arq_status))

#define	SCSI_OPTIONS_VHCI_MASK		0x7000000
#define	SCSI_OPTIONS_DISABLE_DEV_TYPE	0x7000000
#define	SCSI_OPTIONS_SYMMETRIC		0x1000000
#define	SCSI_OPTIONS_ASYMMETRIC		0x2000000
#define	SCSI_OPTIONS_SUN_T3_ASYMMETRIC	0x3000000

/*
 * flag to determine failover support
 */
#define	SCSI_NO_FAILOVER	0x0
#define	SCSI_IMPLICIT_FAILOVER	0x1
#define	SCSI_EXPLICIT_FAILOVER	0x2
#define	SCSI_BOTH_FAILOVER \
	(SCSI_IMPLICIT_FAILOVER |  SCSI_EXPLICIT_FAILOVER)

#define	SCSI_OPTIONS_VHCI(n)	((n) & SCSI_OPTIONS_VHCI_MASK)

typedef struct vhci_dev_vidpid_entry {
	char	vid[10];
	int	vid_len;
	char	pid[20];
	int	pid_len;
} vhci_dev_vidpid_entry_t;

struct	scsi_vhci_swarg;

typedef struct vhci_prin_readkeys {
	uint32_t		generation;
	uint32_t		length;
	mhioc_resv_key_t	keylist[MHIOC_RESV_KEY_SIZE];
} vhci_prin_readkeys_t;

#define	VHCI_PROUT_SIZE	\
	((sizeof (vhci_prout_t) - 2 * (MHIOC_RESV_KEY_SIZE) * sizeof (char)))

typedef struct vhci_prout {
	/* PGR register parameters start */
	uchar_t		res_key[MHIOC_RESV_KEY_SIZE];
	uchar_t		service_key[MHIOC_RESV_KEY_SIZE];
	uint32_t	scope_address;

#if defined(_BIT_FIELDS_LTOH)
	uchar_t		aptpl:1,
			reserved:7;
#else
	uchar_t		reserved:7,
			aptpl:1;
#endif /* _BIT_FIELDS_LTOH */

	uchar_t		reserved_1;
	uint16_t	ext_len;
	/* PGR register parameters end */

	/* Update VHCI_PROUT_SIZE if new fields are added here */

	uchar_t		active_res_key[MHIOC_RESV_KEY_SIZE];
	uchar_t		active_service_key[MHIOC_RESV_KEY_SIZE];
} vhci_prout_t;

#define	VHCI_PROUT_REGISTER	0x0
#define	VHCI_PROUT_RESERVE	0x1
#define	VHCI_PROUT_RELEASE	0x2
#define	VHCI_PROUT_CLEAR	0x3
#define	VHCI_PROUT_PREEMPT	0x4
#define	VHCI_PROUT_P_AND_A	0x5
#define	VHCI_PROUT_R_AND_IGNORE	0x6

struct vhci_pkt {
	struct scsi_pkt			*vpkt_tgt_pkt;
	mdi_pathinfo_t			*vpkt_path; 	/* path pkt bound to */

	/*
	 * pHCI packet that does the actual work.
	 */
	struct scsi_pkt			*vpkt_hba_pkt;

	uint_t				vpkt_state;
	uint_t				vpkt_flags;

	/*
	 * copy of vhci_scsi_init_pkt args.  Used when we invoke
	 * scsi_init_pkt() of the pHCI corresponding to the path that we
	 * bind to
	 */
	int				vpkt_tgt_init_cdblen;
	int				vpkt_tgt_init_privlen;
	int				vpkt_tgt_init_scblen;
	int				vpkt_tgt_init_pkt_flags;
	struct buf			*vpkt_tgt_init_bp;

	/*
	 * Pointer to original struct vhci_pkt for cmd sent by ssd.
	 * Saved when the command is being retried internally.
	 */
	struct vhci_pkt			*vpkt_org_vpkt;
};

typedef struct scsi_vhci_lun {
	kmutex_t		svl_mutex;
	kcondvar_t		svl_cv;

	/*
	 * following three fields are under svl_mutex protection
	 */
	int			svl_transient;

	/*
	 * to prevent unnecessary failover when a device is
	 * is discovered across a passive path and active path
	 * is still comng up
	 */
	int			svl_waiting_for_activepath;
	time_t			svl_wfa_time;

	/*
	 * for RESERVE/RELEASE support
	 */
	client_lb_t		svl_lb_policy_save;

	struct scsi_failover_ops	*svl_fops;
	void			*svl_fops_ctpriv;
	struct scsi_vhci_lun	*svl_hash_next;
	char			*svl_lun_wwn;

	/*
	 * currently active pathclass
	 */
	char			*svl_active_pclass;

	dev_info_t		*svl_dip;
	uint32_t		svl_flags;	/* protected by svl_mutex */

	/*
	 * When SCSI-II reservations are active we set the following pip
	 * to point to the path holding the reservation.  As long as
	 * the reservation is active this svl_resrv_pip is bound for the
	 * transport directly.  We bypass calling mdi_select_path to return
	 * a pip.
	 * The following pip is only valid when VLUN_RESERVE_ACTIVE_FLG
	 * is set.  This pip should not be accessed if this flag is reset.
	 */
	mdi_pathinfo_t	*svl_resrv_pip;

	/*
	 * following fields are for PGR support
	 */
	taskq_t			*svl_taskq;
	ksema_t			svl_pgr_sema;	/* PGR serialization */
	vhci_prin_readkeys_t	svl_prin;	/* PGR in data */
	vhci_prout_t		svl_prout;	/* PGR out data */
	uchar_t			svl_cdb[CDB_GROUP4];
	int			svl_time;	/* pkt_time */
	uint32_t		svl_bcount;	/* amount of data */
	int			svl_pgr_active; /* registrations active */
	mdi_pathinfo_t		*svl_first_path;

	/* external failover */
	int			svl_efo_update_path;
	struct	scsi_vhci_swarg	*svl_swarg;

	uint32_t		svl_support_lun_reset; /* Lun reset support */
	int			svl_not_supported;
	int			svl_xlf_capable; /* XLF implementation */
	int			svl_sector_size;
	int			svl_setcap_done;
	uint16_t		svl_fo_type;	 /* failover type */
	uint16_t		svl_fo_support;	 /* failover mode */
} scsi_vhci_lun_t;

#define	VLUN_TASK_D_ALIVE_FLG		0x01

/*
 * This flag is used to monitor the state of SCSI-II RESERVATION on the
 * lun.  A SCSI-II RESERVE cmd may be accepted by the target on the inactive
 * path.  This would then cause a subsequent IO to cause the paths to be
 * updated and be returned with a reservation conflict.  By monitoring this
 * flag, and sending a reset to the target when needed to clear the reservation,
 * one can avoid this conflict.
 */
#define	VLUN_RESERVE_ACTIVE_FLG		0x04

/*
 * This flag is set when a SCSI-II RESERVE cmd is received by scsi_vhci
 * and cleared when the pkt completes in vhci_intr.  It ensures that the
 * lun remains quiesced for the duration of this pkt.  This is different
 * from VHCI_HOLD_LUN as this pertains to IOs only.
 */
#define	VLUN_QUIESCED_FLG		0x08

/*
 * This flag is set to tell vhci_update_pathstates to call back
 * into vhci_mpapi_update_tpg_acc_state.
 */
#define	VLUN_UPDATE_TPG			0x10

/*
 * Various reset recovery depth.
 */

#define	VHCI_DEPTH_ALL		3
#define	VHCI_DEPTH_TARGET	2
#define	VHCI_DEPTH_LUN		1	/* For the sake completeness */
#define	TRUE			(1)
#define	FALSE			(0)

/*
 * this is stashed away in the client private area of
 * pathinfo
 */
typedef struct scsi_vhci_priv {
	kmutex_t		svp_mutex;
	kcondvar_t		svp_cv;
	struct scsi_vhci_lun	*svp_svl;

	/*
	 * scsi device associated with this
	 * pathinfo
	 */
	struct scsi_device	*svp_psd;

	/*
	 * number of outstanding commands on this
	 * path.  Protected by svp_mutex
	 */
	int			svp_cmds;

	/*
	 * following is used to prevent packets completing with the
	 * same error reason from flooding the screen
	 */
	uchar_t			svp_last_pkt_reason;

	/* external failover scsi_watch token */
	opaque_t		svp_sw_token;

	/* any cleanup operations for a newly found path. */
	int			svp_new_path;
} scsi_vhci_priv_t;

/*
 * argument to scsi_watch callback.  Used for processing
 * externally initiated failovers
 */
typedef struct scsi_vhci_swarg {
	scsi_vhci_priv_t	*svs_svp;
	time_t			svs_tos;	/* time of submission */
	mdi_pathinfo_t		*svs_pi;	/* pathinfo being "watched" */
	int			svs_release_lun;
	int			svs_done;
} scsi_vhci_swarg_t;

/*
 * scsi_vhci softstate
 *
 * vhci_mutex protects
 *	vhci_state
 * and	vhci_reset_notify list
 */
struct scsi_vhci {
	kmutex_t			vhci_mutex;
	dev_info_t			*vhci_dip;
	struct scsi_hba_tran		*vhci_tran;
	uint32_t			vhci_state;
	uint32_t			vhci_instance;
	kstat_t				vhci_kstat;
	/*
	 * This taskq is for general vhci operations like reservations,
	 * auto-failback, etc.
	 */
	taskq_t				*vhci_taskq;
	/* Dedicate taskq to handle external failovers */
	taskq_t				*vhci_update_pathstates_taskq;
	struct scsi_reset_notify_entry	*vhci_reset_notify_listf;
	uint16_t			vhci_conf_flags;
	mpapi_priv_t			*mp_priv;
};

/*
 * vHCI flags for configuration settings, defined in scsi_vhci.conf
 */
#define	VHCI_CONF_FLAGS_AUTO_FAILBACK	0x0001	/* Enables auto failback */

typedef enum {
	SCSI_PATH_INACTIVE,
	SCSI_PATH_ACTIVE,
	SCSI_PATH_ACTIVE_NONOPT
} scsi_path_state_t;

#define	SCSI_MAXPCLASSLEN	25

#define	OPINFO_REV	1

/*
 * structure describing operational characteristics of
 * path
 */
struct scsi_path_opinfo {
	int			opinfo_rev;

	/*
	 * name of pathclass. Eg. "primary", "secondary"
	 */
	char			opinfo_path_attr[SCSI_MAXPCLASSLEN];

	/*
	 * path state: ACTIVE/PASSIVE
	 */
	scsi_path_state_t	opinfo_path_state;

	/*
	 * the best and worst case time estimates for
	 * failover operation to complete
	 */
	uint_t			opinfo_pswtch_best;
	uint_t			opinfo_pswtch_worst;

	/* XLF implementation */
	int			opinfo_xlf_capable;
	uint16_t		opinfo_preferred;
	uint16_t		opinfo_mode;

};


#define	SFO_REV		1

/*
 * vectors for device specific failover related operations
 */
struct scsi_failover_ops {
	int	sfo_rev;

	/*
	 * identify device
	 */
	int	(*sfo_device_probe)(
			struct scsi_device	*sd,
			struct scsi_inquiry 	*stdinq,
			void 			**ctpriv);

	/*
	 * housekeeping (free memory etc alloc'ed during probe
	 */
	void	(*sfo_device_unprobe)(
			struct scsi_device 	*sd,
			void 			*ctpriv);

	/*
	 * bring a path ONLINE (ie make it ACTIVE)
	 */
	int	(*sfo_path_activate)(
			struct scsi_device 	*sd,
			char 			*pathclass,
			void 			*ctpriv);

	/*
	 * inverse of above
	 */
	int 	(*sfo_path_deactivate)(
			struct scsi_device 	*sd,
			char 			*pathclass,
			void 			*ctpriv);

	/*
	 * returns operational characteristics of path
	 */
	int	(*sfo_path_get_opinfo)(
			struct scsi_device 	*sd,
			struct scsi_path_opinfo *opinfo,
			void 			*ctpriv);

	/*
	 * verify path is operational
	 */
	int	(*sfo_path_ping)(
			struct scsi_device 	*sd,
			void 			*ctpriv);

	/*
	 * analyze SENSE data to detect externally initiated
	 * failovers
	 */
	int	(*sfo_analyze_sense)(
			struct scsi_device 		*sd,
			struct scsi_extended_sense 	*sense,
			void 				*ctpriv);

	/*
	 * return the next pathclass in order of preference
	 * eg. "secondary" comes after "primary"
	 */
	int	(*sfo_pathclass_next)(
			char 			*cur,
			char 			**nxt,
			void 			*ctpriv);
};

/* return values for sfo_analyze_sense() */
#define	SCSI_SENSE_NOFAILOVER		0
#define	SCSI_SENSE_FAILOVER_INPROG	1
#define	SCSI_SENSE_ACT2INACT		2
#define	SCSI_SENSE_INACT2ACT		3
#define	SCSI_SENSE_INACTIVE		4
#define	SCSI_SENSE_UNKNOWN		5
#define	SCSI_SENSE_STATE_CHANGED	6

/* vhci_intr action codes */
#define	JUST_RETURN			0
#define	BUSY_RETURN			1
#define	PKT_RETURN			2

#if	defined(_SYSCALL32)
/*
 * 32 bit varients of sv_path_info_prop_t and sv_path_info_t;
 * To be used only in the driver and NOT applications
 */
typedef struct sv_path_info_prop32 {
	uint32_t	buf_size;	/* user buffer size */
	caddr32_t	ret_buf_size;	/* actual buffer needed */
	caddr32_t	buf;		/* user space buffer */
} sv_path_info_prop32_t;

typedef struct sv_path_info32 {
	union {
		char	ret_ct[MAXPATHLEN];		/* client device */
		char	ret_phci[MAXPATHLEN];		/* pHCI device */
	} device;

	char			ret_addr[MAXNAMELEN];	/* device address */
	mdi_pathinfo_state_t	ret_state;		/* state information */
	uint32_t		ret_ext_state;		/* Extended State */
	sv_path_info_prop32_t	ret_prop;		/* path attributes */
} sv_path_info32_t;

typedef struct sv_iocdata32 {
	caddr32_t	client;		/* client dev devfs path name */
	caddr32_t	phci;		/* pHCI dev devfs path name */
	caddr32_t	addr;		/* device address */
	uint32_t	buf_elem;	/* number of path_info elems */
	caddr32_t	ret_buf;	/* addr of array of sv_path_info */
	caddr32_t	ret_elem;	/* count of above sv_path_info */
} sv_iocdata32_t;

typedef struct sv_switch_to_cntlr_iocdata32 {
	caddr32_t	client;	/* client device devfs path name */
	caddr32_t	class;	/* desired path class to be made active */
} sv_switch_to_cntlr_iocdata32_t;

#endif	/* _SYSCALL32 */

#endif	/* _KERNEL */

/*
 * Userland (Non Kernel) definitions start here.
 * Multiplexed I/O SCSI vHCI IOCTL Definitions
 */

/*
 * IOCTL structure for path properties
 */
typedef struct sv_path_info_prop {
	uint_t	buf_size;	/* user buffer size */
	uint_t	*ret_buf_size;	/* actual buffer needed */
	caddr_t	buf;		/* user space buffer */
} sv_path_info_prop_t;

/*
 * Max buffer size of getting path properties
 */
#define	SV_PROP_MAX_BUF_SIZE	4096

/*
 * String values for "path-class" property
 */
#define	PCLASS_PRIMARY		"primary"
#define	PCLASS_SECONDARY	"secondary"

#define	PCLASS_PREFERRED	1
#define	PCLASS_NONPREFERRED	0

/*
 * IOCTL structure for path information
 */
typedef struct sv_path_info {
	union {
		char	ret_ct[MAXPATHLEN];		/* client device */
		char	ret_phci[MAXPATHLEN];		/* pHCI device */
	} device;

	char			ret_addr[MAXNAMELEN];	/* device address */
	mdi_pathinfo_state_t	ret_state;		/* state information */
	uint32_t		ret_ext_state;		/* Extended State */
	sv_path_info_prop_t	ret_prop;		/* path attributes */
} sv_path_info_t;

/*
 * IOCTL argument structure
 */
typedef struct sv_iocdata {
	caddr_t		client;		/* client dev devfs path name */
	caddr_t		phci;		/* pHCI dev devfs path name */
	caddr_t		addr;		/* device address */
	uint_t		buf_elem;	/* number of path_info elems */
	sv_path_info_t	*ret_buf;	/* array of sv_path_info */
	uint_t		*ret_elem;	/* count of sv_path_info */
} sv_iocdata_t;

/*
 * IOCTL argument structure for switching controllers
 */
typedef struct sv_switch_to_cntlr_iocdata {
	caddr_t		client;	/* client device devfs path name */
	caddr_t		class;	/* desired path class to be made active */
} sv_switch_to_cntlr_iocdata_t;


/*
 * IOCTL definitions
 */
#define	SCSI_VHCI_CTL		('X' << 8)
#define	SCSI_VHCI_CTL_CMD	(SCSI_VHCI_CTL | ('S' << 8) | 'P')
#define	SCSI_VHCI_CTL_SUB_CMD	('x' << 8)

#define	SCSI_VHCI_GET_CLIENT_MULTIPATH_INFO	(SCSI_VHCI_CTL_SUB_CMD + 0x01)
#define	SCSI_VHCI_GET_PHCI_MULTIPATH_INFO	(SCSI_VHCI_CTL_SUB_CMD + 0x02)
#define	SCSI_VHCI_GET_CLIENT_NAME		(SCSI_VHCI_CTL_SUB_CMD + 0x03)
#define	SCSI_VHCI_PATH_ONLINE			(SCSI_VHCI_CTL_SUB_CMD + 0x04)
#define	SCSI_VHCI_PATH_OFFLINE			(SCSI_VHCI_CTL_SUB_CMD + 0x05)
#define	SCSI_VHCI_PATH_STANDBY			(SCSI_VHCI_CTL_SUB_CMD + 0x06)
#define	SCSI_VHCI_PATH_TEST			(SCSI_VHCI_CTL_SUB_CMD + 0x07)
#define	SCSI_VHCI_SWITCH_TO_CNTLR		(SCSI_VHCI_CTL_SUB_CMD + 0x08)

#ifdef	DEBUG
#define	SCSI_VHCI_GET_PHCI_LIST			(SCSI_VHCI_CTL_SUB_CMD + 0x09)
#define	SCSI_VHCI_CONFIGURE_PHCI		(SCSI_VHCI_CTL_SUB_CMD + 0x0A)
#define	SCSI_VHCI_UNCONFIGURE_PHCI		(SCSI_VHCI_CTL_SUB_CMD + 0x0B)
#endif

#define	SCSI_VHCI_PATH_DISABLE			(SCSI_VHCI_CTL_SUB_CMD + 0x0C)
#define	SCSI_VHCI_PATH_ENABLE			(SCSI_VHCI_CTL_SUB_CMD + 0x0D)
#define	SCSI_VHCI_MPAPI				(SCSI_VHCI_CTL_SUB_CMD + 0x0E)

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_SCSI_ADAPTERS_SCSI_VHCI_H */