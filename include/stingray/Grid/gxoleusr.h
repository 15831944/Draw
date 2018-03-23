///////////////////////////////////////////////////////////////////////////////
// gxoleusr.h
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
// Author: Stefan Hoenig, Daniel Jebaraj
//

#ifndef _GX_OLEVARIANT_USER_H__
#define _GX_OLEVARIANT_USER_H__

#if _MFC_VER >= 0x0400

#include "gxman.h"
// #include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

class CGXOleVarUserAttribute: public CGXAbstractUserAttribute
{
	GRID_DECLARE_SERIAL(CGXOleVarUserAttribute);

public:
	GRID_API CGXOleVarUserAttribute();
	GRID_API CGXOleVarUserAttribute(const COleVariant& var);

	GRID_API virtual ~CGXOleVarUserAttribute();

	// Change value, update the grid, generate undo info
	GRID_API virtual CGXAbstractUserAttribute& SetValue(const CString& strValue);
	GRID_API virtual CGXAbstractUserAttribute& SetValue(LPCTSTR pszValue);

	GRID_API virtual const CString& GetValue() const;

	GRID_API CGXOleVarUserAttribute& SetOleVarValue(const COleVariant& var);

	GRID_API const COleVariant* GetOleVarValue() const;

	// Copying attribute (e.g. from one style object to another)
	GRID_API virtual CGXAbstractUserAttribute* Clone() const;

	GRID_API virtual void Serialize(CArchive& ar);

	// Comparision
	GRID_API virtual BOOL IsEqual(const CGXOleVarUserAttribute& p) const; // (TRUE if equal)

	GRID_API operator LPCTSTR() const;
	
	GRID_API virtual BOOL IsEmpty() const;

public:
	static CGXCaptiveManager<COleVariant> g_VarCreator;
	COleVariant* m_pOleVar;
	// special flag that is useful when updating the browser grid
	BOOL m_bModifyState;
};

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif //#if _MFC_VER >= 0x0400

#endif //_GX_OLEVARIANT_USER_H__
