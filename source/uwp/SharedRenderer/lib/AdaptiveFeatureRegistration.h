// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveFeatureRegistration.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct DECLSPEC_UUID("34988ccd-4c0d-4043-b53d-3c1d2868860b") AdaptiveFeatureRegistration
        : AdaptiveFeatureRegistrationT<AdaptiveFeatureRegistration, ITypePeek>
    {
        AdaptiveFeatureRegistration(std::shared_ptr<::AdaptiveCards::FeatureRegistration> sharedParserRegistration =
                                        std::make_shared<::AdaptiveCards::FeatureRegistration>());

        void Set(winrt::hstring const& name, winrt::hstring const& version);
        winrt::hstring Get(winrt::hstring const& name);
        void Remove(winrt::hstring const& name);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        const std::shared_ptr<::AdaptiveCards::FeatureRegistration>& GetSharedFeatureRegistration()
        {
            return m_sharedFeatureRegistration;
        }

    private:
        std::shared_ptr<::AdaptiveCards::FeatureRegistration> m_sharedFeatureRegistration;
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveFeatureRegistration
        : AdaptiveFeatureRegistrationT<AdaptiveFeatureRegistration, implementation::AdaptiveFeatureRegistration>
    {
    };
}
