///////////////////////////////////////////////////////////////////////////////
// browseh.h
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
//          Supplement Section 227.7202, Government�s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __AH_BROWSE_H_
#define __AH_BROWSE_H_

#include <StingrayExportDefs.h>

#ifdef WIN32

#ifdef UNICODE
    #define FROM_OLE_STRING(str) str
    #define TO_OLE_STRING(str) str 
#else
    #define FROM_OLE_STRING(str) ConvertToAnsi(str)
    TOOLKIT_API char FAR* ConvertToAnsi(OLECHAR FAR* szW);  
    #define TO_OLE_STRING(str) ConvertToUnicode(str)
    TOOLKIT_API OLECHAR FAR* ConvertToUnicode(char FAR* szA);   
    // Maximum length of string that can be converted between Ansi & Unicode
    #define STRCONVERT_MAXLEN 300         
#endif

#else  // WIN16
  #define TCHAR char
  #define TEXT(sz) sz 
  #define FROM_OLE_STRING(str) str  
  #define TO_OLE_STRING(str) str  
  #define LPTSTR LPSTR
#endif
      
#include "toolkit\ActvHost\mydisp.h"
#include "toolkit\ActvHost\tlb.h"

//
// SEC Extension DLL
// Initialize declaration context
//
#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL

// MAX len of string table entries
#define STR_LEN   200

/////////////////////////////////////////////////////////
// OTPro lower resource range 21000 - 21499      
// IDD_, IDB_, IDI_, IDS_
// This block contains 21225-21240
//
// Note: ActiveScript resources start at 21200
//
/////////////////////////////////////////////////////////
// String table constants
#define IDS_SERVERNAME                      21225
// These exception strings IDs that is will used in EXCEPINFO.wCode   
#define IDS_Unexpected                      21226
#define IDS_OutOfMemory                     21227
#define IDS_InvalidIndex                    21228
#define IDS_CollectionFull                  21229
#define IDS_CannotFindTypeLibrary           21230
#define IDS_TypeLibraryCreationFailed       21231   
#define IDS_WrongType                       21232
#define IDS_InvalidProgid                   21233
#define IDS_CouldNotCreateObject            21234
#define IDS_ObjectDoesNotSupportAutomation  21235      
#define IDS_ObjectDoesNotProvideTypeInfo    21236

// Function prototypes
TOOLKIT_API BOOL InitDLL (HINSTANCE hInstance);
// NOTE: #define STDAPI     EXTERN_C HRESULT STDAPICALLTYPE [defined in Microsoft header, basetyps.h]
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID FAR *ppv);   
STDAPI DllCanUnloadNow(void);

// Forward declaration
class SECAArrayBound;
 
class FAR SECABrowseHelperCF : public IClassFactory
{
public:
    // IUnknown methods 
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)(void);
    STDMETHOD_(ULONG, Release)(void); 
    
    // IClassFactory methods
    STDMETHOD(CreateInstance)(IUnknown FAR* punkOuter, REFIID riid, void FAR* FAR* ppv);
    STDMETHOD(LockServer)(BOOL fLock);    
    
    TOOLKIT_API SECABrowseHelperCF();
    
private:
    ULONG m_cRef;                   // Reference count
}; 

    
class FAR SECABrowseHelper : public ISBrowseHelper
{
public:
    // ISBrowseHelper automation exposed methods
    STDMETHOD_(ISTypeLibrary FAR*, BrowseTypeLibrary)(BSTR bstrPath);     
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    TOOLKIT_API static HRESULT Create(SECABrowseHelper FAR* FAR* ppBrowseHelper); // Creates and intializes Applicaton object 
    TOOLKIT_API SECABrowseHelper();
    TOOLKIT_API ~SECABrowseHelper();
};

class FAR SECATypeLibrary : public ISTypeLibrary
{
public:
    // ISTypeLibrary automation exposed properties & methods 
    STDMETHOD_(BSTR, get_Name)();
    STDMETHOD_(BSTR, get_Documentation)();
    STDMETHOD_(long, get_HelpContext)();
    STDMETHOD_(BSTR, get_HelpFile)();
    STDMETHOD_(long, get_LocaleID)();
    STDMETHOD_(int, get_MajorVersion)();
    STDMETHOD_(int, get_MinorVersion)();
    STDMETHOD_(ISCollection FAR*, get_TypeInfos)();   
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    TOOLKIT_API static HRESULT Create(LPTYPELIB ptlib, SECATypeLibrary FAR* FAR* ppTypeLibrary); // Creates and intializes TypeLibrary object 
    TOOLKIT_API SECATypeLibrary();
    TOOLKIT_API ~SECATypeLibrary();
    
private:    
    BSTR m_bstrName;               // Type Library name
    BSTR m_bstrDocumentation;      // Documentation
    unsigned long m_ulHelpContext; // HelpContext
    BSTR m_bstrHelpFile;           // HelpFile
    GUID m_guid;                   // GUID
    LCID m_lcid;                   // Locale ID
    unsigned short m_wMajorVer;    // Major version
    unsigned short m_wMinorVer;    // Minor version
    LPTYPELIB m_ptlib;             // ITypeLib* of type library.
    LPDISPATCH m_pdispTypeInfos;   // Collection of typeinfos contained by this typelib
};

// SECATypeInfo is the base class for all the TypeInfos (SECAInterface, SECADispinterface,
// SECAModule, SECACoClass, SECAEnum, SECAStruct, SECAUnion, SECAAlias)
class FAR SECATypeInfo : public ISTypeInformation
{
public:
    // ITypeInfo automation exposed properties & methods 
    STDMETHOD_(BSTR, get_Name)();
    STDMETHOD_(BSTR, get_Documentation)();
    STDMETHOD_(long, get_HelpContext)();
    STDMETHOD_(BSTR, get_HelpFile)();
    STDMETHOD_(TYPEKIND, get_TypeInfoKind)();    
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();
    STDMETHOD(_InitTypeInfo)(LPTYPEINFO ptinfo); // Called by derived class to intialize this base class
    TOOLKIT_API static HRESULT Create(LPTYPEINFO ptinfo, SECATypeInfo FAR* FAR* ppTypeInfo); // Creates and intializes TypeInfo object 
    TOOLKIT_API SECATypeInfo();
    TOOLKIT_API ~SECATypeInfo();
    
public:    
    BSTR m_bstrName;               // TypeInfo name
private:
    BSTR m_bstrDocumentation;      // Documentation 
    unsigned long m_ulHelpContext; // Help context
    BSTR m_bstrHelpFile;           // Help file
    TYPEKIND m_typekind;           // Type of TypeInfo. See TYPEKIND enumeration.
    GUID m_guid;                   // GUID
};

class FAR SECAInterface : public SECATypeInfo       
{
public:
    // ISInterface automation exposed properties & methods 
    STDMETHOD_(ISCollection FAR*, get_Functions)();    
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    TOOLKIT_API static HRESULT Create(LPTYPEINFO ptinfo, SECAInterface FAR* FAR* ppInterface); // Creates and intializes Interface object 
    TOOLKIT_API SECAInterface();
    TOOLKIT_API ~SECAInterface();
    
private:
    LPTYPEINFO m_ptinfo;             // ITypeInfo* of interface typeinfo.
    LPDISPATCH m_pdispFunctions;     // Collection of functions in interface.
};

class FAR SECADispinterface : public SECATypeInfo
{
public:
    // ISDispinterface automation exposed properties & methods 
    STDMETHOD_(ISCollection FAR*, get_Properties)();
    STDMETHOD_(ISCollection FAR*, get_Methods)();      
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    TOOLKIT_API static HRESULT Create(LPTYPEINFO ptinfo, SECADispinterface FAR* FAR* ppDispinterface); // Creates and intializes Dispinterface object 
    TOOLKIT_API SECADispinterface();
    TOOLKIT_API ~SECADispinterface();
    
private:
    LPTYPEINFO m_ptinfo;              // ITypeInfo* of dispinterface typeinfo.
    LPDISPATCH m_pdispProperties;     // Collection of properties in dispinterface
    LPDISPATCH m_pdispMethods;        // Collection of methods in dispinterface
};  

class FAR SECAModule : public SECATypeInfo       
{
public:
    // ISModule automation exposed properties & methods 
    STDMETHOD_(ISCollection FAR*, get_Functions)();    
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();   
    TOOLKIT_API static HRESULT Create(LPTYPEINFO ptinfo, SECAModule FAR* FAR* ppInterface); // Creates and intializes Module object 
    TOOLKIT_API SECAModule();
    TOOLKIT_API ~SECAModule();
    
private:                             
    LPTYPEINFO m_ptinfo;              // ITypeInfo* of module typeinfo.
    LPDISPATCH m_pdispFunctions;      // Collection of functions in module
};

class FAR SECACoClass : public SECATypeInfo
{
public:   
    // ISCoClass automation exposed properties & methods 
    STDMETHOD_(ISCollection FAR*, get_Interfaces)();     
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    TOOLKIT_API static HRESULT Create(LPTYPEINFO ptinfo, SECACoClass FAR* FAR* ppCoClass); // Creates and intializes CoClass object     
    TOOLKIT_API SECACoClass();
    TOOLKIT_API ~SECACoClass();
    
private:
    LPTYPEINFO m_ptinfo;              // ITypeInfo* of coclass typeinfo.
    LPDISPATCH m_pdispInterfaces;     // Collection of interfaces/dispinterfaces in coclass
}; 

class FAR SECAEnum : public SECATypeInfo
{
public:
    // ISEnum automation exposed properties & methods
    STDMETHOD_(ISCollection FAR*, get_Elements)();    
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    TOOLKIT_API static HRESULT Create(LPTYPEINFO ptinfo, SECAEnum FAR* FAR* ppEnum); // Creates and intializes Enum object 
    TOOLKIT_API SECAEnum();
    TOOLKIT_API ~SECAEnum();
    
private:
    LPTYPEINFO m_ptinfo;             // ITypeInfo* of enum typeinfo.
    LPDISPATCH m_pdispElements;      // Collection of elements in enum.
};

class FAR SECAStruct : public SECATypeInfo
{
public: 
     // ISStruct automation exposed properties & methods 
    STDMETHOD_(ISCollection FAR*, get_Members)(); 
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    TOOLKIT_API static HRESULT Create(LPTYPEINFO ptinfo, SECAStruct FAR* FAR* ppStruct); // Creates and intializes Struct object 
    TOOLKIT_API SECAStruct();
    TOOLKIT_API ~SECAStruct();
    
private:
    LPTYPEINFO m_ptinfo;            // ITypeInfo* of struct typeinfo.
    LPDISPATCH m_pdispMembers;      // Collection of members in struct.
};

class FAR SECAUnion : public SECATypeInfo
{  
public:
    // ISUnion automation exposed properties & methods  
    STDMETHOD_(ISCollection FAR*, get_Members)();   
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    TOOLKIT_API static HRESULT Create(LPTYPEINFO ptinfo, SECAUnion FAR* FAR* ppUnion); // Creates and intializes Struct object 
    TOOLKIT_API SECAUnion();
    TOOLKIT_API ~SECAUnion();
    
private:
    LPTYPEINFO m_ptinfo;            // ITypeInfo* of union typeinfo.
    LPDISPATCH m_pdispMembers;      // Collection of members in union.
};


class FAR SECAAlias : public SECATypeInfo
{ 
public:    
    // ISAlias automation exposed properties & methods  
    STDMETHOD_(ISTypeDesc FAR*, get_BaseType)(); 
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    TOOLKIT_API static HRESULT Create(LPTYPEINFO ptinfo, SECAAlias FAR* FAR* ppAlias); // Creates and intializes Alias object 
    TOOLKIT_API SECAAlias();
    TOOLKIT_API ~SECAAlias();
    
private:
    LPTYPEINFO m_ptinfo;             // ITypeInfo* of alias typeinfo.
    LPDISPATCH m_pdispTypeDescBase;  // IDispatch of ISTypeDesc which describes the base type of this alias.
};  

// SECAFunction represents all functions (including methods).
class FAR SECAFunction : public ISFunction
{
public:
    // ISFunction automation exposed properties & methods 
    STDMETHOD_(BSTR, get_Name)();
    STDMETHOD_(BSTR, get_Documentation)();
    STDMETHOD_(long, get_HelpContext)();
    STDMETHOD_(BSTR, get_HelpFile)();
    STDMETHOD_(ISTypeDesc FAR*, get_ReturnType)();
    STDMETHOD_(ISCollection FAR*, get_Parameters)(); 
    STDMETHOD_(MEMBERID, get_Memberid)();
    STDMETHOD_(CALLCONV, get_CallConvention)(); 
    STDMETHOD_(FUNCKIND, get_FuncKind)();
    STDMETHOD_(INVOKEKIND, get_InvocationKind)();
    STDMETHOD_(SECA_OBJTYPE, get_Kind)();      
    STDMETHOD_(short, get_FuncFlags)();
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    TOOLKIT_API static HRESULT Create(LPTYPEINFO ptinfo, unsigned short nIndex, SECAFunction FAR* FAR* ppFunction); // Creates and intializes Function object 
    TOOLKIT_API SECAFunction();
    TOOLKIT_API ~SECAFunction();
    
private:   
    BSTR m_bstrName;                     // Function name.
    BSTR m_bstrDocumentation;            // Documentation.
    unsigned long m_ulHelpContext;       // Help context.
    BSTR m_bstrHelpFile;                 // Help file.
    LPDISPATCH m_pdispTypeDesc;          // IDispatch of ISTypeDesc that described return type.
    LPDISPATCH m_pdispParameters;        // Collection of parameters function.
    LPFUNCDESC m_pfuncdesc;              // FUNCDESC of function.
    LPTYPEINFO m_ptinfoFunction;         // TypeInfo of which this function is an element.
};

// SECAProperty represents dispinterface properties and structure & union members.
class FAR SECAProperty : public ISProperty
{
public:
    // ISProperty automation exposed properties & methods 
    STDMETHOD_(BSTR, get_Name)();
    STDMETHOD_(BSTR, get_Documentation)();
    STDMETHOD_(long, get_HelpContext)();
    STDMETHOD_(BSTR, get_HelpFile)();
    STDMETHOD_(ISTypeDesc FAR*, get_Type)();
    STDMETHOD_(MEMBERID, get_Memberid)(); 
    STDMETHOD_(SECA_OBJTYPE, get_Kind)();  
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();   
    TOOLKIT_API static HRESULT Create(LPTYPEINFO ptinfo, LPVARDESC pvardesc, SECAProperty FAR* FAR* ppProperty); // Creates and intializes Property object 
    TOOLKIT_API SECAProperty();
    TOOLKIT_API ~SECAProperty();
    
private:        
    BSTR m_bstrName;                     // Property name.
    BSTR m_bstrDocumentation;            // Documentation.
    unsigned long m_ulHelpContext;       // Help Context.
    BSTR m_bstrHelpFile;                 // Helpfile.
    MEMBERID m_memid;                    // MEMBERID of property.
    LPDISPATCH m_pdispTypeDesc;          // ISTypeDesc that describes type of property.
};

class FAR SECAConstant : public ISConstant
{
public:
    // ISConstant automation exposed properties & methods
    STDMETHOD_(BSTR, get_Name)();
    STDMETHOD_(BSTR, get_Documentation)();
    STDMETHOD_(long, get_HelpContext)();
    STDMETHOD_(BSTR, get_HelpFile)();
    STDMETHOD_(ISTypeDesc FAR*, get_Type)();    
    STDMETHOD_(VARIANT, get_Value)();      
    STDMETHOD_(MEMBERID, get_Memberid)(); 
    STDMETHOD_(SECA_OBJTYPE, get_Kind)();  
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    TOOLKIT_API static HRESULT Create(LPTYPEINFO ptinfo, LPVARDESC pvardesc, SECAConstant FAR* FAR* ppConstant); // Creates and intializes Constant object 
    TOOLKIT_API SECAConstant();
    TOOLKIT_API ~SECAConstant();
    
private:        
    BSTR m_bstrName;                       // Constant name
    BSTR m_bstrDocumentation;              // Documentation
    unsigned long m_ulHelpContext;         // Help context
    BSTR m_bstrHelpFile;                   // Helpfile
    LPDISPATCH m_pdispTypeDesc;            // ISTypeDesc that describes type of constant.
    MEMBERID m_memid;                      // MEMBERID.
    VARIANT m_vValue;                      // Constant value.
};

class FAR SECAParameter : public ISParameter
{
public:
    // ISParameter automation exposed properties & methods 
    STDMETHOD_(BSTR, get_Name)();
    STDMETHOD_(ISTypeDesc FAR*, get_Type)(); 
    STDMETHOD_(int, get_IDLFlags)();
    STDMETHOD_(SECA_OBJTYPE, get_Kind)();    
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    TOOLKIT_API static HRESULT Create(LPTYPEINFO ptinfo, BSTR bstrName, TYPEDESC FAR* ptypedesc, 
         IDLDESC FAR* pidldesc, SECAParameter FAR* FAR* ppParameter);  // Creates and intializes Parameter object 
    TOOLKIT_API SECAParameter();
    TOOLKIT_API ~SECAParameter();
    
private:  
    BSTR m_bstrName;                      // Parameter name.
    unsigned short m_wIDLFlags;           // specifies in/out/in-out/none
    LPDISPATCH m_pdispTypeDesc;           // ISTypeDesc* that describes type of parameter.
};  

// Describes a type
class FAR SECATypeDesc : public ISTypeDesc
{
public:   
    // ISTypeDesc automation exposed properties & methods
    STDMETHOD_(short, get_Type)();
    STDMETHOD_(ISTypeInformation FAR*, get_UserDefinedDesc)();
    STDMETHOD_(ISArrayDesc FAR*, get_ArrayDesc)();
    STDMETHOD_(ISTypeDesc FAR*, get_PointerDesc)();  

    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    TOOLKIT_API static HRESULT Create(LPTYPEINFO ptinfo, TYPEDESC FAR* ptypedesc, SECATypeDesc FAR* FAR* ppTypeDesc); // Creates and intializes TypeDesc object 
    TOOLKIT_API SECATypeDesc();
    TOOLKIT_API ~SECATypeDesc();
    
private:
    VARTYPE m_vartype;                  // Type
    LPDISPATCH m_pdispUserDefinedDesc;  // If m_vartype==VT_USERDEFINED, contains ISTypeInformation* of user-defined type., 
    LPDISPATCH m_pdispArrayDesc;        // if m_vartype==VT_CARRAY, contains ISArrayDesc* 
    LPDISPATCH m_pdispPointerDesc;      // if m_vartype==VT_PTR contains ISTypeDesc* of type pointed to.
};

// Describes C-Style array
class FAR SECAArrayDesc : public ISArrayDesc
{
public:     
    // ISArrayDesc automation exposed properties & methods
    STDMETHOD_(ISTypeDesc FAR*, get_ElementType)();
    STDMETHOD_(ISCollection FAR*, get_ArrayBounds)();   

    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    TOOLKIT_API static HRESULT Create(LPTYPEINFO ptinfo, ARRAYDESC FAR* parraydesc, SECAArrayDesc FAR* FAR* ppArrayDesc); // Creates and intializes ArrayDesc object 
    TOOLKIT_API SECAArrayDesc();
    TOOLKIT_API ~SECAArrayDesc();
    
private:
    LPDISPATCH m_pdispTypeDescElement;     // ISTypeDesc that descibed type of array element.
    LPDISPATCH m_pdispArrayBounds;         // ISArrayBound that describes array bounds.
};

class FAR SECAArrayBound : public ISArrayBound
{
public:
    // ISArrayBound automation exposed properties & methods
    STDMETHOD_(long, get_ElementsCount)();
    STDMETHOD_(long, get_LowerBound)();  

    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    TOOLKIT_API static HRESULT Create(unsigned long cElements, long lLBound, SECAArrayBound FAR* FAR* ppArrayBound); // Creates and intializes ArrayBound object
    
private:
    unsigned long m_cElements;             // Count of elements in array.
    long m_lLBound;                        // Lower bound of array.
};

// Generic collection class that holds all collections.
class FAR SECACollection : public ISCollection
{
public:
    // ISCollection automation exposed properties & methods
    STDMETHOD_(long, get_Count)();
    STDMETHOD_(LPDISPATCH, get_Item)(long lIndex);
    STDMETHOD_(LPUNKNOWN, get__NewEnum)();
    
    // SECACollection methods 
    STDMETHOD_(void, Add)(LPDISPATCH pdispItem);  
    STDMETHOD_(REFCLSID, GetInterfaceID)();   
    TOOLKIT_API static HRESULT Create(ULONG lMaxSize, long lLBound, SECACollection FAR* FAR* ppCollection); // Creates and intializes Collection object 
    TOOLKIT_API SECACollection();
    TOOLKIT_API ~SECACollection();
    
private:
    SAFEARRAY FAR *m_psa;          // Safe array that holds Collection collection items.
    ULONG m_cElements;             // Number of items in Collection collection.
    ULONG m_cMax;                  // Maximum number of items Collection collection can hold.
    long m_lLBound;                // Lower bound of index of Collection collection.
};

class FAR SECAEnumVariant : public IEnumVARIANT
{
public:
    // IUnknown methods 
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

    // IEnumVARIANT methods 
    STDMETHOD(Next)(ULONG cElements, VARIANT FAR* pvar, ULONG FAR* pcElementFetched);
    STDMETHOD(Skip)(ULONG cElements);
    STDMETHOD(Reset)();
    STDMETHOD(Clone)(IEnumVARIANT FAR* FAR* ppenum);
    
    TOOLKIT_API static HRESULT Create(SAFEARRAY FAR*, ULONG, SECAEnumVariant FAR* FAR*); // Creates and intializes Enumerator
    TOOLKIT_API SECAEnumVariant();
    TOOLKIT_API ~SECAEnumVariant();
    
private:
    ULONG m_cRef;           // Reference count                                 
    ULONG m_cElements;      // Number of elements in enumerator. 
    long m_lLBound;         // Lower bound of index.
    long m_lCurrent;        // Current index.
    SAFEARRAY FAR* m_psa;   // Safe array that holds elements.
};  

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif		// __AH_BROWSE_H_

