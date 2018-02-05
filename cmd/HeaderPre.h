#if defined(__HEADERPRE_H__)
#error Export header file error. check following causes. (ask jbseon)
#endif
#define __HEADERPRE_H__

#if defined(__PROJ_WG_CMD__) 
	#define __MY_EXT_CLASS__      AFX_EXT_CLASS
	#define __MY_EXT_API__        AFX_EXT_API
	#define __MY_EXT_DATA__       AFX_EXT_DATA
#else
	#if defined(_WINDLL)  
		#define __MY_EXT_CLASS__      __declspec(dllimport)
		#define __MY_EXT_API__        __declspec(dllimport)
		#define __MY_EXT_DATA__       __declspec(dllimport)
	#else                    
		#define __MY_EXT_CLASS__      AFX_EXT_CLASS
		#define __MY_EXT_API__        AFX_EXT_API
		#define __MY_EXT_DATA__       AFX_EXT_DATA
	#endif
#endif
