// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Uwp
{
    class DECLSPEC_UUID("6A0EFDB7-AC1B-4C76-981E-2188297095AD") AdaptiveHostConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveHostConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const HostConfig& config);

        // IAdaptiveHostConfig
        IFACEMETHODIMP get_FontFamily(_Outptr_ HSTRING* text) override;
        IFACEMETHODIMP put_FontFamily(_In_ HSTRING text) override;

        IFACEMETHODIMP get_FontSizes(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontSizesConfig** fontSize) override;
        IFACEMETHODIMP put_FontSizes(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontSizesConfig* fontSize) override;

        IFACEMETHODIMP get_FontWeights(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontWeightsConfig** fontWeight) override;
        IFACEMETHODIMP put_FontWeights(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontWeightsConfig* fontWeight) override;

        IFACEMETHODIMP get_FontTypes(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontTypesDefinition** value) override;
        IFACEMETHODIMP put_FontTypes(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontTypesDefinition* value) override;

        IFACEMETHODIMP get_SupportsInteractivity(_Out_ boolean* supportsInteractivity) override;
        IFACEMETHODIMP put_SupportsInteractivity(boolean supportsInteractivity) override;

        IFACEMETHODIMP get_ImageBaseUrl(_Outptr_ HSTRING* imageBaseUrl) override;
        IFACEMETHODIMP put_ImageBaseUrl(_In_ HSTRING imageBaseUrl) override;

        IFACEMETHODIMP get_ContainerStyles(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStylesDefinition** value) override;
        IFACEMETHODIMP put_ContainerStyles(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStylesDefinition* value) override;

        IFACEMETHODIMP get_ImageSizes(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveImageSizesConfig** imageConfig) override;
        IFACEMETHODIMP put_ImageSizes(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveImageSizesConfig* imageConfig) override;

        IFACEMETHODIMP get_Spacing(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveSpacingConfig** spacingConfigConfig) override;
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveSpacingConfig* spacingConfigConfig) override;

        IFACEMETHODIMP get_Separator(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveSeparatorConfig** separatorConfigConfig) override;
        IFACEMETHODIMP put_Separator(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveSeparatorConfig* separatorConfigConfig) override;

        IFACEMETHODIMP get_AdaptiveCard(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardConfig** adaptiveCardConfigConfig) override;
        IFACEMETHODIMP put_AdaptiveCard(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardConfig* adaptiveCardConfigConfig) override;

        IFACEMETHODIMP get_ImageSet(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveImageSetConfig** imageSetConfigConfig) override;
        IFACEMETHODIMP put_ImageSet(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveImageSetConfig* imageSetConfigConfig) override;

        IFACEMETHODIMP get_Image(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveImageConfig** imageConfigConfig) override;
        IFACEMETHODIMP put_Image(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveImageConfig* imageConfigConfig) override;

        IFACEMETHODIMP get_FactSet(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFactSetConfig** factSetConfigConfig) override;
        IFACEMETHODIMP put_FactSet(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFactSetConfig* factSetConfigConfig);

        IFACEMETHODIMP get_Actions(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionsConfig** actionsOptionConfig) override;
        IFACEMETHODIMP put_Actions(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionsConfig* actionsOptionConfig) override;

        IFACEMETHODIMP get_Media(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveMediaConfig** mediaConfig) override;
        IFACEMETHODIMP put_Media(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveMediaConfig* mediaConfig) override;

        IFACEMETHODIMP get_Inputs(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputsConfig** inputsConfig) override;
        IFACEMETHODIMP put_Inputs(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputsConfig* inputsConfig) override;

        IFACEMETHODIMP get_TextBlock(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextBlockConfig** textBlockConfig) override;
        IFACEMETHODIMP put_TextBlock(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextBlockConfig* textBlockConfig) override;

        IFACEMETHODIMP get_TextStyles(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextStylesConfig** textStylesConfig) override;
        IFACEMETHODIMP put_TextStyles(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextStylesConfig* textStylesConfig) override;

        IFACEMETHODIMP get_Table(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTableConfig** tableConfig) override;
        IFACEMETHODIMP put_Table(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTableConfig* tableConfig) override;

        // Additional host properties that can be set by the host via AdaptiveCardRenderer APIs but are not part of the host config API/Schema.
        HRESULT get_OverflowMaxActions(_Out_ boolean* overflowMaxActions);
        HRESULT put_OverflowMaxActions(boolean overflowMaxActions);

        HRESULT get_OverflowButtonText(_Outptr_ HSTRING* overflowButtonText);
        HRESULT put_OverflowButtonText(_In_ HSTRING overflowButtonText);

        HRESULT get_OverflowButtonAccessibilityText(_Outptr_ HSTRING* overflowButtonAccessibilityText);
        HRESULT put_OverflowButtonAccessibilityText(_In_ HSTRING overflowButtonAccessibilityText);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::Wrappers::HString m_fontFamily;
        boolean m_supportsInteractivity;
        Microsoft::WRL::Wrappers::HString m_imageBaseUrl;

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontSizesConfig> m_fontSizes;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontWeightsConfig> m_fontWeights;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontTypesDefinition> m_fontTypes;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStylesDefinition> m_containerStyles;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveImageSizesConfig> m_imageSizes;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveSpacingConfig> m_spacing;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveSeparatorConfig> m_separator;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardConfig> m_adaptiveCard;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveImageSetConfig> m_imageSet;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveImageConfig> m_image;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFactSetConfig> m_factSet;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionsConfig> m_actions;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveMediaConfig> m_media;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputsConfig> m_inputs;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextBlockConfig> m_textBlock;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextStylesConfig> m_textStyles;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTableConfig> m_table;

        bool m_overflowMaxActions;
        HString m_overflowButtonText;
        HString m_overflowButtonAccessibilityText;
    };

    class AdaptiveHostConfigStaticsImpl WrlFinal
        : public Microsoft::WRL::AgileActivationFactory<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfigStatics>
    {
        AdaptiveRuntimeStatic(AdaptiveHostConfig);

    public:
        IFACEMETHOD(ActivateInstance)(_COM_Outptr_ IInspectable** ppvObject) noexcept override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveHostConfig>(ppvObject);
        }

        // IAdaptiveHostConfigStatics
        IFACEMETHODIMP FromJsonString(_In_ HSTRING hostConfigJson,
                                      _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfigParseResult** config) noexcept;
        IFACEMETHODIMP FromJson(_In_ ABI::Windows::Data::Json::IJsonObject* hostConfigJson,
                                _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfigParseResult** config) noexcept;

    private:
        HRESULT _FromJsonString(const std::string& jsonString,
                                _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfigParseResult** config);
    };

    ActivatableClassWithFactory(AdaptiveHostConfig, AdaptiveHostConfigStaticsImpl);
}
