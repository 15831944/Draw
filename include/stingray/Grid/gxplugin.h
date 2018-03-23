///////////////////////////////////////////////////////////////////////////////
// gxplugin.h : Interface of the CGXPluginComponent class

#ifndef _GXPLUGIN_H_
#define _GXPLUGIN_H_

// // #include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

class CGXPluginComponent: public CWnd
{
	GRID_DECLARE_DYNAMIC(CGXPluginComponent);

public:
	GRID_API CGXPluginComponent();
	GRID_API virtual BOOL PlugIn(CWnd* pParentWnd);
	GRID_API virtual ~CGXPluginComponent();

public:
	// Attributes 
	// Reserved for later usage with a PluginManager
	BOOL m_bSkipOtherPlugins;	// set this TRUE from within your message handler
								// if no other plugins should be called	for this message
	BOOL m_bExitMesssage;		// set this TRUE from within your message handler        
								// if no other plugins and also not the default window message 
								// should be called

// Generated message map functions
protected:
	//{{AFX_MSG(CGXPluginComponent)
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()

public:
	// for processing Windows messages
	GRID_API BOOL HandleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

protected:
	// for handling default processing
	GRID_API virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif
};

#define CGXPlugInComponent CGXPluginComponent	// for backward compatibility

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif //_GXPLUGIN_H_
