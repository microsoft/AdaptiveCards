#include "pch.h"
#include "Util.h"
#include "AdaptiveCardConfig.h"
#include "AdaptiveSpacingDefinition.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::UI;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveCardConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveCardConfig::RuntimeClassInitialize(AdaptiveCards::AdaptiveCardConfig adaptiveCardConfig) noexcept
    {
        m_sharedAdaptiveCardConfig = adaptiveCardConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardConfig::get_Padding(IAdaptiveSpacingDefinition** spacingDefinition)
    {
        return MakeAndInitialize<AdaptiveSpacingDefinition>(spacingDefinition, m_sharedAdaptiveCardConfig.padding);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardConfig::put_Padding(IAdaptiveSpacingDefinition* /*value*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardConfig::get_AllowCustomStyle(boolean * allowCustomStyle)
    {
        *allowCustomStyle = m_sharedAdaptiveCardConfig.allowCustomStyle;
        return S_OK;
    }
    
    _Use_decl_annotations_
    HRESULT AdaptiveCardConfig::put_AllowCustomStyle(boolean allowCustomStyle)
    {
        m_sharedAdaptiveCardConfig.allowCustomStyle = allowCustomStyle;
        return S_OK;
    }
}}
