///////////////////////////////////////////////////////////////////////////////
// MvcModel.h : Declaration of MvcModel
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

// Author:       Dean Hallman
// Description:  Declaration of MvcModel interface.
//

//@doc MvcModel

#pragma once

#ifndef __MFC_MVCMODEL_H__
#define __MFC_MVCMODEL_H__

// Includes
#include <Foundation\MVC\MvcModel.h>

//
// MVC Extension DLL
// Initialize declaration context
//
#ifdef _SFLDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SFL_DATAEXT
#endif //_SFLDLL


namespace stingray {
namespace foundation {

//@type MvcModel | This is an alias for <c CMvcModel> used to preserve compability with old names.
//@iex typedef stingray::foundation::CMvcModel MvcModel;
//@xref <c CMvcModel>
typedef stingray::foundation::CMvcModel MvcModel;

};  // namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __MFC_MVCMODEL_H__
