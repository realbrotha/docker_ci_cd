/*
 * Copyright (c) 1992-2000 by Sun Microsystems, Inc.
 * All rights reserved.
 */

#ifndef	_SYS_GE_COMMON_H
#define	_SYS_GE_COMMON_H

#pragma ident	"@(#)ge_common.h	2.14	03/08/30 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef _KERNEL

typedef int	(*fptri_t)();
typedef void	(*fptrv_t)();



#if 0
#define		GE_CORRUPTION_DEBUG
#define		GE_OBPFORCE_DEBUG
#define		GE_100T4_DEBUG
#define		GE_LINKPULSE_DEBUG
#define		GE_LANCE_MODE_DEBUG
#define		GE_BOOT_DEBUG
#define		GE_CONF_DEBUG
#define		GE_FASTDMA_DEBUG
#define		GE_INTR_DEBUG
#define		GE_DMA_DEBUG
#define		GE_ALLOC_DEBUG
#define		GE_CORRUPTION_DEBUG
#define		GE_START_DEBUG
#define		GE_IPG_DEBUG
#define		GE_ND_DEBUG
#define		GE_PHY_DEBUG
#define		GE_MAC_DEBUG
#define		GE_LATECOLL_DEBUG
#define		GE_CFG_DEBUG
#define		GE_MIFPOLL_DEBUG
#define		GE_AUTOINFO_DEBUG
#define		GE_LINKCHECK_DEBUG
#define		GE_AR_DEBUG
#define		GE_AUTOINFO_DEBUG
#define		GE_FDX_DEBUG
#define		GE_AUTONEG_DEBUG
#define		GE_EXT_XCVR_DEBUG
#define		GE_FRM_DEBUG
#define		GE_SYNC_DEBUG
#define		GE_READ_DEBUG
#define		GE_FORCE_DEBUG
#endif

#if defined SOL2_8 || defined SOL2_8_1
#define	GE_HWCSUM
#else
#define	GE_NEW_HWCSUM
#endif

#define	GE_CKSUM_START 0

/*
 * GEM REV 2.0 has some hardware bugs which doesn't alow it
 * to function to full features. We define this flag to disable
 * the features affected by these bugs.
 */

#define	GE_GEM_REV_2_0

#ifdef		GE_GEM_REV_2_0
#define		GE_CONTINUOUS_RESET
#define		GE_HDX_BUG_WORKAROUND
#define		RCV_OVRFLOW_CORRUPTION_BUG
#endif


#ifdef GE_HWCSUM
#include	<sys/strick.h>
#define	GE_RCV_CKSUM
#define	IP_PACKET_IS_TCP(ipp)	(ipp->ip_p & 0x06)
#endif

#define	GEHIWAT		(128 * 1024)    /* hi-water mark */
#define	GE_HB_SAP	0x833		/* for cluster heartbeat sap == 0x833 */
#define	GE_SPWB_INTR	1		/* for using putnext in rcv */

#define	GERINDEX(i)	(i & gep->ge_gerpending_mask)

#define	DONT_FLUSH	-1


/*
 * XXX
 * Define GESYNCIOPB to nothing for now.
 * If/when we have PSO-mode kernels running which really need
 * to sync something during a ddi_dma_sync() of iopb-allocated memory,
 * then this can go back in, but for now we take it out
 * to save some microseconds.
 */
#define	GESYNCIOPB(gep, a, size, who)

#ifdef notdef
/*
 * ddi_dma_sync() a TMD or RMD descriptor.
 */
#define	GESYNCIOPB(gep, a, size, who) \
	(void) ddi_dma_sync((gep)->ge_iopbhandle, \
		((uintptr_t)(a) - (gep)->ge_iopbkbase), \
		(size), \
		(who))
#endif


/* ------------------------------------------------------------------------- */
/*
 * Patchable debug flag.
 * Set this to nonzero to enable error messages.
 */

/*
 * The following parameters may be configured by the user. If they are not
 * configured by the user, the values will be based on the capabilities of
 * the transceiver.
 * The value "GE_NOTUSR" is ORed with the parameter value to indicate values
 * which are NOT configured by the user.
 */

/* command */

#define	ND_BASE		('N' << 8)	/* base */
#define	ND_GET		(ND_BASE + 0)	/* Get a value */
#define	ND_SET		(ND_BASE + 1)	/* Set a value */

#define	GE_ND_GET	ND_GET
#define	GE_ND_SET	ND_SET
#define	GE_NOTUSR	0x0f000000
#define	GE_MASK_1BIT	0x1
#define	GE_MASK_2BIT	0x3
#define	GE_MASK_8BIT	0xff

#define	ge_param_transceiver	(gep->ge_param_arr[0].ge_param_val)
#define	ge_param_linkup		(gep->ge_param_arr[1].ge_param_val)
#define	ge_param_speed		(gep->ge_param_arr[2].ge_param_val)
#define	ge_param_mode		(gep->ge_param_arr[3].ge_param_val)
#define	ge_param_ipg1		(gep->ge_param_arr[4].ge_param_val)
#define	ge_param_ipg2		(gep->ge_param_arr[5].ge_param_val)
#define	ge_param_use_intphy	(gep->ge_param_arr[6].ge_param_val)
#define	ge_param_pace_count	(gep->ge_param_arr[7].ge_param_val)
#define	ge_param_autoneg	(gep->ge_param_arr[8].ge_param_val)
#define	ge_param_anar_100T4	(gep->ge_param_arr[9].ge_param_val)
#define	ge_param_anar_100fdx	(gep->ge_param_arr[10].ge_param_val)
#define	ge_param_anar_100hdx	(gep->ge_param_arr[11].ge_param_val)
#define	ge_param_anar_10fdx	(gep->ge_param_arr[12].ge_param_val)
#define	ge_param_anar_10hdx	(gep->ge_param_arr[13].ge_param_val)
#define	ge_param_bmsr_ancap	(gep->ge_param_arr[14].ge_param_val)
#define	ge_param_bmsr_100T4	(gep->ge_param_arr[15].ge_param_val)
#define	ge_param_bmsr_100fdx	(gep->ge_param_arr[16].ge_param_val)
#define	ge_param_bmsr_100hdx	(gep->ge_param_arr[17].ge_param_val)
#define	ge_param_bmsr_10fdx	(gep->ge_param_arr[18].ge_param_val)
#define	ge_param_bmsr_10hdx	(gep->ge_param_arr[19].ge_param_val)
#define	ge_param_aner_lpancap	(gep->ge_param_arr[20].ge_param_val)
#define	ge_param_anlpar_100T4	(gep->ge_param_arr[21].ge_param_val)
#define	ge_param_anlpar_100fdx	(gep->ge_param_arr[22].ge_param_val)
#define	ge_param_anlpar_100hdx	(gep->ge_param_arr[23].ge_param_val)
#define	ge_param_anlpar_10fdx	(gep->ge_param_arr[24].ge_param_val)
#define	ge_param_anlpar_10hdx	(gep->ge_param_arr[25].ge_param_val)
#define	ge_param_device		(gep->ge_param_arr[26].ge_param_val)
#define	ge_param_lance_mode	(gep->ge_param_arr[27].ge_param_val)
#define	ge_param_ipg0		(gep->ge_param_arr[28].ge_param_val)
#define	ge_param_serial_link	(gep->ge_param_arr[29].ge_param_val)
#define	ge_param_non_serial_link	(gep->ge_param_arr[30].ge_param_val)
#define	ge_param_select_link	(gep->ge_param_arr[31].ge_param_val)
#define	ge_param_default_link	(gep->ge_param_arr[32].ge_param_val)
#define	ge_param_link_in_use	(gep->ge_param_arr[33].ge_param_val)
#define	ge_param_1000autoneg	(gep->ge_param_arr[34].ge_param_val)
#define	ge_param_anar_1000fdx	(gep->ge_param_arr[35].ge_param_val)
#define	ge_param_anar_1000hdx	(gep->ge_param_arr[36].ge_param_val)
#define	ge_param_pauseTX	(gep->ge_param_arr[37].ge_param_val)
#define	ge_param_pauseRX	(gep->ge_param_arr[38].ge_param_val)
#define	ge_param_bmsr_1000aneg	(gep->ge_param_arr[39].ge_param_val)
#define	ge_param_bmsr_1000fdx	(gep->ge_param_arr[40].ge_param_val)
#define	ge_param_bmsr_1000hdx	(gep->ge_param_arr[41].ge_param_val)
#define	ge_param_bmsr_asm_dir	(gep->ge_param_arr[42].ge_param_val)
#define	ge_param_bmsr_pause	(gep->ge_param_arr[43].ge_param_val)
#define	ge_param_anlpar_autoneg	(gep->ge_param_arr[44].ge_param_val)
#define	ge_param_anlpar_1000fdx	(gep->ge_param_arr[45].ge_param_val)
#define	ge_param_anlpar_1000hdx	(gep->ge_param_arr[46].ge_param_val)
#define	ge_param_anlpar_asm_dir	(gep->ge_param_arr[47].ge_param_val)
#define	ge_param_anlpar_pause	(gep->ge_param_arr[48].ge_param_val)





/* ------------------------------------------------------------------------- */
/*
 * Global Functions.
 */

/* ge_hw.c */
extern	uint_t	geintr();
extern	int	geinit(struct ge *);
extern	int	gestop(struct ge *);
extern	int	gefreebufs(struct ge *);
extern	void	geuninit(struct ge *gep);
extern	void	gesavecntrs(struct ge *);

/* ge_xcvr.c */
extern	void	ge_check_link(struct ge *);
extern	void	ge_stop_timer(struct ge *gep);
extern	void	ge_start_timer(struct ge *gep, fptrv_t func, clock_t msec);
extern	void	ge_start_linkpoll(struct ge *);
extern	void	ge_stop_linkpoll(struct ge *);


/* ge_dlpi.c */
extern	int	gewput(queue_t *, mblk_t *);
extern	int	geopen(queue_t *, dev_t *, int, int, cred_t *);
extern	int	geclose(queue_t *);
extern	int	gewsrv(queue_t *);
extern	int	gersrv(queue_t *);

/* ge_io.c */
extern	mblk_t * geallocb(size_t size, uint32_t pri);
extern	void	gereclaim(struct ge *, uint32_t);
extern void ge_rcv_putnext();

/* ge_util.c */
extern	int	geinit_xfer_params(struct ge *gep);
extern	void	gerror(dev_info_t *dip, char *fmt, ...);
extern  void	ge_display_msg(struct ge *gep, dev_info_t *dip, char *fmt, ...);
extern	int	ge_nd_getset(queue_t *q, caddr_t nd_param, MBLKP mp);
extern	void	ge_param_cleanup(struct ge *gep);
extern	int	ge_param_register(struct ge *, geparam_t *, int);
extern	void	ge_process_ndd_ioctl(queue_t *wq, mblk_t *mp, int cmd);

#pragma weak strtol
#ifdef GE_NEW_HWCSUM
#pragma weak hcksum_retrieve
#pragma weak hcksum_assoc
#endif
#pragma weak dlcapabsetqid

extern	long int strtol(const char *, char **, int);
#define	strtol(a, b, c) \
	(strtol != NULL ? strtol(a, b, c) : ge_strtol(a, b, c))
#ifdef GE_NEW_HWCSUM
#define	hcksum_retrieve(a, b, c, d, e, f, g, h) \
	if (hcksum_retrieve != NULL) \
		 hcksum_retrieve(a, b, c, d, e, f, g, h)
#define	hcksum_assoc(a, b, c, d, e, f, g, h, i) \
	(hcksum_assoc != NULL ? hcksum_assoc(a, b, c, d, e, f, g, h, i) : 0)
#endif
#define	dlcapabsetqid(a, b) \
	if (dlcapabsetqid != NULL) \
		dlcapabsetqid(a, b)

/* <<<<<<<<<<<<<<<<<<<<<<  Register operations >>>>>>>>>>>>>>>>>>>>> */

#define	GET_PCSREG(reg) \
	ddi_get32(gep->ge_pcsregh, (uint32_t *)&gep->ge_pcsregp->reg)
#define	PUT_PCSREG(reg, value) \
	ddi_put32(gep->ge_pcsregh, (uint32_t *)&gep->ge_pcsregp->reg, value)
#define	GET_MIFREG(reg) \
	ddi_get32(gep->ge_mifregh, (uint32_t *)&gep->ge_mifregp->reg)
#define	PUT_MIFREG(reg, value) \
	ddi_put32(gep->ge_mifregh, (uint32_t *)&gep->ge_mifregp->reg, value)
#define	GET_ETXREG(reg) \
	ddi_get32(gep->ge_etxregh, (uint32_t *)&gep->ge_etxregp->reg)
#define	PUT_ETXREG(reg, value) \
	ddi_put32(gep->ge_etxregh, (uint32_t *)&gep->ge_etxregp->reg, value)
#define	GET_ERXREG(reg) \
	ddi_get32(gep->ge_erxregh, (uint32_t *)&gep->ge_erxregp->reg)
#define	PUT_ERXREG(reg, value) \
	ddi_put32(gep->ge_erxregh, (uint32_t *)&gep->ge_erxregp->reg, value)
#define	GET_MACREG(reg) \
	ddi_get32(gep->ge_bmacregh, (uint32_t *)&gep->ge_bmacregp->reg)
#define	PUT_MACREG(reg, value) \
	ddi_put32(gep->ge_bmacregh, \
		(uint32_t *)&gep->ge_bmacregp->reg, value)
#define	GET_GLOBREG(reg) \
	ddi_get32(gep->ge_globregh, (uint32_t *)&gep->ge_globregp->reg)
#define	PUT_GLOBREG(reg, value) \
	ddi_put32(gep->ge_globregh, \
		(uint32_t *)&gep->ge_globregp->reg, value)

#define	GET_SWRSTREG(reg) \
	ddi_get32(gep->ge_sw_reset_regh, (uint32_t *)gep->ge_sw_reset_reg)

#define	PUT_SWRSTREG(reg, value) \
	ddi_put32(gep->ge_sw_reset_regh, \
	(uint32_t *)gep->ge_sw_reset_reg, value)
#define	GET_ROM8(offset) \
	ddi_get8((gep->ge_romh), (offset))

/* ********************** Descriptor OPerations ******************** */


/* <<<<<<<<<<<<<<<<<<<<<  for Solaris 2.6 and beyond >>>>>>>>>>>>>>>>>>>> */

/* TMD and RMD Descriptor Operations */
/* aaa it was using cookie.dmac_laddress for PUT_TMD */
/* we'll give appropriate dmac_[l]address for using macro now */
#define	PUT_TMD(ptr, cookie, len, flags, pci_bus) \
	ddi_put64(gep->ge_mdm_h, (uint64_t *)&ptr->tmd_addr, \
		cookie); \
	ddi_put64(gep->ge_mdm_h, (uint64_t *)&ptr->tmd_flags, len | flags)

#define	PUT_TMD_FAST(ptr, cookie, len, flags, pci_bus) \
	ddi_put64(gep->ge_mdm_h, (uint64_t *)&ptr->tmd_addr, \
		cookie.dmac_address); \
	ddi_put64(gep->ge_mdm_h, (uint64_t *)&ptr->tmd_flags, len | flags)

#define	GET_TMD_FLAGS(ptr, pci_bus) \
	ddi_get64(gep->ge_mdm_h, (uint64_t *)&ptr->tmd_flags)

#define	PUT_RMD(ptr, cookie, gerbufsize, pci_bus) \
	ddi_put64(gep->ge_mdm_h, (uint64_t *)&ptr->rmd_addr, \
		cookie.dmac_laddress); \
	ddi_put64(gep->ge_mdm_h, (uint64_t *)&ptr->rmd_flags, \
	    (uint64_t)(gerbufsize << GERMD_BUFSIZE_SHIFT) | GERMD_OWN)

#define	UPDATE_RMD(ptr, gerbufsize, pci_bus) \
	ddi_put64(gep->ge_mdm_h, (uint64_t *)&ptr->rmd_flags, \
	    (uint64_t)(gerbufsize << GERMD_BUFSIZE_SHIFT) | GERMD_OWN)

#define	PUT_RMD_FAST(ptr, cookie, gerbufsize, pci_bus) \
	ddi_put64(gep->ge_mdm_h, (uint64_t *)&ptr->rmd_addr, \
		cookie.dmac_address); \
	ddi_put64(gep->ge_mdm_h, (uint64_t *)&ptr->rmd_flags, \
	    (uint64_t)(gerbufsize << GERMD_BUFSIZE_SHIFT) | GERMD_OWN)

#define	GET_RMD_FLAGS(ptr, pci_bus) \
	ddi_get64(gep->ge_mdm_h, (uint64_t *)&ptr->rmd_flags)

#define	GET_RMD_ADDR(ptr, pci_bus) \
	ddi_get64(gep->ge_mdm_h, (uint64_t *)&ptr->rmd_addr)

#define	GET_SBRSTREG(reg) \
	ddi_get32(gep->ge_Sbus_reset_regh, (uint32_t *)gep->ge_Sbus_reset_reg)

#define	GET_SBCFGREG(reg) \
	ddi_get32(gep->ge_Sbus_config_regh, (uint32_t *)gep->ge_Sbus_config_reg)

#define	GET_SBSTSREG(reg) \
	ddi_get32(gep->ge_Sbus_status_regh, (uint32_t *)gep->ge_Sbus_status_reg)

#define	GET_SBIDREG(reg) \
	ddi_get32(gep->ge_Sbus_id_regh, (uint32_t *)gep->ge_Sbus_id_reg)

#define	PUT_SBRSTREG(reg, value) \
	ddi_put32(gep->ge_Sbus_reset_regh, \
	(uint32_t *)gep->ge_Sbus_reset_reg, value)

#define	ENABLE_TXMAC(gep) \
	PUT_MACREG(txcfg, GET_MACREG(txcfg) | BMAC_TXCFG_ENAB)

#define	ENABLE_RXMAC(gep) \
	PUT_MACREG(rxcfg, GET_MACREG(rxcfg) | BMAC_RXCFG_ENAB)

#define	DISABLE_RXMAC(gep) \
	PUT_MACREG(rxcfg, GET_MACREG(rxcfg) & ~BMAC_RXCFG_ENAB)

#define	DISABLE_TXMAC(gep) \
	PUT_MACREG(txcfg, GET_MACREG(txcfg) & ~BMAC_TXCFG_ENAB)

#define	ENABLE_MAC(gep) \
	ENABLE_RXMAC(gep); \
	ENABLE_TXMAC(gep)

#define	DISABLE_MAC(gep) \
	DISABLE_RXMAC(gep); \
	DISABLE_TXMAC(gep)

#define	ENABLE_TXDMA(gep) \
	PUT_ETXREG(config,  GET_ETXREG(config) | GET_CONFIG_TXDMA_EN)

#define	ENABLE_RXDMA(gep) \
	PUT_ERXREG(config,  GET_ERXREG(config) | GER_CONFIG_RXDMA_EN)


/*
 * Ether_copy is not endian-correct. Define an endian-correct version.
 */
#define	ether_bcopy(a, b) (bcopy((caddr_t)a, (caddr_t)b, 6))

/*
 * Ether-type is specifically big-endian, but data region is unknown endian
 */

typedef struct ether_header *eehp;

#define	get_ether_type(ptr) (\
	(((uchar_t *)&((eehp)ptr)->ether_type)[0] << 8) | \
	(((uchar_t *)&((eehp)ptr)->ether_type)[1]))
#define	put_ether_type(ptr, value) {\
	((uchar_t *)(&((eehp)ptr)->ether_type))[0] = \
	    ((uint16_t)value & 0xff00) >> 8; \
	((uchar_t *)(&((eehp)ptr)->ether_type))[1] = (value & 0xff); }


/*
 * The following MACROS are used to filter out bad packets which are
 * a result of descriptor corruption in GEM 1.0 ASIC. The packets are
 * either concatenated or truncated. Here we compare the length field
 * of the incoming packet with what is reported by the decriptor
 * length field. This check is in addition to the illegal packet
 *  (64 < len < 1518)  size check done in geread routines.
 */

#ifdef GE_GEM_REV_2_0
#define	IP_PACKET_LEN(len) \
	(len - 14)
#define	INVALID_IP_PACKET_LENGTH(ipp, len) \
	((len > 0x3c) && (ipp->ip_len != (len - 14)))

#define	IP_PACKET_IS_TCP(ipp)	(ipp->ip_p & 0x06)

#define	GE_ERX_HANG(wp, rp) \
	    ((rp <= wp) ? ((wp - rp) > 1275) : ((rp -wp) < 4))
#endif



#define	GE_TX_FREE(gep, txinfop)					\
	if (txinfop->flags & TXB_TINYBUF) {				\
		txinfop->idx = 0;					\
		txinfop->flags &= ~TXB_TINYBUF;				\
	} else if (txinfop->flags & TXB_FASTMAP) {			\
		dvma_unload(gep->txfast_handle, txinfop->idx,		\
			(uint_t) DONT_FLUSH);				\
		gep->txfast_quehd++;					\
		gep->txfast_queue[gep->txfast_quehd] = txinfop->idx;	\
		txinfop->idx = 0;					\
		txinfop->flags &= ~TXB_FASTMAP;	                        \
	} else if (txinfop->flags & TXB_BINDMAP) {			\
		if (ddi_dma_unbind_handle(txinfop->handle))		\
			gerror(gep->ge_dip, 				\
				"ddi_dma_unbind_handle failed.");	\
		txinfop->flags &= ~TXB_BINDMAP;				\
	} /* else do nothing */


#define	DEVICE_NAME(dip) \
	    ((strcmp(ddi_get_name(dip), "SUNW,sbus-gem") == 0) ? \
	    "SUNW,sbus-gem" : "SUNW,pci-gem")


/*
 * Allocate and zero-out "number" structures
 * each of type "structure" in kernel memory.
 */
#define	GETSTRUCT(structure, number)   \
	((structure *) kmem_zalloc(\
		(size_t) (sizeof (structure) * (number)), KM_SLEEP))


#define	GE_FREE_POLL_QUEUE(gep)	{				\
		drv_queue_t *queue;				\
		mblk_t *mp;					\
		queue = &gep->drv_queue;			\
		while (mp = queue->drvq_head) {			\
			queue->drvq_head = mp->b_next;		\
			mp->b_next = NULL;			\
			freemsg(mp);				\
		}						\
		queue->drvq_head = NULL;			\
		queue->drvq_tail = NULL;			\
		queue->drvq_count = 0;				\
}

/* Global Variables */

/*
 * Linked list of ge structures - one per card.
 */
extern struct ge *geup;

/*
 * Linked list of active (inuse) driver Streams.
 */
extern	struct	gestr	*gestrup;
extern	krwlock_t	gestruplock;


extern	kmutex_t	gelock;


#endif	/* _KERNEL */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_GE_COMMON_H */
