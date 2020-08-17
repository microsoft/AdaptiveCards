// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ImageLoadTracker.h"
#include "IXamlBuilderListener.h"
#include "IImageLoadTrackerListener.h"
#include "InputValue.h"
#include "RenderedAdaptiveCard.h"
#include "AdaptiveRenderContext.h"

namespace AdaptiveNamespace
{
    class AdaptiveCardRenderer;

    class XamlBuilder
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, Microsoft::WRL::FtmBase, AdaptiveNamespace::IImageLoadTrackerListener>
    {
        friend HRESULT Microsoft::WRL::Details::MakeAndInitialize<AdaptiveNamespace::XamlBuilder, AdaptiveNamespace::XamlBuilder>(
            AdaptiveNamespace::XamlBuilder**);

        AdaptiveRuntimeStringClass(XamlBuilder);

    public:
        // IImageLoadTrackerListener
        STDMETHODIMP AllImagesLoaded() noexcept;
        STDMETHODIMP ImagesLoadingHadError() noexcept;

        static HRESULT BuildXamlTreeFromAdaptiveCard(_In_ ABI::AdaptiveNamespace::IAdaptiveCard* adaptiveCard,
                                                     _COM_Outptr_ ABI::Windows::UI::Xaml::IFrameworkElement** xamlTreeRoot,
                                                     _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                                     Microsoft::WRL::ComPtr<XamlBuilder> xamlBuilder,
                                                     ABI::AdaptiveNamespace::ContainerStyle defaultContainerStyle =
                                                         ABI::AdaptiveNamespace::ContainerStyle::Default) noexcept;
        HRESULT AddListener(_In_ IXamlBuilderListener* listener) noexcept;
        HRESULT RemoveListener(_In_ IXamlBuilderListener* listener) noexcept;
        void SetFixedDimensions(UINT width, UINT height) noexcept;
        void SetEnableXamlImageHandling(bool enableXamlImageHandling) noexcept;

        static HRESULT BuildPanelChildren(
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>* children,
            _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* context,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            std::function<void(ABI::Windows::UI::Xaml::IUIElement* child)> childCreatedCallback) noexcept;

        HRESULT BuildImage(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                           _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                           _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                           _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** imageControl);

    private:
        XamlBuilder();

        ImageLoadTracker m_imageLoadTracker;
        std::set<Microsoft::WRL::ComPtr<IXamlBuilderListener>> m_listeners;
        Microsoft::WRL::ComPtr<ABI::Windows::Storage::Streams::IRandomAccessStreamStatics> m_randomAccessStreamStatics;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<ABI::Windows::Storage::Streams::IInputStream*, ABI::Windows::Web::Http::HttpProgress>>> m_getStreamOperations;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<UINT64, UINT64>>> m_copyStreamOperations;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<UINT32, UINT32>>> m_writeAsyncOperations;

        UINT m_fixedWidth = 0;
        UINT m_fixedHeight = 0;
        bool m_fixedDimensions = false;
        bool m_enableXamlImageHandling = false;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardResourceResolvers> m_resourceResolvers;

        static HRESULT CreateRootCardElement(_In_ ABI::AdaptiveNamespace::IAdaptiveCard* adaptiveCard,
                                             _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                             _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                             Microsoft::WRL::ComPtr<XamlBuilder> xamlBuilder,
                                             _COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IPanel** bodyElementContainer,
                                             _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** rootUIElement) noexcept;

        template<typename T>
        void SetAutoSize(T* destination, IInspectable* parentElement, IInspectable* imageContainer, bool isVisible, bool imageFiresOpenEvent);

        template<typename T>
        void SetImageSource(T* destination,
                            ABI::Windows::UI::Xaml::Media::IImageSource* imageSource,
                            ABI::Windows::UI::Xaml::Media::Stretch stretch = Stretch_UniformToFill);
        template<typename T>
        void SetImageOnUIElement(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl,
                                 T* uiElement,
                                 ABI::AdaptiveNamespace::IAdaptiveCardResourceResolvers* resolvers,
                                 bool isSizeAuto,
                                 IInspectable* parentElement,
                                 IInspectable* imageContainer,
                                 bool isVisible,
                                 _Out_ bool* mustHideElement,
                                 ABI::Windows::UI::Xaml::Media::Stretch stretch = Stretch_UniformToFill);

        template<typename T>
        void PopulateImageFromUrlAsync(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl, _In_ T* imageControl);

        void FireAllImagesLoaded();
        void FireImagesLoadingHadError();
    };
}
