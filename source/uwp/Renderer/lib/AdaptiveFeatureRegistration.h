// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveFeatureRegistration.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct DECLSPEC_UUID("34988ccd-4c0d-4043-b53d-3c1d2868860b") AdaptiveFeatureRegistration
        : AdaptiveFeatureRegistrationT<AdaptiveFeatureRegistration, ITypePeek>
    {
        AdaptiveFeatureRegistration(std::shared_ptr<::AdaptiveCards::FeatureRegistration> sharedParserRegistration =
                                        std::make_shared<::AdaptiveCards::FeatureRegistration>());

        void Set(hstring const& name, hstring const& version);
        hstring Get(hstring const& name);
        void Remove(hstring const& name);

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
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveFeatureRegistration
        : AdaptiveFeatureRegistrationT<AdaptiveFeatureRegistration, implementation::AdaptiveFeatureRegistration>
    {
    };
}
