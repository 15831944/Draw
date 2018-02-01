#pragma once

#define MIDAS_SDK

#include "MCoolButton.h"

#include "HeaderPre.h"

#define PROP_HAS_LIST	0x0001
#define PROP_HAS_BUTTON	0x0002
#define PROP_HAS_SPIN	0x0004

namespace mit
{
	namespace lib
	{
		class MUnitCtrl;
	}

    namespace frx
    {
		class MStaticProp;

		class MPropEdit : public CBCGPEdit
		{
			friend class MStaticProp;

		public:
			MPropEdit(MStaticProp* pParent);
			virtual ~MPropEdit() {}

		protected:
			mit::frx::MStaticProp* m_pParentProp;

		public:
			virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
				LPCTSTR lpszWindowName, DWORD dwStyle,
				const RECT& rect,
				CWnd* pParentWnd, UINT nID,
				LPVOID lpParam = NULL);

			virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
				LPCTSTR lpszWindowName, DWORD dwStyle,
				int x, int y, int nWidth, int nHeight,
				HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam = NULL);
		};

		class MPropComboBox : public CBCGPComboBox
		{
			friend class MStaticProp;

		public:
			MPropComboBox(MStaticProp* pParent);
			virtual ~MPropComboBox() {}

		protected:
			mit::frx::MStaticProp* m_pParentProp;

		public:
			virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
				LPCTSTR lpszWindowName, DWORD dwStyle,
				const RECT& rect,
				CWnd* pParentWnd, UINT nID,
				LPVOID lpParam = NULL);

			virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
				LPCTSTR lpszWindowName, DWORD dwStyle,
				int x, int y, int nWidth, int nHeight,
				HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam = NULL);
		};

        // Static Prop
        class __MY_EXT_CLASS__ MStaticProp : public CBCGPProp
        {
        public:
			MStaticProp(const CString& strGroupName, DWORD_PTR dwData = 0,
				BOOL bIsValueList = FALSE);
			MStaticProp(const CString& strName, const _variant_t& varValue, 
				LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
				LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL,
				LPCTSTR lpszValidChars = NULL);
			MStaticProp(const CString& strName, UINT nID, const _variant_t& varValue, 
				LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
				LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL,
				LPCTSTR lpszValidChars = NULL);
            virtual ~MStaticProp();

		public:
			CBCGPPropList* GetParentPropList() { return m_pWndList; }

		public:
			virtual void OnDrawName (CDC* pDC, CRect rect);
			virtual void OnDrawValue (CDC* pDC, CRect rect);
			virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);
        };

		// MUnitProp
		class __MY_EXT_CLASS__ MUnitProp : public MStaticProp
		{
			typedef mit::MList<MUnitProp*>	tu_list;

		public:
			MUnitProp(const CString& strName, const _variant_t& varValue, LPCTSTR lpszDescr=NULL, DWORD_PTR dwData=0);
			virtual ~MUnitProp();

		public:
			static void SetStatic(mit::lib::MUnitCtrl* pUnitCtrl);
			
		public:
			mit::lib::MUnitCtrl* GetUnitCtrl() { return m_pUnitCtrl; }
			void SetUnitType(mit::lib::MUnitCtrl* pUnitCtrl, int iUnitType);

			void SetUnitWidthRadio(double dRadio) { m_dUnitWitdhRadio = dRadio; }

		protected:
			static tu_list m_slTU;

		protected:
			CString		m_strUnit;
			double		m_dUnitWitdhRadio;  //  Unit 부분의 Width가 전체에서 차지하는 비율.			

		protected:
			int	m_iUnitType;
			mit::lib::MUnitCtrl*	m_pUnitCtrl;
			void SetStaticText();
			void SetTextUnit(CString& strUnit);

			// Override 
		public:
			virtual void OnDrawValue (CDC* pDC, CRect rect);
			virtual void AdjustInPlaceEditRect (CRect& rectEdit, CRect& rectUnit);
			virtual void AdjustButtonRect ();
			virtual CComboBox* CreateCombo (CWnd* pWndParent, CRect rect);
			virtual CSpinButtonCtrl* CreateSpinControl (CRect rectSpin);
			virtual BOOL OnEndEdit ();
			virtual BOOL IsButtonVisible() const;

			// 추가된 virtual 함수.
		public:
			virtual void OnDrawSpinButton(CDC* pDC);
		};


		//////////////////////////////////////////////////////////////////////////
		// Button Prop
		class __MY_EXT_CLASS__ MButtonProp : public MStaticProp
		{
		public:
			MButtonProp(const CString& strName, const _variant_t& varValue, LPCTSTR lpszDescr=NULL, DWORD_PTR dwData=0);
			virtual ~MButtonProp();

		protected:
			virtual BOOL HasButton () const	{	return TRUE;	}
			virtual void OnClickButton (CPoint point);

		};

        class MSliderProp;
        class __MY_EXT_CLASS__ MPropSliderCtrl : public CSliderCtrl
        {
        public:
            MPropSliderCtrl(MSliderProp* pProp);
            virtual ~MPropSliderCtrl();

        protected:
            MSliderProp* m_pProp;

            // Generated message map functions
        protected:
            //{{AFX_MSG(CPropSliderCtrl)
            afx_msg void HScroll (UINT nSBCode, UINT nPos);
            //}}AFX_MSG
            DECLARE_MESSAGE_MAP()
        };

        // 범위를 0~100로 가지고 %를 위치값으로 입력 받는 슬라이더
        class __MY_EXT_CLASS__ MSliderProp  : public MStaticProp
        {
        public:
            MSliderProp(const CString& strName, const _variant_t& varValue,
                LPCTSTR lpszDescr=NULL, DWORD_PTR dwData=0);
            virtual ~MSliderProp();

            virtual void OnDrawValue(CDC* pDC, CRect rect);
            // setting slider
            void  SetSlider(int nInit);
            /******************************************************************
            int nInit : slider thumb이 초기에 위치하게 되는 값 (%)
            ******************************************************************/

            int GetSliderPos();
            void SetSliderPos(int nPos);

            virtual void  UpdatePropList();
            virtual void  ShowControl(BOOL bShow);

            virtual BOOL HasButton () const						{	return TRUE;	}

        protected:
            MPropSliderCtrl* m_pSlider;
        };

        // combo box customizing
        class __MY_EXT_CLASS__ MComboBoxProp : public MStaticProp
        {
        public:
            MComboBoxProp( const CString& strName, const _variant_t& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0 );

        protected:
            int m_nCurSel;

        public:
            virtual void OnSelectCombo();
            virtual BOOL OnDblClk(CPoint point); 

        public:
            int GetCurrentSelect()  { return m_nCurSel; }
        };

        // CIconCombo window
        class __MY_EXT_CLASS__ MIconCombo : public CComboBox
        {
            // Construction
        public:
            MIconCombo(CBCGPToolBarImages& imageListIcons, CStringList& lstIconNames);
            virtual ~MIconCombo();

        protected:
            CBCGPToolBarImages&	m_imageListIcons;
            CStringList&		m_lstIconNames;

            // Generated message map functions
        protected:
            //{{AFX_MSG(CIconCombo)
            afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
            afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
            //}}AFX_MSG

            DECLARE_MESSAGE_MAP()
        };

        class __MY_EXT_CLASS__ MIconListProp : public MStaticProp
        {
        public:
            MIconListProp(
                const CString& strName,
                const CImageList& imageListIcons,
                int nSelectedIcon,
                CStringList* plstIconNames = NULL,
                LPCTSTR lpszDescr = NULL,
                DWORD_PTR dwData = 0
                );

        protected:
            virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);
            virtual CComboBox* CreateCombo (CWnd* pWndParent, CRect rect);
            virtual void OnDrawValue (CDC* pDC, CRect rect);

            CBCGPToolBarImages	m_imageListIcons;
            CStringList			m_lstIconNames;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////
        // Property Grid Color Property
        ////////////////////////////////////////////////////////////////////////////////////////////
        class __MY_EXT_CLASS__ MOptionColorProp : public CBCGPColorProp
        {
            DECLARE_DYNAMIC(MOptionColorProp)

            friend class MPropList;
			
        public:
            MOptionColorProp(const CString& strName, const COLORREF& color, CPalette* pPalette = NULL, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0);

            virtual ~MOptionColorProp();
        public:
            virtual BOOL OnEdit(LPPOINT lptClick);
            virtual void OnClickName(CPoint /*point*/);
            virtual BOOL OnClickValue(UINT uiMsg, CPoint point);
        protected:
            virtual void OnDestroyWindow();

        protected:
            BOOL	m_bInitCtrl;
        };

        // Name에 check box가 나타나는 콘트롤 
        class __MY_EXT_CLASS__ MCheckBoxProp : public MStaticProp
        {
        public:
            MCheckBoxProp( const CString& strName, BOOL bCheck, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0 );

        protected:
            virtual BOOL OnEdit(LPPOINT lptClick)				{	return FALSE;	}
            virtual void OnDrawButton (CDC* pDC, CRect rectButton)	{}
            virtual void OnDrawValue(CDC* pDC, CRect rect);

            virtual BOOL PushChar (UINT nChar);
            virtual void OnDrawCheckBox (CDC * pDC, CRect rectCheck, BOOL bChecked);
            virtual void OnDrawName (CDC* pDC, CRect rect);
            virtual void OnClickName (CPoint point);
            virtual BOOL OnDblClk(CPoint point);

        protected:
            CRect	m_rectCheck;
        };

        // Name에 check box가 Value에 수정 가능한 edit box가 나타나는 콘트롤 
        class __MY_EXT_CLASS__ MCheckEditBoxProp : public MStaticProp
        {
        public:
            MCheckEditBoxProp( const CString& strName, BOOL bCheck, _variant_t& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0 );

            BOOL	GetCheck()	{ return m_bCheck; }
            void	SetCheck( BOOL bCheck )	{ m_bCheck = bCheck; }
        protected:
            virtual void OnDrawButton (CDC* pDC, CRect rectButton)	{}

            virtual BOOL PushChar (UINT nChar);
            virtual void OnDrawCheckBox (CDC * pDC, CRect rectCheck, BOOL bChecked);
            virtual void OnDrawName (CDC* pDC, CRect rect);
            virtual void OnClickName (CPoint point);

        protected:
            CRect	m_rectCheck;
            BOOL	m_bCheck;
        };

		// Check + Unit + ( Edit or Combo or Spin )
		class __MY_EXT_CLASS__ MCheckUnitProp : public MUnitProp
		{
		public:
			MCheckUnitProp( const CString& strName, BOOL bCheck, _variant_t& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0 );

			BOOL	GetCheck()	{ return m_bCheck; }
			void	SetCheck( BOOL bCheck )	{ m_bCheck = bCheck; }
		protected:
			virtual BOOL PushChar (UINT nChar);
			virtual void OnDrawCheckBox (CDC * pDC, CRect rectCheck, BOOL bChecked);
			virtual void OnDrawName (CDC* pDC, CRect rect);
			virtual void OnClickName (CPoint point);

		protected:
			CRect	m_rectCheck;
			BOOL	m_bCheck;
		};

        class __MY_EXT_CLASS__ MSpinCtrlProp : public MStaticProp
        {
        public:
            MSpinCtrlProp(const CString& strName, const _variant_t& varValue, int nMinValue, int nMaxValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0 );

            virtual CSpinButtonCtrl* CreateSpinControl(CRect rectSpin);
            virtual BOOL OnUpdateValue();
            virtual void OnClickName(CPoint /*point*/);
            virtual BOOL OnClickValue(UINT uiMsg, CPoint point);
        
        private:
            int		m_nMinValue;
            int		m_nMaxValue;
        };

    }
}

#include "HeaderPost.h"
