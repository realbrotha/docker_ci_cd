/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/usr/ccs/lib/liberrlog/errlog.h 1.7                      */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2000,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
#ifndef H_errlog
#define	H_errlog
/* @(#)74        1.7  src/bos/usr/ccs/lib/liberrlog/errlog.h, cmderrlg, bos53D, d2005_09B1 2/24/05 15:34:58 */ 

/*
 * COMPONENT_NAME: CMDERRLG   system error logging and reporting facility
 *
 * External definitions and declarations for liberrlog.a
 *
 */


#include <sys/types.h>
#include <sys/err_rec.h>

typedef void *errlog_handle_t;

/*
 *  These magic numbers will indicate which version of errlog
 *  entry is being returned.
 *  All users of errlog_entry_t should use only LE_MAGIC.
 */
#define LE_MAGIC_41 0x0C3DF420
/* LE_MAGIC434_INTERUM is an interum 43T magic, before le_errdiag was added. */
#define LE_MAGIC434_INTERUM 0x0C3DF434
#define LE_MAGIC434 0x0C4DF434
#define LE_MAGIC52F 0x0C4DF52F
#define LE_MAGIC53D 0x0C4DF53D
#define LE_MAGIC   LE_MAGIC53D		/* current errlog_open magic # */
/* VALID_LE_MAGIC gives valid magic numbers for an error log record. */
#define VALID_LE_MAGIC(m) (((m) == LE_MAGIC_41) || \
		((m) == LE_MAGIC434_INTERUM) || ((m) == LE_MAGIC434))
/* VALID_LENTRY_MAGIC gives valid magic numbers for errlog_open(). */
#define VALID_LENTRY_MAGIC(m) (((m) == LE_MAGIC) || ((m) == LE_MAGIC434) ||\
			       ((m) == LE_MAGIC52F))

/*
 * Optional duplicate information.
 */
struct errdup {
    unsigned int	ed_dupcount;
    time32_t		ed_time1;
    time32_t		ed_time2;
};

/* Lengths of the various fields in the structure. */
#define LE_LABEL_MAX		20
#define LE_MACHINE_ID_MAX	32
#define LE_NODE_ID_MAX		32
#define LE_CLASS_MAX		2
#define LE_TYPE_MAX		5
#define LE_RESOURCE_MAX		16
#define LE_RCLASS_MAX		16
#define LE_RTYPE_MAX		16
#define LE_VPD_MAX		512
#define LE_IN_MAX		256
#define LE_CONN_MAX		20
#define LE_DETAIL_MAX		ERR_REC_MAX
#define LE_SYMPTOM_MAX		312
#define LE_ERRDUP_MAX		sizeof(struct errdup)

/* The data structure that contains an errlog entry */
typedef struct errlog_entry {
    unsigned int	el_magic;
    unsigned int	el_sequence;
    char		el_label[LE_LABEL_MAX];
    unsigned int	el_timestamp;
    unsigned int	el_crcid;
    unsigned int	el_errdiag;
    char		el_machineid[LE_MACHINE_ID_MAX];
    char		el_nodeid[LE_NODE_ID_MAX];
    char		el_class[LE_CLASS_MAX];
    char		el_type[LE_TYPE_MAX];
    char		el_resource[LE_RESOURCE_MAX];
    char		el_rclass[LE_RCLASS_MAX];
    char		el_rtype[LE_RTYPE_MAX];
    char		el_vpd_ibm[LE_VPD_MAX];
    char		el_vpd_user[LE_VPD_MAX];
    char		el_in[LE_IN_MAX];
    char		el_connwhere[LE_CONN_MAX];
    unsigned short	el_flags;
    unsigned short	el_detail_length;
    char		el_detail_data[LE_DETAIL_MAX];
    unsigned int	el_symptom_length;
    char		el_symptom_data[LE_SYMPTOM_MAX];
    struct errdup	el_errdup;
} errlog_entry_t;


/* Values for the el_flags element. */
#define	LE_FLAG_ERR64		0x01
#define	LE_FLAG_ERRDUP		0x100

/*
 *  This structure is used to pass search criteria to errlog_find_first.

 *  To use it an operation is put in em_op.  If it is a leaf operation,
 *  the field in errlog_entry_t to apply the op to is put in em_field and
 *  the value to compare against is put in em_strvalue or em_intvalue.
 *  Boolean values are put in em_intvalue.
 *
 *  To connect operations, a unary or binary operator is put in em_op.
 *  The operation(s) to apply the operator to are put in em_left and,
 *  if it's a binary operator, em_right.
 */

typedef struct errlog_match {
    unsigned int		em_op;
    union {
	struct errlog_match	*emu_left;
	unsigned int		emu_field;
    } emu1;
    union {
	struct errlog_match	*emu_right;
	unsigned int		emu_intvalue;
	unsigned char		*emu_strvalue;
    } emu2;
} errlog_match_t;

#define	em_left		emu1.emu_left
#define	em_field	emu1.emu_field
#define	em_right	emu2.emu_right
#define	em_intvalue	emu2.emu_intvalue
#define	em_strvalue	emu2.emu_strvalue

/* Operators to use in the match structures for the find functions */
#define	LE_OP_EQUAL		0x01
#define	LE_OP_NE		0x02
#define	LE_OP_SUBSTR		0x03
#define	LE_OP_LT		0x04
#define	LE_OP_LE		0x05
#define	LE_OP_GT		0x06
#define	LE_OP_GE		0x07
#define	LE_OP_LEAF		0x100
#define	LE_OP_NOT		0x101
#define	LE_OP_AND		0x201
#define	LE_OP_OR		0x202
#define	LE_OP_XOR		0x203

/* Flags to combine with the field id to indicate the data type of the field */
#define	LE_TYPE			0xff00
#define	LE_TYPE_INT		0x0100
#define	LE_TYPE_STRING		0x0200
#define	LE_TYPE_BOOLEAN		0x0300

/* Flags to indicate which field to match in the find functions. */
#define	LE_MATCH_FIELD		0xff
#define	LE_MATCH_SEQUENCE	(0x01|LE_TYPE_INT)
#define	LE_MATCH_LABEL		(0x02|LE_TYPE_STRING)
#define	LE_MATCH_TIMESTAMP	(0x03|LE_TYPE_INT)
#define	LE_MATCH_CRCID		(0x04|LE_TYPE_INT)
#define	LE_MATCH_MACHINEID	(0x05|LE_TYPE_STRING)
#define	LE_MATCH_NODEID		(0x06|LE_TYPE_STRING)
#define	LE_MATCH_CLASS		(0x07|LE_TYPE_STRING)
#define	LE_MATCH_TYPE		(0x08|LE_TYPE_STRING)
#define	LE_MATCH_RESOURCE	(0x09|LE_TYPE_STRING)
#define	LE_MATCH_RCLASS		(0x0a|LE_TYPE_STRING)
#define	LE_MATCH_RTYPE		(0x0b|LE_TYPE_STRING)
#define	LE_MATCH_VPD_IBM	(0x0c|LE_TYPE_STRING)
#define	LE_MATCH_VPD_USER	(0x0d|LE_TYPE_STRING)
#define	LE_MATCH_IN		(0x0e|LE_TYPE_STRING)
#define	LE_MATCH_CONNWHERE	(0x0f|LE_TYPE_STRING)
#define	LE_MATCH_FLAG_ERR64	(0x10|LE_TYPE_BOOLEAN)
#define	LE_MATCH_FLAG_ERRDUP	(0x11|LE_TYPE_BOOLEAN)
#define	LE_MATCH_DETAIL_DATA	(0x12|LE_TYPE_STRING)
#define	LE_MATCH_SYMPTOM_DATA	(0x13|LE_TYPE_STRING)
#define	LE_MATCH_ERRDIAG	(0x14|LE_TYPE_INT)

/*
 *  Define the directions find can walk through the errlog file.
 */

#define	LE_FORWARD		0x01
#define	LE_REVERSE		0x02

/*
 * Define the errors that the functions can return.
 */

#define	LE_ERR_INVARG	0x01		/* Invalid input argument */
#define	LE_ERR_NOFILE	0x02		/* The errlog file can't be opened */
#define	LE_ERR_INVFILE	0x03		/* The errlog file isn't valid */
#define	LE_ERR_NOMEM	0x04		/* We're out of memory */
#define	LE_ERR_NOWRITE	0x05		/* Can't write entry back */
#define	LE_ERR_IO	0x06		/* IO error in the errlog file */
#define	LE_ERR_DONE	0x07		/* The find function reached the end */

/* 
 * These are the functions that comprise the API
 */
extern int errlog_open(char		*path,
		       int		mode,
		       unsigned int	magic,
		       errlog_handle_t	*handle);

extern int errlog_close(errlog_handle_t	handle);

extern int errlog_find_first(errlog_handle_t	handle,
			     errlog_match_t	*filter,
			     errlog_entry_t	*result);

extern int errlog_find_next(errlog_handle_t	handle,
			    errlog_entry_t	*result);

extern int errlog_find_sequence(errlog_handle_t	handle,
				int		sequence,
				errlog_entry_t	*result);

extern int errlog_set_direction(errlog_handle_t	handle,
				int		direction);

extern int errlog_write(errlog_handle_t		handle,
			errlog_entry_t		*data);

#endif
