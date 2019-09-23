// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveActionParserRegistration.h"
#include "AdaptiveActionSetRenderer.h"
#include "AdaptiveChoiceSetInputRenderer.h"
#include "AdaptiveColumnRenderer.h"
#include "AdaptiveColumnSetRenderer.h"
#include "AdaptiveContainerRenderer.h"
#include "AdaptiveDateInputRenderer.h"
#include "AdaptiveElementRendererRegistration.h"
#include "AdaptiveFactSetRenderer.h"
#include "AdaptiveHostConfig.h"
#include "AdaptiveImageRenderer.h"
#include "AdaptiveImageSetRenderer.h"
#include "AdaptiveMediaRenderer.h"
#include "AdaptiveNumberInputRenderer.h"
#include "AdaptiveRenderContext.h"
#include "AdaptiveRichTextBlockRenderer.h"
#include "AdaptiveTextBlockRenderer.h"
#include "AdaptiveTextInputRenderer.h"
#include "AdaptiveTimeInputRenderer.h"
#include "AdaptiveToggleInputRenderer.h"
#include "CustomElementWrapper.h"
#include "Util.h"
#include "Vector.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::UI;

namespace AdaptiveNamespace
{
    AdaptiveElementParserRegistration::AdaptiveElementParserRegistration() {}

    HRESULT AdaptiveElementParserRegistration::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<ElementParserRegistration> sharedParserRegistration = std::make_shared<ElementParserRegistration>();
        RuntimeClassInitialize(sharedParserRegistration);
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveElementParserRegistration::RuntimeClassInitialize(
        std::shared_ptr<AdaptiveSharedNamespace::ElementParserRegistration> sharedParserRegistration) noexcept try
    {
        m_registration = std::make_shared<RegistrationMap>();
        m_sharedParserRegistration = sharedParserRegistration;

        m_isInitializing = true;
        RegisterDefaultElementRenderers(this, nullptr);
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

    std::shared_ptr<BaseCardElement> SharedModelElementParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
    {
        return Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
    }

    std::shared_ptr<BaseCardElement> SharedModelElementParser::Deserialize(ParseContext& context, const Json::Value& value)
    {
        std::string type = ParseUtil::GetTypeAsString(value);

        HString typeAsHstring;
        THROW_IF_FAILED(UTF8ToHString(type, typeAsHstring.GetAddressOf()));

        ComPtr<IAdaptiveElementParser> parser;
        THROW_IF_FAILED(m_parserRegistration->Get(typeAsHstring.Get(), &parser));

        ComPtr<ABI::Windows::Data::Json::IJsonObject> jsonObject;
        THROW_IF_FAILED(JsonCppToJsonObject(value, &jsonObject));

        ComPtr<IAdaptiveElementParserRegistration> adaptiveElementParserRegistration;
        MakeAndInitialize<AdaptiveNamespace::AdaptiveElementParserRegistration>(&adaptiveElementParserRegistration,
                                                                                context.elementParserRegistration);

        ComPtr<IAdaptiveActionParserRegistration> adaptiveActionParserRegistration;
        MakeAndInitialize<AdaptiveNamespace::AdaptiveActionParserRegistration>(&adaptiveActionParserRegistration,
                                                                               context.actionParserRegistration);

        ComPtr<IAdaptiveCardElement> cardElement;
        ComPtr<ABI::Windows::Foundation::Collections::IVector<AdaptiveWarning*>> adaptiveWarnings =
            Make<Vector<AdaptiveWarning*>>();
        THROW_IF_FAILED(parser->FromJson(jsonObject.Get(),
                                         adaptiveElementParserRegistration.Get(),
                                         adaptiveActionParserRegistration.Get(),
                                         adaptiveWarnings.Get(),
                                         &cardElement));

        THROW_IF_FAILED(AdaptiveWarningsToSharedWarnings(adaptiveWarnings.Get(), context.warnings));

        std::shared_ptr<CustomElementWrapper> elementWrapper = std::make_shared<CustomElementWrapper>(cardElement.Get());
        return elementWrapper;
    }
}
