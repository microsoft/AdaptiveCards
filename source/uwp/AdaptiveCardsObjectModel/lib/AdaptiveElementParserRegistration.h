// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.ObjectModel.Uwp.h"
#include "ObjectModelUtil.h"
#include "AdaptiveActionParserRegistration.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    constexpr char* c_uwpElementParserRegistration = "447C3D76-CAAD-405F-B929-E3201F1537AB";

    class DECLSPEC_UUID("fdf8457d-639f-4bbd-9e32-26c14bac3813") AdaptiveElementParserRegistration
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParserRegistration>,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntime(AdaptiveElementParserRegistration);

        typedef std::unordered_map<std::string, Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParser>, CaseInsensitiveHash, CaseInsensitiveEqualTo> RegistrationMap;

    public:
        AdaptiveElementParserRegistration();
        HRESULT RuntimeClassInitialize() noexcept;

        // IAdaptiveElementParserRegistration
        IFACEMETHODIMP Set(_In_ HSTRING type, _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParser* Parser) noexcept;
        IFACEMETHODIMP Get(_In_ HSTRING type, _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParser** result) noexcept;
        IFACEMETHODIMP Remove(_In_ HSTRING type) noexcept;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        std::shared_ptr<ElementParserRegistration> GetSharedParserRegistration();

    private:
        HRESULT RegisterDefaultElementParsers(ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParserRegistration* registration);

        bool m_isInitializing;
        std::shared_ptr<RegistrationMap> m_registration;
        std::shared_ptr<ElementParserRegistration> m_sharedParserRegistration;
    };

    ActivatableClass(AdaptiveElementParserRegistration);

    class SharedModelElementParser : public AdaptiveCards::BaseCardElementParser
    {
    public:
        SharedModelElementParser(_In_ AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration* parserRegistration);

        // AdaptiveCards::BaseCardElementParser
        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& value) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;

        HRESULT GetAdaptiveParserRegistration(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParserRegistration** elementParserRegistration);

    private:
        // This a a weak reference to the UWP level AdaptiveElementParserRegistration for this parse. Store as a weak
        // reference to avoid circular references:
        //
        // SharedModelElementParser(This Object)->
        //      m_parserRegistration(AdaptiveElementParserRegistration)->
        //          m_sharedParserRegistration(ElementParserRegistration)->
        //              m_cardElementParsers (Contains this object)
        Microsoft::WRL::WeakRef m_parserRegistration;
    };

    template<typename TAdaptiveCardElement, typename TSharedModelElement, typename TSharedModelParser, typename TAdaptiveElementInterface>
    HRESULT FromJson(_In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
                     _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParserRegistration* elementParserRegistration,
                     _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParserRegistration* actionParserRegistration,
                     _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning*>* adaptiveWarnings,
                     _COM_Outptr_ TAdaptiveElementInterface** element)
    {
        std::string jsonString;
        JsonObjectToString(jsonObject, jsonString);

        ComPtr<AdaptiveElementParserRegistration> elementParserRegistrationImpl =
            PeekInnards<AdaptiveElementParserRegistration>(elementParserRegistration);

        ComPtr<AdaptiveActionParserRegistration> actionParserRegistrationImpl =
            PeekInnards<AdaptiveActionParserRegistration>(actionParserRegistration);

        ParseContext context(elementParserRegistrationImpl->GetSharedParserRegistration(),
                             actionParserRegistrationImpl->GetSharedParserRegistration());

        std::vector<std::shared_ptr<AdaptiveCardParseWarning>> warnings;
        std::shared_ptr<TSharedModelParser> parser = std::make_shared<TSharedModelParser>();
        auto baseCardElement = parser->DeserializeFromString(context, jsonString);

        RETURN_IF_FAILED(SharedWarningsToAdaptiveWarnings(context.warnings, adaptiveWarnings));

        THROW_IF_FAILED(MakeAndInitialize<TAdaptiveCardElement>(element, std::AdaptivePointerCast<TSharedModelElement>(baseCardElement)));

        return S_OK;
    }
}
