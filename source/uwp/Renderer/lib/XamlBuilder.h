// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ImageLoadTracker.h"
#include "IXamlBuilderListener.h"
#include "IImageLoadTrackerListener.h"

namespace AdaptiveCards::Rendering::Uwp
{
    struct XamlBuilder : winrt::implements<XamlBuilder, winrt::IInspectable, IImageLoadTrackerListener>
    {
    public:
        XamlBuilder();

        // IImageLoadTrackerListener
        void AllImagesLoaded() override;
        void ImagesLoadingHadError() override;

        static winrt::FrameworkElement BuildXamlTreeFromAdaptiveCard(winrt::AdaptiveCard const& adaptiveCard,
                                                                     winrt::AdaptiveRenderContext const& renderContext,
                                                                     XamlBuilder* xamlBuilder,
                                                                     winrt::ContainerStyle defaultContainerStyle = winrt::ContainerStyle::Default);

        void AddListener(IXamlBuilderListener* listener);
        void RemoveListener(IXamlBuilderListener* listener);
        void SetFixedDimensions(uint32_t width, uint32_t height) noexcept;
        void SetEnableXamlImageHandling(bool enableXamlImageHandling) noexcept;

        static void BuildPanelChildren(winrt::IVector<winrt::IAdaptiveCardElement> const& children,
                                       winrt::Panel ParentPanel,
                                       winrt::AdaptiveRenderContext context,
                                       winrt::AdaptiveRenderArgs renderArgs,
                                       std::function<void(winrt::UIElement const& child)> childCreatedCallback);

        winrt::UIElement BuildImage(winrt::IAdaptiveCardElement const& adaptiveCardElement,
                                    winrt::AdaptiveRenderContext const& renderContext,
                                    winrt::AdaptiveRenderArgs const& renderArgs);

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

        static std::pair<winrt::Panel, winrt::UIElement> CreateRootCardElement(winrt::IAdaptiveCard const& adaptiveCard,
                                                                               winrt::AdaptiveRenderContext const& renderContext,
                                                                               winrt::AdaptiveRenderArgs const& renderArgs,
                                                                               XamlBuilder* xamlBuilder);

        template<typename T>
        void SetAutoSize(T const& destination,
                         winrt::IInspectable const& parentElement,
                         winrt::IInspectable const& imageContainer,
                         bool isVisible,
                         bool imageFiresOpenEvent);

        template<typename T>
        void SetImageSource(T const& destination, winrt::ImageSource const& imageSource, winrt::Stretch stretch = winrt::Stretch::UniformToFill);

        template<typename T>
        winrt::ImageSource SetImageOnUIElement(winrt::Uri const& imageUrl,
                                               T const& uiElement,
                                               winrt::AdaptiveCardResourceResolvers const& resolvers,
                                               bool isAutoSize,
                                               winrt::IInspectable const& parentElement,
                                               winrt::IInspectable const& imageContainer,
                                               bool isVisible,
                                               bool isImageSvg = false,
                                               winrt::Stretch stretch = winrt::Stretch::UniformToFill);

        winrt::ImageSource CreateImageSource(bool isImageSvg);

        template<typename T>
        winrt::ImageSource PopulateImageFromUrlAsync(winrt::Uri const& imageUrl,
                                                     T const& uiElement,
                                                     bool isAutoSize,
                                                     winrt::IInspectable const& parentElement,
                                                     winrt::IInspectable const& imageContainer,
                                                     bool isVisible,
                                                     bool isImageSvg,
                                                     winrt::Stretch stretch);

        template<typename T, typename S>
        void HandleAccessStreamForImageSource(T const& uiElement,
                                              bool isAutoSize,
                                              winrt::IInspectable const& parentElement,
                                              winrt::IInspectable const& imageContainer,
                                              bool isVisible,
                                              bool isImageSvg,
                                              S const& stream,
                                              winrt::ImageSource const& imageSource,
                                              winrt::Stretch stretch);

        winrt::IAsyncAction SetSvgUriSource(winrt::SvgImageSource const imageSourceRef,
                                            winrt::Uri const uriRef);

        template<typename T, typename S>
        winrt::IAsyncAction SetSvgImageSourceAsync(winrt::SvgImageSource const imageSourceRef,
                                                   S const streamRef,
                                                   T const uiElementRef,
                                                   bool isAutoSize,
                                                   winrt::IInspectable const parentElementRef,
                                                   winrt::IInspectable const imageContainerRef,
                                                   bool isVisible);

        boolean IsSvgImage(std::string url);

        void FireAllImagesLoaded();
        void FireImagesLoadingHadError();

        void ParseXmlForHeightAndWidth(winrt::XmlDocument const& xmlDoc,
                                       winrt::SvgImageSource const& imageSourceRef);
        
        winrt::IAsyncAction SetRasterizedPixelHeight(winrt::SvgImageSource const imageSourceRef,
                                                     double imageSize,
                                                     bool dropIfUnset = false);
        winrt::IAsyncAction SetRasterizedPixelWidth(winrt::SvgImageSource const imageSourceRef,
                                                    double imageSize,
                                                    bool dropIfUnset = false);

        void SetRasterizedPixelHeight(winrt::ImageSource const& imageSource, double imageSize);
        void SetRasterizedPixelWidth(winrt::ImageSource const& imageSource, double imageSize);
    };
}
