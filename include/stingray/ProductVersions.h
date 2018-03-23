/////////////////////////////////////////////////////////////////////
// ProductVersions.h
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
//
// Author:	David Noi
// Date:	02.20.2006
//
// Changelog
// Date:	Initials:	Description:
//===========================================================================
// 09.08.2006	DN		Updated product versions for CD 49 release
// 09.28.2006	DN		No changes. 
//				NOTE: _SFL_VER in this file is different 
//				      from _SFL_VER in ..\Src\ProductsVersion.mak
// 02.22.2007	CD		Updated product versions 
//				to localize all version changes to 
//				..\Include\ProductsVersion.h and 
//				..\Src\ProductsVersion.mak
// 04.09.2007	CD		Updated product versions for CD 50 release
// 07.29.2008	DN		Added RWUXTheme versioning info (changelist 178714)
// 09.11.2008	CD		Updated product versions for (10.1) CD 50.1 release
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __PRODUCT_VERSION__H__
#define __PRODUCT_VERSION__H__

//------------------------------------------------------------//
// Here we define the product version numbers per release.    //
//------------------------------------------------------------//

// QA: 32237

#if _MSC_VER >= 1700 // vc++ 11.0
	// RWUXTheme version 11.01
	#define _RWUXTHEME_VER		0x1101
	#define _RWUXTHEME_VER_COMMA	11,0,0,1
	#define _RWUXTHEME_VER_TEXT	"11.01"
	#define _RWUXTHEME_VER_LIB	"1101"

	// Stingray Foundation Library version 6.00
	#define _SFL_VER	0x601
	#define _SFL_VER_COMMA	6,0,1,0
	#define _SFL_VER_TEXT	"6.01"
	#define _SFL_VER_LIB    "601"

	// Objective Chart version 11.01
	#define _OC_VER		0x1101
	#define _OC_VER_COMMA	11,0,1,0
	#define _OC_VER_TEXT	"11.01"
	#define _OC_VER_LIB     "1101"

	// Objective Chart Utility Toolkit version 11.01
	#define _OCUT_VER	0x01101
	#define _OCUT_VER_COMMA 11,0,1,0
	#define _OCUT_VER_TEXT	"11.01"
	#define _OCUT_VER_LIB   "1101"

	// Objective Edit version 11.01
	#define _OE_VER		0x01101
	#define _OE_VER_COMMA	11,0,1,0
	#define _OE_VER_TEXT	"11.01"
	#define _OE_VER_LIB     "1101"

	// Objective Grid version 12.01
	#define _GX_VER		0x01201
	#define _GX_VER_COMMA	12,0,0,1
	#define _GX_VER_TEXT	"12.01"
	#define _GX_VER_LIB     "1201"

	// Objective Toolkit version 12.01
	#define _SEC_VER	0x01201
	#define _SEC_PRO_VER	0x01201
	#define _SEC_VER_COMMA	12,0,0,1
	#define _SEC_VER_TEXT	"12.01"
	#define _SEC_VER_LIB    "1201"

	// Objective Views version 12.01
	#define _OV_VER		0x01201
	#define _OV_VER_COMMA	12,0,0,1
	#define _OV_VER_TEXT	"12.01"
	#define _OV_VER_LIB     "1201"
#else  // vc++ 9.0
	// RWUXTheme version 10.01
	#define _RWUXTHEME_VER		0x1001
	#define _RWUXTHEME_VER_COMMA	10,0,0,1
	#define _RWUXTHEME_VER_TEXT	"10.01"
	#define _RWUXTHEME_VER_LIB	"1001"

	// Stingray Foundation Library version 5.00
	#define _SFL_VER	0x501
	#define _SFL_VER_COMMA	5,0,1,0
	#define _SFL_VER_TEXT	"5.01"
	#define _SFL_VER_LIB    "501"

	// Objective Chart version 10.01
	#define _OC_VER		0x1001
	#define _OC_VER_COMMA	10,0,1,0
	#define _OC_VER_TEXT	"10.01"
	#define _OC_VER_LIB     "1001"

	// Objective Chart Utility Toolkit version 10.01
	#define _OCUT_VER	0x01001
	#define _OCUT_VER_COMMA 10,0,1,0
	#define _OCUT_VER_TEXT	"10.01"
	#define _OCUT_VER_LIB   "1001"

	// Objective Edit version 10.01
	#define _OE_VER		0x01001
	#define _OE_VER_COMMA	10,0,1,0
	#define _OE_VER_TEXT	"10.01"
	#define _OE_VER_LIB     "1001"

	// Objective Grid version 12.01
	#define _GX_VER		0x01201
	#define _GX_VER_COMMA	12,0,0,1
	#define _GX_VER_TEXT	"12.01"
	#define _GX_VER_LIB     "1201"

	// Objective Toolkit version 11.01
	#define _SEC_VER	0x01101
	#define _SEC_PRO_VER	0x01101
	#define _SEC_VER_COMMA	11,0,0,1
	#define _SEC_VER_TEXT	"11.01"
	#define _SEC_VER_LIB    "1101"

	// Objective Views version 11.01
	#define _OV_VER		0x01101
	#define _OV_VER_COMMA	11,0,0,1
	#define _OV_VER_TEXT	"11.01"
	#define _OV_VER_LIB     "1101"
#endif



#endif // __PRODUCT_VERSION__H__
