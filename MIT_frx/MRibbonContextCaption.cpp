#include "StdAfx.h"
#include "MRibbonContextCaption.h"

using namespace mit::frx;

IMPLEMENT_DYNCREATE (MRibbonContextCaption, CBCGPRibbonContextCaption)

MRibbonContextCaption::MRibbonContextCaption()
: CBCGPRibbonContextCaption()
{

}

MRibbonContextCaption::MRibbonContextCaption(LPCTSTR lpszName, UINT uiID, BCGPRibbonCategoryColor clrContext)
: CBCGPRibbonContextCaption(lpszName, uiID, clrContext)
{

}

void MRibbonContextCaption::OnDraw (CDC* pDC)
{
	CBCGPRibbonContextCaption::OnDraw( pDC );
}