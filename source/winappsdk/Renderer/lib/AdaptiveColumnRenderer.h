// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Column.h"
#include "AdaptiveColumnRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveColumnRenderer : AdaptiveColumnRendererT<AdaptiveColumnRenderer>
       /* : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveElementRenderer>*/
    {
        // AdaptiveRuntime(AdaptiveColumnRenderer);

        AdaptiveColumnRenderer() = default;

        /* IFACEMETHODIMP Render(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement* cardElement,
                               _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                               _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                               _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept override;*/

        rtxaml::UIElement Render(rtom::IAdaptiveCardElement const& cardElement,
                                 rtrender::AdaptiveRenderContext const& renderContext,
                                 rtrender::AdaptiveRenderArgs const& renderArgs);
    };

    // ActivatableClass(AdaptiveColumnRenderer);
}

namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveColumnRenderer : AdaptiveColumnRendererT<AdaptiveColumnRenderer, implementation::AdaptiveColumnRenderer>
    {
    };
}
