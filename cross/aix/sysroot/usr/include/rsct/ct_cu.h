/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2000,2009          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/*===========================================================================*/
/*                                                                           */
/* Module Name:  ct_cu.h                                                     */
/*                                                                           */
/* Description:                                                              */
/*     Interface definitions for the Cluster Utilities.                      */
/*                                                                           */
/*     This file is formatted to be viewed with tab stops set to 4.          */
/*===========================================================================*/
/* sccsid = "@(#)71   1.93   src/rsct/utils/ct_cu.h, common_utils, rsct_rhay53, rhay531006a 9/30/09 10:04:31"; */

#ifndef _H_CT_CU
#define _H_CT_CU

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>
#include <limits.h>
#include <float.h>
#include <rsct/ct.h>
#include <stdarg.h>
#include <unistd.h>
#ifdef __linux__
#define __need_timespec
#include <time.h>
#endif    
#include <iconv.h>
#include <locale.h>
#include <nl_types.h>
#include <langinfo.h>
#include <inttypes.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <stdlib.h>

/*---------------------------------------------------------------------------*/
/*  Cluster Utilities API constants.                                         */
/*---------------------------------------------------------------------------*/

/*
 *  CU_VERSION identifies the version of the Cluster Utilities Application
 *  Programming Interface desired by a client.  If the client has not
 *  specified a particular version, version 1 is used.
 */

#ifndef CU_VERSION
#define CU_VERSION           1
#endif  /* CU_VERSION */

/*	Error code definitions	*/

#define CU_EFAILURE          1
#define CU_EINVALIDNAME      2
#define CU_ENOMEM            3
#define CU_EINVAL            4
#define CU_EDIVIDEZERO       5
#define CU_EINVALIDSDINDEX   6
#define CU_EINVALIDINDEX     7
#define CU_EINVALIDELEMENTID 8
#define CU_EINVALIDOPTION    9
#define CU_EMISSINGFUNC      10
#define CU_ENOEXPR           11
#define CU_ETOOFEWVALUES     12
#define CU_EINVALIDRANGE     13
#define CU_EINVALIDFORMAT    14
#define CU_EVARCONFLICT      15

/*	Error code definitions for cu_iconv_* routines	*/

#define CU_ECONVNOMEM		 15	  /* Required memory could not be allocated	  */
#define CU_ECONVAGAIN		 16	  /* Some system resource is not available	  */
#define CU_ECONVINVALID		 17	  /* Invalid call or argments				  */
#define CU_ECONVNOSUPPORT	 18	  /* Codeset conversion not supported		  */
#define CU_ECONVBADINPUT	 19	  /* Codeset conv failed: bad input	string	  */
#define CU_ECONVBUFFERSIZE	 20	  /* Codeset conv failed: small output buffer */
#define CU_ECONVESCAPESEQ	 24	  /* Codeset conv failed: escape sequence	  */
								  /*   ... found or required, but not allowed */

/*	Error code definitions for cu_get_locale_info() routine	*/

#define CU_ELOCALENOMEM		 21	  /* Required memory could not be allocated	  */
#define CU_ELOCALEAGAIN		 22	  /* Some system resource is not available	  */
#define CU_ELOCALEFAILURE	 23	  /* Unexpected failure getting locale info.  */

/*
 *  Error code definitions for cu_validate_specific_node_id(),
 *  cu_set_specific_node_id(), cu_set_node_id(), and cu_get_node_id()
 *  routines.
 */

#define CU_ENODEIDINVALID	 40	  /* Specified node id invalid				  */
								  /*    (validate_specific/set_specific)	  */
#define CU_ENODEIDGENERATE	 25	  /* Could not generate a node id (set)		  */
#define CU_ENODEIDALREADY	 26	  /* Machine already has id (set_specific/set)*/
#define CU_ENODEIDMISSING	 27	  /* The machine does not have a node id (get)*/
#define CU_ENODEIDMISMATCH	 28	  /* Saved node ids do not match (get)		  */
#define CU_ENODEIDOTHER		 29	  /* Some other error (set_specific/set/get)  */

/* Error code definitions for cu_get_cdef_info() routines                     */
#define CU_ECDEFNOENT        30   /* Class def file does not exist            */
#define CU_ECDEFOTHER        31   /* Some other error -- errno provided in msg*/
#define CU_ECDEFCORRUPT      32   /* Class def file is corrupted              */
#define CU_ECDEFINVALID      33   /* Class def file is not single class def   */

/*
 *	Error code definitions for cu_gethostbyname() and cu_gethostbyaddr().
 *
 *  Note the correspondence between these error codes and the error codes
 *  set in h_errno by gethostbyname() and gethostbyaddr():
 *
 *      CU_EHOSTNOTFOUND	HOST_NOT_FOUND
 *      CU_EHOSTNODATA		NO_DATA
 *      CU_EHOSTTRYAGAIN	TRY_AGAIN
 *      CU_HOSTNORECOVERY	NO_RECOVERY
 */

#define CU_EHOSTNOTFOUND	 34	  /* No such host is known					  */
#define CU_EHOSTNODATA		 35	  /* No address is available				  */
#define CU_EHOSTTRYAGAIN	 36	  /* A temporary error occurred				  */
#define CU_EHOSTNORECOVERY	 37	  /* An unexpected server failure occurred	  */
#define CU_EHOSTNOMEM		 38	  /* Required memory could not be allocated	  */
#define CU_EHOSTOTHER		 39	  /* Some other error occurred				  */
    
/*
 *  Note: The next available error number is not 40.  CU_ENODEIDINVALID is
 *        assigned to 40.  The next available error number is 41.
 */

/*
 *  Include definitions for cu_get_proc_xxx functions.  This is temporary until
 *  the users of cu_get_proc_info() can be changed to include ct_cu_proc.h.
 */
#include <rsct/ct_cu_proc.h>

/*
 *  The following macros convert references to the generic names of CUAPI
 *  routines, like cu_rsrc_is_dependent(), to references to version specific
 *  CUAPI routines, like cu_rsrc_is_dependent_1(). The version used during
 *  conversion is determined by the value of CU_VERSION.  Note that these
 *  macros can deal with the different versions of a routine having different
 *  arguments.
 */

#define cu_rsrc_is_fixed                                                \
	CU_ROUTINE_VERSION(cu_rsrc_is_fixed, CU_VERSION)

#define cu_rsrc_hndl_has_node_id                                        \
	CU_ROUTINE_VERSION(cu_rsrc_hndl_has_node_id, CU_VERSION)

#define cu_get_resource_location                                        \
	CU_ROUTINE_VERSION(cu_get_resource_location, CU_VERSION)

#define cu_set_resource_location                                        \
	CU_ROUTINE_VERSION(cu_set_resource_location, CU_VERSION)

#define cu_get_resource_node_id                                         \
	CU_ROUTINE_VERSION(cu_get_resource_node_id, CU_VERSION)

#define cu_set_resource_node_id                                         \
	CU_ROUTINE_VERSION(cu_set_resource_node_id, CU_VERSION)

#define cu_get_resource_id                                              \
	CU_ROUTINE_VERSION(cu_get_resource_id, CU_VERSION)

#define cu_get_resource_id_ext                                          \
	CU_ROUTINE_VERSION(cu_get_resource_id_ext, CU_VERSION)

#define cu_get_resource_class_id                                        \
	CU_ROUTINE_VERSION(cu_get_resource_class_id, CU_VERSION)

#define cu_gen_resource_handle                                          \
	CU_ROUTINE_VERSION(cu_gen_resource_handle, CU_VERSION)

#define cu_gen_resource_handle_ext                                      \
	CU_ROUTINE_VERSION(cu_gen_resource_handle_ext, CU_VERSION)

#define cu_mk_resource_handle                                           \
	CU_ROUTINE_VERSION(cu_mk_resource_handle, CU_VERSION)
	
#define cu_mk_resource_handle_pd                                        \
	CU_ROUTINE_VERSION(cu_mk_resource_handle_pd, CU_VERSION)
	
#define cu_mk_resource_handle_icid                                      \
	CU_ROUTINE_VERSION(cu_mk_resource_handle_icid, CU_VERSION)
	
#define cu_rsrcs_are_same                                               \
	CU_ROUTINE_VERSION(cu_rsrcs_are_same, CU_VERSION)

#define cu_rsrc_hndl_cmp                                                \
	CU_ROUTINE_VERSION(cu_rsrc_hndl_cmp, CU_VERSION)

#define cu_get_canon_hndl                                               \
	CU_ROUTINE_VERSION(cu_get_canon_hndl, CU_VERSION)

#define cu_set_no_error                                                 \
	CU_ROUTINE_VERSION(cu_set_no_error, CU_VERSION)

#define cu_set_error                                                    \
	CU_ROUTINE_VERSION(cu_set_error, CU_VERSION)

#define cu_vset_error                                                   \
	CU_ROUTINE_VERSION(cu_vset_error, CU_VERSION)

#define cu_pset_error                                                   \
	CU_ROUTINE_VERSION(cu_pset_error, CU_VERSION)

#define cu_get_error                                                    \
	CU_ROUTINE_VERSION(cu_get_error, CU_VERSION)

#define cu_pkg_no_error                                                 \
	CU_ROUTINE_VERSION(cu_pkg_no_error, CU_VERSION)

#define cu_pkg_error                                                    \
	CU_ROUTINE_VERSION(cu_pkg_error, CU_VERSION)

#define cu_vpkg_error                                                   \
	CU_ROUTINE_VERSION(cu_vpkg_error, CU_VERSION)

#define cu_apkg_error                                                   \
	CU_ROUTINE_VERSION(cu_apkg_error, CU_VERSION)

#define cu_dup_error                                                    \
	CU_ROUTINE_VERSION(cu_dup_error, CU_VERSION)

#define cu_rel_error                                                    \
	CU_ROUTINE_VERSION(cu_rel_error, CU_VERSION)

#define cu_get_errmsg                                                   \
	CU_ROUTINE_VERSION(cu_get_errmsg, CU_VERSION)

#define cu_fmt_errmsg                                                   \
	CU_ROUTINE_VERSION(cu_fmt_errmsg, CU_VERSION)

#define cu_fmt_msg                                                      \
	CU_ROUTINE_VERSION(cu_fmt_msg, CU_VERSION)     

#define cu_rel_errmsg                                                   \
	CU_ROUTINE_VERSION(cu_rel_errmsg, CU_VERSION)

#define cu_set_error_args                                               \
	CU_ROUTINE_VERSION(cu_set_error_args, CU_VERSION)

#define cu_rel_error_args                                               \
	CU_ROUTINE_VERSION(cu_rel_error_args, CU_VERSION)

#define cu_get_cluster_info												\
	CU_ROUTINE_VERSION(cu_get_cluster_info, CU_VERSION)

#define cu_get_tsgs_cluster_info										\
	CU_ROUTINE_VERSION(cu_get_tsgs_cluster_info, CU_VERSION)

#define cu_get_registry_server_list										\
	CU_ROUTINE_VERSION(cu_get_registry_server_list, CU_VERSION)

#define cu_free_registry_server_list									\
	CU_ROUTINE_VERSION(cu_free_registry_server_list, CU_VERSION)

#define cu_get_cluster_ID                                               \
    CU_ROUTINE_VERSION(cu_get_cluster_ID, CU_VERSION)

#define cu_get_node_number                                              \
    CU_ROUTINE_VERSION(cu_get_node_number, CU_VERSION)

#define cu_gen_rsrc_ids_init                                            \
    CU_ROUTINE_VERSION(cu_gen_rsrc_ids_init, CU_VERSION)

#define cu_gen_rsrc_ids                                                 \
    CU_ROUTINE_VERSION(cu_gen_rsrc_ids, CU_VERSION)

#define cu_gen_rsrc_ids_for_specified_node                              \
    CU_ROUTINE_VERSION(cu_gen_rsrc_ids_for_specified_node, CU_VERSION)

#define cu_gen_rsrc_ids_with_icid                                       \
    CU_ROUTINE_VERSION(cu_gen_rsrc_ids_with_icid, CU_VERSION)

#define cu_rsrc_id_to_string                                            \
    CU_ROUTINE_VERSION(cu_rsrc_id_to_string, CU_VERSION)

#define cu_rsrc_id_from_string                                          \
    CU_ROUTINE_VERSION(cu_rsrc_id_from_string, CU_VERSION)

#define cu_get_hwid                                                     \
    CU_ROUTINE_VERSION(cu_get_hwid, CU_VERSION)

#define cu_validate_specific_node_id                                    \
    CU_ROUTINE_VERSION(cu_validate_specific_node_id, CU_VERSION)

#define cu_set_specific_node_id                                         \
    CU_ROUTINE_VERSION(cu_set_specific_node_id, CU_VERSION)

#define cu_set_node_id                                                  \
    CU_ROUTINE_VERSION(cu_set_node_id, CU_VERSION)

#define cu_get_node_id                                                  \
    CU_ROUTINE_VERSION(cu_get_node_id, CU_VERSION)

#define cu_get_procspeed                                                \
    CU_ROUTINE_VERSION(cu_get_procspeed, CU_VERSION)

#define cu_compute_base_timeinfo										\
    CU_ROUTINE_VERSION(cu_compute_base_timeinfo, CU_VERSION)

#define cu_get_ctr                                                      \
    CU_ROUTINE_VERSION(cu_get_ctr, CU_VERSION)

#define cu_cvt_time                                                     \
    CU_ROUTINE_VERSION(cu_cvt_time, CU_VERSION)

#define cu_get_monotonic_time											\
    CU_ROUTINE_VERSION(cu_get_monotonic_time, CU_VERSION)

#define cu_gettimeofday													\
    CU_ROUTINE_VERSION(cu_gettimeofday, CU_VERSION)

#define cu_get_current_time												\
    CU_ROUTINE_VERSION(cu_get_current_time, CU_VERSION)

#define cu_force_iconv_single_threaded									\
    CU_ROUTINE_VERSION(cu_force_iconv_single_threaded, CU_VERSION)

#define cu_iconv_open													\
    CU_ROUTINE_VERSION(cu_iconv_open, CU_VERSION)

#define cu_iconv_dup													\
    CU_ROUTINE_VERSION(cu_iconv_dup, CU_VERSION)

#define cu_iconv_close													\
    CU_ROUTINE_VERSION(cu_iconv_close, CU_VERSION)

#define cu_iconv_str													\
    CU_ROUTINE_VERSION(cu_iconv_str, CU_VERSION)

#define cu_iconv_buf													\
    CU_ROUTINE_VERSION(cu_iconv_buf, CU_VERSION)

#define cu_iconv_intermediate_codeset									\
    CU_ROUTINE_VERSION(cu_iconv_intermediate_codeset, CU_VERSION)

#define cu_iconv_get_cntrs												\
    CU_ROUTINE_VERSION(cu_iconv_get_cntrs, CU_VERSION)

#define cu_iconv_rel_cntrs												\
    CU_ROUTINE_VERSION(cu_iconv_rel_cntrs, CU_VERSION)

#define cu_get_locale_info												\
    CU_ROUTINE_VERSION(cu_get_locale_info, CU_VERSION)

#define cu_rel_locale_info												\
    CU_ROUTINE_VERSION(cu_rel_locale_info, CU_VERSION)

#define cu_get_utf8_locale												\
    CU_ROUTINE_VERSION(cu_get_utf8_locale, CU_VERSION)

#define cu_rel_utf8_locale												\
    CU_ROUTINE_VERSION(cu_rel_utf8_locale, CU_VERSION)

#define cu_assume_utf8													\
    CU_ROUTINE_VERSION(cu_assume_utf8, CU_VERSION)

#define cu_utf8_is_assumed												\
    CU_ROUTINE_VERSION(cu_utf8_is_assumed, CU_VERSION)

#define cu_do_not_modify_utf8											\
    CU_ROUTINE_VERSION(cu_do_not_modify_utf8, CU_VERSION)

#define cu_utf8_is_not_modified											\
    CU_ROUTINE_VERSION(cu_utf8_is_not_modified, CU_VERSION)

#define cu_limit_utf8_to_bmp											\
    CU_ROUTINE_VERSION(cu_limit_utf8_to_bmp, CU_VERSION)

#define cu_utf8_is_limited_to_bmp										\
    CU_ROUTINE_VERSION(cu_utf8_is_limited_to_bmp, CU_VERSION)

#define cu_strcasecmp_posix												\
	CU_ROUTINE_VERSION(cu_strcasecmp_posix, CU_VERSION)

#define cu_utf8_strcasecmp_posix										\
	CU_ROUTINE_VERSION(cu_utf8_strcasecmp_posix, CU_VERSION)

#define cu_cset_strcasecmp_posix										\
	CU_ROUTINE_VERSION(cu_cset_strcasecmp_posix, CU_VERSION)

#define cu_8bit_strcasecmp_posix										\
	CU_ROUTINE_VERSION(cu_8bit_strcasecmp_posix, CU_VERSION)

#define cu_strncasecmp_posix											\
	CU_ROUTINE_VERSION(cu_strncasecmp_posix, CU_VERSION)

#define cu_utf8_strncasecmp_posix										\
	CU_ROUTINE_VERSION(cu_utf8_strncasecmp_posix, CU_VERSION)

#define cu_cset_strncasecmp_posix										\
	CU_ROUTINE_VERSION(cu_cset_strncasecmp_posix, CU_VERSION)

#define cu_8bit_strncasecmp_posix										\
	CU_ROUTINE_VERSION(cu_8bit_strncasecmp_posix, CU_VERSION)

#define cu_tolower_posix												\
	CU_ROUTINE_VERSION(cu_tolower_posix, CU_VERSION)

#define cu_toupper_posix												\
	CU_ROUTINE_VERSION(cu_toupper_posix, CU_VERSION)

#define cu_utf8_mblen													\
	CU_ROUTINE_VERSION(cu_utf8_mblen, CU_VERSION)

#define cu_prepare_locale												\
    CU_ROUTINE_VERSION(cu_prepare_locale, CU_VERSION)

#define cu_catopen														\
    CU_ROUTINE_VERSION(cu_catopen, CU_VERSION)
    
#define cu_dtc_table                                                    \
    CU_ROUTINE_VERSION(cu_dtc_table, CU_VERSION)

#define cu_dtc_base_types                                               \
    CU_ROUTINE_VERSION(cu_dtc_base_types, CU_VERSION)

#define cu_get_cdef_info                                                \
    CU_ROUTINE_VERSION(cu_get_cdef_info, CU_VERSION)

#define cu_get_version                                                  \
    CU_ROUTINE_VERSION(cu_get_version, CU_VERSION)

#define cu_cmp_rsct_versions											\
    CU_ROUTINE_VERSION(cu_cmp_rsct_versions, CU_VERSION)

#define cu_gethostbyname												\
    CU_ROUTINE_VERSION(cu_gethostbyname, CU_VERSION)

#define cu_gethostbyaddr												\
    CU_ROUTINE_VERSION(cu_gethostbyaddr, CU_VERSION)

#define cu_getaddrinfo													\
    CU_ROUTINE_VERSION(cu_getaddrinfo, CU_VERSION)

#define cu_getnameinfo													\
    CU_ROUTINE_VERSION(cu_getnameinfo, CU_VERSION)

#define cu_ipaddr_ntop													\
    CU_ROUTINE_VERSION(cu_ipaddr_ntop, CU_VERSION)

#define cu_ipaddr_pton													\
    CU_ROUTINE_VERSION(cu_ipaddr_pton, CU_VERSION)

#define cu_pick_thread_stacksize                                        \
    CU_ROUTINE_VERSION(cu_pick_thread_stacksize, CU_VERSION)

#define cu_check_crit_rsrc_meth											\
   CU_ROUTINE_VERSION(cu_check_crit_rsrc_meth, CU_VERSION)

#define cu_protect_crit_rsrc											\
   CU_ROUTINE_VERSION(cu_protect_crit_rsrc, CU_VERSION)
    
#define cu_getadmin_group_id                                            \
   CU_ROUTINE_VERSION(cu_getadmin_group_id, CU_VERSION)

#define cu_get_clusters_info											\
	CU_ROUTINE_VERSION(cu_get_clusters_info, CU_VERSION)

#define cu_is_sys_wpar											\
	CU_ROUTINE_VERSION(cu_is_sys_wpar, CU_VERSION)

#define CU_ROUTINE_VERSION(routine, version)                            \
    CU_ROUTINE_VERSION_GLUE(routine, version)

#define CU_ROUTINE_VERSION_GLUE(routine, version)                       \
    routine ## _ ## version

/*---------------------------------------------------------------------------*/
/*  Cluster Utilities data type characteristics.                             */
/*                                                                           */
/*  The following macros are used to determine the characteristics of the    */
/*  various data types enumerated in ct_data_type_t (see ct.h)               */
/*---------------------------------------------------------------------------*/

/* Define a Data Type Characteristic Bit for each characteristic a data type
 * may have
 */

#define CU_DTCB_REG			0x0001	/* data type supported by Registry    */
#define CU_DTCB_RMC			0x0002	/* data type supported by RMC         */
#define CU_DTCB_PTR			0x0004	/* value is actually a pointer to     */
									/*    the data type                   */
#define CU_DTCB_CMPCT		0x0008	/* referenced data type is guaranteed */
									/*    contiguous in memory            */
#define CU_DTCB_ARRAY		0x0010	/* data type is an array type         */
#define CU_DTCB_NUM			0x0020	/* data type is a simple numeric type */
#define CU_DTCB_NUM_ARRAY	0x0040	/* data type is an array type with a  */
									/*    base type that is numeric       */

#if (CU_VERSION == 1)

/* The characteristics of each data type are:
 *
 * CT_NONE					=> CU_DTCB_RMC
 *
 * CT_INT32					=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_NUM
 *
 * CT_UINT32				=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_NUM
 *
 * CT_INT64					=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_NUM
 *
 * CT_UINT64				=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_NUM
 *
 * CT_FLOAT32				=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_NUM
 *
 * CT_FLOAT64				=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_NUM
 *
 * CT_CHAR_PTR				=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_PTR,CU_DTCB_CMPCT
 *
 * CT_BINARY_PTR			=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_PTR,CU_DTCB_CMPCT
 *
 * CT_RSRC_HANDLE_PTR		=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_PTR,CU_DTCB_CMPCT
 *
 * CT_SD_PTR				=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_PTR
 *
 * CT_SBS_PTR				=> CU_DTCB_PTR,CU_DTCB_CMPCT
 *
 * CT_INT32_ARRAY			=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_PTR,
 *							   CU_DTCB_CMPCT,CU_DTCB_ARRAY,CU_DTCB_NUM_ARRAY
 *
 * CT_UINT32_ARRAY			=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_PTR,
 *							   CU_DTCB_CMPCT,CU_DTCB_ARRAY,CU_DTCB_NUM_ARRAY
 *
 * CT_INT64_ARRAY			=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_PTR,
 *							   CU_DTCB_CMPCT,CU_DTCB_ARRAY,CU_DTCB_NUM_ARRAY
 *
 * CT_UINT64_ARRAY			=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_PTR,
 *							   CU_DTCB_CMPCT,CU_DTCB_ARRAY,CU_DTCB_NUM_ARRAY
 *
 * CT_FLOAT32_ARRAY			=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_PTR,
 *							   CU_DTCB_CMPCT,CU_DTCB_ARRAY,CU_DTCB_NUM_ARRAY
 *
 * CT_FLOAT64_ARRAY			=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_PTR,
 *							   CU_DTCB_CMPCT,CU_DTCB_ARRAY,CU_DTCB_NUM_ARRAY
 *
 * CT_CHAR_PTR_ARRAY		=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_PTR,CU_DTCB_ARRAY
 *
 * CT_BINARY_PTR_ARRAY		=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_PTR,CU_DTCB_ARRAY
 *
 * CT_RSRC_HANDLE_PTR_ARRAY	=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_PTR,CU_DTCB_ARRAY
 *
 * CT_SD_PTR_ARRAY			=> CU_DTCB_REG,CU_DTCB_RMC,CU_DTCB_PTR,CU_DTCB_ARRAY
 *
 */

/* define macros to determine the characteristics of a data type. The argument
 * to each macro is the enumerated type value from ct_data_type_t. Each
 * macro is an expression that is either TRUE or FALSE.
 */

extern ct_uint16_t cu_dtc_table[];

#define CU_DT_IS_VALID(t)			(t && t <= CT_SD_PTR_ARRAY)

#define CU_DT_IS_REGISTRY(t)		(t <= CT_SD_PTR_ARRAY && \
										cu_dtc_table[t] & CU_DTCB_REG)

#define CU_DT_IS_RMC(t)				(t <= CT_SD_PTR_ARRAY && \
										cu_dtc_table[t] & CU_DTCB_RMC)

#define CU_DT_IS_REG_RMC(t)			(t <= CT_SD_PTR_ARRAY && \
										cu_dtc_table[t] & CU_DTCB_REG && \
										cu_dtc_table[t] & CU_DTCB_RMC)

#define CU_DT_IS_POINTER(t)			(t <= CT_SD_PTR_ARRAY && \
										cu_dtc_table[t] & CU_DTCB_PTR)

#define CU_DT_IS_COMPACT(t)			(t <= CT_SD_PTR_ARRAY && \
										cu_dtc_table[t] & CU_DTCB_CMPCT)

#define CU_DT_IS_ARRAY(t)			(t <= CT_SD_PTR_ARRAY && \
										cu_dtc_table[t] & CU_DTCB_ARRAY)

#define CU_DT_IS_NUMERIC(t)			(t <= CT_SD_PTR_ARRAY && \
										cu_dtc_table[t] & CU_DTCB_NUM)

#define CU_DT_IS_NUMERIC_ARRAY(t)	(t <= CT_SD_PTR_ARRAY && \
										cu_dtc_table[t] & CU_DTCB_NUM_ARRAY)

/*
 *  Define a macro that returns for each array data type defined in the
 *  ct_data_type_t enumeration the data type of the array's elements.
 *  The macro returns CT_UNKNOWN for data types that are not array data types.
 */

extern ct_data_type_t cu_dtc_base_types[];

#define CU_DT_BASE_TYPE(t)		( (t <= CT_SD_PTR_ARRAY)					\
										? cu_dtc_base_types[t]				\
										: CT_UNKNOWN						\
								)

#endif /* (CU_VERSION == 1) */
	
/*---------------------------------------------------------------------------*/
/*  Cluster Utilities data type empty or invalid values.                     */
/*                                                                           */
/*  The following macros define pointers to empty or invalid values          */
/*  for pointer data types enumerated in ct_data_type_t (see ct.h)           */
/*---------------------------------------------------------------------------*/

#if (CU_VERSION == 1) || defined(CU_ALL_VERSIONS)

extern ct_char_t				*cu_ptr_empty_char_1;
extern ct_binary_t				*cu_ptr_empty_binary_1;
extern ct_sbs_t					*cu_ptr_empty_sbs_1;
extern ct_structured_data_t		*cu_ptr_empty_sd_1;
extern ct_array_t				*cu_ptr_empty_array_1;
extern ct_resource_handle_t		*cu_ptr_invld_rsrc_hndl_1;

#define CU_PTR_EMPTY_CHAR		 cu_ptr_empty_char_1
#define CU_PTR_EMPTY_BINARY		 cu_ptr_empty_binary_1
#define CU_PTR_EMPTY_SBS		 cu_ptr_empty_sbs_1
#define CU_PTR_EMPTY_SD			 cu_ptr_empty_sd_1
#define CU_PTR_EMPTY_ARRAY		 cu_ptr_empty_array_1
#define CU_PTR_INVLD_RSRC_HNDL	 cu_ptr_invld_rsrc_hndl_1

#endif /* (CU_VERSION == 1) || defined(CU_ALL_VERSIONS) */
	
/*---------------------------------------------------------------------------*/
/*  Cluster Utilities invalid node id value.                                 */
/*                                                                           */
/*  The following macro defines an invalid node id.  An invalid node id is   */
/*  an unsigned 64-bit integer with all bits set.                            */
/*---------------------------------------------------------------------------*/

#if (CU_VERSION == 1) || defined(CU_ALL_VERSIONS)

#define CU_INVALID_NODE_ID		(~(UINT64_C(0)))

#endif /* (CU_VERSION == 1) || defined(CU_ALL_VERSIONS) */

/*---------------------------------------------------------------------------*/
/*  Cluster Utilities API type definitions.                                  */
/*---------------------------------------------------------------------------*/

/* Data type definitions for cluster info and server lists */

#define CU_ID_LEN 64		
#define CU_IP_ADDR_LEN 64
#define CU_MAX_NAME_LEN 64
typedef char cu_cluster_id_t[CU_ID_LEN];
typedef char cu_cluster_name_t[CU_MAX_NAME_LEN];
typedef char cu_ip_addr_t[CU_IP_ADDR_LEN];
typedef char **cu_ip_addr_list_t;

typedef struct 
{
	cu_cluster_id_t		cu_cluster_ID;
	cu_cluster_name_t	cu_cluster_name;
	ct_int32_t			cu_node_number;
} cu_cluster_info_t;

typedef struct
{
	cu_ip_addr_t		cu_ip_address;
	ct_int32_t          cu_port_number;
} cu_registry_server_address_t;


typedef struct
{
	ct_int32_t						cu_list_size;
	cu_registry_server_address_t	*cu_server_list;
} cu_registry_server_list_t;

/*---------------------------------------------------------------------------------
 *  Following are the data types for cu_get_procspeed() and cu_cvt_time() functions
 *--------------------------------------------------------------------------------*/

typedef struct cu_timeinfo
{
    ct_uint64_t timeinfo1;
    ct_uint64_t timeinfo2;
} cu_timeinfo_t;

/*---------------------------------------------------------------------------*
 *  Following are the data types for routines that handle cluster software
 *  error information in a common fashion.
 *
 *  Note that the unsigned variants to the integer types are not represented.
 *  They are not because the same error argument can be interpreted as both
 *  signed and unsigned in a format string.  That is OK because ANSI C states
 *  that the signed and unsigned variants have the same alignment requirements
 *  and occupy the same amount of storage.  The standard goes on to say that
 *  "The same representation and alignment requirements are meant to imply
 *  interchangeability as arguments to functions, return values from functions,
 *  and members of unions."
 *
 *  Also note that certain types appear to be missing, like char, short, and
 *  float.  They are not seen here because during C argument passing char and
 *  short are promoted to int, and float is promoted to double.
 *
 *  The long double type is not supported.  The CU_ERROR_ARG_RESERVED type
 *  exists to maintain binary compatability with prior versions of the routines
 *  handling cluster software error information.
 *
 *---------------------------------------------------------------------------*/

typedef enum {
	CU_ERROR_ARG_INT,			/* int										*/
	CU_ERROR_ARG_LONG,			/* long 									*/
	CU_ERROR_ARG_LONG_LONG,		/* long long								*/
	CU_ERROR_ARG_DOUBLE,		/* double									*/
	CU_ERROR_ARG_RESERVED,		/* <this position in the enum is reserved>	*/
	CU_ERROR_ARG_CHAR_STR,		/* char *     -  character string			*/
	CU_ERROR_ARG_VOID_PTR		/* void *									*/
} cu_error_arg_type_t;

typedef union {
	int			 cu_arg_int;
	long		 cu_arg_long;
	long long	 cu_arg_long_long;
	double		 cu_arg_double;
	char		*cu_arg_char_str;
	void		*cu_arg_void_ptr;
} cu_error_arg_value_t;

typedef struct {
	cu_error_arg_type_t		cu_arg_type;	/* Type of error argument */
	cu_error_arg_value_t	cu_arg_value;	/* Error argument value */
} cu_error_arg_t;

typedef struct {
    ct_int32_t		 cu_error_id;		/* error value */
    ct_char_t		*cu_ffdc_id;		/* FFDC ID library logged entry */
    ct_char_t		*cu_msg_cat;		/* message catalog name */
    ct_int32_t		 cu_msg_set;		/* message catalog set */
    ct_int32_t		 cu_msg_num;		/* message number */
    ct_char_t		*cu_msg_default;	/* default message */
    ct_uint32_t		 cu_arg_cnt;		/* count of error arguments */
    cu_error_arg_t	*cu_args;			/* array of error arguments */
} cu_error_t;

/*---------------------------------------------------------------------------*
 *  The following data types are used by the codeset conversion functions.      
 *
 *  The codset conversion functions are wrappers to iconv_open(), iconv(),
 *  and iconv_close().  The wrapper functions are named cu_iconv_open(),
 *  cu_iconv_str(), cu_iconv_buf(), and cu_iconv_close().  The cu_iconv_t type,
 *  known as a conversion handle, is a wrapper for the iconv_t type, known as a
 *  conversion descriptor.  A conversion handle should be considered opaque;
 *  the fields of the handle should not be directly referenced outside of
 *  the wrapper functions.
 *
 *  The wrapper functions provide the following features above those of the
 *  normal iconv() functions:
 *
 *   1) Access to a conversion descriptor is serialized.
 *   2) A conversion handle can be duplicated - via cu_iconv_dup().
 *   3) Conversion is always between the cluster software's internal codeset,
 *      UTF-8, and the client's codeset.
 *   4) The cu_iconv_str() function is oriented toward null-terminated
 *      multi-byte character strings.
 *   5) The cu_iconv_str() and cu_iconv_buf() functions avoid calling iconv()
 *      when the client codeset is UTF-8.  Calls to iconv() may be avoided for
 *      some strings when the client codeset includes 7-bit ASCII (the Portable
 *      Character Set) and has other characteristics.
 *
 *  The cu_iconv_multipliers() macro can be called for a conversion handle
 *  to determine the conversion multipliers for the conversion that can be
 *  done with that convesion handle.  The conversion multipliers indicate
 *  how much larger an output buffer should be than an input buffer when
 *  cu_iconv_str() is called.  If an input string to be converted is 20 bytes
 *  in size (including the null-terminator), and the conversion multiplier is
 *  3, the output buffer should be 20 * 3 = 60 bytes.  The "nominal"
 *  multiplier may be smaller than the "maximum" multiplier.  The value of the
 *  nominal multiplier is based on inspection of conversion tables.  The value
 *  of the maximum multiplier is based on the general structure of the
 *  codesets involved, without reference to conversion tables.  A caller of
 *  cu_iconv_str() that wishes to allocate the output buffer's memory might
 *  allocate a buffer based on the nominal multiplier first.  If
 *  cu_iconv_str() returns CU_ECONVBUFFERSIZE, the caller might want to
 *  allocate an output buffer based on the maximum multiplier, and try the
 *  call to cu_iconv_str() again.  The goal is that the nominal multiplier
 *  should almost always be sufficient.  A nominal multiplier might become
 *  insufficient if the mappings of characters between the codesets involved
 *  change.  The nominal multiplier might also be insufficient if characters
 *  in the input string cannot be represented in the codeset to which the
 *  string is being converted.
 *
 *  A caller of cu_iconv_str() need not worry about conversion multipliers
 *  if it allows cu_iconv_str() to allocate the output buffer.
 *
 *  A caller of cu_iconv_buf() must concern itself with conversion multipliers,
 *  since it must allocate the output buffer.
 *---------------------------------------------------------------------------*/

typedef struct cu_iconv		cu_iconv_t;

struct cu_iconv {
	void			 *cui_serial_p;				/* Ptr to serialization obj.  */
	ct_uint32_t		  cui_refcnt;				/* Handle reference count	  */
	ct_uint16_t		  cui_iconv_flags;			/* Codeset conversion flags	  */
	ct_uint16_t		  cui_codeset_flags;		/* Client codeset flags		  */
	ct_uint16_t		  cui_nominal_multiplier;	/* Conv. nominal multiplier	  */
	ct_uint16_t		  cui_maximum_multiplier;	/* Conv. maximum multiplier	  */
	void			 *cui_conv_state_p;			/* Conversion state info.	  */
};

#define cu_iconv_multipliers(cui_p, nm_p, mm_p)								\
{																			\
	*(nm_p) = (cui_p)->cui_nominal_multiplier;								\
	*(mm_p) = (cui_p)->cui_maximum_multiplier;								\
}

/*
 *  Define the codeset name for UTF-8.  Codeset names are platform-dependent.
 */

#if _AIX
#define CU_UTF8_CODESET	"UTF-8"
#endif /* _AIX */

#if __linux__
#define CU_UTF8_CODESET	"UTF-8"
#endif /* __linux__ */

#if defined(__INTERIX)
#define CU_UTF8_CODESET "UTF-8"
#endif

#if defined(__sun)
#define CU_UTF8_CODESET "UTF-8"
#endif

/*
 *  Conversion flag values, passed in iconv_flags argument of cu_iconv_open().
 *
 *  CU_ICONV_FLAG_TO_CLIENT_CODESET - Conversion is from UTF-8 to the client's
 *									  codeset.
 *
 *  CU_ICONV_FLAG_NO_SERIALIZATION  - cu_iconv_* routines are not to serialize
 *									  the use of the conversion handle.  If this
 *                                    is specified, the caller of the cu_iconv_*
 *                                    routines must ensure only one call to the
 *                                    routines are in progress at a time for a
 *                                    particular conversion handle.
 *
 *  CU_ICONV_FLAG_NO_ESCAPE_SEQUENCE - Conversion should not accept or generate
 *									   escape sequences in the client's strings.
 *                                     These are the <U+XXXX> escapes sequences
 *                                     that represent Unicode character values.
 *
 *  CU_ICONV_FLAG_DO_NOT_MODIFY_UTF8 - Conversion should not modify strings,
 *                                     assuming the client's strings are
 *                                     meant to be internal UTF-8 strings.
 *
 *  CU_ICONV_FLAG_KEEP_DEBUG_COUNTERS - Conversion handle should maintain
 *                                      debugging counters.
 *
 *  CU_ICONV_FLAG_LIMIT_UTF8_TO_BMP - Generated UTF-8 strings should be limited
 *                                    to characters in the Unicode Basic
 *                                    Multilingual Plane (BMP).
 */

#define CU_ICONV_FLAG_TO_CLIENT_CODESET		0x0001
#define CU_ICONV_FLAG_NO_SERIALIZATION		0x0002
#define CU_ICONV_FLAG_NO_ESCAPE_SEQUENCE	0x0004
#define CU_ICONV_FLAG_DO_NOT_MODIFY_UTF8	0x0008
#define CU_ICONV_FLAG_KEEP_DEBUG_COUNTERS	0x0010
#define CU_ICONV_FLAG_LIMIT_UTF8_TO_BMP		0x0020

/*---------------------------------------------------------------------------*
 *  The following definitions are used by the cu_get_locale_info().      
 *
 *  CU_NUM_LOCALE_CATEGORIES is the number of locale categories returned.
 *  CU_NUM_LANGINFO_ITEMS is the number of language info. items returned.
 *---------------------------------------------------------------------------*/

#define CU_NUM_LOCALE_CATEGORIES	6
#define CU_NUM_LANGINFO_ITEMS		1

/*---------------------------------------------------------------------------*
 *  The following definitions are useful to process multi-byte character
 *  strings.
 *
 *    CU_UTF8_CHAR_MAX - Maximum size, in bytes, of a UTF-8 character.
 *
 *    CU_MB_CUR_MAX    - This macro returns the maximum length of a character
 *                       in the process locale encoding (or in UTF-8).
 *
 *    CU_MBLEN         - This macro returns the length of the character whose
 *                       first byte is pointed to by s.  However, 0 is returned
 *                       if s points to a null byte, and -1 is returned if the
 *                       sequence of bytes beginning at s is not a valid
 *                       character.  The bytes are interpreted according to the
 *                       rules of the process locale encoding (or UTF-8).
 *
 *---------------------------------------------------------------------------*/

#define CU_UTF8_CHAR_MAX  6

#define CU_MB_CUR_MAX	  (cu_utf8_is_assumed() ? CU_UTF8_CHAR_MAX : MB_CUR_MAX)

#define CU_MBLEN(s, n)	  (cu_utf8_is_assumed() ? cu_utf8_mblen(s, n)		   \
												: mblen(s, n))

/*---------------------------------------------------------------------------*
 *  The following definitions are used by cu_catopen().      
 *
 *  CU_CAT_INCLUDE_C_LOCALE specifies that the C locale should also be searched
 *                          for the message file. 
 *---------------------------------------------------------------------------*/
#define CU_CATOPEN_INCLUDE_C_LOCALE  0x00000001

/*---------------------------------------------------------------------------*/
/*  The following definitions are used with the .cdef query functions.       */
/*---------------------------------------------------------------------------*/
#define CU_RSRC_CLASS_SUBDIVIDED  0
#define CU_RSRC_CLASS_CENTRALIZED 1
#define CU_RSRC_CLASS_GLOBALIZED  2

/*---------------------------------------------------------------------------------
 *  Following are the data types for cu_get_version
 *--------------------------------------------------------------------------------*/
typedef struct cu_vrmf cu_vrmf_t;

struct cu_vrmf {
    ct_uint16_t    version;
    ct_uint16_t    release;
    ct_uint16_t    modlevel;
    ct_uint16_t    fixlevel;
};

/*---------------------------------------------------------------------------*/
/*  Cluster Utilites API function prototypes - Version 1                     */
/*---------------------------------------------------------------------------*/

/*
 * Function prototypes for functions intended for Cluster Utilities API clients.
 * Clients should use the generic routine names defined by macros included
 * in this header file, such as cu_rsrc_is_dependent(), instead of the version
 * specific routine names, like cu_rsrc_is_dependent_1().  Those macros
 * convert the generic names to the appropriate version specific names.
 */

#if (CU_VERSION == 1) || defined(CU_ALL_VERSIONS)

extern ct_int32_t
cu_get_cluster_info_1(
	cu_cluster_info_t *cluster_info		/* return par: cluster info	 		*/
);										/* return: 0(OK) or CU_EFAILURE     */

extern ct_int32_t
cu_get_tsgs_cluster_info_1(
	cu_cluster_info_t *cluster_info		/* return par: cluster info			*/
);										/* return: 0(OK) or CU_EFAILURE		*/

extern ct_int32_t
cu_get_registry_server_list_1(
	cu_cluster_name_t cluster_name,		/* input: cluster name				*/
	cu_registry_server_list_t *			/* return par: server list			*/
);										/* return: 0(OK) or CU_EINVALIDNAME */

extern void
cu_free_registry_server_list_1(
	cu_registry_server_list_t *			/* input: server list				*/
);										/* return: void						*/

extern ct_int32_t
cu_get_cluster_ID_1(
	cu_cluster_name_t cluster_name,		/* input: cluster name				*/
	cu_cluster_id_t	clusterID			/* return: cluster ID				*/
);

extern ct_int32_t
cu_get_node_number_1(
	cu_cluster_name_t cluster_name,		/* input: cluster name				*/
    ct_uint32_t       *node_number      /* return: node number              */
);

extern ct_int32_t
cu_rsrc_is_fixed_1(		        		/* Is resource type == fixed         */
	const ct_resource_handle_t *		/* input:  ptr to rsrc handle        */
);										/* return: boolean (TRUE if yes)     */

extern ct_int32_t
cu_rsrc_hndl_has_node_id_1(        		/* Resource handle includes node id  */
	const ct_resource_handle_t *		/* input:  ptr to rsrc handle        */
);										/* return: boolean (TRUE if yes)     */

extern ct_uint16_t
cu_get_resource_location_1(				/* get location of resource          */
	const ct_resource_handle_t *		/* input:  ptr to rsrc handle        */
);										/* return: node number               */

extern void
cu_set_resource_location_1(				/* set location of resource in hndl  */
	ct_resource_handle_t *,		        /* input:  ptr to rsrc handle        */
	const ct_uint16_t					/* input:  node number               */
);										/* return: void (but updated hndl)   */

extern ct_uint64_t
cu_get_resource_node_id_1(				/* get node id of resource           */
	const ct_resource_handle_t *		/* input:  ptr to rsrc handle        */
);										/* return: node id                   */

extern void
cu_set_resource_node_id_1(				/* set location of resource in hndl  */
	ct_resource_handle_t *,		        /* input:  ptr to rsrc handle        */
	const ct_uint64_t					/* input:  node id                   */
);										/* return: void (but updated hndl)   */

extern ct_uint64_t
cu_get_resource_id_1(					/* get resource ID                   */
	const ct_resource_handle_t * 	    /* input:  ptr to rsrc handle        */
);                                      /* return: resource specific ID      */

extern ct_resource_id_t
cu_get_resource_id_ext_1(				/* get resource ID                   */
	const ct_resource_handle_t *		/* input:  ptr to rsrc handle        */
);	                                    /* return: resource specific ID      */

extern ct_resource_class_id_t
cu_get_resource_class_id_1(				/* get resource class ID             */
	const ct_resource_handle_t *		/* input:  ptr to rsrc handle        */
);										/* return: resource class ID         */

extern ct_resource_handle_t
cu_gen_resource_handle_1(	        			/* make resource handle      */
	const ct_uint64_t				id,			/* input:  rsrc specific ID  */
	const ct_uint16_t				node_num,	/* input:  node number or    */
												/*         0xffff            */
	const ct_resource_class_id_t	class_id,	/* input:  resource class ID */
	const ct_int32_t 				is_fixed	/* input:  TRUE if fixed     */
												/*         location          */
);                                      		/* return: resource handle   */

extern ct_resource_handle_t
cu_gen_resource_handle_ext_1(       			/* make resource handle      */
	const ct_resource_id_t			id,		    /* input:  rsrc specific ID  */
	const ct_uint16_t				node_num,	/* input:  node number or    */
												/*         0xffff            */
	const ct_resource_class_id_t	class_id,	/* input:  resource class ID */
	const ct_int32_t				is_fixed	/* input:  TRUE if fixed     */
												/*         location          */
);                                      		/* return: resource handle   */

extern ct_resource_handle_t
cu_mk_resource_handle_1(		       			/* make resource handle      */
	const ct_resource_id_t			id,		    /* input:  rsrc specific ID  */
	const ct_resource_class_id_t	class_id,	/* input:  resource class ID */
	const ct_int32_t				is_fixed	/* input:  TRUE if fixed     */
												/*         location          */
);                                      		/* return: resource handle   */

extern ct_int32_t
cu_mk_resource_handle_pd_1(		       			/* make PD resource handle   */
	const ct_resource_class_id_t	class_id,	/* input:  resource class ID */
	ct_uint32_t						*icidp,		/* output: internal clstr ID */
	ct_resource_handle_t			*rhp		/* output: resource handle   */
);                                      		/* return: error code        */

extern ct_int32_t
cu_mk_resource_handle_icid_1(	       			/* make PD resource handle   */
	const ct_resource_class_id_t	class_id,	/* input:  resource class ID */
	const ct_uint32_t				icid,		/* input:  internal clstr ID */
	ct_resource_handle_t			*rhp		/* output: resource handle   */
);                                      		/* return: error code        */

extern ct_int32_t
cu_rsrcs_are_same_1(					/* are resources the same?           */
	const ct_resource_handle_t *,		/* input:  ptr to rsrc handle        */
	const ct_resource_handle_t *		/* input:  ptr to rsrc handle        */
);										/* return: boolean (TRUE if yes)     */

extern ct_int32_t
cu_rsrc_hndl_cmp_1(						/* compare two resource handles      */
	const ct_resource_handle_t *,		/* input:  ptr to rsrc handle        */
	const ct_resource_handle_t *		/* input:  ptr to rsrc handle        */
);										/* return: <0, 0, >0                 */

extern ct_resource_handle_t
cu_get_canon_hndl_1(					/* get canonical form of rsrc hndl   */
	const ct_resource_handle_t *		/* input:  ptr to rsrc handle        */
);										/* return: resource handle           */

extern ct_int32_t
cu_set_no_error_1(						/* set API to return no error        */
	void								/* input:  none                      */
);										/* return: 0			             */

extern ct_int32_t						/* set API to return an error,       */
cu_set_error_1(							/*      specifying arguments         */
	ct_int32_t		  error_id,			/* input:  error code                */
	const ct_char_t	 *ffdc_id,			/* input:  FFDC ID string            */
	const ct_char_t	 *msg_cat,			/* input:  message catalog name      */
	ct_int32_t		  msg_set,			/* input:  message set number        */
	ct_int32_t		  msg_num,			/* input:  message number            */
	const ct_char_t	 *msg_default,		/* input:  default message text      */
	...									/* input:  variable number of args   */
);										/* return: error_id or -1			 */

extern ct_int32_t						/* set API to return an error,       */
cu_vset_error_1(						/*      specifying an argument list  */
	ct_int32_t		  error_id,			/* input:  error code                */
	const ct_char_t	 *ffdc_id,			/* input:  FFDC ID string            */
	const ct_char_t	 *msg_cat,			/* input:  message catalog name      */
	ct_int32_t		  msg_set,			/* input:  message set number        */
	ct_int32_t		  msg_num,			/* input:  message number            */
	const ct_char_t	 *msg_default,		/* input:  default message text      */
	va_list			  val				/* input:  variable argument list	 */
);										/* return: error_id or -1			 */

extern ct_int32_t						/* set API to return an error,       */
cu_pset_error_1(						/*      specifying packaged error    */
	cu_error_t		 *err_p				/* input:  error block pointer       */
);										/* return: error_id or -1			 */

extern void
cu_get_error_1(							/* get error information from API    */
	cu_error_t		**err_pp			/* output: error block pointer       */
);										/* return: void                      */

extern ct_int32_t						/* package an error block,           */
cu_pkg_no_error_1(						/*      indicating no error			 */
	cu_error_t		**err_pp			/* output: error block pointer       */
);										/* return: error_id or -1			 */

extern ct_int32_t						/* package an error block,           */
cu_pkg_error_1(							/*      specifying arguments         */
	cu_error_t		**err_pp,			/* output: error block pointer       */
	ct_int32_t		  error_id,			/* input:  error code                */
	const ct_char_t	 *ffdc_id,			/* input:  FFDC ID string            */
	const ct_char_t	 *msg_cat,			/* input:  message catalog name      */
	ct_int32_t		  msg_set,			/* input:  message set number        */
	ct_int32_t		  msg_num,			/* input:  message number            */
	const ct_char_t	 *msg_default,		/* input:  default message text      */
	...									/* input:  variable number of args   */
);										/* return: error_id or -1			 */

extern ct_int32_t						/* package an error block,           */
cu_vpkg_error_1(						/*      specifying an argument list  */
	cu_error_t		**err_pp,			/* output: error block pointer       */
	ct_int32_t		  error_id,			/* input:  error code                */
	const ct_char_t	 *ffdc_id,			/* input:  FFDC ID string            */
	const ct_char_t	 *msg_cat,			/* input:  message catalog name      */
	ct_int32_t		  msg_set,			/* input:  message set number        */
	ct_int32_t		  msg_num,			/* input:  message number            */
	const ct_char_t	 *msg_default,		/* input:  default message text      */
	va_list			  val				/* input:  variable argument list	 */
);										/* return: error_id or -1			 */

extern ct_int32_t						/* package an error block,           */
cu_apkg_error_1(						/*      specifying cu_error_arg_t	 */
	cu_error_t			**err_pp,		/* output: error block pointer       */
	ct_int32_t			  error_id,		/* input:  error code                */
	const ct_char_t		 *ffdc_id,		/* input:  FFDC ID string            */
	const ct_char_t		 *msg_cat,		/* input:  message catalog name      */
	ct_int32_t			  msg_set,		/* input:  message set number        */
	ct_int32_t			  msg_num,		/* input:  message number            */
	const ct_char_t		 *msg_default,	/* input:  default message text      */
	const cu_error_arg_t *args,			/* input:  error arguments array	 */
	ct_uint32_t			  arg_cnt		/* input:  error arguments count	 */
);										/* return: error_id or -1			 */

extern void
cu_dup_error_1(							/* duplicate an error block			 */
	cu_error_t		 *err_p,			/* input:  error block to duplicate  */
	cu_error_t		**err_pp			/* output: duplicated error block    */
);										/* return: void                      */

extern void
cu_rel_error_1(							/* free error information            */
	cu_error_t		 *err_p				/* input:  ptr to error block to free*/
);										/* return: void                      */

extern void
cu_get_errmsg_1(						/* get error message from API        */
	cu_error_t		 *err_p,			/* input:  ptr to error block        */
	ct_char_t		**msg_pp			/* output: error message			 */
);										/* return: void                      */

extern void
cu_fmt_errmsg_1(						/* format error message				 */
	const ct_char_t		 *fmt,			/* input:  format string			 */
	const cu_error_arg_t *args,			/* input:  error arguments array	 */
	ct_uint32_t			  arg_cnt,		/* input:  error arguments count	 */
	ct_char_t			**msg_pp		/* output: error message			 */
);										/* return: void                      */

extern void
cu_fmt_msg_1(	  					    /* format a message		   		     */
	const ct_char_t		 *fmt,			/* input:  format string			 */
	const ct_structured_data_element_t *args, /* input:  arguments array     */
	ct_uint32_t			  arg_cnt,		/* input:  arguments count      	 */
	ct_char_t			**msg_pp		/* output: error message			 */
);

extern void
cu_rel_errmsg_1(						/* free error message                */
	ct_char_t		 *msg_p				/* input:  ptr to message to free    */
);										/* return: void                      */

extern ct_int32_t
cu_set_error_args_1(					/* set private error arguments array */
	const ct_char_t	 *fmt,				/* input:  format string			 */
	va_list			  val,				/* input:  variable argument list	 */
	cu_error_arg_t	**args_p,			/* output: error arguments array	 */
	ct_uint32_t		 *arg_cnt_p			/* output: error arguments count	 */
);										/* return: 0 or -1					 */

extern void
cu_rel_error_args_1(					/* free private error args. array	 */
	cu_error_arg_t	 *args,				/* input:  error arguments array	 */
	ct_uint32_t		  arg_cnt			/* input:  error arguments count	 */
);										/* return: void                      */

extern ct_int32_t
cu_gen_rsrc_ids_init_1(					/* initialize resource ID generation */
	void								/* no arguments                      */
);										/* return: 0(OK) or CU_EFAILURE      */

extern ct_int32_t
cu_gen_rsrc_ids_1(						/* generate resource IDs             */
	ct_resource_id_t	*ids,			/* output: array of resource IDs     */
	const ct_uint32_t	numOfIDs		/* input:  number of IDs to generate */
);										/* return: 0(OK) or CU_EFAILURE      */

extern ct_int32_t
cu_gen_rsrc_ids_for_specified_node_1(	/* generate resource IDs for a node  */
	ct_uint64_t			nodeid,			/* input:  specified node id		 */
	ct_resource_id_t	*ids,			/* output: array of resource IDs     */
	const ct_uint32_t	numOfIDs		/* input:  number of IDs to generate */
);										/* return: 0(OK) or CU_EFAILURE      */

extern ct_int32_t
cu_gen_rsrc_ids_with_icid_1(			/* generate resource IDs with        */
										/*   internal cluster ID             */
	ct_resource_id_t	*ids,			/* output: array of resource IDs     */
	const ct_uint32_t	numOfIDs		/* input:  number of IDs to generate */
);										/* return: 0(OK) or CU_EFAILURE      */

extern void
cu_rsrc_id_to_string_1(					/* convert resource ID to string     */
	const ct_resource_id_t	id,			/* input:  resource ID               */
	ct_char_t				*string		/* output: string                    */
);										/* return: void                      */

extern void
cu_rsrc_id_from_string_1(				/* convert string to resource ID     */
	ct_resource_id_t	*id,			/* output: resource ID               */
	const ct_char_t		*string			/* input:  string                    */
);										/* return: void                      */

extern ct_int32_t
cu_get_hwid_1(							/* get the node's hardware ID	     */
	ct_uint64_t	*id						/* output: hardware ID               */
);										/* return: void                      */

extern ct_int32_t
cu_validate_specific_node_id_1(			/* validate the specific node ID     */
	const char	*node_id_str,			/* input:  node ID to validate	     */
	ct_uint64_t	*node_id_p				/* output: binary node ID (optional) */
);										/* return: 0, or CU_ENODEIDINVALID	 */

extern ct_int32_t
cu_set_specific_node_id_1(				/* set the specific node ID for node */
	int			 force,					/* input:  force specified node ID	 */
	const char	*node_id_str			/* input:  specific node ID to set   */
);										/* return: 0, CU_ENODEIDINVALID,	 */
										/*         CU_ENODEIDALREADY, or	 */
										/*		   CU_ENODEIDOTHER			 */

extern ct_int32_t
cu_set_node_id_1(						/* set the node's node ID		     */
	int			 force,					/* input:  force new node ID		 */
	ct_uint64_t	*node_id_p				/* output: node ID (optional)        */
);										/* return: 0, CU_ENODEIDGENERATE,	 */
										/*         CU_ENODEIDALREADY, or	 */
										/*		   CU_ENODEIDOTHER			 */

extern ct_int32_t
cu_get_node_id_1(						/* get the node's node ID		     */
	ct_uint64_t	*node_id_p				/* output: node ID                   */
);										/* return: 0, CU_ENODEIDMISSING,	 */
										/*         CU_ENODEIDMISMATCH, or	 */
										/*		   CU_ENODEIDOTHER			 */

extern ct_int32_t
cu_get_procspeed_1(
        cu_timeinfo_t* timeinfo_p      /* Get the conversion factor for  */
                                       /* the CPU used.                  */
                                       /* Get the time corresponding to  */
                                       /* TSC=0                          */
);

extern ct_int32_t
cu_compute_base_timeinfo_1(
	cu_timeinfo_t *base		/* get the new base timeinfo */
);

extern ct_int32_t
cu_get_ctr_1(
        ct_uint64_t* counter           /* Use the structure to store the  */
                                       /* low and high parts of the TSC.  */
);

extern ct_int32_t
cu_cvt_time_1(
	ct_uint64_t counter,				/* On entry the TSC, on exit the  */
										/* corresponding to that TSC.	  */
	cu_timeinfo_t *timeinfo_p,			/* The CPU specific factor.		  */
										/* The base returned by			  */
										/* cu_get_procspeed()			  */
	struct timespec	 *time_p			/* The result					  */
);

extern ct_int32_t 
cu_get_monotonic_time_1( 
	struct timeval *curtime 	/* time of day -- but only increasing */
);

extern ct_int32_t
cu_gettimeofday_1(
	struct timeval *curtime,	/* time of day */
	struct timezone *tz		/* timezone -- obsolete */
);

extern ct_int32_t 
cu_get_current_time_1(
	struct timespec *timestamp	/* precision timestamp */
);

extern void
cu_force_iconv_single_threaded_1(		/* Single thread use of cu_iconv_*    */
	void								/* input:  none                       */
);										/* return: nothing		              */

extern ct_int32_t
cu_iconv_open_1(						/* Open codeset conversion handle	  */
	const char	*client_codeset_p,		/* input:  client codeset			  */
	ct_uint32_t	 iconv_flags,			/* input:  conversion flags			  */
	cu_iconv_t **cui_pp					/* output: conversion handle		  */
);										/* return: 0, CU_ECONVNOMEM,		  */
										/*   CU_ECONVAGAIN, CU_ECONVINVALID,  */
										/*   or CU_ECONVNOSUPPORT			  */
extern void
cu_iconv_dup_1(							/* Duplicate codeset conv. handle	  */
	cu_iconv_t	*cui_p,					/* input:  conversion handle		  */
	cu_iconv_t **dup_cui_pp				/* output: duplicated conv. handle	  */
);										/* return: nothing					  */

extern void
cu_iconv_close_1(						/* Close codeset conversion handle	  */
	cu_iconv_t	*cui_p					/* input:  conversion handle		  */
);										/* return: nothing					  */

extern ct_int32_t
cu_iconv_str_1(							/* Perform string codeset conversion  */
	cu_iconv_t	*cui_p,			    	/* input:  conversion handle		  */
	ct_uint32_t	 try_in_place,	    	/* input:  try to do in place		  */
	char		*in_str_p,		    	/* input:  input string				  */
	size_t	    *in_str_size_p,	    	/* in/out: input string size		  */
	char	   **out_str_pp,	    	/* in/out: output string			  */
	size_t	    *out_str_size_p	    	/* in/out: output string length		  */
);										/* return: 0, CU_ECONVNOMEM,		  */
										/*  CU_ECONVINVALID, CU_ECONVBADINPUT,*/
										/*  CU_ECONVBUFFERSIZE, or			  */
										/*  CU_ECONVESCAPESEQ				  */

extern ct_int32_t
cu_iconv_buf_1(							/* Perform buffer codeset conversion  */
	cu_iconv_t	*cui_p,			    	/* input:  conversion handle		  */
	const char **in_buf_pp,		    	/* in/out: input buffer				  */
	size_t	    *in_bytes_left_p,    	/* in/out: input buffer bytes left	  */
	char	   **out_buf_pp,	    	/* in/out: output buffer			  */
	size_t	    *out_bytes_left_p    	/* in/out: output buffer bytes left	  */
);										/* return: 0,				 		  */
										/*  CU_ECONVINVALID, CU_ECONVBADINPUT,*/
										/*  CU_ECONVBUFFERSIZE, or			  */

extern const char *
cu_iconv_intermediate_codeset_1(		/* Get intermediate Unicode codeset	  */
	void								/* input:  none	                      */
);										/* return: Intermediate codeset name  */

extern ct_int32_t
cu_iconv_get_cntrs_1(					/* Get conversion debug counters	  */
	cu_iconv_t	  *cui_p,		    	/* input:  conversion handle		  */
	char		***cntr_names_ppp,    	/* output: array of counter names	  */
	ct_uint32_t  **cntr_values_pp,    	/* output: array of counter values	  */
	ct_uint32_t	  *cntr_elements_p    	/* output: # elements in arrays		  */
);										/* return: 0, CU_ECONVNOMEM,		  */
										/*  or CU_ECONVINVALID.				  */

extern void
cu_iconv_rel_cntrs_1(					/* Release conversion debug counters  */
	cu_iconv_t	  *cui_p,		    	/* input:  conversion handle		  */
	char		 **cntr_names_pp,    	/* input:  array of counter names	  */
	ct_uint32_t   *cntr_values_p,    	/* input:  array of counter values	  */
	ct_uint32_t	   cntr_elements    	/* input:  # elements in arrays		  */
);										/* return: nothing					  */

extern ct_int32_t
cu_get_locale_info_1(					/* Get process' locale information	  */
	ct_uint32_t	*category_count_p,		/* output: number of categories		  */
	int		   **category_list_pp,		/* output: list of category IDs		  */
	char	  ***category_locales_ppp,	/* output: list of category locales	  */
	ct_uint32_t	*item_count_p,			/* output: number of items			  */
	nl_item	   **item_list_pp,			/* output: list of item identifiers	  */
	char	  ***item_langinfo_pp,		/* output: list of item values		  */
	char	   **codeset_pp				/* output: string codeset			  */
);										/* return: 0, CU_ELOCALEFAILURE,	  */
										/*         CU_ELOCALENOMEM, or		  */
										/*         CU_ELOCALEAGAIN			  */

extern void
cu_rel_locale_info_1(					/* Release process' locale info.	  */
	int		    *category_list_p,		/* input:  list of category IDs		  */
	char	   **category_locales_pp,	/* input:  list of category locales	  */
	nl_item	    *item_list_p,			/* input:  list of item identifiers	  */
	char	   **item_langinfo_pp,		/* input:  list of item values		  */
	char	    *codeset_p				/* input:  string codeset			  */
);										/* return: nothing					  */

extern ct_int32_t
cu_get_utf8_locale_1(					/* Get name of UTF-8 encoded locale	  */
	char		*locale_p,				/* input:  name of a locale			  */
	char	   **utf8_locale_pp			/* output: name of a UTF-8 encoded 	  */
										/*         locale for same language	  */
										/*         and territory			  */
);										/* return: 0, CU_ELOCALEFAILURE,	  */
										/*         or CU_ELOCALENOMEM		  */

extern void
cu_rel_utf8_locale_1(					/* Free name of UTF-8 encoded locale  */
	char		*utf8_locale_p			/* input:  UTF-8 encoded locale name  */
);										/* return: nothing					  */

extern void
cu_assume_utf8_1(						/* Assume client strings are UTF-8    */
	void								/* input:  none                       */
);										/* return: nothing		              */

extern int
cu_utf8_is_assumed_1(					/* Client strings are assumed UTF-8   */
	void								/* input:  none                       */
);										/* return: 1 if client strings UTF-8; */
										/*         0 if they are not.		  */

extern void
cu_do_not_modify_utf8_1(				/* Do not modify UTF-8 strings		  */
	void								/* input:  none                       */
);										/* return: nothing		              */

extern int
cu_utf8_is_not_modified_1(				/* UTF-8 strings are not modified	  */
	void								/* input:  none                       */
);										/* return: 1 if UTF-8 not modified;	  */
										/*         0 if they are.			  */
extern void
cu_limit_utf8_to_bmp_1(					/* Limit generated UTF-8 chars to BMP */
	void								/* input:  none                       */
);										/* return: nothing		              */

extern int
cu_utf8_is_limited_to_bmp_1(			/* Generated UTF-8 chars only in BMP  */
	void								/* input:  none                       */
);										/* return: 1 if UTF-8 chars only BMP; */
										/*         0 if they are not.		  */

extern int								/* strcasecmp() w/POSIX case rules:   */
cu_strcasecmp_posix_1(					/*  (UTF-8 or locale codeset strings) */
	const char *s1,						/* input: string 1					  */
	const char *s2						/* input: string 2					  */
);										/* return: <0 if string 1 < string 2  */
										/*          0 if string 1 = string 2  */
										/*         >0 if string 1 > string 2  */

extern int								/* strcasecmp() w/POSIX case rules:   */
cu_utf8_strcasecmp_posix_1(				/*  (for UTF-8 encoded strings only)  */
	const char *s1,						/* input: string 1					  */
	const char *s2						/* input: string 2					  */
);										/* return: <0 if string 1 < string 2  */
										/*          0 if string 1 = string 2  */
										/*         >0 if string 1 > string 2  */

extern int								/* strcasecmp() w/POSIX case rules:   */
cu_cset_strcasecmp_posix_1(				/*  (for locale codeset strings only) */
	const char *s1,						/* input: string 1					  */
	const char *s2						/* input: string 2					  */
);										/* return: <0 if string 1 < string 2  */
										/*          0 if string 1 = string 2  */
										/*         >0 if string 1 > string 2  */

extern int								/* strcasecmp() w/POSIX case rules:   */
cu_8bit_strcasecmp_posix_1(				/*  (for 8-bit ASCII strings only)	  */
	const char *s1,						/* input: string 1					  */
	const char *s2						/* input: string 2					  */
);										/* return: <0 if string 1 < string 2  */
										/*          0 if string 1 = string 2  */
										/*         >0 if string 1 > string 2  */

extern int								/* strncasecmp() w/POSIX case rules:  */
cu_strncasecmp_posix_1(					/*  (UTF-8 or locale codeset strings) */
	const char *s1,						/* input: string 1					  */
	const char *s2,						/* input: string 2					  */
	size_t		n						/* input: maximum number of bytes	  */
);										/* return: <0 if string 1 < string 2  */
										/*          0 if string 1 = string 2  */
										/*         >0 if string 1 > string 2  */

extern int								/* strncasecmp() w/POSIX case rules:  */
cu_utf8_strncasecmp_posix_1(			/*  (for UTF-8 encoded strings only)  */
	const char *s1,						/* input: string 1					  */
	const char *s2,						/* input: string 2					  */
	size_t		n						/* input: maximum number of bytes	  */
);										/* return: <0 if string 1 < string 2  */
										/*          0 if string 1 = string 2  */
										/*         >0 if string 1 > string 2  */

extern int								/* strncasecmp() w/POSIX case rules:  */
cu_cset_strncasecmp_posix_1(			/*  (for locale codeset strings only) */
	const char *s1,						/* input: string 1					  */
	const char *s2,						/* input: string 2					  */
	size_t		n						/* input: maximum number of bytes	  */
);										/* return: <0 if string 1 < string 2  */
										/*          0 if string 1 = string 2  */
										/*         >0 if string 1 > string 2  */

extern int								/* strncasecmp() w/POSIX case rules:  */
cu_8bit_strncasecmp_posix_1(			/*  (for 8-bit ASCII strings only)	  */
	const char *s1,						/* input: string 1					  */
	const char *s2,						/* input: string 2					  */
	size_t		n						/* input: maximum number of bytes	  */
);										/* return: <0 if string 1 < string 2  */
										/*          0 if string 1 = string 2  */
										/*         >0 if string 1 > string 2  */

extern int
cu_tolower_posix_1(						/* tolower() with POSIX case rules	  */
	int	c								/* input:  a single byte character	  */
);										/* return: corresponding lower case	  */
										/*         character or input char.	  */

extern int
cu_toupper_posix_1(						/* toupper() with POSIX case rules	  */
	int c								/* input:  a single byte character	  */
);										/* return: corresponding upper case	  */
										/*         character or input char.	  */

extern int
cu_utf8_mblen_1(						/* mblen() for a UTF-8 encoded string */
	const char *s,						/* input:  points to char's 1st byte  */
	size_t		n						/* input:  maximum number of bytes	  */
);										/* return: same as mblen()			  */

extern void
cu_prepare_locale_1(					/* Prepare locale environment	      */
	void								/* input:  none                       */
);										/* return: nothing		              */

extern nl_catd
cu_catopen_1(							/* Open message catalog               */
	char *,								/* input:  locale name                */
    char *,                             /* input:  catalog name               */
    ct_uint32_t                         /* input:  option                     */
);										/* return: catalog descriptor         */
										/*         or -1 if error             */
extern ct_int32_t
cu_get_cdef_info_1(                     /* Get info from .cdef file           */
    ct_char_t   *file_name_p,           /* input:  cdef filename              */
    ct_uint32_t *version_p,             /* output: version of cdef file       */
    ct_uint32_t *mgt_style_p            /* output: management style           */
);

extern ct_int32_t 
cu_get_version_1(                       /* Get RSCT version string VRMF       */
    ct_char_t   **version_string_p,     /* output: ptr to VRMF string         */
    cu_vrmf_t   **vrmf_p                /* output: ptr to VRMF structure      */
);

extern ct_int32_t 
cu_cmp_rsct_versions_1(                 /* Compare two VRMFs */
    const cu_vrmf_t *va,                
    const cu_vrmf_t *vb
);

extern ct_int32_t 
cu_gethostbyname_1(
	const char		*host_name_p,		/* Host name						  */
	struct hostent **hostent_pp			/* Returned hostent structure		  */
);										/* return: 0 or CU_EHOST*			  */

extern ct_int32_t 
cu_gethostbyaddr_1(
	const void		*host_addr_p,		/* Host address						  */
	size_t			 host_addr_len,		/* Length of host address			  */
	int				 host_addr_type,	/* Address family					  */
	struct hostent **hostent_pp			/* Returned hostent structure		  */
);										/* return: 0 or CU_EHOST*			  */

/*
 *  Temporary evil of defining AI_NUMERICSERV here until such time as the
 *  build environment is updated.  AI_NUMERICSERV can be specified in the
 *  ai_flags field of the *hints_p structure of cu_getaddrinfo() and
 *  getaddrinfo().
 */

#if defined(__linux__)
	#if !defined(AI_NUMERICSERV)
		#define AI_NUMERICSERV	0x0400		   /* don't use name resolution	  */
	#endif
#elif defined(__sun)
	#if !defined(AI_NUMERICSERV)
		#define AI_NUMERICSERV	0x0040		   /* don't use name resolution	  */
	#endif
#endif

extern int
cu_getaddrinfo_1(						/* Update resolver/call getaddrinfo() */
	const char			  *nodename_p,	/* input:  see getaddrinfo() man page */
	const char			  *servname_p,	/* input:  see getaddrinfo() man page */
	const struct addrinfo *hints_p,		/* input:  see getaddrinfo() man page */
	struct addrinfo		 **res_pp		/* output: see getaddrinfo() man page */
);										/* return: see getaddrinfo() man page */

extern int
cu_getnameinfo_1(						/* Update resolver/call getnameinfo() */
	const struct sockaddr *sa_p,		/* input:  see getnameinfo() man page */
	socklen_t			   salen,		/* input:  see getnameinfo() man page */
	char				  *node_p,		/* output: see getnameinfo() man page */
	socklen_t			   nodelen,		/* output: see getnameinfo() man page */
	char				  *service_p,	/* output: see getnameinfo() man page */
	socklen_t			   servicelen,	/* output: see getnameinfo() man page */
	int					   flags		/* output: see getnameinfo() man page */
);										/* return: see getnameinfo() man page */

extern void
cu_ipaddr_ntop_1(						/* IP addr: network to presentation	  */
	const struct in6_addr	*src_p,		/* input:  source network address	  */
	char					*dst_p		/* output: dest presentation address  */
);										/* return: nothing					  */

extern int
cu_ipaddr_pton_1(						/* IP addr: presentation to network	  */
	const char				*src_p,		/* input:  source presentation addr	  */
	struct in6_addr			*dst_p		/* output: destination network addr	  */
);										/* return: 1 if conversion successful */
										/*         0 if not successful		  */

extern size_t 
cu_pick_thread_stacksize_1(
	const size_t		byte_count		/* Needed thread stack size 		  */
);										/* return: a good size 				  */

extern ct_int32_t
cu_check_crit_rsrc_meth_1(
	ct_uint32_t		method			/* critical resource protection method    */
);							/* return 1 if protect_method will take an action */

extern ct_int32_t 
cu_protect_crit_rsrc_1(
	ct_uint32_t		method		/* way of protection the critical resource    */
);								/* return:  0 if method is 'none',			  */
								/*         -1 if method is invalid			  */

extern int
cu_getadmin_group_id_1(gid_t *gid_p);       /* retrieve group id of RSCT admin
                                               group */

extern ct_int32_t
cu_get_clusters_info_1(
	cu_cluster_info_t	**clusters_info,	/* return par: cluster info array */
											/* caller must free returned ptr  */
	ct_int32_t			*cluster_count		/* return par: cluster count      */
);											/* return: 0(OK) or CU_EFAILURE   */


#endif /* (CU_VERSION == 1) || defined(CU_ALL_VERSIONS) */

#ifdef __cplusplus
} // end extern "C"
#endif /* __cplusplus */

#endif	/* _H_CT_CU */



