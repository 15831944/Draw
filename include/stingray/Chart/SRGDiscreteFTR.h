///////////////////////////////////////////////////////////////////////////////
// SRGDiscreteFTR.h
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
//@doc SRGDiscreteFTR
//@module SRGDiscreteFTR.h | Definition of the XML formatters for the Objective Chart discrete graph classes.<nl>
//The XML formatters inherit from the SFL CXMLSerializeImp base class and implement the IXMLSerialize
//interface. All Objective Chart data types that take part in the serialization process will have an 
//equivalent formatter object. Invoking the IXMLSerialize::XMLSerialize() function on a formatter will
//serialize the state information of the connected chart data object.<nl>
//For more detailed information on the XML Serialization mechanism please refer to the Objective Chart 
//User's Guide.<nl>
//Written by Prakash Surendra (www.roguewave.com)


#ifdef _OC_DISCRETE

#ifndef __SRGDISCRETEFTR__
#define __SRGDISCRETEFTR__

#pragma once

#include "Chart\SRGCommonFTR.h"
#include "Chart\SRGLineGraph.h"
#include <StingrayExportDefs.h>

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

///////////////////////////////////////////////////////////////////////
// Autoduck comment block for SRGLineGraphFTR class
//
//@doc SRGLineGraphFTR
//@mfunc  | SRGLineGraphFTR | SRGLineGraphFTR | Initializing constructor
//@parm SRGLineGraph*& | ptrObj | A reference to the SRGLineGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGLineGraph type.

//@mfunc | SRGLineGraphFTR | ~SRGLineGraphFTR | Destructor

//@mfunc void | SRGLineGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGLineGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGLineGraph*&  | SRGLineGraphFTR | m_ptrObj | References the SRGLineGraph instance tied to this formatter.

////////////////////////////////////////////////////////////////////////
//$head XML Serialization (Discrete Graph Classes)
//$level 2

//@doc SRGLineGraphFTR
//@class XML Formatter for the SRGLineGraph class defined in Objective Chart. SRGLineGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGLineGraph>
//
class SRGLineGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGLineGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGLineGraph, SRGLineGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGLineGraphFTR(SRGLineGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLLINEGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGLineGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGLineGraph reference*/
	SRGLineGraph*& m_ptrObj;
};

#ifdef _AREA_GRAPH_

#include "Chart\SRGAreaGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGAreaGraph class

//@doc SRGAreaGraphFTR
//@mfunc  | SRGAreaGraphFTR | SRGAreaGraphFTR | Initializing constructor
//@parm SRGAreaGraph*& | ptrObj | A reference to the SRGAreaGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGAreaGraph type.

//@mfunc | SRGAreaGraphFTR | ~SRGAreaGraphFTR | Destructor

//@mfunc void | SRGAreaGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGAreaGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGAreaGraph*&  | SRGAreaGraphFTR | m_ptrObj | References the SRGAreaGraph instance tied to this formatter.

// adinsert

//@doc SRGAreaGraphFTR
//@class XML Formatter for the SRGAreaGraph class defined in Objective Chart. SRGAreaGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGAreaGraph>
//
class SRGAreaGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGAreaGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGAreaGraph, SRGAreaGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGAreaGraphFTR(SRGAreaGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLAREAGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGAreaGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGAreaGraph reference*/
	SRGAreaGraph*& m_ptrObj;
};

#endif	// _AREA_GRAPH_

#ifdef _BUBBLE_GRAPH_

#include "Chart\SRGBubbleGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGBubbleGraph class

//@doc SRGBubbleGraphFTR
//@mfunc  | SRGBubbleGraphFTR | SRGBubbleGraphFTR | Initializing constructor
//@parm SRGBubbleGraph*& | ptrObj | A reference to the SRGBubbleGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGBubbleGraph type.

//@mfunc | SRGBubbleGraphFTR | ~SRGBubbleGraphFTR | Destructor

//@mfunc void | SRGBubbleGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGBubbleGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGBubbleGraph*&  | SRGBubbleGraphFTR | m_ptrObj | References the SRGBubbleGraph instance tied to this formatter.

// adinsert

//@doc SRGBubbleGraphFTR
//@class XML Formatter for the SRGBubbleGraph class defined in Objective Chart. SRGBubbleGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGBubbleGraph>
//
class SRGBubbleGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGBubbleGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGBubbleGraph, SRGBubbleGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGBubbleGraphFTR(SRGBubbleGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLBUBBLEGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGBubbleGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGBubbleGraph reference*/
	SRGBubbleGraph*& m_ptrObj;
};

#endif // _BUBBLE_GRAPH

#ifdef _CANDLE_GRAPH_

#include "Chart\SRGCandleGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGCandleGraph class

//@doc SRGCandleGraphFTR
//@mfunc  | SRGCandleGraphFTR | SRGCandleGraphFTR | Initializing constructor
//@parm SRGCandleGraph*& | ptrObj | A reference to the SRGCandleGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGCandleGraph type.

//@mfunc | SRGCandleGraphFTR | ~SRGCandleGraphFTR | Destructor

//@mfunc void | SRGCandleGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGCandleGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGCandleGraph*&  | SRGCandleGraphFTR | m_ptrObj | References the SRGCandleGraph instance tied to this formatter.

// adinsert

//@doc SRGCandleGraphFTR
//@class XML Formatter for the SRGCandleGraph class defined in Objective Chart. SRGCandleGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGCandleGraph>
//
class SRGCandleGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGCandleGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGCandleGraph, SRGCandleGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGCandleGraphFTR(SRGCandleGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLCANDLEGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGCandleGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGCandleGraph reference*/
	SRGCandleGraph*& m_ptrObj;
};

#endif // _CANDLE_GRAPH_

#ifdef _FREESTYLE_GRAPH_

#include "Chart\SRGFreestyleGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGFreestyleGraph class

//@doc SRGFreestyleGraphFTR
//@mfunc  | SRGFreestyleGraphFTR | SRGFreestyleGraphFTR | Initializing constructor
//@parm SRGFreestyleGraph*& | ptrObj | A reference to the SRGFreestyleGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGFreestyleGraph type.

//@mfunc | SRGFreestyleGraphFTR | ~SRGFreestyleGraphFTR | Destructor

//@mfunc void | SRGFreestyleGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGFreestyleGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGFreestyleGraph*&  | SRGFreestyleGraphFTR | m_ptrObj | References the SRGFreestyleGraph instance tied to this formatter.

// adinsert

//@doc SRGFreestyleGraphFTR
//@class XML Formatter for the SRGFreestyleGraph class defined in Objective Chart. SRGFreestyleGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGFreestyleGraph>
//
class SRGFreestyleGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGFreestyleGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGFreestyleGraph, SRGFreestyleGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGFreestyleGraphFTR(SRGFreestyleGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLFREESTLGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGFreestyleGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGFreestyleGraph reference*/
	SRGFreestyleGraph*& m_ptrObj;
};

#endif // _FREESTYLE_GRAPH_

#ifdef _GANTT_GRAPH_

#include "Chart\SRGGanttGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGGanttGraph class

//@doc SRGGanttGraphFTR
//@mfunc  | SRGGanttGraphFTR | SRGGanttGraphFTR | Initializing constructor
//@parm SRGGanttGraph*& | ptrObj | A reference to the SRGGanttGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGGanttGraph type.

//@mfunc | SRGGanttGraphFTR | ~SRGGanttGraphFTR | Destructor

//@mfunc void | SRGGanttGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGGanttGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGGanttGraph*&  | SRGGanttGraphFTR | m_ptrObj | References the SRGGanttGraph instance tied to this formatter.

// adinsert

//@doc SRGGanttGraphFTR
//@class XML Formatter for the SRGGanttGraph class defined in Objective Chart. SRGGanttGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGGanttGraph>
//
class SRGGanttGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGGanttGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGGanttGraph, SRGGanttGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGGanttGraphFTR(SRGGanttGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLGANTTGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGGanttGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGGanttGraph reference*/
	SRGGanttGraph*& m_ptrObj;
};

#endif // _GANTT_GRAPH_

#ifdef _HBAR_GRAPH_

#include "Chart\SRGHBarGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGHBarGraph class

//@doc SRGHBarGraphFTR
//@mfunc  | SRGHBarGraphFTR | SRGHBarGraphFTR | Initializing constructor
//@parm SRGHBarGraph*& | ptrObj | A reference to the SRGHBarGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGHBarGraph type.

//@mfunc | SRGHBarGraphFTR | ~SRGHBarGraphFTR | Destructor

//@mfunc void | SRGHBarGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGHBarGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGHBarGraph*&  | SRGHBarGraphFTR | m_ptrObj | References the SRGHBarGraph instance tied to this formatter.

// adinsert

//@doc SRGHBarGraphFTR
//@class XML Formatter for the SRGHBarGraph class defined in Objective Chart. SRGHBarGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGHBarGraph>
//
class SRGHBarGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGHBarGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGHBarGraph, SRGHBarGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGHBarGraphFTR(SRGHBarGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLHBARGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGHBarGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGHBarGraph reference*/
	SRGHBarGraph*& m_ptrObj;
};

#endif // _HBAR_GRAPH_

#ifdef _ISOAREA_GRAPH_

#include "Chart\SRGIsoAreaGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGIsoAreaGraph class

//@doc SRGIsoAreaGraphFTR
//@mfunc  | SRGIsoAreaGraphFTR | SRGIsoAreaGraphFTR | Initializing constructor
//@parm SRGIsoAreaGraph*& | ptrObj | A reference to the SRGIsoAreaGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGIsoAreaGraph type.

//@mfunc | SRGIsoAreaGraphFTR | ~SRGIsoAreaGraphFTR | Destructor

//@mfunc void | SRGIsoAreaGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGIsoAreaGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGIsoAreaGraph*&  | SRGIsoAreaGraphFTR | m_ptrObj | References the SRGIsoAreaGraph instance tied to this formatter.

// adinsert

//@doc SRGIsoAreaGraphFTR
//@class XML Formatter for the SRGIsoAreaGraph class defined in Objective Chart. SRGIsoAreaGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGIsoAreaGraph>
//
class SRGIsoAreaGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGIsoAreaGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGIsoAreaGraph, SRGIsoAreaGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGIsoAreaGraphFTR(SRGIsoAreaGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLISOAREAGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGIsoAreaGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGIsoAreaGraph reference*/
	SRGIsoAreaGraph*& m_ptrObj;
};

#endif // _ISOAREA_GRAPH_

#ifdef _ISOBAR_GRAPH_

#include "Chart\SRGIsoBarGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGIsoBarGraph class

//@doc SRGIsoBarGraphFTR
//@mfunc  | SRGIsoBarGraphFTR | SRGIsoBarGraphFTR | Initializing constructor
//@parm SRGIsoBarGraph*& | ptrObj | A reference to the SRGIsoBarGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGIsoBarGraph type.

//@mfunc | SRGIsoBarGraphFTR | ~SRGIsoBarGraphFTR | Destructor

//@mfunc void | SRGIsoBarGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGIsoBarGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGIsoBarGraph*&  | SRGIsoBarGraphFTR | m_ptrObj | References the SRGIsoBarGraph instance tied to this formatter.

// adinsert

//@doc SRGIsoBarGraphFTR
//@class XML Formatter for the SRGIsoBarGraph class defined in Objective Chart. SRGIsoBarGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGIsoBarGraph>
//
class SRGIsoBarGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGIsoBarGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGIsoBarGraph, SRGIsoBarGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGIsoBarGraphFTR(SRGIsoBarGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLISOBARGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGIsoBarGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGIsoBarGraph reference*/
	SRGIsoBarGraph*& m_ptrObj;
};

#endif // _ISOBAR_GRAPH_

#ifdef _PIE_GRAPH_

#include "Chart\SRGPieGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGPieGraph class

//@doc SRGPieGraphFTR
//@mfunc  | SRGPieGraphFTR | SRGPieGraphFTR | Initializing constructor
//@parm SRGPieGraph*& | ptrObj | A reference to the SRGPieGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGPieGraph type.

//@mfunc | SRGPieGraphFTR | ~SRGPieGraphFTR | Destructor

//@mfunc void | SRGPieGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGPieGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGPieGraph*&  | SRGPieGraphFTR | m_ptrObj | References the SRGPieGraph instance tied to this formatter.

// adinsert

//@doc SRGPieGraphFTR
//@class XML Formatter for the SRGPieGraph class defined in Objective Chart. SRGPieGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGPieGraph>
//
class SRGPieGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGPieGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGPieGraph, SRGPieGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGPieGraphFTR(SRGPieGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLPIEGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGPieGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGPieGraph reference*/
	SRGPieGraph*& m_ptrObj;
};

#endif // _PIE_GRAPH_

#ifdef _POLAR_GRAPH_

#include "Chart\SRGPolarGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGPolarGraph class

//@doc SRGPolarGraphFTR
//@mfunc  | SRGPolarGraphFTR | SRGPolarGraphFTR | Initializing constructor
//@parm SRGPolarGraph*& | ptrObj | A reference to the SRGPolarGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGPolarGraph type.

//@mfunc | SRGPolarGraphFTR | ~SRGPolarGraphFTR | Destructor

//@mfunc void | SRGPolarGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGPolarGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGPolarGraph*&  | SRGPolarGraphFTR | m_ptrObj | References the SRGPolarGraph instance tied to this formatter.

// adinsert

//@doc SRGPolarGraphFTR
//@class XML Formatter for the SRGPolarGraph class defined in Objective Chart. SRGPolarGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGPolarGraph>
//
class SRGPolarGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGPolarGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGPolarGraph, SRGPolarGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGPolarGraphFTR(SRGPolarGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLPOLARGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGPolarGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGPolarGraph reference*/
	SRGPolarGraph*& m_ptrObj;
};

#endif // _POLAR_GRAPH_

#ifdef _SCATTER_GRAPH_

#include "Chart\SRGScatterGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGScatterGraph class

//@doc SRGScatterGraphFTR
//@mfunc  | SRGScatterGraphFTR | SRGScatterGraphFTR | Initializing constructor
//@parm SRGScatterGraph*& | ptrObj | A reference to the SRGScatterGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGScatterGraph type.

//@mfunc | SRGScatterGraphFTR | ~SRGScatterGraphFTR | Destructor

//@mfunc void | SRGScatterGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGScatterGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGScatterGraph*&  | SRGScatterGraphFTR | m_ptrObj | References the SRGScatterGraph instance tied to this formatter.

// adinsert

//@doc SRGScatterGraphFTR
//@class XML Formatter for the SRGScatterGraph class defined in Objective Chart. SRGScatterGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGScatterGraph>
//
class SRGScatterGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGScatterGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGScatterGraph, SRGScatterGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGScatterGraphFTR(SRGScatterGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLSCTTRGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGScatterGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGScatterGraph reference*/
	SRGScatterGraph*& m_ptrObj;
};

#endif // _SCATTER_GRAPH_

#ifdef _STACKHBAR_GRAPH_

#include "Chart\SRGStackHBarGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGStackHBarGraph class

//@doc SRGStackHBarGraphFTR
//@mfunc  | SRGStackHBarGraphFTR | SRGStackHBarGraphFTR | Initializing constructor
//@parm SRGStackHBarGraph*& | ptrObj | A reference to the SRGStackHBarGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGStackHBarGraph type.

//@mfunc | SRGStackHBarGraphFTR | ~SRGStackHBarGraphFTR | Destructor

//@mfunc void | SRGStackHBarGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGStackHBarGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGStackHBarGraph*&  | SRGStackHBarGraphFTR | m_ptrObj | References the SRGStackHBarGraph instance tied to this formatter.

// adinsert

//@doc SRGStackHBarGraphFTR
//@class XML Formatter for the SRGStackHBarGraph class defined in Objective Chart. SRGStackHBarGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGStackHBarGraph>
//
class SRGStackHBarGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGStackHBarGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGStackHBarGraph, SRGStackHBarGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGStackHBarGraphFTR(SRGStackHBarGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLSTKHBARGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGStackHBarGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGStackHBarGraph reference*/
	SRGStackHBarGraph*& m_ptrObj;
};

#endif // _STACKHBAR_GRAPH_

#ifdef _STACKVBAR_GRAPH_

#include "Chart\SRGStackVBarGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGStackVBarGraph class

//@doc SRGStackVBarGraphFTR
//@mfunc  | SRGStackVBarGraphFTR | SRGStackVBarGraphFTR | Initializing constructor
//@parm SRGStackVBarGraph*& | ptrObj | A reference to the SRGStackVBarGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGStackVBarGraph type.

//@mfunc | SRGStackVBarGraphFTR | ~SRGStackVBarGraphFTR | Destructor

//@mfunc void | SRGStackVBarGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGStackVBarGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGStackVBarGraph*&  | SRGStackVBarGraphFTR | m_ptrObj | References the SRGStackVBarGraph instance tied to this formatter.

// adinsert

//@doc SRGStackVBarGraphFTR
//@class XML Formatter for the SRGStackVBarGraph class defined in Objective Chart. SRGStackVBarGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGStackVBarGraph>
//
class SRGStackVBarGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGStackVBarGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGStackVBarGraph, SRGStackVBarGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGStackVBarGraphFTR(SRGStackVBarGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLSTKVBARGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGStackVBarGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGStackVBarGraph reference*/
	SRGStackVBarGraph*& m_ptrObj;
};

#endif // _STACKVBAR_GRAPH_

#ifdef _STEP_GRAPH_

#include "Chart\SRGStepGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGStepGraph class

//@doc SRGStepGraphFTR
//@mfunc  | SRGStepGraphFTR | SRGStepGraphFTR | Initializing constructor
//@parm SRGStepGraph*& | ptrObj | A reference to the SRGStepGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGStepGraph type.

//@mfunc | SRGStepGraphFTR | ~SRGStepGraphFTR | Destructor

//@mfunc void | SRGStepGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGStepGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGStepGraph*&  | SRGStepGraphFTR | m_ptrObj | References the SRGStepGraph instance tied to this formatter.

// adinsert

//@doc SRGStepGraphFTR
//@class XML Formatter for the SRGStepGraph class defined in Objective Chart. SRGStepGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGStepGraph>
//
class SRGStepGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGStepGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGStepGraph, SRGStepGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGStepGraphFTR(SRGStepGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLSTEPGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGStepGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGStepGraph reference*/
	SRGStepGraph*& m_ptrObj;
};

#endif // _STEP_GRAPH_

#ifdef _STOCK_GRAPH_

#include "Chart\SRGStockGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGStockGraph class

//@doc SRGStockGraphFTR
//@mfunc  | SRGStockGraphFTR | SRGStockGraphFTR | Initializing constructor
//@parm SRGStockGraph*& | ptrObj | A reference to the SRGStockGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGStockGraph type.

//@mfunc | SRGStockGraphFTR | ~SRGStockGraphFTR | Destructor

//@mfunc void | SRGStockGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGStockGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGStockGraph*&  | SRGStockGraphFTR | m_ptrObj | References the SRGStockGraph instance tied to this formatter.

// adinsert

//@doc SRGStockGraphFTR
//@class XML Formatter for the SRGStockGraph class defined in Objective Chart. SRGStockGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGStockGraph>
//
class SRGStockGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGStockGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGStockGraph, SRGStockGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGStockGraphFTR(SRGStockGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLSTOCKGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGStockGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGStockGraph reference*/
	SRGStockGraph*& m_ptrObj;
};

#endif // _STOCK_GRAPH_

#ifdef _STRATA_GRAPH_

#include "Chart\SRGStrataGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGStrataGraph class

//@doc SRGStrataGraphFTR
//@mfunc  | SRGStrataGraphFTR | SRGStrataGraphFTR | Initializing constructor
//@parm SRGStrataGraph*& | ptrObj | A reference to the SRGStrataGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGStrataGraph type.

//@mfunc | SRGStrataGraphFTR | ~SRGStrataGraphFTR | Destructor

//@mfunc void | SRGStrataGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGStrataGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGStrataGraph*&  | SRGStrataGraphFTR | m_ptrObj | References the SRGStrataGraph instance tied to this formatter.

// adinsert

//@doc SRGStrataGraphFTR
//@class XML Formatter for the SRGStrataGraph class defined in Objective Chart. SRGStrataGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGStrataGraph>
//
class SRGStrataGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGStrataGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGStrataGraph, SRGStrataGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGStrataGraphFTR(SRGStrataGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLSTRATAGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGStrataGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGStrataGraph reference*/
	SRGStrataGraph*& m_ptrObj;
};

#endif // _STRATA_GRAPH_

#ifdef _STRATAHBAR_GRAPH_

#include "Chart\SRGStrataHBarGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGStrataHBarGraph class

//@doc SRGStrataHBarGraphFTR
//@mfunc  | SRGStrataHBarGraphFTR | SRGStrataHBarGraphFTR | Initializing constructor
//@parm SRGStrataHBarGraph*& | ptrObj | A reference to the SRGStrataHBarGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGStrataHBarGraph type.

//@mfunc | SRGStrataHBarGraphFTR | ~SRGStrataHBarGraphFTR | Destructor

//@mfunc void | SRGStrataHBarGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGStrataHBarGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGStrataHBarGraph*&  | SRGStrataHBarGraphFTR | m_ptrObj | References the SRGStrataHBarGraph instance tied to this formatter.

// adinsert

//@doc SRGStrataHBarGraphFTR
//@class XML Formatter for the SRGStrataHBarGraph class defined in Objective Chart. SRGStrataHBarGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGStrataHBarGraph>
//
class SRGStrataHBarGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGStrataHBarGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGStrataHBarGraph, SRGStrataHBarGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGStrataHBarGraphFTR(SRGStrataHBarGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLSTRTHBARGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGStrataHBarGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/	
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGStrataHBarGraph reference*/
	SRGStrataHBarGraph*& m_ptrObj;
};

#endif // _STRATAHBAR_GRAPH_

#ifdef _STRATAVBAR_GRAPH_

#include "Chart\SRGStrataVBarGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGStrataVBarGraph class

//@doc SRGStrataVBarGraphFTR
//@mfunc  | SRGStrataVBarGraphFTR | SRGStrataVBarGraphFTR | Initializing constructor
//@parm SRGStrataVBarGraph*& | ptrObj | A reference to the SRGStrataVBarGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGStrataVBarGraph type.

//@mfunc | SRGStrataVBarGraphFTR | ~SRGStrataVBarGraphFTR | Destructor

//@mfunc void | SRGStrataVBarGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGStrataVBarGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGStrataVBarGraph*&  | SRGStrataVBarGraphFTR | m_ptrObj | References the SRGStrataVBarGraph instance tied to this formatter.

// adinsert

//@doc SRGStrataVBarGraphFTR
//@class XML Formatter for the SRGStrataVBarGraph class defined in Objective Chart. SRGStrataVBarGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGStrataVBarGraph>
//
class SRGStrataVBarGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGStrataVBarGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGStrataVBarGraph, SRGStrataVBarGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGStrataVBarGraphFTR(SRGStrataVBarGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLSTRTVBARGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGStrataVBarGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/	
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGStrataVBarGraph reference*/
	SRGStrataVBarGraph*& m_ptrObj;
};


#endif // _STRATAVBAR_GRAPH_

#ifdef _VBAR_GRAPH_

#include "Chart\SRGVBarGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGVBarGraph class

//@doc SRGVBarGraphFTR
//@mfunc  | SRGVBarGraphFTR | SRGVBarGraphFTR | Initializing constructor
//@parm SRGVBarGraph*& | ptrObj | A reference to the SRGVBarGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGVBarGraph type.

//@mfunc | SRGVBarGraphFTR | ~SRGVBarGraphFTR | Destructor

//@mfunc void | SRGVBarGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGVBarGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGVBarGraph*&  | SRGVBarGraphFTR | m_ptrObj | References the SRGVBarGraph instance tied to this formatter.

// adinsert

//@doc SRGVBarGraphFTR
//@class XML Formatter for the SRGVBarGraph class defined in Objective Chart. SRGVBarGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGVBarGraph>
//
class SRGVBarGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGVBarGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGVBarGraph, SRGVBarGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGVBarGraphFTR(SRGVBarGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLVBARGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGVBarGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/	
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGVBarGraph reference*/
	SRGVBarGraph*& m_ptrObj;
};

#endif // _VBAR_GRAPH_

#ifdef _VECTOR_GRAPH_

#include "Chart\SRGVectorGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGVectorGraph class

//@doc SRGVectorGraphFTR
//@mfunc  | SRGVectorGraphFTR | SRGVectorGraphFTR | Initializing constructor
//@parm SRGVectorGraph*& | ptrObj | A reference to the SRGVectorGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGVectorGraph type.

//@mfunc | SRGVectorGraphFTR | ~SRGVectorGraphFTR | Destructor

//@mfunc void | SRGVectorGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGVectorGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGVectorGraph*&  | SRGVectorGraphFTR | m_ptrObj | References the SRGVectorGraph instance tied to this formatter.

// adinsert

//@doc SRGVectorGraphFTR
//@class XML Formatter for the SRGVectorGraph class defined in Objective Chart. SRGVectorGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGVectorGraph>
//
class SRGVectorGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGVectorGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGVectorGraph, SRGVectorGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGVectorGraphFTR(SRGVectorGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLVECTORGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGVectorGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/	
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGVectorGraph reference*/
	SRGVectorGraph*& m_ptrObj;
};


#endif // _VECTOR_GRAPH_

#ifdef _WEB_GRAPH_

#include "Chart\SRGWebGraph.h"

///////////////////////////////////////////////////////////////////////////
// XML Formatter for the SRGWebGraph class

//@doc SRGWebGraphFTR
//@mfunc  | SRGWebGraphFTR | SRGWebGraphFTR | Initializing constructor
//@parm SRGWebGraph*& | ptrObj | A reference to the SRGWebGraph instance.
//@parm LPCTSTR | strTag | The XML tag descriptor for the SRGWebGraph type.

//@mfunc | SRGWebGraphFTR | ~SRGWebGraphFTR | Destructor

//@mfunc void | SRGWebGraphFTR | XMLSerialize | Does a read/write of the XML formatted SRGWebGraph data 
//from/to the XML archiver object.
//@rdesc void 
//@parm SECXMLArchive& | ar | Reference to the XML archive object
//@rem Implementation of the IXMLSerialize::XMLSerialize() virtual. XMLSerialize() is analogous 
//to the CObject::Serialize() routine and will be invoked, either directly or indirectly, by the
//document class. 

//@mdata SRGWebGraph*&  | SRGWebGraphFTR | m_ptrObj | References the SRGWebGraph instance tied to this formatter.

// adinsert

//@doc SRGWebGraphFTR
//@class XML Formatter for the SRGWebGraph class defined in Objective Chart. SRGWebGraphFTR, through it's SRGDisplayBaseFTR 
//base, derives from the SFL CXMLSerializeImp base class and implements the IXMLSerialize interface.
//
//See <c SRGWebGraph>
//
class SRGWebGraphFTR : public SRGDisplayBaseFTR
{
BEGIN_SEC_XMLFORMATTERMAP(SRGWebGraphFTR)
XMLFORMATTERMAP_ADDENTRY(SRGWebGraph, SRGWebGraphFTR)
END_SEC_XMLFORMATTERMAP()

public:
	//@cmember
	/* Constructor*/
	inline SRGWebGraphFTR(SRGWebGraph*& ptrObj, LPCTSTR strTag=SECXMLLoadString(IDS_SRG_XMLWEBGPH))
		: SRGDisplayBaseFTR((SRGDisplayBase*&)ptrObj, strTag), m_ptrObj(ptrObj)
	{
	}

	//@cmember
	/* Destructor*/
	inline virtual ~SRGWebGraphFTR()
	{
	}

	//@cmember
	/* Serializing function*/	
	inline virtual void XMLSerialize(SECXMLArchive& ar)
	{
		SRGDisplayBaseFTR::XMLSerialize(ar);		
	}

protected:
	//@cmember
	/* SRGWebGraph reference*/
	SRGWebGraph*& m_ptrObj;
};

#endif //_WEB_GRAPH_

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SRGDISCRETEFTR__

#endif // _OC_DISCRETE
