#pragma once
#include "pch.h"

#include "AdaptiveElementRenderers.h"
#include "AdaptiveWarning.h"
#include "AdaptiveRenderArgs.h"

namespace RendererQml
{
    class AdaptiveRenderContext;
    using CardRendererFunction = std::function<std::shared_ptr<QmlTag>(std::shared_ptr<AdaptiveCards::AdaptiveCard>, std::shared_ptr<AdaptiveRenderContext>)>;

    class AdaptiveRenderContext : public std::enable_shared_from_this<AdaptiveRenderContext>
    {
    public:
        AdaptiveRenderContext(std::shared_ptr<AdaptiveCards::HostConfig> hostConfig, std::shared_ptr<AdaptiveElementRenderers<QmlTag, AdaptiveRenderContext>> elementRenderers);

        std::shared_ptr<QmlTag> Render(std::shared_ptr<AdaptiveCards::AdaptiveCard> card, CardRendererFunction renderFunction);
        std::shared_ptr<QmlTag> Render(std::shared_ptr<AdaptiveCards::BaseElement> element);

        const std::vector<AdaptiveWarning>& GetWarnings();
        void AddWarning(const AdaptiveWarning& warning);

        std::shared_ptr<AdaptiveCards::HostConfig> GetConfig();

        std::string GetRGBColor(const std::string& color, bool isQml = 1);

		std::string GetColor(const AdaptiveCards::ForegroundColor color, bool isSubtle, bool isHighlight, bool isQml = 1);

        std::string GetLang();
        void SetLang(const std::string& lang);

        void SetOnClickFunction(AdaptiveCardDependency::OnClickFunction onClickFunction);
        AdaptiveCardDependency::OnClickFunction& GetOnClickFunction();

        const int getContainerCounter();
        const int getImageCounter();
		const int getColumnSetCounter();
		const int getColumnCounter();

    private:
        std::vector<AdaptiveWarning> m_warnings;
        bool m_ancestorHasFallback;
        std::shared_ptr<AdaptiveCards::HostConfig> m_hostConfig;
        AdaptiveRenderArgs m_renderArgs;
        AdaptiveCards::FeatureRegistration m_featureRegistration;
        std::shared_ptr<AdaptiveElementRenderers<QmlTag, AdaptiveRenderContext>> m_elementRenderers;
        std::string m_lang;
        AdaptiveCardDependency::OnClickFunction m_onClickFunction;
        int m_ContainerCounter{ 0 };
        int m_ImageCounter{ 0 };
		int m_ColumnSetCounter{ 0 };
		int m_ColumnCounter{ 0 };
    };
}
