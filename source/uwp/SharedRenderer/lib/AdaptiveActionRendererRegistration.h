// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveActionRendererRegistration.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveActionRendererRegistration : AdaptiveActionRendererRegistrationT<AdaptiveActionRendererRegistration>
    {
        using RegistrationMap =
            std::unordered_map<winrt::hstring, winrt::render_xaml::IAdaptiveActionRenderer, ::AdaptiveCards::CaseInsensitiveHash, ::AdaptiveCards::CaseInsensitiveEqualTo>;

        AdaptiveActionRendererRegistration() = default;

        winrt::render_xaml::IAdaptiveActionRenderer Get(winrt::hstring const& type);
        void Set(winrt::hstring const& type, winrt::render_xaml::IAdaptiveActionRenderer const& renderer);
        void Remove(winrt::hstring const& type);

        RegistrationMap m_registration;
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveActionRendererRegistration
        : AdaptiveActionRendererRegistrationT<AdaptiveActionRendererRegistration, implementation::AdaptiveActionRendererRegistration>
    {
    };
}
