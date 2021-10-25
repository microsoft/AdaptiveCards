// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "TileControl.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct DECLSPEC_UUID("0F485063-EF2A-400E-A946-73E00EDFAC83") TileControl : public TileControlT<TileControl, ITypePeek>
    {

        TileControl();
    public:
        //HRESULT RuntimeClassInitialize() noexcept;

        void BackgroundImage(rtom::AdaptiveBackgroundImage const& adaptiveBackgroundImage) { m_adaptiveBackgroundImage = adaptiveBackgroundImage; }
        void RootElement(rtxaml::FrameworkElement const& rootElement) { m_rootElement = rootElement; }
        rtxaml::UIElement ResolvedImage() { return m_resolvedImage; }
        void ImageSize(winrt::Windows::Foundation::Size const& imageSize) { m_imageSize = imageSize; }

        void LoadImageBrush(rtxaml::UIElement const& image);

        // IFrameworkElementOverrides overrides
        void OnApplyTemplate();

        winrt::Windows::Foundation::Size MeasureOverride(winrt::Windows::Foundation::Size const& availableSize);
        winrt::Windows::Foundation::Size ArrangeOverride(winrt::Windows::Foundation::Size const& arrangeBounds);

        // not implemented
        //void get_BackgroundImage(_Outptr_ IAdaptiveBackgroundImage** /*value*/)
        //{
        //    return E_NOTIMPL;
        //}
        //void get_RootElement(_Outptr_ IFrameworkElement** /*value*/) { return E_NOTIMPL; }
        //void put_ResolvedImage(rtxaml::UIElement const& /*value*/) { return E_NOTIMPL; }
        //void get_ImageSize(_Out_ ABI::Windows::Foundation::Size* /*value*/)
        //{
        //    return E_NOTIMPL;
        //}

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        void RefreshContainerTile();
        void ExtractBackgroundImageData(rtom::BackgroundImageFillMode& fillMode,
                                           rtom::HAlignment& hAlignment,
                                           rtom::VAlignment& vAlignment);

        void ImageOpened(const IInspectable& sender, const rtxaml::RoutedEventArgs& args);

        // Fields
        rtxaml::FrameworkElement m_rootElement;
        rtxaml::UIElement m_resolvedImage;
        rtxaml::Controls::Canvas m_containerElement;
        rtxaml::Media::ImageBrush m_brushXaml;

        rtom::AdaptiveBackgroundImage m_adaptiveBackgroundImage;
        winrt::Windows::Foundation::Size m_imageSize{};
        winrt::Windows::Foundation::Size m_containerSize{};
        std::vector<rtxaml::Shapes::IRectangle> m_xamlChildren;

        // Revokers
        rtxaml::Media::Imaging::BitmapImage::ImageOpened_revoker m_imageOpenedRevoker;
    };
}

namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct TileControl : TileControlT<TileControl, implementation::TileControl>
    {
    };
}
