///////////////////////////////////////////////////////////////////////////////
// Property.h : Property class
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
// Authors:      Jeff Boenig
// Description:  Property class.
//

#pragma once

#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include <comdef.h>
#include <Foundation\Properties\PropIFace.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

/////////////////////////////////////////////////////////////////////////////
//@doc CProperty
//
//@class CProperty | This class provides a default implementation of the
// <c IProperty> interface.
//
//@base public | IQueryGuid
//@base public | IRefCount

class CProperty : public IProperty
{
// Constructors/destructor
public:
	//@cmember,mfunc
	// Construct a property.
	//@@syntax CProperty(const PropertyId id = 0, LPCTSTR lpszName = _T(""), LPCTSTR lpszDesc = _T(""), const int nCatId = -1);
	//@@syntax CProperty(const CProperty& src)
	//@@parmopt const PropertyId | id | 0 | Property ID
	//@@parmopt LPCTSTR | lpszName | _T("") | Property name
	//@@parmopt LPCTSTR | lpszDesc | _T("") | Property description
	//@@parmopt const int | nCatId | -1 | Category ID
	//@@parm const CProperty& | src | Source property to make copy of.
	//@@end
	/* Construct a property*/
	CProperty(const PropertyId id = 0,
	          LPCTSTR lpszName = _T(""),
	          LPCTSTR lpszDesc = _T(""),
	          const int nCatId = -1)
	{
		m_ulRefCount = 0L;
		m_id = id;
		m_varType = VT_EMPTY;
		m_dwStyleFlags = 0;
		m_name = lpszName;
		m_desc = lpszDesc;
		m_pEnumeration = NULL;
		m_nCatId = nCatId;
	}

	CProperty(const CProperty& src)
	{
		m_ulRefCount = 0L;
		m_id = src.m_id;
		m_varType = src.m_varType;
		m_dwStyleFlags = src.m_dwStyleFlags;
		m_name = src.m_name;
		m_desc = src.m_desc;
		m_pEnumeration = src.m_pEnumeration;
		m_nCatId = src.m_nCatId;
	}

	//@cmember
	/* Destroy a property. */
	virtual ~CProperty()
	{
		SetEnumeration(NULL);	// release
	}

// Attributes
protected:
	//@cmember
	/* Reference count */
	ULONG m_ulRefCount;
	//@cmember
	/* Style flags */
	DWORD m_dwStyleFlags;
	//@cmember
	/* Property identifier */
	PropertyId m_id;
	//@cmember
	/* Property type */
	VARTYPE m_varType;
	//@cmember
	/* Property name */
	_bstr_t m_name;
	//@cmember
	/* Property description */
	_bstr_t m_desc;
	//@cmember
	/* Pointer to enumeration for enumerated properties */
	IEnumeration* m_pEnumeration;	
	//@cmember
	/* Category identifier */
	int m_nCatId;

// Operations
public:
	//@cmember,mfunc
	// Get the ID of the property.
	//@@rdesc A property ID
	//@@comm
	// Each property has an identifier that is unique within a container.
	// The property ID is a LONG, which also happens to be compatible with
	// COM property IDs (DISPID).
	//@@end
	/* Get the ID of the property*/
	virtual PropertyId GetId() const
	{
		return m_id;
	}

	//@cmember,mfunc
	// Set the ID of the property.
	//@@rdesc void
	//@@parm Property ID to assign to the property.
	//@@end
	/* Set the ID of the property*/
	void SetId(const PropertyId id)
	{
		m_id = id;
	}

	//@cmember,mfunc
	// Get the variant type of the property.
	//@@rdesc Data type for the property
	//@@comm
	// This function returns the data type of the property. Since
	// VARIANTs are used for accessing property values, the property
	// data type is described using a VARTYPE.
	//@@end
	/* Get the variant type of the property*/
	virtual VARTYPE GetVariantType() const
	{
		return m_varType;
	}

	//@cmember,mfunc
	// Set the variant type of the property.
	//@@rdesc void
	//@@parm The variant type to assign to the property.
	//@@end
	/* Set the variant type of the property*/
	virtual void SetVariantType(const VARTYPE varType)
	{
		m_varType = varType;
	}

	//@cmember,mfunc
	// Get the style flags for the property.
	//@@rdesc DWORD containing style flags for the property
	//@@comm
	// Style flags are used to control how the property is displayed
	// and edited.
	//@@end
	/* Get the style flags for the property*/
	virtual DWORD GetStyleFlags() const
	{
		return m_dwStyleFlags;
	}

	//@cmember
	/* Set the style flags for the property. */
	void SetStyleFlags(const DWORD dwStyleFlags)
	{
		m_dwStyleFlags = dwStyleFlags;
	}

	//@cmember,mfunc
	// Get the name of the property.
	//@@rdesc void
	//@@parm String in which to return the name of the property.
	//@@end
	/* Get the name of the property*/
	virtual void GetName(BSTR& bName) const
	{
		bName = m_name.copy();
	}

	//@cmember,mfunc
	// Set the name of the property.
	//@@rdesc void
	//@@parm Value to assign as the name of the property.
	//@@end
	/* Set the name of the property*/
	void SetName(const OLECHAR* pszName)
	{
		m_name = pszName;
	}

	//@cmember,mfunc
	// Get the description of the property.
	//@@rdesc void
	//@@parm String in which to return the description of the property.
	//@@end
	/* Get the description of the property*/
	virtual void GetDescription(BSTR& bDesc) const
	{
		bDesc = m_desc.copy();
	}

	//@cmember,mfunc
	// Set the description of the property.
	//@@rdesc void
	//@@parm Value to assign as the description of the property.
	//@@end
	/* Set the description of the property*/
	void SetDescription(const OLECHAR* pszDesc)
	{
		m_desc = pszDesc;
	}

	//@cmember,mfunc
	// Get the category of the property.
	//@@rdesc Integer that identifiers the category to which the property
	// belongs or -1 if it doesn't belong to a category.
	//@@comm
	// Categories are used as a grouping mechanism for properties. The name
	// of a category is acquired by passing the category ID to the property
	// container.
	//@@end
	/* Get the category of the property*/
	virtual int GetCategory() const
	{
		return m_nCatId;
	}

	//@cmember,mfunc
	// Set the category of the property.
	//@@rdesc void
	//@@parm Category to assign property to.
	//@@end
	/* Set the category of the property.*/
	void SetCategory(const int nCatId)
	{
		m_nCatId = nCatId;
	}

	//@cmember,mfunc
	// Get the enumeration for the property.
	//@@rdesc Pointer to an enumeration.
	//@@comm
	// If the property is an enumerated property, this function returns a
	// pointer to the enumeration that describes the possible values for
	// the property. The value of an enumerated property is an index into
	// the enumeration. This function returns NULL for properties that are
	// not enumerated properties.
	//@@xref <c IEnumeration>
	//@@end
	/* Get the enumeration for the property*/
	virtual IEnumeration* GetEnumeration() const
	{
		if(m_pEnumeration)
			m_pEnumeration->AddRef();
		return m_pEnumeration;
	}

	//@cmember,mfunc
	// Set the enumerated values for the property.
	//@@rdesc void
	//@@parm Pointer to enumeration to assign to the property.
	//@@comm
	// Properties that are assigned an enumeration are referred to as
	// enumerated properties. The value of an enumerated property is
	// an index into the enumeration.
	//@@xref <c IEnumeration>
	//@@end
	/* Set the enumerated values for the property*/
	void SetEnumeration(IEnumeration* pIEnumVals)
	{
		if(m_pEnumeration)
		{
			m_pEnumeration->Release();
			m_pEnumeration = NULL;
		}

		if(pIEnumVals)
		{
			pIEnumVals->AddRef();
		}

		m_pEnumeration = pIEnumVals;
	}

	//@cmember,mfunc
	// Assignment operator to assign one property to another.
	//@@rdesc Reference to lhs object
	//@@parm Property to assign.
	//@@end
	/* Assignment operator to assign one property to another*/
	CProperty& operator=(const CProperty& src)
	{
		m_id = src.m_id;
		m_varType = src.m_varType;
		m_dwStyleFlags = src.m_dwStyleFlags;
		m_name = src.m_name;
		m_desc = src.m_desc;
		m_pEnumeration = src.m_pEnumeration;
		return *this;
	}

	BEGIN_GUID_MAP(CProperty)
		GUID_ENTRY(IProperty)
		GUID_ENTRY(IQueryGuid)
		GUID_ENTRY(IRefCount)
	END_GUID_MAP

	//@cmember,mfunc
	// Add a reference to this object.
	//@@rdesc New reference count value.
	//@@end
	/* Add a reference to this object*/
	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		return ++m_ulRefCount;
	}

	//@cmember,mfunc
	// Release a reference to this object.
	//@@rdesc New reference count value.
	//@@end
	/* Release a reference to this object*/
	virtual ULONG STDMETHODCALLTYPE Release()
	{
		ULONG ulRefCount = --m_ulRefCount;
		if (m_ulRefCount == 0)
			delete this;
		return ulRefCount;
	}
};

}; // namespace stingray::foundation
}; // namespace stingray

#endif  // #ifndef __PROPERTY_H__
