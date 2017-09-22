#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "ChoiceSetInput.h"
#include "Enums.h"
#include <windows.foundation.h>

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveChoiceSetInput :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceSetInput,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveInputElement,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveChoiceSetInput, BaseTrust)

    public:
        AdaptiveChoiceSetInput();

        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::ChoiceSetInput>& sharedChoiceSetInput);

        // IAdaptiveChoiceSetInput

        IFACEMETHODIMP get_IsMultiSelect(_Out_ boolean* isMultiSelect);
        IFACEMETHODIMP put_IsMultiSelect(_In_ boolean isMultiSelect);

        IFACEMETHODIMP get_ChoiceSetStyle(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ChoiceSetStyle* choiceSetStyle);
        IFACEMETHODIMP put_ChoiceSetStyle(_In_ ABI::AdaptiveCards::XamlCardRenderer::ChoiceSetStyle choiceSetStyle);

        IFACEMETHODIMP get_Choices(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput*>** columns);

        // IAdaptiveInputElement
        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_IsRequired(_Out_ boolean* isRequired);
        IFACEMETHODIMP put_IsRequired(_In_ boolean isRequired);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::XamlCardRenderer::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::XamlCardRenderer::Spacing spacing);

        IFACEMETHODIMP get_Separator(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator** separator);
        IFACEMETHODIMP put_Separator(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator* separator);

        IFACEMETHODIMP get_Speak(_In_ HSTRING* speak);
        IFACEMETHODIMP put_Speak(_Out_ HSTRING speak);

    private:
        // TODO: MSFT 11015796: Sync UWP Projection container classes to Shared object model counterparts.
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput*>> m_choices;

        //Using a Container as backing element for now
        std::shared_ptr<AdaptiveCards::ChoiceSetInput> m_sharedChoiceSetInput;
    };

    ActivatableClass(AdaptiveChoiceSetInput);
}}
