/*
 * Copyright (c) 1992 by Sun Microsystems, Inc.
 */

#ident  "@(#)cm.h 1.17 97/10/31 SMI"

/************************************************************************/
/*			cm.h						*/
/*	Copyright (c) 1992 by Sun Microsystems, Inc.			*/
/*									*/
/************************************************************************/

#include <sys/types.h>

typedef unsigned short		Operation_type;
typedef int			Cm_session;
typedef	unsigned char		e_char;		/* euc */

/*
 * When the cursor or the focus does not exist in interm region
 * or misc region, the value of its cursor or focusstart has the
 * following value.
 */

#define MAX_INTERM_TEXT		1024
#define INVALID_TEXT_INDEX	MAX_INTERM_TEXT + 2
/*
 * Cm_session
 * cm_open(cm_initvalue, se_initvalue)
 *      struct cm_initstruct *cm_initvalue;
 *      struct cm_to_env **se_initvalue;
 *
 * struct cm_to_env *
 * cm_put(cmsession, inptr)
 *      Cm_session cmsession;
 *      struct env_to_cm *inptr;
 *
 * cm_close(cmsession)
 *      Cm_session cmsession;
 *
 * Note:
 * Struct inptr is allocated and deallocated by ENV, while struct outptr
 * is allocated and deallocated by CM.
 */
 
Cm_session cm_open();

struct usr_auth_info {
	int	uid;		/* User ID */
	char	*user_name;	/* User Name */
	int	gid;		/* Group ID */
	char	*grp_name;	/* Group Name */
	int	hid;		/* Host ID */
	char	*host_name;	/* Host Name */
};

struct cm_initstruct {
	e_char	*env_value;			/* Resered */
	struct	usr_auth_info	usr_auth_info;	/* User authorization info */
};

struct cm_sw {
	Cm_session		(*cm_open)();
	struct	cm_to_env	*(*cm_put)();
	int			(*cm_close)();
};

/*
 * env_to_cm
 */

struct env_to_cm {
	struct	env_to_cm	*ec_next;
	Operation_type		ec_operation;
	union {
		u_int		ep_key;
		u_short		ep_convlevel;
		int		ep_select;
		struct {
			int		e_size;
			e_char		*e_keyptr;
		} ep_string;
#define ep_size		ep_string.e_size
#define ep_keyptr	ep_string.e_keyptr

		int		ep_select_invalid;

	} ec_parameter;
};

#define ec_key			ec_parameter.ep_key
#define ec_keyptr		ec_parameter.ep_keyptr
#define ec_size			ec_parameter.ep_size
#define ec_select		ec_parameter.ep_select

#define ec_select_invalid	ec_parameter.ep_select_invalid

/* 
 * env_to_cm operations 
 * An operation is put to (struct env_to_cm *)->ec_operation.  
 * The parameters of the operation are put to (struct env_to_cm *)->
 * ec_parameter.  Each operation may use different elements from
 * union ec_parameter from other operations.
 */

/* GENERAL Operation */
#define CM_RESET		1
/* 
 * CM_RESET() requests CM to commit data, clear status and
 * turn off the conversion.
 */
#define CM_SIMPLE_EVENT		2
/* 
 * CM_SIMPLE_EVENT((u_int)ec_key) passes a keyboard action to CM.
 */
#define CM_STRING_EVENT		3
/*
 * CM_STRING_EVENT((e_char *)ec_keyptr) passes a string to CM.
 * This operation is used when the user wants to input a string
 * using cut-and-paste feature.
 */
#define CM_SET_CURRENT_REGION	5
/*
 * CM_SET_CURRENT_REGION((int)ec_select) sets ec_select to be
 * the current region.   This operation and the notion of current
 * region are used to direct keyboard actions between the INTERM region
 * and the MISC region.  Thus, ec_select in this operation can only be
 * INTERM or MISC.
 * In return, CM passes back ENV_SET_CURRENT_REGION(cts_region) to
 * confirm the region change.
 */
#define CM_SET_CONVLEVEL	6
/*
 * CM_SET_CONV_LEVEL((int)ec_convlevel) sets the level of committed string.
 */
#define CM_GET_CONVLEVEL	7
/*
 * CM_GET_CONVLEVEL() gets the current conversion level.
 */
#define CM_GET_CONVID		8
/*
 * CM_GET_CONV_ID() gets the conversion id.
 */
#define CM_GET_KEYBINDING	9
/*
 * CM_GET_KEYBINDING((u_int)ec_key) retrieves the keybinding of
 * ec_key.  CM returns the keybinding with ENV_RTN_VALUE.
 */
#define CM_CMON			10
/*
 * CM_CMON() turns on conversion.  In return, CM should inform
 * ENV about the new mode.
 */

/* Operation for SELECTION REGION */
/*
 * CM enters into a selection phase when it sees a specified control
 * key from CM_SIMPLE_EVENT(ec_key).  ENV enters into a selection
 * phase when CM issues a ENV_SELECT(cts_ncandidate, ...) operation.
 * ENV exits from a selection phase when the user makes a seclection
 * or aborts the selection, either through the mouse or the keyboard.
 * CM exits from a selection phase when it gets CM_SELECT(ec_select)
 * or CM_ABORT_SELECTION() from ENV.
 * When EVN doesn't do selection by itself, ENV can send all key event
 * to CM by CM_SIMPLE_EVENT(ec_key). 
 */ 



#define CM_NEXT_CANDIDATE	30
/*
 * CM_NEXT_CANDIDATE() asks for the next set of candidates.
 * In return, CM passes back ENV_SELECT(cts_ncandidate, cts_candidate,
 * cts_prevexist, cts_nextexist) to ENV.
 */
#define CM_PREV_CANDIDATE	31
/*
 * CM_PREV_CANDIDATE() asks for the previous set of candidates.
 * In return, CM passes back ENV_SELECT(cts_ncandidate, cts_candidate,
 * cts_prevexist, cts_nextexist) to ENV.
 */
#define CM_SELECT		32
/*
 * CM_SELECT((int)ec_select) selects the ec_select-th
 * candidate as the choice of this selection.  Both CM and ENV
 * exit from the selection phase.
 */
#define CM_ABORT_SELECTION	33	
/*
 * CM_ABORT_SELECTION() makes both CM and ENV exit from the
 * selection phase without making a choice.  The focus area
 * is the same as before the selection starts.
 * If no region is changed for this operation, CM passes
 * ENV_NOP() to ENV.
 */

#define CM_SELECT_INVALID	34
/*
 * CM_SELECT_INVALID((int)ec_select_invalid) tells CM that the
 * value of ENV_SELECT was invalid.  And it is used as an answer
 * of ENV_SELECT_TEST.
 */

/*
 * Invalid value
 * used by CM_SELECT_INVALID
 */

#define INVALID         0x00    /* Invalid */
#define COMMITT         0x01    /* Committable */
#define COMMITT_NOTC    0x02    /* Committable but not complete */
#define AMB_C           0x03    /* Commitable but Ambiguous */
#define AMB             0x04    /* Ambiguous */

/*
 * (u_int)ec_key used in CM_GET_KEYBINDING.
 */
#define CONV_ON				1

/*
 * New LUC interface definitions for negotiation in cm_open() and cm_put()
 */

/*
 * CM_IMSERVER_NEGOTIATION tells CM that im server wants
 * to negotiate with CM about the LUC window.
 */
#define         CM_IMSERVER_NEGOTIATION         35

typedef struct _LucNegotiation {
    int		luc_is_rootwindow;  /* non zero if rootwindow style luc */
    int		ims_takes_control;  /* non zero if IMS takes all key
				       inputs while LUC is active */
    int		label_type;
    int		choice_per_window;  /* max # of candidates in a LUC window */
    int		root_width;         /* root window width in pixels */
    int		root_lines;         /* # of lines in the IMS window */
    int		e_width_per_can;    /* pixel value width per candidate
                                       excluding the candidate string
				       itself. ie.(Label width)+(Space) */
    int		max_width_per_car;  /* max char width in pixels */
} LucNegotiation;

#define IM_CM_LUC_NEGOTIATED    (1L<<0)

#define LUC_LABEL_NONE          0
#define LUC_LABEL_NUMERIC       1
#define LUC_LABEL_ALPHABETIC    2
#define LUC_LABEL_ALPHA_UPPER   3

typedef struct _ImsCmNegotiation {
    int			cm_interested;
    LucNegotiation      *luc;
} ImsCmNegotiation;

