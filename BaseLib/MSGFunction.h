#pragma once
#define _LS(ResID)	CMSGFunction::GetValue(CString(#ResID))
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
		static CString GetValue(LPCTSTR lpszID);
	};
//}
#include "HeaderPost.h"

