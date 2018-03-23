///////////////////////////////////////////////////////////////////////////////
// PageSettings.h : SFL Print Preview package 
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

#pragma once

#if !defined(_SFL)
#define _SFL
#endif

#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

//////////////////////////////////////////////////////////////////////////
// CPageLayout

class FOUNDATION_API CPageLayout
{
// Constructors/destructor
public:
	CPageLayout()
	{
		m_nFromPage = 0;
		m_nToPage = 0;
		m_rcMargins.left = 0;
		m_rcMargins.top = 0;
		m_rcMargins.right = 0;
		m_rcMargins.bottom = 0;
	}

// Attributes
protected:
	int m_nFromPage;
	int m_nToPage;
	RECT m_rcMargins;

// Operations
public:
	int GetFromPage() const
	{
		return m_nFromPage;
	}

	int GetToPage() const
	{
		return m_nToPage;
	}

	RECT& GetMargins()
	{
		return m_rcMargins;
	}
};

//////////////////////////////////////////////////////////////////////////
// CPageSettings

template <class _PageLayout = CPageLayout>
class CPageSettingsBase
{
// Embedded types
public:
	typedef _PageLayout PageLayoutClass;

// Constructors/destructor
public:
	CPageSettingsBase() :
		m_nFromPage(-1),
		m_nToPage(-1)
	{
	}

// Attributes
protected:
	int m_nFromPage;
	int m_nToPage;

// Operations
public:
	virtual void LoadPageSetupDlg(PAGESETUPDLG& psd)
	{
		// to get rid of the warnings
		psd;
	}

	virtual void StorePageSetupDlg(const PAGESETUPDLG& psd)
	{
		// to get rid of the warnings
		psd;
	}

	int GetFromPage() const
	{
		return m_nFromPage;
	}

	int GetToPage() const
	{
		return m_nToPage;
	}

	virtual PageLayoutClass* GetPageLayout(const int nPageNo) = 0;
};

//////////////////////////////////////////////////////////////////////////
// CPageSettings

class FOUNDATION_API CPageSettings : public CPageSettingsBase<CPageLayout>
{
// Constructors/destructor
public:
	CPageSettings()
	{
	}

// Attributes
protected:
	CPageLayout m_pageLayout;

// Operations
public:
	CPageLayout* GetPageLayout(const int nPageNo)
	{
		nPageNo;
		return &m_pageLayout;
	}
};

};	// namespace stingray::foundation
};	// namespace stingray
