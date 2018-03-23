///////////////////////////////////////////////////////////////////////////////
// gxproc.h
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
// Authors: Daniel Jebarai, Stefan Hoenig
//

// gxproc.h : application-specific data for shared dlls
//

#ifndef _GXPROC_H_
#define _GXPROC_H_

#if _MFC_VER >= 0x0400
#include <afxtempl.h>
#endif

//
// GX_PROCESS_LOCAL implements application-specific data for shared dlls.
// The application-specific data structure must be derived from CGXNoTrackObject.
//
//
// Example (works both with 16 and 32 Bit):
// 
// struct GRID_API GX_APPSPECIFIC_STATE: public CGXNoTrackObject
// {
// 	int nLockMouseTicks;
//	int nScrollByPix;
// };                               
//
// GX_PROCESS_LOCAL(GX_APPSPECIFIC_STATE, _gxAppSpecificState)
//
// void myfunc
// {
//     int nScroll = _gxAppSpecificState->nScrollByPix;
//     ...
// }
//

#if _MFC_VER < 0x0400  // 16-Bit 

  #define CGXNoTrackObject	CObject

  #if defined(_GXDLL) // Objective Grid shared Dll

	// emulate PROCESS_LOCAL under 16 Bit environment.

	#define GX_PROCESS_LOCAL(class_name, ident_name) \
		struct _gx##class_name \
		{ \
			class_name* GetData() { \
				class_name* pData; \
				GX_APP_STATE* pAppState = GXGetAppState(); \
				if (!pAppState->m_mapProcessLocalData.Lookup(this, (void*&) pData)) \
					pAppState->m_mapProcessLocalData.SetAt(this, pData = new class_name); \
				return pData; \
			} \
			operator class_name*() { return GetData(); } \
			class_name* operator->() { return GetData(); } \
		} GXNEAR ident_name;

	#define GX_EXTERN_PROCESS_LOCAL(class_name, ident_name) \
		extern GX_PROCESS_LOCAL(class_name, ident_name)

  #else // static linking

	#define GX_PROCESS_LOCAL(class_name, ident_name) \
		struct _gx##class_name: public class_name \
		{ \
			class_name data; \
			class_name* GetData() { return &data; } \
			operator class_name*() { return &data; } \
			class_name* operator->() { return &data; } \
		} GXNEAR ident_name;

	#define GX_EXTERN_PROCESS_LOCAL(class_name, ident_name) \
		extern GX_PROCESS_LOCAL(class_name, ident_name)

  #endif

#elif _MFC_VER < 0x0420 // MFC 4.0 and 4.1

// CNoTrackObject stores application specific data

#define CGXNoTrackObject	CNoTrackObject
#define CGXProcessLocal		CProcessLocalObject

// define GX_PROCESS_LOCAL
#define GX_PROCESS_LOCAL PROCESS_LOCAL
#define GX_EXTERN_PROCESS_LOCAL EXTERN_PROCESS_LOCAL

#else // MFC 4.2 and later

// manipulate this such that it always stores data in a map and fishes it out of there
extern void AFXAPI AfxLockGlobals(int nLockType);
extern void AFXAPI AfxUnlockGlobals(int nLockType);

// same as CRIT_PROCESSLOCAL
#define  GXCRIT_PROCESSLOCAL 16
 
template<class TYPE>
class CGXProcessLocal : public CProcessLocalObject
{
protected:
	CTypedPtrMap<CMapPtrToPtr, AFX_MODULE_STATE*, TYPE*> m_ObjectMap;
	// Attributes
public:
	
	inline CGXProcessLocal(void)
	{
		// TRACE0("CGXProcessLocal object constructed\n");
	}

	inline ~CGXProcessLocal()
	{
		TYPE* pData = NULL;
		AFX_MODULE_STATE* pState = NULL;
		
		//ASSERT(0);

		for( POSITION pos = m_ObjectMap.GetStartPosition(); pos != NULL; )    
		{
			m_ObjectMap.GetNextAssoc( pos, pState, pData);

#ifdef _DEBUG
		//	afxDump << "~CGXProcessLocal called\n";
		//	afxDump << pState << " : Data value" << pData << "\n";
#endif  //_DEBUG

			// delete the object
			if(pData)
				delete pData;
		}
		
		m_ObjectMap.RemoveAll();
		m_pObject = NULL;
	};
	
	inline TYPE* GetData()
	{
		//TRACE0("CGXProcessLocal invoked\n");
		TYPE* pData = NULL;
		if(m_ObjectMap.Lookup(AfxGetModuleState(), pData))
		{
			//TRACE1("CGXProcessLocal::Module State %p\n", AfxGetModuleState());
			//TRACE1("CGXProcessLocal::Returning old object %p\n", pData);
			return pData;
		}
		
		pData = (TYPE*)GetData(&CreateObject);
		ASSERT(pData != NULL);
		m_ObjectMap.SetAt(AfxGetModuleState(), pData);
		//TRACE1("CGXProcessLocal::Module State %p\n", AfxGetModuleState());
		//TRACE1("CGXProcessLocal::Creating new object %p\n", pData);
			
		return pData;
	}
	inline TYPE* GetDataNA()
		{
			TYPE* pData = NULL;
			if(m_ObjectMap.Lookup(AfxGetModuleState(), pData))
				return pData;
			else
				return (TYPE*)m_pObject; 
		}
	
	inline operator TYPE*()
		{ return GetData(); }
	inline TYPE* operator->()
		{ return GetData(); }

// Implementation
public:
	static CNoTrackObject* AFXAPI CreateObject()
		{ return new TYPE; }

	inline CNoTrackObject* GetData(CNoTrackObject* (AFXAPI* pfnCreateObject)())
	{
		pfnCreateObject;
		{
			AfxLockGlobals(GXCRIT_PROCESSLOCAL);
			TRY
			{
				m_pObject = new TYPE;
			}
			CATCH_ALL(e)
			{
				AfxUnlockGlobals(GXCRIT_PROCESSLOCAL);
				THROW_LAST();
			}
			END_CATCH_ALL
			AfxUnlockGlobals(GXCRIT_PROCESSLOCAL);
		}
		return m_pObject;
	}

};

// CNoTrackObject stores application specific data

#define CGXNoTrackObject	CNoTrackObject

// define GX_PROCESS_LOCAL
#define GX_PROCESS_LOCAL(class_name, ident_name) \
	AFX_DATADEF CGXProcessLocal<class_name> ident_name;

#define GX_EXTERN_PROCESS_LOCAL(class_name, ident_name) \
	extern AFX_DATA GX_PROCESS_LOCAL(class_name, ident_name)

#endif // 32 Bit

#endif //_GX_PROC_H_
