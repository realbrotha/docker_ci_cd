/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

/*
 * sysconf.h - include file for sysconf utility and the kernel.
 */

#ifndef _SYS_SYSCONF_H
#define	_SYS_SYSCONF_H

#pragma ident	"@(#)sysconf.h	1.12	06/03/10 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * For each entry in /etc/system a sysparam record is created.
 */
struct sysparam {
	struct sysparam *sys_next; /* pointer to next */
	int	sys_type;	/* type of record */
	int	sys_op;		/* operation */
	char 	*sys_modnam;	/* module name (null if param in kernel) */
	char	*sys_ptr;	/* string pointer to device, etc. */
	u_longlong_t	sys_info;	/* additional information */
	char	*sys_config;	/* configuration data */
	int	sys_len;	/* len of config data */
	ulong_t	*addrp;		/* pointer to valloced config addresses */
	int	sys_flags; 	/* flags to check duplicate entries */
};

#define	MAXLINESIZE 80		/* max size of a line in /etc/system */

struct modcmd {
	char *mc_cmdname;
	int mc_type;
};

#define	MOD_EXCLUDE	0	/* we'll never load this one */
#define	MOD_INCLUDE	1	/* load on demand */
#define	MOD_FORCELOAD	2	/* load during initialization */
#define	MOD_ROOTDEV	3	/* root device */
#define	MOD_ROOTFS 	4	/* root fs type */
#define	MOD_SWAPDEV	5	/* swap device */
#define	MOD_SWAPFS 	6	/* swap fs type */
#define	MOD_MODDIR	7	/* default directory for modules */
#define	MOD_SET		8	/* set int to specified value */
#define	MOD_UNKNOWN	9	/* unknown command */
#define	MOD_SET32	10	/* like MOD_SET but -only- on 32-bit kernel */
#define	MOD_SET64	11	/* like MOD_SET but -only- on 64-bit kernel */
#define	MOD_ZFSROOT	12	/* use zfs as the root filesystem */

/*
 * Commands for mod_sysctl()
 */
#define	SYS_FORCELOAD	0	/* forceload modules */
#define	SYS_SET_KVAR	1	/* set kernel variables */
#define	SYS_SET_MVAR 	2	/* set module variables */
#define	SYS_CHECK_EXCLUDE 3	/* check if a module is excluded */

/*
 * Legal operations for MOD_SET.
 */
#define	SETOP_NONE	0	/* no op - for types other than MOD_SET */
#define	SETOP_ASSIGN	1	/* '=' - simple assignment */
#define	SETOP_AND	2	/* '&' - bitwise AND */
#define	SETOP_OR	3	/* '|' - bitwise OR */

/*
 * Defines for sys_flags.
 */
#define	SYSPARAM_STR_TOKEN	0x0001 /* a string token is set */
#define	SYSPARAM_HEX_TOKEN	0x0002 /* a hexadecimal number is set */
#define	SYSPARAM_DEC_TOKEN	0x0004 /* a decimal number is set */
#define	SYSPARAM_DUP		0x0010 /* this entry is duplicated */
#define	SYSPARAM_TERM		0x0020 /* this entry is the last entry */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_SYSCONF_H */