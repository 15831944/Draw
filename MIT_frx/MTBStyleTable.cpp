#include "stdafx.h"
#include "MTBStyleTable.h"

using namespace mit;
using namespace mit::frx;

MTBStyleTableDB::MTBStyleTableDB(ITable* pTable, ITableDB* pObjTableDB) : 
	MPostTableDB(pTable, &m_schema),
	m_pObjTableDB(pObjTableDB),
	m_pObjTable(dynamic_cast<MTable*>(pObjTableDB->GetTable()))
{
	MakeSchema(); 
	MakeData();
}

MTBStyleTableDB::~MTBStyleTableDB()
{
}

void MTBStyleTableDB::MakeSchema()
{
	MBeginAddTBColumn(m_schema)
		MAddTBColumn(CID_Name, _LSX(Name), _T(""), MTBStyleTableData, CString, strName, 0)
		MAddTBColumn(CID_Type, _LSX(Type), _T(""), MTBStyleTableData, int, nType, 0)
		MAddTBColumn(CID_Width, _LSX(Width), _T(""), MTBStyleTableData, int, nWidth, 0)
		MAddTBColumn(CID_Align, _LSX(Align), _T(""), MTBStyleTableData, int, nAlign, 0)
		MAddTBColumn(CID_Format, _LSX(Format), _T(""), MTBStyleTableData, int, nFormat, 0)
		MAddTBColumn(CID_Precision, _LSX(Precision), _T(""), MTBStyleTableData, int, nPrecision, 0)
	MEndAddTBColumn()
	m_schema.SetDefaultData( MTBStyleTableData() );

	m_schema.GetColumn(CID_Type).GetDataMap()->AddItem(MTBColumn::TB_KEY, MTBColumn::GetTypeName(MTBColumn::TB_KEY));
	m_schema.GetColumn(CID_Type).GetDataMap()->AddItem(MTBColumn::TB_MKey, MTBColumn::GetTypeName(MTBColumn::TB_MKey));
	m_schema.GetColumn(CID_Type).GetDataMap()->AddItem(MTBColumn::TB_BOOL, MTBColumn::GetTypeName(MTBColumn::TB_BOOL));
	m_schema.GetColumn(CID_Type).GetDataMap()->AddItem(MTBColumn::TB_bool, MTBColumn::GetTypeName(MTBColumn::TB_bool));
	m_schema.GetColumn(CID_Type).GetDataMap()->AddItem(MTBColumn::TB_int, MTBColumn::GetTypeName(MTBColumn::TB_int));
	m_schema.GetColumn(CID_Type).GetDataMap()->AddItem(MTBColumn::TB_UINT, MTBColumn::GetTypeName(MTBColumn::TB_UINT));
	m_schema.GetColumn(CID_Type).GetDataMap()->AddItem(MTBColumn::TB_float, MTBColumn::GetTypeName(MTBColumn::TB_float));
	m_schema.GetColumn(CID_Type).GetDataMap()->AddItem(MTBColumn::TB_double, MTBColumn::GetTypeName(MTBColumn::TB_double));
	m_schema.GetColumn(CID_Type).GetDataMap()->AddItem(MTBColumn::TB_CString, MTBColumn::GetTypeName(MTBColumn::TB_CString));

	m_schema.GetColumn(CID_Align).GetDataMap()->AddItem(HDF_LEFT, CString(_LSX(Left)));
	m_schema.GetColumn(CID_Align).GetDataMap()->AddItem(HDF_CENTER, CString(_LSX(Center)));
	m_schema.GetColumn(CID_Align).GetDataMap()->AddItem(HDF_RIGHT, CString(_LSX(Right)));

	m_schema.GetColumn(CID_Format).GetDataMap()->AddItem(D_FMT_DEFAULT, CString(_LSX(Default)));
	m_schema.GetColumn(CID_Format).GetDataMap()->AddItem(D_FMT_FIXED, CString(_LSX(Fixed)));
	m_schema.GetColumn(CID_Format).GetDataMap()->AddItem(D_FMT_SCIENTIFIC, CString(_LSX(Scientific)));
	m_schema.GetColumn(CID_Format).GetDataMap()->AddItem(D_FMT_GENERAL, CString(_LSX(General)));
}

void MTBStyleTableDB::MakeData()
{
	const MTBSchemaBase* pSchema = GetObjSchema();
	int nDataCount = (int)pSchema->GetColumnCount();
	m_data.resize(nDataCount);
	for (int i = 0; i < nDataCount; i++)
	{
		const MTBColumn& column = pSchema->GetColumn(i);
		MTBStyleTableData& data = m_data[i];
		MGridColumnsInfo* pColumnsEx = (MGridColumnsInfo*)GetObjTable()->PGetColumnsInfo();
		data.strName = column.GetDisplayName();
		data.nType = column.GetDisplayType();
		data.nWidth = pColumnsEx->GetColumnWidth(i);
		data.nAlign = pColumnsEx->GetColumnAlign(i);
		MFormatInfo formatInfo;
		if (column.IsFloatType())
		{
			VERIFY(pColumnsEx->GetColumnFormat(i, formatInfo));
			data.nFormat = formatInfo.GetRawType();
			data.nPrecision = formatInfo.GetRawPrecision();
		}
	}
}

size_t MTBStyleTableDB::GetDataCount() const
{
	return m_data.size();
}

BOOL MTBStyleTableDB::GetData(int nRow, LPCVOID& pData) const
{
	pData = &(m_data[nRow]);
	return TRUE;
}

BOOL MTBStyleTableDB::ModifyData(int nRow, int nCol, LPCVOID pData)
{
	const MTBStyleTableData& data = (const MTBStyleTableData&)*((const MTBStyleTableData*)pData);
	m_data[nRow] = data;
	return TRUE;
}

BOOL MTBStyleTableDB::ModifyData(const std::vector<int>& aRow, const std::vector<LPCVOID>& aData)
{
	ASSERT(aRow.size() == aData.size());
	ASSERT(aRow.size() <= INT_MAX);
	int nRowCount = (int)aRow.size();
	for (int nRow = 0; nRow < nRowCount; nRow++)
	{
		const MTBStyleTableData& data = (const MTBStyleTableData&)*((const MTBStyleTableData*)aData[nRow]);
		m_data[nRow] = data;
	}
	return TRUE;
}

IMPLEMENT_DYNAMIC(MTBStyleTable, MTable)

BEGIN_MESSAGE_MAP(MTBStyleTable, MTable)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

MTBStyleTable::MTBStyleTable(MTable* pObjTable) :
	m_pObjTable(pObjTable),
	m_tableDB(this, pObjTable->GetTableDB())
{
	m_canAppendRow = FALSE;
	m_canDeleteRow = FALSE;
	m_canModifyItem = TRUE;
	m_bRowMarker = FALSE;
}

MTBStyleTable::~MTBStyleTable()
{
}

BOOL MTBStyleTable::InitializeTable()
{
	if (!MTable::InitializeTable()) return FALSE;
	GetColumnsInfo().SetColumnWidth(MTBStyleTableDB::CID_Name, 100);
	return TRUE;
}

void MTBStyleTable::OnPreDrawRow(MGridRow* pRow)
{
	MTable::OnPreDrawRow(pRow);
	const MTBStyleTableData* pData = reinterpret_cast<const MTBStyleTableData*>(pRow->GetDBData());
	if (!pData) return;

	pRow->GetItem(MTBStyleTableDB::CID_Name)->AllowEdit(FALSE);
	pRow->GetItem(MTBStyleTableDB::CID_Type)->AllowEdit(FALSE);
	pRow->GetItem(MTBStyleTableDB::CID_Format)->AllowEdit(pData->nFormat >= 0);
	BOOL bEnablePrecision = pData->nFormat >= 0 && pData->nFormat != D_FMT_DEFAULT;
	pRow->GetItem(MTBStyleTableDB::CID_Precision)->AllowEdit(bEnablePrecision);
	pRow->GetItem(MTBStyleTableDB::CID_Precision)->ShowValue(bEnablePrecision);
}

int MTBStyleTable::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (MTable::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetSingleSel(TRUE);
	EnableHeader(TRUE, BCGP_GRID_HEADER_SELECT);  
	EnableRowHeader();	
	//EnableLineNumbers();
	EnableInvertSelOnCtrl();

	AdjustLayout();

	return 0;
}

void MTBStyleTable::MakeContextMenu(CMenu& menu)
{
	menu.AppendMenu(MF_STRING, ID_TB_COPY, _T("Copy"));
	menu.AppendMenu(MF_STRING, ID_TB_PASTE, _T("Paste"));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, ID_TB_FIND, _T("Find..."));
	menu.AppendMenu(MF_STRING, ID_TB_STYLE, _T("Style..."));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, ID_TB_EXPORT_TO_EXCEL, _T("Export to Excel"));
}