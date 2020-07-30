/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1998,2010          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/*===========================================================================*/
/*                                                                           */
/* Module Name:  ct_rmc.h                                                    */
/*                                                                           */
/* Description:                                                              */
/*     Interface definitions common to the Resource Monitoring and Control   */
/*     API and the Resource Manager API.                                     */
/*                                                                           */
/*     This file is formatted to be viewed with tab stops set to 4.          */
/*===========================================================================*/
/* @(#)13   1.19   src/rsct/rmc/mccommon/ct_rmc.h, mccommon, rsct_rhay53, rhay531006a 1/8/10 17:17:26 */

#ifndef _H_CT_RMC
#define _H_CT_RMC

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <rsct/ct.h>

/*****************************************************************************/
/*                                                                           */
/*     Data types and enumerations common to the RMCAPI and the RMgrAPI      */
/*                                                                           */
/*****************************************************************************/

/*
 *  Event flags are defined by the mc_event_flags_t enumeration.
 *
 *  MC_EVENT_RE_ARM indicates that the event was generated from the re-arm
 *  expression.
 *
 *  MC_EVENT_EXPR_FALSE indicates that the expression evaluated to false, but
 *  the application requested immediate evaluation when the event was
 *  registered, or the event was generated as a result of either a refresh of
 *  the resource variable or a query event command.
 *
 *  MC_EVENT_IMMED_EVAL indicates that the event was generated as the result
 *  of an immediate evaluation.
 *
 *  MC_EVENT_REFRESH indicates that the event was generated as the result of
 *  a refresh of the resource variable, i.e. monitoring of the variable resumed
 *  after a resource manager recovered from a failure.
 *
 *  MC_EVENT_MISSING_PATTR indicates that one or more requested persistent
 *  attributes could not be returned; these missing persistent attributes are
 *  not supported in the resource specified by mc_rsrc_hndl or the resource
 *  class specified by mc_class_name.
 *
 *  MC_EVENT_UNASSIGN indicates that the resource variable specified in the
 *  event has been unassigned from the event registration; the
 *  MC_EVENT_UNASSIGN_* flags indicate why the unassignment occurred.
 *
 *      MC_EVENT_UNASSIGN_UNDEF indicates the associated resource has been
 *      undefined.
 *
 *      MC_EVENT_UNASSIGN_NO_MATCH indicates the persistent attributes of the
 *      associated resource no longer match the select string or the
 *      associated resource is located on a node just unconfigured.
 *
 *      MC_EVENT_UNASSIGN_NO_GROUP indicates the associated resource is
 *      located on a node that is no longer in the node group specified in the
 *      select string that was supplied to the event registration command.
 *
 *  MC_EVENT_QUERY_EVENT indicates the event was generated as the result of a
 *  query event command.
 *
 *  MC_EVENT_ASSIGN_RESOURCE and MC_EVENT_ASSIGN_NEW_RESOURCE indicate that
 *  the associated resource has been assigned subsequent to the initial event
 *  registration. Furthermore, MC_EVENT_ASSIGN_NEW_RESOURCE indicates that the
 *  resource has recently been created. However, unless the event registration
 *  specified immediate evaluation, some time may elapse from the time the
 *  resource is assigned to the registration to when the event notification
 *  containing MC_EVENT_ASSIGN_RESOURCE or MC_EVENT_ASSIGN_NEW_RESOURCE is
 *  generated. Note that the MC_EVENT_ASSIGN_RESOURCE or
 *  MC_EVENT_ASSIGN_NEW_RESOURCE flags are only present in the first event
 *  notification after the resource is assigned.
 */

typedef enum {
	MC_EVENT_RE_ARM				    = 0x0001,
	MC_EVENT_EXPR_FALSE			    = 0x0002,
	MC_EVENT_IMMED_EVAL			    = 0x0004,
	MC_EVENT_REFRESH			    = 0x0008,
	MC_EVENT_MISSING_PATTR		    = 0x0010,
	MC_EVENT_UNASSIGN			    = 0x0020,

	/*  The following flags were introduced with version 2 of the RMCAPI  */

	MC_EVENT_UNASSIGN_UNDEF		    = 0x0040,
	MC_EVENT_UNASSIGN_NO_MATCH	    = 0x0080,
	MC_EVENT_UNASSIGN_NO_GROUP	    = 0x0100,
	MC_EVENT_QUERY_EVENT		    = 0x0200,
	MC_EVENT_ASSIGN_RESOURCE		= 0x0400,
	MC_EVENT_ASSIGN_NEW_RESOURCE	= 0x0800,

	/* the following flag is internal the RMC subsystem and is
	 * never passed to the RMC client
	 */

	MC_EVENT_FIRST_EVENT	        = 0x40000000
} mc_event_flags_t;

/* define a type for resource class ids -- this is only for compatibility */
typedef ct_resource_class_id_t rmc_resource_class_id_t;

/* define a type for attribute ids */
typedef ct_int32_t rmc_attribute_id_t;

/* define a type for action ids */
typedef ct_int32_t rmc_action_id_t;

/* define a type for error injection ids */
typedef ct_int32_t rmc_error_id_t;
        
/* enumeration of variable types (a variable is a dynamic attribute) */

typedef enum {
	RMC_COUNTER,
	RMC_QUANTITY,
	RMC_STATE,
    RMC_QUANTUM
} rmc_variable_type_t;

/* enumeration of the possible resource type */
typedef enum {
    RMC_TYPE_FIXED,
    RMC_TYPE_FLOATING,
    RMC_TYPE_CONCURRENT
} rmc_resource_type_t;

/* enumeration of resource category */
typedef enum {
    RMC_CATEGORY_MANAGED,
    RMC_CATEGORY_ALIAS,
    RMC_CATEGORY_NOCONTROL
} rmc_resource_category_t;

/* enumeration of the bit of a "ConfigChanged dynamic attribute */
typedef enum {
    RMC_CONFIG_CHG_NONE=0,
    RMC_CONFIG_CHG_ATTR=1,
    RMC_CONFIG_CHG_ACLS=2,
    RMC_CONFIG_CHG_CONSTRAINTS=4
} rmc_config_changed_t;
    
/* enumeration of the possible resource state */
   
typedef enum {
    RMC_OPSTATE_UNKNOWN=0,
    RMC_OPSTATE_ONLINE,
    RMC_OPSTATE_OFFLINE,
    RMC_OPSTATE_FAILED_OFFLINE,
    RMC_OPSTATE_STUCK_ONLINE,
    RMC_OPSTATE_PENDING_ONLINE,
    RMC_OPSTATE_PENDING_OFFLINE,
    RMC_OPSTATE_MIXED,
    RMC_OPSTATE_INELIGIBLE,
    RMF_OPSTATE_MASK=0x7f,
    RMC_OPSTATE_MANUAL_MODE=0x80,
    RMC_OPSTATE_ONLINE_MANUAL,
    RMC_OPSTATE_OFFLINE_MANUAL,
    RMC_OPSTATE_FAILED_OFFLINE_MANUAL,
    RMC_OPSTATE_STUCK_ONLINE_MANUAL,
    RMC_OPSTATE_PENDING_ONLINE_MANUAL,
    RMC_OPSTATE_PENDING_OFFLINE_MANUAL,
    RMC_OPSTATE_MIXED_MANUAL,
    RMC_OPSTATE_INELIGIBLE_MANUAL
} rmc_opstate_t;

/* enumeration of the possible move states */

typedef enum {
	RMC_MOVESTATE_NONE=0,
	RMC_MOVESTATE_PREPARE,
	RMC_MOVESTATE_READY,
	RMC_MOVESTATE_FAILED,
	RMC_MOVESTATE_ENDING
} rmc_movestate_t;

/* enumeration of the possible quorum states */

typedef enum {
	RMC_QUORUM_STATE_HAS=0,
	RMC_QUORUM_STATE_PENDING,
	RMC_QUORUM_STATE_NONE,
	RMC_QUORUM_STATE_UNKNOWN,
	RMC_QUORUM_STATE_NO_SUPPORT
} rmc_quorum_state_t;

/* HealthState - Indicate resource health; augments what is available
 *               via OpState.
 *
 * UNKNOWN       =  0 The resource is offline (OpState = 2).
 * OKAY          =  5 The resource is online with no problems (OpState = 1).
 * WARNING       = 10 Not used.
 * MINOR         = 15 In IBM.VolumeGroup, one or more of the IBM.Disk resources
 *                    making this VG has gone offline; the VG remains online,
 *                    though some of its FileSystems may be inaccessible. Not
 *                    used in other classes.
 * MAJOR         = 20 Not used.
 * CRITICAL      = 25 Not used.
 * FATAL         = 30 Equivalent to OpState=3, Failed Offline.
 * SYSTEMGONE    = 31 Not used.
 * NOTAPPLICABLE = 32 Not used.
 * IN_PROGRESS   = 33 An operation is currently in progress. The value is set
 *                    every five seconds while an online or offline operation
 *                    for this resource is in progress.
 */

typedef enum {
    RMC_HEALTHSTATE_UNKNOWN       = 0,
    RMC_HEALTHSTATE_OKAY          = 5,
    RMC_HEALTHSTATE_WARNING       = 10,
    RMC_HEALTHSTATE_MINOR         = 15,
    RMC_HEALTHSTATE_MAJOR         = 20,
    RMC_HEALTHSTATE_CRITICAL      = 25,
    RMC_HEALTHSTATE_FATAL         = 30,
    RMC_HEALTHSTATE_SYSTEMGONE    = 31,
    RMC_HEALTHSTATE_NOTAPPLICABLE = 32,
    RMC_HEALTHSTATE_IN_PROGRESS   = 33
} rmc_healthstate_t;

/* enumeration of constraint types.  */

typedef enum {
	RMC_CONST_HARD_DEPENDS_ON   = 0,
	RMC_CONST_SOFT_DEPENDS_ON,
	RMC_CONST_HARD_DEPENDS_ON_COLOCATED,
	RMC_CONST_SOFT_DEPENDS_ON_COLOCATED
} rmc_constraint_type_t;

/* enumeration of equivalency policies */
typedef enum {
    RMC_EQU_DEFAULT_POLICY = 0,
    RMC_EQU_PREFERRED_HOME_POLICY
} rmc_equivalency_policy_t;

/* enumeration of equivalency qualifiers */
typedef enum {
    RMC_EQU_AUTO_RETURN_HOME=1,
    RMC_EQU_SERIAL=2
} rmc_equivalency_modifiers_t;

/* define a type to hold information about a constraint */
    
typedef struct {
	ct_int32_t				     constraint_id;
    ct_resource_handle_t         constraint_handle;
    rmc_constraint_type_t        type;
    ct_resource_handle_t         cur_resource;
    rmc_equivalency_policy_t     equ_policy;
    rmc_equivalency_modifiers_t  equ_modifiers;
    ct_uint32_t                  sup_rsrc_count;
    ct_resource_handle_t         sup_rsrc_list[1];    
} rmc_constraint_t;

/* define a type for the parameter on ConstraintAdvisory() to contain failing and
   alternate resource specifications. */

typedef struct {
    ct_int32_t           constraint_id;
    ct_resource_handle_t affected_resource;
    ct_resource_handle_t replacement_resource;
} rmc_constraint_alternate_resource_t;

/* define a type for the parameter to Online() that requires a resolved constraint */
typedef struct {
    ct_int32_t           constraint_id;
    ct_resource_handle_t resource_handle;
} rmc_constraint_resolved_t;
    
/* enumeration of Integrity Check types */

typedef enum {
	RMC_QUICK_INTEGRITY_CHECK = 0,
	RMC_THOROUGH_INTEGRITY_CHECK
} rmc_integrity_check_type_t;

/* enumeration of severity levels in Integrity Check Response */

typedef enum {
	RMC_SEVERITY_INFORMATION,
	RMC_SEVERITY_WARNING,
	RMC_SEVERITY_ERROR
} rmc_severity_t;

/* enumeration of resource manager control log entry types */

typedef enum {
	RMC_CTRL_LOG_ONLINE_REQUEST = 0,
	RMC_CTRL_LOG_OFFLINE_REQUEST,
	RMC_CTRL_LOG_CONSTRAINT_ADV_REQUEST,
	RMC_CTRL_LOG_TRANSITION_ONLINE,
	RMC_CTRL_LOG_TRANSITION_ONLINE_PENDING,
	RMC_CTRL_LOG_TRANSITION_OFFLINE_PENDING,
	RMC_CTRL_LOG_TRANSITION_OFFLINE,
	RMC_CTRL_LOG_TRANSITION_FAILED_OFFLINE,
	RMC_CTRL_LOG_TRANSITION_FAILED_ONLINE
} rmc_log_entry_type_t;

/* name of directory where RMC resource mamnager instances execute; place
 * where core files are produced. The first %s is the cluster id; the second
 * %s is the resource manager name.
 */
#define RMC_RM_RUN_DIR_FMT     "/var/ct/%s/run/mc/%s"

/* name of directory where RMC resource mananger log files are placed.
 * The first %s is the cluster id; the second is the resource manager name.
 */
#define RMC_RM_LOG_DIR_FMT     "/var/ct/%s/log/mc/%s"

#ifdef __cplusplus
} // end extern "C"
#endif /* __cplusplus */

#endif	/* _H_CT_RMC */
