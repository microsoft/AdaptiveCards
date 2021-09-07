// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveActionParserRegistration.h"
#include "AdaptiveElementParserRegistration.h"
#include "CustomActionWrapper.h"
#include "AdaptiveShowCardActionParser.h"
#include "AdaptiveSubmitActionParser.h"
#include "AdaptiveOpenUrlActionParser.h"
#include "AdaptiveToggleVisibilityActionParser.h"
#include "AdaptiveExecuteActionParser.h"
#include "windows.ui.xaml.h"
#include "AdaptiveActionParserRegistration.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveActionParserRegistration::AdaptiveActionParserRegistration()
    {
        RegisterDefaultActionParsers();

        // Register this (UWP) registration with a well known guid string in the shared model
        // registration so we can get it back again
        m_sharedParserRegistration->AddParser(::AdaptiveCards::ObjectModel::Uwp::c_upwActionParserRegistration,
                                              std::make_shared<::AdaptiveCards::ObjectModel::Uwp::SharedModelActionParser>(*this));

        m_isInitializing = false;
    }

    void AdaptiveActionParserRegistration::Set(hstring const& type, _In_ Uwp::IAdaptiveActionParser const& Parser)
    {
        std::string typeString = HStringToUTF8(type);
        (*m_registration)[typeString] = Parser;

        // During initialization we will add the known parsers to m_registration. These are already present in the corresponding
        // shared model registration (m_sharedParserRegistration) which will throw if we attempt to modify them by adding them again.
        if (!m_isInitializing)
        {
            m_sharedParserRegistration->AddParser(
                typeString, std::make_shared<::AdaptiveCards::ObjectModel::Uwp::SharedModelActionParser>(*this));
        }
    }

    Uwp::IAdaptiveActionParser AdaptiveActionParserRegistration::Get(hstring const& type)
    {
        auto found = m_registration->find(HStringToUTF8(type));
        if (found != m_registration->end())
        {
            return found->second;
        }
        return nullptr;
    }

    void AdaptiveActionParserRegistration::Remove(hstring const& type)
    {
        std::string typeString = HStringToUTF8(type);

        m_sharedParserRegistration->RemoveParser(typeString);
        m_registration->erase(typeString);
    }

    std::shared_ptr<::AdaptiveCards::ActionParserRegistration> AdaptiveActionParserRegistration::GetSharedParserRegistration()
    {
        return m_sharedParserRegistration;
    }

    template<typename D> auto MakeParser()
    {
        return winrt::make<D>().as<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParser>();
    }

    void AdaptiveActionParserRegistration::RegisterDefaultActionParsers()
    {
        Set(L"Action.OpenUrl", MakeParser<implementation::AdaptiveOpenUrlActionParser>());
        Set(L"Action.ShowCard", MakeParser<implementation::AdaptiveShowCardActionParser>());
        Set(L"Action.Submit", MakeParser<implementation::AdaptiveSubmitActionParser>());
        Set(L"Action.ToggleVisibility", MakeParser<implementation::AdaptiveToggleVisibilityActionParser>());
        Set(L"Action.Execute", MakeParser<implementation::AdaptiveExecuteActionParser>());
    }
}

namespace AdaptiveCards::ObjectModel::Uwp
{
    SharedModelActionParser::SharedModelActionParser(winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration const& parserRegistration)
    {
        m_parserRegistration = winrt::make_weak(parserRegistration);
    }

    std::shared_ptr<BaseActionElement> SharedModelActionParser::Deserialize(ParseContext& context, const Json::Value& value)
    {
        std::string type = ParseUtil::GetTypeAsString(value);

        auto adaptiveActionParserRegistration = GetAdaptiveParserRegistration();
        auto parser = adaptiveActionParserRegistration.Get(UTF8ToHString(type));
        auto jsonObject = JsonCppToJsonObject(value);
        auto adaptiveWarnings = winrt::single_threaded_vector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning>();

        // Get the element parser registration from the shared model
        auto adaptiveElementParserRegistration =
            GetAdaptiveElementParserRegistrationFromSharedModel(context.elementParserRegistration);

        auto actionElement = parser.FromJson(jsonObject, adaptiveElementParserRegistration, adaptiveActionParserRegistration, adaptiveWarnings);

        AdaptiveWarningsToSharedWarnings(adaptiveWarnings, context.warnings);

        return std::make_shared<CustomActionWrapper>(actionElement);
    }

    std::shared_ptr<BaseActionElement> SharedModelActionParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
    {
        return Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
    }

    winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration SharedModelActionParser::GetAdaptiveParserRegistration()
    {
        return m_parserRegistration.get();
    }
}
