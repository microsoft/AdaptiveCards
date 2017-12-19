#include "pch.h"
#include "Util.h"
#include "AdaptiveCardConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::UI;

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    HRESULT AdaptiveCardConfig::RuntimeClassInitialize() noexcept try
    {
        AdaptiveCards::AdaptiveCardConfig cardConfig;
        return RuntimeClassInitialize(cardConfig);
    } CATCH_RETURN;

    HRESULT AdaptiveCardConfig::RuntimeClassInitialize(AdaptiveCards::AdaptiveCardConfig adaptiveCardConfig) noexcept
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
}}}
