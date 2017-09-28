#include "pch.h"

#include "AdaptiveRenderContext.h"
#include "AdaptiveHostConfig.h"
#include "AdaptiveElementRendererRegistration.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Uwp;
using namespace ABI::Windows::Foundation;

namespace AdaptiveCards { namespace Uwp
{
    HRESULT AdaptiveRenderContext::RuntimeClassInitialize() noexcept
    {
        return S_OK;
    }

    HRESULT AdaptiveRenderContext::RuntimeClassInitialize(
        ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig* hostConfig,
        ABI::AdaptiveCards::Uwp::IAdaptiveElementRendererRegistration* elementRendererRegistration,
        ABI::AdaptiveCards::Uwp::IAdaptiveActionRendererRegistration* actionRendererRegistration) noexcept try
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
