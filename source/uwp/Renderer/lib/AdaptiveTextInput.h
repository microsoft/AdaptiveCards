#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "TextInput.h"
#include "AdaptiveInputElement.h"

AdaptiveNamespaceStart
    class DECLSPEC_UUID("2e716e94-a83a-4e9b-9873-bff858af068d") AdaptiveTextInput :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveTextInput,
            ABI::AdaptiveNamespace::IAdaptiveInputElement,
            ABI::AdaptiveNamespace::IAdaptiveCardElement,
            Microsoft::WRL::CloakedIid<ITypePeek>,
            Microsoft::WRL::CloakedIid<AdaptiveNamespace::AdaptiveInputElementBase>>
    {
        AdaptiveRuntime(AdaptiveTextInput)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveSharedNamespace::TextInput>& sharedTextInput);

        // IAdaptiveTextInput
        IFACEMETHODIMP get_Placeholder(_Out_ HSTRING* placeholder);
        IFACEMETHODIMP put_Placeholder(_In_ HSTRING placeholder);

        IFACEMETHODIMP get_Value(_Out_ HSTRING* text);
        IFACEMETHODIMP put_Value(_In_ HSTRING text);

        IFACEMETHODIMP get_IsMultiline(_Out_ boolean* isMultiline);
        IFACEMETHODIMP put_IsMultiline(_In_ boolean isMultiline);

        IFACEMETHODIMP get_MaxLength(_Out_ UINT32* value);
        IFACEMETHODIMP put_MaxLength(_In_ UINT32 value);

        IFACEMETHODIMP get_TextInputStyle(_Out_ ABI::AdaptiveNamespace::TextInputStyle *textInputStyle);
        IFACEMETHODIMP put_TextInputStyle(_In_ ABI::AdaptiveNamespace::TextInputStyle textInputStyle);

        // IAdaptiveInputElement
        IFACEMETHODIMP get_IsRequired(_Out_ boolean* isRequired) { return AdaptiveInputElementBase::get_IsRequired(isRequired); }
        IFACEMETHODIMP put_IsRequired(_In_ boolean isRequired) { return AdaptiveInputElementBase::put_IsRequired(isRequired); }

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveNamespace::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveNamespace::Spacing* spacing) { return AdaptiveCardElementBase::get_Spacing(spacing); }
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveNamespace::Spacing spacing) { return AdaptiveCardElementBase::put_Spacing(spacing); }

        IFACEMETHODIMP get_Separator(_Out_ boolean* separator) { return AdaptiveCardElementBase::get_Separator(separator); }
        IFACEMETHODIMP put_Separator(_In_ boolean separator) { return AdaptiveCardElementBase::put_Separator(separator); }

        IFACEMETHODIMP get_Id(_Out_ HSTRING* id) { return AdaptiveCardElementBase::get_Id(id); }
        IFACEMETHODIMP put_Id(_In_ HSTRING id) { return AdaptiveCardElementBase::put_Id(id); }

        IFACEMETHODIMP get_ElementTypeString(_Out_ HSTRING* value) { return AdaptiveCardElementBase::get_ElementTypeString(value); }

        IFACEMETHODIMP get_AdditionalProperties(_Out_ ABI::Windows::Data::Json::IJsonObject** result) { return AdaptiveCardElementBase::get_AdditionalProperties(result); }
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value) { return AdaptiveCardElementBase::put_AdditionalProperties(value); }

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result) { return AdaptiveCardElementBase::ToJson(result); }

        virtual HRESULT GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel) override;

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        Microsoft::WRL::Wrappers::HString m_placeholder;
        Microsoft::WRL::Wrappers::HString m_value;
        UINT32 m_maxLength;
        boolean m_isMultiline;
        ABI::AdaptiveNamespace::TextInputStyle m_textInputStyle;
    };

    ActivatableClass(AdaptiveTextInput);
AdaptiveNamespaceEnd