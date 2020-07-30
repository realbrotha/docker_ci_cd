/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/sys/dma.h 1.51.1.2                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)99     1.51.1.2  src/bos/kernel/sys/dma.h, sysios, bos53L, l2007_22A4 5/24/07 08:34:39 */

#ifndef _H_DMA
#define _H_DMA
/*
 * COMPONENT_NAME: (SYSIOS) IO subsystem
 *
 * FUNCTIONS: DMA external interface definition.
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#include <sys/sysdma.h>
#include <sys/types.h>
#include <sys/xmem.h>

/*****************************  IMPORTANT NOTICE  ***************************
* In AIX 5.2, the Micro-channel support is removed. Therefore, all symbols  *
* that are Micro-channel (MCA) specific are isolated in this file using     *
* #ifdef OBSOLETE_MCA_PREP. Symbols enclosed in #ifdef OBSOLETE_MCA_PREP    *
* are obsolete and will be removed from this file in the future versions of *
* AIX. Therefore, the following are recommended:                            * 
* (1) New programs must NOT use these symbols, and                          *
* (2) Existing programs should be cleaned up with respect to these symbols. *
*     To cleanly compile the existing programs that use these symbols,      *
*     define OBSOLETE_MCA_PREP in YOUR program.                             *
*                                                                           *
* DO NOT MODIFY THIS FILE, BECAUSE IT WILL GLOBALLY AFFECT ALL PROGRAMS IN  *
* THE SYSTEM THAT INCLUDE THIS FILE.                                        *
*                                                                           *
****************************************************************************/

/****************************************************************************
 *	PCI/ISA Specific Flags, Structures, Functions, Macros, etc.         *
 ****************************************************************************/

/***********************  INITIALIZATION FLAGS ******************************/

/*	
 * These are the flag values for the d_map_init service. These flags must each 
 * be unique with respect to each other.
 */
#define		DMA_SLAVE	0x10		/* device is a DMA slave  */
#define		DMA_MASTER	0x00		/* device is a DMA master */

/*
* NOTE:  DMA_ENABLE_64 allows a 32-bit driver to use the 64-bit
*        interfaces (which are automatically used by 64-bit drivers).
*        DMA_ADDRESS_64_BIT indicates the device is capable of
*        generating 64-bit addresses.  Using the 64-bit interfaces
*        in conjunction with a device that supports 64-bit addressing
*        can avoid unnecessary address translation and latency, if all
*        intervening PCI bridges also support 64-bit addressing.
*
*        DMA_CONTIGUOUS specifies that a buffer mapped using this
*        handle will have contiguous bus addresses.  The d_map_init
*        call will fail if the system does not provide the resources
*        required to guarantee the contiguity property.
*/
#define		DMA_ADDRESS_64_BIT	0x80	/* can drive 64-bit address */
#define		DMA_ENABLE_64		0x100	/* enable 64-bit interfaces */
#define         DMA_CONTIGUOUS          0x800	/* only contiguous mapping  */

/*
* NOTE: DMA_NO_ZERO_ADDR flag should be used by those device drivers that
* cannot drive a PCI bus address of '0'. On systems with TCEs enabled (I/O 
* address remapping hardware), specifying this flag will guarantee that the
* driver will never be given bus address '0'.  On LPAR systems, setting this
* flag has the additional side effect of reducing the driver's DMA mappable 
* memory by 4K.  On systems without TCEs enabled, the presence of this flag
* will cause d_map_init to fail, since the system can not guarantee that the
* driver will never see bus address '0'.
*/
#define         DMA_NO_ZERO_ADDR        0x40    /* cannot drive bus addr '0' */

/*
 * For IA64 (no TCE hardware) it is important to know the addressing
 * capabilities (64 or 32 bit) of the bus and its path to system memory.
 * This information is available at initialization time via the
 * per-bus "pci_bus" structure. The PCI bus driver code preserves the 
 * info in a flag bit for easy reference later. This flag value is 
 * not intended to be supplied by the adapter driver.
 * The 0x200 position of the flag is defined in m_dma.h
*/
#define		DMA_64_BIT_PATH		0x400	/* 64-bit addressing path */
						/* to system memory       */

/*
* By default, the PCI bus device driver and the vdevice bus device driver
* allocates one additional page more DMA space than what the calling device
* driver requests via the DMA_MAXMIN_* flag.  This is done to support
* non-page aligned transfers of size MAXMIN.  A device driver may avoid
* the additional page by specifying DMA_MAXMIN_MAPSPACE in its flags at
* d_map_init time.  DMA_MAXMIN_MAPSPACE indicates that the DMA_MAXMIN_* flag
* represents the amount of mappable address space the device driver requires,
* rather than the maximum transfer value.
*
* Example:
* Assume that a device driver has specified DMA_MAXMIN_256K and that the page
* size is 4K.  Given these assumptions, that device driver must be able to
* ensure both of the following when using DMA_MAXMIN_MAPSPACE:
*
* 1. The largest successful non-page aligned single DMA transfer is
*    252K (256K - 4K).
* 2. The largest successful page aligned single DMA transfer is 256K.
*
* If the DMA_MAXMIN_MAPSPACE flag is not used, then the device driver's largest
* successful non-page aligned single DMA transfer is 256K.
*/
#define		DMA_MAXMIN_MAPSPACE	0x1000	/* do not add extra page to */
						/* requested size	    */

/*
* The DMA_MAXMIN_QUIET flag allows a driver to indicate that it makes
* multiple D_MAP_INIT calls with a decreasing value of the DMA_MAXMIN_* flag.
* This flag prevents an error from being logged when there is not enough DMA
* space to fulfill the request specified by the DMA_MAXMIN_* flag.
*/
#define		DMA_MAXMIN_QUIET	0x2000	/* do not log errors due to */
						/* insufficent DMA space to */
						/* fulfill request	    */

/* The DMA_MAXMIN_* encoded flag values should be used by the
 * device driver to represent AT A MINIMUM the largest required
 * minimum transfer for any device on that adapter to make forward
 * progress.  For example:
 *    
 *     A SCSI adapter may have 3 disks (block size 512 bytes) and
 *     1 tape device (block size 8MB).  In this case, the SCSI
 *     adapter driver would have to specify at least a flag of
 *     DMA_MAXMIN_8M to guarantee that the SCSI Tape could do its
 *     minimum transfer.
 * 
 * Another consideration is throughput.  In the above example, 
 * each time a single tape operation takes place, the SCSI adapter
 * will be forced to throttle its queues, until there are no 
 * outstanding commands to any devices in order for the 8MB mappable
 * I/O space to become free in order to do the single minimum tape transfer.  
 * So it might be desirable to select a reasonable DMA_MAXMIN value to
 * allow a reasonable amount of concurrency per adapter.
 * 
 * The default is 64K so these flags should be used only if the
 * device needs a guaranteed mapping that exceeds the default.
 *
 * WARNING: The solution is not to simply select the largest possible
 *          DMA_MAXMIN flag.  That most likely would result in either the
 *          requesting device not configuring (due to lack of resources) or
 *          to other devices on the same HostBridge not configuring.
 */
#define		DMA_MAXMIN_MASK		0xF
#define		DMA_MAXMIN_64K		0x0	/* 64K byte max minxfer size */
#define		DMA_MAXMIN_128K		0x1	/* 128K byte max minxfer size */
#define		DMA_MAXMIN_256K		0x2	/* 256K byte max minxfer size */
#define		DMA_MAXMIN_512K		0x3	/* 512K byte max minxfer size */
#define		DMA_MAXMIN_1M		0x4	/* 1M byte max minxfer size */
#define		DMA_MAXMIN_2M		0x5	/* 2M byte max minxfer size */
#define		DMA_MAXMIN_4M		0x6	/* 4M byte max minxfer size */
#define		DMA_MAXMIN_8M		0x7	/* 8M byte max minxfer size */
#define		DMA_MAXMIN_16M		0x8	/* 16M byte max minxfer size */
#define		DMA_MAXMIN_32M		0x9	/* 32M byte max minxfer size */
#define		DMA_MAXMIN_64M		0xA	/* 64M byte max minxfer size */
#define		DMA_MAXMIN_128M		0xB	/* 128M byte max minxfer size */
#define		DMA_MAXMIN_256M		0xC	/* 256M byte max minxfer size */
#define		DMA_MAXMIN_512M		0xD	/* 512M byte max minxfer size */
#define		DMA_MAXMIN_1G		0xE	/* 1G byte max minxfer size */
#define		DMA_MAXMIN_2G		0xF	/* 2G byte max minxfer size */

/*
 * So, in summary, here is the breakdown of the INITIALIZATION flags for 
 * the d_map_init service.
 * 
 *   +---------------------------------------------------------------+
 *   |    R    e    s    e     r     v   |Q|M|C|6|r|6|6|z| |S|  MAX  |
 *   |                                   |U|A|O|4|s|4|4|r| |L|  MIN  |
 *   |                                   |I|P|N|B|v|E|A|0| |V|  XFER |
 *   | | | | | | | | | | |1|1|1|1|1|1|1|1|1|1|2|2|2|2|2|2|2|2|2|2|3|3|
 *   |0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|
 *   +---------------------------------------------------------------+
 */

/****************************  SERVICE FLAGS ******************************/
/*	
* These are the flag values for the d_map_page/d_map_list/d_map_slave services
*/
#define		DMA_READ	0x80		/* xfer from device to buffer*/
#define		BUS_DMA		0x100		/* buffer in bus memory   */
#define		DMA_BYPASS	0x4000		/* don't perform access check*/

/*
* This flag is defined for source-compatibility reasons only.
* It has no effect on the d_map_page/d_map_list/d_map_slave services
*/
#define		DMA_WRITE_ONLY	0x400		/* will not write to memory */


/*
 * So, in summary, here is the breakdown of the SERVICE flags for 
 * the d_map_page/d_map_list/d_map_slave services
 * 
 *   +---------------------------------------------------------------+
 *   |    R  e  s  e  r  v  e  d       |B|resvd|W| |B|R|  reserved   |
 *   |                                 |y|     |R| |U|d|             |
 *   |                                 |p|     |O| |S| |             |
 *   | | | | | | | | | | |1|1|1|1|1|1|1|1|1|1|2|2|2|2|2|2|2|2|2|2|3|3|
 *   |0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|
 *   +---------------------------------------------------------------+
 */


/**************************************************************************/

/*
 * The following flags are specific to the d_map_slave() service, and
 * represent the definitions for the chan_flags parameter for the d_map_slave
 * service
 *   +---------------------------------------------------------------+
 *   |mod|I|A|Reserved |E|Tim|Adr|         R e s e r v e d           |
 *   |bit|n|u|         |O|Bit|Mod|                                   |
 *   |   |c|t|         |P|   |   |                                   |
 *   | | | | | | | | | | |1|1|1|1|1|1|1|1|1|1|2|2|2|2|2|2|2|2|2|2|3|3|
 *   |0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|
 *   +---------------------------------------------------------------+
 */
#define CH_DEFAULT	   0x00000000	/* run channel with default settings*/

#define CH_DEMAND          0x00000000   /* xfer until TC or device releases */
#define CH_SINGLE          0x40000000   /* single byte or word at a time    */
#define CH_BLOCK           0x80000000   /* lock out other devices until done*/
#define CH_CASCADE         0xC0000000   /* used for cascading ISA masters   */

#define CH_ADDR_INC        0x00000000   /* increment address during DMA     */

#define CH_AUTOINIT        0x10000000   /* at TC, reset address/count to orig*/

#define CH_EOP_OUTPUT      0x00000000   /* specifies EOP signal is output   */
#define CH_EOP_INPUT       0x00400000   /* specifies EOP signal as input    */

#define CH_COMPAT          0x00000000   /* compatible timing, 8 sysclks     */
#define CH_TYPE_A          0x00100000   /* shorter cycles, 6 sysclks        */
#define CH_TYPE_B          0x00200000   /* faster i/o timing, 5 sysclks     */
#define CH_TYPE_F          0x00300000   /* high performance, 3 sysclks      */

#define CH_8BIT_BYTES      0x00000000   /* 8 bit I/O device, count by bytes */
#define CH_16BIT_WORDS     0x00040000   /* 16 bit I/O device, count by words*/
#define CH_16BIT_BYTES     0x000C0000   /* 16 bit I/O device, count by bytes*/


/***************************  DATA STRUCTURES ****************************/

typedef uint_t          dma_channel_t; /* DMA channel */

/*
 * This is the dio and d_iovec structures for the d_map_* services
 */ 
struct d_iovec {
        caddr_t iov_base;       /* base memory address                  */
        int32long64_t  iov_len; /* length of transfer for this area     */
        struct xmem *xmp;       /* cross memory pointer for this address*/
#ifdef __ia64
        /* IA64 machines don't have TCE support */
        caddr_t  bounce_lo;     /* virtual addr of bounced page in low mem */
        caddr_t  bounce_hi;     /* ...in high mem */
#endif /* __ia64 */
};
typedef struct d_iovec * d_iovec_t;

struct dio {
        int32long64_t  total_iovecs; /* total available iovec entries    */
        int32long64_t  used_iovecs;  /* number of used iovecs            */
        int32long64_t  bytes_done;   /* count of bytes processed         */
        int32long64_t  resid_iov;    /* number of iovec that couldn't be */
				     /* fully mapped (for NORES, DIOFULL)*/
        d_iovec_t	dvec;        /* pointer to list of d_iovecs      */
#ifdef __ia64
        int            busdd_flags;  /* internal per-mapping flags, should */
                                     /* be preserved by adapter drivers    */
                                     /* between map and unmap calls.       */
#endif
};
typedef struct dio *	dio_t;

#ifndef __64BIT_KERNEL
/*
 * These are the dio_64 and d_iovec_64 structures for the d_map_* services
 * These are used when the 64-bit interfaces are selected on the d_map_init
 * call by setting the DMA_ENABLE_64 flags. 
 * NOTE: The DMA_ENABLE_64 flag will ensure that the interfaces assigned
 *       on the D_MAP_INIT call will be the 64-bit interfaces.  However, the
 *	 DMA_ADDRESS_64_BIT flag must also be set to indicate that the device
 *       is truly 64-bit capable.  In other words, BOTH of these flags must
 *       be set to take advantage of 64-bit addressing by a PCI device.
 *	 The reason the flags are distinct is to allow a single device driver
 * 	 to potentially control both a 32-bit and a 64-bit device.  In this
 *	 case, the 64-bit interfaces would be used for both (single common
 *       set of interfaces for the driver independent of the device), but
 *	 the DMA_ADDRESS_64_BIT would also be set for the 64-bit device.  This
 * 	 will result in 32-bit address remapping for the 32-bit device (still
 *       using 64-bit interfaces), but straight 64-bit addressing for the 64-bit
 * 	 device.
 */ 
struct d_iovec_64 {
        unsigned long long iov_base;  /* base memory address                  */
        int     iov_len;        /* length of transfer for this area     */
        struct xmem *xmp;       /* cross memory pointer for this address*/
};
typedef struct d_iovec_64 * d_iovec_64_t;

struct dio_64 {
        int     total_iovecs;           /* total available iovec entries    */
        int     used_iovecs;            /* number of used iovecs            */
        int     bytes_done;             /* count of bytes processed         */
        int	resid_iov;              /* number of iovec that couldn't be */
					/* fully mapped (for NORES, DIOFULL)*/
        d_iovec_64_t	dvec;           /* pointer to list of d_iovecs      */
};
typedef struct dio_64 *	dio_64_t;
#endif /* ! __64BIT_KERNEL */

/*
 * This is the d_handle structure for the d_map_* services
 */
typedef struct d_handle *	d_handle_t;
struct d_handle {
    uint        id;                     /* identifier for this device       */
    uint        flags;                  /* device capabilities              */
#ifdef __64BIT_KERNEL
					/* pointer to d_map_page routine    */
    int         (*d_map_page)(d_handle_t,int,caddr_t, ulong *, struct xmem *);
					/* pointer to d_unmap_page routine  */
    void        (*d_unmap_page)(d_handle_t, ulong *);      
					/* pointer to d_map_list routine    */
    int         (*d_map_list)(d_handle_t, int, int, dio_t, dio_t);        
					/* pointer to d_unmap_list routine  */
    void        (*d_unmap_list)(d_handle_t, dio_t);      
					/* pointer to d_map_slave routine   */
    int         (*d_map_slave)(d_handle_t, int, int, dio_t, uint);       
					/* pointer to d_unmap_slave routine */
    int         (*d_unmap_slave)(d_handle_t);     
					/* pointer to d_map_disable routine */
    int         (*d_map_disable)(d_handle_t);     
					/* pointer to d_map_enable routine  */
    int         (*d_map_enable)(d_handle_t);      
					/* pointer to d_map_clear routine   */
    void        (*d_map_clear)(d_handle_t);       
					/* pointer to d_sync_mem routine    */
    int         (*d_sync_mem)(d_handle_t, dio_t);
#else
    int         (*d_map_page)();        /* pointer to d_map_page routine    */
    void        (*d_unmap_page)();      /* pointer to d_unmap_page routine  */
    int         (*d_map_list)();        /* pointer to d_map_list routine    */
    void        (*d_unmap_list)();      /* pointer to d_unmap_list routine  */
    int         (*d_map_slave)();       /* pointer to d_map_slave routine   */
    int         (*d_unmap_slave)();     /* pointer to d_unmap_slave routine */
    int         (*d_map_disable)();     /* pointer to d_map_disable routine */
    int         (*d_map_enable)();      /* pointer to d_map_enable routine  */
    void        (*d_map_clear)();       /* pointer to d_map_clear routine   */
    int         (*d_sync_mem)();        /* pointer to d_sync_mem routine    */	
#endif /* __64BIT_KERNEL */
    int         bid;                    /* bus id passed to d_map_init      */
    void	*bus_sys_xlate_ptr;     /* pointer to dma bus to system
					   translation information          */
    uint        reserved1;              /* padding                          */
    uint        reserved2;              /* padding                          */
    uint        reserved3;              /* padding                          */
};

extern void *d_alloc_dmamem(d_handle_t d_handle, size_t size, uint align);
extern int d_free_dmamem(d_handle_t d_handle, void *addr, size_t size);

/****************************  MACROS ************************************/
/*
 * The following macros are for to the d_map_* services 
 */

/*
 * Initialize a DIO structure
 *		DIO_INIT(struct dio *d,		- pointer to dio struct 
 *			 int n_iovecs);         - number of iovecs 
 *		(Must only be used from process level)
 */
#define DIO_INIT(d, n_iovecs)	\
	{	((struct dio *)(d))->dvec = (struct d_iovec *)xmalloc( \
			(sizeof(struct d_iovec) * (n_iovecs)), 2, pinned_heap);\
		if (((struct dio *)(d))->dvec == NULL)			\
			((struct dio *)(d))->total_iovecs = 0; 		\
		else							\
			((struct dio *)(d))->total_iovecs = n_iovecs; 	\
		((struct dio *)(d))->used_iovecs = 0;			\
		((struct dio *)(d))->bytes_done = 0;   			\
		((struct dio *)(d))->resid_iov = 0;   			\
	}

/*
 * Free elements of a DIO structure
 *		DIO_FREE(struct dio *d)		- pointer to dio struct 
 *		(Must only be used from process level)
 */
#define DIO_FREE(d)	\
	xmfree(((struct dio *)(d))->dvec, pinned_heap)

#ifndef __64BIT_KERNEL
/*
 * Initialize a 64-bit DIO structure
 *	**USED WHEN 64-bit INTERFACES ARE SELECTED...SEE DMA_ENABLE_64**
 *		DIO_INIT_64(struct dio_64 *d,	- pointer to dio struct 
 *			 int n_iovecs);         - number of iovecs 
 *		(Must only be used from process level)
 */
#define DIO_INIT_64(d, n_iovecs)	\
	{	((struct dio_64 *)(d))->dvec = (struct d_iovec_64 *)xmalloc( \
	  	   (sizeof(struct d_iovec_64) * (n_iovecs)), 2, pinned_heap);\
		if (((struct dio_64 *)(d))->dvec == NULL)		\
			((struct dio_64 *)(d))->total_iovecs = 0;	\
		else							\
			((struct dio_64 *)(d))->total_iovecs = n_iovecs; \
		((struct dio_64 *)(d))->used_iovecs = 0;		\
		((struct dio_64 *)(d))->bytes_done = 0;   		\
		((struct dio_64 *)(d))->resid_iov = 0;   		\
	}

/*
 * Free elements of a 64-bit DIO structure
 *	**USED WHEN 64-bit INTERFACES ARE SELECTED...SEE DMA_ENABLE_64**
 *		DIO_FREE_64(struct dio_64 *d)	- pointer to dio struct 
 *		(Must only be used from process level)
 */
#define DIO_FREE_64(d)	\
	xmfree(((struct dio_64 *)(d))->dvec, pinned_heap)

#endif /* ! __64BIT_KERNEL */


/*
 * Invoke the d_map_init service 
 */
#define D_MAP_INIT(bid, flags, bus_flags, channel)	\
                d_map_init(bid, flags, bus_flags, channel)

/*
 * Invoke the d_map_clear service for a specific bus type 
 */
#define D_MAP_CLEAR(handle)					\
                (handle->d_map_clear)(handle)

/*
 * Invoke the d_map_page service for a specific bus type 
 */
#define D_MAP_PAGE(handle, flags, baddr, busaddr, xmp)		\
                (handle->d_map_page)(handle, flags, baddr, busaddr, xmp)

/*
 * Invoke the d_unmap_page service for a specific bus type 
 */
#define D_UNMAP_PAGE(handle, bus_addr)				\
                if (handle->d_unmap_page != NULL)		\
                        (handle->d_unmap_page)(handle, bus_addr)

/*
 * Invoke the d_map_list service for a specific bus type 
 */
#define D_MAP_LIST(handle, flags, minxfer, virt_list, bus_list)		\
           (handle->d_map_list)(handle, flags, minxfer, virt_list, bus_list)

/*
 * Invoke the d_unmap_list service for a specific bus type 
 */
#define D_UNMAP_LIST(handle, bus_list)				\
                if (handle->d_unmap_list != NULL)		\
                        (handle->d_unmap_list)(handle, bus_list)

/*
 * Invoke the d_map_slave service for a specific bus type 
 */
#define D_MAP_SLAVE(handle, flags, minxfer, vlist, chan_flags)		\
           (handle->d_map_slave)(handle, flags, minxfer, vlist, chan_flags)

/*
 * Invoke the d_unmap_slave service for a specific bus type 
 */
#define D_UNMAP_SLAVE(handle)					\
                (handle->d_unmap_slave != NULL) ?		\
                        (handle->d_unmap_slave)(handle) : DMA_SUCC

/*
 * Invoke the d_map_disable service for a specific bus type 
 */
#define D_MAP_DISABLE(handle)					\
                (handle->d_map_disable)(handle)

/*
 * Invoke the d_map_enable service for a specific bus type 
 */
#define D_MAP_ENABLE(handle)					\
                (handle->d_map_enable)(handle)

/*
 * Invoke the d_sync_mem service for a specific bus type 
 */
#define D_SYNC_MEM(handle, bus_list)					\
                (handle->d_sync_mem != NULL) ?		\
                            (handle->d_sync_mem)(handle, bus_list) : DMA_SUCC

/*
 * Invoke the d_alloc_dmamem service
 */
#define D_ALLOC_DMAMEM	d_alloc_dmamem

/*
 * Invoke the d_free_dmamem service
 */
#define D_FREE_DMAMEM	d_free_dmamem

/****************************  RETURN CODES ******************************/
/*
* These are for the d_map_* services
*/
#define         DMA_FAIL        -1              /* error		*/
#define         DMA_SUCC        0               /* succesful completion */
#define         DMA_NOACC       	-2      /* page access violation   */
#define         DMA_NORES       	-3      /* resources exhausted     */
#define         DMA_DIOFULL     	-4      /* dio structure exhausted */
#define         DMA_TC_NOTREACHED       -5      /* terminal count ! reached*/
#define         DMA_BAD_MODE  		-6      /* unsupported mode setting*/
#define         DMA_R_FAIL    		-7      /* remote mapping failed */
#define         DMA_R_NORES   		-8      /* remote mapping failed due to
						 * duplicate mappings */
 
/****************************  MISC MACROS ******************************/
#define TCE_MAP_SIZE    4096    /* bytes */

/*************************  FUNCTION PROTOTYPES ******************************/
#ifndef _NO_PROTO

/*
 * Initialize a session with the DMA mapping services (non-microchannel)
 */
d_handle_t d_map_init(int bid, int flags, int bus_flags, uint channel);	
/* arguments:
 *	int bid;			bus type/number identifier
 *	int flags;			device capabilities
 *	int bus_flags;			flags specific to the target bus
 *	uint channel;			channel assignment specific to dev/bus
 */

#else 

d_handle_t d_map_init();		/* Initialize session */

#endif /* not _NO_PROTO */

#ifdef _KERNEL
/*******************  DYNAMIC RECONFIG AWARE DMA MAPPERS ********************/
/*
 * The following definitions, structures, and prototypes make up the various
 * components for a DMA Mapper, any entity that manages an I/O translation
 * layer (TCEs) and/or utilizes a physical address for the purpose of direct 
 * memory access, to register for and handle dynamic reconfiguration events 
 * corresponding to the removal and/or migration of physical memory.
 */

/*
 * DMA Mapper DR Event Handler Registration/Unregistration 
 */
typedef struct dr_dma_handler {
    struct dr_dma_handler *next;              /* list of dr_dma handlers      */
    struct dr_dma_handler *active;            /* active mapping list          */
					      /* event handler                */
    int     (*handler)(struct dr_dma_handler *drh, int event, ptr64 arg); 
    uint64_t   handler_data;                  /* handlers private data field  */
    uint64_t   dr_data1;		      /* data field for DR            */
    uint64_t   dr_data2;		      /* data field for DR            */
    uint64_t   dr_rsvd1;		      /* reserved                     */
    uint64_t   dr_rsvd2;		      /* reserved                     */
} dr_dma_handler_t;
/* dr_register_dma_mapperx flags
 */
#define DR_DMA_DRUNSAFE      0x1UL            /* mapper not DR-Safe           */
#define DR_DMA_ALLFLAGS      (DR_DMA_DRUNSAFE)

void dr_register_dma_mapper(dr_dma_handler_t *, rpn_t *);
int  dr_register_dma_mapperx(dr_dma_handler_t *, rpn_t *, ulong);
void dr_unregister_dma_mapper(dr_dma_handler_t *);
     
/*
 * DMA Handler Events and Structures          
 *  
 *  Event identifier and structure definition that "arg" can be cast to
 */
    
/*
 * Notification that memory remove is about to begin, or that it
 * is complete
 */
#define DR_DMA_RMLMB_START        0x1
#define DR_DMA_RMLMB_END          0x2
struct dr_dma_rmlmb {
    rpn_t   start;       /* starting RPN of memory range to be removed (input)*/
    rpn_t   end;         /* ending RPN (inclusive) of memory range (input)    */
    rpn_t   gencount;	 /* memory remove generation count */
}; 
      
/*
 * Query if a physical page is currently mapped for DMA
 * Returns count of mappings.
 * "arg" == RPN to query
 */
#define DR_DMA_RPN_QUERY           0x3 
    
/* 
 * Notification that migration of specified RPN is starting, and request
 * list of all active mappings for that RPN
 * Notification that physical page has been migrated (or aborted if new == old)
 */
#define DR_DMA_RPN_MIGRATE_START   0x4
#define DR_DMA_RPN_MIGRATE_END     0x5
#define DR_DMA_RPN_MAX_MAPPINGS	   256
struct dr_dma_mapping {
       	uint busnum;        /* logical bus#, ibm,dma-window property (output) */
       	uint hi;            /* high 4 bytes of io address (output) */
       	uint mid;           /* middle 4 bytes of io address (output) */
       	uint lo;            /* low 4 bytes of io address (output) */
};
struct dr_dma_rpn_migrate {   
    rpn_t   rpn;            /* rpn to migrate/query (input) */
    rpn_t   new_rpn;        /* new rpn after migrate (input) */
    int     table_entries;  /* number of table entries (input) */
    int     num_mappings;   /* number of mappings (output) */
    struct dr_dma_mapping *dma_tbl; /* table of dma mappings */
};

/****************************************************************************/
/*
 * Prototypes for non-exported internal DR DMA services
 */
#ifdef _KERNSYS

int dr_dma_rmlmb_start(rpn_t, rpn_t, rpn_t);
int dr_dma_rpn_query(rpn_t, int, int, int);
int dr_dma_migrate_rpn_start(rpn_t, rpn_t, int, int, int *);
int dr_dma_migrate_rpn(rpn_t, rpn_t, int, int, int);
void dr_dma_migrate_rpn_end(rpn_t, rpn_t, int, int);
void dr_dma_rmlmb_end(rpn_t, rpn_t);
int  dr_dma_drunsafe(void);

#endif /* _KERNSYS */
/****************************************************************************/

#endif /* _KERNEL */

#ifdef OBSOLETE_MCA_PREP /* See the "IMPORTANT NOTICE" above */

/****************************************************************************
 *			MCA Specific flags				    *
 ****************************************************************************/

/***********************  INITIALIZATION FLAGS ******************************/
/*
* These are the flag values specific to the d_init service. These flags must 
* each be unique with respect to each other.
*/
#define		DMA_BUS_MASK	0x0F		/* bus type mask	  */
#define		PC_AT_DMA	0x01		/* PC AT BUS		  */
#define		MICRO_CHANNEL_DMA 0x02		/* Micro channel bus      */
#define		DMA_BUS_MAX	0x02		/* largest valid bus	  */
#define		REGION_DMA	0x20		/* region mode  	  */
#define		BUFFERED_DMA	0x40		/* buffer DMA  RT PC only */

/****************************  SERVICE FLAGS ******************************/
/*	
* These are the flag values specific to the d_master/d_slave/d_complete 
* services.
*/
#define		DMA_VERIFY	0x200		/* don't write to memory  */
#define         DMA_PG_PROTECT  0x800           /* set if access violaton */
#define         DMA_CONTINUE    0x1000          /* continue mapping tags  */
						/* where previos d_slave  */
						/* finished */

/* Use with DMA_READ to prevent the page from being hidden.  Caller had
 * better be sure the buffer will not be accessed (load/store) between 
 * d_master/d_slave and d_complete.  This provides faster DMA setup.
 */
#define		DMA_NOHIDE	0x2000

/****************************  RETURN CODES ******************************/

/*
 * These are specific to the d_* services
 */
#define         DMA_CONFLICT    1               /* inconsistent flag val*/
#define         DMA_LIMIT       3               /* limit check		*/
#define         DMA_PAGE_FAULT  4               /* page fault		*/
#define         DMA_BAD_ADDR    5               /* invalid bus address	*/
#define         DMA_AUTHORITY   6               /* protection exception	*/
#define         DMA_INVALID     7               /* invalid operation    */
#define         DMA_EXTRA     	8               /* extra slave request  */
/*
*	All errors that have a return value greater than
*	DMA_RETRY are re-tryable.
*/
#define         DMA_RETRY       9
#define         DMA_DATA        10              /* data parity error	*/
#define         DMA_ADDRESS     11              /* address parity error */
#define         DMA_SYSTEM      12              /* system error		*/
#define         DMA_CHECK       13              /* channel check	*/
#define         DMA_MULTIPLE    14              /* multiple DMA errors  */
#define         DMA_NO_RESPONSE 15              /* no response		*/

#endif /* OBSOLETE_MCA_PREP */

#endif /* _H_DMA	*/
