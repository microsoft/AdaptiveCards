// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Fact.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    class DECLSPEC_UUID("d37e5b66-2a5e-4a9e-b087-dbef5a1705b1") AdaptiveFact
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveFact,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveFact);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::Fact>& sharedFact);

        // IAdaptiveFact
        IFACEMETHODIMP get_Title(_Outptr_ HSTRING* title);
        IFACEMETHODIMP put_Title(_In_ HSTRING title);

        IFACEMETHODIMP get_Value(_Outptr_ HSTRING* value);
        IFACEMETHODIMP put_Value(_In_ HSTRING value);

        IFACEMETHODIMP get_Language(_Outptr_ HSTRING* language);
        IFACEMETHODIMP put_Language(_In_ HSTRING language);

        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ElementType* elementType);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveCards::Fact>& sharedModel);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::Wrappers::HString m_title;
        Microsoft::WRL::Wrappers::HString m_value;
        Microsoft::WRL::Wrappers::HString m_language;
    };

    ActivatableClass(AdaptiveFact);
}
