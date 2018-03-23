///////////////////////////////////////////////////////////////////////////////
// PrintPreviewModel.h : Print preview model class.
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
// Author:       Jeff Boenig
// Description:  Print preview model class.
//

#pragma once

#include <Foundation\MVC\MvcModel.h>
#include <Foundation\Print\Printable.h>
#include <Foundation\Print\PrintDoc.h>
#include <Foundation\Util\Convert.h>
#include <Foundation\Debug.h>

namespace stingray {
namespace foundation {

//////////////////////////////////////////////////////////////////////////
//@doc CPrtPreviewModel

//@class This class implements the print preview model. It derives from
// IPrintJobImpl and contains a pointer to the IPrintable interface of the
// object that is being printed.


class FOUNDATION_API CPrtPreviewModel : public CMvcModel
{
// Constructors/destructor
public:
	CPrtPreviewModel(CPrinterConfig* pPrinterConfig = NULL) :
		m_pPrintDoc(NULL),
		m_pIPrintable(NULL),
		m_nFirstVisiblePage(1),
		m_nNumVisiblePages(1)
	{
		// To get rid of warning...
		pPrinterConfig;
	}

// Attributes
protected:
	IPrintable* m_pIPrintable;
	CPrintDoc* m_pPrintDoc;
	int m_nFirstVisiblePage;
	int m_nNumVisiblePages;

// Operations
public:

	//@cmember
	/* Get a pointer to the print document object. */
	CPrintDoc* GetPrintDoc()
	{
		return m_pPrintDoc;
	}

	//@cmember
	/* Get a pointer to the object being printed. */
	virtual IPrintable* GetPrintable()
	{
		return m_pIPrintable;
	}

	//@cmember
	/* Return the number of pages currently visible. */
	int GetNumVisiblePages() const
	{
		return m_nNumVisiblePages;
	}

	//@cmember
	/* Set the number of pages currently visible. */
	void SetNumVisiblePages(const int nNumVisiblePages)
	{
		m_nNumVisiblePages = nNumVisiblePages;
	}

	//@cmember
	/* Return the page number of the first page currently visible. */
	int GetFirstVisiblePage() const
	{
		return m_nFirstVisiblePage;
	}

	//@cmember
	/* Set the page number of the first page currently visible. */
	void SetFirstVisiblePage(const int nFirstVisiblePage)
	{
		m_nFirstVisiblePage = nFirstVisiblePage;
	}

	//@cmember
	/* Preview the next page. */
	virtual void GotoNextPage()
	{
		m_nFirstVisiblePage++;
		UpdateAllObservers(NULL, NULL);
	}

	//@cmember
	/* Preview the next page. */
	virtual void GotoPrevPage()
	{
		m_nFirstVisiblePage--;
		UpdateAllObservers(NULL, NULL);
	}

	//@cmember
	/* Return the print preview background color. */
	virtual COLORREF GetBackgroundColor()
	{
		return RGB(97,97,97);  // gray
	}

	//@cmember
	/* Return the print preview page color. */
	virtual COLORREF GetPageColor()
	{
		return RGB(255,255,255);  // white
	}

	//@cmember
	/* Start the print job. */
	virtual bool Start(IPrintable* pIPrintable, CPrintDoc* pPrintDoc)
	{
		bool bSuccess = false;

		m_pIPrintable = pIPrintable;
		m_pPrintDoc = pPrintDoc;

		if (m_pPrintDoc != NULL)
		{
			CPrinterConfig* pPrinterConfig = m_pPrintDoc->GetPrinterConfig();

			if (pPrinterConfig != NULL)
			{
				HDC hPrintDC = pPrinterConfig->CreateDC();
				if (hPrintDC != NULL)
				{
					m_pPrintDoc->SetPrintDC(hPrintDC);
					UpdateAllObservers(NULL, NULL);
					bSuccess = true;
				}
			}
		}

		return bSuccess;
	}
};

}; // namespace stingray::foundation
}; // namespace stingray

