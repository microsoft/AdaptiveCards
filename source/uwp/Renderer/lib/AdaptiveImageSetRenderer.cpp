#include "pch.h"

#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveImageSet.h"
#include "AdaptiveImageSetRenderer.h"
#include "enums.h"
#include "Util.h"
#include "XamlBuilder.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::Foundation;

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    HRESULT AdaptiveImageSetRenderer::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveImageSetRenderer::Render(
        IAdaptiveCardElement* cardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* renderArgs,
        ABI::Windows::UI::Xaml::IUIElement** result)
    {
        XamlBuilder::BuildImageSet(cardElement, renderContext, renderArgs, result);
        return S_OK;
    }

    HRESULT AdaptiveImageSetRenderer::FromJson(
        ABI::Windows::Data::Json::IJsonObject* jsonObject,
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParserRegistration* elementParserRegistration,
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionParserRegistration* actionParserRegistration,
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement** element)
    {
        return AdaptiveCards::Rendering::Uwp::FromJson<AdaptiveCards::Rendering::Uwp::AdaptiveImageSet, AdaptiveCards::ImageSet, AdaptiveCards::ImageSetParser>(jsonObject, elementParserRegistration, actionParserRegistration, element);
    }
}}}
