#include "stdafx.h"
#include "SectUtil.h"
#pragma region CSectUtil
CString CSectUtil::m_aRegShapeName[] ={
	D_SECT_SHAPE_REG_L_S,
	D_SECT_SHAPE_REG_C_S,
	D_SECT_SHAPE_REG_H_S,
	D_SECT_SHAPE_REG_T_S,
	D_SECT_SHAPE_REG_B_S,
	D_SECT_SHAPE_REG_P_S,
	D_SECT_SHAPE_REG_2L_S,
	D_SECT_SHAPE_REG_2C_S,
	D_SECT_SHAPE_REG_SB_S,
	D_SECT_SHAPE_REG_SR_S,
};
#pragma endregion CSectUtil
const int CSectUtil::D_SECT_REG_NUM = (sizeof(CSectUtil::m_aRegShapeName)/sizeof(CString));
CSectUtil::CSectUtil(void)
{
}
CSectUtil::~CSectUtil(void)
{
}

CString CSectUtil::GetShapeNameFromIndexReg(int nShape)
{
	ASSERT(nShape < D_SECT_REG_NUM);
	return m_aRegShapeName[nShape];
}

int CSectUtil::GetShapeIndexFromNameReg(const CString& Shape)
{
	int i;
	for(i = 0;i<D_SECT_REG_NUM;i++)
		if(m_aRegShapeName[i] == Shape)break;
	if(i == D_SECT_REG_NUM)return -1;
	return i;
}

BOOL CSectUtil::CalcSectData(T_SECT_D& data)
{
	return FALSE;
}
void CSectUtil::GetSizeTitleFromShapeIndexReg(int nShapeIndex,CStringArray& aSizeTitle)
{
	CString RegTitleForSize[][8]={
		{_T("H"),_T("B"),_T("tw"),_T("tf"),_T(""),_T(""),_T(""),_T("")},
		{_T("H"),_T("B1"),_T("tw"),_T("tf1"),_T("B2"),_T("tf2"),_T("r1"),_T("r2")},
		{_T("H"),_T("B1"),_T("tw"),_T("tf1"),_T("B2"),_T("tf2"),_T("r1"),_T("r2")},
		{_T("H"),_T("B"),_T("tw"),_T("tf"),_T(""),_T(""),_T(""),_T("")},
		{_T("H"),_T("B"),_T("tw"),_T("tf1"),_T("C"),_T("tf2"),_T(""),_T("")},
		{_T("D"),_T("tw"),_T(""),_T(""),_T(""),_T(""),_T(""),_T("")},
		{_T("H"),_T("B"),_T("tw"),_T("tf"),_T("C"),_T(""),_T(""),_T("")},
		{_T("H"),_T("B"),_T("tw"),_T("tf"),_T("C"),_T(""),_T(""),_T("")},
		{_T("H"),_T("B"),_T(""),_T(""),_T(""),_T(""),_T(""),_T("")},
		{_T("D"),_T(""),_T(""),_T(""),_T(""),_T(""),_T(""),_T("")},
	};
	for(int i = 0;RegTitleForSize[nShapeIndex][i] != _T("") && i < 8;i++)
	{
		aSizeTitle.Add(RegTitleForSize[nShapeIndex][i]);
	}

}