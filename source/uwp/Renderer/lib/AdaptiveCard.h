#pragma once

#include "AdaptiveCards.Uwp.h"
#include "SharedAdaptiveCard.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveCard :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
            ABI::AdaptiveCards::Uwp::IAdaptiveCard>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveCard, BaseTrust)

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

        IFACEMETHODIMP get_BackgroundImage(_Out_ ABI::Windows::Foundation::IUriRuntimeClass** url);
        IFACEMETHODIMP put_BackgroundImage(_In_ ABI::Windows::Foundation::IUriRuntimeClass* url);

        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveCards::Uwp::ContainerStyle* style);
        IFACEMETHODIMP put_Style(_In_ ABI::AdaptiveCards::Uwp::ContainerStyle style);

        IFACEMETHODIMP get_Speak(_Out_ HSTRING* speak);
        IFACEMETHODIMP put_Speak(_In_ HSTRING speak);

        IFACEMETHODIMP get_Body(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveCardElement*>** body);

        IFACEMETHODIMP get_Actions(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveActionElement*>** actions);

        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::Uwp::ElementType* elementType);

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveCardElement*>> m_body;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveActionElement*>> m_actions;

        std::shared_ptr<::AdaptiveCards::AdaptiveCard> m_sharedAdaptiveCard;
    };

    class AdaptiveCardStaticsImpl WrlFinal
        : public Microsoft::WRL::AgileActivationFactory<
        ABI::AdaptiveCards::Uwp::IAdaptiveCardStatics>
    {
        InspectableClassStatic(RuntimeClass_AdaptiveCards_Uwp_AdaptiveCard, TrustLevel::BaseTrust);

    public:
        IFACEMETHOD(ActivateInstance)(_COM_Outptr_ IInspectable** ppvObject) noexcept override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveCard>(ppvObject);
        }

        // IAdaptiveCardStatics
        IFACEMETHODIMP FromJson(
            _In_ ABI::Windows::Data::Json::IJsonObject* adaptiveJson, 
            _COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveCardParseResult** parseResult) noexcept;

        IFACEMETHODIMP FromJsonWithParserRegistration(
            _In_ ABI::Windows::Data::Json::IJsonObject* adaptiveJson, 
            ABI::AdaptiveCards::Uwp::IAdaptiveElementParserRegistration* elementParserRegistration,
            ABI::AdaptiveCards::Uwp::IAdaptiveActionParserRegistration* actionParserRegistration,
            _COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveCardParseResult** parseResult) noexcept;

        IFACEMETHODIMP FromJsonString(
            _In_ HSTRING adaptiveJson, 
            _COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveCardParseResult** parseResult) noexcept;

        IFACEMETHODIMP FromJsonStringWithParserRegistration(
            _In_ HSTRING adaptiveJson,
            ABI::AdaptiveCards::Uwp::IAdaptiveElementParserRegistration* elementParserRegistration,
            ABI::AdaptiveCards::Uwp::IAdaptiveActionParserRegistration* actionParserRegistration,
            _COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveCardParseResult** parseResult) noexcept;

    private:
        HRESULT FromJsonString(
            _In_ const std::string jsonString, 
            ABI::AdaptiveCards::Uwp::IAdaptiveElementParserRegistration* elementParserRegistration,
            ABI::AdaptiveCards::Uwp::IAdaptiveActionParserRegistration* actionParserRegistration,
            _COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveCardParseResult** parseResult);
    };

    ActivatableClassWithFactory(AdaptiveCard, AdaptiveCardStaticsImpl);
}}