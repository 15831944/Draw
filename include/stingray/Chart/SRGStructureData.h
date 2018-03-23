///////////////////////////////////////////////////////////////////////////////
// SRGStructureData.h
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

/////////////////////////////////////////////////////////////
// The text comments in this file are formatted to generate
// a help file on build using Microsoft's free Autoduck tool.
// The help file is available with this source and it is
// recommended that you use this file in conjunction with the
// mfc help files.
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
//@doc SRGStructureData
//@module SRGStructureData.h | SRGStructureData header file<nl>
//Includes SRGShortStructData, SRGIntStructData, SRGCharStructData, 
//SRGDoubleStructData, and SRGFloatStructData<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////////
//
// SRGStructureData.h: Interface of the SRGStructureData classes
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SRGSTRUCTUREDATA_H_INCLUDED_)
#define AFX_SRGSTRUCTUREDATA_H_INCLUDED_

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

//$head Structure data classes
//$level 1

/////////////////////////////
// AutoDuck tag block for SRGStructureData 

//@doc SRGStructureData
//@mfunc virtual void  | SRGStructureData | SetValue | Sets a char value in the structure 
//@parm  | _TCHAR | Char value to set 

//@mfunc virtual void  | SRGStructureData | SetValue | Sets a double value in the structure 
//@parm  | double | Double value to set

//@mfunc virtual void  | SRGStructureData | SetValue | Sets an int value in the structure 
//@parm  | int | Integer value to set

//@mfunc virtual void  | SRGStructureData | SetStructure | Sets the pointer to the memory block to be accessed
//@parm void *  | v | Void pointer to a memory block

//@mfunc virtual void * | SRGStructureData | GetStructure | Returns the pointer to the memory block

//@mfunc virtual void  | SRGStructureData | SetStructureSize | Sets the stepping interval for locating the next structure in the array 
//@parm int  | v | Size to be used to determine the address difference between successive structures in the memory block 

//@mfunc virtual int  | SRGStructureData | GetStructureSize | Returns the current structure size (stepping interval) 

//@mfunc virtual void  | SRGStructureData | SetDataOffset | Sets the offset from the base of the structure to the desired data item 
//@parm int  | v | Byte count offset

//@mfunc virtual int  | SRGStructureData | GetDataOffset | Returns the byte count offset of the current data item within the data structure 

//@mdata void *  | SRGStructureData | m_pStructure | Pointer to a data structure or memory block

//@mdata int  | SRGStructureData | m_nStructureSize | Size of each elemental structure within the memory block

//@mdata int  | SRGStructureData | m_nDataOffset | Offset of the data item within the structure

// adinsert AutoDuck insertion point for SRGStructureData 

//@doc SRGStructureData 
//@class Based upon SRGraphDynamicData, this class adds the ability to connect to external 
//data sources that can be interpreted as an array of data structures in a memory block.
//@base public | SRGraphDynamicData
class SRGStructureData : public SRGraphDynamicData  
{
public:
	//@cmember
	/* Sets the grow size to zero -- can't expand external data*/
	CHART_API virtual void SetGrowSize(UINT nSize=0);
	//@cmember
	/* Override to set char values*/
	CHART_API virtual void SetValue(_TCHAR);
	//@cmember
	/* Override to set double values*/
	CHART_API virtual void SetValue(double);
	//@cmember
	/* Override to set int values*/
	CHART_API virtual void SetValue(int);
	//@cmember
	/* 	Returns the buffer grow size (zero)*/
	CHART_API virtual UINT GetGrowSize();
	//@cmember
	/* 	Override to roll the structure data in the memory block*/
	CHART_API virtual void Roll(double dValue,BOOL bDirection);
	//@cmember
	/* Sets the buffer size (the number of structures in the memory block)*/
	CHART_API virtual void SetBufferSize(UINT size);
	//@cmember
	/* Constructor*/
	CHART_API SRGStructureData();
	//@cmember
	/* 	Destructor*/
	CHART_API virtual ~SRGStructureData();
	//@cmember
	/* 	Sets a pointer to the memory block*/
	CHART_API virtual void SetStructure(void * v);
	//@cmember
	/* 	Returns the current pointer to the memory block*/
	CHART_API virtual void * GetStructure();
	//@cmember
	/* 	Sets the size of the structures within the buffer*/
	CHART_API virtual void SetStructureSize(int v);
	//@cmember
	/* 	Returns the size of the structures within the buffer*/
	CHART_API virtual int GetStructureSize();
	//@cmember
	/* Sets the offset of the desired data item within the structure*/
	CHART_API virtual void SetDataOffset(int v);
	//@cmember
	/* Returns the offset of the desired data item within the structure */
	CHART_API virtual int GetDataOffset();
	//@cmember
	/* Increments the input index*/
	CHART_API virtual void IncrementInput();
	//@cmember
	/* Increments the output index*/
	CHART_API virtual void IncrementOutput();
	//@cmember
	/* Decrements the input index*/
	CHART_API virtual void DecrementInput();
	//@cmember
	/* Decrements the output index*/
	CHART_API virtual void DecrementOutput();
	
protected:
	//@cmember
	/* Pointer to the memory block that contains the structures*/
	void * m_pStructure;
	//@cmember
	/* Size in bytes of the structure*/
	int m_nStructureSize;
	//@cmember
	/* Offset of the desired data item within the structure*/
	int m_nDataOffset;
};

/////////////////////////////
// AutoDuck tag block for SRGIntStructData 

// adinsert AutoDuck insertion point for SRGIntStructData 

//@doc SRGIntStructData 
//@class SRGIntStructData is a specialized enhancement of SRGStructureData that retrieves 
//or places an int value at the current position within the array of structures or memory block.
//@base public | SRGStructureData
//@devnote The data value is always cast to double -- the data type that OC expects.
class SRGIntStructData : public SRGStructureData
{
public:
	//@cmember
	/* Constructor*/
	CHART_API SRGIntStructData();
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGIntStructData();
	//@cmember
	/* Sets an int into the structure at the current position*/
	CHART_API virtual void SetValue(double v);
	//@cmember
	/* Retrieves an int from the structure at the current position*/
	CHART_API virtual double GetValue(BOOL bLogData = FALSE);
};

/////////////////////////////
// AutoDuck tag block for SRGCharStructData 

// adinsert AutoDuck insertion point for SRGCharStructData 

//@doc SRGCharStructData 
//@class SRGCharStructData is a specialized enhancement of SRGStructureData that retrieves 
//or places an char value at the current position within the array of structures or memory block.
//@base public | SRGStructureData
//@devnote The data value is always cast to double -- the data type that OC expects.
class SRGCharStructData : public SRGStructureData
{
public:
	//@cmember
	/* Constructor*/
	CHART_API SRGCharStructData();
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGCharStructData();
	//@cmember
	/* Sets a char into the structure at the current position*/
	CHART_API virtual void SetValue(double v);
	//@cmember
	/* Retrieves a char from the structure at the current position*/
	CHART_API virtual double GetValue(BOOL bLogData = FALSE);
};

/////////////////////////////
// AutoDuck tag block for SRGDoubleStructData 

// adinsert AutoDuck insertion point for SRGDoubleStructData 

//@doc SRGDoubleStructData 
//@class SRGDoubleStructData is a specialized enhancement of SRGStructureData that retrieves 
//or places an double value at the current position within the array of structures or memory block.
//@base public | SRGStructureData
//@devnote The data value is always cast to double -- the data type that OC expects.
class SRGDoubleStructData : public SRGStructureData
{
public:
	//@cmember
	/* Constructor*/
	CHART_API SRGDoubleStructData();
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGDoubleStructData();
	//@cmember
	/* Sets a double into the structure at the current position*/
	CHART_API virtual void SetValue(double v);
	//@cmember
	/* Retrieves a double from the structure at the current position*/
	CHART_API virtual double GetValue(BOOL bLogData = FALSE);
};

/////////////////////////////
// AutoDuck tag block for SRGFloatStructData 

// adinsert AutoDuck insertion point for SRGFloatStructData 

//@doc SRGFloatStructData 
//@class SRGFloatStructData is a specialized enhancement of SRGStructureData that retrieves 
//or places a float value at the current position within the array of structures or memory block.
//@base public | SRGStructureData
//@devnote The data value is always cast to double -- the data type that OC expects.
class SRGFloatStructData : public SRGStructureData
{
public:
	//@cmember
	/* Constructor*/
	CHART_API SRGFloatStructData();
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGFloatStructData();
	//@cmember
	/* Sets a float into the structure at the current position*/
	CHART_API virtual void SetValue(double v);
	//@cmember
	/* Retrieves a float from the structure at the current position*/
	CHART_API virtual double GetValue(BOOL bLogData = FALSE);
};

/////////////////////////////
// AutoDuck tag block for SRGShortStructData 

// adinsert AutoDuck insertion point for SRGShortStructData 

//@doc SRGShortStructData 
//@class SRGShortStructData is a specialized enhancement of SRGStructureData that retrieves 
//or places an short value at the current position within the array of structures or memory block.
//@base public | SRGStructureData
//@devnote The data value is always cast to double -- the data type that OC expects.
class SRGShortStructData : public SRGStructureData
{
public:
	//@cmember
	/* Constructor.*/
	CHART_API SRGShortStructData();
	//@cmember
	/* Destructor.*/
	CHART_API virtual ~SRGShortStructData();
	//@cmember
	/* Sets a short into the structure at the current position*/
	CHART_API virtual void SetValue(double v);
	//@cmember
	/* Retrieves a short from the structure at the current position*/
	CHART_API virtual double GetValue(BOOL bLogData = FALSE);
};

#if !defined(_WIN32_WCE_PSPC) || (_WIN32_WCE != 201)
/////////////////////////////
// AutoDuck tag block for SRGDateStructData 

// adinsert AutoDuck insertion point for SRGDateStructData 

//@doc SRGDateStructData 
//@class SRGDateStructData is a specialized enhancement of SRGStructureData that retrieves 
//or places an COleDateTime object at the current position within the array of structures or memory block.
//@base public | SRGStructureData
//@devnote The data value is always cast to double -- the data type that OC expects.
class SRGDateStructData : public SRGStructureData  
{
public:
	//@cmember
	/* Constructor.*/
	CHART_API SRGDateStructData();
	//@cmember
	/* Destructor.*/
	CHART_API virtual ~SRGDateStructData();

	//@cmember
	/* Sets a DATE member of the COleDateTime object at the current position in the structure*/
	CHART_API virtual void SetValue(double v);
	//@cmember
	/* Retrieves the DATE member (cast to double) from the COleDateTime object at the current position in the structure*/
	CHART_API virtual double GetValue(BOOL bLogData = FALSE);
};

#endif
#endif // !defined(AFX_SRGSTRUCTUREDATA_H_INCLUDED_)

// Reset DLL declaration context

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

