///////////////////////////////////////////////////////////////////////////////
// SrFormuladefines.h
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

#ifndef __defines_h__
#define __defines_h__

#pragma warning( disable : 4067 )  


#ifndef _tstrcmp
  #define _tstrcmp(x,y) strcmp(x,y)
#endif

#ifndef _tstrcpy
  #define _tstrcpy(d,s) strcpy(d,s)
#endif

#ifndef _tstrlen
  #define _tstrlen(x) strlen(x)
#endif

#ifndef _tstrncpy
  #define _tstrncpy(d,s,x) strncpy(d,s,x)
#endif

#ifndef _tstrstr
  #define _tstrstr(s,d) strstr(s,d)
#endif
#ifndef _ttof
  #define _ttof(x) atof(x)
#endif

#ifndef _ttoi
  #define _ttoi(x) atoi(x)
#endif

#ifndef _ttolower
  #define _ttolower(x) tolower(x)
#endif

#ifndef _ttoupper
  #define _ttoupper(x) toupper(x)
#endif

#endif //__defines_h__
