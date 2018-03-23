///////////////////////////////////////////////////////////////////////////////
// LyoutAll.h
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
//  Author:			Mark Isham
//  Description:	LyoutAll.h - Layout Mgr composite header
//  Created:		December 1997
//
//
//	This file is included via "ProAll.h"
//

#ifndef __LAYOUT_MGR_HEADERS_
#define __LAYOUT_MGR_HEADERS_

// Base Types

#ifndef __SEC_NODE_IFACES_H__
#include "toolkit\layout\NodeIFace.h"
#endif

#ifndef __SECLAYOUTNODE_H__
#include "toolkit\layout\layoutnd.h"
#endif

#ifndef __SECLAYOUT_DOCKING_CONTAINER_H__
#include "toolkit\layout\Container.h"
#endif

// Worker Classes

#ifndef __SECLAYOUT_FACTORY_H__
#include "toolkit\layout\factory.h"
#endif

#ifndef __SEC_LN_HITTEST_H__
#include "toolkit\layout\NodeHT.h"
#endif 

#ifndef __SEC_LAYOUT_NODE_DIAGNOSTIC_ROUTINES__
#include "toolkit\layout\NodeDiag.h"
#endif

#ifndef __SEC_LAYOUT_MGR_UNDO_FUNCTION_H__
#include "toolkit\layout\UndoNode.h"
#endif

// Derived Types
#ifndef __SECLAYOUT_LISTENER_H__
#include "toolkit\layout\LayListn.h"
#endif

#ifndef __SECLAYOUTNODEWND_H__
#include "toolkit\layout\nodewnd.h"
#endif

#ifndef __SECLAYOUTNODEDC_H__
#include "toolkit\layout\NodeDC.h"
#endif

#ifndef __SECLAYOUTNODE_BORDER_GRAPHIC_H___
#include "toolkit\layout\BorderGraphic.h"
#endif

// Composite Node Algorithms
#ifndef __SECLAYOUT_ALIGN_H__
#include "toolkit\layout\align.h"
#endif

#ifndef __SECLAYOUT_GRID_H__
#include "toolkit\layout\grid.h"
#endif

#ifndef __SECLAYOUT_GRIDBAG_H__
#include "toolkit\layout\gridbag.h"
#endif

#ifndef __SECLAYOUT_RELATIVE_H__
#include "toolkit\layout\relative.h"
#endif

#ifndef __SECLAYOUT_SCALE_H__
#include "toolkit\layout\scale.h"
#endif

#include "toolkit\layout\border.h"
#include "toolkit\layout\BorderClient.h"
#include "toolkit\layout\DynGrid.h"
#include "toolkit\layout\DynGrid2d.h"

// Splitter Functionality
// (nodesplt.h in the ProPre prefix header for proper MI resolution)
#ifndef __SECSPLITTERBASE_H
#include "toolkit\layout\splitter.h"
#endif

#ifndef __SECSPLITTERWND_H
#include "toolkit\layout\splitwnd.h"
#endif

#include "toolkit\layout\nodesplt.h"
#include "toolkit\layout\SizeNode.h"

#endif 		// __LAYOUT_MGR_HEADERS_
