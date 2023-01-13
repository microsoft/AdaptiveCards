// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRenderArgs.h"
#include "AdaptiveRenderArgs.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    // This constructor is kept so all elements keep working as expected
    AdaptiveRenderArgs::AdaptiveRenderArgs(winrt::ContainerStyle const& containerStyle,
                                           winrt::IInspectable const& parentElement,
                                           winrt::AdaptiveRenderArgs const& renderArgs) :
        ContainerStyle{containerStyle},
        ParentElement{parentElement}
    {
        if (renderArgs)
        {
            AncestorHasFallback = renderArgs.AncestorHasFallback();
            ParentCard = renderArgs.ParentCard();
        }
    }

    AdaptiveRenderArgs::AdaptiveRenderArgs(winrt::ContainerStyle const& containerStyle,
                                           winrt::IInspectable const& parentElement,
                                           winrt::AdaptiveCard const& parentCard,
                                           winrt::AdaptiveRenderArgs const& renderArgs) :
        ContainerStyle{containerStyle},
        ParentElement{parentElement}, ParentCard{parentCard}
    {
        if (renderArgs)
        {
            AncestorHasFallback = renderArgs.AncestorHasFallback();
        }
    }
}
