// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveActionParserRegistration.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("fc95029a-9ec0-4d93-b170-09c99876db20") AdaptiveActionParserRegistration
        : AdaptiveActionParserRegistrationT<AdaptiveActionParserRegistration, ITypePeek>
    {
        using RegistrationMap =
            std::unordered_map<std::string, winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParser, ::AdaptiveCards::CaseInsensitiveHash, ::AdaptiveCards::CaseInsensitiveEqualTo>;

    public:
        AdaptiveActionParserRegistration();

        void Set(hstring const& type, winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParser const& Parser);
        winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParser Get(hstring const& type);
        void Remove(hstring const& type);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        std::shared_ptr<::AdaptiveCards::ActionParserRegistration> GetSharedParserRegistration();

    private:
        void RegisterDefaultActionParsers();

        bool m_isInitializing{true};
        std::shared_ptr<RegistrationMap> m_registration{std::make_shared<RegistrationMap>()};
        std::shared_ptr<::AdaptiveCards::ActionParserRegistration> m_sharedParserRegistration{
            std::make_shared<::AdaptiveCards::ActionParserRegistration>()};
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveActionParserRegistration
        : AdaptiveActionParserRegistrationT<AdaptiveActionParserRegistration, implementation::AdaptiveActionParserRegistration>
    {
    };
}

namespace AdaptiveCards::ObjectModel::Uwp
{
    constexpr char* c_upwActionParserRegistration = "AB3CC8B0-FF27-4859-A2AA-BCE2E729805";

    class SharedModelActionParser : public AdaptiveCards::ActionElementParser
    {
    public:
        SharedModelActionParser(_In_ winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration const& parserRegistration);

        // AdaptiveCards::ActionElementParser
        std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& value) override;
        std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;

        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration GetAdaptiveParserRegistration();

    private:
        // This a a weak reference to the UWP level AdaptiveActionParserRegistration for this parse. Store as a weak
        // reference to avoid circular references:
        //
        // SharedModelActionParser(This Object)->
        //      m_parserRegistration(AdaptiveActionParserRegistration)->
        //          m_sharedParserRegistration(ActionParserRegistration)->
        //              m_cardElementParsers (Contains this object)
        winrt::weak_ref<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration> m_parserRegistration;
    };
}
