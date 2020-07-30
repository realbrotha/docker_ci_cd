/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/arm4.h 1.2                                  */
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
/* @(#)90        1.2  src/bos/usr/include/arm4.h, sysewlm, bos530  12/17/03  11:56:35	*/
/*
 *   COMPONENT_NAME: sysewlm
 *
 *   ORIGINS: 259, 27
 */

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Copyright (c) 2003 The Open Group                                         */
/* Copyright (c) 2003 IBM Corporation                                        */
/*                                                                           */
/* This file has been modified by the IBM Corporation from the original      */
/* version copyrighted by The Open Group.                                    */
/*                                                                           */
/* Permission is hereby granted, free of charge, to any person obtaining a   */
/* copy of this software (the "Software"), to deal in the Software without   */
/* restriction, including without limitation the rights to use, copy,        */
/* modify, merge, publish, distribute, sublicense, and/or sell copies of     */
/* the Software, and to permit persons to whom the Software is furnished     */
/* to do so, subject to the following conditions:                            */
/*                                                                           */
/* The above copyright notice and this permission notice shall be included   */
/* in all copies or substantial portions of the Software.                    */
/*                                                                           */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS   */
/* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF                */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.    */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY      */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT */
/* OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR  */
/* THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                */
/*                                                                           */
/* ------------------------------------------------------------------------- */

/* --------------------------------------------------------------- */
/* arm4.h - ARM4 standard header file                              */
/*                                                                 */
/* This header file defines all defines, typedefs, structures,     */
/* and API functions visible for an application which uses an ARM  */
/* agent. All compiler/platform specifics are handled in a         */
/* separate header file named <arm4os.h>.                          */
/*                                                                 */
/* NOTE: The ARM4 C language binding differs completely from       */
/* ARM1 and ARM2 bindings.                                         */
/* --------------------------------------------------------------- */

#ifndef ARM4_H_INCLUDED
#define ARM4_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ------------------------------------------------------------------------- */
/* ------------------------ basic types section ---------------------------- */
/* ------------------------------------------------------------------------- */

#define ARM4_CHAR        char 
#define ARM4_INT8        signed char 
#define ARM4_UINT8       unsigned char 
#define ARM4_INT16       short
#define ARM4_UINT16      unsigned short
#define ARM4_INT32       int
#define ARM4_UINT32      unsigned int
#define ARM4_INT64       long long
#define ARM4_UINT64      unsigned long long

#define ARM4_API_DYNAMIC(type) type

/* --------------------------------------------------------------- */
/* ---------------------- defines section ------------------------ */
/* --------------------------------------------------------------- */

/* Boolean values */
#define ARM_FALSE                               0
#define ARM_TRUE                                1

/* Transaction status */
#define ARM_STATUS_GOOD                         0
#define ARM_STATUS_ABORTED                      1
#define ARM_STATUS_FAILED                       2
#define ARM_STATUS_UNKNOWN                      3

/* -------------- reserved error codes range --------------------- */

#define ARM_ERROR_CODE_RESERVED_MIN        -20999
#define ARM_ERROR_CODE_RESERVED_MAX        -20000

/* --------------- known sub-buffer formats ---------------------- */

#define ARM_SUBBUFFER_USER                      3
#define ARM_SUBBUFFER_ARRIVAL_TIME              4
#define ARM_SUBBUFFER_METRIC_VALUES             5
#define ARM_SUBBUFFER_SYSTEM_ADDRESS            6
#define ARM_SUBBUFFER_DIAG_DETAIL               7

#define ARM_SUBBUFFER_APP_IDENTITY            102
#define ARM_SUBBUFFER_APP_CONTEXT             103
#define ARM_SUBBUFFER_TRAN_IDENTITY           104
#define ARM_SUBBUFFER_TRAN_CONTEXT            105
#define ARM_SUBBUFFER_METRIC_BINDINGS         106
#define ARM_SUBBUFFER_CHARSET                 107

/* -------------------- metric defines --------------------------- */

#define ARM_METRIC_FORMAT_RESERVED              0
#define ARM_METRIC_FORMAT_COUNTER32             1
#define ARM_METRIC_FORMAT_COUNTER64             2
#define ARM_METRIC_FORMAT_CNTRDIVR32            3
#define ARM_METRIC_FORMAT_GAUGE32               4
#define ARM_METRIC_FORMAT_GAUGE64               5
#define ARM_METRIC_FORMAT_GAUGEDIVR32           6
#define ARM_METRIC_FORMAT_NUMERICID32           7
#define ARM_METRIC_FORMAT_NUMERICID64           8
/* format 9 (string8) is deprecated */
#define ARM_METRIC_FORMAT_STRING32             10

#define ARM_METRIC_USE_GENERAL                  0
#define ARM_METRIC_USE_TRAN_SIZE                1
#define ARM_METRIC_USE_TRAN_STATUS              2

#define ARM_METRIC_MIN_ARRAY_INDEX              0
#define ARM_METRIC_MAX_ARRAY_INDEX              6
#define ARM_METRIC_MAX_COUNT                    7

#define ARM_METRIC_STRING32_MAX_CHARS          31
#define ARM_METRIC_STRING32_MAX_LENGTH \
    (ARM_METRIC_STRING32_MAX_CHARS*3+1)

/* ------------------- misc string defines ----------------------- */

#define ARM_NAME_MAX_CHARS                    127
#define ARM_NAME_MAX_LENGTH (ARM_NAME_MAX_CHARS*3+1)

#define ARM_DIAG_DETAIL_MAX_CHARS            4095
#define ARM_DIAG_DETAIL_MAX_LENGTH (ARM_DIAG_DETAIL_MAX_CHARS*3+1)

#define ARM_MSG_BUFFER_CHARS                  255
#define ARM_MSG_BUFFER_LENGTH (ARM_MSG_BUFFER_CHARS*3+1)

/* ------------------- properties defines ------------------------ */

#define ARM_PROPERTY_MIN_ARRAY_INDEX            0
#define ARM_PROPERTY_MAX_ARRAY_INDEX           19
#define ARM_PROPERTY_MAX_COUNT                 20

#define ARM_PROPERTY_NAME_MAX_CHARS (ARM_NAME_MAX_CHARS)
#define ARM_PROPERTY_NAME_MAX_LENGTH \
    (ARM_PROPERTY_NAME_MAX_CHARS*3+1)
#define ARM_PROPERTY_VALUE_MAX_CHARS          255
#define ARM_PROPERTY_VALUE_MAX_LENGTH \
    (ARM_PROPERTY_VALUE_MAX_CHARS*3+1)

#define ARM_PROPERTY_URI_MAX_CHARS           4095
#define ARM_PROPERTY_URI_MAX_LENGTH (ARM_PROPERTY_URI_MAX_CHARS*3+1)

/* -------------- system address format values ------------------- */

#define ARM_SYSADDR_FORMAT_RESERVED             0
#define ARM_SYSADDR_FORMAT_IPV4                 1
#define ARM_SYSADDR_FORMAT_IPV4PORT             2
#define ARM_SYSADDR_FORMAT_IPV6                 3
#define ARM_SYSADDR_FORMAT_IPV6PORT             4
#define ARM_SYSADDR_FORMAT_SNA                  5
#define ARM_SYSADDR_FORMAT_X25                  6
#define ARM_SYSADDR_FORMAT_HOSTNAME             7
#define ARM_SYSADDR_FORMAT_UUID                 8

/* ------------------ mandatory charsets ------------------------- */

/* IANA charset MIBenum numbers (http://www.iana.org/) */
#define ARM_CHARSET_ASCII                       3  /* mandatory */
#define ARM_CHARSET_UTF8                      106  /* mandatory */
#define ARM_CHARSET_UTF16BE                  1013
#define ARM_CHARSET_UTF16LE                  1014
    /* mandatory on Windows */
#define ARM_CHARSET_UTF16                    1015
#define ARM_CHARSET_IBM037                   2028
    /* mandatory on iSeries */
#define ARM_CHARSET_IBM1047                  2102
    /* mandatory on zSeries */

/* ------------- flags to be passed on API calls ----------------- */

/* Use ARM_FLAG_NONE instead of zero to be more readable.          */
#define ARM_FLAG_NONE                (0x00000000)

/* ARM_FLAG_TRACE_REQUEST could be used in the following calls to  */
/* request a trace:                                                */
/*   - arm_generate_correlator()                                   */
/*   - arm_start_transaction()                                     */
/*   - arm_report_transaction()                                    */
/* NOTE: The agent need not support instance tracing, so to be     */
/* sure check the generated correlator using the                   */
/* arm_get_correlator_flags() function.                            */
#define ARM_FLAG_TRACE_REQUEST       (0x00000001)

/* ARM_FLAG_BIND_THREAD could be used on arm_start_transaction()   */
/* call to do an implicit arm_bind_thread().                       */
#define ARM_FLAG_BIND_THREAD         (0x00000002)

/* ARM_FLAG_CORR_IN_PROCESS indicates that a correlator will only  */
/* be used within the process it was created. So an ARM            */
/* implementation may optimize the generation of a correlator      */
/* for that special usage. This flag can be passed to:             */
/*   - arm_generate_correlator()                                   */
/*   - arm_start_transaction()                                     */
/* NOTE: The agent need not support in-process correlation at all. */
#define ARM_FLAG_CORR_IN_PROCESS     (0x00000004)

/* --------------- correlator defines ---------------------------- */

#define ARM_CORR_MAX_LENGTH                   512
    /* total max length */

/* Correlator interface flag numbers. See                          */
/* arm_get_correlator_flags().                                     */
#define ARM_CORR_FLAGNUM_APP_TRACE              1
#define ARM_CORR_FLAGNUM_AGENT_TRACE            2


/* Use if no correlator should be provided (e.g., in               */
/* arm_start_transaction().                                        */
#define ARM_CORR_NONE ((arm_correlator_t *) NULL)

/* --- current time for arm_report_transaction() stop time ------- */

#define ARM_USE_CURRENT_TIME ((arm_stop_time_t)-1)

/* ------------------ misc defines ------------------------------- */

/* Use ARM_BUF4_NONE instead of a NULL to be more readable.        */
#define ARM_BUF4_NONE ((arm_buffer4_t*) NULL)

/* Use ARM_ID_NONE instead of a NULL to be more readable.          */
#define ARM_ID_NONE ((arm_id_t *) NULL)

/* Use ARM_STRING_NONE instead of a NULL to be more readable.      */
#define ARM_STRING_NONE ((arm_char_t *) NULL)

/* --------------------------------------------------------------- */
/* --------------- basic typedef section ------------------------- */
/* --------------------------------------------------------------- */

/* Generic data types */
/* ARM4_*INT* defines are set in the <arm4os.h> header file.       */
/* They are platform/compiler-specific.                            */
typedef ARM4_CHAR arm_char_t;

typedef ARM4_INT8 arm_int8_t;
typedef ARM4_UINT8 arm_uint8_t;
    /* used to define an opaque byte array */

typedef ARM4_INT16 arm_int16_t;
typedef ARM4_UINT16 arm_uint16_t;

typedef ARM4_INT32 arm_int32_t;
typedef ARM4_UINT32 arm_uint32_t;

typedef ARM4_INT64 arm_int64_t;
typedef ARM4_UINT64 arm_uint64_t;

/* ARM-specific simple types */
typedef arm_int32_t arm_boolean_t;
typedef arm_int32_t arm_error_t;

typedef arm_int64_t arm_arrival_time_t;  /* opaque arrival time */
typedef arm_int64_t arm_stop_time_t;  /* stop time in milli secs */
typedef arm_int64_t arm_response_time_t;
    /* response time in nano secs */

typedef arm_int32_t arm_tran_status_t;  /* ARM_TRAN_STATUS_* values */
typedef arm_int32_t arm_charset_t;  /* IANA MIBenum values */
typedef arm_int32_t arm_sysaddr_format_t;  /* ARM_SYSADDR_* values */

/* ARM string buffer types */
typedef arm_char_t arm_message_buffer_t[ARM_MSG_BUFFER_LENGTH];

/* subbuffer types */
typedef arm_int32_t arm_subbuffer_format_t;

/* metric types */
typedef arm_uint8_t arm_metric_format_t;
typedef arm_uint8_t arm_metric_slot_t;
typedef arm_int16_t arm_metric_usage_t;

/* handle types */
typedef arm_int64_t arm_app_start_handle_t;
typedef arm_int64_t arm_tran_start_handle_t;
typedef arm_int64_t arm_tran_block_handle_t;

/* correlator types */
typedef arm_int16_t arm_correlator_length_t;

/* --------------------------------------------------------------- */
/* ---------------- compound typedefs section -------------------- */
/* --------------------------------------------------------------- */
/* All IDs are 16 bytes aligned on integer boundaries for performance */
/* reasons so they can be processed as a byte array or integers       */
typedef struct arm_id
{
    union
    {
        arm_uint8_t  uint8[16];
        arm_uint32_t uint32[4];
        arm_uint64_t uint64[2];
    } id_u;
} arm_id_t;

/* Correlator */
typedef struct arm_correlator
{
    arm_uint8_t opaque[ARM_CORR_MAX_LENGTH];
} arm_correlator_t;

/* User-defined metrics */
typedef arm_int32_t arm_metric_counter32_t;
typedef arm_int64_t arm_metric_counter64_t;
typedef arm_int32_t arm_metric_divisor32_t;
typedef arm_int32_t arm_metric_gauge32_t;
typedef arm_int64_t arm_metric_gauge64_t;
typedef arm_int32_t arm_metric_numericID32_t;
typedef arm_int64_t arm_metric_numericID64_t;
typedef const arm_char_t *arm_metric_string32_t;
typedef struct arm_metric_cntrdivr32
{
    arm_metric_counter32_t counter;
    arm_metric_divisor32_t divisor;
} arm_metric_cntrdivr32_t;
typedef struct arm_metric_gaugedivr32
{
    arm_metric_gauge32_t gauge;
    arm_metric_divisor32_t divisor;
} arm_metric_gaugedivr32_t;

typedef struct arm_metric
{
    arm_metric_slot_t slot;
    arm_metric_format_t format;
    arm_metric_usage_t usage;
    arm_boolean_t valid;
    union
    {
        arm_metric_counter32_t counter32;
        arm_metric_counter64_t counter64;
        arm_metric_cntrdivr32_t counterdivisor32;
        arm_metric_gauge32_t gauge32;
        arm_metric_gauge64_t gauge64;
        arm_metric_gaugedivr32_t gaugedivisor32;
        arm_metric_numericID32_t numericid32;
        arm_metric_numericID64_t numericid64;
        arm_metric_string32_t string32;
    } metric_u;
} arm_metric_t;

typedef struct arm_metric_binding
{
    arm_metric_slot_t slot;
    arm_id_t id;
} arm_metric_binding_t;

typedef struct arm_property
{
    const arm_char_t *name;
    const arm_char_t *value;
} arm_property_t;

/* ------------------------------------------------------------- */
/* -------------- sub-buffer typedefs section ------------------ */
/* ------------------------------------------------------------- */

typedef struct arm_subbuffer {
    arm_subbuffer_format_t format;
    /* Format-specific data fields follow here. */
} arm_subbuffer_t;

/* This macro could be used avoid a compiler warning if you      */
/* direct one of the following arm_subbuffer_*_t structure       */
/* pointers to a function accepting sub-buffer pointers. Any     */
/* sub-buffer is passed to the ARM API call as a                 */
/* (arm_subbuffer_t *) pointer. Use this macro if you pass a     */
/* "real" subbuffer to an API function. Note for the special     */
/* ARM SDK subbuffers the ARM_SDKSB() macro has to be used.      */
#define ARM_SB(x)  (&((x).header))

/* The user data buffer */
typedef struct arm_buffer4
{
    arm_int32_t count;
    arm_subbuffer_t **subbuffer_array;
} arm_buffer4_t;

typedef struct arm_subbuffer_charset
{
    arm_subbuffer_t header;  /* ARM_SUBBUFFER_CHARSET */

    arm_charset_t charset;  /* One of the IANA MIBenum values */
    arm_int32_t flags;
} arm_subbuffer_charset_t;

typedef struct arm_subbuffer_app_identity
{
    arm_subbuffer_t header;  /* ARM_SUBBUFFER_APP_IDENTITY */

    arm_int32_t identity_property_count;
    const arm_property_t *identity_property_array;
    arm_int32_t context_name_count;
    const arm_char_t **context_name_array;
} arm_subbuffer_app_identity_t;

typedef struct arm_subbuffer_app_context
{
    arm_subbuffer_t header;  /* ARM_SUBBUFFER_APP_CONTEXT */

    arm_int32_t context_value_count;
    const arm_char_t **context_value_array;
} arm_subbuffer_app_context_t;

typedef struct arm_subbuffer_tran_identity
{
    arm_subbuffer_t header;  /* ARM_SUBBUFFER_TRAN_IDENTITY */

    arm_int32_t identity_property_count;
    const arm_property_t *identity_property_array;
    arm_int32_t context_name_count;
    const arm_char_t **context_name_array;
    const arm_char_t *uri;
} arm_subbuffer_tran_identity_t;

typedef struct arm_subbuffer_tran_context
{
    arm_subbuffer_t header;  /* ARM_SUBBUFFER_TRAN_CONTEXT */

    arm_int32_t context_value_count;
    const arm_char_t **context_value_array;
    const arm_char_t *uri;
} arm_subbuffer_tran_context_t;

typedef struct arm_subbuffer_arrival_time
{
    arm_subbuffer_t header;  /* ARM_SUBBUFFER_ARRIVAL_TIME */

    arm_arrival_time_t opaque_time;
} arm_subbuffer_arrival_time_t;

typedef struct arm_subbuffer_metric_bindings
{
    arm_subbuffer_t header;  /* ARM_SUBBUFFER_METRIC_BINDINGS */

    arm_int32_t count;
    const arm_metric_binding_t *metric_binding_array;
} arm_subbuffer_metric_bindings_t;

typedef struct arm_subbuffer_metric_values
{
    arm_subbuffer_t header;  /* ARM_SUBBUFFER_METRIC_VALUES */

    arm_int32_t count;
    const arm_metric_t *metric_value_array;
} arm_subbuffer_metric_values_t;

typedef struct arm_subbuffer_user
{
    arm_subbuffer_t header;  /* ARM_SUBBUFFER_USER */

    const arm_char_t *name;
    arm_boolean_t id_valid;
    arm_id_t id;
} arm_subbuffer_user_t;

typedef struct arm_subbuffer_system_address
{
    arm_subbuffer_t header;  /* ARM_SUBBUFFER_SYSTEM_ADDRESS */

    arm_int16_t address_format;
    arm_int16_t address_length;
    const arm_uint8_t *address;
    arm_boolean_t id_valid;
    arm_id_t id;
} arm_subbuffer_system_address_t;

typedef struct arm_subbuffer_diag_detail
{
    arm_subbuffer_t header;  /* ARM_SUBBUFFER_DIAG_DETAIL */

    const arm_char_t *diag_detail;
} arm_subbuffer_diag_detail_t;

/* --------------------------------------------------------------- */
/* ------------------ ARM4 API section --------------------------- */
/* --------------------------------------------------------------- */

/* register metadata API functions */
ARM4_API_DYNAMIC(arm_error_t)
arm_register_application(
    const arm_char_t *app_name,
    const arm_id_t *input_app_id,
    const arm_int32_t flags,
    const arm_buffer4_t *buffer4,
    arm_id_t *output_app_id);

ARM4_API_DYNAMIC(arm_error_t)
arm_destroy_application(
    const arm_id_t *app_id,
    const arm_int32_t flags,
    const arm_buffer4_t *buffer4);

ARM4_API_DYNAMIC(arm_error_t)
arm_register_transaction(
    const arm_id_t *app_id,
    const arm_char_t *tran_name,
    const arm_id_t *input_tran_id,
    const arm_int32_t flags,
    const arm_buffer4_t *buffer4,
    arm_id_t *output_tran_id);

ARM4_API_DYNAMIC(arm_error_t)
arm_register_metric(
    const arm_id_t *app_id,
    const arm_char_t *metric_name,
    const arm_metric_format_t metric_format,
    const arm_metric_usage_t metric_usage,
    const arm_char_t *metric_unit,
    const arm_id_t *input_metric_id,
    const arm_int32_t flags,
    const arm_buffer4_t *buffer4,
    arm_id_t *output_metric_id);

/* application instance API functions */
ARM4_API_DYNAMIC(arm_error_t)
arm_start_application(
    const arm_id_t *app_id,
    const arm_char_t *app_group,
    const arm_char_t *app_instance,
    const arm_int32_t flags,
    const arm_buffer4_t *buffer4,
    arm_app_start_handle_t *app_handle);

ARM4_API_DYNAMIC(arm_error_t)
arm_stop_application(
    const arm_app_start_handle_t app_handle,
    const arm_int32_t flags,
    const arm_buffer4_t *buffer4);

/* transaction instance API functions */
ARM4_API_DYNAMIC(arm_error_t)
arm_start_transaction(
    const arm_app_start_handle_t app_handle,
    const arm_id_t *tran_id,
    const arm_correlator_t *parent_correlator,
    const arm_int32_t flags,
    const arm_buffer4_t *buffer4,
    arm_tran_start_handle_t *tran_handle,
    arm_correlator_t *current_correlator);

ARM4_API_DYNAMIC(arm_error_t)
arm_stop_transaction(
    const arm_tran_start_handle_t tran_handle,
    const arm_tran_status_t tran_status,
    const arm_int32_t flags,
    const arm_buffer4_t *buffer4);

ARM4_API_DYNAMIC(arm_error_t)
arm_update_transaction(
    const arm_tran_start_handle_t tran_handle,
    const arm_int32_t flags,
    const arm_buffer4_t *buffer4);

ARM4_API_DYNAMIC(arm_error_t)
arm_discard_transaction(
    const arm_tran_start_handle_t tran_handle,
    const arm_int32_t flags,
    const arm_buffer4_t *buffer4);

ARM4_API_DYNAMIC(arm_error_t)
arm_block_transaction(
    const arm_tran_start_handle_t tran_handle,
    const arm_int32_t flags,
    const arm_buffer4_t *buffer4,
    arm_tran_block_handle_t *block_handle);

ARM4_API_DYNAMIC(arm_error_t)
arm_unblock_transaction(
    const arm_tran_start_handle_t tran_handle,
    const arm_tran_block_handle_t block_handle,
    const arm_int32_t flags,
    const arm_buffer4_t *buffer4);

/* thread support API functions */
ARM4_API_DYNAMIC(arm_error_t)
arm_bind_thread(
    const arm_tran_start_handle_t tran_handle,
    const arm_int32_t flags,
    const arm_buffer4_t *buffer4);

ARM4_API_DYNAMIC(arm_error_t)
arm_unbind_thread(
    const arm_tran_start_handle_t tran_handle,
    const arm_int32_t flags,
    const arm_buffer4_t *buffer4);

/* report transaction data API function */
ARM4_API_DYNAMIC(arm_error_t)
arm_report_transaction(
    const arm_app_start_handle_t app_handle,
    const arm_id_t *tran_id,
    const arm_tran_status_t tran_status,
    const arm_response_time_t response_time,
    const arm_stop_time_t stop_time,
    const arm_correlator_t *parent_correlator,
    const arm_correlator_t *current_correlator,
    const arm_int32_t flags,
    const arm_buffer4_t *buffer4);

/* correlator API functions */
ARM4_API_DYNAMIC(arm_error_t)
arm_generate_correlator(
    const arm_app_start_handle_t app_handle,
    const arm_id_t *tran_id,
    const arm_correlator_t *parent_correlator,
    const arm_int32_t flags,
    const arm_buffer4_t *buffer4,
    arm_correlator_t *current_correlator);

ARM4_API_DYNAMIC(arm_error_t)
arm_get_correlator_length(
    const arm_correlator_t *correlator,
    arm_correlator_length_t *length);

ARM4_API_DYNAMIC(arm_error_t)
arm_get_correlator_flags(
    const arm_correlator_t *correlator,
    const arm_int32_t corr_flag_num,
    arm_boolean_t *flag);

/* miscellaneous API functions */
ARM4_API_DYNAMIC(arm_error_t)
arm_get_arrival_time(
    arm_arrival_time_t *opaque_time);

ARM4_API_DYNAMIC(arm_error_t)
arm_get_error_message(
    const arm_charset_t charset,
    const arm_error_t code, 
    arm_message_buffer_t msg);

ARM4_API_DYNAMIC(arm_error_t)
arm_is_charset_supported(
    const arm_charset_t charset,
    arm_boolean_t *supported);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ARM4_H_INCLUDED */

