

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0620 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for C:\Users\riarenas\AppData\Local\Temp\AdaptiveCards.XamlCardRenderer.idl-388d03dd:
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

#ifndef ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
typedef interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement;

#endif 	/* ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__ */


#ifndef ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
typedef interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement;

#endif 	/* ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__ */


#ifndef ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
typedef interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement;

#endif 	/* ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__ */


#ifndef ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
typedef interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement;

#endif 	/* ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__ */


#ifndef ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
typedef interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn;

#endif 	/* ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__ */


#ifndef ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
typedef interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn;

#endif 	/* ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__ */


#ifndef ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
typedef interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn;

#endif 	/* ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__ */


#ifndef ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
typedef interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn;

#endif 	/* ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__ */


#ifndef ____FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
#define ____FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
typedef interface __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement;

#endif 	/* ____FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__ */


#ifndef ____FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
#define ____FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
typedef interface __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement;

#endif 	/* ____FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__ */


#ifndef ____FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
#define ____FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
typedef interface __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn;

#endif 	/* ____FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__ */


#ifndef ____FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
#define ____FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
typedef interface __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn;

#endif 	/* ____FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__ */


#ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement_FWD_DEFINED__
#define ____FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement_FWD_DEFINED__
typedef interface __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement;

#endif 	/* ____FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement_FWD_DEFINED__ */


#ifndef ____FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_FWD_DEFINED__
#define ____FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_FWD_DEFINED__
typedef interface __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement;

#endif 	/* ____FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_FWD_DEFINED__ */


#ifndef ____FIReference_1_Windows__CUI__CText__CFontWeight_FWD_DEFINED__
#define ____FIReference_1_Windows__CUI__CText__CFontWeight_FWD_DEFINED__
typedef interface __FIReference_1_Windows__CUI__CText__CFontWeight __FIReference_1_Windows__CUI__CText__CFontWeight;

#endif 	/* ____FIReference_1_Windows__CUI__CText__CFontWeight_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveCardElement;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveTextBlock;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveCard;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveCardStatics;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveImage;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveContainer;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveColumn;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveColumnSet;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_FWD_DEFINED__ */


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

#ifdef __cplusplus
} /*extern "C"*/ 
#endif
#include <windows.foundation.collections.h>
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
interface IAdaptiveCardElement;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0000 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0000_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4707 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4707 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4707_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4707_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0001 */
/* [local] */ 

#ifndef DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE
#define DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("ad869642-67ac-5b8d-8f6c-0d6d368f9394"))
IIterator<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> : IIterator_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IIterator`1<AdaptiveCards.XamlCardRenderer.IAdaptiveCardElement>"; }
};
typedef IIterator<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_t;
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement ABI::Windows::Foundation::Collections::__FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0001 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0001_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4708 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4708 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4708_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4708_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0002 */
/* [local] */ 

#ifndef DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE
#define DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("d9517a3e-61be-5d41-ae61-f944c5dcd00e"))
IIterable<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> : IIterable_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IIterable`1<AdaptiveCards.XamlCardRenderer.IAdaptiveCardElement>"; }
};
typedef IIterable<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_t;
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement ABI::Windows::Foundation::Collections::__FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0002 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0002_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4709 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4709 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4709_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4709_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0003 */
/* [local] */ 

#ifndef DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE
#define DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("cc2a09d0-2290-5837-9948-78caf849cba5"))
IVectorView<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> : IVectorView_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IVectorView`1<AdaptiveCards.XamlCardRenderer.IAdaptiveCardElement>"; }
};
typedef IVectorView<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_t;
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement ABI::Windows::Foundation::Collections::__FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0003 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0003_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0003_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4710 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4710 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4710_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4710_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0004 */
/* [local] */ 

#ifndef DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE
#define DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("71051658-3679-58b1-a6f3-52269536b48b"))
IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> : IVector_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IVector`1<AdaptiveCards.XamlCardRenderer.IAdaptiveCardElement>"; }
};
typedef IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_t;
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement ABI::Windows::Foundation::Collections::__FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE */

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
interface IAdaptiveColumn;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0004 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0004_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0004_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4711 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4711 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4711_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4711_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0005 */
/* [local] */ 

#ifndef DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE
#define DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("177b1a85-afd6-5364-8def-fcc95592e900"))
IIterator<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> : IIterator_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IIterator`1<AdaptiveCards.XamlCardRenderer.IAdaptiveColumn>"; }
};
typedef IIterator<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_t;
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn ABI::Windows::Foundation::Collections::__FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0005 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0005_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0005_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4712 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4712 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4712_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4712_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0006 */
/* [local] */ 

#ifndef DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE
#define DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("a16a1a57-e954-59b5-bbf7-9813bec6cf90"))
IIterable<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> : IIterable_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IIterable`1<AdaptiveCards.XamlCardRenderer.IAdaptiveColumn>"; }
};
typedef IIterable<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_t;
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn ABI::Windows::Foundation::Collections::__FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0006 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0006_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0006_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4713 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4713 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4713_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4713_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0007 */
/* [local] */ 

#ifndef DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE
#define DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("00890892-b06d-5203-ae15-2d85b293a22b"))
IVectorView<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> : IVectorView_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IVectorView`1<AdaptiveCards.XamlCardRenderer.IAdaptiveColumn>"; }
};
typedef IVectorView<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_t;
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn ABI::Windows::Foundation::Collections::__FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0007 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0007_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0007_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4714 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4714 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4714_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4714_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0008 */
/* [local] */ 

#ifndef DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE
#define DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("8d7fcc96-66f7-519f-a795-168988436cac"))
IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> : IVector_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IVector`1<AdaptiveCards.XamlCardRenderer.IAdaptiveColumn>"; }
};
typedef IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_t;
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn ABI::Windows::Foundation::Collections::__FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0008 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0008_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4715 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4715 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4715_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4715_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0009 */
/* [local] */ 

#ifndef DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE
#define DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("8d9d7686-ac0d-5cb7-8382-571a335cf05b"))
VectorChangedEventHandler<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> : VectorChangedEventHandler_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.VectorChangedEventHandler`1<AdaptiveCards.XamlCardRenderer.IAdaptiveCardElement>"; }
};
typedef VectorChangedEventHandler<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_t;
#define ____FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
#define __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement ABI::Windows::Foundation::Collections::__FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0009 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0009_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0009_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4716 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4716 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4716_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4716_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0010 */
/* [local] */ 

#ifndef DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE
#define DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("5686deef-094a-53f8-a070-ce563eeefa1f"))
IObservableVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> : IObservableVector_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IObservableVector`1<AdaptiveCards.XamlCardRenderer.IAdaptiveCardElement>"; }
};
typedef IObservableVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*> __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_t;
#define ____FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_FWD_DEFINED__
#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement ABI::Windows::Foundation::Collections::__FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_USE */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0010 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0010_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0010_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4717 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4717 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4717_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4717_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0011 */
/* [local] */ 

#ifndef DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE
#define DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("0de4579a-0022-5241-8788-7d0d8f30707e"))
VectorChangedEventHandler<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> : VectorChangedEventHandler_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.VectorChangedEventHandler`1<AdaptiveCards.XamlCardRenderer.IAdaptiveColumn>"; }
};
typedef VectorChangedEventHandler<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_t;
#define ____FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
#define __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn ABI::Windows::Foundation::Collections::__FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0011 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0011_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0011_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4718 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4718 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4718_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4718_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0012 */
/* [local] */ 

#ifndef DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE
#define DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("5aa87e1f-0282-53de-ae2c-7b5b90d9679b"))
IObservableVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> : IObservableVector_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IObservableVector`1<AdaptiveCards.XamlCardRenderer.IAdaptiveColumn>"; }
};
typedef IObservableVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*> __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_t;
#define ____FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_FWD_DEFINED__
#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn ABI::Windows::Foundation::Collections::__FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_USE */
#ifdef __cplusplus
namespace ABI {
namespace Windows {
namespace UI {
namespace Xaml {
class UIElement;
} /*Xaml*/
} /*UI*/
} /*Windows*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace Windows {
namespace UI {
namespace Xaml {
interface IUIElement;
} /*Xaml*/
} /*UI*/
} /*Windows*/
}
#endif


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0012 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0012_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4719 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4719 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4719_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4719_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0013 */
/* [local] */ 

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("a080f956-aced-5764-9f05-fb1f443729aa"))
IAsyncOperationCompletedHandler<ABI::Windows::UI::Xaml::UIElement*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Windows::UI::Xaml::UIElement*, ABI::Windows::UI::Xaml::IUIElement*>> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Windows.UI.Xaml.UIElement>"; }
};
typedef IAsyncOperationCompletedHandler<ABI::Windows::UI::Xaml::UIElement*> __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement_t;
#define ____FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement_FWD_DEFINED__
#define __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement_t

/* ABI */ } /* Windows */ } /* Foundation */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement_USE */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0013 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0013_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0013_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4720 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4720 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4720_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4720_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0014 */
/* [local] */ 

#ifndef DEF___FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_USE
#define DEF___FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("a41e0c0e-fb5e-5b57-ac81-f128277be260"))
IAsyncOperation<ABI::Windows::UI::Xaml::UIElement*> : IAsyncOperation_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Windows::UI::Xaml::UIElement*, ABI::Windows::UI::Xaml::IUIElement*>> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.IAsyncOperation`1<Windows.UI.Xaml.UIElement>"; }
};
typedef IAsyncOperation<ABI::Windows::UI::Xaml::UIElement*> __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_t;
#define ____FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_FWD_DEFINED__
#define __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement ABI::Windows::Foundation::__FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_t

/* ABI */ } /* Windows */ } /* Foundation */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_USE */

#ifdef __cplusplus
namespace ABI {
namespace Windows {
namespace UI {
namespace Text {
struct FontWeight;
} /*Text*/
} /*UI*/
} /*Windows*/
}
#endif


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0014 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0014_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0014_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4721 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4721 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4721_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4721_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0015 */
/* [local] */ 

#ifndef DEF___FIReference_1_Windows__CUI__CText__CFontWeight_USE
#define DEF___FIReference_1_Windows__CUI__CText__CFontWeight_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("741446b3-9c81-5daa-b995-5bd67473492c"))
IReference<struct ABI::Windows::UI::Text::FontWeight> : IReference_impl<struct ABI::Windows::UI::Text::FontWeight> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.IReference`1<Windows.UI.Text.FontWeight>"; }
};
typedef IReference<struct ABI::Windows::UI::Text::FontWeight> __FIReference_1_Windows__CUI__CText__CFontWeight_t;
#define ____FIReference_1_Windows__CUI__CText__CFontWeight_FWD_DEFINED__
#define __FIReference_1_Windows__CUI__CText__CFontWeight ABI::Windows::Foundation::__FIReference_1_Windows__CUI__CText__CFontWeight_t

/* ABI */ } /* Windows */ } /* Foundation */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIReference_1_Windows__CUI__CText__CFontWeight_USE */

interface IInspectable;


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0015 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0015_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0015_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4722 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4722 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4722_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4722_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0016 */
/* [local] */ 

#ifndef DEF___FIKeyValuePair_2_IInspectable_IInspectable_USE
#define DEF___FIKeyValuePair_2_IInspectable_IInspectable_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("59e7ae0c-c29d-5ad6-bef5-dedb52a198e1"))
IKeyValuePair<IInspectable*,IInspectable*> : IKeyValuePair_impl<IInspectable*,IInspectable*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IKeyValuePair`2<Object, Object>"; }
};
typedef IKeyValuePair<IInspectable*,IInspectable*> __FIKeyValuePair_2_IInspectable_IInspectable_t;
#define ____FIKeyValuePair_2_IInspectable_IInspectable_FWD_DEFINED__
#define __FIKeyValuePair_2_IInspectable_IInspectable ABI::Windows::Foundation::Collections::__FIKeyValuePair_2_IInspectable_IInspectable_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIKeyValuePair_2_IInspectable_IInspectable_USE */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0016 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0016_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0016_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4723 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4723 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4723_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4723_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0017 */
/* [local] */ 

#ifndef DEF___FIIterator_1___FIKeyValuePair_2_IInspectable_IInspectable_USE
#define DEF___FIIterator_1___FIKeyValuePair_2_IInspectable_IInspectable_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("31e55e8a-0f05-52fd-90d3-b04aa331aaa4"))
IIterator<__FIKeyValuePair_2_IInspectable_IInspectable*> : IIterator_impl<__FIKeyValuePair_2_IInspectable_IInspectable*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IIterator`1<Windows.Foundation.Collections.IKeyValuePair`2<Object, Object>>"; }
};
typedef IIterator<__FIKeyValuePair_2_IInspectable_IInspectable*> __FIIterator_1___FIKeyValuePair_2_IInspectable_IInspectable_t;
#define ____FIIterator_1___FIKeyValuePair_2_IInspectable_IInspectable_FWD_DEFINED__
#define __FIIterator_1___FIKeyValuePair_2_IInspectable_IInspectable ABI::Windows::Foundation::Collections::__FIIterator_1___FIKeyValuePair_2_IInspectable_IInspectable_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIIterator_1___FIKeyValuePair_2_IInspectable_IInspectable_USE */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0017 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0017_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0017_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4724 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4724 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4724_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4724_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0018 */
/* [local] */ 

#ifndef DEF___FIIterable_1___FIKeyValuePair_2_IInspectable_IInspectable_USE
#define DEF___FIIterable_1___FIKeyValuePair_2_IInspectable_IInspectable_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("33ac68f0-1084-529a-8a17-4e7c8adb7a0c"))
IIterable<__FIKeyValuePair_2_IInspectable_IInspectable*> : IIterable_impl<__FIKeyValuePair_2_IInspectable_IInspectable*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IIterable`1<Windows.Foundation.Collections.IKeyValuePair`2<Object, Object>>"; }
};
typedef IIterable<__FIKeyValuePair_2_IInspectable_IInspectable*> __FIIterable_1___FIKeyValuePair_2_IInspectable_IInspectable_t;
#define ____FIIterable_1___FIKeyValuePair_2_IInspectable_IInspectable_FWD_DEFINED__
#define __FIIterable_1___FIKeyValuePair_2_IInspectable_IInspectable ABI::Windows::Foundation::Collections::__FIIterable_1___FIKeyValuePair_2_IInspectable_IInspectable_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIIterable_1___FIKeyValuePair_2_IInspectable_IInspectable_USE */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0018 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0018_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0018_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4725 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4725 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4725_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4725_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0019 */
/* [local] */ 

#ifndef DEF___FIMapView_2_IInspectable_IInspectable_USE
#define DEF___FIMapView_2_IInspectable_IInspectable_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("efe76d10-cb60-50ad-8a4f-6885cd6212a1"))
IMapView<IInspectable*,IInspectable*> : IMapView_impl<IInspectable*,IInspectable*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IMapView`2<Object, Object>"; }
};
typedef IMapView<IInspectable*,IInspectable*> __FIMapView_2_IInspectable_IInspectable_t;
#define ____FIMapView_2_IInspectable_IInspectable_FWD_DEFINED__
#define __FIMapView_2_IInspectable_IInspectable ABI::Windows::Foundation::Collections::__FIMapView_2_IInspectable_IInspectable_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIMapView_2_IInspectable_IInspectable_USE */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0019 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0019_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0019_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4726 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4726 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4726_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4726_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0020 */
/* [local] */ 

#ifndef DEF___FIMap_2_IInspectable_IInspectable_USE
#define DEF___FIMap_2_IInspectable_IInspectable_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("f5f69427-55ed-5512-8429-d4f6626dfcdd"))
IMap<IInspectable*,IInspectable*> : IMap_impl<IInspectable*,IInspectable*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IMap`2<Object, Object>"; }
};
typedef IMap<IInspectable*,IInspectable*> __FIMap_2_IInspectable_IInspectable_t;
#define ____FIMap_2_IInspectable_IInspectable_FWD_DEFINED__
#define __FIMap_2_IInspectable_IInspectable ABI::Windows::Foundation::Collections::__FIMap_2_IInspectable_IInspectable_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIMap_2_IInspectable_IInspectable_USE */
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

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveTextBlock;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveCard;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveImage;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveContainer;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveColumn;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif
#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveColumnSet;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextSize
    {
        TextSize_Small	= 0,
        TextSize_Normal	= ( TextSize_Small + 1 ) ,
        TextSize_Medium	= ( TextSize_Normal + 1 ) ,
        TextSize_Large	= ( TextSize_Medium + 1 ) ,
        TextSize_ExtraLarge	= ( TextSize_Large + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextSize __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextSize;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextWeight
    {
        TextWeight_Lighter	= 0,
        TextWeight_Normal	= ( TextWeight_Lighter + 1 ) ,
        TextWeight_Bolder	= ( TextWeight_Normal + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextWeight __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextWeight;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextColor
    {
        TextColor_Default	= 0,
        TextColor_Dark	= ( TextColor_Default + 1 ) ,
        TextColor_Light	= ( TextColor_Dark + 1 ) ,
        TextColor_Accent	= ( TextColor_Light + 1 ) ,
        TextColor_Good	= ( TextColor_Accent + 1 ) ,
        TextColor_Warning	= ( TextColor_Good + 1 ) ,
        TextColor_Attention	= ( TextColor_Warning + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextColor __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextColor;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CHAlignment
    {
        HAlignment_Left	= 0,
        HAlignment_Center	= ( HAlignment_Left + 1 ) ,
        HAlignment_Right	= ( HAlignment_Center + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CHAlignment __x_ABI_CAdaptiveCards_CXamlCardRenderer_CHAlignment;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CElementType
    {
        ElementType_Unsupported	= 0,
        ElementType_AdaptiveCard	= ( ElementType_Unsupported + 1 ) ,
        ElementType_TextBlock	= ( ElementType_AdaptiveCard + 1 ) ,
        ElementType_Image	= ( ElementType_TextBlock + 1 ) ,
        ElementType_Container	= ( ElementType_Image + 1 ) ,
        ElementType_Column	= ( ElementType_Container + 1 ) ,
        ElementType_ColumnSet	= ( ElementType_Column + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CElementType __x_ABI_CAdaptiveCards_CXamlCardRenderer_CElementType;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageStyle
    {
        ImageStyle_Normal	= 0,
        ImageStyle_Person	= ( ImageStyle_Normal + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageStyle __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageStyle;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageSize
    {
        ImageSize_Auto	= 0,
        ImageSize_Stretch	= ( ImageSize_Auto + 1 ) ,
        ImageSize_Small	= ( ImageSize_Stretch + 1 ) ,
        ImageSize_Medium	= ( ImageSize_Small + 1 ) ,
        ImageSize_Large	= ( ImageSize_Medium + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageSize __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageSize;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSeparationStyle
    {
        SeparationStyle_Default	= 0,
        SeparationStyle_None	= ( SeparationStyle_Default + 1 ) ,
        SeparationStyle_Strong	= ( SeparationStyle_None + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSeparationStyle __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSeparationStyle;


#endif /* end if !defined(__cplusplus) */


#endif


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0020 */
/* [local] */ 








#ifdef __cplusplus
} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            /* [v1_enum] */ 
            MIDL_ENUM TextSize
                {
                    Small	= 0,
                    Normal	= ( Small + 1 ) ,
                    Medium	= ( Normal + 1 ) ,
                    Large	= ( Medium + 1 ) ,
                    ExtraLarge	= ( Large + 1 ) 
                } ;

            const MIDL_ENUM TextSize TextSize_Small = TextSize::Small;
            const MIDL_ENUM TextSize TextSize_Normal = TextSize::Normal;
            const MIDL_ENUM TextSize TextSize_Medium = TextSize::Medium;
            const MIDL_ENUM TextSize TextSize_Large = TextSize::Large;
            const MIDL_ENUM TextSize TextSize_ExtraLarge = TextSize::ExtraLarge;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus

} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            typedef MIDL_ENUM TextSize TextSize;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus
} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            /* [v1_enum] */ 
            MIDL_ENUM TextWeight
                {
                    Lighter	= 0,
                    Normal	= ( Lighter + 1 ) ,
                    Bolder	= ( Normal + 1 ) 
                } ;

            const MIDL_ENUM TextWeight TextWeight_Lighter = TextWeight::Lighter;
            const MIDL_ENUM TextWeight TextWeight_Normal = TextWeight::Normal;
            const MIDL_ENUM TextWeight TextWeight_Bolder = TextWeight::Bolder;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus

} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            typedef MIDL_ENUM TextWeight TextWeight;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus
} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            /* [v1_enum] */ 
            MIDL_ENUM TextColor
                {
                    Default	= 0,
                    Dark	= ( Default + 1 ) ,
                    Light	= ( Dark + 1 ) ,
                    Accent	= ( Light + 1 ) ,
                    Good	= ( Accent + 1 ) ,
                    Warning	= ( Good + 1 ) ,
                    Attention	= ( Warning + 1 ) 
                } ;

            const MIDL_ENUM TextColor TextColor_Default = TextColor::Default;
            const MIDL_ENUM TextColor TextColor_Dark = TextColor::Dark;
            const MIDL_ENUM TextColor TextColor_Light = TextColor::Light;
            const MIDL_ENUM TextColor TextColor_Accent = TextColor::Accent;
            const MIDL_ENUM TextColor TextColor_Good = TextColor::Good;
            const MIDL_ENUM TextColor TextColor_Warning = TextColor::Warning;
            const MIDL_ENUM TextColor TextColor_Attention = TextColor::Attention;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus

} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            typedef MIDL_ENUM TextColor TextColor;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus
} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            /* [v1_enum] */ 
            MIDL_ENUM HAlignment
                {
                    Left	= 0,
                    Center	= ( Left + 1 ) ,
                    Right	= ( Center + 1 ) 
                } ;

            const MIDL_ENUM HAlignment HAlignment_Left = HAlignment::Left;
            const MIDL_ENUM HAlignment HAlignment_Center = HAlignment::Center;
            const MIDL_ENUM HAlignment HAlignment_Right = HAlignment::Right;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus

} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            typedef MIDL_ENUM HAlignment HAlignment;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus
} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            /* [v1_enum] */ 
            MIDL_ENUM ElementType
                {
                    Unsupported	= 0,
                    AdaptiveCard	= ( Unsupported + 1 ) ,
                    TextBlock	= ( AdaptiveCard + 1 ) ,
                    Image	= ( TextBlock + 1 ) ,
                    Container	= ( Image + 1 ) ,
                    Column	= ( Container + 1 ) ,
                    ColumnSet	= ( Column + 1 ) 
                } ;

            const MIDL_ENUM ElementType ElementType_Unsupported = ElementType::Unsupported;
            const MIDL_ENUM ElementType ElementType_AdaptiveCard = ElementType::AdaptiveCard;
            const MIDL_ENUM ElementType ElementType_TextBlock = ElementType::TextBlock;
            const MIDL_ENUM ElementType ElementType_Image = ElementType::Image;
            const MIDL_ENUM ElementType ElementType_Container = ElementType::Container;
            const MIDL_ENUM ElementType ElementType_Column = ElementType::Column;
            const MIDL_ENUM ElementType ElementType_ColumnSet = ElementType::ColumnSet;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus

} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            typedef MIDL_ENUM ElementType ElementType;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus
} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            /* [v1_enum] */ 
            MIDL_ENUM ImageStyle
                {
                    Normal	= 0,
                    Person	= ( Normal + 1 ) 
                } ;

            const MIDL_ENUM ImageStyle ImageStyle_Normal = ImageStyle::Normal;
            const MIDL_ENUM ImageStyle ImageStyle_Person = ImageStyle::Person;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus

} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            typedef MIDL_ENUM ImageStyle ImageStyle;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus
} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            /* [v1_enum] */ 
            MIDL_ENUM ImageSize
                {
                    Auto	= 0,
                    Stretch	= ( Auto + 1 ) ,
                    Small	= ( Stretch + 1 ) ,
                    Medium	= ( Small + 1 ) ,
                    Large	= ( Medium + 1 ) 
                } ;

            const MIDL_ENUM ImageSize ImageSize_Auto = ImageSize::Auto;
            const MIDL_ENUM ImageSize ImageSize_Stretch = ImageSize::Stretch;
            const MIDL_ENUM ImageSize ImageSize_Small = ImageSize::Small;
            const MIDL_ENUM ImageSize ImageSize_Medium = ImageSize::Medium;
            const MIDL_ENUM ImageSize ImageSize_Large = ImageSize::Large;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus

} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            typedef MIDL_ENUM ImageSize ImageSize;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus
} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            /* [v1_enum] */ 
            MIDL_ENUM SeparationStyle
                {
                    Default	= 0,
                    None	= ( Default + 1 ) ,
                    Strong	= ( None + 1 ) 
                } ;

            const MIDL_ENUM SeparationStyle SeparationStyle_Default = SeparationStyle::Default;
            const MIDL_ENUM SeparationStyle SeparationStyle_None = SeparationStyle::None;
            const MIDL_ENUM SeparationStyle SeparationStyle_Strong = SeparationStyle::Strong;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus

} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            typedef MIDL_ENUM SeparationStyle SeparationStyle;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0020_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0020_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4727 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4727 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4727_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4727_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0021 */
/* [local] */ 

#ifndef DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#define DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0021 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0021_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0021_v0_0_s_ifspec;

#ifndef ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__

/* interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */
/* [unique][uuid][object] */ 



/* interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ad869642-67ac-5b8d-8f6c-0d6d368f9394")
    __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement : public IInspectable
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Current( 
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement **current) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_HasCurrent( 
            /* [retval][out] */ boolean *hasCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveNext( 
            /* [retval][out] */ boolean *hasCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Current )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement **current);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasCurrent )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [retval][out] */ boolean *hasCurrent);
        
        HRESULT ( STDMETHODCALLTYPE *MoveNext )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [retval][out] */ boolean *hasCurrent);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement **items,
            /* [retval][out] */ unsigned int *actual);
        
        END_INTERFACE
    } __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl;

    interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
    {
        CONST_VTBL struct __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_get_Current(This,current)	\
    ( (This)->lpVtbl -> get_Current(This,current) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_get_HasCurrent(This,hasCurrent)	\
    ( (This)->lpVtbl -> get_HasCurrent(This,hasCurrent) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_MoveNext(This,hasCurrent)	\
    ( (This)->lpVtbl -> MoveNext(This,hasCurrent) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetMany(This,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,capacity,items,actual) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0022 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0022 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0022_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0022_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4728 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4728 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4728_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4728_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0023 */
/* [local] */ 

#ifndef DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#define DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0023 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0023_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0023_v0_0_s_ifspec;

#ifndef ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__

/* interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */
/* [unique][uuid][object] */ 



/* interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d9517a3e-61be-5d41-ae61-f944c5dcd00e")
    __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE First( 
            /* [retval][out] */ __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement **first) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *First )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [retval][out] */ __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement **first);
        
        END_INTERFACE
    } __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl;

    interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
    {
        CONST_VTBL struct __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_First(This,first)	\
    ( (This)->lpVtbl -> First(This,first) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0024 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0024 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0024_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0024_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4729 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4729 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4729_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4729_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0025 */
/* [local] */ 

#ifndef DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#define DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0025 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0025_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0025_v0_0_s_ifspec;

#ifndef ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__

/* interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */
/* [unique][uuid][object] */ 



/* interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("cc2a09d0-2290-5837-9948-78caf849cba5")
    __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAt( 
            /* [in] */ unsigned int index,
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement **item) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ unsigned int *size) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IndexOf( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *GetAt )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ unsigned int index,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement **item);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [retval][out] */ unsigned int *size);
        
        HRESULT ( STDMETHODCALLTYPE *IndexOf )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement **items,
            /* [retval][out] */ unsigned int *actual);
        
        END_INTERFACE
    } __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl;

    interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
    {
        CONST_VTBL struct __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetAt(This,index,item)	\
    ( (This)->lpVtbl -> GetAt(This,index,item) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_get_Size(This,size)	\
    ( (This)->lpVtbl -> get_Size(This,size) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_IndexOf(This,item,index,found)	\
    ( (This)->lpVtbl -> IndexOf(This,item,index,found) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetMany(This,startIndex,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,startIndex,capacity,items,actual) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0026 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0026 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0026_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0026_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4730 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4730 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4730_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4730_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0027 */
/* [local] */ 

#ifndef DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#define DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0027 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0027_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0027_v0_0_s_ifspec;

#ifndef ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__

/* interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */
/* [unique][uuid][object] */ 



/* interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("71051658-3679-58b1-a6f3-52269536b48b")
    __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAt( 
            /* [in] */ unsigned int index,
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement **item) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ unsigned int *size) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetView( 
            /* [retval][out] */ __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement **view) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IndexOf( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAt( 
            /* [in] */ unsigned int index,
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InsertAt( 
            /* [in] */ unsigned int index,
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAt( 
            /* [in] */ unsigned int index) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Append( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAtEnd( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReplaceAll( 
            /* [in] */ unsigned int count,
            /* [size_is][in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement **value) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *GetAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ unsigned int index,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement **item);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [retval][out] */ unsigned int *size);
        
        HRESULT ( STDMETHODCALLTYPE *GetView )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [retval][out] */ __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement **view);
        
        HRESULT ( STDMETHODCALLTYPE *IndexOf )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found);
        
        HRESULT ( STDMETHODCALLTYPE *SetAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ unsigned int index,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement *item);
        
        HRESULT ( STDMETHODCALLTYPE *InsertAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ unsigned int index,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement *item);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ unsigned int index);
        
        HRESULT ( STDMETHODCALLTYPE *Append )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement *item);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveAtEnd )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clear )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement **items,
            /* [retval][out] */ unsigned int *actual);
        
        HRESULT ( STDMETHODCALLTYPE *ReplaceAll )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ unsigned int count,
            /* [size_is][in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement **value);
        
        END_INTERFACE
    } __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl;

    interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
    {
        CONST_VTBL struct __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetAt(This,index,item)	\
    ( (This)->lpVtbl -> GetAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_get_Size(This,size)	\
    ( (This)->lpVtbl -> get_Size(This,size) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetView(This,view)	\
    ( (This)->lpVtbl -> GetView(This,view) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_IndexOf(This,item,index,found)	\
    ( (This)->lpVtbl -> IndexOf(This,item,index,found) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_SetAt(This,index,item)	\
    ( (This)->lpVtbl -> SetAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_InsertAt(This,index,item)	\
    ( (This)->lpVtbl -> InsertAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_RemoveAt(This,index)	\
    ( (This)->lpVtbl -> RemoveAt(This,index) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_Append(This,item)	\
    ( (This)->lpVtbl -> Append(This,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_RemoveAtEnd(This)	\
    ( (This)->lpVtbl -> RemoveAtEnd(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetMany(This,startIndex,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,startIndex,capacity,items,actual) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_ReplaceAll(This,count,value)	\
    ( (This)->lpVtbl -> ReplaceAll(This,count,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0028 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0028 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0028_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0028_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4731 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4731 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4731_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4731_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0029 */
/* [local] */ 

#ifndef DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#define DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0029 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0029_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0029_v0_0_s_ifspec;

#ifndef ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__

/* interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */
/* [unique][uuid][object] */ 



/* interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("177b1a85-afd6-5364-8def-fcc95592e900")
    __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn : public IInspectable
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Current( 
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn **current) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_HasCurrent( 
            /* [retval][out] */ boolean *hasCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveNext( 
            /* [retval][out] */ boolean *hasCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Current )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn **current);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasCurrent )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [retval][out] */ boolean *hasCurrent);
        
        HRESULT ( STDMETHODCALLTYPE *MoveNext )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [retval][out] */ boolean *hasCurrent);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn **items,
            /* [retval][out] */ unsigned int *actual);
        
        END_INTERFACE
    } __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl;

    interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
    {
        CONST_VTBL struct __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_get_Current(This,current)	\
    ( (This)->lpVtbl -> get_Current(This,current) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_get_HasCurrent(This,hasCurrent)	\
    ( (This)->lpVtbl -> get_HasCurrent(This,hasCurrent) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_MoveNext(This,hasCurrent)	\
    ( (This)->lpVtbl -> MoveNext(This,hasCurrent) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetMany(This,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,capacity,items,actual) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0030 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0030 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0030_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0030_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4732 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4732 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4732_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4732_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0031 */
/* [local] */ 

#ifndef DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#define DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0031 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0031_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0031_v0_0_s_ifspec;

#ifndef ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__

/* interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */
/* [unique][uuid][object] */ 



/* interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a16a1a57-e954-59b5-bbf7-9813bec6cf90")
    __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE First( 
            /* [retval][out] */ __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn **first) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *First )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [retval][out] */ __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn **first);
        
        END_INTERFACE
    } __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl;

    interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
    {
        CONST_VTBL struct __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_First(This,first)	\
    ( (This)->lpVtbl -> First(This,first) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0032 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0032 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0032_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0032_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4733 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4733 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4733_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4733_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0033 */
/* [local] */ 

#ifndef DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#define DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0033 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0033_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0033_v0_0_s_ifspec;

#ifndef ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__

/* interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */
/* [unique][uuid][object] */ 



/* interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00890892-b06d-5203-ae15-2d85b293a22b")
    __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAt( 
            /* [in] */ unsigned int index,
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn **item) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ unsigned int *size) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IndexOf( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *GetAt )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ unsigned int index,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn **item);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [retval][out] */ unsigned int *size);
        
        HRESULT ( STDMETHODCALLTYPE *IndexOf )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn **items,
            /* [retval][out] */ unsigned int *actual);
        
        END_INTERFACE
    } __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl;

    interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
    {
        CONST_VTBL struct __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetAt(This,index,item)	\
    ( (This)->lpVtbl -> GetAt(This,index,item) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_get_Size(This,size)	\
    ( (This)->lpVtbl -> get_Size(This,size) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_IndexOf(This,item,index,found)	\
    ( (This)->lpVtbl -> IndexOf(This,item,index,found) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetMany(This,startIndex,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,startIndex,capacity,items,actual) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0034 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0034 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0034_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0034_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4734 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4734 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4734_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4734_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0035 */
/* [local] */ 

#ifndef DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#define DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0035 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0035_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0035_v0_0_s_ifspec;

#ifndef ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__

/* interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */
/* [unique][uuid][object] */ 



/* interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8d7fcc96-66f7-519f-a795-168988436cac")
    __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAt( 
            /* [in] */ unsigned int index,
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn **item) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ unsigned int *size) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetView( 
            /* [retval][out] */ __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn **view) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IndexOf( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAt( 
            /* [in] */ unsigned int index,
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InsertAt( 
            /* [in] */ unsigned int index,
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAt( 
            /* [in] */ unsigned int index) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Append( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAtEnd( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReplaceAll( 
            /* [in] */ unsigned int count,
            /* [size_is][in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn **value) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *GetAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ unsigned int index,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn **item);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [retval][out] */ unsigned int *size);
        
        HRESULT ( STDMETHODCALLTYPE *GetView )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [retval][out] */ __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn **view);
        
        HRESULT ( STDMETHODCALLTYPE *IndexOf )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found);
        
        HRESULT ( STDMETHODCALLTYPE *SetAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ unsigned int index,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn *item);
        
        HRESULT ( STDMETHODCALLTYPE *InsertAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ unsigned int index,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn *item);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ unsigned int index);
        
        HRESULT ( STDMETHODCALLTYPE *Append )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn *item);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveAtEnd )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clear )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn **items,
            /* [retval][out] */ unsigned int *actual);
        
        HRESULT ( STDMETHODCALLTYPE *ReplaceAll )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ unsigned int count,
            /* [size_is][in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn **value);
        
        END_INTERFACE
    } __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl;

    interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
    {
        CONST_VTBL struct __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetAt(This,index,item)	\
    ( (This)->lpVtbl -> GetAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_get_Size(This,size)	\
    ( (This)->lpVtbl -> get_Size(This,size) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetView(This,view)	\
    ( (This)->lpVtbl -> GetView(This,view) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_IndexOf(This,item,index,found)	\
    ( (This)->lpVtbl -> IndexOf(This,item,index,found) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_SetAt(This,index,item)	\
    ( (This)->lpVtbl -> SetAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_InsertAt(This,index,item)	\
    ( (This)->lpVtbl -> InsertAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_RemoveAt(This,index)	\
    ( (This)->lpVtbl -> RemoveAt(This,index) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_Append(This,item)	\
    ( (This)->lpVtbl -> Append(This,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_RemoveAtEnd(This)	\
    ( (This)->lpVtbl -> RemoveAtEnd(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetMany(This,startIndex,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,startIndex,capacity,items,actual) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_ReplaceAll(This,count,value)	\
    ( (This)->lpVtbl -> ReplaceAll(This,count,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0036 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0036 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0036_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0036_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4735 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4735 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4735_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4735_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0037 */
/* [local] */ 

#ifndef DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#define DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)



/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0037 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0037_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0037_v0_0_s_ifspec;

#ifndef ____FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__
#define ____FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__

/* interface __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */
/* [unique][uuid][object] */ 



/* interface __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8d9d7686-ac0d-5cb7-8382-571a335cf05b")
    __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Invoke( 
            /* [in] */ __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement *sender,
            /* [in] */ ABI::Windows::Foundation::Collections::IVectorChangedEventArgs *e) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement *sender,
            /* [in] */ __x_ABI_CWindows_CFoundation_CCollections_CIVectorChangedEventArgs *e);
        
        END_INTERFACE
    } __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl;

    interface __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
    {
        CONST_VTBL struct __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_Invoke(This,sender,e)	\
    ( (This)->lpVtbl -> Invoke(This,sender,e) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0038 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0038 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0038_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0038_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4736 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4736 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4736_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4736_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0039 */
/* [local] */ 

#ifndef DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#define DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0039 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0039_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0039_v0_0_s_ifspec;

#ifndef ____FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__
#define ____FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__

/* interface __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */
/* [unique][uuid][object] */ 



/* interface __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5686deef-094a-53f8-a070-ce563eeefa1f")
    __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE add_VectorChanged( 
            /* [in] */ __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement *handler,
            /* [retval][out] */ EventRegistrationToken *token) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE remove_VectorChanged( 
            /* [in] */ EventRegistrationToken token) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *add_VectorChanged )( 
            __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement *handler,
            /* [retval][out] */ EventRegistrationToken *token);
        
        HRESULT ( STDMETHODCALLTYPE *remove_VectorChanged )( 
            __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement * This,
            /* [in] */ EventRegistrationToken token);
        
        END_INTERFACE
    } __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl;

    interface __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
    {
        CONST_VTBL struct __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_add_VectorChanged(This,handler,token)	\
    ( (This)->lpVtbl -> add_VectorChanged(This,handler,token) ) 

#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_remove_VectorChanged(This,token)	\
    ( (This)->lpVtbl -> remove_VectorChanged(This,token) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0040 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0040 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0040_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0040_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4737 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4737 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4737_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4737_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0041 */
/* [local] */ 

#ifndef DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#define DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)



/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0041 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0041_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0041_v0_0_s_ifspec;

#ifndef ____FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__
#define ____FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__

/* interface __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */
/* [unique][uuid][object] */ 



/* interface __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0de4579a-0022-5241-8788-7d0d8f30707e")
    __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Invoke( 
            /* [in] */ __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn *sender,
            /* [in] */ ABI::Windows::Foundation::Collections::IVectorChangedEventArgs *e) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This);
        
        HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn *sender,
            /* [in] */ __x_ABI_CWindows_CFoundation_CCollections_CIVectorChangedEventArgs *e);
        
        END_INTERFACE
    } __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl;

    interface __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
    {
        CONST_VTBL struct __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_Invoke(This,sender,e)	\
    ( (This)->lpVtbl -> Invoke(This,sender,e) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0042 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0042 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0042_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0042_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4738 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4738 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4738_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4738_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0043 */
/* [local] */ 

#ifndef DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#define DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0043 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0043_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0043_v0_0_s_ifspec;

#ifndef ____FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__
#define ____FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__

/* interface __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */
/* [unique][uuid][object] */ 



/* interface __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5aa87e1f-0282-53de-ae2c-7b5b90d9679b")
    __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE add_VectorChanged( 
            /* [in] */ __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn *handler,
            /* [retval][out] */ EventRegistrationToken *token) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE remove_VectorChanged( 
            /* [in] */ EventRegistrationToken token) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *add_VectorChanged )( 
            __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ __FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn *handler,
            /* [retval][out] */ EventRegistrationToken *token);
        
        HRESULT ( STDMETHODCALLTYPE *remove_VectorChanged )( 
            __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn * This,
            /* [in] */ EventRegistrationToken token);
        
        END_INTERFACE
    } __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl;

    interface __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
    {
        CONST_VTBL struct __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumnVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_add_VectorChanged(This,handler,token)	\
    ( (This)->lpVtbl -> add_VectorChanged(This,handler,token) ) 

#define __FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_remove_VectorChanged(This,token)	\
    ( (This)->lpVtbl -> remove_VectorChanged(This,token) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0044 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0044 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0044_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0044_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4739 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4739 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4739_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4739_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0045 */
/* [local] */ 

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement
#define DEF___FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)



/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0045 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0045_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0045_v0_0_s_ifspec;

#ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement_INTERFACE_DEFINED__
#define ____FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement_INTERFACE_DEFINED__

/* interface __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement */
/* [unique][uuid][object] */ 



/* interface __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a080f956-aced-5764-9f05-fb1f443729aa")
    __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Invoke( 
            /* [in] */ __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement *asyncInfo,
            /* [in] */ AsyncStatus status) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement * This,
            /* [in] */ __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement *asyncInfo,
            /* [in] */ AsyncStatus status);
        
        END_INTERFACE
    } __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElementVtbl;

    interface __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement
    {
        CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement_Invoke(This,asyncInfo,status)	\
    ( (This)->lpVtbl -> Invoke(This,asyncInfo,status) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0046 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0046 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0046_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0046_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4740 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4740 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4740_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4740_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0047 */
/* [local] */ 

#ifndef DEF___FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement
#define DEF___FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0047 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0047_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0047_v0_0_s_ifspec;

#ifndef ____FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_INTERFACE_DEFINED__
#define ____FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_INTERFACE_DEFINED__

/* interface __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement */
/* [unique][uuid][object] */ 



/* interface __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a41e0c0e-fb5e-5b57-ac81-f128277be260")
    __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement : public IInspectable
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Completed( 
            /* [in] */ __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement *handler) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Completed( 
            /* [retval][out] */ __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement **handler) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetResults( 
            /* [retval][out] */ ABI::Windows::UI::Xaml::IUIElement **results) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Completed )( 
            __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement * This,
            /* [in] */ __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement *handler);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Completed )( 
            __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement * This,
            /* [retval][out] */ __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement **handler);
        
        HRESULT ( STDMETHODCALLTYPE *GetResults )( 
            __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement * This,
            /* [retval][out] */ __x_ABI_CWindows_CUI_CXaml_CIUIElement **results);
        
        END_INTERFACE
    } __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElementVtbl;

    interface __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement
    {
        CONST_VTBL struct __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_put_Completed(This,handler)	\
    ( (This)->lpVtbl -> put_Completed(This,handler) ) 

#define __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_get_Completed(This,handler)	\
    ( (This)->lpVtbl -> get_Completed(This,handler) ) 

#define __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_GetResults(This,results)	\
    ( (This)->lpVtbl -> GetResults(This,results) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0048 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0048 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0048_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0048_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4741 */




/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4741 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4741_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer2Eidl_0000_4741_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0049 */
/* [local] */ 

#ifndef DEF___FIReference_1_Windows__CUI__CText__CFontWeight
#define DEF___FIReference_1_Windows__CUI__CText__CFontWeight
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0049 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0049_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0049_v0_0_s_ifspec;

#ifndef ____FIReference_1_Windows__CUI__CText__CFontWeight_INTERFACE_DEFINED__
#define ____FIReference_1_Windows__CUI__CText__CFontWeight_INTERFACE_DEFINED__

/* interface __FIReference_1_Windows__CUI__CText__CFontWeight */
/* [unique][uuid][object] */ 



/* interface __FIReference_1_Windows__CUI__CText__CFontWeight */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIReference_1_Windows__CUI__CText__CFontWeight;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("741446b3-9c81-5daa-b995-5bd67473492c")
    __FIReference_1_Windows__CUI__CText__CFontWeight : public IInspectable
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ struct ABI::Windows::UI::Text::FontWeight *value) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIReference_1_Windows__CUI__CText__CFontWeightVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIReference_1_Windows__CUI__CText__CFontWeight * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIReference_1_Windows__CUI__CText__CFontWeight * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIReference_1_Windows__CUI__CText__CFontWeight * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIReference_1_Windows__CUI__CText__CFontWeight * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIReference_1_Windows__CUI__CText__CFontWeight * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIReference_1_Windows__CUI__CText__CFontWeight * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            __FIReference_1_Windows__CUI__CText__CFontWeight * This,
            /* [retval][out] */ struct __x_ABI_CWindows_CUI_CText_CFontWeight *value);
        
        END_INTERFACE
    } __FIReference_1_Windows__CUI__CText__CFontWeightVtbl;

    interface __FIReference_1_Windows__CUI__CText__CFontWeight
    {
        CONST_VTBL struct __FIReference_1_Windows__CUI__CText__CFontWeightVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIReference_1_Windows__CUI__CText__CFontWeight_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIReference_1_Windows__CUI__CText__CFontWeight_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIReference_1_Windows__CUI__CText__CFontWeight_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIReference_1_Windows__CUI__CText__CFontWeight_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIReference_1_Windows__CUI__CText__CFontWeight_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIReference_1_Windows__CUI__CText__CFontWeight_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIReference_1_Windows__CUI__CText__CFontWeight_get_Value(This,value)	\
    ( (This)->lpVtbl -> get_Value(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIReference_1_Windows__CUI__CText__CFontWeight_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0050 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIReference_1_Windows__CUI__CText__CFontWeight */
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveCardElement[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveCardElement";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0050 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0050_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0050_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("74D69C2F-7F1C-47FD-A319-F4B4E7F72EE9")
                IAdaptiveCardElement : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ElementType( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ElementType *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Speak( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Speak( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Separation( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Separation( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveCardElement = __uuidof(IAdaptiveCardElement);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ElementType )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CElementType *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Speak )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Speak )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Separation )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSeparationStyle *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Separation )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSeparationStyle value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElementVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_get_ElementType(This,value)	\
    ( (This)->lpVtbl -> get_ElementType(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_get_Speak(This,value)	\
    ( (This)->lpVtbl -> get_Speak(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_put_Speak(This,value)	\
    ( (This)->lpVtbl -> put_Speak(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_get_Separation(This,value)	\
    ( (This)->lpVtbl -> get_Separation(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_put_Separation(This,value)	\
    ( (This)->lpVtbl -> put_Separation(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0051 */
/* [local] */ 

#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveTextBlock[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveTextBlock";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0051 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0051_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0051_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextBlock */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("f3b844da-2d6a-4003-8a57-4e5541fcd078")
                IAdaptiveTextBlock : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::TextSize *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Size( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::TextSize value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Weight( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::TextWeight *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Weight( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::TextWeight value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Color( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::TextColor *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Color( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::TextColor value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Text( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Text( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_IsSubtle( 
                        /* [out][retval] */ boolean *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_IsSubtle( 
                        /* [in] */ boolean value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Wrap( 
                        /* [out][retval] */ boolean *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Wrap( 
                        /* [in] */ boolean value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_HorizontalAlignment( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::HAlignment *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_HorizontalAlignment( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::HAlignment value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MaxLines( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MaxLines( 
                        /* [in] */ UINT32 value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveTextBlock = __uuidof(IAdaptiveTextBlock);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlockVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextSize *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Size )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextSize value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Weight )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextWeight *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Weight )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextWeight value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextColor *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextColor value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Text )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Text )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSubtle )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [out][retval] */ boolean *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsSubtle )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [in] */ boolean value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Wrap )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [out][retval] */ boolean *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Wrap )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [in] */ boolean value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_HorizontalAlignment )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CHAlignment *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_HorizontalAlignment )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CHAlignment value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxLines )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxLines )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [in] */ UINT32 value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlockVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlockVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_get_Size(This,value)	\
    ( (This)->lpVtbl -> get_Size(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_put_Size(This,value)	\
    ( (This)->lpVtbl -> put_Size(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_get_Weight(This,value)	\
    ( (This)->lpVtbl -> get_Weight(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_put_Weight(This,value)	\
    ( (This)->lpVtbl -> put_Weight(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_get_Color(This,value)	\
    ( (This)->lpVtbl -> get_Color(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_put_Color(This,value)	\
    ( (This)->lpVtbl -> put_Color(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_get_Text(This,value)	\
    ( (This)->lpVtbl -> get_Text(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_put_Text(This,value)	\
    ( (This)->lpVtbl -> put_Text(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_get_IsSubtle(This,value)	\
    ( (This)->lpVtbl -> get_IsSubtle(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_put_IsSubtle(This,value)	\
    ( (This)->lpVtbl -> put_IsSubtle(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_get_Wrap(This,value)	\
    ( (This)->lpVtbl -> get_Wrap(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_put_Wrap(This,value)	\
    ( (This)->lpVtbl -> put_Wrap(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_get_HorizontalAlignment(This,value)	\
    ( (This)->lpVtbl -> get_HorizontalAlignment(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_put_HorizontalAlignment(This,value)	\
    ( (This)->lpVtbl -> put_HorizontalAlignment(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_get_MaxLines(This,value)	\
    ( (This)->lpVtbl -> get_MaxLines(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_put_MaxLines(This,value)	\
    ( (This)->lpVtbl -> put_MaxLines(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0052 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveTextBlock_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveTextBlock_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveTextBlock[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveTextBlock";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveCard[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveCard";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0052 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0052_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0052_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("9F68A612-9DCB-4710-8121-A116BD33B69B")
                IAdaptiveCard : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Body( 
                        /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement **value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ElementType( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ElementType *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Version( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MinVersion( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MinVersion( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_FallbackText( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_FallbackText( 
                        /* [in] */ HSTRING value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveCard = __uuidof(IAdaptiveCard);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Body )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement **value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ElementType )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CElementType *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Version )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinVersion )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_MinVersion )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_FallbackText )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_FallbackText )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [in] */ HSTRING value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_get_Body(This,value)	\
    ( (This)->lpVtbl -> get_Body(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_get_ElementType(This,value)	\
    ( (This)->lpVtbl -> get_ElementType(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_get_Version(This,value)	\
    ( (This)->lpVtbl -> get_Version(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_put_Version(This,value)	\
    ( (This)->lpVtbl -> put_Version(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_get_MinVersion(This,value)	\
    ( (This)->lpVtbl -> get_MinVersion(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_put_MinVersion(This,value)	\
    ( (This)->lpVtbl -> put_MinVersion(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_get_FallbackText(This,value)	\
    ( (This)->lpVtbl -> get_FallbackText(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_put_FallbackText(This,value)	\
    ( (This)->lpVtbl -> put_FallbackText(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0053 */
/* [local] */ 

#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveCardStatics[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveCardStatics";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0053 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0053_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0053_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardStatics */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("C312AD20-DFE3-4418-819F-E3CB7A0CD2FE")
                IAdaptiveCardStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE CreateCardFromJson( 
                        /* [in] */ HSTRING adaptiveJson,
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard **card) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveCardStatics = __uuidof(IAdaptiveCardStatics);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStaticsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *CreateCardFromJson )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics * This,
            /* [in] */ HSTRING adaptiveJson,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard **card);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStaticsVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStaticsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_CreateCardFromJson(This,adaptiveJson,card)	\
    ( (This)->lpVtbl -> CreateCardFromJson(This,adaptiveJson,card) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0054 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveCard_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveCard_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveCard[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveCard";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveImage[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveImage";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0054 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0054_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0054_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("16452a2e-1152-47f3-90bd-6e4148b09669")
                IAdaptiveImage : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Url( 
                        /* [out][retval] */ ABI::Windows::Foundation::IUriRuntimeClass **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Url( 
                        /* [in] */ ABI::Windows::Foundation::IUriRuntimeClass *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Style( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ImageStyle *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Style( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ImageStyle value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ImageSize *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Size( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ImageSize value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_HorizontalAlignment( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::HAlignment *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_HorizontalAlignment( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::HAlignment value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_AltText( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_AltText( 
                        /* [in] */ HSTRING value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveImage = __uuidof(IAdaptiveImage);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Url )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage * This,
            /* [out][retval] */ __x_ABI_CWindows_CFoundation_CIUriRuntimeClass **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Url )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage * This,
            /* [in] */ __x_ABI_CWindows_CFoundation_CIUriRuntimeClass *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageStyle *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageStyle value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageSize *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Size )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageSize value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_HorizontalAlignment )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CHAlignment *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_HorizontalAlignment )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CHAlignment value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_AltText )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_AltText )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage * This,
            /* [in] */ HSTRING value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_get_Url(This,value)	\
    ( (This)->lpVtbl -> get_Url(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_put_Url(This,value)	\
    ( (This)->lpVtbl -> put_Url(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_get_Style(This,value)	\
    ( (This)->lpVtbl -> get_Style(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_put_Style(This,value)	\
    ( (This)->lpVtbl -> put_Style(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_get_Size(This,value)	\
    ( (This)->lpVtbl -> get_Size(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_put_Size(This,value)	\
    ( (This)->lpVtbl -> put_Size(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_get_HorizontalAlignment(This,value)	\
    ( (This)->lpVtbl -> get_HorizontalAlignment(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_put_HorizontalAlignment(This,value)	\
    ( (This)->lpVtbl -> put_HorizontalAlignment(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_get_AltText(This,value)	\
    ( (This)->lpVtbl -> get_AltText(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_put_AltText(This,value)	\
    ( (This)->lpVtbl -> put_AltText(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0055 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveImage_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveImage_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveImage[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveImage";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveContainer[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveContainer";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0055 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0055_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0055_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainer */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("ba90da3f-556c-4e3a-9d01-11f2ce78dcd7")
                IAdaptiveContainer : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Items( 
                        /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement **value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveContainer = __uuidof(IAdaptiveContainer);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Items )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer * This,
            /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement **value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_get_Items(This,value)	\
    ( (This)->lpVtbl -> get_Items(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0056 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveContainer_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveContainer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveContainer[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveContainer";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveColumn[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveColumn";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0056 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0056_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0056_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("91e03800-d239-43bc-b5fb-2ccfe0cc7fcb")
                IAdaptiveColumn : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Size( 
                        /* [in] */ HSTRING value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveColumn = __uuidof(IAdaptiveColumn);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Size )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn * This,
            /* [in] */ HSTRING value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_get_Size(This,value)	\
    ( (This)->lpVtbl -> get_Size(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_put_Size(This,value)	\
    ( (This)->lpVtbl -> put_Size(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0057 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveColumn_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveColumn_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveColumn[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveColumn";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveColumnSet[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveColumnSet";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0057 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0057_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0057_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumnSet */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("4e3e1cd1-906b-4718-96ea-0a6e16bf0199")
                IAdaptiveColumnSet : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Columns( 
                        /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn **value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveColumnSet = __uuidof(IAdaptiveColumnSet);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Columns )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet * This,
            /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn **value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSetVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_get_Columns(This,value)	\
    ( (This)->lpVtbl -> get_Columns(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0058 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveColumnSet_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveColumnSet_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveColumnSet[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveColumnSet";
#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CRenderOptions
    {
        RenderOptions_None	= 0,
        RenderOptions_SupportsActionBar	= 0x1,
        RenderOptions_SupportsInlineActions	= 0x2
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CRenderOptions __x_ABI_CAdaptiveCards_CXamlCardRenderer_CRenderOptions;


#endif /* end if !defined(__cplusplus) */


#else
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
#if defined(MIDL_ENUM)
typedef MIDL_ENUM RenderOptions RenderOptions;
#else
typedef enum class RenderOptions RenderOptions;
#endif
DEFINE_ENUM_FLAG_OPERATORS(RenderOptions)
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IXamlCardRenderer[] = L"AdaptiveCards.XamlCardRenderer.IXamlCardRenderer";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0058 */
/* [local] */ 

#ifdef __cplusplus
} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            /* [v1_enum] */ 
            MIDL_ENUM RenderOptions
                {
                    None	= 0,
                    SupportsActionBar	= 0x1,
                    SupportsInlineActions	= 0x2
                } ;

            const MIDL_ENUM RenderOptions RenderOptions_None = RenderOptions::None;
            const MIDL_ENUM RenderOptions RenderOptions_SupportsActionBar = RenderOptions::SupportsActionBar;
            const MIDL_ENUM RenderOptions RenderOptions_SupportsInlineActions = RenderOptions::SupportsInlineActions;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus

} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            
            typedef MIDL_ENUM RenderOptions RenderOptions;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0058_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0058_v0_0_s_ifspec;

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
                    virtual HRESULT STDMETHODCALLTYPE SetRenderOptions( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::RenderOptions options) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE SetOverrideStyles( 
                        /* [in] */ ABI::Windows::UI::Xaml::IResourceDictionary *overrideDictionary) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE RenderCardAsXaml( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard *adaptiveCard,
                        /* [out][retval] */ ABI::Windows::UI::Xaml::IUIElement **result) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE RenderCardAsXamlAsync( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard *adaptiveCard,
                        /* [out][retval] */ __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement **result) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE RenderAdaptiveJsonAsXaml( 
                        /* [in] */ HSTRING adaptiveJson,
                        /* [out][retval] */ ABI::Windows::UI::Xaml::IUIElement **result) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE RenderAdaptiveJsonAsXamlAsync( 
                        /* [in] */ HSTRING adaptiveJson,
                        /* [out][retval] */ __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement **result) = 0;
                    
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
        
        HRESULT ( STDMETHODCALLTYPE *SetRenderOptions )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CRenderOptions options);
        
        HRESULT ( STDMETHODCALLTYPE *SetOverrideStyles )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [in] */ __x_ABI_CWindows_CUI_CXaml_CIResourceDictionary *overrideDictionary);
        
        HRESULT ( STDMETHODCALLTYPE *RenderCardAsXaml )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard *adaptiveCard,
            /* [out][retval] */ __x_ABI_CWindows_CUI_CXaml_CIUIElement **result);
        
        HRESULT ( STDMETHODCALLTYPE *RenderCardAsXamlAsync )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard *adaptiveCard,
            /* [out][retval] */ __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement **result);
        
        HRESULT ( STDMETHODCALLTYPE *RenderAdaptiveJsonAsXaml )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [in] */ HSTRING adaptiveJson,
            /* [out][retval] */ __x_ABI_CWindows_CUI_CXaml_CIUIElement **result);
        
        HRESULT ( STDMETHODCALLTYPE *RenderAdaptiveJsonAsXamlAsync )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [in] */ HSTRING adaptiveJson,
            /* [out][retval] */ __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement **result);
        
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


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_SetRenderOptions(This,options)	\
    ( (This)->lpVtbl -> SetRenderOptions(This,options) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_SetOverrideStyles(This,overrideDictionary)	\
    ( (This)->lpVtbl -> SetOverrideStyles(This,overrideDictionary) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_RenderCardAsXaml(This,adaptiveCard,result)	\
    ( (This)->lpVtbl -> RenderCardAsXaml(This,adaptiveCard,result) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_RenderCardAsXamlAsync(This,adaptiveCard,result)	\
    ( (This)->lpVtbl -> RenderCardAsXamlAsync(This,adaptiveCard,result) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_RenderAdaptiveJsonAsXaml(This,adaptiveJson,result)	\
    ( (This)->lpVtbl -> RenderAdaptiveJsonAsXaml(This,adaptiveJson,result) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_RenderAdaptiveJsonAsXamlAsync(This,adaptiveJson,result)	\
    ( (This)->lpVtbl -> RenderAdaptiveJsonAsXamlAsync(This,adaptiveJson,result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0059 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_XamlCardRenderer_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_XamlCardRenderer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_XamlCardRenderer[] = L"AdaptiveCards.XamlCardRenderer.XamlCardRenderer";
#endif


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0059 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0059_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0059_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  HSTRING_UserSize(     unsigned long *, unsigned long            , HSTRING * ); 
unsigned char * __RPC_USER  HSTRING_UserMarshal(  unsigned long *, unsigned char *, HSTRING * ); 
unsigned char * __RPC_USER  HSTRING_UserUnmarshal(unsigned long *, unsigned char *, HSTRING * ); 
void                      __RPC_USER  HSTRING_UserFree(     unsigned long *, HSTRING * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


