/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1998,2009          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/*===========================================================================*/
/*                                                                           */
/* Module Name:  ct_mc.h                                                     */
/*                                                                           */
/* Description:                                                              */
/*     Interface definitions for the RMCAPI.								 */
/*                                                                           */
/*     This file is formatted to be viewed with tab stops set to 4.          */
/*===========================================================================*/
/* @(#)18   1.48   src/rsct/rmc/rmcapi/ct_mc.h, rmcapi, rsct_rhay53, rhay531006a 5/21/09 23:21:02 */

#ifndef _H_CT_MC
#define _H_CT_MC

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>
#include <sys/time.h>

#include <rsct/ct.h>					/* Cluster common types				*/
#include <rsct/ct_cu.h>					/* Cluster common utilities			*/
#include <rsct/ct_rmc.h>				/* RMC common types					*/
#include <rsct/ct_mcerr.h>				/* RMC command response error codes	*/
	

/*--------------------------------------------------------------------------*/
/*  Error Codes																*/
/*--------------------------------------------------------------------------*/

#define MC_ELIB					1	/* Severe library or system error		  */
#define MC_ESESSREFUSED			2	/* A session could not be established	  */
#define MC_ESESSINTRPT			3	/* The session has been interrupted		  */
#define MC_ESESSENDED			4	/* The session has been ended			  */
#define MC_EINVALIDSESS			5	/* Specified session handle is invalid	  */
#define MC_ENODSCRP				6	/* Descriptor cannot be allocated		  */
#define MC_EINVALIDDSCRP		7 	/* The specified descriptor is invalid	  */
#define MC_EINVALIDCMD			8 	/* Specified cmd grp handle is invalid	  */
#define MC_ENOCMDS				9	/* Command group contains no commands	  */
#define MC_ESENTENDED			10	/* Command group sent; session ended	  */
#define MC_ESENTINTRPT			11	/* Cmd. group sent; session interrupted	  */
#define MC_EINVALIDDATA			12	/* Invalid response or notification		  */
#define MC_ECMDGRPSLIMIT		13	/* Session contains max. command groups   */
#define MC_ECMDGRPLIMIT			14	/* Command group contains max. commands   */
#define MC_EINVALIDEID			15	/* Specified registration ID is invalid	  */
#define MC_EINVALIDOPT			16	/* The specified option is invalid		  */
#define	MC_EBUSY				17	/* Function busy						  */
#define	MC_ENOMEM				18	/* Memory allocation error				  */
#define	MC_EAGAIN				19	/* Some system resource not available	  */
#define	MC_EINVALIDCB			20	/* Invalid callback routine specified	  */
#define	MC_EINVALIDRSPPTR		21	/* Invalid response pointer specified	  */
#define	MC_EINVALIDCNTPTR		22	/* Invalid rsp. count pointer specified	  */
#define MC_EINVALIDRSRCCNT		23	/* Invalid resource handle count		  */
#define MC_ECMDTOOLARGE			24	/* Command is too large					  */
#define	MC_ELIBNOMEM			25	/* Memory severe allocation error		  */
#define	MC_EORDERGROUP			26	/* Attempted to add to ordered cmd grp    */
#define	MC_ETARGETMISMATCH		27	/* Command/cmd group target(s) mismatch	  */
#define MC_EINVALIDDATATYPE		28	/* Invalid attribute data type			  */
#define MC_EINVALIDVALUEPTR		29	/* Invalid attribute value pointer		  */
#define MC_EINVALIDSBSLEN		30	/* Invalid structured byte string len.    */
#define MC_EINVALIDSDTYPE		31	/* Invalid structured data subtype		  */
#define MC_EINVALIDCONTACT		32	/* Invalid contact type					  */
#define MC_ENOTSUPPORTED		33	/* Called function is not supported		  */
#define MC_EDEADLOCK			34	/* Possible deadlock detected			  */
#define MC_EINVALIDNAME			35	/* Invalid contact point name (NULL)	  */
#define MC_EINVALIDSTRING		36	/* Invalid string						  */
#define MC_ELIBSECURITY			37	/* RMCAPI security service error	 	  */
#define MC_ESUBSECURITY			38	/* RMC subsystem security service error	  */
#define MC_EAUTHENTICATE		39	/* Could not authenticate user			  */
#define MC_EAUTHORIZATION		40	/* User not authorized to use RMC		  */
#define MC_EMUTUALAUTHENT		41	/* RMCAPI could not authenticate subsys	  */
#define MC_EVERSIONMISMATCH		42	/* RMCAPI version mismatch				  */

/*  The following error codes were introduced with version 2 of the RMCAPI    */

#define MC_EINVALSCOPE		    43	/* Specified session scope not supported  */
#define MC_EMULTISCOPE		    44	/* Multiple session scopes specified	  */
#define MC_ENOTPRIVATESCOPE	    45	/* Specified session scope not private	  */
#define MC_EQEVENTACTIVE	    46	/* A query event command is active		  */
#define MC_ENOSUPPORTRTNVER	    47	/* No support for routine/RMC version	  */
#define MC_ENOSUPPORTARGVER	    48	/* No support for arguments/RMC version	  */
#define MC_ECLASSEID		    49	/* Registration ID for a class event	  */
#define MC_ENOIPADDRCONTACT		50	/* Contact must be IP address			  */
#define MC_ENOIPAUTHENTSUPPORT	51	/* IP authent. not supported by session	  */
#define MC_ETIMEDOUT			52	/* Start session, or command, timed out	  */
#define MC_EUNKNOWNINFO			53	/* Unknown type of information requested  */
#define MC_EIMPROPERINFO		54	/* Info not appropriate for circumstances */
#define MC_EUNATTAINABLEINFO	55	/* Requested information not attainable   */


/*--------------------------------------------------------------------------*/
/*  Handles and Identifiers													*/
/*--------------------------------------------------------------------------*/


typedef void *	mc_sess_hndl_t;			/* session handle					*/
typedef void *	mc_cmdgrp_hndl_t;		/* command group handle				*/
typedef void *	mc_registration_id_t;	/* event registration ID	 		*/


/*--------------------------------------------------------------------------*/
/*  Resource Monitoring and Control (RMC) constants							*/
/*--------------------------------------------------------------------------*/


/*
 *  MC_CMD_GRPS_LIMIT is the maximum number of command groups allowed in a
 *  session.
 */

#define MC_CMD_GRPS_LIMIT		65535


/*
 *  MC_CMD_GRP_LIMIT is the maximum number of commands allowed in a command
 *  group.
 */

#define MC_CMD_GRP_LIMIT		65535


/*--------------------------------------------------------------------------*/
/*  Resource Monitoring and Control (RMC) API enumerations.                 */
/*--------------------------------------------------------------------------*/


/*
 *  Session Status Flags (introduced with version 2 of the RMCAPI)
 */

typedef enum {
	MC_SESS_STATUS_NONE					= 0x0000,
	MC_SESS_STATUS_INTRPT				= 0x0001,
	MC_SESS_STATUS_INTRPT_CHANGED_SCOPE	= 0x0002
} mc_sess_status_t;					


/*
 *  Session Information Type (introduced with version 2 of the RMCAPI)
 *
 *    The second argument to mc_session_info() is of this type; it specifies
 *    what type of information is requested.  The data type of the third
 *    argument to mc_session_info() is determined by this value.
 *
 *      Value of info_type               Data type of info_returned
 *      ------------------               --------------------------
 *
 *      MC_SESS_INFO_LOCAL_IP_ADDRESS    struct in6_addr *
 *                                          (as defined in netinet/in.h)
 *
 *    When MC_SESS_INFO_LOCAL_IP_ADDRESS is specified, mc_session_info()
 *    returns the session's local IP address.  This operation is only
 *    supported for remote sessions.
 */

typedef enum {
	MC_SESS_INFO_LOCAL_IP_ADDRESS
} mc_sess_info_t;					


/*
 *  Start Session options
 */

typedef enum {
	MC_SESSION_OPTS_NONE				= 0x0000,
	MC_SESSION_OPTS_LOCAL_SCOPE			= 0x0001,

	/*  The following options were introduced with version 2 of the RMCAPI  */

	MC_SESSION_OPTS_SR_SCOPE			= 0x0002,
	MC_SESSION_OPTS_DM_SCOPE			= 0x0004,
	MC_SESSION_OPTS_PRIVATE				= 0x0008,

	MC_SESSION_OPTS_SR_LOCAL_SCOPE		= 0x0010,
	MC_SESSION_OPTS_DM_LOCAL_SCOPE		= 0x0020,

	MC_SESSION_OPTS_SR_DM_SCOPE			= 0x0040,
	MC_SESSION_OPTS_DM_SR_SCOPE			= 0x0080,

	MC_SESSION_OPTS_SR_DM_LOCAL_SCOPE	= 0x0100,
	MC_SESSION_OPTS_DM_SR_LOCAL_SCOPE	= 0x0200,

	MC_SESSION_OPTS_IP_AUTHENTICATION	= 0x0400
} mc_session_opts_t;					


/*
 *  Dispatch options
 */

typedef enum {
	MC_DISPATCH_OPTS_WAIT,
	MC_DISPATCH_OPTS_ASSIGN
} mc_dispatch_opts_t;					


/*
 *  Start command group options
 */

typedef enum {
	MC_CMD_GRP_OPTS_NONE		  = 0x0000,
	MC_CMD_GRP_OPTS_ORDERED		  = 0x0001,
	MC_CMD_GRP_OPTS_NO_INTERLEAVE = 0x0002,
	MC_CMD_GRP_OPTS_STOP_ON_ERROR = 0x0004				
} mc_cmd_grp_opts_t;	


/*
 *  Registration command options (The MC_REG_OPTS_KEEP_REG constant is only
 *  used with the attribute selection form of the command):
 */

typedef enum {
	MC_REG_OPTS_NONE		= 0x0000,
	MC_REG_OPTS_NO_REG		= 0x0001,
	MC_REG_OPTS_IMMED_EVAL	= 0x0002,
	MC_REG_OPTS_REARM_EVENT	= 0x0004,
  	MC_REG_OPTS_KEEP_REG	= 0x0008,
 	MC_REG_OPTS_NO_TOGGLE   = 0x0010
} mc_reg_opts_t;

	
/*
 *  Query Definition command options:
 */

typedef enum {
	MC_QDEF_OPTS_NONE    = 0x0000,
	MC_QDEF_OPTS_NODSCRP = 0x0001
} mc_qdef_opts_t;

	
/*
 *  Name list usage (introduced with version 3 of the RMCAPI)
 */

typedef enum {
	MC_LIST_USAGE_NODES        = 0x0000,
	MC_LIST_USAGE_PEER_DOMAINS = 0x0001
} mc_list_usage_t;

	
/*
 *  Offline command options (introduced with version 2 of the RMCAPI)
 */

typedef enum {
	MC_OFFLINE_OPTS_NONE    = 0x0000,
	MC_OFFLINE_OPTS_FAILED  = 0x0001
} mc_offline_opts_t;


/*
 *  Properties of a resource class are defined by the mc_rsrc_class_props_t
 *  enumeration.
 */

typedef enum {
	MC_RSRC_CLASS_HAS_IW_ACCESS			= 0x0001,
	MC_RSRC_CLASS_HAS_RSRC_INSTS		= 0x0002,
	MC_RSRC_CLASS_HAS_CTRL_INTERFACE	= 0x0004,
	MC_RSRC_CLASS_CAN_DEFINE_UNDEFINE	= 0x0008,
	MC_RSRC_CLASS_INVOKE_PHASE0			= 0x0010,
	MC_RSRC_CLASS_INVOKE_PHASE1			= 0x0020,
	MC_RSRC_CLASS_PERFMON_SUPPORTED		= 0x0040,
	MC_RSRC_CLASS_HAS_CONSTRAINTS		= 0x0080,
	MC_RSRC_CLASS_RMC_ELECTS_COORD		= 0x0100,
	MC_RSRC_CLASS_SUPPORTS_MOVE			= 0x0200,
	MC_RSRC_CLASS_CAN_BATCH_DEFINE		= 0x0400,
	MC_RSRC_CLASS_CAN_BATCH_UNDEFINE	= 0x0800,
	MC_RSRC_CLASS_CAN_BATCH_SET_ATTR	= 0x1000,
	MC_RSRC_CLASS_MTYPE_SUBDIVIDED		= 0x2000,
	MC_RSRC_CLASS_MTYPE_CENTRALIZED		= 0x4000,
	MC_RSRC_CLASS_MTYPE_GLOBALIZED		= 0x8000,
	MC_RSRC_CLASS_ACT_QUORUM_CHANGE		= 0x00010000,
	MC_RSRC_CLASS_QRY_REQS_MONITORING	= 0x00020000
} mc_rsrc_class_props_t;


/*
 *  Properties of a persistent attribute are defined by the mc_pattr_props_t
 *  enumeration.
 */

typedef enum {
	MC_RSRC_PATTR_READ_ONLY			= 0x0001,
	MC_RSRC_PATTR_REQD_FOR_DEFINE	= 0x0002,
	MC_RSRC_PATTR_INVAL_FOR_DEFINE	= 0x0004,
	MC_RSRC_PATTR_OPTION_FOR_DEFINE	= 0x0008,
	MC_RSRC_PATTR_SELECTABLE		= 0x0010,
	MC_RSRC_PATTR_PUBLIC			= 0x0020
} mc_pattr_props_t;


/*
 *  Properties of a dynamic attribute are defined by the mc_dattr_props_t
 *  enumeration.
 */

typedef enum {
	MC_RSRC_DATTR_PUBLIC				= 0x0020,
	MC_RSRC_DATTR_QRY_REQS_MONITORING	= 0x0040
} mc_dattr_props_t;


/*
 *  A Structured Data type can be used as the type of a persistent attribute,
 *  action input, action response, error input, and as an argument in a
 *  mc_define_resource, mc_undefine_resource, mc_online, mc_offline or mc_reset
 *  command. The mc_sd_usage_t enumeration is used to specify how structured
 *  data is used.
 */

typedef enum {
	MC_SD_USAGE_PATTR_RSRC_CLASS,
	MC_SD_USAGE_PATTR_RESOURCE,
	MC_SD_USAGE_DATTR_RSRC_CLASS,
	MC_SD_USAGE_DATTR_RESOURCE,
	MC_SD_USAGE_RSRC_ACTION_INPUT,
	MC_SD_USAGE_RSRC_ACTION_RESPONSE,
	MC_SD_USAGE_CLASS_ACTION_INPUT,
	MC_SD_USAGE_CLASS_ACTION_RESPONSE,
	MC_SD_USAGE_ERROR_INPUT,
	MC_SD_USAGE_DEFINE_ARG,
	MC_SD_USAGE_UNDEFINE_ARG,
	MC_SD_USAGE_ONLINE_ARG,
	MC_SD_USAGE_OFFLINE_ARG,
	MC_SD_USAGE_RESET_ARG
} mc_sd_usage_t;


/*
 *  Valid values may be specified for a persistent attribute, a dynamic
 *  attribute that has a variable type of RMC_STATE, action input, error
 *  input, and for the argument in a mc_define_resource, mc_undefine_resource,
 *  mc_online, mc_offline or mc_reset command. The mc_vv_usage_t enumeration
 *  defines to which of these the valid value applies.
 */

typedef enum {
	MC_VV_USAGE_PATTR_RSRC_CLASS,
	MC_VV_USAGE_PATTR_RESOURCE,
	MC_VV_USAGE_DATTR_RSRC_CLASS,
	MC_VV_USAGE_DATTR_RESOURCE,
	MC_VV_USAGE_RSRC_ACTION_INPUT,
	MC_VV_USAGE_CLASS_ACTION_INPUT,
	MC_VV_USAGE_ERROR_INPUT,
	MC_VV_USAGE_DEFINE_ARG,
	MC_VV_USAGE_UNDEFINE_ARG,
	MC_VV_USAGE_ONLINE_ARG,
	MC_VV_USAGE_OFFLINE_ARG,
	MC_VV_USAGE_RESET_ARG
} mc_vv_usage_t;


/*
 *  Instead of statically defined valid values, a resource class may have a
 *  defined action that can be invoked to return a list of valid values for a
 *  persistent attribute, action input, error input or command argument.  In
 *  that case, the mc_action_type_t enumeration indicates whether the defined
 *  action is a resource action or class action.
 */

typedef enum {
	MC_ACTION_TYPE_RESOURCE,
	MC_ACTION_TYPE_CLASS
} mc_action_type_t;


/*
 *  Properties of an action are defined by the mc_action_props_t enumeration.
 */

typedef enum {
	MC_RSRC_ACTION_LONG_RUNNING	= 0x0001,
	MC_RSRC_ACTION_PUBLIC		= 0x0002
} mc_action_props_t;


/*
 *  Properties of an error injection are defined by the mc_error_props_t
 *  enumeration.
 */

typedef enum {
	MC_RSRC_ERROR_PUBLIC	= 0x0001
} mc_error_props_t;
	

/*
 *  Integrity Check command options:
 */

typedef enum {
	MC_CHK_OPTS_NONE	= 0x0000,
	MC_CHK_OPTS_FIX		= 0x0001
} mc_integrity_check_opts_t;


/*
 *  Check flags are defined by the mc_check_flags_t enumeration.
 *
 *  MC_CHECK_FIXED indicates that the associated resource error was fixed.
 */

typedef enum {
	MC_CHECK_FIXED = 0x0001
} mc_check_flags_t;


/*
 *  Event flags are defined by the mc_event_flags_t enumeration.
 *
 *  This enumeration is defined in ct_rmc.h
 */


/*
 *  RMC ACL types are defined by the mc_acl_type_t enumeration.
 */

typedef enum {
	MC_ACL_TYPE_RESOURCE,						/* Resource ACL				*/
	MC_ACL_TYPE_RESOURCE_INITIAL,				/* Resource Initial ACL		*/
	MC_ACL_TYPE_RESOURCE_SHARED,				/* Resource Shared ACL		*/
	MC_ACL_TYPE_CLASS							/* Class ACL				*/
} mc_acl_type_t;


/*
 *  RMC ACL flags are defined by the mc_acl_flags_t enumeration.
 */

typedef enum {
	MC_ACL_USE_RESOURCE_SHARED  =  0x0001		/* Use Resource Shared ACL	*/
} mc_acl_flags_t;


/*--------------------------------------------------------------------------*/
/*  Resource Monitoring and Control (RMC) API responses and notifications.  */
/*--------------------------------------------------------------------------*/


/*
 *  A resource attribute is returned in a mc_attribute_t type. This type
 *  includes the attribute (programmatic) name and data type. This type is
 *  also used to provide attributes to the RMCAPI. When provided to the API,
 *  the mc_at_id field is not defined and the mc_at_dtype field must be set
 *  appropriately.
 */

typedef struct {
	ct_char_t			*mc_at_name;
	rmc_attribute_id_t	 mc_at_id;
	ct_data_type_t		 mc_at_dtype;
	ct_value_t			 mc_at_value;
} mc_attribute_t;


/*
 *  All responses and event notifications contain error information in a
 *  structure of mc_errnum_t type.
 *
 *  The first entry in the structure is an error code from the RMC
 *  Subsystem. If the mc_errnum field is zero, there is no error. If there is
 *  an error the mc_error_msg field contains a pointer to a message that is
 *  descriptive of the error. If the mc_arg_count field is non-zero, the
 *  mc_args field is a pointer to an array containing additional error
 *  information; this information is specific to, and documented with, the
 *  error. The mc_arg_count field is the count of array elements. The
 *  mc_ffdc_id field contains a pointer to string that is a failure
 *  identifier. This failure identifier specifies additional error
 *  information that may have been logged by the RMC Subsystem. If this field
 *  contains a NULL pointer then no additional error information has been
 *  logged. If the application is logging errors that it has detected then
 *  this failure identifier should be a part of the error information so
 *  logged.
 *
 *  Error codes that may be returned in the mc_errnum field are grouped in
 *  ranges of 64K, starting with the lowest valued code in each group. For
 *  example, one group indicates an error in the arguments of a command,
 *  another group indicates resource availability errors, another group
 *  indicates resource class independent errors from a resource class,
 *  etc. Thus, the high-order sixteen bits of the error code identify the
 *  error group or general class of error and the lower sixteen bits indicate
 *  a specific error within the group.  The MC_GET_GENERR and MC_GET_SPECERR
 *  macros can be used to obtain these values.
 */

typedef struct {
	ct_uint32_t		 mc_errnum;
	ct_char_t		*mc_ffdc_id;
	ct_char_t		*mc_error_msg;
	cu_error_arg_t	*mc_args;
	ct_uint32_t		 mc_arg_count;
} mc_errnum_t;

#define MC_GET_GENERR(e)							((e >> 16) & 0xffff)
#define MC_GET_SPECERR(e)							(e & 0xffff)


/*
 *  A number of query definition responses include a pointer to a variety
 *  list, specified by a structure of type mc_variety_t.  The mc_first_variety
 *  and mc_last_variety fields specify the first and last variety,
 *  respectively, in a range of varieties. The mc_first_variety field is
 *  always less than or equal to the mc_last_variety field. A variety list
 *  consists of an array of elements of type mc_variety_t.
 */

typedef struct {
	ct_uint32_t		mc_first_variety;
	ct_uint32_t		mc_last_variety;
} mc_variety_t;


/*
 *  An Event Notification consists of a structure of type mc_event_t or
 *  mc_class_event_t. The type mc_event_t is used if the event is generated
 *  from a resource and the type mc_class_event_t is used if the event is
 *  generated from a resource class.
 *
 *  The event notification structure is passed to the application as an
 *  argument to the callback the application specified when issuing an event
 *  registration command.
 *
 *  The mc_error field indicates whether or not the event is an error event.
 *  If an error event, the error codes imply which of the remaining fields in
 *  the structure are defined.  If not an error event, all of the remaining
 *  fields are defined.  The mc_event_flags field is a bit field; its values
 *  are defined by the mc_event_flags_t enumeration.  Note that the
 *  mc_event_flags field is undefined in any error event.  The mc_timestamp
 *  field indicates the time the event was generated.  The mc_rsrc_hndl field
 *  specifies the resource handle of the resource, or the mc_class_name field
 *  specifies the name of the resource class, whose state change resulted in
 *  the generation of this event.  The mc_peer_domain_name field specifies the
 *  name of the peer domain where the class event was generated.  The name is
 *  the node name in angle brackets (<>) if the response is from a node not in
 *  a peer domain.  The mc_attrs field is a pointer to an array of attributes;
 *  the mc_attr_count field indicates the number of entries in this array.
 *
 *  The attribute array is considered as a list, wherein there are up to two
 *  sub-lists. The first is a list of attributes found in the event
 *  expression(s). The second is a list of persistent attributes specified as
 *  return attributes in the event registration command. There are no
 *  duplicate attributes among the two sub-lists. If a persistent attribute is
 *  specified both in an event expression and as a return attribute, it is
 *  only placed in the first sub-list.
 *
 *  The number of attributes in the first sub-list is given by
 *  mc_e_attr_count. The number of attributes in the second sub-list is given
 *  by the expression:
 *
 *      mc_attr_count - mc_e_attr_count
 *
 *  This expression is guaranteed to be greater than or equal to zero.
 *
 *  The MC_RETURN_ATTR_COUNT macro can be used to calculate the number of
 *  return attributes.
 *
 *  The mc_node_name field specifies the primary node name of the node where
 *  the resource, specified by the mc_rsrc_hndl field, is, or was, in the case
 *  of certain error events, being monitored.
 */

typedef struct {
	mc_errnum_t				 mc_error;
	mc_event_flags_t		 mc_event_flags;
	struct timeval			 mc_timestamp;
	ct_resource_handle_t	 mc_rsrc_hndl;
	mc_attribute_t			*mc_attrs;
	ct_uint32_t				 mc_attr_count;
	ct_uint32_t				 mc_e_attr_count;
	ct_char_t				*mc_node_name;
} mc_event_6_t;

typedef struct {
	mc_errnum_t				 mc_error;
	mc_event_flags_t		 mc_event_flags;
	struct timeval			 mc_timestamp;
	ct_resource_handle_t	 mc_rsrc_hndl;
	mc_attribute_t			*mc_attrs;
	ct_uint32_t				 mc_attr_count;
	ct_char_t				*mc_node_name;
} mc_event_2_t;

typedef struct {
	mc_errnum_t				 mc_error;
	mc_event_flags_t		 mc_event_flags;
	struct timeval			 mc_timestamp;
	ct_resource_handle_t	 mc_rsrc_hndl;
	mc_attribute_t			*mc_attrs;
	ct_uint32_t				 mc_attr_count;
} mc_event_1_t;

typedef struct {
	mc_errnum_t				 mc_error;
	mc_event_flags_t		 mc_event_flags;
	struct timeval			 mc_timestamp;
	ct_char_t				*mc_class_name;
	ct_char_t				*mc_peer_domain_name;
	mc_attribute_t			*mc_attrs;
	ct_uint32_t				 mc_attr_count;
	ct_uint32_t				 mc_e_attr_count;
} mc_class_event_6_t;

typedef struct {
	mc_errnum_t				 mc_error;
	mc_event_flags_t		 mc_event_flags;
	struct timeval			 mc_timestamp;
	ct_char_t				*mc_class_name;
	ct_char_t				*mc_peer_domain_name;
	mc_attribute_t			*mc_attrs;
	ct_uint32_t				 mc_attr_count;
} mc_class_event_3_t;

typedef struct {
	mc_errnum_t				 mc_error;
	mc_event_flags_t		 mc_event_flags;
	struct timeval			 mc_timestamp;
	ct_char_t				*mc_class_name;
	mc_attribute_t			*mc_attrs;
	ct_uint32_t				 mc_attr_count;
} mc_class_event_1_t;

#define MC_RETURN_ATTR_COUNT(p)		((p)->mc_attr_count - (p)->mc_e_attr_count)
	
/*
 *  A Registration Response consists of a structure of type mc_reg_rsp_t.
 *  
 *  If the Registration Response indicates no error, the event has been
 *  successfully registered by the Resource Monitoring and Control
 *  Subsystem. The mc_registration_id field contains the event ID, which is
 *  used to unregister the event. Note that a successful registration does not
 *  indicate that events will ever be generated. However, if events are
 *  generated, in a multi-threaded application the event notification callback
 *  can be invoked before the Registration Response is processed by the
 *  application.
 *  
 *  If the response indicates an error, the event has not been registered by
 *  the RMC Subsystem and the mc_registration_id field is undefined. If the
 *  error indicates an error in the arguments supplied with the event
 *  registration command, the error code indicates which argument is in error.
 *
 */

typedef struct {
	mc_errnum_t				mc_error;
	mc_registration_id_t	mc_registration_id;
} mc_reg_rsp_t;


/*
 *  An Unregistration Response consists of a structure of type mc_unreg_rsp_t.
 *  
 *  The mc_error field always indicates no error; the event specified by the
 *  mc_registration_id field has been successfully unregistered. The Resource
 *  Monitoring and Control Subsystem guarantees that this response is passed
 *  to the application only when no event notification callbacks for the
 *  specified event are being executed. Once the response has been passed to
 *  the application the specified event ID is invalid and no more event
 *  notifications are delivered to the application. This permits the
 *  application to release any application resources, associated with the
 *  event, when it receives the response.
 */

typedef struct {
	mc_errnum_t				mc_error;
	mc_registration_id_t	mc_registration_id;
} mc_unreg_rsp_t;


/*
 *  A Query Event Response consists of a structure of type mc_query_event_rsp_t.
 *  
 *  If the mc_error field indicates an error, the Resource Monitoring and
 *  Control Subsystem could not complete the command. The error may also
 *  indicate that the command arguments were in error. The error codes imply
 *  which of the remaining fields in the structure are defined. Otherwise, the
 *  event query command has completed for the event indicated by the
 *  mc_registration_id field. The mc_event_count field specifies the number of
 *  events that were generated as a result of this command. If the
 *  mc_event_count field is not zero, then the Resource Monitoring and Control
 *  Subsystem guarantees that this response is passed to the application only
 *  after all event notification callbacks for the events generated by this
 *  command have been executed.
 *
 *  This response was introduced with version 2 of the RMCAPI.
 */

typedef struct {
	mc_errnum_t				mc_error;
	mc_registration_id_t	mc_registration_id;
	ct_uint32_t				mc_event_count;
} mc_query_event_rsp_t;


/*
 *  An Enumerate Response consists of a structure of type mc_enumerate_rsp_t.
 *
 *  If the mc_error field indicates an error, the Resource Monitoring and
 *  Control Subsystem or a Resource Manager could not provide any or all of
 *  the requested information. The error may also indicate that the command
 *  arguments were in error. The error codes imply which of the remaining
 *  fields in the structure are defined. Otherwise, the mc_class_name field
 *  specifies the name of the resource class whose resources are
 *  contained in this response. the mc_rsrc_handles field specifies a pointer
 *  to a resource handle array, which contains the resource handles of the
 *  selected resources.  The mc_rsrc_handle_count field indicates the number
 *  of resource handles in the array.
 */

typedef struct {
	mc_errnum_t				 mc_error;
	ct_char_t				*mc_class_name;
	ct_resource_handle_t	*mc_rsrc_handles;
	ct_uint32_t				 mc_rsrc_handle_count;
} mc_enumerate_rsp_t;


/*
 *  A Query Response consists of a structure of type mc_query_rsp_t or
 *  mc_class_query_rsp_t.  The type mc_query_rsp_t is used if the response is
 *  from a resource and the type mc_class_query_rsp_t is used if the response
 *  is from a resource class.
 *  
 *  If the mc_error field indicates an error, the Resource Monitoring and
 *  Control Subsystem or a Resource Manager could not provide any or all of
 *  the requested information.  The error may also indicate that the command
 *  arguments were in error.  The error codes imply which of the remaining
 *  fields in the structure are defined. Otherwise, the mc_rsrc_hndl field
 *  specifies the resource handle of the resource, or the mc_class_name field
 *  specifies the name of the resource class, whose attributes are contained
 *  in this response.  The mc_peer_domain_name field specifies the name of the
 *  peer domain from which the attributes were obtained.  The mc_attrs field
 *  is a pointer to an array of the requested attributes; the mc_attr_count
 *  field indicates the number of entries in this array.
 */

typedef struct {
	mc_errnum_t				 mc_error;
	ct_resource_handle_t	 mc_rsrc_hndl;
	mc_attribute_t			*mc_attrs;
	ct_uint32_t				 mc_attr_count;
} mc_query_rsp_t;

typedef struct {
	mc_errnum_t				 mc_error;
	ct_char_t				*mc_class_name;
	ct_char_t				*mc_peer_domain_name;
	mc_attribute_t			*mc_attrs;
	ct_uint32_t				 mc_attr_count;
} mc_class_query_rsp_3_t;	

typedef struct {
	mc_errnum_t				 mc_error;
	ct_char_t				*mc_class_name;
	mc_attribute_t			*mc_attrs;
	ct_uint32_t				 mc_attr_count;
} mc_class_query_rsp_1_t;	


/*
 *  A Query Definition Resource Class Response consists of a structure of type 
 *  mc_qdef_rsrc_class_rsp_t.
 *  
 *  If the mc_error field indicates an error, the Resource Monitoring and
 *  Control Subsystem could not provide any or all of the requested
 *  information. The error may also indicate that the command arguments were
 *  in error. The error codes imply which of the remaining fields in the
 *  structure are defined.  Otherwise, mc_properties is a bit field that
 *  specifies the properties of the resource class, as defined by the
 *  mc_rsrc_class_props_t type. The mc_class_name and mc_class_id fields
 *  specify the resource class name and resource class ID, respectively. The
 *  mc_display_name field is a pointer to a string that is suitable to display
 *  as the name of this resource class in a Graphical User Interface. The
 *  mc_description field is a pointer to a string that contains a description
 *  of the resource class; the description may contains multiple lines of
 *  text. The mc_locator field specifies the name of a persistent attribute of
 *  the resource class that implies the location of a resource of this
 *  resource class. The mc_class_pattr_count field specifies the number of
 *  persistent attributes defined for the class itself. The
 *  mc_class_dattr_count field specifies the number of dynamic attributes
 *  defined for the class itself. The mc_pattr_count field specifies the
 *  number of persistent attributes defined for a resource. The mc_dattr_count
 *  field specifies the number of dynamic attributes defined for a
 *  resource. The mc_action_count specifies the number of different actions
 *  that can be invoked against the resources of the class. The
 *  mc_class_action_count specifies the num ber of different actions that can
 *  be invoked against the class itself. The mc_error_count specifies the
 *  number of different errors that can be injected into the resources of the
 *  class. The mc_rsrc_mgrs field is a pointer to an array of mc_rsrc_mgr_t
 *  types. Each element of this array specifies the resource managers that
 *  implement the resource class. The mc_rsrc_mgr_count field indicates the
 *  number of elements in the array.
 *
 *  Each Resource Manager that supports a resource class is specified in a
 *  mc_rsrc_mgr_t type.
 *  
 *  The resource manager name is specified by the mc_mgr_name field. When a
 *  resource manager is installed on a cluster node its ClassKey number is
 *  made available to the RMC Subsystem. The mc_first_key and mc_last_key
 *  fields specify a range of resource manager ClassKeys that implement this
 *  resource class. Note that there may be multiple entries specifying the
 *  same resource manager in the array specified by mc_rsrc_mgrs; however,
 *  each such entry specifies non-overlap ping ranges of ClassKeys.
 */

typedef struct {
	ct_char_t				*mc_mgr_name;
	ct_uint32_t				 mc_first_key;
	ct_uint32_t				 mc_last_key;
} mc_rsrc_mgr_t;

typedef struct {
	mc_errnum_t				 mc_error;
	mc_rsrc_class_props_t	 mc_properties;
	ct_char_t				*mc_class_name;
	rmc_resource_class_id_t	 mc_class_id;
	ct_char_t				*mc_display_name;
	ct_char_t				*mc_description;
	ct_char_t				*mc_locator;
	ct_uint32_t				 mc_class_pattr_count;
	ct_uint32_t				 mc_class_dattr_count;
	ct_uint32_t				 mc_pattr_count;
	ct_uint32_t				 mc_dattr_count;
	ct_uint32_t				 mc_action_count;
	ct_uint32_t				 mc_class_action_count;
	ct_uint32_t				 mc_error_count;
	mc_rsrc_mgr_t			*mc_rsrc_mgrs;
	ct_uint32_t				 mc_rsrc_mgr_count;
} mc_qdef_rsrc_class_rsp_t;


/*	
 *  A Query Definition Persistent Attribute Response consists of a structure
 *  of type mc_qdef_pattr_rsp_t.
 *  
 *  If the mc_error field indicates an error, the Resource Monitoring and
 *  Control Subsystem could not provide any or all of the requested
 *  information. The error may also indicate that the command arguments were
 *  in error. The error codes imply which of the remaining fields in the
 *  structure are defined.  Otherwise, mc_properties is a bit field that
 *  specifies the properties of the persistent attribute, as defined by the
 *  mc_pattr_props_t type. The mc_program_name field is a pointer to the pro-
 *  grammatic name of the attribute (this name is provided as input to other
 *  RMCAPI functions). The mc_display_name field is a pointer to a string that
 *  is suitable to display as the name of this attribute in a Graphical User
 *  Interface. The mc_group_name field is a pointer to a string that is
 *  suitable to display as the name of the group, to which this attribute
 *  belongs, in a Graphical User Interface. The mc_description field is a
 *  pointer to a string that contains a description of the persistent
 *  attribute; the description may contains multiple lines of text. The
 *  mc_attribute_id field specifies the attribute ID. The mc_group_id field
 *  specifies the group ID. This ID is used to group related attributes of a
 *  resource or the resource class. The mc_variety_list field is a pointer to
 *  an array of mc_variety_t types. Each element of the array is a range of
 *  resource variety numbers. This attribute then applies to any resource of
 *  the class, or the resource class itself if this response is that of a
 *  resource class persis tent attribute, which has one of the indicated
 *  variety numbers. The mc_variety_count field specifies the number of
 *  elements in the array. The mc_data_type field specifies the data type of
 *  the persistent attribute. The mc_default_value field specifies the default
 *  value this attribute assumes when a resource, for which this attribute is
 *  defined, is created.
 *
 *  N.B. The value of the mc_attribute_id field may be used as an index. The
 *  highest value of a resource or resource class persistent attribute ID is
 *  one less than the value of the mc_pattr_count or mc_class_pattr_count
 *  field of the Query Definition Resource Class Response, respectively.
 */

typedef struct {
	mc_errnum_t			 mc_error;
	mc_pattr_props_t	 mc_properties;
	ct_char_t			*mc_program_name;
	ct_char_t			*mc_display_name;
	ct_char_t			*mc_group_name;
	ct_char_t			*mc_description;
	rmc_attribute_id_t	 mc_attribute_id;
	ct_uint32_t			 mc_group_id;
	ct_data_type_t		 mc_data_type;
	mc_variety_t		*mc_variety_list;
	ct_uint32_t			 mc_variety_count;
	ct_value_t			 mc_default_value;	
} mc_qdef_pattr_rsp_t;


/*
 *  A Query Definition Dynamic Attribute Response consists of a structure of
 *  type mc_qdef_dattr_rsp_t.
 *  
 *  If the mc_error field indicates an error, the Resource Monitoring and
 *  Control Subsystem could not provide any or all of the requested
 *  information. The error may also indicate that the command arguments were
 *  in error. The error codes imply which of the remaining fields in the
 *  structure are defined. Otherwise, mc_properties is a bit field that
 *  specifies the properties of the dynamic attribute, as defined by the
 *  mc_dattr_props_t type. The mc_program_name field is a pointer to the
 *  programmatic name of the attribute (this name is provided as input to
 *  other RMCAPI functions). The mc_display_name field is a pointer to a
 *  string that is suitable to display as the name of this attribute in a
 *  Graphical User Interface. The mc_group_name field is a pointer to a string
 *  that is suitable to display as the name of the group, to which this
 *  attribute belongs, in a Graphical User Interface. The mc_description
 *  field is a pointer to a string that contains a description of the dynamic
 *  attribute; the description may contains multiple lines of text. The
 *  mc_attribute_id field specifies the attribute ID. The mc_group_id field
 *  specifies the group ID. This ID is used to group related attributes of a
 *  resource or the resource class. The mc_data_type field specifies the data
 *  type of the dynamic attribute.  The mc_variable_type field specifies the
 *  variable type of the dynamic attribute (a dynamic attribute is also known
 *  as variable), i.e. is it a Counter, Quantity, State, or Quantum. The
 *  mc_variety_list field is a pointer to an array of mc_variety_t types. Each
 *  element of the array is a range of resource variety numbers. This
 *  attribute then applies to any resource of the class, or the resource class
 *  itself if this response is that of a resource class dynamic attribute,
 *  which has one of the indicated variety numbers. The mc_variety_count field
 *  specifies the number of elements in the array. The mc_init_value field
 *  specifies the initial value this variable assumes the first time it is
 *  monitored. Thus, at the first observation of this variable, the initial
 *  value can be referenced as the previous value in an expression.  The
 *  mc_min_value and mc_max_value fields specify a dynamic range for the
 *  variable, i.e. what are the lowest and highest values of the variable that
 *  should be displayed in a GUI. This dynamic range is only defined if the
 *  attribute type is an arithmetic type. If the mc_expression field is a
 *  non-NULL pointer, it points to a string that is an example expression for
 *  this variable. If the mc_expression_description field is a non-NULL
 *  pointer, it points to a string that is a description of the event
 *  generated by the example expression. If the mc_rearm_expression field is a
 *  non-NULL pointer, it points to a string that is an example re-arm
 *  expression for this variable. If the mc_rearm_description field is a
 *  non-NULL pointer, it points to a string that is a description of the
 *  example re-arm expression. If the mc_PTX_name field is a non-NULL pointer,
 *  it points to a string that is the PTX path name for this variable.
 *
 *  N.B. The value of the mc_attribute_id field may be used as an index. The
 *  highest value of a resource or resource class dynamic attribute ID is one
 *  less than the value of the mc_dattr_count or mc_class_dattr_count field of
 *  the Query Definition Resource Class Response, respectively.
 */

typedef struct {
	mc_errnum_t				 mc_error;
	mc_dattr_props_t		 mc_properties;
	ct_char_t				*mc_program_name;
	ct_char_t				*mc_display_name;
	ct_char_t				*mc_group_name;
	ct_char_t				*mc_description;
	rmc_attribute_id_t		 mc_attribute_id;
	ct_uint32_t				 mc_group_id;
	ct_data_type_t			 mc_data_type;
	rmc_variable_type_t		 mc_variable_type;
	mc_variety_t			*mc_variety_list;
	ct_uint32_t				 mc_variety_count;
	ct_value_t				 mc_init_value;	
	ct_value_t				 mc_min_value;
	ct_value_t				 mc_max_value;
	ct_char_t				*mc_expression;
	ct_char_t				*mc_expression_description;
	ct_char_t				*mc_rearm_expression;
	ct_char_t				*mc_rearm_description;
	ct_char_t				*mc_PTX_name;
	ct_uint32_t				 mc_reporting_interval;
} mc_qdef_dattr_rsp_6_t;

typedef struct {
	mc_errnum_t				 mc_error;
	mc_dattr_props_t		 mc_properties;
	ct_char_t				*mc_program_name;
	ct_char_t				*mc_display_name;
	ct_char_t				*mc_group_name;
	ct_char_t				*mc_description;
	rmc_attribute_id_t		 mc_attribute_id;
	ct_uint32_t				 mc_group_id;
	ct_data_type_t			 mc_data_type;
	rmc_variable_type_t		 mc_variable_type;
	mc_variety_t			*mc_variety_list;
	ct_uint32_t				 mc_variety_count;
	ct_value_t				 mc_init_value;	
	ct_value_t				 mc_min_value;
	ct_value_t				 mc_max_value;
	ct_char_t				*mc_expression;
	ct_char_t				*mc_expression_description;
	ct_char_t				*mc_rearm_expression;
	ct_char_t				*mc_rearm_description;
	ct_char_t				*mc_PTX_name;
} mc_qdef_dattr_rsp_1_t;


/*
 *  A Query Definition Structured Byte String Response consists of a structure
 *  of type mc_qdef_sbs_rsp_t.
 *  
 *  If the mc_error field indicates an error, the Resource Monitoring and
 *  Control Subsystem could not provide any or all of the requested
 *  information. The error may also indicate that the command arguments were
 *  in error. The error codes imply which of the remaining fields in the
 *  structure are defined.  Otherwise, the mc_sbs_fields field is a pointer to
 *  an array of elements of type mc_sbs_field_t; the mc_field_count field
 *  specifies the number of entries in the array. The mc_attribute_id field is
 *  the id of the attribute for which this SBS definition is being returned.
 *  
 *  Individual Structured Byte String fields are described by the
 *  mc_sbs_field_t type.
 *  
 *  The mc_field_name field is a pointer to the programmatic name of the SBS
 *  field (this name is provided as input to other RMCAPI functions). The
 *  mc_display_name field is a pointer to a string that is suitable to display
 *  as the name of this field in a Graphical User Interface. The
 *  mc_description field is a pointer to a string that contains a description
 *  of the SBS field; the description may contains multiple lines of text. The
 *  mc_field_data_type field specifies the data type of the SBS field. The
 *  mc_min_value and mc_max_value fields specify a dynamic range for the SBS
 *  field, i.e. what are the lowest and highest values of the field that
 *  should be displayed in a GUI. This dynamic range is only defined if the
 *  field type is an arithmetic type. The mc_SBS_serial_number field specifies
 *  the serial number of this SBS field.
 */

typedef struct {
	ct_char_t				*mc_field_name;
	ct_char_t				*mc_display_name;
	ct_char_t				*mc_description;
	ct_sbs_field_data_type_t mc_field_data_type;
	ct_value_t				 mc_min_value;
	ct_value_t				 mc_max_value;
	ct_int8_t				 mc_SBS_serial_number;
} mc_sbs_field_t;

typedef struct {
	mc_errnum_t				 mc_error;
	mc_sbs_field_t			*mc_sbs_fields;
	ct_uint32_t				 mc_field_count;
	rmc_attribute_id_t		 mc_attribute_id;
} mc_qdef_sbs_rsp_t;


/*
 *  A Query Definition Structured Data Response consists of a structure of
 *  type mc_qdef_sd_rsp_t.
 *
 *  If the mc_error field indicates an error, the Resource Monitoring and
 *  Control Subsystem could not provide any or all of the requested
 *  information. The error may also indicate that the command arguments were
 *  in error. The error codes imply which of the remaining fields in the
 *  structure are defined.  Otherwise, the mc_sd_elements field is a pointer
 *  to an array of elements of type mc_sd_element_t; the mc_element_count
 *  field specifies the number of entries in the array.  The mc_usage field
 *  indicates if the mc_id field is the ID of an attribute or action for which
 *  this SD definition is being returned. If the ID is that of an attribute,
 *  then the mc_program_name field is a pointer to the programmatic name of
 *  the attribute and the mc_usage field indicates if the returned SD
 *  definition is that of a resource class persistent or dynamic attribute or
 *  resource persistent or dynamic attribute. If the ID is that of an action,
 *  then the mc_program_name field is a pointer to the programmatic name of
 *  the action and the mc_usage field indicates if the returned SD definition
 *  is that of an action input or response for a resource or class action. If
 *  this SD definition is that of a command argument, the mc_id and
 *  mc_program_name fields are undefined.
 *
 *  Individual Structured Data elements are described by the mc_sd_element_t
 *  type.
 *
 *  The mc_element_name field is a pointer to the programmatic name of the SD
 *  element (this name is provided as input to other RMCAPI functions). The
 *  mc_display_name field is a pointer to a string that is suitable to display
 *  as the name of this element in a Graphical User Interface. The
 *  mc_description field is a pointer to a string that contains a description
 *  of the SD element; the description may contains multiple lines of
 *  text. The mc_element_data_type field specifies the data type of the SD
 *  element. The mc_element_index field specifies the index of this SD
 *  element, i.e. the number that can be used as an index into the array
 *  specified by the elements field of a ct_structured_data_t type.
 */

typedef struct {
	ct_char_t		*mc_element_name;
	ct_char_t		*mc_display_name;
	ct_char_t		*mc_description;
	ct_data_type_t	 mc_element_data_type;
	ct_uint32_t		 mc_element_index;
} mc_sd_element_t;

typedef struct {
	mc_errnum_t		 mc_error;
	mc_sd_element_t	*mc_sd_elements;
	ct_uint32_t		 mc_element_count;
	ct_uint32_t		 mc_id;
	ct_char_t		*mc_program_name;
	mc_sd_usage_t	 mc_usage;
} mc_qdef_sd_rsp_t;


/*
 *  A Query Definition Valid Values Response consists of a structure of
 *  type mc_qdef_valid_vals_rsp_t.
 *  
 *  If the mc_error field indicates an error, the Resource Monitoring and
 *  Control Subsystem could not provide any or all of the requested
 *  information. The error may also indicate that the command arguments were
 *  in error. The error codes imply which of the remaining fields in the
 *  structure are defined.  Otherwise, if the mc_count field is not zero, the
 *  mc_valid_values field is a pointer to an array of elements of type
 *  mc_valid_value_t; the mc_count field specifies the number of entries in
 *  the array. Each entry in this array specifies a valid value or range of
 *  valid values for the attribute, input or argument. If the mc_count field
 *  is zero, then the name of an action that can be invoked to obtain valid
 *  values is specified by the mc_action_name field; the mc_action_type field
 *  indicates whether this is a resource action or class action.
 *
 *  The mc_usage field indicates if the mc_id field is the id of a persistent
 *  attribute, dynamic attribute, action or error for which these valid values
 *  are being returned, or for which the named action can be used to obtain
 *  valid values. If the id is that of a persistent attribute then the
 *  mc_usage field indicates if the valid values are that of a resource class
 *  persistent attribute or resource persistent attribute. If the id is that
 *  of a dynamic attribute then the mc_usage field indicates if the valid
 *  values are that of a resource class dynamic attribute or resource dynamic
 *  attribute.  If the id is that of an action then the mc_usage field indicates
 *  if the valid values are that of an action input for a resource or class
 *  action.  If the valid values are that of a command argument the mc_id
 *  field is undefined. If the returned valid values are those of an
 *  attribute, the mc_data_type field specifies the data type of the attribute
 *  and, except as noted below, the valid values. If the returned valid values
 *  are those of an action or error input or a command argument, the
 *  mc_data_type field is set to CT_SD_PTR.
 *
 *  If the mc_data_type field specifies an arithmetic type and the
 *  mc_low_value field is less than the mc_high_value field, a range of valid
 *  values is specified; otherwise, the mc_low_value field is equal to the
 *  mc_high_value field, specifying a single valid value. If the mc_data_type
 *  field specifies a non-arithmetic type, but not CT_SD_PTR or
 *  CT_SD_PTR_ARRAY, the mc_low_value field specifies the valid value and the
 *  mc_high_value field is undefined. If the mc_data_type field is not
 *  CT_SD_PTR or CT_SD_PTR_ARRAY, then the mc_sd_element_index and
 *  mc_sd_element_data_type fields are undefined.
 *
 *  If the mc_data_type field is CT_SD_PTR, then each returned
 *  mc_valid_value_t specifies a valid value, or range of valid values, for a
 *  single structured data element. The mc_sd_element_index field specifies
 *  the index of the SD element and the mc_sd_element_data_type field
 *  specifies the data type of the element. If the mc_sd_element_data_type
 *  field specifies an arithmetic type and the mc_low_value field is less than
 *  the mc_high_value field, a range of valid values is specified; otherwise,
 *  the mc_low_value field is equal to the mc_high_value field, specifying a
 *  single valid value. If the mc_sd_element_data_type field specifies a
 *  non-arithmetic type, the mc_low_value field specifies the valid value and
 *  the mc_high_value field is undefined. The mc_sd_element_data_type field is
 *  never set to CT_SD_PTR or CT_SD_PTR_ARRAY.
 *
 *  If the mc_data_type field is CT_SD_PTR_ARRAY, then the valid values
 *  returned apply to all ele ments with the identical index value in each SD
 *  of the array.
 *
 *  Note that when valid values are for an SD or SD array, each element of the
 *  SD may have varying numbers of valid values returned, including no
 *  returned valid values.
 *
 *  If any non-SD type is an array type then the valid value or valid value
 *  range applies to each element of the array.
 *
 *  In all cases the mc_label field, if non-NULL, specifies a pointer to a
 *  string containing a short description of the valid value or range.
 */

typedef struct {
	ct_value_t			 mc_low_value;
	ct_value_t			 mc_high_value;
	ct_char_t			*mc_label;
	ct_uint32_t			 mc_sd_element_index;
	ct_data_type_t		 mc_sd_element_data_type;
} mc_valid_value_t;

typedef struct {
	mc_errnum_t			 mc_error;
	mc_valid_value_t	*mc_valid_values;
	ct_uint32_t			 mc_count;
	ct_uint32_t			 mc_id;
	mc_vv_usage_t		 mc_usage;
	ct_data_type_t		 mc_data_type;
	ct_char_t			*mc_action_name;
	mc_action_type_t	 mc_action_type;
} mc_qdef_valid_vals_rsp_t;


/*
 *  A Query Definition Resource Actions Response consists of a structure of
 *  type mc_qdef_actions_rsp_t.
 *  
 *  If the mc_error field indicates an error, the Resource Monitoring and
 *  Control Subsystem could not provide any or all of the requested
 *  information. The error may also indicate that the command arguments were
 *  in error. The error codes imply which of the remaining fields in the
 *  structure are defined.  Otherwise, the mc_actions field is a pointer to an
 *  array of elements of type mc_action_t; the mc_action_count field specifies
 *  the number of entries in the array. The mc_class_id field is the id of the
 *  resource class for which these actions are being returned.
 *  
 *  Individual actions are described by the mc_action_t type.
 *  
 *  The mc_properties field is a bit field that specifies the properties of
 *  the action, as defined by the mc_action_props_t type. The mc_action_name
 *  field is a pointer to the programmatic name of the action (this name is
 *  provided as input to other RMCAPI functions). The mc_display_name field is
 *  a pointer to a string that is suitable to display as the name of this
 *  action in a Graphical User Interface. The mc_description field is a
 *  pointer to a string that contains a description of the action; the
 *  description may contains multiple lines of text. The mc_confirm_prompt
 *  field, if not NULL, is a pointer to a string that is used by a GUI to
 *  prompt the user for confirmation to perform the action. The mc_action_id
 *  field specifies the action ID. The mc_variety_list field is a pointer to
 *  an array of mc_variety_t types.  Each element of the array is a range of
 *  resource variety numbers. This action then applies to any resource of the
 *  class, or the resource class itself if this response is that of a resource
 *  class action, which has one of the indicated variety numbers. The
 *  mc_variety_count field specifies the number of elements in the array. The
 *  mc_timeout field specifies the approximate amount of time, in seconds,
 *  that the action should take to complete. This value is only defined if the
 *  MC_RSRC_ACTION_LONG_RUNNING property is set. The mc_permissions field
 *  specifies the permissions required to execute this action.
 *
 *  N.B. The value of the mc_action_id field may be used as an index. The
 *  highest value of a resource action or class action ID is one less than the
 *  value of the mc_action_count or mc_class_action_count field of the Query
 *  Definition Resource Class Response, respectively.
 */

typedef struct {
	mc_action_props_t		 mc_properties;
	ct_char_t				*mc_action_name;
	ct_char_t				*mc_display_name;
	ct_char_t				*mc_description;
	ct_char_t				*mc_confirm_prompt;
	rmc_action_id_t			 mc_action_id;
	mc_variety_t			*mc_variety_list;
	ct_uint32_t				 mc_variety_count;
	ct_uint32_t				 mc_timeout;
	ct_uint32_t				 mc_permissions;
} mc_action_t;

typedef struct {
	mc_errnum_t				 mc_error;
	mc_action_t				*mc_actions;
	ct_uint32_t				 mc_action_count;
	rmc_resource_class_id_t	 mc_class_id;
} mc_qdef_actions_rsp_t;


/*
 *  A Query Definition Resource Error Injection Response consists of a
 *  structure of type mc_qdef_err_inject_rsp_t.
 *  
 *  If the mc_error field indicates an error, the Resource Monitoring and
 *  Control Subsystem could not provide any or all of the requested
 *  information. The error may also indicate that the command arguments were
 *  in error. The error codes imply which of the remaining fields in the
 *  structure are defined.  Otherwise, the mc_error_injection field is a
 *  pointer to an array of elements of type mc_error_injection_t; the
 *  mc_error_injection_count field specifies the number of entries in the
 *  array. The mc_class_id field is the id of the resource class for which
 *  these error injections are being returned.
 *  
 *  Individual errors are described by the mc_error_injection_t type.
 *
 *  The mc_properties field is a bit field that specifies the properties of
 *  the error, as defined by the mc_error_props_t type. The mc_error_name
 *  field is a pointer to the programmatic name of the error (this name is
 *  provided as input to other RMCAPI functions). The mc_display_name field is
 *  a pointer to a string that is suitable to display as the name of this
 *  error in a Graphical User Interface. The mc_description field is a pointer
 *  to a string that contains a description of the error; the description may
 *  contains multiple lines of text. The mc_error_id field specifies the error
 *  ID. The mc_variety_list field is a pointer to an array of mc_variety_t
 *  types. Each element of the array is a range of resource variety
 *  numbers. This error then applies to any resource of the class which has
 *  one of the indicated variety numbers. The mc_variety_count field specifies
 *  the number of elements in the array. The mc_permissions field specifies
 *  the permissions required to inject this error.
 *
 *  N.B. The value of the mc_error_id field may be used as an index. The
 *  highest value of an error injection ID is one less than the value of the
 *  mc_error_count field of the Query Definition Resource Class Response.
 *
 */

typedef struct {
	mc_error_props_t		 mc_properties;
	ct_char_t				*mc_error_name;
	ct_char_t				*mc_display_name;
	ct_char_t				*mc_description;
	rmc_error_id_t			 mc_error_id;
	mc_variety_t			*mc_variety_list;
	ct_uint32_t				 mc_variety_count;
	ct_uint32_t				 mc_permissions;
} mc_error_injection_t;

typedef struct {
	mc_errnum_t				 mc_error;
	mc_error_injection_t	*mc_error_injection;
	ct_uint32_t				 mc_error_injection_count;
	rmc_resource_class_id_t	 mc_class_id;
} mc_qdef_err_inject_rsp_t;


/*
 *  A Query Definition Resource Dependencies Response consists of a structure
 *  of type mc_qdef_rsrc_deps_rsp_t.
 *  
 *  If the mc_error field indicates an error, the Resource Monitoring and
 *  Control Subsystem could not provide any or all of the requested
 *  information. The error may also indicate that the command arguments
 *  were in error. The error codes imply which of the remaining fields in
 *  the structure are defined.  Otherwise, the mc_class_ids field is a
 *  pointer to an array of elements of type uint16_t; the mc_id_count
 *  field specifies the number of entries in the array. Each ID in this
 *  array represent a resource class upon which the resource class,
 *  specified by the mc_class_id field, depends.
 */

typedef struct {
	mc_errnum_t				 mc_error;
	rmc_resource_class_id_t	*mc_class_ids;
	ct_uint32_t				 mc_id_count;
	rmc_resource_class_id_t	 mc_class_id;
} mc_qdef_rsrc_deps_rsp_t;


/*
 *  The Resource Handle Response consists of a structure of type
 *  mc_rsrc_hndl_rsp_t.
 *  
 *  The Resource Handle Response is the response to a number of different
 *  commands, where the only information needed in response is a resource
 *  handle. If the mc_error field indicates no error, then the command was
 *  successful and the resource handle specifies the resource which was the
 *  target of the command. If there is an error, the error codes indicate
 *  whether the resource handle contained in mc_rsrc_hndl is invalid or the
 *  command could not be completed for the resource specified by the resource
 *  handle. The error may also indicate that the command arguments were in
 *  error.
 */

typedef struct {
	mc_errnum_t				 mc_error;
	ct_resource_handle_t	 mc_rsrc_hndl;
} mc_rsrc_hndl_rsp_t;


/*
 *  The Class Name Response consists of a structure of type mc_class_name_rsp_t.
 *
 *  The Class Name Response is the response to a number of different commands,
 *  where the only information needed in the response is a class name. If the
 *  mc_error field indicates no error, then the command was successful and the
 *  class name specifies the resource class which was the target of the
 *  command. If there is an error, the error codes indicate whether the class
 *  name specified by mc_class_name is invalid or the command could not be
 *  completed for the resource class specified by the class name. The error
 *  may also indicate that the command arguments were in error.
 */

typedef struct {
	mc_errnum_t				 mc_error;
	ct_char_t				*mc_class_name;
} mc_class_name_rsp_t;


/*
 *  The Define Resource Response consists of a structure of type
 *  mc_define_rsrc_rsp_t.
 *  
 *  If the mc_error field indicates an error, the Resource Monitoring and
 *  Control Subsystem or a Resource Manager could not complete the command.
 *  The error may also indicate that the command arguments were in error.  The
 *  error codes imply which of the remaining fields in the structure are
 *  defined.  Otherwise, the mc_class_name field specifies the name of the
 *  resource class in which a new resource instance is defined.  The
 *  mc_rsrc_hndl field specifies the resource handle of the new resource
 *  instance.
 */

typedef struct {
	mc_errnum_t				 mc_error;
	ct_char_t				*mc_class_name;
	ct_resource_handle_t	 mc_rsrc_hndl;
} mc_define_rsrc_rsp_t;


/*
 *  The Undefine Resource Response consists of a structure of type
 *  mc_undefine_rsrc_rsp_t.
 *  
 *  If the mc_error field indicates an error, the Resource Monitoring and
 *  Control Subsystem or a Resource Manager could not complete the command.
 *  The error may also indicate that the command arguments were in error.  The
 *  error codes imply which of the remaining fields in the structure are
 *  undefined.  Otherwise, the mc_class_name field specifies the name of the
 *  resource class from which the resource instance is deleted.  The
 *  mc_rsrc_hndl field specifies the resource handle of the deleted resource
 *  instance.
 */

typedef struct {
	mc_errnum_t				 mc_error;
	ct_char_t				*mc_class_name;
	ct_resource_handle_t	 mc_rsrc_hndl;
} mc_undefine_rsrc_rsp_t;


/*
 *  An Integrity Check Response consists of a structure of type
 *  mc_integrity_chk_rsp_t.
 *  
 *  The mc_class_name field specifies the name of the resource class
 *  which was requested to perform integrity checks. If the mc_error field
 *  indicates no error, then all integrity checks were performed
 *  successfully. Otherwise, one response is returned for each integrity check
 *  that was not performed successfully; the mc_error field indicates the
 *  nature of the problem. The mc_check_severity field indicates the severity
 *  of the problem and a flag in the mc_check_flags field indicates whether or
 *  not the problem was fixed.
 */

typedef struct {
	mc_errnum_t				 mc_error;
	ct_char_t				*mc_class_name;
	mc_check_flags_t		 mc_check_flags;
	rmc_severity_t			 mc_check_severity;
} mc_integrity_chk_rsp_t;


/*
 *  A Set Attribute Response consists of a structure of type mc_set_rsp_t or
 *  mc_class_set_rsp_t.  The type mc_set_rsp_t is used if the response is from
 *  a resource and the type mc_class_set_rsp_t is used if the response is from
 *  a resource class.
 *  
 *  If the mc_error field indicates no error, the mc_rsrc_hndl field specifies
 *  the resource handle of the resource, or the mc_class_name field specifies
 *  the name of the resource class, which was the target of the set resource
 *  attribute command.  The mc_peer_domain_name field specifies the name of
 *  the peer domain where the attributes were set.  If an error is indicated
 *  the mc_rsrc_hndl field contains the resource handle specified on the
 *  command or the mc_class_name field is a pointer to the name of the
 *  resource class specified on the command.  Furthermore, if the
 *  mc_attr_count field is non-zero, the mc_error_attrs field contains a
 *  pointer to an array of attributes that could not be set, where each array
 *  element is of mc_error_attr_t type.  The mc_attr_count field indicates the
 *  number of array elements.
 *  
 *  In the mc_error_attr_t type, the mc_error field indicates the reason the
 *  attribute could not be set and the mc_at_name field indicates the name of
 *  the attribute that could not be set.
 */

typedef struct {
	mc_errnum_t				 mc_error;
	ct_char_t				*mc_at_name;
} mc_error_attr_t;

typedef struct {
	mc_errnum_t				 mc_error;
	ct_resource_handle_t	 mc_rsrc_hndl;
	mc_error_attr_t			*mc_error_attrs;
	ct_uint32_t				 mc_attr_count;
} mc_set_rsp_t;

typedef struct {
	mc_errnum_t				 mc_error;
	ct_char_t				*mc_class_name;
	ct_char_t				*mc_peer_domain_name;
	mc_error_attr_t			*mc_error_attrs;
	ct_uint32_t				 mc_attr_count;
} mc_class_set_rsp_3_t;

typedef struct {
	mc_errnum_t				 mc_error;
	ct_char_t				*mc_class_name;
	mc_error_attr_t			*mc_error_attrs;
	ct_uint32_t				 mc_attr_count;
} mc_class_set_rsp_1_t;


/*
 *  An Invoke Action Response consists of a structure of type mc_action_rsp_t
 *  or mc_class_action_rsp_t.  The type mc_action_rsp_t is used if the
 *  response is from a resource and the type mc_class_action_rsp_t is used if
 *  the response is from a resource class.
 *  
 *  The mc_rsrc_hndl field specifies the resource handle of the resource, or
 *  the mc_class_name field specifies the name of the resource class, which
 *  was the target of the invoke action command.  The mc_node_name field
 *  specifies the primary node name of the node where the class action was
 *  invoked.  The mc_peer_domain_name field specifies the name of the peer
 *  domain where the class action was invoked.  The mc_error field indicates
 *  whether or not there was an error in processing the action. If the
 *  mc_count field is non-zero, then the mc_data field is a pointer to an
 *  array of pointers to Structured Data resulting from the action; mc_count
 *  indicates the number of pointers in the array. If the mc_count field is
 *  zero then the mc_data field is undefined. Each SD in the response has an
 *  identical format, as defined for the action resulting in the
 *  response. More than one response may be generated from invoking an action,
 *  each containing one or more SDs.
 */

typedef struct {
	mc_errnum_t				 mc_error;
	ct_resource_handle_t	 mc_rsrc_hndl;
	ct_structured_data_t   **mc_data;
	ct_uint32_t				 mc_count;
} mc_action_rsp_t;

typedef struct {
	mc_errnum_t				 mc_error;
	ct_char_t				*mc_class_name;
	ct_structured_data_t   **mc_data;
	ct_uint32_t				 mc_count;
	ct_char_t				*mc_node_name;
	ct_char_t				*mc_peer_domain_name;
} mc_class_action_rsp_3_t;

typedef struct {
	mc_errnum_t				 mc_error;
	ct_char_t				*mc_class_name;
	ct_structured_data_t   **mc_data;
	ct_uint32_t				 mc_count;
	ct_char_t				*mc_node_name;
} mc_class_action_rsp_2_t;

typedef struct {
	mc_errnum_t				 mc_error;
	ct_char_t				*mc_class_name;
	ct_structured_data_t   **mc_data;
	ct_uint32_t				 mc_count;
} mc_class_action_rsp_1_t;


/*
 *  An Enumerate Constraints Response consists of a structure of type
 *  mc_constraint_rsp_t.
 *  
 *  If the mc_error field indicates no error, the mc_rsrc_hndl field specifies
 *  the resource handle of the resource whose constraints are being
 *  returned. The mc_constraint field points to an array of pointers to
 *  constraints; the mc_constraint_count field indicates the number of
 *  pointers in the array. If the count is zero there are no constraints and
 *  the mc_constraint field is undefined. If an error is indicated the
 *  mc_rsrc_hndl field contains the resource handle specified on the command.
 */

typedef struct {
	mc_errnum_t				 mc_error;
	ct_resource_handle_t	 mc_rsrc_hndl;
	rmc_constraint_t	   **mc_constraints;
	ct_uint32_t				 mc_constraint_count;
} mc_constraint_rsp_t;


/*
 *  A Get Control Log Response consists of a structure of type
 *  mc_control_log_rsp_t.
 *  
 *  If the mc_error field indicates no error, the mc_rsrc_hndl field specifies
 *  the resource handle of the resource whose control log is being
 *  returned. The mc_entry_count field indicates the number of entries in the
 *  control log and the mc_log field is a pointer to an array of control log
 *  entries, as specified below. If there are no entries currently in the
 *  control log the mc_entry_count field is 0 and the mc_log field is
 *  undefined. If an error is indicated the mc_rsrc_hndl field contains the
 *  resource handle specified on the command.
 *  
 *  In the mc_control_log_entry_t type, the mc_log_error field specifies error
 *  information for this log entry, if any. The mc_log_entry_type field
 *  indicates the type of control log entry. The mc_timestamp field indicates
 *  the time the log entry was made.
 */

typedef struct {
	mc_errnum_t				 mc_log_error;
	rmc_log_entry_type_t	 mc_log_entry_type;
	time_t					 mc_log_timestamp;
} mc_control_log_entry_t;

typedef struct {
	mc_errnum_t				 mc_error;
	ct_resource_handle_t	 mc_rsrc_hndl;
	mc_control_log_entry_t	*mc_log;
	ct_uint32_t				 mc_entry_count;
} mc_control_log_rsp_t;


/*
 *  The format of a RMC/CtSec ACL is defined by mc_acl_t.
 *
 *  The mc_type field indicates the type of the ACL: Resource ACL, Resource
 *  Initial ACL, Resource Shared ACL, or Class ACL.
 *
 *  The mc_flags field may be used by a Resource ACL or Resource Initial ACL
 *  to direct the use of the Resource Shared ACL.  If the flag is set
 *  directing the use of the Resource Shared ACL, the mc_value and mc_length
 *  fields are not interpreted.
 *
 *  If the mc_flags field does not direct the use of the Resource Shared ACL,
 *  the mc_value field points to the beginning of the memory location holding
 *  the CtSec ACL, and the mc_length field indicates the size of the CtSec
 *  ACL.  Note that a CtSec ACL can be empty, indicating no access to the
 *  resource or class.  An empty CtSec ACL is represented in the mc_acl_t type
 *  with NULL and 0 values for the mc_value and mc_length fields,
 *  respectively.
 */
	
typedef struct {
	mc_acl_type_t	mc_type;
	mc_acl_flags_t	mc_flags;
	void		   *mc_value;
	ct_uint32_t		mc_length;
} mc_acl_t;


/*
 *  A Get Resource-Specific ACL Response consists of a structure of type
 *  mc_get_acl_rsp_t.
 */

typedef struct {
	mc_errnum_t				 mc_error;
	ct_resource_handle_t	 mc_rsrc_hndl;
	mc_acl_t				 mc_acl;
} mc_get_acl_rsp_t;


/*
 *  A Get Class-Wide ACL Response consists of a structure of type
 *  mc_class_get_acl_rsp_t.
 */

typedef struct {
	mc_errnum_t				 mc_error;
	ct_char_t				*mc_class_name;
	ct_char_t				*mc_node_name;
	ct_char_t				*mc_peer_domain_name;
	mc_acl_t				 mc_acl;
} mc_class_get_acl_rsp_t;	


/*
 *  A Set Class-Wide ACL Response consists of a structure of type
 *  mc_class_set_acl_rsp_t.
 */

typedef struct {
	mc_errnum_t				 mc_error;
	ct_char_t				*mc_class_name;
	ct_char_t				*mc_node_name;
	ct_char_t				*mc_peer_domain_name;
} mc_class_set_acl_rsp_t;	


/*--------------------------------------------------------------------------*/
/*  Resource Monitoring and Control (RMC) API callback function prototypes. */
/*--------------------------------------------------------------------------*/


typedef void
(mc_complete_cb_t)(				/* Command Group Complete Callback			*/
	mc_sess_hndl_t,				/* session handle							*/
	ct_int32_t,					/* error value								*/
	void *						/* callback argument						*/
);

typedef void
(mc_event_cb_6_t)(				/* Event Notification Callback				*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_event_6_t *,				/* event notification data					*/
	void *						/* callback argument						*/
);

typedef void
(mc_event_cb_2_t)(				/* Event Notification Callback				*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_event_2_t *,				/* event notification data					*/
	void *						/* callback argument						*/
);

typedef void
(mc_event_cb_1_t)(				/* Event Notification Callback				*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_event_1_t *,				/* event notification data					*/
	void *						/* callback argument						*/
);

typedef void
(mc_class_event_cb_6_t)(		/* Class Event Notification Callback		*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_class_event_6_t *,		/* class event notification data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_class_event_cb_3_t)(		/* Class Event Notification Callback		*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_class_event_3_t *,		/* class event notification data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_class_event_cb_1_t)(		/* Class Event Notification Callback		*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_class_event_1_t *,		/* class event notification data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_reg_cb_t)(					/* Registration Response Callback			*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_reg_rsp_t *,				/* registration response data				*/
	void *						/* callback argument						*/
);

typedef void
(mc_unreg_cb_t)(				/* Unregistration Response Callback			*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_unreg_rsp_t *,			/* unregistration response data				*/
	void *						/* callback argument						*/
);

typedef void
(mc_query_event_cb_t)(			/* Query Event Response Callback			*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_query_event_rsp_t *,		/* query event response data				*/
	void *						/* callback argument						*/
);

typedef void
(mc_enumerate_cb_t)(			/* Enumerate Resources Callback				*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_enumerate_rsp_t *,		/* enumerate resources response data		*/
	void *						/* callback argument						*/
);

typedef void
(mc_query_cb_t)(				/* Query Resource Callback					*/ 
	mc_sess_hndl_t,				/* session handle							*/
	mc_query_rsp_t *,			/* query resource response data				*/
	void *						/* callback argument						*/
);

typedef void
(mc_class_query_cb_3_t)(		/* Query Class Resource Callback			*/ 
	mc_sess_hndl_t,				/* session handle							*/
	mc_class_query_rsp_3_t *,	/* query class response data				*/
	void *						/* callback argument						*/
);

typedef void
(mc_class_query_cb_1_t)(		/* Query Class Resource Callback			*/ 
	mc_sess_hndl_t,				/* session handle							*/
	mc_class_query_rsp_1_t *,	/* query class response data				*/
	void *						/* callback argument						*/
);

typedef void
(mc_qdef_rsrc_class_cb_t)(		/* Query Resource Class Definitions C.B.	*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_qdef_rsrc_class_rsp_t *,	/* query resource class definitions data	*/
	void *						/* callback argument						*/
);

typedef void
(mc_qdef_pattr_cb_t)(			/* Query Persistent Attribute Defns. C.B.	*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_qdef_pattr_rsp_t *,		/* query persistent attribute defns. data	*/
	void *						/* callback argument						*/
);

typedef void
(mc_qdef_dattr_cb_6_t)(			/* Query Dynamic Attribute Definitions C.B.	*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_qdef_dattr_rsp_6_t *,	/* query dynamic attribute defns. data		*/
	void *						/* callback argument						*/
);

typedef void
(mc_qdef_dattr_cb_1_t)(			/* Query Dynamic Attribute Definitions C.B.	*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_qdef_dattr_rsp_1_t *,	/* query dynamic attribute defns. data		*/
	void *						/* callback argument						*/
);

typedef void
(mc_qdef_sbs_cb_t)(				/* Query Structured Byte String Defns. C.B.	*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_qdef_sbs_rsp_t *,		/* query structured byte string defns. data	*/
	void *						/* callback argument						*/
);

typedef void
(mc_qdef_sd_cb_t)(				/* Query Structured Data Callback			*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_qdef_sd_rsp_t *,			/* query structured data response data		*/
	void *						/* callback argument						*/
);

typedef void
(mc_qdef_valid_vals_cb_t)(		/* Query Valid Value Definitions Callback	*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_qdef_valid_vals_rsp_t *,	/* query valid value definitions data		*/
	void *						/* callback argument						*/
);

typedef void
(mc_qdef_actions_cb_t)(			/* Query Action Definitions Callback		*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_qdef_actions_rsp_t *,	/* query action definitions data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_qdef_err_inject_cb_t)(		/* Query Error Injection Definitions C.B.	*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_qdef_err_inject_rsp_t *,	/* query error injections definitions data	*/
	void *						/* callback argument						*/
);

typedef void
(mc_qdef_rsrc_deps_cb_t)(		/* Query Resource Dependency Defns. C.B.	*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_qdef_rsrc_deps_rsp_t *,	/* query resource dependency defns. data	*/
	void *						/* callback argument						*/
);

typedef void
(mc_val_rsrc_hndl_cb_t)(		/* Validate Resource Handles Callback		*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_rsrc_hndl_rsp_t *,		/* resource handle response data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_def_rsrc_cb_t)(				/* Define a Resource Callback				*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_define_rsrc_rsp_t *,		/* define resource response data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_undef_rsrc_cb_t)(			/* Undefine a Resource Callback				*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_undefine_rsrc_rsp_t *,	/* undefine resource response data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_refresh_cfg_cb_t)(			/* Refresh Resource Configuration Callback	*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_class_name_rsp_t *,		/* class name response data					*/
	void *						/* callback argument						*/
);

typedef void
(mc_integrity_chk_cb_t)(		/* Do Integrity Check Callback				*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_integrity_chk_rsp_t *,	/* do integrity check response data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_set_cb_t)(					/* Set Resource Attributes Callback			*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_set_rsp_t *,				/* set resource attributes response data	*/
	void *						/* callback argument						*/
);

typedef void
(mc_class_set_cb_3_t)(			/* Set Class Attributes Callback			*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_class_set_rsp_3_t *,		/* set class attributes response data		*/
	void *						/* callback argument						*/
);

typedef void
(mc_class_set_cb_1_t)(			/* Set Class Attributes Callback			*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_class_set_rsp_1_t *,		/* set class attributes response data		*/
	void *						/* callback argument						*/
);

typedef void
(mc_action_cb_t)(				/* Invoke Action Callback					*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_action_rsp_t *,			/* invoke action response data				*/
	void *						/* callback argument						*/
);

typedef void
(mc_class_action_cb_3_t)(		/* Invoke Class Action Callback				*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_class_action_rsp_3_t *,	/* invoke class action response data		*/
	void *						/* callback argument						*/
);

typedef void
(mc_class_action_cb_2_t)(		/* Invoke Class Action Callback				*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_class_action_rsp_2_t *,	/* invoke class action response data		*/
	void *						/* callback argument						*/
);

typedef void
(mc_class_action_cb_1_t)(		/* Invoke Class Action Callback				*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_class_action_rsp_1_t *,	/* invoke class action response data		*/
	void *						/* callback argument						*/
);

typedef void
(mc_enum_constraints_cb_t)(		/* Enumerate Constraints Callback			*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_constraint_rsp_t *,		/* enumerate constraints response			*/
	void *						/* callback argument						*/
);

typedef void
(mc_define_constraint_cb_t)(	/* Define Constraint Callback				*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_rsrc_hndl_rsp_t *,		/* resource handle response data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_undefine_constraint_cb_t)(	/* Undefine Constraint Callback				*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_rsrc_hndl_rsp_t *,		/* resource handle response data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_online_cb_t)(				/* Bring a Resource On-line Callback		*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_rsrc_hndl_rsp_t *,		/* resource handle response data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_offline_cb_t)(				/* Take a Resource Off-line Callback		*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_rsrc_hndl_rsp_t *,		/* resource handle response data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_reset_cb_t)(				/* Force a Resource Off-line Callback		*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_rsrc_hndl_rsp_t *,		/* resource handle response data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_advisory_cb_t)(				/* Constraint Advisory Callback				*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_rsrc_hndl_rsp_t *,		/* resource handle response data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_get_control_log_cb_t)(		/* Get Control Log Callback					*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_control_log_rsp_t *,		/* get control log response data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_inject_error_cb_t)(			/* Inject an Error into a Resource C.B.		*/
	mc_sess_hndl_t,				/* session handle							*/
	mc_rsrc_hndl_rsp_t *,		/* resource handle response data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_get_acl_cb_t)(				/* Get Resource-Specific ACL Callback		*/ 
	mc_sess_hndl_t,				/* session handle							*/
	mc_get_acl_rsp_t *,			/* get resource ACL response data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_class_get_acl_cb_t)(		/* Get Class-Wide ACL Callback				*/ 
	mc_sess_hndl_t,				/* session handle							*/
	mc_class_get_acl_rsp_t *,	/* get class ACL response data				*/
	void *						/* callback argument						*/
);

typedef void
(mc_set_acl_cb_t)(				/* Set Resource-Specific ACL Callback		*/ 
	mc_sess_hndl_t,				/* session handle							*/
	mc_rsrc_hndl_rsp_t *,		/* set resource ACL response data			*/
	void *						/* callback argument						*/
);

typedef void
(mc_class_set_acl_cb_t)(		/* Set Class-Wide ACL Callback				*/ 
	mc_sess_hndl_t,				/* session handle							*/
	mc_class_set_acl_rsp_t *,	/* set class ACL response data				*/
	void *						/* callback argument						*/
);


/*--------------------------------------------------------------------------*/
/*	Resource Monitoring and Control (RMC) -									*/
/*	  Function Prototypes for Session Interfaces							*/
/*--------------------------------------------------------------------------*/

extern ct_int32_t
mc_start_session_6(						/* Start a RMC session				*/
	ct_contact_t   *contact_array,		/* input:  contact array			*/
	ct_uint32_t		number_of_contacts,	/* input:  number of contacts		*/
	mc_session_opts_t options,			/* input:  session options			*/
	mc_sess_hndl_t *session_hndl		/* output: session handle			*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_start_session_5(						/* Start a RMC session				*/
	ct_contact_t   *contact_array,		/* input:  contact array			*/
	ct_uint32_t		number_of_contacts,	/* input:  number of contacts		*/
	mc_session_opts_t options,			/* input:  session options			*/
	mc_sess_hndl_t *session_hndl		/* output: session handle			*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_start_session_4(						/* Start a RMC session				*/
	ct_contact_t   *contact_array,		/* input:  contact array			*/
	ct_uint32_t		number_of_contacts,	/* input:  number of contacts		*/
	mc_session_opts_t options,			/* input:  session options			*/
	mc_sess_hndl_t *session_hndl		/* output: session handle			*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_start_session_3(						/* Start a RMC session				*/
	ct_contact_t   *contact_array,		/* input:  contact array			*/
	ct_uint32_t		number_of_contacts,	/* input:  number of contacts		*/
	mc_session_opts_t options,			/* input:  session options			*/
	mc_sess_hndl_t *session_hndl		/* output: session handle			*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_start_session_2(						/* Start a RMC session				*/
	ct_contact_t   *contact_array,		/* input:  contact array			*/
	ct_uint32_t		number_of_contacts,	/* input:  number of contacts		*/
	mc_session_opts_t options,			/* input:  session options			*/
	mc_sess_hndl_t *session_hndl		/* output: session handle			*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_start_session_1(						/* Start a RMC session				*/
	ct_contact_t   *contact_array,		/* input:  contact array			*/
	ct_uint32_t		number_of_contacts,	/* input:  number of contacts		*/
	mc_session_opts_t options,			/* input:  session options			*/
	mc_sess_hndl_t *session_hndl		/* output: session handle			*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_timed_start_session_6(				/* Start a RMC session, with timeouts */
	ct_contact_t	  *contact_array,	/* input:  contact array			  */
	ct_uint32_t		   num_contacts,	/* input:  number of contacts		  */
	mc_session_opts_t  options,			/* input:  session options			  */
	ct_uint32_t		   start_timeout,	/* input:  start timeout in seconds	  */
	ct_uint32_t		   cmd_timeout,		/* input:  command timeout in seconds */
	mc_sess_hndl_t	  *session_hndl		/* output: session handle			  */
);										/* return: 0 or error number		  */

extern ct_int32_t
mc_timed_start_session_5(				/* Start a RMC session, with timeouts */
	ct_contact_t	  *contact_array,	/* input:  contact array			  */
	ct_uint32_t		   num_contacts,	/* input:  number of contacts		  */
	mc_session_opts_t  options,			/* input:  session options			  */
	ct_uint32_t		   start_timeout,	/* input:  start timeout in seconds	  */
	ct_uint32_t		   cmd_timeout,		/* input:  command timeout in seconds */
	mc_sess_hndl_t	  *session_hndl		/* output: session handle			  */
);										/* return: 0 or error number		  */

extern ct_int32_t
mc_timed_start_session_4(				/* Start a RMC session, with timeouts */
	ct_contact_t	  *contact_array,	/* input:  contact array			  */
	ct_uint32_t		   num_contacts,	/* input:  number of contacts		  */
	mc_session_opts_t  options,			/* input:  session options			  */
	ct_uint32_t		   start_timeout,	/* input:  start timeout in seconds	  */
	ct_uint32_t		   cmd_timeout,		/* input:  command timeout in seconds */
	mc_sess_hndl_t	  *session_hndl		/* output: session handle			  */
);										/* return: 0 or error number		  */

extern ct_int32_t
mc_timed_start_session_3(				/* Start a RMC session, with timeouts */
	ct_contact_t	  *contact_array,	/* input:  contact array			  */
	ct_uint32_t		   num_contacts,	/* input:  number of contacts		  */
	mc_session_opts_t  options,			/* input:  session options			  */
	ct_uint32_t		   start_timeout,	/* input:  start timeout in seconds	  */
	ct_uint32_t		   cmd_timeout,		/* input:  command timeout in seconds */
	mc_sess_hndl_t	  *session_hndl		/* output: session handle			  */
);										/* return: 0 or error number		  */

extern ct_int32_t
mc_timed_start_session_2(				/* Start a RMC session, with timeouts */
	ct_contact_t	  *contact_array,	/* input:  contact array			  */
	ct_uint32_t		   num_contacts,	/* input:  number of contacts		  */
	mc_session_opts_t  options,			/* input:  session options			  */
	ct_uint32_t		   start_timeout,	/* input:  start timeout in seconds	  */
	ct_uint32_t		   cmd_timeout,		/* input:  command timeout in seconds */
	mc_sess_hndl_t	  *session_hndl		/* output: session handle			  */
);										/* return: 0 or error number		  */

extern ct_int32_t
mc_end_session_1(						/* End a RMC session				*/
	mc_sess_hndl_t	 session_hndl		/* input:  session handle			*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_session_status_2(
	mc_sess_hndl_t	  session_hndl,		/* input:  session handle			*/
	mc_sess_status_t *session_status	/* output: session status			*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_session_info_2(
	mc_sess_hndl_t	  session_hndl,		/* input:  session handle			  */
	mc_sess_info_t	  info_type,		/* input:  type of information		  */
	void			 *info_return		/* output: returned information		  */
										/*           actual data type depends */
										/*           on information requested */
										/*           (see mc_sess_info_t)	  */
);										/* return: 0 or error number		  */

extern ct_int32_t
mc_get_descriptor_1(					/* Get RMC session file descriptor	*/
	mc_sess_hndl_t	 session_hndl,		/* input:  session handle			*/
	int				*descriptor			/* output: session file descriptor	*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_free_descriptor_1(					/* Free RMC session file descriptor */
	mc_sess_hndl_t	 session_hndl,		/* input:  session handle			*/
	int				 descriptor			/* input:  session file descriptor	*/
);										/* return: 0 or error number		*/


/*--------------------------------------------------------------------------*/
/*	Resource Monitoring and Control (RMC) -									*/
/*	  Function Prototypes for Command Management Interfaces					*/
/*--------------------------------------------------------------------------*/

extern ct_int32_t
mc_dispatch_1(							/* Dispatch thread					*/
	mc_sess_hndl_t		 session_hndl,	/* input:  session handle			*/
	mc_dispatch_opts_t	 options		/* input:  dispatch options			*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_start_cmd_grp_1(						/* Start command group				*/
	mc_sess_hndl_t		 session_hndl,	/* input:  session handle			*/
	mc_cmd_grp_opts_t	 options,		/* input:  command group options	*/
	mc_cmdgrp_hndl_t	*cmdgrp_hndl	/* output: command group handle		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_cancel_cmd_grp_1(					/* Cancel command group				*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl	/* input:  command group handle		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_send_cmd_grp_1(						/* Send command group				*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_complete_cb_t	*complete_cb,	/* input:  complete callback		*/
	void				*cb_arg			/* input:  client callback argument	*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_send_cmd_grp_wait_1(					/* Send command group and wait		*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl	/* input:  command group handle		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_free_response_1(						/* Free response					*/
	void				*rsp_ptr		/* input:  response to free			*/
);										/* return: 0 or error number		*/


/*--------------------------------------------------------------------------*/
/*	Resource Monitoring and Control (RMC) -									*/
/*	  Function Prototypes for Monitoring Command Interfaces					*/
/*--------------------------------------------------------------------------*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_select_bp_6(				/*		using Attribute Selection	*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_reg_rsp_t	 **response,		/* output: response					*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_event_cb_6_t	  *event_cb,		/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_select_ap_6(				/*		using Attribute Selection	*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_reg_rsp_t	 **response,		/* output: response					*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_event_cb_6_t	  *event_cb,		/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_select_bc_6(				/*		using Attribute Selection	*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_reg_cb_t		  *reg_cb,			/* input:  registration response cb */
	void			  *reg_cb_arg,		/* input:  callback argument		*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_event_cb_6_t	  *event_cb,		/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_select_ac_6(				/*		using Attribute Selection	*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_reg_cb_t		  *reg_cb,			/* input:  registration response cb */
	void			  *reg_cb_arg,		/* input:  callback argument		*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_event_cb_6_t	  *event_cb,		/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_handle_bp_6(				/*		using Resource Handle		*/
	mc_sess_hndl_t		 sess_hndl,		/* input:  session handle			*/
	mc_reg_rsp_t	   **response,		/* output: response					*/
	mc_reg_opts_t		 options,		/* input:  registration options		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t			 attr_count,	/* input:  count of attrs to return	*/
	ct_char_t			*expr,			/* input:  registration expression	*/
	ct_char_t			*raexpr,		/* input:  registration rearm expr. */
	mc_event_cb_6_t		*event_cb,		/* input:  event notification c.b.	*/
	void				*event_cb_arg	/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_handle_ap_6(				/*		using Resource Handle		*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_reg_rsp_t	   **response,		/* output: response					*/
	mc_reg_opts_t		 options,		/* input:  registration options		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t			 attr_count,	/* input:  count of attrs to return	*/
	ct_char_t			*expr,			/* input:  registration expression	*/
	ct_char_t			*raexpr,		/* input:  registration rearm expr. */
	mc_event_cb_6_t		*event_cb,		/* input:  event notification c.b.	*/
	void				*event_cb_arg	/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_handle_bc_6(				/*		using Resource Handle		*/
	mc_sess_hndl_t		 sess_hndl,		/* input:  session handle			*/
	mc_reg_cb_t			*reg_cb,		/* input:  registration response cb */
	void				*reg_cb_arg,	/* input:  callback argument		*/
	mc_reg_opts_t		 options,		/* input:  registration options		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t			 attr_count,	/* input:  count of attrs to return	*/
	ct_char_t			*expr,			/* input:  registration expression	*/
	ct_char_t			*raexpr,		/* input:  registration rearm expr. */
	mc_event_cb_6_t		*event_cb,		/* input:  event notification c.b.	*/
	void				*event_cb_arg	/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_handle_ac_6(				/*		using Resource Handle		*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_reg_cb_t			*reg_cb,		/* input:  registration response cb */
	void				*reg_cb_arg,	/* input:  callback argument		*/
	mc_reg_opts_t		 options,		/* input:  registration options		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t			 attr_count,	/* input:  count of attrs to return	*/
	ct_char_t			*expr,			/* input:  registration expression	*/
	ct_char_t			*raexpr,		/* input:  registration rearm expr. */
	mc_event_cb_6_t		*event_cb,		/* input:  event notification c.b.	*/
	void				*event_cb_arg	/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_select_bp_2(				/*		using Attribute Selection	*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_reg_rsp_t	 **response,		/* output: response					*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_event_cb_2_t	  *event_cb,		/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_select_ap_2(				/*		using Attribute Selection	*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_reg_rsp_t	 **response,		/* output: response					*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_event_cb_2_t	  *event_cb,		/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_select_bc_2(				/*		using Attribute Selection	*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_reg_cb_t		  *reg_cb,			/* input:  registration response cb */
	void			  *reg_cb_arg,		/* input:  callback argument		*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_event_cb_2_t	  *event_cb,		/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_select_ac_2(				/*		using Attribute Selection	*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_reg_cb_t		  *reg_cb,			/* input:  registration response cb */
	void			  *reg_cb_arg,		/* input:  callback argument		*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_event_cb_2_t	  *event_cb,		/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_handle_bp_2(				/*		using Resource Handle		*/
	mc_sess_hndl_t		 sess_hndl,		/* input:  session handle			*/
	mc_reg_rsp_t	   **response,		/* output: response					*/
	mc_reg_opts_t		 options,		/* input:  registration options		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t			 attr_count,	/* input:  count of attrs to return	*/
	ct_char_t			*expr,			/* input:  registration expression	*/
	ct_char_t			*raexpr,		/* input:  registration rearm expr. */
	mc_event_cb_2_t		*event_cb,		/* input:  event notification c.b.	*/
	void				*event_cb_arg	/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_handle_ap_2(				/*		using Resource Handle		*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_reg_rsp_t	   **response,		/* output: response					*/
	mc_reg_opts_t		 options,		/* input:  registration options		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t			 attr_count,	/* input:  count of attrs to return	*/
	ct_char_t			*expr,			/* input:  registration expression	*/
	ct_char_t			*raexpr,		/* input:  registration rearm expr. */
	mc_event_cb_2_t		*event_cb,		/* input:  event notification c.b.	*/
	void				*event_cb_arg	/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_handle_bc_2(				/*		using Resource Handle		*/
	mc_sess_hndl_t		 sess_hndl,		/* input:  session handle			*/
	mc_reg_cb_t			*reg_cb,		/* input:  registration response cb */
	void				*reg_cb_arg,	/* input:  callback argument		*/
	mc_reg_opts_t		 options,		/* input:  registration options		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t			 attr_count,	/* input:  count of attrs to return	*/
	ct_char_t			*expr,			/* input:  registration expression	*/
	ct_char_t			*raexpr,		/* input:  registration rearm expr. */
	mc_event_cb_2_t		*event_cb,		/* input:  event notification c.b.	*/
	void				*event_cb_arg	/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_handle_ac_2(				/*		using Resource Handle		*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_reg_cb_t			*reg_cb,		/* input:  registration response cb */
	void				*reg_cb_arg,	/* input:  callback argument		*/
	mc_reg_opts_t		 options,		/* input:  registration options		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t			 attr_count,	/* input:  count of attrs to return	*/
	ct_char_t			*expr,			/* input:  registration expression	*/
	ct_char_t			*raexpr,		/* input:  registration rearm expr. */
	mc_event_cb_2_t		*event_cb,		/* input:  event notification c.b.	*/
	void				*event_cb_arg	/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_select_bp_1(				/*		using Attribute Selection	*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_reg_rsp_t	 **response,		/* output: response					*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_event_cb_1_t	  *event_cb,		/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_select_ap_1(				/*		using Attribute Selection	*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_reg_rsp_t	 **response,		/* output: response					*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_event_cb_1_t	  *event_cb,		/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_select_bc_1(				/*		using Attribute Selection	*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_reg_cb_t		  *reg_cb,			/* input:  registration response cb */
	void			  *reg_cb_arg,		/* input:  callback argument		*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_event_cb_1_t	  *event_cb,		/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_select_ac_1(				/*		using Attribute Selection	*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_reg_cb_t		  *reg_cb,			/* input:  registration response cb */
	void			  *reg_cb_arg,		/* input:  callback argument		*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_event_cb_1_t	  *event_cb,		/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_handle_bp_1(				/*		using Resource Handle		*/
	mc_sess_hndl_t		 sess_hndl,		/* input:  session handle			*/
	mc_reg_rsp_t	   **response,		/* output: response					*/
	mc_reg_opts_t		 options,		/* input:  registration options		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t			 attr_count,	/* input:  count of attrs to return	*/
	ct_char_t			*expr,			/* input:  registration expression	*/
	ct_char_t			*raexpr,		/* input:  registration rearm expr. */
	mc_event_cb_1_t		*event_cb,		/* input:  event notification c.b.	*/
	void				*event_cb_arg	/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_handle_ap_1(				/*		using Resource Handle		*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_reg_rsp_t	   **response,		/* output: response					*/
	mc_reg_opts_t		 options,		/* input:  registration options		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t			 attr_count,	/* input:  count of attrs to return	*/
	ct_char_t			*expr,			/* input:  registration expression	*/
	ct_char_t			*raexpr,		/* input:  registration rearm expr. */
	mc_event_cb_1_t		*event_cb,		/* input:  event notification c.b.	*/
	void				*event_cb_arg	/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_handle_bc_1(				/*		using Resource Handle		*/
	mc_sess_hndl_t		 sess_hndl,		/* input:  session handle			*/
	mc_reg_cb_t			*reg_cb,		/* input:  registration response cb */
	void				*reg_cb_arg,	/* input:  callback argument		*/
	mc_reg_opts_t		 options,		/* input:  registration options		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t			 attr_count,	/* input:  count of attrs to return	*/
	ct_char_t			*expr,			/* input:  registration expression	*/
	ct_char_t			*raexpr,		/* input:  registration rearm expr. */
	mc_event_cb_1_t		*event_cb,		/* input:  event notification c.b.	*/
	void				*event_cb_arg	/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Register Event ...				*/
mc_reg_event_handle_ac_1(				/*		using Resource Handle		*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_reg_cb_t			*reg_cb,		/* input:  registration response cb */
	void				*reg_cb_arg,	/* input:  callback argument		*/
	mc_reg_opts_t		 options,		/* input:  registration options		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t			 attr_count,	/* input:  count of attrs to return	*/
	ct_char_t			*expr,			/* input:  registration expression	*/
	ct_char_t			*raexpr,		/* input:  registration rearm expr. */
	mc_event_cb_1_t		*event_cb,		/* input:  event notification c.b.	*/
	void				*event_cb_arg	/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_reg_class_event_bp_6(				/* Register Class Event				*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_reg_rsp_t	 **response,		/* output: response					*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_class_event_cb_6_t *event_cb,	/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_reg_class_event_ap_6(				/* Register Class Event				*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_reg_rsp_t	 **response,		/* output: response					*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_class_event_cb_6_t *event_cb,	/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_reg_class_event_bc_6(				/* Register Class Event				*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_reg_cb_t		  *reg_cb,			/* input:  registration response cb */
	void			  *reg_cb_arg,		/* input:  callback argument		*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_class_event_cb_6_t *event_cb,	/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_reg_class_event_ac_6(				/* Register Class Event				*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_reg_cb_t		  *reg_cb,			/* input:  registration response cb */
	void			  *reg_cb_arg,		/* input:  callback argument		*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_class_event_cb_6_t *event_cb,	/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_reg_class_event_bp_3(				/* Register Class Event				*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_reg_rsp_t	 **response,		/* output: response					*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_class_event_cb_3_t *event_cb,	/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_reg_class_event_ap_3(				/* Register Class Event				*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_reg_rsp_t	 **response,		/* output: response					*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_class_event_cb_3_t *event_cb,	/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_reg_class_event_bc_3(				/* Register Class Event				*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_reg_cb_t		  *reg_cb,			/* input:  registration response cb */
	void			  *reg_cb_arg,		/* input:  callback argument		*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_class_event_cb_3_t *event_cb,	/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_reg_class_event_ac_3(				/* Register Class Event				*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_reg_cb_t		  *reg_cb,			/* input:  registration response cb */
	void			  *reg_cb_arg,		/* input:  callback argument		*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_class_event_cb_3_t *event_cb,	/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_reg_class_event_bp_1(				/* Register Class Event				*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_reg_rsp_t	 **response,		/* output: response					*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_class_event_cb_1_t *event_cb,	/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_reg_class_event_ap_1(				/* Register Class Event				*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_reg_rsp_t	 **response,		/* output: response					*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_class_event_cb_1_t *event_cb,	/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_reg_class_event_bc_1(				/* Register Class Event				*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_reg_cb_t		  *reg_cb,			/* input:  registration response cb */
	void			  *reg_cb_arg,		/* input:  callback argument		*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_class_event_cb_1_t *event_cb,	/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_reg_class_event_ac_1(				/* Register Class Event				*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_reg_cb_t		  *reg_cb,			/* input:  registration response cb */
	void			  *reg_cb_arg,		/* input:  callback argument		*/
	mc_reg_opts_t	   options,			/* input:  registration options		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count,		/* input:  count of attrs to return	*/
	ct_char_t		  *expr,			/* input:  registration expression	*/
	ct_char_t		  *raexpr,			/* input:  registration rearm expr. */
	mc_class_event_cb_1_t *event_cb,	/* input:  event notification c.b.	*/
	void			  *event_cb_arg		/* input:  callback argument		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_unreg_event_bp_1(					/* Unregister Event					*/
	mc_sess_hndl_t		 sess_hndl,		/* input:  session handle			*/
	mc_unreg_rsp_t	   **response,		/* output: response					*/
	mc_registration_id_t reg_id			/* input:  registration identifier	*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_unreg_event_ap_1(					/* Unregister Event					*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_unreg_rsp_t	   **response,		/* output: response					*/
	mc_registration_id_t reg_id			/* input:  registration identifier	*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_unreg_event_bc_1(					/* Unregister Event					*/
	mc_sess_hndl_t		 sess_hndl,		/* input:  session handle			*/
	mc_unreg_cb_t		*unreg_cb,		/* input:  unregistration callback	*/
	void				*unreg_cb_arg,	/* input:  callback argument		*/
	mc_registration_id_t reg_id			/* input:  registration identifier	*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_unreg_event_ac_1(					/* Unregister Event					*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_unreg_cb_t		*unreg_cb,		/* input:  unregistration callback	*/
	void				*unreg_cb_arg,	/* input:  callback argument		*/
	mc_registration_id_t reg_id			/* input:  registration identifier	*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_query_event_bp_2(					/* Query Current Event State		*/
	mc_sess_hndl_t		   sess_hndl,	/* input:  session handle			*/
	mc_query_event_rsp_t **response,	/* output: response					*/
	mc_registration_id_t   reg_id		/* input:  registration identifier	*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_query_event_ap_2(					/* Query Current Event State		*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl,	/* input:  command group handle		*/
	mc_query_event_rsp_t **response,	/* output: response					*/
	mc_registration_id_t   reg_id		/* input:  registration identifier	*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_query_event_bc_2(					/* Query Current Event State		*/
	mc_sess_hndl_t		 sess_hndl,		/* input:  session handle			*/
	mc_query_event_cb_t	*qevent_cb,		/* input:  query event callback		*/
	void				*qevent_cb_arg,	/* input:  callback argument		*/
	mc_registration_id_t reg_id			/* input:  registration identifier	*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_query_event_ac_2(					/* Query Current Event State		*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_query_event_cb_t	*qevent_cb,		/* input:  query event callback		*/
	void				*qevent_cb_arg,	/* input:  callback argument		*/
	mc_registration_id_t reg_id			/* input:  registration identifier	*/
);										/* return: 0 or error number		*/


/*--------------------------------------------------------------------------*/
/*	Resource Monitoring and Control (RMC) -									*/
/*	  Function Prototypes for Configuration Command Interfaces				*/
/*--------------------------------------------------------------------------*/

extern ct_int32_t						  /* Enumerate Resources ...		*/
mc_enumerate_resources_bp_1(			  /*	 using Attribute Selection	*/
	mc_sess_hndl_t		 sess_hndl,		  /* input:  session handle			*/
	mc_enumerate_rsp_t **rsp_array,		  /* output: array of responses		*/
	ct_uint32_t			*array_cnt,		  /* output: count of responses		*/
	ct_char_t			*rsrc_class_name, /* input:  resource class name	*/
	ct_char_t			*select_attrs	  /* input:  select string			*/
);

extern ct_int32_t						  /* Enumerate Resources ...		*/
mc_enumerate_resources_ap_1(			  /*	 using Attribute Selection	*/
	mc_cmdgrp_hndl_t     cmdgrp_hndl,	  /* input:  command group handle	*/
	mc_enumerate_rsp_t **rsp_array,		  /* output: array of responses		*/
	ct_uint32_t			*array_cnt,		  /* output: count of responses		*/
	ct_char_t			*rsrc_class_name, /* input:  resource class name	*/
	ct_char_t			*select_attrs	  /* input:  select string			*/
);

extern ct_int32_t						  /* Enumerate Resources ...		*/
mc_enumerate_resources_bc_1(			  /*	 using Attribute Selection	*/
	mc_sess_hndl_t		sess_hndl,		  /* input:  session handle			*/
	mc_enumerate_cb_t  *enumerate_cb,	  /* input:  enumerate response cb	*/
	void			   *enumerate_cb_arg, /* input:  callback argument		*/
	ct_char_t		   *rsrc_class_name,  /* input:  resource class name	*/
	ct_char_t		   *select_attrs	  /* input:  select string			*/
);

extern ct_int32_t						  /* Enumerate Resources ...		*/
mc_enumerate_resources_ac_1(			  /*	 using Attribute Selection	*/
	mc_cmdgrp_hndl_t    cmdgrp_hndl,	  /* input:  command group handle	*/
	mc_enumerate_cb_t  *enumerate_cb,	  /* input:  enumerate response cb	*/
	void			   *enumerate_cb_arg, /* input:  callback argument		*/
	ct_char_t		   *rsrc_class_name,  /* input:  resource class name	*/
	ct_char_t		   *select_attrs	  /* input:  select string			*/
);

extern ct_int32_t						  /* Enumerate Permitted Resources 	*/
mc_enumerate_permitted_rsrcs_bp_4(		  /*  ... using Attribute Selection	*/
	mc_sess_hndl_t		 sess_hndl,		  /* input:  session handle			*/
	mc_enumerate_rsp_t **rsp_array,		  /* output: array of responses		*/
	ct_uint32_t			*array_cnt,		  /* output: count of responses		*/
	ct_char_t			*rsrc_class_name, /* input:  resource class name	*/
	ct_char_t			*select_attrs,	  /* input:  select string			*/
	ct_uint32_t			perms			  /* input:  required permissions	*/
);

extern ct_int32_t						  /* Enumerate Permitted Resources 	*/
mc_enumerate_permitted_rsrcs_ap_4(		  /*  ... using Attribute Selection	*/
	mc_cmdgrp_hndl_t     cmdgrp_hndl,	  /* input:  command group handle	*/
	mc_enumerate_rsp_t **rsp_array,		  /* output: array of responses		*/
	ct_uint32_t			*array_cnt,		  /* output: count of responses		*/
	ct_char_t			*rsrc_class_name, /* input:  resource class name	*/
	ct_char_t			*select_attrs,	  /* input:  select string			*/
	ct_uint32_t			perms			  /* input:  required permissions	*/
);

extern ct_int32_t						  /* Enumerate Permitted Resources 	*/
mc_enumerate_permitted_rsrcs_bc_4(		  /*  ... using Attribute Selection	*/
	mc_sess_hndl_t		sess_hndl,		  /* input:  session handle			*/
	mc_enumerate_cb_t  *enumerate_cb,	  /* input:  enumerate response cb	*/
	void			   *enumerate_cb_arg, /* input:  callback argument		*/
	ct_char_t			*rsrc_class_name, /* input:  resource class name	*/
	ct_char_t			*select_attrs,	  /* input:  select string			*/
	ct_uint32_t			perms			  /* input:  required permissions	*/
);

extern ct_int32_t						  /* Enumerate Permitted Resources 	*/
mc_enumerate_permitted_rsrcs_ac_4(		  /*  ... using Attribute Selection	*/
	mc_cmdgrp_hndl_t    cmdgrp_hndl,	  /* input:  command group handle	*/
	mc_enumerate_cb_t  *enumerate_cb,	  /* input:  enumerate response cb	*/
	void			   *enumerate_cb_arg, /* input:  callback argument		*/
	ct_char_t			*rsrc_class_name, /* input:  resource class name	*/
	ct_char_t			*select_attrs,	  /* input:  select string			*/
	ct_uint32_t			perms			  /* input:  required permissions	*/
);

extern ct_int32_t						/* Query Resource Persistent Attrs. */
mc_query_p_select_bp_1(					/*	... using Attribute Selection	*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_query_rsp_t	 **rsp_array,		/* output: array of responses		*/
	ct_uint32_t		  *array_cnt,		/* output: count of responses		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Persistent Attrs. */
mc_query_p_select_ap_1(					/*	... using Attribute Selection	*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_query_rsp_t	 **rsp_array,		/* output: array of responses		*/
	ct_uint32_t		  *array_cnt,		/* output: count of responses		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Persistent Attrs. */
mc_query_p_select_bc_1(					/*	... using Attribute Selection	*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_query_cb_t	  *query_cb,		/* input:  query response callback	*/
	void			  *query_cb_arg,	/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Persistent Attrs. */
mc_query_p_select_ac_1(					/*	... using Attribute Selection	*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_query_cb_t	  *query_cb,		/* input:  query response callback	*/
	void			  *query_cb_arg,	/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Dynamic Attrs.	*/
mc_query_d_select_bp_1(					/*	... using Attribute Selection	*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_query_rsp_t	 **rsp_array,		/* output: array of responses		*/
	ct_uint32_t		  *array_cnt,		/* output: count of responses		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Dynamic Attrs.	*/
mc_query_d_select_ap_1(					/*	... using Attribute Selection	*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_query_rsp_t	 **rsp_array,		/* output: array of responses		*/
	ct_uint32_t		  *array_cnt,		/* output: count of responses		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Dynamic Attrs.	*/
mc_query_d_select_bc_1(					/*	... using Attribute Selection	*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_query_cb_t	  *query_cb,		/* input:  query response callback	*/
	void			  *query_cb_arg,	/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Dynamic Attrs.	*/
mc_query_d_select_ac_1(					/*	... using Attribute Selection	*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_query_cb_t	  *query_cb,		/* input:  query response callback	*/
	void			  *query_cb_arg,	/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Persistent Attrs. */
mc_query_p_handle_bp_1(					/*	... using Resource Handle		*/
	mc_sess_hndl_t		 sess_hndl,		/* input:  session handle			*/
	mc_query_rsp_t	   **response,		/* output: response					*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		     attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Persistent Attrs. */
mc_query_p_handle_ap_1(					/*	... using Resource Handle		*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_query_rsp_t	   **response,		/* output: response					*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		     attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Persistent Attrs. */
mc_query_p_handle_bc_1(					/*	... using Resource Handle		*/
	mc_sess_hndl_t		 sess_hndl,		/* input:  session handle			*/
	mc_query_cb_t		*query_cb,		/* input:  query response callback	*/
	void				*query_cb_arg,	/* input:  callback argument		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		     attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Persistent Attrs. */
mc_query_p_handle_ac_1(					/*	... using Resource Handle		*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_query_cb_t		*query_cb,		/* input:  query response callback	*/
	void				*query_cb_arg,	/* input:  callback argument		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		     attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Dynamic Attrs.	*/
mc_query_d_handle_bp_1(					/*	... using Resource Handle		*/
	mc_sess_hndl_t		 sess_hndl,		/* input:  session handle			*/
	mc_query_rsp_t	   **response,		/* output: response					*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		     attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Dynamic Attrs.	*/
mc_query_d_handle_ap_1(					/*	... using Resource Handle		*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_query_rsp_t	   **response,		/* output: response					*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		     attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Dynamic Attrs.	*/
mc_query_d_handle_bc_1(					/*	... using Resource Handle		*/
	mc_sess_hndl_t		 sess_hndl,		/* input:  session handle			*/
	mc_query_cb_t		*query_cb,		/* input:  query response callback	*/
	void				*query_cb_arg,	/* input:  callback argument		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		     attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Dynamic Attrs.	*/
mc_query_d_handle_ac_1(					/*	... using Resource Handle		*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_query_cb_t		*query_cb,		/* input:  query response callback	*/
	void				*query_cb_arg,	/* input:  callback argument		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t		   **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		     attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Class				*/
mc_class_query_p_bp_3(					/*	... Persistent Attributes		*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_class_query_rsp_3_t **rsp_array, /* output: array of responses		*/
	ct_uint32_t		  *array_cnt,	  	/* output: count of responses		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Class				*/
mc_class_query_p_ap_3(					/*	... Persistent Attributes		*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_class_query_rsp_3_t **rsp_array, /* output: array of responses		*/
	ct_uint32_t		  *array_cnt,	  	/* output: count of responses		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Class				*/
mc_class_query_p_bc_3(					/*	... Persistent Attributes		*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_class_query_cb_3_t *query_cb,	/* input:  query response callback	*/
	void			  *query_cb_arg,	/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Class				*/
mc_class_query_p_ac_3(					/*	... Persistent Attributes		*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_class_query_cb_3_t *query_cb,	/* input:  query response callback	*/
	void			  *query_cb_arg,	/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Class				*/
mc_class_query_p_bp_1(					/*	... Persistent Attributes		*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_class_query_rsp_1_t **response,	/* output: response					*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Class				*/
mc_class_query_p_ap_1(					/*	... Persistent Attributes		*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_class_query_rsp_1_t **response,	/* output: response					*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Class				*/
mc_class_query_p_bc_1(					/*	... Persistent Attributes		*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_class_query_cb_1_t *query_cb,	/* input:  query response callback	*/
	void			  *query_cb_arg,	/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Class				*/
mc_class_query_p_ac_1(					/*	... Persistent Attributes		*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_class_query_cb_1_t *query_cb,	/* input:  query response callback	*/
	void			  *query_cb_arg,	/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Class				*/
mc_class_query_d_bp_3(					/*	... Dynamic Attributes			*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_class_query_rsp_3_t **rsp_array, /* output: array of responses		*/
	ct_uint32_t		  *array_cnt,	  	/* output: count of responses		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Class				*/
mc_class_query_d_ap_3(					/*	... Dynamic Attributes			*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_class_query_rsp_3_t **rsp_array, /* output: array of responses		*/
	ct_uint32_t		  *array_cnt,	  	/* output: count of responses		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Class				*/
mc_class_query_d_bc_3(					/*	... Dynamic Attributes			*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_class_query_cb_3_t *query_cb,	/* input:  query response callback	*/
	void			  *query_cb_arg,	/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Class				*/
mc_class_query_d_ac_3(					/*	... Dynamic Attributes			*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_class_query_cb_3_t *query_cb,	/* input:  query response callback	*/
	void			  *query_cb_arg,	/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Class				*/
mc_class_query_d_bp_1(					/*	... Dynamic Attributes			*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_class_query_rsp_1_t **response,	/* output: response					*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Class				*/
mc_class_query_d_ap_1(					/*	... Dynamic Attributes			*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_class_query_rsp_1_t **response,	/* output: response					*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Class				*/
mc_class_query_d_bc_1(					/*	... Dynamic Attributes			*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_class_query_cb_1_t *query_cb,	/* input:  query response callback	*/
	void			  *query_cb_arg,	/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Query Resource Class				*/
mc_class_query_d_ac_1(					/*	... Dynamic Attributes			*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_class_query_cb_1_t *query_cb,	/* input:  query response callback	*/
	void			  *query_cb_arg,	/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name,	/* input:  resource class name		*/
	ct_char_t		 **return_attrs,	/* input:  attributes to return		*/
	ct_uint32_t		   attr_count		/* input:  count of attrs to return	*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_qdef_resource_class_bp_1(			   	/* Query Resource Class Defn.	*/
	mc_sess_hndl_t		    sess_hndl,		/* input:  session handle		*/
	mc_qdef_rsrc_class_rsp_t **rsp_array,  	/* output: array of responses	*/
	ct_uint32_t			   *array_cnt,		/* output: count of responses	*/
	mc_qdef_opts_t			options,	   	/* input:  query defn. options	*/
	ct_char_t			   *rsrc_class_name	/* input:  resource class name	*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_resource_class_ap_1(			    /* Query Resource Class Defn.	*/
	mc_cmdgrp_hndl_t		cmdgrp_hndl,	/* input:  command group handle	*/
	mc_qdef_rsrc_class_rsp_t **rsp_array,  	/* output: array of responses	*/
	ct_uint32_t			   *array_cnt,  	/* output: count of responses	*/
	mc_qdef_opts_t			options,	   	/* input:  query defn. options	*/
	ct_char_t			   *rsrc_class_name	/* input:  resource class name	*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_resource_class_bc_1(				/* Query Resource Class Defn.	*/
	mc_sess_hndl_t			sess_hndl,  	/* input:  session handle		*/
	mc_qdef_rsrc_class_cb_t *qdef_cb,		/* input:  query defn callback	*/
	void				   *qdef_cb_arg,	/* input:  callback argument	*/
	mc_qdef_opts_t			options,	   	/* input:  query defn. options	*/
	ct_char_t			   *rsrc_class_name	/* input:  resource class name	*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_resource_class_ac_1(				/* Query Resource Class Defn.	*/
	mc_cmdgrp_hndl_t		cmdgrp_hndl,	/* input:  command group handle	*/
	mc_qdef_rsrc_class_cb_t *qdef_cb,		/* input:  query defn callback	*/
	void				   *qdef_cb_arg,	/* input:  callback argument	*/
	mc_qdef_opts_t			options,	   	/* input:  query defn. options	*/
	ct_char_t			   *rsrc_class_name	/* input:  resource class name	*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_p_attribute_bp_1(					/* Query Persistent Attr. Defn.	*/
	mc_sess_hndl_t		   sess_hndl,  		/* input:  session handle		*/
	mc_qdef_pattr_rsp_t	 **rsp_array,  		/* output: array of responses	*/
	ct_uint32_t			  *array_cnt,  		/* output: count of responses	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	ct_uint32_t			   qry_class_attrs,	/* input:  query class attrs.	*/
	ct_char_t			 **attr_names,		/* input:  attribute names		*/
	ct_uint32_t			   attr_count		/* input:  attribute count		*/
);										   	/* return: 0 or error number	*/
	
extern ct_int32_t
mc_qdef_p_attribute_ap_1(					/* Query Persistent Attr. Defn.	*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl, 	/* input:  command group handle	*/
	mc_qdef_pattr_rsp_t	 **rsp_array,  		/* output: array of responses	*/
	ct_uint32_t			  *array_cnt,  		/* output: count of responses	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	ct_uint32_t			   qry_class_attrs,	/* input:  query class attrs.	*/
	ct_char_t			 **attr_names,		/* input:  attribute names		*/
	ct_uint32_t			   attr_count		/* input:  attribute count		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_p_attribute_bc_1(					/* Query Persistent Attr. Defn.	*/
	mc_sess_hndl_t		   sess_hndl,  		/* input:  session handle		*/
	mc_qdef_pattr_cb_t	  *qdef_cb,			/* input:  query defn callback	*/
	void				  *qdef_cb_arg,		/* input:  callback argument	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	ct_uint32_t			   qry_class_attrs,	/* input:  query class attrs.	*/
	ct_char_t			 **attr_names,		/* input:  attribute names		*/
	ct_uint32_t			   attr_count		/* input:  attribute count		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_p_attribute_ac_1(					/* Query Persistent Attr. Defn.	*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl, 	/* input:  command group handle	*/
	mc_qdef_pattr_cb_t	  *qdef_cb,			/* input:  query defn callback	*/
	void				  *qdef_cb_arg,		/* input:  callback argument	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	ct_uint32_t			   qry_class_attrs,	/* input:  query class attrs.	*/
	ct_char_t			 **attr_names,		/* input:  attribute names		*/
	ct_uint32_t			   attr_count		/* input:  attribute count		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_d_attribute_bp_6(					/* Query Dynamic Attr. Defn.	*/
	mc_sess_hndl_t			sess_hndl,  	/* input:  session handle		*/
	mc_qdef_dattr_rsp_6_t **rsp_array, 		/* output: array of responses	*/
	ct_uint32_t			   *array_cnt,  	/* output: count of responses	*/
	mc_qdef_opts_t			options,	   	/* input:  query defn. options	*/
	ct_char_t			   *class_name,		/* input:  resource class name	*/
	ct_uint32_t				qy_class_attrs,	/* input:  query class attrs.	*/
	ct_char_t			  **attr_names,		/* input:  attribute names		*/
	ct_uint32_t				attr_count		/* input:  attribute count		*/
);										   	/* return: 0 or error number	*/
	
extern ct_int32_t
mc_qdef_d_attribute_ap_6(					/* Query Dynamic Attr. Defn.	*/
	mc_cmdgrp_hndl_t		cmdgrp_hndl, 	/* input:  command group handle	*/
	mc_qdef_dattr_rsp_6_t **rsp_array, 		/* output: array of responses	*/
	ct_uint32_t			   *array_cnt,  	/* output: count of responses	*/
	mc_qdef_opts_t			options,	   	/* input:  query defn. options	*/
	ct_char_t			   *class_name,		/* input:  resource class name	*/
	ct_uint32_t				qy_class_attrs,	/* input:  query class attrs.	*/
	ct_char_t			  **attr_names,		/* input:  attribute names		*/
	ct_uint32_t				attr_count		/* input:  attribute count		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_d_attribute_bc_6(					/* Query Dynamic Attr. Defn.	*/
	mc_sess_hndl_t		   sess_hndl,  		/* input:  session handle		*/
	mc_qdef_dattr_cb_6_t  *qdef_cb,			/* input:  query defn callback	*/
	void				  *qdef_cb_arg,		/* input:  callback argument	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	ct_uint32_t			   qry_class_attrs,	/* input:  query class attrs.	*/
	ct_char_t			 **attr_names,		/* input:  attribute names		*/
	ct_uint32_t			   attr_count		/* input:  attribute count		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_d_attribute_ac_6(					/* Query Dynamic Attr. Defn.	*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl, 	/* input:  command group handle	*/
	mc_qdef_dattr_cb_6_t  *qdef_cb,			/* input:  query defn callback	*/
	void				  *qdef_cb_arg,		/* input:  callback argument	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	ct_uint32_t			   qry_class_attrs,	/* input:  query class attrs.	*/
	ct_char_t			 **attr_names,		/* input:  attribute names		*/
	ct_uint32_t			   attr_count		/* input:  attribute count		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_d_attribute_bp_1(					/* Query Dynamic Attr. Defn.	*/
	mc_sess_hndl_t			sess_hndl,  	/* input:  session handle		*/
	mc_qdef_dattr_rsp_1_t **rsp_array, 		/* output: array of responses	*/
	ct_uint32_t			   *array_cnt,  	/* output: count of responses	*/
	mc_qdef_opts_t			options,	   	/* input:  query defn. options	*/
	ct_char_t			   *class_name,		/* input:  resource class name	*/
	ct_uint32_t				qy_class_attrs,	/* input:  query class attrs.	*/
	ct_char_t			  **attr_names,		/* input:  attribute names		*/
	ct_uint32_t				attr_count		/* input:  attribute count		*/
);										   	/* return: 0 or error number	*/
	
extern ct_int32_t
mc_qdef_d_attribute_ap_1(					/* Query Dynamic Attr. Defn.	*/
	mc_cmdgrp_hndl_t		cmdgrp_hndl, 	/* input:  command group handle	*/
	mc_qdef_dattr_rsp_1_t **rsp_array, 		/* output: array of responses	*/
	ct_uint32_t			   *array_cnt,  	/* output: count of responses	*/
	mc_qdef_opts_t			options,	   	/* input:  query defn. options	*/
	ct_char_t			   *class_name,		/* input:  resource class name	*/
	ct_uint32_t				qy_class_attrs,	/* input:  query class attrs.	*/
	ct_char_t			  **attr_names,		/* input:  attribute names		*/
	ct_uint32_t				attr_count		/* input:  attribute count		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_d_attribute_bc_1(					/* Query Dynamic Attr. Defn.	*/
	mc_sess_hndl_t		   sess_hndl,  		/* input:  session handle		*/
	mc_qdef_dattr_cb_1_t  *qdef_cb,			/* input:  query defn callback	*/
	void				  *qdef_cb_arg,		/* input:  callback argument	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	ct_uint32_t			   qry_class_attrs,	/* input:  query class attrs.	*/
	ct_char_t			 **attr_names,		/* input:  attribute names		*/
	ct_uint32_t			   attr_count		/* input:  attribute count		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_d_attribute_ac_1(					/* Query Dynamic Attr. Defn.	*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl, 	/* input:  command group handle	*/
	mc_qdef_dattr_cb_1_t  *qdef_cb,			/* input:  query defn callback	*/
	void				  *qdef_cb_arg,		/* input:  callback argument	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	ct_uint32_t			   qry_class_attrs,	/* input:  query class attrs.	*/
	ct_char_t			 **attr_names,		/* input:  attribute names		*/
	ct_uint32_t			   attr_count		/* input:  attribute count		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_sbs_bp_1(							/* Query SBS Definition			*/
	mc_sess_hndl_t		   sess_hndl,  		/* input:  session handle		*/
	mc_qdef_sbs_rsp_t	 **rsp_array,  		/* output: array of responses	*/
	ct_uint32_t			  *array_cnt,  		/* output: count of responses	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	ct_uint32_t			   qry_class_SBS,	/* input:  query class SBS		*/
	ct_char_t			 **attr_names,		/* input:  attribute names		*/
	ct_uint32_t			   attr_count		/* input:  attribute count		*/
);										   	/* return: 0 or error number	*/
	
extern ct_int32_t
mc_qdef_sbs_ap_1(							/* Query SBS Definition			*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl, 	/* input:  command group handle	*/
	mc_qdef_sbs_rsp_t	 **rsp_array,  		/* output: array of responses	*/
	ct_uint32_t			  *array_cnt,  		/* output: count of responses	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	ct_uint32_t			   qry_class_SBS,	/* input:  query class SBS		*/
	ct_char_t			 **attr_names,		/* input:  attribute names		*/
	ct_uint32_t			   attr_count		/* input:  attribute count		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_sbs_bc_1(							/* Query SBS Definition			*/
	mc_sess_hndl_t		   sess_hndl,  		/* input:  session handle		*/
	mc_qdef_sbs_cb_t	  *qdef_cb,			/* input:  query defn callback	*/
	void				  *qdef_cb_arg,		/* input:  callback argument	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	ct_uint32_t			   qry_class_SBS,	/* input:  query class SBS		*/
	ct_char_t			 **attr_names,		/* input:  attribute names		*/
	ct_uint32_t			   attr_count		/* input:  attribute count		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_sbs_ac_1(							/* Query SBS Definition			*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl, 	/* input:  command group handle	*/
	mc_qdef_sbs_cb_t	  *qdef_cb,			/* input:  query defn callback	*/
	void				  *qdef_cb_arg,		/* input:  callback argument	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	ct_uint32_t			   qry_class_SBS,	/* input:  query class SBS		*/
	ct_char_t			 **attr_names,		/* input:  attribute names		*/
	ct_uint32_t			   attr_count		/* input:  attribute count		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_sd_bp_1(							/* Query Structured Data Defn.	*/
	mc_sess_hndl_t		   sess_hndl,  		/* input:  session handle		*/
	mc_qdef_sd_rsp_t	 **rsp_array,  		/* output: array of responses	*/
	ct_uint32_t			  *array_cnt,  		/* output: count of responses	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	mc_sd_usage_t		   sd_use,			/* input:  structured data use	*/
	ct_char_t			 **names,			/* input:  attr./action names	*/
	ct_uint32_t			   count			/* input:  attr./action count	*/
);

extern ct_int32_t
mc_qdef_sd_ap_1(							/* Query Structured Data Defn.	*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl, 	/* input:  command group handle	*/
	mc_qdef_sd_rsp_t	 **rsp_array,  		/* output: array of responses	*/
	ct_uint32_t			  *array_cnt,  		/* output: count of responses	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	mc_sd_usage_t		   sd_use,			/* input:  structured data use	*/
	ct_char_t			 **names,			/* input:  attr./action names	*/
	ct_uint32_t			   count			/* input:  attr./action count	*/
);

extern ct_int32_t
mc_qdef_sd_bc_1(							/* Query Structured Data Defn.	*/
	mc_sess_hndl_t		   sess_hndl,  		/* input:  session handle		*/
	mc_qdef_sd_cb_t		  *qdef_cb,			/* input:  query defn callback	*/
	void				  *qdef_cb_arg,		/* input:  callback argument	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	mc_sd_usage_t		   sd_use,			/* input:  structured data use	*/
	ct_char_t			 **names,			/* input:  attr./action names	*/
	ct_uint32_t			   count			/* input:  attr./action count	*/
);

extern ct_int32_t
mc_qdef_sd_ac_1(							/* Query Structured Data Defn.	*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl, 	/* input:  command group handle	*/
	mc_qdef_sd_cb_t		  *qdef_cb,			/* input:  query defn callback	*/
	void				  *qdef_cb_arg,		/* input:  callback argument	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	mc_sd_usage_t		   sd_use,			/* input:  structured data use	*/
	ct_char_t			 **names,			/* input:  attr./action names	*/
	ct_uint32_t			   count			/* input:  attr./action count	*/
);

extern ct_int32_t
mc_qdef_valid_values_bp_1(					/* Query Valid Values Definition*/
	mc_sess_hndl_t		   sess_hndl,		/* input:  session handle		*/
	mc_qdef_valid_vals_rsp_t **rsp_array,  	/* output: array of responses	*/
	ct_uint32_t			  *array_cnt,  		/* output: count of responses	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	mc_vv_usage_t		   vv_use,			/* input:  valid values usage	*/
	ct_char_t			 **names,			/* input:  attribute, action,   */
											/*           or error names		*/
	ct_uint32_t			   count			/* input:  count of names		*/
);										   	/* return: 0 or error number	*/
	
extern ct_int32_t
mc_qdef_valid_values_ap_1(					/* Query Valid Values Definition*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl, 	/* input:  command group handle	*/
	mc_qdef_valid_vals_rsp_t **rsp_array,  	/* output: array of responses	*/
	ct_uint32_t			  *array_cnt,  		/* output: count of responses	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	mc_vv_usage_t		   vv_use,			/* input:  valid values usage	*/
	ct_char_t			 **names,			/* input:  attribute, action,   */
											/*           or error names		*/
	ct_uint32_t			   count			/* input:  count of names		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_valid_values_bc_1(					/* Query Valid Values Definition*/
	mc_sess_hndl_t		   sess_hndl,		/* input:  session handle		*/
	mc_qdef_valid_vals_cb_t *qdef_cb,		/* input:  query defn callback	*/
	void				  *qdef_cb_arg,		/* input:  callback argument	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	mc_vv_usage_t		   vv_use,			/* input:  valid values usage	*/
	ct_char_t			 **names,			/* input:  attribute, action,   */
											/*           or error names		*/
	ct_uint32_t			   count			/* input:  count of names		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_valid_values_ac_1(					/* Query Valid Values Definition*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl,		/* input:  command group handle	*/
	mc_qdef_valid_vals_cb_t *qdef_cb,		/* input:  query defn callback	*/
	void				  *qdef_cb_arg,		/* input:  callback argument	*/
	mc_qdef_opts_t		   options,	   		/* input:  query defn. options	*/
	ct_char_t			  *rsrc_class_name,	/* input:  resource class name	*/
	mc_vv_usage_t		   vv_use,			/* input:  valid values usage	*/
	ct_char_t			 **names,			/* input:  attribute, action,   */
											/*           or error names		*/
	ct_uint32_t			   count			/* input:  count of names		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_actions_bp_1(						/* Query Action Definition		*/
	mc_sess_hndl_t		  sess_hndl,	  	/* input:  session handle		*/
	mc_qdef_actions_rsp_t **rsp_array,  	/* output: array of responses	*/
	ct_uint32_t			 *array_cnt,	  	/* output: count of responses	*/
	mc_qdef_opts_t		  options,		   	/* input:  query defn. options	*/
	ct_char_t			 *rsrc_class_name,	/* input:  resource class name	*/
	ct_uint32_t			  qry_class_actns,	/* input:  query class actions	*/
	ct_char_t			**names,			/* input:  action names		    */
	ct_uint32_t			  count				/* input:  count of names		*/
);										   	/* return: 0 or error number	*/
	
extern ct_int32_t
mc_qdef_actions_ap_1(						/* Query Action Definition		*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,		/* input:  command group handle	*/
	mc_qdef_actions_rsp_t **rsp_array,  	/* output: array of responses	*/
	ct_uint32_t			 *array_cnt,	  	/* output: count of responses	*/
	mc_qdef_opts_t		  options,		   	/* input:  query defn. options	*/
	ct_char_t			 *rsrc_class_name,	/* input:  resource class name	*/
	ct_uint32_t			  qry_class_actns,	/* input:  query class actions	*/
	ct_char_t			**names,			/* input:  action names		    */
	ct_uint32_t			  count				/* input:  count of names		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_actions_bc_1(						/* Query Action Definition		*/
	mc_sess_hndl_t		  sess_hndl,  		/* input:  session handle		*/
	mc_qdef_actions_cb_t *qdef_cb,			/* input:  query defn callback	*/
	void				 *qdef_cb_arg,		/* input:  callback argument	*/
	mc_qdef_opts_t		  options,	   		/* input:  query defn. options	*/
	ct_char_t			 *rsrc_class_name,	/* input:  resource class name	*/
	ct_uint32_t			  qry_class_actns,	/* input:  query class actions	*/
	ct_char_t			**names,			/* input:  action names		    */
	ct_uint32_t			  count				/* input:  count of names		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_actions_ac_1(						/* Query Action Definition		*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,		/* input:  command group handle	*/
	mc_qdef_actions_cb_t *qdef_cb,			/* input:  query defn callback	*/
	void				 *qdef_cb_arg,		/* input:  callback argument	*/
	mc_qdef_opts_t		  options,	   		/* input:  query defn. options	*/
	ct_char_t			 *rsrc_class_name,	/* input:  resource class name	*/
	ct_uint32_t			  qry_class_actns,	/* input:  query class actions	*/
	ct_char_t			**names,			/* input:  action names		    */
	ct_uint32_t			  count				/* input:  count of names		*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_err_inject_bp_1(					/* Query Error Injection Defn.	*/
	mc_sess_hndl_t			sess_hndl,  	/* input:  session handle		*/
	mc_qdef_err_inject_rsp_t **rsp_array,  	/* output: array of responses	*/
	ct_uint32_t			   *array_cnt,  	/* output: count of responses	*/
	mc_qdef_opts_t			options,	   	/* input:  query defn. options	*/
	ct_char_t			   *rsrc_class_name	/* input:  resource class name	*/
);										   	/* return: 0 or error number	*/
	
extern ct_int32_t
mc_qdef_err_inject_ap_1(					/* Query Error Injection Defn.	*/
	mc_cmdgrp_hndl_t		cmdgrp_hndl,	/* input:  command group handle	*/
	mc_qdef_err_inject_rsp_t **rsp_array,  	/* output: array of responses	*/
	ct_uint32_t			   *array_cnt,  	/* output: count of responses	*/
	mc_qdef_opts_t			options,	   	/* input:  query defn. options	*/
	ct_char_t			   *rsrc_class_name	/* input:  resource class name	*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_err_inject_bc_1(					/* Query Error Injection Defn.	*/
	mc_sess_hndl_t			sess_hndl,  	/* input:  session handle		*/
	mc_qdef_err_inject_cb_t *qdef_cb,		/* input:  query defn callback	*/
	void				   *qdef_cb_arg,	/* input:  callback argument	*/
	mc_qdef_opts_t			options,	   	/* input:  query defn. options	*/
	ct_char_t			   *rsrc_class_name	/* input:  resource class name	*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_err_inject_ac_1(					/* Query Error Injection Defn.	*/
	mc_cmdgrp_hndl_t		cmdgrp_hndl,	/* input:  command group handle	*/
	mc_qdef_err_inject_cb_t *qdef_cb,		/* input:  query defn callback	*/
	void				   *qdef_cb_arg,	/* input:  callback argument	*/
	mc_qdef_opts_t			options,	   	/* input:  query defn. options	*/
	ct_char_t			   *rsrc_class_name	/* input:  resource class name	*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_dependencies_bp_1(					/* Query Dependency Definition	*/
	mc_sess_hndl_t			sess_hndl,  	/* input:  session handle		*/
	mc_qdef_rsrc_deps_rsp_t	 **rsp_array,  	/* output: array of responses	*/
	ct_uint32_t			   *array_cnt,  	/* output: count of responses	*/
	ct_char_t			   *rsrc_class_name	/* input:  resource class name	*/
);										   	/* return: 0 or error number	*/
	
extern ct_int32_t
mc_qdef_dependencies_ap_1(					/* Query Dependency Definition	*/
	mc_cmdgrp_hndl_t		cmdgrp_hndl,	/* input:  command group handle	*/
	mc_qdef_rsrc_deps_rsp_t	 **rsp_array,  	/* output: array of responses	*/
	ct_uint32_t			   *array_cnt,  	/* output: count of responses	*/
	ct_char_t			   *rsrc_class_name	/* input:  resource class name	*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_dependencies_bc_1(					/* Query Dependency Definition	*/
	mc_sess_hndl_t			sess_hndl,  	/* input:  session handle		*/
	mc_qdef_rsrc_deps_cb_t *qdef_cb,		/* input:  query defn callback	*/
	void				   *qdef_cb_arg,	/* input:  callback argument	*/
	ct_char_t			   *rsrc_class_name	/* input:  resource class name	*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_qdef_dependencies_ac_1(					/* Query Dependency Definition	*/
	mc_cmdgrp_hndl_t		cmdgrp_hndl,	/* input:  command group handle	*/
	mc_qdef_rsrc_deps_cb_t *qdef_cb,		/* input:  query defn callback	*/
	void				   *qdef_cb_arg,	/* input:  callback argument	*/
	ct_char_t			   *rsrc_class_name	/* input:  resource class name	*/
);										   	/* return: 0 or error number	*/

extern ct_int32_t
mc_validate_rsrc_hndl_bp_1(				   /* Validate Resource Handles		*/
	mc_sess_hndl_t		   sess_hndl,	   /* input:  session handle		*/
	mc_rsrc_hndl_rsp_t	 **rsp_array,	   /* output: array of responses	*/
	ct_uint32_t			  *array_cnt,	   /* output: count of responses	*/
	ct_resource_handle_t  *rsrc_hndl,	   /* input:  resource handle array */
	ct_uint32_t			   rsrc_hndl_cnt   /* input:  resource handle count */
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_validate_rsrc_hndl_ap_1(				   /* Validate Resource Handles		*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl,	   /* input:  command group handle	*/
	mc_rsrc_hndl_rsp_t	 **rsp_array,	   /* output: array of responses	*/
	ct_uint32_t			  *array_cnt,	   /* output: count of responses	*/
	ct_resource_handle_t  *rsrc_hndl,	   /* input:  resource handle array */
	ct_uint32_t			   rsrc_hndl_cnt   /* input:  resource handle count	*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_validate_rsrc_hndl_bc_1(				   /* Validate Resource Handles		*/
	mc_sess_hndl_t		   sess_hndl,	   /* input:  session handle		*/
	mc_val_rsrc_hndl_cb_t *val_rsrc_hndl_cb,	  /*  response callback		*/
	void				  *val_rsrc_hndl_cb_arg,  /*  callback argument		*/
	ct_resource_handle_t  *rsrc_hndl,	   /* input:  resource handle array */
	ct_uint32_t			   rsrc_hndl_cnt   /* input:  resource handle count	*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_validate_rsrc_hndl_ac_1(				   /* Validate Resource Handles		*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl,	   /* input:  command group handle	*/
	mc_val_rsrc_hndl_cb_t *val_rsrc_hndl_cb,	  /*  response callback		*/
	void				  *val_rsrc_hndl_cb_arg,  /*  callback argument		*/
	ct_resource_handle_t  *rsrc_hndl,	   /* input:  resource handle array */
	ct_uint32_t			   rsrc_hndl_cnt   /* input:  resource handle count	*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_define_resource_bp_1(				   /* Define a Resource				*/
	mc_sess_hndl_t		  sess_hndl,	   /* input:  session handle		*/
	mc_define_rsrc_rsp_t **response,	   /* output: response				*/
	ct_char_t			 *rsrc_class_name, /* input:  resource class name	*/
	mc_attribute_t		 *attrs,		   /* input:  resource attributes	*/
	ct_uint32_t			  attr_count,	   /* input:  count of attributes	*/
	ct_structured_data_t *data			   /* input:  data					*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_define_resource_ap_1(				   /* Define a Resource				*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,	   /* input:  command group handle	*/
	mc_define_rsrc_rsp_t **response,	   /* output: response				*/
	ct_char_t			 *rsrc_class_name, /* input:  resource class name	*/
	mc_attribute_t		 *attrs,		   /* input:  resource attributes	*/
	ct_uint32_t			  attr_count,	   /* input:  count of attributes	*/
	ct_structured_data_t *data			   /* input:  data					*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_define_resource_bc_1(				   /* Define a Resource				*/
	mc_sess_hndl_t		  sess_hndl,	   /* input:  session handle		*/
	mc_def_rsrc_cb_t	 *def_rsrc_cb,	   /* input:  response callback		*/
	void				 *def_rsrc_cb_arg, /* input:  callback argument		*/
	ct_char_t			 *rsrc_class_name, /* input:  resource class name	*/
	mc_attribute_t		 *attrs,		   /* input:  resource attributes	*/
	ct_uint32_t			  attr_count,	   /* input:  count of attributes	*/
	ct_structured_data_t *data			   /* input:  data					*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_define_resource_ac_1(				   /* Define a Resource				*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,	   /* input:  command group handle	*/
	mc_def_rsrc_cb_t	 *def_rsrc_cb,	   /* input:  response callback		*/
	void				 *def_rsrc_cb_arg, /* input:  callback argument		*/
	ct_char_t			 *rsrc_class_name, /* input:  resource class name	*/
	mc_attribute_t		 *attrs,		   /* input:  resource attributes	*/
	ct_uint32_t			  attr_count,	   /* input:  count of attributes	*/
	ct_structured_data_t *data			   /* input:  data					*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_undefine_resource_bp_1(				   /* Undefine a Resource			*/
	mc_sess_hndl_t		     sess_hndl,	   /* input:  session handle		*/
	mc_undefine_rsrc_rsp_t **response,	   /* output: response				*/
	ct_resource_handle_t	 rsrc_hndl,	   /* input:  resource handle		*/
	ct_structured_data_t	*data		   /* input:  data					*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_undefine_resource_ap_1(				   /* Undefine a Resource			*/
	mc_cmdgrp_hndl_t		 cmdgrp_hndl,  /* input:  command group handle	*/
	mc_undefine_rsrc_rsp_t **response,	   /* output: response				*/
	ct_resource_handle_t	 rsrc_hndl,	   /* input:  resource handle	    */
	ct_structured_data_t	*data		   /* input:  data					*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_undefine_resource_bc_1(				   /* Undefine a Resource			*/
	mc_sess_hndl_t		   sess_hndl,	   /* input:  session handle		*/
	mc_undef_rsrc_cb_t	  *undef_rsrc_cb,  /* input:  response callback		*/
	void				  *undef_rsrc_cb_arg,
	ct_resource_handle_t   rsrc_hndl,	   /* input:  resource handle		*/
	ct_structured_data_t  *data			   /* input:  data					*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_undefine_resource_ac_1(				   /* Undefine a Resource			*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl,	   /* input:  command group handle	*/
	mc_undef_rsrc_cb_t	  *undef_rsrc_cb,  /* input:  response callback		*/
	void				  *undef_rsrc_cb_arg,
	ct_resource_handle_t   rsrc_hndl,	   /* input:  resource handle		*/
	ct_structured_data_t  *data			   /* input:  data					*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_refresh_config_bp_1(					   /* Refresh Resource Configuration*/
	mc_sess_hndl_t		   sess_hndl,	   /* input:  session handle		*/
	mc_class_name_rsp_t	 **rsp_array,	   /* output: array of responses	*/
	ct_uint32_t			  *array_cnt,	   /* output: count of responses	*/
	ct_char_t			  *rsrc_class_name /* input:  resource class name	*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_refresh_config_ap_1(					   /* Refresh Resource Configuration*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl,	   /* input:  command group handle	*/
	mc_class_name_rsp_t	 **rsp_array,	   /* output: array of responses	*/
	ct_uint32_t			  *array_cnt,	   /* output: count of responses	*/
	ct_char_t			  *rsrc_class_name /* input:  resource class name	*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_refresh_config_bc_1(					   /* Refresh Resource Configuration*/
	mc_sess_hndl_t		   sess_hndl,	   /* input:  session handle		*/
	mc_refresh_cfg_cb_t	  *refresh_cfg_cb, /* input:  response callback		*/
	void				  *refresh_cfg_cb_arg,
	ct_char_t			  *rsrc_class_name /* input:  resource class name	*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_refresh_config_ac_1(					   /* Refresh Resource Configuration*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl,	   /* input:  command group handle	*/
	mc_refresh_cfg_cb_t	  *refresh_cfg_cb, /* input:  response callback		*/
	void				  *refresh_cfg_cb_arg,
	ct_char_t			  *rsrc_class_name /* input:  resource class name	*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_do_integrity_check_bp_1(				   /* Do Integrity Check			*/
	mc_sess_hndl_t			   sess_hndl,  /* input:  session handle		*/
	mc_integrity_chk_rsp_t	 **rsp_array,  /* output: array of responses	*/
	ct_uint32_t				  *array_cnt,  /* output: count of responses	*/
	mc_integrity_check_opts_t  options,	   /* input:  options				*/
	rmc_integrity_check_type_t check_type, /* input:  integrity check type	*/
	ct_char_t				  *class_name  /* input:  resource class name	*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_do_integrity_check_ap_1(				   /* Do Integrity Check			*/
	mc_cmdgrp_hndl_t		  cmdgrp_hndl, /* input:  command group handle	*/
	mc_integrity_chk_rsp_t	 **rsp_array,  /* output: array of responses	*/
	ct_uint32_t				  *array_cnt,  /* output: count of responses	*/
	mc_integrity_check_opts_t  options,	   /* input:  options				*/
	rmc_integrity_check_type_t check_type, /* input:  integrity check type	*/
	ct_char_t				  *class_name  /* input:  resource class name	*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_do_integrity_check_bc_1(				   /* Do Integrity Check			*/
	mc_sess_hndl_t			   sess_hndl,  /* input:  session handle		*/
	mc_integrity_chk_cb_t	  *integrity_chk_cb,
	void					  *integrity_chk_cb_arg,
	mc_integrity_check_opts_t  options,	   /* input:  options				*/
	rmc_integrity_check_type_t check_type, /* input:  integrity check type	*/
	ct_char_t				  *class_name  /* input:  resource class name	*/
);										   /* return: 0 or error number		*/

extern ct_int32_t
mc_do_integrity_check_ac_1(				   /* Do Integrity Check			*/
	mc_cmdgrp_hndl_t		  cmdgrp_hndl, /* input:  command group handle	*/
	mc_integrity_chk_cb_t	  *integrity_chk_cb,
	void					  *integrity_chk_cb_arg,
	mc_integrity_check_opts_t  options,	   /* input:  options				*/
	rmc_integrity_check_type_t check_type, /* input:  integrity check type	*/
	ct_char_t				  *class_name  /* input:  resource class name	*/
);										   /* return: 0 or error number		*/

extern ct_int32_t						/* Set Resource Attributes ...		*/
mc_set_select_bp_1(						/*		using Attribute Selection	*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_set_rsp_t	 **rsp_array,		/* output: array of responses		*/
	ct_uint32_t		  *array_cnt,		/* output: count of responses		*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	mc_attribute_t	  *attrs,			/* input:  resource attributes		*/
	ct_uint32_t		   attr_count		/* input:  count of attributes		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Set Resource Attributes ...		*/
mc_set_select_ap_1(						/*		using Attribute Selection	*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_set_rsp_t	 **rsp_array,		/* output: array of responses		*/
	ct_uint32_t		  *array_cnt,		/* output: count of responses		*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	mc_attribute_t	  *attrs,			/* input:  resource attributes		*/
	ct_uint32_t		   attr_count		/* input:  count of attributes		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Set Resource Attributes ...		*/
mc_set_select_bc_1(						/*		using Attribute Selection	*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_set_cb_t		  *set_cb,			/* input:  response callback		*/
	void			  *set_cb_arg,		/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	mc_attribute_t	  *attrs,			/* input:  resource attributes		*/
	ct_uint32_t		   attr_count		/* input:  count of attributes		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Set Resource Attributes ...		*/
mc_set_select_ac_1(						/*		using Attribute Selection	*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_set_cb_t		  *set_cb,			/* input:  response callback		*/
	void			  *set_cb_arg,		/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	ct_char_t		  *select_attrs,	/* input:  select string			*/
	mc_attribute_t	  *attrs,			/* input:  resource attributes		*/
	ct_uint32_t		   attr_count		/* input:  count of attributes		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Set Resource Attributes ...		*/
mc_set_handle_bp_1(						/*		using Resource Handle		*/	
	mc_sess_hndl_t		 sess_hndl,		/* input:  session handle			*/
	mc_set_rsp_t	   **response,		/* output: response					*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	mc_attribute_t		*attrs,			/* input:  resource attributes		*/
	ct_uint32_t			 attr_count		/* input:  count of attributes		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Set Resource Attributes ...		*/
mc_set_handle_ap_1(						/*		using Resource Handle		*/	
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_set_rsp_t	   **response,		/* output: response					*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	mc_attribute_t		*attrs,			/* input:  resource attributes		*/
	ct_uint32_t			 attr_count		/* input:  count of attributes		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Set Resource Attributes ...		*/
mc_set_handle_bc_1(						/*		using Resource Handle		*/	
	mc_sess_hndl_t		 sess_hndl,		/* input:  session handle			*/
	mc_set_cb_t			*set_cb,		/* input:  response callback		*/
	void				*set_cb_arg,	/* input:  callback argument		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	mc_attribute_t		*attrs,			/* input:  resource attributes		*/
	ct_uint32_t			 attr_count		/* input:  count of attributes		*/
);										/* return: 0 or error number		*/

extern ct_int32_t						/* Set Resource Attributes ...		*/
mc_set_handle_ac_1(						/*		using Resource Handle		*/	
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_set_cb_t			*set_cb,		/* input:  response callback		*/
	void				*set_cb_arg,	/* input:  callback argument		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	mc_attribute_t		*attrs,			/* input:  resource attributes		*/
	ct_uint32_t			 attr_count		/* input:  count of attributes		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_class_set_bp_3(						/* Set Resource Class Attributes	*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_class_set_rsp_3_t **rsp_array,	 /* output: array of responses		*/
	ct_uint32_t		  *array_cnt,	  	/* output: count of responses		*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	mc_attribute_t	  *attrs,			/* input:  resource attributes		*/
	ct_uint32_t		   attr_count		/* input:  count of attributes		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_class_set_ap_3(						/* Set Resource Class Attributes	*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_class_set_rsp_3_t **rsp_array,	 /* output: array of responses		*/
	ct_uint32_t		  *array_cnt,	  	/* output: count of responses		*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	mc_attribute_t	  *attrs,			/* input:  resource attributes		*/
	ct_uint32_t		   attr_count		/* input:  count of attributes		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_class_set_bc_3(						/* Set Resource Class Attributes	*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_class_set_cb_3_t *set_cb,		/* input:  response callback		*/
	void			  *set_cb_arg,		/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	mc_attribute_t	  *attrs,			/* input:  resource attributes		*/
	ct_uint32_t		   attr_count		/* input:  count of attributes		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_class_set_ac_3(						/* Set Resource Class Attributes	*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_class_set_cb_3_t *set_cb,		/* input:  response callback		*/
	void			  *set_cb_arg,		/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	ct_char_t		 **pd_names,		/* input:  peer domain names		*/
	ct_uint32_t		   name_count,		/* input:  count of domain names	*/
	mc_attribute_t	  *attrs,			/* input:  resource attributes		*/
	ct_uint32_t		   attr_count		/* input:  count of attributes		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_class_set_bp_1(						/* Set Resource Class Attributes	*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_class_set_rsp_1_t **response,	/* output: response					*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	mc_attribute_t	  *attrs,			/* input:  resource attributes		*/
	ct_uint32_t		   attr_count		/* input:  count of attributes		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_class_set_ap_1(						/* Set Resource Class Attributes	*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_class_set_rsp_1_t **response,	/* output: response					*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	mc_attribute_t	  *attrs,			/* input:  resource attributes		*/
	ct_uint32_t		   attr_count		/* input:  count of attributes		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_class_set_bc_1(						/* Set Resource Class Attributes	*/
	mc_sess_hndl_t	   sess_hndl,		/* input:  session handle			*/
	mc_class_set_cb_1_t *set_cb,		/* input:  response callback		*/
	void			  *set_cb_arg,		/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	mc_attribute_t	  *attrs,			/* input:  resource attributes		*/
	ct_uint32_t		   attr_count		/* input:  count of attributes		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_class_set_ac_1(						/* Set Resource Class Attributes	*/
	mc_cmdgrp_hndl_t   cmdgrp_hndl,		/* input:  command group handle		*/
	mc_class_set_cb_1_t *set_cb,		/* input:  response callback		*/
	void			  *set_cb_arg,		/* input:  callback argument		*/
	ct_char_t		  *rsrc_class_name, /* input:  resource class name		*/
	mc_attribute_t	  *attrs,			/* input:  resource attributes		*/
	ct_uint32_t		   attr_count		/* input:  count of attributes		*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_invoke_action_bp_1(					/* Invoke Action					*/
	mc_sess_hndl_t		   sess_hndl,	/* input:  session handle			*/
	mc_action_rsp_t	     **rsp_array,	/* output: array of responses		*/
	ct_uint32_t			  *array_cnt,	/* output: count of responses		*/
	ct_resource_handle_t   rsrc_hndl,	/* input:  resource handle			*/
	ct_char_t			  *action_name,	/* input:  action name				*/
	ct_structured_data_t  *data			/* input:  data						*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_invoke_action_ap_1(					/* Invoke Action					*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl,	/* input:  command group handle		*/
	mc_action_rsp_t	     **rsp_array,	/* output: array of responses		*/
	ct_uint32_t			  *array_cnt,	/* output: count of responses		*/
	ct_resource_handle_t   rsrc_hndl,	/* input:  resource handle			*/
	ct_char_t			  *action_name,	/* input:  action name				*/
	ct_structured_data_t  *data			/* input:  data						*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_invoke_action_bc_1(					/* Invoke Action					*/
	mc_sess_hndl_t		 sess_hndl,		/* input:  session handle			*/
	mc_action_cb_t		*action_cb,		/* input:  response callback		*/
	void				*action_cb_arg, /* input:  callback argument		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t			*action_name,	/* input:  action name				*/
	ct_structured_data_t  *data			/* input:  data						*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_invoke_action_ac_1(					/* Invoke Action					*/
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,	/* input:  command group handle		*/
	mc_action_cb_t		*action_cb,		/* input:  response callback		*/
	void				*action_cb_arg, /* input:  callback argument		*/
	ct_resource_handle_t rsrc_hndl,		/* input:  resource handle			*/
	ct_char_t			*action_name,	/* input:  action name				*/
	ct_structured_data_t  *data			/* input:  data						*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_invoke_class_action_bp_3(			      /* Invoke Action on a Class	  */
	mc_sess_hndl_t			  sess_hndl,      /* input:  session handle		  */
	mc_class_action_rsp_3_t **rsp_array,      /* output: array of responses	  */
	ct_uint32_t				 *array_cnt,      /* output: count of responses	  */
	ct_char_t		    	 *class_name,	  /* input:  resource class name  */
	ct_char_t		    	 *action_name,	  /* input:  action name		  */
	ct_char_t		    	**names,		  /* input:  node or domain names */
	ct_uint32_t		    	  name_count,	  /* input:  node or domain count */
	mc_list_usage_t			  list_usage,	  /* input:  name list usage	  */
	ct_structured_data_t	 *data			  /* input:  data				  */
);											  /* return: 0 or error number	  */

extern ct_int32_t
mc_invoke_class_action_ap_3(				  /* Invoke Action on a Class	  */
	mc_cmdgrp_hndl_t		  cmdgrp_hndl,	  /* input:  command group handle */
	mc_class_action_rsp_3_t	**rsp_array,	  /* output: array of responses	  */
	ct_uint32_t		    	 *array_cnt,	  /* output: count of responses	  */
	ct_char_t		    	 *class_name,	  /* input:  resource class name  */
	ct_char_t		    	 *action_name,	  /* input:  action name		  */
	ct_char_t		    	**names,		  /* input:  node or domain names */
	ct_uint32_t		    	  name_count,	  /* input:  node or domain count */
	mc_list_usage_t			  list_usage,	  /* input:  name list usage	  */
	ct_structured_data_t	 *data			  /* input:  data				  */
);											  /* return: 0 or error number	  */

extern ct_int32_t
mc_invoke_class_action_bc_3(				  /* Invoke Action on a Class	  */
	mc_sess_hndl_t			  sess_hndl,	  /* input:  session handle		  */
	mc_class_action_cb_3_t	 *action_cb,	  /* input:  response callback	  */
	void					 *action_cb_arg,  /* input:  callback argument	  */
	ct_char_t				 *class_name,	  /* input:  resource class name  */
	ct_char_t				 *action_name,	  /* input:  action name		  */
	ct_char_t				**names,		  /* input:  node or domain names */
	ct_uint32_t		    	  name_count,	  /* input:  node or domain count */
	mc_list_usage_t			  list_usage,	  /* input:  name list usage	  */
	ct_structured_data_t	 *data			  /* input:  data				  */
);											  /* return: 0 or error number	  */

extern ct_int32_t
mc_invoke_class_action_ac_3(				  /* Invoke Action on a Class	  */
	mc_cmdgrp_hndl_t		  cmdgrp_hndl,	  /* input:  command group handle */
	mc_class_action_cb_3_t	 *action_cb,	  /* input:  response callback	  */
	void					 *action_cb_arg,  /* input:  callback argument	  */
	ct_char_t				 *class_name,	  /* input:  resource class name  */
	ct_char_t				 *action_name,	  /* input:  action name		  */
	ct_char_t				**names,		  /* input:  node or domain names */
	ct_uint32_t		    	  name_count,	  /* input:  node or domain count */
	mc_list_usage_t			  list_usage,	  /* input:  name list usage	  */
	ct_structured_data_t	 *data			  /* input:  data				  */
);											  /* return: 0 or error number	  */

extern ct_int32_t
mc_invoke_class_action_bp_2(			      /* Invoke Action on a Class	  */
	mc_sess_hndl_t			  sess_hndl,      /* input:  session handle		  */
	mc_class_action_rsp_2_t **rsp_array,      /* output: array of responses	  */
	ct_uint32_t				 *array_cnt,      /* output: count of responses	  */
	ct_char_t		    	 *class_name,	  /* input:  resource class name  */
	ct_char_t		    	 *action_name,	  /* input:  action name		  */
	ct_char_t		    	**node_names,	  /* input:  node names			  */
	ct_uint32_t		    	  name_count,	  /* input:  node name count	  */
	ct_structured_data_t	 *data			  /* input:  data				  */
);											  /* return: 0 or error number	  */

extern ct_int32_t
mc_invoke_class_action_ap_2(				  /* Invoke Action on a Class	  */
	mc_cmdgrp_hndl_t		  cmdgrp_hndl,	  /* input:  command group handle */
	mc_class_action_rsp_2_t	**rsp_array,	  /* output: array of responses	  */
	ct_uint32_t		    	 *array_cnt,	  /* output: count of responses	  */
	ct_char_t		    	 *class_name,	  /* input:  resource class name  */
	ct_char_t		    	 *action_name,	  /* input:  action name		  */
	ct_char_t		    	**node_names,	  /* input:  node names			  */
	ct_uint32_t		    	  name_count,	  /* input:  node name count	  */
	ct_structured_data_t	 *data			  /* input:  data				  */
);											  /* return: 0 or error number	  */

extern ct_int32_t
mc_invoke_class_action_bc_2(				  /* Invoke Action on a Class	  */
	mc_sess_hndl_t			  sess_hndl,	  /* input:  session handle		  */
	mc_class_action_cb_2_t	 *action_cb,	  /* input:  response callback	  */
	void					 *action_cb_arg,  /* input:  callback argument	  */
	ct_char_t				 *class_name,	  /* input:  resource class name  */
	ct_char_t				 *action_name,	  /* input:  action name		  */
	ct_char_t				**node_names,	  /* input:  node names			  */
	ct_uint32_t				  name_count,	  /* input:  node name count	  */
	ct_structured_data_t	 *data			  /* input:  data				  */
);											  /* return: 0 or error number	  */

extern ct_int32_t
mc_invoke_class_action_ac_2(				  /* Invoke Action on a Class	  */
	mc_cmdgrp_hndl_t		  cmdgrp_hndl,	  /* input:  command group handle */
	mc_class_action_cb_2_t	 *action_cb,	  /* input:  response callback	  */
	void					 *action_cb_arg,  /* input:  callback argument	  */
	ct_char_t				 *class_name,	  /* input:  resource class name  */
	ct_char_t				 *action_name,	  /* input:  action name		  */
	ct_char_t				**node_names,	  /* input:  node names			  */
	ct_uint32_t				  name_count,	  /* input:  node name count	  */
	ct_structured_data_t	 *data			  /* input:  data				  */
);											  /* return: 0 or error number	  */

extern ct_int32_t
mc_invoke_class_action_bp_1(				  /* Invoke Action on a Class 	  */
	mc_sess_hndl_t			  sess_hndl,	  /* input:  session handle		  */
	mc_class_action_rsp_1_t	**rsp_array,	  /* output: array of responses	  */
	ct_uint32_t				 *array_cnt,	  /* output: count of responses	  */
	ct_char_t				 *class_name,	  /* input:  resource class name  */
	ct_char_t				 *action_name,	  /* input:  action name		  */
	ct_structured_data_t	 *data			  /* input:  data				  */
);										      /* return: 0 or error number	  */

extern ct_int32_t
mc_invoke_class_action_ap_1(				  /* Invoke Action on a Class	  */
	mc_cmdgrp_hndl_t		  cmdgrp_hndl,	  /* input:  command group handle */
	mc_class_action_rsp_1_t **rsp_array,	  /* output: array of responses	  */
	ct_uint32_t		    	 *array_cnt,	  /* output: count of responses	  */
	ct_char_t		    	 *class_name,	  /* input:  resource class name  */
	ct_char_t		    	 *action_name,	  /* input:  action name		  */
	ct_structured_data_t	 *data			  /* input:  data				  */
);											  /* return: 0 or error number	  */

extern ct_int32_t
mc_invoke_class_action_bc_1(				  /* Invoke Action on a Class	  */
	mc_sess_hndl_t			  sess_hndl,	  /* input:  session handle		  */
	mc_class_action_cb_1_t	 *action_cb,	  /* input:  response callback	  */
	void				     *action_cb_arg,  /* input:  callback argument	  */
	ct_char_t			     *class_name,	  /* input:  resource class name  */
	ct_char_t			     *action_name,	  /* input:  action name		  */
	ct_structured_data_t	 *data			  /* input:  data				  */
);											  /* return: 0 or error number	  */

extern ct_int32_t
mc_invoke_class_action_ac_1(				  /* Invoke Action on a Class	  */
	mc_cmdgrp_hndl_t		  cmdgrp_hndl,	  /* input:  command group handle */
	mc_class_action_cb_1_t	 *action_cb,	  /* input:  response callback	  */
	void				     *action_cb_arg,  /* input:  callback argument	  */
	ct_char_t			     *class_name,	  /* input:  resource class name  */
	ct_char_t			     *action_name,	  /* input:  action name		  */
	ct_structured_data_t	 *data			  /* input:  data				  */
);											  /* return: 0 or error number	  */

extern ct_int32_t
mc_enum_constraints_bp_1(				/* Enumerate Constraints			*/
	mc_sess_hndl_t		  sess_hndl,	/* input:  session handle			*/
	mc_constraint_rsp_t	**response,		/* output: response					*/
	ct_resource_handle_t  rsrc_hndl		/* input:  resource handle			*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_enum_constraints_ap_1(				/* Enumerate Constraints			*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,	/* input:  command group handle		*/
	mc_constraint_rsp_t	**response,		/* output: response					*/
	ct_resource_handle_t  rsrc_hndl		/* input:  resource handle			*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_enum_constraints_bc_1(				/* Enumerate Constraints			*/
	mc_sess_hndl_t			  sess_hndl,
	mc_enum_constraints_cb_t *enum_constraints_cb,
	void					 *enum_constraints_cb_arg,
	ct_resource_handle_t	  rsrc_hndl
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_enum_constraints_ac_1(				/* Enumerate Constraints			*/
	mc_cmdgrp_hndl_t		  cmdgrp_hndl,
	mc_enum_constraints_cb_t *enum_constraints_cb,
	void					 *enum_constraints_cb_arg,
	ct_resource_handle_t	  rsrc_hndl
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_define_constraint_bp_1(				/* Define Constraint				*/
	mc_sess_hndl_t		  sess_hndl,	/* input:  session handle			*/
	mc_rsrc_hndl_rsp_t	**response,		/* output: response					*/
	ct_resource_handle_t  rsrc_hndl,	/* input:  resource handle			*/
	rmc_constraint_t	 *constraint	/* input:  constraint				*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_define_constraint_ap_1(				/* Define Constraint				*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,	/* input:  command group handle		*/
	mc_rsrc_hndl_rsp_t	**response,		/* output: response					*/
	ct_resource_handle_t  rsrc_hndl,	/* input:  resource handle			*/
	rmc_constraint_t	 *constraint	/* input:  constraint				*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_define_constraint_bc_1(				/* Define Constraint				*/
	mc_sess_hndl_t				 sess_hndl,
	mc_define_constraint_cb_t	*constraint_cb,
	void						*constraint_cb_arg,
	ct_resource_handle_t		 rsrc_hndl,
	rmc_constraint_t			*constraint
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_define_constraint_ac_1(				/* Define Constraint				*/
	mc_cmdgrp_hndl_t			 cmdgrp_hndl,
	mc_define_constraint_cb_t	*constraint_cb,
	void						*constraint_cb_arg,
	ct_resource_handle_t		 rsrc_hndl,
	rmc_constraint_t			*constraint
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_undefine_constraint_bp_1(			/* Undefine Constraint				*/
	mc_sess_hndl_t		  sess_hndl,	/* input:  session handle			*/
	mc_rsrc_hndl_rsp_t	**response,		/* output: response					*/
	ct_resource_handle_t  rsrc_hndl,	/* input:  resource handle			*/
	ct_int32_t			  constraint_id	/* input:  constraint ID			*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_undefine_constraint_ap_1(			/* Undefine Constraint				*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,	/* input:  command group handle		*/
	mc_rsrc_hndl_rsp_t	**response,		/* output: response					*/
	ct_resource_handle_t  rsrc_hndl,	/* input:  resource handle			*/
	ct_int32_t			  constraint_id	/* input:  constraint ID			*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_undefine_constraint_bc_1(			/* Undefine Constraint				*/
	mc_sess_hndl_t				 sess_hndl,
	mc_undefine_constraint_cb_t	*constraint_cb,
	void						*constraint_cb_arg,
	ct_resource_handle_t		 rsrc_hndl,
	ct_int32_t					 constraint_id
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_undefine_constraint_ac_1(			/* Undefine Constraint				*/
	mc_cmdgrp_hndl_t			 cmdgrp_hndl,
	mc_undefine_constraint_cb_t	*constraint_cb,
	void						*constraint_cb_arg,
	ct_resource_handle_t		 rsrc_hndl,
	ct_int32_t					 constraint_id
);										/* return: 0 or error number		*/


/*--------------------------------------------------------------------------*/
/*	Resource Monitoring and Control (RMC) -									*/
/*	  Function Prototypes for Control Command Interfaces					*/
/*--------------------------------------------------------------------------*/

extern ct_int32_t
mc_online_bp_2(								/* Bring a Resource On-line		*/
	mc_sess_hndl_t			   sess_hndl,	/* input:  session handle		*/
	mc_rsrc_hndl_rsp_t		 **response,	/* output: response				*/
	ct_resource_handle_t	   rsrc_hndl,	/* input:  resource handle		*/
	ct_char_t				 **node_names,	/* input:  node names			*/
	ct_uint32_t				   name_count,	/* input:  node name count		*/
	ct_structured_data_t	  *data			/* input:  data					*/
);											/* return: 0 or error number	*/

extern ct_int32_t
mc_online_ap_2(								/* Bring a Resource On-line		*/
	mc_cmdgrp_hndl_t		   cmdgrp_hndl,	/* input:  command group handle	*/
	mc_rsrc_hndl_rsp_t		 **response,	/* output: response				*/
	ct_resource_handle_t	   rsrc_hndl,	/* input:  resource handle		*/
	ct_char_t				 **node_names,	/* input:  node names			*/
	ct_uint32_t				   name_count,	/* input:  node name count		*/
	ct_structured_data_t	  *data			/* input:  data					*/
);											/* return: 0 or error number	*/

extern ct_int32_t
mc_online_bc_2(								/* Bring a Resource On-line		*/
	mc_sess_hndl_t			   sess_hndl,	/* input:  session handle		*/
	mc_online_cb_t			  *online_cb,	/* input:  response callback	*/
	void					  *online_cb_arg,   /* input: callback argument	*/
	ct_resource_handle_t	   rsrc_hndl,	/* input:  resource handle		*/
	ct_char_t				 **node_names,	/* input:  node names			*/
	ct_uint32_t				   name_count,	/* input:  node name count		*/
	ct_structured_data_t	  *data			/* input:  data					*/
);											/* return: 0 or error number	*/

extern ct_int32_t
mc_online_ac_2(								/* Bring a Resource On-line		*/
	mc_cmdgrp_hndl_t		   cmdgrp_hndl,	/* input:  command group handle	*/
	mc_online_cb_t			  *online_cb,	/* input:  response callback	*/
	void					  *online_cb_arg,   /* input: callback argument	*/
	ct_resource_handle_t	   rsrc_hndl,	/* input:  resource handle		*/
	ct_char_t				 **node_names,	/* input:  node names			*/
	ct_uint32_t				   name_count,	/* input:  node name count		*/
	ct_structured_data_t	  *data			/* input:  data					*/
);											/* return: 0 or error number	*/

extern ct_int32_t
mc_online_bp_1(								/* Bring a Resource On-line		*/
	mc_sess_hndl_t			   sess_hndl,	/* input:  session handle		*/
	mc_rsrc_hndl_rsp_t		 **response,	/* output: response				*/
	ct_resource_handle_t	   rsrc_hndl,	/* input:  resource handle		*/
	ct_uint32_t				   node_number,	/* input:  node number			*/
	ct_structured_data_t	  *data			/* input:  data					*/
);											/* return: 0 or error number	*/

extern ct_int32_t
mc_online_ap_1(								/* Bring a Resource On-line		*/
	mc_cmdgrp_hndl_t		   cmdgrp_hndl,	/* input:  command group handle	*/
	mc_rsrc_hndl_rsp_t		 **response,	/* output: response				*/
	ct_resource_handle_t	   rsrc_hndl,	/* input:  resource handle		*/
	ct_uint32_t				   node_number,	/* input:  node number			*/
	ct_structured_data_t	  *data			/* input:  data					*/
);											/* return: 0 or error number	*/

extern ct_int32_t
mc_online_bc_1(								/* Bring a Resource On-line		*/
	mc_sess_hndl_t			   sess_hndl,	/* input:  session handle		*/
	mc_online_cb_t			  *online_cb,	/* input:  response callback	*/
	void					  *online_cb_arg,   /* input: callback argument	*/
	ct_resource_handle_t	   rsrc_hndl,	/* input:  resource handle		*/
	ct_uint32_t				   node_number,	/* input:  node number			*/
	ct_structured_data_t	  *data			/* input:  data					*/
);											/* return: 0 or error number	*/

extern ct_int32_t
mc_online_ac_1(								/* Bring a Resource On-line		*/
	mc_cmdgrp_hndl_t		   cmdgrp_hndl,	/* input:  command group handle	*/
	mc_online_cb_t			  *online_cb,	/* input:  response callback	*/
	void					  *online_cb_arg,   /* input: callback argument	*/
	ct_resource_handle_t	   rsrc_hndl,	/* input:  resource handle		*/
	ct_uint32_t				   node_number,	/* input:  node number			*/
	ct_structured_data_t	  *data			/* input:  data					*/
);											/* return: 0 or error number	*/

extern ct_int32_t
mc_offline_bp_2(						/* Take a Resource Off-line			*/
	mc_sess_hndl_t		  sess_hndl,	/* input:  session handle			*/
	mc_rsrc_hndl_rsp_t	**response,		/* output: response					*/
	mc_offline_opts_t	  options,		/* input:  options					*/
	ct_resource_handle_t  rsrc_hndl,	/* input:  resource handle			*/
	ct_structured_data_t *data			/* input:  data						*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_offline_ap_2(						/* Take a Resource Off-line			*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,	/* input:  command group handle		*/
	mc_rsrc_hndl_rsp_t	**response,		/* output: response					*/
	mc_offline_opts_t	  options,		/* input:  options					*/
	ct_resource_handle_t  rsrc_hndl,	/* input:  resource handle			*/
	ct_structured_data_t *data			/* input:  data						*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_offline_bc_2(						  /* Take a Resource Off-line		*/
	mc_sess_hndl_t		  sess_hndl,	  /* input:	 session handle			*/
	mc_offline_cb_t		 *offline_cb,	  /* input:	 response callback		*/
	void				 *offline_cb_arg, /* input:	 callback argument		*/
	mc_offline_opts_t	  options,		  /* input:  options				*/
	ct_resource_handle_t  rsrc_hndl,	  /* input:	 resource handle		*/
	ct_structured_data_t *data			  /* input:  data					*/
);										  /* return: 0 or error number		*/

extern ct_int32_t
mc_offline_ac_2(						  /* Take a Resource Off-line		*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,	  /* input:	 command group handle	*/
	mc_offline_cb_t		 *offline_cb,	  /* input:	 response callback		*/
	void				 *offline_cb_arg, /* input:	 callback argument		*/
	mc_offline_opts_t	  options,		  /* input:  options				*/
	ct_resource_handle_t  rsrc_hndl,	  /* input:	 resource handle		*/
	ct_structured_data_t *data			  /* input:  data					*/
);										  /* return: 0 or error number		*/

extern ct_int32_t
mc_offline_bp_1(						/* Take a Resource Off-line			*/
	mc_sess_hndl_t		  sess_hndl,	/* input:  session handle			*/
	mc_rsrc_hndl_rsp_t	**response,		/* output: response					*/
	ct_resource_handle_t  rsrc_hndl,	/* input:  resource handle			*/
	ct_structured_data_t *data			/* input:  data						*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_offline_ap_1(						/* Take a Resource Off-line			*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,	/* input:  command group handle		*/
	mc_rsrc_hndl_rsp_t	**response,		/* output: response					*/
	ct_resource_handle_t  rsrc_hndl,	/* input:  resource handle			*/
	ct_structured_data_t *data			/* input:  data						*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_offline_bc_1(						  /* Take a Resource Off-line		*/
	mc_sess_hndl_t		  sess_hndl,	  /* input:	 session handle			*/
	mc_offline_cb_t		 *offline_cb,	  /* input:	 response callback		*/
	void				 *offline_cb_arg, /* input:	 callback argument		*/
	ct_resource_handle_t  rsrc_hndl,	  /* input:	 resource handle		*/
	ct_structured_data_t *data			  /* input:  data					*/
);										  /* return: 0 or error number		*/

extern ct_int32_t
mc_offline_ac_1(						  /* Take a Resource Off-line		*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,	  /* input:	 command group handle	*/
	mc_offline_cb_t		 *offline_cb,	  /* input:	 response callback		*/
	void				 *offline_cb_arg, /* input:	 callback argument		*/
	ct_resource_handle_t  rsrc_hndl,	  /* input:	 resource handle		*/
	ct_structured_data_t *data			  /* input:  data					*/
);										  /* return: 0 or error number		*/

extern ct_int32_t
mc_reset_bp_2(							/* Force a Resource Off-line		*/
	mc_sess_hndl_t		  sess_hndl,	/* input:  session handle			*/
	mc_rsrc_hndl_rsp_t	**response,		/* output: response					*/
	ct_resource_handle_t  rsrc_hndl,	/* input:  resource handle			*/
	ct_structured_data_t *data			/* input:  data						*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_reset_ap_2(							/* Force a Resource Off-line		*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,	/* input:  command group handle		*/
	mc_rsrc_hndl_rsp_t	**response,		/* output: response					*/
	ct_resource_handle_t  rsrc_hndl,	/* input:  resource handle			*/
	ct_structured_data_t *data			/* input:  data						*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_reset_bc_2(							  /* Force a Resource Off-line		*/
	mc_sess_hndl_t		  sess_hndl,	  /* input:	 session handle			*/
	mc_reset_cb_t		 *reset_cb,		  /* input:	 response callback		*/
	void				 *reset_cb_arg,	  /* input:	 callback argument		*/
	ct_resource_handle_t  rsrc_hndl,	  /* input:	 resource handle		*/
	ct_structured_data_t *data			  /* input:  data					*/
);										  /* return: 0 or error number		*/

extern ct_int32_t
mc_reset_ac_2(							  /* Force a Resource Off-line		*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,	  /* input:	 command group handle	*/
	mc_reset_cb_t		 *reset_cb,		  /* input:	 response callback		*/
	void				 *reset_cb_arg,	  /* input:	 callback argument		*/
	ct_resource_handle_t  rsrc_hndl,	  /* input:	 resource handle		*/
	ct_structured_data_t *data			  /* input:  data					*/
);										  /* return: 0 or error number		*/

extern ct_int32_t
mc_reset_bp_1(							/* Force a Resource Off-line		*/
	mc_sess_hndl_t		  sess_hndl,	/* input:  session handle			*/
	mc_rsrc_hndl_rsp_t	**response,		/* output: response					*/
	ct_resource_handle_t  rsrc_hndl,	/* input:  resource handle			*/
	ct_structured_data_t *data			/* input:  data						*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_reset_ap_1(							/* Force a Resource Off-line		*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,	/* input:  command group handle		*/
	mc_rsrc_hndl_rsp_t	**response,		/* output: response					*/
	ct_resource_handle_t  rsrc_hndl,	/* input:  resource handle			*/
	ct_structured_data_t *data			/* input:  data						*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_reset_bc_1(							  /* Force a Resource Off-line		*/
	mc_sess_hndl_t		  sess_hndl,	  /* input:	 session handle			*/
	mc_reset_cb_t		 *reset_cb,		  /* input:	 response callback		*/
	void				 *reset_cb_arg,	  /* input:	 callback argument		*/
	ct_resource_handle_t  rsrc_hndl,	  /* input:	 resource handle		*/
	ct_structured_data_t *data			  /* input:  data					*/
);										  /* return: 0 or error number		*/

extern ct_int32_t
mc_reset_ac_1(							  /* Force a Resource Off-line		*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,	  /* input:	 command group handle	*/
	mc_reset_cb_t		 *reset_cb,		  /* input:	 response callback		*/
	void				 *reset_cb_arg,	  /* input:	 callback argument		*/
	ct_resource_handle_t  rsrc_hndl,	  /* input:	 resource handle		*/
	ct_structured_data_t *data			  /* input:  data					*/
);										  /* return: 0 or error number		*/

extern ct_int32_t
mc_constraint_advisory_bp_1(			/* Constraint Advisory				*/
	mc_sess_hndl_t						 sess_hndl,   /* i: session handle	*/
	mc_rsrc_hndl_rsp_t				   **response,	  /* o: response		*/
	ct_resource_handle_t				 rsrc_hndl,	  /* i: resource handle	*/
	rmc_constraint_alternate_resource_t	*constraints, /* i: constraints 	*/
	ct_uint32_t							 count		  /* i: # constraints  	*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_constraint_advisory_ap_1(			/* Constraint Advisory				*/
	mc_cmdgrp_hndl_t					 cmdgrp_hndl, /* i: cmdgrp. handle	*/
	mc_rsrc_hndl_rsp_t				   **response,	  /* o: response		*/
	ct_resource_handle_t				 rsrc_hndl,	  /* i: resource handle	*/
	rmc_constraint_alternate_resource_t	*constraints, /* i: constraints 	*/
	ct_uint32_t							 count		  /* i: # constraints  	*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_constraint_advisory_bc_1(			/* Constraint Advisory				*/
	mc_sess_hndl_t						 sess_hndl,   /* i: session handle	*/
	mc_advisory_cb_t					*advisory_cb, /* i: rsp. callback	*/
	void								*advisory_cb_arg,
	ct_resource_handle_t				 rsrc_hndl,	  /* i: resource handle	*/
	rmc_constraint_alternate_resource_t	*constraints, /* i: constraints 	*/
	ct_uint32_t							 count		  /* i: # constraints  	*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_constraint_advisory_ac_1(			/* Constraint Advisory				*/
	mc_cmdgrp_hndl_t					 cmdgrp_hndl, /* i: cmdgrp. handle	*/
	mc_advisory_cb_t					*advisory_cb, /* i: rsp. callback	*/
	void								*advisory_cb_arg,
	ct_resource_handle_t				 rsrc_hndl,	  /* i: resource handle	*/
	rmc_constraint_alternate_resource_t	*constraints, /* i: constraints 	*/
	ct_uint32_t							 count		  /* i: # constraints  	*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_get_control_log_bp_1(				/* Get Control Log					*/
	mc_sess_hndl_t		   sess_hndl,	/* input:  session handle			*/
	mc_control_log_rsp_t **response,	/* output: response					*/
	ct_resource_handle_t   rsrc_hndl	/* input:  resource handle			*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_get_control_log_ap_1(				/* Get Control Log					*/
	mc_cmdgrp_hndl_t	   cmdgrp_hndl,	/* input:  command group handle		*/
	mc_control_log_rsp_t **response,	/* output: response					*/
	ct_resource_handle_t   rsrc_hndl	/* input:  resource handle			*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_get_control_log_bc_1(				/* Get Control Log					*/
	mc_sess_hndl_t			 sess_hndl,
	mc_get_control_log_cb_t *get_control_log_cb,
	void					*get_control_log_cb_arg,
	ct_resource_handle_t	 rsrc_hndl
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_get_control_log_ac_1(				/* Get Control Log					*/
	mc_cmdgrp_hndl_t		 cmdgrp_hndl,
	mc_get_control_log_cb_t *get_control_log_cb,
	void					*get_control_log_cb_arg,
	ct_resource_handle_t	 rsrc_hndl
);										/* return: 0 or error number		*/


/*--------------------------------------------------------------------------*/
/*	Resource Monitoring and Control (RMC) -									*/
/*	  Function Prototypes for Error Injection Command Interfaces			*/
/*--------------------------------------------------------------------------*/

extern ct_int32_t
mc_inject_error_bp_1(					/* Inject an Error into a Resource	*/
	mc_sess_hndl_t		  sess_hndl,	/* input:  session handle			*/
	mc_rsrc_hndl_rsp_t  **response,		/* output: response					*/
	ct_resource_handle_t  rsrc_hndl,	/* input:  resource handle			*/
	ct_char_t			 *error_name,	/* input:  error name				*/
	ct_structured_data_t *data			/* input:  data						*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_inject_error_ap_1(					/* Inject an Error into a Resource	*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,	/* input:  command group handle		*/
	mc_rsrc_hndl_rsp_t  **response,		/* output: response					*/
	ct_resource_handle_t  rsrc_hndl,	/* input:  resource handle			*/
	ct_char_t			 *error_name,	/* input:  error name				*/
	ct_structured_data_t *data			/* input:  data						*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_inject_error_bc_1(					/* Inject an Error into a Resource	*/
	mc_sess_hndl_t		  sess_hndl,	/* input:  session handle			*/
	mc_inject_error_cb_t *inject_error_cb,
	void				 *inject_error_cb_arg,
	ct_resource_handle_t  rsrc_hndl,	/* input:  resource handle			*/
	ct_char_t			 *error_name,	/* input:  error name				*/
	ct_structured_data_t *data			/* input:  data						*/
);										/* return: 0 or error number		*/

extern ct_int32_t
mc_inject_error_ac_1(					/* Inject an Error into a Resource	*/
	mc_cmdgrp_hndl_t	  cmdgrp_hndl,	/* input:  command group handle		*/
	mc_inject_error_cb_t *inject_error_cb,
	void				 *inject_error_cb_arg,
	ct_resource_handle_t  rsrc_hndl,	/* input:  resource handle			*/
	ct_char_t			 *error_name,	/* input:  error name				*/
	ct_structured_data_t *data			/* input:  data						*/
);										/* return: 0 or error number		*/


/*--------------------------------------------------------------------------*/
/*	Resource Monitoring and Control (RMC) -									*/
/*	  Function Prototypes for Access Control List Interfaces				*/
/*--------------------------------------------------------------------------*/

extern ct_int32_t							/* Get Resource-Specific ACL ...  */
mc_get_acl_select_bp_4(						/*		using Attribute Selection */
	mc_sess_hndl_t	   sess_hndl,			/* input:  session handle		  */
	mc_get_acl_rsp_t **rsp_array,			/* output: array of responses	  */
	ct_uint32_t		  *array_cnt,			/* output: count of responses	  */
	ct_char_t		  *rsrc_class_name,		/* input:  resource class name	  */
	ct_char_t		  *select_attrs			/* input:  select string		  */
);											/* return: 0 or error number	  */

extern ct_int32_t							/* Get Resource-Specific ACL ...  */
mc_get_acl_select_ap_4(						/*		using Attribute Selection */
	mc_cmdgrp_hndl_t   cmdgrp_hndl,			/* input:  command group handle	  */
	mc_get_acl_rsp_t **rsp_array,			/* output: array of responses	  */
	ct_uint32_t		  *array_cnt,			/* output: count of responses	  */
	ct_char_t		  *rsrc_class_name,		/* input:  resource class name	  */
	ct_char_t		  *select_attrs			/* input:  select string		  */
);											/* return: 0 or error number	  */

extern ct_int32_t							/* Get Resource-Specific ACL ...  */
mc_get_acl_select_bc_4(						/*		using Attribute Selection */
	mc_sess_hndl_t	   sess_hndl,			/* input:  session handle		  */
	mc_get_acl_cb_t	  *get_acl_cb,			/* input:  response callback	  */
	void			  *cb_arg,				/* input:  callback argument	  */
	ct_char_t		  *rsrc_class_name,		/* input:  resource class name	  */
	ct_char_t		  *select_attrs			/* input:  select string		  */
);											/* return: 0 or error number	  */

extern ct_int32_t							/* Get Resource-Specific ACL ...  */
mc_get_acl_select_ac_4(						/*		using Attribute Selection */
	mc_cmdgrp_hndl_t   cmdgrp_hndl,			/* input:  command group handle	  */
	mc_get_acl_cb_t	  *get_acl_cb,			/* input:  response callback	  */
	void			  *cb_arg,				/* input:  callback argument	  */
	ct_char_t		  *rsrc_class_name,		/* input:  resource class name	  */
	ct_char_t		  *select_attrs			/* input:  select string		  */
);											/* return: 0 or error number	  */

extern ct_int32_t							/* Get Resource-Specific ACL ...  */
mc_get_acl_handle_bp_4(						/*		using Resource Handle	  */
	mc_sess_hndl_t		 sess_hndl,			/* input:  session handle		  */
	mc_get_acl_rsp_t   **response,			/* output: response				  */
	ct_resource_handle_t rsrc_hndl			/* input:  resource handle		  */
);											/* return: 0 or error number	  */

extern ct_int32_t							/* Get Resource-Specific ACL ...  */
mc_get_acl_handle_ap_4(						/*		using Resource Handle	  */
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,		/* input:  command group handle	  */
	mc_get_acl_rsp_t   **response,			/* output: response				  */
	ct_resource_handle_t rsrc_hndl			/* input:  resource handle		  */
);											/* return: 0 or error number	  */

extern ct_int32_t							/* Get Resource-Specific ACL ...  */
mc_get_acl_handle_bc_4(						/*		using Resource Handle	  */
	mc_sess_hndl_t		 sess_hndl,			/* input:  session handle		  */
	mc_get_acl_cb_t		*get_acl_cb,		/* input:  response callback	  */
	void				*cb_arg,			/* input:  callback argument	  */
	ct_resource_handle_t rsrc_hndl			/* input:  resource handle		  */
);											/* return: 0 or error number	  */

extern ct_int32_t							/* Get Resource-Specific ACL ...  */
mc_get_acl_handle_ac_4(						/*		using Resource Handle	  */
	mc_cmdgrp_hndl_t	 cmdgrp_hndl,		/* input:  command group handle	  */
	mc_get_acl_cb_t		*get_acl_cb,		/* input:  response callback	  */
	void				*cb_arg,			/* input:  callback argument	  */
	ct_resource_handle_t rsrc_hndl			/* input:  resource handle		  */
);											/* return: 0 or error number	  */

extern ct_int32_t
mc_class_get_acl_bp_4(						/* Get Class-Wide ACL             */
	mc_sess_hndl_t			 sess_hndl,		/* input:  session handle		  */
	mc_class_get_acl_rsp_t **rsp_array,		/* output: array of responses	  */
	ct_uint32_t				*array_cnt,		/* output: count of responses	  */
	ct_char_t				*class_name,	/* input:  resource class name	  */
	ct_char_t			   **names,		    /* input:  node or domain names	  */
	ct_uint32_t				 name_count,    /* input:  node or domain count	  */
	mc_list_usage_t			 list_usage,    /* input:  name list usage		  */
	mc_acl_type_t			 acl_type		/* input:  type of ACL			  */
);											/* return: 0 or error number	  */

extern ct_int32_t
mc_class_get_acl_ap_4(						/* Get Class-Wide ACL             */
	mc_cmdgrp_hndl_t		 cmdgrp_hndl,	/* input:  command group handle	  */
	mc_class_get_acl_rsp_t **rsp_array,		/* output: array of responses	  */
	ct_uint32_t				*array_cnt,		/* output: count of responses	  */
	ct_char_t				*class_name,	/* input:  resource class name	  */
	ct_char_t			   **names,		    /* input:  node or domain names	  */
	ct_uint32_t				 name_count,    /* input:  node or domain count	  */
	mc_list_usage_t			 list_usage,    /* input:  name list usage		  */
	mc_acl_type_t			 acl_type		/* input:  type of ACL			  */
);											/* return: 0 or error number	  */

extern ct_int32_t
mc_class_get_acl_bc_4(						/* Get Class-Wide ACL             */
	mc_sess_hndl_t			 sess_hndl,		/* input:  session handle		  */
	mc_class_get_acl_cb_t	*get_acl_cb,	/* input:  response callback	  */
	void					*cb_arg,		/* input:  callback argument	  */
	ct_char_t				*class_name,	/* input:  resource class name	  */
	ct_char_t			   **names,		    /* input:  node or domain names	  */
	ct_uint32_t				 name_count,    /* input:  node or domain count	  */
	mc_list_usage_t			 list_usage,    /* input:  name list usage		  */
	mc_acl_type_t			 acl_type		/* input:  type of ACL			  */
);											/* return: 0 or error number	  */

extern ct_int32_t
mc_class_get_acl_ac_4(						/* Get Class-Wide ACL             */
	mc_cmdgrp_hndl_t		 cmdgrp_hndl,	/* input:  command group handle	  */
	mc_class_get_acl_cb_t	*get_acl_cb,	/* input:  response callback	  */
	void					*cb_arg,		/* input:  callback argument	  */
	ct_char_t				*class_name,	/* input:  resource class name	  */
	ct_char_t			   **names,		    /* input:  node or domain names	  */
	ct_uint32_t				 name_count,    /* input:  node or domain count	  */
	mc_list_usage_t			 list_usage,    /* input:  name list usage		  */
	mc_acl_type_t			 acl_type		/* input:  type of ACL			  */
);											/* return: 0 or error number	  */

extern ct_int32_t							/* Set Resource-Specific ACL ...  */
mc_set_acl_select_bp_4(						/*		using Attribute Selection */
	mc_sess_hndl_t			 sess_hndl,		/* input:  session handle		  */
	mc_rsrc_hndl_rsp_t	   **rsp_array,		/* output: array of responses	  */
	ct_uint32_t				*array_cnt,		/* output: count of responses	  */
	ct_char_t				*class_name, 	/* input:  resource class name	  */
	ct_char_t				*select_attrs,	/* input:  select string		  */
	mc_acl_t				 mc_acl			/* input:  resource ACL			  */
);											/* return: 0 or error number	  */

extern ct_int32_t							/* Set Resource-Specific ACL ...  */
mc_set_acl_select_ap_4(						/*		using Attribute Selection */
	mc_cmdgrp_hndl_t		 cmdgrp_hndl,	/* input:  command group handle	  */
	mc_rsrc_hndl_rsp_t	   **rsp_array,		/* output: array of responses	  */
	ct_uint32_t				*array_cnt,		/* output: count of responses	  */
	ct_char_t				*class_name, 	/* input:  resource class name	  */
	ct_char_t				*select_attrs,	/* input:  select string		  */
	mc_acl_t				 mc_acl			/* input:  resource ACL			  */
);											/* return: 0 or error number	  */

extern ct_int32_t							/* Set Resource-Specific ACL ...  */
mc_set_acl_select_bc_4(						/*		using Attribute Selection */
	mc_sess_hndl_t			 sess_hndl,		/* input:  session handle		  */
	mc_set_acl_cb_t			*set_acl_cb,	/* input:  response callback	  */
	void					*cb_arg,		/* input:  callback argument	  */
	ct_char_t				*class_name, 	/* input:  resource class name	  */
	ct_char_t				*select_attrs,	/* input:  select string		  */
	mc_acl_t				 mc_acl			/* input:  resource ACL			  */
);											/* return: 0 or error number	  */

extern ct_int32_t							/* Set Resource-Specific ACL ...  */
mc_set_acl_select_ac_4(						/*		using Attribute Selection */
	mc_cmdgrp_hndl_t		 cmdgrp_hndl,	/* input:  command group handle	  */
	mc_set_acl_cb_t			*set_acl_cb,	/* input:  response callback	  */
	void					*cb_arg,		/* input:  callback argument	  */
	ct_char_t				*class_name, 	/* input:  resource class name	  */
	ct_char_t				*select_attrs,	/* input:  select string		  */
	mc_acl_t				 mc_acl			/* input:  resource ACL			  */
);											/* return: 0 or error number	  */

extern ct_int32_t							/* Set Resource-Specific ACL ...  */
mc_set_acl_handle_bp_4(						/*		using Resource Handle	  */
	mc_sess_hndl_t			 sess_hndl,		/* input:  session handle		  */
	mc_rsrc_hndl_rsp_t	   **response,		/* output: response				  */
	ct_resource_handle_t	 rsrc_hndl,		/* input:  resource handle		  */
	mc_acl_t				 mc_acl			/* input:  resource ACL			  */
);											/* return: 0 or error number	  */

extern ct_int32_t							/* Set Resource-Specific ACL ...  */
mc_set_acl_handle_ap_4(						/*		using Resource Handle	  */
	mc_cmdgrp_hndl_t		 cmdgrp_hndl,	/* input:  command group handle	  */
	mc_rsrc_hndl_rsp_t	   **response,		/* output: response				  */
	ct_resource_handle_t	 rsrc_hndl,		/* input:  resource handle		  */
	mc_acl_t				 mc_acl			/* input:  resource ACL			  */
);											/* return: 0 or error number	  */

extern ct_int32_t							/* Set Resource-Specific ACL ...  */
mc_set_acl_handle_bc_4(						/*		using Resource Handle	  */
	mc_sess_hndl_t			 sess_hndl,		/* input:  session handle		  */
	mc_set_acl_cb_t			*set_acl_cb,	/* input:  response callback	  */
	void					*cb_arg,		/* input:  callback argument	  */
	ct_resource_handle_t	 rsrc_hndl,		/* input:  resource handle		  */
	mc_acl_t				 mc_acl			/* input:  resource ACL			  */
);											/* return: 0 or error number	  */

extern ct_int32_t							/* Set Resource-Specific ACL ...  */
mc_set_acl_handle_ac_4(						/*		using Resource Handle	  */
	mc_cmdgrp_hndl_t		 cmdgrp_hndl,	/* input:  command group handle	  */
	mc_set_acl_cb_t			*set_acl_cb,	/* input:  response callback	  */
	void					*cb_arg,		/* input:  callback argument	  */
	ct_resource_handle_t	 rsrc_hndl,		/* input:  resource handle		  */
	mc_acl_t				 mc_acl			/* input:  resource ACL			  */
);											/* return: 0 or error number	  */

extern ct_int32_t
mc_class_set_acl_bp_4(						/* Set Class-Wide ACL             */
	mc_sess_hndl_t			 sess_hndl,		/* input:  session handle		  */
	mc_class_set_acl_rsp_t **rsp_array,		/* output: array of responses	  */
	ct_uint32_t				*array_cnt,		/* output: count of responses	  */
	ct_char_t				*class_name,	/* input:  resource class name	  */
	ct_char_t			   **names,		    /* input:  node or domain names	  */
	ct_uint32_t				 name_count,    /* input:  node or domain count	  */
	mc_list_usage_t			 list_usage,    /* input:  name list usage		  */
	mc_acl_t				 mc_acl			/* input:  class ACL			  */
);											/* return: 0 or error number	  */

extern ct_int32_t
mc_class_set_acl_ap_4(						/* Set Class-Wide ACL             */
	mc_cmdgrp_hndl_t		 cmdgrp_hndl,	/* input:  command group handle	  */
	mc_class_set_acl_rsp_t **rsp_array,		/* output: array of responses	  */
	ct_uint32_t				*array_cnt,		/* output: count of responses	  */
	ct_char_t				*class_name,	/* input:  resource class name	  */
	ct_char_t			   **names,		    /* input:  node or domain names	  */
	ct_uint32_t				 name_count,    /* input:  node or domain count	  */
	mc_list_usage_t			 list_usage,    /* input:  name list usage		  */
	mc_acl_t				 mc_acl			/* input:  class ACL			  */
);											/* return: 0 or error number	  */

extern ct_int32_t
mc_class_set_acl_bc_4(						/* Set Class-Wide ACL             */
	mc_sess_hndl_t			 sess_hndl,		/* input:  session handle		  */
	mc_class_set_acl_cb_t	*set_acl_cb,	/* input:  response callback	  */
	void					*cb_arg,		/* input:  callback argument	  */
	ct_char_t				*class_name,	/* input:  resource class name	  */
	ct_char_t			   **names,		    /* input:  node or domain names	  */
	ct_uint32_t				 name_count,    /* input:  node or domain count	  */
	mc_list_usage_t			 list_usage,    /* input:  name list usage		  */
	mc_acl_t				 mc_acl			/* input:  class ACL			  */
);											/* return: 0 or error number	  */

extern ct_int32_t
mc_class_set_acl_ac_4(						/* Set Class-Wide ACL             */
	mc_cmdgrp_hndl_t		 cmdgrp_hndl,	/* input:  command group handle	  */
	mc_class_set_acl_cb_t	*set_acl_cb,	/* input:  response callback	  */
	void					*cb_arg,		/* input:  callback argument	  */
	ct_char_t				*class_name,	/* input:  resource class name	  */
	ct_char_t			   **names,		    /* input:  node or domain names	  */
	ct_uint32_t				 name_count,    /* input:  node or domain count	  */
	mc_list_usage_t			 list_usage,    /* input:  name list usage		  */
	mc_acl_t				 mc_acl			/* input:  class ACL			  */
);											/* return: 0 or error number	  */

	
#ifdef __cplusplus
} // end extern "C"
#endif /* __cplusplus */

#endif	/* _H_CT_MC */

/*
 *  If this header file is included multiple times, data type definitions and
 *  function prototypes are only executed once, thanks to the _H_CT_MC macro.
 *  However, if this header file is included multiple times, the
 *  ct_mc_version.h header file must be included multiple times; this allows
 *  the client to change the MC_VERSION desired.  Therefore, it is very
 *  important that the include of ct_mc_version.h by this header file occur
 *  outside of the area protected from multiple execution by the _H_CT_MC
 *  macro.
 */

#include <rsct/ct_mc_version.h>			/* RMCAPI versioning macros			*/
