/*
 * This is the extension of wctype.h which defines international
 * classification functions for multi byte character.
 *
 * If you want to use multi byte character classification 
 * for your language,additional functions can be defined here.
 *
 * This file is not automatically included by <wctype.h> in ALE5.0.
 */

/*	@(#)xctype.h	1.27 90/05/23 SMI; ALE */
/*	from AT&T JAE 2.1	*/

#ifndef _XCTYPE_H
#define _XCTYPE_H

#if defined(__cplusplus)
extern "C" {
#endif

/* Beginning of Korean Language Environment (KLE) */
#define isksc(c)	((((c) & WCHAR_CSMASK) == WCHAR_CS1 ) ?	\
					_iswctype(c, _E9) : 0)
			/* classification 1-94 */

			/* classification 16-40 */
#define iskhangul(c)	isphonogram(c) 

                        /* classification 42-93 */
#define iskhanja(c)   	isideogram(c)

/* KSC5601 code classification */

#define iskparen(c)	_iswctype((c),_E10)	
#define iskroman(c)	_iswctype((c),_E11)
#define iskletter(c)	_iswctype((c),_E12)	
#define iskgreek(c) 	_iswctype((c),_E13)
#define iskromannum(c) 	_iswctype((c),_E14)
#define iskline(c)	_iswctype((c),_E15)
#define iskunit(c) 	_iswctype((c),_E16)
#define isksymbol(c) 	_iswctype((c),_E17)
#define	iskhira(c)	_iswctype((c),_E18)
#define iskkata(c)	_iswctype((c),_E19)
#define iskrussian(c)   _iswctype((c),_E20)
#define iskuser(c) 	_iswctype((c),_E21)
#define isksci(c)	_iswctype((c),_E22)
#define iskgen(c)	_iswctype((c),_E23)
#define isklatin(c)	_iswctype((c),_E24)

#ifndef K_ILLEGAL
#define K_ILLEGAL	0xffff
#endif

#if defined(FUNCPROTO) || __STDC__ || defined(__cplusplus) || defined(c_plusplus)
extern unsigned short comptopack(unsigned short);
extern unsigned short packtocomp(unsigned short);
extern unsigned short wansungtojohap(unsigned short);
extern unsigned short johaptowansung(unsigned short);
#else
extern unsigned short comptopack();
extern unsigned short packtocomp();
extern unsigned short wansungtojohap();
extern unsigned short johaptowansung();
#endif

/* end of KLE */

#if defined(__cplusplus)
}
#endif

#endif /*!_XCTYPE_H*/
