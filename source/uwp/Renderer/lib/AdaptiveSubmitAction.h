#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "SubmitAction.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveSubmitAction :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSubmitAction,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveSubmitAction, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::SubmitAction>& sharedSubmitAction);

        // IAdaptiveActionElement
        IFACEMETHODIMP get_ActionType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ActionType* actionType);

        IFACEMETHODIMP get_Title(_Out_ HSTRING* title);
        IFACEMETHODIMP put_Title(_In_ HSTRING title);

        IFACEMETHODIMP get_DataJson(_Out_ ABI::Windows::Data::Json::IJsonObject** data);
        IFACEMETHODIMP put_DataJson(_In_ ABI::Windows::Data::Json::IJsonObject* data);
    private:
        std::shared_ptr<AdaptiveCards::SubmitAction> m_sharedSubmitAction;
    };

    ActivatableClass(AdaptiveSubmitAction);
}}