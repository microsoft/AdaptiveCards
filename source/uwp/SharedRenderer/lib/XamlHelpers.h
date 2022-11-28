// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Xaml_Rendering::XamlHelpers
{
    void SetStyleFromResourceDictionary(winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                        winrt::hstring const& resourceName,
                                        winrt::xaml::FrameworkElement const& frameworkElement);

    winrt::xaml::UIElement CreateSeparator(winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                           uint32_t spacing,
                                           uint32_t separatorThickness,
                                           winrt::Windows::UI::Color const& separatorColor,
                                           bool isHorizontal = true);

    inline winrt::IInspectable TryGetResourceFromResourceDictionaries(winrt::xaml::ResourceDictionary const& resourceDictionary,
                                                                      winrt::hstring const& resourceName)
    {
        if (resourceDictionary == nullptr)
        {
            return nullptr;
        }

        auto resourceKey = winrt::box_value(resourceName);
        return resourceDictionary.HasKey(resourceKey) ? resourceDictionary.Lookup(resourceKey) : nullptr;
    }

    void SetSeparatorVisibility(winrt::xaml_controls::Panel const& parentPanel);

    void HandleColumnWidth(winrt::AdaptiveColumn const& column, bool isVisible, winrt::xaml_controls::ColumnDefinition const& columnDefinition);

    void HandleTableColumnWidth(winrt::AdaptiveTableColumnDefinition const& column,
                                winrt::xaml_controls::ColumnDefinition const& columnDefinition);

    template<typename T>
    void AppendXamlElementToPanel(T const& xamlElement,
                                  winrt::xaml_controls::Panel const& panel,
                                  winrt::HeightType heightType = winrt::HeightType::Auto)
    {
        if (!xamlElement)
        {
            return;
        }

        auto elementToAppend = xamlElement.as<winrt::xaml::UIElement>();
        panel.Children().Append(elementToAppend);

        if (heightType == winrt::HeightType::Stretch)
        {
            if (const auto wholeItemsPanel = panel.try_as<winrt::render_xaml::WholeItemsPanel>())
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
        auto toggleButton = item.as<winrt::xaml_controls::Primitives::ToggleButton>();
        return GetValueFromRef(toggleButton.IsChecked(), false);
    }

    winrt::xaml_controls::TextBlock CreateTextBlockWithContent(winrt::hstring const& contentString, bool wrap);

    template<typename T> void SetContent(T const& item, winrt::hstring const& contentString)
    {
        SetContent(item, contentString, false /* wrap */);
    }

    template<typename T> void SetContent(T const& item, winrt::hstring const& contentString, bool wrap)
    {
        if (const auto contentControl = item.try_as<winrt::xaml_controls::ContentControl>())
        {
            contentControl.Content(CreateTextBlockWithContent(contentString, wrap));
        }
    }

    winrt::ContainerStyle HandleStylingAndPadding(winrt::IAdaptiveContainerBase const& adaptiveContainer,
                                                  winrt::xaml_controls::Border const& containerBorder,
                                                  winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                                  winrt::render_xaml::AdaptiveRenderArgs renderArgs);

    bool SupportsInteractivity(winrt::render_xaml::AdaptiveHostConfig const& hostConfig);

    template<typename T>
    void SetVerticalContentAlignmentToChildren(T const& container, winrt::VerticalContentAlignment verticalContentAlignment)
    {
        if (const auto containerAsPanel = container.try_as<winrt::render_xaml::WholeItemsPanel>())
        {
            if (const auto containerAsPanelImpl = peek_innards<winrt::implementation::WholeItemsPanel>(containerAsPanel))
            {
                containerAsPanelImpl->SetVerticalContentAlignment(verticalContentAlignment);
            }
        }
    }

    winrt::xaml::UIElement RenderInputLabel(winrt::IAdaptiveInputElement const& adaptiveInputElement,
                                      winrt::render_xaml::AdaptiveRenderContext const& renderContext);

    winrt::xaml::UIElement RenderInputErrorMessage(winrt::IAdaptiveInputElement const& adaptiveInputElement,
                                             winrt::render_xaml::AdaptiveRenderContext const& renderContext);

    winrt::xaml_controls::Border CreateValidationBorder(winrt::xaml::UIElement const& childElement, winrt::render_xaml::AdaptiveRenderContext const& renderContext);

    winrt::xaml::UIElement HandleLabelAndErrorMessage(winrt::IAdaptiveInputElement const& adaptiveInput,
                                                winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                                      winrt::xaml::UIElement const& inputLayout);

    std::tuple<winrt::xaml::UIElement, winrt::xaml_controls::Border>
    HandleInputLayoutAndValidation(winrt::IAdaptiveInputElement const& adaptiveInput,
                                   winrt::xaml::UIElement const& inputUIElement,
                                   bool hasTypeSpecificValidation,
                                                                               winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                   bool ifValidationBorderIsNeeded = true);

    void AddHandledTappedEvent(winrt::xaml::UIElement const& uiElement);

    void ApplyBackgroundToRoot(winrt::xaml_controls::Panel const& rootPanel,
                               winrt::AdaptiveBackgroundImage const& backgroundImage,
                               winrt::render_xaml::AdaptiveRenderContext const& renderContext);

    void AddRenderedControl(winrt::xaml::UIElement const& newControl,
                            winrt::IAdaptiveCardElement const& element,
                            winrt::xaml_controls::Panel const& parentPanel,
                            winrt::xaml::UIElement const& separator,
                            winrt::xaml_controls::ColumnDefinition const& columnDefinition,
                            std::function<void(winrt::xaml::UIElement const& child)> childCreatedCallback);

    std::tuple<winrt::xaml::UIElement, winrt::IAdaptiveCardElement> RenderFallback(winrt::IAdaptiveCardElement const& currentElement,
                                                                             winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                                                             winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);

    bool NeedsSeparator(winrt::IAdaptiveCardElement const& cardElement);

    inline void WarnFallbackString(winrt::render_xaml::AdaptiveRenderContext const& renderContext, winrt::hstring const& warning)
    {
        renderContext.AddWarning(winrt::WarningStatusCode::PerformingFallback, warning);
    }

    inline void WarnForFallbackContentElement(winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                              winrt::hstring const& parentElementType,
                                              winrt::hstring const& fallbackElementType)
    {
        auto warning = L"Performing fallback for element of type \"" + parentElementType +
            L"\" (fallback element type \"" + fallbackElementType + L"\")";
        WarnFallbackString(renderContext, warning);
    }

    inline void WarnForFallbackDrop(winrt::render_xaml::AdaptiveRenderContext const& renderContext, winrt::hstring const& elementType)
    {
        WarnFallbackString(renderContext, L"Dropping element of type \"" + elementType + L"\" for fallback");
    }

    inline void LogErrRenderFailed(winrt::render_xaml::AdaptiveRenderContext const& renderContext,
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

    inline void ErrForRenderFailed(winrt::render_xaml::AdaptiveRenderContext const& renderContext, winrt::hstring const& exceptionMessage = L"")
    {
        LogErrRenderFailed(renderContext, L"", exceptionMessage);
    }

    inline void ErrForRenderFailedForElement(winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                             winrt::hstring const& elementType,
                                             winrt::hstring const& exceptionMessage = L"")
    {
        LogErrRenderFailed(renderContext, elementType, exceptionMessage);
    }

    winrt::xaml::UIElement AddSeparatorIfNeeded(int& currentElement,
                                                winrt::IAdaptiveCardElement const& element,
                                          winrt::render_xaml::AdaptiveHostConfig const& hostConfig,
                                          winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                                winrt::xaml_controls::Panel const& parentPanel);

    void SetAutoImageSize(winrt::xaml::FrameworkElement const& imageControl,
                          winrt::IInspectable const& parentElement,
                          winrt::xaml_media::ImageSource const& imageSource,
                          bool setVisible);

    void ApplyMarginToXamlElement(winrt::render_xaml::IAdaptiveHostConfig const& hostConfig, winrt::xaml::IFrameworkElement const& element);

    SeparatorParemeters GetSeparatorParameters(winrt::IAdaptiveCardElement const& element, winrt::render_xaml::AdaptiveHostConfig const& hostConfig);

    winrt::xaml_controls::Image RenderImageFromDataUri(winrt::Uri const& imageUrl);
}
