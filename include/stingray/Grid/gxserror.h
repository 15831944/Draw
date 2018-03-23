///////////////////////////////////////////////////////////////////////////////
// gxserror.h : Formula Engine Errors
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

#ifndef _GXSERROR_H_
#define _GXSERROR_H_

#define GX_UNKNOWN_ERROR                     0
#define GX_MAX_FORMS_ERROR                   1
#define GX_MAX_VIEWS_ERROR                   2
#define GX_BAD_COLUMN_WIDTH                  3
#define GX_BAD_ROW_HEIGHT                    4
#define GX_OUT_OF_MEMORY                     5
#define GX_BAD_RANGE                         6
#define GX_BAD_ADDRESS                       7
#define GX_BAD_FILE_WRITE                    8
#define GX_BAD_FILE_READ                     9
#define GX_BAD_COLOR                        10
#define GX_BAD_FONT                         11
#define GX_TITLES_LOCKED                    12
#define GX_TITLES_NOT_LOCKED                13
#define GX_NO_TITLES_CHOSEN                 14
#define GX_UNSUPPORTED_OPTION               15
#define GX_V2_OPEN_ERROR                    16
#define GX_V2_FORMAT_ERROR                  17
#define GX_WKS_FILE_ERR                     18
#define GX_XLS_FILE_ERR                     19
#define GX_BAD_RANGE_NAME                   20
#define GX_MAX_GE_ERROR                     21
#define GX_MAX_GV_ERROR                     22
#define GX_GRAPH_DELETE                     23
#define GX_GRAPH_EDIT                       24
#define GX_GRAPH_VIEW                       25
#define GX_GRAPH_INSERT                     26
#define GX_GRAPH_DELETE_MESSAGE             27
#define GX_NO_HELP_FILE                     28
#define GX_NO_HELP_TOPIC                    29
#define GX_NO_FIND                          30
#define GX_SUCCESS_SAVE                     31
#define GX_NO_VERSION_2                     32
#define GX_UNSAVED_GRAPHS                   33
#define GX_LICENSE_ERROR                    34
#define GX_FATAL_X_ERROR                    35
#define GX_X_ERROR                          36
#define GX_BAD_TC_RANGE                     37
#define GX_BAD_TR_RANGE                     38
#define GX_FN_ERR_F_GE_0                    39
#define GX_FN_ERR_IEEE_INF_NAN              40
#define GX_FN_ERR_SELF_REF                  41
#define GX_FN_ERR_L_P_INT                   42
#define GX_FN_ERR_L_GT_0                    43
#define GX_FN_ERR_PV_FV_NE_0                44
#define GX_FN_ERR_PV_FV_SIGN                45
#define GX_FN_ERR_PMT_FV_SIGN               46
#define GX_FN_ERR_PMT_NE_0                  47
#define GX_FN_ERR_P_GE_0                    48
#define GX_FN_ERR_P_INT_GT_0                49
#define GX_FN_ERR_R_INT_GT_NEG_1            50
#define GX_FN_ERR_R_NE_0                    51
#define GX_FN_ERR_ARG_IS_NEG                52
#define GX_FN_ERR_ARG_INT                   53
#define GX_FN_ERR_ARG_CELL_OR_RNG           54
#define GX_FN_ERR_ARG_OUT_OF_RNG            55
#define GX_FN_ERR_ARG_NUMERIC               56
#define GX_FN_ERR_COND_STR_PARSE            57
#define GX_FN_ERR_CF_RANGE                  58
#define GX_FN_ERR_CF_COL_OR_ROW             59
#define GX_FN_ERR_CELL_ERROR                60
#define GX_FN_ERR_LIN_DEP                   61
#define GX_FN_ERR_OFF_OUT_OF_RNG            62
#define GX_FN_ERR_NO_REAL_ROOT              63
#define GX_FN_ERR_CNT_LT_0                  64
#define GX_FN_ERR_DS_GE_3                   65
#define GX_FN_ERR_DS_GE_DP2                 66
#define GX_FN_ERR_PLACES                    67
#define GX_FN_ERR_DF_GT_0                   68
#define GX_FN_ERR_DIM_POW_2                 69
#define GX_FN_ERR_DIV_0                     70
#define GX_FN_ERR_NO_ARGS                   71
#define GX_FN_ERR_DOMAIN_M1_1_NE            72
#define GX_FN_ERR_DOMAIN_M1_1               73
#define GX_FN_ERR_DOMAIN_0_170              74
#define GX_FN_ERR_DOMAIN_0_33               75
#define GX_FN_ERR_DOMAIN_GT_0               76
#define GX_FN_ERR_DOMAIN_GE_1               77
#define GX_FN_ERR_ALARM_ERROR               78
#define GX_FN_ERR_REGEX                     79
#define GX_FN_ERR_EXPECT_FN                 80
#define GX_FN_ERR_EXPECT_OPRND              81
#define GX_FN_ERR_EXPECT_OPRTR              82
#define GX_FN_ERR_EXTRAN_OPRNDS             83
#define GX_FN_ERR_R_NUMERIC                 84
#define GX_FN_ERR_FIRST_NUMERIC             85
#define GX_FN_ERR_FLOAT                     86
#define GX_FN_ERR_FN_STK_OVFL               87
#define GX_FN_ERR_HEX_GT_32B                88
#define GX_FN_ERR_ILLEGAL_REF               89
#define GX_FN_ERR_OPRND_OF_NE               90
#define GX_FN_ERR_OPRND_OF_AMPSD            91
#define GX_FN_ERR_OPRND_OF_LE               92
#define GX_FN_ERR_OPRND_OF_LT               93
#define GX_FN_ERR_OPRND_OF_EE               94
#define GX_FN_ERR_OPRND_OF_GE               95
#define GX_FN_ERR_OPRND_OF_GT               96
#define GX_FN_ERR_IMPROP_ARG_VALUE          97
#define GX_FN_ERR_IMPROP_ARG_TYPE           98
#define GX_FN_ERR_IMPROP_ARG_TYPE1          99
#define GX_FN_ERR_IMPROP_ARG_TYPE2         100
#define GX_FN_ERR_IMPROP_ARG_TYPE3         101
#define GX_FN_ERR_IMPROP_COEF_TYPE         102
#define GX_FN_ERR_IMPROP_DIM               103
#define GX_FN_ERR_MATRIX_DIMS              104
#define GX_FN_ERR_RANGE_DIMS               105
#define GX_FN_ERR_INDEX_COL_E_CELL         106
#define GX_FN_ERR_INDEX_OUT_OF_RNG         107
#define GX_FN_ERR_INDEX_ROW_E_CELL         108
#define GX_FN_INT_OUT_OF_RNG               109
#define GX_FN_ERR_INVALID_CELL_REF         110
#define GX_FN_ERR_INVALID_DATE             111
#define GX_FN_ERR_INVALID_RNG_REF          112
#define GX_FN_ERR_TIME                     113
#define GX_FN_ERR_ARG_CNT_LT_2             114
#define GX_FN_ERR_BAD_LOOKUP               115
#define GX_FN_ERR_MAGNITUDE                116
#define GX_FN_ERR_SING                     117
#define GX_FN_ERR_SQUARE                   118
#define GX_FN_ERR_SYMMETRY                 119
#define GX_FN_ERR_MISSING_COND             120
#define GX_FN_ERR_INCMPLT_COND             121
#define GX_FN_ERR_MOD_DIV_0                122
#define GX_FN_ERR_PLACES_M15_15            123
#define GX_FN_ERR_C_GE_S_GE_0              124
#define GX_FN_ERR_L_GE_P_GE_1              125
#define GX_FN_ERR_2_CASH_FLOWS             126
#define GX_FN_ERR_NON_HEX_DIGITS           127
#define GX_FN_ERR_NON_NUM_OPRND            128
#define GX_FN_ERR_NON_NUM_CASH_FL          129
#define GX_FN_ERR_NON_NUM_IN_MTRX          130
#define GX_FN_ERR_NON_NUM_IN_VEC           131
#define GX_FN_ERR_1_ARG_NE_0               132
#define GX_FN_ERR_OPRND_ERR                133
#define GX_FN_ERR_OP_EQ_0                  134
#define GX_FN_ERR_INDEX_OPS_EQ_0           135
#define GX_FN_ERR_OP_GT_32_BITS            136
#define GX_FN_ERR_OP_LE_0                  137
#define GX_FN_ERR_OP_OUT_OF_RANGE          138
#define GX_FN_ERR_OPRND_STK_OVFL           139
#define GX_FN_ERR_OPRNDS_OF_AMPSD          140
#define GX_FN_ERR_OPRNDS_OF_DOTDOT         141
#define GX_FN_ERR_OPRTR_STK_OVFL           142
#define GX_FN_ERR_DEGREE_1_10              143
#define GX_FN_ERR_POOL_LT_3                144
#define GX_FN_ERR_POP_LT_1                 145
#define GX_FN_ERR_RNG_DIM_EQ               146
#define GX_FN_ERR_R_LT_M1                  147
#define GX_FN_ERR_RECUR_TOO_DEEP           148
#define GX_FN_ERR_RESULT_IS_RNG            149
#define GX_FN_ERR_STR_TOO_LONG             150
#define GX_FN_ERR_ROW_OUT_OF_RNG           151
#define GX_FN_ERR_SAMPLE_MISSING           152
#define GX_FN_ERR_SAMPLE_SIZE_LT_1         153
#define GX_FN_ERR_SAMPLE_SIZE_LT_2         154
#define GX_FN_ERR_SEL_OUT_OF_RNG           155
#define GX_FN_ERR_STR_RESULT               156
#define GX_FN_ERR_SUBSTR_GT_STR            157
#define GX_FN_ERR_SUBSTR_NOT_FOUND         158
#define GX_FN_ERR_TOO_FEW_ARGS             159
#define GX_FN_ERR_TOO_MANY_ARGS            160
#define GX_FN_ERR_UNEXP_QSTN               161
#define GX_FN_ERR_UNKNOWN_FMT              162
#define GX_FN_ERR_UNM_LEFT_PAREN           163
#define GX_FN_ERR_UNM_RIGHT_PAREN          164
#define GX_FN_ERR_ARG_CNT_WRONG            165
#define GX_FN_ERR_FN_NOT_INSTALLED         166
#define GX_FN_ERR_REMOTE                   167
#define GX_FN_ERR_X_FILE_OPEN              168
#define GX_XS3_INVALID_MODE                169
#define GX_XS3_OPEN_FAIL                   170
#define GX_XS3_NOT                         171
#define GX_XS3_READ_EOF                    172
#define GX_XS3_READ_FAIL                   173
#define GX_XS3_BAD_CONTINUE                174
#define GX_XS3_BAD_REC                     175
#define GX_XS3_MAX_OPTS                    176
#define GX_XS3_WRITE_FAIL                  177
#define GX_XS3_LINE_TOO_LONG               178
#define GX_XS3_OPT_DECODE                  179
#define GX_XS3_OPT_BOUNDS                  180
#define GX_XS3_REC_DECODE                  181
#define GX_XS3_REC_BOUNDS                  182
#define GX_XS3_BAD_VIEW_RANGE              183
#define GX_XS3_BAD_CELL_ID                 184
#define GX_XS3_V_OPT_IN_NOT_ALLOWED        185
#define GX_XS3_LABEL_MISSING_START_QUOTE   186
#define GX_XS3_LABEL_MISSING_END_QUOTE     187
#define GX_XS3_OPTION_UNKNOWN              188
#define GX_XS3_RECTYPE_UNKNOWN             189
#define GX_XS3_SUBTYPE_UNKNOWN             190
#define GX_XS3_MISSING_X_REC               191
#define GX_XS3_BAD_GRAPH_INDEX             192
#define GX_XS3_BAD_DATASET                 193
#define GX_XS3_BAD_CURR_STYLE_INDEX        194
#define GX_GS_TARGET_ERROR                 195
#define GX_NO_FILE_SPECFD                  196
#define GX_NO_FILE_ACCESS                  197
#define GX_FILE_NOT_XS3                    198
#define GX_FILE_NOT_XS                     199
#define GX_FILE_NOT_WK1                    200
#define GX_FILE_NOT_WKS                    201
#define GX_FILE_NOT_XLS                    202
#define GX_FILE_OLD_XLS_VERSION            203
#define GX_PASSWD_NOT_SUPPORTED            204
#define GX_CP_ERR_SRC_DST                  205
#define GX_PROTECT_ALTER_ERR               206
#define GX_PROTECT_EDIT_ERR                207
#define GX_NOT_ALLOWED_W_PROTECT           208
#define GX_NO_CC_W_AS_NEED                 209
#define GX_NO_IT_W_AS_NEED                 210
#define GX_INSERT_WOULD_ERASE_ALL          211
#define GX_DELETE_WOULD_ERASE_ALL          212
#define GX_SEARCH_PARSE_ERR                213
#define GX_EXTRACT_PARSE_ERR               214
#define GX_LIC_READ_ERR                    215
#define GX_LIC_EXPIRED_ERR                 216
#define GX_LIC_PLATFORM_ERR                217
#define GX_LIC_DOMAIN_ERR                  218
#define GX_LIC_INVALID_ERR                 219
#define GX_LIC_DISPLAY_ERR                 220
#define GX_LIC_CELL_LIMIT                  221
#define GX_LIC_LOST_CONTACT_ERR            222
#define GX_SCAN_ERR_BAD_CHAR               223
#define GX_SCAN_ERR_INVALID_LOTUS          224
#define GX_PARSE_ERR_UNEXPECTED            225
#define GX_PARSE_ERR_BAD_CELL              226
#define GX_PARSE_ERR_UNDEF_FN              227
#define GX_PARSE_ERR_INTERNAL_FREE         228
#define GX_PARSE_ERR_TOO_MANY_ARGS         229
#define GX_PARSE_ERR_TOO_FEW_ARGS          230
#define GX_PARSE_ERR_T_SEMICOLON           231
#define GX_PARSE_ERR_T_COLON               232
#define GX_PARSE_ERR_T_COMMA               233
#define GX_PARSE_ERR_T_QMARK               234
#define GX_PARSE_ERR_T_POUND               235
#define GX_PARSE_ERR_T_BACKSLASH           236
#define GX_PARSE_ERR_T_PLUS                237
#define GX_PARSE_ERR_T_MINUS               238
#define GX_PARSE_ERR_T_STAR                239
#define GX_PARSE_ERR_T_SLASH               240
#define GX_PARSE_ERR_T_PERCENT             241
#define GX_PARSE_ERR_T_BAR                 242
#define GX_PARSE_ERR_T_CARET               243
#define GX_PARSE_ERR_T_AMPERSAND           244
#define GX_PARSE_ERR_T_BANG                245
#define GX_PARSE_ERR_T_TILDE               246
#define GX_PARSE_ERR_T_LANGLE              247
#define GX_PARSE_ERR_T_RANGLE              248
#define GX_PARSE_ERR_T_LPAREN              249
#define GX_PARSE_ERR_T_RPAREN              250
#define GX_PARSE_ERR_T_LBRACE              251
#define GX_PARSE_ERR_T_RBRACE              252
#define GX_PARSE_ERR_T_EQUAL               253
#define GX_PARSE_ERR_T_D_STAR              254
#define GX_PARSE_ERR_T_D_AMPERSAND         255
#define GX_PARSE_ERR_T_D_BAR               256
#define GX_PARSE_ERR_T_D_LANGLE            257
#define GX_PARSE_ERR_T_D_RANGLE            258
#define GX_PARSE_ERR_T_LANGLE_EQUAL        259
#define GX_PARSE_ERR_T_RANGLE_EQUAL        260
#define GX_PARSE_ERR_T_BANG_EQUAL          261
#define GX_PARSE_ERR_T_EQUAL_EQUAL         262
#define GX_PARSE_ERR_T_DOT_DOT             263
#define GX_PARSE_ERR_T_CELL                264
#define GX_PARSE_ERR_T_NAME                265
#define GX_PARSE_ERR_T_FUNCTION            266
#define GX_PARSE_ERR_T_STRING              267
#define GX_PARSE_ERR_T_NUMBER              268
#define GX_PARSE_ERR_T_HEX_NUMBER          269
#define GX_PARSE_ERR_T_COMMENT             270
#define GX_PARSE_ERR_T_END_OF_EXPR         271
#define GX_PARSE_ERR_T_ERROR               272
#define GX_PARSE_ERR_T_DOT                 273
#define GX_PARSE_ERR_PRIMARY               274
#define GX_PARSE_ERR_RANGE_RHS             275
#define GX_PARSE_ERR_CONSTR_NA             276
#define GX_PARSE_ERR_BAD_OFFSET            277
#define GX_PARSE_ERR_BAD_OPRTR             278
#define GX_PARSE_ERR_OPRTR_NA              279
#define GX_PARSE_ERR_TOK_BUF_OVFL          280
#define GX_PARSE_ERR_BAD_NAME              281
#define GX_PARSE_ERR_BAD_NUM               282
#define GX_FN_ERR_NAME_USED                283
#define GX_FN_ERR_UNCONSUMED               284
#define GX_FN_ERR_SP_LS_1                  285
#define GX_FN_ERR_EP_LS_1                  286
#define GX_FN_ERR_SP_GT_EP                 287
#define GX_FN_ERR_INV_PER                  288
#define GX_FN_ERR_FRAC_LE_0                289
#define GX_FN_ERR_INTR_LE_0                290
#define GX_FN_ERROR_NPERY_LS_1             291
#define GX_FN_ERR_SDT_GE_MDT               292
#define GX_FN_ERR_IDT_GT_SDT               293
#define GX_FN_ERR_INVALID_BASIS            294
#define GX_FN_ERR_INVALID_FQ               295
#define GX_FN_ERR_DT_COL_OR_ROW            296
#define GX_FN_ERR_VA_DT_DIMS               297
#define GX_FN_ERR_ODD1                     298
#define GX_FN_ERR_ODD2                     299
#define GX_FN_ERR_NO_MODE                  300
#define GX_FN_ERR_NUM_NOT_IN_LIST          301
#define GX_FN_ERR_STR_MATCH                302
#define GX_FN_ERR_NO_MATCH                 303
#define GX_FN_ERR_MIRR_CF                  304
#define GX_FN_ERR_INVALID_TBILL            305
#define GX_FN_ERR_INVALID_TBL              306
#define GX_FN_ERR_NO_INTERP                307
#define GX_FN_ERR_CF_DTS                   308
#define GX_FN_ERR_INTS_COL_OR_ROW          309
#define GX_FN_ERR_ERF_LLIMIT               310
#define GX_FN_ERR_ERF_ULIMIT               311
#define GX_FN_ERR_PERMUT                   312
#define GX_FN_ERR_NEG_FINA_ARG             313
#define GX_GR_NON_OBJECT                   314
#define GX_GR_BAD_CMD                      315
#define GX_GR_BAD_NUM_STRING               316
#define GX_GR_UNEXPECTED_NUM               317
#define GX_GR_TOO_FEW_TICS                 318
#define GX_GR_LOG_OF_NEG_MAX               319
#define GX_GR_LOG_OF_NEG_MIN               320
#define GX_GR_BAD_DATA_RANGE               321
#define GX_GR_ROW_NOT_ALLOWED              322
#define GX_GR_COL_NOT_ALLOWED              323
#define GX_GR_BLOCK_NOT_ALLOWED            324
#define GX_GR_NO_HIST_BINS                 325
#define GX_GR_ZERO_RNG_HIST                326
#define GX_GR_PIE_RNG_MISMATCH             327
#define GX_GR_XY_RNG_MISMATCH              328
#define GX_GR_XYZ_RNG_MISMATCH             329
#define GX_GR_XY_DATA_MISMATCH             330
#define GX_GR_XY_ACC_NONNUMERIC            331
#define GX_GR_NEG_DIM_ALLOC                332
#define GX_GR_NEG_DIM_FREE                 333
#define GX_GR_NULL_FREE                    334
#define GX_GR_SURF_XMIN_TOO_HIGH           335
#define GX_GR_SURF_XMAX_TOO_LOW            336
#define GX_GR_SURF_YMIN_TOO_HIGH           337
#define GX_GR_SURF_YMAX_TOO_LOW            338
#define GX_GR_SURF_ZMIN_TOO_HIGH           339
#define GX_GR_SURF_ZMAX_TOO_LOW            340
#define GX_GR_UNKNOWN_IDRAW                341
#define GX_GR_NO_MARKER_POSTSCRIPT         342
#define GX_GR_BAD_GRAPH_TYPE               343
#define GX_GR_BAD_SI_OR_GI                 344
#define GX_GR_TOO_FEW_SPLINE_POINTS        345
#define GX_GR_NEG_PIE_DATA                 346
#define GX_GR_PIE_DATA_TOO_LARGE           347
#define GX_GR_PIE_DATA_TOO_SMALL           348
#define GX_GR_TOO_FEW_PLANE_POINTS         349
#define GX_GR_NON_PLANAR_PART              350
#define GX_GR_STRANGE_3D_PT                351
#define GX_GR_TEXT_BEG_WITH_SUBSCR         352
#define GX_GR_TEXT_END_WITH_SUBSCR         353
#define GX_GR_TEXT_END_WITH_SUPER          354
#define GX_GR_TEXT_END_WITH_BSLASH         355
#define GX_GR_MISMATCHED_BRACES            356
#define GX_GR_MISPLACED_CL_BRACE           357
#define GX_GR_MISPLACED_NL                 358
#define GX_GR_WINDOW_TOO_SMALL             359
#define GX_GR_COMPASS_TOO_SMALL            360
#define GX_GR_DEGENERATE_BARS              361
#define GX_GR_TOO_FEW_CONTOURS             362
#define GX_GR_VECNORM_ERROR                363
#define GX_GR_MAKE_NULL_LIST               364
#define GX_GR_REMOVE_NULL_LIST             365
#define GX_GR_REMOVE_NULL_ITEM             366
#define GX_GR_SEARCH_NULL_LIST             367
#define GX_GR_SEARCH_FUNC_NULL             368
#define GX_GR_SHOW_NULL_LIST               369
#define GX_GR_SHOW_FUNC_NULL               370
#define GX_GR_UNKNOWN_TYPE                 371
#define GX_GR_INFINITE_ERR                 372
#define GX_GR_INFINITESIMAL_ERR            373
#define GX_GR_LOG_OF_NEG_DATA              374
#define GX_GR_NON_STRING                   375
#define GX_GR_UNPLACED_ANNOT               376
#define GX_GR_ERROR_CELL                   377
#define GX_GR_NULL_WINDOW                  378
#define GX_GR_SKEW_DISABLE                 379
#define GX_GR_SKEW_ENABLE                  380
#define GX_REG_ERR_BADDFA                   381
#define GX_MAX_ERRORS                      381


#define GX_FATAL_ERROR  0
#define GX_SERIOUS_ERROR    50
#define GX_MINOR_ERROR  1000
#define GX_DATA_ERROR   1001
#define GX_CLEAR_ERROR  10000

#define GX_ERROR_FILE   1
#define GX_ERROR_LINE   2
#define GX_ERROR_DIALOG 4
#define GX_ERROR_BOX    8
#define GX_ERROR_ALL    GX_ERROR_FILE | GX_ERROR_LINE | GX_ERROR_DIALOG | GX_ERROR_BOX

extern void __cdecl _gx_xs_error(int si, int severity, int audience,
                                 LPCTSTR tag, int err, LPTSTR text);

extern "C" GRID_API LPCTSTR __cdecl _gx_xs_error_msg(int err);

extern void __cdecl _gx_silence_xs_error(int state);

extern int __cdecl _gx_get_xs_error_status(void);

extern int __cdecl _gx_get_xs_error_code(void);

#endif //_GXSERROR_H_
