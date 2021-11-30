// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveToggleInputRenderer.h"
#include "AdaptiveToggleInputRenderer.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    rtxaml::UIElement AdaptiveToggleInputRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                          rtrender::AdaptiveRenderContext const& renderContext,
                                                          rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto hostConfig = renderContext.HostConfig();
            if (!::AdaptiveCards::Rendering::Uwp::XamlHelpers::SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(rtom::WarningStatusCode::InteractivityNotSupported,
                                         L"Toggle Input was stripped from card because interactivity is not supported");
                return nullptr;
            }

            auto adaptiveToggleInput = cardElement.as<rtom::AdaptiveToggleInput>();

            rtxaml::Controls::CheckBox checkBox{};

            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetContent(checkBox,
                                                                        adaptiveToggleInput.Title(),
                                                                        adaptiveToggleInput.Wrap());

            checkBox.IsChecked(adaptiveToggleInput.ValueOn() == adaptiveToggleInput.Value());
            checkBox.Tapped([](winrt::Windows::Foundation::IInspectable const& /* sender */,
                               rtxaml::Input::TappedRoutedEventArgs const& args) { return args.Handled(true); });

            checkBox.VerticalAlignment(rtxaml::VerticalAlignment::Top);
            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Toggle", checkBox);

            rtxaml::UIElement inputLayout{nullptr};
            std::tie(inputLayout, std::ignore) =
                ::AdaptiveCards::Rendering::Uwp::XamlHelpers::HandleInputLayoutAndValidation(adaptiveToggleInput, checkBox, false, renderContext, false);

            // TODO: come back here, not sure if this is right
            auto input = winrt::make_self<rtrender::ToggleInputValue>(adaptiveToggleInput, checkBox, nullptr);
            renderContext.AddInputValue(*input, renderArgs);
            return inputLayout;
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
