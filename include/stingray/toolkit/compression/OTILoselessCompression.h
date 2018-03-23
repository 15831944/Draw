///////////////////////////////////////////////////////////////////////////////
// OTILoselessCompression.h
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
// Author:       Ilya Sharin
// Description:  Declaration of OTILoselessCompression
//
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//


#ifndef __OTILOSELESSCOMPRESSION_H__
#define __OTILOSELESSCOMPRESSION_H__

#include <StingrayExportDefs.h>

class TOOLKIT_API OTILoselessCompression
{
public:
	virtual int Compress(unsigned char *pSrcBuf, int nSrcBufLen, unsigned char *pDestBuf, int nDestBufLen) = 0;
	virtual int Decompress(unsigned char *pSrcBuf, int nSrcBufLen, unsigned char *pDestBuf, int nDestBufLen) = 0;

	virtual void SetCompressionLevel(int nCompression) = 0;
	virtual int GetCompressionLevel() = 0;

	virtual CString GetVersion() = 0;
	virtual CString GetLastError() = 0;
};

class TOOLKIT_API OTCompressionFile : public CFile
{
public:
	virtual void SetCompressionLevel(int nCompression) = 0;
	virtual CString GetVersion() = 0;
	virtual CString GetLastError() = 0;

	virtual BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags) = 0;
	virtual UINT Read(void FAR *pBuf, UINT nCount) = 0;
	virtual void Write(const void FAR *pBuf, UINT nCount) = 0;
	virtual void Close() = 0;

private:
	OTILoselessCompression* m_pCompression;
};

#endif // __OTILOSELESSCOMPRESSION_H__