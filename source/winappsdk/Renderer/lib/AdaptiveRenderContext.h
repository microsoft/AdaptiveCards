// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "RenderedAdaptiveCard.h"
#include "AdaptiveActionInvoker.h"
#include "AdaptiveMediaEventInvoker.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class DECLSPEC_UUID("F29649FF-C718-4F94-8F39-2415C86BE77E") AdaptiveRenderContext
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<IWeakReferenceSource>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveRenderContext);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                       _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFeatureRegistration* featureRegistration,
                                       _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementRendererRegistration* elementRendererRegistration,
                                       _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionRendererRegistration* actionRendererRegistration,
                                       _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardResourceResolvers* resourceResolvers,
                                       _In_ ABI::Windows::UI::Xaml::IResourceDictionary* overrideStyles,
                                       _In_ ABI::Windows::UI::Xaml::IResourceDictionary* defaultActionSentimentStyles,
                                       _In_ AdaptiveCards::Rendering::Uwp::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP get_HostConfig(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig** value) override;
        IFACEMETHODIMP get_FeatureRegistration(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFeatureRegistration** value) override;
        IFACEMETHODIMP get_ElementRenderers(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementRendererRegistration** value) override;
        IFACEMETHODIMP get_ActionRenderers(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionRendererRegistration** value) override;
        IFACEMETHODIMP get_ActionInvoker(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionInvoker** value) override;
        IFACEMETHODIMP get_MediaEventInvoker(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveMediaEventInvoker** value) override;
        IFACEMETHODIMP get_UserInputs(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputs** value) override;
        IFACEMETHODIMP AddInputValue(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputValue* inputValue,
                                     _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs) override;
        IFACEMETHODIMP LinkSubmitActionToCard(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* submitAction,
                                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs) override;
        IFACEMETHODIMP LinkCardToParent(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard* card,
                                        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs) override;

        IFACEMETHODIMP GetInputValue(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInputElement* inputElement,
                                     _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputValue** inputValue) override;

        IFACEMETHODIMP get_Rtl(_COM_Outptr_ ABI::Windows::Foundation::IReference<bool>** value) override;
        IFACEMETHODIMP put_Rtl(_In_ ABI::Windows::Foundation::IReference<bool>* value) override;

        IFACEMETHODIMP get_TextStyle(_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::TextStyle>** value) override;
        IFACEMETHODIMP put_TextStyle(_In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::TextStyle>* value) override;

        IFACEMETHODIMP get_HorizontalContentAlignment(
            _Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>** value) override;
        IFACEMETHODIMP put_HorizontalContentAlignment(
            _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>* value) override;

        IFACEMETHODIMP get_ResourceResolvers(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardResourceResolvers** value) override;
        IFACEMETHODIMP get_OverrideStyles(_COM_Outptr_ ABI::Windows::UI::Xaml::IResourceDictionary** overrideDictionary) override;
        IFACEMETHODIMP AddError(ABI::AdaptiveCards::ObjectModel::Uwp::ErrorStatusCode statusCode, _In_ HSTRING message) override;
        IFACEMETHODIMP AddWarning(ABI::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode statusCode, _In_ HSTRING message) override;

        HRESULT AddInlineShowCard(_In_opt_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionSet* actionSet,
                                  _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveShowCardAction* showCardAction,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionButtonUIElement,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionOverflowUIElement,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* showCardUIElement,
                                  UINT32 primaryButtonIndex,
                                  _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs);

        HRESULT AddInlineShowCard(_In_opt_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard* adaptiveCard,
                                  _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveShowCardAction* showCardAction,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionButtonUIElement,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionOverflowUIElement,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* showCardUIElement,
                                  UINT32 primaryButtonIndex,
                                  _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs);

        HRESULT AddOverflowButton(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionSet* actionSet,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionUIElement);

        HRESULT AddOverflowButton(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard* actionCard,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionUIElement);

        HRESULT GetRenderResult(_COM_Outptr_ AdaptiveCards::Rendering::Uwp::RenderedAdaptiveCard** renderResult);
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> GetDefaultActionSentimentDictionary();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFeatureRegistration> m_featureRegistration;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementRendererRegistration> m_elementRendererRegistration;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionRendererRegistration> m_actionRendererRegistration;
        Microsoft::WRL::WeakRef m_weakRenderResult;
        Microsoft::WRL::ComPtr<AdaptiveCards::Rendering::Uwp::AdaptiveActionInvoker> m_actionInvoker;
        Microsoft::WRL::ComPtr<AdaptiveCards::Rendering::Uwp::AdaptiveMediaEventInvoker> m_mediaEventInvoker;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardResourceResolvers> m_resourceResolvers;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_overrideDictionary;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_actionSentimentDefaultDictionary;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<bool>> m_rtl;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::TextStyle>> m_textStyle;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>> m_horizontalAlignment;
    };

    ActivatableClass(AdaptiveRenderContext);
}
