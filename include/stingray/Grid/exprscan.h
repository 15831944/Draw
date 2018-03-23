///////////////////////////////////////////////////////////////////////////////
// exprscan.h: Scanner routines
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
// Portions Copyright (C) 1995-1998 X Engineering Software Systems Corp
//

#ifndef _EXPRSCAN_H_
#define _EXPRSCAN_H_

typedef enum
{
    GX_T_SEMICOLON, /* 0  */
    GX_T_COLON,/* 1  */
    GX_T_COMMA,/* 2  */
    GX_T_QMARK,/* 3  */
    GX_T_POUND,/* 4  */
    GX_T_BACKSLASH, /* 5  */
    GX_T_PLUS, /* 6  */
    GX_T_MINUS,/* 7  */
    GX_T_STAR, /* 8  */
    GX_T_SLASH,/* 9  */
    GX_T_PERCENT,   /* 10 */
    GX_T_BAR,  /* 11 */
    GX_T_CARET,/* 12 */
    GX_T_AMPERSAND, /* 13 */
    GX_T_BANG, /* 14 */
    GX_T_TILDE,/* 15 */
    GX_T_LANGLE,    /* 16 */
    GX_T_RANGLE,    /* 17 */
    GX_T_LPAREN,    /* 18 */
    GX_T_RPAREN,    /* 19 */
    GX_T_LBRACE,    /* 20 */
    GX_T_RBRACE,    /* 21 */
    GX_T_EQUAL,/* 22 */
    GX_T_D_STAR,    /* 23 */
    GX_T_D_AMPERSAND,   /* 24 */
    GX_T_D_BAR,/* 25 */
    GX_T_D_LANGLE,  /* 26 */
    GX_T_D_RANGLE,  /* 27 */
    GX_T_LANGLE_EQUAL,  /* 28 */
    GX_T_RANGLE_EQUAL,  /* 29 */
    GX_T_BANG_EQUAL,    /* 30 */
    GX_T_EQUAL_EQUAL,   /* 31 */
    GX_T_DOT_DOT,   /* 32 */
    GX_T_CELL, /* 33 */
    GX_T_NAME, /* 34 */
    GX_T_FUNCTION,  /* 35 */
    GX_T_STRING,    /* 36 */
    GX_T_NUMBER,    /* 37 */
    GX_T_HEX_NUMBER,    /* 38 */
    GX_T_COMMENT,   /* 39 */
    GX_T_END_OF_EXPR,   /* 40 */
    GX_T_ERROR,/* 41 */
    GX_T_DOT,  /* 42 */
    GX_T_D_QMARK    /* 43 */
} TokType;

typedef struct
{
    TokType type;
    LPTSTR text;
    int     code;
    int     position;
} gxSToken;

struct yy_buffer_state;
typedef struct yy_buffer_state *YY_BUFFER_STATE;
typedef int yy_state_type;

class GX_PARSE_STATE: public CObject
{
public:
// costruction/destruction
	GX_PARSE_STATE();
	~GX_PARSE_STATE();

	YY_BUFFER_STATE yy_current_buffer;
	TCHAR yy_hold_char;
	int yy_n_chars;
	int yyleng;
	TCHAR *yy_c_buf_p;
	int yy_did_buffer_switch_on_eof;
	TCHAR *yytext;
	yy_state_type yy_last_accepting_state;
	TCHAR *yy_last_accepting_cpos;
	LPCTSTR formula_buffer;
	gxSToken  token;
	int   position;
	int   input_pointer;
	int   input_length;
	int yy_init;     /* whether we need to initialize */
	int yy_start;    /* start state number */
	int yy_start_stack_ptr;
	int yy_start_stack_depth;
	int *yy_start_stack;
	int scanner_init_first;
};

extern gxSToken __cdecl _gx_get_token(int);
extern void __cdecl _gx_scanner_init(LPCTSTR);


#endif //_EXPRSCAN_H_
