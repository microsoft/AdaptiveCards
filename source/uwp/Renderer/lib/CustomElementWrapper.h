#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Util.h"

namespace AdaptiveCards { namespace Uwp
{
    class CustomElementWrapper : public AdaptiveCards::BaseCardElement
    {
    public:
        CustomElementWrapper(ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* cardElement):
            BaseCardElement(AdaptiveCards::CardElementType::Custom),
            m_cardElement(cardElement)
        {}

        bool GetSeparator() const override;
        void SetSeparator(const bool value) override;

        Spacing GetSpacing() const override;
        void SetSpacing(const Spacing value) override;

        std::string GetId() const override;
        void SetId(const std::string value) override;

        virtual std::string Serialize() override;

        HRESULT GetWrappedElement(ABI::AdaptiveCards::Uwp::IAdaptiveCardElement** cardElement);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveCardElement> m_cardElement;
    };
}}
