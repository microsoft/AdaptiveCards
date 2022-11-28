// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveToggleInputRenderer.h"
#include "AdaptiveToggleInputRenderer.g.cpp"
#include "InputValue.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    winrt::xaml::UIElement AdaptiveToggleInputRenderer::Render(winrt::IAdaptiveCardElement const& cardElement,
                                                         winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                                         winrt::render_xaml::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto hostConfig = renderContext.HostConfig();
            if (!XamlHelpers::SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(winrt::WarningStatusCode::InteractivityNotSupported,
                                         L"Toggle Input was stripped from card because interactivity is not supported");
                return nullptr;
            }

            auto adaptiveToggleInput = cardElement.as<winrt::AdaptiveToggleInput>();

            winrt::xaml_controls::CheckBox checkBox{};

            XamlHelpers::SetContent(checkBox, adaptiveToggleInput.Title(), adaptiveToggleInput.Wrap());

            checkBox.IsChecked(adaptiveToggleInput.ValueOn() == adaptiveToggleInput.Value());
            checkBox.Tapped([](winrt::IInspectable const& /* sender */, winrt::xaml_input::TappedRoutedEventArgs const& args)
                            { return args.Handled(true); });

            checkBox.VerticalAlignment(winrt::xaml::VerticalAlignment::Top);
            XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Toggle", checkBox);

            winrt::xaml::UIElement inputLayout{nullptr};
            std::tie(inputLayout, std::ignore) =
                XamlHelpers::HandleInputLayoutAndValidation(adaptiveToggleInput, checkBox, false, renderContext, false);

            auto input = winrt::make<winrt::render_xaml::ToggleInputValue>(adaptiveToggleInput, checkBox, nullptr);
            renderContext.AddInputValue(input, renderArgs);
            return inputLayout;
        }
        catch (winrt::hresult_error const& ex)
        {
            XamlHelpers::ErrForRenderFailedForElement(renderContext, cardElement.ElementTypeString(), ex.message());
            return nullptr;
        }
    }
}
