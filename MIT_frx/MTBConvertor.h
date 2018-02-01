#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		template<typename TYPE>
		class MTBConvertor
		{
		public:
			static const TYPE* PConvert(LPCVOID pItem)	
			{
				return static_cast<const TYPE*>(pItem);
			}
			static const TYPE& Convert(LPCVOID pItem)	
			{
				return *(PConvert(pItem));
			}
			// Overloading 되지만 실수 방지를 위해 const 아닌 함수는 W 붙인다.
			static TYPE* PConvertW(LPVOID pItem)	
			{
				return static_cast<TYPE*>(pItem);
			}
			static TYPE& ConvertW(LPVOID pItem)	
			{
				return *(PConvertW(pItem));
			}
		};

		template<typename TYPE>
		class MTBCompare
		{
		public:
			static int Compare(const TYPE& item1, const TYPE& item2)			
			{
				return item1 < item2 ? -1 : item1 == item2 ? 0 : 1;
			}
			static int Compare(LPCVOID pItem1, LPCVOID pItem2)			
			{
				return Compare(MTBConvertor<TYPE>::Convert(pItem1), MTBConvertor<TYPE>::Convert(pItem2));
			}
			static int Subtract(const TYPE& item1, const TYPE& item2)			
			{
				return item1 - item2;
			}
			static int Subtract(LPCVOID pItem1, LPCVOID pItem2)			
			{
				return Subtract(MTBConvertor<TYPE>::Convert(pItem1), MTBConvertor<TYPE>::Convert(pItem2));
			}
		};

		template<typename TYPE>
		class MTBArrayCompare
		{
		public:
			static int Compare(LPCVOID paItem1, LPCVOID paItem2, int nIndex)			
			{
				return MTBCompare<TYPE>::Compare(MTBConvertor<CArray<TYPE>>::Convert(paItem1).GetAt(nIndex), MTBConvertor<CArray<TYPE>>::Convert(paItem2).GetAt(nIndex));
			}
			static int Subtract(LPCVOID paItem1, LPCVOID paItem2, int nIndex)			
			{
				return MTBCompare<TYPE>::Subtract(MTBConvertor<CArray<TYPE>>::Convert(paItem1).GetAt(nIndex), MTBConvertor<CArray<TYPE>>::Convert(paItem2).GetAt(nIndex));
			}
		};

		// 요거 다른곳에 있어야 할듯...
		inline int MTBStringCompare(const CString& str1, const CString& str2)
		{
			// TODO: 요거 Optimize 하기
			int nComp = 0;
			// "xxxx10" 가 "xxxx2" 뒤에 오도록 비교하는 함수
			{
				CString tmpStr1, tmpStr2;
				int index = str1.FindOneOf(_T("0123456789"));
				if(index!=-1)
					tmpStr1 = str1.Right(str1.GetLength()-index);
				index = str2.FindOneOf(_T("0123456789"));
				if(index!=-1)
					tmpStr2 = str2.Right(str2.GetLength()-index);

				tmpStr1 = tmpStr1.SpanIncluding(_T("0123456789"));
				tmpStr2 = tmpStr2.SpanIncluding(_T("0123456789"));

				if((tmpStr1==_T("")) && (tmpStr2==_T("")))
					nComp = str1.CompareNoCase(str2);
				else
				{
					int num1 = _ttoi(tmpStr1);
					int num2 = _ttoi(tmpStr2);

					tmpStr1 = str1.SpanExcluding(_T("0123456789"));
					tmpStr2 = str2.SpanExcluding(_T("0123456789"));

					if(tmpStr1 == tmpStr2)
					{
						if(num1 > num2)
							nComp = 1;
						else
							if(num1 < num2)
								nComp = -1;
							else
								nComp = str1.CompareNoCase(str2);
					}
					else
						nComp = str1.CompareNoCase(str2);			
				}
			}

			return nComp;
		}

		inline int MTBStringCompare(LPCVOID pItem1, LPCVOID pItem2)
		{
			return MTBStringCompare(MTBConvertor<CString>::Convert(pItem1), MTBConvertor<CString>::Convert(pItem2));
		}

		inline int MTBStringArrayCompare(LPCVOID pItem1, LPCVOID pItem2, int nIndex)
		{
			return MTBStringCompare(MTBConvertor<CArray<CString>>::Convert(pItem1).GetAt(nIndex), MTBConvertor<CArray<CString>>::Convert(pItem2).GetAt(nIndex));
		}
	}
}

#include "HeaderPost.h"