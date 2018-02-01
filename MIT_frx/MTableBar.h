#pragma once

#include "MLayeredDockingControlBar.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MTable;

		class __MY_EXT_CLASS__ MTableBar : public mit::frx::MLayeredDockingControlBar
		{
			friend class MTabbedChildFrame;

			DECLARE_SERIAL(MTableBar);
		public:
			MTableBar();
			MTableBar(CDocument* pDoc);
			MTableBar(CDocument* pDoc, CRuntimeClass* pRTC);	
			MTableBar(CDocument* pDoc, CArray<CRuntimeClass*>& arRTCs);	
			virtual ~MTableBar();

			// Attributes
		protected:
			CBCGPTabWnd				m_wndTabs;
			CArray<MTable*>			m_arTables;
			CArray<CRuntimeClass*>	m_arRTC;
			CDocument*				m_pDoc;
			// Operations
		public:
			void SetDocument(CDocument* pDoc) { ASSERT(pDoc); m_pDoc = pDoc; }
			CDocument* GetDocument() { return m_pDoc; }
			int  SetTableClass(CArray<CRuntimeClass*>& arTable);
			void AddTableClass(CRuntimeClass* pRTC);
			const CRuntimeClass* GetTableClass(int idx);

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
			afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
			afx_msg void OnNcPaint();
			afx_msg void OnPaint();
			//}}AFX_MSG
			DECLARE_MESSAGE_MAP()			
		};
	}
}

#include "HeaderPost.h"

/////////////////////////////////////////////////////////////////////////////