#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
//TODO: MSFT:11054344 - remove the relative pathing once this is fixed
#include "shared\ObjectModel\AdaptiveCard.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveCardStaticsImpl WrlFinal
        : public Microsoft::WRL::AgileActivationFactory<
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardStatics>
    {
        InspectableClassStatic(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveCard, TrustLevel::BaseTrust);

    public:
        IFACEMETHOD(ActivateInstance)(_COM_Outptr_ IInspectable** /*inspectable*/) noexcept override
        {
            return E_NOTIMPL;
        }

        // IAdaptiveCardStatics
        IFACEMETHODIMP CreateCardFromJson(_In_ HSTRING adaptiveJson, _COM_Outptr_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard** card) noexcept;
    };

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
        IFACEMETHODIMP get_Version(HSTRING *version);
        IFACEMETHODIMP put_Version(HSTRING version);

        IFACEMETHODIMP get_MinVersion(HSTRING *minVersion);
        IFACEMETHODIMP put_MinVersion(HSTRING minVersion);

        IFACEMETHODIMP get_FallbackText(HSTRING *fallbackText);
        IFACEMETHODIMP put_FallbackText(HSTRING fallbackText);

        IFACEMETHODIMP get_Body(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*>** body);

        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*>> m_body;

        std::shared_ptr<::AdaptiveCards::AdaptiveCard> m_sharedAdaptiveCard;
    };

    ActivatableClass(AdaptiveCard);
}}