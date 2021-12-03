// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Uwp::ActionHelpers
{
    winrt::Windows::UI::Xaml::UIElement BuildAction(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& adaptiveActionElement,
                                                    winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                                    winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs,
                                                    bool isOverflowActionButton);

    winrt::Windows::UI::Xaml::Thickness GetButtonMargin(winrt::AdaptiveCards::Rendering::Uwp::AdaptiveActionsConfig const& actionsConfig);

    void SetTooltip(winrt::hstring const& toolTipText, winrt::Windows::UI::Xaml::DependencyObject const& tooltipTarget);

    void SetAutomationNameAndDescription(winrt::Windows::UI::Xaml::DependencyObject const& dependencyObject,
                                         winrt::hstring const& name,
                                         winrt::hstring const& description);

    void ArrangeButtonContent(winrt::hstring const& actionTitle,
                              winrt::hstring const& actionIconUrl,
                              winrt::hstring const& actionTooltip,
                              winrt::hstring const& actionAccessibilityText,
                              winrt::AdaptiveCards::Rendering::Uwp::AdaptiveActionsConfig const& actionsConfig,
                              winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                              winrt::AdaptiveCards::ObjectModel::Uwp::ContainerStyle containerStyle,
                              winrt::AdaptiveCards::Rendering::Uwp::AdaptiveHostConfig const& hostConfig,
                              bool allActionsHaveIcons,
                              winrt::Windows::UI::Xaml::Controls::Button const& button);

    void SetMatchingHeight(winrt::Windows::UI::Xaml::FrameworkElement const& elementToChange,
                           winrt::Windows::UI::Xaml::FrameworkElement const& elementToMatch);

    void HandleActionStyling(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& adaptiveActionElement,
                             winrt::Windows::UI::Xaml::FrameworkElement const& buttonFrameworkElement,
                             bool isOverflowActionButton,
                             winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext);

    bool WarnForInlineShowCard(winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                               winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& action,
                               const std::wstring& warning);

    void HandleKeydownForInlineAction(winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& args,
                                      winrt::AdaptiveCards::Rendering::Uwp::AdaptiveActionInvoker const& actionInvoker,
                                      winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& inlineAction);

    winrt::Windows::UI::Xaml::UIElement
    HandleInlineAction(winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                       winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs,
                       winrt::Windows::UI::Xaml::UIElement const& textInputUIElement,
                       winrt::Windows::UI::Xaml::UIElement const& textBoxParentContainer,
                       bool isMultilineTextBox,
                       winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& inlineAction);

    void WireButtonClickToAction(winrt::Windows::UI::Xaml::Controls::Button const& button,
                                 winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& action,
                                 winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext);

    winrt::Windows::UI::Xaml::UIElement
    WrapInTouchTarget(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement const& adaptiveCardElement,
                      winrt::Windows::UI::Xaml::UIElement const& elementToWrap,
                      winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& action,
                      winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                      bool fullWidth,
                      const std::wstring& style,
                      winrt::hstring const& altText,
                      bool allowTitleAsTooltip);

    winrt::Windows::UI::Xaml::UIElement
    HandleSelectAction(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement const& adaptiveCardElement,
                       winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& selectAction,
                       winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                       winrt::Windows::UI::Xaml::UIElement const& uiElement,
                       bool supportsInteractivity,
                       bool fullWidthTouchTarget);

    winrt::Windows::UI::Xaml::UIElement BuildActionSetHelper(
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveCard const& adaptiveCard,
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionSet const& adaptiveActionSet,
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement> const& children,
        winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
        winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);

    void BuildActions(winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveCard const& adaptiveCard,
                      winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement> const& children,
                      winrt::Windows::UI::Xaml::Controls::Panel const& bodyPanel,
                      bool insertSeparator,
                      winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                      winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);

    void BuildInlineShowCard(winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveCard const& adaptiveCard,
                             winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionSet const& adaptiveActionSet,
                             winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& action,
                             winrt::Windows::UI::Xaml::Controls::Panel const& showCardsPanel,
                             winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                             winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);

    winrt::Windows::UI::Xaml::UIElement BuildActionSetHelper(
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveCard const& adaptiveCard,
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionSet const& adaptiveActionSet,
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement> const& children,
        winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
        winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);

    winrt::Windows::UI::Xaml::Controls::Button
    CreateAppropriateButton(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& action);
}
