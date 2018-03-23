///////////////////////////////////////////////////////////////////////////////
// sdcvwfbk.h
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
//  Author:       Daniel Jebaraj
//  Description:  Declarations for ISECVwDockFeedBack and SECVwDockFeedBackOleImp
//  Created:      April 1999
//

#ifdef WIN32

#ifndef __S_DC_VW_FBK_H__
#define __S_DC_VW_FBK_H__

#include <StingrayExportDefs.h>

//
// SEC Extension DLL
// Initialize declaration context
//

#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL


// ISECVwDockFeedBack

//@doc ISECVwDockFeedBack 
//@struct Interface for feedback when view docking takes place
//@comm Implement this interface in your derived view to recieve docking feedback
struct ISECVwDockFeedBack
{
	/* Called before docking takes place*/
	virtual void PreDock(CFrameWnd* pFrameOld, CFrameWnd* pFrameNew) = 0; // @field Called before docking takes place
	
	/* Called after docking takes place*/
	virtual void PostDock(CFrameWnd* pFrameNew) = 0; // @field Called after docking takes place
	
	/* Called prior to undocking view*/
	virtual void PreUnDock(CFrameWnd* pFrameOld, CFrameWnd* pFrameNew) = 0; // @field Called prior to undocking view
	
	/* Called after undocking view*/
	virtual void PostUnDock(CFrameWnd* pFrameNew) = 0;  // @field Called after undocking view
};


//@doc SECVwDockFeedBackOleImp 
//@class Interface for feedback when view docking takes place
//@BASE public | ISECVwDockFeedBack
//@comm SECVwDockFeedBackOleImp handles docking feedback to facilitate better
// support for OLE containment when docking views is used. Derive your view
// from this class if you use docking views and have OLE containment support.
class SECVwDockFeedBackOleImp : public ISECVwDockFeedBack
{
public:
	TOOLKIT_API SECVwDockFeedBackOleImp();

	//@cmember
	/* Called before docking takes place*/
	TOOLKIT_API void PreDock(CFrameWnd* pFrameOld, CFrameWnd* pFrameNew);
	
	//@cmember
	/* Called after docking takes place*/
	TOOLKIT_API void PostDock(CFrameWnd* pFrameNew);
	
	//@cmember
	/* Called prior to undocking view*/
	TOOLKIT_API void PreUnDock(CFrameWnd* pFrameOld, CFrameWnd* pFrameNew);
	
	//@cmember
	/* Called after undocking view*/
	TOOLKIT_API void PostUnDock(CFrameWnd* pFrameNew);

protected:
	COleClientItem* m_pUIActiveCItem;

	TOOLKIT_API virtual void PreDockUnDockHelper(CFrameWnd* pFrameOld, CFrameWnd* pFrameNew);
	TOOLKIT_API virtual void PostDockUnDockHelper(CFrameWnd* pFrameNew);
};

//
// SEC Extension DLL
// Reset declaration context
//
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __S_DC_VW_FBK_H__

#endif // WIN32
