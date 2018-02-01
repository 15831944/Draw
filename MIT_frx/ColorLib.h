
#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// jpahn: 각종 Color 제어
		class __MY_EXT_CLASS__ CColorLib
		{
			// 기본 Color 연산
		public:
			// 비율 b 로 c1, c2 섞는다. (0 <= b <= 255)
			static COLORREF MixColor(COLORREF c1, COLORREF c2, BYTE b);
			// 비율 d 로 c1, c2 섞는다. (0.0 <= d <= 1.0)
			static COLORREF MixColor(COLORREF c1, COLORREF c2, double d);
			// d를 곱한다. 0-255 넘을 경우 자른다.
			static COLORREF MultipleColor(COLORREF c, double d);
			// c의 RGB를 평균내서 Gray 색상으로 만든다.
			static COLORREF AverageGray(COLORREF c);
			// Level 을 조절
			static COLORREF Levels(COLORREF c, BYTE out_min, BYTE out_max);

			// Color Model 변환
		public:
			// Hue, Saturation, Lightness
			static void RGBtoHSL(COLORREF rgb) {}
			// HSV(HSB)
			// Hue, Saturation, Value(Brightness)
			static void RGBtoHSV() {}

			// 기능적 Color 연산
		public:
			// Disable 색상을 얻는다. (단순 흑백화 보다 조금 밝게 만든다.)
			static COLORREF DisableColor(COLORREF c);
		};
	}
}

#include "HeaderPost.h"