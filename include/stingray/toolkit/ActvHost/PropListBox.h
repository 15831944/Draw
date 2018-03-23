///////////////////////////////////////////////////////////////////////////////
// PropListBox.h
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
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//


#ifndef _PROP_LIST
#define _PROP_LIST

/////////////////////////////////////////////////////////////////////////////
// SECAPropList window

#include <afxtempl.h>

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

class SECAPropList : public CListBox
{
public:
	TOOLKIT_API SECAPropList();

private:
    CListBox m_wndList;
    CFont m_font, m_font_bold;
    int m_iFontHeight;
    int m_iFontWidth;

	struct ListData
	{
	   CString strLeft;
	   CString strRight;
	   CString strSortName; //usually left ""
	   DWORD   dwData;
	};

	CArray < ListData, ListData& > m_Data;

public:

	TOOLKIT_API void AddString( const CString &strLeft, const CString &strRight, const DWORD &prop_index, const CString *pSortName = NULL );
	TOOLKIT_API void ModifyStringItem( int nIndex, const CString &strLeft, const CString &strRight );
	TOOLKIT_API BOOL GetValue ( int nIndex, CString &strRight );
	TOOLKIT_API int	 GetSelectedPropIndex( int &nSelectedItem );
	TOOLKIT_API int	 GetPropIndexFromLBindex( int nIndex );
	TOOLKIT_API void ResetContent();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECAPropList)
	public:
	TOOLKIT_API virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	TOOLKIT_API virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	TOOLKIT_API virtual ~SECAPropList();

	// Generated message map functions
protected:
	//{{AFX_MSG(SECAPropList)
	//}}AFX_MSG

	TOOLKIT_DECLARE_MESSAGE_MAP()

TOOLKIT_API 	void SortDataArray();
	BOOL m_fNeedsSorting;
	int  m_cachedHeight;
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

/////////////////////////////////////////////////////////////////////////////
#endif
