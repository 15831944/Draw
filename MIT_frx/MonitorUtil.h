#pragma once

#define MONITOR_CENTER     0x0001        // center rect to monitor 
#define MONITOR_CLIP       0x0000        // clip rect to monitor 
#define MONITOR_WORKAREA   0x0002        // use monitor work area 
#define MONITOR_AREA       0x0000        // use monitor entire area 
#define MONITOR_ALL_AREA   0x00F0        // (!!아직 제대로 안된다) dual monitor 이상 일때 monitor 사이에 걸치는 것 허용
#define MONITOR_EACH_AREA  0x0000		 // dual monitor 이상 일때 monitor 사이에 걸치는 것 허용안함
#define MONITOR_HORIZONTAL 0x0004        // parent rect와 겹칠 경우 피하는 방향
#define MONITOR_VERTICAL   0x0008        // parent rect와 겹칠 경우 피하는 방향

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// jpahn: 모니터 안에서 Popup 띄우기
		class __MY_EXT_CLASS__ CMonitorUtil
		{
		public:
			// parent 가 근접한 모니터 결정하는 주체가 됨.
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