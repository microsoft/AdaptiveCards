#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "SharedAdaptiveCard.h"

AdaptiveNamespaceStart
    class DECLSPEC_UUID("6a88e6d4-373a-48ba-840e-16c4b39278b1") AdaptiveCard :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
            ABI::AdaptiveNamespace::IAdaptiveCard,
            Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveCard)

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCard> sharedAdaptiveCard);

        // IAdaptiveCard
        IFACEMETHODIMP get_Version(_Out_ HSTRING* version);
        IFACEMETHODIMP put_Version(_In_ HSTRING version);

        IFACEMETHODIMP get_FallbackText(_Out_ HSTRING* fallbackText);
        IFACEMETHODIMP put_FallbackText(_In_ HSTRING fallbackText);

        IFACEMETHODIMP get_BackgroundImage(_Out_ ABI::Windows::Foundation::IUriRuntimeClass** url);
        IFACEMETHODIMP put_BackgroundImage(_In_ ABI::Windows::Foundation::IUriRuntimeClass* url);

        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveNamespace::ContainerStyle* style);
        IFACEMETHODIMP put_Style(_In_ ABI::AdaptiveNamespace::ContainerStyle style);

        IFACEMETHODIMP get_Speak(_Out_ HSTRING* speak);
        IFACEMETHODIMP put_Speak(_In_ HSTRING speak);

        IFACEMETHODIMP get_Body(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>** body);

        IFACEMETHODIMP get_Actions(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveActionElement*>** actions);

        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveNamespace::ElementType* elementType);

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCard>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>> m_body;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveActionElement*>> m_actions;

        Microsoft::WRL::Wrappers::HString m_version;
        Microsoft::WRL::Wrappers::HString m_minVersion;
        Microsoft::WRL::Wrappers::HString m_fallbackText;
        Microsoft::WRL::Wrappers::HString m_speak;

        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IUriRuntimeClass> m_backgroundImage;
        ABI::AdaptiveNamespace::ContainerStyle m_style;
    };

    class AdaptiveCardStaticsImpl WrlFinal
        : public Microsoft::WRL::AgileActivationFactory<
        ABI::AdaptiveNamespace::IAdaptiveCardStatics>
    {
        AdaptiveRuntimeStatic(AdaptiveCard)

    public:
        IFACEMETHOD(ActivateInstance)(_COM_Outptr_ IInspectable** ppvObject) noexcept override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveCard>(ppvObject);
        }

        // IAdaptiveCardStatics
        IFACEMETHODIMP FromJson(
            _In_ ABI::Windows::Data::Json::IJsonObject* adaptiveJson,
            _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardParseResult** parseResult) noexcept;

        IFACEMETHODIMP FromJsonWithParserRegistration(
            _In_ ABI::Windows::Data::Json::IJsonObject* adaptiveJson,
            ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
            ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
            _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardParseResult** parseResult) noexcept;

        IFACEMETHODIMP FromJsonString(
            _In_ HSTRING adaptiveJson,
            _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardParseResult** parseResult) noexcept;

        IFACEMETHODIMP FromJsonStringWithParserRegistration(
            _In_ HSTRING adaptiveJson,
            ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
            ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
            _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardParseResult** parseResult) noexcept;

    private:
        HRESULT FromJsonString(
            _In_ const std::string jsonString,
            ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
            ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
            _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardParseResult** parseResult);
    };

    ActivatableClassWithFactory(AdaptiveCard, AdaptiveCardStaticsImpl);
AdaptiveNamespaceEnd