#include "pch.h"

#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveImage.h"
#include "AdaptiveImageRenderer.h"
#include "enums.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;

AdaptiveNamespaceStart
    AdaptiveImageRenderer::AdaptiveImageRenderer()
    {
        m_xamlBuilder = std::make_shared<XamlBuilder>();
    }

    AdaptiveImageRenderer::AdaptiveImageRenderer(std::shared_ptr<XamlBuilder> xamlBuilder) : m_xamlBuilder(xamlBuilder)
    {
    }

    HRESULT AdaptiveImageRenderer::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveImageRenderer::Render(
        IAdaptiveCardElement* cardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* renderArgs,
        ABI::Windows::UI::Xaml::IUIElement** result)
    {
        m_xamlBuilder->BuildImage(cardElement, renderContext, renderArgs, result);
        return S_OK;
    }

    HRESULT AdaptiveImageRenderer::FromJson(
        ABI::Windows::Data::Json::IJsonObject* jsonObject,
        ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        ABI::AdaptiveNamespace::IAdaptiveCardElement** element)
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveImage, AdaptiveSharedNamespace::Image, AdaptiveSharedNamespace::ImageParser>(jsonObject, elementParserRegistration, actionParserRegistration, element);
    }
AdaptiveNamespaceEnd
