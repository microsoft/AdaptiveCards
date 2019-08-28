// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;

using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Shapes;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Media;

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("0F485063-EF2A-400E-A946-73E00EDFAC83") TileControl
        : public Microsoft::WRL::RuntimeClass<ABI::AdaptiveNamespace::ITileControl,
                                              ABI::Windows::UI::Xaml::IFrameworkElementOverrides,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::ComposableBase<ABI::Windows::UI::Xaml::Controls::IContentControlFactory>>
    {
        AdaptiveRuntimeStringClass(TileControl);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        virtual HRESULT STDMETHODCALLTYPE put_BackgroundImage(_In_ IAdaptiveBackgroundImage* value);
        virtual HRESULT STDMETHODCALLTYPE put_RootElement(_In_ IFrameworkElement* value);
        virtual HRESULT STDMETHODCALLTYPE get_ResolvedImage(_Outptr_ IUIElement** value);
        virtual HRESULT STDMETHODCALLTYPE put_ImageSize(ABI::Windows::Foundation::Size value);

        virtual HRESULT STDMETHODCALLTYPE LoadImageBrush(_In_ IUIElement* image);

        // IFrameworkElementOverrides overrides
        virtual HRESULT STDMETHODCALLTYPE OnApplyTemplate();
        virtual HRESULT STDMETHODCALLTYPE MeasureOverride(_In_ Size availableSize, _Out_ Size* pReturnValue);
        virtual HRESULT STDMETHODCALLTYPE ArrangeOverride(_In_ Size arrangeBounds, _Out_ Size* pReturnValue);

        // not implemented
        virtual HRESULT STDMETHODCALLTYPE get_BackgroundImage(_Outptr_ IAdaptiveBackgroundImage** /*value*/) { return E_NOTIMPL; }
        virtual HRESULT STDMETHODCALLTYPE get_RootElement(_Outptr_ IFrameworkElement** /*value*/) { return E_NOTIMPL; }
        virtual HRESULT STDMETHODCALLTYPE put_ResolvedImage(_In_ IUIElement* /*value*/) { return E_NOTIMPL; }
        virtual HRESULT STDMETHODCALLTYPE get_ImageSize(_Out_ ABI::Windows::Foundation::Size* /*value*/)
        {
            return E_NOTIMPL;
        }

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        void RefreshContainerTile();
        HRESULT ExtractBackgroundImageData(_Out_ ABI::AdaptiveNamespace::BackgroundImageFillMode* fillMode,
                                           _Out_ ABI::AdaptiveNamespace::HAlignment* hAlignment,
                                           _Out_ ABI::AdaptiveNamespace::VAlignment* vAlignment);

        // Fields
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IFrameworkElement> m_rootElement;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_resolvedImage;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::ICanvas> m_containerElement;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::IImageBrush> m_brushXaml;

        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveBackgroundImage> m_adaptiveBackgroundImage;
        ABI::Windows::Foundation::Size m_imageSize{};
        ABI::Windows::Foundation::Size m_containerSize{};
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Shapes::IRectangle>> m_xamlChildren;
    };
    ActivatableClass(TileControl);
}
