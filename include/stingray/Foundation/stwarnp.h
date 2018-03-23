///////////////////////////////////////////////////////////////////////////////
// stwarnp.h
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

// This files restores the warning level to the saved value (saved by 
// including stwarn.h)

// For information on fixing the warnings with STL please refer to the
// following web page:
// http://www.dinkumware.com/vc_fixes.html
// DJ	10/20/00

#ifndef __STING_NO_DISABLE_STLWARN__

#if _MSC_VER >= 1200
// restore the saved warning state
#pragma warning(pop)
#endif //_MSC_VER >= 1200

#endif //!__STING_NO_DISABLE_STLWARN__ 
