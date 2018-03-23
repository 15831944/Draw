///////////////////////////////////////////////////////////////////////////////
// LayoutFactory.h : SFL Layout Node Factory
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
// Description:  SFL Layout Manager node factory definition
//

#pragma once

#if !defined(_SFL)
#define _SFL
#endif


#include <foundation\Patterns\Factory.h>
#include <foundation\Layout\LayoutBase.h>
#include <foundation\stwarn.h>
#include <map>
#include <foundation\stwarnp.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

//@doc


typedef foundation::ILayoutNode* (*_LayoutNodeCreator)();
typedef void (*_LayoutNodeDestructor)(foundation::ILayoutNode*);

struct LayoutMapEntry
{
	const GUID* pguid;
	_LayoutNodeCreator creator;
	_LayoutNodeDestructor destructor;
};

#define BEGIN_LAYOUT_MAP()	\
	namespace stingray{ \
		namespace foundation {	\
	foundation::LayoutMapEntry __LayoutMap[] = {

#define LAYOUT_MAP_ENTRY(nodeClass)	\
	{&__uuidof(nodeClass), nodeClass::CreateNode, nodeClass::DeleteNode},

#define END_LAYOUT_MAP() \
	{&IID_NULL, 0, 0}};	\
	};};



// Must declare a Layout Map for this symbol to be defined
extern foundation::LayoutMapEntry __LayoutMap[];


//@class CLayoutFactory |
// Helper class responsible for the creation and destruction of the
// layout nodes. Makes use of the layout map to locate the appropiate
// object factory when a node needs to be created.
class CLayoutFactory
{
public:
	CLayoutFactory(): m_pLayoutMap(__LayoutMap) {}
	CLayoutFactory(LayoutMapEntry* pMap): m_pLayoutMap(pMap) {}

public:
	ILayoutNode* CreateLayoutNode (
		const GUID& guid
		)
	{
		LayoutMapEntry* pCurrentEntry = FindEntry(guid);
		if (!pCurrentEntry) {
			return 0;
		}

		return pCurrentEntry->creator();
	}
	 
	void DestroyLayoutNode (ILayoutNode* pNode)
	{
		const GUID* guid = pNode->GetGUID();
		LayoutMapEntry* pCurrentEntry = FindEntry(*guid);
		if (!pCurrentEntry) {
			return;
		}
		ILayoutNode::Iterator* pos = NULL; 
		// Destroy all descendant nodes
		for (pos = pNode->GetChildNodesIterator(); !pos->Finished(); pos->Next()) {
			DestroyLayoutNode(pos->Current());
		}

		delete pos;
		pCurrentEntry->destructor(pNode);
	}
protected:
	LayoutMapEntry* m_pLayoutMap;

	LayoutMapEntry* FindEntry(const GUID& guid)
	{
		LayoutMapEntry* pCurrentEntry = m_pLayoutMap;

		bool bFound = false;
		while (!bFound && (*pCurrentEntry->pguid != IID_NULL)) {
			bFound = (*pCurrentEntry->pguid == guid) != 0;

			if (!bFound) {
				++pCurrentEntry;
			}
		}

		if (!bFound) {
			pCurrentEntry = NULL;
		}

		return pCurrentEntry;
	}
};

///////////////////////

};	// namespace stingray::foundation
};	// namespace foundation

