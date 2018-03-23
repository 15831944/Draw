///////////////////////////////////////////////////////////////////////////////
// Gxstyles.h
//

#ifndef _GXSTYLES_H_
#define _GXSTYLES_H_

#ifndef _GXCOLL_H_
#include "gxcoll.h"
#endif

#ifndef _GXSTATE_H_
#include "gxstate.h"
#endif

// // #include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA	GX_DATAEXT
#endif

// header file

class CGXStylesMap;

// enums

enum GXBorderType {
		gxBorderAll = -1,
		gxBorderLeft = 0,
		gxBorderRight = 1,
		gxBorderTop = 2,
		gxBorderBottom = 3
	};

enum GXDraw3dFrameType {
		gxFrameNormal = 0,
		gxFrameRaised = 1,
		gxFrameInset = 2
	};

// Automatic alignment based on format
#define GX_JUST_AUTO	3

/* Cell Formats */

#define GX_FMT_DEFAULT		0
#define GX_FMT_FLOAT		1
#define GX_FMT_FIXED		2
#define GX_FMT_GEN			3
#define GX_FMT_DOLLARS		4
#define GX_FMT_COMMA		5
#define GX_FMT_HEX			6
#define GX_FMT_LOGIC		7
#define GX_FMT_DAY_MONTH_YEAR	8
#define GX_FMT_DAY_MONTH		9
#define GX_FMT_MONTH_YEAR		10
#define GX_FMT_DATE			11
#define GX_FMT_HIDDEN		12
#define GX_FMT_TIME			13
#define GX_FMT_PERCENT		14
#define GX_FMT_TEXT			15
#define GX_FMT_INTL_DATE	16
#define GX_FMT_ISO8061_DATE	17
#define GX_FMT_DATETIME		18
#define GX_FMT_USER1		19
#define GX_FMT_USER2		20
#define GX_FMT_USER3		21
#define GX_FMT_USER4		22

#define GX_FMT_FIXED_PARENS				23
#define GX_FMT_MIXED_FRACTIONS    		24
#define GX_FMT_TIME_HM_AMPM				25
#define GX_FMT_TIME_HMS_AMPM			26
#define GX_FMT_TIME_HM					27
#define GX_FMT_NUMLOCALE				28
#define GX_FMT_MAXVAL					28

#define GX_CHECK_FORMAT(X)		((X)>=0 && (X)<=GX_FMT_MAXVAL)
#define GX_CHECK_PLACES(X)		((X)>=0 && (X)<=15)

#define GX_IS_DATE_FORMAT(X)	((X)==GX_FMT_DAY_MONTH_YEAR || \
				 (X)==GX_FMT_DAY_MONTH || \
				 (X)==GX_FMT_MONTH_YEAR || \
				 (X)==GX_FMT_DATE || \
				 (X)==GX_FMT_DATETIME)

#define GX_IS_TIME_FORMAT(X)	((X)==GX_FMT_TIME)

// Value Types
#define GX_VT_STRING		0
#define GX_VT_NUMERIC		1
#define GX_VT_EXPRESSION	2
#define GX_VT_ERROR			3

// Support for system colors

#define GXSYSCOLOR(n) ( ((DWORD)(BYTE)(254-n))<<24 | GXGetSysData()->GetSysColor(n) )
#define GXISSYSCOLOR(rgbclr)( (BYTE)((rgbclr)>>24) > 64 && (BYTE)((rgbclr)>>24) <= 254 )
#define GXGETSYSCOLOR(rgbclr) ( GXISSYSCOLOR(rgbclr) ? 254-(BYTE)((rgbclr)>>24) : 0 )
#define GXGETCOLOR(rgbclr)( GXISSYSCOLOR(rgbclr) ? GXGetSysData()->GetSysColor(254-(int)((rgbclr)>>24)) : rgbclr)

// Support for brush and pen colors with separate hi-byte (0 - 24-Bit RGB, 1 - Palette Index, 2 - Palette RGB, 3 - System Color)
#define GXGETCOLOR2(n1, n2)		( (COLORREF) ((n1 == 3) ? GXGetSysData()->GetSysColor((int) n2) : (n1 << 24 | n2) ))
#define GXGETCOLORNA2(n1, n2)	( (COLORREF) ((n1 == 3) ? GXSYSCOLOR((int) n2) : (n1 << 24 | n2) ))
// GXCOLOR1 - Hi-Byte
#define GXCOLOR1(rgbclr)		( GXISSYSCOLOR(rgbclr) ? 3 : (BYTE)((rgbclr)>>24))
// GXCOLOR2 - Color (3 Bytes)
#define GXCOLOR2(rgbclr)		( GXISSYSCOLOR(rgbclr) ? GXGETSYSCOLOR(rgbclr) : ((rgbclr)<<8)>>8 )

class CGXRange;
class CGXFont;


struct CGXFontInfo
{
	GRID_API CGXFontInfo();

	TCHAR		lfFaceName[LF_FACESIZE*2+3];// 67 Byte: Facename (Script)
	BYTE		nFaceLen;
	BYTE		lfPitchAndFamily;
	BYTE		nCharSet;
	unsigned	nFontIndex : 10; // max. 1024 fonts available (see GX_FONT_STATE::m_apUsedFonts)
	unsigned	nFontType: 3;// TRUETYPE_FONTTYPE, DEVICE_FONTTYPE, RASTER_FONTTYPE
	unsigned	nInstalled : 1;
	unsigned	nDefaultCharset : 1;
};

#define GX_DEFAULT_FACENAME		1023
#define GX_DEFAULT_ORIENTATION	511
#define GX_DEFAULT_WEIGHT		15
#define GX_DEFAULT_SIZE			0

class CGXFont: public CObject
{
	GRID_DECLARE_SERIAL(CGXFont)

public:
	// operations
	//@cmember
	// CGXFont constructor.
	GRID_API CGXFont();
	GRID_API CGXFont(LPCTSTR pszDescription);
	GRID_API CGXFont(const LOGFONT& lf);
	GRID_API CGXFont(const CGXFont& font);

	//@cmember
	// CGXFont copy constructor.
	GRID_API const CGXFont& operator=(const CGXFont& font);
	GRID_API const CGXFont& operator=(const LOGFONT& lf);

	// LogFont
	//@cmember
	// Get log font reference.
	GRID_API const LOGFONT& GetLogFontRef() const;
	//@cmember
	// Get log font.
	GRID_API LOGFONT GetLogFont(int nZoom = 100) const;
	//@cmember
	// Set log font.
	GRID_API CGXFont& SetLogFont(const LOGFONT& lf);
	//@cmember
	// LOGFONT operator.
	GRID_API operator LOGFONT() const;
	GRID_API operator const LOGFONT*() const;
	//@cmember
	// CGXFont equal operator.
	GRID_API BOOL operator==(const CGXFont& font) const;
	//@cmember
	// CGXFont not equal operator.
	GRID_API BOOL operator!=(const CGXFont& font) const;

	//@cmember
	// Set default.
	GRID_API CGXFont& SetDefault();
	//@cmember
	// Change font.
	GRID_API CGXFont& ChangeFont(const CGXFont& font, GXModifyType mt);
	//@cmember
	// Is subset of a font?
	GRID_API BOOL IsSubSet(const CGXFont& fontSubSet) const; // is font subset from this
	//@cmember
	// Serialize.
	GRID_API void Serialize(CArchive &ar);
	//@cmember
	// Write profile.
	GRID_API void WriteProfile(LPCTSTR pszSection, LPCTSTR pszEntry) const;
	//@cmember
	// Read profile.
	GRID_API BOOL ReadProfile(LPCTSTR pszSection, LPCTSTR pszEntry);
	//@cmember
	// Set description.
	GRID_API CGXFont& SetDescription(LPCTSTR szDescription);
	//@cmember
	// Get description.
	GRID_API CString GetDescription() const;
	GRID_API void GetDescription(LPTSTR s) const;
	//@cmember
	// Is empty font?
	GRID_API BOOL IsEmptyFont() const;
	//@cmember
	// Get font key.
	GRID_API GXBYTE8 GetFontKey() const;
	//@cmember
	// Is equal?
	GRID_API BOOL IsEqual(const CGXFont& font) const;
	//@cmember
	// CGXFont destructor.
	GRID_API virtual ~CGXFont();

protected:
	GRID_API void Init();
	//@cmember
	// LogFont structure (with reference count)
	GRID_API CGXFontData* GetData(GXBYTE8 key) const;
	GRID_API CGXFontData* GetData() const;
	GRID_API void Release(GXBYTE8 key);
	GRID_API void Release();
	GRID_API void InitLogFont(LOGFONT& lf) const;

	//@cmember
	// static helper functions
	GRID_API static unsigned AFXAPI Size_lf2ui(double lfSize);
	GRID_API static double AFXAPI Size_ui2lf(unsigned nSize);
	GRID_API static unsigned AFXAPI Orientation_lf2ui(LONG lfOrientation);
	GRID_API static LONG AFXAPI Orientation_ui2lf(unsigned nOrientation);
	GRID_API static unsigned AFXAPI Weight_lf2ui(LONG lfWeight);
	GRID_API static LONG AFXAPI Weight_ui2lf(unsigned nWeight);
	GRID_API static unsigned AFXAPI FaceName_str2ui(LPCTSTR lfFaceName);
	GRID_API static LPCTSTR AFXAPI FaceName_ui2str(unsigned nFaceName);

// Attributes
protected:
	union
	{
		struct
		{
			unsigned fontdata : 1;// TRUE if associated CGXFontData exists (and should be freed)

			// include bits
			// weight, size, facename see below
			unsigned italic : 1;
			unsigned underline: 1;
			unsigned strikeout: 1;

			// settings
			unsigned nWeight: 4;	// 15 - not included, weight stored in 100 steps (0-10)
			unsigned nSize: 10;	// 0 - not included
			unsigned nItalic: 1;
			unsigned nUnderline : 1;
			unsigned nStrikeOut : 1;
			unsigned nOrientation : 9;// 511 - not included, orientation stored in 15 degree steps (0-24)
			unsigned nFaceName:10;	// 1023 - not included, index to array with face names
			//----
			// Total 36 Bits - same size as a GXBYTE8
		} fontbits;

		GXBYTE8 m_b8Value;
	};

// Access member functions
public:
	//@cmember
	// Weight.
	GRID_API BOOL GetIncludeWeight() const;
	GRID_API CGXFont& SetIncludeWeight(BOOL b);
	GRID_API LONG GetWeight() const;
	GRID_API CGXFont& SetWeight(LONG nWeight);
	//@cmember
	// Bold.
	GRID_API BOOL GetBold() const;
	GRID_API CGXFont& SetBold(BOOL b);
	//@cmember
	// Italic
	GRID_API BOOL GetIncludeItalic() const;
	GRID_API CGXFont& SetIncludeItalic(BOOL b);
	GRID_API BOOL GetItalic() const;
	GRID_API CGXFont& SetItalic(BOOL b);
	//@cmember
	// Underline
	GRID_API BOOL GetIncludeUnderline() const;
	GRID_API CGXFont& SetIncludeUnderline(BOOL b);
	GRID_API BOOL GetUnderline() const;
	GRID_API CGXFont& SetUnderline(BOOL b);
	//@cmember
	// StrikeOut
	GRID_API BOOL GetIncludeStrikeOut() const;
	GRID_API CGXFont& SetIncludeStrikeOut(BOOL b);
	GRID_API BOOL GetStrikeOut() const;
	GRID_API CGXFont& SetStrikeOut(BOOL b);
	//@cmember
	// Size
	GRID_API BOOL GetIncludeSize() const;
	GRID_API CGXFont& SetIncludeSize(BOOL b);
	GRID_API double GetSize() const;
	GRID_API CGXFont& SetSize(double size);
	//@cmember
	// Orientation
	GRID_API BOOL GetIncludeOrientation() const;
	GRID_API CGXFont& SetIncludeOrientation(BOOL b);
	GRID_API LONG GetOrientation() const;
	GRID_API CGXFont& SetOrientation(LONG Orientation);
	//@cmember
	// FaceName
	GRID_API BOOL GetIncludeFaceName() const;
	GRID_API CGXFont& SetIncludeFaceName(BOOL b);
	GRID_API LPCTSTR GetFaceName() const;
	GRID_API CGXFont& SetFaceName(LPCTSTR facename);
	GRID_API unsigned GetFaceNameId() const;
	GRID_API CGXFont& SetFaceNameId(unsigned nFaceName);

public:
	// constants
	GRID_API static LPCTSTR szArial;

	friend class CGXStyleSerializeImp;
	friend class CGXFontFTR;
};

GRID_API CArchive& AFXAPI operator <<(CArchive& ar, const CGXFont& font);
GRID_API CArchive& AFXAPI operator >>(CArchive& ar, CGXFont& font);

// Brush

// Patterns (used in brushes)
GRID_API const CBitmap* AFXAPI GXGetPatternBitmap(int n);

struct CGXBrush
{
	GRID_API static LPCTSTR szBrushFormat;

// Attributes
	unsigned lbHatch : 3;
	//unsigned notused : 1;
	unsigned long lbColor1: 2;// 0 - 24-Bit RGB, 1 - Palette Index, 2 - Palette RGB, 3 - System Color
	unsigned long lbBkColor1: 2;// 0 - 24-Bit RGB, 1 - Palette Index, 2 - Palette RGB, 3 - System Color
	unsigned long lbColor2: 24;
	unsigned long lbBkColor2: 24;
	// Increased number of bits for lbPattern, remove notused.
	unsigned lbPattern : 7;
	unsigned lbStyle : 2;
	//----
	// Total64 Bits
	//@cmember
	// CGXBrush construction.
	GRID_API CGXBrush();
	GRID_API CGXBrush(const LOGBRUSH& logbrush);
	GRID_API CGXBrush(const CGXBrush& brush);
	GRID_API CGXBrush(LPCTSTR pszDescription);
	GRID_API CGXBrush(UINT style, COLORREF color, LONG hatch);
	//@cmember
	// Copying.
	GRID_API CGXBrush& operator=(const CGXBrush& brush);
	GRID_API operator tagLOGBRUSH() const;
	GRID_API operator const tagLOGBRUSH*() const;
	//@cmember
	// Comparing.
	GRID_API BOOL operator==(const CGXBrush& brush) const;
	GRID_API BOOL operator!=(const CGXBrush& brush) const;
	GRID_API GXBYTE8 GetBrushKey() const;
	//@cmember
	// Attributes.
	GRID_API UINT GetStyle() const;
	GRID_API CGXBrush& SetStyle(UINT style);
	GRID_API COLORREF GetColor() const;
	GRID_API COLORREF GetColorNA() const;
	GRID_API CGXBrush& SetColor(COLORREF color);
	GRID_API LONG GetHatch() const;
	GRID_API CGXBrush& SetHatch(LONG hatch);
	GRID_API int GetPattern() const;
	GRID_API CGXBrush& SetPattern(int nPattern);
	GRID_API COLORREF GetBkColor() const;
	GRID_API COLORREF GetBkColorNA() const;
	GRID_API CGXBrush& SetBkColor(COLORREF color);
	//@cmember
	// Description.
	GRID_API CGXBrush& SetDescription(LPCTSTR szDescription);
	GRID_API CString GetDescription() const;
	GRID_API void GetDescription(LPTSTR s) const;
};

GRID_API CArchive& AFXAPI operator <<(CArchive& ar, const CGXBrush& lb);
GRID_API CArchive& AFXAPI operator >>(CArchive& ar, CGXBrush& lb);

// Pen

#define GX_PS_DEFAULT 7

struct CGXPen
{
	GRID_API static LPCTSTR szPenFormat;

// Attributes
	unsigned lopnStyle : 3;
	unsigned lopnWidth : 16;
	unsigned long lopnColor1: 2;
	unsigned long lopnColor2: 24;
	// Total ----
	// 45 Bits -> same size as a GXBTYE8
	// not included -> lopnstyle = 7
	//@cmember
	// Construction.
	GRID_API CGXPen();
	GRID_API CGXPen(const tagLOGPEN& logpen);
	GRID_API CGXPen(const CGXPen& pen);
	GRID_API CGXPen(LPCTSTR szDescription);
	GRID_API CGXPen(UINT style, int width, COLORREF color);
	//@cmember
	// Assignment.
	GRID_API CGXPen& operator=(const tagLOGPEN& logpen);
	GRID_API CGXPen& operator=(const CGXPen& pen);
	GRID_API operator tagLOGPEN() const;
	GRID_API operator tagLOGPEN*() const;
	//@cmember
	// Comparison.
	GRID_API BOOL operator==(const CGXPen& pen) const;
	GRID_API BOOL operator!=(const CGXPen& pen) const;
	GRID_API GXBYTE8 GetPenKey() const;
	//@cmember
	// Attributes.
	GRID_API CGXPen& SetInclude(BOOL b);
	GRID_API BOOL GetInclude() const;
	GRID_API UINT GetStyle() const;
	GRID_API CGXPen& SetStyle(UINT style);
	GRID_API int GetWidth() const;
	GRID_API CGXPen& SetWidth(int width);
	GRID_API COLORREF GetColor() const;
	GRID_API COLORREF GetColorNA() const;
	GRID_API CGXPen& SetColor(COLORREF color);
	//@cmember
	// Description.
	GRID_API CGXPen& SetDescription(LPCTSTR szDescription);
	GRID_API CString GetDescription() const;
	GRID_API void GetDescription(LPTSTR s) const;
	//@cmember
	// Optimize drawing for vertical and horizontal lines.
	GRID_API BOOL CreateCompatibleBrush(CGXBrush& br, const CGXBrush& brInterior, BOOL bHorzOrVert, BOOL bBlackWhite) const;
};

GRID_API CArchive& AFXAPI operator <<(CArchive& ar, const CGXPen& lp);
GRID_API CArchive& AFXAPI operator >>(CArchive& ar, CGXPen& lp);

// simple wrapper class for using strings directly from a resource id.

class CGXResourceString: public CString
{
public:
	GRID_API CGXResourceString(UINT nID);
};


/////////////////////////////////////////////////////////////////////
// abstract CGXAbstractUserAttribute class

//@doc CGXAbstractUserAttribute
//@class
//By deriving from <c CGXAbstractUserAttribute> you can store binary data into any <c CGXStyle> object. 
//Using a <c CGXAbstractUserAttribute> will be much more convinient for you than using 
//<f SetItemDataPtr> because you don't have to worry about deleting the objects any more.<nl>
// 
//Objective Grid offers a default <c CGXUserAttribute> class that provides support for 
//numbers and strings. <mf CGXStyle::SetUserAttribute> instantiates this default <c CGXUserAttribute> 
//class for strings and numbers automatically which makes Objective Grid 6.0 fully source code
//compatible with the previous Objective Grid versions.<nl>
//
//Using <c CGXUserAttribute> decreases the memory usage of user attributes a lot. 
//Numbers will only be stored as doubles and no string needs to be allocated any more. 
//If you pass a string to <c CGXStyle::SetUserAttribute> 
//the value will be parsed and if it is a plain number it will be stored as a double. <nl>
//
//And it increases the flexibility. It is much easier now to add new attributes to 
//<c CGXStyle> and you don't have to subclass <c CGXStyle> any more. 
//<c GXAbstractUserAttribute> comes with full support for serialization 
//and reading or writing profile or registry. User attributes can also be modified 
//by the user via the <c CGXUserAttributePage> (if wished).<nl>
class CGXAbstractUserAttribute: public CObject
{
	GRID_DECLARE_SERIAL(CGXAbstractUserAttribute);

public:
	//@access Construction
	//@cmember
	//Costructs a CGXAbstractUserAttribute object
	GRID_API CGXAbstractUserAttribute();

	GRID_API virtual ~CGXAbstractUserAttribute();

	//@access Profile, Registry and User Attribute Page

	// Change value, update the grid, generate undo info
	//@cmember SetValue is called with a CString and changes 
	//the value of your attribute. Override this method if you want to support 
	//reading values from registry or the user attribute page. 
	//In your override you should interprete the CString and convert it 
	//to your binary representation of the value.
	GRID_API virtual CGXAbstractUserAttribute& SetValue(const CString& strValue);
	//@cmember SetValue is called with a CString and changes 
	//the value of your attribute. Override this method if you want to support 
	//reading values from registry or the user attribute page. 
	//In your override you should interprete the CString and convert it 
	//to your binary representation of the value.
	GRID_API virtual CGXAbstractUserAttribute& SetValue(LPCTSTR pszValue);

	// Simply return the value
	//@cmember GetValue returns a CString with the textual 
	//representation of the binary stored in the user attribute. 
	//Override this method if you want to support writing values to 
	//registry or the user attribute page. 
	GRID_API virtual const CString& GetValue() const;
	//@cmember GetDWordValue returns a DWORD value.
	// By default, the method returns (DWORD) atol(GetValue()); 
	GRID_API virtual DWORD GetDWordValue() const;
	//@cmember GetLongValue returns a LONG value. 
	// By default, the method returns atol(GetValue()); 
	GRID_API virtual LONG GetLongValue() const;
	//@cmember GetDoubleValue returns a double value. 
	//By default, the method returns atof(GetValue()); 
	GRID_API virtual double GetDoubleValue() const;

	// Copying attribute (e.g. from one style object to another)
	//@access Overridables
	//@cmember
	//Clones this object. If you derive from <c CGXAbstractUserAttribute>
	//you have to provide this method.
	GRID_API virtual CGXAbstractUserAttribute* Clone() const;

	//@access Serialization
	//@cmember
	//Override this method if you want to support serialization 
	//and clipboard operations for this attribute class.
	GRID_API virtual void Serialize(CArchive& ar);

	// Comparision
	// @access Operations
	// @cmember Compares two user attributes. 
	// The default implementation will simply compare the values returned by
	// GetValue for both attributes to be compared.
	// Override this method if you need a more specialized behavior for your user attribute.
	GRID_API virtual BOOL IsEqual(const CGXAbstractUserAttribute& p) const; // (TRUE if equal)

	GRID_API operator LPCTSTR() const;

        //@cmember Checks if the value is empty. By default it simply checks 
	//if GetValue returns an empty string. 
	//Override this method if you need a more specialized behavior for your user attribute.
	GRID_API virtual BOOL IsEmpty() const;

private:
	// Disable the copy constructor and assignment by default so you will get
	//   compiler errors instead of unexpected behaviour if you pass objects
	//   by value or assign objects.
	CGXAbstractUserAttribute(const CGXAbstractUserAttribute& src);  // no implementation
	void operator=(const CGXAbstractUserAttribute& src);            // no implementation

	// Note: The correct way to copy user attributes is to call Clone()

public:
	WORD m_nId;
	GRID_API static CString m_strValueCache;	// Value to be used for converting into a string in GetValue
};

/////////////////////////////////////////////////////////////////////
// CGXUserAttribute class for C++ datatypes

class CGXUserAttribute: public CGXAbstractUserAttribute
{
	GRID_DECLARE_SERIAL(CGXUserAttribute);

public:
	//@cmember
	// Attributes.
	GRID_API CGXUserAttribute();
	GRID_API CGXUserAttribute(DWORD value);
	GRID_API CGXUserAttribute(LONG value);
	GRID_API CGXUserAttribute(const CString& value);
	GRID_API CGXUserAttribute(LPCTSTR value);
	GRID_API CGXUserAttribute(double value);
	GRID_API CGXUserAttribute(GXBYTE8 value);
	GRID_API CGXUserAttribute(const CGXUserAttribute& p);
	GRID_API virtual ~CGXUserAttribute();

	GRID_API virtual CGXAbstractUserAttribute& SetValue(LPCTSTR pszValue);
	GRID_API virtual const CString& GetValue() const;
	GRID_API virtual DWORD GetDWordValue() const;
	GRID_API virtual LONG GetLongValue() const;
	GRID_API virtual double GetDoubleValue() const;
	GRID_API virtual void Serialize(CArchive& ar);

	// Copying attribute (e.g. from one style object to another)
	GRID_API virtual CGXAbstractUserAttribute* Clone() const;

	// Comparision
	GRID_API virtual BOOL IsEqual(const CGXAbstractUserAttribute& p) const; // (TRUE if equal)

protected:
	typedef enum
	{
		vtEmpty,
		vtDWord,
		vtLong,
		vtShortString,
		vtString,
		vtDouble,
		vtByte8
	} ValueType;

	ValueType m_vtType;
	union
	{
		DWORD dwValue;
		LONG lValue;
		LPTSTR pszValue;
		TCHAR szShortString[8/sizeof(TCHAR)];
		double dValue;
		GXBYTE8 b8Value;
	} m_value;

	friend class CGXUserAttributeFTR;
};


/////////////////////////////////////////////////////////////////////
// CGXEllipseUserAttribute class for gxEllipseType
// used by CGXDrawingAndFormatting for ellipse setting

enum gxEllipseType
{
	gxNoEllipse			= 0, // no ellipse...the default setting
	gxDotEllipse		= 1, // Dotted ellipse ...
	gxPoundEllipse		= 2, // Pound ellipses ####
};


class CGXEllipseUserAttribute: public CGXAbstractUserAttribute
{
	GRID_DECLARE_SERIAL(CGXEllipseUserAttribute);
public:
	//@cmember
	// Attributes.
	GRID_API CGXEllipseUserAttribute();
	GRID_API CGXEllipseUserAttribute(gxEllipseType type);
	GRID_API CGXEllipseUserAttribute(const CGXEllipseUserAttribute& p);

	GRID_API virtual ~CGXEllipseUserAttribute();

	GRID_API virtual CGXAbstractUserAttribute& SetValue(const CString& strValue);
	GRID_API virtual CGXAbstractUserAttribute& SetValue(LPCTSTR pszValue);
	//@cmember
	// This is the interface to be used.
	GRID_API virtual CGXAbstractUserAttribute& SetEllipseValue(gxEllipseType type);

	//@cmember
	// Return the value.
	GRID_API virtual const CString& GetValue() const;
	GRID_API virtual DWORD GetDWordValue() const;
	GRID_API virtual LONG GetLongValue() const;
	GRID_API virtual double GetDoubleValue() const;
	//@cmember
	// Get ellipse value.
	GRID_API virtual gxEllipseType GetEllipseValue() const;
	//@cmember
	// Copying attribute (e.g. from one style object to another)
	GRID_API virtual CGXAbstractUserAttribute* Clone() const;

	GRID_API virtual void Serialize(CArchive& ar);
	//@cmember
	// Comparision.
	GRID_API virtual BOOL IsEqual(const CGXAbstractUserAttribute& p) const; // (TRUE if equal)
	//@cmember
	// Is empty?
	GRID_API virtual BOOL IsEmpty() const;

protected:
	gxEllipseType m_gxEllipseType;

	friend class CGXEllipseUserAttributeFTR;
};


/////////////////////////////////////////////////////////////////////
// CGXUserAttributeMap

class CGXUserAttributeMap: public CObArray
{
	GRID_DECLARE_SERIAL(CGXUserAttributeMap)
public:
	//@cmember
	// Construction.
	GRID_API CGXUserAttributeMap();
	GRID_API ~CGXUserAttributeMap();
	//@cmember
	// Empty.
	GRID_API void Empty();
	GRID_API BOOL IsEmpty() const;
	//@cmember
	// Attributes (each CGXUserAttributeMap always holds its own
	// attribute objects on the heap).
	GRID_API void SetAttribute(WORD nID, const CGXAbstractUserAttribute& value);
	GRID_API void SetAttributePtr(WORD nID, CGXAbstractUserAttribute* pValue);
	GRID_API void DeleteAttribute(WORD nID);
	GRID_API const CGXAbstractUserAttribute* GetAttribute(WORD nID) const;
	//@cmember
	// Change map.
	GRID_API void ChangeMap(const CGXUserAttributeMap* pSrc, GXModifyType mt);

	GRID_API int FindAttribute(WORD nID) const;
	GRID_API void Sort();
	//@cmember
	// Operations
	GRID_API void WriteProfile(LPCTSTR pszSection) const;
	GRID_API BOOL ReadProfile(LPCTSTR pszSection);
	GRID_API void Serialize(CArchive& ar);
	//@cmember
	// compatibility with OG 5.
	GRID_API void AppendOG5Map(CGXCollMapDWordToString* pSrc);
};


// cell style

class CGXStyle : public CObject
{
	GRID_DECLARE_SERIAL(CGXStyle)

public:
	//@cmember
	// Operations.
	GRID_API CGXStyle();
	GRID_API CGXStyle(const CGXStyle& p);
	GRID_API CGXStyle(LPCTSTR s);

	GRID_API virtual ~CGXStyle();
	//@cmember
	// Clone.
	GRID_API virtual CGXStyle* Clone() const;// create a new style with "new CGXStyle(*this);"
	//@cmember
	// Operators.
	GRID_API virtual const CGXStyle& operator=(const CGXStyle& p);
	GRID_API virtual const CGXStyle& operator=(LPCTSTR s);

	GRID_API virtual CGXStyle& SetDefault();
	//@cmember
	// Is subset?
	GRID_API virtual BOOL IsSubSet(const CGXStyle& styleSubSet) const; // is styleSubSet subset from this

	GRID_API virtual void Serialize(CArchive& ar);
	GRID_API virtual void Serialize(CArchive& ar, const CGXStylesMap* pStylesMap);

	GRID_API virtual void WriteProfile(LPCTSTR pszSection, const CGXStylesMap* pStylesMap) const;
	GRID_API virtual BOOL ReadProfile(LPCTSTR pszSection, const CGXStylesMap* pStylesMap);

	GRID_API virtual void LoadBaseStyle(const CGXStylesMap& stylesmap);
	GRID_API virtual void ChangeStyle(const CGXStyle& p, GXModifyType mt);

#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

	GRID_API virtual void Free();

	GRID_API static void AFXAPI ImplementCompareSubset();
	GRID_API static void AFXAPI ImplementSerialize();
	GRID_API static void AFXAPI ImplementSerializeOG5Compatible();
	GRID_API static void AFXAPI ImplementProfile();

protected:
	GRID_API void ConstructStyle();

// Attributes
public:

	struct STYLEBITS
	{
         // Attributes
		unsigned horzalign: 1;
		unsigned vertalign: 1;
		unsigned readonly : 1;
		unsigned control: 1;
		unsigned interior : 1;
		unsigned textcolor: 1;
		unsigned wraptext : 1;
		unsigned allowenter : 1;
		unsigned borders: 1;
		unsigned font : 1;
		unsigned value: 1;
		unsigned choicelist : 1;
		unsigned vertscroll : 1;
		unsigned maxlength: 1;
		unsigned basestyle: 1;
		unsigned enabled: 1;
		unsigned tristate : 1;
		unsigned draw3dframe: 1;
		unsigned userattr : 1;
		unsigned autosize : 1;
		unsigned itemdataptr: 1;
		unsigned floodcell: 1;
		unsigned floatcell: 1;
		unsigned mergecell: 1;
		unsigned format:1;
		unsigned places:1;
				//24 Bits
		//@cmember
        // Access member functions.
		GRID_API DWORD GetPortable() const;
		GRID_API void SetPortable(DWORD dw);
		GRID_API STYLEBITS(DWORD dw = 0);
		GRID_API DWORD GetNoPortableBits() const;
        GRID_API void SetNoPortableBits(DWORD dw);
        GRID_API BOOL NoPortableIsEmptyBits() const;
	};

protected:
	STYLEBITS	stylebits;// 4 Byte

	WORD		m_nMaxLength; // 2 Byte

	CGXBrush	m_lbInterior; // 8 Byte

	WORD		m_nControl; // 2 byte: edit, text, combobox, ...

	struct BOOLS
	{
		unsigned m_nDraw3dFrame : 2;
		unsigned m_bReadOnly: 1;
		unsigned m_bVertScroll: 1;
		unsigned m_bWrapText: 1;
		unsigned m_bAllowEnter: 1;
		unsigned m_bEnabled : 1;
		unsigned m_bTriState: 1;
		unsigned m_bAutoSize: 1;
		unsigned m_bFloodCell : 1;
		unsigned m_bFloatCell : 1;
		unsigned m_nMergeCell : 3;
		unsigned m_nHorizontalAlignment : 2;
		unsigned m_nVerticalAlignment : 2;
		unsigned long m_rgbTextColor1 : 2; // Textcolor
		unsigned m_nValueType : 3;
		unsigned long m_rgbTextColor2 : 24; // Textcolor
		unsigned m_wBaseStyleId : 8;// derive from another style
		unsigned m_nFormat : 5;  // format
		unsigned m_nPlaces : 4;  // precision
		// 64 Bits

	} boolbits; // 8 Byte

	//@cmember
	// pointer to array with borders
	CGXPen* m_pPenArray;	// 4 byte
		
	//@cmember
	// Pointer to font structure.
	CGXFont* m_pFont;	// 4 byte
		
	//@cmember
	// String value.
	CString m_sValue;// 4 byte
	
	//@cmember
	// Used for DropDown-Lists, Items are separated with newline.
	CString m_sChoiceList;	// 4 byte
		
	//@cmember
	// The programmer can use extra attributes for derived CGXControls
	// key is an String-Resource-Id, value is a CGXAbstractUserAttribute.
	CGXUserAttributeMap*	m_pmapUserAttributes;	// 4 byte
		
	//@cmember
	// Item data pointer.
	void* m_pItemDataPtr;	// 4 byte
		
	// Total = 50 byte for empty style object
	//         + heap allocations (choice list, value string, user attributes, pen array 4x4Byte)

// Access member functions
public:
	//@cmember
	// Horizontal Alignment.
	GRID_API BOOL GetIncludeHorizontalAlignment() const;
	GRID_API CGXStyle& SetIncludeHorizontalAlignment(BOOL b);
	GRID_API DWORD GetHorizontalAlignment() const;
	GRID_API CGXStyle& SetHorizontalAlignment(DWORD dwAlign);
	//@cmember
	// Vertical Alignment.
	GRID_API BOOL GetIncludeVerticalAlignment() const;
	GRID_API CGXStyle& SetIncludeVerticalAlignment(BOOL b);
	GRID_API DWORD GetVerticalAlignment() const;
	GRID_API CGXStyle& SetVerticalAlignment(DWORD dwAlign);
	//@cmember
	// Readonly.
	GRID_API BOOL GetIncludeReadOnly() const;
	GRID_API CGXStyle& SetIncludeReadOnly(BOOL b);
	GRID_API BOOL GetReadOnly() const;
	GRID_API CGXStyle& SetReadOnly(BOOL b);
	//@cmember
	// Control.
	GRID_API BOOL GetIncludeControl() const;
	GRID_API CGXStyle& SetIncludeControl(BOOL b);
	GRID_API WORD GetControl() const;
	GRID_API CGXStyle& SetControl(WORD nControl);
	//@cmember
	// MaxLength.
	GRID_API BOOL GetIncludeMaxLength() const;
	GRID_API CGXStyle& SetIncludeMaxLength(BOOL b);
	GRID_API WORD GetMaxLength() const;
	GRID_API CGXStyle& SetMaxLength(WORD nMaxLength);
	//@cmember
	// VertScrollBar.
	GRID_API BOOL GetIncludeVertScrollBar() const;
	GRID_API CGXStyle& SetIncludeVertScrollBar(BOOL b);
	GRID_API BOOL GetVertScrollBar() const;
	GRID_API CGXStyle& SetVertScrollBar(BOOL b);
	//@cmember
	// Interior.
	GRID_API BOOL GetIncludeInterior() const;
	GRID_API CGXStyle& SetIncludeInterior(BOOL b);
	GRID_API CGXBrush GetInterior() const;
	GRID_API const CGXBrush& GetInteriorRef() const;
	GRID_API CGXStyle& SetInterior(const CGXBrush& lb);
	GRID_API CGXStyle& SetInterior(COLORREF rgbColor);
	//@cmember
	// Borders.
	GRID_API BOOL GetIncludeBorders() const;
	GRID_API CGXStyle& SetIncludeBorders(BOOL b);
	GRID_API CGXPen GetBorders(GXBorderType border) const;
	GRID_API const CGXPen& GetBordersRef(GXBorderType border) const;
	GRID_API CGXStyle& SetBorders(GXBorderType border, const CGXPen& pen);
	GRID_API BOOL GetIncludeBorders(GXBorderType border) const;
	GRID_API CGXStyle& SetIncludeBorders(GXBorderType border, BOOL b);
	//@cmember
	// Font.
	GRID_API BOOL GetIncludeFont() const;
	GRID_API CGXStyle& SetIncludeFont(BOOL b);
	GRID_API CGXFont GetFont() const;
	GRID_API const CGXFont& GetFontRef() const;
	GRID_API CGXStyle& SetFont(const CGXFont& font, GXModifyType mt = gxOverride);
	//@cmember
	// Text Color.
	GRID_API BOOL GetIncludeTextColor() const;
	GRID_API CGXStyle& SetIncludeTextColor(BOOL b);
	GRID_API COLORREF GetTextColor() const;
	GRID_API COLORREF GetTextColorNA() const;
	GRID_API CGXStyle& SetTextColor(COLORREF rgbColor);
	//@cmember
	// WrapText.
	GRID_API BOOL GetIncludeWrapText() const;
	GRID_API CGXStyle& SetIncludeWrapText(BOOL b);
	GRID_API BOOL GetWrapText() const;
	GRID_API CGXStyle& SetWrapText(BOOL b);
	//@cmember
	// AutoSize.
	GRID_API BOOL GetIncludeAutoSize() const;
	GRID_API CGXStyle& SetIncludeAutoSize(BOOL b);
	GRID_API BOOL GetAutoSize() const;
	GRID_API CGXStyle& SetAutoSize(BOOL b);
	//@cmember
	// Allow Enter.
	GRID_API BOOL GetIncludeAllowEnter() const;
	GRID_API CGXStyle& SetIncludeAllowEnter(BOOL b);
	GRID_API BOOL GetAllowEnter() const;
	GRID_API CGXStyle& SetAllowEnter(BOOL b);
	//@cmember
	// Value.
	GRID_API CGXStyle& SetValueType(unsigned nType);
	GRID_API unsigned GetValueType() const;

	GRID_API BOOL GetIncludeValue() const;
	GRID_API CGXStyle& SetIncludeValue(BOOL b);
	GRID_API const CString& GetValue() const;
	GRID_API const CString& GetValueRef() const;
	GRID_API CGXStyle& SetValue(LPCTSTR s);
	GRID_API CGXStyle& SetValue(const CString& s);
#ifdef _UNICODE
	//@cmember
	// This special UNICODE version of SetValue will convert ansi characters
	// to wide characters.
	GRID_API CGXStyle& SetValue(const char* s);
#endif
	GRID_API CGXStyle& SetValue(DWORD dw);
	GRID_API CGXStyle& SetValue(UINT ui);
	GRID_API CGXStyle& SetValue(WORD w);
	GRID_API CGXStyle& SetValue(short s);
	GRID_API CGXStyle& SetValue(LONG l);
	GRID_API CGXStyle& SetValue(float f);
	GRID_API CGXStyle& SetValue(double d);
	GRID_API DWORD GetDWordValue() const;
	GRID_API WORD GetWordValue() const;
	GRID_API UINT GetUIntValue() const;
	GRID_API short GetShortValue() const;
	GRID_API LONG GetLongValue() const;
	GRID_API float GetFloatValue() const;
	GRID_API double GetDoubleValue() const;
	//@cmember
	// Basestyle.
	GRID_API BOOL GetIncludeBaseStyle() const;
	GRID_API CGXStyle& SetIncludeBaseStyle(BOOL b);
	GRID_API WORD GetBaseStyle() const;
	GRID_API CGXStyle& SetBaseStyle(WORD wBaseStyleId);
	//@cmember
	// Choice list: each choice is separated with a new newline.
	GRID_API BOOL GetIncludeChoiceList() const;
	GRID_API CGXStyle& SetIncludeChoiceList(BOOL b);
	GRID_API const CString& GetChoiceList() const;
	GRID_API const CString& GetChoiceListRef() const;
	GRID_API CGXStyle& SetChoiceList(LPCTSTR s);
	GRID_API CGXStyle& SetChoiceList(const CString& s);
#ifdef _UNICODE
	//@cmember
	// This special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
	GRID_API CGXStyle& SetChoiceList(const char* s);
#endif
	//@cmember
	// Enabled.
	GRID_API BOOL GetIncludeEnabled() const;
	GRID_API CGXStyle& SetIncludeEnabled(BOOL b);
	GRID_API BOOL GetEnabled() const;
	GRID_API CGXStyle& SetEnabled(BOOL b);
	//@cmember
	// TriState.
	GRID_API BOOL GetIncludeTriState() const;
	GRID_API CGXStyle& SetIncludeTriState(BOOL b);
	GRID_API BOOL GetTriState() const;
	GRID_API CGXStyle& SetTriState(BOOL b);
	//@cmember
	// Draw3dFrame.
	GRID_API BOOL GetIncludeDraw3dFrame() const;
	GRID_API CGXStyle& SetIncludeDraw3dFrame(BOOL b);
	GRID_API GXDraw3dFrameType GetDraw3dFrame() const;
	GRID_API CGXStyle& SetDraw3dFrame(GXDraw3dFrameType t);
	//@cmember
	// FloatCell.
	GRID_API BOOL GetIncludeFloatCell() const;
	GRID_API CGXStyle& SetIncludeFloatCell(BOOL b);
	GRID_API BOOL GetFloatCell() const;
	GRID_API CGXStyle& SetFloatCell(BOOL b);
	//@cmember
	// FloodCell.
	GRID_API BOOL GetIncludeFloodCell() const;
	GRID_API CGXStyle& SetIncludeFloodCell(BOOL b);
	GRID_API BOOL GetFloodCell() const;
	GRID_API CGXStyle& SetFloodCell(BOOL b);
	//@cmember
	// MergeCell.
	GRID_API BOOL GetIncludeMergeCell() const;
	GRID_API CGXStyle& SetIncludeMergeCell(BOOL b);
	GRID_API unsigned GetMergeCell() const;
	GRID_API CGXStyle& SetMergeCell(unsigned ui);
	//@cmember
	// Format.
	GRID_API BOOL GetIncludeFormat() const;
	GRID_API CGXStyle& SetIncludeFormat(BOOL b);
	GRID_API unsigned GetFormat() const;
	GRID_API CGXStyle& SetFormat(unsigned ui);
	//@cmember
	// Places.
	GRID_API BOOL GetIncludePlaces() const;
	GRID_API CGXStyle& SetIncludePlaces(BOOL b);
	GRID_API unsigned GetPlaces() const;
	GRID_API CGXStyle& SetPlaces(unsigned ui);
	//@cmember
	// ItemDataPtr.
	GRID_API BOOL GetIncludeItemDataPtr() const;
	GRID_API CGXStyle& SetIncludeItemDataPtr(BOOL b);
	GRID_API void* GetItemDataPtr() const;
	GRID_API CGXStyle& SetItemDataPtr(void* pv);
	//@cmember
	// Negative State Text color.
	GRID_API BOOL GetIncludeNegativeStateColor() const;
	GRID_API CGXStyle& SetIncludeNegativeStateColor(BOOL b);
	GRID_API DWORD GetNegativeStateColor() const;
	GRID_API CGXStyle& SetNegativeStateColor(DWORD color);
	//@cmember
	// User attributes
	GRID_API BOOL GetIncludeUserAttribute(WORD nID) const;
	GRID_API CGXStyle& SetIncludeUserAttribute(WORD nID, BOOL b);
	GRID_API const CGXAbstractUserAttribute& GetUserAttribute(WORD nID) const;
	GRID_API void GetUserAttribute(WORD nID, CString& s) const;
	GRID_API CGXStyle& SetUserAttribute(WORD nID, const CGXAbstractUserAttribute& attribute);
	GRID_API CGXStyle& SetUserAttributePtr(WORD nID, CGXAbstractUserAttribute* pValue);
	GRID_API CGXStyle& SetUserAttribute(WORD nID, const CString& s);
	GRID_API CGXStyle& SetUserAttribute(WORD nID, LPCTSTR pszValue);
	GRID_API CGXStyle& SetUserAttribute(WORD nID, DWORD value);
	GRID_API CGXStyle& SetUserAttribute(WORD nID, LONG value);
	GRID_API CGXStyle& SetUserAttribute(WORD nID, double value);
	GRID_API CGXStyle& SetUserAttribute(WORD nID, GXBYTE8 value);

	GRID_API CGXStyle& SetUserAttributes(const CGXUserAttributeMap* p);
	GRID_API const CGXUserAttributeMap* GetUserAttributeMap() const;

protected:
	GRID_API CGXPen* GetBorders() const;

	GRID_API CGXStyle& SetBorders(const CGXPen* pPenArray);

public:
	//@cmember
	// Constants.
	GRID_API static const int nBorders;
	//@cmember
	// Profile entries.
	GRID_API static LPCTSTR szHorizontalAlignment;
	GRID_API static LPCTSTR szVerticalAlignment;
	GRID_API static LPCTSTR szReadOnly;
	GRID_API static LPCTSTR szControl;
	GRID_API static LPCTSTR szInterior;
	GRID_API static LPCTSTR szTextColor;
	GRID_API static LPCTSTR szWrapText;
	GRID_API static LPCTSTR szAllowEnter;
	GRID_API static LPCTSTR szFont;
	GRID_API static LPCTSTR szBorders;
	GRID_API static LPCTSTR szBorder[4];
	GRID_API static LPCTSTR szValue;
	GRID_API static LPCTSTR szMaxLength;
	GRID_API static LPCTSTR szVertScroll;
	GRID_API static LPCTSTR szBaseStyle;
	GRID_API static LPCTSTR szChoiceList;
	GRID_API static LPCTSTR szEnabled;
	GRID_API static LPCTSTR szTriState;
	GRID_API static LPCTSTR szDraw3dFrame;
	GRID_API static LPCTSTR szAutoSize;
	GRID_API static LPCTSTR szFloatCell;
	GRID_API static LPCTSTR szFloodCell;
	GRID_API static LPCTSTR szMergeCell;
	GRID_API static LPCTSTR szFormat;
	GRID_API static LPCTSTR szPlaces;
	//@cmember
	// Implementation.
	GRID_API DWORD GetStyleBits() const;

	friend class CGXStyleCompareSubsetImp;
	friend class CGXStyleSerializeImp;
	friend class CGXGridProfileImp;
	friend class CGXSerializeOG5CompatibleImp;
	friend class CGXStyleFTR;
};

// for portability
#define AddUserAttribut AddUserAttribute

typedef const CGXStyle* LPCSTYLE;

class CGXStylesMap: public CObject
{
	GRID_DECLARE_SERIAL(CGXStylesMap)

public:
	//@cmember
	// Operations.
	GRID_API CGXStylesMap(CRuntimeClass* pStyleClass = NULL);
	GRID_API CGXStylesMap(const CGXStylesMap& p);
	GRID_API void CreateStandardStyles();

	GRID_API const CGXStylesMap& operator=(const CGXStylesMap& p);

	GRID_API void Serialize(CArchive& ar);
	//@cmember
	// Profile.
	GRID_API virtual void WriteProfile() const;
	GRID_API virtual BOOL ReadProfile();

	GRID_API void SetSection(LPCTSTR pszSection);
	GRID_API const CString& GetSection() const;
	//@cmember
	// Base Style
	// Register a new style (or change an already registered style).
	GRID_API WORD RegisterStyle(LPCTSTR pszName, const CGXStyle& style, BOOL bSystemStyle = FALSE);
	GRID_API WORD RegisterStyle(UINT nResourceId, const CGXStyle& style, BOOL bSystemStyle = FALSE);

		// Return the id for the style
	GRID_API WORD GetBaseStyleId(LPCTSTR pszName) const;
	GRID_API WORD GetBaseStyleId(UINT nResourceID) const;

		// Return the name for the style
	GRID_API LPCTSTR GetStyleName(WORD wStyleId) const;
	GRID_API LPCTSTR GetStyleName(WORD wStyleId, UINT& nResourceId) const;
	//@cmember
	// Some Operations with the styles.
	GRID_API BOOL IsSystemStyle(WORD wStyleId) const;
	GRID_API BOOL LookupStyle(WORD wStyleId, CGXStyle*& style) const;
	GRID_API void RemoveStyle(WORD wStyleId);
	//@cmember
	// Support for User attributes.
	GRID_API void AddUserAttribute(WORD nID, const CGXStyle& style);
	GRID_API void AddUserAttribute(WORD nID, const CGXStyle* pStyle = NULL);
	//@cmember
	// Default user attribute and control which shall be shown
	// in CGXStyleSheet Controls and User Attribute page.
	GRID_API void RegisterDefaultControls();
	GRID_API void RegisterDefaultUserAttributes();

	GRID_API CGXGridCore* Grid() const;

public:
	// constants
	// default style names
	static LPCTSTR szDefaultSection;

	WORD m_wStyleStandard,
		 m_wStyleColHeader,
		 m_wStyleRowHeader;

	CRuntimeClass* m_pStyleClass;

// Implementation
public:
	GRID_API virtual ~CGXStylesMap();

#ifdef _DEBUG
	GRID_API void AssertValid() const;
	GRID_API void Dump(CDumpContext& dc) const;
#endif
	//@cmember
	// Implementation - Iterate through the styles.
	GRID_API POSITION StartStylesIteration() const;
	GRID_API void GetNextStyle(POSITION& pos, WORD& wStyleId, CString& sName, UINT& nResourceID, const CGXStyle*& pStyle) const;
	//@cmember
	// Implementation - Controls.
	GRID_API void AddControl(WORD nID);
	GRID_API const CMapWordToPtr& GetControlNameMap() const;
	//@cmember
	// Implementation - User attributes.
	GRID_API const CMapWordToPtr& GetUserAttrInfoMap() const;

public:
	// Implementation - structures
	struct UserAttrInfo
	{
         // Access member functions
		GRID_API UserAttrInfo();
		GRID_API UserAttrInfo(const UserAttrInfo& srcInfo);
		GRID_API ~UserAttrInfo();

         // Attributes
		WORD nID;
		CString sName;
		CGXStyle* pStyle;
	};

	struct BaseStyleInfo
	{
         // Access member functions
		GRID_API BaseStyleInfo();
		GRID_API BaseStyleInfo(const BaseStyleInfo& srcInfo);
		GRID_API ~BaseStyleInfo();

         // Attributes
		WORD nID;
		UINT nResourceID;// used for system-styles, otherwise 0
		CString sName;
		CGXStyle* pStyle;
		BOOL bSystem;
	};

protected:
	//@cmember
	// Implementation - CleanUp.
	GRID_API void Free();
	GRID_API void FreeStylesMap();
	GRID_API void FreeControlMap();

protected:
	// Implementation - Attributes
	GRID_API void StoreStyle(WORD wStyleId, const CGXStyle& style, LPCTSTR szName, UINT nResourceId, BOOL bSystem);

	// base styles
	CMapWordToPtr m_mwpIdInfo;
	CMapWordToPtr m_mwpIdStyle;
	CMapPtrToWord m_mpwResourceId;
	CMapStringToPtr m_mswNameId;

	WORD m_nLastId;
	GRID_API WORD GetNewId();

	// control names
	CMapWordToPtr m_ControlNameMap;

	// user attributes
	CMapWordToPtr m_UserAttrInfoMap;

	// section name
	CString m_sSection;

	friend class CGXGridDocSerializeImp;
	friend class CGXGridProfileImp;
	friend class CGXGridParamCopyOperatorImp;
	friend class CGXStylesMapFTR;
};


// type-safe CPtrArray for CGXStyle objects

class CGXStylePtrArray: public CPtrArray
{
	GRID_DECLARE_DYNAMIC(CGXStylePtrArray)

public:
	//@cmember
	// Construction/Destruction
	GRID_API CGXStylePtrArray();
	GRID_API CGXStylePtrArray(const CGXStylePtrArray& other);
	GRID_API virtual ~CGXStylePtrArray();
		// destructor automatically deletes all referenced objects

	GRID_API const CGXStylePtrArray& operator=(const CGXStylePtrArray& other);

	GRID_API void DeleteAll(); // delete all referenced objects
	GRID_API void DeleteAt(int nIndex, int nCount = 1);
	GRID_API void Move(int nIndex, int nCount, int nDest);

	GRID_API virtual void Serialize(CArchive& ar);

public:
	//@cmember
	// Accessing elements.
	GRID_API CGXStyle* GetAt(int nIndex) const;
	GRID_API void SetAt(int nIndex, CGXStyle* newElement);
	//@cmember
	// Potentially growing the array.
	GRID_API void SetAtGrow(int nIndex, CGXStyle* newElement);
	GRID_API int Add(CGXStyle* newElement);
	//@cmember
	// Overloaded operator helpers.
	GRID_API CGXStyle* operator[](int nIndex) const;
	GRID_API CGXStyle*& operator[](int nIndex);
	//@cmember
	// Operations that move elements around.
	GRID_API void InsertAt(int nIndex, CGXStyle* newElement, int nCount = 1);
	GRID_API void InsertAt(int nStartIndex, CGXStylePtrArray* pNewArray);

	friend class CGXGridDocSerializeImp;
};

// type-safe CPtrArray for array with CGXStylePtrArray objects

class CGXStylePtrArrayPtrArray: public CPtrArray
{
	GRID_DECLARE_DYNAMIC(CGXStylePtrArrayPtrArray)

public:
	// Construcion/Destruction
	GRID_API CGXStylePtrArrayPtrArray();
	GRID_API CGXStylePtrArrayPtrArray(const CGXStylePtrArrayPtrArray& other);
	GRID_API virtual ~CGXStylePtrArrayPtrArray();
		// destructor automatically deletes all referenced objects

	GRID_API const CGXStylePtrArrayPtrArray& operator=(const CGXStylePtrArrayPtrArray& other);

	GRID_API void DeleteAll(); // delete all referenced objects
	GRID_API void DeleteAt(int nIndex, int nCount = 1);
	GRID_API void Move(int nIndex, int nCount, int nDest);

	GRID_API virtual void Serialize(CArchive& ar);

public:
	//@cmember
	// Accessing elements.
	GRID_API CGXStylePtrArray* GetAt(int nIndex) const;
	GRID_API void SetAt(int nIndex, CGXStylePtrArray* newElement);
	//@cmember
	// Potentially growing the array.
	GRID_API void SetAtGrow(int nIndex, CGXStylePtrArray* newElement);
	GRID_API int Add(CGXStylePtrArray* newElement);
	//@cmember
	// overloaded operator helpers.
	GRID_API CGXStylePtrArray* operator[](int nIndex) const;
	GRID_API CGXStylePtrArray*& operator[](int nIndex);
	//@cmember
	// Operations that move elements around.
	GRID_API void InsertAt(int nIndex, CGXStylePtrArray* newElement, int nCount = 1);
	GRID_API void InsertAt(int nStartIndex, CGXStylePtrArrayPtrArray* pNewArray);

	friend class CGXGridDocSerializeImp;
};

/* [VC7] VC7 Libraries already defines these operators, so
calls are ambigous*/
#if (_MFC_VER < 0x0700)
GRID_API CArchive& AFXAPI operator <<(CArchive& ar, const GXBYTE8& b);
GRID_API CArchive& AFXAPI operator >>(CArchive& ar, GXBYTE8& b);
#endif

// Data

class CGXGridParam;

class CGXData: public CObject
{
	GRID_DECLARE_SERIAL(CGXData)

public:
	// operations
	GRID_API CGXData();
	GRID_API virtual ~CGXData();
	GRID_API virtual void DeleteContents();
	GRID_API virtual void Serialize(CArchive& ar);

	GRID_API virtual const CGXData& operator=(const CGXData& p);
	GRID_API virtual void InitParam(CGXGridParam* pParam);

	GRID_API static void AFXAPI ImplementSortMoveData();
	GRID_API static void AFXAPI ImplementCopyMoveCells();

	friend class CGXGridSortMoveDataImp;
	friend class CGXDataCopyMoveCellsImp;
	friend class CGXDataFTR;

protected:
	// attributes
	ROWCOL	m_nRows, // row count
			m_nCols; // column count

	CGXStylePtrArray m_apRowBaseStyle;// row base styles
	CGXStylePtrArray m_apColBaseStyle;// column base styles

	CGXStylePtrArrayPtrArray m_apapCellStyle; // spans the cell matrix,
												// CGXStylePtrArray elements are rows
												// which CGXStyle elements are styles

	CGXStyle m_tmpValueStyle;
	CGXStyle m_tmpValueGetStyle;

	CGXAppData* m_pAppData;

// Access member functions
public:
	//@cmember
	// Number of Rows and Columns.
	GRID_API virtual ROWCOL GetRowCount();
	GRID_API virtual ROWCOL GetColCount();
	GRID_API virtual BOOL StoreRowCount(ROWCOL wRows);
	GRID_API virtual BOOL StoreColCount(ROWCOL wCols);

// Operations
public:
	//@cmember
	// Inserting Columns or Rows.
	GRID_API virtual BOOL StoreInsertRows(ROWCOL nRow, ROWCOL nCount);
	GRID_API virtual BOOL StoreInsertCols(ROWCOL nCol, ROWCOL nCount);
	//@cmember
	// Removing Columns or Rows.
	GRID_API virtual BOOL StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow);
	GRID_API virtual BOOL StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol);
	//@cmember
	// Moving Columns or Rows.
	GRID_API virtual BOOL StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow);
	GRID_API virtual BOOL StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol);
	//@cmember
	// Copy/move ranges in one step.
	GRID_API virtual BOOL StoreCopyCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol);
	GRID_API virtual BOOL StoreMoveCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol, CObject*& pUndoInfo, BOOL bCreateUndoInfo, int ctCmd);
	//@cmember
	// Cell data.
	GRID_API virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType = 0);
	GRID_API BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, GXModifyType mt, int nType = 0);
	GRID_API virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt, int nType = 0);
	//@cmember
	// Sorting (rearraging) rows and columns.
	GRID_API virtual BOOL StoreMoveDataRows(const CGXRange& sortRange, const CRowColArray& anRowIndex);
	GRID_API virtual BOOL StoreMoveDataCols(const CGXRange& sortRange, const CRowColArray& anColIndex);
	//@cmember
	// Update.
	GRID_API virtual BOOL GetUpdateFlag(ROWCOL nRow, ROWCOL nCol);
	GRID_API virtual void SetUpdateFlag(ROWCOL nRow, ROWCOL nCol, BOOL bToggle);
		// set update flag (TRUE if cell shall be updated next time CGXGridCore::RefreshView is called)
	GRID_API virtual void AddRecalcRange(const CGXRange& range);
	GRID_API virtual void Recalc(BOOL bForceRecalc = FALSE);
	GRID_API virtual void ResetError();
	GRID_API virtual BOOL GetError(CString& strError);

	GRID_API virtual CObject* GetAdvancedUndoInfo();
	GRID_API virtual BOOL UndoAdvanced(CObject* pAdvUndo, BOOL bCreateUndoInfo, BOOL bOnlyToolCells);
	GRID_API virtual BOOL SetAdvancedUndo(BOOL b);

	GRID_API virtual BOOL SetRangeName(LPCTSTR name, const CGXRange& rg, CObject* pUndoInfo = NULL);
	GRID_API virtual BOOL GetRangeName(LPCTSTR name, CGXRange& rg);
	GRID_API virtual BOOL DeleteRangeName(LPCTSTR name, CObject*& pUndoInfo, BOOL bCreateUndoInfo);

	GRID_API CGXGridCore* Grid() const;
	//@cmember
	// Optimized for value only
	GRID_API BOOL StoreValueRowCol(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszValue, GXModifyType mt, int nType = 0, CGXStyle* pValueStyle = NULL);
	GRID_API LPCTSTR GetValueRowCol(ROWCOL nRow, ROWCOL nCol, int nType = 0, CGXStyle* pValueStyle = NULL);

	friend class CGXGridDocSerializeImp;
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "gxstyles.inl"
#endif

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//


#endif // _GXSTYLES_H_
