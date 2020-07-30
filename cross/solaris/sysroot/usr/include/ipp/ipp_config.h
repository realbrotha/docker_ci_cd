/*
 * Copyright 2002 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_IPP_IPP_CONFIG_H
#define	_IPP_IPP_CONFIG_H

#pragma ident	"@(#)ipp_config.h	1.1	02/02/26 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * ipp action modules configuration type codes
 */

#define	IPP_CONFIG_TYPE	"ipp.config_type" /* byte */

#define	IPP_SET				0x00

/*
 * Classifier configuration type codes.
 */
#define	CLASSIFIER_ADD_FILTER		0x01
#define	CLASSIFIER_ADD_CLASS		0x02
#define	CLASSIFIER_REMOVE_FILTER	0x03
#define	CLASSIFIER_REMOVE_CLASS		0x04
#define	CLASSIFIER_MODIFY_FILTER	0x05
#define	CLASSIFIER_MODIFY_CLASS		0x06

/* classifier generic parameters */
#define	CLASSIFIER_FILTER_NAME		"ipp.filter_name"
#define	CLASSIFIER_CLASS_NAME		"ipp.class_name"
#define	CLASSIFIER_NEXT_ACTION		"ipp.next_action_name"
#define	CLASSIFIER_CLASS_STATS_ENABLE	"ipp.class_stats"

/* all actions generic parameters */
#define	IPP_ACTION_STATS_ENABLE		"ipp.action_stats"
#define	IPP_MODULE_VERSION		"ipp.module_version"

/*
 * Record configuration object ownership
 */
#define	IPP_CONFIG_ORIGINATOR		"ipp.originator"

#define	IPP_CONFIG_PERMANENT		0x00000000
#define	IPP_CONFIG_IPQOSCONF		0x00000001
#define	IPP_CONFIG_FTPCL		0x00000002

#define	IPP_CONFIG_NAME_PERMANENT	"permanent"
#define	IPP_CONFIG_NAME_IPQOSCONF	"ipqosconf"
#define	IPP_CONFIG_NAME_FTPCL		"ftpcl"

/*
 * macros to extract the major and minor version from a module version
 * integer encoding.
 */
#define	IPP_MAJOR_MODULE_VER(ver)	(ver / 10000)
#define	IPP_MINOR_MODULE_VER(ver)	(ver % 10000)

#ifdef	__cplusplus
}
#endif

#endif /* _IPP_IPP_CONFIG_H */
