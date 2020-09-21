// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include <cmath>
#include "AdaptiveBackgroundImage.h"
#include "TileControl.h"
#include "XamlHelpers.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;

using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Shapes;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Media;
using namespace ABI::Windows::UI::Xaml::Media::Imaging;

namespace AdaptiveNamespace
{
    HRESULT TileControl::RuntimeClassInitialize() noexcept
    try
    {
        ComPtr<IContentControlFactory> spFactory;
        RETURN_IF_FAILED(Windows::Foundation::GetActivationFactory(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ContentControl).Get(), &spFactory));

        // Create composable base
        ComPtr<IInspectable> spInnerInspectable;
        ComPtr<IContentControl> spInnerContentControl;
        RETURN_IF_FAILED(spFactory->CreateInstance(static_cast<ITileControl*>(this),
                                                   spInnerInspectable.GetAddressOf(),
                                                   spInnerContentControl.GetAddressOf()));
        RETURN_IF_FAILED(SetComposableBasePointers(spInnerInspectable.Get(), spFactory.Get()));

        // initialize members
        m_containerElement =
            XamlHelpers::CreateXamlClass<ICanvas>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Canvas));
        m_brushXaml = XamlHelpers::CreateXamlClass<IImageBrush>(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_ImageBrush));

        // Add m_containerElement to content of ContentControl
        ComPtr<IInspectable> content;
        RETURN_IF_FAILED(m_containerElement.As(&content));
        RETURN_IF_FAILED(spInnerContentControl->put_Content(content.Get()));

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT TileControl::put_BackgroundImage(_In_ IAdaptiveBackgroundImage* value)
    {
        m_adaptiveBackgroundImage = value;
        return S_OK;
    }

    HRESULT TileControl::put_RootElement(_In_ IFrameworkElement* value)
    {
        m_rootElement = value;
        return S_OK;
    }

    HRESULT TileControl::get_ResolvedImage(_COM_Outptr_ IUIElement** value) { return m_resolvedImage.CopyTo(value); }

    HRESULT TileControl::put_ImageSize(_In_ Size value)
    {
        m_imageSize = value;
        return S_OK;
    }

    HRESULT TileControl::LoadImageBrush(_In_ IUIElement* uielement)
    {
        m_resolvedImage = uielement;

        ComPtr<IImage> image;
        RETURN_IF_FAILED(m_resolvedImage.As(&image));

        if (image == nullptr)
        {
            return E_INVALIDARG;
        }

        ComPtr<IImageSource> imageSource;
        THROW_IF_FAILED(image->get_Source(&imageSource));

        if (imageSource == nullptr)
        {
            return E_INVALIDARG;
        }

        ComPtr<IBitmapImage> bitmapImage;
        THROW_IF_FAILED(imageSource.As(&bitmapImage));

        if (bitmapImage == nullptr)
        {
            return E_INVALIDARG;
        }

        EventRegistrationToken eventToken;

        THROW_IF_FAILED(bitmapImage->add_ImageOpened(Callback<IRoutedEventHandler>(
            [&](IInspectable* /*sender*/, IRoutedEventArgs* /*args*/) -> HRESULT {
                ComPtr<IUIElement> uiElement;
                THROW_IF_FAILED(get_ResolvedImage(&uiElement));

                // Extract BitmapSource from Image
                ComPtr<IImage> image;
                THROW_IF_FAILED(uiElement.As(&image));
                ComPtr<IImageSource> imageSource;
                THROW_IF_FAILED(image->get_Source(&imageSource));
                ComPtr<IBitmapSource> bitmapSource;
                THROW_IF_FAILED(imageSource.As(&bitmapSource));

                // Extract Size from Image
                int height{}, width{};
                THROW_IF_FAILED(bitmapSource->get_PixelHeight(&height));
                THROW_IF_FAILED(bitmapSource->get_PixelWidth(&width));

                // Save size to member variable
                Size imageSize{};
                imageSize.Height = static_cast<float>(height);
                imageSize.Width = static_cast<float>(width);
                THROW_IF_FAILED(put_ImageSize(imageSize));

                RefreshContainerTile();
                return S_OK;
            }).Get(),
                &eventToken));

        THROW_IF_FAILED(m_brushXaml->put_ImageSource(imageSource.Get()));

        return S_OK;
    }

    HRESULT TileControl::OnApplyTemplate()
    {
        // Call OnApplyTemplate() for composable base
        ComPtr<IInspectable> composableBase = GetComposableBase();
        ComPtr<IFrameworkElementOverrides> frameworkOverrides;
        RETURN_IF_FAILED(composableBase.As(&frameworkOverrides));
        return frameworkOverrides->OnApplyTemplate();
    }

    HRESULT TileControl::MeasureOverride(Size availableSize, Size* pReturnValue)
    {
        ComPtr<IFrameworkElementOverrides> base;
        RETURN_IF_FAILED(GetComposableBase()->QueryInterface(__uuidof(IFrameworkElementOverrides),
                                                             reinterpret_cast<void**>(base.GetAddressOf())));

        return base->MeasureOverride(availableSize, pReturnValue);
    }

    HRESULT TileControl::ArrangeOverride(Size arrangeBounds, Size* pReturnValue)
    {
        ComPtr<IFrameworkElementOverrides> base;
        RETURN_IF_FAILED(GetComposableBase()->QueryInterface(__uuidof(IFrameworkElementOverrides),
                                                             reinterpret_cast<void**>(base.GetAddressOf())));

        RETURN_IF_FAILED(base->ArrangeOverride(arrangeBounds, pReturnValue));
        m_containerSize = *pReturnValue;

        // Define clip properties for m_containerElement
        Rect* rect = new Rect();
        rect->X = 0;
        rect->Y = 0;
        rect->Width = m_containerSize.Width;
        rect->Height = m_containerSize.Height;

        ComPtr<IRectangleGeometry> clip = AdaptiveNamespace::XamlHelpers::CreateXamlClass<IRectangleGeometry>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Media_RectangleGeometry));
        RETURN_IF_FAILED(clip->put_Rect(*rect));

        ComPtr<IUIElement> containerAsUIElement;
        RETURN_IF_FAILED(m_containerElement.As(&containerAsUIElement));
        RETURN_IF_FAILED(containerAsUIElement->put_Clip(clip.Get()));

        RefreshContainerTile();
        return S_OK;
    }

    void TileControl::RefreshContainerTile()
    {
        BackgroundImageFillMode fillMode{};
        HAlignment hAlignment{};
        VAlignment vAlignment{};
        THROW_IF_FAILED(ExtractBackgroundImageData(&fillMode, &hAlignment, &vAlignment));

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
            case BackgroundImageFillMode::RepeatHorizontally:
                numberImagePerRow = static_cast<int>(ceil(m_containerSize.Width / m_imageSize.Width));
                numberImagePerColumn = 1;

                switch (vAlignment)
                {
                case VAlignment::Bottom:
                    offsetVerticalAlignment = m_containerSize.Height - m_imageSize.Height;
                    break;
                case VAlignment::Center:
                    offsetVerticalAlignment = static_cast<float>((m_containerSize.Height - m_imageSize.Height) / 2.0f);
                    break;
                case VAlignment::Top:
                default:
                    break;
                }
                break;

            case BackgroundImageFillMode::RepeatVertically:
                numberImagePerRow = 1;
                numberImagePerColumn = static_cast<int>(ceil(m_containerSize.Height / m_imageSize.Height));

                switch (hAlignment)
                {
                case HAlignment::Right:
                    offsetHorizontalAlignment = m_containerSize.Width - m_imageSize.Width;
                    break;
                case HAlignment::Center:
                    offsetHorizontalAlignment = static_cast<float>((m_containerSize.Width - m_imageSize.Width) / 2.0f);
                    break;
                case HAlignment::Left:
                default:
                    break;
                }
                break;

            case BackgroundImageFillMode::Repeat:
                numberImagePerColumn = static_cast<int>(ceil(m_containerSize.Height / m_imageSize.Height));
                numberImagePerRow = static_cast<int>(ceil(m_containerSize.Width / m_imageSize.Width));
                break;

            case BackgroundImageFillMode::Cover:
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
        ComPtr<IVector<UIElement*>> children;
        ComPtr<IPanel> containerElementAsPanel;
        THROW_IF_FAILED(m_containerElement.As(&containerElementAsPanel));
        THROW_IF_FAILED(containerElementAsPanel->get_Children(&children));

        if (numberSpriteToInstanciate > count)
        {
            // instanciate all elements not created yet
            for (int x{}; x < (numberSpriteToInstanciate - count); x++)
            {
                ComPtr<IRectangle> rectangle = AdaptiveNamespace::XamlHelpers::CreateXamlClass<IRectangle>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Rectangle));

                ComPtr<IUIElement> rectangleAsUIElement;
                THROW_IF_FAILED(rectangle.As(&rectangleAsUIElement));
                THROW_IF_FAILED(children->Append(rectangleAsUIElement.Get()));

                m_xamlChildren.push_back(rectangle);
            }
        }
        else
        {
            // remove elements not used now
            for (int x{}; x < (count - numberSpriteToInstanciate); ++x)
            {
                THROW_IF_FAILED(children->RemoveAtEnd());
                m_xamlChildren.pop_back();
            }
        }

        // Convert ImageBrush to Brush
        ComPtr<IBrush> brushXamlAsBrush;
        THROW_IF_FAILED(m_brushXaml.As(&brushXamlAsBrush));

        // Change positions+brush for all actives elements
        for (int x = 0, index = 0; x < numberImagePerRow; x++)
        {
            for (int y = 0; y < numberImagePerColumn; y++, index++)
            {
                // Get Rectangle
                auto rectangle = m_xamlChildren[index];

                // For cover, the bitmapimage must be scaled to fill the container and then clipped to only the
                // necessary section Set rectangle.Fill
                ComPtr<IShape> rectangleAsShape;
                THROW_IF_FAILED(rectangle.As(&rectangleAsShape));
                THROW_IF_FAILED(rectangleAsShape->put_Fill(brushXamlAsBrush.Get()));

                // Convert rectangle to UIElement
                ComPtr<IUIElement> rectangleAsUIElement;
                THROW_IF_FAILED(rectangleAsShape.As(&rectangleAsUIElement));

                double originPositionX{}, originPositionY{};
                if (fillMode != BackgroundImageFillMode::Cover)
                {
                    originPositionX = (x * m_imageSize.Width) + offsetHorizontalAlignment;
                    originPositionY = (y * m_imageSize.Height) + offsetVerticalAlignment;
                }

                // Set Left and Top for rectangle
                ComPtr<ICanvasStatics> canvasStatics;
                ABI::Windows::Foundation::GetActivationFactory(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Canvas).Get(), &canvasStatics);
                THROW_IF_FAILED(canvasStatics->SetLeft(rectangleAsUIElement.Get(), originPositionX));
                THROW_IF_FAILED(canvasStatics->SetTop(rectangleAsUIElement.Get(), originPositionY));

                double imageWidth{}, imageHeight{};
                if (fillMode == BackgroundImageFillMode::Cover)
                {
                    imageWidth = m_containerSize.Width;
                    imageHeight = m_containerSize.Height;
                }
                else
                {
                    imageWidth = m_imageSize.Width;
                    imageHeight = m_imageSize.Height;
                }

                ComPtr<IFrameworkElement> rectangleAsFElement;
                THROW_IF_FAILED(rectangle.As(&rectangleAsFElement));
                // Set Width and Height for Rectangle
                THROW_IF_FAILED(rectangleAsFElement->put_Width(imageWidth));
                THROW_IF_FAILED(rectangleAsFElement->put_Height(imageHeight));

                if (fillMode == BackgroundImageFillMode::Cover)
                {
                    ComPtr<ITileBrush> brushXamlAsTileBrush;
                    THROW_IF_FAILED(m_brushXaml.As(&brushXamlAsTileBrush));

                    THROW_IF_FAILED(brushXamlAsTileBrush->put_Stretch(Stretch_UniformToFill));

                    // Vertical and Horizontal Alignments map to the same values in our shared model and UWP, so we just cast
                    THROW_IF_FAILED(brushXamlAsTileBrush->put_AlignmentX(static_cast<AlignmentX>(hAlignment)));
                    THROW_IF_FAILED(brushXamlAsTileBrush->put_AlignmentY(static_cast<AlignmentY>(vAlignment)));
                }
            }
        }
    }

    HRESULT TileControl::ExtractBackgroundImageData(BackgroundImageFillMode* fillMode, HAlignment* hAlignment, VAlignment* vAlignment)
    {
        RETURN_IF_FAILED(m_adaptiveBackgroundImage->get_FillMode(fillMode));
        RETURN_IF_FAILED(m_adaptiveBackgroundImage->get_HorizontalAlignment(hAlignment));
        RETURN_IF_FAILED(m_adaptiveBackgroundImage->get_VerticalAlignment(vAlignment));
        return S_OK;
    }
}
