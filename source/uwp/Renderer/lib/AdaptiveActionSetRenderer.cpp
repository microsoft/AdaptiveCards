#include "pch.h"

#include "AdaptiveActionSet.h"
#include "AdaptiveActionSetRenderer.h"
#include "AdaptiveElementParserRegistration.h"
#include "enums.h"
#include "Util.h"
#include "XamlBuilder.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;

namespace AdaptiveCards
{
    namespace Rendering
    {
        namespace Uwp
        {
            HRESULT AdaptiveActionSetRenderer::RuntimeClassInitialize() noexcept try
            {
                return S_OK;
            }
            CATCH_RETURN;

            _Use_decl_annotations_ HRESULT AdaptiveActionSetRenderer::Render(IAdaptiveCardElement* cardElement,
                                                                             IAdaptiveRenderContext* renderContext,
                                                                             IAdaptiveRenderArgs* renderArgs,
                                                                             ABI::Windows::UI::Xaml::IUIElement** result) noexcept try
            {
                XamlBuilder::BuildActionSet(cardElement, renderContext, renderArgs, result);
                return S_OK;
            }
            CATCH_RETURN;

            HRESULT AdaptiveActionSetRenderer::FromJson(
                ABI::Windows::Data::Json::IJsonObject* jsonObject,
                ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
                ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
                ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
                ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept try
            {
                return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveActionSet, AdaptiveSharedNamespace::ActionSet, AdaptiveSharedNamespace::ActionSetParser>(
                    jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
            }
            CATCH_RETURN;
        }
    }
}
