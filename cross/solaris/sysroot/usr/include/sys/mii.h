/*
 * Copyright (c) 2002 by Sun Microsystems, Inc.
 * All rights reserved.
 */
#pragma ident	"@(#)mii.h 1.10	03/11/11 SMI"

#ifndef _MII_H_
#define _MII_H_

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Configuration Register space.
 */
typedef struct _mii_regs_t {
	uchar_t bmcr;		/* Basic mode control register */
	uchar_t bmsr;		/* Basic mode status register */
	uchar_t idr1;		/* Phy identifier register 1 */
	uchar_t idr2;		/* Phy identifier register 2 */
	uchar_t anar;		/* Auto-Negotiation advertisement register */
	uchar_t anlpar;		/* Auto-Negotiation link Partner ability reg */
	uchar_t aner;		/* Auto-Negotiation expansion register */
	uchar_t mii_res0[2];
	uchar_t gcr;		/* Gigabit basic mode control register. */
	uchar_t gsr;		/* Gigabit basic mode status register */
	uchar_t mii_res1[4];	/* For future use by MII working group */
	uchar_t esr;		/* Extended status register. */
	uchar_t vendor_res[16];	/* For future use by Phy Vendors */
} mii_regs_t, *p_mii_regs_t;

/*
 * MII Register 0: Basic mode control register.
 */
typedef union _mii_bmcr_t {
	uint16_t value;
	struct {
#ifdef _BIT_FIELDS_HTOL
		uint16_t reset:1;
		uint16_t loopback:1;
		uint16_t speed_sel:1;
		uint16_t enable_autoneg:1;
		uint16_t power_down:1;
		uint16_t isolate:1;
		uint16_t restart_autoneg:1;
		uint16_t duplex_mode:1;
		uint16_t col_test:1;
		uint16_t speed_1000_sel:1;
		uint16_t res1:6;
#else
		uint16_t res1:6;
		uint16_t speed_1000_sel:1;
		uint16_t col_test:1;
		uint16_t duplex_mode:1;
		uint16_t restart_autoneg:1;
		uint16_t isolate:1;
		uint16_t power_down:1;
		uint16_t enable_autoneg:1;
		uint16_t speed_sel:1;
		uint16_t loopback:1;
		uint16_t reset:1;
#endif
	} bits;
} mii_bmcr_t, *p_mii_bmcr_t;

/*
 * MII Register 1:  Basic mode status register.
 */
typedef union _mii_bmsr_t {
	uint16_t value;
	struct {
#ifdef _BIT_FIELDS_HTOL
		uint16_t link_100T4:1;
		uint16_t link_100fdx:1;
		uint16_t link_100hdx:1;
		uint16_t link_10fdx:1;
		uint16_t link_10hdx:1;
		uint16_t res2:2;
		uint16_t extend_status:1;
		uint16_t res1:1;
		uint16_t preamble_supress:1;
		uint16_t auto_neg_complete:1;
		uint16_t remote_fault:1;
		uint16_t auto_neg_able:1;
		uint16_t link_status:1;
		uint16_t jabber_detect:1;
		uint16_t ext_cap:1;
#else
		uint16_t ext_cap:1;
		uint16_t jabber_detect:1;
		uint16_t link_status:1;
		uint16_t auto_neg_able:1;
		uint16_t remote_fault:1;
		uint16_t auto_neg_complete:1;
		uint16_t preamble_supress:1;
		uint16_t res1:1;
		uint16_t extend_status:1;
		uint16_t res2:2;
		uint16_t link_10hdx:1;
		uint16_t link_10fdx:1;
		uint16_t link_100hdx:1;
		uint16_t link_100fdx:1;
		uint16_t link_100T4:1;
#endif
	} bits;
} mii_bmsr_t, *p_mii_bmsr_t;

/*
 * MII Register 2: Physical Identifier 1.
 */
typedef union _mii_idr1_t {
        uint16_t value;
        struct {
		uint16_t ieee_address:16;
	} bits;
} mii_idr1_t, *p_mii_idr1_t;

/*
 * MII Register 3: Physical Identifier 2.
 */
typedef union _mii_idr2_t {
        uint16_t value;
        struct {
#ifdef _BIT_FIELDS_HTOL
		uint16_t ieee_address:4;
		uint16_t model_no:4;
		uint16_t rev_no:4;
#else
		uint16_t rev_no:4;
		uint16_t model_no:4;
		uint16_t ieee_address:4;
#endif
	} bits;
} mii_idr2_t, *p_mii_idr2_t; 

/*
 * MII Register 4: Auto-negotiation advertisement register.
 */
typedef union _mii_anar_t {
	uint16_t value;
	struct {
#ifdef _BIT_FIELDS_HTOL
		uint16_t np_indication:1;
		uint16_t acknowledge:1;
		uint16_t remote_fault:1;
		uint16_t res1:1;
		uint16_t cap_asmpause:1;
		uint16_t cap_pause:1;
		uint16_t cap_100T4:1;
		uint16_t cap_100fdx:1;
		uint16_t cap_100hdx:1;
		uint16_t cap_10fdx:1;
		uint16_t cap_10hdx:1;
		uint16_t selector:5;
#else
		uint16_t selector:5;
		uint16_t cap_10hdx:1;
		uint16_t cap_10fdx:1;
		uint16_t cap_100hdx:1;
		uint16_t cap_100fdx:1;
		uint16_t cap_100T4:1;
		uint16_t cap_pause:1;
		uint16_t cap_asmpause:1;
		uint16_t res1:1;
		uint16_t remote_fault:1;
		uint16_t acknowledge:1;
		uint16_t np_indication:1;
#endif
	} bits;
} mii_anar_t, *p_mii_anar_t;

/*
 * MII Register 5: Auto-negotiation link partner advertisement register.
 */
typedef mii_anar_t mii_anlpar_t, *p_mii_anlpar_t;

/*
 * MII Register 6: Auto-negotiation expansion register.
 */
typedef union _mii_aner_t {
	uint16_t value;
	struct {
#ifdef _BIT_FIELDS_HTOL
		uint16_t res:11;
		uint16_t mlf:1;
		uint16_t lp_np_able:1;
		uint16_t np_able:1;
		uint16_t page_rx:1;
		uint16_t lp_an_able:1;
#else
		uint16_t lp_an_able:1;
		uint16_t page_rx:1;
		uint16_t np_able:1;
		uint16_t lp_np_able:1;
		uint16_t mlf:1;
		uint16_t res:11;
#endif
	} bits;
} mii_aner_t, *p_mii_aner_t;

/*
 * MII Register 9: 1000BaseT control register.
 */
typedef union _mii_gcr_t {
	uint16_t value;
	struct {
#ifdef _BIT_FIELDS_HTOL
		uint16_t test_mode:3;
		uint16_t ms_mode_en:1;
		uint16_t master:1;
		uint16_t dte_or_repeater:1;
		uint16_t link_1000fdx:1;
		uint16_t link_1000hdx:1;
		uint16_t res:8;
#else
		uint16_t res:8;
		uint16_t link_1000hdx:1;
		uint16_t link_1000fdx:1;
		uint16_t dte_or_repeater:1;
		uint16_t master:1;
		uint16_t ms_mode_en:1;
		uint16_t test_mode:3;
#endif
	} bits;
} mii_gcr_t, *p_mii_gcr_t;

/*
 * MII Register 10: 1000BaseT status register.
 */
typedef union _mii_gsr_t {
	uint16_t value;
	struct {
#ifdef _BIT_FIELDS_HTOL
		uint16_t ms_config_fault:1;
		uint16_t ms_resolve:1;
		uint16_t local_rx_status:1;
		uint16_t remote_rx_status:1;
		uint16_t link_1000fdx:1;
		uint16_t link_1000hdx:1;
		uint16_t asm_dir:1;
		uint16_t res:1;
		uint16_t idle_err_cnt:8;
#else
		uint16_t idle_err_cnt:8;
		uint16_t res:1;
		uint16_t asm_dir:1;
		uint16_t link_1000hdx:1;
		uint16_t link_1000fdx:1;
		uint16_t remote_rx_status:1;
		uint16_t local_rx_status:1;
		uint16_t ms_resolve:1;
		uint16_t ms_config_fault:1;
#endif
	} bits;
} mii_gsr_t, *p_mii_gsr_t;

/*
 * MII Register 15: Extended status register.
 */
typedef union _mii_esr_t {
	uint16_t value;
	struct {
#ifdef _BIT_FIELDS_HTOL
		uint16_t link_1000Xfdx:1;
		uint16_t link_1000Xhdx:1;
		uint16_t link_1000fdx:1;
		uint16_t link_1000hdx:1;
		uint16_t res:12;
#else
		uint16_t res:12;
		uint16_t link_1000hdx:1;
		uint16_t link_1000fdx:1;
		uint16_t link_1000Xhdx:1;
		uint16_t link_1000Xfdx:1;
#endif
	} bits;
} mii_esr_t, *p_mii_esr_t;

#define BROADCOM_PHY_5411 0x00206071
#define BROADCOM_PHY_B0	0x00206050
#define LUCENT_PHY_B0	0x00437421
#define	NSC_DP83065	0x20005c78

#ifdef __cplusplus
}
#endif

#endif
