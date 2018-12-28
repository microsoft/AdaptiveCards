#include "pch.h"

#include "AdaptiveChoiceSetInput.h"
#include "AdaptiveChoiceSetInputRenderer.h"
#include "AdaptiveElementParserRegistration.h"
#include "enums.h"
#include "Util.h"
#include "XamlBuilder.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveChoiceSetInputRenderer::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveChoiceSetInputRenderer::Render(_In_ IAdaptiveCardElement* cardElement,
                                                   _In_ IAdaptiveRenderContext* renderContext,
                                                   _In_ IAdaptiveRenderArgs* renderArgs,
                                                   _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result)
    {
        XamlBuilder::BuildChoiceSetInput(cardElement, renderContext, renderArgs, result);
        return S_OK;
    }

    HRESULT AdaptiveChoiceSetInputRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element)
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveChoiceSetInput, AdaptiveSharedNamespace::ChoiceSetInput, AdaptiveSharedNamespace::ChoiceSetInputParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
}
