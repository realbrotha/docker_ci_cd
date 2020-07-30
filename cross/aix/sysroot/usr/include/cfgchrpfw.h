/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/usr/include/cfgchrpfw.h 1.12.2.2                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1996,2010              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)62 1.12.2.2  src/bos/usr/include/cfgchrpfw.h, libcfg, bos53X, x2010_31A7 7/19/10 15:05:46 */
/*
 * COMPONENT_NAME: (LIBCFG) 
 *
 * FUNCTIONS: DEFINITIONS for Open Firmware device tree access functions 
 *
 * ORIGINS: 27
 *
 *                  -- (                            when
 * combined with the aggregated modules for this product)
 * OBJECT CODE ONLY SOURCE MATERIALS
 * (C) COPYRIGHT International Business Machines Corp. 1996, 2006
 * All Rights Reserved
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */                                                                   

/* prevent multiple inclusion */
#ifndef _H_CFGCHRPFW
#define _H_CFGCHRPFW


#include <sys/cfgodm.h>		/* For PdDv and CuDv structures */

#define ENCODE_INT_SIZE       4
#define DEFAULT_ADDRESS_CELLS 2
#define DEFAULT_SIZE_CELLS    1

/*--------------------------------------------*/
/* Open Firmware device tree access functions */
/*--------------------------------------------*/

#define PATH_TO_TOK    		1
#define GET_NEXT_TOK   		2
#define GET_CHILD_TOK  		3
#define GET_PARENT_TOK 		4
#define ODM_TO_TOK     		5
#define GET_NODE_NAME  		6
#define GET_PROPERTY   		7
#define GET_PROP_NAME 		8
#define PATH_TO_ODM    		9
#define TOK_TO_ODM    		10
#define SPECIFY_FILE  		11
#define ODM_TO_TOKS   		12
#define ODM_PATH_TO_TOK   	13
#define ODM_TO_LOC		14
#define EPATH_TO_ODM      	15
#define CFG_SPACE_ACCESS_TYPE	16
#define CFG_SET_SAS_PHYSLOC	17
#define PATH_TO_ODMPATH   	18
#define CFG_GET_MSG_INTERRUPTS	19

typedef struct _path_to_tok
{
	char          *pathname;
	unsigned long tok;
} path_to_tok_t;
  
typedef struct _get_next_tok
{
	unsigned long tok;
} get_next_tok_t;

typedef struct _get_child_tok
{
	unsigned long parent_tok;
	unsigned long child_tok;
} get_child_tok_t;

typedef struct _get_parent_tok
{
	unsigned long tok;
} get_parent_tok_t;

typedef struct _odm_to_tok
{
	struct CuDv   *cudv;
	unsigned long tok;
} odm_to_tok_t;

typedef struct _get_node_name
{
	unsigned long tok;
	const char    *node_name;
	const char    *unit_address;
} get_node_name_t;

typedef struct _get_property
{
	unsigned long tok;
	char          *property_name;
	int           found;
	int           property_length;
	const char    *property_value;
} get_property_t;

typedef struct _get_prop_name
{
	unsigned long tok;
	unsigned long property_token;
	const char    *property_name;
} get_prop_name_t;

typedef struct _path_to_odmpath
{
	char          *path;
	struct CuDv   cudv;
	struct PdDv   pddv;
	struct CuPath cupath;
} path_to_odmpath_t;

typedef struct _path_to_odm
{
	char          *path;
	struct CuDv   cudv;
	struct PdDv   pddv;
} path_to_odm_t;

typedef struct _epath_to_odm
{
        char          *path;
        char          *args;
        struct CuDv   cudv;
        struct PdDv   pddv;
} epath_to_odm_t;

typedef struct _tok_to_odm
{
	unsigned long tok;
	char          *odm_parent_name;
	struct CuDv   cudv;
	struct PdDv   pddv;
	int	      status;
	int	      built_in;
	int	      device_id_len;
	char	      device_id[1024];
	int	      pkg_list_len;
	char	      pkg_list[1024];
	char	      connection[16];
	char	      subclass[16];
	char	      aix_loc[3];
} tok_to_odm_t;

typedef struct _odm_to_toks
{
	struct CuDv   *cudv;
	unsigned long *tok_list;
} odm_to_toks_t;

typedef struct _odm_path_to_tok
{
	struct CuDv   *cudv;
	struct CuPath *cupath;
	unsigned long tok;
} odm_path_to_tok_t;


typedef struct _odm_to_loc { 
    struct CuDv *cudv; 
    struct CuPath *cupath; 
    char **location; 
} odm_to_loc_t; 

typedef struct _cfg_sas_set_physloc
{
	struct CuDv   *cudv;
	int  	      type;
	char	      *ccfskeyword;
	char	      *snkeyword;
	char          *drive_loc;
} cfg_sas_set_physloc_t ;

typedef struct _cfg_space_access_type
{
	struct CuDv   *cudv;
	unsigned int  *type;
} cfg_space_access_type_t;

typedef struct _cfg_get_message_interrupts
{
	struct CuDv   *cudv;
	int  	      intr_type;
	int  	      intr_req;
	int	      *intr_allocated;
	unsigned int  **intr_vector;
} cfg_get_msg_interrupts_t;

/*---------------------*/
/* Function prototypes */
/*---------------------*/

#ifdef _NO_PROTO
int PAL_libcfg();
#else /* _NO_PROTO */
int PAL_libcfg(int, void *);
#endif /* _NO_PROTO */

#endif /* _H_CFGCHRPFW */

