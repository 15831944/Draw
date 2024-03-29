// 
// Build wizard generated file. 
// DO NOT EDIT MANUALLY!!!
//
// Stingray Foundation Library
//
//////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////
// 
//@doc SFLDll
//@module SFLDll.h | DLL initialization.
//
// Author: GF
// <nl>Created: 11/99
// 


#ifndef __SFLDLL_H__
#define __SFLDLL_H__

#ifdef _SFLDLL
	#ifdef _SFL_MFC_SUPPORT	
		#ifndef SFL_DATAEXT
			#define SFL_DATAEXT     AFX_DATA_IMPORT
			#define SFL_DATADEF
		#endif
	#else
	#endif
#endif // _SFLDLL

#endif // __SFLDLL_H__
