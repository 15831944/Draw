#pragma once
class CConvertAccelIDToString
{
private:
  CConvertAccelIDToString(void);

public:
  virtual ~CConvertAccelIDToString(void);
  static CConvertAccelIDToString* GetInstance()
  {
    if (m_pConv == NULL)
    { 
      m_pConv = new CConvertAccelIDToString();
    }
    return m_pConv;
  }
  BOOL GetStringByID(UINT nID, CString& strText);

private:
  CMap<UINT,UINT,CString,CString> m_mIDToStr;

  CString GetVirtStr(WORD fVirt);
  CString GetKeyStr(WORD fKey);
  void Initialize();

private:
  static CConvertAccelIDToString* m_pConv;
};

