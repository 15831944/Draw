///////////////////////////////////////////////////////////////////////////////
// GXSTYLES.inl
//
// Copyright (c) 1999-2009 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
// Author: Stefan Hoenig
//

// This file provides GX_INLINE methods for the following classes

#pragma once

#ifdef GX_INLINE

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

// #include <StingrayExportDefs.h>

#pragma warning(disable: 4311)

class CGXFont;
struct CGXBrush;
struct CGXPen;
class CGXResourceString;
class CGXStyle;
class CGXStylesMap;
class CGXStylePtrArray;
class CGXStylePtrArrayPtrArray;
class CGXData;


/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXFont

GX_INLINE CGXFont::CGXFont()
{
	memset(&m_b8Value, 0, sizeof(m_b8Value));
	fontbits.nOrientation = GX_DEFAULT_ORIENTATION;
	fontbits.nWeight = GX_DEFAULT_WEIGHT;
	fontbits.nFaceName = GX_DEFAULT_FACENAME;
}

GX_INLINE CGXFontData* CGXFont::GetData() const
{
	return GetData(GetFontKey());
}

GX_INLINE void CGXFont::Release()
{
	if (fontbits.fontdata) Release(GetFontKey());
}

GX_INLINE BOOL CGXFont::IsEmptyFont() const
{
	return GetFontKey() == CGXFont().GetFontKey();
}

GX_INLINE GXBYTE8 CGXFont::GetFontKey() const
{          
#if _MFC_VER >= 0x0300
	return m_b8Value >> 1;
#else
	GXBYTE8 d = m_b8Value;
	BYTE* pd = (BYTE*) &d;

	*pd = (BYTE) (*pd >> 1);	
	
	return d;
#endif
}

// weight
GX_INLINE BOOL CGXFont::GetIncludeWeight() const
	{ return (BOOL) fontbits.nWeight != GX_DEFAULT_WEIGHT; }

GX_INLINE CGXFont& CGXFont::SetIncludeWeight(BOOL b)
	{ Release(); if (!b) fontbits.nWeight = GX_DEFAULT_WEIGHT; return *this; }

GX_INLINE LONG CGXFont::GetWeight() const
	{   ASSERT(GetIncludeWeight());
		// ASSERTION-> Did you check GetInclude...?() ->END
		return Weight_ui2lf(fontbits.nWeight); }

GX_INLINE CGXFont& CGXFont::SetWeight(LONG nWeight)
	{ Release(); fontbits.nWeight = Weight_lf2ui(nWeight); return SetIncludeWeight(TRUE); }

GX_INLINE BOOL CGXFont::GetBold() const
	{   ASSERT(GetIncludeWeight());
		// ASSERTION-> Did you check CGXFont::GetInclude...?() ->END
		return GetWeight() >= FW_BOLD; }

GX_INLINE BOOL CGXFont::IsEqual(const CGXFont& font) const
	{ return memcmp(&GetLogFontRef(), &font.GetLogFontRef(), sizeof(LOGFONT)) == 0; }

GX_INLINE CGXFont& CGXFont::SetBold(BOOL b)
	{ SetWeight(b ? FW_BOLD : FW_NORMAL); return CGXFont::SetIncludeWeight(TRUE); }

// Italic
GX_INLINE BOOL CGXFont::GetIncludeItalic() const
	{ return (BOOL) fontbits.italic; }

GX_INLINE CGXFont& CGXFont::SetIncludeItalic(BOOL b)
	{ Release(); fontbits.italic = (unsigned) b; return *this; }

GX_INLINE BOOL CGXFont::GetItalic() const
	{   ASSERT(GetIncludeItalic());
		// ASSERTION-> Did you check CGXFont::GetInclude...?() ->END
		return fontbits.nItalic != 0; }

GX_INLINE CGXFont& CGXFont::SetItalic(BOOL b)
	{ Release(); fontbits.nItalic = b?1:0; return CGXFont::SetIncludeItalic(TRUE); }

// Underline
GX_INLINE BOOL CGXFont::GetIncludeUnderline() const
	{ return (BOOL) fontbits.underline; }

GX_INLINE CGXFont& CGXFont::SetIncludeUnderline(BOOL b)
	{ Release(); fontbits.underline = (unsigned) b; return *this; }

GX_INLINE BOOL CGXFont::GetUnderline() const
	{   ASSERT(GetIncludeUnderline());
		// ASSERTION-> Did you check CGXFont::GetInclude...? ->END
		return fontbits.nUnderline != 0; }

GX_INLINE CGXFont& CGXFont::SetUnderline(BOOL b)
	{ Release(); fontbits.nUnderline = b?1:0; return CGXFont::SetIncludeUnderline(TRUE); }

// StrikeOut
GX_INLINE BOOL CGXFont::GetIncludeStrikeOut() const
	{   return (BOOL) fontbits.strikeout; }

GX_INLINE CGXFont& CGXFont::SetIncludeStrikeOut(BOOL b)
	{ Release(); fontbits.strikeout = (unsigned) b; return *this; }

GX_INLINE BOOL CGXFont::GetStrikeOut() const
	{   ASSERT(GetIncludeStrikeOut());
		// ASSERTION-> Did you check CGXFont::GetInclude...? ->END
		return fontbits.nStrikeOut != 0; }

GX_INLINE CGXFont& CGXFont::SetStrikeOut(BOOL b)
	{ Release(); fontbits.nStrikeOut = b?1:0; return CGXFont::SetIncludeStrikeOut(TRUE); }

// Size
GX_INLINE BOOL CGXFont::GetIncludeSize() const
	{ return (BOOL) fontbits.nSize != GX_DEFAULT_SIZE; }

GX_INLINE CGXFont& CGXFont::SetIncludeSize(BOOL b)
	{ Release(); if (!b) fontbits.nSize = GX_DEFAULT_SIZE; return *this; }

GX_INLINE double CGXFont::GetSize() const
	{   ASSERT(GetIncludeSize());
		// ASSERTION-> Did you check CGXFont::GetInclude...? ->END
		return Size_ui2lf(fontbits.nSize); }

GX_INLINE CGXFont& CGXFont::SetSize(double size)
	{ Release(); fontbits.nSize = Size_lf2ui(size); return CGXFont::SetIncludeSize(TRUE); }

// Orientation
GX_INLINE BOOL CGXFont::GetIncludeOrientation() const
	{ return (BOOL) fontbits.nOrientation != GX_DEFAULT_ORIENTATION; }

GX_INLINE CGXFont& CGXFont::SetIncludeOrientation(BOOL b)
	{ Release(); if (!b) fontbits.nOrientation = GX_DEFAULT_ORIENTATION; return *this; }

GX_INLINE LONG CGXFont::GetOrientation() const
	{   ASSERT(GetIncludeOrientation());
		// ASSERTION-> Did you check CGXFont::GetInclude...? ->END
		return Orientation_ui2lf(fontbits.nOrientation); }

GX_INLINE CGXFont& CGXFont::SetOrientation(LONG nOrientation)
	{ Release(); fontbits.nOrientation = Orientation_lf2ui(nOrientation); return CGXFont::SetIncludeOrientation(TRUE); }

// FaceName
GX_INLINE BOOL CGXFont::GetIncludeFaceName() const
	{ return (BOOL) fontbits.nFaceName != GX_DEFAULT_FACENAME; }

GX_INLINE CGXFont& CGXFont::SetIncludeFaceName(BOOL b)
	{ Release(); if (!b) fontbits.nFaceName = GX_DEFAULT_FACENAME; return *this; }

GX_INLINE LPCTSTR CGXFont::GetFaceName() const
	{   ASSERT(GetIncludeFaceName());
		// ASSERTION-> Did you check CGXFont::GetInclude...? ->END
		return FaceName_ui2str(GetFaceNameId()); }

GX_INLINE unsigned CGXFont::GetFaceNameId() const
	{   ASSERT(GetIncludeFaceName());
		// ASSERTION-> Did you check CGXFont::GetInclude...? ->END
		return fontbits.nFaceName; }

GX_INLINE CGXFont& CGXFont::SetFaceName(LPCTSTR facename)
	{ return SetFaceNameId(FaceName_str2ui(facename)); }

GX_INLINE CGXFont& CGXFont::SetFaceNameId(unsigned nFaceName)
	{ Release(); fontbits.nFaceName = nFaceName; return *this; }

GX_INLINE BOOL CGXFont::operator==(const CGXFont& font) const
	{ return font.GetFontKey() == GetFontKey(); }

GX_INLINE BOOL CGXFont::operator!=(const CGXFont& font) const
	{ return font.GetFontKey() != GetFontKey();; }

/////////////////////////////////////////////////////////////////////////////
// struct GRID_API CGXBrush

GX_INLINE UINT CGXBrush::GetStyle() const
	{ return lbStyle; }

GX_INLINE CGXBrush& CGXBrush::SetStyle(UINT style)
	{ lbStyle = style; return *this; }

GX_INLINE COLORREF CGXBrush::GetColor() const
	{ return GXGETCOLOR2(lbColor1, lbColor2); }

GX_INLINE COLORREF CGXBrush::GetColorNA() const
	{ return GXGETCOLORNA2(lbColor1, lbColor2); }

GX_INLINE CGXBrush& CGXBrush::SetColor(COLORREF color)
	{ lbColor1 = GXCOLOR1(color); lbColor2 = GXCOLOR2(color); return *this; }

GX_INLINE LONG CGXBrush::GetHatch() const
	{ return lbHatch; }

GX_INLINE CGXBrush& CGXBrush::SetHatch(LONG hatch)
	{ lbHatch = (int) hatch; return *this; }

GX_INLINE int CGXBrush::GetPattern() const
	{ return lbPattern; }

GX_INLINE CGXBrush& CGXBrush::SetPattern(int nPattern)
	{ lbHatch = (int)(SEC_DWORD)GXGetPatternBitmap(lbPattern = nPattern)->GetSafeHandle(); return SetStyle(BS_PATTERN); }

GX_INLINE COLORREF CGXBrush::GetBkColor() const
	{ return GXGETCOLOR2(lbBkColor1, lbBkColor2); }

GX_INLINE COLORREF CGXBrush::GetBkColorNA() const
	{ return GXGETCOLORNA2(lbBkColor1, lbBkColor2); }

GX_INLINE CGXBrush& CGXBrush::SetBkColor(COLORREF color)
	{ lbBkColor1 = GXCOLOR1(color); lbBkColor2 = GXCOLOR2(color); return *this; }


GX_INLINE CGXBrush& CGXBrush::operator=(const CGXBrush& brush)
{ 
	memcpy(this, &brush, sizeof(CGXBrush));  return *this; 
}

GX_INLINE BOOL CGXBrush::operator==(const CGXBrush& brush) const
{ 
	return memcmp(this, &brush, sizeof(CGXBrush)) == 0; 
}

GX_INLINE BOOL CGXBrush::operator!=(const CGXBrush& brush) const
{ 
	return memcmp(this, &brush, sizeof(CGXBrush)) != 0;  
}

GX_INLINE GXBYTE8 CGXBrush::GetBrushKey() const
{
	return *((GXBYTE8*) this);
}


/////////////////////////////////////////////////////////////////////////////
// struct GRID_API CGXPen

// Pen

GX_INLINE CGXPen::CGXPen()
	{ memset(this, 0, sizeof(CGXPen)); lopnStyle = GX_PS_DEFAULT; lopnWidth = 1; }

GX_INLINE CGXPen::CGXPen(const tagLOGPEN& logpen)
	{ lopnStyle = logpen.lopnStyle; lopnWidth = logpen.lopnWidth.x; lopnColor1 = GXCOLOR1(logpen.lopnColor); lopnColor2 = GXCOLOR2(logpen.lopnColor); SetInclude(TRUE); }

GX_INLINE CGXPen::CGXPen(const CGXPen& pen)
	{ memcpy(this, &pen, sizeof(pen)); }

GX_INLINE CGXPen::CGXPen(UINT style, int width, COLORREF color)
	{ lopnStyle = style; lopnColor1 = GXCOLOR1(color); lopnColor2 = GXCOLOR2(color); lopnWidth = width; SetInclude(TRUE); }

GX_INLINE CGXPen& CGXPen::operator=(const tagLOGPEN& logpen)
	{ lopnStyle = logpen.lopnStyle; lopnWidth = logpen.lopnWidth.x; lopnColor1 = GXCOLOR1(logpen.lopnColor); lopnColor2 = GXCOLOR2(logpen.lopnColor); return SetInclude(TRUE); }

GX_INLINE CGXPen& CGXPen::operator=(const CGXPen& pen)
	{ memcpy(this, &pen, sizeof(pen)); return *this; }

GX_INLINE BOOL CGXPen::operator==(const CGXPen& pen) const
	{ return memcmp(this, &pen, sizeof(CGXPen)) == 0; }

GX_INLINE BOOL CGXPen::operator!=(const CGXPen& pen) const
	{ return memcmp(this, &pen, sizeof(CGXPen)) != 0; }

GX_INLINE BOOL CGXPen::GetInclude() const
	{ return lopnStyle != GX_PS_DEFAULT; }

GX_INLINE UINT CGXPen::GetStyle() const
	{   ASSERT(GetInclude());
		// ASSERTION-> Did you check GetInclude? ->END
		return lopnStyle; }

GX_INLINE CGXPen& CGXPen::SetStyle(UINT style)
	{ lopnStyle = style; return SetInclude(TRUE); }

GX_INLINE int CGXPen::GetWidth() const
	{   ASSERT(GetInclude());
		// ASSERTION-> Did you check GetInclude? ->END
		return (int) lopnWidth; }

GX_INLINE CGXPen& CGXPen::SetWidth(int width)
	{ lopnWidth = (unsigned) width; return SetInclude(TRUE); }

GX_INLINE COLORREF CGXPen::GetColor() const
	{   ASSERT(GetInclude());
		// ASSERTION-> Did you check GetInclude? ->END
		return GXGETCOLOR2(lopnColor1, lopnColor2); }

GX_INLINE COLORREF CGXPen::GetColorNA() const
	{   ASSERT(GetInclude());
		// ASSERTION-> Did you check GetInclude? ->END
		return GXGETCOLORNA2(lopnColor1, lopnColor2); }

GX_INLINE CGXPen& CGXPen::SetColor(COLORREF color)
	{ lopnColor1 = GXCOLOR1(color); lopnColor2 = GXCOLOR2(color); return SetInclude(TRUE); }

GX_INLINE GXBYTE8 CGXPen::GetPenKey() const
{
	return *((GXBYTE8*) this);
}


/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXResourceString

// simple wrapper class for using strings directly from a resource id.

GX_INLINE CGXResourceString::CGXResourceString(UINT nID)
	{ if (!LoadString(nID))
		AfxThrowResourceException(); }

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXStyle

// cell style


GX_INLINE CGXStyle::CGXStyle()
	{ ConstructStyle(); }

GX_INLINE CGXStyle::CGXStyle(LPCTSTR s)
	{ ConstructStyle(); SetValue(s); }

GX_INLINE CGXStyle::STYLEBITS::STYLEBITS(DWORD dw)
	{ SetPortable(dw); }

GX_INLINE DWORD CGXStyle::STYLEBITS::GetNoPortableBits() const
	{ return *((DWORD*) this); } 

GX_INLINE void CGXStyle::STYLEBITS::SetNoPortableBits(DWORD dw) 
	{ *((DWORD*) this) = dw; }

GX_INLINE BOOL CGXStyle::STYLEBITS::NoPortableIsEmptyBits() const 
	{ return GetNoPortableBits() == 0; }

// Horizontal Alignment
GX_INLINE BOOL CGXStyle::GetIncludeHorizontalAlignment() const
	{ return (BOOL) stylebits.horzalign; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeHorizontalAlignment(BOOL b)
	{ stylebits.horzalign = (unsigned) b; return *this; }

GX_INLINE DWORD CGXStyle::GetHorizontalAlignment() const
	{   
		ASSERT(GetIncludeHorizontalAlignment());
		// ASSERTION-> Did you check CGXStyle::GetInclude... ->END
		switch (boolbits.m_nHorizontalAlignment)
		{
		default: return DT_LEFT;
		case 1: return DT_CENTER;
		case 2: return DT_RIGHT;
		}
	}	


GX_INLINE CGXStyle& CGXStyle::SetHorizontalAlignment(DWORD dwAlign)
	{   
		ASSERT(dwAlign == DT_CENTER || dwAlign == DT_LEFT || dwAlign == DT_RIGHT);
		// ASSERTION-> wrong argument ->END
		switch (dwAlign)
		{
		default:		boolbits.m_nHorizontalAlignment = 0; break;
		case DT_CENTER:	boolbits.m_nHorizontalAlignment = 1; break;
		case DT_RIGHT:	boolbits.m_nHorizontalAlignment = 2; break;
		}
		return CGXStyle::SetIncludeHorizontalAlignment(TRUE); 
	}

// Vertical Alignment
GX_INLINE BOOL CGXStyle::GetIncludeVerticalAlignment()  const
	{ return (BOOL) stylebits.vertalign; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeVerticalAlignment(BOOL b)
	{ stylebits.vertalign = (unsigned) b; return *this; }

GX_INLINE DWORD CGXStyle::GetVerticalAlignment() const
	{   
		ASSERT(GetIncludeVerticalAlignment());
		// ASSERTION-> Did you check CGXStyle::GetInclude... ->END
		switch (boolbits.m_nVerticalAlignment)
		{
		default: return DT_TOP;
		case 1: return DT_VCENTER;
		case 2: return DT_BOTTOM;
		}
	}	

GX_INLINE CGXStyle& CGXStyle::SetVerticalAlignment(DWORD dwAlign)
	{   
		ASSERT(dwAlign == DT_VCENTER || dwAlign == DT_TOP || dwAlign == DT_BOTTOM);
		// ASSERTION-> wrong argument ->END
		switch (dwAlign)
		{
		default:			boolbits.m_nVerticalAlignment = 0; break;
		case DT_VCENTER:	boolbits.m_nVerticalAlignment = 1; break;
		case DT_BOTTOM:		boolbits.m_nVerticalAlignment = 2; break;
		}
		return CGXStyle::SetIncludeVerticalAlignment(TRUE); 
	}

// Readonly
GX_INLINE BOOL CGXStyle::GetIncludeReadOnly() const
	{ return (BOOL) stylebits.readonly; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeReadOnly(BOOL b)
	{ stylebits.readonly = (unsigned) b; return *this; }

GX_INLINE BOOL CGXStyle::GetReadOnly() const
	{   ASSERT(GetIncludeReadOnly());
		// ASSERTION-> Did you check CGXStyle::GetInclude... ->END
		return boolbits.m_bReadOnly; }

GX_INLINE CGXStyle& CGXStyle::SetReadOnly(BOOL b)
	{ boolbits.m_bReadOnly = (BYTE) b; return CGXStyle::SetIncludeReadOnly(TRUE); }

// Control
GX_INLINE BOOL CGXStyle::GetIncludeControl() const
	{ return (BOOL) stylebits.control; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeControl(BOOL b)
	{ stylebits.control = (unsigned) b; return *this; }

GX_INLINE WORD CGXStyle::GetControl() const
	{   ASSERT(GetIncludeControl());
		// ASSERTION-> Did you check CGXStyle::GetInclude... ->END
		return m_nControl; }

GX_INLINE CGXStyle& CGXStyle::SetControl(WORD nControl)
	{ ASSERT(nControl <= xWORD_MAX); m_nControl = nControl; return CGXStyle::SetIncludeControl(TRUE); }

// MaxLength
GX_INLINE BOOL CGXStyle::GetIncludeMaxLength() const
	{ return (BOOL) stylebits.maxlength; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeMaxLength(BOOL b)
	{ stylebits.maxlength = (unsigned) b; return *this; }

GX_INLINE WORD CGXStyle::GetMaxLength() const
	{   ASSERT(GetIncludeMaxLength());
		// ASSERTION-> Did you check CGXStyle::GetInclude... ->END
		return m_nMaxLength; }

GX_INLINE CGXStyle& CGXStyle::SetMaxLength(WORD nMaxLength)
	{ m_nMaxLength = nMaxLength; return CGXStyle::SetIncludeMaxLength(TRUE); }

// VertScrollBar
GX_INLINE BOOL CGXStyle::GetIncludeVertScrollBar() const
	{ return (BOOL) stylebits.vertscroll; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeVertScrollBar(BOOL b)
	{ stylebits.vertscroll = (unsigned) b; return *this; }

GX_INLINE BOOL CGXStyle::GetVertScrollBar() const
	{   ASSERT(GetIncludeVertScrollBar());
		// ASSERTION-> Did you check CGXStyle::GetInclude... ->END
		return (BOOL) boolbits.m_bVertScroll; }

GX_INLINE CGXStyle& CGXStyle::SetVertScrollBar(BOOL b)
	{ boolbits.m_bVertScroll = (BYTE) b; return CGXStyle::SetIncludeVertScrollBar(TRUE); }

// Interior
GX_INLINE BOOL CGXStyle::GetIncludeInterior() const
	{ return (BOOL) stylebits.interior; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeInterior(BOOL b)
	{ stylebits.interior = (unsigned) b; return *this; }

GX_INLINE CGXBrush CGXStyle::GetInterior() const
	{   ASSERT(GetIncludeInterior());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return m_lbInterior; }

GX_INLINE const CGXBrush& CGXStyle::GetInteriorRef() const
	{   ASSERT(GetIncludeInterior());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return m_lbInterior; }

GX_INLINE CGXStyle& CGXStyle::SetInterior(const CGXBrush& lb)
	{ m_lbInterior = lb; return CGXStyle::SetIncludeInterior(TRUE); }

GX_INLINE CGXStyle& CGXStyle::SetInterior(COLORREF rgbColor)
	{   m_lbInterior.SetStyle(BS_SOLID).SetColor(rgbColor);
	  	return CGXStyle::SetIncludeInterior(TRUE); }

// Negative State Text Color
GX_INLINE BOOL CGXStyle::GetIncludeNegativeStateColor() const
	{ return GetIncludeUserAttribute(GX_IDS_UA_NEGATIVE_TEXT); }

GX_INLINE CGXStyle& CGXStyle::SetIncludeNegativeStateColor(BOOL b)
	{ if(b && !GetIncludeUserAttribute(GX_IDS_UA_NEGATIVE_TEXT))
		SetUserAttribute(GX_IDS_UA_NEGATIVE_TEXT, RGB(0, 0, 0));	// Default color, black
	else if(!b)
		SetIncludeUserAttribute(GX_IDS_UA_NEGATIVE_TEXT, FALSE);
	return *this; }

GX_INLINE DWORD CGXStyle::GetNegativeStateColor() const
	{   ASSERT(GetIncludeNegativeStateColor());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return (DWORD)GetUserAttribute(GX_IDS_UA_NEGATIVE_TEXT).GetLongValue(); }

GX_INLINE CGXStyle& CGXStyle::SetNegativeStateColor(DWORD color)
{ SetUserAttribute(GX_IDS_UA_NEGATIVE_TEXT, color); return CGXStyle::SetIncludeNegativeStateColor(TRUE);}

// Borders
GX_INLINE BOOL CGXStyle::GetIncludeBorders() const
	{ return (BOOL) stylebits.borders; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeBorders(BOOL b)
	{ stylebits.borders = (unsigned) b; return *this; }

GX_INLINE CGXPen CGXStyle::GetBorders(GXBorderType border) const
	{   ASSERT(m_pPenArray && CGXStyle::GetIncludeBorders());
		// ASSERTION-> Either Borders is not included or m_pPenArray is NULL
		// Did you check CGXStyle::GetIncludeBorders? ->END
		return m_pPenArray[border]; }

GX_INLINE const CGXPen& CGXStyle::GetBordersRef(GXBorderType border) const
	{   ASSERT(m_pPenArray && CGXStyle::GetIncludeBorders());
		// ASSERTION-> Either Borders is not included or m_pPenArray is NULL
		// Did you check CGXStyle::GetIncludeBorders? ->END
		return m_pPenArray[border]; }

GX_INLINE BOOL CGXStyle::GetIncludeBorders(GXBorderType border) const
	{ return (BOOL) stylebits.borders
		&& m_pPenArray
		&& m_pPenArray[border].GetInclude(); }

// Font
GX_INLINE BOOL CGXStyle::GetIncludeFont() const
	{ return (BOOL) stylebits.font; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeFont(BOOL b)
	{ stylebits.font = (unsigned) b; return *this; }

GX_INLINE CGXFont CGXStyle::GetFont() const
	{   ASSERT(m_pFont && CGXStyle::GetIncludeFont());
		// ASSERTION-> Either Font is not included or m_pFont is NULL.
		// Did you check CGXStyle::GetIncludeFont? ->END
		return *m_pFont; }

GX_INLINE const CGXFont& CGXStyle::GetFontRef() const
	{   ASSERT(m_pFont && CGXStyle::GetIncludeFont());
		// ASSERTION-> Either Font is not included or m_pFont is NULL.
		// Did you check CGXStyle::GetIncludeFont? ->END
		return *m_pFont; }

// Text Color
GX_INLINE BOOL CGXStyle::GetIncludeTextColor() const
	{ return (BOOL) stylebits.textcolor; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeTextColor(BOOL b)
	{ stylebits.textcolor = (unsigned) b; return *this; }

GX_INLINE COLORREF CGXStyle::GetTextColor() const
	{   ASSERT(GetIncludeTextColor());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return GXGETCOLOR2(boolbits.m_rgbTextColor1, boolbits.m_rgbTextColor2); }

GX_INLINE COLORREF CGXStyle::GetTextColorNA() const
	{   ASSERT(GetIncludeTextColor());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return GXGETCOLORNA2(boolbits.m_rgbTextColor1, boolbits.m_rgbTextColor2); }

GX_INLINE CGXStyle& CGXStyle::SetTextColor(COLORREF rgbColor)
	{ boolbits.m_rgbTextColor1 = GXCOLOR1(rgbColor); boolbits.m_rgbTextColor2 = GXCOLOR2(rgbColor); return CGXStyle::SetIncludeTextColor(TRUE); }

// WrapText
GX_INLINE BOOL CGXStyle::GetIncludeWrapText() const
	{ return stylebits.wraptext; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeWrapText(BOOL b)
	{ stylebits.wraptext = (unsigned) b; return *this; }

GX_INLINE BOOL CGXStyle::GetWrapText() const
	{   ASSERT(GetIncludeWrapText());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return boolbits.m_bWrapText; }

GX_INLINE CGXStyle& CGXStyle::SetWrapText(BOOL b)
	{ boolbits.m_bWrapText = (BYTE) b; return CGXStyle::SetIncludeWrapText(TRUE); }

// AutoSize
GX_INLINE BOOL CGXStyle::GetIncludeAutoSize() const
	{ return stylebits.autosize; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeAutoSize(BOOL b)
	{ stylebits.autosize = (unsigned) b; return *this; }

GX_INLINE BOOL CGXStyle::GetAutoSize() const
	{   ASSERT(GetIncludeAutoSize());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return boolbits.m_bAutoSize; }

GX_INLINE CGXStyle& CGXStyle::SetAutoSize(BOOL b)
	{ boolbits.m_bAutoSize = (BYTE) b; return CGXStyle::SetIncludeAutoSize(TRUE); }

// Allow Enter
GX_INLINE BOOL CGXStyle::GetIncludeAllowEnter() const
	{ return stylebits.allowenter; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeAllowEnter(BOOL b)
	{ stylebits.allowenter = (unsigned) b; return *this; }

GX_INLINE BOOL CGXStyle::GetAllowEnter() const
	{   ASSERT(GetIncludeAllowEnter());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return boolbits.m_bAllowEnter; }

GX_INLINE CGXStyle& CGXStyle::SetAllowEnter(BOOL b)
	{ boolbits.m_bAllowEnter = (BYTE) b; return CGXStyle::SetIncludeAllowEnter(TRUE); }

// Float Cells
GX_INLINE BOOL CGXStyle::GetIncludeFloatCell() const
	{ return stylebits.floatcell; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeFloatCell(BOOL b)
	{ stylebits.floatcell = (unsigned) b; return *this; }

GX_INLINE BOOL CGXStyle::GetFloatCell() const
	{   ASSERT(GetIncludeFloatCell());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return boolbits.m_bFloatCell; }

GX_INLINE CGXStyle& CGXStyle::SetFloatCell(BOOL b)
	{ boolbits.m_bFloatCell = (BYTE) b; return CGXStyle::SetIncludeFloatCell(TRUE); }

// Flood Cells
GX_INLINE BOOL CGXStyle::GetIncludeFloodCell() const
	{ return stylebits.floodcell; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeFloodCell(BOOL b)
	{ stylebits.floodcell = (unsigned) b; return *this; }

GX_INLINE BOOL CGXStyle::GetFloodCell() const
	{   ASSERT(GetIncludeFloodCell());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return boolbits.m_bFloodCell; }

GX_INLINE CGXStyle& CGXStyle::SetFloodCell(BOOL b)
	{ boolbits.m_bFloodCell = (BYTE) b; return CGXStyle::SetIncludeFloodCell(TRUE); }

// Merge Cells
GX_INLINE BOOL CGXStyle::GetIncludeMergeCell() const
	{ return stylebits.mergecell; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeMergeCell(BOOL b)
	{ stylebits.mergecell = (unsigned) b; return *this; }

GX_INLINE unsigned CGXStyle::GetMergeCell() const
	{   ASSERT(GetIncludeMergeCell());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return boolbits.m_nMergeCell; }

GX_INLINE CGXStyle& CGXStyle::SetMergeCell(unsigned ui)
	{ boolbits.m_nMergeCell = ui; return CGXStyle::SetIncludeMergeCell(TRUE); }

// Format
GX_INLINE BOOL CGXStyle::GetIncludeFormat() const
	{ return stylebits.format; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeFormat(BOOL b)
	{ stylebits.format = (unsigned) b; return *this; }

GX_INLINE unsigned CGXStyle::GetFormat() const
	{   ASSERT(GetIncludeFormat());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return boolbits.m_nFormat; }

GX_INLINE CGXStyle& CGXStyle::SetFormat(unsigned ui)
	{ boolbits.m_nFormat = ui; return CGXStyle::SetIncludeFormat(TRUE); }

// Places (for format)
GX_INLINE BOOL CGXStyle::GetIncludePlaces() const
	{ return stylebits.places; }

GX_INLINE CGXStyle& CGXStyle::SetIncludePlaces(BOOL b)
	{ stylebits.places = (unsigned) b; return *this; }

GX_INLINE unsigned CGXStyle::GetPlaces() const
	{   ASSERT(GetIncludePlaces());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return boolbits.m_nPlaces; }

GX_INLINE CGXStyle& CGXStyle::SetPlaces(unsigned ui)
	{ boolbits.m_nPlaces = ui; return SetIncludePlaces(TRUE); }

// Value

GX_INLINE CGXStyle& CGXStyle::SetValueType(unsigned nType)
	{ boolbits.m_nValueType = nType; return *this; }

GX_INLINE unsigned CGXStyle::GetValueType()	const
	{ return boolbits.m_nValueType; }

GX_INLINE BOOL CGXStyle::GetIncludeValue() const
	{ return stylebits.value; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeValue(BOOL b)
	{ stylebits.value = (unsigned) b; if (!b) m_sValue.Empty(); return *this; }

// Note! CGXStyle::GetValue and CGXStyle::GetValueRef return an empty string
// if the value is not included in the style.
GX_INLINE const CString& CGXStyle::GetValue() const
	{   return m_sValue; }	    

GX_INLINE const CString& CGXStyle::GetValueRef() const
	{   return m_sValue; }

GX_INLINE CGXStyle& CGXStyle::SetValue(LPCTSTR s)
	{ m_sValue = s; SetValueType(GX_VT_STRING); return CGXStyle::SetIncludeValue(TRUE); }

GX_INLINE CGXStyle& CGXStyle::SetValue(const CString& s)
	{ m_sValue = s; SetValueType(GX_VT_STRING); return CGXStyle::SetIncludeValue(TRUE); }

//      I have already tried to use a pointer instead of CString
//      { delete m_pszValue; m_pszValue = new char [strlen(s)+1]; _tcscpy(m_pszValue, s); return CGXStyle::SetIncludeValue(TRUE); }
//      But, this is not much faster, so I continued to use CString for the value

#ifdef _UNICODE
// special UNICODE version of SetValue will convert ansi characters
// to wide characters.
GX_INLINE CGXStyle& CGXStyle::SetValue(const char* s)
	{ m_sValue = s; SetValueType(GX_VT_STRING); return CGXStyle::SetIncludeValue(TRUE); }

#endif

#if _MFC_VER >= 0x0300

GX_INLINE CGXStyle& CGXStyle::SetValue(DWORD dw)
	{ CString str; str.Format(_T("%lu"), dw); CGXStyle::SetValue(str); return SetValueType(GX_VT_NUMERIC); }

GX_INLINE CGXStyle& CGXStyle::SetValue(UINT ui)
	{ CString str; str.Format(_T("%u"), ui); CGXStyle::SetValue(str); return SetValueType(GX_VT_NUMERIC); }

GX_INLINE CGXStyle& CGXStyle::SetValue(WORD w)
	{ CString str; str.Format(_T("%u"), w); CGXStyle::SetValue(str); return SetValueType(GX_VT_NUMERIC); }

GX_INLINE CGXStyle& CGXStyle::SetValue(short s)
	{ CString str; str.Format(_T("%d"), s); CGXStyle::SetValue(str); return SetValueType(GX_VT_NUMERIC); }

GX_INLINE CGXStyle& CGXStyle::SetValue(LONG l)
	{ CString str; str.Format(_T("%ld"), l); CGXStyle::SetValue(str); return SetValueType(GX_VT_NUMERIC); }

GX_INLINE CGXStyle& CGXStyle::SetValue(float f)
	{ CString str; str.Format(_T("%.7g"), f); GXGetAppData()->PutPointInString(str); CGXStyle::SetValue(str); return SetValueType(GX_VT_NUMERIC); }

GX_INLINE CGXStyle& CGXStyle::SetValue(double d)
	{ CString str; str.Format(_T("%.13g"), d); GXGetAppData()->PutPointInString(str); CGXStyle::SetValue(str); return SetValueType(GX_VT_NUMERIC); }

#else

GX_INLINE CGXStyle& CGXStyle::SetValue(DWORD dw)
	{ TCHAR sz[18]; wsprintf(sz, _T("%lu"), dw); CGXStyle::SetValue(sz); return SetValueType(GX_VT_NUMERIC); }

GX_INLINE CGXStyle& CGXStyle::SetValue(UINT ui)
	{ TCHAR sz[18]; wsprintf(sz, _T("%u"), ui); CGXStyle::SetValue(sz); return SetValueType(GX_VT_NUMERIC); }

GX_INLINE CGXStyle& CGXStyle::SetValue(WORD w)
	{ TCHAR sz[18]; wsprintf(sz, _T("%u"), w); CGXStyle::SetValue(sz); return SetValueType(GX_VT_NUMERIC); }

GX_INLINE CGXStyle& CGXStyle::SetValue(short s)
	{ TCHAR sz[18]; wsprintf(sz, _T("%d"), s); CGXStyle::SetValue(sz); return SetValueType(GX_VT_NUMERIC); }

GX_INLINE CGXStyle& CGXStyle::SetValue(LONG l)
	{ TCHAR sz[18]; wsprintf(sz, _T("%ld"), l); CGXStyle::SetValue(sz); return SetValueType(GX_VT_NUMERIC); }

GX_INLINE CGXStyle& CGXStyle::SetValue(float f)
	{ TCHAR sz[64]; _stprintf(sz, _T("%g"), f); CGXStyle::SetValue(sz); return SetValueType(GX_VT_NUMERIC); }

GX_INLINE CGXStyle& CGXStyle::SetValue(double d)
	{ TCHAR sz[64]; _stprintf(sz, _T("%g"), d); CGXStyle::SetValue(sz); return SetValueType(GX_VT_NUMERIC); }

#endif

GX_INLINE DWORD CGXStyle::GetDWordValue() const
	{   return (DWORD) _ttol(GetValueRef()); }

GX_INLINE WORD CGXStyle::GetWordValue() const
	{   return (WORD) _ttoi(GetValueRef()); }

GX_INLINE UINT CGXStyle::GetUIntValue() const
	{   return (UINT) _ttoi(GetValueRef()); }

GX_INLINE short CGXStyle::GetShortValue() const
	{   return (short) _ttoi(GetValueRef()); }

GX_INLINE LONG CGXStyle::GetLongValue() const
	{   return (LONG) _ttol(GetValueRef()); }

GX_INLINE float CGXStyle::GetFloatValue() const
	{   return (float) _gxttof(GetValueRef()); }

GX_INLINE double CGXStyle::GetDoubleValue() const
	{   return (double) _gxttof(GetValueRef()); }

// Basestyle
GX_INLINE BOOL CGXStyle::GetIncludeBaseStyle() const
	{ return stylebits.basestyle; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeBaseStyle(BOOL b)
	{ stylebits.basestyle = (unsigned) b; return *this; }

GX_INLINE WORD CGXStyle::GetBaseStyle() const
	{   ASSERT(GetIncludeBaseStyle());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return (WORD) boolbits.m_wBaseStyleId; }

GX_INLINE CGXStyle& CGXStyle::SetBaseStyle(WORD wBaseStyleId)
	{ ASSERT(wBaseStyleId < 256);
		// ASSERTION-> Only 256 base styles supported ->END
		boolbits.m_wBaseStyleId = wBaseStyleId; return CGXStyle::SetIncludeBaseStyle(TRUE); }

// Choice list: each choice is separated with a new newline
GX_INLINE BOOL CGXStyle::GetIncludeChoiceList() const
	{ return stylebits.choicelist; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeChoiceList(BOOL b)
	{ stylebits.choicelist = (unsigned) b; return *this; }

GX_INLINE const CString& CGXStyle::GetChoiceList() const
	{   ASSERT(GetIncludeChoiceList());
		// ASSERTION-> // Did you check CGXStyle::GetInclude...? ->END
		return m_sChoiceList; }

GX_INLINE const CString& CGXStyle::GetChoiceListRef() const
	{   ASSERT(GetIncludeChoiceList());
		// ASSERTION-> // Did you check CGXStyle::GetInclude...? ->END
		return m_sChoiceList; }

GX_INLINE CGXStyle& CGXStyle::SetChoiceList(LPCTSTR s)
	{ m_sChoiceList = s; return CGXStyle::SetIncludeChoiceList(TRUE); }

GX_INLINE CGXStyle& CGXStyle::SetChoiceList(const CString& s)
	{ m_sChoiceList = s; return CGXStyle::SetIncludeChoiceList(TRUE); }

#ifdef _UNICODE

	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
GX_INLINE CGXStyle& CGXStyle::SetChoiceList(const char* s)
	{ m_sChoiceList = s; return CGXStyle::SetIncludeChoiceList(TRUE); }

#endif

// Enabled
GX_INLINE BOOL CGXStyle::GetIncludeEnabled() const
	{ return stylebits.enabled; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeEnabled(BOOL b)
	{ stylebits.enabled = (unsigned) b; return *this; }

GX_INLINE BOOL CGXStyle::GetEnabled() const
	{   ASSERT(GetIncludeEnabled());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return boolbits.m_bEnabled; }

GX_INLINE CGXStyle& CGXStyle::SetEnabled(BOOL b)
	{ boolbits.m_bEnabled = (BYTE) b; return CGXStyle::SetIncludeEnabled(TRUE); }

// TriState
GX_INLINE BOOL CGXStyle::GetIncludeTriState() const
	{ return stylebits.tristate; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeTriState(BOOL b)
	{ stylebits.tristate = (unsigned) b; return *this; }

GX_INLINE BOOL CGXStyle::GetTriState() const
	{   ASSERT(GetIncludeTriState());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return boolbits.m_bTriState; }

GX_INLINE CGXStyle& CGXStyle::SetTriState(BOOL b)
	{ boolbits.m_bTriState = (BYTE) b; return CGXStyle::SetIncludeTriState(TRUE); }

// Draw3dFrame
GX_INLINE BOOL CGXStyle::GetIncludeDraw3dFrame() const
	{ return stylebits.draw3dframe; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeDraw3dFrame(BOOL b)
	{ stylebits.draw3dframe = (unsigned) b; return *this; }

GX_INLINE GXDraw3dFrameType CGXStyle::GetDraw3dFrame() const
	{   ASSERT(GetIncludeDraw3dFrame());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return (GXDraw3dFrameType) boolbits.m_nDraw3dFrame; }

GX_INLINE CGXStyle& CGXStyle::SetDraw3dFrame(GXDraw3dFrameType t)
	{ boolbits.m_nDraw3dFrame = (BYTE) t; return CGXStyle::SetIncludeDraw3dFrame(TRUE); }

// ItemDataPtr
GX_INLINE BOOL CGXStyle::GetIncludeItemDataPtr() const
	{ return stylebits.itemdataptr; }

GX_INLINE CGXStyle& CGXStyle::SetIncludeItemDataPtr(BOOL b)
	{ stylebits.itemdataptr = (unsigned) b; return *this; }

GX_INLINE void* CGXStyle::GetItemDataPtr() const
	{   ASSERT(GetIncludeItemDataPtr());
		// ASSERTION-> Did you check CGXStyle::GetInclude...? ->END
		return m_pItemDataPtr; }

GX_INLINE CGXStyle& CGXStyle::SetItemDataPtr(void* pv)
	{ m_pItemDataPtr = pv; return CGXStyle::SetIncludeItemDataPtr(TRUE); }

// Borders
GX_INLINE CGXPen* CGXStyle::GetBorders() const
	{ return m_pPenArray; }

GX_INLINE DWORD CGXStyle::GetStyleBits() const
	{ return stylebits.GetPortable(); }

GX_INLINE const CGXStyle& CGXStyle::operator=(LPCTSTR s)
	{ SetValue(s); return *this; }

GX_INLINE void CGXStyle::GetUserAttribute(WORD nID, CString& s) const
{
	s = GetUserAttribute(nID);
}

GX_INLINE CGXStyle& CGXStyle::SetUserAttribute(WORD nID, const CString& s)
{
	return SetUserAttributePtr(nID, new CGXUserAttribute(s));
}

GX_INLINE CGXStyle& CGXStyle::SetUserAttribute(WORD nID, LPCTSTR pszValue)
{
	return SetUserAttributePtr(nID, new CGXUserAttribute(pszValue));
}

GX_INLINE CGXStyle& CGXStyle::SetUserAttribute(WORD nID, DWORD value)
{
	return SetUserAttributePtr(nID, new CGXUserAttribute(value));
}

GX_INLINE CGXStyle& CGXStyle::SetUserAttribute(WORD nID, LONG value)
{
	return SetUserAttributePtr(nID, new CGXUserAttribute(value));
}

GX_INLINE CGXStyle& CGXStyle::SetUserAttribute(WORD nID, double value)
{
	return SetUserAttributePtr(nID, new CGXUserAttribute(value));
}

GX_INLINE CGXStyle& CGXStyle::SetUserAttribute(WORD nID, GXBYTE8 value)
{
	return SetUserAttributePtr(nID, new CGXUserAttribute(value));
}

GX_INLINE const CGXUserAttributeMap* CGXStyle::GetUserAttributeMap() const
{
	return m_pmapUserAttributes;
}

class GRID_API CGXStylesMap;

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXStylesMap

// UserAttrInfo

GX_INLINE CGXStylesMap::UserAttrInfo::UserAttrInfo()
{
	pStyle = NULL;
}

GX_INLINE CGXStylesMap::UserAttrInfo::~UserAttrInfo()
{
	delete pStyle;
}

// BaseStyleInfo

GX_INLINE CGXStylesMap::BaseStyleInfo::BaseStyleInfo()
{
	pStyle = NULL;
}

GX_INLINE CGXStylesMap::BaseStyleInfo::~BaseStyleInfo()
{
	delete pStyle;
}

GX_INLINE void CGXStylesMap::AddUserAttribute(WORD nID, const CGXStyle& style)
{
	AddUserAttribute(nID, &style);
}

GX_INLINE LPCTSTR CGXStylesMap::GetStyleName(WORD wStyleId) const
{
	UINT nResourceId;

	return GetStyleName(wStyleId, nResourceId);
}

// Section

GX_INLINE void CGXStylesMap::SetSection(LPCTSTR pszSection)
	{ m_sSection = pszSection; }

GX_INLINE const CString& CGXStylesMap::GetSection() const
	{ return m_sSection; }


/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXStylePtrArray

GX_INLINE CGXStylePtrArray::CGXStylePtrArray()
	{ };

GX_INLINE CGXStylePtrArray::CGXStylePtrArray(const CGXStylePtrArray& other)
	{ operator=(other); };

GX_INLINE CGXStyle* CGXStylePtrArray::GetAt(int nIndex) const
	{ return (CGXStyle*) CPtrArray::GetAt(nIndex); }

GX_INLINE void CGXStylePtrArray::SetAt(int nIndex, CGXStyle* newElement)
	{ CPtrArray::SetAt(nIndex, newElement); }

	// Potentially growing the array
GX_INLINE void CGXStylePtrArray::SetAtGrow(int nIndex, CGXStyle* newElement)
	{ CPtrArray::SetAtGrow(nIndex, newElement); }

GX_INLINE int CGXStylePtrArray::Add(CGXStyle* newElement)
	{ return (int)CPtrArray::Add(newElement); }

	// overloaded operator helpers
GX_INLINE CGXStyle* CGXStylePtrArray::operator[](int nIndex) const
	{ return (CGXStyle*) CPtrArray::operator[](nIndex); }

GX_INLINE CGXStyle*& CGXStylePtrArray::operator[](int nIndex)
	{ return (CGXStyle*&) CPtrArray::operator[](nIndex); }

	// Operations that move elements around
GX_INLINE void CGXStylePtrArray::InsertAt(int nIndex, CGXStyle* newElement, int nCount)
	{ CPtrArray::InsertAt(nIndex, newElement, nCount); }

GX_INLINE void CGXStylePtrArray::InsertAt(int nStartIndex, CGXStylePtrArray* pNewArray)
	{ CPtrArray::InsertAt(nStartIndex, pNewArray); }

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXStylePtrArrayPtrArray

GX_INLINE CGXStylePtrArrayPtrArray::CGXStylePtrArrayPtrArray()
	{ };

GX_INLINE CGXStylePtrArrayPtrArray::CGXStylePtrArrayPtrArray(const CGXStylePtrArrayPtrArray& other)
	{ operator=(other); };

GX_INLINE CGXStylePtrArray* CGXStylePtrArrayPtrArray::GetAt(int nIndex) const
	{ return (CGXStylePtrArray*) CPtrArray::GetAt(nIndex); }

GX_INLINE void CGXStylePtrArrayPtrArray::SetAt(int nIndex, CGXStylePtrArray* newElement)
	{ CPtrArray::SetAt(nIndex, newElement); }

	// Potentially growing the array
GX_INLINE void CGXStylePtrArrayPtrArray::SetAtGrow(int nIndex, CGXStylePtrArray* newElement)
	{ CPtrArray::SetAtGrow(nIndex, newElement); }

GX_INLINE int CGXStylePtrArrayPtrArray::Add(CGXStylePtrArray* newElement)
	{ return (int)CPtrArray::Add(newElement); }

	// overloaded operator helpers
GX_INLINE CGXStylePtrArray* CGXStylePtrArrayPtrArray::operator[](int nIndex) const
	{ return (CGXStylePtrArray*) CPtrArray::operator[](nIndex); }

GX_INLINE CGXStylePtrArray*& CGXStylePtrArrayPtrArray::operator[](int nIndex)
	{ return (CGXStylePtrArray*&) CPtrArray::operator[](nIndex); }

	// Operations that move elements around
GX_INLINE void CGXStylePtrArrayPtrArray::InsertAt(int nIndex, CGXStylePtrArray* newElement, int nCount)
	{ CPtrArray::InsertAt(nIndex, newElement, nCount); }

GX_INLINE void CGXStylePtrArrayPtrArray::InsertAt(int nStartIndex, CGXStylePtrArrayPtrArray* pNewArray)
	{ CPtrArray::InsertAt(nStartIndex, pNewArray); }

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXData

GX_INLINE BOOL CGXData::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, GXModifyType mt, int nType)
{
	return StoreStyleRowCol(nRow, nCol, &style, mt, nType);
}

#endif // GX_INLINE
