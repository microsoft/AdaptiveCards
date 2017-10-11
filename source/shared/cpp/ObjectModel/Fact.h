#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"
#include "ElementParserRegistration.h"

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

    static std::shared_ptr<Fact> Deserialize(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration, 
        const Json::Value& root);

    static std::shared_ptr<Fact> DeserializeFromString(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration, 
        const std::string& jsonString);

private:
    std::string m_title;
    std::string m_value;
};
}
