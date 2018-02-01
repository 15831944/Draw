#pragma once

#define MIDAS_SDK

#include "HeaderPre.h"

namespace mit
{
    namespace frx
    {
        class __MY_EXT_CLASS__ MTextProgressCtrl : public CBCGPRibbonProgressBar
        {
        public:
            MTextProgressCtrl();
			MTextProgressCtrl(UINT nID, int nWidth = 90, int nHeight = 22);
            virtual ~MTextProgressCtrl();

        public:
			int			StepIt();
			int			OffsetPos(int nPos);
			int			SetStep(int nStep);
			void		SetForeColour(COLORREF col);
			void		SetBkColour(COLORREF col);
			void		SetTextForeColour(COLORREF col);
			void		SetTextBkColour(COLORREF col);
			COLORREF	GetForeColour();
			COLORREF	GetBkColour();
			COLORREF	GetTextForeColour();
			COLORREF	GetTextBkColour();
			void		SetShowText(BOOL bShow);
			void		SetFontData(CString strFaceName, int nWeight, BOOL bItalic, BOOL bUnderline);
			void		SetWidth(int iWidth);
			int			GetWidth();
			void		SetHeight(int iHeight);
			int			GetHeight();

            // Overrides
		protected:
			virtual void OnDraw(CDC* pDC);

		protected:
			int	     m_iStepSize;
			BOOL	 m_bShowText;
			int		 m_iBarWidth;
			COLORREF m_clrFore, m_clrBk, m_clrTextFore, m_clrTextBk;
			CString  m_strFaceName;
			int		 m_iWeight;
			BOOL     m_bItalic;
			BOOL     m_bUnderline;
        };
    }
}

#include "HeaderPost.h"
