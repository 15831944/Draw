// CMSectPageItemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CMSectPageItemDlg.h"
#include "afxdialogex.h"
#include "../DB/SectDB.h"
#include "../BaseLib/DlgUtil.h"

#include "../DB/DBDoc.h"
#include "../DB/AttrCtrl.h"
#include "../DB/DataCtrl.h"
#include "../DB/SectUtil.h"
#include "../DB/DB_ST_DT_SECT.h"
#include "CMStiffDlg.h"
// CCMSectPageItemDlg 对话框

IMPLEMENT_DYNAMIC(CCMSectPageItemDlg, CDialog)

CCMSectPageItemDlg::CCMSectPageItemDlg(CDBDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialog(CCMSectPageItemDlg::IDD, pParent)
{
	m_pDoc = pDoc;
	m_pImageList = NULL;
	m_Data.initialize();
	m_aCtrlDB.Add(IDC_CMD_SP_ID_USER_RADIO);
	m_aCtrlDB.Add(IDC_CMD_SP_ID_DB_RADIO);

	m_aCtrlDBUser.Add(IDC_EDIT1);
	m_aCtrlDBUser.Add(IDC_EDIT2);
	m_aCtrlDBUser.Add(IDC_EDIT3);
	m_aCtrlDBUser.Add(IDC_EDIT4);
	m_aCtrlDBUser.Add(IDC_EDIT5);
	m_aCtrlDBUser.Add(IDC_EDIT6);
	m_aCtrlDBUser.Add(IDC_EDIT7);
	m_aCtrlDBUser.Add(IDC_EDIT8);
	m_aCtrlDBUser2.Add(IDC_CMD_SP_ID_CODE);
	m_aCtrlDBUser2.Add(IDC_CMD_SP_ID_CBO_NAME);
}

CCMSectPageItemDlg::~CCMSectPageItemDlg()
{
	if(m_pImageList)
	{
		delete m_pImageList;
		m_pImageList = NULL;
	}
}

void CCMSectPageItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMD_SP_ID_TYPE, m_cboType);
	DDX_Control(pDX, IDC_CMD_SP_ID_ID, m_wndID);
	DDX_Control(pDX, IDC_CMD_SP_ID_BUILTUP, m_wndBuiltUp);
	DDX_Control(pDX, IDC_CMD_SP_ID_CODE, m_wndDB);
	DDX_Control(pDX, IDC_CMD_SP_ID_CBO_NAME, m_wndFirstName);
	//DDX_Control(pDX, IDC_CMD_SP_ID_BMP, m_Bitmap);
	UINT aFirstID[][8] ={
		{IDC_EDIT1,IDC_EDIT2,IDC_EDIT3,IDC_EDIT4,IDC_EDIT5,IDC_EDIT6,IDC_EDIT7,IDC_EDIT8},
		{IDC_SIZE_TITLE1,IDC_SIZE_TITLE2,IDC_SIZE_TITLE3,IDC_SIZE_TITLE4,IDC_SIZE_TITLE5,IDC_SIZE_TITLE6,IDC_SIZE_TITLE7,IDC_SIZE_TITLE8},
	};
	for(int i = 0;i<8;i++)
	{
		DDX_Control(pDX, aFirstID[0][i],m_wndFirstSize[i]);
		DDX_Control(pDX, aFirstID[1][i],m_wndFirstTitle[i]);
	}
	
}

BOOL CCMSectPageItemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitControls();
	m_wndSectView.SetDataSource(&m_Data);
	m_wndDB.GetWindowText(m_Data.SectI.DBName);
	m_Key = m_pDoc->m_pAttrCtrl->GetStartNumSect();
	m_Data.nStype = D_SECT_TYPE_REGULAR;
	CString str;
	str.Format(_T("%d"),m_Key);
	m_wndID.SetWindowText(str);
	ShowDataToDlg();
	
	return TRUE;
}

BEGIN_MESSAGE_MAP(CCMSectPageItemDlg, CDialog)
	ON_BN_CLICKED(ID_APPLY, &CCMSectPageItemDlg::OnApply)
	ON_BN_CLICKED(IDC_CMD_SP_ID_USER_RADIO, &CCMSectPageItemDlg::OnRadio)
	ON_BN_CLICKED(IDC_CMD_SP_ID_DB_RADIO, &CCMSectPageItemDlg::OnRadio)
	ON_CBN_SELCHANGE(IDC_CMD_SP_ID_TYPE, &CCMSectPageItemDlg::OnChangeShape)
	ON_CBN_SELCHANGE(IDC_CMD_SP_ID_CODE, &CCMSectPageItemDlg::OnChangeDB)
	ON_CBN_SELCHANGE(IDC_CMD_SP_ID_CBO_NAME, &CCMSectPageItemDlg::OnChangeFirstName)
	ON_BN_CLICKED(IDC_CMD_SP_ID_BTN_CALC, &CCMSectPageItemDlg::OnBtnCalculate)
END_MESSAGE_MAP()
void CCMSectPageItemDlg::InitControls()
{
	SetSectionShapeCombo();
	int nShapeIndex = D_SECT_SHAPE_REG_H;
	m_cboType.SetCurSel(nShapeIndex);
	CDlgUtil::CtrlEnableDisable(this,m_aCtrlDBUser,0);
	m_wndBuiltUp.EnableWindow(FALSE);

	SetDBNameList();
	m_wndDB.SetCurSel(0);
	m_Data.SectI.Shape = CSectUtil::GetShapeNameFromIndexReg(nShapeIndex);
	CWnd* pWnd = GetDlgItem(IDC_CMD_SP_ID_PREVIEW);
	ASSERT(pWnd);
	m_wndSectView.Init(pWnd);
}
void CCMSectPageItemDlg::SetSectionShapeCombo()
{
	int nSectSieze = 10;
	UINT* aBitmapID = new UINT[nSectSieze];
	CString* aItemName = new CString[nSectSieze];
	int nIdx = 0;
	int nIndex[10];
	aBitmapID[nIdx] = IDB_CMD_SEC_REG_01;		aItemName[nIdx] = _LS(IDS_WG_CMD__ADDD__Angle);		nIndex[nIdx++] = D_SECT_SHAPE_REG_L;
	aBitmapID[nIdx] = IDB_CMD_SEC_REG_02;		aItemName[nIdx] = _LS(IDS_WG_CMD__ADDD__Channel);		nIndex[nIdx++] = D_SECT_SHAPE_REG_C;
	aBitmapID[nIdx] = IDB_CMD_SEC_REG_03;		aItemName[nIdx] = _LS(IDS_WG_CMD__ADDD__H_Section);		nIndex[nIdx++] = D_SECT_SHAPE_REG_H;
	aBitmapID[nIdx] = IDB_CMD_SEC_REG_04;		aItemName[nIdx] = _LS(IDS_WG_CMD__ADDD__T_Section);		nIndex[nIdx++] = D_SECT_SHAPE_REG_T;
	aBitmapID[nIdx] = IDB_CMD_SEC_REG_05;		aItemName[nIdx] = _LS(IDS_WG_CMD__ADDD__Box);		nIndex[nIdx++] = D_SECT_SHAPE_REG_B;
	aBitmapID[nIdx] = IDB_CMD_SEC_REG_06;		aItemName[nIdx] = _LS(IDS_WG_CMD__ADDD__Pipe);		nIndex[nIdx++] = D_SECT_SHAPE_REG_P;
	aBitmapID[nIdx] = IDB_CMD_SEC_REG_07;		aItemName[nIdx] = _LS(IDS_WG_CMD__ADDD__Double_Angle);		nIndex[nIdx++] = D_SECT_SHAPE_REG_2L;
	aBitmapID[nIdx] = IDB_CMD_SEC_REG_08;		aItemName[nIdx] = _LS(IDS_WG_CMD__ADDD__Cross_Angle);		nIndex[nIdx++] = D_SECT_SHAPE_REG_2C;
	aBitmapID[nIdx] = IDB_CMD_SEC_REG_09;		aItemName[nIdx] = _LS(IDS_WG_CMD__ADDD__Solid_Rectangle);		nIndex[nIdx++] = D_SECT_SHAPE_REG_SB;
	aBitmapID[nIdx] = IDB_CMD_SEC_REG_10;		aItemName[nIdx] = _LS(IDS_WG_CMD__ADDD__Solid_Round);		nIndex[nIdx++] = D_SECT_SHAPE_REG_SR;
	if(m_pImageList)
	{
		delete m_pImageList;
		m_pImageList = NULL;
	}
	m_pImageList = new CImageList;
	m_pImageList->Create(25,25,ILC_COLOR,nSectSieze,1);
	for(int i = 0;i<nSectSieze;i++)
	{
		CBitmap bitmap;
		bitmap.LoadBitmap(aBitmapID[i]);
		m_pImageList->Add(&bitmap,COLORREF(RGB(0,0,0)));
	}
	m_cboType.SetImageList(m_pImageList);
	
	for(int i = 0;i<nSectSieze;i++)
	{
		COMBOBOXEXITEM cbi;
		cbi.mask = CBEIF_IMAGE | CBEIF_INDENT | CBEIF_TEXT
			| CBEIF_OVERLAY | CBEIF_SELECTEDIMAGE;
		cbi.iItem = i;
		CString str = aItemName[i];
		cbi.pszText = (LPTSTR)(LPCTSTR)str;/*.GetBuffer(0);*/
		cbi.cchTextMax = str.GetLength();
		cbi.iImage = i;
		cbi.iSelectedImage = i;
		cbi.iOverlay = i;
		cbi.iIndent = 0;
		m_cboType.SetItemData(m_cboType.InsertItem(&cbi),nIndex[i]);
		//CDlgUtil::CobxAddItem(m_cboType,str,i);
		//m_cboType.InsertItem(&cbi);
	}
}
void CCMSectPageItemDlg::SetDBNameList()
{
	CArray<CString,CString&> DBNameList;
	m_pDoc->m_pSectDB->GetNameList(DBNameList);
	for(int i=0;i<DBNameList.GetSize();i++)
	{
		CString str = DBNameList[i];
		m_wndDB.AddString(str);
	}
}
void CCMSectPageItemDlg::ShowDataToDlg()
{
	CDlgUtil::CtrlRadioSetCheck(this,m_aCtrlDB,1);
	SetFirstSectData();
	SetFirstNameCombo();
	ChangeBitmap();
}
void CCMSectPageItemDlg::SetFirstSectData()
{
	int nSize = 8;
	T_SECT_SECTBASE_D* pSect = &m_Data.SectI;
	for(int i=0;i<nSize;i++)
	{
		CString csValue;
		csValue.Format(_T("%g"),pSect->dSize[i]);
		m_wndFirstSize[i].SetWindowText(csValue);
	}
	CStringArray aSizeTitle;
	int nShapeIndex = CSectUtil::GetShapeIndexFromNameReg(pSect->Shape);
	CSectUtil::GetSizeTitleFromShapeIndexReg(nShapeIndex,aSizeTitle);
	int i = 0;
	for(;i<aSizeTitle.GetSize();i++)
	{
		m_wndFirstTitle[i].ShowWindow(TRUE);
		m_wndFirstSize[i].ShowWindow(TRUE);
	}
	for(;i<8;i++)
	{
		m_wndFirstTitle[i].ShowWindow(FALSE);
		m_wndFirstSize[i].ShowWindow(FALSE);
	}
	m_wndSectView.Invalidate();
}
void CCMSectPageItemDlg::SetFirstNameCombo()
{
	m_wndFirstName.ResetContent();
	CArray<CString,CString&> aSectNameList;
	m_pDoc->m_pSectDB->GetSectNameList(m_Data.SectI.DBName,m_Data.SectI.Shape,aSectNameList);
	int nCount = static_cast<int>(aSectNameList.GetCount());
	for(int i = 0;i<nCount;i++)
		m_wndFirstName.AddString(aSectNameList.GetAt(i));
}
void CCMSectPageItemDlg::ChangeBitmap()
{
	int nShapeIndex = CSectUtil::GetShapeIndexFromNameReg(m_Data.SectI.Shape);
	if(nShapeIndex < 0)
	{
		AfxMessageBox(_LS(IDS_WG_CMD__ADDD__Error___Invalid_regular_section_s));
		return;
	}
	UINT aBitmapID[] = {
		IDB_CMD_SP_ISGL_BMP01,IDB_CMD_SP_ISGL_BMP02,IDB_CMD_SP_ISGL_BMP03,IDB_CMD_SP_ISGL_BMP04,
		IDB_CMD_SP_ISGL_BMP05,IDB_CMD_SP_ISGL_BMP06,IDB_CMD_SP_ISGL_BMP07,IDB_CMD_SP_ISGL_BMP08,
		IDB_CMD_SP_ISGL_BMP09,IDB_CMD_SP_ISGL_BMP10,
	};

	CStatic* SectImage = (CStatic*)GetDlgItem(IDC_CMD_SP_ID_BMP);
	//if(m_Bitmap){delete m_Bitmap;m_Bitmap = 0;}
	//m_Bitmap = new CBitmap;
	//CBitmap m_Bitmap1;
	m_Bitmap.DeleteObject();
	m_Bitmap.LoadBitmap(aBitmapID[nShapeIndex]);
	SectImage->SetBitmap((HBITMAP)m_Bitmap);
	//this->OnPaint();
}
// CCMSectPageItemDlg 消息处理程序
void CCMSectPageItemDlg::OnOk()
{
	CDialog::OnOK();
}
void CCMSectPageItemDlg::OnApply()
{
	m_pDoc->m_pDataCtrl->AddSect(m_Key,m_Data);
}
void CCMSectPageItemDlg::OnRadio()
{
	int nUserOrDB;
	CDlgUtil::CtrlRadioGetCheck(this,m_aCtrlDB,nUserOrDB);
	ASSERT(nUserOrDB != -1);
	m_wndBuiltUp.SetCheck(nUserOrDB);
	m_wndDB.EnableWindow(nUserOrDB);
	CDlgUtil::CtrlEnableDisable(this,m_aCtrlDBUser2,nUserOrDB);
	CDlgUtil::CtrlEnableDisable(this,m_aCtrlDBUser,!nUserOrDB);
}
void CCMSectPageItemDlg::OnChangeShape()
{
	int nShapeIndex = m_cboType.GetCurSel();
	nShapeIndex = static_cast<int>(m_cboType.GetItemData(nShapeIndex));
	if(nShapeIndex < 0)return;
	int nCurShapeIndex = CSectUtil::GetShapeIndexFromNameReg(m_Data.SectI.Shape);
	if(nShapeIndex == nCurShapeIndex)return;
	T_SECT_SECTBASE_D* pSect = &m_Data.SectI;
	CString csDBName = pSect->DBName;
	pSect->initialize();
	pSect->Shape = CSectUtil::GetShapeNameFromIndexReg(nShapeIndex);
	pSect->DBName = csDBName;
	//m_Data.SectI.SName.Empty();
	ShowDataToDlg();
}
void CCMSectPageItemDlg::OnChangeDB()
{
	m_wndDB.GetWindowText(m_Data.SectI.DBName);
	SetFirstNameCombo();
	OnChangeFirstName();
	//OnChangeShape();
}
void CCMSectPageItemDlg::OnChangeFirstName()
{
	CString csName;
	m_wndFirstName.GetWindowText(csName);
	T_SECT_SECTBASE_D* pSect = &m_Data.SectI;
	if(csName == pSect->SName)return;
	pSect->SName = csName;
	T_SECT_SECTBASE_D SectData;
	SectData.initialize();
	if(csName != _T(""))
		m_pDoc->m_pSectDB->GetSectData_Org(pSect->DBName,pSect->SName,SectData);
	for(int i = 0;i<D_SECT_SIZE_NUM_MAX;i++)
		pSect->dSize[i] = SectData.dSize[i];
	pSect->BuiltUpFlag = SectData.BuiltUpFlag;
	SetFirstSectData();
}
void CCMSectPageItemDlg::OnBtnCalculate()
{
	CCMStiffDlg dlg(m_pDoc,&m_Data,this);
	dlg.DoModal();
}
