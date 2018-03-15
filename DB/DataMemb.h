#pragma once
#include "DB_MATL.h"
#include "DB_SECT.h"

class CDataMemb
{
public:
	CDataMemb();
	~CDataMemb();
public:
	CDB_MATL m_matl;
	CDB_SECT m_sect;
};

