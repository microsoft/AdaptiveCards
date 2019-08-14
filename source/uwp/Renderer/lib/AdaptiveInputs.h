// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "InputValue.h"

namespace AdaptiveNamespace
{
    class AdaptiveInputs
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveInputs>
    {
        AdaptiveRuntime(AdaptiveInputs);

    public:
        AdaptiveInputs();
        HRESULT RuntimeClassInitialize() noexcept;

        // IAdaptiveInputs
        IFACEMETHODIMP AsJson(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** value);
        IFACEMETHODIMP AsValueSet(_COM_Outptr_ ABI::Windows::Foundation::Collections::IPropertySet** value);

        HRESULT AddInputValue(_In_ ABI::AdaptiveNamespace::IAdaptiveInputValue* inputValue);

    private:
        std::string GetInputItemsAsJsonString();
        std::shared_ptr<std::vector<Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveInputValue>>> m_inputValues;
    };

    ActivatableClass(AdaptiveInputs);
}
