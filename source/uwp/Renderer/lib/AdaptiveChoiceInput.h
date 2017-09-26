#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "ChoiceInput.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveChoiceInput :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Uwp::IAdaptiveChoiceInput>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveChoiceInput, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::ChoiceInput>& sharedChoiceInput);

        // IAdaptiveChoiceInput
        IFACEMETHODIMP get_Title(_In_ HSTRING* title);
        IFACEMETHODIMP put_Title(_Out_ HSTRING title);

        IFACEMETHODIMP get_Value(_In_ HSTRING* value);
        IFACEMETHODIMP put_Value(_Out_ HSTRING value);

        IFACEMETHODIMP get_IsSelected(_Out_ boolean* isSelected);
        IFACEMETHODIMP put_IsSelected(_In_ boolean isSelected);

        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::Uwp::ElementType* elementType);

    private:
        std::shared_ptr<AdaptiveCards::ChoiceInput> m_sharedChoiceInput;
    };

    ActivatableClass(AdaptiveChoiceInput);
}}