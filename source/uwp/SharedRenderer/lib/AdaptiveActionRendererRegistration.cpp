// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveActionRendererRegistration.h"
#include "AdaptiveActionRendererRegistration.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    void AdaptiveActionRendererRegistration::Set(winrt::hstring const& type, winrt::IAdaptiveActionRenderer const& renderer)
    {
        m_registration[type] = renderer;
    }

    winrt::IAdaptiveActionRenderer AdaptiveActionRendererRegistration::Get(winrt::hstring const& type)
    {
        if (const auto found = m_registration.find(type); found != m_registration.end())
        {
            return found->second;
        }
        else
        {
            return nullptr;
        }
    }

    void AdaptiveActionRendererRegistration::Remove(winrt::hstring const& type) { m_registration.erase(type); }
}
