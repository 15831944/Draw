#pragma once
#include "PL_SymbolTable.h"
//#include "HeaderPre.h"
namespace mit
{
	namespace lib
	{
		class Parser
		{
		public:
			Parser();
			~Parser();
			BOOL ParsingINumberArg(CString str);
			BOOL GetINumberData(int& Data);
		private:
			SymbolTabl m_SymbolTable;
			int m_nValue;
		};

		class /*__MY_EXT_CLASS__*/ MyParser
		{
		public:
			MyParser();
			~MyParser();
			
			BOOL ParsingINumberArg(CString str);
			BOOL GetINumberData(int& Data);
		private:
			Parser * m_pParser;
		};
	}
}

//#include "HeaderPost.h"