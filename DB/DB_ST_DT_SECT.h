#pragma once
#pragma pack(push,4)
typedef unsigned int T_SECT_K;
enum
{
	D_SECT_BUILT_BUILTUP=1,
	D_SECT_BUILT_ROLLED,//轧制刚
};
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
enum
{
	D_SECT_TYPE_REGULAR =1,
	D_SECT_TYPE_USER,

};
#pragma region CString
//Regular
const CString D_SECT_SHAPE_REG_L_S			= _T("L");//角钢
const CString D_SECT_SHAPE_REG_C_S			= _T("C");//槽钢
const CString D_SECT_SHAPE_REG_H_S			= _T("H");//工字型钢
const CString D_SECT_SHAPE_REG_T_S			= _T("T");//T型
const CString D_SECT_SHAPE_REG_B_S			= _T("B");//箱型
const CString D_SECT_SHAPE_REG_P_S      = _T("P");//管型
const CString D_SECT_SHAPE_REG_SB_S     = _T("SB");//双角钢截面
const CString D_SECT_SHAPE_REG_SR_S     = _T("SR");//交叉角钢截面
const CString D_SECT_SHAPE_REG_2L_S     = _T("2L");//实腹长方形截面
const CString D_SECT_SHAPE_REG_2C_S     = _T("2C");//实腹圆形截面
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
//const CString D_SECT_SHAPE_REG_GEN    = _T("GEN");  // General Section (Value俊辑父 荤侩)
//const CString D_SECT_SHAPE_REG_UDT    = _T("UDT");  // Upside-Down T
#pragma endregion CString
const int D_SECT_SIZE_NUM_MAX = 8;
struct T_SECT_STIFFNESS
{
	void initialize()
	{

	}
};
struct T_SECT_SECTBASE_D
{
	CString Shape;
	CString DBName;//GB-YB
	CString SName;//HW5x5x5
	T_SECT_STIFFNESS Stiffness;
	int BuiltUpFlag;  // 1=Builtup Section(D_SECT_BUILT_BUILTUP)  2=Rolled Section(D_SECT_BUILT_ROLLED)
	double dSize[D_SECT_SIZE_NUM_MAX];

	void initialize()
	{
		Shape.Empty();
		DBName.Empty();
		SName.Empty();
		Stiffness.initialize();
		BuiltUpFlag = 0;
		for(int i = 0;i<D_SECT_SIZE_NUM_MAX;i++)
			dSize[i] = 0.0;
	}
};
struct T_SECT_D
{
	int nStype;//D_SECT_SHAPE_REG_??
	CString csName;
	T_SECT_SECTBASE_D SectI;
	void initialize()
	{
		nStype = 0;
		csName.Empty();
		SectI.initialize();
	}
};
#pragma pack(pop)