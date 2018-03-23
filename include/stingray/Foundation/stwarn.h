/*

///////////////////////////////////////////////////////////////////////////////
// stwarn.h
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

This files sets the compiler warning level to 3 to turn off a few STL
related warnings. 

Warning C4786 may still be seen. Please refer to the following MSDN article
for more information.

Q167355 BUG: C4786 Warning Is Not Disabled with #pragma Warning 

For information on fixing these warnings with STL please refer to the
following web page

http://www.dinkumware.com/libcppvc.html

Please note that if you include this file you should then include 
"stwarnp.h" after you are done with #include statements for the STL
headers. We do this for all our library headers that use this header.

DJ	10/20/00

--*/
#ifndef __STING_NO_DISABLE_STLWARN__

#if _MSC_VER >= 1200

#pragma warning(push, 3)

#pragma warning(disable: 4018)
#pragma warning(disable: 4146)
#pragma warning(disable: 4786)

#endif //_MSC_VER >= 1200
#endif //!__STING_NO_DISABLE_STLWARN__
