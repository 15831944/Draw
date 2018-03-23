///////////////////////////////////////////////////////////////////////////////
// MvcPrintable.h : SFL Model-View-Controller architecture 
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
// Description:  Default implementation of IPrintable for MVC viewports.
//

#pragma once

#ifndef __MVCPRINTABLE_H__
#define __MVCPRINTABLE_H__

#include <Foundation\Print\Printable.h>
#include <Foundation\StructuredGraphics\LogCoordinates.h>
#include <Foundation\StructuredGraphics\VisualWindow.h>
#include <Foundation\Util\Convert.h>

namespace stingray {
namespace foundation {

/////////////////////////////////////////////////////////////////////
//@doc CMvcPrintable

//@class This class provides an implementation of the IPrintable
// interface for MVC viewports.  It paginates the virtual bounds
// of the viewport from left to right and top to bottom using
// the printer configuration specified in the print document.

template <typename _Base>
class CMvcPrintable : public _Base, public IPrintable
{
// Operations
public:
	//@cmember
	/* Get number of pages in document. */
	virtual int GetPageCount(CPrintDoc* pPrintDoc)
	{
		if (pPrintDoc == NULL)
			return 0;

		CPrinterConfig* pPrinterConfig = pPrintDoc->GetPrinterConfig();
		if (pPrinterConfig == NULL)
			return 0;

		// Calculate the page dimensions
		CSize szPageDimensions(GetPageDimensions(pPrinterConfig));

		// The virtual size is the size of the viewport by default.
		// If the viewport implements ILogCoordinates, then get
		// the virtual size through that interface.
		CSize szVirtual(GetSize());
		ILogCoordinates* pLog = guid_cast<ILogCoordinates*>(this);
		if (pLog != NULL)
		{
			szVirtual = pLog->GetVirtualSize();
		}
		
		// If WYSISWYG is not enabled, then scale the visual component's virtual size to match the printer's resolution.
		if(!pPrintDoc->IsWYSIWYGEnabled())
		{
			HDC hScreenDC = ::GetDC(NULL);	

			int baseDpiX = ::GetDeviceCaps(hScreenDC, LOGPIXELSX);
			int baseDpiY = ::GetDeviceCaps(hScreenDC, LOGPIXELSY);
			int destDpiX = ::GetDeviceCaps(pPrintDoc->GetPrintDC(), LOGPIXELSX);
			int destDpiY = ::GetDeviceCaps(pPrintDoc->GetPrintDC(), LOGPIXELSY);

			szVirtual.cx = static_cast<long>(szVirtual.cx * ((float)baseDpiX / (float)destDpiX));
			szVirtual.cy = static_cast<long>(szVirtual.cy * ((float)baseDpiY / (float)destDpiY));

			::ReleaseDC(NULL, hScreenDC);
		}

		int nPagesAcross = 0;
		int nPagesDown = 0;

		if (szPageDimensions.cx > 0)
		{
			nPagesAcross = szVirtual.cx / szPageDimensions.cx;
			if ((szVirtual.cx % szPageDimensions.cx) > 0)
				nPagesAcross++;
		}

		if (szPageDimensions.cy > 0)
		{
			nPagesDown = szVirtual.cy / szPageDimensions.cy;
			if ((szVirtual.cy % szPageDimensions.cy) > 0)
				nPagesDown++;
		}

		return (nPagesAcross * nPagesDown);
	}

	//@cmember
	/* Prepare to print the next page. */
	virtual bool BeginPage(CPrintDoc* pPrintDoc)
	{
		CDC dc(pPrintDoc->GetOutputDC());
		dc.SetAttribDC(pPrintDoc->GetPrintDC());		
		OnPrepareDC(&dc);

		pPrintDoc->ScaleOutputToScreenResolution();

		return true;
	}

	//@cmember
	/* Print the current page to the print document. */
	virtual bool PrintPage(CPrintDoc* pPrintDoc)
	{
		if (pPrintDoc == NULL)
			return false;

		CPrinterConfig* pPrinterConfig = pPrintDoc->GetPrinterConfig();
		if (pPrinterConfig == NULL)
			return false;

		// Get the output DC from the print document object
		// and prepare it for rendering.
		CDC dc(pPrintDoc->GetOutputDC());
		dc.SetAttribDC(pPrintDoc->GetPrintDC());
	
		// If we are in preview mode, then retain the current viewport origin. Else
		// get the logical bounds of the current page and set the viewport origin to the 
		// top left of the page bounds.
		if(pPrintDoc->GetOutputDC() == pPrintDoc->GetPrintDC())
		{	
			CRect rcPageBounds(GetPageBounds(pPrinterConfig, pPrintDoc->GetCurPage()));
			dc.SetViewportOrg(rcPageBounds.left, rcPageBounds.top);
		}

		// Have the visual object draw the page
		Draw(&dc);

		// Restore the DC
		OnCleanupDC(&dc);

		return true;
	}

	//@cmember
	/* Cleanup after printing a page. */
	virtual bool EndPage(CPrintDoc* pPrintDoc)
	{
		pPrintDoc;
		return true;
	}

	//@cmember
	/* Calculate page dimensions in logical units. */
	virtual CSize GetPageDimensions(CPrinterConfig* pPrinterConfig)
	{
		CSize szPageDimensions(0,0);

		// Get the paper width and length and printer margins
		// from the printer configuration.
		CSize szPaper;
		CRect rcPrinterMargin;
		pPrinterConfig->GetPaperMeasurements(szPaper);
		pPrinterConfig->GetPrinterMargins(rcPrinterMargin);
		CSize szPrinterMargin(rcPrinterMargin.left + rcPrinterMargin.right,
					          rcPrinterMargin.top + rcPrinterMargin.bottom);

		// NOT YET IMPLEMENTED - Page margin is for document specific
		// page settings. 
		CSize szPageMargin(0,0);

		// Calculate page dimensions in MM_LOMETRIC
		szPageDimensions.cx = szPaper.cx - szPageMargin.cx - szPrinterMargin.cx;
		szPageDimensions.cy = szPaper.cy - szPageMargin.cy - szPrinterMargin.cy;

		if (szPageDimensions.cx > 0 && szPageDimensions.cy > 0)
		{
			// Convert from MM_LOMETRIC into logical units
			// for this viewport
			CDC dc;
			HWND hWnd = NULL;
			IVisualWindow* pVisualWnd = guid_cast<IVisualWindow*>(this);
			if (pVisualWnd != NULL)
			{
				hWnd = pVisualWnd->GetWindowHandle();
			}
			dc.Attach(::GetDC(hWnd));
			OnPrepareDC(&dc);
			Convert::LPtoLP(dc, MM_LOMETRIC, szPageDimensions);
			::ReleaseDC(hWnd, dc.Detach());
		}

		return szPageDimensions;
	}

	//@cmember
	/* Calculate the bounds of a given page in logical units. */
	virtual CRect GetPageBounds(CPrinterConfig* pPrinterConfig, const int nPageNo)
	{
		CRect rcPageBounds(0,0,0,0);

		int nCol = 0;
		int nRow = 0;
		CSize szPageDimensions(GetPageDimensions(pPrinterConfig));
		CSize szVirtual(GetSize());

		ILogCoordinates* pLog = guid_cast<ILogCoordinates*>(this);
		if (pLog != NULL)
		{
			szVirtual = pLog->GetVirtualSize();
		}

		if (szPageDimensions.cx > 0 && szPageDimensions.cy > 0)
		{
			int nPageIdx = nPageNo - 1;
			ASSERT(nPageIdx >= 0);

			int nPagesAcross = szVirtual.cx / szPageDimensions.cx;
			if ((szVirtual.cx % szPageDimensions.cx) > 0)
				nPagesAcross++;

			if (nPagesAcross != 0)
			{
				nRow = nPageIdx / nPagesAcross;
				nCol = nPageIdx % nPagesAcross;
			}
		}

		rcPageBounds.left = nCol * szPageDimensions.cx;
		rcPageBounds.top = nRow * szPageDimensions.cy;
		rcPageBounds.right = (nCol + 1) * szPageDimensions.cx;
		rcPageBounds.bottom = (nRow + 1) * szPageDimensions.cy;

		return rcPageBounds;
	}

	// GUID map implements the QueryGuid() function
	BEGIN_GUID_MAP(CMvcPrintable<_Base>)
		GUID_ENTRY(IPrintable)
		GUID_CHAIN_ENTRY(_Base)
	END_GUID_MAP
};

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __MVCPRINTABLE_H__
