///////////////////////////////////////////////////////////////////////////////
// secxmlcore.h
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

#ifndef __SEC_XML_CORE_DEF_H___
#define __SEC_XML_CORE_DEF_H___

//
// GridMFC extension DLL
// reset declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

#pragma warning(disable: 4786)

// [VC7] Suppress Platform SDK warning for VC7 since it is integrated

#if (_MFC_VER < 0x0700)
#pragma message("Information: You need to have the latest version of the Platform SDK installed")
#pragma message("to compile this file. If there is a problem please check if you have this SDK installed.")

#if _WIN32_IE < 0x0500
#pragma message("Warning: It appears that the Platform SDK in not available or is outdated. Errors may result.")
#endif //_WIN32_IE < 0x0500
#endif

// includes

#include <list>
#include <map>
#include <stack>
#include <string>

#ifndef _UNICODE
typedef std::string secxmlstring;
#else
typedef std::wstring secxmlstring;
#endif

//@doc
//@type secxmlstring | A typedef which resolves to string or wstring depending on whether
//UNICODE is enabled or not.

#ifdef NTDDI_VERSION
	//---------------------------------------------------------------
	// NOTE: msxml.h is no longer used on the Windows Vista platform. 
	// Use msxml6.h instead. 
	// 
	// To use MSXML6, make sure that NTDDI_VERSION is defined as 
	// NTDDI_VISTA on Windows Vista platforms and that the MSXML6 SDK 
	// is installed and pathed correctly. 
	//---------------------------------------------------------------
	#if NTDDI_VERSION >= NTDDI_VISTA
		#include <msxml6.h>
		#import "msxml6.dll" exclude("tagDOMNodeType", "DOMNodeType")
	#else
		#include <msxml.h>
		#import "msxml.dll" exclude("tagDOMNodeType", "DOMNodeType")
		using namespace MSXML;
	#endif
#else
	#include <msxml.h>
	#import "msxml.dll" exclude("tagDOMNodeType", "DOMNodeType")
	using namespace MSXML;
#endif

#include <afxdisp.h> // for COleDateTime
#include "secxmldef.h"
// #include <StingrayExportDefs.h>

//@doc
//@topic Objective Grid XML support |
// Microsoft provides an XML parser with IE 5.0 (and will provide one as part of the
// operating system with Windows 2000). We can use this parser to parse an XML
// file. The Stingray XML implementation makes this easier by providing a wrapper library over the XML
// DOM. We also provide a tool that can generate most of the required source code from a
// valid schema file.
//
// Please refer to the Objective Grid user's guide for details on the usage of this library. There are two samples
// xml_samp and xml_grid that are provided under the samples folder of the Objective Grid installation.
//
// This version includes XML support in the context of Objective Grid. But there is complete support
// for using this library to write XML files outside of Objective Grid. The xml_samp sample shows  how to use
// this library outside the context of Objective Grid.
//

namespace rw
{

// structure definitions
// class XML_ENTRY_MAP declaration
// adinsert AutoDuck insertion point for
//@doc XML_ENTRY_MAP
//@class
// XML_ENTRY_MAP
// This structure forms the basis for the representation of an
// XML schema in a format that we can readily process. It basically
// has information that ties the name of a node to a unique ID. It also
// contains the node type (for more information on node types, please
// refer to DOMNodeType in the MSDN documentation.
// Each of these structures has a member list that can hold children
// under this node thus providing for the representation of complete
// XML trees
//@comm You will normally never have to manually initialize this structure
// since this is usually done using macros.
class XML_ENTRY_MAP
{
public:
	typedef std::list<XML_ENTRY_MAP*> CXMLList;

//@access constructor/destructor
	//@cmember
	/* Constructor */
	GRID_API XML_ENTRY_MAP(LPCTSTR _pszName,
		ENTRYID _dwID,
		DOMNodeType _entryType
	);

	//@cmember
	/* Constructor with namespace specification. */
	GRID_API XML_ENTRY_MAP(LPCTSTR _pszName,
		ENTRYID _dwID,
		DOMNodeType _entryType,
		LPCTSTR _pszNamespace
	);

	//@cmember
	/* Destructor */
	GRID_API virtual ~XML_ENTRY_MAP();

// data
//@access public
	//@cmember
	/*The name of the node.*/
	LPCTSTR pszName;

	//@cmember
	/*Unique id assigned to this node. When an element appears in more than one part of a document, each occurence should usually have a different relative id.*/
	ENTRYID dwID;

	//@cmember
	/*The type of the node. Please refer to DOMNode type in the MSDN documentation.*/
	DOMNodeType entryType;

	//@cmember
	/*Qualifying namespace if any.*/
	LPCTSTR pszNameSpace;

	//@cmember
	/*List that holds nested nodes.*/
	CXMLList listXMLMapEntries_p;
};

//@doc XML_ENTRY_MAP
//@mdata LPCTSTR  | XML_ENTRY_MAP | pszName | The name of the node that this structure defines.

//@mdata ENTRYID  | XML_ENTRY_MAP | dwID | The unique ID for this node. Note that is there are elements
// that appear in more than one part of the tree they should normally have different IDs. For example if the
// element price occurs under both a book item and a CD item, then the id for the price under the CD item should
// logically be different from the one under the book item. This is however not required.

//@mdata DOMNodeType  | XML_ENTRY_MAP | entryType | The node type. Please refer to MSDN documentation on DOMNodeType
// for more information on this.

//@mdata LPCTSTR  | XML_ENTRY_MAP | pszNameSpace | The namespace qualifier if present.

//@mdata CXMLList  | XML_ENTRY_MAP | listXMLMapEntries_p | List that contains the nodes that are children of this
// node. This list is simply a typedef as shown below
// typedef list<lt>XML_ENTRY_MAP*<gt> CXMLList;

// class XMLVALUE declaration
//@doc XMLVALUE
//@doc XMLVALUE
//@class
/*
XMLVALUE is a helper class that can take common arguments and convert these into a string.
*/
class XMLVALUE
{
public:
// constants used for initialization
	const DWORD ____dwDefSize;
	const int ____nRadix;

//@access construction / destruction
	//@cmember
	/* Default constructor. */
	GRID_API XMLVALUE();
	//@cmember
	/* Construct object from string data. */
	GRID_API XMLVALUE(LPCTSTR psz);
	//@cmember
	/* Construct object from integer data. */
	GRID_API XMLVALUE(int n);
	//@cmember
	/* Construct object from WORD. */
	GRID_API XMLVALUE(WORD w);
	//@cmember
	/* Construct object from long. */
	GRID_API XMLVALUE(long l);
	//@cmember
	/* Construct object from DWORD. */
	GRID_API XMLVALUE(DWORD dw);
	//@cmember
	/* Construct object from COleDateTime object. */
	GRID_API XMLVALUE(const COleDateTime& dt);

	// destruction
	//@cmember
	/* Destructor. */
	GRID_API virtual ~XMLVALUE();

//@access attributes
	//@cmember
	/* Return the value of the object.*/
	GRID_API LPCTSTR GetValue() const;
	//@cmember
	/* Set the value of the object. */
	GRID_API void SetValue(LPCTSTR lpsz);

	//@cmember
	/* Returns the radix that is used internally for data conversion. */
	GRID_API int GetRadix() const;
	//@cmember
	/* Sets the radix that is used internally for data conversion. */
	GRID_API void SetRadix(int nRadix);

	//@cmember
	/* Returns the size of the default buffer that will be allocated internally when needed for data conversion.*/
	GRID_API DWORD GetDefAllocSize() const;
	//@cmember
	/* Sets the size of the default buffer that will be allocated internally when needed for data conversion. */
	GRID_API void SetDefAllocSize(DWORD dwDefSize);

//@access operations
	//@cmember
	/* Attaches the string to the object. */
	GRID_API void Attach(LPTSTR psz);
	//@cmember
	/* Detach the current string value. */
	GRID_API LPTSTR Detach();
	//@cmember
	/* Call to reuse this instance */
	GRID_API void Recycle();

//@access operators
	// const operators
	//@cmember
	/* Returns const string data.*/
	GRID_API operator LPCTSTR() const;
	//@cmember
	/* Enables easy check for validity. */
	GRID_API operator bool() const;
	//@cmember
	/* Enables easy check for validity. */
	GRID_API bool operator !() const;

	// non-const operators
	//@cmember
	/* Assigns string to object. */
	GRID_API XMLVALUE& operator = (LPCTSTR psz);
	//@cmember
	/* Assigns integer to object. */
	GRID_API XMLVALUE& operator = (int n);
	//@cmember
	/* Assigns WORD to object. */
	GRID_API XMLVALUE& operator = (WORD w);
	//@cmember
	/* Assigns DWORD to object. */
	GRID_API XMLVALUE& operator = (DWORD dw);
	//@cmember
	/* Assigns long to object. */
	GRID_API XMLVALUE& operator = (long n);
	//@cmember
	/* Assigns a COleDateTime object to this object.*/
	GRID_API XMLVALUE& operator = (const COleDateTime& dt);

protected:
	// whethere we should free this memory
	bool bFree;

	// the actual character data
	LPTSTR pszValue;

	// the allocation size to use in case we do the allocation
	// default is set to 50 characters
	DWORD m_dwAllocSize;

	// the radix to use for converting numbers to strings
	int m_nRadix;

	// call to cleanup internal data
	GRID_API void Cleanup();

	// call to initialize internal state to defaults
	// This function does not change the values of m_dwAllocSize and m_nRadix be default
	// use initall = true to do this
	GRID_API void InitValues(bool bInitall = false);
};

// struct IXMLRResolver
// Feedback interface used when reading

//@doc IXMLRResolver
//@class
/*
	The IXMLRResolver interface is the primary interface that is used by the XML read/write code that processes
	<c XML_ENTRY_MAP> structures when reading XML data streams. One term that bears mention here is
	the use of the word, loop. In this context the loop refers to repetitive calls to the same unique
	node position as a result of data streams that have mutiple instances of elements. The <mf IXMLRResolver::OnStartReadLoop>
	callback gives an opportunity for the hosting code to initialize any data structures that need to be
	in place for the rest of the read operation to be successful.

	You do not normally have to implement these functions. They are implemented as part of the BEGIN_WRITE_MAP macro. This and other
	related macros define an implementation of this class and map these callback functions to a single function prototype. This function
	will get called with different context (defined by the enum <t eTypeRWContext>.

	The prototype of the function to which these calls get mapped looks like this.

	void Handler(XML_ENTRY_PARAM& pParam, eTypeRWContext context, bool& bRetval, XMLVALUE& pValue);
*/
// @xref <c IXMLWResolver> <t eTypeRWContext>  <c IXMLRWResolver>
class IXMLRResolver
{
public:
//@access constructor/destructor
	//@cmember
	/* Default constructor */
	GRID_API IXMLRResolver();
	//@cmember
	/* Destructor */
	GRID_API virtual ~IXMLRResolver();

// read feedback interface

	//@cmember
	/* Will be called when the system starts to read data from the XML data stream.*/
	GRID_API virtual void OnStartRead() = 0;

	//@cmember
	/* Will be called when the system completes reading from the stream*/
	GRID_API virtual void OnCompleteRead() = 0;

	//@cmember
	/* Will be called when read is started for a particular node type. */
	GRID_API virtual bool OnStartReadLoop(const XML_ENTRY_MAP* pEntry) = 0;

	//@cmember
	/* Will be called to give the value of a node (as the nodes are read out) */
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		GRID_API virtual bool OnSetValue(const XML_ENTRY_MAP* pEntry, ::IXMLDOMNode* pThisNode, XMLVALUE& xmlValue) = 0;
	#else
		GRID_API virtual bool OnSetValue(const XML_ENTRY_MAP* pEntry, MSXML::IXMLDOMNode* pThisNode, XMLVALUE& xmlValue) = 0;
	#endif
#else
	GRID_API virtual bool OnSetValue(const XML_ENTRY_MAP* pEntry, MSXML::IXMLDOMNode* pThisNode, XMLVALUE& xmlValue) = 0;
#endif
};

// struct IXMLWResolver
// Feedback interface used when writing
//@doc IXMLWResolver
//@class
/*
	The IXMLWResolver interface is the primary interface that is used by the XML read/write code that processes
	<c XML_ENTRY_MAP> structures when writing XML data streams. One term that bears mention here is
	the use of the word, loop. In this context the loop refers to repetitive calls to the same unique
	node position as a result of data streams that have mutiple instances of elements. The <mf IXMLWResolver::OnStartWriteLoop>
	callback gives an opportunity for the hosting code to initialize any data structures that need to be
	in place for the rest of the write operation to be successful. <mf IXMLWResolver::OnCanContinueWriteLoop> allows the
	hosting code to decide the number of iterations for which data will be supplied for this unique node. <mf IXMLWResolver::OnEndWriteLoop>
	is called to allow the hosting code to cleanup if required.

	You do not normally have to implement these functions. They are implemented as part of the BEGIN_WRITE_MAP macro. This and other
	related macros define an implementation of this class and map these callback functions to a single function prototype. This function
	will get called with different context (defined by the enum <t eTypeRWContext>).

	The prototype of the function to which these calls get mapped looks like this.

	void Handler(XML_ENTRY_PARAM& pParam, eTypeRWContext context, bool& bRetval, XMLVALUE& pValue);
*/
// @xref<c IXMLRResolver>
// @xref<t eTypeRWContext>
// @xref<c IXMLRWResolver>
// @xref<I xml write map macros>
class IXMLWResolver
{
public:
//@access Constructor/Destructor
	//@cmember
	/* Constructor*/
	GRID_API IXMLWResolver();
	//@cmember
	/* Destructor*/
	GRID_API virtual ~IXMLWResolver();

// write feedback interface
//@access public
	//@cmember
	/* Will be called when write is started */
	GRID_API virtual void OnStartWrite() = 0;

	//@cmember
	/* Will be called when write is completed */
	GRID_API virtual void OnCompleteWrite() = 0;

	//@cmember
	/* Will be called when a value needs to be supplied (just before the write operation for a node takes place) */
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		GRID_API virtual bool OnGetValue(const XML_ENTRY_MAP* pEntry, ::IXMLDOMNode* pParentNode, XMLVALUE& xmlValue) = 0;
	#else
		GRID_API virtual bool OnGetValue(const XML_ENTRY_MAP* pEntry, MSXML::IXMLDOMNode* pParentNode, XMLVALUE& xmlValue) = 0;
	#endif
#else
	GRID_API virtual bool OnGetValue(const XML_ENTRY_MAP* pEntry, MSXML::IXMLDOMNode* pParentNode, XMLVALUE& xmlValue) = 0;
#endif

	//@cmember
	/* Will be called when a node is to be written out for the first time. */

	GRID_API virtual bool OnStartWriteLoop(const XML_ENTRY_MAP* pEntry) = 0;

	//@cmember
	/* Will be called when to check whether write needs to be continued on a node type*/
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		GRID_API virtual bool OnCanContinueWriteLoop(const XML_ENTRY_MAP* pEntry, ::IXMLDOMNode* pNodeAdded) = 0;
	#else
		GRID_API virtual bool OnCanContinueWriteLoop(const XML_ENTRY_MAP* pEntry, MSXML::IXMLDOMNode* pNodeAdded) = 0;
	#endif
#else
	GRID_API virtual bool OnCanContinueWriteLoop(const XML_ENTRY_MAP* pEntry, MSXML::IXMLDOMNode* pNodeAdded) = 0;
#endif

	//@cmember
	/* Will be called when writing is stopped for a particular node type */
	GRID_API virtual bool OnEndWriteLoop(const XML_ENTRY_MAP* pEntry) = 0;
};

// struct IXMLRWResolver declaration
//
//@doc IXMLRWResolver
//@class
/*
	The default combination of both the read and write feedback interfaces, IXMLRWResolver derives from
	<c IXMLWResolver> and <c IXMLRResolver>. Please refer to these classes for more information. This class
	does not add any additional definitions.
*/
// @base	public | <c IXMLRResolver>
// @base	public | <c IXMLWResolver>
// @xref <c IXMLRResolver> <c IXMLWResolver> <t eTypeRWContext>

// Exported through base class. 
class IXMLRWResolver : public IXMLRResolver, public IXMLWResolver
{
public:
// construction
	GRID_API IXMLRWResolver();
	GRID_API virtual ~IXMLRWResolver();

// overrides

	// just provides a default implementation for this call
	GRID_API virtual bool OnEndWriteLoop(const XML_ENTRY_MAP* pEntry);
};


// class IXMLBase declaration

/////////////////////////////
//@doc IXMLBase
//@class
/*
	IXMLBase is a standard interface that aggregates and ties together the resolver (the feedback interfaces;
	refer <c IXMLRWResolver>, <c IXMLRResolver> and <c IXMLWResolver>) and the <c XML_ENTRY_MAP> data structure.
	This interface can be used by a processing system to write out or read in the XML defines in the <c XML_ENTRY_MAP>
	data structure using the feedback interfaces for data collection or population as the case may be. IXMLBase
	is used as the foundational interface for systems that read and write XML data. There are specializations of
	this interface for read (<c IXMLRead>) and write (<c IXMLWrite>). Please refer to these for additional information.
*/
// @xref <c IXMLRead> <c IXMLWrite>
class GRID_API IXMLBase
{
public:
// attributes
	virtual void SetXMLMap(XML_ENTRY_MAP* pMap) = 0;
	virtual const XML_ENTRY_MAP* GetXMLMap() const = 0;

	virtual void SetResolver(IXMLRWResolver* pResolver) = 0;
	virtual IXMLRWResolver* GetResolver() const = 0;

	virtual eTypeSeen IsFirstLoop(DWORD dwID) const = 0;
	virtual void MarkAsSeen(DWORD dwID, eTypeSeen seen) = 0;
};

// class IXMLWrite declaration

//@doc IXMLWrite
//@class
/*
	IXMLWrite is derived from <c IXMLBase>. In the current implementation this interface adds no functionality
	to the base interface. No other methods are required to be implemented in order to support a write operation.
*/
// @base public | <c IXMLBase>
// @xref <c IXMLBase> <c IXMLRead>
class GRID_API IXMLWrite : public IXMLBase
{
	// no additional implementation required
};

// class IXMLRead declaration
//@doc IXMLRead
//@class
/*
	IXMLRead is derived from <c IXMLBase>. It adds one function that needs to be implemented to support read
	operations, <mf IXMLRead::LocateEntry>. During the read process the read system will compose a string that
	identifies the location of the node in the document. With this string the implementation of IXMLRead has to
	locate the <c XML_ENTRY_MAP> entry that corresponds to the node. This enables the read sytem to call the correct
	feedback interfaces for the node.
*/
//@base public | <c IXMLBase>
// @xref <c IXMLBase> <c IXMLWrite>
class GRID_API IXMLRead : public IXMLBase
{
public:
	virtual const XML_ENTRY_MAP* LocateEntry(secxmlstring& pszMonikerData) const = 0;
};


// the base XML map helper

// @type CMapSlots | Used internally to hold string data, <c XML_ENTRY_MAP>
// relationship. This can change in a future release.
typedef std::map<secxmlstring, const XML_ENTRY_MAP*> CMapSlots;
// @type CMapInit | Used internally to remember the initialization of the XML read/write system with
// respect to various nodes. This can change in a future implementation.
typedef std::map<DWORD, eTypeSeen> CMapInit;


/////////////////////////////
//@doc CXMLBaseHelper
//@class
/*
	CXMLBaseHelper derives from <c IXMLRead> and <c IXMLWrite> and provides a default implementation
	of these interfaces by aggregating <c XML_ENTRY_MAP> and <c IXMLRWResolver>. It adds a few functions
	for easy initialization of data.
*/
// @xref <c IXMLWrite> <c IXMLRead> <c XML_ENTRY_MAP> <c IXMLRWResolver>
// @base public | <c IXMLRead>
// @base public | <c IXMLWrite>

// Exported through base class. 
class CXMLBaseHelper : public IXMLWrite, public IXMLRead
{
public:
//@access Construction
	//@cmember
	/* Default constructor for CXMLBaseHelper.*/
	GRID_API CXMLBaseHelper();
	//@cmember
	/* Destructor.*/
	GRID_API virtual ~CXMLBaseHelper();


//access Operations
	//@cmember
	/* Call initialize before performing any other operations on this object. Initialize will
	populate the <c XML_ENTRY_MAP> structure based on macro entries. */
	GRID_API virtual void Initialize() = 0;

	//@cmember
	/* Call this function to clean up the <c XML_ENTRY_MAP> map*/
	GRID_API virtual void Cleanup();

	// for read
	//@cmember
	/* In addition to calling Initialize, this function has to be called to use this class for a read operation.*/
	GRID_API virtual bool InitializeForRead();

// attributes
	//@cmember
	/* Returns true if this instance is initialized for a read operation. */
	GRID_API bool IsInitForRead();

// implementation of IXMLWrite / IXMLRead

	GRID_API virtual void SetXMLMap(XML_ENTRY_MAP* pMap);
	GRID_API virtual const XML_ENTRY_MAP* GetXMLMap() const;
	GRID_API virtual void SetResolver(IXMLRWResolver* pResolver);
	GRID_API virtual IXMLRWResolver* GetResolver() const;
	GRID_API virtual eTypeSeen IsFirstLoop(DWORD dwID) const;
	GRID_API virtual void MarkAsSeen(DWORD dwID, eTypeSeen seen);
	GRID_API virtual const XML_ENTRY_MAP* LocateEntry(secxmlstring& pszMonikerData) const;


// implementation
protected:
	XML_ENTRY_MAP*	m_pXMLMap;
	IXMLRWResolver* m_pResolver;
	// for read support
	CMapSlots		m_slotMap;
	CMapInit		m_initMap;
	bool			m_bInitForRead;
};

// class CXMLIO declaration
//@doc CXMLIO
//@class
/*
	This class ties an actual read/write processing system to the <c XML_ENTRY_MAP> and
	<c IXMLRWResolver> structures. Implementation of CXMLIO can provide implementations of
	that allow the reading and writing of XML files to physical files, virtual streams etc.
*/
// @xref <c CXMLFileIO>
class CXMLIO
{

public:
//@access Construction
	//@cmember
	/*Default constructor.*/
	GRID_API CXMLIO();
	//@cmember
	/*Destructor*/
	GRID_API virtual ~CXMLIO();

//@access Attributes
	//@cmember
	/*Sets the <c IXMLWrite> interface that this class will work with.*/
	GRID_API void SetXMLWrite(IXMLWrite* pXMLWrite);
	//@cmember
	/*Returns the <c IXMLWrite> interface that this class will work with.*/
	GRID_API IXMLWrite* GetXMLWrite() const;

	//@cmember
	/*Sets the <c IXMLRead> interface that this class will work with.*/
	GRID_API void SetXMLRead(IXMLRead* pXMLRead);
	//@cmember
	/*Returns the <c IXMLRead> interface that this class will work with.*/
	GRID_API IXMLRead* GetXMLRead() const;

//@access Operations
	//@cmember
	/*Call to perform a write operation based on the <c XML_ENTRY_MAP> and the provided resolver <c IXMLRWResolver>*/
	GRID_API virtual bool Write();
	//@cmember
	/*Call to perform a read operation based on the <c XML_ENTRY_MAP> and the provided resolver <c IXMLRWResolver>*/
	GRID_API virtual bool Read();

//@access Overrideables
	//@cmember
	/* Override this funtion and return a IXMLDOMDocument.*/
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		GRID_API virtual ::IXMLDOMDocument* OnGetDocument();
	#else
		GRID_API virtual MSXML::IXMLDOMDocument* OnGetDocument();
	#endif
#else
	GRID_API virtual MSXML::IXMLDOMDocument* OnGetDocument();
#endif


#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		//@cmember
		/* Called before the write operation starts.*/
		virtual bool OnStartWrite(::IXMLDOMDocument* pDoc) = 0;
		//@cmember
		/* Called before the write operation ends. */
		virtual bool OnCompleteWrite(::IXMLDOMDocument* pDoc) = 0;

		//@cmember
		/*Called before the read operation starts.*/
		virtual bool OnStartRead(::IXMLDOMDocument* pDoc) = 0;
		//@cmember
		/*Called before the read operation ends.*/
		virtual bool OnCompleteRead(::IXMLDOMDocument* pDoc) = 0;
	#else
		//@cmember
		/* Called before the write operation starts.*/
		virtual bool OnStartWrite(MSXML::IXMLDOMDocument* pDoc) = 0;
		//@cmember
		/* Called before the write operation ends. */
		virtual bool OnCompleteWrite(MSXML::IXMLDOMDocument* pDoc) = 0;

		//@cmember
		/*Called before the read operation starts.*/
		virtual bool OnStartRead(MSXML::IXMLDOMDocument* pDoc) = 0;
		//@cmember
		/*Called before the read operation ends.*/
		virtual bool OnCompleteRead(MSXML::IXMLDOMDocument* pDoc) = 0;
	#endif
#else
	//@cmember
	/* Called before the write operation starts.*/
	virtual bool OnStartWrite(MSXML::IXMLDOMDocument* pDoc) = 0;
	//@cmember
	/* Called before the write operation ends. */
	virtual bool OnCompleteWrite(MSXML::IXMLDOMDocument* pDoc) = 0;

	//@cmember
	/*Called before the read operation starts.*/
	virtual bool OnStartRead(MSXML::IXMLDOMDocument* pDoc) = 0;
	//@cmember
	/*Called before the read operation ends.*/
	virtual bool OnCompleteRead(MSXML::IXMLDOMDocument* pDoc) = 0;
#endif

//@access Implementation
protected:
	IXMLWrite*	m_pIXMLWrite;
	IXMLRead*	m_pIXMLRead;
};


// Writes the XML document to a file
//@doc CXMLFileIO
//@class
/*
	This class subclasses <c CXMLIO> and allows the reading and writing of an
	XML document to a file.
*/
//@xref <c CXMLIO>
//@base public | <c CXMLIO>

// Exported through base class. 
class CXMLFileIO : public CXMLIO
{
public:
// construction
	GRID_API CXMLFileIO();
	GRID_API virtual ~CXMLFileIO();

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		// Overrides
		GRID_API virtual bool OnStartWrite(::IXMLDOMDocument* pDoc);
		GRID_API virtual bool OnCompleteWrite(::IXMLDOMDocument* pDoc);

		GRID_API virtual bool OnStartRead(::IXMLDOMDocument* pDoc);
		GRID_API virtual bool OnCompleteRead(::IXMLDOMDocument* pDoc);
	#else
		// Overrides
		GRID_API virtual bool OnStartWrite(MSXML::IXMLDOMDocument* pDoc);
		GRID_API virtual bool OnCompleteWrite(MSXML::IXMLDOMDocument* pDoc);

		GRID_API virtual bool OnStartRead(MSXML::IXMLDOMDocument* pDoc);
		GRID_API virtual bool OnCompleteRead(MSXML::IXMLDOMDocument* pDoc);
	#endif
#else
	// Overrides
	GRID_API virtual bool OnStartWrite(MSXML::IXMLDOMDocument* pDoc);
	GRID_API virtual bool OnCompleteWrite(MSXML::IXMLDOMDocument* pDoc);

	GRID_API virtual bool OnStartRead(MSXML::IXMLDOMDocument* pDoc);
	GRID_API virtual bool OnCompleteRead(MSXML::IXMLDOMDocument* pDoc);
#endif


//@access Attributes
	//@cmember
	/* Returns the file name that will be used for the read/write operation*/
	GRID_API const secxmlstring& GetFileName() const;
	//@cmember
	/* Returns a reference to the file name that will be used for the read/write operation */
	GRID_API secxmlstring& GetFileNameRef();

	//@cmember
	/* Sets the filename to be used for the read/write operation */
	GRID_API void SetFileName(LPCTSTR pszFileName);

// implementation
protected:
	secxmlstring m_strFileName;
};

// helpers for typesafety

template<typename T>
inline void __deleteop(T* p)
{
	delete p;
};

template<typename T>
inline void __deleteop_ar(T* p)
{
	delete[] p;
};


typedef void (*pfnDel)(void* p);

// struct __DELSTRUCT declaration

struct __DELSTRUCT
{
	void* p;
	pfnDel pfn;
};

// class CEntryValueHolder declaration

//@doc CEntryValueHolder
//@class
/*
	Helper class that is usually to be used with resolvers. Offers a convenient way to store context specific
	information. You should one of the listed macros to set and get values from this class.
*/
// @xref <f SetEntryValue> <f SetEntryValueAr> <f SetEntryValue_NoManage>
class CEntryValueHolder
{
public:
	typedef std::map<DWORD, void*> CEntryValueMap;
	typedef std::list<__DELSTRUCT> CDelList;

// construction
	GRID_API CEntryValueHolder();
	GRID_API virtual ~CEntryValueHolder();

// attributes
	template<typename T>
	inline const T* GetEntryValue(DWORD dwKey, T*& p) const
	{
		return __GetEntryValueRef(dwKey, p);
	}

	template<typename T>
	inline T* GetEntryValueRef(DWORD dwKey, T*& p)
	{
		return __GetEntryValueRef(dwKey, p);
	}

	// Do not use this function directly.
	// use the macros SetEntryValue and SetEntryValue_NoManage to access this member
	template<typename T>
	inline void _SetEntryValue(DWORD dwKey, T* p, bool bManage = true, bool bSimp = true)
	{
		m_mpEntryValues[dwKey] = p;
		if(bManage)
		{
			typedef void (*pfnDel_type)(T* p);

			pfnDel_type deltype = NULL;

			if(bSimp == true)
				deltype = &__deleteop;
			else
				deltype = &__deleteop_ar;

			pfnDel del;
			del = reinterpret_cast<pfnDel>(deltype);

			ManageMemory(p, del);
		}
	}

//operations
	GRID_API void Cleanup();

// implementation
protected:
// attribute

	// stores the values
	CEntryValueMap m_mpEntryValues;

	// stores the values that need to be deleted
	CDelList m_lstDel;

	// memory management
	GRID_API void ManageMemory(void* p, pfnDel pfn);

	// attribute access
	template<typename T>
	inline T* __GetEntryValueRef(DWORD dwKey, T*& p) const
	{
		CEntryValueMap::const_iterator it = m_mpEntryValues.find(dwKey);
		if(it == m_mpEntryValues.end())
			return NULL;

		void* pVoid = (*it).second;

		if(pVoid != NULL)
		{
			p = static_cast<T*>(pVoid);
			return p;
		}
		else
			return NULL;
	}

};

// some helper classes that you can derive from and use

template<class T>
class CGridRefResolver
{
public:
	inline void GridRefHandler(XML_ENTRY_PARAM& pParam, eTypeRWContext context, bool& bRetval, XMLVALUE& value)
	{
		if(context == eWriteGetValue)
		{
			DWORD dw = pParam.dwContext;

			T* p = static_cast<T*>(this);

			ASSERT(p->m_pCoreData);

			value = p->m_pCoreData->GetExpressionRowCol(LOWORD(dw), HIWORD(dw));
		}
		else if(context == eReadSetValue)
		{
			DWORD dw = pParam.dwContext;

			T* p = static_cast<T*>(this);

			ASSERT(p->m_pCoreData);

			p->m_pCoreData->SetExpressionRowCol(LOWORD(dw), HIWORD(dw), (LPCTSTR)value);
		}
	}
};

//@doc CEmptyResolver
//@class CEmptyResolver
/*
// To use the entry that is implemented by this class derive from this class.
// With this entry as the handler, entries will always be written. If you have a value that is always
// empty but needs to appear in the XML document use this handler. You can specify this handler as the
// default handler thus allowing all entries that are not explicitly handled to have an entry (empty).

*/
//@tcarg class | T | The class that derives from CEmptyResolver.
template<class T>
class CEmptyResolver
{
//@access public
public:
	//@cmember
	/* Handler for generating empty entries*/
	inline void EmptyHandler(XML_ENTRY_PARAM& pParam, eTypeRWContext context, bool& bRetval, XMLVALUE& value)
	{
		if(context == eWriteGetValue)
		{
			value = _T("");
			bRetval = true;
		}
	}
};

//@doc CNoEntryResolver
//@class
/*
To use the entry that is implemented by this class derive from this class.
With this entry as the handler, entries will never be written. If you have a value that is always
empty and does not need to appear in the XML document use this handler. You can specify this handler
as the default handler thus preventing all entries that are not explicitly handled from having an entry.
*/
//@tcarg class | T | The class that derives from CNoEntryResolver.
template<class T>
class CNoEntryResolver
{
//@access public
public:

	//@cmember
	/* Handler for ensuring empty entries are not generated.*/
	inline void NoEntryHandler(XML_ENTRY_PARAM& pParam, eTypeRWContext context, bool& bRetval, XMLVALUE& value)
	{
		if(context == eWriteGetValue)
			bRetval = false;
	}
};


//@doc CMonikerResolver
//@class
/*
	To use the entry that is implemented by this class derive from this class.
	With this entry you can have the void pointer data attached to a node stored as the value. You can use this
	to generate an XML file that has a fairly simple static layout
*/
//@tcarg class | T | The class that derives from CMonikerResolver.
template<class T>
class CMonikerResolver
{
//@access public
public:
	//@cmember
	/* Handler for treating the void* that is a part of <c XML_ENTRY_PARAM> as string data.*/
	inline void MonHandler(XML_ENTRY_PARAM& pParam, eTypeRWContext context, bool& bRetval, XMLVALUE& value)
	{
		if(context == eWriteGetValue)
		{
			bRetval = true;
			value = (TCHAR*) pVoidInfo;
		}
	}
};

}; // namespace rw

//
// GridMFC extension DLL
// reset declaration context
//


#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //__SEC_XML_CORE_DEF_H___
