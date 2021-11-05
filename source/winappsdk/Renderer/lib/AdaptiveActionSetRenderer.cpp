// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveActionSetRenderer.h"
#include "AdaptiveActionSetRenderer.g.cpp"

#include "ActionHelpers.h"
#include "AdaptiveRenderArgs.h"

using namespace winrt;
using namespace winrt::AdaptiveCards::Rendering::WinUI3;
using namespace winrt::AdaptiveCards::ObjectModel::WinUI3;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Controls::Primitives;

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    winrt::Windows::UI::Xaml::UIElement AdaptiveActionSetRenderer::Render(ObjectModel::WinUI3::IAdaptiveCardElement const& cardElement,
                                               WinUI3::AdaptiveRenderContext const& renderContext,
                                               WinUI3::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto hostConfig = renderContext.HostConfig();

            if (!::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(ObjectModel::WinUI3::WarningStatusCode::InteractivityNotSupported,
                                         L"ActionSet was stripped from card because interactivity is not supported");

                return nullptr;
            }
            else
            {
                auto adaptiveActionSet = cardElement.as<ObjectModel::WinUI3::AdaptiveActionSet>();
                auto actions = adaptiveActionSet.Actions();

                return ::AdaptiveCards::Rendering::WinUI3::ActionHelpers::BuildActionSetHelper(
                    nullptr, adaptiveActionSet, actions, renderContext, renderArgs);
            }
        }
        catch(winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
