// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Xaml_Rendering::ActionHelpers
{
    winrt::xaml::UIElement BuildAction(winrt::IAdaptiveActionElement const& adaptiveActionElement,
                                                    winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                                    winrt::render_xaml::AdaptiveRenderArgs const& renderArgs,
                                       bool isOverflowActionButton);

    winrt::xaml::Thickness GetButtonMargin(winrt::render_xaml::AdaptiveActionsConfig const& actionsConfig);

    void SetTooltip(winrt::hstring const& toolTipText, winrt::xaml::DependencyObject const& tooltipTarget);

    void SetAutomationNameAndDescription(winrt::xaml::DependencyObject const& dependencyObject,
                                         winrt::hstring const& name,
                                         winrt::hstring const& description);

    void ArrangeButtonContent(winrt::hstring const& actionTitle,
                              winrt::hstring const& actionIconUrl,
                              winrt::hstring const& actionTooltip,
                              winrt::hstring const& actionAccessibilityText,
                              winrt::render_xaml::AdaptiveActionsConfig const& actionsConfig,
                              winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                              winrt::ContainerStyle containerStyle,
                              winrt::render_xaml::AdaptiveHostConfig const& hostConfig,
                              bool allActionsHaveIcons,
                              winrt::xaml_controls::Button const& button);

    void HandleActionStyling(winrt::IAdaptiveActionElement const& adaptiveActionElement,
                             winrt::xaml::FrameworkElement const& buttonFrameworkElement,
                             bool isOverflowActionButton,
                             winrt::render_xaml::AdaptiveRenderContext const& renderContext);

    bool WarnForInlineShowCard(winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                               winrt::IAdaptiveActionElement const& action,
                               const std::wstring& warning);

    void HandleKeydownForInlineAction(winrt::xaml_input::KeyRoutedEventArgs const& args,
                                      winrt::render_xaml::AdaptiveActionInvoker const& actionInvoker,
                                      winrt::IAdaptiveActionElement const& inlineAction);

    winrt::xaml::UIElement HandleInlineAction(winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                                           winrt::render_xaml::AdaptiveRenderArgs const& renderArgs,
                                              winrt::xaml::UIElement const& textInputUIElement,
                                              winrt::xaml::UIElement const& textBoxParentContainer,
                                              bool isMultilineTextBox,
                                              winrt::IAdaptiveActionElement const& inlineAction);

    void WireButtonClickToAction(winrt::xaml_controls::Button const& button,
                                 winrt::IAdaptiveActionElement const& action,
                                 winrt::render_xaml::AdaptiveRenderContext const& renderContext);

    winrt::xaml::UIElement WrapInTouchTarget(winrt::IAdaptiveCardElement const& adaptiveCardElement,
                                             winrt::xaml::UIElement const& elementToWrap,
                                             winrt::IAdaptiveActionElement const& action,
                                                          winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                             bool fullWidth,
                                             const std::wstring& style,
                                             winrt::hstring const& altText,
                                             bool allowTitleAsTooltip);

    winrt::xaml::UIElement HandleSelectAction(winrt::IAdaptiveCardElement const& adaptiveCardElement,
                                              winrt::IAdaptiveActionElement const& selectAction,
                                                           winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                              winrt::xaml::UIElement const& uiElement,
                                              bool supportsInteractivity,
                                              bool fullWidthTouchTarget);

    winrt::xaml::UIElement BuildActionSetHelper(winrt::AdaptiveCard const& adaptiveCard,
                                                winrt::AdaptiveActionSet const& adaptiveActionSet,
                                                winrt::IVector<winrt::IAdaptiveActionElement> const& children,
                                                             winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                                             winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);

    void BuildActions(winrt::AdaptiveCard const& adaptiveCard,
                      winrt::IVector<winrt::IAdaptiveActionElement> const& children,
                      winrt::xaml_controls::Panel const& bodyPanel,
                      bool insertSeparator,
                      winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                      winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);

    void BuildInlineShowCard(winrt::AdaptiveCard const& adaptiveCard,
                             winrt::AdaptiveActionSet const& adaptiveActionSet,
                             winrt::IAdaptiveActionElement const& action,
                             winrt::xaml_controls::Panel const& showCardsPanel,
                             winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                             winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);

    winrt::xaml::UIElement BuildActionSetHelper(winrt::AdaptiveCard const& adaptiveCard,
                                                winrt::AdaptiveActionSet const& adaptiveActionSet,
                                                winrt::IVector<winrt::IAdaptiveActionElement> const& children,
                                                             winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                                             winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);

    winrt::xaml_controls::Button CreateAppropriateButton(winrt::IAdaptiveActionElement const& action);
}
