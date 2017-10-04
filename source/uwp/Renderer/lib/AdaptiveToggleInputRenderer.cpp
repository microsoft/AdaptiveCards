#include "pch.h"

#include "AdaptiveToggleInputRenderer.h"
#include "enums.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Uwp;
using namespace ABI::Windows::Foundation;

namespace AdaptiveCards { namespace Uwp
{
    AdaptiveToggleInputRenderer::AdaptiveToggleInputRenderer()
    {
    }

    AdaptiveToggleInputRenderer::AdaptiveToggleInputRenderer(const std::shared_ptr<XamlBuilder> xamlBuilder) :
        m_xamlBuilder(xamlBuilder)
    {
    }

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
        m_xamlBuilder->BuildToggleInput(cardElement, renderContext, renderArgs, result);
        return S_OK;
    }
}}
