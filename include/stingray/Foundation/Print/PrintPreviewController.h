///////////////////////////////////////////////////////////////////////////////
// PrintPreviewController.h : Print preview controller class.
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
// Author:       Jeff Boenig
// Description:  Print preview controller class.
//

#pragma once

#include <Foundation\Print\PrintPreviewModel.h>
#include <Foundation\Events\CommandListener.h>
#include <Foundation\Events\KeyboardListener.h>
#include <Foundation\MVC\MvcVisualComponent.h>
#include <Foundation\MVC\MvcController.h>
#include <Foundation\Debug.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

//////////////////////////////////////////////////////////////////////////
//@doc CPrtPreviewController

class FOUNDATION_API CPrtPreviewController : public CMvcController<CPrtPreviewModel, CMvcVisualComponent>,
                              public CCommandAdapter,
                              public CKeyboardAdapter
{
public:
	CPrtPreviewController()
	{
		AddListener(static_cast<CCommandAdapter*>(this));
	}

	virtual bool OnCommand(UINT nID, int nNotifyCode)
	{
		// To get rid of warning
		nID;
		nNotifyCode;

		return false;
	}

	virtual bool OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		// to get rid of warning
		nRepCnt;
		nFlags;

		bool bHandled = false;
		CPrtPreviewModel* pModel = GetModel();
		if (pModel != NULL)
		{
			if (nChar == VK_NEXT)
			{
				pModel->GotoNextPage();
				bHandled = true;
			}
		}
		return bHandled;
	}
};

}; // namespace stingray::foundation
}; // namespace stingray

