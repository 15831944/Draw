///////////////////////////////////////////////////////////////////////////////
// Patterns.h
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
//  Description:	Patterns.h - Patterns Header
//  Created:		May 1998
//
//	This file is included via "ProAll.h"
//

#ifndef __COMPAT_SEC_PATTERNS_H
#define __COMPAT_SEC_PATTERNS_H

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>	// templates used extensively
#endif

#ifndef __COMPAT_SECCOLLECT_H__
#include "Foundation\Compatibility\Common\patterns\Collect.h"
#endif

// Factory pattern 
#ifndef __COMPAT_SECFACTORY_PATTERNS_H__
#include "Foundation\Compatibility\Common\patterns\FactoryP.h"
#endif

// PlugIn pattern 
#ifndef __COMPAT_PLUGIN_H__
#include "Foundation\Compatibility\Common\patterns\PlugIn.h"
#endif

#ifndef __COMPAT_SECWndListener_H__
#include "Foundation\Compatibility\Common\patterns\Listen.h"
#endif

// Note: DO NOT INCLUDE composite.h here!
// Composite.h has conditional RTTI dependencies. Since this file
// is entirely inline (i.e. no buildable .cpp implementation),
// it can safely be included directly by any other library
// which requires the composite support.

#endif 		// __COMPAT_SEC_PATTERNS_H
