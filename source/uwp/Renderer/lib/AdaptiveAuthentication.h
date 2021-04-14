// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Authentication.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("8074FA48-AF80-4295-9BB3-D4827FA81CBE") AdaptiveAuthentication
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveNamespace::IAdaptiveAuthentication,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveAuthentication);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::Authentication>& sharedRefresh);

        IFACEMETHODIMP get_Text(_Outptr_ HSTRING* text);
        IFACEMETHODIMP put_Text(_In_ HSTRING text);

        IFACEMETHODIMP get_ConnectionName(_Outptr_ HSTRING* connectionName);
        IFACEMETHODIMP put_ConnectionName(_In_ HSTRING connectionName);

        IFACEMETHODIMP get_TokenExchangeResource(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveTokenExchangeResource** tokenExchangeResource);
        IFACEMETHODIMP put_TokenExchangeResource(_In_ ABI::AdaptiveNamespace::IAdaptiveTokenExchangeResource* tokenExchangeResource);

        IFACEMETHODIMP get_Buttons(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveAuthCardButton*>** buttons);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::Authentication>& sharedModel);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::Wrappers::HString m_text;
        Microsoft::WRL::Wrappers::HString m_connectionName;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveTokenExchangeResource> m_tokenExchangeResource;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveAuthCardButton*>> m_buttons;
    };

    ActivatableClass(AdaptiveAuthentication);
}
