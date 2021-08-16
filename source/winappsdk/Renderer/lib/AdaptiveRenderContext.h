// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.WinAppSDK.h"
#include "RenderedAdaptiveCard.h"
#include "AdaptiveActionInvoker.h"
#include "AdaptiveMediaEventInvoker.h"

namespace AdaptiveCards::Rendering::WinAppSDK
{
    class DECLSPEC_UUID("F29649FF-C718-4F94-8F39-2415C86BE77E") AdaptiveRenderContext
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<IWeakReferenceSource>,
                                              ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderContext,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveRenderContext);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveHostConfig* hostConfig,
                                       _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFeatureRegistration* featureRegistration,
                                       _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveElementRendererRegistration* elementRendererRegistration,
                                       _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveActionRendererRegistration* actionRendererRegistration,
                                       _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveCardResourceResolvers* resourceResolvers,
                                       _In_ ABI::Windows::UI::Xaml::IResourceDictionary* overrideStyles,
                                       _In_ ABI::Windows::UI::Xaml::IResourceDictionary* defaultActionSentimentStyles,
                                       _In_ AdaptiveCards::Rendering::WinAppSDK::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP get_HostConfig(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveHostConfig** value) override;
        IFACEMETHODIMP get_FeatureRegistration(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFeatureRegistration** value) override;
        IFACEMETHODIMP get_ElementRenderers(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveElementRendererRegistration** value) override;
        IFACEMETHODIMP get_ActionRenderers(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveActionRendererRegistration** value) override;
        IFACEMETHODIMP get_ActionInvoker(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveActionInvoker** value) override;
        IFACEMETHODIMP get_MediaEventInvoker(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveMediaEventInvoker** value) override;
        IFACEMETHODIMP get_UserInputs(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveInputs** value) override;
        IFACEMETHODIMP AddInputValue(_In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveInputValue* inputValue,
                                     _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderArgs* renderArgs) override;
        IFACEMETHODIMP LinkSubmitActionToCard(_In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveActionElement* submitAction,
                                              _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderArgs* renderArgs) override;
        IFACEMETHODIMP LinkCardToParent(_In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveCard* card,
                                        _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderArgs* renderArgs) override;

        IFACEMETHODIMP GetInputValue(_In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveInputElement* inputElement,
                                     _COM_Outptr_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveInputValue** inputValue) override;

        IFACEMETHODIMP get_Rtl(_COM_Outptr_ ABI::Windows::Foundation::IReference<bool>** value) override;
        IFACEMETHODIMP put_Rtl(_In_ ABI::Windows::Foundation::IReference<bool>* value) override;

        IFACEMETHODIMP get_TextStyle(_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinAppSDK::TextStyle>** value) override;
        IFACEMETHODIMP put_TextStyle(_In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinAppSDK::TextStyle>* value) override;

        IFACEMETHODIMP get_HorizontalContentAlignment(
            _Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinAppSDK::HAlignment>** value) override;
        IFACEMETHODIMP put_HorizontalContentAlignment(
            _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinAppSDK::HAlignment>* value) override;

        IFACEMETHODIMP get_ResourceResolvers(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveCardResourceResolvers** value) override;
        IFACEMETHODIMP get_OverrideStyles(_COM_Outptr_ ABI::Windows::UI::Xaml::IResourceDictionary** overrideDictionary) override;
        IFACEMETHODIMP AddError(ABI::AdaptiveCards::ObjectModel::WinAppSDK::ErrorStatusCode statusCode, _In_ HSTRING message) override;
        IFACEMETHODIMP AddWarning(ABI::AdaptiveCards::ObjectModel::WinAppSDK::WarningStatusCode statusCode, _In_ HSTRING message) override;

        HRESULT AddInlineShowCard(_In_opt_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveActionSet* actionSet,
                                  _In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveShowCardAction* showCardAction,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionButtonUIElement,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionOverflowUIElement,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* showCardUIElement,
                                  UINT32 primaryButtonIndex,
                                  _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderArgs* renderArgs);

        HRESULT AddInlineShowCard(_In_opt_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveCard* adaptiveCard,
                                  _In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveShowCardAction* showCardAction,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionButtonUIElement,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionOverflowUIElement,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* showCardUIElement,
                                  UINT32 primaryButtonIndex,
                                  _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderArgs* renderArgs);

        HRESULT AddOverflowButton(_In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveActionSet* actionSet,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionUIElement);

        HRESULT AddOverflowButton(_In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveCard* actionCard,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionUIElement);

        HRESULT GetRenderResult(_COM_Outptr_ AdaptiveCards::Rendering::WinAppSDK::RenderedAdaptiveCard** renderResult);
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> GetDefaultActionSentimentDictionary();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFeatureRegistration> m_featureRegistration;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveElementRendererRegistration> m_elementRendererRegistration;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveActionRendererRegistration> m_actionRendererRegistration;
        Microsoft::WRL::WeakRef m_weakRenderResult;
        Microsoft::WRL::ComPtr<AdaptiveCards::Rendering::WinAppSDK::AdaptiveActionInvoker> m_actionInvoker;
        Microsoft::WRL::ComPtr<AdaptiveCards::Rendering::WinAppSDK::AdaptiveMediaEventInvoker> m_mediaEventInvoker;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveCardResourceResolvers> m_resourceResolvers;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_overrideDictionary;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_actionSentimentDefaultDictionary;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<bool>> m_rtl;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinAppSDK::TextStyle>> m_textStyle;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinAppSDK::HAlignment>> m_horizontalAlignment;
    };

    ActivatableClass(AdaptiveRenderContext);
}
