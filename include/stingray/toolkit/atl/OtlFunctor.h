///////////////////////////////////////////////////////////////////////////////
// OtlFunctor.h
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
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef __OTLFUNCTOR_H__
#define __OTLFUNCTOR_H__

#ifndef __OTLBASE_H__
	#error otlfunctor.h requires otlbase.h to be included first
#endif

#include <StingrayExportDefs.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL
{

/////////////////////////////////////////////////////////////////////////////////
// IOtlFunctorBody -- interface for a functor with zero arguments
//
//  operator() is used to execute the functor.
//
//  This interface is ref-counted.
//
class TOOLKIT_API IOtlFunctorBody
{
public:
    virtual void operator () ( void ) = 0;
    virtual void AddRef      ( void ) = 0;
    virtual void Release     ( void ) = 0;
};


/////////////////////////////////////////////////////////////////////////////////
// COtlFunctor -- handle to an IOtlFunctorBody implementation
//  
//  Follows the handle/body idiom in whic COtlFunctor is a handle
//  and IOtlFunctorBody* is a ref-counted body.
//
//  COtlFunctor::operator() simply delegates to IOtlFunctorBody::operator().
//
class COtlFunctor 
{
public:
	inline COtlFunctor() : m_pfunctor(0){}
    inline COtlFunctor ( IOtlFunctorBody * f, bool bAddRef = true ) : m_pfunctor(0) { Init(f, bAddRef); }
    inline COtlFunctor ( const COtlFunctor & f ) : m_pfunctor(0) { Init(f.m_pfunctor, true); }

    virtual ~COtlFunctor( void ) 
	{ 
		if (m_pfunctor) 
		{
			m_pfunctor->Release(); 
			m_pfunctor = 0;
		}
	}
	
    virtual void operator () ( void ) 
	{ 
		if (m_pfunctor)
			(*m_pfunctor)();
	}

	inline COtlFunctor& operator = (COtlFunctor & f)
	{
		 Init(f.m_pfunctor, true);
		 return *this;
	}

protected:
    inline void Init ( IOtlFunctorBody * f, bool bAddRef ) 
    { 
		if(m_pfunctor)
		{
			m_pfunctor->Release();
			m_pfunctor = 0;
		}

        m_pfunctor = f;
        if (f && bAddRef) f->AddRef();
    }

private:
	IOtlFunctorBody *m_pfunctor;
};



/////////////////////////////////////////////////////////////////////////////////
// IOtlFunctorMinimalImpl -- minimal implementation of IOtlFunctorBody interface
// provides reference counting implementation
// operator() is a no-op

class IOtlFunctorMinimalImpl : public IOtlFunctorBody
{
public:
    inline IOtlFunctorMinimalImpl ( void ) : m_dwRefCount(1) { }
	// need polymorphic destructor so 'delete this' will delete most derived subclass    
    virtual ~IOtlFunctorMinimalImpl ( void ) { }
    virtual void operator () ( void ) { /* do nothing */ }
    virtual void AddRef( void )
	{ 
		++ m_dwRefCount;
	}
   virtual void Release( void )
	{ 
		if (! --m_dwRefCount) 
			delete this;
	}
private:
    unsigned long m_dwRefCount;
};



/////////////////////////////////////////////////////////////////////////////////
// IOtlFunctorBody implementations for a global helper function F
//
//  IOtlFunctorImplForGlobalFunctionNoArgs<DR>          --  F has zero arguments
//  IOtlFunctorImplForGlobalFunction1Arg  <DR,A>        --  F has one argument
//  IOtlFunctorImplForGlobalFunction2Args <DR,A1,A2>    --  F has two arguments
//  IOtlFunctorImplForGlobalFunction3Args <DR,A1,A2,A3> --  F has three arguments

template <class DR>
class IOtlFunctorImplForGlobalFunctionNoArgs : public IOtlFunctorMinimalImpl
{
public:
	typedef DR (*FunctionSignature)(void);
    IOtlFunctorImplForGlobalFunctionNoArgs ( FunctionSignature f ) : m_f(f) { }
    virtual void operator () ( void ) { if (m_f) m_f(); }
protected:
    FunctionSignature m_f;
};

template <class DR, class A>
class IOtlFunctorImplForGlobalFunction1Arg : public IOtlFunctorMinimalImpl
{
public:
	typedef DR (*FunctionSignature)(A);
    IOtlFunctorImplForGlobalFunction1Arg (FunctionSignature f, A a ) : m_f(f), m_a(a) { }
    virtual void operator () ( void ) { if (m_f) m_f(m_a); }
protected:
    FunctionSignature m_f;
    A m_a;
};

template <class DR, class A1, class A2>
class IOtlFunctorImplForGlobalFunction2Args : public IOtlFunctorMinimalImpl
{
public:
	typedef DR (*FunctionSignature)(A1,A2);
    IOtlFunctorImplForGlobalFunction2Args (FunctionSignature f, A1 a1, A2 a2 ) 
		: m_f(f), m_a1(a1), m_a2(a2) { }
    virtual void operator () ( void ) { if (m_f) m_f(m_a1, m_a2); }
protected:
    FunctionSignature m_f;
    A1 m_a1;
    A2 m_a2;
};

template <class DR, class A1, class A2, class A3>
class IOtlFunctorImplForGlobalFunction3Args : public IOtlFunctorMinimalImpl
{
public:
	typedef DR (*FunctionSignature)(A1,A2,A3);
    IOtlFunctorImplForGlobalFunction3Args (FunctionSignature f, A1 a1, A2 a2, A3 a3 ) 
		: m_f(f), m_a1(a1), m_a2(a2), m_a3(a3) { }
    virtual void operator () ( void ) { if (m_f) m_f(m_a1, m_a2, m_a3); }
protected:
    FunctionSignature m_f;
    A1 m_a1;
    A2 m_a2;
    A3 m_a3;
};



/////////////////////////////////////////////////////////////////////////////////
// otlMakeFunctor implementations for a global helper function F
//
//  otlMakeFunctor<DR>          -- F has zero arguments
//  otlMakeFunctor<DR,A>        -- F has one argument
//  otlMakeFunctor<DR,A1,A2>    -- F has two arguments
//  otlMakeFunctor<DR,A1,A2,A3> -- F has three arguments
//
//  example usage:
//
//      int foo ( const char * s, int n )
//          { 
//              // body omitted
//          }
//
//      COtlFunctor f = otlMakeFunctor(foo, "hello world", 1001);
//
//      f(); // same as executing foo("hello world", 1001);
//
template <class DR>
COtlFunctor otlMakeFunctor( DR (*callee)(void) )
{
    return COtlFunctor(new IOtlFunctorImplForGlobalFunctionNoArgs<DR>(callee), false /* no extra addref */);
};

template <class DR, class A, class AA>
COtlFunctor otlMakeFunctor ( DR (*callee)(A), AA a )
{
    return COtlFunctor(new IOtlFunctorImplForGlobalFunction1Arg<DR,A>(callee,a), false);
};

template <class DR, class A1, class A2, class AA1, class AA2>
COtlFunctor otlMakeFunctor ( DR (*callee)(A1,A2), AA1 a1, AA2 a2 )
{
    return COtlFunctor(new IOtlFunctorImplForGlobalFunction2Args<DR,A1,A2>(callee,a1,a2), false);
};

template <class DR, class A1, class A2, class A3, class AA1, class AA2, class AA3>
COtlFunctor otlMakeFunctor ( DR (*callee)(A1,A2,A3), AA1 a1, AA2 a2, AA3 a3 )
{
    return COtlFunctor(new IOtlFunctorImplForGlobalFunction3Args<DR,A1,A2,A3>(callee,a1,a2,a3), false);
};

/////////////////////////////////////////////////////////////////////////////////
// IOtlFunctorBody implementations for a non-static member function F of some class C
//
//  IOtlFunctorImplForMemberFunctionNoArgs<>          -- C::F has zero arguments
//  IOtlFunctorImplForMemberFunctionOneArg<>          -- C::F has one argument
//  IOtlFunctorImplForMemberFunctionTwoArgs<>         -- C::F has two arguments
//  IOtlFunctorImplForMemberFunctionThreeArgs<>       -- C::F has three arguments

template <class theClass, class DR>
class IOtlFunctorImplForMemberFunctionNoArgs : public IOtlFunctorMinimalImpl
{
public:
	typedef DR (theClass::*FunctionSignature)(void);

	IOtlFunctorImplForMemberFunctionNoArgs( theClass& c, FunctionSignature function ) 
		: m_c(c), m_f(function) { }

	virtual void operator () ( void )
	{ 
		if (m_f)
			(m_c.*m_f)();
	}

protected:
    FunctionSignature m_f;
	theClass& m_c;
};


template <class theClass, class DR, class A>
class IOtlFunctorImplForMemberFunctionOneArg : public IOtlFunctorMinimalImpl
{
public:
	typedef DR (theClass::*FunctionSignature)(A);

	IOtlFunctorImplForMemberFunctionOneArg( theClass& c, FunctionSignature function, A a ) 
		: m_c(c), m_f(function), m_a(a) { }

	virtual void operator () ( void )
	{ 
		if (m_f)
			(m_c.*m_f)(m_a);
	}

protected:
    FunctionSignature m_f;
	theClass& m_c;
	A m_a;
};


template <class theClass, class DR, class A1, class A2>
class IOtlFunctorImplForMemberFunctionTwoArgs : public IOtlFunctorMinimalImpl
{
public:
	typedef DR (theClass::*FunctionSignature)(A1,A2);

	IOtlFunctorImplForMemberFunctionTwoArgs( theClass& c, FunctionSignature function, A1 a1, A2 a2 ) 
		: m_c(c), m_f(function), m_a1(a1), m_a2(a2) {}

	virtual void operator () ( void )
	{ 
		if (m_f)
			(m_c.*m_f)(m_a1,m_a2);
	}

protected:
    FunctionSignature m_f;
	theClass& m_c;
	A1 m_a1;
	A2 m_a2;
};


template <class theClass, class DR, class A1, class A2, class A3>
class IOtlFunctorImplForMemberFunctionThreeArgs : public IOtlFunctorMinimalImpl
{
public:
	typedef DR (theClass::*FunctionSignature)(A1,A2,A3);

	IOtlFunctorImplForMemberFunctionThreeArgs( theClass& c, FunctionSignature function, A1 a1, A2 a2, A3 a3  ) 
		: m_c(c), m_f(function), m_a1(a1), m_a2(a2), m_a3(a3) { }

	virtual void operator () ( void )
	{ 
		if (m_f)
			(m_c.*m_f)(m_a1,m_a2,m_a3);
	}

protected:
    FunctionSignature m_f;
	theClass& m_c;
	A1 m_a1;
	A2 m_a2;
	A3 m_a3;
};

/////////////////////////////////////////////////////////////////////////////////
// otlMakeFunctor implementations for a non-static member function F of some class C
//
//  otlMakeFunctor<C,DR>          -- C::F has zero arguments
//  otlMakeFunctor<C,DR,A>        -- C::F has one argument
//  otlMakeFunctor<C,DR,A1,A2>    -- C::F has two arguments
//  otlMakeFunctor<C,DR,A1,A2,A3> -- C::F has three arguments
//
//  example usage:
//
//      class Foo
//      {
//      public:
//          Foo ( void ) :  m_nOtherData(0) { }
//          Foo ( const Foo & f ) : m_nOtherData(f.m_nOtherData) { } // copy constructor required
//          void Bar ( const char * s, int n );
//          int m_nOtherData;
//          // can contain any other state that is useful to the execution of Bar
//      };
//
//      Foo fooSample;
//      fooSample.m_nOtherData = 2002;
//      COtlFunction f = otlMakeFunctor(fooSample, &Foo::Bar, "hello world", 1001);
//              // f now contains a copy of fooSample
//
//      f(); // same as executing fooSample.Bar("hello world", 1001);
//           //     where fooSample.m_nOtherData == 2002
//

template <class theClass, class DR>
COtlFunctor otlMakeFunctor( theClass& classref, DR (theClass::*function)(void))
{
   return COtlFunctor(new IOtlFunctorImplForMemberFunctionNoArgs<theClass,DR>(classref,function), false /* no extra addref */);
}                        

template <class theClass, class DR, class A, class AA>
COtlFunctor otlMakeFunctor( theClass& classref, DR (theClass::*function)(A), AA a)
{
   return COtlFunctor(new IOtlFunctorImplForMemberFunctionOneArg<theClass,DR,A>(classref,function,a), false /* no extra addref */);
}                        

template <class theClass, class DR, class A1, class A2, class AA1, class AA2>
COtlFunctor otlMakeFunctor( theClass& classref, DR (theClass::*function)(A1, A2), AA1 a1, AA2 a2)
{
   return COtlFunctor(new IOtlFunctorImplForMemberFunctionTwoArgs<theClass,DR,A1,A2>(classref,function,a1,a2), false /* no extra addref */);
}                        

template <class theClass, class DR, class A1, class A2, class A3, class AA1, class AA2, class AA3>
COtlFunctor otlMakeFunctor( theClass& classref, DR (theClass::*function)(A1, A2, A3), AA1 a1, AA2 a2, AA3 a3)
{
   return COtlFunctor(new IOtlFunctorImplForMemberFunctionThreeArgs<theClass,DR,A1,A2,A3>(classref,function,a1,a2,a3), false /* no extra addref */);
}                        


};	// namespace StingrayOTL

#endif // __OTLFUNCTOR_H__
