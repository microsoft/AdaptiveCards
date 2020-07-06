// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "XamlHelpers.h"

#include "ActionHelpers.h"
#include "ElementTagContent.h"
#include "TileControl.h"
#include "AdaptiveImage.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Automation;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::UI::Xaml::Input;
using namespace ABI::Windows::UI::Xaml::Media;
using namespace ABI::Windows::UI::Xaml::Media::Imaging;

namespace AdaptiveNamespace::XamlHelpers
{
    constexpr PCWSTR c_BackgroundImageOverlayBrushKey = L"AdaptiveCard.BackgroundOverlayBrush";

    ComPtr<IUIElement> CreateSeparator(_In_ IAdaptiveRenderContext* renderContext,
                                       UINT spacing,
                                       UINT separatorThickness,
                                       ABI::Windows::UI::Color separatorColor,
                                       bool isHorizontal)
    {
        ComPtr<IGrid> separator =
            XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
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

    HRESULT XamlHelpers::SetSeparatorVisibility(_In_ IPanel* parentPanel)
    {
        // Iterate over the elements in a container and ensure that the correct separators are marked as visible
        ComPtr<IVector<UIElement*>> children;
        RETURN_IF_FAILED(parentPanel->get_Children(&children));

        bool foundPreviousVisibleElement = false;
        XamlHelpers::IterateOverVector<UIElement, IUIElement>(children.Get(), [&](IUIElement* child) {
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
                        // If the element is collapsed, or if it's the first visible element, collapse the separator
                        // Images are hidden while they are retrieved, we shouldn't hide the separator
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

    HRESULT HandleStylingAndPadding(_In_ IAdaptiveContainerBase* adaptiveContainer,
                                    _In_ IBorder* containerBorder,
                                    _In_ IAdaptiveRenderContext* renderContext,
                                    _In_ IAdaptiveRenderArgs* renderArgs,
                                    _Out_ ABI::AdaptiveNamespace::ContainerStyle* containerStyle)
    {
        ABI::AdaptiveNamespace::ContainerStyle localContainerStyle;
        RETURN_IF_FAILED(adaptiveContainer->get_Style(&localContainerStyle));

        ABI::AdaptiveNamespace::ContainerStyle parentContainerStyle;
        RETURN_IF_FAILED(renderArgs->get_ContainerStyle(&parentContainerStyle));

        bool hasExplicitContainerStyle{true};
        if (localContainerStyle == ABI::AdaptiveNamespace::ContainerStyle::None)
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

        // If container style was explicitly assigned, apply background color and padding
        if (hasExplicitContainerStyle)
        {
            ABI::Windows::UI::Color backgroundColor;
            RETURN_IF_FAILED(GetBackgroundColorFromStyle(localContainerStyle, hostConfig.Get(), &backgroundColor));
            ComPtr<IBrush> backgroundColorBrush = XamlHelpers::GetSolidColorBrush(backgroundColor);
            RETURN_IF_FAILED(containerBorder->put_Background(backgroundColorBrush.Get()));

            // If the container style doesn't match its parent apply padding.
            if (localContainerStyle != parentContainerStyle)
            {
                Thickness paddingThickness = {paddingAsDouble, paddingAsDouble, paddingAsDouble, paddingAsDouble};
                RETURN_IF_FAILED(containerBorder->put_Padding(paddingThickness));
            }
        }

        // Find out which direction(s) we bleed in, and apply a negative margin to cause the
        // container to bleed
        ABI::AdaptiveNamespace::BleedDirection bleedDirection;
        RETURN_IF_FAILED(adaptiveContainer->get_BleedDirection(&bleedDirection));

        Thickness marginThickness = {0};
        if (bleedDirection != ABI::AdaptiveNamespace::BleedDirection::None)
        {
            if ((bleedDirection & ABI::AdaptiveNamespace::BleedDirection::Left) != ABI::AdaptiveNamespace::BleedDirection::None)
            {
                marginThickness.Left = -paddingAsDouble;
            }

            if ((bleedDirection & ABI::AdaptiveNamespace::BleedDirection::Right) != ABI::AdaptiveNamespace::BleedDirection::None)
            {
                marginThickness.Right = -paddingAsDouble;
            }

            if ((bleedDirection & ABI::AdaptiveNamespace::BleedDirection::Up) != ABI::AdaptiveNamespace::BleedDirection::None)
            {
                marginThickness.Top = -paddingAsDouble;
            }

            if ((bleedDirection & ABI::AdaptiveNamespace::BleedDirection::Down) != ABI::AdaptiveNamespace::BleedDirection::None)
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

    void AddInputValueToContext(_In_ IAdaptiveRenderContext* renderContext,
                                _In_ IAdaptiveCardElement* adaptiveCardElement,
                                _In_ IUIElement* inputUiElement)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveInputElement> inputElement;
        THROW_IF_FAILED(cardElement.As(&inputElement));

        ComPtr<InputValue> input;
        THROW_IF_FAILED(MakeAndInitialize<InputValue>(&input, inputElement.Get(), inputUiElement));
        THROW_IF_FAILED(renderContext->AddInputValue(input.Get()));
    }

    bool SupportsInteractivity(_In_ IAdaptiveHostConfig* hostConfig)
    {
        boolean supportsInteractivity;
        THROW_IF_FAILED(hostConfig->get_SupportsInteractivity(&supportsInteractivity));
        return Boolify(supportsInteractivity);
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

        // Valid widths are "auto", "stretch", a pixel width ("50px"), unset, or a value greater than 0 to use as a star value ("2")
        const boolean isValidWidth = isAuto || isStretch || pixelWidth || !adaptiveColumnWidth.IsValid() || (widthAsDouble > 0);

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
        else if (isStretch || !adaptiveColumnWidth.IsValid())
        {
            // If it's visible and stretch is specified, or width is unset, use stretch with default of 1
            columnWidth.GridUnitType = GridUnitType::GridUnitType_Star;
            columnWidth.Value = 1;
        }
        else
        {
            // If it's visible and the user specified a valid non-pixel width, use that as a star width
            columnWidth.GridUnitType = GridUnitType::GridUnitType_Star;
            columnWidth.Value = _wtof(adaptiveColumnWidth.GetRawBuffer(nullptr));
        }

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
        ComPtr<IAdaptiveImage> adaptiveImage;
        HString url;
        THROW_IF_FAILED(MakeAndInitialize<AdaptiveImage>(&adaptiveImage));
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

        ABI::AdaptiveNamespace::BackgroundImageFillMode fillMode;
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
                XamlHelpers::CreateXamlClass<IShape>(HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Rectangle));
            THROW_IF_FAILED(overlayRectangle->put_Fill(backgroundOverlayBrush.Get()));

            ComPtr<IUIElement> overlayRectangleAsUIElement;
            THROW_IF_FAILED(overlayRectangle.As(&overlayRectangleAsUIElement));
            XamlHelpers::AppendXamlElementToPanel(overlayRectangle.Get(), rootPanel);
        }
    }

    HRESULT RenderFallback(_In_ IAdaptiveCardElement* currentElement,
                           _In_ IAdaptiveRenderContext* renderContext,
                           _In_ IAdaptiveRenderArgs* renderArgs,
                           _COM_Outptr_ IUIElement** result)
    {
        ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
        RETURN_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));

        ABI::AdaptiveNamespace::FallbackType elementFallback;
        RETURN_IF_FAILED(currentElement->get_FallbackType(&elementFallback));

        HString elementType;
        RETURN_IF_FAILED(currentElement->get_ElementTypeString(elementType.GetAddressOf()));

        bool fallbackHandled = false;
        ComPtr<IUIElement> fallbackControl;
        switch (elementFallback)
        {
        case ABI::AdaptiveNamespace::FallbackType::Content:
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
            }

            if (hr == E_PERFORM_FALLBACK)
            {
                // The fallback content told us to fallback, make a recursive call to this method
                RETURN_IF_FAILED(RenderFallback(fallbackElement.Get(), renderContext, renderArgs, &fallbackControl));
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
        case ABI::AdaptiveNamespace::FallbackType::Drop:
        {
            // If the fallback is drop, nothing to do but warn
            RETURN_IF_FAILED(XamlHelpers::WarnForFallbackDrop(renderContext, elementType.Get()));
            fallbackHandled = true;
            break;
        }
        case ABI::AdaptiveNamespace::FallbackType::None:
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
                RETURN_IF_FAILED(renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::NoRendererForType,
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
        ABI::AdaptiveNamespace::Spacing elementSpacing;
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

        *needsSeparator = hasSeparator || (elementSpacing != ABI::AdaptiveNamespace::Spacing::None);

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

            ABI::AdaptiveNamespace::HeightType heightType{};
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
        return uiElement->add_Tapped(Callback<ITappedEventHandler>([](IInspectable* /*sender*/, ITappedRoutedEventArgs* args) -> HRESULT {
                                         return args->put_Handled(TRUE);
                                     }).Get(),
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
                maxWidth = min(maxWidth, parentWidth);
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
            RETURN_IF_FAILED(localElement->put_MaxWidth(min(maxWidth, pixelWidth)));
        }
        else
        {
            RETURN_IF_FAILED(localElement->put_MaxHeight(min(maxHeight, pixelHeight)));
            RETURN_IF_FAILED(localElement->put_MaxWidth(min(maxWidth, pixelWidth)));
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
}
