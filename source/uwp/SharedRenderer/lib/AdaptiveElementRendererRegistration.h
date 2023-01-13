// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Util.h"
#include "AdaptiveElementREndererRegistration.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveElementRendererRegistration : AdaptiveElementRendererRegistrationT<AdaptiveElementRendererRegistration>
    {
        using RegistrationMap =
            std::unordered_map<hstring, winrt::IAdaptiveElementRenderer, ::AdaptiveCards::CaseInsensitiveHash, ::AdaptiveCards::CaseInsensitiveEqualTo>;

        AdaptiveElementRendererRegistration() = default;

        void Set(hstring const& type, winrt::IAdaptiveElementRenderer const& renderer)
        {
            m_registration[type] = renderer;
        }

        winrt::IAdaptiveElementRenderer Get(hstring const& type)
        {
            auto it = m_registration.find(type);
            if (it != m_registration.end())
            {
                return it->second;
            }
            else
            {
                return nullptr;
            }
        }

        void Remove(hstring const& type) { m_registration.erase(type); }

        RegistrationMap m_registration;
    };
}
