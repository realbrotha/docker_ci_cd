/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/hdlc_demux.h 1.3                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1996,1997          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)12	1.3  src/bos/kernel/sys/hdlc_demux.h, dmxhdlc, bos530 9/4/97 16:10:22 */
/*
 *   COMPONENT_NAME: SYSXHDLC
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
#ifndef _HDLC_DEMUX_H
#define _HDLC_DEMUX_H

#include <sys/lock_def.h>
#include <sys/cdli.h>
#include <sys/err_rec.h>
#include <sys/types.h>

#define HDLC_FILTER   (NS_LAST_FILTER + 1)

/*
 * hdlc_filter_t structure is used to specify a filter for an hdlc packet.  
 *  HDLC supports two types of filters, NS_TAP and HDLC_FILTER
 */
struct hdlc_filter
{
        uint	filtertype; 	/* flag that identifies the type of */
				/*  filter the user is requesting */
};
typedef struct hdlc_filter hdlc_filter_t;

/*
 * hdlc_dmx_pnd_t structure is used to specify a status filter pending
 *  deletion.
 */
struct hdlc_dmx_pnd
{
	struct	hdlc_dmx_pnd	*next;
	ndd_t			*p_ndd;
        ns_com_status_t         *p_filter;	/* points to status filter pending */
						/* deletion 			   */
};
typedef struct hdlc_dmx_pnd hdlc_dmx_pnd_t;

/*
 * hdlc_dmx_config_t structure defines the data passed to the hdlc demuxer
 * from its config method.  
 */
struct hdlc_dmx_config 
{
	uchar   lname[ERR_NAMESIZE];    /* device logical name (i.e. dpm0) */
};
typedef struct hdlc_dmx_config hdlc_dmx_config_t;

/*
 * hdlc_dmx_ctl_t structure is used to hold the demuxer information specific
 *  to a particular adapter.  
 */
struct hdlc_dmx_ctl 
{
	struct 	hdlc_dmx_ctl	*next;
	uchar   		lname[ERR_NAMESIZE];    /* device logical name*/
	ns_user_t 		tap_user;		/* tap user info */
	ns_user_t		user_filter;		/* user information */
	ulong			stat_users;		/* number of user's */
						        /* that have added */
							/* status filters */
        Simple_lock             stat_lock;              /* lock used to */
                                                        /*  control access to */
                                                        /*  the status */
                                                        /*  functions */
	hdlc_dmx_pnd_t   	*p_hdlc_pnd; 		/* pointer to global list */
                                                  	/* of hdlc dmx status filters */
                                                  	/* pending deletion */
	int              	status_pending;	  	/* status in progress */
};
typedef struct hdlc_dmx_ctl hdlc_dmx_ctl_t;

#endif
