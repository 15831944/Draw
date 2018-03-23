///////////////////////////////////////////////////////////////////////////////
// CDJPEG.h
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

/*
 *  
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains common declarations for the sample applications
 * cjpeg and djpeg.  It is NOT used by the core JPEG library.
 */

#pragma once

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#define JPEG_CJPEG_DJPEG	/* define proper options in jconfig.h */
#define JPEG_INTERNAL_OPTIONS	/* cjpeg.c,djpeg.c need to see xxx_SUPPORTED */
#include "Foundation\Image\MFC\jinclude.h"
#include "Foundation\Image\MFC\jpeglib.h"
#include "Foundation\Image\MFC\jerror.h"		/* get library error codes too */
#include "toolkit\cderror.h"		/* get application-specific error codes */
#include <StingrayExportDefs.h>

/*
 * Object interface for cjpeg's source file decoding modules
 */

typedef struct cjpeg_source_struct * cjpeg_source_ptr;

struct cjpeg_source_struct 
{
  TOOLKIT_API JMETHOD(void, start_input, (j_compress_ptr cinfo,
			      cjpeg_source_ptr sinfo));
  TOOLKIT_API JMETHOD(JDIMENSION, get_pixel_rows, (j_compress_ptr cinfo,
				       cjpeg_source_ptr sinfo));
  TOOLKIT_API JMETHOD(void, finish_input, (j_compress_ptr cinfo,
			       cjpeg_source_ptr sinfo));

  FILE *input_file;

  JSAMPARRAY buffer;
  JDIMENSION buffer_height;
};


/*
 * Object interface for djpeg's output file encoding modules
 */

typedef struct djpeg_dest_struct * djpeg_dest_ptr;

struct djpeg_dest_struct 
{
  /* start_output is called after jpeg_start_decompress finishes.
   * The color map will be ready at this time, if one is needed.
   */
  TOOLKIT_API JMETHOD(void, start_output, (j_decompress_ptr cinfo,
			       djpeg_dest_ptr dinfo));
  /* Emit the specified number of pixel rows from the buffer. */
  TOOLKIT_API JMETHOD(void, put_pixel_rows, (j_decompress_ptr cinfo,
				 djpeg_dest_ptr dinfo,
				 JDIMENSION rows_supplied));
  /* Finish up at the end of the image. */
  TOOLKIT_API JMETHOD(void, finish_output, (j_decompress_ptr cinfo,
				djpeg_dest_ptr dinfo));

  /* Target file spec; filled in by djpeg.c after object is created. */
  FILE * output_file;

  /* Output pixel-row buffer.  Created by module init or start_output.
   * Width is cinfo->output_width * cinfo->output_components;
   * height is buffer_height.
   */
  JSAMPARRAY buffer;
  JDIMENSION buffer_height;
};


/*
 * cjpeg/djpeg may need to perform extra passes to convert to or from
 * the source/destination file format.  The JPEG library does not know
 * about these passes, but we'd like them to be counted by the progress
 * monitor.  We use an expanded progress monitor object to hold the
 * additional pass count.
 */

struct cdjpeg_progress_mgr 
{
  struct jpeg_progress_mgr pub;	/* fields known to JPEG library */
  int completed_extra_passes;	/* extra passes completed */
  int total_extra_passes;	/* total extra */
  /* last printed percentage stored here to avoid multiple printouts */
  int percent_done;
};

typedef struct cdjpeg_progress_mgr * cd_progress_ptr;


/* Short forms of external names for systems with brain-damaged linkers. */

#ifdef NEED_SHORT_EXTERNAL_NAMES
#define jinit_read_bmp		jIRdBMP
#define jinit_write_bmp		jIWrBMP
#define jinit_read_gif		jIRdGIF
#define jinit_write_gif		jIWrGIF
#define jinit_read_ppm		jIRdPPM
#define jinit_write_ppm		jIWrPPM
#define jinit_read_rle		jIRdRLE
#define jinit_write_rle		jIWrRLE
#define jinit_read_targa	jIRdTarga
#define jinit_write_targa	jIWrTarga
#define read_quant_tables	RdQTables
#define read_scan_script	RdScnScript
#define set_quant_slots		SetQSlots
#define set_sample_factors	SetSFacts
#define read_color_map		RdCMap
#define enable_signal_catcher	EnSigCatcher
#define start_progress_monitor	StProgMon
#define end_progress_monitor	EnProgMon
#define read_stdin		RdStdin
#define write_stdout		WrStdout
#endif /* NEED_SHORT_EXTERNAL_NAMES */

/* Module selection routines for I/O modules. */

EXTERN TOOLKIT_API cjpeg_source_ptr jinit_read_bmp JPP((j_compress_ptr cinfo));
EXTERN TOOLKIT_API djpeg_dest_ptr jinit_write_bmp JPP((j_decompress_ptr cinfo,
					   boolean is_os2));
EXTERN TOOLKIT_API cjpeg_source_ptr jinit_read_gif JPP((j_compress_ptr cinfo));
EXTERN TOOLKIT_API djpeg_dest_ptr jinit_write_gif JPP((j_decompress_ptr cinfo));
EXTERN TOOLKIT_API cjpeg_source_ptr jinit_read_ppm JPP((j_compress_ptr cinfo));
EXTERN TOOLKIT_API djpeg_dest_ptr jinit_write_ppm JPP((j_decompress_ptr cinfo));
EXTERN TOOLKIT_API cjpeg_source_ptr jinit_read_rle JPP((j_compress_ptr cinfo));
EXTERN TOOLKIT_API djpeg_dest_ptr jinit_write_rle JPP((j_decompress_ptr cinfo));
EXTERN TOOLKIT_API cjpeg_source_ptr jinit_read_targa JPP((j_compress_ptr cinfo));
EXTERN TOOLKIT_API djpeg_dest_ptr jinit_write_targa JPP((j_decompress_ptr cinfo));

/* cjpeg support routines (in rdswitch.c) */

EXTERN TOOLKIT_API boolean read_quant_tables JPP((j_compress_ptr cinfo, char * filename,
				   int scale_factor, boolean force_baseline));
EXTERN TOOLKIT_API boolean read_scan_script JPP((j_compress_ptr cinfo, char * filename));
EXTERN TOOLKIT_API boolean set_quant_slots JPP((j_compress_ptr cinfo, char *arg));
EXTERN TOOLKIT_API boolean set_sample_factors JPP((j_compress_ptr cinfo, char *arg));

/* djpeg support routines (in rdcolmap.c) */

EXTERN TOOLKIT_API void read_color_map JPP((j_decompress_ptr cinfo, FILE * infile));

/* common support routines (in cdjpeg.c) */

EXTERN TOOLKIT_API void enable_signal_catcher JPP((j_common_ptr cinfo));
EXTERN TOOLKIT_API void start_progress_monitor JPP((j_common_ptr cinfo,
					cd_progress_ptr progress));
EXTERN TOOLKIT_API void end_progress_monitor JPP((j_common_ptr cinfo));
EXTERN TOOLKIT_API boolean keymatch JPP((char * arg, const char * keyword, int minchars));
EXTERN TOOLKIT_API FILE * read_stdin JPP((void));
EXTERN TOOLKIT_API FILE * write_stdout JPP((void));

/* miscellaneous useful macros */

#ifdef DONT_USE_B_MODE		/* define mode parameters for fopen() */
#define READ_BINARY	"r"
#define WRITE_BINARY	"w"
#else
#define READ_BINARY	"rb"
#define WRITE_BINARY	"wb"
#endif

#ifndef EXIT_FAILURE		/* define exit() codes if not provided */
#define EXIT_FAILURE  1
#endif
#ifndef EXIT_SUCCESS
#ifdef VMS
#define EXIT_SUCCESS  1		/* VMS is very nonstandard */
#else
#define EXIT_SUCCESS  0
#endif
#endif
#ifndef EXIT_WARNING
#ifdef VMS
#define EXIT_WARNING  1		/* VMS is very nonstandard */
#else
#define EXIT_WARNING  2
#endif
#endif
