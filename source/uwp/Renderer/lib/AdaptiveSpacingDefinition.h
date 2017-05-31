#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveSpacingDefinition :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingDefinition>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveSpacingDefinition, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(SpacingDefinition spacingDefinition) noexcept;

        IFACEMETHODIMP get_Left(_Out_ UINT32 *value);
        IFACEMETHODIMP put_Left(_In_ UINT32 value);

        IFACEMETHODIMP get_Right(_Out_ UINT32 *value);
        IFACEMETHODIMP put_Right(_In_ UINT32 value);

        IFACEMETHODIMP get_Bottom(_Out_ UINT32 *value);
        IFACEMETHODIMP put_Bottom(_In_ UINT32 value);

        IFACEMETHODIMP get_Top(_Out_ UINT32 *value);
        IFACEMETHODIMP put_Top(_In_ UINT32 value);

    private:
        SpacingDefinition m_sharedSpacingDefinition;
    };

    ActivatableClass(AdaptiveSpacingDefinition);
}}