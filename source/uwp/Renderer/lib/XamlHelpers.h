// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "WholeItemsPanel.h"
namespace AdaptiveCards::Rendering::Uwp::XamlHelpers
{
    inline winrt::SolidColorBrush GetSolidColorBrush(winrt::Windows::UI::Color const& color)
    {
        winrt::SolidColorBrush solidColorBrush;
        solidColorBrush.Color(color);
        return solidColorBrush;
    }

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
            // TODO: is this the right way?
            // TODO: can we peek innards right away?
            if (const auto wholeItemsPanel = panel.try_as<winrt::WholeItemsPanel>())
            {
                auto wholeItemsPanelImpl = peek_innards<winrt::implementation::WholeItemsPanel>(wholeItemsPanel);
                wholeItemsPanelImpl->AddElementToStretchablesList(elementToAppend);
            }
        }
    }

    template<typename T> void SetToggleValue(T const& item, bool isChecked)
    {
        // TODO: compiling fails at AdaptiveToggleInputRenderer.cpp(66)
        // static_assert(std::is_base_of<winrt::ToggleButton>, T > ::value, "T
        // must inherit from ToggleButton");
        // TODO: do we want static asserts? or is it fine with compilers catching misusages?

        auto toggleButton = item.as<winrt::ToggleButton>(); // TODO: I don't think we need this cast, all
                                                            // toggleButton descendabts have isChecked() exposed, right?
        toggleButton.IsChecked(isChecked);
    }

    template<typename T> bool GetToggleValue(T const& item)
    {
        // TODO: InputValue613 failes to compile, why?
        /*static_assert(std::is_base_of<winrt::ToggleButton, T > ::value, "T must inherit from ToggleButton");*/
        auto toggleButton = item.as<winrt::ToggleButton>(); // TODO: I don't think we need this cast, all
                                                            // toggleButton descendants have isChecked() exposed, right?

        return GetValueFromRef(toggleButton.IsChecked(), false);
    }

    template<typename T> void SetContent(T const& item, winrt::hstring const& contentString)
    {
        // TODO: Do I need this here? should it be simply ContentControl? that should be enough, right?
        /* static_assert(std::is_base_of<winrt::ToggleButton, T > ::value, "T must inherit from ContenControl");*/
        SetContent(item, contentString, false);
    }

    template<typename T> void SetContent(T const& item, winrt::hstring const& contentString, bool wrap)
    {
        // TODO: compiling failing as ToggleInputRenderer(52)
        /*  static_assert(std::is_base_of<winrt::ToggleButton, T > ::value, "T must inherit from ToggleButton");*/
        winrt::TextBlock content{};
        content.Text(contentString);

        if (wrap)
        {
            content.TextWrapping(winrt::TextWrapping::WrapWholeWords);
        }

        if (const auto contentControl = item.try_as<winrt::ContentControl>())
        {
            contentControl.Content(content);
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
            // TODO: can we peek innards right away?
            auto containerAsPanelImpl = peek_innards<winrt::implementation::WholeItemsPanel>(containerAsPanel);
            containerAsPanelImpl->SetVerticalContentAlignment(verticalContentAlignment);
        }
    }

    winrt::UIElement RenderInputLabel(winrt::IAdaptiveInputElement const& adaptiveInputElement,
                                      winrt::AdaptiveRenderContext const& renderContext,
                                      winrt::AdaptiveRenderArgs const& renderArgs);

    winrt::UIElement RenderInputErrorMessage(winrt::IAdaptiveInputElement const& adaptiveInputElement,
                                             winrt::AdaptiveRenderContext const& renderContext);

    winrt::Border CreateValidationBorder(winrt::UIElement const& childElement, winrt::AdaptiveRenderContext const& renderContext);

    winrt::UIElement HandleLabelAndErrorMessage(winrt::IAdaptiveInputElement const& adaptiveInput,
                                                winrt::AdaptiveRenderContext const& renderContext,
                                                winrt::AdaptiveRenderArgs const& renderArgs,
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

    // TODO: come back to this function
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

    inline void ErrForRenderFailed(winrt::AdaptiveRenderContext const& renderContext,
                                   winrt::hstring const& elementType,
                                   winrt::hstring const& exceptionMessage = L"")
    {
        auto error = L"Rendering failed for element of type \"" + elementType + L"\"";
        if (!exceptionMessage.empty())
        {
            error = error + L" with the following message: \n" + exceptionMessage;
        }
        renderContext.AddError(winrt::ErrorStatusCode::RenderFailed, error);
    }

    winrt::UIElement AddSeparatorIfNeeded(int& currentElement,
                                          winrt::IAdaptiveCardElement const& element,
                                          winrt::AdaptiveHostConfig const& hostConfig,
                                          winrt::AdaptiveRenderContext const& renderContext,
                                          winrt::Panel const& parentPanel);

    void SetAutoImageSize(winrt::FrameworkElement const& imageControl,
                          winrt::IInspectable const& parentElement,
                          winrt::BitmapSource const& imageSource,
                          bool setVisible);

    void ApplyMarginToXamlElement(winrt::IAdaptiveHostConfig const& hostConfig, winrt::IFrameworkElement const& element);

    SeparatorParemeters GetSeparatorParameters(winrt::IAdaptiveCardElement const& element, winrt::AdaptiveHostConfig const& hostConfig);
}
