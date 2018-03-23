///////////////////////////////////////////////////////////////////////////////
// secmesmac.h
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

//
// These macros are courtesy of the Objective Grid PRO (CCE) product
//

#ifndef _SECMESMACROS_H
#define _SECMESMACROS_H

#define SECRUNTIME_CLASS(class_name) ((CRuntimeClass*)(&class_name::class##class_name))

#ifdef _AFXDLL
#define SECIMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew, act_base) \
	CRuntimeClass* PASCAL class_name::_GetBaseClass() \
		{ return SECRUNTIME_CLASS(act_base); } \
	const AFX_DATADEF CRuntimeClass class_name::class##class_name = { \
		#class_name, sizeof(class class_name), wSchema, pfnNew, \
			&class_name::_GetBaseClass, NULL }; \
	CRuntimeClass* class_name::GetRuntimeClass() const \
		{ return RUNTIME_CLASS(class_name); } \

#define SECIMPLEMENT_DYNCREATE(class_name, base_class_name, act_base) \
	CObject* PASCAL class_name::CreateObject() \
		{ return new class_name; } \
	SECIMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, \
		class_name::CreateObject, act_base)
#else
#define SECIMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew, act_base) \
	const AFX_DATADEF CRuntimeClass class_name::class##class_name = { \
		#class_name, sizeof(class class_name), wSchema, pfnNew, \
			RUNTIME_CLASS(act_base), NULL }; \
	CRuntimeClass* class_name::GetRuntimeClass() const \
		{ return RUNTIME_CLASS(class_name); } \

#define SECIMPLEMENT_DYNCREATE(class_name, base_class_name, act_base) \
	CObject* PASCAL class_name::CreateObject() \
		{ return new class_name; } \
	SECIMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, \
		class_name::CreateObject, act_base)
#endif

//[VC7] MFC version seperation
#if (_MFC_VER < 0x0700)
#ifdef _AFXDLL
#define SECBEGIN_MESSAGE_MAP(theClass, baseClass) \
	template<class baseClass>\
	const AFX_MSGMAP* PASCAL theClass##<baseClass>::_GetBaseMessageMap() \
		{ return &baseClass::messageMap; } \
	template<class baseClass>\
	const AFX_MSGMAP* theClass##<baseClass>::GetMessageMap() const \
{ return &theClass##<baseClass>::messageMap; } \
	template<class baseClass>\
	AFX_DATADEF const AFX_MSGMAP theClass##<baseClass>::messageMap = \
	{ &theClass::_GetBaseMessageMap, &theClass##<baseClass>::_messageEntries[0] }; \
	template<class baseClass>\
	const AFX_MSGMAP_ENTRY theClass##<baseClass>::_messageEntries[] = \
	{ \

#else
#define SECBEGIN_MESSAGE_MAP(theClass, baseClass) \
	template<class baseClass>\
	const AFX_MSGMAP* theClass##<baseClass>::GetMessageMap() const\
{ return &theClass##<baseClass>::messageMap; } \
	template<class baseClass>\
	AFX_DATADEF const AFX_MSGMAP theClass##<baseClass>::messageMap = \
	{ &baseClass::messageMap, &theClass##<baseClass>::_messageEntries[0] }; \
	template<class baseClass>\
	const AFX_MSGMAP_ENTRY theClass##<baseClass>::_messageEntries[] = \
	{ \

#endif //_AFXDLL

#else //_MFC_VER

#ifdef _AFXDLL
#define SECBEGIN_MESSAGE_MAP(theClass, baseClass) \
	template<class baseClass>\
	const AFX_MSGMAP* PASCAL theClass##<baseClass>::GetThisMessageMap() \
		{ return &baseClass::messageMap; } \
	template<class baseClass>\
	const AFX_MSGMAP* theClass##<baseClass>::GetMessageMap() const \
{ return &theClass##<baseClass>::messageMap; } \
	template<class baseClass>\
	AFX_DATADEF const AFX_MSGMAP theClass##<baseClass>::messageMap = \
	{ &theClass::GetThisMessageMap, &theClass##<baseClass>::_messageEntries[0] }; \
	template<class baseClass>\
	const AFX_MSGMAP_ENTRY theClass##<baseClass>::_messageEntries[] = \
	{ \

#else
#define SECBEGIN_MESSAGE_MAP(theClass, baseClass) \
	template<class baseClass>\
	const AFX_MSGMAP* theClass##<baseClass>::GetMessageMap() const\
{ return &theClass##<baseClass>::messageMap; } \
	template<class baseClass>\
	AFX_DATADEF const AFX_MSGMAP theClass##<baseClass>::messageMap = \
	{ &baseClass::messageMap, &theClass##<baseClass>::_messageEntries[0] }; \
	template<class baseClass>\
	const AFX_MSGMAP_ENTRY theClass##<baseClass>::_messageEntries[] = \
	{ \

#endif //_AFXDLL

#endif //_MFC_VER

// use for intermediate base classes (refer designer code for sample).
//[VC7] MFC Version Seperation
#if (_MFC_VER < 0x0700)
#ifdef _SECDX_USE_DLL_MAP
#ifdef _AFXDLL
#define SECINTERBEGIN_MESSAGE_MAP(theClass, baseClass, templateClass) \
	template<class templateClass>\
	const AFX_MSGMAP* PASCAL theClass##<templateClass>::_GetBaseMessageMap() \
		{ return &baseClass::messageMap; } \
	template<class templateClass>\
	const AFX_MSGMAP* theClass##<templateClass>::GetMessageMap() const \
{ return &theClass##<templateClass>::messageMap; } \
	template<class templateClass>\
	AFX_DATADEF const AFX_MSGMAP theClass##<templateClass>::messageMap = \
	{ &theClass::_GetBaseMessageMap, &theClass##<templateClass>::_messageEntries[0] }; \
	template<class templateClass>\
	const AFX_MSGMAP_ENTRY theClass##<templateClass>::_messageEntries[] = \
	{ \
#else

#define SECINTERBEGIN_MESSAGE_MAP(theClass, baseClass, templateClass) \
	template<class templateClass>\
	const AFX_MSGMAP* theClass##<templateClass>::GetMessageMap() const \
{ return &theClass##<templateClass>::messageMap; } \
	template<class templateClass>\
	AFX_DATADEF const AFX_MSGMAP theClass##<templateClass>::messageMap = \
	{ &baseClass::messageMap, &theClass##<templateClass>::_messageEntries[0] }; \
	template<class templateClass>\
	const AFX_MSGMAP_ENTRY theClass##<templateClass>::_messageEntries[] = \
	{ \

#endif
#endif //0 excluded

#else //_MFC_VER

#ifdef _SECDX_USE_DLL_MAP
#ifdef _AFXDLL
#define SECINTERBEGIN_MESSAGE_MAP(theClass, baseClass, templateClass) \
	template<class templateClass>\
	const AFX_MSGMAP* PASCAL theClass##<templateClass>::GetThisMessageMap() \
		{ return &baseClass::messageMap; } \
	template<class templateClass>\
	const AFX_MSGMAP* theClass##<templateClass>::GetMessageMap() const \
{ return &theClass##<templateClass>::messageMap; } \
	template<class templateClass>\
	AFX_DATADEF const AFX_MSGMAP theClass##<templateClass>::messageMap = \
	{ &theClass::GetThisMessageMap, &theClass##<templateClass>::_messageEntries[0] }; \
	template<class templateClass>\
	const AFX_MSGMAP_ENTRY theClass##<templateClass>::_messageEntries[] = \
	{ \
#else

#define SECINTERBEGIN_MESSAGE_MAP(theClass, baseClass, templateClass) \
	template<class templateClass>\
	const AFX_MSGMAP* theClass##<templateClass>::GetMessageMap() const \
{ return &theClass##<templateClass>::messageMap; } \
	template<class templateClass>\
	AFX_DATADEF const AFX_MSGMAP theClass##<templateClass>::messageMap = \
	{ &baseClass::messageMap, &theClass##<templateClass>::_messageEntries[0] }; \
	template<class templateClass>\
	const AFX_MSGMAP_ENTRY theClass##<templateClass>::_messageEntries[] = \
	{ \

#endif
#endif //0 excluded

#endif //_MFC_VER

#endif //_SECMESMACROS_H
