/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/reboot.h 1.11                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)61	1.11  src/bos/kernel/sys/reboot.h, sysproc, bos530 9/23/03 13:13:02 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1989,2000
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */


#ifndef _H_REBOOT
#define _H_REBOOT

#define	RB_SOFTIPL	0
#define RB_HALT		1
#define RB_POWIPL	2
#define RB_HARDIPL	3
#define RB_HALT_POWERED	4
#define RB_UPDATE_FLASH	5
#define RB_PREPARE	6

/* 
 * This structure has been grown to accomodate the kernel part
 * of the operation to preallocate the block-list memory before
 * disabling and calling the PAL.
 *
 * The first structure is the origianl and is used for compatiblity
 * between reboot command and the kernel.
 *
 * The second structure is used between the kernel and the PAL.  The
 * first three elements of the structurs must match in order to
 * preserve compatibility.  Of course the second structure is protected
 * by the _kernel define to indicate it is a private structure to the
 * kernel and extension and should not be used by applications.
 */
typedef struct {
	caddr_t uf_strt_ptr;		/* Pointer to start of image */
	ulong   uf_img_len;		/* Length of image	     */
	void	*uf_xmem;		/* Pointer to cross mem desc */
} update_flash_t;

#ifdef _KERNSYS
/* structure used between the kernel and the PAL */
typedef struct {
	caddr_t uf_strt_ptr;	/* Pointer to start of image		*/
	ulong   uf_img_len;	/* Length of image	     		*/
	void	*uf_xmem;	/* Pointer to cross mem desc 		*/
	uint	uf_version;	/* version number of the structure	*/
	caddr_t	uf_bl_addr;	/* address block-list        		*/
	ulong	uf_bl_len;	/* block-list length in bytes 		*/
} update_flash_kp_t;

#define	UPDATE_FLASH_KP_VERSION	1

/* structures used to build update-flash block lists, both 32 & 64 bit */
typedef struct {
	uint    addr;
	uint    len;
} block_list_t;

typedef struct {
	unsigned long long     addr;
	unsigned long long     len;
} block_list_64_t;

/* update-flash  version 1 block-list overhead size */
#define UF64_V1_BL_OH   (sizeof(long long) * 2)
#define UF32_V1_BL_OH   (sizeof(int) * 2)


#endif

/* Shutdown notify */
typedef struct _shutdown_notify {
    struct _shutdown_notify 	*next;  	/* Next in the link-list */
    int				version;        /* Version of structure */
    int                 	oper;           /* Bit map of the operation  */
    						/*    being performed */
    int                 	status;         /* The current status of */
    						/*    this notify */
    int                 	padding;        /* padding */
    long                 	(*func)(struct _shutdown_notify *);	
    						/* Function kernel calls to */
    						/*    notify extension */
    void                	*uaddr;         /* Address to help extension
					   	 * identify the object this
						 * structure refers to
						 */
} shutdown_notify_t;

/* Valid values for shutdown_notify_t->oper */
#define SHUTDOWN_NOTIFY_PREPARE 0x1     /* Shutdown has started */
#define SHUTDOWN_NOTIFY_REBOOT  0x2     /* Final notify that shutdown 
						will be a reboot */
#define SHUTDOWN_NOTIFY_HALT    0x4     /* Final notify that shutdown 
						will be a halt */
#define SHUTDOWN_NOTIFY_QUERY   0x8     /* Check to see if finished shutdown */

/* Valid values for shutdown_notify_t->status and for SHUTDOWN_NOTIFY_QUERY 
 * return code
 */
#define SHUTDOWN_STATUS_PREPARE         0x1     /* Preparing for shutdown */
#define SHUTDOWN_STATUS_COMMENCE        0x2     /* Commencing shutdown */
#define SHUTDOWN_STATUS_FINISH          0x4     /* Finished shutdown */
            
#define SHUTDOWN_NOTIFY_VERSION		1   /* Increment by 1
					     * everytime add more
					     * variables to
					     * shutdown_notify_t
					     */

int shutdown_notify_reg(shutdown_notify_t *sn);
int shutdown_notify_unreg(shutdown_notify_t *sn);

#ifdef _KERNSYS

int shutdown_notify(int op_flag, shutdown_notify_t *sn);
void shutdown_notify_init();

/* op_flag passed into shutdown_notify() to indicate what operation 
 * to perform
 */
#define SHUTDOWN_NOTIFY_REGISTER        0
#define SHUTDOWN_NOTIFY_UNREGISTER      1

#define SHUTDOWN_NOTIFY_POLL_TIME	1000 /* in uSecs */

#endif /* _KERNSYS */

#ifdef _LINUX_SOURCE_COMPAT
extern int __linux_reboot(int);
#define reboot(a) __linux_reboot((a))

#define LINUX_REBOOT_CMD_RESTART RB_SOFTIPL
#define LINUX_REBOOT_CMD_HALT RB_HALT_POWERED
#define LINUX_REBOOT_CMD_POWER_OFF RB_HALT
#define LINUX_REBOOT_CMD_RESTART2 RB_POWIPL
#define LINUX_REBOOT_CMD_CAD_ON 90      /* AIX does not offer CAD reboot */
#define LINUX_REBOOT_CMD_CAD_OFF 91
#endif

#endif /* _H_REBOOT */
