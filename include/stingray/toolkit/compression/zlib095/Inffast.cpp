///////////////////////////////////////////////////////////////////////////////
// inffast.cpp
//
// Copyright (c) 1999-2009 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government�s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////

/* inffast.c -- process literals and length/distance pairs fast
 *  
 * For conditions of distribution and use, see copyright notice in zlib.h 
 */
#define _OT_EXPORT_IMPL

#include "stdafx.h"  

#ifdef _SECDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif //_SECDLL

#ifndef __SECCOMP_H__
#include "compeng.h"
#endif

#ifndef _Z_UTIL_H
#include "zutil.h"
#endif

// #include "inftrees.h"
// #include "infblock.h"
// #include "infcodes.h"

#ifndef __INFUTIL_H__
#include "infutil.h"
#endif

// #include "inffast.h"

// struct inflate_codes_state {int dummy;}; /* for buggy compilers */

/* simplify the use of the inflate_huft type with some defines */
#define base more.Base
#define next more.Next
#define exop word.what.Exop
#define bits word.what.Bits

/* macros for bit input with no checking and for returning unused bytes */
#define GRABBITS(j) {while(k<(j)){b|=((uLong)NEXTBYTE)<<k;k+=8;}}
#define UNGRAB {n=(WORD)((WORD)n+(WORD)(c=(WORD)(k>>3)));p-=c;k&=7;}

/* Called with number of bytes left to write in window at least 258
   (the maximum string length) and number of input bytes available
   at least ten.  The ten bytes are six bytes for the longest length/
   distance pair plus four bytes for overloading the bit buffer. */

int SECComp::inflate_fast( WORD bl, WORD bd, inflate_huft *tl, inflate_huft *td,
	inflate_blocks_statef *s, z_stream *z)
{
  inflate_huft *t;      /* temporary pointer */
  WORD e;               /* extra bits or operation */
  DWORD b;              /* bit buffer */
  WORD k;               /* bits in bit buffer */
  BYTE *p;             /* input data pointer */
  DWORD n;               /* bytes available there */
  BYTE *q;             /* output window write pointer */
  WORD m;               /* bytes to end of window or read pointer */
  WORD ml;              /* mask for literal/length tree */
  WORD md;              /* mask for distance tree */
  WORD c;               /* bytes to copy */
  WORD d;               /* distance back to copy from */
  BYTE *r;             /* copy source pointer */

  /* load input, output, bit values */
  LOAD

  /* initialize masks */
  ml = inflate_mask[bl];
  md = inflate_mask[bd];

  /* do until not enough input or output space for fast loop */
  do {                          /* assume called with m >= 258 && n >= 10 */
    /* get literal/length code */
    GRABBITS(20)                /* max bits for literal/length code */
    if ((e = (t = tl + ((WORD)b & ml))->exop) == 0)
    {
      DUMPBITS(t->bits)
      ZTracevv((stderr, t->base >= 0x20 && t->base < 0x7f ?
                _T("inflate:         * literal '%c'\n") :
                _T("inflate:         * literal 0x%02x\n"), t->base));
      *q++ = (Byte)t->base;
      m--;
      continue;
    }
    do {
      DUMPBITS(t->bits)
      if (e & 16)
      {
        /* get extra bits for length */
        e &= 15;
        c = (WORD)(t->base + ((WORD)b & inflate_mask[e]));
        DUMPBITS(e)
        ZTracevv((stderr, _T("inflate:         * length %u\n"), c));

        /* decode distance base of block to copy */
        GRABBITS(15);           /* max bits for distance code */
        e = (t = td + ((WORD)b & md))->exop;
        do {
          DUMPBITS(t->bits)
          if (e & 16)
          {
            /* get extra bits to add to distance base */
            e &= 15;
            GRABBITS(e)         /* get extra bits (up to 13) */
            d = (WORD)(t->base + ((WORD)b & inflate_mask[e]));
            DUMPBITS(e)
            ZTracevv((stderr, _T("inflate:         * distance %u\n"), d));

            /* do the copy */
            m = (WORD)((WORD)m - (WORD)c);
            if ((WORD)(q - s->window) >= d)     /* offset before dest */
            {                                   /*  just copy */
              r = q - d;
              *q++ = *r++;  c--;        /* minimum count is three, */
              *q++ = *r++;  c--;        /*  so unroll loop a little */
            }
            else                        /* else offset after destination */
            {
              e = (WORD)(d - (q - s->window));  /* bytes from offset to end */
              r = s->end - e;           /* pointer to offset */
              if (c > e)                /* if source crosses, */
              {
                c = (WORD)(c - (WORD)e);                 /* copy to end of window */
                do {
                  *q++ = *r++;
				  --e;
                } while (e);
                r = s->window;          /* copy rest from start of window */
              }
            }
            do {                        /* copy all or what's left */
              *q++ = *r++;
			  --c;
            } while (c);
            break;
          }
          else if ((e & 64) == 0)
            e = (t = t->next + ((WORD)b & inflate_mask[e]))->exop;
          else
          {
            z->msg = _T("invalid distance code");
            UNGRAB
            UPDATE
            return Z_DATA_ERROR;
          }
        } while (1);
        break;
      }
      if ((e & 64) == 0)
      {
        if ((e = (t = t->next + ((WORD)b & inflate_mask[e]))->exop) == 0)
        {
          DUMPBITS(t->bits)
          ZTracevv((stderr, t->base >= 0x20 && t->base < 0x7f ?
                    _T("inflate:         * literal '%c'\n") :
                    _T("inflate:         * literal 0x%02x\n"), t->base));
          *q++ = (Byte)t->base;
          m--;
          break;
        }
      }
      else if (e & 32)
      {
        ZTracevv((stderr, _T("inflate:         * end of block\n")));
        UNGRAB
        UPDATE
        return Z_STREAM_END;
      }
      else
      {
        z->msg = _T("invalid literal/length code");
        UNGRAB
        UPDATE
        return Z_DATA_ERROR;
      }
    } while (1);
  } while (m >= 258 && n >= 10);

  /* not enough input or output--restore pointers and return */
  UNGRAB
  UPDATE
  return Z_OK;
}
