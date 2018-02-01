#pragma once

#include "MLayeredDockingControlBar.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MChartCtrl;

		class __MY_EXT_CLASS__ MChartBar : public mit::frx::MLayeredDockingControlBar
		{
			friend class MChartChildFrame;

			DECLARE_SERIAL(MChartBar);

		public:
			MChartBar();
			MChartBar(CDocument* pDoc);
			MChartBar(CDocument* pDoc, CRuntimeClass* pRTC);
			virtual ~MChartBar();

		protected:
			CBCGPTabWnd m_wndTabs;
			CDocument* m_pDoc;
			CArray<MChartCtrl*> m_arChart;
			CArray<CRuntimeClass*>	m_arRTC;
			MChartCtrl* m_pDrawedChart;

		public:
			void SetDocument(CDocument* pDoc) { ASSERT(pDoc); m_pDoc = pDoc; }
			CDocument* GetDocument() { return m_pDoc; }
			int  SetChartClass(CArray<CRuntimeClass*>& arTable);
			void SetChart(MChartCtrl* pChart) { m_pDrawedChart = pChart; }
			void AddChartClass(CRuntimeClass* pRTC);
			const CRuntimeClass* GetChartClass(int idx);
			const MChartCtrl* GetChart(int idx);
			int GetChartCount();

		public:
			virtual BOOL CanBeTabbedDocument () const;
			virtual BOOL DestroyWindow();

		protected:
			virtual void OnPressCloseButton ();

			// Generated message map functions
		protected:
			//{{AFX_MSG(MAutoDestroyBar)
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			afx_msg void OnSize(UINT nType, int cx, int cy);
			afx_msg void OnClose();
			//}}AFX_MSG
			DECLARE_MESSAGE_MAP()			
		};
	}
}

#include "HeaderPost.h"