///////////////////////////////////////////////////////////////////////////////
// ActvHost.h
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
//  Author:			Mark Isham
//  Description:	ActvHost.h - ActiveHost composite header
//  Created:		August 1997
//
//
//	This file is included via "ProAll.h"
//

#ifndef __ACTIVEHOST_H_
#define __ACTIVEHOST_H_

// For internal use only
// This macro is provided to toggle ActiveScript docking window
// compatibility.
#ifdef OT_BLD_DOCKWIN
	#define SEC_TOOLBAR	SECToolBar
	#define SEC_SDIFRAMEWND SECFrameWnd
	#include "toolkit\sbartool.h"
	#include "toolkit\swinfrm.h"
#else
	#define SEC_TOOLBAR CToolBar
	#define SEC_SDIFRAMEWND CFrameWnd
#endif

#include <afxole.h>

#pragma warning(disable:4201)
#include <vfw.h>		// to speed up compilation
#pragma warning(default:4201)

#include "toolkit\ActvHost\AppInfo.h"
#include "toolkit\ActvHost\AppObj.h"
#include "toolkit\ActvHost\FormObj.h"
#include "toolkit\ActvHost\ScriptHost.h"
#include "toolkit\ActvHost\ScriptHostView.h"
#include "toolkit\ActvHost\ScriptHostDoc.h"
#include "toolkit\ActvHost\CodeView.h"
#include "toolkit\ActvHost\CodeViewRTF.h"
#include "toolkit\ActvHost\ContainerProps.h"
#include "toolkit\ActvHost\CtrlItem.h"
#include "toolkit\ActvHost\CustToolBoxDlg.h"
#include "toolkit\ActvHost\Debug.h"
#include "toolkit\ActvHost\Dib.h"
#include "toolkit\ActvHost\DlgFrame.h"
#include "toolkit\ActvHost\ErrorDlg.h"
#include "toolkit\ActvHost\EventBar.h"
#include "toolkit\ActvHost\EventList.h"
#include "toolkit\ActvHost\FactoryPpg.h"
#include "toolkit\ActvHost\FormPpg.h"
#include "toolkit\ActvHost\Helpers.h"
#include "toolkit\ActvHost\HelpersBitmap.h"
#include "toolkit\ActvHost\inctldlg.h"
#include "toolkit\ActvHost\MULTINFO.H"
#include "toolkit\ActvHost\OleFont.h"
#include "toolkit\ActvHost\SECApicture.h"
#include "toolkit\ActvHost\PropBrowser.h"
#include "toolkit\ActvHost\PropList.h"
#include "toolkit\ActvHost\PropListBox.h"
#include "toolkit\ActvHost\ahostres.h"
#include "toolkit\ActvHost\Selection.h"
#include "toolkit\ActvHost\SelTracker.h"
#include "toolkit\ActvHost\ToolBox.h"
#include "toolkit\ActvHost\TopLevelItem.h"
#include "toolkit\ActvHost\Utils.h"
#include "toolkit\ActvHost\LangObj.h"
#include "toolkit\ActvHost\JScriptlang.h"
#include "toolkit\ActvHost\VBSlang.h"
// Not including this file as part of the PCH while building the library since it pulls in
// src/occimpl.h which sometimes causes linker problems when included in PCHs.
#ifndef SEC_LIB_BUILD	
#include "toolkit\ActvHost\ScriptSite.h"
#endif
#include "toolkit\ActvHost\FloatingDocTemplate.h"
#include "toolkit\ActvHost\Tokenizer.h"
#include "toolkit\ActvHost\browseh.h"
#include "toolkit\ActvHost\ColorEditor.h"
#include "toolkit\ActvHost\mydisp.h"
#include "toolkit\ActvHost\tlb.h"

#endif __ACTIVEHOST_H_
