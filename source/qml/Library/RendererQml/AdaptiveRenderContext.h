#pragma once
#include "pch.h"

#include "AdaptiveElementRenderers.h"
#include "AdaptiveWarning.h"
#include "AdaptiveRenderArgs.h"

#include "SubmitAction.h"
#include "ShowCardAction.h"

namespace RendererQml
{
    class AdaptiveRenderContext;
    using CardRendererFunction = std::function<std::shared_ptr<QmlTag>(std::shared_ptr<AdaptiveCards::AdaptiveCard>, std::shared_ptr<AdaptiveRenderContext>, bool)>;

    class AdaptiveRenderContext : public std::enable_shared_from_this<AdaptiveRenderContext>
    {
    public:
        AdaptiveRenderContext(std::shared_ptr<AdaptiveCards::HostConfig> hostConfig, std::shared_ptr<AdaptiveElementRenderers<QmlTag, AdaptiveRenderContext>> elementRenderers, std::shared_ptr<AdaptiveCardRenderConfig> renderConfig);

        std::shared_ptr<QmlTag> Render(std::shared_ptr<AdaptiveCards::AdaptiveCard> card, CardRendererFunction renderFunction, bool isChildCard = false);
        std::shared_ptr<QmlTag> Render(std::shared_ptr<AdaptiveCards::BaseElement> element);

        const std::vector<AdaptiveWarning>& GetWarnings();
        void AddWarning(const AdaptiveWarning& warning);

        std::shared_ptr<AdaptiveCards::HostConfig> GetConfig();
        std::shared_ptr<AdaptiveCardRenderConfig> GetRenderConfig();

		const std::shared_ptr<AdaptiveElementRenderers<QmlTag, AdaptiveRenderContext>> GetElementRenderers();

        std::string GetRGBColor(const std::string& color, bool isQml = 1);

		std::string GetColor(const AdaptiveCards::ForegroundColor color, bool isSubtle, bool isHighlight, bool isQml = 1);

        std::string GetHexColor(const std::string& color);

        std::string GetLang();
        void SetLang(const std::string& lang);

        const int getContainerCounter();
        const int getImageCounter();
		const int getColumnSetCounter();
		const int getColumnCounter();
        const int getButtonCounter();
        const int getSelectActionCounter();

        const int getContentIndex();
        void setContentIndex(int contentCounter);
        void incrementContentIndex();

        void setCardRootId(const std::string& rootId);
        const std::string getCardRootId();

        const int getDefaultIdCounter();
        void setDefaultIdName(const std::string& defaultId);
        const std::string getDefaultIdName();

		void setCardRootElement(const std::shared_ptr<QmlTag>& rootElement);
		const std::shared_ptr<QmlTag> getCardRootElement();

		void addToInputElementList(const std::string& elementId, const std::string& value);
        const std::map<std::string, std::string> getInputElementList();

		void addToSubmitActionButtonList(const std::shared_ptr<QmlTag>& buttonElement, const std::shared_ptr<AdaptiveCards::SubmitAction>& action);
		const std::map<std::shared_ptr<QmlTag>, std::shared_ptr<AdaptiveCards::SubmitAction>> getSubmitActionButtonList();

        void addToShowCardButtonList(const std::shared_ptr<QmlTag>& buttonElement, const std::shared_ptr<AdaptiveCards::ShowCardAction>& action);
        const std::map<std::shared_ptr<QmlTag>, std::shared_ptr<AdaptiveCards::ShowCardAction>> getShowCardButtonList();
        void clearShowCardButtonList();

        void addToShowCardLoaderComponentList(const std::string& componentId, const std::shared_ptr<AdaptiveCards::ShowCardAction>& action);
        const std::map<std::string, std::shared_ptr<AdaptiveCards::ShowCardAction>> getShowCardLoaderComponentList();

        void addToTextRunSelectActionList(const std::shared_ptr<QmlTag>& textRunElement, std::map<std::string, std::shared_ptr<AdaptiveCards::BaseActionElement>>& actionList);
        const std::map<std::shared_ptr<QmlTag>, std::map<std::string, std::shared_ptr<AdaptiveCards::BaseActionElement>>> getTextRunSelectActionList();

		const int getCardWidth();

        const std::string ConvertToValidId(const std::string& id);

        const bool isShowCardInAction();
        void setIsShowCardInAction(const bool isShowCardInAction);

        AdaptiveCards::InternalId getLastActionSetInternalId();
        void setLastActionSetInternalId(AdaptiveCards::InternalId LastActionSetInternalId);

        const int GetActionSetCounter();

        void addToShowCardsLoaderIdsList(const std::string &loaderId);
        const std::vector<std::string>& getShowCardsLoaderIdsList();

        void setIsShowCardLastBodyElement(bool isShowCardLastBodyElement);
        const bool isShowCardLastBodyElement();

        void addToLastShowCardComponentIdsList(const std::string& componentId);
        const std::vector<std::string>& getLastShowCardComponentIdsList();

    private:
        bool m_isShowCardinAction{ false };
        bool m_isShowCardLastBodyElement{ false };
        AdaptiveCards::InternalId m_LastActionSetInternalIds;
        std::vector<std::string> m_ShowCardLoaderIdList;
        std::vector<std::string> m_LastShowCardComponentIdList;

        std::vector<AdaptiveWarning> m_warnings;
        bool m_ancestorHasFallback;
        std::shared_ptr<AdaptiveCards::HostConfig> m_hostConfig;
        std::shared_ptr<AdaptiveCardRenderConfig> m_renderConfig;
        AdaptiveRenderArgs m_renderArgs;
        AdaptiveCards::FeatureRegistration m_featureRegistration;
        std::string m_lang;

        std::string m_CardRootId;
        std::string m_defaultId;
		std::shared_ptr<QmlTag> m_CardRootElement;
        std::shared_ptr<AdaptiveElementRenderers<QmlTag, AdaptiveRenderContext>> m_elementRenderers;

        std::map<std::string, std::string> m_inputElementList;
        std::map<std::shared_ptr<QmlTag>, std::shared_ptr<AdaptiveCards::SubmitAction>> m_submitActionButtonList;
        std::map<std::shared_ptr<QmlTag>, std::shared_ptr<AdaptiveCards::ShowCardAction>> m_showCardButtonList;
        std::map<std::string, std::shared_ptr<AdaptiveCards::ShowCardAction>> m_showCardLoaderComponentList;
        std::map<std::shared_ptr<QmlTag>, std::map<std::string, std::shared_ptr<AdaptiveCards::BaseActionElement>>> m_textRunSelectActionList;

        int m_ContainerCounter{ 0 };
        int m_ImageCounter{ 0 };
		int m_ColumnSetCounter{ 0 };
		int m_ColumnCounter{ 0 };
        int m_ButtonCounter{ 0 };
        int m_SelectActionCounter{ 0 };
        int m_DefaultIdCounter{ 0 };
        int m_ActionSetCounter{ 0 };
        int m_ContentIndex{ 0 };

    };
}
