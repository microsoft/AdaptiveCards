// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveImageRenderer.g.h"
#include "Image.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveImageRenderer : AdaptiveImageRendererT<AdaptiveImageRenderer>
    {
    public:
        AdaptiveImageRenderer(){};
        AdaptiveImageRenderer(winrt::com_ptr<::AdaptiveCards::Rendering::Xaml_Rendering::XamlBuilder> xamlBuilder);

        winrt::UIElement Render(winrt::IAdaptiveCardElement const& cardElement,
                                winrt::AdaptiveRenderContext const& renderContext,
                                winrt::AdaptiveRenderArgs const& renderArgs);

    private:
        winrt::com_ptr<::AdaptiveCards::Rendering::Xaml_Rendering::XamlBuilder> m_xamlBuilder;
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveImageRenderer : AdaptiveImageRendererT<AdaptiveImageRenderer, implementation::AdaptiveImageRenderer>
    {
    };
}
