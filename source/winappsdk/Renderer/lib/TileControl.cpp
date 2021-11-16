// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include <cmath>
#include "TileControl.h"
#include "XamlHelpers.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
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

    void TileControl::OnApplyTemplate()
    {
        this->Content(m_containerElement);
    }

    winrt::Windows::Foundation::Size TileControl::MeasureOverride(winrt::Windows::Foundation::Size const& availableSize){
        /*ComPtr<IFrameworkElementOverrides> base;
        RETURN_IF_FAILED(GetComposableBase()->QueryInterface(__uuidof(IFrameworkElementOverrides),
                                                             reinterpret_cast<void**>(base.GetAddressOf())));

        return base->MeasureOverride(availableSize, pReturnValue);*/
        return TileControl_base::MeasureOverride(availableSize);
    }

    winrt::Windows::Foundation::Size TileControl::ArrangeOverride(winrt::Windows::Foundation::Size const& arrangeBounds)
    {
        m_containerSize = TileControl_base::MeasureOverride(arrangeBounds);

        // Define clip properties for m_containerElement
        winrt::Windows::Foundation::Rect rect{0, 0, m_containerSize.Width, m_containerSize.Height};

        rtxaml::Media::RectangleGeometry clip;
        clip.Rect(rect);
       /* m_containerElement.Clip();
        m_containerElement.as<rtxaml::UIElement>().Clip()
        ComPtr<IUIElement> containerAsUIElement;
        RETURN_IF_FAILED(m_containerElement.As(&containerAsUIElement));
        RETURN_IF_FAILED(containerAsUIElement->put_Clip(clip.Get()));*/
        if (const auto containerAsUIElement = m_containerElement.try_as<rtxaml::UIElement>())
        {
            containerAsUIElement.Clip(clip);
        }
        RefreshContainerTile();
    }

    void TileControl::RefreshContainerTile()
    {
        rtom::BackgroundImageFillMode fillMode{};
        rtom::HAlignment hAlignment{};
        rtom::VAlignment vAlignment{};
        ExtractBackgroundImageData(fillMode, hAlignment, vAlignment);

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
                case rtom::VAlignment::Bottom :
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
            for (int x{}; x < (numberSpriteToInstanciate - count); x++)
            {
                /*ComPtr<IRectangle> rectangle = AdaptiveCards::Rendering::WinUI3::XamlHelpers::CreateABIClass<IRectangle>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Rectangle));

                ComPtr<IUIElement> rectangleAsUIElement;
                THROW_IF_FAILED(rectangle.As(&rectangleAsUIElement));
                THROW_IF_FAILED(children->Append(rectangleAsUIElement.Get()));*/
                rtxaml::Shapes::Rectangle rectangle;

                children.Append(rectangle.as<rtxaml::UIElement>());

                m_xamlChildren.push_back(rectangle);
            }
        }
        else
        {
            // remove elements not used now
            for (int x{}; x < (count - numberSpriteToInstanciate); ++x)
            {
                children.RemoveAtEnd();
                m_xamlChildren.pop_back();
            }
        }

        // Convert ImageBrush to Brush
        /*ComPtr<IBrush> brushXamlAsBrush;
        THROW_IF_FAILED(m_brushXaml.As(&brushXamlAsBrush));*/
        
        if (const auto brushXamlAsBrush = m_brushXaml.try_as<rtxaml::Media::Brush>())
        {
            // Change positions+brush for all actives elements
            for (int x = 0, index = 0; x < numberImagePerRow; x++)
            {
                for (int y = 0; y < numberImagePerColumn; y++, index++)
                {
                    // Get Rectangle
                    auto rectangle = m_xamlChildren[index];

                    // For cover, the bitmapimage must be scaled to fill the container and then clipped to only the
                    // necessary section Set rectangle.Fill
                   /* ComPtr<IShape> rectangleAsShape;
                    THROW_IF_FAILED(rectangle.As(&rectangleAsShape));
                    THROW_IF_FAILED(rectangleAsShape->put_Fill(brushXamlAsBrush.Get()));*/
                    auto rectangleAsShape = rectangle.as<rtxaml::Shapes::Shape>();

                    // Convert rectangle to UIElement
                    auto rectangleAsUIElement = rectangleAsShape.as<rtxaml::UIElement>();

                    double originPositionX{}, originPositionY{};
                    if (fillMode != rtom::BackgroundImageFillMode::Cover)
                    {
                        originPositionX = (x * m_imageSize.Width) + offsetHorizontalAlignment;
                        originPositionY = (y * m_imageSize.Height) + offsetVerticalAlignment;
                    }

                    rtxaml::Controls::ICanvasStatics canvasStatics;

                    // Set Left and Top for rectangle
                   /* ComPtr<ICanvasStatics> canvasStatics;
                    ABI::Windows::Foundation::GetActivationFactory(
                        HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Canvas).Get(), &canvasStatics);*/
                    canvasStatics.SetLeft(rectangleAsUIElement, originPositionX);
                    canvasStatics.SetTop(rectangleAsUIElement, originPositionY);

                    double imageWidth{}, imageHeight{};
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

                    auto rectangleAsFElement = rectangle.as<rtxaml::FrameworkElement>();
                    // Set Width and Height for Rectangle
                    rectangleAsFElement.Width(imageWidth);
                    rectangleAsFElement.Height(imageHeight);

                    if (fillMode == rtom::BackgroundImageFillMode::Cover)
                    {
                        auto brushXamlAsTileBrush = m_brushXaml.as<rtxaml::Media::TileBrush>();

                        brushXamlAsTileBrush.Stretch(rtxaml::Media::Stretch::UniformToFill);

                        // Vertical and Horizontal Alignments map to the same values in our shared model and UWP, so we just cast
                        brushXamlAsTileBrush.AlignmentX(static_cast<rtxaml::Media::AlignmentX>(hAlignment));
                        brushXamlAsTileBrush.AlignmentY(static_cast<rtxaml::Media::AlignmentY>(vAlignment));
                    }
                }
            }
        }
    }

    void TileControl::ExtractBackgroundImageData(rtom::BackgroundImageFillMode& fillMode, rtom::HAlignment& hAlignment, rtom::VAlignment& vAlignment)
    {
        fillMode = m_adaptiveBackgroundImage.FillMode();
        hAlignment = m_adaptiveBackgroundImage.HorizontalAlignment();
        vAlignment = m_adaptiveBackgroundImage.VerticalAlignment();
    }
}
