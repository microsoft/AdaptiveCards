#pragma once

#include "AdaptiveCards.Uwp.h"
#include "ChoiceSetInput.h"
#include "Enums.h"
#include <windows.foundation.h>

namespace AdaptiveCards { namespace Uwp
{
    class DECLSPEC_UUID("fa103f57-5d54-48ba-80a5-d8939b85e82d") AdaptiveChoiceSetInput :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Uwp::IAdaptiveChoiceSetInput,
            ABI::AdaptiveCards::Uwp::IAdaptiveInputElement,
            ABI::AdaptiveCards::Uwp::IAdaptiveCardElement,
            Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveChoiceSetInput, BaseTrust)

    public:
        AdaptiveChoiceSetInput();

        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::ChoiceSetInput>& sharedChoiceSetInput);

        // IAdaptiveChoiceSetInput

        IFACEMETHODIMP get_IsMultiSelect(_Out_ boolean* isMultiSelect);
        IFACEMETHODIMP put_IsMultiSelect(_In_ boolean isMultiSelect);

        IFACEMETHODIMP get_ChoiceSetStyle(_Out_ ABI::AdaptiveCards::Uwp::ChoiceSetStyle* choiceSetStyle);
        IFACEMETHODIMP put_ChoiceSetStyle(_In_ ABI::AdaptiveCards::Uwp::ChoiceSetStyle choiceSetStyle);

        IFACEMETHODIMP get_Choices(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveChoiceInput*>** columns);

        // IAdaptiveInputElement
        IFACEMETHODIMP get_IsRequired(_Out_ boolean* isRequired);
        IFACEMETHODIMP put_IsRequired(_In_ boolean isRequired);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::Uwp::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::Uwp::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::Uwp::Spacing spacing);

        IFACEMETHODIMP get_Separator(_Out_ boolean* separator);
        IFACEMETHODIMP put_Separator(_In_ boolean separator);
        
        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_ElementTypeString(_Out_ HSTRING* value);

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveCards::ChoiceSetInput>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveChoiceInput*>> m_choices;
        boolean m_isRequired;
        boolean m_isMultiSelect;
        ABI::AdaptiveCards::Uwp::ChoiceSetStyle m_choiceSetStyle;

        boolean m_separator;
        Microsoft::WRL::Wrappers::HString m_id;
        ABI::AdaptiveCards::Uwp::Spacing m_spacing;
    };

    ActivatableClass(AdaptiveChoiceSetInput);
}}
