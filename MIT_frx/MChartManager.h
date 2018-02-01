#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MChartBar;
		class __MY_EXT_CLASS__ MChartManager
		{
		protected:
			MChartManager(void);

		public:
			virtual ~MChartManager(void);

		public:
			static MChartManager* GetInstance();

		public:
			void ShowChartBar(UINT uiID, CString strName, CRuntimeClass* pBar, CDocument* pDoc);
			MChartBar* GetChartBar(CRuntimeClass* pBar, CDocument* pDoc);
			BOOL RemoveChartBar(CRuntimeClass* pBar, CDocument* pDoc);
			void ExportToImage();

		protected:
			MHashKMap2K<CRuntimeClass*, CDocument*, MChartBar*> m_hmChartMar;
		};
	}
}

#include "HeaderPost.h"