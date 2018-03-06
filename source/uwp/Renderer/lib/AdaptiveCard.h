#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "SharedAdaptiveCard.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class DECLSPEC_UUID("6a88e6d4-373a-48ba-840e-16c4b39278b1") AdaptiveCard :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCard,
            Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveCard, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ std::shared_ptr<::AdaptiveCards::AdaptiveCard> sharedAdaptiveCard);

        // IAdaptiveCard
        IFACEMETHODIMP get_Version(_Out_ HSTRING* version);
        IFACEMETHODIMP put_Version(_In_ HSTRING version);

        IFACEMETHODIMP get_FallbackText(_Out_ HSTRING* fallbackText);
        IFACEMETHODIMP put_FallbackText(_In_ HSTRING fallbackText);

        IFACEMETHODIMP get_BackgroundImage(_Out_ ABI::Windows::Foundation::IUriRuntimeClass** url);
        IFACEMETHODIMP put_BackgroundImage(_In_ ABI::Windows::Foundation::IUriRuntimeClass* url);

        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle* style);
        IFACEMETHODIMP put_Style(_In_ ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle style);

        IFACEMETHODIMP get_Speak(_Out_ HSTRING* speak);
        IFACEMETHODIMP put_Speak(_In_ HSTRING speak);

        IFACEMETHODIMP get_Body(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement*>** body);

        IFACEMETHODIMP get_Actions(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement*>** actions);

        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::Rendering::Uwp::ElementType* elementType);

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT GetSharedModel(_In_ std::shared_ptr<AdaptiveCards::AdaptiveCard>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement*>> m_body;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement*>> m_actions;

        Microsoft::WRL::Wrappers::HString m_version;
        Microsoft::WRL::Wrappers::HString m_minVersion;
        Microsoft::WRL::Wrappers::HString m_fallbackText;
        Microsoft::WRL::Wrappers::HString m_speak;

        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IUriRuntimeClass> m_backgroundImage;
        ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle m_style;
    };

    class AdaptiveCardStaticsImpl WrlFinal
        : public Microsoft::WRL::AgileActivationFactory<
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardStatics>
    {
        InspectableClassStatic(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveCard, TrustLevel::BaseTrust);

    public:
        IFACEMETHOD(ActivateInstance)(_COM_Outptr_ IInspectable** ppvObject) noexcept override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveCard>(ppvObject);
        }

        // IAdaptiveCardStatics
        IFACEMETHODIMP FromJson(
            _In_ ABI::Windows::Data::Json::IJsonObject* adaptiveJson,
            _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardParseResult** parseResult) noexcept;

        IFACEMETHODIMP FromJsonWithParserRegistration(
            _In_ ABI::Windows::Data::Json::IJsonObject* adaptiveJson,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParserRegistration* elementParserRegistration,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionParserRegistration* actionParserRegistration,
            _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardParseResult** parseResult) noexcept;

        IFACEMETHODIMP FromJsonString(
            _In_ HSTRING adaptiveJson,
            _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardParseResult** parseResult) noexcept;

        IFACEMETHODIMP FromJsonStringWithParserRegistration(
            _In_ HSTRING adaptiveJson,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParserRegistration* elementParserRegistration,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionParserRegistration* actionParserRegistration,
            _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardParseResult** parseResult) noexcept;

    private:
        HRESULT FromJsonString(
            _In_ const std::string jsonString,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParserRegistration* elementParserRegistration,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionParserRegistration* actionParserRegistration,
            _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardParseResult** parseResult);
    };

    ActivatableClassWithFactory(AdaptiveCard, AdaptiveCardStaticsImpl);
}}}