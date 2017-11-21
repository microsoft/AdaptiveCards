#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{

    class AdaptiveShowCardActionConfig :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveShowCardActionConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveShowCardActionConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveCards::ShowCardActionConfig showCardActionConfig) noexcept;

        IFACEMETHODIMP get_ActionMode(_Out_ ABI::AdaptiveCards::Rendering::Uwp::ActionMode* value);
        IFACEMETHODIMP put_ActionMode(_In_ ABI::AdaptiveCards::Rendering::Uwp::ActionMode value);

        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle* style);
        IFACEMETHODIMP put_Style(_In_ ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle style);

        IFACEMETHODIMP get_InlineTopMargin(_Out_ UINT32* value);
        IFACEMETHODIMP put_InlineTopMargin(_In_ UINT32 value);

    private:
        ABI::AdaptiveCards::Rendering::Uwp::ActionMode m_actionMode;
        ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle m_containerStyle;
        UINT32 m_inlineTopMargin;
    };

    ActivatableClass(AdaptiveShowCardActionConfig);
}}}