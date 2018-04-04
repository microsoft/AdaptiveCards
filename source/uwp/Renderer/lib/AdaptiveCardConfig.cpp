#include "pch.h"
#include "Util.h"
#include "AdaptiveCardConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::UI;

AdaptiveNamespaceStart
    HRESULT AdaptiveCardConfig::RuntimeClassInitialize() noexcept try
    {
        AdaptiveSharedNamespace::AdaptiveCardConfig cardConfig;
        return RuntimeClassInitialize(cardConfig);
    } CATCH_RETURN;

    HRESULT AdaptiveCardConfig::RuntimeClassInitialize(AdaptiveSharedNamespace::AdaptiveCardConfig adaptiveCardConfig) noexcept
    {
        m_allowCustomStyle = adaptiveCardConfig.allowCustomStyle;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardConfig::get_AllowCustomStyle(boolean* allowCustomStyle)
    {
        *allowCustomStyle = m_allowCustomStyle;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardConfig::put_AllowCustomStyle(boolean allowCustomStyle)
    {
        m_allowCustomStyle = allowCustomStyle;
        return S_OK;
    }
AdaptiveNamespaceEnd
