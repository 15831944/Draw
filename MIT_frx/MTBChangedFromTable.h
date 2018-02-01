#pragma once

#include <vector>

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		template<typename TYPE>
		class MTBChangedFromTable
		{
		private:
			TYPE& m_memberItem;
		public:
			MTBChangedFromTable(TYPE& memberItem, const TYPE& changedItem) :
				m_memberItem(memberItem)
			{
				m_memberItem = changedItem;
			}
			~MTBChangedFromTable() 
			{
				m_memberItem.Initialize();
			} 
		};

		struct __MY_EXT_CLASS__ TModifiedItem
		{
		public:
			int nRow;
			int nCol;
			_variant_t* pItem;
		public:
			TModifiedItem() : 
				nRow(-1), nCol(-1), pItem(NULL) {}
			TModifiedItem(int row, int col, _variant_t* item) : 
				nRow(row), nCol(col), pItem(item) {}
			void Initialize()
			{ 
				nRow = -1; nCol = -1; pItem = NULL; 
			}
			BOOL HasModifiedItem() const 
			{
				return pItem != NULL; 
			}
		};

		struct __MY_EXT_CLASS__ TModifiedRow
		{
		public:
			int nRow;
			std::vector<_variant_t*> aItems;
		public:
			TModifiedRow() : 
				nRow(-1) {}
			TModifiedRow(int row, std::vector<_variant_t*>& items) : 
				nRow(row), aItems(items) {}
			void Initialize() 
			{
				nRow = -1;
				for (size_t i = 0; i < aItems.size(); i++) aItems[i] = NULL;
			}
			BOOL HasModifiedRow() const 
			{
				return nRow >= 0;
			}
		};

		struct __MY_EXT_CLASS__ TAppendedRow
		{
		public:
			BOOL bAppended;
			std::vector<_variant_t*> aItems;
		public:
			TAppendedRow() : 
				bAppended(FALSE) {}
			TAppendedRow(std::vector<_variant_t*>& items) : 
				bAppended(TRUE), aItems(items) {}
			void Initialize() 
			{
				bAppended = FALSE;
				for (size_t i = 0; i < aItems.size(); i++) aItems[i] = NULL;
			}
			BOOL HasAppendedRow() const 
			{
				return bAppended; 
			}
		};
	}
}

#include "HeaderPost.h"