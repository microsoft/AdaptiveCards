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


            // TODO: I could convert it to structural binding but then compiler will generate unsued variable warning
            // TODO: I could fix it with [[maybe_unused]], but then we aren't sure which variable exactly is unused
            // TODO: I will leave std::tie here, it makes more sense to me.
            rtxaml::UIElement inputLayout{nullptr};
            std::tie(inputLayout, std::ignore) = ::AdaptiveCards::Rendering::Uwp::XamlHelpers::HandleInputLayoutAndValidation(
                adaptiveToggleInput, checkBox, false, renderContext, false);

            // TODO: come back here, not sure if this is right
            // TODO: should it be make self? should I put all input values under ::implementation namespace? Help needed here
            auto input = winrt::make<rtrender::ToggleInputValue>(adaptiveToggleInput, checkBox, nullptr);
            renderContext.AddInputValue(input, renderArgs);
            return inputLayout;
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
