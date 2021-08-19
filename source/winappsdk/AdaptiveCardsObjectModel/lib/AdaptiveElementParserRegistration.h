// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.ObjectModel.WinUI3.h"
#include "ObjectModelUtil.h"
#include "AdaptiveActionParserRegistration.h"
#include "AdaptiveElementParserRegistration.g.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct DECLSPEC_UUID("fdf8457d-639f-4bbd-9e32-26c14bac3813") AdaptiveElementParserRegistration
        : AdaptiveElementParserRegistrationT<AdaptiveElementParserRegistration, ITypePeek>
    {
        using RegistrationMap =
            std::unordered_map<std::string, winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementParser, ::AdaptiveCards::CaseInsensitiveHash, ::AdaptiveCards::CaseInsensitiveEqualTo>;

        AdaptiveElementParserRegistration();

        void Set(hstring const& type, winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementParser const& Parser);
        winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementParser Get(hstring const& type);
        void Remove(hstring const& type);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        std::shared_ptr<::AdaptiveCards::ElementParserRegistration> GetSharedParserRegistration();

    private:
        void RegisterDefaultElementParsers();

        bool m_isInitializing{true};
        std::shared_ptr<RegistrationMap> m_registration{std::make_shared<RegistrationMap>()};
        std::shared_ptr<::AdaptiveCards::ElementParserRegistration> m_sharedParserRegistration{
            std::make_shared<::AdaptiveCards::ElementParserRegistration>()};
    };
}
namespace winrt::AdaptiveCards::ObjectModel::WinUI3::factory_implementation
{
    struct AdaptiveElementParserRegistration
        : AdaptiveElementParserRegistrationT<AdaptiveElementParserRegistration, implementation::AdaptiveElementParserRegistration>
    {
    };
}

namespace AdaptiveCards::ObjectModel::WinUI3
{
    constexpr char* c_uwpElementParserRegistration = "447C3D76-CAAD-405F-B929-E3201F1537AB";

    class SharedModelElementParser : public ::AdaptiveCards::BaseCardElementParser
    {
    public:
        SharedModelElementParser(_In_ winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration const& parserRegistration);

        // AdaptiveCards::BaseCardElementParser
        std::shared_ptr<::AdaptiveCards::BaseCardElement> Deserialize(::AdaptiveCards::ParseContext& context,
                                                                      const Json::Value& value) override;

        std::shared_ptr<::AdaptiveCards::BaseCardElement> DeserializeFromString(::AdaptiveCards::ParseContext& context,
                                                                                const std::string& jsonString) override;

        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration GetAdaptiveParserRegistration();

    private:
        // This a a weak reference to the UWP level AdaptiveElementParserRegistration for this parse. Store as a weak
        // reference to avoid circular references:
        //
        // SharedModelElementParser(This Object)->
        //      m_parserRegistration(AdaptiveElementParserRegistration)->
        //          m_sharedParserRegistration(ElementParserRegistration)->
        //              m_cardElementParsers (Contains this object)
        winrt::weak_ref<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration> m_parserRegistration;
    };

    template<typename TAdaptiveCardElement, typename TSharedModelElement, typename TSharedModelParser, typename TAdaptiveElementInterface>
    HRESULT FromJson(_In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
                     _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementParserRegistration* elementParserRegistration,
                     _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionParserRegistration* actionParserRegistration,
                     _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning*>* adaptiveWarnings,
                     _COM_Outptr_ TAdaptiveElementInterface** element)
    {
        std::string jsonString;
        JsonObjectToString(jsonObject, jsonString);
        auto elementParserRegistrationImpl = peek_innards<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveElementParserRegistration>(elementParserRegistration);
        auto actionParserRegistrationImpl = peek_innards<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveActionParserRegistration>(actionParserRegistration);

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
