#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MLayeredSliderCtrl : public CBCGPCaptionButton
		{
			friend class MLayeredMiniFrameWnd;
			friend class MLayeredMultiMiniFrameWnd;

			DECLARE_DYNCREATE(MLayeredSliderCtrl)
		public:
			MLayeredSliderCtrl ( int nWidth = 100, DWORD dwStyle = 0);	// TBS_**** styles

			virtual ~MLayeredSliderCtrl();

			// Attributes
		public:
			void MakeTransParent(BYTE factor);
			void SetParentMiniFrame(CBCGPMiniFrameWnd* pParent) { m_pParentMiniFrame = pParent; }
			void SetRange (int nMin, int nMax);

			int GetRangeMin () const	{	return m_nMin;	}
			int GetRangeMax () const	{	return m_nMax;	}

			void SetPos (int nPos, BOOL bRedraw = TRUE);

			int GetPos () const			{	return m_nPos;	}

			int GetPageSize () const	{	return m_nPageSize;	}
			void SetPageSize (int nPageSize);

			void SetZoomButtons (BOOL bSet = TRUE);
			BOOL HasZoomButtons () const
			{
				return m_bZoomButtons;
			}

			BOOL IsVert () const
			{
				return (m_dwStyle & TBS_VERT);
			}

			BOOL IsThumbLeftTop () const
			{
				return (m_dwStyle & TBS_BOTH) || (m_dwStyle & TBS_LEFT);
			}

			BOOL IsThumbRightBottom () const
			{
				return (m_dwStyle & TBS_BOTH) || ((m_dwStyle & TBS_LEFT) == 0);
			}

			DWORD GetStyle () const
			{
				return m_dwStyle;
			}

			int GetWidth () const
			{
				return m_nWidth;
			}

			virtual CRect GetRect () const
			{ 
				return m_rect;
			}

			void SetRect(CRect rect) 
			{
				m_rect = rect;
				m_rectSlider = rect;
				SetThumbRect();
			}

			// Operations
		protected:
			void CommonInit ();
			void SetThumbRect ();

			int GetPosFromPoint (CPoint pt);

			int GetHitTest (CPoint point) const;	

			// Overrides
		public:
			virtual void Redraw ();
			virtual void OnDraw (CDC* pDC, BOOL bActive, BOOL bHorz, BOOL bMaximized, BOOL bDisabled);
			virtual CSize GetRegularSize (CDC* pDC);

			virtual BOOL IsHighlighted () const
			{
				return m_bIsHighlighted;
			}

			virtual BOOL IsFocused () const
			{
				return m_bIsFocused;
			}

			virtual BOOL IsPressed () const
			{
				return m_bIsPressed;
			}

			virtual BOOL IsDisabled () const
			{
				return m_bIsDisabled;
			}

		protected:
			virtual int DoDrawText (CDC* pDC, const CString& strText, CRect rectText, UINT uiDTFlags,
				COLORREF clrText = (COLORREF)-1);

			virtual void OnLButtonDown (CPoint point);
			virtual void OnLButtonUp (CPoint point);
			virtual void OnMouseMove (CPoint point);

			virtual BOOL IsAutoRepeatMode (int& nDelay /* ms */) const;
			virtual BOOL OnAutoRepeat ();

			virtual BOOL OnProcessKey (UINT nChar);

			virtual BOOL IsWholeRowHeight () const
			{
				return IsVert ();
			}

			virtual BOOL IsCustomIconAllowed() const	
			{	
				return FALSE;	
			}

			// Attributes
		protected:
			CBCGPMiniFrameWnd* m_pParentMiniFrame;
			int		m_nMin;
			int		m_nMax;
			int		m_nPos;
			int		m_nPageSize;
			BOOL	m_bZoomButtons;
			int		m_nWidth;
			DWORD	m_dwStyle;
			CRect   m_rect;

			CRect	m_rectZoomOut;
			CRect	m_rectZoomIn;
			CRect	m_rectSlider;
			CRect	m_rectThumb;
			CRect	m_rectLabel;

			CString	m_strText;

			BOOL    m_bIsDisabled;
			BOOL    m_bIsFocused;
			BOOL	m_bIsHighlighted;
			BOOL	m_bIsPressed;
			int		m_nHighlighted;	// -1 - none, 0 - thumb, 1 -Zoom In, 2 - Zoom Out
			int		m_nPressed;		// -1 - none, 0 - thumb, 1 -Zoom In, 2 - Zoom Out
			CPoint	m_ptCapture;
		};
	}
}

#include "HeaderPost.h"


