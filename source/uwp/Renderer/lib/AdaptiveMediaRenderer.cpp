#include "pch.h"

#include "AdaptiveMedia.h"
#include "AdaptiveMediaRenderer.h"
#include "XamlBuilder.h"
#include "AdaptiveElementParserRegistration.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

AdaptiveNamespaceStart
    HRESULT AdaptiveMediaRenderer::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveMediaRenderer::Render(
        IAdaptiveCardElement* cardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* renderArgs,
        ABI::Windows::UI::Xaml::IUIElement** result)
    {
        XamlBuilder::BuildMedia(cardElement, renderContext, renderArgs, result);
        return S_OK;
    }

    HRESULT AdaptiveMediaRenderer::FromJson(
        ABI::Windows::Data::Json::IJsonObject* jsonObject,
        ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveWarning*>* adaptiveWarnings,
        ABI::AdaptiveNamespace::IAdaptiveCardElement** element)
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveMedia, AdaptiveSharedNamespace::Media, AdaptiveSharedNamespace::MediaParser>(jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
AdaptiveNamespaceEnd
