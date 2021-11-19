// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "ActionHelpers.h"
#include "AdaptiveRenderArgs.h"
#include "AdaptiveShowCardActionRenderer.h"
#include "LinkButton.h"
#include "AdaptiveHostConfig.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Automation;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::UI::Xaml::Input;
using namespace ABI::Windows::UI::Xaml::Media;

namespace rtom = winrt::AdaptiveCards::ObjectModel::WinUI3;
namespace rtrender = winrt::AdaptiveCards::Rendering::WinUI3;
namespace rtxaml = winrt::Windows::UI::Xaml;

namespace AdaptiveCards::Rendering::WinUI3::ActionHelpers
{
    rtxaml::Thickness GetButtonMargin(rtrender::AdaptiveActionsConfig const& actionsConfig)
    {
        rtxaml::Thickness buttonMargin{};
        const uint32_t buttonSpacing = actionsConfig.ButtonSpacing();
        const auto actionsOrientation = actionsConfig.ActionsOrientation();

        if (actionsOrientation == rtrender::ActionsOrientation::Horizontal)
        {
            buttonMargin.Left = buttonMargin.Right = buttonSpacing / 2;
        }
        else
        {
            buttonMargin.Top = buttonMargin.Bottom = buttonSpacing / 2;
        }

        return buttonMargin;
    }

    void SetTooltip(winrt::hstring const& toolTipText, rtxaml::DependencyObject const& tooltipTarget)
    {
        if (!toolTipText.empty())
        {
            rtxaml::Controls::TextBlock tooltipTextBlock;
            tooltipTextBlock.Text(toolTipText);

            rtxaml::Controls::ToolTip toolTip;
            toolTip.Content(tooltipTextBlock);
            rtxaml::Controls::ToolTipService::SetToolTip(tooltipTarget, toolTip);
        }
    }

    void SetAutomationNameAndDescription(_In_ IDependencyObject* dependencyObject, _In_opt_ HSTRING name, _In_opt_ HSTRING description)
    {
        // Set the automation properties
        ComPtr<IAutomationPropertiesStatics> automationPropertiesStatics;
        THROW_IF_FAILED(
            GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(),
                                 &automationPropertiesStatics));

        ComPtr<IAutomationPropertiesStatics5> automationPropertiesStatics5;
        THROW_IF_FAILED(automationPropertiesStatics.As(&automationPropertiesStatics5));

        THROW_IF_FAILED(automationPropertiesStatics->SetName(dependencyObject, name));
        THROW_IF_FAILED(automationPropertiesStatics5->SetFullDescription(dependencyObject, description));
    }

    void SetAutomationNameAndDescription(rtxaml::DependencyObject const& dependencyObject,
                                         winrt::hstring const& name,
                                         winrt::hstring const& description)
    {
        rtxaml::Automation::AutomationProperties::SetName(dependencyObject, name);
        rtxaml::Automation::AutomationProperties::SetFullDescription(dependencyObject, description);
    }

    template<typename T> auto to_ref(T const& t)
    {
        return winrt::box_value(t).as<winrt::Windows::Foundation::IReference<T>>();
    }

    void ArrangeButtonContent(winrt::hstring const& actionTitle,
                              winrt::hstring const& actionIconUrl,
                              winrt::hstring const& actionTooltip,
                              winrt::hstring const& actionAccessibilityText,
                              rtrender::AdaptiveActionsConfig const& actionsConfig,
                              rtrender::AdaptiveRenderContext const& renderContext,
                              rtom::ContainerStyle containerStyle,
                              rtrender::AdaptiveHostConfig const& hostConfig,
                              bool allActionsHaveIcons,
                              rtxaml::Controls::Button const& button)
    {
        winrt::hstring title{actionTitle};
        winrt::hstring iconUrl{actionIconUrl};
        winrt::hstring tooltip{actionTooltip};
        winrt::hstring accessibilityText{actionAccessibilityText};

        winrt::hstring name{};
        winrt::hstring description{};

        // TODO: is it correct substitution to HString.IsValid()?
        if (!accessibilityText.empty())
        {
            // If we have accessibility text use that as the name and tooltip as the description
            name = accessibilityText;
            description = tooltip;
        }
        // TODO: is it correct substitution to HString.IsValid()?
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

        SetAutomationNameAndDescription(button, name, description);
        SetTooltip(tooltip, button);

        // Check if the button has an iconurl
        // TODO: is it correct substitution to HString != nullptr?
        if (!iconUrl.empty())
        {
            // Get icon configs
            rtrender::IconPlacement iconPlacement = actionsConfig.IconPlacement();
            uint32_t iconSize = actionsConfig.IconSize();

            // Define the alignment for the button contents
            rtxaml::Controls::StackPanel buttonContentsStackPanel{};

            // Create image and add it to the button
            // TODO: should we use adaptive image here at all?
            rtom::AdaptiveImage adaptiveImage{};

            adaptiveImage.Url(iconUrl);
            // TODO: no need to box to convert to IRef, right?
            adaptiveImage.HorizontalAlignment(rtom::HAlignment::Center);

            rtxaml::UIElement buttonIcon{nullptr};

            auto childRenderArgs =
                winrt::make<rtrender::implementation::AdaptiveRenderArgs>(containerStyle, buttonContentsStackPanel, nullptr);

            auto elementRenderers = renderContext.ElementRenderers();

            auto elementRenderer = elementRenderers.Get(L"Image");
            if (elementRenderer != nullptr)
            {
                // TODO: no need to cast adaptiveImage to element right?
                buttonIcon = elementRenderer.Render(adaptiveImage, renderContext, childRenderArgs);
                if (buttonIcon == nullptr)
                {
                    XamlHelpers::SetContent(button, title);
                    return;
                }
            }

            // Create title text block
            rtxaml::Controls::TextBlock buttonText{};
            buttonText.Text(title);
            buttonText.TextAlignment(rtxaml::TextAlignment::Center);
            buttonText.VerticalAlignment(rtxaml::VerticalAlignment::Center);

            // Handle different arrangements inside button
            auto buttonIconAsFrameworkElement = buttonIcon.as<rtxaml::FrameworkElement>();

            // Set icon height to iconSize(aspect ratio is automatically maintained)
            buttonIconAsFrameworkElement.Height(iconSize);

            rtxaml::UIElement separator{nullptr};

            if (iconPlacement == rtrender::IconPlacement::AboveTitle && allActionsHaveIcons)
            {
                buttonContentsStackPanel.Orientation(rtxaml::Controls::Orientation::Vertical);
            }
            else
            {
                buttonContentsStackPanel.Orientation(rtxaml::Controls::Orientation::Horizontal);

                // Only add spacing when the icon must be located at the left of the title
                uint32_t spacingSize = GetSpacingSizeFromSpacing(hostConfig, rtom::Spacing::Default);
                // TODO: We're p
                separator = XamlHelpers::CreateSeparator(renderContext, spacingSize, spacingSize, {0}, false);
            }
        }
    }

    // void ArrangeButtonContent(_In_ HSTRING actionTitle,
    //                          _In_ HSTRING actionIconUrl,
    //                          _In_ HSTRING actionTooltip,
    //                          _In_ HSTRING actionAccessibilityText,
    //                          _In_ IAdaptiveActionsConfig* actionsConfig,
    //                          _In_ IAdaptiveRenderContext* renderContext,
    //                          ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle containerStyle,
    //                          _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* hostConfig,
    //                          bool allActionsHaveIcons,
    //                          _In_ IButton* button)
    //{
    //    HString title;
    //    THROW_IF_FAILED(title.Set(actionTitle));

    //    HString iconUrl;
    //    THROW_IF_FAILED(iconUrl.Set(actionIconUrl));

    //    HString tooltip;
    //    THROW_IF_FAILED(tooltip.Set(actionTooltip));

    //    HString accessibilityText;
    //    THROW_IF_FAILED(accessibilityText.Set(actionAccessibilityText));

    //    HString name;
    //    HString description;
    //    if (accessibilityText.IsValid())
    //    {
    //        // If we have accessibility text use that as the name and tooltip as the description
    //        name.Set(accessibilityText.Get());
    //        description.Set(tooltip.Get());
    //    }
    //    else if (title.IsValid())
    //    {
    //        // If we have a title, use title as the automation name and tooltip as the description
    //        name.Set(title.Get());
    //        description.Set(tooltip.Get());
    //    }
    //    else
    //    {
    //        // If there's no title, use tooltip as the name
    //        name.Set(tooltip.Get());
    //    }

    //    ComPtr<IButton> localButton(button);
    //    ComPtr<IDependencyObject> buttonAsDependencyObject;
    //    THROW_IF_FAILED(localButton.As(&buttonAsDependencyObject));
    //    SetAutomationNameAndDescription(buttonAsDependencyObject.Get(), name.Get(), description.Get());
    //    SetTooltip(to_winrt(tooltip), to_winrt(buttonAsDependencyObject));

    //    // Check if the button has an iconUrl
    //    if (iconUrl != nullptr)
    //    {
    //        // Get icon configs
    //        ABI::AdaptiveCards::Rendering::WinUI3::IconPlacement iconPlacement;
    //        UINT32 iconSize;

    //        THROW_IF_FAILED(actionsConfig->get_IconPlacement(&iconPlacement));
    //        THROW_IF_FAILED(actionsConfig->get_IconSize(&iconSize));

    //        // Define the alignment for the button contents
    //        ComPtr<IStackPanel> buttonContentsStackPanel =
    //            XamlHelpers::CreateABIClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));

    //        // Create image and add it to the button
    //        ComPtr<IAdaptiveImage> adaptiveImage = XamlHelpers::CreateABIClass<IAdaptiveImage>(
    //            HStringReference(RuntimeClass_AdaptiveCards_ObjectModel_WinUI3_AdaptiveImage));

    //        THROW_IF_FAILED(adaptiveImage->put_Url(iconUrl.Get()));

    //        THROW_IF_FAILED(adaptiveImage->put_HorizontalAlignment(
    //            winrt::box_value(winrt::AdaptiveCards::ObjectModel::WinUI3::HAlignment::Center)
    //                .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::HAlignment>>()
    //                .get()));

    //        ComPtr<IAdaptiveCardElement> adaptiveCardElement;
    //        THROW_IF_FAILED(adaptiveImage.As(&adaptiveCardElement));
    //        auto childRenderArgs =
    //            winrt::make<rtrender::implementation::AdaptiveRenderArgs>(containerStyle, buttonContentsStackPanel, nullptr);

    //        /*auto childRenderArgsTo = to_wrl(childRenderArgs);*/

    //        ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
    //        THROW_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));

    //        ComPtr<IUIElement> buttonIcon;
    //        ComPtr<IAdaptiveElementRenderer> elementRenderer;
    //        THROW_IF_FAILED(elementRenderers->Get(HStringReference(L"Image").Get(), &elementRenderer));
    //        if (elementRenderer != nullptr)
    //        {
    //            elementRenderer->Render(adaptiveCardElement.Get(), renderContext, to_wrl(childRenderArgs).Get(),
    //            &buttonIcon); if (buttonIcon == nullptr)
    //            {
    //                XamlHelpers::SetContent(localButton.Get(), title.Get());
    //                return;
    //            }
    //        }

    //        // Create title text block
    //        ComPtr<ITextBlock> buttonText =
    //            XamlHelpers::CreateABIClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
    //        THROW_IF_FAILED(buttonText->put_Text(title.Get()));
    //        THROW_IF_FAILED(buttonText->put_TextAlignment(TextAlignment::TextAlignment_Center));

    //        ComPtr<IFrameworkElement> buttonTextAsFrameworkElement;
    //        THROW_IF_FAILED(buttonText.As(&buttonTextAsFrameworkElement));
    //        THROW_IF_FAILED(buttonTextAsFrameworkElement->put_VerticalAlignment(
    //            ABI::Windows::UI::Xaml::VerticalAlignment::VerticalAlignment_Center));

    //        // Handle different arrangements inside button
    //        ComPtr<IFrameworkElement> buttonIconAsFrameworkElement;
    //        THROW_IF_FAILED(buttonIcon.As(&buttonIconAsFrameworkElement));

    //        // Set icon height to iconSize (aspect ratio is automatically maintained)
    //        THROW_IF_FAILED(buttonIconAsFrameworkElement->put_Height(iconSize));

    //        ComPtr<IUIElement> separator;
    //        if (iconPlacement == ABI::AdaptiveCards::Rendering::WinUI3::IconPlacement::AboveTitle && allActionsHaveIcons)
    //        {
    //            THROW_IF_FAILED(buttonContentsStackPanel->put_Orientation(Orientation::Orientation_Vertical));
    //        }
    //        else
    //        {
    //            THROW_IF_FAILED(buttonContentsStackPanel->put_Orientation(Orientation::Orientation_Horizontal));

    //            // Only add spacing when the icon must be located at the left of the title
    //            UINT spacingSize;
    //            THROW_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig, ABI::AdaptiveCards::ObjectModel::WinUI3::Spacing::Default, &spacingSize));

    //            ABI::Windows::UI::Color color = {0};
    //            separator = XamlHelpers::CreateSeparator(renderContext, spacingSize, spacingSize, color, false);
    //        }

    //        ComPtr<IPanel> buttonContentsPanel;
    //        THROW_IF_FAILED(buttonContentsStackPanel.As(&buttonContentsPanel));

    //        // Add image to stack panel
    //        XamlHelpers::AppendXamlElementToPanel(buttonIcon.Get(), buttonContentsPanel.Get());

    //        // Add separator to stack panel
    //        if (separator != nullptr)
    //        {
    //            XamlHelpers::AppendXamlElementToPanel(separator.Get(), buttonContentsPanel.Get());
    //        }

    //        // Add text to stack panel
    //        XamlHelpers::AppendXamlElementToPanel(buttonText.Get(), buttonContentsPanel.Get());

    //        // Finally, put the stack panel inside the final button
    //        ComPtr<IContentControl> buttonContentControl;
    //        THROW_IF_FAILED(localButton.As(&buttonContentControl));
    //        THROW_IF_FAILED(buttonContentControl->put_Content(buttonContentsPanel.Get()));
    //    }
    //    else
    //    {
    //        XamlHelpers::SetContent(localButton.Get(), title.Get());
    //    }
    //}

    void HandleActionStyling(rtom::IAdaptiveActionElement const& adaptiveActionElement,
                             rtxaml::FrameworkElement const& buttonFrameworkElement,
                             bool isOverflowActionButton,
                             rtrender::AdaptiveRenderContext const& renderContext)
    {
        // TODO: implement this function?
    }

    // HRESULT HandleActionStyling(_In_ IAdaptiveActionElement* adaptiveActionElement,
    //                            _In_ IFrameworkElement* buttonFrameworkElement,
    //                            bool isOverflowActionButton,
    //                            _In_ IAdaptiveRenderContext* renderContext)
    //{
    //    HString actionSentiment;
    //    if (adaptiveActionElement != nullptr)
    //    {
    //        RETURN_IF_FAILED(adaptiveActionElement->get_Style(actionSentiment.GetAddressOf()));
    //    }

    //    INT32 isSentimentPositive{}, isSentimentDestructive{}, isSentimentDefault{};

    //    ComPtr<IResourceDictionary> resourceDictionary;
    //    RETURN_IF_FAILED(renderContext->get_OverrideStyles(&resourceDictionary));
    //    ComPtr<IStyle> styleToApply;

    //    auto contextImpl = peek_innards<rtrender::implementation::AdaptiveRenderContext>(renderContext);

    //    // If we have an overflow style apply it, otherwise we'll fall back on the default button styling
    //    if (isOverflowActionButton)
    //    {
    //        if (SUCCEEDED(XamlHelpers::TryGetResourceFromResourceDictionaries<IStyle>(resourceDictionary.Get(),
    //                                                                                  L"Adaptive.Action.Overflow",
    //                                                                                  &styleToApply)))
    //        {
    //            RETURN_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
    //        }
    //    }

    //    if ((SUCCEEDED(WindowsCompareStringOrdinal(actionSentiment.Get(), HStringReference(L"default").Get(),
    //    &isSentimentDefault)) &&
    //         (isSentimentDefault == 0)) ||
    //        WindowsIsStringEmpty(actionSentiment.Get()))
    //    {
    //        RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Action",
    //        buttonFrameworkElement));
    //    }
    //    else if (SUCCEEDED(WindowsCompareStringOrdinal(actionSentiment.Get(), HStringReference(L"positive").Get(),
    //    &isSentimentPositive)) &&
    //             (isSentimentPositive == 0))
    //    {
    //        if (SUCCEEDED(XamlHelpers::TryGetResourceFromResourceDictionaries<IStyle>(resourceDictionary.Get(),
    //                                                                                  L"Adaptive.Action.Positive",
    //                                                                                  &styleToApply)))
    //        {
    //            RETURN_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
    //        }
    //        else
    //        {
    //            // By default, set the action background color to accent color
    //            auto actionSentimentDictionary = contextImpl->GetDefaultActionSentimentDictionary();

    //            if (SUCCEEDED(XamlHelpers::TryGetResourceFromResourceDictionaries(to_wrl(actionSentimentDictionary).Get(),
    //                                                                              L"PositiveActionDefaultStyle",
    //                                                                              styleToApply.GetAddressOf())))
    //            {
    //                RETURN_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
    //            }
    //        }
    //    }
    //    else if (SUCCEEDED(WindowsCompareStringOrdinal(actionSentiment.Get(), HStringReference(L"destructive").Get(), &isSentimentDestructive)) &&
    //             (isSentimentDestructive == 0))
    //    {
    //        if (SUCCEEDED(XamlHelpers::TryGetResourceFromResourceDictionaries<IStyle>(resourceDictionary.Get(),
    //                                                                                  L"Adaptive.Action.Destructive",
    //                                                                                  &styleToApply)))
    //        {
    //            RETURN_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
    //        }
    //        else
    //        {
    //            // By default, set the action text color to attention color
    //            auto actionSentimentDictionary = contextImpl->GetDefaultActionSentimentDictionary();

    //            if (SUCCEEDED(XamlHelpers::TryGetResourceFromResourceDictionaries(to_wrl(actionSentimentDictionary).Get(),
    //                                                                              L"DestructiveActionDefaultStyle",
    //                                                                              styleToApply.GetAddressOf())))
    //            {
    //                RETURN_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
    //            }
    //        }
    //    }
    //    else
    //    {
    //        HString actionSentimentStyle;
    //        RETURN_IF_FAILED(WindowsConcatString(HStringReference(L"Adaptive.Action.").Get(),
    //                                             actionSentiment.Get(),
    //                                             actionSentimentStyle.GetAddressOf()));
    //        RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext, actionSentimentStyle.Get(), buttonFrameworkElement));
    //    }
    //    return S_OK;
    //}

    HRESULT SetMatchingHeight(_In_ IFrameworkElement* elementToChange, _In_ IFrameworkElement* elementToMatch)
    {
        DOUBLE actualHeight;
        RETURN_IF_FAILED(elementToMatch->get_ActualHeight(&actualHeight));

        ComPtr<IFrameworkElement> localElement(elementToChange);
        RETURN_IF_FAILED(localElement->put_Height(actualHeight));

        ComPtr<IUIElement> frameworkElementAsUIElement;
        RETURN_IF_FAILED(localElement.As(&frameworkElementAsUIElement));
        RETURN_IF_FAILED(frameworkElementAsUIElement->put_Visibility(Visibility::Visibility_Visible));
        return S_OK;
    }

    void SetMatchingHeight(rtxaml::FrameworkElement const& elementToChange, rtxaml::FrameworkElement const& elementToMatch)
    {
        elementToChange.Height(elementToMatch.ActualHeight());
        elementToChange.Visibility(rtxaml::Visibility::Visible);
    }

    rtxaml::UIElement BuildAction(rtom::IAdaptiveActionElement const& adaptiveActionElement,
                                  rtrender::AdaptiveRenderContext const& renderContext,
                                  rtrender::AdaptiveRenderArgs const& renderArgs,
                                  bool isOverflowActionButton)
    {
        // TODO: Should we PeekInnards on the rtrender:: types and save ourselves some layers of C++/winrt?

        auto hostConfig = renderContext.HostConfig();
        auto actionsConfig = hostConfig.Actions();

        auto button = CreateAppropriateButton(adaptiveActionElement);
        button.Margin(GetButtonMargin(actionsConfig));

        auto actionsOrientation = actionsConfig.ActionsOrientation();
        auto actionAlignment = actionsConfig.ActionAlignment();
        if (actionsOrientation == rtrender::ActionsOrientation::Horizontal)
        {
            button.HorizontalAlignment(rtxaml::HorizontalAlignment::Stretch);
        }
        else
        {
            rtxaml::HorizontalAlignment newAlignment;
            switch (actionAlignment)
            {
            case rtrender::ActionAlignment::Center:
                newAlignment = rtxaml::HorizontalAlignment::Center;
                break;
            case rtrender::ActionAlignment::Left:
                newAlignment = rtxaml::HorizontalAlignment::Left;
                break;
            case rtrender::ActionAlignment::Right:
                newAlignment = rtxaml::HorizontalAlignment::Center;
                break;
            case rtrender::ActionAlignment::Stretch:
                newAlignment = rtxaml::HorizontalAlignment::Stretch;
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
            auto hostConfigImpl = peek_innards<rtrender::implementation::AdaptiveHostConfig>(hostConfig);
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

        auto showCardActionConfig = actionsConfig.ShowCard();
        auto actionMode = showCardActionConfig.ActionMode();

        if (adaptiveActionElement)
        {
            auto actionInvoker = renderContext.ActionInvoker();
            auto clickToken = button.Click([adaptiveActionElement, actionInvoker](auto...)
                                           { actionInvoker.SendActionEvent(adaptiveActionElement); });
            button.IsEnabled(adaptiveActionElement.IsEnabled());
        }

        HandleActionStyling(adaptiveActionElement, button, isOverflowActionButton, renderContext);
        return button;
    }

    bool WarnForInlineShowCard(rtrender::AdaptiveRenderContext const& renderContext,
                               rtom::IAdaptiveActionElement const& action,
                               const std::wstring& warning)
    {
        if (action && (action.ActionType() == rtom::ActionType::ShowCard))
        {
            renderContext.AddWarning(rtom::WarningStatusCode::UnsupportedValue, warning);
            return true;
        }
        else
        {
            return false;
        }
    }

    void HandleKeydownForInlineAction(rtxaml::Input::KeyRoutedEventArgs const& args,
                                      rtrender::AdaptiveActionInvoker const& actionInvoker,
                                      rtom::IAdaptiveActionElement const& inlineAction)
    {
        if (args.Key() == winrt::Windows::System::VirtualKey::Enter)
        {
            auto coreWindow = winrt::Windows::UI::Core::CoreWindow::GetForCurrentThread();

            if ((coreWindow.GetKeyState(winrt::Windows::System::VirtualKey::Shift) ==
                 winrt::Windows::UI::Core::CoreVirtualKeyStates::None) &&
                (coreWindow.GetKeyState(winrt::Windows::System::VirtualKey::Control) ==
                 winrt::Windows::UI::Core::CoreVirtualKeyStates::None))
            {
                actionInvoker.SendActionEvent(inlineAction);
                args.Handled(true);
            }
        }
    }

    rtxaml::UIElement HandleInlineAction(rtrender::AdaptiveRenderContext const& renderContext,
                                         rtrender::AdaptiveRenderArgs const& renderArgs,
                                         rtxaml::UIElement const& textInputUIElement,
                                         rtxaml::UIElement const& textBoxParentContainer,
                                         bool isMultilineTextBox,
                                         rtom::IAdaptiveActionElement const& inlineAction)
    {
        rtom::ActionType actionType = inlineAction.ActionType();
        auto hostConfig = renderContext.HostConfig();

        // Inline ShowCards are not supported for inline actions
        if (WarnForInlineShowCard(renderContext, inlineAction, L"Inline ShowCard not supported for InlineAction"))
        {
            // TODO: is this correct?
            return nullptr;
        }
        if ((actionType == rtom::ActionType::Submit) || (actionType == rtom::ActionType::Execute))
        {
            renderContext.LinkSubmitActionToCard(inlineAction, renderArgs);
        }

        // Create a grid to hold the text box and the action button
        rtxaml::Controls::Grid xamlGrid{};
        auto columnDefinitions = xamlGrid.ColumnDefinitions();

        // Create the first column and add the text box to it
        rtxaml::Controls::ColumnDefinition textBoxColumnDefinition{};
        textBoxColumnDefinition.Width({1, rtxaml::GridUnitType::Star});
        columnDefinitions.Append(textBoxColumnDefinition);

        auto textBoxContainerAsFrameworkElement = textBoxParentContainer.as<rtxaml::FrameworkElement>();

        rtxaml::Controls::Grid::SetColumn(textBoxContainerAsFrameworkElement, 0);
        XamlHelpers::AppendXamlElementToPanel(textBoxContainerAsFrameworkElement, xamlGrid);

        // Create a separator column
        rtxaml::Controls::ColumnDefinition separatorColumnDefinition{};
        separatorColumnDefinition.Width({1.0, rtxaml::GridUnitType::Auto});
        columnDefinitions.Append(separatorColumnDefinition);

        uint32_t spacingSize = GetSpacingSizeFromSpacing(hostConfig, rtom::Spacing::Default);

        auto separator = XamlHelpers::CreateSeparator(renderContext, spacingSize, 0, {0}, false);

        auto separatorAsFrameworkElement = separator.as<rtxaml::FrameworkElement>();

        rtxaml::Controls::Grid::SetColumn(separatorAsFrameworkElement, 1);
        XamlHelpers::AppendXamlElementToPanel(separator, xamlGrid);

        // Create a column for the button

        rtxaml::Controls::ColumnDefinition inlineActionColumnDefinition{};
        inlineActionColumnDefinition.Width({0, rtxaml::GridUnitType::Auto});
        columnDefinitions.Append(inlineActionColumnDefinition);

        winrt::hstring iconUrl = inlineAction.IconUrl();

        rtxaml::UIElement actionUIElement{nullptr};

        // TODO: should I check for null here as well? hstring
        if (!iconUrl.empty())
        {
            // TODO: same thing as with rendering Poster/BackgroundImage, should we resort to something else?
            auto elementRenderers = renderContext.ElementRenderers();
            auto imageRenderer = elementRenderers.Get(L"Image");

            rtom::AdaptiveImage adaptiveImage{};

            adaptiveImage.Url(iconUrl);
            actionUIElement = imageRenderer.Render(adaptiveImage, renderContext, renderArgs);
        }
        else
        {
            // If there's no icon, just use the title text. Put it centered in a grid so it is
            // centered relative to the text box.
            winrt::hstring title = inlineAction.Title();
            rtxaml::Controls::TextBlock titleTextBlock{};
            titleTextBlock.Text(title);

            // TOOD: what about text alignment?
            titleTextBlock.VerticalAlignment(rtxaml::VerticalAlignment::Center);

            rtxaml::Controls::Grid titleGrid{};
            XamlHelpers::AppendXamlElementToPanel(titleTextBlock, titleGrid);

            actionUIElement = titleGrid;
        }
        // Make the action the same size as the text box
        textBoxContainerAsFrameworkElement.Loaded(
            [actionUIElement, textBoxContainerAsFrameworkElement](winrt::Windows::Foundation::IInspectable const& /*sender*/,
                                                                  rtxaml::RoutedEventArgs const& /*args*/) -> void
            {
                auto actionFrameworkElement = actionUIElement.as<rtxaml::FrameworkElement>();
                ActionHelpers::SetMatchingHeight(actionFrameworkElement, textBoxContainerAsFrameworkElement);
            });

        // Wrap the action in a button
        auto touchTargetUIElement = WrapInTouchTarget(nullptr,
                                                      actionUIElement,
                                                      inlineAction,
                                                      renderContext,
                                                      false,
                                                      L"Adaptive.Input.Text.InlineAction",
                                                      L"", // TODO: not sure if it's correct to do here
                                                      !iconUrl.empty());

        auto touchTargetFrameworkElement = touchTargetUIElement.as<rtxaml::FrameworkElement>();

        // Align to bottom so the icon stays with the bottom of the text box as it grows in the multiline case
        touchTargetFrameworkElement.VerticalAlignment(rtxaml::VerticalAlignment::Bottom);

        // Add the action to the column
        // TODO: should I use gridStatics?
        rtxaml::Controls::Grid::SetColumn(touchTargetFrameworkElement, 2);
        XamlHelpers::AppendXamlElementToPanel(touchTargetFrameworkElement, xamlGrid);

        // If this isn't a multiline input, enter should invoke the action
        auto actionInvoker = renderContext.ActionInvoker();

        if (!isMultilineTextBox)
        {
            textInputUIElement.KeyDown(
                [actionInvoker, inlineAction](winrt::Windows::Foundation::IInspectable const& /*sender*/,
                                              rtxaml::Input::KeyRoutedEventArgs const& args) -> void
                // TODO: do I need ActionHelpers:: namespace here?
                { ActionHelpers::HandleKeydownForInlineAction(args, actionInvoker, inlineAction); });
        }

        return xamlGrid;
    }

    // void HandleInlineAction(_In_ IAdaptiveRenderContext* renderContext,
    //                        _In_ IAdaptiveRenderArgs* renderArgs,
    //                        _In_ IUIElement* textInputUIElement,
    //                        _In_ IUIElement* textBoxParentContainer,
    //                        bool isMultilineTextBox,
    //                        _In_ IAdaptiveActionElement* inlineAction,
    //                        _COM_Outptr_ IUIElement** textBoxWithInlineAction)
    //{
    //    ComPtr<IUIElement> localTextBoxContainer(textBoxParentContainer);
    //    ComPtr<IAdaptiveActionElement> localInlineAction(inlineAction);

    //    ABI::AdaptiveCards::ObjectModel::WinUI3::ActionType actionType;
    //    THROW_IF_FAILED(localInlineAction->get_ActionType(&actionType));

    //    ComPtr<IAdaptiveHostConfig> hostConfig;
    //    THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

    //    // Inline ShowCards are not supported for inline actions
    //    if (WarnForInlineShowCard(renderContext, localInlineAction.Get(), L"Inline ShowCard not supported for InlineAction"))
    //    {
    //        THROW_IF_FAILED(localTextBoxContainer.CopyTo(textBoxWithInlineAction));
    //        return;
    //    }

    //    if ((actionType == ABI::AdaptiveCards::ObjectModel::WinUI3::ActionType::Submit) ||
    //        (actionType == ABI::AdaptiveCards::ObjectModel::WinUI3::ActionType::Execute))
    //    {
    //        THROW_IF_FAILED(renderContext->LinkSubmitActionToCard(localInlineAction.Get(), renderArgs));
    //    }

    //    // Create a grid to hold the text box and the action button
    //    ComPtr<IGridStatics> gridStatics;
    //    THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));

    //    ComPtr<IGrid> xamlGrid =
    //    XamlHelpers::CreateABIClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid)); ComPtr<IVector<ColumnDefinition*>>
    //    columnDefinitions; THROW_IF_FAILED(xamlGrid->get_ColumnDefinitions(&columnDefinitions)); ComPtr<IPanel>
    //    gridAsPanel; THROW_IF_FAILED(xamlGrid.As(&gridAsPanel));

    //    // Create the first column and add the text box to it
    //    ComPtr<IColumnDefinition> textBoxColumnDefinition = XamlHelpers::CreateABIClass<IColumnDefinition>(
    //        HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
    //    THROW_IF_FAILED(textBoxColumnDefinition->put_Width({1, GridUnitType::GridUnitType_Star}));
    //    THROW_IF_FAILED(columnDefinitions->Append(textBoxColumnDefinition.Get()));

    //    ComPtr<IFrameworkElement> textBoxContainerAsFrameworkElement;
    //    THROW_IF_FAILED(localTextBoxContainer.As(&textBoxContainerAsFrameworkElement));

    //    THROW_IF_FAILED(gridStatics->SetColumn(textBoxContainerAsFrameworkElement.Get(), 0));
    //    XamlHelpers::AppendXamlElementToPanel(textBoxContainerAsFrameworkElement.Get(), gridAsPanel.Get());

    //    // Create a separator column
    //    ComPtr<IColumnDefinition> separatorColumnDefinition = XamlHelpers::CreateABIClass<IColumnDefinition>(
    //        HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
    //    THROW_IF_FAILED(separatorColumnDefinition->put_Width({1.0, GridUnitType::GridUnitType_Auto}));
    //    THROW_IF_FAILED(columnDefinitions->Append(separatorColumnDefinition.Get()));

    //    UINT spacingSize;
    //    THROW_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig.Get(), ABI::AdaptiveCards::ObjectModel::WinUI3::Spacing::Default, &spacingSize));

    //    auto separator = XamlHelpers::CreateSeparator(renderContext, spacingSize, 0, {0}, false);

    //    ComPtr<IFrameworkElement> separatorAsFrameworkElement;
    //    THROW_IF_FAILED(separator.As(&separatorAsFrameworkElement));

    //    THROW_IF_FAILED(gridStatics->SetColumn(separatorAsFrameworkElement.Get(), 1));
    //    XamlHelpers::AppendXamlElementToPanel(separator.Get(), gridAsPanel.Get());

    //    // Create a column for the button
    //    ComPtr<IColumnDefinition> inlineActionColumnDefinition = XamlHelpers::CreateABIClass<IColumnDefinition>(
    //        HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
    //    THROW_IF_FAILED(inlineActionColumnDefinition->put_Width({0, GridUnitType::GridUnitType_Auto}));
    //    THROW_IF_FAILED(columnDefinitions->Append(inlineActionColumnDefinition.Get()));

    //    HString iconUrl;
    //    THROW_IF_FAILED(localInlineAction->get_IconUrl(iconUrl.GetAddressOf()));
    //    ComPtr<IUIElement> actionUIElement;
    //    if (iconUrl != nullptr)
    //    {
    //        // Render the icon using the adaptive image renderer
    //        ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
    //        THROW_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
    //        ComPtr<IAdaptiveElementRenderer> imageRenderer;
    //        THROW_IF_FAILED(elementRenderers->Get(HStringReference(L"Image").Get(), &imageRenderer));

    //        ComPtr<IAdaptiveImage> adaptiveImage = XamlHelpers::CreateABIClass<IAdaptiveImage>(
    //            HStringReference(RuntimeClass_AdaptiveCards_ObjectModel_WinUI3_AdaptiveImage));

    //        THROW_IF_FAILED(adaptiveImage->put_Url(iconUrl.Get()));

    //        ComPtr<IAdaptiveCardElement> adaptiveImageAsElement;
    //        THROW_IF_FAILED(adaptiveImage.As(&adaptiveImageAsElement));

    //        THROW_IF_FAILED(imageRenderer->Render(adaptiveImageAsElement.Get(), renderContext, renderArgs, &actionUIElement));
    //    }
    //    else
    //    {
    //        // If there's no icon, just use the title text. Put it centered in a grid so it is
    //        // centered relative to the text box.
    //        HString title;
    //        THROW_IF_FAILED(localInlineAction->get_Title(title.GetAddressOf()));

    //        ComPtr<ITextBlock> titleTextBlock =
    //            XamlHelpers::CreateABIClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
    //        THROW_IF_FAILED(titleTextBlock->put_Text(title.Get()));

    //        ComPtr<IFrameworkElement> textBlockAsFrameworkElement;
    //        THROW_IF_FAILED(titleTextBlock.As(&textBlockAsFrameworkElement));
    //        THROW_IF_FAILED(textBlockAsFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Center));

    //        ComPtr<IGrid> titleGrid =
    //            XamlHelpers::CreateABIClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
    //        ComPtr<IPanel> panel;
    //        THROW_IF_FAILED(titleGrid.As(&panel));
    //        XamlHelpers::AppendXamlElementToPanel(titleTextBlock.Get(), panel.Get());

    //        THROW_IF_FAILED(panel.As(&actionUIElement));
    //    }

    //    // Make the action the same size as the text box
    //    EventRegistrationToken eventToken;
    //    THROW_IF_FAILED(textBoxContainerAsFrameworkElement->add_Loaded(
    //        Callback<IRoutedEventHandler>(
    //            [actionUIElement, textBoxContainerAsFrameworkElement](IInspectable* /*sender*/, IRoutedEventArgs*
    //                                                                  /*args*/) -> HRESULT
    //            {
    //                ComPtr<IFrameworkElement> actionFrameworkElement;
    //                RETURN_IF_FAILED(actionUIElement.As(&actionFrameworkElement));

    //                return ActionHelpers::SetMatchingHeight(actionFrameworkElement.Get(),
    //                                                        textBoxContainerAsFrameworkElement.Get());
    //            })
    //            .Get(),
    //        &eventToken));

    //    // Wrap the action in a button
    //    ComPtr<IUIElement> touchTargetUIElement;
    //    WrapInTouchTarget(nullptr,
    //                      actionUIElement.Get(),
    //                      localInlineAction.Get(),
    //                      renderContext,
    //                      false,
    //                      L"Adaptive.Input.Text.InlineAction",
    //                      nullptr,
    //                      (iconUrl != nullptr),
    //                      &touchTargetUIElement);

    //    ComPtr<IFrameworkElement> touchTargetFrameworkElement;
    //    THROW_IF_FAILED(touchTargetUIElement.As(&touchTargetFrameworkElement));

    //    // Align to bottom so the icon stays with the bottom of the text box as it grows in the multiline case
    //    THROW_IF_FAILED(touchTargetFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Bottom));

    //    // Add the action to the column
    //    THROW_IF_FAILED(gridStatics->SetColumn(touchTargetFrameworkElement.Get(), 2));
    //    XamlHelpers::AppendXamlElementToPanel(touchTargetFrameworkElement.Get(), gridAsPanel.Get());

    //    // If this isn't a multiline input, enter should invoke the action
    //    ComPtr<IAdaptiveActionInvoker> actionInvoker;
    //    THROW_IF_FAILED(renderContext->get_ActionInvoker(&actionInvoker));

    //    if (!isMultilineTextBox)
    //    {
    //        EventRegistrationToken keyDownEventToken;
    //        THROW_IF_FAILED(textInputUIElement->add_KeyDown(
    //            Callback<IKeyEventHandler>(
    //                [actionInvoker, localInlineAction](IInspectable* /*sender*/, IKeyRoutedEventArgs* args) -> HRESULT
    //                { return HandleKeydownForInlineAction(args, actionInvoker.Get(), localInlineAction.Get()); })
    //                .Get(),
    //            &keyDownEventToken));
    //    }

    //    THROW_IF_FAILED(xamlGrid.CopyTo(textBoxWithInlineAction));
    //}

    rtxaml::UIElement WrapInTouchTarget(rtom::IAdaptiveCardElement const& adaptiveCardElement,
                                        rtxaml::UIElement const& elementToWrap,
                                        rtom::IAdaptiveActionElement const& action,
                                        rtrender::AdaptiveRenderContext const& renderContext,
                                        bool fullWidth,
                                        const std::wstring& style,
                                        winrt::hstring const& altText,
                                        bool allowTitleAsTooltip)
    {
        /*  ComPtr<IAdaptiveHostConfig> hostConfig;
          THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));*/
        auto hostConfig = renderContext.HostConfig();

        if (ActionHelpers::WarnForInlineShowCard(renderContext, action, L"Inline ShowCard not supported for SelectAction"))
        {
            // Was inline show card, so don't wrap the element and just return
            /*ComPtr<IUIElement> localElementToWrap(elementToWrap);
            localElementToWrap.CopyTo(finalElement);*/
            return elementToWrap;
        }

        /*ComPtr<IButton> button;*/
        auto button = CreateAppropriateButton(action);

        /*ComPtr<IContentControl> buttonAsContentControl;
        THROW_IF_FAILED(button.As(&buttonAsContentControl));
        THROW_IF_FAILED(buttonAsContentControl->put_Content(elementToWrap));*/
        // Do I need to cast here before setting content?
        button.Content(elementToWrap);

        /*ComPtr<IAdaptiveSpacingConfig> spacingConfig;
        THROW_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));*/
        auto spacingConfig = hostConfig.Spacing();

        uint32_t cardPadding = 0;
        if (fullWidth)
        {
            /*THROW_IF_FAILED(spacingConfig->get_Padding(&cardPadding));*/
            cardPadding = spacingConfig.Padding();
        }

        /*ComPtr<IFrameworkElement> buttonAsFrameworkElement;
        THROW_IF_FAILED(button.As(&buttonAsFrameworkElement));

        ComPtr<IControl> buttonAsControl;
        THROW_IF_FAILED(button.As(&buttonAsControl));*/

        // We want the hit target to equally split the vertical space above and below the current item.
        // However, all we know is the spacing of the current item, which only applies to the spacing above.
        // We don't know what the spacing of the NEXT element will be, so we can't calculate the correct spacing
        // below. For now, we'll simply assume the bottom spacing is the same as the top. NOTE: Only apply spacings
        // (padding, margin) for adaptive card elements to avoid adding spacings to card-level selectAction.
        if (adaptiveCardElement != nullptr)
        {
            /* ABI::AdaptiveCards::ObjectModel::WinUI3::Spacing elementSpacing;
             THROW_IF_FAILED(adaptiveCardElement->get_Spacing(&elementSpacing));*/
            auto elementSpacing = adaptiveCardElement.Spacing();
            uint32_t spacingSize = GetSpacingSizeFromSpacing(hostConfig, elementSpacing);

            // THROW_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig.Get(), elementSpacing, &spacingSize));
            double topBottomPadding = spacingSize / 2.0;

            // For button padding, we apply the cardPadding and topBottomPadding (and then we negate these in the margin)
            /*THROW_IF_FAILED(buttonAsControl->put_Padding({(double)cardPadding, topBottomPadding, (double)cardPadding, topBottomPadding}));*/
            button.Padding({(double)cardPadding, topBottomPadding, (double)cardPadding, topBottomPadding});

            double negativeCardMargin = cardPadding * -1.0;
            double negativeTopBottomMargin = topBottomPadding * -1.0;

            /*THROW_IF_FAILED(buttonAsFrameworkElement->put_Margin(
                {negativeCardMargin, negativeTopBottomMargin, negativeCardMargin, negativeTopBottomMargin}));*/
            // Do I need to cast here?
            button.Margin({negativeCardMargin, negativeTopBottomMargin, negativeCardMargin, negativeTopBottomMargin});
        }

        // Style the hit target button
        /* THROW_IF_FAILED(
             XamlHelpers::SetStyleFromResourceDictionary(renderContext, style.c_str(), buttonAsFrameworkElement.Get()));*/
        XamlHelpers::SetStyleFromResourceDictionary(renderContext, {style.c_str()}, button);

        // Determine tooltip, automation name, and automation description
        winrt::hstring tooltip, name, description;
        /*  HString tooltip;
          HString name;
          HString description;*/
        if (action != nullptr)
        {
            // If we have an action, get it's title and tooltip.
            winrt::hstring title = action.Title();
            tooltip = action.Tooltip();
            // THROW_IF_FAILED(action->get_Title(title.GetAddressOf()));
            // THROW_IF_FAILED(action->get_Tooltip(tooltip.GetAddressOf()));
            //
            // Is this correct way to check if title has the string inside? should I check c_str()?
            // Do empty strings pass here? I could check for title.empty()
            if (title.data())
            {
                // If we have a title, use title as the name and tooltip as the description
                name = title;
                description = tooltip;

                if (!tooltip.data() && allowTitleAsTooltip)
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
            /* THROW_IF_FAILED(action->get_IsEnabled(&isEnabled));
             THROW_IF_FAILED(buttonAsControl->put_IsEnabled(isEnabled));*/
        }
        // TODO: is it correct? what else should I check for? should I check if it's empty?? to mimick HString.IsValid()?
        else if (altText.data())
        {
            // If we don't have an action but we've been passed altText, use that for name and tooltip
            // name.Set(altText);
            // tooltip.Set(altText);
            name = altText;
            tooltip = altText;
        }

        /* ComPtr<IDependencyObject> buttonAsDependencyObject;
         THROW_IF_FAILED(button.As(&buttonAsDependencyObject));*/
        // SetAutomationNameAndDescription(buttonAsDependencyObject.Get(), name.Get(), description.Get());
        // SetTooltip(to_winrt(tooltip), to_winrt(buttonAsDependencyObject));
        SetAutomationNameAndDescription(button, name, description);
        SetTooltip(tooltip, button);

        // can we do explicit check? or need to call check_pointer()?
        if (action != nullptr)
        {
            WireButtonClickToAction(button, action, renderContext);
        }

        /*THROW_IF_FAILED(button.CopyTo(finalElement));*/
        return button;
    }

    void WireButtonClickToAction(rtxaml::Controls::Button button, rtom::IAdaptiveActionElement action, rtrender::AdaptiveRenderContext renderContext)
    {
        /* ComPtr<IButton> localButton(button);
         ComPtr<IAdaptiveActionInvoker> actionInvoker;
         THROW_IF_FAILED(renderContext->get_ActionInvoker(&actionInvoker));
         ComPtr<IAdaptiveActionElement> strongAction(action);*/

        // TODO: is this a valid way to do it?
        auto actionInvoker = renderContext.ActionInvoker();
        /* auto strongAction = *winrt::make_self<rtom::IAdaptiveActionElement>(actionInvoker);*/
        rtom::IAdaptiveActionElement strongAction{action};

        auto eventToken = button.Click([strongAction, actionInvoker](winrt::Windows::Foundation::IInspectable const&, rtxaml::RoutedEventArgs const&)
                                       { actionInvoker.SendActionEvent(strongAction); });
    }

    void WireButtonClickToAction(_In_ IButton* button, _In_ IAdaptiveActionElement* action, _In_ IAdaptiveRenderContext* renderContext)
    {
        // Note that this method currently doesn't support inline show card actions, it
        // assumes the caller won't call this method if inline show card is specified.
        ComPtr<IButton> localButton(button);
        ComPtr<IAdaptiveActionInvoker> actionInvoker;
        THROW_IF_FAILED(renderContext->get_ActionInvoker(&actionInvoker));
        ComPtr<IAdaptiveActionElement> strongAction(action);

        // Add click handler
        ComPtr<IButtonBase> buttonBase;
        THROW_IF_FAILED(localButton.As(&buttonBase));

        EventRegistrationToken clickToken;

        THROW_IF_FAILED(buttonBase->add_Click(Callback<IRoutedEventHandler>(
                                                  [strongAction, actionInvoker](IInspectable* /*sender*/, IRoutedEventArgs*
                                                                                /*args*/) -> HRESULT
                                                  {
                                                      THROW_IF_FAILED(actionInvoker->SendActionEvent(strongAction.Get()));
                                                      return S_OK;
                                                  })
                                                  .Get(),
                                              &clickToken));
    }

    void HandleSelectAction(_In_ IAdaptiveCardElement* adaptiveCardElement,
                            _In_ IAdaptiveActionElement* selectAction,
                            _In_ IAdaptiveRenderContext* renderContext,
                            _In_ IUIElement* uiElement,
                            bool supportsInteractivity,
                            bool fullWidthTouchTarget,
                            _COM_Outptr_ IUIElement** outUiElement)
    {
        if (selectAction != nullptr && supportsInteractivity)
        {
            // WrapInTouchTarget(adaptiveCardElement, uiElement, selectAction, renderContext, fullWidthTouchTarget,
            // L"Adaptive.SelectAction", nullptr, true, outUiElement);
        }
        else
        {
            if (selectAction != nullptr)
            {
                renderContext->AddWarning(ABI::AdaptiveCards::ObjectModel::WinUI3::WarningStatusCode::InteractivityNotSupported,
                                          HStringReference(L"SelectAction present, but Interactivity is not supported").Get());
            }

            ComPtr<IUIElement> localUiElement(uiElement);
            THROW_IF_FAILED(localUiElement.CopyTo(outUiElement));
        }
    }

    rtxaml::UIElement HandleSelectAction(rtom::IAdaptiveCardElement const& adaptiveCardElement,
                                         rtom::IAdaptiveActionElement const& selectAction,
                                         rtrender::AdaptiveRenderContext const& renderContext,
                                         rtxaml::UIElement const& uiElement,
                                         bool supportsInteractivity,
                                         bool fullWidthTouchTarget)
    {
        if (selectAction != nullptr && supportsInteractivity)
        {
            // TODO: Fix all instances of checking c_str of hstring to .empty()
            // TODO: Does this pass empty hstring or hstring with null c_str?
            return WrapInTouchTarget(
                adaptiveCardElement, uiElement, selectAction, renderContext, fullWidthTouchTarget, L"Adaptive.SelectAction", {}, true);
        }
        else
        {
            if (selectAction != nullptr)
            {
                renderContext.AddWarning(rtom::WarningStatusCode::InteractivityNotSupported,
                                         {L"SelectAction present, but Interactivity is not supported"});
            }

            return uiElement;
            /*ComPtr<IUIElement> localUiElement(uiElement);
            THROW_IF_FAILED(localUiElement.CopyTo(outUiElement));*/
        }
    }

    void BuildActions(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveCard const& adaptiveCard,
                      winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement> const& children,
                      winrt::Windows::UI::Xaml::Controls::Panel const& bodyPanel,
                      bool insertSeparator,
                      winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                      winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs)
    {
        auto hostConfig = renderContext.HostConfig();
        auto actionsConfig = hostConfig.Actions();
        if (insertSeparator)
        {
            auto spacingSize = GetSpacingSizeFromSpacing(hostConfig, actionsConfig.Spacing());
            auto separator = XamlHelpers::CreateSeparator(renderContext, spacingSize, 0u, winrt::Windows::UI::Color{}, false);
            XamlHelpers::AppendXamlElementToPanel(separator, bodyPanel);
        }

        auto actionSetControl = BuildActionSetHelper(adaptiveCard, nullptr, children, renderContext, renderArgs);
        XamlHelpers::AppendXamlElementToPanel(actionSetControl, bodyPanel);
    }

    rtxaml::Controls::Button CreateFlyoutButton(rtrender::AdaptiveRenderContext renderContext, rtrender::AdaptiveRenderArgs renderArgs)
    {
        // Create an action button
        /* ComPtr<IUIElement> overflowButtonAsUIElement;
         RETURN_IF_FAILED(BuildAction(nullptr, renderContext, renderArgs, true, &overflowButtonAsUIElement));*/
        auto overflowButtonAsUIElement = BuildAction(nullptr, renderContext, renderArgs, true);

        // Create a menu flyout for the overflow button
        // TODO : is this correct?
        auto overflowButtonAsButtonWithFlyout = overflowButtonAsUIElement.as<rtxaml::Controls::IButtonWithFlyout>();
        /* ComPtr<IButtonWithFlyout> overflowButtonAsButtonWithFlyout;
         RETURN_IF_FAILED(overflowButtonAsUIElement.As(&overflowButtonAsButtonWithFlyout));*/

        /*ComPtr<IMenuFlyout> overflowFlyout =
            XamlHelpers::CreateABIClass<IMenuFlyout>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_MenuFlyout));*/

        rtxaml::Controls::MenuFlyout overflowFlyout{};

        /* ComPtr<IFlyoutBase> overflowFlyoutAsFlyoutBase;
         RETURN_IF_FAILED(overflowFlyout.As(&overflowFlyoutAsFlyoutBase));*/
        // RETURN_IF_FAILED(overflowButtonAsButtonWithFlyout->put_Flyout(overflowFlyoutAsFlyoutBase.Get()));
        overflowButtonAsButtonWithFlyout.Flyout(overflowFlyout);

        // Return overflow button
        /*ComPtr<IButton> overFlowButtonAsButton;
        RETURN_IF_FAILED(overflowButtonAsUIElement.As(&overFlowButtonAsButton));
        RETURN_IF_FAILED(overFlowButtonAsButton.CopyTo(overflowButton));*/

        return overflowButtonAsUIElement.as<rtxaml::Controls::Button>();
    }

    rtxaml::UIElement AddOverflowFlyoutItem(rtom::IAdaptiveActionElement action,
                                            rtxaml::Controls::Button overflowButton,
                                            rtrender::AdaptiveRenderContext renderContext)
    {
        // Get the flyout items vector
        /* ComPtr<IButton> button(overflowButton);
         ComPtr<IButtonWithFlyout> buttonWithFlyout;
         RETURN_IF_FAILED(button.As(&buttonWithFlyout));*/
        auto buttonWithFlyout = overflowButton.as<rtxaml::Controls::IButtonWithFlyout>();

        auto menuFlyout = buttonWithFlyout.Flyout().as<rtxaml::Controls::MenuFlyout>();
        /*  ComPtr<IFlyoutBase> flyout;
          RETURN_IF_FAILED(buttonWithFlyout->get_Flyout(&flyout));*/

        /* ComPtr<IMenuFlyout> menuFlyout;
         RETURN_IF_FAILED(flyout.As(&menuFlyout));*/

        /* ComPtr<IVector<MenuFlyoutItemBase*>> flyoutItems;*/
        // RETURN_IF_FAILED(menuFlyout->get_Items(&flyoutItems));
        auto flyoutItems = menuFlyout.Items();
        // Create a flyout item
        /*  ComPtr<IMenuFlyoutItem> flyoutItem =
              XamlHelpers::CreateABIClass<IMenuFlyoutItem>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_MenuFlyoutItem));*/
        rtxaml::Controls::MenuFlyoutItem flyoutItem{};

        // Set the title
        // HString actionTitle;
        // RETURN_IF_FAILED(action->get_Title(actionTitle.GetAddressOf()));
        // RETURN_IF_FAILED(flyoutItem->put_Text(actionTitle.Get()));
        flyoutItem.Text(action.Title());

        // Set the tooltip
        /*String tooltip;
        RETURN_IF_FAILED(action->get_Tooltip(tooltip.GetAddressOf()));*/

        /*ComPtr<IDependencyObject> flyoutItemAsDependencyObject;
        RETURN_IF_FAILED(flyoutItem.As(&flyoutItemAsDependencyObject));*/
        // SetTooltip(to_winrt(tooltip), to_winrt(flyoutItemAsDependencyObject));
        SetTooltip(action.Tooltip(), flyoutItem);

        // Hook the menu item up to the action invoker
        /*ComPtr<IAdaptiveActionElement> actionParam(action);
        ComPtr<IAdaptiveActionInvoker> actionInvoker;
        RETURN_IF_FAILED(renderContext->get_ActionInvoker(&actionInvoker));
        EventRegistrationToken clickToken;*/

        // TODO: Which way is better? constructort or winrt::make_self
        rtom::IAdaptiveActionElement actionParam{action};
        rtrender::AdaptiveActionInvoker actionInvoker{};
        /*auto actionParam = *winrt::make_self<rtom::IAdaptiveActionElement>(action);*/

        auto eventToken = flyoutItem.Click([actionParam, actionInvoker](winrt::Windows::Foundation::IInspectable const&, rtxaml::RoutedEventArgs const)
                                           { return actionInvoker.SendActionEvent(actionParam); });

        // Add the new menu item to the vector
        /* ComPtr<IMenuFlyoutItemBase> flyoutItemAsBase;
         RETURN_IF_FAILED(flyoutItem.As(&flyoutItemAsBase));
         RETURN_IF_FAILED(flyoutItems->Append(flyoutItemAsBase.Get()));*/
        flyoutItems.Append(flyoutItem);

        /*ComPtr<IUIElement> flyoutItemAsUIElement;
        RETURN_IF_FAILED(flyoutItem.As(&flyoutItemAsUIElement));
        RETURN_IF_FAILED(flyoutItemAsUIElement.CopyTo(flyoutUIItem));*/

        // TODO: We don't need to do this, right? WinRT will cast for us?
        return flyoutItem.as<rtxaml::UIElement>();
    }

    HRESULT AddOverflowFlyoutItem(_In_ IAdaptiveActionElement* action,
                                  _In_ IButton* overflowButton,
                                  _In_ IAdaptiveRenderContext* renderContext,
                                  _COM_Outptr_ IUIElement** flyoutUIItem)
    {
        // Get the flyout items vector
        ComPtr<IButton> button(overflowButton);
        ComPtr<IButtonWithFlyout> buttonWithFlyout;
        RETURN_IF_FAILED(button.As(&buttonWithFlyout));

        ComPtr<IFlyoutBase> flyout;
        RETURN_IF_FAILED(buttonWithFlyout->get_Flyout(&flyout));

        ComPtr<IMenuFlyout> menuFlyout;
        RETURN_IF_FAILED(flyout.As(&menuFlyout));

        ComPtr<IVector<MenuFlyoutItemBase*>> flyoutItems;
        RETURN_IF_FAILED(menuFlyout->get_Items(&flyoutItems));
        // Create a flyout item
        ComPtr<IMenuFlyoutItem> flyoutItem =
            XamlHelpers::CreateABIClass<IMenuFlyoutItem>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_MenuFlyoutItem));

        // Set the title
        HString actionTitle;
        RETURN_IF_FAILED(action->get_Title(actionTitle.GetAddressOf()));
        RETURN_IF_FAILED(flyoutItem->put_Text(actionTitle.Get()));

        // Set the tooltip
        HString tooltip;
        RETURN_IF_FAILED(action->get_Tooltip(tooltip.GetAddressOf()));

        ComPtr<IDependencyObject> flyoutItemAsDependencyObject;
        RETURN_IF_FAILED(flyoutItem.As(&flyoutItemAsDependencyObject));
        SetTooltip(to_winrt(tooltip), to_winrt(flyoutItemAsDependencyObject));

        // Hook the menu item up to the action invoker
        ComPtr<IAdaptiveActionElement> actionParam(action);
        ComPtr<IAdaptiveActionInvoker> actionInvoker;
        RETURN_IF_FAILED(renderContext->get_ActionInvoker(&actionInvoker));
        EventRegistrationToken clickToken;
        RETURN_IF_FAILED(flyoutItem->add_Click(Callback<IRoutedEventHandler>(
                                                   [actionParam, actionInvoker](IInspectable* /*sender*/, IRoutedEventArgs*
                                                                                /*args*/) -> HRESULT
                                                   { return actionInvoker->SendActionEvent(actionParam.Get()); })
                                                   .Get(),
                                               &clickToken));

        // Add the new menu item to the vector
        ComPtr<IMenuFlyoutItemBase> flyoutItemAsBase;
        RETURN_IF_FAILED(flyoutItem.As(&flyoutItemAsBase));
        RETURN_IF_FAILED(flyoutItems->Append(flyoutItemAsBase.Get()));

        ComPtr<IUIElement> flyoutItemAsUIElement;
        RETURN_IF_FAILED(flyoutItem.As(&flyoutItemAsUIElement));
        RETURN_IF_FAILED(flyoutItemAsUIElement.CopyTo(flyoutUIItem));

        return S_OK;
    }

    void BuildInlineShowCard(rtom::AdaptiveCard const& adaptiveCard,
                             rtom::AdaptiveActionSet const& adaptiveActionSet,
                             rtom::IAdaptiveActionElement const& action,
                             rtxaml::Controls::Panel const& showCardsPanel,
                             rtxaml::UIElement actionButton,
                             rtxaml::UIElement actionOverflowItem,
                             uint32_t buttonIndex,
                             rtrender::AdaptiveRenderContext const& renderContext,
                             rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        auto hostConfig = renderContext.HostConfig();
        auto actionsConfig = hostConfig.Actions();
        auto showCardActionConfig = actionsConfig.ShowCard();
        rtrender::ActionMode showCardActionMode = showCardActionConfig.ActionMode();
        if (showCardActionMode == rtrender::ActionMode::Inline)
        {
            auto actionAsShowCardAction = action.as<rtom::AdaptiveShowCardAction>();
            auto showCard = actionAsShowCardAction.Card();
            auto uiShowCard = winrt::AdaptiveCards::Rendering::WinUI3::implementation::AdaptiveShowCardActionRenderer::BuildShowCard(
                showCard, renderContext, renderArgs, (adaptiveActionSet == nullptr));
            XamlHelpers::AppendXamlElementToPanel(uiShowCard, showCardsPanel);

            auto contextImpl = peek_innards<rtrender::implementation::AdaptiveRenderContext>(renderContext);
            if (adaptiveActionSet)
            {
                contextImpl->AddInlineShowCard(
                    adaptiveActionSet, actionAsShowCardAction, actionButton, actionOverflowItem, uiShowCard, buttonIndex, renderArgs);
            }
            else
            {
                contextImpl->AddInlineShowCard(adaptiveCard, actionAsShowCardAction, actionButton, actionOverflowItem, uiShowCard, buttonIndex, renderArgs);
            }
        }
    }

    rtxaml::UIElement CreateActionButtonInActionSet(
        rtom::AdaptiveCard const& adaptiveCard,
        rtom::AdaptiveActionSet const& adaptiveActionSet,
        rtom::IAdaptiveActionElement const& actionToCreate,
        bool buttonVisible,
        uint32_t columnIndex,
        rtxaml::Controls::Panel const& actionsPanel,
        rtxaml::Controls::Panel const& showCardPanel,
        winrt::Windows::Foundation::Collections::IVector<rtxaml::Controls::ColumnDefinition> const& columnDefinitions,
        rtxaml::UIElement const& overflowItem,
        rtrender::AdaptiveRenderContext const& renderContext,
        rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        // Render each action using the registered renderer
        rtom::IAdaptiveActionElement action = actionToCreate;
        auto actionType = action.ActionType();
        auto actionRegistration = renderContext.ActionRenderers();

        rtrender::IAdaptiveActionRenderer renderer;
        while (!renderer)
        {
            auto actionTypeString = action.ActionTypeString();
            renderer = actionRegistration.Get(actionTypeString);
            if (!renderer)
            {
                switch (action.FallbackType())
                {
                case rtom::FallbackType::Drop:
                    XamlHelpers::WarnForFallbackDrop(renderContext, actionTypeString);
                    return nullptr;

                case rtom::FallbackType::Content:
                    action = action.FallbackContent();
                    XamlHelpers::WarnForFallbackContentElement(renderContext, actionTypeString, action.ActionTypeString());
                    break; // Go again

                case rtom::FallbackType::None:
                    throw winrt::hresult_error(E_FAIL); // TODO: Really?
                }
            }
        }

        rtxaml::UIElement actionControl = renderer.Render(action, renderContext, renderArgs);

        if (!buttonVisible)
        {
            actionControl.Visibility(rtxaml::Visibility::Collapsed);
        }

        XamlHelpers::AppendXamlElementToPanel(actionControl, actionsPanel);

        if (columnDefinitions)
        {
            // If using the equal width columns, we'll add a column and assign the column
            rtxaml::Controls::ColumnDefinition columnDefinition;
            if (buttonVisible)
            {
                columnDefinition.Width({1.0, rtxaml::GridUnitType::Star});
            }
            else
            {
                columnDefinition.Width({0, rtxaml::GridUnitType::Auto});
            }
            rtxaml::Controls::Grid::SetColumn(actionControl.as<rtxaml::FrameworkElement>(), columnIndex);
        }

        if (actionType == rtom::ActionType::ShowCard)
        {
            // Build the inline show card.
            BuildInlineShowCard(adaptiveCard, adaptiveActionSet, action, showCardPanel, actionControl, overflowItem, columnIndex, renderContext, renderArgs);
        }

        return actionControl;
    }

    rtxaml::UIElement BuildActionSetHelper(rtom::AdaptiveCard const& adaptiveCard,
                                           rtom::AdaptiveActionSet const& adaptiveActionSet,
                                           winrt::Windows::Foundation::Collections::IVector<rtom::IAdaptiveActionElement> const& children,
                                           rtrender::AdaptiveRenderContext const& renderContext,
                                           rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        /* ComPtr<IAdaptiveHostConfig> hostConfig;
         RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
         ComPtr<IAdaptiveActionsConfig> actionsConfig;
         RETURN_IF_FAILED(hostConfig->get_Actions(actionsConfig.GetAddressOf()));*/

        auto hostConfig = renderContext.HostConfig();
        auto actionsConfig = hostConfig.Actions();

        /*ABI::AdaptiveCards::Rendering::WinUI3::ActionAlignment actionAlignment;
        RETURN_IF_FAILED(actionsConfig->get_ActionAlignment(&actionAlignment));

        ABI::AdaptiveCards::Rendering::WinUI3::ActionsOrientation actionsOrientation;
        RETURN_IF_FAILED(actionsConfig->get_ActionsOrientation(&actionsOrientation));*/

        rtrender::ActionAlignment actionAlignment = actionsConfig.ActionAlignment();
        rtrender::ActionsOrientation actionsOrientation = actionsConfig.ActionsOrientation();

        // Declare the panel that will host the buttons
        /* winrt::com_ptr<rtxaml::Controls::Panel> actionsPanel;*/
        rtxaml::Controls::Panel actionsPanel{nullptr};
        winrt::Windows::Foundation::Collections::IVector<rtxaml::Controls::ColumnDefinition> columnDefinitions;

        if (actionAlignment == rtrender::ActionAlignment::Stretch && actionsOrientation == rtrender::ActionsOrientation::Horizontal)
        {
            // If stretch alignment and orientation is horizontal, we use a grid with equal column widths to achieve
            // stretch behavior. For vertical orientation, we'll still just use a stack panel since the concept of
            // stretching buttons height isn't really valid, especially when the height of cards are typically dynamic.
            /*ComPtr<IGrid> actionsGrid =
                XamlHelpers::CreateABIClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));*/

            rtxaml::Controls::Grid actionsGrid;
            columnDefinitions = actionsGrid.ColumnDefinitions();
            // TODO: Am I doing this right?
            /* actionsPanel = winrt::make_self<rtxaml::Controls::Panel>(actionsGrid);*/
            actionsPanel = actionsGrid.as<rtxaml::Controls::Panel>();
            /*  RETURN_IF_FAILED(actionsGrid->get_ColumnDefinitions(&columnDefinitions));
              RETURN_IF_FAILED(actionsGrid.As(&actionsPanel));*/
        }
        else
        {
            // Create a stack panel for the action buttons
            /*ComPtr<IStackPanel> actionStackPanel =
                XamlHelpers::CreateABIClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));*/
            rtxaml::Controls::StackPanel actionStackPanel{};

            auto uiOrientation = actionsOrientation == rtrender::ActionsOrientation::Horizontal ?
                rtxaml::Controls::Orientation::Horizontal :
                rtxaml::Controls::Orientation::Vertical;

            actionStackPanel.Orientation(uiOrientation);

            /*RETURN_IF_FAILED(actionStackPanel->put_Orientation(uiOrientation));*/

            /* ComPtr<IFrameworkElement> actionsFrameworkElement;
             RETURN_IF_FAILED(actionStackPanel.As(&actionsFrameworkElement));*/

            switch (actionAlignment)
            {
            case rtrender::ActionAlignment::Center:
                // TODO: DO I need this cast?
                // actionsFrameworkElement.HorizontalAlignment(rtxaml::HorizontalAlignment::Center);
                actionStackPanel.HorizontalAlignment(rtxaml::HorizontalAlignment::Center);
                break;
            case rtrender::ActionAlignment::Left:
                actionStackPanel.HorizontalAlignment(rtxaml::HorizontalAlignment::Left);
                break;
            case rtrender::ActionAlignment::Right:
                actionStackPanel.HorizontalAlignment(rtxaml::HorizontalAlignment::Right);
                break;
            case rtrender::ActionAlignment::Stretch:
                actionStackPanel.HorizontalAlignment(rtxaml::HorizontalAlignment::Stretch);
                break;
            }

            // Add the action buttons to the stack panel
            // RETURN_IF_FAILED(actionStackPanel.As(&actionsPanel));
            // TODO: Can I just call as?
            // actionStackPanel.as(actionsPanel);
            /*actionsPanel = winrt::make_self<rtxaml::Controls::StackPanel>(actionStackPanel);*/
            // TODO: is this correct?
            actionsPanel = actionStackPanel.as<rtxaml::Controls::Panel>();
        }

        /*Thickness buttonMargin = reinterpret_cast<Thickness&>(GetButtonMargin(to_winrt(actionsConfig)));*/
        auto buttonMargin = GetButtonMargin(actionsConfig);
        if (actionsOrientation == rtrender::ActionsOrientation::Horizontal)
        {
            // Negate the spacing on the sides so the left and right buttons are flush on the side.
            // We do NOT remove the margin from the individual button itself, since that would cause
            // the equal columns stretch behavior to not have equal columns (since the first and last
            // button would be narrower without the same margins as its peers).
            /*ComPtr<IFrameworkElement> actionsPanelAsFrameworkElement;
            RETURN_IF_FAILED(actionsPanel.As(&actionsPanelAsFrameworkElement));
            RETURN_IF_FAILED(actionsPanelAsFrameworkElement->put_Margin({buttonMargin.Left * -1, 0, buttonMargin.Right * -1, 0}));*/
            actionsPanel.Margin({buttonMargin.Left * -1, 0, buttonMargin.Right * -1, 0});
        }
        else
        {
            // Negate the spacing on the top and bottom so the first and last buttons don't have extra padding
            /*ComPtr<IFrameworkElement> actionsPanelAsFrameworkElement;
            RETURN_IF_FAILED(actionsPanel.As(&actionsPanelAsFrameworkElement));
            RETURN_IF_FAILED(actionsPanelAsFrameworkElement->put_Margin({0, buttonMargin.Top * -1, 0, buttonMargin.Bottom * -1}));*/
            actionsPanel.Margin({0, buttonMargin.Top * -1, 0, buttonMargin.Bottom * -1});
        }

        // Get the max number of actions and check the host config to confirm whether we render actions beyond the max in the overflow menu
        /*UINT32 maxActions;
        RETURN_IF_FAILED(actionsConfig->get_MaxActions(&maxActions));*/
        auto maxActions = actionsConfig.MaxActions();

        auto hostConfigImpl = peek_innards<rtrender::implementation::AdaptiveHostConfig>(hostConfig);
        bool overflowMaxActions = hostConfigImpl->OverflowMaxActions();

        uint32_t currentButtonIndex = 0;
        uint32_t lastPrimaryActionIndex = 0;
        rtom::IAdaptiveActionElement lastPrimaryAction;
        bool allActionsHaveIcons{true};

        IterateOverVector<rtom::IAdaptiveActionElement>(children,
                                                        [&](rtom::IAdaptiveActionElement child)
                                                        {
                                                            winrt::hstring iconUrl = child.IconUrl();

                                                            if (iconUrl.empty())
                                                            {
                                                                allActionsHaveIcons = false;
                                                            }

                                                            // We need to figure out which button is going to be the last
                                                            // visible button. That button may need to be handled separately
                                                            // if we have show card actions in the overflow menu.
                                                            // TODO: Is this correct? or winrt_make is needed here?
                                                            rtom::IAdaptiveActionElement action(child);
                                                            rtom::ActionMode mode = action.Mode();

                                                            if (currentButtonIndex < maxActions && mode == rtom::ActionMode::Primary)
                                                            {
                                                                lastPrimaryActionIndex = currentButtonIndex;
                                                                lastPrimaryAction = action;
                                                                currentButtonIndex++;
                                                            }
                                                        });

        renderArgs.AllowAboveTitleIconPlacement(allActionsHaveIcons);

        /* ComPtr<IStackPanel> showCardsStackPanel =
             XamlHelpers::CreateABIClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
         ComPtr<IPanel> showCardsPanel;
         RETURN_IF_FAILED(showCardsStackPanel.As(&showCardsPanel));*/
        rtxaml::Controls::StackPanel showCardsStackPanel{};
        rtxaml::Controls::Panel showCardsPanel = showCardsStackPanel.as<rtxaml::Controls::Panel>();
        /*ComPtr<IGridStatics> gridStatics;
        RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));*/

        currentButtonIndex = 0;
        bool pastLastPrimaryAction = false;
        /* ComPtr<IButton> overflowButton;
         std::vector<std::pair<ComPtr<IAdaptiveActionElement>, ComPtr<IUIElement>>> showCardOverflowButtons;*/
        rtxaml::Controls::Button overflowButton;
        std::vector<std::pair<rtom::IAdaptiveActionElement, rtxaml::UIElement>> showCardOverflowButtons;
        IterateOverVector<rtom::IAdaptiveActionElement>(
            children,
            [&](rtom::IAdaptiveActionElement child)
            {
                // TODO: is this correct?
                /*ComPtr<IAdaptiveActionElement> action(child);*/
                rtom::IAdaptiveActionElement action(child);
                rtom::ActionMode mode = action.Mode();

                rtom::ActionType actionType = action.ActionType();
                // TODO: can I just construct rtxaml::IUIElement instead?
                // ComPtr<IUIElement> actionControl;
                /*  winrt::com_ptr<rtxaml::UIElement> actionControl;*/
                rtxaml::UIElement actionControl{nullptr};

                if (!pastLastPrimaryAction && mode == rtom::ActionMode::Primary)
                {
                    // The last button may need special handling so don't handle it here
                    if (currentButtonIndex != lastPrimaryActionIndex)
                    {
                        // If we have fewer than the maximum number of actions and this action's mode is primary, make a button
                        // TODO: Can we do this? How to properly assign UIElement to COM_PTR, use peek_innards? can I use .as(&comPtr)?
                        actionControl = CreateActionButtonInActionSet(adaptiveCard,
                                                                      adaptiveActionSet,
                                                                      action,
                                                                      true,
                                                                      currentButtonIndex,
                                                                      actionsPanel,
                                                                      showCardsPanel,
                                                                      columnDefinitions,
                                                                      nullptr,
                                                                      renderContext,
                                                                      renderArgs);

                        currentButtonIndex++;
                    }
                    else
                    {
                        pastLastPrimaryAction = true;
                    }
                }
                else if (pastLastPrimaryAction && (mode == rtom::ActionMode::Primary) && !overflowMaxActions)
                {
                    // If we have more primary actions than the max actions and we're not allowed to overflow them just set a warning and continue
                    renderContext.AddWarning(rtom::WarningStatusCode::MaxActionsExceeded,
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
                    // RETURN_IF_FAILED(AddOverflowFlyoutItem(action.Get(), overflowButton.Get(), renderContext, &actionControl));
                    AddOverflowFlyoutItem(action, overflowButton, renderContext);

                    // Show card actions in the overflow menu move to the action bar when selected, so we need to keep track
                    // of these so we can make non-visible buttons for them later. They need to go after all the actions we're creating as primary.
                    if (actionType == rtom::ActionType::ShowCard)
                    {
                        showCardOverflowButtons.emplace_back(std::make_pair(action, actionControl));
                    }

                    // If this was supposed to be a primary action but it got overflowed due to max actions, add a warning
                    if (mode == rtom::ActionMode::Primary)
                    {
                        renderContext.AddWarning(rtom::WarningStatusCode::MaxActionsExceeded,
                                                 {L"Some actions were moved to an overflow menu due to exceeding the maximum number of actions allowed"});
                    }
                }
            });

        /*  winrt::com_ptr<rtxaml::UIElement> lastActionOverflowItem;*/
        rtxaml::UIElement lastActionOverflowItem{nullptr};
        if (overflowButton != nullptr && showCardOverflowButtons.size() != 0)
        {
            // Show card actions from the overflow menu switch places with the last primary action when invoked.
            // If we any primary actions, create a non-visible overflow item for the last primary action. This
            // allows it to be moved to the overflow menu to make space for a show card action.

            if (lastPrimaryAction != nullptr)
            {
                lastActionOverflowItem = AddOverflowFlyoutItem(lastPrimaryAction, overflowButton, renderContext);
                lastActionOverflowItem.Visibility(rtxaml::Visibility::Collapsed);
            }

            // Create non-visible primary buttons for all overflow show card actions so they can be moved to the action bar when invoked
            for (auto& overflowShowCard : showCardOverflowButtons)
            {
                auto createdButton = CreateActionButtonInActionSet(adaptiveCard,
                                                                   adaptiveActionSet,
                                                                   overflowShowCard.first,
                                                                   false,
                                                                   currentButtonIndex,
                                                                   actionsPanel,
                                                                   showCardsPanel,
                                                                   columnDefinitions,
                                                                   overflowShowCard.second,
                                                                   renderContext,
                                                                   renderArgs);
                currentButtonIndex++;
            }
        }

        // Now that we have the overflow item if needed, we can create the button for the last primary action
        if (lastPrimaryAction != nullptr)
        {
            auto createdButton = CreateActionButtonInActionSet(adaptiveCard,
                                                               adaptiveActionSet,
                                                               lastPrimaryAction,
                                                               true,
                                                               currentButtonIndex,
                                                               actionsPanel,
                                                               showCardsPanel,
                                                               columnDefinitions,
                                                               lastActionOverflowItem,
                                                               renderContext,
                                                               renderArgs);
            currentButtonIndex++;
        }

        // Lastly add the overflow button itself to the action panel
        if (overflowButton != nullptr)
        {
            // If using equal width columns, add another column and assign the it to the overflow button
            if (columnDefinitions != nullptr)
            {
                /* ComPtr<IColumnDefinition> columnDefinition = XamlHelpers::CreateABIClass<IColumnDefinition>(
                     HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));*/
                /*  RETURN_IF_FAILED(columnDefinition->put_Width({1.0, GridUnitType::GridUnitType_Star}));
                  RETURN_IF_FAILED(columnDefinitions->Append(columnDefinition.Get()));*/
                rtxaml::Controls::ColumnDefinition columnDefinition{};
                columnDefinition.Width({1.0, rtxaml::GridUnitType::Star});
                columnDefinitions.Append(columnDefinition);

                /* ComPtr<IFrameworkElement> actionFrameworkElement;
                 THROW_IF_FAILED(overflowButton.As(&actionFrameworkElement));
                 THROW_IF_FAILED(gridStatics->SetColumn(actionFrameworkElement.Get(), currentButtonIndex));*/
                // TODO: No need to convert, right?
                rtxaml::Controls::Grid::SetColumn(overflowButton, currentButtonIndex);
            }

            // Add the overflow button to the panel
            XamlHelpers::AppendXamlElementToPanel(overflowButton, actionsPanel);

            // Register the overflow button with the render context
            /* ComPtr<IUIElement> overflowButtonAsUIElement;
             overflowButton.As(&overflowButtonAsUIElement);*/

            auto contextImpl = peek_innards<rtrender::implementation::AdaptiveRenderContext>(renderContext);

            if (adaptiveActionSet != nullptr)
            {
                // TODO: no need to .as<rtxaml::UIElement> for overflowButton, correct?
                contextImpl->AddOverflowButton(adaptiveActionSet, overflowButton);
            }
            else
            {
                contextImpl->AddOverflowButton(adaptiveCard, overflowButton);
            }
        }

        // Reset icon placement value
        /*  RETURN_IF_FAILED(renderArgs->put_AllowAboveTitleIconPlacement(false));*/
        renderArgs.AllowAboveTitleIconPlacement(false);

        /*ComPtr<IFrameworkElement> actionsPanelAsFrameworkElement;
        RETURN_IF_FAILED(actionsPanel.As(&actionsPanelAsFrameworkElement));
        RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                     L"Adaptive.Actions",
                                                                     actionsPanelAsFrameworkElement.Get()));*/
        XamlHelpers::SetStyleFromResourceDictionary(renderContext, {L"Adapative.Actions"}, actionsPanel);

        /*  ComPtr<IStackPanel> actionSet =
              XamlHelpers::CreateABIClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
          ComPtr<IPanel> actionSetAsPanel;
          actionSet.As(&actionSetAsPanel);*/
        rtxaml::Controls::StackPanel actionPanel;

        // Add buttons and show cards to panel
        XamlHelpers::AppendXamlElementToPanel(actionsPanel, actionPanel);
        XamlHelpers::AppendXamlElementToPanel(showCardsStackPanel, actionPanel);

        return actionPanel;
    }

    rtxaml::Controls::Button CreateAppropriateButton(rtom::IAdaptiveActionElement const& action)
    {
        if (action && (action.ActionType() == rtom::ActionType::OpenUrl))
        {
            return winrt::make<LinkButton>();
        }
        else
        {
            return rtxaml::Controls::Button{};
        }
    }
}
