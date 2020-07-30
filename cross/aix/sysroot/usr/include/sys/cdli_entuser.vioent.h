/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernel/sys/cdli_entuser.vioent.h 1.7.1.2                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2004,2008              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/* @(#)31       1.7.1.2  src/bos/kernel/sys/cdli_entuser.vioent.h, vioent, bos53Q, q2008_19C6 5/1/08 11:34:58 */

#ifndef _H_CDLI_ENTUSER_VIOENT
#define _H_CDLI_ENTUSER_VIOENT

/************************************************************************/
/*                      Trace hook numbers                              */
/************************************************************************/

#define HKWD_VIOENT_XMIT   0x53B   /* Traces data on the transmit path. */
#define HKWD_VIOENT_RECV   0x53C   /* Traces data on the receive path.  */
#define HKWD_VIOENT_OTHER  0x53D   /* Traces data on all other paths.   */

/************************************************************************/
/*           Virtual I/O Ethernet Device Specific Ioctls                */
/************************************************************************/

#define VIOENT_ATTRIBUTES             (NDD_DEVICE_SPECIFIC)
#define VIOENT_MAKE_TRUNK_ACTIVE      (NDD_DEVICE_SPECIFIC+1)
#define VIOENT_GET_VID_LIST           (NDD_DEVICE_SPECIFIC+2)
#define VIOENT_GET_SWITCH_ID          (NDD_DEVICE_SPECIFIC+3)


/************************************************************************/
/*              Virtual I/O Ethernet Statistics                         */
/************************************************************************/

/*
 * The first character of the switch_id field in the stats will be
 * null terminiated if the function is not supported or there was an
 * error retrieving the switch id.
 */

#define VIOENT_SWITCH_ID_SIZE   33

/*
 * vioent_vidlist_t
 *
 * Structure used for entstats and the VIOENT_GET_VID_LIST ioctl call.
 *
 *   The first entry in the vidlist is always the default port VID (pvid)
 *   If a pvid was not configured the first entry will have a value of zero
 *   and should be counted when reading the vid list.  vidcnt contains the
 *   number of vids in the vidlist.
 */

#define VIOENT_VIDLIST_SIZE   63

#pragma options align=packed

typedef struct {
   uint16_t vidcnt;
   uint16_t vidlist[VIOENT_VIDLIST_SIZE];
} vioent_vidlist_t;

typedef struct {
   int lan_state;
   int rx_que_size;          /* Size of the Receive Queue                    */ 
   int filters;              /* Number of MCast Filters                      */ 
   int filters_enabled;      /* Number Enabled of MCast Filters              */ 
   int filters_enqueued;     /* Number Enqueued MCast Filters                */ 
   int filters_exceeded;     /* Non-Zero: Max Filters Exceeded               */ 
   int trunk_adapter;        /* Non-Zero: Adapter is a Trunk Adapter         */
   int nocopybufs;           /* The number of times we ran out of copy buffers */
   int huge_min;             /* Number of pre-allocated buffers              */
   int huge_max;             /* Maximum number of buffer allowed             */
   int huge_alloc;           /* Number of buffers allocated                  */
   int huge_maxa;            /* Maximum number of buffers ever allocated     */
   int huge_reg;             /* Number of buffers registered with Hypervisor */
   int huge_lowreg;          /* Lowest buffers registered                    */
   int large_min;            /* Number of pre-allocated buffers              */
   int large_max;            /* Maximum number of buffer allowed             */
   int large_alloc;          /* Number of buffers allocated                  */
   int large_maxa;           /* Maximum number of buffers ever allocated     */
   int large_reg;            /* Number of buffers registered with Hypervisor */
   int large_lowreg;         /* Lowest buffers registered                    */
   int medium_min;           /* Number of pre-allocated buffers              */
   int medium_max;           /* Maximum number of buffer allowed             */
   int medium_alloc;         /* Number of buffers allocated                  */
   int medium_maxa;          /* Maximum number of buffers ever allocated     */
   int medium_reg;           /* Number of buffers registered with Hypervisor */
   int medium_lowreg;        /* Lowest buffers registered                    */
   int small_min;            /* Number of pre-allocated buffers              */
   int small_max;            /* Maximum number of buffer allowed             */
   int small_alloc;          /* Number of buffers allocated                  */
   int small_maxa;           /* Maximum number of buffers ever allocated     */
   int small_reg;            /* Number of buffers registered with Hypervisor */
   int small_lowreg;         /* Lowest buffers registered                    */
   int tiny_min;             /* Number of pre-allocated buffers              */
   int tiny_max;             /* Maximum number of buffer allowed             */
   int tiny_alloc;           /* Number of buffers allocated                  */
   int tiny_maxa;            /* Maximum number of buffers ever allocated     */
   int tiny_reg;             /* Number of buffers registered with Hypervisor */
   int tiny_lowreg;          /* Lowest buffers registered                    */
   uint trunk_priority;      /* Trunk Adapter Priority                       */
   uint trunk_active;        /* Trunk Adapter Active: TRUE/FALSE             */
   uint64_t illan_attrs;     /* Hypervisor and Adapter Attributes            */
   uint64_t illan_iattrs;    /* Hypervisor and Adapter Initial Attributes    */
   uint64_t hsend_failures;  /* Hypervisor Send Failures                     */
   uint64_t hsend_errors;    /* Hypervisor Send Errors                       */
   uint64_t hsend_drops;     /* Hypervisor Sends Dropped by the Remote       */
   uint64_t hrecv_failures;  /* Hypervisor Receive Failures                  */
   vioent_vidlist_t vidlist; /* List of PHYP configured VLAN IDs             */ 
   char switch_id[VIOENT_SWITCH_ID_SIZE]; /* Switch ID of the Virtual Switch */
   uint64_t invalid_vlan_errors; /* The number of invalid VLAN Id packets sent */

   uint16_t  huge_vrm_min;    /* The number of VRM min pages for this pool */
   uint16_t  large_vrm_min;   /* The number of VRM min pages for this pool */
   uint16_t  medium_vrm_min;  /* The number of VRM min pages for this pool */
   uint16_t  small_vrm_min;   /* The number of VRM min pages for this pool */
   uint16_t  tiny_vrm_min;    /* The number of VRM min pages for this pool */

   uint16_t  huge_vrm_des;    /* The number of VRM desired pages for this pool */
   uint16_t  large_vrm_des;   /* The number of VRM desired pages for this pool */
   uint16_t  medium_vrm_des;  /* The number of VRM desired pages for this pool */
   uint16_t  small_vrm_des;   /* The number of VRM desired pages for this pool */
   uint16_t  tiny_vrm_des;    /* The number of VRM desired pages for this pool */

   uint8_t  huge_dma_flag;    /* The DMA MAXMIN flag for this pool */
   uint8_t  large_dma_flag;   /* The DMA MAXMIN flag for this pool */
   uint8_t  medium_dma_flag;  /* The DMA MAXMIN flag for this pool */
   uint8_t  small_dma_flag;   /* The DMA MAXMIN flag for this pool */
   uint8_t  tiny_dma_flag;    /* The DMA MAXMIN flag for this pool */

   uint16_t  tx_vrm_min;      /* The number of VRM min pages for this pool */
   uint16_t  tx_vrm_des;      /* The number of VRM min pages for this pool */
   uint8_t   tx_dma_flag;     /* The DMA MAXMIN flag for this pool */
   uint16_t  copy_buffs;      /* The number of copy buffers */
   uint32_t  copy_bytes;      /* The size threshold to copy versus map */

   uint32_t  phyp_mem;        /* The amount of memory allocated to PHYP */
   uint16_t  phyp_vrm_min;    /* The number of VRM min pages for this pool */
   uint8_t   phyp_dma_flag;   /* The DMA MAXMIN flag for this pool */

   uint32_t attributes;                              /* Driver Attributes */
     #define VIOENT_STATS_ATTR_DMA_EXT   0x00000001   /* Using Extended DMA Init */

   uint64_t reserved[5];      /* Reserve Space   */


} vioent_stats_t;

#pragma options align=reset

typedef struct {
   ndd_genstats_t     ent_ndd_stats;
   ent_genstats_t     ent_gen_stats;
   vioent_stats_t     vioent_stats;
} vioent_all_stats_t;

/* 
 * Structure for VIOENT_ATTRIBUTES ioctl call 
 */

typedef struct {
   uint8_t  trunk_adapter;   /* TRUE / FALSE */
   uint8_t  trunk_active;    /* TRUE / FALSE */
   uint8_t  trunk_priority;  /* Value: 0-15  */
   uint64_t reserved[16];    /* Reserve Space */
} vioent_attr_t;

#endif /* _H_CDLI_ENTUSER_VIOENT */
