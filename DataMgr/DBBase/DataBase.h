#pragma once
#include "../common/HeaderPre.h"
typedef UINT T_KEY;

class __MY_EXT_CLASS__ CDataBase
{
public:
	//CDataBase(void);
	CDataBase(const T_KEY nKey);
	virtual ~CDataBase();
	virtual CDataBase* Duplicate() const = 0;

public:
	const T_KEY m_nKey;
};
#include "../common/HeaderPost.h"
