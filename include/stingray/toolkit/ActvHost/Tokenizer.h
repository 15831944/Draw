///////////////////////////////////////////////////////////////////////////////
// Tokenizer.h
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
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef  _TOKENIZER_H_
#define  _TOKENIZER_H_

#include "toolkit\ActvHost\constants.h"
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

/////////////////////// start namespace SECActiveScript
namespace SECActiveScript{
	enum KEYWORDS
	{
	   NONUSER_KEYWORDS = 3000,

	// operators
	//----------
	   L_BRACE, R_BRACE, L_CURLY, R_CURLY, L_PAREN, R_PAREN, COLON, SEMI, COMMA,
	   AMP, MOD, GT, GE, LT, LE, NOTEQ, EQEQ, PLUS, MINUS, PLUSPLUS, MINUSMINUS,
	   DIV, MULT, NOTSYMBOL, QUOTE, ASSIGN, DOT, EOI,

	// others
	//-------
	   NEWLINE, CHAR_CONSTANT, DOUBLE_CONSTANT, INT_CONSTANT, IDENTIFIER,
	   COMMENT, SPACES, STRING, DEFAULTTEXT, RELOP, SIGN, INTEGER, CONSTANT,
	   UNARY_MINUS, FAILED2, PROCEED2, CUT2, GAP, DO_AND_UNDO, PROVIDED,
	   VARIABLE, PROCEDURE, SUBARRAY, PROc
	};



	#define  CURRENTWORDLENGTH    160

	// class SECAUndoEdit manages undoing editing operetions
	/////////////////////////////////////////////////////

	#define  MAXUNDOCOUNT      100
	#define  TABSIZE           4
	#define  SPACE             ' '
	#define  BUFFER_INCREMENT  4096

	// operation codes
	//----------------
	#define  INSERT               1
	#define  DEL                  2

	// OVERWRITE acts the same way as DEL does with the only difference
	// that immidiately after OVERWRITE we do one more undo step that is
	// supposed to be INSERT
	//------------------------------------------------------------------
	#define  OVERWRITE            3
} /////////////////////// end namespace SECActiveScript


typedef struct tagUndo
{
   int   nOperCode;     // operation code
   int   nStartPos;     // first affected character
   int   nEndPos;       // first unaffected character
   TCHAR *pszData;      // pointer to text data
}  UndoItem;


class TOOLKIT_API SECAUndoEdit : public CPtrArray
{
public:
   SECAUndoEdit() { p = NULL; m_bCanRestore = TRUE; m_bUndoEnabled = TRUE; }
   ~SECAUndoEdit();

   BOOL  CanUndo( void ) const;
   BOOL  CanRestore( void ) const;
   void  Push( UndoItem & );
   void  Push( int, int, int, const TCHAR * = NULL );
   const UndoItem * Pop( void );
   void  RemoveAll( void );
   void  SetCanRestore( BOOL = TRUE );
   void  EnableUndo( BOOL = TRUE );
   BOOL  IsUndoEnabled( void ) const;

protected:
   UndoItem * p;
   BOOL       m_bCanRestore; // if some operation are lost because of low
                             // memory or exceeding MAXUNDOCOUNT this
                             // member is FALSE
   BOOL       m_bUndoEnabled;
};

// SECATokenizer class represents main text buffer
////////////////////////////////////////////
class TOOLKIT_API SECATokenizer
{
protected:
   BOOL         m_bInStarComment;
   BOOL         m_bInString;
   TCHAR        *m_pszBuffer;
   CString      m_syytext;
   TCHAR        *m_pcpsca;
   int          m_nCurrToken;   
   int          m_nTextLen;
   int          m_nSize;
   int          m_nCurrWordOffs;
   BOOL         m_bModified;
   CDWordArray  m_Lines;
   SECAUndoEdit    m_undo;
   BOOL		    m_fCaseSensative;
   CStringArray m_KeywordsArray;

// we keep track about current "insertion" point and selection in the
// source text buffer to help with scrolling, selecting text, and
// working with the clipboard
//-------------------------------------------------------------------
   int         m_nStartSel;   // the first selected character
   int         m_nEndSel;     // the first unselected character past the end
                              // of the current selection
   int         m_nCaretOffs;
   int         m_nCaretLine;
   int         m_nCaretInLinePos;
   int         m_nObjectStatus;

protected:  // functions
   int         yylex( void );
   int         GetNumericConstant( void );

public:
   SECATokenizer();
   SECATokenizer( const TCHAR * );
   ~SECATokenizer();

   int		   AddKeyword(const TCHAR *keywd);// returns id of the keyword
   int		   IsKeyword( const TCHAR *token);// -1 if not a keyword
   int         GetObjectStatus( void );      // gets current object's condition
   void        ResetScaner( void );          // completely empties the object
   int         LoadText( const TCHAR *, int );// load new source to process
   BOOL        StartScanFromLine( int );     // move scaner to specified line
   void        StartScanFromBegin( void );   // start scan from the beginning
   void        Advance( void );              // advance to the next token
   const TCHAR * GetCurrWord( void ) const;  // get character representation
                                             // of the current token
   int         GetCurrWordOffs( void );      // returns offset of the current
                                             // word from the beginning of the
                                             // text buffer
   int         GetCurrToken( void ) const;   // get current token
   int         GetCurrLineNum( void ) const; // get current line number
   int         GetLineLen( int = -1 ) const; // get the length in characters of
                                             // a line at the specified index
   int         GetNumbOfLines( void ) const; // get number of lines in source
   TCHAR       GetChar( int = -1 ) const;
   TCHAR       GetChar( int, int ) const;
   int         TokenFromChar( int = -1 );
   int         TokenFromChar( int, int );
   int         SetLastToken( int );
   DWORD       GetCurrSel( void ) const;
   void        GetCurrSel( int &, int & ) const;
   int         MovePointByOneChar( BOOL = TRUE, BOOL = FALSE );
   int         MovePointByOneLine( BOOL = TRUE, BOOL = FALSE );
   int         MovePointByOneWord( BOOL = TRUE, BOOL = FALSE );
   int         SetPointOffset( int, BOOL = FALSE );
   int         SetPointOnEnd( BOOL = FALSE );
   int         SetPoint( int, int, BOOL = FALSE );
   int         SetPointOnLine( int, BOOL = FALSE );
   int         SetPointOnLineEnd( int, BOOL = FALSE );
   BOOL        GetSelText( CString & ) const;
   void        CloseCurrSel( void );
   void        GetPointPos( int &, int & ) const;
   int         GetPointPos( void ) const;
   int         GetLineIndex( int = -1 ) const;
   int         GetLineToPoint( CString & ) const;
   int         GetLine( CString &, int = -1 ) const;
   int         GetLine( TCHAR *, int, int = -1 ) const;
   int         GetTextLength( void ) const;
   int         LineFromChar( int = -1 );
   int         IndexFromInLinePos( int, int );
   const TCHAR * GetText( void );
   BOOL        GetModify( void );
   void        SetModify( BOOL = TRUE );
   int         GetCaretWord( TCHAR *, BOOL = FALSE );
   BOOL        FindString( const TCHAR *, BOOL, BOOL, int &, int & );

// editing stuff
//--------------
   void        BackTab( void );
   BOOL        InsertChar( TCHAR, BOOL = TRUE );
   BOOL        OverwriteChar( TCHAR, BOOL = TRUE );
   void        DeleteChar( BOOL = TRUE );
   void        DeleteLine( int, BOOL = TRUE );
   void        DeleteMultLines( int, int, BOOL = TRUE );
   void        BackspaceChar( BOOL = TRUE );
   BOOL        InsertText( const TCHAR *, BOOL = TRUE, BOOL = TRUE );
   BOOL        RemoveSelectedText( BOOL = TRUE );
   BOOL        CanUndo( void );
   BOOL        Undo( void );
   void        SetCanRestore( BOOL = TRUE );
   void        EnableUndo( BOOL = TRUE );
   BOOL        IsUndoEnabled( void ) const;
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif
