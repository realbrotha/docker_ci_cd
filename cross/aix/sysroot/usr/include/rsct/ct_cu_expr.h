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
/* Module Name:  ct_cu_expr.h                                                */
/*                                                                           */
/* Description:                                                              */
/*     Interface definitions for the expression related Cluster Utilities.   */
/*                                                                           */
/*     This file is formatted to be viewed with tab stops set to 4.          */
/*===========================================================================*/
/* @(#)36   1.6   src/rsct/utils/ct_cu_expr.h, common_utils, rsct_rhay53, rhay531006a 10/20/08 21:47:17 */

#ifndef _H_CT_CU_EXPR
#define _H_CT_CU_EXPR

    
#include <rsct/ct_cu.h>
#include <rsct/ct_pmsg.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*---------------------------------------------------------------------------*/
/*  Cluster Utilities API constants.                                         */
/*---------------------------------------------------------------------------*/

/*
 *  CU_VERSION identifies the version of the Cluster Utilities Application
 *  Programming Interface desired by a client.  The default value is defined
 *  by ct_cu.h.
 */

/*	Error code definitions are defined in ct_cu.h */

/*
 *  The following macros convert references to the generic names of CUAPI
 *  routines, like cu_rsrc_is_dependent(), to references to version specific
 *  CUAPI routines, like cu_rsrc_is_dependent_1(). The version used during
 *  conversion is determined by the value of CU_VERSION.  Note that these
 *  macros can deal with the different versions of a routine having different
 *  arguments.
 */

#define cu_comp_expr                                                     \
    CU_ROUTINE_VERSION(cu_comp_expr, CU_VERSION)

#define cu_free_expr                                                     \
    CU_ROUTINE_VERSION(cu_free_expr, CU_VERSION)
    
#define cu_exec_expr                                                     \
    CU_ROUTINE_VERSION(cu_exec_expr, CU_VERSION)

#define cu_probe_expr                                                    \
    CU_ROUTINE_VERSION(cu_probe_expr, CU_VERSION)
    
#define cu_get_expr_props                                                \
    CU_ROUTINE_VERSION(cu_get_expr_props, CU_VERSION)

#define cu_same_expr                                                     \
    CU_ROUTINE_VERSION(cu_same_expr, CU_VERSION)

#define cu_expand_expr                                                      \
    CU_ROUTINE_VERSION(cu_expand_expr, CU_VERSION)

#define cu_flush_cached_constant                                            \
    CU_ROUTINE_VERSION(cu_flush_cached_constant, CU_VERSION)

/*---------------------------------------------------------------------------*
 *  The following data types are used by the cu_xxxx_expr functions.      
 *---------------------------------------------------------------------------*/

/* The following values may be used for the options parameter of cu_comp_expr(), */
/* cu_exec_expr() and cu_free_expr() functions.                                  */
#define CU_EXPR_NO_OPTIONS  0
#define CU_EXPR_MEM_FUNCS   1
#define CU_EXPR_ALLOW_AT    2
#define CU_EXPR_ALLOW_SUBST 4
#define CU_EXPR_API_FORMAT  8
#define CU_EXPR_BASE_ADDR   16
#define CU_EXPR_MAP_VAR     32
#define CU_EXPR_ENCODED_IDS 64
#define CU_COMP_ALL_OPTS (CU_EXPR_MEM_FUNCS | CU_EXPR_API_FORMAT | CU_EXPR_ALLOW_AT | \
                          CU_EXPR_ALLOW_SUBST)
#define CU_EXEC_ALL_OPTS (CU_EXPR_MEM_FUNCS | CU_EXPR_API_FORMAT | CU_EXPR_BASE_ADDR | \
                          CU_EXPR_MAP_VAR | CU_EXPR_ENCODED_IDS)
#define CU_FREE_ALL_OPTS (CU_EXPR_MEM_FUNCS)
#define CU_PROBE_ALL_OPTS (CU_EXPR_MEM_FUNCS | CU_EXPR_API_FORMAT)
    
/*
 *   The following constant is passed to cu_validate_callback() if the
 *   information is being requested for the top level variable.  i.e. not
 *   the element of an SD.
 */ 
#define CU_EXPR_NO_PARENT  0xffffffff
/*
 *  Optional specification of memory allocation functions to be
 *  used by the cu_xxxx_expr utilities.
 */
typedef struct cu_mem_funcs {
    void *(*p_malloc)( size_t );
    void (*p_free)(void *);
    void *(*p_realloc)(void *, size_t);
} cu_mem_funcs_t;

/*
 * Data that is returned by the validate callback
 */
typedef struct cu_validate_data {
    ct_data_type_t      type;
    ct_uint32_t         id;
} cu_validate_data_t;

/*
 * Translation callback functions 
 */
typedef char *(*map_id_to_name_cb)( void           *token,
                                    ct_uint32_t    id,
                                    ct_uint32_t    parent_id,
                                    ct_data_type_t type );

typedef int (*trans_literal_value_cb)( void           *token,
                                       ct_uint32_t    *ids,
                                       ct_uint32_t    num_ids,
                                       ct_data_type_t orig_type,
                                       ct_value_t     *p_orig_value,
                                       ct_data_type_t *p_trans_type,
                                       ct_value_t     *p_trans_value );

typedef void (*free_literal_value_cb)( void           *token,
                                       ct_data_type_t type,
                                       ct_value_t     *p_trans_value );
    
/*
 * The following structure that may be passed to cu_exec_expr to map the
 * ids in compiled expression and/or override the normal variable resolution.
 *
 * If this structure is passed in as a variable parameter, the resolution
 * of a variable reference will be augumented as follows:
 *
 *   1. The variable id assigned at compilation time will be used to
 *      index this array.
 *   2. If the mapped_id field in the corresponding entry is >= 0 then
 *      it will replace the variable id and normal lookup will continue
 *      in the ct_value_t array that was passed to cu_exec_expr().
 *   3. If the mapped_id field contains -1 then p_value will be used
 *      as the pointer to the value (not ct_value_t) and the ct_value_t
 *      input array will not be referenced for this variable.
 *   4. If the mapped_id field contains -2 then an error will be
 *      generated.
 *
 *  This mapping is useful when multiple records must be searched that
 *  have varying formats and fields. 
 *
 */
typedef struct cu_variable_override {
    ct_int32_t  mapped_id;
    void        *p_value;
} cu_variable_override_t;
    

/* an array of elements of the type cu_variable_map_t may be passed
 * to cu_exec_expr to map "encoded" ids in compiled expressions to
 * to their corresponding ct_value_t values. Encoded IDs support
 * the gathering of value arrays located in sets of arbitrary objects,
 * where each set has its own variable ID space. Each set is assumed
 * to have the same type of objects, but the objects may differ
 * between sets. In other words, each object in the set contains
 * an array of up to 16 ct_value_t and each object in the set has
 * a corresponding 0 based variable identifier. The array of
 * ct_value_t support the notion that a variable may be "qualified"
 * to express a different value (use of CU_EXPR_ALLOW_AT).
 *
 * When an expression is compiled all the IDs returned may be
 * encoded as follows:
 *
 *   3      2  2      1  1
 *   1      4  3      6  5      8  7      0
 *   0xxxxxxx  xxxxxxxx  xxxxxxxx  vvvvssss
 *                                     ^^^^     set index
 *                                 ^^^^         value index
 *    ^^^^^^^  ^^^^^^^^  ^^^^^^^^               object index
 *
 *    Bits  3 - 0   set index
 *    Bits  7 - 4   value index
 *    Bits 30 - 8   index to pointer to object
 *    Bit  31       must be zero
 *
 * If a pointer to a variable map array is passed to cu_exec_expr,
 * the resolution of a variable reference is:
 *
 *   1. The variable ID assigned at compilation time is decoded
 *      into the set index, value index and object index.
 *   2. The set index is used to index into the variable map
 *      array to find the corresponding variable map structure.
 *   3. The object index is used to index into the pointer
 *      array specified by pp_object, to obtain the object
 *      pointer.
 *   4. The values_offset is then added to the object pointer
 *      (cast to char *) to get a pointer to the ct_value_t
 *      array (cast to ct_value_t *).
 *   5. Finally, the value index is used to index into the
 *      ct_value_t array to fetch the value.
 *
 * The object_p_count value is provided for error checking.
 */

typedef struct cu_variable_map {
    void           **pp_object;
    ct_uint32_t    object_p_count;
    ct_uint32_t    values_offset;
} cu_variable_map_t;

/* the CU_SET_ENCODED_ID macro can be used to create an encoded variable ID
 *
 * Arguments:  s => set index
 *             v => value index
 *             o => object index
 *
 * Return value: encoded variable ID of type ct_uint32_t
 */

#define CU_SET_ENCODED_ID(s, v, o) \
    (ct_uint32_t)( ((ct_uint32_t)(s) & 0x0000000f)       | \
                  (((ct_uint32_t)(v) & 0x0000000f) << 4) | \
                  (((ct_uint32_t)(o) & 0x007fffff) << 8) )

/* Macros to decode an encoded variable ID
 *
 * Argument:  n => encoded variable ID of type ct_uint32_t
 */

#define CU_SET_IDX_FROM_EID(n)   ((n) & 0x0000000f)
#define CU_VAL_IDX_FROM_EID(n) ( ((n) & 0x000000f0) >> 4 )
#define CU_OBJ_IDX_FROM_EID(n) ( ((n) & 0x7fffff00) >> 8 )


/*
 *  Types of lists returned by cu_probe_expr_t()
 */
typedef enum {
    INCLUSION_LIST=0,
    EXCLUSION_LIST=1
} cu_list_type_t;

/*
 *   Data structure returned by cu_probe_expr()
 */

typedef struct cu_probe_result {
    cu_list_type_t  list_type;   /* Type of list -- inclusion or exclusion */
    ct_data_type_t  data_type;   /* Datatype of values in list             */
    union {                      /* Array of values or ranges              */
        ct_pmsg_array_t pmsg;    /*    in protocol format                  */
        ct_array_t      api;     /*    in api format                       */
    } array;
} cu_probe_result_t;

/*
 * Callback function that is invoked by the cu_comp_expr function to
 * validate a variable name or the name of an structured data element.
 * This call back returns the data type of the specified variable and
 * an id for it.
 *
 *     token - provided by caller of cu_comp_expr() and passed through
 *
 *     p_name - pointer to name to be validated.  This may be the
 *              name of an attribute if parent_id is 0xffffffff or the
 *              name of an element.  In the later case, the parent_id
 *              refers to the structured data or structured data array
 *              variable that was assigned this id via a previous call
 *              to this function.
 *
 *     length - length of name to be validated.   
 *
 *     parent_id - If not CU_EXPR_NO_PARENT, this value identifies the variable
 *              that contains the element identified by p_name.  This id was 
 *              returned by a previous call to this function with the
 *              parent_id set to 0xffffffff.   A value of 0xffffffff indicates
 *              that p_name is the name of a top level variable, not an
 *              element of an SD.
 *
 *     p_return_data - Points to memory into which the data type and an id
 *              for the attribute or element is to be returned.  These values
 *              must be set by the callback routine.
 *
 *   Returns:
 *      0 = Name is valid and its data type and id are returned in p_return_data.
 *     !0 = The name is not valid. 
 *
 */
typedef ct_int32_t (*cu_validate_callback)( void               *token,
                                            ct_char_t          *p_name,
                                            ct_uint32_t        length, 
                                            ct_uint32_t        parent_id,
                                            cu_validate_data_t *p_return_data );


/*---------------------------------------------------------------------------*/
/*  Cluster Utilites API function prototypes - Version 1                     */
/*---------------------------------------------------------------------------*/

/*
 * Function prototypes for functions intended for Cluster Utilities API clients.
 * Clients should use the generic routine names defined by macros included
 * in this header file, such as cu_comp_expr(), instead of the version
 * specific routine names, like cu_comp_expr_1().  Those macros convert
 * the generic names to the appropriate version specific names.
 */

#if (CU_VERSION == 1) || defined(CU_ALL_VERSIONS)

/*
 * cu_comp_expr -  This function will compile an expression contained in pString.
 *                 The result of the compilation will be suitable for passing to
 *                 cu_exec_expr() for execution of the expression. 
 *
 *      p_string - pointer to the null terminated string to be compiled.
 *
 *      options - bitmask that controls how the compilation is to be performed. Any
 *                of the following values may be bitwise Or'd together:
 *
 *           CU_EXPR_MEM_FUNCS - The first optional parameter points to a structure of
 *                               type cu_mem_funcs which contains pointers to the
 *                               memory allocation functions equivalent to malloc(), free(),
 *                               and realloc().
 *
 *           CU_EXPR_API_FORMAT - Any indirect data is interpreted according to the ct_value_t
 *                               and related data structures.  If this options is not set,
 *                               all indirect data is interpreted as protocol format
 *                               (ct_pmsg_value_t... ).
 *
 *           CU_EXPR_ALLOW_AT  - Allow the character '@' in symbols.
 *
 *           CU_EXPR_ALLOW_SUBST - Allow the character '$' as the first character of symbols.
 *
 *      validate_cb - function provided by caller that is invoked to validate variable
 *                    names and to return the variable's type and an id.
 *
 *      token       - opaque data item that is provided by called to be passed to
 *                    each invocation of the validate_cb.
 *
 *      p_comp_expr - points to a memory location into which the address of the
 *                    compiled expression will be stored.  If this parameter is NULL,
 *                    the expression will only be validated and no compiled
 *                    expression will be returned.
 *
 *      p_mem_funcs - (optional) points to a list of memory function addresses to be used
 *                    in allocating and freeing memory. This parameter is optional and
 *                    is only used when the CU_EXPR_MEM_FUNCS option is specified. 
 *
 */
extern
ct_int32_t cu_comp_expr_1( char                 *p_string,
                           ct_uint32_t          options,
                           cu_validate_callback validate_cb,
                           void                 *token,
                           void                 **p_comp_expr,
                           ... );

/*
 *  cu_exec_expr  - This function executes an expression that was compiled by
 *                  cu_comp_expr() and returns the result as a ct_uint32_t. 
 *
 *    p_comp_expr - pointer to the compiled expression that was returned by cu_comp_expr().
 *
 *    options     - bitmask that controls how the execution is to be performed. Any
 *                  of the following values may be bitwise Or'd together:
 *
 *           CU_EXPR_MEM_FUNCS - The first optional parameter points to a structure of
 *                               type cu_mem_funcs which contains pointers to the
 *                               memory allocation functions equivalent to malloc(), 
 *                               free() and realloc().
 *
 *           CU_EXPR_BASE_ADDR - If this option is specified, an optional parameter of type
 *                               void * is expected following the optional parameter for
 *                               CU_EXPR_MEM_FUNCS, if specified.  This parameter is used as
 *                               the base address to be added to all ptr_xxxx fields within
 *                               the values list. This option is mutually exclusive of
 *                               CU_EXPR_ENCODED_IDS.
 *
 *           CU_EXPR_ENCODED_IDS - If this option is specified, an optional parameter of type
 *                                 cu_variable_map_t * is expected following the optional parameter
 *                                 for CU_EXPR_MEM_FUNCS, if specified.  This parameter is 
 *                                 a pointer to a variable map array. This option is mutually
 *                                 exclusive of CU_EXPR_BASE_ADDR. If this option is specified
 *                                the compiled expression must contain encoded variable IDs.
 *
 *           CU_EXPR_API_FORMAT - Any indirect data is interpreted according to the ct_value_t
 *                               and related data structures.  If this options is not set,
 *                               all indirect data is interpreted as protocol format
 *                               (ct_pmsg_value_t... ).  It this option was specified when
 *                               compiling the expression, then it must be specified on this
 *                               function as well. 
 *
 *    values      - is an array of ct_value_t structures.  The number of items in this array
 *                  must be equal to the largest id plus 1 used in the expression.   The ids
 *                  were provided by the validate_callback during the compilation of the
 *                  expression.  If the ct_value_t corresponds to an indirect data type,
 *                  the CU_EXPR_BASE_ADDR option determines how the ptr_xxxx field is
 *                  interpreted.  If the CU_EXPR_BASE_ADDR parameter is not specified, the
 *                  ptr_xxxx field is used as an absolute address.  If the CU_EXPR_BASE_ADDR
 *                  option is specified, the ptr_xxxx field is interpreted as an offset
 *                  relative to the optional parameter "base_addr".
 *
 *                  Any indirect data may be specified either in API format (i.e. ct_value_t)
 *                  or in protocol format (i.e. ct_pmsg_value_t). The main difference is the
 *                  the handling of pointers fields to other indirect data.  If the API
 *                  format is selected via the option CU_EXPR_API_FORMAT, all ptr_xxx fields
 *                  will be treated as absolute addresses.  If the protocol format is
 *                  selected by omitting the CU_EXPR_API_FORMAT option, ct_pmsg_xxx structures
 *                  will be used which represent indirect data as offset relative to the
 *                  beginning of the containing data item.  Also, on some platforms, the
 *                  size of the protocol structures may be different than the API format.
 *                  Typically, the protocol format is only used if the caller is using the
 *                  protocol utilites for packing and unpacking values. 
 *
 *                  This argument must be NULL if CU_EXPR_ENCODED_IDS is set.
 *
 *    number_of_values - this parameters specifies the number of elements that are in the
 *                  values array.  It must be greater than the largest id plus one used in
 *                  the expression. Or, if the CU_EXPR_ENCODED_IDS option is specified, it
 *                  specified the number of elements in the variable map array.
 *
 *    p_result -    specifies the address of a variable of type ct_uint32_t into which the
 *                  result of executing the expression will be stored. 
 *
 *    p_mem_funcs - (optional) points to a list of memory function addresses to be used
 *                  in allocating and freeing memory. This parameter is optional and
 *                  is only used when the CU_EXPR_MEM_FUNCS option is specified. 
 *
 *    base_addr   - (optional) contains the base address of any indirect data referred to 
 *                  by the elements in the values array.  However, this base address is
 *                  not used to interpret the content of the indirect data since that is
 *                  controlled by the CU_EXPR_API_FORMAT option. 
 *
 *    var_map     - (optional) points to a variable map array if the CU_EXPR_ENCODED_IDS
 *                  option is set.
 */

extern
ct_int32_t cu_exec_expr_1( void                   *p_comp_expr,
                           ct_uint32_t            options,
                           ct_value_t             values[],
                           ct_uint32_t            number,
                           ct_uint32_t            *p_result, ... );
/*
 * cu_free_expr - frees any storage associated with the compiled expression
 *                that was returned by cu_comp_expr().
 *
 *
 *   p_comp_expr - pointer to the compiled expression that was returned by cu_comp_expr().
 *
 *
 *   options     - bitmask that controls how the operation is to be performed.
 *
 *           CU_EXPR_MEM_FUNCS - The first optional parameter points to a structure of
 *                               type cu_mem_funcs which contains pointers to the
 *                               memory allocation functions equivalent to malloc(), 
 *                               free() and realloc().
 *
 *    p_mem_funcs - (optional) points to a list of memory function addresses to be used
 *                  in allocating and freeing memory. This parameter is optional and
 *                  is only used when the CU_EXPR_MEM_FUNCS option is specified. 
 */
extern
ct_int32_t cu_free_expr_1( void   *p_comp_expr, ct_uint32_t options, ... );


/*
 *   cu_probe_expr - analyze a compiled expression to determine the possible set
 *                   of values a variable may possess so that the execution of 
 *                   the expression produces a true result.
 *
 *    If the set of potential values can be determined, the function
 *    will return 0 and a structure of type cu_probe_result_t. The storage
 *    for the returned structured is allocated by the library and may be
 *    freed by calling free(), passing the pointer that is returned in
 *    p_result.
 *
 *    If it impossible to determine the set of values, a NULL pointer will be
 *    returned as the result along with a 0 return code. 
 *
 *  Parameters:
 *
 *     p_comp_expr - pointer to the compiled expression that was returned by
 *                   cu_comp_expr().
 *
 *     options     - a bitmask that is provided by the caller to control how the
 *                   operation is performed.  The following options may be specified:
 *
 *           CU_EXPR_MEM_FUNCS - The first optional parameter points to a structure of
 *                               type cu_mem_funcs which contains pointers to the
 *                               memory allocation functions equivalent to malloc(), 
 *                               free() and realloc().
 *
 *           CU_EXPR_API_FORMAT - Any indirect data is interpreted according to the ct_value_t
 *                                and related data structures.  If this options is not set,
 *                                all indirect data is interpreted as protocol format
 *                                (ct_pmsg_value_t... ).  This option must be passed if it
 *                                was used to compile the expression.
 *
 *     variable_id - specifies the id of a variable in the expression that is to be probed.
 *                   An attempt will be made to determine the possible set of values for this
 *                   variable that will result in the execution producing a true result. 
 *                   The id must be the same as was assigned to the variable name by the
 *                   validate_callback() during the compilation of the expression.
 *
 *     p_result    - specifies the address of a memory location into which a pointer to
 *                   a structure of type cu_probe_result_t will be stored if a set of
 *                   possible values can be determined.  This structure may be freed by
 *                   the caller using the free() function passing the returned address.
 *                   The information in the returned structure is:
 *
 *         data_type - specifies the data type of the values in the array below.
 *
 *         list_type - specifies whether elements are to be considered inclusive or
 *                     exclusive.  INCLUSIVE_LIST indicates that any value in the
 *                     array below will produce a true execution result.  EXCLUSIVE_LIST
 *                     means that all values except those in the list will produce
 *                     a true result. 
 *
 *         array     - is a array containing either a list of ranges for numeric
 *                     data types or a simple array of non-numeric data types.  A range
 *                     consists of the values in two adjacent array entries.  The low
 *                     value of each range is contained in the even array entries and the
 *                     high values are in the odd entries. Ranges always represent
 *                     the integral values between the low and high bounds, inclusive even
 *                     if the data type is floating point.  Non-integer values may be
 *                     present in a floating point array but the low and high values of
 *                     the range will always be the same.   The array will be in the format
 *                     selected by the CU_EXPR_API_FORMAT option.  If this option is 
 *                     present, the array will be returned in ct_array_t format.
 *                     Otherwise, it will be returned in ct_pmsg_array_t format. 
 *
 *     p_mem_funcs - (optional) points to a list of memory function addresses to be used
 *                   in allocating and freeing memory. This parameter is optional and
 *                   is only used when the CU_EXPR_MEM_FUNCS option is specified.
 *
 */
ct_int32_t cu_probe_expr_1( void                   *p_comp_expr,
                            ct_uint32_t            options,
                            ct_uint32_t            variable_id,
                            cu_probe_result_t      **p_result,
                            ... );

/*
 * cu_get_expr_props - Return the properties of a compiled expression.
 *
 *      This function will returned the number of operators and
 *      variable references in an expression that was compiled with
 *      cu_comp_expr().
 *
 *  Parameters:
 *      p_comp_expr - pointer to a compiled expression that was
 *                    produced by cu_comp_expr().
 *
 *      p_num_ops   - pointer to a ct_uint32_t in which the number
 *                    of operators in the expression will be returned.
 *  
 *      p_num_vars  - pointer to a ct_uint32_t variable in which
 *                    the number of variable references in the expression
 *                    will be returned.  This is not necessarily the
 *                    number of variables used since the same variable
 *                    may be referenced more than once.
 *
 *      p_num_consts- pointer to a ct_uint32_t variable in which
 *                    the number of constants used in the expression
 *                    will be returned. 
 *
 */
ct_int32_t cu_get_expr_props( void        *p_comp_expr,
                              ct_uint32_t *p_num_ops,
                              ct_uint32_t *p_num_var_refs,
                              ct_uint32_t *p_num_consts );

/*
 * cu_same_expr - Returns TRUE is expressions are semantically the same
 *
 *      This function will compare two compiled expressions to determine
 *      whether they are semantically the same. 
 *
 *  Parameters:
 *      p_comp_expr1 - pointer to a compiled expression that was
 *                     produced by cu_comp_expr().
 *
 *      p_comp_expr2 - pointer to a second compiled expression that was
 *                     produced by cu_comp_expr().
 *
 *      options      - options to control the comparison
 *                     (must be zero for now)
 *    
 *      p_result     - ptr to a location where the result is to be stored.  On return,
 *                     it contains 1 if expressions are the same, 0 otherwise.
 *
 */
ct_int32_t cu_same_expr( void        *p_comp_expr1,
                         void        *p_comp_expr2,
                         ct_uint32_t options,
                         ct_uint32_t *p_result,
                         ... );

/*
 * cu_expand_expr - Expand a compiled expression into a selection string. 
 *
 *      This function will take a compiled expression and produce
 *      a valid select string. In addition, variable names and literal
 *      values may be replaced as the expression is processed.
 *
 *  Parameters:
 *      p_comp_expr - pointer to a compiled expression that was
 *                    produced by cu_comp_expr().
 *
 *      options     - a bitmask that is provided by the caller to control how the
 *                    operation is performed.  The following options may be specified:
 *
 *           CU_EXPR_MEM_FUNCS - The first optional parameter points to a structure of
 *                               type cu_mem_funcs which contains pointers to the
 *                               memory allocation functions equivalent to malloc(), 
 *                               free() and realloc().
 *
 *           CU_EXPR_API_FORMAT - Any indirect data is interpreted according to the ct_value_t
 *                                and related data structures.  If this options is not set,
 *                                all indirect data is interpreted as protocol format
 *                                (ct_pmsg_value_t... ).  This option must be passed if it
 *                                was used to compile the expression.
 *
 *      p_select_string - pointer to a location into which the pointer to the
 *                    resulting select string will be returned.  The memory holding it
 *                    will be allocated using the provided mem functions or malloc if
 *                    the mem functions were not provided.  This storage must be
 *                    freed by the caller.
 *
 *      ids_to_translate - Array of variable ids whose literal values are to be
 *                    translated in the expression.  The ids in the this array must
 *                    correspond to those that were assigned during cu_comp_expr().
 *                    Note that an id being in this array or not only affects whether
 *                    the translation of literal values is performed.  It does
 *                    not mean that the callback to resolve an id into a name will not
 *                    be called.
 *
 *      number_of_ids - Defines the number of variable ids in the ids_to_translate array
 *
 *      token         - Arbitrary value that is passed to the following callbacks.
 *
 *      map_id_name   - Pointer to a function that returns the variable name associated
 *                    with an id that was assigned when the expression was compiled. The
 *                    returned pointer must remain valid until cu_exp_expr returns.
 *                    This function must be specified.
 *
 *                    char * (*func)( void           *token,    // Caller's token
 *                                    ct_uint32_t    id,        // Requested id 
 *                                    ct_uint32_t    parent_id, // Var id of owning SD if one
 *                                    ct_data_type_t type       // data type of variable
 *
 *      trans_value_func - Pointer to a function that returns a replacement literal value.
 *                    Returns 0 if no replacement is to take place. Non-zero means to
 *                    use the filled in ct_value_t as a replacement.  This function is
 *                    optionalif the ids_to_translate array is empty.
 *
 *                     int (*func)( void           *token         // Caller's token
 *                                  ct_uint32_t    *ids,          // Ids in same subexpr as const
 *                                  ct_uint32_t    num_ids,       // number of ids 
 *                                  ct_data_type_t orig_type,     // Original type of const
 *                                  ct_value_t     *p_orig_value, // Pointer to orig value
 *                                  ct_data_type_t *p_trans_type, // Translated type (out)
 *                                  ct_value_t     *p_trans_value ); // Translated value (out)
 *  
 *      free_value_func - Pointer to a function that is called to release any resources
 *                     associated with the value previously returned by p_trans_lit_func.
 *                     This function is option if the storage returned by trans_value_func
 *                     does not need to be freed.
 *
 *                     void (*func)( void           *token,
 *                                   ct_data_type_t type,
 *                                   ct_value_t     *value );
 */
ct_int32_t cu_expand_expr( void                   *p_comp_expr1,
                           ct_uint32_t            options,            
                           char                   **p_select_string,  
                           ct_uint32_t            *ids_to_translate,
                           ct_uint32_t            number_of_ids,
                           void                   *token,
                           map_id_to_name_cb      map_id_func,
                           trans_literal_value_cb trans_value_func,
                           free_literal_value_cb  free_value_func,
                           ... );
    
/*
 * cu_flush_cached_constant - frees any cached value of the specified system constant
 *
 *
 *   p_sys_constant - pointer to the name of the system constant.
 */
extern
ct_int32_t cu_flush_cached_constant_1( char   *p_sys_constant );

#endif /* (CU_VERSION == 1) || defined(CU_ALL_VERSIONS) */

#ifdef __cplusplus
} // end extern "C"
#endif /* __cplusplus */

#endif	/* _H_CT_CU_EXPR */



