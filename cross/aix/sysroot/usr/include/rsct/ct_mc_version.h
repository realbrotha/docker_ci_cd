/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2004,2009          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/*===========================================================================*/
/*                                                                           */
/* Module Name:  ct_mc_version.h                                             */
/*                                                                           */
/* Description:                                                              */
/*     Versioning macros for the RMCAPI.  Included by ct_mc.h.               */
/*                                                                           */
/*     This file is formatted to be viewed with tab stops set to 4.          */
/*===========================================================================*/
/* @(#)89   1.6   src/rsct/rmc/rmcapi/ct_mc_version.h, rmcapi, rsct_rhay53, rhay531006a 5/21/09 23:22:36 */


/*
 *  MC_VERSION identifies the version of the Resource Monitoring and Control
 *  Application Programming Interface desired by a client.  The client sets it
 *  before including ct_mc.h.  If the client has not specified a particular
 *  version, version 1 is used.
 */

#define MC_BASE_VERSION		1

#ifndef MC_VERSION
#define MC_VERSION			MC_BASE_VERSION           
#endif  /* MC_VERSION */
 
#if (MC_VERSION < 1) || (MC_VERSION > 6)
#error "MC_VERSION MUST BE AN INTEGER BETWEEN 1 AND 6, INCLUSIVE."
#endif

/*
 *  The following macros convert references to the generic names of RMCAPI
 *  routines, like mc_start_session(), to references to version specific
 *  RMCAPI routines, like mc_start_session_1().  Note that these macros can
 *  deal with the different versions of a routine having different arguments.
 *
 *  These macros are cumulative; each set builds on the previous sets.  First,
 *  there are the macros defined for version 1 of the RMCAPI.  Following are
 *  the sets for subsequent versions of the RMCAPI.  Each subsequent set of
 *  macros only redefines routines that have changed for that version of the
 *  RMCAPI definition.
 *
 *  Before defining a macro, it must be undefined.  This is done to support
 *  the ability to define the macros multiple times for different sections of
 *  a source module, specifying different versions.
 */

/*
 *  =============== Version 1 Routine Name Macro Definitions ===============
 */

#undef  mc_start_session
#undef  mc_end_session
#undef  mc_get_descriptor
#undef  mc_free_descriptor

#define mc_start_session				mc_start_session_1
#define mc_end_session					mc_end_session_1
#define mc_get_descriptor				mc_get_descriptor_1
#define mc_free_descriptor				mc_free_descriptor_1

#undef  mc_dispatch
#undef  mc_start_cmd_grp
#undef  mc_cancel_cmd_grp
#undef  mc_send_cmd_grp
#undef  mc_send_cmd_grp_wait
#undef  mc_free_response

#define mc_dispatch						mc_dispatch_1
#define mc_start_cmd_grp				mc_start_cmd_grp_1
#define mc_cancel_cmd_grp				mc_cancel_cmd_grp_1
#define mc_send_cmd_grp					mc_send_cmd_grp_1
#define mc_send_cmd_grp_wait			mc_send_cmd_grp_wait_1
#define mc_free_response				mc_free_response_1

#undef  mc_reg_event_select_bp
#undef  mc_reg_event_select_ap
#undef  mc_reg_event_select_bc
#undef  mc_reg_event_select_ac

#define mc_reg_event_select_bp			mc_reg_event_select_bp_1
#define mc_reg_event_select_ap			mc_reg_event_select_ap_1
#define mc_reg_event_select_bc			mc_reg_event_select_bc_1
#define mc_reg_event_select_ac			mc_reg_event_select_ac_1

#undef  mc_reg_event_handle_bp
#undef  mc_reg_event_handle_ap
#undef  mc_reg_event_handle_bc
#undef  mc_reg_event_handle_ac

#define mc_reg_event_handle_bp			mc_reg_event_handle_bp_1
#define mc_reg_event_handle_ap			mc_reg_event_handle_ap_1
#define mc_reg_event_handle_bc			mc_reg_event_handle_bc_1
#define mc_reg_event_handle_ac			mc_reg_event_handle_ac_1

#undef  mc_reg_class_event_bp
#undef  mc_reg_class_event_ap
#undef  mc_reg_class_event_bc
#undef  mc_reg_class_event_ac

#define mc_reg_class_event_bp			mc_reg_class_event_bp_1
#define mc_reg_class_event_ap			mc_reg_class_event_ap_1
#define mc_reg_class_event_bc			mc_reg_class_event_bc_1
#define mc_reg_class_event_ac			mc_reg_class_event_ac_1

#undef  mc_unreg_event_bp
#undef  mc_unreg_event_ap
#undef  mc_unreg_event_bc
#undef  mc_unreg_event_ac

#define mc_unreg_event_bp				mc_unreg_event_bp_1
#define mc_unreg_event_ap				mc_unreg_event_ap_1
#define mc_unreg_event_bc				mc_unreg_event_bc_1
#define mc_unreg_event_ac				mc_unreg_event_ac_1

#undef  mc_enumerate_resources_bp
#undef  mc_enumerate_resources_ap
#undef  mc_enumerate_resources_bc
#undef  mc_enumerate_resources_ac

#define mc_enumerate_resources_bp		mc_enumerate_resources_bp_1
#define mc_enumerate_resources_ap		mc_enumerate_resources_ap_1
#define mc_enumerate_resources_bc		mc_enumerate_resources_bc_1
#define mc_enumerate_resources_ac		mc_enumerate_resources_ac_1

#undef  mc_query_p_select_bp
#undef  mc_query_p_select_ap
#undef  mc_query_p_select_bc
#undef  mc_query_p_select_ac

#define mc_query_p_select_bp			mc_query_p_select_bp_1
#define mc_query_p_select_ap			mc_query_p_select_ap_1
#define mc_query_p_select_bc			mc_query_p_select_bc_1
#define mc_query_p_select_ac			mc_query_p_select_ac_1

#undef  mc_query_d_select_bp
#undef  mc_query_d_select_ap
#undef  mc_query_d_select_bc
#undef  mc_query_d_select_ac

#define mc_query_d_select_bp			mc_query_d_select_bp_1
#define mc_query_d_select_ap			mc_query_d_select_ap_1
#define mc_query_d_select_bc			mc_query_d_select_bc_1
#define mc_query_d_select_ac			mc_query_d_select_ac_1

#undef  mc_query_p_handle_bp
#undef  mc_query_p_handle_ap
#undef  mc_query_p_handle_bc
#undef  mc_query_p_handle_ac

#define mc_query_p_handle_bp			mc_query_p_handle_bp_1
#define mc_query_p_handle_ap			mc_query_p_handle_ap_1
#define mc_query_p_handle_bc			mc_query_p_handle_bc_1
#define mc_query_p_handle_ac			mc_query_p_handle_ac_1

#undef  mc_query_d_handle_bp
#undef  mc_query_d_handle_ap
#undef  mc_query_d_handle_bc
#undef  mc_query_d_handle_ac

#define mc_query_d_handle_bp			mc_query_d_handle_bp_1
#define mc_query_d_handle_ap			mc_query_d_handle_ap_1
#define mc_query_d_handle_bc			mc_query_d_handle_bc_1
#define mc_query_d_handle_ac			mc_query_d_handle_ac_1

#undef  mc_class_query_p_bp
#undef  mc_class_query_p_ap
#undef  mc_class_query_p_bc
#undef  mc_class_query_p_ac

#define mc_class_query_p_bp				mc_class_query_p_bp_1
#define mc_class_query_p_ap				mc_class_query_p_ap_1
#define mc_class_query_p_bc				mc_class_query_p_bc_1
#define mc_class_query_p_ac				mc_class_query_p_ac_1

#undef  mc_class_query_d_bp
#undef  mc_class_query_d_ap
#undef  mc_class_query_d_bc
#undef  mc_class_query_d_ac

#define mc_class_query_d_bp				mc_class_query_d_bp_1
#define mc_class_query_d_ap				mc_class_query_d_ap_1
#define mc_class_query_d_bc				mc_class_query_d_bc_1
#define mc_class_query_d_ac				mc_class_query_d_ac_1

#undef  mc_qdef_resource_class_bp
#undef  mc_qdef_resource_class_ap
#undef  mc_qdef_resource_class_bc
#undef  mc_qdef_resource_class_ac

#define mc_qdef_resource_class_bp		mc_qdef_resource_class_bp_1
#define mc_qdef_resource_class_ap		mc_qdef_resource_class_ap_1
#define mc_qdef_resource_class_bc		mc_qdef_resource_class_bc_1
#define mc_qdef_resource_class_ac		mc_qdef_resource_class_ac_1

#undef  mc_qdef_p_attribute_bp
#undef  mc_qdef_p_attribute_ap
#undef  mc_qdef_p_attribute_bc
#undef  mc_qdef_p_attribute_ac

#define mc_qdef_p_attribute_bp			mc_qdef_p_attribute_bp_1
#define mc_qdef_p_attribute_ap			mc_qdef_p_attribute_ap_1
#define mc_qdef_p_attribute_bc			mc_qdef_p_attribute_bc_1
#define mc_qdef_p_attribute_ac			mc_qdef_p_attribute_ac_1

#undef  mc_qdef_d_attribute_bp
#undef  mc_qdef_d_attribute_ap
#undef  mc_qdef_d_attribute_bc
#undef  mc_qdef_d_attribute_ac

#define mc_qdef_d_attribute_bp			mc_qdef_d_attribute_bp_1
#define mc_qdef_d_attribute_ap			mc_qdef_d_attribute_ap_1
#define mc_qdef_d_attribute_bc			mc_qdef_d_attribute_bc_1
#define mc_qdef_d_attribute_ac			mc_qdef_d_attribute_ac_1

#undef  mc_qdef_sbs_bp
#undef  mc_qdef_sbs_ap
#undef  mc_qdef_sbs_bc
#undef  mc_qdef_sbs_ac

#define mc_qdef_sbs_bp					mc_qdef_sbs_bp_1
#define mc_qdef_sbs_ap					mc_qdef_sbs_ap_1
#define mc_qdef_sbs_bc					mc_qdef_sbs_bc_1
#define mc_qdef_sbs_ac					mc_qdef_sbs_ac_1

#undef  mc_qdef_sd_bp
#undef  mc_qdef_sd_ap
#undef  mc_qdef_sd_bc
#undef  mc_qdef_sd_ac

#define mc_qdef_sd_bp					mc_qdef_sd_bp_1
#define mc_qdef_sd_ap					mc_qdef_sd_ap_1
#define mc_qdef_sd_bc					mc_qdef_sd_bc_1
#define mc_qdef_sd_ac					mc_qdef_sd_ac_1

#undef  mc_qdef_valid_values_bp
#undef  mc_qdef_valid_values_ap
#undef  mc_qdef_valid_values_bc
#undef  mc_qdef_valid_values_ac

#define mc_qdef_valid_values_bp			mc_qdef_valid_values_bp_1
#define mc_qdef_valid_values_ap			mc_qdef_valid_values_ap_1
#define mc_qdef_valid_values_bc			mc_qdef_valid_values_bc_1
#define mc_qdef_valid_values_ac			mc_qdef_valid_values_ac_1

#undef  mc_qdef_actions_bp
#undef  mc_qdef_actions_ap
#undef  mc_qdef_actions_bc
#undef  mc_qdef_actions_ac

#define mc_qdef_actions_bp				mc_qdef_actions_bp_1
#define mc_qdef_actions_ap				mc_qdef_actions_ap_1
#define mc_qdef_actions_bc				mc_qdef_actions_bc_1
#define mc_qdef_actions_ac				mc_qdef_actions_ac_1

#undef  mc_qdef_err_inject_bp
#undef  mc_qdef_err_inject_ap
#undef  mc_qdef_err_inject_bc
#undef  mc_qdef_err_inject_ac

#define mc_qdef_err_inject_bp			mc_qdef_err_inject_bp_1
#define mc_qdef_err_inject_ap			mc_qdef_err_inject_ap_1
#define mc_qdef_err_inject_bc			mc_qdef_err_inject_bc_1
#define mc_qdef_err_inject_ac			mc_qdef_err_inject_ac_1

#undef  mc_qdef_dependencies_bp
#undef  mc_qdef_dependencies_ap
#undef  mc_qdef_dependencies_bc
#undef  mc_qdef_dependencies_ac

#define mc_qdef_dependencies_bp			mc_qdef_dependencies_bp_1
#define mc_qdef_dependencies_ap			mc_qdef_dependencies_ap_1
#define mc_qdef_dependencies_bc			mc_qdef_dependencies_bc_1
#define mc_qdef_dependencies_ac			mc_qdef_dependencies_ac_1

#undef  mc_validate_rsrc_hndl_bp
#undef  mc_validate_rsrc_hndl_ap
#undef  mc_validate_rsrc_hndl_bc
#undef  mc_validate_rsrc_hndl_ac

#define mc_validate_rsrc_hndl_bp		mc_validate_rsrc_hndl_bp_1
#define mc_validate_rsrc_hndl_ap		mc_validate_rsrc_hndl_ap_1
#define mc_validate_rsrc_hndl_bc		mc_validate_rsrc_hndl_bc_1
#define mc_validate_rsrc_hndl_ac		mc_validate_rsrc_hndl_ac_1

#undef  mc_define_resource_bp
#undef  mc_define_resource_ap
#undef  mc_define_resource_bc
#undef  mc_define_resource_ac

#define mc_define_resource_bp			mc_define_resource_bp_1
#define mc_define_resource_ap			mc_define_resource_ap_1
#define mc_define_resource_bc			mc_define_resource_bc_1
#define mc_define_resource_ac			mc_define_resource_ac_1

#undef  mc_undefine_resource_bp
#undef  mc_undefine_resource_ap
#undef  mc_undefine_resource_bc
#undef  mc_undefine_resource_ac

#define mc_undefine_resource_bp			mc_undefine_resource_bp_1
#define mc_undefine_resource_ap			mc_undefine_resource_ap_1
#define mc_undefine_resource_bc			mc_undefine_resource_bc_1
#define mc_undefine_resource_ac			mc_undefine_resource_ac_1

#undef  mc_refresh_config_bp
#undef  mc_refresh_config_ap
#undef  mc_refresh_config_bc
#undef  mc_refresh_config_ac

#define mc_refresh_config_bp			mc_refresh_config_bp_1
#define mc_refresh_config_ap			mc_refresh_config_ap_1
#define mc_refresh_config_bc			mc_refresh_config_bc_1
#define mc_refresh_config_ac			mc_refresh_config_ac_1

#undef  mc_do_integrity_check_bp
#undef  mc_do_integrity_check_ap
#undef  mc_do_integrity_check_bc
#undef  mc_do_integrity_check_ac

#define mc_do_integrity_check_bp		mc_do_integrity_check_bp_1
#define mc_do_integrity_check_ap		mc_do_integrity_check_ap_1
#define mc_do_integrity_check_bc		mc_do_integrity_check_bc_1
#define mc_do_integrity_check_ac		mc_do_integrity_check_ac_1

#undef  mc_set_select_bp
#undef  mc_set_select_ap
#undef  mc_set_select_bc
#undef  mc_set_select_ac

#define mc_set_select_bp				mc_set_select_bp_1
#define mc_set_select_ap				mc_set_select_ap_1
#define mc_set_select_bc				mc_set_select_bc_1
#define mc_set_select_ac				mc_set_select_ac_1

#undef  mc_set_handle_bp
#undef  mc_set_handle_ap
#undef  mc_set_handle_bc
#undef  mc_set_handle_ac

#define mc_set_handle_bp				mc_set_handle_bp_1
#define mc_set_handle_ap				mc_set_handle_ap_1
#define mc_set_handle_bc				mc_set_handle_bc_1
#define mc_set_handle_ac				mc_set_handle_ac_1

#undef  mc_class_set_bp
#undef  mc_class_set_ap
#undef  mc_class_set_bc
#undef  mc_class_set_ac

#define mc_class_set_bp					mc_class_set_bp_1
#define mc_class_set_ap					mc_class_set_ap_1
#define mc_class_set_bc					mc_class_set_bc_1
#define mc_class_set_ac					mc_class_set_ac_1

#undef  mc_invoke_action_bp
#undef  mc_invoke_action_ap
#undef  mc_invoke_action_bc
#undef  mc_invoke_action_ac

#define mc_invoke_action_bp				mc_invoke_action_bp_1
#define mc_invoke_action_ap				mc_invoke_action_ap_1
#define mc_invoke_action_bc				mc_invoke_action_bc_1
#define mc_invoke_action_ac				mc_invoke_action_ac_1

#undef  mc_invoke_class_action_bp
#undef  mc_invoke_class_action_ap
#undef  mc_invoke_class_action_bc
#undef  mc_invoke_class_action_ac

#define mc_invoke_class_action_bp		mc_invoke_class_action_bp_1
#define mc_invoke_class_action_ap		mc_invoke_class_action_ap_1
#define mc_invoke_class_action_bc		mc_invoke_class_action_bc_1
#define mc_invoke_class_action_ac		mc_invoke_class_action_ac_1

#undef  mc_enum_constraints_bp
#undef  mc_enum_constraints_ap
#undef  mc_enum_constraints_bc
#undef  mc_enum_constraints_ac

#define mc_enum_constraints_bp			mc_enum_constraints_bp_1
#define mc_enum_constraints_ap			mc_enum_constraints_ap_1
#define mc_enum_constraints_bc			mc_enum_constraints_bc_1
#define mc_enum_constraints_ac			mc_enum_constraints_ac_1

#undef  mc_define_constraint_bp
#undef  mc_define_constraint_ap
#undef  mc_define_constraint_bc
#undef  mc_define_constraint_ac

#define mc_define_constraint_bp			mc_define_constraint_bp_1
#define mc_define_constraint_ap			mc_define_constraint_ap_1
#define mc_define_constraint_bc			mc_define_constraint_bc_1
#define mc_define_constraint_ac			mc_define_constraint_ac_1

#undef  mc_undefine_constraint_bp
#undef  mc_undefine_constraint_ap
#undef  mc_undefine_constraint_bc
#undef  mc_undefine_constraint_ac

#define mc_undefine_constraint_bp		mc_undefine_constraint_bp_1
#define mc_undefine_constraint_ap		mc_undefine_constraint_ap_1
#define mc_undefine_constraint_bc		mc_undefine_constraint_bc_1
#define mc_undefine_constraint_ac		mc_undefine_constraint_ac_1

#undef  mc_online_bp
#undef  mc_online_ap
#undef  mc_online_bc
#undef  mc_online_ac

#define mc_online_bp					mc_online_bp_1
#define mc_online_ap					mc_online_ap_1
#define mc_online_bc					mc_online_bc_1
#define mc_online_ac					mc_online_ac_1

#undef  mc_offline_bp
#undef  mc_offline_ap
#undef  mc_offline_bc
#undef  mc_offline_ac

#define mc_offline_bp					mc_offline_bp_1
#define mc_offline_ap					mc_offline_ap_1
#define mc_offline_bc					mc_offline_bc_1
#define mc_offline_ac					mc_offline_ac_1

#undef  mc_reset_bp
#undef  mc_reset_ap
#undef  mc_reset_bc
#undef  mc_reset_ac

#define mc_reset_bp						mc_reset_bp_1
#define mc_reset_ap						mc_reset_ap_1
#define mc_reset_bc						mc_reset_bc_1
#define mc_reset_ac						mc_reset_ac_1

#undef  mc_constraint_advisory_bp
#undef  mc_constraint_advisory_ap
#undef  mc_constraint_advisory_bc
#undef  mc_constraint_advisory_ac

#define mc_constraint_advisory_bp		mc_constraint_advisory_bp_1
#define mc_constraint_advisory_ap		mc_constraint_advisory_ap_1
#define mc_constraint_advisory_bc		mc_constraint_advisory_bc_1
#define mc_constraint_advisory_ac		mc_constraint_advisory_ac_1

#undef  mc_get_control_log_bp
#undef  mc_get_control_log_ap
#undef  mc_get_control_log_bc
#undef  mc_get_control_log_ac

#define mc_get_control_log_bp			mc_get_control_log_bp_1
#define mc_get_control_log_ap			mc_get_control_log_ap_1
#define mc_get_control_log_bc			mc_get_control_log_bc_1
#define mc_get_control_log_ac			mc_get_control_log_ac_1

#undef  mc_inject_error_bp
#undef  mc_inject_error_ap
#undef  mc_inject_error_bc
#undef  mc_inject_error_ac

#define mc_inject_error_bp				mc_inject_error_bp_1
#define mc_inject_error_ap				mc_inject_error_ap_1
#define mc_inject_error_bc				mc_inject_error_bc_1
#define mc_inject_error_ac				mc_inject_error_ac_1

/*
 *  =============== Version 2 Routine Name Macro Definitions ===============
 *
 *  There must be a version 2 mc_start_session() routine to enable run-time
 *  checks.  mc_timed_start_session(), mc_session_status(), mc_session_info(),
 *  and the mc_query_event_xx() routines are new to version 2.  All the other
 *  routines referenced below have been modified in version 2.
 */

#if (MC_VERSION >= 2)

#undef  mc_start_session
#undef  mc_timed_start_session	
#undef  mc_session_status
#undef  mc_session_info

#define mc_start_session				mc_start_session_2
#define mc_timed_start_session			mc_timed_start_session_2
#define mc_session_status				mc_session_status_2
#define mc_session_info					mc_session_info_2

#undef  mc_reg_event_select_bp
#undef  mc_reg_event_select_ap
#undef  mc_reg_event_select_bc
#undef  mc_reg_event_select_ac

#define mc_reg_event_select_bp			mc_reg_event_select_bp_2
#define mc_reg_event_select_ap			mc_reg_event_select_ap_2
#define mc_reg_event_select_bc			mc_reg_event_select_bc_2
#define mc_reg_event_select_ac			mc_reg_event_select_ac_2

#undef  mc_reg_event_handle_bp
#undef  mc_reg_event_handle_ap
#undef  mc_reg_event_handle_bc
#undef  mc_reg_event_handle_ac

#define mc_reg_event_handle_bp			mc_reg_event_handle_bp_2
#define mc_reg_event_handle_ap			mc_reg_event_handle_ap_2
#define mc_reg_event_handle_bc			mc_reg_event_handle_bc_2
#define mc_reg_event_handle_ac			mc_reg_event_handle_ac_2

#undef  mc_query_event_bp
#undef  mc_query_event_ap
#undef  mc_query_event_bc
#undef  mc_query_event_ac

#define mc_query_event_bp				mc_query_event_bp_2
#define mc_query_event_ap				mc_query_event_ap_2
#define mc_query_event_bc				mc_query_event_bc_2
#define mc_query_event_ac				mc_query_event_ac_2

#undef  mc_invoke_class_action_bp
#undef  mc_invoke_class_action_ap
#undef  mc_invoke_class_action_bc
#undef  mc_invoke_class_action_ac

#define mc_invoke_class_action_bp		mc_invoke_class_action_bp_2
#define mc_invoke_class_action_ap		mc_invoke_class_action_ap_2
#define mc_invoke_class_action_bc		mc_invoke_class_action_bc_2
#define mc_invoke_class_action_ac		mc_invoke_class_action_ac_2

#undef  mc_online_bp
#undef  mc_online_ap
#undef  mc_online_bc
#undef  mc_online_ac

#define mc_online_bp					mc_online_bp_2
#define mc_online_ap					mc_online_ap_2
#define mc_online_bc					mc_online_bc_2
#define mc_online_ac					mc_online_ac_2

#undef  mc_offline_bp
#undef  mc_offline_ap
#undef  mc_offline_bc
#undef  mc_offline_ac

#define mc_offline_bp					mc_offline_bp_2
#define mc_offline_ap					mc_offline_ap_2
#define mc_offline_bc					mc_offline_bc_2
#define mc_offline_ac					mc_offline_ac_2

#undef  mc_reset_bp
#undef  mc_reset_ap
#undef  mc_reset_bc
#undef  mc_reset_ac

#define mc_reset_bp						mc_reset_bp_2
#define mc_reset_ap						mc_reset_ap_2
#define mc_reset_bc						mc_reset_bc_2
#define mc_reset_ac						mc_reset_ac_2

#endif /* (MC_VERSION >= 2) */

/*
 *  =============== Version 3 Routine Name Macro Definitions ===============
 *
 *  There must be version 3 flavors of the mc_start_session() and
 *  mc_timed_start_session() routines to enable run-time checks.
 *  All the other routines referenced below have been modified in version 3.
 */

#if (MC_VERSION >= 3)

#undef  mc_start_session
#undef  mc_timed_start_session	

#define mc_start_session				mc_start_session_3
#define mc_timed_start_session			mc_timed_start_session_3

#undef  mc_reg_class_event_bp
#undef  mc_reg_class_event_ap
#undef  mc_reg_class_event_bc
#undef  mc_reg_class_event_ac

#define mc_reg_class_event_bp			mc_reg_class_event_bp_3
#define mc_reg_class_event_ap			mc_reg_class_event_ap_3
#define mc_reg_class_event_bc			mc_reg_class_event_bc_3
#define mc_reg_class_event_ac			mc_reg_class_event_ac_3

#undef  mc_class_query_p_bp
#undef  mc_class_query_p_ap
#undef  mc_class_query_p_bc
#undef  mc_class_query_p_ac

#define mc_class_query_p_bp				mc_class_query_p_bp_3
#define mc_class_query_p_ap				mc_class_query_p_ap_3
#define mc_class_query_p_bc				mc_class_query_p_bc_3
#define mc_class_query_p_ac				mc_class_query_p_ac_3

#undef  mc_class_query_d_bp
#undef  mc_class_query_d_ap
#undef  mc_class_query_d_bc
#undef  mc_class_query_d_ac

#define mc_class_query_d_bp				mc_class_query_d_bp_3
#define mc_class_query_d_ap				mc_class_query_d_ap_3
#define mc_class_query_d_bc				mc_class_query_d_bc_3
#define mc_class_query_d_ac				mc_class_query_d_ac_3

#undef  mc_class_set_bp
#undef  mc_class_set_ap
#undef  mc_class_set_bc
#undef  mc_class_set_ac

#define mc_class_set_bp					mc_class_set_bp_3
#define mc_class_set_ap					mc_class_set_ap_3
#define mc_class_set_bc					mc_class_set_bc_3
#define mc_class_set_ac					mc_class_set_ac_3

#undef  mc_invoke_class_action_bp
#undef  mc_invoke_class_action_ap
#undef  mc_invoke_class_action_bc
#undef  mc_invoke_class_action_ac

#define mc_invoke_class_action_bp		mc_invoke_class_action_bp_3
#define mc_invoke_class_action_ap		mc_invoke_class_action_ap_3
#define mc_invoke_class_action_bc		mc_invoke_class_action_bc_3
#define mc_invoke_class_action_ac		mc_invoke_class_action_ac_3

#endif /* (MC_VERSION >= 3) */

/*
 *  =============== Version 4 Routine Name Macro Definitions ===============
 *
 *  There must be version 4 flavors of the mc_start_session() and
 *  mc_timed_start_session() routines to enable run-time checks.
 *  All the other routines referenced below are new to version 4.
 */

#if (MC_VERSION >= 4)

#undef  mc_start_session
#undef  mc_timed_start_session	

#define mc_start_session					mc_start_session_4
#define mc_timed_start_session				mc_timed_start_session_4

#undef  mc_enumerate_permitted_rsrcs_bp
#undef  mc_enumerate_permitted_rsrcs_ap
#undef  mc_enumerate_permitted_rsrcs_bc
#undef  mc_enumerate_permitted_rsrcs_ac

#define mc_enumerate_permitted_rsrcs_bp		mc_enumerate_permitted_rsrcs_bp_4
#define mc_enumerate_permitted_rsrcs_ap		mc_enumerate_permitted_rsrcs_ap_4
#define mc_enumerate_permitted_rsrcs_bc		mc_enumerate_permitted_rsrcs_bc_4
#define mc_enumerate_permitted_rsrcs_ac		mc_enumerate_permitted_rsrcs_ac_4

#undef  mc_get_acl_select_bp
#undef  mc_get_acl_select_ap
#undef  mc_get_acl_select_bc
#undef  mc_get_acl_select_ac

#define mc_get_acl_select_bp				mc_get_acl_select_bp_4
#define mc_get_acl_select_ap				mc_get_acl_select_ap_4
#define mc_get_acl_select_bc				mc_get_acl_select_bc_4
#define mc_get_acl_select_ac				mc_get_acl_select_ac_4

#undef  mc_get_acl_handle_bp
#undef  mc_get_acl_handle_ap
#undef  mc_get_acl_handle_bc
#undef  mc_get_acl_handle_ac

#define mc_get_acl_handle_bp				mc_get_acl_handle_bp_4
#define mc_get_acl_handle_ap				mc_get_acl_handle_ap_4
#define mc_get_acl_handle_bc				mc_get_acl_handle_bc_4
#define mc_get_acl_handle_ac				mc_get_acl_handle_ac_4

#undef  mc_class_get_acl_bp
#undef  mc_class_get_acl_ap
#undef  mc_class_get_acl_bc
#undef  mc_class_get_acl_ac

#define mc_class_get_acl_bp					mc_class_get_acl_bp_4
#define mc_class_get_acl_ap					mc_class_get_acl_ap_4
#define mc_class_get_acl_bc					mc_class_get_acl_bc_4
#define mc_class_get_acl_ac					mc_class_get_acl_ac_4

#undef  mc_set_acl_select_bp
#undef  mc_set_acl_select_ap
#undef  mc_set_acl_select_bc
#undef  mc_set_acl_select_ac

#define mc_set_acl_select_bp				mc_set_acl_select_bp_4
#define mc_set_acl_select_ap				mc_set_acl_select_ap_4
#define mc_set_acl_select_bc				mc_set_acl_select_bc_4
#define mc_set_acl_select_ac				mc_set_acl_select_ac_4

#undef  mc_set_acl_handle_bp
#undef  mc_set_acl_handle_ap
#undef  mc_set_acl_handle_bc
#undef  mc_set_acl_handle_ac

#define mc_set_acl_handle_bp				mc_set_acl_handle_bp_4
#define mc_set_acl_handle_ap				mc_set_acl_handle_ap_4
#define mc_set_acl_handle_bc				mc_set_acl_handle_bc_4
#define mc_set_acl_handle_ac				mc_set_acl_handle_ac_4

#undef  mc_class_set_acl_bp
#undef  mc_class_set_acl_ap
#undef  mc_class_set_acl_bc
#undef  mc_class_set_acl_ac

#define mc_class_set_acl_bp					mc_class_set_acl_bp_4
#define mc_class_set_acl_ap					mc_class_set_acl_ap_4
#define mc_class_set_acl_bc					mc_class_set_acl_bc_4
#define mc_class_set_acl_ac					mc_class_set_acl_ac_4

#endif /* (MC_VERSION >= 4) */

/*
 *  =============== Version 5 Routine Name Macro Definitions ===============
 *
 *  There must be version 5 flavors of the mc_start_session() and
 *  mc_timed_start_session() routines to enable run-time checks.
 */

#if (MC_VERSION >= 5)

#undef  mc_start_session
#undef  mc_timed_start_session	

#define mc_start_session					mc_start_session_5
#define mc_timed_start_session				mc_timed_start_session_5

#endif /* (MC_VERSION >= 5) */

/*
 *  =============== Version 6 Routine Name Macro Definitions ===============
 *
 *  There must be version 6 flavors of the mc_start_session() and
 *  mc_timed_start_session() routines to enable run-time checks.
 */

#if (MC_VERSION >= 6)

#undef  mc_start_session
#undef  mc_timed_start_session	

#define mc_start_session					mc_start_session_6
#define mc_timed_start_session				mc_timed_start_session_6

#undef  mc_reg_event_select_bp
#undef  mc_reg_event_select_ap
#undef  mc_reg_event_select_bc
#undef  mc_reg_event_select_ac

#define mc_reg_event_select_bp				mc_reg_event_select_bp_6
#define mc_reg_event_select_ap				mc_reg_event_select_ap_6
#define mc_reg_event_select_bc				mc_reg_event_select_bc_6
#define mc_reg_event_select_ac				mc_reg_event_select_ac_6

#undef  mc_reg_event_handle_bp
#undef  mc_reg_event_handle_ap
#undef  mc_reg_event_handle_bc
#undef  mc_reg_event_handle_ac

#define mc_reg_event_handle_bp				mc_reg_event_handle_bp_6
#define mc_reg_event_handle_ap				mc_reg_event_handle_ap_6
#define mc_reg_event_handle_bc				mc_reg_event_handle_bc_6
#define mc_reg_event_handle_ac				mc_reg_event_handle_ac_6

#undef  mc_reg_class_event_bp
#undef  mc_reg_class_event_ap
#undef  mc_reg_class_event_bc
#undef  mc_reg_class_event_ac

#define mc_reg_class_event_bp				mc_reg_class_event_bp_6
#define mc_reg_class_event_ap				mc_reg_class_event_ap_6
#define mc_reg_class_event_bc				mc_reg_class_event_bc_6
#define mc_reg_class_event_ac				mc_reg_class_event_ac_6

#undef  mc_qdef_d_attribute_bp
#undef  mc_qdef_d_attribute_ap
#undef  mc_qdef_d_attribute_bc
#undef  mc_qdef_d_attribute_ac

#define mc_qdef_d_attribute_bp				mc_qdef_d_attribute_bp_6
#define mc_qdef_d_attribute_ap				mc_qdef_d_attribute_ap_6
#define mc_qdef_d_attribute_bc				mc_qdef_d_attribute_bc_6
#define mc_qdef_d_attribute_ac				mc_qdef_d_attribute_ac_6

#endif /* (MC_VERSION >= 6) */

/*
 *  The following macros convert references to the generic names of RMCAPI
 *  data types, like mc_event_t, to references to version specific RMCAPI
 *  data types, like mc_event_1_t.  This is only done for data types that
 *  have changed between versions of the RMCAPI.
 *
 *  These macros are cumulative; each set builds on the previous sets.  First,
 *  there are the macros defined for version 1 of the RMCAPI.  Following are
 *  the sets for subsequent versions of the RMCAPI.  Each subsequent set of
 *  macros only redefines data types that have changed for that version of the
 *  RMCAPI definition.
 *
 *  Before defining a macro, it must be undefined.  This is done to support
 *  the ability to define the macros multiple times for different sections of
 *  a source module, specifying different versions.
 */

/*
 *  =============== Version 1 Data Type Macro Definitions ===============
 */

#undef  mc_event_t
#undef  mc_event_cb_t
#undef  mc_class_event_t
#undef  mc_class_event_cb_t
#undef  mc_class_query_rsp_t
#undef  mc_class_query_cb_t
#undef  mc_class_set_rsp_t
#undef  mc_class_set_cb_t
#undef  mc_class_action_rsp_t
#undef  mc_class_action_cb_t
#undef  mc_qdef_dattr_rsp_t
#undef  mc_qdef_dattr_cb_t

#define mc_event_t						mc_event_1_t
#define mc_event_cb_t					mc_event_cb_1_t
#define mc_class_event_t				mc_class_event_1_t
#define mc_class_event_cb_t				mc_class_event_cb_1_t
#define mc_class_query_rsp_t			mc_class_query_rsp_1_t
#define mc_class_query_cb_t				mc_class_query_cb_1_t
#define mc_class_set_rsp_t				mc_class_set_rsp_1_t
#define mc_class_set_cb_t				mc_class_set_cb_1_t
#define mc_class_action_rsp_t			mc_class_action_rsp_1_t
#define mc_class_action_cb_t			mc_class_action_cb_1_t
#define mc_qdef_dattr_rsp_t				mc_qdef_dattr_rsp_1_t
#define mc_qdef_dattr_cb_t				mc_qdef_dattr_cb_1_t

/*
 *  =============== Version 2 Data Type Macro Definitions ===============
 */

#if (MC_VERSION >= 2)

#undef  mc_event_t
#undef  mc_event_cb_t
#undef  mc_class_action_rsp_t
#undef  mc_class_action_cb_t

#define mc_event_t						mc_event_2_t
#define mc_event_cb_t					mc_event_cb_2_t
#define mc_class_action_rsp_t			mc_class_action_rsp_2_t
#define mc_class_action_cb_t			mc_class_action_cb_2_t

#endif /* (MC_VERSION >= 2) */

/*
 *  =============== Version 3 Data Type Macro Definitions ===============
 */

#if (MC_VERSION >= 3)

#undef  mc_class_event_t
#undef  mc_class_event_cb_t
#undef  mc_class_query_rsp_t
#undef  mc_class_query_cb_t
#undef  mc_class_set_rsp_t
#undef  mc_class_set_cb_t
#undef  mc_class_action_rsp_t
#undef  mc_class_action_cb_t

#define mc_class_event_t				mc_class_event_3_t
#define mc_class_event_cb_t				mc_class_event_cb_3_t
#define mc_class_query_rsp_t			mc_class_query_rsp_3_t
#define mc_class_query_cb_t				mc_class_query_cb_3_t
#define mc_class_set_rsp_t				mc_class_set_rsp_3_t
#define mc_class_set_cb_t				mc_class_set_cb_3_t
#define mc_class_action_rsp_t			mc_class_action_rsp_3_t
#define mc_class_action_cb_t			mc_class_action_cb_3_t

#endif /* (MC_VERSION >= 3) */

/*
 *  =============== Version 4 Data Type Macro Definitions ===============
 */

#if (MC_VERSION >= 4)

/*  Version 4 does not change any already defined data types; it only provides
 *  additional types.
 */

#endif /* (MC_VERSION >= 4) */

/*
 *  =============== Version 5 Data Type Macro Definitions ===============
 */

#if (MC_VERSION >= 5)

/*  Version 5 does not change any already defined data types; it only
 *  adds a value to an enumeration type.
 */

#endif /* (MC_VERSION >= 5) */

/*
 *  =============== Version 6 Data Type Macro Definitions ===============
 */

#if (MC_VERSION >= 6)

#undef  mc_event_t
#undef  mc_event_cb_t
#undef  mc_class_event_t
#undef  mc_class_event_cb_t
#undef  mc_qdef_dattr_rsp_t
#undef  mc_qdef_dattr_cb_t

#define mc_event_t						mc_event_6_t
#define mc_event_cb_t					mc_event_cb_6_t
#define mc_class_event_t				mc_class_event_6_t
#define mc_class_event_cb_t				mc_class_event_cb_6_t
#define mc_qdef_dattr_rsp_t				mc_qdef_dattr_rsp_6_t
#define mc_qdef_dattr_cb_t				mc_qdef_dattr_cb_6_t

#endif /* (MC_VERSION >= 6) */
