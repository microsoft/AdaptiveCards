// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Util.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("34988ccd-4c0d-4043-b53d-3c1d2868860b") AdaptiveFeatureRegistration
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveNamespace::IAdaptiveFeatureRegistration>,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntime(AdaptiveFeatureRegistration);

    public:
        AdaptiveFeatureRegistration();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(std::shared_ptr<AdaptiveSharedNamespace::FeatureRegistration> sharedParserRegistration) noexcept;

        // IAdaptiveFeatureRegistration
        IFACEMETHODIMP Set(_In_ HSTRING name, _In_ HSTRING version) noexcept;
        IFACEMETHODIMP Get(_In_ HSTRING name, _Outptr_ HSTRING* version) noexcept;
        IFACEMETHODIMP Remove(_In_ HSTRING name) noexcept;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        std::shared_ptr<FeatureRegistration> GetSharedFeatureRegistration();

    private:
        std::shared_ptr<FeatureRegistration> m_sharedFeatureRegistration;
    };

    ActivatableClass(AdaptiveFeatureRegistration);
}
