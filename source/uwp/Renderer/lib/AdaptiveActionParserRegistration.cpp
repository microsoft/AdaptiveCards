#include "pch.h"
#include "AdaptiveActionParserRegistration.h"
#include "AdaptiveElementParserRegistration.h"
#include "CustomActionWrapper.h"
#include "Util.h"
#include "Vector.h"
#include "AdaptiveShowCardActionRenderer.h"
#include "AdaptiveSubmitActionRenderer.h"
#include "AdaptiveOpenUrlActionRenderer.h"
#include "AdaptiveToggleVisibilityActionRenderer.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::UI;

namespace AdaptiveNamespace
{
    AdaptiveActionParserRegistration::AdaptiveActionParserRegistration() {}

    HRESULT AdaptiveActionParserRegistration::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<ActionParserRegistration> sharedParserRegistration = std::make_shared<ActionParserRegistration>();
        RuntimeClassInitialize(sharedParserRegistration);

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveActionParserRegistration::RuntimeClassInitialize(
        std::shared_ptr<AdaptiveSharedNamespace::ActionParserRegistration> sharedParserRegistration) noexcept try
    {
        m_registration = std::make_shared<RegistrationMap>();
        m_sharedParserRegistration = sharedParserRegistration;

        m_isInitializing = true;
        RegisterDefaultActionRenderers(this);
        m_isInitializing = false;

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveActionParserRegistration::Set(_In_ HSTRING type, _In_ IAdaptiveActionParser* Parser) noexcept try
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

    HRESULT AdaptiveActionParserRegistration::Get(_In_ HSTRING type, _COM_Outptr_ IAdaptiveActionParser** result) noexcept try
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

    HRESULT AdaptiveActionParserRegistration::Remove(_In_ HSTRING type) noexcept try
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

    std::shared_ptr<BaseActionElement> SharedModelActionParser::Deserialize(ParseContext& context, const Json::Value& value)
    {
        std::string type = ParseUtil::GetTypeAsString(value);

        HString typeAsHstring;
        THROW_IF_FAILED(UTF8ToHString(type, typeAsHstring.GetAddressOf()));

        ComPtr<IAdaptiveActionParser> parser;
        THROW_IF_FAILED(m_parserRegistration->Get(typeAsHstring.Get(), &parser));

        ComPtr<ABI::Windows::Data::Json::IJsonObject> jsonObject;
        THROW_IF_FAILED(JsonCppToJsonObject(value, &jsonObject));

        ComPtr<IAdaptiveElementParserRegistration> adaptiveElementParserRegistration;
        MakeAndInitialize<AdaptiveNamespace::AdaptiveElementParserRegistration>(&adaptiveElementParserRegistration,
                                                                                context.elementParserRegistration);

        ComPtr<IAdaptiveActionParserRegistration> adaptiveActionParserRegistration;
        MakeAndInitialize<AdaptiveNamespace::AdaptiveActionParserRegistration>(&adaptiveActionParserRegistration,
                                                                               context.actionParserRegistration);

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
}
