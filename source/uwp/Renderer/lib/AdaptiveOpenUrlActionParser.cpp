#include "pch.h"

#include "AdaptiveOpenUrlAction.h"
#include "AdaptiveOpenUrlActionParser.h"
#include "Util.h"
#include "AdaptiveElementParserRegistration.h"

using namespace Microsoft::WRL;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveOpenUrlActionParser::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveOpenUrlActionParser::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** element) noexcept try
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveOpenUrlAction, AdaptiveSharedNamespace::OpenUrlAction, AdaptiveSharedNamespace::OpenUrlActionParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
