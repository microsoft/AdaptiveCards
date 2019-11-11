// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "BaseInputElement.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("E2E42BA6-A0AE-4B01-B161-29AF2F2B302B") AdaptiveInputElementBase : public AdaptiveCardElementBase
    {
    protected:
        HRESULT InitializeBaseElement(const std::shared_ptr<AdaptiveSharedNamespace::BaseInputElement>& sharedModel);

        IFACEMETHODIMP get_IsRequired(_Out_ boolean* isRequired);
        IFACEMETHODIMP put_IsRequired(boolean isRequired);

        IFACEMETHODIMP get_ErrorMessage(_Outptr_ HSTRING* title);
        IFACEMETHODIMP put_ErrorMessage(_In_ HSTRING title);

        IFACEMETHODIMP get_Label(_Outptr_ HSTRING* label);
        IFACEMETHODIMP put_Label(_In_ HSTRING label);

        HRESULT SetSharedElementProperties(std::shared_ptr<AdaptiveSharedNamespace::BaseInputElement> sharedCardElement);

    private:
        boolean m_isRequired;
        Microsoft::WRL::Wrappers::HString m_errorMessage;
        Microsoft::WRL::Wrappers::HString m_label;
    };
}
