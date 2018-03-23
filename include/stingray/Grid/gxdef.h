///////////////////////////////////////////////////////////////////////////////
// gxdef.h

#ifndef _GXDEF_H_
#define _GXDEF_H_
 
//Uncomment the following line if you want the grid to re-throw the exceptions that it catches.
//#define _GX_THROW_LAST_EXCEPTION 

#ifdef _GX_THROW_LAST_EXCEPTION
#define GX_THROW_LAST  THROW_LAST(); 
#else
#define GX_THROW_LAST ;
#endif 

#endif // _GXDEF_H_
