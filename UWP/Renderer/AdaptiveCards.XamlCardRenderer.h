

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0620 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for C:\Users\riarenas\AppData\Local\Temp\AdaptiveCards.XamlCardRenderer.idl-0aef13a4:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0620 
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


#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_FWD_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_FWD_DEFINED__
typedef interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock;

#ifdef __cplusplus
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            namespace ObjectModel {
                interface IAdaptiveTextBlock;
            } /* end namespace */
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_FWD_DEFINED__ */


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
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CSize
    {
        Size_Auto	= 0,
        Size_Stretch	= ( Size_Auto + 1 ) ,
        Size_Small	= ( Size_Stretch + 1 ) ,
        Size_Medium	= ( Size_Small + 1 ) ,
        Size_Large	= ( Size_Medium + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CSize __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CSize;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CTextSize
    {
        TextSize_Small	= 0,
        TextSize_Normal	= ( TextSize_Small + 1 ) ,
        TextSize_Medium	= ( TextSize_Normal + 1 ) ,
        TextSize_Large	= ( TextSize_Medium + 1 ) ,
        TextSize_ExtraLarge	= ( TextSize_Large + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CTextSize __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CTextSize;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CTextWeight
    {
        TextWeight_Lighter	= 0,
        TextWeight_Normal	= ( TextWeight_Lighter + 1 ) ,
        TextWeight_Bolder	= ( TextWeight_Normal + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CTextWeight __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CTextWeight;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CTextColor
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

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CTextColor __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CTextColor;


#endif /* end if !defined(__cplusplus) */


#endif
#if !defined(__cplusplus)

#if !defined(__cplusplus)
/* [v1_enum] */ 
enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CHAlignment
    {
        HAlignment_Left	= 0,
        HAlignment_Center	= ( HAlignment_Left + 1 ) ,
        HAlignment_Right	= ( HAlignment_Center + 1 ) 
    } ;
#endif /* end if !defined(__cplusplus) */

#if !defined(__cplusplus)

typedef enum __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CHAlignment __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CHAlignment;


#endif /* end if !defined(__cplusplus) */


#endif
#ifdef __cplusplus
namespace ABI {
namespace AdaptiveCards {
namespace XamlCardRenderer {
namespace ObjectModel {
class AdaptiveTextBlock;
} /*ObjectModel*/
} /*XamlCardRenderer*/
} /*AdaptiveCards*/
}
#endif

#if !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_AdaptiveCards_XamlCardRenderer_ObjectModel_IAdaptiveTextBlock[] = L"AdaptiveCards.XamlCardRenderer.ObjectModel.IAdaptiveTextBlock";
#endif /* !defined(____x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0001 */
/* [local] */ 

#ifdef __cplusplus
} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            namespace ObjectModel {
                
                /* [v1_enum] */ 
                MIDL_ENUM Size
                    {
                        Auto	= 0,
                        Stretch	= ( Auto + 1 ) ,
                        Small	= ( Stretch + 1 ) ,
                        Medium	= ( Small + 1 ) ,
                        Large	= ( Medium + 1 ) 
                    } ;

                const MIDL_ENUM Size Size_Auto = Size::Auto;
                const MIDL_ENUM Size Size_Stretch = Size::Stretch;
                const MIDL_ENUM Size Size_Small = Size::Small;
                const MIDL_ENUM Size Size_Medium = Size::Medium;
                const MIDL_ENUM Size Size_Large = Size::Large;
                
            } /* end namespace */
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
            namespace ObjectModel {
                
                typedef MIDL_ENUM Size Size;
                
            } /* end namespace */
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
            namespace ObjectModel {
                
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
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus

} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            namespace ObjectModel {
                
                typedef MIDL_ENUM TextSize TextSize;
                
            } /* end namespace */
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
            namespace ObjectModel {
                
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
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus

} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            namespace ObjectModel {
                
                typedef MIDL_ENUM TextWeight TextWeight;
                
            } /* end namespace */
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
            namespace ObjectModel {
                
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
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus

} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            namespace ObjectModel {
                
                typedef MIDL_ENUM TextColor TextColor;
                
            } /* end namespace */
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
            namespace ObjectModel {
                
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
} /* end namespace */

extern "C" { 
#endif

#ifdef __cplusplus

} /* end extern "C" */
namespace ABI {
    namespace AdaptiveCards {
        namespace XamlCardRenderer {
            namespace ObjectModel {
                
                typedef MIDL_ENUM HAlignment HAlignment;
                
            } /* end namespace */
        } /* end namespace */
    } /* end namespace */
} /* end namespace */

extern "C" { 
#endif




extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0001_v0_0_s_ifspec;

#ifndef ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_INTERFACE_DEFINED__
#define ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_INTERFACE_DEFINED__

/* interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock */
/* [uuid][object] */ 



/* interface ABI::AdaptiveCards::XamlCardRenderer::ObjectModel::IAdaptiveTextBlock */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace AdaptiveCards {
            namespace XamlCardRenderer {
                namespace ObjectModel {
                    
                    MIDL_INTERFACE("f3b844da-2d6a-4003-8a57-4e5541fcd078")
                    IAdaptiveTextBlock : public IInspectable
                    {
                    public:
                        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_TextSize( 
                            /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ObjectModel::TextSize *value) = 0;
                        
                        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_TextSize( 
                            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ObjectModel::TextSize value) = 0;
                        
                        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_TextWeight( 
                            /* [out][retval] */ ABI::AdaptiveCards::XamlCardRenderer::ObjectModel::TextWeight *value) = 0;
                        
                        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_TextWeight( 
                            /* [in] */ ABI::AdaptiveCards::XamlCardRenderer::ObjectModel::TextWeight value) = 0;
                        
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
                        
                        virtual HRESULT STDMETHODCALLTYPE Render( 
                            /* [out][retval] */ ABI::Windows::UI::Xaml::IUIElement **uiElement) = 0;
                        
                    };

                    extern const __declspec(selectany) IID & IID_IAdaptiveTextBlock = __uuidof(IAdaptiveTextBlock);

                    
                }  /* end namespace */
            }  /* end namespace */
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlockVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This,
            /* [out] */ TrustLevel *trustLevel);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_TextSize )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CTextSize *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_TextSize )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CTextSize value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_TextWeight )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This,
            /* [out][retval] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CTextWeight *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_TextWeight )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This,
            /* [in] */ __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CTextWeight value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Text )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This,
            /* [out][retval] */ HSTRING *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Text )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This,
            /* [in] */ HSTRING value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSubtle )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This,
            /* [out][retval] */ boolean *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsSubtle )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This,
            /* [in] */ boolean value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Wrap )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This,
            /* [out][retval] */ boolean *value);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Wrap )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This,
            /* [in] */ boolean value);
        
        HRESULT ( STDMETHODCALLTYPE *Render )( 
            __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock * This,
            /* [out][retval] */ __x_ABI_CWindows_CUI_CXaml_CIUIElement **uiElement);
        
        END_INTERFACE
    } __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlockVtbl;

    interface __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock
    {
        CONST_VTBL struct __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlockVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_get_TextSize(This,value)	\
    ( (This)->lpVtbl -> get_TextSize(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_put_TextSize(This,value)	\
    ( (This)->lpVtbl -> put_TextSize(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_get_TextWeight(This,value)	\
    ( (This)->lpVtbl -> get_TextWeight(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_put_TextWeight(This,value)	\
    ( (This)->lpVtbl -> put_TextWeight(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_get_Text(This,value)	\
    ( (This)->lpVtbl -> get_Text(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_put_Text(This,value)	\
    ( (This)->lpVtbl -> put_Text(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_get_IsSubtle(This,value)	\
    ( (This)->lpVtbl -> get_IsSubtle(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_put_IsSubtle(This,value)	\
    ( (This)->lpVtbl -> put_IsSubtle(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_get_Wrap(This,value)	\
    ( (This)->lpVtbl -> get_Wrap(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_put_Wrap(This,value)	\
    ( (This)->lpVtbl -> put_Wrap(This,value) ) 

#define __x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_Render(This,uiElement)	\
    ( (This)->lpVtbl -> Render(This,uiElement) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CAdaptiveCards_CXamlCardRenderer_CObjectModel_CIAdaptiveTextBlock_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0002 */
/* [local] */ 

#ifndef RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_ObjectModel_AdaptiveTextBlock_DEFINED
#define RUNTIMECLASS_AdaptiveCards_XamlCardRenderer_ObjectModel_AdaptiveTextBlock_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_AdaptiveCards_XamlCardRenderer_ObjectModel_AdaptiveTextBlock[] = L"AdaptiveCards.XamlCardRenderer.ObjectModel.AdaptiveTextBlock";
#endif


/* interface __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0002 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AdaptiveCards2EXamlCardRenderer_0000_0002_v0_0_s_ifspec;

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


