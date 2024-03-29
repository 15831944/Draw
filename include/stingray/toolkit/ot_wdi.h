///////////////////////////////////////////////////////////////////////////////
// ot_wdi.h
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
// 
//  Author:			Rob Oliver
//  Description:	ot_wdi.h - WDI (MDI alternative) component header
//  Created:		Tue Aug 27 14:08:25 1998
//
//

#ifndef __OTM_WDI_H__
#define __OTM_WDI_H__

// ***********************************************************
// *
// *  OT needs 8 byte packing for structures
// *
// ***********************************************************

#if (_MFC_VER >= 0x0300)
// pshpack8.h saves the current #pragma pack value
#include "pshpack8.h"
#else
#pragma pack(8)
#endif

// ***********************************************************
// *
// *  OT optimized include file
// *
// ***********************************************************

#ifndef __SECOPT_H__
    #include "toolkit\secopt.h"
#endif

// ***********************************************************
// *
// *  Workbook Document Interface
// *
// ***********************************************************

#ifdef OT_BLD_WDI

	// SECFrameWnd
	#ifndef __SWINMDI_H__
	#include "toolkit\swinmdi.h"
	#endif //__SWINMDI_H__

	// SECMDIFrameWnd
	#ifndef __SWINFRM_H__
	#include "toolkit\swinfrm.h"
	#endif //__SWINFRM_H__

	// SECCDialogBar
	#ifndef __SBARDLG_H__
	#include "toolkit\sbardlg.h"
	#endif //__SBARDLG_H__

	// SECDockBar
	#ifndef __SECBARDOCK_H__
	#include "toolkit\sbardock.h"
	#endif //__SECBARDOCK_H__

	// SECControlBar
	#ifndef __SBARCORE_H__
	#include "toolkit\sbarcore.h"
	#endif //__SBARCORE_H__

	// SECToolBar
	#ifndef __SBARTOOL_H__
	#include "toolkit\sbartool.h"
	#endif //__SBARTOOL_H__

	// SECStatusBar
	#ifndef __SBARSTAT_H__
	#include "toolkit\sbarstat.h"
	#endif //__SBARSTAT_H__


	#ifndef __SDOCKCNT_H__
	#include "toolkit\sdockcnt.h"
	#endif //__SDOCKCNT_H__

	// SECDockContext
	#ifndef __SDOCKSTA_H__
	#include "toolkit\sdocksta.h"
	#endif

	// SECControlBarManager
	#ifndef __SBARMGR_H__
	#include "toolkit\sbarmgr.h"
	#endif //__SBARMGR_H__

	// SECOleServerItem
	#ifndef __SECOLEDOCK_H__
	#include "toolkit\SOleDock.h"
	#endif

	#ifndef __SECWB_H__
	#include "toolkit\secwb.h"
	#endif //__SECWB_H__

#else
	#pragma message("Warning:  WDI support was not included in the Objective Toolkit library.")
	#pragma message("          Add this component to the library using the BuildWizard and rebuild Objective Toolkit.")
#endif // OT_BLD_WDI

// ***********************************************************
// *
// *  Restore default byte packing
// *
// ***********************************************************

#if (_MFC_VER >= 0x0300)
// poppack.h restores the original #pragma pack value
#include /* */ "poppack.h"
#else
// restore default packing value
#pragma pack()
#endif

#endif // __OTM_WDI_H__
