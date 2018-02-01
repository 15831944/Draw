#pragma once

#define MIDAS_SDK

#include "HeaderPre.h"

#define INIT_DEFAULT_COOLBUTTON(_Button_, _BMP_OFF, _BMP_ON_)			\
{	                                                                    \
	if( _Button_.GetSafeHwnd() )                                        \
	{                                                                   \
	_Button_.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_SEMIFLAT;       \
	_Button_.m_bDrawFocus = FALSE;                                  \
	_Button_.SetImage (_BMP_OFF);									\
	_Button_.SetCheckedImage (_BMP_ON_);							\
	}                                                                   \
}

#define CHECK_OFF_COOLBUTTON(_Button_, _Text_, _BMP_OFF)				\
{	                                                                    \
	if( _Button_.GetSafeHwnd() )                                        \
	{                                                                   \
	_Button_.SetCheck(FALSE);                                       \
	_Button_.SetImage(_BMP_OFF);									\
	_Button_.SetWindowText(_Text_);                                 \
	}                                                                   \
}

#define CHECK_ON_COOLBUTTON(_Button_, _Text_, _BMP_OFF)                 \
{                                                                       \
	if( _Button_.GetSafeHwnd() )                                        \
	{                                                                   \
	_Button_.SetCheck(TRUE);                                        \
	_Button_.SetImage(_BMP_OFF);									\
	_Button_.SetWindowText(_Text_);                                 \
	}                                                                   \
}

namespace mit
{
    namespace frx
    {
        class __MY_EXT_CLASS__ MCoolButton : public CBCGPButton
        {
        public:
            MCoolButton();
            virtual ~MCoolButton();
			MCoolButton( const MCoolButton &S );
			MCoolButton& operator=( const MCoolButton &S );
            void SetOnlyImage(BOOL bSet);
            void SetImage(UINT uImageId);
			void SetImageKeepString(UINT uImageId);
            void SetImageID(UINT uBmpOff, UINT uBmpOn, UINT uBmpCheck);

			void SetPushButton(CString strText);
			void SetPopButton(CString strText, BOOL bCheck);

            BOOL IsSel() const { return m_bSel; }
            void SetSel(BOOL bSel = TRUE) { m_bSel = bSel; }
            void ResetSel() { m_bSel = FALSE; }
            void PopBtn();
            void PopBtn(LPCTSTR lpszText);
            void PushBtn();
            void PushBtn(LPCTSTR lpszText);

        public:
            virtual BOOL PreTranslateMessage(MSG* pMsg);
        private:
            BOOL m_bSel;
            UINT m_uBmpCheck;
            UINT m_uBmpOff;
            BOOL m_bOnlyImage;
        };
    }
}
using namespace mit::frx;

#include "HeaderPost.h"