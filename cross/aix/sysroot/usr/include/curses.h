#ifndef _AIX32_CURSES

/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/ccs/lib/libxcurses/copyright.h 1.2                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1994,1996          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)97	1.2  src/bos/usr/ccs/lib/libxcurses/copyright.h, libcurses, bos530 2/29/96 10:34:49  */
/*
 *   COMPONENT_NAME: LIBCURSES
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27, 110
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1994,1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * Copyright (c) 1984-1994
 * Novell, Inc. All Rights Reserved.
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF Novell Inc.
 * The copyright notice above does not evidence any 
 * actual or intended publication of such source code.
 */
/*      Copyright (c) 1984 AT&T
 *        All Rights Reserved
 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
 *      The copyright notice above does not evidence any
 *      actual or intended publication of such source code.
 */

#ifdef IDENT
#ident  "$Header: copyright.h 1.2 91/06/26 $"
#endif /* IDENT */
#ifdef IDENT
#ident	"@( #)curses:common/lib/xlibcurses/screen/curses.ed	1.60.2.8"
#ident "$Header: /u/hotdev/sandbox/russv/fomp/curses/RCS/\
curses.ed,v 3.10 1995/11/15 17:31:26 RUSSV Exp $"
#endif /* IDENT */
 
/*
 * curses.h - this file is automatically made from caps and
 *	curses.ed. Don't make changes directly to curses.h!
 */

#define _XOPEN_CURSES   4002

#ifndef CURSES_H

#define CURSES_H	/* define prevents multiple includes */
#include <wchar.h>	/* Let the system typedef wchar_t */

#ifndef __attr_t_
        #define __attr_t_
        typedef int attr_t;
#endif

#ifndef SYSV
#define SYSV
#endif
#define ZLC_MOD_MAX	5

#define SETMCC(__wc)		((__wc).c = 0)
#define CLRMCC(win, __wc)	((__wc) = (win)->_bkgd)
#define ISMCC(__wc)		((__wc).c == 0)

#ifndef __cchar_t_
        #define __cchar_t_
        typedef struct {
             attr_t  a;
             wchar_t c;
             wchar_t z[ZLC_MOD_MAX];
        } cchar_t;
#endif

#define	CSMAX	4

#include  <stdio.h>

#ifdef LINT
#ifdef NULL
#undef NULL
#endif
#define NULL 0L
#endif /* LINT */

  /*
   * This trick is used to distinguish between SYSV and V7 systems.
   * We assume that L_ctermid is only defined in stdio.h in SYSV
   * systems, but not in V7 or Berkeley UNIX.
   */
#if 0
#ifdef L_ctermid
# define SYSV
#endif
#endif

   /* Some V7 systems define L_ctermid - we list those here */
#ifdef BSD
# undef SYSV
#endif

#ifndef __SGTTY_
#  define __SGTTY_
#ifdef SYSV
# ifndef VINTR
#  ifndef __DOT1
#  include <termio.h>
#endif  /*  __DOT1     */
#  include <termios.h>
# endif /* VINTR */
    typedef struct termios SGTTY;
#else /* !SYSV */
# ifndef _SGTTYB_
#  include <sgtty.h>
# endif /* _SGTTYB_ */
    typedef struct sgttyb SGTTY;
#endif /* SYSV */
#endif /* __SGTTY_ */

#if !defined(__cplusplus) || (defined(__IBMCPP__) &&(__IBMCPP__<400))
#ifndef _BOOL
#define _BOOL
typedef int bool;
#endif
#endif

#include <term.h>

#define _VR3_COMPAT_CODE

/*
 * chtype is the type used to store a character together with attributes.
 * It can be set to "char" to save space, or "int" to get more attributes.
 */
#ifdef	CHTYPE
	typedef	CHTYPE chtype;
#else
	typedef unsigned int chtype;
#endif /* CHTYPE */

/*
	Define for the 'old' definition of chtype is required
	when we are running in compatibility mode
*/
#ifdef _VR3_COMPAT_CODE
typedef unsigned short _ochtype;
#endif

/* TRUE and FALSE get defined so many times, */
/* let's not get in the way of other definitions. */
#if	!defined(TRUE) || ((TRUE) != 1)
#define	TRUE	(1)
#endif
#if	!defined(FALSE) || ((FALSE) != 0)
#define	FALSE	(0)
#endif
#if	!defined(ERR) || ((ERR) != -1)
#define	ERR	(-1)
#endif
#if	!defined(OK) || ((OK) != 0)
#define	OK	(0)
#endif

/* short-hand notations */
typedef struct _win_st	WINDOW;
typedef struct screen	SCREEN;
typedef struct _Mouse	MOUSE_STATUS;

struct _win_st
{
	short		_cury, _curx;	/* current coordinates */
	short		_maxy, _maxx;	/* max coordinates */
	short		_begy, _begx;	/* (0,0) screen coordinates */
	char		_flags;
	short		_yoffset;	/* actual begy is _begy+_yoffset */
	bool		_clear,		/* clearok() info */
			_leave,		/* leaveok() info */
			_immed,		/* window in immediate mode */
			_sync;		/* auto syncup of parent */
	WINDOW		*_padwin;	/* "pad" area for current window */
	short		*_firstch;	/* first change in line */
	short		*_lastch;	/* last change in line */
	short		_tmarg, _bmarg;	/* scrolling region bounds */
					/* MUST stay at this offset in WINDOW */
	unsigned	_scroll		: 1;	/* scrollok() info */
	unsigned	_use_idl	: 1;	
	unsigned	_use_keypad	: 1;
	unsigned	_notimeout	: 1;
	unsigned	_use_idc	: 1;	
	attr_t		_attrs;		/* current window attributes */
	cchar_t		_bkgd;		/* background, normally blank */
	int		_delay;		/* delay period on wgetch
					 * 0:  for nodelay
					 * <0: for infinite delay
					 * >0: delay time in units of millisec
					 */
	short		_ndescs;	/* number of descendants */
	short		_parx, _pary;	/* coords relative to parent (0,0) */
	WINDOW		*_parent;	/* the parent if this is a subwin */
	cchar_t		**_y;		/* lines of data */

	char		_waitc[CSMAX+1];/* array to store partial m-width char*/
};

/* _lastch is initially set to this, _firstch is set to win->_maxx */
#define	_NOCHANGE	-1
#define _INFINITY	16000	/* no line can be longer than this */

/* values for win->_flags */
#define	_ISPAD		001
#define	_WINCHANGED	002
#define	_WINMOVED	004
#define	_WINSDEL	010
#define	_CANT_BE_IMMED	020
#define	_WIN_ADD_ONE	040
#define	_WIN_INS_ONE	100

struct _Mouse {
	int x, y;
	short button[3];
	int   changes;
};

#define CURS_STUPID	0
#define CURS_UNKNOWN	1
#define CURS_BAD_MALLOC	2

/*
 * Various tricks to shut up lint about things that are perfectly fine.
 */
#if	defined(lint) && !defined(CURSES) /* if not internal to curses source */
 struct screen {
	 int _nobody_;
 };
#endif /* lint */

/* common external variables */

extern	int	LINES, COLS, TABSIZE, COLORS, COLOR_PAIRS;

extern	short	curs_errno;

extern	WINDOW	*stdscr, *curscr;

extern  MOUSE_STATUS	Mouse_status;

extern	char	ttytype[];

extern char	curs_parm_err[],
		*curs_err_strings[];

extern	cchar_t	*wacs_map;

#ifdef _ACS_COMPAT_CODE
extern	chtype acs32map[0400];
#endif

/* Function declarations */

#ifdef	_VR3_COMPAT_CODE

/* definitions for Vr3 source compatibility */

#define initscr		initscr32
#define newterm		newterm32
#define waddch		w32addch
#define wechochar	w32echochar
#define pechochar	p32echochar
#define winsch		w32insch
#define vidputs		vid32puts
#define vidattr		vid32attr
#define wattroff	w32attroff
#define wattron		w32attron
#define wattrset	w32attrset
#define acs_map		acs32map
#define box		box32

/* declarations for mini-curses */

#if defined(__STDC__) || !defined(_NO_PROTO)
extern	WINDOW	*m_initscr(void);

extern	SCREEN	*m_newterm(char *, FILE *, FILE *);

extern	int	m_addch(int), m_addstr(char *), m_clear(void), m_erase(void),
		m_move(int, int), m_refresh(void);

#else  /* __STDC__ */
extern	WINDOW	*m_initscr();

extern	SCREEN	*m_newterm();

extern	int	m_addch(), m_addstr(), m_clear(), m_erase(),
		m_move(), m_refresh();

#endif /* __STDC__ */

#endif	/* _VR3_COMPAT_CODE */

#if defined(__STDC__) || !defined(_NO_PROTO)

extern	SCREEN	*newscreen(char *, int, int, int, FILE *, FILE *),
		*setcurscreen(SCREEN *);

extern	WINDOW	*initscr(void),
		*newwin(int, int, int, int),
		*newpad(int, int),
		*derwin(WINDOW *, int, int, int, int),
		*dupwin(WINDOW *),
		*getwin(FILE *);

extern	int	wgetch(WINDOW *); /* it can return KEY_*, for instance. */

extern  int     chgat(int, attr_t, short, const void *),
                mvchgat(int, int, int, attr_t, short, const void *),
                mvwchgat(WINDOW *, int, int, int, attr_t, short, const void *),
                wchgat(WINDOW *, int, attr_t, short, const void *); 

extern	char	*longname(void),	/* long name of terminal */
		*termname(void),	/* effective terminal name */
		*keyname(int), 	/* name of token returned by wgetch() */
		*key_name(wchar_t), 
		*slk_label(int),
		erasechar(void),
		killchar(void),
		*unctrl(chtype);

extern  wchar_t *wunctrl(cchar_t *);

extern  int     erasewchar(wchar_t *), killwchar(wchar_t *);

extern  chtype	termattrs(void);

extern  attr_t	term_attrs(void);

extern  int     vidputs(chtype, int (*)(int)), vidattr(chtype),
                vid_puts(attr_t, short, void *, int (*)(int)),
                vid_attr(attr_t, short, void *);

extern	void	vidupdate(chtype, chtype, int (*)(int)),
		wsyncup(WINDOW *), wsyncdown(WINDOW *),
		delscreen(SCREEN *), curserr(void),
		_setqiflush(int),
		wcursyncup(WINDOW *);

extern	int	cbreak(void), nocbreak(void),
		reset_prog_mode(void), reset_shell_mode(void),
		def_prog_mode(void), _setecho(int), _setnonl(int),
		def_shell_mode(void), raw(void),
		savetty(void), traceon(void), _meta(int),
		traceoff(void), noraw(void), flushinp(void),
		_getsyx(int *, int *),
		_ring(int), resetty(void),
		ripoffline(int, int (*)(WINDOW *, int)),
		setsyx(int, int), slk_refresh(void),
		slk_restore(void),
		wstandend(WINDOW *), wstandout(WINDOW *),
		wattroff(WINDOW *, int), wattron(WINDOW *, int),
		wattrset(WINDOW *, int), 
                wattr_off(WINDOW *, attr_t, void *),
                wattr_on(WINDOW *, attr_t, void *),
	        wattr_set(WINDOW *, attr_t, short, void *),
		wrefresh(WINDOW *);

extern	int	copywin(const WINDOW * , WINDOW *,int,int,int,int,int,int,int),
		curs_set(int), delay_output(int), delwin(WINDOW *),
		doupdate(void), draino(int), endwin(void), 
		baudrate(void), 
		keypad(WINDOW *, bool),
		mvcur(int, int, int, int);

extern	int	mvprintw(int, int, char *, ...), mvscanw(int, int, char *, ...),
		mvwprintw(WINDOW *, int, int, char *, ...),
		mvwscanw(WINDOW *, int, int, char *, ...),
		printw(char *, ...), scanw(char *, ...),
		wprintw(WINDOW *, char *, ...), wscanw(WINDOW *, char *, ...);

		/* in the following 2 functions 'void *' is really va_list */
		/* however, we cannot include <stdarg.h> in curses.h,      */
		/* because some applications may be using <varargs.h> that */
		/* conflicts with <stdarg.h>				   */

extern  int	vwprintw(WINDOW *, char *, void *),
        	vw_printw(WINDOW *, char *, void *),
		vwscanw(WINDOW *, char *, void *),
		vw_scanw(WINDOW *, char *, void *);
extern int vsscanf(const char *, const char *, va_list); 
/* extern int vsscanf(const char *, const char *, void * ); */

extern	int	mvwin(WINDOW *, int, int), mvderwin(WINDOW *, int, int),
		napms(int), newkey(char *, int, int),
		_overlay (WINDOW *, WINDOW *, int),
		pechochar(WINDOW *, chtype),
		pnoutrefresh(WINDOW *, int, int, int, int, int, int),
		prefresh(WINDOW *, int, int, int, int, int, int);

extern  void	filter(void);

extern  int     wattr_get(WINDOW *, attr_t *, short *, void *);

extern 	int	putwin(WINDOW *, FILE *), wredrawln(WINDOW *, int, int),
		scr_dump(const char *), setupterm(char *, int, int *);

extern	int	slk_attron(const chtype), slk_attroff(const chtype),                             slk_attrset(const chtype),
        	slk_attr_on(const attr_t, void *), 
		slk_attr_off(const attr_t, void *),     
                slk_attr_set(const attr_t, short, void *),
		slk_clear(void), slk_noutrefresh(void),
		slk_color(short),
		slk_set(int, const char *, int),
		slk_wset(int, const wchar_t *, int),
		slk_start(int, int *), slk_touch(void), start_color(void),
		typeahead(int);

extern	bool	can_change_color(void), has_colors(void), has_ic(void),
                has_il(void), isendwin(void);
		
extern int	waddch(WINDOW *, const chtype),
		waddchnstr(WINDOW *, const chtype *, int),
		waddnstr(WINDOW *, const char * , int),
		wbkgd(WINDOW *, chtype),
		wborder(WINDOW *, chtype, chtype, chtype, chtype,
				  chtype, chtype, chtype, chtype),
		wclrtobot(WINDOW *), wclrtoeol(WINDOW *),
		wdelch(WINDOW *), wechochar(WINDOW *, const chtype),
		wgetstr(WINDOW *, char *),
		wgetnstr(WINDOW *, char *, int),
		whline(WINDOW *, chtype, int),
		wvline(WINDOW *, chtype, int),
		winchnstr(WINDOW *, chtype *, int),
		winchstr(WINDOW *, chtype *),
		winnstr(WINDOW *, char *, int),
		winsch(WINDOW *, chtype),
		winsdelln(WINDOW *, int),
		winsnstr(WINDOW *, const char *, int),
		winstr(WINDOW *, char *),
		wmove(WINDOW *, int, int),
		wnoutrefresh(WINDOW *),
		wredrawln(WINDOW *, int, int),
		wscrl(WINDOW *, int),
		wsetscrreg(WINDOW *, int, int),
		wtouchln(WINDOW *, int, int, int);

extern	int	crmode(void), nocrmode(void), ungetch(int);

extern	int	mouse_set(long int), mouse_on(long int),
		mouse_off(long int), request_mouse_pos(void),
		map_button(unsigned long);

extern	void	wmouse_position (WINDOW *, int *, int *);

extern unsigned long getmouse(void), getbmap(void);
		
extern	int	PAIR_NUMBER(int); 

extern	int	pair_content(short, short *, short *),
		color_content(short, short *, short *, short *),
		COLOR_PAIR(int),
		init_color(short, short, short, short),
		init_pair(short, short, short),
		idlok(WINDOW *, bool);

extern	void	immedok(WINDOW *, bool);

extern int	unget_wch(const wchar_t),
		waddnwstr(WINDOW *, const wchar_t *, int),
		wgetn_wstr(WINDOW *, wint_t *, int),
		wget_wch(WINDOW *, wint_t *),
		wget_wstr(WINDOW *, wint_t *),
		winnwstr(WINDOW *, wchar_t *, int),
		wins_nwstr(WINDOW *, const wchar_t *, int),
		wins_wch(WINDOW *, const cchar_t *),
		win_wchnstr(WINDOW *, cchar_t *, int),
		winwstr(WINDOW *, wchar_t *);

int add_wch(const cchar_t * );	
int win_wch(WINDOW *, cchar_t *);
int wadd_wch(WINDOW *, const cchar_t * );
int mvadd_wch(int, int, const cchar_t * );
int mvwadd_wch(WINDOW *, int, int, const cchar_t *);
int add_wchnstr(const cchar_t * , int);
int add_wchstr(const cchar_t * );
int wadd_wchnstr(WINDOW *, const cchar_t * , int);
int wadd_wchstr(WINDOW *, const cchar_t * );
int mvadd_wchnstr(int, int, const cchar_t * , int);
int mvadd_wchstr(int, int, const cchar_t * );
int mvwadd_wchnstr(WINDOW *, int, int, const cchar_t * , int);
int mvwadd_wchstr(WINDOW *, int, int, const cchar_t * );
void bkgrndset(const cchar_t *);
int bkgrnd(const cchar_t *);
int getbkgrnd(cchar_t *);
int wbkgrnd(WINDOW *, const cchar_t *);
void wbkgrndset(WINDOW *, const cchar_t *);
int wgetbkgrnd(WINDOW *, cchar_t *);
int border_set(const cchar_t *, const cchar_t *, const cchar_t *,
               const cchar_t *, const cchar_t *, const cchar_t *,
               const cchar_t *, const cchar_t *);
int wborder_set(WINDOW *, const cchar_t *, const cchar_t *,
                const cchar_t *, const cchar_t *, const cchar_t *,
                const cchar_t *, const cchar_t *, const cchar_t *);
int box_set(WINDOW *, const cchar_t *, const cchar_t *);
int getcchar(const cchar_t *, wchar_t *, attr_t *, short *, void *);
int setcchar(cchar_t *, const wchar_t *, const attr_t, short, const void *);
int hline_set(const cchar_t *, int);
int mvhline_set(int, int, const cchar_t *, int);
int mvvline_set(int, int, const cchar_t *, int);
int mvwhline_set(WINDOW *, int, int, const cchar_t *, int);
int mvwvline_set(WINDOW *, int, int, const cchar_t *, int);
int whline_set(WINDOW *, const cchar_t *, int);
int vline_set(const cchar_t *, int);
int wvline_set(WINDOW *, const cchar_t *, int);
int pecho_wchar(WINDOW *, const cchar_t *);
int echo_wchar(const cchar_t *);
int wecho_wchar(WINDOW *, const cchar_t *);
int wget_wch(WINDOW *, wint_t *);
int wget_wstr(WINDOW *, wint_t *);
int wgetn_wstr(WINDOW *, wint_t *, int);
int wins_wch(WINDOW *, const cchar_t *);

#else /* __STDC__ */

extern	SCREEN	*newscreen(/*termname,lines,cols,tabsiz,fout,fin*/),
		*setcurscreen(/*screenptr*/);

extern	WINDOW	*initscr(),
		*newwin(/*nlines,ncols,begy,begx*/),
		*newpad(/*nlines,ncols*/),
		*derwin(/*orig,nlines,ncols,begy,begx*/),
		*dupwin(/*orig*/),
		*getwin(/*file*/);

extern	int	wgetch(); /* because it can return KEY_*, for instance. */

extern  int     chgat(),
                mvchgat(),
                mvwchgat(),
                wchgat(); 

extern	char	*longname(),	/* long name of terminal */
		*termname(),	/* effective terminal name */
		*keyname(/*int*/), /* name of token returned by wgetch() */
		*key_name(),
		*slk_label(/*index*/),
		erasechar(),
		killchar(),
		*unctrl();

extern  wchar_t *wunctrl();

extern	chtype	termattrs();

extern  attr_t 	term_attrs();

extern  int     erasewchar(), killwchar(), getcchar(), setcchar();

extern  int     vidputs(), vidattr(),
                vid_puts(),
                vid_attr();       

extern	void	vidupdate(), wsyncup(), wsyncdown(),
		delkeymap(),
		delscreen(), curserr(),
		_setqiflush(),
		immedok(),
		wcursyncup();

extern	int	cbreak(), nocbreak(),
		reset_prog_mode(), reset_shell_mode(), def_prog_mode(),
		_setecho(), _setnonl(),
		def_shell_mode(), raw(),
		savetty(), traceon(), _meta(),
		traceoff(), noraw(), flushinp(), _getsyx(),
		_ring(), resetty(), ripoffline(), setsyx(), slk_refresh(),
		slk_restore(), wstandend(), wstandout(),
		wattroff(), wattron(), wattrset(), wrefresh();

extern	int	color_cont(), copywin(), curs_set(), delay_output(), delwin(),
		doupdate(), draino(), endwin(), 
		baudrate(), idlok(), COLOR_PAIR(),
		init_color(), init_pair(), keypad(), mvcur();

extern int    PAIR_NUMBER();

extern int      mvprintw(), mvscanw(), mvwprintw(), mvwscanw(),
                printw(), scanw(), wprintw(), wscanw(), vwprintw(), vwscanw(), 
                vw_printw(), vw_scanw();
 
extern	int	vsscanf();

extern	int	mvwin(), mvderwin(), napms(), newkey(), _overlay(),
		pair_content(), pechochar(), pnoutrefresh(), prefresh();

extern	void	filter();

extern 	int	putwin(), wredrawln(), scr_dump(), setupterm();

extern	int	slk_attroff(), slk_attron(), slk_attrset(),
        	slk_attr_off(), slk_attr_on(), slk_attr_set(),
		slk_clear(), slk_noutrefresh(), slk_set(), slk_wset(),
		slk_start(), slk_touch(), start_color(), slk_color(),
		typeahead();

extern	bool	can_change_color(), has_colors(), has_ic(), has_il(),
                isendwin();
		
extern	int	waddch(), waddchnstr(), waddnstr(), wbkgd(),
		wborder(), wclrtobot(), wclrtoeol(), wdelch(), wechochar(),
		wgetstr(), wgetnstr(), whline(), wvline(), winchnstr(),
		winchstr(), winnstr(), winsch(),
		winsdelln(),		/*internal */
		winsnstr(), winstr(), wmove(), wnoutrefresh(), wredrawln(),
		wscrl(), wsetscrreg(), wtouchln();

extern	int	crmode(), nocrmode(), ungetch();

extern	int	mouse_set(), mouse_on(), mouse_off(),
		request_mouse_pos(), map_button();
		
extern void	wmouse_position();

extern unsigned long getmouse(), getbmap();

extern int      unget_wch();

extern int	waddnwstr(), 
		wgetn_wstr(), wget_wch(),
		wget_wstr(), winnwstr(), wins_nwstr(), wins_wch(),
		win_wchnstr(), winwstr();

extern int add_wch();
extern int win_wch();
extern int add_wchnstr();
extern int add_wchstr();
extern int bkgrnd();
extern int border_set();
extern int box_set();
extern int echo_wchar();
extern int getbkgrnd();
extern int hline_set();
extern int mvadd_wch();
extern int mvadd_wchnstr();
extern int mvadd_wchstr();
extern int mvhline_set();
extern int mvvline_set();
extern int mvwadd_wch();
extern int mvwadd_wchnstr();
extern int mvwadd_wchstr();
extern int mvwhline_set();
extern int mvwvline_set();
extern int pecho_wchar();
extern int vline_set();
extern int wadd_wch();
extern int wadd_wchnstr();
extern int wadd_wchstr();
extern int wbkgrnd();
extern int wborder_set();
extern int wecho_wchar();
extern int wget_wch();
extern int wget_wstr();
extern int wgetbkgrnd();
extern int wgetn_wstr();
extern int whline_set();
extern int wins_wch();
extern int wvline_set();
extern void bkgrndset();
extern void wbkgrndset();
#endif /* __STDC__ */

#define getsyx(y,x)		_getsyx(&(y),&(x))

/*
 * Functions to get at the window structure.
 */

#define getyx(win,y,x)		((y) = getcury(win), (x) = getcurx(win))
#define	getbegyx(win,y,x)	((y) = getbegy(win), (x) = getbegx(win))
#define	getmaxyx(win,y,x)	((y) = getmaxy(win), (x) = getmaxx(win))
#define	getparyx(win,y,x)	((y) = getpary(win), (x) = getparx(win))

#if	defined(CURS_PERFORMANCE) && !defined(lint)
#define getcury(win)		((win)->_cury)
#define getcurx(win)		((win)->_curx)
#define	getbegy(win)		((win)->_begy)
#define	getbegx(win)		((win)->_begx)
#define	getmaxy(win)		((win)->_maxy)
#define	getmaxx(win)		((win)->_maxx)
#define	getpary(win)		((win)->_pary)
#define	getparx(win)		((win)->_parx)
#define getbkgd(win)		((win)->_bkgd)
#define getattrs(win)		((win)->_attrs)
#else 	/* defined(CURS_PERFORMANCE) && !defined(lint) */

#if defined(__STDC__) || !defined(_NO_PROTO)
extern	int	getcury(WINDOW *), getcurx(WINDOW *),
		getbegy(WINDOW *), getbegx(WINDOW *),
		getmaxy(WINDOW *), getmaxx(WINDOW *),
		getpary(WINDOW *), getparx(WINDOW *);

extern chtype	getbkgd(WINDOW *), getattrs(WINDOW *);

#else  /* __STDC__ */
extern	int	getcury(), getcurx(), getbegy(), getbegx(),
		getmaxy(), getmaxx(), getpary(), getparx();

extern chtype	getbkgd(), getattrs();

#endif  /* __STDC__ */
#endif	/* defined(CURS_PERFORMANCE) && !defined(lint) */

#if	defined(NOMACROS) || defined(lint)

#if defined(__STDC__) || !defined(_NO_PROTO)

SCREEN	*newterm(char *, FILE *, FILE *);
SCREEN *set_term(SCREEN *);

WINDOW *subpad(WINDOW *, int, int, int, int);
WINDOW *subwin(WINDOW *, int, int, int, int);

char *unctrl(chtype);

wchar_t *wunctrl(cchar_t *);

chtype inch(void);
chtype winch(WINDOW *);
chtype mvinch(int, int);
chtype mvwinch(WINDOW *, int, int);

int addch(const chtype);
int addchnstr(const chtype *, int);
int addchstr(const chtype *);
int addnstr(const char *, int);
int addstr(const char *);
int attroff(int);
int attr_off(attr_t attrs, void *opts);    
int attron(int);
int attr_on(attr_t attrs, void *opts); 
int attrset(int);
int attr_set(attr_t attrs, short color_pair_number, void  *opts);
int color_set(short color_pair_number, void  *opts);
int wcolor_set(WINDOW *, short color_pair_number, void  *opts);
int attr_get(attr_t *attrs, short *color_pair_number, void *opts);
int beep(void);
int bkgd(chtype);
int border(chtype, chtype, chtype, chtype, chtype, chtype, chtype, chtype);
int box(WINDOW *, chtype, chtype);
int chgat(int, attr_t, short, const void *);
int clear(void);
int clearok(WINDOW *, bool);
int clrtobot(void);
int clrtoeol(void);
int crmode(void);
int delch(void);
int deleteln(void);
int echo(void);
int echochar(const chtype);
int erase(void);
int fixterm(void);
int flash(void);
int garbagedlines(WINDOW *, int, int);
int garbagedwin(WINDOW *);
int getch(void);
int getstr(char *);
int gettmode(void);
int halfdelay(int);
int hline(chtype, int);
int inchnstr(chtype *, int);
int inchstr(chtype *);
int innstr(char *, int);
int insch(chtype);
int insdelln(int);
int insertln(void);
int insnstr(const char *, int);
int insstr(const char *);
int instr(char *);
int intrflush(WINDOW *, bool);
bool is_linetouched(WINDOW *, int);
bool is_wintouched(WINDOW *);
int leaveok(WINDOW *, bool);
int meta(WINDOW *, bool);
int move(int, int);
int mvaddch(int, int, const chtype);
int mvaddchnstr(int, int, const chtype *, int);
int mvaddchstr(int, int, const chtype *);
int mvaddnstr(int, int, const char *, int);
int mvaddstr(int, int, const char *);
int mvdelch(int, int);
int mvchgat(int, int, int, attr_t, short, const void *);
int mvwchgat(WINDOW *, int, int, int, attr_t, short, const void *);
int mvgetch(int, int);
int mvgetstr(int, int, char *);
int mvgetnstr(int, int, char *, int);
int mvhline(int, int, chtype, int);
int mvinchnstr(int, int, chtype *, int);
int mvinchstr(int, int, chtype *);
int mvinnstr(int, int, char *, int);
int mvinsch(int, int, chtype);
int mvinsnstr(int, int, const char *, int);
int mvinsstr(int, int, const char *);
int mvinstr(int, int, char *);
int mvvline(int, int, chtype, int);
int mvwaddch(WINDOW *, int, int, const chtype);
int mvwaddchnstr(WINDOW *, int, int, const chtype *, int);
int mvwaddchstr(WINDOW *, int, int, const chtype *);
int mvwaddnstr(WINDOW *, int, int, const char *, int);
int mvwaddstr(WINDOW *, int, int, const char *);
int mvwdelch(WINDOW *, int, int);
int mvwgetch(WINDOW *, int, int);
int mvwgetstr(WINDOW *, int, int, char *);
int mvwgetnstr(WINDOW *, int, int, char *, int);
int mvwhline(WINDOW *, int, int, chtype, int);
int mvwinchnstr(WINDOW *, int, int, chtype *, int);
int mvwinchstr(WINDOW *, int, int, chtype *);
int mvwinnstr(WINDOW *, int, int, char *, int);
int mvwinsch(WINDOW *, int, int, chtype);
int mvwinsnstr(WINDOW *, int, int, const char *, int);
int mvwinsstr(WINDOW *, int, int, const char *);
int mvwinstr(WINDOW *, int, int, char *);
int mvwvline(WINDOW *, int, int, chtype, int);
int nl(void);
int nocrmode(void);
int nodelay(WINDOW *, bool);
int noecho(void);
int nonl(void);
int notimeout(WINDOW *, bool);
int overlay(const WINDOW *, WINDOW *);
int overwrite(const WINDOW *, WINDOW *);
int redrawwin(WINDOW *);
int refresh(void);
int resetterm(void);
int saveterm(void);
int scr_init(const char *);
int scr_restore(const char *);
int scr_set(const char *);
int scrl(int);
int scroll(WINDOW *);
int scrollok(WINDOW *, bool);
int setscrreg(int, int);
int setterm(char *);
int slk_init(int);
int standend(void);
int standout(void);
int syncok(WINDOW *, bool);
int touchline(WINDOW *, int, int);
int touchwin(WINDOW *);
int untouchwin(WINDOW *);
int vline(chtype, int);
int waddchstr(WINDOW *, const chtype *);
int waddstr(WINDOW *, const char *);
int wchgat(WINDOW *, int, attr_t, short, const void *);
int wclear(WINDOW *);
int wdeleteln(WINDOW *);
int werase(WINDOW *);
int getnstr(char *, int);
int winchstr(WINDOW *, chtype *);
int winsertln(WINDOW *);
int winsstr(WINDOW *, const char *);
int winstr(WINDOW *, char *);
int wstandend(WINDOW *);
int wstandout(WINDOW *);

void bkgdset(chtype);
void idcok(WINDOW *, bool);
void noqiflush(void);
void wbkgdset(WINDOW *, chtype);
void qiflush(void);
void timeout(int);
void wtimeout(WINDOW *, int);
void use_env(bool);
int _overlap(register const WINDOW *, WINDOW *, int);
int _scr_all(const char *, int);
int ttimeout(int);

int addnwstr(const wchar_t *, int);
int addwstr(const wchar_t *);
int getn_wstr(wint_t *, int);
int get_wch(wint_t *);
int get_wstr(wint_t *);
int innwstr(wchar_t *, int);
int ins_nwstr(const wchar_t *, int);
int in_wch(cchar_t *);
int ins_wch(const cchar_t *);
int ins_wstr(const wchar_t *);
int in_wchnstr(cchar_t *, int);
int in_wchstr(cchar_t *);
int inwstr(wchar_t *);
int mvaddnwstr(int, int, const wchar_t *, int);
int mvaddwstr(int, int, const wchar_t *);
int mvgetn_wstr(int, int, wint_t *, int);
int mvget_wch(int, int, wint_t *);
int mvget_wstr(int, int, wint_t *);
int mvinnwstr(int, int, wchar_t *, int);
int mvins_nwstr(int, int, const wchar_t *, int);
int mvin_wch(int, int, cchar_t *);
int mvins_wch(int, int, const cchar_t *);
int mvins_wstr(int, int, const wchar_t *);
int mvin_wchnstr(int, int, cchar_t *, int);
int mvin_wchstr(int, int, cchar_t *);
int mvinwstr(int, int, wchar_t *);
int mvwaddnwstr(WINDOW *, int, int, const wchar_t *, int);
int mvwaddwstr(WINDOW *, int, int, const wchar_t *);
int mvwgetn_wstr(WINDOW *, int, int, wint_t *, int);
int mvwget_wch(WINDOW *, int, int, wint_t *);
int mvwget_wstr(WINDOW *, int, int, wint_t *);
int mvwinnwstr(WINDOW *, int, int, wchar_t *, int);
int mvwins_nwstr(WINDOW *, int, int, const wchar_t *, int);
int mvwin_wch(WINDOW *, int, int, cchar_t *);
int mvwins_wch(WINDOW *, int, int, const cchar_t *);
int mvwins_wstr(WINDOW *, int, int, const wchar_t *);
int mvwin_wchnstr(WINDOW *, int, int, cchar_t *, int);
int mvwin_wchstr(WINDOW *, int, int, cchar_t *);
int mvwinwstr(WINDOW *, int, int, wchar_t *);
int waddwstr(WINDOW *, const wchar_t *);
int wins_wstr(WINDOW *, const wchar_t *);
int win_wchstr(WINDOW *, cchar_t *);

#else /* __STDC__ */

extern	SCREEN	*newterm(),
		*set_term();

extern	WINDOW	*subpad(),
		*subwin();

extern	chtype	inch(), winch(), mvinch(), mvwinch();

extern	char	*unctrl();

extern	wchar_t	*wunctrl();

extern int      attr_get(), wattr_get();

extern int	addch(), addchnstr(), addchstr(), addnstr(), addstr(),
		attroff(), attron(), attrset(), beep(), bkgd(),
		border(), box(), clear(), clearok(), clrtobot(), clrtoeol(),
		crmode(), delch(), deleteln(), echo(), echochar(),
		erase(), attr_off(), attr_on(), attr_set(), wattr_off(),
/* MORE */	fixterm(), wattr_on(), wattr_set(), chgat(), mvchgat(),
		flash(), garbagedlines(), garbagedwin(), mvwchgat(),
		getch(), getstr(), gettmode(), halfdelay(), hline(),
		inchnstr(), inchstr(), innstr(), insch(), wchgat(),
		insdelln(), insertln(), insnstr(), insstr(), instr(),
		intrflush(), getnstr(), color_set(), wcolor_set(),
		leaveok(), meta(),
		move(), mvaddch(), mvaddchnstr(), mvaddchstr(), mvaddnstr(),
		mvaddstr(), mvdelch(), mvgetch(), mvgetstr(), mvhline(),
		mvinchnstr(), mvinchstr(), mvinnstr(), mvinsch(), mvinsnstr(),
		mvinsstr(), mvinstr(), mvvline(), mvwaddch(), mvwaddchnstr(),
		mvwaddchstr(), mvwaddnstr(), mvwaddstr(), mvwdelch(),
		mvwgetch(), mvwgetstr(), mvwhline(), mvwinchnstr(),
		mvwinchstr(), mvwinnstr(), mvwinsch(), mvwinsnstr(),
		mvwinsstr(), mvwinstr(), mvwvline(), mvgetnstr(),
		nl(), nocrmode(), nodelay(), mvwgetnstr(),
		noecho(), nonl(), notimeout(),
		overlay(), overwrite(), redrawwin(), refresh(),
		resetterm(), saveterm(), scr_init(),
		scr_restore(), scr_set(), scrl(),
		scroll(), scrollok(), setscrreg(), setterm(),
		slk_init(), standend(), standout(),
		syncok(), touchline(), touchwin(), untouchwin(), vline(),
		waddchstr(), waddstr(), wclear(),
		wdeleteln(), werase(), winchstr(), winsertln(),
		winsstr(), winstr(), wstandend(), wstandout();

extern	void	bkgdset(), wbkgdset(), idcok(), noqiflush(),
		qiflush(), timeout(), wtimeout(), use_env();

extern unsigned long getmouse(), getbmap();

extern int	addnwstr(), _overlap(), _scr_all(), ttimeout(),
		addwstr(), getn_wstr(), get_wch(),
		get_wstr(), innwstr(), ins_nwstr(), ins_wch(),
		ins_wstr(), in_wchnstr(), in_wchstr(), inwstr(),
		mvaddnwstr(),
		mvaddwstr(), mvgetn_wstr(), mvget_wch(), mvget_wstr(),
		mvinnwstr(), mvins_nwstr(), mvins_wch(), mvins_wstr(),
		mvin_wchnstr(), mvin_wchstr(), mvinwstr(), mvwaddnwstr(),
		mvwaddwstr(),
		mvwgetn_wstr(), mvwget_wch(), mvwget_wstr(), mvwinnwstr(),
		mvwins_nwstr(), mvwins_wch(), mvwins_wstr(), mvwin_wchnstr(),
		mvwin_wchstr(), mvwinwstr(), waddwstr(),
		wins_wstr(), win_wchstr();

extern int      in_wch(), mvin_wch(), mvwin_wch(), win_wch();

#endif /* __STDC__ */

#else	/* NOMACROS || lint */

/*
 * The defines from here down to the #endif for NOMACROS
 * define macros, which may be more efficient than their
 * function versions. The functions may be accessed by defining
 * NOMACROS in C code. This is useful for debugging purposes.
 */

#include  <unctrl.h>

/* pseudo functions for stdscr */
#define	addch(ch)		waddch(stdscr, ch)
#define	addchnstr(str,n)	waddchnstr(stdscr,str,n)
#define	addchstr(str)		waddchstr(stdscr,str)
#define	addnstr(s,n)		waddnstr(stdscr,s,n)
#define	addnwstr(ws,n)		waddnwstr(stdscr,ws,n)
#define	addstr(str)		waddstr(stdscr, str)
#define	add_wch(ch)		wadd_wch(stdscr,ch)
#define	add_wchnstr(str,n)	wadd_wchnstr(stdscr,str,n)
#define	add_wchstr(str)		wadd_wchstr(stdscr,str)
#define	addwstr(ws)		waddwstr(stdscr,ws)
#define	attroff(at)		wattroff(stdscr,at)
#define	attr_off(at,v)		wattr_off(stdscr,at,v)
#define	attron(at)		wattron(stdscr,at)
#define	attr_on(at,v)		wattr_on(stdscr,at,v)
#define	attrset(at)		wattrset(stdscr,at)
#define	attr_get(at,n,v)	wattr_get(stdscr,at,n,v)
#define	attr_set(at,n,v)	wattr_set(stdscr,at,n,v)
#define	bkgd(c)			wbkgd(stdscr,c)
#define	bkgdset(c)		wbkgdset(stdscr,c)
#define	border(ls, rs, ts, bs, tl, tr, bl, br) \
			wborder(stdscr, ls, rs, ts, bs, tl, tr, bl, br)	
#define chgat(n,at,sh,v)        wchgat(stdscr,n,at,sh,v)
#define	clrtobot()		wclrtobot(stdscr)
#define	clrtoeol()		wclrtoeol(stdscr)
#define	delch()			wdelch(stdscr)
#define	deleteln()		wdeleteln(stdscr)
#define	echochar(ch)		wechochar(stdscr, ch)
#define	echo_wchar(ch)		wecho_wchar(stdscr,ch)
#define	erase()			werase(stdscr)
#define	getch()			wgetch(stdscr)
#define	getn_wstr(ws,n)		wgetn_wstr(stdscr,ws,n)
#define	getstr(str)		wgetstr(stdscr, str)
#define	getnstr(ch,n)		wgetnstr(stdscr,ch,n)
#define	get_wch(ws)		wget_wch(stdscr,ws)
#define	get_wstr(ws)		wget_wstr(stdscr,ws)
#define	hline(c,num)		whline(stdscr,c,num)
#define	inch()			winch(stdscr)
#define	inchnstr(str,n)		winchnstr(stdscr,str,n)
#define	inchstr(str)		winchstr(stdscr,str)
#define	innstr(str,n)		winnstr(stdscr,(str),(n))
#define	innwstr(ws,n)		winnwstr(stdscr,ws,n)
#define	insch(c)		winsch(stdscr,c)
#define	insdelln(id)		winsdelln(stdscr,id)
#define	insertln()		winsertln(stdscr)
#define	insnstr(s,n)		winsnstr(stdscr,s,n)
#define	ins_nwstr(ws,n)		wins_nwstr(stdscr,ws,n)
#define	insstr(s)		winsstr(stdscr,s)
#define	instr(str)		winstr(stdscr,(str))
#define	ins_wch(c)		wins_wch(stdscr,c)
#define	ins_wstr(ws)		wins_wstr(stdscr,ws)
#define	in_wch(ch)		win_wch(stdscr,ch)
#define	in_wchnstr(str,n)	win_wchnstr(stdscr,str,n)
#define	in_wchstr(str)		win_wchstr(stdscr,str)
#define	inwstr(ws)		winwstr(stdscr,ws)
#define	move(y, x)		wmove(stdscr, y, x)
#define	mvaddch(y,x,ch)		mvwaddch(stdscr,y,x,ch)
#define	mvaddnstr(y,x,s,n)	mvwaddnstr(stdscr,y,x,s,n)
#define	mvaddstr(y,x,str)	mvwaddstr(stdscr,y,x,str)
#define	mvdelch(y,x)		mvwdelch(stdscr,y,x)
#define	mvgetch(y,x)		mvwgetch(stdscr,y,x)
#define	mvchgat(y,x,n,at,c,cn)	mvwchgat(stdscr,y,x,n,at,c,cn)
#define	mvgetstr(y,x,str)	mvwgetstr(stdscr,y,x,str)
#define	mvgetnstr(y,x,str,n)	mvwgetnstr(stdscr,y,x,str,n)
#define	mvinch(y,x)		mvwinch(stdscr,y,x)
#define	mvinsch(y,x,c)		mvwinsch(stdscr,y,x,c)
#define	mvinsnstr(y,x,s,n)	mvwinsnstr(stdscr,y,x,s,n)
#define	mvinsstr(y,x,s)		mvwinsstr(stdscr,y,x,s)
#define	mvaddchstr(y,x,str)	mvwaddchstr(stdscr,y,x,str)
#define	mvaddchnstr(y,x,str,n)	mvwaddchnstr(stdscr,y,x,str,n)
#define	mvinstr(y,x,str)	mvwinstr(stdscr,y,x,(str))
#define	mvinnstr(y,x,str,n)	mvwinnstr(stdscr,y,x,(str),(n))
#define	mvinchstr(y,x,str)	mvwinchstr(stdscr,y,x,str)
#define	mvinchnstr(y,x,str,n)	mvwinchnstr(stdscr,y,x,str,n)
#define	mvhline(y,x,c,num)	mvwhline(stdscr,y,x,c,num)
#define	mvvline(y,x,c,num)	mvwvline(stdscr,y,x,c,num)
#define	mvaddnwstr(y,x,ws,n)	mvwaddnwstr(stdscr,y,x,ws,n)
#define	mvadd_wch(y,x,ch)	mvwadd_wch(stdscr,y,x,ch)
#define	mvadd_wchnstr(y,x,str,n)	mvwadd_wchnstr(stdscr,y,x,str,n)
#define	mvadd_wchstr(y,x,str)	mvwadd_wchstr(stdscr,y,x,str)
#define	mvaddwstr(y,x,ws)	mvwaddwstr(stdscr,y,x,ws)
#define	mvgetn_wstr(y,x,ws,n)	mvwgetn_wstr(stdscr,y,x,ws,n)
#define	mvget_wch(y,x,ws)	mvwget_wch(stdscr,y,x,ws)
#define	mvget_wstr(y,x,ws)	mvwget_wstr(stdscr,y,x,ws)
#define	mvinnwstr(y,x,ws,n)	mvwinnwstr(stdscr,y,x,ws,n)
#define	mvins_nwstr(y,x,ws,n)	mvwins_nwstr(stdscr,y,x,ws,n)
#define	mvin_wch(y,x,c)	        mvwin_wch(stdscr,y,x,c)
#define	mvins_wch(y,x,c)	mvwins_wch(stdscr,y,x,c)
#define	mvins_wstr(y,x,ws)	mvwins_wstr(stdscr,y,x,ws)
#define	mvin_wchnstr(y,x,str,n)	mvwin_wchnstr(stdscr,y,x,str,n)
#define	mvin_wchstr(y,x,str)	mvwin_wchstr(stdscr,y,x,str)
#define	mvinwstr(y,x,ws)	mvwinwstr(stdscr,y,x,ws)
#define	mvwaddch(win,y,x,ch)	(wmove(win,y,x)==ERR?ERR:waddch(win,ch))
#define	mvwaddnstr(win,y,x,s,n)	(wmove(win,y,x)==ERR?ERR:waddnstr(win,s,n))
#define	mvwaddstr(win,y,x,str)	(wmove(win,y,x)==ERR?ERR:waddstr(win,str))
#define	mvwdelch(win,y,x)	(wmove(win,y,x)==ERR?ERR:wdelch(win))
#define	mvwgetch(win,y,x)	(wmove(win,y,x)==ERR?ERR:wgetch(win))
#define	mvwchgat(win,y,x,n,at,c,cn)\
	(wmove(win,y,x)==ERR?ERR:wchgat(win,n,at,c,cn))
#define	mvwgetstr(win,y,x,str)	(wmove(win,y,x)==ERR?ERR:wgetstr(win,str))
#define	mvwgetnstr(win,y,x,str,n)\
	(wmove(win,y,x)==ERR?ERR:wgetnstr(win,str,n))
#define	mvwinch(win,y,x)	(wmove(win,y,x)==ERR?(chtype) ERR:winch(win))
#define	mvwinsch(win,y,x,c)	(wmove(win,y,x)==ERR?ERR:winsch(win,c))
#define	mvwinsnstr(win,y,x,s,n)	(wmove(win,y,x)==ERR?ERR:winsnstr(win,s,n))
#define	mvwinsstr(win,y,x,s)	(wmove(win,y,x)==ERR?ERR:winsstr(win,s))
#define	mvwhline(win,y,x,c,num)	(wmove(win,y,x)==ERR?ERR:whline(win,c,num))
#define	mvwvline(win,y,x,c,num)	(wmove(win,y,x)==ERR?ERR:wvline(win,c,num))
#define	mvwaddchstr(win,y,x,str)\
	(wmove(win,y,x)==ERR?ERR:waddchstr(win,str))
#define	mvwaddchnstr(win,y,x,str,n)\
	(wmove(win,y,x)==ERR?ERR:waddchnstr(win,str,n))
#define	mvwinstr(win,y,x,str)	(wmove(win,y,x)==ERR?ERR:winstr(win,str))
#define	mvwinnstr(win,y,x,str,n)\
	(wmove(win,y,x)==ERR?ERR:winnstr(win,str,n))
#define	mvwinchstr(win,y,x,str)	(wmove(win,y,x)==ERR?ERR:winchstr(win,str))
#define	mvwinchnstr(win,y,x,str,n)\
	(wmove(win,y,x)==ERR?ERR:winchnstr(win,str,n))

#define	mvwaddnwstr(win,y,x,ws,n) (wmove(win,y,x)==ERR?ERR:waddnwstr(win,ws,n))
#define	mvwadd_wch(win,y,x,ch)	(wmove(win,y,x)==ERR?ERR:wadd_wch(win,ch))
#define	mvwadd_wchnstr(win,y,x,str,n)\
 (wmove(win,y,x)==ERR?ERR:wadd_wchnstr(win,str,n))
#define	mvwadd_wchstr(win,y,x,str)\
 (wmove(win,y,x)==ERR?ERR:wadd_wchstr(win,str))
#define	mvwaddwstr(win,y,x,ws)	(wmove(win,y,x)==ERR?ERR:waddwstr(win,ws))
#define	mvwgetn_wstr(win,y,x,ws,n) \
(wmove(win,y,x)==ERR?ERR:wgetn_wstr(win,ws,n))
#define	mvwget_wch(win,y,x,ws)	(wmove(win,y,x)==ERR?ERR:wget_wch(win,ws))
#define	mvwget_wstr(win,y,x,ws)	(wmove(win,y,x)==ERR?ERR:wget_wstr(win,ws))
#define	mvwinnwstr(win,y,x,ws,n) (wmove(win,y,x)==ERR?ERR:winnwstr(win,ws,n))
#define	mvwins_nwstr(win,y,x,ws,n)\
 (wmove(win,y,x)==ERR?ERR:wins_nwstr(win,ws,n))
#define	mvwin_wch(win,y,x,c)	(wmove(win,y,x)==ERR?ERR:win_wch(win,c))
#define	mvwins_wch(win,y,x,c)	(wmove(win,y,x)==ERR?ERR:wins_wch(win,c))
#define	mvwins_wstr(win,y,x,ws)	(wmove(win,y,x)==ERR?ERR:wins_wstr(win,ws))
#define	mvwin_wchnstr(win,y,x,str,n)\
 (wmove(win,y,x)==ERR?ERR:win_wchnstr(win,str,n))
#define	mvwin_wchstr(win,y,x,str) (wmove(win,y,x)==ERR?ERR:win_wchstr(win,str))
#define	mvwinwstr(win,y,x,ws)	(wmove(win,y,x)==ERR?ERR:winwstr(win,ws))

#define	refresh()		wrefresh(stdscr)
#define	scrl(n)			wscrl(stdscr,n)
#define	setscrreg(t,b)		wsetscrreg(stdscr, t, b)
#define	standend()		wstandend(stdscr)
#define	standout()		wstandout(stdscr)
#define	timeout(tm)		wtimeout(stdscr,tm)
#define	vline(c,num)		wvline(stdscr,c,num)
#define	wadd_wchstr(win,str)	wadd_wchnstr(win,str,-1)
#define	win_wchstr(win,str)	win_wchnstr(win,str,-1)
#define waddwstr(win,ws)	waddnwstr(win,ws,-1)
#define wins_wstr(win,ws)	wins_nwstr(win,ws,-1)


/* functions to define environment flags of a window */
#ifdef	CURS_PERFORMANCE
#define	wbkgdset(win,c)		(((win)->_attrs = (((win)->_attrs\
                                & ~((win)->_bkgd & A_ATTRIBUTES))\
                                | (c & A_ATTRIBUTES))), ((win)->_bkgd = (c)))
#define syncok(win,bf)		((win)->_parent?(win)->_sync=(bf):ERR)
#define	notimeout(win,bf)	(((win)->_notimeout = ((bf) ? TRUE : FALSE)),OK)
#define	clearok(win,bf)		(((win)->_clear = (bf)), OK)
#define	leaveok(win,bf)		(((win)->_leave = (bf)), OK)
#define	scrollok(win,bf)	(((win)->_scroll = ((bf) ? TRUE : FALSE)), OK)
#define	idcok(win,bf)		((win)->_use_idc = ((bf) ? TRUE : FALSE))
#define	nodelay(win,bf)		(((win)->_delay = (bf) ? 0 : -1), OK)
#define is_wintouched(win)	((win)->_flags & _WINCHANGED)
#define is_linetouched(win,line)	((((line) >= (win)->_maxy) || \
				     ((line) < 0)) ? ERR : \
				    (((win)->_firstch[(line)] == _INFINITY) ? \
								  FALSE : TRUE))

#define subwin(win,nl,nc,by,bx)\
	derwin((win),(nl),(nc),(by-win->_begy),(bx-win->_begx))
#define touchwin(win)		wtouchln((win),0,(win)->_maxy,TRUE)
#define redrawwin(win)		wredrawln((win),0,(win)->_maxy)
#define	winchstr(win,str) \
	winchnstr((win),str,((win)->_maxx - (win)->_curx))
#define	winstr(win,str)		winnstr((win),str,((win)->_maxx - (win)->_curx))
#define untouchwin(win)		wtouchln((win),0,((win)->_maxy),FALSE)
#define	winch(win)		((win)->_y[(win)->_cury][(win)->_curx])

#define wtimeout(win,tm)	((win)->_delay = (tm))
#define use_env(bf)		(_use_env = (bf))

#else	/* CURS_PERFORMANCE */

#if defined(__STDC__) || !defined(_NO_PROTO)

extern	void	wbkgdset(WINDOW *, chtype),
		idcok(WINDOW *, bool),
		wtimeout(WINDOW *, int), use_env(bool);

extern	int	syncok(WINDOW *, bool),
		notimeout(WINDOW *, bool),
		clearok(WINDOW *, bool),
		leaveok(WINDOW *, bool),
		scrollok(WINDOW *, bool),
		nodelay(WINDOW *, bool),
		touchwin(WINDOW *), redrawwin(WINDOW *),
		winchstr(WINDOW *, chtype *), winstr(WINDOW *, char *),
		untouchwin(WINDOW *);

extern  bool    is_linetouched(WINDOW *, int), is_wintouched(WINDOW *);

extern  chtype  winch(WINDOW *);

extern	WINDOW	*subwin(WINDOW *, int, int, int, int);

#else  /* __STDC__ */

extern	void	wbkgdset(), idcok(), wtimeout(), use_env();

extern	int	syncok(), notimeout(), clearok(), leaveok(),
		scrollok(), nodelay(), 
		touchwin(), redrawwin(), winchstr(), winstr(),
		untouchwin();

extern  bool    is_linetouched(), is_wintouched();

extern  chtype  winch();

extern	WINDOW	*subwin();

#endif /* __STDC__ */

#endif	/* CURS_PERFORMANCE */

#ifdef CURS_MACROS
#define overlay(src,dst)	_overlap((src),(dst),TRUE)
#define overwrite(src,dst)	_overlap((src),(dst),FALSE)
#define wdeleteln(win)		winsdelln((win),-1)
#define winsertln(win)		winsdelln((win),1)
#define wstandend(win)		wattrset((win),A_NORMAL)
#define wstandout(win)		wattron((win),A_STANDOUT)
#define beep()			_ring(TRUE)
#define flash()			_ring(FALSE)
#define scroll(win)		wscrl((win),1)
#define slk_init(f)		slk_start(((f == 0) ? 3 : 2),NULL)
#define	scr_init(file)		_scr_all(file,0)
#define	scr_restore(file)	_scr_all(file,1)
#define	scr_set(file)		_scr_all(file,2)
#define subpad(win,nl,nc,by,bx)	derwin((win),(nl),(nc),(by),(bx))
#define box(win,v,h)		wborder((win),(v),(v),(h),(h),0,0,0,0)
#define newterm(type,fout,fin)	newscreen((type),0,0,0,(fout),(fin))
#define touchline(win,y,n)	wtouchln((win),(y),(n),TRUE)

#define waddstr(win,str)	waddnstr((win),(str),-1)
#define werase(win)		(wmove((win),0,0), wclrtobot(win))
#define wclear(win)		(clearok((win),TRUE), werase(win))
#define intrflush(win,flag)	_setqiflush(flag)
#define meta(win,flag)		_meta(flag)

#define setterm(name)		setupterm((name),1,(char*)NULL)
#define gettmode()		(OK)
#define halfdelay(tens)		ttimeout((tens)*100)

#define echo()			_setecho(TRUE)
#define noecho()		_setecho(FALSE)
#define nl()			_setnonl(FALSE)
#define nonl()			_setnonl(TRUE)

#else /* CURS_MACROS */

#if defined(__STDC__) || !defined(_NO_PROTO)

extern	int	overlay(const WINDOW *, WINDOW *),                                               overwrite(const WINDOW *, WINDOW *),
		wdeleteln(WINDOW *), winsertln(WINDOW *),
		wstandend(WINDOW *), wstandout(WINDOW *),
		beep(void), flash(void), scroll(WINDOW *), slk_init(int),
		scr_init(const char *), scr_restore(const char *),                                 scr_set(const char *),
		box(WINDOW *, chtype, chtype), touchline(WINDOW *, int, int),
		waddstr(WINDOW *, const char *), werase(WINDOW *),
		wclear(WINDOW *), intrflush(WINDOW *, bool),
		meta(WINDOW *, bool), setterm(char *), gettmode(void),
		halfdelay(int), echo(void), noecho(void), nl(void), nonl(void);

extern	WINDOW *subpad(WINDOW *, int, int, int, int);

extern  SCREEN  *newterm(char *, FILE *, FILE *);

#else  /* __STDC__ */

extern	int	overlay(), overwrite(), wdeleteln(), winsertln(),
		wstandend(), wstandout(), beep(), flash(),
		scroll(), slk_init(), scr_init(), scr_restore(), scr_set(),
		box(), touchline(), waddstr(), werase(),
		wclear(), intrflush(), meta(), setterm(), gettmode(),
		halfdelay(), echo(), noecho(), nl(), nonl();

extern	WINDOW *subpad();

extern  SCREEN  *newterm();

#endif /* __STDC__ */
#endif /* CURS_MACROS */

#define garbagedlines		wredrawln
#define garbagedwin		redrawwin

#define crmode			cbreak
#define nocrmode		nocbreak
#define saveterm		def_prog_mode
#define fixterm			reset_prog_mode
#define resetterm		reset_shell_mode

#define	waddchstr(win,str)	waddchnstr((win),(str),-1)
#define winsstr(win,str)	winsnstr((win),(str),-1)

/* iocontrol functions */
#define qiflush()		_setqiflush(TRUE)
#define noqiflush()		_setqiflush(FALSE)

#define set_term		setcurscreen

#endif	/* NOMACROS || lint */

/*
 * Standard alternate character set.  The current ACS world is evolving,
 * so we support only a widely available subset: the line drawing characters
 * from the VT100, plus a few from the Teletype 5410v1.  Eventually there
 * may be support of more sophisticated ACS line drawing, such as that
 * in the Teletype 5410, the HP line drawing set, and the like.  There may
 * be support for some non line oriented characters as well.
 *
 * Line drawing ACS names are of the form ACS_trbl, where t is the top, r
 * is the right, b is the bottom, and l is the left.  t, r, b, and l might
 * be B (blank), S (single), D (double), or T (thick).  The subset defined
 * here only uses B and S.
 */

#define _WACS_TO_ACS(x) \
	((chtype)((((x)->a)&A_ATTRIBUTES)|(((x)->c)&A_CHARTEXT)))

#define WACS_BSSB	(&(wacs_map['l']))
#define WACS_SSBB	(&(wacs_map['m']))
#define WACS_BBSS	(&(wacs_map['k']))
#define WACS_SBBS	(&(wacs_map['j']))
#define WACS_SBSS	(&(wacs_map['u']))
#define WACS_SSSB	(&(wacs_map['t']))
#define WACS_SSBS	(&(wacs_map['v']))
#define WACS_BSSS	(&(wacs_map['w']))
#define WACS_BSBS	(&(wacs_map['q']))
#define WACS_SBSB	(&(wacs_map['x']))
#define WACS_SSSS	(&(wacs_map['n']))

#define ACS_BSSB	(_WACS_TO_ACS(WACS_BSSB))
#define ACS_SSBB	(_WACS_TO_ACS(WACS_SSBB))
#define ACS_BBSS	(_WACS_TO_ACS(WACS_BBSS))
#define ACS_SBBS	(_WACS_TO_ACS(WACS_SBBS))
#define ACS_SBSS	(_WACS_TO_ACS(WACS_SBSS))
#define ACS_SSSB	(_WACS_TO_ACS(WACS_SSSB))
#define ACS_SSBS	(_WACS_TO_ACS(WACS_SSBS))
#define ACS_BSSS	(_WACS_TO_ACS(WACS_BSSS))
#define ACS_BSBS	(_WACS_TO_ACS(WACS_BSBS))
#define ACS_SBSB	(_WACS_TO_ACS(WACS_SBSB))
#define ACS_SSSS	(_WACS_TO_ACS(WACS_SSSS))

/*
 * Human readable names for the most commonly used characters.
 * "Upper", "right", etc. are chosen to be consistent with the vt100 manual.
 */

#define WACS_ULCORNER	WACS_BSSB
#define WACS_LLCORNER	WACS_SSBB
#define WACS_URCORNER	WACS_BBSS
#define WACS_LRCORNER	WACS_SBBS
#define WACS_RTEE	WACS_SBSS
#define WACS_LTEE	WACS_SSSB
#define WACS_BTEE	WACS_SSBS
#define WACS_TTEE	WACS_BSSS
#define WACS_HLINE	WACS_BSBS
#define WACS_VLINE	WACS_SBSB
#define WACS_PLUS	WACS_SSSS

#define ACS_ULCORNER	ACS_BSSB
#define ACS_LLCORNER	ACS_SSBB
#define ACS_URCORNER	ACS_BBSS
#define ACS_LRCORNER	ACS_SBBS
#define ACS_RTEE	ACS_SBSS
#define ACS_LTEE	ACS_SSSB
#define ACS_BTEE	ACS_SSBS
#define ACS_TTEE	ACS_BSSS
#define ACS_HLINE	ACS_BSBS
#define ACS_VLINE	ACS_SBSB
#define ACS_PLUS	ACS_SSSS

#define WACS_S1		(&(wacs_map['o'])) /* scan line 1 */
#define WACS_S9 	(&(wacs_map['s'])) /* scan line 9 */
#define WACS_DIAMOND	(&(wacs_map['`'])) /* diamond */
#define WACS_CKBOARD	(&(wacs_map['a'])) /* checker board */
#define WACS_DEGREE	(&(wacs_map['f'])) /* degree symbol */
#define WACS_PLMINUS	(&(wacs_map['g'])) /* plus/minus */
#define WACS_BULLET	(&(wacs_map['~'])) /* bullet */

#define ACS_S1 		(_WACS_TO_ACS(WACS_S1))
#define ACS_S9		(_WACS_TO_ACS(WACS_S9))
#define ACS_DIAMOND	(_WACS_TO_ACS(WACS_DIAMOND))
#define ACS_CKBOARD	(_WACS_TO_ACS(WACS_CKBOARD))
#define ACS_DEGREE	(_WACS_TO_ACS(WACS_DEGREE))
#define ACS_PLMINUS	(_WACS_TO_ACS(WACS_PLMINUS))
#define ACS_BULLET	(_WACS_TO_ACS(WACS_BULLET))

	/* Teletype 5410v1 symbols */
#define WACS_LARROW	(&(wacs_map[','])) /* arrow left */
#define WACS_RARROW	(&(wacs_map['+'])) /* arrow right */
#define WACS_DARROW	(&(wacs_map['.'])) /* arrow down */
#define WACS_UARROW	(&(wacs_map['-'])) /* arrow up */
#define WACS_BOARD	(&(wacs_map['h'])) /* board of squares */
#define WACS_LANTERN	(&(wacs_map['i'])) /* lantern symbol */
#define WACS_BLOCK	(&(wacs_map['0'])) /* solid square block */

#define ACS_LARROW	(_WACS_TO_ACS(WACS_LARROW))
#define ACS_RARROW	(_WACS_TO_ACS(WACS_RARROW))
#define ACS_DARROW	(_WACS_TO_ACS(WACS_DARROW))
#define ACS_UARROW	(_WACS_TO_ACS(WACS_UARROW))
#define ACS_BOARD	(_WACS_TO_ACS(WACS_BOARD))
#define ACS_LANTERN	(_WACS_TO_ACS(WACS_LANTERN))
#define ACS_BLOCK	(_WACS_TO_ACS(WACS_BLOCK))

/* Funny "characters" enabled for various special function keys for input */
/* This list is created from caps and curses.ed. Do not edit it! */
#define KEY_CODE_YES	03477		/* A key was returned */
#define KEY_MIN		03501		/* Minimum curses key */
#define KEY_BREAK	03501		/* break key (unreliable) */
#define KEY_DOWN	03502		/* Sent by terminal down arrow key */
#define KEY_UP		03503		/* Sent by terminal up arrow key */
#define KEY_LEFT	03504		/* Sent by terminal left arrow key */
#define KEY_RIGHT	03505		/* Sent by terminal right arrow key */
#define KEY_HOME	03506		/* Sent by home key. */
#define KEY_BACKSPACE	03507		/* Sent by backspace key */
#define KEY_F0		03510		/* function key f0. */
#define KEY_F(n)	(KEY_F0+(n))	/* Space for 64 function keys is ed. */
#define KEY_DL		03610		/* Sent by delete line key. */
#define KEY_IL		03611		/* Sent by insert line. */
#define KEY_DC		03612		/* Sent by delete character key. */
#define KEY_IC		03613		/* Sent by ins char/enter ins mode key. */
#define KEY_EIC		03614		/* Sent by rmir or smir in insert mode. */
#define KEY_CLEAR	03615		/* Sent by clear screen or erase key. */
#define KEY_EOS		03616		/* Sent by clear-to-end-of-screen key. */
#define KEY_EOL		03617		/* Sent by clear-to-end-of-line key. */
#define KEY_SF		03620		/* Sent by scroll-forward/down key */
#define KEY_SR		03621		/* Sent by scroll-backward/up key */
#define KEY_NPAGE	03622		/* Sent by next-page key */
#define KEY_PPAGE	03623		/* Sent by previous-page key */
#define KEY_STAB	03624		/* Sent by set-tab key */
#define KEY_CTAB	03625		/* Sent by clear-tab key */
#define KEY_CATAB	03626		/* Sent by clear-all-tabs key. */
#define KEY_ENTER	03627		/* Enter/send (unreliable) */
#define KEY_SRESET	03630		/* soft (partial) reset (unreliable) */
#define KEY_RESET	03631		/* reset or hard reset (unreliable) */
#define KEY_PRINT	03632		/* print or copy */
#define KEY_LL		03633		/* Sent by home-down key */
					/* The keypad is arranged like this: */
					/*    a1    up    a3   */
					/*   left   b2  right  */
					/*    c1   down   c3   */
#define KEY_A1		03634		/* Upper left of keypad */
#define KEY_A3		03635		/* Upper right of keypad */
#define KEY_B2		03636		/* Center of keypad */
#define KEY_C1		03637		/* Lower left of keypad */
#define KEY_C3		03640		/* Lower right of keypad */
#define KEY_BTAB	03641		/* Back tab key */
#define KEY_BEG		03642		/* beg(inning) key */
#define KEY_CANCEL	03643		/* cancel key */
#define KEY_CLOSE	03644		/* close key */
#define KEY_COMMAND	03645		/* cmd (command) key */
#define KEY_COPY	03646		/* copy key */
#define KEY_CREATE	03647		/* create key */
#define KEY_END		03650		/* end key */
#define KEY_EXIT	03651		/* exit key */
#define KEY_FIND	03652		/* find key */
#define KEY_HELP	03653		/* help key */
#define KEY_MARK	03654		/* mark key */
#define KEY_MESSAGE	03655		/* message key */
#define KEY_MOVE	03656		/* move key */
#define KEY_NEXT	03657		/* next object key */
#define KEY_OPEN	03660		/* open key */
#define KEY_OPTIONS	03661		/* options key */
#define KEY_PREVIOUS	03662		/* previous object key */
#define KEY_REDO	03663		/* redo key */
#define KEY_REFERENCE	03664		/* ref(erence) key */
#define KEY_REFRESH	03665		/* refresh key */
#define KEY_REPLACE	03666		/* replace key */
#define KEY_RESTART	03667		/* restart key */
#define KEY_RESUME	03670		/* resume key */
#define KEY_SAVE	03671		/* save key */
#define KEY_SBEG	03672		/* shifted beginning key */
#define KEY_SCANCEL	03673		/* shifted cancel key */
#define KEY_SCOMMAND	03674		/* shifted command key */
#define KEY_SCOPY	03675		/* shifted copy key */
#define KEY_SCREATE	03676		/* shifted create key */
#define KEY_SDC		03677		/* shifted delete char key */
#define KEY_SDL		03700		/* shifted delete line key */
#define KEY_SELECT	03701		/* select key */
#define KEY_SEND	03702		/* shifted end key */
#define KEY_SEOL	03703		/* shifted clear line key */
#define KEY_SEXIT	03704		/* shifted exit key */
#define KEY_SFIND	03705		/* shifted find key */
#define KEY_SHELP	03706		/* shifted help key */
#define KEY_SHOME	03707		/* shifted home key */
#define KEY_SIC		03710		/* shifted input key */
#define KEY_SLEFT	03711		/* shifted left arrow key */
#define KEY_SMESSAGE	03712		/* shifted message key */
#define KEY_SMOVE	03713		/* shifted move key */
#define KEY_SNEXT	03714		/* shifted next key */
#define KEY_SOPTIONS	03715		/* shifted options key */
#define KEY_SPREVIOUS	03716		/* shifted prev key */
#define KEY_SPRINT	03717		/* shifted print key */
#define KEY_SREDO	03720		/* shifted redo key */
#define KEY_SREPLACE	03721		/* shifted replace key */
#define KEY_SRIGHT	03722		/* shifted right arrow */
#define KEY_SRSUME	03723		/* shifted resume key */
#define KEY_SSAVE	03724		/* shifted save key */
#define KEY_SSUSPEND	03725		/* shifted suspend key */
#define KEY_SUNDO	03726		/* shifted undo key */
#define KEY_SUSPEND	03727		/* suspend key */
#define KEY_UNDO	03730		/* undo key */
#define KEY_ACTION	03731		/* Sent by the action key. */
#define KEY_MOUSE	03732		/* Mouse event has occured */
#define KEY_MAX		04077		/* Maximum curses key */

/*
	The definition for 'reg' is not standard, and is provided for
	compatibility reasons. User's are discouraged from using this.
*/
#define	reg	register

/* Various video attributes */
#define A_STANDOUT	000000200000
#define	_STANDOUT	A_STANDOUT    /* for compatability with old curses */
#define A_UNDERLINE	000000400000
#define A_REVERSE	000001000000
#define A_BLINK		000002000000
#define A_DIM		000004000000
#define A_BOLD		000010000000
/* The next two are subject to change so don't depend on them */
#define A_INVIS		000020000000
#define A_PROTECT	000040000000
#define A_ALTCHARSET	000100000000

/* The next 7 attributes overlap the same bits used above, but
 *  these have the high bit set to distinguish them.  Note that
 *  now, the only bits left for future use are
 *  020040000000, and 020100000000 (A_RESERVED1 & A_RESERVED2).
 *  #define A_EXT_ATTRS	020177600000
 */


#define WA_HORIZONTAL  	020000200000
#define WA_LEFT		 020000400000
#define WA_LOW		 020001000000
#define WA_RIGHT	 020002000000
#define WA_TOP		 020004000000
#define WA_VERTICAL	 020010000000
#define WA_STANDOUT      000000200000
#define WA_UNDERLINE     000000400000
#define WA_REVERSE       000001000000
#define WA_BLINK         000002000000
#define WA_DIM           000004000000
#define WA_BOLD          000010000000
#define WA_INVIS         000020000000
#define WA_PROTECT       000040000000
#define WA_ALTCHARSET    000100000000

#ifdef ALL_SOURCE
#define A_WORDBREAK	020020000000
#define A_RESERVED1	020040000000
#define A_RESERVED2	020100000000
#else
#define _A_WORDBREAK	020020000000
#define _A_RESERVED1	020040000000
#define _A_RESERVED2	020100000000
#endif /* ALL_SOURCE */

/* Composition of a 32-bit chtype:
 * Bits		#bits	Description
 * 00-15	16	Character
 * 16-24	09	Display Attributes
 * 25-30	06	Color Attributes (3-Background, 3-Forground)
 * 31           01      reserved
 */
#define A_NORMAL	000000000000
#define A_ATTRIBUTES	037777600000	/* 0xFFFF0000 */
#define A_CHARTEXT	000000177777	/* 0x0000FFFF */
#define A_COLOR		017600000000   /* 0x7E00000  */

#define COLOR_PAIR(n)	((n) << 25)
#define PAIR_NUMBER(n)	(((n) & A_COLOR) >> 25)

/* definition of 8 basic color	*/
#define COLOR_BLACK	0
#define COLOR_RED	1
#define COLOR_GREEN	2
#define COLOR_YELLOW	3
#define COLOR_BLUE	4
#define COLOR_MAGENTA	5
#define COLOR_CYAN	6
#define COLOR_WHITE	7

/* mouse related macros: don't change these definitions or bit-masks. */
/* they are interdependent (used by _map_button() in tgetch()	      */
#define BUTTON_RELEASED            0
#define BUTTON_PRESSED             1
#define BUTTON_CLICKED             2
#define BUTTON_DOUBLE_CLICKED      3
#define BUTTON_TRIPLE_CLICKED      4

#define MOUSE_X_POS                (Mouse_status.x)
#define MOUSE_Y_POS                (Mouse_status.y)
#define A_BUTTON_CHANGED           (Mouse_status.changes & 7)
#define MOUSE_MOVED                (Mouse_status.changes & 8)
#define MOUSE_POS_REPORT	   (Mouse_status.changes & 16)
#define BUTTON_CHANGED(x)          (Mouse_status.changes & (1 << ((x) - 1)))
#define BUTTON_STATUS(x)           (Mouse_status.button[(x)-1])

/* definition of mouse bit-masks	*/
#define	BUTTON1_RELEASED	000000000001
#define	BUTTON1_PRESSED		000000000002
#define	BUTTON1_CLICKED		000000000004
#define	BUTTON1_DOUBLE_CLICKED	000000000010
#define	BUTTON1_TRIPLE_CLICKED	000000000020
#define	BUTTON2_RELEASED	000000000040
#define	BUTTON2_PRESSED		000000000100
#define	BUTTON2_CLICKED		000000000200
#define	BUTTON2_DOUBLE_CLICKED	000000000400
#define	BUTTON2_TRIPLE_CLICKED	000000001000
#define	BUTTON3_RELEASED	000000002000
#define	BUTTON3_PRESSED		000000004000
#define	BUTTON3_CLICKED		000000010000
#define	BUTTON3_DOUBLE_CLICKED	000000020000
#define	BUTTON3_TRIPLE_CLICKED	000000040000
#define ALL_MOUSE_EVENTS	000000077777
#define REPORT_MOUSE_POSITION	000000100000

#endif /* CURSES_H */

#else /* _AIX32_CURSES */

/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/ccs/lib/libcurses/compat/curses3.h 1.4              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1988          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)42    1.4  src/bos/usr/ccs/lib/libcurses/compat/curses3.h, libcurses, bos530 7/6/01 06:05:48 */
#ifndef _H_CURSES
#define _H_CURSES

/*
 *   COMPONENT_NAME: LIBCURSES
 *
 *   FUNCTIONS: curses3.h
 *
 *   ORIGINS: 3,10,27
 *
 *   This module contains                  code. -- (IBM
 *   Confidential Restricted when combined with the aggregated
 *   modules for this product)
 *   OBJECT CODE ONLY SOURCE MATERIALS
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1985,1999
 *   All Rights Reserved
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */



#ifndef WINDOW

#ifndef __ia64
# ifndef _H_NLCHAR
# include <sys/NLchar.h>
# endif
#endif

# ifndef 	NONSTANDARD
#  include  <stdio.h>
  /*
   * This is used to distinguish between USG and V7 systems.
   * Assume that L_ctermid is only defined in stdio.h in USG
   * systems, but not in V7 or Berkeley UNIX.
   */
#  ifdef L_ctermid
#  define USG
#  endif
#  include  <unctrl.h>
#  ifdef USG
#   include <termio.h>
   typedef struct termio SGTTY;
#  else
#   include <sgtty.h>
   typedef struct sgttyb SGTTY;
#  endif
# else          /* NONSTANDARD */
/*
 * NONSTANDARD is intended for a standalone program (no UNIX)
 * that manages screens.  The specific program is Alan Hewett's
 * ITC, which runs standalone on an 11/23 (at least for now).
 * It is unclear whether this code needs to be supported anymore.
 */
# define NULL ((void *)0)
# endif		/* NONSTANDARD */

/*
 * chtype is the type used to store a character together with attributes.
 * It can be set to "char" to save space, or "long" to get more attributes.
 */
# ifdef	CHTYPE
	typedef	CHTYPE chtype;
# else
	typedef unsigned long chtype;
# endif /* CHTYPE */

# define        TRUE    1
# define        FALSE   0

# define        ERR     (-1)
# define        OK      0

# define	_SUBWIN		01
# define	_ENDLINE	02
# define	_FULLWIN	04
# define	_SCROLLWIN	010
# define	_FLUSH		020
# define	_ISPAD		040
# define	_STANDOUT	0x80000000
# define        _NOCHANGE       (-1)
#if !defined(__cplusplus) || (defined(__IBMCPP__) &&(__IBMCPP__<400))
typedef char bool ; /* bool type required by X/open */
#endif
struct _win_st {
	short	_cury, _curx;
	short	_maxy, _maxx;
	short	_begy, _begx;
	short   _flags;
	chtype  _attrs;
	char    _clear;
	char    _leave;
	char    _scroll;
	char    _use_idl;
	char    _use_keypad;    /* 0=no, 1=yes, 2=yes/timeout */
	char    _use_meta;      /* T=use the meta key */
	char    _nodelay;       /* T=don't wait for tty input */
	chtype	**_y;
	short	*_firstch;
	short	*_lastch;
	short	_tmarg,_bmarg;
};

extern int	LINES, COLS;

typedef struct _win_st	WINDOW;
extern WINDOW	*stdscr, *curscr;

extern char	*Def_term, ttytype[];

typedef struct screen	SCREEN;

# ifndef NOMACROS 
#  ifndef MINICURSES
/*
 * psuedo functions for standard screen
 */
# define	addch(ch)	waddch(stdscr, ch)
# define	getch()		wgetch(stdscr)
# define	NLgetch()	NLwgetch(stdscr)
# define	addstr(str)	waddstr(stdscr, str)
# define	getstr(str)	wgetstr(stdscr, str)
# define	move(y, x)	wmove(stdscr, y, x)
# define	clear()		wclear(stdscr)
# define	erase()		werase(stdscr)
# define	clrtobot()	wclrtobot(stdscr)
# define	clrtoeol()	wclrtoeol(stdscr)
# define	insertln()	winsertln(stdscr)
# define	deleteln()	wdeleteln(stdscr)
# define	refresh()	wrefresh(stdscr)
# define	inch()		winch(stdscr)
# define	insch(c)	winsch(stdscr,c)
# define	delch()		wdelch(stdscr)
# define	standout()	wstandout(stdscr)
# define	standend()	wstandend(stdscr)
# define	attron(at)	wattron(stdscr,at)
# define	attroff(at)	wattroff(stdscr,at)
# define	attrset(at)	wattrset(stdscr,at)

# define	setscrreg(t,b)	wsetscrreg(stdscr, t, b)
# define	wsetscrreg(win,t,b)	(win->_tmarg=(t),win->_bmarg=(b))

/*
 * mv functions
 */
#define	mvwaddch(win,y,x,ch)	(wmove(win,y,x)==ERR?ERR:waddch(win,ch))
#define	mvwgetch(win,y,x)	(wmove(win,y,x)==ERR?ERR:wgetch(win))
#define	mvwaddstr(win,y,x,str)	(wmove(win,y,x)==ERR?ERR:waddstr(win,str))
#define	mvwgetstr(win,y,x,str)	(wmove(win,y,x)==ERR?ERR:wgetstr(win,str))
#define	mvwinch(win,y,x)	(wmove(win,y,x)==ERR?ERR:winch(win))
#define	mvwdelch(win,y,x)	(wmove(win,y,x)==ERR?ERR:wdelch(win))
#define	mvwinsch(win,y,x,c)	(wmove(win,y,x)==ERR?ERR:winsch(win,c))
#define	mvaddch(y,x,ch)		mvwaddch(stdscr,y,x,ch)
#define	mvgetch(y,x)		mvwgetch(stdscr,y,x)
#define	mvaddstr(y,x,str)	mvwaddstr(stdscr,y,x,str)
#define	mvgetstr(y,x,str)	mvwgetstr(stdscr,y,x,str)
#define	mvinch(y,x)		mvwinch(stdscr,y,x)
#define	mvdelch(y,x)		mvwdelch(stdscr,y,x)
#define	mvinsch(y,x,c)		mvwinsch(stdscr,y,x,c)

#  else /* MINICURSES */

# define	addch(ch)		m_addch(ch)
# define	addstr(str)		m_addstr(str)
# define	move(y, x)		m_move(y, x)
# define	clear()			m_clear()
# define	erase()			m_erase()
# define	refresh()		m_refresh()
# define	standout()		wstandout(stdscr)
# define	standend()		wstandend(stdscr)
# define	attron(at)		wattron(stdscr,at)
# define	attroff(at)		wattroff(stdscr,at)
# define	attrset(at)		wattrset(stdscr,at)
# define	mvaddch(y,x,ch)		move(y, x), addch(ch)
# define	mvaddstr(y,x,str)	move(y, x), addstr(str)
# define	initscr			m_initscr
# define	newterm			m_newterm

/*
 * These functions don't exist in minicurses, so we define them
 * to nonexistent functions to help the user catch the error.
 */
#define	getch		m_getch
#define	getstr		m_getstr
#define	clrtobot	m_clrtobot
#define	clrtoeol	m_clrtoeol
#define	insertln	m_insertln
#define	deleteln	m_deleteln
#define	inch		m_inch
#define	insch		m_insch
#define	delch		m_delch
/* mv functions that aren't valid */
#define	mvwaddch	m_mvwaddch
#define	mvwgetch	m_mvwgetch
#define	mvwaddstr	m_mvaddstr
#define	mvwgetstr	m_mvwgetstr
#define	mvwinch		m_mvwinch
#define	mvwdelch	m_mvwdelch
#define	mvwinsch	m_mvwinsch
#define	mvgetch		m_mvwgetch
#define	mvgetstr	m_mvwgetstr
#define	mvinch		m_mvwinch
#define	mvdelch		m_mvwdelch
#define	mvinsch		m_mvwinsch
/* Real functions that aren't valid */
#define box		m_box
#define delwin		m_delwin
#define longname	m_longname
#define makenew		m_makenew
#define mvprintw	m_mvprintw
#define mvscanw		m_mvscanw
#define mvwin		m_mvwin
#define mvwprintw	m_mvwprintw
#define mvwscanw	m_mvwscanw
#define newwin		m_newwin
#define _outchar        m_outchar
#define overlay		m_overlay
#define overwrite	m_overwrite
#define printw		m_printw
#define putp		m_putp
#define scanw		m_scanw
#define scroll		m_scroll
#define subwin		m_subwin
#define touchwin	m_touchwin
#define _tscroll        m_tscroll
#define _tstp		m_tstp
#define vidattr		m_vidattr
#define waddch		m_waddch
#define waddstr		m_waddstr
#define wclear		m_wclear
#define wclrtobot	m_wclrtobot
#define wclrtoeol	m_wclrtoeol
#define wdelch		m_wdelch
#define wdeleteln	m_wdeleteln
#define werase		m_werase
#define wgetch		m_wgetch
#define wgetstr		m_wgetstr
#define winsch		m_winsch
#define winsertln	m_winsertln
#define wmove		m_wmove
#define wprintw		m_wprintw
#define wrefresh	m_wrefresh
#define wscanw		m_wscanw
#define setscrreg	m_setscrreg
#define wsetscrreg	m_wsetscrreg

#  endif /* MINICURSES */

/*
 * psuedo functions
 */

#define	getyx(win,y,x)	 y = win->_cury, x = win->_curx
#define	winch(win)	 (win->_y[win->_cury][win->_curx])
#define flushok(win,bf)  (bf ? (win->_flags|=_FLUSH):(win->_flags&=~_FLUSH))

WINDOW	*initscr(), *newwin(), *subwin(), *newpad();
char	*longname();
char	erasechar(), killchar();
int	wgetch();	/* because it can return KEY_*, for instance. */
SCREEN	*newterm();

/* Various video attributes */
/*
   We start from the left and attributes bits from left to right to permit
   larger collating sequences.  Add attributes in this fashion if necessary.
*/

#define A_STANDOUT	0x80000000
#define A_UNDERLINE	0x40000000
#define A_REVERSE	0x20000000
#define A_BLINK		0x10000000
#define A_DIM		0x08000000
#define A_BOLD		0x04000000

#define A_INVIS		0x02000000
#define A_PROTECT	0x01000000
#define A_ALTCHARSET	0x00800000

#define A_NORMAL	0x00000000
#define A_ATTRIBUTES	0xff800000
#define A_CHARTEXT	0x007fffff

/* Funny "characters" enabled for various special function keys for input */
/*
 * Under NLS, we start their collation around 3500 octal (1856 decimal)
 * to permit room for NLS characters with large values
*/
#define KEY_BREAK	03501		/* break key (unreliable) */
#define KEY_DOWN	03502		/* The four arrow keys ... */
#define KEY_UP		03503
#define KEY_LEFT	03504
#define KEY_RIGHT	03505		/* ... */
#define KEY_HOME	03506		/* Home key (upward+left arrow) */
#define KEY_BACKSPACE	03507		/* backspace (unreliable) */
#define KEY_F0		03510		/* Function keys.  Space for 64 */
#define KEY_F(n)	(KEY_F0+(n))	/* keys is reserved. */
#define KEY_DL		03610		/* Delete line */
#define KEY_IL		03611		/* Insert line */
#define KEY_DC		03612		/* Delete character */
#define KEY_IC		03613		/* Insert char or enter insert mode */
#define KEY_EIC		03614		/* Exit insert char mode */
#define KEY_CLEAR	03615		/* Clear screen */
#define KEY_EOS		03616		/* Clear to end of screen */
#define KEY_EOL		03617		/* Clear to end of line */
#define KEY_SF		03620		/* Scroll 1 line forward */
#define KEY_SR          03621           /* Scroll 1 line backwards (reverse)*/
#define KEY_NPAGE	03622		/* Next page */
#define KEY_PPAGE	03623		/* Previous page */
#define KEY_STAB	03624		/* Set tab */
#define KEY_CTAB	03625		/* Clear tab */
#define KEY_CATAB	03626		/* Clear all tabs */
#define KEY_ENTER	03627		/* Enter or send (unreliable) */
#define KEY_SRESET      03630           /* soft (partial) reset (unreliable)*/
#define KEY_RESET	03631		/* reset or hard reset (unreliable) */
#define KEY_PRINT	03632		/* print or copy */
#define KEY_LL		03633		/* home down or bottom (lower left) */
					/* The keypad is arranged like this:*/
					/*    a1    up    a3   */
					/*   left   b2  right  */
					/*    c1   down   c3   */
#define KEY_A1		03634		/* upper left of keypad */
#define KEY_A3		03635		/* upper right of keypad */
#define KEY_B2		03636		/* center of keypad */
#define KEY_C1		03637		/* lower left of keypad */
#define KEY_C3		03640		/* lower right of keypad */
#define KEY_ACTION      03641           /* Action key            */
#define KEY_END         03642           /* End key               */
#define KEY_BTAB        03643           /* Back-tab key          */

SCREEN * set_term (SCREEN * n) ; /* prototype for set_term */

# endif /* NOMACROS */
#endif /* WINDOW */

#endif /* _H_CURSES */


#endif /* _AIX32_CURSES */
