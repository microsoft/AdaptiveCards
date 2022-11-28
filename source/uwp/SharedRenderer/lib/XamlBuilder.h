// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ImageLoadTracker.h"
#include "IXamlBuilderListener.h"
#include "IImageLoadTrackerListener.h"

namespace AdaptiveCards::Rendering::Xaml_Rendering
{
    struct XamlBuilder : winrt::implements<XamlBuilder, winrt::IInspectable, IImageLoadTrackerListener>
    {
    public:
        XamlBuilder();

        // IImageLoadTrackerListener
        void AllImagesLoaded() override;
        void ImagesLoadingHadError() override;

        static winrt::xaml::FrameworkElement
        BuildXamlTreeFromAdaptiveCard(winrt::AdaptiveCard const& adaptiveCard,
                                      winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                      XamlBuilder* xamlBuilder,
                                      winrt::ContainerStyle defaultContainerStyle = winrt::ContainerStyle::Default);

        void AddListener(IXamlBuilderListener* listener);
        void RemoveListener(IXamlBuilderListener* listener);
        void SetFixedDimensions(uint32_t width, uint32_t height) noexcept;
        void SetEnableXamlImageHandling(bool enableXamlImageHandling) noexcept;

        static void BuildPanelChildren(winrt::IVector<winrt::IAdaptiveCardElement> const& children,
                                       winrt::xaml_controls::Panel ParentPanel,
            winrt::render_xaml::AdaptiveRenderContext context,
            winrt::render_xaml::AdaptiveRenderArgs renderArgs,
                                       std::function<void(winrt::xaml::UIElement const& child)> childCreatedCallback);

        winrt::xaml::UIElement BuildImage(winrt::IAdaptiveCardElement const& adaptiveCardElement,
        winrt::render_xaml::AdaptiveRenderContext const& renderContext,
        winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);

    private:
        winrt::com_ptr<ImageLoadTracker> m_imageLoadTracker;
        std::set<IXamlBuilderListener*> m_listeners;
        std::vector<winrt::IAsyncOperationWithProgress<winrt::IInputStream, winrt::HttpProgress>> m_getStreamOperations;
        std::vector<winrt::IAsyncOperationWithProgress<uint64_t, uint64_t>> m_copyStreamOperations;
        std::vector<winrt::IAsyncOperation<uint32_t>> m_writeAsyncOperations;
        uint32_t m_fixedWidth = 0;
        uint32_t m_fixedHeight = 0;

        bool m_fixedDimensions = false;
        bool m_enableXamlImageHandling = false;

        static std::pair<winrt::xaml_controls::Panel, winrt::xaml::UIElement>
        CreateRootCardElement(winrt::IAdaptiveCard const& adaptiveCard,
                              winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                              winrt::render_xaml::AdaptiveRenderArgs const& renderArgs,
                              XamlBuilder* xamlBuilder);

        template<typename T>
        void SetAutoSize(T const& destination,
                         winrt::IInspectable const& parentElement,
                         winrt::IInspectable const& imageContainer,
                         bool isVisible,
                         bool imageFiresOpenEvent);

        template<typename T>
        void SetImageSource(T const& destination,
                            winrt::xaml_media::ImageSource const& imageSource,
                            winrt::xaml_media::Stretch stretch = winrt::xaml_media::Stretch::UniformToFill);

        template<typename T>
        void SetImageOnUIElement(winrt::Uri const& imageUrl,
                                 T const& uiElement,
                                 winrt::render_xaml::AdaptiveCardResourceResolvers const& resolvers,
                                 bool isAutoSize,
                                 winrt::IInspectable const& parentElement,
                                 winrt::IInspectable const& imageContainer,
                                 bool isVisible,
                                 bool isImageSvg = false,
                                 winrt::xaml_media::Stretch stretch = winrt::xaml_media::Stretch::UniformToFill);

        winrt::xaml_media::ImageSource CreateImageSource(bool isImageSvg);

        template<typename T> void PopulateImageFromUrlAsync(winrt::Uri const& imageUrl, T const& imageControl, bool const& isImageSvg);

        boolean IsSvgImage(std::string url);

        void FireAllImagesLoaded();
        void FireImagesLoadingHadError();
    };
}
