///////////////////////////////////////////////////////////////////////////////
// Relative.h : Declaration of SECLNRelative
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
// Description:  Declaration of SECLNRelative class
//
// SECLNRelative
// Allows relative placement of nodes with respect to each other and 
// to their parent.
// 

#ifndef __SECLAYOUT_RELATIVE_H__
#define __SECLAYOUT_RELATIVE_H__

// Header Includes
#include <StingrayExportDefs.h>

#ifndef __SECLAYOUTNODE_H__
#include "toolkit\layout\layoutnd.h"
#endif

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

#define REL_TOP		SECLNRelativeConstraint::TOP
#define REL_BOTTOM 	SECLNRelativeConstraint::BOTTOM
#define REL_LEFT	SECLNRelativeConstraint::LEFT
#define REL_RIGHT	SECLNRelativeConstraint::RIGHT
#define REL_WIDTH	SECLNRelativeConstraint::WIDTH
#define REL_HEIGHT	SECLNRelativeConstraint::HEIGHT
#define REL_HCENTER SECLNRelativeConstraint::CENTER_HORZ
#define REL_VCENTER SECLNRelativeConstraint::CENTER_VERT
#define REL_MOVEL	SECLNRelativeConstraint::MOVE_LEFT
#define REL_MOVER	SECLNRelativeConstraint::MOVE_RIGHT
#define REL_MOVET	SECLNRelativeConstraint::MOVE_TOP
#define REL_MOVEB	SECLNRelativeConstraint::MOVE_BOTTOM
#define REL_DEFAULT	SECLNRelativeConstraint::DEFAULT


// Types
typedef CTypedPtrMap<CMapPtrToPtr,SECLayoutNode*,CRect*> SECMapNodeRect;

//@doc SECLNRelativeConstraint
//@mdata SECLayoutNode*  | SECLNRelativeConstraint | m_pNodeFrom | Node to which the constraint is applied
//@xref <c SECLNRelativeConstraint>

//@doc SECLNRelativeConstraint
//@mdata ConstraintType  | SECLNRelativeConstraint | m_constraintFrom | Type of constraint applied to m_pNodeFrom
//@xref <c SECLNRelativeConstraint>

//@doc SECLNRelativeConstraint
//@mdata SECLayoutNode*  | SECLNRelativeConstraint | m_pNodeTo | Position m_pNodeFrom relative to this node. Use NULL for absolute position.
//@xref <c SECLNRelativeConstraint>

//@doc SECLNRelativeConstraint
//@mdata ConstraintType  | SECLNRelativeConstraint | m_constraintTo | Target constraint for relatively positioned node.
//@xref <c SECLNRelativeConstraint>

//@doc SECLNRelativeConstraint
//@mdata int  | SECLNRelativeConstraint | m_nModifier | Additive modifier applied to relative constraint
//@xref <c SECLNRelativeConstraint>

//@doc SECLNRelativeConstraint
//@mdata float  | SECLNRelativeConstraint | m_fModifier | Multiplicative modifier applied to relative constraint
//@xref <c SECLNRelativeConstraint>


/////////////////////////////////////////////////////////////////////////////
// SECLNRelativeConstraint

// Relative layout constraint class:
// Subclass, use SetConstraint, and override ApplyConstraint to
// implement your own constraints.

//@doc SECLNRelativeConstraint 
//@class Constraint properties utilized by SECLNRelative
//@xref <c SECLNRelative>
//@comm
// For convenience, the following constants can be used in place of the ConstraintType enum:
// REL_TOP     = SECLNRelativeConstraint::TOP
// REL_BOTTOM  = SECLNRelativeConstraint::BOTTOM
// REL_LEFT    = SECLNRelativeConstraint::LEFT
// REL_RIGHT   = SECLNRelativeConstraint::RIGHT
// REL_WIDTH   = SECLNRelativeConstraint::WIDTH
// REL_HEIGHT  = SECLNRelativeConstraint::HEIGHT
// REL_HCENTER = SECLNRelativeConstraint::CENTER_HORZ
// REL_VCENTER = SECLNRelativeConstraint::CENTER_VERT
// REL_MOVEL   = SECLNRelativeConstraint::MOVE_LEFT
// REL_MOVER   = SECLNRelativeConstraint::MOVE_RIGHT
// REL_MOVET   = SECLNRelativeConstraint::MOVE_TOP
// REL_MOVEB   = SECLNRelativeConstraint::MOVE_BOTTOM
// REL_DEFAULT = SECLNRelativeConstraint::DEFAULT
class SECLNRelativeConstraint : public CObject 
{
public:
	TOOLKIT_API SECLNRelativeConstraint();

	//@cmember,menum
	/* ConstraintType - available constraint types*/
	enum ConstraintType { 
			LEFT,			//@@emem adjust node rectangle's left side
			RIGHT,			//@@emem adjust node rectangle's right side
			TOP,			//@@emem adjust node rectangle's top side
			BOTTOM,			//@@emem adjust node rectangle's bottom side
			WIDTH,			//@@emem adjust node rectangle's width
			HEIGHT,			//@@emem adjust node rectangle's height
			CENTER_HORZ,	//@@emem center node rectangle with respect to width
			CENTER_VERT,	//@@emem center node rectangle with respect to height
			MOVE_LEFT,		//@@emem move node rectangle, with respect to left
			MOVE_RIGHT,		//@@emem move node rectangle, with respect to right
			MOVE_TOP,		//@@emem move node rectangle, with respect to top
			MOVE_BOTTOM,	//@@emem move node rectangle, with respect to bottom
			DEFAULT			//@@emem default constraint
		};

	//@cmember
	/* Node to which the constraint is applied*/
	SECLayoutNode* m_pNodeFrom;

	//@cmember
	/* Type of constraint applied to m_pNodeFrom*/
	ConstraintType m_constraintFrom;

	//@cmember
	/* Position m_pNodeFrom relative to this node. Use NULL for absolute position.*/
	SECLayoutNode* m_pNodeTo;		

	//@cmember
	/* Target constraint for relatively positioned node.*/
	ConstraintType m_constraintTo;

	//@cmember
	/* Additive modifier applied to relative constraint*/
	int m_nModifier;

	//@cmember
	/* Multiplicative modifier applied to relative constraint*/
	float m_fModifier;			

//	friend class SECLNRelative;
};

/////////////////////////////////////////////////////////////////////////////
// SECLNRelative

//@doc SECLNRelative 
//@class Implements the relative layout algorithm
//@BASE public | SECLayoutNode
//@xref <c SECLNRelativeConstraint>
class SECLNRelative : public SECLayoutNode
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	TOOLKIT_API SECLNRelative();
	TOOLKIT_API virtual ~SECLNRelative();

	//@access Operations

	//@cmember
	/* Set relative constraint*/
	TOOLKIT_API virtual BOOL SetConstraint(SECLayoutNode* pNodeFrom,
					SECLNRelativeConstraint::ConstraintType constraintFrom,
					SECLayoutNode* pNodeTo,
					SECLNRelativeConstraint::ConstraintType constraintTo=REL_DEFAULT,
					int nModifier=0,float fModifier=1.0);

	//@cmember
	/* Set relative constraint*/
	TOOLKIT_API virtual BOOL SetConstraint(SECLayoutNode* pNodeFrom,
					SECLNRelativeConstraint::ConstraintType constraintFrom,
					int nValue);

	//@cmember
	/* Set relative constraint*/
	TOOLKIT_API virtual BOOL SetConstraint(SECLNRelativeConstraint* pConstraint);

	//@cmember
	/* Remove relative constraint*/
	TOOLKIT_API virtual BOOL RemoveConstraint(SECLayoutNode* pNodeFrom,
					SECLNRelativeConstraint::ConstraintType constraint);

	//@cmember
	/* Remove relative constraint*/
	TOOLKIT_API virtual BOOL RemoveConstraint(SECLNRelativeConstraint* pConstraint);

	//@cmember
	/* Remove all relative constraints*/
	TOOLKIT_API virtual BOOL RemoveAllConstraints();

	// Locate a particular constraint
	TOOLKIT_API virtual SECLNRelativeConstraint* FindConstraint(SECLayoutNode* pNodeFrom,
				SECLNRelativeConstraint::ConstraintType constraint);

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
	CTypedPtrList<CPtrList,SECLNRelativeConstraint* > m_listCnstr;
	CTypedPtrList<CPtrList,SECLNRelativeConstraint* > m_listAllocCnstr;

	// Implementation Member Functions

	// Constraint application:
	TOOLKIT_API virtual BOOL ApplyAllConstraints(SECMapNodeRect& mapNodeRects);
	TOOLKIT_API virtual BOOL ApplyConstraint(SECLNRelativeConstraint* pConstr,
								CRect* pRectFrom,CRect* pRectTo);
	TOOLKIT_API virtual BOOL ApplyConstraintPosition(long& nRectPos,
									SECLNRelativeConstraint* pConstr,
									CRect* pRectTo); 
	TOOLKIT_API virtual BOOL ApplyConstraintSizing(long& nBoundStart,long& nBoundStop,
									SECLNRelativeConstraint* pConstr,
									CRect* pRectTo);
	TOOLKIT_API virtual BOOL ApplyConstraintCentering(long& lBoundStart,long& lBoundStop,
									long lRectToBase,
									SECLNRelativeConstraint* pConstr,
									CRect* pRectTo);

	// Temp Node rectangle storage/utilization
	TOOLKIT_API virtual void GetNodeRects(SECMapNodeRect& mapNodeRects);
	TOOLKIT_API virtual CRect ApplyNodeRects(SECMapNodeRect& mapNodeRects,
								BOOL bChildNegotiate,BOOL bStrictRecalc);
	TOOLKIT_API virtual void FreeNodeRects(SECMapNodeRect& mapNodeRects);

	// Constraint manipulation
	TOOLKIT_API virtual void SetDefaultConstraint(SECLNRelativeConstraint::ConstraintType& cFrom,
										 SECLNRelativeConstraint::ConstraintType& cTo);
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


#endif //__SECLAYOUT__RELATIVE_H__

