//// BaseLib.cpp : ���� DLL �ĳ�ʼ�����̡�
////
//
#include "stdafx.h"

#include "BaseLib.h"

static AFX_EXTENSION_MODULE baselibdll = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("WG_DGN.DLL Initializing!\n");

		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(baselibdll, hInstance))
			return 0;

		

		new CDynLinkLibrary(baselibdll);
		/*XMultiLang* pLangTranslate = new XMultiLang;
		pLangTranslate->LoadResourceHeaderByDLL(IDR_WGDGN_RESHEADER,_T("Binary"), hInstance);
		INIResourceManager::AppendMap(_T("wg_dgn"), pLangTranslate);*/
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("WG_DGN.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(baselibdll);
	}
	return 1;   // ok
}

//
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif
//
////
////TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
////		��Ӵ� DLL �������κε���
////		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
////		�ú�������ǰ�档
////
////		����:
////
////		extern "C" BOOL PASCAL EXPORT ExportedFunction()
////		{
////			AFX_MANAGE_STATE(AfxGetStaticModuleState());
////			// �˴�Ϊ��ͨ������
////		}
////
////		�˺������κ� MFC ����
////		������ÿ��������ʮ����Ҫ������ζ��
////		��������Ϊ�����еĵ�һ�����
////		���֣������������ж������������
////		������Ϊ���ǵĹ��캯���������� MFC
////		DLL ���á�
////
////		�й�������ϸ��Ϣ��
////		����� MFC ����˵�� 33 �� 58��
////
//
//// CBaseLibApp
//
//BEGIN_MESSAGE_MAP(CBaseLibApp, CWinApp)
//END_MESSAGE_MAP()
//
//
//// CBaseLibApp ����
//
//CBaseLibApp::CBaseLibApp()
//{
//	// TODO: �ڴ˴���ӹ�����룬
//	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
//}
//
//
//// Ψһ��һ�� CBaseLibApp ����
//
//CBaseLibApp theApp;
//
//
//// CBaseLibApp ��ʼ��
//
//BOOL CBaseLibApp::InitInstance()
//{
//	CWinApp::InitInstance();
//
//	return TRUE;
//}
