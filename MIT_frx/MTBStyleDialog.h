#pragma once

#include "MTBDialogBase.h"
#include "MTBStyleTable.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// TODO: 모달리스에 대한 고려되어 있지 않음
		class __MY_EXT_CLASS__ MTBStyleDialog : public MTBDialogBase
		{
			DECLARE_DYNAMIC(MTBStyleDialog)

		public:
			MTBStyleDialog();
			MTBStyleDialog(MTable* pObjTable);
			virtual ~MTBStyleDialog();

		public:
			virtual BOOL Create(MTable* pObjTable);

			// Controls
		protected:
			enum
			{
				IDC_GRID = 1,
				IDC_BTN_OK,
				IDC_BTN_APPLY,
				IDC_BTN_CANCEL
			};
			
			MTable* m_pObjTable;
			MTBStyleTable m_table;		
			CBCGPButton m_btnOK;
			CBCGPButton m_btnCancel;
			CBCGPButton m_btnApply;

		protected:
			virtual BOOL Apply();

		protected:
			virtual void PostNcDestroy();

		protected:
			virtual BOOL CreateControls();
			virtual BOOL OnInitDialog();
		protected:
			DECLARE_MESSAGE_MAP()
			afx_msg void OnBtnOK();
			afx_msg void OnBtnCancel();
			afx_msg void OnBtnApply();
		};
	}
}

#include "HeaderPost.h"