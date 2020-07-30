#ident	"@(#)bdio.h	6.1 of 02/29/96 SMI"
/*
 * Copyright (c) 1988 by Sun Microsystems, Inc.
 */
#ifndef	_SYS_BDIO_H
#define	_SYS_BDIO_H

#include <sys/ioccom.h>

/*
 * For the dialbox:
 */
#define DIAL_DEVID	0x7B
#define NDIALS		8

/* DELTA event for a particular dial */
#define DIAL_DELTA(dialnum)     (vuid_first(DIAL_DEVID) + (dialnum))

/* Macro to extract dial number from event */
#define DIAL_NUMBER(event_code)	(event_code & 0xFF)

#define	event_is_dial(event)	\
	(vuid_in_range(DIAL_DEVID, event->ie_code))

/* Dial deltas are in 64ths of degrees */
#define DIAL_UNITS_PER_DEGREE 64
#define DIAL_UNITS_PER_CYCLE (360 * DIAL_UNITS_PER_DEGREE)

/* Convert dial deltas to degrees */
#define DIAL_TO_DEGREES(n)	((float)(n) / DIAL_UNITS_PER_DEGREE)

/* converts dial units (64th of degrees) to radians */
#define DIAL_TO_RADIANS(n) \
	(((float)(n) * 2.0 * M_PI) / (float) DIAL_UNITS_PER_CYCLE)

/*
 * For the buttonbox:
 */
#define BUTTON_DEVID	0x7A
#define NBUTTON		32

/* Name for the ioctl to turn the leds on the button box on */
#define BDIOC		('B'<<8)
#define BDIOBUTLITE	(BDIOC|1)

/*Macros for the button box */
#define	event_is_32_button(event) \
		(vuid_in_range(BUTTON_DEVID, event->ie_code))

/*These are the bit masks to turn the leds and buttons on/off */
#define BUTTON_MAP(butnum)  (butnum)
#define LED_MAP(butnum)	    (1<< (butnum - 1))

/*
 * To work around bug win_event.h:
 */
#undef	VUIOC
#undef	VUIDSFORMAT
#undef	VUIDGFORMAT
#define VUIOC		('v'<<8)
#define VUIDSFORMAT	(VUIOC|1)
#define VUIDGFORMAT	(VUIOC|2)

#endif	_SYS_BDIO_H
