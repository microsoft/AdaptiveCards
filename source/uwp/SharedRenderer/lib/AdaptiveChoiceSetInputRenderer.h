// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveChoiceSetInputRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveChoiceSetInputRenderer : AdaptiveChoiceSetInputRendererT<AdaptiveChoiceSetInputRenderer>
    {
    public:
        AdaptiveChoiceSetInputRenderer() = default;

        winrt::xaml::UIElement Render(winrt::IAdaptiveCardElement const& cardElement,
                                      winrt::AdaptiveRenderContext const& renderContext,
                                      winrt::AdaptiveRenderArgs const& renderArgs);

    private:
        static std::vector<std::string> GetChoiceSetValueVector(winrt::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput);

        static bool IsChoiceSelected(std::vector<std::string> selectedValues, winrt::AdaptiveChoiceInput const& choice);

        winrt::xaml::UIElement BuildExpandedChoiceSetInput(winrt::AdaptiveRenderContext const& renderContext,
                                                           winrt::AdaptiveRenderArgs const& renderArgs,
                                                           winrt::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput,
                                                           bool isMultiSelect);

        winrt::xaml::UIElement BuildCompactChoiceSetInput(winrt::AdaptiveRenderContext const& renderContext,
                                                          winrt::AdaptiveRenderArgs const& renderArgs,
                                                          winrt::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput);

        winrt::xaml::UIElement BuildFilteredChoiceSetInput(winrt::AdaptiveRenderContext const& renderContext,
                                                           winrt::AdaptiveRenderArgs const& renderArgs,
                                                           winrt::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput);
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveChoiceSetInputRenderer
        : AdaptiveChoiceSetInputRendererT<AdaptiveChoiceSetInputRenderer, implementation::AdaptiveChoiceSetInputRenderer>
    {
    };
}
