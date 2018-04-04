#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Util.h"

AdaptiveNamespaceStart
    class CustomActionWrapper : public AdaptiveSharedNamespace::BaseActionElement
    {
    public:
        CustomActionWrapper(ABI::AdaptiveNamespace::IAdaptiveActionElement* actionElement) :
            AdaptiveSharedNamespace::BaseActionElement(AdaptiveSharedNamespace::ActionType::Custom),
            m_actionElement(actionElement)
        {}

        std::string GetId() const override;
        void SetId(const std::string value) override;

        std::string GetTitle() const override;
        void SetTitle(const std::string value) override;

        virtual Json::Value SerializeToJsonValue() override;

        HRESULT GetWrappedElement(ABI::AdaptiveNamespace::IAdaptiveActionElement** actionElement);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionElement> m_actionElement;
    };
AdaptiveNamespaceEnd
