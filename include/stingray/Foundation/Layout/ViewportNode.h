///////////////////////////////////////////////////////////////////////////////
// ViewportNode.h : SFL Layout Manager
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
// Author:       Gilberto Araya
// Description:  SFL Layout Manager: MVC Viewport layout node
//

#pragma once

#if !defined(_SFL)
#define _SFL
#endif

#ifndef _SFL_NO_PRAGMA_WARNINGS
	#if 1200 <= _MSC_VER
		#pragma warning(push,3)
	#endif
	#pragma warning(disable:4097)
#endif

#include <foundation\Layout\LayoutNode.h>
#include <foundation\Layout\DCNode.h>
#include <foundation\String\sflstring.h>
#include <foundation\StructuredGraphics\Visual.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

#pragma warning(disable: 4275)

//@doc


//@interface IViewportNode |
//  Interface that helps integrate SFL's layout manager with the Model-View-Controller (MVC)
//  architecture. 
//@base | ILayoutNode
interface __declspec(uuid("0B3556B0-6171-11d3-9D9A-00C04F91E286")) IViewportNode:
	public ILayoutNode
{
	//@meth,method void | Init |
	// Initializes a viewport layout node. Unlike the version of Init() 
	// found in ILayoutNode, it receives in its second parameter a pointer
	// to the IVisual interface implemented by the viewport. 
	//@@syntax pVPNode->Init(hwndParent, pVP);
	//@@parm HWND | hwndParent | Window associated to the entire layout manager structure.
	//@@parm IVisual* | pVP | Pointer to the IVisual interface implemented by the viewport.
	//@@comm
	// After this method returns, the layout node is permanently associated with the
	// viewport pointed by pVP. If this viewport gets destroyed by some means other than
	// upon the window destruction, you need to manually destroy this layout node.
	virtual void Init(HWND hwndParent, foundation::IVisual* pVP) = 0;
};


//@class CViewportNode |
// Implementation of the IViewportNode interface.<nl>
// Provides integration of the Layout Manager service with the
// MVC architecture, by allowing MVC windowless viewports to participate
// in layout operations.<nl>
//@base public | CDCLayoutBase<lt>CViewportNode, IViewportNode<gt>
//@comm 
// There are two types of viewports in MVC: windowed viewports and windowless
// viewports. The former are implemented as real windows, so they can be attached
// to standard window layout nodes. Windowless viewports draw directly on the area 
// of their master window, they do not have a window of their own. This characteristic
// is very similar to the functionality <c CDCLayoutBase> offers in the context
// of the layout manager. CViewportNode specializes CDCLayoutBase by delegating the
// painting processes to the corresponding IVisual methods, and performing the appropiate
// steps in RealizeNode to assign the new area to the viewport.
class __declspec(uuid("0B3556B1-6171-11d3-9D9A-00C04F91E286"))  CViewportNode:
	public CDCLayoutBase<CViewportNode, IViewportNode>
{
public:
	typedef CDCLayoutBase<CViewportNode, IViewportNode> _LayoutBase;

	CViewportNode(): m_pVP(0) {}

public:
	virtual void Init(HWND hwndParent, HWND hwndChild = 0);
	virtual bool OnRealizeNode(CLayoutTransaction& aTransaction);

	virtual void Init(HWND hwndParent, foundation::IVisual* pVP);

protected:
	// CDCLayoutBase overrides

	virtual void OnPaint(HDC hDC = NULL);
	virtual bool PrepareDC(HDC);
	virtual void RestoreDC(HDC);

private:
	IVisual* m_pVP;
};

};
};


#ifndef _SFL_ALL_WARNINGS
#pragma warning (pop)
#endif
