#include "pch.h"

#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveToggleInput.h"
#include "AdaptiveToggleInputRenderer.h"
#include "enums.h"
#include "Util.h"
#include "XamlBuilder.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;

AdaptiveNamespaceStart
    HRESULT AdaptiveToggleInputRenderer::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInputRenderer::Render(
        IAdaptiveCardElement* cardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* renderArgs,
        ABI::Windows::UI::Xaml::IUIElement** result)
    {
        XamlBuilder::BuildToggleInput(cardElement, renderContext, renderArgs, result);
        return S_OK;
    }

    HRESULT AdaptiveToggleInputRenderer::FromJson(
        ABI::Windows::Data::Json::IJsonObject* jsonObject,
        ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        ABI::AdaptiveNamespace::IAdaptiveCardElement** element)
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveToggleInput, AdaptiveSharedNamespace::ToggleInput, AdaptiveSharedNamespace::ToggleInputParser>(jsonObject, elementParserRegistration, actionParserRegistration, element);
    }
AdaptiveNamespaceEnd
