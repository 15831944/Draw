///////////////////////////////////////////////////////////////////////////////
// CtrlItem.h
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

#ifndef _CCtrlItem_H
#define _CCtrlItem_H

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

class SECScriptHostDoc;
class SECScriptHostView;

class SECACtrlItem : public COleClientItem
{
	TOOLKIT_DECLARE_SERIAL(SECACtrlItem)
	TOOLKIT_API SECACtrlItem();

public:
	TOOLKIT_API SECACtrlItem(SECScriptHostDoc* pContainer, const CString &strNameInScrpt, const CRect *initialRect=NULL);
	TOOLKIT_API ~SECACtrlItem();

	TOOLKIT_API static CLIPFORMAT	m_cfOleControl;

	inline CString GetItemName() { return m_strNameInScrpt; }
	CPoint m_ptPos;				//position in document
	TOOLKIT_API CSize GetSize();			//current size
	TOOLKIT_API void SetSize(CSize size);
	TOOLKIT_API CSize GetBaseSize();		//base size
	TOOLKIT_API void SetBaseSize(CSize size);
	inline CRect GetRect() { return CRect(m_ptPos, GetSize()); } //current rect
	TOOLKIT_API void SetRect(CRect& rect);

	inline SECScriptHostDoc* GetDocument() { return (SECScriptHostDoc*)COleClientItem::GetDocument(); }
	inline void SetDocument(SECScriptHostDoc *pDoc) { m_pDocument = (COleDocument*)pDoc; }
	inline SECScriptHostView* GetActiveView() { return (SECScriptHostView*)COleClientItem::GetActiveView(); }

    //dragging/pasting
    inline void  SetDraggedRect(const CRect &rect) { m_DraggedRect = rect; }
    inline const CRect &GetDraggedRect() { return m_DraggedRect; } 
	TOOLKIT_API void  AdjustAfterPaste();

// Operations
	TOOLKIT_API void Dirty();

	TOOLKIT_API void Invalidate(CView* pNotThisView = NULL);
	TOOLKIT_API BOOL UpdateExtent();
	TOOLKIT_API void Move(CRect &rc);
	TOOLKIT_API void ResetSize();
	TOOLKIT_API void GetNativeClipboardData(COleDataSource *pDataSource);

	TOOLKIT_API virtual void Serialize(CArchive& ar); // from CObject - public to call directly
	TOOLKIT_API virtual void SerializeSelectedItems(CArchive& ar);

public: //for property browser

	inline CString GetID()	const			    { return m_strNameInScrpt; }
	TOOLKIT_API BOOL	SetID(const CString &id, BOOL fThrowException = TRUE);

	inline BOOL	IsTabStop()	const			{ return m_fTabStop;	}
	inline void	SetTabStop(BOOL fTabStop)   { m_fTabStop = fTabStop;}

	inline int		GetTabIndex()	const		{ return m_nTabIndex;	}
	inline void	SetTabIndex(int idx)		{ m_nTabIndex = idx;	}

	inline BOOL	IsVisible()	const			{ return m_fVisible;	}
	inline void    SetVisible(BOOL vis)		{ m_fVisible = vis;		}

// Overridables
protected:
	TOOLKIT_API virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	TOOLKIT_API virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	TOOLKIT_API virtual void OnActivate();
	TOOLKIT_API virtual COleDataSource* OnGetClipboardData(BOOL bIncludeLink, LPPOINT lpOffset, LPSIZE lpSize);
	TOOLKIT_API virtual void OnDeactivateUI(BOOL bUndoable);

public:
	TOOLKIT_API virtual void OnGetItemPosition(CRect& rPosition);
	TOOLKIT_API virtual void WriteItem(CArchive& ar);
	TOOLKIT_API virtual void WriteItemFlatFixed(CArchive& ar);

protected:
	CSize	m_sizeIcon;			//current size
	CSize	m_sizeContent;		//current size
	CSize	m_sizeIconExtent;		//default size
	CSize	m_sizeContentExtent;	//default size
protected: //for proper control contaiment
	CString m_strNameInScrpt;
	BOOL	m_fTabStop;
	int		m_nTabIndex;
    CRect	m_DraggedRect; //in client coords
	BOOL	m_fVisible;	
	BOOL	m_fInitialSizeSpecified;
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif	// _CCtrlItem_H
