#include "stdafx.h"
#include "ColorLib.h"


using namespace mit::frx;

COLORREF CColorLib::MixColor(COLORREF c1, COLORREF c2, BYTE b)
{
	return MixColor(c1, c2, (b / 255.0));
}

COLORREF CColorLib::MixColor(COLORREF c1, COLORREF c2, double d)
{
	BYTE r1 = GetRValue(c1);
	BYTE g1 = GetGValue(c1);
	BYTE b1 = GetBValue(c1);
	BYTE r2 = GetRValue(c2);
	BYTE g2 = GetGValue(c2);
	BYTE b2 = GetBValue(c2);
	BYTE r = r1 + (BYTE)(d * (r2 - r1));
	BYTE g = g1 + (BYTE)(d * (g2 - g1));
	BYTE b = b1 + (BYTE)(d * (b2 - b1));
	return RGB(r, g, b);
}

COLORREF CColorLib::MultipleColor(COLORREF color, double d)
{
	int r = (int)(GetRValue(color) * d);
	int g = (int)(GetGValue(color) * d);
	int b = (int)(GetBValue(color) * d);
	r = (r < 0 ? 0 : (r > 255 ? 255 : r));
	g = (g < 0 ? 0 : (g > 255 ? 255 : g));
	b = (b < 0 ? 0 : (b > 255 ? 255 : b));
	return RGB(r, g, b);
}

COLORREF CColorLib::AverageGray(COLORREF c)
{
	int r = GetRValue(c);
	int g = GetGValue(c);
	int b = GetBValue(c);
	int i = (int)((r + g + b) / 3.0);
	return RGB(i, i, i);
}

COLORREF CColorLib::Levels(COLORREF c, BYTE out_min, BYTE out_max)
{
	BYTE r = GetRValue(c);
	BYTE g = GetGValue(c);
	BYTE b = GetBValue(c);
	double d = ((int)out_max - (int)out_min) / 255.0;
	r = (BYTE)(r * d) + out_min;
	g = (BYTE)(g * d) + out_min;
	b = (BYTE)(b * d) + out_min;
	return RGB(r, g, b);
}



COLORREF CColorLib::DisableColor(COLORREF c)
{
	return Levels(AverageGray(c), 68, 250);
}