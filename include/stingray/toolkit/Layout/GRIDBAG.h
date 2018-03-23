///////////////////////////////////////////////////////////////////////////////
// GridBag.h : Declaration of SECLNGridBagBag
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
//
// Author:       Mark Isham
// Description:  Declaration of SECLNGridBag and SECGridBagConstraints classes
//
// SECLNGridBag
// SECLayoutNode derived class implementing the Java GridBag layout manager
//
// SECGridBagConstraints
// Data object utilized by SECLNGridBag
//

#ifndef __SECLAYOUT_GRIDBAG_H__
#define __SECLAYOUT_GRIDBAG_H__

// Header Includes

#ifndef __SECLAYOUTNODE_H__
#include "toolkit\layout\layoutnd.h"
#endif

#include <StingrayExportDefs.h>

//
// SEC Extension DLL
// Initialize declaration context
//
#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL

// Constants
#define GB_RELATIVE		-1
#define GB_REMAINDER	0	

// Forward Declarations
class SECGridBagConstraints;

// Types
typedef CTypedPtrMap<CMapPtrToPtr,SECLayoutNode*,SECGridBagConstraints*> SECMapNodeToConstraint;

//@doc SECGridBagConstraints
//@mfunc void  | SECGridBagConstraints | RestoreDefaults | Restore all gridbag constraints to the default values.
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mfunc void  | SECGridBagConstraints | ClearInsets | Clear the Gridbag constraints inset settings
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mfunc void  | SECGridBagConstraints | StartNextRow | Increment the m_nGridX, m_nGridY settings to start a new row.
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mfunc void  | SECGridBagConstraints | StartNextCol | Increment the m_nGridX, m_nGridY settings to start a new col.
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mdata int  | SECGridBagConstraints | m_nGridX | Cell x position, or use 'GB_RELATIVE' for relative to last
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mdata int  | SECGridBagConstraints | m_nGridY | Cell y position, or use 'GB_RELATIVE' for relative to last
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mdata int  | SECGridBagConstraints | m_nGridWidth | Cell width, or use 'GB_REMAINDER' for remainder of row
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mdata int  | SECGridBagConstraints | m_nGridX | Cell x position, or use 'GB_RELATIVE' for relative to last
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mdata int  | SECGridBagConstraints | m_nGridHeight | Cell height, or use 'GB_REMAINDER' for remainder of column
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mdata float  | SECGridBagConstraints | m_fWeightX | Horizontal weight to be applied to this cell, controls rate of column width change
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mdata float  | SECGridBagConstraints | m_fWeightY | Vertical weight to be applied to this cell, controls rate of row height change
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mdata AnchorType  | SECGridBagConstraints | m_Anchor | nchor type for this cell, determines any special alignment considerations within the cell
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mdata FillType  | SECGridBagConstraints | m_Fill | Fill type for this cell, determines any special stretching of the node to fit the cell
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mdata int  | SECGridBagConstraints | m_nIPADx | Internal padding to width of node. Internal padding adds to the configured minimum width of the node. Like Java, this pads both sides, so actual pad is twice this value.
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mdata int  | SECGridBagConstraints | m_nIPADy | Internal padding to height of node. Internal padding adds to the configured minimum height of the node. Like Java, this pads both sides, so actual pad is twice this value.
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mdata int  | SECGridBagConstraints | m_nInsetL | Left inset of node within cell. This is just like a left margin within the cell.
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mdata int  | SECGridBagConstraints | m_nInsetR | Right inset of node within cell. This is just like a right margin within the cell.
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mdata int  | SECGridBagConstraints | m_nInsetT | Top inset of node within cell. This is just like a top margin within the cell.
//@xref <c SECGridBagConstraints>

//@doc SECGridBagConstraints
//@mdata int  | SECGridBagConstraints | m_nInsetB | Bottom inset of node within cell. This is just like a bottom margin within the cell.
//@xref <c SECGridBagConstraints>

/////////////////////////////////////////////////////////////////////////////
// SECGridBagConstraints


//@doc SECGridBagConstraints 
//@class GridBag configuration constraints
//@xref <c SECLNGridBag>

class SECGridBagConstraints : public CObject
{
	TOOLKIT_DECLARE_DYNAMIC(SECGridBagConstraints);

public:

	// Initialization/Destruction
	TOOLKIT_API SECGridBagConstraints();
	TOOLKIT_API virtual ~SECGridBagConstraints();

	// Attributes
	//@access Attributes

	//@cmember,menum
	/* AnchorType - controls alignment of node inside a gridbag cell*/
	enum AnchorType 
	{ 
		CENTER,			//@@emem horz and vert middle anchor
		NORTH,			//@@emem top, middle anchor
		NORTHEAST,		//@@emem top, right anchor
		EAST,			//@@emem middle, right anchor
		SOUTHEAST,		//@@emem bottom, right anchor
	    SOUTH,			//@@emem bottom, middle anchor
		SOUTHWEST,		//@@emem bottom, left anchor
		WEST,			//@@emem middle, left anchor
		NORTHWEST		//@@emem top, left anchor
	};

	//@cmember,menum
	/* FillType - controls node stretching inside a gridbag cell*/
	enum FillType 
	{ 
		NONE,			//@@emem no fill
		BOTH,			//@@emem fill horizontal and vertical (stretch to cell width and height)
		HORIZONTAL,		//@@emem fill horizontal only (stretch to cell width)
		VERTICAL		//@@emem fill vertical only (stretch to cell height)
	};

	//	...Publicly accessible member variables...

	//@cmember
	/* Cell x position, or use 'GB_RELATIVE' for relative to last*/
	int 		m_nGridX;
	//@cmember
	/* Cell y position, or use 'GB_RELATIVE' for relative to last*/
	int			m_nGridY;				
	//@cmember
	/* Cell width, or use 'GB_REMAINDER' for remainder of row*/
	int 		m_nGridWidth;
	//@cmember
	/* Cell height, or use 'GB_REMAINDER' for remainder of column*/
	int			m_nGridHeight;		
	//@cmember
	/* Horizontal weight to be applied to this cell, controls rate of column width change*/
	float 		m_fWeightX;
	//@cmember
	/* Vertical weight to be applied to this cell, controls rate of row height change*/
	float		m_fWeightY;			
	//@cmember
	/* Anchor type for this cell, determines any special alignment considerations within the cell*/
	AnchorType 	m_Anchor;						
	//@cmember
	/* Fill type for this cell, determines any special stretching of the node to fit the cell*/
	FillType 	m_Fill;		
	//@cmember
	/* Internal padding to width of node. Internal padding adds to the configured minimum width of the node. Like Java, this pads both sides, so actual pad is twice this value.*/
	int 		m_nIPADx;
	//@cmember
	/* Internal padding to height of node. Internal padding adds to the configured minimum height of the node. Like Java, this pads both sides, so actual pad is twice this value.*/
	int			m_nIPADy;			
	//@cmember
	/* Left inset of node within cell. This is just like a left margin within the cell.*/
	int			m_nInsetL;
	//@cmember
	/* Right inset of node within cell. This is just like a right margin within the cell.*/
	int			m_nInsetR;
	//@cmember
	/* Top inset of node within cell. This is just like a top margin within the cell.*/
	int			m_nInsetT;
	//@cmember
	/* Bottom inset of node within cell. This is just like a bottom margin within the cell.*/
	int			m_nInsetB;	

	//@access Operations

	//@cmember
	/* Reset all attributes to default values*/
	TOOLKIT_API void RestoreDefaults();

	//@cmember
	/* Reset all the inset values to zero.*/
	TOOLKIT_API void ClearInsets();

	//@cmember
	/* Increment m_nGridX and m_nGridY to start next row*/
	TOOLKIT_API void StartNextRow();

	//@cmember
	/* Increment m_nGridX and m_nGridY to start next col*/
	TOOLKIT_API void StartNextCol();

	// Accessors
	TOOLKIT_API SECGridBagConstraints& operator=(const SECGridBagConstraints& rhs); 
	TOOLKIT_API SECGridBagConstraints* Clone() const;

protected:

	// Implementation Member Variables
	int m_nGridXActual,m_nGridYActual;

	// SECLNGridBag is a jolly good friend of SECGridBagConstraints
	friend class SECLNGridBag;

};


/////////////////////////////////////////////////////////////////////////////
// SECLNGridBag

//@doc SECGridBagConstraints 
//@class Implements the gridbag layout algorithm
//@BASE public | SECLayoutNode
//@comm Inspired by the Java Gridbag layout manager, Gridbag is a powerful grid layout that allows multiple cell spanning rows/cols, differing weights, anchoring, filling, and use of insets.
//@xref <c SECGridBagConstraints>

class SECLNGridBag : public SECLayoutNode
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	TOOLKIT_API SECLNGridBag();
	TOOLKIT_API virtual ~SECLNGridBag();

	//@access Attributes

	//@cmember
	/* Get the constraint information associated with a particular child node.*/
	TOOLKIT_API virtual SECGridBagConstraints* GetConstraints(SECLayoutNode* pNode) const;

	//@cmember
	/* Reset the constraint information of the specified child node to the new information passed in.*/
	TOOLKIT_API virtual void ResetConstraints(SECLayoutNode* pNode,const SECGridBagConstraints& rConstraints);

	// Operations
	TOOLKIT_API virtual int AddLayoutNode(SECLayoutNode* pNode);

	//@access Operations

	//@cmember
	/* Use this overload of SECLayoutNode::AddLayoutNode to pass gridbag constraint information.*/
	TOOLKIT_API virtual int AddLayoutNode(SECLayoutNode* pNode,
									const SECGridBagConstraints& rConstraints);
	TOOLKIT_API virtual int RemoveLayoutNode(SECLayoutNode* pNode);

	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//
protected:
	TOOLKIT_API virtual CRect OnRecalcLayout(const CRect& rectDesired,
								 BOOL bChildNegotiate,BOOL bStrictRecalc);

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	SECMapNodeToConstraint m_MapNodeToGBC;				// map node to GridBag constraint

	// GridBag information - this is the persistent data that need
	// not be recalculated for each RecalcLayout call.
	SECGridBagConstraints*	m_pLastCellAdded;
	CArray<float,float>		m_arrMaxRowWeights,m_arrMaxColWeights;					// max weight for each row/col
	float					m_fSumMaxRowWeights,m_fSumMaxColWeights;
	CUIntArray				m_arrRowMinHeights,m_arrColMinWidths;					// max of the mins for each row/col
	CUIntArray				m_arrRowPrefHeights,m_arrColPrefWidths;					// max of the preferred sizes
	UINT					m_nMinAcceptableGridWidth,m_nMinAcceptableGridHeight;	// sum min widths, heights
	UINT					m_nPrefGridWidth,m_nPrefGridHeight;						// sum min widths, heights
	BOOL					m_bWeightedX,m_bWeightedY;								// true if 1 or more weights >0

	// Implementation Member Functions
	TOOLKIT_API virtual void EmptyConstraintMap();
	TOOLKIT_API virtual BOOL RemoveConstraint(SECLayoutNode* pNode);

	// data calculation members called on each recalc
	TOOLKIT_API virtual BOOL RecalcRowColSizes(const CRect& rectGrid,CUIntArray& arrRowHeights,
									CUIntArray& arrColWidths);
	TOOLKIT_API virtual BOOL SetNodePositions(const CUIntArray& arrRowHeights,
									const CUIntArray& arrColWidths,
									const CRect& rectGrid,
						 			BOOL bChildNegotiate,BOOL bStrictRecalc);
	TOOLKIT_API virtual BOOL GetNodeActualPosition(SECLayoutNode* pNode,
									SECGridBagConstraints* pConstraints,
									const CUIntArray& arrRowHeights,
									const CUIntArray& arrColWidths,
									const CRect& rectGrid,
									CRect& rectChild);
	TOOLKIT_API virtual BOOL GetNodeDisplayArea(SECLayoutNode* pNode,
									SECGridBagConstraints* pConstraints,
									const CUIntArray& arrRowHeights,
									const CUIntArray& arrColWidths,
									const CRect& rectGrid,
									CRect& rectDisplay);

	// Used by GetNodeActualPosition to account directly for constraints
	TOOLKIT_API virtual void AdjustNodeExternalPadding(SECGridBagConstraints* pConstraints,
									const CRect& rectDisplay,
									int nMinWidth,int nMinHeight,
									CRect& rectChild);
	TOOLKIT_API virtual void AdjustNodeAnchor(SECGridBagConstraints* pConstraints,
									const CRect& rectDisplay,
									const CRect& rectPreferred,
									CRect& rectChild);
	TOOLKIT_API virtual void AdjustNodeFill(SECGridBagConstraints* pConstraints,
									const CRect& rectDisplay,
									const CRect& rectPreferred,
									CRect& rectChild);

	// data calculation members called only on node add/removal
	TOOLKIT_API virtual BOOL ResetGridBagInfo();
	TOOLKIT_API virtual void InitGridBagInfo();
	TOOLKIT_API virtual BOOL UpdateGridBagInfo(SECLayoutNode* pNode,
									SECGridBagConstraints* pConstraints);
	TOOLKIT_API virtual void TrackMaxWeightArrayState(CArray<float,float>& arrWeight,
									int nIndex,float fWeight,BOOL& bWeighted,
									float& fTotal);
	TOOLKIT_API virtual void TrackMaxSizeArrayState(CUIntArray& arrState,int nIndex,
									UINT sizeState,BOOL bUseState,
									UINT& uStateTotal);
	TOOLKIT_API virtual void GetRowColMaxIndex(int& nRowMaxIndex,int& nColMaxIndex);
	TOOLKIT_API virtual BOOL GrowArraysToFit(SECGridBagConstraints* pConstraints);
	TOOLKIT_API virtual BOOL CalcActualCellPos(SECGridBagConstraints* pConstraints);
};

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif //__SECLAYOUT_GRIDBAG_H__

