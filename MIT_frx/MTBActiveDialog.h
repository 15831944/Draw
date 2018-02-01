#pragma once

#include "MTBDialogBase.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MTBActiveInfo
		{
		private:
			int m_nColumn;
		};

		// TODO: 모달리스에 대한 고려되어 있지 않음
		class __MY_EXT_CLASS__ MTBActiveDialog : public MTBDialogBase
		{
			DECLARE_DYNAMIC(MTBActiveDialog)

		public:
			MTBActiveDialog();
			MTBActiveDialog(MTable* pTable);
			virtual ~MTBActiveDialog();

		public:
			virtual BOOL Create(MTable* pTable);

			// Controls
		protected:
			enum
			{
				IDC_GRID = 1,
				IDC_BTN_OK,
				IDC_BTN_APPLY,
				IDC_BTN_CANCEL
			};

			MTable* m_pTable;
			CBCGPButton m_btnOK;
			CBCGPButton m_btnCancel;
			CBCGPButton m_btnApply;
			
		public:
			BOOL AddActiveColumn(int nColumn);
			BOOL AddActiveDialog(CDialog* pDialog);
			
		protected:
			//virtual BOOL Apply();

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