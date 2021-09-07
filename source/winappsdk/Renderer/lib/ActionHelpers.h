// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::WinUI3::ActionHelpers
{
    namespace rtrender = winrt::AdaptiveCards::Rendering::WinUI3;
    namespace rtom = winrt::AdaptiveCards::ObjectModel::WinUI3;
    namespace rtxaml = winrt::Windows::UI::Xaml;

    HRESULT BuildAction(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* adaptiveActionElement,
                        _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                        _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                        bool isOverflowActionButton,
                        _Outptr_ ABI::Windows::UI::Xaml::IUIElement** actionControl);

    winrt::Windows::UI::Xaml::Thickness GetButtonMargin(winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveActionsConfig const& actionsConfig);

    void SetTooltip(winrt::hstring const& toolTipText, winrt::Windows::UI::Xaml::DependencyObject const& tooltipTarget);

    void SetAutomationNameAndDescription(winrt::Windows::UI::Xaml::DependencyObject const& dependencyObject,
                                         winrt::hstring const& name,
                                         winrt::hstring const& description);

    void ArrangeButtonContent(winrt::hstring const& actionTitle,
                              winrt::hstring const& actionIconUrl,
                              winrt::hstring const& actionTooltip,
                              winrt::hstring const& actionAccessibilityText,
                              rtrender::AdaptiveActionsConfig const& actionsConfig,
                              rtrender::AdaptiveRenderContext const& renderContext,
                              rtom::ContainerStyle containerStyle,
                              rtrender::AdaptiveHostConfig const& hostConfig,
                              bool allActionsHaveIcons,
                              rtxaml::Controls::Button const& button);

    void ArrangeButtonContent(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* action,
                              _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveActionsConfig* actionsConfig,
                              _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                              ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle containerStyle,
                              _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* hostConfig,
                              bool allActionsHaveIcons,
                              _In_ ABI::Windows::UI::Xaml::Controls::IButton* button);

    HRESULT SetMatchingHeight(_In_ ABI::Windows::UI::Xaml::IFrameworkElement* elementToChange,
                              _In_ ABI::Windows::UI::Xaml::IFrameworkElement* elementToMatch);

    void SetMatchingHeight(winrt::Windows::UI::Xaml::FrameworkElement const& elementToChange,
                           winrt::Windows::UI::Xaml::FrameworkElement const& elementToMatch);

    HRESULT HandleActionStyling(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* adaptiveActionElement,
                                _In_ ABI::Windows::UI::Xaml::IFrameworkElement* buttonFrameworkElement,
                                bool isOverflowActionButton,
                                _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext);

    bool WarnForInlineShowCard(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                               _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* action,
                               const std::wstring& warning);

    void HandleKeydownForInlineAction(winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& args,
                                      winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveActionInvoker const& actionInvoker,
                                      winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement const& inlineAction);

    void HandleInlineAction(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                            _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                            _In_ ABI::Windows::UI::Xaml::Controls::ITextBox* textBox,
                            _In_ ABI::Windows::UI::Xaml::IUIElement* textBoxParentContainer,
                            _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* inlineAction,
                            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** textBoxWithInlineAction);

    void WireButtonClickToAction(_In_ ABI::Windows::UI::Xaml::Controls::IButton* button,
                                 _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* action,
                                 _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext);

    void WrapInTouchTarget(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement* adaptiveCardElement,
                           _In_ ABI::Windows::UI::Xaml::IUIElement* elementToWrap,
                           _In_opt_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* action,
                           _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                           bool fullWidth,
                           const std::wstring& style,
                           HSTRING altText,
                           bool allowTitleAsTooltip,
                           _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** finalElement);

    void HandleSelectAction(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement* adaptiveCardElement,
                            _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* selectAction,
                            _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                            _In_ ABI::Windows::UI::Xaml::IUIElement* uiElement,
                            bool supportsInteractivity,
                            bool fullWidthTouchTarget,
                            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** outUiElement);

    HRESULT BuildActions(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* adaptiveCard,
                         _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement*>* children,
                         _In_ ABI::Windows::UI::Xaml::Controls::IPanel* bodyPanel,
                         bool insertSeparator,
                         _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                         _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs);

    HRESULT BuildActionSetHelper(
        _In_opt_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* adaptiveCard,
        _In_opt_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionSet* adaptiveActionSet,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement*>* children,
        _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
        _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
        _Outptr_ ABI::Windows::UI::Xaml::IUIElement** actionSetControl);

    void BuildActions(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveCard const& adaptiveCard,
                      winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement> const& children,
                      winrt::Windows::UI::Xaml::Controls::Panel const& bodyPanel,
                      bool insertSeparator,
                      winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                      winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);

    void BuildInlineShowCard(rtom::AdaptiveCard const& adaptiveCard,
                             rtom::AdaptiveActionSet const& adaptiveActionSet,
                             rtom::IAdaptiveActionElement const& action,
                             rtxaml::Controls::Panel const& showCardsPanel,
                             rtxaml::UIElement actionButton,
                             rtxaml::UIElement actionOverflowItem,
                             uint32_t buttonIndex,
                             rtrender::AdaptiveRenderContext const& renderContext,
                             rtrender::AdaptiveRenderArgs const& renderArgs);

    rtxaml::UIElement BuildActionSetHelper(
        rtom::AdaptiveCard const& adaptiveCard,
        rtom::AdaptiveActionSet const& adaptiveActionSet,
        winrt::Windows::Foundation::Collections::IVector<rtom::IAdaptiveActionElement> const& children,
        rtrender::AdaptiveRenderContext const& renderContext,
        rtrender::AdaptiveRenderArgs const& renderArgs);

    void CreateAppropriateButton(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* action,
                                 Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::IButton>& button);
    rtxaml::Controls::Button CreateAppropriateButton(rtom::IAdaptiveActionElement const& action);
}
