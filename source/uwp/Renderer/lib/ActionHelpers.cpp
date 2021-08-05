// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "ActionHelpers.h"
#include "AdaptiveRenderArgs.h"
#include "AdaptiveShowCardActionRenderer.h"
#include "LinkButton.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Automation;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::UI::Xaml::Input;
using namespace ABI::Windows::UI::Xaml::Media;

namespace AdaptiveCards::Rendering::Uwp::ActionHelpers
{
    HRESULT GetButtonMargin(_In_ IAdaptiveActionsConfig* actionsConfig, Thickness& buttonMargin) noexcept
    {
        buttonMargin = {0, 0, 0, 0};
        UINT32 buttonSpacing;
        RETURN_IF_FAILED(actionsConfig->get_ButtonSpacing(&buttonSpacing));

        ABI::AdaptiveCards::Rendering::Uwp::ActionsOrientation actionsOrientation;
        RETURN_IF_FAILED(actionsConfig->get_ActionsOrientation(&actionsOrientation));

        if (actionsOrientation == ABI::AdaptiveCards::Rendering::Uwp::ActionsOrientation::Horizontal)
        {
            buttonMargin.Left = buttonMargin.Right = buttonSpacing / 2;
        }
        else
        {
            buttonMargin.Top = buttonMargin.Bottom = buttonSpacing / 2;
        }

        return S_OK;
    }

    void SetTooltip(_In_opt_ HSTRING toolTipText, _In_ IDependencyObject* tooltipTarget)
    {
        if (toolTipText != nullptr)
        {
            ComPtr<ITextBlock> tooltipTextBlock =
                XamlHelpers::CreateABIClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
            THROW_IF_FAILED(tooltipTextBlock->put_Text(toolTipText));

            ComPtr<IToolTip> toolTip =
                XamlHelpers::CreateABIClass<IToolTip>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ToolTip));
            ComPtr<IContentControl> toolTipAsContentControl;
            THROW_IF_FAILED(toolTip.As(&toolTipAsContentControl));
            THROW_IF_FAILED(toolTipAsContentControl->put_Content(tooltipTextBlock.Get()));

            ComPtr<IToolTipServiceStatics> toolTipService;
            THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ToolTipService).Get(),
                                                 &toolTipService));

            THROW_IF_FAILED(toolTipService->SetToolTip(tooltipTarget, toolTip.Get()));
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

    void ArrangeButtonContent(_In_ IAdaptiveActionElement* action,
                              _In_ IAdaptiveActionsConfig* actionsConfig,
                              _In_ IAdaptiveRenderContext* renderContext,
                              ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle containerStyle,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                              bool allActionsHaveIcons,
                              _In_ IButton* button)
    {
        HString title;
        THROW_IF_FAILED(action->get_Title(title.GetAddressOf()));

        HString iconUrl;
        THROW_IF_FAILED(action->get_IconUrl(iconUrl.GetAddressOf()));

        HString tooltip;
        THROW_IF_FAILED(action->get_Tooltip(tooltip.GetAddressOf()));

        HString name;
        HString description;
        if (title.IsValid())
        {
            // If we have a title, use title as the automation name and tooltip as the description
            name.Set(title.Get());
            description.Set(tooltip.Get());
        }
        else
        {
            // If there's no title, use tooltip as the name
            name.Set(tooltip.Get());
        }

        ComPtr<IButton> localButton(button);
        ComPtr<IDependencyObject> buttonAsDependencyObject;
        THROW_IF_FAILED(localButton.As(&buttonAsDependencyObject));
        SetAutomationNameAndDescription(buttonAsDependencyObject.Get(), name.Get(), description.Get());
        SetTooltip(tooltip.Get(), buttonAsDependencyObject.Get());

        // Check if the button has an iconUrl
        if (iconUrl != nullptr)
        {
            // Get icon configs
            ABI::AdaptiveCards::Rendering::Uwp::IconPlacement iconPlacement;
            UINT32 iconSize;

            THROW_IF_FAILED(actionsConfig->get_IconPlacement(&iconPlacement));
            THROW_IF_FAILED(actionsConfig->get_IconSize(&iconSize));

            // Define the alignment for the button contents
            ComPtr<IStackPanel> buttonContentsStackPanel =
                XamlHelpers::CreateABIClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));

            // Create image and add it to the button
            ComPtr<IAdaptiveImage> adaptiveImage = XamlHelpers::CreateABIClass<IAdaptiveImage>(
                HStringReference(RuntimeClass_AdaptiveCards_ObjectModel_Uwp_AdaptiveImage));

            THROW_IF_FAILED(adaptiveImage->put_Url(iconUrl.Get()));

            THROW_IF_FAILED(adaptiveImage->put_HorizontalAlignment(
                winrt::box_value(winrt::AdaptiveCards::ObjectModel::Uwp::HAlignment::Center)
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>>()
                    .get()));

            ComPtr<IAdaptiveCardElement> adaptiveCardElement;
            THROW_IF_FAILED(adaptiveImage.As(&adaptiveCardElement));
            ComPtr<AdaptiveRenderArgs> childRenderArgs;
            THROW_IF_FAILED(
                MakeAndInitialize<AdaptiveRenderArgs>(&childRenderArgs, containerStyle, buttonContentsStackPanel.Get(), nullptr));

            ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
            THROW_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));

            ComPtr<IUIElement> buttonIcon;
            ComPtr<IAdaptiveElementRenderer> elementRenderer;
            THROW_IF_FAILED(elementRenderers->Get(HStringReference(L"Image").Get(), &elementRenderer));
            if (elementRenderer != nullptr)
            {
                elementRenderer->Render(adaptiveCardElement.Get(), renderContext, childRenderArgs.Get(), &buttonIcon);
                if (buttonIcon == nullptr)
                {
                    XamlHelpers::SetContent(localButton.Get(), title.Get());
                    return;
                }
            }

            // Create title text block
            ComPtr<ITextBlock> buttonText =
                XamlHelpers::CreateABIClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
            THROW_IF_FAILED(buttonText->put_Text(title.Get()));
            THROW_IF_FAILED(buttonText->put_TextAlignment(TextAlignment::TextAlignment_Center));

            ComPtr<IFrameworkElement> buttonTextAsFrameworkElement;
            THROW_IF_FAILED(buttonText.As(&buttonTextAsFrameworkElement));
            THROW_IF_FAILED(buttonTextAsFrameworkElement->put_VerticalAlignment(
                ABI::Windows::UI::Xaml::VerticalAlignment::VerticalAlignment_Center));

            // Handle different arrangements inside button
            ComPtr<IFrameworkElement> buttonIconAsFrameworkElement;
            THROW_IF_FAILED(buttonIcon.As(&buttonIconAsFrameworkElement));

            // Set icon height to iconSize (aspect ratio is automatically maintained)
            THROW_IF_FAILED(buttonIconAsFrameworkElement->put_Height(iconSize));

            ComPtr<IUIElement> separator;
            if (iconPlacement == ABI::AdaptiveCards::Rendering::Uwp::IconPlacement::AboveTitle && allActionsHaveIcons)
            {
                THROW_IF_FAILED(buttonContentsStackPanel->put_Orientation(Orientation::Orientation_Vertical));
            }
            else
            {
                THROW_IF_FAILED(buttonContentsStackPanel->put_Orientation(Orientation::Orientation_Horizontal));

                // Only add spacing when the icon must be located at the left of the title
                UINT spacingSize;
                THROW_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig, ABI::AdaptiveCards::ObjectModel::Uwp::Spacing::Default, &spacingSize));

                ABI::Windows::UI::Color color = {0};
                separator = XamlHelpers::CreateSeparator(renderContext, spacingSize, spacingSize, color, false);
            }

            ComPtr<IPanel> buttonContentsPanel;
            THROW_IF_FAILED(buttonContentsStackPanel.As(&buttonContentsPanel));

            // Add image to stack panel
            XamlHelpers::AppendXamlElementToPanel(buttonIcon.Get(), buttonContentsPanel.Get());

            // Add separator to stack panel
            if (separator != nullptr)
            {
                XamlHelpers::AppendXamlElementToPanel(separator.Get(), buttonContentsPanel.Get());
            }

            // Add text to stack panel
            XamlHelpers::AppendXamlElementToPanel(buttonText.Get(), buttonContentsPanel.Get());

            // Finally, put the stack panel inside the final button
            ComPtr<IContentControl> buttonContentControl;
            THROW_IF_FAILED(localButton.As(&buttonContentControl));
            THROW_IF_FAILED(buttonContentControl->put_Content(buttonContentsPanel.Get()));
        }
        else
        {
            XamlHelpers::SetContent(localButton.Get(), title.Get());
        }
    }

    HRESULT HandleActionStyling(_In_ IAdaptiveActionElement* adaptiveActionElement,
                                _In_ IFrameworkElement* buttonFrameworkElement,
                                _In_ IAdaptiveRenderContext* renderContext)
    {
        HString actionSentiment;
        RETURN_IF_FAILED(adaptiveActionElement->get_Style(actionSentiment.GetAddressOf()));

        INT32 isSentimentPositive{}, isSentimentDestructive{}, isSentimentDefault{};

        ComPtr<IResourceDictionary> resourceDictionary;
        RETURN_IF_FAILED(renderContext->get_OverrideStyles(&resourceDictionary));
        ComPtr<IStyle> styleToApply;

        ComPtr<AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext> contextImpl =
            PeekInnards<AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext>(renderContext);

        if ((SUCCEEDED(WindowsCompareStringOrdinal(actionSentiment.Get(), HStringReference(L"default").Get(), &isSentimentDefault)) &&
             (isSentimentDefault == 0)) ||
            WindowsIsStringEmpty(actionSentiment.Get()))
        {
            RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Action", buttonFrameworkElement));
        }
        else if (SUCCEEDED(WindowsCompareStringOrdinal(actionSentiment.Get(), HStringReference(L"positive").Get(), &isSentimentPositive)) &&
                 (isSentimentPositive == 0))
        {
            if (SUCCEEDED(XamlHelpers::TryGetResourceFromResourceDictionaries<IStyle>(resourceDictionary.Get(),
                                                                                      L"Adaptive.Action.Positive",
                                                                                      &styleToApply)))
            {
                RETURN_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
            }
            else
            {
                // By default, set the action background color to accent color
                ComPtr<IResourceDictionary> actionSentimentDictionary = contextImpl->GetDefaultActionSentimentDictionary();

                if (SUCCEEDED(XamlHelpers::TryGetResourceFromResourceDictionaries(actionSentimentDictionary.Get(),
                                                                                  L"PositiveActionDefaultStyle",
                                                                                  styleToApply.GetAddressOf())))
                {
                    RETURN_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
                }
            }
        }
        else if (SUCCEEDED(WindowsCompareStringOrdinal(actionSentiment.Get(), HStringReference(L"destructive").Get(), &isSentimentDestructive)) &&
                 (isSentimentDestructive == 0))
        {
            if (SUCCEEDED(XamlHelpers::TryGetResourceFromResourceDictionaries<IStyle>(resourceDictionary.Get(),
                                                                                      L"Adaptive.Action.Destructive",
                                                                                      &styleToApply)))
            {
                RETURN_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
            }
            else
            {
                // By default, set the action text color to attention color
                ComPtr<IResourceDictionary> actionSentimentDictionary = contextImpl->GetDefaultActionSentimentDictionary();

                if (SUCCEEDED(XamlHelpers::TryGetResourceFromResourceDictionaries(actionSentimentDictionary.Get(),
                                                                                  L"DestructiveActionDefaultStyle",
                                                                                  styleToApply.GetAddressOf())))
                {
                    RETURN_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
                }
            }
        }
        else
        {
            HString actionSentimentStyle;
            RETURN_IF_FAILED(WindowsConcatString(HStringReference(L"Adaptive.Action.").Get(),
                                                 actionSentiment.Get(),
                                                 actionSentimentStyle.GetAddressOf()));
            RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext, actionSentimentStyle.Get(), buttonFrameworkElement));
        }
        return S_OK;
    }

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

    HRESULT BuildAction(_In_ IAdaptiveActionElement* adaptiveActionElement,
                        _In_ IAdaptiveRenderContext* renderContext,
                        _In_ IAdaptiveRenderArgs* renderArgs,
                        _Outptr_ IUIElement** actionControl)
    {
        // determine what type of action we're building
        ComPtr<IAdaptiveActionElement> action(adaptiveActionElement);

        // now construct an appropriate button for the action type
        ComPtr<IButton> button;
        try
        {
            CreateAppropriateButton(action.Get(), button);
        }
        CATCH_RETURN;

        ComPtr<IFrameworkElement> buttonFrameworkElement;
        RETURN_IF_FAILED(button.As(&buttonFrameworkElement));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ComPtr<IAdaptiveActionsConfig> actionsConfig;
        RETURN_IF_FAILED(hostConfig->get_Actions(actionsConfig.GetAddressOf()));

        Thickness buttonMargin;
        RETURN_IF_FAILED(GetButtonMargin(actionsConfig.Get(), buttonMargin));
        RETURN_IF_FAILED(buttonFrameworkElement->put_Margin(buttonMargin));

        ABI::AdaptiveCards::Rendering::Uwp::ActionsOrientation actionsOrientation;
        RETURN_IF_FAILED(actionsConfig->get_ActionsOrientation(&actionsOrientation));

        ABI::AdaptiveCards::Rendering::Uwp::ActionAlignment actionAlignment;
        RETURN_IF_FAILED(actionsConfig->get_ActionAlignment(&actionAlignment));

        if (actionsOrientation == ABI::AdaptiveCards::Rendering::Uwp::ActionsOrientation::Horizontal)
        {
            // For horizontal alignment, we always use stretch
            RETURN_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(
                ABI::Windows::UI::Xaml::HorizontalAlignment::HorizontalAlignment_Stretch));
        }
        else
        {
            switch (actionAlignment)
            {
            case ABI::AdaptiveCards::Rendering::Uwp::ActionAlignment::Center:
                RETURN_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Center));
                break;
            case ABI::AdaptiveCards::Rendering::Uwp::ActionAlignment::Left:
                RETURN_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Left));
                break;
            case ABI::AdaptiveCards::Rendering::Uwp::ActionAlignment::Right:
                RETURN_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Right));
                break;
            case ABI::AdaptiveCards::Rendering::Uwp::ActionAlignment::Stretch:
                RETURN_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Stretch));
                break;
            }
        }

        ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle containerStyle;
        RETURN_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));

        boolean allowAboveTitleIconPlacement;
        RETURN_IF_FAILED(renderArgs->get_AllowAboveTitleIconPlacement(&allowAboveTitleIconPlacement));

        ArrangeButtonContent(action.Get(),
                             actionsConfig.Get(),
                             renderContext,
                             containerStyle,
                             hostConfig.Get(),
                             allowAboveTitleIconPlacement,
                             button.Get());

        ComPtr<IAdaptiveShowCardActionConfig> showCardActionConfig;
        RETURN_IF_FAILED(actionsConfig->get_ShowCard(&showCardActionConfig));
        ABI::AdaptiveCards::Rendering::Uwp::ActionMode showCardActionMode;
        RETURN_IF_FAILED(showCardActionConfig->get_ActionMode(&showCardActionMode));

        // Add click handler which calls IAdaptiveActionInvoker::SendActionEvent
        ComPtr<IButtonBase> buttonBase;
        RETURN_IF_FAILED(button.As(&buttonBase));

        ComPtr<IAdaptiveActionInvoker> actionInvoker;
        RETURN_IF_FAILED(renderContext->get_ActionInvoker(&actionInvoker));
        EventRegistrationToken clickToken;
        RETURN_IF_FAILED(buttonBase->add_Click(Callback<IRoutedEventHandler>([action, actionInvoker](IInspectable* /*sender*/, IRoutedEventArgs*
                                                                                                     /*args*/) -> HRESULT {
                                                   return actionInvoker->SendActionEvent(action.Get());
                                               }).Get(),
                                               &clickToken));

        boolean isEnabled;
        RETURN_IF_FAILED(adaptiveActionElement->get_IsEnabled(&isEnabled));

        ComPtr<IControl> buttonAsControl;
        RETURN_IF_FAILED(buttonBase.As(&buttonAsControl));

        RETURN_IF_FAILED(buttonAsControl->put_IsEnabled(isEnabled));

        RETURN_IF_FAILED(HandleActionStyling(adaptiveActionElement, buttonFrameworkElement.Get(), renderContext));

        ComPtr<IUIElement> buttonAsUIElement;
        RETURN_IF_FAILED(button.As(&buttonAsUIElement));
        *actionControl = buttonAsUIElement.Detach();
        return S_OK;
    }

    bool WarnForInlineShowCard(_In_ IAdaptiveRenderContext* renderContext, _In_ IAdaptiveActionElement* action, const std::wstring& warning)
    {
        if (action != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::ActionType actionType;
            THROW_IF_FAILED(action->get_ActionType(&actionType));

            if (actionType == ABI::AdaptiveCards::ObjectModel::Uwp::ActionType::ShowCard)
            {
                THROW_IF_FAILED(renderContext->AddWarning(ABI::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode::UnsupportedValue,
                                                          HStringReference(warning.c_str()).Get()));
                return true;
            }
        }

        return false;
    }

    static HRESULT HandleKeydownForInlineAction(_In_ IKeyRoutedEventArgs* args,
                                                _In_ IAdaptiveActionInvoker* actionInvoker,
                                                _In_ IAdaptiveActionElement* inlineAction)
    {
        ABI::Windows::System::VirtualKey key;
        RETURN_IF_FAILED(args->get_Key(&key));

        if (key == ABI::Windows::System::VirtualKey::VirtualKey_Enter)
        {
            ComPtr<ABI::Windows::UI::Core::ICoreWindowStatic> coreWindowStatics;
            RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Core_CoreWindow).Get(), &coreWindowStatics));

            ComPtr<ABI::Windows::UI::Core::ICoreWindow> coreWindow;
            RETURN_IF_FAILED(coreWindowStatics->GetForCurrentThread(&coreWindow));

            ABI::Windows::UI::Core::CoreVirtualKeyStates shiftKeyState;
            RETURN_IF_FAILED(coreWindow->GetKeyState(ABI::Windows::System::VirtualKey_Shift, &shiftKeyState));

            ABI::Windows::UI::Core::CoreVirtualKeyStates ctrlKeyState;
            RETURN_IF_FAILED(coreWindow->GetKeyState(ABI::Windows::System::VirtualKey_Control, &ctrlKeyState));

            if (shiftKeyState == ABI::Windows::UI::Core::CoreVirtualKeyStates_None &&
                ctrlKeyState == ABI::Windows::UI::Core::CoreVirtualKeyStates_None)
            {
                RETURN_IF_FAILED(actionInvoker->SendActionEvent(inlineAction));
                RETURN_IF_FAILED(args->put_Handled(true));
            }
        }

        return S_OK;
    }

    void HandleInlineAction(_In_ IAdaptiveRenderContext* renderContext,
                            _In_ IAdaptiveRenderArgs* renderArgs,
                            _In_ ITextBox* textBox,
                            _In_ IUIElement* textBoxParentContainer,
                            _In_ IAdaptiveActionElement* inlineAction,
                            _COM_Outptr_ IUIElement** textBoxWithInlineAction)
    {
        ComPtr<IUIElement> localTextBoxContainer(textBoxParentContainer);
        ComPtr<IAdaptiveActionElement> localInlineAction(inlineAction);

        ABI::AdaptiveCards::ObjectModel::Uwp::ActionType actionType;
        THROW_IF_FAILED(localInlineAction->get_ActionType(&actionType));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        // Inline ShowCards are not supported for inline actions
        if (WarnForInlineShowCard(renderContext, localInlineAction.Get(), L"Inline ShowCard not supported for InlineAction"))
        {
            THROW_IF_FAILED(localTextBoxContainer.CopyTo(textBoxWithInlineAction));
            return;
        }

        if ((actionType == ABI::AdaptiveCards::ObjectModel::Uwp::ActionType::Submit) ||
            (actionType == ABI::AdaptiveCards::ObjectModel::Uwp::ActionType::Execute))
        {
            THROW_IF_FAILED(renderContext->LinkSubmitActionToCard(localInlineAction.Get(), renderArgs));
        }

        // Create a grid to hold the text box and the action button
        ComPtr<IGridStatics> gridStatics;
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));

        ComPtr<IGrid> xamlGrid =
            XamlHelpers::CreateABIClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IVector<ColumnDefinition*>> columnDefinitions;
        THROW_IF_FAILED(xamlGrid->get_ColumnDefinitions(&columnDefinitions));
        ComPtr<IPanel> gridAsPanel;
        THROW_IF_FAILED(xamlGrid.As(&gridAsPanel));

        // Create the first column and add the text box to it
        ComPtr<IColumnDefinition> textBoxColumnDefinition = XamlHelpers::CreateABIClass<IColumnDefinition>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
        THROW_IF_FAILED(textBoxColumnDefinition->put_Width({1, GridUnitType::GridUnitType_Star}));
        THROW_IF_FAILED(columnDefinitions->Append(textBoxColumnDefinition.Get()));

        ComPtr<IFrameworkElement> textBoxContainerAsFrameworkElement;
        THROW_IF_FAILED(localTextBoxContainer.As(&textBoxContainerAsFrameworkElement));

        THROW_IF_FAILED(gridStatics->SetColumn(textBoxContainerAsFrameworkElement.Get(), 0));
        XamlHelpers::AppendXamlElementToPanel(textBoxContainerAsFrameworkElement.Get(), gridAsPanel.Get());

        // Create a separator column
        ComPtr<IColumnDefinition> separatorColumnDefinition = XamlHelpers::CreateABIClass<IColumnDefinition>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
        THROW_IF_FAILED(separatorColumnDefinition->put_Width({1.0, GridUnitType::GridUnitType_Auto}));
        THROW_IF_FAILED(columnDefinitions->Append(separatorColumnDefinition.Get()));

        UINT spacingSize;
        THROW_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig.Get(), ABI::AdaptiveCards::ObjectModel::Uwp::Spacing::Default, &spacingSize));

        auto separator = XamlHelpers::CreateSeparator(renderContext, spacingSize, 0, {0}, false);

        ComPtr<IFrameworkElement> separatorAsFrameworkElement;
        THROW_IF_FAILED(separator.As(&separatorAsFrameworkElement));

        THROW_IF_FAILED(gridStatics->SetColumn(separatorAsFrameworkElement.Get(), 1));
        XamlHelpers::AppendXamlElementToPanel(separator.Get(), gridAsPanel.Get());

        // Create a column for the button
        ComPtr<IColumnDefinition> inlineActionColumnDefinition = XamlHelpers::CreateABIClass<IColumnDefinition>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
        THROW_IF_FAILED(inlineActionColumnDefinition->put_Width({0, GridUnitType::GridUnitType_Auto}));
        THROW_IF_FAILED(columnDefinitions->Append(inlineActionColumnDefinition.Get()));

        HString iconUrl;
        THROW_IF_FAILED(localInlineAction->get_IconUrl(iconUrl.GetAddressOf()));
        ComPtr<IUIElement> actionUIElement;
        if (iconUrl != nullptr)
        {
            // Render the icon using the adaptive image renderer
            ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
            THROW_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
            ComPtr<IAdaptiveElementRenderer> imageRenderer;
            THROW_IF_FAILED(elementRenderers->Get(HStringReference(L"Image").Get(), &imageRenderer));

            ComPtr<IAdaptiveImage> adaptiveImage = XamlHelpers::CreateABIClass<IAdaptiveImage>(
                HStringReference(RuntimeClass_AdaptiveCards_ObjectModel_Uwp_AdaptiveImage));

            THROW_IF_FAILED(adaptiveImage->put_Url(iconUrl.Get()));

            ComPtr<IAdaptiveCardElement> adaptiveImageAsElement;
            THROW_IF_FAILED(adaptiveImage.As(&adaptiveImageAsElement));

            THROW_IF_FAILED(imageRenderer->Render(adaptiveImageAsElement.Get(), renderContext, renderArgs, &actionUIElement));
        }
        else
        {
            // If there's no icon, just use the title text. Put it centered in a grid so it is
            // centered relative to the text box.
            HString title;
            THROW_IF_FAILED(localInlineAction->get_Title(title.GetAddressOf()));

            ComPtr<ITextBlock> titleTextBlock =
                XamlHelpers::CreateABIClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
            THROW_IF_FAILED(titleTextBlock->put_Text(title.Get()));

            ComPtr<IFrameworkElement> textBlockAsFrameworkElement;
            THROW_IF_FAILED(titleTextBlock.As(&textBlockAsFrameworkElement));
            THROW_IF_FAILED(textBlockAsFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Center));

            ComPtr<IGrid> titleGrid =
                XamlHelpers::CreateABIClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
            ComPtr<IPanel> panel;
            THROW_IF_FAILED(titleGrid.As(&panel));
            XamlHelpers::AppendXamlElementToPanel(titleTextBlock.Get(), panel.Get());

            THROW_IF_FAILED(panel.As(&actionUIElement));
        }

        // Make the action the same size as the text box
        EventRegistrationToken eventToken;
        THROW_IF_FAILED(textBoxContainerAsFrameworkElement->add_Loaded(
            Callback<IRoutedEventHandler>([actionUIElement, textBoxContainerAsFrameworkElement](IInspectable* /*sender*/, IRoutedEventArgs*
                                                                                                /*args*/) -> HRESULT {
                ComPtr<IFrameworkElement> actionFrameworkElement;
                RETURN_IF_FAILED(actionUIElement.As(&actionFrameworkElement));

                return ActionHelpers::SetMatchingHeight(actionFrameworkElement.Get(), textBoxContainerAsFrameworkElement.Get());
            }).Get(),
            &eventToken));

        // Wrap the action in a button
        ComPtr<IUIElement> touchTargetUIElement;
        WrapInTouchTarget(nullptr,
                          actionUIElement.Get(),
                          localInlineAction.Get(),
                          renderContext,
                          false,
                          L"Adaptive.Input.Text.InlineAction",
                          nullptr,
                          (iconUrl != nullptr),
                          &touchTargetUIElement);

        ComPtr<IFrameworkElement> touchTargetFrameworkElement;
        THROW_IF_FAILED(touchTargetUIElement.As(&touchTargetFrameworkElement));

        // Align to bottom so the icon stays with the bottom of the text box as it grows in the multiline case
        THROW_IF_FAILED(touchTargetFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Bottom));

        // Add the action to the column
        THROW_IF_FAILED(gridStatics->SetColumn(touchTargetFrameworkElement.Get(), 2));
        XamlHelpers::AppendXamlElementToPanel(touchTargetFrameworkElement.Get(), gridAsPanel.Get());

        // If this isn't a multiline input, enter should invoke the action
        ComPtr<IAdaptiveActionInvoker> actionInvoker;
        THROW_IF_FAILED(renderContext->get_ActionInvoker(&actionInvoker));

        boolean isMultiLine;
        THROW_IF_FAILED(textBox->get_AcceptsReturn(&isMultiLine));

        if (!isMultiLine)
        {
            ComPtr<ITextBox> localTextBox(textBox);
            ComPtr<IUIElement> textBoxAsUIElement;
            THROW_IF_FAILED(localTextBox.As(&textBoxAsUIElement));

            EventRegistrationToken keyDownEventToken;
            THROW_IF_FAILED(textBoxAsUIElement->add_KeyDown(
                Callback<IKeyEventHandler>([actionInvoker, localInlineAction](IInspectable* /*sender*/, IKeyRoutedEventArgs* args) -> HRESULT {
                    return HandleKeydownForInlineAction(args, actionInvoker.Get(), localInlineAction.Get());
                }).Get(),
                &keyDownEventToken));
        }

        THROW_IF_FAILED(xamlGrid.CopyTo(textBoxWithInlineAction));
    }

    void WrapInTouchTarget(_In_ IAdaptiveCardElement* adaptiveCardElement,
                           _In_ IUIElement* elementToWrap,
                           _In_opt_ IAdaptiveActionElement* action,
                           _In_ IAdaptiveRenderContext* renderContext,
                           bool fullWidth,
                           const std::wstring& style,
                           HSTRING altText,
                           bool allowTitleAsTooltip,
                           _COM_Outptr_ IUIElement** finalElement)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        if (ActionHelpers::WarnForInlineShowCard(renderContext, action, L"Inline ShowCard not supported for SelectAction"))
        {
            // Was inline show card, so don't wrap the element and just return
            ComPtr<IUIElement> localElementToWrap(elementToWrap);
            localElementToWrap.CopyTo(finalElement);
            return;
        }

        ComPtr<IButton> button;
        CreateAppropriateButton(action, button);

        ComPtr<IContentControl> buttonAsContentControl;
        THROW_IF_FAILED(button.As(&buttonAsContentControl));
        THROW_IF_FAILED(buttonAsContentControl->put_Content(elementToWrap));

        ComPtr<IAdaptiveSpacingConfig> spacingConfig;
        THROW_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

        UINT32 cardPadding = 0;
        if (fullWidth)
        {
            THROW_IF_FAILED(spacingConfig->get_Padding(&cardPadding));
        }

        ComPtr<IFrameworkElement> buttonAsFrameworkElement;
        THROW_IF_FAILED(button.As(&buttonAsFrameworkElement));

        ComPtr<IControl> buttonAsControl;
        THROW_IF_FAILED(button.As(&buttonAsControl));

        // We want the hit target to equally split the vertical space above and below the current item.
        // However, all we know is the spacing of the current item, which only applies to the spacing above.
        // We don't know what the spacing of the NEXT element will be, so we can't calculate the correct spacing
        // below. For now, we'll simply assume the bottom spacing is the same as the top. NOTE: Only apply spacings
        // (padding, margin) for adaptive card elements to avoid adding spacings to card-level selectAction.
        if (adaptiveCardElement != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::Spacing elementSpacing;
            THROW_IF_FAILED(adaptiveCardElement->get_Spacing(&elementSpacing));
            UINT spacingSize;
            THROW_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig.Get(), elementSpacing, &spacingSize));
            double topBottomPadding = spacingSize / 2.0;

            // For button padding, we apply the cardPadding and topBottomPadding (and then we negate these in the margin)
            THROW_IF_FAILED(buttonAsControl->put_Padding({(double)cardPadding, topBottomPadding, (double)cardPadding, topBottomPadding}));

            double negativeCardMargin = cardPadding * -1.0;
            double negativeTopBottomMargin = topBottomPadding * -1.0;

            THROW_IF_FAILED(buttonAsFrameworkElement->put_Margin(
                {negativeCardMargin, negativeTopBottomMargin, negativeCardMargin, negativeTopBottomMargin}));
        }

        // Style the hit target button
        THROW_IF_FAILED(
            XamlHelpers::SetStyleFromResourceDictionary(renderContext, style.c_str(), buttonAsFrameworkElement.Get()));

        // Determine tooltip, automation name, and automation description
        HString tooltip;
        HString name;
        HString description;
        if (action != nullptr)
        {
            // If we have an action, get it's title and tooltip.
            HString title;
            THROW_IF_FAILED(action->get_Title(title.GetAddressOf()));
            THROW_IF_FAILED(action->get_Tooltip(tooltip.GetAddressOf()));

            if (title.IsValid())
            {
                // If we have a title, use title as the name and tooltip as the description
                name.Set(title.Get());
                description.Set(tooltip.Get());

                if (!tooltip.IsValid() && allowTitleAsTooltip)
                {
                    // If we don't have a tooltip, set the title to the tooltip if we're allowed
                    tooltip.Set(title.Get());
                }
            }
            else
            {
                // If we don't have a title, use the tooltip as the name
                name.Set(tooltip.Get());
            }

            // Disable the select action button if necessary
            boolean isEnabled;
            THROW_IF_FAILED(action->get_IsEnabled(&isEnabled));
            THROW_IF_FAILED(buttonAsControl->put_IsEnabled(isEnabled));
        }
        else if (altText != nullptr)
        {
            // If we don't have an action but we've been passed altText, use that for name and tooltip
            name.Set(altText);
            tooltip.Set(altText);
        }

        ComPtr<IDependencyObject> buttonAsDependencyObject;
        THROW_IF_FAILED(button.As(&buttonAsDependencyObject));
        SetAutomationNameAndDescription(buttonAsDependencyObject.Get(), name.Get(), description.Get());
        SetTooltip(tooltip.Get(), buttonAsDependencyObject.Get());

        if (action != nullptr)
        {
            WireButtonClickToAction(button.Get(), action, renderContext);
        }

        THROW_IF_FAILED(button.CopyTo(finalElement));
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
        THROW_IF_FAILED(buttonBase->add_Click(Callback<IRoutedEventHandler>([strongAction, actionInvoker](IInspectable* /*sender*/, IRoutedEventArgs*
                                                                                                          /*args*/) -> HRESULT {
                                                  THROW_IF_FAILED(actionInvoker->SendActionEvent(strongAction.Get()));
                                                  return S_OK;
                                              }).Get(),
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
            WrapInTouchTarget(adaptiveCardElement, uiElement, selectAction, renderContext, fullWidthTouchTarget, L"Adaptive.SelectAction", nullptr, true, outUiElement);
        }
        else
        {
            if (selectAction != nullptr)
            {
                renderContext->AddWarning(ABI::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode::InteractivityNotSupported,
                                          HStringReference(L"SelectAction present, but Interactivity is not supported").Get());
            }

            ComPtr<IUIElement> localUiElement(uiElement);
            THROW_IF_FAILED(localUiElement.CopyTo(outUiElement));
        }
    }

    HRESULT BuildActions(_In_ IAdaptiveCard* adaptiveCard,
                         _In_ IVector<IAdaptiveActionElement*>* children,
                         _In_ IPanel* bodyPanel,
                         bool insertSeparator,
                         _In_ IAdaptiveRenderContext* renderContext,
                         _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ComPtr<IAdaptiveActionsConfig> actionsConfig;
        RETURN_IF_FAILED(hostConfig->get_Actions(actionsConfig.GetAddressOf()));

        // Create a separator between the body and the actions
        if (insertSeparator)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::Spacing spacing;
            RETURN_IF_FAILED(actionsConfig->get_Spacing(&spacing));

            UINT spacingSize;
            RETURN_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig.Get(), spacing, &spacingSize));

            ABI::Windows::UI::Color color = {0};
            auto separator = XamlHelpers::CreateSeparator(renderContext, spacingSize, 0, color);
            XamlHelpers::AppendXamlElementToPanel(separator.Get(), bodyPanel);
        }

        ComPtr<IUIElement> actionSetControl;
        RETURN_IF_FAILED(BuildActionSetHelper(adaptiveCard, nullptr, children, renderContext, renderArgs, &actionSetControl));

        XamlHelpers::AppendXamlElementToPanel(actionSetControl.Get(), bodyPanel);
        return S_OK;
    }

    HRESULT BuildActionSetHelper(_In_opt_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard* adaptiveCard,
                                 _In_opt_ IAdaptiveActionSet* adaptiveActionSet,
                                 _In_ IVector<IAdaptiveActionElement*>* children,
                                 _In_ IAdaptiveRenderContext* renderContext,
                                 _In_ IAdaptiveRenderArgs* renderArgs,
                                 _Outptr_ IUIElement** actionSetControl)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ComPtr<IAdaptiveActionsConfig> actionsConfig;
        RETURN_IF_FAILED(hostConfig->get_Actions(actionsConfig.GetAddressOf()));

        ABI::AdaptiveCards::Rendering::Uwp::ActionAlignment actionAlignment;
        RETURN_IF_FAILED(actionsConfig->get_ActionAlignment(&actionAlignment));

        ABI::AdaptiveCards::Rendering::Uwp::ActionsOrientation actionsOrientation;
        RETURN_IF_FAILED(actionsConfig->get_ActionsOrientation(&actionsOrientation));

        // Declare the panel that will host the buttons
        ComPtr<IPanel> actionsPanel;
        ComPtr<IVector<ColumnDefinition*>> columnDefinitions;

        if (actionAlignment == ABI::AdaptiveCards::Rendering::Uwp::ActionAlignment::Stretch &&
            actionsOrientation == ABI::AdaptiveCards::Rendering::Uwp::ActionsOrientation::Horizontal)
        {
            // If stretch alignment and orientation is horizontal, we use a grid with equal column widths to achieve
            // stretch behavior. For vertical orientation, we'll still just use a stack panel since the concept of
            // stretching buttons height isn't really valid, especially when the height of cards are typically dynamic.
            ComPtr<IGrid> actionsGrid =
                XamlHelpers::CreateABIClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
            RETURN_IF_FAILED(actionsGrid->get_ColumnDefinitions(&columnDefinitions));
            RETURN_IF_FAILED(actionsGrid.As(&actionsPanel));
        }
        else
        {
            // Create a stack panel for the action buttons
            ComPtr<IStackPanel> actionStackPanel =
                XamlHelpers::CreateABIClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));

            auto uiOrientation = (actionsOrientation == ABI::AdaptiveCards::Rendering::Uwp::ActionsOrientation::Horizontal) ?
                Orientation::Orientation_Horizontal :
                Orientation::Orientation_Vertical;

            RETURN_IF_FAILED(actionStackPanel->put_Orientation(uiOrientation));

            ComPtr<IFrameworkElement> actionsFrameworkElement;
            RETURN_IF_FAILED(actionStackPanel.As(&actionsFrameworkElement));

            switch (actionAlignment)
            {
            case ABI::AdaptiveCards::Rendering::Uwp::ActionAlignment::Center:
                RETURN_IF_FAILED(actionsFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Center));
                break;
            case ABI::AdaptiveCards::Rendering::Uwp::ActionAlignment::Left:
                RETURN_IF_FAILED(actionsFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Left));
                break;
            case ABI::AdaptiveCards::Rendering::Uwp::ActionAlignment::Right:
                RETURN_IF_FAILED(actionsFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Right));
                break;
            case ABI::AdaptiveCards::Rendering::Uwp::ActionAlignment::Stretch:
                RETURN_IF_FAILED(actionsFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Stretch));
                break;
            }

            // Add the action buttons to the stack panel
            RETURN_IF_FAILED(actionStackPanel.As(&actionsPanel));
        }

        Thickness buttonMargin;
        RETURN_IF_FAILED(ActionHelpers::GetButtonMargin(actionsConfig.Get(), buttonMargin));
        if (actionsOrientation == ABI::AdaptiveCards::Rendering::Uwp::ActionsOrientation::Horizontal)
        {
            // Negate the spacing on the sides so the left and right buttons are flush on the side.
            // We do NOT remove the margin from the individual button itself, since that would cause
            // the equal columns stretch behavior to not have equal columns (since the first and last
            // button would be narrower without the same margins as its peers).
            ComPtr<IFrameworkElement> actionsPanelAsFrameworkElement;
            RETURN_IF_FAILED(actionsPanel.As(&actionsPanelAsFrameworkElement));
            RETURN_IF_FAILED(actionsPanelAsFrameworkElement->put_Margin({buttonMargin.Left * -1, 0, buttonMargin.Right * -1, 0}));
        }
        else
        {
            // Negate the spacing on the top and bottom so the first and last buttons don't have extra padding
            ComPtr<IFrameworkElement> actionsPanelAsFrameworkElement;
            RETURN_IF_FAILED(actionsPanel.As(&actionsPanelAsFrameworkElement));
            RETURN_IF_FAILED(actionsPanelAsFrameworkElement->put_Margin({0, buttonMargin.Top * -1, 0, buttonMargin.Bottom * -1}));
        }

        UINT32 maxActions;
        RETURN_IF_FAILED(actionsConfig->get_MaxActions(&maxActions));

        bool allActionsHaveIcons{true};
        IterateOverVector<IAdaptiveActionElement>(children, [&](IAdaptiveActionElement* child) {
            HString iconUrl;
            RETURN_IF_FAILED(child->get_IconUrl(iconUrl.GetAddressOf()));

            if (WindowsIsStringEmpty(iconUrl.Get()))
            {
                allActionsHaveIcons = false;
            }
            return S_OK;
        });

        UINT currentAction = 0;

        RETURN_IF_FAILED(renderArgs->put_AllowAboveTitleIconPlacement(allActionsHaveIcons));

        std::shared_ptr<std::vector<ComPtr<IUIElement>>> allShowCards = std::make_shared<std::vector<ComPtr<IUIElement>>>();
        ComPtr<IStackPanel> showCardsStackPanel =
            XamlHelpers::CreateABIClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        ComPtr<IGridStatics> gridStatics;
        RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));
        IterateOverVector<IAdaptiveActionElement>(children, [&](IAdaptiveActionElement* child) {
            if (currentAction < maxActions)
            {
                // Render each action using the registered renderer
                ComPtr<IAdaptiveActionElement> action(child);
                ComPtr<IAdaptiveActionRendererRegistration> actionRegistration;
                RETURN_IF_FAILED(renderContext->get_ActionRenderers(&actionRegistration));

                ComPtr<IAdaptiveActionRenderer> renderer;
                while (!renderer)
                {
                    HString actionTypeString;
                    RETURN_IF_FAILED(action->get_ActionTypeString(actionTypeString.GetAddressOf()));
                    RETURN_IF_FAILED(actionRegistration->Get(actionTypeString.Get(), &renderer));
                    if (!renderer)
                    {
                        ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType actionFallbackType;
                        action->get_FallbackType(&actionFallbackType);
                        switch (actionFallbackType)
                        {
                        case ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType::Drop:
                        {
                            RETURN_IF_FAILED(XamlHelpers::WarnForFallbackDrop(renderContext, actionTypeString.Get()));
                            return S_OK;
                        }

                        case ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType::Content:
                        {
                            ComPtr<IAdaptiveActionElement> actionFallback;
                            RETURN_IF_FAILED(action->get_FallbackContent(&actionFallback));

                            HString fallbackTypeString;
                            RETURN_IF_FAILED(actionFallback->get_ActionTypeString(fallbackTypeString.GetAddressOf()));
                            RETURN_IF_FAILED(XamlHelpers::WarnForFallbackContentElement(renderContext,
                                                                                        actionTypeString.Get(),
                                                                                        fallbackTypeString.Get()));

                            action = actionFallback;
                            break;
                        }

                        case ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType::None:
                        default:
                            return E_FAIL;
                        }
                    }
                }

                ComPtr<IUIElement> actionControl;
                RETURN_IF_FAILED(renderer->Render(action.Get(), renderContext, renderArgs, &actionControl));

                XamlHelpers::AppendXamlElementToPanel(actionControl.Get(), actionsPanel.Get());

                ABI::AdaptiveCards::ObjectModel::Uwp::ActionType actionType;
                RETURN_IF_FAILED(action->get_ActionType(&actionType));

                // Build inline show cards if needed
                if (actionType == ABI::AdaptiveCards::ObjectModel::Uwp::ActionType_ShowCard)
                {
                    ComPtr<IUIElement> uiShowCard;

                    ComPtr<IAdaptiveShowCardActionConfig> showCardActionConfig;
                    RETURN_IF_FAILED(actionsConfig->get_ShowCard(&showCardActionConfig));

                    ABI::AdaptiveCards::Rendering::Uwp::ActionMode showCardActionMode;
                    RETURN_IF_FAILED(showCardActionConfig->get_ActionMode(&showCardActionMode));

                    if (showCardActionMode == ABI::AdaptiveCards::Rendering::Uwp::ActionMode::Inline)
                    {
                        ComPtr<IAdaptiveShowCardAction> showCardAction;
                        RETURN_IF_FAILED(action.As(&showCardAction));

                        ComPtr<IAdaptiveCard> showCard;
                        RETURN_IF_FAILED(showCardAction->get_Card(&showCard));

                        RETURN_IF_FAILED(AdaptiveShowCardActionRenderer::BuildShowCard(
                            showCard.Get(), renderContext, renderArgs, (adaptiveActionSet == nullptr), uiShowCard.GetAddressOf()));

                        ComPtr<IPanel> showCardsPanel;
                        RETURN_IF_FAILED(showCardsStackPanel.As(&showCardsPanel));
                        XamlHelpers::AppendXamlElementToPanel(uiShowCard.Get(), showCardsPanel.Get());

                        if (adaptiveActionSet)
                        {
                            RETURN_IF_FAILED(
                                renderContext->AddInlineShowCard(adaptiveActionSet, showCardAction.Get(), uiShowCard.Get(), renderArgs));
                        }
                        else
                        {
                            ComPtr<AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext> contextImpl =
                                PeekInnards<AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext>(renderContext);

                            RETURN_IF_FAILED(
                                contextImpl->AddInlineShowCard(adaptiveCard, showCardAction.Get(), uiShowCard.Get(), renderArgs));
                        }
                    }
                }

                if (columnDefinitions != nullptr)
                {
                    // If using the equal width columns, we'll add a column and assign the column
                    ComPtr<IColumnDefinition> columnDefinition = XamlHelpers::CreateABIClass<IColumnDefinition>(
                        HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
                    RETURN_IF_FAILED(columnDefinition->put_Width({1.0, GridUnitType::GridUnitType_Star}));
                    RETURN_IF_FAILED(columnDefinitions->Append(columnDefinition.Get()));

                    ComPtr<IFrameworkElement> actionFrameworkElement;
                    THROW_IF_FAILED(actionControl.As(&actionFrameworkElement));
                    THROW_IF_FAILED(gridStatics->SetColumn(actionFrameworkElement.Get(), currentAction));
                }
            }
            else
            {
                renderContext->AddWarning(ABI::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode::MaxActionsExceeded,
                                          HStringReference(L"Some actions were not rendered due to exceeding the maximum number of actions allowed")
                                              .Get());
            }
            currentAction++;
            return S_OK;
        });

        // Reset icon placement value
        RETURN_IF_FAILED(renderArgs->put_AllowAboveTitleIconPlacement(false));

        ComPtr<IFrameworkElement> actionsPanelAsFrameworkElement;
        RETURN_IF_FAILED(actionsPanel.As(&actionsPanelAsFrameworkElement));
        RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                     L"Adaptive.Actions",
                                                                     actionsPanelAsFrameworkElement.Get()));

        ComPtr<IStackPanel> actionSet =
            XamlHelpers::CreateABIClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        ComPtr<IPanel> actionSetAsPanel;
        actionSet.As(&actionSetAsPanel);

        // Add buttons and show cards to panel
        XamlHelpers::AppendXamlElementToPanel(actionsPanel.Get(), actionSetAsPanel.Get());
        XamlHelpers::AppendXamlElementToPanel(showCardsStackPanel.Get(), actionSetAsPanel.Get());

        return actionSetAsPanel.CopyTo(actionSetControl);
    }

    void CreateAppropriateButton(ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* action, ComPtr<IButton>& button)
    {
        if (action != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::ActionType actionType;
            THROW_IF_FAILED(action->get_ActionType(&actionType));

            // construct an appropriate button for the action type
            if (actionType == ABI::AdaptiveCards::ObjectModel::Uwp::ActionType_OpenUrl)
            {
                // OpenUrl buttons should appear as links for accessibility purposes, so we use our custom LinkButton.
                auto linkButton = winrt::make<LinkButton>();
                button = linkButton.as<IButton>().detach();
            }
        }

        if (!button)
        {
            // Either no action, non-OpenUrl action, or instantiating LinkButton failed. Use standard button.
            button = XamlHelpers::CreateABIClass<IButton>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Button));
        }
    }
}
