#pragma once

#include <vector>
#include <map>
#include "HeaderPre.h"
//namespace lib
//{
	class __MY_EXT_CLASS__ CMSGParser
	{
	friend class CMSGFunction;
	public:
		CMSGParser(void);
		~CMSGParser(void);
		typedef std::vector<CString> file_vect;
		typedef std::map<CString,CString> msg_map;
		CString GetValue(const CString& id);
	private:
		file_vect	m_svFile;
		msg_map m_smMsg;
		void AddPath(LPCTSTR lpszPath);
		bool Load();
		void Clear();
		

	};
//}
#include "HeaderPost.h"

