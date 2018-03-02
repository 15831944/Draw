#pragma once
#define _LS(ResID)	CMSGFunction::GetValue(CString(#ResID))
#define _ULS(String) CMSGFunction::RemoveQuote(CString(#String))
#include "HeaderPre.h"
//namespace lib
//{
	class __MY_EXT_CLASS__ CMSGFunction
	{
	public:
		CMSGFunction(void);
		~CMSGFunction(void);
		static void AddFile(LPCTSTR filePath);
		static bool LoadFile();
		static void Reset();
		static void Clear();
		static CString GetValue(LPCTSTR lpszID);
		static CString RemoveQuote(LPCTSTR lpszStr);
	};
//}
#include "HeaderPost.h"

