// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.WinUI3.h"
#include "RenderedAdaptiveCard.h"
#include "AdaptiveActionInvoker.h"
#include "AdaptiveMediaEventInvoker.h"
#include "AdaptiveRenderContext.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    class DECLSPEC_UUID("F29649FF-C718-4F94-8F39-2415C86BE77E") AdaptiveRenderContext : AdaptiveRenderContextT < AdaptiveRenderContext, ITypePeek>
    {
        AdaptiveRenderContext() noexcept;

        AdaptiveRenderContext(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* hostConfig,
                                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFeatureRegistration* featureRegistration,
                                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveElementRendererRegistration* elementRendererRegistration,
                                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveActionRendererRegistration* actionRendererRegistration,
                                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveCardResourceResolvers* resourceResolvers,
                                       _In_ ABI::Windows::UI::Xaml::IResourceDictionary* overrideStyles,
                                       _In_ ABI::Windows::UI::Xaml::IResourceDictionary* defaultActionSentimentStyles,
                                       _In_ AdaptiveCards::Rendering::WinUI3::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP get_HostConfig(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig** value) override;
        IFACEMETHODIMP get_FeatureRegistration(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFeatureRegistration** value) override;
        IFACEMETHODIMP get_ElementRenderers(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveElementRendererRegistration** value) override;
        IFACEMETHODIMP get_ActionRenderers(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveActionRendererRegistration** value) override;
        IFACEMETHODIMP get_ActionInvoker(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveActionInvoker** value) override;
        IFACEMETHODIMP get_MediaEventInvoker(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveMediaEventInvoker** value) override;
        IFACEMETHODIMP get_UserInputs(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputs** value) override;
        IFACEMETHODIMP AddInputValue(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputValue* inputValue,
                                     _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs) override;
        IFACEMETHODIMP LinkSubmitActionToCard(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* submitAction,
                                              _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs) override;
        IFACEMETHODIMP LinkCardToParent(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* card,
                                        _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs) override;

        IFACEMETHODIMP GetInputValue(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveInputElement* inputElement,
                                     _COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputValue** inputValue) override;

        IFACEMETHODIMP get_Rtl(_COM_Outptr_ ABI::Windows::Foundation::IReference<bool>** value) override;
        IFACEMETHODIMP put_Rtl(_In_ ABI::Windows::Foundation::IReference<bool>* value) override;

        IFACEMETHODIMP get_TextStyle(_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextStyle>** value) override;
        IFACEMETHODIMP put_TextStyle(_In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextStyle>* value) override;

        IFACEMETHODIMP get_HorizontalContentAlignment(
            _Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::HAlignment>** value) override;
        IFACEMETHODIMP put_HorizontalContentAlignment(
            _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::HAlignment>* value) override;

        IFACEMETHODIMP get_ResourceResolvers(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveCardResourceResolvers** value) override;
        IFACEMETHODIMP get_OverrideStyles(_COM_Outptr_ ABI::Windows::UI::Xaml::IResourceDictionary** overrideDictionary) override;
        IFACEMETHODIMP AddError(ABI::AdaptiveCards::ObjectModel::WinUI3::ErrorStatusCode statusCode, _In_ HSTRING message) override;
        IFACEMETHODIMP AddWarning(ABI::AdaptiveCards::ObjectModel::WinUI3::WarningStatusCode statusCode, _In_ HSTRING message) override;

        HRESULT AddInlineShowCard(_In_opt_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionSet* actionSet,
                                  _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveShowCardAction* showCardAction,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionButtonUIElement,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionOverflowUIElement,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* showCardUIElement,
                                  UINT32 primaryButtonIndex,
                                  _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs);

        HRESULT AddInlineShowCard(_In_opt_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* adaptiveCard,
                                  _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveShowCardAction* showCardAction,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionButtonUIElement,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionOverflowUIElement,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* showCardUIElement,
                                  UINT32 primaryButtonIndex,
                                  _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs);

        HRESULT AddOverflowButton(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionSet* actionSet,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionUIElement);

        HRESULT AddOverflowButton(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* actionCard,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionUIElement);

        HRESULT GetRenderResult(_COM_Outptr_ AdaptiveCards::Rendering::WinUI3::RenderedAdaptiveCard** renderResult);
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> GetDefaultActionSentimentDictionary();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFeatureRegistration> m_featureRegistration;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveElementRendererRegistration> m_elementRendererRegistration;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveActionRendererRegistration> m_actionRendererRegistration;
        Microsoft::WRL::WeakRef m_weakRenderResult;
        winrt::com_ptr<winrt::AdaptiveCards::Rendering::WinUI3::implementation::AdaptiveActionInvoker> m_actionInvoker;
        Microsoft::WRL::ComPtr<AdaptiveCards::Rendering::WinUI3::AdaptiveMediaEventInvoker> m_mediaEventInvoker;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveCardResourceResolvers> m_resourceResolvers;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_overrideDictionary;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_actionSentimentDefaultDictionary;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<bool>> m_rtl;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextStyle>> m_textStyle;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::HAlignment>> m_horizontalAlignment;
    };

    ActivatableClass(AdaptiveRenderContext);
}
