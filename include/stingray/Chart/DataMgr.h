///////////////////////////////////////////////////////////////////////////////
// DataMgr.h
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
//@doc SRGDataManager
//@module DataMgr.h | SRGDataManager header file<nl>
//Written by Bob Powell and Chuanzhong Zhu (www.roguewave.com)

#ifndef _SRG_DATA_MANAGER_H_
#define _SRG_DATA_MANAGER_H_

#include "SRGDat.h"
#include <StingrayExportDefs.h>

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	//#define AFX_DATA OC_DATA
	#define AFX_DATA CHART_API
#endif



class SRGraphDummyData : public SRGraphData
{
public:
	inline virtual void SetNull(BOOL /*b*/){};
	inline virtual void SetValue(double /*number*/){};
	inline SRGraphDummyData(){m_HiLoValue.Zero();m_bNULL=TRUE;m_dValue=0.0;}
	inline virtual void SetAnnotation(int /*code*/, LPCTSTR /*text*/){};
	inline virtual void SetAnnotation(LPCTSTR /*text*/, BOOL /*clear=FALSE*/, int /*code=1*/){};
};

/////////////////////////////
// AutoDuck tag block block for SRGDataManager 

//@doc SRGDataManager
//@mdata CPtrList  | SRGDataManager | m_data | A pointer list that store the data

//@doc SRGDataManager
//@mdata SRGraphAnnotationList  | SRGDataManager | m_strTitle | The title string for this data. Note this is actually a
//list of string indexed by the country code of the international phone call. The corresponding string for each of
//the code will using the language of the country

// adinsert AutoDuck insertion point for SRGDataManager 

//$head The Data Manager Object
//$level 1

//@doc SRGDataManager 
//@class This class stores the data of a graph. The data is stored as a virtual 2-dimensional array of SRGrpahData object. The row of
//this array is called Group while the column is called Index. Each data object in this array can be accessed by group
//and index numbers. Even though you can get one row of data by using GetGroup() function, you can not get a whole column
//in one function call. You need to use each group to get the corresponding column. It is highly recommended that you
//always use the GetSafeData() function to access existing individual data objects.
//A standard SRGDataManager object is instantiated by the SRGraph constructor.
//If you need to customize the data manager, first create your custom SRGDataManager object and then pass this object to 
//SRGraph object via its constructor or SetDataManager() function. 
//You can setup the data for your chart using functions from either the SRGraph or SRGDataManager object. 
//Note that a SRGDataManager object can be shared by several SRGraph objects.
class SRGDataManager : public CObject
{
	CHART_DECLARE_SERIAL(SRGDataManager)

public:
	//@cmember
	/* Constructor */
	CHART_API SRGDataManager();
	//@cmember
	/* Destructor that frees the internal memory */
	CHART_API virtual ~SRGDataManager();

	//@cmember
	/* Initialize the default data style */
	CHART_API void SetDefaultDataStyle(SRGraphStyle v);
	//@cmember
	/* Obtain the default data style */
	CHART_API SRGraphStyle *GetDefaultDataStyle();

	//@cmember
	/* Retrieves the number of the default group*/
	inline  int GetDefaultGroup() const { return m_nDefaultGroup;}
	//@cmember
	/* Sets the number of the default group*/
	inline void SetDefaultGroup(int nDefaultGroup) { m_nDefaultGroup = nDefaultGroup; }

	//@cmember
	/* Creates a new SRGraphDataList object on the application heap */
	CHART_API  virtual SRGraphDataList* NewGroup();
	//@cmember
	/* Serialize this object */
	CHART_API  virtual void Serialize(CArchive &ar);

	//@cmember
	/* Clear all the data inside this object */
	CHART_API virtual void KillData();

	//@cmember
	/* Add a numeric data item into the data array */
	CHART_API virtual void SetValue(int index,int group,double number,BOOL bUseDefaultStyle = FALSE);
	//@cmember
	/* Add a text string for the indicating data item */
	CHART_API virtual void SetText(int index,int group,LPCTSTR text);
	//@cmember
	/* Add a text string for the indicating group of data */
	CHART_API virtual void SetHeader(int group,LPCTSTR text,int nCode = 1);
	//@cmember
	/* Obtain a pointer to a group with given group index */
	CHART_API virtual SRGraphDataList *GetGroup(int group,BOOL GrowList = TRUE);
	//@cmember
	/* Returns the maximum and minimum values stored in this graph */
	CHART_API virtual CScale GetAutoScaleRange(BOOL HiLo = FALSE);
	//@cmember
	/* Returns the count of the longest group */
	CHART_API virtual int GetMaxXDivisions();
	//@cmember
	/* Returns  the number of groups in this object */
	CHART_API virtual int GetGroupCount();
	//@cmember
	/* Returns the title string of this class object */
	CHART_API CString GetGraphTitle(int code = 1);
	//@cmember
	/* Returns the text string of the given data item */
	CHART_API CString GetText(int group,int index,int code = 1);
	//@cmember
	/* Returns the text string of the given group */
	CHART_API CString GetHeader(int group,int code = 1);
	//@cmember
	/* Returns the sum of the data of the specified group */
	CHART_API double GetDataTotal(int group = -1);
	//@cmember
	/* Returns the number of data items in the specified group */
	CHART_API virtual int GetDataCount(int nGroup, BOOL bGrowList = TRUE);
	//@cmember
	/* Set the title for this object */
	CHART_API virtual void SetGraphTitle(LPCTSTR title, int code = 1);
	//@cmember
	/* Returns the average value of the specified group */
	CHART_API virtual double GetGroupAverage(int group);
	//@cmember
	/* Returns the sum of the data items with specified index and group range */
	CHART_API virtual double GetIndexTotal(int index,int nMinGroup = 0,int nMaxGroup = 0);
	//@cmember
	/* Returns the sum of a the data item in this object */
	CHART_API virtual double GetTotal();
	//@cmember
	/* Returns the average value of the specified group and index range */
	CHART_API virtual double GetGroupAverage(int MinIndex,int MaxIndex,int Group);
	//@cmember
	/* Returns the sum of the data items in the specified group and index range */
	CHART_API virtual double GetDataTotal(int mingroup, int  minindex, int maxgroup, int maxindex);
	//@cmember
	/* Returns the numeric value of the specified data item */
	CHART_API virtual double GetValue(int index,int group);
	//@cmember
	/* Returns the whole data list */
	CHART_API virtual CPtrList *GetDataList();
	//@cmember
	/* Returns the header position of the internal data list */
	CHART_API virtual POSITION GetFirstDataPosition();
	//@cmember
	/* Returns the next position in the internal data list */
	CHART_API virtual void *GetNextData(POSITION& p);
	//@cmember
	/* Returns the whole title string list */
	CHART_API virtual SRGraphAnnotationList *GetTitle();
	//@cmember
	/* Set the style to all the specified data item */
	CHART_API virtual void SetGlobalStyle(int nStartGroup,int nEndGroup,int nStartIndex,int nEndIndex,SRGraphStyle *ptrStyle,BOOL bSetHeaders = TRUE);
	//@cmember
	/* Rolls a group in the specified direction */
	CHART_API virtual void RollGroup(int nGroup, double dValue = 0.0, BOOL bDirection = FALSE);
	//@cmember
	/* Returns the data object in the specified position */
	CHART_API virtual SRGraphData *GetData(int index, int group);
	//@cmember
	/* Returns the data object in the specified position */
	CHART_API virtual SRGraphData* GetSafeData(int index, int group);
	//@cmember
	/* Reset the internal pointer position */
	CHART_API virtual void InvalidateGroupPosition();

#ifdef _DEBUG
	CHART_API void Dump(CDumpContext& dc) const;
#endif //_DEBUG

protected:
	//@cmember
	/* The data list -- contains a SRGraphDataList for each group */
	CPtrList	m_data;
	//@cmember
	/* The graph title */
	SRGraphAnnotationList m_strTitle;
	//@cmember
	/* The default data style object*/
	SRGraphStyle m_DefaultDataStyle;
	//@cmember
	/* POSITION of last accessed data item -- used to enhance data access speed*/
	POSITION m_LastPos;

	//@cmember
	/*  Group of last accessed data item -- used to enhance data access speed*/
	int m_LastGroup;
	//@cmember
	/* Dummy chart data object that is returned in case none exists*/
	SRGraphDummyData dummydata;
	//@cmember
	/* Default group for all display types that use only one group -- pie charts, etc. */
	int m_nDefaultGroup;

	// XML formatter for SRGDataManager
	friend class SRGDataManagerFTR;
};


/////////////////////////////
// AutoDuck tag block for SRGDynamicDataManager 

//$head The Data Manager Object
//$level 1


// adinsert AutoDuck insertion point for SRGDynamicDataManager 

//@doc SRGDynamicDataManager 
//@class SRGDynamicDataManager is a alternate data manager to SRGDataManager.
// See the description of SRGDataManager for general information about data managers.
// SRGDataManager can be used for all Data Storage models (Standard, Dynamic, or Structure),
// but it requires special data setup code to utilize the Dynamic and Structure models.
// SRGDynamicDataManager is specialized for the Dynamic data model, making the Dynamic model easier to use.
// SRGDynamicDataManager is used by default with SRDynamicGraph.
class SRGDynamicDataManager : public SRGDataManager
{
	CHART_DECLARE_SERIAL(SRGDynamicDataManager)
public:
	//@cmember
	/* Constructor */
	CHART_API SRGDynamicDataManager();
	//@cmember
	/* Destructor that frees the internal memory */
	CHART_API virtual ~SRGDynamicDataManager();

	//@cmember
	/* Creates a new SRGraphDataList object and initializes it with a SRGraphDynamicData object */
	CHART_API virtual SRGraphDataList* NewGroup();
	//@cmember
	/* Returns the maximum and minimum values stored in this graph */
	CHART_API virtual CScale GetAutoScaleRange(BOOL HiLo = FALSE);
	//@cmember
	/* Returns the sum of the data of the specified group */
	CHART_API virtual double GetDataTotal(int group = -1);
	//@cmember
	/* Returns the count of the longest group */
	CHART_API virtual int GetMaxXDivisions();
	//@cmember
	/* Returns the text string of the given data item */
	CHART_API CString GetText(int group, int index, int code = 1);
	//@cmember
	/* Add a text string for the indicating data item */
	CHART_API virtual void SetText(int index,int group,LPCTSTR text);
	//@cmember
	/* Add a double value into the data array */
	CHART_API virtual void SetValue(int index,int group,double number);
	//@cmember
	/* Add a character value into the data array */
	CHART_API virtual void SetValue(int index,int group,_TCHAR number);
	//@cmember
	/* Add an integer value into the data array */
	CHART_API virtual void SetValue(int index,int group,int number);

	// XML formatter for SRGDynamicDataManager
	friend class SRGDynamicDataManagerFTR;
};

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif//_SRG_DATA_MANAGER_H_
