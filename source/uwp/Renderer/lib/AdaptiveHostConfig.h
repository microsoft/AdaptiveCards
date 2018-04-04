#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

AdaptiveNamespaceStart
    class AdaptiveHostConfig :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveHostConfig>
    {
        AdaptiveRuntime(AdaptiveHostConfig)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const HostConfig& config);

        // IAdaptiveHostConfig
        IFACEMETHODIMP get_FontFamily(_Out_ HSTRING* text);
        IFACEMETHODIMP put_FontFamily(_In_ HSTRING text);

        IFACEMETHODIMP get_FontSizes(_Out_ ABI::AdaptiveNamespace::IAdaptiveFontSizesConfig** fontSize);
        IFACEMETHODIMP put_FontSizes(_In_ ABI::AdaptiveNamespace::IAdaptiveFontSizesConfig* fontSize);

        IFACEMETHODIMP get_FontWeights(_Out_ ABI::AdaptiveNamespace::IAdaptiveFontWeightsConfig** fontWeight);
        IFACEMETHODIMP put_FontWeights(_In_ ABI::AdaptiveNamespace::IAdaptiveFontWeightsConfig* fontWeight);

        IFACEMETHODIMP get_SupportsInteractivity(_Out_ boolean* supportsInteractivity);
        IFACEMETHODIMP put_SupportsInteractivity(_In_ boolean supportsInteractivity);

        IFACEMETHODIMP get_ContainerStyles(_Out_ ABI::AdaptiveNamespace::IAdaptiveContainerStylesDefinition** value);
        IFACEMETHODIMP put_ContainerStyles(_In_ ABI::AdaptiveNamespace::IAdaptiveContainerStylesDefinition* value);

        IFACEMETHODIMP get_ImageSizes(_Out_ ABI::AdaptiveNamespace::IAdaptiveImageSizesConfig** imageConfig);
        IFACEMETHODIMP put_ImageSizes(_In_ ABI::AdaptiveNamespace::IAdaptiveImageSizesConfig* imageConfig);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveNamespace::IAdaptiveSpacingConfig** spacingConfigConfig);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveNamespace::IAdaptiveSpacingConfig* spacingConfigConfig);

        IFACEMETHODIMP get_Separator(_Out_ ABI::AdaptiveNamespace::IAdaptiveSeparatorConfig** separatorConfigConfig);
        IFACEMETHODIMP put_Separator(_In_ ABI::AdaptiveNamespace::IAdaptiveSeparatorConfig* separatorConfigConfig);

        IFACEMETHODIMP get_AdaptiveCard(_Out_ ABI::AdaptiveNamespace::IAdaptiveCardConfig** adaptiveCardConfigConfig);
        IFACEMETHODIMP put_AdaptiveCard(_In_ ABI::AdaptiveNamespace::IAdaptiveCardConfig* adaptiveCardConfigConfig);

        IFACEMETHODIMP get_ImageSet(_Out_ ABI::AdaptiveNamespace::IAdaptiveImageSetConfig** imageSetConfigConfig);
        IFACEMETHODIMP put_ImageSet(_In_ ABI::AdaptiveNamespace::IAdaptiveImageSetConfig* imageSetConfigConfig);

        IFACEMETHODIMP get_Image(_Out_ ABI::AdaptiveNamespace::IAdaptiveImageConfig** imageConfigConfig);
        IFACEMETHODIMP put_Image(_In_ ABI::AdaptiveNamespace::IAdaptiveImageConfig* imageConfigConfig);

        IFACEMETHODIMP get_FactSet(_Out_ ABI::AdaptiveNamespace::IAdaptiveFactSetConfig** factSetConfigConfig);
        IFACEMETHODIMP put_FactSet(_In_ ABI::AdaptiveNamespace::IAdaptiveFactSetConfig* factSetConfigConfig);

        IFACEMETHODIMP get_Actions(_Out_ ABI::AdaptiveNamespace::IAdaptiveActionsConfig** actionsOptionConfig);
        IFACEMETHODIMP put_Actions(_In_ ABI::AdaptiveNamespace::IAdaptiveActionsConfig* actionsOptionConfig);

    private:

        Microsoft::WRL::Wrappers::HString m_fontFamily;
        boolean m_supportsInteractivity;

        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveFontSizesConfig> m_fontSizes;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveFontWeightsConfig> m_fontWeights;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveContainerStylesDefinition> m_containerStyles;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveImageSizesConfig> m_imageSizes;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveSpacingConfig> m_spacing;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveSeparatorConfig> m_separator;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardConfig> m_adaptiveCard;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveImageSetConfig> m_imageSet;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveImageConfig> m_image;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveFactSetConfig> m_factSet;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionsConfig> m_actions;
    };

    class AdaptiveHostConfigStaticsImpl WrlFinal
        : public Microsoft::WRL::AgileActivationFactory<
        ABI::AdaptiveNamespace::IAdaptiveHostConfigStatics>
    {
        AdaptiveRuntimeStatic(AdaptiveHostConfig);

    public:
        IFACEMETHOD(ActivateInstance)(_COM_Outptr_ IInspectable** ppvObject) noexcept override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveHostConfig>(ppvObject);
        }

        // IAdaptiveHostConfigStatics
        IFACEMETHODIMP FromJsonString(_In_ HSTRING hostConfigJson, _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveHostConfigParseResult** config) noexcept;
        IFACEMETHODIMP FromJson(_In_ ABI::Windows::Data::Json::IJsonObject* hostConfigJson, _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveHostConfigParseResult** config) noexcept;

    private:
        HRESULT FromJsonString(_In_ const std::string jsonString, _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveHostConfigParseResult** config);
    };

    ActivatableClassWithFactory(AdaptiveHostConfig, AdaptiveHostConfigStaticsImpl);
AdaptiveNamespaceEnd