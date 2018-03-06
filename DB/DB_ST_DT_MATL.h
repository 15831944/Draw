#pragma once
typedef unsigned int T_MATL_K;
#pragma pack(push,4)
struct T_MATL_STEEL
{
	double S_Fu;
	double S_Fy1;
	double S_Fy2;
	double S_Fy3;
	double S_Fy4;
	double S_Fy5;
	double S_Fy;
	void Initial()
	{
		S_Fu = 0.;
		S_Fy1 = 0.;
		S_Fy2 = 0.;
		S_Fy3 = 0.;
		S_Fy4 = 0.;
		S_Fy5 = 0.;
		S_Fy = 0.0;
	}
};
struct T_MATL_ALL
{
	CString CodeName;
	void Initial()
	{
		CodeName.Empty();
	}
};
struct T_MATL_D
{
	CString Type;
	void initialize()
	{
		Type.Empty();
	}
};

//for design
struct T_MATL_DESIGN
{
	double S_Fu;
	double S_Fy1;
	double S_Fy2;
	double S_Fy3;
	double S_Fy4;
	double S_Fy5;
	double S_Fy;
	void Initial()
	{
		S_Fu = 0.;
		S_Fy1 = 0.;
		S_Fy2 = 0.;
		S_Fy3 = 0.;
		S_Fy4 = 0.;
		S_Fy5 = 0.;
		S_Fy = 0.0;
	}
};
struct T_MATD_ALL
{
	CString CodeName;

	void Initial()
	{
		CodeName.Empty();
	}
};
struct T_MATD_D
{
	CString Type;//"S" "C" "SRC"
	T_MATD_ALL Data1;
	void Initialize()
	{
		Type.Empty();
		Data1.Initial();
	}
};
const int HASHSIZEMATL = 11;
#pragma pack(pop)