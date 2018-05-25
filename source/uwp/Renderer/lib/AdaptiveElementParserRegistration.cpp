#include "pch.h"
#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveActionParserRegistration.h"
#include "CustomElementWrapper.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::UI;

AdaptiveNamespaceStart
    AdaptiveElementParserRegistration::AdaptiveElementParserRegistration()
    {
    }

    HRESULT AdaptiveElementParserRegistration::RuntimeClassInitialize() noexcept try
    {
        m_registration = std::make_shared<RegistrationMap>();
        m_sharedParserRegistration = std::make_shared<ElementParserRegistration>();

        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveElementParserRegistration::RuntimeClassInitialize(
        std::shared_ptr<AdaptiveSharedNamespace::ElementParserRegistration> sharedParserRegistration) noexcept try
    {
        m_registration = std::make_shared<RegistrationMap>();
        m_sharedParserRegistration = sharedParserRegistration;

        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveElementParserRegistration::Set(HSTRING type, IAdaptiveElementParser* Parser)
    {
        std::string typeString = HStringToUTF8(type);

        m_sharedParserRegistration->AddParser(typeString, std::make_shared<SharedModelElementParser>(this));

        ComPtr<IAdaptiveElementParser> localParser(Parser);
        (*m_registration)[typeString] = localParser;

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveElementParserRegistration::Get(HSTRING type, IAdaptiveElementParser** result)
    {
        *result = nullptr;

        RegistrationMap::iterator found = m_registration->find(HStringToUTF8(type));
        if (found != m_registration->end())
        {
            *result = found->second.Get();
        }
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveElementParserRegistration::Remove(HSTRING type)
    {
        std::string typeString = HStringToUTF8(type);

        m_sharedParserRegistration->RemoveParser(typeString);
        m_registration->erase(typeString);

        return S_OK;
    }

    std::shared_ptr<ElementParserRegistration> AdaptiveElementParserRegistration::GetSharedParserRegistration()
    {
        return m_sharedParserRegistration;
    }

    std::shared_ptr<BaseCardElement> SharedModelElementParser::Deserialize(
        std::shared_ptr<AdaptiveSharedNamespace::ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<AdaptiveSharedNamespace::ActionParserRegistration> actionParserRegistration,
        const Json::Value& value)
    {
        std::string type = ParseUtil::GetTypeAsString(value);

        HString typeAsHstring;
        THROW_IF_FAILED(UTF8ToHString(type, typeAsHstring.GetAddressOf()));

        ComPtr<IAdaptiveElementParser> parser;
        THROW_IF_FAILED(m_parserRegistration->Get(typeAsHstring.Get(), &parser));

        ComPtr<ABI::Windows::Data::Json::IJsonObject>jsonObject;
        THROW_IF_FAILED(JsonCppToJsonObject(value, &jsonObject));

        ComPtr<IAdaptiveElementParserRegistration> adaptiveElementParserRegistration;
        MakeAndInitialize<AdaptiveNamespace::AdaptiveElementParserRegistration>(&adaptiveElementParserRegistration , elementParserRegistration);

        ComPtr<IAdaptiveActionParserRegistration> adaptiveActionParserRegistration;
        MakeAndInitialize<AdaptiveNamespace::AdaptiveActionParserRegistration>(&adaptiveActionParserRegistration, actionParserRegistration);

        ComPtr<IAdaptiveCardElement> cardElement;
        THROW_IF_FAILED(parser->FromJson(jsonObject.Get(), adaptiveElementParserRegistration.Get(), adaptiveActionParserRegistration.Get(), &cardElement));

        std::shared_ptr<CustomElementWrapper> elementWrapper = std::make_shared<CustomElementWrapper>(cardElement.Get());
        return elementWrapper;
    }
AdaptiveNamespaceEnd
