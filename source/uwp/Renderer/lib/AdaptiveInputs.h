#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "InputValue.h"

AdaptiveNamespaceStart
    class AdaptiveInputs :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveNamespaceRef::IAdaptiveInputs>
    {
        AdaptiveRuntime(AdaptiveInputs)

    public:
        AdaptiveInputs();
        HRESULT RuntimeClassInitialize() noexcept;

        // IAdaptiveInputs
        IFACEMETHODIMP AsJson(_Out_ ABI::Windows::Data::Json::IJsonObject** value);
        IFACEMETHODIMP AsValueSet(_COM_Outptr_ ABI::Windows::Foundation::Collections::IPropertySet** value);

        HRESULT AddInputValue(ABI::AdaptiveNamespaceRef::IAdaptiveInputValue* inputValue);

    private:
        std::string GetInputItemsAsJsonString();
        std::shared_ptr<std::vector<Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveInputValue>>> m_inputValues;
    };

    ActivatableClass(AdaptiveInputs);
AdaptiveNamespaceEnd
