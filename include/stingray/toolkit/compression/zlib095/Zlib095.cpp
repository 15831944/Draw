///////////////////////////////////////////////////////////////////////////////
// zlib095.cpp
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
#include "toolkit\compression\zlib095.h"
#include "compeng.h"

ZLib095Compression::ZLib095Compression()
{
	m_nCompressionLevel = Z_DEFAULT_COMPRESSION;
}

ZLib095Compression::~ZLib095Compression()
{
}

//@doc ZLib095Compression
//@mfunc Compresses specified data from source buffer into destination buffer.
//@rdesc  Nonzero if the comp was successful; otherwise 0.
//@parm  unsigned char* | pSrcBuf | Pointer to the source buffer
//@parm  int | nSrcBufLen | Length of the source buffer
//@parm  unsigned char* | pDestBuf | Pointer to the destination buffer
//@parm  int | nDestBufLen | Length of the destination buffer
//@comm 
//@xref <c ZLib095Compression> <mf ZLib095Compression::Decompress>
int ZLib095Compression::Compress(unsigned char *pSrcBuf, int nSrcBufLen, unsigned char *pDestBuf, int nDestBufLen)
{
	SECComp comp;
	DWORD dwDestLen = nDestBufLen;
	return comp.compress((BYTE*)pDestBuf, &dwDestLen, (BYTE*)pSrcBuf, (DWORD)nSrcBufLen);
}

//@doc ZLib095Compression
//@mfunc Decompresses specified data from source buffer into destination buffer.
//@rdesc  Nonzero if the comp was successful; otherwise 0.
//@parm  unsigned char* | pSrcBuf | Pointer to the source buffer
//@parm  int | nSrcBufLen | Length of the source buffer
//@parm  unsigned char* | pDestBuf | Pointer to the destination buffer
//@parm  int | nDestBufLen | Length of the destination buffer
//@xref <c ZLib095Compression> <mf ZLib095Compression::Compress>
int ZLib095Compression::Decompress(unsigned char *pSrcBuf, int nSrcBufLen, unsigned char *pDestBuf, int nDestBufLen)
{
	SECComp comp;
	DWORD dwDestLen = nDestBufLen;
	return comp.uncompress((BYTE*)pDestBuf, &dwDestLen, (BYTE*)pSrcBuf, (DWORD)nSrcBufLen);
}

//@doc ZLib095Compression
//@mfunc Sets compression level (0 to 9)
//@rdesc  None
//@parm  int | nCompression | Compression level value
//@xref <c ZLib095Compression> <mf ZLib095Compression::GetCompressionLevel>
void ZLib095Compression::SetCompressionLevel(int nCompression)
{
	if (nCompression < Z_BEST_SPEED || nCompression > Z_BEST_COMPRESSION)
		m_nCompressionLevel = Z_DEFAULT_COMPRESSION;
	else
		m_nCompressionLevel = nCompression;
}

//@doc ZLib095Compression
//@mfunc Gets compression level
//@rdesc  Previously set compression level (0 to 9) or -1 in case of default compression level
//@xref <c ZLib095Compression> <mf ZLib095Compression::SetCompressionLevel>
int ZLib095Compression::GetCompressionLevel()
{
	return m_nCompressionLevel;
}

//@doc ZLib095Compression
//@mfunc Gets compression level
//@rdesc Version of the compressor ("Zlib 0.9.5")
CString ZLib095Compression::GetVersion()
{
	return CString(_T("Zlib 0.9.5"));
}

//@doc ZLib095Compression
//@mfunc Gets last error text
//@rdesc Last error's text
CString ZLib095Compression::GetLastError()
{
	return CString();
}

