#pragma once

#include "MDialog.h"
#include "MTable.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
#pragma pack(push, 4)    
		struct __MY_EXT_CLASS__ MYDLGTEMPLATE
		{
			WORD	dlgVer;
			WORD	signature;
			DWORD	helpID;
			DWORD	exStyle;
			DWORD	style;
			WORD	cDlgItems;
			short	x;
			short	y;
			short	cx;
			short	cy;
			WORD	menu;
			WORD	windowClass;
			WCHAR	title[1];

			MYDLGTEMPLATE()
			{
				ZeroMemory(this, sizeof(MYDLGTEMPLATE));
				dlgVer = 1;
				signature = 0xFFFF;
			}
		};
#pragma pack(pop)

		class __MY_EXT_CLASS__ MTBDialogBase : public MDialog
		{
			DECLARE_DYNAMIC(MTBDialogBase)

		public:
			MTBDialogBase();
			MTBDialogBase(MTable* pTable);
			virtual ~MTBDialogBase();

			// Table
		private:
			MTable* m_pTable;
			ITableDB* m_pTableDB;
			MTBSchemaBase* m_pSchema;
		protected:
			MTable* GetTable() const { ASSERT(m_pTable); return m_pTable; }
			ITableDB* GetTableDB() const { ASSERT(m_pTableDB); return m_pTableDB; }
			MTBSchemaBase* GetSchema() const { ASSERT(m_pSchema); return m_pSchema; }

		private:
			MYDLGTEMPLATE m_dlgTemplate;
			CFont m_font;
		public:
			virtual BOOL Create(MTable* pTable);

		protected:
			virtual BOOL CreateFont();
			virtual BOOL CreateControls();
			virtual BOOL OnInitDialog();
		};
	}
}

#include "HeaderPost.h"