// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "ElementTagContent.h"
#include "TileControl.h"
#include "AdaptiveBase64Util.h"
#include "WholeItemsPanel.h"
#include "Util.h"

namespace AdaptiveCards::Rendering::Xaml_Rendering::XamlHelpers
{
    constexpr PCWSTR c_BackgroundImageOverlayBrushKey = L"AdaptiveCard.BackgroundOverlayBrush";

    winrt::UIElement CreateSeparator(winrt::AdaptiveRenderContext const& renderContext,
                                     uint32_t spacing,
                                     uint32_t separatorThickness,
                                     winrt::Windows::UI::Color const& separatorColor,
                                     bool isHorizontal)
    {
        winrt::Grid separator;
        separator.Background(winrt::SolidColorBrush{separatorColor});

        const uint32_t separatorMarginValue = spacing > separatorThickness ? (spacing - separatorThickness) / 2 : 0;
        winrt::Thickness margin{};

        if (isHorizontal)
        {
            margin.Top = margin.Bottom = separatorMarginValue;
            separator.Height(separatorThickness);
        }
        else
        {
            margin.Left = margin.Right = separatorMarginValue;
            separator.Width(separatorThickness);
        }

        separator.Margin(margin);

        XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Separator", separator);

        return separator;
    }

    void SetStyleFromResourceDictionary(winrt::AdaptiveRenderContext const& renderContext,
                                        winrt::hstring const& resourceName,
                                        winrt::FrameworkElement const& frameworkElement)
    {
        auto resourceDictionary = renderContext.OverrideStyles();

        if (auto style = TryGetResourceFromResourceDictionaries(resourceDictionary, resourceName).try_as<winrt::Style>())
        {
            frameworkElement.Style(style);
        }
    }
    void XamlHelpers::SetSeparatorVisibility(winrt::Panel const& parentPanel)
    {
        // Iterate over the elements in a container and ensure that the correct separators are marked as visible

        auto children = parentPanel.Children();

        bool foundPreviousVisibleElement = false;

        for (auto child : children)
        {
            if (const auto childAsFrameworkElement = child.try_as<winrt::FrameworkElement>())
            {
                if (const auto tag = childAsFrameworkElement.Tag())
                {
                    if (const auto elementTagContent = tag.try_as<winrt::ElementTagContent>())
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
                                separator.Visibility(winrt::Visibility::Collapsed);
                            }
                            else
                            {
                                separator.Visibility(winrt::Visibility::Visible);
                            }
                        }

                        foundPreviousVisibleElement |= (visibility == winrt::Visibility::Visible);
                    }
                }
            }
        }
    }

    winrt::ContainerStyle HandleStylingAndPadding(winrt::IAdaptiveContainerBase const& adaptiveContainer,
                                                  winrt::Border const& containerBorder,
                                                  winrt::AdaptiveRenderContext const& renderContext,
                                                  winrt::AdaptiveRenderArgs renderArgs)
    {
        winrt::UIElement elem{nullptr};

        auto localContainerStyle = adaptiveContainer.Style();
        auto parentContainerStyle = renderArgs.ContainerStyle();

        bool hasExplicitContainerStyle{true};
        if (localContainerStyle == winrt::ContainerStyle::None)
        {
            hasExplicitContainerStyle = false;
            localContainerStyle = parentContainerStyle;
        }

        auto hostConfig = renderContext.HostConfig();

        auto spacingConfig = hostConfig.Spacing();

        uint32_t padding = spacingConfig.Padding();
        double paddingAsDouble = static_cast<double>(padding);

        bool addContainerPadding = renderArgs.AddContainerPadding();

        // If container style was explicitly assigned, apply background color and padding
        if (hasExplicitContainerStyle)
        {
            auto backgroundColor = GetBackgroundColorFromStyle(localContainerStyle, hostConfig);
            containerBorder.Background(winrt::SolidColorBrush{backgroundColor});

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

        winrt::Thickness marginThickness{0};
        if (bleedDirection != winrt::BleedDirection::None)
        {
            if ((bleedDirection & winrt::BleedDirection::Left) != winrt::BleedDirection::None)
            {
                marginThickness.Left = -paddingAsDouble;
            }

            if ((bleedDirection & winrt::BleedDirection::Right) != winrt::BleedDirection::None)
            {
                marginThickness.Right = -paddingAsDouble;
            }

            if ((bleedDirection & winrt::BleedDirection::Up) != winrt::BleedDirection::None)
            {
                marginThickness.Top = -paddingAsDouble;
            }

            if ((bleedDirection & winrt::BleedDirection::Down) != winrt::BleedDirection::None)
            {
                marginThickness.Bottom = -paddingAsDouble;
            }
            containerBorder.Margin(marginThickness);
        }

        return localContainerStyle;
    }

    bool SupportsInteractivity(winrt::AdaptiveHostConfig const& hostConfig)
    {
        return hostConfig.SupportsInteractivity();
    }

    winrt::GridLength CalculateColumnWidth(bool isVisible, bool isAuto, bool isStretch, bool isUnsetWidth, UINT32 pixelWidth, double ratioWidth)
    {
        const boolean isValidWidth = isAuto || isStretch || pixelWidth || isUnsetWidth || (ratioWidth > 0);

        winrt::GridLength columnWidth;
        if (!isVisible || isAuto || !isValidWidth)
        {
            // If the column isn't visible, or is set to "auto" or an invalid value ("-1", "foo"), set it to Auto
            columnWidth.GridUnitType = winrt::GridUnitType::Auto;
            columnWidth.Value = 0;
        }
        else if (pixelWidth)
        {
            // If it's visible and pixel width is specified, use pixel width
            columnWidth.GridUnitType = winrt::GridUnitType::Pixel;
            columnWidth.Value = pixelWidth;
        }
        else if (isStretch || isUnsetWidth)
        {
            // If it's visible and stretch is specified, or width is unset, use stretch with default of 1
            columnWidth.GridUnitType = winrt::GridUnitType::Star;
            columnWidth.Value = 1;
        }
        else
        {
            // If it's visible and the user specified a valid non-pixel width, use that as a star width
            columnWidth.GridUnitType = winrt::GridUnitType::Star;
            columnWidth.Value = ratioWidth;
        }

        return columnWidth;
    }

    void HandleColumnWidth(winrt::AdaptiveColumn const& column, bool isVisible, winrt::ColumnDefinition const& columnDefinition)
    {
        auto adaptiveColumnWidth = column.Width();
        const bool isStretch = adaptiveColumnWidth == L"stretch";
        const bool isAuto = adaptiveColumnWidth == L"auto";
        double widthAsDouble = _wtof(adaptiveColumnWidth.data());
        uint32_t pixelWidth = column.PixelWidth();

        columnDefinition.Width(CalculateColumnWidth(isVisible, isAuto, isStretch, adaptiveColumnWidth.empty(), pixelWidth, widthAsDouble));
    }

    void HandleTableColumnWidth(winrt::AdaptiveTableColumnDefinition const& column, winrt::ColumnDefinition const& columnDefinition)
    {
        auto widthRef = column.Width();
        auto pixelWidthRef = column.PixelWidth();

        uint32_t width = GetValueFromRef(widthRef, (uint32_t)0);
        uint32_t pixelWidth = GetValueFromRef(pixelWidthRef, (uint32_t)0);

        bool isWidthUnset = (widthRef == nullptr) && (pixelWidthRef == nullptr);

        columnDefinition.Width(CalculateColumnWidth(true, false, false, isWidthUnset, pixelWidth, width));
    }

    winrt::TextBlock CreateTextBlockWithContent(winrt::hstring const& contentString, bool wrap)
    {
        winrt::TextBlock content{};
        content.Text(contentString);
        if (wrap)
        {
            content.TextWrapping(winrt::TextWrapping::WrapWholeWords);
        }

        return content;
    }

    winrt::Image CreateBackgroundImage(winrt::AdaptiveRenderContext const& renderContext,
                                       winrt::TileControl const& tileControl,
                                       bool IsSvg,
                                       winrt::Uri imageUrl)
    {
        try
        {
            if (IsSvg)
            {
                winrt::SvgImageSource svgImageSource{};

                ConfigureSvgImageSourceAsync(imageUrl, svgImageSource, tileControl);

                winrt::Image backgroundImage;
                backgroundImage.Source(svgImageSource);

                return backgroundImage;
			}
            else
            {
                if (imageUrl.SchemeName() == L"data")
                {
                    return RenderImageFromDataUri(imageUrl);
                }
                else
                {
                    winrt::BitmapImage bitmapImage{};
                    bitmapImage.UriSource(imageUrl);

                    winrt::Image backgroundImage;
                    backgroundImage.Source(bitmapImage);

                    return backgroundImage;
                }
            }
        }
        catch (winrt::hresult_error const& ex)
        {
            renderContext.AddWarning(winrt::WarningStatusCode::CustomWarning, ex.message() + L" Skipping rendering of background image.");
            return nullptr;
        }
    }

    winrt::fire_and_forget ConfigureSvgImageSourceAsync(winrt::Uri imageUrl,
                                                        winrt::SvgImageSource svgImageSource,
                                                        winrt::TileControl tileControl)
    {
        auto weakImageSource{winrt::make_weak(svgImageSource)};
        auto weakTileControl{winrt::make_weak(tileControl)};

        if (imageUrl.SchemeName() == L"data")
        {
            auto imagePath = HStringToUTF8(imageUrl.Path());
            auto foundBase64 = imagePath.find("base64");
            winrt::DataWriter dataWriter{winrt::InMemoryRandomAccessStream{}};

            if (foundBase64 != std::string::npos)
            {
                // Decode base 64 string
                std::string data = AdaptiveBase64Util::ExtractDataFromUri(imagePath);
                std::vector<char> decodedData = AdaptiveBase64Util::Decode(data);
                dataWriter.WriteBytes(std::vector<byte>{decodedData.begin(), decodedData.end()});
            }
            else
            {
                std::string data = ExtractSvgDataFromUri(imageUrl);
                dataWriter.WriteBytes(std::vector<byte>{data.begin(), data.end()});
            }
                
            co_await dataWriter.StoreAsync();
            if (auto strongImageSource = weakImageSource.get())
            {
                auto stream = dataWriter.DetachStream().try_as<winrt::InMemoryRandomAccessStream>();
                stream.Seek(0);
                auto sizeParseOp{ParseSizeOfSVGImageFromStreamAsync(stream)};          
                co_await wil::resume_foreground(GetDispatcher(strongImageSource));
                auto size = co_await sizeParseOp;
                strongImageSource.RasterizePixelHeight(size.Height);
                strongImageSource.RasterizePixelWidth(size.Width);
                co_await strongImageSource.SetSourceAsync(stream); 
                winrt::Image image;
                image.Source(strongImageSource);
                if (auto strongTileControl = weakTileControl.get())
                {
                    strongTileControl.LoadImageBrush(image);
                }
            }
            co_return;
        }

        winrt::HttpClient httpClient;
        auto getOperation = co_await httpClient.GetAsync(imageUrl);
        auto readOperation = co_await getOperation.Content().ReadAsStringAsync();
        auto size{ParseSizeOfSVGImageFromXmlString(readOperation)};

        if (auto strongImageSource = weakImageSource.get())
        {
            co_await wil::resume_foreground(GetDispatcher(strongImageSource));
            strongImageSource.RasterizePixelHeight(size.Height);
            strongImageSource.RasterizePixelWidth(size.Width);
            winrt::Image image; 
            image.Source(strongImageSource);
            strongImageSource.UriSource(imageUrl);
            if (auto strongTileControl = weakTileControl.get())
            {
                strongTileControl.LoadImageBrush(image);
			}
        }
    }

    void ApplyBackgroundToRoot(winrt::Panel const& rootPanel,
                               winrt::AdaptiveBackgroundImage const& adaptiveBackgroundImage,
                               winrt::AdaptiveRenderContext const& renderContext)
    {
        // Creates the background image for all fill modes
        auto tileControl = winrt::make<winrt::implementation::TileControl>();
        auto imageUrl = GetUrlFromString(renderContext.HostConfig(), adaptiveBackgroundImage.Url());
        bool IsSvg = IsSvgImage(imageUrl);

        // In order to reuse the image creation code paths, we simply create an adaptive card
        // image element and then build that into xaml and apply to the root.
        if (const auto backgroundImage = CreateBackgroundImage(renderContext, tileControl, IsSvg, imageUrl))
        {
            // Set IsEnabled to false to avoid generating a tab stop for the background image tile control
            tileControl.IsEnabled(false);
            tileControl.BackgroundImage(adaptiveBackgroundImage);
            if (!IsSvg)
            {
                tileControl.LoadImageBrush(backgroundImage);
            }

            XamlHelpers::AppendXamlElementToPanel(tileControl, rootPanel);

            // The overlay applied to the background image is determined by a resouce, so create
            // the overlay if that resources exists
            auto resourceDictionary = renderContext.OverrideStyles();
            if (const auto backgroundOverlayBrush =
                    XamlHelpers::TryGetResourceFromResourceDictionaries(resourceDictionary, c_BackgroundImageOverlayBrushKey)
                        .try_as<winrt::Brush>())
            {
                winrt::Rectangle overlayRectangle;
                overlayRectangle.Fill(backgroundOverlayBrush);

                XamlHelpers::AppendXamlElementToPanel(overlayRectangle, rootPanel);
            }
        }
    }

    std::tuple<winrt::UIElement, winrt::IAdaptiveCardElement> RenderFallback(winrt::IAdaptiveCardElement const& currentElement,
                                                                             winrt::AdaptiveRenderContext const& renderContext,
                                                                             winrt::AdaptiveRenderArgs const& renderArgs)
    {
        if (!currentElement)
        {
            return {nullptr, nullptr};
        }

        auto elementRenderers = renderContext.ElementRenderers();
        auto elementFallback = currentElement.FallbackType();
        winrt::hstring elementType = currentElement.ElementTypeString();

        bool fallbackHandled = false;
        winrt::UIElement fallbackControl{nullptr};
        winrt::IAdaptiveCardElement renderedElement{nullptr};
        winrt::UIElement result{nullptr};

        switch (elementFallback)
        {
        case winrt::FallbackType::Content:
        {
            auto fallbackElement = currentElement.FallbackContent();

            winrt::hstring fallbackElementType = fallbackElement.ElementTypeString();

            WarnForFallbackContentElement(renderContext, elementType, fallbackElementType);

            auto fallbackElementRenderer = elementRenderers.Get(fallbackElementType);

            if (fallbackElementRenderer)
            {
                try
                {
                    fallbackControl = fallbackElementRenderer.Render(fallbackElement, renderContext, renderArgs);
                    renderedElement = fallbackElement;
                }
                catch (winrt::hresult_error const& ex)
                {
                    if (ex.code() == E_PERFORM_FALLBACK)
                    {
                        std::tie(fallbackControl, renderedElement) = RenderFallback(fallbackElement, renderContext, renderArgs);
                    }
                    else
                    {
                        throw(ex);
                    }
                }
            }
            else
            {
                std::tie(fallbackControl, renderedElement) = RenderFallback(fallbackElement, renderContext, renderArgs);
            }

            fallbackHandled = true;
            break;
        }
        case winrt::FallbackType::Drop:
        {
            XamlHelpers::WarnForFallbackDrop(renderContext, elementType);
            fallbackHandled = true;
            break;
        }
        case winrt::FallbackType::None:
        default:
        {
            break;
        }
        }

        if (fallbackHandled)
        {
            result = fallbackControl;
        }
        else
        {
            if (!renderArgs.AncestorHasFallback())
            {
                renderContext.AddWarning(winrt::WarningStatusCode::NoRendererForType, L"No Renderer found for type: " + elementType);
            }
            else
            {
                throw winrt::hresult_error(E_PERFORM_FALLBACK);
            }
        }
        return std::tuple(result, renderedElement);
    }

    bool NeedsSeparator(winrt::IAdaptiveCardElement const& cardElement)
    {
        auto elementSpacing = cardElement.Spacing();
        auto hasSeparator = cardElement.Separator();

        return hasSeparator || (elementSpacing != winrt::Spacing::None);
    }

    void AddRenderedControl(winrt::UIElement const& newControl,
                            winrt::IAdaptiveCardElement const& element,
                            winrt::Panel const& parentPanel,
                            winrt::UIElement const& separator,
                            winrt::ColumnDefinition const& columnDefinition,
                            std::function<void(winrt::UIElement const& child)> childCreatedCallback)
    {
        if (newControl)
        {
            bool isVisible = element.IsVisible();

            if (!isVisible)
            {
                newControl.Visibility(winrt::Visibility::Collapsed);
            }

            auto newControlAsFrameworkElement = newControl.as<winrt::FrameworkElement>();

            winrt::hstring id = element.Id();

            if (!id.empty())
            {
                newControlAsFrameworkElement.Name(id);
            }

            auto heightType = element.Height();

            auto tagContent = winrt::make<winrt::implementation::ElementTagContent>(
                element, parentPanel, separator, columnDefinition, isVisible, heightType == winrt::HeightType::Stretch);
            newControlAsFrameworkElement.Tag(tagContent);

            XamlHelpers::AppendXamlElementToPanel(newControl, parentPanel, heightType);

            childCreatedCallback(newControl);
        }
    }

    void AddHandledTappedEvent(winrt::UIElement const& uiElement)
    {
        if (!uiElement)
        {
            return;
        }
        uiElement.Tapped([](winrt::IInspectable const&, winrt::TappedRoutedEventArgs const& args) { args.Handled(true); });
    }

    // TODO: file bug here - when size = auto and we use resource resolvers, this method is called twice and the second time the height and width are set to 0
    void SetAutoImageSize(winrt::FrameworkElement const& imageControl,
                          winrt::IInspectable const& parentElement,
                          winrt::ImageSource const& imageSource,
                          bool setVisible)
    {
        double pixelHeight;
        double pixelWidth;

        if (const auto bitmap = imageSource.try_as<winrt::BitmapSource>())
        {
            pixelHeight = bitmap.PixelHeight();
            pixelWidth = bitmap.PixelWidth();
        }
        else
        {
            auto svg = imageSource.try_as<winrt::SvgImageSource>();
            pixelHeight = svg.RasterizePixelHeight();
            pixelWidth = svg.RasterizePixelWidth();
        }

        double maxHeight = imageControl.MaxHeight();
        double maxWidth = imageControl.MaxWidth();

        if (const auto parentAsColumnDefinition = parentElement.try_as<winrt::ColumnDefinition>())
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
        if (const auto localElementAsEllipse = imageControl.try_as<winrt::Ellipse>())
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
            imageControl.Visibility(winrt::Visibility::Visible);
        }
    }

    winrt::UIElement AddSeparatorIfNeeded(int& currentElement,
                                          winrt::IAdaptiveCardElement const& element,
                                          winrt::AdaptiveHostConfig const& hostConfig,
                                          winrt::AdaptiveRenderContext const& renderContext,
                                          winrt::Panel const& parentPanel)
    {
        // First element does not need a separator added
        if (currentElement++ > 0)
        {
            if (NeedsSeparator(element))
            {
                auto separatorParams = XamlHelpers::GetSeparatorParameters(element, hostConfig);
                auto separator = XamlHelpers::CreateSeparator(renderContext,
                                                              separatorParams.spacing,
                                                              separatorParams.thickness,
                                                              separatorParams.color);
                XamlHelpers::AppendXamlElementToPanel(separator, parentPanel);
                return separator;
            }
        }
        return nullptr;
    }

    void ApplyMarginToXamlElement(winrt::IAdaptiveHostConfig const& hostConfig, winrt::IFrameworkElement const& element)
    {
        auto spacingConfig = hostConfig.Spacing();
        uint32_t padding = spacingConfig.Padding();

        element.Margin({(double)padding, (double)padding, (double)padding, (double)padding});
    }

    void FormatLabelRunWithHostConfig(winrt::AdaptiveHostConfig const& hostConfig,
                                      winrt::AdaptiveInputLabelConfig const& inputLabelConfig,
                                      bool isHint,
                                      winrt::Run const& labelRun)
    {
        // If we're formatting a hint then use attention color
        winrt::ForegroundColor textColor = isHint ? winrt::ForegroundColor::Attention : inputLabelConfig.Color();

        auto color = GetColorFromAdaptiveColor(hostConfig, textColor, winrt::ContainerStyle::Default, false, false);

        labelRun.Foreground(winrt::SolidColorBrush{color});

        winrt::TextSize textSize = inputLabelConfig.Size();

        uint32_t resultSize = GetFontSizeFromFontType(hostConfig, winrt::FontType::Default, textSize);

        labelRun.FontSize(resultSize);
    }

    void AddRequiredHintInline(winrt::AdaptiveHostConfig const& hostConfig,
                               winrt::AdaptiveInputLabelConfig const& inputLabelConfig,
                               winrt::IVector<winrt::Inline> const& inlines)
    {
        // Create an inline for the suffix
        winrt::Run hintRun{};

        winrt::hstring suffix = inputLabelConfig.Suffix();
        // If no suffix was defined, use * as default

        if (suffix.empty())
        {
            suffix = UTF8ToHString(" *");
        }

        hintRun.Text(suffix);

        FormatLabelRunWithHostConfig(hostConfig, inputLabelConfig, true /*isHint*/, hintRun);

        inlines.Append(hintRun);
    }

    winrt::UIElement RenderInputLabel(winrt::IAdaptiveInputElement const& adaptiveInputElement,
                                      winrt::AdaptiveRenderContext const& renderContext)
    {
        winrt::hstring inputLabel = adaptiveInputElement.Label();
        // Retrieve if the input is required so we can file a warning if the label is empty
        bool isRequired = adaptiveInputElement.IsRequired();

        // TOOD: is this correct way instead of? should I check for data?
        if (!inputLabel.empty())
        {
            // Create a rich text block for the label
            winrt::RichTextBlock xamlRichTextBlock{};

            // Add a paragraph for the inlines
            auto xamlBlocks = xamlRichTextBlock.Blocks();

            winrt::Paragraph xamlParagraph{};

            xamlBlocks.Append(xamlParagraph);

            // Add the inlines
            auto xamlInlines = xamlParagraph.Inlines();

            // First inline is the label from the card
            winrt::Run labelRun{};
            labelRun.Text(inputLabel);

            xamlInlines.Append(labelRun);

            // Get the label config depending if the input is required
            auto hostConfig = renderContext.HostConfig();
            auto inputsConfig = hostConfig.Inputs();
            auto labelConfig = inputsConfig.Label();
            winrt::AdaptiveInputLabelConfig inputLabelConfig =
                isRequired ? labelConfig.RequiredInputs() : labelConfig.OptionalInputs();

            if (isRequired)
            {
                AddRequiredHintInline(hostConfig, inputLabelConfig, xamlInlines);
            }
            FormatLabelRunWithHostConfig(hostConfig, inputLabelConfig, false /*isHint*/, labelRun);

            xamlRichTextBlock.TextWrapping(winrt::TextWrapping::Wrap);
            return xamlRichTextBlock;
        }
        else if (isRequired)
        {
            renderContext.AddWarning(winrt::WarningStatusCode::EmptyLabelInRequiredInput,
                                     L"Input is required but there's no label for required hint rendering");
        }
        return nullptr;
    }

    // Error messages are formatted for text size and weight
    void FormatErrorMessageWithHostConfig(winrt::AdaptiveRenderContext const& renderContext, winrt::TextBlock const& errorMessage)
    {
        auto hostConfig = renderContext.HostConfig();
        auto inputsConfig = hostConfig.Inputs();
        auto errorMessageConfig = inputsConfig.ErrorMessage();

        // Set size defined in host config
        winrt::TextSize textSize = errorMessageConfig.Size();
        uint32_t resultSize = GetFontSizeFromFontType(hostConfig, winrt::FontType::Default, textSize);
        errorMessage.FontSize(resultSize);

        // Set weight defined in host config
        winrt::TextWeight textWeight = errorMessageConfig.Weight();
        auto resultWeight = GetFontWeightFromStyle(hostConfig, winrt::FontType::Default, textWeight);
        errorMessage.FontWeight(resultWeight);
    }

    winrt::UIElement RenderInputErrorMessage(winrt::IAdaptiveInputElement const& adaptiveInputElement,
                                             winrt::AdaptiveRenderContext const& renderContext)
    {
        // Add the error message if present
        winrt::hstring errorMessage = adaptiveInputElement.ErrorMessage();

        if (!errorMessage.empty())
        {
            winrt::TextBlock errorMessageTextBlock{};
            errorMessageTextBlock.Text(errorMessage);

            // Set the color to Attention color
            auto hostConfig = renderContext.HostConfig();

            auto attentionColor =
                GetColorFromAdaptiveColor(hostConfig, winrt::ForegroundColor::Attention, winrt::ContainerStyle::Default, false, false);

            errorMessageTextBlock.Foreground(winrt::SolidColorBrush{attentionColor});

            // Format the error message through host config
            FormatErrorMessageWithHostConfig(renderContext, errorMessageTextBlock);

            // Error message should begin collapsed and only be show when validated
            errorMessageTextBlock.Visibility(winrt::Visibility::Collapsed);
            errorMessageTextBlock.TextWrapping(winrt::TextWrapping::Wrap);
            return errorMessageTextBlock;
        }
        return nullptr;
    }

    winrt::Border XamlHelpers::CreateValidationBorder(winrt::UIElement const& childElement, winrt::AdaptiveRenderContext const& renderContext)
    {
        auto hostConfig = renderContext.HostConfig();

        auto attentionColor =
            GetColorFromAdaptiveColor(hostConfig, winrt::ForegroundColor::Attention, winrt::ContainerStyle::Default, false, false);

        // Create a border in the attention color. The thickness is 0 for now so it won't be visibile until validation is run
        winrt::Border validationBorder{};
        validationBorder.BorderBrush(winrt::SolidColorBrush{attentionColor});
        validationBorder.Child(childElement);

        return validationBorder;
    }

    winrt::UIElement HandleLabelAndErrorMessage(winrt::IAdaptiveInputElement const& adaptiveInput,
                                                winrt::AdaptiveRenderContext const& renderContext,
                                                winrt::UIElement const& inputLayout)
    {
        // Create a new stack panel to add the label and error message
        // The contents from the input panel will be copied to the new panel
        winrt::StackPanel inputStackPanel{};

        auto hostConfig = renderContext.HostConfig();
        // TOOD: rename Inputs to something more meaningful
        auto inputsConfig = hostConfig.Inputs();

        // Render the label and add it to the stack panel
        auto label = XamlHelpers::RenderInputLabel(adaptiveInput, renderContext);
        XamlHelpers::AppendXamlElementToPanel(label, inputStackPanel);

        if (label)
        {
            auto labelConfig = inputsConfig.Label();
            winrt::Spacing labelSpacing = labelConfig.InputSpacing();

            uint32_t spacing = GetSpacingSizeFromSpacing(hostConfig, labelSpacing);

            auto separator = XamlHelpers::CreateSeparator(renderContext, spacing, 0, winrt::Windows::UI::Color{});
            XamlHelpers::AppendXamlElementToPanel(separator, inputStackPanel);
        }

        winrt::UIElement actualUIElement{nullptr};

        // Copy the contents into the new panel and get the rendered element to set acessibility properties
        if (const auto inputPanel = inputLayout.try_as<winrt::Panel>())
        {
            auto panelChildren = inputPanel.Children();
            uint32_t childrenCount = panelChildren.Size();

            // We only copy one element into the input layout, if there's only one element, then we can assume it's our layout
            if (childrenCount == 1)
            {
                auto onlyElement = panelChildren.GetAt(0);
                // We enclose multiple items using a border, so we try to check for it
                if (const auto inputBorder = onlyElement.try_as<winrt::Border>())
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

        if (errorMessageControl)
        {
            // Render the spacing between the input and the error message
            auto errorMessageConfig = inputsConfig.ErrorMessage();

            winrt::Spacing errorSpacing = errorMessageConfig.Spacing();

            uint32_t spacing = GetSpacingSizeFromSpacing(hostConfig, errorSpacing);

            auto separator = XamlHelpers::CreateSeparator(renderContext, spacing, 0, winrt::Windows::UI::Color{});
            auto inputValue = renderContext.GetInputValue(adaptiveInput);

            if (inputValue)
            {
                inputValue.ErrorMessage(errorMessageControl);
            }

            XamlHelpers::AppendXamlElementToPanel(separator, inputStackPanel);

            // Add the rendered error message
            XamlHelpers::AppendXamlElementToPanel(errorMessageControl, inputStackPanel);
        }

        if (label)
        {
            winrt::AutomationProperties::SetLabeledBy(actualUIElement, label);

            /// SetIsRequiredForForm does not work for AutoSuggestBox, manually adding a11y label 
            if (adaptiveInput.IsRequired() && actualUIElement.try_as<winrt::AutoSuggestBox>() != nullptr)
            {
                winrt::AutomationProperties::SetName(actualUIElement, adaptiveInput.Label() + L" required, ");
            }
            else
            {
                winrt::AutomationProperties::SetName(actualUIElement, adaptiveInput.Label());
            }
        }

        return inputStackPanel;
    }

    std::tuple<winrt::UIElement, winrt::Border>
    XamlHelpers::HandleInputLayoutAndValidation(winrt::IAdaptiveInputElement const& adaptiveInput,
                                                winrt::UIElement const& inputUIElement,
                                                bool hasTypeSpecificValidation,
                                                winrt::AdaptiveRenderContext const& renderContext,
                                                bool ifValidationBorderIsNeeded)
    {
        winrt::StackPanel inputStackPanel{};

        // The input may need to go into a border to handle validation before being added to the stack panel.
        // inputUIElementParentContainer represents the current parent container.
        auto inputUIElementParentContainer = inputUIElement;

        // If there's any validation on this input, and the caller has requested a validation border by passing
        // validationBorderOut, put the input inside a border
        auto isRequired = adaptiveInput.IsRequired();

        auto hasValidation = (hasTypeSpecificValidation || isRequired);

        if (hasValidation)
        {
            // If we have validation, we should have an error message to display if it fails. If we don't, return a
            // warning to encourage the card author to add one.
            if (adaptiveInput.ErrorMessage().empty())
            {
                renderContext.AddWarning(winrt::WarningStatusCode::MissingValidationErrorMessage,
                                         L"Inputs with validation should include an errorMessage");
            }
        }

        winrt::Border validationBorder{nullptr};
        if (hasValidation && ifValidationBorderIsNeeded)
        {
            validationBorder = XamlHelpers::CreateValidationBorder(inputUIElement, renderContext);
            inputUIElementParentContainer = validationBorder;
        }

        XamlHelpers::AppendXamlElementToPanel(inputUIElementParentContainer, inputStackPanel);

        // Different input renderers perform stuff differently
        // Input.Text and Input.Number render the border previously so the object received as parameter may be a
        // border Input.Time and Input.Date let this method render the border for them Input.Toggle
        winrt::UIElement actualInputUIElement{nullptr};

        if (hasValidation && ifValidationBorderIsNeeded)
        {
            actualInputUIElement = validationBorder.Child();
        }
        else
        {
            if (hasValidation)
            {
                // This handles the case when the sent item was a Input.Text or Input.Number as we have to get the actual TextBox from the border
                if (const auto containerAsBorder = inputUIElementParentContainer.try_as<winrt::Border>())
                {
                    validationBorder = containerAsBorder;
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

        // The AutomationProperties.IsRequiredForForm property allows an input to provide a little bit of extra information to
        // people using a screen reader by specifying if an input is required. Visually we represent this with a hint.
        winrt::AutomationProperties::SetIsRequiredForForm(actualInputUIElement, isRequired);

        // In the case of Input.Toggle we have to define the DescribedBy property to put the title in it
        if (const auto adaptiveToggleInput = adaptiveInput.try_as<winrt::AdaptiveToggleInput>())
        {
            if (const auto uiInputElementAsContentControl = actualInputUIElement.try_as<winrt::ContentControl>())
            {
                if (const auto content = uiInputElementAsContentControl.Content())
                {
                    if (const auto contentAsDependencyObject = content.try_as<winrt::DependencyObject>())
                    {
                        auto uiElementDescribers = winrt::AutomationProperties::GetDescribedBy(actualInputUIElement);
                        uiElementDescribers.Append(contentAsDependencyObject);
                    }
                }
            }
        }

        return {inputStackPanel, validationBorder};
    }

    SeparatorParemeters XamlHelpers::GetSeparatorParameters(winrt::IAdaptiveCardElement const& element,
                                                            winrt::AdaptiveHostConfig const& hostConfig)
    {
        auto spacing = GetSpacingSizeFromSpacing(hostConfig, element.Spacing());
        winrt::Windows::UI::Color lineColor{0};
        uint32_t lineThickness{0};
        if (element.Separator())
        {
            auto separatorConfig = hostConfig.Separator();
            lineColor = separatorConfig.LineColor();
            lineThickness = separatorConfig.LineThickness();
        }

        return {lineColor, spacing, lineThickness};
    }

    winrt::Image XamlHelpers::RenderImageFromDataUri(winrt::Uri const& imageUrl)
    {
        winrt::Image image{};
        winrt::BitmapImage bitmapImage{};
        bitmapImage.CreateOptions(winrt::BitmapCreateOptions::IgnoreImageCache);

        // Decode base 64 string
        std::string data = AdaptiveBase64Util::ExtractDataFromUri(HStringToUTF8(imageUrl.Path()));
        std::vector<char> decodedData = AdaptiveBase64Util::Decode(data);

        winrt::DataWriter dataWriter{winrt::InMemoryRandomAccessStream{}};

        dataWriter.WriteBytes(std::vector<byte>{decodedData.begin(), decodedData.end()});

        dataWriter.StoreAsync().Completed(
            [dataWriter, bitmapImage, image](winrt::IAsyncOperation<uint32_t> const& /*operation*/, winrt::AsyncStatus /*status*/) -> void
            {
                if (const auto stream = dataWriter.DetachStream().try_as<winrt::InMemoryRandomAccessStream>())
                {
                    stream.Seek(0);
                    image.Source(bitmapImage);
                    bitmapImage.SetSourceAsync(stream);
                }
            });

        return image;
    }
}
