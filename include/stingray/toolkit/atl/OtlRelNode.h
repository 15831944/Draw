///////////////////////////////////////////////////////////////////////////////
// OtlRelNode.h
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

#ifndef __OTLRELNODE_H__
#define __OTLRELNODE_H__

#ifndef __OTLBASE_H__
	#error otlrelnode.h requires otlbase.h to be included first
#endif

#include <Toolkit\atl\otllayoutnode.h>
#include <foundation\stwarn.h>
#include <map>
#include <list>
#include <algorithm>
#include <foundation\stwarnp.h>
#include <StingrayExportDefs.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL
{


// Multiply by float modifier, than add int modifier
#define MODIFIY_CONSTRAINT(x,n,f)	(long)(f*(float)x+0.5)+n

/////////////////////////////////////////////////////////////////////////////
// layout manager - relative algorithm

#define REL_TOP		COtlRelativeConstraint::TOP
#define REL_BOTTOM 	COtlRelativeConstraint::BOTTOM
#define REL_LEFT	COtlRelativeConstraint::LEFT
#define REL_RIGHT	COtlRelativeConstraint::RIGHT
#define REL_WIDTH	COtlRelativeConstraint::WIDTH
#define REL_HEIGHT	COtlRelativeConstraint::HEIGHT
#define REL_HCENTER COtlRelativeConstraint::CENTER_HORZ
#define REL_VCENTER COtlRelativeConstraint::CENTER_VERT
#define REL_MOVEL	COtlRelativeConstraint::MOVE_LEFT
#define REL_MOVER	COtlRelativeConstraint::MOVE_RIGHT
#define REL_MOVET	COtlRelativeConstraint::MOVE_TOP
#define REL_MOVEB	COtlRelativeConstraint::MOVE_BOTTOM
#define REL_DEFAULT	COtlRelativeConstraint::DEFAULT


// Types
typedef std::map<COtlLayoutNode*, RECT* > OTLMapNodeRect;

/////////////////////////////////////////////////////////////////////////////
// COtlRelativeConstraint

class COtlRelativeConstraint
{
public:
	inline COtlRelativeConstraint()
	{
		m_pNodeFrom=(COtlLayoutNode *)NULL;
		m_constraintFrom=REL_DEFAULT;					// to be configured...
		m_pNodeTo=(COtlLayoutNode *)NULL;
		m_constraintTo=REL_DEFAULT;						// to be configured...
		m_nModifier=0;
		m_fModifier=1.0;
	}

	enum ConstraintType { 
			LEFT,
			RIGHT,
			TOP,
			BOTTOM,
			WIDTH,
			HEIGHT,
			CENTER_HORZ,
			CENTER_VERT,
			MOVE_LEFT,
			MOVE_RIGHT,
			MOVE_TOP,
			MOVE_BOTTOM,
			DEFAULT
		};

	// Node to which the constraint is applied
	COtlLayoutNode* m_pNodeFrom;

	// Type of constraint applied to m_pNodeFrom
	ConstraintType m_constraintFrom;

	// Position m_pNodeFrom relative to this node. Use NULL for absolute position
	COtlLayoutNode* m_pNodeTo;		

	// Target constraint for relatively positioned node
	ConstraintType m_constraintTo;

	// Additive modifier applied to relative constraint
	int m_nModifier;

	// Multiplicative modifier applied to relative constraint
	float m_fModifier;			

};

/////////////////////////////////////////////////////////////////////////////
// COtlRelativeNode

class COtlRelativeNode : public COtlLayoutNode
{
public:
	typedef std::list<COtlRelativeConstraint* > OTLCONSTRAINTLIST;

	inline COtlRelativeNode() {}
	virtual ~COtlRelativeNode() {RemoveAllConstraints();}

	virtual BOOL SetConstraint(COtlLayoutNode* pNodeFrom,
					COtlRelativeConstraint::ConstraintType constraintFrom,
					COtlLayoutNode* pNodeTo,
					COtlRelativeConstraint::ConstraintType constraintTo=REL_DEFAULT,
					int nModifier=0,float fModifier=1.0)
	{
		// pNodeTo can be NULL (absolute position)
		if(!pNodeFrom) return FALSE;

		// "Default" is no more than a keyword to identify unitialized constraints.
		// If either constraint is default, set to an appropriate initial state.
		SetDefaultConstraint(constraintFrom,constraintTo);

		// If constraint object already exists, modify existing
		COtlRelativeConstraint* pConstr;
		pConstr=FindConstraint(pNodeFrom,constraintFrom);
		if(pConstr) 
		{
			// Modify existing:
			pConstr->m_pNodeFrom=pNodeFrom;
			pConstr->m_constraintFrom=constraintFrom;
			pConstr->m_pNodeTo=pNodeTo;
			pConstr->m_constraintTo=constraintTo;
			pConstr->m_nModifier=nModifier;
			pConstr->m_fModifier=fModifier;
			return TRUE;
		}
		
		// Otherwise, setting a new constraint:
		pConstr=new COtlRelativeConstraint;
		pConstr->m_pNodeFrom=pNodeFrom;
		pConstr->m_constraintFrom=constraintFrom;
		pConstr->m_pNodeTo=pNodeTo;
		pConstr->m_constraintTo=constraintTo;
		pConstr->m_nModifier=nModifier;
		pConstr->m_fModifier=fModifier;
		if(!SetConstraint(pConstr)) 
		{
			delete pConstr;
			return FALSE;
		}

		// Add to allocation list for proper cleanup later.
		m_listAllocCnstr.push_back(pConstr);
		
		return TRUE;
	}

	virtual BOOL SetConstraint(COtlLayoutNode* pNodeFrom,
					COtlRelativeConstraint::ConstraintType constraintFrom,
					int nValue)
	{
		// NULL "To" node, "constraintTo" ignored.
		return SetConstraint(pNodeFrom,constraintFrom,NULL,constraintFrom,nValue);
	}

	virtual BOOL SetConstraint(COtlRelativeConstraint* pConstraint)
	{
		if(!pConstraint) return FALSE;
		// Bail if already present
		OTLCONSTRAINTLIST::iterator it = std::find(m_listCnstr.begin(), m_listCnstr.end(), pConstraint);
		if(it != m_listCnstr.end() )
			return FALSE;

		// Add to constraint list, but not to allocation list!
		m_listCnstr.push_back(pConstraint);

		// Resolve any default constraints
		SetDefaultConstraint(pConstraint->m_constraintFrom,pConstraint->m_constraintTo);

		return TRUE;
	}

	virtual BOOL RemoveConstraint(COtlLayoutNode* pNodeFrom,
					COtlRelativeConstraint::ConstraintType constraint)
	{
		COtlRelativeConstraint* pTemp = 0;
		OTLCONSTRAINTLIST::iterator it;
		for(it = m_listCnstr.begin(); it != m_listCnstr.end(); it++) 
		{
			OTLASSERT(*it);
			pTemp = *it;
			if((pTemp->m_pNodeFrom==pNodeFrom)&&
			   (pTemp->m_constraintFrom==constraint)) 
			{

			   // Found it. Remove and exit.
			   RemoveConstraint(pTemp);
			   return TRUE;
			}

		}

		return FALSE;
	}

	virtual BOOL RemoveConstraint(COtlRelativeConstraint* pConstraint)
	{
		if(!pConstraint) return FALSE;

		OTLCONSTRAINTLIST::iterator it = std::find(m_listCnstr.begin(), m_listCnstr.end(), pConstraint);
		if(it == m_listCnstr.end() )
			return FALSE;

		m_listCnstr.erase(it);

		// If constraint was allocated by this class, auto-delete
		it = std::find(m_listAllocCnstr.begin(), m_listAllocCnstr.end(), pConstraint);
		if(it != m_listAllocCnstr.end() )
		{
			m_listAllocCnstr.erase(it);
			delete pConstraint;
		}
		return TRUE;
	}

	virtual BOOL RemoveAllConstraints()
	{
		// Remove all configured constraints
		m_listCnstr.erase(m_listCnstr.begin(), m_listCnstr.end());

		// Delete all alloc'd constraints (subset of configured)
		COtlRelativeConstraint* pTemp = 0;
		OTLCONSTRAINTLIST::iterator it;
		for(it = m_listAllocCnstr.begin(); it != m_listAllocCnstr.end(); it++) 
		{
			OTLASSERT(*it);
			pTemp = *it;
			delete pTemp;
		}

		m_listAllocCnstr.erase(m_listAllocCnstr.begin(), m_listAllocCnstr.end());

		return TRUE;
	}

	// Locate a particular constraint
	virtual COtlRelativeConstraint* FindConstraint(COtlLayoutNode* pNodeFrom,
				COtlRelativeConstraint::ConstraintType constraint)
	{
		if(!pNodeFrom) 
			return (COtlRelativeConstraint *)NULL; 

		COtlRelativeConstraint* pTemp = 0;
		OTLCONSTRAINTLIST::iterator it;
		for(it = m_listCnstr.begin(); it != m_listCnstr.end(); it++) 
		{
			OTLASSERT(*it);
			pTemp = *it;
			if((pTemp->m_pNodeFrom==pNodeFrom)&&
			   (pTemp->m_constraintFrom==constraint))
			   return pTemp;
		}
		return (COtlRelativeConstraint *)NULL; 
	}


	virtual void OnRecalcLayout(LPRECT lpRect,
								const RECT& rectDesired,
								BOOL bChildNegotiate,
								BOOL bStrictRecalc)
	{
		// must apply the rect before ApplyConstraints for proper parent rect query
		SetCurrentRect(rectDesired);

		// Store a temp copy of all child node rectangles for quick manipulation
		OTLMapNodeRect mapNodeRects;
		GetNodeRects(mapNodeRects);

		// Edit the child rects in one swoop. Do not use node RecalcLayout yet as
		// that could be a potentially CPU intensive operation
		ApplyAllConstraints(mapNodeRects);

		// OK, rectangles positioned, now iterate through and issue the 
		// node RecalcLayouts
		RECT rectCurrent;
		ApplyNodeRects(&rectCurrent, mapNodeRects,bChildNegotiate,bStrictRecalc);
		SetCurrentRect(rectCurrent);

		// Deallocate the rectangle entries alloc'd by GetNodeRects
		FreeNodeRects(mapNodeRects);
		
		if(lpRect)
			::CopyRect(lpRect, &rectCurrent);
	}

protected:

	// Implementation Member Variables
	OTLCONSTRAINTLIST m_listCnstr;
	OTLCONSTRAINTLIST m_listAllocCnstr;

	// Implementation Member Functions

	// Constraint application:
	virtual BOOL ApplyAllConstraints(OTLMapNodeRect& mapNodeRects)
	{
		COtlRelativeConstraint* pConstr = 0;
		LPRECT pRectFrom = 0;
		LPRECT pRectTo = 0;
		
		OTLCONSTRAINTLIST::iterator it;
		OTLMapNodeRect::iterator itm;

		for(it = m_listCnstr.begin(); it != m_listCnstr.end(); it++) 
		{
			OTLASSERT(*it);
			pConstr= *it;
			// This should work if everything was set up properly!
			if((itm = mapNodeRects.find(pConstr->m_pNodeFrom)) != mapNodeRects.end())
				pRectFrom = (*itm).second;

			if(pConstr->m_pNodeTo) 
			{
				if((itm = mapNodeRects.find(pConstr->m_pNodeTo)) != mapNodeRects.end())
					pRectTo = (*itm).second;
			}
			else pRectTo=pRectFrom;

			ApplyConstraint(pConstr,pRectFrom,pRectTo);
		}
		return TRUE;
	}

	virtual BOOL ApplyConstraint(	COtlRelativeConstraint* pConstr,
									LPRECT pRectFrom,
									LPRECT pRectTo)
	{
		if((!pConstr)||(!pRectFrom)||(!pRectTo)) return FALSE;

		// establish the constraint
		long lHeight,lWidth;
		switch(pConstr->m_constraintFrom) 
		{
			case COtlRelativeConstraint::LEFT:
				return ApplyConstraintPosition(pRectFrom->left,pConstr,pRectTo);
			case COtlRelativeConstraint::RIGHT:
				return ApplyConstraintPosition(pRectFrom->right,pConstr,pRectTo);
			case COtlRelativeConstraint::TOP:
				return ApplyConstraintPosition(pRectFrom->top,pConstr,pRectTo);
			case COtlRelativeConstraint::BOTTOM:
				return ApplyConstraintPosition(pRectFrom->bottom,pConstr,pRectTo);
			case COtlRelativeConstraint::WIDTH:
				return ApplyConstraintSizing(pRectFrom->left,pRectFrom->right,pConstr,pRectTo);
			case COtlRelativeConstraint::HEIGHT:
				return ApplyConstraintSizing(pRectFrom->top,pRectFrom->bottom,pConstr,pRectTo);
			case COtlRelativeConstraint::CENTER_HORZ:
				return ApplyConstraintCentering(pRectFrom->left,pRectFrom->right,
											pRectTo->left,pConstr,pRectTo);
			case COtlRelativeConstraint::CENTER_VERT:
				return ApplyConstraintCentering(pRectFrom->top,pRectFrom->bottom,
											pRectTo->top,pConstr,pRectTo);
			case COtlRelativeConstraint::MOVE_LEFT:
				// Position to left, and adjust right to maintain size
				lWidth=OtlRectWidth(*pRectFrom);
				if(ApplyConstraintPosition(pRectFrom->left,pConstr,pRectTo)) 
				{
					pRectFrom->right=pRectFrom->left+lWidth;
					return TRUE;
				}
				break;
			case COtlRelativeConstraint::MOVE_RIGHT:
				// Position to right, and adjust left to maintain size
				lWidth=OtlRectWidth(*pRectFrom);
				if(ApplyConstraintPosition(pRectFrom->right,pConstr,pRectTo)) 
				{
					pRectFrom->left=pRectFrom->right-lWidth;
					return TRUE;
				}
				break;
			case COtlRelativeConstraint::MOVE_TOP:
				// Position to top, and adjust bottom to maintain size
				lHeight=OtlRectHeight(*pRectFrom);
				if(ApplyConstraintPosition(pRectFrom->top,pConstr,pRectTo)) 
				{
					pRectFrom->bottom=pRectFrom->top+lHeight;
					return TRUE;
				}
				break;
			case COtlRelativeConstraint::MOVE_BOTTOM:
				// Position to bottom, and adjust top to maintain size
				lHeight=OtlRectHeight(*pRectFrom);
				if(ApplyConstraintPosition(pRectFrom->bottom,pConstr,pRectTo)) 
				{
					pRectFrom->top=pRectFrom->bottom-lHeight;
					return TRUE;
				}
				break;
			default:
				// constraint not found!
				break;
		}
		return FALSE;

	}

	virtual BOOL ApplyConstraintPosition(	long& lRectPos,
											COtlRelativeConstraint* pConstr,
											LPRECT pRectTo)
	{
		// ApplyConstraint should insure this:
		OTLASSERT((pConstr)&&(pRectTo));

		// If target node is NULL, use absolute positioning
		if(!pConstr->m_pNodeTo) 
		{
			lRectPos=pConstr->m_nModifier;
			return TRUE;
		}

		// establish the constraint
		int nMod=pConstr->m_nModifier;
		float fMod=pConstr->m_fModifier;
		switch(pConstr->m_constraintTo) 
		{
			case COtlRelativeConstraint::LEFT:
				lRectPos=MODIFIY_CONSTRAINT(pRectTo->left,nMod,fMod);
				break;
			case COtlRelativeConstraint::RIGHT:
				lRectPos=MODIFIY_CONSTRAINT(pRectTo->right,nMod,fMod);
				break;
			case COtlRelativeConstraint::TOP:
				lRectPos=MODIFIY_CONSTRAINT(pRectTo->top,nMod,fMod);
				break;
			case COtlRelativeConstraint::BOTTOM:
				lRectPos=MODIFIY_CONSTRAINT(pRectTo->bottom,nMod,fMod);
				break;
			case COtlRelativeConstraint::WIDTH:
				lRectPos=MODIFIY_CONSTRAINT(OtlRectWidth(*pRectTo),nMod,fMod);
				break;
			case COtlRelativeConstraint::HEIGHT:
				lRectPos=MODIFIY_CONSTRAINT(OtlRectHeight(*pRectTo),nMod,fMod);
				break;
			case COtlRelativeConstraint::DEFAULT: 
				{
				// Default constraints should be resolved by SetDefaultConstraint!
				// If overriding and providing custom constraints, make sure you
				// issue this call on SetConstraint.
				OTLASSERT(FALSE);
				return FALSE;
				}
			default:
				// Didn't handle constraint here!
				return FALSE;
		}
		return TRUE;
	}

	virtual BOOL ApplyConstraintSizing(	long& lBoundStart,
										long& lBoundStop,
										COtlRelativeConstraint* pConstr,
										LPRECT pRectTo)
	{
		// ApplyConstraint should insure this:
		OTLASSERT((pConstr)&&(pRectTo));

		// If target node is NULL, use absolute positioning
		if(!pConstr->m_pNodeTo) 
		{
			lBoundStop=lBoundStart+pConstr->m_nModifier;
			return TRUE;
		}

		// establish the constraint
		int nMod=pConstr->m_nModifier;
		float fMod=pConstr->m_fModifier;
		switch(pConstr->m_constraintTo) 
		{
			case COtlRelativeConstraint::LEFT:
				lBoundStop=lBoundStart+MODIFIY_CONSTRAINT(pRectTo->left,nMod,fMod);
				break;
			case COtlRelativeConstraint::RIGHT:
				lBoundStop=lBoundStart+MODIFIY_CONSTRAINT(pRectTo->right,nMod,fMod);
				break;
			case COtlRelativeConstraint::TOP:
				lBoundStop=lBoundStart+MODIFIY_CONSTRAINT(pRectTo->top,nMod,fMod);
				break;
			case COtlRelativeConstraint::BOTTOM:
				lBoundStop=lBoundStart+MODIFIY_CONSTRAINT(pRectTo->bottom,nMod,fMod);
				break;
			case COtlRelativeConstraint::WIDTH:
				lBoundStop=lBoundStart+MODIFIY_CONSTRAINT(OtlRectWidth(*pRectTo),nMod,fMod);
				break;
			case COtlRelativeConstraint::HEIGHT:
				lBoundStop=lBoundStart+MODIFIY_CONSTRAINT(OtlRectHeight(*pRectTo),nMod,fMod);
				break;
			case COtlRelativeConstraint::DEFAULT: {
				// Default constraints should be resolved by SetDefaultConstraint!
				// If overriding and providing custom constraints, make sure you
				// issue this call on SetConstraint.
				OTLASSERT(FALSE);
				return FALSE;
				}
			default:
				// Didn't handle constraint here!
				return FALSE;
		}
		return TRUE;
	}

	virtual BOOL ApplyConstraintCentering(	long& lBoundStart,
											long& lBoundStop,
											long lRectToBase,
											COtlRelativeConstraint* pConstr,
											LPRECT pRectTo)
	{
		// ApplyConstraint should insure this:
		OTLASSERT((pConstr)&&(pRectTo));

		// establish the constraint
		long lCenterRelativeTo=0;
		switch(pConstr->m_constraintTo) 
		{
			case COtlRelativeConstraint::LEFT:
				lCenterRelativeTo=pRectTo->left;
				break;
			case COtlRelativeConstraint::RIGHT:
				lCenterRelativeTo=pRectTo->right;
				break;
			case COtlRelativeConstraint::TOP:
				lCenterRelativeTo=pRectTo->top;
				break;
			case COtlRelativeConstraint::BOTTOM:
				lCenterRelativeTo=pRectTo->bottom;
				break;
			case COtlRelativeConstraint::WIDTH:
				lCenterRelativeTo=OtlRectWidth(*pRectTo);
				break;
			case COtlRelativeConstraint::HEIGHT:
				lCenterRelativeTo=OtlRectHeight(*pRectTo);
				break;
			case COtlRelativeConstraint::DEFAULT: 
				{
				// Default constraints should be resolved by SetDefaultConstraint!
				// If overriding and providing custom constraints, make sure you
				// issue this call on SetConstraint.
				OTLASSERT(FALSE);
				return FALSE;
				}
			default:
				// Didn't handle constraint here!
				return FALSE;
		}

		// Perform center operation
		long lBoundSize=lBoundStop-lBoundStart;
		long lOffset=(lCenterRelativeTo-lBoundSize)/2;
		lBoundStart=lRectToBase+
					MODIFIY_CONSTRAINT(lOffset,pConstr->m_nModifier,pConstr->m_fModifier);
		lBoundStop=lBoundStart+lBoundSize;

		return TRUE;
	}

	// Temp Node rectangle storage/utilization
	virtual void GetNodeRects(OTLMapNodeRect& mapNodeRects)
	{
		// Iterate through all nodes in the constraint list, querying
		// and saving the current rect for each
		COtlRelativeConstraint* pConstr = 0;
		LPRECT pRect = 0;

		OTLCONSTRAINTLIST::iterator it;
		OTLMapNodeRect::iterator itm;
		for(it = m_listCnstr.begin(); it != m_listCnstr.end(); it++) 
		{
			OTLASSERT(*it);
			pConstr= *it;
			
			// SetConstraint should insure this:			
			OTLASSERT(pConstr->m_pNodeFrom);

			// Check both the "from" and "to" nodes for existance in
			// our rect map. If not, then query and add.
			if((itm = mapNodeRects.find(pConstr->m_pNodeFrom)) == mapNodeRects.end())
			{
				pRect=new RECT;
				pConstr->m_pNodeFrom->GetCurrentRect(pRect);
				mapNodeRects.insert(OTLMapNodeRect::value_type(pConstr->m_pNodeFrom,pRect));
			}

			if(pConstr->m_pNodeTo)
			{
				if((itm = mapNodeRects.find(pConstr->m_pNodeTo)) == mapNodeRects.end())
				{
					pRect=new RECT;
					pConstr->m_pNodeTo->GetCurrentRect(pRect);
					mapNodeRects.insert(OTLMapNodeRect::value_type(pConstr->m_pNodeTo,pRect));
				}
			}
		}
		
	}

	virtual void ApplyNodeRects(	LPRECT lpRect,
									OTLMapNodeRect& mapNodeRects,
									BOOL bChildNegotiate,
									BOOL bStrictRecalc)
	{
		COtlLayoutNode* pNode = 0;
		LPRECT pRectDesired = 0;
		RECT rectUsed;

		OTLMapNodeRect::iterator itm;
		for(itm = mapNodeRects.begin(); itm != mapNodeRects.end(); itm++)
		{
			pNode = (*itm).first;
			pRectDesired = (*itm).second;

			OTLASSERT(pNode);
			OTLASSERT(pRectDesired);

			// constraint map contains both child nodes and their
			// reference nodes (not necessarily children). Only
			// reposition child nodes!
			if(pNode->GetParentNode()!=this) 
				continue;
			
			pNode->RecalcLayout(&rectUsed,*pRectDesired,bChildNegotiate,bStrictRecalc);

			// if child suggested an alternate sizing, and we allow child negotiation,
			// process the requested size as desired. Do nothing if size is ok.
			if( bChildNegotiate && !::EqualRect(&rectUsed, pRectDesired)) 
			{

				// massage rectUsed here

				// If rectUsed has been changed, apply again, with no child negotiation
				RECT rTemp;
				pNode->RecalcLayout(&rTemp,rectUsed,FALSE,bStrictRecalc);
			}
		}
		if(lpRect)
			GetCurrentRect(lpRect);
	}

	virtual void FreeNodeRects(OTLMapNodeRect& mapNodeRects)
	{
		COtlLayoutNode* pNode = 0;
		LPRECT pRectDesired = 0;

		OTLMapNodeRect::iterator itm;
		for(itm = mapNodeRects.begin(); itm != mapNodeRects.end(); itm++)
		{
			pRectDesired = (*itm).second;
			OTLASSERT(pRectDesired);
			delete pRectDesired;
		}

		mapNodeRects.erase(mapNodeRects.begin(), mapNodeRects.end());
	}

	// Constraint manipulation
	virtual void SetDefaultConstraint(	COtlRelativeConstraint::ConstraintType& cFrom,
										COtlRelativeConstraint::ConstraintType& cTo)
	{
		// Set the default "from" constraint to "MOVE_LEFT"
		if(cFrom==REL_DEFAULT) 
			cFrom=REL_MOVEL;

		// Set the default "to" constraint based on the "from" constraint
		if(cTo==REL_DEFAULT)
		{
			switch(cFrom) 
			{
				case REL_TOP: 
				case REL_BOTTOM: 
				case REL_LEFT:
				case REL_RIGHT:
				case REL_WIDTH:
				case REL_HEIGHT:
					cTo=cFrom;
					break;
				case REL_HCENTER:
					cTo=REL_WIDTH;
					break;
				case REL_VCENTER:
					cTo=REL_HEIGHT;
					break;
				case REL_MOVEL:
					cTo=REL_LEFT;
					break;
				case REL_MOVER:
					cTo=REL_RIGHT;
					break;
				case REL_MOVET:
					cTo=REL_TOP;
					break;
				case REL_MOVEB:
					cTo=REL_BOTTOM;
					break;
				case REL_DEFAULT:
					// Defaults should be resolved by now!
					OTLASSERT(FALSE);
				default:
					// Custom constraints? You need to override.
					break;
			}
		}

	}
};

};	// namespace StingrayOTL

#endif // __OTLRELNODE_H__
