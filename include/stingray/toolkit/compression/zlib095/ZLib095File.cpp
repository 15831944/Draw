///////////////////////////////////////////////////////////////////////////////
// zlib095file.cpp
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

#define _OT_EXPORT_IMPL

#include "stdafx.h"
#include "Toolkit/compression/zlib095file.h"
#include "compeng.h"

ZLib095File::ZLib095File()
{
	m_gzFile = 0;
}

ZLib095File::~ZLib095File()
{
	Close();
}

//@doc ZLib095File
//@mfunc Opens a ZLib095File with the specified pathname.
//@rdesc  Nonzero if the open was successful; otherwise 0.
//@parm LPCTSTR | lpszFileName | A string that is the path to the desired file. 
// The path may be relative or absolute.
//@parm  UINT | nOpenFlags | Sharing and access mode. Specifies the action 
// to take when opening the file.  Note: modeReadWrite is mapped to modeWrite.
// ModeReadWrite is not supported by the compression code.
//@comm Open is designed for use with the default ZLib095File constructor.  
// The two functions form a "safe" method for opening a file where a failure 
// is a normal, expected condition. The constructor is guaranteed to succeed, 
// and Open returns a pointer to an exception object, bypassing the 
// THROW/TRY/CATCH mechanism.
//@xref <c ZLib095File> <mf ZLib095File::Close> <mf ZLib095File::ZLib095File>
BOOL ZLib095File::Open(LPCTSTR lpszFileName, UINT nOpenFlags)
{
	if (m_gzFile)
	{
		Close();
	}

	CString strMode;

	// Note, modeReadWrite is mapped to modeWrite.  ModeReadWrite
	// is not supported by the compression code.
	if (nOpenFlags & (CFile::modeWrite|CFile::modeReadWrite))
		strMode = _T("wb");
	else if ((nOpenFlags & (CFile::modeWrite | CFile::modeReadWrite)) == 0)
	{
		nOpenFlags |= CFile::shareDenyWrite;
		strMode = _T("rb");
	}
	else
		ASSERT(FALSE);

	int nCompressionLevel = m_compression.GetCompressionLevel();
	if(nCompressionLevel > Z_DEFAULT_COMPRESSION && nCompressionLevel <= Z_BEST_COMPRESSION)
	{
		strMode.Format(_T("%s%d"), strMode, nCompressionLevel);
	}

	if (!CFile::Open(lpszFileName, nOpenFlags))
		return FALSE;
	
	SECComp comp;
	m_gzFile = comp.gz_open((TCHAR *)lpszFileName, strMode.GetBuffer(strMode.GetLength()), 0, this); 
	if (m_gzFile)
		return TRUE;
	else
		return FALSE;
}

//@doc ZLib095File
//@mfunc Reads a number of bytes from the file and decompresses them.  
//@rdesc The number of bytes transferred to the buffer.  Note that for all 
// CFile-derived objects, the return value can be less than nCount if 
// the end of file was reached.
//@parm  void FAR * | pBuf | Pointer to the user-supplied buffer that is 
// to receive the data read from the file.
//@parm  DWORD | nCount | The maximum number of bytes to be read from the file.
//@comm Reads data into a buffer from the file associated with the 
// ZLib095File object.
//@xref <c ZLib095File> <mf ZLib095File::Write>
UINT ZLib095File::Read(void FAR *pBuf, UINT nCount)
{
	if (!m_gzFile)		
		return 0;

	SECComp comp;
	return (UINT)comp.gzread(m_gzFile, pBuf, (long)nCount);
}

//@doc ZLib095File
//@mfunc Compresses and then writes a number of characters to the file.
//@rdesc void 
//@parm  const void FAR * | pBuf | A pointer to the user-supplied buffer 
// that contains the data to be written to the file.
//@parm  UINT | nCount | The number of bytes to be transferred from 
// the buffer.
//@comm Writes data from a buffer to the file associated with the 
// SECCompressFile object.  Write throws an exception in response to 
// several conditions including the disk-full condition.
//@xref <c ZLib095File> <mf ZLib095File::Read>
void ZLib095File::Write(const void FAR *pBuf, UINT nCount)
{
	if (!m_gzFile)
		return;  

	SECComp comp;
	comp.gzwrite(m_gzFile, (BYTE*)pBuf, nCount);
}

//@doc ZLib095File
//@mfunc Closes the file.
//@rdesc void 
//@xref <c ZLib095File> <mf ZLib095File::Close>
void ZLib095File::Close()
{
	if (m_gzFile) 
	{
		SECComp comp;
		int nErr = 0;
		nErr = comp.gzclose(m_gzFile);
		m_gzFile = 0;
		// make sure file closed properly
		ASSERT(nErr != Z_ERRNO);
	}

	if (m_hFile != CFile::hFileNull)
		CFile::Close();
}