// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "AdaptiveCards.Rendering.Uwp.h"
#include "WholeItemsPanel.h"
#include <type_traits>

namespace AdaptiveCards::Rendering::Uwp::XamlHelpers
{
 /*   namespace winrt
    {
        namespace rendering = ::winrt::AdaptiveCards::Rendering::Uwp;
    };*/

    namespace rtxaml = winrt::Windows::UI::Xaml;

    inline winrt::SolidColorBrush GetSolidColorBrush(winrt::Windows::UI::Color const& color)
    {
        winrt::SolidColorBrush solidColorBrush;
        solidColorBrush.Color(color);
        return solidColorBrush;
    }

    void SetStyleFromResourceDictionary(winrt::AdaptiveRenderContext const& renderContext,
                                        winrt::hstring const& resourceName,
                                        rtxaml::FrameworkElement const& frameworkElement);

    rtxaml::UIElement CreateSeparator(winrt::AdaptiveRenderContext const& renderContext,
                                      uint32_t spacing,
                                      uint32_t separatorThickness,
                                      winrt::Windows::UI::Color const& separatorColor,
                                      bool isHorizontal = true);

    template<typename T>
    T TryGetResourceFromResourceDictionaries(rtxaml::ResourceDictionary const& resourceDictionary, winrt::hstring const& resourceName)
    {
        if (resourceDictionary == nullptr)
        {
            return nullptr;
        }
        T toReturn{nullptr};
        try
        {
            auto resourceKey = winrt::box_value(resourceName);

            toReturn = resourceDictionary.TryLookup(resourceKey).try_as<T>();
            return toReturn;
        }
        catch (...)
        {
            // TODO: do we want to catch exception and extract some value from it?
        }
        // TOOD: do we return nullptr?
        return nullptr;
    }

    template<typename T>
    T TryGetResourceFromResourceDictionaries(rtxaml::ResourceDictionary const& resourceDictionary, const wchar_t* resourceName)
    {
        return TryGetResourceFromResourceDictionaries<T>(resourceDictionary, winrt::to_hstring(resourceName));
    }

    void SetSeparatorVisibility(winrt::Panel const& parentPanel);

    void HandleColumnWidth(winrt::AdaptiveColumn const& column,
                           bool isVisible,
                           winrt::ColumnDefinition const& columnDefinition);

    void HandleTableColumnWidth(winrt::AdaptiveTableColumnDefinition const& column,
                                winrt::ColumnDefinition const& columnDefinition);

    template<typename T>
    void AppendXamlElementToPanel(T const& xamlElement,
                                  winrt::Panel const& panel,
                                  winrt::HeightType heightType = winrt::HeightType::Auto)
    {
        if (!xamlElement)
        {
            return;
        }

        auto elementToAppend = xamlElement.as<rtxaml::UIElement>();
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

        auto toggleButton =
            item.as<winrt::ToggleButton>(); // TODO: I don't think we need this cast, all
                                                                                     // toggleButton descendabts have isChecked() exposed, right?
        toggleButton.IsChecked(isChecked);
    }

    template<typename T> bool GetToggleValue(T const& item)
    {
        // TODO: InputValue613 failes to compile, why?
        /*static_assert(std::is_base_of<winrt::ToggleButton, T > ::value, "T must inherit from ToggleButton");*/
        auto toggleButton =
            item.as<winrt::ToggleButton>(); // TODO: I don't think we need this cast, all
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
            content.TextWrapping(rtxaml::TextWrapping::WrapWholeWords);
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

    winrt::Windows::UI::Xaml::UIElement
    RenderInputLabel(winrt::IAdaptiveInputElement const& adaptiveInputElement,
                     winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                     winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);

    winrt::Windows::UI::Xaml::UIElement
    RenderInputErrorMessage(winrt::IAdaptiveInputElement const& adaptiveInputElement,
                            winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext);

    winrt::Border
    CreateValidationBorder(winrt::Windows::UI::Xaml::UIElement const& childElement,
                           winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext);

    winrt::Windows::UI::Xaml::UIElement
    HandleLabelAndErrorMessage(winrt::IAdaptiveInputElement const& adaptiveInput,
                               winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                               winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs,
                               winrt::Windows::UI::Xaml::UIElement const& inputLayout);

    std::tuple<winrt::Windows::UI::Xaml::UIElement, winrt::Border>
    HandleInputLayoutAndValidation(winrt::IAdaptiveInputElement const& adaptiveInput,
                                   winrt::Windows::UI::Xaml::UIElement const& inputUIElement,
                                   bool hasTypeSpecificValidation,
                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                   bool ifValidationBorderIsNeeded = true);

    void AddHandledTappedEvent(winrt::Windows::UI::Xaml::UIElement const& uiElement);

    void ApplyBackgroundToRoot(winrt::Panel const& rootPanel, winrt::AdaptiveBackgroundImage const& backgroundImage, winrt::AdaptiveRenderContext const& renderContext);

    void AddRenderedControl(rtxaml::UIElement const& newControl,
                            winrt::IAdaptiveCardElement const& element,
                            winrt::Panel const& parentPanel,
                            rtxaml::UIElement const& separator,
                            winrt::ColumnDefinition const& columnDefinition,
                            std::function<void(rtxaml::UIElement const& child)> childCreatedCallback);

    // TODO: come back to this function
    std::tuple<rtxaml::UIElement, winrt::IAdaptiveCardElement> RenderFallback(winrt::IAdaptiveCardElement const& currentElement,
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

    winrt::Windows::UI::Xaml::UIElement
    AddSeparatorIfNeeded(int& currentElement,
                         winrt::IAdaptiveCardElement const& element,
                         winrt::AdaptiveCards::Rendering::Uwp::AdaptiveHostConfig const& hostConfig,
                         winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                         winrt::Panel const& parentPanel);

    void SetAutoImageSize(winrt::Windows::UI::Xaml::FrameworkElement const& imageControl,
                          winrt::IInspectable const& parentElement,
                          winrt::BitmapSource const& imageSource,
                          bool setVisible);

    void ApplyMarginToXamlElement(winrt::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig const& hostConfig,
                                  winrt::Windows::UI::Xaml::IFrameworkElement const& element);

    SeparatorParemeters GetSeparatorParameters(winrt::IAdaptiveCardElement const& element,
                                               winrt::AdaptiveCards::Rendering::Uwp::AdaptiveHostConfig const& hostConfig);
}
