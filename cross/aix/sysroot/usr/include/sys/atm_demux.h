/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/atm_demux.h 1.4                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1995,2001          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)97  1.4  src/bos/kernel/sys/atm_demux.h, sysxatm, bos530 11/5/01 11:16:27 */
/*
 *   COMPONENT_NAME: SYSXATM
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#ifndef _ATM_DEMUX_H
#define _ATM_DEMUX_H

#include <sys/lock_def.h>
#include <sys/cdli.h>
#include <sys/err_rec.h>
#include <sys/types.h>

#define ATM_VC_FILTER 	(NS_LAST_FILTER + 1)

/*
 * atm_dmx_config_t structure defines the data passed to the atm demuxer
 * from its config method.  
 */
struct atm_dmx_config 
{
	uchar   lname[ERR_NAMESIZE];    /* device logical name (i.e. atm0) */
	uint	max_filters;		/* the number of filters the device */
					/*  is configured to support */
};
typedef struct atm_dmx_config atm_dmx_config_t;

struct leaf_link_str 
{
	int   leaf_handle;
        void                    (*isr)();   /* protocol input function     */
        caddr_t                 isr_data;   /* arg to isr                  */
        struct leaf_link_str    *pre_link_ptr;   /* point to the next link */
        struct leaf_link_str    *next_link_ptr;  /* point to the next link */
};

/*
 * atm_dmx_user_t structure defines the user structure internal to the atm 
 * demuxer for its filter table.  It is different from the ns_user_t that
 * most of the other Demuxers use.
 */
struct atm_dmx_user {
        struct leaf_link_str    *leaf_ptr;/* base of the leaf chain      */
};
typedef struct atm_dmx_user atm_dmx_user_t;

/*
 * atm_dmx_ctl_t structure is used to hold the demuxer information specific
 *  to a particular adapter.  
 */
struct atm_dmx_ctl 
{
	struct 	atm_dmx_ctl	*next;
	uchar   		lname[ERR_NAMESIZE];    /* device logical name*/
	uint			max_filters;		/* number of filters  */
							/*  the device is     */
							/*  configured to     */
							/*  support (not */
							/*  counting the tap */
	ns_user_t 		tap_user;		/* holds the tap */
							/*  user */
	int			tap_rcv_flag;		/* rcv flag for the */
							/*  tap user */
	atm_dmx_user_t		*p_filter;		/* pointer to block of*/
							/*  filters */
	int			*p_rcv_flag;		/* pointer to block of*/
							/*  rcv flags */
							/*  (one/filter) */
	Simple_lock		stat_lock;		/* lock used to */
							/*  control access to */
							/*  the status */
							/*  functions */
};
typedef struct atm_dmx_ctl atm_dmx_ctl_t;

struct adapter_filter
{
        uint    filtertype;     /* flag that identifies the type of */
                                /*  filter the user is requesting */
        int     vc_handle;      /* contains the identifier of the packets */
};
typedef struct adapter_filter adapter_filter_t;


/*
 * atm_vc_filter_t structure is used to specify a filter for an atm packet.  
 *  ATM supports two types of filters, NS_TAP and ATM_VC_FILTER
 */
struct atm_vc_filter
{
        uint    filtertype;     /* flag that identifies the type of */
                                /*  filter the user is requesting */
        int     vc_handle;      /* contains the identifier of the packets */
        int     leaf_handle;    /* for point_to_multipoint only */
};
typedef struct atm_vc_filter atm_vc_filter_t;

#endif
