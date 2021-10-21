// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ImageLoadTracker.h"
#include "IXamlBuilderListener.h"
#include "IImageLoadTrackerListener.h"
#include "InputValue.h"
#include "RenderedAdaptiveCard.h"
#include "AdaptiveRenderContext.h"

namespace AdaptiveCards::Rendering::WinUI3
{
    struct XamlBuilder : winrt::implements<XamlBuilder, ::AdaptiveCards::Rendering::WinUI3::IImageLoadTrackerListener>
    {
    public:
        XamlBuilder();

        // IImageLoadTrackerListener
        STDMETHODIMP AllImagesLoaded() noexcept;
        STDMETHODIMP ImagesLoadingHadError() noexcept;

        static HRESULT BuildXamlTreeFromAdaptiveCard(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* adaptiveCard,
                                                     _COM_Outptr_ ABI::Windows::UI::Xaml::IFrameworkElement** xamlTreeRoot,
                                                     _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                                                     Microsoft::WRL::ComPtr<XamlBuilder> xamlBuilder,
                                                     ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle defaultContainerStyle =
                                                         ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle::Default) noexcept;

        static winrt::Windows::UI::Xaml::FrameworkElement
        BuildXamlTreeFromAdaptiveCard(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveCard const& adaptiveCard,
                                      winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext renderContext,
                                      XamlBuilder* xamlBuilder,
                                      winrt::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle defaultContainerStyle =
                                          winrt::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle::Default);

        HRESULT AddListener(_In_ ::AdaptiveCards::Rendering::WinUI3::IXamlBuilderListener* listener) noexcept;
        HRESULT RemoveListener(_In_ ::AdaptiveCards::Rendering::WinUI3::IXamlBuilderListener* listener) noexcept;
        void SetFixedDimensions(UINT width, UINT height) noexcept;
        void SetEnableXamlImageHandling(bool enableXamlImageHandling) noexcept;

        static HRESULT BuildPanelChildren(
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement*>* children,
            _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
            _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* context,
            _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
            std::function<void(ABI::Windows::UI::Xaml::IUIElement* child)> childCreatedCallback) noexcept;
		
		void BuildPanelChildren(
            winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement> const& children,
			rtxaml::Controls::Panel ParentPanel,
            rtrender::AdaptiveRenderContext context,
            rtrender::AdaptiveRenderArgs renderArgs,
            std::function<void(rtxaml::UIElement child)> childCreatedCallback);

        HRESULT BuildImage(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement* adaptiveCardElement,
                           _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                           _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                           _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** imageControl);

    private:
        ::AdaptiveCards::Rendering::WinUI3::ImageLoadTracker m_imageLoadTracker;
        std::set<Microsoft::WRL::ComPtr<::AdaptiveCards::Rendering::WinUI3::IXamlBuilderListener>> m_listeners;
        Microsoft::WRL::ComPtr<ABI::Windows::Storage::Streams::IRandomAccessStreamStatics> m_randomAccessStreamStatics;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<ABI::Windows::Storage::Streams::IInputStream*, ABI::Windows::Web::Http::HttpProgress>>> m_getStreamOperations;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<UINT64, UINT64>>> m_copyStreamOperations;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<UINT32, UINT32>>> m_writeAsyncOperations;

        UINT m_fixedWidth = 0;
        UINT m_fixedHeight = 0;
        bool m_fixedDimensions = false;
        bool m_enableXamlImageHandling = false;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveCardResourceResolvers> m_resourceResolvers;

        static HRESULT CreateRootCardElement(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* adaptiveCard,
                                             _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                                             _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
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
                                 ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveCardResourceResolvers* resolvers,
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
