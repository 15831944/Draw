#pragma once
#include "HeaderPre.h"
class __MY_EXT_CLASS__ CSectUtil
{
public:
	CSectUtil(void);
	~CSectUtil(void);
	static int GetShapeIndexFromNameReg(const CString& Shape);
	static CString GetShapeNameFromIndexReg(int nShape);
private:
	static CString m_aRegShapeName[];
	static const int D_SECT_REG_NUM;
	//CString m_aRegShapeName1[];
};


#include "HeaderPost.h"