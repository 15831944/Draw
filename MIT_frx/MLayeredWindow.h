#pragma once

#define MWT_MIN_FACTOR (0)
#define MWT_MAX_FACTOR (0xFF)

#include "HeaderPre.h"
namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MLayeredWindow
		{
		public:
			MLayeredWindow() {}
			~MLayeredWindow() {}
			
		public:
			static bool MakeTransparent(HWND hWnd, BYTE factor);
			static bool MakeWindowTransparent(CWnd *w, BYTE factor);
		};
	}
}

#include "HeaderPost.h"