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
    /*struct XamlBuilder : winrt::implements<XamlBuilder, ::AdaptiveCards::Rendering::WinUI3::IImageLoadTrackerListener>*/
    struct XamlBuilder : winrt::implements<XamlBuilder, IImageLoadTrackerListener>
    {
    public:
        XamlBuilder();

        // IImageLoadTrackerListener
        void AllImagesLoaded() override;
        void ImagesLoadingHadError() override;

        static HRESULT BuildXamlTreeFromAdaptiveCard(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* adaptiveCard,
                                                     _COM_Outptr_ ABI::Windows::UI::Xaml::IFrameworkElement** xamlTreeRoot,
                                                     _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                                                     Microsoft::WRL::ComPtr<XamlBuilder> xamlBuilder,
                                                     ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle defaultContainerStyle =
                                                         ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle::Default) noexcept;

        static winrt::Windows::UI::Xaml::FrameworkElement
        BuildXamlTreeFromAdaptiveCard(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveCard const& adaptiveCard,
                                      winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                                      XamlBuilder* xamlBuilder,
                                      winrt::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle defaultContainerStyle =
                                          winrt::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle::Default);

        /* HRESULT AddListener(_In_ ::AdaptiveCards::Rendering::WinUI3::IXamlBuilderListener* listener) noexcept;
         HRESULT RemoveListener(_In_ ::AdaptiveCards::Rendering::WinUI3::IXamlBuilderListener* listener) noexcept;*/
        // TODO: not sure what we need this for? Are they for public? remove them for now
        // TODO: I think these methods are created so people from outside can listen to images loading?
        void AddListener(::AdaptiveCards::Rendering::WinUI3::IXamlBuilderListener* listener);
        void RemoveListener(::AdaptiveCards::Rendering::WinUI3::IXamlBuilderListener* listener);
        void SetFixedDimensions(uint32_t width, uint32_t height) noexcept;
        void SetEnableXamlImageHandling(bool enableXamlImageHandling) noexcept;

        static HRESULT BuildPanelChildren(
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement*>* children,
            _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
            _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* context,
            _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
            std::function<void(ABI::Windows::UI::Xaml::IUIElement* child)> childCreatedCallback) noexcept;

        static void BuildPanelChildren(
            winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement> const& children,
            rtxaml::Controls::Panel ParentPanel,
            rtrender::AdaptiveRenderContext context,
            rtrender::AdaptiveRenderArgs renderArgs,
            std::function<void(rtxaml::UIElement child)> childCreatedCallback);

        winrt::Windows::UI::Xaml::UIElement
        BuildImage(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& adaptiveCardElement,
                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);

    private:
        /* winrt::com_ptr<winrt::AdaptiveCards::Rendering::WinUI3::ImageLoadTracker> m_imageLoadTracker;*/
        winrt::com_ptr<::AdaptiveCards::Rendering::WinUI3::ImageLoadTracker> m_imageLoadTracker;
        // TODO: why do we need this?
        std::set<::AdaptiveCards::Rendering::WinUI3::IXamlBuilderListener*> m_listeners;
        /*winrt::Windows::Storage::Streams::IRandomAccessStreamStatics m_randomAccessStreamStatics{};*/
        winrt::Windows::Storage::Streams::RandomAccessStream m_randomAccessStreamStatics{};
        /* std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<ABI::Windows::Storage::Streams::IInputStream*,
         * ABI::Windows::Web::Http::HttpProgress>>> m_getStreamOperations;*/
        /*  std::vector<winrt::com_ptr<winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Windows::Storage::Streams::IInputStream,
         * winrt::Windows::Web::Http::HttpProgress>>> m_getStreamOperations;*/
        std::vector<winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Windows::Storage::Streams::IInputStream, winrt::Windows::Web::Http::HttpProgress>> m_getStreamOperations;
        std::vector<winrt::Windows::Foundation::IAsyncOperationWithProgress<uint64_t, uint64_t>> m_copyStreamOperations;
        /* std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<UINT32, UINT32>>> m_writeAsyncOperations;*/
        /*std::vector<winrt::com_ptr<winrt::Windows::Foundation::IAsyncOperationWithProgress<uint32_t, uint32_t>>> m_writeAsyncOperations;*/
        std::vector<winrt::Windows::Foundation::IAsyncOperationWithProgress<uint32_t, uint32_t>> m_writeAsyncOperations;
        /*  UINT m_fixedWidth = 0;
          UINT m_fixedHeight = 0;*/
        uint32_t m_fixedWidth = 0;
        uint32_t m_fixedHeight = 0;

        bool m_fixedDimensions = false;
        bool m_enableXamlImageHandling = false;

        /*Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveCardResourceResolvers> m_resourceResolvers;*/
        /*  winrt::com_ptr<winrt::AdaptiveCards::Rendering::WinUI3::implementation::AdaptiveCardResourceResolvers> m_resourceResolvers;*/
        /*winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveCardResourceResolvers m_resourceResolvers;*/

        static HRESULT CreateRootCardElement(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* adaptiveCard,
                                             _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                                             _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                                             Microsoft::WRL::ComPtr<XamlBuilder> xamlBuilder,
                                             _COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IPanel** bodyElementContainer,
                                             _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** rootUIElement) noexcept;

        // TODO: can we move word static to the function name?
        static std::pair<winrt::Windows::UI::Xaml::Controls::Panel, winrt::Windows::UI::Xaml::UIElement>
        CreateRootCardElement(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard const& adaptiveCard,
                              winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                              winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs,
                              XamlBuilder* xamlBuilder);

        template<typename T>
        void SetAutoSize(T* destination, IInspectable* parentElement, IInspectable* imageContainer, bool isVisible, bool imageFiresOpenEvent);
        template<typename T>
        void SetAutoSize(T const& destination,
                         winrt::Windows::Foundation::IInspectable const& parentElement,
                         winrt::Windows::Foundation::IInspectable const&, /* imageContainer */
                         bool isVisible,
                         bool imageFiresOpenEvent);

        template<typename T>
        void SetImageSource(T* destination,
                            ABI::Windows::UI::Xaml::Media::IImageSource* imageSource,
                            ABI::Windows::UI::Xaml::Media::Stretch stretch = Stretch_UniformToFill);

        template<typename T>
        void SetImageSource(T const& destination,
                            winrt::Windows::UI::Xaml::Media::ImageSource const& imageSource,
                            winrt::Windows::UI::Xaml::Media::Stretch stretch = winrt::Windows::UI::Xaml::Media::Stretch::UniformToFill);

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

        // TODO: do we want to return bool to indicate success/failure?
        template<typename T>
        void SetImageOnUIElement(winrt::Windows::Foundation::Uri const& imageUrl,
                                 T const& uiElement,
                                 winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveCardResourceResolvers const& resolvers,
                                 bool isAutoSize,
                                 winrt::Windows::Foundation::IInspectable const& parentElement,
                                 winrt::Windows::Foundation::IInspectable const& imageContainer,
                                 bool isVisible,
                                 winrt::Windows::UI::Xaml::Media::Stretch stretch = winrt::Windows::UI::Xaml::Media::Stretch::UniformToFill);

        template<typename T>
        void PopulateImageFromUrlAsync(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl, _In_ T* imageControl);

        template<typename T>
        void PopulateImageFromUrlAsync(winrt::Windows::Foundation::Uri const& imageUrl, T const& imageControl);

        void FireAllImagesLoaded();
        void FireImagesLoadingHadError();
    };
}
