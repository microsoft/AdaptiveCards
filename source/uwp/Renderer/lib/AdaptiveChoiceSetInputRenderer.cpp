#include "pch.h"

#include "AdaptiveChoiceSetInput.h"
#include "AdaptiveChoiceSetInputRenderer.h"
#include "AdaptiveElementParserRegistration.h"
#include "enums.h"
#include "Util.h"
#include "XamlBuilder.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespaceRef;
using namespace ABI::Windows::Foundation;

AdaptiveNamespaceStart
    HRESULT AdaptiveChoiceSetInputRenderer::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInputRenderer::Render(
        IAdaptiveCardElement* cardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* renderArgs,
        ABI::Windows::UI::Xaml::IUIElement** result)
    {
        XamlBuilder::BuildChoiceSetInput(cardElement, renderContext, renderArgs, result);
        return S_OK;
    }

    HRESULT AdaptiveChoiceSetInputRenderer::FromJson(
        ABI::Windows::Data::Json::IJsonObject* jsonObject,
        ABI::AdaptiveNamespaceRef::IAdaptiveElementParserRegistration* elementParserRegistration,
        ABI::AdaptiveNamespaceRef::IAdaptiveActionParserRegistration* actionParserRegistration,
        ABI::AdaptiveNamespaceRef::IAdaptiveCardElement** element)
    {
        return AdaptiveNamespaceRef::FromJson<AdaptiveNamespaceRef::AdaptiveChoiceSetInput, AdaptiveCards::ChoiceSetInput, AdaptiveCards::ChoiceSetInputParser>(jsonObject, elementParserRegistration, actionParserRegistration, element);
    }
AdaptiveNamespaceEnd
