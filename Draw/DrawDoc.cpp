
// DrawDoc.cpp: CDrawDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Draw.h"
#endif

#include "DrawDoc.h"
#include "../DB/UndoRedoDlg.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "test.h"
#include "../DB/UndoRedo.h"
// CDrawDoc
#define CDocument CDBDoc
#undef CDocument
IMPLEMENT_DYNCREATE(CDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrawDoc, CDocument)
	ON_COMMAND(ID_TEST_32773, &CDrawDoc::OnTest)
	ON_COMMAND(ID_TEST1_ONTEST, &CDrawDoc::OnTest1Ontest)
	ON_COMMAND(ID_COLOR_BLACK, &CDrawDoc::OnColorBlack)
	ON_COMMAND(ID_COLOR_BLUE, &CDrawDoc::OnColorBlue)
	ON_COMMAND(ID_COLOR_GREEN, &CDrawDoc::OnColorGreen)
	ON_COMMAND(ID_COLOR_RED, &CDrawDoc::OnColorRed)
	ON_COMMAND(ID_ELEMENT_LINE, &CDrawDoc::OnElementLine)
	ON_COMMAND(ID_ELEMENT_DEFAULT, &CDrawDoc::OnElementDefault)
	ON_COMMAND(ID_ELEMENT_RECTANGLE, &CDrawDoc::OnElementRectangle)
	ON_COMMAND(ID_UNDO, &CDrawDoc::OnUndo)
	ON_COMMAND(ID_UNDO_LIST, &CDrawDoc::OnEditUndo)
	ON_COMMAND(ID_REDO, &CDrawDoc::OnRedo)
	ON_COMMAND(ID_REDO_LIST, &CDrawDoc::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CDrawDoc::OnUpdateColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CDrawDoc::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CDrawDoc::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CDrawDoc::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_DEFAULT, &CDrawDoc::OnUpdateElementDefault)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_LINE, &CDrawDoc::OnUpdateElementLine)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_RECTANGLE, &CDrawDoc::OnUpdateElementRectangle)
	ON_COMMAND(ID_STRUCT_PROP_MATERIAL, &CDrawDoc::OnStructPropMaterial)
	ON_COMMAND(ID_STRUCT_PROP_SECTION, &CDrawDoc::OnStructPropSection)
END_MESSAGE_MAP()


// CDrawDoc 构造/析构

CDrawDoc::CDrawDoc()
	:m_Element(ElementType::DEFAULT), m_Color(ElementColor::BLACK), m_PenStyle(PS_SOLID)
{
}

CDrawDoc::~CDrawDoc()
{
}

BOOL CDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}

#pragma region UndoRedo

void CDrawDoc::OnRedo()
{
	if(m_redo->GetCountidx() != 0)
		DoRedo();
}
void CDrawDoc::OnEditRedo()
{
	if(m_bIsUndoRedoVisible)	
		m_pUndoRedoDlg->DestroyWindow();
	else
	{
		m_pUndoRedoDlg = new CUndoRedoDlg(NULL);
		POINT pos = {0,0};
		GetCursorPos(&pos);
		m_pUndoRedoDlg->SetDlgMode(this,FALSE,pos.x,pos.y+20);
		m_pUndoRedoDlg->Create(CUndoRedoDlg::IDD,NULL);
		m_pUndoRedoDlg->ShowWindow(SW_SHOW);
		m_bIsUndoRedoVisible = TRUE;
	}
}
void CDrawDoc::OnUndo()
{
	if(m_undo->GetCountidx() != 0)
		DoUndo();
}
void CDrawDoc::OnEditUndo()
{
	
	if(m_bIsUndoRedoVisible)
		m_pUndoRedoDlg->DestroyWindow();
	else
	{
		m_pUndoRedoDlg = new CUndoRedoDlg(NULL);
		POINT pos = {0,0};
		GetCursorPos(&pos);
		m_pUndoRedoDlg->SetDlgMode(this,TRUE,pos.x,pos.y+20);
		m_pUndoRedoDlg->Create(CUndoRedoDlg::IDD,NULL);
		m_pUndoRedoDlg->ShowWindow(SW_SHOW);
		m_bIsUndoRedoVisible = TRUE;
	}
}

#pragma endregion UndoRedo

// CDrawDoc 序列化
void CDrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CDrawDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CDrawDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CDrawDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDrawDoc 诊断

#ifdef _DEBUG
void CDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
void CDrawDoc::AddElement(const CPElement & pElement)
{
	m_Sketch.push_back(pElement);
	UpdateAllViews(nullptr, 0);
}
void CDrawDoc::DeleteElement(const CPElement & pElement)
{
	m_Sketch.remove(pElement);
	UpdateAllViews(nullptr, 0);
}
#endif //_DEBUG

// CDrawDoc 命令

#include "MainFrm.h"
#include "test.h"

void CDrawDoc::OnTest()
{
	CMainFrame* pFrm = dynamic_cast<CMainFrame*>(::AfxGetMainWnd());
	ClassPool* pDB = new ClassPool(1);
	IDBMgr::Inst()->Register(pDB);
	ClassBase* pClass = new ClassBase(pDB,1);
	pDB->Register(pClass);
	//pClass->ObserverMgr()->Add(pFrm->GetOutPut());
	for (int i = 0; i < 10; i++)
	{
		CTest CTest(i);
		CTest.m_nData = 100 + i;
		pClass->Add(&CTest);
	}
	pClass->Del(2);
	CTest Test(3, 666);
	//pClass->Mod(&Test);
}

#include "../test/Test.h"

void CDrawDoc::OnTest1Ontest()
{
	//CMSGInfo::Instance();
	MTest TestDlg;
	TestDlg.DoModal();
}

void CDrawDoc::OnColorBlack()
{
	m_Color = ElementColor::BLACK;
}

void CDrawDoc::OnColorBlue()
{
	m_Color = ElementColor::BLUE;
}

void CDrawDoc::OnColorGreen()
{
	m_Color = ElementColor::GREEN;
}

void CDrawDoc::OnColorRed()
{
	m_Color = ElementColor::RED;
}

void CDrawDoc::OnElementLine()
{
	m_Element = ElementType::LINE;
}

void CDrawDoc::OnElementDefault()
{
	m_Element = ElementType::DEFAULT;
}

void CDrawDoc::OnElementRectangle()
{
	m_Element = ElementType::RECTANGLE;
}

void CDrawDoc::SetTitle(LPCTSTR lpszTitle)
{
	lpszTitle = _T("Draw");
	CDocument::SetTitle(lpszTitle);
}

void CDrawDoc::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Color == ElementColor::BLACK);
}

void CDrawDoc::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Color == ElementColor::BLUE);
}

void CDrawDoc::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Color == ElementColor::GREEN);
}

void CDrawDoc::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Color == ElementColor::RED);
}

void CDrawDoc::OnUpdateElementDefault(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::DEFAULT);
}

void CDrawDoc::OnUpdateElementLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::LINE);
}

void CDrawDoc::OnUpdateElementRectangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::RECTANGLE);
}

#include "../cmd/CMPropertiesDlg.h"
#include "../cmd/ExportFunc.h"

void CDrawDoc::OnStructPropMaterial()
{
	CCMPropertiesDlg* pPropDlg = (CCMPropertiesDlg*)CreateOrActivateDlg((CDBDoc*)this, CCMPropertiesDlg::IDD);
	pPropDlg->SetActivePage(0);
}

void CDrawDoc::OnStructPropSection()
{
	CCMPropertiesDlg* pPropDlg = (CCMPropertiesDlg*)CreateOrActivateDlg((CDBDoc*)this, CCMPropertiesDlg::IDD);
	pPropDlg->SetActivePage(1);
}
