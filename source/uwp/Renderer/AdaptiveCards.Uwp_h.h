

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for C:\Users\riarenas\AppData\Local\Temp\AdaptiveCards.Uwp.idl-3f84932d:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
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

#ifndef __AdaptiveCards2EUwp_h_h__
#define __AdaptiveCards2EUwp_h_h__

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


#ifndef ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_FWD_DEFINED__
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_FWD_DEFINED__
typedef interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement;

#endif 	/* ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_FWD_DEFINED__ */


#ifndef ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_FWD_DEFINED__
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_FWD_DEFINED__
typedef interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement;

#endif 	/* ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_FWD_DEFINED__ */


#ifndef ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_FWD_DEFINED__
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_FWD_DEFINED__
typedef interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement;

#endif 	/* ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_FWD_DEFINED__ */


#ifndef ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_FWD_DEFINED__
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_FWD_DEFINED__
typedef interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement;

#endif 	/* ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_FWD_DEFINED__ */


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


#ifndef ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_FWD_DEFINED__
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_FWD_DEFINED__
typedef interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact;

#endif 	/* ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_FWD_DEFINED__ */


#ifndef ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_FWD_DEFINED__
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_FWD_DEFINED__
typedef interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact;

#endif 	/* ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_FWD_DEFINED__ */


#ifndef ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_FWD_DEFINED__
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_FWD_DEFINED__
typedef interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact;

#endif 	/* ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_FWD_DEFINED__ */


#ifndef ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_FWD_DEFINED__
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_FWD_DEFINED__
typedef interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact;

#endif 	/* ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_FWD_DEFINED__ */


#ifndef ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_FWD_DEFINED__
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_FWD_DEFINED__
typedef interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput;

#endif 	/* ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_FWD_DEFINED__ */


#ifndef ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_FWD_DEFINED__
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_FWD_DEFINED__
typedef interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput;

#endif 	/* ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_FWD_DEFINED__ */


#ifndef ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_FWD_DEFINED__
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_FWD_DEFINED__
typedef interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput;

#endif 	/* ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_FWD_DEFINED__ */


#ifndef ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_FWD_DEFINED__
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_FWD_DEFINED__
typedef interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput;

#endif 	/* ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_FWD_DEFINED__ */


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


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveSeparator;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_FWD_DEFINED__ */


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


#ifndef ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_FWD_DEFINED__
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_FWD_DEFINED__
typedef interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage;

#endif 	/* ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_FWD_DEFINED__ */


#ifndef ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_FWD_DEFINED__
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_FWD_DEFINED__
typedef interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage;

#endif 	/* ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_FWD_DEFINED__ */


#ifndef ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_FWD_DEFINED__
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_FWD_DEFINED__
typedef interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage;

#endif 	/* ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_FWD_DEFINED__ */


#ifndef ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_FWD_DEFINED__
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_FWD_DEFINED__
typedef interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage;

#endif 	/* ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveImageSet;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveInputElement;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveChoiceInput;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveChoiceSetInput;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveDateInput;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveNumberInput;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveTextInput;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveTimeInput;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveToggleInput;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_FWD_DEFINED__ */


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


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveFact;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveFactSet;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet_FWD_DEFINED__ */


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


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveActionEventArgs;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveContainerStyleDefinition;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveContainerStylesDefinition;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveFontSizesConfig;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveFontWeightsConfig;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveColorConfig;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveColorsConfig;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveTextConfig;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveSpacingConfig;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveSeparatorConfig;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveImageSizesConfig;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveImageSetConfig;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveImageConfig;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveCardConfig;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveFactSetConfig;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveShowCardActionConfig;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveActionsConfig;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveHostConfig;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveHostConfigStatics;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveActionElement;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveOpenUrlAction;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveShowCardAction;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveSubmitAction;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IXamlCardResourceResolvers;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IXamlCardResourceResolver;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IXamlCardGetResourceStreamArgsFactory;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IXamlCardGetResourceStreamArgs;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs_FWD_DEFINED__ */


#ifndef ____FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs_FWD_DEFINED__
#define ____FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs_FWD_DEFINED__
typedef interface __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs;

#endif 	/* ____FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IRenderedAdaptiveCard;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_FWD_DEFINED__ */


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            interface IAdaptiveInputs;
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs_FWD_DEFINED__ */


/* header files for imported files */
#include "inspectable.h"
#include "Windows.Foundation.h"
#include "Windows.UI.Xaml.h"
#include "Windows.Data.Json.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0000 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0000 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0000_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5392 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5392 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5392_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5392_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0001 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0001 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0001_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5393 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5393 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5393_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5393_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0002 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0002 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0002_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5394 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5394 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5394_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5394_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0003 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0003 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0003_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0003_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5395 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5395 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5395_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5395_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0004 */
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
interface IAdaptiveActionElement;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0004 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0004_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0004_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5396 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5396 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5396_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5396_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0005 */
/* [local] */ 

#ifndef DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_USE
#define DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("47dc16f3-a8d2-5a29-a5b0-b31c21beee95"))
IIterator<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*> : IIterator_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IIterator`1<AdaptiveCards.XamlCardRenderer.IAdaptiveActionElement>"; }
};
typedef IIterator<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*> __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_t;
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_FWD_DEFINED__
#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement ABI::Windows::Foundation::Collections::__FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0005 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0005_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0005_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5397 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5397 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5397_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5397_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0006 */
/* [local] */ 

#ifndef DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_USE
#define DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("b7e3f02e-b05b-5159-b923-aa7e42e845b9"))
IIterable<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*> : IIterable_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IIterable`1<AdaptiveCards.XamlCardRenderer.IAdaptiveActionElement>"; }
};
typedef IIterable<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*> __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_t;
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_FWD_DEFINED__
#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement ABI::Windows::Foundation::Collections::__FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0006 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0006_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0006_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5398 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5398 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5398_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5398_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0007 */
/* [local] */ 

#ifndef DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_USE
#define DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("d1875062-8cb6-52c2-a4ca-a688446b653a"))
IVectorView<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*> : IVectorView_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IVectorView`1<AdaptiveCards.XamlCardRenderer.IAdaptiveActionElement>"; }
};
typedef IVectorView<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*> __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_t;
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_FWD_DEFINED__
#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement ABI::Windows::Foundation::Collections::__FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0007 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0007_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0007_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5399 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5399 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5399_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5399_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0008 */
/* [local] */ 

#ifndef DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_USE
#define DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("d04e3022-521f-511c-8bc3-d18bf9e04141"))
IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*> : IVector_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IVector`1<AdaptiveCards.XamlCardRenderer.IAdaptiveActionElement>"; }
};
typedef IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*> __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_t;
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_FWD_DEFINED__
#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement ABI::Windows::Foundation::Collections::__FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_USE */

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
interface IAdaptiveColumn;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0008 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0008_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5400 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5400 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5400_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5400_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0009 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0009 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0009_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0009_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5401 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5401 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5401_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5401_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0010 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0010 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0010_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0010_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5402 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5402 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5402_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5402_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0011 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0011 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0011_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0011_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5403 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5403 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5403_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5403_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0012 */
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

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
interface IAdaptiveFact;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0012 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0012_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5404 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5404 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5404_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5404_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0013 */
/* [local] */ 

#ifndef DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_USE
#define DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("8bad3de1-5811-584b-a9a4-6ae52b105014"))
IIterator<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*> : IIterator_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IIterator`1<AdaptiveCards.XamlCardRenderer.IAdaptiveFact>"; }
};
typedef IIterator<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*> __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_t;
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_FWD_DEFINED__
#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact ABI::Windows::Foundation::Collections::__FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0013 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0013_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0013_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5405 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5405 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5405_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5405_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0014 */
/* [local] */ 

#ifndef DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_USE
#define DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("b45d24d6-9613-50d6-badc-b77fb8674aa3"))
IIterable<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*> : IIterable_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IIterable`1<AdaptiveCards.XamlCardRenderer.IAdaptiveFact>"; }
};
typedef IIterable<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*> __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_t;
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_FWD_DEFINED__
#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact ABI::Windows::Foundation::Collections::__FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0014 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0014_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0014_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5406 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5406 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5406_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5406_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0015 */
/* [local] */ 

#ifndef DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_USE
#define DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("950143e8-0e3d-5af1-bb0d-83dd61a4860f"))
IVectorView<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*> : IVectorView_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IVectorView`1<AdaptiveCards.XamlCardRenderer.IAdaptiveFact>"; }
};
typedef IVectorView<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*> __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_t;
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_FWD_DEFINED__
#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact ABI::Windows::Foundation::Collections::__FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0015 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0015_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0015_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5407 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5407 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5407_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5407_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0016 */
/* [local] */ 

#ifndef DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_USE
#define DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("498c296a-f49a-587e-a2b5-f72eb27a242e"))
IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*> : IVector_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IVector`1<AdaptiveCards.XamlCardRenderer.IAdaptiveFact>"; }
};
typedef IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*> __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_t;
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_FWD_DEFINED__
#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact ABI::Windows::Foundation::Collections::__FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_USE */

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
interface IAdaptiveChoiceInput;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0016 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0016_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0016_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5408 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5408 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5408_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5408_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0017 */
/* [local] */ 

#ifndef DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_USE
#define DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("91c31dae-fb47-5942-a529-6e6b87233bfc"))
IIterator<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput*> : IIterator_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IIterator`1<AdaptiveCards.XamlCardRenderer.IAdaptiveChoiceInput>"; }
};
typedef IIterator<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput*> __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_t;
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_FWD_DEFINED__
#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput ABI::Windows::Foundation::Collections::__FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0017 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0017_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0017_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5409 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5409 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5409_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5409_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0018 */
/* [local] */ 

#ifndef DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_USE
#define DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("4831254d-c5d5-58e0-b6fc-c93849e0b664"))
IIterable<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput*> : IIterable_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IIterable`1<AdaptiveCards.XamlCardRenderer.IAdaptiveChoiceInput>"; }
};
typedef IIterable<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput*> __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_t;
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_FWD_DEFINED__
#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput ABI::Windows::Foundation::Collections::__FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0018 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0018_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0018_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5410 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5410 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5410_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5410_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0019 */
/* [local] */ 

#ifndef DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_USE
#define DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("55c6abc5-3ffe-50a1-9a6b-f1a910b1d41a"))
IVectorView<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput*> : IVectorView_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IVectorView`1<AdaptiveCards.XamlCardRenderer.IAdaptiveChoiceInput>"; }
};
typedef IVectorView<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput*> __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_t;
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_FWD_DEFINED__
#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput ABI::Windows::Foundation::Collections::__FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0019 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0019_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0019_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5411 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5411 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5411_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5411_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0020 */
/* [local] */ 

#ifndef DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_USE
#define DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("dd74128c-ed8b-5df2-a17a-c42c83f78360"))
IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput*> : IVector_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IVector`1<AdaptiveCards.XamlCardRenderer.IAdaptiveChoiceInput>"; }
};
typedef IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput*> __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_t;
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_FWD_DEFINED__
#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput ABI::Windows::Foundation::Collections::__FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0020 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0020_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0020_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5412 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5412 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5412_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5412_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0021 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0021 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0021_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0021_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5413 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5413 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5413_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5413_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0022 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0022 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0022_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0022_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5414 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5414 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5414_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5414_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0023 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0023 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0023_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0023_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5415 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5415 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5415_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5415_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0024 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0024 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0024_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0024_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5416 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5416 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5416_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5416_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0025 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0025 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0025_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0025_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5417 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5417 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5417_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5417_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0026 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0026 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0026_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0026_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5418 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5418 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5418_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5418_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0027 */
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

#ifdef __cplusplus
namespace ABI {
namespace Windows {
namespace Data {
namespace Json {
interface IJsonValue;
} /*Json*/
} /*Data*/
} /*Windows*/
}
#endif


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0027 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0027_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0027_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5419 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5419 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5419_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5419_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0028 */
/* [local] */ 

#ifndef DEF___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#define DEF___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("4deecc89-b0b8-5ee8-a51d-1c25ad9a5b01"))
IKeyValuePair<HSTRING,ABI::Windows::Data::Json::IJsonValue*> : IKeyValuePair_impl<HSTRING,ABI::Windows::Data::Json::IJsonValue*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IKeyValuePair`2<String, Windows.Data.Json.IJsonValue>"; }
};
typedef IKeyValuePair<HSTRING,ABI::Windows::Data::Json::IJsonValue*> __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_t;
#define ____FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_FWD_DEFINED__
#define __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue ABI::Windows::Foundation::Collections::__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0028 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0028_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0028_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5420 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5420 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5420_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5420_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0029 */
/* [local] */ 

#ifndef DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#define DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("f948eac5-33eb-50f5-b5af-e7cecf0e4501"))
IIterator<__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue*> : IIterator_impl<__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IIterator`1<Windows.Foundation.Collections.IKeyValuePair`2<String, Windows.Data.Json.IJsonValue>>"; }
};
typedef IIterator<__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue*> __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_t;
#define ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_FWD_DEFINED__
#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue ABI::Windows::Foundation::Collections::__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0029 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0029_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0029_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5421 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5421 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5421_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5421_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0030 */
/* [local] */ 

#ifndef DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#define DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("dfabb6e1-0411-5a8f-aa87-354e7110f099"))
IIterable<__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue*> : IIterable_impl<__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IIterable`1<Windows.Foundation.Collections.IKeyValuePair`2<String, Windows.Data.Json.IJsonValue>>"; }
};
typedef IIterable<__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue*> __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_t;
#define ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_FWD_DEFINED__
#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue ABI::Windows::Foundation::Collections::__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0030 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0030_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0030_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5422 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5422 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5422_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5422_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0031 */
/* [local] */ 

#ifndef DEF___FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#define DEF___FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("eecd690c-1ff3-529f-923f-9b1c31fd3d0f"))
IMapView<HSTRING,ABI::Windows::Data::Json::IJsonValue*> : IMapView_impl<HSTRING,ABI::Windows::Data::Json::IJsonValue*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IMapView`2<String, Windows.Data.Json.IJsonValue>"; }
};
typedef IMapView<HSTRING,ABI::Windows::Data::Json::IJsonValue*> __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_t;
#define ____FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_FWD_DEFINED__
#define __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue ABI::Windows::Foundation::Collections::__FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0031 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0031_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0031_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5423 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5423 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5423_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5423_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0032 */
/* [local] */ 

#ifndef DEF___FIMap_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#define DEF___FIMap_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("c9d9a725-786b-5113-b4b7-9b61764c220b"))
IMap<HSTRING,ABI::Windows::Data::Json::IJsonValue*> : IMap_impl<HSTRING,ABI::Windows::Data::Json::IJsonValue*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IMap`2<String, Windows.Data.Json.IJsonValue>"; }
};
typedef IMap<HSTRING,ABI::Windows::Data::Json::IJsonValue*> __FIMap_2_HSTRING_Windows__CData__CJson__CIJsonValue_t;
#define ____FIMap_2_HSTRING_Windows__CData__CJson__CIJsonValue_FWD_DEFINED__
#define __FIMap_2_HSTRING_Windows__CData__CJson__CIJsonValue ABI::Windows::Foundation::Collections::__FIMap_2_HSTRING_Windows__CData__CJson__CIJsonValue_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIMap_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE */

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
interface IAdaptiveImage;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0032 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0032_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0032_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5424 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5424 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5424_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5424_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0033 */
/* [local] */ 

#ifndef DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_USE
#define DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("3fb9c73d-25d0-57c4-ab92-6d8dde93112a"))
IIterator<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*> : IIterator_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IIterator`1<AdaptiveCards.XamlCardRenderer.IAdaptiveImage>"; }
};
typedef IIterator<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*> __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_t;
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_FWD_DEFINED__
#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage ABI::Windows::Foundation::Collections::__FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0033 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0033_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0033_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5425 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5425 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5425_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5425_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0034 */
/* [local] */ 

#ifndef DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_USE
#define DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("856a66c3-59fe-56fd-8832-65ee7e9d879e"))
IIterable<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*> : IIterable_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IIterable`1<AdaptiveCards.XamlCardRenderer.IAdaptiveImage>"; }
};
typedef IIterable<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*> __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_t;
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_FWD_DEFINED__
#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage ABI::Windows::Foundation::Collections::__FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0034 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0034_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0034_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5426 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5426 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5426_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5426_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0035 */
/* [local] */ 

#ifndef DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_USE
#define DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("70b6197c-e977-542e-8922-1c3bbff1c5c1"))
IVectorView<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*> : IVectorView_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IVectorView`1<AdaptiveCards.XamlCardRenderer.IAdaptiveImage>"; }
};
typedef IVectorView<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*> __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_t;
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_FWD_DEFINED__
#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage ABI::Windows::Foundation::Collections::__FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0035 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0035_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0035_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5427 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5427 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5427_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5427_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0036 */
/* [local] */ 

#ifndef DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_USE
#define DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("fd0d3dcc-6fc5-5216-9322-30006c6dd402"))
IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*> : IVector_impl<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.Collections.IVector`1<AdaptiveCards.XamlCardRenderer.IAdaptiveImage>"; }
};
typedef IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*> __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_t;
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_FWD_DEFINED__
#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage ABI::Windows::Foundation::Collections::__FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_t

/* ABI */ } /* Windows */ } /* Foundation */ } /* Collections */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_USE */

interface IInspectable;


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0036 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0036_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0036_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5428 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5428 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5428_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5428_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0037 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0037 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0037_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0037_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5429 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5429 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5429_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5429_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0038 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0038 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0038_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0038_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5430 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5430 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5430_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5430_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0039 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0039 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0039_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0039_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5431 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5431 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5431_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5431_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0040 */
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0040 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0040_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0040_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5432 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5432 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5432_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5432_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0041 */
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

#ifdef __cplusplus
namespace ABI {
namespace Windows {
namespace Storage {
namespace Streams {
interface IRandomAccessStream;
} /*Streams*/
} /*Storage*/
} /*Windows*/
}
#endif


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0041 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0041_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0041_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5433 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5433 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5433_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5433_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0042 */
/* [local] */ 

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("398c4183-793d-5b00-819b-4aef92485e94"))
IAsyncOperationCompletedHandler<ABI::Windows::Storage::Streams::IRandomAccessStream*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Storage::Streams::IRandomAccessStream*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Windows.Storage.Streams.IRandomAccessStream>"; }
};
typedef IAsyncOperationCompletedHandler<ABI::Windows::Storage::Streams::IRandomAccessStream*> __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_t;
#define ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_FWD_DEFINED__
#define __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_t

/* ABI */ } /* Windows */ } /* Foundation */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0042 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0042_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0042_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5434 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5434 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5434_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5434_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0043 */
/* [local] */ 

#ifndef DEF___FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE
#define DEF___FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("430ecece-1418-5d19-81b2-5ddb381603cc"))
IAsyncOperation<ABI::Windows::Storage::Streams::IRandomAccessStream*> : IAsyncOperation_impl<ABI::Windows::Storage::Streams::IRandomAccessStream*> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.IAsyncOperation`1<Windows.Storage.Streams.IRandomAccessStream>"; }
};
typedef IAsyncOperation<ABI::Windows::Storage::Streams::IRandomAccessStream*> __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_t;
#define ____FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_FWD_DEFINED__
#define __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream ABI::Windows::Foundation::__FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_t

/* ABI */ } /* Windows */ } /* Foundation */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE */
#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class RenderedAdaptiveCard;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
interface IRenderedAdaptiveCard;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif
#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveActionEventArgs;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
interface IAdaptiveActionEventArgs;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0043 */
/* [local] */ 






extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0043_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0043_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5435 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5435 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5435_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5435_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0044 */
/* [local] */ 

#ifndef DEF___FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs_USE
#define DEF___FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs_USE
#if defined(__cplusplus) && !defined(RO_NO_TEMPLATE_NAME)
} /*extern "C"*/ 
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("a5828abb-42c3-54fa-b7d0-001e85b4b639"))
ITypedEventHandler<ABI::AdaptiveCards::XamlCardRenderer::RenderedAdaptiveCard*,ABI::AdaptiveCards::XamlCardRenderer::AdaptiveActionEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::AdaptiveCards::XamlCardRenderer::RenderedAdaptiveCard*, ABI::AdaptiveCards::XamlCardRenderer::IRenderedAdaptiveCard*>,ABI::Windows::Foundation::Internal::AggregateType<ABI::AdaptiveCards::XamlCardRenderer::AdaptiveActionEventArgs*, ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionEventArgs*>> {
static const wchar_t* z_get_rc_name_impl() {
return L"Windows.Foundation.TypedEventHandler`2<AdaptiveCards.XamlCardRenderer.RenderedAdaptiveCard, AdaptiveCards.XamlCardRenderer.AdaptiveActionEventArgs>"; }
};
typedef ITypedEventHandler<ABI::AdaptiveCards::XamlCardRenderer::RenderedAdaptiveCard*,ABI::AdaptiveCards::XamlCardRenderer::AdaptiveActionEventArgs*> __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs_t;
#define ____FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs_FWD_DEFINED__
#define __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs_t

/* ABI */ } /* Windows */ } /* Foundation */ }
extern "C" {
#endif //__cplusplus
#endif /* DEF___FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs_USE */
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
class XamlCardResourceResolvers;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class XamlCardGetResourceStreamArgs;
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
class AdaptiveImageSet;
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

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveFact;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif
#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveFactSet;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveChoiceInput;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif
#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveChoiceSetInput;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveDateInput;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveNumberInput;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveTextInput;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveTimeInput;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveToggleInput;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveSeparator;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveFontSizesConfig;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveFontWeightsConfig;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveColorsConfig;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveColorConfig;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveTextConfig;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveImageSizesConfig;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveImageSetConfig;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveImageConfig;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveCardConfig;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveFactSetConfig;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveShowCardActionConfig;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveActionsConfig;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveHostConfig;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveSpacingConfig;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveSeparatorConfig;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveContainerStyleDefinition;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveContainerStylesDefinition;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveInputs;
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
        TextSize_Default	= ( TextSize_Small + 1 ) ,
        TextSize_Medium	= ( TextSize_Default + 1 ) ,
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
        TextWeight_Default	= ( TextWeight_Lighter + 1 ) ,
        TextWeight_Bolder	= ( TextWeight_Default + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextWeight __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextWeight;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CForegroundColor
    {
        ForegroundColor_Default	= 0,
        ForegroundColor_Dark	= ( ForegroundColor_Default + 1 ) ,
        ForegroundColor_Light	= ( ForegroundColor_Dark + 1 ) ,
        ForegroundColor_Accent	= ( ForegroundColor_Light + 1 ) ,
        ForegroundColor_Good	= ( ForegroundColor_Accent + 1 ) ,
        ForegroundColor_Warning	= ( ForegroundColor_Good + 1 ) ,
        ForegroundColor_Attention	= ( ForegroundColor_Warning + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CForegroundColor __x_ABI_CAdaptiveCards_CXamlCardRenderer_CForegroundColor;


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
        ElementType_ColumnSet	= ( ElementType_Column + 1 ) ,
        ElementType_FactSet	= ( ElementType_ColumnSet + 1 ) ,
        ElementType_Fact	= ( ElementType_FactSet + 1 ) ,
        ElementType_ImageSet	= ( ElementType_Fact + 1 ) ,
        ElementType_ChoiceInput	= ( ElementType_ImageSet + 1 ) ,
        ElementType_ChoiceSetInput	= ( ElementType_ChoiceInput + 1 ) ,
        ElementType_DateInput	= ( ElementType_ChoiceSetInput + 1 ) ,
        ElementType_NumberInput	= ( ElementType_DateInput + 1 ) ,
        ElementType_TextInput	= ( ElementType_NumberInput + 1 ) ,
        ElementType_TimeInput	= ( ElementType_TextInput + 1 ) ,
        ElementType_ToggleInput	= ( ElementType_TimeInput + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CElementType __x_ABI_CAdaptiveCards_CXamlCardRenderer_CElementType;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionType
    {
        ActionType_Unsupported	= 0,
        ActionType_ShowCard	= ( ActionType_Unsupported + 1 ) ,
        ActionType_Submit	= ( ActionType_ShowCard + 1 ) ,
        ActionType_OpenUrl	= ( ActionType_Submit + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionType __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionType;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageStyle
    {
        ImageStyle_Default	= 0,
        ImageStyle_Person	= ( ImageStyle_Default + 1 ) 
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
        ImageSize_None	= 0,
        ImageSize_Auto	= ( ImageSize_None + 1 ) ,
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
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSeparatorThickness
    {
        SeparatorThickness_Default	= 0,
        SeparatorThickness_Thick	= ( SeparatorThickness_Default + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSeparatorThickness __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSeparatorThickness;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSpacing
    {
        Spacing_Default	= 0,
        Spacing_None	= ( Spacing_Default + 1 ) ,
        Spacing_Small	= ( Spacing_None + 1 ) ,
        Spacing_Medium	= ( Spacing_Small + 1 ) ,
        Spacing_Large	= ( Spacing_Medium + 1 ) ,
        Spacing_ExtraLarge	= ( Spacing_Large + 1 ) ,
        Spacing_Padding	= ( Spacing_ExtraLarge + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSpacing __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSpacing;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionsOrientation
    {
        ActionsOrientation_Vertical	= 0,
        ActionsOrientation_Horizontal	= ( ActionsOrientation_Vertical + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionsOrientation __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionsOrientation;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionAlignment
    {
        ActionAlignment_Left	= 0,
        ActionAlignment_Center	= ( ActionAlignment_Left + 1 ) ,
        ActionAlignment_Right	= ( ActionAlignment_Center + 1 ) ,
        ActionAlignment_Stretch	= ( ActionAlignment_Right + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionAlignment __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionAlignment;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionMode
    {
        ActionMode_Inline	= 0,
        ActionMode_Popup	= ( ActionMode_Inline + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionMode __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionMode;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CChoiceSetStyle
    {
        ChoiceSetStyle_Compact	= 0,
        ChoiceSetStyle_Expanded	= ( ChoiceSetStyle_Compact + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CChoiceSetStyle __x_ABI_CAdaptiveCards_CXamlCardRenderer_CChoiceSetStyle;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextInputStyle
    {
        TextInputStyle_Text	= 0,
        TextInputStyle_Tel	= ( TextInputStyle_Text + 1 ) ,
        TextInputStyle_Url	= ( TextInputStyle_Tel + 1 ) ,
        TextInputStyle_Email	= ( TextInputStyle_Url + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextInputStyle __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextInputStyle;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CContainerStyle
    {
        ContainerStyle_None	= 0,
        ContainerStyle_Default	= ( ContainerStyle_None + 1 ) ,
        ContainerStyle_Emphasis	= ( ContainerStyle_Default + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CContainerStyle __x_ABI_CAdaptiveCards_CXamlCardRenderer_CContainerStyle;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CInputValueMode
    {
        InputValueMode_RawString	= 0
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CInputValueMode __x_ABI_CAdaptiveCards_CXamlCardRenderer_CInputValueMode;


#endif /* end if !defined(__cplusplus) */


#endif


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0044 */
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
                    Default	= ( Small + 1 ) ,
                    Medium	= ( Default + 1 ) ,
                    Large	= ( Medium + 1 ) ,
                    ExtraLarge	= ( Large + 1 ) 
                } ;

            const MIDL_ENUM TextSize TextSize_Small = TextSize::Small;
            const MIDL_ENUM TextSize TextSize_Default = TextSize::Default;
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
                    Default	= ( Lighter + 1 ) ,
                    Bolder	= ( Default + 1 ) 
                } ;

            const MIDL_ENUM TextWeight TextWeight_Lighter = TextWeight::Lighter;
            const MIDL_ENUM TextWeight TextWeight_Default = TextWeight::Default;
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
            MIDL_ENUM ForegroundColor
                {
                    Default	= 0,
                    Dark	= ( Default + 1 ) ,
                    Light	= ( Dark + 1 ) ,
                    Accent	= ( Light + 1 ) ,
                    Good	= ( Accent + 1 ) ,
                    Warning	= ( Good + 1 ) ,
                    Attention	= ( Warning + 1 ) 
                } ;

            const MIDL_ENUM ForegroundColor ForegroundColor_Default = ForegroundColor::Default;
            const MIDL_ENUM ForegroundColor ForegroundColor_Dark = ForegroundColor::Dark;
            const MIDL_ENUM ForegroundColor ForegroundColor_Light = ForegroundColor::Light;
            const MIDL_ENUM ForegroundColor ForegroundColor_Accent = ForegroundColor::Accent;
            const MIDL_ENUM ForegroundColor ForegroundColor_Good = ForegroundColor::Good;
            const MIDL_ENUM ForegroundColor ForegroundColor_Warning = ForegroundColor::Warning;
            const MIDL_ENUM ForegroundColor ForegroundColor_Attention = ForegroundColor::Attention;
            
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
            
            typedef MIDL_ENUM ForegroundColor ForegroundColor;
            
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
                    ColumnSet	= ( Column + 1 ) ,
                    FactSet	= ( ColumnSet + 1 ) ,
                    Fact	= ( FactSet + 1 ) ,
                    ImageSet	= ( Fact + 1 ) ,
                    ChoiceInput	= ( ImageSet + 1 ) ,
                    ChoiceSetInput	= ( ChoiceInput + 1 ) ,
                    DateInput	= ( ChoiceSetInput + 1 ) ,
                    NumberInput	= ( DateInput + 1 ) ,
                    TextInput	= ( NumberInput + 1 ) ,
                    TimeInput	= ( TextInput + 1 ) ,
                    ToggleInput	= ( TimeInput + 1 ) 
                } ;

            const MIDL_ENUM ElementType ElementType_Unsupported = ElementType::Unsupported;
            const MIDL_ENUM ElementType ElementType_AdaptiveCard = ElementType::AdaptiveCard;
            const MIDL_ENUM ElementType ElementType_TextBlock = ElementType::TextBlock;
            const MIDL_ENUM ElementType ElementType_Image = ElementType::Image;
            const MIDL_ENUM ElementType ElementType_Container = ElementType::Container;
            const MIDL_ENUM ElementType ElementType_Column = ElementType::Column;
            const MIDL_ENUM ElementType ElementType_ColumnSet = ElementType::ColumnSet;
            const MIDL_ENUM ElementType ElementType_FactSet = ElementType::FactSet;
            const MIDL_ENUM ElementType ElementType_Fact = ElementType::Fact;
            const MIDL_ENUM ElementType ElementType_ImageSet = ElementType::ImageSet;
            const MIDL_ENUM ElementType ElementType_ChoiceInput = ElementType::ChoiceInput;
            const MIDL_ENUM ElementType ElementType_ChoiceSetInput = ElementType::ChoiceSetInput;
            const MIDL_ENUM ElementType ElementType_DateInput = ElementType::DateInput;
            const MIDL_ENUM ElementType ElementType_NumberInput = ElementType::NumberInput;
            const MIDL_ENUM ElementType ElementType_TextInput = ElementType::TextInput;
            const MIDL_ENUM ElementType ElementType_TimeInput = ElementType::TimeInput;
            const MIDL_ENUM ElementType ElementType_ToggleInput = ElementType::ToggleInput;
            
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
            MIDL_ENUM ActionType
                {
                    Unsupported	= 0,
                    ShowCard	= ( Unsupported + 1 ) ,
                    Submit	= ( ShowCard + 1 ) ,
                    OpenUrl	= ( Submit + 1 ) 
                } ;

            const MIDL_ENUM ActionType ActionType_Unsupported = ActionType::Unsupported;
            const MIDL_ENUM ActionType ActionType_ShowCard = ActionType::ShowCard;
            const MIDL_ENUM ActionType ActionType_Submit = ActionType::Submit;
            const MIDL_ENUM ActionType ActionType_OpenUrl = ActionType::OpenUrl;
            
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
            
            typedef MIDL_ENUM ActionType ActionType;
            
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
                    Default	= 0,
                    Person	= ( Default + 1 ) 
                } ;

            const MIDL_ENUM ImageStyle ImageStyle_Default = ImageStyle::Default;
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
                    None	= 0,
                    Auto	= ( None + 1 ) ,
                    Stretch	= ( Auto + 1 ) ,
                    Small	= ( Stretch + 1 ) ,
                    Medium	= ( Small + 1 ) ,
                    Large	= ( Medium + 1 ) 
                } ;

            const MIDL_ENUM ImageSize ImageSize_None = ImageSize::None;
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
            MIDL_ENUM SeparatorThickness
                {
                    Default	= 0,
                    Thick	= ( Default + 1 ) 
                } ;

            const MIDL_ENUM SeparatorThickness SeparatorThickness_Default = SeparatorThickness::Default;
            const MIDL_ENUM SeparatorThickness SeparatorThickness_Thick = SeparatorThickness::Thick;
            
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
            
            typedef MIDL_ENUM SeparatorThickness SeparatorThickness;
            
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
            MIDL_ENUM Spacing
                {
                    Default	= 0,
                    None	= ( Default + 1 ) ,
                    Small	= ( None + 1 ) ,
                    Medium	= ( Small + 1 ) ,
                    Large	= ( Medium + 1 ) ,
                    ExtraLarge	= ( Large + 1 ) ,
                    Padding	= ( ExtraLarge + 1 ) 
                } ;

            const MIDL_ENUM Spacing Spacing_Default = Spacing::Default;
            const MIDL_ENUM Spacing Spacing_None = Spacing::None;
            const MIDL_ENUM Spacing Spacing_Small = Spacing::Small;
            const MIDL_ENUM Spacing Spacing_Medium = Spacing::Medium;
            const MIDL_ENUM Spacing Spacing_Large = Spacing::Large;
            const MIDL_ENUM Spacing Spacing_ExtraLarge = Spacing::ExtraLarge;
            const MIDL_ENUM Spacing Spacing_Padding = Spacing::Padding;
            
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
            
            typedef MIDL_ENUM Spacing Spacing;
            
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
            MIDL_ENUM ActionsOrientation
                {
                    Vertical	= 0,
                    Horizontal	= ( Vertical + 1 ) 
                } ;

            const MIDL_ENUM ActionsOrientation ActionsOrientation_Vertical = ActionsOrientation::Vertical;
            const MIDL_ENUM ActionsOrientation ActionsOrientation_Horizontal = ActionsOrientation::Horizontal;
            
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
            
            typedef MIDL_ENUM ActionsOrientation ActionsOrientation;
            
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
            MIDL_ENUM ActionAlignment
                {
                    Left	= 0,
                    Center	= ( Left + 1 ) ,
                    Right	= ( Center + 1 ) ,
                    Stretch	= ( Right + 1 ) 
                } ;

            const MIDL_ENUM ActionAlignment ActionAlignment_Left = ActionAlignment::Left;
            const MIDL_ENUM ActionAlignment ActionAlignment_Center = ActionAlignment::Center;
            const MIDL_ENUM ActionAlignment ActionAlignment_Right = ActionAlignment::Right;
            const MIDL_ENUM ActionAlignment ActionAlignment_Stretch = ActionAlignment::Stretch;
            
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
            
            typedef MIDL_ENUM ActionAlignment ActionAlignment;
            
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
            MIDL_ENUM ActionMode
                {
                    Inline	= 0,
                    Popup	= ( Inline + 1 ) 
                } ;

            const MIDL_ENUM ActionMode ActionMode_Inline = ActionMode::Inline;
            const MIDL_ENUM ActionMode ActionMode_Popup = ActionMode::Popup;
            
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
            
            typedef MIDL_ENUM ActionMode ActionMode;
            
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
            MIDL_ENUM ChoiceSetStyle
                {
                    Compact	= 0,
                    Expanded	= ( Compact + 1 ) 
                } ;

            const MIDL_ENUM ChoiceSetStyle ChoiceSetStyle_Compact = ChoiceSetStyle::Compact;
            const MIDL_ENUM ChoiceSetStyle ChoiceSetStyle_Expanded = ChoiceSetStyle::Expanded;
            
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
            
            typedef MIDL_ENUM ChoiceSetStyle ChoiceSetStyle;
            
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
            MIDL_ENUM TextInputStyle
                {
                    Text	= 0,
                    Tel	= ( Text + 1 ) ,
                    Url	= ( Tel + 1 ) ,
                    Email	= ( Url + 1 ) 
                } ;

            const MIDL_ENUM TextInputStyle TextInputStyle_Text = TextInputStyle::Text;
            const MIDL_ENUM TextInputStyle TextInputStyle_Tel = TextInputStyle::Tel;
            const MIDL_ENUM TextInputStyle TextInputStyle_Url = TextInputStyle::Url;
            const MIDL_ENUM TextInputStyle TextInputStyle_Email = TextInputStyle::Email;
            
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
            
            typedef MIDL_ENUM TextInputStyle TextInputStyle;
            
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
            MIDL_ENUM ContainerStyle
                {
                    None	= 0,
                    Default	= ( None + 1 ) ,
                    Emphasis	= ( Default + 1 ) 
                } ;

            const MIDL_ENUM ContainerStyle ContainerStyle_None = ContainerStyle::None;
            const MIDL_ENUM ContainerStyle ContainerStyle_Default = ContainerStyle::Default;
            const MIDL_ENUM ContainerStyle ContainerStyle_Emphasis = ContainerStyle::Emphasis;
            
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
            
            typedef MIDL_ENUM ContainerStyle ContainerStyle;
            
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
            MIDL_ENUM InputValueMode
                {
                    RawString	= 0
                } ;

            const MIDL_ENUM InputValueMode InputValueMode_RawString = InputValueMode::RawString;
            
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
            
            typedef MIDL_ENUM InputValueMode InputValueMode;
            
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0044_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0044_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5436 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5436 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5436_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5436_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0045 */
/* [local] */ 

#ifndef DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#define DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0045 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0045_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0045_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0046 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0046 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0046_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0046_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5437 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5437 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5437_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5437_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0047 */
/* [local] */ 

#ifndef DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#define DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0047 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0047_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0047_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0048 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0048 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0048_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0048_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5438 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5438 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5438_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5438_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0049 */
/* [local] */ 

#ifndef DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#define DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0049 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0049_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0049_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0050 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0050 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0050_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0050_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5439 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5439 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5439_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5439_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0051 */
/* [local] */ 

#ifndef DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#define DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0051 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0051_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0051_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0052 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0052 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0052_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0052_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5440 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5440 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5440_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5440_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0053 */
/* [local] */ 

#ifndef DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement
#define DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0053 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0053_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0053_v0_0_s_ifspec;

#ifndef ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_INTERFACE_DEFINED__
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_INTERFACE_DEFINED__

/* interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement */
/* [unique][uuid][object] */ 



/* interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47dc16f3-a8d2-5a29-a5b0-b31c21beee95")
    __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement : public IInspectable
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Current( 
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement **current) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_HasCurrent( 
            /* [retval][out] */ boolean *hasCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveNext( 
            /* [retval][out] */ boolean *hasCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Current )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement **current);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasCurrent )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [retval][out] */ boolean *hasCurrent);
        
        HRESULT ( STDMETHODCALLTYPE *MoveNext )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [retval][out] */ boolean *hasCurrent);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement **items,
            /* [retval][out] */ unsigned int *actual);
        
        END_INTERFACE
    } __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElementVtbl;

    interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement
    {
        CONST_VTBL struct __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_get_Current(This,current)	\
    ( (This)->lpVtbl -> get_Current(This,current) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_get_HasCurrent(This,hasCurrent)	\
    ( (This)->lpVtbl -> get_HasCurrent(This,hasCurrent) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_MoveNext(This,hasCurrent)	\
    ( (This)->lpVtbl -> MoveNext(This,hasCurrent) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetMany(This,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,capacity,items,actual) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0054 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0054 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0054_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0054_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5441 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5441 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5441_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5441_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0055 */
/* [local] */ 

#ifndef DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement
#define DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0055 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0055_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0055_v0_0_s_ifspec;

#ifndef ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_INTERFACE_DEFINED__
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_INTERFACE_DEFINED__

/* interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement */
/* [unique][uuid][object] */ 



/* interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b7e3f02e-b05b-5159-b923-aa7e42e845b9")
    __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE First( 
            /* [retval][out] */ __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement **first) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *First )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [retval][out] */ __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement **first);
        
        END_INTERFACE
    } __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElementVtbl;

    interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement
    {
        CONST_VTBL struct __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_First(This,first)	\
    ( (This)->lpVtbl -> First(This,first) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0056 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0056 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0056_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0056_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5442 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5442 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5442_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5442_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0057 */
/* [local] */ 

#ifndef DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement
#define DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0057 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0057_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0057_v0_0_s_ifspec;

#ifndef ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_INTERFACE_DEFINED__
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_INTERFACE_DEFINED__

/* interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement */
/* [unique][uuid][object] */ 



/* interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d1875062-8cb6-52c2-a4ca-a688446b653a")
    __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAt( 
            /* [in] */ unsigned int index,
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement **item) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ unsigned int *size) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IndexOf( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *GetAt )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [in] */ unsigned int index,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement **item);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [retval][out] */ unsigned int *size);
        
        HRESULT ( STDMETHODCALLTYPE *IndexOf )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement **items,
            /* [retval][out] */ unsigned int *actual);
        
        END_INTERFACE
    } __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElementVtbl;

    interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement
    {
        CONST_VTBL struct __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetAt(This,index,item)	\
    ( (This)->lpVtbl -> GetAt(This,index,item) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_get_Size(This,size)	\
    ( (This)->lpVtbl -> get_Size(This,size) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_IndexOf(This,item,index,found)	\
    ( (This)->lpVtbl -> IndexOf(This,item,index,found) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetMany(This,startIndex,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,startIndex,capacity,items,actual) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0058 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0058 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0058_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0058_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5443 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5443 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5443_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5443_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0059 */
/* [local] */ 

#ifndef DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement
#define DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0059 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0059_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0059_v0_0_s_ifspec;

#ifndef ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_INTERFACE_DEFINED__
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_INTERFACE_DEFINED__

/* interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement */
/* [unique][uuid][object] */ 



/* interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d04e3022-521f-511c-8bc3-d18bf9e04141")
    __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAt( 
            /* [in] */ unsigned int index,
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement **item) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ unsigned int *size) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetView( 
            /* [retval][out] */ __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement **view) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IndexOf( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAt( 
            /* [in] */ unsigned int index,
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InsertAt( 
            /* [in] */ unsigned int index,
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAt( 
            /* [in] */ unsigned int index) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Append( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAtEnd( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReplaceAll( 
            /* [in] */ unsigned int count,
            /* [size_is][in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement **value) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *GetAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [in] */ unsigned int index,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement **item);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [retval][out] */ unsigned int *size);
        
        HRESULT ( STDMETHODCALLTYPE *GetView )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [retval][out] */ __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement **view);
        
        HRESULT ( STDMETHODCALLTYPE *IndexOf )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found);
        
        HRESULT ( STDMETHODCALLTYPE *SetAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [in] */ unsigned int index,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement *item);
        
        HRESULT ( STDMETHODCALLTYPE *InsertAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [in] */ unsigned int index,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement *item);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [in] */ unsigned int index);
        
        HRESULT ( STDMETHODCALLTYPE *Append )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement *item);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveAtEnd )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clear )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement **items,
            /* [retval][out] */ unsigned int *actual);
        
        HRESULT ( STDMETHODCALLTYPE *ReplaceAll )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement * This,
            /* [in] */ unsigned int count,
            /* [size_is][in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement **value);
        
        END_INTERFACE
    } __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElementVtbl;

    interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement
    {
        CONST_VTBL struct __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetAt(This,index,item)	\
    ( (This)->lpVtbl -> GetAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_get_Size(This,size)	\
    ( (This)->lpVtbl -> get_Size(This,size) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetView(This,view)	\
    ( (This)->lpVtbl -> GetView(This,view) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_IndexOf(This,item,index,found)	\
    ( (This)->lpVtbl -> IndexOf(This,item,index,found) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_SetAt(This,index,item)	\
    ( (This)->lpVtbl -> SetAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_InsertAt(This,index,item)	\
    ( (This)->lpVtbl -> InsertAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_RemoveAt(This,index)	\
    ( (This)->lpVtbl -> RemoveAt(This,index) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_Append(This,item)	\
    ( (This)->lpVtbl -> Append(This,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_RemoveAtEnd(This)	\
    ( (This)->lpVtbl -> RemoveAtEnd(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_GetMany(This,startIndex,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,startIndex,capacity,items,actual) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_ReplaceAll(This,count,value)	\
    ( (This)->lpVtbl -> ReplaceAll(This,count,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0060 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0060 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0060_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0060_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5444 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5444 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5444_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5444_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0061 */
/* [local] */ 

#ifndef DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#define DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0061 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0061_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0061_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0062 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0062 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0062_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0062_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5445 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5445 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5445_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5445_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0063 */
/* [local] */ 

#ifndef DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#define DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0063 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0063_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0063_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0064 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0064 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0064_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0064_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5446 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5446 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5446_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5446_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0065 */
/* [local] */ 

#ifndef DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#define DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0065 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0065_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0065_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0066 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0066 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0066_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0066_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5447 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5447 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5447_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5447_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0067 */
/* [local] */ 

#ifndef DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#define DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0067 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0067_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0067_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0068 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0068 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0068_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0068_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5448 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5448 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5448_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5448_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0069 */
/* [local] */ 

#ifndef DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact
#define DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0069 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0069_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0069_v0_0_s_ifspec;

#ifndef ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_INTERFACE_DEFINED__
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_INTERFACE_DEFINED__

/* interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact */
/* [unique][uuid][object] */ 



/* interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8bad3de1-5811-584b-a9a4-6ae52b105014")
    __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact : public IInspectable
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Current( 
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact **current) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_HasCurrent( 
            /* [retval][out] */ boolean *hasCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveNext( 
            /* [retval][out] */ boolean *hasCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFactVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Current )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact **current);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasCurrent )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [retval][out] */ boolean *hasCurrent);
        
        HRESULT ( STDMETHODCALLTYPE *MoveNext )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [retval][out] */ boolean *hasCurrent);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact **items,
            /* [retval][out] */ unsigned int *actual);
        
        END_INTERFACE
    } __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFactVtbl;

    interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact
    {
        CONST_VTBL struct __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFactVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_get_Current(This,current)	\
    ( (This)->lpVtbl -> get_Current(This,current) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_get_HasCurrent(This,hasCurrent)	\
    ( (This)->lpVtbl -> get_HasCurrent(This,hasCurrent) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_MoveNext(This,hasCurrent)	\
    ( (This)->lpVtbl -> MoveNext(This,hasCurrent) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetMany(This,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,capacity,items,actual) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0070 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0070 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0070_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0070_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5449 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5449 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5449_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5449_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0071 */
/* [local] */ 

#ifndef DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact
#define DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0071 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0071_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0071_v0_0_s_ifspec;

#ifndef ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_INTERFACE_DEFINED__
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_INTERFACE_DEFINED__

/* interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact */
/* [unique][uuid][object] */ 



/* interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b45d24d6-9613-50d6-badc-b77fb8674aa3")
    __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE First( 
            /* [retval][out] */ __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact **first) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFactVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *First )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [retval][out] */ __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact **first);
        
        END_INTERFACE
    } __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFactVtbl;

    interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact
    {
        CONST_VTBL struct __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFactVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_First(This,first)	\
    ( (This)->lpVtbl -> First(This,first) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0072 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0072 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0072_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0072_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5450 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5450 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5450_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5450_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0073 */
/* [local] */ 

#ifndef DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact
#define DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0073 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0073_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0073_v0_0_s_ifspec;

#ifndef ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_INTERFACE_DEFINED__
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_INTERFACE_DEFINED__

/* interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact */
/* [unique][uuid][object] */ 



/* interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("950143e8-0e3d-5af1-bb0d-83dd61a4860f")
    __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAt( 
            /* [in] */ unsigned int index,
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact **item) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ unsigned int *size) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IndexOf( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFactVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *GetAt )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [in] */ unsigned int index,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact **item);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [retval][out] */ unsigned int *size);
        
        HRESULT ( STDMETHODCALLTYPE *IndexOf )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact **items,
            /* [retval][out] */ unsigned int *actual);
        
        END_INTERFACE
    } __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFactVtbl;

    interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact
    {
        CONST_VTBL struct __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFactVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetAt(This,index,item)	\
    ( (This)->lpVtbl -> GetAt(This,index,item) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_get_Size(This,size)	\
    ( (This)->lpVtbl -> get_Size(This,size) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_IndexOf(This,item,index,found)	\
    ( (This)->lpVtbl -> IndexOf(This,item,index,found) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetMany(This,startIndex,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,startIndex,capacity,items,actual) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0074 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0074 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0074_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0074_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5451 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5451 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5451_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5451_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0075 */
/* [local] */ 

#ifndef DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact
#define DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0075 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0075_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0075_v0_0_s_ifspec;

#ifndef ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_INTERFACE_DEFINED__
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_INTERFACE_DEFINED__

/* interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact */
/* [unique][uuid][object] */ 



/* interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("498c296a-f49a-587e-a2b5-f72eb27a242e")
    __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAt( 
            /* [in] */ unsigned int index,
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact **item) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ unsigned int *size) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetView( 
            /* [retval][out] */ __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact **view) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IndexOf( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAt( 
            /* [in] */ unsigned int index,
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InsertAt( 
            /* [in] */ unsigned int index,
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAt( 
            /* [in] */ unsigned int index) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Append( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAtEnd( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReplaceAll( 
            /* [in] */ unsigned int count,
            /* [size_is][in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact **value) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFactVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *GetAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [in] */ unsigned int index,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact **item);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [retval][out] */ unsigned int *size);
        
        HRESULT ( STDMETHODCALLTYPE *GetView )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [retval][out] */ __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact **view);
        
        HRESULT ( STDMETHODCALLTYPE *IndexOf )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found);
        
        HRESULT ( STDMETHODCALLTYPE *SetAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [in] */ unsigned int index,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact *item);
        
        HRESULT ( STDMETHODCALLTYPE *InsertAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [in] */ unsigned int index,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact *item);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [in] */ unsigned int index);
        
        HRESULT ( STDMETHODCALLTYPE *Append )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact *item);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveAtEnd )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clear )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact **items,
            /* [retval][out] */ unsigned int *actual);
        
        HRESULT ( STDMETHODCALLTYPE *ReplaceAll )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact * This,
            /* [in] */ unsigned int count,
            /* [size_is][in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact **value);
        
        END_INTERFACE
    } __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFactVtbl;

    interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact
    {
        CONST_VTBL struct __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFactVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetAt(This,index,item)	\
    ( (This)->lpVtbl -> GetAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_get_Size(This,size)	\
    ( (This)->lpVtbl -> get_Size(This,size) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetView(This,view)	\
    ( (This)->lpVtbl -> GetView(This,view) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_IndexOf(This,item,index,found)	\
    ( (This)->lpVtbl -> IndexOf(This,item,index,found) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_SetAt(This,index,item)	\
    ( (This)->lpVtbl -> SetAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_InsertAt(This,index,item)	\
    ( (This)->lpVtbl -> InsertAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_RemoveAt(This,index)	\
    ( (This)->lpVtbl -> RemoveAt(This,index) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_Append(This,item)	\
    ( (This)->lpVtbl -> Append(This,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_RemoveAtEnd(This)	\
    ( (This)->lpVtbl -> RemoveAtEnd(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_GetMany(This,startIndex,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,startIndex,capacity,items,actual) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_ReplaceAll(This,count,value)	\
    ( (This)->lpVtbl -> ReplaceAll(This,count,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0076 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0076 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0076_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0076_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5452 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5452 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5452_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5452_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0077 */
/* [local] */ 

#ifndef DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput
#define DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0077 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0077_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0077_v0_0_s_ifspec;

#ifndef ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_INTERFACE_DEFINED__
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_INTERFACE_DEFINED__

/* interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput */
/* [unique][uuid][object] */ 



/* interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("91c31dae-fb47-5942-a529-6e6b87233bfc")
    __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput : public IInspectable
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Current( 
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput **current) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_HasCurrent( 
            /* [retval][out] */ boolean *hasCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveNext( 
            /* [retval][out] */ boolean *hasCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInputVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Current )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput **current);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasCurrent )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [retval][out] */ boolean *hasCurrent);
        
        HRESULT ( STDMETHODCALLTYPE *MoveNext )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [retval][out] */ boolean *hasCurrent);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput **items,
            /* [retval][out] */ unsigned int *actual);
        
        END_INTERFACE
    } __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInputVtbl;

    interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput
    {
        CONST_VTBL struct __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInputVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_get_Current(This,current)	\
    ( (This)->lpVtbl -> get_Current(This,current) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_get_HasCurrent(This,hasCurrent)	\
    ( (This)->lpVtbl -> get_HasCurrent(This,hasCurrent) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_MoveNext(This,hasCurrent)	\
    ( (This)->lpVtbl -> MoveNext(This,hasCurrent) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetMany(This,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,capacity,items,actual) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0078 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0078 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0078_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0078_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5453 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5453 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5453_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5453_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0079 */
/* [local] */ 

#ifndef DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput
#define DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0079 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0079_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0079_v0_0_s_ifspec;

#ifndef ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_INTERFACE_DEFINED__
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_INTERFACE_DEFINED__

/* interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput */
/* [unique][uuid][object] */ 



/* interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4831254d-c5d5-58e0-b6fc-c93849e0b664")
    __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE First( 
            /* [retval][out] */ __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput **first) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInputVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *First )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [retval][out] */ __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput **first);
        
        END_INTERFACE
    } __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInputVtbl;

    interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput
    {
        CONST_VTBL struct __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInputVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_First(This,first)	\
    ( (This)->lpVtbl -> First(This,first) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0080 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0080 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0080_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0080_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5454 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5454 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5454_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5454_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0081 */
/* [local] */ 

#ifndef DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput
#define DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0081 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0081_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0081_v0_0_s_ifspec;

#ifndef ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_INTERFACE_DEFINED__
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_INTERFACE_DEFINED__

/* interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput */
/* [unique][uuid][object] */ 



/* interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("55c6abc5-3ffe-50a1-9a6b-f1a910b1d41a")
    __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAt( 
            /* [in] */ unsigned int index,
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput **item) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ unsigned int *size) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IndexOf( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInputVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *GetAt )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [in] */ unsigned int index,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput **item);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [retval][out] */ unsigned int *size);
        
        HRESULT ( STDMETHODCALLTYPE *IndexOf )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput **items,
            /* [retval][out] */ unsigned int *actual);
        
        END_INTERFACE
    } __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInputVtbl;

    interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput
    {
        CONST_VTBL struct __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInputVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetAt(This,index,item)	\
    ( (This)->lpVtbl -> GetAt(This,index,item) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_get_Size(This,size)	\
    ( (This)->lpVtbl -> get_Size(This,size) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_IndexOf(This,item,index,found)	\
    ( (This)->lpVtbl -> IndexOf(This,item,index,found) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetMany(This,startIndex,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,startIndex,capacity,items,actual) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0082 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0082 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0082_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0082_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5455 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5455 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5455_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5455_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0083 */
/* [local] */ 

#ifndef DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput
#define DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0083 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0083_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0083_v0_0_s_ifspec;

#ifndef ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_INTERFACE_DEFINED__
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_INTERFACE_DEFINED__

/* interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput */
/* [unique][uuid][object] */ 



/* interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("dd74128c-ed8b-5df2-a17a-c42c83f78360")
    __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAt( 
            /* [in] */ unsigned int index,
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput **item) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ unsigned int *size) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetView( 
            /* [retval][out] */ __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput **view) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IndexOf( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAt( 
            /* [in] */ unsigned int index,
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InsertAt( 
            /* [in] */ unsigned int index,
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAt( 
            /* [in] */ unsigned int index) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Append( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAtEnd( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReplaceAll( 
            /* [in] */ unsigned int count,
            /* [size_is][in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput **value) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInputVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *GetAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [in] */ unsigned int index,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput **item);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [retval][out] */ unsigned int *size);
        
        HRESULT ( STDMETHODCALLTYPE *GetView )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [retval][out] */ __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput **view);
        
        HRESULT ( STDMETHODCALLTYPE *IndexOf )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found);
        
        HRESULT ( STDMETHODCALLTYPE *SetAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [in] */ unsigned int index,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput *item);
        
        HRESULT ( STDMETHODCALLTYPE *InsertAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [in] */ unsigned int index,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput *item);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [in] */ unsigned int index);
        
        HRESULT ( STDMETHODCALLTYPE *Append )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput *item);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveAtEnd )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clear )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput **items,
            /* [retval][out] */ unsigned int *actual);
        
        HRESULT ( STDMETHODCALLTYPE *ReplaceAll )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput * This,
            /* [in] */ unsigned int count,
            /* [size_is][in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput **value);
        
        END_INTERFACE
    } __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInputVtbl;

    interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput
    {
        CONST_VTBL struct __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInputVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetAt(This,index,item)	\
    ( (This)->lpVtbl -> GetAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_get_Size(This,size)	\
    ( (This)->lpVtbl -> get_Size(This,size) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetView(This,view)	\
    ( (This)->lpVtbl -> GetView(This,view) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_IndexOf(This,item,index,found)	\
    ( (This)->lpVtbl -> IndexOf(This,item,index,found) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_SetAt(This,index,item)	\
    ( (This)->lpVtbl -> SetAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_InsertAt(This,index,item)	\
    ( (This)->lpVtbl -> InsertAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_RemoveAt(This,index)	\
    ( (This)->lpVtbl -> RemoveAt(This,index) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_Append(This,item)	\
    ( (This)->lpVtbl -> Append(This,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_RemoveAtEnd(This)	\
    ( (This)->lpVtbl -> RemoveAtEnd(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_GetMany(This,startIndex,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,startIndex,capacity,items,actual) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_ReplaceAll(This,count,value)	\
    ( (This)->lpVtbl -> ReplaceAll(This,count,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0084 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0084 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0084_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0084_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5456 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5456 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5456_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5456_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0085 */
/* [local] */ 

#ifndef DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#define DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)



/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0085 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0085_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0085_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0086 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0086 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0086_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0086_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5457 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5457 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5457_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5457_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0087 */
/* [local] */ 

#ifndef DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#define DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0087 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0087_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0087_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0088 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0088 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0088_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0088_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5458 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5458 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5458_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5458_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0089 */
/* [local] */ 

#ifndef DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#define DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)



/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0089 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0089_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0089_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0090 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FVectorChangedEventHandler_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0090 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0090_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0090_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5459 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5459 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5459_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5459_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0091 */
/* [local] */ 

#ifndef DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#define DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0091 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0091_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0091_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0092 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIObservableVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveColumn */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0092 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0092_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0092_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5460 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5460 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5460_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5460_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0093 */
/* [local] */ 

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement
#define DEF___FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)



/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0093 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0093_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0093_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0094 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CUIElement */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0094 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0094_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0094_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5461 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5461 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5461_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5461_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0095 */
/* [local] */ 

#ifndef DEF___FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement
#define DEF___FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0095 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0095_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0095_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0096 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0096 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0096_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0096_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5462 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5462 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5462_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5462_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0097 */
/* [local] */ 

#ifndef DEF___FIReference_1_Windows__CUI__CText__CFontWeight
#define DEF___FIReference_1_Windows__CUI__CText__CFontWeight
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0097 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0097_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0097_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0098 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIReference_1_Windows__CUI__CText__CFontWeight */
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveCardElement[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveCardElement";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0098 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0098_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0098_v0_0_s_ifspec;

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
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Spacing( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::Spacing *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Spacing( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::Spacing value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Separator( 
                        /* [out][retval] */ boolean *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Separator( 
                        /* [in] */ boolean value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Id( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Id( 
                        /* [in] */ HSTRING value) = 0;
                    
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
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Spacing )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSpacing *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Spacing )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSpacing value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Separator )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This,
            /* [out][retval] */ boolean *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Separator )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This,
            /* [in] */ boolean value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Id )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Id )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement * This,
            /* [in] */ HSTRING value);
        
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

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_get_Spacing(This,value)	\
    ( (This)->lpVtbl -> get_Spacing(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_put_Spacing(This,value)	\
    ( (This)->lpVtbl -> put_Spacing(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_get_Separator(This,value)	\
    ( (This)->lpVtbl -> get_Separator(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_put_Separator(This,value)	\
    ( (This)->lpVtbl -> put_Separator(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_get_Id(This,value)	\
    ( (This)->lpVtbl -> get_Id(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_put_Id(This,value)	\
    ( (This)->lpVtbl -> put_Id(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardElement_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0099 */
/* [local] */ 

#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveSeparator[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveSeparator";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0099 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0099_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0099_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("a2a0727a-e4aa-423d-b5b0-4b85f7a534c4")
                IAdaptiveSeparator : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Color( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ForegroundColor *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Color( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ForegroundColor value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Thickness( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::SeparatorThickness *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Thickness( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::SeparatorThickness value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveSeparator = __uuidof(IAdaptiveSeparator);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CForegroundColor *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CForegroundColor value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Thickness )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSeparatorThickness *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Thickness )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSeparatorThickness value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_get_Color(This,value)	\
    ( (This)->lpVtbl -> get_Color(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_put_Color(This,value)	\
    ( (This)->lpVtbl -> put_Color(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_get_Thickness(This,value)	\
    ( (This)->lpVtbl -> get_Thickness(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_put_Thickness(This,value)	\
    ( (This)->lpVtbl -> put_Thickness(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparator_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0100 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveSeparator_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveSeparator_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveSeparator[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveSeparator";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveTextBlock[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveTextBlock";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0100 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0100_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0100_v0_0_s_ifspec;

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
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ForegroundColor *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Color( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ForegroundColor value) = 0;
                    
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
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CForegroundColor *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextBlock * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CForegroundColor value);
        
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0101 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveTextBlock_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveTextBlock_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveTextBlock[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveTextBlock";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveCard[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveCard";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0101 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0101_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0101_v0_0_s_ifspec;

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
                
                MIDL_INTERFACE("1fbf16f2-7c70-4b19-9d76-fb107fc33821")
                IAdaptiveCard : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Body( 
                        /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement **value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Actions( 
                        /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement **value) = 0;
                    
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
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundImage( 
                        /* [out][retval] */ ABI::Windows::Foundation::IUriRuntimeClass **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_BackgroundImage( 
                        /* [in] */ ABI::Windows::Foundation::IUriRuntimeClass *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Speak( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Speak( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Style( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ContainerStyle *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Style( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ContainerStyle value) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE ToJson( 
                        /* [out][retval] */ ABI::Windows::Data::Json::IJsonObject **value) = 0;
                    
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
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Actions )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveActionElement **value);
        
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
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundImage )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [out][retval] */ __x_ABI_CWindows_CFoundation_CIUriRuntimeClass **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackgroundImage )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [in] */ __x_ABI_CWindows_CFoundation_CIUriRuntimeClass *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Speak )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Speak )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CContainerStyle *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CContainerStyle value);
        
        HRESULT ( STDMETHODCALLTYPE *ToJson )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard * This,
            /* [out][retval] */ __x_ABI_CWindows_CData_CJson_CIJsonObject **value);
        
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

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_get_Actions(This,value)	\
    ( (This)->lpVtbl -> get_Actions(This,value) ) 

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

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_get_BackgroundImage(This,value)	\
    ( (This)->lpVtbl -> get_BackgroundImage(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_put_BackgroundImage(This,value)	\
    ( (This)->lpVtbl -> put_BackgroundImage(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_get_Speak(This,value)	\
    ( (This)->lpVtbl -> get_Speak(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_put_Speak(This,value)	\
    ( (This)->lpVtbl -> put_Speak(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_get_Style(This,value)	\
    ( (This)->lpVtbl -> get_Style(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_put_Style(This,value)	\
    ( (This)->lpVtbl -> put_Style(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_ToJson(This,value)	\
    ( (This)->lpVtbl -> ToJson(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0102 */
/* [local] */ 

#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveCardStatics[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveCardStatics";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0102 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0102_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0102_v0_0_s_ifspec;

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
                
                MIDL_INTERFACE("bace01f2-5642-4366-879a-dec601d8b7e3")
                IAdaptiveCardStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE FromJson( 
                        /* [in] */ ABI::Windows::Data::Json::IJsonObject *adaptiveJson,
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard **card) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE FromJsonString( 
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
        
        HRESULT ( STDMETHODCALLTYPE *FromJson )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics * This,
            /* [in] */ __x_ABI_CWindows_CData_CJson_CIJsonObject *adaptiveJson,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard **card);
        
        HRESULT ( STDMETHODCALLTYPE *FromJsonString )( 
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


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_FromJson(This,adaptiveJson,card)	\
    ( (This)->lpVtbl -> FromJson(This,adaptiveJson,card) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_FromJsonString(This,adaptiveJson,card)	\
    ( (This)->lpVtbl -> FromJsonString(This,adaptiveJson,card) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardStatics_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0103 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveCard_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveCard_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveCard[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveCard";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveImage[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveImage";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0103 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0103_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0103_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0104 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveImage_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveImage_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveImage[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveImage";
#endif


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0104 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0104_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0104_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5463 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5463 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5463_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5463_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0105 */
/* [local] */ 

#ifndef DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage
#define DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0105 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0105_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0105_v0_0_s_ifspec;

#ifndef ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_INTERFACE_DEFINED__
#define ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_INTERFACE_DEFINED__

/* interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage */
/* [unique][uuid][object] */ 



/* interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3fb9c73d-25d0-57c4-ab92-6d8dde93112a")
    __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage : public IInspectable
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Current( 
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage **current) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_HasCurrent( 
            /* [retval][out] */ boolean *hasCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveNext( 
            /* [retval][out] */ boolean *hasCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Current )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage **current);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasCurrent )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [retval][out] */ boolean *hasCurrent);
        
        HRESULT ( STDMETHODCALLTYPE *MoveNext )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [retval][out] */ boolean *hasCurrent);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage **items,
            /* [retval][out] */ unsigned int *actual);
        
        END_INTERFACE
    } __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImageVtbl;

    interface __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage
    {
        CONST_VTBL struct __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_get_Current(This,current)	\
    ( (This)->lpVtbl -> get_Current(This,current) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_get_HasCurrent(This,hasCurrent)	\
    ( (This)->lpVtbl -> get_HasCurrent(This,hasCurrent) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_MoveNext(This,hasCurrent)	\
    ( (This)->lpVtbl -> MoveNext(This,hasCurrent) ) 

#define __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetMany(This,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,capacity,items,actual) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0106 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0106 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0106_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0106_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5464 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5464 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5464_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5464_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0107 */
/* [local] */ 

#ifndef DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage
#define DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0107 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0107_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0107_v0_0_s_ifspec;

#ifndef ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_INTERFACE_DEFINED__
#define ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_INTERFACE_DEFINED__

/* interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage */
/* [unique][uuid][object] */ 



/* interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("856a66c3-59fe-56fd-8832-65ee7e9d879e")
    __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE First( 
            /* [retval][out] */ __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage **first) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *First )( 
            __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [retval][out] */ __FIIterator_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage **first);
        
        END_INTERFACE
    } __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImageVtbl;

    interface __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage
    {
        CONST_VTBL struct __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_First(This,first)	\
    ( (This)->lpVtbl -> First(This,first) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0108 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIIterable_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0108 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0108_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0108_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5465 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5465 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5465_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5465_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0109 */
/* [local] */ 

#ifndef DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage
#define DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0109 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0109_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0109_v0_0_s_ifspec;

#ifndef ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_INTERFACE_DEFINED__
#define ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_INTERFACE_DEFINED__

/* interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage */
/* [unique][uuid][object] */ 



/* interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("70b6197c-e977-542e-8922-1c3bbff1c5c1")
    __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAt( 
            /* [in] */ unsigned int index,
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage **item) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ unsigned int *size) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IndexOf( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *GetAt )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [in] */ unsigned int index,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage **item);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [retval][out] */ unsigned int *size);
        
        HRESULT ( STDMETHODCALLTYPE *IndexOf )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage **items,
            /* [retval][out] */ unsigned int *actual);
        
        END_INTERFACE
    } __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImageVtbl;

    interface __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage
    {
        CONST_VTBL struct __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetAt(This,index,item)	\
    ( (This)->lpVtbl -> GetAt(This,index,item) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_get_Size(This,size)	\
    ( (This)->lpVtbl -> get_Size(This,size) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_IndexOf(This,item,index,found)	\
    ( (This)->lpVtbl -> IndexOf(This,item,index,found) ) 

#define __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetMany(This,startIndex,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,startIndex,capacity,items,actual) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0110 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0110 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0110_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0110_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5466 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5466 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5466_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5466_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0111 */
/* [local] */ 

#ifndef DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage
#define DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0111 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0111_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0111_v0_0_s_ifspec;

#ifndef ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_INTERFACE_DEFINED__
#define ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_INTERFACE_DEFINED__

/* interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage */
/* [unique][uuid][object] */ 



/* interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("fd0d3dcc-6fc5-5216-9322-30006c6dd402")
    __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAt( 
            /* [in] */ unsigned int index,
            /* [retval][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage **item) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ unsigned int *size) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetView( 
            /* [retval][out] */ __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage **view) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IndexOf( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAt( 
            /* [in] */ unsigned int index,
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InsertAt( 
            /* [in] */ unsigned int index,
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAt( 
            /* [in] */ unsigned int index) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Append( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage *item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAtEnd( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMany( 
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage **items,
            /* [retval][out] */ unsigned int *actual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReplaceAll( 
            /* [in] */ unsigned int count,
            /* [size_is][in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage **value) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *GetAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [in] */ unsigned int index,
            /* [retval][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage **item);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [retval][out] */ unsigned int *size);
        
        HRESULT ( STDMETHODCALLTYPE *GetView )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [retval][out] */ __FIVectorView_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage **view);
        
        HRESULT ( STDMETHODCALLTYPE *IndexOf )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage *item,
            /* [out] */ unsigned int *index,
            /* [retval][out] */ boolean *found);
        
        HRESULT ( STDMETHODCALLTYPE *SetAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [in] */ unsigned int index,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage *item);
        
        HRESULT ( STDMETHODCALLTYPE *InsertAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [in] */ unsigned int index,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage *item);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveAt )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [in] */ unsigned int index);
        
        HRESULT ( STDMETHODCALLTYPE *Append )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage *item);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveAtEnd )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clear )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetMany )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [in] */ unsigned int startIndex,
            /* [in] */ unsigned int capacity,
            /* [size_is][length_is][out] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage **items,
            /* [retval][out] */ unsigned int *actual);
        
        HRESULT ( STDMETHODCALLTYPE *ReplaceAll )( 
            __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage * This,
            /* [in] */ unsigned int count,
            /* [size_is][in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImage **value);
        
        END_INTERFACE
    } __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImageVtbl;

    interface __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage
    {
        CONST_VTBL struct __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetAt(This,index,item)	\
    ( (This)->lpVtbl -> GetAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_get_Size(This,size)	\
    ( (This)->lpVtbl -> get_Size(This,size) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetView(This,view)	\
    ( (This)->lpVtbl -> GetView(This,view) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_IndexOf(This,item,index,found)	\
    ( (This)->lpVtbl -> IndexOf(This,item,index,found) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_SetAt(This,index,item)	\
    ( (This)->lpVtbl -> SetAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_InsertAt(This,index,item)	\
    ( (This)->lpVtbl -> InsertAt(This,index,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_RemoveAt(This,index)	\
    ( (This)->lpVtbl -> RemoveAt(This,index) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_Append(This,item)	\
    ( (This)->lpVtbl -> Append(This,item) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_RemoveAtEnd(This)	\
    ( (This)->lpVtbl -> RemoveAtEnd(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_GetMany(This,startIndex,capacity,items,actual)	\
    ( (This)->lpVtbl -> GetMany(This,startIndex,capacity,items,actual) ) 

#define __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_ReplaceAll(This,count,value)	\
    ( (This)->lpVtbl -> ReplaceAll(This,count,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0112 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage */
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveImageSet[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveImageSet";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0112 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0112_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0112_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSet */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("f618bd35-8fe3-46bd-8988-cdf5607314d1")
                IAdaptiveImageSet : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Images( 
                        /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage **value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ImageSize( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ImageSize *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ImageSize( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ImageSize value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveImageSet = __uuidof(IAdaptiveImageSet);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Images )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet * This,
            /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveImage **value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageSize )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageSize *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImageSize )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageSize value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_get_Images(This,value)	\
    ( (This)->lpVtbl -> get_Images(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_get_ImageSize(This,value)	\
    ( (This)->lpVtbl -> get_ImageSize(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_put_ImageSize(This,value)	\
    ( (This)->lpVtbl -> put_ImageSize(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSet_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0113 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveImageSet_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveImageSet_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveImageSet[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveImageSet";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveInputElement[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveInputElement";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0113 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0113_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0113_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveInputElement */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("9b10f5ef-26e8-4d65-ba76-b986b5e90586")
                IAdaptiveInputElement : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_IsRequired( 
                        /* [out][retval] */ boolean *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_IsRequired( 
                        /* [in] */ boolean value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveInputElement = __uuidof(IAdaptiveInputElement);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsRequired )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement * This,
            /* [out][retval] */ boolean *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsRequired )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement * This,
            /* [in] */ boolean value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElementVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement_get_IsRequired(This,value)	\
    ( (This)->lpVtbl -> get_IsRequired(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement_put_IsRequired(This,value)	\
    ( (This)->lpVtbl -> put_IsRequired(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputElement_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0114 */
/* [local] */ 

#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveChoiceInput[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveChoiceInput";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0114 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0114_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0114_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("99797dfe-d39c-43a4-9f2b-d457cc358e1e")
                IAdaptiveChoiceInput : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ElementType( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ElementType *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Title( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Title( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_IsSelected( 
                        /* [out][retval] */ boolean *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_IsSelected( 
                        /* [in] */ boolean value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveChoiceInput = __uuidof(IAdaptiveChoiceInput);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInputVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ElementType )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CElementType *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Title )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Title )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSelected )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput * This,
            /* [out][retval] */ boolean *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsSelected )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput * This,
            /* [in] */ boolean value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInputVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInputVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_get_ElementType(This,value)	\
    ( (This)->lpVtbl -> get_ElementType(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_get_Title(This,value)	\
    ( (This)->lpVtbl -> get_Title(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_put_Title(This,value)	\
    ( (This)->lpVtbl -> put_Title(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_get_Value(This,value)	\
    ( (This)->lpVtbl -> get_Value(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_put_Value(This,value)	\
    ( (This)->lpVtbl -> put_Value(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_get_IsSelected(This,value)	\
    ( (This)->lpVtbl -> get_IsSelected(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_put_IsSelected(This,value)	\
    ( (This)->lpVtbl -> put_IsSelected(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceInput_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0115 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveChoiceInput_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveChoiceInput_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveChoiceInput[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveChoiceInput";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveChoiceSetInput[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveChoiceSetInput";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0115 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0115_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0115_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceSetInput */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("ce0735ef-f983-4a5e-bdad-f5eb7f962faa")
                IAdaptiveChoiceSetInput : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_IsMultiSelect( 
                        /* [out][retval] */ boolean *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_IsMultiSelect( 
                        /* [in] */ boolean value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ChoiceSetStyle( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ChoiceSetStyle *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ChoiceSetStyle( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ChoiceSetStyle value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Choices( 
                        /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput **value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveChoiceSetInput = __uuidof(IAdaptiveChoiceSetInput);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInputVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsMultiSelect )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput * This,
            /* [out][retval] */ boolean *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsMultiSelect )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput * This,
            /* [in] */ boolean value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ChoiceSetStyle )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CChoiceSetStyle *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ChoiceSetStyle )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CChoiceSetStyle value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Choices )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput * This,
            /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveChoiceInput **value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInputVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInputVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_get_IsMultiSelect(This,value)	\
    ( (This)->lpVtbl -> get_IsMultiSelect(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_put_IsMultiSelect(This,value)	\
    ( (This)->lpVtbl -> put_IsMultiSelect(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_get_ChoiceSetStyle(This,value)	\
    ( (This)->lpVtbl -> get_ChoiceSetStyle(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_put_ChoiceSetStyle(This,value)	\
    ( (This)->lpVtbl -> put_ChoiceSetStyle(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_get_Choices(This,value)	\
    ( (This)->lpVtbl -> get_Choices(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveChoiceSetInput_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0116 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveChoiceSetInput_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveChoiceSetInput_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveChoiceSetInput[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveChoiceSetInput";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveDateInput[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveDateInput";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0116 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0116_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0116_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveDateInput */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("359e2cc5-9b8d-40bf-bbb2-2d3494d30991")
                IAdaptiveDateInput : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Max( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Max( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Min( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Min( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Placeholder( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Placeholder( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
                        /* [in] */ HSTRING value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveDateInput = __uuidof(IAdaptiveDateInput);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInputVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Max )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Max )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Min )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Min )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Placeholder )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Placeholder )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput * This,
            /* [in] */ HSTRING value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInputVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInputVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_get_Max(This,value)	\
    ( (This)->lpVtbl -> get_Max(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_put_Max(This,value)	\
    ( (This)->lpVtbl -> put_Max(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_get_Min(This,value)	\
    ( (This)->lpVtbl -> get_Min(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_put_Min(This,value)	\
    ( (This)->lpVtbl -> put_Min(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_get_Placeholder(This,value)	\
    ( (This)->lpVtbl -> get_Placeholder(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_put_Placeholder(This,value)	\
    ( (This)->lpVtbl -> put_Placeholder(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_get_Value(This,value)	\
    ( (This)->lpVtbl -> get_Value(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_put_Value(This,value)	\
    ( (This)->lpVtbl -> put_Value(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveDateInput_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0117 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveDateInput_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveDateInput_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveDateInput[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveDateInput";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveNumberInput[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveNumberInput";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0117 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0117_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0117_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveNumberInput */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("3bd0868c-5fbd-4341-91ff-4b07eb2bd54c")
                IAdaptiveNumberInput : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Max( 
                        /* [out][retval] */ INT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Max( 
                        /* [in] */ INT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Min( 
                        /* [out][retval] */ INT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Min( 
                        /* [in] */ INT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Placeholder( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Placeholder( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
                        /* [out][retval] */ INT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
                        /* [in] */ INT32 value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveNumberInput = __uuidof(IAdaptiveNumberInput);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInputVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Max )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput * This,
            /* [out][retval] */ INT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Max )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput * This,
            /* [in] */ INT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Min )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput * This,
            /* [out][retval] */ INT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Min )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput * This,
            /* [in] */ INT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Placeholder )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Placeholder )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput * This,
            /* [out][retval] */ INT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput * This,
            /* [in] */ INT32 value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInputVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInputVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_get_Max(This,value)	\
    ( (This)->lpVtbl -> get_Max(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_put_Max(This,value)	\
    ( (This)->lpVtbl -> put_Max(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_get_Min(This,value)	\
    ( (This)->lpVtbl -> get_Min(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_put_Min(This,value)	\
    ( (This)->lpVtbl -> put_Min(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_get_Placeholder(This,value)	\
    ( (This)->lpVtbl -> get_Placeholder(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_put_Placeholder(This,value)	\
    ( (This)->lpVtbl -> put_Placeholder(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_get_Value(This,value)	\
    ( (This)->lpVtbl -> get_Value(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_put_Value(This,value)	\
    ( (This)->lpVtbl -> put_Value(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveNumberInput_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0118 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveNumberInput_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveNumberInput_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveNumberInput[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveNumberInput";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveTextInput[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveTextInput";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0118 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0118_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0118_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextInput */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("ab30772b-172d-4595-bcd2-01001df19d1e")
                IAdaptiveTextInput : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_IsMultiline( 
                        /* [out][retval] */ boolean *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_IsMultiline( 
                        /* [in] */ boolean value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MaxLength( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MaxLength( 
                        /* [in] */ UINT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Placeholder( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Placeholder( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_TextInputStyle( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::TextInputStyle *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_TextInputStyle( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::TextInputStyle value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveTextInput = __uuidof(IAdaptiveTextInput);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInputVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsMultiline )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput * This,
            /* [out][retval] */ boolean *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsMultiline )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput * This,
            /* [in] */ boolean value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxLength )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxLength )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput * This,
            /* [in] */ UINT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Placeholder )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Placeholder )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_TextInputStyle )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextInputStyle *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_TextInputStyle )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextInputStyle value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInputVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInputVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_get_IsMultiline(This,value)	\
    ( (This)->lpVtbl -> get_IsMultiline(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_put_IsMultiline(This,value)	\
    ( (This)->lpVtbl -> put_IsMultiline(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_get_MaxLength(This,value)	\
    ( (This)->lpVtbl -> get_MaxLength(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_put_MaxLength(This,value)	\
    ( (This)->lpVtbl -> put_MaxLength(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_get_Placeholder(This,value)	\
    ( (This)->lpVtbl -> get_Placeholder(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_put_Placeholder(This,value)	\
    ( (This)->lpVtbl -> put_Placeholder(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_get_Value(This,value)	\
    ( (This)->lpVtbl -> get_Value(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_put_Value(This,value)	\
    ( (This)->lpVtbl -> put_Value(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_get_TextInputStyle(This,value)	\
    ( (This)->lpVtbl -> get_TextInputStyle(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_put_TextInputStyle(This,value)	\
    ( (This)->lpVtbl -> put_TextInputStyle(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextInput_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0119 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveTextInput_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveTextInput_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveTextInput[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveTextInput";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveTimeInput[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveTimeInput";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0119 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0119_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0119_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTimeInput */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("1ee90aff-93e8-4292-ac49-39d4c3289cd9")
                IAdaptiveTimeInput : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Max( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Max( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Min( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Min( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Placeholder( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Placeholder( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
                        /* [in] */ HSTRING value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveTimeInput = __uuidof(IAdaptiveTimeInput);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInputVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Max )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Max )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Min )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Min )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Placeholder )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Placeholder )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput * This,
            /* [in] */ HSTRING value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInputVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInputVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_get_Max(This,value)	\
    ( (This)->lpVtbl -> get_Max(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_put_Max(This,value)	\
    ( (This)->lpVtbl -> put_Max(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_get_Min(This,value)	\
    ( (This)->lpVtbl -> get_Min(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_put_Min(This,value)	\
    ( (This)->lpVtbl -> put_Min(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_get_Placeholder(This,value)	\
    ( (This)->lpVtbl -> get_Placeholder(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_put_Placeholder(This,value)	\
    ( (This)->lpVtbl -> put_Placeholder(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_get_Value(This,value)	\
    ( (This)->lpVtbl -> get_Value(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_put_Value(This,value)	\
    ( (This)->lpVtbl -> put_Value(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTimeInput_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0120 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveTimeInput_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveTimeInput_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveTimeInput[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveTimeInput";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveToggleInput[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveToggleInput";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0120 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0120_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0120_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveToggleInput */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("e8af72a5-597c-4a19-b9c2-1a597db1c79a")
                IAdaptiveToggleInput : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Title( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Title( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ValueOff( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ValueOff( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ValueOn( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ValueOn( 
                        /* [in] */ HSTRING value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveToggleInput = __uuidof(IAdaptiveToggleInput);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInputVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Title )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Title )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ValueOff )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ValueOff )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ValueOn )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ValueOn )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput * This,
            /* [in] */ HSTRING value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInputVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInputVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_get_Title(This,value)	\
    ( (This)->lpVtbl -> get_Title(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_put_Title(This,value)	\
    ( (This)->lpVtbl -> put_Title(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_get_Value(This,value)	\
    ( (This)->lpVtbl -> get_Value(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_put_Value(This,value)	\
    ( (This)->lpVtbl -> put_Value(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_get_ValueOff(This,value)	\
    ( (This)->lpVtbl -> get_ValueOff(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_put_ValueOff(This,value)	\
    ( (This)->lpVtbl -> put_ValueOff(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_get_ValueOn(This,value)	\
    ( (This)->lpVtbl -> get_ValueOn(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_put_ValueOn(This,value)	\
    ( (This)->lpVtbl -> put_ValueOn(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveToggleInput_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0121 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveToggleInput_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveToggleInput_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveToggleInput[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveToggleInput";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveContainer[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveContainer";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0121 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0121_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0121_v0_0_s_ifspec;

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
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Style( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ContainerStyle *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Style( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ContainerStyle value) = 0;
                    
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
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CContainerStyle *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CContainerStyle value);
        
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


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_get_Style(This,value)	\
    ( (This)->lpVtbl -> get_Style(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_put_Style(This,value)	\
    ( (This)->lpVtbl -> put_Style(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_get_Items(This,value)	\
    ( (This)->lpVtbl -> get_Items(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainer_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0122 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveContainer_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveContainer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveContainer[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveContainer";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveColumn[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveColumn";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0122 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0122_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0122_v0_0_s_ifspec;

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
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Style( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ContainerStyle *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Style( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ContainerStyle value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Items( 
                        /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement **value) = 0;
                    
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
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CContainerStyle *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CContainerStyle value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Items )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn * This,
            /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveCardElement **value);
        
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


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_get_Width(This,value)	\
    ( (This)->lpVtbl -> get_Width(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_put_Width(This,value)	\
    ( (This)->lpVtbl -> put_Width(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_get_Style(This,value)	\
    ( (This)->lpVtbl -> get_Style(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_put_Style(This,value)	\
    ( (This)->lpVtbl -> put_Style(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_get_Items(This,value)	\
    ( (This)->lpVtbl -> get_Items(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumn_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0123 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveColumn_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveColumn_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveColumn[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveColumn";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveColumnSet[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveColumnSet";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColumnSet_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0123 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0123_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0123_v0_0_s_ifspec;

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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0124 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveColumnSet_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveColumnSet_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveColumnSet[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveColumnSet";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveFact[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveFact";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0124 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0124_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0124_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("5c19aa31-03aa-4148-a529-75b855ba045b")
                IAdaptiveFact : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ElementType( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ElementType *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Title( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Title( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
                        /* [in] */ HSTRING value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveFact = __uuidof(IAdaptiveFact);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ElementType )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CElementType *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Title )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Title )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact * This,
            /* [in] */ HSTRING value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_get_ElementType(This,value)	\
    ( (This)->lpVtbl -> get_ElementType(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_get_Title(This,value)	\
    ( (This)->lpVtbl -> get_Title(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_put_Title(This,value)	\
    ( (This)->lpVtbl -> put_Title(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_get_Value(This,value)	\
    ( (This)->lpVtbl -> get_Value(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_put_Value(This,value)	\
    ( (This)->lpVtbl -> put_Value(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFact_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0125 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveFact_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveFact_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveFact[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveFact";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveFactSet[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveFactSet";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0125 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0125_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0125_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFactSet */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("05457b99-8090-4937-a637-b469f8edc74f")
                IAdaptiveFactSet : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Facts( 
                        /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact **value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveFactSet = __uuidof(IAdaptiveFactSet);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Facts )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet * This,
            /* [out][retval] */ __FIVector_1_AdaptiveCards__CXamlCardRenderer__CIAdaptiveFact **value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet_get_Facts(This,value)	\
    ( (This)->lpVtbl -> get_Facts(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSet_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0126 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveFactSet_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveFactSet_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveFactSet[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveFactSet";
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


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0126 */
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



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0126_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0126_v0_0_s_ifspec;

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
                
                MIDL_INTERFACE("b4f101af-1743-4552-807f-54c0f49a2004")
                IXamlCardRenderer : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ResourceResolvers( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IXamlCardResourceResolvers **value) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE SetRenderOptions( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::RenderOptions options) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE SetOverrideStyles( 
                        /* [in] */ ABI::Windows::UI::Xaml::IResourceDictionary *overrideDictionary) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE SetHostConfig( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfig *hostConfig) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE SetFixedDimensions( 
                        /* [in] */ UINT32 desiredWidth,
                        /* [in] */ UINT32 desiredHeight) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE ResetFixedDimensions( void) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE RenderCardAsXamlAsync( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard *adaptiveCard,
                        /* [out][retval] */ __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement **result) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE RenderAdaptiveCard( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard *adaptiveCard,
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IRenderedAdaptiveCard **result) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE RenderAdaptiveJsonAsXamlAsync( 
                        /* [in] */ HSTRING adaptiveJson,
                        /* [out][retval] */ __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement **result) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE RenderAdaptiveCardFromJsonString( 
                        /* [in] */ HSTRING adaptiveJson,
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IRenderedAdaptiveCard **result) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE RenderAdaptiveCardFromJson( 
                        /* [in] */ ABI::Windows::Data::Json::IJsonObject *adaptiveJson,
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IRenderedAdaptiveCard **result) = 0;
                    
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
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ResourceResolvers )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers **value);
        
        HRESULT ( STDMETHODCALLTYPE *SetRenderOptions )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CRenderOptions options);
        
        HRESULT ( STDMETHODCALLTYPE *SetOverrideStyles )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [in] */ __x_ABI_CWindows_CUI_CXaml_CIResourceDictionary *overrideDictionary);
        
        HRESULT ( STDMETHODCALLTYPE *SetHostConfig )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig *hostConfig);
        
        HRESULT ( STDMETHODCALLTYPE *SetFixedDimensions )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [in] */ UINT32 desiredWidth,
            /* [in] */ UINT32 desiredHeight);
        
        HRESULT ( STDMETHODCALLTYPE *ResetFixedDimensions )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This);
        
        HRESULT ( STDMETHODCALLTYPE *RenderCardAsXamlAsync )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard *adaptiveCard,
            /* [out][retval] */ __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement **result);
        
        HRESULT ( STDMETHODCALLTYPE *RenderAdaptiveCard )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard *adaptiveCard,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard **result);
        
        HRESULT ( STDMETHODCALLTYPE *RenderAdaptiveJsonAsXamlAsync )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [in] */ HSTRING adaptiveJson,
            /* [out][retval] */ __FIAsyncOperation_1_Windows__CUI__CXaml__CUIElement **result);
        
        HRESULT ( STDMETHODCALLTYPE *RenderAdaptiveCardFromJsonString )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [in] */ HSTRING adaptiveJson,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard **result);
        
        HRESULT ( STDMETHODCALLTYPE *RenderAdaptiveCardFromJson )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer * This,
            /* [in] */ __x_ABI_CWindows_CData_CJson_CIJsonObject *adaptiveJson,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard **result);
        
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


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_get_ResourceResolvers(This,value)	\
    ( (This)->lpVtbl -> get_ResourceResolvers(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_SetRenderOptions(This,options)	\
    ( (This)->lpVtbl -> SetRenderOptions(This,options) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_SetOverrideStyles(This,overrideDictionary)	\
    ( (This)->lpVtbl -> SetOverrideStyles(This,overrideDictionary) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_SetHostConfig(This,hostConfig)	\
    ( (This)->lpVtbl -> SetHostConfig(This,hostConfig) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_SetFixedDimensions(This,desiredWidth,desiredHeight)	\
    ( (This)->lpVtbl -> SetFixedDimensions(This,desiredWidth,desiredHeight) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_ResetFixedDimensions(This)	\
    ( (This)->lpVtbl -> ResetFixedDimensions(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_RenderCardAsXamlAsync(This,adaptiveCard,result)	\
    ( (This)->lpVtbl -> RenderCardAsXamlAsync(This,adaptiveCard,result) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_RenderAdaptiveCard(This,adaptiveCard,result)	\
    ( (This)->lpVtbl -> RenderAdaptiveCard(This,adaptiveCard,result) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_RenderAdaptiveJsonAsXamlAsync(This,adaptiveJson,result)	\
    ( (This)->lpVtbl -> RenderAdaptiveJsonAsXamlAsync(This,adaptiveJson,result) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_RenderAdaptiveCardFromJsonString(This,adaptiveJson,result)	\
    ( (This)->lpVtbl -> RenderAdaptiveCardFromJsonString(This,adaptiveJson,result) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_RenderAdaptiveCardFromJson(This,adaptiveJson,result)	\
    ( (This)->lpVtbl -> RenderAdaptiveCardFromJson(This,adaptiveJson,result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardRenderer_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0127 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_XamlCardRenderer_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_XamlCardRenderer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_XamlCardRenderer[] = L"AdaptiveCards.XamlCardRenderer.XamlCardRenderer";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveActionEventArgs[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveActionEventArgs";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0127 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0127_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0127_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionEventArgs */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("6bc7a30c-6971-474d-8dd3-bb9e1bcde381")
                IAdaptiveActionEventArgs : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Action( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement **action) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Inputs( 
                        /* [out][retval] */ ABI::Windows::Data::Json::IJsonObject **value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveActionEventArgs = __uuidof(IAdaptiveActionEventArgs);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Action )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement **action);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Inputs )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs * This,
            /* [out][retval] */ __x_ABI_CWindows_CData_CJson_CIJsonObject **value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgsVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs_get_Action(This,action)	\
    ( (This)->lpVtbl -> get_Action(This,action) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs_get_Inputs(This,value)	\
    ( (This)->lpVtbl -> get_Inputs(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0128 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveActionEventArgs_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveActionEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveActionEventArgs[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveActionEventArgs";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveContainerStyleDefinition[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveContainerStyleDefinition";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0128 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0128_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0128_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleDefinition */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("ae687d0f-ce50-483c-8478-a17d017d4c25")
                IAdaptiveContainerStyleDefinition : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundColor( 
                        /* [out][retval] */ ABI::Windows::UI::Color *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_BackgroundColor( 
                        /* [in] */ ABI::Windows::UI::Color value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ForegroundColors( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorsConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ForegroundColors( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorsConfig *value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveContainerStyleDefinition = __uuidof(IAdaptiveContainerStyleDefinition);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinitionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundColor )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition * This,
            /* [out][retval] */ __x_ABI_CWindows_CUI_CColor *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackgroundColor )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition * This,
            /* [in] */ __x_ABI_CWindows_CUI_CColor value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForegroundColors )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ForegroundColors )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig *value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinitionVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinitionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_get_BackgroundColor(This,value)	\
    ( (This)->lpVtbl -> get_BackgroundColor(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_put_BackgroundColor(This,value)	\
    ( (This)->lpVtbl -> put_BackgroundColor(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_get_ForegroundColors(This,value)	\
    ( (This)->lpVtbl -> get_ForegroundColors(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_put_ForegroundColors(This,value)	\
    ( (This)->lpVtbl -> put_ForegroundColors(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0129 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveContainerStyleDefinition_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveContainerStyleDefinition_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveContainerStyleDefinition[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveContainerStyleDefinition";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveContainerStylesDefinition[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveContainerStylesDefinition";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0129 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0129_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0129_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStylesDefinition */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("7e57fadd-78a6-4501-a769-a8a44bb9f9d2")
                IAdaptiveContainerStylesDefinition : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Default( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleDefinition **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Default( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleDefinition *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Emphasis( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleDefinition **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Emphasis( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleDefinition *value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveContainerStylesDefinition = __uuidof(IAdaptiveContainerStylesDefinition);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinitionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Default )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Default )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Emphasis )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Emphasis )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStyleDefinition *value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinitionVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinitionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_get_Default(This,value)	\
    ( (This)->lpVtbl -> get_Default(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_put_Default(This,value)	\
    ( (This)->lpVtbl -> put_Default(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_get_Emphasis(This,value)	\
    ( (This)->lpVtbl -> get_Emphasis(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_put_Emphasis(This,value)	\
    ( (This)->lpVtbl -> put_Emphasis(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0130 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveContainerStylesDefinition_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveContainerStylesDefinition_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveContainerStylesDefinition[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveContainerStylesDefinition";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveFontSizesConfig[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveFontSizesConfig";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0130 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0130_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0130_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFontSizesConfig */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("ebca0eab-b08b-4087-9c42-4667ec6ab0e0")
                IAdaptiveFontSizesConfig : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Small( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Small( 
                        /* [in] */ UINT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Default( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Default( 
                        /* [in] */ UINT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Medium( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Medium( 
                        /* [in] */ UINT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Large( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Large( 
                        /* [in] */ UINT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ExtraLarge( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ExtraLarge( 
                        /* [in] */ UINT32 value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveFontSizesConfig = __uuidof(IAdaptiveFontSizesConfig);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Small )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Small )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig * This,
            /* [in] */ UINT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Default )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Default )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig * This,
            /* [in] */ UINT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Medium )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Medium )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig * This,
            /* [in] */ UINT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Large )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Large )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig * This,
            /* [in] */ UINT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExtraLarge )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExtraLarge )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig * This,
            /* [in] */ UINT32 value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfigVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_get_Small(This,value)	\
    ( (This)->lpVtbl -> get_Small(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_put_Small(This,value)	\
    ( (This)->lpVtbl -> put_Small(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_get_Default(This,value)	\
    ( (This)->lpVtbl -> get_Default(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_put_Default(This,value)	\
    ( (This)->lpVtbl -> put_Default(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_get_Medium(This,value)	\
    ( (This)->lpVtbl -> get_Medium(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_put_Medium(This,value)	\
    ( (This)->lpVtbl -> put_Medium(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_get_Large(This,value)	\
    ( (This)->lpVtbl -> get_Large(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_put_Large(This,value)	\
    ( (This)->lpVtbl -> put_Large(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_get_ExtraLarge(This,value)	\
    ( (This)->lpVtbl -> get_ExtraLarge(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_put_ExtraLarge(This,value)	\
    ( (This)->lpVtbl -> put_ExtraLarge(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0131 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveFontSizesConfig_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveFontSizesConfig_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveFontSizesConfig[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveFontSizesConfig";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveFontWeightsConfig[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveFontWeightsConfig";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0131 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0131_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0131_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFontWeightsConfig */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("23c9d287-afdc-4ca4-87b4-92c551e4c8bc")
                IAdaptiveFontWeightsConfig : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Lighter( 
                        /* [out][retval] */ UINT16 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Lighter( 
                        /* [in] */ UINT16 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Default( 
                        /* [out][retval] */ UINT16 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Default( 
                        /* [in] */ UINT16 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Bolder( 
                        /* [out][retval] */ UINT16 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Bolder( 
                        /* [in] */ UINT16 value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveFontWeightsConfig = __uuidof(IAdaptiveFontWeightsConfig);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Lighter )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig * This,
            /* [out][retval] */ UINT16 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Lighter )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig * This,
            /* [in] */ UINT16 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Default )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig * This,
            /* [out][retval] */ UINT16 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Default )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig * This,
            /* [in] */ UINT16 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bolder )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig * This,
            /* [out][retval] */ UINT16 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Bolder )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig * This,
            /* [in] */ UINT16 value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfigVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_get_Lighter(This,value)	\
    ( (This)->lpVtbl -> get_Lighter(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_put_Lighter(This,value)	\
    ( (This)->lpVtbl -> put_Lighter(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_get_Default(This,value)	\
    ( (This)->lpVtbl -> get_Default(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_put_Default(This,value)	\
    ( (This)->lpVtbl -> put_Default(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_get_Bolder(This,value)	\
    ( (This)->lpVtbl -> get_Bolder(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_put_Bolder(This,value)	\
    ( (This)->lpVtbl -> put_Bolder(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0132 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveFontWeightsConfig_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveFontWeightsConfig_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveFontWeightsConfig[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveFontWeightsConfig";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveColorConfig[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveColorConfig";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0132 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0132_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0132_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("421149d7-65e9-4ec9-b70b-802ba7d6cf98")
                IAdaptiveColorConfig : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Default( 
                        /* [out][retval] */ ABI::Windows::UI::Color *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Default( 
                        /* [in] */ ABI::Windows::UI::Color value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Subtle( 
                        /* [out][retval] */ ABI::Windows::UI::Color *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Subtle( 
                        /* [in] */ ABI::Windows::UI::Color value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveColorConfig = __uuidof(IAdaptiveColorConfig);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Default )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig * This,
            /* [out][retval] */ __x_ABI_CWindows_CUI_CColor *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Default )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig * This,
            /* [in] */ __x_ABI_CWindows_CUI_CColor value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Subtle )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig * This,
            /* [out][retval] */ __x_ABI_CWindows_CUI_CColor *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Subtle )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig * This,
            /* [in] */ __x_ABI_CWindows_CUI_CColor value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfigVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_get_Default(This,value)	\
    ( (This)->lpVtbl -> get_Default(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_put_Default(This,value)	\
    ( (This)->lpVtbl -> put_Default(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_get_Subtle(This,value)	\
    ( (This)->lpVtbl -> get_Subtle(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_put_Subtle(This,value)	\
    ( (This)->lpVtbl -> put_Subtle(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0133 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveColorConfig_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveColorConfig_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveColorConfig[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveColorConfig";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveColorsConfig[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveColorsConfig";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0133 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0133_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0133_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorsConfig */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("1ade7d94-f0ae-4301-a9e2-b1f9c065916f")
                IAdaptiveColorsConfig : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Default( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Default( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Accent( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Accent( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Dark( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Dark( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Light( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Light( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Good( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Good( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Warning( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Warning( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Attention( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Attention( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig *value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveColorsConfig = __uuidof(IAdaptiveColorsConfig);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Default )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Default )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Accent )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Accent )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dark )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Dark )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Light )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Light )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Good )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Good )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Warning )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Warning )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Attention )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Attention )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorConfig *value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfigVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_get_Default(This,value)	\
    ( (This)->lpVtbl -> get_Default(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_put_Default(This,value)	\
    ( (This)->lpVtbl -> put_Default(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_get_Accent(This,value)	\
    ( (This)->lpVtbl -> get_Accent(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_put_Accent(This,value)	\
    ( (This)->lpVtbl -> put_Accent(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_get_Dark(This,value)	\
    ( (This)->lpVtbl -> get_Dark(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_put_Dark(This,value)	\
    ( (This)->lpVtbl -> put_Dark(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_get_Light(This,value)	\
    ( (This)->lpVtbl -> get_Light(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_put_Light(This,value)	\
    ( (This)->lpVtbl -> put_Light(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_get_Good(This,value)	\
    ( (This)->lpVtbl -> get_Good(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_put_Good(This,value)	\
    ( (This)->lpVtbl -> put_Good(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_get_Warning(This,value)	\
    ( (This)->lpVtbl -> get_Warning(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_put_Warning(This,value)	\
    ( (This)->lpVtbl -> put_Warning(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_get_Attention(This,value)	\
    ( (This)->lpVtbl -> get_Attention(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_put_Attention(This,value)	\
    ( (This)->lpVtbl -> put_Attention(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveColorsConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0134 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveColorsConfig_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveColorsConfig_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveColorsConfig[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveColorsConfig";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveTextConfig[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveTextConfig";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0134 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0134_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0134_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextConfig */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("d730ba59-1f48-4dc6-8375-17f364f6086a")
                IAdaptiveTextConfig : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Weight( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::TextWeight *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Weight( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::TextWeight value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::TextSize *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Size( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::TextSize value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Color( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ForegroundColor *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Color( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ForegroundColor value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_IsSubtle( 
                        /* [out][retval] */ boolean *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_IsSubtle( 
                        /* [in] */ boolean value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Wrap( 
                        /* [out][retval] */ boolean *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Wrap( 
                        /* [in] */ boolean value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MaxWidth( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MaxWidth( 
                        /* [in] */ UINT32 value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveTextConfig = __uuidof(IAdaptiveTextConfig);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Weight )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextWeight *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Weight )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextWeight value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextSize *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Size )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CTextSize value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CForegroundColor *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CForegroundColor value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSubtle )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This,
            /* [out][retval] */ boolean *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsSubtle )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This,
            /* [in] */ boolean value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Wrap )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This,
            /* [out][retval] */ boolean *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Wrap )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This,
            /* [in] */ boolean value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxWidth )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxWidth )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig * This,
            /* [in] */ UINT32 value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfigVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_get_Weight(This,value)	\
    ( (This)->lpVtbl -> get_Weight(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_put_Weight(This,value)	\
    ( (This)->lpVtbl -> put_Weight(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_get_Size(This,value)	\
    ( (This)->lpVtbl -> get_Size(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_put_Size(This,value)	\
    ( (This)->lpVtbl -> put_Size(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_get_Color(This,value)	\
    ( (This)->lpVtbl -> get_Color(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_put_Color(This,value)	\
    ( (This)->lpVtbl -> put_Color(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_get_IsSubtle(This,value)	\
    ( (This)->lpVtbl -> get_IsSubtle(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_put_IsSubtle(This,value)	\
    ( (This)->lpVtbl -> put_IsSubtle(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_get_Wrap(This,value)	\
    ( (This)->lpVtbl -> get_Wrap(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_put_Wrap(This,value)	\
    ( (This)->lpVtbl -> put_Wrap(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_get_MaxWidth(This,value)	\
    ( (This)->lpVtbl -> get_MaxWidth(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_put_MaxWidth(This,value)	\
    ( (This)->lpVtbl -> put_MaxWidth(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0135 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveTextConfig_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveTextConfig_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveTextConfig[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveTextConfig";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveSpacingConfig[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveSpacingConfig";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0135 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0135_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0135_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingConfig */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("0e21ac82-4838-43cb-b7ef-7b023011061b")
                IAdaptiveSpacingConfig : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Small( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Small( 
                        /* [in] */ UINT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Default( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Default( 
                        /* [in] */ UINT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Medium( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Medium( 
                        /* [in] */ UINT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Large( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Large( 
                        /* [in] */ UINT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ExtraLarge( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ExtraLarge( 
                        /* [in] */ UINT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Padding( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Padding( 
                        /* [in] */ UINT32 value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveSpacingConfig = __uuidof(IAdaptiveSpacingConfig);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Small )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Small )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This,
            /* [in] */ UINT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Default )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Default )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This,
            /* [in] */ UINT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Medium )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Medium )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This,
            /* [in] */ UINT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Large )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Large )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This,
            /* [in] */ UINT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExtraLarge )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExtraLarge )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This,
            /* [in] */ UINT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Padding )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Padding )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig * This,
            /* [in] */ UINT32 value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfigVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_get_Small(This,value)	\
    ( (This)->lpVtbl -> get_Small(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_put_Small(This,value)	\
    ( (This)->lpVtbl -> put_Small(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_get_Default(This,value)	\
    ( (This)->lpVtbl -> get_Default(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_put_Default(This,value)	\
    ( (This)->lpVtbl -> put_Default(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_get_Medium(This,value)	\
    ( (This)->lpVtbl -> get_Medium(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_put_Medium(This,value)	\
    ( (This)->lpVtbl -> put_Medium(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_get_Large(This,value)	\
    ( (This)->lpVtbl -> get_Large(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_put_Large(This,value)	\
    ( (This)->lpVtbl -> put_Large(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_get_ExtraLarge(This,value)	\
    ( (This)->lpVtbl -> get_ExtraLarge(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_put_ExtraLarge(This,value)	\
    ( (This)->lpVtbl -> put_ExtraLarge(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_get_Padding(This,value)	\
    ( (This)->lpVtbl -> get_Padding(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_put_Padding(This,value)	\
    ( (This)->lpVtbl -> put_Padding(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0136 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveSpacingConfig_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveSpacingConfig_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveSpacingConfig[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveSpacingConfig";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveSeparatorConfig[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveSeparatorConfig";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0136 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0136_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0136_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparatorConfig */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("c34a155d-6913-4f8b-9b94-f4ab8c578aee")
                IAdaptiveSeparatorConfig : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LineThickness( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_LineThickness( 
                        /* [in] */ UINT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LineColor( 
                        /* [out][retval] */ ABI::Windows::UI::Color *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_LineColor( 
                        /* [in] */ ABI::Windows::UI::Color value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveSeparatorConfig = __uuidof(IAdaptiveSeparatorConfig);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineThickness )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_LineThickness )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig * This,
            /* [in] */ UINT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineColor )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig * This,
            /* [out][retval] */ __x_ABI_CWindows_CUI_CColor *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_LineColor )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig * This,
            /* [in] */ __x_ABI_CWindows_CUI_CColor value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfigVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_get_LineThickness(This,value)	\
    ( (This)->lpVtbl -> get_LineThickness(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_put_LineThickness(This,value)	\
    ( (This)->lpVtbl -> put_LineThickness(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_get_LineColor(This,value)	\
    ( (This)->lpVtbl -> get_LineColor(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_put_LineColor(This,value)	\
    ( (This)->lpVtbl -> put_LineColor(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0137 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveSeparatorConfig_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveSeparatorConfig_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveSeparatorConfig[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveSeparatorConfig";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveImageSizesConfig[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveImageSizesConfig";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0137 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0137_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0137_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSizesConfig */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("ce5cd318-502c-4017-a076-4f8cdbb0316d")
                IAdaptiveImageSizesConfig : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Small( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Small( 
                        /* [in] */ UINT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Medium( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Medium( 
                        /* [in] */ UINT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Large( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Large( 
                        /* [in] */ UINT32 value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveImageSizesConfig = __uuidof(IAdaptiveImageSizesConfig);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Small )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Small )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig * This,
            /* [in] */ UINT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Medium )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Medium )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig * This,
            /* [in] */ UINT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Large )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Large )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig * This,
            /* [in] */ UINT32 value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfigVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_get_Small(This,value)	\
    ( (This)->lpVtbl -> get_Small(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_put_Small(This,value)	\
    ( (This)->lpVtbl -> put_Small(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_get_Medium(This,value)	\
    ( (This)->lpVtbl -> get_Medium(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_put_Medium(This,value)	\
    ( (This)->lpVtbl -> put_Medium(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_get_Large(This,value)	\
    ( (This)->lpVtbl -> get_Large(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_put_Large(This,value)	\
    ( (This)->lpVtbl -> put_Large(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0138 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveImageSizesConfig_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveImageSizesConfig_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveImageSizesConfig[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveImageSizesConfig";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveImageSetConfig[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveImageSetConfig";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0138 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0138_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0138_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSetConfig */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("29685cc3-027f-4da8-9659-6d3a53c34d88")
                IAdaptiveImageSetConfig : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ImageSize( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ImageSize *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ImageSize( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ImageSize value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MaxImageHeight( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MaxImageHeight( 
                        /* [in] */ UINT32 value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveImageSetConfig = __uuidof(IAdaptiveImageSetConfig);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageSize )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageSize *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImageSize )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageSize value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxImageHeight )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxImageHeight )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig * This,
            /* [in] */ UINT32 value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfigVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_get_ImageSize(This,value)	\
    ( (This)->lpVtbl -> get_ImageSize(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_put_ImageSize(This,value)	\
    ( (This)->lpVtbl -> put_ImageSize(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_get_MaxImageHeight(This,value)	\
    ( (This)->lpVtbl -> get_MaxImageHeight(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_put_MaxImageHeight(This,value)	\
    ( (This)->lpVtbl -> put_MaxImageHeight(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0139 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveImageSetConfig_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveImageSetConfig_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveImageSetConfig[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveImageSetConfig";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveImageConfig[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveImageConfig";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0139 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0139_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0139_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageConfig */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("ba0d7d84-d708-4919-a2f2-5c322a6f5460")
                IAdaptiveImageConfig : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ImageSize( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ImageSize *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ImageSize( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ImageSize value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveImageConfig = __uuidof(IAdaptiveImageConfig);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageSize )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageSize *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImageSize )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CImageSize value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfigVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig_get_ImageSize(This,value)	\
    ( (This)->lpVtbl -> get_ImageSize(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig_put_ImageSize(This,value)	\
    ( (This)->lpVtbl -> put_ImageSize(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0140 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveImageConfig_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveImageConfig_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveImageConfig[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveImageConfig";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveCardConfig[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveCardConfig";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0140 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0140_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0140_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardConfig */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("9363ea9c-9f73-4e7d-8d6e-0559ac52b314")
                IAdaptiveCardConfig : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_AllowCustomStyle( 
                        /* [out][retval] */ boolean *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_AllowCustomStyle( 
                        /* [in] */ boolean value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveCardConfig = __uuidof(IAdaptiveCardConfig);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_AllowCustomStyle )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig * This,
            /* [out][retval] */ boolean *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_AllowCustomStyle )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig * This,
            /* [in] */ boolean value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfigVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig_get_AllowCustomStyle(This,value)	\
    ( (This)->lpVtbl -> get_AllowCustomStyle(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig_put_AllowCustomStyle(This,value)	\
    ( (This)->lpVtbl -> put_AllowCustomStyle(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0141 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveCardConfig_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveCardConfig_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveCardConfig[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveCardConfig";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveFactSetConfig[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveFactSetConfig";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0141 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0141_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0141_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFactSetConfig */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("9949ed60-fbc0-49fd-80d4-29fb1184854d")
                IAdaptiveFactSetConfig : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Title( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Title( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Spacing( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Spacing( 
                        /* [in] */ UINT32 value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveFactSetConfig = __uuidof(IAdaptiveFactSetConfig);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Title )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Title )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveTextConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Spacing )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Spacing )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig * This,
            /* [in] */ UINT32 value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfigVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_get_Title(This,value)	\
    ( (This)->lpVtbl -> get_Title(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_put_Title(This,value)	\
    ( (This)->lpVtbl -> put_Title(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_get_Value(This,value)	\
    ( (This)->lpVtbl -> get_Value(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_put_Value(This,value)	\
    ( (This)->lpVtbl -> put_Value(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_get_Spacing(This,value)	\
    ( (This)->lpVtbl -> get_Spacing(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_put_Spacing(This,value)	\
    ( (This)->lpVtbl -> put_Spacing(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0142 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveFactSetConfig_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveFactSetConfig_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveFactSetConfig[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveFactSetConfig";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveShowCardActionConfig[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveShowCardActionConfig";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0142 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0142_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0142_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveShowCardActionConfig */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("eacabf24-288c-4307-bd5a-5888a00da918")
                IAdaptiveShowCardActionConfig : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ActionMode( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ActionMode *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ActionMode( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ActionMode value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Style( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ContainerStyle *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Style( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ContainerStyle value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_InlineTopMargin( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_InlineTopMargin( 
                        /* [in] */ UINT32 value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveShowCardActionConfig = __uuidof(IAdaptiveShowCardActionConfig);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ActionMode )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionMode *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ActionMode )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionMode value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CContainerStyle *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CContainerStyle value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_InlineTopMargin )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_InlineTopMargin )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig * This,
            /* [in] */ UINT32 value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfigVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_get_ActionMode(This,value)	\
    ( (This)->lpVtbl -> get_ActionMode(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_put_ActionMode(This,value)	\
    ( (This)->lpVtbl -> put_ActionMode(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_get_Style(This,value)	\
    ( (This)->lpVtbl -> get_Style(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_put_Style(This,value)	\
    ( (This)->lpVtbl -> put_Style(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_get_InlineTopMargin(This,value)	\
    ( (This)->lpVtbl -> get_InlineTopMargin(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_put_InlineTopMargin(This,value)	\
    ( (This)->lpVtbl -> put_InlineTopMargin(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0143 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveShowCardActionConfig_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveShowCardActionConfig_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveShowCardActionConfig[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveShowCardActionConfig";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveActionsConfig[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveActionsConfig";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0143 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0143_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0143_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionsConfig */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("c01e7195-0c83-4fed-9911-3845bdb8ebc6")
                IAdaptiveActionsConfig : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ShowCard( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveShowCardActionConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ShowCard( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveShowCardActionConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ActionsOrientation( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ActionsOrientation( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ActionAlignment( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ActionAlignment( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ButtonSpacing( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ButtonSpacing( 
                        /* [in] */ UINT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MaxActions( 
                        /* [out][retval] */ UINT32 *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MaxActions( 
                        /* [in] */ UINT32 value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Spacing( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::Spacing *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Spacing( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::Spacing value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveActionsConfig = __uuidof(IAdaptiveActionsConfig);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShowCard )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ShowCard )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ActionsOrientation )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionsOrientation *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ActionsOrientation )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionsOrientation value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ActionAlignment )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionAlignment *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ActionAlignment )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionAlignment value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ButtonSpacing )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ButtonSpacing )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This,
            /* [in] */ UINT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxActions )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This,
            /* [out][retval] */ UINT32 *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxActions )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This,
            /* [in] */ UINT32 value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Spacing )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSpacing *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Spacing )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CSpacing value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfigVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_get_ShowCard(This,value)	\
    ( (This)->lpVtbl -> get_ShowCard(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_put_ShowCard(This,value)	\
    ( (This)->lpVtbl -> put_ShowCard(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_get_ActionsOrientation(This,value)	\
    ( (This)->lpVtbl -> get_ActionsOrientation(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_put_ActionsOrientation(This,value)	\
    ( (This)->lpVtbl -> put_ActionsOrientation(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_get_ActionAlignment(This,value)	\
    ( (This)->lpVtbl -> get_ActionAlignment(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_put_ActionAlignment(This,value)	\
    ( (This)->lpVtbl -> put_ActionAlignment(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_get_ButtonSpacing(This,value)	\
    ( (This)->lpVtbl -> get_ButtonSpacing(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_put_ButtonSpacing(This,value)	\
    ( (This)->lpVtbl -> put_ButtonSpacing(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_get_MaxActions(This,value)	\
    ( (This)->lpVtbl -> get_MaxActions(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_put_MaxActions(This,value)	\
    ( (This)->lpVtbl -> put_MaxActions(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_get_Spacing(This,value)	\
    ( (This)->lpVtbl -> get_Spacing(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_put_Spacing(This,value)	\
    ( (This)->lpVtbl -> put_Spacing(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0144 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveActionsConfig_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveActionsConfig_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveActionsConfig[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveActionsConfig";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveHostConfig[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveHostConfig";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0144 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0144_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0144_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfig */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("85ef9ddc-4599-4ab6-adf1-1e04238601a5")
                IAdaptiveHostConfig : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_FontFamily( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_FontFamily( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_FontSizes( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFontSizesConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_FontSizes( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFontSizesConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_FontWeights( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFontWeightsConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_FontWeights( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFontWeightsConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SupportsInteractivity( 
                        /* [out][retval] */ boolean *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SupportsInteractivity( 
                        /* [in] */ boolean value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ContainerStyles( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStylesDefinition **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ContainerStyles( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStylesDefinition *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ImageSizes( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSizesConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ImageSizes( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSizesConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Separator( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparatorConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Separator( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparatorConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Spacing( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Spacing( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_AdaptiveCard( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_AdaptiveCard( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ImageSet( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSetConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ImageSet( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSetConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Image( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Image( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_FactSet( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFactSetConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_FactSet( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFactSetConfig *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Actions( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionsConfig **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Actions( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionsConfig *value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveHostConfig = __uuidof(IAdaptiveHostConfig);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_FontFamily )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_FontFamily )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_FontSizes )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_FontSizes )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontSizesConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_FontWeights )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_FontWeights )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFontWeightsConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SupportsInteractivity )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [out][retval] */ boolean *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_SupportsInteractivity )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [in] */ boolean value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ContainerStyles )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ContainerStyles )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveContainerStylesDefinition *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageSizes )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImageSizes )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSizesConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Separator )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Separator )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSeparatorConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Spacing )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Spacing )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSpacingConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_AdaptiveCard )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_AdaptiveCard )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCardConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageSet )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImageSet )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageSetConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Image )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Image )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveImageConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_FactSet )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_FactSet )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveFactSetConfig *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Actions )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Actions )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionsConfig *value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_get_FontFamily(This,value)	\
    ( (This)->lpVtbl -> get_FontFamily(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_put_FontFamily(This,value)	\
    ( (This)->lpVtbl -> put_FontFamily(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_get_FontSizes(This,value)	\
    ( (This)->lpVtbl -> get_FontSizes(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_put_FontSizes(This,value)	\
    ( (This)->lpVtbl -> put_FontSizes(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_get_FontWeights(This,value)	\
    ( (This)->lpVtbl -> get_FontWeights(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_put_FontWeights(This,value)	\
    ( (This)->lpVtbl -> put_FontWeights(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_get_SupportsInteractivity(This,value)	\
    ( (This)->lpVtbl -> get_SupportsInteractivity(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_put_SupportsInteractivity(This,value)	\
    ( (This)->lpVtbl -> put_SupportsInteractivity(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_get_ContainerStyles(This,value)	\
    ( (This)->lpVtbl -> get_ContainerStyles(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_put_ContainerStyles(This,value)	\
    ( (This)->lpVtbl -> put_ContainerStyles(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_get_ImageSizes(This,value)	\
    ( (This)->lpVtbl -> get_ImageSizes(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_put_ImageSizes(This,value)	\
    ( (This)->lpVtbl -> put_ImageSizes(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_get_Separator(This,value)	\
    ( (This)->lpVtbl -> get_Separator(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_put_Separator(This,value)	\
    ( (This)->lpVtbl -> put_Separator(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_get_Spacing(This,value)	\
    ( (This)->lpVtbl -> get_Spacing(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_put_Spacing(This,value)	\
    ( (This)->lpVtbl -> put_Spacing(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_get_AdaptiveCard(This,value)	\
    ( (This)->lpVtbl -> get_AdaptiveCard(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_put_AdaptiveCard(This,value)	\
    ( (This)->lpVtbl -> put_AdaptiveCard(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_get_ImageSet(This,value)	\
    ( (This)->lpVtbl -> get_ImageSet(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_put_ImageSet(This,value)	\
    ( (This)->lpVtbl -> put_ImageSet(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_get_Image(This,value)	\
    ( (This)->lpVtbl -> get_Image(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_put_Image(This,value)	\
    ( (This)->lpVtbl -> put_Image(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_get_FactSet(This,value)	\
    ( (This)->lpVtbl -> get_FactSet(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_put_FactSet(This,value)	\
    ( (This)->lpVtbl -> put_FactSet(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_get_Actions(This,value)	\
    ( (This)->lpVtbl -> get_Actions(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_put_Actions(This,value)	\
    ( (This)->lpVtbl -> put_Actions(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0145 */
/* [local] */ 

#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveHostConfigStatics[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveHostConfigStatics";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0145 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0145_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0145_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfigStatics */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("1a09b9b7-d678-495f-949e-3ad677424fdb")
                IAdaptiveHostConfigStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE FromJsonString( 
                        /* [in] */ HSTRING hostConfigJson,
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfig **config) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE FromJson( 
                        /* [in] */ ABI::Windows::Data::Json::IJsonObject *hostConfigJson,
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfig **config) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveHostConfigStatics = __uuidof(IAdaptiveHostConfigStatics);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStaticsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *FromJsonString )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics * This,
            /* [in] */ HSTRING hostConfigJson,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig **config);
        
        HRESULT ( STDMETHODCALLTYPE *FromJson )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics * This,
            /* [in] */ __x_ABI_CWindows_CData_CJson_CIJsonObject *hostConfigJson,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfig **config);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStaticsVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStaticsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics_FromJsonString(This,hostConfigJson,config)	\
    ( (This)->lpVtbl -> FromJsonString(This,hostConfigJson,config) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics_FromJson(This,hostConfigJson,config)	\
    ( (This)->lpVtbl -> FromJson(This,hostConfigJson,config) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveHostConfigStatics_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0146 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveHostConfig_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveHostConfig_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveHostConfig[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveHostConfig";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveActionElement[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveActionElement";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0146 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0146_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0146_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("f0076852-de82-4cc6-8cb3-26cf6ab3c196")
                IAdaptiveActionElement : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ActionType( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ActionType *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Title( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Title( 
                        /* [in] */ HSTRING value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Id( 
                        /* [out][retval] */ HSTRING *value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Id( 
                        /* [in] */ HSTRING value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveActionElement = __uuidof(IAdaptiveActionElement);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ActionType )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CActionType *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Title )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Title )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Id )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Id )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement * This,
            /* [in] */ HSTRING value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElementVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_get_ActionType(This,value)	\
    ( (This)->lpVtbl -> get_ActionType(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_get_Title(This,value)	\
    ( (This)->lpVtbl -> get_Title(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_put_Title(This,value)	\
    ( (This)->lpVtbl -> put_Title(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_get_Id(This,value)	\
    ( (This)->lpVtbl -> get_Id(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_put_Id(This,value)	\
    ( (This)->lpVtbl -> put_Id(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionElement_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0147 */
/* [local] */ 

#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveOpenUrlAction[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveOpenUrlAction";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0147 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0147_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0147_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveOpenUrlAction */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("d70a58cb-4d51-4f96-bb6b-2698eced32ff")
                IAdaptiveOpenUrlAction : public IInspectable
                {
                public:
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Url( 
                        /* [in] */ ABI::Windows::Foundation::IUriRuntimeClass *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Url( 
                        /* [out][retval] */ ABI::Windows::Foundation::IUriRuntimeClass **value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveOpenUrlAction = __uuidof(IAdaptiveOpenUrlAction);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlActionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Url )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction * This,
            /* [in] */ __x_ABI_CWindows_CFoundation_CIUriRuntimeClass *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Url )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction * This,
            /* [out][retval] */ __x_ABI_CWindows_CFoundation_CIUriRuntimeClass **value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlActionVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlActionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction_put_Url(This,value)	\
    ( (This)->lpVtbl -> put_Url(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction_get_Url(This,value)	\
    ( (This)->lpVtbl -> get_Url(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveOpenUrlAction_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0148 */
/* [local] */ 

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveOpenUrlAction;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveOpenUrlAction_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveOpenUrlAction_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveOpenUrlAction[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveOpenUrlAction";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveShowCardAction[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveShowCardAction";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0148 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0148_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0148_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveShowCardAction */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("435ea974-33c7-43b0-a6ac-8137c1b7bb44")
                IAdaptiveShowCardAction : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Card( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Card( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard *value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveShowCardAction = __uuidof(IAdaptiveShowCardAction);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Card )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Card )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard *value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardActionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction_get_Card(This,value)	\
    ( (This)->lpVtbl -> get_Card(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction_put_Card(This,value)	\
    ( (This)->lpVtbl -> put_Card(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveShowCardAction_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0149 */
/* [local] */ 

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveShowCardAction;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveShowCardAction_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveShowCardAction_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveShowCardAction[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveShowCardAction";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveSubmitAction[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveSubmitAction";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0149 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0149_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0149_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSubmitAction */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("97b9b3a3-657b-4d38-a136-154cc8da19a9")
                IAdaptiveSubmitAction : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DataJson( 
                        /* [out][retval] */ ABI::Windows::Data::Json::IJsonObject **value) = 0;
                    
                    virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_DataJson( 
                        /* [in] */ ABI::Windows::Data::Json::IJsonObject *value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveSubmitAction = __uuidof(IAdaptiveSubmitAction);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitActionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataJson )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction * This,
            /* [out][retval] */ __x_ABI_CWindows_CData_CJson_CIJsonObject **value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DataJson )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction * This,
            /* [in] */ __x_ABI_CWindows_CData_CJson_CIJsonObject *value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitActionVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitActionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction_get_DataJson(This,value)	\
    ( (This)->lpVtbl -> get_DataJson(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction_put_DataJson(This,value)	\
    ( (This)->lpVtbl -> put_DataJson(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveSubmitAction_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0150 */
/* [local] */ 

#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
class AdaptiveSubmitAction;
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveSubmitAction_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveSubmitAction_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveSubmitAction[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveSubmitAction";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IXamlCardResourceResolvers[] = L"AdaptiveCards.XamlCardRenderer.IXamlCardResourceResolvers";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0150 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0150_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0150_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IXamlCardResourceResolvers */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("3b655db6-54d2-47e7-8658-b58ced5fb237")
                IXamlCardResourceResolvers : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE Set( 
                        /* [in] */ HSTRING scheme,
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IXamlCardResourceResolver *resolver) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE Get( 
                        /* [in] */ HSTRING scheme,
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IXamlCardResourceResolver **resolver) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IXamlCardResourceResolvers = __uuidof(IXamlCardResourceResolvers);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolversVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *Set )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers * This,
            /* [in] */ HSTRING scheme,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver *resolver);
        
        HRESULT ( STDMETHODCALLTYPE *Get )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers * This,
            /* [in] */ HSTRING scheme,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver **resolver);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolversVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolversVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers_Set(This,scheme,resolver)	\
    ( (This)->lpVtbl -> Set(This,scheme,resolver) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers_Get(This,scheme,resolver)	\
    ( (This)->lpVtbl -> Get(This,scheme,resolver) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolvers_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0151 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_XamlCardResourceResolvers_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_XamlCardResourceResolvers_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_XamlCardResourceResolvers[] = L"AdaptiveCards.XamlCardRenderer.XamlCardResourceResolvers";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IXamlCardResourceResolver[] = L"AdaptiveCards.XamlCardRenderer.IXamlCardResourceResolver";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0151 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0151_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0151_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IXamlCardResourceResolver */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("30f17ba9-133a-4484-8002-a8f4b6764e3f")
                IXamlCardResourceResolver : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE GetResourceStreamAsync( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IXamlCardGetResourceStreamArgs *args,
                        /* [out][retval] */ __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream **result) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IXamlCardResourceResolver = __uuidof(IXamlCardResourceResolver);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *GetResourceStreamAsync )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs *args,
            /* [out][retval] */ __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream **result);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolverVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver_GetResourceStreamAsync(This,args,result)	\
    ( (This)->lpVtbl -> GetResourceStreamAsync(This,args,result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardResourceResolver_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0152 */
/* [local] */ 

#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IXamlCardGetResourceStreamArgsFactory[] = L"AdaptiveCards.XamlCardRenderer.IXamlCardGetResourceStreamArgsFactory";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0152 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0152_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0152_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IXamlCardGetResourceStreamArgsFactory */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("e1d63f44-6550-454f-99f4-d02df5ae9b8c")
                IXamlCardGetResourceStreamArgsFactory : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE CreateXamlCardGetResourceStreamArgs( 
                        /* [in] */ ABI::Windows::Foundation::IUriRuntimeClass *value,
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IXamlCardGetResourceStreamArgs **args) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IXamlCardGetResourceStreamArgsFactory = __uuidof(IXamlCardGetResourceStreamArgsFactory);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *CreateXamlCardGetResourceStreamArgs )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory * This,
            /* [in] */ __x_ABI_CWindows_CFoundation_CIUriRuntimeClass *value,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs **args);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactoryVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory_CreateXamlCardGetResourceStreamArgs(This,value,args)	\
    ( (This)->lpVtbl -> CreateXamlCardGetResourceStreamArgs(This,value,args) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsFactory_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0153 */
/* [local] */ 

#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IXamlCardGetResourceStreamArgs[] = L"AdaptiveCards.XamlCardRenderer.IXamlCardGetResourceStreamArgs";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0153 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0153_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0153_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IXamlCardGetResourceStreamArgs */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("0eea761b-5a3e-4f1f-86f6-d511c178e671")
                IXamlCardGetResourceStreamArgs : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Url( 
                        /* [out][retval] */ ABI::Windows::Foundation::IUriRuntimeClass **value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IXamlCardGetResourceStreamArgs = __uuidof(IXamlCardGetResourceStreamArgs);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Url )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs * This,
            /* [out][retval] */ __x_ABI_CWindows_CFoundation_CIUriRuntimeClass **value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs_get_Url(This,value)	\
    ( (This)->lpVtbl -> get_Url(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIXamlCardGetResourceStreamArgs_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0154 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_XamlCardGetResourceStreamArgs_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_XamlCardGetResourceStreamArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_XamlCardGetResourceStreamArgs[] = L"AdaptiveCards.XamlCardRenderer.XamlCardGetResourceStreamArgs";
#endif


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0154 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0154_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0154_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5467 */




/* interface __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5467 */




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5467_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp2Eidl_0000_5467_v0_0_s_ifspec;

/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0155 */
/* [local] */ 

#ifndef DEF___FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs
#define DEF___FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs
#if !defined(__cplusplus) || defined(RO_NO_TEMPLATE_NAME)


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0155 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0155_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0155_v0_0_s_ifspec;

#ifndef ____FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs_INTERFACE_DEFINED__
#define ____FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs_INTERFACE_DEFINED__

/* interface __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs */
/* [unique][uuid][object] */ 



/* interface __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID___FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a5828abb-42c3-54fa-b7d0-001e85b4b639")
    __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Invoke( 
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IRenderedAdaptiveCard *sender,
            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionEventArgs *e) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs * This);
        
        HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard *sender,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveActionEventArgs *e);
        
        END_INTERFACE
    } __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgsVtbl;

    interface __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs
    {
        CONST_VTBL struct __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs_Invoke(This,sender,e)	\
    ( (This)->lpVtbl -> Invoke(This,sender,e) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0156 */
/* [local] */ 

#endif /* pinterface */
#endif /* DEF___FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs */
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IRenderedAdaptiveCard[] = L"AdaptiveCards.XamlCardRenderer.IRenderedAdaptiveCard";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0156 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0156_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0156_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IRenderedAdaptiveCard */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("7bf9ceac-105c-421a-8b4e-8e5be9ead986")
                IRenderedAdaptiveCard : public IInspectable
                {
                public:
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_OriginatingCard( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard **value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_FrameworkElement( 
                        /* [out][retval] */ ABI::Windows::UI::Xaml::IUIElement **value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_IsRenderedSuccessfully( 
                        /* [out][retval] */ boolean *value) = 0;
                    
                    virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_UserInputs( 
                        /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveInputs **value) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE add_Action( 
                        /* [in] */ __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs *pHandler,
                        /* [out][retval] */ EventRegistrationToken *pToken) = 0;
                    
                    virtual HRESULT STDMETHODCALLTYPE remove_Action( 
                        /* [in] */ EventRegistrationToken token) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IRenderedAdaptiveCard = __uuidof(IRenderedAdaptiveCard);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCardVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_OriginatingCard )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveCard **value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_FrameworkElement )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard * This,
            /* [out][retval] */ __x_ABI_CWindows_CUI_CXaml_CIUIElement **value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsRenderedSuccessfully )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard * This,
            /* [out][retval] */ boolean *value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_UserInputs )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs **value);
        
        HRESULT ( STDMETHODCALLTYPE *add_Action )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard * This,
            /* [in] */ __FITypedEventHandler_2_AdaptiveCards__CXamlCardRenderer__CRenderedAdaptiveCard_AdaptiveCards__CXamlCardRenderer__CAdaptiveActionEventArgs *pHandler,
            /* [out][retval] */ EventRegistrationToken *pToken);
        
        HRESULT ( STDMETHODCALLTYPE *remove_Action )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard * This,
            /* [in] */ EventRegistrationToken token);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCardVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCardVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_get_OriginatingCard(This,value)	\
    ( (This)->lpVtbl -> get_OriginatingCard(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_get_FrameworkElement(This,value)	\
    ( (This)->lpVtbl -> get_FrameworkElement(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_get_IsRenderedSuccessfully(This,value)	\
    ( (This)->lpVtbl -> get_IsRenderedSuccessfully(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_get_UserInputs(This,value)	\
    ( (This)->lpVtbl -> get_UserInputs(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_add_Action(This,pHandler,pToken)	\
    ( (This)->lpVtbl -> add_Action(This,pHandler,pToken) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_remove_Action(This,token)	\
    ( (This)->lpVtbl -> remove_Action(This,token) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIRenderedAdaptiveCard_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0157 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_RenderedAdaptiveCard_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_RenderedAdaptiveCard_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_RenderedAdaptiveCard[] = L"AdaptiveCards.XamlCardRenderer.RenderedAdaptiveCard";
#endif
#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_IAdaptiveInputs[] = L"AdaptiveCards.XamlCardRenderer.IAdaptiveInputs";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0157 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0157_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0157_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveInputs */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                
                MIDL_INTERFACE("a172be96-7ab5-4faa-a0fd-99e8160e359e")
                IAdaptiveInputs : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE AsJson( 
                        /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::InputValueMode inputMode,
                        /* [out][retval] */ ABI::Windows::Data::Json::IJsonObject **value) = 0;
                    
                };

                extern const __declspec(selectany) IID & IID_IAdaptiveInputs = __uuidof(IAdaptiveInputs);

                
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *AsJson )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CInputValueMode inputMode,
            /* [out][retval] */ __x_ABI_CWindows_CData_CJson_CIJsonObject **value);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputsVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs_AsJson(This,inputMode,value)	\
    ( (This)->lpVtbl -> AsJson(This,inputMode,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CIAdaptiveInputs_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0158 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveInputs_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_AdaptiveInputs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveInputs[] = L"AdaptiveCards.XamlCardRenderer.AdaptiveInputs";
#endif


/* interface __MIDL_itf_AdaptiveCards2EUwp_0000_0158 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0158_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EUwp_0000_0158_v0_0_s_ifspec;

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


