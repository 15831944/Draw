///////////////////////////////////////////////////////////////////////////////
// SECMEDIT.h
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
//  Author:		Scot Wingo
//  Description:	SECMaskEdit declaration
//
//
//  CHANGELOG:
//
//     8/21/95    MSW  Started, new logic, new ui.
//     12/9/95    MSW  Added cut/copy/paste/insert mode for B5.
//
//
//
#ifndef __SECMASKEDIT_H__
#define __SECMASKEDIT_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
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

#define LITERAL_SENTINEL    128
#define LITERAL_ANY_ASCII	256

//forward declaration
class SECMaskEdit;

//SECMaskEdit DDX/DDV routines

//@doc SECMaskEdit
//@func void | DDX_Mask | SECMaskEdit DDX/DDV routine.
//@rdesc void
//@parm SECMaskEdit& | medit | A SECMaskEdit control.
//@parm CString& | value | The value to set or retrieve without literals.
//@parm CString& | raw_value  | The value used in retrieving information 
// only for getting the raw string.
//@comm Use DDX_Mask() instead of DDX_Text to transfer data to and from the subclasse edit control.
// The use of DDX_Control() is not needed because the control is subclassed in AttachEdit().
//@xref <c SECMaskEdit> <mf SECMaskEdit::AttachEdit> 
TOOLKIT_API void AFXAPI DDX_Mask(CDataExchange * pDX, SECMaskEdit &medit, CString &value, CString &raw_value);


/////////////////////////////
// AutoDuck tag block block for SECMaskEdit 

//@doc SECMaskEdit
//@mfunc virtual TCHAR  | SECMaskEdit | GetPromptChar | Retrieves the 
// current prompt character.
//@comm At runtime, the mask characters are replaced with the prompt 
// character which is a space by default.  The prompt character can be 
// changed via the <mf SECMaskEdit::SetPromptChar> member function.
//@rdesc The current prompt character.
//@xref <c SECMaskEdit> <mf SECMaskEdit::SetPromptChar>

//@doc SECMaskEdit
//@mfunc virtual CString&  | SECMaskEdit | GetRawData | Retrieves the data 
// from the masked edit with all literal characters intact.
//@rdesc The string of the current data as displayed in the control. 
//@xref <c SECMaskEdit>

//@doc SECMaskEdit
//@mfunc virtual BOOL  | SECMaskEdit | InsertMode | Determines if the 
//control is in insert mode or not.
//@rdesc Nonzero if the control is in insert mode, otherwise 0.
//@xref <c SECMaskEdit>

//@doc SECMaskEdit
//@mfunc virtual CString&  | SECMaskEdit | SetInsertMode | Sets the insert edit mode.
//@parm BOOL | bInsert | If TRUE, sets the control to insert edit mode.
//@rdesc void
//@xref <c SECMaskEdit>

//@doc SECMaskEdit
//@mdata CString  | SECMaskEdit | m_strMask | The mask string.
//@comm See <mf SECMaskEdit::SetMask> for valid mask strings.
//@xref <c SECMaskEdit> <mf SECMaskEdit::SetMask>

//@doc SECMaskEdit
//@mdata CString  | SECMaskEdit | m_strDisplay | The displayed string.
//@xref <c SECMaskEdit> <mf SECMaskEdit::GetRawData>

//@doc SECMaskEdit
//@mdata TCHAR  | SECMaskEdit | m_chPrompt | The prompt character 
// (default=space).
//@xref <c SECMaskEdit> <mf SECMaskEdit::GetPromptChar> <mf SECMaskEdit::SetPromptChar>

//@doc SECMaskEdit
//@mdata BOOL  | SECMaskEdit | m_bKeyProcessed | Signals OnChar that a key 
// was already handled.
//@xref <c SECMaskEdit>

//@doc SECMaskEdit
//@mdata BOOL  | SECMaskEdit | m_bInsert | Insert mode flag (default=FALSE).
//@xref <c SECMaskEdit> <mf SECMaskEdit::InsertMode> 

//@doc SECMaskEdit
//@mdata CString  | SECMaskEdit | m_strUndoText | The undo buffer.
//@xref <c SECMaskEdit> <mf SECMaskEdit::CanUndo> <mf SECMaskEdit::Undo> 

//@doc SECMaskEdit
//@mdata CString  | SECMaskEdit | m_strRedoText | The redo buffer.
//@xref <c SECMaskEdit>

// adinsert AutoDuck insertion point for SECMaskEdit 
//@doc SECMaskEdit 
//@class SECMaskEdit attaches to existing CEdit controls and lets you add 
// formatted input capabilites to them.  To use SECMaskEdit, you 
// follow these steps:
//
// 1. Attach SECMaskEdit to an existing CEdit using the 
// <mf SECMaskEdit::AttachEdit> member function.<nl>
// 2. Set a mask that defines the format of the data to be entered.<nl>
// 3. Call <mf SECMaskEdit::GetData> to retrieve the data without the mask, or 
// <mf SECMaskEdit::GetRawData> to retrieve the entire contents of the 
// SECMaskEdit.
//
//@comm SECMaskEdit supports cut, copy, paste and clear.  Insert mode is also 
// supported and is toggled on/off when the user presses the ‘VK_INSERT’ key.
//
// Masks consist of ‘mask characters’ and literals.  Literals are 
// characters that appear unchanged in the mask, while mask characters 
// specify a spot in the mask edit that accepts certain characters.  
// See <mf SECMaskEdit::SetMask> for a list of valid mask characters and
// examples of popular masks.
//
// At runtime the mask characters are replaced with the prompt character 
// which is a space by default.  The prompt character can be changed 
// via the SetPromptChar() member function.
//
// NOTE: In this version of SECMaskEdit, validation is not performed on 
// the various ‘types’ of data.  For example, it is up to the 
// SECMaskEdit user to detect that 12/35/95 is an invalid date, because 
// while this data fits the requirements of the mask, it is invalid 
// for a US date format.
//
// Intelligent validation, and DDV capabilities will be added in a 
// future version of SECMaskEdit.
// 
// The SECMaskEdit class supports DDX using <f DDX_Mask>.
//
// The MASKTEST sample in the \SAMPLES\TOOLKIT\STANDARD\CONTROLS\MASKTEST directory 
// demonstrates how to use the SECMaskEdit class.
//@base public | CEdit
class SECMaskEdit : public CEdit
{
    TOOLKIT_DECLARE_DYNAMIC(SECMaskEdit);
    
public:     

	//access Creation/Initialization

	//@cmember
	/* Constructs a SECMaskEdit object.*/
    TOOLKIT_API SECMaskEdit();
    
	//@cmember
	/* Attaches the SECMaskEdit to an existing CEdit control.*/
    TOOLKIT_API BOOL AttachEdit(int nCtlID, CWnd* pParentWnd);

public:    
	
	//@access Attributes

    //@cmember
    /* Sets the input mask for the edit control.*/
    TOOLKIT_API virtual BOOL SetMask(LPCTSTR lpszMask);
    
	//@cmember
	/* Sets the prompt character.*/
    TOOLKIT_API virtual void SetPromptChar(TCHAR chNewPrompt );

	//@cmember
	/* Retrieves the current prompt character.*/
    TOOLKIT_API virtual TCHAR GetPromptChar() {return m_chPrompt;}
    
	//@cmember
	/* Puts data into the masked edit.*/
    TOOLKIT_API virtual BOOL SetData(const CString& strData, 
						int nStartPos = 0, 
						BOOL bInsert = FALSE,
						BOOL bIgnorePromptChars = TRUE);
    
	//@cmember
	/* Retrieves data from the masked edit and strips out the */
	// literals and spaces if specified.
    TOOLKIT_API virtual void GetData(CString& strData, BOOL bTrim = FALSE);

	//@cmember
	/* Retrieves the data from the masked edit with all literal */
	// characters intact.
    TOOLKIT_API virtual CString& GetRawData(void) {return m_strDisplay;}

	//@cmember
	/* Sets the insert mode */
	TOOLKIT_API virtual void SetInsertMode(BOOL bInsert = TRUE) {m_bInsert = bInsert;}

	//@cmember
	/* Determines if the edit is in insert mode or not.*/
    TOOLKIT_API virtual BOOL InsertMode() {return m_bInsert;}
    
public:

	//@access Operations

	//@cmember
	/* Clears the non-literal data from the masked edit.*/
    TOOLKIT_API void ClearData(void);

	// Undo operations
	// Since the CEdit::Undo functions are not virtual,
	// these are new implementations.

	//@cmember
	/* Determines if the last operation can be undone.*/
	TOOLKIT_API virtual BOOL CanUndo();

	//@cmember
	/* Performs an "undo" on the last operation.*/
	TOOLKIT_API virtual BOOL Undo();	

	//@cmember
	/* Clears the "undo" buffer.*/
	TOOLKIT_API virtual void EmptyUndoBuffer();
    

// Implementation
    
public:
    TOOLKIT_API virtual ~SECMaskEdit();

#ifdef _DEBUG
    BOOL m_bIsAttached;
    TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
    TOOLKIT_API virtual void AssertValid() const;
#endif

//@access Overrideables    
protected:

	//@cmember
	/* Determines if a character is valid for the specified position.*/
    TOOLKIT_API virtual BOOL IsCharValid(int nPos, TCHAR& ch);

	//@cmember
	/* Determines if a character is a literal character.*/
    TOOLKIT_API virtual BOOL IsLiteralChar(TCHAR ch);

	//@cmember
	/* Determines if a character is a mask character.*/
    TOOLKIT_API virtual BOOL IsMaskChar(TCHAR ch);
    
	//@cmember
	/* Updates the string displayed in the control based on the current mask.*/
    TOOLKIT_API virtual void UpdateDisplayStr();

	// Implementation - mask operations

	//@cmember
	/* Given a mask, returns a displayable string based on the current*/
	// prompt character.
	TOOLKIT_API virtual void ConvertMaskToDisplayStr(CString strMask,CString& strResult);

	//@cmember
	/* Parses the mask string.*/
    TOOLKIT_API virtual void ParseMaskString();

	//@cmember
	/* Locates the last filled in data position.*/
    TOOLKIT_API virtual int  FindLastFilledDataPos(int nStartPos);
    
	// Implementation - edit manipulation...    

	//@cmember
	/* Inserts a character, and optionally refreshes the display.*/
    TOOLKIT_API virtual BOOL PushChar(int nStartPos, TCHAR ch, BOOL bRefreshDisplay = TRUE);

	//@cmember
	/* Removes a range of characters.*/
    TOOLKIT_API virtual void PullChar(int nFromPos, int nToPos);

	//@cmember
	/* Sets the cursor position.*/
    TOOLKIT_API virtual int SetCursorPos(int nOldPos, int nDirection, BOOL bSelect = FALSE);

	//@cmember
	/* Retrieves the next data position relative to a given position.*/
    TOOLKIT_API virtual int GetNextDataPos(int nOldPos);

	//@cmember
	/* Retrieves the previous data position relative to a given position.*/
    TOOLKIT_API virtual int GetPrevDataPos(int nOldPos);

	// Implementation - redrawing

	//@cmember
	/* Redraws the control.*/
    TOOLKIT_API virtual void UpdateDisplay();

	//@access Overrides
	
	// Called when a nonsystem key is pressed.
    TOOLKIT_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	// Called when a keystroke translates to a nonsystem character. 
    TOOLKIT_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	// Called when the user presses the left mouse button.
    TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	// Called when a copy operation occurs.
    TOOLKIT_API afx_msg LRESULT OnCopy(WPARAM, LPARAM);
	
	// Called when a paste operation occurs.
    TOOLKIT_API afx_msg LRESULT OnPaste(WPARAM, LPARAM);
	
	// Called when a cut operation occurs.
    TOOLKIT_API afx_msg LRESULT OnCut(WPARAM,LPARAM);
	
	// Called when a clear operation occurs.
    TOOLKIT_API afx_msg LRESULT OnClear(WPARAM,LPARAM);

	// Called when the control receive the input focus.
	TOOLKIT_API afx_msg void OnSetFocus(CWnd* pOldWnd);

protected:

	//@access Protected data members

	//@cmember
	/* The mask string.*/
    CString m_strMask;

	//@cmember
	/* The displayed string.*/
    CString m_strDisplay;

	//@cmember
	/* The prompt character (default = space)*/
    TCHAR m_chPrompt;

	// Set by OnKeyDown...
	//@cmember
	/* Signals OnChar that a key was already handled.*/
    BOOL m_bKeyProcessed;     

	//@cmember
	/* Insert mode flag (default = overwrite).*/
    BOOL m_bInsert;

	//@cmember
	/* The undo buffer.*/
	CString m_strUndoText;

	//@cmember
	/* The redo buffer.*/
	CString m_strRedoText;
    
	
	// Implementation - Message map and entries    
    TOOLKIT_DECLARE_MESSAGE_MAP();
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SECMASKEDIT_H__

