// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveActionParserRegistration.h"
#include "AdaptiveElementParserRegistration.h"
#include "CustomActionWrapper.h"
#include "ObjectModelUtil.h"
#include "Vector.h"
#include "AdaptiveShowCardActionParser.h"
#include "AdaptiveSubmitActionParser.h"
#include "AdaptiveOpenUrlActionParser.h"
#include "AdaptiveToggleVisibilityActionParser.h"
#include "AdaptiveExecuteActionParser.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::UI;

namespace AdaptiveCards::ObjectModel::Uwp
{
    AdaptiveActionParserRegistration::AdaptiveActionParserRegistration() {}

    HRESULT AdaptiveActionParserRegistration::RuntimeClassInitialize() noexcept
    try
    {
        m_registration = std::make_shared<RegistrationMap>();
        m_sharedParserRegistration = std::make_shared<ActionParserRegistration>();

        m_isInitializing = true;
        RegisterDefaultActionParsers(this);

        // Register this (UWP) registration with a well known guid string in the shared model
        // registration so we can get it back again
        m_sharedParserRegistration->AddParser(c_upwActionParserRegistration, std::make_shared<SharedModelActionParser>(this));

        m_isInitializing = false;

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveActionParserRegistration::Set(_In_ HSTRING type, _In_ IAdaptiveActionParser* Parser) noexcept
    try
    {
        std::string typeString = HStringToUTF8(type);

        ComPtr<IAdaptiveActionParser> localParser(Parser);
        (*m_registration)[typeString] = localParser;

        // During initialization we will add the known parsers to m_registration. These are already present in the corresponding
        // shared model registration (m_sharedParserRegistration) which will throw if we attempt to modify them by adding them again.
        if (!m_isInitializing)
        {
            m_sharedParserRegistration->AddParser(typeString, std::make_shared<SharedModelActionParser>(this));
        }

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveActionParserRegistration::Get(_In_ HSTRING type, _COM_Outptr_ IAdaptiveActionParser** result) noexcept
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

    HRESULT AdaptiveActionParserRegistration::Remove(_In_ HSTRING type) noexcept
    try
    {
        std::string typeString = HStringToUTF8(type);

        m_sharedParserRegistration->RemoveParser(typeString);
        m_registration->erase(typeString);
        return S_OK;
    }
    CATCH_RETURN;

    std::shared_ptr<ActionParserRegistration> AdaptiveActionParserRegistration::GetSharedParserRegistration()
    {
        return m_sharedParserRegistration;
    }

    HRESULT AdaptiveActionParserRegistration::RegisterDefaultActionParsers(ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParserRegistration* registration)
    {
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Action.OpenUrl").Get(),
                                           Make<AdaptiveCards::ObjectModel::Uwp::AdaptiveOpenUrlActionParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Action.ShowCard").Get(),
                                           Make<AdaptiveCards::ObjectModel::Uwp::AdaptiveShowCardActionParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Action.Submit").Get(),
                                           Make<AdaptiveCards::ObjectModel::Uwp::AdaptiveSubmitActionParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Action.ToggleVisibility").Get(),
                                           Make<AdaptiveCards::ObjectModel::Uwp::AdaptiveToggleVisibilityActionParser>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Action.Execute").Get(),
                                           Make<AdaptiveCards::ObjectModel::Uwp::AdaptiveExecuteActionParser>().Get()));
        return S_OK;
    }

    SharedModelActionParser::SharedModelActionParser(AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration* parserRegistration)
    {
        ComPtr<AdaptiveActionParserRegistration> localParserRegistration(parserRegistration);
        localParserRegistration.AsWeak(&m_parserRegistration);
    }

    std::shared_ptr<BaseActionElement> SharedModelActionParser::Deserialize(ParseContext& context, const Json::Value& value)
    {
        std::string type = ParseUtil::GetTypeAsString(value);

        HString typeAsHstring;
        THROW_IF_FAILED(UTF8ToHString(type, typeAsHstring.GetAddressOf()));

        ComPtr<IAdaptiveActionParserRegistration> adaptiveActionParserRegistration;
        THROW_IF_FAILED(GetAdaptiveParserRegistration(&adaptiveActionParserRegistration));

        ComPtr<IAdaptiveActionParser> parser;
        THROW_IF_FAILED(adaptiveActionParserRegistration->Get(typeAsHstring.Get(), &parser));

        ComPtr<ABI::Windows::Data::Json::IJsonObject> jsonObject;
        THROW_IF_FAILED(JsonCppToJsonObject(value, &jsonObject));

        // Get the element parser registration from the shared model
        ComPtr<IAdaptiveElementParserRegistration> adaptiveElementParserRegistration;
        THROW_IF_FAILED(GetAdaptiveElementParserRegistrationFromSharedModel(context.elementParserRegistration,
                                                                            &adaptiveElementParserRegistration));

        ComPtr<IAdaptiveActionElement> actionElement;
        ComPtr<ABI::Windows::Foundation::Collections::IVector<AdaptiveWarning*>> adaptiveWarnings =
            Make<Vector<AdaptiveWarning*>>();
        THROW_IF_FAILED(parser->FromJson(jsonObject.Get(),
                                         adaptiveElementParserRegistration.Get(),
                                         adaptiveActionParserRegistration.Get(),
                                         adaptiveWarnings.Get(),
                                         &actionElement));

        THROW_IF_FAILED(AdaptiveWarningsToSharedWarnings(adaptiveWarnings.Get(), context.warnings));

        std::shared_ptr<CustomActionWrapper> actionWrapper = std::make_shared<CustomActionWrapper>(actionElement.Get());
        return actionWrapper;
    }

    std::shared_ptr<BaseActionElement> SharedModelActionParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
    {
        return Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
    }

    HRESULT SharedModelActionParser::GetAdaptiveParserRegistration(_COM_Outptr_ IAdaptiveActionParserRegistration** actionParserRegistration)
    {
        return m_parserRegistration.CopyTo<IAdaptiveActionParserRegistration>(actionParserRegistration);
    }
}
