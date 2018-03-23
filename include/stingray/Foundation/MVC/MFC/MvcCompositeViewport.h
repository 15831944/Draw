///////////////////////////////////////////////////////////////////////////////
// MvcCompositeViewport.h : Implementation of MvcCompositeViewport
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
//  Author:       Brad King
//  Description:  Implementation of MvcCompositeViewport
//

//@doc MvcCompositeViewport

#pragma once

#ifndef __MFC_MVCCOMPOSITEVIEWPORT_H__
#define __MFC_MVCCOMPOSITEVIEWPORT_H__

// Header Includes
#include <Foundation\MVC\MFC\MvcViewport.h>

//
// MVC Extension DLL
// Initialize declaration context
//
#ifdef _SFLDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SFL_DATAEXT
#endif //_SFLDLL

namespace stingray {
namespace foundation {

/////////////////////////////////////////////////////////////////////////////
// MvcCompositeViewport

//@doc MvcCompositeViewport
//@mdata ComponentSet | MvcCompositeViewport | m_setComponents | The internal collection declaration
//@xref <c MvcCompositeViewport>

//@doc MvcCompositeViewport
//@mfunc void  | MvcCompositeViewport | AddComponent | Adds a child component to the composite
//@parm MvcVisualComponent* | pComponent | A pointer to the visual component to add.
//@xref <c MvcCompositeViewport>

//@doc MvcCompositeViewport
//@mfunc void  | MvcCompositeViewport | RemoveComponent | Removes a component from the composite
//@parm MvcVisualComponent* | pComponent | A pointer to the visual component to remove. The object itself will not be deleted.
//@xref <c MvcCompositeViewport>

//@doc MvcCompositeViewport
//@mfunc void  | MvcCompositeViewport | CreateComponents | Creates child components. Called by SetModel
//@parm MvcVisualComponent* | pComponent | A pointer to the visual component to remove. The object itself will not be deleted.
//@xref <c MvcCompositeViewport>

//@doc MvcCompositeViewport
//@class This class simplifies the use of child components by providing a default
// collection implementation. Children can be added or removed from the collection,
// and each child will have it's Draw function called during the painting process.
// A function for hit testing child components in the composite helps controllers
// determine appropriate commands for child component actions. 
//
//@base public | MvcViewport

 
class FOUNDATION_API MvcCompositeViewport : public MvcViewport
{
public:
	typedef CCArray_T<MvcVisualComponent*,MvcVisualComponent*> ComponentSet;

	MvcCompositeViewport();
	virtual ~MvcCompositeViewport();

public:
	// MvcViewport overrides
	//@cmember
	/* Draws this viewport and calls Draw for all children in the composite*/
	virtual void Draw(CDC* pDC);
	//@cmember
	/* Sets the model that this viewport will observe*/
	virtual void SetModel(MvcModel* pModel);
	//@cmember
	/* Determines the child component that contains a point*/
	virtual MvcVisualComponent* HitTestComponent( CPoint pt );
	//@cmember
	/* Adds a child component to the composite*/
	virtual int AddComponent(MvcVisualComponent* pComponent){ return (int)m_setComponents.Add(pComponent);}
	//@cmember
	/* Removes a child component from the composite*/
	virtual void RemoveComponent(MvcVisualComponent* pComponent){ m_setComponents.Remove(pComponent);}
	//@cmember
	/* Returns the collection of children in the composite viewport*/
	inline ICollection_T<MvcVisualComponent*>* GetComponents();

protected:
	//@cmember
	/* Override this function to initially create child components. Called by SetModel()*/
	virtual void CreateComponents(){;}
	//@cmember
	/* Deletes all child components and empties the collection*/
	virtual void DestroyComponents();


protected:
	//@cmember
	/* The internal collection declaration*/
	ComponentSet m_setComponents;
};

//@doc MvcCompositeViewport
//@mfunc Returns the collection of children in the composite viewport
//@rdesc The collection of children
inline ICollection_T<MvcVisualComponent*>* MvcCompositeViewport::GetComponents()
{
	return &m_setComponents;
}

};  // namespace stingray::foundation
};  // namespace stingray

//
// MVC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif  // #ifndef __MFC_MVCCOMPOSITEVIEWPORT_H__

