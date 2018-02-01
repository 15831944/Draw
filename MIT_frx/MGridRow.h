#pragma once

#include "MGridItem.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MTable;
		class __MY_EXT_CLASS__ MGridRow : public CBCGPGridRow
		{
			DECLARE_SERIAL(MGridRow)

			friend class MTable;
			friend class MPreTable;
			friend class MGridItem;

		public:
			// Group constructor
			MGridRow (const CString& strGroupName, DWORD_PTR dwData = 0, int nBlockSize = 10);
			// Simple item
			MGridRow (int nColumnsNum = 0, DWORD_PTR dwData = 0, int nBlockSize = 10);
			virtual ~MGridRow();

		protected:
			MTable* GetTable() const { return (MTable*)m_pWndList; }

		private:
			// mutable MKey m_nCachedKey;
			mutable LPCVOID m_pCachedRow;
		private:
			LPCVOID GetCachedRow() const;
		public:
			LPCVOID GetDBData() const;

		public:
			MGridItem* GetItem(int nColumn) const
			{
				if (nColumn >= 0 && nColumn < m_arrRowItems.GetSize ())
				{
					ASSERT(m_arrRowItems[nColumn]->IsKindOf(RUNTIME_CLASS(MGridItem)));
					return (MGridItem*)m_arrRowItems[nColumn];
				}
				return NULL;
			}

		public:
			virtual void OnDrawItems(CDC* pDC, CRect rect);
			virtual void OnDrawEditingRowMarker(CDC* pDC, CRect rect);
			virtual void OnDrawAppendRowMarker(CDC* pDC, CRect rect);

		public:
			virtual BOOL OnEdit(LPPOINT lptClick);
			virtual BOOL OnEndEdit();
		};
	}
}

#include "HeaderPost.h"