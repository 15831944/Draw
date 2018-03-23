///////////////////////////////////////////////////////////////////////////////
// DockAll.h
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
//  Description:	Docking.h - Advanced docking composite header.
//  Created:		December 1997
//

#ifndef __ADV_DOCKING_HEADERS__
#define __ADV_DOCKING_HEADERS__

// Docking Node Infrastructure
#include "DockIFace.h"
#include "DockHT.h"
#include "DockFactory.h"
#include "DockInfo.h"
#include "DockMgr.h"

// Drag/Drop framework
#include "..\..\DragDrop\StartDragCore.h"
#include "..\..\DragDrop\DragBase.h"
#include "..\..\DragDrop\LocalMsgDragTask.h"
#include "..\..\DragDrop\OleDragTask.h"
#include "DragDrop\DragDropDockFeat.h"
#include "DragDrop\DockListn.h"

// Docking Initiators
#include "DefDockBase.h"

// Docking Targets
#include "Targets\StatGridTarg.h"
#include "Targets\DynGridTarg.h"

// Floating Window Support
#include "Floating\FloatNode.h"
#include "Floating\MiniFloatWnd.h"

// Frame Window Support
#include "Frame\DockSizeNode.h"
#include "Frame\FrameDockBase.h"
#include "Frame\FrameDock.h"

#endif 		// __ADV_DOCKING_HEADERS__
