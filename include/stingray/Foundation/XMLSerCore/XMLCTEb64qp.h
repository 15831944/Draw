///////////////////////////////////////////////////////////////////////////////
// XMLCTEb64qp.h : Header file for the SECBase64Encoder and SECQPEncoder classes
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
// Author:      Prakash Surendra
// Description: SECBase64Encoder and SECQPEncoder - MIME Content Transfer Encoding/Decoding classes
//

// The Base64 and Quoted-Printable Encoding/Decoding implementations used in these classes are
// based on the free MimePak 1.1 C routines obtained from Hunny Software (www.hunnysoft.com)
/*--------------------------------------------------------------------------*\
  Copyright (C) 1999 Douglas W. Sauder

  This software is provided "as is," without any express or implied
  warranty.  In no event will the author be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  The original distribution can be obtained from www.hunnysoft.com.
  You can email the author at dwsauder@hunnysoft.com.

  $RCSfile: base64.h,v $
  $Revision: 1.2 $
  $Date: 1999-07-29 18:42:39-04 $
\*--------------------------------------------------------------------------*/


#ifndef __SFL_XMLCTEB64QP_H__
#define __SFL_XMLCTEB64QP_H__

#pragma once

#include <StingrayExportDefs.h>

namespace stingray {
	namespace foundation {

#define OUT_BUFFER_SIZE 1240
#define TEMP_BUFFER_SIZE 100


/////////////////////////////////////////////////////////////////////////////////////////////////
//  SECCTEBase - Base class for SECBase64Encoder and SECQPEncoder



///////////////////////////////////////////////////////////////////////////
//@doc SECCTEBase
//
//
//@mfunc void | SECCTEBase | InitializeEncoder | Initializes the encoder to it's zero state. Calling 
// InitializeEncoder during a streaming encode/decode operation will reset the internal state.
//@rdesc void
//@comm Pure virtual in SECCTEBase. Implementated in the SECBase64Encoder and SECQPEncoder classes.
//	
//@mfunc int | SECCTEBase | Encode | Calling the Encode function will encode the data provided in the 
// pInBuffer parameter. Depending on the streaming mode, input data can be fed in one encode call or 
// sequential calls. When the pOutBuffer parameter is NULL the encoded data is written to an internal buffer 
// and can be obtained by a call to EndEncode.
//@rdesc Returns the length in bytes of the encoded data.
//@parm BYTE* | pInBuffer | Starting address of the input buffer.
//@parm int | nInLength | Length of the input buffer.
//@parm BYTE* | pOutBuffer = NULL | Address of the output buffer. If NULL, an internal buffer will be used.
//@parm int | nOutLength = -1 | Length of the output buffer.
//@comm Pure virtual in SECCTEBase. Implementated in the SECBase64Encoder and SECQPEncoder classes.
//
//@mfunc int | SECCTEBase | EndEncode | Calling EndEncode instructs the encoder that the input data stream is 
// complete. This will write the encoded data to the output buffer.
//@rdesc Returns the length in bytes of the encoded data.
//@parm BYTE* | pOutBuffer | The output buffer onto which the encoded data is to be copied.
//@parm int | nOutLength | The size of the output buffer.
//	
//@mfunc int | SECCTEBase | Decode | Calling the Decode function will decode the encoded data provided in the 
// pInBuffer parameter. Depending on the streaming mode, input data can be fed in one decode call or 
// sequential calls. When the pOutBuffer parameter is NULL the decoded data is written to an internal buffer 
// and can be obtained by a call to EndDecode.
//@rdesc Returns the length in bytes of the decoded data.
//@parm BYTE* | pInBuffer | Starting address of the input buffer.
//@parm int | nInLength | Length of the input buffer.
//@parm BYTE* | pOutBuffer = NULL | Address of the output buffer. If NULL, an internal buffer will be used.
//@parm int | nOutLength = -1 | Length of the output buffer.
//@comm Pure virtual in SECCTEBase. Implementation provided in the SECBase64Encoder and SECQPEncoder classes. 
//
//@mfunc int | SECCTEBase | EndDecode | Calling EndDecode instructs the encoder that the input data stream is 
// complete. This will write the decoded output to the output buffer.
//@rdesc Returns the length in bytes of the decoded data.
//@parm BYTE* | pOutBuffer | The output buffer onto which the decoded data is to be copied.
//@parm int | nOutLength | The size of the output buffer.
//	
//@mfunc void | SECCTEBase | SetMaxLineLen | Sets the maximum line length of the encoded data. The default is 72 characters.
//@rdesc void
//@parm int | nMax | The line length.
//
//@mfunc int | SECCTEBase | GetMaxLineLen | Returns the maximum line length.
//@rdesc Line length of the encoded data.
//
//@mfunc void | SECCTEBase | SetCRLFOutput | Calling SetCRLFOutput with a TRUE parameter will set the encoder to output 
// carriage return-line feed sequences. Default is to omit carriage returns.
//@rdesc void
//@parm bool | bSet | TRUE to output CRLF.
//
//@mfunc bool | SECCTEBase | GetCRLFOutput | Returns the current carriage return-line feed output state.
//@rdesc Returns TRUE if CRLF output is set. FALSE otherwise.
//
//@mfunc void | SECCTEBase | SetFinalNewline | Calling SetFinalNewline with a TRUE param will append a final newline 
// character to the encoded output.
//@rdesc void
//@parm bool | bSet | TRUE to output final newline.
//
//@mfunc bool | SECCTEBase | GetFinalNewline | Returns the final newline output state.
//@rdesc Returns TRUE if final newline is set. FALSE otherwise.
//@comm The SECBase64Encoder class has this attribute set to FALSE by default. The default behavior for SECQPEncoder, however, 
// is to output the final newline character.
//
//@mfunc void | SECCTEBase | SetStreamingMode | Specifies how the input data is provided to the Encoder. Default is non-streaming.
//@rdesc void
//@parm bool | bStreaming | When TRUE, an input stream is used for the Encode/Decode calls.
//
//@mfunc bool | SECCTEBase | GetStreamingMode | Returns the streaming mode.
//@rdesc TRUE if the input mode is streaming. FALSE otherwise
//
//@mfunc int | SECCTEBase | GetOutBufferSize | Returns the size of the internally stored output buffer.
//@rdesc Buffer size in bytes.
//
//
//@class SECCTEBase | SECCTEBase is an abstract class that serves as the base for the SECBase64Encoder 
// and SECQPEncoder MIME content-transfer-encoding classes. SECCTEBase defines the API for the encoding/decoding 
// operations and also implements some of the buffer management routines common to the encoder classes.
//
// See Also <c SECBase64Encoder> and <c SECQPEncoder>
//
// Member functions include:
//  <mf SECCTEBase::Encode>, 
//  <mf SECCTEBase::EndEncode>, 
//  <mf SECCTEBase::Decode>, 
//  <mf SECCTEBase::EndDecode>, 
//  <mf SECCTEBase::GetOutBufferSize>,
//  <mf SECCTEBase::InitializeEncoder>,
//  <mf SECCTEBase::SetMaxLinelen>, 
//  <mf SECCTEBase::GetMaxLinelen>,
//  <mf SECCTEBase::SetCRLFOutput>,
//  <mf SECCTEBase::GetCRLFOutput>, 
//  <mf SECCTEBase::SetFinalNewline>, 
//  <mf SECCTEBase::GetFinalNewline>, 
//  <mf SECCTEBase::SetStreamingMode>, and
//  <mf SECCTEBase::GetStreamingMode>
//
class FOUNDATION_API SECCTEBase
{
protected:
	SECCTEBase(bool bStreaming=false);
public:
	virtual ~SECCTEBase();

// Implementation
protected:
	int AllocOutBuffer(BYTE*& pBuffer, int nSize=OUT_BUFFER_SIZE);
	bool CheckIOBuffers(BYTE* pInBuffer, int nInLength, BYTE*& pOutBuffer, int& nOutLength);

	virtual void InternalEndEncode(BYTE* pOutBuffer, int& nOutLength) = 0;
	virtual void InternalEndDecode(BYTE* pOutBuffer, int& nOutLength) = 0;


// CTE classes API
public:
	//@cmember
	/* Sets/Resets the encoder state.*/
	virtual void InitializeEncoder() = 0;

	//@cmember
	/* Encodes the data provided in the in-buffer.*/
	virtual int Encode(BYTE* pInBuffer, int nInLength, BYTE* pOutBuffer=NULL, int nOutLength=-1) = 0;
	
	//@cmember
	/* Writes the encoded data to the out-buffer.*/
	virtual int EndEncode(BYTE* pOutBuffer, int nOutLength);

	//@cmember
	/* Decodes the encoded data provided in the in-buffer.*/
	virtual int Decode(BYTE* pInBuffer, int nInLength, BYTE* pOutBuffer=NULL, int nOutLength=-1) = 0;

	//@cmember
	/* Writes the decoded data to the out-buffer.*/
	virtual int EndDecode(BYTE* pOutBuffer, int nOutLength);

	// Accessor functions
	
	//@cmember
	/* Sets the maximum line length.*/
	void SetMaxLinelen(int nMax)	{ m_nMaxLineLen = nMax; }
	
	//@cmember
	/* Returns the maximum line length*/
	int GetMaxLinelen()	{ return m_nMaxLineLen; }
	
	//@cmember
	/* Sets the CRLF output attribute.*/
	void SetCRLFOutput(bool bSet) { m_bOutputCRLF = bSet; }
	
	//@cmember
	/* Returns the CRLF output attribute.*/
	bool GetCRLFOutput() { return m_bOutputCRLF; }
	
	//@cmember
	/* Sets the final new line attribute.*/
	void SetFinalNewline(bool bSet) { m_bFinalNewline = bSet; }
	
	//@cmember
	/* Returns the final new line attribute.*/
	bool GetFinalNewline() { return m_bFinalNewline; }
	
	int GetCurrentState() { return m_nState; }
	
	//@cmember
	/* Sets the streaming mode.*/
	void SetStreamingMode(bool bStreaming) { m_bStreaming = bStreaming; }
	
	//@cmember
	/* Returns the current streaming mode.*/
	bool GetStreamingMode() { return m_bStreaming; }
	
	//@cmember
	/* Returns the size of the output buffer.*/
	int GetOutBufferSize() { return m_nOutBuffLen; }

protected:
	// Properties
	int m_nMaxLineLen;
	bool m_bOutputCRLF;
	bool m_bFinalNewline;
	bool m_bStreaming;

	// Current state Information
	int m_nState;
	int m_nInPos;
	int m_nOutPos;
	int m_nOutBuffLen;
	int m_nTempLen;
	BYTE* m_pOutBuffer;
};

//
/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////
//  SECBase64Encoder - Base64 Encoding/Decoding class

///////////////////////////////////////////////////////////////////////////
//@doc SECBase64Encoder
//
//@mfunc | SECBase64Encoder | SECBase64Encoder | Constructor. Creates an instance of the SECBase64Encoder class. 
// The lone argument specifies the input mode.
//@parm bool | bStreaming = FALSE | If TRUE, the encoder will be initialized for the streaming mode. Default is FALSE.
//
//@mfunc | SECBase64Encoder | ~SECBase64Encoder | Destructor
//
//@class SECBase64Encoder | The SECBase64Encoder class derives from the SECCTEBase class and implements the logic for 
// the Base64 encoding scheme. SECBase64Encoder merely inherits the API implemented by SECCTEBase and does not add any 
// attributes of it's own.
//
// See Also <c SECCTEBase> and <c SECQPEncoder>
//
//@base public | SECCTEBase

class FOUNDATION_API SECBase64Encoder : public SECCTEBase
{
public:
	//@cmember
	/* Constructor.*/
	SECBase64Encoder(bool bStreaming=false);

	//@cmember
	/* Destructor.*/
	virtual ~SECBase64Encoder();

protected:
// Implementation details
	enum states
	{
		B64_STATE_0 = 0,
		B64_STATE_1, 
		B64_STATE_2,
		B64_STATE_3,
		B64_STATE_OUTPUT_CRLF,
		B64_STATE_OUTPUT_LF,
		B64_STATE_OUTPUT_EQ_EQ,
		B64_STATE_OUTPUT_EQ,
		B64_STATE_DONE,
		B64_STATE_ERROR
	};

protected:
	virtual void InternalEndEncode(BYTE* pOutBuffer, int& nOutLength);
	virtual void InternalEndDecode(BYTE* pOutBuffer, int& nOutLength);

public:
	virtual void InitializeEncoder();
	virtual int Encode(BYTE* pInBuffer, int nInLength, BYTE* pOutBuffer=NULL, int nOutLength=-1);
	virtual int Decode(BYTE* pInBuffer, int nInLength, BYTE* pOutBuffer=NULL, int nOutLength=-1);

protected:
	BYTE m_LastByte;
};

//
/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////
//  SECQPEncoder - Quoted Printable Encoding/Decoding class

#define SAFE       'S'
#define UNSAFE     'U'
#define SPECIAL    'L'
#define LITERAL    'P'
#define SPACE      'W'
#define SOFT_LINE_BREAK 1
#define HARD_LINE_BREAK 2


///////////////////////////////////////////////////////////////////////////
//@doc SECQPEncoder
//
//@mfunc | SECQPEncoder | SECQPEncoder | Constructor. Creates an instance of the SECQPEncoder class. 
// The bStreaming argument specifies the input mode.
//@parm bool | bStreaming = FALSE | If TRUE, the encoder will be initialized for the streaming mode. Default is FALSE.
//
//@mfunc | SECQPEncoder | ~SECQPEncoder | Destructor
//
//@mfunc void | SECQPEncoder | SetProtectFrom | Setting the 'protect-from' mode to TRUE forces the encoder to replace  
// the first character of a "From" sub-string encountered at the beginning of a line with it's hexadecimal equivalent.
// The default is set to FALSE. 
//@rdesc void
//@parm bool | bSet | When TRUE, 'protect-from' is enabled.
//@comm This functionality is provided for compliance with certain mail systems.
//
//@mfunc bool | SECQPEncoder | GetProtectFrom | Returns the 'protect-from' mode.
//@rdesc TRUE if the 'protect-from' mode is set. FALSE otherwise
//
//@mfunc void | SECQPEncoder | SetProtectDot | Setting the 'protect-dot' mode to TRUE forces the SECQPEncoder to encode  
// any '.' character encountered at the beginning of a line.
// The default is set to FALSE. 
//@rdesc void
//@parm bool | bSet | When TRUE, 'protect-dot' is enabled.
//@comm This functionality is provided for compliance with certain mail systems.
//
//@mfunc bool | SECQPEncoder | GetProtectDot | Returns the 'protect-from' mode.
//@rdesc TRUE if the 'protect-from' mode is set. FALSE otherwise
//
//@class SECQPEncoder | The SECQPEncoder class derives from the SECCTEBase class and implements the logic for 
// the Quoted-Printable encoding scheme. SECQPEncoder, in addition to the API that it inherits from SECCTEBase, adds 
// the following member functions specific to the quoted-printable scheme. 
//
//  <mf SECCTEBase::SetProtectFrom>, 
//  <mf SECCTEBase::GetProtectFrom>, 
//  <mf SECCTEBase::SetProtectDot>, and 
//  <mf SECCTEBase::GetProtectDot>
//
// See Also <c SECCTEBase> and <c SECBase64Encoder>
//
//@base public | SECCTEBase

class FOUNDATION_API SECQPEncoder : public SECCTEBase
{
public:
	//@cmember
	/* Constructor.*/
	SECQPEncoder(bool bStreaming=false);
	
	//@cmember
	/* Destructor.*/
	virtual ~SECQPEncoder();

// Implementation
protected:
	enum states
	{
		QP_STATE_NORMAL = 0,
		QP_STATE_WRITE_OUTPUT,
		QP_STATE_BUFFER,
		QP_STATE_SKIP,
		QP_STATE_FLUSH,
		QP_STATE_ESCAPE,
		QP_STATE_HEX,
		QP_STATE_ERROR
	};

protected:
	virtual void PrepareLine();
	virtual void FillLineBuffer(BYTE* pInBuffer, int nInLength);
	virtual void WriteOutput(BYTE* pOutBuffer, int& nOutLength);
	virtual void InternalEndEncode(BYTE* pOutBuffer, int& nOutLength);
	virtual void InternalEndDecode(BYTE* pOutBuffer, int& nOutLength);

// SECQPEncoder accessor functions
public:
	//@cmember
	/* Sets the 'protect-from' mode.*/
	void SetProtectFrom(bool bSet) { m_bProtectFrom = bSet; }
	
	//@cmember
	/* Returns the 'protect-from' mode.*/
	bool GetProtectFrom() { return m_bProtectFrom; }
	
	//@cmember
	/* Sets the 'protect-dot' mode.*/
	void SetProtectDot(bool bSet) { m_bProtectDot = bSet; }
	
	//@cmember
	/* Returns the 'protect-dot' mode.*/
	bool GetProtectDot() { return m_bProtectDot; }

public:
	virtual void InitializeEncoder();
	virtual int Encode(BYTE* pInBuffer, int nInLength, BYTE* pOutBuffer=NULL, int nOutLength=-1);
	virtual int Decode(BYTE* pInBuffer, int nInLength, BYTE* pOutBuffer=NULL, int nOutLength=-1);

protected:
	bool m_bProtectFrom;
	bool m_bProtectDot;
	int m_nCharsInBuffer;
	int m_nTempPos;
	BYTE* m_pTempBuffer;
};

//
/////////////////////////////////////////////////////////////////////////////////////////////////

}; // namespace stingray::foundation
}; // namespace stingray

#endif // __SFL_XMLCTEB64QP_H__