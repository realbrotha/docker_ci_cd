/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53S src/bos/kernel/sys/skeys.h 1.4.1.1                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2005,2008              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)21     1.4.1.1  src/bos/kernel/sys/skeys.h, sysras, bos53S, s2008_33C3 7/18/08 09:26:52 */
/*
 * COMPONENT_NAME: (sysras) Storage Keys Information
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 */


#ifndef _H_SKEYS
#define _H_SKEYS

#if defined(__KDB) || defined(_KERNEL)
typedef unsigned int kkey_t;		/* individual kernel key */
typedef unsigned long long hkeyset_t;	/* hardware keyset (amr value) */
typedef struct kkeyset *kkeyset_t;	/* kernel keyset */
#endif

#ifdef _KERNEL
#include <sys/ras.h>			/* INVALID_PTR, kerrno_t from ras.h */

#define KKEYSET_INVALID ((kkeyset_t)INVALID_PTR(0x4b534554))	/* "KSET" */

#ifdef __64BIT_KERNEL
kerrno_t kkeyset_create(kkeyset_t *set);
kerrno_t kkeyset_delete(kkeyset_t set);

kerrno_t kkeyset_add_key(kkeyset_t set, kkey_t key, unsigned long flags);
kerrno_t kkeyset_remove_key(kkeyset_t set, kkey_t key, unsigned long flags);
	/*
	 * The flags values above are deliberately given very large
	 * values so that they will never be possible kernel key values.
	 * This is necessary for kkeyset_add_keys/kkeyset_remove_keys.
	 */
#define KA_READ		0x10000000	/* specifies read access to the key */
#define KA_WRITE	0x20000000	/* specifies write access to the key */
#define KA_RW		(KA_READ|KA_WRITE)

kerrno_t kkeyset_add_set(kkeyset_t set, kkeyset_t addset);
kerrno_t kkeyset_remove_set(kkeyset_t set, kkeyset_t removeset);
kerrno_t kkeyset_to_hkeyset(kkeyset_t kset, hkeyset_t *hset);

hkeyset_t hkeyset_add(hkeyset_t keyset);
hkeyset_t hkeyset_replace(hkeyset_t keyset);
void hkeyset_restore(hkeyset_t keyset);
hkeyset_t hkeyset_get(void);

kerrno_t hkeyset_update_userkeys(hkeyset_t *oldset);
kerrno_t hkeyset_restore_userkeys(hkeyset_t set);

kerrno_t kkey_assign_private(char *id, long instance,
				unsigned long flags, kkey_t *kkey);
#else /* __64BIT_KERNEL */

#define kkeyset_create(x)		0
#define kkeyset_delete(x)		0
#define kkeyset_add_key(x,y,z)		0
#define kkeyset_remove_key(x,y,z)	0
#define kkeyset_add_set(x,y)		0
#define kkeyset_remove_set(x,y)		0
#define kkeyset_to_hkeyset(x,y)		0
#define hkeyset_add(x)			0
#define hkeyset_replace(x)		0
#define hkeyset_restore(x)
#define hkeyset_get()			0
#define hkeyset_update_userkeys(x)	0
#define hkeyset_restore_userkeys(x)	0
#define kkey_assign_private(w,x,y,z)	0

#endif /* __64BIT_KERNEL */

#define HKEYSET_GLOBAL (0ull)	/* accesses all kernel and user hkeys */
#define HKEYSET_INVALID 0xffffffffffffffffull	/* accesses no hkeys */

/*
 * The structure kernel_keysets contains all the predefined kkeysets,
 * and is exported to kernel extensions.
 * Each predefined kkeyset should be referenced using the macros following.
 */
struct export_keysets {
	kkeyset_t	global_keyset;
	kkeyset_t	global_keyset_read;
	kkeyset_t	legacy_kernext_keyset;
	kkeyset_t	legacy_kernext_keyset_read;
	kkeyset_t	kernext_keyset;
	kkeyset_t	kernext_keyset_read;
	kkeyset_t	commo_kernext_keyset;
	kkeyset_t	commo_kernext_keyset_read;
	kkeyset_t	block_kernext_keyset;
	kkeyset_t	block_kernext_keyset_read;
	kkeyset_t	graphics_kernext_keyset;
	kkeyset_t	graphics_kernext_keyset_read;
	kkeyset_t	usb_kernext_keyset;
	kkeyset_t	usb_kernext_keyset_read;
	kkeyset_t	userdata_keyset;
	kkeyset_t	userdata_keyset_read;
};
extern struct export_keysets kernel_keysets;

/*
 * KKEYSET_NUM_PREDEFINED is used to loop through all these things
 * to initialize them conveniently.
 */
#ifdef _KERNSYS
#define KKEYSET_NUM_PREDEFINED	(sizeof(kernel_keysets) / sizeof(kkeyset_t))
#endif

#define	KKEYSET_GLOBAL		(kernel_keysets.global_keyset)
#define	KKEYSET_GLOBAL_READ	(kernel_keysets.global_keyset_read)
#define	KKEYSET_LEGACY		(kernel_keysets.legacy_kernext_keyset)
#define	KKEYSET_LEGACY_READ	(kernel_keysets.legacy_kernext_keyset_read)
#define	KKEYSET_KERNEXT		(kernel_keysets.kernext_keyset)
#define	KKEYSET_KERNEXT_READ	(kernel_keysets.kernext_keyset_read)
#define	KKEYSET_COMMO		(kernel_keysets.commo_kernext_keyset)
#define	KKEYSET_COMMO_READ	(kernel_keysets.commo_kernext_keyset_read)
#define	KKEYSET_BLOCK		(kernel_keysets.block_kernext_keyset)
#define	KKEYSET_BLOCK_READ	(kernel_keysets.block_kernext_keyset_read)
#define	KKEYSET_GRAPHICS	(kernel_keysets.graphics_kernext_keyset)
#define	KKEYSET_GRAPHICS_READ	(kernel_keysets.graphics_kernext_keyset_read)
#define	KKEYSET_USB		(kernel_keysets.usb_kernext_keyset)
#define	KKEYSET_USB_READ	(kernel_keysets.usb_kernext_keyset_read)
#define	KKEYSET_USERDATA	(kernel_keysets.userdata_keyset)
#define	KKEYSET_USERDATA_READ	(kernel_keysets.userdata_keyset_read)

#endif /* _KERNEL  */
#if defined(__KDB) || defined(_KERNEL)

/*
 *	Define values for each kernel key here.  They needn't be in any
 *	special order, and it is OK for values to be skipped.
 *
 *	If you add a new kkey here:
 *
 *	  - The name must begin with "KKEY_"
 *
 *	  - A line must be added to the mapping table in kkeys_init_mapping
 *	    to assign a mapping to the new kkey.  Most likely, you will
 *	    simply find an appropriate location (row) in the table for it,
 *	    and the HKEY_TAB "bump" characters will all be "|" to inherit
 *	    the hardware key from the immediately preceeding entry.
 *
 *	The first key *must* be numbered 0, and the numbering assignments
 *	must never be forced backwards.  (It is possible to bump the
 *	next number forwards, leaving a hole in the scheme, but why bother?)
 *	This ensures uniqueness, and that NUM_KKEYS is properly determined.
 *
 *	     012345678901234	<-- only these 15 chars saved for printing
 */
enum kkeys {
	KKEY_UPUBLIC = 0,
	KKEY_UPRIVATE1,
	KKEY_UPRIVATE2,
	KKEY_UPRIVATE3,
	KKEY_UPRIVATE4,
	KKEY_UPRIVATE5,
	KKEY_UPRIVATE6,
	KKEY_UPRIVATE7,
	KKEY_UPRIVATE8,
	KKEY_UPRIVATE9,
	KKEY_UPRIVATE10,
	KKEY_UPRIVATE11,
	KKEY_UPRIVATE12,
	KKEY_UPRIVATE13,
	KKEY_UPRIVATE14,
	KKEY_UPRIVATE15,
	KKEY_UPRIVATE16,
	KKEY_UPRIVATE17,
	KKEY_UPRIVATE18,
	KKEY_UPRIVATE19,
	KKEY_UPRIVATE20,
	KKEY_UPRIVATE21,
	KKEY_UPRIVATE22,
	KKEY_UPRIVATE23,
	KKEY_UPRIVATE24,
	KKEY_UPRIVATE25,
	KKEY_UPRIVATE26,
	KKEY_UPRIVATE27,
	KKEY_UPRIVATE28,
	KKEY_UPRIVATE29,
	KKEY_UPRIVATE30,
	KKEY_UPRIVATE31,

	KKEY_FILE_DATA,
	KKEY_PUBLIC,
	KKEY_BLOCK_DEV,
	KKEY_FILE_SYSTEM,
	KKEY_COMMO,
	KKEY_MBUF,
	KKEY_USB,
	KKEY_GRAPHICS,
	KKEY_DMA,
	KKEY_TRB,
	KKEY_IOMAP,

	KKEY_PRIVATE1,
	KKEY_PRIVATE2,
	KKEY_PRIVATE3,
	KKEY_PRIVATE4,
	KKEY_PRIVATE5,
	KKEY_PRIVATE6,
	KKEY_PRIVATE7,
	KKEY_PRIVATE8,
	KKEY_PRIVATE9,
	KKEY_PRIVATE10,
	KKEY_PRIVATE11,
	KKEY_PRIVATE12,
	KKEY_PRIVATE13,
	KKEY_PRIVATE14,
	KKEY_PRIVATE15,
	KKEY_PRIVATE16,
	KKEY_PRIVATE17,
	KKEY_PRIVATE18,
	KKEY_PRIVATE19,
	KKEY_PRIVATE20,
	KKEY_PRIVATE21,
	KKEY_PRIVATE22,
	KKEY_PRIVATE23,
	KKEY_PRIVATE24,
	KKEY_PRIVATE25,
	KKEY_PRIVATE26,
	KKEY_PRIVATE27,
	KKEY_PRIVATE28,
	KKEY_PRIVATE29,
	KKEY_PRIVATE30,
	KKEY_PRIVATE31,
	KKEY_PRIVATE32,

	KKEY_VMM_PMAP,
	KKEY_VMM,
	KKEY_PROC,
	KKEY_LDR,
	KKEY_LFS,
	KKEY_J2,
	KKEY_FILE_METADATA,
	KKEY_IOS,
	KKEY_IPC,
	KKEY_CRED,
	KKEY_LDATA_ALLOC,
	KKEY_KER,

	KKEY_KKEYSET,

	KKEY_RESERVED1,
	KKEY_RESERVED2,

	/*
	 * When adding a new key, put it above this comment.
	 * That will keep NUM_KKEYS correct automatically.
	 */
	NUM_KKEYS};		/* number of kernel keys supported */

#endif /* _KERNEL || __KDB */
#endif /* _H_SKEYS */
