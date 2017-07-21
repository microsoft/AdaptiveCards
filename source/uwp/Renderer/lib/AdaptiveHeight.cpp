#include "pch.h"
#include "AdaptiveHeight.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

AdaptiveNamespaceStart
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
    HRESULT AdaptiveHeight::get_HeightType(ABI::AdaptiveNamespace::HeightType* heightType)
    {
        *heightType = static_cast<ABI::AdaptiveNamespace::HeightType>(m_sharedHeight.heightType);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHeight::put_HeightType(ABI::AdaptiveNamespace::HeightType heightType)
    {
        m_sharedHeight.heightType = static_cast<AdaptiveCards::HeightType>(heightType);
        return S_OK;
    }
AdaptiveNamespaceEnd
