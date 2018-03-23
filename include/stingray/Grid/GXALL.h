///////////////////////////////////////////////////////////////////////////////
// GXALL.h

#ifndef _GXALL_H_
#define _GXALL_H_

// OG needs 8 byte packing for structures
#if _MFC_VER >= 0x0300
// pshpack8.h saves the current #pragma pack value
#include /* */ "pshpack8.h"
#else
#pragma pack(8)
#endif

#if _MFC_VER >= 0x0300
#include <afxcmn.h>         // MFC support for Windows 95 Common Controls
#include <afxole.h>         // MFC support for OLE
#endif

// version info
#include "gxver.h"

// resources
#include "gxresrc.h"

#ifndef __RWUXTHEME_H
#include "RWUXTheme.h"
#endif

// dll support
#ifndef _GXDLL_H_
#include "gxdll.h"
#endif

#ifndef _GXDEF_H_
#include "gxdef.h"
#endif

// Unicode
#ifndef _GXTCHAR_H_
#include "gxtchar.h"
#endif

// core header
#ifndef _GXCOLL_H_
#include "gxcoll.h"
#endif
#ifndef _GXCORE_H_
#include "gxcore.h"
#endif
#ifndef _GXSTYLES_H_
#include "gxstyles.h"
#endif
#ifndef _GXEXT_H_
#include "gxext.h"
#endif
#ifndef _GXSTATE_H_
#include "gxstate.h"
#endif
#ifndef _GXCTRLI_H_
#include "gxctrli.h"
#endif
#ifndef _GXCVRCEL_H_
#include "gxcvrcel.h"
#endif
#ifndef _GXDELAYR_H_
#include "gxdelayr.h"
#endif
#ifndef _GXMSG_H_
#include "gxmsg.h"
#endif

// grid window
#ifndef _GXWND_H_
#include "gxwnd.h"
#endif

// grid view
#ifndef _GXVIEW_H_
#include "gxview.h"
#endif
#ifndef _GXVW_H_
#include "gxvw.h"
#endif

// dialogs
#ifndef _GXPRPDLG_H_
#include "gxprpdlg.h"
#endif
#ifndef _GXSTYDLG_H_
#include "gxstydlg.h"
#endif

// workbooks
#ifndef _GXTWND_H_
#include "gxtwnd.h"
#endif

// Record status window
#ifndef _GXINFWND_H_
#include "gxinfwnd.h"
#endif

// Browser Grid
#ifndef _GXBROWSE_H_
#include "gxbrowse.h"
#endif

#if _MFC_VER >= 0x0400

#include <winnls.h>

#ifndef _GXCRTF_H_
#include "gxcrtf.h"
#endif

#ifndef _GXOLE_H_
#include "gxole.h"
#endif

#ifndef _GXSCRLTP_H_
#include "gxscrltp.h"
#endif

#ifndef _GXDTCTRL_H_
#include "gxdtctrl.h"
#endif

#ifndef _GXCURCTL_H_
#include "gxcurctl.h"
#endif

#ifndef _GXCMD_H_
#include "gxcmd.h"
#endif

#ifndef _GXSINC_H_
#include "gxsinc.h" // formula support
#endif

#ifndef _GXSPLIT_H_
#include "gxsplit.h"
#endif

// Grid HTML Write support
#ifndef _GXHTMLW_H_
#include "gxhtmlW.h"
#endif

//Dynamic split window support
#ifndef _GXDTABWND_H_
#include "gxDTabWnd.h"
#endif

#ifndef _GXDSPLIT_H_
#include "gxDSplit.h"
#endif

// Page break UI
#ifndef _GXPGBRAK_H_
#include "gxpgbrak.h"
#endif

#endif

#ifndef _GXIMOUSE_H_
#include "gximouse.h"
#endif

#ifndef _GX_TAB_SER_H__
#include "gxtabser.h"
#endif


//XML 
#ifndef _SFL_MFC_SUPPORT
#define _SFL_MFC_SUPPORT
#endif //_SFL_MFC_SUPPORT 

#if _MFC_VER >= 0x0300
// poppack.h restores the original #pragma pack value
#include /* */ "poppack.h"
#else
// restore default packing value
#pragma pack()
#endif

#endif // _GXALL_H_
