///////////////////////////////////////////////////////////////////////////////
// SECPidlMgr.h
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

#if !defined(AFX_SECPIDLMGR_H__FA3502CA_728D_4DA8_AF8D_4B32B11A7858__INCLUDED_)
#define AFX_SECPIDLMGR_H__FA3502CA_728D_4DA8_AF8D_4B32B11A7858__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <shlobj.h>
/////////////////////////////
// SECPidlMgr
// AutoDuck tag block block for SECPidlMgr  

//@doc SECPidlMgr
//@mdata CComPtr &lt; IMalloc &gt;  | SECPidlMgr | m_spMalloc | A smart pointer of IMalloc interface. It is
//always valid as long as this object is alive.

//@doc SECPidlMgr
//@mfunc | SECPidlMgr | SECPidlMgr | It obtains a valid IMalloc interface pointer from the shell.
//If it cannot successfully obtain a valid IMalloc interface pointer, it will 
//delete itself. The obtained IMalloc interface pointer is stored in a COM smart
//pointer.
//@xref <c SECPidlMgr>

//@doc SECPidlMgr
//@mfunc void | SECPidlMgr | Delete | This function will free the memory used be the passed PIDL. If the passed
//PIDL is empty if will do nothing.
//@rdesc void 
//@parm LPITEMIDLIST | pidl | The PIDL to be deleted.
//@xref <c SECPidlMgr>

//@doc SECPidlMgr
//@mfunc LPITEMIDLIST | SECPidlMgr | CreateItem | This function creates an PIDL from a given block memory of data. Even though this
//function is virtual, you generallly will not need to override this function. Instead, if
//the data in your template class T can change size dynamically, you create a helper function
//to place your data in the template class T into a single contiguous block of memory and then
//pass the block of memory into this function giving the function the size of the memory. 
//See MirrorDirectory sample for an example for what you need to do.
//@rdesc LPITEMIDLIST Return a created PIDL. The PIDL should be freed using IMalloc obtained from
//the shell. You can safely use Delete method of any instance of this class.
//@parm LPBYTE | pData | A block of memory that contains the data in the layouted as in the template class T.
//The memory used by pData is not freed by this function. So caller is responsible to free the memory
//used by pData.
//@parm  SEC_UINT | nInSize | The size of the memory block.
//@xref <c SECPidlMgr>

//@doc SECPidlMgr
//@mfunc LPITEMIDLIST | SECPidlMgr | Copy | This function will make a new copy of the passing PIDL.
//@rdesc LPITEMIDLIST Return the new copy of PIDL. The caller will own the memory of this new copy of PIDL
//and should free it using IMalloc obtained from the shell.
//@parm LPCITEMIDLIST | pidlSrc | The source PIDL to copy from. It's memroy is not touched by this function.
//@xref <c SECPidlMgr>

//@doc SECPidlMgr
//@mfunc T* | SECPidlMgr | GetDataPointer | This function obtains the position of the data in the first PIDL item and cast the pointer back
//to our data type.
//@rdesc T* A pointer to our data in the first PIDL item. Caller should not try to free the memory pointed
//by the returned pointer.
//@parm LPCITEMIDLIST | pidl | The PIDL we are looking for data.
//@xref <c SECPidlMgr>

//@doc SECPidlMgr
//@mfunc T* | SECPidlMgr | GetLastDataPointer | This function obtains the position of the data in the last PIDL item and cast the pointer back
//to our data type.
//@rdesc T* A pointer to our data in the last PIDL item. Caller should not try to free the memory pointed 
//by the returned pointer.
//@parm LPCITEMIDLIST | pidl | The PIDL we are looking for data.
//@xref <c SECPidlMgr>

//@doc SECPidlMgr
//@mfunc SEC_UINT | SECPidlMgr | GetSize | This function calculate the total size of the given PIDL
//@rdesc SEC_UINT Return the totoal size of the given PIDL.
//@parm LPCITEMIDLIST | pidl | The PIDL to calculate the size for.
//@xref <c SECPidlMgr>

//@doc SECPidlMgr
//@mfunc LPITEMIDLIST | SECPidlMgr | GetNextItem | This function gets the next PIDL in the given PIDL.
//@rdesc LPITEMIDLIST Return the next PIDL. Caller should not free the memroy used by this PIDL.
//@parm LPCITEMIDLIST | pidl | The PIDL to look for next PIDL.
//@xref <c SECPidlMgr>

//@doc SECPidlMgr
//@mfunc LPITEMIDLIST | SECPidlMgr | GetLastItem | This function gets the last PIDL in the given PIDL.
//@rdesc LPITEMIDLIST Return the last PIDL. Caller should not free the memory used by this PIDL.
//@parm LPCITEMIDLIST | pidl | The PIDL to look for last PIDL.
//@xref <c SECPidlMgr>

//@doc SECPidlMgr
//@mfunc LPITEMIDLIST | SECPidlMgr | Concatenate | This function will create a new copy of PIDL that is a concatenation of the give two PIDLs with
//the first pidl1 on the head and pidl2 at the end. Any of the two passing PIDLs can be NULL.
//@rdesc LPITEMIDLIST Return the new copy of PIDL. Caller is responsible to free the memory used by this PIDL.
//@parm LPCITEMIDLIST | pidl1 | The first source PIDL. It's memory is not touched by this function.
//@parm  LPCITEMIDLIST | pidl2 | The second source PIDL. It's memory is not touched by this function.
//@xref <c SECPidlMgr>

//@doc SECPidlMgr
//@mfunc LPITEMIDLIST* | SECPidlMgr | DupPidlArray | This function creates a new copy of the given PIDL
//array. If the source PIDL array is NULL or the count is not positive, this function return NULL.
//@rdesc LPITEMIDLIST* Return the new copy of PIDL array if succeeded, otherwise return NULL.
//@parm LPCITEMIDLIST* | aSrcPidls | The source PIDL array. It's memory is not changed by this function.
//@parm int	| nCount | The number of PIDLs in the source PIDL array. 
//@xref <c SECPidlMgr>

//@doc SECPidlMgr
//@mfunc void | SECPidlMgr | DeletePidlArray | Free all the memory used by the given PIDL array, i.e.
//the memory used the elements of the array and the array itself.
//@rdesc void
//@parm LPITEMIDLIST* | apidls | The PIDL array to be deleted.
//@parm int | nCount | The number of elements in the PIDL array.
//@xref <c SECPidlMgr>

// adinsert AutoDuck insertion point for SECPidlMgr  
//@doc SECPidlMgr  
//@class SECPidlMgr
//@comm This class encapsulates the operations on PIDL. It requires a template argument that is
//only used to access the data in the PIDL in a type safe way. There is a very important
//requirements to the data in this template class T. That is, all the data in this class
//has to in a single contigous memory block. Generally, you don't need to override this
//class. However, if you are data type class T dyamically change size, you should first
//layout the data in a memory block before call CreateItem method giving it the memory
//location and the memory size. Refer to MirrorDirectory sample for an example. This
//class is intended to be used in the shell and namespace extension development. As documented
//in the Win32 SDK, the memory management should be handled using IMalloc interface obtained
//from the shell. So you should always use instance of this class to create and delete PIDL.
//Whenever a instance of this class is successfully created, it will have a usable IMalloc 
//interface pointer.
//@tcarg class | T | The structured data in the PIDL
template<typename T>   
class SECPidlMgr  
{
protected:
	//@cmember
	/* Memory managing object */
	CComPtr<IMalloc> m_spMalloc;

public:
	//@cmember
	/* Constructor	*/
	inline SECPidlMgr()
	{
		if( FAILED(SHGetMalloc(&m_spMalloc)) )
		{
			delete this;
			return;
		}
		ATLASSERT(m_spMalloc != NULL);
	}
	virtual ~SECPidlMgr()
	{}

	//@cmember
	/* Delete the given pidl */
	inline void Delete(LPITEMIDLIST pidl)
	{
		if( pidl != NULL )
			m_spMalloc->Free(pidl);
	}
	//@cmember
	/* Create PIDL from given data */
	virtual LPITEMIDLIST CreateItem(LPBYTE pData, SEC_UINT nInSize)
	{
		SEC_UINT uSize = sizeof(ITEMIDLIST) + nInSize;

		LPITEMIDLIST pidlRet = reinterpret_cast<LPITEMIDLIST>(
			m_spMalloc->Alloc(uSize + sizeof(ITEMIDLIST) ) );
		if( pidlRet != NULL )
		{
			// Possible Loss of Data.
			LPITEMIDLIST pidlTmp = pidlRet;
			// Possible Loss of Data.
			pidlTmp->mkid.cb = static_cast<USHORT>(uSize);
			LPBYTE pBuf = pidlTmp->mkid.abID;

			CopyMemory(pBuf, pData, nInSize);

			// Set the NULL terminating end;
			pidlTmp = GetNextItem(pidlTmp);
			pidlTmp->mkid.cb = 0;
			pidlTmp->mkid.abID[0] = 0;
		}
		return pidlRet;
	}

	//@cmember
	/* Make a copy of the given pidl */
	inline LPITEMIDLIST Copy(LPCITEMIDLIST pidlSrc)
	{
		LPITEMIDLIST pidlTarget = NULL;
		SEC_UINT cbSrc = 0;
		if( pidlSrc == NULL )
			return NULL;
		cbSrc = GetSize(pidlSrc);
		pidlTarget = reinterpret_cast<LPITEMIDLIST>(m_spMalloc->Alloc(cbSrc));
		if( pidlTarget == NULL )
			return NULL;
		ATLASSERT(pidlTarget != NULL);
		
		CopyMemory(pidlTarget, pidlSrc, cbSrc);
		return pidlTarget;
	}

	//@cmember
	/* Get the pointer to the data in the given pidl */
	inline T*	GetDataPointer(LPCITEMIDLIST pidl)
	{
		if( pidl == NULL )
			return NULL;
		return (T*)(pidl->mkid.abID);
	}
	//@cmember
	/* Get the pointer to the data of the last pidl */
	inline T*	GetLastDataPointer(LPCITEMIDLIST pidl)
	{
		if( pidl == NULL )
			return NULL;
		LPITEMIDLIST p = GetLastItem(pidl);
		return (T*)(p->mkid.abID);
	}

	//@cmember
	/* Get the totoal size of the pidl */
	inline SEC_UINT GetSize(LPCITEMIDLIST pidl)
	{
		SEC_UINT cbTotal = 0;
		LPITEMIDLIST	pidlTmp = const_cast<LPITEMIDLIST>(pidl);
		if( pidlTmp != NULL )
		{
			while( pidlTmp->mkid.cb != 0 )
			{
				cbTotal += pidlTmp->mkid.cb;
				pidlTmp = GetNextItem(pidlTmp);
			}

			// There is a terminating item at the end of the list. So we
			// need to add the size of this item
			cbTotal += sizeof(ITEMIDLIST);
		}
		return cbTotal;
	}
 
	//@cmember
	/* Get Next pidl of the given pidl */
	inline LPITEMIDLIST GetNextItem(LPCITEMIDLIST pidl)
	{
		if( pidl != NULL )
		{
			return (LPITEMIDLIST)(LPBYTE)(((LPBYTE)pidl) + pidl->mkid.cb);
		}
		else
			return NULL;
	}
	//@cmember
	/* Get the last pidl of the given pidl */
	inline LPITEMIDLIST GetLastItem(LPCITEMIDLIST pidl)
	{
		LPITEMIDLIST pidlLast = NULL;
		if( pidl != NULL )
		{
			while(pidl->mkid.cb != 0 )
			{
				pidlLast = const_cast<LPITEMIDLIST>(pidl);
				pidl = GetNextItem(pidl);
			}
		}
		return pidlLast;
	}
	//@cmember
	/* Create a pidl that is the concatenation of the given two pidls */
	inline LPITEMIDLIST Concatenate(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
	{
		if( pidl1 == NULL && pidl2 == NULL)
			return NULL;
		if( pidl1 == NULL )
			return Copy(pidl2);
		if( pidl2 == NULL )
			return Copy(pidl1);

		LPITEMIDLIST pidlNew = NULL;
		SEC_UINT uSize1, uSize2;

		uSize1 = GetSize(pidl1) - sizeof(ITEMIDLIST);
		uSize2 = GetSize(pidl2);

		pidlNew = (LPITEMIDLIST)m_spMalloc->Alloc(uSize1 + uSize2);
		if( pidlNew != NULL )
		{
			CopyMemory(pidlNew, pidl1, uSize1);
			CopyMemory( ((LPBYTE)pidlNew) + uSize1, pidl2, uSize2);
		}
		return pidlNew;
	}
	
	//@cmember
	/* Duplicate an PIDL array */
	inline LPITEMIDLIST* DupPidlArray(LPCITEMIDLIST* aSrcPidls, int nCount)
	{
		if( aSrcPidls == NULL || nCount <= 0 )
			return NULL;
		LPITEMIDLIST* ppidl = (LPITEMIDLIST*)m_spMalloc->Alloc(nCount * sizeof(LPITEMIDLIST));
		if( ppidl != NULL )
		{
			::ZeroMemory(ppidl, nCount * sizeof(LPITEMIDLIST));
			for(int i = 0; i < nCount; i++)
				ppidl[i] = Copy(aSrcPidls[i]);
		}
		return ppidl;
	}

	//@cmember
	/* Free the memory used by the given PIDL array */
	inline void DeletePidlArray(LPITEMIDLIST* apidls, int nCount)
	{
		if( apidls != NULL )
		{
			for(int i = 0; i < nCount; i++)
				m_spMalloc->Free(apidls[i]);
			m_spMalloc->Free(apidls);
		}
	}
};

#endif // !defined(AFX_SECPIDLMGR_H__FA3502CA_728D_4DA8_AF8D_4B32B11A7858__INCLUDED_)
