#pragma once
class CDBDoc;
extern __declspec(dllexport) void* CreateOrActivateDlg(CDBDoc* pDoc, UINT nIDTemplate, CWnd* pParent = NULL, void* pExtData = NULL);