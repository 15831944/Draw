#pragma once

#include "HeaderPre.h"

#define NM_GL_SIZE_CHANGED  1
#define NM_GL_EXECUTE       2
#define NM_GL_HELP          3
#define NM_GL_INTERNET      4

namespace mit
{
	namespace frx
	{
		struct __MY_EXT_CLASS__ NMHDR_GL_SIZE_CHANGED : public NMHDR
		{
			int cx;
			int cy;
		};

		typedef struct __MY_EXT_CLASS__ NMHDR_GL_EXECUTE : public NMHDR
		{
			CString strItem;
		} NMHDR_GL_HELP, NMHDR_GL_INTERNET;

		struct TGroupListItem
		{
			int idx;
			CString strName;

			TGroupListItem()
			{
				idx = 0;
				strName = _T("");
			}

			TGroupListItem(int idx, CString strName)
			{
				this->idx = idx;
				this->strName = strName;
			}

			TGroupListItem(const TGroupListItem& src)
			{
				idx = src.idx;
				strName = src.strName;
			}

			TGroupListItem& operator=(const TGroupListItem& rhs)
			{
				idx = rhs.idx;
				strName = rhs.strName;
				return *this;
			}
		};

		struct TGroupListGroup
		{
			CString strName;
			int nSelectedItem;
			int nScroll;
			CArray<TGroupListItem> items;

			TGroupListGroup( CString strName = _T("") )
			{
				this->strName = strName;
				nSelectedItem = -1;
				nScroll = -1;
			}

			void AddItem(int idx, const CString& strItemName)
			{
				items.Add(TGroupListItem(idx, strItemName));
				if (nSelectedItem == -1) 
				{
					nSelectedItem = 0;
					nScroll = 0;
				}
			}

			void RemoveItemAll()
			{
				items.RemoveAll();
				nSelectedItem = -1;
				nScroll = -1;
			}
		};

		enum HitTestInfoType
		{
			HIT_NONE, 
			HIT_ITEM, 
			HIT_ITEM_EMPTY, 
			HIT_SCROLL_BAR, 
			HIT_SCROLL_PGUP, 
			HIT_SCROLL_PGDN,
			HIT_GROUP_EXECUTE,
			HIT_GROUP_EXTEND
		};

		struct THitTestInfo
		{
			HitTestInfoType type;
			POSITION pos;
			CRect rect;

			// type == HIT_ITEM 일때만 사용
			int idx;

			THitTestInfo()
			{
				type = HIT_NONE;
				pos = NULL;
				rect.SetRect(0,0,0,0);

				idx = -1;
			}
		};

		class __MY_EXT_CLASS__ CGroupList : public CWnd
		{
			DECLARE_DYNCREATE(CGroupList)

		public:
			CGroupList();
			virtual ~CGroupList();

		protected:
			enum { IDT_FADE_EXECUTE = 1, IDT_FADE_EXTEND, IDT_FADE_GROUP };

		protected:
			TRACKMOUSEEVENT m_trackMouse;
			BOOL m_bMouseOver;
			CPoint m_ptMouse;

		protected:
			THitTestInfo m_hitInfo;
			BOOL m_bMouseDrag;
			CPoint m_ptScrollBarMouseDragStart;
			CPoint m_ptScrollMouseDragStart;
			BOOL m_bLButtonClick;
			BOOL m_bNeedHitTest;

		protected:
			CImageList* m_pImageList;
			POSITION m_posActiveGroup;
			CList<TGroupListGroup*> m_listGroup;

		protected:
			int m_nItemHeight;
			int m_nItemCount;
			BOOL m_bFitItemCount;

		protected:
			COLORREF m_clrBorder;

		protected:
			COLORREF m_clrListBack;
			COLORREF m_clrListSelectBorder;
			COLORREF m_clrListSelectBack1;
			COLORREF m_clrListSelectBack2;
			COLORREF m_clrListText;
			COLORREF m_clrScrollBarBack;
			COLORREF m_clrScrollBar;
			COLORREF m_clrScrollBarOver;
			int m_nScrollWidth;
			int m_nScrollBarWidth;

		protected:
			COLORREF m_clrGroupBack;
			COLORREF m_clrGroupText;
			int m_nGroupDeactiveAlpha;
			int m_nExtendBtnWidth;
			int m_nExtendBtnThick;

		protected:
			HFONT m_hFont;
			BOOL m_bSuspendUpdate;
			int m_nHeightBeforeUpdate;

			// Setter
			// jpahn: 얘들은 OnCreate 에서 혹은 이전에만 호출
			//        중간에 바꾸면 실시간으로 반영. 이런거 고려하지 않았음.
		public:
			void SetItemHeight(int nItemHeight) { m_nItemHeight = nItemHeight; }
			//void SetItemCount(int nItemCount) { m_nItemHeight = nItemCount; } 밑에 있다.
			void SetFitItemCount(BOOL bFitItemCount) { m_bFitItemCount = bFitItemCount; }
			void SetScrollWidth(int nScrollWidth) { m_nScrollWidth = nScrollWidth; }
			void SetScrollBarWidth(int nScrollBarWidth) { m_nScrollBarWidth = nScrollBarWidth; }
			void SetExtendBtnWidth(int nExtendBtnWidth) { m_nExtendBtnWidth = nExtendBtnWidth; }
			void SetExtendBtnThick(int nExtendBtnThick) { m_nExtendBtnThick = nExtendBtnThick; }
			void SetBorder(COLORREF clrBorder) { m_clrBorder = clrBorder; }
			void SetListBack(COLORREF clrListBack) { m_clrListBack = clrListBack; }
			void SetListSelectBorder(COLORREF clrListSelectBorder) { m_clrListSelectBorder = clrListSelectBorder; }
			void SetListSelectBack1(COLORREF clrListSelectBack1) { m_clrListSelectBack1 = clrListSelectBack1; }
			void SetListSelectBack2(COLORREF clrListSelectBack2) { m_clrListSelectBack2 = clrListSelectBack2; }
			void SetListText(COLORREF clrListText) { m_clrListText = clrListText; }
			void SetGroupBack(COLORREF clrGroupBack) { m_clrGroupBack = clrGroupBack; }
			void SetGroupText(COLORREF clrGroupText) { m_clrGroupText = clrGroupText; }
			void SetGroupDeactiveAlpha(int nGroupDeactiveAlpha) { m_nGroupDeactiveAlpha = nGroupDeactiveAlpha; }
			void SetScrollBarBack(COLORREF clrScrollBarBack) { m_clrScrollBarBack = clrScrollBarBack; }
			void SetScrollBar(COLORREF clrScrollBar) { m_clrScrollBar = clrScrollBar; }
			void SetScrollBarOver(COLORREF clrScrollBarOver) { m_clrScrollBarOver = clrScrollBarOver; }

			// Create
		public:
			BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

			// Group
		public:
			POSITION AddGroup(const CString& strName);
			void RemoveGroup(POSITION pos);
			void RemoveGroupAll();
			void SetActiveGroup(POSITION pos);
			POSITION GetActiveGroup() const { return m_posActiveGroup; }
			CString GetActiveGroupName() const;
			BOOL SetActiveGroupName(const CString& strName);
			BOOL IsNoActiveGroup() const { return (m_posActiveGroup == NULL); }
			int GetGroupCount() const { return (int)m_listGroup.GetSize(); }

			// Item
		public:
			void SetImageList(CImageList* pImageList) { m_pImageList = pImageList; }
			void AddItem(POSITION pos, const CString& strItemName, int idx);
			void RemoveItemAll(POSITION pos);
			BOOL IsEmpty() const;
		protected:
			virtual CString GetExecuteName(const CString& strItemName) const { return strItemName; }

			// Update
		public:
			void BeginUpdate();
			void EndUpdate();

			// Size
		protected:
			void AdjustSize();

			// Height
		public:
			void SetItemCount(int nItemCount);
			int GetItemCount() const { return m_nItemCount; }
		protected:
			int GetCalcItemCount() const;
			int GetHeight() const { return m_nItemHeight * GetCalcItemCount() + (min(GetCalcItemCount(), GetGroupCount()) - 1); }
			int GetListItemCount() const { return max(GetCalcItemCount() - (GetGroupCount() - 1), 1); }
			int GetListHeight() const { return m_nItemHeight * GetListItemCount(); }

			// Rect
		protected:
			int GetListGroupRect(POSITION pos, CRect& rectGroup) const;
			int GetListGroupRect(POSITION pos, int y, CRect& rectGroup) const;
			void GetGroupRect(const CRect& rectGroup, CRect& rectExecute, CRect& rectExtend) const;
			void GetListRect(const CRect& rectGroup, CRect& rectItems, CRect& rectScroll) const;
			void GetListItemRect(int idx,const CRect& rectItems, CRect& rectItem) const;
			void GetListScrollRect(const CRect& rectScroll, CRect& rectScrollBar, BOOL bDraw) const;
			BOOL HasScroll(POSITION pos) const;

			// HitTest
		protected:
			virtual void HitInfoChanged();
			void HitTest();
			void HitTest(const CPoint& pt);
			void HitTest(const CPoint& pt, THitTestInfo& info);
			POSITION FindGroup(const CPoint& pt, CRect& rectGroup) const;
			int GetListItemIndex(const CRect& rectItems, const CPoint& ptItems) const;

			// Scroll
		protected:
			void ScrollDrag(const CPoint& pt);
			void Scroll(int scroll);
			double GetScrollRate(int rectScrollHeight, int rectScrollBarHeight, const CPoint& ptScroll) const;

			// Select
		protected:
			int GetSelectedItem() const;
			BOOL SetSelectItem(int idx, BOOL bRelativeIdx = FALSE, BOOL bScroll = TRUE);
			void ActiveNextGroup();

			// Draw List
		protected:
			virtual int DrawList(CDC* pDC, POSITION pos, int y);
			virtual void DrawListItems(CDC* pDC, TGroupListGroup* pGroup, const CRect& rect);
			virtual void DrawListItem(CDC* pDC, TGroupListItem* pItem, BOOL bSelected, const CRect& rect);
			virtual void DrawListScroll(CDC* pDC, TGroupListGroup* pGroup, const CRect& rect);

			// Draw Group
		protected:
			virtual int DrawGroup(CDC* pDC, POSITION pos, int y);
			virtual void DrawGroupExecute(CDC* pDC, TGroupListItem* pItem, BOOL bMouseOver, const CRect& rect);
			virtual void DrawGroupText(CDC* pDC, const CString& str, const CRect& rect, COLORREF cf, COLORREF cb);
			virtual void DrawGroupExtendBtn(CDC* pDC, BOOL bMouseOver, const CRect& rect);
			virtual void DrawGroupExtendBtn(CDC* pDC, const CRect& rect, COLORREF cf, COLORREF cb);
			virtual void DrawGroupExtendSymbol(CDC* pDC, const CPoint& pt, COLORREF c);

			// Draw Util
		protected:
			virtual void DrawImage(CDC* pDC, int idx, const CRect& rect);
			virtual void DrawGradient(CDC* pDC, const CRect& rect, COLORREF c1, COLORREF c2);

			// SendNotifyMessage
		protected:
			void SendNotifyMsgSizeChanged(int cx, int cy);
			void SendNotifyMsgItem(int code, POSITION pos);

			// Message
		public:
			virtual BOOL HandleMessage(MSG* pMsg);
		protected:
			virtual BOOL PreTranslateMessage(MSG* pMsg);
			virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

			// Event Handler
		protected:
			DECLARE_MESSAGE_MAP()
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			afx_msg void OnDestroy();
			afx_msg void OnSize(UINT nType, int cx, int cy);
			afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
			afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
			afx_msg BOOL OnEraseBkgnd(CDC* pDC);
			afx_msg void OnPaint();
			afx_msg void OnNcPaint();
			afx_msg void OnMouseMove(UINT nFlags, CPoint point);
			afx_msg void OnMouseLeave();
			afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
			afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
			afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
			afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
			afx_msg void OnTimer(UINT_PTR nIDEvent);
			afx_msg void OnSetFocus(CWnd* pOldWnd);
		};
	}
}

#include "HeaderPost.h"