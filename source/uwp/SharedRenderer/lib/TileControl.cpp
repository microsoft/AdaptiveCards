// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "TileControl.h"
#include "TileControl.g.cpp"
#include <cmath>

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    TileControl::TileControl()
    {
        m_containerElement = winrt::Canvas{};
        m_brushXaml = winrt::ImageBrush{};
        this->Content(m_containerElement);
    }

    void TileControl::ImageOpened(const IInspectable& /* sender */, const winrt::RoutedEventArgs& /* args */)
    {
        auto uiElement = m_resolvedImage;

        // Do we need to throw/log if we fail here?
        if (const auto image = m_resolvedImage.try_as<winrt::Image>())
        {
            if (const auto imageSource = image.Source())
            {
                if (const auto bitmapSource = imageSource.try_as<winrt::BitmapSource>())
                {
                    m_imageSize = {(float)bitmapSource.PixelWidth(), (float)bitmapSource.PixelHeight()};
                    RefreshContainerTile();
                }
            }
        }
    }

    void TileControl::SvgImageOpened(const IInspectable& /* sender */, const winrt::SvgImageSourceOpenedEventArgs& /* args */)
    {
        auto uiElement = m_resolvedImage;

        // Do we need to throw/log if we fail here?
        if (const auto image = m_resolvedImage.try_as<winrt::Image>())
        {
            if (const auto imageSource = image.Source())
            {
                if (const auto svgImageSource = imageSource.try_as<winrt::SvgImageSource>())
                {
                    m_imageSize = {(float)svgImageSource.RasterizePixelWidth(), (float)svgImageSource.RasterizePixelHeight()};
                    RefreshContainerTile();
                }
            }
        }
    }

    void TileControl::LoadImageBrush(winrt::UIElement const& uielement)
    {
        m_resolvedImage = uielement;

        if (const auto image = m_resolvedImage.try_as<winrt::Image>())
        {
            if (const auto imageSource = image.Source())
            {
                if (const auto bitmapImage = imageSource.try_as<winrt::BitmapImage>())
                {
                    m_imageOpenedRevoker.revoke();
                    m_imageOpenedRevoker = bitmapImage.ImageOpened(winrt::auto_revoke, {this, &TileControl::ImageOpened});
                    m_brushXaml.ImageSource(imageSource);
                }
                else if (const auto svgImageSource = imageSource.try_as<winrt::SvgImageSource>())
                {
                    m_svgImageOpenedRevoker.revoke();
                    m_svgImageOpenedRevoker = svgImageSource.Opened(winrt::auto_revoke, {this, &TileControl::SvgImageOpened});
                    m_brushXaml.ImageSource(imageSource);
                }
            }
        }
    }

    void TileControl::OnApplyTemplate()
    {
        TileControl_base::OnApplyTemplate();
    }

    winrt::Size TileControl::MeasureOverride(winrt::Size const& availableSize)
    {
        return TileControl_base::MeasureOverride(availableSize);
    }

    winrt::Size TileControl::ArrangeOverride(winrt::Size const& arrangeBounds)
    {
        m_containerSize = TileControl_base::ArrangeOverride(arrangeBounds);

        // Define clip properties for m_containerElement
        winrt::Rect rect{0, 0, m_containerSize.Width, m_containerSize.Height};

        winrt::RectangleGeometry clip;
        clip.Rect(rect);
        if (const auto containerAsUIElement = m_containerElement.try_as<winrt::UIElement>())
        {
            containerAsUIElement.Clip(clip);
        }
        RefreshContainerTile();
        return m_containerSize;
    }

    void TileControl::RefreshContainerTile()
    {
        winrt::BackgroundImageFillMode fillMode = m_adaptiveBackgroundImage.FillMode();
        winrt::HAlignment hAlignment = m_adaptiveBackgroundImage.HorizontalAlignment();
        winrt::VAlignment vAlignment = m_adaptiveBackgroundImage.VerticalAlignment();

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
            case winrt::BackgroundImageFillMode::RepeatHorizontally:
                numberImagePerRow = static_cast<int>(ceil(m_containerSize.Width / m_imageSize.Width));
                numberImagePerColumn = 1;

                switch (vAlignment)
                {
                case winrt::VAlignment::Bottom:
                    offsetVerticalAlignment = m_containerSize.Height - m_imageSize.Height;
                    break;
                case winrt::VAlignment::Center:
                    offsetVerticalAlignment = static_cast<float>((m_containerSize.Height - m_imageSize.Height) / 2.0f);
                    break;
                case winrt::VAlignment::Top:
                default:
                    break;
                }
                break;

            case winrt::BackgroundImageFillMode::RepeatVertically:
                numberImagePerRow = 1;
                numberImagePerColumn = static_cast<int>(ceil(m_containerSize.Height / m_imageSize.Height));

                switch (hAlignment)
                {
                case winrt::HAlignment::Right:
                    offsetHorizontalAlignment = m_containerSize.Width - m_imageSize.Width;
                    break;
                case winrt::HAlignment::Center:
                    offsetHorizontalAlignment = static_cast<float>((m_containerSize.Width - m_imageSize.Width) / 2.0f);
                    break;
                case winrt::HAlignment::Left:
                default:
                    break;
                }
                break;

            case winrt::BackgroundImageFillMode::Repeat:
                numberImagePerColumn = static_cast<int>(ceil(m_containerSize.Height / m_imageSize.Height));
                numberImagePerRow = static_cast<int>(ceil(m_containerSize.Width / m_imageSize.Width));
                break;

            case winrt::BackgroundImageFillMode::Cover:
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

        winrt::IVector<winrt::UIElement> children{};
        // Not sure what is the need to convert to xaml::controls::Panel?
        if (const auto containerElementAsPanel = m_containerElement.try_as<winrt::Panel>())
        {
            children = containerElementAsPanel.Children();
        }

        if (numberSpriteToInstanciate > count)
        {
            // instanciate all elements not created yet
            for (int x = 0; x < (numberSpriteToInstanciate - count); x++)
            {
                winrt::Rectangle rectangle;

                children.Append(rectangle.as<winrt::UIElement>());

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
                if (fillMode != winrt::BackgroundImageFillMode::Cover)
                {
                    originPositionX = (x * m_imageSize.Width) + offsetHorizontalAlignment;
                    originPositionY = (y * m_imageSize.Height) + offsetVerticalAlignment;
                }

                // Set Left and Top for rectangle
                winrt::Canvas::SetLeft(rectangle, originPositionX);
                winrt::Canvas::SetTop(rectangle, originPositionY);

                double imageWidth{0.0}, imageHeight{0.0};
                if (fillMode == winrt::BackgroundImageFillMode::Cover)
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

                if (fillMode == winrt::BackgroundImageFillMode::Cover)
                {
                    m_brushXaml.Stretch(winrt::Stretch::UniformToFill);

                    // Vertical and Horizontal Alignments map to the same values in our shared model and UWP, so we just cast
                    m_brushXaml.AlignmentX(static_cast<winrt::AlignmentX>(hAlignment));
                    m_brushXaml.AlignmentY(static_cast<winrt::AlignmentY>(vAlignment));
                }
            }
        }
    }
}
