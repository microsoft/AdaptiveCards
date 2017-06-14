#pragma once

#include "BaseCardElement.h"
#include "BaseActionElement.h"
#include "Container.h"
#include "Enums.h"
#include "pch.h"

namespace AdaptiveCards
{
class Container;

class AdaptiveCard
{
public:
    AdaptiveCard();
    AdaptiveCard(std::string version, std::string minVersion, std::string fallbackText, std::string backgroundImageUrl);
    AdaptiveCard(
        std::string version,
        std::string minVersion,
        std::string fallbackText,
        std::string backgroundImageUrl,
        std::vector<std::shared_ptr<BaseCardElement>>& body,
        std::vector<std::shared_ptr<BaseActionElement>>& actions);

    std::string GetVersion() const;
    void SetVersion(const std::string value);
    std::string GetMinVersion() const;
    void SetMinVersion(const std::string value);
    std::string GetFallbackText() const;
    void SetFallbackText(const std::string value);
    std::string GetBackgroundImageUrl () const;
    void SetBackgroundImageUrl(const std::string value);

    std::vector<std::shared_ptr<BaseCardElement>>& GetBody();
    const std::vector<std::shared_ptr<BaseCardElement>>& GetBody() const;
    const std::vector<std::shared_ptr<BaseActionElement>>& GetActions() const;

    const CardElementType GetElementType() const;

    static std::shared_ptr<AdaptiveCard> DeserializeFromFile(const std::string& jsonFile) throw(AdaptiveCards::AdaptiveCardParseException);
    static std::shared_ptr<AdaptiveCard> Deserialize(const Json::Value& json) throw(AdaptiveCards::AdaptiveCardParseException);
    static std::shared_ptr<AdaptiveCard> DeserializeFromString(const std::string& jsonString) throw(AdaptiveCards::AdaptiveCardParseException);
    Json::Value SerializeToJsonValue();
    std::string Serialize();

private:
    static const std::unordered_map<CardElementType, std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)>, EnumHash> CardElementParsers;
    static const std::unordered_map<ActionType, std::function<std::shared_ptr<BaseActionElement>(const Json::Value&)>, EnumHash> CardActionParsers;

    std::string m_version;
    std::string m_minVersion;
    std::string m_fallbackText;
    std::string m_backgroundImageUrl;

    std::vector<std::shared_ptr<BaseCardElement>> m_body;
    std::vector<std::shared_ptr<BaseActionElement>> m_actions;

};
}