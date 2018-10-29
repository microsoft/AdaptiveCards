#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "SharedAdaptiveCard.h"

namespace AdaptiveNamespace
{
    class AdaptiveJsonTemplaterStaticsImpl WrlFinal
        : public Microsoft::WRL::AgileActivationFactory<ABI::AdaptiveNamespace::IAdaptiveJsonTemplaterStatics>
    {
        AdaptiveRuntimeStatic(AdaptiveJsonTemplater);

        IFACEMETHODIMP ApplyJsonTemplating(_In_ ABI::Windows::Data::Json::IJsonObject* adaptiveJson,
                                           _In_ ABI::Windows::Data::Json::IJsonObject* adaptiveFrame,
                                           _COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result) noexcept;
    };

    ActivatableStaticOnlyFactory(AdaptiveJsonTemplaterStaticsImpl);
}
