#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "ChoiceSetInput.h"
#include "Enums.h"
#include <windows.foundation.h>

AdaptiveNamespaceStart
    class DECLSPEC_UUID("fa103f57-5d54-48ba-80a5-d8939b85e82d") AdaptiveChoiceSetInput :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveChoiceSetInput,
            ABI::AdaptiveNamespace::IAdaptiveInputElement,
            ABI::AdaptiveNamespace::IAdaptiveCardElement,
            Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveChoiceSetInput)

    public:
        AdaptiveChoiceSetInput();

        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveSharedNamespace::ChoiceSetInput>& sharedChoiceSetInput);

        // IAdaptiveChoiceSetInput

        IFACEMETHODIMP get_Value(_Out_ HSTRING* value);
        IFACEMETHODIMP put_Value(_In_ HSTRING value);

        IFACEMETHODIMP get_IsMultiSelect(_Out_ boolean* isMultiSelect);
        IFACEMETHODIMP put_IsMultiSelect(_In_ boolean isMultiSelect);

        IFACEMETHODIMP get_ChoiceSetStyle(_Out_ ABI::AdaptiveNamespace::ChoiceSetStyle* choiceSetStyle);
        IFACEMETHODIMP put_ChoiceSetStyle(_In_ ABI::AdaptiveNamespace::ChoiceSetStyle choiceSetStyle);

        IFACEMETHODIMP get_Choices(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveChoiceInput*>** columns);

        // IAdaptiveInputElement
        IFACEMETHODIMP get_IsRequired(_Out_ boolean* isRequired);
        IFACEMETHODIMP put_IsRequired(_In_ boolean isRequired);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveNamespace::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveNamespace::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveNamespace::Spacing spacing);

        IFACEMETHODIMP get_Separator(_Out_ boolean* separator);
        IFACEMETHODIMP put_Separator(_In_ boolean separator);
        
        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_ElementTypeString(_Out_ HSTRING* value);

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

        IFACEMETHODIMP get_AdditionalProperties(_Out_ ABI::Windows::Data::Json::IJsonObject** result);
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value);

        HRESULT GetSharedModel(_In_ std::shared_ptr<AdaptiveSharedNamespace::ChoiceSetInput>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveChoiceInput*>> m_choices;
        boolean m_isRequired;
        boolean m_isMultiSelect;
        ABI::AdaptiveNamespace::ChoiceSetStyle m_choiceSetStyle;
        Microsoft::WRL::Wrappers::HString m_value;

        boolean m_separator;
        Microsoft::WRL::Wrappers::HString m_id;
        ABI::AdaptiveNamespace::Spacing m_spacing;
        Microsoft::WRL::ComPtr<ABI::Windows::Data::Json::IJsonObject> m_additionalProperties;
    };

    ActivatableClass(AdaptiveChoiceSetInput);
AdaptiveNamespaceEnd
