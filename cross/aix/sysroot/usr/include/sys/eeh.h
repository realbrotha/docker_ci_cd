/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/eeh.h 1.19.1.4                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1999,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)23     1.19.1.4  src/bos/kernel/sys/eeh.h, sysios, bos53X, x2010_01B4 10/30/09 11:40:06 */


/*

   The EEH kernel services has been implemented in two phases. The first
   phase concerned only single function adapters. Most of the EEH services
   were implemented in the first phase. The second implementation is for
   multi-function adapter support which also included adapters with an
   integrated bridge controller. In order to support multi-function adapters
   a state machine was devised to assist in coordination among the drivers
   on a multi-function adapter. A EEH_MASTER driver is chosen from among the
   drivers on the adapter to drive the states involved in handling an EEH
   event. This coordination allows only one device driver on the adapter, the
   EEH_MASTER to issue the reset instead of all the drivers attempting resets.

   EEH Event States for multi-function adapters:

                ---------------------
   ------------>| NORMAL_EE_STATE   |
   |            ---------------------
   |                    |
   |                    |
   |    eeh event       |
   |    RTAS eeh_read_slot_state
   |                    |
   |                    |-----------
   |                    |          |
   |                    |          V
   |                    |   RTAS eeh_slot_error ---------
   |                    |          |                    |
   |                    |<----------                    |
   |                    |                               |
   |                    |                               |
   |                    V                               |
   |            ---------------------                   |
   |            | SUSPEND_STATE     |                   |
   |            ---------------------                   |
   |                    |                               |
   |                    |                               |
   |    eeh_broadcast(EEH_DD_SUSPEND)                   |
   |                    |                               |
   |                    |                               |
   |                    |--------------			|
   |                    |	      |			|
   |                    |             V			|
   |                    |      -----------------	|
   |                    |      | BUSY_STATE    |	|
   |                    |      -----------------	|
   |                    |             |			|
   |                    |<-------------			|
   |                    |                               |
   |  |-----------------|                               |
   |  |                 |                               |
   |  | --------------->|                               |
   |  | |               |                               |
   |  | |    RTAS eeh_enable_pio/eeh_enable_dma         |
   |  | |               |                               |
   |  | |               |-----------                    |
   |  | |               |          |                    |
   |  | |               |          V                    V
   |  | |               |   RTAS eeh_slot_error ---------
   |  | |               |          |                    |
   |  | |               |<----------                    |
   |  | |               |                               |
   |  | |               |                               |
   |  | |               V                               |
   |  | |        ---------------------                  |
   |  | |        | DEBUG_STATE       |                  |
   |  | |        ---------------------                  |
   |  | |               |                               |
   |  | |   eeh_broadcast(EEH_DD_DEBUG)                 |
   |  | |               |                               |
   |  | ----------------|                               |
   |  |                 |                               |
   |  |                 |                               |
   |  |---------------->|                               |
   |                    |                               |
   |    RTAS eeh_reset_slot (EEH_ACTIVE)                |
   |                    |                               V
   |                    |--------------------------------
   |                    V                               |
   |            ---------------------                   |
   |            | ACTIVATE_STATE    |                   |
   |            ---------------------                   |
   |                    |                               |
   |                    |                               |
   |    trb suspend 100ms                               V
   |    RTAS eeh_reset_slot (EEH_DEACTIVE)            --------------
   |                    |                             |            |
   |                    |---------------------------->| DEAD_STATE |
   |                    V                             |            | 
   |            ---------------------                 --------------
   |            | DEACTIVATE_STATE  |                   ^ eeh_broadcast(
   |            ---------------------                   |        EEH_DD_DEAD)
   |                    |                               |
   |                    |                               |
   |    trb suspend dd time (default 1 sec)             |
   |                    |                               |
   |                    |                               |
   | eeh_broadcast      |                               |
   |    (EEH_DD_RESUME) V                               |
   |<--------------------                               |
   |                    |                               |
   |    RTAS configure-bridge                           |
   |                    |                               |
   |                    |-------------------------------|
   |                    |                               
   | eeh_broadcast      |
   |    (EEH_DD_RESUME) V
   ----------------------


*/


/*
 * Flags for eeh_init() and eeh_init_multifunc()
 */
#define	EEH_ENABLE			0x0
#define	EEH_DISABLE			0x1
#define EEH_CHECK_SLOT			0x2
#define EEH_ENABLE_NO_SUPPORT_RC	0x4

/*
 * Flags on eeh_slot_error()
 */
#define EEH_RESET_TEMP		0x1
#define EEH_RESET_PERM		0x2	/* also used with eeh_reset_slot() */
#define EEH_INTERNAL_FAIL	0x80	/* only for IBM internal use */

/*
 * Flags on eeh_reset_slot()
 * Only the following combinations of flags are valid on eeh_reset_slot()
 *  o EEH_DEACTIVE (0x0)
 *  o EEH_ACTIVE (0x1)
 *  o EEH_FUNDAMENTAL_RESET (0x4)
 *  o EEH_ACTIVE | EEH_UNCONDITIONAL_RESET (0x8001)
 *  o EEH_FUNDAMENTAL_RESET | EEH_UNCONDITIONAL_RESET (0x8004)
 *  o EEH_RESET_PERM (0x2)
 *  o EEH_RESET_PERM | EEH_ACTIVE (0x3)
 */
#define EEH_DEACTIVE		0x0
#define EEH_ACTIVE		0x1
#define EEH_FUNDAMENTAL_RESET	0x4  /* only valid with PCI-E devices */
#define EEH_UNCONDITIONAL_RESET	0x8000

/*
 * Returns
 */
#define EEH_FAIL		-1
#define	EEH_NO_SUPPORT		0x0
#define EEH_SUCC		0x1 
#define EEH_SLOT_ACTIVE		0x2 
#define EEH_SLOT_FREE 		0x3 
#define EEH_BUSY 		0x4 

/*
 * Reset States returned from eeh_read_slot_state
 */
#define	EEH_NSTOPPED_RST_DEA	0x0
#define	EEH_NSTOPPED_RST_ACT	0x1
#define	EEH_STOPPED_LS_DIS	0x2
#define	EEH_STOPPED_LS_ENA	0x4
#define	EEH_UNAVAILABLE		0x5

/*
 * EEH States for controlling multifunction adapters
 */
#define NORMAL_EEH_STATE		0x0
#define SUSPEND_STATE			0x1
#define SUSPEND_STATE_LS_ENA		0x2
#define DEBUG_STATE			0x3
#define ACTIVATE_STATE			0x4
#define DEACTIVATE_STATE		0x5
#define DEAD_STATE			0x6
#define BUSY_EEH_STATE			0x7
#define RESUME_EEH_STATE		0x8
#define BUSY_DEAD_STATE			0x9
#define RESUME_DEAD_STATE		0xA
#define TEMP_UNAVAIL_STATE		0xB
#define RESUME_TEMP_UNAVAIL_STATE	0xC
#define SUSPEND_RESET_STATE		0xD
#define DEBUG_RESET_STATE		0xE
#define TEMP_FWRESET_STATE		0xF
#define RESUME_TEMP_FWRESET_STATE	0x10

/*
 * Flag values in callback
 */
#define EEH_MASTER		0x01
#define EEH_DD_PIO_ENABLED	0x40
#define EEH_DD_DMA_ENABLED	0x80

/*
 * EEH kernel services defined messages (up to 32 bits)
 */
#define EEH_DD_RESUME		0x00800000ULL	/* sent last */
#define EEH_DD_DEACTIVE		0x01000000ULL
#define EEH_DD_DEBUG		0x02000000ULL
#define EEH_DD_ACTIVE		0x04000000ULL
#define EEH_DD_SUSPEND		0x08000000ULL
#define EEH_DD_DEAD		0x80000000ULL	/* sent first */

/*
 * Device Driver defined messages (starting at bit 0 up to bit 31)
 * For example, 
 * #define EEH_DD_USR1	0x4000000000000000ULL
 */


/*
 * General defines
 */
#define NMULTIDD		7
#define EEH_SAFE		0x2 
#define EEH_CONFIGURE		0x3 

/*
 * This is the eeh_handle structure for the eeh_* services
 */
typedef struct eeh_handle *       eeh_handle_t;
struct eeh_handle {
	struct	eeh_handle *next;
	long	bid;			/* bus id passed to eeh_init	*/
	long	slot;			/* slot passed to eeh_init	*/
	long	flag;			/* flag passed to eeh_init	*/
	int	config_addr;		/* Configuration Space Address	*/
	int	eeh_mode;		/* Indicates safe mode		*/
	uint	retry_delay;		/* re-read the slot state after *
					 * these many seconds.		*/
	int	reserved1;
	int	reserved2;     
	int	reserved3;     
	long long	PHB_Unit_ID;	/* /pci@<Unit_ID>		*/
	void	(*eeh_clear)(eeh_handle_t);
	long	(*eeh_enable_pio)(eeh_handle_t);
	long	(*eeh_enable_dma)(eeh_handle_t);
	long    (*eeh_reset_slot)(eeh_handle_t, int);
	long	(*eeh_enable_slot)(eeh_handle_t);
	long	(*eeh_disable_slot)(eeh_handle_t);
	long	(*eeh_read_slot_state)(eeh_handle_t, long *, long *);
	long    (*eeh_slot_error)(eeh_handle_t, int, char *, long);
	struct eeh_shared_domain *parent_sd;	/* point back to the parent 
					 * shared domain structure if
					 * in shared domain, NULL if singlefunc.
					 */
	void    (*eeh_configure_bridge)(eeh_handle_t);
	void	(*eeh_broadcast)(eeh_handle_t, unsigned long long);
};




/* define macros for eeh services */
#define EEH_INIT(bid, slot, flag)	\
	eeh_init(bid, slot, flag)

#define EEH_INIT_MULTIFUNC(bid, bid2, slot, flag, delay_seconds, callback_ptr, dds_ptr)	\
	eeh_init_multifunc(bid, bid2, slot, flag, delay_seconds, callback_ptr, dds_ptr)

#define EEH_CLEAR(handle)		\
	(handle->eeh_clear)(handle)

#define EEH_ENABLE_PIO(handle)		\
	(handle->eeh_enable_pio)(handle)

#define EEH_ENABLE_DMA(handle)		\
	(handle->eeh_enable_dma)(handle)

#define EEH_RESET_SLOT(handle, flag)	\
	(handle->eeh_reset_slot)(handle, flag)

#define EEH_SLOT_ERROR(handle, flag, dd_buf, dd_buf_length)	\
	(handle->eeh_slot_error)(handle, flag, dd_buf, dd_buf_length)

#define EEH_ENABLE_SLOT(handle)		\
	(handle->eeh_enable_slot)(handle)

#define EEH_DISABLE_SLOT(handle)	\
	(handle->eeh_disable_slot)(handle)

#define EEH_READ_SLOT_STATE(handle, state, support)	\
	(handle->eeh_read_slot_state)(handle, state, support)

#define EEH_BROADCAST(handle, msg)	\
	(handle->eeh_broadcast)(handle, msg)


/*************************  FUNCTION PROTOTYPES ******************************/
#ifndef _NO_PROTO

/* PCI EEH multi-adapter init routine */
eeh_handle_t eeh_init_multifunc(long bid,
					long bid2,
					long slot,
					long flag,
					long delay_seconds,
					long (*callback_ptr)(),
					void *dds_ptr);
/*
 * Arguments:
 *	long bid	Bus id
 *	long bid2	Parent bus bridge id
 *	long slot	Device slot
 *	long flag	Flag that enables eeh
 *	long delay_seconds  Time to delay before config bridge
 *	long (*callback_ptr)() Pointer to callback routine
 *	void *dds_ptr	DD suplied pointer
 */

/* PCI EEH multi-adapter init routine */
eeh_handle_t eeh_init_multifunc_pci(long bid,
					long bid2,
					long slot,
					long flag,
					long delay_seconds,
					long (*callback_ptr)(),
					void *dds_ptr);
/*
 * Arguments:
 *	long bid	Bus id
 *	long bid2	Parent bus bridge id
 *	long slot	Device slot
 *	long flag	Flag that enables eeh
 *	long delay_seconds  Time to delay before config bridge
 *	long (*callback_ptr)() Pointer to callback routine
 *	void *dds_ptr	DD suplied pointer
 */

/* PCI EEH single adapter init routine  */
eeh_handle_t eeh_init(long bid, long slot, long flag);
/*
 * Arguments:
 *	long bid	Bus id
 *	long slot	Device slot
 *	long flag	Flag that enables eeh
 */

/* PCI EEH single adapter init routine  */
eeh_handle_t eeh_init_pci(long bid, long slot, long flag);
/*
 * Arguments:
 *	long bid	Bus id
 *	long slot	Device slot
 *	long flag	Flag that enables eeh
 */

/* DD suplied callback routine          */
long eeh_callback(unsigned long long cmd, void *arg, unsigned long flag);
/*
 * Arguments:
 *	unsigned long long cmd	EEH state commands or messages
 *	void *arg	Pointer to dd defined argument
 *	long flag	DD defined flag
 */

/* Coordinates activities between dd's  */
void eeh_broadcast(eeh_handle_t handle, unsigned long long msg);
/*
 * Arguments:
 *	eeh_handle_t handle	EEH handle for calling driver
 *	unsigned long long msg		EEH bit map message
 */


#else

eeh_handle_t eeh_init();	/* PCI EEH single adapter init routine	*/
eeh_handle_t eeh_init_pci();	/* PCI EEH single adapter init routine	*/
long eeh_callback();		/* DD suplied callback routine		*/
void eeh_broadcast();		/* Coordinates activities between dd's	*/
eeh_handle_t eeh_init_multifunc_pci(); /* Multi-adapter init routine	*/
eeh_handle_t eeh_init_multifunc(); /* Multi-adapter init routine */

#endif /* not _NO_PROTO */
/* End of eeh.h */

