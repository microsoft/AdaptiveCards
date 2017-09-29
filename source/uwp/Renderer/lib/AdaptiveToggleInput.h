#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "ToggleInput.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveToggleInput :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Uwp::IAdaptiveToggleInput,
            ABI::AdaptiveCards::Uwp::IAdaptiveInputElement,
            ABI::AdaptiveCards::Uwp::IAdaptiveCardElement>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveToggleInput, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::ToggleInput>& sharedToggleInput);

        // IAdaptiveToggleInput
        IFACEMETHODIMP get_Title(_Out_ HSTRING* title);
        IFACEMETHODIMP put_Title(_In_ HSTRING title);

        IFACEMETHODIMP get_Value(_Out_ HSTRING* value);
        IFACEMETHODIMP put_Value(_In_ HSTRING value);

        IFACEMETHODIMP get_ValueOff(_Out_ HSTRING* value);
        IFACEMETHODIMP put_ValueOff(_In_ HSTRING value);

        IFACEMETHODIMP get_ValueOn(_Out_ HSTRING* value);
        IFACEMETHODIMP put_ValueOn(_In_ HSTRING value);

        // IAdaptiveInputElement
        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_IsRequired(_Out_ boolean* isRequired);
        IFACEMETHODIMP put_IsRequired(_In_ boolean isRequired);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::Uwp::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::Uwp::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::Uwp::Spacing spacing);

        IFACEMETHODIMP get_Separator(boolean* separator);
        IFACEMETHODIMP put_Separator(boolean separator);

        IFACEMETHODIMP get_ElementTypeString(_Out_ HSTRING* value);

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

    private:
        std::shared_ptr<AdaptiveCards::ToggleInput> m_sharedToggleInput;
    };

    ActivatableClass(AdaptiveToggleInput);
}}