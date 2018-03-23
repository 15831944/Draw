///////////////////////////////////////////////////////////////////////////////
// gxabstr.h : Interface of abstract base classes that have no implementation
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
// Author: Stefan Hoenig
//

#ifndef _GXABSTR_H_
#define _GXABSTR_H_

#ifndef _GXVER_H_
#include "gxver.h"
#endif

// // #include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

// abstract base classes declared in this file
class CGXAbstractControlFactory;
class CGXAbstractTabWndInterface;
class CGXAbstractRecordInfoWndInterface;
class CGXAbstractCommandFactory;
class CGXNoOleDataObjectProxy;
class CGXNoOleDataSourceProxy;
class CGXAbstractGridDropTargetImp;
class CGXNoToolTipCtrlProxy;
class CGXAbstractGridSortImp;
class CGXAbstractGridSortMoveDataImp;
class CGXAbstractCalcSizeImp;
class CGXAbstractStyleCompareSubsetImp;
class CGXAbstractGridFloatCellsImp;
class CGXAbstractSpanCellPoolImp;
class CGXAbstractDelayedRangePoolImp;
class CGXAbstractGridCoveredCellsImp;
class CGXAbstractCoveredCellPoolImp;
class CGXAbstractGridMergeCellsImp;
class CGXAbstractDrawSpannedCellsImp;
class CGXAbstractGridFindReplaceImp;
class CGXAbstractGridPrintImp;
class CGXAbstractGridOldDrawingImp;
class CGXAbstractGridUpdateHintImp;
class CGXAbstractGridResizeToFitImp;
class CGXAbstractPrintDeviceImp;
class CGXAbstractGridHideCellsImp;
class CGXAbstractStyleSerializeImp;
class CGXAbstractSerializeOG5CompatibleImp;
class CGXAbstractGridDocSerializeImp;
class CGXAbstractGridProfileImp;
class CGXAbstractGridParamCopyOperatorImp;
class CGXAbstractGridUserSelectRangeImp;
class CGXAbstractGridExcelLikeFrameImp;
class CGXAbstractGridUserDragSelectRangeImp;
class CGXAbstractGridMoveRowsColsImp;
class CGXAbstractGridUserResizeCellsImp;
class CGXAbstractGridOptimizedUpdateImp;
class CGXAbstractDrawRotatedTextImp;
class CGXAbstractDateTimeImp;
class CGXAbstractGridMarkEditHeaderImp;
class CGXAbstractGridFreezeMenuHelperImp;
class CGXAbstractDataCopyMoveCellsImp;
class CGXAbstractGridDirectCopyMoveCellsImp;
class CGXAbstractGridTextDataExchangeImp;
class CGXAbstractGridStyleDataExchangeImp;
class CGXAbstractGridCutPasteImp;
class CGXAbstractGridClearCellsImp;
class CGXAbstractGridRangeNameImp;
class CGXAbstractLongOperationImp;
class CGXAbstractNumberFormattingImp;
class CGXAbstractGridExcelLikeFillImp;

// Display a warning if funtions are called that have no concrete 
// implementation.
// 

#ifdef _DEBUG

GRID_API void AFXAPI GXCheckImp(void* pImp, LPCTSTR pszFunc);
GRID_API void AFXAPI GXSetAssertNoImp(LPCTSTR pszFunc);

#define GX_CHECKIMP(pImp, pszFunc) GXCheckImp(pImp, _T(pszFunc))

#else

#define GX_CHECKIMP(pImp, pszFunc) 
#define GXSetAssertNoImp(pszFunc)

#endif

/////////////////////////////////////////////////////////////////////////////
// Control Factory

// forward declarations 
class CGXControl;
class CGXGridCore;
class CGXStylesMap;

//@doc CGXAbstractControlFactory 
//@class CGXAbstractControlFactory 
// Abstract base class.<nl>
// In order to create a Control Factory Class for your application 
// you have to derive a class from <c CGXAbstractControlFactory> and 
// override all the pure virtual methods. The "Control Factory Wizard" 
// fully automates the creation of the Control Factory Class. 
// See the section "Reducing the size of your application" in the Objective 
// Grid User's Guide for more information on how to use the Control Factory Wizard 
// to create a Control Factory Class.<nl>
//
// Responsibilities of the Control Factory Class are:<nl>
// <ul>
// <li>Registration of cell types and instantiation of cell type objects on demand. <eli>
// <li>Registration of "concrete implementations" for various Objective Grid features (e.g. Undo/Redo, Serialization, and more). <eli>
// <li>Registration of window classes for custom controls in dialog templates. <eli>
// <eul>
// <np>
// If you are linking your application statically to Objective Grid and are concerned about the size of your application, a Control Factory lets you specify which cell types should be linked into your application and excludes cell types and features you don't need. This will shrink the size of your final application. 
// <np>
// <h3>How do I use the Control Factory Class?<eh3>
// <np>
// You have two choices:<nl>
// <ul> 
// <li>You are not concerned about space considerations - you only want to add new cell types.<eli>
// <li>You want to limit the number of cell types or features linked into your application.<eli> 
// <eul>
// If a) is your choice, simply derive a class from CGXControlFactory (the default factory class implementation) and override the following virtual methods: 
// <ul>
//
// <li>CGXControl* CreateControl(UINT nID, CGXGridCore* pGrid);<eli>
// <li>void RegisterAllControls(CGXStylesMap* pStylesMap);<eli>
// <li>void RegisterAllUserAttributes(CGXStylesMap* pStylesMap);<eli>
// <li>) is your choice, you cannot derive from CGXControlFactory.  Instead, you must derive from CGXAbstractControlFactory using the "Control Factory Wizard". In the "Control Factory Wizard" you can select the cell types and features that should be linked into your application. <eli>
// <eul>
// 
// In the <f InitInstance> method of your application object, you have to register your control factory by inserting the following line (instead of using the standard <f GXInit()> call):
//
// <np><code> GXInit(new CMyControlFactory);<enp><ecode>
// <nl> In the <f OnInitialUpdate> method of your view class you can specify whether user attributes and cell types should be visible in the <c CGXStyleSheet> by inserting the following lines:
// <np><code>// Register default controls for the CGXStyleSheet-Controls<ecode><enp> 
// <np><code>// page (control objects will be created on demand in <enp><ecode>
// <np><code>// CGXControlFactory). <ecode><enp>
// <np><code>stylesmap->RegisterDefaultControls();<ecode><enp> 
// <np><code>// Register user attributes for the CGXStyleSheet-User <ecode><enp> 
// <np><code> // Attributes page (control objects will be created on <ecode><enp>
// <np><code> // demand in CGXControlFactory). <ecode><enp>
// <nl> <np><code>stylesmap->RegisterDefaultUserAttributes();<ecode><enp>
// <nl>If you do not want the attributes and cell types visible in the <c CGXStyleSheet>, then you should skip the previous lines of code. You will still be able to use the cell type objects and user attributes in your grid. They will only be hidden from the user in the <c CGXStyleSheet>.
// @xref <mf CGXGridCore::GetRegisteredControl> <f GXInit> <f GXTerminate> <mf CGXStylesMap::RegisteredDefaultControls>
// <mf CGXStylesMap::RegisteredDefaultUserAttributes> <c CGXControlFactory>  
class CGXAbstractControlFactory
{
public:
	//@cmember
	// CreateControl is called to instantiate a specific cell type as 
	// child of the given grid. In your override of CreateControl., 
	// you should check nID to determine which control to instantiate. 
	// This is best done with a switch statement
	virtual CGXControl* CreateControl(UINT nID, CGXGridCore* pGrid) = 0;

	//@cmember
	// RegisterAllControls is called to register the 
	// control names with the styles map. This is necessary 
	// when you want the controls to appear in the Controls-page of the CGXStyleSheet.	
	virtual void RegisterAllControls(CGXStylesMap* pStylesMap) = 0;

	//@cmember
	// RegisterAllUserAttributes is called to register 
	// the user attribute names with the styles map. This is necessary when
	// you want the user attributes to appear in the User attribute-page of the CGXStyleSheet.
	virtual void RegisterAllUserAttributes(CGXStylesMap* pStylesMap) = 0;

	//@cmember 
	// This method is called from each grid at initialization 
	// time (from OnGridInitialUpdate() to be more concrete). 
	// It instantiates concrete implementations for grid features 
	// and attaches the instantiated object to the grid. 
	virtual void InitializeGridComponents(CGXGridCore* pGrid) = 0;
	
	//@cmember
	// This method is called from Objective Grid at application initialization 
	// time (from GXInit). It instantiates concrete implementations for various features.
	virtual void InitializeApplicationComponents() = 0;

	//@cmember
	// RegisterWndClasses is called during the initialization of 
	// your application to register window class names used in Objective Grid. 
	// These window classes can then be used as registered controls in the dialog 
	// template (see GRID_DECLARE_REGISTER and GRID_IMPLEMENT_REGISTER for further information).	
	virtual void RegisterWndClasses(HINSTANCE hResource) = 0;
	
	//@cmember
	// The counterpart of RegisterWndClasses. 
	// Called during the cleanup of your application (i.e., when you call GXTerminate).
	virtual void UnregisterWndClasses(HINSTANCE hResource) = 0;
};

//@doc CGXAbstractControlFactory
//@mfunc virtual void  | CGXAbstractControlFactory | CreateControl  | 
// @parm UINT | nID | Specifies the control id (same as CGXStyle::GetControl)
// @parm CGXGridCore* | pGridCore | Points to the parent grid
// @rdesc 
// A pointer to the allocated control object.
// @rem
// <mf CreateControl> is called to instantiate a specific cell type as child of the given grid. 
// In your override of <mf CreateControl>, you should check nID to determine which control to 
// instantiate. This is best done with a switch statement.<nl>
// Please note that some control require additional initialization steps 
// beyond simple construction before the control pointer can be returned.
// Please refer to the code in Src\Grid\gxfactry.cpp for any additional initialization steps.
// The following sample code shows a typical case statement for control instantiation.
// @ex
//The following sample code shows a typical case statement for control instantiation.|
//CGXControl* CGXControlFactory::CreateControl(UINT nID, 
//CGXGridCore* pGrid)
//{
//CGXControl* pControl = NULL;
//  // Create control on demand
//switch (nID)
//{
//case GX_IDS_CTRL_EDIT:
//  // Default edit box
// pControl = new CGXEditControl(pGrid, GX_IDS_CTRL_EDIT);
// break;
// case GX_IDS_CTRL_HEADER:
//  // default headers
// pControl = new CGXHeader(pGrid);
// break;
// }
// return pControl;
// }
// @xref <mf CGXStyle::GetControl CGXGridCore::GetRegisteredControl >
//<c CGXAbstractControlFactory>

//@doc CGXAbstractControlFactory
//@mfunc virtual void  | CGXAbstractControlFactory | InitializeApplicationComponents  | 
//@rem
//This method is called from Objective Grid at application initialization time (from GXInit). 
//It instantiates concrete implementations for various features.
//@ex
/*Here is how your override of <mf InitializeApplicationComponents> might look: |
void CGXControlFactory::InitializeApplicationComponents()
{
  // General application wide components - other components
  // rely on some of these application wide components. 

CGXPrintDevice::ImplementPrintDevice();

  // Store printer settings in document

CGXStyle::ImplementCompareSubset();

  // CGXStyle and CGXFont's IsSubSet method

CGXStyle::ImplementSerialize();

  // CGXStyle, CGXFont, CGXBrush and CGXPen's Serialize 

  // method

CGXStyle::ImplementSerializeOG5Compatible();

  // OG 5 Backward compatibility for deserializing 

  // CGXStyle class CGXStyle::ImplementProfile();

  // CGXStyle - read and write profile

CGXGridParam::ImplementSerialize();

  // Serialize parameter and related subobjects

CGXGridParam::ImplementCopyOperator();

  // Copy parameter object with all its subobjects

CGXDrawingAndFormatting::ImplementDrawRotatedText();

  // Draw rotated text in cells

CGXDrawingAndFormatting::ImplementNumberFormatting();

  // Number formatting with GXStyle::SetFormat

GXImplementOleDateTime();

  // Date & Time parsing with COleDateTime routines

  // using COleDateTime routines

CGXData::ImplementSortMoveData();

  // Rearrange rows and columns in CGXData (when sorting the grid)

CGXData::ImplementCopyMoveCells();

  // Direct copying and moving cells within grid in CGXData

CGXLongOperation::ImplementLongOperation(); 

  // Wait cursor, ESC key and status messages

CGXCoveredCellPool::ImplementCoveredCellPool();

  // Covered cells pool data structure

CGXSpanCellPool::ImplementSpanCellPool();

Float&Merge cells pool data structure

CGXDelayedRangePool::ImplementDelayedRangePool();

  // Lazy Evaluation data structure for float&merge cells
}
*/
// @xref <c CGXAbstractControlFactory>

//@doc CGXAbstractControlFactory
//@mfunc virtual void  | CGXAbstractControlFactory | InitializeGridComponents  | 
//@parm CGXGridCore* | pGrid | Pointer to the grid object |
//@rem
//This method is called from each grid at initialization time 
//(from OnGridInitialUpdate() to be more concrete). It instantiates concrete
//implementations for grid features and attaches the instantiated object to the grid. 
//The grid will keep the object alive until the grid gets out of scope. 
//When the grid is destructed all grid feature objects will be destroyed. 
//This method instantiates objects that are used by particular grids (referred to by pGrid).
//@ex
/*Here is how your override of <mf InitializeGridComponents> might look: |
void CGXControlFactory::InitializeGridComponents(CGXGridCore* pGrid)

{

  // InitializeGridComponents is called from CGXGridCore 

  // constructor. No window been created for the grid yet. 

  // m_pGridWnd is NULL.

  // Do not use pGrid->m_pGridWnd!

pGrid;

  // General grid components - enable them in the control

  // factory so that all grids in your application behave

  // similar. You can enable/disable the behavior for individual

  // grid with CGXGridParam settings (e.g. EnableMoveRows, 

  // EnableSelection etc).

  pGrid->ImplementFindReplace();// Find and Replace 

  pGrid->ImplementHideCells();// Hiding rows and columns

  pGrid->ImplementAutoScroll();// AutoScrolling,

  // SpeedScrolling

  pGrid->ImplementResizeToFit();// Resize Cells to fit size

  pGrid->ImplementUpdateHint();// Update Hint mechanism

  pGrid->ImplementUndoRedo();// Undo and Redo 

  pGrid->ImplementGridSort();// Sorting rows or columns

  pGrid->ImplementOldDrawing();// Old drawing (for backward

  // compatibility)

  pGrid->ImplementCoveredCells();// Covered Cells

  pGrid->ImplementMergeCells();// Merge Cells

  pGrid->ImplementFloatCells();// Floating Cells

  pGrid->ImplementPrinting();// Printing

  pGrid->ImplementUserSelectRange();// Select cell ranges with

  // mouse or keyboard

  pGrid->ImplementExcelLikeFrame();// Excel-like Selection Frame

  pGrid->ImplementUserDragSelectRange();// Drag selected rows or

  // columns with mouse

  pGrid->ImplementUserResizeCells();// Resize rows or columns 

  // with mouse

  pGrid->ImplementOptimizedUpdate();// Optimized update for 

  // inserting, moving and 

  // removing rows and columms

  pGrid->ImplementMarkEditHeader();// Outline row and column

  // header of current cell

  pGrid->ImplementFreezeMenuHelper();// FreezeRows, UnfreezeRows

  // (and ..Cols) methods

  pGrid->ImplementDirectCopyMoveCells();// Direct copying, moving

  // of cells within one grid

  pGrid->ImplementTextDataExchange();// CSV text file and

  // clipboard data exchange

  pGrid->ImplementStyleDataExchange();// CGXStyle binary file and

  // clipboard data exchange

  pGrid->ImplementCutPaste();// Cut, Copy and Paste methods

  pGrid->ImplementClearCells();// ClearCells method

  #if _MFC_VER >= 0x0400

  pGrid->ImplementToolTips();// Tool-tips 

  #endif
  }
*/
// @xref <c CGXAbstractControlFactory>

//@doc CGXAbstractControlFactory
//@mfunc virtual void  | CGXAbstractControlFactory | RegisterAllControls  | 
//@parm CGXStylesMap* | pStylesMap | Points to the CGXStylesMap object where the controls' descriptions shall be added.|
//@rem
//<mf RegisterAllControls> is called to register the control names with the styles map.
//This is necessary when you want the controls to appear in the Controls-page of the <c CGXStyleSheet>.<nl>
//
//You should override this method either if you have added your own cell types 
//and you want them to appear in the style sheets for all grids in your application
//or if you only want a specific selection of cell types to appear in the <c CGXStyleSheet>.<nl>
//
//Note: This method registers controls only to appear in the <c CGXStyleSheet>.
//The method <mf CGXAbstractControlFactory::CreateControl> is responsible for 
//instantiating the control. If you don't want a cell type to be visible in the 
// <c CGXStyleSheet>, you don't have to register it here. 
// You will still be able to use the cell type with <mf CGXStyle::SetControl> in your grid.
//@ex
/*Here is how your override of <mf RegisterAllControls > might look: |
void CGXControlFactory::RegisterAllControls(CGXStylesMap* pStylesMap)

{

pStylesMap->AddControl(GX_IDS_CTRL_EDIT);

pStylesMap->AddControl(GX_IDS_CTRL_HEADER);

pStylesMap->AddControl(GX_IDS_CTRL_TEXTFIT);

pStylesMap->AddControl(GX_IDS_CTRL_COMBOBOX);

pStylesMap->AddControl(GX_IDS_CTRL_ONEBASED);

pStylesMap->AddControl(GX_IDS_CTRL_ZEROBASED);

pStylesMap->AddControl(GX_IDS_CTRL_ONEBASED_EX);

pStylesMap->AddControl(GX_IDS_CTRL_ZEROBASED_EX);

pStylesMap->AddControl(GX_IDS_CTRL_CBS_DROPDOWN);

pStylesMap->AddControl(GX_IDS_CTRL_CBS_DROPDOWNLIST);

pStylesMap->AddControl(GX_IDS_CTRL_SPINEDIT);

pStylesMap->AddControl(GX_IDS_CTRL_HOTSPOT);

pStylesMap->AddControl(GX_IDS_CTRL_SCROLLEDIT);

pStylesMap->AddControl(GX_IDS_CTRL_LISTBOX);

pStylesMap->AddControl(GX_IDS_CTRL_STATIC);

pStylesMap->AddControl(GX_IDS_CTRL_PUSHBTN);

pStylesMap->AddControl(GX_IDS_CTRL_RADIOBTN);

pStylesMap->AddControl(GX_IDS_CTRL_RADIOBTN3D);

pStylesMap->AddControl(GX_IDS_CTRL_CHECKBOX);

pStylesMap->AddControl(GX_IDS_CTRL_CHECKBOX3D);

pStylesMap->AddControl(GX_IDS_CTRL_MASKEDIT);

pStylesMap->AddControl(GX_IDS_CTRL_PROGRESS);

pStylesMap->AddControl(GX_IDS_CTRL_PASSWORD);

pStylesMap->AddControl(GX_IDS_CTRL_CBS_TABBED_DROPDOWN);

pStylesMap->AddControl(GX_IDS_CTRL_CBS_TABBED_DROPDOWNLIST);

pStylesMap->AddControl(GX_IDS_CTRL_TABBED_COMBOBOX);

#if _MFC_VER >= 0x0400

pStylesMap->AddControl(GX_IDS_CTRL_RICHEDIT);

pStylesMap->AddControl(GX_IDS_CTRL_CHECKLIST_COMBOBOX);

pStylesMap->AddControl(GX_IDS_CTRL_DATETIME);

pStylesMap->AddControl(GX_IDS_CTRL_DATETIMENOCAL);

#endif

}
*/
// @xref <c CGXAbstractControlFactory> <mf CGXControl::AddUserAttributes>
// <mf CGXStylesMap::RegisterDefaultControls> 


//@doc CGXAbstractControlFactory
//@mfunc virtual void  | CGXAbstractControlFactory | RegisterAllUserAttributes  | 
//@parm CGXStylesMap* | pStylesMap | Points to the <c CGXStylesMap> object where the user attribute descriptions shall be added.|
//@rem
//RegisterAllUserAttributes is called to register the user attribute names with the styles map.
//This is necessary when you want the user attributes to appear in the User attribute-page of the 
//CGXStyleSheet.<nl>
//
//You should override this method either if you have added your own user attributes and you 
//want them to appear in the style sheets for all grids in your application or if you only 
//want a specific selection of user attributes to appear in the <c CGXStyleSheet>.<nl>
//
//Note: This method registers user attributes only to appear in the <c CGXStyleSheet>. 
//If you don't want a user attribute to be visible in the <c CGXStyleSheet>, 
//you don't have to register it here. You will still be able to use the user attribute
//with <mf CGXStyle::SetUserAttribute> in your grid. 
//You only disable the possibility that the user can change the user attribute 
//through the style sheet. 
//@ex
/*Here is how your override of <mf RegisterAllUserAttributes > might look: |
void CGXControlFactory::RegisterAllUserAttributes(CGXStylesMap* pStylesMap)

{

CGXControl::AddUserAttributes(pStylesMap);

CGXSpinEdit::AddUserAttributes(pStylesMap);

CGXCheckBox::AddUserAttributes(pStylesMap);

CGXMaskControl::AddUserAttributes(pStylesMap);

CGXProgressCtrl::AddUserAttributes(pStylesMap);

CGXTabbedComboBox::AddUserAttributes(pStylesMap);

CGXTabbedComboBoxWnd::AddUserAttributes(pStylesMap);

#if _MFC_VER >= 0x0400

CGXDateTimeCtrl::AddUserAttributes(pStylesMap);

#endif

}
*/
// @xref <c CGXAbstractControlFactory> <mf CGXControl::AddUserAttributes>
// <mf CGXStylesMap::RegisterDefaultControls> <mf CGXStylesMap::RegisterDefaultUserAttributes>


//@doc CGXAbstractControlFactory
//@mfunc virtual void  | CGXAbstractControlFactory | RegisterWndClasses  | 
//@parm HINSTANCE | hResource | Use this instance handle for registering the window class (as shown in the example).|
//@rem
//<f RegisterWndClasses> is called during the initialization of your application to register window
// class names used in Objective Grid. These window classes can then be used as registered
// controls in the dialog template (see GRID_DECLARE_REGISTER and GRID_IMPLEMENT_REGISTER for 
//further information). <nl>
//
//If you have derived a class <c CGXAbstractControlFactory>, you need to override this method.<nl> 
//
//Here is how a typical override of RegisterWndClasses should look.
//If you don't need support for using CGXGridWnd or CGXTabWnd as a registered control 
//in a dialog template, you don't have to register any window classes.
//@ex
/* |
void CGXControlFactory::RegisterWndClasses(HINSTANCE hInstance)
{

CGXGridWnd::RegisterClass(hInstance);

#if !defined(_GX_NO_TABWND_SUPPORT)

  // Tab Window

CGXTabBeam::RegisterClass(hInstance);

CGXTabWnd::RegisterClass(hInstance);

#endif

}
*/
// @xref <c CGXAbstractControlFactory>

//@doc CGXAbstractControlFactory
//@mfunc virtual void  | CGXAbstractControlFactory | UnRegisterWndClasses  | 
//@parm HINSTANCE | hResource | Use this instance handle for unregistering the window class (as shown in the example).|
//@rem
//<f UnRegisterWndClasses>  is the counterpart to <f RegisterWndClasses>. 
//It is called during the cleanup of your application (i.e., when you call <f GXTerminate>).<nl>
//
//If you have derived a class <c CGXAbstractControlFactory>, you need to override this method.<nl> 
//
//Here is how a typical override of RegisterWndClasses should look.
//If you don't need support for using CGXGridWnd or CGXTabWnd as a registered control 
//in a dialog template, you don't have to register any window classes.
//@ex
/*
Here is how a typical override of UnregisterWndClasses should look: |
void CGXControlFactory::UnregisterWndClasses(HINSTANCE hInstance)
{

CGXGridWnd::UnregisterClass(hInstance);

#if !defined(_GX_NO_TABWND_SUPPORT)

  // Tab Window

CGXTabBeam::UnregisterClass(hInstance);

CGXTabWnd::UnregisterClass(hInstance);

#endif

}
*/
// @xref <c CGXAbstractControlFactory>








// You should derive your own CGXAbstractControlFactory and override
// the CreateControl method if you are concerned about the executable size
// of your application.
//
// If you have implemented a derived CGXAbstractControlFactory, you should
// call
//     GXInit(new CMyControlFactory)
// instead of GXInit()
// in your InitInstance method.


/////////////////////////////////////////////////////////////////////////////
// Support for tab window - Load or refresh worksheet name

class CGXAbstractTabWndInterface
{
public:
	virtual void UpdateTabName(const CWnd* pWnd, CString& sName, BOOL bUpdateBeam) = 0;
	virtual CString GetTabName(const CWnd* pWnd, int nTab) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Support for record info window 

// forward declarations 
class CGXGridCore;

class CGXAbstractRecordInfoWndInterface
{
public:
	virtual void UpdateRecordInfoWnd(CGXGridCore* pGrid) = 0;
	virtual void SetActivePane(CGXGridCore* pGrid) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Undo/Redo support 

// forward declarations 
class CGXRange;
class CGXStylesMap;
class CGXProperties;
class CGXStyle;
class CGXGridCore;
class CGXCommand;
class CGXLongOperation;

class CGXAbstractCommandFactory
{
public:
	GRID_API virtual ~CGXAbstractCommandFactory();

	virtual CGXCommand* CreateBlockCmd(LPCTSTR s = NULL) = 0;
	virtual CGXCommand* CreateSetRowHeightCmd(ROWCOL nFromRow, ROWCOL nToRow, int* anHeightArray) = 0;
	virtual CGXCommand* CreateHideRowsCmd(ROWCOL nFromRow, ROWCOL nToRow, BOOL* abHide) = 0;
	virtual CGXCommand* CreateSetDefaultRowHeightCmd(int nHeight) = 0;
	virtual CGXCommand* CreateSetColWidthCmd(ROWCOL nFromCol, ROWCOL nToCol, int* anWidthArray) = 0;
	virtual CGXCommand* CreateHideColsCmd(ROWCOL nFromCol, ROWCOL nToCol, BOOL* abHide) = 0;
	virtual CGXCommand* CreateSetDefaultColWidthCmd(int nWidth) = 0;
	virtual CGXCommand* CreateMoveRowsCmd(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow) = 0;
	virtual CGXCommand* CreateMoveColsCmd(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol) = 0;
	virtual CGXCommand* CreateRemoveRowsCmd(ROWCOL nFromRow, ROWCOL nToRow) = 0;
	virtual CGXCommand* CreateRemoveColsCmd(ROWCOL nFromCol, ROWCOL nToCol) = 0;
	virtual CGXCommand* CreateInsertRowsCmd(ROWCOL nRow, ROWCOL nCount, int* anHeightArray, CObArray* pCellsArray, CObArray* pRowsArray, ROWCOL nColCount) = 0;
	virtual CGXCommand* CreateInsertColsCmd(ROWCOL nCol, ROWCOL nCount, int* anWidthArray, CObArray* pCellsArray, CObArray* pColsArray, ROWCOL nRowCount) = 0;
	virtual CGXCommand* CreateSetCoveredCellsCmd(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol) = 0;
	virtual CGXCommand* CreateSetStyleRangeCmd(const CGXRange& range, int nType, CObArray* pCellsArray) = 0;
	virtual CGXCommand* CreateSetFrozenRowsCmd(ROWCOL nFrozenRows, ROWCOL nHeaderRows) = 0;
	virtual CGXCommand* CreateSetFrozenColsCmd(ROWCOL nFrozenCols, ROWCOL nHeaderCols) = 0;
	virtual CGXCommand* CreateMoveDataRowsCmd(const CGXRange& rangeSort, CRowColArray* pawRowIndex) = 0;
	virtual CGXCommand* CreateMoveDataColsCmd(const CGXRange& rangeSort, CRowColArray* pawColIndex) = 0;
	virtual CGXCommand* CreateChangeStylesMapCmd(const CGXStylesMap& stylesMap) = 0;
	virtual CGXCommand* CreateChangePropertiesCmd(const CGXProperties& Properties) = 0;
	virtual CGXCommand* CreateChangeBaseStyleCmd(WORD wStyleId, const CGXStyle& BaseStyle, const CString& sName) = 0;
	virtual CGXCommand* CreateMoveCellsCmd(const CGXRange& rg, ROWCOL nRow, ROWCOL nCol, CObject* pUndoInfo) = 0;
	virtual CGXCommand* CreateSetRangeNameCmd(CString name, BOOL bOldRange, const CGXRange& oldRange) = 0;
	virtual CGXCommand* CreateDeleteRangeNameCmd(CString name, const CGXRange& oldRange, CObject* pUndoInfo) = 0;
	
	virtual BOOL SetAdvancedUndo(CGXGridCore* pGrid, BOOL bAdvUndo) = 0;
	virtual CObject* GetAdvancedUndoInfo(CGXGridCore* pGrid) = 0;
	virtual BOOL UndoAdvanced(CGXGridCore* pGrid, CObject* pAdvUndo, BOOL bCreateUndoInfo, BOOL bOnlyToolCells) = 0;
	virtual void CleanAdvancedUndo(CGXGridCore* pGrid) = 0;
	virtual BOOL ExecuteCommand(CGXCommand* pCmd, CGXGridCore* pGrid, GXCmdType ctType) = 0;
	virtual void AddCommand(CGXGridCore* pGrid, CGXCommand* pCmd, GXCmdType ctCmd) = 0;
	virtual void RemoveCommand(CGXGridCore* pGrid, GXCmdType ctCmd) = 0;
	virtual BOOL Undo(CGXGridCore* pGrid) = 0;
	virtual BOOL Redo(CGXGridCore* pGrid) = 0;
	virtual void BeginTrans(CGXGridCore* pGrid, LPCTSTR s) = 0;
	virtual void CommitTrans(CGXGridCore* pGrid) = 0;
	virtual void Rollback(CGXGridCore* pGrid) = 0;
	virtual void OnCellUndone(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, BOOL bSetEdit) = 0;
	virtual BOOL CanUndo(CGXGridCore* pGrid, CCmdUI* pCmdUI) = 0;
	virtual BOOL CanRedo(CGXGridCore* pGrid, CCmdUI* pCmdUI) = 0;
	virtual BOOL CreateRemoveRowsUndoInfo(CGXGridCore* pGrid, ROWCOL& nFromRow, ROWCOL& nCount, ROWCOL& nColCount, CObArray*& pOldCellsArray, CObArray*& pOldRowsArray, CGXLongOperation& theOp) = 0;
	virtual BOOL CreateRemoveColsUndoInfo(CGXGridCore* pGrid, ROWCOL& nFromCol, ROWCOL& nCount, ROWCOL& nRowCount, CObArray*& pOldCellsArray, CObArray*& pOldRowsArray, CGXLongOperation& theOp) = 0;
};


/////////////////////////////////////////////////////////////////////////////
// CGXNoOleDataObjectProxy
//
// This abstract base class helps us to call functions from COleDataObject
// without having to statically link in all the OLE stuff.
//
// The OLE stuff will only be linked into the application when
// the programmer wants to add support for OLE Drag'n Drop and
// registers the grid with CGXGridDropTarget::Register().
//
// The base class version does not hold a COleDataObject. Only the
// derived CGXOleDataObjectProxy implements a COleDataObject.

class CGXNoOleDataObjectProxy;
class CGXAbstractGridDropTargetImp;
class CGXNoOleDataSourceProxy;

#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_OLE_SUPPORT)

class CGXNoOleDataObjectProxy
{
public:
	GRID_API virtual ~CGXNoOleDataObjectProxy();

	virtual BOOL GetData(CLIPFORMAT cfFormat, LPSTGMEDIUM lpStgMedium,
		LPFORMATETC lpFormatEtc = NULL) = 0;

	virtual BOOL IsDataAvailable(CLIPFORMAT cfFormat,
		LPFORMATETC lpFormatEtc = NULL) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// CGXNoOleDataSourceProxy
//

class COleDropSource;
class CGXNoOleDataSourceProxy;
class CGXRangeList;

class CGXNoOleDataSourceProxy
{
public:
	GRID_API virtual ~CGXNoOleDataSourceProxy();

	// CacheData & DelayRenderData operations similar to ::SetClipboardData
	virtual void CacheGlobalData(CLIPFORMAT cfFormat, HGLOBAL hGlobal,
		LPFORMATETC lpFormatEtc = NULL) = 0;    // for HGLOBAL based data

	// Clipboard and Drag/Drop access
	virtual DROPEFFECT DoDragDrop(
		DWORD dwEffects = DROPEFFECT_COPY|DROPEFFECT_MOVE|DROPEFFECT_LINK,
		LPCRECT lpRectStartDrag = NULL,
		COleDropSource* pDropSource = NULL) = 0;

	virtual void Empty() = 0;   // empty cache (similar to ::EmptyClipboard)

	// CGXGridCore Overridables
	virtual BOOL DndStartDragDrop(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol) = 0;
	virtual BOOL OnDndCacheGlobalData(CGXGridCore* pGrid, CGXNoOleDataSourceProxy* pSrcItem, const CGXRangeList& selList, ROWCOL& nDndRowExt, ROWCOL& nDndColExt) = 0;
};

class CGXAbstractGridDropTargetImp
{
public:
	// GridCore overrides
	// overridables for drop target
	virtual BOOL OnDndCalculateFocusRect(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pOleDataObjectProxy, ROWCOL& nRowExt, ROWCOL& nColExt) = 0;
	virtual BOOL OnDndQueryAcceptData(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject) = 0;
	virtual BOOL OnDndDropData(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, ROWCOL nRow, ROWCOL nCol) = 0;

	// support for drop target, functions called from CGXGridDropTarget
	virtual DROPEFFECT OnGridDragEnter(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, DWORD dwKeyState, CPoint point) = 0;
	virtual DROPEFFECT OnGridDragOver(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, DWORD dwKeyState, CPoint point) = 0;
	virtual void OnGridDragLeave(CGXGridCore* pGrid) = 0;
	virtual BOOL OnGridDrop(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, DROPEFFECT dropEffect, CPoint point) = 0;
	virtual DROPEFFECT OnGridDropEx(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point) = 0;
	virtual DROPEFFECT OnGridDragScroll(CGXGridCore* pGrid, DWORD dwKeyState, CPoint point) = 0;

	// helpers for drop target
	virtual void DndDrawMoveRect(CGXGridCore* pGrid, CPoint point, BOOL bEraseOld, BOOL bDrawNew) = 0;
	virtual BOOL DoDragScroll(CGXGridCore* pGrid, CPoint point) = 0;
	virtual BOOL IsOverAnotherApplication(CGXGridCore* pGrid, POINT point) = 0;
};

#endif // _AFX_NO_OLE_SUPPORT

/////////////////////////////////////////////////////////////////////////////
// CGXNoToolTipCtrlProxy
//
// This abstract base class helps to call functions from CToolTipCtrl
// without having to statically link in tooltip code if the functionality
// is not wished.

class CGXNoToolTipCtrlProxy
{
public:
	GRID_API virtual ~CGXNoToolTipCtrlProxy();

	// Will be called from CGXGridCore::OnGridPreTranslateMessage
	virtual void RelayEvent(LPMSG lpMsg) = 0;

	// Will be called from CGXGridCore::DoMouseMove
	virtual BOOL OnMouseMove(UINT flags, CPoint pt) = 0;

	// Will be called from CGXGridCore::DoSize
	virtual void UpdateTipArea() = 0;

	// Reset tips 
	virtual void Reset() = 0;

	// Will be called from OnInitialUpdate
	virtual BOOL InitToolTip() = 0;
};


/////////////////////////////////////////////////////////////////////////////
// Sorting the grid

class CGXGridCore;
class CGXControl;
struct CGXSortInfo;
class CGXSortInfoArray;
class CGXRange;

class CGXAbstractGridSortImp
{
public:
	// General
	virtual void SortKeys(CGXGridCore* pGrid, const CGXSortInfoArray& sortInfo, CPtrArray& sortKeyArray) = 0;

	// Rows
	virtual void SortRows(CGXGridCore* pGrid, CGXRange& sortRange, CGXSortInfoArray& sortInfo, UINT flags) = 0;
	virtual BOOL MoveDataRows(CGXGridCore* pGrid, const CGXRange& sortRange, const CRowColArray& awRowIndex, UINT flags, GXCmdType ctCmd) = 0;
	virtual BOOL StoreMoveDataRows(CGXGridCore* pGrid, const CGXRange& sortRange, const CRowColArray& awRowIndex) = 0;
	virtual void UpdateMoveDataRows(CGXGridCore* pGrid, const CGXRange& sortRange, UINT flags, BOOL bCreateHint) = 0;
	virtual void OnGetSortRowsKey(CGXGridCore* pGrid, ROWCOL nRow, const CGXSortInfoArray& sortInfo, CStringArray& keys) = 0;

	// Columns
	virtual void SortCols(CGXGridCore* pGrid, CGXRange& sortRange, CGXSortInfoArray& sortInfo, UINT flags) = 0;
	virtual BOOL MoveDataCols(CGXGridCore* pGrid, const CGXRange& sortRange, const CRowColArray& awColIndex, UINT flags, GXCmdType ctCmd) = 0;
	virtual BOOL StoreMoveDataCols(CGXGridCore* pGrid, const CGXRange& sortRange, const CRowColArray& awColIndex) = 0;
	virtual void UpdateMoveDataCols(CGXGridCore* pGrid, const CGXRange& sortRange, UINT flags, BOOL bCreateHint) = 0;
	virtual void OnGetSortColsKey(CGXGridCore* pGrid, ROWCOL nCol, const CGXSortInfoArray& sortInfo, CStringArray& keys) = 0;

	// Dbl Click on header
	virtual BOOL OnLButtonDblClkRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt) = 0;
};

class CGXData;

class CGXAbstractGridSortMoveDataImp
{
public:
	virtual BOOL StoreMoveDataRows(CGXData* pData, const CGXRange& sortRange, const CRowColArray& anRowIndex) = 0;
	virtual BOOL StoreMoveDataCols(CGXData* pData, const CGXRange& sortRange, const CRowColArray& anColIndex) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// CalcSize (needed by floating cells and resize to fit)

class CGXAbstractCalcSizeImp
{
public:
	virtual CSize CalcSize(CGXControl* pControl, CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// IsSubset (needed by merge cells and toolbar items in mygridvw, e.g. bold. italic etc.)

class CGXAbstractStyleCompareSubsetImp
{
public:
	virtual BOOL IsSubset(const CGXStyle* pStyle, const CGXStyle& p) = 0;
};


/////////////////////////////////////////////////////////////////////////////
// Floating Cells

class CGXSpanCellPool;
class CGXRange;
class CGXGridCore;
class CGXStyle;

class CGXAbstractGridFloatCellsImp
{
public:
	virtual void SetFloatCellsMode(CGXGridCore* pGrid, WORD nMode, BOOL bRedraw) = 0;
	virtual void DelayFloatCells(CGXGridCore* pGrid, const CGXRange& range, ROWCOL nMaxCols) = 0;
	virtual BOOL EvalFloatCells(CGXGridCore* pGrid, const CGXRange& range, BOOL bUpdate, CGXRange* prgBoundary, BOOL bLookupStyle) = 0;
	virtual CGXRange* GetFloatedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXRange& range) = 0;
	virtual BOOL CanFloatCell(CGXGridCore* pGrid, CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood) = 0;
	virtual BOOL SetFloatedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags) = 0;
	virtual void UpdateFloatedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags, BOOL bCreateHint) = 0;
	virtual void MergeFloatedCells(CGXGridCore* pGrid, CGXRange& range) = 0;
	virtual BOOL CanFloatCell(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood) = 0;
};

class CGXAbstractSpanCellPoolImp
{
public:
	virtual CGXSpanCellPool* CreateSpanCellPool() = 0;
	virtual CGXSpanCellPool* CreateSpanCellPool(const CGXSpanCellPool& src) = 0;
	virtual void CopySpanCellPool(CGXSpanCellPool& dest, const CGXSpanCellPool& src) = 0;
	virtual void InsertRows(CGXSpanCellPool* pPool, ROWCOL nRow, ROWCOL nCount) = 0;
	virtual void RemoveRows(CGXSpanCellPool* pPool, ROWCOL nFromRow, ROWCOL nToRow) = 0;
	virtual void MoveRows(CGXSpanCellPool* pPool, ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow) = 0;
	virtual void InsertCols(CGXSpanCellPool* pPool, ROWCOL nCol, ROWCOL nCount) = 0;
	virtual void RemoveCols(CGXSpanCellPool* pPool, ROWCOL nFromCol, ROWCOL nToCol) = 0;
	virtual void MoveCols(CGXSpanCellPool* pPool, ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol) = 0;
};

class CGXDelayedRangePool;

class CGXAbstractDelayedRangePoolImp
{
public:
	virtual CGXDelayedRangePool* CreateDelayedRangePool() = 0;
	virtual CGXDelayedRangePool* CreateDelayedRangePool(const CGXDelayedRangePool& src) = 0;
	virtual void CopyDelayedRangePool(CGXDelayedRangePool& dest, const CGXDelayedRangePool& src) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Covered Cells

class CGXCoveredCellPool;
class CGXRangeList;

class CGXAbstractGridCoveredCellsImp
{
public:
	virtual BOOL SetCoveredCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags, GXCmdType ctCmd) = 0;
	virtual CGXRange* GetCoveredCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXRange& range) = 0;
	virtual BOOL StoreCoveredCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, BOOL bSet) = 0;
	virtual void UpdateCoveredCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags, BOOL bCreateHint) = 0;
	virtual void MergeCoveredCells(CGXGridCore* pGrid, CGXRange& range) = 0;
	virtual BOOL RemoveRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, UINT& flags, GXCmdType ctCmd) = 0;
	virtual BOOL RemoveCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, UINT& flags, GXCmdType ctCmd) = 0;
};

class CGXAbstractCoveredCellPoolImp
{
public:
	virtual CGXCoveredCellPool* CreateCoveredCellPool() = 0;
	virtual void InitFromRangeList(CGXCoveredCellPool*, CGXRangeList&) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Merge Cells

class CGXAbstractGridMergeCellsImp
{
public:
	virtual void SetMergeCellsMode(CGXGridCore* pGrid, WORD nMode, BOOL bRedraw) = 0;
	virtual void DelayMergeCells(CGXGridCore* pGrid, const CGXRange& range, ROWCOL nMaxRows, ROWCOL nMaxCols) = 0;
	virtual BOOL EvalMergeCells(CGXGridCore* pGrid, const CGXRange& range, BOOL bUpdate, CGXRange* prgBoundary, BOOL bLookupStyle) = 0;
	virtual CGXRange* GetMergedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXRange& range, int mtType) = 0;
	virtual BOOL CanMergeCell(CGXGridCore* pGrid, CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, int mtType) = 0;
	virtual BOOL CanMergeCells(CGXGridCore* pGrid, const CGXStyle& style1, const CGXStyle& style2) = 0;
	virtual BOOL SetMergedCellsRowCol(CGXGridCore* pGrid, int mtType, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags) = 0;
	virtual void UpdateMergedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags, BOOL bCreateHint) = 0;
	virtual void MergeMergedCells(CGXGridCore* pGrid, CGXRange& range) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Drawing for covered, merhe and floating Cells

class CGXAbstractDrawSpannedCellsImp
{
public:
	virtual BOOL OnDrawTLBR_LoadCell(CGXGridCore* pGrid, void* pds, unsigned nRow, unsigned nCol) = 0;
	virtual BOOL OnDrawTLBR_DrawCell(CGXGridCore* pGrid, void* pds, unsigned nRow, unsigned nCol) = 0;
	virtual BOOL EvalVisibleFloatMergeCells(CGXGridCore* pGrid, const CGXRange& range, ROWCOL nfr, ROWCOL nfc, ROWCOL nTopRow, ROWCOL nLefCol, ROWCOL nLastRow, ROWCOL nLastCol, BOOL bUpdate, CGXRange* prgBoundary, BOOL bLookupStyle) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Find&Replace

class CFindReplaceDialog;

struct GX_FR_STATE;

class CGXAbstractGridFindReplaceImp
{
public:
	virtual void OnShowFindReplaceDialog(CGXGridCore* pGrid, BOOL bFindOnly) = 0;
	virtual void OnFindNext(CGXGridCore * pGrid, LPCTSTR lpszFind, BOOL bNext, BOOL bCase) = 0;
	virtual BOOL FindText(CGXGridCore* pGrid, BOOL bSetCell) = 0;
	virtual void OnReplaceSel(CGXGridCore* pGrid, LPCTSTR lpszFind, BOOL bNext, BOOL bCase, LPCTSTR lpszReplace) = 0;
	virtual void OnReplaceAll(CGXGridCore* pGrid, LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase) = 0;
	virtual void OnFindReplace(CGXGridCore* pGrid, CFindReplaceDialog* pDialog) = 0;
	virtual BOOL FindText(CGXGridCore* pGrid, ROWCOL& nRow, ROWCOL& nCol, BOOL bSetCell) = 0;
	virtual BOOL FindText(CGXControl* pControl, const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell) = 0;
	virtual BOOL ReplaceAll(CGXControl* pControl, const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol) = 0;
};


//////////////////////////////////////////////////////////////////////////////
// Printing

class CGXGridParam;
class CGXProperties;
class CGXData;

class CGXAbstractGridPrintImp
{
public:
	virtual void OnGridBeginPrinting(CGXGridCore* pGrid, CDC* pDC, CPrintInfo* pInfo) = 0;
	virtual void OnGridPrint(CGXGridCore* pGrid, CDC* pDC, CPrintInfo* pInfo) = 0;
	virtual void OnGridEndPrinting(CGXGridCore* pGrid, CDC* pDC, CPrintInfo* pInfo) = 0;

	virtual void OnPrintHeaderAndFooter(CGXProperties* pProp, CDC* pDC, CPrintInfo* pInfo, CDocument* pDoc, CGXGridParam* pParam) = 0;
	virtual int CalculateHeight(CGXProperties* pProp, CDC* pDC, CGXData &data, CGXStylesMap* pStylesMap) = 0;
	virtual void PrintHeaderFooter(CGXProperties* pProp, CDC* pDC, CPrintInfo* pInfo, CRect& rect, CGXData& data, CGXStylesMap* pStylesMap) = 0;
	virtual CString ParseText(CGXProperties* pProp, LPCTSTR sz) = 0;
	virtual CString SubstTokenText(CGXProperties* pProp, int nToken, CString& sRest) = 0;
	virtual CString GetTokenArgs(CGXProperties* pProp, CString& sRest) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Old Drawing (with clipping)
// Ole drawing might be necessary if you have custom cell types that don't 
// take care on clipping themselves in Draw method.
// - Or -
// If you are using the CGXGridParam::m_bTransparentBackground setting


class CGXAbstractGridOldDrawingImp
{
public:
	virtual BOOL OnDrawTLBR(CGXGridCore* pGrid, CDC* pDC, void* pds) = 0;
	virtual void OnDrawTLBR_DrawBackground(CGXGridCore* pGrid, void* pds) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Update hint Mechanism

class CGXAbstractGridUpdateHintImp
{
public:
	virtual void OnGridUpdate(CGXGridCore * pGrid, CObject* pHint) = 0;
	virtual void HintUpdateReadOnly(CGXGridCore* pGrid, BOOL bOldReadOnly) = 0;
	virtual void HintSetCurrentCell(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, UINT flags) = 0;
	virtual BOOL HintTransferCurrentCell(CGXGridCore* pGrid, BOOL bSaveAndValidate, UINT flags) = 0;
	virtual void HintUpdateChangedRowCount(CGXGridCore* pGrid, ROWCOL nOldRows, UINT flags) = 0;
	virtual void HintUpdateChangedColCount(CGXGridCore* pGrid, ROWCOL nOldCols, UINT flags) = 0;
	virtual void HintUpdateFrozenCols(CGXGridCore* pGrid, ROWCOL nOldFrozenCols, ROWCOL nOldHeaderCols, UINT flags) = 0;
	virtual void HintUpdateFrozenRows(CGXGridCore* pGrid, ROWCOL nOldFrozenRows, ROWCOL nOldHeaderRows, UINT flags) = 0;
	virtual void HintSetTopRow(CGXGridCore* pGrid, ROWCOL nRow, UINT flags) = 0;
	virtual void HintSetLeftCol(CGXGridCore* pGrid, ROWCOL nCol, UINT flags) = 0;
	virtual void HintUpdateInsertRows(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCount, UINT flags) = 0;
	virtual void HintUpdateInsertCols(CGXGridCore* pGrid, ROWCOL nCol, ROWCOL nCount, UINT flags) = 0;
	virtual void HintRedrawRowCol(CGXGridCore* pGrid, ROWCOL nStartRow, ROWCOL nStartCol, ROWCOL nEndRow, ROWCOL nEndCol, UINT flags) = 0;
	virtual void HintRedraw(CGXGridCore* pGrid, UINT flags) = 0;
	virtual void HintRefreshViews(CGXGridCore* pGrid, CString* pErrorStr) = 0;
	virtual void HintOnTabChanged(CGXGridCore* pGrid, int nTab) = 0;
	virtual void HintOnAutoScroll(CGXGridCore* pGrid, int direction, ROWCOL nCell) = 0;
	virtual void HintUpdateSelectRange(CGXGridCore* pGrid, const CGXRange& range, const CGXRangeList* pOldRangeList) = 0;
	virtual void HintLockSelectionFrame(CGXGridCore* pGrid, BOOL bLock) = 0;
	virtual void HintPrepareChangeSelection(CGXGridCore* pGrid, POSITION oldPos, ROWCOL top, ROWCOL left, ROWCOL bottom, ROWCOL right) = 0;
	virtual void HintPrepareClearSelection(CGXGridCore* pGrid) = 0;
	virtual void HintUpdateChangedRowHeights(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, int* nOldHeights, UINT flags) = 0;
	virtual void HintUpdateChangedColWidths(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, int* nOldWidths, UINT flags) = 0;
	virtual void HintStoreZoom(CGXGridCore* pGrid, int nZoom) = 0;
	virtual void HintUpdateZoom(CGXGridCore* pGrid, int nOldZoom, UINT flags) = 0;
	virtual void HintUpdateStyleRange(CGXGridCore* pGrid, const CGXRange& range, const CGXStyle* pStyle, GXModifyType mt, int nType, UINT flags) = 0;
	virtual void HintUpdateStylesMap(CGXGridCore* pGrid, UINT flags) = 0;
	virtual void HintUpdateProperties(CGXGridCore* pGrid, UINT flags) = 0;
	virtual void HintUpdateBaseStyle(CGXGridCore* pGrid, WORD wStyleId, UINT flags) = 0;
	virtual void HintUpdateCoveredCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags) = 0;
	virtual void HintUpdateFloatedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags) = 0;
	virtual void HintUpdateMergedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags) = 0;
	virtual void HintUpdateMoveDataRows(CGXGridCore* pGrid, const CGXRange& sortRange, UINT flags) = 0;
	virtual void HintUpdateMoveDataCols(CGXGridCore* pGrid, const CGXRange& sortRange, UINT flags) = 0;
	virtual void HintUpdateRemoveRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, int* anOldHeights, UINT flags) = 0;
	virtual void HintUpdateRemoveCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, int* anOldWidths, UINT flags) = 0;
	virtual void HintUpdateMoveRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, UINT flags) = 0;
	virtual void HintUpdateMoveCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, UINT flags) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Resize cells to fit contents

class CGXAbstractGridResizeToFitImp
{
public:
	virtual BOOL ResizeRowHeightsToFit(CGXGridCore* pGrid, CGXRange& range, BOOL bResizeCoveredCells, UINT nFlags) = 0;
	virtual BOOL ResizeColWidthsToFit(CGXGridCore* pGrid, CGXRange& range, BOOL bResizeCoveredCells, UINT nFlags) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Printer settings (landscape, portrait, paper format etc.)

class CGXPrintDevice;

class CGXAbstractPrintDeviceImp
{
public:
	virtual void UpdatePrinterDevice(CGXPrintDevice* pd) = 0;
	virtual int DoPrintDialog(CGXPrintDevice* pDevice, CPrintDialog* pPD) = 0;
	virtual BOOL DoPreparePrinting(CView* pView, CGXPrintDevice* pDevice, CPrintInfo* pInfo) = 0;
	virtual void CreateDeviceHandles(CGXPrintDevice* pDevice, LPDEVNAMES pDevNames, DWORD cbSizeDevNames, LPDEVMODE pDevMode, DWORD cbSizeDevMode) = 0;
	virtual void CreateDeviceHandles(CGXPrintDevice* pDevice, HGLOBAL hDN, HGLOBAL hDM) = 0;
	virtual void DestroyDeviceHandles(CGXPrintDevice* pDevice) = 0;
	virtual void GetDeviceInfo(CGXPrintDevice* pDevice, HGLOBAL hDN, HGLOBAL hDM, LPDEVNAMES& pDevNames, DWORD &cbSizeDevNames, LPDEVMODE& pDevMode, DWORD& cbSizeDevMode) = 0;
	virtual void GetDefaults(CGXPrintDevice* pDevice) = 0;
	virtual HDC GetPrintDC(CGXPrintDevice* pDevice) = 0;
	virtual void ResetPrintDC(CGXPrintDevice* pDevice) = 0;
	virtual void CopyDeviceHandles(CGXPrintDevice* pDevice, HGLOBAL& hDN, HGLOBAL& hDM) = 0;
	virtual BOOL CompareDeviceHandles(CGXPrintDevice* pDevice, LPDEVNAMES pDevNames, DWORD cbSizeDevNames, LPDEVMODE pDevMode, DWORD cbSizeDevMode) = 0;
	virtual BOOL CompareDeviceHandles(CGXPrintDevice* pDevice, HGLOBAL hDN, HGLOBAL hDM) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Hiding cells 

class CGXAbstractGridHideCellsImp
{
public:
	virtual void RemoveRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow) = 0;
	virtual void RemoveCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol) = 0;
	virtual void InsertRows(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCount) = 0;
	virtual void InsertCols(CGXGridCore* pGrid, ROWCOL nCol, ROWCOL nCount) = 0;
	virtual void MoveRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow) = 0;
	virtual void MoveCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol) = 0;
	virtual BOOL HideRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, BOOL bHide, BOOL* abHideArray, UINT flags, GXCmdType ctCmd) = 0;
	virtual BOOL IsRowHidden(CGXGridCore* pGrid, ROWCOL nRow) = 0;
	virtual BOOL StoreHideRow(CGXGridCore* pGrid, ROWCOL nRow, BOOL bHide) = 0;
	virtual BOOL HideCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, BOOL bHide, BOOL* abHideArray, UINT flags, GXCmdType ctCmd) = 0;
	virtual BOOL IsColHidden(CGXGridCore* pGrid, ROWCOL nCol) = 0;
	virtual BOOL StoreHideCol(CGXGridCore* pGrid, ROWCOL nCol, BOOL bHide) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Serialize style objects

struct CGXPen;
struct CGXBrush;
class CGXFont;
class CGXStyle;

class CGXAbstractStyleSerializeImp
{
public:
	virtual void Serialize(CGXStyle* pStyle, CArchive& ar, const CGXStylesMap* pStylesMap) = 0;
	virtual void Serialize(CGXPen& lp, CArchive& ar) = 0;
	virtual void Serialize(CGXBrush& lb, CArchive& ar) = 0;
	virtual void Serialize(CGXFont* pFont, CArchive &ar) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Read style objects serialized with OG 5.0 or earlier

class CGXAbstractSerializeOG5CompatibleImp
{
public:
	virtual void SerializeOG5Map(CGXStyle* pStyle, CArchive& ar) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Serialize parameter, properties, stylesmap etc.

class CGXGridParam;
class CGXProperties;
class CGXStylePtrArray;
class CGXStylePtrArrayPtrArray;
class CGXData;
class CGXStylesMap;

class CGXAbstractGridDocSerializeImp
{
public:
	virtual void Serialize(CGXGridParam* pParam, CArchive& ar) = 0;
	virtual void Serialize(CGXProperties* pProp, CArchive& ar) = 0;
	virtual void Serialize(CGXStylePtrArray* pArray, CArchive& ar) = 0;
	virtual void Serialize(CGXStylePtrArrayPtrArray* pArray, CArchive& ar) = 0;
	virtual void Serialize(CGXData* pData, CArchive& ar) = 0;
	virtual void Serialize(CGXStylesMap* pStyMap, CArchive& ar) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Write styles, property settings to/from profile/registry

class CGXAbstractGridProfileImp
{
public:
	virtual void WriteProfile(const CGXProperties* pProp) = 0;
	virtual BOOL ReadProfile(CGXProperties* pProp) = 0;
	virtual void WriteProfile(const CGXStyle* pStyle, LPCTSTR pszSection, const CGXStylesMap* pStylesMap) = 0;
	virtual BOOL ReadProfile(CGXStyle* pStyle, LPCTSTR pszSection, const CGXStylesMap* pStylesMap) = 0;
	virtual void WriteProfile(const CGXFont* pFont, LPCTSTR pszSection, LPCTSTR pszEntry) = 0;
	virtual BOOL ReadProfile(CGXFont* pFont, LPCTSTR pszSection, LPCTSTR pszEntry) = 0;
	virtual BOOL ReadProfile(CGXStylesMap* pStyMap) = 0;
	virtual void WriteProfile(const CGXStylesMap* pStyMap) = 0;
};


/////////////////////////////////////////////////////////////////////////////
// Copy parameter object (operator= support)

class CGXAbstractGridParamCopyOperatorImp
{
public:
	virtual void CopyObject(CGXProperties* pDest, const CGXProperties& p) = 0;
	virtual void CopyObject(CGXStylesMap* pDest, const CGXStylesMap& p) = 0;
	virtual void CopyObject(CGXGridParam* pDest, const CGXGridParam& p) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Allow user to select range of cells in grid with mouse

class CGXAbstractGridUserSelectRangeImp
{
public:
	virtual BOOL MoveCurrentCellEx(CGXGridCore* pGrid, int direction, UINT nCell) = 0;
	virtual void OnLButtonDown(CGXGridCore* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol) = 0;
	virtual BOOL OnMouseMove(CGXGridCore* pGrid, CPoint& point, UINT& flags, ROWCOL& nRow, ROWCOL& nCol) = 0;
	virtual void OnLButtonUp(CGXGridCore* pGrid, CPoint& point, UINT& flags) = 0;
	virtual void SelectRange(CGXGridCore* pGrid, const CGXRange& range, BOOL bSelect /* = TRUE */, BOOL bUpdate ) = 0;
	virtual BOOL StoreSelectRange(CGXGridCore* pGrid, const CGXRange& range, BOOL bSelect) = 0;
	virtual void UpdateSelectRange(CGXGridCore* pGrid, const CGXRange& range, const CGXRangeList* pOldRangeList, BOOL bCreateHint) = 0;
	virtual void SetSelection(CGXGridCore* pGrid, POSITION pos, ROWCOL nTop, ROWCOL nLeft, ROWCOL nBottom, ROWCOL nRight) = 0;
	virtual void PrepareChangeSelection(CGXGridCore* pGrid, POSITION oldPos, ROWCOL top, ROWCOL left, ROWCOL bottom, ROWCOL right, BOOL bCreateHint) = 0;
	virtual void PrepareClearSelection(CGXGridCore* pGrid, BOOL bCreateHint) = 0;
	virtual BOOL OnLButtonClickedRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Excel-like selection frame

class CGXAbstractGridExcelLikeFrameImp
{
public:
	virtual void DrawInvertFrame(CGXGridCore* pGrid, CDC* pDC, const CRect& rc, const CRect& rectClip, BOOL bTopVisible, BOOL bLeftVisible, int nMarker, BOOL bOnlyMarker) = 0;
	virtual void DrawSelectionRangeFrame(CGXGridCore* pGrid, CDC* pDC, const CGXRange& rg, int nMarker, BOOL bOnlyMarker) = 0;
	virtual void DrawSelectionFrame(CGXGridCore* pGrid, CDC* pDC, BOOL bDrawOld, const CGXRange* pNewRange) = 0;
	virtual void ToggleSelectionFrameMarker(CGXGridCore* pGrid) = 0;
	virtual BOOL LockSelectionFrame(CGXGridCore* pGrid, BOOL bLock, BOOL bCreateHint) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Drag select rows and columns (and rearrange row/column order)

class CGXAbstractGridUserDragSelectRangeImp
{
public:
	virtual BOOL OnLButtonDown(CGXGridCore* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol) = 0;
	virtual BOOL OnMouseMove(CGXGridCore* pGrid, CPoint& point, UINT& flags) = 0;
	virtual BOOL OnLButtonUp(CGXGridCore* pGrid, CPoint& point, UINT& flags) = 0;
	virtual BOOL OnSelDragStart(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol) = 0;
	virtual BOOL OnSelDragMove(CGXGridCore* pGrid, ROWCOL nRow1, ROWCOL nCol1, ROWCOL nRow, ROWCOL nCol) = 0;
	virtual BOOL OnSelDragDrop(CGXGridCore* pGrid, ROWCOL nRow1, ROWCOL nCol1, ROWCOL nRow, ROWCOL nCol) = 0;
	virtual void OnSelDragCancel(CGXGridCore* pGrid) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// rearrange row/column order API (MoveRows, MoveCols methods)

class CGXAbstractGridMoveRowsColsImp
{
public:
	virtual BOOL StoreMoveRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, BOOL bProcessed) = 0;
	virtual void UpdateMoveRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, UINT flags, BOOL bCreateHint) = 0;
	virtual BOOL StoreMoveCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, BOOL bProcessed) = 0;
	virtual void UpdateMoveCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, UINT flags, BOOL bCreateHint) = 0;
	virtual BOOL MoveRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, UINT flags, GXCmdType ctCmd) = 0;
	virtual BOOL MoveCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, UINT flags, GXCmdType ctCmd) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// allow user to resize rows or columns with mouse

class CGXAbstractGridUserResizeCellsImp
{
public:
	virtual BOOL OnMouseMove(CGXGridCore* pGrid, CPoint& point, UINT& flags) = 0;
	virtual BOOL OnLButtonDown(CGXGridCore* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol) = 0;
	virtual BOOL OnLButtonUp(CGXGridCore* pGrid, CPoint& point, UINT& flags) = 0;
	virtual BOOL OnLButtonDblClk(CGXGridCore* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol) = 0;
	virtual BOOL OnStartTracking(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, int nTrackingMode) = 0;
	virtual void OnMoveTracking(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize &size) = 0;
	virtual void OnCancelTracking(CGXGridCore* pGrid) = 0;
	virtual void OnEndTracking(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize& size) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Optimized update for inserting, removing rows and columns and for changing 
// row and column size.

class CGXAbstractGridOptimizedUpdateImp
{
public:
	virtual void UpdateInsertRows(CGXGridCore* pGrid, ROWCOL& nRow, ROWCOL& nCount, UINT& flags) = 0;
	virtual void UpdateInsertCols(CGXGridCore* pGrid, ROWCOL& nCol, ROWCOL& nCount, UINT& flags) = 0;
	virtual void UpdateRemoveRows(CGXGridCore* pGrid, ROWCOL& nFromRow, ROWCOL& nToRow, int* anOldHeights, UINT flags) = 0;
	virtual void UpdateRemoveCols(CGXGridCore* pGrid, ROWCOL& nFromCol, ROWCOL& nToCol, int* anOldWidths, UINT& flags) = 0;
	virtual void UpdateChangedRowHeights(CGXGridCore* pGrid, ROWCOL& nFromRow, ROWCOL& nToRow, int* nOldHeights, UINT& flags) = 0;
	virtual void UpdateChangedColWidths(CGXGridCore* pGrid, ROWCOL& nFromCol, ROWCOL& nToCol, int* nOldWidths, UINT& flags) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Draw rotated text in cells (CGXStyle::SetOrientation)

class CGXAbstractDrawRotatedTextImp
{
public:
	virtual int GXDrawRotatedText(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rc, UINT nFormat, LONG lfOrientation, LPRECT lpClipRect) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Date/Time parsing and formatting (OG offers concrete classes for OleDateTime
// and NoOleDateTime)

enum GXDateFormat { gxDDMMYY, gxMMDDYY, gxYYMMDD, gxDEFAULT };
typedef struct tagTIMESTAMP_STRUCT TIMESTAMP_STRUCT;

class CGXAbstractDateTimeImp
{
public:
	virtual void UpdateDateTimeSettings() = 0;
	virtual GXDateFormat GetDateFormatFromWinIni(BOOL bReload, BOOL& bCentury, TCHAR& chDateSep) = 0;
	virtual TCHAR GetTimeSeparatorFromWinIni(BOOL bReload) = 0;
	virtual BOOL ParseDateTime(struct tm* ptm, LPCTSTR szValue, GXDateFormat DateFormat) = 0;
	virtual BOOL ParseDateTime(TIMESTAMP_STRUCT* ptm, LPCTSTR szValue, GXDateFormat DateFormat) = 0;
	virtual void FormatTimeStamp(CString& strRet, const CTime* pTime) = 0;
	virtual void FormatTimeStamp(CString& strRet, const TIMESTAMP_STRUCT* pTime) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Outline row and column header for current cell

class CGXAbstractGridMarkEditHeaderImp
{
public:
	virtual void MarkEdit(CGXGridCore* pGrid, ROWCOL nEditRow, ROWCOL nEditCol, UINT direction, UINT flags) = 0;
	virtual BOOL GetMarkHeaderState(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Freeze rows and columns

class CGXAbstractGridFreezeMenuHelperImp
{
public:
	virtual BOOL CanFreezeCols(CGXGridCore* pGrid) = 0;
	virtual BOOL CanUnfreezeCols(CGXGridCore* pGrid) = 0;
	virtual void FreezeCols(CGXGridCore* pGrid) = 0;
	virtual void UnfreezeCols(CGXGridCore* pGrid) = 0;
	virtual BOOL CanFreezeRows(CGXGridCore* pGrid) = 0;
	virtual BOOL CanUnfreezeRows(CGXGridCore* pGrid) = 0;
	virtual void FreezeRows(CGXGridCore* pGrid) = 0;
	virtual void UnfreezeRows(CGXGridCore* pGrid) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Direct copying and moving of cells

class CGXAbstractDataCopyMoveCellsImp
{
public:
	virtual BOOL StoreCopyCells(CGXData* pData, CGXRange rg, ROWCOL nRow, ROWCOL nCol) = 0;
	virtual BOOL StoreMoveCells(CGXData* pData, CGXRange& rg, ROWCOL nRow, ROWCOL nCol, CObject*& pUndoInfo, BOOL bCreateUndoInfo, int ctCmd) = 0;
};

class CGXAbstractGridDirectCopyMoveCellsImp
{
public:
	virtual BOOL CopyCells(CGXGridCore* pGrid, CGXRange& rg, ROWCOL nRow, ROWCOL nCol, UINT flags) = 0;
	virtual BOOL StoreCopyCells(CGXGridCore* pGrid, CGXRange& rg, ROWCOL nRow, ROWCOL nCol) = 0;
	virtual BOOL MoveCells(CGXGridCore* pGrid, CGXRange& rg, ROWCOL nRow, ROWCOL nCol, CObject* pUndoInfo, UINT flags, GXCmdType ctCmd) = 0;
	virtual BOOL StoreMoveCells(CGXGridCore* pGrid, CGXRange& rg, ROWCOL nRow, ROWCOL nCol, CObject*& pUndoInfo, BOOL bCreateUndo, GXCmdType ctCmd) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Text data exchange (clipboard and text files)

class CGXAbstractGridTextDataExchangeImp
{
public:
	virtual BOOL CopyTextToFile(CGXGridCore* pGrid, CFile& destFile, const CGXRangeList& selList) = 0;
	virtual CString GetCopyTextRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol) = 0;
	virtual BOOL PasteTextFromBuffer(CGXGridCore* pGrid, LPCTSTR psz, DWORD size, const CGXRange& range) = 0;
	virtual BOOL PasteTextRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags, const CGXStyle* pOldStyle) = 0;
	virtual BOOL CalcBufferDimension(CGXGridCore* pGrid, LPCTSTR psz, DWORD size, ROWCOL& nRows, ROWCOL& nCols) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Style data exchange (clipboard and binary resources, files and og designer files)

class CGXAbstractGridStyleDataExchangeImp
{
public:
	virtual BOOL CopyCellsToArchive(CGXGridCore* pGrid, CArchive& ar, const CGXRangeList& selList, BOOL bLoadBaseStyles) = 0;
	virtual BOOL GetClipboardStyleRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, BOOL bLoadBaseStyles) = 0;
	virtual BOOL PasteCellsFromArchive(CGXGridCore* pGrid, CArchive& ar, const CGXRange& range, BOOL bIgnoreDiffRange) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Cut, Copy and Paste clipboard support

class CGXAbstractGridCutPasteImp
{
public:
	virtual BOOL CanCopy(CGXGridCore* pGrid) = 0;
	virtual BOOL Copy(CGXGridCore* pGrid) = 0;
	virtual BOOL CopyRange(CGXGridCore* pGrid, const CGXRangeList& selList) = 0;
	virtual BOOL CopyTextToClipboard(CGXGridCore* pGrid, const CGXRangeList& selList) = 0;
	virtual BOOL CopyCellsToClipboard(CGXGridCore* pGrid, const CGXRangeList& selList, BOOL bLoadBaseStyles) = 0;
	virtual BOOL CanCut(CGXGridCore* pGrid) = 0;
	virtual BOOL Cut(CGXGridCore* pGrid) = 0;
	virtual BOOL CutRange(CGXGridCore* pGrid, const CGXRangeList& selList, BOOL bStyleOrValue) = 0;
	virtual BOOL CanPaste(CGXGridCore* pGrid) = 0;
	virtual BOOL OnCheckClipboardFormat(CGXGridCore* pGrid) = 0;
	virtual BOOL Paste(CGXGridCore* pGrid) = 0;
	virtual BOOL OnPasteDirect(CGXGridCore* pGrid, const CGXRange& range) = 0;
	virtual BOOL OnPasteFromClipboard(CGXGridCore* pGrid, const CGXRange& rg) = 0;
	virtual BOOL OnPasteDiffRange(CGXGridCore* pGrid) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Clear cells support

class CGXAbstractGridClearCellsImp
{
public:
	virtual BOOL CanClear(CGXGridCore* pGrid) = 0;
	virtual BOOL Clear(CGXGridCore* pGrid, BOOL bStyleOrValue) = 0;
	virtual BOOL ClearCells(CGXGridCore* pGrid, const CGXRangeList& selList, BOOL bStyleOrValue) = 0;
	virtual BOOL ClearCellsAlternate(CGXGridCore* pGrid, const CGXRange& sel, BOOL bStyleOrValue) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Named Ranges (used for formula support only)

class CGXAbstractGridRangeNameImp
{
public:
	virtual BOOL SetRangeName(CGXGridCore* pGrid, LPCTSTR name, const CGXRange& rg, CObject* pUndoInfo, UINT flags, GXCmdType ctCmd) = 0;
	virtual BOOL GetRangeName(CGXGridCore* pGrid, LPCTSTR name, CGXRange& rg) = 0;
	virtual BOOL DeleteRangeName(CGXGridCore* pGrid, LPCTSTR name, CObject* pUndoInfo, GXCmdType ctCmd) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// CGXLongOperation support

class CGXAbstractLongOperationImp
{
public:
	virtual void Start(CGXLongOperation* pTheOp) = 0;
	virtual void Stop(CGXLongOperation* pTheOp) = 0;
	virtual void FreeStatusText(CGXLongOperation* pTheOp) = 0;
	virtual void SetStatusText(CGXLongOperation* pTheOp, LPCTSTR pszText, BOOL bCopyBuffer) = 0;
	virtual BOOL DoMessages(CGXLongOperation* pTheOp) = 0;
	virtual BOOL DoMessages(CGXLongOperation* pTheOp, BOOL& bAbort) = 0;
	virtual void ProcessMessages(CGXLongOperation* pTheOp) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Number formatting support for numeric cells

class CGXAbstractNumberFormattingImp
{
public:
	// Text formatting and parsing
	virtual CString GXFormatText(const CGXStyle& style, LPCTSTR pszValue, unsigned nValueType, CGXGridCore* pGrid, CGXControl* pControl) = 0;
	virtual BOOL GXDeval(LPCTSTR s, double *d, unsigned* pImportFormat, unsigned* pImportPlaces) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Excel like fill implementation

class CGXAbstractGridExcelLikeFillImp
{
public:
	virtual void OnLButtonDown(CGXGridCore* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol) = 0;
	virtual BOOL OnMouseMove(CGXGridCore* pGrid, CPoint& point, UINT& flags, ROWCOL& nRow, ROWCOL& nCol) = 0;
	virtual void OnLButtonUp(CGXGridCore* pGrid, CPoint& point, UINT& flags) = 0;
	virtual void ClearCurrentDragRect(CGXGridCore* pGrid) = 0;
	virtual void DrawDragRect(CGXGridCore* pGrid, CGXRange& rect, BOOL bEraseOld, BOOL bDrawNew) = 0;
	virtual void FillRect(CGXGridCore* pGrid, CGXRange& nFrom, CGXRange& nTo) = 0;
	virtual void OnAutoFillDone(CGXGridCore* pGrid, CGXRange& rFinal) = 0;
};



/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES

// inlines

#endif

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//


#endif //_GXABSTR_H_
