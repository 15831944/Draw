///////////////////////////////////////////////////////////////////////////////
// XMLSerialize.h : SFL XML Serialization Framework 
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

#pragma once

#if !defined(_SFL)
#define _SFL
#endif

#if !defined(__SFL_BWDEFINES_H) && !defined(_SFLBWCONFIG_H_)
#include "foundation\BWDef.h"
#endif //_SFLBWCONFIG_H_

#include <Foundation\sflcommon.h>

#ifdef _SFL_MFC_SUPPORT

#ifndef SFL_BLD_XMLSERCORE
#pragma message("Warning! The Stingray Foundation Library was built without the XML Serialization option.")
#pragma message("To enable XML serialization, please run the SFL build wizard, select this option and rebuild the library.")
#endif // SFL_BLD_XMLSERCORE

#include <foundation\XMLSerCore\XMLArch.h>
#include <foundation\XMLSerCore\XMLFTRFactory.h>
#include <foundation\XMLSerCore\XMLValueTypes.h>
#include <foundation\XMLSerCore\XMLCollFormatters.h>
#include <foundation\XMLSerCore\XMLCTEb64qp.h>

// If this header is being included from an application, then it is safe to assume that a definition of ATL _Module is present
#if defined(__ATLBASE_H__) && defined(__ATLCOM_H__)
#include <foundation\XMLSerCore\XMLDocAdapter.h>
#endif	// ATL

#endif // _SFL_MFC_SUPPORT




