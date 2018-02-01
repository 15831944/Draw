#pragma once

#include "MTBClipboard.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MPreTableDB2G;
		class __MY_EXT_CLASS__ MTBPreClipboard2G : public MTBClipboard
		{
		public:
			MTBPreClipboard2G(ITableDB* pTableDB);
			virtual ~MTBPreClipboard2G();

			// TableDB
		private:
			MPreTableDB2G* GetPreTableDB2G() { return reinterpret_cast<MPreTableDB2G*>(GetTableDB()); }

		protected:
			virtual int GetApproximateRowLength(const std::vector<MKey>& aKey, const std::vector<LPCVOID>& aRow);

			// Export
		protected:
			virtual void Export(CString& strText);
			virtual void ParallelExport(int nTaskCount, CString* aText);

			// Import
		protected:
			virtual int ImportAppend(const CString& strText);
			virtual int ImportModify(const CString& strText);
		};
	}
}

#include "HeaderPost.h"