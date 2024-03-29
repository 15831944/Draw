///////////////////////////////////////////////////////////////////////////////
// Jpegint.h
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
//          Supplement Section 227.7202, Government�s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////

/*
 * jpegint.h
 *
 * Copyright (C) 1991-1995, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file provides common declarations for the various JPEG modules.
 * These declarations are considered internal to the JPEG library; most
 * applications using the library shouldn't need to include this file.
 */

#ifndef __SFL_JPEGINT_H__
#define __SFL_JPEGINT_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

/* Declarations for both compression & decompression */

typedef enum {			/* Operating modes for buffer controllers */
	JBUF_PASS_THRU,		/* Plain stripwise operation */
	/* Remaining modes require a full-image buffer to have been created */
	JBUF_SAVE_SOURCE,	/* Run source subobject only, save output */
	JBUF_CRANK_DEST,	/* Run dest subobject only, using saved data */
	JBUF_SAVE_AND_PASS	/* Run both subobjects, save output */
} J_BUF_MODE;

/* Values of global_state field (jdapi.c has some dependencies on ordering!) */
#define CSTATE_START	100	/* after create_compress */
#define CSTATE_SCANNING	101	/* start_compress done, write_scanlines OK */
#define CSTATE_RAW_OK	102	/* start_compress done, write_raw_data OK */
#define CSTATE_WRCOEFS	103	/* jpeg_write_coefficients done */
#define DSTATE_START	200	/* after create_decompress */
#define DSTATE_INHEADER	201	/* reading header markers, no SOS yet */
#define DSTATE_READY	202	/* found SOS, ready for start_decompress */
#define DSTATE_PRELOAD	203	/* reading multiscan file in start_decompress*/
#define DSTATE_PRESCAN	204	/* performing dummy pass for 2-pass quant */
#define DSTATE_SCANNING	205	/* start_decompress done, read_scanlines OK */
#define DSTATE_RAW_OK	206	/* start_decompress done, read_raw_data OK */
#define DSTATE_BUFIMAGE	207	/* expecting jpeg_start_output */
#define DSTATE_BUFPOST	208	/* looking for SOS/EOI in jpeg_finish_output */
#define DSTATE_RDCOEFS	209	/* reading file in jpeg_read_coefficients */
#define DSTATE_STOPPING	210	/* looking for EOI in jpeg_finish_decompress */


/* Declarations for compression modules */

/* Master control module */
typedef void (SECJpeg::*jpeg_prepare_for_pass)(j_compress_ptr cinfo);
typedef void (SECJpeg::*jpeg_pass_startup)(j_compress_ptr cinfo);
typedef void (SECJpeg::*jpeg_finish_pass)(j_compress_ptr cinfo);
struct FOUNDATION_API  jpeg_comp_master {
	jpeg_prepare_for_pass prepare_for_pass;
	jpeg_pass_startup pass_startup;
	jpeg_finish_pass finish_pass;

  /* State variables made visible to other modules */
  boolean call_pass_startup;	/* True if pass_startup must be called */
  boolean is_last_pass;		/* True during last pass */
};

/* Main buffer control (downsampled-data buffer) */
  typedef void (SECJpeg::*jpeg_start_pass3)(j_compress_ptr cinfo, J_BUF_MODE pass_mode);
  typedef void (SECJpeg::*jpeg_process_data)(j_compress_ptr cinfo,
			       JSAMPARRAY input_buf, JDIMENSION *in_row_ctr,
			       JDIMENSION in_rows_avail);

struct FOUNDATION_API  jpeg_c_main_controller {
	jpeg_start_pass3 start_pass;
	jpeg_process_data process_data;
};

/* Compression preprocessing (downsampling input buffer control) */
  typedef void (SECJpeg::*jpeg_pre_process_data)(j_compress_ptr cinfo,
				   JSAMPARRAY input_buf,
				   JDIMENSION *in_row_ctr,
				   JDIMENSION in_rows_avail,
				   JSAMPIMAGE output_buf,
				   JDIMENSION *out_row_group_ctr,
				   JDIMENSION out_row_groups_avail);

struct FOUNDATION_API  jpeg_c_prep_controller {
	jpeg_start_pass3 start_pass;
	jpeg_pre_process_data pre_process_data;
};

typedef boolean (SECJpeg::*jpeg_compress_data)(j_compress_ptr cinfo,
					JSAMPIMAGE input_buf);
/* Coefficient buffer control */
struct FOUNDATION_API  jpeg_c_coef_controller {
	jpeg_start_pass3 start_pass;
	jpeg_compress_data compress_data;
};

/* Colorspace conversion */
typedef void (SECJpeg::*jpeg_color_convert2)(j_compress_ptr cinfo,
				JSAMPARRAY input_buf, JSAMPIMAGE output_buf,
				JDIMENSION output_row, int num_rows);
typedef void (SECJpeg::*jpeg_start_pass)(j_compress_ptr cinfo);

struct FOUNDATION_API  jpeg_color_converter {
	jpeg_start_pass start_pass;
	jpeg_color_convert2 color_convert;
};

/* Downsampling */
typedef void (SECJpeg::*jpeg_downsample)(j_compress_ptr cinfo,
			     JSAMPIMAGE input_buf, JDIMENSION in_row_index,
			     JSAMPIMAGE output_buf,
			     JDIMENSION out_row_group_index);


struct FOUNDATION_API  jpeg_downsampler {
	jpeg_start_pass start_pass;
	jpeg_downsample downsample;
  boolean need_context_rows;	/* TRUE if need rows above & below */
};

/* Forward DCT (also controls coefficient quantization) */
typedef void (SECJpeg::*jpeg_forward_DCT) (j_compress_ptr cinfo,
			      jpeg_component_info * compptr,
			      JSAMPARRAY sample_data, JBLOCKROW coef_blocks,
			      JDIMENSION start_row, JDIMENSION start_col,
			      JDIMENSION num_blocks);

struct FOUNDATION_API  jpeg_forward_dct {
	jpeg_start_pass start_pass;
  /* perhaps this should be an array??? */
	jpeg_forward_DCT forward_DCT;
};

/* Entropy encoding */
typedef void (SECJpeg::*jpeg_start_pass2)(j_compress_ptr cinfo, boolean gather_statistics);
typedef boolean (SECJpeg::*jpeg_encode_mcu)(j_compress_ptr cinfo, JBLOCKROW *MCU_data);

struct FOUNDATION_API  jpeg_entropy_encoder {
	jpeg_start_pass2 start_pass;
	jpeg_encode_mcu encode_mcu;
	jpeg_finish_pass finish_pass;
};

/* Marker writing */
typedef void (SECJpeg::*jpeg_write_any_marker)(j_compress_ptr cinfo, int marker,
				const JOCTET *dataptr, unsigned int datalen);
typedef void (SECJpeg::*jpeg_write_file_header)(j_compress_ptr cinfo);
typedef void (SECJpeg::*jpeg_write_frame_header)(j_compress_ptr cinfo);
typedef void (SECJpeg::*jpeg_write_scan_header)(j_compress_ptr cinfo);
typedef void (SECJpeg::*jpeg_write_file_trailer)(j_compress_ptr cinfo);
typedef void (SECJpeg::*jpeg_write_tables_only)(j_compress_ptr cinfo);

struct FOUNDATION_API  jpeg_marker_writer {
  /* write_any_marker is exported for use by applications */
  /* Probably only COM and APPn markers should be written */
  jpeg_write_any_marker write_any_marker;
  jpeg_write_file_header write_file_header;
  jpeg_write_frame_header write_frame_header;
  jpeg_write_scan_header write_scan_header;
  jpeg_write_file_trailer write_file_trailer;
  jpeg_write_tables_only write_tables_only;
};


/* Declarations for decompression modules */

/* Master control module */
typedef void (SECJpeg::*jpeg_prepare_for_output_pass)(j_decompress_ptr cinfo);
typedef void (SECJpeg::*jpeg_finish_output_pass)(j_decompress_ptr cinfo);

struct FOUNDATION_API  jpeg_decomp_master {
	jpeg_prepare_for_output_pass prepare_for_output_pass;
	jpeg_finish_output_pass finish_output_pass;

  /* State variables made visible to other modules */
  boolean is_dummy_pass;	/* True during 1st pass for 2-pass quant */
};

/* Input control module */
typedef int (SECJpeg::*jpeg_consume_input2)(j_decompress_ptr cinfo);
typedef void (SECJpeg::*jpeg_reset_input_controller)(j_decompress_ptr cinfo);
typedef void (SECJpeg::*jpeg_start_input_pass)(j_decompress_ptr cinfo);
typedef void (SECJpeg::*jpeg_finish_input_pass)(j_decompress_ptr cinfo);

struct FOUNDATION_API  jpeg_input_controller {
	jpeg_consume_input2 consume_input;
	jpeg_reset_input_controller reset_input_controller;
	jpeg_start_input_pass start_input_pass;
	jpeg_finish_input_pass finish_input_pass;

  /* State variables made visible to other modules */
  boolean has_multiple_scans;	/* True if file has multiple scans */
  boolean eoi_reached;		/* True when EOI has been consumed */
};

/* Main buffer control (downsampled-data buffer) */
typedef void (SECJpeg::*jpeg_process_data2)(j_decompress_ptr cinfo,
			       JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
			       JDIMENSION out_rows_avail);
typedef void (SECJpeg::*jpeg_decode_start_pass3)(j_decompress_ptr cinfo,
					J_BUF_MODE pass_mode);

struct FOUNDATION_API  jpeg_d_main_controller {
	jpeg_decode_start_pass3 start_pass;
	jpeg_process_data2 process_data;
};

/* Coefficient buffer control */
typedef void (SECJpeg::*jpeg_start_input_pass)(j_decompress_ptr cinfo);
typedef int (SECJpeg::*jpeg_consume_data)(j_decompress_ptr cinfo);
typedef void (SECJpeg::*jpeg_start_output_pass)(j_decompress_ptr cinfo);
typedef int (SECJpeg::*jpeg_decompress_data)(j_decompress_ptr cinfo,
				JSAMPIMAGE output_buf);

struct FOUNDATION_API  jpeg_d_coef_controller {
	jpeg_start_input_pass start_input_pass;
	jpeg_consume_data consume_data;
	jpeg_start_output_pass start_output_pass;
	jpeg_decompress_data decompress_data;
  /* Pointer to array of coefficient virtual arrays, or NULL if none */
  jvirt_barray_ptr *coef_arrays;
};

/* Decompression postprocessing (color quantization buffer control) */
typedef void (SECJpeg::*jpeg_post_process_data)(j_decompress_ptr cinfo,
				    JSAMPIMAGE input_buf,
				    JDIMENSION *in_row_group_ctr,
				    JDIMENSION in_row_groups_avail,
				    JSAMPARRAY output_buf,
				    JDIMENSION *out_row_ctr,
				    JDIMENSION out_rows_avail);
struct FOUNDATION_API  jpeg_d_post_controller {
	jpeg_decode_start_pass3 start_pass;
	jpeg_post_process_data post_process_data;
};

/* Marker reading & parsing */
typedef void (SECJpeg::*jpeg_reset_marker_reader)(j_decompress_ptr cinfo);
typedef int (SECJpeg::*jpeg_read_markers)(j_decompress_ptr cinfo);

struct FOUNDATION_API  jpeg_marker_reader {
	jpeg_reset_marker_reader reset_marker_reader;
  /* Read markers until SOS or EOI.
   * Returns same codes as are defined for jpeg_consume_input:
   * JPEG_SUSPENDED, JPEG_REACHED_SOS, or JPEG_REACHED_EOI.
   */
	jpeg_read_markers read_markers;
  /* Read a restart marker --- exported for use by entropy decoder only */
  jpeg_marker_parser_method read_restart_marker;
  /* Application-overridable marker processing methods */
  jpeg_marker_parser_method process_COM;
  jpeg_marker_parser_method process_APPn[16];

  /* State of marker reader --- nominally internal, but applications
   * supplying COM or APPn handlers might like to know the state.
   */
  boolean saw_SOI;		/* found SOI? */
  boolean saw_SOF;		/* found SOF? */
  int next_restart_num;		/* next restart number expected (0-7) */
  unsigned int discarded_bytes;	/* # of bytes skipped looking for a marker */
};

/* Entropy decoding */
typedef BYTE (SECJpeg::*jpeg_decode_mcu)(j_decompress_ptr cinfo,
				JBLOCKROW *MCU_data);

typedef void (SECJpeg::*jpeg_decode_start_pass)(j_decompress_ptr dinfo);

struct FOUNDATION_API  jpeg_entropy_decoder {
	jpeg_decode_start_pass start_pass;
	jpeg_decode_mcu decode_mcu;
};

/* Inverse DCT (also performs dequantization) */
typedef void (SECJpeg::*inverse_DCT_method_ptr) \
		(j_decompress_ptr cinfo, jpeg_component_info * compptr,
		 JCOEFPTR coef_block,
		 JSAMPARRAY output_buf, JDIMENSION output_col);

struct FOUNDATION_API  jpeg_inverse_dct {
	jpeg_decode_start_pass start_pass;
  /* It is useful to allow each component to have a separate IDCT method. */
  inverse_DCT_method_ptr inverse_DCT[MAX_COMPONENTS];
};

/* Upsampling (note that upsampler must also call color converter) */
typedef void (SECJpeg::*jpeg_upsample)(j_decompress_ptr cinfo,
			   JSAMPIMAGE input_buf,
			   JDIMENSION *in_row_group_ctr,
			   JDIMENSION in_row_groups_avail,
			   JSAMPARRAY output_buf,
			   JDIMENSION *out_row_ctr,
			   JDIMENSION out_rows_avail);

struct FOUNDATION_API  jpeg_upsampler {
	jpeg_decode_start_pass start_pass;
	jpeg_upsample upsample;


  boolean need_context_rows;	/* TRUE if need rows above & below */
};

/* Colorspace conversion */
typedef void (SECJpeg::*jpeg_color_convert)(j_decompress_ptr cinfo,
				JSAMPIMAGE input_buf, JDIMENSION input_row,
				JSAMPARRAY output_buf, int num_rows);

struct FOUNDATION_API  jpeg_color_deconverter {
jpeg_decode_start_pass start_pass;
jpeg_color_convert color_convert;
};

/* Color quantization or color precision reduction */
typedef void (SECJpeg::*jpeg_color_quantize2)(j_decompress_ptr cinfo,
				JSAMPARRAY input_buf, JSAMPARRAY output_buf, 
				int num_rows);
typedef void (SECJpeg::*jpeg_d_finish_pass)(j_decompress_ptr cinfo);
typedef void (SECJpeg::*jpeg_new_color_map)(j_decompress_ptr cinfo);
typedef void (SECJpeg::*jpeg_decode_start_pass2)(j_decompress_ptr cinfo,
					boolean is_pre_scan);
struct FOUNDATION_API  jpeg_color_quantizer {
	jpeg_decode_start_pass2 start_pass;
	jpeg_color_quantize2 color_quantize;
	jpeg_d_finish_pass finish_pass;
	jpeg_new_color_map new_color_map;
};


/* Miscellaneous useful macros */

#ifndef MAX
#define MAX(a,b)	((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a,b)	((a) < (b) ? (a) : (b))
#endif

/* We assume that right shift corresponds to signed division by 2 with
 * rounding towards minus infinity.  This is correct for typical "arithmetic
 * shift" instructions that shift in copies of the sign bit.  But some
 * C compilers implement >> with an unsigned shift.  For these machines you
 * must define RIGHT_SHIFT_IS_UNSIGNED.
 * RIGHT_SHIFT provides a proper signed right shift of an INT32 quantity.
 * It is only applied with constant shift counts.  SHIFT_TEMPS must be
 * included in the variables of any routine using RIGHT_SHIFT.
 */

#ifdef RIGHT_SHIFT_IS_UNSIGNED
#define SHIFT_TEMPS	INT32 shift_temp;
#define RIGHT_SHIFT(x,shft)  \
	((shift_temp = (x)) < 0 ? \
	 (shift_temp >> (shft)) | ((~((INT32) 0)) << (32-(shft))) : \
	 (shift_temp >> (shft)))
#else
#define SHIFT_TEMPS
#define RIGHT_SHIFT(x,shft)	((x) >> (shft))
#endif


/* Short forms of external names for systems with brain-damaged linkers. */

#ifdef NEED_SHORT_EXTERNAL_NAMES
#define jinit_compress_master	jICompress
#define jinit_c_master_control	jICMaster
#define jinit_c_main_controller	jICMainC
#define jinit_c_prep_controller	jICPrepC
#define jinit_c_coef_controller	jICCoefC
#define jinit_color_converter	jICColor
#define jinit_downsampler	jIDownsampler
#define jinit_forward_dct	jIFDCT
#define jinit_huff_encoder	jIHEncoder
#define jinit_phuff_encoder	jIPHEncoder
#define jinit_marker_writer	jIMWriter
#define jinit_master_decompress	jIDMaster
#define jinit_d_main_controller	jIDMainC
#define jinit_d_coef_controller	jIDCoefC
#define jinit_d_post_controller	jIDPostC
#define jinit_input_controller	jIInCtlr
#define jinit_marker_reader	jIMReader
#define jinit_huff_decoder	jIHDecoder
#define jinit_phuff_decoder	jIPHDecoder
#define jinit_inverse_dct	jIIDCT
#define jinit_upsampler		jIUpsampler
#define jinit_color_deconverter	jIDColor
#define jinit_1pass_quantizer	jI1Quant
#define jinit_2pass_quantizer	jI2Quant
#define jinit_merged_upsampler	jIMUpsampler
#define jinit_memory_mgr	jIMemMgr
#define jdiv_round_up		jDivRound
#define jround_up		jRound
#define jcopy_sample_rows	jCopySamples
#define jcopy_block_row		jCopyBlocks
#define jzero_far		jZeroFar
#define jpeg_zigzag_order	jZIGTable
#define jpeg_natural_order	jZAGTable
#endif /* NEED_SHORT_EXTERNAL_NAMES */


/* Compression module initialization routines */
EXTERN FOUNDATION_API void jinit_compress_master JPP((j_compress_ptr cinfo));
EXTERN FOUNDATION_API void jinit_c_master_control JPP((j_compress_ptr cinfo,
					boolean transcode_only));
EXTERN FOUNDATION_API void jinit_c_main_controller JPP((j_compress_ptr cinfo,
					 boolean need_full_buffer));
EXTERN FOUNDATION_API void jinit_c_prep_controller JPP((j_compress_ptr cinfo,
					 boolean need_full_buffer));
EXTERN FOUNDATION_API void jinit_c_coef_controller JPP((j_compress_ptr cinfo,
					 boolean need_full_buffer));
EXTERN FOUNDATION_API void jinit_color_converter JPP((j_compress_ptr cinfo));
EXTERN FOUNDATION_API void jinit_downsampler JPP((j_compress_ptr cinfo));
EXTERN FOUNDATION_API void jinit_forward_dct JPP((j_compress_ptr cinfo));
EXTERN FOUNDATION_API void jinit_huff_encoder JPP((j_compress_ptr cinfo));
EXTERN FOUNDATION_API void jinit_phuff_encoder JPP((j_compress_ptr cinfo));
EXTERN FOUNDATION_API void jinit_marker_writer JPP((j_compress_ptr cinfo));
/* Decompression module initialization routines */
EXTERN FOUNDATION_API void jinit_master_decompress JPP((j_decompress_ptr cinfo));
EXTERN FOUNDATION_API void jinit_d_main_controller JPP((j_decompress_ptr cinfo,
					 boolean need_full_buffer));
EXTERN FOUNDATION_API void jinit_d_coef_controller JPP((j_decompress_ptr cinfo,
					 boolean need_full_buffer));
EXTERN FOUNDATION_API void jinit_d_post_controller JPP((j_decompress_ptr cinfo,
					 boolean need_full_buffer));
EXTERN FOUNDATION_API void jinit_input_controller JPP((j_decompress_ptr cinfo));
EXTERN FOUNDATION_API void jinit_marker_reader JPP((j_decompress_ptr cinfo));
EXTERN FOUNDATION_API void jinit_huff_decoder JPP((j_decompress_ptr cinfo));
EXTERN FOUNDATION_API void jinit_phuff_decoder JPP((j_decompress_ptr cinfo));
EXTERN FOUNDATION_API void jinit_inverse_dct JPP((j_decompress_ptr cinfo));
EXTERN FOUNDATION_API void jinit_upsampler JPP((j_decompress_ptr cinfo));
EXTERN FOUNDATION_API void jinit_color_deconverter JPP((j_decompress_ptr cinfo));
EXTERN FOUNDATION_API void jinit_1pass_quantizer JPP((j_decompress_ptr cinfo));
EXTERN FOUNDATION_API void jinit_2pass_quantizer JPP((j_decompress_ptr cinfo));
EXTERN FOUNDATION_API void jinit_merged_upsampler JPP((j_decompress_ptr cinfo));
/* Memory manager initialization */
EXTERN FOUNDATION_API void jinit_memory_mgr JPP((j_common_ptr cinfo));

/* Utility routines in jutils.c */
EXTERN FOUNDATION_API long jdiv_round_up JPP((long a, long b));
EXTERN FOUNDATION_API long jround_up JPP((long a, long b));
EXTERN FOUNDATION_API void jcopy_sample_rows JPP((JSAMPARRAY input_array, int source_row,
				   JSAMPARRAY output_array, int dest_row,
				   int num_rows, JDIMENSION num_cols));
EXTERN FOUNDATION_API void jcopy_block_row JPP((JBLOCKROW input_row, JBLOCKROW output_row,
				 JDIMENSION num_blocks));
EXTERN FOUNDATION_API void jzero_far JPP((void FAR * target, size_t bytestozero));
/* Constant tables in jutils.c */
extern const int jpeg_zigzag_order[DCTSIZE2]; /* natural coef order to zigzag order */
extern const int jpeg_natural_order[DCTSIZE2+16]; /* zigzag coef order to natural order */

/* Suppress undefined-structure complaints if necessary. */

#ifdef INCOMPLETE_TYPES_BROKEN
#ifndef AM_MEMORY_MANAGER	/* only jmemmgr.c defines these */
 struct jvirt_sarray_control { long dummy; };
 struct jvirt_barray_control { long dummy; };
#endif
#endif /* INCOMPLETE_TYPES_BROKEN */


};  // namespace stingray::foundation
};  // namespace stingray


#endif /* __SFL_JPEGINT_H__ */