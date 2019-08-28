// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveNamespace::ActionHelpers
{
    HRESULT BuildAction(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* adaptiveActionElement,
                        _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                        _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                        _Outptr_ ABI::Windows::UI::Xaml::IUIElement** actionControl);

    HRESULT GetButtonMargin(_In_ ABI::AdaptiveNamespace::IAdaptiveActionsConfig* actionsConfig,
                            ABI::Windows::UI::Xaml::Thickness& buttonMargin) noexcept;

    void ArrangeButtonContent(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action,
                              _In_ ABI::AdaptiveNamespace::IAdaptiveActionsConfig* actionsConfig,
                              _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                              ABI::AdaptiveNamespace::ContainerStyle containerStyle,
                              _In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                              bool allActionsHaveIcons,
                              _In_ ABI::Windows::UI::Xaml::Controls::IButton* button);

    HRESULT SetMatchingHeight(_In_ ABI::Windows::UI::Xaml::IFrameworkElement* elementToChange,
                              _In_ ABI::Windows::UI::Xaml::IFrameworkElement* elementToMatch);

    HRESULT HandleActionStyling(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* adaptiveActionElement,
                                _In_ ABI::Windows::UI::Xaml::IFrameworkElement* buttonFrameworkElement,
                                _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext);

    bool WarnForInlineShowCard(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                               _In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action,
                               const std::wstring& warning);

    void HandleInlineAction(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                            _In_ ABI::Windows::UI::Xaml::Controls::ITextBox* textBox,
                            _In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* inlineAction,
                            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** textBoxWithInlineAction);
}
