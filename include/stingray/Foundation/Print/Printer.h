///////////////////////////////////////////////////////////////////////////////
// Printer.h : SFL Print Preview package 
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
// Description:  Class to encapsulate a printer.
//

#pragma once

#if !defined(_SFL)
#define _SFL
#endif

#include <winspool.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

//////////////////////////////////////////////////////////////////////////
//@doc CPrinter

//@class This class encapsulates a Windows printer. It is basically a
// wrapper class that provides easy access to the printer API functions.
// The class can be passed an existing printer handle or it can create
// one by opening a specified printer. This class can be used in
// conjunction with the <c CPrinterConfig> class to open a printer.
// It is also used in conjunction with the <c CPrintJob> class.
// Using this class you can get a list of print jobs currently
// spooled to a printer. You can also reset the printer or even
// delete the printer.

class FOUNDATION_API CPrinter
{
// Constructors/destructor
public:
	//@cmember
	/* Construct a printer from a handle. */
	CPrinter(HANDLE hPrinter = NULL, const bool bOwnHandle = true) :
		m_hPrinter(hPrinter),
		m_bOwnHandle(bOwnHandle)
	{
	}

	//@cmember
	/* Destroy printer object. */
	virtual ~CPrinter()
	{
		Close();
	}

// Attributes
protected:
	//@cmember
	/* Handle to printer. */
	HANDLE m_hPrinter;
	//@cmember
	/* API structure passed to OpenPrinter to specify desired access level to printer. */
	PRINTER_DEFAULTS m_printerDefaults;
	//@cmember
	/* Flag to determine if this object will close the printer when destroyed. */
	bool m_bOwnHandle;

// Operations
public:
	//@cmember
	/* Return the printer handle associated with this object. */
	operator HANDLE()
	{
		return m_hPrinter;
	}

	//@cmember
	/* Attach an existing printer handle to this object. */
	virtual void Attach(HANDLE hPrinter, bool bOwnHandle = true)
	{
		if (m_bOwnHandle)
		{
			Close();
		}
		m_bOwnHandle = bOwnHandle;
		m_hPrinter = hPrinter;
	}

	//@cmember
	/* Detach the handle associated with this object. */
	virtual HANDLE Detach() 
	{
		HANDLE hPrinter = m_hPrinter;
		m_hPrinter = NULL;
		m_bOwnHandle = true;
		return hPrinter;
	}

	//@cmember
	/* Open a printer by device name. */
	bool Open(LPCTSTR pPrinterName)
	{
		bool bSuccess = false;

		if (m_hPrinter == NULL)
		{
			if (::OpenPrinter(const_cast<LPTSTR>(pPrinterName), &m_hPrinter, NULL /* printer defaults */))
			{
				m_bOwnHandle = true;
				bSuccess = true;
			}
		}

		return bSuccess;
	}

	//@cmember
	/* Determines if this object is associated with an open printer handle. */
	bool IsOpen() const
	{
		return (m_hPrinter != NULL);
	}

	//@cmember
	/* Close the printer handle associated with this object. */
	bool Close()
	{
		bool bSuccess = false;

		if (m_hPrinter != NULL && m_bOwnHandle)
		{
			if (::ClosePrinter(m_hPrinter))
			{
				m_hPrinter = NULL;
				bSuccess = true;
			}
		}

		return bSuccess;
	}

	bool Reset()
	{
		bool bSuccess = false;

		if (m_hPrinter != NULL)
		{
			if (::ResetPrinter(m_hPrinter, NULL /* printer defaults */))
			{
				bSuccess = true;
			}
		}

		return bSuccess;
	}

	//@cmember
	/* Delete the printer configuration associated with this object. */
	bool Delete()
	{
		bool bSuccess = false;

		if (m_hPrinter != NULL)
		{
			if (::DeletePrinter(m_hPrinter))
			{
				m_hPrinter = NULL;
				bSuccess = true;
			}
		}

		return bSuccess;
	}
};

};	// namespace stingray::foundation
};	// namespace stingray
