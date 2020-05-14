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
using namespace ABI::Windows::UI::Xaml::Documents;
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
                                           const std::wstring& resourceName,
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

    // TextBlock and RichTextBlock xaml types both support inlines, so we reuse the same method for rendering the " *" hint in both cases
    HRESULT AddRequiredHintInline(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                  IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines)
    {
        ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> xamlInlines(inlines);

        // Create an inline for the *
        ComPtr<IRun> starRun = XamlHelpers::CreateXamlClass<IRun>(HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Run));

        HString starString;
        UTF8ToHString(" *", starString.GetAddressOf());

        RETURN_IF_FAILED(starRun->put_Text(starString.Get()));

        // Set the color to Attention color
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        ABI::Windows::UI::Color attentionColor;
        RETURN_IF_FAILED(
            GetColorFromAdaptiveColor(hostConfig.Get(), ForegroundColor_Attention, ContainerStyle_Default, false, false, &attentionColor));

        ComPtr<ABI::Windows::UI::Xaml::Documents::ITextElement> starRunAsTextElement;
        RETURN_IF_FAILED(starRun.As(&starRunAsTextElement));

        RETURN_IF_FAILED(starRunAsTextElement->put_Foreground(XamlHelpers::GetSolidColorBrush(attentionColor).Get()));

        ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> starRunAsInline;
        RETURN_IF_FAILED(starRun.As(&starRunAsInline));

        RETURN_IF_FAILED(xamlInlines->Append(starRunAsInline.Get()));

        return S_OK;
    }

    HRESULT FormatLabelWithHostConfig(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                      _In_ boolean isRequired,
                                      ABI::Windows::UI::Xaml::Documents::IRun* labelRun)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        ComPtr<IAdaptiveInputsConfig> inputsConfig;
        RETURN_IF_FAILED(hostConfig->get_Inputs(&inputsConfig));

        ComPtr<IAdaptiveInputLabelsConfig> inputLabelsConfig;
        RETURN_IF_FAILED(inputsConfig->get_InputLabels(&inputLabelsConfig));

        ComPtr<IAdaptiveInputLabelConfig> labelConfig;
        if (isRequired)
        {
            inputLabelsConfig->get_RequiredInputs(&labelConfig);
        }
        else
        {
            inputLabelsConfig->get_OptionalInputs(&labelConfig);
        }

        ABI::AdaptiveNamespace::ForegroundColor textColor;
        RETURN_IF_FAILED(labelConfig->get_Color(&textColor));      

        ABI::Windows::UI::Color color;
        RETURN_IF_FAILED(GetColorFromAdaptiveColor(hostConfig.Get(), textColor, ContainerStyle_Default, false, false, &color));

        ComPtr<ABI::Windows::UI::Xaml::Documents::IRun> xamlLabelRun(labelRun);

        ComPtr<ABI::Windows::UI::Xaml::Documents::ITextElement> labelRunAsTextElement;
        RETURN_IF_FAILED(xamlLabelRun.As(&labelRunAsTextElement));

        RETURN_IF_FAILED(labelRunAsTextElement->put_Foreground(XamlHelpers::GetSolidColorBrush(color).Get()));

        ABI::AdaptiveNamespace::TextSize textSize;
        RETURN_IF_FAILED(labelConfig->get_Size(&textSize));

        UINT32 resultSize{};
        GetFontSizeFromFontType(hostConfig.Get(), ABI::AdaptiveNamespace::FontType_Default, textSize, &resultSize);

        RETURN_IF_FAILED(labelRunAsTextElement->put_FontSize(resultSize));

        return S_OK;
    }

    HRESULT RenderInputLabel(_In_ ABI::AdaptiveNamespace::IAdaptiveInputElement* adaptiveInputElement,
                             _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                             _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* /*renderArgs*/,
                             _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** labelControl)
    {
        HString inputLabel;
        RETURN_IF_FAILED(adaptiveInputElement->get_Label(inputLabel.GetAddressOf()));

        if (inputLabel != nullptr)
        {
            // Create a rich text block for the label
            ComPtr<IRichTextBlock> xamlRichTextBlock = XamlHelpers::CreateXamlClass<IRichTextBlock>(
                HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RichTextBlock));

            // Add a paragraph for the inlines
            ComPtr<IVector<Block*>> xamlBlocks;
            RETURN_IF_FAILED(xamlRichTextBlock->get_Blocks(&xamlBlocks));

            ComPtr<IParagraph> xamlParagraph =
                XamlHelpers::CreateXamlClass<IParagraph>(HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Paragraph));

            ComPtr<IBlock> paragraphAsBlock;
            RETURN_IF_FAILED(xamlParagraph.As(&paragraphAsBlock));
            RETURN_IF_FAILED(xamlBlocks->Append(paragraphAsBlock.Get()));

            // Add the Inlines
            ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> xamlInlines;
            RETURN_IF_FAILED(xamlParagraph->get_Inlines(&xamlInlines));

            // First inline is the label from the card
            ComPtr<IRun> labelRun =
                XamlHelpers::CreateXamlClass<IRun>(HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Run));
            RETURN_IF_FAILED(labelRun->put_Text(inputLabel.Get()));

            ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> labelRunAsInline;
            RETURN_IF_FAILED(labelRun.As(&labelRunAsInline));

            RETURN_IF_FAILED(xamlInlines->Append(labelRunAsInline.Get()));

            // If the input is required, add a *
            boolean isRequired;
            adaptiveInputElement->get_IsRequired(&isRequired);

            if (isRequired)
            {
                RETURN_IF_FAILED(AddRequiredHintInline(renderContext, xamlInlines.Get()));
            }

            FormatLabelWithHostConfig(renderContext, isRequired, labelRun.Get());

            RETURN_IF_FAILED(xamlRichTextBlock.CopyTo(labelControl));
        }

        return S_OK;
    }

    // Error messages are formatted for text size and weight
    HRESULT FormatErrorMessageWithHostConfig(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                             ITextBlock* errorMessage)
    {
        ComPtr<ITextBlock> xamlErrorMessage(errorMessage);

        xamlErrorMessage->put_TextWrapping(TextWrapping::TextWrapping_WrapWholeWords);

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(hostConfig.GetAddressOf()));

        ComPtr<IAdaptiveInputsConfig> inputsConfig;
        RETURN_IF_FAILED(hostConfig->get_Inputs(inputsConfig.GetAddressOf()));

        ComPtr<IAdaptiveErrorMessageConfig> errorMessageConfig;
        RETURN_IF_FAILED(inputsConfig->get_ErrorMessage(errorMessageConfig.GetAddressOf()));

        // Set size defined in host config
        ABI::AdaptiveNamespace::TextSize textSize;
        RETURN_IF_FAILED(errorMessageConfig->get_Size(&textSize));

        UINT32 resultSize{};
        RETURN_IF_FAILED(GetFontSizeFromFontType(hostConfig.Get(), ABI::AdaptiveNamespace::FontType_Default, textSize, &resultSize));

        RETURN_IF_FAILED(xamlErrorMessage->put_FontSize(resultSize));

        // Set weight defined in host config
        ABI::AdaptiveNamespace::TextWeight textWeight;
        RETURN_IF_FAILED(errorMessageConfig->get_Weight(&textWeight));

        ABI::Windows::UI::Text::FontWeight resultWeight;
        RETURN_IF_FAILED(GetFontWeightFromStyle(hostConfig.Get(), ABI::AdaptiveNamespace::FontType_Default, textWeight, &resultWeight));

        RETURN_IF_FAILED(xamlErrorMessage->put_FontWeight(resultWeight));

        return S_OK;
    }

    HRESULT RenderInputErrorMessage(_In_ ABI::AdaptiveNamespace::IAdaptiveInputElement* adaptiveInputElement,
                                    _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                    _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** errorMessageControl)
    {
        // Add the error message if present
        HString errorMessage;
        RETURN_IF_FAILED(adaptiveInputElement->get_ErrorMessage(errorMessage.GetAddressOf()));

        if (errorMessage.IsValid())
        {
            ComPtr<ITextBlock> errorMessageTextBlock =
                XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
            errorMessageTextBlock->put_Text(errorMessage.Get());

            // Set the color to Attention color
            ComPtr<IAdaptiveHostConfig> hostConfig;
            RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

            ABI::Windows::UI::Color attentionColor;
            RETURN_IF_FAILED(
                GetColorFromAdaptiveColor(hostConfig.Get(), ForegroundColor_Attention, ContainerStyle_Default, false, false, &attentionColor));

            errorMessageTextBlock->put_Foreground(XamlHelpers::GetSolidColorBrush(attentionColor).Get());

            // Format the error message through host config
            RETURN_IF_FAILED(FormatErrorMessageWithHostConfig(renderContext, errorMessageTextBlock.Get()));

            // Error message should begin collapsed and only be show when validated
            ComPtr<IUIElement> errorMessageTextBlockAsUIElement;
            errorMessageTextBlock.As(&errorMessageTextBlockAsUIElement);

            errorMessageTextBlockAsUIElement->put_Visibility(Visibility_Collapsed);
            errorMessageTextBlockAsUIElement.CopyTo(errorMessageControl);
        }

        return S_OK;
    }

    HRESULT CreateValidationBorder(_In_ ABI::Windows::UI::Xaml::IUIElement* childElement,
                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                   _COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IBorder** elementWithBorder)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        renderContext->get_HostConfig(&hostConfig);

        ABI::Windows::UI::Color attentionColor;
        RETURN_IF_FAILED(
            GetColorFromAdaptiveColor(hostConfig.Get(), ForegroundColor_Attention, ContainerStyle_Default, false, false, &attentionColor));

        // Create a border in the attention color. The thickness is 0 for now so it won't be visibile until validation is run
        ComPtr<IBorder> validationBorder;
        validationBorder = XamlHelpers::CreateXamlClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));

        RETURN_IF_FAILED(validationBorder->put_BorderBrush(XamlHelpers::GetSolidColorBrush(attentionColor).Get()));

        RETURN_IF_FAILED(validationBorder->put_Child(childElement));

        validationBorder.CopyTo(elementWithBorder);
        return S_OK;
    }

    HRESULT HandleInputLayoutAndValidation(IAdaptiveInputElement* adaptiveInput,
                                           IUIElement* inputUIElement,
                                           boolean hasTypeSpecificValidation,
                                           _In_ IAdaptiveRenderContext* renderContext,
                                           _In_ IAdaptiveRenderArgs* renderArgs,
                                           IUIElement** inputLayout,
                                           IBorder** validationBorderOut,
                                           IUIElement** validationErrorOut)
    {
        // Create a stack panel for the input and related controls
        ComPtr<IStackPanel> inputStackPanel =
            XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));

        ComPtr<IPanel> stackPanelAsPanel;
        inputStackPanel.As(&stackPanelAsPanel);

        // Render the label and add it to the stack panel
        // TODO - Ideally the label would use the control's header property if one exists. Unfortunately, that causes
        // the error border to surround the label and the control rather than just the control. This should hopefully be
        // fixable once we're using WinUI 3.0's input validation to handle validation UI.
        ComPtr<IUIElement> label;
        XamlHelpers::RenderInputLabel(adaptiveInput, renderContext, renderArgs, &label);
        XamlHelpers::AppendXamlElementToPanel(label.Get(), stackPanelAsPanel.Get());

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        ComPtr<IAdaptiveInputsConfig> inputsConfig;
        RETURN_IF_FAILED(hostConfig->get_Inputs(&inputsConfig));

        // Render the spacing between the label and the input
        if (label != nullptr)
        {
            ComPtr<IAdaptiveInputLabelsConfig> inputLabelsConfig;
            RETURN_IF_FAILED(inputsConfig->get_InputLabels(inputLabelsConfig.GetAddressOf()));

            ABI::AdaptiveNamespace::Spacing labelSpacing;
            RETURN_IF_FAILED(inputLabelsConfig->get_InputSpacing(&labelSpacing));

            UINT spacing{};
            RETURN_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig.Get(), labelSpacing, &spacing));
            auto separator = XamlHelpers::CreateSeparator(renderContext, spacing, 0, ABI::Windows::UI::Color());

            ComPtr<IPanel> inputPanel;
            inputStackPanel.As(&inputPanel);
            XamlHelpers::AppendXamlElementToPanel(separator.Get(), inputPanel.Get());
        }

        // The input may need to go into a border to handle validation before being added to the stack panel.
        // inputUIElementParentContainer represents the current parent container.
        ComPtr<IUIElement> inputUIElementParentContainer = inputUIElement;
        
        // If there's any validation on this input, and the caller has requested a validation border by passing
        // validationBorderOut, put the input inside a border
        boolean isRequired;
        RETURN_IF_FAILED(adaptiveInput->get_IsRequired(&isRequired));

        boolean hasValidation = (hasTypeSpecificValidation || isRequired);

        ComPtr<IBorder> validationBorder;
        if (validationBorderOut && hasValidation)
        {
            RETURN_IF_FAILED(XamlHelpers::CreateValidationBorder(inputUIElement, renderContext, &validationBorder));

            ABI::AdaptiveNamespace::ValidationBehavior validationBehavior{};
            inputsConfig->get_ValidationBehavior(&validationBehavior);

            RETURN_IF_FAILED(validationBorder.As(&inputUIElementParentContainer));
        }

        XamlHelpers::AppendXamlElementToPanel(inputUIElementParentContainer.Get(), stackPanelAsPanel.Get());

        // Add the error message if there's validation and one exists
        ComPtr<IUIElement> errorMessageControl;
        if (hasValidation)
        {
            RETURN_IF_FAILED(XamlHelpers::RenderInputErrorMessage(adaptiveInput, renderContext, &errorMessageControl));

            if (errorMessageControl != nullptr)
            {
                // Render the spacing between the input and the error message
                ComPtr<IAdaptiveErrorMessageConfig> errorMessageConfig;
                RETURN_IF_FAILED(inputsConfig->get_ErrorMessage(errorMessageConfig.GetAddressOf()));

                ABI::AdaptiveNamespace::Spacing errorSpacing;
                RETURN_IF_FAILED(errorMessageConfig->get_Spacing(&errorSpacing));

                UINT spacing{};
                RETURN_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig.Get(), errorSpacing, &spacing));
                auto separator = XamlHelpers::CreateSeparator(renderContext, spacing, 0, ABI::Windows::UI::Color());

                XamlHelpers::AppendXamlElementToPanel(separator.Get(), stackPanelAsPanel.Get());

                // Add the rendered error message
                XamlHelpers::AppendXamlElementToPanel(errorMessageControl.Get(), stackPanelAsPanel.Get());
            }
        }

        // Different input renderers perform stuff differently
        // Input.Text and Input.Number render the border previously so the object received as parameter may be a border
        // Input.Time and Input.Date let this method render the border for them
        // Input.Toggle 

        ComPtr<IUIElement> actualInputUIElement;

        if (validationBorderOut && hasValidation)
        {
            validationBorder->get_Child(&actualInputUIElement);
        }
        else
        {
            if (hasValidation)
            {
                // This handles the case when the sent item was a Input.Text or Input.Number as we have to get the actual TextBox from the border
                if (SUCCEEDED(inputUIElementParentContainer.As(&validationBorder)))
                {
                    validationBorder->get_Child(&actualInputUIElement);
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

        // The AutomationProperties.LabeledBy property allows an input to have more context for people using a screen
        // reader, as it reads the label we rendered previously
        if (label != nullptr)
        {
            RETURN_IF_FAILED(automationPropertiesStatics->SetLabeledBy(inputUIElementAsDependencyObject.Get(), label.Get()));
        }

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
        RETURN_IF_FAILED(errorMessageControl.CopyTo(validationErrorOut));

        if (validationBorderOut)
        {
            RETURN_IF_FAILED(validationBorder.CopyTo(validationBorderOut));
        }

        return S_OK;
    }
}
