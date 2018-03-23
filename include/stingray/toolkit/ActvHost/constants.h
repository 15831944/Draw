///////////////////////////////////////////////////////////////////////////////
// constants.h
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
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _CNSTANTS_H_
#define _CNSTANTS_H_

/////////////////////// start namespace SECActiveScript

namespace SECActiveScript{

// color and background can be set for the following items
//--------------------------------------------------------
enum ITEMS
{
   ITEM_CURRLINE, ITEM_SELTEXT,
   ITEM_KEYWORD, ITEM_COMMENT, ITEM_TYPE, ITEM_STRING, ITEM_IDENTIFIER,
   ITEM_INTCONST, ITEM_REALCONST, ITEM_CHARCONST, ITEM_DEFTEXT,
   ITEM_NEWLINE, ITEM_EOI
};

// define macros to represent colors literally
//--------------------------------------------
#define  BLACK          ( RGB( ( 0 ), ( 0 ), ( 0 ) ) )
#define  GRAY           ( RGB( ( 128 ), ( 128 ), ( 128 ) ) )

#define  LIGHTGRAY      ( RGB( ( 192 ), ( 192 ), ( 192 ) ) )
#define  WHITE          ( RGB( ( 255 ), ( 255 ), ( 255 ) ) )

#define  BROWN          ( RGB( ( 128 ), ( 0 ), ( 0 ) ) )
#define  RED            ( RGB( ( 255 ), ( 0 ), ( 0 ) ) )

#define  GREEN          ( RGB( ( 0 ), ( 128 ), ( 0 ) ) )
#define  LIGHTGREEN     ( RGB( ( 0 ), ( 255 ), ( 0 ) ) )

#define  BLUE           ( RGB( ( 0 ), ( 0 ), ( 128 ) ) )
#define  LIGHTBLUE      ( RGB( ( 0 ), ( 0 ), ( 255 ) ) )

#define  CYAN           ( RGB( ( 0 ), ( 128 ), ( 128 ) ) )
#define  LIGHTCYAN      ( RGB( ( 0 ), ( 255 ), ( 255 ) ) )

#define  MAGENTA        ( RGB( ( 128 ), ( 0 ), ( 128 ) ) )
#define  LIGHTMAGENTA   ( RGB( ( 255 ), ( 0 ), ( 255 ) ) )

#define  KHACKY         ( RGB( ( 128 ), ( 128 ), ( 0 ) ) )
#define  YELLOW         ( RGB( ( 255 ), ( 255 ), ( 0 ) ) )

// default text colors for different items
//----------------------------------------
#define  DEFCOLOR_KEYWORD     LIGHTBLUE
#define  DEFCOLOR_COMMENT     GREEN
#define  DEFCOLOR_TYPE        BROWN // RED
#define  DEFCOLOR_STRING      KHACKY
#define  DEFCOLOR_IDENTIFIER  BLACK
#define  DEFCOLOR_INTCONST    BLACK
#define  DEFCOLOR_REALCONST   BLACK
#define  DEFCOLOR_CHARCONST   BLACK
#define  DEFCOLOR_DEFTEXT     BLACK

// default background colors for different items
//----------------------------------------------
#define  DEFBKGRND_KEYWORD    WHITE
#define  DEFBKGRND_COMMENT    WHITE
#define  DEFBKGRND_TYPE       WHITE
#define  DEFBKGRND_STRING     WHITE
#define  DEFBKGRND_IDENTIFIER WHITE
#define  DEFBKGRND_INTCONST   WHITE
#define  DEFBKGRND_REALCONST  WHITE
#define  DEFBKGRND_CHARCONST  WHITE
#define  DEFBKGRND_DEFTEXT    WHITE

// default color and background for the current line
//--------------------------------------------------
#define  DEFCOLOR_CURRLINE    BLACK
#define  DEFBKGRND_CURRLINE   YELLOW

// default color and background for the selected text
//---------------------------------------------------
#define  DEFCOLOR_SELTEXT     WHITE
#define  DEFBKGRND_SELTEXT    BLUE


// define some virtual key codes
//------------------------------
#define  VK_0      0x30
#define  VK_1      0x31
#define  VK_2      0x32
#define  VK_3      0x33
#define  VK_4      0x34
#define  VK_5      0x35
#define  VK_6      0x36
#define  VK_7      0x37
#define  VK_8      0x38
#define  VK_9      0x39
#define  VK_A      0x41
#define  VK_B      0x42
#define  VK_C      0x43
#define  VK_D      0x44
#define  VK_E      0x45
#define  VK_F      0x46
#define  VK_G      0x47
#define  VK_H      0x48
#define  VK_I      0x49
#define  VK_J      0x4A
#define  VK_K      0x4B
#define  VK_L      0x4C
#define  VK_M      0x4D
#define  VK_N      0x4E
#define  VK_O      0x4F
#define  VK_P      0x50
#define  VK_Q      0x51
#define  VK_R      0x52
#define  VK_S      0x53
#define  VK_T      0x54
#define  VK_U      0x55
#define  VK_V      0x56
#define  VK_W      0x57
#define  VK_X      0x58
#define  VK_Y      0x59
#define  VK_Z      0x5A
#define  BACKSPACE 0x08
#define  ESCAPE    0x1B

#define  SPACE     ' '

} /////////////////////// end namespace SECActiveScript

extern int   m_nCurrLine;

#endif // _CNSTANTS_H_

