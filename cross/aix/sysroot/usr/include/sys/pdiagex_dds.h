/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53S src/bos/kernel/sys/pdiagex_dds.h 1.8                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1995,2008              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)38       1.8  src/bos/kernel/sys/pdiagex_dds.h, sysxdiag, bos53S, s2008_39B0 9/18/08 16:28:24 */
/*
 *
 * COMPONENT_NAME: (sysxdiag) Diagnostic Kernel Extension
 *
 * FUNCTIONS: Device Dependent Structure used by the           
 *          : Portable Diagnostic Kernel Extension
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _h_pdiagex_dds
#define _h_pdiagex_dds

#include <sys/time.h>
#include <sys/pdiag_def.h>

/************************************************************************/
/* PIO Constants						        */
/************************************************************************/
/* PIO TYPE VALUES */
#define IOCHAR8            1  /* PIO TYPEs (size values) 		*/
#define IOSHORT16          2
#define IOLONG32           4
#define IOLONGLONG64       8

/* INTLEV VALUES */
#define PROCLEV            1  /* PIO called from User Process Level 	*/
#define INTRKMEM           2  /* PIO called from IntrptLev,Buf inKmem	*/
#define INTRPMEM           3  /* PIO called from IntrptLev,Buf XMAttc	*/

#define PDIAG_SING_LOC_ACC 123  /* R/W from 1 location to 1 loc,        */
                                /* count times                          */
#define PDIAG_SING_LOC_HW  124  /* buffer gets R/W count times,         */
                                /* hardware gets W/R once               */
#define PDIAG_SING_LOC_BUF 125  /* buffer gets R/W once,                */
                                /* hardware gets W/R count times        */
#define PDIAG_MULT_LOC_ACC 126  /* R/W from count locs to count locs    */
                                /* once each                            */

/* INTERRUPT HANDLER SPECIAL RETURN CODE 				*/
#define INTR_SUCC_ALARM	   0x4321

/* MEMIO VALUES */
#define PDIAG_IO_OP         1   /* I/O Operation                        */
#define PDIAG_MEM_OP        2   /* Memory Operation                     */
#define PDIAG_POS_OP        3   /* POS Operation                        */
#define PDIAG_CFG_OP        4   /* Cfg Reg Operation                    */
#define PDIAG_SPECIAL_IO_OP 5   /* I/O Operation using io_att           */
#define PDIAG_HOST_OP 	    6   /* user host memory that is dma mapped. */

/* OPERATION TYPE VALUES */
#define PDIAG_DMA_MASTER    1   /* Master 			        */
#define PDIAG_DMA_SLAVE	    2   /* Slave 			        */
#define PDIAG_DMA_ENABLE    3   /* DMA enable                           */
#define PDIAG_DMA_DISABLE   4   /* DMA disable                          */
#define PDIAG_DMA_FLUSH	    5   /* DMA flush                            */

#define HCALL_PARM_CNT	12
typedef struct
{
#ifdef __64BIT_KERNEL
        unsigned long long h0;
        unsigned long long h1;
        unsigned long long h2;
        unsigned long long h3;
        unsigned long long h4;
        unsigned long long h5;
        unsigned long long h6;
        unsigned long long h7;
        unsigned long long h8;
        unsigned long long h9;
        unsigned long long h10;
        unsigned long long h11;
#else
        uint32  h0[2];
        uint32  h1[2];
        uint32  h2[2];
        uint32  h3[2];
        uint32  h4[2];
        uint32  h5[2];
        uint32  h6[2];
        uint32  h7[2];
        uint32  h8[2];
        uint32  h9[2];
        uint32  h10[2];
        uint32  h11[2];
#endif
} hcall_parms_t;

/************************************************************************/
/* kick_io_t is used to pass "kick" io operation information to pass to
 * pdiag_dd_kick_hdw_and_watch_for_interrupts_safe_mode() call.
 ************************************************************************/
typedef struct
{
   uint32	kick_type;	/* Size of the transfer.
				 * Use IOCHAR8, IOSHORT16, or IOLONG32.
				 * Use IOEND in last record to end list.
				 */
   uint32	memio;		/* Indicates IO or memory map space.  
				 * Must be PDIAG_IO_OP or PDIAG_MEM_OP. 
				 */
   uint32	offset;		/* Offset in bytes from card base address.
				 */
   uint32	data;		/* Right justified data to write.
				 * If IOCHAR8, then use 000000XX,
				 * if IOSHORT16, then use 0000XXXX,
				 * if IOLONG32, then use XXXXXXXX.
				 */
}  kick_io_t;
				
/*----------------------------------------------------------------------*/
/*  PDIAGEX_OPFLAGS_T							*/
/*     This structure MUST be filled in by the Calling Application (TU)	*/
/*     This structure is used for Read and Write Operations             */
/*----------------------------------------------------------------------*/
typedef struct {
   uint32       memio;   	/* Type of Memory Operation		*/
                        	/* PDIAG_MEM_OP,PDIAG_IO_OP,PDIAG_POS_OP*/
   uint32       count;   	/* Number of accesses to perform	*/
   uint32       addr_incr_flag;	/* Flag that determines whether the data*/
                        	/* buffer address and/or the offset     */
                        	/* address gets incremented on each of  */
                        	/* count accesses.                      */
				/* PDIAG_SING_LOC_ACC or 		*/
				/* PDIAG_SING_LOC_HW   or		*/
				/* PDIAG_SING_LOC_BUF  or		*/
				/* PDIAG_MULT_LOC_ACC  			*/
   uint32       intr_level;  	/* Indicates which environment the 	*/
				/* calling application is in.    	*/
				/* PROCLEV or INTRKMEM or INTRPMEM      */
#ifdef __64BIT_KERNEL
   uint32       times;          /* Address of times structure, NULL if  */
                                /* not used.                            */
#else
   struct timestruc_t *times; 	/* Address of times structure, NULL if  */
				/* not used.                            */
#endif
} pdiagex_opflags_t;


/*----------------------------------------------------------------------*/
/*  PDIAGEX_INTR_DDS_T                                                  */
/*    This struct is filled in by the calling appl, as part of          */
/*    the main pdiagex_dds_msi_t.                                       */
/*----------------------------------------------------------------------*/
typedef struct 
{
   /* Interrupt Handler related DDS substructure */
#ifdef __64BIT_KERNEL
   uint32       data_ptr;      /* Pointer for passing data to interrupt */ 
#else
   pdiag_addr_t data_ptr;      /* Pointer for passing data to interrupt */
#endif
   uint32       d_count;       /* Count of bytes of data for interrupt  */
   uint32       bus_intr_lvl;  /* Interrupt level                       */
   uint32       intr_priority; /* Interrupt priority                    */
   uint32       intr_flags;    /* Interrupt flags as defined in intr.h  */
   uint32	wake_up_any_flag;/* this interrupt must wake any sleeper*/
   uint32	reserved2[2];  /* size of this struct = 8*uint32	*/
} pdiagex_intr_dds_t;


/*----------------------------------------------------------------------*/
/*  PDIAGEX_DDS_MSI_T			*/
/*    This structure MUST be filled in by the Calling Application (TU)	*/
/*    This structure is passed to pdiagex in the pdiag_open() routine   */
/*----------------------------------------------------------------------*/
typedef struct {
   uint32       slot_num;      /* slot number of adapter                */

   /* BUS DATA                                                          */
   uint32       bus_id;        /* Identifies the I/O bus that the DMA   */
                               /*  channel is to be allocated on.       */
   uint32	parent_bus_id;
   uint32       bus_type;      /* BUS_BID or BUS_PCIE			*/
#define BUS_PCIE (BUS_MAXTYPE + 1)
#define BUS_FUNNY (BUS_MAXTYPE + 2)
#define BUS_HEA (BUS_MAXTYPE + 3)
   uint32       bus_io_addr;   /* Base address of Bus I/O area          */
   uint32       bus_io_length; /* Length (width) of Bus I/O area        */
   uint32       bus_mem_addr;  /* Base address of Shared Bus Memory area*/
   uint32       bus_mem_length;/* Length (width) of Shared Bus Memory   */
                               /*  area                                 */
   /* DMA                                                               */
   /* Next three are for BUS_MICRO_CHANNEL devices only                 */
   uint32       dma_bus_mem;   /* Base address of Bus Memory DMA area   */
   uint32       dma_bus_length;/* Length (multiple of PAGESIZE) of BUS  */
                               /* Memory DMA area in bytes.             */
   uint32       dma_lvl;       /* Bus arbitration level                 */

   uint32       maxmaster;     /* maximum number of concurrent          */
                               /* dma_master calls                      */
   uint32       dma_flags;     /* DMA flags as defined in sys/dma.h.    */
                               /* These flags describe what actions to  */
                               /* take ( master/slave, initialize the   */
                               /* channel, etc.)                        */
   /* dma_bus_flags is for BUS_BID devices only                         */
   uint32       dma_bus_flags; /* Bus flags specific for DMA operation  */

   uint32       dma_chan_id;   /* For BUS_MICRO_CHANNEL                 */
                               /* Dma channel ID is returned as a result*/
                               /* of the DMA initialization.            */
                               /* For BUS_BID                           */
                               /* Dma channel ID is the assigned DMA    */
                               /* channel for the device.               */
                               /* For BUS_60X                           */
                               /* Dma channel ID is not used            */

   /* Attribute Expansion Area                                          */
#ifdef __64BIT_KERNEL
   uint32       attributes;    /* Pointer to specific attributes        */
#else
   pdiag_addr_t attributes;    /* Pointer to specific attributes        */
#endif

   /* Interrupt Handlers                                                */
   pdiagex_intr_dds_t	intr_dds[32];

} pdiagex_dds_msi_t;

/*----------------------------------------------------------------------*/
/*  PDIAGEX_DDS_64_T							*/
/*    This structure MUST be filled in by the Calling Application (TU)	*/
/*    This structure is passed to pdiagex in the pdiag_open() routine   */
/*----------------------------------------------------------------------*/
typedef struct {
   uint32	dds_version;   /* dds version - must be 0x00000301	*/
   uint32       slot_num;      /* slot number of adapter                */

   /* BUS DATA                                                          */
   uint32       bus_id;        /* Identifies the I/O bus that the DMA   */
                               /*  channel is to be allocated on.       */
   uint32	parent_bus_id;
   uint32       bus_type;      /* BUS_BID or BUS_PCIE			*/
#define BUS_PCIE (BUS_MAXTYPE + 1)
   uint32	reserved;
   uint32       bus_io_addr;   /* Base address of Bus I/O area          */
   uint32       bus_io_length; /* Length (width) of Bus I/O area        */
   uint32	bus_mem_addr_hi; /* hi 32 bits of adapter mem base addr */
   uint32       bus_mem_addr;  /* low 32 bits of adapter mem base addr  */
   uint32       bus_mem_length;/* size in bytes of adapter mem area     */
   /* DMA                                                               */
   /* Next three are for BUS_MICRO_CHANNEL devices only                 */
   uint32       dma_bus_mem;   /* Base address of Bus Memory DMA area   */
   uint32       dma_bus_length;/* Length (multiple of PAGESIZE) of BUS  */
                               /* Memory DMA area in bytes.             */
   uint32       dma_lvl;       /* Bus arbitration level                 */

   uint32       maxmaster;     /* maximum number of concurrent          */
                               /* mapped pages.                         */
   uint32       dma_flags;     /* DMA flags as defined in sys/dma.h.    */
                               /* These flags describe what actions to  */
                               /* take ( master/slave, initialize the   */
                               /* channel, etc.)                        */
   /* dma_bus_flags is for BUS_BID devices only                         */
   uint32       dma_bus_flags; /* Bus flags specific for DMA operation  */

   uint32       dma_chan_id;   /* For BUS_MICRO_CHANNEL                 */
                               /* Dma channel ID is returned as a result*/
                               /* of the DMA initialization.            */
                               /* For BUS_BID                           */
                               /* Dma channel ID is the assigned DMA    */
                               /* channel for the device.               */
                               /* For BUS_60X                           */
                               /* Dma channel ID is not used            */

   /* Attribute Expansion Area                                          */
#ifdef __64BIT_KERNEL
   uint32       attributes;    /* Pointer to specific attributes        */
#else
   pdiag_addr_t attributes;    /* Pointer to specific attributes        */
#endif

   uint32	reserved14[14];	/* total size = 128 bytes = 32 * 4 	*/

   /* Interrupt Handlers                                                */
   pdiagex_intr_dds_t	intr_dds[32];	/*  1024 =32*32 bytes		*/

   char		reserved896[896];	/* total size = 2048 bytes	*/

} pdiagex_dds_64_t;



/*----------------------------------------------------------------------*/
/*  LEGACY PDIAGEX_DDS_T						*/
/*    This structure MUST be filled in by the Calling Application (TU)	*/
/*    This structure is passed to pdiagex in the pdiag_open() routine   */
/*----------------------------------------------------------------------*/
typedef struct {
   uint32       slot_num;      /* slot number of adapter                */

   /* BUS DATA                                                          */
   uint32       bus_id;        /* Identifies the I/O bus that the DMA   */
                               /*  channel is to be allocated on.       */
   uint32       bus_type;      /* BUS_MICRO_CHANNEL, BUS_60X or BUS_BID */
   uint32       bus_io_addr;   /* Base address of Bus I/O area          */
   uint32       bus_io_length; /* Length (width) of Bus I/O area        */
   uint32       bus_mem_addr;  /* Base address of Shared Bus Memory area*/
   uint32       bus_mem_length;/* Length (width) of Shared Bus Memory   */
                               /*  area                                 */
   /* DMA                                                               */
   /* Next three are for BUS_MICRO_CHANNEL devices only                 */
   uint32       dma_bus_mem;   /* Base address of Bus Memory DMA area   */
   uint32       dma_bus_length;/* Length (multiple of PAGESIZE) of BUS  */
                               /* Memory DMA area in bytes.             */
   uint32       dma_lvl;       /* Bus arbitration level                 */

   uint32       maxmaster;     /* maximum number of concurrent          */
                               /* dma_master calls                      */
   uint32       dma_flags;     /* DMA flags as defined in sys/dma.h.    */
                               /* These flags describe what actions to  */
                               /* take ( master/slave, initialize the   */
                               /* channel, etc.)                        */
   /* dma_bus_flags is for BUS_BID devices only                         */
   uint32       dma_bus_flags; /* Bus flags specific for DMA operation  */

   uint32       dma_chan_id;   /* For BUS_MICRO_CHANNEL                 */
                               /* Dma channel ID is returned as a result*/
                               /* of the DMA initialization.            */
                               /* For BUS_BID                           */
                               /* Dma channel ID is the assigned DMA    */
                               /* channel for the device.               */
                               /* For BUS_60X                           */
                               /* Dma channel ID is not used            */

   /* Interrupt Handler                                                 */
#ifdef __64BIT_KERNEL
   uint32       data_ptr;      /* Pointer for passing data to interrupt */ 
#else
   pdiag_addr_t data_ptr;      /* Pointer for passing data to interrupt */
#endif
   uint32       d_count;       /* Count of bytes of data for interrupt  */
   uint32       bus_intr_lvl;  /* Interrupt level                       */
   uint32       intr_priority; /* Interrupt priority                    */
   uint32       intr_flags;    /* Interrupt flags as defined in intr.h  */

   /* Attribute Expansion Area                                          */
#ifdef __64BIT_KERNEL
   uint32       attributes;    /* Pointer to specific attributes        */
#else
   pdiag_addr_t attributes;    /* Pointer to specific attributes        */
#endif

} pdiagex_dds_t;


#endif
