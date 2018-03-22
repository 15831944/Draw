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