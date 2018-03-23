///////////////////////////////////////////////////////////////////////////////
// gxexmpst.h

#ifndef _GX_EX__MP_SET_H__
#define _GX_EX__MP_SET_H__

#include "gxexhdr.h"
#include "gxexman.h"
#include "gxexhnd.h"
#include "gxextbl.h"
#include "gxexmap.h"
// #include <StingrayExportDefs.h>

#ifndef _UNICODE

typedef CGXExcelMap<CGXExcelHandler> CGXHandlerMap;
typedef CGXExcelMap<CGXExcelTable>	CGXTableMap;

typedef CGXExcelMapImpl<CGXExcelHandler> CGXHandlerMapImpl;
typedef CGXExcelMapImpl<CGXExcelTable>	CGXTableMapImpl;

GRID_API CGXHandlerMap* GXExGetHandlerMap();
GRID_API CGXTableMap* GXExGetTableMap();

class CGXExMapHolder
{
public:
	// construction
	GRID_API CGXExMapHolder();
	GRID_API ~CGXExMapHolder();

	// access
	GRID_API void SetHandlerMap(CGXHandlerMap* pHandlerMap);
	GRID_API void SetTableMap(CGXTableMap* pTableMap);

	GRID_API CGXHandlerMap* GetHandlerMap() const;
	GRID_API CGXTableMap*  GetTableMap() const;

protected:
	// data
	CGXHandlerMap*	m_pHandlerMap;
	CGXTableMap*	m_pTableMap;
};

#endif

#endif
