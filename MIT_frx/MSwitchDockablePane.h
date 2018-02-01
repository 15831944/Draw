#pragma once

#define MIDAS_SDK

#include "MLayeredDockingControlBar.h"

#include <map>
#include <list>

#include "HeaderPre.h"

namespace mit
{
    namespace frx
    {
        class MBaseDockWnd;
        class __MY_EXT_CLASS__ MSwitchDockablePane : public MLayeredDockingControlBar
        {	
        public:
            MSwitchDockablePane();
            virtual ~MSwitchDockablePane();

            typedef std::map<CDocument*,MBaseDockWnd*> pane_map;

            void RegisterPane(CRuntimeClass* pRuntimeClass, UINT uiID );

            void AddDocument(CDocument* pDoc);
            void RemoveDocument(CDocument* pDoc);
            void SetCurrentDocument(CDocument* pDoc);

            MBaseDockWnd* GetDefaultPaneWnd();
            MBaseDockWnd* GetCurPaneWnd();
            MBaseDockWnd* GetPaneWnd(CDocument* pDoc);
            long GetPaneList(mit::MList<MBaseDockWnd*>& lPane);
			UINT GetID() { return m_uiID; }

        public:

		protected:
			void OnSlide(BOOL bSlideOut);

        protected:

            CRuntimeClass* m_pRuntimeClass;
            UINT m_uiID;

            pane_map m_mapPane;

            // Docking Pane
            MBaseDockWnd* m_pDefaultPane;
            MBaseDockWnd* m_pCurPaneWnd;

            // Messages
            DECLARE_MESSAGE_MAP()
            afx_msg void OnSize(UINT nType, int cx, int cy);
            afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        };
    }
}

#include "HeaderPost.h"