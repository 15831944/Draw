///////////////////////////////////////////////////////////////////////////////
// MultiTrace.h : interface for the MultiTrace class.
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


#if !defined(AFX_MULTITRACE_H__79AE4213_815B_44F2_BCDC_C5AF6859C954__INCLUDED_)
#define AFX_MULTITRACE_H__79AE4213_815B_44F2_BCDC_C5AF6859C954__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include "rgbase.h"
#include <StingrayExportDefs.h>

struct LoggerErrors
{
	enum eTypeMTError
	{
		eLogGeneralError, //throw this: ... rg_throw(cRgMTException,LoggerErrors::eLogGeneralError);
		eLogAllocBuffer
	};
};

typedef stingray_ot_rg::CRgDefProvideDetail<LoggerErrors::eTypeMTError> _CMTProvideDetail;

class CMTProvideDetail : public _CMTProvideDetail
{
public:
	inline CMTProvideDetail()
	{
		this->AddDetail(LoggerErrors::eLogGeneralError,_T("error in  MTlogging."));
		this->AddDetail(LoggerErrors::eLogAllocBuffer,_T("Could not allocate buffer for in-memory base64 conversion."));
	}
};

typedef stingray_ot_rg::CRgDefException<LoggerErrors::eTypeMTError> CRgMTException;

static CRITICAL_SECTION csect;
static FILE *fout;

static long iWritten_Count;

//denote what sort of "tag" information is output with each call to LogWrite()
enum tagtypes
{
	No_Tags,
	Thread_Tags,
	Custom_Tags
};

//extern int to64(void* inbuffer, int bufferlen, FILE *outfile, long limit);
extern int to64(void* inbuffer, int bufferlen, void *outfile, long limit);

////////////////////////////////////
// trait class definition for Single Thread/MultiThread behaviour.
struct SingleThreadLogTraits
{
	inline static void lock() {};
	inline static void unlock() {};
	inline static void init() {};
	inline static void term() {};
};

struct MultiThreadLogTraits
{
public:
	inline static void lock(){ EnterCriticalSection(&csect);}
	inline static void unlock(){ LeaveCriticalSection(&csect);}
	inline static void init(){InitializeCriticalSection(&csect);}
	inline static void term(){DeleteCriticalSection(&csect);}
};

/////////////////////////////////////////////////////////////////
// trait class definition for wide/narrow character type behaviour
// note that this can be extended/overridden/re-written by the user
// for customization.

struct LogFileCharTraits
{
	inline  static void fileopen(const _TCHAR *fname, _TCHAR *writemode)
	{
	#ifdef _UNICODE
		fout = _wfopen(fname,writemode);
	#else
		fout = fopen(fname,writemode);
	#endif
	}
	inline static int fileprintf(_TCHAR *format, va_list arglist)
	{
		if (fout)
		{
			#ifdef _UNICODE
				return vfwprintf(fout,format,arglist);
			#else
				return vfprintf(fout,format,arglist);	
			#endif
		}
		else
			return 0;
	}
	
	inline static int	FilePrintThreadOpenTag()
	{
		DWORD dwThreadID = GetCurrentThreadId();
		SYSTEMTIME st;
		if (fout)
		{
			GetSystemTime(&st);
			#ifdef _UNICODE
				return fwprintf(fout,_T("<%x %02d:%02d:%02d.%04d>"),dwThreadID,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
			#else
				return fprintf(fout,_T("<%x %02d:%02d:%02d.%04d>"),dwThreadID,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
			#endif
		}
		else
			return 0;

	}
	
	inline static int FilePrintThreadCloseTag()
	{
		if(fout)
		{
			DWORD dwThreadID = GetCurrentThreadId();
			#ifdef _UNICODE
				return fwprintf(fout,_T("</%x>\n"),dwThreadID);
			#else
				return fprintf(fout,_T("</%x>\n"),dwThreadID);
			#endif
		}
		else
			return 0;
	}

	inline static int FilePrintCustomOpenTag(const _TCHAR *tag)
	{
		if(fout)
		{
			#ifdef _UNICODE
				return fwprintf(fout,_T("%s"),tag);
			#else
				return fprintf(fout,_T("%s"),tag);
			#endif
		}
		else
			return 0;
	}

	inline static int FilePrintCustomCloseTag(const _TCHAR *tag)
	{
		if(fout)
		{
			#ifdef _UNICODE
				return fwprintf(fout,_T("%s"),tag);
			#else
				return fprintf(fout,_T("%s"),tag);
			#endif
		}
		else
			return 0;
	}

};



template<typename ThreadTraits = MultiThreadLogTraits,
		 typename CharTraits = LogFileCharTraits> 
class MultiTrace 
{
public:
	inline void Initialize()
	{
		try
		{
			iWritten_Count = 0;
			iLargestBufferSoFar = 0;
			charbuff = NULL;
			ThreadTraits::init();
			if (!(fname == _T("")))
			{
				CharTraits::fileopen(fname.c_str(),_T("w"));
			}else
			{	

				rg_throw(CRgMTException,LoggerErrors::eLogGeneralError);
				fout = 0;
			}
		}catch(...){
          if (!bNoThrow)
		  {
			  if(fout)
				  fclose(fout);
			  throw; //rg_throw back to client here...
		  }
		}
	}

	inline MultiTrace()
	{
		LogFileTagTypes = Thread_Tags;
		opentag = _T("");
		closetag = _T("");
		iMaxFileLen = 0;
		bNoThrow = true;
	}

	inline MultiTrace(_TCHAR * logfilename)
	{
		fname = logfilename;
		LogFileTagTypes = Thread_Tags;
		opentag = _T("");
		closetag = _T("");
		iMaxFileLen = 0;
		bNoThrow = true;

	}

	inline virtual ~MultiTrace()
		{
			if (fout)
				  fclose(fout);
			if (charbuff)
					delete(charbuff);
			ThreadTraits::term();
		}

	inline void increment_written_count(int iWritten)
	{
       iWritten_Count += iWritten;
	   if (iMaxFileLen && (iWritten_Count > iMaxFileLen))
	   {
			iWritten_Count = 0;
			rewind(fout);
	   }
	 }
	
	inline int PrintOpenTag()
	{
		int iret = 0;
		if (LogFileTagTypes == Thread_Tags)
		{
			iret = CharTraits::FilePrintThreadOpenTag();
		}

		if (LogFileTagTypes == Custom_Tags)
		{
			iret = CharTraits::FilePrintCustomOpenTag(opentag.c_str());
		}

		return iret;

	}

	inline int PrintCloseTag()
	{
		int iret = 0;
		if (LogFileTagTypes == Custom_Tags)
		{
			iret = CharTraits::FilePrintCustomCloseTag(closetag.c_str());
		}

		if (LogFileTagTypes == Thread_Tags)
		{
			iret = CharTraits::FilePrintThreadCloseTag();
		}
		return iret;
	}


//the base printf like function, which passes arguments along to fprintf, 
//inside a critical section as required for type safety.

	inline int LogFilePrintf(_TCHAR *format, ...)
	{
		int retval = 0;
		try{
			va_list arglist;
			ThreadTraits::lock();
			va_start(arglist, format);
			retval = CharTraits::fileprintf(format,arglist);
			increment_written_count(retval);
			//iWritten_Count += retval;
			ThreadTraits::unlock();
		}catch(...){
          if (!bNoThrow)
		  {
			  if (fout)
				  fclose(fout);
			  throw; //rg_throw back to client here...
		  }
		}

		return retval;
	}


//slightly higer level routine, designed to be called from multi-threaded code...
//if the "tags" property is set, will "sandwich" a call to fileprintf between
//"tags" which can be custom(user specified), null, or "standard", library supplied
//html like tags containing the thread ID and time.
	inline int LogWrite(_TCHAR *format, ...)
	{
		int retval = 0;
		try{
			va_list arglist;
			ThreadTraits::lock();

			retval += PrintOpenTag();

			va_start(arglist, format);
			retval += CharTraits::fileprintf(format,arglist);

			retval += PrintCloseTag();
			increment_written_count(retval);
			//iWritten_Count += retval;
			ThreadTraits::unlock();
		
		}catch(...){
          if (!bNoThrow)
		  {
			  if (fout)
				  fclose(fout);
			  throw; //rg_throw back to client here...
		  }
		}

		return retval;
	}

	inline int LogBinary(void *bufptr, int buflen)
	{
		
		int retval = 0;
		if (fout){
			try{
				//if the buffer we most recently allocated is adequate, reuse it.
				//otherwise, allocate a number of TCHARS according to the
				//base64 conversion requirements:  every 3 chars in the input 
				//become 4 chars in the output.  Plus a 'fudge factor'.
				if (buflen > iLargestBufferSoFar)
				{
					if (charbuff)
					{
						delete ( charbuff);
						charbuff = NULL;
					}
					charbuff = new _TCHAR[(((buflen/3)+1) * 4) + 2];
					iLargestBufferSoFar = buflen;
				}else{
					memset((void *)charbuff,0,sizeof(_TCHAR));
				}
				retval = PrintOpenTag();
				retval += to64(bufptr, buflen, (void *)charbuff, 0);
				CharTraits::fileprintf(charbuff,0);
				retval += PrintCloseTag();
				increment_written_count(retval);
			}catch(std::bad_alloc a){
				//we could not allocate the char buffer.  Only likely if we're
				//trying to convert larger objects.
				 if(!bNoThrow)
				 {
					 if(fout)
						 fclose(fout);
					 rg_throw(CRgMTException,LoggerErrors::eLogAllocBuffer);
				 }

			}catch(...){
				 if (!bNoThrow)
				 {
					 if(fout)
						 fclose(fout);
					 throw; //throw back to client here...
				 }
			}
		} //if (fout)
		return retval;
	}
	

	enum tagtypes LogFileTagTypes; 	

public:
	std::basic_string<_TCHAR> fname;
	std::basic_string<_TCHAR> opentag;
	std::basic_string<_TCHAR> closetag;
	int iMaxFileLen;
	int iLargestBufferSoFar;
	_TCHAR *charbuff; 
	//if bNoThrow is TRUE, it means the client does not want any exceptions 
	//arising from logging operations to be thrown back to him.  
	bool bNoThrow;
};

//easy to use typedefs for what are thought to be the main choices.
//this can be extended or modified with user defined trait classes

typedef MultiTrace<MultiThreadLogTraits> multithreadedlogger;
typedef MultiTrace<SingleThreadLogTraits> singlethreadedlogger;



//////////////////////////////////////////////////////////////////////////////
//the following code clipped from the public domain base64/mime conversion
//library MPACK.  It has been changed somewhat to operate with arrays of 
//TCHARS instead of file handles.
//////////////////////////////////////////////////////////////////////////////
static char basis_64[] =
   "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static int buffoffset = 0;
static int outputbuffoffset = 0;

inline void bufputc(int val, void *outfile)
{
   _TCHAR *buffer = (_TCHAR *)outfile;
   buffer[outputbuffoffset++] = val;
}


inline char bufgetc(void *buffer, int bufferlen)
{
	if (buffoffset >= bufferlen)
		return -1;
	char *charbuff = (char *)buffer;
	return charbuff[buffoffset++];
}

inline void output64chunk(int c1, int c2, int c3, int pads, void *outfile)

{
    bufputc(basis_64[c1>>2], outfile);
    bufputc(basis_64[((c1 & 0x3)<< 4) | ((c2 & 0xF0) >> 4)], outfile);
    if (pads == 2) {
        bufputc('=', outfile);
        bufputc('=', outfile);
    } else if (pads) {
        bufputc(basis_64[((c2 & 0xF) << 2) | ((c3 & 0xC0) >>6)], outfile);
        bufputc('=', outfile);
    } else {
        bufputc(basis_64[((c2 & 0xF) << 2) | ((c3 & 0xC0) >>6)], outfile);
        bufputc(basis_64[c3 & 0x3F], outfile);
    }
}

//int to64(void* inbuffer, int bufferlen, FILE *outfile, long limit)
inline int to64(void* inbuffer, int bufferlen, void *outfile, long limit)
{
   int c1, c2, c3, ct=0, written=0;
 //  outfile = new _TCHAR[bufferlen * 2];
   int inputbufoffset = 0;
   buffoffset = 0;
   outputbuffoffset = 0;
   if (limit && limit < 73) return 1;
   while ((c1 = bufgetc(inbuffer, bufferlen)) != EOF){
	   c2 = bufgetc(inbuffer,bufferlen);
       if (c2 == EOF){
		   output64chunk(c1,0,0,2,outfile);
	   } else {
		   c3 = bufgetc(inbuffer,bufferlen);
		   if (c3 == EOF){
			   output64chunk(c1,c2,0,1,outfile);
		   }else{
			   output64chunk(c1,c2,c3,0,outfile);
		   }
	   }
	   ct += 4;
	   if(ct > 71){
		   bufputc('\n',outfile);
		   if (limit){
			   limit -= ct + 1;
			   if (limit < 73) return 1;
		   }
	   
			written += 73;
			ct = 0;
	   }
   }
   if(ct){
	   bufputc('\n',outfile);
	   ct++;

   }	  
   bufputc(0,outfile);
   return written + ct;
}



#endif // !defined(AFX_MULTITRACE_H__79AE4213_815B_44F2_BCDC_C5AF6859C954__INCLUDED_)
