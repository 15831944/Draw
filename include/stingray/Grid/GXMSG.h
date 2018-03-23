///////////////////////////////////////////////////////////////////////////////
// GXMSG.h : User defined window messages.
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
//
// Author: Stefan Hoenig
//

#ifndef _GXMSG_H
#define _GXMSG_H

// According to MFC documentation, user defined messages
// should be defined in the range WM_USER to 0x7FFF.
//
// Objective Grid uses the range WM_USER+901 to WM_USER+999


////////////////////////////////////////////////////////
// CGXTabWnd

#define WM_GX_TABSWITCH     (WM_USER+901)
#define WM_GX_TABDBLCLK     (WM_USER+902)
#define WM_GX_CANTABSWITCH  (WM_USER+903)


////////////////////////////////////////////////////////
// CGXTabBeam

#define WM_GX_INITTAB       (WM_USER+911)
#define WM_GX_NEEDCHANGETAB (WM_USER+912)
#define WM_GX_CHANGEDTAB    (WM_USER+913)
#define WM_GX_CANACTIVATE   (WM_USER+914)

#define WM_GX_EDITEND       (WM_USER+921)
#define WM_GX_EDITCANCEL    (WM_USER+922)


////////////////////////////////////////////////////////
// CGXRecordInfoWnd

#define WM_GX_MOVERECORD    (WM_USER+931)

// Attributes for WM_GX_MOVERECORD
#define GX_MOVERECORD_FIRST 0
#define GX_MOVERECORD_PREV  1
#define GX_MOVERECORD_NEXT  2
#define GX_MOVERECORD_LAST  3
#define GX_MOVERECORD_SEEK  4



////////////////////////////////////////////////////////
// CGXComboBox

#define WM_GX_LBOXEND       (WM_USER+941)
#define WM_GX_LBOXCANCEL    (WM_USER+952)
#define WM_GX_LBOXCHANGED   (WM_USER+963)
#define WM_GX_LBOXKILLFOCUS (WM_USER+964)

////////////////////////////////////////////////////////
// CGXGridCore - Smart Resizing

#define WM_GX_LOCKRESIZE    (WM_USER+971)

// Calendar-control-to-parent messages.
#define GXDT_DATESELECTED				(WM_USER+981)
#define GXDT_HIGHLIGHTLISTCHANGED		(WM_USER+982)
#define GXDT_OK							(WM_USER+983)
#define GXDT_CANCEL						(WM_USER+984)

// Attributes for WM_GX_LOCKRESIZE

#define GX_STARTRESIZE      1
#define GX_ENDRESIZE        0

////////////////////////////////////////////////////////
// CGXColorButtonBox (used in Color page and Properties dialog)

#define WM_GX_COLORCHANGED				(WM_USER+987)

////////////////////////////////////////////////////////
// Intellimouse

#define WM_GX_IMOUSE_GETZOOM			(WM_USER+991)
#define WM_GX_IMOUSE_SETZOOM			(WM_USER+992)

#define GX_IMOUSETIMER		991

////////////////////////////////////////////////////////
// Autoscroll

#define GX_AUTOSCROLLTIMER	992



////////////////////////////////////////////////////////
// Cell Tips

#define GX_CELLTIPTIMER		993


////////////////////////////////////////////////////////////////////////////////////
// messages that are used by grid workbook frame windows to initialize created views
// Workbook persistence

#define WM_GX_INITNEW					(WM_USER+993)
#define WM_GX_INITFILE					(WM_USER+994)
#define GX_INVALID_CREATEINFOINDEX		0xFFFFFFFF

#define GX_DEFNUMTABS		3

// for the currency control
#define WM_GX_SETTEXT					(WM_USER+995)

// for OG Pro
#define WM_GXINITIALUPDATE					(WM_USER+996)
#define WM_GXINITIALUPDATEDONE				(WM_USER+997)

// for Database requery
#define WM_GX_REQUERY					(WM_USER+998)
// for ADO (use the same as above)
#define WM_GX_ADO_REQUERY				WM_GX_REQUERY

#endif // _GXMSG_H
