#pragma once

#include "pch.h"
#include "Enums.h"
#include "BaseCardElement.h"
#include "Container.h"

namespace AdaptiveCards
{
class Container;

class AdaptiveCard
{
public:
    AdaptiveCard();
    AdaptiveCard(std::string version, std::string minVersion, std::string fallbackText);
    AdaptiveCard(std::string version, std::string minVersion, std::string fallbackText, std::vector<std::shared_ptr<BaseCardElement>>& body);

    std::string GetVersion() const;
    void SetVersion(const std::string value);
    std::string GetMinVersion() const;
    void SetMinVersion(const std::string value);
    std::string GetFallbackText() const;
    void SetFallbackText(const std::string value);

    std::vector<std::shared_ptr<BaseCardElement>>& GetBody();
    const std::vector<std::shared_ptr<BaseCardElement>>& GetBody() const;

    const CardElementType GetElementType() const;

    static std::shared_ptr<AdaptiveCard> DeserializeFromFile(const std::string & jsonFile);
    static std::shared_ptr<AdaptiveCard> Deserialize(const Json::Value& json);

private:

    static const std::unordered_map<CardElementType, std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)>> CardElementParsers;

    std::string m_version;
    std::string m_minVersion;
    std::string m_fallbackText;

    std::vector<std::shared_ptr<BaseCardElement>> m_body;

};
}