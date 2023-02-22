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

        template<typename TElement>
        struct ImageProperties
        {
            TElement uiElement;
            bool isAutoSize;
            winrt::IInspectable parentElement;
            winrt::IInspectable imageContainer;
            bool isVisible;
            boolean isImageSvg;
            winrt::Stretch stretch = winrt::Stretch::UniformToFill;
        };

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

        template<typename TDest>
        void SetAutoSize(TDest const& destination,
                         winrt::IInspectable const& parentElement,
                         winrt::IInspectable const& imageContainer,
                         bool isVisible,
                         bool imageFiresOpenEvent);

        template<typename TDest>
        void SetImageSource(TDest const& destination, winrt::ImageSource const& imageSource, winrt::Stretch stretch = winrt::Stretch::UniformToFill);

        template<typename TElement>
        winrt::ImageSource SetImageOnUIElement(winrt::Uri const& imageUrl,
                                               winrt::AdaptiveCardResourceResolvers const& resolvers,
                                               ImageProperties<TElement> const& imgProperties);

        winrt::ImageSource CreateImageSource(bool isImageSvg);

        template<typename TElement>
        winrt::ImageSource PopulateImageFromUrlAsync(winrt::Uri const& imageUrl,
                                                     ImageProperties<TElement> const& imgProperties);

        template<typename TElement, typename TStream>
        void HandleAccessStreamForImageSource(ImageProperties<TElement> const& imgProperties,
                                              TStream const& stream,
                                              winrt::ImageSource const& imageSource);

        winrt::fire_and_forget SetSvgUriSource(winrt::SvgImageSource const imageSourceRef,
                                            winrt::Uri const uriRef);

        template<typename TElement, typename TStream>
        winrt::IAsyncAction SetSvgImageSourceAsync(winrt::SvgImageSource const imageSourceRef,
                                                   TStream const streamRef,
                                                   ImageProperties<TElement> const imgProperties);

        boolean IsSvgImage(std::string url);

        void FireAllImagesLoaded();
        void FireImagesLoadingHadError();

        bool ParseXmlForHeightAndWidth(winrt::XmlDocument const& xmlDoc,
                                       winrt::SvgImageSource const& imageSourceRef);
        
        winrt::fire_and_forget SetRasterizedPixelHeightAsync(winrt::SvgImageSource const imageSourceRef,
                                                     double const imageSize,
                                                     bool const dropIfUnset = false);
        winrt::fire_and_forget SetRasterizedPixelWidthAsync(winrt::SvgImageSource const imageSourceRef,
                                                    double const imageSize,
                                                    bool const dropIfUnset = false);

        void SetRasterizedPixelHeight(winrt::ImageSource const& imageSource, double const& imageSize);
        void SetRasterizedPixelWidth(winrt::ImageSource const& imageSource, double const& imageSize);
    };
}
