///////////////////////////////////////////////////////////////////////////////
// Printable.h : SFL Print Preview package 
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
// Description:  Declaration of the IPrintable interface.
//

#pragma once

#if !defined(_SFL)
#define _SFL
#endif

#include <Foundation\Print\PrintDoc.h>

namespace stingray {
namespace foundation {

//////////////////////////////////////////////////////////////////////////
//@doc IPrintable

//@class IPrintable | This interface is implemented by objects to support
// printing and print preview. The methods in this interface provide a
// means to print a page at time to a <c CPrintDoc> object and to
// determine the total number of pages the printable object contains.

class __declspec(uuid("9B35CA0F-7A12-401e-8BD5-4330074FF35B"))
	IPrintable
{
public:
	//@cmember
	/* Get number of pages in document. */
	virtual int GetPageCount(CPrintDoc* pPrintDoc) = 0;
	//@cmember
	/* Prepare the next page for printing. */
	virtual bool BeginPage(CPrintDoc* pPrintDoc) = 0;
	//@cmember
	/* Print the current page to the print document. */
	virtual bool PrintPage(CPrintDoc* pPrintDoc) = 0;
	//@cmember
	/* Cleanup after printing a page. */
	virtual bool EndPage(CPrintDoc* pPrintDoc) = 0;
};

};	// namespace stingray::foundation
};	// namespace stingray
