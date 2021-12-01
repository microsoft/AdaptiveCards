// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveActionSetRenderer.h"

#include "ActionHelpers.h"
#include "AdaptiveRenderArgs.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveActionSetRenderer::RuntimeClassInitialize() noexcept { return S_OK; }

    HRESULT AdaptiveActionSetRenderer::Render(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                              _In_ IAdaptiveRenderContext* renderContext,
                                              _In_ IAdaptiveRenderArgs* renderArgs,
                                              _COM_Outptr_ IUIElement** actionSetControl) noexcept
    try
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        if (!XamlHelpers::SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
                ABI::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"ActionSet was stripped from card because interactivity is not supported").Get());
            return S_OK;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveActionSet> adaptiveActionSet;
        RETURN_IF_FAILED(cardElement.As(&adaptiveActionSet));

        ComPtr<IVector<IAdaptiveActionElement*>> actions;
        RETURN_IF_FAILED(adaptiveActionSet->get_Actions(&actions));

        return ActionHelpers::BuildActionSetHelper(nullptr, adaptiveActionSet.Get(), actions.Get(), renderContext, renderArgs, actionSetControl);
    }
    CATCH_RETURN;
}
