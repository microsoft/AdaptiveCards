// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::WinUI3::ActionHelpers
{
    winrt::Windows::UI::Xaml::UIElement BuildAction(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement const& adaptiveActionElement,
                                                    winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                                                    winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs,
                                                    bool isOverflowActionButton);

    winrt::Windows::UI::Xaml::Thickness GetButtonMargin(winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveActionsConfig const& actionsConfig);

    void SetTooltip(winrt::hstring const& toolTipText, winrt::Windows::UI::Xaml::DependencyObject const& tooltipTarget);

    void SetAutomationNameAndDescription(winrt::Windows::UI::Xaml::DependencyObject const& dependencyObject,
                                         winrt::hstring const& name,
                                         winrt::hstring const& description);

    void ArrangeButtonContent(winrt::hstring const& actionTitle,
                              winrt::hstring const& actionIconUrl,
                              winrt::hstring const& actionTooltip,
                              winrt::hstring const& actionAccessibilityText,
                              winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveActionsConfig const& actionsConfig,
                              winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                              winrt::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle containerStyle,
                              winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveHostConfig const& hostConfig,
                              bool allActionsHaveIcons,
                              winrt::Windows::UI::Xaml::Controls::Button const& button);

    void SetMatchingHeight(winrt::Windows::UI::Xaml::FrameworkElement const& elementToChange,
                           winrt::Windows::UI::Xaml::FrameworkElement const& elementToMatch);

    void HandleActionStyling(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement const& adaptiveActionElement,
                             winrt::Windows::UI::Xaml::FrameworkElement const& buttonFrameworkElement,
                             bool isOverflowActionButton,
                             winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext);

    bool WarnForInlineShowCard(winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                               winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement const& action,
                               const std::wstring& warning);

    void HandleKeydownForInlineAction(winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& args,
                                      winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveActionInvoker const& actionInvoker,
                                      winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement const& inlineAction);

    winrt::Windows::UI::Xaml::UIElement
    HandleInlineAction(winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                       winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs,
                       winrt::Windows::UI::Xaml::UIElement const& textInputUIElement,
                       winrt::Windows::UI::Xaml::UIElement const& textBoxParentContainer,
                       bool isMultilineTextBox,
                       winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement const& inlineAction);

    void WireButtonClickToAction(winrt::Windows::UI::Xaml::Controls::Button button,
                                 winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement action,
                                 winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext renderContext);

    winrt::Windows::UI::Xaml::UIElement
    WrapInTouchTarget(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& adaptiveCardElement,
                      winrt::Windows::UI::Xaml::UIElement const& elementToWrap,
                      winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement const& action,
                      winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                      bool fullWidth,
                      const std::wstring& style,
                      winrt::hstring const& altText,
                      bool allowTitleAsTooltip);

    winrt::Windows::UI::Xaml::UIElement
    HandleSelectAction(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& adaptiveCardElement,
                       winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement const& selectAction,
                       winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                       winrt::Windows::UI::Xaml::UIElement const& uiElement,
                       bool supportsInteractivity,
                       bool fullWidthTouchTarget);

    winrt::Windows::UI::Xaml::UIElement BuildActionSetHelper(
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveCard const& adaptiveCard,
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionSet const& adaptiveActionSet,
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement> const& children,
        winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
        winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);

    void BuildActions(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveCard const& adaptiveCard,
                      winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement> const& children,
                      winrt::Windows::UI::Xaml::Controls::Panel const& bodyPanel,
                      bool insertSeparator,
                      winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                      winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);

    void BuildInlineShowCard(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveCard const& adaptiveCard,
                             winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionSet const& adaptiveActionSet,
                             winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement const& action,
                             winrt::Windows::UI::Xaml::Controls::Panel const& showCardsPanel,
                             winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                             winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);

    winrt::Windows::UI::Xaml::UIElement BuildActionSetHelper(
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveCard const& adaptiveCard,
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionSet const& adaptiveActionSet,
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement> const& children,
        winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
        winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);

    winrt::Windows::UI::Xaml::Controls::Button
    CreateAppropriateButton(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement const& action);
}
