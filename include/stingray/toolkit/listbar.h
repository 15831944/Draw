///////////////////////////////////////////////////////////////////////////////
// listbar.h
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
//  Author:             Justin Rudd
//  Description:        Declarations for SECListBar
//  Created:            September 1997
//
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifdef WIN32

#ifndef __LISTBAR_H__
#define __LISTBAR_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SECBAR_H__
#include "toolkit\secbar.h"
#endif

#include <StingrayExportDefs.h>

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

//Forward Declarations
class SECShortcutListCtrl;

//@doc SECListBar 
//@class SECListBar is a specialized SECBar that contains the knowledge of how to insert and remove items from its associated CWnd.
// The CWnd will always be a SECShortcutListCtrl or a SECShortcutListCtrl derived class. This class adds simple one liner
// functions around the most commonly used list control functions, such as InsertItem, HitTest, and SetItemData.
//@comm See the DEMO sample in the \SAMPLES\TOOLKIT\STANDARD\TABS\LISTBAR directory for a demonstration of the SECListBar class.
//@base public | SECBar
//@xref<c SECBar> <c SECShortcutBar>
class SECListBar : public SECBar
{

	TOOLKIT_DECLARE_DYNCREATE( SECListBar )

public:
	//@Access Public Members
	//@Access Constructors/Destructors
	//@cmember
	/* Constructs the SECListBar object.*/
	TOOLKIT_API SECListBar();

	//@cmember
	/* Constructs an SECListBar object from another SECListBar object.*/
	TOOLKIT_API SECListBar( const SECListBar& src );

	//@cmember
	/* Destroys the SECListBar object.*/
	TOOLKIT_API virtual ~SECListBar();

	//@Access Operators
	//@cmember
	/* Overloaded assignment operator for SECListBar objects.*/
	TOOLKIT_API const SECListBar& operator=( const SECListBar& src );

	//@Access Attributes
	//@cmember
	/* Returns the associated SECShortcutListCtrl object.*/
	TOOLKIT_API SECShortcutListCtrl* GetListCtrl();
	TOOLKIT_API const SECShortcutListCtrl* GetListCtrl() const;

	TOOLKIT_API virtual void SetWnd( const CWnd* const pWnd );
	TOOLKIT_API virtual void DestroyWindow();
	TOOLKIT_API virtual void DeleteWindow();

	//@cmember
	/* Sets the notification window.*/
	TOOLKIT_API void SetNotifyWnd( CWnd* pWnd );

	//@cmember
	/* Returns the image list associated with this object.*/
	TOOLKIT_API CImageList* GetImageList(int nImageList) const;

	//@cmember
	/* Associates an image list with the list bar object.*/
	TOOLKIT_API CImageList* SetImageList(CImageList* pImageList, int nImageListType);

	//@cmember
	/* Returns a count of the items contained in the list bar.*/
	TOOLKIT_API int GetItemCount() const;
	

	TOOLKIT_API BOOL GetItem(LV_ITEM* pItem) const;
	TOOLKIT_API BOOL SetItem(const LV_ITEM* pItem);
	
	TOOLKIT_API CString GetItemText(int nItem, int nSubItem) const;
	TOOLKIT_API CString GetItemText(int nItem) const;

	TOOLKIT_API int GetItemText(int nItem, int nSubItem, LPTSTR lpszText, int nLen) const;
	TOOLKIT_API int GetItemText(int nItem, LPTSTR lpszText, int nLen) const;

	TOOLKIT_API BOOL SetItemText(int nItem, int nSubItem, LPCTSTR lpszText);
	TOOLKIT_API BOOL SetItemText(int nItem, LPCTSTR lpszText );
	
	//@cmember
	/* Sets the data for an item in the list bar.*/
	TOOLKIT_API BOOL SetItemData(int nItem, SEC_DWORD dwData);

	//@cmember
	/* Gets the data for an item in the list bar */
	TOOLKIT_API SEC_DWORD GetItemData(int nItem) const;
	
// Operations

	//@Access Public Operations
	//@cmember
	/* Appends an item to the list bar from the associated image list. */
	TOOLKIT_API int AddItem( LPCTSTR lpszItem, int nImage );

	TOOLKIT_API int InsertItem(const LV_ITEM* pItem);

	//@cmember
	/* Inserts an item into the list bar at a specific location.*/
	TOOLKIT_API int InsertItem(int nItem, LPCTSTR lpszItem, int nImage);
	
	//@cmember
	/* Removes an item from the list bar.*/
	TOOLKIT_API BOOL DeleteItem(int nItem);

	//@cmember
	/* Deletes all the items in the list bar.*/
	TOOLKIT_API BOOL DeleteAllItems();
	
	//@cmember
	/* todo Add a description*/
	TOOLKIT_API int HitTest(LV_HITTESTINFO* pHitTestInfo) const;

	//@cmember
	/* Checks to see if the point is on the location as specified by the pFlags parameter.*/
	TOOLKIT_API int HitTest(CPoint pt, UINT* pFlags = NULL) const;
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // #ifndef __LISTBAR_H__
#endif // #ifdef  WIN32

