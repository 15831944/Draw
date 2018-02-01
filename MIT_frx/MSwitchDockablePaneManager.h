#pragma once

#define MIDAS_SDK

#include <list>

#include "HeaderPre.h"

namespace mit
{
    namespace frx
    {
        class MSwitchDockablePane;
        class __MY_EXT_CLASS__ MSwitchDockablePaneManager
        {
        public:
            MSwitchDockablePaneManager();
            ~MSwitchDockablePaneManager();

            // Singleton
            static MSwitchDockablePaneManager& Instance();

            typedef std::list<MSwitchDockablePane*> pane_list;

            void RegisterSwitchDockPane(MSwitchDockablePane* pPane);

            void AddDocument(CDocument* pDoc);
            void RemoveDocument(CDocument* pDoc);

            void SetCurrentDocument(CDocument* pDoc);

        protected:

            pane_list m_listPane;
        };
    }
}

#include "HeaderPost.h"
