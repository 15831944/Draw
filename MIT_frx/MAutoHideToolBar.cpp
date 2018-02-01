#include "StdAfx.h"
#include "MAutoHideToolBar.h"

#include "MVisualManager.h"
#include "MAutoHideButton.h"

#include "BCGPAutoHideDockBar.h"

using namespace mit;
using namespace mit::frx;

class MAutoHideDockBar : public CBCGPAutoHideDockBar
{
	friend class MAutoHideToolBar;
};

IMPLEMENT_DYNCREATE(MAutoHideToolBar, CBCGPAutoHideToolBar)

//-------------------------------------------------------------------------------//
CSize MAutoHideToolBar::StretchControlBar (int /*nLength*/, BOOL /*bVert*/)
{
	CRect rect;
	GetWindowRect (rect);
	CSize size (0, 0);

	for (POSITION pos = m_lstAutoHideButtons.GetHeadPosition (); pos != NULL;)
	{
		MAutoHideButton* pBtn = (MAutoHideButton*) m_lstAutoHideButtons.GetNext (pos);
		ASSERT_VALID (pBtn);

		size = pBtn->GetSize (m_bResetSizes);
	}

	SetWindowPos (NULL, 0, 0, size.cx, size.cy, SWP_NOMOVE | SWP_NOZORDER); 

	m_bResetSizes = FALSE;
	return size;
}

//***********************************************************************************
void MAutoHideToolBar::PrepareToDock (CBCGPDockBar* pDockBar, BCGP_DOCK_METHOD dockMethod)
{
	CBCGPAutoHideToolBar::PrepareToDock(pDockBar, dockMethod);
}