#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"

namespace AdaptiveCards
{
class Fact
{
public:
    Fact();
    Fact(std::string title, std::string value);

    std::string Serialize();
    Json::Value SerializeToJsonValue();

    std::string GetTitle() const;
    void SetTitle(const std::string value);

    std::string GetValue() const;
    void SetValue(const std::string value);

    static std::shared_ptr<Fact> Deserialize(const Json::Value& root);
    static std::shared_ptr<Fact> DeserializeFromString(const std::string& jsonString);

private:
    std::string m_title;
    std::string m_value;
};
}
