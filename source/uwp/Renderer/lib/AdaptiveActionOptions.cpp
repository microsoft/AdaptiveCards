#include "pch.h"
#include "Util.h"
#include "AdaptiveActionOptions.h"
#include "AdaptiveBoundaryOptions.h"
#include "AdaptiveShowCardOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::UI;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveActionOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveActionOptions::RuntimeClassInitialize(AdaptiveCards::ActionOptions actionOptions) noexcept
    {
        m_sharedActionOptions = actionOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::get_ShowCard(IAdaptiveShowCardOptions** showCardOptions)
    {
        return MakeAndInitialize<AdaptiveShowCardOptions>(showCardOptions, m_sharedActionOptions.showCard);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::put_ShowCard(IAdaptiveShowCardOptions* showCardOptions)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::get_Padding(IAdaptiveBoundaryOptions** boundaryOptions)
    {
        return MakeAndInitialize<AdaptiveBoundaryOptions>(boundaryOptions, m_sharedActionOptions.padding);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::put_Padding(IAdaptiveBoundaryOptions* value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::get_BorderThickness(UINT32* value)
    {
        *value = m_sharedActionOptions.borderThickness;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::put_BorderThickness(UINT32 value)
    {
        m_sharedActionOptions.borderThickness = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::get_FontWeight(UINT32* value)
    {
        *value = m_sharedActionOptions.fontWeight;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::put_FontWeight(UINT32 value)
    {
        m_sharedActionOptions.fontWeight = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::get_FontSize(UINT32* value)
    {
        *value = m_sharedActionOptions.fontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::put_FontSize(UINT32 value)
    {
        m_sharedActionOptions.fontSize = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::get_Spacing(UINT32* value)
    {
        *value = m_sharedActionOptions.spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::put_Spacing(UINT32 value)
    {
        m_sharedActionOptions.spacing = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::get_ActionAlignment(HAlignment* value)
    {
        *value = static_cast<HAlignment>(m_sharedActionOptions.actionAlignment);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::put_ActionAlignment(HAlignment value)
    {
        m_sharedActionOptions.actionAlignment = static_cast<AdaptiveCards::HorizontalAlignment>(value);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::get_ActionsOrientation(ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation* value)
    {
        *value = static_cast<ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation>(m_sharedActionOptions.actionsOrientation);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::put_ActionsOrientation(ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation value)
    {
        m_sharedActionOptions.actionsOrientation = static_cast<AdaptiveCards::ActionsOrientation>(value);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::get_BorderColor(Color* value)
    {
        return GetColorFromString(m_sharedActionOptions.borderColor, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::put_BorderColor(Color value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::get_TextColor(Color* value)
    {
        return GetColorFromString(m_sharedActionOptions.textColor, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::put_TextColor(Color value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::get_BackgroundColor(Color* value)
    {
        return GetColorFromString(m_sharedActionOptions.backgroundColor, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::put_BackgroundColor(Color value)
    {
        return E_NOTIMPL;
    }
}}
