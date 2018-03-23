///////////////////////////////////////////////////////////////////////////////
// PropBrowser.h
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
// UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef __SECPROPBROWSER_H_
#define __SECPROPBROWSER_H_

#include "toolkit\ActvHost\PropListBox.h"
#include "toolkit\ActvHost\PropList.h"
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

#define CONT_PROP_BASE		30000

// Forward declaration
class SECACtrlItem;

/////////////////////////////////////////////////////////////////////////////
// SECAPropBrowser dialog

class SECAPropBrowser : public CDialog
{
public:
	TOOLKIT_API SECAPropBrowser(CWnd* pParent, SECACtrlItem *pRectItem);
	TOOLKIT_API virtual ~SECAPropBrowser();

	//{{AFX_DATA(SECAPropBrowser)
	enum { IDD = SECAH_IDD_PropertiesDlg };
	CComboBox	m_EnumItems;
	SECAPropList	m_PropList;
	//}}AFX_DATA

	TOOLKIT_API static CString StringFromColor( COLORREF color );

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECAPropBrowser)
	protected:
	TOOLKIT_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	enum refreshType { Rfr_Cancel,
					   Rfr_RefreshThisItem,
					   Rfr_RefreshAll,
					   Rfr_NoOptions };

	TOOLKIT_API int		RefreshListItem	  ( int   nPropIndex = Rfr_RefreshAll );
	TOOLKIT_API CString	GetPropStringValue( const SECABrowseProp &bp, long &usrDefIndex  ); //a value of some property and maybe an index of a user type
	TOOLKIT_API CString	GetStockPropValue ( const SECABrowseProp &bp, long &usrDefIndex  ); //a value of some stock property
	TOOLKIT_API CString	GetOleColorString ( const OLE_COLOR &usrDefColor );
	TOOLKIT_API CString	FormatEnumItem	  ( const SECA_EnumType, const CString &strUserDefined );

	TOOLKIT_API void SetupEditArea( const SECABrowseProp &bp, const CString &strValue ); // sets up either an edit box or a combo
	TOOLKIT_API BOOL IsEditable( const SECABrowseProp &bp );                             // can we press [...] ?
	TOOLKIT_API refreshType EditStockProperty( const SECABrowseProp &bp );
	TOOLKIT_API BOOL LoadUserDefinedPicture( CPictureHolder &NewPictureHolder );         // FALSE if failed
	TOOLKIT_API BOOL LoadUserDefinedIcon( CPictureHolder &NewIconHolder	 ); 	         // FALSE if failed		

	//container properties
	TOOLKIT_API void AddContainerProperties( SECAPropList &PropList )	const;
	TOOLKIT_API CString GetContPropStringValue( int propID, CString &strPropName, VARTYPE &vt)const;
	TOOLKIT_API void ApplyContainerProperty( int propID, int nComboIsSource );

protected:
	SECACtrlItem *m_pRectItem;
	LPDISPATCH    m_pItemDisp;
	BOOL		  m_fPropModified;
	PROPARRAY     m_BrowsedProperties;

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

#endif 		// __SECPROPBROWSER_H_
