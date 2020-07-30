/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/usr/ccs/lib/libdecNumber/decPacked.h 1.4                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2006,2008              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)01     1.4  src/bos/usr/ccs/lib/libdecNumber/decPacked.h, libdecNumber, bos53Q, q2008_07A2 2/1/08 06:13:44 */
/* ------------------------------------------------------------------ */
/* Packed Decimal conversion module header                            */
/* ------------------------------------------------------------------ */
/* Copyright (c) IBM Corporation, 2000, 2005.  All rights reserved.   */
/*                                                                    */
/* This software is made available under the terms of the             */
/* ICU License -- ICU 1.8.1 and later.                                */
/*                                                                    */
/* The description and User's Guide ("The decNumber C Library") for   */
/* this software is called decNumber.pdf.  This document is           */
/* available, together with arithmetic and format specifications,     */
/* testcases, and Web links, at: http://www2.hursley.ibm.com/decimal  */
/*                                                                    */
/* Please send comments, suggestions, and corrections to the author:  */
/*   mfc@uk.ibm.com                                                   */
/*   Mike Cowlishaw, IBM Fellow                                       */
/*   IBM UK, PO Box 31, Birmingham Road, Warwick CV34 5JL, UK         */
/* ------------------------------------------------------------------ */

#if !defined(DECPACKED)
  #define DECPACKED
  #define DECPNAME     "decPacked"                      /* Short name */
  #define DECPFULLNAME "Packed Decimal conversions"   /* Verbose name */
  #define DECPAUTHOR   "Mike Cowlishaw"               /* Who to blame */

  #define DECPACKED_DefP 32             /* default precision          */

  #ifndef  DECNUMDIGITS
    #define DECNUMDIGITS DECPACKED_DefP /* size if not already defined*/
  #endif
  #include "decNumber.h"                /* context and number library */

  /* Sign nibble constants                                            */
  #if !defined(DECPPLUSALT)
    #define DECPPLUSALT  0x0A /* alternate plus  nibble               */
    #define DECPMINUSALT 0x0B /* alternate minus nibble               */
    #define DECPPLUS     0x0C /* preferred plus  nibble               */
    #define DECPMINUS    0x0D /* preferred minus nibble               */
    #define DECPPLUSALT2 0x0E /* alternate plus  nibble               */
    #define DECPUNSIGNED 0x0F /* alternate plus  nibble (unsigned)    */
  #endif

  /* ---------------------------------------------------------------- */
  /* decPacked public routines                                        */
  /* ---------------------------------------------------------------- */
  /* Conversions                                                      */
  uint8_t * decPackedFromNumber(uint8_t *, int32_t, int32_t *,
                                const decNumber *);
  decNumber * decPackedToNumber(const uint8_t *, int32_t, const int32_t *,
                                decNumber *);

#endif
