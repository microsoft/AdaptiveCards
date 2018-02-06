#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Util.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class CustomActionWrapper : public AdaptiveCards::BaseActionElement
    {
    public:
        CustomActionWrapper(ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement* actionElement) :
            AdaptiveCards::BaseActionElement(AdaptiveCards::ActionType::Custom),
            m_actionElement(actionElement)
        {}

        std::string GetId() const override;
        void SetId(const std::string value) override;

        std::string GetTitle() const override;
        void SetTitle(const std::string value) override;

        virtual Json::Value SerializeToJsonValue() override;

        HRESULT GetWrappedElement(ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement** actionElement);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement> m_actionElement;
    };
}}}
