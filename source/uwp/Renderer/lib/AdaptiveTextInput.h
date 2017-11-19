#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "TextInput.h"

namespace AdaptiveCards { namespace Uwp
{
    class DECLSPEC_UUID("2e716e94-a83a-4e9b-9873-bff858af068d") AdaptiveTextInput :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Uwp::IAdaptiveTextInput,
            ABI::AdaptiveCards::Uwp::IAdaptiveInputElement,
            ABI::AdaptiveCards::Uwp::IAdaptiveCardElement,
            Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveTextInput, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::TextInput>& sharedTextInput);

        // IAdaptiveTextInput
        IFACEMETHODIMP get_Placeholder(_Out_ HSTRING* placeholder);
        IFACEMETHODIMP put_Placeholder(_In_ HSTRING placeholder);

        IFACEMETHODIMP get_Value(_Out_ HSTRING* text);
        IFACEMETHODIMP put_Value(_In_ HSTRING text);

        IFACEMETHODIMP get_IsMultiline(_Out_ boolean* isMultiline);
        IFACEMETHODIMP put_IsMultiline(_In_ boolean isMultiline);

        IFACEMETHODIMP get_MaxLength(_Out_ UINT32* value);
        IFACEMETHODIMP put_MaxLength(_In_ UINT32 value);

        IFACEMETHODIMP get_TextInputStyle(_Out_ ABI::AdaptiveCards::Uwp::TextInputStyle *textInputStyle);
        IFACEMETHODIMP put_TextInputStyle(_In_ ABI::AdaptiveCards::Uwp::TextInputStyle textInputStyle);

        // IAdaptiveInputElement
        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_IsRequired(_Out_ boolean* isRequired);
        IFACEMETHODIMP put_IsRequired(_In_ boolean isRequired);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::Uwp::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::Uwp::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::Uwp::Spacing spacing);

        IFACEMETHODIMP get_Separator(_Out_ boolean* separator);
        IFACEMETHODIMP put_Separator(_In_ boolean separator);

        IFACEMETHODIMP get_ElementTypeString(_Out_ HSTRING* value);

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT GetSharedModel(_In_ std::shared_ptr<AdaptiveCards::TextInput>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        std::shared_ptr<AdaptiveCards::TextInput> m_sharedTextInput;
    };

    ActivatableClass(AdaptiveTextInput);
}}