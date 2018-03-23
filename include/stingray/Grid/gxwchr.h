///////////////////////////////////////////////////////////////////////////////
// gxwchr.h : Interface of the CGXWChar class
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
// Author: Daniel Jebaraj
//

#ifndef _GX_W_CHR_H__
#define _GX_W_CHR_H__

// #include <StingrayExportDefs.h>

// simple helper class for wide characters
class CGXWChar
{
public:
// construction
	GRID_API CGXWChar();
	
	GRID_API CGXWChar(char* psz, UINT uiPage = CP_ACP, DWORD dwFlags = 0);
	
	GRID_API CGXWChar(WCHAR* pszW, UINT uiPage = CP_ACP, DWORD dwFlags = 0);
	
	GRID_API virtual ~CGXWChar();
	
// access interface
	GRID_API const WCHAR* GetWChar();
	
	// you must take care to realloc and then call SetWChar when you call this
	// call Detach if you do not want to do this
	GRID_API WCHAR* GetWCharRef();
	
	GRID_API void Attach(WCHAR* pszW);
	GRID_API WCHAR* Detach();
	
	// access
	GRID_API void SetWChar(const WCHAR* pszW);
	GRID_API void SetChar(const char* psz);

	GRID_API UINT GetCodePage() const;
	GRID_API void SetCodePage(UINT uiPage);

	GRID_API DWORD GetFlags() const;
	GRID_API void SetFlags(DWORD dwFlags);
	
// static helpers
	// They use defaults for member data
	GRID_API static WCHAR* ConvertDef(const char* psz);
	GRID_API static void FreeAllocData(WCHAR*& pszW);
	
protected:
// helpers
	GRID_API static void ReportError();

	GRID_API WCHAR* Convert(const char* psz);
	GRID_API WCHAR* Clone(const WCHAR* pszW);
	
	GRID_API void Free();

// data
	WCHAR*	m_pszWChar;
	
	// code page
	UINT	m_uiPage;
	
	// flags
	DWORD	m_dwFlags;
};

#endif //_GX_W_CHR_H__
