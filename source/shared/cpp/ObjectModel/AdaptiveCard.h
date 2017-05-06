#pragma once

#include "Enums.h"
#include "pch.h"
#include "BaseCardElement.h"
#include "Container.h"

namespace AdaptiveCards
{
class Container;

class AdaptiveCard
{
public:
    AdaptiveCard();
    AdaptiveCard(std::string version, std::string minVersion, std::string fallbackText, std::string backgroundImageUrl);
    AdaptiveCard(std::string version, std::string minVersion, std::string fallbackText, std::string backgroundImageUrl, std::vector<std::shared_ptr<BaseCardElement>>& body);

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

    const CardElementType GetElementType() const;

    static std::shared_ptr<AdaptiveCard> DeserializeFromFile(const std::string& jsonFile);
    static std::shared_ptr<AdaptiveCard> Deserialize(const Json::Value& json);
    static std::shared_ptr<AdaptiveCard> DeserializeFromString(const std::string& jsonString);

private:
    static const std::unordered_map<CardElementType, std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)>, EnumHash> CardElementParsers;

    std::string m_version;
    std::string m_minVersion;
    std::string m_fallbackText;
    std::string m_backgroundImageUrl;

    std::vector<std::shared_ptr<BaseCardElement>> m_body;

};
}