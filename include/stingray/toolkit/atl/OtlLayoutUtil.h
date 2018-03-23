///////////////////////////////////////////////////////////////////////////////
// OtlLayoutUtil.h
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

#ifndef __OTLLAYOUTUTIL_H__
#define __OTLLAYOUTUTIL_H__

#ifndef __OTLBASE_H__
	#error otllayoututil.h requires otlbase.h to be included first
#endif

#include <Toolkit\atl\otlwindownode.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL
{

/////////////////////////////////////////////////////////////////////////////
// COtlLayoutFactory

class COtlLayoutFactory
{
public:

	inline BOOL AutoPopulateNodeWnd( COtlLayoutNode* pParentNode, HWND hwndParent)
	{
		OTLASSERT(::IsWindow(hwndParent));
		if(!pParentNode) return FALSE;
		// iterate through the children, allocating and adding as we go
		HWND hwndChild = ::GetWindow(hwndParent, GW_CHILD);
		while(hwndChild) 
		{
			COtlWindowNode* pNode = CreateNodeWnd( hwndChild, hwndParent);
			if( pNode )
				pParentNode->AddChild(pNode);
			hwndChild = ::GetNextWindow(hwndChild, GW_HWNDNEXT);
		}
		return TRUE;											
	}


	inline COtlWindowNode* CreateNodeWnd( HWND hwndAttach, 
									      HWND hwndParent,
									      COtlLayoutNode* pParentNode=NULL) 
	{
		COtlWindowNode* pNode = new COtlWindowNode;
		if(!pNode) return pNode;

		// now, try to autoset and attach. If failure, dealloc and return NULL for failure.
		// (note: autoset must be done first for proper intialization order).
		if( (!OnAutoSetNode(pNode)) || (!pNode->AttachWnd(hwndAttach, hwndParent)) ) 
		{
			delete pNode;
			return NULL;
		}

		// Must perform add after attach phase 
		if(pParentNode) 
		{
			if(!pParentNode->AddChild(pNode)) 
			{
				delete pNode;
				return NULL;
			}
		}
		
		return pNode;
	}

	inline COtlWindowNode* CreateNodeWnd(	const int nIDAttachWnd, 
									HWND hwndParent,
									COtlLayoutNode* pParentNode=NULL )
	{
		OTLASSERT(hwndParent);
		HWND hwndAttach = ::GetDlgItem(hwndParent, nIDAttachWnd);
		// invalid control ID
		OTLASSERT(hwndAttach);
		if(!hwndAttach)
			return NULL;
		return CreateNodeWnd(hwndAttach, hwndParent, pParentNode);
	}

	inline BOOL OnAutoSetNode(COtlLayoutNode* pNode) { return TRUE; }

	inline int CreateNodeWndArray(	const UINT* lpuIDs,int nIDCount,
							HWND hwndParent,
							COtlLayoutNode* pParentNode )
	{
		// Verify valid memory buffer
		if(!lpuIDs) return -1;
			// Iterate through and add all command ids in the array
		int nAddCount=0;
		UINT uWndID;
		COtlWindowNode* pNodeWnd;
		for(int nID=0;nID < nIDCount; ++nID) 
		{
			uWndID = *lpuIDs++;
			pNodeWnd = CreateNodeWnd(uWndID,hwndParent,pParentNode);
			if(pNodeWnd) 
			{
				++nAddCount;
			}
		}
		return nAddCount;
	}


	inline COtlLayoutNode* CreateNode(COtlLayoutNode* pParentNode=NULL)
	{
		COtlLayoutNode* pNode = new COtlLayoutNode;
		if( pNode && pParentNode)
		{
			if(!pParentNode->AddChild(pNode)) 
			{
				delete pNode;
				pNode=(COtlLayoutNode *)NULL;
			}
		}
		return pNode;
	}

};

};	// namespace StingrayOTL

#endif // __OTLLAYOUTUTIL_H__
