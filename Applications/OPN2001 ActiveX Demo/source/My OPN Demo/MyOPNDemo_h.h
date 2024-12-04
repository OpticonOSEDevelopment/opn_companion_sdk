

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Tue Sep 29 16:37:42 2009
 */
/* Compiler settings for .\MyOPNDemo.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __MyOPNDemo_h_h__
#define __MyOPNDemo_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMyOPNDemo_FWD_DEFINED__
#define __IMyOPNDemo_FWD_DEFINED__
typedef interface IMyOPNDemo IMyOPNDemo;
#endif 	/* __IMyOPNDemo_FWD_DEFINED__ */


#ifndef __MyOPNDemo_FWD_DEFINED__
#define __MyOPNDemo_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyOPNDemo MyOPNDemo;
#else
typedef struct MyOPNDemo MyOPNDemo;
#endif /* __cplusplus */

#endif 	/* __MyOPNDemo_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __MyOPNDemo_LIBRARY_DEFINED__
#define __MyOPNDemo_LIBRARY_DEFINED__

/* library MyOPNDemo */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MyOPNDemo;

#ifndef __IMyOPNDemo_DISPINTERFACE_DEFINED__
#define __IMyOPNDemo_DISPINTERFACE_DEFINED__

/* dispinterface IMyOPNDemo */
/* [uuid] */ 


EXTERN_C const IID DIID_IMyOPNDemo;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1C37E8C7-EA05-4EEC-8BAA-1E4315684020")
    IMyOPNDemo : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IMyOPNDemoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyOPNDemo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyOPNDemo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyOPNDemo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMyOPNDemo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMyOPNDemo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMyOPNDemo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMyOPNDemo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IMyOPNDemoVtbl;

    interface IMyOPNDemo
    {
        CONST_VTBL struct IMyOPNDemoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyOPNDemo_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyOPNDemo_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyOPNDemo_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyOPNDemo_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMyOPNDemo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMyOPNDemo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMyOPNDemo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMyOPNDemo_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MyOPNDemo;

#ifdef __cplusplus

class DECLSPEC_UUID("E3B1C89C-34FC-4067-BF3C-6BEE46581C7C")
MyOPNDemo;
#endif
#endif /* __MyOPNDemo_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


