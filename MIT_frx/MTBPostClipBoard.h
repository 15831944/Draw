#pragma once

#include "MTBClipboard.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MPostTableDB;
		class __MY_EXT_CLASS__ MTBPostClipboard : public MTBClipboard
		{
		public:
			MTBPostClipboard(ITableDB* pTableDB);
			virtual ~MTBPostClipboard();

			// TableDB
		private:
			MPostTableDB* GetPostTableDB() { return reinterpret_cast<MPostTableDB*>(GetTableDB()); }

		protected:
			virtual int GetApproximateRowLength(const std::vector<MKey>&, const std::vector<LPCVOID>&);

			// Export
		protected:
			virtual void Export(CString& strText);
			virtual void ParallelExport(int nTaskCount, CString* aText);

			// Import ( Modify ¸¸ °¡´É )
		protected:
			virtual int ImportAppend(const CString& strText) { ASSERT(0); return 0; }
			virtual int ImportModify(const CString& strText);
		};
	}
}

#include "HeaderPost.h"