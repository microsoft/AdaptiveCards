#pragma once

#include "pch.h"
#include "util.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveCardParseResult :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            Microsoft::WRL::Implements<ABI::AdaptiveCards::Uwp::IAdaptiveCardParseResult>>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveCardParseResult, BaseTrust)

    public:
        AdaptiveCardParseResult();

        HRESULT RuntimeClassInitialize(); 
        HRESULT RuntimeClassInitialize(ABI::AdaptiveCards::Uwp::IAdaptiveCard* adaptiveCard);

        // IAdaptiveCardParseResult
        IFACEMETHODIMP get_AdaptiveCard(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveCard** value);

        IFACEMETHODIMP get_Errors(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveFailure*>** value);
        IFACEMETHODIMP get_Warnings(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveFailure*>** value);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveCard> m_adaptiveCard;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveFailure*>> m_errors;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveFailure*>> m_warnings;
    };

    ActivatableClass(AdaptiveCardParseResult);
}}