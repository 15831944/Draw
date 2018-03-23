///////////////////////////////////////////////////////////////////////////////
// ComDoc.h
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


/////////////////////////////////////////////////////////////
// The text comments in this file are formatted to generate
// a help file on build using Microsoft's free Autoduck tool.
// The help file is available with this source and it is
// recommended that you use this file in conjunction with the
// mfc help files.
/////////////////////////////////////////////////////////////
//
//@doc
//@module ComDoc.h | class definition  of the SECComDoc class<nl>
//Written by Bob Powell (www.roguewave.com)

//
/////////////////////////////////////////////////////////////////////////////
#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#ifndef __SECCOMDOC__
#define __SECCOMDOC__

#define SEC_NOOP			0x00000000
#define SEC_CLIPBOARD_TEXT	0x00000001
#define SEC_GMEM_INIT		0x00000002
#define SEC_DOC_UPDATE		0x00000003 // broadcast to all owned documents
#define SEC_USER_COMMAND	0x00008000 // ALL commands below 32768 are reserved by possible future SEC++ operations

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block for SECComDoc 
//@doc SECComDoc

//@mdata BOOL  | SECComDoc | m_bUpdatingParent | TRUE while this document is updating the parent document

//@mdata POSITION | SECComDoc | m_LinkPosition | POSITION used in the iteration of linked documents (protected)

//@mdata CPtrList | SECComDoc | m_DocLinkList | List of pointers to all the SECComDoc-based documents linked to this parent document (protected)

//@mdata SECComDoc * | SECComDoc | m_pParent | Pointer to the parent of this document -- Null if this document is the top level in a chain (protected)

// adinsert AutoDuck insertion point for SECComDoc 
//$head The "ComDoc" system
//$level 1
//@class SECComDoc is a document class extension with special linking and inter-document communication abilities.
//@devnote To use the special functions described here, your document manager must be derived from <c SECDocManager>.<nl><nl>
//Documents based on SECComDoc may own or be parents of other documents. 
//Child documents need not be of the same type as their parents. 
//They may or may not be updated by the parent. 
//All documents, regardless of their child or parent status, will behave like ordinary documents 
//within the application.<nl><nl>
//From a developer's point of view, the process of maintaining child lists and notifications is automatic. 
//You simply call the OnNewDocument function with the optional parameters, and child documents 
//derived from SECComDoc will add themselves to the parent's document list for dynamic updating.<nl>
//If a child document is destroyed, it will inform its parent (and all its children) of the fact 
//and its links to the document will be broken automatically.
class SECComDoc : public CDocument
{
//@access Protected data members
protected:
	//@cmember
	/* TRUE while this document is updating the parent document*/
	BOOL m_bUpdatingParent;
	//@cmember
	/* Position of the current document in the update list*/
	POSITION m_LinkPosition;
	//@cmember
	/* List of documents that have been opened and may be updated by this document*/
	CPtrList m_DocLinkList;
	//@cmember
	/* Pointer to the document which opened and updates this document*/
	SECComDoc * m_pParent;

	//@access protected member functions
protected: // create from serialization only
	//@cmember
	/* Constructor*/
	CHART_API SECComDoc();

	CHART_DECLARE_DYNCREATE(SECComDoc)

	//@cmember
	/* Called by the ProcessDocumentCommand routine in response to a SEC_DOC_UPDATE command*/
	CHART_API virtual BOOL SecDocUpdate(SEC_UINT nSubCode, SEC_DWORD dwData=NULL);
	//@cmember
	/* Override this function to process your own commands*/
	CHART_API virtual BOOL ProcessUserCommand(SEC_UINT nOpCode, SEC_UINT nSubCode, SEC_DWORD dwData);
	//@cmember
	/* Called in response to a SEC_CLIPBOARD_TEXT command*/
	CHART_API virtual BOOL ClipboardText(void); // starter function which you must alter to convert between what is on the text clipboard and the internal document structure.
	//@cmember
	/* Called in response to a SEG_GMEM_INIT command*/
	CHART_API virtual BOOL GmemInit(SEC_UINT code,HANDLE hMem);

// Attributes
public:
	//@cmember
	/* Called to inform the parent document of a change in the child -- */
	//the parent may subsequently update its own document and those of its other children as a result.
	CHART_API virtual BOOL UpdateParentDocument(SEC_UINT nSubCode, SEC_DWORD dwData);
	//@cmember
	/* Retrieves a pointer to the next linked document in the list*/
	CHART_API virtual SECComDoc * GetNextLink(POSITION& pos);
	//@cmember
	/* Retrieves a pointer to the previous linked document in the list*/
	CHART_API virtual SECComDoc * GetPrevLink(POSITION& pos);
	//@cmember
	/* Retrieves the first document position in the list -- this POSITION may be used to iterate the list.*/
	CHART_API virtual POSITION GetHeadLinkPosition();
	//@cmember
	/* Returns the number of documents currently linked to this one*/
	CHART_API virtual int GetLinkCount();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECComDoc)
public:
	CHART_API virtual BOOL OnNewDocument();
	CHART_API virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

/////////////////////////////////////////////////////////////
// SEC++ Special parameter passing system for new documents 
// Overridden OnOpenDocument(...) has expandable features.

//@access Public member functions
public:

	//@cmember
	/* Decodes document commands*/
	CHART_API virtual BOOL ProcessDocumentCommand(SEC_UINT nOpCode, SEC_UINT nSubCode, SEC_DWORD dwData);
	//@cmember
	/* Opens a document with OnNewDocument and passes parameters to it*/
	CHART_API virtual BOOL OnOpenDocument(SEC_UINT nOpCode,SEC_UINT nSubCode,SEC_DWORD dwData);
	//@cmember
	/* Opens a document with OnNewDocument and passes parameters to it*/
	CHART_API virtual BOOL OnOpenDocument(LPCTSTR lpszPathName); 
	//@cmember
	/* Sets a document name filtering out document command codes passed as text*/
	CHART_API virtual void SetPathName(LPCTSTR lpszPathName,BOOL bAddToMRU=TRUE);
	//@cmember
	/* Called when a child document is deleted*/
	CHART_API virtual void DestroyingDocument(SECComDoc *doc);
	//@cmember
	/* Removes the link to a document*/
	CHART_API virtual void Unlink(SECComDoc *ToUnlink);
	//@cmember
	/* Notifies a parent document that the child is "alive"*/
	CHART_API virtual void NotifyLink(SECComDoc *newlink);
	//@cmember
	/* Initializes a pointer to the parent document*/
	CHART_API virtual void SetParentPointer(SECComDoc* pParent);
	//@cmember
	/* Sequentially updates all child documents in the list*/
	CHART_API virtual BOOL UpdateLinkedDocuments(SEC_UINT nSubCode, SEC_DWORD dwData=NULL);

// End of SEC++ special functions
//////////////////////////////////////////////////////////////

// Implementation
public:
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SECComDoc();


#ifdef _DEBUG
	//@cmember
	/* DEBUG*/
	CHART_API virtual void AssertValid() const;
	//@cmember
	/* DEBUG*/
	CHART_API virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(SECComDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

#endif //__SECCOMDOC__
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

