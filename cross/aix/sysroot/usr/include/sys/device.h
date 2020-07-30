/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/sys/device.h 1.16.2.16                           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)10     1.16.2.16  src/bos/kernel/sys/device.h, sysios, bos53H, h2005_33B9 8/3/05 14:29:42 */

#ifndef _H_DEVICE
#define _H_DEVICE
/*
 * COMPONENT_NAME: (SYSIOS) Device Switch Table header file
 *
 * ORIGINS: 27, 83
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 *   LEVEL 1,  5 Years Bull Confidential Information
 */

#include <sys/types.h>
#include <sys/file.h>
#include <sys/sysmacros.h>
#include <sys/lockl.h>
#include <sys/intr.h>
#include <sys/low.h>
#include <sys/syspest.h>
#ifdef _POWER_MP
#include <sys/processor.h>
#ifdef _KERNSYS
#include <sys/m_types.h>
#include <sys/ppda.h>
#include <sys/proc.h>
#endif /* _KERNSYS */
#endif /* _POWER_MP */

#define	DEVCNT	1024		/* # of entries in device switch tbl	*/

#ifdef __cplusplus
struct tty;
#endif

/*
   Device Switch Table entry structure.
 */
struct devsw
{
	int	(*d_open)();	/* entry point for open routine		*/
	int	(*d_close)();	/* entry point for close routine	*/
	int	(*d_read)();	/* entry point for read routine		*/
	int	(*d_write)();	/* entry point for write routine	*/
	int	(*d_ioctl)();	/* entry point for ioctl routine	*/
	int	(*d_strategy)();/* entry point for strategy routine	*/
	struct tty	*d_ttys;/* pointer to tty device structure	*/
	int	(*d_select)();	/* entry point for select routine	*/
	int	(*d_config)();	/* entry point for config routine	*/
	int	(*d_print)();	/* entry point for print routine	*/
	int	(*d_dump)();	/* entry point for dump routine		*/
	int	(*d_mpx)();	/* entry point for mpx routine		*/
	int	(*d_revoke)();	/* entry point for revoke routine	*/
	caddr_t	d_dsdptr;	/* pointer to device specific data	*/
	/*
	 *	The following entries are control fields managed
	 *	by the kernel and should not be modified by device
	 *	drivers or kernel extensions.  They may be set to
	 *	0 in the devsw structure for devswadd(), since they
	 *	are not copied into the device switch table.
	 */
	caddr_t	d_selptr;	/* ptr to outstanding select cntl blks	*/
	ulong	d_opts;		/* internal device switch control field	*/
};

/* d_opts flags */
#define DEV_NOT_DEFINED		0x0
#define DEV_DEFINED		0x2
#define	CONS_DEFINED		0x4	/* Console defined flag in d_opts */
#define	DEV_MPSAFE		0x8	/* MP safe device driver	  */
#ifndef DEV_64BIT
#define DEV_64BIT		0x10	/* driver understands 64-bit apps */
#endif
#ifdef __ia64
#define DEV_64L			DEV_64BIT /* driver understands 64-l apps */
#else
#define DEV_64L			0x20	/* driver understands 64-l apps */
#endif
#define	DEV_MEM			0x40	/* device is a memory device */
#define DEV_LAZYTIMES	0x80	/* timestamp update less frequent */
#define DEV_EXTBUF	0x100		/* Driver is bufx aware */

extern struct devsw	*devsw;

#define DSW_UNDEFINED	0x0	/* dev. switch entry not defined	*/
#define DSW_CREAD	0x1	/* dd supports char/raw reads		*/
#define DSW_CWRITE	0x2	/* dd supports char/raw writes		*/
#define DSW_BLOCK	0x4	/* dev. switch entry in use by block dd	*/
#define DSW_TTY		0x8	/* dev. switch entry in use by TTY dd	*/
#define DSW_SELECT	0x10	/* dd supports select or poll sys. call	*/
#define DSW_DUMP	0x20	/* supports device's dump target	*/
#define DSW_MPX		0x40	/* dev. switch entry in use by mpx dd	*/
#define DSW_TCPATH	0x80	/* supports Trusted Comp.Path revoke service*/
#define DSW_OPENED	0x100	/* dev. switch entry in use w/ >=1 open	*/
#define DSW_DEFINED	0x200	/* dev. switch entry in use		*/
#define DSW_CONSOLE	0x400	/* Entry is static console driver 	*/
#define DSW_CONFIG	0x800	/* dev. switch entry in use by config */
#define DSW_MEM		0x1000	/* if DEV_MEM is set in d_opts */
#define DSW_LAZYTIMES	0x2000	/* if DEV_LAZYTIMES is set in d_opts */

/*
 * Common commands provided by the device driver's ddconfig entry point.
 */
#define	CFG_INIT	0x1	/* init. the dd and internal data areas	*/
#define	CFG_TERM	0x2	/* terminate the dd 			*/
#define	CFG_QVPD	0x3	/* request dev. specific vital product data */
#define CFG_UCODE       0x4     /* download microcode to kernel device  */
#define CFG_PARTITIONS  0x5     /* download media partition info to dd  */
#define CFG_MPIO        0x6     /* MPIO path control command            */

/*
 * Device flags provided to the ddopen and ddioctl
 * entry points for device drivers.
 */
#define	DKERNEL	FKERNEL		/* ddopen/ddioctl called from within kernel*/
#define	DREAD	FREAD		/* device is open for reading		*/
#define	DWRITE	FWRITE		/* device is open for writing		*/
#define	DAPPEND	FAPPEND		/* device is open for appending		*/
#define	DNDELAY	(FNDELAY|FNONBLOCK) /* device is open in non-blocking mode */
#define	DMOUNT	FMOUNT		/* device is open for mounting 		*/
#define	DNOCTTY FNOCTTY		/* do not assign control tty		*/
#define DDOCLONE FDOCLONE	/* do a clone open for streams		*/
#define	DMASK	(DKERNEL|DREAD|DWRITE|DAPPEND|DNDELAY|DNOCTTY)

/*
 * Command flags for dddump routine.
 */
#define	DUMPINIT	0x1	/* dump dev. selected for dump		*/
#define	DUMPSTART	0x2	/* sys.dump being initiated to this dev.*/
#define	DUMPWRITE	0x3	/* cmd to write dump data to the dev.	*/
#define	DUMPEND		0x4	/* all dump data has been sent to the dev*/
#define	DUMPTERM	0x5	/* dev. no longer selected for a dump	*/
#define	DUMPQUERY	0x6	/* return blksize requirements for this dev.*/
#define	DUMPREAD	0x7	/* cmd to signal the network dump device    */
                                /* to start polling within a timeout period.*/


/* flags for filesystem invocation of the DD_ENT macro */
#define IPRI_BASE 	0
#define IPRI_OTHER	1
#define IPRI_NOPREMPT	2
#define DD_SETJMP	3

#ifdef _KERNSYS
/*
 * The DD_ENT macro is used by the file system when calling device driver
 * entry points.  This macro is not to be used by device drivers!!!
 */
#if !defined(_POWER_MP) || defined(__64BIT_KERNEL)

#define FUNNEL_START(major,flag)

#define FUNNEL_END(major)	

#else

#define FUNNEL_START(major,flag)				\
{								\
	label_t		funnel_jmpb;				\
	int		rv;					\
	int		setfunnel;				\
	int		setjmpset;				\
	volatile int	wasfunneled=0;				\
								\
	setfunnel = (!(devsw[(major)].d_opts & DEV_MPSAFE) &&	\
		(curcsa->prev == NULL) &&			\
		(curcsa->intpri == INTBASE));			\
	if (setfunnel)						\
		wasfunneled =					\
		   switch_cpu(MP_MASTER, SET_PROCESSOR_ID);	\
	setjmpset = ((flag & DD_SETJMP) && setfunnel);		\
	if (setjmpset) {					\
		if ( rv = setjmpx(&funnel_jmpb)) {		\
		  if (setfunnel && !wasfunneled)		\
		    switch_cpu(0,RESET_PROCESSOR_ID);		\
		  longjmpx(rv);					\
		}						\
	};

#define FUNNEL_END(major)					\
	if (setjmpset) {					\
		clrjmpx(&funnel_jmpb);				\
	};							\
	if (setfunnel && !wasfunneled) {			\
		switch_cpu(0, RESET_PROCESSOR_ID);		\
	}							\
}
#endif /* !_POWER_MP || __64BIT_KERNEL */

#define DD_ENT(rc,ddcall,flag,major)                            \
{                                                               \
        void specfs_intsdisabled(int, int, char *);             \
        int waslocked;                                          \
        int tmpipri, tmprc;                                     \
        struct kmstsave *curcsa;                                \
                                                                \
        curcsa = CSA;                                           \
        if (waslocked = ((curcsa->prev == NULL) &&              \
                IS_LOCKED(&kernel_lock) && !(flag & IPRI_NOPREMPT))) \
                unlockl(&kernel_lock);                          \
        if (flag & IPRI_OTHER) {                                \
                tmpipri = curcsa->intpri;                       \
        }                                                       \
        else  {                                                 \
                tmpipri = INTBASE;                              \
                ASSERT(curcsa->intpri == INTBASE);              \
        };                                                      \
        FUNNEL_START(major,flag)                                \
        /* Because we need the return code, the way this macro  \
         * was coded before is inconvenient. What used to be    \
         * expanded as "(void)ddcall" now gets turned into      \
         * "(void)trc" which the compiler optimizes away. If    \
         * the caller wants the return code, "rc = trc" works   \
         * just as well.                                        \
         */                                                     \
        tmprc = ddcall;                                         \
        rc tmprc;                                               \
        FUNNEL_END(major)                                       \
        if ((curcsa->intpri != tmpipri))                        \
        {                                                       \
                /* Log error and halt system.                   \
                 * The preprocessor expands the #ddcall token   \
                 * to "what_was_passed_to_macro."               \
                 */                                             \
                specfs_intsdisabled(major,tmprc,#ddcall);       \
        }                                                       \
        if (waslocked)                                          \
                lockl(&kernel_lock, LOCK_SHORT);                \
}
#endif /* _KERNSYS */

#ifndef _NO_PROTO

int	devswadd(
	dev_t devno,
	struct devsw *dswptr);
/* arguments:
 *	dev_t		devno;		device# (maj/minor) of entry to add
 *	struct devsw	*dswptr;	address of device switch information
 */

int	devswdel(
	dev_t devno);
/* arguments:
 *	dev_t		devno;		device# (maj/minor) of entry to delete
 */

int	devswqry(
	dev_t devno,
	uint *status,
	caddr_t *dsdptr);
/* arguments:
 *	dev_t		devno;		device# (maj/minor) of entry to query
 *	uint		*status;	address of device status
 *	caddr_t		*dsdptr;	address of device dependent information
 */

int	devswchg(
	dev_t devno,
	int type,
	int (*newfunc)(),
	int (**oldfunc)());
/* arguments:
 *	dev_t		devno;		device# (maj/minor) of entry to query
 *	int		type;		entry point to change
 *	int		(*newfunc)();	value for new entry
 *	int		(**oldfunc)();	value for old function returned here
 */

#else

int	devswadd();
/* arguments:
 *	dev_t		devno;		device# (maj/minor) of entry to add
 *	struct devsw	*dswptr;	address of device switch information
 */

int	devswdel();
/* arguments:
 *	dev_t		devno;		device# (maj/minor) of entry to delete
 */

int	devswqry();
/* arguments:
 *	dev_t		devno;		device# (maj/minor) of entry to query
 *	uint		*status;	address of device status
 *	struct devsw	*dswptr;	address of device switch information
 */

int	devswchg();
/* arguments:
 *	dev_t		devno;		device# (maj/minor) of entry to query
 *	int		type;		entry point to change
 *	int		(*newfunc)();	value for new entry
 *	int		(**oldfunc)();	value for old function returned here
 */

#endif /* not _NO_PROTO */

#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)

int nodev(void);		/* for illegal entries in devsw table */
int nulldev(void);		/* for insignificant entries in devsw table */

/* routines for accessing devices through the device switch */
extern int devstrat(struct buf *bp);	/* call device strategy routine */

extern int devdump(			/* call device dump routine 	*/
	dev_t		devno,          /* dev num of device to write   */
	struct uio *	uiop,           /* write location information   */
	int		cmd,		/* dump command			*/
	int32long64_t	arg,		/* address of parameter block	*/
	chan_t		chan,           /* device channel number        */
	ext_t		ext);		/* extension parameter		*/

extern int devwrite(			/* call device write routine 	*/
	dev_t		devno,		/* dev num of device to write   */
	struct uio *	uiop,		/* write location information   */
	chan_t		chan,		/* device channel number        */
	ext_t		ext);		/* extended write parameter     */



#endif /* (__64BIT_KERNEL) || (__FULL_PROTO) */

#endif	/* _H_DEVICE */
