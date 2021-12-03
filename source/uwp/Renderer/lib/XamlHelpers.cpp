// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "XamlHelpers.h"

#include "ActionHelpers.h"
#include "ElementTagContent.h"
#include "TileControl.h"

namespace AdaptiveCards::Rendering::Uwp::XamlHelpers
{
    constexpr PCWSTR c_BackgroundImageOverlayBrushKey = L"AdaptiveCard.BackgroundOverlayBrush";

    rtxaml::UIElement CreateSeparator(rtrender::AdaptiveRenderContext const& renderContext,
                                      uint32_t spacing,
                                      uint32_t separatorThickness,
                                      winrt::Windows::UI::Color const& separatorColor,
                                      bool isHorizontal)
    {
        rtxaml::Controls::Grid separator;
        auto separatorAsFrameworkElement = separator.as<rtxaml::FrameworkElement>();
        auto seperatorPanel = separator.as<rtxaml::Controls::IPanel>();
        seperatorPanel.Background(XamlHelpers::GetSolidColorBrush(separatorColor));

        const uint32_t separatorMarginValue = spacing > separatorThickness ? (spacing - separatorThickness) / 2 : 0;
        rtxaml::Thickness margin{};

        if (isHorizontal)
        {
            margin.Top = margin.Bottom = separatorMarginValue;
            separatorAsFrameworkElement.Height(separatorThickness);
        }
        else
        {
            margin.Left = margin.Right = separatorMarginValue;
            separatorAsFrameworkElement.Width(separatorThickness);
        }

        separatorAsFrameworkElement.Margin(margin);

        XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Separator", separatorAsFrameworkElement);

        return separator;
    }

    void SetStyleFromResourceDictionary(rtrender::AdaptiveRenderContext const& renderContext,
                                        winrt::hstring const& resourceName,
                                        rtxaml::FrameworkElement const& frameworkElement)
    {
        auto resourceDictionary = renderContext.OverrideStyles();
        try
        {
            if (auto style = TryGetResourceFromResourceDictionaries<rtxaml::Style>(resourceDictionary, resourceName))
            {
                frameworkElement.Style(style);
            }
        }
        catch(...)
        {
            // TODO: lookup will throw if it cannot find a resource
        }
       
    }

    void XamlHelpers::SetSeparatorVisibility(rtxaml::Controls::Panel const& parentPanel)
    {
        // Iterate over the elements in a container and ensure that the correct separators are marked as visible

        auto children = parentPanel.Children();

        bool foundPreviousVisibleElement = false;

        for (auto child : children)
        {
            if (const auto childAsFrameworkElement = child.try_as<rtxaml::FrameworkElement>())
            {
                auto tag = childAsFrameworkElement.Tag();
                if (tag)
                {
                    // TODDO: do we wanto to peek_innards to make sure this is our implementation?
                    if (const auto elementTagContent = tag.try_as<rtrender::ElementTagContent>())
                    {
                        auto separator = elementTagContent.Separator();
                        auto visibility = child.Visibility();
                        auto expectedVisibility = elementTagContent.ExpectedVisibility();

                        if (separator)
                        {
                            if (!expectedVisibility || !foundPreviousVisibleElement)
                            {
                                // If the element is collapsed, or if it's the first
                                // visible element, collapse the separator Images are
                                // hidden while they are retrieved, we shouldn't hide
                                // the separator
                                separator.Visibility(rtxaml::Visibility::Collapsed);
                            }
                            else
                            {
                                separator.Visibility(rtxaml::Visibility::Visible);
                            }
                        }

                        foundPreviousVisibleElement |= (visibility == rtxaml::Visibility::Visible);
                    }
                }
            }
        }
    }

    rtom::ContainerStyle HandleStylingAndPadding(rtom::IAdaptiveContainerBase const& adaptiveContainer,
                                                 rtxaml::Controls::Border const& containerBorder,
                                                 rtrender::AdaptiveRenderContext const& renderContext,
                                                 rtrender::AdaptiveRenderArgs renderArgs)
    {
        rtxaml::UIElement elem{nullptr};

        auto localContainerStyle = adaptiveContainer.Style();
        auto parentContainerStyle = renderArgs.ContainerStyle();

        bool hasExplicitContainerStyle{true};
        if (localContainerStyle == rtom::ContainerStyle::None)
        {
            hasExplicitContainerStyle = false;
            localContainerStyle = parentContainerStyle;
        }

        auto hostConfig = renderContext.HostConfig();

        auto spacingConfig = hostConfig.Spacing();

        uint32_t padding = spacingConfig.Padding();
        double paddingAsDouble = (double)padding;

        bool addContainerPadding = renderArgs.AddContainerPadding();

        // If container style was explicitly assigned, apply background color and padding
        if (hasExplicitContainerStyle)
        {
            auto backgroundColor = GetBackgroundColorFromStyle(localContainerStyle, hostConfig);
            // TODO: do we need this getSolidColorBrush helper at all?
            containerBorder.Background(XamlHelpers::GetSolidColorBrush(backgroundColor));

            // If the container style doesn't match its parent apply padding.
            addContainerPadding |= (localContainerStyle != parentContainerStyle);
        }

        if (addContainerPadding)
        {
            containerBorder.Padding({paddingAsDouble, paddingAsDouble, paddingAsDouble, paddingAsDouble});
        }

        // Find out which direction(s) we bleed in, and apply a negative margin to cause the
        // container to bleed
        auto bleedDirection = adaptiveContainer.BleedDirection();

        rtxaml::Thickness marginThickness{0};
        if (bleedDirection != rtom::BleedDirection::None)
        {
            if ((bleedDirection & rtom::BleedDirection::Left) != rtom::BleedDirection::None)
            {
                marginThickness.Left = -paddingAsDouble;
            }

            if ((bleedDirection & rtom::BleedDirection::Right) != rtom::BleedDirection::None)
            {
                marginThickness.Right = -paddingAsDouble;
            }

            if ((bleedDirection & rtom::BleedDirection::Up) != rtom::BleedDirection::None)
            {
                marginThickness.Top = -paddingAsDouble;
            }

            if ((bleedDirection & rtom::BleedDirection::Down) != rtom::BleedDirection::None)
            {
                marginThickness.Bottom = -paddingAsDouble;
            }
            containerBorder.Margin(marginThickness);
        }

        return localContainerStyle;
    }

    bool SupportsInteractivity(rtrender::AdaptiveHostConfig const& hostConfig)
    {
        return hostConfig.SupportsInteractivity();
    }

    rtxaml::GridLength CalculateColumnWidth(bool isVisible, bool isAuto, bool isStretch, bool isUnsetWidth, UINT32 pixelWidth, double ratioWidth)
    {
        const boolean isValidWidth = isAuto || isStretch || pixelWidth || isUnsetWidth || (ratioWidth > 0);

        rtxaml::GridLength columnWidth;
        if (!isVisible || isAuto || !isValidWidth)
        {
            // If the column isn't visible, or is set to "auto" or an invalid value ("-1", "foo"), set it to Auto
            columnWidth.GridUnitType = rtxaml::GridUnitType::Auto;
            columnWidth.Value = 0;
        }
        else if (pixelWidth)
        {
            // If it's visible and pixel width is specified, use pixel width
            columnWidth.GridUnitType = rtxaml::GridUnitType::Pixel;
            columnWidth.Value = pixelWidth;
        }
        else if (isStretch || isUnsetWidth)
        {
            // If it's visible and stretch is specified, or width is unset, use stretch with default of 1
            columnWidth.GridUnitType = rtxaml::GridUnitType::Star;
            columnWidth.Value = 1;
        }
        else
        {
            // If it's visible and the user specified a valid non-pixel width, use that as a star width
            columnWidth.GridUnitType = rtxaml::GridUnitType::Star;
            columnWidth.Value = ratioWidth;
        }

        return columnWidth;
    }

    void HandleColumnWidth(rtom::AdaptiveColumn const& column, bool isVisible, rtxaml::Controls::ColumnDefinition const& columnDefinition)
    {
        auto adaptiveColumnWidth = column.Width();
        const bool isStretch = adaptiveColumnWidth == L"stretch";
        const bool isAuto = adaptiveColumnWidth == L"auto";
        double widthAsDouble = _wtof(adaptiveColumnWidth.data());
        uint32_t pixelWidth = column.PixelWidth();

        columnDefinition.Width(CalculateColumnWidth(isVisible, isAuto, isStretch, adaptiveColumnWidth.empty(), pixelWidth, widthAsDouble));
    }

    void HandleTableColumnWidth(rtom::AdaptiveTableColumnDefinition const& column, rtxaml::Controls::ColumnDefinition const& columnDefinition)
    {
        auto widthRef = column.Width();
        auto pixelWidthRef = column.PixelWidth();

        uint32_t width = GetValueFromRef(widthRef, (uint32_t)0);
        uint32_t pixelWidth = GetValueFromRef(widthRef, (uint32_t)0);

        bool isWidthUnset = (widthRef == nullptr) && (pixelWidthRef == nullptr);

        columnDefinition.Width(CalculateColumnWidth(true, false, false, isWidthUnset, pixelWidth, width));
    }

    void ApplyBackgroundToRoot(rtxaml::Controls::Panel const& rootPanel,
                               rtom::AdaptiveBackgroundImage const& backgroundImage,
                               rtrender::AdaptiveRenderContext const& renderContext,
                               rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        // In order to reuse the image creation code paths, we simply create an adaptive card
        // image element and then build that into xaml and apply to the root.
        // TODO: it might be an overkill to render apdativeImage for background image
        // TODO: we should probably create a routine to do that without adaptive image. Should be simple enough.
        rtom::AdaptiveImage adaptiveImage;
        adaptiveImage.Url(backgroundImage.Url());

        auto elementRenderer = renderContext.ElementRenderers().Get(L"Image");

        if (elementRenderer != nullptr)
        {
            auto background = elementRenderer.Render(adaptiveImage, renderContext, renderArgs);
            if (background == nullptr)
            {
                return;
            }
            else
            {
                auto xamlImage = background.as<rtxaml::Controls::Image>();

                rtom::BackgroundImageFillMode fillMode = backgroundImage.FillMode();

                // Creates the background image for all fill modes
                auto tileControl = winrt::make<rtrender::implementation::TileControl>();

                // Set IsEnabled to false to avoid generating a tab stop for the background image tile control
                tileControl.IsEnabled(false);

                // THROW_IF_FAILED(tileControl->put_BackgroundImage(backgroundImage));
                tileControl.BackgroundImage(backgroundImage);

                // TODO: I don't see this rootelement being used anywhere, a bug?
                // THROW_IF_FAILED(tileControl->put_RootElement(rootElement.Get()));
                // tileControl.RootElement(rootPanel);

                tileControl.LoadImageBrush(background);

                XamlHelpers::AppendXamlElementToPanel(tileControl, rootPanel);

                // The overlay applied to the background image is determined by a resouce, so create
                // the overlay if that resources exists
                auto resourceDictionary = renderContext.OverrideStyles();
                if (const auto backgroundOverlayBrush =
                        XamlHelpers::TryGetResourceFromResourceDictionaries<rtxaml::Media::Brush>(resourceDictionary, c_BackgroundImageOverlayBrushKey))
                {
                    rtxaml::Shapes::Rectangle overlayRectangle;
                    overlayRectangle.Fill(backgroundOverlayBrush);

                    XamlHelpers::AppendXamlElementToPanel(overlayRectangle, rootPanel);
                }
            }
        }
    }

    std::tuple<rtxaml::UIElement, rtom::IAdaptiveCardElement> RenderFallback(rtom::IAdaptiveCardElement const& currentElement,
                                                                             rtrender::AdaptiveRenderContext const& renderContext,
                                                                             rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        // TODO: come back to this routine later
        // TODO: still not sure I'm doing this right...
        auto elementRenderers = renderContext.ElementRenderers();
        auto elementFallback = currentElement.FallbackType();
        winrt::hstring elementType = currentElement.ElementTypeString();

        bool fallbackHandled = false;
        /*winrt::com_ptr<rtxaml::UIElement> fallbackControl;*/
        rtxaml::UIElement fallbackControl{nullptr};
        rtom::IAdaptiveCardElement renderedElement;
        rtxaml::UIElement result{nullptr};

        switch (elementFallback)
        {
        case rtom::FallbackType::Content:
        {
            auto fallbackElement = currentElement.FallbackContent();

            winrt::hstring fallbackElementType = fallbackElement.ElementTypeString();

            WarnForFallbackContentElement(renderContext, elementType, fallbackElementType);

            auto fallbackElementRenderer = elementRenderers.Get(fallbackElementType);

            bool shouldPerformFallBack = true;

            if (fallbackElementRenderer)
            {
                fallbackControl = fallbackElementRenderer.Render(fallbackElement, renderContext, renderArgs);

                // TODO: FIGURE OUT HOW TO DO PROPER LOGIC FOR CALLBACK
                // shouldPerformFallBack = false;
                // TODO: what is the proper logic here?
                renderedElement = fallbackElement;
            }
            // if (hr == E_PERFORM_FALLBACK)
            // TODO: I assume the correct check here is this. We didn't get anything returned from render, so we try to renderfallback
            if (fallbackControl == nullptr)
            {
                // RenderFallback(fallbackElement, renderContext, renderArgs, fallbackControl, renderedElement);
                std::tie(fallbackControl, renderedElement) = RenderFallback(fallbackElement, renderContext, renderArgs);
            }
            else
            {
                // Check the non-fallback return value from the render call
                // RETURN_IF_FAILED(hr);

                // TODO: what do we do here?
                // TODO: return nullptrs??
            }
            fallbackHandled = true;
            break;
        }
        case rtom::FallbackType::Drop:
        {
            XamlHelpers::WarnForFallbackDrop(renderContext, elementType);
            fallbackHandled = true;
            break;
        }
        case rtom::FallbackType::None:
        default:
        {
            break;
        }
        }

        if (fallbackHandled)
        {
            // TODO: refactor
            result = fallbackControl;
        }
        else
        {
            if (!renderArgs.AncestorHasFallback())
            {
                renderContext.AddWarning(rtom::WarningStatusCode::NoRendererForType, L"No Renderer found for type: " + elementType);
            }
            else
            {
                // TODO: return E_perform_callback. What do we do here?
            }
        }
        return std::tuple(result, renderedElement);
    }

    bool NeedsSeparator(rtom::IAdaptiveCardElement const& cardElement)
    {
        auto elementSpacing = cardElement.Spacing();
        auto hasSeparator = cardElement.Separator();

        return hasSeparator || (elementSpacing != rtom::Spacing::None);
    }

    void AddRenderedControl(rtxaml::UIElement const& newControl,
                            rtom::IAdaptiveCardElement const& element,
                            rtxaml::Controls::Panel const& parentPanel,
                            rtxaml::UIElement const& separator,
                            rtxaml::Controls::ColumnDefinition const& columnDefinition,
                            std::function<void(rtxaml::UIElement const& child)> childCreatedCallback)
    {
        if (newControl != nullptr)
        {
            bool isVisible = element.IsVisible();

            if (!isVisible)
            {
                newControl.Visibility(rtxaml::Visibility::Collapsed);
            }

            auto newControlAsFrameworkElement = newControl.as<rtxaml::FrameworkElement>();

            winrt::hstring id = element.Id();
            // RETURN_IF_FAILED(element->get_Id(id.GetAddressOf()));

            // TODO: what does it mean for hstring to be valid? to have c_str? to not be empty? both?
            // TODO: can we do if (const auto id = element.Id()) instead of assigning and checking for empty in different places?
            if (!id.empty())
            {
                newControlAsFrameworkElement.Name(id);
            }

            auto heightType = element.Height();

            auto tagContent = winrt::make<rtrender::implementation::ElementTagContent>(
                element, parentPanel, separator, columnDefinition, isVisible, heightType == rtom::HeightType::Stretch);
            newControlAsFrameworkElement.Tag(tagContent);

            XamlHelpers::AppendXamlElementToPanel(newControl, parentPanel, heightType);

            childCreatedCallback(newControl);
        }
    }

    void AddHandledTappedEvent(winrt::Windows::UI::Xaml::UIElement const& uiElement)
    {
        // TODO: is ! enough? no need for == nullptr?
        if (!uiElement)
        {
            return;
        }
        // TODO: Don't we need a revoker?
        // TODO: no need to save a token, right?
        uiElement.Tapped([](winrt::Windows::Foundation::IInspectable const&, rtxaml::Input::TappedRoutedEventArgs const& args)
                         { args.Handled(true); });
    }

    void SetAutoImageSize(winrt::Windows::UI::Xaml::FrameworkElement const& imageControl,
                          winrt::Windows::Foundation::IInspectable const& parentElement,
                          winrt::Windows::UI::Xaml::Media::Imaging::BitmapSource const& imageSource,
                          bool setVisible)
    {
        int32_t pixelHeight = imageSource.PixelHeight();
        int32_t pixelWidth = imageSource.PixelWidth();

        double maxHeight = imageControl.MaxHeight();
        double maxWidth = imageControl.MaxWidth();

        if (const auto parentAsColumnDefinition = parentElement.try_as<rtxaml::Controls::ColumnDefinition>())
        {
            double parentWidth = parentAsColumnDefinition.ActualWidth();
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
        if (const auto localElementAsEllipse = imageControl.try_as<rtxaml::Shapes::Ellipse>())
        {
            // don't need to set both width and height when image size is auto since
            // we want a circle as shape.
            // max value for width should be set since adaptive cards is constrained horizontally
            imageControl.MaxWidth(std::min(maxWidth, static_cast<double>(pixelWidth)));
        }
        else
        {
            imageControl.MaxHeight(std::min(maxHeight, static_cast<double>(pixelHeight)));
            imageControl.MaxWidth(std::min(maxWidth, static_cast<double>(pixelWidth)));
        }

        if (setVisible)
        {
            imageControl.Visibility(rtxaml::Visibility::Visible);
        }
    }

    rtxaml::UIElement AddSeparatorIfNeeded(int& currentElement,
                                           rtom::IAdaptiveCardElement const& element,
                                           rtrender::AdaptiveHostConfig const& hostConfig,
                                           rtrender::AdaptiveRenderContext const& renderContext,
                                           winrt::Windows::UI::Xaml::Controls::Panel const& parentPanel)
    {
        // First element does not need a separator added
        if (currentElement++ > 0)
        {
            if (NeedsSeparator(element))
            {
                auto separatorConfig = hostConfig.Separator();
                auto separatorColor = separatorConfig.LineColor();
                auto separatorThickness = separatorConfig.LineThickness();
                uint32_t spacing = GetSpacingSizeFromSpacing(hostConfig, element.Spacing());
                auto separator = XamlHelpers::CreateSeparator(renderContext, spacing, separatorThickness, separatorColor);
                XamlHelpers::AppendXamlElementToPanel(separator, parentPanel);
                return separator;
            }
        }
        return nullptr;
    }

    void ApplyMarginToXamlElement(winrt::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig const& hostConfig,
                                  winrt::Windows::UI::Xaml::IFrameworkElement const& element)
    {
        auto spacingConfig = hostConfig.Spacing();
        uint32_t padding = spacingConfig.Padding();

        element.Margin({(double)padding, (double)padding, (double)padding, (double)padding});
    }

    void FormatLabelRunWithHostConfig(rtrender::AdaptiveHostConfig const& hostConfig,
                                      rtrender::AdaptiveInputLabelConfig const& inputLabelConfig,
                                      bool isHint,
                                      rtxaml::Documents::Run const& labelRun)
    {
        // If we're formatting a hint then use attention color
        rtom::ForegroundColor textColor = isHint ? rtom::ForegroundColor::Attention : inputLabelConfig.Color();

        auto color = GetColorFromAdaptiveColor(hostConfig, textColor, rtom::ContainerStyle::Default, false, false);

        labelRun.Foreground(XamlHelpers::GetSolidColorBrush(color));

        rtom::TextSize textSize = inputLabelConfig.Size();

        uint32_t resultSize = GetFontSizeFromFontType(hostConfig, rtom::FontType::Default, textSize);

        labelRun.FontSize(resultSize);
    }

    void AddRequiredHintInline(rtrender::AdaptiveHostConfig const& hostConfig,
                               rtrender::AdaptiveInputLabelConfig const& inputLabelConfig,
                               winrt::Windows::Foundation::Collections::IVector<rtxaml::Documents::Inline> const& inlines)
    {
        // Create an inline for the suffix
        rtxaml::Documents::Run hintRun{};

        winrt::hstring suffix = inputLabelConfig.Suffix();
        // If no suffix was defined, use * as default

        // TODO: is this correct?
        if (suffix.empty())
        {
            suffix = UTF8ToHString(" *");
        }

        hintRun.Text(suffix);

        FormatLabelRunWithHostConfig(hostConfig, inputLabelConfig, true /*isHint*/, hintRun);

        inlines.Append(hintRun);
    }

    rtxaml::UIElement RenderInputLabel(rtom::IAdaptiveInputElement const& adaptiveInputElement,
                                       rtrender::AdaptiveRenderContext const& renderContext,
                                       rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        winrt::hstring inputLabel = adaptiveInputElement.Label();
        // Retrieve if the input is required so we can file a warning if the label is empty
        bool isRequired = adaptiveInputElement.IsRequired();

        // TOOD: is this correct way instead of != nullptr? should I check for data?
        if (!inputLabel.empty())
        {
            // Create a rich text block for the label
            rtxaml::Controls::RichTextBlock xamlRichTextBlock{};

            // Add a paragraph for the inlines
            auto xamlBlocks = xamlRichTextBlock.Blocks();

            rtxaml::Documents::Paragraph xamlParagraph{};

            xamlBlocks.Append(xamlParagraph);

            // Add the inlines
            auto xamlInlines = xamlParagraph.Inlines();

            // First inline is the label from the card
            rtxaml::Documents::Run labelRun{};
            labelRun.Text(inputLabel);

            xamlInlines.Append(labelRun);

            // Get the label config depending if the input is required
            auto hostConfig = renderContext.HostConfig();
            auto inputsConfig = hostConfig.Inputs();
            auto labelConfig = inputsConfig.Label();
            rtrender::AdaptiveInputLabelConfig inputLabelConfig =
                isRequired ? labelConfig.RequiredInputs() : labelConfig.OptionalInputs();

            if (isRequired)
            {
                AddRequiredHintInline(hostConfig, inputLabelConfig, xamlInlines);
            }
            FormatLabelRunWithHostConfig(hostConfig, inputLabelConfig, false /*isHint*/, labelRun);

            xamlRichTextBlock.TextWrapping(rtxaml::TextWrapping::Wrap);
            return xamlRichTextBlock;
        }
        else if (isRequired)
        {
            renderContext.AddWarning(rtom::WarningStatusCode::EmptyLabelInRequiredInput,
                                     L"Input is required but there's no label for required hint rendering");
        }
        // TODO: is this correct here?
        return nullptr;
    }

    // Error messages are formatted for text size and weight
    void FormatErrorMessageWithHostConfig(rtrender::AdaptiveRenderContext const& renderContext,
                                          rtxaml::Controls::TextBlock const& errorMessage)
    {
        auto hostConfig = renderContext.HostConfig();
        auto inputsConfig = hostConfig.Inputs();
        auto errorMessageConfig = inputsConfig.ErrorMessage();

        // Set size defined in host config
        rtom::TextSize textSize = errorMessageConfig.Size();
        uint32_t resultSize = GetFontSizeFromFontType(hostConfig, rtom::FontType::Default, textSize);
        errorMessage.FontSize(resultSize);

        // Set weight defined in host config
        rtom::TextWeight textWeight = errorMessageConfig.Weight();
        auto resultWeight = GetFontWeightFromStyle(hostConfig, rtom::FontType::Default, textWeight);
        errorMessage.FontWeight(resultWeight);
    }

    rtxaml::UIElement RenderInputErrorMessage(rtom::IAdaptiveInputElement const& adaptiveInputElement,
                                              rtrender::AdaptiveRenderContext const& renderContext)
    {
        // Add the error message if present
        winrt::hstring errorMessage = adaptiveInputElement.ErrorMessage();

        // TODO: is this correct in this scenario instead of .IsValid()?
        if (!errorMessage.empty())
        {
            rtxaml::Controls::TextBlock errorMessageTextBlock{};
            errorMessageTextBlock.Text(errorMessage);

            // Set the color to Attention color
            auto hostConfig = renderContext.HostConfig();

            auto attentionColor =
                GetColorFromAdaptiveColor(hostConfig, rtom::ForegroundColor::Attention, rtom::ContainerStyle::Default, false, false);

            errorMessageTextBlock.Foreground(XamlHelpers::GetSolidColorBrush(attentionColor));

            // Format the error message through host config
            FormatErrorMessageWithHostConfig(renderContext, errorMessageTextBlock);

            // Error message should begin collapsed and only be show when validated
            errorMessageTextBlock.Visibility(rtxaml::Visibility::Collapsed);
            errorMessageTextBlock.TextWrapping(rtxaml::TextWrapping::Wrap);
            return errorMessageTextBlock;
        }
        return nullptr;
    }

    rtxaml::Controls::Border XamlHelpers::CreateValidationBorder(rtxaml::UIElement const& childElement,
                                                                 rtrender::AdaptiveRenderContext const& renderContext)
    {
        auto hostConfig = renderContext.HostConfig();

        auto attentionColor =
            GetColorFromAdaptiveColor(hostConfig, rtom::ForegroundColor::Attention, rtom::ContainerStyle::Default, false, false);

        // Create a border in the attention color. The thickness is 0 for now so it won't be visibile until validation is run
        rtxaml::Controls::Border validationBorder{};
        validationBorder.BorderBrush(XamlHelpers::GetSolidColorBrush(attentionColor));
        validationBorder.Child(childElement);

        return validationBorder;
    }

    rtxaml::UIElement HandleLabelAndErrorMessage(rtom::IAdaptiveInputElement const& adaptiveInput,
                                                 rtrender::AdaptiveRenderContext const& renderContext,
                                                 rtrender::AdaptiveRenderArgs const& renderArgs,
                                                 rtxaml::UIElement const& inputLayout)
    {
        // Create a new stack panel to add the label and error message
        // The contents from the input panel will be copied to the new panel
        rtxaml::Controls::StackPanel inputStackPanel{};

        auto hostConfig = renderContext.HostConfig();
        // TOOD: rename Inputs to something more meaningful
        auto inputsConfig = hostConfig.Inputs();

        // Render the label and add it to the stack panel
        auto label = XamlHelpers::RenderInputLabel(adaptiveInput, renderContext, renderArgs);
        XamlHelpers::AppendXamlElementToPanel(label, inputStackPanel);

        if (label != nullptr)
        {
            auto labelConfig = inputsConfig.Label();
            rtom::Spacing labelSpacing = labelConfig.InputSpacing();

            uint32_t spacing = GetSpacingSizeFromSpacing(hostConfig, labelSpacing);

            auto separator = XamlHelpers::CreateSeparator(renderContext, spacing, 0, winrt::Windows::UI::Color{});
            XamlHelpers::AppendXamlElementToPanel(separator, inputStackPanel);
        }

        rtxaml::UIElement actualUIElement{nullptr};

        // Copy the contents into the new panel and get the rendered element to set acessibility properties
        if (const auto inputPanel = inputLayout.try_as<rtxaml::Controls::Panel>())
        {
            auto panelChildren = inputPanel.Children();
            uint32_t childrenCount = panelChildren.Size();

            // We only copy one element into the input layout, if there's only one element, then we can assume it's our layout
            if (childrenCount == 1)
            {
                auto onlyElement = panelChildren.GetAt(0);
                // We enclose multiple items using a border, so we try to check for it
                if (const auto inputBorder = onlyElement.try_as<rtxaml::Controls::Border>())
                {
                    actualUIElement = inputBorder.Child();
                }
                else
                {
                    actualUIElement = onlyElement;
                }
                panelChildren.RemoveAt(0);
                XamlHelpers::AppendXamlElementToPanel(onlyElement, inputStackPanel);
            }
            else
            {
                for (auto child : panelChildren)
                {
                    XamlHelpers::AppendXamlElementToPanel(child, inputStackPanel);
                }
                panelChildren.Clear();
            }
        }
        else
        {
            actualUIElement = inputLayout;
            XamlHelpers::AppendXamlElementToPanel(inputLayout, inputStackPanel);
        }

        // Add the error message if there's validation and one exists
        auto errorMessageControl = XamlHelpers::RenderInputErrorMessage(adaptiveInput, renderContext);

        if (errorMessageControl != nullptr)
        {
            // Render the spacing between the input and the error message
            auto errorMessageConfig = inputsConfig.ErrorMessage();

            rtom::Spacing errorSpacing = errorMessageConfig.Spacing();

            uint32_t spacing = GetSpacingSizeFromSpacing(hostConfig, errorSpacing);

            auto separator = XamlHelpers::CreateSeparator(renderContext, spacing, 0, winrt::Windows::UI::Color{});
            auto inputValue = renderContext.GetInputValue(adaptiveInput);

            if (inputValue != nullptr)
            {
                inputValue.ErrorMessage(errorMessageControl);
            }

            XamlHelpers::AppendXamlElementToPanel(separator, inputStackPanel);

            // Add the rendered error message
            XamlHelpers::AppendXamlElementToPanel(errorMessageControl, inputStackPanel);
        }

        // TODO: do I need this?
        // This smart pointer is created as the variable inputUIElementParentContainer may contain the border instead of the
        // actual element if validations are required. If these properties are set into the border then they are not mentioned.

        /*  ComPtr<IDependencyObject> inputUIElementAsDependencyObject;
          RETURN_IF_FAILED(actualUIElement.As(&inputUIElementAsDependencyObject));*/

        if (label != nullptr)
        {
            rtxaml::Automation::AutomationProperties::SetLabeledBy(actualUIElement, label);
        }

        return inputStackPanel;
    }

    std::tuple<rtxaml::UIElement, rtxaml::Controls::Border>
    XamlHelpers::HandleInputLayoutAndValidation(rtom::IAdaptiveInputElement const& adaptiveInput,
                                                rtxaml::UIElement const& inputUIElement,
                                                bool hasTypeSpecificValidation,
                                                rtrender::AdaptiveRenderContext const& renderContext,
                                                bool ifValidationBorderIsNeeded)
    {
        // TODO: Make sure this function works properly
        rtxaml::Controls::StackPanel inputStackPanel{};

        // The input may need to go into a border to handle validation before being added to the stack panel.
        // inputUIElementParentContainer represents the current parent container.
        /*ComPtr<IUIElement> inputUIElementParentContainer = inputUIElement;*/
        // TODO: I do not need this right?
        auto inputUIElementParentContainer = inputUIElement;

        // If there's any validation on this input, and the caller has requested a validation border by passing
        // validationBorderOut, put the input inside a border
        auto isRequired = adaptiveInput.IsRequired();

        auto hasValidation = (hasTypeSpecificValidation || isRequired);

        if (hasValidation)
        {
            // If we have validation, we should have an error message to display if it fails. If we don't, return a
            // warning to encourage the card author to add one.

            winrt::hstring errorMessage = adaptiveInput.ErrorMessage();

            // TODO: what if the user just wants an empty error message? do we allow that?
            if (errorMessage.empty())
            {
                renderContext.AddWarning(rtom::WarningStatusCode::MissingValidationErrorMessage,
                                         L"Inputs with validation should include an errorMessage");
            }
        }

        rtxaml::Controls::Border validationBorder{nullptr};
        if (hasValidation && ifValidationBorderIsNeeded)
        {
            validationBorder = XamlHelpers::CreateValidationBorder(inputUIElement, renderContext);
            inputUIElementParentContainer = validationBorder;
        }

        XamlHelpers::AppendXamlElementToPanel(inputUIElementParentContainer, inputStackPanel);

        // Different input renderers perform stuff differently
        // Input.Text and Input.Number render the border previously so the object received as parameter may be a border
        // Input.Time and Input.Date let this method render the border for them
        // Input.Toggle
        rtxaml::UIElement actualInputUIElement{nullptr};
        // TODO: revisit this
        // if (validationBorderOut && hasValidation)
        if (hasValidation && ifValidationBorderIsNeeded)
        {
            // RETURN_IF_FAILED(validationBorder->get_Child(&actualInputUIElement));
            actualInputUIElement = validationBorder.Child();
        }
        else
        {
            if (hasValidation)
            {
                // This handles the case when the sent item was a Input.Text or Input.Number as we have to get the actual TextBox from the border
                // TODO: no need to save inputUIElementParentContainre in validationBorder because we're not going to return it anyway
                /* if (SUCCEEDED(inputUIElementParentContainer.As(&validationBorder)))
                 {
                     RETURN_IF_FAILED(validationBorder->get_Child(&actualInputUIElement));
                 }*/
                if (const auto containerAsBorder = inputUIElementParentContainer.try_as<rtxaml::Controls::Border>())
                {
                    actualInputUIElement = containerAsBorder.Child();
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

        // TODO: do I need this
        // This smart pointer is created as the variable inputUIElementParentContainer may contain the border instead of the
        // actual element if validations are required. If these properties are set into the border then they are not mentioned.
        /*ComPtr<IDependencyObject> inputUIElementAsDependencyObject;
        RETURN_IF_FAILED(actualInputUIElement.As(&inputUIElementAsDependencyObject));*/

        // The AutomationProperties.IsRequiredForForm property allows an input to provide a little bit of extra information to
        // people using a screen reader by specifying if an input is required. Visually we represent this with a hint.
        rtxaml::Automation::AutomationProperties::SetIsRequiredForForm(actualInputUIElement, isRequired);

        // In the case of Input.Toggle we have to define the DescribedBy property to put the title in it
        if (const auto adaptiveToggleInput = adaptiveInput.try_as<rtom::AdaptiveToggleInput>())
        {
            if (const auto uiInputElementAsContentControl = actualInputUIElement.try_as<rtxaml::Controls::ContentControl>())
            {
                if (const auto content = uiInputElementAsContentControl.Content())
                {
                    if (const auto contentAsDependencyObject = content.try_as<rtxaml::DependencyObject>())
                    {
                        auto uiElementDescribers = rtxaml::Automation::AutomationProperties::GetDescribedBy(actualInputUIElement);
                        uiElementDescribers.Append(contentAsDependencyObject);
                    }
                }
            }
        }

        return {inputStackPanel, validationBorder};
    }
}
