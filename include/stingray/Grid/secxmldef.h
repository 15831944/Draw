///////////////////////////////////////////////////////////////////////////////
// secxmldef.h
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
// Author: Daniel Jebaraj       
// Description: XML read/write helper classes
//

#ifndef __SEC_XML_DEF_H__
#define __SEC_XML_DEF_H__

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

// #include <StingrayExportDefs.h>

#pragma warning(disable: 4786)

namespace rw
{

//
// GridMFC Extension DLL
// initialize declaration context
//

// All common defines used in the Stingray Objective Toolkit XML read/write system go in here

typedef DWORD RESOLVERID;
typedef DWORD ENTRYID;

const RESOLVERID RESDEFID = 0xFFFF;
const ENTRYID	ENTRYDEFID = 0xFFFFFFFF;
const ENTRYID	SECENTRYROOTID = 0xFFFFFFFF-1;

const DWORD SECXMLDEFBUFSIZE	= 500;
const DWORD SECXMLDEFLBUFSIZE	= 2500;

#define SEC_XML_ROOT	_T("root")

#define base_resolver(scope)\
scope IXMLRWResolver, scope CEntryValueHolder

// @func void | SetEntryValue | Helper macro for setting void pointers. Use this variant when a delete is needed to free
// memory. Use <f SetEntryValue_NoManage> if you want to manage the memory yourself. The class has to be derived from
// <c CEntryValueHolder> to use this macro. Default resolvers are derived from this class.
//
// @parm id of the slot to be used| key | Specifies a pointer to the first string.
//
// @parm class type| class_type | Specifies a pointer to the second string.
//
// @parm type *| pointer_value | Specifies a pointer to the second string.
//
// @xref <f SetEntryValueAr> <f SetEntryValue_NoManage>
#define SetEntryValue(key, class_type, pointer_value)\
typedef void (CEntryValueHolder::*pfn##key)(DWORD dwKey, class_type* p, bool bManage/* = true*/, bool bSimp/* = true*/);\
pfn##key fn##key = &CEntryValueHolder::_SetEntryValue;\
(this->*fn##key)(key, pointer_value, true, true);

// @func void | SetEntryValueAr | Helper macro for setting void pointers. Use this variant when a delete []
// is needed. Use <f SetEntryValue_NoManage> if you want to manage the memory yourself. The class has to be derived from
// <c CEntryValueHolder> to use this macro. Default resolvers are derived from this class.
//
// @parm id of the slot to be used| key | Specifies a pointer to the first string.
//
// @parm class type| class_type | Specifies a pointer to the second string.
//
// @parm type *| pointer_value | Specifies a pointer to the second string.
//
// @xref <f SetEntryValue> <f SetEntryValue_NoManage>
#define SetEntryValueAr(key, class_type, pointer_value)\
typedef void (CEntryValueHolder::*pfn##key)(DWORD dwKey, class_type* p, bool bManage = true, bool bSimp = true);\
pfn##key fn##key = &CEntryValueHolder::_SetEntryValue;\
(this->*fn##key)(key, pointer_value, true, false);


// @func void | SetEntryValue_NoManage | Helper macro for setting void pointers. Use this variant if you want
// to manage the memory yourself. The class has to be derived from
// <c CEntryValueHolder> to use this macro. Default resolvers are derived from this class.
//
// @parm id of the slot to be used| key | Specifies a pointer to the first string.
//
// @parm class type| class_type | Specifies a pointer to the second string.
//
// @parm type *| pointer_value | Specifies a pointer to the second string.
// @xref <f SetEntryValueAr> <f SetEntryValue>
#define SetEntryValue_NoManage(key, class_type, pointer_value)\
typedef void (CEntryValueHolder::*pfn##key)(DWORD dwKey, class_type* p, bool bManage = true, bool bSimp = true);\
pfn##key fn##key = &CEntryValueHolder::_SetEntryValue;\
(this->*fn##key)(key, pointer_value, false);


//@enum eTypeRWContext 
enum eTypeRWContext
{
	eWriteStartLoop, //@emem The write loop is starting.
	eWriteEndLoop,//@emem The write loop is ending.
	eWriteGetValue,//@emem Specifies call context is GetValue when writing data.
	eWriteContinueLoop,//@emem System is asking whether the write operation should continue.
	eReadStartLoop,//@emem The read loop is starting
	eReadEndLoop,//@emem The read loop is ending
	eReadSetValue,//@emem Specifies call context is SetValue when reading data. 
};


enum eTypeSeen
{
	eNotSeen = 0,
	eRefused = 0x1,
	eOk = 0x2,
};

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		//#include "msxml6.h"
		struct /*MSXML6::*/IXMLDOMDocument;
		struct /*MSXML6::*/IXMLDOMNode;
	#else
		struct MSXML::IXMLDOMDocument;
		struct MSXML::IXMLDOMNode;
	#endif
#else
	struct MSXML::IXMLDOMDocument;
	struct MSXML::IXMLDOMNode;
#endif

class XML_ENTRY_MAP;

//@doc XML_ENTRY_PARAM
//@class XML_ENTRY_PARAM |
//This class is used to pass arguments to handler functions. For more details on handler functions please refer to
// IXMLWResolver>. The members of this structure of interest are listed below.

 //@mdata const XML_ENTRY_MAP*  | XML_ENTRY_PARAM | pEntry | Holds the <c XML_ENTRY_MAP> entry.
// This entry holds information that describes the node that is being written out or read in.

//@mdata MSXML::IXMLDOMNode*  | XML_ENTRY_PARAM | pContextNode | Context specific node. This has the pointer to the
//parent node when the context is eWriteGetValue (<t eTypeRWContext>). It has the pointer to the last node that was
//added when the context is eWriteContinueLoop (<t eTypeRWContext>). It is NULL at all other times.

//@mdata DWORD  | XML_ENTRY_PARAM | dwContext | This is the DWORD value that is initialized as part of the handler 
//context using the WRITE_MAP_ENTRY family of macros (<I xml write map macros>). 

//@mdata void*  | XML_ENTRY_PARAM | pVoidInfo | This is the void* value that is initialized as part of the handler 
//context using the WRITE_MAP_ENTRY family of macros (<I xml write map macros>). 

class GRID_API XML_ENTRY_PARAM
{
public:
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		XML_ENTRY_PARAM(const XML_ENTRY_MAP* _pEntry, 
			::IXMLDOMNode* _pContextNode,
			DWORD _dwContext,
			void* _pVoidInfo);
	#else
		XML_ENTRY_PARAM(const XML_ENTRY_MAP* _pEntry, 
			MSXML::IXMLDOMNode* _pContextNode,
			DWORD _dwContext,
			void* _pVoidInfo);
	#endif
#else
	XML_ENTRY_PARAM(const XML_ENTRY_MAP* _pEntry, 
		MSXML::IXMLDOMNode* _pContextNode,
		DWORD _dwContext,
		void* _pVoidInfo);
#endif
	
	//@cmember
	/* Holds the <c XML_ENTRY_MAP> entry. */
	const XML_ENTRY_MAP* pEntry;
	//@cmember
	/* Context specific node. The value of this will be different under different contexts. */
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		::IXMLDOMNode* pContextNode;
	#else
		MSXML::IXMLDOMNode* pContextNode;
	#endif
#else
	MSXML::IXMLDOMNode* pContextNode;
#endif
	//@cmember
	/* DWORD value that is context specific. */
	DWORD dwContext;
	//@cmember
	/* Void pointer that is context specific. */
	void* pVoidInfo;
};

// macros for the resolver
//@topic xml write map macros |
/*
These macros implement the <c IXMLWResolver> and map it to handler functions with the signature (it also has to be
a member)

  void Handler(<c XML_ENTRY_PARAM>& pParam, <t eTypeRWContext> context, bool& bRetval, <c XMLVALUE>& pValue);

BEGIN_WRITE_MAP(class_name)
This macro just takes the name of the class that implements the resolver.

END_WRITE_MAP()
No arguments. Simply closes the declaration.

WRITE_MAP_DEF_ENTRY(fn)
The default handler that is to be used. If a handler is not found for an id then this will be used if initialized.
The signature for this function has to be as above.

WRITE_MAP_ENTRY(id, fn)
WRITE_MAP_ENTRY1(id, fn, dw)
WRITE_MAP_ENTRY2(id, fn, dw, pv)
WRITE_MAP_ENTRY3(id, fn, pv)
These tie a node id with a function along with optional context information. This can be a DWORD and/or a void*.

WRITE_MAP_ENTRY_RANGE(idStart, idEnd, fn)
This macro ties an entire range of id values to a single function.

DECLARE_WRITE_MAP(class_name, enumType)
This macro declares the write map in the class declaration.
*/
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		#define IXMLDN ::IXMLDOMNode
	#else
		#define IXMLDN MSXML::IXMLDOMNode
	#endif
#else
	#define IXMLDN MSXML::IXMLDOMNode
#endif


#define BEGIN_WRITE_MAP(class_name)\
bool class_name::OnStartWriteLoop(const XML_ENTRY_MAP* pEntry)\
{\
	bool bRetval(true);\
	\
	class_name::__eType id = (__eType) pEntry->dwID;\
	\
	__handlerMap::iterator	it;\
	if( (it = m_mpHandlers.find(id)) != m_mpHandlers.end())\
	{\
		XML_ENTRY_PARAM param(pEntry, NULL, (*it).second.dwContext, (*it).second.pVoidInfo );\
		(this->*((*it).second.handler))(param, eWriteStartLoop, bRetval, __xmlValueDummy);\
	}\
\
	return bRetval;\
}\
\
bool class_name::OnGetValue(const XML_ENTRY_MAP* pEntry, IXMLDN* pParentNode, XMLVALUE& value)\
{\
	bool bRetval(true);\
\
	__eType id = (__eType) pEntry->dwID;\
\
	__handlerMap::iterator	it;\
	if( (it = m_mpHandlers.find(id)) != m_mpHandlers.end())\
	{\
		XML_ENTRY_PARAM param(pEntry, pParentNode, (*it).second.dwContext, (*it).second.pVoidInfo);\
		(this->*((*it).second.handler))(param, eWriteGetValue, bRetval, value);\
	}\
	else if(m_pDefHandler != NULL)\
	{\
		XML_ENTRY_PARAM param(pEntry, pParentNode, (*it).second.dwContext, (*it).second.pVoidInfo);\
		(this->*(m_pDefHandler))(param, eWriteGetValue, bRetval, value);\
	}\
\
	return bRetval;\
}\
\
\
bool class_name::OnCanContinueWriteLoop(const XML_ENTRY_MAP* pEntry, IXMLDN* pNodeAdded)\
{\
	bool bRetval(false);\
\
	__eType id = (__eType) pEntry->dwID;\
\
	__handlerMap::iterator	it;\
	if( (it = m_mpHandlers.find(id)) != m_mpHandlers.end() )\
	{\
		XML_ENTRY_PARAM param(pEntry, pNodeAdded, (*it).second.dwContext, (*it).second.pVoidInfo);\
		(this->*((*it).second.handler))(param, eWriteContinueLoop, bRetval, __xmlValueDummy);\
	}\
\
	return bRetval;\
}\
\
bool class_name::OnEndWriteLoop(const XML_ENTRY_MAP* pEntry)\
{\
	bool bRetval(false);\
\
	__eType id = (__eType) pEntry->dwID;\
\
	__handlerMap::iterator	it;\
	if( (it = m_mpHandlers.find(id)) != m_mpHandlers.end())\
	{\
		XML_ENTRY_PARAM param(pEntry, NULL, (*it).second.dwContext, (*it).second.pVoidInfo);\
		(this->*((*it).second.handler))(param, eWriteEndLoop, bRetval, __xmlValueDummy);\
	}\
\
	return bRetval;\
}\
void class_name::OnStartWrite()\
{\
\
}\
\
void class_name::OnCompleteWrite()\
{\
Cleanup();\
}\
void class_name::OnStartRead()\
{\
\
}\
\
void class_name::OnCompleteRead()\
{\
\
}\
\
bool class_name::OnStartReadLoop(const XML_ENTRY_MAP* pEntry)\
{\
	TRACE1("The ID in OnStartReadLoop is %x\n", pEntry->dwID);\
	bool bRetval(true);\
\
	__eType id = (__eType) pEntry->dwID;\
\
	__handlerMap::iterator	it;\
	if( (it = m_mpHandlers.find(id)) != m_mpHandlers.end())\
	{\
		XML_ENTRY_PARAM param(pEntry, NULL, (*it).second.dwContext, (*it).second.pVoidInfo);\
		(this->*((*it).second.handler))(param, eReadStartLoop, bRetval, __xmlValueDummy);\
	}\
\
	return bRetval;\
}\
\
bool class_name::OnSetValue(const XML_ENTRY_MAP* pEntry, IXMLDN* pThisNode, XMLVALUE& xmlValue)\
{\
	TRACE1("The ID in OnSetValue is %x\n", pEntry->dwID);\
	TRACE1("The node name is %s:", pEntry->pszName);\
	TRACE1("The value is %s\n", (LPCTSTR) xmlValue);\
\
	bool bRetval(false);\
\
	__eType id = (__eType) pEntry->dwID;\
\
	__handlerMap::iterator	it;\
	if( (it = m_mpHandlers.find(id)) != m_mpHandlers.end())\
	{\
		XML_ENTRY_PARAM param(pEntry, NULL, (*it).second.dwContext, (*it).second.pVoidInfo);\
		(this->*((*it).second.handler))(param, eReadSetValue, bRetval, xmlValue);\
	}\
\
	return bRetval;\
}\
bool class_name::SetContext(class_name::__eType e, DWORD dw)\
{\
	__handlerMap::iterator	it;\
	if( (it = m_mpHandlers.find(e)) == m_mpHandlers.end())\
		return false;\
\
	(*it).second.dwContext = dw;\
\
	return true;\
}\
bool class_name::SetValuePtr(class_name::__eType e, void* p)\
{\
	__handlerMap::iterator	it;\
	if( (it = m_mpHandlers.find(e)) == m_mpHandlers.end())\
		return false;\
\
	(*it).second.pVoidInfo = p;\
\
	return true;\
}\
void class_name::Initialize()\
{\
	m_pDefHandler = NULL;	


#define END_WRITE_MAP()\
}

#define WRITE_MAP_DEF_ENTRY(fn)\
	m_pDefHandler = fn;

#define WRITE_MAP_ENTRY(id, fn)\
m_mpHandlers[id] = __mapData(__name::fn, 0, NULL);

#define WRITE_MAP_ENTRY1(id, fn, dw)\
m_mpHandlers[id] = __mapData(__name::fn, dw, NULL);

#define WRITE_MAP_ENTRY2(id, fn, dw, pv)\
m_mpHandlers[id] = __mapData(__name::fn, dw, pv);

#define WRITE_MAP_ENTRY3(id, fn, pv)\
m_mpHandlers[id] = __mapData(__name::fn, 0, pv);


// Careful when using these! Make sure that your values are
// indeed in sequence
#define WRITE_MAP_ENTRY_RANGE(idStart, idEnd, fn)\
for (DWORD dw = idStart; dw <= idEnd; dw++)\
m_mpHandlers[dw] = __mapData(__name::fn, 0, NULL);


#define DECLARE_WRITE_MAP(class_name, enumType)\
public:\
typedef void (class_name::*pfnHandler)(XML_ENTRY_PARAM& pParam, eTypeRWContext context, bool& bRetval, XMLVALUE& pValue);\
typedef class_name __name;\
typedef enumType __eType;\
struct __mapData\
{\
	__mapData(){\
		handler = NULL;\
		dwContext = 0;\
		pVoidInfo = NULL;\
	}\
	__mapData(pfnHandler _handler, DWORD _dwContext, void* _pContextInfo){\
		handler = _handler;\
		dwContext = _dwContext;\
		pVoidInfo = _pContextInfo;\
	}\
\
	pfnHandler handler;\
	DWORD dwContext;\
	void* pVoidInfo;\
};\
typedef map<DWORD, __mapData> class_name##HandlerMap;\
void Initialize();\
bool SetContext(enumType e, DWORD dw);\
bool SetValuePtr(enumType e, void* p);\
virtual void OnStartWrite();\
virtual void OnCompleteWrite();\
virtual bool OnStartWriteLoop(const XML_ENTRY_MAP* pEntry);\
virtual bool OnEndWriteLoop(const XML_ENTRY_MAP* pEntry);\
virtual bool OnCanContinueWriteLoop(const XML_ENTRY_MAP* pEntry, IXMLDN* pNodeAdded);\
virtual bool OnGetValue(const XML_ENTRY_MAP* pEntry, IXMLDN* pParentNode, XMLVALUE& xmlValue);\
\
virtual void OnStartRead();\
virtual void OnCompleteRead();\
virtual bool OnStartReadLoop(const XML_ENTRY_MAP* pEntry);\
virtual bool OnSetValue(const XML_ENTRY_MAP* pEntry, IXMLDN* pThisNode, XMLVALUE& xmlValue);\
\
protected:\
XMLVALUE __xmlValueDummy;\
pfnHandler m_pDefHandler;\
class_name##HandlerMap m_mpHandlers;\
typedef class_name##HandlerMap	__handlerMap;


// Macros for the map

//@topic xml map |
/*
These macros help declare and implement a map of <c XML_ENTRY_MAP> objects.

DECLARE_XML_MAP(class_name)
Declares the XML map in the class (that aggregates the map).

BEGIN_XML_MAP(class_name)
Start the implementation with this entry.

END_XML_MAP()
End the implementation with this entry.

SEC_XML_NEST()
Use this macro when the element being defined has nested nodes.

SEC_XML_END_NEST()
Use this macro to terminate the nested entries for this node.

SEC_XML_START()
Use this macro to indicate that you starting to define a node.

SEC_XML_END()
Use this macro to indicate that you are ending the node definition.

WRAP(text)
Use this macro to combine the START and END macros for nodes that do not have any
children.

XML_ROOT_ENTRY()
Start any map with this entry.

XML_ELEMENT_ENTRY(name, id)
Defines a NODE_ELEMENT.

XML_TEXT_ENTRY(name, id)
Defines a text node (NODE_TEXT).

XML_CDATA_ENTRY(name, id)
Defines a node of type NODE_CDATA_SECTION.

XML_ENTITY_ENTRY(name)
Defines a node of type NODE_ENTITY_REFERENCE.

XML_ENTITY_ATTRIB_ENTRY(name, id)
Defines a node that is an attribute (defined by an entity reference).

XML_ATTRIBUTE_ENTRY(name, id)
Defines a node that is of type NODE_ATTRIBUTE.

XML_COMMENT_ENTRY(name, id)
Defines a node that is of type NODE_COMMENT.

XML_PROCESS_ENTRY(name, id)
Defines a node that is of type NODE_PROCESSING_INSTRUCTION.

XML_ROOT_ENTRY_NS(name, id, ns)
Defines a root node with a namespace specification.

XML_ELEMENT_ENTRY_NS(name, id, ns)
Defines a NODE_ELEMENT with a namespace specification.

XML_TEXT_ENTRY_NS(name, id, ns)
Defines a text entry with a namespace specification.

Abbreviations used:
name: Name of the node
id: Unique id for the node.
ns: Qualifying namespace.
class_name: The name of the class enclosing this map.
*/

#define DECLARE_XML_MAP(class_name)\
	public:\
		virtual void Initialize();


#define BEGIN_XML_MAP(class_name)\
void class_name::Initialize()\
{
	
#define END_XML_MAP()\
}

#define SEC_XML_NEST()\
{

#define SEC_XML_END_NEST()\
}

#define SEC_XML_START()\
{

#define SEC_XML_END()\
}

#define WRAP(text)\
{\
	text\
}

// Entry macros without Namespace specification

// ROOT Entry

#define XML_ROOT_ENTRY()\
m_pXMLMap = new XML_ENTRY_MAP(_T("xml"), SECENTRYROOTID, NODE_PROCESSING_INSTRUCTION);\
list<XML_ENTRY_MAP*>* pList = &m_pXMLMap->listXMLMapEntries_p;

// Element entry

#define XML_ELEMENT_ENTRY(name, id)\
XML_ENTRY_MAP* pEntry = new XML_ENTRY_MAP(_T(#name), id, NODE_ELEMENT);\
pList->push_back(pEntry);\
list<XML_ENTRY_MAP*>* pList = &pEntry->listXMLMapEntries_p;
		

// Text entry

#define XML_TEXT_ENTRY(name, id)\
XML_ENTRY_MAP* pEntry = new XML_ENTRY_MAP(_T(#name), id, NODE_TEXT);\
pList->push_back(pEntry);\
list<XML_ENTRY_MAP*>* pList = &pEntry->listXMLMapEntries_p;
		
// NODE_CDATA_SECTION

#define XML_CDATA_ENTRY(name, id)\
XML_ENTRY_MAP* pEntry = new XML_ENTRY_MAP(_T(#name), id, NODE_CDATA_SECTION);\
pList->push_back(pEntry);\
list<XML_ENTRY_MAP*>* pList = &pEntry->listXMLMapEntries_p;


// NODE_ENTITY_REFERENCE
#define __NODE_ENTITY_REFERENCE_ATTRIB	ULONG_MAX - 1


#define XML_ENTITY_ENTRY(name)\
XML_ENTRY_MAP* pEntry = new XML_ENTRY_MAP(_T(#name), 0xFFFFFFFF, NODE_ENTITY_REFERENCE);\
pList->push_back(pEntry);\
list<XML_ENTRY_MAP*>* pList = &pEntry->listXMLMapEntries_p;


#define XML_ENTITY_ATTRIB_ENTRY(name, id)\
	XML_ENTRY_MAP* pEntry = new XML_ENTRY_MAP(_T(#name), id, (MSXML::DOMNodeType)__NODE_ENTITY_REFERENCE_ATTRIB);\
pList->push_back(pEntry);\
list<XML_ENTRY_MAP*>* pList = &pEntry->listXMLMapEntries_p;


// Attribute entry

#define XML_ATTRIBUTE_ENTRY(name, id)\
XML_ENTRY_MAP* pEntry = new XML_ENTRY_MAP(_T(#name), id, NODE_ATTRIBUTE);\
pList->push_back(pEntry);\
list<XML_ENTRY_MAP*>* pList = &pEntry->listXMLMapEntries_p;
		

// Comment entry

#define XML_COMMENT_ENTRY(name, id)\
XML_ENTRY_MAP* pEntry = new XML_ENTRY_MAP(_T(#name), id, NODE_COMMENT);\
pList->push_back(pEntry);\
list<XML_ENTRY_MAP*>* pList = &pEntry->listXMLMapEntries_p;
		
// Process entry
 
#define XML_PROCESS_ENTRY(name, id)\
XML_ENTRY_MAP* pEntry = new XML_ENTRY_MAP(_T(#name), id, NODE_PROCESSING_INSTRUCTION);\
pList->push_back(pEntry);\
list<XML_ENTRY_MAP*>* pList = &pEntry->listXMLMapEntries_p;
		

// Entry macros with Namespace specification

// ROOT Entry

#define XML_ROOT_ENTRY_NS(name, id, ns)\
m_pXMLMap = new XML_ENTRY_MAP(_T(#name), id, NODE_ELEMENT, ns);\
list<XML_ENTRY_MAP*>* pList = &m_pXMLMap->listXMLMapEntries_p;

// Element entry

#define XML_ELEMENT_ENTRY_NS(name, id, ns)\
XML_ENTRY_MAP* pEntry = new XML_ENTRY_MAP(_T(#name), id, NODE_ELEMENT, ns);\
pList->push_back(pEntry);\
list<XML_ENTRY_MAP*>* pList = &pEntry->listXMLMapEntries_p;
		

// Text entry

#define XML_TEXT_ENTRY_NS(name, id, ns)\
XML_ENTRY_MAP* pEntry = new XML_ENTRY_MAP(_T(#name), id, NODE_TEXT, ns);\
pList->push_back(pEntry);\
list<XML_ENTRY_MAP*>* pList = &pEntry->listXMLMapEntries_p;

//
// GridMFC extension DLL
// reset declaration context
//

}; // namespace rw

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

		
#endif //__SEC_XML_DEF_H__
