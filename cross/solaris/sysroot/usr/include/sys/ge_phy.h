/*
 * Copyright (c) 1992 by Sun Microsystems, Inc.
 */

#ifndef	_SYS_GE_PHY_H
#define	_SYS_GE_PHY_H

#pragma ident	"@(#)ge_phy.h	2.3	02/01/29 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef SOL2_5_1
typedef int int32_t;
typedef unsigned int uintptr_t;
typedef unsigned short uint16_t;
#endif

struct	xcvr_table {
	void	(*check_link_main) ();	/* Main check_link function. */
	uint32_t (*xcvr_read) ();	/* XCVR Register Read Procedure */
	void	(*xcvr_write) ();	/* XCVR Register Write Procedure */
	void	(*xcvr_link_verify) ();	/* XCVR Register Write Procedure */
	void	(*xcvr_reset) ();	/* XCVR Reset Procedure */
	void	(*xcvr_autoneg_link) (); /* Auto Negotitation Procedure */
	void	(*xcvr_manual_link) ();	/* Manual Mode Procedure */
	uint32_t vendor_id;		/* Vendor ID */
	uint16_t device_id;		/* Device Model */
	uint16_t device_rev;		/* Device Revision */
	uint32_t phy_address;		/* PHY Address */
	uint32_t xcvr_status;		/* xcvr status */
	uint32_t xcvr_state;		/* xcvr state */
	uint32_t bringup_mode;		/* Bringup Mode: */
	uint32_t bringup_speed;		/* Bringup Speed */
	uint32_t speed;			/* current speed  */
	uint32_t duplex;			/* xcvr Duplex */
	uint32_t capablity;		/* xcvr capability */
/* These are MII Standard Register Equivalents */
	uint16_t mii_control;		/* MII Standard Control Register */
	uint16_t mii_status;		/* MII Standard Status Register */
	uint16_t mii_anar;		/* MII Standard ANAR Register */
	uint16_t mii_lpanar;		/* MII Standard LP ANAR Register */
};



/*
MII supports a 16-bit register stack of upto 32, addressable through the
MDIO and MDC serial port.
 */
#define	GE_PHY_BMCR	00	/* Basic Mode Control Register */
#define	GE_PHY_BMSR	01	/* Basic Mode Status Register */
#define	GE_PHY_IDR1	02	/* PHY Identifier Register 1 */
#define	GE_PHY_IDR2	03	/* PHY Identifier Register 2 */
#define	GE_PHY_ANAR	04	/* Auto-Negotiation Advertisement Register */
#define	GE_PHY_ANLPAR	05	/* Auto-Negotiation Link Partner Ability Reg */
#define	GE_PHY_ANER	06	/* Auto-Negotiation Expansion Register */

/* Registers 7-15 are reserved for future assignments by MII working group */
/* Do not write to these registers */

/* Registers 16-17 are reserved for future assignment by Vendor */
/* Do not write to these registers */

#define	GE_PHY_DIS	18	/* Disconnect Counter */
#define	GE_PHY_FCSC	19	/* False Carrier Sense Counter */
#define	GE_PHY_NWAYTR	20	/* NWay Test Register */
#define	GE_PHY_REC	21	/* RX_ER Counter */
#define	GE_PHY_SRR	22	/* Silicon Revision Register */
#define	GE_PHY_CSC	23	/* CS Configuration Register */
#define	GE_PHY_LBREMR	24	/* Loopback, Bypass, Receiver Error Mask Reg */
#define	GE_PHY_AR	25	/* PHY Address Register */
#define	GE_PHY_VRES1	26	/* Reserverd for future assignement by vendor */
#define	GE_PHY_TPISR	27	/* 10 Mbps TPI Status Register */
#define	GE_PHY_NICR	28	/* 10 Mbps Network I/F Configuration Register */

/* Registers 29-31 are reserved for future assignment by Vendor */
/* Do not write to these registers */


/* ************************************************************************ */
/*  Register 00	 Basic Mode Control Register */

#define	PHY_BMCR_RESET	(1 << 15)	/* Reset */
#define	PHY_BMCR_LPBK	(1 << 14)	/* Loopback of TXD<3:0> */
#define	PHY_BMCR_100M	(1 << 13)	/* Speed selection, 1=100Mbps */
#define	PHY_BMCR_ANE	(1 << 12)	/* Auto Negotiation Enable */
#define	PHY_BMCR_PWRDN	(1 << 11)	/* Power down */
#define	PHY_BMCR_ISOLATE (1 << 10)	/* Isolate PHY from MII */
#define	PHY_BMCR_RAN	(1 << 9)	/* Restart Auto Negotiation */
#define	PHY_BMCR_FDX	(1 << 8)	/* Full Duplex */
#define	PHY_BMCR_COLTST	(1 << 7)	/* Collision Test */
#define	PHY_BMCR_RES1	(0x7f << 0)	/* 0-6 Reserved */

/* ************************************************************************ */
/* Register 01	 Basic Mode Status Register */

#define	PHY_BMSR_100T4	(1 << 15)	/* PHY able to perform 100Base-T4 */
#define	PHY_BMSR_100FDX	(1 << 14)	/* PHY able to perform 100Base-TX FDX */
#define	PHY_BMSR_100HDX	(1 << 13)	/* PHY able to perform 100Base-TX HDX */
#define	PHY_BMSR_10FDX	(1 << 12)	/* PHY able to perform 10Base-T FDX */
#define	PHY_BMSR_10HDX	(1 << 11)	/* PHY able to perform 10Base-T HDX */
#define	PHY_BMSR_RES1	(0x1f << 6)	/* 6-10 reserved */
#define	PHY_BMSR_ANC	(1 << 5)	/* Auto Negotiation Completed */
#define	PHY_BMSR_REMFLT	(1 << 4)	/* Remote Fault detected */
#define	PHY_BMSR_ACFG	(1 << 3)	/* Able to do Auto Link Negotiation */
#define	PHY_BMSR_LNKSTS	(1 << 2)	/* Link Status */
#define	PHY_BMSR_JABDET	(1 << 1)	/* Jabber Condition Detected */
#define	PHY_BMSR_EXTCAP	(1 << 0)	/* Extended Register Capability */

#define	PHY_CAPABILITY_MASK (PHY_BMSR_100FDX | PHY_BMSR_100HDX \
				| PHY_BMSR_10FDX | PHY_BMSR_10HDX)

/* ************************************************************************ */
/*
 * Registers 2 and 3 provide a 32 bit value which is a unique identifier
 * for a particular type of PHY. A 24-bit Organizationally Unique Identifier
 * (OUI) is defined with bit 1 as the MSB and bit 24 as the LSB. Bits 3-18 of
 * the OUI are found in PHY Identifier Register 1 and bits 19-24 are found in
 * PHY Identifier Register 2.

 * The hexadecimal OUI code for NSC is 0x080017 .
 */
/* Register 02	 PHY Identifier Register 1 */

/* Register 03	 PHY Identifier Register 2 */

#define	PHY_IDR2_OUILSB (0x3f << 10)	/* Bits 19-24 of OUI */
#define	PHY_IDR2_VNDMDL (0x3f << 4)	/* vendor Model no. */
#define	PHY_IDR2_MDLREV (0xf << 0)	/* Model revision no. */

/* ************************************************************************ */
/*
 * Register 04	Auto-Negotiation Advertisement Register (nway1Reg)
 * This register will hold the different modes of operation to be advertised to
 * the far-end PHY.
 */

#define	PHY_ANAR_NP	(1 << 15)	/* Next Page bit */
#define	PHY_ANAR_ACK	(1 << 14)	/* Acks reception of Link Partner */
					/* Capability word  */
#define	PHY_ANAR_RF	(1 << 13)	/* Advertise Remote Fault det. cap. */
#define	PHY_ANAR_RES1	(0x7 << 10)	/* 10-12 reserved */
#define	PHY_ANAR_T4	(1 << 9)	/* Advertise 100Base-T4 Capability */
#define	PHY_ANAR_TXFDX	(1 << 8)	/* Advertise 100Base-TX FDX Cap. */
#define	PHY_ANAR_TX	(1 << 7)	/* Advertise 100Base-TX Cap. */
#define	PHY_ANAR_10FDX	(1 << 6)	/* Advertise 10Base-T FDX Cap. */
#define	PHY_ANAR_10	(1 << 5)	/* Advertise 10Base-T Cap. */
#define	PHY_ANAR_SELECT	(0x1f << 0)	/* Binary Encoded selector supported */
					/* this node. Currently only CSMA/CD */
					/* <00001> is specified  */

#define	PHY_SELECTOR	1	/* Default selector for CSMA/CD */
/*
 * Priority scheme (from highest to lowest) for Auto Link Negotiation:
	1 - 100Base-TX Full Duplex
	2 - 100Base-T4
	3 - 100Base-TX
	4 - 10Base-T Full Duplex
	5 - 10Base-T
 */

/* ************************************************************************ */
/*
 * Register 05	 Auto-Negotiation Link Partner Ability Reg
 * This register contains the Link Partners capabilities after NWay
 * Auto-Negotiation is complete.
 */

#define	PHY_ANLPAR_NP	(1 << 15)	/* Next page Bit */
#define	PHY_ANLPAR_ACK	(1 << 14)	/* Link Partner acks reception of our */
					/* capability data word  */
#define	PHY_ANLPAR_RF	(1 << 13)	/* LP indicates Remote fault */
#define	PHY_ANLPAR_RES1	(0x7 << 10)	/* 10-12 reserved */
#define	PHY_ANLPAR_T4 	(1 << 9)	/* 100Base-T4 supported by LP */
#define	PHY_ANLPAR_TXFDX (1 << 8)	/* 100Base-TX FDX supp. by LP */
#define	PHY_ANLPAR_TX	(1 << 7)	/* 100Base-TX supp. by LP */
#define	PHY_ANLPAR_10FDX (1 << 6)	/* 10Base-T FDX supp. by LP */
#define	PHY_ANLPAR_10	(1 << 5)	/* 10Base-T supp. by LP */
#define	PHY_ANLPAR_SELECT (0x1f << 0)	/* LP's binary encoded node selector */
					/* Currently only CSMA/CD is <00001> */
					/* is specified  */

/* ************************************************************************ */
/*
 * Register 06	 Auto-Negotiation Expansion Register
 * This register contains additional status for NWay Auto-Negotiation
 */

#define	PHY_ANER_RES1	(0x7ff << 5)	/* 5-15 reserved */
#define	PHY_ANER_MLF	(1 << 4)	/* Multiple Link faults occured */
#define	PHY_ANER_LPNP	(1 << 3)	/* LP supports Next Page negotiation */
#define	PHY_ANER_NPABLE	(1 << 2)	/* This node can send additional */
				/* Next Pages. Should be 0 for DP83840  */
#define	PHY_ANER_PAGERX	(1 << 1)	/* new LINK Code Word Page recvd. */
#define	PHY_ANER_LPNW	(1 << 0)	/* LP supports NWay Auto-negotiation */


/* ************************************************************************ */

/* Registers 7-15 are reserved for future assignments by MII working group */
/* Do not write to these registers */

/* DP83840 - 10/100 Mbps Physical layer from National semiconductor */
/* Registers 16-17 are reserved for future assignment by Vendor */
/* Do not write to these registers */

/* ************************************************************************ */

/*
 * Register 18	 Disconnect Counter
 * This 16-bit counter is incremented for every disconnect event. It rolls over
 * when full.
 */

/* ************************************************************************ */
/*
 * Register 19	 False Carrier Sense Counter
 * This 16-bit counter is incremented for each false carrier event (i.e. carrier
 * assertion without JK detect). It freezes when full.
 */

/* ************************************************************************ */
/*
 * Register 20	 NWay Test Register
 */
#define	PHY_NWAYTR_RES1	(0xff << 8)	/* 8-15 reserved */
#define	PHY_NWAYTR_LPBK	(1 << 7)	/* Puts NWay into Loopback mode */
#define	PHY_NWAYTR_RES2	(0x7f << 0)	/* 0-6 reserved */

/* ************************************************************************ */
/*
 * Register 21	 RX_ER Counter
 * This 16-bit counter is incremented once per valid packet (i.e. no collision
 * occured during packet reception), if there is one or more receive error
 * condition during the packet reception. The counter is incremented at the end
 * of the packet reception.
 */

/* ************************************************************************ */
/*
 * Register 22	 Silicon Revision Register
 * Contains information on silicon revision
 * This register will be incremented for any change made to the device.
 */
/* ************************************************************************ */
/*
 * Register 23	 CS Configuration Register
 */

#define	PHY_CSCR_NRZIDIS (1 << 15)	/* NRZI disabled (for FDDI) */
#define	PHY_CSCR_RES1	(1 << 14)	/* reserved */
#define	PHY_CSCR_TOCDIS	(1 << 13)	/* disable Timeout counter */
					/* in descrambler  */
#define	PHY_CSCR_REPTR	(1 << 12)	/* Mode1: Node = 0, repeater = 1 */
#define	PHY_CSCR_ENCSEL	(1 << 11)	/* encoder: 0 = MLT-3, 1 = binary */
#define	PHY_CSCR_RES2	(0x7 << 8)	/* 8-10 reserved */
#define	PHY_CSCR_CLK25M	(1 << 7)	/* Tristates CLK25M */
#define	PHY_CSCR_FLN100	(1 << 6)	/* 0 = force good link in 100Mbps */
#define	PHY_CSCR_FCONN	(1 << 5)	/* 1 = bypass disconnect function */
#define	PHY_CSCR_TXOFF	(1 << 4)	/* 1 = Pulls TD from phaser ckt low */
#define	PHY_CSCR_RES3	(1 << 3)	/* reserved */
#define	PHY_CSCR_CSTSEN	(1 << 2)	/* LED1 pin for connection status */
#define	PHY_CSCR_10FDXE	(1 << 1)	/* LED4 pin for 10Base-T FDX */
#define	PHY_CSCR_RES4	(1 << 0)	/* reserved */

/* ************************************************************************ */
/*
 * Register 24	 Loopback, Bypass, Receiver Error Mask Reg
 * The high byte of this register configures the DP83840 whilst its low byte
 * programs the receive error types to be reported in real time as a HEX code
 * across the MII RXD<3:0> interface.
 */

#define	PHY_LBREMR_BPEB	(1 << 15)	/* Bypass Elasticity buffer */
#define	PHY_LBREMR_BP4B5B (1 << 14)	/* Bypass 4B5B and 5B4B encoder */
#define	PHY_LBREMR_BPSCR (1 << 13)	/* Bypass scrambler/descrambler */
#define	PHY_LBREMR_BPALIGN (1 << 12)	/* Bypass symbol alignment ckt */
#define	PHY_LBREMR_EWRAP (1 << 11)	/* 10Base-T ENDEC Loopback */
#define	PHY_LBREMR_XWRAP (1 << 10)	/* 10Base-T Transceiver loopback */
#define	PHY_LBREMR_LB	(0x3 << 8)	/* Twister and remote loopback */
#define	PHY_LBREMR_RES1	(0x7 << 5)	/* Reserved */
#define	PHY_LBREMR_CODE	(1 << 4)	/* Report det. of Code Error */
#define	PHY_LBREMR_PME	(1 << 3)	/* Report det. of Pre-mature End err */
#define	PHY_LBREMR_LINK	(1 << 2)	/* Report det. of Link Error */
#define	PHY_LBREMR_PKT	(1 << 1)	/* Report det. of Packet error */
#define	PHY_LBREMR_EB	(1 << 0)	/* Report det. of Elasticty buf err */

/* ************************************************************************ */
/*
 * Register 25	 PHY Address Register
 */

#define	PHY_AR_RES1	(0x1ff << 7)	/* reserved */
#define	PHY_AR_SPEED10	(1 << 6)	/* speed : 1 = 10 Mbps, 0 - 100 Mbps */
#define	PHY_AR_CONSTS	(1 << 5)	/* status of the disconnect function */
#define	PHY_AR_ADDR	(0x1f << 0)	/* PHY Address */

/*
 * The PHYAD<4:0> allow 32 unique PHY addresses. The PHYAD<4:0> share the RX_ER,
 * PHYAD3, CRS, ENCSEL ald LBEN pins of the PHY. By patching the PHYAD address
 * pins with a light pull-up or pull-down resistor, the PMD address can be
 * strobed and stored in these register location during Reset or Power-on reset
 * time.

 * The first PHY address bit transmitted or received is the MSB of the address.
 * A PHY connected to a station management entity via an interface connector
 * shall always respond to PHY address < 00000 > . A station management entity
 * connected to multiple PHY entities must know the appropriate PHY address of
 * each PHY entity. PHY address should be set to < 00001 > for a single
 * PHY entity. A PHY address of < 00000 > will cause the Isolate bit 0: < 10 >
 * to be set to one.
 */

/* ************************************************************************ */
/*
 * Register 26	 Reserverd for future assignement by vendor
 */

/* ************************************************************************ */
/*
 * Register 27	 10 Mbps TPI Status Register
 */

#define	PHY_TPISR_RES1	(0x3f << 10)	/* reserved */
#define	PHY_TPISR_10BTSER (1 << 9)	/* 10BASE-T Serial mode */
#define	PHY_TPISR_RES2	(0x1ff << 0)	/* reserved */

/* ************************************************************************ */
/*
 * Register 28	 10 Mbps Network I/F Configuration Register
 */

#define	PHY_NICR_RES1	(0x3ff << 6)	/* reserved */
#define	PHY_NICR_LD	(1 << 5)	/* Link disable */
#define	PHY_NICR_HBE	(1 << 4)	/* Enable Heart beat function */
#define	PHY_NICR_UTP	(1 << 3)	/* 1 = UTP, 0 = STP */
#define	PHY_NICR_LSS	(1 << 2)	/* Low Squelch select */
#define	PHY_NICR_RES2	(1 << 1)	/* reserved */
#define	PHY_NICR_JBEN	(1 << 0)	/* Enables Jabber function  in FDX */
					/* or xwrap mode  */

/* ************************************************************************ */

/* Registers 29-31 are reserved for future assignment by Vendor */
/* Do not write to these registers */

/* ************************************************************************ */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_GE_PHY_H */