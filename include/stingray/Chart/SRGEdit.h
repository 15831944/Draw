///////////////////////////////////////////////////////////////////////////////
// SRGEdit.h
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

#ifndef __SRGRAPHEDIT_H__
#define __SRGRAPHEDIT_H__

#ifndef __OCHART_H__
#include "ochart.h"
#endif

#include <afxcmn.h>
#include  "SRGRes.h"
//#include /* */ "SRGEdRes.h" superceeded by new SRGRes
#include  "TreeCtrl.h"
#include  "ItemEdit.h"
#include  "AnnoEdit.h"
#include  "VluEdit.h"
#include  "SwtchBtn.h"
#include  "CPropSht.h"
#include  "CmpChce.h"
#include  "grpeddlg.h"

#ifdef _OBJCHART_DLL

extern "C" OC_DATA int EditGraph(SRGraph *Graph);

#endif

#endif
