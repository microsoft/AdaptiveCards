// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Uwp::ActionHelpers
{
    HRESULT BuildAction(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* adaptiveActionElement,
                        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                        _Outptr_ ABI::Windows::UI::Xaml::IUIElement** actionControl);

    HRESULT GetButtonMargin(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionsConfig* actionsConfig,
                            ABI::Windows::UI::Xaml::Thickness& buttonMargin) noexcept;

    void ArrangeButtonContent(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* action,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionsConfig* actionsConfig,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                              ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle containerStyle,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                              bool allActionsHaveIcons,
                              _In_ ABI::Windows::UI::Xaml::Controls::IButton* button);

    HRESULT SetMatchingHeight(_In_ ABI::Windows::UI::Xaml::IFrameworkElement* elementToChange,
                              _In_ ABI::Windows::UI::Xaml::IFrameworkElement* elementToMatch);

    HRESULT HandleActionStyling(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* adaptiveActionElement,
                                _In_ ABI::Windows::UI::Xaml::IFrameworkElement* buttonFrameworkElement,
                                _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext);

    bool WarnForInlineShowCard(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                               _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* action,
                               const std::wstring& warning);

    void HandleInlineAction(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                            _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                            _In_ ABI::Windows::UI::Xaml::Controls::ITextBox* textBox,
                            _In_ ABI::Windows::UI::Xaml::IUIElement* textBoxParentContainer,
                            _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* inlineAction,
                            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** textBoxWithInlineAction);

    void WireButtonClickToAction(_In_ ABI::Windows::UI::Xaml::Controls::IButton* button,
                                 _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* action,
                                 _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext);

    void WrapInTouchTarget(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement* adaptiveCardElement,
                           _In_ ABI::Windows::UI::Xaml::IUIElement* elementToWrap,
                           _In_opt_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* action,
                           _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                           bool fullWidth,
                           const std::wstring& style,
                           HSTRING altText,
                           bool allowTitleAsTooltip,
                           _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** finalElement);

    void HandleSelectAction(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement* adaptiveCardElement,
                            _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* selectAction,
                            _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                            _In_ ABI::Windows::UI::Xaml::IUIElement* uiElement,
                            bool supportsInteractivity,
                            bool fullWidthTouchTarget,
                            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** outUiElement);

    HRESULT BuildActions(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard* adaptiveCard,
                         _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement*>* children,
                         _In_ ABI::Windows::UI::Xaml::Controls::IPanel* bodyPanel,
                         bool insertSeparator,
                         _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                         _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs);

    HRESULT BuildActionSetHelper(_In_opt_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard* adaptiveCard,
                                 _In_opt_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionSet* adaptiveActionSet,
                                 _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement*>* children,
                                 _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                 _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                                 _Outptr_ ABI::Windows::UI::Xaml::IUIElement** actionSetControl);

    void CreateAppropriateButton(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* action,
                                 Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::IButton>& button);
}
