// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "RenderedAdaptiveCard.h"
#include "AdaptiveActionInvoker.h"
#include "AdaptiveMediaEventInvoker.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("F29649FF-C718-4F94-8F39-2415C86BE77E") AdaptiveRenderContext
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<IWeakReferenceSource>,
                                              ABI::AdaptiveNamespace::IAdaptiveRenderContext,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveRenderContext);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveFeatureRegistration* featureRegistration,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveElementRendererRegistration* elementRendererRegistration,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveActionRendererRegistration* actionRendererRegistration,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveCardResourceResolvers* resourceResolvers,
                                       _In_ ABI::Windows::UI::Xaml::IResourceDictionary* overrideStyles,
                                       _In_ ABI::Windows::UI::Xaml::IResourceDictionary* defaultActionSentimentStyles,
                                       _In_ AdaptiveNamespace::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP get_HostConfig(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveHostConfig** value) override;
        IFACEMETHODIMP get_FeatureRegistration(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveFeatureRegistration** value) override;
        IFACEMETHODIMP get_ElementRenderers(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveElementRendererRegistration** value) override;
        IFACEMETHODIMP get_ActionRenderers(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionRendererRegistration** value) override;
        IFACEMETHODIMP get_ActionInvoker(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionInvoker** value) override;
        IFACEMETHODIMP get_MediaEventInvoker(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveMediaEventInvoker** value) override;
        IFACEMETHODIMP get_UserInputs(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputs** value) override;
        IFACEMETHODIMP AddInputValue(_In_ ABI::AdaptiveNamespace::IAdaptiveInputValue* inputValue,
                                     _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs) override;
        IFACEMETHODIMP LinkSubmitActionToCard(_In_ ABI::AdaptiveNamespace::IAdaptiveSubmitAction* submitAction,
                                     _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs) override;
        IFACEMETHODIMP LinkCardToParent(_In_ ABI::AdaptiveNamespace::IAdaptiveCard* card,
                                     _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs) override;
        IFACEMETHODIMP AddInlineShowCard(_In_opt_ ABI::AdaptiveNamespace::IAdaptiveActionSet* actionSet,
                                         _In_ ABI::AdaptiveNamespace::IAdaptiveShowCardAction* showCardAction,
                                         _In_ ABI::Windows::UI::Xaml::IUIElement* showCardUIElement,
                                         _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs) override;
        IFACEMETHODIMP GetInputValue(_In_ ABI::AdaptiveNamespace::IAdaptiveInputElement* inputElement,
                                     _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveInputValue** inputValue) override;

        IFACEMETHODIMP get_ResourceResolvers(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardResourceResolvers** value) override;
        IFACEMETHODIMP get_OverrideStyles(_COM_Outptr_ ABI::Windows::UI::Xaml::IResourceDictionary** overrideDictionary) override;
        IFACEMETHODIMP AddError(ABI::AdaptiveNamespace::ErrorStatusCode statusCode, _In_ HSTRING message) override;
        IFACEMETHODIMP AddWarning(ABI::AdaptiveNamespace::WarningStatusCode statusCode, _In_ HSTRING message) override;

        HRESULT AddInlineShowCard(_In_opt_ ABI::AdaptiveNamespace::IAdaptiveCard* adaptiveCard,
                                  _In_ ABI::AdaptiveNamespace::IAdaptiveShowCardAction* showCardAction,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* showCardUIElement,
                                  _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs);

        HRESULT GetRenderResult(_COM_Outptr_ AdaptiveNamespace::RenderedAdaptiveCard** renderResult);
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> GetDefaultActionSentimentDictionary();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveFeatureRegistration> m_featureRegistration;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveElementRendererRegistration> m_elementRendererRegistration;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionRendererRegistration> m_actionRendererRegistration;
        Microsoft::WRL::WeakRef m_weakRenderResult;
        Microsoft::WRL::ComPtr<AdaptiveNamespace::AdaptiveActionInvoker> m_actionInvoker;
        Microsoft::WRL::ComPtr<AdaptiveNamespace::AdaptiveMediaEventInvoker> m_mediaEventInvoker;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardResourceResolvers> m_resourceResolvers;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_overrideDictionary;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_actionSentimentDefaultDictionary;
    };

    ActivatableClass(AdaptiveRenderContext);
}
