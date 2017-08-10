#include "pch.h"
#include "AdaptiveHeight.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveHeight::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveHeight::RuntimeClassInitialize(Height Height) noexcept
    {
        m_sharedHeight = Height;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHeight::get_HeightType(ABI::AdaptiveCards::XamlCardRenderer::HeightType* heightType)
    {
        *heightType = static_cast<ABI::AdaptiveCards::XamlCardRenderer::HeightType>(m_sharedHeight.heightType);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHeight::put_HeightType(ABI::AdaptiveCards::XamlCardRenderer::HeightType heightType)
    {
        m_sharedHeight.heightType = static_cast<AdaptiveCards::HeightType>(heightType);
        return S_OK;
    }
}
}
