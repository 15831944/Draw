#include "stdafx.h"
#include "CompFunc.h"

CCompFunc::CCompFunc()
{

}

CCompFunc::~CCompFunc()
{

}

int CCompFunc::UINTAsc(const void* v1, const void* v2)
{
	UINT u1 = *((UINT*)v1);
	UINT u2 = *((UINT*)v2);
	if (u1 > u2)return 1;
	else if (u1 < u2)return -1;
	return 0;
}