///////////////////////////////////////////////////////////////////////////////
// PrinterConfig.h : SFL Print Preview package 
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

#include <commdlg.h>
#include <winspool.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

//////////////////////////////////////////////////////////////////////////
// CPrinterConfig

//@doc CPrinterConfig
//@class The CPrinterConfig class encapsulates the Windows DEVNAMES and DEVMODE structures used by printing systems for
// identifying and configuring printers. CPrinterConfig takes care of the messy details involved in allocating and manipulating
// these variable length structures and provides convenient accessors and methods that allow you to work with them.
// All physical measurements are in units of 0.1mm (MM_LOMETRIC).
//
// NOTE: CPrinterConfig is an abstract class and cannot be directly instantiated. For configuring the printer, you must use 
// the <c CPrinterConfigImpl> template class. 
// 
//@xref <c IPrintable>
//@xref <c CPrintDoc>
//@xref <c CPrintJob>
//@xref <c CPrintPreviewFrameImpl>	
class CPrinterConfig
{
public:
	//@cmember
	/* Returns a handle to the DEVNAMES structure.*/
	virtual HGLOBAL GetDevNames() const = 0;
	//@cmember
	/* Sets the DEVNAMES structure.*/
	virtual void SetDevNames(const HGLOBAL hSrcDevNames) = 0;
	//@cmember
	/* Returns a handle to the DEVMODE structure.*/
	virtual HGLOBAL GetDevMode() const = 0;
	//@cmember
	/* Sets the DEVMODE structure.*/
	virtual void SetDevMode(const HGLOBAL hSrcDevMode) = 0;

	//@cmember
	/* Creates a device context using the information specified in the DEVNAMES and DEVMODE structures.*/
	inline virtual HDC CreateDC() const;
	//@cmember
	/* Updates the PRINTDLG parameter with the DEVNAMES and DEVMODE information stored in CPrinterConfig.*/
	inline virtual void LoadPrintDlg(PRINTDLG& printDlg);
	//@cmember
	/* Updates CPrinterConfig's DEVNAMES and DEVMODE members with the global memory handles specified in the PRINTDLG parameter.*/
	inline virtual void StorePrintDlg(const PRINTDLG& printDlg);
	//@cmember
	/* Updates the PAGESETUPDLG parameter with the DEVNAMES and DEVMODE handles stored in CPrinterConfig.*/
	inline virtual void LoadPageSetupDlg(PAGESETUPDLG& psd);
	//@cmember
	/* Updates CPrinterConfig's DEVNAMES and DEVMODE members with the handle information specified in the PAGESETUPDLG parameter.*/
	inline virtual void StorePageSetupDlg(const PAGESETUPDLG& psd);

	//@cmember
	/* Returns a pointer to a null-terminated string that contains the device driver file name specified in CPrintConfig's DEVNAMES member.*/
	inline LPTSTR GetDriverName() const;
	//@cmember
	/* Returns a pointer to a null-terminated string that contains the device name specified in CPrintConfig's DEVNAMES member.*/
	inline LPTSTR GetDeviceName() const;
	//@cmember
	/* Returns a pointer to a null-terminated string that contains the device name for the physical output medium.*/
	inline LPTSTR GetOutputName() const;

	//@cmember
	/* Sets CPrinterConfig's DEVNAMES and DEVMODE members to handles that have been initialized for the system default printer.*/  
	inline void SetDefaultPrinter();
	//@cmember
	/* Returns TRUE if the information specified in CPrinterConfig accurately identifies an existing printer. Else FALSE.*/
	inline bool PrinterExists() const;

	//@cmember
	/* Returns the paper orientation specified in the DEVMODE structure. Valid return values are DMORIENT_PORTRAIT and DMORIENT_LANDSCAPE.*/
	inline short GetOrientation() const;
	//@cmember
	/* Sets the printer's paper orientation. This can be either DMORIENT_PORTRAIT or DMORIENT_LANDSCAPE.*/
	inline void SetOrientation(const short nOrientation);

	//@cmember
	/* Returns the paper size specified in CPrinterConfig's DEVMODE structure. For information on paper sizes, please refer to the Win32 documentation on the DEVMODE structure.*/
	inline short GetPaperSize() const;
	//@cmember
	/* Sets the printer's paper size. For information on paper sizes, please refer to the Win32 documentation on the DEVMODE structure.*/
	inline void SetPaperSize(const short nPaperSize);

	//@cmember
	/* Returns the paper length specified in the DEVMODE structure's dmPaperLength member.*/
	inline short GetPaperLength() const;
	//@cmember
	/* Sets the dmPaperLength member in CPrinterConfig's DEVMODE structure.*/
	inline void SetPaperLength(const short nPaperLength);

	//@cmember
	/* Returns the paper width specified in the DEVMODE structure's dmPaperWidth member.*/
	inline short GetPaperWidth() const;
	//@cmember
	/* Sets the dmPaperWidth member in CPrinterConfig's DEVMODE structure.*/
	inline void SetPaperWidth(const short nPaperWidth);

	//@cmember
	/* Returns the number of copies specified in CPrinterConfig's DEVMODE member.*/
	inline short GetNumCopies() const;
	//@cmember
	/* Sets the number of copies, dmCopies, in CPrinterConfig's DEVMODE structure.*/
	inline void SetNumCopies(const short nNumCopies);

	//@cmember
	/* Retrieves the logical coordinates identifying the physical page's printable area.*/
	inline bool GetPrinterMargins(RECT& rcPrinterMargins);
	//@cmember
	/* Retrieves the paper size specified in CPrinterConfig's DEVMODE member.*/
	inline bool GetPaperMeasurements(SIZE& szPaper);

	inline static int CalcDevNamesSize(LPDEVNAMES lpDevNames);
	inline static HGLOBAL DupDevNames(HGLOBAL hSrcDevNames);
	inline static int CalcDevModeSize(HGLOBAL hDevNames);
	inline static HGLOBAL DupDevMode(HGLOBAL hSrcDevMode);
};




//////////////////////////////////////////////////////////////////////////
// CPrinterConfigImpl

//@doc CPrinterConfigImpl
//@class The CPrinterConfigImpl template class derives from <c CPrinterConfig> and provides the requisite concretization
// of the CPrinterConfig abstract base class.
//@tcarg bool | bOwnsHandles = true | Default value of true assigns CPrinterConfigImpl ownership of the DEVMODE and DEVNAMES global
// memory handles and frees them when the CPrintConfigImpl object destructs.
//@base public | CPrinterConfig
template <bool bOwnsHandles = true>
class CPrinterConfigImpl : public CPrinterConfig
{
// Constructors/destructor
public:
	//@cmember,mfunc
	// Constructs the printer configuration object.
	//@@syntax CPrinterConfigImpl()
	//@@syntax CPrinterConfigImpl(HANDLE hDevMode, HANDLE hDevNames)
	//@@parm HANDLE | hDevMode | DEVMODE handle. 
	//@@parm HANDLE | hDevNames | DEVNAMES handle.
	/* Constructs the printer configuration object.*/
	FOUNDATION_API CPrinterConfigImpl()
	{
		m_hDevMode = NULL;
		m_hDevNames = NULL;
	}

	FOUNDATION_API CPrinterConfigImpl(HANDLE hDevMode, HANDLE hDevNames)
	{
		m_hDevMode = NULL;
		m_hDevNames = NULL;
		SetDevMode(hDevMode);
		SetDevNames(hDevNames);
	}

	FOUNDATION_API virtual ~CPrinterConfigImpl()
	{
		if (bOwnsHandles)
		{
			if (m_hDevNames != NULL)
			{
				::GlobalFree(m_hDevNames);
			}

			if (m_hDevMode != NULL)
			{
				::GlobalFree(m_hDevMode);
			}
		}
	}

// Attributes
protected:
	//@cmember
	/* Handle to the Win32 DEVMODE structure.*/
	HANDLE m_hDevMode;
	//@cmember
	/* Handle to the Win32 DEVNAMES structure.*/
	HANDLE m_hDevNames;

// Operations
public:
	inline virtual HGLOBAL GetDevNames() const
	{
		return m_hDevNames;
	}

	inline virtual void SetDevNames(const HGLOBAL hSrcDevNames)
	{
		if (bOwnsHandles)
		{
			if (m_hDevNames != NULL)
			{
				::GlobalFree(m_hDevNames);
			}
		}

		m_hDevNames = hSrcDevNames;
	}

	inline virtual HGLOBAL GetDevMode() const
	{
		return m_hDevMode;
	}

	inline virtual void SetDevMode(const HGLOBAL hSrcDevMode)
	{
		if (bOwnsHandles)
		{
			if (m_hDevMode != NULL)
			{
				::GlobalFree(m_hDevMode);
			}
		}

		m_hDevMode = hSrcDevMode;
	}
};

/////////////////////////////////////////////////////////////////////////
// CPrinterConfig
void CPrinterConfig::SetDefaultPrinter()
{
	PRINTDLG pd;
	memset(&pd, 0, sizeof(PRINTDLG));
	pd.lStructSize = sizeof(PRINTDLG);
	pd.Flags |= PD_RETURNDEFAULT;
	::PrintDlg(&pd);
	StorePrintDlg(pd);
}

void CPrinterConfig::LoadPrintDlg(PRINTDLG& printDlg)
{
	printDlg.hDevMode = GetDevMode();
	printDlg.hDevNames = GetDevNames();
}

void CPrinterConfig::StorePrintDlg(const PRINTDLG& printDlg)
{
	SetDevMode(DupDevMode(printDlg.hDevMode));
	SetDevNames(DupDevNames(printDlg.hDevNames));
}

void CPrinterConfig::LoadPageSetupDlg(PAGESETUPDLG& psd)
{
	psd.hDevMode = GetDevMode();
	psd.hDevNames = GetDevNames();
}

void CPrinterConfig::StorePageSetupDlg(const PAGESETUPDLG& psd)
{
	SetDevMode(DupDevMode(psd.hDevMode));
	SetDevNames(DupDevNames(psd.hDevNames));
}

LPTSTR CPrinterConfig::GetDriverName() const
{
	LPTSTR pDriverName;
	HANDLE hDevNames = GetDevNames();

	if (hDevNames == NULL)
		return NULL;

	LPDEVNAMES lpDevNames = reinterpret_cast<LPDEVNAMES>(::GlobalLock(hDevNames));

	if (lpDevNames == NULL)
		return NULL;

	pDriverName = _tcsdup((LPCTSTR)lpDevNames + lpDevNames->wDriverOffset);

	::GlobalUnlock(hDevNames);

	return pDriverName;
}

LPTSTR CPrinterConfig::GetDeviceName() const
{
	LPTSTR pDeviceName;
	HANDLE hDevNames = GetDevNames();

	if (hDevNames == NULL)
		return NULL;

	LPDEVNAMES lpDevNames = reinterpret_cast<LPDEVNAMES>(::GlobalLock(hDevNames));

	if (lpDevNames == NULL)
		return NULL;

	pDeviceName = _tcsdup((LPCTSTR)lpDevNames + lpDevNames->wDeviceOffset);

	::GlobalUnlock(hDevNames);

	return pDeviceName;
}

LPTSTR CPrinterConfig::GetOutputName() const
{
	LPTSTR pOutputName;
	HANDLE hDevNames = GetDevNames();

	if (hDevNames == NULL)
		return NULL;

	LPDEVNAMES lpDevNames = reinterpret_cast<LPDEVNAMES>(::GlobalLock(hDevNames));

	if (lpDevNames == NULL)
		return NULL;

	pOutputName = _tcsdup((LPCTSTR)lpDevNames + lpDevNames->wOutputOffset);

	::GlobalUnlock(hDevNames);

	return pOutputName;
}

//@doc CPrinterConfig
//@mfunc Creates a device context using the device driver and device name specified in the DEVNAMES structure. Any device 
// specific initialization data set in the DEVMODE structure is also used.
//@rdesc If successful, a handle to the device context is returned. Else NULL.
//@xref<c CPrinterConfig>
HDC CPrinterConfig::CreateDC() const
{
	HANDLE hDevNames = GetDevNames();
	HANDLE hDevMode = GetDevMode();
	HDC hDC = 0;

	if (hDevNames == NULL)
		return 0;

	LPDEVNAMES lpDevNames = reinterpret_cast<LPDEVNAMES>(::GlobalLock(hDevNames));
	LPDEVMODE  lpDevMode = (hDevMode != NULL) ?
		reinterpret_cast<LPDEVMODE>(::GlobalLock(hDevMode)) : NULL;

	if (lpDevNames == NULL)
		return 0;

	hDC = ::CreateDC((LPCTSTR)lpDevNames + lpDevNames->wDriverOffset,
		(LPCTSTR)lpDevNames + lpDevNames->wDeviceOffset,
		(LPCTSTR)lpDevNames + lpDevNames->wOutputOffset,
		lpDevMode);

	::GlobalUnlock(hDevNames);
	if (hDevMode != NULL)
		::GlobalUnlock(hDevMode);

	return hDC;
}

bool CPrinterConfig::PrinterExists() const
{
	HDC hDC = (const_cast<CPrinterConfig*>(this))->CreateDC();
	if (hDC != NULL)
	{
		::DeleteDC(hDC);
		return true;
	}
	return false;
}

short CPrinterConfig::GetOrientation() const
{
	HANDLE hDevMode = GetDevMode();
	short nOrientation = DMORIENT_PORTRAIT;

	if (hDevMode != NULL)
	{
		LPDEVMODE lpDevMode = reinterpret_cast<LPDEVMODE>(::GlobalLock(hDevMode));
		if (lpDevMode != NULL)
		{
			nOrientation = lpDevMode->dmOrientation;
			::GlobalUnlock(hDevMode);
		}
	}

	return nOrientation;
}

void CPrinterConfig::SetOrientation(const short nOrientation)
{
	HANDLE hDevMode = GetDevMode();
	if (hDevMode != NULL)
	{
		LPDEVMODE lpDevMode = reinterpret_cast<LPDEVMODE>(::GlobalLock(hDevMode));
		if (lpDevMode != NULL)
		{
			lpDevMode->dmOrientation = nOrientation;
			::GlobalUnlock(hDevMode);
		}
	}
}

short CPrinterConfig::GetPaperSize() const
{
	HANDLE hDevMode = GetDevMode();
	short nPaperSize = DMPAPER_LETTER;

	if (hDevMode != NULL)
	{
		LPDEVMODE lpDevMode = reinterpret_cast<LPDEVMODE>(::GlobalLock(hDevMode));
		if (lpDevMode != NULL)
		{
			nPaperSize = lpDevMode->dmPaperSize;
			::GlobalUnlock(hDevMode);
		}
	}

	return nPaperSize;
}

void CPrinterConfig::SetPaperSize(const short nPaperSize)
{
	HANDLE hDevMode = GetDevMode();

	if (hDevMode != NULL)
	{
		LPDEVMODE lpDevMode = reinterpret_cast<LPDEVMODE>(::GlobalLock(hDevMode));
		if (lpDevMode != NULL)
		{
			lpDevMode->dmPaperSize = nPaperSize;
			::GlobalUnlock(hDevMode);
		}
	}
}

short CPrinterConfig::GetPaperLength() const
{
	HANDLE hDevMode = GetDevMode();
	short nPaperLength = 0;

	if (hDevMode != NULL)
	{
		LPDEVMODE lpDevMode = reinterpret_cast<LPDEVMODE>(::GlobalLock(hDevMode));
		if (lpDevMode != NULL)
		{
			nPaperLength = lpDevMode->dmPaperLength;
			::GlobalUnlock(hDevMode);
		}
	}

	return nPaperLength;
}

void CPrinterConfig::SetPaperLength(const short nPaperLength)
{
	HANDLE hDevMode = GetDevMode();

	if (hDevMode != NULL)
	{
		LPDEVMODE lpDevMode = reinterpret_cast<LPDEVMODE>(::GlobalLock(hDevMode));
		if (lpDevMode != NULL)
		{
			lpDevMode->dmPaperLength = nPaperLength;
			::GlobalUnlock(hDevMode);
		}
	}
}

short CPrinterConfig::GetPaperWidth() const
{
	HANDLE hDevMode = GetDevMode();
	short nPaperWidth = 0;

	if (hDevMode != NULL)
	{
		LPDEVMODE lpDevMode = reinterpret_cast<LPDEVMODE>(::GlobalLock(hDevMode));
		if (lpDevMode != NULL)
		{
			nPaperWidth = lpDevMode->dmPaperWidth;
			::GlobalUnlock(hDevMode);
		}
	}

	return nPaperWidth;
}

void CPrinterConfig::SetPaperWidth(const short nPaperWidth)
{
	HANDLE hDevMode = GetDevMode();

	if (hDevMode != NULL)
	{
		LPDEVMODE lpDevMode = reinterpret_cast<LPDEVMODE>(::GlobalLock(hDevMode));
		if (lpDevMode != NULL)
		{
			lpDevMode->dmPaperWidth = nPaperWidth;
			::GlobalUnlock(hDevMode);
		}
	}
}

short CPrinterConfig::GetNumCopies() const
{
	HANDLE hDevMode = GetDevMode();
	short nNumCopies = 1;

	if (hDevMode != NULL)
	{
		LPDEVMODE lpDevMode = reinterpret_cast<LPDEVMODE>(::GlobalLock(hDevMode));
		if (lpDevMode != NULL)
		{
			nNumCopies = lpDevMode->dmCopies;
			::GlobalUnlock(hDevMode);
		}
	}

	return nNumCopies;
}

void CPrinterConfig::SetNumCopies(const short nNumCopies)
{
	HANDLE hDevMode = GetDevMode();

	if (hDevMode != NULL)
	{
		LPDEVMODE lpDevMode = reinterpret_cast<LPDEVMODE>(::GlobalLock(hDevMode));
		if (lpDevMode != NULL)
		{
			lpDevMode->dmCopies = nNumCopies;
			::GlobalUnlock(hDevMode);
		}
	}
}

bool CPrinterConfig::GetPrinterMargins(RECT& rcPrinterMargins)
{
	rcPrinterMargins.left = 0;
	rcPrinterMargins.top = 0;
	rcPrinterMargins.right = 0;
	rcPrinterMargins.bottom = 0;

	CDC dc;
	dc.Attach(CreateDC());

	SIZE szUpperLeft;
	SIZE szLowerRight;

	szUpperLeft.cx = dc.GetDeviceCaps(PHYSICALOFFSETX);
	szUpperLeft.cy = dc.GetDeviceCaps(PHYSICALOFFSETY);

	int nPhysicalWidth = dc.GetDeviceCaps(PHYSICALWIDTH);
	int nHorzRes = dc.GetDeviceCaps(HORZRES);
	int nPhysicalHeight = dc.GetDeviceCaps(PHYSICALHEIGHT);
	int nVertRes = dc.GetDeviceCaps(VERTRES);

	szLowerRight.cx = nPhysicalWidth - nHorzRes - szUpperLeft.cx;
	szLowerRight.cy = nPhysicalHeight - nVertRes - szUpperLeft.cy;

	dc.SetMapMode(MM_LOMETRIC);
	dc.DPtoLP(&szUpperLeft);
	dc.DPtoLP(&szLowerRight);

	rcPrinterMargins.left = szUpperLeft.cx;
	rcPrinterMargins.top = szUpperLeft.cy;
	rcPrinterMargins.right = szLowerRight.cx;
	rcPrinterMargins.bottom = szLowerRight.cy;

	return true;
}

bool CPrinterConfig::GetPaperMeasurements(SIZE& szPaper)
{
	HANDLE hDevMode = GetDevMode();
	bool bSuccess = false;

	if (hDevMode != NULL)
	{
		LPDEVMODE lpDevMode = reinterpret_cast<LPDEVMODE>(::GlobalLock(hDevMode));
		if (lpDevMode != NULL)
		{
			if ((lpDevMode->dmFields & DM_PAPERLENGTH) && (lpDevMode->dmFields & DM_PAPERWIDTH))
			{
				szPaper.cx = lpDevMode->dmPaperWidth;
				szPaper.cy = lpDevMode->dmPaperLength;
				bSuccess = true;
			}
			else if (lpDevMode->dmFields & DM_PAPERSIZE)
			{
				int nWidth = 0;
				int nLength = 0;

				switch(lpDevMode->dmPaperSize)
				{
				case DMPAPER_LETTER: // Letter, 8 1/2 by 11 inches
					nWidth = static_cast<int>(85 * 25.4f);
					nLength = static_cast<int>(110 * 25.4f);
					break;

				case DMPAPER_LEGAL: // Legal, 8 1/2 by 14 inches
					nWidth = static_cast<int>(85 * 25.4f);
					nLength = static_cast<int>(140 * 25.4f);
					break;

				case DMPAPER_A4: // A4 Sheet, 210 by 297 millimeters
					nWidth = 2100;
					nLength = 2970;
					break;

				case DMPAPER_CSHEET: // C Sheet, 17 by 22 inches
					nWidth = static_cast<int>(170 * 25.4f);
					nLength = static_cast<int>(220 * 25.4f);
					break;

				case DMPAPER_DSHEET: // D Sheet, 22 by 34 inches
					nWidth = static_cast<int>(220 * 25.4f);
					nLength = static_cast<int>(340 * 25.4f);
					break;

				case DMPAPER_ESHEET: // E Sheet, 34 by 44 inches
					nWidth = static_cast<int>(340 * 25.4f);
					nLength = static_cast<int>(440 * 25.4f);
					break;

				case DMPAPER_LETTERSMALL: // Letter Small, 8 1/2 by 11 inches
					nWidth = static_cast<int>(85 * 25.4f);
					nLength = static_cast<int>(110 * 25.4f);
					break;

				case DMPAPER_TABLOID: // Tabloid, 11 by 17 inches
					nWidth = static_cast<int>(110 * 25.4f);
					nLength = static_cast<int>(170 * 25.4f);
					break;

				case DMPAPER_LEDGER: // Ledger, 17 by 11 inches
					nWidth = static_cast<int>(170 * 25.4f);
					nLength = static_cast<int>(110 * 25.4f);
					break;

				case DMPAPER_STATEMENT: // Statement, 5 1/2 by 8 1/2 inches
					nWidth = static_cast<int>(55 * 25.4f);
					nLength = static_cast<int>(85 * 25.4f);
					break;

				case DMPAPER_EXECUTIVE: // Executive, 7 1/4 by 10 1/2 inches
					nWidth = static_cast<int>(72 * 25.4f);
					nLength = static_cast<int>(105 * 25.4f);
					break;

				case DMPAPER_A3: // A3 sheet, 297 by 420 millimeters
					nWidth = 2970;
					nLength = 4200;
					break;

				case DMPAPER_A4SMALL: // A4 small sheet, 210 by 297 millimeters
					nWidth = 2100;
					nLength = 2970;
					break;

				case DMPAPER_A5: // A5 sheet, 148 by 210 millimeters
					nWidth = 1480;
					nLength = 2100;
					break;

				case DMPAPER_B4: // B4 sheet, 250 by 354 millimeters
					nWidth = 2500;
					nLength = 3540;
					break;

				case DMPAPER_B5: // B5 sheet, 182-by-257-millimeter paper
					nWidth = 1820;
					nLength = 2570;
					break;

				case DMPAPER_FOLIO: // Folio, 8-1/2-by-13-inch paper
					nWidth = static_cast<int>(85 * 25.4f);
					nLength = static_cast<int>(130 * 25.4f);
					break;

				case DMPAPER_QUARTO: // Quarto, 215-by-275-millimeter paper
					nWidth = 2150;
					nLength = 2750;
					break;

				case DMPAPER_10X14: // 10-by-14-inch sheet
					nWidth = static_cast<int>(100 * 25.4f);
					nLength = static_cast<int>(140 * 25.4f);
					break;

				case DMPAPER_11X17: // 11-by-17-inch sheet
					nWidth = static_cast<int>(110 * 25.4f);
					nLength = static_cast<int>(170 * 25.4f);
					break;

				case DMPAPER_NOTE: // Note, 8 1/2 by 11 inches
					nWidth = static_cast<int>(85 * 25.4f);
					nLength = static_cast<int>(110 * 25.4f);
					break;

				case DMPAPER_ENV_9: // #9 Envelope, 3 7/8 by 8 7/8 inches
					nWidth = static_cast<int>(38 * 25.4f);
					nLength = static_cast<int>(88 * 25.4f);
					break;

				case DMPAPER_ENV_10: // #10 Envelope, 4 1/8 by 9 1/2 inches
					//					nWidth = 4125;
					//					nLength = 9500;
					break;

				case DMPAPER_ENV_11: // #11 Envelope, 4 1/2 by 10 3/8 inches
					//					nWidth = 4500;
					//					nLength = 10375;
					break;

				case DMPAPER_ENV_12: // #12 Envelope, 4 3/4 by 11 inches
					//					nWidth = 4750;
					//					nLength = 11000;
					break;

				case DMPAPER_ENV_14: // #14 Envelope, 5 by 11 1/2 inches
					//					nWidth = 5000;
					//					nLength = 11500;
					break;

				case DMPAPER_ENV_DL: // DL Envelope, 110 by 220 millimeters
					nWidth = 1100;
					nLength = 2200;
					break;

				case DMPAPER_ENV_C5: // C5 Envelope, 162 by 229 millimeters
					nWidth = 1620;
					nLength = 2290;
					break;

				case DMPAPER_ENV_C3: // C3 Envelope, 324 by 458 millimeters
					nWidth = 3240;
					nLength = 4580;
					break;

				case DMPAPER_ENV_C4: // C4 Envelope, 229 by 324 millimeters
					nWidth = 2290;
					nLength = 3240;
					break;

				case DMPAPER_ENV_C6: // C6 Envelope, 114 by 162 millimeters
					nWidth = 1140;
					nLength = 1620;
					break;

				case DMPAPER_ENV_C65: // C65 Envelope, 114 by 229 millimeters
					nWidth = 1140;
					nLength = 2290;
					break;

				case DMPAPER_ENV_B4: // B4 Envelope, 250 by 353 millimeters
					nWidth = 2500;
					nLength = 3530;
					break;

				case DMPAPER_ENV_B5: // B5 Envelope, 176 by 250 millimeters
					nWidth = 1760;
					nLength = 2500;
					break;

				case DMPAPER_ENV_B6: // B6 Envelope, 176 by 125 millimeters
					nWidth = 1760;
					nLength = 1250;
					break;

				case DMPAPER_ENV_ITALY: // Italy Envelope, 110 by 230 millimeters
					nWidth = 1100;
					nLength = 2300;
					break;

				case DMPAPER_ENV_MONARCH: // Monarch Envelope, 3 7/8 by 7 1/2 inches
					//					nWidth = 3875;
					//					nLength = 7500;
					break;

				case DMPAPER_ENV_PERSONAL: // 6 3/4 Envelope, 3 5/8 by 6 1/2 inches
					//					nWidth = 3625;
					//					nLength = 6500;
					break;

				case DMPAPER_FANFOLD_US: // US Std Fanfold, 14 7/8 by 11 inches
					//					nWidth = 14875;
					//					nLength = 10000;
					break;

				case DMPAPER_FANFOLD_STD_GERMAN: // German Std Fanfold, 8 1/2 by 12 inches
					//					nWidth = 8500;
					//					nLength = 12000;
					break;

				case DMPAPER_FANFOLD_LGL_GERMAN: // German Legal Fanfold, 8 1/2 by 13 inches
					//					nWidth = 8500;
					//					nLength = 13000;
					break;
				}

				if (lpDevMode->dmOrientation == DMORIENT_PORTRAIT)
				{
					szPaper.cx = nWidth;
					szPaper.cy = nLength;
					bSuccess = true;
				}
				else if (lpDevMode->dmOrientation == DMORIENT_LANDSCAPE)
				{
					szPaper.cx = nLength;
					szPaper.cy = nWidth;
					bSuccess = true;
				}
			}

			::GlobalUnlock(hDevMode);
		}
	}

	return bSuccess;
}

int CPrinterConfig::CalcDevNamesSize(LPDEVNAMES lpDevNames)
{
	char* pDriver = reinterpret_cast<char*>(&((LPBYTE) lpDevNames)[lpDevNames->wDriverOffset]);
	char* pDevice = reinterpret_cast<char*>(&((LPBYTE) lpDevNames)[lpDevNames->wDeviceOffset]);
	char* pOutput = reinterpret_cast<char*>(&((LPBYTE) lpDevNames)[lpDevNames->wOutputOffset]);
	int nVarSize = (int)strlen(pDriver) + (int)strlen(pDevice) + (int)strlen(pOutput) + 3;
	return (sizeof(DEVNAMES) + nVarSize);
}

HGLOBAL CPrinterConfig::DupDevNames(HGLOBAL hSrcDevNames)
{
	HGLOBAL hDstDevNames = NULL;

	if (hSrcDevNames != NULL)
	{
		size_t nSize = ::GlobalSize(hSrcDevNames);
		LPDEVNAMES lpSrcDevNames = reinterpret_cast<LPDEVNAMES>(::GlobalLock(hSrcDevNames));

		if (lpSrcDevNames != NULL)
		{
			hDstDevNames = ::GlobalAlloc(GMEM_MOVEABLE, nSize);

			if (hDstDevNames != NULL)
			{
				LPDEVNAMES lpDstDevNames = reinterpret_cast<LPDEVNAMES>(::GlobalLock(hDstDevNames));
				if (lpDstDevNames != NULL)
				{
					memcpy(lpDstDevNames, lpSrcDevNames, nSize);
					::GlobalUnlock(hDstDevNames);
				}
			}

			::GlobalUnlock(hSrcDevNames);
		}
	}

	return hDstDevNames;
}

int CPrinterConfig::CalcDevModeSize(HGLOBAL hDevNames)
{
	int nDevModeSize = 0;

	LPDEVNAMES lpDevNames = (LPDEVNAMES) ::GlobalLock(hDevNames);
	if (lpDevNames != NULL)
	{
		LPTSTR lpDeviceName = (LPTSTR) &((LPBYTE) lpDevNames)[lpDevNames->wDeviceOffset];

		HANDLE hPrinter;

		if (::OpenPrinter(lpDeviceName, &hPrinter, NULL))
		{
			// Determine number of bytes needed for the DEVMODE structure.

			nDevModeSize = ::DocumentProperties(NULL,
				hPrinter,
				lpDeviceName,
				NULL, NULL, 0);

			::ClosePrinter(hPrinter);
		}

		::GlobalUnlock(hDevNames);
	}

	return nDevModeSize;		
}

HGLOBAL CPrinterConfig::DupDevMode(HGLOBAL hSrcDevMode)
{
	HGLOBAL hDstDevMode = NULL;

	if (hSrcDevMode != NULL)
	{
		size_t nSize = ::GlobalSize(hSrcDevMode);
		LPDEVMODE lpSrcDevMode = reinterpret_cast<LPDEVMODE>(::GlobalLock(hSrcDevMode));

		if (lpSrcDevMode != NULL)
		{
			hDstDevMode = ::GlobalAlloc(GMEM_MOVEABLE, nSize);

			if (hDstDevMode != NULL)
			{
				LPDEVMODE lpDstDevMode = reinterpret_cast<LPDEVMODE>(::GlobalLock(hDstDevMode));
				if (lpDstDevMode != NULL)
				{
					memcpy(lpDstDevMode, lpSrcDevMode, nSize);
					::GlobalUnlock(hDstDevMode);
				}
			}

			::GlobalUnlock(hSrcDevMode);
		}
	}

	return hDstDevMode;
}




};	// namespace stingray::foundation
};	// namespace stingray
