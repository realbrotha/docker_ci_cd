/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernel/sys/fcparray.h 1.25                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1998,2008              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)10        1.25  src/bos/kernel/sys/fcparray.h, sysxarray, bos53Q, q2008_10A8 2/27/08 21:50:16 */
#ifndef _H_FCPARRAY
#define _H_FCPARRAY
/*
 * COMPONENT_NAME: SYSXARRAY 
 *
 * FUNCTIONS:  NONE
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1993, 1994
 *
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/************************************************************************/
/* fcparray.h header dependencies                                         */
/************************************************************************/

#include <sys/types.h>
#include <sys/scsi.h>
#include <sys/scsi.h>
#include <sys/scsi_buf.h>

#define DK_SCSI_STRING_SZ         256      /* Size of SCSI string in bytes */

/* Hardware-related constants */
#define MAX_CHANNELS	0x06	/* Maximum supported channels, 1-n */
#define MAX_IDS		0x0f	/* Highest SCSI id per channel */
#define MAX_DRIVES	84	/* Maximum # drives per subsystem */

/* SCSI Disk Ioctls */
#define DKIOLRDSE	0x10	/* Read and return sense data on error  */
#define DKIOLWRSE	0x11	/* Write and return sense data on error */
#define DKIOLCMD	0x12	/* Issue a user-defined SCSI command    */

#define DK_PASSTHRU          0x17     /* Issue user-defined SCSI      */
                                      /* command with argument of     */
                                      /* struct sc_passthru defined   */
                                      /* scsi.h                       */

#define DKPRES_READKEYS		0x19    /* Persistent Reserve In command*/ 
					/* read keys service action	*/ 
#define DKPRES_READRES		0x1a	/* Persistent Reserve In command*/
					/* read reservations ser action */
#define DKPRES_CLEAR		0x1b	/* Persistent ReserveOut command*/
					/* with clear service action    */
#define DKPRES_PREEMPT		0x1c	/* Persistent ReserveOut command*/
					/* with preempt service action  */
#define DKPRES_PREEMPT_ABORT	0x1d	/* Persistent ReserveOut command*/ 
					/* with preempt and abort 	*/
					/* service action		*/
#define DKPRES_REGISTER         0x1e    /* Persistent ReserveOut command*/
                                        /* with Register & Ignore exist */
                                        /* ing key service action.      */

#define DKIOLCMD_RS	0x52	/* Issue a user-defined SCSI command    */
#define DKIOLCMD2       0x53    /* Issue user-defined SCSI command with */
                                /* automatic request sense.             */
#define DKIOLCMD2_NQ    0x58    /* Issue user-defined SCSI command with */
                                /* automatic request sense. Do not      */
				/* quiesce the target LUN.              */
#define DKIOLCMD_PT     0x54	/* Issue user-defined SCSI command with */
				/* automatic request sense for pass	*/
				/* through.				*/
#define DKIOLCMD_PT2    0x55    /* Issue user-defined SCSI command with */
				/* automatic request sense for pass	*/
				/* through.				*/
#define DKDRVGROUP      0x56	/* Issue command to set a drive group   */
                                /* automatic request sense for pass     */
                                /* through.                             */
#define DKRESETCTRL	0x57	/* Reset the specified controller or the */
	       			/* controller of the specified hdisk    */
#define DKBITMAPID	0x59	/* Returns the bitmap id (0 or 1) of the */					/* addressed unit within its dar. The	*/					/* value is returned in arg, which should */					/* be a pointer to a char 		*/
#define DKFORMATPEND	0x5a	/* Returns the number of pending formats */
				/* on the addressed unit (usually a dac).*/
				/* The value is returned in arg, which   */
				/* should be a pointer to a char.	 */
#define DKIOLCMD_UPT     0x5B	/* Issue user-defined SCSI command with */
				/* automatic request sense for unsafe	*/
				/* pass through.			*/

/* Router specific Ioctls */
#define RT_GET_ROUTER_INFO			0x100
#define RT_GET_EXTENDED_ROUTER_INFO		0x101
#define RT_GET_VERSION				0x102
#define RT_GET_ADAPTER_LIST			0x103
#define RT_ADD_PATH				0x104
#define RT_GET_ROUTER_STATE			0x105
#define RT_SET_ROUTER_STATE			0x106
#define RT_FAIL_ADAPTER				0x107
#define RT_FAIL_CONTROLLER			0x108
#define RT_RESTORE_ADAPTER			0x109
#define RT_RESTORE_CONTROLLER			0x10a
#define RT_PREVENT_SWITCHING			0x10b
#define RT_ALLOW_SWITCHING			0x10c
#define RT_START_MONITOR			0x10d
#define RT_GET_DACS				0x10e


/* New errno values */
#define EDRV                    160
#define EICON                   161

/* handy stuff for interpreting SCSI data */
struct scsi_short {
    unsigned char hi;
    unsigned char lo;
};
struct scsi_long {
    unsigned char hi;
    unsigned char mhi;
    unsigned char mlo;
    unsigned char lo;
};

#define FROM_SCSI_SHORT(x)      (((x).hi << 8) + ((x).lo))
#define FROM_SCSI_LONG(x)      (((x).hi << 24) + ((x).mhi << 16) + ((x).mlo << 8) + ((x).lo))

/************************************************************************/
/* Mode Select page information				                */
/************************************************************************/

/* header returned from a 10-byte MODE SENSE */
struct scsi_10byte_mode_header {
    struct scsi_short   data_length;
    unsigned char       medium_type;
    unsigned char       device_specific;
    unsigned char       reserved[2];
    struct scsi_short   block_desc_length;
};

/* Page 0x2a */
struct array_physical_page {
    unsigned char       page_code;
    unsigned char       page_length;
    unsigned char	drive_status[16][15];
};

/* Page 0x2b */
struct logical_array_page {
    unsigned char       page_code;
    unsigned char       page_length;
    unsigned char       lun_status;
    unsigned char       raid_level;
    unsigned char       lun_type;
    struct scsi_long    lun_blocksize;
    struct scsi_short   drive_sector_size;
    struct scsi_long    num_of_blocks;
    struct scsi_long    avail_capacity;
    struct scsi_long    segment_size;
    unsigned char       segment0_size;
    struct scsi_short   lun_flags;
    struct scsi_long    recon_block_completed;
    unsigned char       recon_frequency;
    struct scsi_short   recon_amount;
    unsigned char       reserved[3];
    unsigned char       disk_bit_map[32];
    unsigned char       config_table[64];
};

/* Page 0x2c, subpage 0x00 - base page (legacy - pre 256/1024 lun support) */
struct redundant_controller_page {
    unsigned char       page_code;
    unsigned char       page_length;
    unsigned char       primary_id[16];
    unsigned char       alternate_id[16];
    unsigned char       alt_present1;
    unsigned char       primary_mode;
    unsigned char       alt_present2;
    unsigned char       alternate_mode;
    unsigned char	quiescence_timeout;
    unsigned char	rdac_options;	
    unsigned char       lun_table[64];
    unsigned char       reserved2[2];
};

/* Page 0x2c, subpage 0x01 */
struct redundant_controller_subpage1 {
    unsigned char       page_code;
    unsigned char       subpage_code;
    struct scsi_short	page_length;
    unsigned char       primary_id[16];
    unsigned char       alternate_id[16];
    unsigned char       alt_present1;
    unsigned char       primary_mode;
    unsigned char       alt_present2;
    unsigned char       alternate_mode;
    unsigned char	quiescence_timeout;
    unsigned char	rdac_options;	
    unsigned char       lun_table[256];
    unsigned char       reserved2[2];
};

#define	PAGECODE_IDX		0

#define	ALTPRES1_IDX_SUB0	34
#define	PRIME_MODE_IDX_SUB0	35
#define	ALTPRES2_IDX_SUB0	36
#define	ALT_MODE_IDX_SUB0	37
#define	QUIESCE_IDX_SUB0	38
#define	RDAC_IDX_SUB0		39
#define LUNTBL_IDX_SUB0 	40

#define	ALTPRES1_IDX_SUB1	36
#define	PRIME_MODE_IDX_SUB1	37
#define	ALTPRES2_IDX_SUB1	38
#define	ALT_MODE_IDX_SUB1	39
#define	QUIESCE_IDX_SUB1	40
#define	RDAC_IDX_SUB1		41
#define LUNTBL_IDX_SUB1		42

/************************************************************************/
/*                Pages 0x2e and 0x8 used for fast write                */
/************************************************************************/
/* Page 0x2e */
struct vendor_unique_cache_page {
    unsigned char	page_code;
    unsigned char	page_length;
    unsigned reserved1	: 5;
    unsigned cwob		: 1;    /* allow cache without batteries */
    unsigned fwt		: 1;    /* force write through on two    */
    			                /*     minute warning from ups   */
    unsigned cme		: 1;	/* cache mirror enable           */
    unsigned abpr		: 1;	/* alternate controller          */
					/*     batteries present         */
    unsigned bpr		: 1;	/* bateries present              */
    unsigned acma		: 1;	/* alternate controller cache    */
					/*     mirroring active          */
    unsigned cma		: 1;	/* cache mirroring active        */
    unsigned abok		: 1;	/* alternate controller          */
					/*     batteries OK              */
    unsigned bok		: 1;	/* batteries OK                  */
    unsigned rca		: 1;	/* read cache active             */
    unsigned wca		: 1;	/* write cache active            */
    unsigned reserved2		:16;
    unsigned char	read_caching_algo; /* read caching algorithm     */
    unsigned char	reserved3;
    unsigned char	write_caching_algo;/* write caching algorithm    */
    unsigned char	reserved4;
    unsigned cache_flush_algo :8 ;         /* cache flush algorithm      */
    unsigned reserved5		: 4;
    unsigned cache_flush_modifier	: 4;
    unsigned tmw_flush_algo : 8;	/* two minute warning flush      */
					/*     algorithm                 */
    unsigned reserved6	: 4;
    unsigned tmw_flush_mod : 4;		/* two minute warning flush      */
					/*     modifier                  */
    struct scsi_short	reserved7;
    unsigned char	demand_flush_thresh; /* demand flush threshhold  */
    unsigned char	demand_flush_amt;    /* demand flush amount      */
    struct scsi_long	reserved8;
    struct scsi_short	cache_size_mbs;      /* cache size (MB)          */
    struct scsi_short	cache_size_blks;     /* cache size (blocks)      */
    struct scsi_short	large_io_size;       /* large I/O size           */
    unsigned char	cache_mirror_aloc_size; /* cache mirror          */
						/*    allocation size    */
    unsigned char	reserved9[35];
};

/* Page 0x8 */
struct caching_page {
    unsigned page_code :8;
    unsigned page_length :8;
    unsigned reserved	: 5;	/* reserved bits */
    unsigned wce		: 1;	/* write cache enabled bit       */
    unsigned mf			: 1;	/* multiplication factor bit     */
    unsigned rcd		: 1;	/* read cache disabled bit       */
    unsigned dmd_read_ret_prior	: 4;	/* demand read retention priority*/
    unsigned write_ret_prior	: 4;	/* write retention priority      */
    struct scsi_short	disbl_prefetch_trans_lenght;
    struct scsi_short	min_prefetch;
    struct scsi_short	max_prefetch;
    struct scsi_short	max_prefetch_ceiling;
};

/************************************************************************/
/* Information on routers                                               */
/************************************************************************/
struct path_desc {
	uchar		ctrl_num;	/* Will be 0 or 1		*/
        dev32_t         adapter_devno;  /* devno of the SCSI adapter    */
                                        /* device on this path.         */
        dev32_t         ctrl_devno;     /* devno of the controller      */
                                        /* device on this path.         */
#if defined(__ia64) && !defined(__64BIT__)
        uchar pad[4];           /* Padding for IA64 ILP32 mode */
#endif
        unsigned long long ctrl_scsi_id;/* SCSI id of the controller on */
                                        /* this path.                   */
        char            ctrl_name[8];   /* Name of the controller on    */
                                        /* this path.                   */
	uint		max_luns;      	/* max # luns for this router   */
};

struct router_ioctl_state {
        uchar           state;          /* State desired: Dual Active,  */
                                        /* Active/Passive, etc.         */
#define DUAL_ACTIVE             0x00
#define ACTIVE_PASSIVE          0x01
#define ACTIVE_RESET            0x02
#define ACTIVE_NONE		0x03
#define PASSIVE_ACTIVE          0x10
#define RESET_ACTIVE            0x20
#define NONE_ACTIVE		0x30

#define CTRL0_MASK              0xf0
#define CTRL1_MASK              0x0f
					/* Note these are not the same as  */
					/* the mode 2C values		   */
#define CTRL_NONE		0x3	/* the controller is not present   */
					/* or we didn't see it at cfg time */
#define CTRL_IN_RESET           0x2	/* Held in Reset or failed 	   */
#define CTRL_PASSIVE            0x1	/* Passive or in service mode      */
#define CTRL_ACTIVE             0x0     /* Active 			   */

        uint            hlthchk_freq;   /* Intervals between health-    */
                                        /* checks, in seconds           */
        uint            aen_freq;       /* Intervals between aen        */
                                        /* polling, in seconds          */
        uint            balance_freq;   /* Intervals between load       */
                                        /* balancing, in seconds        */
        uint            lun_ownership;  /* Bitmap of LUN ownership      */
                                        /* desired. Bit 0 is for LUN 0, */
                                        /* etc. A zero means the LUN is */
                                        /* assigned to the even SCSI id */
                                        /* controller.                  */
        uchar           load_balancing; /* TRUE if router will do dyna- */
                                        /* mic load balancing.          */
	uchar           autorecover;    /* TRUE if router will auto-    */
					/* recover failed paths         */
	uchar		failover_retries;/* number of times to retry a  */
					/* failing failover		*/
        struct path_desc ctrl_path[2];  /* Path for each controller in  */
                                        /* this router.                 */
};

/************************************************************************/
/* scsi_iocmd_pt structure for DKIOCMD_PTRS                             */
/************************************************************************/
struct scsi_iocmd_pt {
        ushort version;              /* The version number of this      */
                                     /* structure.  This allows the     */
                                     /* structure to expand in the      */
                                     /* future.                         */


        uint   data_length;          /* Bytes of data to be transfered  */
        char   *buffer;              /* Pointer to transfer data buffer */
        uint   timeout_value;        /* In seconds                      */
        uchar  status_validity;      /* 0 = no valid status             */

        /* 1 = valid SCSI bus status only       */
        /* 2 = valid adapter status only        */

        uchar  scsi_bus_status;      /* SCSI bus status (if valid)      */
        uchar  adapter_status;       /* Adapter status (if valid), refer*/
                                     /* to scsi_buf definition          */
        uchar  adap_set_flags;       /* These flags are set by the SCSI */
                                     /* adapter driver when a command is*/
                                     /* returned. See scsi_buf          */
                                     /* for valid values                */

        uchar  add_device_status;    /* Additional device status.       */
                                     /* For FCP devices, this field     */
                                     /* contains the FCP response code. */

        uchar  adap_q_status;        /* used to return back whether or  */
                                     /* or not the SCSI adapter driver  */
                                     /* and SCSI adapter cleared their  */
                                     /* queue for this device or not.   */
                                     /* A value of zero implies that    */
                                     /* the device's queue at the       */
                                     /* adapter is cleared.             */
                                     /* A value of SCSI_DID_NOT_CLEAR_Q,*/
                                     /* defined in scsi_buf, implies that*/
                                     /* the device's queue at the       */
                                     /* adapter has not be cleared.     */
        uchar  q_tag_msg;            /* Used to pass down Queue Tag     */
                                     /* message fields of SCSI_NO_Q,    */
                                     /* SCSI_SIMPLE, SCSI_HEAD_OF_Q,    */
                                     /* SCSI_ORDERED_Q, or SCSI_ACA_Q,  */
                                     /* defined above in scsi_buf's     */
                                     /* definition.                     */
        uchar  flags;                /* SCSI_NODISC, SCSI_ASYNC, B_READ,*/
                                     /* B_WRITE                         */
        uchar  q_flags;              /* Used to tell the SCSI adapter   */
                                     /* driver, and SCSI adapter whether*/
                                     /* or not it should clear or resume*/
                                     /* its queue. This is done via the */
                                     /* defines SCSI_Q_CLR, SCSI_Q_RESUME,*/
                                     /* or SCSI_CLEAR_ACA defined above */
                                     /* in scsi_buf.                    */

        ushort autosense_length;     /* This specifies the maximum size */
                                     /* in bytes of the SCSI heads auto-*/
                                     /* sense buffer referenced by the  */
                                     /* autosense_buffer_ptr field.     */

        uchar  command_length;       /* Length of SCSI command block    */
        uchar  scsi_cdb[16];         /* SCSI command descriptor block   */


        char   *autosense_buffer_ptr;/* A pointer to the SCSI head's    */
                                     /* autosense buffer for this SCSI  */
                                     /* command.                        */
                                     /* NOTE: if this is NULL and the   */
                                     /* SCSI device returns autosense,  */
                                     /* then the adapter driver will    */
                                     /* throw away the autosense data.  */

#if defined(__ia64) && !defined(__64BIT__)
        uchar pad0[4];           /* Padding for IA64 ILP32 mode */
#endif
        unsigned long long  scsi_id; /* This is the 64-bit SCSI ID for  */
                                     /* the device.                     */

        unsigned long long  lun_id;  /* This is the 64-bit lun ID for   */
                                     /* the device.                     */
	uchar	passthru_status;	/* Status of this command	*/
#define NO_ERR			0x00
#define ERR_ON_PASS_MODE	0x01
#define ERR_ON_CMD		0x02
	uchar	passthru_direction;	/* Direction bits for the Set	*/
					/* Pass Thru Mode command. 	*/
#define NO_DATA_TRANSFER	0x01
#define INITIATOR_TO_TARGET	0x02
#define TARGET_TO_INITIATOR	0x03
	uchar	dest_channel;		/* The channel number to select	*/
					/* the drive			*/
	uchar	dest_scsi_id;		/* The SCSI id to select the	*/
					/* drive.			*/
#if defined(__ia64) && !defined(__64BIT__)
        uchar pad1[4];           /* Padding for IA64 ILP32 mode */
#endif
};
/************************************************************************/
/* scsi_get_dacs structure for RT_GET_DACS                              */
/************************************************************************/
struct scsi_get_dacs {
        ushort version;              /* The version number of this      */
                                     /* structure.  This allows the     */
                                     /* structure to expand in the      */
                                     /* future.                         */
#define DK_GET_DACS_VERSION0	0
       unsigned long long  lun_id;   /* This is the 64-bit lun ID for   */
                                     /* the device.                     */
        char  	cur_ctrl_name[8];    /* Name of the current controller  */
        char    alt_ctrl_name[8];    /* Name of the alternate controller*/
};

#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Pass-through Ioctl Structure used internally by device driver 
 * to support 64-bit applications
 */
struct scsi_iocmd_pt64 {
        ushort version;              /* The version number of this      */
                                     /* structure.  This allows the     */
                                     /* structure to expand in the      */
                                     /* future.                         */


        uint   data_length;          /* Bytes of data to be transfered  */
        ptr64  buffer;               /* Pointer to transfer data buffer */
        uint   timeout_value;        /* In seconds                      */
        uchar  status_validity;      /* 0 = no valid status             */

        /* 1 = valid SCSI bus status only       */
        /* 2 = valid adapter status only        */

        uchar  scsi_bus_status;      /* SCSI bus status (if valid)      */
        uchar  adapter_status;       /* Adapter status (if valid), refer*/
                                     /* to scsi_buf definition          */
        uchar  adap_set_flags;       /* These flags are set by the SCSI */
                                     /* adapter driver when a command is*/
                                     /* returned. See scsi_buf          */
                                     /* for valid values                */

        uchar  add_device_status;    /* Additional device status.       */
                                     /* For FCP devices, this field     */
                                     /* contains the FCP response code. */

        uchar  adap_q_status;        /* used to return back whether or  */
                                     /* or not the SCSI adapter driver  */
                                     /* and SCSI adapter cleared their  */
                                     /* queue for this device or not.   */
                                     /* A value of zero implies that    */
                                     /* the device's queue at the       */
                                     /* adapter is cleared.             */
                                     /* A value of SCSI_DID_NOT_CLEAR_Q,*/
                                     /* defined in scsi_buf, implies that*/
                                     /* the device's queue at the       */
                                     /* adapter has not be cleared.     */
        uchar  q_tag_msg;            /* Used to pass down Queue Tag     */
                                     /* message fields of SCSI_NO_Q,    */
                                     /* SCSI_SIMPLE, SCSI_HEAD_OF_Q,    */
                                     /* SCSI_ORDERED_Q, or SCSI_ACA_Q,  */
                                     /* defined above in scsi_buf's     */
                                     /* definition.                     */
        uchar  flags;                /* SCSI_NODISC, SCSI_ASYNC, B_READ,*/
                                     /* B_WRITE                         */
        uchar  q_flags;              /* Used to tell the SCSI adapter   */
                                     /* driver, and SCSI adapter whether*/
                                     /* or not it should clear or resume*/
                                     /* its queue. This is done via the */
                                     /* defines SCSI_Q_CLR, SCSI_Q_RESUME,*/
                                     /* or SCSI_CLEAR_ACA defined above */
                                     /* in scsi_buf.                    */

        ushort autosense_length;     /* This specifies the maximum size */
                                     /* in bytes of the SCSI heads auto-*/
                                     /* sense buffer referenced by the  */
                                     /* autosense_buffer_ptr field.     */

        uchar  command_length;       /* Length of SCSI command block    */
        uchar  scsi_cdb[16];         /* SCSI command descriptor block   */


        ptr64  autosense_buffer_ptr; /* A pointer to the SCSI head's    */
                                     /* autosense buffer for this SCSI  */
                                     /* command.                        */
                                     /* NOTE: if this is NULL and the   */
                                     /* SCSI device returns autosense,  */
                                     /* then the adapter driver will    */
                                     /* throw away the autosense data.  */

        unsigned long long  scsi_id; /* This is the 64-bit SCSI ID for  */
                                     /* the device.                     */

        unsigned long long  lun_id;  /* This is the 64-bit lun ID for   */
                                     /* the device.                     */
	uchar	passthru_status;	/* Status of this command	*/
	uchar	passthru_direction;	/* Direction bits for the Set	*/
					/* Pass Thru Mode command. 	*/
	uchar	dest_channel;		/* The channel number to select	*/
					/* the drive			*/
	uchar	dest_scsi_id;		/* The SCSI id to select the	*/
					/* drive.			*/
};

struct scsi_iocmd_pt32 {
        ushort version;              /* The version number of this      */
                                     /* structure.  This allows the     */
                                     /* structure to expand in the      */
                                     /* future.                         */


        uint   data_length;          /* Bytes of data to be transfered  */
        ptr32  buffer;               /* Pointer to transfer data buffer */
        uint   timeout_value;        /* In seconds                      */
        uchar  status_validity;      /* 0 = no valid status             */

        /* 1 = valid SCSI bus status only       */
        /* 2 = valid adapter status only        */

        uchar  scsi_bus_status;      /* SCSI bus status (if valid)      */
        uchar  adapter_status;       /* Adapter status (if valid), refer*/
                                     /* to scsi_buf definition          */
        uchar  adap_set_flags;       /* These flags are set by the SCSI */
                                     /* adapter driver when a command is*/
                                     /* returned. See scsi_buf          */
                                     /* for valid values                */

        uchar  add_device_status;    /* Additional device status.       */
                                     /* For FCP devices, this field     */
                                     /* contains the FCP response code. */

        uchar  adap_q_status;        /* used to return back whether or  */
                                     /* or not the SCSI adapter driver  */
                                     /* and SCSI adapter cleared their  */
                                     /* queue for this device or not.   */
                                     /* A value of zero implies that    */
                                     /* the device's queue at the       */
                                     /* adapter is cleared.             */
                                     /* A value of SCSI_DID_NOT_CLEAR_Q,*/
                                     /* defined in scsi_buf, implies that*/
                                     /* the device's queue at the       */
                                     /* adapter has not be cleared.     */
        uchar  q_tag_msg;            /* Used to pass down Queue Tag     */
                                     /* message fields of SCSI_NO_Q,    */
                                     /* SCSI_SIMPLE, SCSI_HEAD_OF_Q,    */
                                     /* SCSI_ORDERED_Q, or SCSI_ACA_Q,  */
                                     /* defined above in scsi_buf's     */
                                     /* definition.                     */
        uchar  flags;                /* SCSI_NODISC, SCSI_ASYNC, B_READ,*/
                                     /* B_WRITE                         */
        uchar  q_flags;              /* Used to tell the SCSI adapter   */
                                     /* driver, and SCSI adapter whether*/
                                     /* or not it should clear or resume*/
                                     /* its queue. This is done via the */
                                     /* defines SCSI_Q_CLR, SCSI_Q_RESUME,*/
                                     /* or SCSI_CLEAR_ACA defined above */
                                     /* in scsi_buf.                    */

        ushort autosense_length;     /* This specifies the maximum size */
                                     /* in bytes of the SCSI heads auto-*/
                                     /* sense buffer referenced by the  */
                                     /* autosense_buffer_ptr field.     */

        uchar  command_length;       /* Length of SCSI command block    */
        uchar  scsi_cdb[16];         /* SCSI command descriptor block   */


        ptr32  autosense_buffer_ptr; /* A pointer to the SCSI head's    */
                                     /* autosense buffer for this SCSI  */
                                     /* command.                        */
                                     /* NOTE: if this is NULL and the   */
                                     /* SCSI device returns autosense,  */
                                     /* then the adapter driver will    */
                                     /* throw away the autosense data.  */

#if defined(__ia64) && !defined(__64BIT__)
        uchar pad0[4];               /* Padding for IA64 ILP32 mode     */
#endif

        unsigned long long  scsi_id; /* This is the 64-bit SCSI ID for  */
                                     /* the device.                     */

        unsigned long long  lun_id;  /* This is the 64-bit lun ID for   */
                                     /* the device.                     */
	uchar	passthru_status;	/* Status of this command	*/
	uchar	passthru_direction;	/* Direction bits for the Set	*/
					/* Pass Thru Mode command. 	*/
	uchar	dest_channel;		/* The channel number to select	*/
					/* the drive			*/
	uchar	dest_scsi_id;		/* The SCSI id to select the	*/
					/* drive.			*/
};
#endif

/************************************************************************/
/* Initialization information on individual arrays                       */
/************************************************************************/
struct array_ddi  {
	char	resource_name[ERR_NAMESIZE];	/* resource name logged with  	*/
					/* each error log entry.        */
	dev32_t	adapter_devno;		/* SCSI adapter device driver   */
					/* major/minor num 		*/
#if defined(__ia64) && !defined(__64BIT__)
        uchar pad[4];           /* Padding for IA64 ILP32 mode */
#endif
        unsigned long long scsi_id;     /* 64-bit SCSI ID for device    */
        unsigned long long lun_id;      /* 64-bit SCSI LUN ID for device*/
        unsigned long long utm_lun_id;  /* 64-bit SCSI LUN ID for UTM lun*/
        uchar  scsi_flags;              /* SCSI flags set by the config */
                                        /* method.                      */
#define DK_AUTOSENSE_ENABLED    0x1     /* This flag indicates the      */
                                        /* device will automatically    */
                                        /* return request sense data    */
                                        /* when an autocontingent       */
                                        /* allegiance (ACA) condition   */
                                        /* occurs.                      */
#define DK_NACA_1_ENABLED       0x2     /* The Normal ACA (NACA) value  */
                                        /* of 1 in the SCSI CDB is      */
                                        /* supported by this device.    */
#define DK_64BIT_IDS            0x4     /* This flag indicates the SCSI */
                                        /* adapter driver supports 64-  */
                                        /* bit SCSI ids and lun ids for */
                                        /* this device.                 */
#define DK_LUN_RESET_ENABLED    0x8     /* This flag indicates the      */
					/* support the lun reset task   */
					/* management command           */

	uchar	safe_relocate;		/* Flag to indicate whether or  */
					/* not hardware re-assign of    */
					/* bad blocks is supported by   */
					/* the device, and if supported,*/
					/* whether or not it is safe in */
					/* case of power disruption.    */
#define DK_NO_RELOCATION	0       /* Relocation not supported     */
#define DK_SAFE_RELOCATION	1       /* Relocation is safe           */
#define DK_UNSAFE_RELOCATION	2       /* Rel. supported but not safe  */
	uchar	async_flag;		/* Flag to force a device to    */
					/* run async.  Possible values  */
					/* are SC_ASYNC or NULL.  For   */
					/* most devices, this should be */
					/* NULL (even if the device is  */
					/* async, it should still work).*/
					/* The purpose of this flag is  */
					/* to force a sync device to    */
					/* run async.                   */
	uchar	extended_rw;		/* This flag is set to TRUE if  */
					/* the SCSI extended read and   */
					/* write commands are supported */
					/* by the device.		*/
	uchar	reset_delay;		/* This flag is set to 		*/
                                        /* SC_DELAY_CMD if a delay is   */
					/* required after the device is */
					/* reset and before a command   */
					/* is sent.  The flag is set to */
					/* NULL if the delay is not     */
					/* needed.			*/
	uchar	q_type;			/* The queuing type of the array */
					/* These are defined in scsi.h  */
					/* for resvd8 of sc_buf		*/
	uchar   q_err_value;	       	/* TRUE if Qerr bit should be   */
					/* set.	Otherwise FALSE.	*/
	uchar   clr_q_on_error;	       	/* TRUE if device clears its    */
					/* queue on error.  Otherwise   */
					/* FALSE.			*/
	uchar   buffer_ratio;           /* read/write data buffer ratio */
					/* of SCSI arrays to be filled in*/
					/* for page 2 mode select data  */
	uchar   cmd_tag_q;		/* if device supports command   */
					/* tag queuing	this is TRUE	*/
					/* otherwise it is FALSE	*/

	uchar	 reserve_lock;		/* If true, open sequence will 	*/
					/* include a reserve cmd. Else	*/
					/* no reserve issued to device  */
#define	DK_NO_RESERVE		0x00	/* User does not want to have	*/
					/* any reservation policy on	*/
					/* this disk.			*/
#define	DK_SINGLE_PATH_RESERVE	0x01	/* Legacy reservation policy    */
					/* using reserve/release.       */
#define	DK_PR_EXCLUSIVE		0x02	/* Exclusive host access policy */
					/* using Persistent Reserve.	*/
#define	DK_PR_SHARED		0x04	/* Multi-Hosts shared access	*/
					/* policy using Persistent	*/
					/* Reserve.			*/

	uchar	 write_cache;		/* If true, WCE bit in mode  	*/
					/* page 08 will be set 		*/
#define CACHE_OFF  0x00 /* Caching is currently off */
#define USE_CACHE  0x01 /* Use the cache (fast-load unless FAST_WRITE set) */
#define FAST_WRITE 0x02 /* Use fast-write (mirrored) write caching */
#define CACHE_CHANGED 0x04 /* Need to update ODM */

	uchar	 device_features;	/* bitmask for feature support  */
#define ALTPATH_RESERVE 0x01		/* altpath reserve is supported */
#define	SNAPSHOT_VOL	0x02		/* this is a snapshot volume    */
#define CACHE_MODE_DATA 0x04		/* cache mode data is supported */

	uchar	raid_level;		/* RAID level of this volume	*/

	ushort   queue_depth;		/* maximum number of commands   */
					/* that can be queued up to the */
					/* SCSI adpater device driver   */
					/* for a given device.		*/
	ushort	reserve_delay;		/* Total # sec to delay reserves */
	int	recovery_limit;		/* Max allowable recovery level */
					/* before a device recovered    */
					/* error is reported to be      */
					/* re-assigned. 		*/

	uchar	dev_type;		/* Is this devno a controller, 	*/
					/* an array, or a router.	*/

#define ARRAY_DEVICE		0x00
#define CONTROLLER_DEVICE	0x01
#define ROUTER_DEVICE		0x02

	uchar	ctrl_type;		/* Which type of controller 	*/

#define INF_CONTROLLER		0x00
#define ADP_CONTROLLER		0x01
#define FCS_CONTROLLER		0x02
	ushort	rw_timeout;		/* Timeout values in secs for	*/
					/* read and write commands.	*/
	ushort	reassign_timeout;	/* Timeout values in secs for	*/
					/* re-assign commands.		*/

	uint	segment_size;		/* # bytes in sample rate       */
	uint	segment_cnt;		/* # of segments read from this */
					/* device 			*/
	uint	byte_count;		/* # bytes read beyond the      */
					/* number of segments		*/
	uint	max_coalesce;		/* Max number of bytes to be 	*/
					/* coalesced.			*/
	uint    max_request;		/* maximum request size for     */
					/* a SCSI array			*/
	int	mode_data_length;	/* mode select data length      */
	char	mode_data[256];		/* mode select data buffer      */
	int	mode_default_length;	/* mode select default data lng */
	char	mode_default_data[256];	/* mode select default data     */
	uint	restart_dev;		/* Is dynamic tracking enabled  */
					/* for this controller		*/
	ushort	scsi_version;		/* Version of scsi_buf to be	*/
					/* used				*/
	uint64_t	ww_name;	/* Port Name of target		*/
	uint64_t	node_name;	/* Node Name of target		*/
	uint	max_luns;		/* max # luns for this router   */
	unsigned long long PR_key_value;/* persistent reserve		*/
					/* registration key value	*/
	uchar   transport_type;         /* Tranport layer type          */
#define DK_TRANSPORT_FCP        0x1     /* FCP transport type           */
#define DK_TRANSPORT_ISCSI      0x2     /* iSCSI transport type         */
   	ushort  valid_flags;            /* Indicates whether certain    */
                                        /* fields in ddi are valid      */
#define DK_WWN_VALID            0x01    /* ww_name field valid          */
#define DK_NODE_N_VALID         0x02    /* node_name field valid        */
#define DK_TARGET_N_VALID       0x04    /* target_name field valid      */
#define DK_PORT_NUM_VALID       0x08    /* port_num field valid         */
#define DK_IP_ADDR_VALID        0x10    /* ip_addr field is valid       */
   	uint64_t port_num;              /* Port number of the device.   */
	iscsi_ip_addr  ip_addr;         /* Contains IPv4/v6 address     */
                                        /* of the device.               */
        char target_name[DK_SCSI_STRING_SZ]; /* Contains the target     */
                                        /* name of the device.          */
	uchar	delay_control;		/* control delay timing		*/


};

/*
 * Persistent Reserve In - IOCTL structure.  This structure
 * supports DKPRES_READKEYS & DKPRES_READRES flags.  
 */
struct dk_pres_in {
	ushort	version;		/* Version of Persistent Reserve */
					/* implementation.		 */
	ushort 	allocation_length;	/* Allocation space for the 	 */
					/* return parameters pertain to  */
					/* reservation_info		 */
	uint 	generation;		/* counter maintain by the LUN to*/
					/* keep track of reservation key */
					/* on when it's being changed.   */
	uint	returned_length;	/* number of bytes in the 	 */
					/* reservation key list.	 */
	uchar	scsi_status;		/* scsi command status		 */
	uchar	sense_key;		/* check condition data	 	 */
	uchar	scsi_asc;		/* check condition data	 	 */
	uchar	scsi_ascq;		/* check condition data	 	 */
	uchar	*reservation_info;	/* reservation key(s) data return*/
};

#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only 
 *       for internal device driver use.
 * 
 * dk_pres_in is size variant for 32/64 bit, thus require two separate
 * structure to handle the size differences.
 */
struct dk_pres_in32 {
        ushort  version;                /* Version of Persistent Reserve */
                                        /* implementation.               */
        ushort  allocation_length;      /* Allocation space for the      */      
                                        /* return parameters pertain to  */
                                        /* reservation_info              */
        uint    generation;             /* counter maintain by the LUN to*/
                                        /* keep track of reservation key */
                                        /* on when it's being changed.   */
        uint    returned_length;        /* number of bytes in the        */
                                        /* reservation key list.         */
        uchar   scsi_status;            /* scsi command status           */
        uchar   sense_key;              /* check condition data          */
        uchar   scsi_asc;               /* check condition data          */
        uchar   scsi_ascq;              /* check condition data          */
        ptr32   reservation_info;      /* reservation key(s) data return */
};

/*
 * NOTE: This structure is not supported for use by applications. It is only 
 *       for internal device driver use.
 *
 * dk_pres_in is size variant for 32/64 bit, thus require two separate
 * structure to handle the size differences.
 */
struct dk_pres_in64 {
        ushort  version;                /* Version of Persistent Reserve */
                                        /* implementation.               */
        ushort  allocation_length;      /* Allocation space for the      */      
                                        /* return parameters pertain to  */
                                        /* reservation_info              */
        uint    generation;             /* counter maintain by the LUN to*/
                                        /* keep track of reservation key */
                                        /* on when it's being changed.   */
        uint    returned_length;        /* number of bytes in the        */
                                        /* reservation key list.         */
        uchar   scsi_status;            /* scsi command status           */
        uchar   sense_key;              /* check condition data          */
        uchar   scsi_asc;               /* check condition data          */
        uchar   scsi_ascq;              /* check condition data          */
        ptr64   reservation_info;      /* reservation key(s) data return */
};

#endif /* _KERNEL */

/*
 * Persistent Reserve Out - IOCTL structure.  This structure
 * supports DKPRES_CLEAR flag. 
 */
struct dk_pres_clear {
   ushort               version;        /* Version of Persistent Reserve */
                                        /* implementation.               */
   uchar              scsi_status;      /* scsi command status           */
   uchar              sense_key;        /* check condition data          */
   uchar              scsi_asc;         /* check condition data          */
   uchar              scsi_ascq;        /* check condition data          */

};

/*
 * Persistent Reserve Out - IOCTL structure.  This structure
 * supports DKPRES_PREEMPT & DKPRES_PREEMPT_ABORT flags.
 */
struct dk_pres_preempt {
   ushort               version;        /* Version of Persistent Reserve */
   unsigned long long preempt_key; 	/* current key in the LUN being  */
					/* preempted.			 */
   uchar              scsi_status;      /* scsi command status           */
   uchar              sense_key;        /* check condition data          */
   uchar              scsi_asc;         /* check condition data          */
   uchar              scsi_ascq;        /* check condition data          */
};
                                                                           
/*                                                                         
 * Persistent Reserve Out - IOCTL structure.  This structure               
 * supports DKPRES_REGISTER flag.                                          
 */                                                                        
struct dk_pres_register {                                                  
   ushort             version;          /* Version of Persistent Reserve */
   uchar              scsi_status;      /* scsi command status           */
   uchar              sense_key;        /* check condition data          */
   uchar              scsi_asc;         /* check condition data          */
   uchar              scsi_ascq;        /* check condition data          */
};
#endif /* _H_FCPARRAY */
