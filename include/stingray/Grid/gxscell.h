///////////////////////////////////////////////////////////////////////////////
// gxscell.h : Formula Engine cell and worksheet info
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

#ifndef _GXSCELL_H_
#define _GXSCELL_H_

// // #include <StingrayExportDefs.h>

// Comment out GX_LARGE_GRID if all your grids come along well with 32767 rows.
// This has the advantage that you save 8 Byte per cell and range object
#define GX_LARGE_GRID

#if _MFC_VER >= 0x0300        
#define GX_ULONG_SIZE       32  /* # of bits in unsigned long */
#define GX_ULONG_MASK       0xffffffff  /* was ULONG_MAX */
#else
#define GX_ULONG_SIZE       16  /* # of bits in unsigned long */
#define GX_ULONG_MASK       0xffff  /* was ULONG_MAX */
#endif

#if _MSC_VER <= 800

// 16-bit
#define GX_MIN_ROW          1L
#define GX_MAX_ROW          2048L
#define GX_MIN_COL          0L
#define GX_MAX_COL          255L
typedef unsigned gxRowCol;

#else // 32-bit

#ifdef GX_LARGE_GRID
	#define GX_MIN_ROW          1L
	#define GX_MAX_ROW          8388607L
	#define GX_MIN_COL          0L
	#define GX_MAX_COL          4095L
	typedef unsigned gxRowCol;
#else
	#define GX_MIN_ROW          1L
	#define GX_MAX_ROW          32767L
	#define GX_MIN_COL          0L
	#define GX_MAX_COL          4095L
	typedef unsigned short gxRowCol;
#endif

#endif
#define GX_MAX_TEXT     512
#define GX_MAX_NAME_LEN     32  /* chars in range name + 1 */

#define GX_VALID_COL(C)     ((C)>=0 && (C)<= GX_MAX_COL)
#define GX_VALID_ROW(R)     ((R)>=1 && (R)<= GX_MAX_ROW)

#ifndef GX_MIN
#define GX_MIN(X,Y)     ((X)<(Y)?(X):(Y))
#endif
#ifndef GX_MAX
#define GX_MAX(X,Y)     ((X)>(Y)?(X):(Y))
#endif
#define GX_LIMIT(X,LO,HI)       ((X)<(LO)?(LO):((X)>(HI)?(HI):(X)))
#define GX_IN_LIMITS(X,LO,HI)   ((X)<(LO)?(0):((X)>(HI)?(0):(1)))

#define GX_BOUNDS_CHECK(R,C)    (GX_VALID_ROW(R) && GX_VALID_COL(C))

#define GX_RANGE_CHECK(gxRange) (GX_BOUNDS_CHECK((gxRange).r0, (gxRange).c0) && \
				 GX_BOUNDS_CHECK((gxRange).r1, (gxRange).c1))

#define GX_IN_RANGE(gxRange,R,C)    ((R)>=(gxRange).r0 && (R)<=(gxRange).r1 && \
				 (C)>=(gxRange).c0 && (C)<=(gxRange).c1)

#define GX_IS_SORTED(gxRange)   ((gxRange).r0<=(gxRange).r1 && \
				 (gxRange).c0<=(gxRange).c1)

#define GX_IS_MAX_RANGE(gxRange) ((gxRange).r0 == GX_MIN_ROW && (gxRange).r1 == GX_MAX_ROW && \
				 (gxRange).c0 == GX_MIN_COL && (gxRange).c1 == GX_MAX_COL)

#define GX_CELL_IS_EMPTY(cp)    ((cp) == NULL || (cp)->cell_type == GX_EMPTY_CELL)
#define GX_CELL_IS_EMPTYVALUE(cp)   ((cp) == NULL || (cp)->cell_type == GX_EMPTY_CELL || (cp)->value_type == GX_VALUE_NONE )

#define GX_CELL_IS_CONSTANT(cp) ((cp) && (cp)->formula == NULL)

#define GX_CELL_HAS_FORMULA(cp) ((cp) && (cp)->formula != NULL)

#define GX_CELL_CONTAINS_TEXT(cp)   ((cp) && ((cp)->value_type == GX_VALUE_STRING || \
				 (cp)->value_type == GX_VALUE_SHORT_STRING))

#define GX_CELL_CONTAINS_NUMBER(cp) ((cp) && (cp)->value_type == \
					 GX_VALUE_NUMERIC)

#define GX_CELL_CONTAINS_ERROR(cp)  ((cp) && (cp)->value_type == GX_VALUE_ERROR)

#define GX_CELL_SET_FLAG(cp, flag)      ((cp)->flags |= (flag))
#define GX_CELL_CLEAR_FLAG(cp, flag)    ((cp)->flags &= ~(flag))
#define GX_CELL_TEST_FLAG(cp, flag) (((cp)->flags & (flag)) != 0)

#define GX_CELL_SET_FLAGS(cp, flag) ((cp)->flags |= (flag))
#define GX_CELL_CLEAR_FLAGS(cp, flag)   ((cp)->flags &= ~(flag))
#define GX_CELL_TEST_FLAGS(cp, flag)    ((cp)->flags & (flag))

#define GX_MARK_MODIFIED(si)    (_gx_get_context_ptr(si)->modified = 1)
#define GX_RESET_MODIFIED(si)   (_gx_get_context_ptr(si)->modified = 0)
#define GX_IS_MODIFIED(si)      (_gx_get_context_ptr(si)->modified)

typedef double gxNumber;

/* Engine cell structure */

class CGXStyle;
struct gxCell;

struct gxCell
{
    gxCell *next;        /* used by hash table & undo  */
    gxRowCol row, 
		     col;    /* cell location              */

    union
    {
        gxNumber number;    /* numeric value              */
        LPTSTR   string; /* string value pointer       */
        TCHAR    short_string[8/sizeof(TCHAR)];    /* for 8-byte string values   */
        struct
        {
            int     code;   /* code from error_defs.h     */
            LPTSTR  fn; /* ptr to name of fn, or NULL */
        } err;
    } value;
    struct _gx_formula *formula;    /* cell formula pointer       */
    unsigned serial;    /* _gx_recalc serial number       */
    unsigned   /* cell property fields       */
         cell_type:		4, /* cell type                  */
         value_type:	4, /* cell value type            */
         inserted:		1, /* cell is in the sheet       */
         block_index:	6, /* internal use               */
         flags:			8; /* internal use               */
    CGXStyle *pStyle;
};


typedef struct _gx_cell_prop
{
    int     dummy;
}       gxCellProp;

/* gxCell Types */

#define GX_EMPTY_CELL       0
#define GX_NUMERIC_CELL     1
#define GX_LABEL_CELL       2
#define GX_FORMULA_CELL     3
#define GX_CONSTANT_FORMULA_CELL    4
#define GX_CELL_TYPE_MAXVAL 4

#define GX_CHECK_CELL_TYPE(X)   ((X)>=0 && (X)<=GX_CELL_TYPE_MAXVAL)


/* gxCell Value Types */

#define GX_VALUE_NONE       0
#define GX_VALUE_NA     1
#define GX_VALUE_ERROR      2
#define GX_VALUE_NUMERIC        3
#define GX_VALUE_STRING     4
#define GX_VALUE_SHORT_STRING   5
#define GX_VALUE_MAXVAL     5

#define GX_CHECK_VALUE_TYPE(X)  ((X)>=0 && (X)<=GX_VALUE_MAXVAL)

#define GX_SHORTSTRING_LEN	(8/sizeof(TCHAR))

/* Status Flags */

#define GX_NEEDS_RECALC     (1<<0)  /* may not need */
#define GX_VISITED          (1<<1)
#define GX_TOUCHED          (1<<2)
#define GX_UPDATED          (1<<3)  /* may not need */
#define GX_CYCLE            (1<<4)
#define GX_CONSTRAINT_VIOL      (1<<5)


/*
  gxCell Allocation Blocks.  These are blocks of cell structures, which are
  allocated in clumps of 32 or 64 (depending on the machine's definition
  of "unsigned long").  There is an "in_use" bit for each cell structure
  which indicates whether or not it is currently allocated.
*/

#define GX_CELL_BLOCK_SIZE      GX_ULONG_SIZE
#define GX_CELL_BLOCK_MASK      GX_ULONG_MASK


typedef struct _gx_cell_block
{
    unsigned long in_use;
    unsigned frozen;
    struct _gx_cell_block *next, *prev;
    struct _gx_cell_block_list *gxlist;
    gxCell  cells[GX_CELL_BLOCK_SIZE];
}       gxCellBlock;


typedef struct _gx_cell_block_list
{
    gxCellBlock *head,
           *tail;
    unsigned _gx_cell_count;
    unsigned freeze_order,
            needs_reorder;
}       gxCellBlockList;


#ifdef GX_LARGE_GRID

typedef struct _gx_range
{
	unsigned long
		r0:24, 
		r1:24,
        c0:13,
	    abs_r0:1,
        abs_c0:1,
        c1:13,
        abs_r1:1,
        abs_c1:1,
        cell_only:1;
}       gxRange;

#else

typedef struct _gx_range
{
	unsigned 
		r0:16, 
		r1:16,
        c0:13,
	    abs_r0:1,
        abs_c0:1,
        c1:13,
        abs_r1:1,
        abs_c1:1,
        cell_only:1;
}       gxRange;

#endif


typedef struct _gx_range_list
{
    struct _gx_range_list *next;
    gxRange range;
}       gxRangeList;

typedef struct _gx_range_name
{
    struct _gx_range_name *next;
    LPTSTR  name;
    gxRange range;
}       gxRangeName;

typedef struct _gx_cell_value
{
    int     type;
    union
    {
        gxNumber number;
        LPTSTR   string;
        int     graph_index;
        struct
        {
            int     code;
            LPTSTR  fn;
        } err;
    } value;
} gxCellValue;


typedef struct _gx_scan_buf
{              /* context for efficient range scans */
    int     type,
            si;
    unsigned row,
            col,
            index;
    unsigned mask,
            current_mask;
    gxCellBlockList *gxlist;
    gxCellBlock *cb;
    unsigned long bitmask;
    gxRange range;
}       gxScanBuf;


/* gxCell hash table parameters (size should be a prime number */

#if _MSC_VER <= 800
#define GX_HASH_SIZE        7999L    /* prime number near 32K */
#else
#define GX_HASH_SIZE        32749L   /* prime number near 32K */
#endif
#define GX_HASH_FUNCTION(R,C)   (((unsigned) ((R)+GX_MAX_ROW*(C)))%((unsigned)GX_HASH_SIZE))

/* mask values used by _gx_init_range_scan() */

#define GX_CONSTANT_LIST        (1<<0)
#define GX_RECALC_LIST      (1<<1)
#define GX_EMPTY_LIST       (1<<2)
#define GX_ALL_LISTS        ((unsigned) -1)

/* recalc_mode values */

#define GX_RECALC_AUTO      0
#define GX_RECALC_MANUAL        1

/* recalc_method values */

#define GX_RECALC_AS_NEEDED 0
#define GX_RECALC_FOREGROUND    1
#define GX_RECALC_BACKGROUND    2   /* NOT IMPLEMENTED!!! */

/* iteration_limit max value */

#define GX_RECALC_MAX_ITER      100

/* Currency digits separator style (gxCurrencyStyle.sep) */

#define GX_CURR_SEP_1       0   /* 1,234,567.89 */
#define GX_CURR_SEP_2       1   /* 1.234.567,89 */
#define GX_CURR_SEP_3       2   /* 1 234 567.89 */
#define GX_CURR_SEP_4       3   /* 1 234 567,89 */

/* How negative currency values are displayed (gxCurrencyStyle.neg) */

#define GX_CURR_NEG_PAREN       0
#define GX_CURR_NEG_MINUS       1

/* Where the tag is displayed (gxCurrencyStyle.tag_loc) */

#define GX_CURR_TAG_IS_PREFIX   0
#define GX_CURR_TAG_IS_SUFFIX   1

typedef struct
{
    int     sep;
    int     neg;
    int     tag_loc;
    TCHAR   tag[8];
} gxCurrencyStyle;



/*
 * The gxSheetContext structure defined below contains all persistent data
 * and parameters for a sheet, as well as internal variables pertaining
 * to the sheet, which must be preserved across function calls.
 */

class CGXFormulaSheet;

typedef struct _gx_sheet_context
{
/*
 * gxCell Hash Table
 */

    gxCell *hash[GX_HASH_SIZE];

/*
 * gxCell Lists
 */

    gxCellBlockList constant_list,  /* const. numbers, strings, formulas */
            recalc_list,    /* non-constant formulas             */
            empty_list; /* used only if "keep_empties" set   */

/*
 * Named gxRange List
 */

    gxRangeName *range_name_list;
    gxRangeName *deleted_range_name;

/*
 * Recalculation Options
 */

    int     recalc_mode,
            recalc_method,
            constraint_check,
            iteration_limit,
            blanks_are_zeros;

/*
 * Import/Export Options
 */

/*  int xswsthreshold,
                xsonewordpercol,
                latex_auto_escape;
*/

/*
 * gxCell Defaults
 */

    int     default_format,
            default_places;
/*
 * Currency Style Options
 */

    gxCurrencyStyle currency_style[4];

/*
 * Misc. Options
 */

//  int alias_first;        /* vertical or horizontal precedence          */
//    int lotus_mode;       /* use Lotus-style formula syntax             */
    int     keep_empties;   // keep empty cells after move or
// clear range

//
//Excel related stuff

//    int   use_1904_dates;     /* flag for using Excel's 1904 date system    */
//    int   excel_mode;     /* flags if in Excel compatibility mode       */


//
/*
 * Persistent Internal Data
 */

    unsigned long _gx_cell_count;   /* total cells in sheet                       */
    unsigned long cell_limit;   /* maximum cells in sheet                     */
    int     modified;   /* modified since last save                   */
    unsigned serial;    /* recalculation serial number                */

/*
 * Non-persistent Internal Data
 */

    gxRowCol *row_cell_count; // [GX_MAX_ROW-GX_MIN_ROW];
    gxRowCol *col_cell_count; // [GX_MAX_COL-GX_MIN_COL];
	gxRowCol highwater_rowcount;
	gxRowCol highwater_colcount;
    gxRange extent_cache;
    int     extent_cache_valid;
    gxRangeList *recalc_rangelist;
    int     recalc_status;
    int     first_error;
    int     error_suppress;
    int     do_preserve;
	gxRange undo_dst;
	int     is_undo_init;
    gxCell *preserve_list;
    void   *gscontext;  /* Goalseek context (see goalseek.[ch]) */
    int     v2_string_mode; /* turns off ANSI C string escape */
	int     bCycle;
    TCHAR    szErrorText[254];

    CGXFormulaSheet *m_pSheetContext;
}       gxSheetContext;


/* prototypes for cell.c */

extern int __cdecl _gx_new_sheet_context(void);

extern void __cdecl _gx_free_sheet_context(int si);

extern "C" GRID_API gxSheetContext * __cdecl _gx_get_context_ptr(int si);

extern gxCell * __cdecl _gx_new_cell(gxCellBlockList * gxlist);

extern void __cdecl _gx_free_cell_block_list(gxCellBlockList * gxlist);

extern gxCell * __cdecl _gx_copy_cell_to_list(gxCellBlockList * dst, gxCell * cp);

extern gxCell * __cdecl _gx_cell_dup(gxCell * cp);

extern gxCell * __cdecl _gx_move_cell_to_list(gxCellBlockList * dst, gxCell * cp);

extern gxCell * __cdecl _gx_find_cell(int si, int r, int c);

extern int __cdecl _gx_insert_cell(int si, gxCell * cp);

extern void __cdecl _gx_remove_cell(int si, gxCell * cp);

extern void __cdecl _gx_free_cell(gxCell * cp);

extern void __cdecl _gx_destroy_cell(int si, gxCell * cp);

extern int __cdecl _gx_cell_put_number(int si, int r, int c,
                                       gxNumber number, gxCellProp * cprop);

extern int __cdecl _gx_cell_put_label(int si, int r, int c, LPCTSTR label, gxCellProp * cprop);

extern unsigned __cdecl _gx_cell_count(int si, unsigned mask);

extern void __cdecl _gx_init_range_scan(int si, gxRange range, gxScanBuf * scan, unsigned mask);

extern gxCell * __cdecl _gx_do_range_scan(gxScanBuf * scan);

extern void __cdecl _gx_init_cell_list_scan(gxCellBlockList * gxlist, gxScanBuf * scan);

extern gxCell * __cdecl _gx_do_cell_list_scan(gxScanBuf * scan);

extern int __cdecl _gx_get_sheet_extent(int si, gxRange * all);

extern int __cdecl _gx_limit_to_extent(int si, gxRange * rng);

extern int __cdecl _gx_cell_put_formula(int si, int r, int c,
                       LPCTSTR formula, gxCellProp * cprop, gxCellValue * cv);

extern void __cdecl _gx_replace_cell_formula(gxCell * cp, struct _gx_formula * fm);

extern gxCell * __cdecl _gx_insert_empty_cell(int si, int r, int c, gxCellProp * cprop);

extern gxCell * __cdecl _gx_get_cell_value(int si, int r, int c, gxCellValue * cval);

extern int __cdecl _gx_set_recalc_mode(int si, int mode);

extern int __cdecl _gx_get_recalc_mode(int si);

extern int __cdecl _gx_set_recalc_method(int si, int method);

extern int __cdecl _gx_get_recalc_method(int si);

extern int __cdecl _gx_set_constraint_check(int si, int toggle);

extern int __cdecl _gx_get_constraint_check(int si);

extern int __cdecl _gx_set_blanks_are_zeros(int si, int toggle);

extern int __cdecl _gx_get_blanks_are_zeros(int si);

extern int __cdecl _gx_set_iteration_limit(int si, int limit);

extern int __cdecl _gx_get_iteration_limit(int si);

extern int __cdecl _gx_freeze_list_order(int si, int mask);

extern void __cdecl _gx_unfreeze_list_order(int si, int mask);

extern void __cdecl _gx_set_cell_value(gxCell * cp, gxCellValue * cv);

extern LPCTSTR __cdecl _gx_get_formatted_text(int si, gxCell * cp, gxCellProp * cprop);

extern void __cdecl _gx_grow_highwater_row_count(int si, gxRowCol nNewSize);

extern void __cdecl _gx_grow_highwater_col_count(int si, gxRowCol nNewSize);

/* prototypes for _gx_recalc.c */

extern void __cdecl _gx_add_recalc_range(int si, gxRange * rp);

extern void __cdecl _gx_clear_recalc_rangelist(int si);

extern int __cdecl _gx_test_partial_recalc(int si);

extern int __cdecl _gx_check_recalc_status(int si);

extern void __cdecl _gx_force_recalc(int si);

extern int __cdecl _gx_edit_recalc(int si);

extern int __cdecl _gx_recalc(int si);

extern int __cdecl _gx_find_constraints(int si, gxCellBlockList * gxlist);

extern void __cdecl _gx_back_calc(int si, gxCell * cp);

extern void __cdecl _gx_check_tool_neighborhood(int si, gxCell* cp);


/* public function prototypes for range_name.c */

extern int __cdecl _gx_range_name_set(int si, LPCTSTR name, gxRange * range);

extern int __cdecl _gx_valid_range_name_char(TCHAR c);

extern int __cdecl _gx_valid_range_name(LPCTSTR name);

extern gxRangeName * __cdecl _gx_range_name_lookup(int si, LPCTSTR name, gxRange * range);

extern void __cdecl _gx_adjust_reorder_named_ranges(int si, gxRange * range, int nRowOrCol, int nFrom, int nTo, int nDest);

extern void __cdecl _gx_adjust_named_ranges(int si, gxRange * range, int dr, int dc);

extern int __cdecl _gx_range_name_delete(int si, LPCTSTR name);

extern int __cdecl _gx_range_name_undelete(int si, gxRangeName* rnp);

extern void __cdecl _gx_resolve_names(int si, struct _gx_formula * fm);

extern void __cdecl _gx_free_range_name_list(int si);

/* Values for abs_mask parameter in _gx_make_range() and _gx_make_cell() */

#define GX_CELL_ONLY    1
#define GX_ABS_C0       2
#define GX_ABS_R0       4
#define GX_ABS_C1       8
#define GX_ABS_R1       16
#define GX_ABS_R        (GX_ABS_R0 | GX_ABS_R1)
#define GX_ABS_C        (GX_ABS_C0 | GX_ABS_C1)
#define GX_ABS_ALL      (GX_ABS_R | GX_ABS_C)

/* prototypes for range_util.c */

extern LPCTSTR __cdecl _gx_col_to_text(unsigned int col);

extern LPCTSTR __cdecl _gx_rc_to_text(int r, int c);

extern int __cdecl _gx_text_to_col(LPCTSTR name);

extern int __cdecl _gx_text_to_rc(LPCTSTR name, int *row, int *col);

extern int __cdecl _gx_text_to_range(LPCTSTR name, gxRange * range);

extern int __cdecl _gx_si_text_to_range(int si, LPCTSTR name, gxRange * range);

extern LPCTSTR __cdecl _gx_range_to_text(gxRange * range);

extern int __cdecl _gx_sort_range(gxRange * range);

extern int __cdecl _gx_intersect(gxRange * rp0, gxRange * rp1);

extern int __cdecl _gx_intersection(gxRange * rp0, gxRange * rp1, gxRange * result);

extern int __cdecl _gx_same_range(gxRange * rp0, gxRange * rp1);

extern gxRange __cdecl _gx_make_range(int r0, int c0, int r1, int c1, int abs_mask);

extern gxRange __cdecl _gx_make_cell(int r, int c, int abs_mask);

extern void __cdecl _gx_purify_range(gxRange * range);

extern void __cdecl _gx_init_range(gxRange * range);

/* xsstring.h */

extern void __cdecl _gx_set_iso_escape(int x);

extern int __cdecl _gx_get_iso_escape(void);

extern LPTSTR __cdecl _gx_xs_strdup(LPCTSTR string);

extern LPTSTR __cdecl _gx_xs_short_strdup(LPCTSTR string);

extern void __cdecl _gx_xs_short_strcpy(LPTSTR dst, LPCTSTR src, BOOL bAddEOS);

extern int __cdecl _gx_decode_hex_digit(TCHAR c);

extern LPTSTR __cdecl _gx_xs_encode_string(LPTSTR outstr, LPCTSTR instr, int quote_escape);

extern LPTSTR __cdecl _gx_xs_decode_string(LPTSTR outstr, LPCTSTR instr);

extern int __cdecl _gx_xs_string_linecount(LPCTSTR t);

extern LPTSTR __cdecl _gx_xs_encode_html(LPTSTR outstr, LPCTSTR instr);

/* move.h */

extern gxRange __cdecl _gx_figure_move_dest(gxRange * sp, int r, int c);

extern int __cdecl _gx_move_range(int si, gxRange src, int r, int c, int adjust_suppress);

extern void __cdecl _gx_figure_insert_col_src_dst(int c, int n, gxRange * src, gxRange * dst);

extern int __cdecl _gx_insert_columns(int si, int c, int n);

extern void __cdecl _gx_figure_insert_row_src_dst(int r, int n, gxRange * src, gxRange * dst);

extern int __cdecl _gx_insert_rows(int si, int r, int n);

extern void __cdecl _gx_figure_delete_col_src_dst(int c, int n, gxRange * src, gxRange * dst);

extern int __cdecl _gx_delete_cols(int si, int c, int n);

extern int __cdecl _gx_delete_rows(int si, int r, int n);

extern int __cdecl _gx_reorder_range(int si, int nRowOrCol, int nFrom, int nTo, int nDest);

extern void __cdecl _gx_adjust_value_move1(unsigned *c, unsigned nFrom, unsigned nTo, unsigned nDest);

extern void __cdecl _gx_adjust_value_move2(unsigned *c0, unsigned *c1, unsigned nFrom, unsigned nTo, unsigned nDest);

extern int __cdecl _gx_copy_range(int si, gxRange src, int r, int c, int adjust_suppress);

/* clear.h */

int	__cdecl _gx_clear_range(int si, gxRange dst);


#endif //_GXSCELL_H_
