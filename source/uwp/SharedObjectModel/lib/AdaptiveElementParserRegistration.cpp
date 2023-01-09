// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveActionParserRegistration.h"
#include "AdaptiveActionSetParser.h"
#include "AdaptiveChoiceSetInputParser.h"
#include "AdaptiveColumnParser.h"
#include "AdaptiveColumnSetParser.h"
#include "AdaptiveContainerParser.h"
#include "AdaptiveDateInputParser.h"
#include "AdaptiveFactSetParser.h"
#include "AdaptiveImageParser.h"
#include "AdaptiveImageSetParser.h"
#include "AdaptiveMediaParser.h"
#include "AdaptiveNumberInputParser.h"
#include "AdaptiveRichTextBlockParser.h"
#include "AdaptiveTableParser.h"
#include "AdaptiveTextBlockParser.h"
#include "AdaptiveTextInputParser.h"
#include "AdaptiveTimeInputParser.h"
#include "AdaptiveToggleInputParser.h"
#include "CustomElementWrapper.h"
#include "AdaptiveElementParserRegistration.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveElementParserRegistration::AdaptiveElementParserRegistration()
    {
        RegisterDefaultElementParsers();

        // Register this (UWP) registration with a well known guid string in the shared model
        // registration so we can get it back again
        m_sharedParserRegistration->AddParser(::AdaptiveCards::ObjectModel::Uwp::c_uwpElementParserRegistration,
                                              std::make_shared<::AdaptiveCards::ObjectModel::Uwp::SharedModelElementParser>(*this));

        m_isInitializing = false;
    }

    void AdaptiveElementParserRegistration::Set(hstring const& type,
                                                winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParser const& Parser)
    {
        auto typeString = HStringToUTF8(type);

        // During initialization we will add the known parsers to m_registration. These are already present in the corresponding
        // shared model registration (m_sharedParserRegistration) which will throw if we attempt to modify them by adding them again.
        if (!m_isInitializing)
        {
            m_sharedParserRegistration->AddParser(
                typeString, std::make_shared<::AdaptiveCards::ObjectModel::Uwp::SharedModelElementParser>(*this));
        }

        (*m_registration)[typeString] = Parser;
    }

    winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParser AdaptiveElementParserRegistration::Get(hstring const& type)
    {
        auto found = m_registration->find(HStringToUTF8(type));
        if (found != m_registration->end())
        {
            return found->second;
        }
        return nullptr;
    }

    void AdaptiveElementParserRegistration::Remove(hstring const& type)
    {
        std::string typeString = HStringToUTF8(type);

        m_sharedParserRegistration->RemoveParser(typeString);
        m_registration->erase(typeString);
    }

    std::shared_ptr<::AdaptiveCards::ElementParserRegistration> AdaptiveElementParserRegistration::GetSharedParserRegistration()
    {
        return m_sharedParserRegistration;
    }

    void AdaptiveElementParserRegistration::RegisterDefaultElementParsers()
    {
        Set(L"ActionSet", winrt::make<implementation::AdaptiveActionSetParser>());
        Set(L"Column", winrt::make<implementation::AdaptiveColumnParser>());
        Set(L"ColumnSet", winrt::make<implementation::AdaptiveColumnSetParser>());
        Set(L"Container", winrt::make<implementation::AdaptiveContainerParser>());
        Set(L"FactSet", winrt::make<implementation::AdaptiveFactSetParser>());
        Set(L"Image", winrt::make<implementation::AdaptiveImageParser>());
        Set(L"ImageSet", winrt::make<implementation::AdaptiveImageSetParser>());
        Set(L"Input.ChoiceSet", winrt::make<implementation::AdaptiveChoiceSetInputParser>());
        Set(L"Input.Date", winrt::make<implementation::AdaptiveDateInputParser>());
        Set(L"Input.Number", winrt::make<implementation::AdaptiveNumberInputParser>());
        Set(L"Input.Text", winrt::make<implementation::AdaptiveTextInputParser>());
        Set(L"Input.Time", winrt::make<implementation::AdaptiveTimeInputParser>());
        Set(L"Input.Toggle", winrt::make<implementation::AdaptiveToggleInputParser>());
        Set(L"Media", winrt::make<implementation::AdaptiveMediaParser>());
        Set(L"RichTextBlock", winrt::make<implementation::AdaptiveRichTextBlockParser>());
        Set(L"Table", winrt::make<implementation::AdaptiveTableParser>());
        Set(L"TextBlock", winrt::make<implementation::AdaptiveTextBlockParser>());
    }
}

namespace AdaptiveCards::ObjectModel::Uwp
{
    std::shared_ptr<::AdaptiveCards::BaseCardElement>
    SharedModelElementParser::DeserializeFromString(::AdaptiveCards::ParseContext& context, const std::string& jsonString)
    {
        return Deserialize(context, ::AdaptiveCards::ParseUtil::GetJsonValueFromString(jsonString));
    }

    SharedModelElementParser::SharedModelElementParser(winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration const& parserRegistration)
    {
        m_parserRegistration = winrt::make_weak(parserRegistration);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> SharedModelElementParser::Deserialize(::AdaptiveCards::ParseContext& context,
                                                                                            const Json::Value& value)
    {
        std::string type = ::AdaptiveCards::ParseUtil::GetTypeAsString(value);

        auto adaptiveElementParserRegistration = GetAdaptiveParserRegistration();
        auto parser = adaptiveElementParserRegistration.Get(UTF8ToHString(type));
        auto jsonObject = JsonCppToJsonObject(value);

        // Get the action parser registration from the shared model
        auto adaptiveActionParserRegistration = GetAdaptiveActionParserRegistrationFromSharedModel(context.actionParserRegistration);
        auto adaptiveWarnings = winrt::single_threaded_vector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning>();

        auto cardElement =
            parser.FromJson(jsonObject, adaptiveElementParserRegistration, adaptiveActionParserRegistration, adaptiveWarnings);

        AdaptiveWarningsToSharedWarnings(adaptiveWarnings, context.warnings);

        return std::make_shared<::AdaptiveCards::ObjectModel::Uwp::CustomElementWrapper>(cardElement);
    }

    winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration SharedModelElementParser::GetAdaptiveParserRegistration()
    {
        return m_parserRegistration.get();
    }
}
