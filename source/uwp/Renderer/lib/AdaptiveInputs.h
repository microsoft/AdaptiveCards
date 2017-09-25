#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "InputItem.h"

namespace AdaptiveCards { namespace XamlCardRenderer 
{
    class AdaptiveInputs :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveInputs>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveInputs, BaseTrust)

    public:
        AdaptiveInputs();
        HRESULT RuntimeClassInitialize() noexcept;

        // IAdaptiveInputs
        IFACEMETHODIMP get_AsJson(_Out_ ABI::Windows::Data::Json::IJsonObject** value);

        std::shared_ptr<std::vector<InputItem>> GetInputItems();

    private:
        std::shared_ptr<std::vector<AdaptiveCards::XamlCardRenderer::InputItem>> m_inputItems;
    };

    ActivatableClass(AdaptiveInputs);
}}
