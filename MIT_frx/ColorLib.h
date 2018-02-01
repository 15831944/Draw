
#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// jpahn: ���� Color ����
		class __MY_EXT_CLASS__ CColorLib
		{
			// �⺻ Color ����
		public:
			// ���� b �� c1, c2 ���´�. (0 <= b <= 255)
			static COLORREF MixColor(COLORREF c1, COLORREF c2, BYTE b);
			// ���� d �� c1, c2 ���´�. (0.0 <= d <= 1.0)
			static COLORREF MixColor(COLORREF c1, COLORREF c2, double d);
			// d�� ���Ѵ�. 0-255 ���� ��� �ڸ���.
			static COLORREF MultipleColor(COLORREF c, double d);
			// c�� RGB�� ��ճ��� Gray �������� �����.
			static COLORREF AverageGray(COLORREF c);
			// Level �� ����
			static COLORREF Levels(COLORREF c, BYTE out_min, BYTE out_max);

			// Color Model ��ȯ
		public:
			// Hue, Saturation, Lightness
			static void RGBtoHSL(COLORREF rgb) {}
			// HSV(HSB)
			// Hue, Saturation, Value(Brightness)
			static void RGBtoHSV() {}

			// ����� Color ����
		public:
			// Disable ������ ��´�. (�ܼ� ���ȭ ���� ���� ��� �����.)
			static COLORREF DisableColor(COLORREF c);
		};
	}
}

#include "HeaderPost.h"