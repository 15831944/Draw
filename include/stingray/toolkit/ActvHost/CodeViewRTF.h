///////////////////////////////////////////////////////////////////////////////
// CodeView.h
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

#ifndef __SECACODEVIEWRTF_H_
#define __SECACODEVIEWRTF_H_

#include <afxrich.h>
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

/////////////////////////////////////////////////////////////////////////////
// SECACodeViewRTF view

#ifndef sec_charformat
	#if ( _MFC_VER >= 0x0700 )
		#define sec_charformat CHARFORMAT2	
/*		#ifdef _UNICODE
			#define sec_charformat CHARFORMAT2W
		#else //!_UNICODE
			#define sec_charformat CHARFORMAT2A
		#endif //_UNICODE
*/
	#else
		#if ( _MFC_VER < 0x0421 )
			#ifdef _UNICODE
				#define sec_charformat _charformatw
			#else //!_UNICODE
				#define sec_charformat _charformat
			#endif //_UNICODE
		#else  // _MFC_VER >= 0x0421
			#define sec_charformat _charformat
		#endif // _MFC_VER < 0x0421
	#endif //_MFC_VER >= 0x0700
#endif

#define SEC_CHARFORMATSIZE	(sizeof(sec_charformat))

class SECScriptHostDoc;

struct SECACharFormat : public sec_charformat
{
	inline SECACharFormat() {cbSize = SEC_CHARFORMATSIZE;}
	//BOOL operator==(SECACharFormat& cf);
};

class SECACodeViewRTF : public CRichEditView
{
protected:
	TOOLKIT_API SECACodeViewRTF();
	TOOLKIT_DECLARE_DYNCREATE(SECACodeViewRTF)

public:

	TOOLKIT_API SECScriptHostDoc* GetDocument() const;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECACodeViewRTF)
public:
	TOOLKIT_API virtual void OnInitialUpdate();
protected:
	TOOLKIT_API virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	TOOLKIT_API virtual ~SECACodeViewRTF();
#ifdef _DEBUG
	TOOLKIT_API virtual void AssertValid() const;
	TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
#endif

	//in/out serialization
	TOOLKIT_API void		StreamCode(CArchive& ar, BOOL bSelection);

	//font and color formatting
	TOOLKIT_API void		GetDefaultFont(SECACharFormat& cf);
	TOOLKIT_API void		SetDefaultFont(BOOL bText);

	SECACharFormat m_defCharFormat;
	SECACharFormat m_defTextCharFormat;

	//helpers
	TOOLKIT_API long CurrentLine(long &nThisLineCharIndex);
	TOOLKIT_API void ColorRange (long nStartChar, long nEndChar, COLORREF color );
	TOOLKIT_API afx_msg LRESULT DoColor( WPARAM, LPARAM );

protected:
	//{{AFX_MSG(SECACodeViewRTF)
	TOOLKIT_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	TOOLKIT_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif		// __SECACODEVIEWRTF_H_

/////////////////////////////////////////////////////////////////////////////
