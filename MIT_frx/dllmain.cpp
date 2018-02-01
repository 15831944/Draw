// dllmain.cpp : DLL�� �ʱ�ȭ ��ƾ�� �����մϴ�.
//

#include "stdafx.h"
#include "dllmain.h"
#include <afxwin.h>
#include <afxdllx.h>
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern "C" AFX_EXTENSION_MODULE MIT_frxDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// lpReserved�� ����ϴ� ��� ������ �����Ͻʽÿ�.
	UNREFERENCED_PARAMETER(lpReserved);

	_tsetlocale(LC_ALL, _T("korean"));


	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("MIT_frx.DLL�� �ʱ�ȭ�ϰ� �ֽ��ϴ�.\n");
		
		// Ȯ�� DLL�� �� ���� �ʱ�ȭ�մϴ�.
		if (!AfxInitExtensionModule(MIT_frxDLL, hInstance))
			return 0;

		// �� DLL�� ���ҽ� ü�ο� �����մϴ�.
		// ����: �� Ȯ�� DLL�� MFC ���� ���α׷���
		//  �ƴ� ActiveX ��Ʈ�Ѱ� ���� MFC �⺻ DLL��
		//  ���� ��������� ��ũ�Ǿ� �ִ� ��쿡��
		//  DllMain���� �� ���� �����ϰ�, ������ ���� �� Ȯ�� DLL����
		//  ������ ������ �Լ��� �߰��մϴ�.
		//  �׷� ���� �� Ȯ�� DLL�� ����ϴ� �⺻ DLL��
		//  �ش� �Լ��� ��������� ȣ���Ͽ� �� Ȯ�� DLL�� �߰��ؾ� �մϴ�.
		//  �׷��� ������ CDynLinkLibrary ��ü��
		//  �⺻ DLL�� ���ҽ� ü�ο� �߰����� �����Ƿ�
		//  �ɰ��� ������ �߻��մϴ�.

		new CDynLinkLibrary(MIT_frxDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("MIT_frx.DLL�� �����ϰ� �ֽ��ϴ�.\n");

		// �Ҹ��ڰ� ȣ��Ǳ� ���� ���̺귯���� �����մϴ�.
		AfxTermExtensionModule(MIT_frxDLL);
	}
	return 1;   // Ȯ��
}

// ������� �ʱ�ȭ�� �ʿ��Ҷ� Dll  Client ��
// Application class�� InitInstance Member �Լ����� ȣ���Ѵ�. 
// ���� DllMain�� new CDynLinkLibrary(MIT_frxDLL);
// ������ Comment �� �ٲپ�� �Ѵ�. 
extern "C" void WINAPI Init_MIT_frxdll()
{
	//new CDynLinkLibrary(MIT_frxDLL);
}