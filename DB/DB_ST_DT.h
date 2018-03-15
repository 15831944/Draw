#pragma once
#include "DB_ST_DT_MATL.h"//material  ≤ƒ¡œ
#include "DB_ST_DT_SECT.h"//section		Ωÿ√Ê
#include "DB_ST_DT_CMD.h"
typedef unsigned int T_UDRD_KEY;
//Update Message
enum DBUpdateMessageId
{
	D_UPDATE_BUFFER_BEFFORE,
	D_UPDATE_BUFFER_AFTER,
};
struct T_UDRD_INDEX
{
	int Index;
	int nCommandType;
	CString strCmd;
};
struct T_UDRD_BUFFER//UndoRedo 
{
	int Index;
	int nCmd;
	int nKey;
};
enum
{
	CMDTYPE_REMOVE_ANALYSIS
};