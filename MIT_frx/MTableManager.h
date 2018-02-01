#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MTableBar;
		class __MY_EXT_CLASS__ MTableManager
		{
		protected:
			MTableManager(void);

		public:
			virtual ~MTableManager(void);

		public:
			static MTableManager* GetInstance();

		public:
			void ShowTableBar(UINT uiID, CString strName, CRuntimeClass* pBar, CDocument* pDoc);
			MTableBar* GetTableBar(CRuntimeClass* pBar, CDocument* pDoc);
			BOOL RemoveTableBar(CRuntimeClass* pBar, CDocument* pDoc);

		protected:
			MHashKMap2K<CRuntimeClass*, CDocument*, MTableBar*>  m_hmTableBar;
		};
	}
}

#include "HeaderPost.h"