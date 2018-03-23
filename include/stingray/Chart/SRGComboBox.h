///////////////////////////////////////////////////////////////////////////////
// SRGComboBox.h
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
// The text comments in this file are formatted to generate
// a help file on build using Microsoft's free Autoduck tool.
// The help file is available with this source and it is
// recommended that you use this file in conjunction with the
// mfc help files.
/////////////////////////////////////////////////////////////
//
// SRGComboBox.h : header file
//
//////////////////////////////////////////////////////////////
#if !defined(_SRGCOMBOBOX_H_INCLUDED_)
#define _SRGCOMBOBOX_H_INCLUDED_

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block for SRGraphItemData
// adinsert AutoDuck insertion point for SRGraphItemData
//@doc SRGraphItemData
//@struct SRGraphItemData | The SRGraphItemData structure combines a DWORD value and a string into a single object. 
//It is used by the wizard to associate a resource ID and a resource file name with an item in a list box.
struct SRGraphItemData
{
	DWORD    id;			//@field Resource ID
	CString  axisResName;	//@field Resource file name string

	//@cmember
	/* Constructor with parameters*/
	inline SRGraphItemData(DWORD value, LPCTSTR lpResName)
	{
		id = value;
		axisResName = lpResName;
	}
};

/////////////////////////////
// AutoDuck tag block for SRGComboBox 
// adinsert AutoDuck insertion point for SRGComboBox 
//$head The Chart Wizard
//$level 1

//@doc SRGComboBox 
//@class SRGComboBox is an extension of CComboBox with several useful utility functions.<nl>
//Several functions assume that the 32-bit value associated with each combobox item is a 
//pointer to an SRGraphItemData object.
class SRGComboBox : public CComboBox
{
// Construction
public:
	//@cmember
	/* Constructor*/
	CHART_API SRGComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SRGComboBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	CHART_API virtual BOOL ReplaceItemString(int nIndex, LPCTSTR lpszNew);
	//@cmember
	/* Remove the item with index nSrcIndex and insert it before*/
	// the item with index nDestIndex.
	CHART_API virtual void RePositionItemAndData(int nSrcIndex, int nDestIndex);
	//@cmember
	/* Replaces the data dwOld with the data dwNew. Every item */
	//with data dwOld will have its data be replaced.
	CHART_API virtual void ReplaceItemData(SEC_DWORD dwOld, SEC_DWORD dwNew);
	//@cmember
	/* Searches the items in the combobox for one that has the specified resource ID */
	//in its associated SRGraphItemData object -- if such an item is found, it becomes the current selection
	CHART_API virtual int SetCurSelByPtrData(SEC_DWORD dwValue);
	//@cmember
	/* Deletes the item from the combobox that has the specified resource ID */
	//in its associated SRGraphItemData object
	CHART_API virtual void DeleteItemByData(SEC_DWORD dwItemData);
	//@cmember
	/* Adds a string to the combobox and sets the 32/64-bit value associated with the item to the specified value*/
	CHART_API int AddStringData(LPCTSTR lpszString, SEC_DWORD dwItemData);
	//@cmember
	/* Searches the items in the combobox for one that has the specified value */
	//in its associated 32/64-bit data -- if such an item is found, it becomes the current selection
	CHART_API int SetCurSelByData(SEC_DWORD dwValue);
	//@cmember
	/* Returns the 32/64-bit value associated the currently selected item or CB_ERR*/
	CHART_API virtual		SEC_DWORD GetCurItemData();
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(SRGComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif // !defined(_SRGCOMBOBOX_H_INCLUDED_)
