// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "TileControl.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct DECLSPEC_UUID("0F485063-EF2A-400E-A946-73E00EDFAC83") TileControl : public TileControlT<TileControl, ITypePeek>
    {
        TileControl();

    public:
        // TODO: convert to property?
        void BackgroundImage(rtom::AdaptiveBackgroundImage const& adaptiveBackgroundImage)
        {
            m_adaptiveBackgroundImage = adaptiveBackgroundImage;
        }
        rtom::AdaptiveBackgroundImage BackgroundImage() { return m_adaptiveBackgroundImage; }

        // TODO: couldn't see rootElement being used anywhere?
        /*  void RootElement(rtxaml::FrameworkElement const& rootElement) { m_rootElement = rootElement; }
                  rtxaml::FrameworkElement RootElement() { return m_rootElement;}*/

        rtxaml::UIElement ResolvedImage() { return m_resolvedImage; }
        // TODO: convert to property?
        void ImageSize(winrt::Windows::Foundation::Size const& imageSize) { m_imageSize = imageSize; }
        winrt::Windows::Foundation::Size ImageSize() { return m_imageSize; }

        void LoadImageBrush(rtxaml::UIElement const& image);

        void OnApplyTemplate();
        winrt::Windows::Foundation::Size MeasureOverride(winrt::Windows::Foundation::Size const& availableSize);
        winrt::Windows::Foundation::Size ArrangeOverride(winrt::Windows::Foundation::Size const& arrangeBounds);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        void RefreshContainerTile();
        void ImageOpened(const IInspectable& sender, const rtxaml::RoutedEventArgs& args);

        // Fields
        /* rtxaml::FrameworkElement m_rootElement;*/
        rtxaml::UIElement m_resolvedImage{nullptr};
        rtxaml::Controls::Canvas m_containerElement;
        rtxaml::Media::ImageBrush m_brushXaml;

        rtom::AdaptiveBackgroundImage m_adaptiveBackgroundImage;
        winrt::Windows::Foundation::Size m_imageSize{};
        winrt::Windows::Foundation::Size m_containerSize{};
        std::vector<rtxaml::Shapes::Rectangle> m_xamlChildren;

        // Revokers
        rtxaml::Media::Imaging::BitmapImage::ImageOpened_revoker m_imageOpenedRevoker;
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct TileControl : TileControlT<TileControl, implementation::TileControl>
    {
    };
}
