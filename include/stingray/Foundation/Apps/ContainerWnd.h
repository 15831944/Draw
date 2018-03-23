///////////////////////////////////////////////////////////////////////////////
// ContainerWnd.h : SFL Window Container
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
// Description:  Integration between windowing framework and Layout Manager
//


#pragma once

#if !defined(_SFL)
#define _SFL
#endif

#include <foundation\SflCommon.h>
#include <foundation\Layout\LayoutManager.h>


namespace stingray {
namespace foundation {


/////////////////////////////////////////////////////////////////////////////
// CContainerImplBase- Container window description
//
//
//@doc CContainerImplBase
//
//@class CContainerImplBase | This class is the main class mixing a window class with 
// an SFL plugin
//
//@tcarg typename | _Derived | The ultimately-derived class
//@tcarg typename | _Traits | Window creation flags 
//@tcarg typename | _BaseImpl | The base class 
//@tcarg typename | _LayoutPlugin | Layout plugin 
//
//@base public | _BaseImpl
//@base public | _LayoutPlugin
//
//@comm CContainerImplBase is the main class mixing a window class 
// with one of SFL's layout plugins. 
//
template <typename _Derived, typename _Traits, typename _BaseImpl, typename _LayoutPlugin >
class CContainerImplBase:
	public _BaseImpl,
	public _LayoutPlugin
{
protected:
	typedef _BaseImpl _WindowBaseImpl;
	typedef CContainerImplBase<_Derived, _Traits, _BaseImpl, _LayoutPlugin> _ContainerBase;

public:
	BEGIN_MSG_MAP(CContainerImplBase)
		CHAIN_MSG_MAP(_LayoutPlugin)
	END_MSG_MAP()
};


/////////////////////////////////////////////////////////////////////
// Specific specializations based on exepected use cases 
// of the container class

/////////////////////////////////////////////////////////////////////////////
// CContainerWindowImpl - Container window Implementation
//
//@doc CContainerWindowImpl
//
//@class CContainerWindowImpl | Convenient implementation version of a container window.
//
//@tcarg typename | _Derived | The ultimately-derived class
//@tcarg typename | _Traits | Window creation flags 
//@tcarg typename | _Base | The base class 
//@tcarg typename | _LayoutPlugin | Layout manager base class
//
//@base public | <c CContainerImplBase>
//
//@comm CContainerWindowImpl is a convenient implementation of the container window 
//
template <typename _Derived, typename _Traits, typename _Base = CWindow, typename _LayoutPlugin = foundation::CLayoutManager<_Derived> >
class CContainerWindowImpl : 
	public CContainerImplBase<_Derived, _Traits, CWindowImpl<_Derived, _Base, _Traits>, _LayoutPlugin >
{
};

/////////////////////////////////////////////////////////////////////////////
// CContainerDialogImpl - Container dialog Implementation
//
//@doc CContainerDialogImpl
//
//@class CContainerDialogImpl | Convenient implementation version of a container window.
//
//@tcarg typename | _Derived | The ultimately-derived class
//@tcarg typename | _Traits | Window creation flags 
//@tcarg typename | _Base | The base class 
//
//@base public | <c CContainerImplBase>
//
//@comm CContainerDialogImpl is a convenient implementation of the container dialog 
//
template <typename _Derived>
class CContainerDialogImpl : 
	public CContainerImplBase<_Derived, CNullTraits, CAxDialogImpl<_Derived>, foundation::CLayoutManager<_Derived, WM_INITDIALOG> >
{
};


#if defined(__ATLCTL_H__)
// Only when implementing ActiveX controls
template <typename _Derived, typename _Traits = CControlWinTraits>
class CContainerControlImpl : 
	public CContainerImplBase<_Derived, _Traits, CComCompositeControl<_Derived>, foundation::CLayoutManager<_Derived, WM_INITDIALOG> >
{
};

#endif


};	// namespace stingray::foundation
};	// namespace stingray
