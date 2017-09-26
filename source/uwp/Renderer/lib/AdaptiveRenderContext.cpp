#include "pch.h"

#include "AdaptiveRenderContext.h"
#include "AdaptiveHostConfig.h"
#include "AdaptiveElementRendererRegistration.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveRenderContext::RuntimeClassInitialize() noexcept
    {
        return S_OK;
    }

    HRESULT AdaptiveRenderContext::RuntimeClassInitialize(
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfig* hostConfig,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveElementRendererRegistration* elementRendererRegistration,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionRendererRegistration* actionRendererRegistration) noexcept try
    {
        m_hostConfig.Attach(hostConfig);
        m_elementRendererRegistration.Attach(elementRendererRegistration);
        m_actionRendererRegistration.Attach(actionRendererRegistration);
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveRenderContext::get_HostConfig(IAdaptiveHostConfig** value)
    {
        value = &m_hostConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRenderContext::get_ElementRenderers(IAdaptiveElementRendererRegistration** value)
    {
        value = &m_elementRendererRegistration;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRenderContext::get_ActionRenderers(IAdaptiveActionRendererRegistration** value)
    {
        value = &m_actionRendererRegistration;
        return S_OK;
    }
}}
