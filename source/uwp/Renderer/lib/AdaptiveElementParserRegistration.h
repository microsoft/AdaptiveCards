#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Util.h"
#include "AdaptiveActionParserRegistration.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("fdf8457d-639f-4bbd-9e32-26c14bac3813") AdaptiveElementParserRegistration
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration>,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntime(AdaptiveElementParserRegistration);

        typedef std::unordered_map<std::string, Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveElementParser>, CaseInsensitiveHash, CaseInsensitiveEqualTo> RegistrationMap;

    public:
        AdaptiveElementParserRegistration();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(std::shared_ptr<AdaptiveSharedNamespace::ElementParserRegistration> sharedParserRegistration) noexcept;

        // IAdaptiveElementParserRegistration
        IFACEMETHODIMP Set(_In_ HSTRING type, _In_ ABI::AdaptiveNamespace::IAdaptiveElementParser* Parser);
        IFACEMETHODIMP Get(_In_ HSTRING type, _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveElementParser** result);
        IFACEMETHODIMP Remove(_In_ HSTRING type);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        std::shared_ptr<ElementParserRegistration> GetSharedParserRegistration();

    private:
        std::shared_ptr<RegistrationMap> m_registration;
        std::shared_ptr<ElementParserRegistration> m_sharedParserRegistration;
    };

    ActivatableClass(AdaptiveElementParserRegistration);

    class SharedModelElementParser : public AdaptiveSharedNamespace::BaseCardElementParser
    {
    public:
        SharedModelElementParser(AdaptiveNamespace::AdaptiveElementParserRegistration* parserRegistration) :
            m_parserRegistration(parserRegistration)
        {
        }

        // IBaseCardElementParser
        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& value) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;

    private:
        Microsoft::WRL::ComPtr<AdaptiveNamespace::AdaptiveElementParserRegistration> m_parserRegistration;
    };

    template<typename TAdaptiveCardElement, typename TSharedModelElement, typename TSharedModelParser>
    HRESULT FromJson(ABI::Windows::Data::Json::IJsonObject* jsonObject,
                     ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
                     ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
                     ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveWarning*>* adaptiveWarnings,
                     ABI::AdaptiveNamespace::IAdaptiveCardElement** element)
    {
        std::string jsonString;
        JsonObjectToString(jsonObject, jsonString);

        std::shared_ptr<AdaptiveSharedNamespace::ElementParserRegistration> sharedModelElementParserRegistration;
        ComPtr<AdaptiveElementParserRegistration> elementParserRegistrationImpl =
            PeekInnards<AdaptiveElementParserRegistration>(elementParserRegistration);
        std::shared_ptr<AdaptiveSharedNamespace::ActionParserRegistration> sharedModelActionParserRegistration;
        ComPtr<AdaptiveActionParserRegistration> actionParserRegistrationImpl =
            PeekInnards<AdaptiveActionParserRegistration>(actionParserRegistration);

        ParseContext context(elementParserRegistrationImpl->GetSharedParserRegistration(),
                             actionParserRegistrationImpl->GetSharedParserRegistration());

        std::vector<std::shared_ptr<AdaptiveCardParseWarning>> warnings;
        std::shared_ptr<TSharedModelParser> parser = std::make_shared<TSharedModelParser>();
        std::shared_ptr<BaseCardElement> baseCardElement = parser->DeserializeFromString(context, jsonString);

        RETURN_IF_FAILED(SharedWarningsToAdaptiveWarnings(context.warnings, adaptiveWarnings));

        THROW_IF_FAILED(MakeAndInitialize<TAdaptiveCardElement>(element, std::AdaptivePointerCast<TSharedModelElement>(baseCardElement)));

        return S_OK;
    }
}
