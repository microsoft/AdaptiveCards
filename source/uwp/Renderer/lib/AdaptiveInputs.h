#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "InputValue.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp 
{
    class AdaptiveInputs :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputs>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveInputs, BaseTrust)

    public:
        AdaptiveInputs();
        HRESULT RuntimeClassInitialize() noexcept;

        // IAdaptiveInputs
        IFACEMETHODIMP AsJson(_Out_ ABI::Windows::Data::Json::IJsonObject** value);
        IFACEMETHODIMP AsValueSet(_COM_Outptr_ ABI::Windows::Foundation::Collections::IPropertySet** value);

        HRESULT AddInputValue(ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputValue* inputValue);

    private:
        std::string GetInputItemsAsJsonString();
        std::shared_ptr<std::vector<Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputValue>>> m_inputValues;
    };

    ActivatableClass(AdaptiveInputs);
}}}
