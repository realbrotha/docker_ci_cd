/*
 * Copyright (c) 1992 by Sun Microsystems, Inc.
 */

#ident  "@(#)env.h 1.21 97/10/31 SMI"

/************************************************************************/
/*									*/
/*			env.h						*/
/*									*/
/************************************************************************/

/*
 * cm_to_env
 */

struct cm_to_env {
	struct	cm_to_env 	*ce_next;
	Operation_type		ce_operation;
	union {
		struct {
                        e_char  *c_string;
                        int     c_size;
                } cp_commit;
#define cp_string               cp_commit.c_string
#define cp_size                 cp_commit.c_size
		int		cp_region;
		int		cp_rtn_value;
                struct {
                        int     ct_cursor_pos;
                        int     ct_cursor_type;
                        e_char  *ct_text;
                        u_char  *ct_text_attr;
			int	ct_v_pos;
			int	ct_v_type;
                } cp_region_Text;       /* Region Text structure */
#define cp_cursor_pos           cp_region_Text.ct_cursor_pos
#define cp_cursor_type          cp_region_Text.ct_cursor_type
#define cp_text                 cp_region_Text.ct_text
#define cp_text_attr		cp_region_Text.ct_text_attr
#define cp_v_pos		cp_region_Text.ct_v_pos
#define cp_v_type		cp_region_Text.ct_v_type
                struct {
                        int         c_ncandidate; /* no. of candidates */
                        e_char          **c_candidate; /* candidate array */
                        int          c_prevexist; /* prev cand. exists */
                        int          c_nextexist; /* next cand. exists */
                        e_char          *c_select_prompt;
                } cp_select;
#define cp_ncandidate           cp_select.c_ncandidate
#define cp_candidate            cp_select.c_candidate
#define cp_prevexist            cp_select.c_prevexist
#define cp_nextexist            cp_select.c_nextexist
#define cp_sel_prompt           cp_select.c_select_prompt
		e_char			*c_mode_list;
		e_char			*c_mode_data;

                struct {
                        e_char          *c_sel_string;
                        u_char          c_sel_commit_flag;
                } cp_sel_commit;
#define cp_sel_string          cp_sel_commit.c_sel_string
#define cp_sel_commit_flag      cp_sel_commit.c_sel_commit_flag
                struct {
                        e_char  *cm_text;
			int	cm_nextexist;
			int	cm_prevexist;
                } cp_Misc_Text;       /* Misc Region Text structure */
#define cp_misc_text 		cp_Misc_Text.cm_text
#define cp_misc_nextexist	cp_Misc_Text.cm_nextexist
#define cp_misc_prevexist	cp_Misc_Text.cm_prevexist

		struct {
			enum {
				CE_ERR_WARNING	= 10,
				CE_ERR_ERROR	= 20,
				CE_ERR_FATAL	= 30
			}		c_err_level;
			int		c_err_id; /* will not use in JLE1.X */
			e_char		*c_err_mess;
		} cp_error;
#define	cp_err_level		cp_error.c_err_level
#define	cp_err_id		cp_error.c_err_id
#define	cp_err_mess		cp_error.c_err_mess

	} ce_parameter;
};

#define ce_string		ce_parameter.cp_string	
#define ce_size			ce_parameter.cp_size
#define ce_region		ce_parameter.cp_region
#define ce_rtn_value		ce_parameter.cp_rtn_value
#define ce_cursor	        ce_parameter.cp_cursor_pos
#define ce_cursor_type          ce_parameter.cp_cursor_type
#define ce_text                 ce_parameter.cp_text
#define ce_text_attr            ce_parameter.cp_text_attr 
#define ce_v_pos		ce_parameter.cp_v_pos
#define ce_v_type		ce_parameter.cp_v_type 
#define ce_nchar                ce_parameter.cp_nchar
#define ce_ncandidate           ce_parameter.cp_ncandidate
#define ce_candidate            ce_parameter.cp_candidate
#define ce_prevexist            ce_parameter.cp_prevexist
#define ce_nextexist            ce_parameter.cp_nextexist
#define ce_sel_prompt           ce_parameter.cp_sel_prompt
#define ce_mode_list		ce_parameter.c_mode_list
#define ce_mode_data		ce_parameter.c_mode_data

#define ce_sel_string		ce_parameter.cp_sel_string
#define ce_sel_commit_flag	ce_parameter.cp_sel_commit_flag
#define ce_misc_text		ce_parameter.cp_misc_text
#define ce_m_nextexist		ce_parameter.cp_misc_nextexist
#define ce_m_prevexist		ce_parameter.cp_misc_prevexist

#define	ce_err_level		ce_parameter.cp_err_level
#define	ce_err_id		ce_parameter.cp_err_id
#define	ce_err_mess		ce_parameter.cp_err_mess

/*
 * cm_to_env operations
 * An operation is put to (struct cm_to_env *)->ce_operation.
 * The parameters of the operation are put to (struct cm_to_env *)->
 * ce_parameter.  Each operation may use different elements from
 * union ce_parameter from other operations.
 */

#define ENV_COMMIT		65
/*
 * ENV_COMMIT(((char *)ce_string) commits ce_string.
 * As the result, ce_string will be sent to the application program.
 * The INTERM region is not changed by this operation.
 * If cm wants to change the intermediate region at the same time,
 * cm should chain one or more opetations to do that.
 */
#define ENV_SET_CURRENT_REGION	67
/*
 * ENV_SET_CURRENT_REGION((int)ce_region) sets ce_region
 * to be the current region.  This operation and the notion of
 * current region are used to direct keyboard actions between
 * INTERM and MISC region.  Thus, ce_region in this operation
 * can only be INTERM or MISC.
 */
#define ENV_NOP			68
/*
 * ENV_NOP() is a nop  to SE.  This nop is used when CM does not
 * have any operation return to ENV.
 */
#define ENV_RTN_VALUE		69
/*
 * ENV_RTN_VALUE((int)ce_rtn_value) returns in ce_rtn_value
 * the value requested via CM_GET_CONVID, CM_GET_CONVOPT, or
 * CM_GET_CONVLEVEL.
 */
#define ENV_CM_OFF		70
/*
 * ENV_CM_OFF tells ENV to turn off the CM. If there is an automatic
 * commit, CM does it.
 */
#define ENV_SETKEY_CM_ON	71
/*
 * ENV_SETKEY_CM_ON ((int)ce_rtn_value) sets cm_on key
 */

#define	ENV_INTERM_RESET	81
/*
 * ENV_INTERM_RESET() resets everything in the INTERM region.
 */
#define ENV_INTERM		82
/*
 * ENV_INTERM((int)ce_cursor, (int)ce_cursor_type, (e_char *)ce_text,
 * (u_char *)ce_text_attr, (int)ce_v_pos, (int)ce_v_type) specifies 
 * the entire intermediate region.
 */
#define ENV_I_INSERT		83
/*
 * ENV_I_INSERT((e_char *)ce_text, (u_char *)ce_text_attr) inserts
 * the string ce_string after the cursor (i.e. starting at
 * ir_text[ir_cursor]) and moves the cursor to the right by
 * the length of ce_string.
 */
#define ENV_I_DELETE		87
/*
 * ENV_I_DELETE((int)ce_nchar) deletes ce_nchar e_char's to the left
 * of the cursor and move the cursor ce_nchar positions to the left.
 * (Ir_text[ir_cursor-ce_nchar] to ir_text[ir_cursor-1] are deleted.)
 */
#define ENV_I_SET_CURSOR	86
/*
 * ENV_I_SET_CURSOR((int)ce_cursor, (int)ce_cursor_type) sets the cursor
 * position and its type.
 */

/* Operation for the Selection Region */
/*
 *
 * CM enters into a selection phase when it sees a specified control
 * key from CM_SIMPLE_EVENT(stc_key).  ENV enters into a selection
 * phase when CM issues a ENV_SELECT(ce_ncandidate, ...) operation.
 * ENV exits from a selection phase when the user makes a seclection
 * or aborts the selection, either through the mouse or the keyboard.
 * CM exits from a selection phase when it gets CM_SELECT(stc_select)
 * or CM_ABORT_SELECTION() from SE.
 * ENV can send CM all key event instead of doing all seleciont phase
 * by itself. In that case, CM will use EVN_SELECT_END, ENV_SELECT_NEXT,
 * ENV_SELECT_PREV, ENV_SELECT_COMMIT, ENV_NEXT_CAN, ENV_PREV_CAN.
 */

#define ENV_SELECT_RESET	101
/* ENV_SELECT_RESET() resets the selection region. */
#define ENV_SELECT		102
/*
 * ENV_SELECT(((int)ce_ncandidate, (e_char **)ce_candidate,
 * (int)ce_prevexist, (int)ce_nextexist, (e_char *)ce_sel_prompt)
 * makes ENV enter into a selection phase by setting sr_ncandidate
 * to ce_ncandidate, sr_candidate to ce_candidate,
 * sr_prev_exist to ce_prevexist, * and sr_next_exist to ce_nextexist.
 * CM is also in the selection phase until it receives
 * CM_SELECT or CM_ABORT_SELECTION from ENV.
 */

#define ENV_SELECT_END		103 
/*
 * ENV_SELECT_END() tells ENV to end the selection phase.
 */
#define ENV_SELECT_NEXT 	104
/*
 * ENV_SELECT_NEXT() tells ENV to display the next set of the candidates
 * This operation will be used when ENV sends key event to CM while
 * selection phase.
 */
#define ENV_SELECT_PREV		105
/*
 * ENV_SELECT_PREV() tells ENV to display the previous set of the candidates
 * This operation will be used when ENV sends key event to CM while
 * selection phase.
 */
#define ENV_SELECT_COMMIT	107
/*
 * ENV_SELECT_COMMIT((e_char *)ce_sel_string, (u_char)ce_sel_commit_flag)
 * request SE to select one candidate which
 * title is matches the string (ce_sel_string).
 * When ENV can select one of them, ENV will
 * send CM_SELECT with candidate id. When ENV
 * can't select one by some reason, ENV will
 * send CM_SELECT_INVALID with invalid status.
 * (See CM_SELECT_INVALID)
 * In the case of AMB_C and COMMIT_NOTC, if ce_sel_commit_flag
 * is TRUE, ENV will select one candidate.
 * If the flag if FALSE, ENV will return CM_SELECT_INVALID.
 */
#define ENV_SELECT_NEXT_CAN	108
/* 
 * ENV_SELECT_NEXT_CAN() requests ENV to move focus to the next candidate
 */
#define ENV_SELECT_PREV_CAN	109
/* 
 * ENV_SELECT_NEXT_CAN() requests ENV to move focus to the previous candidate
 */
#define ENV_SELECT_TEST		110
/*
 * ENV_SELECT_TEST((e_char *)ce_sel_string) requests ENV ot compair the
 * string with selection titiles. ENV will send CM_SELECT_INVALID with the
 * result of the pomparison.
 */

/* Operation for Mode Region */

#define ENV_SET_MODE            115
/*
 * ENV_SET_MODE((e_char *)ce_mode_list) sets the mode.
 * ce_mode_data is mode_name.
 * ENV will display the corresponding string for the mode.
 */

/*
 * #define ENV_SET_MODE_DATA       116
 * This operation is obsolete.
 *
 * ENV_SET_MODE_DATA((e_char *)ce_mode_data) send a mode-binding data.
 */

#define ENV_SET_SIMPLE_MODE     117
/* ENV_SET_SIMPLE_MODE((e_char *)ce_string) sets the mode to ce_string,
 * ENV will display the corresponding string for the mode.
 */

/* Operation for MISC Region */

#define ENV_MISC_RESET		121	
/*
 * ENV_MISC_RESET() resets the misc region.
 */

#define ENV_M_INTERACTIVE	122
/* 
 * ENV_M_INTERACTIVE((int)ce_cursor, (int)ce_cursor_type, (e_char *)ce_text,
 * (u_char *)ce_text_attr,(int)ce_v_pos,(int)ce_v_type) specifies the 
 * entire misc region.
 * previously ENV_MISC	
 */
#define ENV_M_I_SET_CURSOR	123 
/*
 * ENV_M_I_SET_CURSOR((int)ce_cursor, (int)ce_cursor_type) sets the cursor
 * position and its type.
 */
#define ENV_M_I_INSERT		124
/*
 * ENV_M_I_INSERT((e_char *)ce_text, (u_char *)ce_text_attr) inserts
 * the string ce_string after the cursor (i.e. starting at
 * ce_text[ce_cur_pos]) and moves the cursor to the right by
 * the length of ce_string.
 */
#define ENV_M_I_DELETE		125
/*
 * ENV_M_I_DELETE((int)ce_nchar) deletes ce_nchar e_char's to the left
 * of the cursor and move the cursor ce_nchar positions to the left.
 * (ce_text[ce_cursor - ce_nchar] to ce_text[ce_cursor - 1] are deleted.)
 */
#define ENV_M_LABEL		126
/*
 * ENV_M_LABEL((e_char *)ce_misc_text) spcifies the string to be displayed on
 * MICS-LABEL region
 */
#define ENV_M_MESS		127
/*
 * ENV_M_MESS((e_char *)ce_misc_text,(int)ce_m_prevexist, (int)ce_m_nextexist)
 * specifies the data to be displayed on MISC-MESSAGE region 
 * (FOR JLS1.0, ce_m_prevexist, ce_m_nextexist are always false )
 */
#define ENV_M_MESS_NEXT_P	128
/*
 * ENV_M_MESS_NEXT_P() tells ENV to display  the next block of message data
 */
#define ENV_M_MESS_PREV_P	129
/*
 * ENV_M_MESS_PREV_P() tells ENV to display  the previous block of message data
 */

#define	ENV_ERROR		140
/*
 * ENV_ERROR(ce_err_level, ce_err_id, ce_err_mess) will tell the error
 * information, which found and/or causes by CM.  The "ce_err_id" is
 * currently fake and no plan to support in JLE1.X release.
 */


/* ce_text_att
 * used by ENV_INTERM, ENV_I_SET_ATT, ENV_MISC, ENV_M_SET_ATT
 */

#define ATTR_COLOR_MASK			0xF0
#define ATTR_BKGND_MASK			0x0F
/*
 * Note: How to display is upto ENV.  I still like to let CM to tell
 * ENV some chars need to be displayed differently from other if ENV can.
 * E.g. ENV may have different display technique than upperline and
 * overline.  Also, we use reverse video for NORMAL intermediate
 * region.
 */
#define ATTR_REVERSE			0x01
#define ATTR_UNDERLINE			0x02
#define ATTR_UPPERLINE			0x04
#define ATTR_OVERLINE			0x08

/* 
 * Position to be displeyd 	
 */

#define POS_END				0x01
/* 
 * ENV has to display the string before the ce_text[ce_v_pos] 
 * as long as ENV can.
 */
#define POS_START			0x02
/* 
 * ENV has to display the string after the ce_text[ce_v_pos] 
 * as long as ENV can.
 */
#define POS_MID				0x03
/* 
 * ENV has to display the string at the point that ce_text[ce_v_pos] 
 * will be the middle of the display area.
 */

/* ce_region 
 * used by ENV_REGION_CTL, ENV_SET_CURRENT_REGION 
 */

#define TEXT_REGION	0
#define INTERM_REGION	1
#define MISC_REGION	2
#define SELECT_REGION	3
#define MODE_REGION	4
