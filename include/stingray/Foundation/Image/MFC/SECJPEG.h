////////////////////////////////////////////////////////////////////////////////
// SECJPEG.h
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
// CHANGELOG: 
//
//    AAB	7/03/95	Started
//    AAB	2/01/95	update to JPEG v.6
//

#ifndef __SFL_SECJPEG_H__
#define __SFL_SECJPEG_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

//
// CMN Extension DLL
// Initialize declaration context
//

#ifdef _SFLDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SFL_DATAEXT
#endif //_SFLDLL

#ifndef __SFL_SECIMAGE_H__
#include "Foundation\Image\MFC\secimage.h"
#endif

#ifndef __SFL_JPEGLIB_H__
#include "Foundation\Image\MFC\jpeglib.h"
#endif

#ifndef __SFL_JINCLUDE_H__
#include "Foundation\Image\MFC\jinclude.h"
#endif

//AAB #include "jpegint.h"

#ifndef __SFL_JMEMSYS_H__
#include "Foundation\Image\MFC\jmemsys.h"
#endif

#ifndef __SFL_JDHUFF_H__
#include "Foundation\Image\MFC\jdhuff.h"
#endif

#ifndef __SFL_JCHUFF_H__
#include "Foundation\Image\MFC\jchuff.h"
#endif

#ifndef __SFL_JDCT_H__
#include "Foundation\Image\MFC\jdct.h"
#endif

#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {


//typedefs needed here for class prototype fxns.
// from jquant1.cpp
#define ODITHER_SIZE  16	/* dimension of dither matrix */
/* NB: if ODITHER_SIZE is not a power of 2, ODITHER_MASK uses will break */
#define ODITHER_CELLS (ODITHER_SIZE*ODITHER_SIZE)	/* # cells in matrix */
#define ODITHER_MASK  (ODITHER_SIZE-1) /* mask for wrapping around counters */

typedef int ODITHER_MATRIX[ODITHER_SIZE][ODITHER_SIZE];
typedef int (*ODITHER_MATRIX_PTR)[ODITHER_SIZE];


// jchuff.cpp
/* Expanded entropy encoder object for Huffman encoding.
 *
 * The savable_state subrecord contains fields that change within an MCU,
 * but must not be updated permanently until we complete the MCU.
 */
typedef struct {
  JSECINT32 put_buffer;		/* current bit-accumulation buffer */
  int put_bits;			/* # of bits now in it */
  int last_dc_val[MAX_COMPS_IN_SCAN]; /* last DC coef for each component */
} comp_savable_state;


/* Working state while writing an MCU.
 * This struct contains all the fields that are needed by subroutines.
 */

typedef struct {
  JOCTET * next_output_byte;	/* => next byte to write in buffer */
  size_t free_in_buffer;	/* # of byte spaces remaining in buffer */
  comp_savable_state cur;		/* Current bit buffer & DC state */
  j_compress_ptr cinfo;		/* dump_buffer needs access to this */
} comp_working_state;

//jcmarker.cpp
typedef enum {			/* JPEG marker codes */
  M_SOF0  = 0xc0,
  M_SOF1  = 0xc1,
  M_SOF2  = 0xc2,
  M_SOF3  = 0xc3,
  
  M_SOF5  = 0xc5,
  M_SOF6  = 0xc6,
  M_SOF7  = 0xc7,
  
  M_JPG   = 0xc8,
  M_SOF9  = 0xc9,
  M_SOF10 = 0xca,
  M_SOF11 = 0xcb,
  
  M_SOF13 = 0xcd,
  M_SOF14 = 0xce,
  M_SOF15 = 0xcf,
  
  M_DHT   = 0xc4,
  
  M_DAC   = 0xcc,
  
  M_RST0  = 0xd0,
  M_RST1  = 0xd1,
  M_RST2  = 0xd2,
  M_RST3  = 0xd3,
  M_RST4  = 0xd4,
  M_RST5  = 0xd5,
  M_RST6  = 0xd6,
  M_RST7  = 0xd7,
  
  M_SOI   = 0xd8,
  M_EOI   = 0xd9,
  M_SOS   = 0xda,
  M_DQT   = 0xdb,
  M_DNL   = 0xdc,
  M_DRI   = 0xdd,
  M_DHP   = 0xde,
  M_EXP   = 0xdf,
  
  M_APP0  = 0xe0,
  M_APP1  = 0xe1,
  M_APP2  = 0xe2,
  M_APP3  = 0xe3,
  M_APP4  = 0xe4,
  M_APP5  = 0xe5,
  M_APP6  = 0xe6,
  M_APP7  = 0xe7,
  M_APP8  = 0xe8,
  M_APP9  = 0xe9,
  M_APP10 = 0xea,
  M_APP11 = 0xeb,
  M_APP12 = 0xec,
  M_APP13 = 0xed,
  M_APP14 = 0xee,
  M_APP15 = 0xef,
  
  M_JPG0  = 0xf0,
  M_JPG13 = 0xfd,
  M_COM   = 0xfe,
  
  M_TEM   = 0x01,
  
  M_ERROR = 0x100
} COMP_JPEG_MARKER;

//jdmarker.cpp


// jcphuff.cpp
typedef struct {
  struct jpeg_entropy_encoder pub; /* public fields */

  /* Mode flag: TRUE for optimization, FALSE for actual data output */
  boolean gather_statistics;

  /* Bit-level coding status.
   * next_output_byte/free_in_buffer are local copies of cinfo->dest fields.
   */ 
  boolean aab_filler;
  JOCTET * next_output_byte;	/* => next byte to write in buffer */
  size_t free_in_buffer;	/* # of byte spaces remaining in buffer */
  JSECINT32 put_buffer;		/* current bit-accumulation buffer */
  int put_bits;			/* # of bits now in it */
  j_compress_ptr cinfo;		/* link to cinfo (needed for dump_buffer) */

  /* Coding status for DC components */
  int last_dc_val[MAX_COMPS_IN_SCAN]; /* last DC coef for each component */

  /* Coding status for AC components */
  int ac_tbl_no;		/* the table number of the single component */
  unsigned int EOBRUN;		/* run length of EOBs */
  unsigned int BE;		/* # of buffered correction bits before MCU */
  char * bit_buffer;		/* buffer for correction bits (1 per char) */
  /* packing correction bits tightly would save some space but cost time... */

  unsigned int restarts_to_go;	/* MCUs left in this restart interval */
  int next_restart_num;		/* next restart number to write (0-7) */

  /* Pointers to derived tables (these workspaces have image lifespan).
   * Since any one scan codes only DC or only AC, we only need one set
   * of tables, not one for DC and one for AC.
   */
  c_derived_tbl * derived_tbls[NUM_HUFF_TBLS];

  /* Statistics tables for optimization; again, one set is enough */
  long * count_ptrs[NUM_HUFF_TBLS];
} cp_phuff_entropy_encoder;
typedef cp_phuff_entropy_encoder * cp_phuff_entropy_ptr;

// jquant2.cpp
typedef struct {
  /* The bounds of the box (inclusive); expressed as histogram indexes */
  int c0min, c0max;
  int c1min, c1max;
  int c2min, c2max;
  /* The volume (actually 2-norm) of the box */
  JSECINT32 volume;
  /* The number of nonzero histogram cells within this box */
  long colorcount;
} sec_box;

typedef sec_box * boxptr;


/////////////////////////////
// AutoDuck tag block block for SECJpeg
//@doc SECJpeg
//@mdata long  | SECJpeg | m_nQuality | Image quality factor.
//@comm This factor influences compression.
//@xref <c SECJpeg>

//@doc SECJpeg
//@mdata long  | SECJpeg | m_nSmoothing | Smoothing factor.
//@xref <c SECJpeg>

//@doc SECJpeg
//@mdata BOOL  | SECJpeg | m_bOptimizeEntropyCoding | Entropy coding flag.
//@xref <c SECJpeg>

//@doc SECJpeg
//@mdata BOOL  | SECJpeg | m_bArithmeticCoding | Arithmetic coding flag.
//@comm If this flag is FALSE, Huffman scheme encoding is used.
//@xref <c SECJpeg>

//@doc SECJpeg
//@mdata BOOL  | SECJpeg | m_bQuantize | Flag to invoke color dithering for 
// images loaded into systems with a different number of colors.
//@xref <c SECJpeg>

// adinsert AutoDuck insertion point for SECJpeg
//@doc SECJpeg
//@class SECJpeg is <c SECImage> derived class which supports the JFIF (JPEG file interchange 
// format) file standard.  
//
//@comm It should be noted that "JPEG" is actually a specification for a compression scheme, while 
// JFIF is a file format which utilizes the JPEG scheme.
//
// The JFIF standard offers a superior compression scheme and supports up to 24-bit images.  
// JFIF files are often used in image processing applications.
//
// SECJpeg is based on the JFIF version 1.0.2 specification.
//
// You can control image quality by setting the member variables <md SECJpeg::m_nQuality> 
// (for image quality), <md SECJpeg::m_nSmoothing> (for smoothing factor), <md SECJpeg::m_bOptimizeEntropyCoding>
// (TRUE or FALSE on whether you wish to use Entropy Coding) and <md SECJpeg::m_bArithmeticCoding>
// (TRUE or FALSE on whether you wish to use Arithmetic coding).  All these parameters are well 
// documented and discussed thoroughly by the Independendent JPEG User’s Group from which SECJpeg 
// is based.
//
// See the IMAGETST sample in the \OT\SAMPLES\STANDARD\IMAGE\IMAGETST directory for a 
// demonstration of this class.
//@xref <c SECImage>
//@base public | SECImage
class SECJpeg : public SECImage
{

private:
	 FOUNDATION_API void SECoutput_init(j_decompress_ptr cinfo);

// Overrides
protected:
	 FOUNDATION_API virtual BOOL DoLoadImage(CFile* pFile);
	 FOUNDATION_API virtual BOOL DoSaveImage(CFile* pFile);

	DWORD m_dwSizeSrcBits;

//jccoefct.cpp
	 FOUNDATION_API void jinit_c_coef_controller (j_compress_ptr cinfo, boolean need_full_buffer);
	 FOUNDATION_API void coefct_start_iMCU_row (j_compress_ptr cinfo);
	 FOUNDATION_API void coefct_start_pass_coef (j_compress_ptr cinfo, J_BUF_MODE pass_mode);
	 FOUNDATION_API boolean compress_data (j_compress_ptr cinfo, JSAMPIMAGE input_buf);
	 FOUNDATION_API boolean compress_first_pass (j_compress_ptr cinfo, JSAMPIMAGE input_buf);
	 FOUNDATION_API boolean coefct_compress_output (j_compress_ptr cinfo, JSAMPIMAGE input_buf);

//jcdctmgr.cpp
	 FOUNDATION_API void start_pass_fdctmgr (j_compress_ptr cinfo);
	 FOUNDATION_API void forward_DCT (j_compress_ptr cinfo, jpeg_component_info * compptr,
									  JSAMPARRAY sample_data, JBLOCKROW coef_blocks,
									  JDIMENSION start_row, JDIMENSION start_col,
									  JDIMENSION num_blocks);
	 FOUNDATION_API void forward_DCT_float (j_compress_ptr cinfo, jpeg_component_info * compptr,
											JSAMPARRAY sample_data, JBLOCKROW coef_blocks,
											JDIMENSION start_row, JDIMENSION start_col,
											JDIMENSION num_blocks);
	 FOUNDATION_API void jinit_forward_dct (j_compress_ptr cinfo);

//jcinit.cpp
	 FOUNDATION_API void jinit_compress_master (j_compress_ptr cinfo);

//jcmainct.cpp
	 FOUNDATION_API void start_pass_main (j_compress_ptr cinfo, J_BUF_MODE pass_mode);
	 FOUNDATION_API void process_data_simple_main (j_compress_ptr cinfo,
												   JSAMPARRAY input_buf, JDIMENSION *in_row_ctr,
												   JDIMENSION in_rows_avail);
	 FOUNDATION_API void process_data_buffer_main (j_compress_ptr cinfo,
												   JSAMPARRAY input_buf, JDIMENSION *in_row_ctr,
											       JDIMENSION in_rows_avail);
	 FOUNDATION_API void jinit_c_main_controller (j_compress_ptr cinfo, boolean need_full_buffer);

//jcmaster.cpp
	 FOUNDATION_API void initial_setup (j_compress_ptr cinfo);
	 FOUNDATION_API void validate_script (j_compress_ptr cinfo);
	 FOUNDATION_API void select_scan_parameters (j_compress_ptr cinfo);
	 FOUNDATION_API void per_scan_setup (j_compress_ptr cinfo);
	 FOUNDATION_API void prepare_for_pass (j_compress_ptr cinfo);
	 FOUNDATION_API void pass_startup (j_compress_ptr cinfo);
	 FOUNDATION_API void finish_pass_master (j_compress_ptr cinfo);
	 FOUNDATION_API void jinit_c_master_control (j_compress_ptr cinfo, boolean transcode_only);


//jcparam.cpp 
	 FOUNDATION_API void jpeg_add_quant_table (j_compress_ptr cinfo, int which_tbl,
											   const unsigned int *basic_table,
											   int scale_factor, boolean force_baseline);
	 FOUNDATION_API void jpeg_set_linear_quality (j_compress_ptr cinfo, int scale_factor,
											  	  boolean force_baseline);
	 FOUNDATION_API int jpeg_quality_scaling (int quality);
	 FOUNDATION_API void jpeg_set_quality (j_compress_ptr cinfo, int quality, boolean force_baseline);
	 FOUNDATION_API void add_huff_table (j_compress_ptr cinfo,
										 JHUFF_TBL **htblptr, const JSECUINT8 *bits, const JSECUINT8 *val);
	 FOUNDATION_API void std_huff_tables (j_compress_ptr cinfo);
	 FOUNDATION_API void jpeg_set_defaults (j_compress_ptr cinfo);
	 FOUNDATION_API void jpeg_default_colorspace (j_compress_ptr cinfo);
	 FOUNDATION_API void jpeg_set_colorspace (j_compress_ptr cinfo, J_COLOR_SPACE colorspace);
	 FOUNDATION_API jpeg_scan_info* fill_a_scan (jpeg_scan_info * scanptr, int ci,
												 int Ss, int Se, int Ah, int Al);
	 FOUNDATION_API jpeg_scan_info* fill_scans (jpeg_scan_info * scanptr, int ncomps,	
												int Ss, int Se, int Ah, int Al);
	 FOUNDATION_API jpeg_scan_info* fill_dc_scans (jpeg_scan_info * scanptr, int ncomps, int Ah, int Al);
	 FOUNDATION_API void jpeg_simple_progression (j_compress_ptr cinfo);

// jcprepct.cpp
	 FOUNDATION_API void start_pass_prep (j_compress_ptr cinfo, J_BUF_MODE pass_mode);
	 FOUNDATION_API void expand_bottom_edge (JSAMPARRAY image_data, JDIMENSION num_cols,
											 int input_rows, int output_rows);
	 FOUNDATION_API void pre_process_data (j_compress_ptr cinfo,
										   JSAMPARRAY input_buf, JDIMENSION *in_row_ctr,
										   JDIMENSION in_rows_avail,
										   JSAMPIMAGE output_buf, JDIMENSION *out_row_group_ctr,
										   JDIMENSION out_row_groups_avail);
	 FOUNDATION_API void pre_process_context (j_compress_ptr cinfo,
											  JSAMPARRAY input_buf, JDIMENSION *in_row_ctr,
											  JDIMENSION in_rows_avail,
											  JSAMPIMAGE output_buf, JDIMENSION *out_row_group_ctr,
											  JDIMENSION out_row_groups_avail);
	 FOUNDATION_API void create_context_buffer (j_compress_ptr cinfo);
	 FOUNDATION_API void jinit_c_prep_controller (j_compress_ptr cinfo, boolean need_full_buffer);

//jctrans.cpp
	 FOUNDATION_API void jpeg_write_coefficients (j_compress_ptr cinfo, jvirt_barray_ptr * coef_arrays);
	 FOUNDATION_API void jpeg_copy_critical_parameters (j_decompress_ptr srcinfo, j_compress_ptr dstinfo);
	 FOUNDATION_API void transencode_master_selection (j_compress_ptr cinfo, jvirt_barray_ptr * coef_arrays);
	 FOUNDATION_API void start_iMCU_row (j_compress_ptr cinfo);
	 FOUNDATION_API void start_pass_coef (j_compress_ptr cinfo, J_BUF_MODE pass_mode);
	 FOUNDATION_API boolean compress_output (j_compress_ptr cinfo, JSAMPIMAGE input_buf);
	 FOUNDATION_API void transencode_coef_controller (j_compress_ptr cinfo, jvirt_barray_ptr * coef_arrays);

// jdapistd.cpp
	 FOUNDATION_API boolean jpeg_start_decompress (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean output_pass_setup (j_decompress_ptr cinfo);
	 FOUNDATION_API JDIMENSION jpeg_read_scanlines (j_decompress_ptr cinfo, JSAMPARRAY scanlines, JDIMENSION max_lines);
	 FOUNDATION_API JDIMENSION jpeg_read_raw_data (j_decompress_ptr cinfo, JSAMPIMAGE data,	JDIMENSION max_lines);
	 FOUNDATION_API boolean jpeg_start_output (j_decompress_ptr cinfo, int scan_number);
	 FOUNDATION_API boolean jpeg_finish_output (j_decompress_ptr cinfo);

// jdatasrc.cpp
	 FOUNDATION_API void init_source (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean fill_input_buffer (j_decompress_ptr cinfo);
	 FOUNDATION_API void skip_input_data (j_decompress_ptr cinfo, long num_bytes);
	 FOUNDATION_API void term_source (j_decompress_ptr cinfo);
	 FOUNDATION_API void jpeg_stdio_src (j_decompress_ptr cinfo, CFile * infile);

// jdcolor.cpp 
	 FOUNDATION_API void build_ycc_rgb_table (j_decompress_ptr cinfo);
	 FOUNDATION_API void ycc_rgb_convert (j_decompress_ptr cinfo,
										  JSAMPIMAGE input_buf, JDIMENSION input_row,
										  JSAMPARRAY output_buf, int num_rows);
	 FOUNDATION_API void null_convert (j_decompress_ptr cinfo,
									   JSAMPIMAGE input_buf, JDIMENSION input_row,
									   JSAMPARRAY output_buf, int num_rows);
	 FOUNDATION_API void grayscale_convert (j_decompress_ptr cinfo,
											JSAMPIMAGE input_buf, JDIMENSION input_row,
											JSAMPARRAY output_buf, int num_rows);
	 FOUNDATION_API void ycck_cmyk_convert (j_decompress_ptr cinfo,
											JSAMPIMAGE input_buf, JDIMENSION input_row,
											JSAMPARRAY output_buf, int num_rows);
	 FOUNDATION_API void start_pass_dcolor (j_decompress_ptr cinfo);
	 FOUNDATION_API void jinit_color_deconverter (j_decompress_ptr cinfo);

// jdhuff.cpp
	 FOUNDATION_API void start_pass_huff_decoder (j_decompress_ptr cinfo);
	 FOUNDATION_API void jpeg_make_d_derived_tbl (j_decompress_ptr cinfo, JHUFF_TBL * htbl, d_derived_tbl **pdtbl);
	 FOUNDATION_API boolean jpeg_fill_bit_buffer (bitread_working_state * state,
												  register bit_buf_type get_buffer, register int bits_left,
												  int nbits);
	 FOUNDATION_API int jpeg_huff_decode (bitread_working_state * state,
										  register bit_buf_type get_buffer, register int bits_left,
										  d_derived_tbl * htbl, int min_bits);
	 FOUNDATION_API boolean process_restart (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean decode_mcu (j_decompress_ptr cinfo, JBLOCKROW *MCU_data);
	 FOUNDATION_API void jinit_huff_decoder (j_decompress_ptr cinfo);

// jdmainct.cpp
	 FOUNDATION_API void alloc_funny_pointers (j_decompress_ptr cinfo);
	 FOUNDATION_API void make_funny_pointers (j_decompress_ptr cinfo);
	 FOUNDATION_API void set_wraparound_pointers (j_decompress_ptr cinfo);
	 FOUNDATION_API void set_bottom_pointers (j_decompress_ptr cinfo);
	 FOUNDATION_API void start_pass_main (j_decompress_ptr cinfo, J_BUF_MODE pass_mode);
	 FOUNDATION_API void process_data_simple_main (j_decompress_ptr cinfo,
												   JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
												   JDIMENSION out_rows_avail);
	 FOUNDATION_API void process_data_context_main (j_decompress_ptr cinfo,
													JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
													JDIMENSION out_rows_avail);
	 FOUNDATION_API void process_data_crank_post (j_decompress_ptr cinfo,
												  JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
												  JDIMENSION out_rows_avail);
	 FOUNDATION_API void jinit_d_main_controller (j_decompress_ptr cinfo, boolean need_full_buffer);

//jdmaster.cpp
	 FOUNDATION_API boolean use_merged_upsample (j_decompress_ptr cinfo);
	 FOUNDATION_API void jpeg_calc_output_dimensions (j_decompress_ptr cinfo);
	 FOUNDATION_API void prepare_range_limit_table (j_decompress_ptr cinfo);
	 FOUNDATION_API void master_selection (j_decompress_ptr cinfo);
	 FOUNDATION_API void prepare_for_output_pass (j_decompress_ptr cinfo);
	 FOUNDATION_API void finish_output_pass (j_decompress_ptr cinfo);
	 FOUNDATION_API void jpeg_new_colormap (j_decompress_ptr cinfo);
	 FOUNDATION_API void jinit_master_decompress (j_decompress_ptr cinfo);

//jdphuff.cpp
	 FOUNDATION_API void start_pass_phuff_decoder (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean progressive_process_restart (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean decode_mcu_DC_first (j_decompress_ptr cinfo, JBLOCKROW *MCU_data);
	 FOUNDATION_API boolean decode_mcu_AC_first (j_decompress_ptr cinfo, JBLOCKROW *MCU_data);
	 FOUNDATION_API boolean decode_mcu_DC_refine (j_decompress_ptr cinfo, JBLOCKROW *MCU_data);
	 FOUNDATION_API boolean decode_mcu_AC_refine (j_decompress_ptr cinfo, JBLOCKROW *MCU_data);
	 FOUNDATION_API void jinit_phuff_decoder (j_decompress_ptr cinfo);


//jdsample.cpp
	 FOUNDATION_API void start_pass_upsample (j_decompress_ptr cinfo);
	 FOUNDATION_API void sep_upsample (j_decompress_ptr cinfo,
									   JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
									   JDIMENSION in_row_groups_avail,
									   JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
									   JDIMENSION out_rows_avail);
	 FOUNDATION_API void fullsize_upsample (j_decompress_ptr cinfo, jpeg_component_info * compptr,
											JSAMPARRAY input_data, JSAMPARRAY *output_data_ptr);
	 FOUNDATION_API void noop_upsample (j_decompress_ptr cinfo, jpeg_component_info * compptr,
										JSAMPARRAY input_data, JSAMPARRAY *output_data_ptr);
	 FOUNDATION_API void int_upsample (j_decompress_ptr cinfo, jpeg_component_info * compptr,
									   JSAMPARRAY input_data, JSAMPARRAY *ouput_data_ptr);
	 FOUNDATION_API void h2v1_upsample (j_decompress_ptr cinfo, jpeg_component_info * compptr,
										JSAMPARRAY input_data, JSAMPARRAY *output_data_ptr);
	 FOUNDATION_API void h2v2_upsample (j_decompress_ptr cinfo, jpeg_component_info * compptr,
										JSAMPARRAY input_data, JSAMPARRAY *output_data_ptr);
	 FOUNDATION_API void h2v1_fancy_upsample (j_decompress_ptr cinfo, jpeg_component_info * compptr,
											  JSAMPARRAY input_data, JSAMPARRAY *ouput_data_ptr);
	 FOUNDATION_API void h2v2_fancy_upsample (j_decompress_ptr cinfo, jpeg_component_info * compptr,
											  JSAMPARRAY input_data, JSAMPARRAY *output_data_ptr);
	 FOUNDATION_API void jinit_upsampler (j_decompress_ptr cinfo);

// jerror.cpp
	 FOUNDATION_API void error_exit (j_common_ptr cinfo);
	 FOUNDATION_API void output_message (j_common_ptr cinfo);
	 FOUNDATION_API void emit_message (j_common_ptr cinfo, int msg_level);
	 FOUNDATION_API void format_message (j_common_ptr cinfo, TCHAR * buffer);
	 FOUNDATION_API void reset_error_mgr (j_common_ptr cinfo);
	 FOUNDATION_API struct jpeg_error_mgr * jpeg_std_error (struct jpeg_error_mgr * err);

// jfdctfst.cpp
	 FOUNDATION_API void jpeg_fdct_ifast (DCTELEM * data);
	 FOUNDATION_API void jpeg_idct_float (j_decompress_ptr cinfo, jpeg_component_info * compptr,
										  JCOEFPTR coef_block,
										  JSAMPARRAY output_buf, JDIMENSION output_col);

// jidctint.cpp
	 FOUNDATION_API void jpeg_idct_islow (j_decompress_ptr cinfo, jpeg_component_info * compptr,
										  JCOEFPTR coef_block,
										  JSAMPARRAY output_buf, JDIMENSION output_col);

//jquant1.cpp
	 FOUNDATION_API int select_ncolors (j_decompress_ptr cinfo, int Ncolors[]);
	 FOUNDATION_API int output_value (j_decompress_ptr cinfo, int ci, int j, int maxj);
	 FOUNDATION_API int largest_input_value (j_decompress_ptr cinfo, int ci, int j, int maxj);
	 FOUNDATION_API void create_colormap (j_decompress_ptr cinfo);
	 FOUNDATION_API void create_colorindex (j_decompress_ptr cinfo);
	 FOUNDATION_API ODITHER_MATRIX_PTR make_odither_array (j_decompress_ptr cinfo, int ncolors);
	 FOUNDATION_API void create_odither_tables (j_decompress_ptr cinfo);
	 FOUNDATION_API void color_quantize (j_decompress_ptr cinfo, JSAMPARRAY input_buf,
										 JSAMPARRAY output_buf, int num_rows);
	 FOUNDATION_API void color_quantize3 (j_decompress_ptr cinfo, JSAMPARRAY input_buf,
										  JSAMPARRAY output_buf, int num_rows);
	 FOUNDATION_API void quantize_ord_dither (j_decompress_ptr cinfo, JSAMPARRAY input_buf,
											  JSAMPARRAY output_buf, int num_rows);
	 FOUNDATION_API void quantize3_ord_dither (j_decompress_ptr cinfo, JSAMPARRAY input_buf,
											   JSAMPARRAY output_buf, int num_rows);
	 FOUNDATION_API void quantize_fs_dither (j_decompress_ptr cinfo, JSAMPARRAY input_buf,
											 JSAMPARRAY output_buf, int num_rows);
	 FOUNDATION_API void alloc_fs_workspace (j_decompress_ptr cinfo);
	 FOUNDATION_API void start_pass_1_quant (j_decompress_ptr cinfo, boolean is_pre_scan);
	 FOUNDATION_API void finish_pass_1_quant (j_decompress_ptr cinfo);
	 FOUNDATION_API void new_color_map_1_quant (j_decompress_ptr cinfo);
	 FOUNDATION_API void jinit_1pass_quantizer (j_decompress_ptr cinfo);

//jutils.cpp
	 FOUNDATION_API long jdiv_round_up (long a, long b);
	 FOUNDATION_API long jround_up (long a, long b);
	 FOUNDATION_API void jcopy_sample_rows (JSAMPARRAY input_array, int source_row,
											JSAMPARRAY output_array, int dest_row,
											int num_rows, JDIMENSION num_cols);
	 FOUNDATION_API void jcopy_block_row (JBLOCKROW input_row, JBLOCKROW output_row,
										  JDIMENSION num_blocks);
	 FOUNDATION_API void jzero_far (void FAR * target, size_t bytestozero);

//jmemansi.cpp
	 FOUNDATION_API void * jpeg_get_small (j_common_ptr cinfo, size_t sizeofobject);
	 FOUNDATION_API void jpeg_free_small (j_common_ptr cinfo, void * object, size_t sizeofobject);
#ifdef WIN32
	 FOUNDATION_API void  * jpeg_get_large (j_common_ptr cinfo, long sizeofobject);
	 FOUNDATION_API void jpeg_free_large (j_common_ptr cinfo, void FAR * object, size_t sizeofobject);
#else
	 FOUNDATION_API void huge * jpeg_get_large (j_common_ptr cinfo, long sizeofobject);
	 FOUNDATION_API void jpeg_free_large (j_common_ptr cinfo, void huge * object, size_t sizeofobject);
#endif
	 FOUNDATION_API long jpeg_mem_available (j_common_ptr cinfo, long min_bytes_needed,
											 long max_bytes_needed, long already_allocated);
	 FOUNDATION_API void read_backing_store (j_common_ptr cinfo, backing_store_ptr info,
#ifdef WIN32
											 void *buffer_address,
#else
											 void huge *buffer_address,
#endif
											 long file_offset, long byte_count);
	 FOUNDATION_API void write_backing_store (j_common_ptr cinfo, backing_store_ptr info,
											  void FAR * buffer_address,
											  long file_offset, long byte_count);
	 FOUNDATION_API void close_backing_store (j_common_ptr cinfo, backing_store_ptr info);
	 FOUNDATION_API void jpeg_open_backing_store (j_common_ptr cinfo, backing_store_ptr info,
												  long total_bytes_needed);
	 											  long jpeg_mem_init (j_common_ptr cinfo);
	 FOUNDATION_API void jpeg_mem_term (j_common_ptr cinfo);

//jmemnobs.cpp
// void * jpeg_get_small (j_common_ptr cinfo, size_t sizeofobject);
// void jpeg_free_small (j_common_ptr cinfo, void * object, size_t sizeofobject);
// void FAR * jpeg_get_large (j_common_ptr cinfo, size_t sizeofobject);
// void jpeg_free_large (j_common_ptr cinfo, void FAR * object, size_t sizeofobject);
// long jpeg_mem_available (j_common_ptr cinfo, long min_bytes_needed,
// 							long max_bytes_needed, long already_allocated);
// void jpeg_open_backing_store (j_common_ptr cinfo, backing_store_ptr info,
// 								 long total_bytes_needed);
// long jpeg_mem_init (j_common_ptr cinfo);
// void jpeg_mem_term (j_common_ptr cinfo);

// jcapimin.cpp
	 FOUNDATION_API void jpeg_create_compress (j_compress_ptr cinfo);
	 FOUNDATION_API void jpeg_destroy_compress (j_compress_ptr cinfo);
	 FOUNDATION_API void jpeg_abort_compress (j_compress_ptr cinfo);
	 FOUNDATION_API void jpeg_suppress_tables (j_compress_ptr cinfo, boolean suppress);
	 FOUNDATION_API void jpeg_finish_compress (j_compress_ptr cinfo);
	 FOUNDATION_API void jpeg_write_marker (j_compress_ptr cinfo, int marker,
											const JOCTET *dataptr, unsigned int datalen);
	 FOUNDATION_API void jpeg_write_tables (j_compress_ptr cinfo);

//jcapistd.cpp
	 FOUNDATION_API void jpeg_start_compress (j_compress_ptr cinfo, boolean write_all_tables);
											  JDIMENSION jpeg_write_scanlines (j_compress_ptr cinfo, JSAMPARRAY scanlines,
											  JDIMENSION num_lines);
	 FOUNDATION_API JDIMENSION jpeg_write_raw_data (j_compress_ptr cinfo, JSAMPIMAGE data,
													JDIMENSION num_lines);

// jccolor.cpp
	 FOUNDATION_API void rgb_ycc_start (j_compress_ptr cinfo);
	 FOUNDATION_API void rgb_ycc_convert (j_compress_ptr cinfo,
										  JSAMPARRAY input_buf, JSAMPIMAGE output_buf,
										  JDIMENSION output_row, int num_rows);
	 FOUNDATION_API void rgb_gray_convert (j_compress_ptr cinfo,
										   JSAMPARRAY input_buf, JSAMPIMAGE output_buf,
										   JDIMENSION output_row, int num_rows);
	 FOUNDATION_API void cmyk_ycck_convert (j_compress_ptr cinfo,
											JSAMPARRAY input_buf, JSAMPIMAGE output_buf,
											JDIMENSION output_row, int num_rows);
	 FOUNDATION_API void grayscale_convert (j_compress_ptr cinfo,
											JSAMPARRAY input_buf, JSAMPIMAGE output_buf,
											JDIMENSION output_row, int num_rows);
	 FOUNDATION_API void null_convert (j_compress_ptr cinfo,
									   JSAMPARRAY input_buf, JSAMPIMAGE output_buf,
									   JDIMENSION output_row, int num_rows);
	 FOUNDATION_API void null_method (j_compress_ptr cinfo);
	 FOUNDATION_API void jinit_color_converter (j_compress_ptr cinfo);

// jchuff.cpp
	 FOUNDATION_API void start_pass_huff (j_compress_ptr cinfo, boolean gather_statistics);
	 FOUNDATION_API void jpeg_make_c_derived_tbl (j_compress_ptr cinfo, JHUFF_TBL * htbl, c_derived_tbl **pdtbl);
	 FOUNDATION_API boolean dump_buffer (comp_working_state * state);
	 FOUNDATION_API boolean emit_bits (comp_working_state * state, unsigned int code, int size);
	 FOUNDATION_API boolean flush_bits (comp_working_state * state);
	 FOUNDATION_API boolean encode_one_block (comp_working_state * state, JCOEFPTR block, int last_dc_val,
	 										  c_derived_tbl  *dctbl, c_derived_tbl *actbl);
	 FOUNDATION_API boolean emit_restart (comp_working_state * state, int restart_num);
	 FOUNDATION_API boolean encode_mcu_huff (j_compress_ptr cinfo, JBLOCKROW *MCU_data);
	 FOUNDATION_API void finish_pass_huff (j_compress_ptr cinfo);
	 FOUNDATION_API void htest_one_block (JCOEFPTR block, int last_dc_val, long dc_counts[], long ac_counts[]);
	 FOUNDATION_API boolean encode_mcu_gather (j_compress_ptr cinfo, JBLOCKROW *MCU_data);
	 FOUNDATION_API void jpeg_gen_optimal_table (j_compress_ptr cinfo, JHUFF_TBL * htbl, long freq[]);
	 FOUNDATION_API void finish_pass_gather (j_compress_ptr cinfo);
	 FOUNDATION_API void jinit_huff_encoder (j_compress_ptr cinfo);

// jcmarker.cpp
	 FOUNDATION_API void emit_byte (j_compress_ptr cinfo, int val);
	 FOUNDATION_API void emit_marker (j_compress_ptr cinfo, COMP_JPEG_MARKER mark);
	 FOUNDATION_API void emit_2bytes (j_compress_ptr cinfo, int value);
	 FOUNDATION_API int emit_dqt (j_compress_ptr cinfo, int index);
	 FOUNDATION_API void emit_dht (j_compress_ptr cinfo, int index, boolean is_ac);
	 FOUNDATION_API void emit_dac (j_compress_ptr cinfo);
	 FOUNDATION_API void emit_dri (j_compress_ptr cinfo);
	 FOUNDATION_API void emit_sof (j_compress_ptr cinfo, COMP_JPEG_MARKER code);
	 FOUNDATION_API void emit_sos (j_compress_ptr cinfo);
	 FOUNDATION_API void emit_jfif_app0 (j_compress_ptr cinfo);
	 FOUNDATION_API void emit_adobe_app14 (j_compress_ptr cinfo);
	 FOUNDATION_API void write_any_marker (j_compress_ptr cinfo, int marker, const JOCTET *dataptr, unsigned int datalen);
	 FOUNDATION_API void write_file_header (j_compress_ptr cinfo);
	 FOUNDATION_API void write_frame_header (j_compress_ptr cinfo);
	 FOUNDATION_API void write_scan_header (j_compress_ptr cinfo);
	 FOUNDATION_API void write_file_trailer (j_compress_ptr cinfo);
	 FOUNDATION_API void write_tables_only (j_compress_ptr cinfo);
	 FOUNDATION_API void jinit_marker_writer (j_compress_ptr cinfo);

// jcomapi.cpp
	 FOUNDATION_API void jpeg_abort (j_common_ptr cinfo);
	 FOUNDATION_API void jpeg_destroy (j_common_ptr cinfo);
	 FOUNDATION_API JQUANT_TBL* jpeg_alloc_quant_table (j_common_ptr cinfo);
	 FOUNDATION_API JHUFF_TBL* jpeg_alloc_huff_table (j_common_ptr cinfo);

//out8
// jcphuff.cpp 
	 FOUNDATION_API void start_pass_phuff (j_compress_ptr cinfo, boolean gather_statistics);
	 FOUNDATION_API void dump_buffer (cp_phuff_entropy_ptr entropy);
	 FOUNDATION_API void emit_bits (cp_phuff_entropy_ptr entropy, unsigned int code, int size);
	 FOUNDATION_API void flush_bits (cp_phuff_entropy_ptr entropy);
	 FOUNDATION_API void emit_symbol (cp_phuff_entropy_ptr entropy, int tbl_no, int symbol);
	 FOUNDATION_API void emit_buffered_bits (cp_phuff_entropy_ptr entropy, char * bufstart, unsigned int nbits);
	 FOUNDATION_API void emit_eobrun (cp_phuff_entropy_ptr entropy);
	 FOUNDATION_API void emit_restart (cp_phuff_entropy_ptr entropy, int restart_num);
	 FOUNDATION_API boolean encode_mcu_DC_first (j_compress_ptr cinfo, JBLOCKROW *MCU_data);
	 FOUNDATION_API boolean encode_mcu_AC_first (j_compress_ptr cinfo, JBLOCKROW *MCU_data);
	 FOUNDATION_API boolean encode_mcu_DC_refine (j_compress_ptr cinfo, JBLOCKROW *MCU_data);
	 FOUNDATION_API boolean encode_mcu_AC_refine (j_compress_ptr cinfo, JBLOCKROW *MCU_data);
	 FOUNDATION_API void finish_pass_phuff (j_compress_ptr cinfo);
	 FOUNDATION_API void finish_pass_gather_phuff (j_compress_ptr cinfo);
	 FOUNDATION_API void jinit_phuff_encoder (j_compress_ptr cinfo);

// jcsample.cpp
	 FOUNDATION_API void start_pass_downsample (j_compress_ptr cinfo);
	 FOUNDATION_API void expand_right_edge (JSAMPARRAY image_data, int num_rows,
											JDIMENSION input_cols, JDIMENSION output_cols);
	 FOUNDATION_API void sep_downsample (j_compress_ptr cinfo,
										 JSAMPIMAGE input_buf, JDIMENSION in_row_index,
										 JSAMPIMAGE output_buf, JDIMENSION out_row_group_index);
	 FOUNDATION_API void int_downsample (j_compress_ptr cinfo, jpeg_component_info * compptr,
										 JSAMPARRAY input_data, JSAMPARRAY output_data);
	 FOUNDATION_API void fullsize_downsample (j_compress_ptr cinfo, jpeg_component_info * compptr,
											  JSAMPARRAY input_data, JSAMPARRAY output_data);
	 FOUNDATION_API void h2v1_downsample (j_compress_ptr cinfo, jpeg_component_info * compptr,
										  JSAMPARRAY input_data, JSAMPARRAY output_data);
	 FOUNDATION_API void h2v2_downsample (j_compress_ptr cinfo, jpeg_component_info * compptr,
										  JSAMPARRAY input_data, JSAMPARRAY output_data);
	 FOUNDATION_API void h2v2_smooth_downsample (j_compress_ptr cinfo, jpeg_component_info * compptr,
												 JSAMPARRAY input_data, JSAMPARRAY output_data);
	 FOUNDATION_API void fullsize_smooth_downsample (j_compress_ptr cinfo, jpeg_component_info *compptr,
													 JSAMPARRAY input_data, JSAMPARRAY output_data);
	 FOUNDATION_API void jinit_downsampler (j_compress_ptr cinfo);

// jdapimin.cpp
	 FOUNDATION_API void jpeg_create_decompress (j_decompress_ptr cinfo);
	 FOUNDATION_API void jpeg_destroy_decompress (j_decompress_ptr cinfo);
	 FOUNDATION_API void jpeg_abort_decompress (j_decompress_ptr cinfo);
	 FOUNDATION_API void jpeg_set_marker_processor (j_decompress_ptr cinfo, int marker_code, jpeg_marker_parser_method routine);
	 FOUNDATION_API void default_decompress_parms (j_decompress_ptr cinfo);
	 FOUNDATION_API int jpeg_read_header (j_decompress_ptr cinfo, boolean require_image);
	 FOUNDATION_API int jpeg_consume_input (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean jpeg_input_complete (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean jpeg_has_multiple_scans (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean jpeg_finish_decompress (j_decompress_ptr cinfo);

// jdatadst.cpp
	 FOUNDATION_API void init_destination (j_compress_ptr cinfo);
	 FOUNDATION_API boolean empty_output_buffer (j_compress_ptr cinfo);
	 FOUNDATION_API void term_destination (j_compress_ptr cinfo);
	 FOUNDATION_API void jpeg_stdio_dest (j_compress_ptr cinfo, CFile * outfile);

//jdcoefct.cpp
	 FOUNDATION_API void start_iMCU_row (j_decompress_ptr cinfo);
	 FOUNDATION_API void jdcoefct_start_input_pass (j_decompress_ptr cinfo);
	 FOUNDATION_API void start_output_pass (j_decompress_ptr cinfo);
	 FOUNDATION_API int decompress_onepass (j_decompress_ptr cinfo, JSAMPIMAGE output_buf);
	 FOUNDATION_API int dummy_consume_data (j_decompress_ptr cinfo);
	 FOUNDATION_API int consume_data (j_decompress_ptr cinfo);
	 FOUNDATION_API int decompress_data (j_decompress_ptr cinfo, JSAMPIMAGE output_buf);
	 FOUNDATION_API boolean smoothing_ok (j_decompress_ptr cinfo);
	 FOUNDATION_API int decompress_smooth_data (j_decompress_ptr cinfo, JSAMPIMAGE output_buf);
	 FOUNDATION_API void jinit_d_coef_controller (j_decompress_ptr cinfo, boolean need_full_buffer);

//jddctmgr.cpp
	 FOUNDATION_API void start_pass (j_decompress_ptr cinfo);
	 FOUNDATION_API void jinit_inverse_dct (j_decompress_ptr cinfo);

//jdinput.cpp
	 FOUNDATION_API void initial_setup (j_decompress_ptr cinfo);
	 FOUNDATION_API void per_scan_setup (j_decompress_ptr cinfo);
	 FOUNDATION_API void latch_quant_tables (j_decompress_ptr cinfo);
	 FOUNDATION_API void start_input_pass (j_decompress_ptr cinfo);
	 FOUNDATION_API void finish_input_pass (j_decompress_ptr cinfo);
	 FOUNDATION_API int consume_markers (j_decompress_ptr cinfo);
	 FOUNDATION_API void reset_input_controller (j_decompress_ptr cinfo);
	 FOUNDATION_API void jinit_input_controller (j_decompress_ptr cinfo);

//jdmarker.cpp
	 FOUNDATION_API boolean get_soi (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean get_sof (j_decompress_ptr cinfo, boolean is_prog, boolean is_arith);
	 FOUNDATION_API boolean get_sos (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean get_app0 (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean get_app14 (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean get_dac (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean get_dht (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean get_dqt (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean get_dri (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean skip_variable (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean next_marker (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean first_marker (j_decompress_ptr cinfo);
	 FOUNDATION_API int read_markers (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean read_restart_marker (j_decompress_ptr cinfo);
	 FOUNDATION_API boolean jpeg_resync_to_restart (j_decompress_ptr cinfo, int desired);
	 FOUNDATION_API void reset_marker_reader (j_decompress_ptr cinfo);
	 FOUNDATION_API void jinit_marker_reader (j_decompress_ptr cinfo);

// jdmerge.cpp
	 FOUNDATION_API void merge_build_ycc_rgb_table (j_decompress_ptr cinfo);
	 FOUNDATION_API void start_pass_merged_upsample (j_decompress_ptr cinfo);
	 FOUNDATION_API void merged_2v_upsample (j_decompress_ptr cinfo,
											 JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
											 JDIMENSION in_row_groups_avail,
											 JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
											 JDIMENSION out_rows_avail);
	 FOUNDATION_API void merged_1v_upsample (j_decompress_ptr cinfo,
											 JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
											 JDIMENSION in_row_groups_avail,
											 JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
											 JDIMENSION out_rows_avail);
	 FOUNDATION_API void h2v1_merged_upsample (j_decompress_ptr cinfo,
											   JSAMPIMAGE input_buf, JDIMENSION in_row_group_ctr,
											   JSAMPARRAY output_buf);
	 FOUNDATION_API void h2v2_merged_upsample (j_decompress_ptr cinfo,
											   JSAMPIMAGE input_buf, JDIMENSION in_row_group_ctr,
											   JSAMPARRAY output_buf);
	 FOUNDATION_API void jinit_merged_upsampler (j_decompress_ptr cinfo);
	 FOUNDATION_API void crucial_function();

// jdpostct.cpp
	 FOUNDATION_API void start_pass_dpost (j_decompress_ptr cinfo, J_BUF_MODE pass_mode);
	 FOUNDATION_API void post_process_1pass (j_decompress_ptr cinfo,
											 JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
											 JDIMENSION in_row_groups_avail,
											 JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
									 		 JDIMENSION out_rows_avail);
	 FOUNDATION_API void post_process_prepass (j_decompress_ptr cinfo,
											   JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
											   JDIMENSION in_row_groups_avail,
											   JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
											   JDIMENSION out_rows_avail);
	 FOUNDATION_API void post_process_2pass (j_decompress_ptr cinfo,
											 JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
											 JDIMENSION in_row_groups_avail,
											 JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
											 JDIMENSION out_rows_avail);
	 FOUNDATION_API void jinit_d_post_controller (j_decompress_ptr cinfo, boolean need_full_buffer);


//jdtrans.cpp
	 FOUNDATION_API jvirt_barray_ptr * jpeg_read_coefficients (j_decompress_ptr cinfo);
	 FOUNDATION_API void transdecode_master_selection (j_decompress_ptr cinfo);

//jfdctflt.cpp
	 FOUNDATION_API void jpeg_fdct_float (FAST_FLOAT * data);
	 FOUNDATION_API void jpeg_fdct_islow (DCTELEM * data);

//jidctfst.cpp
	 FOUNDATION_API void jpeg_idct_ifast (j_decompress_ptr cinfo, jpeg_component_info * compptr,
										  JCOEFPTR coef_block, JSAMPARRAY output_buf, JDIMENSION output_col);

//jidctred.cpp
	 FOUNDATION_API void jpeg_idct_4x4 (j_decompress_ptr cinfo, jpeg_component_info * compptr,
										JCOEFPTR coef_block,
										JSAMPARRAY output_buf, JDIMENSION output_col);
	 FOUNDATION_API void jpeg_idct_2x2 (j_decompress_ptr cinfo, jpeg_component_info * compptr,
										JCOEFPTR coef_block,
										JSAMPARRAY output_buf, JDIMENSION output_col);
	 FOUNDATION_API void jpeg_idct_1x1 (j_decompress_ptr cinfo, jpeg_component_info * compptr,
										JCOEFPTR coef_block,
										JSAMPARRAY output_buf, JDIMENSION output_col);


//jquant2.cpp
	 FOUNDATION_API void prescan_quantize (j_decompress_ptr cinfo, JSAMPARRAY input_buf,
										   JSAMPARRAY output_buf, int num_rows);
	 FOUNDATION_API boxptr find_biggest_color_pop (boxptr boxlist, int numboxes);
	 FOUNDATION_API boxptr find_biggest_volume (boxptr boxlist, int numboxes);
	 FOUNDATION_API void update_box (j_decompress_ptr cinfo, boxptr boxp);
	 FOUNDATION_API int median_cut (j_decompress_ptr cinfo, boxptr boxlist, int numboxes, int desired_colors);
	 FOUNDATION_API void compute_color (j_decompress_ptr cinfo, boxptr boxp, int icolor);
	 FOUNDATION_API void select_colors (j_decompress_ptr cinfo, int desired_colors);
	 FOUNDATION_API int find_nearby_colors (j_decompress_ptr cinfo, int minc0, int minc1, int minc2, JSAMPLE colorlist[]);
	 FOUNDATION_API void find_best_colors (j_decompress_ptr cinfo, int minc0, int minc1, int minc2,
										   int numcolors, JSAMPLE colorlist[], JSAMPLE bestcolor[]);
	 FOUNDATION_API void fill_inverse_cmap (j_decompress_ptr cinfo, int c0, int c1, int c2);
	 FOUNDATION_API void pass2_no_dither (j_decompress_ptr cinfo,
										  JSAMPARRAY input_buf, JSAMPARRAY output_buf, int num_rows);
	 FOUNDATION_API void pass2_fs_dither (j_decompress_ptr cinfo,
										  JSAMPARRAY input_buf, JSAMPARRAY output_buf, int num_rows);
	 FOUNDATION_API void init_error_limit (j_decompress_ptr cinfo);
	 FOUNDATION_API void finish_pass1 (j_decompress_ptr cinfo);
	 FOUNDATION_API void finish_pass2 (j_decompress_ptr cinfo);
	 FOUNDATION_API void start_pass_2_quant (j_decompress_ptr cinfo, boolean is_pre_scan);
	 FOUNDATION_API void new_color_map_2_quant (j_decompress_ptr cinfo);
	 FOUNDATION_API void jinit_2pass_quantizer (j_decompress_ptr cinfo);

//jmemmgr.cpp
	 FOUNDATION_API void print_mem_stats (j_common_ptr cinfo, int pool_id);
	 FOUNDATION_API void out_of_memory (j_common_ptr cinfo, int which);
	 FOUNDATION_API void * alloc_small (j_common_ptr cinfo, int pool_id, size_t sizeofobject);
	#ifdef WIN32
	 FOUNDATION_API void * alloc_large (j_common_ptr cinfo, int pool_id, long sizeofobject);
	#else
	 FOUNDATION_API void huge * alloc_large (j_common_ptr cinfo, int pool_id, long sizeofobject);
	#endif
	 FOUNDATION_API JSAMPARRAY alloc_sarray (j_common_ptr cinfo, int pool_id,
											 JDIMENSION samplesperrow, JDIMENSION numrows);
	 FOUNDATION_API JBLOCKARRAY alloc_barray (j_common_ptr cinfo, int pool_id,
											  JDIMENSION samplesperrow, JDIMENSION numrows);
	 FOUNDATION_API jvirt_sarray_ptr request_virt_sarray (j_common_ptr cinfo, int pool_id, boolean pre_zero,
														  JDIMENSION samplesperrow, JDIMENSION numrows,
														  JDIMENSION maxaccess);
	 FOUNDATION_API jvirt_barray_ptr request_virt_barray (j_common_ptr cinfo, int pool_id, boolean pre_zero,
														  JDIMENSION blocksperrow, JDIMENSION numrows,
														  JDIMENSION maxaccess);	
	 FOUNDATION_API void realize_virt_arrays (j_common_ptr cinfo);
	 FOUNDATION_API void do_sarray_io (j_common_ptr cinfo, jvirt_sarray_ptr ptr, boolean writing);
	 FOUNDATION_API void do_barray_io (j_common_ptr cinfo, jvirt_barray_ptr ptr, boolean writing);
	 FOUNDATION_API JSAMPARRAY access_virt_sarray (j_common_ptr cinfo, jvirt_sarray_ptr ptr,
												   JDIMENSION start_row, JDIMENSION num_rows,
												   boolean writable);
	 FOUNDATION_API JBLOCKARRAY access_virt_barray (j_common_ptr cinfo, jvirt_barray_ptr ptr,
													JDIMENSION start_row, JDIMENSION num_rows,
													boolean writable);
	 FOUNDATION_API void free_pool (j_common_ptr cinfo, int pool_id);
	 FOUNDATION_API void self_destruct (j_common_ptr cinfo);
	 FOUNDATION_API void jinit_memory_mgr (j_common_ptr cinfo);

protected:
  FOUNDATION_DECLARE_SERIAL(SECJpeg)  

public:
   FOUNDATION_API virtual void Serialize(CArchive& ar);
#ifndef WIN32
   FOUNDATION_API BOOL SECQuantizeImage();
#endif

  //@access Construction                                 
	
	//@cmember
	/* Constructs a SECJpeg object.*/
	 FOUNDATION_API SECJpeg();

	 FOUNDATION_API ~SECJpeg();

  // Destruction

  
  // Operations


  // Implementation 
private:
#ifdef WIN32
  LPBYTE m_lpArrayPtr;  // iterator that fills up m_lpSrcBits
  short *cache;
#else
  BYTE huge *m_lpArrayPtr;
  short huge *cache;
#endif

public:

	// flag to invoke color dithering for images loaded into
	// systems with a different number of colors.
	//@cmember
	/* Flag to invoke color dithering.*/
	BOOL m_bQuantize;  	

	LPBYTE m_lpQuant;

	//Quality factor; big factors in compression come into play with this setting
	//@cmember
	/* Image quality (affects compression).*/
	long	m_nQuality;	

	//@cmember
	/* Smoothing factor.*/
	long	m_nSmoothing;

	//@cmember
	/* Entropy coding flag.*/
	BOOL	m_bOptimizeEntropyCoding;

	// use arithmetic or Huffman scheme
	//@cmember
	/* Arithmetic coding flag.*/
	BOOL	m_bArithmeticCoding;	

#ifdef _DEBUG
	 FOUNDATION_API void AssertValid() const;
#endif


};

};  // namespace stingray::foundation
};  // namespace stingray

//////////////////////////////////////////////////////
// Promote the operator>> symbol declared by the
// DECLARE_SERIAL macro to the global namespace.
using stingray::foundation::operator>>;
//////////////////////////////////////////////////////

//
// CMN Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SFL_SECJPEG_H__
