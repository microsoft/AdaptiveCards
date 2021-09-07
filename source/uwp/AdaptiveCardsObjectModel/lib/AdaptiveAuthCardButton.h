// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AuthCardButton.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    class DECLSPEC_UUID("0DF8553F-E958-4E9C-897D-847691F1F3CC") AdaptiveAuthCardButton
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveAuthCardButton,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveAuthCardButton);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::AuthCardButton>& sharedAuthCardButton);

        IFACEMETHODIMP get_Type(_Outptr_ HSTRING* type);
        IFACEMETHODIMP put_Type(_In_ HSTRING type);

        IFACEMETHODIMP get_Title(_Outptr_ HSTRING* title);
        IFACEMETHODIMP put_Title(_In_ HSTRING title);

        IFACEMETHODIMP get_Image(_Outptr_ HSTRING* image);
        IFACEMETHODIMP put_Image(_In_ HSTRING image);

        IFACEMETHODIMP get_Value(_Outptr_ HSTRING* value);
        IFACEMETHODIMP put_Value(_In_ HSTRING value);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveCards::AuthCardButton>& sharedModel);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::Wrappers::HString m_type;
        Microsoft::WRL::Wrappers::HString m_title;
        Microsoft::WRL::Wrappers::HString m_image;
        Microsoft::WRL::Wrappers::HString m_value;
    };

    ActivatableClass(AdaptiveAuthCardButton);
}
