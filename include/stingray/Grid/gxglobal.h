#pragma once

inline wchar_t* CharToWChar(const char* pstrSrc)
{
	USES_CONVERSION;
	return A2W(pstrSrc);
}

inline char* WCharToChar( const wchar_t* pwstrSrc)
{
	USES_CONVERSION;
	return W2A(pwstrSrc);
}