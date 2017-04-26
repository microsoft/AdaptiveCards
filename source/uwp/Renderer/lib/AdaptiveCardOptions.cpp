#include "pch.h"
#include "AdaptiveHostOptions.h"
#include "Util.h"
#include <windows.foundation.collections.h>
#include "XamlCardRendererComponent.h"
#include "AdaptiveCardOptions.h"
#include "AdaptiveBoundaryOptions.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveCardOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveCardOptions::RuntimeClassInitialize(AdaptiveCards::AdaptiveCardOptions adaptiveCardOptions) noexcept
    {
        m_sharedAdaptiveCardOptions = adaptiveCardOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::get_Padding(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveBoundaryOptions ** boundaryOptions)
    {
        return MakeAndInitialize<AdaptiveBoundaryOptions>(boundaryOptions, m_sharedAdaptiveCardOptions.padding);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::put_Padding(IAdaptiveBoundaryOptions* value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::get_MaxActions(INT32* value)
    {
        *value = m_sharedAdaptiveCardOptions.maxActions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::put_MaxActions(INT32 value)
    {
        m_sharedAdaptiveCardOptions.maxActions = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::get_ActionAlignment(HAlignment* value)
    {
        *value = static_cast<HAlignment>(m_sharedAdaptiveCardOptions.actionAlignment);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::put_ActionAlignment(HAlignment value)
    {
        m_sharedAdaptiveCardOptions.actionAlignment = static_cast<AdaptiveCards::HorizontalAlignment>(value);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::get_ActionsOrientation(ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation* value)
    {
        *value = static_cast<ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation>(m_sharedAdaptiveCardOptions.actionsOrientation);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::put_ActionsOrientation(ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation value)
    {
        m_sharedAdaptiveCardOptions.actionsOrientation = static_cast<AdaptiveCards::ActionsOrientation>(value);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::get_BorderColor(Color* value)
    {
        return GetColorFromString(m_sharedAdaptiveCardOptions.borderColor, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::put_BorderColor(Color value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::get_TextColor(Color* value)
    {
        return GetColorFromString(m_sharedAdaptiveCardOptions.textColor, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::put_TextColor(Color value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::get_BackgroundColor(Color* value)
    {
        return GetColorFromString(m_sharedAdaptiveCardOptions.backgroundColor, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::put_BackgroundColor(Color value)
    {
        return E_NOTIMPL;
    }
}}
