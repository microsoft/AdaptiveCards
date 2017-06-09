#include "pch.h"
#include "AdaptiveChoiceSetInputConfig.h"
#include "AdaptiveSeparationConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveChoiceSetInputConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveChoiceSetInputConfig::RuntimeClassInitialize(ChoiceSetConfig choiceSetConfig) noexcept
    {
        m_sharedChoiceSetConfig = choiceSetConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInputConfig::get_Separation(IAdaptiveSeparationConfig** separationConfig)
    {
        return MakeAndInitialize<AdaptiveSeparationConfig>(separationConfig, m_sharedChoiceSetConfig.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInputConfig::put_Separation(IAdaptiveSeparationConfig*)
    {
        return E_NOTIMPL;
    }
}
}
