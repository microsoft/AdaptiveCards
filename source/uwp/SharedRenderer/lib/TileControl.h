// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "TileControl.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct DECLSPEC_UUID("0F485063-EF2A-400E-A946-73E00EDFAC83") TileControl : public TileControlT<TileControl, ITypePeek>
    {
        TileControl();

    public:
        void BackgroundImage(winrt::AdaptiveBackgroundImage const& adaptiveBackgroundImage)
        {
            m_adaptiveBackgroundImage = adaptiveBackgroundImage;
        }
        winrt::AdaptiveBackgroundImage BackgroundImage() { return m_adaptiveBackgroundImage; }

        winrt::UIElement ResolvedImage() { return m_resolvedImage; }
        void ImageSize(winrt::Size const& imageSize) { m_imageSize = imageSize; }
        winrt::Size ImageSize() { return m_imageSize; }

        void LoadImageBrush(winrt::UIElement const& image);

        void OnApplyTemplate();
        winrt::Size MeasureOverride(winrt::Size const& availableSize);
        winrt::Size ArrangeOverride(winrt::Size const& arrangeBounds);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        void RefreshContainerTile();
        void ImageOpened(const IInspectable& sender, const winrt::RoutedEventArgs& args);
        void SvgImageOpened(const IInspectable& sender, const winrt::SvgImageSourceOpenedEventArgs& args);

        // Fields
        /* winrt::FrameworkElement m_rootElement;*/
        winrt::UIElement m_resolvedImage{nullptr};
        winrt::Canvas m_containerElement;
        winrt::ImageBrush m_brushXaml;

        winrt::AdaptiveBackgroundImage m_adaptiveBackgroundImage;
        winrt::Size m_imageSize{};
        winrt::Size m_containerSize{};
        std::vector<winrt::Rectangle> m_xamlChildren;

        // Revokers
        winrt::BitmapImage::ImageOpened_revoker m_imageOpenedRevoker;
        winrt::SvgImageSource::Opened_revoker m_svgImageOpenedRevoker;
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct TileControl : TileControlT<TileControl, implementation::TileControl>
    {
    };
}
