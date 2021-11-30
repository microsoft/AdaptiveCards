// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveActionRendererRegistration.h"
#include "AdaptiveActionRendererRegistration.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    void AdaptiveActionRendererRegistration::Set(hstring const& type, Uwp::IAdaptiveActionRenderer const& renderer)
    {
        m_registration[type] = renderer;
    }

    Uwp::IAdaptiveActionRenderer AdaptiveActionRendererRegistration::Get(hstring const& type)
    {
        auto found = m_registration.find(type);
        if (found != m_registration.end())
        {
            return found->second;
        }
        else
        {
            return nullptr;
        }
    }

    void AdaptiveActionRendererRegistration::Remove(hstring const& type) { m_registration.erase(type); }
}
