#pragma once
#include "AdaptiveCards.XamlCardRenderer.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveOpenUrlActionEventArgs :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveOpenUrlActionEventArgs,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionEventArgs>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveOpenUrlActionEventArgs, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize();
        IFACEMETHODIMP get_ActionType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ActionType* actionType);
    };
    ActivatableClass(AdaptiveOpenUrlActionEventArgs);
}}