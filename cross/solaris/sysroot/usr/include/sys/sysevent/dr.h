/*
 * Copyright 2000-2002 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_SYSEVENT_DR_H
#define	_SYS_SYSEVENT_DR_H

#pragma ident	"@(#)dr.h	1.7	02/03/11 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * dr.h contains the publicly defined sysevent attribute names and values
 * for all DR type sysevents.  Additions/removals/changes are subject to
 * PSARC approval.
 */

/*
 * Event type EC_DR/ESC_DR_AP_STATE_CHANGE event schema
 *	Event Class 	- EC_DR
 *	Event Sub-Class - ESC_DR_AP_STATE_CHANGE
 *	Event Publisher	- SUNW:kern:[dr_subsystem_name]
 *	Attribute Name	- DR_AP_ID
 *	Attribute Type	- SE_DATA_TYPE_STRING
 *	Attribute Value	- [Attachment Point Identifier]
 *	Attribute Name	- DR_HINT
 *	Attribute Type	- SE_DATA_TYPE_STRING
 *	Attribute Value	- DR_RESERVED_ATTR | DR_HINT_INSERT | DR_HINT_REMOVE
 */
#define	DR_AP_ID	"dr_ap_id"	/* Attachment point id */
#define	DR_HINT	"dr_hint"		/* Operation hint */
#define	DR_HINT_INSERT	"dr_insert"	/* Insert hint */
#define	DR_HINT_REMOVE	"dr_remove"	/* Remove hint */
#define	DR_RESERVED_ATTR	""

/*
 * Useful macros for insert/remove event.
 */
#define	SE_NO_HINT		0x0
#define	SE_HINT_INSERT		0x1
#define	SE_HINT_REMOVE		0x2
#define	SE_HINT2STR(h)		((h) == SE_HINT_INSERT ? DR_HINT_INSERT : \
				    (h) == SE_HINT_REMOVE ? DR_HINT_REMOVE : \
				    DR_RESERVED_ATTR)
/*
 * Event type EC_DR/ESC_DR_REQ event schema
 *	Event Class	- EC_DR
 *	Event Sub-Class	- ESC_DR_REQ
 *	Event Publisher	- SUNW:kern:[dr_subsystem_name]
 *	Attribute Name	- DR_AP_ID
 *	Attribute Type	- SE_DATA_TYPE_STRING
 *	Attribute Value	- [Attachment Point Name]
 *	Attribute Name	- DR_REQ_TYPE
 *	Attribute Type	- SE_DATA_TYPE_STRING
 *	Attribute Value	- DR_RESERVED_ATTR | DR_REQ_INCOMING_RES |
			DR_REQ_OUTGOING_RES | DR_REQ_INVESTIGATE_RES
 */
#define	DR_REQ_TYPE	"dr_request_type"	/* User request type */
#define	DR_REQ_INCOMING_RES	"dr_request_incoming_resource"
#define	DR_REQ_OUTGOING_RES	"dr_request_outgoing_resource"
#define	DR_REQ_INVESTIGATE_RES	"dr_request_investigate_resource"

#define	SE_INVESTIGATE_RES	0x0
#define	SE_INCOMING_RES		0x1
#define	SE_OUTGOING_RES		0x2
#define	SE_REQ2STR(h)		((h) == SE_INCOMING_RES ? \
					DR_REQ_INCOMING_RES : \
					(h) == SE_OUTGOING_RES ? \
					DR_REQ_OUTGOING_RES : \
					DR_REQ_INVESTIGATE_RES)

#ifdef	__cplusplus
}
#endif

#endif /* _SYS_SYSEVENT_DR_H */
