#include "stdafx.h"
#include "MonitorUtil.h"


using namespace mit::frx;

void CMonitorUtil::ClipOrCenterRectToMonitor(LPRECT lpRect, UINT flags)
{
  ClipOrCenterRectToMonitor(lpRect, lpRect, flags);
}

void CMonitorUtil::ClipOrCenterRectToMonitor(LPRECT lpRectParent, LPRECT lpRect, UINT flags)
{
  SIZE size;
  size.cx = lpRect->right - lpRect->left;
  size.cy = lpRect->bottom - lpRect->top;

  RECT rc;
  if (flags & MONITOR_ALL_AREA)
  {
	  if (flags & MONITOR_WORKAREA)
	  {
		  rc.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
		  rc.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
		  rc.right = GetSystemMetrics(SM_CXVIRTUALSCREEN);
		  rc.bottom = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	  }
	  else
	  {
		  rc.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
		  rc.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
		  rc.right = GetSystemMetrics(SM_CXVIRTUALSCREEN);
		  rc.bottom = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	  }
  }
  else
  {
	  // get the nearest monitor to the passed parent rect. 
	  HMONITOR hMonitor = MonitorFromRect(lpRectParent, MONITOR_DEFAULTTONEAREST);

	  // get the work area or entire monitor rect. 
	  MONITORINFO mi;
	  mi.cbSize = sizeof(mi);
	  GetMonitorInfo(hMonitor, &mi);

	  if (flags & MONITOR_WORKAREA)
		  rc = mi.rcWork;
	  else
		  rc = mi.rcMonitor;
  }


  // center or clip the passed rect to the monitor rect 
  if (flags & MONITOR_CENTER)
  {
    lpRect->left   = rc.left + (rc.right  - rc.left - size.cx) / 2;
    lpRect->top    = rc.top  + (rc.bottom - rc.top  - size.cy) / 2;
  }
  else
  {
    lpRect->left   = max(rc.left, min(rc.right-size.cx,  lpRect->left));
    lpRect->top    = max(rc.top,  min(rc.bottom-size.cy, lpRect->top));
  }

  if (flags & MONITOR_HORIZONTAL || flags & MONITOR_VERTICAL)
  {
    BOOL bCollision = (lpRect->left < lpRectParent->right && lpRect->right > lpRectParent->left &&
      lpRect->top < lpRectParent->bottom && lpRect->bottom > lpRectParent->top);

    if (flags & MONITOR_HORIZONTAL)
    {
      if (bCollision) bCollision = !HorizontalCollision(lpRectParent, lpRect, size, rc);
      if (bCollision) bCollision = !VerticalCollision(lpRectParent, lpRect, size, rc);
    }
    else if (flags & MONITOR_VERTICAL)
    {
      if (bCollision) bCollision = !VerticalCollision(lpRectParent, lpRect, size, rc);
      if (bCollision) bCollision = !HorizontalCollision(lpRectParent, lpRect, size, rc);
    }
  }

  lpRect->right  = lpRect->left + size.cx;
  lpRect->bottom = lpRect->top  + size.cy;
}

void CMonitorUtil::ClipOrCenterWindowToMonitor(HWND hwnd, UINT flags)
{
  ClipOrCenterWindowToMonitor(hwnd, hwnd, flags);
}

void CMonitorUtil::ClipOrCenterWindowToMonitor(HWND hwndParent, HWND hwnd, UINT flags)
{
  CRect rcParent;
  GetWindowRect(hwndParent, rcParent);
  CRect rc;
  GetWindowRect(hwnd, rc);
  ClipOrCenterRectToMonitor(rcParent, rc, flags);
  SetWindowPos(hwnd, NULL, rc.left, rc.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

BOOL CMonitorUtil::HorizontalCollision(LPRECT lpRectParent, LPRECT lpRect, const SIZE& size, const RECT& rc)
{
  int x = (lpRect->left + lpRect->right) / 2;
  int xp = (lpRectParent->left + lpRectParent->right) / 2;
  int left = lpRectParent->left - size.cx;
  int right = lpRectParent->right;
  if (x < xp)
  {
    if (left > rc.left) { lpRect->left = left; return TRUE; }
    else if (right < rc.right - size.cx) { lpRect->left = right; return TRUE; }
  }
  else
  {
    if (right < rc.right - size.cx) { lpRect->left = right; return TRUE; }
    else if (left > rc.left) { lpRect->left = left; return TRUE; }
  }
  return FALSE;
}

BOOL CMonitorUtil::VerticalCollision(LPRECT lpRectParent, LPRECT lpRect, const SIZE& size, const RECT& rc)
{
  int y = (lpRect->bottom + lpRect->top) / 2;
  int yp = (lpRectParent->bottom + lpRectParent->top) / 2;
  int top = lpRectParent->top - size.cy;
  int bot = lpRectParent->bottom;
  if (y < yp)
  {
    if (top > rc.top) { lpRect->top = top; return TRUE; }
    else if (bot < rc.bottom - size.cy) { lpRect->top = bot; return TRUE; }
  }
  else
  {
    if (bot < rc.bottom - size.cy) { lpRect->top = bot; return TRUE; }
    else if (top > rc.top) { lpRect->top = top; return TRUE; }
  }
  return FALSE;
}