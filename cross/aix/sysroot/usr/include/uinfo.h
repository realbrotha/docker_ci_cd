/* @(#)84	1.7  src/bos/usr/include/uinfo.h, sysproc, bos530 4/15/03 18:30:05 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: usrinfo
 *		
 *
 *   ORIGINS: 9
 *
 *
 * Copyright 1983, INTERACTIVE Systems Corporation
 *
 * RESTRICTED RIGHTS:   Use, duplication or disclosure is subject to
 *                      restrictions stated in your contract with
 *                      Interactive Systems Corp.
 *
 * NAME:        uinfo.h
 *
 * PURPOSE:     This file defines command codes for the usrinfo() system
 *              call and the length of the uinfo buffer.
 *
 */

#ifndef _H_UINFO
#define _H_UINFO

#define UINFO
#define UINFOSIZ        64      /* size of user info buffer             */
#define SETUINFO        1       /* set user info command code           */
#define GETUINFO        2       /* get user info command code           */
typedef char uinfo_t[UINFOSIZ];

#define UINFOXSIZ	4096	/* size of largest extended info buffer */
#define SETUINFOX	3	/* set extended user info command code */
#define GETUINFOX	4	/* get extended user info command code */

typedef struct {
        int ui_ref;             /* reference count (requires atomic ops)*/
        int ui_len;             /* length of data                       */
        char ui_buf[1];         /* actual data                          */
} uinfox_t;

#ifdef _KERNEL
extern uinfox_t *uinfox_ref (void);
extern void uinfox_free (uinfox_t *);
extern void uinfox_set (uinfox_t *);
#endif

#endif /* _H_UINFO */

