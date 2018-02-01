#pragma once

#include <memory>
using namespace std;

extern "C" AFX_EXTENSION_MODULE MIT_frxDLL;
class CExtDllInstanceSwitcher
{
public:
    CExtDllInstanceSwitcher()
    {
        m_hInst = AfxGetResourceHandle();
        AfxSetResourceHandle(MIT_frxDLL.hResource);
    }

    ~CExtDllInstanceSwitcher()
    {
        AfxSetResourceHandle(m_hInst);
    }

private:
    HINSTANCE m_hInst;
};

#define SWITCH_RESOURCE  CExtDllInstanceSwitcher __SwitchInstance

