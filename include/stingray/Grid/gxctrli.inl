///////////////////////////////////////////////////////////////////////////////
// gxctrli.inl
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
// Author: Stefan Hoenig
//

#pragma once

#ifdef GX_INLINE

GX_INLINE void CGXEditControl::GetSel(int& nStartChar, int& nEndChar) const
	{ ASSERT(::IsWindow(m_hWnd)); DWORD dw = (DWORD)::SendMessage(m_hWnd, EM_GETSEL, 0, 0); nStartChar = LOWORD(dw); nEndChar = HIWORD(dw); }

GX_INLINE DWORD CGXEditControl::GetSel() const
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD)::SendMessage(m_hWnd, EM_GETSEL, 0, 0); }

GX_INLINE CListBox& CGXGridCombo::GetLBox()
	{ return *((CListBox*) m_pListBox); }

GX_INLINE void CGXComboListBox::SetBackColor(COLORREF rgb)
	{ m_bColor = TRUE; m_rgbBack = rgb; }

GX_INLINE int CGXComboBoxWnd::GetWindowText(LPTSTR lpszStringBuf, int nMaxCount) const
	{ return CComboBox::GetWindowText(lpszStringBuf, nMaxCount); }

GX_INLINE const CString& CGXMaskData::GetPromptChar() const
	{ return m_sPrompt; }

GX_INLINE BOOL CGXMaskData::IsEmptyMask() const
	{ return m_astrMask.GetSize() == 0; }

GX_INLINE int CGXMaskData::GetTextLength() const
	{ return (int)m_astrDisplay.GetSize(); }

GX_INLINE void CGXMaskData::SetMaxLength(int nLength)
	{ m_nMaxLength = nLength; }

GX_INLINE int CGXMaskData::SetMaxLength() const
	{ return m_nMaxLength; }

GX_INLINE void CGXMaskControl::GetSel(int& nStartChar, int& nEndChar) const
	{ ASSERT(::IsWindow(m_hWnd)); DWORD dw = (DWORD)::SendMessage(m_hWnd, EM_GETSEL, 0, 0); nStartChar = LOWORD(dw); nEndChar = HIWORD(dw); }

GX_INLINE DWORD CGXMaskControl::GetSel() const
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD)::SendMessage(m_hWnd, EM_GETSEL, 0, 0); }


#if _MFC_VER >= 0x0400

GX_INLINE void CGXCheckListComboLBox::SetBackColor(COLORREF rgb)
	{ m_bColor = TRUE; m_rgbBack = rgb; }

#endif

#endif // GX_INLINE

