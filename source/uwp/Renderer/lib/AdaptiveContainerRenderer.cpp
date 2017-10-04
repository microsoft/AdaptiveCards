#include "pch.h"

#include "AdaptiveContainerRenderer.h"
#include "enums.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Uwp;
using namespace ABI::Windows::Foundation;

namespace AdaptiveCards { namespace Uwp
{
    AdaptiveContainerRenderer::AdaptiveContainerRenderer()
    {
    }

    AdaptiveContainerRenderer::AdaptiveContainerRenderer(const std::shared_ptr<XamlBuilder> xamlBuilder) :
        m_xamlBuilder(xamlBuilder)
    {
    }

    HRESULT AdaptiveContainerRenderer::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveContainerRenderer::Render(
        IAdaptiveCardElement* cardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* renderArgs,
        ABI::Windows::UI::Xaml::IUIElement** result)
    {
        m_xamlBuilder->BuildContainer(cardElement, renderContext, renderArgs, result);
        return S_OK;
    }

}}
