#include "stdafx.h"
#include "MPostTBSort.h"

#include "MPostTableDB.h"

using namespace mit::frx;

MPostTBSort::MPostTBSort(MPostTableDB* pTableDB) :
	MTBSort(pTableDB)
{
}

MPostTBSort::~MPostTBSort()
{
}

BOOL MPostTBSort::PrivateSort()
{
	return MTBSort::Sort(GetPostTableDB()->m_records);
}