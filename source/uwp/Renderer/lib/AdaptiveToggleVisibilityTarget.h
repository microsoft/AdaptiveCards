// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ToggleVisibilityTarget.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("d37e5b66-2a5e-4a9e-b087-dbef5a1705b1") AdaptiveToggleVisibilityTarget
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveNamespace::IAdaptiveToggleVisibilityTarget,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveToggleVisibilityTarget);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTarget>& sharedToggleTarget);

        // IAdaptiveToggleVisibilityTarget
        IFACEMETHODIMP get_ElementId(_Outptr_ HSTRING* id);
        IFACEMETHODIMP put_ElementId(_In_ HSTRING id);

        IFACEMETHODIMP get_IsVisible(_Out_ ABI::AdaptiveNamespace::IsVisible* value);
        IFACEMETHODIMP put_IsVisible(ABI::AdaptiveNamespace::IsVisible value);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTarget>& sharedModel);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::Wrappers::HString m_elementId;
        ABI::AdaptiveNamespace::IsVisible m_visibilityToggle;
    };

    ActivatableClass(AdaptiveToggleVisibilityTarget);
}
