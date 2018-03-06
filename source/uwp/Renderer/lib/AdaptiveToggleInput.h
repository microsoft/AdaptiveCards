#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "ToggleInput.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class DECLSPEC_UUID("502edea9-72fd-4856-a89e-54565181bed8") AdaptiveToggleInput :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveToggleInput,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputElement,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement,
            Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveToggleInput, BaseTrust)

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
        IFACEMETHODIMP get_IsRequired(_Out_ boolean* isRequired);
        IFACEMETHODIMP put_IsRequired(_In_ boolean isRequired);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::Rendering::Uwp::ElementType* elementType);

        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::Rendering::Uwp::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::Rendering::Uwp::Spacing spacing);

        IFACEMETHODIMP get_Separator(_Out_ boolean* separator);
        IFACEMETHODIMP put_Separator(_In_ boolean separator);

        IFACEMETHODIMP get_ElementTypeString(_Out_ HSTRING* value);

        IFACEMETHODIMP get_AdditionalProperties(_Out_ ABI::Windows::Data::Json::IJsonObject** result);
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value);

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT GetSharedModel(_In_ std::shared_ptr<AdaptiveCards::ToggleInput>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        Microsoft::WRL::Wrappers::HString m_title;
        Microsoft::WRL::Wrappers::HString m_value;
        Microsoft::WRL::Wrappers::HString m_valueOn;
        Microsoft::WRL::Wrappers::HString m_valueOff;

        boolean m_isRequired;
        boolean m_separator;
        Microsoft::WRL::Wrappers::HString m_id;
        ABI::AdaptiveCards::Rendering::Uwp::Spacing m_spacing;
        Microsoft::WRL::ComPtr<ABI::Windows::Data::Json::IJsonObject> m_additionalProperties;
    };

    ActivatableClass(AdaptiveToggleInput);
}}}