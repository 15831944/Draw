///////////////////////////////////////////////////////////////////////////////
// gxtabser.h
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
// Author: Daniel Jebaraj
//

#ifndef _GX_TAB_SER_H__
#define _GX_TAB_SER_H__

#ifndef _GX_TMPL_H__
#include "gxtmpl.h"
#endif

#ifndef _GX_TB_MGR_H__
#include "gxtbmgr.h"
#endif

#ifndef _GXTWND_H_
#include "gxtwnd.h"
#endif

#ifndef _GX_TAB_ADAPT_H__
#include "gxtbadpt.h"
#endif

#ifndef _GX_TB_GRD_ADAPT_H__
#include "gxtbgadp.h"
#endif

#ifndef _GXPRIV_H_
#include "gxpriv.h"
#endif

#ifndef _GXMSG_H
#include "gxmsg.h"
#endif

#ifndef _GX_AP_ATR_H__
#include "gxapatr.h"
#endif

#ifndef _GX_DOC_H__
#include "gxdoc.h"
#endif

#ifndef _GX_FRAME_ADPT_H__
#include "gxfradpt.h"
#endif

#ifndef _GX_CH_FRM_H__
#include "gxchfrm.h"
#endif

#ifndef _GX_DTMPL_H__
#include "gxdtmpl.h"
#endif


#define GXIMPLEMENT_DYNCREATE(cl, clb)\
	IMPLEMENT_SERIAL(cl, clb, 0)

#define GXDECLARE_DYNCREATE(cl)\
	GRID_DECLARE_SERIAL(cl) // QA: 31861


#endif //_GX_TAB_SER_H__
