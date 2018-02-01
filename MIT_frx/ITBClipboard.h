#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ ITBClipboard
		{
		public:
			virtual BOOL Copy(DWORD dwFlags) = 0;
			virtual BOOL Paste() = 0;
		};
	}
}

#include "HeaderPost.h"