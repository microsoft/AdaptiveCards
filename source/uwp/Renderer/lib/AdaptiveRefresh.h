// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Refresh.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("8D452985-D06B-4541-AEAF-DD7A3DC7CCD8") AdaptiveRefresh
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveNamespace::IAdaptiveRefresh,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveRefresh);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::Refresh>& sharedRefresh);

        IFACEMETHODIMP get_Action(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** action);
        IFACEMETHODIMP put_Action(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action);

        IFACEMETHODIMP get_UserIds(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<HSTRING>** userIds);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::Refresh>& sharedModel);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionElement> m_action;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<HSTRING>> m_userIds;
    };

    ActivatableClass(AdaptiveRefresh);
}
