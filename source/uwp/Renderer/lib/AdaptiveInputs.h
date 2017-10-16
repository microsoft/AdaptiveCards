#pragma once

#include "AdaptiveCards.Uwp.h"
#include "InputItem.h"

namespace AdaptiveCards { namespace Uwp 
{
    class AdaptiveInputs :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Uwp::IAdaptiveInputs>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveInputs, BaseTrust)

    public:
        AdaptiveInputs();
        HRESULT RuntimeClassInitialize() noexcept;

        // IAdaptiveInputs
        IFACEMETHODIMP AsJson(_In_ ABI::AdaptiveCards::Uwp::InputValueMode inputMode, _Out_ ABI::Windows::Data::Json::IJsonObject** value);
        IFACEMETHODIMP AsValueSet(_COM_Outptr_ ABI::Windows::Foundation::Collections::IPropertySet** value);

        std::shared_ptr<std::vector<InputItem>> GetInputItems();

    private:
        std::string GetInputItemsAsJsonString();
        std::shared_ptr<std::vector<AdaptiveCards::Uwp::InputItem>> m_inputItems;
    };

    ActivatableClass(AdaptiveInputs);
}}
