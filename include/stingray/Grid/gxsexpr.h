///////////////////////////////////////////////////////////////////////////////
// gxsexpr.h : Expression routines and untilities for worksheet functions


#ifndef _GXSEXPR_H_
#define _GXSEXPR_H_

// // #include <StingrayExportDefs.h>

#define GX_ENULL        (-1)
#define GX_MAX_NODES    200
#define GX_MAX_ARGS 100

typedef enum
{
    GX_OPERATOR_NODE,   /* 0 */
    GX_NUMBER_NODE, /* 1 */
    GX_STRING_NODE, /* 2 */
    GX_CELL_NODE,   /* 3 */
    GX_RANGE_NODE,  /* 4 */
    GX_NAME_NODE,   /* 5 */
    GX_NAMED_CELL_NODE, /* 6 */
    GX_NAMED_RANGE_NODE,    /* 7 */
    GX_FUNCTION_NODE,   /* 8 */
    GX_ARG_NODE,    /* 9 */
    GX_RELATIVE_NODE,   /* 10 */
    GX_EXTENSION_NODE   /* 11 */
}       gxNodeType;


typedef enum
{
    GX_PLUS,   /* 0 */
    GX_MINUS,  /* 1 */
    GX_UNARY_PLUS,  /* 2 */
    GX_UNARY_MINUS, /* 3 */
    GX_MULTIPLY,    /* 4 */
    GX_DIVIDE, /* 5 */
    GX_POWER,  /* 6 */
    GX_MODULUS,/* 7 */
    GX_LOGICAL_AND, /* 8 */
    GX_LOGICAL_OR,  /* 9 */
    GX_LOGICAL_NOT, /* 10 */
    GX_BOOLEAN_AND, /* 11 */
    GX_BOOLEAN_OR,  /* 12 */
    GX_BOOLEAN_XOR, /* 13 */
    GX_BOOLEAN_NOT, /* 14 */
    GX_SHIFT_LEFT,  /* 15 */
    GX_SHIFT_RIGHT, /* 16 */
    GX_EQUAL,  /* 17 */
    GX_NOT_EQUAL,   /* 18 */
    GX_LESS_THAN,   /* 19 */
    GX_GREATER_THAN,    /* 20 */
    GX_LT_OR_EQUAL, /* 21 */
    GX_GT_OR_EQUAL, /* 22 */
    GX_CONDITIONAL, /* 23 */
    GX_JOINRANGE,   /* 24 */
    GX_PERCENT,/* 25 */
    GX_ILLEGAL_OP   /* 26 */
}       gxOpType;


typedef short int gxExprPointer;

typedef double gxNumber;

typedef struct
{
 unsigned node_type:		8;
 unsigned has_parens:		1;
 unsigned number_is_hex:	1;
 unsigned arg_is_nonstrict:	1;
 unsigned is_typesafe:		1;
 unsigned is_extern_ref:	1;
    gxExprPointer left;
    gxExprPointer right;
    union
    {
        gxOpType operator_;			/* GX_OPERATOR_NODE            */
        gxNumber operand;			/* GX_NUMBER_NODE              */
        LPTSTR   name;				/* GX_NAME_NODE                */
        LPTSTR   string;			/* GX_STRING_NODE              */
        gxRange range;				/* GX_CELL_NODE, GX_RANGE_NODE */
        gxRangeName *rnp;			/* NAMED_CELL, NAMED_RANGE     */
        struct _gx_keyword *fnp;    /* GX_FUNCTION_NODE            */
        gxExprPointer eback;		/* GX_EXTENSION_NODE           */
        struct
        {							/* GX_ARG_NODE                 */
            gxExprPointer back;
            unsigned short decl_arg_type;
        } arg;
        struct
        {							 /* GX_RELATIVE_NODE            */
            gxExprPointer r_expr;
            gxExprPointer c_expr;
        } rel;
    } value;
} gxExprNode;

typedef struct _gx_formula
{
    gxExprPointer expr_start;
    gxExprPointer cons_start;
    gxExprPointer depend_start;
    short int expr_size;
    gxExprNode *expression;
    LPTSTR comment;
} gxFormula;


/*---------------------------------------------------------------------------*/
/*  Evaluator operand definitions.                                           */

typedef enum
{
    GX_NUMBER,
    GX_STRING,
    GX_RANGE,
    GX_CELL,
    GX_EXPR_TREE,
    GX_OP_NA,
    GX_OP_ERROR
} gxOType;

typedef struct _gx_operand
{
    gxOType type;
    union
    {
        gxNumber number;    /* GX_NUMBER    */
        LPTSTR   string;	/* GX_STRING    */
        gxRange range;		/* GX_RANGE     */
        int     count;		/* GX_CELL      */
        struct
        {					/* GX_EXPR_TREE */
            gxExprNode *nbuf;
            gxExprPointer start;
        } etree;
        struct
        {
            int     code;
            LPTSTR  fn;
        } err;
    } val;
} gxOperand;

#define  GX_MAX_TYPED_ARGS      9

#define  GX_STRICT      0
#define  GX_NONSTRICT   1

#define  GX_REQUIRED    0   /* Exactly one  */
#define  GX_OPTIONAL    1   /* Zero or one  */
#define  GX_VARIABLE    2   /* One or more  */

typedef enum
{
    GX_TC_NUMBER,
    GX_TC_NUMERIC,
    GX_TC_NUM_RNG,
    GX_TC_STRING,
    GX_TC_STR_CL,
    GX_TC_STR_RNG,
    GX_TC_CELL,
    GX_TC_RANGE,
    GX_TC_RNG_ONLY,
    GX_TC_MATRIX,
    GX_TC_POLY,
    GX_TC_NULL
} gxCheckerTypes;

typedef struct
{
    short int type;
	unsigned is_nonstrict: 1;
	unsigned presence:     2;
} gxArgDescript;

typedef struct _gx_keyword
{
    LPTSTR  name;
    gxOperand(__cdecl *function) (gxOperand argv[]);
    int     port;   /* 0 for intrinsic, port # for extr. */
    long    tag;    /* for generic function handlers */
    short int type; /* operand type of result */
    short int num_args; /* number of typed arguments */
    gxArgDescript args[GX_MAX_TYPED_ARGS];
	int		xlf;		/* index into XL function table */
} gxKeyword;


typedef struct _gx_ext_fn
{              /* List of extrinsic functions */
    gxKeyword kw;
    struct _gx_ext_fn *next;
} gxExtFnList;


typedef struct _gx_matrix
{              /* working matrix structure */
    unsigned r_dim,
            c_dim;
    double *data;
} gxMatrix;

#define GX_MVAL(m,i,j)      (m).data[(i)*(m).c_dim+(j)]


/*---------------------------------------------------------------------------*/
/*  Expression functions.                                                    */

RWGLOBAL_FUNC_API(void)			_gx_expr_print(int, gxFormula *, LPTSTR);
RWGLOBAL_FUNC_API(gxOperand)	_gx_expr_eval(int, int, int, gxExprNode *, gxExprPointer);
RWGLOBAL_FUNC_API(gxOperand)	_gx_do_eval(gxExprNode *, gxExprPointer, int bAddMemObj = 0);
RWGLOBAL_FUNC_API(gxOperand)	_gx_do_eval_et(gxExprNode *, gxExprPointer);
RWGLOBAL_FUNC_API(int)			_gx_evaluate_cexpr(int, int, int, gxExprNode *, gxExprPointer);
RWGLOBAL_FUNC_API(int)			_gx_evaluate_cell(int, gxCell *);
RWGLOBAL_FUNC_API(void)			_gx_set_error_reason(int reason);
RWGLOBAL_FUNC_API(int)			_gx_get_error_reason(void);
RWGLOBAL_FUNC_API(void)			_gx_set_error_position(int pos);
RWGLOBAL_FUNC_API(int)			_gx_get_error_position(void);
RWGLOBAL_FUNC_API(void)			_gx_set_expr_err_flag(int flag);
RWGLOBAL_FUNC_API(int)			_gx_get_expr_err_flag(void);
RWGLOBAL_FUNC_API(int)			_gx_get_expr_si(void);
RWGLOBAL_FUNC_API(LPTSTR)		_gx_get_xs_fn_name(void);
RWGLOBAL_FUNC_API(LPTSTR)		_gx_get_expr_sbuf(void);
RWGLOBAL_FUNC_API(void)			_gx_get_expr_rc(unsigned *, unsigned *);
RWGLOBAL_FUNC_API(int)			_gx_get_expr_err_code(void);

#ifdef _GXDLL
	#ifdef _OG_EXPORT_IMPL 
		RWGLOBAL_FUNC_API(gxOperand)*	_gx_get_fn_arg_ptr(void);
	#else
		RWGLOBAL_FUNC_API(gxOperand*)	_gx_get_fn_arg_ptr(void);
	#endif
	//RWGLOBAL_FUNC_API(gxOperand*)	_gx_get_fn_arg_ptr(void);
#else
	RWGLOBAL_FUNC_API(gxOperand*)	_gx_get_fn_arg_ptr(void);
#endif

RWGLOBAL_FUNC_API(void)			_gx_set_fn_arg_ptr(gxOperand * p);
RWGLOBAL_FUNC_API(int)			_gx_references_cells(gxExprNode * nbuf, int size);
RWGLOBAL_FUNC_API(int)			_gx_calls_functions(gxExprNode * nbuf, int size);
RWGLOBAL_FUNC_API(void)			_gx_free_formula(gxFormula *);
RWGLOBAL_FUNC_API(void)			_gx_free_formula_strings(gxFormula *);

#ifdef _GXDLL
	#ifdef _OG_EXPORT_IMPL
		RWGLOBAL_FUNC_API(gxFormula)*	_gx_formula_dup(gxFormula *);
	#else
		RWGLOBAL_FUNC_API(gxFormula*)	_gx_formula_dup(gxFormula *);
	#endif
	//RWGLOBAL_FUNC_API(gxFormula*)	_gx_formula_dup(gxFormula *);
#else
	RWGLOBAL_FUNC_API(gxFormula*)	_gx_formula_dup(gxFormula *);
#endif

RWGLOBAL_FUNC_API(void)			_gx_reset_first_error(int);
RWGLOBAL_FUNC_API(void)			_gx_convert_upper(LPTSTR);
RWGLOBAL_FUNC_API(void)			_gx_convert_lower(LPTSTR);
RWGLOBAL_FUNC_API(int) 			_gx_xs_int_check(double);
RWGLOBAL_FUNC_API(void)			_gx_str_trim(LPTSTR);
RWGLOBAL_FUNC_API(int)			_gx_ieee_infnan(gxNumber *);
RWGLOBAL_FUNC_API(void)			_gx_fp_error_init(void);
RWGLOBAL_FUNC_API(LPTSTR)		_gx_format_function_name(LPTSTR, LPCTSTR, int);
RWGLOBAL_FUNC_API(void)			_gx_mkwm(gxMatrix * m);
RWGLOBAL_FUNC_API(int)			_gx_freewm(gxMatrix * m);
RWGLOBAL_FUNC_API(void)			_gx_cleanwm(void);

#ifdef _GXDLL
	#ifdef _OG_EXPORT_IMPL
		RWGLOBAL_FUNC_API(gxNumber)*	_gx_mknumarray(int n);
	#else
		RWGLOBAL_FUNC_API(gxNumber*)	_gx_mknumarray(int n);
	#endif
	//RWGLOBAL_FUNC_API(gxNumber*)	_gx_mknumarray(int n);
#else
	RWGLOBAL_FUNC_API(gxNumber*)	_gx_mknumarray(int n);
#endif

// exprutil.cpp
RWGLOBAL_FUNC_API(int)			_gx_si_evaluate_expr(int si, LPCTSTR expr, int r, int c, gxOperand * result);

// expreval.cpp
RWGLOBAL_FUNC_API(int)			_gx_evaluate_cell_constraint(int si, gxCell * cp);

// exprpars.cpp
RWGLOBAL_FUNC_API(int)			_gx_parse_formula(int si, LPCTSTR text, gxFormula * fm);

// function.cpp

#define     GX_M_PI     3.14159265358979323846
#define     GX_M_LN2    0.69314718055994530942

#define GX_HANDLE_OP_ERROR(op)  if ((op).type == GX_OP_ERROR) \
					_gx_propagate_error(&(op))

RWGLOBAL_FUNC_API(void)			_gx_fn_table_init(void);

#ifdef _GXDLL
	#ifdef _OG_EXPORT_IMPL
		RWGLOBAL_FUNC_API(gxKeyword)*	_gx_fn_lookup(LPCTSTR text);
	#else
		RWGLOBAL_FUNC_API(gxKeyword*)	_gx_fn_lookup(LPCTSTR text);
	#endif
	//RWGLOBAL_FUNC_API(gxKeyword*)	_gx_fn_lookup(LPCTSTR text);
#else
	RWGLOBAL_FUNC_API(gxKeyword*)	_gx_fn_lookup(LPCTSTR text);
#endif

RWGLOBAL_FUNC_API(gxNumber)		_gx_get_one_number(gxOperand argv[]);
RWGLOBAL_FUNC_API(int)			_gx_cvt2constant(gxOperand * opp); // QA 31853
RWGLOBAL_FUNC_API(int)			_gx_cvt2int(gxNumber x);
RWGLOBAL_FUNC_API(int)			_gx_fn_get_value(int r, int c, gxNumber * vp);
RWGLOBAL_FUNC_API(void)			_gx_fn_xsstrcpy(LPTSTR dst, LPCTSTR src, int n);
RWGLOBAL_FUNC_API(void)			_gx_fn_xsstrcat(LPTSTR dst, LPCTSTR src, int n);
RWGLOBAL_FUNC_API(void)			_gx_function_error(int code); // QA 31853
RWGLOBAL_FUNC_API(void)			_gx_propagate_error(gxOperand * argv);
RWGLOBAL_FUNC_API(void)			_gx_clean_fn_args(void);

// stat.cpp
RWGLOBAL_FUNC_API(double)		_gx_gammalog(double x);
RWGLOBAL_FUNC_API(double)		_gx_betacf(double a, double b, double x);
RWGLOBAL_FUNC_API(double)		_gx_betai(double a, double b, double x);
RWGLOBAL_FUNC_API(double)		_gx_alphaT(double nu, double t);
RWGLOBAL_FUNC_API(double)		_gx_alphaF(double nu1, double nu2, double F);
RWGLOBAL_FUNC_API(double)		_gx_phi(double x);
RWGLOBAL_FUNC_API(double)		_gx_phi_inverse(double x);

#define GX_VALID_DT(d)      ((d>0) && (d<73051))

// date.cpp
#define GX_LEAPYEAR(y) ((y%4==0) ? 1 : 0)

RWGLOBAL_FUNC_API(int)			_gx_end_of_month(int m, int y);
RWGLOBAL_FUNC_API(long)			_gx_edate(int si, long start_date, int mos);
RWGLOBAL_FUNC_API(void)			_gx_find_yearfrac1(int si, long start_date, long end_date, int basis, gxNumber * year_frac);
RWGLOBAL_FUNC_API(void)			_gx_find_yearfrac(int si, long start_date, long end_date, int basis, gxNumber * year_frac);
RWGLOBAL_FUNC_API(long)			_gx_days360(int si, long date1, long date2);
RWGLOBAL_FUNC_API(long)			_gx_encode_date(int si, int year, int month, int day);
RWGLOBAL_FUNC_API(int)			_gx_decode_date(int si, long gdate, int *year, int *month, int *day);
RWGLOBAL_FUNC_API(int)			_gx_encode_time(double *timeval, int hr, int min, int sec);
RWGLOBAL_FUNC_API(int)			_gx_decode_time(double timeval, int *hr, int *min, int *sec);
RWGLOBAL_FUNC_API(void)			_gx_current_time(int *yr, int *mo, int *da, int *hr, int *min, int *sec);
RWGLOBAL_FUNC_API(int)			_gx_get_date(int si, LPCTSTR date_str, int *mp, int *dp, int *yp, int *fmtp);
RWGLOBAL_FUNC_API(int)			_gx_get_time(LPCTSTR time_str, int *hp, int *mp, int *sp);

// matrix.cpp
RWGLOBAL_FUNC_API(int)			_gx_asymmetric(gxMatrix a);
RWGLOBAL_FUNC_API(gxMatrix)		_gx_mtranspose(gxMatrix a);
RWGLOBAL_FUNC_API(gxMatrix)		_gx_mmul(gxMatrix a, gxMatrix b);
RWGLOBAL_FUNC_API(gxMatrix)		_gx_mTmul(gxMatrix a, gxMatrix b);
RWGLOBAL_FUNC_API(gxMatrix)		_gx_mLUdecomp(gxMatrix a, int *indx, double *d);
RWGLOBAL_FUNC_API(gxMatrix)		_gx_mLUbksub(gxMatrix a, int *indx, gxMatrix b);
RWGLOBAL_FUNC_API(gxMatrix)		_gx_minvert(gxMatrix a);
RWGLOBAL_FUNC_API(gxMatrix)		_gx_mlinsolv(gxMatrix a, gxMatrix b);
RWGLOBAL_FUNC_API(int)			_gx_mlls_short(gxMatrix a, gxMatrix b, gxMatrix * result);
RWGLOBAL_FUNC_API(int)			_gx_mlls(gxMatrix a, gxMatrix b, gxMatrix * result);
RWGLOBAL_FUNC_API(double)		_gx_mdet(gxMatrix a);
RWGLOBAL_FUNC_API(void)			_gx_fft(gxMatrix a, int sign);
RWGLOBAL_FUNC_API(gxMatrix)		_gx_dft(gxMatrix a, int sign);
RWGLOBAL_FUNC_API(gxMatrix)		_gx_meigen(gxMatrix a);
RWGLOBAL_FUNC_API(void)			_gx_hh_tridiag(gxMatrix a, gxMatrix d, gxMatrix e);
RWGLOBAL_FUNC_API(void)			_gx_tridiag_eigen(gxMatrix d, gxMatrix e);

/*---------------------------------------------------------------------------*/
/*  Expression evaluator state.                                              */

#define GX_MAX_WM  8   /* maximum concurrent working memory buffers */

class GX_EVAL_STATE: public CObject
{
public:
	GRID_API GX_EVAL_STATE();
	GRID_API ~GX_EVAL_STATE();
	const GX_EVAL_STATE& operator=(const GX_EVAL_STATE& eval);

	int			expr_si;	
	LPTSTR		xs_fn_name;
	LPTSTR		expr_sbuf;
	unsigned	expr_r;
	unsigned	expr_c;
	int			eval_err_code;
	LPTSTR		eval_err_fn;
	gxOperand *	fn_arg_ptr;
	void *		wm[GX_MAX_WM];   /* dynamically allocated working memory */
#if _MSC_VER <= 800
	CATCHBUF eval_jmp_buf;
#else
	jmp_buf eval_jmp_buf;
#endif
};

// Exception code
const int nEvalError = 1;


/*----------------------------------------------------------------------------------*/
/*  Excel function numbers															*/
// The actual read/write code is only available with the Objective Grid Pro product

#define	gxxlfCount			0
#define	gxxlfIsna			2
#define	gxxlfIserror		3
#define	gxxlfSum			4
#define	gxxlfAverage		5
#define	gxxlfMin			6
#define	gxxlfMax			7
#define	gxxlfRow			8
#define	gxxlfColumn			9
#define	gxxlfNa				10
#define	gxxlfNpv			11
#define	gxxlfStdev			12
#define	gxxlfDollar			13
#define	gxxlfFixed			14
#define	gxxlfSin			15
#define	gxxlfCos			16
#define	gxxlfTan			17
#define	gxxlfAtan			18
#define	gxxlfPi				19
#define	gxxlfSqrt			20
#define	gxxlfExp			21
#define	gxxlfLn				22
#define	gxxlfLog10			23
#define	gxxlfAbs			24
#define	gxxlfInt			25
#define	gxxlfSign			26
#define	gxxlfRound			27
#define	gxxlfLookup			28
#define	gxxlfIndex			29
#define	gxxlfRept			30
#define	gxxlfMid			31
#define	gxxlfLen			32
#define	gxxlfValue			33
#define	gxxlfTrue			34
#define	gxxlfFalse			35
#define	gxxlfAnd			36
#define	gxxlfOr				37
#define	gxxlfNot			38
#define	gxxlfMod			39
#define	gxxlfDcount			40
#define	gxxlfDsum			41
#define	gxxlfDaverage		42
#define	gxxlfDmin			43
#define	gxxlfDmax			44
#define	gxxlfDstdev			45
#define	gxxlfVar			46
#define	gxxlfDvar			47
#define	gxxlfText			48
#define	gxxlfLinest			49
#define	gxxlfTrend			50
#define	gxxlfLogest			51
#define	gxxlfGrowth			52
#define	gxxlfGoto			53
#define	gxxlfHalt			54
#define	gxxlfPv				56
#define	gxxlfFv				57
#define	gxxlfNper			58
#define	gxxlfPmt			59
#define	gxxlfRate			60
#define	gxxlfMirr			61
#define	gxxlfIrr			62
#define	gxxlfRand			63
#define	gxxlfMatch			64
#define	gxxlfDate			65
#define	gxxlfTime			66
#define	gxxlfDay			67
#define	gxxlfMonth			68
#define	gxxlfYear			69
#define	gxxlfWeekday		70
#define	gxxlfHour			71
#define	gxxlfMinute			72
#define	gxxlfSecond			73
#define	gxxlfNow			74
#define	gxxlfAreas			75
#define	gxxlfRows			76
#define	gxxlfColumns		77
#define	gxxlfOffset			78
#define	gxxlfAbsref			79
#define	gxxlfRelref			80
#define	gxxlfArgument		81
#define	gxxlfSearch			82
#define	gxxlfTranspose		83
#define	gxxlfError			84
#define	gxxlfStep			85
#define	gxxlfType			86
#define	gxxlfEcho			87
#define	gxxlfSetName		88
#define	gxxlfCaller			89
#define	gxxlfDeref			90
#define	gxxlfWindows		91
#define	gxxlfSeries			92
#define	gxxlfDocuments		93
#define	gxxlfActiveCell		94
#define	gxxlfSelection		95
#define	gxxlfResult			96
#define	gxxlfAtan2			97
#define	gxxlfAsin			98
#define	gxxlfAcos			99
#define	gxxlfChoose			100
#define	gxxlfHlookup		101
#define	gxxlfVlookup		102
#define	gxxlfLinks			103
#define	gxxlfInput			104
#define	gxxlfIsref			105
#define	gxxlfGetFormula		106
#define	gxxlfGetName		107
#define	gxxlfSetValue		108
#define	gxxlfLog			109
#define	gxxlfExec			110
#define	gxxlfChar			111
#define	gxxlfLower			112
#define	gxxlfUpper			113
#define	gxxlfProper			114
#define	gxxlfLeft			115
#define	gxxlfRight			116
#define	gxxlfExact			117
#define	gxxlfTrim			118
#define	gxxlfReplace		119
#define	gxxlfSubstitute		120
#define	gxxlfCode			121
#define	gxxlfNames			122
#define	gxxlfDirectory		123
#define	gxxlfFind			124
#define	gxxlfCell			125
#define	gxxlfIserr			126
#define	gxxlfIstext			127
#define	gxxlfIsnumber		128
#define	gxxlfIsblank		129
#define	gxxlfT				130
#define	gxxlfN				131
#define	gxxlfFopen			132
#define	gxxlfFclose			133
#define	gxxlfFsize			134
#define	gxxlfFreadln		135
#define	gxxlfFread			136
#define	gxxlfFwriteln		137
#define	gxxlfFwrite			138
#define	gxxlfFpos			139
#define	gxxlfDatevalue		140
#define	gxxlfTimevalue		141
#define	gxxlfSln			142
#define	gxxlfSyd			143
#define	gxxlfDdb			144
#define	gxxlfGetDef			145
#define	gxxlfReftext		146
#define	gxxlfTextref		147
#define	gxxlfIndirect		148
#define	gxxlfRegister		149
#define	gxxlfCall			150
#define	gxxlfAddBar			151
#define	gxxlfAddMenu		152
#define	gxxlfAddCommand		153
#define	gxxlfEnableCommand	154
#define	gxxlfCheckCommand	155
#define	gxxlfRenameCommand	156
#define	gxxlfShowBar		157
#define	gxxlfDeleteMenu		158
#define	gxxlfDeleteCommand	159
#define	gxxlfGetChartItem	160
#define	gxxlfDialogBox		161
#define	gxxlfClean			162
#define	gxxlfMdeterm		163
#define	gxxlfMinverse		164
#define	gxxlfMmult			165
#define	gxxlfFiles			166
#define	gxxlfIpmt			167
#define	gxxlfPpmt			168
#define	gxxlfCounta			169
#define	gxxlfCancelKey		170
#define	gxxlfInitiate		175
#define	gxxlfRequest		176
#define	gxxlfPoke			177
#define	gxxlfExecute		178
#define	gxxlfTerminate		179
#define	gxxlfRestart		180
#define	gxxlfHelp			181
#define	gxxlfGetBar			182
#define	gxxlfProduct		183
#define	gxxlfFact			184
#define	gxxlfGetCell		185
#define	gxxlfGetWorkspace	186
#define	gxxlfGetWindow		187
#define	gxxlfGetDocument	188
#define	gxxlfDproduct		189
#define	gxxlfIsnontext		190
#define	gxxlfGetNote		191
#define	gxxlfNote			192
#define	gxxlfStdevp			193
#define	gxxlfVarp			194
#define	gxxlfDstdevp		195
#define	gxxlfDvarp			196
#define	gxxlfTrunc			197
#define	gxxlfIslogical		198
#define	gxxlfDcounta		199
#define	gxxlfDeleteBar		200
#define	gxxlfUnregister		201
#define	gxxlfUsdollar		204
#define	gxxlfFindb			205
#define	gxxlfSearchb		206
#define	gxxlfReplaceb		207
#define	gxxlfLeftb			208
#define	gxxlfRightb			209
#define	gxxlfMidb			210
#define	gxxlfLenb			211
#define	gxxlfRoundup		212
#define	gxxlfRounddown		213
#define	gxxlfAsc			214
#define	gxxlfDbcs			215
#define	gxxlfRank			216
#define	gxxlfAddress		219
#define	gxxlfDays360		220
#define	gxxlfToday			221
#define	gxxlfVdb			222
#define	gxxlfMedian			227
#define	gxxlfSumproduct		228
#define	gxxlfSinh			229
#define	gxxlfCosh			230
#define	gxxlfTanh			231
#define	gxxlfAsinh			232
#define	gxxlfAcosh			233
#define	gxxlfAtanh			234
#define	gxxlfDget			235
#define	gxxlfCreateObject	236
#define	gxxlfVolatile		237
#define	gxxlfLastError		238
#define	gxxlfCustomUndo		239
#define	gxxlfCustomRepeat	240
#define	gxxlfFormulaConvert	241
#define	gxxlfGetLinkInfo	242
#define	gxxlfTextBox		243
#define	gxxlfInfo			244
#define	gxxlfGroup			245
#define	gxxlfGetObject		246
#define	gxxlfDb				247
#define	gxxlfPause			248
#define	gxxlfResume			251
#define	gxxlfFrequency		252
#define	gxxlfAddToolbar		253
#define	gxxlfDeleteToolbar	254
#define	gxxlfResetToolbar	256
#define	gxxlfEvaluate		257
#define	gxxlfGetToolbar		258
#define	gxxlfGetTool		259
#define	gxxlfSpellingCheck	260
#define	gxxlfErrorType		261
#define	gxxlfAppTitle		262
#define	gxxlfWindowTitle	263
#define	gxxlfSaveToolbar	264
#define	gxxlfEnableTool		265
#define	gxxlfPressTool		266
#define	gxxlfRegisterId		267
#define	gxxlfGetWorkbook	268
#define	gxxlfAvedev			269
#define	gxxlfBetadist		270
#define	gxxlfGammaln		271
#define	gxxlfBetainv		272
#define	gxxlfBinomdist		273
#define	gxxlfChidist		274
#define	gxxlfChiinv			275
#define	gxxlfCombin			276
#define	gxxlfConfidence		277
#define	gxxlfCritbinom		278
#define	gxxlfEven			279
#define	gxxlfExpondist		280
#define	gxxlfFdist			281
#define	gxxlfFinv			282
#define	gxxlfFisher			283
#define	gxxlfFisherinv		284
#define	gxxlfFloor			285
#define	gxxlfGammadist		286
#define	gxxlfGammainv		287
#define	gxxlfCeiling		288
#define	gxxlfHypgeomdist	289
#define	gxxlfLognormdist	290
#define	gxxlfLoginv			291
#define	gxxlfNegbinomdist	292
#define	gxxlfNormdist		293
#define	gxxlfNormsdist		294
#define	gxxlfNorminv		295
#define	gxxlfNormsinv		296
#define	gxxlfStandardize	297
#define	gxxlfOdd			298
#define	gxxlfPermut			299
#define	gxxlfPoisson		300
#define	gxxlfTdist			301
#define	gxxlfWeibull		302
#define	gxxlfSumxmy2		303
#define	gxxlfSumx2my2		304
#define	gxxlfSumx2py2		305
#define	gxxlfChitest		306
#define	gxxlfCorrel			307
#define	gxxlfCovar			308
#define	gxxlfForecast		309
#define	gxxlfFtest			310
#define	gxxlfIntercept		311
#define	gxxlfPearson		312
#define	gxxlfRsq			313
#define	gxxlfSteyx			314
#define	gxxlfSlope			315
#define	gxxlfTtest			316
#define	gxxlfProb			317
#define	gxxlfDevsq			318
#define	gxxlfGeomean		319
#define	gxxlfHarmean		320
#define	gxxlfSumsq			321
#define	gxxlfKurt			322
#define	gxxlfSkew			323
#define	gxxlfZtest			324
#define	gxxlfLarge			325
#define	gxxlfSmall			326
#define	gxxlfQuartile		327
#define	gxxlfPercentile		328
#define	gxxlfPercentrank	329
#define	gxxlfMode			330
#define	gxxlfTrimmean		331
#define	gxxlfTinv			332
#define gxxlfConcatenate	336



#endif // _GXSEXPR_H_
