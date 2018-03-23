///////////////////////////////////////////////////////////////////////////////
// ContainerProps.h
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

#ifndef _CONT_PROPERTIES_H
#define _CONT_PROPERTIES_H
#include "toolkit\ActvHost\PropListBox.h"
#include "toolkit\ActvHost\ahostres.h"
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

class SECScriptHostView;
class SECALangAwareObj;

#ifdef GetWindowStyle
#undef GetWindowStyle
#endif

/////////////////////////////////////////////////////////////////////////
enum { Border_Resizable, Border_Thin };
/////////////////////////////////////////////////////////////////////////
//available container properties
/////////////////////////////////////////////////////////////////////////
enum { cpID, cpColor, cpWidth, cpHeight, cpTitle, cpBorderStyle, cpMinimize, cpMaximize, cpWndRestoreType, cpActiveEngine };
/////////////////////////////////////////////////////////////////////////

class SECAContBrowser;

class SECAContainerProps : public CObject
{
	friend SECAContBrowser; //the only class that can modify this object
	TOOLKIT_DECLARE_SERIAL( SECAContainerProps )
	TOOLKIT_API SECAContainerProps(); //ctor for de-serialization

public:
	inline const CSize	  &GetFormSize()     { return m_Size;		  }
	inline void  SetFormSize(const CSize& size) { m_Size=size; }
	inline const CString &GetInitialTitle() { return m_initialTitle; }
	inline void  SetTitle(LPCTSTR title)	 { m_initialTitle = title; }
	inline const BOOL TitleChangedByUser()	 { return m_fTitleChangedByUser; }
	inline const CString &GetNameInScript() { return m_nameInScript; }
	inline COLORREF	   GetColor()		 { return m_color;		  }
	TOOLKIT_API DWORD		   GetWindowStyle();
	TOOLKIT_API void 		   ModifyWindowStyle(DWORD& dwStyle);
	inline void		   SetWindowPlacement( WINDOWPLACEMENT wp ) { m_wp = wp; }
	inline const WINDOWPLACEMENT &GetWindowPlacement() { return m_wp; }
	inline BOOL		   NeedToRestoreWinPos() { return m_fRestoreWinPos; }
	TOOLKIT_API BOOL		   CanRestoreWinPos();
	TOOLKIT_API CString		   StyleFromIndex( int nStyleIndex );
	TOOLKIT_API virtual CLSID  GetActiveEngineCLSID();

	//language specific stuff like function decalarations and syntax via this object
	TOOLKIT_API virtual SECALangAwareObj* CreateLangAwareObject(); //called must delete returning pointer when no longer needed.
												   	  //can be NULL if active language is not supported.
	//methods
	TOOLKIT_API void Serialize(CArchive& ar);
	TOOLKIT_API void ResetToDefault();

protected:
	TOOLKIT_API void ReadWindowPlacement (CArchive& ar);
	TOOLKIT_API void WriteWindowPlacement(CArchive& ar);

protected:
	WORD	 m_wSchema; //MFC's versionable schema is not used
	CString  m_initialTitle;
	BOOL	 m_fTitleChangedByUser;	// User has explicitly modified title
	CString  m_nameInScript;		//same as ID
	COLORREF m_color;
	CSize	 m_Size;
	//window position
	WINDOWPLACEMENT	m_wp;
	BOOL	 m_fRestoreWinPos;
	//window styles
	DWORD	 m_dwWindowStyle;	//not displayed
	WORD	 m_borderStyle;
	WORD	 m_wMin;
	WORD	 m_wMax;
	//active language used
	CString  m_strLangClassID;
	CString  m_strLangName;
};


/////////////////container properties dialog//////////////////////

class SECAContBrowser : public CDialog
{
public:
	TOOLKIT_API SECAContBrowser(SECAContainerProps &contProps, SECScriptHostView *pView);
	TOOLKIT_API ~SECAContBrowser();

	//{{AFX_DATA(SECAPropBrowser)
	enum { IDD = SECAH_IDD_PropertiesDlg };
	CComboBox	m_EnumItems;
	SECAPropList	m_PropList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECAPropBrowser)
protected:
	TOOLKIT_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	TOOLKIT_API int	RefreshListItem	  ( int   nPropIndex = 0 );

protected:
	SECAContainerProps &	m_contProps;
	BOOL					m_fPropModified;
	SECScriptHostView*		m_pScriptHostView;
	TOOLKIT_API void		OnApplyProperty(BOOL fRefresh);
	//active scripts
	TOOLKIT_API BOOL	  ObtainActiveEngineList();
	TOOLKIT_API CString	  LangNameFromIndex(int index);
	TOOLKIT_API CString	  CLSIDFromIndex   (int index);
	CArray <CString, CString&> m_activeEnginesCLSIDs;
	CArray <CString, CString&> m_activeEnginesNames;

	// Generated message map functions
	//{{AFX_MSG(SECAPropBrowser)
	TOOLKIT_API virtual BOOL OnInitDialog();
	TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
	TOOLKIT_API afx_msg void OnEditStockProp();
	TOOLKIT_API afx_msg void OnPropListChangedSelection();
	TOOLKIT_API afx_msg void OnApplyProperty();
	TOOLKIT_API afx_msg void OnEntryBoxModified();
	TOOLKIT_API afx_msg void OnEntryBoxLostFocus();
	TOOLKIT_API afx_msg void OnEnumItemsChangedSelection();
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
	
	TOOLKIT_API void SizeContents();
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif
