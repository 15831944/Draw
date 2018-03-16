#pragma once
typedef unsigned int T_SECT_K;
enum
{
	D_SECT_SHAPE_REG_L,
	D_SECT_SHAPE_REG_C,
	D_SECT_SHAPE_REG_H,
	D_SECT_SHAPE_REG_T,
	D_SECT_SHAPE_REG_B,
	D_SECT_SHAPE_REG_P,
	D_SECT_SHAPE_REG_2L,
	D_SECT_SHAPE_REG_2C,
	D_SECT_SHAPE_REG_SB,
	D_SECT_SHAPE_REG_SR,
};
//Regular
const CString D_SECT_SHAPE_REG_L_S			= _T("L");//�Ǹ�
const CString D_SECT_SHAPE_REG_C_S			= _T("C");//�۸�
const CString D_SECT_SHAPE_REG_H_S			= _T("H");//�����͸�
const CString D_SECT_SHAPE_REG_T_S			= _T("T");//T��
const CString D_SECT_SHAPE_REG_B_S			= _T("B");//����
const CString D_SECT_SHAPE_REG_P_S      = _T("P");//����
const CString D_SECT_SHAPE_REG_SB_S     = _T("SB");//˫�Ǹֽ���
const CString D_SECT_SHAPE_REG_SR_S     = _T("SR");//����Ǹֽ���
const CString D_SECT_SHAPE_REG_2L_S     = _T("2L");//ʵ�������ν���
const CString D_SECT_SHAPE_REG_2C_S     = _T("2C");//ʵ��Բ�ν���
//const CString D_SECT_SHAPE_REG_CC     = _T("CC");
//const CString D_SECT_SHAPE_REG_URIB   = _T("URIB");
//const CString D_SECT_SHAPE_REG_OCT    = _T("OCT");
//const CString D_SECT_SHAPE_REG_SOCT   = _T("SOCT");
//const CString D_SECT_SHAPE_REG_TRK    = _T("TRK");
//const CString D_SECT_SHAPE_REG_STRK   = _T("STRK");
//const CString D_SECT_SHAPE_REG_HTRK   = _T("HTRK");
//const CString D_SECT_SHAPE_REG_CL     = _T("CL");   // Cross Angle
//const CString D_SECT_SHAPE_REG_ROCT   = _T("ROCT");
//const CString D_SECT_SHAPE_REG_BSTF   = _T("BSTF");  // Box with stiffener
//const CString D_SECT_SHAPE_REG_PSTF   = _T("PSTF");  // Pipe with stiffener
//const CString D_SECT_SHAPE_REG_GEN    = _T("GEN");  // General Section (Value������ ���)
//const CString D_SECT_SHAPE_REG_UDT    = _T("UDT");  // Upside-Down T
const int D_SECT_SIZE_NUM_MAX = 8;
struct T_SECT_SECTBASE_D
{
	CString Shape;
	CString SName;//GB-YB

	double dSize[D_SECT_SIZE_NUM_MAX];
	void initialize()
	{
		Shape.Empty();
		SName.Empty();
		for(int i = 0;i<D_SECT_SIZE_NUM_MAX;i++)
			dSize[i] = 0.0;
	}
};
struct T_SECT_D
{
	CString csName;
	T_SECT_SECTBASE_D SectI;
	void initialize()
	{
		csName.Empty();
		SectI.initialize();
	}
};