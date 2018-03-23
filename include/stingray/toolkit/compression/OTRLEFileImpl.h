///////////////////////////////////////////////////////////////////////////////
// OTRLEFileImpl.h
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

#ifndef __OTRLEFILEIMPL_H__
#define __OTRLEFILEIMPL_H__

#include "Toolkit\compression\OTILoselessCompression.h"
#include "Toolkit\compression\OTRLEImpl.h"
#include <StingrayExportDefs.h>

class OTRLEFileImpl: public OTCompressionFile
{
public:
	TOOLKIT_API OTRLEFileImpl();
	TOOLKIT_API virtual ~OTRLEFileImpl();

	inline void SetCompressionLevel(int nCompression)
	{
		m_compression.SetCompressionLevel(nCompression);
	}

	inline CString GetVersion()
	{
		return m_compression.GetVersion();
	}

	inline CString GetLastError()
	{
		return m_compression.GetLastError();
	}

	TOOLKIT_API BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags);
	TOOLKIT_API void Close();

	TOOLKIT_API UINT Read(void FAR *pBuf, UINT nCount);
	TOOLKIT_API void Write(const void FAR *pBuf, UINT nCount);

private:
	OTRLEImpl m_compression;
};

#endif __OTRLEFILEIMPL_H__