#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

AdaptiveNamespaceStart
    class AdaptiveHostConfig :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespaceRef::IAdaptiveHostConfig>
    {
        AdaptiveRuntime(AdaptiveHostConfig)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const HostConfig& config);

        // IAdaptiveHostConfig
        IFACEMETHODIMP get_FontFamily(_Out_ HSTRING* text);
        IFACEMETHODIMP put_FontFamily(_In_ HSTRING text);

        IFACEMETHODIMP get_FontSizes(_Out_ ABI::AdaptiveNamespaceRef::IAdaptiveFontSizesConfig** fontSize);
        IFACEMETHODIMP put_FontSizes(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveFontSizesConfig* fontSize);

        IFACEMETHODIMP get_FontWeights(_Out_ ABI::AdaptiveNamespaceRef::IAdaptiveFontWeightsConfig** fontWeight);
        IFACEMETHODIMP put_FontWeights(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveFontWeightsConfig* fontWeight);

        IFACEMETHODIMP get_SupportsInteractivity(_Out_ boolean* supportsInteractivity);
        IFACEMETHODIMP put_SupportsInteractivity(_In_ boolean supportsInteractivity);

        IFACEMETHODIMP get_ContainerStyles(_Out_ ABI::AdaptiveNamespaceRef::IAdaptiveContainerStylesDefinition** value);
        IFACEMETHODIMP put_ContainerStyles(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveContainerStylesDefinition* value);

        IFACEMETHODIMP get_ImageSizes(_Out_ ABI::AdaptiveNamespaceRef::IAdaptiveImageSizesConfig** imageConfig);
        IFACEMETHODIMP put_ImageSizes(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveImageSizesConfig* imageConfig);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveNamespaceRef::IAdaptiveSpacingConfig** spacingConfigConfig);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveSpacingConfig* spacingConfigConfig);

        IFACEMETHODIMP get_Separator(_Out_ ABI::AdaptiveNamespaceRef::IAdaptiveSeparatorConfig** separatorConfigConfig);
        IFACEMETHODIMP put_Separator(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveSeparatorConfig* separatorConfigConfig);

        IFACEMETHODIMP get_AdaptiveCard(_Out_ ABI::AdaptiveNamespaceRef::IAdaptiveCardConfig** adaptiveCardConfigConfig);
        IFACEMETHODIMP put_AdaptiveCard(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveCardConfig* adaptiveCardConfigConfig);

        IFACEMETHODIMP get_ImageSet(_Out_ ABI::AdaptiveNamespaceRef::IAdaptiveImageSetConfig** imageSetConfigConfig);
        IFACEMETHODIMP put_ImageSet(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveImageSetConfig* imageSetConfigConfig);

        IFACEMETHODIMP get_Image(_Out_ ABI::AdaptiveNamespaceRef::IAdaptiveImageConfig** imageConfigConfig);
        IFACEMETHODIMP put_Image(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveImageConfig* imageConfigConfig);

        IFACEMETHODIMP get_FactSet(_Out_ ABI::AdaptiveNamespaceRef::IAdaptiveFactSetConfig** factSetConfigConfig);
        IFACEMETHODIMP put_FactSet(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveFactSetConfig* factSetConfigConfig);

        IFACEMETHODIMP get_Actions(_Out_ ABI::AdaptiveNamespaceRef::IAdaptiveActionsConfig** actionsOptionConfig);
        IFACEMETHODIMP put_Actions(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveActionsConfig* actionsOptionConfig);

    private:

        Microsoft::WRL::Wrappers::HString m_fontFamily;
        boolean m_supportsInteractivity;

        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveFontSizesConfig> m_fontSizes;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveFontWeightsConfig> m_fontWeights;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveContainerStylesDefinition> m_containerStyles;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveImageSizesConfig> m_imageSizes;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveSpacingConfig> m_spacing;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveSeparatorConfig> m_separator;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveCardConfig> m_adaptiveCard;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveImageSetConfig> m_imageSet;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveImageConfig> m_image;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveFactSetConfig> m_factSet;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveActionsConfig> m_actions;
    };

    class AdaptiveHostConfigStaticsImpl WrlFinal
        : public Microsoft::WRL::AgileActivationFactory<
        ABI::AdaptiveNamespaceRef::IAdaptiveHostConfigStatics>
    {
        AdaptiveRuntimeStatic(AdaptiveHostConfig);

    public:
        IFACEMETHOD(ActivateInstance)(_COM_Outptr_ IInspectable** ppvObject) noexcept override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveHostConfig>(ppvObject);
        }

        // IAdaptiveHostConfigStatics
        IFACEMETHODIMP FromJsonString(_In_ HSTRING hostConfigJson, _COM_Outptr_ ABI::AdaptiveNamespaceRef::IAdaptiveHostConfigParseResult** config) noexcept;
        IFACEMETHODIMP FromJson(_In_ ABI::Windows::Data::Json::IJsonObject* hostConfigJson, _COM_Outptr_ ABI::AdaptiveNamespaceRef::IAdaptiveHostConfigParseResult** config) noexcept;

    private:
        HRESULT FromJsonString(_In_ const std::string jsonString, _COM_Outptr_ ABI::AdaptiveNamespaceRef::IAdaptiveHostConfigParseResult** config);
    };

    ActivatableClassWithFactory(AdaptiveHostConfig, AdaptiveHostConfigStaticsImpl);
AdaptiveNamespaceEnd