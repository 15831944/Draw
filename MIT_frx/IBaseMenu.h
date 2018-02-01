#pragma once

#define MIDAS_SDK

namespace mit
{
    namespace frx
    {
		class MRibbonCategory;
		class MRibbonBar;
		class MRibbonPanel;

        class IBaseMenu
        {
        public:
			virtual ~IBaseMenu() {}
            virtual void SetMenu( MRibbonBar* pRibbonBar )=0;
            virtual void OnChangeLanguage()=0;
            virtual UINT GetType() = 0;
            virtual MRibbonCategory* GetCategory() = 0;
			virtual MRibbonPanel* GetPanel( UINT uiType ) = 0;
        };
    }
}
