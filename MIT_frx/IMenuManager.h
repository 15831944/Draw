#pragma once

#define MIDAS_SDK

namespace mit
{
    namespace frx
    {
		class IBaseMenu;
		class MRibbonBar;
		class MRibbonCategory;
		class MRibbonPanel;

        class IMenuManager
        {
        public:
			virtual int  AddMenu( mit::frx::IBaseMenu* pMenu ) = 0;
			virtual int  DeleteMenu( mit::frx::IBaseMenu* pMenu ) = 0;
			virtual int  DeleteMenu( UINT uiType ) = 0;
			virtual void SetRibbonBar( mit::frx::MRibbonBar* pRibbonBar ) = 0;
            virtual void SetChangeMode( UINT uiMode = 0) = 0;
            virtual void OnChangeLanguage() = 0;
            virtual void SetActiveCategory( UINT uiCategory ) = 0;
            virtual void SetChangeCategory( UINT uiCategory, UINT uiCmdFinishButton, BOOL bShowHide ) = 0;
            virtual mit::frx::MRibbonCategory* GetCategory( UINT uiCategory ) = 0;
			virtual mit::frx::MRibbonPanel* GetPanel( UINT uiCategory, UINT uiPanelType ) = 0;
            virtual void DeleteAllMenu() = 0;
            virtual int  SetDefaultActiveCategory() = 0;
            virtual void SetActiveCategoryWhenCloseAllDocument() = 0;
			virtual mit::frx::IBaseMenu* GetMenu( UINT uiCategory ) =0;
			virtual int  GetMenuConut() = 0;
			virtual int  GetMenus( MArray<mit::frx::IBaseMenu*>& maMenus ) = 0;

			// 제품에서 Context Category를 사용한다면 재정의해서 사용하세요.
			virtual void SetRibbonContextCategory (UINT uiCategoryID) {}
			virtual void ActivateRibbonContextCategory (UINT uiCategoryID) {}
        };
    }
}


