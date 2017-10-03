#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveHostConfig :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveHostConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const HostConfig& config);

        // IAdaptiveHostConfig
        IFACEMETHODIMP get_FontFamily(_Out_ HSTRING* text);
        IFACEMETHODIMP put_FontFamily(_In_ HSTRING text);

        IFACEMETHODIMP get_FontSizes(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveFontSizesConfig** fontSize);
        IFACEMETHODIMP put_FontSizes(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveFontSizesConfig* fontSize);

        IFACEMETHODIMP get_FontWeights(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveFontWeightsConfig** fontWeight);
        IFACEMETHODIMP put_FontWeights(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveFontWeightsConfig* fontWeight);

        IFACEMETHODIMP get_SupportsInteractivity(_Out_ boolean* supportsInteractivity);
        IFACEMETHODIMP put_SupportsInteractivity(_In_ boolean supportsInteractivity);

        IFACEMETHODIMP get_ContainerStyles(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveContainerStylesDefinition** value);
        IFACEMETHODIMP put_ContainerStyles(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveContainerStylesDefinition* value);

        IFACEMETHODIMP get_ImageSizes(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveImageSizesConfig** imageConfig);
        IFACEMETHODIMP put_ImageSizes(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveImageSizesConfig* imageConfig);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveSpacingConfig** spacingConfigConfig);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveSpacingConfig* spacingConfigConfig);

        IFACEMETHODIMP get_Separator(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveSeparatorConfig** separatorConfigConfig);
        IFACEMETHODIMP put_Separator(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveSeparatorConfig* separatorConfigConfig);

        IFACEMETHODIMP get_AdaptiveCard(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveCardConfig** adaptiveCardConfigConfig);
        IFACEMETHODIMP put_AdaptiveCard(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardConfig* adaptiveCardConfigConfig);

        IFACEMETHODIMP get_ImageSet(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveImageSetConfig** imageSetConfigConfig);
        IFACEMETHODIMP put_ImageSet(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveImageSetConfig* imageSetConfigConfig);

        IFACEMETHODIMP get_Image(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveImageConfig** imageConfigConfig);
        IFACEMETHODIMP put_Image(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveImageConfig* imageConfigConfig);

        IFACEMETHODIMP get_FactSet(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveFactSetConfig** factSetConfigConfig);
        IFACEMETHODIMP put_FactSet(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveFactSetConfig* factSetConfigConfig);

        IFACEMETHODIMP get_Actions(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveActionsConfig** actionsOptionConfig);
        IFACEMETHODIMP put_Actions(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveActionsConfig* actionsOptionConfig);

    private:
        HostConfig m_sharedHostConfig;
    };

    class AdaptiveHostConfigStaticsImpl WrlFinal
        : public Microsoft::WRL::AgileActivationFactory<
        ABI::AdaptiveCards::Uwp::IAdaptiveHostConfigStatics>
    {
        InspectableClassStatic(RuntimeClass_AdaptiveCards_Uwp_AdaptiveHostConfig, TrustLevel::BaseTrust);

    public:
        IFACEMETHOD(ActivateInstance)(_COM_Outptr_ IInspectable** ppvObject) noexcept override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveHostConfig>(ppvObject);
        }

        // IAdaptiveHostConfigStatics
        IFACEMETHODIMP FromJsonString(_In_ HSTRING hostConfigJson, _COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveHostConfigParseResult** config) noexcept;
        IFACEMETHODIMP FromJson(_In_ ABI::Windows::Data::Json::IJsonObject* hostConfigJson, _COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveHostConfigParseResult** config) noexcept;

    private:
        HRESULT FromJsonString(_In_ const std::string jsonString, _COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveHostConfigParseResult** config);
    };

    ActivatableClassWithFactory(AdaptiveHostConfig, AdaptiveHostConfigStaticsImpl);
}}