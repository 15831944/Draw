#include "StdAfx.h"
#include "MRibbonMainButton.h"

#include "MVisualManager.h"
#include "MRibbonPanelMenu.h"
#include "MRibbonMainPanel.h"

using namespace mit;
using namespace mit::frx;

class MRibbonBar : public CBCGPRibbonBar
{
	friend class MRibbonMainButton;
};

IMPLEMENT_DYNCREATE(MRibbonMainButton, CBCGPRibbonMainButton);
MRibbonMainButton::MRibbonMainButton()
{

}

MRibbonMainButton::~MRibbonMainButton()
{

}

void MRibbonMainButton::OnShowPopupMenu ()
{
	CBCGPRibbonMainButton::OnShowPopupMenu();	
}

//********************************************************************************
BOOL MRibbonMainButton::OnKey (BOOL bIsMenuKey)
{
	return CBCGPRibbonButton::OnKey (bIsMenuKey);
}

//********************************************************************************
void MRibbonMainButton::OnLButtonDown (CPoint point)
{
	CBCGPRibbonButton::OnLButtonDown (point);
}