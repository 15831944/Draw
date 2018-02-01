#pragma once

#include "MTBDialogBase.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// TODO: 모달리스에 대한 고려되어 있지 않음
		class __MY_EXT_CLASS__ MTBSortDialog : public MTBDialogBase
		{
			DECLARE_DYNAMIC(MTBSortDialog)

		public:
			MTBSortDialog();
			MTBSortDialog(MTable* pTable);
			virtual ~MTBSortDialog();

		private:
			ITBSort* m_pSort;
		protected:
			ITBSort* GetSort() const { ASSERT(m_pSort); return m_pSort; }

		public:
			virtual BOOL Create(MTable* pTable);
			
		public:
			void SetHorizontalScroll(CListBox& lstbox);

			// Controls
		protected:
			enum
			{
				IDC_STT_TABLE_COLS = 1,
				IDC_STT_SORT_COLS,
				IDC_LISTBOX_TABLE_COLS,
				IDC_LISTBOX_SORT_COLS,
				IDC_BTN_ADD,
				IDC_BTN_DEL,
				IDC_GRP_PRIORITY,
				IDC_BTN_UP,
				IDC_BTN_DOWN,
				IDC_BTN_SORT,
				IDC_BTN_CLOSE
			};
			CBCGPStatic m_sttTableCols;
			CBCGPStatic m_sttSortCols;
			CListBox	m_lbCols;
			CCheckListBox m_lbSortCols;
			CBCGPButton m_btnAdd;
			CBCGPButton m_btnDel;
			CButton		m_groupPriority;
			CBCGPButton m_btnUp;
			CBCGPButton m_btnDown;
			CBCGPButton m_btnSort;
			CBCGPButton m_btnClose;

		protected:
			virtual void PostNcDestroy();

		protected:
			virtual CString GetSortColName(const TBSortColumn& sortcol);

		protected:
			virtual void InitTableCols();
			virtual void InitSortCols();
			virtual BOOL CreateControls();
			virtual BOOL OnInitDialog();
		protected:
			DECLARE_MESSAGE_MAP()
			afx_msg void OnBtnClose();
			afx_msg void OnBtnSort();
			afx_msg void OnColAdd();
			afx_msg void OnColDel();
			afx_msg void OnPrioUp();
			afx_msg void OnPrioDown();
			afx_msg void OnDblClickColsItem();
			afx_msg void OnDblClickSortColsItem();
			afx_msg void OnChkChangeSortColsItem();
		};
	}
}

#include "HeaderPost.h"