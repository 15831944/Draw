///////////////////////////////////////////////////////////////////////////////
// OCutItem.h: interface for the OCutItem class.
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

#if !defined(AFX_OCUTITEM_H__62F41647_AD27_11D1_B2AA_006008AFBC41__INCLUDED_)
#define AFX_OCUTITEM_H__62F41647_AD27_11D1_B2AA_006008AFBC41__INCLUDED_

#ifdef _OBJCHART_UT_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OCUT_DATA
#endif

#include <StingrayExportDefs.h>

class OCutItem  
{
public:
	CHART_UT_API virtual SRGraph * GetGraph();
	CHART_UT_API virtual void Paint(CDC *pDC,CWnd *pWnd, CRect r=CRect(0,0,0,0));
	CHART_UT_API virtual void ClearData();
	CHART_UT_API virtual void ClearComponents();
	virtual void Clear() = 0;
	virtual void InitializeData() = 0;
	virtual void SetupComponents() = 0;
	CHART_UT_API OCutItem();
	CHART_UT_API virtual ~OCutItem();

protected:
	SRGraph m_Graph;
};

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif // !defined(AFX_OCUTITEM_H__62F41647_AD27_11D1_B2AA_006008AFBC41__INCLUDED_)
