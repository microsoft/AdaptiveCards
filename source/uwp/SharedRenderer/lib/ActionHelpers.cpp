// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "ActionHelpers.h"
#include "AdaptiveHostConfig.h"
#include "AdaptiveRenderArgs.h"
#include "AdaptiveShowCardActionRenderer.h"
#include "WholeItemsPanel.h"

#ifdef USE_WINUI3
#include <winrt/Microsoft.UI.Input.h>
using InputKeyboardSource = winrt::Microsoft::UI::Input::InputKeyboardSource;
#endif

namespace AdaptiveCards::Rendering::Xaml_Rendering::ActionHelpers
{
    winrt::Thickness GetButtonMargin(winrt::AdaptiveActionsConfig const& actionsConfig)
    {
        winrt::Thickness buttonMargin{};
        const uint32_t buttonSpacing = actionsConfig.ButtonSpacing();
        const auto actionsOrientation = actionsConfig.ActionsOrientation();

        if (actionsOrientation == winrt::ActionsOrientation::Horizontal)
        {
            buttonMargin.Left = buttonMargin.Right = buttonSpacing / 2;
        }
        else
        {
            buttonMargin.Top = buttonMargin.Bottom = buttonSpacing / 2;
        }

        return buttonMargin;
    }

    void SetTooltip(winrt::hstring const& toolTipText, winrt::DependencyObject const& tooltipTarget)
    {
        if (!toolTipText.empty())
        {
            winrt::TextBlock tooltipTextBlock;
            tooltipTextBlock.Text(toolTipText);

            winrt::ToolTip toolTip;
            toolTip.Content(tooltipTextBlock);
            winrt::ToolTipService::SetToolTip(tooltipTarget, toolTip);
        }
    }

    void SetAutomationNameAndDescription(winrt::DependencyObject const& dependencyObject,
                                         winrt::hstring const& name,
                                         winrt::hstring const& description)
    {
        winrt::AutomationProperties::SetName(dependencyObject, name);
        winrt::AutomationProperties::SetFullDescription(dependencyObject, description);
    }

    void ArrangeButtonContent(winrt::hstring const& actionTitle,
                              winrt::hstring const& actionIconUrl,
                              winrt::hstring const& actionTooltip,
                              winrt::hstring const& actionAccessibilityText,
                              winrt::AdaptiveActionsConfig const& actionsConfig,
                              winrt::AdaptiveRenderContext const& renderContext,
                              winrt::ContainerStyle containerStyle,
                              winrt::AdaptiveHostConfig const& hostConfig,
                              bool allActionsHaveIcons,
                              winrt::Button const& button)
    {
        winrt::hstring title{actionTitle};
        winrt::hstring iconUrl{actionIconUrl};
        winrt::hstring tooltip{actionTooltip};
        winrt::hstring accessibilityText{actionAccessibilityText};

        winrt::hstring name{};
        winrt::hstring description{};

        if (!accessibilityText.empty())
        {
            // If we have accessibility text use that as the name and tooltip as the description
            name = accessibilityText;
            description = tooltip;
        }
        else if (!title.empty())
        {
            // If we have a title, use title as the automation name and tooltip as the description
            name = title;
            description = tooltip;
        }
        else
        {
            // If there's no title, use tooltip as the name
            name = tooltip;
        }

        if (tooltip.empty())
        {
            tooltip = title;
        }

        SetAutomationNameAndDescription(button, name, description);
        SetTooltip(tooltip, button);

        // Check if the button has an iconurl
        if (!iconUrl.empty())
        {
            // Define the alignment for the button contents
            winrt::StackPanel buttonContentsStackPanel{};

            // Create image and add it to the button
            winrt::AdaptiveImage adaptiveImage{};

            adaptiveImage.Url(iconUrl);
            adaptiveImage.HorizontalAlignment(winrt::HAlignment::Center);

            winrt::UIElement buttonIcon{nullptr};

            if (const auto elementRenderer = renderContext.ElementRenderers().Get(L"Image"))
            {
                buttonIcon = elementRenderer.Render(adaptiveImage,
                                                    renderContext,
                                                    winrt::make<winrt::implementation::AdaptiveRenderArgs>(containerStyle,
                                                                                                           buttonContentsStackPanel,
                                                                                                           nullptr));
                if (buttonIcon == nullptr)
                {
                    XamlHelpers::SetContent(button, title);
                    return;
                }
            }

            // Create title text block
            winrt::TextBlock buttonText{};
            buttonText.Text(title);
            buttonText.TextAlignment(winrt::TextAlignment::Center);
            buttonText.VerticalAlignment(winrt::VerticalAlignment::Center);

            // Handle different arrangements inside button
            auto buttonIconAsFrameworkElement = buttonIcon.as<winrt::FrameworkElement>();

            // Set icon height to iconSize(aspect ratio is automatically maintained)
            buttonIconAsFrameworkElement.Height(actionsConfig.IconSize());

            winrt::UIElement separator{nullptr};

            if (actionsConfig.IconPlacement() == winrt::IconPlacement::AboveTitle && allActionsHaveIcons)
            {
                buttonContentsStackPanel.Orientation(winrt::Orientation::Vertical);
            }
            else
            {
                buttonContentsStackPanel.Orientation(winrt::Orientation::Horizontal);

                // Only add spacing when the icon must be located at the left of the title
                uint32_t spacingSize = GetSpacingSizeFromSpacing(hostConfig, winrt::Spacing::Default);
                separator = XamlHelpers::CreateSeparator(renderContext, spacingSize, spacingSize, {0}, false);
            }

            XamlHelpers::AppendXamlElementToPanel(buttonIcon, buttonContentsStackPanel);

            // Add separator to stack panel
            if (separator)
            {
                XamlHelpers::AppendXamlElementToPanel(separator, buttonContentsStackPanel);
            }

            // Add Text to stack panel
            XamlHelpers::AppendXamlElementToPanel(buttonText, buttonContentsStackPanel);

            // Finally, put the stack panel inside the final button
            button.Content(buttonContentsStackPanel);
        }
        else
        {
            XamlHelpers::SetContent(button, title);
        }
    }

    void HandleActionStyling(winrt::IAdaptiveActionElement const& adaptiveActionElement,
                             winrt::FrameworkElement const& buttonFrameworkElement,
                             bool isOverflowActionButton,
                             winrt::AdaptiveRenderContext const& renderContext)
    {
        winrt::hstring actionSentiment{};
        if (adaptiveActionElement)
        {
            actionSentiment = adaptiveActionElement.Style();
        }

        auto resourceDictionary = renderContext.OverrideStyles();

        auto contextImpl = peek_innards<winrt::implementation::AdaptiveRenderContext>(renderContext);

        // If we have an overflow style apply it, otherwise we'll fall back on the default button styling
        if (isOverflowActionButton)
        {
            if (const auto overflowActionStyle =
                    XamlHelpers::TryGetResourceFromResourceDictionaries(resourceDictionary, L"Adaptive.Action.Overflow").try_as<winrt::Style>())
            {
                buttonFrameworkElement.Style(overflowActionStyle);
            }
        }

        if (actionSentiment.empty() || actionSentiment == L"default")
        {
            XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Action", buttonFrameworkElement);
        }
        else if (actionSentiment == L"positive")
        {
            if (const auto positiveActionStyle =
                    XamlHelpers::TryGetResourceFromResourceDictionaries(resourceDictionary, L"Adaptive.Action.Positive").try_as<winrt::Style>())
            {
                buttonFrameworkElement.Style(positiveActionStyle);
            }
            else
            {
                // By default, set the action background color to accent color
                auto actionSentimentDictionary = contextImpl->GetDefaultActionSentimentDictionary();

                if (const auto positiveActionDefaultStyle =
                        XamlHelpers::TryGetResourceFromResourceDictionaries(actionSentimentDictionary, L"PositiveActionDefaultStyle")
                            .try_as<winrt::Style>())
                {
                    buttonFrameworkElement.Style(positiveActionDefaultStyle);
                }
            }
        }
        else if (actionSentiment == L"destructive")
        {
            if (const auto destructiveActionStyle =
                    XamlHelpers::TryGetResourceFromResourceDictionaries(resourceDictionary, L"Adaptive.Action.Destructive")
                        .try_as<winrt::Style>())
            {
                buttonFrameworkElement.Style(destructiveActionStyle);
            }
            else
            {
                // By default, set the action text color to attention color
                auto actionSentimentDictionary = contextImpl->GetDefaultActionSentimentDictionary();

                if (const auto destructiveActionDefaultStyle =
                        XamlHelpers::TryGetResourceFromResourceDictionaries(actionSentimentDictionary, L"DestructiveActionDefaultStyle")
                            .try_as<winrt::Style>())
                {
                    buttonFrameworkElement.Style(destructiveActionDefaultStyle);
                }
            }
        }
        else
        {
            winrt::hstring actionSentimentStyle = L"Adaptive.Action." + actionSentiment;
            XamlHelpers::SetStyleFromResourceDictionary(renderContext, actionSentimentStyle, buttonFrameworkElement);
        }
    }

    winrt::UIElement BuildAction(winrt::IAdaptiveActionElement const& adaptiveActionElement,
                                 winrt::AdaptiveRenderContext const& renderContext,
                                 winrt::AdaptiveRenderArgs const& renderArgs,
                                 bool isOverflowActionButton)
    {
        auto hostConfig = renderContext.HostConfig();
        auto actionsConfig = hostConfig.Actions();

        auto button = CreateButton(adaptiveActionElement);
        button.Margin(GetButtonMargin(actionsConfig));

        if (actionsConfig.ActionsOrientation() == winrt::ActionsOrientation::Horizontal)
        {
            button.HorizontalAlignment(winrt::HorizontalAlignment::Stretch);
        }
        else
        {
            winrt::HorizontalAlignment newAlignment;
            switch (actionsConfig.ActionAlignment())
            {
            case winrt::ActionAlignment::Center:
                newAlignment = winrt::HorizontalAlignment::Center;
                break;
            case winrt::ActionAlignment::Left:
                newAlignment = winrt::HorizontalAlignment::Left;
                break;
            case winrt::ActionAlignment::Right:
                newAlignment = winrt::HorizontalAlignment::Center;
                break;
            case winrt::ActionAlignment::Stretch:
                newAlignment = winrt::HorizontalAlignment::Stretch;
                break;
            }
            button.HorizontalAlignment(newAlignment);
        }

        auto containerStyle = renderArgs.ContainerStyle();
        bool allowAboveTitleIconPlacement = renderArgs.AllowAboveTitleIconPlacement();

        winrt::hstring title;
        winrt::hstring iconUrl;
        winrt::hstring tooltip;
        winrt::hstring accessibilityText;
        if (isOverflowActionButton)
        {
            auto hostConfigImpl = peek_innards<winrt::implementation::AdaptiveHostConfig>(hostConfig);
            title = hostConfigImpl->OverflowButtonText();
            accessibilityText = hostConfigImpl->OverflowButtonAccessibilityText();
        }
        else
        {
            title = adaptiveActionElement.Title();
            iconUrl = adaptiveActionElement.IconUrl();
            tooltip = adaptiveActionElement.Tooltip();
        }

        ArrangeButtonContent(title, iconUrl, tooltip, accessibilityText, actionsConfig, renderContext, containerStyle, hostConfig, allowAboveTitleIconPlacement, button);

        if (adaptiveActionElement)
        {
            auto actionInvoker = renderContext.ActionInvoker();
            auto clickToken = button.Click([adaptiveActionElement, actionInvoker](winrt::IInspectable const& /*sender*/,
                                                                                  winrt::RoutedEventArgs const& /*args*/) -> void
                                           { actionInvoker.SendActionEvent(adaptiveActionElement); });
            button.IsEnabled(adaptiveActionElement.IsEnabled());
        }

        HandleActionStyling(adaptiveActionElement, button, isOverflowActionButton, renderContext);
        return button;
    }

    bool WarnForInlineShowCard(winrt::AdaptiveRenderContext const& renderContext,
                               winrt::IAdaptiveActionElement const& action,
                               const std::wstring& warning)
    {
        if (action && (action.ActionType() == winrt::ActionType::ShowCard))
        {
            renderContext.AddWarning(winrt::WarningStatusCode::UnsupportedValue, warning);
            return true;
        }
        else
        {
            return false;
        }
    }

    void HandleKeydownForInlineAction(winrt::KeyRoutedEventArgs const& args,
                                      winrt::AdaptiveActionInvoker const& actionInvoker,
                                      winrt::IAdaptiveActionElement const& inlineAction)
    {
        if (args.Key() == winrt::VirtualKey::Enter)
        {
#ifdef USE_WINUI3
            auto const& shiftKeyState = InputKeyboardSource::GetKeyStateForCurrentThread(winrt::VirtualKey::Shift);
            auto const& controlKeyState = InputKeyboardSource::GetKeyStateForCurrentThread(winrt::VirtualKey::Control);
#else
            auto coreWindow = winrt::CoreWindow::GetForCurrentThread();

            auto const& shiftKeyState = coreWindow.GetKeyState(winrt::VirtualKey::Shift);
            auto const& controlKeyState = coreWindow.GetKeyState(winrt::VirtualKey::Control);
#endif
            if (shiftKeyState == winrt::CoreVirtualKeyStates::None &&
                controlKeyState == winrt::CoreVirtualKeyStates::None)
            {
                actionInvoker.SendActionEvent(inlineAction);
                args.Handled(true);
            }
        }
    }

    winrt::UIElement HandleInlineAction(winrt::AdaptiveRenderContext const& renderContext,
                                        winrt::AdaptiveRenderArgs const& renderArgs,
                                        winrt::UIElement const& textInputUIElement,
                                        winrt::UIElement const& textBoxParentContainer,
                                        bool isMultilineTextBox,
                                        winrt::IAdaptiveActionElement const& inlineAction)
    {
        auto hostConfig = renderContext.HostConfig();

        // Inline ShowCards are not supported for inline actions
        if (WarnForInlineShowCard(renderContext, inlineAction, L"Inline ShowCard not supported for InlineAction"))
        {
            return nullptr;
        }

        winrt::ActionType actionType = inlineAction.ActionType();
        if ((actionType == winrt::ActionType::Submit) || (actionType == winrt::ActionType::Execute))
        {
            renderContext.LinkSubmitActionToCard(inlineAction, renderArgs);
        }

        // Create a grid to hold the text box and the action button
        winrt::Grid xamlGrid{};
        auto columnDefinitions = xamlGrid.ColumnDefinitions();

        // Create the first column and add the text box to it
        winrt::ColumnDefinition textBoxColumnDefinition{};
        textBoxColumnDefinition.Width({1, winrt::GridUnitType::Star});
        columnDefinitions.Append(textBoxColumnDefinition);

        auto textBoxContainerAsFrameworkElement = textBoxParentContainer.as<winrt::FrameworkElement>();

        winrt::Grid::SetColumn(textBoxContainerAsFrameworkElement, 0);
        XamlHelpers::AppendXamlElementToPanel(textBoxContainerAsFrameworkElement, xamlGrid);

        // Create a separator column
        winrt::ColumnDefinition separatorColumnDefinition{};
        separatorColumnDefinition.Width({1.0, winrt::GridUnitType::Auto});
        columnDefinitions.Append(separatorColumnDefinition);

        const auto spacingSize = GetSpacingSizeFromSpacing(hostConfig, winrt::Spacing::Default);

        auto separator = XamlHelpers::CreateSeparator(renderContext, spacingSize, 0, {0}, false);

        auto separatorAsFrameworkElement = separator.as<winrt::FrameworkElement>();

        winrt::Grid::SetColumn(separatorAsFrameworkElement, 1);
        XamlHelpers::AppendXamlElementToPanel(separator, xamlGrid);

        // Create a column for the button

        winrt::ColumnDefinition inlineActionColumnDefinition{};
        inlineActionColumnDefinition.Width({0, winrt::GridUnitType::Auto});
        columnDefinitions.Append(inlineActionColumnDefinition);

        const auto iconUrl = inlineAction.IconUrl();

        winrt::UIElement actionUIElement{nullptr};

        if (!iconUrl.empty())
        {
            auto elementRenderers = renderContext.ElementRenderers();
            auto imageRenderer = elementRenderers.Get(L"Image");

            winrt::AdaptiveImage adaptiveImage{};

            adaptiveImage.Url(iconUrl);
            actionUIElement = imageRenderer.Render(adaptiveImage, renderContext, renderArgs);
        }
        else
        {
            // If there's no icon, just use the title text. Put it centered in a grid so it is
            // centered relative to the text box.
            winrt::TextBlock titleTextBlock{};
            titleTextBlock.Text(inlineAction.Title());
            titleTextBlock.VerticalAlignment(winrt::VerticalAlignment::Center);

            winrt::Grid titleGrid{};
            XamlHelpers::AppendXamlElementToPanel(titleTextBlock, titleGrid);

            actionUIElement = titleGrid;
        }

        // Make the action the same size as the text box
        textBoxContainerAsFrameworkElement.Loaded(
            [actionUIElement, textBoxContainerAsFrameworkElement](winrt::IInspectable const& /*sender*/,
                                                                  winrt::RoutedEventArgs const& /*args*/) -> void
            {
                if (const auto actionFrameworkElement = actionUIElement.as<winrt::FrameworkElement>())
                {
                    actionFrameworkElement.Height(textBoxContainerAsFrameworkElement.ActualHeight());
                    actionFrameworkElement.Visibility(winrt::Visibility::Visible);
                }
            });

        // Wrap the action in a button
        auto touchTargetUIElement = WrapInTouchTarget(nullptr,
                                                      actionUIElement,
                                                      inlineAction,
                                                      renderContext,
                                                      false,
                                                      L"Adaptive.Input.Text.InlineAction",
                                                      L"",
                                                      !iconUrl.empty());

        auto touchTargetFrameworkElement = touchTargetUIElement.as<winrt::FrameworkElement>();

        // Align to bottom so the icon stays with the bottom of the text box as it grows in the multiline case
        touchTargetFrameworkElement.VerticalAlignment(winrt::VerticalAlignment::Bottom);

        // Add the action to the column
        winrt::Grid::SetColumn(touchTargetFrameworkElement, 2);
        XamlHelpers::AppendXamlElementToPanel(touchTargetFrameworkElement, xamlGrid);

        // If this isn't a multiline input, enter should invoke the action

        if (!isMultilineTextBox)
        {
            auto actionInvoker = renderContext.ActionInvoker();

            textInputUIElement.KeyDown(
                [actionInvoker, inlineAction](winrt::IInspectable const& /*sender*/, winrt::KeyRoutedEventArgs const& args) -> void
                { ActionHelpers::HandleKeydownForInlineAction(args, actionInvoker, inlineAction); });
        }

        return xamlGrid;
    }

    winrt::UIElement WrapInTouchTarget(winrt::IAdaptiveCardElement const& adaptiveCardElement,
                                       winrt::UIElement const& elementToWrap,
                                       winrt::IAdaptiveActionElement const& action,
                                       winrt::AdaptiveRenderContext const& renderContext,
                                       bool fullWidth,
                                       const std::wstring& style,
                                       winrt::hstring const& altText,
                                       bool allowTitleAsTooltip)
    {
        auto hostConfig = renderContext.HostConfig();

        if (ActionHelpers::WarnForInlineShowCard(renderContext, action, L"Inline ShowCard not supported for SelectAction"))
        {
            // Was inline show card, so don't wrap the element and just return
            return elementToWrap;
        }

        auto button = CreateButton(action);
        button.Content(elementToWrap);

        uint32_t cardPadding = 0;
        if (fullWidth)
        {
            cardPadding = hostConfig.Spacing().Padding();
        }

        // We want the hit target to equally split the vertical space above and below the current item.
        // However, all we know is the spacing of the current item, which only applies to the spacing above.
        // We don't know what the spacing of the NEXT element will be, so we can't calculate the correct spacing
        // below. For now, we'll simply assume the bottom spacing is the same as the top. NOTE: Only apply spacings
        // (padding, margin) for adaptive card elements to avoid adding spacings to card-level selectAction.
        if (adaptiveCardElement)
        {
            auto elementSpacing = adaptiveCardElement.Spacing();
            uint32_t spacingSize = GetSpacingSizeFromSpacing(hostConfig, elementSpacing);

            double topBottomPadding = spacingSize / 2.0;

            // For button padding, we apply the cardPadding and topBottomPadding (and then we negate these in the margin)
            button.Padding({(double)cardPadding, topBottomPadding, (double)cardPadding, topBottomPadding});

            double negativeCardMargin = cardPadding * -1.0;
            double negativeTopBottomMargin = topBottomPadding * -1.0;

            button.Margin({negativeCardMargin, negativeTopBottomMargin, negativeCardMargin, negativeTopBottomMargin});
        }

        // Style the hit target button
        XamlHelpers::SetStyleFromResourceDictionary(renderContext, {style.c_str()}, button);

        // Determine tooltip, automation name, and automation description
        winrt::hstring tooltip{}, name{}, description{};
        if (action)
        {
            // If we have an action, get it's title and tooltip.
            winrt::hstring title = action.Title();
            tooltip = action.Tooltip();

            if (!title.empty())
            {
                // If we have a title, use title as the name and tooltip as the description
                name = title;
                description = tooltip;

                if (tooltip.empty() && allowTitleAsTooltip)
                {
                    // If we don't have a tooltip, set the title to the tooltip if we're allowed
                    tooltip = title;
                }
            }
            else
            {
                // If we don't have a title, use the tooltip as the name
                name = tooltip;
            }

            // Disable the select action button if necessary
            button.IsEnabled(action.IsEnabled());
        }
        else if (!altText.empty())
        {
            // If we don't have an action but we've been passed altText, use that for name and tooltip
            name = altText;
            tooltip = altText;
        }

        SetAutomationNameAndDescription(button, name, description);
        SetTooltip(tooltip, button);

        // can we do explicit check? or need to call check_pointer()?
        if (action)
        {
            WireButtonClickToAction(button, action, renderContext);
        }

        return button;
    }

    void WireButtonClickToAction(winrt::Button const& button,
                                 winrt::IAdaptiveActionElement const& action,
                                 winrt::AdaptiveRenderContext const& renderContext)
    {
        auto actionInvoker = renderContext.ActionInvoker();

        auto token = button.Click([action, actionInvoker](winrt::IInspectable const&, winrt::RoutedEventArgs const&)
                                  { actionInvoker.SendActionEvent(action); });
    }

    winrt::UIElement HandleSelectAction(winrt::IAdaptiveCardElement const& adaptiveCardElement,
                                        winrt::IAdaptiveActionElement const& selectAction,
                                        winrt::AdaptiveRenderContext const& renderContext,
                                        winrt::UIElement const& uiElement,
                                        bool supportsInteractivity,
                                        bool fullWidthTouchTarget)
    {
        if (selectAction && supportsInteractivity)
        {
            return WrapInTouchTarget(adaptiveCardElement, uiElement, selectAction, renderContext, fullWidthTouchTarget, L"Adaptive.SelectAction", L"", true);
        }
        else
        {
            if (selectAction)
            {
                renderContext.AddWarning(winrt::WarningStatusCode::InteractivityNotSupported,
                                         {L"SelectAction present, but Interactivity is not supported"});
            }

            return uiElement;
        }
    }

    void BuildActions(winrt::AdaptiveCard const& adaptiveCard,
                      winrt::IVector<winrt::IAdaptiveActionElement> const& children,
                      winrt::Panel const& bodyPanel,
                      bool insertSeparator,
                      winrt::AdaptiveRenderContext const& renderContext,
                      winrt::AdaptiveRenderArgs const& renderArgs)
    {
        auto hostConfig = renderContext.HostConfig();
        auto actionsConfig = hostConfig.Actions();
        if (insertSeparator)
        {
            auto spacingSize = GetSpacingSizeFromSpacing(hostConfig, actionsConfig.Spacing());
            auto separator = XamlHelpers::CreateSeparator(renderContext, spacingSize, 0u, winrt::Windows::UI::Color{0});
            XamlHelpers::AppendXamlElementToPanel(separator, bodyPanel);
        }

        auto actionSetControl = BuildActionSetHelper(adaptiveCard, nullptr, children, renderContext, renderArgs);
        XamlHelpers::AppendXamlElementToPanel(actionSetControl, bodyPanel);
    }

    winrt::Button CreateFlyoutButton(winrt::AdaptiveRenderContext renderContext, winrt::AdaptiveRenderArgs renderArgs)
    {
        // Create an action button
        auto overflowButtonAsUIElement = BuildAction(nullptr, renderContext, renderArgs, true);

        // Create a menu flyout for the overflow button
        if (const auto overflowButton = overflowButtonAsUIElement.try_as<winrt::Button>())
        {
            overflowButton.Flyout(winrt::MenuFlyout{});
            return overflowButton;
        }

        return nullptr;
    }

    winrt::UIElement AddOverflowFlyoutItem(winrt::IAdaptiveActionElement const& action,
                                           winrt::Button const& overflowButton,
                                           winrt::AdaptiveCard const& adaptiveCard,
                                           winrt::AdaptiveActionSet const& adaptiveActionSet,
                                           winrt::Panel const& showCardPanel,
                                           winrt::AdaptiveRenderContext const& renderContext,
                                           winrt::AdaptiveRenderArgs const& renderArgs)
    {
        // Get the flyout items vector
        auto buttonWithFlyout = overflowButton.as<winrt::IButtonWithFlyout>();
        auto menuFlyout = buttonWithFlyout.Flyout().as<winrt::MenuFlyout>();
        auto flyoutItems = menuFlyout.Items();

        // Create a flyout item
        winrt::MenuFlyoutItem flyoutItem{};

        // Set the title
        flyoutItem.Text(action.Title());

        // Set the tooltip
        SetTooltip(action.Tooltip(), flyoutItem);

        // Hook the menu item up to the action invoker
        winrt::IAdaptiveActionElement actionParam{action};
        winrt::AdaptiveActionInvoker actionInvoker = renderContext.ActionInvoker();

        flyoutItem.Click([actionParam, actionInvoker](winrt::IInspectable const&, winrt::RoutedEventArgs const)
                         { return actionInvoker.SendActionEvent(actionParam); });

        winrt::ActionType actionType = action.ActionType();
        if (actionType == winrt::ActionType::ShowCard)
        {
            // Build the inline show card.
            BuildInlineShowCard(adaptiveCard, adaptiveActionSet, action, showCardPanel, renderContext, renderArgs);
        }

        // Add the new menu item to the vector
        flyoutItems.Append(flyoutItem);

        return flyoutItem;
    }

    void BuildInlineShowCard(winrt::AdaptiveCard const& adaptiveCard,
                             winrt::AdaptiveActionSet const& adaptiveActionSet,
                             winrt::IAdaptiveActionElement const& action,
                             winrt::Panel const& showCardsPanel,
                             winrt::AdaptiveRenderContext const& renderContext,
                             winrt::AdaptiveRenderArgs const& renderArgs)
    {
        auto hostConfig = renderContext.HostConfig();
        auto actionsConfig = hostConfig.Actions();
        auto showCardActionConfig = actionsConfig.ShowCard();
        auto showCardActionMode = showCardActionConfig.ActionMode();
        // ActionMode enum exists both in Rendering in ObjectModel namespaces. When the time permits, fix it.
        if (showCardActionMode == winrt::AdaptiveCards::Rendering::Xaml_Rendering::ActionMode::Inline)
        {
            // Get the card to be shown
            auto actionAsShowCardAction = action.as<winrt::AdaptiveShowCardAction>();
            auto showCard = actionAsShowCardAction.Card();

            // Render the card and add it to the show card panel
            auto uiShowCard = winrt::implementation::AdaptiveShowCardActionRenderer::BuildShowCard(
                showCard, renderContext, renderArgs, (adaptiveActionSet == nullptr));
            XamlHelpers::AppendXamlElementToPanel(uiShowCard, showCardsPanel);

            // Register the show card with the render context
            auto contextImpl = peek_innards<winrt::implementation::AdaptiveRenderContext>(renderContext);

            if (adaptiveActionSet)
            {
                contextImpl->AddInlineShowCard(adaptiveActionSet, actionAsShowCardAction, uiShowCard, renderArgs);
            }
            else
            {
                contextImpl->AddInlineShowCard(adaptiveCard, actionAsShowCardAction, uiShowCard, renderArgs);
            }
        }
    }

    winrt::UIElement CreateActionButtonInActionSet(winrt::AdaptiveCard const& adaptiveCard,
                                                   winrt::AdaptiveActionSet const& adaptiveActionSet,
                                                   winrt::IAdaptiveActionElement const& actionToCreate,
                                                   uint32_t columnIndex,
                                                   winrt::Panel const& actionsPanel,
                                                   winrt::Panel const& showCardPanel,
                                                   winrt::IVector<winrt::ColumnDefinition> const& columnDefinitions,
                                                   winrt::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveRenderArgs const& renderArgs)
    {
        // Render each action using the registered renderer
        winrt::IAdaptiveActionElement action = actionToCreate;
        auto actionType = action.ActionType();
        auto actionRegistration = renderContext.ActionRenderers();

        winrt::IAdaptiveActionRenderer renderer;
        while (!renderer)
        {
            auto actionTypeString = action.ActionTypeString();
            renderer = actionRegistration.Get(actionTypeString);
            if (!renderer)
            {
                switch (action.FallbackType())
                {
                case winrt::FallbackType::Drop:
                    XamlHelpers::WarnForFallbackDrop(renderContext, actionTypeString);
                    return nullptr;

                case winrt::FallbackType::Content:
                    action = action.FallbackContent();
                    actionType = action.ActionType();
                    XamlHelpers::WarnForFallbackContentElement(renderContext, actionTypeString, action.ActionTypeString());
                    break; // Go again

                case winrt::FallbackType::None:
                default:
                    throw winrt::hresult_error(E_FALLBACK_NOT_FOUND);
                }
            }
        }

        winrt::UIElement actionControl = renderer.Render(action, renderContext, renderArgs);

        XamlHelpers::AppendXamlElementToPanel(actionControl, actionsPanel);

        if (columnDefinitions)
        {
            // If using the equal width columns, we'll add a column and assign the column
            winrt::ColumnDefinition columnDefinition;
            columnDefinition.Width({0, winrt::GridUnitType::Auto});
            columnDefinitions.Append(columnDefinition);
            winrt::Grid::SetColumn(actionControl.as<winrt::FrameworkElement>(), columnIndex);
        }

        if (actionType == winrt::ActionType::ShowCard)
        {
            // Build the inline show card.
            BuildInlineShowCard(adaptiveCard, adaptiveActionSet, action, showCardPanel, renderContext, renderArgs);
        }

        return actionControl;
    }

    winrt::UIElement BuildActionSetHelper(winrt::AdaptiveCard const& adaptiveCard,
                                          winrt::AdaptiveActionSet const& adaptiveActionSet,
                                          winrt::IVector<winrt::IAdaptiveActionElement> const& children,
                                          winrt::AdaptiveRenderContext const& renderContext,
                                          winrt::AdaptiveRenderArgs const& renderArgs)
    {
        auto hostConfig = renderContext.HostConfig();
        auto actionsConfig = hostConfig.Actions();

        winrt::ActionAlignment actionAlignment = actionsConfig.ActionAlignment();
        winrt::ActionsOrientation actionsOrientation = actionsConfig.ActionsOrientation();

        // Declare the panel that will host the buttons
        winrt::Panel actionsPanel{nullptr};
        winrt::IVector<winrt::ColumnDefinition> columnDefinitions;

        if (actionAlignment == winrt::ActionAlignment::Stretch && actionsOrientation == winrt::ActionsOrientation::Horizontal)
        {
            // If stretch alignment and orientation is horizontal, we use a grid with equal column widths to achieve
            // stretch behavior. For vertical orientation, we'll still just use a stack panel since the concept of
            // stretching buttons height isn't really valid, especially when the height of cards are typically dynamic.
            winrt::Grid actionsGrid;
            columnDefinitions = actionsGrid.ColumnDefinitions();
            actionsPanel = actionsGrid;
        }
        else
        {
            // Create a stack panel for the action buttons
            winrt::StackPanel actionStackPanel{};

            const auto uiOrientation = (actionsOrientation == winrt::ActionsOrientation::Horizontal) ?
                winrt::Orientation::Horizontal :
                winrt::Orientation::Vertical;

            actionStackPanel.Orientation(uiOrientation);

            switch (actionAlignment)
            {
            case winrt::ActionAlignment::Center:
                actionStackPanel.HorizontalAlignment(winrt::HorizontalAlignment::Center);
                break;
            case winrt::ActionAlignment::Left:
                actionStackPanel.HorizontalAlignment(winrt::HorizontalAlignment::Left);
                break;
            case winrt::ActionAlignment::Right:
                actionStackPanel.HorizontalAlignment(winrt::HorizontalAlignment::Right);
                break;
            case winrt::ActionAlignment::Stretch:
                actionStackPanel.HorizontalAlignment(winrt::HorizontalAlignment::Stretch);
                break;
            }

            // Add the action buttons to the stack panel
            actionsPanel = actionStackPanel;
        }

        auto buttonMargin = GetButtonMargin(actionsConfig);
        if (actionsOrientation == winrt::ActionsOrientation::Horizontal)
        {
            // Negate the spacing on the sides so the left and right buttons are flush on the side.
            // We do NOT remove the margin from the individual button itself, since that would cause
            // the equal columns stretch behavior to not have equal columns (since the first and last
            // button would be narrower without the same margins as its peers).
            actionsPanel.Margin({-buttonMargin.Left, 0, -buttonMargin.Right, 0});
        }
        else
        {
            // Negate the spacing on the top and bottom so the first and last buttons don't have extra padding
            actionsPanel.Margin({0, -buttonMargin.Top, 0, -buttonMargin.Bottom});
        }

        // Get the max number of actions and check the host config to confirm whether we render actions beyond the max in the overflow menu
        auto maxActions = actionsConfig.MaxActions();

        auto hostConfigImpl = peek_innards<winrt::implementation::AdaptiveHostConfig>(hostConfig);
        bool overflowMaxActions = hostConfigImpl->OverflowMaxActions();

        winrt::StackPanel showCardsStackPanel{};
        winrt::Button overflowButton{nullptr};
        uint32_t currentButtonIndex{0};

        for (auto action : children)
        {
            auto mode = action.Mode();
            winrt::UIElement actionControl{nullptr};

            if (action.IconUrl().empty())
            {
                renderArgs.AllowAboveTitleIconPlacement(false);
            }

            if (currentButtonIndex < maxActions && mode == winrt::AdaptiveCards::ObjectModel::Xaml_OM::ActionMode::Primary)
            {
                try
                {
                    // If we have fewer than the maximum number of actions and this action's mode is primary, make a button
                    actionControl = CreateActionButtonInActionSet(adaptiveCard,
                                                                  adaptiveActionSet,
                                                                  action,
                                                                  currentButtonIndex,
                                                                  actionsPanel,
                                                                  showCardsStackPanel,
                                                                  columnDefinitions,
                                                                  renderContext,
                                                                  renderArgs);

                    currentButtonIndex++;
                }
                catch (winrt::hresult_error const& ex)
                {
                    // We want to continue if the error is E_FALLBACK_NOT_FOUND
                    // There was no fallback mechanism for this action, but we need to render the rest of the ActionSet
                    if (ex.code() != E_FALLBACK_NOT_FOUND)
                    {
                        throw ex;
                    }
                }
            }
            else if (currentButtonIndex >= maxActions &&
                     (mode == winrt::AdaptiveCards::ObjectModel::Xaml_OM::ActionMode::Primary) && !overflowMaxActions)
            {
                // If we have more primary actions than the max actions and we're not allowed to overflow them just set a warning and continue
                renderContext.AddWarning(winrt::WarningStatusCode::MaxActionsExceeded,
                                         {L"Some actions were not rendered due to exceeding the maximum number of actions allowed"});
                return S_OK;
            }
            else
            {
                // If the action's mode is secondary or we're overflowing max actions, create a flyout item on the overflow menu
                if (overflowButton == nullptr)
                {
                    // Create a button for the overflow menu if it doesn't exist yet
                    overflowButton = CreateFlyoutButton(renderContext, renderArgs);
                }

                // Add a flyout item to the overflow menu
                AddOverflowFlyoutItem(action, overflowButton, adaptiveCard, adaptiveActionSet, showCardsStackPanel, renderContext, renderArgs);

                // If this was supposed to be a primary action but it got overflowed due to max actions, add a warning
                if (mode == winrt::AdaptiveCards::ObjectModel::Xaml_OM::ActionMode::Primary)
                {
                    renderContext.AddWarning(winrt::WarningStatusCode::MaxActionsExceeded,
                                             {L"Some actions were moved to an overflow menu due to exceeding the maximum number of actions allowed"});
                }
            }
        }

        // Lastly add the overflow button itself to the action panel
        if (overflowButton)
        {
            // If using equal width columns, add another column and assign the it to the overflow button
            if (columnDefinitions)
            {
                winrt::ColumnDefinition columnDefinition{};
                columnDefinition.Width({1.0, winrt::GridUnitType::Star});
                columnDefinitions.Append(columnDefinition);
                winrt::Grid::SetColumn(overflowButton, currentButtonIndex);
            }

            // Add the overflow button to the panel
            XamlHelpers::AppendXamlElementToPanel(overflowButton, actionsPanel);

            // Register the overflow button with the render context

            if (const auto contextImpl = peek_innards<winrt::implementation::AdaptiveRenderContext>(renderContext))
            {
                if (adaptiveActionSet)
                {
                    contextImpl->AddOverflowButton(adaptiveActionSet, overflowButton);
                }
                else
                {
                    contextImpl->AddOverflowButton(adaptiveCard, overflowButton);
                }
            }
        }

        // Reset icon placement value
        renderArgs.AllowAboveTitleIconPlacement(false);
        XamlHelpers::SetStyleFromResourceDictionary(renderContext, {L"Adaptive.Actions"}, actionsPanel);

        winrt::StackPanel actionPanel;

        // Add buttons and show cards to panel
        XamlHelpers::AppendXamlElementToPanel(actionsPanel, actionPanel);
        XamlHelpers::AppendXamlElementToPanel(showCardsStackPanel, actionPanel);

        return actionPanel;
    }

    winrt::Button CreateButton(winrt::IAdaptiveActionElement const& action)
    {
        winrt::Button button = winrt::Button{};
        if (action && (action.Role() != winrt::ActionRole::Button))
        {
            SetAutomationType(action.Role(), button);
        }
        return button;
    }

    void SetAutomationType(winrt::ActionRole const& actionRole, winrt::Button const& button)
    {
        // Default to button role
        winrt::AutomationControlType roleType = winrt::AutomationControlType::Button;
        switch (actionRole)
        {
            case winrt::ActionRole::Link:
                roleType = winrt::AutomationControlType::Hyperlink;
                break;
            case winrt::ActionRole::Tab:
                roleType = winrt::AutomationControlType::Tab;
                break;
            case winrt::ActionRole::Menu:
                roleType = winrt::AutomationControlType::Menu;
                break;
            case winrt::ActionRole::MenuItem:
                roleType = winrt::AutomationControlType::MenuItem;
                break;
        }
        winrt::AutomationProperties::SetAutomationControlType(button, roleType);
    }
}
