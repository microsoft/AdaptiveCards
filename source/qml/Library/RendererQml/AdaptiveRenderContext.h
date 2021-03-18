#pragma once
#include "pch.h"

#include "AdaptiveElementRenderers.h"
#include "AdaptiveWarning.h"
#include "AdaptiveRenderArgs.h"

#include "SubmitAction.h"

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

        const int getContainerCounter();
        const int getImageCounter();
		const int getColumnSetCounter();
		const int getColumnCounter();
        const int getButtonCounter();

        void setCardRootId(const std::string& rootId);
        const std::string getCardRootId();

        void addToInputElementList(const std::string& elementId, const std::string& value);
        const std::map<std::string, std::string> getInputElementList();

        void addToActionButtonList(const std::shared_ptr<QmlTag>& buttonElement, const std::shared_ptr<AdaptiveCards::BaseActionElement>& action);
        const std::map<std::shared_ptr<QmlTag>, std::shared_ptr<AdaptiveCards::BaseActionElement>> getActionButtonList();

    private:
        std::vector<AdaptiveWarning> m_warnings;
        bool m_ancestorHasFallback;
        std::shared_ptr<AdaptiveCards::HostConfig> m_hostConfig;
        AdaptiveRenderArgs m_renderArgs;
        AdaptiveCards::FeatureRegistration m_featureRegistration;
        std::shared_ptr<AdaptiveElementRenderers<QmlTag, AdaptiveRenderContext>> m_elementRenderers;
        std::string m_lang;
        std::string m_CardRootId;
        std::map<std::string, std::string> m_inputElementList;
        std::map<std::shared_ptr<QmlTag>, std::shared_ptr<AdaptiveCards::BaseActionElement>> m_actionButtonList;

        int m_ContainerCounter{ 0 };
        int m_ImageCounter{ 0 };
		int m_ColumnSetCounter{ 0 };
		int m_ColumnCounter{ 0 };
        int m_ButtonCounter{ 0 };
    };
}
