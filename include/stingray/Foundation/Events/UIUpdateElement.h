///////////////////////////////////////////////////////////////////////////////
// UIUpdateElement.h : Interface for UIUpdate elements.
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
// Authors:      Jeff Boenig and George Shepherd
// Description:  Framework independent event model.
//

#pragma once

#ifndef __UIUPDATEELEMENT_H__
#define __UIUPDATEELEMENT_H__

#include <foundation\SflGuids.h>
#include <foundation\SflCommon.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//@doc IUIUpdateElement
//
//@class IUIUpdateElement | Interface for user interface elements that
// can be updated by a UI update listener. Provides a consistent
// interface to UI update listeners for modifying menus, toolbars,
// status bars, etc.
//
//@base public | IRefCount, IQueryGuid
//
class __declspec(uuid("85A9C953-7B7D-11d3-8160-00C04F8D83A6"))
				IUIUpdateElement : public IRefCount, public IQueryGuid
{
public:
	//@cmember
	/* Call this to the te the text of the interface element. */
	virtual void SetText(const UINT nCommandID, LPCTSTR) = 0;

	//@cmember
	/* Call this to enable or disable the interface element. */
	virtual void Enable(const UINT nCommandID, bool bEnable = true) = 0;

	//@cmember
	/* Call this to turn on or off a radio button within the interface element. */
	virtual void SetRadio(const UINT nCommandID, bool bEnable = true) = 0;

	//@cmember
	/* Call this to turn on or off a check button within the interface element. */
	virtual void SetCheck(const UINT nCommandID, int nState = 1) = 0;
};

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __UIUPDATEELEMENT_H__
