/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/usr/include/pwdpolicy.h 1.2                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2003,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
#include <sys/types.h>

/*
 * Name types.
 *
 * These macros select the meaning of the name passed to the
 * passwdpolicy() function.
 *
 * PWP_USERNAME		The name references a valid user identity
 *			The password strength attributes will be
 *			obtained by calling the getuserattr()
 *			function.
 *
 * PWP_SYSTEMPOLICY	The name references a stanza in the
 *			/etc/security/passwd_policy file.
 *
 * PWP_LOCALPOLICY	The name references a stanza in the
 *			/usr/lib/security/passwd_policy file.
 */

#define	PWP_USERNAME		1
#define	PWP_SYSTEMPOLICY	2
#define	PWP_LOCALPOLICY		3

/*
 * Test flag values.
 *
 * These macros select the tests to perform, or indicate the tests
 * which have failed.
 */

#define PWP_TOO_SOON		0x0001
#define PWP_EXPIRED		0x0002
#define	PWP_TOO_FEW_ALPHA	0x0004
#define	PWP_TOO_FEW_OTHER	0x0008
#define PWP_TOO_SHORT		0x0010
#define	PWP_TOO_MANY_REPEATS	0x0020
#define	PWP_TOO_MANY_SAME	0x0040
#define	PWP_IN_DICTIONARY	0x0080
#define	PWP_REUSED_PW		0x0100
#define	PWP_REUSED_TOO_SOON	0x0200
#define	PWP_FAILED_OTHER	0x0400

/*
 * Policy structure version number.
 *
 * This value must be stored in the structure prior to calling the
 * passwdstrength() function.  It indicates the version number of
 * the structure being passed to that function.
 */

#define	PWP_VERSION_1		1
#define	PWP_VERSION		PWP_VERSION_1

/*
 * Policy structure definition.
 */

typedef struct {
	int		pwp_version;
	time32_t	pwp_minage;
	time32_t	pwp_maxage;
	time32_t	pwp_maxexpired;
	int		pwp_minalpha;
	int		pwp_minother;
	int		pwp_minlen;
	int		pwp_maxrepeats;
	int		pwp_mindiff;
} passwd_policy_t;

int
passwdstrength(const char *, const char *,time64_t, passwd_policy_t *,int);
