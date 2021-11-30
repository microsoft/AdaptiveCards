// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRenderArgs.h"
#include "AdaptiveRenderArgs.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    // This constructor is kept so all elements keep working as expected
    AdaptiveRenderArgs::AdaptiveRenderArgs(ObjectModel::Uwp::ContainerStyle const& containerStyle,
                                           winrt::Windows::Foundation::IInspectable const& parentElement,
                                           Uwp::AdaptiveRenderArgs const& renderArgs) :
        ContainerStyle{containerStyle},
        ParentElement{parentElement}
    {
        if (renderArgs)
        {
            AncestorHasFallback = renderArgs.AncestorHasFallback();
            ParentCard = renderArgs.ParentCard();
        }
    }

    AdaptiveRenderArgs::AdaptiveRenderArgs(ObjectModel::Uwp::ContainerStyle const& containerStyle,
                                           winrt::Windows::Foundation::IInspectable const& parentElement,
                                           ObjectModel::Uwp::AdaptiveCard const& parentCard,
                                           Uwp::AdaptiveRenderArgs const& renderArgs) :
        ContainerStyle{containerStyle},
        ParentElement{parentElement}, ParentCard{parentCard}
    {
        if (renderArgs)
        {
            AncestorHasFallback = renderArgs.AncestorHasFallback();
        }
    }
}
