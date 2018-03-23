///////////////////////////////////////////////////////////////////////////////
// CmnGuids.h
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
// Author: Jeff Boenig
// <nl>Created: 3/99
// 
/////////////////////////////////////////////////////////////////////////////
//@doc
//@module CmnGuids.h | This module contains GUID declarations for
// the Stingray common library. If initguid.h is included before
// this file, the GUIDs are defined.

#include <objbase.h>

// {3D80F542-D51B-11d2-8CAB-0010A4F36466}
DEFINE_GUID(IID_ISize2D, 
0x3d80f542, 0xd51b, 0x11d2, 0x8c, 0xab, 0x0, 0x10, 0xa4, 0xf3, 0x64, 0x66);

// {3D80F544-D51B-11d2-8CAB-0010A4F36466}
DEFINE_GUID(IID_IBounds2D, 
0x3d80f544, 0xd51b, 0x11d2, 0x8c, 0xab, 0x0, 0x10, 0xa4, 0xf3, 0x64, 0x66);

// {3D80F545-D51B-11d2-8CAB-0010A4F36466}
DEFINE_GUID(IID_IVisual, 
0x3d80f545, 0xd51b, 0x11d2, 0x8c, 0xab, 0x0, 0x10, 0xa4, 0xf3, 0x64, 0x66);

// {47E1CE31-D500-11d2-8CAB-0010A4F36466}
DEFINE_GUID(IID_IEvent, 
0x47e1ce31, 0xd500, 0x11d2, 0x8c, 0xab, 0x0, 0x10, 0xa4, 0xf3, 0x64, 0x66);

// {47E1CE32-D500-11d2-8CAB-0010A4F36466}
DEFINE_GUID(IID_IWinEvent, 
0x47e1ce32, 0xd500, 0x11d2, 0x8c, 0xab, 0x0, 0x10, 0xa4, 0xf3, 0x64, 0x66);

// {47E1CE33-D500-11d2-8CAB-0010A4F36466}
DEFINE_GUID(IID_IMouseEvent, 
0x47e1ce33, 0xd500, 0x11d2, 0x8c, 0xab, 0x0, 0x10, 0xa4, 0xf3, 0x64, 0x66);

// {47E1CE34-D500-11d2-8CAB-0010A4F36466}
DEFINE_GUID(IID_ICommandEvent, 
0x47e1ce34, 0xd500, 0x11d2, 0x8c, 0xab, 0x0, 0x10, 0xa4, 0xf3, 0x64, 0x66);

// {47E1CE35-D500-11d2-8CAB-0010A4F36466}
DEFINE_GUID(IID_ICommandQueryEvent, 
0x47e1ce35, 0xd500, 0x11d2, 0x8c, 0xab, 0x0, 0x10, 0xa4, 0xf3, 0x64, 0x66);

// {47E1CE36-D500-11d2-8CAB-0010A4F36466}
DEFINE_GUID(IID_IEventRouter, 
0x47e1ce36, 0xd500, 0x11d2, 0x8c, 0xab, 0x0, 0x10, 0xa4, 0xf3, 0x64, 0x66);

// {47E1CE37-D500-11d2-8CAB-0010A4F36466}
DEFINE_GUID(IID_IEventQueue, 
0x47e1ce37, 0xd500, 0x11d2, 0x8c, 0xab, 0x0, 0x10, 0xa4, 0xf3, 0x64, 0x66);

// {47E1CE38-D500-11d2-8CAB-0010A4F36466}
DEFINE_GUID(IID_IEventListener, 
0x47e1ce38, 0xd500, 0x11d2, 0x8c, 0xab, 0x0, 0x10, 0xa4, 0xf3, 0x64, 0x66);

// {47E1CE39-D500-11d2-8CAB-0010A4F36466}
DEFINE_GUID(IID_IMouseListener, 
0x47e1ce39, 0xd500, 0x11d2, 0x8c, 0xab, 0x0, 0x10, 0xa4, 0xf3, 0x64, 0x66);

// {47E1CE3A-D500-11d2-8CAB-0010A4F36466}
DEFINE_GUID(IID_ICommandListener, 
0x47e1ce3a, 0xd500, 0x11d2, 0x8c, 0xab, 0x0, 0x10, 0xa4, 0xf3, 0x64, 0x66);

// {F0526982-E944-11d2-B412-006008AFE059}
DEFINE_GUID(IID_IMessage, 
0xf0526982, 0xe944, 0x11d2, 0xb4, 0x12, 0x0, 0x60, 0x8, 0xaf, 0xe0, 0x59);

// {F0526981-E944-11d2-B412-006008AFE059}
DEFINE_GUID(IID_ISubject, 
0xf0526981, 0xe944, 0x11d2, 0xb4, 0x12, 0x0, 0x60, 0x8, 0xaf, 0xe0, 0x59);

// {F0526983-E944-11d2-B412-006008AFE059}
DEFINE_GUID(IID_IObserver, 
0xf0526983, 0xe944, 0x11d2, 0xb4, 0x12, 0x0, 0x60, 0x8, 0xaf, 0xe0, 0x59);
