#include "pch.h"

#include "AdaptiveNumberInputRenderer.h"
#include "enums.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Uwp;
using namespace ABI::Windows::Foundation;

namespace AdaptiveCards { namespace Uwp
{
    AdaptiveNumberInputRenderer::AdaptiveNumberInputRenderer()
    {
    }

    AdaptiveNumberInputRenderer::AdaptiveNumberInputRenderer(const std::shared_ptr<XamlBuilder> xamlBuilder) :
        m_xamlBuilder(xamlBuilder)
    {
    }

    HRESULT AdaptiveNumberInputRenderer::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInputRenderer::Render(
        IAdaptiveCardElement* cardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* renderArgs,
        ABI::Windows::UI::Xaml::IUIElement** result)
    {
        m_xamlBuilder->BuildNumberInput(cardElement, renderContext, renderArgs, result);
        return S_OK;
    }
}}
