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
#include "ObjectModelUtil.h"
#include "Vector.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::UI;

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    AdaptiveElementParserRegistration::AdaptiveElementParserRegistration()
    {
        RegisterDefaultElementParsers();

        // Register this (UWP) registration with a well known guid string in the shared model
        // registration so we can get it back again
        m_sharedParserRegistration->AddParser(::AdaptiveCards::ObjectModel::WinUI3::c_uwpElementParserRegistration,
                                              std::make_shared<::AdaptiveCards::ObjectModel::WinUI3::SharedModelElementParser>(*this));

        m_isInitializing = false;
    }

    void AdaptiveElementParserRegistration::Set(hstring const& type,
                                                winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementParser const& Parser)
    {
        auto typeString = HStringToUTF8(type);
        if (!m_isInitializing)
        {
            m_sharedParserRegistration->AddParser(
                typeString, std::make_shared<::AdaptiveCards::ObjectModel::WinUI3::SharedModelElementParser>(*this));
        }

        (*m_registration)[typeString] = Parser;
    }

    winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementParser AdaptiveElementParserRegistration::Get(hstring const& type)
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

    template<typename D> auto MakeParser()
    {
        return MakeOrThrow<D>().as<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementParser>();
    }

    void AdaptiveElementParserRegistration::RegisterDefaultElementParsers()
    {
        Set(L"ActionSet", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionSetParser>());
        Set(L"Column", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveColumnParser>());
        Set(L"ColumnSet", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveColumnSetParser>());
        Set(L"Container", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveContainerParser>());
        Set(L"FactSet", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveFactSetParser>());
        Set(L"Image", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveImageParser>());
        Set(L"ImageSet", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveImageSetParser>());
        Set(L"Input.ChoiceSet", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveChoiceSetInputParser>());
        Set(L"Input.Date", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveDateInputParser>());
        Set(L"Input.Number", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveNumberInputParser>());
        Set(L"Input.Text", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTextInputParser>());
        Set(L"Input.Time", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTimeInputParser>());
        Set(L"Input.Toggle", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveToggleInputParser>());
        Set(L"Media", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveMediaParser>());
        Set(L"RichTextBlock", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveRichTextBlockParser>());
        Set(L"Table", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTableParser>());
        Set(L"TextBlock", MakeParser<::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTextBlockParser>());
    }
}

namespace AdaptiveCards::ObjectModel::WinUI3
{
    std::shared_ptr<::AdaptiveCards::BaseCardElement>
    SharedModelElementParser::DeserializeFromString(::AdaptiveCards::ParseContext& context, const std::string& jsonString)
    {
        return Deserialize(context, ::AdaptiveCards::ParseUtil::GetJsonValueFromString(jsonString));
    }

    SharedModelElementParser::SharedModelElementParser(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration const& parserRegistration)
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
        auto adaptiveWarnings = winrt::single_threaded_vector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning>();

        auto cardElement =
            parser.FromJson(jsonObject, adaptiveElementParserRegistration, adaptiveActionParserRegistration, adaptiveWarnings);

        AdaptiveWarningsToSharedWarnings(adaptiveWarnings, context.warnings);

        return std::make_shared<::AdaptiveCards::ObjectModel::WinUI3::CustomElementWrapper>(cardElement);
    }

    winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration SharedModelElementParser::GetAdaptiveParserRegistration()
    {
        return m_parserRegistration.get();
    }
}
