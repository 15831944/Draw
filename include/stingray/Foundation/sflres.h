///////////////////////////////////////////////////////////////////////////////
// sflres.h
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


#ifndef __SFLRES_H__
#define __SFLRES_H__


/////////////////////////////////////////////////////////////////////////////
// Custom resource formats

#ifndef RC_INVOKED
#if !defined(RT_DLGINIT)
#define RT_DLGINIT  MAKEINTRESOURCE(240)
#endif
#if !defined(RT_TOOLBAR)
#define RT_TOOLBAR  MAKEINTRESOURCE(241)
#endif
#endif //RC_INVOKED



/****************************************************
*****************************************************
// SFL Resource Ranges
// Resources   23000 - 23499
// Command IDs 45500 - 45999
*****************************************************
****************************************************/

/****************************************************
/////////////////////////////////////////////////////
// Low Resource Range divisions
/////////////////////////////////////////////////////
****************************************************/

/////////////////////////////////////////////////////
// Controls                            1000 - 2000
/////////////////////////////////////////////////////


/////////////////////////////////////////////////////
// Bitmaps, Cursors, Icons, Multiple    23000 - 23074
/////////////////////////////////////////////////////

#define IDB_CMN_DOWNARROW               23000
#define IDB_CMN_RIGHTARROW              23001
#define IDC_HSPLITBAR                   23002
#define IDC_VSPLITBAR                   23003
#define IDC_CROSSSPLITBAR               23004
#define IDC_MENURADIOBUTTON             23005
#define IDC_BARS_HAND					23006

/////////////////////////////////////////////////////
// General String Resources             23075 - 23149
/////////////////////////////////////////////////////

#define IDS_ALLFILES					23075

#define IDS_CMN_OTHERBUTTON             23100
#define IDS_CMN_SECIMAGE_MSG1           23101
#define ID_WINDOW_MENU_TEXT				23102
#define IDS_SFL_XMLFILTER				23103

/////////////////////////////////////////////////////
// Dialogs                              23150 - 23224
/////////////////////////////////////////////////////

#define IDD_PRINTPREVIEW_BAR            23150

/////////////////////////////////////////////////////
// Distinct Menus                       23225 - 23249
/////////////////////////////////////////////////////


/////////////////////////////////////////////////////
// Reserved for future expansion        23250 - 23499
/////////////////////////////////////////////////////

/****************************************************
/////////////////////////////////////////////////////
// High Resource Range divisions
/////////////////////////////////////////////////////
****************************************************/

/////////////////////////////////////////////////////
// Commands and Menu Prompts            45500 - 45749
/////////////////////////////////////////////////////

#define IDC_SFL_FILE_NEW					45601
#define IDC_SFL_FILE_OPEN					45602
#define IDC_SFL_FILE_SAVE					45603
#define IDC_SFL_FILE_SAVEAS					45604
#define IDC_SFL_FILE_PRINT					45605
#define IDC_SFL_FILE_PRINT_PREVIEW			45606
#define IDC_SFL_FILE_CLOSE					45607

#define IDC_SFL_MDI_CASCADE                  45660
#define IDC_SFL_MDI_TILEVERTICAL             45661
#define IDC_SFL_MDI_TILEHORIZONTAL           45662
#define IDC_SFL_MDI_ARRANGEICONS             45663

#define IDC_SFL_PPV_CLOSE                   45675
#define IDC_SFL_PPV_ZOOM                    45676
#define IDC_SFL_PPV_PRINT                   45677
#define IDC_SFL_PPV_NEXT                    45678
#define IDC_SFL_PPV_PREV                    45679

/////////////////////////////////////////////////////
// Reserved for future expansion        45750 - 45999
/////////////////////////////////////////////////////


#endif //__CMNRES_H__
