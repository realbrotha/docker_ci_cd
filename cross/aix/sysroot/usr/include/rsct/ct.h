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
/* Module Name:  ct.h                                                        */
/*                                                                           */
/* Description:                                                              */
/*     Interface definitions common to multiple RS/6000 Cluster Technology   */
/*     Application Programming Interfaces.                                   */
/*                                                                           */
/*     This file is formatted to be viewed with tab stops set to 4.          */
/*===========================================================================*/
/* sccsid = "@(#)12   1.19   src/rsct/ct.h, rsct_common, rsct_rhay53, rhay531006a 1/31/08 22:04:43" */

#ifndef _H_CT
#define _H_CT

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* rsct_copyright.h removed */
#include <inttypes.h>
#if defined(__INTERIX)
#include <stdint.h>	/* uint64_t for Windows BLD */
#endif

/****************************************************************************/
/*                                                                          */
/*       Typedefs for basic data types for System Registry table cells      */
/*       and Resource Class attributes.                                     */
/*                                                                          */
/****************************************************************************/

typedef char        ct_char_t;
typedef int8_t      ct_int8_t;
typedef uint8_t     ct_uint8_t;
typedef int16_t     ct_int16_t;
typedef uint16_t    ct_uint16_t;
typedef int32_t		ct_int32_t;
typedef uint32_t	ct_uint32_t;
typedef int64_t		ct_int64_t;
typedef uint64_t	ct_uint64_t;
typedef float		ct_float32_t;
typedef double		ct_float64_t;

/****************************************************************************/
/*                                                                          */
/*       Typedefs for composite data types for System Registry table cells  */
/*       and Resource Class attributes.  The internals of the composite     */
/*       types are defined later in this file.                              */
/*                                                                          */
/*       N.B. refer to ct_cu.h for a definition of which types are          */
/*       supported by the System Registry                                   */
/*                                                                          */
/****************************************************************************/

typedef struct ct_binary             ct_binary_t;
typedef struct ct_resource_handle    ct_resource_handle_t;
typedef struct ct_resource_id        ct_resource_id_t;
typedef struct ct_sbs                ct_sbs_t;
typedef struct ct_structured_data    ct_structured_data_t;
typedef struct ct_array              ct_array_t;

/* Since the composite types can become quite large, it is convenient to
 * use pointers to the composite types. Define these pointer types.
 */

typedef ct_binary_t			 * ct_binary_ptr_t;
typedef ct_resource_handle_t * ct_resource_handle_ptr_t;
typedef ct_sbs_t			 * ct_sbs_ptr_t;
typedef ct_structured_data_t * ct_sd_ptr_t;
typedef ct_array_t           * ct_array_ptr_t;
typedef ct_char_t            * ct_char_ptr_t;  /* Null terminated string    */

/****************************************************************************/
/*                                                                          */
/*       Value Type                                                         */
/*                                                                          */
/****************************************************************************/

/* Define a type to contain any resource attribute value or, if the attribute
 *  is of composite or string type, a pointer to a resource attribute value.
 */

typedef union {
	ct_int32_t					val_int32;
	ct_uint32_t					val_uint32;
	ct_int64_t					val_int64;
	ct_uint64_t					val_uint64;
	ct_float32_t				val_float32;
	ct_float64_t				val_float64;
	ct_char_ptr_t				ptr_char;
	ct_binary_ptr_t				ptr_binary;
    ct_resource_handle_ptr_t	ptr_rsrc_handle;
	ct_sd_ptr_t					ptr_sd;
    ct_sbs_ptr_t				ptr_sbs;
    ct_array_ptr_t              ptr_array;
} ct_value_t;

/* Enumeration of resource attribute data types or of pointers to data 
 * types that may be present in a ct_value_t
 *
 * N.B. refer to ct_cu.h for a definition of which types are supported by
 * the System Registry
 */

typedef enum {
	CT_UNKNOWN = 0,
	CT_NONE,					/* for Quantum variables only             */
	CT_INT32,
	CT_UINT32,
	CT_INT64,
	CT_UINT64,
	CT_FLOAT32,
	CT_FLOAT64,
	CT_CHAR_PTR,				/* pointer to NULL-terminated string      */
	CT_BINARY_PTR,				/* pointer to ct_binary_t                 */
	CT_RSRC_HANDLE_PTR,			/* pointer to ct_resource_handle_t        */
    CT_SD_PTR,					/* pointer to ct_sd_t                     */
    CT_SBS_PTR,					/* pointer to ct_sbs_t                    */
    CT_INT32_ARRAY,				/* CT_INT32 array                         */
    CT_UINT32_ARRAY,			/* CT_UINT32 array                        */
    CT_INT64_ARRAY,				/* CT_INT64 array                         */
    CT_UINT64_ARRAY,			/* CT_UINT64 array                        */
    CT_FLOAT32_ARRAY,			/* CT_FLOAT32 array                       */
    CT_FLOAT64_ARRAY,			/* CT_FLOAT64 array                       */
    CT_CHAR_PTR_ARRAY,			/* CT_CHAR_PTR array                      */
    CT_BINARY_PTR_ARRAY,		/* CT_BINARY_PTR array                    */
    CT_RSRC_HANDLE_PTR_ARRAY,	/* CT_RSRC_HANDLE_PTR array               */
    CT_SD_PTR_ARRAY			/* CT_SD_PTR array                        */
} ct_data_type_t;

/****************************************************************************/
/*                                                                          */
/*       Definitions of composite data types for System Registry table      */
/*       cells and Resource Class attributes.                               */
/*                                                                          */
/*       N.B. refer to ct_cu.h for a definition of which types are          */
/*       supported by the System Registry                                   */
/*                                                                          */
/****************************************************************************/

/* Binary type:
 *
 * Define a type to specify a binary value. Note that the structure
 * only defines a binary value of length 1. Otherwise, the type is used to
 * overlay a buffer of appropriate size to contain the desired binary value.
 *
 * N.B. If the length field is zero, the binary value is NULL. If such is
 * the case, the first element of the data array should NOT be assumed to
 * be addressable.
 */

struct ct_binary {
	ct_uint32_t		length;		/* length of binary value */
	ct_char_t		data[1];	/* binary value */
};								/* ct_binary_t defined earlier in file */

/*--------------------------------------------------------------------------*/

/* Resource Handle type:
 * 
 * Define a type to contain a resource handle. A resource handle is a cluster
 * unique, persistent identifier of a resource . While the resource handle is
 * opaque to an application, the Cluster Utilities library supports several
 * subroutine to obtain useful information from a resource handle.
 */
    
typedef ct_uint16_t  ct_resource_class_id_t;  /* Resource class identifier  */ 

    
struct ct_resource_id {
	ct_uint32_t  id1;
	ct_uint32_t  id2;
	ct_uint32_t  id3;
	ct_uint32_t	 id4;
};                              /* ct_resource_id_t already defined         */
	
struct ct_resource_handle {
	ct_uint32_t      header;
	ct_resource_id_t id;
};                              /* ct_resource_handle_t already defined     */

/*--------------------------------------------------------------------------*/

/* Structured Byte String type:
 *
 * define a type that specifies a Structured Byte String field. Note that the
 * actual data length depends on the data type of the field and/or the 
 * data value.
 *
 * The data length of a field of type CT_SF_STRING includes the terminating
 * NULL byte of the string. Data in a field type of CT_SF_BINARY consists 
 * of one or more bytes containing arbitrary values, including 0.
 */

typedef struct {
	ct_int16_t		field_length;		/* length of data in field_data[] */
	ct_int8_t		field_dtype;		/* type from ct_sbs_field_data_type_t */
	ct_int8_t		field_sn;			/* serial number */
	ct_char_t		field_data[1];
} ct_sbs_field_t;

typedef enum {
	CT_SF_INT32,
	CT_SF_FLOAT32,
	CT_SF_STRING,
	CT_SF_BINARY
} ct_sbs_field_data_type_t;

/* define a type that specifies a Structured Byte String. While this type
 * contains one SBS field, additional fields are placed immediately after the
 * first and subsequent fields.
 */

struct ct_sbs {
	ct_int32_t		length;			/* length of all that follows */
	ct_sbs_field_t	field1;
};									/* ct_sbs_t already defined in this file */

/*--------------------------------------------------------------------------*/

/* Structured Data type:
 *
 * Define a type that specifies an element of Structured Data.  Note that
 * data_type may be any value taken from ct_data_type_t EXCEPT CT_SBS_PTR and
 * CT_SD_PTR. In other words, a SD element may be any type other than Structured
 * Byte String or Structured Data.
 */

typedef struct {
	ct_data_type_t	data_type;
    ct_uint32_t     pad;
	ct_value_t		value;
} ct_structured_data_element_t;

/* Define a type that specifies a Structured Data attribute value. Note that
 * the structure only defines an array with one array element. Otherwise, the
 * type is used to overlay a buffer of appropriate size to contain the desired
 * number of elements. If the element_count field is zero, a NULL array is
 * indicated. If such is the case, the first element of the array should NOT be
 * assumed to be addressable.
 */

struct ct_structured_data {
	ct_uint32_t	 				    element_count;
	ct_uint32_t			 			pad;
	ct_structured_data_element_t	elements[1];
};								/*  ct_structured_data_t already defined */

/*--------------------------------------------------------------------------*/

/* Array type:
 *
 * define a type that specifies a "generic array". Note that the structure
 * only defines an array with one element. Otherwise, the type is used to
 * overlay a buffer of appropriate size to contain the desired number of
 * elements.
 *
 * N.B. If the element count field is zero, the array is NULL. If such is
 * the case, the first element of the array should NOT be assumed to be
 * addressable.
 */

struct ct_array {
	ct_uint32_t			element_count;
	ct_uint32_t			pad;
	ct_value_t			elements[1];
};								/* ct_array_t already defined in file */


/****************************************************************************/
/*                                                                          */
/*       Definitions for identifying cluster nodes or clusters.             */
/*                                                                          */
/****************************************************************************/

/* The ct_IP_contact_point_t type specifies a cluster node host name or 
 * cluster node IP address and its associated port number. This type is used
 * by an application to inform a cluster API, if required, of a node to which
 * a connection should be attempted.
 */

typedef struct {
	ct_int32_t		port;		/* port number */
	ct_char_ptr_t	name;		/* host name or IP address */ 
} ct_IP_contact_point_t;

/* There are three supported contact types, as defined by the ct_contact_type_t
 * enumeration.   In the future, other naming schemes for identifying cluster
 * nodes or clusters may be supported.
 *
 * The IP_point element of the ct_contact_point_t union is used if the contact
 * type is CT_CONTACT_IP.
 *
 * If the contact type is CT_CONTACT_ENV_VAR, then the point field in
 * ct_contact_t is ignored by the API.  Instead, the API fetches the value of
 * the CT_CONTACT environment variable and uses this value as the contact
 * point.  The syntax and semantics of this value is a function of the
 * particular API.
 *
 * If the contact type is CT_CONTACT_LOCAL, then the point field in
 * ct_contact_t is ignored by the API.  Instead, the API assumes the cluster
 * node upon which the application is running is the contact point.
 */

typedef union {
	ct_IP_contact_point_t	IP_point;
} ct_contact_point_t;

typedef enum {
	CT_CONTACT_IP,
	CT_CONTACT_ENV_VAR,
	CT_CONTACT_LOCAL
} ct_contact_type_t;

/* The ct_contact_t type is defined to insulate an API definition (not its
 * implementation) from the specific naming scheme that is used to identify
 * a cluster or cluster node. A pointer to a ct_contact_t, or array of such,
 * is passed to the appropriate API subroutine to identify the cluster or
 * cluster node(s).
 */

typedef struct {
	ct_contact_type_t	type;
	ct_contact_point_t	point;
} ct_contact_t;


/*
 *  Macros defining printf format specifiers for basic data type for System
 *  Registry table cells and Resource Class attributes.
 */

#ifdef _AIX
#ifdef __64BIT__
#define CT_PRI64_PREFIX	"l"
#else
#define CT_PRI64_PREFIX	"ll"
#endif
#endif

#ifdef __linux__
#if __WORDSIZE == 64
#define CT_PRI64_PREFIX	"l"
#else
#define CT_PRI64_PREFIX	"ll"
#endif
#endif

#ifndef CT_PRI64_PREFIX
#define CT_PRI64_PREFIX	"ll"
#endif

#define CT_PRId8	"hd"
#define CT_PRId16	"hd"
#define CT_PRId32	"d"
#define CT_PRId64	CT_PRI64_PREFIX "d"

#define CT_PRIi8	"hi"
#define CT_PRIi16	"hi"
#define CT_PRIi32	"i"
#define CT_PRIi64	CT_PRI64_PREFIX "i"

#define CT_PRIo8	"ho"
#define CT_PRIo16	"ho"
#define CT_PRIo32	"o"
#define CT_PRIo64	CT_PRI64_PREFIX "o"

#define CT_PRIx8	"hx"
#define CT_PRIx16	"hx"
#define CT_PRIx32	"x"
#define CT_PRIx64	CT_PRI64_PREFIX "x"

#define CT_PRIX8	"hX"
#define CT_PRIX16	"hX"
#define CT_PRIX32	"X"
#define CT_PRIX64	CT_PRI64_PREFIX "X"

#define CT_PRIu8	"hu"
#define CT_PRIu16	"hu"
#define CT_PRIu32	"u"
#define CT_PRIu64	CT_PRI64_PREFIX "u"


/*
 *  Macros defining scanf format specifiers for basic data type for System
 *  Registry table cells and Resource Class attributes.
 */

#define CT_SCN64_PREFIX		CT_PRI64_PREFIX

#define CT_SCNx64	CT_SCN64_PREFIX "x"

#ifdef __cplusplus
} // end extern "C"
#endif /* __cplusplus */

#endif	/* _H_CT */
