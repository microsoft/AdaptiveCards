// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveToggleInputRenderer.h"

namespace Xaml
{
    using namespace winrt::Windows::UI::Xaml;
}

namespace XamlHelpers
{
    using namespace AdaptiveCards::Rendering::Uwp::XamlHelpers;
}

using namespace winrt::AdaptiveCards::ObjectModel::Uwp;
using namespace winrt::AdaptiveCards::Rendering::Uwp;

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    Xaml::UIElement AdaptiveToggleInputRenderer::Render(IAdaptiveCardElement cardElement,
                                                        AdaptiveRenderContext renderContext,
                                                        AdaptiveRenderArgs renderArgs)
    {
        if (!renderContext.HostConfig().SupportsInteractivity())
        {
            renderContext.AddWarning(winrt::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode::InteractivityNotSupported,
                                     L"Toggle Input was stripped from card because interactivity is not supported");

            return nullptr;
        }

        AdaptiveToggleInput toggleInput = cardElement.as<AdaptiveToggleInput>();

        Xaml::Controls::CheckBox checkBox{};
        XamlHelpers::SetContent(checkBox, toggleInput.Title(), toggleInput.Wrap());

        checkBox.IsChecked(toggleInput.ValueOn() == toggleInput.Value());
        checkBox.VerticalAlignment(Xaml::VerticalAlignment::Top);

        // Add Tap handler that sets the event as handled so that it doesn't propagate to the parent containers.
        checkBox.Tapped([](IInspectable const& /* sender */, Xaml::Input::TappedRoutedEventArgs const& args)
                        { return args.Handled(true); });

        XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Toggle", checkBox);
        Xaml::UIElement inputLayout = XamlHelpers::HandleInputLayoutAndValidation(toggleInput, checkBox, false, renderContext);

        winrt::com_ptr<::AdaptiveCards::Rendering::Uwp::ToggleInputValue> inputValue;
        THROW_IF_FAILED(Microsoft::WRL::MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::ToggleInputValue>(
            inputValue.put(),
            toggleInput.as<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveToggleInput>().get(),
            checkBox.as<ABI::Windows::UI::Xaml::Controls::ICheckBox>().get(),
            nullptr));

        renderContext.AddInputValue(inputValue.as<IAdaptiveInputValue>(), renderArgs);

        return inputLayout;
    }
}
