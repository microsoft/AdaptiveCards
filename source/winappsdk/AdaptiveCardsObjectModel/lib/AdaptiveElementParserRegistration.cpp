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

namespace AdaptiveCards::ObjectModel::WinUI3
{
    AdaptiveElementParserRegistration::AdaptiveElementParserRegistration() {}

    HRESULT AdaptiveElementParserRegistration::RuntimeClassInitialize() noexcept
    try
    {
        m_registration = std::make_shared<RegistrationMap>();
        m_sharedParserRegistration = std::make_shared<ElementParserRegistration>();

        m_isInitializing = true;
        RegisterDefaultElementParsers(this);

        // Register this (UWP) registration with a well known guid string in the shared model
        // registration so we can get it back again
        m_sharedParserRegistration->AddParser(c_uwpElementParserRegistration, std::make_shared<SharedModelElementParser>(this));

        m_isInitializing = false;
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveElementParserRegistration::Set(_In_ HSTRING type, _In_ IAdaptiveElementParser* Parser) noexcept
    try
    {
        std::string typeString = HStringToUTF8(type);

        // During initialization we will add the known parsers to m_registration. These are already present in the corresponding
        // shared model registration (m_sharedParserRegistration) which will throw if we attempt to modify them by adding them again.
        if (!m_isInitializing)
        {
            m_sharedParserRegistration->AddParser(typeString, std::make_shared<SharedModelElementParser>(this));
        }

        ComPtr<IAdaptiveElementParser> localParser(Parser);
        (*m_registration)[typeString] = localParser;

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveElementParserRegistration::Get(_In_ HSTRING type, _COM_Outptr_ IAdaptiveElementParser** result) noexcept
    try
    {
        *result = nullptr;

        RegistrationMap::iterator found = m_registration->find(HStringToUTF8(type));
        if (found != m_registration->end())
        {
            RETURN_IF_FAILED(found->second.CopyTo(result));
        }
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveElementParserRegistration::Remove(_In_ HSTRING type) noexcept
    try
    {
        std::string typeString = HStringToUTF8(type);

        m_sharedParserRegistration->RemoveParser(typeString);
        m_registration->erase(typeString);

        return S_OK;
    }
    CATCH_RETURN;

    std::shared_ptr<ElementParserRegistration> AdaptiveElementParserRegistration::GetSharedParserRegistration()
    {
        return m_sharedParserRegistration;
    }

    HRESULT AdaptiveElementParserRegistration::RegisterDefaultElementParsers(ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementParserRegistration* registration)
    {
        RETURN_IF_FAILED(registration->Set(HStringReference(L"ActionSet").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionSetParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Column").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveColumnParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"ColumnSet").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveColumnSetParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Container").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveContainerParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"FactSet").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveFactSetParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Image").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveImageParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"ImageSet").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveImageSetParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.ChoiceSet").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveChoiceSetInputParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Date").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveDateInputParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Number").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveNumberInputParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Text").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveTextInputParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Time").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveTimeInputParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Toggle").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveToggleInputParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Media").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveMediaParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"RichTextBlock").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveRichTextBlockParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Table").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveTableParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"TextBlock").Get(),
                                           Make<AdaptiveCards::ObjectModel::WinUI3::AdaptiveTextBlockParser>().Get()));

        return S_OK;
    }

    std::shared_ptr<BaseCardElement> SharedModelElementParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
    {
        return Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
    }

    SharedModelElementParser::SharedModelElementParser(AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration* parserRegistration)
    {
        m_parserRegistration = winrt::make_weak(
            copy_from_abi<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration>(parserRegistration));
    }

    std::shared_ptr<BaseCardElement> SharedModelElementParser::Deserialize(ParseContext& context, const Json::Value& value)
    {
        std::string type = ParseUtil::GetTypeAsString(value);

        auto adaptiveElementParserRegistration = GetAdaptiveParserRegistration();
        auto parser = adaptiveElementParserRegistration.Get(UTF8ToHString(type));
        auto jsonObject = JsonCppToJsonObject(value);

        // Get the action parser registration from the shared model
        auto adaptiveActionParserRegistration = GetAdaptiveActionParserRegistrationFromSharedModel(context.actionParserRegistration);
        auto adaptiveWarnings = winrt::single_threaded_vector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning>();

        auto cardElement =
            parser.FromJson(jsonObject, adaptiveElementParserRegistration, adaptiveActionParserRegistration, adaptiveWarnings);

        AdaptiveWarningsToSharedWarnings(adaptiveWarnings, context.warnings);

        return std::make_shared<CustomElementWrapper>(cardElement);
    }

    winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration SharedModelElementParser::GetAdaptiveParserRegistration()
    {
        return m_parserRegistration.get();
    }
}
