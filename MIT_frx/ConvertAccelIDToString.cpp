#include "stdafx.h"
#include "ConvertAccelIDToString.h"
#include "..\wg_main\wg_mainRes2.h"

//*** Virtual-key codes for the accelerators that are not in any windows headers.
#define VK_BACK_SPACE 0x0008

#define VK_ZERO 0x30
#define VK_1	0x31
#define VK_2	0x32
#define VK_3	0x33
#define VK_4	0x34
#define VK_5	0x35
#define VK_6	0x36
#define VK_7	0x37
#define VK_8	0x38
#define VK_9	0x39

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

CConvertAccelIDToString* CConvertAccelIDToString::m_pConv = NULL;

CConvertAccelIDToString::CConvertAccelIDToString(void)
{
  Initialize();
}

CConvertAccelIDToString::~CConvertAccelIDToString(void)
{

}

void CConvertAccelIDToString::Initialize()
{
  // wg_main에 있는 단축키 정보를 읽어옴
  HINSTANCE hInst = AfxFindResourceHandle (MAKEINTRESOURCE(IDR_WGEN60TYPE), RT_ACCELERATOR);
  HACCEL hAccel = LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_WGEN60TYPE));

  int nAccelerators = CopyAcceleratorTable(hAccel, NULL, 0); 
  LPACCEL lpaccelNew = (LPACCEL) LocalAlloc(LPTR, nAccelerators * sizeof(ACCEL)); 
  if (lpaccelNew) CopyAcceleratorTable(hAccel, lpaccelNew, nAccelerators); 

  // 맵을 구성한다.
  m_mIDToStr.RemoveAll();
  const int nMapSize = 0xffff;
  m_mIDToStr.InitHashTable(nMapSize);

  for (int i=0; i<nAccelerators; i++) 
  {
    tagACCEL tag = lpaccelNew[i];

    CString str = _T("");
    str += GetVirtStr(tag.fVirt);
    str += GetKeyStr(tag.key);

    if(str.GetLength()>0)
    {
      m_mIDToStr.SetAt(tag.cmd, str);
    }
  }
}

CString CConvertAccelIDToString::GetVirtStr(WORD fVirt)
{
  CString str=_T("");

  if (fVirt & FCONTROL)    str += "Ctrl+";
  if (fVirt & FALT)        str += "Alt+";
  if (fVirt & FSHIFT)      str += "Shift+";
  if (!(fVirt & FVIRTKEY))
  {
    //*** There must be a virtual-key code or the accelerator is invalid.
    str.Empty();
  }
    
  return str;
}

CString CConvertAccelIDToString::GetKeyStr(WORD fKey)
{
  CString str;
  switch (fKey)
  {
  case VK_BACK_SPACE:
    str+="Backspace";
    break;
  case VK_PAUSE:
    str+="Pause";
    break;
  case VK_PRIOR:
    str+="Page Up";
    break;
  case VK_NEXT:
    str+="Page Down";
    break;
  case VK_END:
    str+="End";
    break;
  case VK_HOME:
    str+="Home";
    break;
  case VK_LEFT:
    str+="Left";
    break;
  case VK_UP:
    str+="Up";
    break;
  case VK_RIGHT:
    str+="Right";
    break;
  case VK_DOWN:
    str+="Down";
    break;
  case VK_EXECUTE:
    str+="Exe";
    break;
  case VK_INSERT:
    str+="Ins";
    break;
  case VK_DELETE:
    str+="Del";
    break;
  case VK_ZERO:
    str+="Zero";
    break;
  case VK_1:
    str+="1";
    break;
  case VK_2:
    str+="2";
    break;
  case VK_3:
    str+="3";
    break;
  case VK_4:
    str+="4";
    break;
  case VK_5:
    str+="5";
    break;
  case VK_6:
    str+="6";
    break;
  case VK_7:
    str+="7";
    break;
  case VK_8:
    str+="8";
    break;
  case VK_9:
    str+="9";
    break;
  case VK_A:
    str+="A";
    break;
  case VK_B:
    str+="B";
    break;
  case VK_C:
    str+="C";
    break;
  case VK_D:
    str+="D";
    break;
  case VK_E:
    str+="E";
    break;
  case VK_F:
    str+="F";
    break;
  case VK_G:
    str+="G";
    break;
  case VK_H:
    str+="H";
    break;
  case VK_I:
    str+="I";
    break;
  case VK_J:
    str+="J";
    break;
  case VK_K:
    str+="K";
    break;
  case VK_L:
    str+="L";
    break;
  case VK_M:
    str+="M";
    break;
  case VK_N:
    str+="N";
    break;
  case VK_O:
    str+="O";
    break;
  case VK_P:
    str+="P";
    break;
  case VK_Q:
    str+="Q";
    break;
  case VK_R:
    str+="R";
    break;
  case VK_S:
    str+="S";
    break;
  case VK_T:
    str+="T";
    break;
  case VK_U:
    str+="U";
    break;
  case VK_V:
    str+="V";
    break;
  case VK_W:
    str+="W";
    break;
  case VK_X:
    str+="X";
    break;
  case VK_Y:
    str+="Y";
    break;
  case VK_Z:
    str+="Z";
    break;
  case VK_NUMPAD0:
    str+="Num 0";
    break;
  case VK_NUMPAD1:
    str+="Num 1";
    break;
  case VK_NUMPAD2:
    str+="Num 2";
    break;
  case VK_NUMPAD3:
    str+="Num 3";
    break;
  case VK_NUMPAD4:
    str+="Num 4";
    break;
  case VK_NUMPAD5:
    str+="Num 5";
    break;
  case VK_NUMPAD6:
    str+="Num 6";
    break;
  case VK_NUMPAD7:
    str+="Num 7";
    break;
  case VK_NUMPAD8:
    str+="Num 8";
    break;
  case VK_NUMPAD9:
    str+="Num 9";
    break;
  case VK_MULTIPLY:
    str+="Num *";
    break;
  case VK_ADD:
    str+="Num +";
    break;
  case VK_SUBTRACT:
    str+="Num -";
    break;
  case VK_DECIMAL:
    str+="Num Del";
    break;
  case VK_DIVIDE:
    str+="Num /";
    break;
  case VK_F1:
    str+="F1";
    break;
  case VK_F2:
    str+="F2";
    break;
  case VK_F3:
    str+="F3";
    break;
  case VK_F4:
    str+="F4";
    break;
  case VK_F5:
    str+="F5";
    break;
  case VK_F6:
    str+="F6";
    break;
  case VK_F7:
    str+="F7";
    break;
  case VK_F8:
    str+="F8";
    break;
  case VK_F9:
    str+="F9";
    break;
  case VK_F10:
    str+="F10";
    break;
  case VK_F11:
    str+="F11";
    break;
  case VK_F12:
    str+="F12";
    break;
  case VK_F13:
    str+="F13";
    break;
  case VK_F14:
    str+="F14";
    break;
  case VK_F15:
    str+="F15";
    break;
  case VK_F16:
    str+="F16";
    break;
  case VK_OEM_3:
    str+="`";
    break;
  default:
    // 없는 키가 있으면 추가해주세요
    ASSERT(0);
    str.Empty();
    break;
  }
  return str;
}

BOOL CConvertAccelIDToString::GetStringByID(UINT nID, CString& strText)
{
  if(m_mIDToStr.Lookup(nID,strText)) return TRUE;
  return FALSE;
}