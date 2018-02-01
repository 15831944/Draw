#pragma once

#include "MGridColumnsInfo.h"
#include "ITable.h"
#include "MTBProgressCtrl.h"
#include "MTBMessageCtrl.h"
#include "MGridRow.h"
#include "MGridItem.h"

#include <vector>

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// TODO: 수정 중에 ContextMenu 막을거 막기
		// TODO: 수정 중에 스크롤 확 옮기면??

		class MGridRow;
		class MGridItem;
		class MGridColumnsInfo;

		// 깜빡임, 여러번 그리기 방지용
		class __MY_EXT_CLASS__ MTBNoUpdateWindow
		{
		private:
			BOOL m_bOldValue;
			BOOL& m_bNoUpdateWindow;
		public:
			MTBNoUpdateWindow(BOOL& bNoUpdateWindow) : m_bNoUpdateWindow(bNoUpdateWindow) { m_bOldValue = m_bNoUpdateWindow; m_bNoUpdateWindow = TRUE; }
			~MTBNoUpdateWindow() { m_bNoUpdateWindow = m_bOldValue; }
		};

		class __MY_EXT_CLASS__ MDISPINFO_USERDATA : public CObject
		{
			friend class MTable;
			friend class MGridItem;
			friend class MGridRow;

			DECLARE_DYNAMIC(MDISPINFO_USERDATA)
		public:
			MDISPINFO_USERDATA();
			virtual ~MDISPINFO_USERDATA();

			// operator = 
			MDISPINFO_USERDATA& operator=(const MDISPINFO_USERDATA& rData )
			{
				if( this == &rData ) return *this;

				m_pGridItem		= rData.m_pGridItem;
				m_dwData		= rData.m_dwData;
				m_bAllowEdit	= rData.m_bAllowEdit;
				m_bEnabled		= rData.m_bEnabled;
				m_bBold			= rData.m_bBold;
				m_bItalic		= rData.m_bItalic;
				m_bUnderline	= rData.m_bUnderline;
				m_bStrikeOut	= rData.m_bStrikeOut;

				return *this;
			}

		public:
			BOOL    m_bAllowEdit;
			BOOL    m_bEnabled;
			BOOL    m_bBold;
			BOOL    m_bItalic;
			BOOL	m_bUnderline;
			BOOL	m_bStrikeOut;
			MGridItem*  m_pGridItem; // For Control ( ComboBox, CheckBox, etc );
			DWORD_PTR		m_dwData;    // User Data

		public:
			void Clear();
		};

		class MTableCache : public CBCGPGridCache
		{
			friend class MTable;
		};

		class __MY_EXT_CLASS__ MRecordInfo
		{
			friend class MTable;
			friend class MTableExportToExcel;

		public:
			MRecordInfo();
			MRecordInfo(int nRow, int nColumn);
			virtual ~MRecordInfo();

		protected:
			CArray<CBCGPGridRange*> m_arMerge;
			int						m_nRow;			// 하나의 Record는 몇 개의 row로 만들어졌나? 
			int						m_nColumns;     // 하나의 Record는 몇 개의 Column으로 만들어졌나?

		public:
			const CArray<CBCGPGridRange*>& GetMergeInfo()
			{
				return m_arMerge;
			}

			void Initialize(int nRow = 0, int nColumn = 0);
			int AddMergeRange(CBCGPGridRange* range);
			const CBCGPGridRange* GetMergeRange(int nIndex);
		};

		class __MY_EXT_CLASS__ MTable : public CBCGPGridCtrl, public ITable
		{
			friend class MGridRow;
			friend class MGridItem;
			friend class MGridColumnsInfo;
			friend class MTableSort;
			friend class MouseWheelProcess;
			friend class MTableExportToExcel;
			friend class MTBClipboard;

			DECLARE_DYNAMIC(MTable)
		public:
			MTable();
			virtual ~MTable();

			// ITable Impl
		protected: 
			CRect m_rectProgressCtrl;
			CFont m_fontMessageCtrl;
			mutable MTBProgressCtrl m_wndProgressCtrl; // TODO: 교체 가능하도록...
			mutable MTBMessageCtrl m_wndMessageCtrl; // TODO: 교체 가능하도록...
		public:
			virtual ITableDB* GetTableDB() const = 0;
			virtual ITBProgressCtrl* GetProgressCtrl() const { return &m_wndProgressCtrl; }
			virtual ITBMessageCtrl* GetMessageCtrl() const { return &m_wndMessageCtrl; }
		public:
			MTBSchemaBase* GetSchema() { return GetTableDB()->GetSchema(); }
			ITBSort* GetSort() { return GetTableDB()->GetSort(); }

			// ITable Impl - Update
		public:
			virtual void UpdateRowCount();
			virtual void UpdateData();
			virtual void UpdateSortColumns();
			virtual void UpdateAppendRow();
			virtual void UpdateUnit();
		public:
			void RemoveAll();
			void SetVirtualRows(int nRowsNum);

			// Title
		public:
			CString GetTableTitle() { return m_strTableTitle; }
			void    SetTableTitle(CString strTitle) { m_strTableTitle = strTitle; }

			// Initialize
		protected:
			virtual int GetDefaultColumnWidth(MTBColumn::Type type);
			virtual void InitializeColumns();
			virtual BOOL InitializeTable();
			BOOL CheckItemType();

			// RowCount
		public:
			int GetRowCount() const { return GetExtraTopRowCount() + GetDataRowCount() + GetExtraBottomRowCount(); }
			int GetDataRowCount() const { return GetTableDB()->GetRowCount(); }
			int GetExtraTopRowCount() const { return m_pExtraTopInfo->m_nRow; }
			int GetExtraBottomRowCount() const { return m_canAppendRow ? (IsAppendingRow() ? 2 : 1) : m_pExtraBottomInfo->m_nRow; }
			int GetDataRowEndIndex() const { return GetExtraTopRowCount() + GetDataRowCount(); }
			int GetDBRowIndex(int nRow) const { return nRow - GetExtraTopRowCount(); }
			BOOL IsDataRow(int nRow) const { return nRow >= GetExtraTopRowCount() && nRow < GetDataRowEndIndex(); }
			BOOL IsAppendingRow(int nRow) const { return nRow == GetDataRowEndIndex(); }

			// Callback
		protected:
			static BOOL CALLBACK StaticGridCallback(BCGPGRID_DISPINFO* pdi, LPARAM lp);
			virtual BOOL GridCallback(BCGPGRID_DISPINFO* pdi);
			virtual BOOL DataCallback(BCGPGRID_DISPINFO* pdi);
			virtual BOOL ExtraTopCallback(BCGPGRID_DISPINFO* pdi) { return TRUE; }
			virtual BOOL ExtraBottomCallback(BCGPGRID_DISPINFO* pdi) { return TRUE; }
			virtual void AfterDataCallback(BCGPGRID_DISPINFO* pdi) {}
			virtual void AfterExtraTopCallback(BCGPGRID_DISPINFO* pdi) {}
			virtual void AfterExtraBottomCallback(BCGPGRID_DISPINFO* pdi) {}
			
		public:
			int CalcRowHeaderWidth (int nRowCount);
			MRecordInfo* GetDataRecordInfo() { return m_pDataRecordInfo; }
			MRecordInfo* GetExtraTopRecordInfo() { return m_pExtraTopInfo; }
			MRecordInfo* GetExtraBottomRecordInfo() { return m_pExtraBottomInfo; }

			//Column 별 형식 ( General, 지수, Fixed ... )
		public:
			bool GetColumnFormat(int nCol, MFormatInfo& info);
			void SetColumnFormat(int nCol, MFormatInfo& info);
			void SetColumnFormat(int nStartCol, int nEndCol, MFormatInfo& info);
			
		public:
			virtual void OnPosSizeChanged (); // Merged header items:
			virtual CBCGPGridColumnsInfoEx* PGetColumnsInfo () { return m_pColumnsEx; }
			virtual CBCGPGridColumnsInfo& GetColumnsInfo () { return (*m_pColumnsEx); }
			virtual const CBCGPGridColumnsInfo& GetColumnsInfo () const { return (*m_pColumnsEx); }

			virtual int OnGetGroupNumber (LPCVOID /*pRow*/, int /*iSortedColumn*/)
			{
				return -1;
			}
			
			// Dialog
		public:
			virtual void ShowFindDialog();
			virtual void ShowSortDialog();
			virtual void ShowStyleDialog();
			virtual void ShowActiveDialog();
			virtual void ShowGraphDialog();

			// Columns - virtual 함수 아니지만 그냥 똑같은 Signature 로 선언해서 BCG 꺼 막아버린다.
			//           BCG 내부에서는 부르지 않는 함수라 상관없음.
		public:
			int InsertColumn(int nColumn, LPCTSTR lpszColumn, int nWidth, int iImage = -1, BOOL bHideNameWithImage = TRUE);
			BOOL DeleteColumn(int nColumn);
			void DeleteAllColumns();

			// ButtonItem
			enum
			{
				ID_TB_BUTTON_ITEM = 1000
			};

			// ContextMenu
		protected:
			enum 
			{
				ID_TB_TABBED_DOCUMENT = 1,
				ID_TB_COPY,
				ID_TB_PASTE,
				ID_TB_FIND,
				ID_TB_SORT,
				ID_TB_STYLE,
				ID_TB_GRAPH,
				ID_TB_EXPORT_TO_EXCEL,
				ID_TB_ACTIVE_DIALOG,
				NEXT_ID_TB_TABLE
			};
			CBCGPDockingControlBar* GetParentBar() const;
			BOOL IsMDITabbed() const;
			// 간편하게 ContextMenu 바꾸고 싶을때 Override
			// ( AppendMenu() 만 하면 됨. 물론 새기능 추가시 핸들러는 직접 만들어야 함 )
			virtual void MakeContextMenu(CMenu& menu);
			// ContextMenu 막거나 Customizing 하려면 OnContextMenu() 만들어서 알아서...

			// Sort
		protected:
			// Column 클릭으로 Sort Toggle 시
			//   TRUE : none - asc - desc - none - asc - desc - none - ...
			//   FALSE : none - asc - desc - asc - desc - asc - desc - ...
			BOOL m_bThreeSortToggle; 
		public:
			virtual BOOL IsSortingMode () const;
			virtual void Sort(int nColumn, BOOL bAscending = TRUE, BOOL bAdd = FALSE);
			virtual void ToggleSortColumn(int nColumn);
			// Sort - virtual 함수 아니지만 그냥 똑같은 Signature 로 선언해서 BCG 꺼 막아버린다.
			//        BCG 내부에서는 부르지 않는 함수라 상관없음.
		public:
			void SetSortColumn(int nColumn, BOOL bAscending = TRUE, BOOL bAdd = FALSE);
			BOOL RemoveSortColumn(int nColumn);
			void RemoveAllSortColumns();
			void EnableMultipleSort(BOOL bEnable = TRUE);

			// Find/Replace
			virtual BOOL Find (const CString& strFind, DWORD dwFindMask, DWORD dwFindParamsEx);
			virtual BOOL Search (CBCGPGridItemID &idPos, CBCGPGridItemID idStart, const BCGP_GRID_FINDREPLACE_PARAM &params);
			virtual CBCGPGridItem* SearchColumn (int nCol, int &nPos, int nStart, const BCGP_GRID_FINDREPLACE_PARAM &params);

			// Clipboard
		public:
			virtual BOOL Cut(DWORD dwFlags = (DWORD) -1) { ASSERT(0); return FALSE; } // Cut 은 지원하지 않는다.	
			virtual BOOL Copy(DWORD dwFlags = (DWORD) -1); // dwFlags - Format_CSV, Format_TabSV, Format_Html
			virtual BOOL Paste();

			// Draw
		protected:
			virtual void OnDraw(CDC* pDCPaint);
			virtual void DrawHeaderItem (CDC* pDC, CRect rect, CBCGPHeaderItem* pHeaderItem);
			virtual void OnDrawList (CDC* pDC);
			virtual BOOL OnDrawItem (CDC* pDC, CBCGPGridRow* pItem);
			virtual void RedrawMergedItems2 (CDC* pDC);
			virtual CRect OnGetHeaderRect (CDC* pDC, const CRect& rectDraw);
			virtual void OnDrawHeader (CDC* pDC);
			virtual void OnPrintHeader(CDC* pDC, CPrintInfo* pInfo);
			virtual BOOL MergeRecord(int nRow, MRecordInfo* pMergeInfo);
			virtual void OnDrawLineNumber(CDC* pDC, CBCGPGridRow* pRow, CRect rect, BOOL bSelected, BOOL bPressed);
			virtual void OnDrawRowHeaderItem(CDC* pDC, CBCGPGridRow* pBCGGridItem);
		protected:
			virtual void OnPreDrawRow(MGridRow* pRow) {}

			// Virtual Mode
		protected:
			BOOL m_bCreateCheckItem;
			BOOL m_bCreateComboItem;
		protected:
			virtual BOOL SendDispInfoRequest (BCGPGRID_DISPINFO* pdi) const;
			virtual CBCGPGridRow* CreateVirtualRow (int nIndex);
			virtual CBCGPGridRow* OnCreateVirtualRow (BCGPGRID_DISPINFO* pdi);
			virtual CBCGPGridItem* OnCreateVirtualItem (BCGPGRID_DISPINFO* pdi);
			virtual CBCGPGridRow* CreateRow ();
			virtual CBCGPGridItem* CreateItem (int nRow, int nColumn);
		public:
			virtual MGridRow* CreateDummyRow(BOOL bFillDefaultData);

			// Edit.
			// TODO: AppendRow 는 선택 막기
		protected:
			BOOL m_canAppendRow;		// Append 가능?
			BOOL m_canDeleteRow;		// Delete 가능?
			BOOL n_canDeleteEditingRow;	// Editing Row 중 Editing 취소하고 Delete 할 것인가?
			BOOL m_bDeleteSelectedWholeRowOnly;		// 전체 Row 가 선택되어야한 Delete
			BOOL m_canModifyItem;		// Item (Cell) 단위로 Modify 가능한가
			int m_nEditingRow;			// 현재 편집중인 Row
			CBCGPGridCachePageInfo* m_pEditingCachePage;
			BOOL m_bAppendRowMarker;	// Append Row 의 Row Header 에 마크표시
			BOOL m_bEditingRowMarker;	// Editing Row 의 Row Header 에 마크표시
			BOOL m_bSelectEditingRow;	// 편집하는 동안 현재 Editing Row 를 선택상태로 만듬
			CBCGPGridItem* m_pEndEditItem;		// EndEditItem() 중첩되서 불리는 것 방지
		public:
			BOOL IsEditingRow() const { return m_nEditingRow >= 0; }
			BOOL IsAppendingRow() const { return IsAppendingRow(m_nEditingRow); }
			BOOL IsModifyingRow() const { return IsDataRow(m_nEditingRow); }
			int GetEditingRow() const { return m_nEditingRow; }
			BOOL IsAppendRowMarkerOnRowHeader () const { return m_canAppendRow && m_bAppendRowMarker && m_bRowHeader; }
			BOOL IsEditingRowMarkerOnRowHeader() const { return !m_canModifyItem && m_bEditingRowMarker && m_bRowHeader; }
			BOOL IsSelectEditingRow() const { return m_bSelectEditingRow; }
			BOOL CanModifyItem() const { return m_canModifyItem; }
			void SetEditingRow(int nEditingRow, CBCGPGridRow* pRow);
			void EndEditingRow(CBCGPGridRow* pRow) { SetEditingRow(-1, pRow); }
		protected:
			CBCGPGridCachePageInfo* FindCachePageInfo(int nRow);
		public:
			virtual BOOL EditItem(CBCGPGridRow* pItem, LPPOINT lptClick = NULL);
			virtual BOOL EndEditItem(BOOL bUpdateData = TRUE);
		protected:
			virtual BOOL OnEditEmptyValue(int nRow, int nColumn, CBCGPGridItem* pItem);
			virtual BOOL ValidateItemData(CBCGPGridRow* pRow);
			virtual BOOL SetCurSel(CBCGPGridItemID idItem, DWORD dwSelMode = SM_SINGE_SEL_GROUP | SM_SINGLE_ITEM, BOOL bRedraw = TRUE);
			virtual void DeleteSelRows();
		public:
			virtual BOOL ValidateItem(MGridRow* pRow);
			virtual BOOL OnUpdateValue(MGridItem* pItem);
			virtual BOOL OnEdit(MGridRow* pRow);
			virtual BOOL OnEndEdit(MGridRow* pRow);
			virtual BOOL OnEndEditRow(MGridRow* pRow);
			virtual BOOL OnCancelEditingRow(MGridRow* pRow);
			virtual void OnButtonClicked(MGridItem* pItem);
			
			// Editing 되는 동안 Select 막기
		protected:
			virtual void EnsureVisible(CBCGPGridRow* pItem, BOOL bExpandParents = FALSE);
			virtual BOOL SelectItems(CPoint ptClient);
			virtual void OnFilterBarUpdate(int nColumn);

			// In-place edit
		protected:
			virtual void OnEndInplaceEdit(CBCGPGridItem* pItem);
			virtual BOOL IsAcceleratorKey(UINT nChar, UINT nRepCnt, UINT nFlags) const;
			virtual BOOL CanBeginInplaceEditOnChar(UINT nChar, UINT nRepCnt, UINT nFlags) const;
			virtual BOOL CanEndInplaceEditOnChar(UINT nChar, UINT nRepCnt, UINT nFlags) const;
			virtual BOOL OnInplaceEditKeyDown(CBCGPGridRow* pSel, MSG* pMsg);
			virtual UINT OnInplaceEditSetSel(CBCGPGridItem* pCurItem, UINT nReason) const;	// returns InplaceEditSetSelFlags, used for CBCGPGridItem::DoSetSel
			virtual void DoInplaceEditSetSel(UINT nFlags);

			// Easy Input
		protected:
			BOOL m_bEasyInput;
			DWORD_PTR m_dwEasyInputFlag;	// EndEdit_XXX. Easy Input 발생시키는 Flag
		protected:
			void OnEasyInput(MGridItem* pItem, DWORD_PTR dwResultCode);
			void ContinueInplaceEditing();

			// For Merge
			virtual void ReposItems ();
			virtual void ShiftItems (int dx, int dy);

		protected:
			void UpdateMergeCache();
		protected:
			// Scroll
			virtual void OnAfterHScroll (int nHOffset, int nPrevHOffset);
			virtual void OnAfterVScroll (int nVOffset, int nPrevVOffset);

		protected:
			CBCGPGridColumnsInfoEx*	m_pColumnsEx;	// other header implementation
			CString					m_strTableTitle;

		protected:
			MRecordInfo*		m_pDataRecordInfo;
			MRecordInfo*		m_pExtraTopInfo;
			MRecordInfo*		m_pExtraBottomInfo;
			BOOL m_bCallMouseWheel;

		private:
			MDISPINFO_USERDATA*		m_pUserData;

			// Layout
		public:
			virtual void SetRowHeight ();
			virtual void AdjustLayout();

		public:
			virtual BOOL PreTranslateMessage(MSG* pMsg);

			// Generated message map functions
		protected:
			//{{AFX_MSG(MPostTable)
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			afx_msg void OnDestroy();
			afx_msg void OnPaint();
			afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
			afx_msg void OnMouseMove(UINT nFlags, CPoint point);
			afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
			afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
			afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
			afx_msg void OnKillFocus(CWnd* pNewWnd);
			afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
			afx_msg void OnTabbedDocument();
			afx_msg void OnCopy();
			afx_msg void OnPaste();
			afx_msg void OnFind();
			afx_msg void OnSort();
			afx_msg void OnStyle();
			afx_msg void OnActiveDialog();
			afx_msg void OnGraph();
			afx_msg void OnExportToExcel();
			afx_msg void OnBtnClicked();
			afx_msg void OnEditChanged();
			afx_msg void OnEditKillFocus();
			afx_msg void OnComboKillFocus();
			afx_msg LRESULT OnUpdate(WPARAM wParam, LPARAM lParam);
			afx_msg LRESULT OnEndLabelEdit(WPARAM wParam, LPARAM lParam);
			//}}AFX_MSG
			DECLARE_MESSAGE_MAP()
		
		public:
			enum MTABLE_MSG
			{
				MSG_REDRAW = 1,

				MSG_END
			};
			// Registered Message
			static UINT REG_WM_MTABLE_UPDATE;
};

		class MouseWheelProcess
		{
		public:
			MouseWheelProcess(mit::frx::MTable* pTable) 
			{ 
				ASSERT(pTable);
				m_pTable = pTable; 
				m_pTable->m_bCallMouseWheel = TRUE; 
			}
			~MouseWheelProcess() 
			{
				m_pTable->m_bCallMouseWheel = FALSE;
			}

		protected:
			mit::frx::MTable* m_pTable;
		};
	}
}

#include "HeaderPost.h"