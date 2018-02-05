#pragma once
#include <vector>
#include "HeaderPre.h"
//namespace lib
//{
	class __MY_EXT_CLASS__ CMSGInfo
	{
		typedef std::vector<CString> file_vect;
	public:
		//static CMSGInfo* Instance();
		~CMSGInfo(void);

	//private:
		CMSGInfo(void);
	private:
		//static CMSGInfo* m_pInstance;
		file_vect _file;
		void LoadMessage();
		CString GetProgramPath();
	};
//}
#include "HeaderPost.h"

