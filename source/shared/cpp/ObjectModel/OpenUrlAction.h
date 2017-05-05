#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "Enums.h"

namespace AdaptiveCards
{
class OpenUrlAction : public BaseActionElement
{
public:
    OpenUrlAction();

    static std::shared_ptr<OpenUrlAction> Deserialize(const Json::Value& root);
    static std::shared_ptr<OpenUrlAction> DeserializeFromString(const std::string& jsonString);

    virtual std::string Serialize();

    std::string GetUrl() const;
    void SetUrl(const std::string value);
    
private:
    std::string m_url;
};
}