#pragma once
#include "AdaptiveCards.Uwp.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveCardGetResourceStreamArgs :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
            ABI::AdaptiveCards::Uwp::IAdaptiveCardGetResourceStreamArgs>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveCardGetResourceStreamArgs, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize(_In_ ABI::Windows::Foundation::IUriRuntimeClass* url);

        IFACEMETHODIMP get_Url(_Outptr_ ABI::Windows::Foundation::IUriRuntimeClass** url);

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IUriRuntimeClass> m_url;
    };
}}