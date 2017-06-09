#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
//TODO: MSFT:11054344 - remove the relative pathing once this is fixed
#include "shared\cpp\ObjectModel\AdaptiveCard.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveCard :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveCard, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ std::shared_ptr<::AdaptiveCards::AdaptiveCard> sharedAdaptiveCard);

        // IAdaptiveCard
        IFACEMETHODIMP get_Version(_Out_ HSTRING* version);
        IFACEMETHODIMP put_Version(_In_ HSTRING version);

        IFACEMETHODIMP get_MinVersion(_Out_ HSTRING* minVersion);
        IFACEMETHODIMP put_MinVersion(_In_ HSTRING minVersion);

        IFACEMETHODIMP get_FallbackText(_Out_ HSTRING* fallbackText);
        IFACEMETHODIMP put_FallbackText(_In_ HSTRING fallbackText);

        IFACEMETHODIMP get_BackgroundImageUrl(_Out_ ABI::Windows::Foundation::IUriRuntimeClass** url);
        IFACEMETHODIMP put_BackgroundImageUrl(_In_ ABI::Windows::Foundation::IUriRuntimeClass* url);

        IFACEMETHODIMP get_Body(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*>** body);

        IFACEMETHODIMP get_Actions(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*>** actions);

        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*>> m_body;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*>> m_actions;

        std::shared_ptr<::AdaptiveCards::AdaptiveCard> m_sharedAdaptiveCard;
    };

    class AdaptiveCardStaticsImpl WrlFinal
        : public Microsoft::WRL::AgileActivationFactory<
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardStatics>
    {
        InspectableClassStatic(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveCard, TrustLevel::BaseTrust);

    public:
        IFACEMETHOD(ActivateInstance)(_COM_Outptr_ IInspectable** ppvObject) noexcept override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveCard>(ppvObject);
        }

        // IAdaptiveCardStatics
        IFACEMETHODIMP CreateCardFromJson(_In_ HSTRING adaptiveJson, _COM_Outptr_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard** card) noexcept;
    };

    ActivatableClassWithFactory(AdaptiveCard, AdaptiveCardStaticsImpl);
}}