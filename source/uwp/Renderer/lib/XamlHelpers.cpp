// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "XamlHelpers.h"

#include "ActionHelpers.h"
#include "ElementTagContent.h"
#include "TileControl.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Automation;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::UI::Xaml::Documents;
using namespace ABI::Windows::UI::Xaml::Input;
using namespace ABI::Windows::UI::Xaml::Media;
using namespace ABI::Windows::UI::Xaml::Media::Imaging;

namespace AdaptiveCards::Rendering::Uwp::XamlHelpers
{
    constexpr PCWSTR c_BackgroundImageOverlayBrushKey = L"AdaptiveCard.BackgroundOverlayBrush";

    ComPtr<IUIElement> CreateSeparator(_In_ IAdaptiveRenderContext* renderContext,
                                       UINT spacing,
                                       UINT separatorThickness,
                                       ABI::Windows::UI::Color separatorColor,
                                       bool isHorizontal)
    {
        ComPtr<IGrid> separator =
            XamlHelpers::CreateABIClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IFrameworkElement> separatorAsFrameworkElement;
        THROW_IF_FAILED(separator.As(&separatorAsFrameworkElement));

        ComPtr<IBrush> lineColorBrush = XamlHelpers::GetSolidColorBrush(separatorColor);
        ComPtr<IPanel> separatorAsPanel;
        THROW_IF_FAILED(separator.As(&separatorAsPanel));
        separatorAsPanel->put_Background(lineColorBrush.Get());

        const UINT32 separatorMarginValue = spacing > separatorThickness ? (spacing - separatorThickness) / 2 : 0;
        Thickness margin = {0, 0, 0, 0};

        if (isHorizontal)
        {
            margin.Top = margin.Bottom = separatorMarginValue;
            separatorAsFrameworkElement->put_Height(separatorThickness);
        }
        else
        {
            margin.Left = margin.Right = separatorMarginValue;
            separatorAsFrameworkElement->put_Width(separatorThickness);
        }

        THROW_IF_FAILED(separatorAsFrameworkElement->put_Margin(margin));

        THROW_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                    L"Adaptive.Separator",
                                                                    separatorAsFrameworkElement.Get()));

        ComPtr<IUIElement> result;
        THROW_IF_FAILED(separator.As(&result));
        return result;
    }

    HRESULT SetStyleFromResourceDictionary(_In_ IAdaptiveRenderContext* renderContext,
                                           HSTRING resourceName,
                                           _In_ IFrameworkElement* frameworkElement) noexcept
    {
        ComPtr<IResourceDictionary> resourceDictionary;
        RETURN_IF_FAILED(renderContext->get_OverrideStyles(&resourceDictionary));

        ComPtr<IStyle> style;
        if (SUCCEEDED(TryGetResourceFromResourceDictionaries<IStyle>(resourceDictionary.Get(), resourceName, &style)))
        {
            RETURN_IF_FAILED(frameworkElement->put_Style(style.Get()));
        }

        return S_OK;
    }

    HRESULT SetStyleFromResourceDictionary(_In_ IAdaptiveRenderContext* renderContext,
                                           const wchar_t* resourceName,
                                           _In_ IFrameworkElement* frameworkElement) noexcept
    {
        return SetStyleFromResourceDictionary(renderContext, HStringReference(resourceName).Get(), frameworkElement);
    }

    void SetStyleFromResourceDictionary(winrt::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext renderContext,
                                        winrt::hstring resourceName,
                                        winrt::Windows::UI::Xaml::IFrameworkElement frameworkElement)
    {
        THROW_IF_FAILED(SetStyleFromResourceDictionary(
            renderContext.as<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext>().get(),
            std::wstring_view(resourceName).data(),
            frameworkElement.as<ABI::Windows::UI::Xaml::IFrameworkElement>().get()));
    }

    HRESULT XamlHelpers::SetSeparatorVisibility(_In_ IPanel* parentPanel)
    {
        // Iterate over the elements in a container and ensure that the correct separators are marked as visible
        ComPtr<IVector<UIElement*>> children;
        RETURN_IF_FAILED(parentPanel->get_Children(&children));

        bool foundPreviousVisibleElement = false;
        IterateOverVector<UIElement, IUIElement>(children.Get(),
                                                 [&](IUIElement* child)
                                                 {
                                                     ComPtr<IUIElement> localChild(child);

                                                     ComPtr<IFrameworkElement> childAsFrameworkElement;
                                                     RETURN_IF_FAILED(localChild.As(&childAsFrameworkElement));

                                                     // Get the tag for the element. The separators themselves will not have tags.
                                                     ComPtr<IInspectable> tag;
                                                     RETURN_IF_FAILED(childAsFrameworkElement->get_Tag(&tag));

                                                     if (tag)
                                                     {
                                                         ComPtr<IElementTagContent> elementTagContent;
                                                         RETURN_IF_FAILED(tag.As(&elementTagContent));

                                                         ComPtr<IUIElement> separator;
                                                         RETURN_IF_FAILED(elementTagContent->get_Separator(&separator));

                                                         Visibility visibility;
                                                         RETURN_IF_FAILED(child->get_Visibility(&visibility));

                                                         boolean expectedVisibility{};
                                                         RETURN_IF_FAILED(elementTagContent->get_ExpectedVisibility(&expectedVisibility));

                                                         if (separator)
                                                         {
                                                             if (!expectedVisibility || !foundPreviousVisibleElement)
                                                             {
                                                                 // If the element is collapsed, or if it's the first
                                                                 // visible element, collapse the separator Images are
                                                                 // hidden while they are retrieved, we shouldn't hide
                                                                 // the separator
                                                                 RETURN_IF_FAILED(separator->put_Visibility(Visibility_Collapsed));
                                                             }
                                                             else
                                                             {
                                                                 // Otherwise show the separator
                                                                 RETURN_IF_FAILED(separator->put_Visibility(Visibility_Visible));
                                                             }
                                                         }

                                                         foundPreviousVisibleElement |= (visibility == Visibility_Visible);
                                                     }

                                                     return S_OK;
                                                 });

        return S_OK;
    }

    void SetContent(winrt::Windows::UI::Xaml::Controls::IContentControl contentControl, winrt::param::hstring contentString, boolean wrap)
    {
        winrt::Windows::UI::Xaml::Controls::TextBlock textBlock{};
        textBlock.Text(contentString);

        if (wrap)
        {
            textBlock.TextWrapping(winrt::Windows::UI::Xaml::TextWrapping::WrapWholeWords);
        }

        contentControl.Content(textBlock);
    }

    HRESULT HandleStylingAndPadding(_In_ IAdaptiveContainerBase* adaptiveContainer,
                                    _In_ IBorder* containerBorder,
                                    _In_ IAdaptiveRenderContext* renderContext,
                                    _In_ IAdaptiveRenderArgs* renderArgs,
                                    _Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle* containerStyle)
    {
        ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle localContainerStyle;
        RETURN_IF_FAILED(adaptiveContainer->get_Style(&localContainerStyle));

        ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle parentContainerStyle;
        RETURN_IF_FAILED(renderArgs->get_ContainerStyle(&parentContainerStyle));

        bool hasExplicitContainerStyle{true};
        if (localContainerStyle == ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle::None)
        {
            hasExplicitContainerStyle = false;
            localContainerStyle = parentContainerStyle;
        }

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        ComPtr<IAdaptiveSpacingConfig> spacingConfig;
        RETURN_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

        UINT32 padding;
        RETURN_IF_FAILED(spacingConfig->get_Padding(&padding));
        DOUBLE paddingAsDouble = static_cast<DOUBLE>(padding);

        boolean addContainerPadding;
        RETURN_IF_FAILED(renderArgs->get_AddContainerPadding(&addContainerPadding));

        // If container style was explicitly assigned, apply background color and padding
        if (hasExplicitContainerStyle)
        {
            ABI::Windows::UI::Color backgroundColor;
            RETURN_IF_FAILED(GetBackgroundColorFromStyle(localContainerStyle, hostConfig.Get(), &backgroundColor));
            ComPtr<IBrush> backgroundColorBrush = XamlHelpers::GetSolidColorBrush(backgroundColor);
            RETURN_IF_FAILED(containerBorder->put_Background(backgroundColorBrush.Get()));

            // If the container style doesn't match its parent apply padding.
            addContainerPadding |= (localContainerStyle != parentContainerStyle);
        }

        if (addContainerPadding)
        {
            Thickness paddingThickness = {paddingAsDouble, paddingAsDouble, paddingAsDouble, paddingAsDouble};
            RETURN_IF_FAILED(containerBorder->put_Padding(paddingThickness));
        }

        // Find out which direction(s) we bleed in, and apply a negative margin to cause the
        // container to bleed
        ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection bleedDirection;
        RETURN_IF_FAILED(adaptiveContainer->get_BleedDirection(&bleedDirection));

        Thickness marginThickness = {0};
        if (bleedDirection != ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection::None)
        {
            if ((bleedDirection & ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection::Left) !=
                ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection::None)
            {
                marginThickness.Left = -paddingAsDouble;
            }

            if ((bleedDirection & ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection::Right) !=
                ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection::None)
            {
                marginThickness.Right = -paddingAsDouble;
            }

            if ((bleedDirection & ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection::Up) !=
                ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection::None)
            {
                marginThickness.Top = -paddingAsDouble;
            }

            if ((bleedDirection & ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection::Down) !=
                ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection::None)
            {
                marginThickness.Bottom = -paddingAsDouble;
            }

            ComPtr<IBorder> localContainerBorder(containerBorder);
            ComPtr<IFrameworkElement> containerBorderAsFrameworkElement;
            RETURN_IF_FAILED(localContainerBorder.As(&containerBorderAsFrameworkElement));
            RETURN_IF_FAILED(containerBorderAsFrameworkElement->put_Margin(marginThickness));
        }

        *containerStyle = localContainerStyle;

        return S_OK;
    }

    bool SupportsInteractivity(_In_ IAdaptiveHostConfig* hostConfig)
    {
        boolean supportsInteractivity;
        THROW_IF_FAILED(hostConfig->get_SupportsInteractivity(&supportsInteractivity));
        return Boolify(supportsInteractivity);
    }

    GridLength CalculateColumnWidth(bool isVisible, bool isAuto, bool isStretch, bool isUnsetWidth, UINT32 pixelWidth, double ratioWidth)
    {
        const boolean isValidWidth = isAuto || isStretch || pixelWidth || isUnsetWidth || (ratioWidth > 0);

        GridLength columnWidth;
        if (!isVisible || isAuto || !isValidWidth)
        {
            // If the column isn't visible, or is set to "auto" or an invalid value ("-1", "foo"), set it to Auto
            columnWidth.GridUnitType = GridUnitType::GridUnitType_Auto;
            columnWidth.Value = 0;
        }
        else if (pixelWidth)
        {
            // If it's visible and pixel width is specified, use pixel width
            columnWidth.GridUnitType = GridUnitType::GridUnitType_Pixel;
            columnWidth.Value = pixelWidth;
        }
        else if (isStretch || isUnsetWidth)
        {
            // If it's visible and stretch is specified, or width is unset, use stretch with default of 1
            columnWidth.GridUnitType = GridUnitType::GridUnitType_Star;
            columnWidth.Value = 1;
        }
        else
        {
            // If it's visible and the user specified a valid non-pixel width, use that as a star width
            columnWidth.GridUnitType = GridUnitType::GridUnitType_Star;
            columnWidth.Value = ratioWidth;
        }

        return columnWidth;
    }

    HRESULT HandleColumnWidth(_In_ IAdaptiveColumn* column, boolean isVisible, _In_ IColumnDefinition* columnDefinition)
    {
        HString adaptiveColumnWidth;
        RETURN_IF_FAILED(column->get_Width(adaptiveColumnWidth.GetAddressOf()));

        INT32 isStretchResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(adaptiveColumnWidth.Get(), HStringReference(L"stretch").Get(), &isStretchResult));
        const boolean isStretch = (isStretchResult == 0);

        INT32 isAutoResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(adaptiveColumnWidth.Get(), HStringReference(L"auto").Get(), &isAutoResult));
        const boolean isAuto = (isAutoResult == 0);

        double widthAsDouble = _wtof(adaptiveColumnWidth.GetRawBuffer(nullptr));
        UINT32 pixelWidth = 0;
        RETURN_IF_FAILED(column->get_PixelWidth(&pixelWidth));

        GridLength columnWidth =
            CalculateColumnWidth(isVisible, isAuto, isStretch, !adaptiveColumnWidth.IsValid(), pixelWidth, widthAsDouble);

        RETURN_IF_FAILED(columnDefinition->put_Width(columnWidth));

        return S_OK;
    }

    HRESULT HandleTableColumnWidth(_In_ IAdaptiveTableColumnDefinition* column, _In_ IColumnDefinition* columnDefinition)
    {
        ComPtr<IReference<UINT32>> width;
        RETURN_IF_FAILED(column->get_Width(&width));

        UINT32 widthValue = 0;
        if (width != nullptr)
        {
            RETURN_IF_FAILED(width->get_Value(&widthValue));
        }

        ComPtr<IReference<UINT32>> pixelWidth;
        RETURN_IF_FAILED(column->get_PixelWidth(&pixelWidth));

        UINT32 pixelWidthValue = 0;
        if (pixelWidth != nullptr)
        {
            RETURN_IF_FAILED(pixelWidth->get_Value(&pixelWidthValue));
        }

        bool isWidthUnset = (width == nullptr) && (pixelWidth == nullptr);

        GridLength columnWidth = CalculateColumnWidth(true, false, false, isWidthUnset, pixelWidthValue, widthValue);

        RETURN_IF_FAILED(columnDefinition->put_Width(columnWidth));

        return S_OK;
    }

    void ApplyBackgroundToRoot(_In_ IPanel* rootPanel,
                               _In_ IAdaptiveBackgroundImage* backgroundImage,
                               _In_ IAdaptiveRenderContext* renderContext,
                               _In_ IAdaptiveRenderArgs* renderArgs)
    {
        // In order to reuse the image creation code paths, we simply create an adaptive card
        // image element and then build that into xaml and apply to the root.
        ComPtr<IAdaptiveImage> adaptiveImage = XamlHelpers::CreateABIClass<IAdaptiveImage>(
            HStringReference(RuntimeClass_AdaptiveCards_ObjectModel_Uwp_AdaptiveImage));

        HString url;
        THROW_IF_FAILED(backgroundImage->get_Url(url.GetAddressOf()));
        THROW_IF_FAILED(adaptiveImage->put_Url(url.Get()));

        ComPtr<IAdaptiveCardElement> adaptiveCardElement;
        THROW_IF_FAILED(adaptiveImage.As(&adaptiveCardElement));

        ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
        THROW_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));

        ComPtr<IAdaptiveElementRenderer> elementRenderer;
        THROW_IF_FAILED(elementRenderers->Get(HStringReference(L"Image").Get(), &elementRenderer));

        ComPtr<IUIElement> background;
        if (elementRenderer != nullptr)
        {
            elementRenderer->Render(adaptiveCardElement.Get(), renderContext, renderArgs, &background);
            if (background == nullptr)
            {
                return;
            }
        }

        ComPtr<IImage> xamlImage;
        THROW_IF_FAILED(background.As(&xamlImage));

        ABI::AdaptiveCards::ObjectModel::Uwp::BackgroundImageFillMode fillMode;
        THROW_IF_FAILED(backgroundImage->get_FillMode(&fillMode));

        // Creates the background image for all fill modes
        ComPtr<TileControl> tileControl;
        THROW_IF_FAILED(MakeAndInitialize<TileControl>(&tileControl));

        // Set IsEnabled to false to avoid generating a tab stop for the background image tile control
        ComPtr<IControl> tileControlAsControl;
        THROW_IF_FAILED(tileControl.As(&tileControlAsControl));
        THROW_IF_FAILED(tileControlAsControl->put_IsEnabled(false));

        THROW_IF_FAILED(tileControl->put_BackgroundImage(backgroundImage));

        ComPtr<IFrameworkElement> rootElement;
        THROW_IF_FAILED(rootPanel->QueryInterface(rootElement.GetAddressOf()));
        THROW_IF_FAILED(tileControl->put_RootElement(rootElement.Get()));

        THROW_IF_FAILED(tileControl->LoadImageBrush(background.Get()));

        ComPtr<IFrameworkElement> backgroundAsFrameworkElement;
        THROW_IF_FAILED(tileControl.As(&backgroundAsFrameworkElement));

        XamlHelpers::AppendXamlElementToPanel(backgroundAsFrameworkElement.Get(), rootPanel);

        // The overlay applied to the background image is determined by a resouce, so create
        // the overlay if that resources exists
        ComPtr<IResourceDictionary> resourceDictionary;
        THROW_IF_FAILED(renderContext->get_OverrideStyles(&resourceDictionary));
        ComPtr<IBrush> backgroundOverlayBrush;
        if (SUCCEEDED(XamlHelpers::TryGetResourceFromResourceDictionaries<IBrush>(resourceDictionary.Get(),
                                                                                  c_BackgroundImageOverlayBrushKey,
                                                                                  &backgroundOverlayBrush)))
        {
            ComPtr<IShape> overlayRectangle =
                XamlHelpers::CreateABIClass<IShape>(HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Rectangle));
            THROW_IF_FAILED(overlayRectangle->put_Fill(backgroundOverlayBrush.Get()));

            ComPtr<IUIElement> overlayRectangleAsUIElement;
            THROW_IF_FAILED(overlayRectangle.As(&overlayRectangleAsUIElement));
            XamlHelpers::AppendXamlElementToPanel(overlayRectangle.Get(), rootPanel);
        }
    }

    HRESULT RenderFallback(_In_ IAdaptiveCardElement* currentElement,
                           _In_ IAdaptiveRenderContext* renderContext,
                           _In_ IAdaptiveRenderArgs* renderArgs,
                           _COM_Outptr_ IUIElement** result,
                           _COM_Outptr_ IAdaptiveCardElement** renderedElement)
    {
        ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
        RETURN_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));

        ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType elementFallback;
        RETURN_IF_FAILED(currentElement->get_FallbackType(&elementFallback));

        HString elementType;
        RETURN_IF_FAILED(currentElement->get_ElementTypeString(elementType.GetAddressOf()));

        bool fallbackHandled = false;
        ComPtr<IUIElement> fallbackControl;
        switch (elementFallback)
        {
        case ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType::Content:
        {
            // We have content, get the type of the fallback element
            ComPtr<IAdaptiveCardElement> fallbackElement;
            RETURN_IF_FAILED(currentElement->get_FallbackContent(&fallbackElement));

            HString fallbackElementType;
            RETURN_IF_FAILED(fallbackElement->get_ElementTypeString(fallbackElementType.GetAddressOf()));

            RETURN_IF_FAILED(WarnForFallbackContentElement(renderContext, elementType.Get(), fallbackElementType.Get()));

            // Try to render the fallback element
            ComPtr<IAdaptiveElementRenderer> fallbackElementRenderer;
            RETURN_IF_FAILED(elementRenderers->Get(fallbackElementType.Get(), &fallbackElementRenderer));
            HRESULT hr = E_PERFORM_FALLBACK;

            if (fallbackElementRenderer)
            {
                // perform this element's fallback
                hr = fallbackElementRenderer->Render(fallbackElement.Get(), renderContext, renderArgs, &fallbackControl);
                if (renderedElement)
                {
                    RETURN_IF_FAILED(fallbackElement.CopyTo(renderedElement));
                }
            }

            if (hr == E_PERFORM_FALLBACK)
            {
                // The fallback content told us to fallback, make a recursive call to this method
                RETURN_IF_FAILED(RenderFallback(fallbackElement.Get(), renderContext, renderArgs, &fallbackControl, renderedElement));
            }
            else
            {
                // Check the non-fallback return value from the render call
                RETURN_IF_FAILED(hr);
            }

            // We handled the fallback content
            fallbackHandled = true;
            break;
        }
        case ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType::Drop:
        {
            // If the fallback is drop, nothing to do but warn
            RETURN_IF_FAILED(XamlHelpers::WarnForFallbackDrop(renderContext, elementType.Get()));
            fallbackHandled = true;
            break;
        }
        case ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType::None:
        default:
        {
            break;
        }
        }

        if (fallbackHandled)
        {
            // We did it, copy out the result if any
            RETURN_IF_FAILED(fallbackControl.CopyTo(result));
            return S_OK;
        }
        else
        {
            // We didn't do it, can our ancestor?
            boolean ancestorHasFallback;
            RETURN_IF_FAILED(renderArgs->get_AncestorHasFallback(&ancestorHasFallback));

            if (!ancestorHasFallback)
            {
                // standard unknown element handling
                std::wstring errorString = L"No Renderer found for type: ";
                errorString += elementType.GetRawBuffer(nullptr);
                RETURN_IF_FAILED(renderContext->AddWarning(ABI::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode::NoRendererForType,
                                                           HStringReference(errorString.c_str()).Get()));
                return S_OK;
            }
            else
            {
                return E_PERFORM_FALLBACK;
            }
        }
    }

    void GetSeparationConfigForElement(_In_ IAdaptiveCardElement* cardElement,
                                       _In_ IAdaptiveHostConfig* hostConfig,
                                       _Out_ UINT* spacing,
                                       _Out_ UINT* separatorThickness,
                                       _Out_ ABI::Windows::UI::Color* separatorColor,
                                       _Out_ bool* needsSeparator)
    {
        ABI::AdaptiveCards::ObjectModel::Uwp::Spacing elementSpacing;
        THROW_IF_FAILED(cardElement->get_Spacing(&elementSpacing));

        UINT localSpacing;
        THROW_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig, elementSpacing, &localSpacing));

        boolean hasSeparator;
        THROW_IF_FAILED(cardElement->get_Separator(&hasSeparator));

        ABI::Windows::UI::Color localColor = {0};
        UINT localThickness = 0;
        if (hasSeparator)
        {
            ComPtr<IAdaptiveSeparatorConfig> separatorConfig;
            THROW_IF_FAILED(hostConfig->get_Separator(&separatorConfig));

            THROW_IF_FAILED(separatorConfig->get_LineColor(&localColor));
            THROW_IF_FAILED(separatorConfig->get_LineThickness(&localThickness));
        }

        *needsSeparator = hasSeparator || (elementSpacing != ABI::AdaptiveCards::ObjectModel::Uwp::Spacing::None);

        *spacing = localSpacing;
        *separatorThickness = localThickness;
        *separatorColor = localColor;
    }

    HRESULT AddRenderedControl(_In_ IUIElement* newControl,
                               _In_ IAdaptiveCardElement* element,
                               _In_ IPanel* parentPanel,
                               _In_ IUIElement* separator,
                               _In_ IColumnDefinition* columnDefinition,
                               std::function<void(IUIElement* child)> childCreatedCallback)
    {
        if (newControl != nullptr)
        {
            boolean isVisible;
            RETURN_IF_FAILED(element->get_IsVisible(&isVisible));

            if (!isVisible)
            {
                RETURN_IF_FAILED(newControl->put_Visibility(Visibility_Collapsed));
            }

            ComPtr<IUIElement> localControl(newControl);
            ComPtr<IFrameworkElement> newControlAsFrameworkElement;
            RETURN_IF_FAILED(localControl.As(&newControlAsFrameworkElement));

            HString id;
            RETURN_IF_FAILED(element->get_Id(id.GetAddressOf()));

            if (id.IsValid())
            {
                RETURN_IF_FAILED(newControlAsFrameworkElement->put_Name(id.Get()));
            }

            ABI::AdaptiveCards::ObjectModel::Uwp::HeightType heightType{};
            RETURN_IF_FAILED(element->get_Height(&heightType));

            ComPtr<ElementTagContent> tagContent;
            RETURN_IF_FAILED(MakeAndInitialize<ElementTagContent>(
                &tagContent, element, parentPanel, separator, columnDefinition, isVisible, heightType == HeightType_Stretch));
            RETURN_IF_FAILED(newControlAsFrameworkElement->put_Tag(tagContent.Get()));

            XamlHelpers::AppendXamlElementToPanel(newControl, parentPanel, heightType);

            childCreatedCallback(newControl);
        }
        return S_OK;
    }

    HRESULT AddHandledTappedEvent(_In_ IUIElement* uiElement)
    {
        if (uiElement == nullptr)
        {
            return E_INVALIDARG;
        }

        EventRegistrationToken clickToken;
        // Add Tap handler that sets the event as handled so that it doesn't propagate to the parent containers.
        return uiElement->add_Tapped(Callback<ITappedEventHandler>([](IInspectable* /*sender*/, ITappedRoutedEventArgs* args) -> HRESULT
                                                                   { return args->put_Handled(TRUE); })
                                         .Get(),
                                     &clickToken);
    }

    HRESULT SetAutoImageSize(_In_ IFrameworkElement* imageControl, _In_ IInspectable* parentElement, _In_ IBitmapSource* imageSource, bool setVisible)
    {
        INT32 pixelHeight;
        RETURN_IF_FAILED(imageSource->get_PixelHeight(&pixelHeight));
        INT32 pixelWidth;
        RETURN_IF_FAILED(imageSource->get_PixelWidth(&pixelWidth));
        DOUBLE maxHeight;
        DOUBLE maxWidth;
        ComPtr<IInspectable> localParentElement(parentElement);
        ComPtr<IFrameworkElement> localElement(imageControl);
        ComPtr<IColumnDefinition> parentAsColumnDefinition;

        RETURN_IF_FAILED(localElement->get_MaxHeight(&maxHeight));
        RETURN_IF_FAILED(localElement->get_MaxWidth(&maxWidth));

        if (SUCCEEDED(localParentElement.As(&parentAsColumnDefinition)))
        {
            DOUBLE parentWidth;
            RETURN_IF_FAILED(parentAsColumnDefinition->get_ActualWidth(&parentWidth));
            if (parentWidth >= pixelWidth)
            {
                // Make sure to keep the aspect ratio of the image
                maxWidth = std::min(maxWidth, parentWidth);
                double aspectRatio = (double)pixelHeight / pixelWidth;
                maxHeight = maxWidth * aspectRatio;
            }
        }

        // Prevent an image from being stretched out if it is smaller than the
        // space allocated for it (when in auto mode).
        ComPtr<IEllipse> localElementAsEllipse;
        if (SUCCEEDED(localElement.As(&localElementAsEllipse)))
        {
            // don't need to set both width and height when image size is auto since
            // we want a circle as shape.
            // max value for width should be set since adaptive cards is constrained horizontally
            RETURN_IF_FAILED(localElement->put_MaxWidth(std::min(maxWidth, static_cast<DOUBLE>(pixelWidth))));
        }
        else
        {
            RETURN_IF_FAILED(localElement->put_MaxHeight(std::min(maxHeight, static_cast<DOUBLE>(pixelHeight))));
            RETURN_IF_FAILED(localElement->put_MaxWidth(std::min(maxWidth, static_cast<DOUBLE>(pixelWidth))));
        }

        if (setVisible)
        {
            ComPtr<IUIElement> frameworkElementAsUIElement;
            RETURN_IF_FAILED(localElement.As(&frameworkElementAsUIElement));
            RETURN_IF_FAILED(frameworkElementAsUIElement->put_Visibility(Visibility::Visibility_Visible));
        }

        return S_OK;
    }

    void AddSeparatorIfNeeded(int& currentElement,
                              _In_ IAdaptiveCardElement* element,
                              _In_ IAdaptiveHostConfig* hostConfig,
                              _In_ IAdaptiveRenderContext* renderContext,
                              _In_ IPanel* parentPanel,
                              _Outptr_ IUIElement** addedSeparator)
    {
        // First element does not need a separator added
        if (currentElement++ > 0)
        {
            bool needsSeparator;
            UINT spacing;
            UINT separatorThickness;
            ABI::Windows::UI::Color separatorColor;
            XamlHelpers::GetSeparationConfigForElement(element, hostConfig, &spacing, &separatorThickness, &separatorColor, &needsSeparator);
            if (needsSeparator)
            {
                auto separator = XamlHelpers::CreateSeparator(renderContext, spacing, separatorThickness, separatorColor);
                XamlHelpers::AppendXamlElementToPanel(separator.Get(), parentPanel);
                THROW_IF_FAILED(separator.CopyTo(addedSeparator));
            }
        }
    }

    HRESULT ApplyMarginToXamlElement(_In_ IAdaptiveHostConfig* hostConfig, _In_ IFrameworkElement* element) noexcept
    {
        ComPtr<IFrameworkElement> localElement(element);
        ComPtr<IAdaptiveSpacingConfig> spacingConfig;
        RETURN_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

        UINT32 padding;
        spacingConfig->get_Padding(&padding);
        Thickness margin = {(double)padding, (double)padding, (double)padding, (double)padding};

        RETURN_IF_FAILED(localElement->put_Margin(margin));
        return S_OK;
    }

    HRESULT FormatLabelRunWithHostConfig(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                         _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputLabelConfig* inputLabelConfig,
                                         _In_ boolean isHint,
                                         ABI::Windows::UI::Xaml::Documents::IRun* labelRun)
    {
        ABI::AdaptiveCards::ObjectModel::Uwp::ForegroundColor textColor;

        // If we're formatting a hint then use attention color
        if (isHint)
        {
            textColor = ABI::AdaptiveCards::ObjectModel::Uwp::ForegroundColor::Attention;
        }
        else
        {
            RETURN_IF_FAILED(inputLabelConfig->get_Color(&textColor));
        }

        ABI::Windows::UI::Color color;
        RETURN_IF_FAILED(GetColorFromAdaptiveColor(hostConfig, textColor, ContainerStyle_Default, false, false, &color));

        ComPtr<ABI::Windows::UI::Xaml::Documents::IRun> xamlLabelRun(labelRun);

        ComPtr<ABI::Windows::UI::Xaml::Documents::ITextElement> labelRunAsTextElement;
        RETURN_IF_FAILED(xamlLabelRun.As(&labelRunAsTextElement));

        RETURN_IF_FAILED(labelRunAsTextElement->put_Foreground(XamlHelpers::GetSolidColorBrush(color).Get()));

        ABI::AdaptiveCards::ObjectModel::Uwp::TextSize textSize;
        RETURN_IF_FAILED(inputLabelConfig->get_Size(&textSize));

        UINT32 resultSize{};
        RETURN_IF_FAILED(GetFontSizeFromFontType(hostConfig, ABI::AdaptiveCards::ObjectModel::Uwp::FontType_Default, textSize, &resultSize));

        RETURN_IF_FAILED(labelRunAsTextElement->put_FontSize(resultSize));

        return S_OK;
    }

    HRESULT AddRequiredHintInline(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                  _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputLabelConfig* inputLabelConfig,
                                  IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines)
    {
        ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> xamlInlines(inlines);

        // Create an inline for the suffix
        ComPtr<IRun> hintRun = XamlHelpers::CreateABIClass<IRun>(HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Run));

        HString suffix;
        RETURN_IF_FAILED(inputLabelConfig->get_Suffix(suffix.GetAddressOf()));

        // If no suffix was defined, use * as default
        if (WindowsIsStringEmpty(suffix.Get()))
        {
            RETURN_IF_FAILED(UTF8ToHString(" *", suffix.GetAddressOf()));
        }

        RETURN_IF_FAILED(hintRun->put_Text(suffix.Get()));

        FormatLabelRunWithHostConfig(hostConfig, inputLabelConfig, true /*isHint*/, hintRun.Get());

        ComPtr<ABI::Windows::UI::Xaml::Documents::ITextElement> hintRunAsTextElement;
        RETURN_IF_FAILED(hintRun.As(&hintRunAsTextElement));

        ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> hintRunAsInline;
        RETURN_IF_FAILED(hintRun.As(&hintRunAsInline));

        RETURN_IF_FAILED(xamlInlines->Append(hintRunAsInline.Get()));

        return S_OK;
    }

    HRESULT RenderInputLabel(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInputElement* adaptiveInputElement,
                             _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                             _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* /*renderArgs*/,
                             _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** labelControl)
    {
        HString inputLabel;
        RETURN_IF_FAILED(adaptiveInputElement->get_Label(inputLabel.GetAddressOf()));

        // Retrieve if the input is required so we can file a warning if the label is empty
        boolean isRequired;
        RETURN_IF_FAILED(adaptiveInputElement->get_IsRequired(&isRequired));

        if (inputLabel != nullptr)
        {
            // Create a rich text block for the label
            ComPtr<IRichTextBlock> xamlRichTextBlock = XamlHelpers::CreateABIClass<IRichTextBlock>(
                HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RichTextBlock));

            // Add a paragraph for the inlines
            ComPtr<IVector<Block*>> xamlBlocks;
            RETURN_IF_FAILED(xamlRichTextBlock->get_Blocks(&xamlBlocks));

            ComPtr<IParagraph> xamlParagraph =
                XamlHelpers::CreateABIClass<IParagraph>(HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Paragraph));

            ComPtr<IBlock> paragraphAsBlock;
            RETURN_IF_FAILED(xamlParagraph.As(&paragraphAsBlock));
            RETURN_IF_FAILED(xamlBlocks->Append(paragraphAsBlock.Get()));

            // Add the Inlines
            ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> xamlInlines;
            RETURN_IF_FAILED(xamlParagraph->get_Inlines(&xamlInlines));

            // First inline is the label from the card
            ComPtr<IRun> labelRun =
                XamlHelpers::CreateABIClass<IRun>(HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Run));
            RETURN_IF_FAILED(labelRun->put_Text(inputLabel.Get()));

            ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> labelRunAsInline;
            RETURN_IF_FAILED(labelRun.As(&labelRunAsInline));

            RETURN_IF_FAILED(xamlInlines->Append(labelRunAsInline.Get()));

            // Get the label config depending if the input is required
            ComPtr<IAdaptiveHostConfig> hostConfig;
            RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

            ComPtr<IAdaptiveInputsConfig> inputsConfig;
            RETURN_IF_FAILED(hostConfig->get_Inputs(&inputsConfig));

            ComPtr<IAdaptiveLabelConfig> labelConfig;
            RETURN_IF_FAILED(inputsConfig->get_Label(&labelConfig));

            ComPtr<IAdaptiveInputLabelConfig> inputLabelConfig;
            if (isRequired)
            {
                RETURN_IF_FAILED(labelConfig->get_RequiredInputs(&inputLabelConfig));
            }
            else
            {
                RETURN_IF_FAILED(labelConfig->get_OptionalInputs(&inputLabelConfig));
            }

            if (isRequired)
            {
                RETURN_IF_FAILED(AddRequiredHintInline(hostConfig.Get(), inputLabelConfig.Get(), xamlInlines.Get()));
            }

            RETURN_IF_FAILED(
                FormatLabelRunWithHostConfig(hostConfig.Get(), inputLabelConfig.Get(), false /*isHint*/, labelRun.Get()));

            RETURN_IF_FAILED(xamlRichTextBlock->put_TextWrapping(TextWrapping_Wrap));

            RETURN_IF_FAILED(xamlRichTextBlock.CopyTo(labelControl));
        }
        else if (isRequired)
        {
            // if there was no label but the input is required file a warning for the card author
            RETURN_IF_FAILED(renderContext->AddWarning(
                ABI::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode::EmptyLabelInRequiredInput,
                HStringReference(L"Input is required but there's no label for required hint rendering").Get()));
        }

        return S_OK;
    }

    // Error messages are formatted for text size and weight
    HRESULT FormatErrorMessageWithHostConfig(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                             ITextBlock* errorMessage)
    {
        ComPtr<ITextBlock> xamlErrorMessage(errorMessage);

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(hostConfig.GetAddressOf()));

        ComPtr<IAdaptiveInputsConfig> inputsConfig;
        RETURN_IF_FAILED(hostConfig->get_Inputs(inputsConfig.GetAddressOf()));

        ComPtr<IAdaptiveErrorMessageConfig> errorMessageConfig;
        RETURN_IF_FAILED(inputsConfig->get_ErrorMessage(errorMessageConfig.GetAddressOf()));

        // Set size defined in host config
        ABI::AdaptiveCards::ObjectModel::Uwp::TextSize textSize;
        RETURN_IF_FAILED(errorMessageConfig->get_Size(&textSize));

        UINT32 resultSize{};
        RETURN_IF_FAILED(
            GetFontSizeFromFontType(hostConfig.Get(), ABI::AdaptiveCards::ObjectModel::Uwp::FontType_Default, textSize, &resultSize));

        RETURN_IF_FAILED(xamlErrorMessage->put_FontSize(resultSize));

        // Set weight defined in host config
        ABI::AdaptiveCards::ObjectModel::Uwp::TextWeight textWeight;
        RETURN_IF_FAILED(errorMessageConfig->get_Weight(&textWeight));

        ABI::Windows::UI::Text::FontWeight resultWeight;
        RETURN_IF_FAILED(
            GetFontWeightFromStyle(hostConfig.Get(), ABI::AdaptiveCards::ObjectModel::Uwp::FontType_Default, textWeight, &resultWeight));

        RETURN_IF_FAILED(xamlErrorMessage->put_FontWeight(resultWeight));

        return S_OK;
    }

    HRESULT RenderInputErrorMessage(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInputElement* adaptiveInputElement,
                                    _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                    _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** errorMessageControl)
    {
        // Add the error message if present
        HString errorMessage;
        RETURN_IF_FAILED(adaptiveInputElement->get_ErrorMessage(errorMessage.GetAddressOf()));

        if (errorMessage.IsValid())
        {
            ComPtr<ITextBlock> errorMessageTextBlock =
                XamlHelpers::CreateABIClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
            RETURN_IF_FAILED(errorMessageTextBlock->put_Text(errorMessage.Get()));

            // Set the color to Attention color
            ComPtr<IAdaptiveHostConfig> hostConfig;
            RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

            ABI::Windows::UI::Color attentionColor;
            RETURN_IF_FAILED(
                GetColorFromAdaptiveColor(hostConfig.Get(), ForegroundColor_Attention, ContainerStyle_Default, false, false, &attentionColor));

            RETURN_IF_FAILED(errorMessageTextBlock->put_Foreground(XamlHelpers::GetSolidColorBrush(attentionColor).Get()));

            // Format the error message through host config
            RETURN_IF_FAILED(FormatErrorMessageWithHostConfig(renderContext, errorMessageTextBlock.Get()));

            // Error message should begin collapsed and only be show when validated
            ComPtr<IUIElement> errorMessageTextBlockAsUIElement;
            RETURN_IF_FAILED(errorMessageTextBlock.As(&errorMessageTextBlockAsUIElement));

            RETURN_IF_FAILED(errorMessageTextBlockAsUIElement->put_Visibility(Visibility_Collapsed));
            RETURN_IF_FAILED(errorMessageTextBlock->put_TextWrapping(TextWrapping_Wrap));

            RETURN_IF_FAILED(errorMessageTextBlockAsUIElement.CopyTo(errorMessageControl));
        }

        return S_OK;
    }

    HRESULT CreateValidationBorder(_In_ ABI::Windows::UI::Xaml::IUIElement* childElement,
                                   _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                   _COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IBorder** elementWithBorder)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        ABI::Windows::UI::Color attentionColor;
        RETURN_IF_FAILED(
            GetColorFromAdaptiveColor(hostConfig.Get(), ForegroundColor_Attention, ContainerStyle_Default, false, false, &attentionColor));

        // Create a border in the attention color. The thickness is 0 for now so it won't be visibile until validation is run
        ComPtr<IBorder> validationBorder;
        validationBorder = XamlHelpers::CreateABIClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));

        RETURN_IF_FAILED(validationBorder->put_BorderBrush(XamlHelpers::GetSolidColorBrush(attentionColor).Get()));

        RETURN_IF_FAILED(validationBorder->put_Child(childElement));

        RETURN_IF_FAILED(validationBorder.CopyTo(elementWithBorder));
        return S_OK;
    }

    HRESULT HandleLabelAndErrorMessage(_In_ IAdaptiveInputElement* adaptiveInput,
                                       _In_ IAdaptiveRenderContext* renderContext,
                                       _In_ IAdaptiveRenderArgs* renderArgs,
                                       _Out_ IUIElement** inputLayout)
    {
        // Create a new stack panel to add the label and error message
        // The contents from the input panel will be copied to the new panel
        ComPtr<IStackPanel> inputStackPanel =
            XamlHelpers::CreateABIClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));

        ComPtr<IPanel> stackPanelAsPanel;
        RETURN_IF_FAILED(inputStackPanel.As(&stackPanelAsPanel));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        ComPtr<IAdaptiveInputsConfig> inputsConfig;
        RETURN_IF_FAILED(hostConfig->get_Inputs(&inputsConfig));

        // Render the label and add it to the stack panel
        ComPtr<IUIElement> label;
        RETURN_IF_FAILED(XamlHelpers::RenderInputLabel(adaptiveInput, renderContext, renderArgs, &label));
        XamlHelpers::AppendXamlElementToPanel(label.Get(), stackPanelAsPanel.Get());

        // Render the spacing between the label and the input
        if (label != nullptr)
        {
            ComPtr<IAdaptiveLabelConfig> labelConfig;
            RETURN_IF_FAILED(inputsConfig->get_Label(labelConfig.GetAddressOf()));

            ABI::AdaptiveCards::ObjectModel::Uwp::Spacing labelSpacing;
            RETURN_IF_FAILED(labelConfig->get_InputSpacing(&labelSpacing));

            UINT spacing{};
            RETURN_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig.Get(), labelSpacing, &spacing));
            auto separator = XamlHelpers::CreateSeparator(renderContext, spacing, 0, ABI::Windows::UI::Color());

            ComPtr<IPanel> inputPanel;
            RETURN_IF_FAILED(inputStackPanel.As(&inputPanel));
            XamlHelpers::AppendXamlElementToPanel(separator.Get(), inputPanel.Get());
        }

        ComPtr<IUIElement> actualUIElement;

        // Copy the contents into the new panel and get the rendered element to set acessibility properties
        ComPtr<IUIElement> localInputLayout(*inputLayout);
        ComPtr<IPanel> inputPanel;
        if (SUCCEEDED(localInputLayout.As(&inputPanel)))
        {
            ComPtr<IVector<UIElement*>> panelChildren;
            RETURN_IF_FAILED(inputPanel->get_Children(&panelChildren));

            unsigned int childrenCount{};
            RETURN_IF_FAILED(panelChildren->get_Size(&childrenCount));

            // We only copy one element into the input layout, if there's only one element, then we can assume it's our layout
            if (childrenCount == 1)
            {
                ComPtr<IUIElement> onlyElement;
                RETURN_IF_FAILED(panelChildren->GetAt(0, &onlyElement));

                // We enclose multiple items using a border, so we try to check for it
                ComPtr<IBorder> inputBorder;
                if (SUCCEEDED(onlyElement.As(&inputBorder)))
                {
                    RETURN_IF_FAILED(inputBorder->get_Child(actualUIElement.GetAddressOf()));
                }
                else
                {
                    actualUIElement = onlyElement;
                }

                RETURN_IF_FAILED(panelChildren->RemoveAt(0));
                XamlHelpers::AppendXamlElementToPanel(onlyElement.Get(), stackPanelAsPanel.Get());
            }
            else
            {
                for (unsigned int i{}; i < childrenCount; ++i)
                {
                    ComPtr<IUIElement> child;
                    RETURN_IF_FAILED(panelChildren->GetAt(i, &child));
                    RETURN_IF_FAILED(panelChildren->RemoveAt(i));

                    XamlHelpers::AppendXamlElementToPanel(child.Get(), stackPanelAsPanel.Get());
                }
            }
        }
        else
        {
            actualUIElement = localInputLayout;
            XamlHelpers::AppendXamlElementToPanel(localInputLayout.Get(), stackPanelAsPanel.Get());
        }

        // Add the error message if there's validation and one exists
        ComPtr<IUIElement> errorMessageControl;
        XamlHelpers::RenderInputErrorMessage(adaptiveInput, renderContext, &errorMessageControl);
        if (errorMessageControl != nullptr)
        {
            // Render the spacing between the input and the error message
            ComPtr<IAdaptiveErrorMessageConfig> errorMessageConfig;
            RETURN_IF_FAILED(inputsConfig->get_ErrorMessage(errorMessageConfig.GetAddressOf()));

            ABI::AdaptiveCards::ObjectModel::Uwp::Spacing errorSpacing;
            RETURN_IF_FAILED(errorMessageConfig->get_Spacing(&errorSpacing));

            UINT spacing{};
            RETURN_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig.Get(), errorSpacing, &spacing));
            auto separator = XamlHelpers::CreateSeparator(renderContext, spacing, 0, ABI::Windows::UI::Color());

            ComPtr<IAdaptiveInputValue> inputValue;
            RETURN_IF_FAILED(renderContext->GetInputValue(adaptiveInput, inputValue.GetAddressOf()));
            if (inputValue)
            {
                RETURN_IF_FAILED(inputValue->put_ErrorMessage(errorMessageControl.Get()));
            }
            XamlHelpers::AppendXamlElementToPanel(separator.Get(), stackPanelAsPanel.Get());

            // Add the rendered error message
            XamlHelpers::AppendXamlElementToPanel(errorMessageControl.Get(), stackPanelAsPanel.Get());
        }

        // Create an AutomationPropertiesStatics object so we can set the accessibility properties that label allow us to use.
        ComPtr<IAutomationPropertiesStatics> automationPropertiesStatics;
        RETURN_IF_FAILED(
            GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(),
                                 &automationPropertiesStatics));

        // This smart pointer is created as the variable inputUIElementParentContainer may contain the border instead of the
        // actual element if validations are required. If these properties are set into the border then they are not mentioned.

        ComPtr<IDependencyObject> inputUIElementAsDependencyObject;
        RETURN_IF_FAILED(actualUIElement.As(&inputUIElementAsDependencyObject));

        // The AutomationProperties.LabeledBy property allows an input to have more context for people using a screen
        // reader, as it reads the label we rendered previously
        if (label != nullptr)
        {
            RETURN_IF_FAILED(automationPropertiesStatics->SetLabeledBy(inputUIElementAsDependencyObject.Get(), label.Get()));
        }

        RETURN_IF_FAILED(stackPanelAsPanel.CopyTo(inputLayout));

        return S_OK;
    }

    HRESULT HandleInputLayoutAndValidation(IAdaptiveInputElement* adaptiveInput,
                                           IUIElement* inputUIElement,
                                           boolean hasTypeSpecificValidation,
                                           _In_ IAdaptiveRenderContext* renderContext,
                                           IUIElement** inputLayout,
                                           IBorder** validationBorderOut)
    {
        // Create a stack panel for the input and related controls
        ComPtr<IStackPanel> inputStackPanel =
            XamlHelpers::CreateABIClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));

        ComPtr<IPanel> stackPanelAsPanel;
        RETURN_IF_FAILED(inputStackPanel.As(&stackPanelAsPanel));

        // The input may need to go into a border to handle validation before being added to the stack panel.
        // inputUIElementParentContainer represents the current parent container.
        ComPtr<IUIElement> inputUIElementParentContainer = inputUIElement;

        // If there's any validation on this input, and the caller has requested a validation border by passing
        // validationBorderOut, put the input inside a border
        boolean isRequired;
        RETURN_IF_FAILED(adaptiveInput->get_IsRequired(&isRequired));

        boolean hasValidation = (hasTypeSpecificValidation || isRequired);

        if (hasValidation)
        {
            // If we have validation, we should have an error message to display if it fails. If we don't, return a
            // warning to encourage the card author to add one.

            HString errorMessage;
            RETURN_IF_FAILED(adaptiveInput->get_ErrorMessage(errorMessage.GetAddressOf()));

            if (!errorMessage.IsValid())
            {
                RETURN_IF_FAILED(
                    renderContext->AddWarning(ABI::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode::MissingValidationErrorMessage,
                                              HStringReference(L"Inputs with validation should include an errorMessage").Get()));
            }
        }

        ComPtr<IBorder> validationBorder;
        if (validationBorderOut && hasValidation)
        {
            RETURN_IF_FAILED(XamlHelpers::CreateValidationBorder(inputUIElement, renderContext, &validationBorder));
            RETURN_IF_FAILED(validationBorder.As(&inputUIElementParentContainer));
        }

        XamlHelpers::AppendXamlElementToPanel(inputUIElementParentContainer.Get(), stackPanelAsPanel.Get());

        // Different input renderers perform stuff differently
        // Input.Text and Input.Number render the border previously so the object received as parameter may be a border
        // Input.Time and Input.Date let this method render the border for them
        // Input.Toggle
        ComPtr<IUIElement> actualInputUIElement;
        if (validationBorderOut && hasValidation)
        {
            RETURN_IF_FAILED(validationBorder->get_Child(&actualInputUIElement));
        }
        else
        {
            if (hasValidation)
            {
                // This handles the case when the sent item was a Input.Text or Input.Number as we have to get the actual TextBox from the border
                if (SUCCEEDED(inputUIElementParentContainer.As(&validationBorder)))
                {
                    RETURN_IF_FAILED(validationBorder->get_Child(&actualInputUIElement));
                }
                else
                {
                    actualInputUIElement = inputUIElement;
                }
            }
            else
            {
                actualInputUIElement = inputUIElement;
            }
        }

        // Create an AutomationPropertiesStatics object so we can set the accessibility properties that label allow us to use.
        ComPtr<IAutomationPropertiesStatics> automationPropertiesStatics;
        RETURN_IF_FAILED(
            GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(),
                                 &automationPropertiesStatics));

        // This smart pointer is created as the variable inputUIElementParentContainer may contain the border instead of the
        // actual element if validations are required. If these properties are set into the border then they are not mentioned.
        ComPtr<IDependencyObject> inputUIElementAsDependencyObject;
        RETURN_IF_FAILED(actualInputUIElement.As(&inputUIElementAsDependencyObject));

        // The AutomationProperties.IsRequiredForForm property allows an input to provide a little bit of extra information to
        // people using a screen reader by specifying if an input is required. Visually we represent this with a hint.
        RETURN_IF_FAILED(automationPropertiesStatics->SetIsRequiredForForm(inputUIElementAsDependencyObject.Get(), isRequired));

        // In the case of Input.Toggle we have to define the DescribedBy property to put the title in it
        ComPtr<IAdaptiveInputElement> localAdaptiveInput(adaptiveInput);
        ComPtr<IAdaptiveToggleInput> adaptiveToggleInput;
        if (SUCCEEDED(localAdaptiveInput.As(&adaptiveToggleInput)))
        {
            ComPtr<IContentControl> uiInpuElementAsContentControl;
            RETURN_IF_FAILED(actualInputUIElement.As(&uiInpuElementAsContentControl));

            ComPtr<IInspectable> content;
            RETURN_IF_FAILED(uiInpuElementAsContentControl->get_Content(content.GetAddressOf()));

            ComPtr<IDependencyObject> contentAsDependencyObject;
            RETURN_IF_FAILED(content.As(&contentAsDependencyObject));

            ComPtr<IAutomationPropertiesStatics5> automationPropertiesStatics5;
            RETURN_IF_FAILED(automationPropertiesStatics.As(&automationPropertiesStatics5));

            ComPtr<IVector<DependencyObject*>> uiElementDescribers;
            RETURN_IF_FAILED(automationPropertiesStatics5->GetDescribedBy(inputUIElementAsDependencyObject.Get(),
                                                                          uiElementDescribers.GetAddressOf()));

            RETURN_IF_FAILED(uiElementDescribers->Append(contentAsDependencyObject.Get()));
        }

        RETURN_IF_FAILED(stackPanelAsPanel.CopyTo(inputLayout));

        if (validationBorderOut)
        {
            RETURN_IF_FAILED(validationBorder.CopyTo(validationBorderOut));
        }

        return S_OK;
    }

    winrt::Windows::UI::Xaml::UIElement HandleInputLayoutAndValidation(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInputElement adaptiveInput,
                                                                       winrt::Windows::UI::Xaml::UIElement inputUIElement,
                                                                       boolean hasTypeSpecificValidation,
                                                                       winrt::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext renderContext)
    {
        winrt::com_ptr<ABI::Windows::UI::Xaml::IUIElement> abiInputLayout;
        THROW_IF_FAILED(HandleInputLayoutAndValidation(
            adaptiveInput.as<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInputElement>().get(),
            inputUIElement.as<ABI::Windows::UI::Xaml::IUIElement>().get(),
            hasTypeSpecificValidation,
            renderContext.as<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext>().get(),
            abiInputLayout.put(),
            nullptr));

        return abiInputLayout.as<winrt::Windows::UI::Xaml::UIElement>();
    }
}
