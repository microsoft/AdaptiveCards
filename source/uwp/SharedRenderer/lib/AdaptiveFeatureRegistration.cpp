// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveFeatureRegistration.h"
#include "AdaptiveFeatureRegistration.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveFeatureRegistration::AdaptiveFeatureRegistration(std::shared_ptr<::AdaptiveCards::FeatureRegistration> sharedParserRegistration) :
        m_sharedFeatureRegistration(sharedParserRegistration)
    {
    }

    void AdaptiveFeatureRegistration::Set(winrt::hstring const& name, winrt::hstring const& version)
    {
        m_sharedFeatureRegistration->AddFeature(HStringToUTF8(name), HStringToUTF8(version));
    }

    winrt::hstring AdaptiveFeatureRegistration::Get(winrt::hstring const& name)
    {
        return UTF8ToHString(m_sharedFeatureRegistration->GetFeatureVersion(HStringToUTF8(name)));
    }

    void AdaptiveFeatureRegistration::Remove(winrt::hstring const& name)
    {
        m_sharedFeatureRegistration->RemoveFeature(HStringToUTF8(name));
    }
}
