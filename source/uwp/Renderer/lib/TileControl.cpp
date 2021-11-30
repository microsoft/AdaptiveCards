// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "TileControl.h"
#include "TileControl.g.cpp"
#include "XamlHelpers.h"
#include <cmath>

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    TileControl::TileControl()
    {
        m_containerElement = rtxaml::Controls::Canvas{};
        m_brushXaml = rtxaml::Media::ImageBrush{};
    }

    void TileControl::ImageOpened(const IInspectable& sender, const rtxaml::RoutedEventArgs& args)
    {
        auto uiElement = m_resolvedImage;

        // Do we need to throw/log if we fail here?
        if (const auto image = m_resolvedImage.try_as<rtxaml::Controls::Image>())
        {
            if (const auto imageSource = image.Source())
            {
                if (const auto bitmapSource = imageSource.try_as<rtxaml::Media::Imaging::BitmapSource>())
                {
                    m_imageSize = {(float)bitmapSource.PixelWidth(), (float)bitmapSource.PixelHeight()};
                    RefreshContainerTile();
                }
            }
        }
    }
    void TileControl::LoadImageBrush(rtxaml::UIElement const& uielement)
    {
        m_resolvedImage = uielement;

        if (const auto image = m_resolvedImage.try_as<rtxaml::Controls::Image>())
        {
            if (const auto imageSource = image.Source())
            {
                if (const auto bitmapImage = imageSource.try_as<rtxaml::Media::Imaging::BitmapImage>())
                {
                    m_imageOpenedRevoker.revoke();
                    m_imageOpenedRevoker = bitmapImage.ImageOpened(winrt::auto_revoke, {this, &TileControl::ImageOpened});
                    m_brushXaml.ImageSource(imageSource);
                }
            }
        }
    }

    void TileControl::OnApplyTemplate() { this->Content(m_containerElement); }

    winrt::Windows::Foundation::Size TileControl::MeasureOverride(winrt::Windows::Foundation::Size const& availableSize)
    {
        /*ComPtr<IFrameworkElementOverrides> base;
        RETURN_IF_FAILED(GetComposableBase()->QueryInterface(__uuidof(IFrameworkElementOverrides),
                                                             reinterpret_cast<void**>(base.GetAddressOf())));

        return base->MeasureOverride(availableSize, pReturnValue);*/
        // TODO: I don't think I need to do it at all, do I?
        return TileControl_base::MeasureOverride(availableSize);
    }

    winrt::Windows::Foundation::Size TileControl::ArrangeOverride(winrt::Windows::Foundation::Size const& arrangeBounds)
    {
        // TODO: am I doing this right?
        m_containerSize = TileControl_base::MeasureOverride(arrangeBounds);

        // Define clip properties for m_containerElement
        winrt::Windows::Foundation::Rect rect{0, 0, m_containerSize.Width, m_containerSize.Height};

        rtxaml::Media::RectangleGeometry clip;
        clip.Rect(rect);
        if (const auto containerAsUIElement = m_containerElement.try_as<rtxaml::UIElement>())
        {
            containerAsUIElement.Clip(clip);
        }
        RefreshContainerTile();
        // TODO: is this correct?
        return m_containerSize;
    }

    void TileControl::RefreshContainerTile()
    {
        rtom::BackgroundImageFillMode fillMode = m_adaptiveBackgroundImage.FillMode();
        rtom::HAlignment hAlignment = m_adaptiveBackgroundImage.HorizontalAlignment();
        rtom::VAlignment vAlignment = m_adaptiveBackgroundImage.VerticalAlignment();

        int numberSpriteToInstanciate{1};
        int numberImagePerColumn{1};
        int numberImagePerRow{1};

        float offsetVerticalAlignment{};
        float offsetHorizontalAlignment{};

        // If we don't have dimensions yet, just make the image the size of
        // the container until we get the right dimensions.
        if (m_imageSize.Width && m_imageSize.Height)
        {
            switch (fillMode)
            {
            case rtom::BackgroundImageFillMode::RepeatHorizontally:
                numberImagePerRow = static_cast<int>(ceil(m_containerSize.Width / m_imageSize.Width));
                numberImagePerColumn = 1;

                switch (vAlignment)
                {
                case rtom::VAlignment::Bottom:
                    offsetVerticalAlignment = m_containerSize.Height - m_imageSize.Height;
                    break;
                case rtom::VAlignment::Center:
                    offsetVerticalAlignment = static_cast<float>((m_containerSize.Height - m_imageSize.Height) / 2.0f);
                    break;
                case rtom::VAlignment::Top:
                default:
                    break;
                }
                break;

            case rtom::BackgroundImageFillMode::RepeatVertically:
                numberImagePerRow = 1;
                numberImagePerColumn = static_cast<int>(ceil(m_containerSize.Height / m_imageSize.Height));

                switch (hAlignment)
                {
                case rtom::HAlignment::Right:
                    offsetHorizontalAlignment = m_containerSize.Width - m_imageSize.Width;
                    break;
                case rtom::HAlignment::Center:
                    offsetHorizontalAlignment = static_cast<float>((m_containerSize.Width - m_imageSize.Width) / 2.0f);
                    break;
                case rtom::HAlignment::Left:
                default:
                    break;
                }
                break;

            case rtom::BackgroundImageFillMode::Repeat:
                numberImagePerColumn = static_cast<int>(ceil(m_containerSize.Height / m_imageSize.Height));
                numberImagePerRow = static_cast<int>(ceil(m_containerSize.Width / m_imageSize.Width));
                break;

            case rtom::BackgroundImageFillMode::Cover:
            default:
                numberImagePerColumn = 1;
                numberImagePerRow = 1;
                offsetHorizontalAlignment = 0;
                offsetVerticalAlignment = 0;
            }
        }
        numberSpriteToInstanciate = numberImagePerColumn * numberImagePerRow;

        int count = static_cast<int>(m_xamlChildren.size());

        // Get containerElement.Children

        winrt::Windows::Foundation::Collections::IVector<rtxaml::UIElement> children{};
        // Not sure what is the need to convert to xaml::controls::Panel?
        if (const auto containerElementAsPanel = m_containerElement.try_as<rtxaml::Controls::Panel>())
        {
            children = containerElementAsPanel.Children();
        }

        if (numberSpriteToInstanciate > count)
        {
            // instanciate all elements not created yet
            for (int x = 0; x < (numberSpriteToInstanciate - count); x++)
            {
                rtxaml::Shapes::Rectangle rectangle;

                children.Append(rectangle.as<rtxaml::UIElement>());

                m_xamlChildren.push_back(rectangle);
            }
        }
        else
        {
            // remove elements not used now
            for (int x = 0; x < (count - numberSpriteToInstanciate); x++)
            {
                children.RemoveAtEnd();
                m_xamlChildren.pop_back();
            }
        }

        // TODO: do we need this cast?
        // m_brushXaml to rtxaml::Media::Brush?
        // Change positions+brush for all actives elements
        for (int x = 0, index = 0; x < numberImagePerRow; x++)
        {
            for (int y = 0; y < numberImagePerColumn; y++, index++)
            {
                // Get Rectangle
                auto rectangle = m_xamlChildren[index];

                // For cover, the bitmapimage must be scaled to fill the container and then clipped to only the
                // necessary section Set rectangle.
                rectangle.Fill(m_brushXaml);

                double originPositionX{0.0}, originPositionY{0.0};
                if (fillMode != rtom::BackgroundImageFillMode::Cover)
                {
                    originPositionX = (x * m_imageSize.Width) + offsetHorizontalAlignment;
                    originPositionY = (y * m_imageSize.Height) + offsetVerticalAlignment;
                }

                // Set Left and Top for rectangle
                rtxaml::Controls::Canvas::SetLeft(rectangle, originPositionX);
                rtxaml::Controls::Canvas::SetTop(rectangle, originPositionY);

                double imageWidth{0.0}, imageHeight{0.0};
                if (fillMode == rtom::BackgroundImageFillMode::Cover)
                {
                    imageWidth = m_containerSize.Width;
                    imageHeight = m_containerSize.Height;
                }
                else
                {
                    imageWidth = m_imageSize.Width;
                    imageHeight = m_imageSize.Height;
                }

                // Set Width and Height for Rectangle
                rectangle.Width(imageWidth);
                rectangle.Height(imageHeight);

                if (fillMode == rtom::BackgroundImageFillMode::Cover)
                {
                    // TODO: do we ened to convert it to tile brush? not really, right?
                    m_brushXaml.Stretch(rtxaml::Media::Stretch::UniformToFill);

                    // Vertical and Horizontal Alignments map to the same values in our shared model and UWP, so we just cast
                    m_brushXaml.AlignmentX(static_cast<rtxaml::Media::AlignmentX>(hAlignment));
                    m_brushXaml.AlignmentY(static_cast<rtxaml::Media::AlignmentY>(vAlignment));
                }
            }
        }
    }
}
