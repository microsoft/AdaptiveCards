

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0620 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for C:\Users\cwhytock\AppData\Local\Temp\srs2_vim_dev\AdaptiveCards.XamlCardRenderer.idl-d865ce28:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=ARM 8.01.0620 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __AdaptiveCards2EXamlCardRenderer_h__
#define __AdaptiveCards2EXamlCardRenderer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if defined(__cplusplus)
#if defined(__MIDL_USE_C_ENUM)
#define MIDL_ENUM enum
#else
#define MIDL_ENUM enum class
#endif
#endif


/* Forward Declarations */ 

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IXamlCardRenderer;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_FWD_DEFINED__ */


/* header files for imported files */
#include "inspectable.h"
#include "Windows.Foundation.h"
#include "Windows.UI.Xaml.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0000 */
/* [local] */ 

#pragma warning(push)
#pragma warning(disable:4668) 
#pragma warning(disable:4001) 
#pragma once
#pragma warning(pop)
#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class XamlCardRenderer;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IXamlCardRenderer[] = L"AdaptiveCards.XamlCardRenderer.IXamlCardRenderer";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0000 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0000_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IXamlCardRenderer */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("DB7C7BB8-C313-440A-A421-B52620107F8B")
                IXamlCardRenderer : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE RenderCardAsXaml( 
                        /* [out][retval] */ ABI::Windows::UI::Xaml::IUIElement **root) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE RenderCardAsImage( void) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IXamlCardRenderer = __uuidof(IXamlCardRenderer);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRendererVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *RenderCardAsXaml )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [out][retval] */ __x_ABI_CWindows_CUI_CXaml_CIUIElement **root);
        
        HRESULT ( STDMETHODCALLTYPE *RenderCardAsImage )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRendererVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRendererVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_RenderCardAsXaml(This,root)	\
    ( (This)->lpVtbl -> RenderCardAsXaml(This,root) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_RenderCardAsImage(This)	\
    ( (This)->lpVtbl -> RenderCardAsImage(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0001 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_XamlCardRenderer_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_XamlCardRenderer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_XamlCardRenderer[] = L"AdaptiveCards.XamlCardRenderer.XamlCardRenderer";
#endif


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0001 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0001_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


