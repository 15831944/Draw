///////////////////////////////////////////////////////////////////////////////
// ColorEditor.h
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

#ifndef  _SECA_EDITOR_H_
#define  _SECA_EDITOR_H_

#include "toolkit\ActvHost\Tokenizer.h"
#include <afxtempl.h>
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


class SECAColorEditor : public CWnd
{
protected:
   SECATokenizer    *m_pTokenizer;

   int      m_nTopMostLine;   // current line at the very top of window
   int      m_cyChar;         // character height for the current font
   int      m_nHRange;        // range of horizontal scrolling in pixels
   int      m_nHScrollPos;    // horizontal scrolling position in pixels

// editing text members
//---------------------
   int      m_nSaveCount;     // how many times the current file has been saved

// caret manipulation
//-------------------
   int      m_nCaretX;
   int      m_nCaretY;
   BOOL     m_bWeHaveCaret;
   BOOL     m_bMouseCapt;
   BOOL     m_bBadLButDown;

// managing debugging session members
/////////////////////////////////////

public:
   TOOLKIT_API SECAColorEditor( DWORD, LOGFONT *, CWnd *pParent, const CRect& rect );
   TOOLKIT_API ~SECAColorEditor();

   TOOLKIT_API BOOL Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, const RECT& rect = CFrameWnd::rectDefault, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL );

   virtual BOOL  IsReadOnly( void ) { return m_bReadOnly; }
   TOOLKIT_API void  SetClientFont( const LOGFONT *, BOOL = TRUE );
   TOOLKIT_API BOOL  LoadText( const TCHAR *, const TCHAR * );
   TOOLKIT_API void  SetItemColor( int, COLORREF, BOOL = FALSE );
   TOOLKIT_API void  SetItemBkgrnd( int, COLORREF, BOOL = FALSE );
   TOOLKIT_API void  SetColLineIndicators( void );
   TOOLKIT_API void  MoveCaretTo( int, BOOL );
   TOOLKIT_API void  MoveCaretTo( int, int, BOOL );

   TOOLKIT_API int   GetText( TCHAR *, int );    // gets the text from the internal buffer
   TOOLKIT_API TCHAR  GetChar( int = -1 );
   TOOLKIT_API TCHAR  GetChar( int, int );
   TOOLKIT_API const TCHAR * GetText( void );
   TOOLKIT_API void  GetText( CString & );
   TOOLKIT_API int   GetTextLength( void );
   TOOLKIT_API void  DeleteLine( int = -1 );

   TOOLKIT_API void  GoToLine( int, BOOL = TRUE );
   TOOLKIT_API int   LineFromChar( int = -1 ) const;
   TOOLKIT_API int   LengthOfLine( int = -1 ) const;
   TOOLKIT_API int   LineLength( int = -1 ) const;
   TOOLKIT_API int   LineIndex( int = -1 ) const;
   TOOLKIT_API int   GetLineCount( void ) const;
   TOOLKIT_API int   GetLine( CString &, int = -1 );
   TOOLKIT_API int   GetLine( TCHAR *, int, int = -1 );
   TOOLKIT_API void  SetSel( int, int, BOOL = FALSE );
   TOOLKIT_API void  ShowErrorLine( int );
   TOOLKIT_API DWORD GetSel( void ) const;
   TOOLKIT_API void  GetSel( int &, int & ) const;
   TOOLKIT_API void  Unselect( void );
   TOOLKIT_API void  MoveCurrLine( int, BOOL = TRUE );
   TOOLKIT_API void  SetSyntaxColoring( BOOL, BOOL = FALSE );
   TOOLKIT_API void  GetCaretPosition( int &, int & ) const;
   TOOLKIT_API int   GetCaretPosition( void ) const;
   TOOLKIT_API const TCHAR * GetCaretWord( BOOL = FALSE );
   TOOLKIT_API void  ShowCurrLine( void );
   TOOLKIT_API void  HideCurrLine( void );

   TOOLKIT_API BOOL  CanUndo( void );
   TOOLKIT_API void  Undo( void );
   TOOLKIT_API void  Cut( void );
   TOOLKIT_API void  Copy( void );
   TOOLKIT_API void  Paste( void );
   TOOLKIT_API void  Delete( void );
   TOOLKIT_API void  SelectAll( void );
   TOOLKIT_API BOOL  Find( const TCHAR *, BOOL = TRUE, BOOL = FALSE,
                                          BOOL = TRUE, BOOL = FALSE );
   TOOLKIT_API BOOL  Replace( const TCHAR *, BOOL = TRUE, BOOL = FALSE );
   TOOLKIT_API int   FindReplaceAll( const TCHAR *, const TCHAR *, BOOL = TRUE, BOOL = FALSE );
   TOOLKIT_API void  EnableUndo( BOOL = TRUE );
   TOOLKIT_API BOOL  IsUndoEnabled( void ) const;
        inline BOOL  IsModified( void ) const { return m_pTokenizer && m_pTokenizer->GetModify(); }
   TOOLKIT_API void SetModified(BOOL bModified = TRUE);
   
   TOOLKIT_API BOOL PreCreateWindow(CREATESTRUCT& cs);   

   TOOLKIT_API CString GetColorEditClass(); 
   TOOLKIT_API void SetColorEditClass(const CString& strColorEditClass);

   // window class name   
   CString m_strColorEditClass;

protected:  // functions
   TOOLKIT_API int   IsHiLitLine( int = -1 );
   TOOLKIT_API int   GetItemClass( int );
   TOOLKIT_API void  PositionCaret( void );
   TOOLKIT_API int   GetHTextExtent( const TCHAR *, UINT );
   TOOLKIT_API void  RestoreLines( int, int = 1 );
   TOOLKIT_API void  CorrectSelection( int, int, int, int );
   TOOLKIT_API void  KeyBoardInput( UINT, UINT, BOOL = TRUE );
   TOOLKIT_API void  DrawLines( CDC *, int, int, BOOL = FALSE );
   TOOLKIT_API void  AdjustVScrollBar( void );
   TOOLKIT_API void  AdjustHScrollBar( void );
   TOOLKIT_API void  AdjustScrollBars( void );
   TOOLKIT_API BOOL  IsSafeChar( TCHAR );

protected:  // message handlers
   TOOLKIT_API afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   TOOLKIT_API afx_msg  void  OnPaint();
   TOOLKIT_API afx_msg  void  OnClose();
   TOOLKIT_API afx_msg  void  OnVScroll( UINT, UINT, CScrollBar * );
   TOOLKIT_API afx_msg  void  OnHScroll( UINT, UINT, CScrollBar * );
   TOOLKIT_API afx_msg  void  OnSize( UINT, int, int );
#if (_MFC_VER >= 0x0800)  // Visual Studio 2005 (as of CTP August 2005)
	TOOLKIT_API afx_msg LRESULT OnNcHitTest(CPoint point);
#else
	TOOLKIT_API afx_msg UINT OnNcHitTest(CPoint point);
#endif
   TOOLKIT_API afx_msg  void  OnSetFocus( CWnd * );
   TOOLKIT_API afx_msg  void  OnKillFocus( CWnd * );
   TOOLKIT_API afx_msg  void  OnKeyDown( UINT, UINT, UINT );
   TOOLKIT_API afx_msg  void  OnLButtonDown( UINT, CPoint );
   TOOLKIT_API afx_msg  void  OnLButtonDblClk( UINT, CPoint );
   TOOLKIT_API afx_msg  void  OnMouseMove( UINT, CPoint );
   TOOLKIT_API afx_msg  void  OnLButtonUp( UINT, CPoint );
   TOOLKIT_API afx_msg  void  OnNcLButtonDblClk( UINT, CPoint );
   TOOLKIT_API afx_msg  void  OnChar( UINT, UINT, UINT );
   TOOLKIT_API afx_msg  void  OnNcDestroy();
   TOOLKIT_DECLARE_MESSAGE_MAP()

protected:
   BOOL     m_bReadOnly;
   TCHAR    m_szCurrFile[ _MAX_PATH ];
   TCHAR    m_szFoundWord[ CURRENTWORDLENGTH ]; // the last word the window
                                                // was searched for
   TCHAR    m_szReplWith[ CURRENTWORDLENGTH ];  // word used in the last
                                                // search-replace action

   COLORREF m_clrCurrColor[ SECActiveScript::ITEM_DEFTEXT + 1 ];
   COLORREF m_clrCurrBkgrnd[ SECActiveScript::ITEM_DEFTEXT + 1 ];
   COLORREF m_clrDefColor[ SECActiveScript::ITEM_DEFTEXT + 1 ];
   COLORREF m_clrDefBkgrnd[ SECActiveScript::ITEM_DEFTEXT + 1 ];

   BOOL     m_bSyntaxColor;      // TRUE if syntax coloring requested
   BOOL     m_bCanColorSyntax;   // FALSE if coloring cannot be used usually
                                 // when line is too long
   LOGFONT  m_lf;
   BOOL     m_bDown;
   BOOL     m_bCase;
   BOOL     m_bUntitled;

   TOOLKIT_API void 	AddUserColoredItems();
   TOOLKIT_API int		ClassFromUserToken( int nUserTok );
   
   CMap< int, int, int, int& > m_userItemClass;

   TOOLKIT_API void		GetTextExpandTabs( CString &strTextToInsert, const TCHAR *pClipbrdText );
   TOOLKIT_API virtual  const TCHAR * GetFileName( void ) const;
   TOOLKIT_API virtual  BOOL  IsUntitled( void ) const;

   virtual  const LOGFONT * GetCurrentFont( void ) const { return &m_lf; }
   virtual  void  SetColors( void ) { }
   virtual  COLORREF GetItemColor( int nItem ) const { return m_clrCurrColor[ nItem ]; }
   virtual  COLORREF GetItemBkgrnd( int nItem ) const { return m_clrCurrBkgrnd[ nItem ]; }
   virtual  COLORREF GetItemDefColor( int nItem ) const { return m_clrDefColor[ nItem ]; }
   virtual  COLORREF GetItemDefBkgrnd( int nItem ) const { return m_clrDefBkgrnd[ nItem ]; }
   virtual  BOOL     IsSyntaxColor( void ) const { return m_bSyntaxColor; }
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif 	// _SECA_EDITOR_H_
