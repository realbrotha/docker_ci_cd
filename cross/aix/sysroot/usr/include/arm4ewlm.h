/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/arm4ewlm.h 1.6                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2003               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)91        1.6  src/bos/usr/include/arm4ewlm.h, sysewlm, bos530  4/26/04  09:25:13	*/
/*
 *   COMPONENT_NAME: sysewlm
 *
 *   ORIGINS: 27
 */

#ifndef _H_EWLM_ARM4EWLM
#define _H_EWLM_ARM4EWLM

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <arm4.h>

#define EWLM_SUBBUFFER_SOCKET_INFO -30000

#define EWLMARM_ACCEPTQ_CLASSIFY_OUTPUT_SIZE 32

typedef arm_int16_t ewlm_hopcount_t;
typedef arm_int16_t ewlm_classification_id_t;
typedef arm_uint8_t ewlm_netclass_t;
typedef arm_int64_t ewlm_socket_desc_t;
typedef arm_int32_t ewlm_boolean_t;

typedef struct ewlm_subbuffer_socket_info
{
   arm_subbuffer_t header;
   ewlm_boolean_t nc_valid;
   ewlm_socket_desc_t socket_desc;
   ewlm_netclass_t opaque[EWLMARM_ACCEPTQ_CLASSIFY_OUTPUT_SIZE];
} ewlm_subbuffer_socket_info_t;

arm_error_t 
ewlm_classify_correlator(
   arm_app_start_handle_t  app_handle,
   arm_id_t                *tran_id,
   arm_int32_t             flags,
   arm_buffer4_t           *buffer4,
   arm_correlator_t        *classify_correlator);


typedef arm_error_t
(* ewlm_classify_correlator_t)(
   arm_app_start_handle_t  app_handle,
   arm_id_t                *tran_id,
   arm_int32_t             flags,
   arm_buffer4_t           *buffer4,
   arm_correlator_t        *classify_correlator);

/* ------------------------------------------------------------------------- */
/* -------------------- EWLM ARM4 adapter services section ----------------- */
/* ------------------------------------------------------------------------- */

#define EWLM_ADAPTER_API_DYNAMIC(type) type
#define EWLM_ADAPTER_API_CALL
#define EWLM_AGENT_TRACE       (0x00000001) 
#define EWLM_CORR_SUFFIX_MAX_LENGTH     128
 
typedef arm_int32_t                ewlm_adap_error_t;
typedef arm_uint64_t               ewlm_time_t;

typedef arm_correlator_length_t    ewlm_pcorr_suffoffset_t;
typedef arm_uint8_t                ewlm_corr_suffix_len_t;

typedef struct ewlm_correlator_suffix
{
   arm_uint8_t    opaque[EWLM_CORR_SUFFIX_MAX_LENGTH];
} ewlm_correlator_suffix_t;

typedef ewlm_correlator_suffix_t           ewlm_corr_suffix_t;

typedef struct ewlm_ad_start_tran_inparms{
        arm_app_start_handle_t     app_handle;
        arm_id_t                   *tran_id;
        arm_correlator_t           *parent_correlator;
        ewlm_pcorr_suffoffset_t    pcorr_suffix_offset;
        arm_tran_start_handle_t    start_handle;
        ewlm_time_t                ewlm_time;  
        ewlm_classification_id_t   tran_class_id;
        ewlm_hopcount_t            hop_count; 
        arm_int32_t                flags;
        arm_buffer4_t              *buffer4;
} ewlm_ad_start_tran_inparms_t;

typedef struct ewlm_ad_generate_correlator_inparms{
        arm_app_start_handle_t     app_handle;
        arm_id_t                   *tran_id;
        arm_correlator_t           *parent_correlator;
        ewlm_pcorr_suffoffset_t    pcorr_suffix_offset;
        arm_int32_t                flags;
        arm_buffer4_t              *buffer4;
} ewlm_ad_generate_correlator_inparms_t;

typedef struct ewlm_ad_register_metric_inparms{
        arm_id_t                   *app_id;
        arm_char_t                 *name;
        arm_metric_format_t        format;
        arm_metric_usage_t         usage;
        arm_char_t                 *unit;
        arm_id_t                   *input_metric_id;
        arm_int32_t                flags;
        arm_buffer4_t              *buffer4;
} ewlm_ad_register_metric_inparms_t;

typedef struct ewlm_ad_report_tran_inparms{
        arm_app_start_handle_t     app_handle;
        arm_id_t                   *tran_id;
        arm_int32_t                tran_status;
        arm_int64_t                response_time;
        arm_stop_time_t            stop_time;
        arm_correlator_t           *parent_correlator;
        ewlm_pcorr_suffoffset_t    pcorr_suffix_offset;
        arm_correlator_t           *current_correlator;
        ewlm_pcorr_suffoffset_t    ccorr_suffix_offset;
        arm_int32_t                flags;
        arm_buffer4_t              *buffer4;
} ewlm_ad_report_tran_inparms_t;

/* ------------------------------------------------------------------------- */
/* --------------------- EWLM ARM4 Adapter API section --------------------- */
/* ------------------------------------------------------------------------- */

EWLM_ADAPTER_API_DYNAMIC(ewlm_adap_error_t) 
adap_register_application(
        arm_id_t                             *input_app_id,
        arm_char_t                           *app_name,
        arm_id_t                             *app_id,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

EWLM_ADAPTER_API_DYNAMIC(ewlm_adap_error_t)
adap_register_transaction(
        arm_id_t                             *input_tran_id,
        arm_id_t                             *app_id,
        arm_char_t                           *tran_name,
        arm_id_t                             *tran_id,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

EWLM_ADAPTER_API_DYNAMIC(ewlm_adap_error_t)
adap_start_application(
        arm_id_t                             *app_id,
        arm_app_start_handle_t               app_handle,
        arm_char_t                           *app_group_name,
        arm_char_t                           *app_instance_name,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

EWLM_ADAPTER_API_DYNAMIC(ewlm_adap_error_t)
adap_start_transaction(
        ewlm_ad_start_tran_inparms_t         *inparms, 
        arm_int32_t                          *out_flags,
        ewlm_corr_suffix_len_t               *corr_suffix_len,
        ewlm_corr_suffix_t                   *corr_suffix);

EWLM_ADAPTER_API_DYNAMIC(ewlm_adap_error_t)
adap_block_transaction(
        arm_tran_start_handle_t              start_handle,
        arm_tran_block_handle_t              block_handle,
        ewlm_time_t                          ewlm_time,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

EWLM_ADAPTER_API_DYNAMIC(ewlm_adap_error_t)
adap_unblock_transaction(
        arm_tran_start_handle_t              start_handle,
        arm_tran_block_handle_t              block_handle,
        ewlm_time_t                          ewlm_time,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

EWLM_ADAPTER_API_DYNAMIC(ewlm_adap_error_t)
adap_stop_transaction(
        arm_tran_start_handle_t              start_handle,
        arm_int32_t                          tran_status,
        ewlm_time_t                          ewlm_time,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

EWLM_ADAPTER_API_DYNAMIC(ewlm_adap_error_t)
adap_discard_transaction(
        arm_tran_start_handle_t              start_handle,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

EWLM_ADAPTER_API_DYNAMIC(ewlm_adap_error_t)
adap_stop_application(
        arm_app_start_handle_t               app_handle,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

EWLM_ADAPTER_API_DYNAMIC(ewlm_adap_error_t)
adap_destroy_application(
        arm_id_t                             *app_id,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

EWLM_ADAPTER_API_DYNAMIC(ewlm_adap_error_t)
adap_bind_thread(
        arm_tran_start_handle_t              start_handle,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

EWLM_ADAPTER_API_DYNAMIC(ewlm_adap_error_t)
adap_unbind_thread(
        arm_tran_start_handle_t              start_handle,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

EWLM_ADAPTER_API_DYNAMIC(ewlm_adap_error_t)
adap_generate_correlator(
        ewlm_ad_generate_correlator_inparms_t  *inparms,
        arm_int32_t                          *out_flags,
        ewlm_corr_suffix_len_t               *corr_suffix_len,
        ewlm_corr_suffix_t                   *corr_suffix);

EWLM_ADAPTER_API_DYNAMIC(ewlm_adap_error_t)
adap_register_metric(
        ewlm_ad_register_metric_inparms_t      *inparms,
        arm_id_t                             *output_metric_id);

EWLM_ADAPTER_API_DYNAMIC(ewlm_adap_error_t)
adap_report_transaction(
        ewlm_ad_report_tran_inparms_t          *inparms);

EWLM_ADAPTER_API_DYNAMIC(ewlm_adap_error_t)
adap_update_transaction(
        arm_tran_start_handle_t              start_handle,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);



/* ------------------------------------------------------------------------- */
/* ------------------ EWLM ARM4 Adapter function pointers------------------- */
/* ------------------------------------------------------------------------- */

/* register meta data API function pointer types */
typedef ewlm_adap_error_t
(EWLM_ADAPTER_API_CALL* adap_register_application_t)(
        arm_id_t                             *input_app_id,
        arm_char_t                           *app_name,
        arm_id_t                             *app_id,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

typedef ewlm_adap_error_t
(EWLM_ADAPTER_API_CALL* adap_register_transaction_t)(
        arm_id_t                             *input_tran_id,
        arm_id_t                             *app_id,
        arm_char_t                           *tran_name,
        arm_id_t                             *tran_id,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

typedef ewlm_adap_error_t
(EWLM_ADAPTER_API_CALL* adap_start_application_t)(
        arm_id_t                             *app_id,
        arm_app_start_handle_t               app_handle,
        arm_char_t                           *app_group_name,
        arm_char_t                           *app_instance_name,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);
 
typedef ewlm_adap_error_t
(EWLM_ADAPTER_API_CALL* adap_start_transaction_t)(
        ewlm_ad_start_tran_inparms_t         *imparms,
        arm_int32_t                          *out_flags,
        ewlm_corr_suffix_len_t               *corr_suffix_len,
        ewlm_corr_suffix_t                   *corr_suffix);

typedef ewlm_adap_error_t
(EWLM_ADAPTER_API_CALL* adap_block_transaction_t)(
        arm_tran_start_handle_t              start_handle,
        arm_tran_block_handle_t              block_handle,
        ewlm_time_t                          ewlm_time,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

typedef ewlm_adap_error_t
(EWLM_ADAPTER_API_CALL* adap_unblock_transaction_t)(
        arm_tran_start_handle_t              start_handle,
        arm_tran_block_handle_t              block_handle,
        ewlm_time_t                          ewlm_time,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

typedef ewlm_adap_error_t
(EWLM_ADAPTER_API_CALL* adap_stop_transaction_t)(
        arm_tran_start_handle_t              start_handle,
        arm_int32_t                          tran_status,
        ewlm_time_t                          ewlm_time,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

typedef ewlm_adap_error_t
(EWLM_ADAPTER_API_CALL* adap_discard_transaction_t)(
        arm_tran_start_handle_t              start_handle,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

typedef ewlm_adap_error_t
(EWLM_ADAPTER_API_CALL* adap_stop_application_t)(
        arm_app_start_handle_t               app_handle,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

typedef ewlm_adap_error_t
(EWLM_ADAPTER_API_CALL* adap_destroy_application_t)(
        arm_id_t                             *app_id,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

typedef ewlm_adap_error_t
(EWLM_ADAPTER_API_CALL* adap_bind_thread_t)(
        arm_tran_start_handle_t              start_handle,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

typedef ewlm_adap_error_t
(EWLM_ADAPTER_API_CALL* adap_unbind_thread_t)(
        arm_tran_start_handle_t              start_handle,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);

typedef ewlm_adap_error_t
(EWLM_ADAPTER_API_CALL* adap_generate_correlator_t)(
        ewlm_ad_generate_correlator_inparms_t  *inparms,
        arm_int32_t                          *out_flags,
        ewlm_corr_suffix_len_t               *corr_suffix_len,
        ewlm_corr_suffix_t                   *corr_suffix);

typedef ewlm_adap_error_t
(EWLM_ADAPTER_API_CALL* adap_register_metric_t)(
        ewlm_ad_register_metric_inparms_t      *inparms,
        arm_id_t                             *output_metric_id);

typedef ewlm_adap_error_t
(EWLM_ADAPTER_API_CALL* adap_report_transaction_t)(
        ewlm_ad_report_tran_inparms_t          *inparms);

typedef ewlm_adap_error_t
(EWLM_ADAPTER_API_CALL* adap_update_transaction_t)(
        arm_tran_start_handle_t              start_handle,
        arm_int32_t                          flags,
        arm_buffer4_t                        *buffer4);


/* ------------------------------------------------------------------------- */
/* --------------------- ARM4 Services Return Codes ------------------------ */
/* ------------------------------------------------------------------------- */

/* 
 * Successful ARM service return codes are positive values.
 */

/* Successful ARM service completion */
#define ARM_RC_SUCCESS                   (0)


/* #define EWLM_IRC_ARM_RANGE_START      (1000) */

/* Successful arm_start_application with an application specified 
 * system address subbuffer.  EWLM does not capture data or manage 
 * such applications */

 #define ARM_RC_SYSADDR                  (1000)

/* An ewlm_classify_correlator() created parent correlator was 
 * ignored because the parent correlator was created with a 
 * different EWLM policy than is currently active on the system.
 * Application should call ewlm_classify_correlator() again to
 * get a new pre-classified parent correlator for the current 
 * EWLM policy. */
#define ARM_RC_CLASSIFY_CORR_IGNORED    (1001) 

/* #define EWLM_IRC_ARM_RANGE_END       (1999) */


/*
 * Unsuccessful ARM service return codes are negative values.   
 */

/* #define EWLM_RC_ARM_RANGE_START      (-1000) */

/*      Application name missing or too long                            */
#define ARM_RC_APPL_NAME                (-1001)

/* Application group name too long */
#define ARM_RC_GRP_NAME                 (-1002)

/* Application instance name too long */
#define ARM_RC_APPL_INST_NAME           (-1003)

/* Transaction name missing or too long */
#define ARM_RC_TRAN_NAME                (-1004)

/* Property name too long */
#define ARM_RC_PROP_NAME                (-1005)

/* Too many property names Some platforms 
   may wish to treat negative property counts 
   the same as zero*/
#define ARM_RC_PROP_NAME_MAX            (-1006)

/* Property value too long */
#define ARM_RC_PROP_VAL                 (-1007)

/* URI name too long */
#define ARM_RC_URI_NAME                 (-1008)

/* User name too long */
#define ARM_RC_USERNAME                 (-1009)

/* Invalid negative buffer4 count */
#define ARM_RC_BUFFER4_COUNT            (-1010)

/* Invalid handle or id output address */
#define ARM_RC_HANDLE_ADDR              (-1011)

/* Invalid correlator output address */
#define ARM_RC_CORR_ADDR                (-1012)

/* Undefined flags bits specified */
#define ARM_RC_FLAGS_UNDEFINED          (-1013)

/* Invalid transaction status */
#define ARM_RC_TRAN_STATUS_INVALID      (-1014)

/* Calling process is not using ARM, it did not register an application */
/* Common team editorial:  This is used by AIX for cases where an input
   ID or handle fails to resolve to an expected control structure.  The
   essence is that the caller is therefore not a legitimate ARM API user.
                                                                        */
#define ARM_RC_NOT_USING_ARM            (-1015)

/* Registered application id does not exist in the calling process */
#define ARM_RC_REGAPP_ID                (-1016)

/* Started application handle does not exist in the calling process */
#define ARM_RC_STARTAPP_HANDLE          (-1017)

/* Registered transaction id does not exist in the calling process */
#define ARM_RC_REGTRAN_ID               (-1018)

/* Transaction handle does not exist in the calling process */ 
#define ARM_RC_TRAN_HANDLE              (-1019)

/* Block handle does not exist */ 
#define ARM_RC_BLOCK_HANDLE             (-1020)

/* Calling process is not authorized to use ARM */
#define ARM_RC_AUTH_ERROR               (-1021)

/* Maximum number of registered applications exceeded */
#define ARM_RC_REGAPP_MAX               (-1022)

/* Maximum number of started applications exceeded */
#define ARM_RC_STARTAPP_MAX             (-1023)

/* Maximum number of registered transactions exceeded */
#define ARM_RC_REGTRAN_MAX              (-1024)

/* Maximum number of started transactions exceeded */
#define ARM_RC_TRAN_MAX                 (-1025)

/* Maximum number of registered applications per process exceeded */
#define ARM_RC_REGAPP_PROC_MAX          (-1026)

/* Maximum number of started applications per process exceeded */
#define ARM_RC_STARTAPP_PROC_MAX        (-1027)

/* Maximum number of registered transactions per process exceeded */
#define ARM_RC_REGTRAN_PROC_MAX         (-1028)

/* Maximum number of started transactions per process exceeded */
#define ARM_RC_TRAN_PROC_MAX            (-1029)

/* Maximum number of blocked threads per transaction exceeded */
#define ARM_RC_BLOCKED_MAX              (-1030)

/* Maximum ARM services memory limit exceeded */
#define ARM_RC_MAXMEM                   (-1031)

/* Process or system out of memory */
#define ARM_RC_ENOMEM                   (-1032)

/* Correlator size is not valid */
#define ARM_RC_CORR_BAD_SIZE            (-1033)

/* System Address buffer was provided */
/* Common team editorial:  This is used for cases of arm_start_transaction()
   or ewlm_classify_correlator() when the started application instance
   associated with the input application handle is for out of process
   transactions (i.e., had a system address sub-buffer specified on the 
   arm_start_application() call.                                         */
#define ARM_RC_SYSADDR_BUFFER           (-1034)

/* This API is not functionally supported by EWLM */
#define ARM_RC_ENOSUPP                  (-1035)

/* ARM support not enabled */
#define ARM_RC_NOT_ENABLED              (-1036)

/* ARM adapter processing failed */
#define ARM_RC_ADAP_FAIL                (-1037)

/* Unsupported character set */
#define ARM_RC_UNSUP_CHARSET            (-1038)

/* Unable to open character set coverter */
/* Common team editorial:  AIX uses this when its libarm4 Init routine,
   following a load, is unable to successfully load its character set
   conversion program.  Other platforms may or may not have this
   consideration.       */
#define ARM_RC_CONVERT_INVAL            (-1039)

/* Invalid string to convert */ 
#define ARM_RC_INVAL_STRING             (-1040)

/* URI mismatch between transaction identity and context */
#define ARM_RC_URI_MISMATCH             (-1041)

/* An invalid NULL ARM parameter was detected */
/* Common team editorial:  This return code applies to all situations
   where a string argument is required but not provided by the
   application.  Examples of this are a null correlator specified on
   arm_get_correlator_flags(), arm_get_correlator_length() and
   arm_generate_correlator(), to name a few.  DO NOT use this return
   code for the cases of missing application name on
   arm_register_application()(use -1001), or missing transaction name
   on arm_register_transaction() (use -1004).  */
#define ARM_RC_NULL_PARM                (-1042)

/* Invalid correlator flag number */
#define ARM_RC_CORR_FLAGNUM             (-1043)

/* Invalid metric format */
/* Common team editorial:  AIX has chosen to validate the
   arm_register_metric() API arguments.  EWLM ARM implementations
   are not required to perform this validation, but if any platform
   chooses to do so, please conform to the following ARM_RC_METRIC_*
   return code uses.  */
#define ARM_RC_METRIC_FORMAT            (-1044) 

/* Invalid metric usage */ 
#define ARM_RC_METRIC_USAGE             (-1045) 

/* Invalid metric name */
#define ARM_RC_METRIC_NAME              (-1046) 

/* Invalid metric unit */
#define ARM_RC_METRIC_UNIT              (-1047)                        

/* No active EWLM agent or policy. */  
/* Common team editorial:  This return code is only applicable to
   ewlm_classify_correlator() for the case where there is not
   sufficient EWLM info/policy to derive a classify correlator.  */
#define ARM_RC_NO_EWLM_AGENT            (-1048)

/* unexpected exception */
#define ARM_RC_INTERNAL_PROBLEM         (-1049) 

#define ARM_RC_INITIALIZATION_ERROR     (-1050)

/* May be used by some platforms for any negative or 
   greater than ARM_PROPERTY_MAX_COUNT value     */
#define ARM_RC_INVALID_PROPERTY_COUNT   (-1051)

/* Mismatch between property names and property values */
#define ARM_RC_VALUE_NAME_MISMATCH      (-1052)

/* NULL pointer passed when identity property count 
   is greater than zero  */
#define ARM_RC_BAD_ID_PROP_ARRAY_PTR    (-1053)

/* NULL pointer passed when context property count 
   is greater than zero */
#define ARM_RC_BAD_CTX_PROP_ARRAY_PTR   (-1054)

/* NULL pointer passed when subbuffer count 
   is greater than zero */
#define ARM_RC_BAD_SUBBUFFER_ARRAY_PTR  (-1055)

/* Maximum number of bind threads per transaction exceeded */
#define ARM_RC_BIND_MAX                 (-1056) 

/* Improperly formatted subbuffer/invalid subbuffer */
#define ARM_RC_SUBBUFFER                (-1058)

/* The maximum number of ID subbuffers has been exceeded */
#define ARM_RC_MAX_ID_COUNT             (-1066)

/* Maximum number of application instance/transaction class 
   combinations has been exceeded                           */
#define ARM_RC_AI_TC_MAX                (-1067)

/* #define EWLM_RC_ARM_RANGE_END        (-1999)  */


/*
 * The return codes below are for implementation internal errors.  
 * They should not occur if the ARM application uses the system
 * provided libarm4 library. 
 *
 * The values within the range -2000 to -2999 are reserved for AIX
 * specific circumstances. The range -1000 to -1999 is for common,
 * cross platform return codes.
 */

/* Invalid buffer type passed to syscall routine */
#define ARM_RC_INT_BADTYPE              (-2000)

/* Invalid buffer length passed to syscall routine */
#define ARM_RC_INT_BUF_LEN              (-2001)

/* Invalid buffer address passed to syscall routine */
#define ARM_RC_INT_BUF_ADDR             (-2002)

/* Invalid group name offset into buffer */
#define ARM_RC_INT_GRP_OFFSET           (-2003)

/* Invalid instance name offset into buffer */
#define ARM_RC_INT_INST_OFFSET          (-2004)

/* Invalid tranclass name offset into buffer */
#define ARM_RC_INT_TRAN_TYPE_OFFSET     (-2005)

/* Invalid property name offset into buffer */
#define ARM_RC_INT_PROP_OFFSET          (-2006)

/* Invalid property value offset into buffer */
#define ARM_RC_INT_PROP_VAL_OFFSET      (-2007)

/* Invalid uri offset into buffer */
#define ARM_RC_INT_URI_OFFSET           (-2008)

/* Internal error 0 */
#define ARM_RC_INT_ERROR_0              (-2009)

/* Internal error in character set encoding */
#define ARM_RC_CHARSET_INT_ERROR_0      (-2010)

/* Invalid application offset into buffer */
#define ARM_RC_INT_APP_OFFSET           (-2011)

/* Invalid buffer4 offset into buffer */
#define ARM_RC_INT_BUF4_OFFSET          (-2012)

/* Invalid buffer length */
#define ARM_RC_INT_BUF4_LEN             (-2013)

/* Invalid context table offset into buffer */
#define ARM_RC_INT_CTX_TBL_OFFSET       (-2014)

/* Invalid context table length */
#define ARM_RC_INT_CTX_TBL_LEN          (-2015)

/* Invalid system address offset into buffer */
#define ARM_RC_INT_ADDR_OFFSET          (-2016)

/* Invalid system address length */
#define ARM_RC_INT_ADDR_LEN             (-2017)

/* Invalid identity offset into buffer */
#define ARM_RC_INT_IDENT_OFFSET         (-2018)

/* Invalid identity length */
#define ARM_RC_INT_IDENT_LEN            (-2019)

/* Invalid correlator offset into buffer */
#define ARM_RC_INT_CORR_OFFSET          (-2020)

/* Invalid user offset into buffer */
#define ARM_RC_INT_USER_OFFSET          (-2021)

/* Invalid user length into buffer */
#define ARM_RC_INT_USER_LEN             (-2022)

/* Invalid user name offset into buffer */
#define ARM_RC_INT_USERNAME_OFFSET      (-2023)

/* Invalid time offset into buffer */
#define ARM_RC_INT_TIME_OFFSET          (-2024)

/* Invalid property table offset into buffer */
#define ARM_RC_INT_PROP_TBL_OFFSET      (-2025)

/* Property values are present, but not the names */
#define ARM_RC_INT_PROP_TBL_EINVAL      (-2026)

/* Invalid property table length */
#define ARM_RC_INT_PROP_TBL_LEN         (-2027)

/* Correlator creation internal failure */
#define ARM_RC_INT_CORR_CREATION        (-2028)
 
/* Invalid adapter buffer address provided to syscall */
#define ARM_RC_INT_ADAPBUF_ADDR         (-2029)                                

/* Undefined flags bits specified in internal flags */
#define ARM_RC_INT_FLAGS_UNDEFINED      (-2030)

/* Classification internal failure */
#define ARM_RC_INT_CLASSIFY_FAIL        (-2031)    

/*      
 * Return codes -20000 through -20999 inclusive are reserved 
 * by the ARM4 standard for possible future standard use
 */
#define ARM4_RC_RESERVED_RANGE_START    (-20000)
#define ARM4_RC_RESERVED_RANGE_END      (-20999)   


#ifdef __cplusplus
}

#endif
#endif

