///////////////////////////////////////////////////////////////////////////////
// XMLFTRFactory.h : SECXMLFormatterFactory
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
//
// Authors:      Praveen Ramesh and Prakash Surendra
// Description:  Formatter Factory class used for runtime type discovery
//

#ifndef __SFL_XMLFTRFACTORY_H__
#define __SFL_XMLFTRFACTORY_H__

#pragma once

#include <foundation\XMLSerCore\XMLCommon.h>
#include <StingrayExportDefs.h>

#ifdef _MT
extern void AFXAPI AfxLockGlobals(int nLockType);
extern void AFXAPI AfxUnlockGlobals(int nLockType);
#else
#define AfxLockGlobals(nLockType)
#define AfxUnlockGlobals(nLockType)
#endif

// Same as CRIT_PROCESSLOCAL
#define  SFLCRIT_PROCESSLOCAL 16

namespace stingray {
	namespace foundation {


// Interface implemented for each formatter by the FTR macros
interface IFTRInitializer
{
	virtual void UpdateFTRFactory() = 0;
};


// Interface implemented by the Formatter Factory
interface IFTRCreator
{
	virtual CXMLSerializeImp* CreateFTR(CObject*& pObj) = 0;
};


template<class classX, class classFTR>
class CFTRCreator : public IFTRCreator
{
public:
	CXMLSerializeImp* CreateFTR(CObject*& pObj)
	{
		classFTR* pFTR = new classFTR((classX*&)pObj);
		ASSERT(pFTR != NULL);
		return (CXMLSerializeImp*)pFTR;
	}
};



///////////////////////////////////////////////////////////////////////////
//@doc SECXMLFormatterFactory
//
//@class SECXMLFormatterFactory | The SECXMLFormatterFactory class implements the SFL XML Formatter Factory. The formatter
// factory is a global singleton used by the XML serialization framework to provide a polymorphic persistence mechanism
// to mimic that provided by MFC for the collection classes for CObject derived types. Building SFL with the XML Serialization
// option selected in the build wizard will define the global instance of the factory object.<nl>
//
// Normally the formatter factory is never directly referenced from within the application. Registration of the formatter
// classes, for the various serializable types, with the factory should be done using the XMLFORMATTERMAP series of macros. 
// Once the registration macros are in place, calling the <f SECXMLInitFTRFactory> global function will initialize the
// factory and update the formatter entries.<nl>
//
// The following macros may be used for registering formatters,<nl>
//<nl>
// BEGIN_SEC_XMLFORMATTERMAP(classThis) - Begins a declaration of the formatter map in the hosting class(classThis).<nl>
// XMLFORMATTERMAP_ADDENTRY(classX, classFTR)  - Adds an association of the serializable class(classX) with it's formatter(classFTR).<nl>
// END_SEC_XMLFORMATTERMAP()   - Ends the declaration of the map.<nl>
// DEFINE_SEC_XMLFORMATTERMAP(classThis) - Defines the formatter map.<nl> 
//
// See Also <f SECXMLInitFTRFactory>
//
class SECXMLFormatterFactory
{
public:
	inline SECXMLFormatterFactory() 
	{
		m_bInitialized = FALSE;
	}

	inline virtual ~SECXMLFormatterFactory()
	{
		m_listIFTRInit.RemoveAll();

		if(!m_mapTagToRTTI.IsEmpty())
			m_mapTagToRTTI.RemoveAll();

		if(!m_mapRTTIToIFTR.IsEmpty())
		{
			for( POSITION pos = m_mapRTTIToIFTR.GetStartPosition(); pos != NULL; )
			{
				CRuntimeClass* pRTTI = NULL;
				IFTRCreator* pCreator = NULL;
				m_mapRTTIToIFTR.GetNextAssoc( pos, pRTTI, pCreator );
				if(pCreator != NULL)
				{
					delete pCreator;
					pCreator = NULL; // QA: 31948
				}
			}
			m_mapRTTIToIFTR.RemoveAll();
		}
	}

public:
	inline void GetFTRFromTag(CString strTag, CObject*& pObject, CXMLSerializeImp*& pFTR)
	{
		AfxLockGlobals(SFLCRIT_PROCESSLOCAL);

		ASSERT(!strTag.IsEmpty());
		// Look up the CRuntimeClass* for the tag passed in and create an instance of this object
		CRuntimeClass* pRTTI = NULL;
		m_mapTagToRTTI.Lookup(strTag, pRTTI);
		ASSERT(pRTTI != NULL);
		pObject = pRTTI->CreateObject();
		ASSERT_VALID(pObject);

		// Ok, now retrieve the FTRCreator for the particular RTTI ptr and use it to create the Formatter object
		IFTRCreator* pCreator = NULL;
		m_mapRTTIToIFTR.Lookup(pRTTI, pCreator);
		ASSERT(pCreator != NULL);
		pFTR = pCreator->CreateFTR(pObject);

		AfxUnlockGlobals(SFLCRIT_PROCESSLOCAL);
	}

	inline void GetFTRFromObject(CObject*& pObject, CXMLSerializeImp*& pFTR)
	{
		ASSERT_VALID(pObject);

		AfxLockGlobals(SFLCRIT_PROCESSLOCAL);

		CRuntimeClass* pRTTI = pObject->GetRuntimeClass(); 
		ASSERT(pRTTI != NULL);
		
		// Iterate RTTI-IFTR map, get the FTRCreator and create a formatter for this object
		IFTRCreator* pCreator = NULL;
		m_mapRTTIToIFTR.Lookup(pRTTI, pCreator);
		ASSERT(pCreator != NULL);
		pFTR = pCreator->CreateFTR(pObject);

		AfxUnlockGlobals(SFLCRIT_PROCESSLOCAL);
	}

	inline BOOL IsInitialized() { return m_bInitialized; }

	inline void AddToTagRTTIMap(CString strTag, CRuntimeClass* pRTTI)
	{
		ASSERT((!strTag.IsEmpty()) && (pRTTI != NULL));
		
		AfxLockGlobals(SFLCRIT_PROCESSLOCAL);
		
		CRuntimeClass* pExists = NULL;
		if(!m_mapTagToRTTI.Lookup(strTag, pExists))
			m_mapTagToRTTI.SetAt(strTag, pRTTI);
		
		AfxUnlockGlobals(SFLCRIT_PROCESSLOCAL);
	}	

	inline void AddToRTTIIFTRMap(CRuntimeClass* pRTTI, IFTRCreator* pCreator)
	{
		ASSERT(pRTTI != NULL && pCreator != NULL);

		AfxLockGlobals(SFLCRIT_PROCESSLOCAL);

		IFTRCreator* pExists = NULL;
		if(!m_mapRTTIToIFTR.Lookup(pRTTI, pExists))
			m_mapRTTIToIFTR.SetAt(pRTTI, pCreator);
		else
			delete pCreator;

		AfxUnlockGlobals(SFLCRIT_PROCESSLOCAL);
	}

	inline void AddToInitializerList(IFTRInitializer* pIFTRInit)
	{
		ASSERT(pIFTRInit != NULL);
		m_listIFTRInit.AddTail(pIFTRInit);		
	}
	
protected:
	typedef CTypedPtrMap<CMapStringToPtr, CString, CRuntimeClass*> _mapStrToRTTI;
	typedef CTypedPtrMap<CMapPtrToPtr, CRuntimeClass*, IFTRCreator*> _mapRTTIToIFTR;
	typedef CTypedPtrList<CPtrList, IFTRInitializer*> _listIFTRInitializer;
	_mapStrToRTTI m_mapTagToRTTI;
	_mapRTTIToIFTR m_mapRTTIToIFTR;
	_listIFTRInitializer m_listIFTRInit;
	BOOL m_bInitialized;

	FOUNDATION_API friend void AFXAPI SECXMLInitFTRFactory();
};



///////////////////////////////////////////////////////////////////////////
//@doc SECXMLInitFTRFactory 
//
//@func void | SECXMLInitFTRFactory | Global API for initializing the SFL XML Formatter Factory singleton.
// SECXMLInitFTRFactory should be called only once, preferrably from the application's InitInstance routine. 
//@rdesc void
//@comm The SECXMLInitFTRFactory function is typically called to initialize the formatter factory when using the MFC 
// collection classes that support polymorphic serialization of CObject derived types. Calling SECXMLInitFTRFactory will
// register, with the formatter factory, all XML formatters that have been defined with the XMLFORMATTERMAP series of macros.
// 
// See Also <c SECXMLFormatterFactory>
//
FOUNDATION_API void AFXAPI SECXMLInitFTRFactory();

// Global that retrieves a reference to the singleton factory instance
FOUNDATION_API SECXMLFormatterFactory* AFXAPI SECXMLGetFTRFactory();

// XML Formatter macros

#define BEGIN_SEC_XMLFORMATTERMAP(classThis) \
public: \
	class classThis##FTRFactoryInitializer : public IFTRInitializer \
	{ \
	public: \
	classThis##FTRFactoryInitializer() \
	{ \
		SECXMLFormatterFactory* pFTRFactory = SECXMLGetFTRFactory(); \
		pFTRFactory->AddToInitializerList(this); \
	} \
	virtual void UpdateFTRFactory() { \
	SECXMLFormatterFactory* pFTRFactory = SECXMLGetFTRFactory(); \
	TCHAR strTagName[MAX_TAGNAME_SIZE] = {'\0'};

#define XMLFORMATTERMAP_ADDENTRY(classX, classFTR) \
	classX* pClassX = NULL; \
	classFTR* pFTR##classX = new classFTR(pClassX); \
	pFTR##classX->GetElementType(strTagName); \
	delete pFTR##classX; \
	CRuntimeClass* pRTTI = (CRuntimeClass*)&classX::class##classX; \
	pFTRFactory->AddToTagRTTIMap(strTagName, pRTTI); \
	CFTRCreator<classX, classFTR>* pFTRCreator##classX = new CFTRCreator<classX, classFTR>; \
	pFTRFactory->AddToRTTIIFTRMap(pRTTI, (IFTRCreator*)pFTRCreator##classX);

#define END_SEC_XMLFORMATTERMAP() } \
	};

#define DEFINE_SEC_XMLFORMATTERMAP(classThis) \
classThis::classThis##FTRFactoryInitializer classThis##FTRInstance;


}; // namespace stingray::foundation
}; // namespace stingray

#endif //__SFL_XMLFTRFACTORY_H__

