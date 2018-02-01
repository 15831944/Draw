#pragma once

#define MIDAS_SDK

#include "../MIT_lib/IUnitListener.h"

// 일단 빌드에러만 안나게 만들어서 추가한 것임. 
// 나중에 소스 옮길 때 이 파일은 덮어쓰면 안됨. 

#include "HeaderPre.h"

namespace mit
{
    namespace frx
    {
        class MDocBase;
        class MPropertiesWnd;
        class MPropListCtrl;

        class __MY_EXT_CLASS__ IPropertySet : public mit::lib::IUnitListener
        {
        public:
            IPropertySet( mit::frx::MDocBase* pDoc, MIterator itr, USHORT usDataType );
            virtual ~IPropertySet();

            // pure virtual function
            virtual void ShowProperty()  = 0;
            virtual void ApplyProperty() = 0;
            virtual void OnPropertyChanged( CBCGPProp* pProp, DWORD_PTR dwData ){}
            virtual void CalProp(){}

            // unit change event function
            virtual const CDocument* GetUnitListenerDoc();
            virtual void OnUnitChanged();

        protected:
            MPropListCtrl* GetPropList();
            ////////////////////////////////////////////////////////////////////////
            // Properties Grid 생성 관련 함수
            void RemoveAllProperties();
            void ResetProperty();
            void AdjustLayout();
            void SetInfo( DWORD_PTR dwpType );

            CBCGPProp* AddTitle( CBCGPProp* pParent, LPCTSTR lpszTitle );
            CBCGPProp* AddGeneralProperty
                (
                CBCGPProp*  pParent,
                LPCTSTR	  lpszName,
                _variant_t var,
                LPCTSTR	  lpszComment,
                BOOL       bEditable = FALSE,
                DWORD_PTR  dwData = 0
                );
            CBCGPProp* AddGeneralPropertyWithOption
                (
                CBCGPProp*  pParent,
                LPCTSTR	  lpszName,
                int		  nNumberOfOption,
                LPCTSTR*	  pOptions,
                int        nInitialIdx,
                LPCTSTR	  lpszComment,
                DWORD_PTR  dwData = 0
                );
            CBCGPProp* AddBooleanProperty
                (
                CBCGPProp*  pParent,
                LPCTSTR	  lpszName,
                bool       bInitialValue,
                LPCTSTR	  lpszComment,
                DWORD_PTR  dwData = 0
                );
            CBCGPProp* AddColorProperty
                (
                CBCGPProp*  pParent,
                LPCTSTR	  lpszName,
                COLORREF&  cInitialColor,
                LPCTSTR	  lpszComment,
                DWORD_PTR  dwData = 0
                );
            CBCGPProp* AddButtonProperty
                (
                CBCGPProp*  pParent,
                LPCTSTR	  lpszName,
                LPCTSTR	  lpszButtonName,
                LPCTSTR	  lpszComment,
                DWORD_PTR  dwData = 0
                );
            CBCGPProp* AddSpinProperty
                (
                CBCGPProp*  pParent,
                LPCTSTR	  lpszName,
                _variant_t var,
                LPCTSTR	  lpszComment,
                int		  min,
                int		  max,
                DWORD_PTR  dwData = 0
                );
            CBCGPProp* AddCheckBoxProperty
                (
                CBCGPProp*  pParent,
                LPCTSTR	  lpszName,
                bool		  bCheck,
                LPCTSTR	  lpszComment,
                DWORD_PTR  dwData = 0
                );

            CBCGPProp* AddCheckEditBoxProperty
                (
                CBCGPProp*  pParent,
                LPCTSTR	  lpszName,
                bool	      bCheck,
                _variant_t var,
                LPCTSTR	  lpszComment,
                DWORD_PTR  dwData = 0
                );
            CBCGPProp* AddIconListProperty
                (
                CBCGPProp*    pParent,
                LPCTSTR	    lpszName,
                CImageList&	imgList,
                int			initList,
                CStringList&	titleList,
                LPCTSTR		lpszComment,
                DWORD_PTR	dwData = 0
                );
            void ShowApplyBtn(BOOL bShow = TRUE);

            ////////////////////////////////////////////////////////////////////////
            // Properties Grid Item Parsing
            void ExtractInt(CBCGPProp* pSrc, int& nDest);
            void ExtractUINT(CBCGPProp* pSrc, UINT& unDest);
            void ExtractColor(CBCGPProp* pSrc, COLORREF& cDest);
            void ExtractDouble(CBCGPProp* pSrc, double& dDest);
            void ExtractString(CBCGPProp* pSrc, CString& strDest);
            void ExtractBoolean(CBCGPProp* pSrc, BOOL& bDest);
            void ExtractOption(CBCGPProp* pSrc, int& iDest);
            void ExtractKey(CBCGPProp* pSrc, MKey& kDest);

        protected:
            MPropertiesWnd* GetPropWnd();
            MPropertiesWnd* m_pPropWnd;
            //mit::frx::MDocBase*		m_pDoc;
            MIterator		m_itr;
            USHORT			m_usDataType;
        };
    }
}
using namespace mit::frx;

#include "HeaderPost.h"