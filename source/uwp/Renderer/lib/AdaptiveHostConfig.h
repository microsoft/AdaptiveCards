#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveHostConfig :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveHostConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const HostConfig& config);

        // IAdaptiveHostConfig
        IFACEMETHODIMP get_FontFamily(_Out_ HSTRING* text);
        IFACEMETHODIMP put_FontFamily(_In_ HSTRING text);

        IFACEMETHODIMP get_FontSizes(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFontSizesConfig** fontSize);
        IFACEMETHODIMP put_FontSizes(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFontSizesConfig* fontSize);

        IFACEMETHODIMP get_SupportsInteractivity(_Out_ boolean* supportsInteractivity);
        IFACEMETHODIMP put_SupportsInteractivity(_In_ boolean supportsInteractivity);

        IFACEMETHODIMP get_Colors(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorsConfig** colorsConfig);
        IFACEMETHODIMP put_Colors(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorsConfig* colorsConfig);

        IFACEMETHODIMP get_ImageSizes(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSizesConfig** imageConfig);
        IFACEMETHODIMP put_ImageSizes(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSizesConfig* imageConfig);

        IFACEMETHODIMP get_MaxActions(_Out_ UINT32 *maxActions);
        IFACEMETHODIMP put_MaxActions(_In_ UINT32 maxActions);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingConfig** spacingConfigConfig);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingConfig* spacingConfigConfig);

        IFACEMETHODIMP get_SeparatorThickness(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparatorThicknessConfig** separatorThicknessConfigConfig);
        IFACEMETHODIMP put_SeparatorThickness(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparatorThicknessConfig* separatorThicknessConfigConfig);

        IFACEMETHODIMP get_AdaptiveCard(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardConfig** adaptiveCardConfigConfig);
        IFACEMETHODIMP put_AdaptiveCard(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardConfig* adaptiveCardConfigConfig);

        IFACEMETHODIMP get_ImageSet(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSetConfig** imageSetConfigConfig);
        IFACEMETHODIMP put_ImageSet(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSetConfig* imageSetConfigConfig);

        IFACEMETHODIMP get_FactSet(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFactSetConfig** factSetConfigConfig);
        IFACEMETHODIMP put_FactSet(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFactSetConfig* factSetConfigConfig);

        IFACEMETHODIMP get_Container(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerConfig** containerConfigConfig);
        IFACEMETHODIMP put_Container(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerConfig* containerConfigConfig);

        IFACEMETHODIMP get_Actions(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionsConfig** actionsOptionConfig);
        IFACEMETHODIMP put_Actions(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionsConfig* actionsOptionConfig);

    private:
        HostConfig m_sharedHostConfig;
    };

    class AdaptiveHostConfigStaticsImpl WrlFinal
        : public Microsoft::WRL::AgileActivationFactory<
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfigStatics>
    {
        InspectableClassStatic(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveHostConfig, TrustLevel::BaseTrust);

    public:
        IFACEMETHOD(ActivateInstance)(_COM_Outptr_ IInspectable** ppvObject) noexcept override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveHostConfig>(ppvObject);
        }

        // IAdaptiveHostConfigStatics
        IFACEMETHODIMP CreateHostConfigFromJson(_In_ HSTRING hostConfigJson, _COM_Outptr_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfig** config) noexcept;
    };

    ActivatableClassWithFactory(AdaptiveHostConfig, AdaptiveHostConfigStaticsImpl);
}}