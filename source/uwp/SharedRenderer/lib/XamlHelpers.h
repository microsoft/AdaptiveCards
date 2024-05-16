// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Xaml_Rendering::XamlHelpers
{
    void SetStyleFromResourceDictionary(winrt::AdaptiveRenderContext const& renderContext,
                                        winrt::hstring const& resourceName,
                                        winrt::FrameworkElement const& frameworkElement);

    winrt::UIElement CreateSeparator(winrt::AdaptiveRenderContext const& renderContext,
                                     uint32_t spacing,
                                     uint32_t separatorThickness,
                                     winrt::Windows::UI::Color const& separatorColor,
                                     bool isHorizontal = true);

    inline winrt::IInspectable TryGetResourceFromResourceDictionaries(winrt::ResourceDictionary const& resourceDictionary,
                                                                      winrt::hstring const& resourceName)
    {
        if (resourceDictionary == nullptr)
        {
            return nullptr;
        }

        auto resourceKey = winrt::box_value(resourceName);
        return resourceDictionary.HasKey(resourceKey) ? resourceDictionary.Lookup(resourceKey) : nullptr;
    }

    void SetSeparatorVisibility(winrt::Panel const& parentPanel);

    void HandleColumnWidth(winrt::AdaptiveColumn const& column, bool isVisible, winrt::ColumnDefinition const& columnDefinition);

    void HandleTableColumnWidth(winrt::AdaptiveTableColumnDefinition const& column, winrt::ColumnDefinition const& columnDefinition);

    template<typename T>
    void AppendXamlElementToPanel(T const& xamlElement, winrt::Panel const& panel, winrt::HeightType heightType = winrt::HeightType::Auto)
    {
        if (!xamlElement)
        {
            return;
        }

        auto elementToAppend = xamlElement.as<winrt::UIElement>();
        panel.Children().Append(elementToAppend);

        if (heightType == winrt::HeightType::Stretch)
        {
            if (const auto wholeItemsPanel = panel.try_as<winrt::WholeItemsPanel>())
            {
                if (const auto wholeItemsPanelImpl = peek_innards<winrt::implementation::WholeItemsPanel>(wholeItemsPanel))
                {
                    wholeItemsPanelImpl->AddElementToStretchablesList(elementToAppend);
                }
            }
        }
    }

    template<typename T> bool GetToggleValue(T const& item)
    {
        auto toggleButton = item.as<winrt::ToggleButton>();
        return GetValueFromRef(toggleButton.IsChecked(), false);
    }

    winrt::TextBlock CreateTextBlockWithContent(winrt::hstring const& contentString, bool wrap);

    template<typename T> void SetContent(T const& item, winrt::hstring const& contentString)
    {
        SetContent(item, contentString, false /* wrap */);
    }

    template<typename T> void SetContent(T const& item, winrt::hstring const& contentString, bool wrap)
    {
        if (const auto contentControl = item.try_as<winrt::ContentControl>())
        {
            contentControl.Content(CreateTextBlockWithContent(contentString, wrap));
        }
    }

    winrt::ContainerStyle HandleStylingAndPadding(winrt::IAdaptiveContainerBase const& adaptiveContainer,
                                                  winrt::Border const& containerBorder,
                                                  winrt::AdaptiveRenderContext const& renderContext,
                                                  winrt::AdaptiveRenderArgs renderArgs);

    bool SupportsInteractivity(winrt::AdaptiveHostConfig const& hostConfig);

    template<typename T>
    void SetVerticalContentAlignmentToChildren(T const& container, winrt::VerticalContentAlignment verticalContentAlignment)
    {
        if (const auto containerAsPanel = container.try_as<winrt::WholeItemsPanel>())
        {
            if (const auto containerAsPanelImpl = peek_innards<winrt::implementation::WholeItemsPanel>(containerAsPanel))
            {
                containerAsPanelImpl->SetVerticalContentAlignment(verticalContentAlignment);
            }
        }
    }

    winrt::UIElement RenderInputLabel(winrt::IAdaptiveInputElement const& adaptiveInputElement,
                                      winrt::AdaptiveRenderContext const& renderContext);

    winrt::UIElement RenderInputErrorMessage(winrt::IAdaptiveInputElement const& adaptiveInputElement,
                                             winrt::AdaptiveRenderContext const& renderContext);

    winrt::Border CreateValidationBorder(winrt::UIElement const& childElement, winrt::AdaptiveRenderContext const& renderContext);

    winrt::UIElement HandleLabelAndErrorMessage(winrt::IAdaptiveInputElement const& adaptiveInput,
                                                winrt::AdaptiveRenderContext const& renderContext,
                                                winrt::UIElement const& inputLayout);

    std::tuple<winrt::UIElement, winrt::Border> HandleInputLayoutAndValidation(winrt::IAdaptiveInputElement const& adaptiveInput,
                                                                               winrt::UIElement const& inputUIElement,
                                                                               bool hasTypeSpecificValidation,
                                                                               winrt::AdaptiveRenderContext const& renderContext,
                                                                               bool ifValidationBorderIsNeeded = true);

    void AddHandledTappedEvent(winrt::UIElement const& uiElement);

    void ApplyBackgroundToRoot(winrt::Panel const& rootPanel,
                               winrt::AdaptiveBackgroundImage const& backgroundImage,
                               winrt::AdaptiveRenderContext const& renderContext);

    void AddRenderedControl(winrt::UIElement const& newControl,
                            winrt::IAdaptiveCardElement const& element,
                            winrt::Panel const& parentPanel,
                            winrt::UIElement const& separator,
                            winrt::ColumnDefinition const& columnDefinition,
                            std::function<void(winrt::UIElement const& child)> childCreatedCallback);

    std::tuple<winrt::UIElement, winrt::IAdaptiveCardElement> RenderFallback(winrt::IAdaptiveCardElement const& currentElement,
                                                                             winrt::AdaptiveRenderContext const& renderContext,
                                                                             winrt::AdaptiveRenderArgs const& renderArgs);

    bool NeedsSeparator(winrt::IAdaptiveCardElement const& cardElement);

    inline void WarnFallbackString(winrt::AdaptiveRenderContext const& renderContext, winrt::hstring const& warning)
    {
        renderContext.AddWarning(winrt::WarningStatusCode::PerformingFallback, warning);
    }

    inline void WarnForFallbackContentElement(winrt::AdaptiveRenderContext const& renderContext,
                                              winrt::hstring const& parentElementType,
                                              winrt::hstring const& fallbackElementType)
    {
        auto warning = L"Performing fallback for element of type \"" + parentElementType +
            L"\" (fallback element type \"" + fallbackElementType + L"\")";
        WarnFallbackString(renderContext, warning);
    }

    inline void WarnForFallbackDrop(winrt::AdaptiveRenderContext const& renderContext, winrt::hstring const& elementType)
    {
        WarnFallbackString(renderContext, L"Dropping element of type \"" + elementType + L"\" for fallback");
    }

    inline void LogErrRenderFailed(winrt::AdaptiveRenderContext const& renderContext,
                                   winrt::hstring const& elementType = L"",
                                   winrt::hstring const& exceptionMessage = L"")
    {
        winrt::hstring errorMessage = L"Rendering failed";

        if (!elementType.empty())
        {
            errorMessage = errorMessage + L" for element of type \"" + elementType + L"\"";
        }

        if (!exceptionMessage.empty())
        {
            errorMessage = errorMessage + L" with the following message: \n" + exceptionMessage;
        }
        renderContext.AddError(winrt::ErrorStatusCode::RenderFailed, errorMessage);
    }

    inline void ErrForRenderFailed(winrt::AdaptiveRenderContext const& renderContext, winrt::hstring const& exceptionMessage = L"")
    {
        LogErrRenderFailed(renderContext, L"", exceptionMessage);
    }

    inline void ErrForRenderFailedForElement(winrt::AdaptiveRenderContext const& renderContext,
                                             winrt::hstring const& elementType,
                                             winrt::hstring const& exceptionMessage = L"")
    {
        LogErrRenderFailed(renderContext, elementType, exceptionMessage);
    }

    winrt::UIElement AddSeparatorIfNeeded(int& currentElement,
                                          winrt::IAdaptiveCardElement const& element,
                                          winrt::AdaptiveHostConfig const& hostConfig,
                                          winrt::AdaptiveRenderContext const& renderContext,
                                          winrt::Panel const& parentPanel);

    void SetAutoImageSize(winrt::FrameworkElement const& imageControl,
                          winrt::IInspectable const& parentElement,
                          winrt::ImageSource const& imageSource,
                          bool setVisible);

    void ApplyMarginToXamlElement(winrt::IAdaptiveHostConfig const& hostConfig, winrt::IFrameworkElement const& element);

    SeparatorParemeters GetSeparatorParameters(winrt::IAdaptiveCardElement const& element, winrt::AdaptiveHostConfig const& hostConfig);

    winrt::Image RenderImageFromDataUri(winrt::Uri const& imageUrl);

    winrt::fire_and_forget ConfigureSvgImageSourceAsync(winrt::Uri imageUrl,
                                                        winrt::SvgImageSource svgImageSource,
                                                        winrt::TileControl tileControl);
}
