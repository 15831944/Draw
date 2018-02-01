#pragma once

#define MONITOR_CENTER     0x0001        // center rect to monitor 
#define MONITOR_CLIP       0x0000        // clip rect to monitor 
#define MONITOR_WORKAREA   0x0002        // use monitor work area 
#define MONITOR_AREA       0x0000        // use monitor entire area 
#define MONITOR_ALL_AREA   0x00F0        // (!!���� ����� �ȵȴ�) dual monitor �̻� �϶� monitor ���̿� ��ġ�� �� ���
#define MONITOR_EACH_AREA  0x0000		 // dual monitor �̻� �϶� monitor ���̿� ��ġ�� �� ������
#define MONITOR_HORIZONTAL 0x0004        // parent rect�� ��ĥ ��� ���ϴ� ����
#define MONITOR_VERTICAL   0x0008        // parent rect�� ��ĥ ��� ���ϴ� ����

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// jpahn: ����� �ȿ��� Popup ����
		class __MY_EXT_CLASS__ CMonitorUtil
		{
		public:
			// parent �� ������ ����� �����ϴ� ��ü�� ��.
			static void ClipOrCenterRectToMonitor(LPRECT lpRect, UINT flags);
			static void ClipOrCenterRectToMonitor(LPRECT lpRectParent, LPRECT lpRect, UINT flags);
			static void ClipOrCenterWindowToMonitor(HWND hwnd, UINT flags);
			static void ClipOrCenterWindowToMonitor(HWND hwndParent, HWND hwnd, UINT flags);
			static BOOL HorizontalCollision(LPRECT lpRectParent, LPRECT lpRect, const SIZE& size, const RECT& rc);
			static BOOL VerticalCollision(LPRECT lpRectParent, LPRECT lpRect, const SIZE& size, const RECT& rc);
		};
	}
}

#include "HeaderPost.h"