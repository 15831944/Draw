///////////////////////////////////////////////////////////////////////////////
// SflDef.h : SFL External Routines
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
// Author:       Gilberto Araya
// Description:  SFL External Routines declarations and definitions
//

#if !defined(_SFL)
#define _SFL
#endif

#include <foundation\sflcommon.h>

/////////////////////////////////////////////////////////////////////////////
// Library support

#if !defined(_SFL_MFC_SUPPORT) && defined(_DEFINE_ATL_ROUTINES) && !defined(_SFLLIB)
#if !defined(_LIBFUNCTIONS_DEFINED)
#define _LIBFUNCTIONS_DEFINED
namespace stingray {
namespace foundation {

#if defined(_SFL_ATL_SUPPORT)
HINSTANCE __stdcall GetResourceHandle()
#if (_ATL_VER < 0x0700)
{return _Module.GetResourceInstance();}
#else
{return _AtlBaseModule.GetResourceInstance();}
#endif
#endif	// defined(_SFL_ATL_SUPPORT)

};
};


#endif	// defined(_LIBFUNCTIONS_DEFINED)

#else 
namespace stingray {
namespace foundation {

#if defined(_SFLDLL) && !defined(_SFL_MFC_SUPPORT)
	extern HINSTANCE _hinstDll;
#endif

// Just declare the symbol, it will be defined elsewhere
	extern HINSTANCE __stdcall GetResourceHandle();
};
};

#endif	// 

