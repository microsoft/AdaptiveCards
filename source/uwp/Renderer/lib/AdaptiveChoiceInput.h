// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "ChoiceInput.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("7263dbfb-cb43-47f9-9022-b43372f529f9") AdaptiveChoiceInput
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveNamespace::IAdaptiveChoiceInput,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveChoiceInput);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::ChoiceInput>& sharedChoiceInput);

        // IAdaptiveChoiceInput
        IFACEMETHODIMP get_Title(_Outptr_ HSTRING* title);
        IFACEMETHODIMP put_Title(_In_ HSTRING title);

        IFACEMETHODIMP get_Value(_Outptr_ HSTRING* value);
        IFACEMETHODIMP put_Value(_In_ HSTRING value);

        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveNamespace::ElementType* elementType);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::ChoiceInput>& sharedModel);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        std::shared_ptr<AdaptiveSharedNamespace::ChoiceInput> m_sharedChoiceInput;
    };

    ActivatableClass(AdaptiveChoiceInput);
}
