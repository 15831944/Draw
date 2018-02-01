#pragma once

#define MIDAS_SDK

#include "MBaseDockWnd.h"
#include "MCoolButton.h"

#include "MLayeredToolBar.h"
#include "MLayeredPropList.h"

#include "HeaderPre.h"

namespace mit
{
    namespace frx
    {
		class __MY_EXT_CLASS__ MPropertiesToolBar : public mit::frx::MLayeredToolbar
        {
        public:
            virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
            {
                MLayeredToolbar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
            }

            virtual BOOL AllowShowOnList() const { return FALSE; }
        };

        class __MY_EXT_CLASS__ MApplyButton : public MCoolButton
        {
        public:
            static unsigned int WM_APPLYBUTTON_CLICKED;
        public:
            MApplyButton();
            virtual ~MApplyButton();

            // Generated message map functions
        protected:
            //{{AFX_MSG(CPropertiesViewBar)
            afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
            //}}AFX_MSG
            DECLARE_MESSAGE_MAP()
        };

        class IPropertySet;
        class MDocBase;
		class __MY_EXT_CLASS__ MPropListCtrl : public mit::frx::MLayeredPropList
        {
        public:
            MPropListCtrl();
            virtual ~MPropListCtrl();
            virtual void OnPropertyChanged(CBCGPProp* pProp) const;
            virtual BOOL EditItem(CBCGPProp* pProp, LPPOINT lptClick = NULL);

            void ResetInfo();
            void SetInfo( DWORD_PTR dwpType, const MIterator itr, const USHORT usDataType );
            DWORD_PTR		GetType()	{ return m_dwpType; }
            MIterator		GetIterator();
            void SetPropertySet( IPropertySet* pSet );

        protected:
            MIterator		m_itr;
            DWORD_PTR		m_dwpType;
            USHORT			m_usDataType;
            IPropertySet*	m_pPropertySet;
        };

        class __MY_EXT_CLASS__ MPropertiesWnd : public MBaseDockWnd
        {
            DECLARE_DYNCREATE(MPropertiesWnd)
            // 생성입니다.
        public:
            MPropertiesWnd();

            // 특성입니다.
        public:
            void SetVSDotNetLook(BOOL bSet)
            {
                m_wndPropList.SetVSDotNetLook(bSet);
                m_wndPropList.SetGroupNameFullWidth(bSet);
            }

        public:
			virtual void AdjustLayout();
			virtual mit::frx::MPropListCtrl* GetPropList() { return &m_wndPropList; }
            virtual void SetMode( int nMode = 0 );
            virtual int  GetMode() { return m_nMode; }
            virtual void SetPropertySet( IPropertySet* pSet );
			virtual void OnChangeLanguage();
			virtual BOOL CreatePropList();
			virtual void SetPropListFont();
			virtual void ShowApplyBtn(BOOL bShow = TRUE) { };

        protected:
            CFont			m_fntPropList;
            CComboBox		m_wndObjectCombo;
			mit::frx::MPropListCtrl m_wndPropList;
			mit::frx::IPropertySet*	m_pPropertySet;
            int m_nMode;

            // 구현입니다.
        public:
            virtual ~MPropertiesWnd();

        protected:
            LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
            afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
            afx_msg void OnSize(UINT nType, int cx, int cy);
            afx_msg void OnSetFocus(CWnd* pOldWnd);
            afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
            DECLARE_MESSAGE_MAP()

            ////////////////////////////////////////////////////////////////////////
            // Properties Grid 생성 관련 함수
        public:
            virtual void RemoveAllProperties();
            virtual void DefaultProperties();
            virtual void ResetProperty();
            virtual CBCGPProp* AddTitle( CBCGPProp* pParent, LPCTSTR lpszTitle );
            virtual CBCGPProp* AddGeneralProperty
                (
                CBCGPProp*  pParent,
                LPCTSTR	lpszName,
                _variant_t var,
                LPCTSTR	lpszComment,
                DWORD_PTR  dwData,
                BOOL       bEditable = FALSE
                );
            virtual CBCGPProp* AddGeneralPropertyWithOption
                (
                CBCGPProp*  pParent,
                LPCTSTR	lpszName,
                int		nNumberOfOption,
                LPCTSTR*	pOptions,
                int        nInitialIdx,
                LPCTSTR	lpszComment,
                DWORD_PTR  dwData
                );
            virtual CBCGPProp* AddBooleanProperty
                (
                CBCGPProp*  pParent,
                LPCTSTR	lpszName,
                bool       bInitialValue,
                LPCTSTR	lpszComment,
                DWORD_PTR  dwData
                );
            virtual CBCGPProp* AddColorProperty
                (
                CBCGPProp*  pParent,
                LPCTSTR	lpszName,
                COLORREF&	cInitialColor,
                LPCTSTR	lpszComment,
                DWORD_PTR  dwData
                );
            virtual CBCGPProp* AddButtonProperty
                (
                CBCGPProp*  pParent,
                LPCTSTR	lpszName,
                LPCTSTR	lpszButtonName,
                LPCTSTR	lpszComment,
                DWORD_PTR  dwData
                );
            virtual CBCGPProp* AddSpinProperty
                (
                CBCGPProp*  pParent,
                LPCTSTR	lpszName,
                _variant_t var,
                LPCTSTR	lpszComment,
                DWORD_PTR  dwData,
                int		min,
                int		max
                );
            virtual CBCGPProp* AddCheckBoxProperty
                (
                CBCGPProp*	pParent,
                LPCTSTR		lpszName,
                bool		bCheck,
                LPCTSTR		lpszComment,
                DWORD_PTR	dwData
                );
            virtual CBCGPProp* AddCheckEditBoxProperty
                (
                CBCGPProp*	pParent,
                LPCTSTR		lpszName,
                bool		bCheck,
                _variant_t	var,
                LPCTSTR		lpszComment,
                DWORD_PTR	dwData
                );
            virtual CBCGPProp* AddIconListProperty
                (
                CBCGPProp*		pParent,
                LPCTSTR	    lpszName,
                CImageList&	imgList,
                int			initList,
                CStringList&	titleList,
                LPCTSTR		lpszComment,
                DWORD_PTR		dwData
                );
        };
    }
}
using namespace mit::frx;

#include "HeaderPost.h"