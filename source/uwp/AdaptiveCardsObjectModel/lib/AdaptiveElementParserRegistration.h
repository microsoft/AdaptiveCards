// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveActionParserRegistration.h"
#include "AdaptiveElementParserRegistration.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("fdf8457d-639f-4bbd-9e32-26c14bac3813") AdaptiveElementParserRegistration
        : AdaptiveElementParserRegistrationT<AdaptiveElementParserRegistration, ITypePeek>
    {
        using RegistrationMap =
            std::unordered_map<std::string, winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParser, ::AdaptiveCards::CaseInsensitiveHash, ::AdaptiveCards::CaseInsensitiveEqualTo>;

        AdaptiveElementParserRegistration();

        void Set(hstring const& type, winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParser const& Parser);
        winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParser Get(hstring const& type);
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
namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveElementParserRegistration
        : AdaptiveElementParserRegistrationT<AdaptiveElementParserRegistration, implementation::AdaptiveElementParserRegistration>
    {
    };
}

namespace AdaptiveCards::ObjectModel::Uwp
{
    constexpr char* c_uwpElementParserRegistration = "447C3D76-CAAD-405F-B929-E3201F1537AB";

    class SharedModelElementParser : public ::AdaptiveCards::BaseCardElementParser
    {
    public:
        SharedModelElementParser(_In_ winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration const& parserRegistration);

        // AdaptiveCards::BaseCardElementParser
        std::shared_ptr<::AdaptiveCards::BaseCardElement> Deserialize(::AdaptiveCards::ParseContext& context,
                                                                      const Json::Value& value) override;

        std::shared_ptr<::AdaptiveCards::BaseCardElement> DeserializeFromString(::AdaptiveCards::ParseContext& context,
                                                                                const std::string& jsonString) override;

        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration GetAdaptiveParserRegistration();

    private:
        // This a a weak reference to the UWP level AdaptiveElementParserRegistration for this parse. Store as a weak
        // reference to avoid circular references:
        //
        // SharedModelElementParser(This Object)->
        //      m_parserRegistration(AdaptiveElementParserRegistration)->
        //          m_sharedParserRegistration(ElementParserRegistration)->
        //              m_cardElementParsers (Contains this object)
        winrt::weak_ref<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration> m_parserRegistration;
    };

    template<typename TAdaptiveCardElement, typename TSharedModelElement, typename TSharedModelParser>
    auto FromJson(_In_ winrt::Windows::Data::Json::JsonObject const& jsonObject,
                  _In_ winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParserRegistration const& elementParserRegistration,
                  _In_ winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParserRegistration const& actionParserRegistration,
                  _In_ winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning> const& adaptiveWarnings)
    {
        auto elementParserRegistrationImpl =
            peek_innards<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveElementParserRegistration>(
                elementParserRegistration);
        auto actionParserRegistrationImpl =
            peek_innards<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveActionParserRegistration>(actionParserRegistration);

        ParseContext context(elementParserRegistrationImpl->GetSharedParserRegistration(),
                             actionParserRegistrationImpl->GetSharedParserRegistration());

        TSharedModelParser parser;
        auto baseCardElement = parser.DeserializeFromString(context, JsonObjectToString(jsonObject));
        SharedWarningsToAdaptiveWarnings(context.warnings, adaptiveWarnings);
        return winrt::make<TAdaptiveCardElement>(std::AdaptivePointerCast<TSharedModelElement>(baseCardElement));
    }
}
