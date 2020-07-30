/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/usr/include/cf.h 1.27.3.2                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1989,1995              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)51       1.27.3.2  src/bos/usr/include/cf.h, cmdcfg, bos53X, x2010_31A7 7/19/10 14:47:30 */
#ifndef _H_CF
#define _H_CF
/*
 * COMPONENT_NAME: (CMDCFG) Generic config support cmd
 *
 * FUNCTIONS: cf.h
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989, 2006
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*---------------------- flag definitions for findmcode -------------------*/
/*									   */
/*  VERSIONING = find highest version of microcode			   */
/*  ABSOLUTE   = input microcode name is absolute name (do not try to      */
/*               find the highest version.)				   */
/*  BASENAME   = input microcode name is basename only and FIRST match     */
/*               on that part of a file name should be returned.           */
/*               (equivalent to search for mcode_name*)                    */
#include <sys/types.h>
#include <sys/cfgodm.h>

#define VERSIONING 0
#define ABSOLUTE   1
#define BASENAME   2

/*-------------------------------- message catalog ------------------------*/
#define CFG_MSG_CATALOG		"cmdcfg.cat"
#define CFG_MSG_SET		1
#define CFG_ERR_SET		2
#define CFG_METH_SET		3

/*--------------------------- default messages ----------------------------*/
extern char *meth_err_msg[];

/*----------------------------------- error messages ----------------------*/
/* These are the defined exit codes for device methods.  The config        */
/* commands have set messages that they display for each of these exit     */
/* codes.  Thus device methods do not need to deal with messages and       */
/* message catalogs.  If a method exits with an exit code not defined in   */
/* this list, then the command will use E_UNKNOWN.  The exit codes for     */
/* E_OK, E_FINDCHILD, and E_NEWCHILD are not failures.  The following      */
/* exit codes require attribute names to be written by the method to       */
/* stderr: E_INVATTR, E_ATTRVAL, and E_BADATTR.  There are four exit codes */
/* relating to attributes, they are to be used as follows:                 */
/*	E_INVATTR - An invalid attribute name was specified to a change    */
/*		    method.						   */
/*	E_ATTRVAL - An invalid attribute value was specifed to a change    */
/*		    method.						   */
/*	E_NOATTR  - A method, usually a config method, could not find an   */
/*		    attribute in the ODM that it needs.  Usually it is     */
/*		    better to code in a default value to use for this      */
/*		    situation rather than to just fail.			   */
/*	E_BADATTR - A method, usually a config method, detected an invalid */
/*		    attribute value in the ODM for an attribute it is      */
/*		    dependent on.  Again it may be better to just code in  */
/*		    a good default value rather than to just fail.         */
/*									   */
#define E_OK			0	/* Successful completion */
#define E_SYSTEM		1	/* Used for various system call errors*/
#define E_ODMINIT		2	/* odm_initialize() failure */
#define E_ODMLOCK		3	/* odm_lock() failure. Note: device
					   methods should not ne calling
					   odm_lock() */
#define E_ODMOPEN		4	/* odm_open_class() failure */
#define E_ODMCLOSE		5	/* odm_close_class() failure */
#define E_ODMGET		6	/* ODM read errors */
#define E_ODMUPDATE		7	/* ODM update errors */
#define E_ODMADD		8	/* ODM add errors */
#define E_ODMDELETE		9	/* ODM delete errors */
#define E_ODMRUNMETHOD		10	/* odm_run_method() failure */
#define E_ARGS			11	/* Invalid command line arguments */
#define E_OPEN			12	/* Open of a file/device failed */
#define E_LNAME			13	/* Device name was not specified
					   but is required */
#define E_TYPE			14	/* Device class, subclass, or type
					   was not specified but is required */
#define E_PARENT		15	/* Parent name or connection was not
					   specified but is required */
#define E_PARENT2		16	/* Parent name was specified but
					   should not have been */
#define E_INVATTR		17	/* Invalid attributes were specifed.
					   Attribute names should be written
					   to stderr */
#define E_ATTRVAL		18	/* Invalid attribute values were
					   specified.  Attribute names should
					   be written to stderr */
#define E_PFLAG			19	/* Method does not support the -P flag*/
#define E_TFLAG			20	/* Method does not support the -T flag*/
#define E_CHGCONNECT		21	/* method does not support a parent
					   or connection change */
#define E_INVCONNECT		22	/* Specified connection is invalid */
#define E_NOCuDv		23	/* No CuDv found for device */
#define E_NOPdDv		24	/* No PdDv found for device */
#define E_NOCuDvPARENT		25	/* No CuDv found for parent device */
#define E_ALREADYDEF		26	/* Can't define another instance of
					   this device type */
#define E_DEVSTATE		27	/* The device is in the wrong state */
#define E_PARENTSTATE		28	/* Parent device is in the wrong state*/
#define E_CHILDSTATE		29	/* A child dev. is in wrong state */
#define E_DEPSTATE		30	/* Dependent on another device which
					   is in the wrong state */
#define E_AVAILCONNECT		31	/* A device is already AVAILABLE at the
					   specified connection */
#define E_NODEPENDENT		32	/* Dependent on another device which
					   does not seem to be present */
#define E_NOATTR		33	/* A required device attribute seems
					   to be missing */
#define E_BADATTR		34	/* Attributes have incorrect values.
					   Attribute names should be written
					   to stderr */
#define E_NOPdOBJ		35	/* Can't find required predefined data
					   in the ODM */
#define E_NOCuOBJ		36	/* Can't find required customized data
					   in the ODM */
#define E_MAKENAME		37	/* Could not generate device name */
#define E_LOADEXT		38	/* Error from loadext() on load */
#define E_UNLOADEXT		39	/* Error from loadext() on unload */
#define E_CFGINIT		40	/* Error from driver on initialization*/
#define E_CFGTERM		41	/* Error from driver on termination */
#define E_MAJORNO		42	/* Error getting major number */
#define E_MINORNO		43	/* Error getting minor number */
#define E_MKSPECIAL		44	/* Error making special files */
#define E_DDS			45	/* Error building device initialization
					   structure. */
#define E_NOUCODE		46	/* Microcode or adapter software not
					   found or not accessable */
#define E_DEVACCESS		47	/* Error accessing a device */
#define E_UCODE			48	/* Error downloading microcode or
					   adapter software */
#define E_VPD			49	/* Error getting VPD */
#define E_NODETECT		50	/* Device to be configured is not
					   physically present or can not be
					   detected */
#define E_WRONGDEVICE		51	/* Device to be configured does not
					   match the device physically present
					   at this connection */
#define E_BUSRESOURCE		52	/* Bus resources could not be assigned
					   to this device */
#define E_SYSCONFIG		53	/* Other errors from sysconfig()
					   system call */
#define E_MALLOC		54	/* malloc() failures */
#define E_RELDEVNO		55	/* Errors in releasing major/minor */
#define E_DEVNO_INUSE		56	/* Requested major/minor already
					   assigned */
#define E_STAT			57	/* stat failure or file has incorrect
					   status */
#define E_RMSPECIAL		58	/* Error removing a special file */
#define E_SYMLINK		59	/* Can not create a symbolic link */
#define E_FORK			60	/* Can not create another process */
#define E_FINDCHILD		61	/* Problem in detecting child
					   devices. NOTE: This is not treated
					   as a config method failure */
#define E_BUSY			62	/* Can't unconfigure because the device
					   is busy or open */
#define E_NAME			63	/* Device driver name is too long */
#define E_UNLOADAIO		64	/* AIO kernel extension specific error*/
#define E_INSTNUM		65	/* Error assigning a device instance
					   number */
#define E_PARENT3		66	/* Parent name required */
#define E_NOSLOTS		67	/* No available slots */
#define E_UNKNOWN		68	/* Unknown failure */
#define E_PLATFORM_LIB_NOLOAD	69	/* Platform specific load module failed
					   to load */
#define E_STDERR		70	/* Device method has written its own
					   error message to stderr */
#define E_FWNOCFG		71	/* Firmware indicates device can not
					   be configured */
#define E_FWNORESOURCE		72	/* Firmware did not allocate resources
					   for the device */
#define E_NEWCHILD		73	/* A new child device was discovered
					   while config method was invoked
					   in cfgmgr parallel mode.  This is
					   not an error.  It informs cfgmgr to
					   reinvoke config method in serial mode
					   so that the method can define the
					   new device */

#define E_NOT_MPIO		74	/* The device is not MPIO capable */
#define E_DEV_PATH_STATE	75	/* A path to the device is in the wrong
					   state to perform the specified
					   operation (e.g., deleting a configed
					   path) */
#define E_ALL_PATHS		76	/* All paths to the device meet the
					   specified parent and connection
					   criteria; need to do device level
					   operation */
#define E_NO_PATH		77	/* No paths were found that meet the
					   specified parent and connection
					   criteria */
#define E_NO_UDID		78	/* The device does not have a (valid)
					   UDID */

#define E_NO_UDID_METHOD	79	/* Device does not have a UDID method;
					   use subclass UDID procedure */

#define E_INVAL			80	/* A routine was called with an invalid
					   parameter */
#define E_INTERNAL		81	/* An internal error was detected */
#define E_SOME_PATHS		82	/* The operation (e.g., configure) could
					   only be performed successfully for a
					   subset of the paths meeting the
					   parent and connection criteria */
#define E_TYPE2			83	/* Device class, subclass, or type
					   was specified and is not allowed */
#define E_UDID_LEN		84	/* Device UDID is too long	*/
#define E_PATH_IO		85	/* DD could not communicate with device
					   over given path. */
#define E_NOT_SUPPORTED	        86	/* The device is an "HV Branded" device, but
					   the system does not support HV devices */
#define E_LAST_ERROR		87	/* This is never returned as an error.
					   See following comments. */

/* WARNING!!!!! - E_LAST_ERROR must be the last error - the high level */
/* commands require this. E_LAST_ERROR does not have a corresponding   */
/* error message. If an error value of E_LAST_ERROR or greater is      */
/* returned, the high level commands will display the message for      */
/* E_UNKNOWN.                                                          */
/*                                                                     */
/* If you need to add a new message, add it in before E_LAST_ERROR,    */
/* increment the value of E_LAST_ERROR, and add the new error's        */
/* message text in:                                                    */
/*   for the default messages, update:                                 */
/*    src/bos/usr/ccs/lib/libcfg/cfdefmsg.c,                           */
/*   for the message catalog, update:                                  */
/*    src/bos/usr/sbin/lsdev/cmdcfg.msg                                */


/* Defines for the cfglock() subroutine */
#define CFG_CUDV_LOCK		0
#define CFG_CUAT_LOCK		1
#define CFG_CUDEP_LOCK		2
#define CFG_CUVPD_LOCK		3
#define CFG_CUDVDR_LOCK		4
#define CFG_SYSFILE_LOCK	5
#define CFG_POWERMAN_LOCK	6
#define CFG_OTHER_LOCK		7


/* log types for the cfglog_start()/cfglog() subroutines */
#define CFGLOG_CMD	1,__FILE__,__LINE__
#define CFGLOG_METH	2,__FILE__,__LINE__
/* CFGLOG_LIB is only for cfglog() subroutine */
#define CFGLOG_LIB	4,__FILE__,__LINE__

/* log levels for the cfglog_start()/cfglog() subroutines */
#define CFGLOG_ERROR		0
#define CFGLOG_INFO		1
#define CFGLOG_DBG		4
#define CFGLOG_EXTDBG		6
#define CFGLOG_ADVDBG		8


/* Defines for cf_update_odm() to identify the update type */
#define CFG_DB_ADD              0
#define CFG_DB_MODIFY           1
#define CFG_DB_DELETE           2


/* Structure for dealing with path states */
typedef struct mpio_path_state
{
    short  path_id;
    short  result;
} mpio_path_state_t;


/* Definitions for the cfg_dspmsg() flag */
#define CFG_DSPMSG_LEFT_TRUNC   1  /* Truncate msg on left instead of on right */
#define CFG_DSPMSG_USE_LINE1    2  /* Start message on line1 instead of line2  */

/* Definitions for msi/msi-x processing */
#define MSI_REQ		1
#define MSI_X_REQ	2

/*---------------------*/
/* Function Prototypes */
/*---------------------*/

#ifdef _NO_PROTO

int genmajor();
int genseq();
int relmajor();
int *getminor();
int *genminor();
int reldevno();
#ifdef __ia64
int relminor();
#endif /* __ia64 */
mid_t	loadext();
int geninst();
int relinst();
int lsinst();
int attrval();
struct CuAt *getattr();
int putattr();
int get_platform();
int findmcode();
int get_bootparms();
int get_scsi_id();
int put_scsi_id();
int get_config_adspace_type();
int set_sas_physloc();
int busresolve();
int cfglock();
int cfgunlock();
int cfgmgr_mode();
int cfglog();
int cfglog_start();
int get_cudv();
int get_pddv();
int cf_update_odm();
int cf_get_friend_pddv();
int cf_get_possible_friends();
int cf_validate_friend();
int get_pending_friend_change();
int clear_pending_friend_change();
int save_pending_friend_change();
int enable_paths();
int disable_paths();
int get_path_states();
int cfg_dspmsg();
int lp_options_supported();
int lp_device();
int get_msg_interrupts();

#else /* _NO_PROTO */

int genmajor(char *);
int genseq(char *);
int relmajor(char *);
int *getminor(int, int *, char *);
int *genminor(char *, int, int, int, int, int);
int reldevno(char *, int);
#ifdef __ia64
int relminor(char *,int);
#endif /* __ia64 */
mid_t loadext(char *, int, int);
int geninst( char *, char *);
int relinst(char *);
int lsinst(char *);
int	attrval(char *, char *, char **);
struct CuAt *getattr(char *, char *, int, int *);
int	putattr(struct CuAt *);
int get_platform(char *);
int findmcode(char *, char *, int, char *);
int get_bootparms(struct CuDv *, struct PdDv *, char *);
int get_scsi_id(struct CuDv *, struct PdDv *, char *);
int put_scsi_id(struct CuDv *, struct PdDv *, char *);
int get_config_adspace_type(struct CuDv *, unsigned int *);
int set_sas_physloc(struct CuDv *, int, char *, char *, char *);
int busresolve(char *, int, char *, char *, char *);
int cfglock(int);
int cfgunlock(void);
int cfgmgr_mode(int *, int *);
int cfglog(int, char*, int, int, char*, ...);
int cfglog_start(int, char*, int, int, char**);
int get_cudv(char*, struct CuDv*);
int get_pddv(char*, char*, char*, char*, struct PdDv*);
int cf_update_odm(struct Class*, void*, int);
int cf_get_friend_pddv(struct CuDv*, char*, struct PdDv*);
int cf_get_possible_friends(struct CuDv*, char*, char***, uint_t*);
int cf_validate_friend(struct CuDv*, char*, char*);
int get_pending_friend_change(struct CuDv*, char*, char*);
int clear_pending_friend_change(struct CuDv*, char*);
int save_pending_friend_change(struct CuDv*, char*, char*);
int enable_paths(struct CuDv*, int, mpio_path_state_t*);
int disable_paths(struct CuDv*, int, mpio_path_state_t*);
int get_path_states(struct CuDv*, int, mpio_path_state_t*);
int cfg_dspmsg(int, char *, int);
int lp_options_supported();
int lp_device(void*, int);
int get_msg_interrupts(struct CuDv*, int, int, int*, unsigned int**);

#endif /* _NO_PROTO */

#endif	/* _H_CF */

