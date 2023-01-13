// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Xaml_Rendering::ActionHelpers
{
    winrt::UIElement BuildAction(winrt::IAdaptiveActionElement const& adaptiveActionElement,
                                                    winrt::AdaptiveRenderContext const& renderContext,
                                                    winrt::AdaptiveRenderArgs const& renderArgs,
                                                    bool isOverflowActionButton);

    winrt::Thickness GetButtonMargin(winrt::AdaptiveActionsConfig const& actionsConfig);

    void SetTooltip(winrt::hstring const& toolTipText, winrt::DependencyObject const& tooltipTarget);

    void SetAutomationNameAndDescription(winrt::DependencyObject const& dependencyObject,
                                         winrt::hstring const& name,
                                         winrt::hstring const& description);

    void ArrangeButtonContent(winrt::hstring const& actionTitle,
                              winrt::hstring const& actionIconUrl,
                              winrt::hstring const& actionTooltip,
                              winrt::hstring const& actionAccessibilityText,
                              winrt::AdaptiveActionsConfig const& actionsConfig,
                              winrt::AdaptiveRenderContext const& renderContext,
                              winrt::ContainerStyle containerStyle,
                              winrt::AdaptiveHostConfig const& hostConfig,
                              bool allActionsHaveIcons,
                              winrt::Button const& button);

    void HandleActionStyling(winrt::IAdaptiveActionElement const& adaptiveActionElement,
                             winrt::FrameworkElement const& buttonFrameworkElement,
                             bool isOverflowActionButton,
                             winrt::AdaptiveRenderContext const& renderContext);

    bool WarnForInlineShowCard(winrt::AdaptiveRenderContext const& renderContext,
                               winrt::IAdaptiveActionElement const& action,
                               const std::wstring& warning);

    void HandleKeydownForInlineAction(winrt::KeyRoutedEventArgs const& args,
                                      winrt::AdaptiveActionInvoker const& actionInvoker,
                                      winrt::IAdaptiveActionElement const& inlineAction);

    winrt::UIElement HandleInlineAction(winrt::AdaptiveRenderContext const& renderContext,
                                                           winrt::AdaptiveRenderArgs const& renderArgs,
                                                           winrt::UIElement const& textInputUIElement,
                                                           winrt::UIElement const& textBoxParentContainer,
                                                           bool isMultilineTextBox,
                                                           winrt::IAdaptiveActionElement const& inlineAction);

    void WireButtonClickToAction(winrt::Button const& button,
                                 winrt::IAdaptiveActionElement const& action,
                                 winrt::AdaptiveRenderContext const& renderContext);

    winrt::UIElement WrapInTouchTarget(winrt::IAdaptiveCardElement const& adaptiveCardElement,
                                                          winrt::UIElement const& elementToWrap,
                                                          winrt::IAdaptiveActionElement const& action,
                                                          winrt::AdaptiveRenderContext const& renderContext,
                                                          bool fullWidth,
                                                          const std::wstring& style,
                                                          winrt::hstring const& altText,
                                                          bool allowTitleAsTooltip);

    winrt::UIElement HandleSelectAction(winrt::IAdaptiveCardElement const& adaptiveCardElement,
                                                           winrt::IAdaptiveActionElement const& selectAction,
                                                           winrt::AdaptiveRenderContext const& renderContext,
                                                           winrt::UIElement const& uiElement,
                                                           bool supportsInteractivity,
                                                           bool fullWidthTouchTarget);

    winrt::UIElement BuildActionSetHelper(winrt::AdaptiveCard const& adaptiveCard,
                                                             winrt::AdaptiveActionSet const& adaptiveActionSet,
                                                             winrt::IVector<winrt::IAdaptiveActionElement> const& children,
                                                             winrt::AdaptiveRenderContext const& renderContext,
                                                             winrt::AdaptiveRenderArgs const& renderArgs);

    void BuildActions(winrt::AdaptiveCard const& adaptiveCard,
                      winrt::IVector<winrt::IAdaptiveActionElement> const& children,
                      winrt::Panel const& bodyPanel,
                      bool insertSeparator,
                      winrt::AdaptiveRenderContext const& renderContext,
                      winrt::AdaptiveRenderArgs const& renderArgs);

    void BuildInlineShowCard(winrt::AdaptiveCard const& adaptiveCard,
                             winrt::AdaptiveActionSet const& adaptiveActionSet,
                             winrt::IAdaptiveActionElement const& action,
                             winrt::Panel const& showCardsPanel,
                             winrt::AdaptiveRenderContext const& renderContext,
                             winrt::AdaptiveRenderArgs const& renderArgs);

    winrt::UIElement BuildActionSetHelper(winrt::AdaptiveCard const& adaptiveCard,
                                                             winrt::AdaptiveActionSet const& adaptiveActionSet,
                                                             winrt::IVector<winrt::IAdaptiveActionElement> const& children,
                                                             winrt::AdaptiveRenderContext const& renderContext,
                                                             winrt::AdaptiveRenderArgs const& renderArgs);

    winrt::Button CreateAppropriateButton(winrt::IAdaptiveActionElement const& action);
}
