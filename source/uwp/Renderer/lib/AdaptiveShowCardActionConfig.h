#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

AdaptiveNamespaceStart
    class AdaptiveShowCardActionConfig :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveNamespaceRef::IAdaptiveShowCardActionConfig>
    {
        AdaptiveRuntime(AdaptiveShowCardActionConfig)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveCards::ShowCardActionConfig showCardActionConfig) noexcept;

        IFACEMETHODIMP get_ActionMode(_Out_ ABI::AdaptiveNamespaceRef::ActionMode* value);
        IFACEMETHODIMP put_ActionMode(_In_ ABI::AdaptiveNamespaceRef::ActionMode value);

        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveNamespaceRef::ContainerStyle* style);
        IFACEMETHODIMP put_Style(_In_ ABI::AdaptiveNamespaceRef::ContainerStyle style);

        IFACEMETHODIMP get_InlineTopMargin(_Out_ UINT32* value);
        IFACEMETHODIMP put_InlineTopMargin(_In_ UINT32 value);

    private:
        ABI::AdaptiveNamespaceRef::ActionMode m_actionMode;
        ABI::AdaptiveNamespaceRef::ContainerStyle m_containerStyle;
        UINT32 m_inlineTopMargin;
    };

    ActivatableClass(AdaptiveShowCardActionConfig);
AdaptiveNamespaceEnd
