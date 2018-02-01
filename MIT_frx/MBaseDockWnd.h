#pragma once

#define MIDAS_SDK

#include "afxwin.h"

#include "HeaderPre.h"

class  CDocument;
namespace mit
{
    namespace frx
    {
        class __MY_EXT_CLASS__ MBaseDockWnd : public CWnd
        {
            DECLARE_DYNCREATE(MBaseDockWnd)

        public:
            MBaseDockWnd();
            virtual ~MBaseDockWnd();

            BOOL Create(CWnd *pParent, UINT nID, CDocument* pDocument, DWORD dwStyle = WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN, CRect rect = CRect(10,10,10,10) );
            CDocument* GetDocument() { return m_pDocument; }

            void SetDefaultRect(CRect& rt) { m_Rect = rt; }
            void GetDefaultRect(CRect& rt) { rt = m_Rect; }

            //For TaskPane
            virtual BOOL IsTaskPane() { return FALSE; }
            virtual void ShowTaskPane(BOOL bShow, BOOL bRemove=FALSE) { ASSERT(0); }
            virtual BOOL IsTaskPaneVisible() { ASSERT(0); return FALSE; }
            virtual CWnd* GetTaskPane() { ASSERT(0); return (CWnd*)NULL; }
            virtual void UpdateMainView() {}
			virtual void OnChangeLanguage() { ASSERT(0); }

        protected:

            CDocument* m_pDocument;
            CRect	   m_Rect;

            // Messages
            DECLARE_MESSAGE_MAP()
            afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        };
    }
}
using namespace mit::frx;

#include "HeaderPost.h"