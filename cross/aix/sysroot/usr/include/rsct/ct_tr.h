/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999,2009          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/*===========================================================================*/
/*                                                                           */
/* Module Name:  ct_tr.h                                                     */
/*                                                                           */
/* Description:                                                              */
/*     Interface definitions for the Cluster Trace Facility                  */
/*                                                                           */
/*     This file is formatted to be viewed with tab stops set to 4.          */
/*===========================================================================*/
/* sccsid = "@(#)61   1.22   src/rsct/trace/ct_tr.h, trace, rsct_rhay53, rhay531006a 11/10/09 12:28:08" */

#ifndef _H_CT_TR
#define _H_CT_TR

#include <rsct/ct.h>
#include <rsct/ct_cu.h>
#include <stdarg.h>

/*---------------------------------------------------------------------------*/
/*  Cluster Trace API constants.                                             */
/*---------------------------------------------------------------------------*/

/*
 *  TR_VERSION identifies the version of the Cluster Utilities Application
 *  Programming Interface desired by a client.  If the client has not
 *  specified a particular version, version 1 is used.
 */

#ifndef TR_VERSION
#define TR_VERSION           1
#endif  /* TR_VERSION */

#define TR_MIN_FILE_SIZE    0x1000
#define TR_MAX_DATA_BLOCK   0x10

/*
 *  Platform ids for tr_query_platform() 
 */
#define TR_PLATFORM_UNKNOWN       	0
#define TR_PLATFORM_AIX_POWERPC   	1
#define TR_PLATFORM_LINUX_INTEL   	2
#define TR_PLATFORM_AIX_IA64      	3
#define TR_PLATFORM_LINUX_S390    	4
#define TR_PLATFORM_LINUX_POWERPC 	5
#define TR_PLATFORM_INTERIX_INTEL 	6
#define TR_PLATFORM_SOLARIS_INTEL 	7
#define TR_PLATFORM_SOLARIS_SPARC 	8

/*	Error code definitions	*/
#define TR_NUMBER_OF_CATEGORIES_INVALID      1
#define TR_COMPONENT_ID_MISSING              2
#define TR_CATEGORIES_MISSING                3
#define TR_DETAIL_LEVELS_MISSING             4
#define TR_CATEGORY_NAME_NULL                5
#define TR_CATEGORY_ID_TOO_BIG               6
#define TR_DEFAULT_LEVEL_TOO_BIG             7
#define TR_MINIMUM_LEVEL_TOO_BIG             8
#define TR_NOT_ABLE_TO_LOCK                  9
#define TR_TRACE_SPEC_COMPID_EXPECTED       10
#define TR_TRACE_SPEC_SEPARATOR_EXPECTED    11
#define TR_TRACE_SPEC_CATEGORY_EXPECTED     12
#define TR_TRACE_SPEC_DETAIL_LEVEL_EXPECTED 13
#define TR_MEMORY_ALLOCATION_FAILED         14
#define TR_TRACE_SPEC_COMPID_INVALID        15
#define TR_TRACE_SPEC_CATEGORY_INVALID      16
#define TR_FILENAME_INVALID                 17
#define TR_FILE_ERROR                       18
#define TR_FILE_STAT_ERROR                  19
#define TR_FILE_NOT_REGULAR_FILE            20
#define TR_COULD_NOT_MAP_FILE               21
#define TR_FILE_TRUNCATE_ERROR              22
#define TR_FILE_FCLEAR_ERROR                23
#define TR_FILESIZE_MODIFIED                24
#define TR_TRACE_NOT_ACTIVE                 25
#define TR_COMPONENT_NOT_REGISTERED         26
#define TR_STRING_MISSING                   27
#define TR_VSPRINTF_ERROR                   28
#define TR_TOO_MANY_DATA_BLOCKS             29
#define TR_INVALID_DATA_BLOCK               30
#define TR_INVALID_DATA_LENGTH              31
#define TR_FILE_MSYNC_ERROR                 32
#define TR_FORMAT_STRING_MISSING            33
#define TR_NUMBER_OF_STRINGS_INVALID        34
#define TR_FILE_NO_SPACE                    35
#define TR_NOT_TRACE_FILE                   36
#define TR_INVALID_TRACE_HANDLE             37
#define TR_COMPONENT_ID_IN_USE              38
#define TR_SPOOL_SPEC_ERROR                 39
#define TR_SPOOL_ON                         40
#define TR_SPOOL_OFF                        41
#define TR_SPOOL_REGCOMP_HDR_ERROR          42
#define TR_SPOOL_REGCOMP_FLD_ERROR          43
#define TR_SPOOL_REGCOMP_CMT_ERROR          44
#define TR_SPOOL_CONF_SYNTAX_ERROR          46
#define TR_SPOOL_CONF_ERROR                 47
#define TR_SPOOL_FILE_ERROR                 48
#define TR_FILE_WRITE_ERROR                 49
	
/* Data type definitions ------------------------------------------------------*/
 
typedef struct trace_anchor *tr_file_token_t;
/*
 * The following typedef is used to define an array that contains the current
 * level of detail for each category.  Each element of the array will represent
 * a category
 */
typedef unsigned char tr_detail_level_t;

/*
 * The following definition contains information necessary to describe a
 * trace category to the trace facility.  An array of these is passed to
 * tr_register_component().
 */
typedef struct tr_category_description {
	ct_uint32_t   category_id;             /* Index of element in level of detail array */
	                                       /*   that corresponds to the category.       */
	ct_char_t     *category_name;          /* Pointer to null terminated string that    */
                                           /*   is the category name.                   */
	ct_uint32_t   default_level_of_detail; /* Default level of detail for this category */
	ct_uint32_t   minimum_level_of_detail; /* Minimum level of detail                   */
} tr_category_description_t;

/*---------------------------------------------------------------------------*/
/*  Component anchor block for the tr_get_current_spooling_status API        */
/*---------------------------------------------------------------------------*/
typedef struct tr_mini_spooling_anchor {
  char fileName[PATH_MAX];
  char dest[PATH_MAX];
} tr_mini_spooling_anchor_t;

/*---------------------------------------------------------------------------*/
/*  Component anchor block for the tr_get_current_trace_levels API           */
/*---------------------------------------------------------------------------*/
typedef struct tr_mini_component_anchor {
	char                      compId[5];          /* Component identifier, NULL */
	                                              /*    terminated. */
	tr_detail_level_t         *pDetailLevels;     /* Ptr to level of detail array */
	int                       numberOfCategories; /* Number of categories in comp */
	tr_category_description_t *categories;        /* Ptr to category descriptions */
} tr_mini_component_anchor_t;

/*
 * The following typedef is for the handle associated with a trace file that
 * is open for query operations.
 */
typedef void * tr_query_handle_t;

/* Macro definitions ---------------------------------------------------------*/

/*! \brief Return file token */
#define tr_get_file_token(tokens,cat) tokens[cat]

/*
 * The following macro is used to determine if trace is enabled
 */
#define tr_check( level_array, category, lod ) \
         ( (lod) <= *(((unsigned char *)(level_array))+(category))) 

/*
 * The following macros provide backward compatibility with an earlier
 * version of the api.
 */
#define tr_record_int32( comp_id, trace_id, int1 )            \
        tr_record_values_32( comp_id, trace_id, 1, (ct_int32_t)(int1) )
	
#define tr_record_int32_2( comp_id, trace_id, int1, int2 )    \
        tr_record_values_32( comp_id, trace_id, 2, (ct_int32_t)(int1), (ct_int32_t)(int2) )
	
#define tr_record_uint32( comp_id, trace_id, int1 )           \
        tr_record_values_32( comp_id, trace_id, 1, (ct_uint32_t)(int1) )
	
#define tr_record_uint32_2( comp_id, trace_id, int1, int2 )   \
        tr_record_values_32( comp_id, trace_id, 2, (ct_uint32_t)(int1), (ct_uint32_t)(int2) )
	
#define tr_record_int64( comp_id, trace_id, int1 )            \
        tr_record_values_64( comp_id, trace_id, 1, (ct_int64_t)(int1) )
	
#define tr_record_int64_2( comp_id, trace_id, int1, int2 )    \
        tr_record_values_64( comp_id, trace_id, 2, (ct_int64_t)(int1), (ct_int64_t)(int2) )
	
#define tr_record_uint64( comp_id, trace_id, int1 )           \
        tr_record_values_64( comp_id, trace_id, 1, (ct_uint64_t)(int1) )
	
#define tr_record_uint64_2( comp_id, trace_id, int1, int2 )   \
        tr_record_values_64( comp_id, trace_id, 2, (ct_uint64_t)(int1), (ct_uint64_t)(int2) )

#define tr_record_string( comp_id, string )                   \
        tr_record_strings( comp_id, 0xffffffff, 1, string )
	
#define tr_record_vprintf( comp_id, format, arg_list )        \
        tr_record_vfmt_string( comp_id, 0xffffffff, format, arg_list )
/*
 *  The following macro definitions combine a check and a record that makes
 *	the code a little neater.
 */
#if 0
#ifndef TR_FILE_TOKENS
#define TR_FILE_TOKENS pTokens
#endif
#endif

#define tr_chk_record_id( category, lod, trace_id )                   \
        {                                                             \
            if ( tr_check( TR_DETAIL_LEVEL_ARRAY, category, lod ) )   \
                tr_record_id( TR_COMP_ID, trace_id );                 \
        }

#define tr_ms_chk_record_id( category, lod, trace_id )                   \
        {                                                             \
            if ( tr_check( TR_DETAIL_LEVEL_ARRAY, category, lod ) )   \
                tr_ms_record_id( TR_COMP_ID, trace_id, tr_get_file_token(TR_FILE_TOKENS, category) );                 \
        }

#define tr_chk_record_string( category, lod, trace_id, string )                \
        {                                                                      \
            if ( tr_check( TR_DETAIL_LEVEL_ARRAY, category, lod ) )            \
                tr_record_strings( TR_COMP_ID, trace_id, 1, (ct_char_t *)(string) );\
        }

#define tr_ms_chk_record_string( category, lod, trace_id, string )                \
        {                                                                      \
            if ( tr_check( TR_DETAIL_LEVEL_ARRAY, category, lod ) )            \
                tr_ms_record_strings( TR_COMP_ID, trace_id, tr_get_file_token(TR_FILE_TOKENS, category), 1, (ct_char_t *)(string) );\
        }

#define tr_chk_record_value_32( category, lod, trace_id, value )                \
        {                                                                       \
            if ( tr_check( TR_DETAIL_LEVEL_ARRAY, category, lod ) )             \
                tr_record_values_32( TR_COMP_ID, trace_id, 1, (ct_uint32_t)(value) );\
        }

#define tr_ms_chk_record_value_32( category, lod, trace_id, value )                \
        {                                                                       \
            if ( tr_check( TR_DETAIL_LEVEL_ARRAY, category, lod ) )             \
                tr_ms_record_values_32( TR_COMP_ID, trace_id, tr_get_file_token(TR_FILE_TOKENS, category), 1, (ct_uint32_t)(value) );\
        }

#define tr_chk_record_data1( category, lod, trace_id, pData, length )                           \
        {                                                                                       \
            if ( tr_check( TR_DETAIL_LEVEL_ARRAY, category, lod ) )                             \
                tr_record_data( TR_COMP_ID, trace_id, 1, (void *)(pData), (ct_uint32_t)(length) ); \
        }

#define tr_ms_chk_record_data1( category, lod, trace_id, pData, length )                           \
        {                                                                                       \
            if ( tr_check( TR_DETAIL_LEVEL_ARRAY, category, lod ) )                             \
                tr_ms_record_data( TR_COMP_ID, trace_id, tr_get_file_token(TR_FILE_TOKENS, category), 1, (void *)(pData), (ct_uint32_t)(length) ); \
        }

#define tr_chk_record_data2( category, lod, trace_id, pData1, length1, pData2, length2 )        \
        {                                                                                       \
            if ( tr_check( TR_DETAIL_LEVEL_ARRAY, category, lod ) )                             \
                tr_record_data( TR_COMP_ID, trace_id, 2, (void *)(pData1), (ct_uint32_t)(length1), (void *)(pData2), (ct_uint32_t)(length2) ); \
        }

#define tr_ms_chk_record_data2( category, lod, trace_id, pData1, length1, pData2, length2 )        \
        {                                                                                       \
            if ( tr_check( TR_DETAIL_LEVEL_ARRAY, category, lod ) )                             \
                tr_ms_record_data( TR_COMP_ID, trace_id, tr_get_file_token(TR_FILE_TOKENS, category), 2, (void *)(pData1), (ct_uint32_t)(length1), (void *)(pData2), (ct_uint32_t)(length2) ); \
        }
	
#define tr_chk_record_error( category, lod, trace_id, pFuncName, pErrorInfo )     \
        {                                                                         \
            if ( tr_check( TR_DETAIL_LEVEL_ARRAY, category, lod ) )               \
                tr_record_error( TR_COMP_ID, trace_id, pFuncName, __LINE__, __FILE__, pErrorInfo );\
        }		

#define tr_ms_chk_record_error( category, lod, trace_id, pFuncName, pErrorInfo )     \
        {                                                                         \
            if ( tr_check( TR_DETAIL_LEVEL_ARRAY, category, lod ) )               \
                tr_ms_record_error( TR_COMP_ID, trace_id, tr_get_file_token(TR_FILE_TOKENS, category), pFuncName, __LINE__, __FILE__, pErrorInfo );\
        }		
	
/*
 *  The following macros convert references to the generic names of Trace API
 *  routines, like tr_register_component(), to references to version specific
 *  Trace API routines, like tr_register_component_1(). The version used during
 *  conversion is determined by the value of TR_VERSION.  Note that these
 *  macros can deal with the different versions of a routine having different
 *  arguments.
 */

#define tr_register_component                                           \
	TR_ROUTINE_VERSION(tr_register_component, TR_VERSION)

#define tr_ms_register_component                                           \
	TR_ROUTINE_VERSION(tr_ms_register_component, TR_VERSION)
	
#define tr_unregister_component                                         \
	TR_ROUTINE_VERSION(tr_unregister_component, TR_VERSION)

#define tr_set_size                                                     \
	TR_ROUTINE_VERSION(tr_set_size, TR_VERSION)

#define tr_get_size                                                     \
	TR_ROUTINE_VERSION(tr_get_size, TR_VERSION)

#define tr_set_file_size                                                     \
	TR_ROUTINE_VERSION(tr_set_file_size, TR_VERSION)

#define tr_get_file_size                                                     \
	TR_ROUTINE_VERSION(tr_get_file_size, TR_VERSION)
	
#define tr_set_filename                                                 \
	TR_ROUTINE_VERSION(tr_set_filename, TR_VERSION)

#define tr_get_filename                                                 \
	TR_ROUTINE_VERSION(tr_get_filename, TR_VERSION)

#define tr_set_file_map                                                 \
	TR_ROUTINE_VERSION(tr_set_file_map, TR_VERSION)
	
#define tr_flush                                                        \
	TR_ROUTINE_VERSION(tr_flush, TR_VERSION)
	
#define tr_set_trace_levels                                             \
	TR_ROUTINE_VERSION(tr_set_trace_levels, TR_VERSION)
	
#define tr_record_id                                                    \
	TR_ROUTINE_VERSION(tr_record_id, TR_VERSION)

#define tr_ms_record_id                                                    \
	TR_ROUTINE_VERSION(tr_ms_record_id, TR_VERSION)

#define tr_record_strings                                               \
	TR_ROUTINE_VERSION(tr_record_strings, TR_VERSION)

#define tr_ms_record_strings                                               \
	TR_ROUTINE_VERSION(tr_ms_record_strings, TR_VERSION)

#define tr_record_strings_v                                             \
	TR_ROUTINE_VERSION(tr_record_strings_v, TR_VERSION)

#define tr_ms_record_strings_v                                             \
	TR_ROUTINE_VERSION(tr_ms_record_strings_v, TR_VERSION)

#define tr_record_fmt_string                                            \
	TR_ROUTINE_VERSION(tr_record_fmt_string, TR_VERSION )

#define tr_ms_record_fmt_string                                            \
	TR_ROUTINE_VERSION(tr_ms_record_fmt_string, TR_VERSION )

#define tr_record_vfmt_string                                           \
	TR_ROUTINE_VERSION(tr_record_vfmt_string, TR_VERSION)

#define tr_ms_record_vfmt_string                                           \
	TR_ROUTINE_VERSION(tr_ms_record_vfmt_string, TR_VERSION)
	
#define tr_record_printf                                                \
	TR_ROUTINE_VERSION(tr_record_printf, TR_VERSION)

#define tr_record_data                                                  \
	TR_ROUTINE_VERSION(tr_record_data, TR_VERSION)

#define tr_ms_record_data                                                  \
	TR_ROUTINE_VERSION(tr_ms_record_data, TR_VERSION)

#define tr_record_data_v                                                \
	TR_ROUTINE_VERSION(tr_record_data_v, TR_VERSION)

#define tr_ms_record_data_v                                                \
	TR_ROUTINE_VERSION(tr_ms_record_data_v, TR_VERSION)

#define tr_record_values_32                                             \
	TR_ROUTINE_VERSION(tr_record_values_32, TR_VERSION)

#define tr_ms_record_values_32                                             \
	TR_ROUTINE_VERSION(tr_ms_record_values_32, TR_VERSION)
	
#define tr_record_values_32_v                                           \
	TR_ROUTINE_VERSION(tr_record_values_32_v, TR_VERSION)

#define tr_ms_record_values_32_v                                           \
	TR_ROUTINE_VERSION(tr_ms_record_values_32_v, TR_VERSION)
	
#define tr_record_values_64                                             \
	TR_ROUTINE_VERSION(tr_record_values_64, TR_VERSION)

#define tr_ms_record_values_64                                             \
	TR_ROUTINE_VERSION(tr_ms_record_values_64, TR_VERSION)

#define tr_record_values_64_v                                           \
	TR_ROUTINE_VERSION(tr_record_values_64_v, TR_VERSION)	

#define tr_ms_record_values_64_v                                           \
	TR_ROUTINE_VERSION(tr_ms_record_values_64_v, TR_VERSION)	

#define tr_record_error                                                 \
    TR_ROUTINE_VERSION(tr_record_error, TR_VERSION)

#define tr_ms_record_error                                                 \
    TR_ROUTINE_VERSION(tr_ms_record_error, TR_VERSION)

#define tr_open_query                                                   \
    TR_ROUTINE_VERSION(tr_open_query, TR_VERSION)

#define tr_close_query                                                  \
    TR_ROUTINE_VERSION(tr_close_query, TR_VERSION)

#define tr_query_pid                                                    \
    TR_ROUTINE_VERSION(tr_query_pid, TR_VERSION)

#define tr_query_prog                                                   \
    TR_ROUTINE_VERSION(tr_query_prog, TR_VERSION)

#define tr_query_platform                                               \
    TR_ROUTINE_VERSION(tr_query_platform, TR_VERSION)

#define tr_get_current_trace_levels										\
    TR_ROUTINE_VERSION(tr_get_current_trace_levels, TR_VERSION)

#define tr_release_comp_info											\
    TR_ROUTINE_VERSION(tr_release_comp_info, TR_VERSION)

#define tr_get_current_spooling_status								    \
    TR_ROUTINE_VERSION(tr_get_current_spooling_status, TR_VERSION)

#define tr_release_spool_info											\
    TR_ROUTINE_VERSION(tr_release_spool_info, TR_VERSION)

#define tr_core_event													\
    TR_ROUTINE_VERSION(tr_core_event, TR_VERSION)

#define tr_copy_file													\
    TR_ROUTINE_VERSION(tr_copy_file, TR_VERSION)

#define tr_get_spool_dir												\
    TR_ROUTINE_VERSION(tr_get_spool_dir, TR_VERSION)

#define TR_ROUTINE_VERSION(routine, version)                            \
    TR_ROUTINE_VERSION_GLUE(routine, version)

#define TR_ROUTINE_VERSION_GLUE(routine, version)                       \
    routine ## _ ## version

#define tr_configure                                               \
    TR_ROUTINE_VERSION(tr_configure, TR_VERSION)

/*---------------------------------------------------------------------------*/
/*  Trace Facility API function prototypes - Version 1                       */
/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * Function prototypes for functions intended for Trace Facility API clients.
 * Clients should use the generic routine names defined by macros included
 * in this header file, such as tr_register_component(),  instead of the version
 * specific routine names, like tr_register_component_1().  Those macros
 * convert the generic names to the appropriate version specific names.
 */

#if (TR_VERSION == 1) || defined(TR_ALL_VERSIONS)

extern ct_int32_t
tr_register_component_1(
	const ct_char_t           component_id[4],       /* 4 Character id string */
	tr_detail_level_t         *detail_levels,        /* Array of level of detail holders */
	const tr_category_description_t *category_description, /* Array of category descs. */
	const ct_uint32_t         number_of_categories         /* Number of categories */
);									

extern ct_int32_t
tr_ms_register_component_1(
	const ct_char_t           component_id[4],       /* 4 Character id string */
	tr_detail_level_t         *detail_levels,        /* Array of level of detail holders */
	const tr_category_description_t *category_description, /* Array of category descs. */
	const ct_uint32_t         number_of_categories,        /* Number of categories */
	tr_file_token_t           **file_tokens
);									

extern ct_int32_t
tr_unregister_component_1(
	const ct_char_t           component_id[4]       /* 4 Character id string */
);

extern ct_int32_t
tr_set_size_1(
	const ct_uint32_t        size                  /* Size of trace file */
);

extern ct_int32_t
tr_set_file_size_1(
	const ct_char_t          *trace_file_name,
	const ct_uint32_t        size                  /* Size of trace file */
);

extern ct_int32_t
tr_get_file_size_1(
	const ct_char_t          *trace_file_name,
	ct_uint32_t        		 *size                 /* Size of trace file */
);

extern ct_int32_t
tr_get_size_1(
	ct_uint32_t              *pSize                /* Size of trace file */
);
	
extern ct_int32_t
tr_set_filename_1(
	const ct_char_t        *filename               /* File name to write trace records */
);
	
extern ct_int32_t
tr_get_filename_1(
	ct_char_t              *filename                /* File that trace records are being */
);                                                 /*   written to. */

extern ct_int32_t
tr_flush_1();   

extern ct_int32_t
tr_set_trace_levels_1(
	const ct_char_t        *trace_spec            /* String specifying new levels of  */
                                               	   /* detail for one or more categories */
                                                   /* of one or more components */
);

extern ct_int32_t
tr_set_file_map_1(
        const ct_char_t        *trace_filename,    /* file name */
	const ct_char_t        *trace_spec         /* String specifying new levels of */
                                               	   /* detail for one or more categories */
                                                   /* of one or more components */
);
	
extern ct_int32_t
tr_record_id_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        traceid               /* Id to add to record */
);

extern ct_int32_t
tr_ms_record_id_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        traceid,              /* Id to add to record */
	const tr_file_token_t	 fileToken	       /* the trace file */
);

extern ct_int32_t
tr_record_strings_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_uint32_t        number,               /* Number of strings to follow */
    ...
);

extern ct_int32_t
tr_ms_record_strings_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const tr_file_token_t	 fileToken,	       /* the trace file */
	const ct_uint32_t        number,               /* Number of strings to follow */
    ...
);

extern ct_int32_t
tr_record_strings_v_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_uint32_t        number,               /* Number of strings to follow */
    va_list                  arg
);

extern ct_int32_t
tr_ms_record_strings_v_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const tr_file_token_t	 fileToken,	       /* the trace file */
	const ct_uint32_t        number,               /* Number of strings to follow */
    va_list                  arg
);
	
extern ct_int32_t
tr_record_fmt_string_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_char_t          *format,              /* sprintf style format */
	...
);

extern ct_int32_t
tr_ms_record_fmt_string_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const tr_file_token_t	 fileToken,	       /* the trace file */
	const ct_char_t          *format,              /* sprintf style format */
	...
);
	
extern ct_int32_t
tr_record_vfmt_string_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_char_t          *format,              /* sprintf style format */
	const va_list            parms
);

extern ct_int32_t
tr_ms_record_vfmt_string_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const tr_file_token_t	 fileToken,	       /* the trace file */
	const ct_char_t          *format,              /* sprintf style format */
	const va_list            parms
);
		
extern ct_int32_t
tr_record_data_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_uint32_t        number_of_blocks,     /* Number of data blocks to follow */
	...
);

extern ct_int32_t
tr_ms_record_data_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const tr_file_token_t	 fileToken,	       /* the trace file */
	const ct_uint32_t        number_of_blocks,     /* Number of data blocks to follow */
	...
);

extern ct_int32_t
tr_record_data_v_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_uint32_t        number_of_blocks,     /* Number of data blocks to follow */
	va_list                  args
);

extern ct_int32_t
tr_ms_record_data_v_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const tr_file_token_t	 fileToken,	       /* the trace file */
	const ct_uint32_t        number_of_blocks,     /* Number of data blocks to follow */
	va_list                  args
);

extern ct_int32_t
tr_record_values_32_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_uint32_t        number,               /* Number of integers to follow */
	...
);

extern ct_int32_t
tr_ms_record_values_32_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const tr_file_token_t	 fileToken,	       /* the trace file */
	const ct_uint32_t        number,               /* Number of integers to follow */
	...
);

extern ct_int32_t
tr_record_values_32_v_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_uint32_t        number,               /* Number of integers to follow */
	va_list                  args 
);	

extern ct_int32_t
tr_ms_record_values_32_v_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const tr_file_token_t	 fileToken,	       /* the trace file */
	const ct_uint32_t        number,               /* Number of integers to follow */
	va_list                  args 
);	
    		
extern ct_int32_t
tr_record_values_64_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_uint32_t        number,               /* Number of integers to follow */
	...
);

extern ct_int32_t
tr_ms_record_values_64_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const tr_file_token_t	 fileToken,	       /* the trace file */
	const ct_uint32_t        number,               /* Number of integers to follow */
	...
);

extern ct_int32_t
tr_record_values_64_v_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_uint32_t        number,               /* Number of integers to follow */
	va_list                  args
);

extern ct_int32_t
tr_ms_record_values_64_v_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const tr_file_token_t	 fileToken,	       /* the trace file */
	const ct_uint32_t        number,               /* Number of integers to follow */
	va_list                  args
);
	
extern ct_int32_t
tr_record_error_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_Id,             /* Trace identifier */
	const ct_char_t          *pFuncName,           /* Function name that produced error */
	const ct_uint32_t        lineNumber,           /* Line number called from */
	const ct_char_t          *pFileName,           /* Filename called from */
	cu_error_t               **pErrorInfo          /* Optional error info */
);

extern ct_int32_t
tr_ms_record_error_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_Id,             /* Trace identifier */
	const tr_file_token_t	 fileToken,	           /* the trace file */
	const ct_char_t          *pFuncName,           /* Function name that produced error */
	const ct_uint32_t        lineNumber,           /* Line number called from */
	const ct_char_t          *pFileName,           /* Filename called from */
	cu_error_t               **pErrorInfo          /* Optional error info */
);

extern int
tr_get_current_trace_levels_1(
	int *componentCount,	       		            /* Output parameter */
	tr_mini_component_anchor_t **components         /* Output parameter */
);

extern void
tr_release_comp_info_1(
	const int componentCount,	    	           /* Input parameter */
	tr_mini_component_anchor_t *components         /* Input parameter, free'd recursively */
);

extern int
tr_get_current_spooling_status_1(
	int *cnt,
	tr_mini_spooling_anchor_t **spa
);

extern void
tr_release_spool_info_1(
	int cnt,
	tr_mini_spooling_anchor_t *spa
);

extern int
tr_core_event_1(
	const char *trc_file,
	const char* message);

extern const char *
tr_get_spool_dir_1(
	const char *trc_file);

extern int
tr_copy_file_1(
	const char *dest,
	const char *file_name,
	      int   del);
  
/* Supported for backward compatibility ONLY */

extern ct_int32_t
tr_record_string_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_char_t          *string               /* Null terminated string to record */
);
	
extern ct_int32_t
tr_record_printf_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_char_t          *format,              /* sprintf style format */
	...
);

extern ct_int32_t
tr_record_vprintf_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_char_t          *format,              /* sprintf style format */
	const va_list            parms
);

extern ct_int32_t
tr_record_int32_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_int32_t         integer               /* Data value to record */
);

extern ct_int32_t
tr_record_int32_2_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_int32_t         integer1,             /* Number of data blocks to follow */
	const ct_int32_t         integer2              /* Data value to record */
);

extern ct_int32_t
tr_record_uint32_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_uint32_t        integer               /* Data value to record */
);

extern ct_int32_t
tr_record_uint32_2_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_uint32_t        integer1,             /* Number of data blocks to follow */
	const ct_uint32_t        integer2              /* Data value to record */
);

extern ct_int32_t
tr_record_int64_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_int64_t         integer               /* Data value to record */
);

extern ct_int32_t
tr_record_int64_2_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_int64_t         integer1,             /* Number of data blocks to follow */
	const ct_int64_t         integer2              /* Data value to record */
);

extern ct_int32_t
tr_record_uint64_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_uint64_t        integer               /* Data value to record */
);

extern ct_int32_t
tr_record_uint64_2_1(
	const ct_char_t          component_id[4],      /* 4 Character id string */
	const ct_uint32_t        trace_id,             /* Trace identifier */
	const ct_uint64_t        integer1,             /* Number of data blocks to follow  */
	const ct_uint64_t        integer2              /* Data value to record */
);

extern ct_int32_t
tr_open_query_1(
	const ct_char_t          *file_name,           /* Name of trace file */
	tr_query_handle_t        *handle_p             /* Ptr to location to return handle */
);

extern ct_int32_t
tr_close_query_1(
	tr_query_handle_t        handle                /* Handle for open trace file */
);

extern ct_int32_t
tr_query_pid_1(
	tr_query_handle_t        handle,               /* Handle for open trace file */
	pid_t                    *pid_p
);

extern ct_int32_t
tr_query_prog_1(
	tr_query_handle_t        handle,               /* Handle for open trace file */
	char                     **progname_p          /* Ptr to loc to store allocated name */
);

extern ct_int32_t
tr_query_platform_1(
	tr_query_handle_t        handle,               /* Handle for open trace file */
	ct_uint32_t              *platform_p           /* Ptr to loc to store allocated name */
);

extern void tr_term();							   /* Normally, an atexit() function. */

extern void tr_configure_1();
  
#endif /* (TR_VERSION == 1) || defined(TR_ALL_VERSIONS) */

#ifdef __cplusplus
} // end extern "C"
#endif /* __cplusplus */

#endif	/* _H_CT_TR */
/* vi:set ts=4: */
