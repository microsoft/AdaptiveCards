// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.WinUI3.h"
#include "WholeItemsPanel.h"
#include <type_traits>

namespace AdaptiveCards::Rendering::WinUI3::XamlHelpers
{
    namespace rtrender = winrt::AdaptiveCards::Rendering::WinUI3;
    namespace rtom = winrt::AdaptiveCards::ObjectModel::WinUI3;
    namespace rtxaml = winrt::Windows::UI::Xaml;

    inline rtxaml::Media::Brush GetSolidColorBrush(winrt::Windows::UI::Color const& color)
    {
        rtxaml::Media::SolidColorBrush solidColorBrush;
        solidColorBrush.Color(color);
        return solidColorBrush;
    }

    void SetStyleFromResourceDictionary(rtrender::AdaptiveRenderContext const& renderContext,
                                        winrt::hstring const& resourceName,
                                        rtxaml::FrameworkElement frameworkElement);

    rtxaml::UIElement CreateSeparator(rtrender::AdaptiveRenderContext const& renderContext,
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

    void SetSeparatorVisibility(rtxaml::Controls::Panel const& parentPanel);

    void HandleColumnWidth(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveColumn const& column,
                           bool isVisible,
                           winrt::Windows::UI::Xaml::Controls::ColumnDefinition const& columnDefinition);

    void HandleTableColumnWidth(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTableColumnDefinition const& column,
                                winrt::Windows::UI::Xaml::Controls::ColumnDefinition const& columnDefinition);

    template<typename T>
    void AppendXamlElementToPanel(T const& xamlElement,
                                  rtxaml::Controls::Panel const& panel,
                                  rtom::HeightType heightType = rtom::HeightType::Auto)
    {
        if (!xamlElement)
        {
            return;
        }

        auto elementToAppend = xamlElement.as<rtxaml::UIElement>();
        panel.Children().Append(elementToAppend);

        if (heightType == rtom::HeightType::Stretch)
        {
            // TODO: is this the right way?
            // TODO: can we peek innards right away?
            if (const auto wholeItemsPanel = panel.try_as<rtrender::WholeItemsPanel>())
            {
                auto wholeItemsPanelImpl = peek_innards<rtrender::implementation::WholeItemsPanel>(wholeItemsPanel);
                wholeItemsPanelImpl->AddElementToStretchablesList(elementToAppend);
            }
        }
    }

    template<typename T> void SetToggleValue(T const& item, bool isChecked)
    {
        // TODO: compiling fails at AdaptiveToggleInputRenderer.cpp(66)
        // static_assert(std::is_base_of<winrt::Windows::UI::Xaml::Controls::Primitives::ToggleButton>, T > ::value, "T
        // must inherit from ToggleButton");
        // TODO: do we want static asserts? or is it fine with compilers catching misusages?

        auto toggleButton =
            item.as<winrt::Windows::UI::Xaml::Controls::Primitives::ToggleButton>(); // TODO: I don't think we need this cast, all
                                                                                     // toggleButton descendabts have isChecked() exposed, right?
        toggleButton.IsChecked(isChecked);
    }

    template<typename T> bool GetToggleValue(T const& item)
    {
        // TODO: InputValue613 failes to compile, why?
        /*static_assert(std::is_base_of<winrt::Windows::UI::Xaml::Controls::Primitives::ToggleButton, T > ::value, "T must inherit from ToggleButton");*/
        auto toggleButton =
            item.as<winrt::Windows::UI::Xaml::Controls::Primitives::ToggleButton>(); // TODO: I don't think we need this cast, all
                                                                                     // toggleButton descendants have isChecked() exposed, right?

        return GetValueFromRef(toggleButton.IsChecked(), false);
    }

    template<typename T> void SetContent(T const& item, winrt::hstring const& contentString)
    {
        // TODO: Do I need this here? should it be simply ContentControl? that should be enough, right?
        /* static_assert(std::is_base_of<winrt::Windows::UI::Xaml::Controls::ToggleButton, T > ::value, "T must inherit from ContenControl");*/
        SetContent(item, contentString, false);
    }

    template<typename T> void SetContent(T const& item, winrt::hstring const& contentString, bool wrap)
    {
        // TODO: compiling failing as ToggleInputRenderer(52)
        /*  static_assert(std::is_base_of<winrt::Windows::UI::Xaml::Controls::ToggleButton, T > ::value, "T must inherit from ToggleButton");*/
        rtxaml::Controls::TextBlock content{};
        content.Text(contentString);

        if (wrap)
        {
            content.TextWrapping(rtxaml::TextWrapping::WrapWholeWords);
        }

        if (const auto contentControl = item.try_as<rtxaml::Controls::ContentControl>())
        {
            contentControl.Content(content);
        }
    }

    rtom::ContainerStyle HandleStylingAndPadding(rtom::IAdaptiveContainerBase const& adaptiveContainer,
                                                 rtxaml::Controls::Border const& containerBorder,
                                                 rtrender::AdaptiveRenderContext const& renderContext,
                                                 rtrender::AdaptiveRenderArgs renderArgs);

    bool SupportsInteractivity(rtrender::AdaptiveHostConfig const& hostConfig);

    template<typename T>
    void SetVerticalContentAlignmentToChildren(T const& container, rtom::VerticalContentAlignment verticalContentAlignment)
    {
        if (const auto containerAsPanel = container.try_as<rtrender::WholeItemsPanel>())
        {
            // TODO: can we peek innards right away?
            auto containerAsPanelImpl = peek_innards<rtrender::implementation::WholeItemsPanel>(containerAsPanel);
            containerAsPanelImpl->SetVerticalContentAlignment(verticalContentAlignment);
        }
    }

    winrt::Windows::UI::Xaml::UIElement
    RenderInputLabel(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveInputElement const& adaptiveInputElement,
                     winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                     winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);

    winrt::Windows::UI::Xaml::UIElement
    RenderInputErrorMessage(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveInputElement const& adaptiveInputElement,
                            winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext);

    winrt::Windows::UI::Xaml::Controls::Border
    CreateValidationBorder(winrt::Windows::UI::Xaml::UIElement const& childElement,
                           winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext);

    winrt::Windows::UI::Xaml::UIElement
    HandleLabelAndErrorMessage(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveInputElement const& adaptiveInput,
                               winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                               winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs,
                               winrt::Windows::UI::Xaml::UIElement const& inputLayout);

    std::tuple<winrt::Windows::UI::Xaml::UIElement, winrt::Windows::UI::Xaml::Controls::Border>
    HandleInputLayoutAndValidation(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveInputElement const& adaptiveInput,
                                   winrt::Windows::UI::Xaml::UIElement const& inputUIElement,
                                   bool hasTypeSpecificValidation,
                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                                   bool ifValidationBorderIsNeeded = true);

    void AddHandledTappedEvent(winrt::Windows::UI::Xaml::UIElement const& uiElement);

    void ApplyBackgroundToRoot(_In_ ABI::Windows::UI::Xaml::Controls::IPanel* rootPanel,
                               _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveBackgroundImage* backgroundImage,
                               _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                               _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs);

    void ApplyBackgroundToRoot(rtxaml::Controls::Panel const& rootPanel,
                               rtom::AdaptiveBackgroundImage const& backgroundImage,
                               rtrender::AdaptiveRenderContext const& renderContext,
                               rtrender::AdaptiveRenderArgs const& renderArgs);

    void AddRenderedControl(rtxaml::UIElement const& newControl,
                            rtom::IAdaptiveCardElement const& element,
                            rtxaml::Controls::Panel const& parentPanel,
                            rtxaml::UIElement const& separator,
                            rtxaml::Controls::ColumnDefinition const& columnDefinition,
                            std::function<void(rtxaml::UIElement const& child)> childCreatedCallback);

    // TODO: come back to this function
    std::tuple<rtxaml::UIElement, rtom::IAdaptiveCardElement> RenderFallback(rtom::IAdaptiveCardElement const& currentElement,
                                                                             rtrender::AdaptiveRenderContext const& renderContext,
                                                                             rtrender::AdaptiveRenderArgs const& renderArgs);

    bool NeedsSeparator(rtom::IAdaptiveCardElement const& cardElement);

    inline void WarnFallbackString(rtrender::AdaptiveRenderContext const& renderContext, winrt::hstring const& warning)
    {
        renderContext.AddWarning(rtom::WarningStatusCode::PerformingFallback, warning);
    }

    inline void WarnForFallbackContentElement(rtrender::AdaptiveRenderContext const& renderContext,
                                              winrt::hstring const& parentElementType,
                                              winrt::hstring const& fallbackElementType)
    {
        auto warning = L"Performing fallback for element of type \"" + parentElementType +
            L"\" (fallback element type \"" + fallbackElementType + L"\")";
        WarnFallbackString(renderContext, warning);
    }

    inline void WarnForFallbackDrop(rtrender::AdaptiveRenderContext const& renderContext, winrt::hstring const& elementType)
    {
        WarnFallbackString(renderContext, L"Dropping element of type \"" + elementType + L"\" for fallback");
    }

    winrt::Windows::UI::Xaml::UIElement
    AddSeparatorIfNeeded(int& currentElement,
                         winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& element,
                         winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveHostConfig const& hostConfig,
                         winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                         winrt::Windows::UI::Xaml::Controls::Panel const& parentPanel);

    void SetAutoImageSize(winrt::Windows::UI::Xaml::FrameworkElement const& imageControl,
                          winrt::Windows::Foundation::IInspectable const& parentElement,
                          winrt::Windows::UI::Xaml::Media::Imaging::BitmapSource const& imageSource,
                          bool setVisible);

    void ApplyMarginToXamlElement(winrt::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig const& hostConfig,
                                  winrt::Windows::UI::Xaml::IFrameworkElement const& element);
}
