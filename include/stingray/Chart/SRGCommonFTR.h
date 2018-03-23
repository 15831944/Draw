///////////////////////////////////////////////////////////////////////////////
// SRGCommonFTR.h
//
// Copyright (c) 1999-2009 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
//@doc SRGCommonFTR
//@module SRGCommonFTR.h | Definition of the XML formatters for the common Objective Chart classes.<nl>
//The XML formatters inherit from the SFL CXMLSerializeImp base class and implement the IXMLSerialize
//interface. All Objective Chart data types that take part in the serialization process will have an 
//equivalent formatter object. Invoking the IXMLSerialize::XMLSerialize() function on a formatter will
//serialize the state information of the connected chart data object.<nl>
//For more detailed information on the XML Serialization mechanism please refer to the Objective Chart 
//User's Guide.<nl>
//Written by Prakash Surendra (www.roguewave.com)

#ifndef __SRGCOMMONFTR__
#define __SRGCOMMONFTR__

#include "Chart\SRGDat.h"
#include "Chart\SRGraphRect.h"
#include "Chart\SRGComp.h"
#include "Chart\SRGCompoundComponent.h"
#include "Chart\DataMgr.h"
#include "Chart\SRGAxisManager.h"
#include "Chart\SRGGridLines.h"
#include "Chart\SRGDataWatcher.h"
#include "Chart\SRGraphBackground.h"
#include "Chart\SRGraphTitle.h"
#include "Chart\SRGraphLabel.h"
#include "Chart\SRGraphLabelBlock.h"
#include "Chart\SRGraphLegend.h"
#include "Chart\SRGTextPanel.h"
#include "Chart\SRGTickMarks.h"
#include "Chart\DScale.h"
#include "Chart\SRGScaleBar.h"
#include "Chart\SRGIndexBar.h"
#include "Chart\SRGDisplayBase.h"
#include "Chart\SRGraphDisplay.h"
#include "Chart\SRGCompoundDisplay.h"
#include "Chart\SRGraph.h"
#include "Chart\SRGXMLrc.h"
#include <foundation\XMLSerialize.h>
#include <StingrayExportDefs.h>

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the CScale utility class

///////////////////////////////////////////////////////////////////////
// Autoduck comment block for CScaleFTR Scale
//
//@doc CScaleFTR
//@mfunc  | CScaleFTR | CScaleFTR | Initializing constructor
//@parm CScale*& | ptrObj | A reference to the CScale instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the CScale type.

//@mfunc | CScaleFTR | ~CScaleFTR | Destructor

//@mdata CScale*&  | CScaleFTR | m_ptrObj | References the CScale instance tied to this formatter.

////////////////////////////////////////////////////////////////////////
//$head XML Serialization (Common Classes)
//$level 2

//@doc CScaleFTR
//@class XML Formatter for the CScale class defined in Objective Chart. CScaleFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c CScale>
//
class CScaleFTR : public CXMLSerializeImp
{
BEGIN_SEC_XMLFORMATTERMAP(CScaleFTR)
XMLFORMATTERMAP_ADDENTRY(CScale, CScaleFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline CScaleFTR(CScale*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLCSCALE))
		: CXMLSerializeImp(strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~CScaleFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* CScale reference*/
	CScale*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGraphStyle class

//@doc SRGraphStyleFTR
//@mfunc  | SRGraphStyleFTR | SRGraphStyleFTR | Initializing constructor
//@parm SRGraphStyle*& | ptrObj | A reference to the SRGraphStyle instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGraphStyle type.

//@mfunc | SRGraphStyleFTR | ~SRGraphStyleFTR | Destructor

//@mdata SRGraphStyle*&  | SRGraphStyleFTR | m_ptrObj | References the SRGraphStyle instance tied to this formatter.

// adinsert

//@doc SRGraphStyleFTR
//@class XML Formatter for the SRGraphStyle class defined in Objective Chart. SRGraphStyleFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGraphStyle>
//
class SRGraphStyleFTR : public CXMLSerializeImp
{
BEGIN_SEC_XMLFORMATTERMAP(SRGraphStyleFTR)
XMLFORMATTERMAP_ADDENTRY(SRGraphStyle, SRGraphStyleFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGraphStyleFTR(SRGraphStyle*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGPHSTYLE))
		: CXMLSerializeImp(strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGraphStyleFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGraphStyle reference*/
	SRGraphStyle*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGraphAnnotation class

//@doc SRGraphAnnotationFTR
//@mfunc  | SRGraphAnnotationFTR | SRGraphAnnotationFTR | Initializing constructor
//@parm SRGraphAnnotation*& | ptrObj | A reference to the SRGraphAnnotation instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGraphAnnotation type.

//@mfunc | SRGraphAnnotationFTR | ~SRGraphAnnotationFTR | Destructor

//@mdata SRGraphAnnotation*&  | SRGraphAnnotationFTR | m_ptrObj | References the SRGraphAnnotation instance tied to this formatter.

// adinsert

//@doc SRGraphAnnotationFTR
//@class XML Formatter for the SRGraphAnnotation class defined in Objective Chart. SRGraphAnnotationFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGraphAnnotation>
//
class SRGraphAnnotationFTR : public CXMLSerializeImp
{
BEGIN_SEC_XMLFORMATTERMAP(SRGraphAnnotationFTR)
XMLFORMATTERMAP_ADDENTRY(SRGraphAnnotation, SRGraphAnnotationFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGraphAnnotationFTR(SRGraphAnnotation*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGPHANNOTATION))
		: CXMLSerializeImp(strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGraphAnnotationFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGraphAnnotation reference*/
	SRGraphAnnotation*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGraphData class

//@doc SRGraphDataFTR
//@mfunc  | SRGraphDataFTR | SRGraphDataFTR | Initializing constructor
//@parm SRGraphData*& | ptrObj | A reference to the SRGraphDataFTR instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGraphData type.

//@mfunc | SRGraphDataFTR | ~SRGraphDataFTR | Destructor

//@mdata SRGraphData*&  | SRGraphDataFTR | m_ptrObj | References the SRGraphData instance tied to this formatter.

// adinsert

//@doc SRGraphDataFTR
//@class XML Formatter for the SRGraphData class defined in Objective Chart. SRGraphDataFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGraphData>
//
class SRGraphDataFTR : public CXMLSerializeImp
{
BEGIN_SEC_XMLFORMATTERMAP(SRGraphDataFTR)
XMLFORMATTERMAP_ADDENTRY(SRGraphData, SRGraphDataFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGraphDataFTR(SRGraphData*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGPHDATA))
		: CXMLSerializeImp(strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGraphDataFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGraphData reference*/
	SRGraphData*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGraphDataList class

//@doc SRGraphDataListFTR
//@mfunc  | SRGraphDataListFTR | SRGraphDataListFTR | Initializing constructor
//@parm SRGraphDataList*& | ptrObj | A reference to the SRGraphDataList instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGraphDataList type.

//@mfunc | SRGraphDataListFTR | ~SRGraphDataListFTR | Destructor

//@mdata SRGraphDataList*&  | SRGraphDataListFTR | m_ptrObj | References the SRGraphDataList instance tied to this formatter.

// adinsert

//@doc SRGraphDataListFTR
//@class XML Formatter for the SRGraphDataList class defined in Objective Chart. SRGraphDataListFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGraphDataList>
//
class SRGraphDataListFTR : public CXMLSerializeImp
{
BEGIN_SEC_XMLFORMATTERMAP(SRGraphDataListFTR)
XMLFORMATTERMAP_ADDENTRY(SRGraphDataList, SRGraphDataListFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGraphDataListFTR(SRGraphDataList*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGPHDATALIST))
		: CXMLSerializeImp(strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGraphDataListFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGraphDataList reference*/
	SRGraphDataList*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGraphDynamicData class

//@doc SRGraphDynamicDataFTR
//@mfunc  | SRGraphDynamicDataFTR | SRGraphDynamicDataFTR | Initializing constructor
//@parm SRGraphDynamicData*& | ptrObj | A reference to the SRGraphDynamicData instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGraphDynamicData type.

//@mfunc | SRGraphDynamicDataFTR | ~SRGraphDynamicDataFTR | Destructor

//@mdata SRGraphDynamicData*&  | SRGraphDynamicDataFTR | m_ptrObj | References the SRGraphDynamicData instance tied to this formatter.

// adinsert

//@doc SRGraphDynamicDataFTR
//@class XML Formatter for the SRGraphDynamicData class defined in Objective Chart. SRGraphDynamicDataFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGraphDynamicData>
//
class SRGraphDynamicDataFTR : public SRGraphDataFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGraphDynamicDataFTR)
XMLFORMATTERMAP_ADDENTRY(SRGraphDynamicData, SRGraphDynamicDataFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGraphDynamicDataFTR(SRGraphDynamicData*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGPHDYNDATA))
		: SRGraphDataFTR((SRGraphData*&)ptrObj,strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGraphDynamicDataFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGraphDynamicData reference*/
	SRGraphDynamicData*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGraphComponentFTR class

//@doc SRGraphRectFTR
//@mfunc  | SRGraphRectFTR | SRGraphRectFTR | Initializing constructor
//@parm SRGraphRect*& | ptrObj | A reference to the SRGraphRect instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGraphRect type.

//@mfunc | SRGraphRectFTR | ~SRGraphRectFTR | Destructor

//@mdata SRGraphRect*&  | SRGraphRectFTR | m_ptrObj | References the SRGraphRect instance tied to this formatter.

// adinsert

//@doc SRGraphRectFTR
//@class XML Formatter for the SRGraphRect class defined in Objective Chart. SRGraphRectFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGraphRect>
//
class SRGraphRectFTR : public CXMLSerializeImp
{
BEGIN_SEC_XMLFORMATTERMAP(SRGraphRectFTR)
XMLFORMATTERMAP_ADDENTRY(SRGraphRect, SRGraphRectFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGraphRectFTR(SRGraphRect*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_GRAPHRECT))
		: CXMLSerializeImp(strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGraphRectFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGraphRect reference*/
	SRGraphRect*& m_ptrObj;
};

//
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGraphComponentFTR class

//@doc SRGraphComponentFTR
//@mfunc  | SRGraphComponentFTR | SRGraphComponentFTR | Initializing constructor
//@parm SRGraphComponent*& | ptrObj | A reference to the SRGraphComponent instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGraphComponent type.

//@mfunc | SRGraphComponentFTR | ~SRGraphComponentFTR | Destructor

//@mdata SRGraphComponent*&  | SRGraphComponentFTR | m_ptrObj | References the SRGraphComponent instance tied to this formatter.

// adinsert

//@doc SRGraphComponentFTR
//@class XML Formatter for the SRGraphComponent class defined in Objective Chart. SRGraphComponentFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGraphComponent>
//
class SRGraphComponentFTR : public CXMLSerializeImp
{
BEGIN_SEC_XMLFORMATTERMAP(SRGraphComponentFTR)
XMLFORMATTERMAP_ADDENTRY(SRGraphComponent, SRGraphComponentFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGraphComponentFTR(SRGraphComponent*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGPHCOMP))
		: CXMLSerializeImp(strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGraphComponentFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGraphComponent reference*/
	SRGraphComponent*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGCompoundComponentFTR class

//@doc SRGCompoundComponentFTR
//@mfunc  | SRGCompoundComponentFTR | SRGCompoundComponentFTR | Initializing constructor
//@parm SRGCompoundComponent*& | ptrObj | A reference to the SRGCompoundComponent instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGCompoundComponent type.

//@mfunc | SRGCompoundComponentFTR | ~SRGCompoundComponentFTR | Destructor

//@mdata SRGCompoundComponent*&  | SRGCompoundComponentFTR | m_ptrObj | References the SRGCompoundComponent instance tied to this formatter.

// adinsert

//@doc SRGCompoundComponentFTR
//@class XML Formatter for the SRGCompoundComponent class defined in Objective Chart. SRGCompoundComponentFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGCompoundComponent>
//
class SRGCompoundComponentFTR : public SRGraphComponentFTR
{

BEGIN_SEC_XMLFORMATTERMAP(SRGCompoundComponentFTR)
XMLFORMATTERMAP_ADDENTRY(SRGCompoundComponent, SRGCompoundComponentFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGCompoundComponentFTR(SRGCompoundComponent*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLCMPDCOMP))
		: SRGraphComponentFTR((SRGraphComponent*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGCompoundComponentFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);
	
protected:
	//@cmember
	/* SRGCompoundComponent reference*/
	SRGCompoundComponent*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGDataManagerFTR class

//@doc SRGDataManagerFTR
//@mfunc  | SRGDataManagerFTR | SRGDataManagerFTR | Initializing constructor
//@parm SRGDataManager*& | ptrObj | A reference to the SRGDataManager instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGDataManager type.

//@mfunc | SRGDataManagerFTR | ~SRGDataManagerFTR | Destructor

//@mdata SRGDataManager*&  | SRGDataManagerFTR | m_ptrObj | References the SRGDataManager instance tied to this formatter.

// adinsert

//@doc SRGDataManagerFTR
//@class XML Formatter for the SRGDataManager class defined in Objective Chart. SRGDataManagerFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGDataManager>
//
class SRGDataManagerFTR : public CXMLSerializeImp
{
BEGIN_SEC_XMLFORMATTERMAP(SRGDataManagerFTR)
XMLFORMATTERMAP_ADDENTRY(SRGDataManager, SRGDataManagerFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGDataManagerFTR(SRGDataManager*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLDATAMGR))
		: CXMLSerializeImp(strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGDataManagerFTR() {}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);	

protected:
	//@cmember
	/* SRGDataManager reference*/
	SRGDataManager*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGDynamicDataManagerFTR class

//@doc SRGDynamicDataManagerFTR
//@mfunc  | SRGDynamicDataManagerFTR | SRGDynamicDataManagerFTR | Initializing constructor
//@parm SRGDynamicDataManager*& | ptrObj | A reference to the SRGDynamicDataManager instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGDynamicDataManager type.

//@mfunc | SRGDynamicDataManagerFTR | ~SRGDynamicDataManagerFTR | Destructor

//@mdata SRGDynamicDataManager*&  | SRGDynamicDataManagerFTR | m_ptrObj | References the SRGDynamicDataManager instance tied to this formatter.

// adinsert

//@doc SRGDynamicDataManagerFTR
//@class XML Formatter for the SRGDynamicDataManager class defined in Objective Chart. SRGDynamicDataManagerFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGDynamicDataManager>
//
class SRGDynamicDataManagerFTR : public SRGDataManagerFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGDynamicDataManagerFTR)
XMLFORMATTERMAP_ADDENTRY(SRGDynamicDataManager, SRGDynamicDataManagerFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGDynamicDataManagerFTR(SRGDynamicDataManager*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLDYNDATAMGR))
		: SRGDataManagerFTR((SRGDataManager*&)ptrObj,strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGDynamicDataManagerFTR()	{}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGDynamicDataManager reference*/
	SRGDynamicDataManager*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGAxisManagerFTR class

//@doc SRGAxisManagerFTR
//@mfunc  | SRGAxisManagerFTR | SRGAxisManagerFTR | Initializing constructor
//@parm SRGAxisManager*& | ptrObj | A reference to the SRGAxisManager instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGAxisManager type.

//@mfunc | SRGAxisManagerFTR | ~SRGAxisManagerFTR | Destructor

//@mdata SRGAxisManager*&  | SRGAxisManagerFTR | m_ptrObj | References the SRGAxisManager instance tied to this formatter.

// adinsert

//@doc SRGAxisManagerFTR
//@class XML Formatter for the SRGAxisManager class defined in Objective Chart. SRGAxisManagerFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGAxisManager>
//
class SRGAxisManagerFTR : public SRGCompoundComponentFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGAxisManagerFTR)
XMLFORMATTERMAP_ADDENTRY(SRGAxisManager, SRGAxisManagerFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGAxisManagerFTR(SRGAxisManager*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLAXISMGR))
		: SRGCompoundComponentFTR((SRGCompoundComponent*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGAxisManagerFTR() {}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);	

protected:
	//@cmember
	/* SRGAxisManager reference*/
	SRGAxisManager*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGGridLinesFTR class

//@doc SRGGridLinesFTR
//@mfunc  | SRGGridLinesFTR | SRGGridLinesFTR | Initializing constructor
//@parm SRGGridLines*& | ptrObj | A reference to the SRGGridLines instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGGridLines type.

//@mfunc | SRGGridLinesFTR | ~SRGGridLinesFTR | Destructor

//@mdata SRGGridLines*&  | SRGGridLinesFTR | m_ptrObj | References the SRGGridLines instance tied to this formatter.

// adinsert

//@doc SRGGridLinesFTR
//@class XML Formatter for the SRGGridLines class defined in Objective Chart. SRGGridLinesFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGGridLines>
//
class SRGGridLinesFTR : public SRGraphComponentFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGGridLinesFTR)
XMLFORMATTERMAP_ADDENTRY(SRGGridLines, SRGGridLinesFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGGridLinesFTR(SRGGridLines*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGRIDLINES))
		: SRGraphComponentFTR((SRGraphComponent*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGGridLinesFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGGridLines reference*/
	SRGGridLines*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGDataWatcherFTR class

//@doc SRGDataWatcherFTR
//@mfunc  | SRGDataWatcherFTR | SRGDataWatcherFTR | Initializing constructor
//@parm SRGDataWatcher*& | ptrObj | A reference to the SRGDataWatcher instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGDataWatcher type.

//@mfunc | SRGDataWatcherFTR | ~SRGDataWatcherFTR | Destructor

//@mdata SRGDataWatcher*&  | SRGDataWatcherFTR | m_ptrObj | References the SRGDataWatcher instance tied to this formatter.

// adinsert

//@doc SRGDataWatcherFTR
//@class XML Formatter for the SRGDataWatcher class defined in Objective Chart. SRGDataWatcherFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGDataWatcher>
//
class SRGDataWatcherFTR : public SRGGridLinesFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGDataWatcherFTR)
XMLFORMATTERMAP_ADDENTRY(SRGDataWatcher, SRGDataWatcherFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGDataWatcherFTR(SRGDataWatcher*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLDATAWATCHER))
		: SRGGridLinesFTR((SRGGridLines*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGDataWatcherFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGDataWatcher reference*/
	SRGDataWatcher*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGraphBackgroundFTR class

//@doc SRGraphBackgroundFTR
//@mfunc  | SRGraphBackgroundFTR | SRGraphBackgroundFTR | Initializing constructor
//@parm SRGraphBackground*& | ptrObj | A reference to the SRGraphBackground instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGraphBackground type.

//@mfunc | SRGraphBackgroundFTR | ~SRGraphBackgroundFTR | Destructor

//@mdata SRGraphBackground*&  | SRGraphBackgroundFTR | m_ptrObj | References the SRGraphBackground instance tied to this formatter.

// adinsert

//@doc SRGraphBackgroundFTR
//@class XML Formatter for the SRGraphBackground class defined in Objective Chart. SRGraphBackgroundFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGraphBackground>
//
class SRGraphBackgroundFTR : public SRGraphComponentFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGraphBackgroundFTR)
XMLFORMATTERMAP_ADDENTRY(SRGraphBackground, SRGraphBackgroundFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGraphBackgroundFTR(SRGraphBackground*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGPHBKGRND))
		: SRGraphComponentFTR((SRGraphComponent*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGraphBackgroundFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGraphBackground reference*/
	SRGraphBackground*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGraphTitleFTR class

//@doc SRGraphTitleFTR
//@mfunc  | SRGraphTitleFTR | SRGraphTitleFTR | Initializing constructor
//@parm SRGraphTitle*& | ptrObj | A reference to the SRGraphTitle instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGraphTitle type.

//@mfunc | SRGraphTitleFTR | ~SRGraphTitleFTR | Destructor

//@mdata SRGraphTitle*&  | SRGraphTitleFTR | m_ptrObj | References the SRGraphTitle instance tied to this formatter.

// adinsert

//@doc SRGraphTitleFTR
//@class XML Formatter for the SRGraphTitle class defined in Objective Chart. SRGraphTitleFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGraphTitle>
//
class SRGraphTitleFTR : public SRGraphComponentFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGraphTitleFTR)
XMLFORMATTERMAP_ADDENTRY(SRGraphTitle, SRGraphTitleFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGraphTitleFTR(SRGraphTitle*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGPHTITLE))
		: SRGraphComponentFTR((SRGraphComponent*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGraphTitleFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGraphTitle reference*/
	SRGraphTitle*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGraphTitleResizeableFTR class

//@doc SRGraphTitleResizeableFTR
//@mfunc  | SRGraphTitleResizeableFTR | SRGraphTitleResizeableFTR | Initializing constructor
//@parm SRGraphTitleResizeable*& | ptrObj | A reference to the SRGraphTitleResizeable instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGraphTitleResizeable type.

//@mfunc | SRGraphTitleResizeableFTR | ~SRGraphTitleResizeableFTR | Destructor

//@mdata SRGraphTitleResizeable*&  | SRGraphTitleResizeableFTR | m_ptrObj | References the SRGraphTitleResizeable instance tied to this formatter.

// adinsert

//@doc SRGraphTitleResizeableFTR
//@class XML Formatter for the SRGraphTitleResizeable class defined in Objective Chart. SRGraphTitleResizeableFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGraphTitleResizeable>
//
class SRGraphTitleResizeableFTR : public SRGraphTitleFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGraphTitleResizeableFTR)
XMLFORMATTERMAP_ADDENTRY(SRGraphTitleResizeable, SRGraphTitleResizeableFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGraphTitleResizeableFTR(SRGraphTitleResizeable*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGPHTITLERESZ))
		: SRGraphTitleFTR((SRGraphTitle*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGraphTitleResizeableFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGraphTitleResizeable reference*/
	SRGraphTitleResizeable*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGraphLabelFTR class

//@doc SRGraphLabelFTR
//@mfunc  | SRGraphLabelFTR | SRGraphLabelFTR | Initializing constructor
//@parm SRGraphLabel*& | ptrObj | A reference to the SRGraphLabel instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGraphLabel type.

//@mfunc | SRGraphLabelFTR | ~SRGraphLabelFTR | Destructor

//@mdata SRGraphLabel*&  | SRGraphLabelFTR | m_ptrObj | References the SRGraphLabel instance tied to this formatter.

// adinsert

//@doc SRGraphLabelFTR
//@class XML Formatter for the SRGraphLabel class defined in Objective Chart. SRGraphLabelFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGraphLabel>
//
class SRGraphLabelFTR : public SRGraphTitleFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGraphLabelFTR)
XMLFORMATTERMAP_ADDENTRY(SRGraphLabel, SRGraphLabelFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGraphLabelFTR(SRGraphLabel*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGPHLABEL))
		: SRGraphTitleFTR((SRGraphTitle*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGraphLabelFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGraphLabel reference*/
	SRGraphLabel*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGraphLabelBlockFTR class

//@doc SRGraphLabelBlockFTR
//@mfunc  | SRGraphLabelBlockFTR | SRGraphLabelBlockFTR | Initializing constructor
//@parm SRGraphLabelBlock*& | ptrObj | A reference to the SRGraphLabelBlock instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGraphLabelBlock type.

//@mfunc | SRGraphLabelBlockFTR | ~SRGraphLabelBlockFTR | Destructor

//@mdata SRGraphLabelBlock*&  | SRGraphLabelBlockFTR | m_ptrObj | References the SRGraphLabelBlock instance tied to this formatter.

// adinsert

//@doc SRGraphLabelBlockFTR
//@class XML Formatter for the SRGraphLabelBlock class defined in Objective Chart. SRGraphLabelBlockFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGraphLabelBlock>
//
class SRGraphLabelBlockFTR : public SRGraphLabelFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGraphLabelBlockFTR)
XMLFORMATTERMAP_ADDENTRY(SRGraphLabelBlock, SRGraphLabelBlockFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGraphLabelBlockFTR(SRGraphLabelBlock*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGPHLBLBLCK))
		: SRGraphLabelFTR((SRGraphLabel*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGraphLabelBlockFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGraphLabelBlock reference*/
	SRGraphLabelBlock*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGraphLegendFTR class

//@doc SRGraphLegendFTR
//@mfunc  | SRGraphLegendFTR | SRGraphLegendFTR | Initializing constructor
//@parm SRGraphLegend*& | ptrObj | A reference to the SRGraphLegend instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGraphLegend type.

//@mfunc | SRGraphLegendFTR | ~SRGraphLegendFTR | Destructor

//@mdata SRGraphLegend*&  | SRGraphLegendFTR | m_ptrObj | References the SRGraphLegend instance tied to this formatter.

// adinsert

//@doc SRGraphLegendFTR
//@class XML Formatter for the SRGraphLegend class defined in Objective Chart. SRGraphLegendFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGraphLegend>
//
class SRGraphLegendFTR : public SRGraphTitleFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGraphLegendFTR)
XMLFORMATTERMAP_ADDENTRY(SRGraphLegend, SRGraphLegendFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGraphLegendFTR(SRGraphLegend*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGPHLGND))
		: SRGraphTitleFTR((SRGraphTitle*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGraphLegendFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGraphLegend reference*/
	SRGraphLegend*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGTextPanelFTR class

//@doc SRGTextPanelFTR
//@mfunc  | SRGTextPanelFTR | SRGTextPanelFTR | Initializing constructor
//@parm SRGTextPanel*& | ptrObj | A reference to the SRGTextPanel instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGTextPanel type.

//@mfunc | SRGTextPanelFTR | ~SRGTextPanelFTR | Destructor

//@mdata SRGTextPanel*&  | SRGTextPanelFTR | m_ptrObj | References the SRGTextPanel instance tied to this formatter.

// adinsert

//@doc SRGTextPanelFTR
//@class XML Formatter for the SRGTextPanel class defined in Objective Chart. SRGTextPanelFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGTextPanel>
//
class SRGTextPanelFTR : public SRGraphTitleFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGTextPanelFTR)
XMLFORMATTERMAP_ADDENTRY(SRGTextPanel, SRGTextPanelFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGTextPanelFTR(SRGTextPanel*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLTEXTPANEL))
		: SRGraphTitleFTR((SRGraphTitle*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGTextPanelFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGTextPanel reference*/
	SRGTextPanel*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGTickMarksFTR class

//@doc SRGTickMarksFTR
//@mfunc  | SRGTickMarksFTR | SRGTickMarksFTR | Initializing constructor
//@parm SRGTickMarks*& | ptrObj | A reference to the SRGTickMarks instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGTickMarks type.

//@mfunc | SRGTickMarksFTR | ~SRGTickMarksFTR | Destructor

//@mdata SRGTickMarks*&  | SRGTickMarksFTR | m_ptrObj | References the SRGTickMarks instance tied to this formatter.

// adinsert

//@doc SRGTickMarksFTR
//@class XML Formatter for the SRGTickMarks class defined in Objective Chart. SRGTickMarksFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGTickMarks>
//
class SRGTickMarksFTR : public SRGraphComponentFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGTickMarksFTR)
XMLFORMATTERMAP_ADDENTRY(SRGTickMarks, SRGTickMarksFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGTickMarksFTR(SRGTickMarks*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLTICKMARKS))
		: SRGraphComponentFTR((SRGraphComponent*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGTickMarksFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGTickMarks reference*/
	SRGTickMarks*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGDecimalScaleFTR class

//@doc SRGDecimalScaleFTR
//@mfunc  | SRGDecimalScaleFTR | SRGDecimalScaleFTR | Initializing constructor
//@parm SRGDecimalScale*& | ptrObj | A reference to the SRGDecimalScale instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGDecimalScale type.

//@mfunc | SRGDecimalScaleFTR | ~SRGDecimalScaleFTR | Destructor

//@mdata SRGDecimalScale*&  | SRGDecimalScaleFTR | m_ptrObj | References the SRGDecimalScale instance tied to this formatter.

// adinsert

//@doc SRGDecimalScaleFTR
//@class XML Formatter for the SRGDecimalScale class defined in Objective Chart. SRGDecimalScaleFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGDecimalScale>
//
class SRGDecimalScaleFTR : public SRGraphLabelBlockFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGDecimalScaleFTR)
XMLFORMATTERMAP_ADDENTRY(SRGDecimalScale, SRGDecimalScaleFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGDecimalScaleFTR(SRGDecimalScale*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLDCMLSCALE))
		: SRGraphLabelBlockFTR((SRGraphLabelBlock*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGDecimalScaleFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGDecimalScale reference*/
	SRGDecimalScale*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGLogScaleFTR class

//@doc SRGLogScaleFTR
//@mfunc  | SRGLogScaleFTR | SRGLogScaleFTR | Initializing constructor
//@parm SRGLogScale*& | ptrObj | A reference to the SRGLogScale instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGLogScale type.

//@mfunc | SRGLogScaleFTR | ~SRGLogScaleFTR | Destructor

//@mdata SRGLogScale*&  | SRGLogScaleFTR | m_ptrObj | References the SRGLogScale instance tied to this formatter.

// adinsert

//@doc SRGLogScaleFTR
//@class XML Formatter for the SRGLogScale class defined in Objective Chart. SRGLogScaleFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGLogScale>
//
class SRGLogScaleFTR : public SRGDecimalScaleFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGLogScaleFTR)
XMLFORMATTERMAP_ADDENTRY(SRGLogScale, SRGLogScaleFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGLogScaleFTR(SRGLogScale*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLLOGSCALE))
		: SRGDecimalScaleFTR((SRGDecimalScale*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGLogScaleFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGLogScale reference*/
	SRGLogScale*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGDateScaleFTR class

//@doc SRGDateScaleFTR
//@mfunc  | SRGDateScaleFTR | SRGDateScaleFTR | Initializing constructor
//@parm SRGDateScale*& | ptrObj | A reference to the SRGDateScale instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGDateScale type.

//@mfunc | SRGDateScaleFTR | ~SRGDateScaleFTR | Destructor

//@mdata SRGDateScale*&  | SRGDateScaleFTR | m_ptrObj | References the SRGDateScale instance tied to this formatter.

// adinsert

//@doc SRGDateScaleFTR
//@class XML Formatter for the SRGDateScale class defined in Objective Chart. SRGDateScaleFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGDateScale>
//
class SRGDateScaleFTR : public SRGDecimalScaleFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGDateScaleFTR)
XMLFORMATTERMAP_ADDENTRY(SRGDateScale, SRGDateScaleFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGDateScaleFTR(SRGDateScale*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLDATESCALE))
		: SRGDecimalScaleFTR((SRGDecimalScale*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGDateScaleFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGDateScale reference*/
	SRGDateScale*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGIndexScaleFTR class

//@doc SRGIndexScaleFTR
//@mfunc  | SRGIndexScaleFTR | SRGIndexScaleFTR | Initializing constructor
//@parm SRGIndexScale*& | ptrObj | A reference to the SRGIndexScale instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGIndexScale type.

//@mfunc | SRGIndexScaleFTR | ~SRGIndexScaleFTR | Destructor

//@mdata SRGIndexScale*&  | SRGIndexScaleFTR | m_ptrObj | References the SRGIndexScale instance tied to this formatter.

// adinsert

//@doc SRGIndexScaleFTR
//@class XML Formatter for the SRGIndexScale class defined in Objective Chart. SRGIndexScaleFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGIndexScale>
//
class SRGIndexScaleFTR : public SRGDecimalScaleFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGIndexScaleFTR)
XMLFORMATTERMAP_ADDENTRY(SRGIndexScale, SRGIndexScaleFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGIndexScaleFTR(SRGIndexScale*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLINDEXSCALE))
		: SRGDecimalScaleFTR((SRGDecimalScale*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGIndexScaleFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);
	
protected:
	//@cmember
	/* SRGIndexScale reference*/
	SRGIndexScale*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGGroupScaleFTR class

//@doc SRGGroupScaleFTR
//@mfunc  | SRGGroupScaleFTR | SRGGroupScaleFTR | Initializing constructor
//@parm SRGGroupScale*& | ptrObj | A reference to the SRGGroupScale instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGGroupScale type.

//@mfunc | SRGGroupScaleFTR | ~SRGGroupScaleFTR | Destructor

//@mdata SRGGroupScale*&  | SRGGroupScaleFTR | m_ptrObj | References the SRGGroupScale instance tied to this formatter.

// adinsert

//@doc SRGGroupScaleFTR
//@class XML Formatter for the SRGGroupScale class defined in Objective Chart. SRGGroupScaleFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGGroupScale>
//
class SRGGroupScaleFTR : public SRGIndexScaleFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGGroupScaleFTR)
XMLFORMATTERMAP_ADDENTRY(SRGGroupScale, SRGGroupScaleFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGGroupScaleFTR(SRGGroupScale*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_GROUPSCALE))
		: SRGIndexScaleFTR((SRGIndexScale*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGGroupScaleFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGGroupScale reference*/
	SRGGroupScale*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGScaleBarFTR class

//@doc SRGScaleBarFTR
//@mfunc  | SRGScaleBarFTR | SRGScaleBarFTR | Initializing constructor
//@parm SRGScaleBar*& | ptrObj | A reference to the SRGScaleBar instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGScaleBar type.

//@mfunc | SRGScaleBarFTR | ~SRGScaleBarFTR | Destructor

//@mdata SRGScaleBar*&  | SRGScaleBarFTR | m_ptrObj | References the SRGScaleBar instance tied to this formatter.

// adinsert

//@doc SRGScaleBarFTR
//@class XML Formatter for the SRGScaleBar class defined in Objective Chart. SRGScaleBarFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGScaleBar>
//
class SRGScaleBarFTR : public SRGDecimalScaleFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGScaleBarFTR)
XMLFORMATTERMAP_ADDENTRY(SRGScaleBar, SRGScaleBarFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGScaleBarFTR(SRGScaleBar*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLSCALEBAR))
		: SRGDecimalScaleFTR((SRGDecimalScale*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGScaleBarFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGScaleBar reference*/
	SRGScaleBar*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGIndexBarFTR class

//@doc SRGIndexBarFTR
//@mfunc  | SRGIndexBarFTR | SRGIndexBarFTR | Initializing constructor
//@parm SRGIndexBar*& | ptrObj | A reference to the SRGIndexBar instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGIndexBar type.

//@mfunc | SRGIndexBarFTR | ~SRGIndexBarFTR | Destructor

//@mfunc void | SRGIndexBarFTR | XMLSerialize | Does a read/write of the XML formatted SRGIndexBar data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGIndexBar*&  | SRGIndexBarFTR | m_ptrObj | References the SRGIndexBar instance tied to this formatter.

// adinsert

//@doc SRGIndexBarFTR
//@class XML Formatter for the SRGIndexBar class defined in Objective Chart. SRGIndexBarFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGIndexBar>
//
class SRGIndexBarFTR : public SRGScaleBarFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGIndexBarFTR)
XMLFORMATTERMAP_ADDENTRY(SRGIndexBar, SRGIndexBarFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGIndexBarFTR(SRGIndexBar*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLINDEXBAR))
		: SRGScaleBarFTR((SRGScaleBar*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGIndexBarFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGScaleBarFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGIndexBar reference*/
	SRGIndexBar*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGGroupBarFTR class

//@doc SRGGroupBarFTR
//@mfunc  | SRGGroupBarFTR | SRGGroupBarFTR | Initializing constructor
//@parm SRGGroupBar*& | ptrObj | A reference to the SRGGroupBar instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGGroupBar type.

//@mfunc | SRGGroupBarFTR | ~SRGGroupBarFTR | Destructor

//@mfunc void | SRGGroupBarFTR | XMLSerialize | Does a read/write of the XML formatted SRGGroupBar data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class.

//@mdata SRGGroupBar*&  | SRGGroupBarFTR | m_ptrObj | References the SRGGroupBar instance tied to this formatter.

// adinsert

//@doc SRGGroupBarFTR
//@class XML Formatter for the SRGGroupBar class defined in Objective Chart. SRGGroupBarFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGGroupBar>
//
class SRGGroupBarFTR : public SRGIndexBarFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGGroupBarFTR)
XMLFORMATTERMAP_ADDENTRY(SRGGroupBar, SRGGroupBarFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGGroupBarFTR(SRGGroupBar*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGROUPBAR))
		: SRGIndexBarFTR((SRGIndexBar*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGGroupBarFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGIndexBarFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGGroupBar reference*/
	SRGGroupBar*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGDateBarFTR class

//@doc SRGDateBarFTR
//@mfunc  | SRGDateBarFTR | SRGDateBarFTR | Initializing constructor
//@parm SRGDateBar*& | ptrObj | A reference to the SRGDateBar instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGDateBar type.

//@mfunc | SRGDateBarFTR | ~SRGDateBarFTR | Destructor

//@mfunc void | SRGDateBarFTR | XMLSerialize | Does a read/write of the XML formatted SRGDateBar data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class.

//@mdata SRGDateBar*&  | SRGDateBarFTR | m_ptrObj | References the SRGDateBar instance tied to this formatter.

// adinsert

//@doc SRGDateBarFTR
//@class XML Formatter for the SRGDateBar class defined in Objective Chart. SRGDateBarFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGDateBar>
//
class SRGDateBarFTR : public SRGScaleBarFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGDateBarFTR)
XMLFORMATTERMAP_ADDENTRY(SRGDateBar, SRGDateBarFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGDateBarFTR(SRGDateBar*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLDATEBAR))
		: SRGScaleBarFTR((SRGScaleBar*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGDateBarFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGScaleBarFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGDateBar reference*/
	SRGDateBar*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGLogBarFTR class

//@doc SRGLogBarFTR
//@mfunc  | SRGLogBarFTR | SRGLogBarFTR | Initializing constructor
//@parm SRGLogBar*& | ptrObj | A reference to the SRGLogBar instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGLogBar type.

//@mfunc | SRGLogBarFTR | ~SRGLogBarFTR | Destructor

//@mfunc void | SRGLogBarFTR | XMLSerialize | Does a read/write of the XML formatted SRGLogBar data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class.

//@mdata SRGLogBar*&  | SRGLogBarFTR | m_ptrObj | References the SRGLogBar instance tied to this formatter.

// adinsert

//@doc SRGLogBarFTR
//@class XML Formatter for the SRGLogBar class defined in Objective Chart. SRGLogBarFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGLogBar>
//
class SRGLogBarFTR : public SRGScaleBarFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGLogBarFTR)
XMLFORMATTERMAP_ADDENTRY(SRGLogBar, SRGLogBarFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGLogBarFTR(SRGLogBar*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLLOGBAR))
		: SRGScaleBarFTR((SRGScaleBar*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGLogBarFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGScaleBarFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGLogBar reference*/
	SRGLogBar*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGDisplayBaseFTR class

//@doc SRGDisplayBaseFTR
//@mfunc  | SRGDisplayBaseFTR | SRGDisplayBaseFTR | Initializing constructor
//@parm SRGDisplayBase*& | ptrObj | A reference to the SRGDisplayBase instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGDisplayBase type.

//@mfunc | SRGDisplayBaseFTR | ~SRGDisplayBaseFTR | Destructor

//@mdata SRGDisplayBase*&  | SRGDisplayBaseFTR | m_ptrObj | References the SRGDisplayBase instance tied to this formatter.

// adinsert

//@doc SRGDisplayBaseFTR
//@class XML Formatter for the SRGDisplayBase class defined in Objective Chart. SRGDisplayBaseFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGDisplayBase>
//
class SRGDisplayBaseFTR : public SRGraphTitleFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGDisplayBaseFTR)
XMLFORMATTERMAP_ADDENTRY(SRGDisplayBase, SRGDisplayBaseFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGDisplayBaseFTR(SRGDisplayBase*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLDISPLAYBASE))
		: SRGraphTitleFTR((SRGraphTitle*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGDisplayBaseFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGDisplayBase reference*/
	SRGDisplayBase*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGraphDisplayFTR class

//@doc SRGraphDisplayFTR
//@mfunc  | SRGraphDisplayFTR | SRGraphDisplayFTR | Initializing constructor
//@parm SRGraphDisplay*& | ptrObj | A reference to the SRGraphDisplay instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGraphDisplay type.

//@mfunc | SRGraphDisplayFTR | ~SRGraphDisplayFTR | Destructor

//@mdata SRGraphDisplay*&  | SRGraphDisplayFTR | m_ptrObj | References the SRGraphDisplay instance tied to this formatter.

// adinsert

//@doc SRGraphDisplayFTR
//@class XML Formatter for the SRGraphDisplay class defined in Objective Chart. SRGraphDisplayFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGraphDisplay>
//
class SRGraphDisplayFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGraphDisplayFTR)
XMLFORMATTERMAP_ADDENTRY(SRGraphDisplay, SRGraphDisplayFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGraphDisplayFTR(SRGraphDisplay*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGPHDISPLAY))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGraphDisplayFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRGraphDisplay reference*/
	SRGraphDisplay*& m_ptrObj;
};

//
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGraphFTR class

//@doc SRGraphFTR
//@mfunc  | SRGraphFTR | SRGraphFTR | Initializing constructor
//@parm SRGraph*& | ptrObj | A reference to the SRGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGraph type.

//@mfunc | SRGraphFTR | ~SRGraphFTR | Destructor

//@mdata SRGraph*&  | SRGraphFTR | m_ptrObj | References the SRGraph instance tied to this formatter.

// adinsert

//@doc SRGraphFTR
//@class XML Formatter for the SRGraph class defined in Objective Chart. SRGraphFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGraph>
//
class SRGraphFTR : public CXMLSerializeImp
{
BEGIN_SEC_XMLFORMATTERMAP(SRGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGraph, SRGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGraphFTR(SRGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGRAPH))
		: CXMLSerializeImp(strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);
	CHART_API virtual void SerializeXMLComponentList(SECXMLArchive& ar);
	
protected:
	//@cmember
	/* SRGraph reference*/
	SRGraph*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRDynamicGraphFTR class

//@doc SRDynamicGraphFTR
//@mfunc  | SRDynamicGraphFTR | SRDynamicGraphFTR | Initializing constructor
//@parm SRDynamicGraph*& | ptrObj | A reference to the SRDynamicGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRDynamicGraph type.

//@mfunc | SRDynamicGraphFTR | ~SRDynamicGraphFTR | Destructor

//@mdata SRDynamicGraph*&  | SRDynamicGraphFTR | m_ptrObj | References the SRDynamicGraph instance tied to this formatter.

// adinsert

//@doc SRDynamicGraphFTR
//@class XML Formatter for the SRDynamicGraph class defined in Objective Chart. SRDynamicGraphFTR derives from the SFL 
//CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRDynamicGraph>
//
class SRDynamicGraphFTR : public SRGraphFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRDynamicGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRDynamicGraph, SRDynamicGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRDynamicGraphFTR(SRDynamicGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLDYNGRAPH))
		: SRGraphFTR((SRGraph*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRDynamicGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	CHART_API virtual void XMLSerialize(SECXMLArchive& ar);

protected:
	//@cmember
	/* SRDynamicGraph reference*/
	SRDynamicGraph*& m_ptrObj;
};
///////////////////////////////////////////////////////////////////////////

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SRGCOMMONFTR__

